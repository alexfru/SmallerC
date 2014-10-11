/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include "itime.h"

static char* DayAbbr[] =
{
  "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};

static char* DayFull[] =
{
  "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
};

static char* MonthAbbr[] =
{
  "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

static char* MonthFull[] =
{
  "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"
};

struct bufstate
{
  char* s;
  size_t maxsize;
  size_t size;
};

static void __putc(int c, struct bufstate* b)
{
  if (b->size++ < b->maxsize)
    *b->s++ = c;
}

static void __puts(char* s, struct bufstate* b)
{
  while (*s != '\0')
    __putc(*s++, b);
}

static void __putn(unsigned n, int width, int padch, struct bufstate* b)
{
  char s[10/*max of 10 decimal digits in 32-bit int*/ + 1/*NUL*/];
  char* p = s + sizeof s;
  int dcnt = 0;
  *--p = '\0';
  do
  {
    *--p = '0' + n % 10;
    n /= 10;
    dcnt++;
  } while (n);
  while (dcnt < width)
    __putc(padch, b), dcnt++;
  __puts(p, b);
}

static int doformat(struct bufstate* b, int c, struct tm* t)
{
  int res = 1;
  // TBD??? better range checks???
  switch (c)
  {
  case 'a': // the first three characters of %A
    __puts((t->tm_wday < 0 || t->tm_wday >= 7) ? "?" : DayAbbr[t->tm_wday], b);
    break;

  case 'A': // one of "Sunday", "Monday", ... , "Saturday"
    __puts((t->tm_wday < 0 || t->tm_wday >= 7) ? "?" : DayFull[t->tm_wday], b);
    break;

  case 'h': // is equivalent to "%b". [tm_mon]
    // fallthrough

  case 'b': // the first three characters of %B
    __puts((t->tm_mon < 0 || t->tm_mon >= 12) ? "?" : MonthAbbr[t->tm_mon], b);
    break;

  case 'B': // one of "January", "February", ... , "December"
    __puts((t->tm_mon < 0 || t->tm_mon >= 12) ? "?" : MonthFull[t->tm_mon], b);
    break;

  case 'c': // is replaced by the locale's appropriate date and time representation: equivalent to "%a %b %e %T %Y"
    res &= doformat(b, 'a', t);
    __putc(' ', b);
    res &= doformat(b, 'b', t);
    __putc(' ', b);
    res &= doformat(b, 'e', t);
    __putc(' ', b);
    res &= doformat(b, 'T', t);
    __putc(' ', b);
    res &= doformat(b, 'Y', t);
    break;

  case 'C': // is replaced by the year divided by 100 and truncated to an integer, as a decimal number (00-99). [tm_year]
    __putn((t->tm_year + 1900) / 100, 2, '0', b);
    break;

  case 'd': // is replaced by the day of the month as a decimal number (01-31). [tm_mday]
    __putn(t->tm_mday, 2, '0', b);
    break;

  case 'x': // is replaced by the locale's appropriate date representation: equivalent to "%m/%d/%y"
    // fallthrough

  case 'D': // is equivalent to "%m/%d/%y". [tm_mon, tm_mday, tm_year]
    res &= doformat(b, 'm', t);
    __putc('/', b);
    res &= doformat(b, 'd', t);
    __putc('/', b);
    res &= doformat(b, 'y', t);
    break;

  case 'e': // is replaced by the day of the month as a decimal number ( 1-31); a single digit is preceded by a space. [tm_mday]
    __putn(t->tm_mday, 2, ' ', b);
    break;

  case 'F': // is equivalent to "%Y-%m-%d" (the ISO 8601 date format). [tm_year, tm_mon, tm_mday]
    res &= doformat(b, 'Y', t);
    __putc('-', b);
    res &= doformat(b, 'm', t);
    __putc('-', b);
    res &= doformat(b, 'd', t);
    break;

  case 'g': // is replaced by the last 2 digits of the week-based year (see below) as a decimal number (00-99). [tm_year, tm_wday, tm_yday]
  case 'G': // is replaced by the week-based year (see below) as a decimal number (e.g., 1997). [tm_year, tm_wday, tm_yday]
  case 'V': // is replaced by the ISO 8601 week number (see below) as a decimal number (01-53). [tm_year, tm_wday, tm_yday]
/*
  %g, %G,and %V give values according to the ISO 8601 week-based year. In this system,
  weeks begin on a Monday and week 1 of the year is the week that includes January 4th,
  which is also the week that includes the first Thursday of the year, and is also the first
  week that contains at least four days in the year. If the first Monday of January is the
  2nd, 3rd, or 4th, the preceding days are part of the last week of the preceding year; thus,
  for Saturday 2nd January 1999, %G is replaced by 1998 and %V is replaced by 53. If
  December 29th, 30th, or 31st is a Monday, it and any following days are part of week 1 of
  the following year. Thus, for Tuesday 30th December 1997, %G is replaced by 1998 and
  %V is replaced by 01.
*/
    {
      int year = t->tm_year + 1900;
      int wday_jan1st = (6 + t->tm_wday - t->tm_yday % 7) % 7; // Jat 1st is: 0=Mon,1=Tue,...,6=Sun
      // Jan 1st week is in this year if Jan 1st is Mon, Tue, Wed or Thu.
      // Otherwise, Jan 1st week is in the previous year.
      int yday_mon_on_or_before_jan1st = -wday_jan1st; // Monday on or just before Jan 1st is this number of days from Jan 1st
      int week = (t->tm_yday - yday_mon_on_or_before_jan1st) / 7; // week (0...52) since the week that includes Jan 1st
      week -= wday_jan1st >= 4; // take into account Jan 1st's week potentially belonging to the previous year
      if (week < 0)
      {
        // The week is the last week of the previous year, find out how many weeks are in that year.
        // If there were 52*7=364 days in a year, the year would always have 52 weeks:
        // either 1) 52 whole weeks or 2) 51 whole weeks and 2 partial weeks, and only one of these two
        // partial weeks would belong to the year because of having the majority (4+) of its days in the year
        // (the other would have 3 or fewer days and thus belong to an adjacent year, in which it has 4+ days).
        // In 365-day years there are always at least 52 weeks. Partial weeks on both ends of a 365-day year
        // may have 4 and 4 of their days respectively in the year. In this special case both partial weeks
        // belong to the year, making the year consist of 53 weeks.
        // In 366-day/leap years there are always at least 52 weeks. Partial weeks on both ends of a 366-day year
        // may have 4 and 5 of their days respectively in the year. In this special case both partial weeks
        // belong to the year, making the year consist of 53 weeks.
        int weeks = 52;
        int days_in_last_partial_week = wday_jan1st; // 0...6
        year--;
        if (days_in_last_partial_week == 4 ||
            (days_in_last_partial_week == 5 && __isleap(year)))
          weeks = 53;
        week += weeks; // 51 or 52
      }
      else if (week == 52)
      {
        // The week is either the last week of this year or the first week of the next year, find out which one it is.
        int weeks = 52;
        int days_in_first_partial_week = (7 - wday_jan1st) % 7; // 0...6
        if (days_in_first_partial_week == 4 ||
            (days_in_first_partial_week == 5 && __isleap(year)))
          weeks = 53;
        if (weeks == 52)
        {
          year++;
          week = 0;
        }
      }
      if (c == 'g')
        __putn(year % 100, 2, '0', b);
      else if (c == 'G')
        __putn(year, 0, '0', b);
      else
        __putn(week + 1, 2, '0', b);
    }
    break;

  case 'H': // is replaced by the hour (24-hour clock) as a decimal number (00-23). [tm_hour]
    __putn(t->tm_hour, 2, '0', b);
    break;

  case 'I': // is replaced by the hour (12-hour clock) as a decimal number (01-12). [tm_hour]
    __putn((t->tm_hour % 12) ? t->tm_hour % 12 : 12, 2, '0', b);
    break;

  case 'j': // is replaced by the day of the year as a decimal number (001-366). [tm_yday]
    __putn(t->tm_yday + 1, 3, '0', b);
    break;

  case 'm': // is replaced by the month as a decimal number (01-12). [tm_mon]
    __putn(t->tm_mon + 1, 2, '0', b);
    break;

  case 'M': // is replaced by the minute as a decimal number (00-59). [tm_min]
    __putn(t->tm_min, 2, '0', b);
    break;

  case 'n': // is replaced by a new-line character
    __putc('\n', b);
    break;

  case 'p': // one of "AM" or "PM"
    __puts((t->tm_hour >= 12) ? "PM" : "AM", b);
    break;

  case 'r': // equivalent to "%I:%M:%S %p"
    res &= doformat(b, 'I', t);
    __putc(':', b);
    res &= doformat(b, 'M', t);
    __putc(':', b);
    res &= doformat(b, 'S', t);
    __putc(' ', b);
    res &= doformat(b, 'p', t);
    break;

  case 'R': // is equivalent to "%H:%M". [tm_hour, tm_min]
    res &= doformat(b, 'H', t);
    __putc(':', b);
    res &= doformat(b, 'M', t);
    break;

  case 'S': // is replaced by the second as a decimal number (00-60). [tm_sec]
    __putn(t->tm_sec, 2, '0', b);
    break;

  case 't': // is replaced by a horizontal-tab character
    __putc('\t', b);
    break;

  case 'X': // is replaced by the locale's appropriate time representation: equivalent to %T
    // fallthrough

  case 'T': // is equivalent to "%H:%M:%S" (the ISO 8601 time format). [tm_hour, tm_min, tm_sec]
    res &= doformat(b, 'H', t);
    __putc(':', b);
    res &= doformat(b, 'M', t);
    __putc(':', b);
    res &= doformat(b, 'S', t);
    break;

  case 'u': // is replaced by the ISO 8601 weekday as a decimal number (1-7), where Monday is 1. [tm_wday]
    __putn(t->tm_wday ? t->tm_wday : 7, 1, '0', b);
    break;

  case 'U': // is replaced by the week number of the year (the first Sunday as the first day of week 1) as a decimal number (00-53). [tm_year, tm_wday, tm_yday]
    __putn((t->tm_yday + 7 - t->tm_wday) / 7, 2, '0', b);
    break;

  case 'w': // is replaced by the weekday as a decimal number (0-6), where Sunday is 0. [tm_wday]
    __putn(t->tm_wday, 1, '0', b);
    break;

  case 'W': // is replaced by the week number of the year (the first Monday as the first day of week 1) as a decimal number (00-53). [tm_year, tm_wday, tm_yday]
    __putn((t->tm_yday + 7 - (t->tm_wday ? (t->tm_wday - 1) : 6)) / 7, 2, '0', b);
    break;

  case 'y': // is replaced by the last 2 digits of the year as a decimal number (00-99). [tm_year]
    __putn((t->tm_year + 1900) % 100, 2, '0', b);
    break;

  case 'Y': // is replaced by the year as a decimal number (e.g., 1997). [tm_year]
    __putn(t->tm_year + 1900, 0, '0', b);
    break;

  case 'z': // is replaced by the offset from UTC in the ISO 8601 format "-0430" (meaning 4 hours 30 minutes behind UTC, west of Greenwich), or by no characters if no time zone is determinable. [tm_isdst]
    // There's no sane way to support time zones in DOS.
    break;

  case 'Z': // implementation-defined: is replaced by the locale's time zone name or abbreviation, or by no characters if no time zone is determinable. [tm_isdst]
    // There's no sane way to support time zones in DOS.
    break;

  default:
    __putc(c, b);
    break;
  }

  return res;
}

static int helper(struct bufstate* b, char* fmt, struct tm* t)
{
  int c;

  while ((c = *fmt++) != '\0')
  {
    if (c != '%' || *fmt == '%')
    {
      __putc(c, b);
      fmt += (c == '%');
      continue;
    }

    if ((c = *fmt++) == '\0')
      return 0;

    if (c == 'E' || c == 'O')
      if ((c = *fmt++) == '\0')
        return 0;

    if (!doformat(b, c, t))
      return 0;
  }

  __putc('\0', b);
  return 1;
}

size_t strftime(char* s, size_t maxsize, char* fmt, struct tm* t)
{
  struct bufstate b;

  b.s = s;
  b.maxsize = maxsize;
  b.size = 0;

  if (!helper(&b, fmt, t))
    return 0;

  return (b.size <= b.maxsize) ? b.size - 1 : 0;
}
