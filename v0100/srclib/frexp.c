/*
  Copyright (c) 2016, Alexey Frunze
  2-clause BSD license.
*/

#ifdef __SMALLER_C_32__

/*
float frexpf(float value, int* e)
{
  int ex = 0;
  if (value == 0 || value == INFINITY || value == -INFINITY || value != value)
  {
    // Return +0.0/-0.0, +INF/-INF and NaN as-is
  }
  else
  {
    while (value < 0.5f)
      value = value * 2, ex--;
    while (value >= 1)
      value = value * 0.5f, ex++;
  }
  *e = ex;
  return value;
}
*/

float frexpf(float value, int* e)
{
  union
  {
    float f;
    unsigned u;
  } u;
  unsigned tmp;

  u.f = value;
  tmp = u.u & 0x7FFFFFFF;

  // Return +0.0/-0.0, +INF/-INF and NaN as-is
  *e = 0;
  if (tmp != 0 && tmp < 0x7F800000)
  {
    int ex;
    if (tmp >= 0x00800000)
    {
      // Normalized
      ex = (tmp >> 23) + (1 - 127/*bias*/);
    }
    else
    {
      // Denormalized, must normalize
      ex = 1/*denorm*/ + 1 - 127/*bias*/;
      while (tmp < 0x00800000/*implicit 1*/)
        tmp <<= 1, ex--;
      u.u = (u.u & 0x80000000) | tmp;
    }
    u.u = (u.u & 0x807FFFFF) | ((127/*bias*/ - 1) << 23);
    *e = ex;
  }
  return u.f;
}

double frexp(double value, int* e)
{
  return frexpf(value, e);
}

#endif
