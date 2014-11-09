/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include "itime.h"

#ifdef __SMALLER_C_32__

// gmtime() must take UTC/GMT time and return UTC/GMT time
struct tm* gmtime(time_t* t)
{
  return __breaktime(t);
}

#endif // __SMALLER_C_32__
