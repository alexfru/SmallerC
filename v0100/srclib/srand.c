/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#ifdef __SMALLER_C_32__
extern unsigned __Seed;

void srand(unsigned seed)
{
  __Seed = seed;
}
#endif

#ifdef __SMALLER_C_16__
extern unsigned short __Seed[2];

void srand(unsigned seed)
{
  __Seed[0] = seed;
  __Seed[1] = 0;
}
#endif
