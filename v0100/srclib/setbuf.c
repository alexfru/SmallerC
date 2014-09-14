/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include "istdio.h"

void setbuf(FILE* f, char* buf)
{
  setvbuf(f, buf, buf ? _IOFBF : _IONBF, BUFSIZ);
}
