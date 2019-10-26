/*
  Copyright (c) 2014-2019, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

#define DLL "kernel32"
#define FXN "GetProcAddress"
#include "../dimports.h"

void (*__GetProcAddress(void* hModule, char* lpProcName))()
{
  asm(
    "push dword [ebp+12]\n"
    "push dword [ebp+8]\n"
    "call dword [__imp__GetProcAddress]"
  );
}

#endif // _WINDOWS
