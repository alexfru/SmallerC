/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#ifndef __STDBOOL_H
#define __STDBOOL_H

#ifdef __SMALLER_PP__
#define _Bool int
#define bool _Bool
#define true 1
#define false 0
#endif

#endif
