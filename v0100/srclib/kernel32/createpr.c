/*
  Copyright (c) 2014-2016, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm(
  "section .kernel32_hints\n"
  "dd _hint_CreateProcessA"
);

asm(
  "section .kernel32_iat\n"
  "__imp__CreateProcessA: dd _hint_CreateProcessA"
);

static char hint_CreateProcessA[] = "\0\0CreateProcessA";

extern char _kernel32_dll__[];
static char* pdll = _kernel32_dll__; // pull trailers for sections .kernel32_hints and .kernel32_iat

struct _SECURITY_ATTRIBUTES;
struct _STARTUPINFO;
struct _PROCESS_INFORMATION;

int CreateProcessA(char* lpApplicationName,
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
