/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#ifndef __ITIME_H
#define __ITIME_H

#include <time.h>

#define SECONDS_PER_MINUTE 60
#define SECONDS_PER_HOUR   (60*SECONDS_PER_MINUTE)
#define SECONDS_PER_DAY    (24UL*SECONDS_PER_HOUR)
#define SECONDS_PER_YEAR   (365UL*SECONDS_PER_DAY)

extern unsigned short __DaysSinceJan1st[2][13];
int __isleap(unsigned);

#ifdef __SMALLER_C_32__
time_t __buildtime(struct tm*);
struct tm* __breaktime(time_t*);
#endif

#endif
