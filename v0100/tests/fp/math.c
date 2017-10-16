/*
  This is a basic test for <math.h> functions.

  How to compile for DOS (huge/.EXE, unreal/.EXE, 32-bit DPMI/.EXE):
    smlrcc -dosh math.c -o mathh.exe
    smlrcc -dosu math.c -o mathu.exe
    smlrcc -dosp math.c -o mathp.exe

  How to compile for Windows:
    smlrcc -win math.c -o mathw.exe

  How to compile for Linux:
    smlrcc -linux math.c -o mathl

  How to compile for MacOS:
    smlrcc -macos math.c -o mathm
*/

#include <math.h>
#include <float.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

enum Flt2Flt
{
  FSIN,
  FCOS,
  FTAN,
  FATAN,
  FASIN,
  FACOS,
  FEXP,
  FEXP2,
  FEXPM1,
  FSQRT,
  FFABS,
  FLOG,
  FLOG2,
  FLOG10,
  FCEIL,
  FFLOOR,
  FTRUNC,
  FROUND,
  FSINH,
  FCOSH,
  FTANH
};

static struct
{
  float(*fxn)(float); char* name;
} aFlt2Flt[/*enum Flt2Flt*/] =
{
   {  &sinf,   "sinf",
 },{  &cosf,   "cosf",
 },{  &tanf,   "tanf",
 },{  &atanf,  "atanf",
 },{  &asinf,  "asinf",
 },{  &acosf,  "acosf",
 },{  &expf,   "expf",
 },{  &exp2f,  "exp2f",
 },{  &expm1f, "expm1f",
 },{  &sqrtf,  "sqrtf",
 },{  &fabsf,  "fabsf",
 },{  &logf,   "logf",
 },{  &log2f,  "log2f",
 },{  &log10f, "log10f",
 },{  &ceilf,  "ceilf",
 },{  &floorf, "floorf",
 },{  &truncf, "truncf",
 },{  &roundf, "roundf",
 },{  &sinhf,  "sinhf",
 },{  &coshf,  "coshf",
 },{  &tanhf,  "tanhf",
 }
};

enum FltFlt2Flt
{
  FHYPOT,
  FATAN2,
  FPOW,
  FFMOD
};

static struct
{
  float(*fxn)(float, float); char* name;
} aFltFlt2Flt[/*enum FltFlt2Flt*/] =
{
   {  &hypotf, "hypotf",
 },{  &atan2f, "atan2f",
 },{  &powf,   "powf",
 },{  &fmodf,  "fmodf",
 }
};

int errors;

int cmp(float v, float emin, float emax)
{
  // Make sure either both emin and emax are NANs or none.
  assert((emin != emin) == (emax != emax));
  // Check for NAN.
  if (emin != emin)
  {
    return v != v;
  }
  assert(emin <= emax);
  // Range check.
  if (emin <= v && v <= emax)
  {
    // Special case for comparing with +/-0.
    if (emin == 0 && emax == 0 && 1 / emin == 1 / emax)
    {
      // If emin and emax are both zeroes of the same sign, check the sign.
      return 1 / emin == 1 / v;
    }
    return 1;
  }
  return 0;
}

void t1(enum Flt2Flt f, float a, float emin, float emax, int err)
{
  float v;
  int vok, eok;
  char* fname = aFlt2Flt[f].name;
  errno = 0;
  v = aFlt2Flt[f].fxn(a);
  vok = cmp(v, emin, emax);
  eok = (err == errno);
  if (vok + eok != 2)
    printf("%s(%+e)=%+e, errno=%d (actual)\n"
           "%s(%+e)=%+e...%+e, errno=%d (expected)\n",
           fname, a, v, errno,
           fname, a, emin, emax, err),
    errors++;
}

void t2(enum FltFlt2Flt f, float a, float b, float emin, float emax, int err)
{
  float v;
  int vok, eok;
  char* fname = aFltFlt2Flt[f].name;
  errno = 0;
  v = aFltFlt2Flt[f].fxn(a, b);
  vok = cmp(v, emin, emax);
  eok = (err == errno);
  if (vok + eok != 2)
    printf("%s(%+e,%+e)=%+e, errno=%d (actual)\n"
           "%s(%+e,%+e)=%+e...%+e, errno=%d (expected)\n",
           fname, a, b, v, errno,
           fname, a, b, emin, emax, err),
    errors++;
}

#define FPI 3.1415927f
#define FPI_2 (FPI/2)
#define FPI_3 (FPI/3)
#define FPI_4 (FPI/4)
#define FPI_6 (FPI/6)

struct
{
  enum Flt2Flt f; float a, emin, emax; int err;
} at1[] =
{
   {  FSIN, +INFINITY, NAN,NAN, EDOM,
 },{  FSIN, -INFINITY, NAN,NAN, EDOM,
 },{  FSIN, NAN, NAN,NAN, 0,
 },{  FSIN, +0.0f, +0.0f,+0.0f, 0,
 },{  FSIN, -0.0f, -0.0f,-0.0f, 0,
 },{  FSIN, +1e-5f, +0.99999e-5f,+1.00001e-5f, 0,
 },{  FSIN, -1e-5f, -1.00001e-5f,-0.99999e-5f, 0,
 },{  FSIN, 0*FPI_2 + FPI_6, +0.49999f,+0.50001f, 0,
 },{  FSIN, 1*FPI_2 + FPI_6, +0.86602f,+0.86603f, 0,
 },{  FSIN, 2*FPI_2 + FPI_6, -0.50001f,-0.49999f, 0,
 },{  FSIN, 3*FPI_2 + FPI_6, -0.86603f,-0.86602f, 0,
 },{  FSIN, 4*FPI_2 + FPI_6, +0.49999f,+0.50001f, 0,
 },{  FSIN, 5*FPI_2 + FPI_6, +0.86602f,+0.86603f, 0,
 },{  FSIN, 6*FPI_2 + FPI_6, -0.50001f,-0.49999f, 0,
 },{  FSIN, 7*FPI_2 + FPI_6, -0.86603f,-0.86602f, 0,
 },{  FSIN, -0*FPI_2 - FPI_6, -0.50001f,-0.49999f, 0,
 },{  FSIN, -1*FPI_2 - FPI_6, -0.86603f,-0.86602f, 0,
 },{  FSIN, -2*FPI_2 - FPI_6, +0.49999f,+0.50001f, 0,
 },{  FSIN, -3*FPI_2 - FPI_6, +0.86602f,+0.86603f, 0,
 },{  FSIN, -4*FPI_2 - FPI_6, -0.50001f,-0.49999f, 0,
 },{  FSIN, -5*FPI_2 - FPI_6, -0.86603f,-0.86602f, 0,
 },{  FSIN, -6*FPI_2 - FPI_6, +0.49999f,+0.50001f, 0,
 },{  FSIN, -7*FPI_2 - FPI_6, +0.86602f,+0.86603f, 0,

 },{  FCOS, +INFINITY, NAN,NAN, EDOM,
 },{  FCOS, -INFINITY, NAN,NAN, EDOM,
 },{  FCOS, NAN, NAN,NAN, 0,
 },{  FCOS, +0.0f, 0.99999f,1.00001f, 0,
 },{  FCOS, -0.0f, 0.99999f,1.00001f, 0,
 },{  FCOS, 0*FPI_2 + FPI_6, +0.86602f,+0.86603f, 0,
 },{  FCOS, 1*FPI_2 + FPI_6, -0.50001f,-0.49999f, 0,
 },{  FCOS, 2*FPI_2 + FPI_6, -0.86603f,-0.86602f, 0,
 },{  FCOS, 3*FPI_2 + FPI_6, +0.49999f,+0.50001f, 0,
 },{  FCOS, 4*FPI_2 + FPI_6, +0.86602f,+0.86603f, 0,
 },{  FCOS, 5*FPI_2 + FPI_6, -0.50001f,-0.49999f, 0,
 },{  FCOS, 6*FPI_2 + FPI_6, -0.86603f,-0.86602f, 0,
 },{  FCOS, 7*FPI_2 + FPI_6, +0.49999f,+0.50001f, 0,
 },{  FCOS, -0*FPI_2 - FPI_6, +0.86602f,+0.86603f, 0,
 },{  FCOS, -1*FPI_2 - FPI_6, -0.50001f,-0.49999f, 0,
 },{  FCOS, -2*FPI_2 - FPI_6, -0.86603f,-0.86602f, 0,
 },{  FCOS, -3*FPI_2 - FPI_6, +0.49999f,+0.50001f, 0,
 },{  FCOS, -4*FPI_2 - FPI_6, +0.86602f,+0.86603f, 0,
 },{  FCOS, -5*FPI_2 - FPI_6, -0.50001f,-0.49999f, 0,
 },{  FCOS, -6*FPI_2 - FPI_6, -0.86603f,-0.86602f, 0,
 },{  FCOS, -7*FPI_2 - FPI_6, +0.49999f,+0.50001f, 0,

 },{  FTAN, +INFINITY, NAN,NAN, EDOM,
 },{  FTAN, -INFINITY, NAN,NAN, EDOM,
 },{  FTAN, NAN, NAN,NAN, 0,
 },{  FTAN, +0.0f, +0.0f,+0.0f, 0,
 },{  FTAN, -0.0f, -0.0f,-0.0f, 0,
 },{  FTAN, +1e-5f, +0.99999e-5f,+1.00001e-5f, 0,
 },{  FTAN, -1e-5f, -1.00001e-5f,-0.99999e-5f, 0,
 },{  FTAN, +FPI_4, +0.99999f,+1.00001f, 0,
 },{  FTAN, -FPI_4, -1.00001f,-0.99999f, 0,
 },{  FTAN, 0*FPI_2 + FPI_6, +0.57734f,+0.57736f, 0,
 },{  FTAN, 1*FPI_2 + FPI_6, -1.73206f,-1.73204f, 0,
 },{  FTAN, 2*FPI_2 + FPI_6, +0.57734f,+0.57736f, 0,
 },{  FTAN, 3*FPI_2 + FPI_6, -1.73206f,-1.73204f, 0,
 },{  FTAN, -0*FPI_2 - FPI_6, -0.57736f,-0.57734f, 0,
 },{  FTAN, -1*FPI_2 - FPI_6, +1.73204f,+1.73206f, 0,
 },{  FTAN, -2*FPI_2 - FPI_6, -0.57736f,-0.57734f, 0,
 },{  FTAN, -3*FPI_2 - FPI_6, +1.73204f,+1.73206f, 0,

 },{  FATAN, +INFINITY, +1.57079f,+1.57080f, 0,
 },{  FATAN, -INFINITY, -1.57080f,-1.57079f, 0,
 },{  FATAN, NAN, NAN,NAN, 0,
 },{  FATAN, +0.0f, +0.0f,+0.0f, 0,
 },{  FATAN, -0.0f, -0.0f,-0.0f, 0,
 },{  FATAN, +1e-5f, +0.99999e-5f,+1.00001e-5f, 0,
 },{  FATAN, -1e-5f, -1.00001e-5f,-0.99999e-5f, 0,
 },{  FATAN, +1, +0.78539f,+0.78540f, 0,
 },{  FATAN, -1, -0.78540f,-0.78539f, 0,
 },{  FATAN, +1.7320508f, +1.04719f,+1.04720f, 0,
 },{  FATAN, -1.7320508f, -1.04720f,-1.04719f, 0,
 },{  FATAN, +1e6f, +1.57079f,+1.57080f, 0,
 },{  FATAN, -1e6f, -1.57080f,-1.57079f, 0,

 },{  FASIN, +INFINITY, NAN,NAN, EDOM,
 },{  FASIN, -INFINITY, NAN,NAN, EDOM,
 },{  FASIN, NAN, NAN,NAN, 0,
 },{  FASIN, +1.00001f, NAN,NAN, EDOM,
 },{  FASIN, -1.00001f, NAN,NAN, EDOM,
 },{  FASIN, +0.0f, +0.0f,+0.0f, 0,
 },{  FASIN, -0.0f, -0.0f,-0.0f, 0,
 },{  FASIN, +1e-5f, +0.99999e-5f,+1.00001e-5f, 0,
 },{  FASIN, -1e-5f, -1.00001e-5f,-0.99999e-5f, 0,
 },{  FASIN, +1, +1.57079f,+1.57080f, 0,
 },{  FASIN, -1, -1.57080f,-1.57079f, 0,
 },{  FASIN, +0.5f, +0.52359f,+0.52360f, 0,
 },{  FASIN, -0.5f, -0.52360f,-0.52359f, 0,

 },{  FACOS, +INFINITY, NAN,NAN, EDOM,
 },{  FACOS, -INFINITY, NAN,NAN, EDOM,
 },{  FACOS, NAN, NAN,NAN, 0,
 },{  FACOS, +1.00001f, NAN,NAN, EDOM,
 },{  FACOS, -1.00001f, NAN,NAN, EDOM,
 },{  FACOS, +0.0f, +1.57079f,+1.57080f, 0,
 },{  FACOS, -0.0f, +1.57079f,+1.57080f, 0,
 },{  FACOS, +1, +0.0f,+0.0f, 0,
 },{  FACOS, -1, +3.14159f,+3.14160f, 0,
 },{  FACOS, +0.5f, +1.04719f,+1.04720f, 0,
 },{  FACOS, -0.5f, +2.09439f,+2.09440f, 0,

 },{  FEXP, +INFINITY, +INFINITY,+INFINITY, 0,
 },{  FEXP, -INFINITY, 0,0, 0,
 },{  FEXP, NAN, NAN,NAN, 0,
 },{  FEXP, +0.0f, 1,1, 0,
 },{  FEXP, -0.0f, 1,1, 0,
 },{  FEXP, +1, +2.71828f,+2.71829f, 0,
 },{  FEXP, -1, +0.367879f,+0.367880f, 0,
 },{  FEXP, +10, +22026.4f,+22026.5f, 0,
 },{  FEXP, -10, +4.53999e-5f,+4.54000e-5f, 0,
 },{  FEXP, -87.336545f, +1.17549e-38f,+1.17550e-38f, 0,
 },{  FEXP, +88.029692f, +1.70140e+38f,+1.70142e+38f, 0,

 },{  FEXP2, +INFINITY, +INFINITY,+INFINITY, 0,
 },{  FEXP2, -INFINITY, 0,0, 0,
 },{  FEXP2, NAN, NAN,NAN, 0,
 },{  FEXP2, +0.0f, 1,1, 0,
 },{  FEXP2, -0.0f, 1,1, 0,
 },{  FEXP2, +1, 2,2, 0,
 },{  FEXP2, -1, +0.5f,+0.5f, 0,
 },{  FEXP2, +10, +1024.0f,+1024.0f, 0,
 },{  FEXP2, -10, +9.765625e-4f,+9.765625e-4f, 0,
 },{  FEXP2, +0.5f, +1.41421f,+1.41422f, 0,
 },{  FEXP2, -0.5f, +0.707106f,+0.707107f, 0,
 },{  FEXP2, -126, +1.17549e-38f,+1.17550e-38f, 0,
 },{  FEXP2, +127, +1.70140e+38f,+1.70142e+38f, 0,

 },{  FEXPM1, +INFINITY, +INFINITY,+INFINITY, 0,
 },{  FEXPM1, -INFINITY, -1,-1, 0,
 },{  FEXPM1, NAN, NAN,NAN, 0,
 },{  FEXPM1, +0.0f, +0.0f,+0.0f, 0,
 },{  FEXPM1, -0.0f, -0.0f,-0.0f, 0,
 },{  FEXPM1, +1e-5f, +0.99999e-5f,+1.00001e-5f, 0,
 },{  FEXPM1, -1e-5f, -1.00001e-5f,-0.99999e-5f, 0,
 },{  FEXPM1, +1, +1.71828f,+1.71829f, 0,
 },{  FEXPM1, -1, -0.632121f,-0.632120f, 0,
 },{  FEXPM1, +10, +22025.4f,+22025.5f, 0,
 },{  FEXPM1, -10, -0.999955f,-0.999954f, 0,
 },{  FEXPM1, -87.336545f, -1.00001f,-0.99999f, 0,
 },{  FEXPM1, +88.029692f, +1.70140e+38f,+1.70142e+38f, 0,

 },{  FSQRT, +INFINITY, +INFINITY,+INFINITY, 0,
 },{  FSQRT, -INFINITY, NAN,NAN, EDOM,
 },{  FSQRT, NAN, NAN,NAN, 0,
 },{  FSQRT, -1, NAN,NAN, EDOM,
 },{  FSQRT, +0.0f, +0.0f,+0.0f, 0,
 },{  FSQRT, -0.0f, -0.0f,-0.0f, 0,
 },{  FSQRT, 2, +1.41421f,+1.41422f, 0,
 },{  FSQRT, 4, +1.99999f,+2.00001f, 0,
 },{  FSQRT, 3.40282347e38f, +1.844674e19f,+1.844675e19f, 0,

 },{  FFABS, +INFINITY, +INFINITY,+INFINITY, 0,
 },{  FFABS, -INFINITY, +INFINITY,+INFINITY, 0,
 },{  FFABS, +NAN, NAN,NAN, 0,
 },{  FFABS, -NAN, NAN,NAN, 0,
 },{  FFABS, +1, +1,+1, 0,
 },{  FFABS, -1, +1,+1, 0,
 },{  FFABS, +0.0f, +0.0f,+0.0f, 0,
 },{  FFABS, -0.0f, +0.0f,+0.0f, 0,

 },{  FLOG2, +INFINITY, +INFINITY,+INFINITY, 0,
 },{  FLOG2, -INFINITY, NAN,NAN, EDOM,
 },{  FLOG2, NAN, NAN,NAN, 0,
 },{  FLOG2, +0.0f, -INFINITY,-INFINITY, ERANGE,
 },{  FLOG2, -0.0f, -INFINITY,-INFINITY, ERANGE,
 },{  FLOG2, -1, NAN,NAN, EDOM,
 },{  FLOG2, +1, -1e-10f,+1e-10f, 0,
 },{  FLOG2, 2, +0.99999f,+1.00001f, 0,
 },{  FLOG2, 0.5f, -1.00001f,-0.99999f, 0,
 },{  FLOG2, 2.71828183f, +1.44269f,+1.44270f, 0,
 },{  FLOG2, 10, +3.32192f,+3.32193f, 0,
 },{  FLOG2, +1.1754944e-38f, -126.001f,-125.999f, 0,
 },{  FLOG2, +1.7014118e+38f, +126.999f,+127.001f, 0,

 },{  FLOG10, +INFINITY, +INFINITY,+INFINITY, 0,
 },{  FLOG10, -INFINITY, NAN,NAN, EDOM,
 },{  FLOG10, NAN, NAN,NAN, 0,
 },{  FLOG10, +0.0f, -INFINITY,-INFINITY, ERANGE,
 },{  FLOG10, -0.0f, -INFINITY,-INFINITY, ERANGE,
 },{  FLOG10, -1, NAN,NAN, EDOM,
 },{  FLOG10, +1, -1e-10f,+1e-10f, 0,
 },{  FLOG10, 2, +0.301029f,+0.301031f, 0,
 },{  FLOG10, 2.71828183f, +0.434294f,+0.434295f, 0,
 },{  FLOG10, 10, +0.99999f,+1.00001f, 0,
 },{  FLOG10, 0.1f, -1.00001f,-0.99999f, 0,
 },{  FLOG10, +1.1754944e-38f, -37.9298f,-37.9297f, 0,
 },{  FLOG10, +1.7014118e+38f, +38.2307f,+38.2309f, 0,

 },{  FLOG, +INFINITY, +INFINITY,+INFINITY, 0,
 },{  FLOG, -INFINITY, NAN,NAN, EDOM,
 },{  FLOG, NAN, NAN,NAN, 0,
 },{  FLOG, +0.0f, -INFINITY,-INFINITY, ERANGE,
 },{  FLOG, -0.0f, -INFINITY,-INFINITY, ERANGE,
 },{  FLOG, -1, NAN,NAN, EDOM,
 },{  FLOG, +1, -1e-10f,+1e-10f, 0,
 },{  FLOG, 2, +0.693146f,+0.693148f, 0,
 },{  FLOG, 2.71828183f, +0.99999f,+1.00001f, 0,
 },{  FLOG, 10, +2.30258f,+2.30259f, 0,
 },{  FLOG, +1.1754944e-38f, -87.3366f,-87.3365f, 0,
 },{  FLOG, +1.7014118e+38f, +88.0296f,+88.0298f, 0,

 },{  FCEIL, +INFINITY, +INFINITY,+INFINITY, 0,
 },{  FCEIL, -INFINITY, -INFINITY,-INFINITY, 0,
 },{  FCEIL, NAN, NAN,NAN, 0,
 },{  FCEIL, +0.0f, +0.0f,+0.0f, 0,
 },{  FCEIL, -0.0f, -0.0f,-0.0f, 0,
 },{  FCEIL, +0.25f, +1.0f,+1.0f, 0,
 },{  FCEIL, -0.25f, -0.0f,-0.0f, 0,
 },{  FCEIL, +0.75f, +1.0f,+1.0f, 0,
 },{  FCEIL, -0.75f, -0.0f,-0.0f, 0,
 },{  FCEIL, +1.0f, +1.0f,+1.0f, 0,
 },{  FCEIL, -1.0f, -1.0f,-1.0f, 0,
 },{  FCEIL, +8388607.5f, +8388608.0f,+8388608.0f, 0,
 },{  FCEIL, -8388607.5f, -8388607.0f,-8388607.0f, 0,

 },{  FFLOOR, +INFINITY, +INFINITY,+INFINITY, 0,
 },{  FFLOOR, -INFINITY, -INFINITY,-INFINITY, 0,
 },{  FFLOOR, NAN, NAN,NAN, 0,
 },{  FFLOOR, +0.0f, +0.0f,+0.0f, 0,
 },{  FFLOOR, -0.0f, -0.0f,-0.0f, 0,
 },{  FFLOOR, +0.25f, +0.0f,+0.0f, 0,
 },{  FFLOOR, -0.25f, -1.0f,-1.0f, 0,
 },{  FFLOOR, +0.75f, +0.0f,+0.0f, 0,
 },{  FFLOOR, -0.75f, -1.0f,-1.0f, 0,
 },{  FFLOOR, +1.0f, +1.0f,+1.0f, 0,
 },{  FFLOOR, -1.0f, -1.0f,-1.0f, 0,
 },{  FFLOOR, +8388607.5f, +8388607.0f,+8388607.0f, 0,
 },{  FFLOOR, -8388607.5f, -8388608.0f,-8388608.0f, 0,

 },{  FTRUNC, +INFINITY, +INFINITY,+INFINITY, 0,
 },{  FTRUNC, -INFINITY, -INFINITY,-INFINITY, 0,
 },{  FTRUNC, NAN, NAN,NAN, 0,
 },{  FTRUNC, +0.0f, +0.0f,+0.0f, 0,
 },{  FTRUNC, -0.0f, -0.0f,-0.0f, 0,
 },{  FTRUNC, +0.25f, +0.0f,+0.0f, 0,
 },{  FTRUNC, -0.25f, -0.0f,-0.0f, 0,
 },{  FTRUNC, +0.75f, +0.0f,+0.0f, 0,
 },{  FTRUNC, -0.75f, -0.0f,-0.0f, 0,
 },{  FTRUNC, +1.0f, +1.0f,+1.0f, 0,
 },{  FTRUNC, -1.0f, -1.0f,-1.0f, 0,
 },{  FTRUNC, +8388607.5f, +8388607.0f,+8388607.0f, 0,
 },{  FTRUNC, -8388607.5f, -8388607.0f,-8388607.0f, 0,

 },{  FROUND, +INFINITY, +INFINITY,+INFINITY, 0,
 },{  FROUND, -INFINITY, -INFINITY,-INFINITY, 0,
 },{  FROUND, NAN, NAN,NAN, 0,
 },{  FROUND, +0.0f, +0.0f,+0.0f, 0,
 },{  FROUND, -0.0f, -0.0f,-0.0f, 0,
 },{  FROUND, +0.25f, +0.0f,+0.0f, 0,
 },{  FROUND, -0.25f, -0.0f,-0.0f, 0,
 },{  FROUND, +0.75f, +1.0f,+1.0f, 0,
 },{  FROUND, -0.75f, -1.0f,-1.0f, 0,
 },{  FROUND, +1.0f, +1.0f,+1.0f, 0,
 },{  FROUND, -1.0f, -1.0f,-1.0f, 0,
 },{  FROUND, +0.5f, +1.0f,+1.0f, 0,
 },{  FROUND, -0.5f, -1.0f,-1.0f, 0,
 },{  FROUND, +8388607.5f, +8388608.0f,+8388608.0f, 0,
 },{  FROUND, -8388607.5f, -8388608.0f,-8388608.0f, 0,

 },{  FSINH, +INFINITY, +INFINITY,+INFINITY, 0,
 },{  FSINH, -INFINITY, -INFINITY,-INFINITY, 0,
 },{  FSINH, NAN, NAN,NAN, 0,
 },{  FSINH, +0.0f, +0.0f,+0.0f, 0,
 },{  FSINH, -0.0f, -0.0f,-0.0f, 0,
 },{  FSINH, +1e-5f, +0.99999e-5f,+1.00001e-5f, 0,
 },{  FSINH, -1e-5f, -1.00001e-5f,-0.99999e-5f, 0,
 },{  FSINH, +1, +1.17519f,+1.17521f, 0,
 },{  FSINH, -1, -1.17521f,-1.17519f, 0,
 },{  FSINH, +10, +11013.23f,+11013.24f, 0,
 },{  FSINH, -10, -11013.24f,-11013.23f, 0,
 },{  FSINH, +88.722839f, +1.701411e38f,+1.701413e38f, 0,
 },{  FSINH, -88.722839f, -1.701413e38f,-1.701411e38f, 0,

 },{  FCOSH, +INFINITY, +INFINITY,+INFINITY, 0,
 },{  FCOSH, -INFINITY, +INFINITY,+INFINITY, 0,
 },{  FCOSH, NAN, NAN,NAN, 0,
 },{  FCOSH, +0.0f, 1,1, 0,
 },{  FCOSH, -0.0f, 1,1, 0,
 },{  FCOSH, +1, +1.543079f,+1.543081f, 0,
 },{  FCOSH, -1, +1.543079f,+1.543081f, 0,
 },{  FCOSH, +10, +11013.23f,+11013.24f, 0,
 },{  FCOSH, -10, +11013.23f,+11013.24f, 0,
 },{  FCOSH, +88.722839f, +1.701411e38f,+1.701413e38f, 0,
 },{  FCOSH, -88.722839f, +1.701411e38f,+1.701413e38f, 0,

 },{  FTANH, +INFINITY, +1,+1, 0,
 },{  FTANH, -INFINITY, -1,-1, 0,
 },{  FTANH, NAN, NAN,NAN, 0,
 },{  FTANH, +0.0f, +0.0f,+0.0f, 0,
 },{  FTANH, -0.0f, -0.0f,-0.0f, 0,
 },{  FTANH, +1e-5f, +0.99999e-5f,+1.00001e-5f, 0,
 },{  FTANH, -1e-5f, -1.00001e-5f,-0.99999e-5f, 0,
 },{  FTANH, +1, +0.76159f,+0.76160f, 0,
 },{  FTANH, -1, -0.76160f,+0.76159f, 0,
 },{  FTANH, +5, +0.99990f,+0.99992f, 0,
 },{  FTANH, -5, -0.99992f,-0.99990f, 0,
 },{  FTANH, +10, +0.99999f,+1.0f, 0,
 },{  FTANH, -10, -1.0f,-0.99999f, 0,

 }
};

struct
{
  enum FltFlt2Flt f; float a, b, emin, emax; int err;
} at2[] =
{
   {  FHYPOT, +INFINITY, 1, +INFINITY,+INFINITY, 0,
 },{  FHYPOT, 1, -INFINITY, +INFINITY,+INFINITY, 0,
 },{  FHYPOT, -INFINITY, NAN, +INFINITY,+INFINITY, 0,
 },{  FHYPOT, NAN, +INFINITY, +INFINITY,+INFINITY, 0,
 },{  FHYPOT, NAN, NAN, NAN,NAN, 0,
 },{  FHYPOT, 3, 4, +4.99999f,+5.00001f, 0,
 },{  FHYPOT, 3e+36f, 4e+36f, +4.99999e+36f,+5.00001e+36f, 0,
 },{  FHYPOT, 3e-36f, 4e-36f, +4.99999e-36f,+5.00001e-36f, 0,
 },{  FHYPOT, +1, +0.01f, +1.000049f,+1.000051f, 0,
 },{  FHYPOT, +0.01f, -1, +1.000049f,+1.000051f, 0,
 },{  FHYPOT, -1, +0.01f, +1.000049f,+1.000051f, 0,
 },{  FHYPOT, -0.01f, -1, +1.000049f,+1.000051f, 0,

 },{  FATAN2, NAN, NAN, NAN,NAN, 0,
 },{  FATAN2, +INFINITY, +INFINITY, +0.78539f,+0.78540f, 0,
 },{  FATAN2, -INFINITY, +INFINITY, -0.78540f,-0.78539f, 0,
 },{  FATAN2, +INFINITY, -INFINITY, +2.35619f,+2.35620f, 0,
 },{  FATAN2, -INFINITY, -INFINITY, -2.35620f,-2.35619f, 0,
 },{  FATAN2, +1, +INFINITY, +0.0f,+0.0f, 0,
 },{  FATAN2, -1, +INFINITY, -0.0f,-0.0f, 0,
 },{  FATAN2, +1, -INFINITY, +3.14159f,+3.14160f, 0,
 },{  FATAN2, -1, -INFINITY, -3.14160f,-3.14159f, 0,
 },{  FATAN2, +INFINITY, -1, +1.57079f,+1.57080f, 0,
 },{  FATAN2, -INFINITY, +1, -1.57080f,-1.57079f, 0,
 },{  FATAN2, +0.0f, +0.0f, +0.0f,+0.0f, 0,
 },{  FATAN2, -0.0f, +0.0f, -0.0f,-0.0f, 0,
 },{  FATAN2, +0.0f, -0.0f, +3.14159f,+3.14160f, 0,
 },{  FATAN2, -0.0f, -0.0f, -3.14160f,-3.14159f, 0,
 },{  FATAN2, +0.0f, +1, +0.0f,+0.0f, 0,
 },{  FATAN2, -0.0f, +1, -0.0f,-0.0f, 0,
 },{  FATAN2, +0.0f, -1, +3.14159f,+3.14160f, 0,
 },{  FATAN2, -0.0f, -1, -3.14160f,-3.14159f, 0,
 },{  FATAN2, +1, +0.0f, +1.57079f,+1.57080f, 0,
 },{  FATAN2, +1, -0.0f, +1.57079f,+1.57080f, 0,
 },{  FATAN2, -1, +0.0f, -1.57080f,-1.57079f, 0,
 },{  FATAN2, -1, -0.0f, -1.57080f,-1.57079f, 0,
 },{  FATAN2, +0.57735027e+38f, +1.0e+38f, +0.523598f,+0.523599f, 0,
 },{  FATAN2, +0.57735027e-37f, +1.0e-37f, +0.523598f,+0.523599f, 0,
 },{  FATAN2, +0.57735027f, +1.0f, +0.523598f,+0.523599f, 0,
 },{  FATAN2, +0.57735027f, -1.0f, +2.617990f,+2.618000f, 0,
 },{  FATAN2, -0.57735027f, +1.0f, -0.523599f,-0.523598f, 0,
 },{  FATAN2, -0.57735027f, -1.0f, -2.618000f,-2.617990f, 0,

 },{  FPOW, NAN, NAN, NAN,NAN, 0,
 },{  FPOW, NAN, +0.0f, 1,1, 0,
 },{  FPOW, NAN, -0.0f, 1,1, 0,
 },{  FPOW, +INFINITY, +INFINITY, +INFINITY,+INFINITY, 0,
 },{  FPOW, -INFINITY, +INFINITY, +INFINITY,+INFINITY, 0,
 },{  FPOW, +INFINITY, -INFINITY, 0,0, 0,
 },{  FPOW, -INFINITY, -INFINITY, 0,0, 0,
 },{  FPOW, +0.0f, +INFINITY, 0,0, 0,
 },{  FPOW, -0.0f, +INFINITY, 0,0, 0,
 },{  FPOW, +1, +INFINITY, 1,1, 0,
 },{  FPOW, +1, -INFINITY, 1,1, 0,
 },{  FPOW, -1, +INFINITY, 1,1, 0,
 },{  FPOW, -1, -INFINITY, 1,1, 0,
 },{  FPOW, +1.25f, +INFINITY, +INFINITY,+INFINITY, 0,
 },{  FPOW, -1.25f, +INFINITY, +INFINITY,+INFINITY, 0,
 },{  FPOW, +0.75f, +INFINITY, 0,0, 0,
 },{  FPOW, -0.75f, +INFINITY, 0,0, 0,
 },{  FPOW, +1e-7f, +INFINITY, 0,0, 0,
 },{  FPOW, -1e-7f, +INFINITY, 0,0, 0,
 },{  FPOW, +0.0f, -INFINITY, +INFINITY,+INFINITY, 0,
 },{  FPOW, -0.0f, -INFINITY, +INFINITY,+INFINITY, 0,
 },{  FPOW, +1.25f, -INFINITY, 0,0, 0,
 },{  FPOW, -1.25f, -INFINITY, 0,0, 0,
 },{  FPOW, +0.75f, -INFINITY, +INFINITY,+INFINITY, 0,
 },{  FPOW, -0.75f, -INFINITY, +INFINITY,+INFINITY, 0,
 },{  FPOW, +1e-7f, -INFINITY, +INFINITY,+INFINITY, 0,
 },{  FPOW, -1e-7f, -INFINITY, +INFINITY,+INFINITY, 0,
 },{  FPOW, +INFINITY, +0.0f, 1,1, 0,
 },{  FPOW, +INFINITY, +1e-7f, +INFINITY,+INFINITY, 0,
 },{  FPOW, +INFINITY, +0.75f, +INFINITY,+INFINITY, 0,
 },{  FPOW, +INFINITY, +1.25f, +INFINITY,+INFINITY, 0,
 },{  FPOW, +INFINITY, +1e+7f, +INFINITY,+INFINITY, 0,
 },{  FPOW, +INFINITY, -0.0f, 1,1, 0,
 },{  FPOW, +INFINITY, -1e-7f, 0,0, 0,
 },{  FPOW, +INFINITY, -0.75f, 0,0, 0,
 },{  FPOW, +INFINITY, -1.25f, 0,0, 0,
 },{  FPOW, +INFINITY, -1e+7f, 0,0, 0,
 },{  FPOW, -INFINITY, +0.0f, 1,1, 0,
 },{  FPOW, -INFINITY, +1, -INFINITY,-INFINITY, 0,
 },{  FPOW, -INFINITY, +2, +INFINITY,+INFINITY, 0,
 },{  FPOW, -INFINITY, +101, -INFINITY,-INFINITY, 0,
 },{  FPOW, -INFINITY, +102, +INFINITY,+INFINITY, 0,
 },{  FPOW, -INFINITY, +0.25f, +INFINITY,+INFINITY, 0,
 },{  FPOW, -INFINITY, +1.25f, +INFINITY,+INFINITY, 0,
 },{  FPOW, -INFINITY, -0.0f, 1,1, 0,
 },{  FPOW, -INFINITY, -1, -0.0f,-0.0f, 0,
 },{  FPOW, -INFINITY, -2, 0,0, 0,
 },{  FPOW, -INFINITY, -101, -0.0f,-0.0f, 0,
 },{  FPOW, -INFINITY, -102, 0,0, 0,
 },{  FPOW, -INFINITY, -0.25f, 0,0, 0,
 },{  FPOW, -INFINITY, -1.25f, 0,0, 0,
 },{  FPOW, +0.0f, NAN, NAN,NAN, 0,
 },{  FPOW, -0.0f, NAN, NAN,NAN, 0,
 },{  FPOW, +1, NAN, 1,1, 0,
 },{  FPOW, -1, NAN, NAN,NAN, 0,
 },{  FPOW, NAN, -1, NAN,NAN, 0,
 },{  FPOW, NAN, +1, NAN,NAN, 0,
 },{  FPOW, +INFINITY, NAN, NAN,NAN, 0,
 },{  FPOW, -INFINITY, NAN, NAN,NAN, 0,
 },{  FPOW, NAN, +INFINITY, NAN,NAN, 0,
 },{  FPOW, NAN, -INFINITY, NAN,NAN, 0,
 },{  FPOW, -0.25f, +1.25f, NAN,NAN, EDOM,
 },{  FPOW, -0.25f, -1.25f, NAN,NAN, EDOM,
 },{  FPOW, +0.0f, -1, +INFINITY,+INFINITY, ERANGE,
 },{  FPOW, -0.0f, -1, -INFINITY,-INFINITY, ERANGE,
 },{  FPOW, +0.0f, -2, +INFINITY,+INFINITY, ERANGE,
 },{  FPOW, -0.0f, -2, +INFINITY,+INFINITY, ERANGE,
 },{  FPOW, +0.0f, -1.5f, +INFINITY,+INFINITY, ERANGE,
 },{  FPOW, -0.0f, -1.5f, +INFINITY,+INFINITY, ERANGE,
 },{  FPOW, +2.71828183f, +3.14159265f, +23.1406f,+23.1408f, 0,
 },{  FPOW, +3.14159265f, +2.71828183f, +22.4591f,+22.4592f, 0,
 },{  FPOW, -2, 3, -8.00001f,-7.99999f, 0,
 },{  FPOW, 2, 0.5f, +1.41421f,+1.41422f, 0,
 },{  FPOW, 10, +38, +0.99999e+38f,+1.00001e+38f, 0,
 },{  FPOW, 10, -38, +0.99999e-38f,+1.00001e-38f, 0,
 },{  FPOW, 1e+38f, 1/+38.0f, +9.9999f,+10.0001f, 0,
 },{  FPOW, 1e-38f, 1/-38.0f, +9.9999f,+10.0001f, 0,

 },{  FFMOD, NAN, NAN, NAN,NAN, 0,
 },{  FFMOD, +0.0f, -1, +0.0f,+0.0f, 0,
 },{  FFMOD, -0.0f, +1, -0.0f,-0.0f, 0,
 },{  FFMOD, +INFINITY, 1, NAN,NAN, EDOM,
 },{  FFMOD, -INFINITY, 1, NAN,NAN, EDOM,
 },{  FFMOD, 1, +0.0f, NAN,NAN, EDOM,
 },{  FFMOD, 1, -0.0f, NAN,NAN, EDOM,
 },{  FFMOD, -1, +INFINITY, -1,-1, 0,
 },{  FFMOD, -1, -INFINITY, -1,-1, 0,
 },{  FFMOD, +1, +INFINITY, +1,+1, 0,
 },{  FFMOD, +1, -INFINITY, +1,+1, 0,
 },{  FFMOD, +5, +3, +2,+2, 0,
 },{  FFMOD, +5, -3, +2,+2, 0,
 },{  FFMOD, -5, +3, -2,-2, 0,
 },{  FFMOD, -5, -3, -2,-2, 0,

 }
};

/*
TBD!!!
float frexpf(float, int*);
float ldexpf(float, int);
float modff(float, float*);
*/

int main(void)
{
  unsigned i;
  for (i = 0; i < sizeof at1 / sizeof at1[0]; i++)
    t1(at1[i].f, at1[i].a, at1[i].emin, at1[i].emax, at1[i].err);
  for (i = 0; i < sizeof at2 / sizeof at2[0]; i++)
    t2(at2[i].f, at2[i].a, at2[i].b, at2[i].emin, at2[i].emax, at2[i].err);
  if (errors)
  {
    printf("Math test failed with %d error(s)!\n", errors);
    return EXIT_FAILURE;
  }
  puts("Math test passed!");
  return 0;
}
