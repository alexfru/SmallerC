/*
  Copyright (c) 2014-2019, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

#define DLL "kernel32"
#define FXN "GetFileType"
#include "../dimports.h"

unsigned __GetFileType(unsigned Handle)
{
  asm(
    "push dword [ebp+8]\n"
    "call dword [__imp__GetFileType]"
  );
}

#endif // _WINDOWS
