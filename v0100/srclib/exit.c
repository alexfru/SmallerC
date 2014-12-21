/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include "istdio.h"

void (*__pAtExitIterator)(void);
void (*__pFileCloser)(void);

#ifdef _DOS

#include "idos.h"

#ifdef __HUGE__
static
void DosTerminate(int e)
{
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
  __DosSetVect(0, __Int00DE);
//  __DosSetVect(1, __Int01DB);
//  __DosSetVect(3, __Int03BP);
  __DosSetVect(4, __Int04OF);
  __DosSetVect(6, __Int06UD);

  DosTerminate(status);
#endif // _DOS

#ifdef _WINDOWS
  ExitProcess(status);
#endif // _WINDOWS

#ifdef _LINUX
  SysExit(status);
#endif // _LINUX
}

void _Exit(int status)
{
  __ExitInner(0, 0, status);
}

void exit(int status)
{
  __ExitInner(1, 1, status);
}
