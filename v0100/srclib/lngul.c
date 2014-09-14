/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
int __lngUnsignedLess(unsigned short a[2], unsigned short b[2])
{
  return (a[1] < b[1]) ||
         ((a[1] == b[1]) && (*a < *b));
}
