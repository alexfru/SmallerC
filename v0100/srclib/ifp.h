/*
  Copyright (c) 2017, Alexey Frunze
  2-clause BSD license.
*/
#ifndef __IFP_H
#define __IFP_H

#ifdef __SMALLER_C_32__

#define MAX_FP_DIGITS 112
#define FP_MANT_BITS  23    // bits in mantissa, excluding the implicit 1
#define FP_EXP_BITS   8     // bits in exponent
#define FP_MIN_EXP    (-46) // from min denormal, ~1.40e-45
                            // (-46 is chosen because we need to handle numbers
                            // like 9e-46 which round up to a non-zero denormal
                            // number ~1.40e-45)
#define FP_MAX_EXP    38    // from max normal, ~3.40e+38
#define FP_BUF_SIZE   (((((MAX_FP_DIGITS-FP_MIN_EXP)*10+2)/3+FP_MANT_BITS+2)+7)/8)

unsigned __cvtfd(unsigned char* digits, int cnt, int eexp);

#endif

#endif
