/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "istdio.h"

FILE* freopen(char* name, char* mode, FILE* stream)
{
  FILE* f;
  int std;

  // TBD??? Support mode changes when name==NULL???
  if (!name || !stream)
    return NULL;

  // TBD??? Should open really happen after close as the standard says???
  if (!(f = fopen(name, mode)))
    return NULL;

  std = !stream->next; // stdin, stdout, stderr aren't chained

  // Prevent free(stream) in fclose(stream) by temporarily unchaining stream
  if (!std)
  {
    stream->next->prev = stream->prev;
    stream->prev->next = stream->next;
    stream->next = stream->prev = NULL;
  }

  fclose(stream);

  // Transplant *f to *stream
  *stream = *f;

  // Unchain and destroy f
  f->next->prev = f->prev;
  f->prev->next = f->next;
  free(f);

  if (std)
  {
    // stdin, stdout, stderr aren't chained
    stream->next = stream->prev = NULL;
  }
  else
  {
    // Chain stream
    stream->prev = __StreamsHead.prev;
    stream->next = &__StreamsHead;
    stream->next->prev = stream;
    stream->prev->next = stream;
  }

  return stream;
}
