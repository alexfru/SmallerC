/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
int __lngSignedLess(unsigned short a[2], unsigned short b[2])
{
  if (a[1] > (unsigned short)-1/2) // a < 0
  {
    if (b[1] <= (unsigned short)-1/2) // b >= 0
      return 1;
  }
  else // a >= 0
  {
    if (b[1] > (unsigned short)-1/2) // b < 0
      return 0;
  }
  // (a < 0 && b < 0) || (a >= 0 && b >= 0)
  return (a[1] < b[1]) ||
         ((a[1] == b[1]) && (*a < *b));
}
