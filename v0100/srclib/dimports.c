/*
  Copyright (c) 2014-2016, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm(
  "section .dll_import\n"
  "align 4\n"
  "dd 0\n" // make sure the section isn't empty
  "global __dll_imports\n"
  "__dll_imports:"
);

// The dll imports table (section .dll_imports) will reside between
// sections .dll_import and .dll_imports_trailer due to alphabetic
// ordering of sections by the linker

asm(
  "section .dll_imports_trailer\n"
  "dd 0, 0, 0, 0, 0"
);

#endif // _WINDOWS
