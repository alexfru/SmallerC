/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
char* strcpy(char* dst, char* src)
{
#ifdef __SMALLER_C_16__
  asm("mov di, [bp+6]\n"
      "mov si, di\n"
      "mov cx, -1\n"
      "xor al, al\n"
      "cld\n"
      "repnz scasb\n"
      "not cx\n"
      "mov di, [bp+4]\n"
      "rep movsb");
#else
  char* p = dst;

  while ((*p++ = *src++) != 0);
#endif

  return dst;
}
