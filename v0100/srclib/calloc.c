/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include <stdlib.h>
#include <string.h>

void* calloc(size_t ecnt, size_t esize)
{
  size_t size = ecnt * esize;
  void* p;
  if (!size || size / esize != ecnt)
    return NULL;
  p = malloc(size);
  if (p)
    memset(p, 0, size);
  return p;
}
