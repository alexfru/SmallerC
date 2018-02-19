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

asm("extern  ___unlink\n"
    "global  _unlink");

#ifdef __HUGE_OR_UNREAL__
asm("section .text\n"
    "_unlink:\n"
    "db      0xEA\n"
    ".1:\n"
    "dd      ___unlink\n"
    "section .relot\n"
    "dd      _unlink.1");
#else
asm("section .text\n"
    "_unlink:\n"
    "jmp     ___unlink");
#endif
