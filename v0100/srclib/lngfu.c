/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#ifdef __SMALLER_C_16__
void __lngFromUnsigned(unsigned short l[2], unsigned n)
{
  l[0] = n;
  l[1] = 0;
}
#endif

#ifdef __SMALLER_C_32__
void __lngFromUnsigned(unsigned short l[2], unsigned n)
{
  union
  {
    unsigned short halves[2];
    unsigned n;
  } u;
  u.n = n;
  l[0] = u.halves[0];
  l[1] = u.halves[1];
}
#endif
