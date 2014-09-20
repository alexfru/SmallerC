/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include "istdio.h"

int fscanf(FILE* f, char* fmt, ...)
{
  return __doscan(f, fmt, (char*)&fmt + sizeof(char*));
}
