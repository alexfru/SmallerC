/*
  Copyright (c) 2014-2018, Alexey Frunze
  2-clause BSD license.
*/
#include <stdlib.h>
#include "istdio.h"
#include <unistd.h>

// Fills the buffer (f->buf) with stream data by invoking read() on f->fd.
// Must be called when f->cnt == 0, IOW, when there's nothing to take
// directly from the buffer (f->buf) at f->ptr.
// Returns EOF on error or end of file.
// Otherwise returns the next available character from the buffer (properly
// advancing f->ptr and f->cnt) and this character must be consumed by the
// caller (or but back into the buffer at f->ptr-1, properly adjusting
// f->ptr and f->cnt).
int __fillbuf(FILE* f)
{
  ssize_t rread;

  if (f->flags & _IOWR) // fail file read immediately after file write or on write-only files
    return EOF;
  if (f->flags & (_IOEOF | _IOSTRING)) // EOF has been reached already
    return EOF;

  f->flags |= _IORD; // last operation was a read

  // Allocate a buffer if there isn't one yet or use the in-situ buffer
  if (!f->buf)
  {
    size_t size = BUFSIZ;
    if (!(f->flags & _IONBF) && ((f->buf = malloc(size)) != NULL))
    {
      f->bufsz = size;
    }
#ifdef _DOS
    else if (!(f->flags & _IONBF) && f == stdin && f->fd == STDIN_FILENO && (f->flags & _IOTERM))
    {
      // If DOS fxn 0x3f is called with 1-byte buffers, it does not
      // append '\n' after '\r' (the Enter key generates '\r').
      // But we do want to receive '\n' (and ignore '\r') even
      // if malloc() fails.
      // Use a small static buffer in this case.
      static unsigned char stdinbuf[130];
      f->buf = stdinbuf;
      f->bufsz = sizeof stdinbuf;
      f->flags |= _IOEXTBUF; // don't free this buffer on close
    }
#endif
    else
    {
      // Either the stream is unbuffered or malloc() failed.
      f->buf = &f->c;
      f->bufsz = 1;
      f->flags &= ~_IOLBF;
    }
  }

  // In case we're about to read from stdin and there's still something
  // in stdout and stderr buffers, flush them to avoid surprises.
  if (f == stdin)
  {
    if (stdout->flags & _IOLBF)
      fflush(stdout);
    if (stderr->flags & _IOLBF)
      fflush(stderr);
  }

  f->flags &= ~_IOUNGOT; // ungetc()'s changes are gone

  f->ptr = f->buf;

  if ((rread = __read(f->fd, f->buf, f->bufsz)) <= 0)
  {
    if (!rread)
      f->flags |= _IOEOF; // if simply read 0 bytes
    else
      f->flags |= _IOERR; // if got an error
    f->cnt = 0;
    return EOF;
  }

  f->cnt = rread - 1;
  return *f->ptr++;
}
