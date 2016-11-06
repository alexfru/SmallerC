/*
  Copyright (c) 2016, Alexey Frunze
  2-clause BSD license.
*/

#ifdef __SMALLER_C_32__

#ifdef UNUSED

float modff(float value, float* iptr)
{
  union
  {
    float f;
    unsigned u;
  } u;
  unsigned tmp;

  u.f = value;
  tmp = u.u & 0x7FFFFFFF;

  *iptr = u.f;
  if (tmp == 0x7F800000)
  {
    // Return +INF/-INF as-is with fractional part of +0.0/-0.0
    u.u &= 0x80000000;
  }
  // Return +0.0/-0.0 and NaN as-is in both integral and fractional parts
  else if (tmp != 0 && tmp < 0x7F800000)
  {
    if (tmp >= ((127/*bias*/ + 23) << 23))
    {
      // Purely integral
      u.u &= 0x80000000;
    }
    else if (tmp < (127/*bias*/ << 23))
    {
      // Purely fractional
      u.u &= 0x80000000;
      *iptr = u.f;
      u.f = value;
    }
    else
    {
      int cnt = 127/*bias*/ + 23 - (tmp >> 23); // number of fract bits, 1 to 23
      u.u &= -(1u << cnt);
      *iptr = u.f;
      u.f = value;
      tmp = u.u & ((1u << cnt) - 1);
      if (tmp)
      {
        // Normalize
        int e = 0;
        while (tmp < 0x00800000/*implicit 1*/)
          tmp <<= 1, e++;
        u.u = ((u.u & 0xFF800000) | (tmp & 0x007FFFFF)) - (e << 23);
      }
      else
      {
        // Integral
        u.u &= 0x80000000;
      }
    }
  }
  return u.f;
}

#else

#ifdef __HUGE__
#define __HUGE_OR_UNREAL__
#endif
#ifdef __UNREAL__
#define __HUGE_OR_UNREAL__
#endif

#ifdef __HUGE_OR_UNREAL__
#define xbp "bp"
#define xsp "sp"
#ifdef __HUGE__
#define xbx "bx"
#else
#define xbx "ebx"
#endif
#else
#define xbp "ebp"
#define xsp "esp"
#define xbx "ebx"
#endif

float modff(float value, float* iptr)
{
  asm
  (
  "mov    eax, ["xbp"+8]\n"
  "mov    ebx, ["xbp"+12]\n"
#ifdef __HUGE__
  "ror    ebx, 4\n"
  "mov    ds, bx\n"
  "shr    ebx, 28\n"
#endif
  "mov    ["xbx"], eax\n" // preset *iptr=value for +/-0.0, +/-INF, NAN
  "mov    ecx, eax\n"
  "shl    ecx, 1\n" // shift the sign out
  "jz     .done\n" // done if +/-0.0
  "cmp    ecx, 0xFF000000\n"
  "jb     .finite\n"
  "ja     .done\n" // done if NAN
  "and    eax, 0x80000000\n" // return +0.0 for +INF, -0.0 for -INF
  "jmp    .done\n"

  ".finite:\n"
  "sub    "xsp", 4\n"
  "fnstcw ["xbp"-2]\n" // save rounding
  "mov    ax, ["xbp"-2]\n"
  "mov    ah, 0x0c\n" // rounding towards 0 (AKA truncate)
  "mov    ["xbp"-4], ax\n"
  "fld    dword ["xbp"+8]\n"
  "fld    st0\n"
  "fldcw  ["xbp"-4]\n"
  "frndint\n" // trunc(value)
  "fst    dword ["xbx"]\n" // *iptr = trunc(value)
  "fldcw  ["xbp"-2]\n" // restore rounding
  "add    "xsp", 4\n"
  "fsubp\n" // value - trunc(value)
  "fstp   dword ["xbp"+8]\n"
  "mov    eax, ["xbp"+8]\n" // eax = value - trunc(value)
  // almost done, copy the sign of *iptr into the returned value...
  "mov    ebx, dword ["xbx"]\n" // ebx = trunc(value)
  "shl    eax, 1\n"
  "rcl    ebx, 1\n"
  "rcr    eax, 1\n"
  ".done:"
  );
}

#endif

double modf(double value, double* iptr)
{
  return modff(value, iptr);
}

#endif
