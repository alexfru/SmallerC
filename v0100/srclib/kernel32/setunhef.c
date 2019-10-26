/*
  Copyright (c) 2014-2019, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

#define DLL "kernel32"
#define FXN "SetUnhandledExceptionFilter"
#include "../dimports.h"

typedef struct TOP_LEVEL_EXCEPTION_FILTER TOP_LEVEL_EXCEPTION_FILTER;

TOP_LEVEL_EXCEPTION_FILTER* __SetUnhandledExceptionFilter(TOP_LEVEL_EXCEPTION_FILTER* lpTopLevelExceptionFilter)
{
  asm(
    "push dword [ebp+8]\n"
    "call dword [__imp__SetUnhandledExceptionFilter]"
  );
}

#endif // _WINDOWS
