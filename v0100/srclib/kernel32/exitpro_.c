/*
  Copyright (c) 2018, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm("extern  ___ExitProcess\n"
    "global  _ExitProcess\n"
    "section .text\n"
    "_ExitProcess:\n"
    "jmp     ___ExitProcess");

#endif
