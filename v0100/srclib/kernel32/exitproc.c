/*
  Copyright (c) 2014-2019, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

#define DLL "kernel32"
#define FXN "ExitProcess"
#include "../dimports.h"

void __ExitProcess(unsigned ExitCode)
{
  asm(
    "push dword [ebp+8]\n"
    "call dword [__imp__ExitProcess]"
  );
}

#endif // _WINDOWS
