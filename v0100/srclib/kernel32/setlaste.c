/*
  Copyright (c) 2014-2019, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

#define DLL "kernel32"
#define FXN "SetLastError"
#include "../dimports.h"

void __SetLastError(unsigned Error)
{
  asm(
    "push dword [ebp+8]\n"
    "call dword [__imp__SetLastError]"
  );
}

#endif // _WINDOWS
