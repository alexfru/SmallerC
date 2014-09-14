/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include <stdlib.h>

#ifdef __SMALLER_C_32__
long atol(char* nptr)
{
  return atoi(nptr);
}
#endif
