/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#ifdef __SMALLER_C_16__
unsigned __lngToUnsigned(unsigned short l[2])
{
  return l[0];
}
#endif

#ifdef __SMALLER_C_32__
unsigned __lngToUnsigned(unsigned short l[2])
{
  union
  {
    unsigned short halves[2];
    unsigned n;
  } u;
  u.halves[0] = l[0];
  u.halves[1] = l[1];
  return u.n;
}
#endif
