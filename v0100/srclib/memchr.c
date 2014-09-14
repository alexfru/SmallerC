/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
char* memchr(char* s, int c, unsigned n)
{
  c = (char)c;

  while (n--)
  {
    if (*s == c)
      return s;
    s++;
  }

  return 0;
}
