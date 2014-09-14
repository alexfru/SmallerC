/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include <stdio.h>

char* fgets(char* s, int n, FILE* f)
{
  char* res = s;
  int c = 0;
  while (--n > 0 && (c = fgetc(f)) != EOF)
    if ((*s++ = c) == '\n')
      break;
  if (c == EOF && s == res)
    return NULL;
  *s = '\0';
  return res;
}
