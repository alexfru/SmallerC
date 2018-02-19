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

asm("extern  ___fileno\n"
    "global  _fileno");

#ifdef __HUGE_OR_UNREAL__
asm("section .text\n"
    "_fileno:\n"
    "db      0xEA\n"
    ".1:\n"
    "dd      ___fileno\n"
    "section .relot\n"
    "dd      _fileno.1");
#else
asm("section .text\n"
    "_fileno:\n"
    "jmp     ___fileno");
#endif
