/*
  Copyright (c) 2014-2019, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

#define DLL "kernel32"
#define FXN "ReadFile"
#include "../dimports.h"

int __ReadFile(unsigned Handle,
               void* Buffer,
               unsigned NumberOfBytesToRead,
               unsigned* NumberOfBytesRead,
               void* Overlapped)
{
  asm(
    "push dword [ebp+24]\n"
    "push dword [ebp+20]\n"
    "push dword [ebp+16]\n"
    "push dword [ebp+12]\n"
    "push dword [ebp+8]\n"
    "call dword [__imp__ReadFile]"
  );
}

#endif // _WINDOWS
