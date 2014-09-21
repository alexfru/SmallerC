/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#ifndef __ASSERT_H
#define __ASSERT_H

#ifdef assert
#undef assert
#endif

#ifdef NDEBUG
#define assert (1)?(void)0:(void) // TBD!!! must be a parametrized macro, ignoring its parameter
#else
#define assert __assert(__func__, __FILE__, __LINE__)
#endif

void (*__assert(char*, char*, int))(unsigned);

#endif
