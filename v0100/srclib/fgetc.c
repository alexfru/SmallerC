/*
  Copyright (c) 2014-2017, Alexey Frunze
  2-clause BSD license.
*/
#include "istdio.h"

#ifdef _LINUX
#define UNIX_LIKE
#endif
#ifdef _MACOS
#define UNIX_LIKE
#endif

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
#ifndef UNIX_LIKE
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
