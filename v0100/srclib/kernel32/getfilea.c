/*
  Copyright (c) 2014-2016, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm(
  "section .kernel32_hints\n"
  "dd _hint_GetFileAttributesA"
);

asm(
  "section .kernel32_iat\n"
  "__imp__GetFileAttributesA: dd _hint_GetFileAttributesA"
);

static char hint_GetFileAttributesA[] = "\0\0GetFileAttributesA";

extern char _kernel32_dll__[];
static char* pdll = _kernel32_dll__; // pull trailers for sections .kernel32_hints and .kernel32_iat

unsigned GetFileAttributesA(char* lpFileName)
{
  asm(
    "push dword [ebp+8]\n"
    "call dword [__imp__GetFileAttributesA]"
  );
}

#endif // _WINDOWS
