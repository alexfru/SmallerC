/*
  Copyright (c) 2014-2018, Alexey Frunze
  2-clause BSD license.
*/
#ifndef __STDDEF_H
#define __STDDEF_H

#ifndef NULL
#define NULL 0
#endif

#ifndef __SIZE_T_DEF
#define __SIZE_T_DEF
typedef unsigned size_t;
#endif

typedef int ptrdiff_t;

#ifndef __WCHAR_T_DEF
#define __WCHAR_T_DEF
#ifdef __SMALLER_C_WCHAR16__
#ifdef __SMALLER_C_SWCHAR__
typedef short wchar_t;
#endif // __SMALLER_C_SWCHAR__
#ifdef __SMALLER_C_UWCHAR__
typedef unsigned short wchar_t;
#endif // __SMALLER_C_UWCHAR__
#endif // __SMALLER_C_WCHAR16__
#ifdef __SMALLER_C_WCHAR32__
#ifdef __SMALLER_C_SWCHAR__
typedef int wchar_t;
#endif // __SMALLER_C_SWCHAR__
#ifdef __SMALLER_C_UWCHAR__
typedef unsigned wchar_t;
#endif // __SMALLER_C_UWCHAR__
#endif // __SMALLER_C_WCHAR32__
#endif // __WCHAR_T_DEF

#ifdef __SMALLER_PP__
#define offsetof(type, member) ((unsigned)&((type*)0)->member)
#endif

#endif
