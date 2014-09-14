/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include "istdio.h"

int fileno(FILE* f)
{
  if (!f)
  {
    return -1;
  }
  return f->fd;
}
