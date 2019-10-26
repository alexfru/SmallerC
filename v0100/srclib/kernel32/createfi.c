/*
  Copyright (c) 2014-2019, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

#define DLL "kernel32"
#define FXN "CreateFileA"
#include "../dimports.h"

unsigned __CreateFileA(char* FileName,
                       unsigned DesiredAccess,
                       unsigned ShareMode,
                       void* SecurityAttributes,
                       unsigned CreationDisposition,
                       unsigned FlagsAndAttributes,
                       unsigned TemplateFile)
{
  asm(
    "push dword [ebp+32]\n"
    "push dword [ebp+28]\n"
    "push dword [ebp+24]\n"
    "push dword [ebp+20]\n"
    "push dword [ebp+16]\n"
    "push dword [ebp+12]\n"
    "push dword [ebp+8]\n"
    "call dword [__imp__CreateFileA]"
  );
}

#endif // _WINDOWS
