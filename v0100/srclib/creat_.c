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

asm("extern  ___creat\n"
    "global  _creat");

#ifdef __HUGE_OR_UNREAL__
asm("section .text\n"
    "_creat:\n"
    "db      0xEA\n"
    ".1:\n"
    "dd      ___creat\n"
    "section .relot\n"
    "dd      _creat.1");
#else
asm("section .text\n"
    "_creat:\n"
    "jmp     ___creat");
#endif
