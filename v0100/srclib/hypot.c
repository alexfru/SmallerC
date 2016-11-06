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

float hypotf(float x, float y)
{
  union
  {
    unsigned u;
    float f;
  } ux, uy;
  ux.f = x;
  uy.f = y;
  ux.u &= 0x7FFFFFFF;
  uy.u &= 0x7FFFFFFF;
  // IEC60559: if one is zero, return fabsf() of the other
  if (ux.u == 0)
    return uy.f;
  if (uy.u == 0)
    return ux.f;
  // IEC60559: if one is infinity, return infinity (the other may be NAN)
  if (ux.u == 0x7F800000 || uy.u == 0x7F800000)
    return INFINITY;
  asm
  (
  "fld  dword ["xbp"+12]\n"
  "fmul st0, st0\n"
  "fld  dword ["xbp"+8]\n"
  "fmul st0, st0\n"
  "faddp\n"
  "fsqrt\n"
  "fstp dword ["xbp"+8]\n"
  "mov  eax, ["xbp"+8]"
  );
}

double hypot(double x, double y)
{
  return hypotf(x, y);
}

#endif
