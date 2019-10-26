/*
  Copyright (c) 2014-2019, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

#define DLL "kernel32"
#define FXN "GetCommandLineA"
#include "../dimports.h"

char* __GetCommandLineA(void)
{
  asm(
    "call dword [__imp__GetCommandLineA]"
  );
}

#endif // _WINDOWS
