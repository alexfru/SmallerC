/*
  Copyright (c) 2014-2019, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

#define DLL "kernel32"
#define FXN "CreateProcessA"
#include "../dimports.h"

struct _SECURITY_ATTRIBUTES;
struct _STARTUPINFO;
struct _PROCESS_INFORMATION;

int __CreateProcessA(char* lpApplicationName,
                     char* lpCommandLine,
                     struct _SECURITY_ATTRIBUTES* lpProcessAttributes,
                     struct _SECURITY_ATTRIBUTES* lpThreadAttributes,
                     int bInheritHandles,
                     unsigned dwCreationFlags,
                     void* lpEnvironment,
                     char* lpCurrentDirectory,
                     struct _STARTUPINFO* lpStartupInfo,
                     struct _PROCESS_INFORMATION* lpProcessInformation)
{
  asm(
    "push dword [ebp+44]\n"
    "push dword [ebp+40]\n"
    "push dword [ebp+36]\n"
    "push dword [ebp+32]\n"
    "push dword [ebp+28]\n"
    "push dword [ebp+24]\n"
    "push dword [ebp+20]\n"
    "push dword [ebp+16]\n"
    "push dword [ebp+12]\n"
    "push dword [ebp+8]\n"
    "call dword [__imp__CreateProcessA]"
  );
}

#endif // _WINDOWS
