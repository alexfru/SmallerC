/*
  Copyright (c) 2014-2016, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm(
  "section .kernel32_hints\n"
  "dd _hint_SetLastError"
);

asm(
  "section .kernel32_iat\n"
  "__imp__SetLastError: dd _hint_SetLastError"
);

static char hint_SetLastError[] = "\0\0SetLastError";

extern char _kernel32_dll__[];
static char* pdll = _kernel32_dll__; // pull trailers for sections .kernel32_hints and .kernel32_iat

void SetLastError(unsigned Error)
{
  asm(
    "push dword [ebp+8]\n"
    "call dword [__imp__SetLastError]"
  );
}

#endif // _WINDOWS
