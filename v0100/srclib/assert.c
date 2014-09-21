/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include <stdlib.h>
#include <stdio.h>

static char *_fxn, *_file;
static int _line;

static void helper(unsigned expr)
{
  if (!expr)
  {
    fprintf(stderr, "Assertion failed!\nFunction: %s\nFile: %s, Line: %d\n", _fxn, _file, _line);
    abort();
  }
}

void (*__assert(char* function, char* file, int line))(unsigned)
{
  _fxn = function;
  _file = file;
  _line = line;
  return &helper;
}
