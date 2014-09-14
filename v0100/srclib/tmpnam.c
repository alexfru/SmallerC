/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include <stdio.h>

#ifdef _DOS

static unsigned num;

char* tmpnam(char* buf)
{
  // TBD!!! redo the function
  char sn[1/*sign*/+10/*magnitude*/+1/*\0*/], *p = sn + sizeof sn;
  static char s[13];
  unsigned n = num;

  if (buf)
    return NULL; // TBD!!!

  *--p = '\0';
  do
  {
    *--p = '0' + n % 10;
    n /= 10;
  } while (n);

  num = (num + 1) % 10000;

  strcpy(s, "_$");
  strcat(s, p);
  strcat(s, "$_.T$_");

  return s;
}

#endif
