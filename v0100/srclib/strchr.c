/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
char* strchr(char* s, int c)
{
#ifdef __SMALLER_C_16__
  asm("mov si, [bp+4]\n"
      "mov bl, [bp+6]\n"
      "xor ax, ax\n"
      "cld\n"
      "strchrlp:\n"
      "lodsb\n"
      "cmp al, bl\n"
      "je strchrmch\n"
      "or al, al\n"
      "jnz strchrlp\n"
      "jmp strchrend");
  asm("strchrmch:\n"
      "lea ax, [si-1]\n"
      "strchrend:");
#else
  c = (char)c;

  while (*s)
  {
    if (*s == c)
      return s;
    ++s;
  }

  if (!c)
    return s;

  return 0;
#endif
}
