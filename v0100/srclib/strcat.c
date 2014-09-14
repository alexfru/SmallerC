/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
char* strcat(char* s1, char* s2)
{
  char* res = s1;
  while (*s1) s1++;
  while ((*s1++ = *s2++) != '\0');
  return res;
}
