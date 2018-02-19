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

asm("extern  ___lseek\n"
    "global  _lseek");

#ifdef __HUGE_OR_UNREAL__
asm("section .text\n"
    "_lseek:\n"
    "db      0xEA\n"
    ".1:\n"
    "dd      ___lseek\n"
    "section .relot\n"
    "dd      _lseek.1");
#else
asm("section .text\n"
    "_lseek:\n"
    "jmp     ___lseek");
#endif
