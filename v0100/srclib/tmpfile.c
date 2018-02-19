/*
  Copyright (c) 2014-2018, Alexey Frunze
  2-clause BSD license.
*/
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "istdio.h"

FILE* tmpfile(void)
{
  unsigned i;
  char* name = malloc(L_tmpnam);
  int fd = -1;
  FILE* f = malloc(sizeof(FILE));

  if (!name || !f)
  {
    goto err;
  }

  for (i = 0; i < TMP_MAX; i++)
  {
    if (!__tmpnam(name, 1))
      continue;

    if ((fd = __open(name, O_EXCL | O_CREAT | O_TRUNC | O_RDWR, 0666)) >= 0)
      break;
  }

  if (fd < 0)
  {
    goto err;
  }

  f->fd = fd;
  f->flags = _IORWOK | _IOBINARY | _IOREMOVE;

  f->ptr = f->buf = NULL;
  f->cnt = f->bufsz = 0;

  f->name = name;

  f->prev = __StreamsHead.prev;
  f->next = &__StreamsHead;
  f->next->prev = f;
  f->prev->next = f;

  __pFileCloser = &__FileCloser;

  return f;

err:

  if (name)
    free(name);

  if (f)
    free(f);

  return NULL;
}
