/*
  Copyright (c) 2014-2016, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm(
  "section .kernel32_hints\n"
  "dd _hint_ReadFile"
);

asm(
  "section .kernel32_iat\n"
  "__imp__ReadFile: dd _hint_ReadFile"
);

static char hint_ReadFile[] = "\0\0ReadFile";

extern char _kernel32_dll__[];
static char* pdll = _kernel32_dll__; // pull trailers for sections .kernel32_hints and .kernel32_iat

int ReadFile(unsigned Handle,
             void* Buffer,
             unsigned NumberOfBytesToRead,
             unsigned* NumberOfBytesRead,
             void* Overlapped)
{
  asm(
    "push dword [ebp+24]\n"
    "push dword [ebp+20]\n"
    "push dword [ebp+16]\n"
    "push dword [ebp+12]\n"
    "push dword [ebp+8]\n"
    "call dword [__imp__ReadFile]"
  );
}

#endif // _WINDOWS
