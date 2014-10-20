/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include <locale.h>

char* setlocale(int category, char* locale)
{
  (void)category;
  if (!locale || *locale == '\0' || (*locale == 'C' && locale[1] == '\0'))
    return "C";
  return 0;
}
