/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
char* __strtoklast;

char* strtok(char* s, char* delims)
{
  char* p;
  int c, c2;
  char* res;

  if (!s && !(s = __strtoklast))
    return 0;

lskip_delims:
  c = *s++;
  p = delims;
  while ((c2 = *p++) != '\0')
    if (c2 == c)
      goto lskip_delims;

  if (c == '\0')
  {
    __strtoklast = 0;
    return 0;
  }
  res = s - 1;

  while ((c = *s++) != '\0')
  {
    p = delims;
    while ((c2 = *p++) != '\0')
      if (c2 == c)
      {
        s[-1] = '\0';
        __strtoklast = s;
        return res;
      }
  }

  __strtoklast = 0;
  return res;
}
