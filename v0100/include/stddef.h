/*
  Copyright (c) 2014, Alexey Frunze
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

#ifdef __SMALLER_PP__
#define offsetof(type, member) ((unsigned)&((type*)0)->member)
#endif

#endif
