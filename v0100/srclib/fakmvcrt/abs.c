/*
  Copyright (c) 2021, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

#define DLL "msvcrt"
#define FXN "abs"
#include "../dimports.h"

int __msvcrt_abs(int x)
{
  asm(
    "push dword [ebp+8]\n"
    "call dword [__imp__abs]\n"
    "add  esp, 4"
  );
}

#endif // _WINDOWS
