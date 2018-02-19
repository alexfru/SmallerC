/*
  Copyright (c) 2014-2018, Alexey Frunze
  2-clause BSD license.
*/
#include <unistd.h>
#include "istdio.h"
#include <errno.h>
#include <sys/lng.h>

int __ftell(FILE* f, fpos_t* pos)
{
  if (__lseekp(f->fd, pos, SEEK_CUR))
  {
//    errno = EUNKNOWN;
    return -1;
  }

  if (f->flags & _IORD) // read-only file or last was read
  {
    // underlying file's current position is after the last byte of data read,
    // so, there's f->cnt bytes from C file's position to underlying file's position
    // pos -= f->cnt;
    fpos_t t;
    __lngFromUnsigned(&t, f->cnt);
    __lngSub(pos, &t);
  }
  else if ((f->flags & _IOWR) && f->ptr != f->buf) // write-only file or last was write; there was no flush
  {
    // underlying file's current position is at the beginning of the buffer with unwritten data,
    // so, there's f->ptr - f->buf from underlying file's position to C file's position
    // pos += f->ptr - f->buf;
    fpos_t t;
    __lngFromUnsigned(&t, f->ptr - f->buf);
    __lngAdd(pos, &t);
  }

  return 0;
}
