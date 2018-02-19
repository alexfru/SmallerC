/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#ifndef __STDIO_H
#define __STDIO_H

#include <stdarg.h>

#ifndef NULL
#define NULL 0
#endif

#ifndef __SIZE_T_DEF
#define __SIZE_T_DEF
typedef unsigned size_t;
#endif

#define EOF (-1)

#ifndef SEEK_SET
#define SEEK_SET 0
#endif
#ifndef SEEK_CUR
#define SEEK_CUR 1
#endif
#ifndef SEEK_END
#define SEEK_END 2
#endif

#ifndef __FPOS_T_DEF
#define __FPOS_T_DEF
typedef struct
{
  unsigned short halves[2];
} fpos_t;
#endif

typedef struct __stream FILE;

extern FILE *__stdin, *__stdout, *__stderr;
#define stdin  __stdin
#define stdout __stdout
#define stderr __stderr

#define _IOFBF 01
#define _IONBF 02
#define _IOLBF 04

#define BUFSIZ 1024

#ifdef _DOS
#define FOPEN_MAX 20
#define FILENAME_MAX 80
#define L_tmpnam 80
#define TMP_MAX 10000
#endif

#ifdef _WINDOWS
#define FOPEN_MAX 20
#define FILENAME_MAX 260
#define L_tmpnam 260
#define TMP_MAX 10000
#endif

#ifdef _LINUX
#define FOPEN_MAX 20
#define FILENAME_MAX 4096
#define L_tmpnam 20
#define TMP_MAX 10000
#endif

#ifdef _MACOS
#define FOPEN_MAX 20
#define FILENAME_MAX 4096
#define L_tmpnam 20
#define TMP_MAX 10000
#endif

FILE* fopen(char*, char*);
FILE* freopen(char*, char*, FILE*);
int fflush(FILE*);
int fclose(FILE*);
int remove(char*);
int rename(char*, char*);
size_t fread(void*, size_t, size_t, FILE*);
int fgetc(FILE*);
int getc(FILE*);
int getchar(void);
char* fgets(char*, int, FILE*);
char* gets(char*);
int ungetc(int, FILE*);
size_t fwrite(void*, size_t, size_t, FILE*);
int fputc(int, FILE*);
int putc(int, FILE*);
int putchar(int);
int fputs(char*, FILE*);
int puts(char*);
void perror(char*);
#ifdef __SMALLER_C_32__
long ftell(FILE*);
int fseek(FILE*, long, int);
#endif
int/*0 on success,-1 on failure*/ __ftell(FILE*, fpos_t*/*position out*/);
int __fseek(FILE*, fpos_t*/*position in*/, int/*whence*/);
void rewind(FILE*);
int fgetpos(FILE*, fpos_t*);
int fsetpos(FILE*, fpos_t*);
void clearerr(FILE*);
int ferror(FILE*);
int feof(FILE*);
int setvbuf(FILE*, char*, int, size_t);
void setbuf(FILE*, char*);
int __fileno(FILE*);
int fileno(FILE*);
char* tmpnam(char*);
FILE* tmpfile(void);

int vfprintf(FILE*, char*, va_list);
int fprintf(FILE*, char*, ...);
int vprintf(char*, va_list);
int printf(char*, ...);
int vsprintf(char*, char*, va_list);
int sprintf(char*, char*, ...);
int vsnprintf(char*, size_t, char*, va_list);
int snprintf(char*, size_t, char*, ...);

int vfscanf(FILE*, char*, va_list);
int fscanf(FILE*, char*, ...);
int vscanf(char*, va_list);
int scanf(char*, ...);
int vsscanf(char*, char*, va_list);
int sscanf(char*, char*, ...);

#endif
