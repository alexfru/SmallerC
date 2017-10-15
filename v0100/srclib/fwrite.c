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

size_t fwrite(void* ptr, size_t esize, size_t ecount, FILE* f)
{
  size_t size = esize * ecount;
  unsigned char* p = ptr;

  if (!size)
    return 0;

  if (f->flags & (_IONBF | _IOLBF))
  {
    while (size)
    {
      if (fputc(*p++, f) == EOF)
        break;
      size--;
    }
  }
#ifndef UNIX_LIKE
  else if (f->flags & _IOBINARY)
#else
  else
#endif
  {
    while (size)
    {
      if (f->cnt < size)
      {
        if (f->cnt)
        {
          memcpy(f->ptr, p, f->cnt);
          p += f->cnt;
          size -= f->cnt;
          f->ptr += f->cnt;
          f->cnt = 0;
        }
        if (__flushbuf(*p, f) == EOF)
          break;
        *p++;
        size--;
      }

      if (f->cnt >= size)
      {
        memcpy(f->ptr, p, size);
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
      if (*p == '\n')
      {
        // insert '\r'
        if (f->cnt)
          *f->ptr++ = '\r', f->cnt--;
        else if (__flushbuf('\r', f) == EOF)
          break;
      }

      if (f->cnt)
        *f->ptr++ = *p, f->cnt--;
      else if (__flushbuf(*p, f) == EOF)
        break;

      p++, size--;
    }
  }
#endif

  return ecount - (size + esize - 1) / esize;
}
