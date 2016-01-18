/*
  Copyright (c) 2016, Alexey Frunze
  2-clause BSD license.
*/
#ifndef __FLOAT_H
#define __FLOAT_H

#define FLT_RADIX       2

#define FLT_ROUNDS      1

#define FLT_MANT_DIG                 24
#define FLT_EPSILON     1.19209290e-07f
#define FLT_DIG                       6
#define FLT_MIN_EXP                -125
#define FLT_MIN         1.17549435e-38f
#define FLT_MIN_10_EXP              -37
#define FLT_MAX_EXP                +128
#define FLT_MAX         3.40282347e+38f
#define FLT_MAX_10_EXP              +38

#define DECIMAL_DIG     9

// double is an alias for float
#define DBL_MANT_DIG    FLT_MANT_DIG
#define DBL_EPSILON     FLT_EPSILON
#define DBL_DIG         FLT_DIG
#define DBL_MIN_EXP     FLT_MIN_EXP
#define DBL_MIN         FLT_MIN
#define DBL_MIN_10_EXP  FLT_MIN_10_EXP
#define DBL_MAX_EXP     FLT_MAX_EXP
#define DBL_MAX         FLT_MAX
#define DBL_MAX_10_EXP  FLT_MAX_10_EXP

// there's no long double

#endif
