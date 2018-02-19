/*
  Copyright (c) 2018, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm("extern  ___GetCommandLineA\n"
    "global  _GetCommandLineA\n"
    "section .text\n"
    "_GetCommandLineA:\n"
    "jmp     ___GetCommandLineA");

#endif
