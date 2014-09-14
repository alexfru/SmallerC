/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
char* strstr(char* s, char* substr)
{
  if (*substr == '\0')
    return s;

  for (;; s++)
  {
    char *p1 = s, *p2 = substr;
    while (*p1 == *p2)
    {
      if (*p2 == '\0')
        return s;
      p1++;
      p2++;
    }
    if (*p2 == '\0')
      return s;
    if (*p1 == '\0')
      return 0;
  }
}
