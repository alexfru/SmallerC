/*
  Copyright (c) 2018, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm("extern  ___SetUnhandledExceptionFilter\n"
    "global  _SetUnhandledExceptionFilter\n"
    "section .text\n"
    "_SetUnhandledExceptionFilter:\n"
    "jmp     ___SetUnhandledExceptionFilter");

#endif
