/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include "istdio.h"

static int __fgetc(FILE* f)
{
  if (f->cnt)
  {
    f->cnt--;
    return *f->ptr++;
  }
  return __fillbuf(f);
}

int fgetc(FILE* f)
{
#if !defined(_LINUX) && !defined(_MACOS)
  int c = __fgetc(f);
  if (f->flags & _IOBINARY)
    return c;
  for (;;)
  {
    if (c != '\r') // drop '\r'
      return c;
    c = __fgetc(f);
  }
#else
  return __fgetc(f);
#endif
}
