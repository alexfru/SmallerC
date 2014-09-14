/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#ifndef __LIMITS_H
#define __LIMITS_H

#define CHAR_BIT 8

#ifdef __SMALLER_C_SCHAR__
#define CHAR_MIN (-128)
#define CHAR_MAX 127
#endif

#ifdef __SMALLER_C_UCHAR__
#define CHAR_MIN 0
#define CHAR_MAX 255
#endif

#define SCHAR_MIN (-128)
#define SCHAR_MAX 127
#define UCHAR_MAX 255

#define SHRT_MIN (-32767-1)
#define SHRT_MAX 32767
#define USHRT_MAX 0xFFFF

#ifdef __SMALLER_C_16__
#define INT_MIN (-32767-1)
#define INT_MAX 32767
#define UINT_MAX 65535U
#endif

#ifdef __SMALLER_C_32__
#define INT_MIN (-2147483647-1)
#define INT_MAX 2147483647
#define UINT_MAX 4294967295U
#define LONG_MIN (-2147483647L-1)
#define LONG_MAX 2147483647L
#define ULONG_MAX 4294967295UL
#endif

#endif
