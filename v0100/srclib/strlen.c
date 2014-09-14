/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
unsigned strlen(char* str)
{
#ifdef __SMALLER_C_16__
  asm("mov di, [bp+4]\n"
      "mov cx, -1\n"
      "xor al, al\n"
      "cld\n"
      "repnz scasb\n"
      "mov ax, cx\n"
      "not ax\n"
      "dec ax");
#else
  char* s = str;

  while (*s)
    s++;

  return s - str;
#endif
}
