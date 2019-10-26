/*
  Copyright (c) 2014-2019, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm(
" section .dll_import0_kernel32 write align=4\n"
"     extern __start__dll_import2_kernel32\n"
"     extern __start__dll_iat2_kernel32\n"
"     dd __start__dll_import2_kernel32, 0, 0, __kernel32_dll__, __start__dll_iat2_kernel32\n"

// .dll_import2_kernel32 section follows.

" section .dll_import2_kernel32_trailer write align=4\n"
"     dd 0\n"

// .dll_import3_kernel32 section follows.

" section .dll_import4_kernel32 write align=1\n"
"     global __kernel32_dll__\n"
" __kernel32_dll__:\n" // win32 functions will pull this file by this symbol
"     db \"kernel32.dll\", 0\n"

// .dll_iat2_kernel32 section follows.

" section .dll_iat2_kernel32_trailer write align=4\n"
"     dd 0\n"

" section .data\n"
"     extern __dll_imports\n"
"     dd __dll_imports\n" // pull ../dimports.c
);

#endif // _WINDOWS
