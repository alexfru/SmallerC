/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include <ctype.h>

int atoi(char* nptr)
{
  unsigned n = 0;
  int neg = 0, c;

  while (isspace((unsigned char)*nptr))
    nptr++;

  if (*nptr == '-')
    neg = 1, nptr++;
  else if (*nptr == '+')
    nptr++;

  while (isdigit(c = (unsigned char)*nptr))
  {
    if (n > (unsigned)-1 / 10)
      return 0;
    n *= 10;
    c -= '0';
    if (n > (unsigned)-1 - c)
      return 0;
    n += c;
    nptr++;
  }

  if (n > (unsigned)-1 / 2 + neg)
    return 0;

  if (neg)
    n = -n;

  return (int)n;
}
