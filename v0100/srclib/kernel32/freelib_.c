/*
  Copyright (c) 2018, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm("extern  ___FreeLibrary\n"
    "global  _FreeLibrary\n"
    "section .text\n"
    "_FreeLibrary:\n"
    "jmp     ___FreeLibrary");

#endif
