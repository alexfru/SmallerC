/*
  Copyright (c) 2016, Alexey Frunze
  2-clause BSD license.
*/

#ifdef __SMALLER_C_32__

#include <math.h>

float sinhf(float x)
{
  if (x >= -80 && x <= 80)
  {
    float e = expm1f(x);
    return (e + e / (e + 1)) * 0.5f;
  }
  else
  {
    // Special case for fabsf(x) > ~logf(FLT_MAX) to avoid
    // premature overflow of expf(x) to infinity
    int neg = x < 0;
    float e = neg ? -x : x;
    e = exp2f(e * 1.44269504f/*log2(e)*/ - 1);
    return neg ? -e : e;
  }
}

double sinh(double x)
{
  return sinhf(x);
}

#endif
