/*
  Copyright (c) 2018, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm("extern  ___WriteFile\n"
    "global  _WriteFile\n"
    "section .text\n"
    "_WriteFile:\n"
    "jmp     ___WriteFile");

#endif
