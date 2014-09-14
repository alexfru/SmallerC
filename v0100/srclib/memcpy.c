/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
void* memcpy(void* dst, void* src, unsigned n)
{
#ifdef __SMALLER_C_16__
  asm("mov di, [bp+4]\n"
      "mov si, [bp+6]\n"
      "mov cx, [bp+8]\n"
      "shr cx, 1\n"
      "cld\n"
      "rep movsw\n"
      "rcl cx, 1\n"
      "rep movsb");
#else
  char* p1 = dst;
  char* p2 = src;

  while (n--)
    *p1++ = *p2++;
#endif
  return dst;
}
