/*
  Copyright (c) 2014-2018, Alexey Frunze
  2-clause BSD license.
*/
#include <fcntl.h>

int __creat(char* name, mode_t mode)
{
  return __open(name, O_WRONLY | O_CREAT | O_TRUNC, mode);
}
