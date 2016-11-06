/*
  Copyright (c) 2016, Alexey Frunze
  2-clause BSD license.
*/

#ifdef __SMALLER_C_32__

#include <math.h>
#include <float.h>

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
float f2xm1p1(float x)
{
  asm
  (
  "fld  dword ["xbp"+8]\n"
  "f2xm1\n" // x must be finite such that -1.0 <= x <= +1.0
  "fld1\n"
  "faddp\n"
  "fstp dword ["xbp"+8]\n"
  "mov  eax, ["xbp"+8]"
  );
}

float exp2f(float x)
{
  float i;
  if (x < FLT_MIN_EXP - FLT_MANT_DIG - 1)
    return 0;
  if (x >= FLT_MAX_EXP)
    return INFINITY;
  if (x != x)
    return x; // NAN
  x = f2xm1p1(modff(x, &i));
  return ldexpf(x, i);
}

double exp2(double x)
{
  return exp2f(x);
}

#endif
