/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include <stdlib.h>
#include <unistd.h>
#include "istdio.h"

int fclose(FILE* f)
{
  int res;

  if (!f)
    return EOF;

  res = fflush(f);
  if ((f->flags & _IOTERM) == 0) // don't close handles of stdin, stdout, stderr
  {
    if (close(f->fd) < 0)
      res = EOF;
  }

  // Delete if temporary
  if (f->flags & _IOREMOVE && f->name)
  {
    remove(f->name);
    free(f->name);
    f->name = NULL;
  }

  if (f->buf && f->buf != &f->c &&
      f->next && // don't free buffers of stdin, stdout, stderr
      !(f->flags & _IOEXTBUF)) // don't free buffers from set(v)buf()
  {
    free(f->buf);
    f->buf = NULL;
  }

  if (f->next) // don't free global FILEs of stdin, stdout, stderr
  {
    f->next->prev = f->prev;
    f->prev->next = f->next;
    free(f);
  }

  return res;
}
