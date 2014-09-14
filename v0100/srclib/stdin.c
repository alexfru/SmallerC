/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include <unistd.h>
#include "istdio.h"

static FILE StdIn =
{
  0,
  0,
  STDIN_FILENO,
  _IORD | _IOTERM | _IOLBF
};

FILE* __stdin = &StdIn;
