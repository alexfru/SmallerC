/*
  Copyright (c) 2015, Alexey Frunze
  2-clause BSD license.
*/
#include <stdlib.h>

div_t div(int numer, int denom)
{
  div_t r;
  r.quot = numer / denom;
  r.rem = numer % denom;
  return r;
}
