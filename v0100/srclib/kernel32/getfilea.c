/*
  Copyright (c) 2014-2019, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

#define DLL "kernel32"
#define FXN "GetFileAttributesA"
#include "../dimports.h"

unsigned __GetFileAttributesA(char* lpFileName)
{
  asm(
    "push dword [ebp+8]\n"
    "call dword [__imp__GetFileAttributesA]"
  );
}

#endif // _WINDOWS
