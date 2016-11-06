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

float fmodf(float x, float y)
{
  union
  {
    unsigned u;
    float f;
  } ux, uy;
  ux.f = x;
  uy.f = y;
  if ((ux.u & 0x7FFFFFFF) == 0x7F800000 || (uy.u & 0x7FFFFFFF) == 0) // infinite x or zero y
  {
    errno = EDOM;
    return NAN;
  }
  asm
  (
  "fld      dword ["xbp"+12]\n"
  "fld      dword ["xbp"+8]\n"
  ".repeat:\n"
  "fprem\n"
  "fstsw    ax\n"
  "sahf\n"
  "jp       .repeat\n"
  "fstp     st1\n"
  "fstp     dword ["xbp"+8]\n"
  "mov      eax, ["xbp"+8]"
  );
}

double fmod(double x, double y)
{
  return fmodf(x, y);
}

#endif
