/*
  Copyright (c) 2014-2016, Alexey Frunze
  2-clause BSD license.
*/
#ifndef __ASSERT_H
#define __ASSERT_H

#ifdef assert
#undef assert
#endif

#ifdef __SMALLER_PP__

#ifdef NDEBUG
#define assert(expr) ((void)0)
#else
#define assert(expr) ((expr) ? (void)0 : __assert(__func__, __FILE__, __LINE__, #expr)(0))
#endif

#else

#ifdef NDEBUG
#define assert (1)?(void)0:(void)
#else
#define assert __assert(__func__, __FILE__, __LINE__, (char*)0)
#endif

#endif

void (*__assert(char*, char*, int, char*))(unsigned);

#endif
