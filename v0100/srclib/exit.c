/*
  Copyright (c) 2014-2017, Alexey Frunze
  2-clause BSD license.
*/
#include "istdio.h"

#ifdef __HUGE__
#define __HUGE_OR_UNREAL__
#endif
#ifdef __UNREAL__
#define __HUGE_OR_UNREAL__
#endif

#ifdef _LINUX
#define UNIX_LIKE
#endif
#ifdef _MACOS
#define UNIX_LIKE
#endif

void (*__pAtExitIterator)(void);
void (*__pFileCloser)(void);

#ifdef _DOS

#include "idos.h"

#ifdef __HUGE_OR_UNREAL__
static
void DosTerminate(int e, ...)
{
#ifdef __UNREAL__
  asm("mov eax, [bp + 12]\n"
      "mov [0xd*4], eax");
#endif
  asm("mov ah, 0x4c\n"
      "mov al, [bp + 8]\n"
      "int 0x21");
}
#endif
#ifdef __SMALLER_C_16__
static
void DosTerminate(int e)
{
  asm("mov ah, 0x4c\n"
      "mov al, [bp + 4]\n"
      "int 0x21");
}
#endif
#ifdef _DPMI
#include "idpmi.h"
static
void DosTerminate(int e)
{
  // Exit using the initial 16-bit code and data selectors and free the 32-bit ones,
  // so they aren't leaked
  __dpmi_terminate(e);
}
#endif

#endif // _DOS

#ifdef _WINDOWS

#include "iwin32.h"

#endif // _WINDOWS

#ifdef _LINUX

static
void SysExit(int status)
{
  asm("mov eax, 1\n" // sys_exit
      "mov ebx, [ebp + 8]\n"
      "int 0x80");
}

#endif // _LINUX

#ifdef _MACOS

static
void SysExit(int status)
{
  asm("mov eax, 1\n" // sys_exit
      "push dword [ebp + 8]\n"
      "sub   esp, 4\n"
      "int 0x80");
}

#endif // _MACOS

void __ExitInner(int iterator, int flushclose, int status)
{
  if (iterator && __pAtExitIterator)
    __pAtExitIterator();

  if (flushclose)
  {
    if (__pFileCloser)
      __pFileCloser();

    fclose(stdin);
    fclose(stdout);
    fclose(stderr);
  }

#ifdef _DOS
#ifndef _DPMI
  __DosSetVect(0, __Int00DE);
//  __DosSetVect(1, __Int01DB);
//  __DosSetVect(3, __Int03BP);
  __DosSetVect(4, __Int04OF);
  __DosSetVect(6, __Int06UD);
#endif

#ifdef __UNREAL__
  extern unsigned long __pOldInt0xdIsr;
  DosTerminate(status, __pOldInt0xdIsr);
#else
  DosTerminate(status);
#endif
#endif // _DOS

#ifdef _WINDOWS
  __ExitProcess(status);
#endif // _WINDOWS

#ifdef UNIX_LIKE
  SysExit(status);
#endif // UNIX_LIKE
}

void _Exit(int status)
{
  __ExitInner(0, 0, status);
}

void exit(int status)
{
  __ExitInner(1, 1, status);
}
