/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
int __lngEq(unsigned short a[2], unsigned short b[2])
{
  return (*a == *b) && (a[1] == b[1]);
}
