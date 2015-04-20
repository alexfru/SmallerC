/*
  Copyright (c) 2015, Alexey Frunze
  2-clause BSD license.
*/
#include <stdlib.h>

#ifdef __SMALLER_C_32__
ldiv_t ldiv(long numer, long denom)
{
  ldiv_t r;
  r.quot = numer / denom;
  r.rem = numer % denom;
  return r;
}
#endif
