/*
  Copyright (c) 2018, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm("extern  ___SetFilePointer\n"
    "global  _SetFilePointer\n"
    "section .text\n"
    "_SetFilePointer:\n"
    "jmp     ___SetFilePointer");

#endif
