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

float cosf(float x)
{
  union
  {
    unsigned u;
    float f;
  } u;
  u.f = x;
  if ((u.u & 0x7FFFFFFF) == 0x7F800000) // if x is infinite
  {
    errno = EDOM;
    return NAN;
  }
  // NAN will successfully propagate through fcos
  asm
  (
  "fldpi\n"
  "fadd     st0, st0\n" // 2*pi to reduce fabs(x) when it's too big
  "fld      dword ["xbp"+8]\n"
  ".repeat:\n"
  "fcos\n"
  "fstsw    ax\n"
  "sahf\n"
  "jnp      .done\n" // success
  "fprem\n" // fabs(x) is too big, reduce fabs(x) by a multiple of 2*pi
  "jmp      .repeat\n"
  ".done:\n"
  "fstp     st1\n"
  "fstp     dword ["xbp"+8]\n"
  "mov      eax, ["xbp"+8]"
  );
}

double cos(double x)
{
  return cosf(x);
}

#endif
