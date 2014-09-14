/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
static void exchange(char* p1, char* p2, unsigned size)
{
  while (size--)
  {
    int t = *p1;
    *p1++ = *p2;
    *p2++ = t;
  }
}

void qsort(void* base, unsigned ecount, unsigned esize, int (*fcmp)(void*, void*))
{
  unsigned heapsz = 0;

  // Using heap sort instead of quick sort to avoid pathological behavior of the latter
  // with O(n*n) cost and potential stack overflow.

  // Transform the array into a heap, element by element, with the maximum element at the root
  while (ecount--)
  {
    unsigned i = heapsz;
    unsigned parent = (i - 1) >> 1;
    while (i && fcmp((char*)base + parent * esize, (char*)base + i * esize) < 0)
    {
      exchange((char*)base + parent * esize, (char*)base + i * esize, esize);
      i = parent;
      parent = (parent - 1) >> 1;
    }
    heapsz++;
  }

  // Transform the heap into a sorted array by repeatedly removing the maximum element
  // from the root and re-establishing the heap property
  while (heapsz--)
  {
    unsigned i = 0;
    exchange((char*)base, (char*)base + heapsz * esize, esize);
    while (i < (heapsz >> 1)) // while i'th node has at least one child (left)
    {
      unsigned left = (i << 1) + 1;
      unsigned right = left + 1;
      unsigned candidate = left;
      if (right < heapsz && // if there's also a right child, pick the largest of the two
          fcmp((char*)base + right * esize, (char*)base + left * esize) > 0)
            candidate = right;
      if (fcmp((char*)base + i * esize, (char*)base + candidate * esize) >= 0)
        break;
      exchange((char*)base + i * esize, (char*)base + candidate * esize, esize);
      i = candidate;
    }
  }
}
