/*
  Copyright (c) 2016, Alexey Frunze
  2-clause BSD license.
*/

#ifdef __SMALLER_C_32__

#include <math.h>
#include <errno.h>

float powf(float x, float y)
{
  int yint, yoddint;
  float hy;
  if (x != x) // if NAN
    return (y == 0) ? 1 : x;
  if (y != y) // if NAN
    return (x == 1) ? 1 : y;
  if (x == 1 || y == 0)
    return 1;
  if (x == -1 && (y == -INFINITY || y == INFINITY))
    return 1;
  if (y == 1)
    return x;
  yint = y == truncf(y); // note: true for +/-INF
  hy = y * 0.5f;
  yoddint = yint && truncf(hy) != hy; // note: false for +/-INF
  if (x == 0)
  {
    union
    {
      unsigned u;
      float f;
    } u;
    int cond;
    u.f = x;
    cond = (int)u.u < 0 && yoddint; // note: false for +/-INF
    if (y < 0)
    {
      if (y != -INFINITY)
        errno = ERANGE;
      return cond ? -INFINITY : INFINITY;
    }
    else
      return cond ? -0.0f : 0.0f;
  }
  if (y == -INFINITY)
    return (fabsf(x) < 1) ? INFINITY : 0;
  if (y == INFINITY)
    return (fabsf(x) < 1) ? 0 : INFINITY;
  if (x == -INFINITY)
  {
    if (y < 0)
      return yoddint ? -0.0f : 0.0f;
    else
      return yoddint ? -INFINITY : INFINITY;
  }
  if (x == INFINITY)
    return (y < 0) ? 0 : INFINITY;
  if (x < 0)
  {
    if (!yint)
    {
      errno = EDOM;
      return NAN;
    }
    y = exp2f(y * log2f(-x));
    return yoddint ? -y : y;
  }
  return exp2f(y * log2f(x));
}

double pow(double x, double y)
{
  return powf(x, y);
}

#endif
