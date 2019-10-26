/*
  Copyright (c) 2014-2019, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

#define DLL "kernel32"
#define FXN "GetProcessHeap"
#include "../dimports.h"

unsigned __GetProcessHeap(void)
{
  asm(
    "call dword [__imp__GetProcessHeap]"
  );
}

#endif // _WINDOWS
