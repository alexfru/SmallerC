/*
  Copyright (c) 2014-2016, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm(
  "section .kernel32_hints\n"
  "dd _hint_ExitProcess"
);

asm(
  "section .kernel32_iat\n"
  "__imp__ExitProcess: dd _hint_ExitProcess"
);

static char hint_ExitProcess[] = "\0\0ExitProcess";

extern char _kernel32_dll__[];
static char* pdll = _kernel32_dll__; // pull trailers for sections .kernel32_hints and .kernel32_iat

void ExitProcess(unsigned ExitCode)
{
  asm(
    "push dword [ebp+8]\n"
    "call dword [__imp__ExitProcess]"
  );
}

#endif // _WINDOWS
