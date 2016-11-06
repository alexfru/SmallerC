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

float fabsf(float x)
{
  asm
  (
  "mov eax, ["xbp"+8]\n"
  "and eax, 0x7fffffff"
  );
}

double fabs(double x)
{
  return fabsf(x);
}

#endif
