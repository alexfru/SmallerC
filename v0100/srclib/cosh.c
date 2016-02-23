/*
  Copyright (c) 2016, Alexey Frunze
  2-clause BSD license.
*/

#ifdef __SMALLER_C_32__

#include <math.h>

float coshf(float x)
{
  x = x * 1.44269504f/*log2(e)*/;
  return exp2f(x - 1) + exp2f(-x - 1);
}

double cosh(double x)
{
  return coshf(x);
}

#endif
