/*
  Copyright (c) 2018, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm("extern  ___SystemTimeToTzSpecificLocalTime\n"
    "global  _SystemTimeToTzSpecificLocalTime\n"
    "section .text\n"
    "_SystemTimeToTzSpecificLocalTime:\n"
    "jmp     ___SystemTimeToTzSpecificLocalTime");

#endif
