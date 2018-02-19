/*
  Copyright (c) 2018, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm("extern  ___HeapAlloc\n"
    "global  _HeapAlloc\n"
    "section .text\n"
    "_HeapAlloc:\n"
    "jmp     ___HeapAlloc");

#endif
