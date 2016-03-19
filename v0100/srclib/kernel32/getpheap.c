/*
  Copyright (c) 2014-2016, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm(
  "section .kernel32_hints\n"
  "dd _hint_GetProcessHeap"
);

asm(
  "section .kernel32_iat\n"
  "__imp__GetProcessHeap: dd _hint_GetProcessHeap"
);

static char hint_GetProcessHeap[] = "\0\0GetProcessHeap";

extern char _kernel32_dll__[];
static char* pdll = _kernel32_dll__; // pull trailers for sections .kernel32_hints and .kernel32_iat

unsigned GetProcessHeap(void)
{
  asm(
    "call dword [__imp__GetProcessHeap]"
  );
}

#endif // _WINDOWS
