/*
  Copyright (c) 2017, Alexey Frunze
  2-clause BSD license.
*/
#ifdef __SMALLER_C_32__

#include <stdlib.h>

double atof(char* nptr)
{
  return strtod(nptr, NULL);
}

#endif
