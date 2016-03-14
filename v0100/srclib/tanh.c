/*
  Copyright (c) 2016, Alexey Frunze
  2-clause BSD license.
*/

#ifdef __SMALLER_C_32__

#include <math.h>

float tanhf(float x)
{
  int neg;
  float e;
  if (x == 0)
    return x; // preserve sign of 0
  if ((neg = x < 0) != 0)
    x = -x;
  if (x >= 10)
  {
    // +/-INF handled here
    e = 1;
  }
  else if (x < 1)
  {
    e = expm1f(x * 2);
    e = e / (e + 2);
  }
  else
  {
    // NAN handled here
    e = expm1f(x * 2);
    e = 1 - 2 / (e + 2);
  }
  return neg ? -e : e;
}

double tanh(double x)
{
  return tanhf(x);
}

#endif
