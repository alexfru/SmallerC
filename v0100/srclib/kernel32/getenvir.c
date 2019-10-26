/*
  Copyright (c) 2014-2019, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

#define DLL "kernel32"
#define FXN "GetEnvironmentVariableA"
#include "../dimports.h"

unsigned __GetEnvironmentVariableA(char* lpName,
                                   char* lpBuffer,
                                   unsigned nSize)
{
  asm(
    "push dword [ebp+16]\n"
    "push dword [ebp+12]\n"
    "push dword [ebp+8]\n"
    "call dword [__imp__GetEnvironmentVariableA]"
  );
}

#endif // _WINDOWS
