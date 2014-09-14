/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#ifndef __TIME_H
#define __TIME_H

#ifndef NULL
#define NULL 0
#endif

#ifndef __SIZE_T_DEF
#define __SIZE_T_DEF
typedef unsigned size_t;
#endif

#ifdef __SMALLER_C_32__
#ifndef __TIME_T_DEF
#define __TIME_T_DEF
typedef unsigned long time_t;
#endif
#endif

#endif
