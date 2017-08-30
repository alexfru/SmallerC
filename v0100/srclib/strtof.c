/*
  Copyright (c) 2017, Alexey Frunze
  2-clause BSD license.
*/
#ifdef __SMALLER_C_32__

#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#include "ifp.h"

static int match(char* s, char* upattern)
{
  int c1, c2;
  do
  {
    c1 = toupper((unsigned char)*s++);
    c2 = *upattern++;
    if (c1 != c2)
      return c2 ? 0 : 1;
  } while (c1);
  return 1;
}

float strtof(char* nptr, char** endptr)
{
  char* nptr0 = nptr;
  int neg = 0;
  float val = 0;

  while (isspace((unsigned char)*nptr))
    nptr++;

  if (*nptr == '-')
    neg = 1, nptr++;
  else if (*nptr == '+')
    nptr++;

  if (match(nptr, "NAN"))
  {
    val = NAN;
    nptr += 3;
  }
  else if (match(nptr, "INF"))
  {
    val = INFINITY;
    nptr += 3;
    if (match(nptr, "INITY"))
      nptr += 5;
  }
  else
  {
    unsigned char digits[MAX_FP_DIGITS];
    int mcnt = 0, mexp = 0;
    int gotint = 0, gotfrct = 0;
    int esign = 0;
    unsigned eexp = 0;
    int e;
    int c;
    while (*nptr == '0')
    {
      gotint = 1; // got integral part digits: all zeroes so far
      nptr++;
    }
    while (isdigit(c = (unsigned char)*nptr))
    {
      gotint = 2; // got integral part digits: non-zero
      if (mcnt < MAX_FP_DIGITS)
        digits[mcnt++] = c - '0';
      else
        mexp++; // TBD??? overflow
      nptr++;
    }
    if (*nptr == '.')
    {
      nptr++;
      if (gotint < 2)
        while (*nptr == '0')
        {
          gotfrct = 1; // got fractional part digits: all zeroes so far
          mexp--; // TBD??? overflow
          nptr++;
        }
      while (isdigit(c = (unsigned char)*nptr))
      {
        gotfrct = 2; // got fractional part digits: non-zero
        if (mcnt < MAX_FP_DIGITS)
          digits[mcnt++] = c - '0';
        mexp--; // TBD??? overflow
        nptr++;
      }
    }
    if ((gotint | gotfrct) == 0)
    {
      nptr = nptr0;
      goto lend;
    }
    if (*nptr == 'E' || *nptr == 'e')
    {
      char* nptr1 = nptr++;
      int gotexp = 0;
      if (*nptr == '-')
        esign = '-', nptr++;
      else if (*nptr == '+')
        nptr++;
      while (isdigit(c = (unsigned char)*nptr))
      {
        int d = c - '0';
        unsigned ex10 = eexp * 10;
        gotexp = 2; // got e/E and exponent part digits
        if (ex10 / 10 != eexp ||
            ex10 + d < ex10 ||
            ex10 + d > (unsigned)-1 / 2)
        {
          nptr = nptr0;
          goto lend;
        }
        eexp = ex10 + d;
        nptr++;
      }
      if (!gotexp)
        nptr = nptr1;
    }

    e = (esign == '-') ? -(int)eexp : (int)eexp;
    // drop trailing zeroes, if any
    while (mcnt && !digits[mcnt - 1])
    {
      mcnt--;
      mexp++; // TBD??? overflow
    }
    if (!mcnt)
      mexp = digits[mcnt++] = 0;

    if (mexp >= 0 && e > INT_MAX - mexp)
      mexp = INT_MAX;
    else if (mexp < 0 && e < INT_MIN - mexp)
      mexp = INT_MIN;
    else
      mexp += e;
    eexp = __cvtfd(digits, mcnt, mexp);
    memcpy(&val, &eexp, sizeof val);
    if (val == INFINITY)
      errno = ERANGE;
  }

  if (neg)
    val = -val;

lend:

  if (endptr)
    *endptr = nptr;

  return val;
}

#endif
