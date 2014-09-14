/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
int strncmp(char* s1, char* s2, unsigned n)
{
#ifdef __SMALLER_C_16__
  asm("mov cx, [bp+8]\n"
      "xor ax, ax\n"
      "jcxz strncmpend\n"
      "mov bx, ax\n"
      "mov di, [bp+6]\n"
      "mov si, di\n"
      "cld\n"
      "repnz scasb\n"
      "sub cx, [bp+8]\n"
      "neg cx");
  asm("mov di, [bp+4]\n"
      "repe cmpsb\n"
      "mov al, [di-1]\n"
      "mov bl, [si-1]\n"
      "sub ax, bx\n"
      "strncmpend:");
#else
  if (!n)
    return 0;

  do
  {
    if (*s1 != *s2++)
      return ((unsigned char)*s1) - ((unsigned char)*--s2);
    if (!*s1++)
      break;
  } while (--n);

  return 0;
#endif
}
