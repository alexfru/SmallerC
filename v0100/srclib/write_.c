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

asm("extern  ___write\n"
    "global  _write");

#ifdef __HUGE_OR_UNREAL__
asm("section .text\n"
    "_write:\n"
    "db      0xEA\n"
    ".1:\n"
    "dd      ___write\n"
    "section .relot\n"
    "dd      _write.1");
#else
asm("section .text\n"
    "_write:\n"
    "jmp     ___write");
#endif
