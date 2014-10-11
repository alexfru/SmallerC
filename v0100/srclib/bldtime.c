/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include "itime.h"

#ifdef __SMALLER_C_32__
time_t __buildtime(struct tm* tm)
{
  time_t res;
  int leap, daysInMonth;

  // Out-of-range inputs make little sense, fail on them.
  // Note: this introduces incompatibility with the C standard.
  if
  (
    tm->tm_sec  <  0 || tm->tm_sec  > 59 ||
    tm->tm_min  <  0 || tm->tm_min  > 59 ||
    tm->tm_hour <  0 || tm->tm_hour > 23 ||
    tm->tm_mday <  1 || tm->tm_mday > 31 ||
    tm->tm_mon  <  0 || tm->tm_mon  > 11 ||
    tm->tm_year < 70 || tm->tm_year > 70+135
  )
    return (time_t)-1;

  leap = __isleap(1900 + tm->tm_year);

  daysInMonth = (tm->tm_mon == 1) ?
                28 + leap: // february
                30 + ((0xAD5 >> tm->tm_mon) & 1); // all other months
  if (tm->tm_mday > daysInMonth) // fail here as well
    return (time_t)-1;

  tm->tm_yday = __DaysSinceJan1st[leap][tm->tm_mon] + tm->tm_mday - 1;

  res = tm->tm_sec +
        tm->tm_min * SECONDS_PER_MINUTE +
        tm->tm_hour * (time_t)SECONDS_PER_HOUR +
        tm->tm_yday * SECONDS_PER_DAY +
        (tm->tm_year - 70) * SECONDS_PER_YEAR;

  // Now account for extra days in the leap years between 1970 and given year:
  //   add a day every 4 years starting in 1973,
  //   subtract a day back out every 100 years starting in 2001, and
  //   add a day back in every 400 years starting in 2001:
  res += ((tm->tm_year-69)>>2) * (time_t)SECONDS_PER_DAY -
         ((tm->tm_year-1)/100) * (time_t)SECONDS_PER_DAY +
         ((tm->tm_year+299)/400) * (time_t)SECONDS_PER_DAY;

  tm->tm_wday = (res / SECONDS_PER_DAY + 4) % 7;

  return res;
}
#endif
