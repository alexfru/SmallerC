/*
  Copyright (c) 2018, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm("extern  ___WaitForSingleObject\n"
    "global  _WaitForSingleObject\n"
    "section .text\n"
    "_WaitForSingleObject:\n"
    "jmp     ___WaitForSingleObject");

#endif
