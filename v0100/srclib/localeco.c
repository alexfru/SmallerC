/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include <locale.h>
#include <limits.h>

static char empty[] = "";

static struct lconv lc =
{
  ".",
  empty,
  empty,
  empty,
  empty,
  empty,
  empty,
  empty,
  empty,
  CHAR_MAX,
  CHAR_MAX,
  CHAR_MAX,
  CHAR_MAX,
  CHAR_MAX,
  CHAR_MAX,
  CHAR_MAX,
  empty,
  CHAR_MAX,
  CHAR_MAX,
  CHAR_MAX,
  CHAR_MAX,
  CHAR_MAX,
  CHAR_MAX,
  CHAR_MAX
};

struct lconv* localeconv(void)
{
  return &lc;
}
