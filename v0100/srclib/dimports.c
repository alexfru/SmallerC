/*
  Copyright (c) 2014-2019, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm(
" section .dll_import write align=4\n"
"     dd 0\n"
"     global __dll_imports\n"
" __dll_imports:\n"

// .dll_import0_<dll> sections follow.

" section .dll_import1 write align=4\n"
"     dd 0, 0, 0, 0, 0\n"

// Pairs of sections follow:
//   .dll_import2_<dll>
//   .dll_import2_<dll>_trailer

// .dll_import3_<dll> sections follow.
// .dll_import4_<dll> sections follow.

" section .dll_imports_end write align=4\n"
"     global __dll_imports_end\n"
" __dll_imports_end:\n"
"     dd 0\n"

" section .dll_iat write align=4\n"
"     dd 0\n"
"     global __dll_iats\n"
" __dll_iats:\n"

// Pairs of sections follow:
//   .dll_iat2_<dll>
//   .dll_iat2_<dll>_trailer

" section .dll_iats_end write align=4\n"
"     global __dll_iats_end\n"
" __dll_iats_end:\n"
"     dd 0\n"
);

#endif // _WINDOWS
