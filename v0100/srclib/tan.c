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

float tanf(float x)
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
  // NAN will successfully propagate through fptan
  asm
  (
  "fldpi\n"
  "fadd     st0, st0\n" // 2*pi to reduce fabs(x) when it's too big
  "fld      dword ["xbp"+8]\n"
  ".repeat:\n"
  "fptan\n"
  "fstsw    ax\n"
  "sahf\n"
  "jnp      .done\n" // success
  "fprem\n" // fabs(x) is too big, reduce fabs(x) by a multiple of 2*pi
  "jmp      .repeat\n"
  ".done:\n"
  "ffree    st0\n" // mark the 1.0 (pushed by fptan) as free
  "fincstp\n" // adjust stack top (the 1.0 is now popped off)
  "fstp     st1\n"
  "fstp     dword ["xbp"+8]\n"
  "mov      eax, ["xbp"+8]"
  );
}

double tan(double x)
{
  return tanf(x);
}

#endif
