/*
  Copyright (c) 2014-2019, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

#define DLL "kernel32"
#define FXN "SetFilePointer"
#include "../dimports.h"

unsigned __SetFilePointer(unsigned hFile,
                          int lDistanceToMove,
                          int* lpDistanceToMoveHigh,
                          unsigned dwMoveMethod)
{
  asm(
    "push dword [ebp+20]\n"
    "push dword [ebp+16]\n"
    "push dword [ebp+12]\n"
    "push dword [ebp+8]\n"
    "call dword [__imp__SetFilePointer]"
  );
}

#endif // _WINDOWS
