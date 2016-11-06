/*
  Copyright (c) 2016, Alexey Frunze
  2-clause BSD license.
*/

#ifdef __SMALLER_C_32__

/*
float ldexpf(float value, int e)
{
  if (value == 0 || value == INFINITY || value == -INFINITY || value != value)
  {
    // Return +0.0/-0.0, +INF/-INF and NaN as-is
  }
  else
  {
    while (e > 0)
      value = value * 2, e--;
    while (e < 0)
      value = value * 0.5f, e++; // won't round denormals correctly
  }
  return value;
}
*/

#ifdef UNUSED

#include <limits.h>

float ldexpf(float value, int e)
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
  if (tmp != 0 && tmp < 0x7F800000)
  {
    int ex;
    if (tmp >= 0x00800000)
    {
      // Normalized
      ex = tmp >> 23;
    }
    else
    {
      // Denormalized, normalize first
      ex = 1/*denorm*/;
      while (tmp < 0x00800000/*implicit 1*/)
        tmp <<= 1, ex--;
      u.u = (u.u & 0x80000000) | tmp;
    }
    if (ex >= 0 && e > INT_MAX - ex)
      ex = INT_MAX;
    else if (ex < 0 && e < INT_MIN - ex)
      ex = INT_MIN;
    else
      ex += e;
    if (ex >= 255)
    {
      // +INF/-INF
      u.u = (u.u & 0x80000000) | 0x7F800000;
    }
    else if (ex > 0)
    {
      // Normalized
      u.u = (u.u & 0x807FFFFF) | (ex << 23);
    }
    else if (ex < -149 - 1/*x*2**-150 may round up to y*2**-149*/ + 127/*bias*/)
    {
      // +0.0/-0.0
      u.u &= 0x80000000;
    }
    else
    {
      // Must denormalize
      int cnt = 1 - ex; // number of bits to shift out right (1 to 24)
      unsigned mask = (1u << (cnt + 1)) - 1;
      unsigned half = 1u << (cnt - 1);
      tmp = (u.u & 0x007FFFFF) | 0x00800000/*implicit 1*/;
      // Round to even
      if ((tmp & mask) != half)
        tmp += half; // May overflow to 0x00800000, but that's correct
      tmp >>= cnt;
      u.u = (u.u & 0x80000000) | tmp;
    }
  }
  return u.f;
}

#else

#ifdef __HUGE__
#define __HUGE_OR_UNREAL__
#endif
#ifdef __UNREAL__
#define __HUGE_OR_UNREAL__
#endif

#ifdef __HUGE_OR_UNREAL__
#define xbp "bp"
#else
#define xbp "ebp"
#endif

float ldexpf(float value, int e)
{
  asm
  (
  "fild  dword ["xbp"+12]\n"
  "fld   dword ["xbp"+8]\n"
  "fscale\n"
  "fstp  st1\n"
  "fstp  dword ["xbp"+8]\n"
  "mov   eax, ["xbp"+8]"
  );
}

#endif

double ldexp(double value, int e)
{
  return ldexpf(value, e);
}

#endif
