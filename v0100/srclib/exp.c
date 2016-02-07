/*
  Copyright (c) 2016, Alexey Frunze
  2-clause BSD license.
*/

#ifdef __SMALLER_C_32__

#include <math.h>

float expf(float x)
{
  return exp2f(x * 1.44269504f/*log2(e)*/);
}

double exp(double x)
{
  return expf(x);
}

#endif
