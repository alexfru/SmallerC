/*
  Copyright (c) 2016, Alexey Frunze
  2-clause BSD license.
*/

#ifdef __SMALLER_C_32__

#include <math.h>

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

static
float f2xm1(float x)
{
  asm
  (
  "fld   dword ["xbp"+8]\n"
  "f2xm1\n" // x must be finite such that -1.0 <= x <= +1.0
  "fstp  dword ["xbp"+8]\n"
  "mov   eax, ["xbp"+8]"
  );
}

float expm1f(float x)
{
  float i;
  if (x == 0)
    return x; // preserve sign of 0
  x = x * 1.44269504f/*log2(e)*/;
  if (x <= 26)
  {
    // -INF handled here
    x = f2xm1(modff(x, &i));
    i = ldexpf(1, i);
    return x * i + (i - 1);
  }
  else
  {
    // NAN, +INF handled here
    return exp2f(x);
  }
}

double expm1(double x)
{
  return expm1f(x);
}

#endif
