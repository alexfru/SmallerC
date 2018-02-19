/*
  Copyright (c) 2014-2018, Alexey Frunze
  2-clause BSD license.
*/
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "istdio.h"

FILE* fopen(char* name, char* mode)
{
  FILE* f = NULL;
  int fd = -1;
  int update;
  int binary;
  int oflags;

  if (!name || !mode || !*mode)
  {
    goto err;
  }

  if (!(f = malloc(sizeof(FILE))))
  {
    goto err;
  }

  update = (mode[1] == '+') || (mode[1] && mode[2] == '+');
  binary = (mode[1] == 'b') || (mode[1] && mode[2] == 'b');

  switch (*mode)
  {
  case 'r':
    oflags = update ? O_RDWR : O_RDONLY;
    break;
  case 'w':
    oflags = O_CREAT | O_TRUNC | (update ? O_RDWR : O_WRONLY);
    break;
  case 'a':
    if (update)
    {
      // For now disallow "a+" (reads and writes) as it complicates things
      // and there's no direct support for append mode in DOS.
      // Allow only "a" (writes only) for now.
      goto err;
    }
    oflags = O_CREAT | O_APPEND | (update ? O_RDWR : O_WRONLY);
    break;
  default:
    goto err;
  }

  if ((fd = __open(name, oflags, 0666)) < 0)
  {
    goto err;
  }

  f->fd = fd;

  if (update)
    f->flags = _IORWOK;
  else if (*mode == 'r')
    f->flags = _IORD;
  else
    f->flags = _IOWR;

  if (binary)
    f->flags |= _IOBINARY;
  
  if (*mode == 'a')
    f->flags |= _IOAPPEND;

  f->ptr = f->buf = NULL;
  f->cnt = f->bufsz = 0;

  f->name = NULL;

  f->prev = __StreamsHead.prev;
  f->next = &__StreamsHead;
  f->next->prev = f;
  f->prev->next = f;

  __pFileCloser = &__FileCloser;

  return f;

err:

  if (f)
    free(f);

  return NULL;
}
