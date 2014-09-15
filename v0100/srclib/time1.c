/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
unsigned short __DaysSinceJan1st[2][13] =
{
  {0,31,59,90,120,151,181,212,243,273,304,334,365}, // 365 days, nonleap
  {0,31,60,91,121,152,182,213,244,274,305,335,366}  // 366 days, leap
};

int __isleap(unsigned year)
{
  if (year & 3)
    return 0;

  year %= 400;

  if (!(year -= 100)) return 0;
  if (!(year -= 100)) return 0;
  if (!(year -= 100)) return 0;

  return 1;
}
