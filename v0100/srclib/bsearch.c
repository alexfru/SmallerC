/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
void* bsearch(void* key, void* base, unsigned ecount, unsigned esize, int (*fcmp)(void*, void*))
{
  while (ecount)
  {
    unsigned mid = ecount >> 1;
    char* p = (char*)base + mid * esize;
    int t = fcmp(key, p);

    if (!t)
    {
      return p;
    }
    else if (t < 0)
    {
      ecount = mid;
    }
    else // if (t > 0)
    {
      base = p + esize;
      ecount -= mid + 1;
    }
  }

  return 0;
}
