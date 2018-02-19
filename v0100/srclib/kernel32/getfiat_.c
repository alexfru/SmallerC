/*
  Copyright (c) 2018, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm("extern  ___GetFileAttributesA\n"
    "global  _GetFileAttributesA\n"
    "section .text\n"
    "_GetFileAttributesA:\n"
    "jmp     ___GetFileAttributesA");

#endif
