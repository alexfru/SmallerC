/*
  Copyright (c) 2014-2016, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm(
  "section .kernel32_hints\n"
  "dd _hint_WriteFile"
);

asm(
  "section .kernel32_iat\n"
  "__imp__WriteFile: dd _hint_WriteFile"
);

static char hint_WriteFile[] = "\0\0WriteFile";

extern char _kernel32_dll__[];
static char* pdll = _kernel32_dll__; // pull trailers for sections .kernel32_hints and .kernel32_iat

int WriteFile(unsigned Handle,
              void* Buffer,
              unsigned NumberOfBytesToWrite,
              unsigned* NumberOfBytesWritten,
              void* Overlapped)
{
  asm(
    "push dword [ebp+24]\n"
    "push dword [ebp+20]\n"
    "push dword [ebp+16]\n"
    "push dword [ebp+12]\n"
    "push dword [ebp+8]\n"
    "call dword [__imp__WriteFile]"
  );
}

#endif // _WINDOWS
