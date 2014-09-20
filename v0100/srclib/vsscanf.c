/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include "istdio.h"
#include <string.h>

int vsscanf(char* s, char* fmt, va_list vl)
{
  FILE f;
  f.flags = _IORD | _IOSTRING | _IOBINARY; // don't do file I/O, don't translate "\n" to "\r\n"
  f.ptr = f.buf = s;
  f.cnt = f.bufsz = strlen(s);
  return __doscan(&f, fmt, vl);
}
