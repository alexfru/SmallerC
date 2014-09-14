/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include "ictype.h"

int toupper(int c)
{
  return c - (__chartype__[c + 1] & 0x20);
}
