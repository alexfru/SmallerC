/*
  Copyright (c) 2016, Alexey Frunze
  2-clause BSD license.
*/

#ifdef __SMALLER_C_32__

#include <math.h>

float sinhf(float x)
{
  int neg;
  float e;
  if ((neg = x < 0) != 0)
    x = -x;
  if (x <= 80)
  {
    e = expm1f(x);
    e = (e + e / (e + 1)) * 0.5f;
  }
  else
  {
    // Special case for fabsf(x) > ~logf(FLT_MAX) to avoid
    // premature overflow of expf(x) to infinity
    e = exp2f(x * 1.44269504f/*log2(e)*/ - 1);
  }
  return neg ? -e : e;
}

double sinh(double x)
{
  return sinhf(x);
}

#endif
