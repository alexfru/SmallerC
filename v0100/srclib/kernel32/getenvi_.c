/*
  Copyright (c) 2018, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm("extern  ___GetEnvironmentVariableA\n"
    "global  _GetEnvironmentVariableA\n"
    "section .text\n"
    "_GetEnvironmentVariableA:\n"
    "jmp     ___GetEnvironmentVariableA");

#endif
