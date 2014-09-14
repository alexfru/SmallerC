/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include <unistd.h>
#include "istdio.h"

static FILE StdOut =
{
  0,
  0,
  STDOUT_FILENO,
  _IOWR | _IOTERM | _IOLBF
};

FILE* __stdout = &StdOut;
