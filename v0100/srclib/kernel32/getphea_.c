/*
  Copyright (c) 2018, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm("extern  ___GetProcessHeap\n"
    "global  _GetProcessHeap\n"
    "section .text\n"
    "_GetProcessHeap:\n"
    "jmp     ___GetProcessHeap");

#endif
