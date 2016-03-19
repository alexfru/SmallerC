/*
  Copyright (c) 2014-2016, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm(
  "section .kernel32_hints\n"
  "dd _hint_GetTickCount"
);

asm(
  "section .kernel32_iat\n"
  "__imp__GetTickCount: dd _hint_GetTickCount"
);

static char hint_GetTickCount[] = "\0\0GetTickCount";

extern char _kernel32_dll__[];
static char* pdll = _kernel32_dll__; // pull trailers for sections .kernel32_hints and .kernel32_iat

unsigned GetTickCount(void)
{
  asm(
    "call dword [__imp__GetTickCount]"
  );
}

#endif // _WINDOWS
