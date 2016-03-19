/*
  Copyright (c) 2014-2016, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm(
  "section .kernel32_hints\n"
  "dd _hint_GetProcAddress"
);

asm(
  "section .kernel32_iat\n"
  "__imp__GetProcAddress: dd _hint_GetProcAddress"
);

static char hint_GetProcAddress[] = "\0\0GetProcAddress";

extern char _kernel32_dll__[];
static char* pdll = _kernel32_dll__; // pull trailers for sections .kernel32_hints and .kernel32_iat

void (*GetProcAddress(void* hModule, char* lpProcName))()
{
  asm(
    "push dword [ebp+12]\n"
    "push dword [ebp+8]\n"
    "call dword [__imp__GetProcAddress]"
  );
}

#endif // _WINDOWS
