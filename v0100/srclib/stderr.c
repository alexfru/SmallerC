/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include <unistd.h>
#include "istdio.h"

static FILE StdErr =
{
  0,
  0,
  STDERR_FILENO,
  _IOWR | _IOTERM | _IONBF
};

FILE* __stderr = &StdErr;
