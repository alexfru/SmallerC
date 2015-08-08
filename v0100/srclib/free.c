/*
  Copyright (c) 2014-2015, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _DOS

#ifdef __HUGE__
static
void DosMemFree(unsigned seg)
{
  asm("mov ah, 0x49\n"
      "mov es, [bp + 8]\n"
      "int 0x21");
}

void free(void* ptr)
{
  DosMemFree((unsigned)ptr >> 4);
}
#endif // __HUGE__

#ifdef _DPMI
#include "idpmi.h"
// TBD!!! proper DPMI memory manager
void free(void* ptr)
{
  if (ptr)
  {
    unsigned id = *((unsigned*)ptr - 2);
    __dpmi_free(id);
  }
}
#endif // _DPMI

#endif // _DOS

#ifndef _DPMI
#ifndef __HUGE__
#ifndef _WINDOWS

#include "mm.h"

void free(void* ptr)
{
  unsigned sz, *blk, *nxtblk;

  if (!ptr)
    return;

  blk = (unsigned*)((unsigned)ptr - HEADER_FOOTER_SZ);
  sz = blk[0];
  nxtblk = (unsigned*)((unsigned)ptr + sz + HEADER_FOOTER_SZ);
  blk[1] = 0; // free
  nxtblk[-2] = 0; // free

  if ((unsigned)blk > __heap_start) // prev block exists
  {
    unsigned* prvblk = (unsigned*)((unsigned)blk - blk[-1] - 2*HEADER_FOOTER_SZ);
    if (!prvblk[1]) // it's free, join the two
    {
      sz += prvblk[0] + 2*HEADER_FOOTER_SZ;
      prvblk[0] = sz;
      nxtblk[-1] = sz;
      blk = prvblk;
    }
  }

  if ((unsigned)nxtblk < __heap_stop && !nxtblk[1]) // next block exists and is free, join the two
  {
    unsigned* nxtnxtblk = (unsigned*)((unsigned)nxtblk + nxtblk[0] + 2*HEADER_FOOTER_SZ);
    sz += nxtblk[0] + 2*HEADER_FOOTER_SZ;
    blk[0] = sz;
    nxtnxtblk[-1] = sz;
  }
}

#endif // !_WINDOWS
#endif // !__HUGE__
#endif // !_DPMI

#ifdef _WINDOWS

#include "iwin32.h"

void free(void* ptr)
{
  HeapFree(GetProcessHeap(), 0, ptr);
}

#endif // _WINDOWS
