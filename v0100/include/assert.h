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
#define assert // TBD!!! must be a parametrized macro, ignoring its parameter
#else
#define assert __assert
#endif

void __assert(unsigned);

#endif
