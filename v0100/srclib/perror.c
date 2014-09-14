/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include <errno.h>
#include <stdio.h>

void perror(char* s)
{
  if (s && *s)
    fprintf(stderr, "%s: Unknown error %d\n", s, errno);
  else
    fprintf(stderr, "Unknown error %d\n", errno);
}
