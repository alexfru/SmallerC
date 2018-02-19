/*
  Copyright (c) 2018, Alexey Frunze
  2-clause BSD license.
*/
#ifdef __HUGE__
#define __HUGE_OR_UNREAL__
#endif
#ifdef __UNREAL__
#define __HUGE_OR_UNREAL__
#endif

asm("extern  ___close\n"
    "global  _close");

#ifdef __HUGE_OR_UNREAL__
asm("section .text\n"
    "_close:\n"
    "db      0xEA\n"
    ".1:\n"
    "dd      ___close\n"
    "section .relot\n"
    "dd      _close.1");
#else
asm("section .text\n"
    "_close:\n"
    "jmp     ___close");
#endif
