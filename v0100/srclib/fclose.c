/*
  Copyright (c) 2014-2018, Alexey Frunze
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

  // close(f->fd), unless f is one of unreopened stdin, stdout, stderr
  // TBD??? Should I let go of stdin, stdout, stderr handles and close the underlying files???
  if ((f->flags & _IOTERM) == 0)
  {
    if (__close(f->fd) < 0)
      res = EOF;
    f->fd = -1;
  }

  // Delete if temporary
  if (f->flags & _IOREMOVE && f->name)
  {
    remove(f->name);
    free(f->name);
  }
  f->name = NULL;

  // Free buffers from set(v)buf()
  if (f->buf && f->buf != &f->c &&
      !(f->flags & _IOEXTBUF))
  {
    free(f->buf);
  }
  f->ptr = f->buf = NULL;
  f->cnt = f->bufsz = 0;

  f->flags = 0;

  // free(f), unless f is one of stdin, stdout, stderr,
  // which are needed around for freopen()
  if (f->next)
  {
    f->next->prev = f->prev;
    f->prev->next = f->next;
    free(f);
  }

  return res;
}
