/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
int __lngLessThan0(unsigned short l[2])
{
  return l[1] > (unsigned short)-1 / 2;
}
