/*
  Copyright (c) 2016, Alexey Frunze
  2-clause BSD license.
*/

#ifdef __SMALLER_C_32__

#include <math.h>

float roundf(float x)
{
  if (x >= 0)
  {
    float i = floorf(x);
    if (x - i >= .5f)
      i = i + 1;
    return i;
  }
  else
  {
    float i = floorf(-x);
    if (x + i <= -.5f)
      i = i + 1;
    return -i;
  }
}

double round(double x)
{
  return roundf(x);
}

#endif
