/*
  Copyright (c) 2018, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm("extern  ___TzSpecificLocalTimeToSystemTime\n"
    "global  _TzSpecificLocalTimeToSystemTime\n"
    "section .text\n"
    "_TzSpecificLocalTimeToSystemTime:\n"
    "jmp     ___TzSpecificLocalTimeToSystemTime");

#endif
