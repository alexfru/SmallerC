/*
  Copyright (c) 2016, Alexey Frunze
  2-clause BSD license.
*/

#ifdef __SMALLER_C_32__

#include <math.h>

float atanf(float x)
{
  return atan2f(x, 1);
}

double atan(double x)
{
  return atanf(x);
}

#endif
