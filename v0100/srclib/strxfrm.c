/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
unsigned strxfrm(char* s1, char* s2, unsigned n)
{
  unsigned res = 0;

  while (n--)
  {
    if ((*s1++ = *s2++) == '\0')
      return res;
    res++;
  }

  // If we get here then it means that we've copied n bytes but '\0' is not among them.
  // It also means that the returned value will be greater or equal to the original value of
  // the parameter n. C99 says: "If the value returned is n or more, the contents of the
  // array pointed to by s1 are indeterminate." IOW, I'm not required to add a '\0' of my own.

  while (*s2++ != '\0')
    res++;

  return res;
}
