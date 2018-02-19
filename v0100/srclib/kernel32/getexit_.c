/*
  Copyright (c) 2018, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm("extern  ___GetExitCodeProcess\n"
    "global  _GetExitCodeProcess\n"
    "section .text\n"
    "_GetExitCodeProcess:\n"
    "jmp     ___GetExitCodeProcess");

#endif
