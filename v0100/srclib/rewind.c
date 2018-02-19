/*
  Copyright (c) 2014-2018, Alexey Frunze
  2-clause BSD license.
*/
#include <unistd.h>
#include "istdio.h"

void rewind(FILE* f)
{
  fflush(f);

  if (f->flags & _IORWOK)
    f->flags &= ~(_IORD | _IOWR); // last operation for read-write files is neither

  f->flags &= ~(_IOUNGOT | _IOERR | _IOEOF); // ungetc()'s changes are gone

  f->ptr = f->buf;
  f->cnt = 0; // force entrance into __fillbuf()/__flushbuf() on the next read/write

  // "a+" mode isn't supported now because DOS doesn't support opening files in append mode directly.
  // "a" should ignore seek requests since it's always appending data at file's end and never reading anything.
  if (f->flags & _IOAPPEND)
    return;

#ifdef __SMALLER_C_16__
{
  fpos_t pos;
  pos.halves[1] = pos.halves[0] = 0;
  __lseekp(f->fd, &pos, SEEK_SET);
}
#else
  __lseek(f->fd, 0, SEEK_SET);
#endif
}
