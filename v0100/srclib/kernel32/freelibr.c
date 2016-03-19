/*
  Copyright (c) 2014-2016, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm(
  "section .kernel32_hints\n"
  "dd _hint_FreeLibrary"
);

asm(
  "section .kernel32_iat\n"
  "__imp__FreeLibrary: dd _hint_FreeLibrary"
);

static char hint_FreeLibrary[] = "\0\0FreeLibrary";

extern char _kernel32_dll__[];
static char* pdll = _kernel32_dll__; // pull trailers for sections .kernel32_hints and .kernel32_iat

int FreeLibrary(void* hModule)
{
  asm(
    "push dword [ebp+8]\n"
    "call dword [__imp__FreeLibrary]"
  );
}

#endif // _WINDOWS
