/*
  Copyright (c) 2014-2016, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm(
  "section .kernel32_hints\n"
  "dd _hint_SetUnhandledExceptionFilter"
);

asm(
  "section .kernel32_iat\n"
  "__imp__SetUnhandledExceptionFilter: dd _hint_SetUnhandledExceptionFilter"
);

static char hint_SetUnhandledExceptionFilter[] = "\0\0SetUnhandledExceptionFilter";

extern char _kernel32_dll__[];
static char* pdll = _kernel32_dll__; // pull trailers for sections .kernel32_hints and .kernel32_iat

typedef struct TOP_LEVEL_EXCEPTION_FILTER TOP_LEVEL_EXCEPTION_FILTER;

TOP_LEVEL_EXCEPTION_FILTER* SetUnhandledExceptionFilter(TOP_LEVEL_EXCEPTION_FILTER* lpTopLevelExceptionFilter)
{
  asm(
    "push dword [ebp+8]\n"
    "call dword [__imp__SetUnhandledExceptionFilter]"
  );
}

#endif // _WINDOWS
