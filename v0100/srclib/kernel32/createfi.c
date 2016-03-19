/*
  Copyright (c) 2014-2016, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm(
  "section .kernel32_hints\n"
  "dd _hint_CreateFileA"
);

asm(
  "section .kernel32_iat\n"
  "__imp__CreateFileA: dd _hint_CreateFileA"
);

static char hint_CreateFileA[] = "\0\0CreateFileA";

extern char _kernel32_dll__[];
static char* pdll = _kernel32_dll__; // pull trailers for sections .kernel32_hints and .kernel32_iat

unsigned CreateFileA(char* FileName,
                     unsigned DesiredAccess,
                     unsigned ShareMode,
                     void* SecurityAttributes,
                     unsigned CreationDisposition,
                     unsigned FlagsAndAttributes,
                     unsigned TemplateFile)
{
  asm(
    "push dword [ebp+32]\n"
    "push dword [ebp+28]\n"
    "push dword [ebp+24]\n"
    "push dword [ebp+20]\n"
    "push dword [ebp+16]\n"
    "push dword [ebp+12]\n"
    "push dword [ebp+8]\n"
    "call dword [__imp__CreateFileA]"
  );
}

#endif // _WINDOWS
