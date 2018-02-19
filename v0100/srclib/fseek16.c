/*
  Copyright (c) 2014-2018, Alexey Frunze
  2-clause BSD license.
*/
#include <unistd.h>
#include "istdio.h"
#include <sys/lng.h>

int __fseek(FILE* f, fpos_t* offset, int whence)
{
  fpos_t pos;

  f->flags &= ~_IOEOF;

  // Don't invalidate the buffer for read-only files, whenever possible,
  // so as to reduce I/O and speed up seeking
  if ((f->flags & (_IORWOK | _IORD | _IOUNGOT)) == _IORD && // read-only file, unaffected by ungetc()
      whence != SEEK_END && // we need to know file size for SEEK_END, but we don't
      f->buf)
  {
    if (whence == SEEK_CUR)
    {
/*
      if (offset >= 0 && offset <= f->cnt ||
          offset < 0 && offset >= f->buf - f->ptr) // equivalent to: offset < 0 && -offset <= f->ptr - f->buf
      {
        f->ptr += offset;
        f->cnt -= offset;
        return 0;
      }
*/
      fpos_t t;
      int ltz = __lngLessThan0(offset);
      if (!ltz && (__lngFromUnsigned(&t, f->cnt), !__lngUnsignedLess(&t, offset)) ||
          ltz && (__lngFromSigned(&t, f->buf - f->ptr), !__lngSignedLess(offset, &t)))
      {
        int t = __lngToSigned(offset);
        f->ptr += t;
        f->cnt -= t;
        return 0;
      }
    }
    else // if (whence == SEEK_SET)
    {
      fpos_t dist, t;
      int cond;
      if (__ftell(f, &pos))
      {
        return -1;
      }
/*
      if (offset >= pos && (offset - pos) <= f->cnt ||
          offset >= 0 && offset < pos && (pos - offset) <= f->ptr - f->buf)
      {
        f->ptr += offset - pos;
        f->cnt -= offset - pos;
        return 0;
      }
*/
      cond = !__lngSignedLess(offset, &pos) &&
             (dist = *offset, __lngSub(&dist, &pos), __lngFromUnsigned(&t, f->cnt), !__lngUnsignedLess(&t, &dist));
      if (!cond)
        cond = !__lngLessThan0(offset) && __lngSignedLess(offset, &pos) &&
               (dist = pos, __lngSub(&dist, offset), __lngFromUnsigned(&t, f->ptr - f->buf), !__lngUnsignedLess(&t, &dist));
      if (cond)
      {
        int t;
        dist = *offset;
        __lngSub(&dist, &pos);
        t = __lngToSigned(&dist);
        f->ptr += t;
        f->cnt -= t;
        return 0;
      }
    }
  }

  if (fflush(f))
  {
    return -1;
  }

  if (f->flags & _IORWOK)
    f->flags &= ~(_IORD | _IOWR); // last operation for read-write files is neither
  f->flags &= ~_IOUNGOT; // ungetc()'s changes are gone
  f->ptr = f->buf;
  f->cnt = 0; // force entrance into __fillbuf()/__flushbuf() on the next read/write

  // "a+" mode isn't supported now because DOS doesn't support opening files in append mode directly.
  // "a" should ignore seek requests since it's always appending data at file's end and never reading anything.
  if (f->flags & _IOAPPEND)
    return 0;

  pos = *offset; // preserve the position parameter
  if (__lseekp(f->fd, &pos, whence))
  {
    return -1;
  }

  return 0;
}
