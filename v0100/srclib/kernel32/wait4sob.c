/*
  Copyright (c) 2014-2019, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

#define DLL "kernel32"
#define FXN "WaitForSingleObject"
#include "../dimports.h"

unsigned __WaitForSingleObject(unsigned hHandle, unsigned dwMilliseconds)
{
  asm(
    "push dword [ebp+12]\n"
    "push dword [ebp+8]\n"
    "call dword [__imp__WaitForSingleObject]"
  );
}

#endif // _WINDOWS
