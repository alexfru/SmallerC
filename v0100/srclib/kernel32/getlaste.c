/*
  Copyright (c) 2014-2016, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm(
  "section .kernel32_hints\n"
  "dd _hint_GetLastError"
);

asm(
  "section .kernel32_iat\n"
  "__imp__GetLastError: dd _hint_GetLastError"
);

static char hint_GetLastError[] = "\0\0GetLastError";

extern char _kernel32_dll__[];
static char* pdll = _kernel32_dll__; // pull trailers for sections .kernel32_hints and .kernel32_iat

unsigned GetLastError(void)
{
  asm(
    "call dword [__imp__GetLastError]"
  );
}

#endif // _WINDOWS
