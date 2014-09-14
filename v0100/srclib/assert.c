/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include <stdlib.h>
#include <stdio.h>

void __assert(unsigned expr)
{
  if (!expr)
  {
    fprintf(stderr, "Assertion failed.\n");
    abort();
  }
}
