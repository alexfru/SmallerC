/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
char* strpbrk(char* s1, char* s2)
{
  int c, c2;
  while ((c = *s1++) != '\0')
  {
    char* p = s2;
    while ((c2 = *p++) != '\0')
      if (c2 == c)
        return s1 - 1;
  }
  return 0;
}
