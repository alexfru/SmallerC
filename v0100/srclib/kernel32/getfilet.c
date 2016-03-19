/*
  Copyright (c) 2014-2016, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm(
  "section .kernel32_hints\n"
  "dd _hint_GetFileType"
);

asm(
  "section .kernel32_iat\n"
  "__imp__GetFileType: dd _hint_GetFileType"
);

static char hint_GetFileType[] = "\0\0GetFileType";

extern char _kernel32_dll__[];
static char* pdll = _kernel32_dll__; // pull trailers for sections .kernel32_hints and .kernel32_iat

unsigned GetFileType(unsigned Handle)
{
  asm(
    "push dword [ebp+8]\n"
    "call dword [__imp__GetFileType]"
  );
}

#endif // _WINDOWS
