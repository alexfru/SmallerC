/*
  Copyright (c) 2014-2017, Alexey Frunze
  2-clause BSD license.
*/
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "istdio.h"

#ifdef _LINUX
#define UNIX_LIKE
#endif
#ifdef _MACOS
#define UNIX_LIKE
#endif

size_t fread(void* ptr, size_t esize, size_t ecount, FILE* f)
{
  size_t size = esize * ecount;
  unsigned char* p = ptr;
  int c;

  if (!size)
    return 0;

#ifndef UNIX_LIKE
  if (f->flags & _IOBINARY)
#endif
  {
    while (size)
    {
      if (f->cnt < size)
      {
        if (f->cnt)
        {
          memcpy(p, f->ptr, f->cnt);
          p += f->cnt;
          size -= f->cnt;
          f->ptr += f->cnt;
          f->cnt = 0;
        }
        if ((c = __fillbuf(f)) == EOF)
          break;
        *p++ = c;
        size--;
      }

      if (f->cnt >= size)
      {
        memcpy(p, f->ptr, size);
        f->ptr += size;
        f->cnt -= size;
        return ecount;
      }
    }
  }
#ifndef UNIX_LIKE
  else
  {
    while (size)
    {
      if (f->cnt < size)
      {
        while (f->cnt)
        {
          if ((c = *f->ptr++) != '\r') // drop '\r'
            *p++ = c, size--;
          f->cnt--;
        }
        if ((c = __fillbuf(f)) == EOF)
          break;
        if (c != '\r') // drop '\r'
          *p++ = c, size--;
      }

      if (f->cnt >= size)
      {
        while (f->cnt && size)
        {
          if ((c = *f->ptr++) != '\r') // drop '\r'
            *p++ = c, size--;
          f->cnt--;
        }
      }
    }
  }
#endif

  return ecount - (size + esize - 1) / esize;
}
