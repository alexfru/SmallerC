/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include <fcntl.h>

int creat(char* name, mode_t mode)
{
  return open(name, O_WRONLY | O_CREAT | O_TRUNC, mode);
}
