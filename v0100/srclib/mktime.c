/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include "itime.h"

#ifdef _DOS
#ifdef __HUGE__
time_t mktime(struct tm* tm)
{
  // There's no sane way to support time zones in DOS. Pretend to have local time=UTC/GMT.
  return __buildtime(tm);
}
#endif
#endif
