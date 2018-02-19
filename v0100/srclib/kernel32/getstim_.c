/*
  Copyright (c) 2018, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm("extern  ___GetSystemTime\n"
    "global  _GetSystemTime\n"
    "section .text\n"
    "_GetSystemTime:\n"
    "jmp     ___GetSystemTime");

#endif
