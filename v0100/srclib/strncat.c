/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
char* strncat(char* s1, char* s2, unsigned n)
{
  char* res = s1;
  int c;

  while (*s1 != '\0')
    s1++;

  while (n)
  {
    if ((c = *s2++) == '\0')
      break;
    *s1++ = c;
    n--;
  }
  *s1 = '\0';

  return res;
}
