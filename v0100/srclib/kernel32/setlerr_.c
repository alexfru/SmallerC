/*
  Copyright (c) 2018, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm("extern  ___SetLastError\n"
    "global  _SetLastError\n"
    "section .text\n"
    "_SetLastError:\n"
    "jmp     ___SetLastError");

#endif
