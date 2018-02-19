/*
  Copyright (c) 2018, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm("extern  ___GetStdHandle\n"
    "global  _GetStdHandle\n"
    "section .text\n"
    "_GetStdHandle:\n"
    "jmp     ___GetStdHandle");

#endif
