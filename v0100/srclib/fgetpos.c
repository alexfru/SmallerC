/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include "istdio.h"
#include <errno.h>

#ifdef __SMALLER_C_32__
int fgetpos(FILE* f, fpos_t* pos)
{
  union
  {
    fpos_t fpos;
    long lpos;
  } u;
  if ((u.lpos = ftell(f)) != -1)
  {
    *pos = u.fpos;
    return 0;
  }
//  errno = EUNKNOWN;
  return -1;
}
#endif

#ifdef __SMALLER_C_16__
int fgetpos(FILE* f, fpos_t* pos)
{
  if (!__ftell(f, pos))
  {
    return 0;
  }
//  errno = EUNKNOWN;
  return -1;
}
#endif
