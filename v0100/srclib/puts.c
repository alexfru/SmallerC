/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include <stdio.h>

int puts(char* s)
{
  int c;
  while ((c = *s++) != '\0')
    putchar(c);
  return putchar('\n');
}
