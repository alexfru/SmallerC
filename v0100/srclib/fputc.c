/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include "istdio.h"

static int __fputc(int c, FILE* f)
{
  int r;

  if (f->cnt)
  {
    f->cnt--;
    r = *f->ptr++ = c;
  }
  else
  {
    if ((r = __flushbuf(c, f)) == EOF)
    {
      return EOF;
    }
  }

  if ((f->flags & _IONBF) || ((f->flags & _IOLBF) && c == '\n'))
  {
    if (fflush(f))
    {
      return EOF;
    }
  }

  return r;
}

int fputc(int c, FILE* f)
{
#ifndef _LINUX
  if (c == '\n' && !(f->flags & _IOBINARY))
    __fputc('\r', f); // insert '\r'
#endif
  return __fputc(c, f);
}
