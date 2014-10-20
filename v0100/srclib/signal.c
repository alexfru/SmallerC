/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include <signal.h>

void (*signal(int sig, void (*func)(int)))(int)
{
  // TBD???
//  errno = EUNKNOWN;
  return SIG_ERR;
}
