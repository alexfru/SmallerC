/*
  Copyright (c) 2014-2019, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

#define DLL "kernel32"
#define FXN "DeleteFileA"
#include "../dimports.h"

int __DeleteFileA(char* FileName)
{
  asm(
    "push dword [ebp+8]\n"
    "call dword [__imp__DeleteFileA]"
  );
}

#endif // _WINDOWS
