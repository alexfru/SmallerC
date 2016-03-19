/*
  Copyright (c) 2014-2016, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm(
  "section .kernel32_hints\n"
  "dd _hint_GetEnvironmentVariableA"
);

asm(
  "section .kernel32_iat\n"
  "__imp__GetEnvironmentVariableA: dd _hint_GetEnvironmentVariableA"
);

static char hint_GetEnvironmentVariableA[] = "\0\0GetEnvironmentVariableA";

extern char _kernel32_dll__[];
static char* pdll = _kernel32_dll__; // pull trailers for sections .kernel32_hints and .kernel32_iat

unsigned GetEnvironmentVariableA(char* lpName,
                                 char* lpBuffer,
                                 unsigned nSize)
{
  asm(
    "push dword [ebp+16]\n"
    "push dword [ebp+12]\n"
    "push dword [ebp+8]\n"
    "call dword [__imp__GetEnvironmentVariableA]"
  );
}

#endif // _WINDOWS
