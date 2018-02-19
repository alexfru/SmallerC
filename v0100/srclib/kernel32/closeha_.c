/*
  Copyright (c) 2018, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm("extern  ___CloseHandle\n"
    "global  _CloseHandle\n"
    "section .text\n"
    "_CloseHandle:\n"
    "jmp     ___CloseHandle");

#endif
