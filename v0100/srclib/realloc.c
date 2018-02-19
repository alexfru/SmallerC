/*
  Copyright (c) 2014-2018, Alexey Frunze
  2-clause BSD license.
*/
#include <string.h>
#include <stdlib.h>

#ifdef __HUGE__
#define __HUGE_OR_UNREAL__
#endif
#ifdef __UNREAL__
#define __HUGE_OR_UNREAL__
#endif

#ifdef _DOS

#ifdef __HUGE_OR_UNREAL__
static
int DosMemResize(unsigned seg, unsigned paras)
{
  asm("mov ah, 0x4a\n"
      "mov es, [bp + 8]\n"
      "mov bx, [bp + 12]\n"
      "int 0x21\n"
      "cmc\n"
      "sbb ax, ax\n"
      "and eax, 1");
#ifdef __UNREAL__
  asm("push word 0\n"
      "pop  es");
#endif
}

void* realloc(void* ptr, unsigned size)
{
  if (!size || size > 0xffff0)
    return 0;

  if (!ptr)
  {
    return malloc(size);
  }
  else
  {
    unsigned newParas = (size + 15) >> 4;
    if (DosMemResize((unsigned)ptr >> 4, newParas))
    {
      return ptr;
    }
    else
    {
      // In-place resize failed. Try another allocation.
      char* mcbSig = (char*)ptr - 16;
      unsigned short* mcbParas = (unsigned short*)(mcbSig + 3);
      int sig = *mcbSig;
      unsigned oldParas = *mcbParas; // size of *ptr in paragraphs from MCB
      if ((sig == 'M' || sig == 'Z') && oldParas < newParas) // minor MCB sanity checks
      {
        void* ptr2 = malloc(size);
        if (ptr2)
        {
          memcpy(ptr2, ptr, oldParas << 4);
          free(ptr);
          return ptr2;
        }
      }
    }
    return 0;
  }
}
#endif // __HUGE_OR_UNREAL__

#ifdef _DPMI
#include "idpmi.h"
#endif // _DPMI

#endif // _DOS

#ifndef __HUGE_OR_UNREAL__
#ifndef _WINDOWS

#include "mm.h"

void* realloc(void* ptr, unsigned size)
{
  if (!size || size > -2*(unsigned)HEADER_FOOTER_SZ) // too small or too large
    return 0;

  if (!ptr)
  {
    return malloc(size);
  }
  else
  {
    size = (size + 2*HEADER_FOOTER_SZ - 1) & -2*HEADER_FOOTER_SZ;
    unsigned* blk = (unsigned*)((unsigned)ptr - HEADER_FOOTER_SZ);
    unsigned sz = blk[0];
    unsigned* nxtblk = (unsigned*)((unsigned)blk + 2*HEADER_FOOTER_SZ + sz);
    if (sz >= size)
    {
      if (sz > size)
      {
        // Shrink/split the block
        unsigned* mid = (unsigned*)((unsigned)blk + 2*HEADER_FOOTER_SZ + size);
        blk[0] = size;
        mid[-2] = 1; // allocated
        mid[-1] = size;
        sz -= size + 2*HEADER_FOOTER_SZ;
        mid[0] = sz;
        mid[1] = 0; // free
        nxtblk[-2] = 0; // free
        nxtblk[-1] = sz;
      }
      return ptr;
    }
    else
    {
      // TBD!!! try to expand into neighbors
      void* ptr2 = malloc(size);
      if (ptr2)
      {
        memcpy(ptr2, ptr, sz);
        free(ptr);
        return ptr2;
      }
      return 0;
    }
  }
}

#endif // !_WINDOWS
#endif // !__HUGE_OR_UNREAL__


#ifdef _WINDOWS

#include "iwin32.h"

void* realloc(void* ptr, unsigned size)
{
  return ptr ?
    __HeapReAlloc(__GetProcessHeap(), 0, ptr, size) :
    __HeapAlloc(__GetProcessHeap(), 0, size);
}

#endif // _WINDOWS
