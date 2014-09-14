/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include <stdio.h>

int putc(int c, FILE* f)
{
  return fputc(c, f);
}
