/*
  Copyright (c) 2018, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm("extern  ___LoadLibraryExA\n"
    "global  _LoadLibraryExA\n"
    "section .text\n"
    "_LoadLibraryExA:\n"
    "jmp     ___LoadLibraryExA");

#endif
