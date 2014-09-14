/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
int strcmp(char* s1, char* s2)
{
#ifdef __SMALLER_C_16__
  asm("mov di, [bp+6]\n"
      "mov si, di\n"
      "mov cx, -1\n"
      "xor ax, ax\n"
      "mov bx, ax\n"
      "cld\n"
      "repnz scasb\n"
      "not cx");
  asm("mov di, [bp+4]\n"
      "repe cmpsb\n"
      "mov al, [di-1]\n"
      "mov bl, [si-1]\n"
      "sub ax, bx");
#else
  while (*s1 == *s2)
  {
    if (!*s1)
      return 0;
    ++s1;
    ++s2;
  }

  return ((unsigned char)*s1) - ((unsigned char)*s2);
#endif
}
