/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
void* memmove(void* dst, void* src, unsigned n)
{
#ifdef __SMALLER_C_16__
  if (src < dst)
  {
    asm("mov di, [bp+4]\n"
        "mov si, [bp+6]\n"
        "mov cx, [bp+8]\n"
        "add di, cx\n"
        "dec di\n"
        "add si, cx\n"
        "dec si\n"
        "std\n"
        "rep movsb");
  }
  else
  {
    asm("mov di, [bp+4]\n"
        "mov si, [bp+6]\n"
        "mov cx, [bp+8]\n"
        "cld\n"
        "rep movsb");
  }
#else
  char* d = dst;
  char* s = src;

  if (s < d)
  {
    s += n;
    d += n;
    while (n--)
      *--d = *--s;
  }
  else
  {
    while (n--)
      *d++ = *s++;
  }
#endif
  return dst;
}
