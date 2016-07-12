/*
  Copyright (c) 2014-2016, Alexey Frunze
  2-clause BSD license.
*/
#include <stdlib.h>
#include <stdio.h>

static char *_fxn, *_file, *_expr;
static int _line;

static void helper(unsigned expr)
{
  if (!expr)
  {
    fprintf(stderr, "Assertion \"%s\" failed!\nFunction: %s\nFile: %s, Line: %d\n",
            (_expr ? _expr : ""), _fxn, _file, _line);
    abort();
  }
}

void (*__assert(char* function, char* file, int line, char* expression))(unsigned)
{
  _fxn = function;
  _file = file;
  _expr = expression;
  _line = line;
  return &helper;
}
