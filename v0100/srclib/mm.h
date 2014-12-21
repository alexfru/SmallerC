/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#ifndef __MM_H
#define __MM_H

#ifdef __SMALLER_C_16__
extern char _stop_alldata__;
extern char _start_stack__;
#endif

#define HEADER_FOOTER_SZ (2*sizeof(unsigned))

extern unsigned __heap_start;
extern unsigned __heap_stop;

#endif
