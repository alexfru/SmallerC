/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include "istdio.h"

int snprintf(char* s, size_t n, char* fmt, ...)
{
  int res;
  FILE f;
  // TBD??? overflow check for n > INT_MAX???
  f.flags = _IOWR | _IOSTRING | _IOBINARY; // don't do file I/O, don't translate "\n" to "\r\n"
  f.ptr = f.buf = s;
  f.cnt = f.bufsz = n ? n - 1 : 0;
  res = __doprint(&f, fmt, (char*)&fmt + sizeof(char*));
  if (n)
    *f.ptr = '\0';
  return res;
}
