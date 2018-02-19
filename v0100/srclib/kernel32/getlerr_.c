/*
  Copyright (c) 2018, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm("extern  ___GetLastError\n"
    "global  _GetLastError\n"
    "section .text\n"
    "_GetLastError:\n"
    "jmp     ___GetLastError");

#endif
