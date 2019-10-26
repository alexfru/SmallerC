/*
  Copyright (c) 2019, Alexey Frunze
  2-clause BSD license.
*/

// Before including this file define DLL and FXN, e.g.:
//
// #define DLL "kernel32"
// #define FXN "ExitProcess"
// #include "../dimports.h"

asm(
" section .dll_import2_" DLL " write align=4\n"
"     dd _hint_" FXN "\n"

" section .dll_import3_" DLL " write align=2\n"
" _hint_" FXN ":\n"
"     db 0, 0, \"" FXN "\", 0\n"
"     align 2, db 0\n"

" section .dll_iat2_" DLL " write align=4\n"
"     global __imp__" FXN "\n"
" __imp__" FXN ":\n"
"     dd _hint_" FXN "\n"

" section .data\n"
"     extern __" DLL "_dll__\n"
"     dd __" DLL "_dll__\n" // pull DLL.c
);
