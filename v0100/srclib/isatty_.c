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

asm("extern  ___isatty\n"
    "global  _isatty");

#ifdef __HUGE_OR_UNREAL__
asm("section .text\n"
    "_isatty:\n"
    "db      0xEA\n"
    ".1:\n"
    "dd      ___isatty\n"
    "section .relot\n"
    "dd      _isatty.1");
#else
asm("section .text\n"
    "_isatty:\n"
    "jmp     ___isatty");
#endif
