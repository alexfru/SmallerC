/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
unsigned strcspn(char* s1, char* s2)
{
  char *s = s1, *p;
  int c, c2;

  for (;;)
  {
    c = *s1++;
    p = s2;
    do
    {
      if ((c2 = *p++) == c)
        return s1 - 1 - s;
    } while (c2);
  }
}
