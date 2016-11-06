/*
  Copyright (c) 2016, Alexey Frunze
  2-clause BSD license.
*/

#ifdef __SMALLER_C_32__

#include <math.h>
#include <errno.h>

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

float asinf(float x)
{
  union
  {
    unsigned u;
    float f;
  } u;
  u.f = x;
  if ((u.u &= 0x7FFFFFFF) > 0x3F800000) // if fabs(x) > 1 or x is NAN
  {
    if (u.u <= 0x7F800000) // if x isn't NAN
      errno = EDOM;
    return NAN;
  }
  asm
  (
  "fld      dword ["xbp"+8]\n"
  "fld      st0\n"
  "fld1\n"
  "fsubr    st1, st0\n"
  "fadd     st0, st2\n"
  "fmulp\n"
  "fsqrt\n"
  "fpatan\n"
  "fstp     dword ["xbp"+8]\n"
  "mov      eax, ["xbp"+8]"
  );
}

double asin(double x)
{
  return asinf(x);
}

#endif
