/*
  Copyright (c) 2018, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm("extern  ___GetProcAddress\n"
    "global  _GetProcAddress\n"
    "section .text\n"
    "_GetProcAddress:\n"
    "jmp     ___GetProcAddress");

#endif
