/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include <time.h>
#include <stdio.h>

char* asctime(struct tm* tm)
{
  static char day[][3] =
  {
    "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
  };
  static char month[][3] =
  {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
  };
  static char res[26];

  sprintf(res, "%.3s %.3s%3d %.2d:%.2d:%.2d %d\n",
          day[tm->tm_wday],
          month[tm->tm_mon],
          tm->tm_mday,
          tm->tm_hour,
          tm->tm_min,
          tm->tm_sec,
          1900 + tm->tm_year);

  return res;
}
