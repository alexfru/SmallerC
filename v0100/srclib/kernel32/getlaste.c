/*
  Copyright (c) 2014-2019, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

#define DLL "kernel32"
#define FXN "GetLastError"
#include "../dimports.h"

unsigned __GetLastError(void)
{
  asm(
    "call dword [__imp__GetLastError]"
  );
}

#endif // _WINDOWS
