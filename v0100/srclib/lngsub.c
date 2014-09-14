/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
void __lngSub(unsigned short acc[2], unsigned short subtrahend[2])
{
  acc[1] -= subtrahend[1] + (*acc < *subtrahend);
  *acc -= *subtrahend;
}
