/*
  Copyright (c) 2018, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm("extern  ___MoveFileA\n"
    "global  _MoveFileA\n"
    "section .text\n"
    "_MoveFileA:\n"
    "jmp     ___MoveFileA");

#endif
