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

asm("extern  ___open\n"
    "global  _open");

#ifdef __HUGE_OR_UNREAL__
asm("section .text\n"
    "_open:\n"
    "db      0xEA\n"
    ".1:\n"
    "dd      ___open\n"
    "section .relot\n"
    "dd      _open.1");
#else
asm("section .text\n"
    "_open:\n"
    "jmp     ___open");
#endif
