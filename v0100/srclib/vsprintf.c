/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include "istdio.h"

int vsprintf(char* s, char* fmt, va_list vl)
{
  int res;
  FILE f;
  f.flags = _IOWR | _IOSTRING | _IOBINARY; // don't do file I/O, don't translate "\n" to "\r\n"
  f.ptr = f.buf = s;
  f.cnt = f.bufsz = (unsigned)-1 / 2 - 1;
  res = __doprint(&f, fmt, vl);
  *f.ptr = '\0';
  return res;
}
