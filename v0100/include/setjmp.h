/*
  Copyright (c) 2014-2016, Alexey Frunze
  2-clause BSD license.
*/
#ifndef __SETJMP_H
#define __SETJMP_H

typedef struct
{
  unsigned xip;    // ip / cs:ip / eip
  unsigned xflags; // (e)flags
  unsigned xbp;    // (e)bp
  unsigned xsp;    // (e)sp
} jmp_buf[1];

int setjmp(jmp_buf);
void longjmp(jmp_buf, int);

#endif
