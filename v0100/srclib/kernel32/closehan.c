/*
  Copyright (c) 2014-2016, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm(
  "section .kernel32_hints\n"
  "dd _hint_CloseHandle"
);

asm(
  "section .kernel32_iat\n"
  "__imp__CloseHandle: dd _hint_CloseHandle"
);

static char hint_CloseHandle[] = "\0\0CloseHandle";

extern char _kernel32_dll__[];
static char* pdll = _kernel32_dll__; // pull trailers for sections .kernel32_hints and .kernel32_iat

int CloseHandle(unsigned Handle)
{
  asm(
    "push dword [ebp+8]\n"
    "call dword [__imp__CloseHandle]"
  );
}

#endif // _WINDOWS
