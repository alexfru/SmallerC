/*
  Copyright (c) 2014-2019, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

#define DLL "kernel32"
#define FXN "FreeLibrary"
#include "../dimports.h"

int __FreeLibrary(void* hModule)
{
  asm(
    "push dword [ebp+8]\n"
    "call dword [__imp__FreeLibrary]"
  );
}

#endif // _WINDOWS
