/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include "ictype.h"

int tolower(int c)
{
  return c + ((__chartype__[c + 1] & 0x10) << 1);
}
