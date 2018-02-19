/*
  Copyright (c) 2018, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm("extern  ___GetTickCount\n"
    "global  _GetTickCount\n"
    "section .text\n"
    "_GetTickCount:\n"
    "jmp     ___GetTickCount");

#endif
