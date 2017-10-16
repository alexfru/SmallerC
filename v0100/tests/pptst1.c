/*
  This is a demo of using gcc as a preprocessor for Smaller C.

  How to compile for DOS (all mode(l)s: tiny/.COM, small/.EXE, huge/.EXE, unreal/.EXE, 32-bit DPMI/.EXE):
    smlrcc -ppg -dost pptst1.c -o pptst1dt.com
    smlrcc -ppg -doss pptst1.c -o pptst1ds.exe
    smlrcc -ppg -dosh pptst1.c -o pptst1dh.exe
    smlrcc -ppg -dosu pptst1.c -o pptst1du.exe
    smlrcc -ppg -dosp pptst1.c -o pptst1dp.exe

  How to compile for Windows:
    smlrcc -ppg -win pptst1.c -o pptst1w.exe

  How to compile for Linux:
    smlrcc -ppg -linux pptst1.c -o pptst1l

  How to compile for MacOS:
    smlrcc -ppg -macos pptst1.c -o pptst1m
*/

#include <stddef.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <sys/types.h>

#ifdef __SMALLER_PP__

#define DOUBLE(x) ((x)*2)

#define DECL_AND_INIT_CHAR_ARR(NAME) \
  char NAME[] = #NAME

DECL_AND_INIT_CHAR_ARR(CharArr);

#ifdef __SMALLER_C_32__
time_t timet;
#endif

struct stru
{
  char a, b, c, d;
};

void printv(char* fmt, ...)
{
  va_list vl;
  va_start(vl, fmt);

  while (*fmt)
  {
    switch (*fmt)
    {
    case 'c':
      printf("char: '%c'\n", va_arg(vl, int));
      break;
    case 'd':
    case 'i':
      printf("int: %d\n", va_arg(vl, int));
      break;
    case 's':
      printf("char*: \"%s\"\n", va_arg(vl, char*));
      break;
    }
    fmt++;
  }

  va_end(vl);
}

int main(void)
{
  printf("CHAR_MAX: %d\n", CHAR_MAX);
  printf("DOUBLE(123): %d\n", DOUBLE(123));
  printf("offsetof(struct stru, d): %u\n", offsetof(struct stru, d));
#if defined(DEF)
  printf("defined(DEF): %d\n", 1);
  printf("DEF: %d\n", DEF);
#endif
  printv("sci", "Str", 'a', 123);
  printf("char CharArr[] = \"%s\";\n", CharArr);
}

#else

int main(void)
{
  printf("No external preprocessor!\n");
}

#endif
