/*
  Copyright (c) 2014-2019, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

#define DLL "kernel32"
#define FXN "GetTickCount"
#include "../dimports.h"

unsigned __GetTickCount(void)
{
  asm(
    "call dword [__imp__GetTickCount]"
  );
}

#endif // _WINDOWS
