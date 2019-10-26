/*
  Copyright (c) 2014-2019, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

#define DLL "kernel32"
#define FXN "GetExitCodeProcess"
#include "../dimports.h"

int __GetExitCodeProcess(unsigned hProcess, unsigned* lpExitCode)
{
  asm(
    "push dword [ebp+12]\n"
    "push dword [ebp+8]\n"
    "call dword [__imp__GetExitCodeProcess]"
  );
}

#endif // _WINDOWS
