/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
unsigned strspn(char* s1, char* s2)
{
  char *s = s1, *p;
  int c, c2;

lskip:
  c = *s1++;
  p = s2;
  while ((c2 = *p++) != '\0')
    if (c2 == c)
      goto lskip;

  return s1 - 1 - s;
}
