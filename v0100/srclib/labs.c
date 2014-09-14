/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#ifdef __SMALLER_C_32__
long labs(long n)
{
  return (n >= 0) ? n : -n;
}
#endif
