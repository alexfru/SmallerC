/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include "istdio.h"

void clearerr(FILE* f)
{
  f->flags &= ~(_IOEOF | _IOERR);
}
