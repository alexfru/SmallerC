/*
  Copyright (c) 2016, Alexey Frunze
  2-clause BSD license.
*/

#ifdef __SMALLER_C_32__

/*
float frexpf(float value, int* e)
{
  int ex = 0;
  if (value == 0 || value == INFINITY || value == -INFINITY || value != value)
  {
    // Return +0.0/-0.0, +INF/-INF and NaN as-is
  }
  else
  {
    while (value < 0.5f)
      value = value * 2, ex--;
    while (value >= 1)
      value = value * 0.5f, ex++;
  }
  *e = ex;
  return value;
}
*/

#ifdef UNUSED

float frexpf(float value, int* e)
{
  union
  {
    float f;
    unsigned u;
  } u;
  unsigned tmp;

  u.f = value;
  tmp = u.u & 0x7FFFFFFF;

  // Return +0.0/-0.0, +INF/-INF and NaN as-is
  *e = 0;
  if (tmp != 0 && tmp < 0x7F800000)
  {
    int ex;
    if (tmp >= 0x00800000)
    {
      // Normalized
      ex = (tmp >> 23) + (1 - 127/*bias*/);
    }
    else
    {
      // Denormalized, must normalize
      ex = 1/*denorm*/ + 1 - 127/*bias*/;
      while (tmp < 0x00800000/*implicit 1*/)
        tmp <<= 1, ex--;
      u.u = (u.u & 0x80000000) | tmp;
    }
    u.u = (u.u & 0x807FFFFF) | ((127/*bias*/ - 1) << 23);
    *e = ex;
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
#ifdef __HUGE__
#define xbx "bx"
#else
#define xbx "ebx"
#endif
#else
#define xbp "ebp"
#define xbx "ebx"
#endif

float frexpf(float value, int* e)
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
  "mov    dword ["xbx"], 0\n" // preset *e=0 for +/-0.0, +/-INF, NAN
  "mov    ecx, eax\n"
  "shl    ecx, 1\n" // shift the sign out
  "jz     .done\n" // done if +/-0.0
  "cmp    ecx, 0xFF000000\n"
  "jnc    .done\n" // done if +/-INF or NAN
  "fld    dword ["xbp"+8]\n"
  "fxtract\n"
  "push   dword 0x3F000000\n" // push 0.5f
  "fld    dword ["xbp"-4]\n"
  "pop    eax\n"
  "fmulp\n"                  // scale significand down from [1,2) to [0.5,1)
  "fstp   dword ["xbp"+8]\n"
  "mov    eax, ["xbp"+8]\n"
  "fistp  dword ["xbx"]\n"
  "inc    dword ["xbx"]\n" // correct exponent
  ".done:"
  );
}

#endif

double frexp(double value, int* e)
{
  return frexpf(value, e);
}

#endif
