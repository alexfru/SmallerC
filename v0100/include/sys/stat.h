/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#ifndef __SYS_STAT_H
#define __SYS_STAT_H

#define S_IRUSR 0400
#define S_IRGRP 0040
#define S_IROTH 0004
#define S_IWUSR 0200
#define S_IWGRP 0020
#define S_IWOTH 0002
#define S_IXUSR 0100
#define S_IXGRP 0010
#define S_IXOTH 0001
#define S_IRWXU 0700
#define S_IRWXG 0070
#define S_IRWXO 0007

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

#ifdef __SMALLER_C_32__
#ifndef __TIME_T_DEF
#define __TIME_T_DEF
typedef unsigned long time_t;
#endif
#endif

#endif
