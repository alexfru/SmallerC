/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include "istdio.h"

void __FileCloser(void)
{
  for (;;)
  {
    FILE* f = __StreamsHead.next;
    if (f == &__StreamsHead)
      break;
    fclose(f);
  }
}
