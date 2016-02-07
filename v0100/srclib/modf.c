/*
  Copyright (c) 2016, Alexey Frunze
  2-clause BSD license.
*/

#ifdef __SMALLER_C_32__

float modff(float value, float* iptr)
{
  union
  {
    float f;
    unsigned u;
  } u;
  unsigned tmp;

  u.f = value;
  tmp = u.u & 0x7FFFFFFF;

  *iptr = u.f;
  if (tmp == 0x7F800000)
  {
    // Return +INF/-INF as-is with fractional part of +0.0/-0.0
    u.u &= 0x80000000;
  }
  // Return +0.0/-0.0 and NaN as-is in both integral and fractional parts
  else if (tmp != 0 && tmp < 0x7F800000)
  {
    if (tmp >= ((127/*bias*/ + 23) << 23))
    {
      // Purely integral
      u.u &= 0x80000000;
    }
    else if (tmp < (127/*bias*/ << 23))
    {
      // Purely fractional
      u.u &= 0x80000000;
      *iptr = u.f;
      u.f = value;
    }
    else
    {
      int cnt = 127/*bias*/ + 23 - (tmp >> 23); // number of fract bits, 1 to 23
      u.u &= -(1u << cnt);
      *iptr = u.f;
      u.f = value;
      tmp = u.u & ((1u << cnt) - 1);
      if (tmp)
      {
        // Normalize
        int e = 0;
        while (tmp < 0x00800000/*implicit 1*/)
          tmp <<= 1, e++;
        u.u = ((u.u & 0xFF800000) | (tmp & 0x007FFFFF)) - (e << 23);
      }
      else
      {
        // Integral
        u.u &= 0x80000000;
      }
    }
  }
  return u.f;
}

double modf(double value, double* iptr)
{
  return modff(value, iptr);
}

#endif
