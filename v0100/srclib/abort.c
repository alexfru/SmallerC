/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include <stdlib.h>

void abort(void)
{
  // TBD??? use raise(SIGABRT)???
  exit(EXIT_FAILURE);
}
