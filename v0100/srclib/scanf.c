/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include "istdio.h"

int scanf(char* fmt, ...)
{
  return __doscan(stdin, fmt, (char*)&fmt + sizeof(char*));
}
