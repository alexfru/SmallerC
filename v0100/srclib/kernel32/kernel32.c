/*
  Copyright (c) 2014-2016, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm(
  "section .kernel32_hints_trailer\n"
  "dd 0" // make sure the section isn't empty
);

asm(
  "section .kernel32_iat_trailer\n"
  "dd 0" // make sure the section isn't empty
);

asm(
  "section .dll_imports\n"
  "extern __start__kernel32_hints\n"
  "extern __start__kernel32_iat\n"
  "dd __start__kernel32_hints, 0, 0, __kernel32_dll__, __start__kernel32_iat"
);

char _kernel32_dll__[] = "kernel32.dll"; // win32 functions will pull this file by this symbol
extern char _dll_imports;
static char* pimports = &_dll_imports; // pull the header & trailer for the dll imports table (section .dll_imports)

#endif // _WINDOWS
