/*
  Copyright (c) 2014-2018, Alexey Frunze
  2-clause BSD license.
*/
#include "istdio.h"
#include <unistd.h>

static int fflush1(FILE* f)
{
  if (f->flags & _IOWR) // if last operation was write or if it's a write-only file
  {
    if (f->ptr != f->buf) // if there's anything in the buffer, flush
    {
      size_t sz = f->bufsz - f->cnt;
      ssize_t written = __write(f->fd, f->buf, sz); // TBD!!! review these writes/sizes
      if (written <= 0 || written != sz)
      {
        f->flags |= _IOERR;
        return EOF;
      }
    }
    f->ptr = f->buf; // tell __flushbuf() that flush isn't needed, it has just been done
    f->cnt = 0; // force entrance into __fillbuf()/__flushbuf() on the next read/write
    if (f->flags & _IORWOK)
      f->flags &= ~_IOWR; // last operation for read-write files is neither read nor write and can now be set to either
  }
  return 0;
}

int fflush(FILE* f)
{
  int res = 0;

  if (f)
    return fflush1(f);

  for (f = __StreamsHead.next; f != &__StreamsHead; f = f->next)
    if (fflush1(f))
      res = EOF;

  if (fflush1(stdin))
    res = EOF;
  if (fflush1(stdout))
    res = EOF;
  if (fflush1(stderr))
    res = EOF;

  return res;
}
