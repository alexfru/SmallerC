/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include "istdio.h"

int feof(FILE* f)
{
  return f->flags & _IOEOF;
}
