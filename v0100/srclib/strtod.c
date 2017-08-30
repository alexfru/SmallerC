/*
  Copyright (c) 2017, Alexey Frunze
  2-clause BSD license.
*/
#ifdef __SMALLER_C_32__

#include <stdlib.h>

double strtod(char* nptr, char** endptr)
{
  return strtof(nptr, endptr);
}

#endif
