/*
  Copyright (c) 2018, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm("extern  ___ReadFile\n"
    "global  _ReadFile\n"
    "section .text\n"
    "_ReadFile:\n"
    "jmp     ___ReadFile");

#endif
