/*
  Copyright (c) 2014-2019, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

#define DLL "kernel32"
#define FXN "GetSystemTime"
#include "../dimports.h"

struct _SYSTEMTIME;

void __GetSystemTime(struct _SYSTEMTIME* pSystemTime)
{
  asm(
    "push dword [ebp+8]\n"
    "call dword [__imp__GetSystemTime]"
  );
}

#endif // _WINDOWS
