/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include "istdio.h"

int vprintf(char* fmt, va_list vl)
{
  return __doprint(stdout, fmt, vl);
}
