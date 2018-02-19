/*
  Copyright (c) 2018, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm("extern  ___HeapReAlloc\n"
    "global  _HeapReAlloc\n"
    "section .text\n"
    "_HeapReAlloc:\n"
    "jmp     ___HeapReAlloc");

#endif
