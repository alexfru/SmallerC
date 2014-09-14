/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include <stdio.h>

char* gets(char* s)
{
  char* res = s;
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    *s++ = c;
  if (c == EOF && s == res)
    return NULL;
  *s = '\0';
  return res;
}
