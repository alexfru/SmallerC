/*
  Copyright (c) 2016, Alexey Frunze
  2-clause BSD license.
*/

#ifdef __SMALLER_C_32__

#include <time.h>

double difftime(time_t time1, time_t time0)
{
  if (time1 >= time0)
    return (double)((unsigned long)time1 - time0);
  return -(double)((unsigned long)time0 - time1);
}

#endif
