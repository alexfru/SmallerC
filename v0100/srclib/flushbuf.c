/*
  Copyright (c) 2014-2018, Alexey Frunze
  2-clause BSD license.
*/
#include <stdlib.h>
#include "istdio.h"
#include <unistd.h>

// Flushes the stream data by invoking write() on f->fd and then stores the given
// character in the buffer.
// Must be called when f->cnt == 0, IOW, when there's no space in the buffer
// (f->buf) at f->ptr to write directly to.
// Returns EOF on error.
// Otherwise returns the given character.
int __flushbuf(int c, FILE* f)
{
  ssize_t written;

  if (f->flags & (_IORD | _IOSTRING)) // fail file write immediately after file read or on read-only files
    return EOF;
  f->flags |= _IOWR; // last operation was a write

  // Allocate a buffer if there isn't one yet or use the in-situ buffer
  if (!f->buf)
  {
    size_t size = BUFSIZ;
    if (!(f->flags & _IONBF) && (f->ptr = f->buf = malloc(size)) != NULL)
    {
      f->cnt = f->bufsz = size;
    }
    else
    {
      // Either the stream is unbuffered or malloc() failed.
      f->ptr = f->buf = &f->c;
      f->cnt = f->bufsz = 1;
      f->flags &= ~_IOLBF;
    }
  }

  if (f->ptr != f->buf) // if there's really anything in the buffer, flush
  {
    written = __write(f->fd, f->buf, f->bufsz); // TBD!!! review these writes/sizes
    if (written <= 0 || written != f->bufsz)
    {
      f->flags |= _IOERR;
      return EOF;
    }
  }
  f->cnt = f->bufsz;
  f->ptr = f->buf;

  f->cnt--;
  return *f->ptr++ = c;
}
