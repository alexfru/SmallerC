/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
void* memset(void* s, int c, unsigned n)
{
#ifdef __SMALLER_C_16__
  asm("mov di, [bp+4]\n"
      "mov al, [bp+6]\n"
      "mov ah, al\n"
      "mov cx, [bp+8]\n"
      "shr cx, 1\n"
      "cld\n"
      "rep stosw\n"
      "rcl cx, 1\n"
      "rep stosb");
#else
  char* p = s;

  while (n--)
    *p++ = c;
#endif
  return s;
}
