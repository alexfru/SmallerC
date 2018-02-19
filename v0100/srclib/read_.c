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

asm("extern  ___read\n"
    "global  _read");

#ifdef __HUGE_OR_UNREAL__
asm("section .text\n"
    "_read:\n"
    "db      0xEA\n"
    ".1:\n"
    "dd      ___read\n"
    "section .relot\n"
    "dd      _read.1");
#else
asm("section .text\n"
    "_read:\n"
    "jmp     ___read");
#endif
