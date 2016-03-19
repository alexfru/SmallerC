/*
  Copyright (c) 2014-2016, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm(
  "section .kernel32_hints\n"
  "dd _hint_GetSystemTime"
);

asm(
  "section .kernel32_iat\n"
  "__imp__GetSystemTime: dd _hint_GetSystemTime"
);

static char hint_GetSystemTime[] = "\0\0GetSystemTime";

extern char _kernel32_dll__[];
static char* pdll = _kernel32_dll__; // pull trailers for sections .kernel32_hints and .kernel32_iat

struct _SYSTEMTIME;

void GetSystemTime(struct _SYSTEMTIME* pSystemTime)
{
  asm(
    "push dword [ebp+8]\n"
    "call dword [__imp__GetSystemTime]"
  );
}

#endif // _WINDOWS
