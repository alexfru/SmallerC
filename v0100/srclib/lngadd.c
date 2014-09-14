/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
void __lngAdd(unsigned short acc[2], unsigned short addend[2])
{
  acc[1] += addend[1] + (*addend > (unsigned short)-1 - *acc);
  *acc += *addend;
}
