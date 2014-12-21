/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#ifndef __SYS_TYPES_H
#define __SYS_TYPES_H

#ifndef __MODE_T_DEF
#define __MODE_T_DEF
typedef int mode_t;
#endif

#ifdef __SMALLER_C_32__
#ifndef __OFF_T_DEF
#define __OFF_T_DEF
typedef long off_t;
#endif
#endif

#ifndef __FPOS_T_DEF
#define __FPOS_T_DEF
typedef struct
{
  unsigned short halves[2];
} fpos_t;
#endif

#ifndef __SIZE_T_DEF
#define __SIZE_T_DEF
typedef unsigned size_t;
#endif

#ifndef __SSIZE_T_DEF
#define __SSIZE_T_DEF
typedef int ssize_t;
#endif

#ifdef __SMALLER_C_32__
#ifndef __TIME_T_DEF
#define __TIME_T_DEF
typedef unsigned long time_t;
#endif
#endif

#ifndef __PID_T_DEF
#define __PID_T_DEF
typedef int pid_t;
#endif

#endif
