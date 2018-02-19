/*
  Copyright (c) 2014-2018, Alexey Frunze
  2-clause BSD license.
*/
#include <unistd.h>

int remove(char* name)
{
  return __unlink(name);
}
