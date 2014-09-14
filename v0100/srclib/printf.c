/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include "istdio.h"

int printf(char* fmt, ...)
{
  return __doprint(stdout, fmt, (char*)&fmt + sizeof(char*));
}
