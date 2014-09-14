/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include <unistd.h>

int remove(char* name)
{
  return unlink(name);
}
