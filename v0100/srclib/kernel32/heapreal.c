/*
  Copyright (c) 2014-2016, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm(
  "section .kernel32_hints\n"
  "dd _hint_HeapReAlloc"
);

asm(
  "section .kernel32_iat\n"
  "__imp__HeapReAlloc: dd _hint_HeapReAlloc"
);

static char hint_HeapReAlloc[] = "\0\0HeapReAlloc";

extern char _kernel32_dll__[];
static char* pdll = _kernel32_dll__; // pull trailers for sections .kernel32_hints and .kernel32_iat

void* HeapReAlloc(unsigned hHeap,
                  unsigned dwFlags,
                  void* lpMem,
                  unsigned dwBytes)
{
  asm(
    "push dword [ebp+20]\n"
    "push dword [ebp+16]\n"
    "push dword [ebp+12]\n"
    "push dword [ebp+8]\n"
    "call dword [__imp__HeapReAlloc]"
  );
}

#endif // _WINDOWS
