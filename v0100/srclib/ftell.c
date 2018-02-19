/*
  Copyright (c) 2014-2018, Alexey Frunze
  2-clause BSD license.
*/
#include <unistd.h>
#include "istdio.h"
#include <errno.h>

#ifdef __SMALLER_C_32__
long ftell(FILE* f)
{
  long pos = __lseek(f->fd, 0L, SEEK_CUR);
  if (pos == -1)
  {
//    errno = EUNKNOWN;
    return -1;
  }

  if (f->flags & _IORD) // read-only file or last was read
  {
    // underlying file's current position is after the last byte of data read,
    // so, there's f->cnt bytes from C file's position to underlying file's position
    pos -= f->cnt;
  }
  else if ((f->flags & _IOWR) && f->ptr != f->buf) // write-only file or last was write; there was no flush
  {
    // underlying file's current position is at the beginning of the buffer with unwritten data,
    // so, there's f->ptr - f->buf from underlying file's position to C file's position
    pos += f->ptr - f->buf;
  }

  return pos;
}
#endif
