/*
  Copyright (c) 2014-2018, Alexey Frunze
  2-clause BSD license.
*/
#ifndef __STDINT_H
#define __STDINT_H

#ifndef __INTPTR_T_DEF
#define __INTPTR_T_DEF
typedef int intptr_t;
#endif
typedef unsigned uintptr_t;

#ifdef __SMALLER_C_16__
#define INTPTR_MIN (-32767-1)
#define INTPTR_MAX 32767
#define UINTPTR_MAX 65535U

#define PTRDIFF_MIN (-32767-1)
#define PTRDIFF_MAX 32767

#define SIZE_MAX 65535U

typedef int intmax_t;
#define INTMAX_MIN (-32767-1)
#define INTMAX_MAX 32767
typedef unsigned uintmax_t;
#define UINTMAX_MAX 65535U
#endif // __SMALLER_C_16__

#ifdef __SMALLER_C_32__
#define INTPTR_MIN (-2147483647-1)
#define INTPTR_MAX 2147483647
#define UINTPTR_MAX 4294967295U

#define PTRDIFF_MIN (-2147483647-1)
#define PTRDIFF_MAX 2147483647

#define SIZE_MAX 4294967295U

typedef long intmax_t;
#define INTMAX_MIN (-2147483647L-1)
#define INTMAX_MAX 2147483647L
typedef unsigned long uintmax_t;
#define UINTMAX_MAX 4294967295UL
#endif // __SMALLER_C_32__

typedef signed char int8_t, int_least8_t, int_fast8_t;
typedef unsigned char uint8_t, uint_least8_t, uint_fast8_t;

typedef short int16_t, int_least16_t, int_fast16_t;
typedef unsigned short uint16_t, uint_least16_t, uint_fast16_t;

#ifdef __SMALLER_C_32__
typedef int int32_t, int_least32_t, int_fast32_t;
typedef unsigned uint32_t, uint_least32_t, uint_fast32_t;
#endif

#define INT8_MIN        (-128)
#define INT_LEAST8_MIN  (-128)
#define INT_FAST8_MIN   (-128)
#define INT8_MAX        127
#define INT_LEAST8_MAX  127
#define INT_FAST8_MAX   127
#define UINT8_MAX       255
#define UINT_LEAST8_MAX 255
#define UINT_FAST8_MAX  255

#define INT16_MIN        (-32767-1)
#define INT_LEAST16_MIN  (-32767-1)
#define INT_FAST16_MIN   (-32767-1)
#define INT16_MAX        32767
#define INT_LEAST16_MAX  32767
#define INT_FAST16_MAX   32767
#define UINT16_MAX       0xFFFF
#define UINT_LEAST16_MAX 0xFFFF
#define UINT_FAST16_MAX  0xFFFF

#ifdef __SMALLER_C_32__
#define INT32_MIN        (-2147483647-1)
#define INT_LEAST32_MIN  (-2147483647-1)
#define INT_FAST32_MIN   (-2147483647-1)
#define INT32_MAX        2147483647
#define INT_LEAST32_MAX  2147483647
#define INT_FAST32_MAX   2147483647
#define UINT32_MAX       4294967295U
#define UINT_LEAST32_MAX 4294967295U
#define UINT_FAST32_MAX  4294967295U
#endif // __SMALLER_C_32__

#ifdef __SMALLER_PP__

#define INT8_C(val) (val)
#define UINT8_C(val) (val)

#ifdef __SMALLER_C_16__
#define INT16_C(val) (val)
#define UINT16_C(val) (val##U)

#define INTMAX_C(val) (val)
#define UINTMAX_C(val) (val##U)
#endif // __SMALLER_C_16__

#ifdef __SMALLER_C_32__
#define INT16_C(val) (val)
#define UINT16_C(val) (val)

#define INT32_C(val) (val)
#define UINT32_C(val) (val##U)

#define INTMAX_C(val) (val)
#define UINTMAX_C(val) (val##UL)
#endif // __SMALLER_C_32__

#endif // __SMALLER_PP__

#ifndef WCHAR_MAX

#ifdef __SMALLER_C_WCHAR16__
#ifdef __SMALLER_C_SWCHAR__
//typedef short wchar_t;
#define WCHAR_MIN (-32767-1)
#define WCHAR_MAX 32767
#endif // __SMALLER_C_SWCHAR__
#ifdef __SMALLER_C_UWCHAR__
//typedef unsigned short wchar_t;
#define WCHAR_MIN 0
#define WCHAR_MAX 0xFFFF
#endif // __SMALLER_C_UWCHAR__
#endif // __SMALLER_C_WCHAR16__

#ifdef __SMALLER_C_WCHAR32__
#ifdef __SMALLER_C_SWCHAR__
//typedef int wchar_t;
#define WCHAR_MIN (-2147483647-1)
#define WCHAR_MAX 2147483647
#endif // __SMALLER_C_SWCHAR__
#ifdef __SMALLER_C_UWCHAR__
//typedef unsigned wchar_t;
#define WCHAR_MIN 0U
#define WCHAR_MAX 4294967295U
#endif // __SMALLER_C_UWCHAR__
#endif // __SMALLER_C_WCHAR32__

#endif // WCHAR_MAX

#endif
