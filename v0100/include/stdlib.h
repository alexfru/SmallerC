/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#ifndef __STDLIB_H
#define __STDLIB_H

#ifndef NULL
#define NULL 0
#endif

#ifndef __SIZE_T_DEF
#define __SIZE_T_DEF
typedef unsigned size_t;
#endif

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

void abort(void);
void _Exit(int);
void exit(int);
int atexit(void (*)(void));

void* malloc(size_t);
void* calloc(size_t, size_t);
void free(void*);
void* realloc(void*, size_t);

int abs(int);
#ifdef __SMALLER_C_32__
long labs(long);
#endif

typedef struct { int quot, rem; } div_t;
div_t div(int, int);
#ifdef __SMALLER_C_32__
typedef struct { long quot, rem; } ldiv_t;
ldiv_t ldiv(long, long);
#endif

int atoi(char*);
#ifdef __SMALLER_C_32__
long atol(char*);
long strtol(char*, char**, int);
unsigned long strtoul(char*, char**, int);
#endif

#define RAND_MAX 32767
int rand(void);
void srand(unsigned);

void* bsearch(void*, void*, size_t, size_t, int (*)(void*, void*));
void qsort(void*, size_t, size_t, int (*)(void*, void*));

char* getenv(char*);
int system(char*);

#endif
