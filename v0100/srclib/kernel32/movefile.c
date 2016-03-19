/*
  Copyright (c) 2014-2016, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm(
  "section .kernel32_hints\n"
  "dd _hint_MoveFileA"
);

asm(
  "section .kernel32_iat\n"
  "__imp__MoveFileA: dd _hint_MoveFileA"
);

static char hint_MoveFileA[] = "\0\0MoveFileA";

extern char _kernel32_dll__[];
static char* pdll = _kernel32_dll__; // pull trailers for sections .kernel32_hints and .kernel32_iat

int MoveFileA(char* lpExistingFileName, char* lpNewFileName)
{
  asm(
    "push dword [ebp+12]\n"
    "push dword [ebp+8]\n"
    "call dword [__imp__MoveFileA]"
  );
}

#endif // _WINDOWS
