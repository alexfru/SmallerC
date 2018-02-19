/*
  Copyright (c) 2018, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm("extern  ___GetFileType\n"
    "global  _GetFileType\n"
    "section .text\n"
    "_GetFileType:\n"
    "jmp     ___GetFileType");

#endif
