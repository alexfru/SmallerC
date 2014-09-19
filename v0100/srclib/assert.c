/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include <stdlib.h>
#include <stdio.h>

static char* msg;

static void helper(unsigned expr)
{
  if (!expr)
  {
    fprintf(stderr, "%s: Assertion failed.\n", msg);
    abort();
  }
}

void (*__assert(char* function))(unsigned)
{
  msg = function;
  return &helper;
}
