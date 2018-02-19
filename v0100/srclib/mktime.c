/*
  Copyright (c) 2014-2018, Alexey Frunze
  2-clause BSD license.
*/
#include "itime.h"

#ifdef _LINUX
#define UNIX_LIKE
#endif
#ifdef _MACOS
#define UNIX_LIKE
#endif

#ifdef _DOS

#ifdef __SMALLER_C_32__

// mktime() must take local time and return UTC/GMT time
time_t mktime(struct tm* tm)
{
  // There's no sane way to support time zones in DOS. Pretend to have local time=UTC/GMT.
  return __buildtime(tm);
}

#endif

#endif // _DOS

#ifdef _WINDOWS

#include "iwin32.h"

// mktime() must take local time and return UTC/GMT time
time_t mktime(struct tm* tm)
{
  SYSTEMTIME st1, st2;
  struct tm tm2;
  // Get proper tm_wday/tm_yday (and wDayOfWeek for TzSpecificLocalTimeToSystemTime())
  if (__buildtime(tm) == (time_t)-1)
  {
    return (time_t)-1;
  }
  // Convert local to UTC/GMT
  st1.wYear         = tm->tm_year + 1900;
  st1.wMonth        = tm->tm_mon + 1;
  st1.wDay          = tm->tm_mday;
  st1.wDayOfWeek    = tm->tm_wday;
  st1.wHour         = tm->tm_hour;
  st1.wMinute       = tm->tm_min;
  st1.wSecond       = tm->tm_sec;
  st1.wMilliseconds = 0;
  if (!__TzSpecificLocalTimeToSystemTime(0, &st1, &st2))
  {
    return (time_t)-1;
  }
  // Convert to seconds
  tm2.tm_year  = st2.wYear - 1900;
  tm2.tm_mon   = st2.wMonth - 1;
  tm2.tm_mday  = st2.wDay;
  tm2.tm_hour  = st2.wHour;
  tm2.tm_min   = st2.wMinute;
  tm2.tm_sec   = st2.wSecond;
  tm2.tm_isdst = 0;
  return __buildtime(&tm2);
}

#endif // _WINDOWS

#ifdef _LINUX

static
int SysGettimeofday(long tv[2], int tz[2])
{
  asm("mov eax, 78\n" // sys_gettimeofday
      "mov ebx, [ebp + 8]\n"
      "mov ecx, [ebp + 12]\n"
      "int 0x80");
}

#endif // _LINUX

#ifdef UNIX_LIKE
// mktime() must take local time and return UTC/GMT time
time_t mktime(struct tm* tm)
{
  // TBD??? struct timezone (or the whole gettimeofday()) is obsolete per POSIX 2008, use something else???
  // TBD??? honor other TZ settings???
  time_t tt = __buildtime(tm);
  // TBD: figure out how to get the time zone on MacOS.
#ifdef _LINUX
  long tv[2];
  int tz[2] = { 0 };
  if (SysGettimeofday(tv, tz) == 0)
    tt += tz[0] * 60;
#endif // _LINUX
  return tt;
}

#endif // UNIX_LIKE
