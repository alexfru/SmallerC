/*
  Copyright (c) 2014-2016, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm(
  "section .kernel32_hints\n"
  "dd _hint_GetStdHandle"
);

asm(
  "section .kernel32_iat\n"
  "__imp__GetStdHandle: dd _hint_GetStdHandle"
);

static char hint_GetStdHandle[] = "\0\0GetStdHandle";

extern char _kernel32_dll__[];
static char* pdll = _kernel32_dll__; // pull trailers for sections .kernel32_hints and .kernel32_iat

unsigned GetStdHandle(unsigned nStdHandle)
{
  asm(
    "push dword [ebp+8]\n"
    "call dword [__imp__GetStdHandle]"
  );
}

#endif // _WINDOWS
