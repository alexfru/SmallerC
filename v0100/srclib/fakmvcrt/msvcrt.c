/*
  Copyright (c) 2021, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm(
" section .dll_import0_msvcrt write align=4\n"
"     extern __start__dll_import2_msvcrt\n"
"     extern __start__dll_iat2_msvcrt\n"
"     dd __start__dll_import2_msvcrt, 0, 0, __msvcrt_dll__, __start__dll_iat2_msvcrt\n"

// .dll_import2_msvcrt section follows.

" section .dll_import2_msvcrt_trailer write align=4\n"
"     dd 0\n"

// .dll_import3_msvcrt section follows.

" section .dll_import4_msvcrt write align=1\n"
"     global __msvcrt_dll__\n"
" __msvcrt_dll__:\n" // win32 functions will pull this file by this symbol
"     db \"msvcrt.dll\", 0\n"

// .dll_iat2_msvcrt section follows.

" section .dll_iat2_msvcrt_trailer write align=4\n"
"     dd 0\n"

" section .data\n"
"     extern __dll_imports\n"
"     dd __dll_imports\n" // pull ../dimports.c
);

#endif // _WINDOWS
