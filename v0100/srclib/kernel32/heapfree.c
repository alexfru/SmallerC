/*
  Copyright (c) 2014-2019, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

#define DLL "kernel32"
#define FXN "HeapFree"
#include "../dimports.h"

int __HeapFree(unsigned hHeap,
               unsigned dwFlags,
               void* lpMem)
{
  asm(
    "push dword [ebp+16]\n"
    "push dword [ebp+12]\n"
    "push dword [ebp+8]\n"
    "call dword [__imp__HeapFree]"
  );
}

#endif // _WINDOWS
