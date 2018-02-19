/*
  Copyright (c) 2018, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm("extern  ___CreateProcessA\n"
    "global  _CreateProcessA\n"
    "section .text\n"
    "_CreateProcessA:\n"
    "jmp     ___CreateProcessA");

#endif
