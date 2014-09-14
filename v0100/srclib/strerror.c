/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include <string.h>

char* strerror(int errnum)
{
  char sn[1/*sign*/+10/*magnitude*/+1/*\0*/], *p = sn + sizeof sn;
  static char s[64];
  unsigned e = (errnum < 0) ? -(unsigned)errnum : errnum;

  *--p = '\0';
  do
  {
    *--p = '0' + e % 10;
    e /= 10;
  } while (e);
  if (errnum < 0)
    *--p = '-';

  strcpy(s, "Unknown error ");
  strcat(s, p);

  return s;
}
