/*
  Copyright (c) 2018, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm("extern  ___DeleteFileA\n"
    "global  _DeleteFileA\n"
    "section .text\n"
    "_DeleteFileA:\n"
    "jmp     ___DeleteFileA");

#endif
