/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include "istdio.h"

void (*__pAtExitIterator)(void);
void (*__pFileCloser)(void);

#ifdef _DOS

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

void _Exit(int status)
{
  DosTerminate(status);
}

void exit(int status)
{
  if (__pAtExitIterator)
    __pAtExitIterator();

  if (__pFileCloser)
    __pFileCloser();

  fflush(stdout);
  fflush(stderr);

  DosTerminate(status);
}

#endif // _DOS

#ifdef _WINDOWS

#include "iwin32.h"

void _Exit(int status)
{
  ExitProcess(status);
}

void exit(int status)
{
  if (__pAtExitIterator)
    __pAtExitIterator();

  if (__pFileCloser)
    __pFileCloser();

  fflush(stdout);
  fflush(stderr);

  ExitProcess(status);
}

#endif // _WINDOWS
