/*
  Copyright (c) 2014-2016, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm(
  "section .kernel32_hints\n"
  "dd _hint_HeapFree"
);

asm(
  "section .kernel32_iat\n"
  "__imp__HeapFree: dd _hint_HeapFree"
);

static char hint_HeapFree[] = "\0\0HeapFree";

extern char _kernel32_dll__[];
static char* pdll = _kernel32_dll__; // pull trailers for sections .kernel32_hints and .kernel32_iat

int HeapFree(unsigned hHeap,
             unsigned dwFlags,
             void* lpMem)
{
  asm(
    "push dword [ebp+16]\n"
    "push dword [ebp+12]\n"
    "push dword [ebp+8]\n"
    "call dword [__imp__HeapFree]"
  );
}

#endif // _WINDOWS
