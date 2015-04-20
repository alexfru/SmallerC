/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#ifndef __STDARG_H
#define __STDARG_H

typedef char* va_list;

#ifdef __SMALLER_PP__
#define va_start(vl, last)      { (vl) = (char*)&(last) + ((sizeof(last) + sizeof(int) - 1) & -sizeof(int)); }
#define va_arg(vl, type)        (*(type*)(((vl) += ((sizeof(type) + sizeof(int) - 1) & -sizeof(int))) - ((sizeof(type) + sizeof(int) - 1) & -sizeof(int))))
#define va_end(vl)
#endif

#endif
