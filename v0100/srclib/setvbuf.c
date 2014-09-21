/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include <stdlib.h>
#include "istdio.h"

int setvbuf(FILE* f, char* buf, int mode, size_t size)
{
  if (!f || f->buf)
    return -1;
  if (mode != _IONBF && mode != _IOLBF && mode != _IOFBF)
    return -1;

  if (mode != _IONBF)
  {
    if (!size || size >= (unsigned)-1/2) // the buffer should be indexable by signed int (__fseek() needs it)
      return -1;
    if (!buf)
    {
      if (!(buf = malloc(size)))
        return -1;
    }
    else
    {
      f->flags |= _IOEXTBUF;
    }
    f->ptr = f->buf = buf;
    f->bufsz = size;
  }

  f->flags &= ~(_IONBF | _IOLBF | _IOFBF);
  f->flags |= mode;
  return 0;
}
