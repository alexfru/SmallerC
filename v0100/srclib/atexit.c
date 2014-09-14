/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
extern void (*__pAtExitIterator)(void);

static void (*functions[32])(void);
static int fcnt;

static
void iterator(void)
{
  while (fcnt)
    functions[--fcnt]();
}

int atexit(void (*func)(void))
{
  if (fcnt >= 32)
    return -1;
  functions[fcnt++] = func;
  __pAtExitIterator = &iterator;
  return 0;
}
