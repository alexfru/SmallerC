/*
  Copyright (c) 2014-2016, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm(
  "section .kernel32_hints\n"
  "dd _hint_DeleteFileA"
);

asm(
  "section .kernel32_iat\n"
  "__imp__DeleteFileA: dd _hint_DeleteFileA"
);

static char hint_DeleteFileA[] = "\0\0DeleteFileA";

extern char _kernel32_dll__[];
static char* pdll = _kernel32_dll__; // pull trailers for sections .kernel32_hints and .kernel32_iat

int DeleteFileA(char*)
{
  asm(
    "push dword [ebp+8]\n"
    "call dword [__imp__DeleteFileA]"
  );
}

#endif // _WINDOWS
