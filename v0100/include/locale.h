/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#ifndef __LOCALE_H
#define __LOCALE_H

#ifndef NULL
#define NULL 0
#endif

struct lconv
{
  char* decimal_point;
  char* thousands_sep;
  char* grouping;
  char* mon_decimal_point;
  char* mon_thousands_sep;
  char* mon_grouping;
  char* positive_sign;
  char* negative_sign;
  char* currency_symbol;
  char  frac_digits;
  char  p_cs_precedes;
  char  n_cs_precedes;
  char  p_sep_by_space;
  char  n_sep_by_space;
  char  p_sign_posn;
  char  n_sign_posn;
  char* int_curr_symbol;
  char  int_frac_digits;
  char  int_p_cs_precedes;
  char  int_n_cs_precedes;
  char  int_p_sep_by_space;
  char  int_n_sep_by_space;
  char  int_p_sign_posn;
  char  int_n_sign_posn;
};

#define LC_ALL      0
#define LC_COLLATE  1
#define LC_CTYPE    2
#define LC_MONETARY 3
#define LC_NUMERIC  4
#define LC_TIME     5

char* setlocale(int, char*);
struct lconv* localeconv(void);

#endif
