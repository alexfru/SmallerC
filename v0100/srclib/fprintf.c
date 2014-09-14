/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include "istdio.h"

int fprintf(FILE* f, char* fmt, ...)
{
  return __doprint(f, fmt, (char*)&fmt + sizeof(char*));
}
