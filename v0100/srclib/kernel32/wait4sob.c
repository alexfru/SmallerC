/*
  Copyright (c) 2014-2016, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm(
  "section .kernel32_hints\n"
  "dd _hint_WaitForSingleObject"
);

asm(
  "section .kernel32_iat\n"
  "__imp__WaitForSingleObject: dd _hint_WaitForSingleObject"
);

static char hint_WaitForSingleObject[] = "\0\0WaitForSingleObject";

extern char _kernel32_dll__[];
static char* pdll = _kernel32_dll__; // pull trailers for sections .kernel32_hints and .kernel32_iat

unsigned WaitForSingleObject(unsigned hHandle, unsigned dwMilliseconds)
{
  asm(
    "push dword [ebp+12]\n"
    "push dword [ebp+8]\n"
    "call dword [__imp__WaitForSingleObject]"
  );
}

#endif // _WINDOWS
