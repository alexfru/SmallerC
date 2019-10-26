/*
  Copyright (c) 2014-2019, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

#define DLL "kernel32"
#define FXN "MoveFileA"
#include "../dimports.h"

int __MoveFileA(char* lpExistingFileName, char* lpNewFileName)
{
  asm(
    "push dword [ebp+12]\n"
    "push dword [ebp+8]\n"
    "call dword [__imp__MoveFileA]"
  );
}

#endif // _WINDOWS
