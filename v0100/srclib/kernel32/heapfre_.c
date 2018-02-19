/*
  Copyright (c) 2018, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm("extern  ___HeapFree\n"
    "global  _HeapFree\n"
    "section .text\n"
    "_HeapFree:\n"
    "jmp     ___HeapFree");

#endif
