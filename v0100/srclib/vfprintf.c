/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include "istdio.h"

int vfprintf(FILE* f, char* fmt, va_list vl)
{
  return __doprint(f, fmt, vl);
}
