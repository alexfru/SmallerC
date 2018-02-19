/*
  Copyright (c) 2018, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm("extern  ___CreateFileA\n"
    "global  _CreateFileA\n"
    "section .text\n"
    "_CreateFileA:\n"
    "jmp     ___CreateFileA");

#endif
