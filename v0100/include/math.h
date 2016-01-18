/*
  Copyright (c) 2016, Alexey Frunze
  2-clause BSD license.
*/
#ifndef __MATH_H
#define __MATH_H

#define INFINITY  (1.f/0.f)
#define NAN       (0.f/0.f)
#define HUGE_VALF INFINITY
#define HUGE_VAL  INFINITY

/*
// C99 TBD???
int fpclassify(real-floating x);
int isfinite(real-floating x);
int isinf(real-floating x);
int isnan(real-floating x);
int isnormal(real-floating x);
int signbit(real-floating x);
*/

/*
// C89 TBD!!!
double acos(double x);
double asin(double x);
double atan(double x);
double atan2(double y, double x);
double cos(double x);
double sin(double x);
double tan(double x);
double cosh(double x);
double sinh(double x);
double tanh(double x);
double exp(double x);
double frexp(double value, int* e);
double ldexp(double x, int e);
double log(double x);
double log10(double x);
double modf(double value, double* iptr);
double pow(double x, double y);
double sqrt(double x);
double ceil(double x);
double fabs(double x);
double floor(double x);
double fmod(double x, double y);
*/

#endif
