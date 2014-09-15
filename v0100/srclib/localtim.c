/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include "itime.h"

#ifdef _DOS
#ifdef __HUGE__
struct tm* localtime(time_t* t)
{
  // There's no sane way to support time zones in DOS. Pretend to have local time=UTC/GMT.
  return __breaktime(t);
}
#endif
#endif
