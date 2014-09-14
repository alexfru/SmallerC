/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
char* strncpy(char* s1, char* s2, unsigned n)
{
  char* res = s1;

  while (n)
  {
    n--;
    if ((*s1++ = *s2++) == '\0')
      break;
  }
  while (n--)
    *s1++ = '\0';

  return res;
}
