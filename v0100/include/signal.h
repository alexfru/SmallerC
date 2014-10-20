/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#ifndef __SIGNAL_H
#define __SIGNAL_H

typedef int sig_atomic_t;

#define SIG_DFL ((void(*)(int))0)
#define SIG_ERR ((void(*)(int))1)
#define SIG_IGN ((void(*)(int))-1)

#define SIGABRT 1
#define SIGFPE  2
#define SIGILL  3
#define SIGINT  4
#define SIGSEGV 5
#define SIGTERM 6

void (*signal(int, void (*)(int)))(int);
int raise(int);

#endif
