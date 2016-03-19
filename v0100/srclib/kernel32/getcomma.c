/*
  Copyright (c) 2014-2016, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm(
  "section .kernel32_hints\n"
  "dd _hint_GetCommandLineA"
);

asm(
  "section .kernel32_iat\n"
  "__imp__GetCommandLineA: dd _hint_GetCommandLineA"
);

static char hint_GetCommandLineA[] = "\0\0GetCommandLineA";

extern char _kernel32_dll__[];
static char* pdll = _kernel32_dll__; // pull trailers for sections .kernel32_hints and .kernel32_iat

char* GetCommandLineA(void)
{
  asm(
    "call dword [__imp__GetCommandLineA]"
  );
}

#endif // _WINDOWS
