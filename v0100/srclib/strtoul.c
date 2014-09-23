/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include <ctype.h>
#include <errno.h>

#ifdef __SMALLER_C_32__
unsigned long strtoul(char* nptr, char** endptr, int base)
{
  char* nptr0 = nptr;
  unsigned long n = 0;
  int neg = 0, hexpfx = 0, toobig = 0, c;
  unsigned cnt = 0;
  unsigned long preMulMax;

  while (isspace((unsigned char)*nptr))
    nptr++;

  if (*nptr == '-')
    neg = 1, nptr++;
  else if (*nptr == '+')
    nptr++;

  if ((base == 0 || base == 16) &&
      *nptr == '0' &&
      (nptr[1] == 'x' || nptr[1] == 'X'))
  {
    base = 16;
    nptr += 2;
    hexpfx = 1;
  }
  if (base == 0)
  {
    base = (*nptr == '0') ? 8 : 10;
  }

  preMulMax = (unsigned long)-1 / base;

  while ((c = (unsigned char)*nptr) != '\0')
  {
    if (isdigit(c))
      c -= '0';
    else if (isalpha(c))
      c = (c & ~0x20) - ('A' - 10);
    else
      break;
    if (c >= base)
      break;

    if (n > preMulMax)
      toobig = 1;
    n *= base;

    if (n > (unsigned long)-1 - c)
      toobig = 1;
    n += c;

    cnt++;
    nptr++;
  }

  if (neg)
    n = -n;

  if (toobig)
  {
    n = (unsigned long)-1;
    errno = ERANGE;
  }

  if (endptr)
  {
    if (!cnt && hexpfx)
      cnt = 1, nptr--; // move the position from after [+-]0x to after [+-]0
    *endptr = cnt ? nptr : nptr0;
  }

  return n;
}
#endif
