/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include "itime.h"

#ifdef _DOS

#ifdef __HUGE__

// localtime() must take UTC/GMT time and return local time
struct tm* localtime(time_t* t)
{
  // There's no sane way to support time zones in DOS. Pretend to have local time=UTC/GMT.
  return __breaktime(t);
}

#endif // __HUGE__

#endif // _DOS

#ifdef _WINDOWS

#include "iwin32.h"

// localtime() must take UTC/GMT time and return local time
struct tm* localtime(time_t* t)
{
  struct tm* tm;
  SYSTEMTIME st1, st2;
  // Convert from seconds to UTC/GMT
  if ((tm = __breaktime(t)) == NULL)
  {
    return NULL;
  }
  // Convert from UTC/GMT to local
  st1.wYear         = tm->tm_year + 1900;
  st1.wMonth        = tm->tm_mon + 1;
  st1.wDay          = tm->tm_mday;
  st1.wDayOfWeek    = tm->tm_wday;
  st1.wHour         = tm->tm_hour;
  st1.wMinute       = tm->tm_min;
  st1.wSecond       = tm->tm_sec;
  st1.wMilliseconds = 0;
  if (!SystemTimeToTzSpecificLocalTime(0, &st1, &st2))
  {
    return NULL;
  }
  tm->tm_year = st2.wYear - 1900;
  tm->tm_mon  = st2.wMonth - 1;
  tm->tm_mday = st2.wDay;
  tm->tm_wday = st2.wDayOfWeek;
  tm->tm_hour = st2.wHour;
  tm->tm_min  = st2.wMinute;
  tm->tm_sec  = st2.wSecond;
  tm->tm_isdst = 0;
  // Get proper tm_yday
  if (__buildtime(tm) == (time_t)-1)
  {
    return NULL;
  }
  return tm;
}

#endif // _WINDOWS
