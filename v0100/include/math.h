/*
  Copyright (c) 2016, Alexey Frunze
  2-clause BSD license.
*/
#ifndef __MATH_H
#define __MATH_H

#ifdef __SMALLER_C_32__

#define INFINITY  (1.f/0.f)
#define NAN       (-(0.f/0.f)) // without '-' we get -NAN on x87
#define HUGE_VALF INFINITY
#define HUGE_VAL  INFINITY
#define HUGE_VALL INFINITY

#define MATH_ERRNO 1
#define MATH_ERREXCEPT 2
#define math_errhandling MATH_ERRNO // only set errno, don't raise exceptions

double frexp(double, int*);
float frexpf(float, int*);
double ldexp(double, int);
float ldexpf(float, int);
double modf(double, double*);
float modff(float, float*);
double fabs(double);
float fabsf(float);
double ceil(double);
float ceilf(float);
double floor(double);
float floorf(float);
double round(double);
float roundf(float);
double trunc(double);
float truncf(float);
double sqrt(double);
float sqrtf(float);
double hypot(double, double);
float hypotf(float, float);
double exp(double);
float expf(float);
double exp2(double);
float exp2f(float);
double expm1(double);
float expm1f(float);
double pow(double, double);
float powf(float, float);
double log(double);
float logf(float);
double log2(double);
float log2f(float);
double log10(double);
float log10f(float);
double sin(double);
float sinf(float);
double cos(double);
float cosf(float);
double tan(double);
float tanf(float);
double atan2(double, double);
float atan2f(float, float);
double atan(double);
float atanf(float);
double acos(double);
float acosf(float);
double asin(double);
float asinf(float);
double fmod(double, double);
float fmodf(float, float);
double cosh(double);
float coshf(float);
double sinh(double);
float sinhf(float);
double tanh(double);
float tanhf(float);

/*
// C99 TBD???

// Perhaps

int fpclassify(real-floating x);
int isfinite(real-floating x);
int isinf(real-floating x);
int isnan(real-floating x);
int isnormal(real-floating x);
int signbit(real-floating x);
int isgreater(real-floating x, real-floating y);
int isgreaterequal(real-floating x, real-floating y);
int isless(real-floating x, real-floating y);
int islessequal(real-floating x, real-floating y);
int islessgreater(real-floating x, real-floating y);
int isunordered(real-floating x, real-floating y);
double copysign(double x, double y);
float copysignf(float x, float y);
double nan(const char* s);
float nanf(const char* s);

long int lround(double x);
long int lroundf(float x);
*/

#endif // __SMALLER_C_32__

#endif // __MATH_H
