/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
char* strrchr(char* s, int c)
{
  char* res = 0;
  c = (char)c;
  while (*s)
  {
    if (*s == c)
      res = s;
    s++;
  }
  if (!c)
    res = s;
  return res;
}
