/*
  Copyright (c) 2016, Alexey Frunze
  2-clause BSD license.
*/

#ifdef __SMALLER_C_32__

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

float atan2f(float y, float x)
{
  asm
  (
  "fld    dword ["xbp"+8]\n"
  "fld    dword ["xbp"+12]\n"
  "fpatan\n"
  "fstp   dword ["xbp"+8]\n"
  "mov    eax, ["xbp"+8]"
  );
}

double atan2(double y, double x)
{
  return atan2f(y, x);
}

#endif
