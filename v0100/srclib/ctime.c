/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include <time.h>

#ifdef __SMALLER_C_32__
char* ctime(time_t* t)
{
  return asctime(localtime(t));
}
#endif
