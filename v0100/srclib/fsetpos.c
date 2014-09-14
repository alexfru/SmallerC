/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include "istdio.h"
#include <errno.h>

#ifdef __SMALLER_C_32__
int fsetpos(FILE* f, fpos_t* pos)
{
  union
  {
    fpos_t fpos;
    long lpos;
  } u;
  u.fpos = *pos;
  if (!fseek(f, u.lpos, SEEK_SET))
    return 0;
//  errno = EUNKNOWN;
  return -1;
}
#endif

#ifdef __SMALLER_C_16__
int fsetpos(FILE* f, fpos_t* pos)
{
  if (!__fseek(f, pos, SEEK_SET))
    return 0;
//  errno = EUNKNOWN;
  return -1;
}
#endif
