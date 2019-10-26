/*
  Copyright (c) 2014-2019, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

#define DLL "kernel32"
#define FXN "HeapReAlloc"
#include "../dimports.h"

void* __HeapReAlloc(unsigned hHeap,
                    unsigned dwFlags,
                    void* lpMem,
                    unsigned dwBytes)
{
  asm(
    "push dword [ebp+20]\n"
    "push dword [ebp+16]\n"
    "push dword [ebp+12]\n"
    "push dword [ebp+8]\n"
    "call dword [__imp__HeapReAlloc]"
  );
}

#endif // _WINDOWS
