/*
  Copyright (c) 2014-2019, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

#define DLL "kernel32"
#define FXN "HeapAlloc"
#include "../dimports.h"

void* __HeapAlloc(unsigned hHeap,
                  unsigned dwFlags,
                  unsigned dwBytes)
{
  asm(
    "push dword [ebp+16]\n"
    "push dword [ebp+12]\n"
    "push dword [ebp+8]\n"
    "call dword [__imp__HeapAlloc]"
  );
}

#endif // _WINDOWS
