/*
  Copyright (c) 2014-2018, Alexey Frunze
  2-clause BSD license.
*/
#ifndef __UNISTD_H
#define __UNISTD_H

#ifndef NULL
#define NULL 0
#endif

#ifndef __SIZE_T_DEF
#define __SIZE_T_DEF
typedef unsigned size_t;
#endif

#ifndef __SSIZE_T_DEF
#define __SSIZE_T_DEF
typedef int ssize_t;
#endif

#ifndef __INTPTR_T_DEF
#define __INTPTR_T_DEF
typedef int intptr_t;
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

#ifndef SEEK_SET
#define SEEK_SET 0
#endif
#ifndef SEEK_CUR
#define SEEK_CUR 1
#endif
#ifndef SEEK_END
#define SEEK_END 2
#endif

#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

int __close(int);
int close(int);
#ifdef __SMALLER_C_32__
off_t __lseek(int, off_t, int);
off_t lseek(int, off_t, int);
#endif
int/*0 on success,-1 on failure*/ __lseekp(int/*file handle*/, fpos_t*/*position in/out*/, int/*whence*/);
ssize_t __read(int, void*, size_t);
ssize_t read(int, void*, size_t);
ssize_t __write(int, void*, size_t);
ssize_t write(int, void*, size_t);
int __unlink(char*);
int unlink(char*);
int __isatty(int);
int isatty(int);

#endif
