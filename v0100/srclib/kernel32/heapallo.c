/*
  Copyright (c) 2014-2016, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm(
  "section .kernel32_hints\n"
  "dd _hint_HeapAlloc"
);

asm(
  "section .kernel32_iat\n"
  "__imp__HeapAlloc: dd _hint_HeapAlloc"
);

static char hint_HeapAlloc[] = "\0\0HeapAlloc";

extern char _kernel32_dll__[];
static char* pdll = _kernel32_dll__; // pull trailers for sections .kernel32_hints and .kernel32_iat

void* HeapAlloc(unsigned hHeap,
                unsigned dwFlags,
                unsigned dwBytes)
{
  asm(
    "push dword [ebp+16]\n"
    "push dword [ebp+12]\n"
    "push dword [ebp+8]\n"
    "call dword [__imp__HeapAlloc]"
  );
}

#endif // _WINDOWS
