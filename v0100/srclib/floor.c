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
#define xsp "sp"
#else
#define xbp "ebp"
#define xsp "esp"
#endif

float floorf(float x)
{
  asm
  (
  "sub    "xsp", 4\n"
  "fnstcw ["xbp"-2]\n" // save rounding
  "mov    ax, ["xbp"-2]\n"
  "mov    ah, 0x04\n" // rounding towards -infinity
  "mov    ["xbp"-4], ax\n"
  "fld    dword ["xbp"+8]\n"
  "fldcw  ["xbp"-4]\n"
  "frndint\n"
  "fstp   dword ["xbp"+8]\n"
  "fldcw  ["xbp"-2]\n" // restore rounding
  "add    "xsp", 4\n"
  "mov    eax, ["xbp"+8]"
  );
}

double floor(double x)
{
  return floorf(x);
}

#endif
