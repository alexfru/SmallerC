/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include <stdio.h>

int fputs(char* s, FILE* f)
{
  int c, r = 0;
  while ((c = *s++) != '\0')
    r |= fputc(c, f);
  return r;
}
