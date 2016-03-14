/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
int memcmp(void* s1, void* s2, unsigned n)
{
  if (n)
  {
    unsigned char *p1 = s1, *p2 = s2;
    do
    {
      if (*p1++ != *p2++)
        return (*--p1 - *--p2);
    } while (--n);
  }
  return 0;
}
