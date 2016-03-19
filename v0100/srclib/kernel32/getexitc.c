/*
  Copyright (c) 2014-2016, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm(
  "section .kernel32_hints\n"
  "dd _hint_GetExitCodeProcess"
);

asm(
  "section .kernel32_iat\n"
  "__imp__GetExitCodeProcess: dd _hint_GetExitCodeProcess"
);

static char hint_GetExitCodeProcess[] = "\0\0GetExitCodeProcess";

extern char _kernel32_dll__[];
static char* pdll = _kernel32_dll__; // pull trailers for sections .kernel32_hints and .kernel32_iat

int GetExitCodeProcess(unsigned hProcess, unsigned* lpExitCode)
{
  asm(
    "push dword [ebp+12]\n"
    "push dword [ebp+8]\n"
    "call dword [__imp__GetExitCodeProcess]"
  );
}

#endif // _WINDOWS
