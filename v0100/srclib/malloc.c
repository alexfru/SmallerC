/*
  Copyright (c) 2014-2018, Alexey Frunze
  2-clause BSD license.
*/
#ifdef __HUGE__
#define __HUGE_OR_UNREAL__
#endif
#ifdef __UNREAL__
#define __HUGE_OR_UNREAL__
#endif

#ifdef _DOS

#ifdef __HUGE_OR_UNREAL__
static
unsigned DosMemAlloc(unsigned paras)
{
  asm("mov ah, 0x48\n"
      "mov bx, [bp + 8]\n"
      "int 0x21\n"
      "cmc\n"
      "sbb bx, bx\n"
      "and ax, bx\n"
      "movzx eax, ax");
}

void* malloc(unsigned size)
{
  if (!size || size > 0xffff0)
    return 0;

  return (void*)(DosMemAlloc((size + 15) >> 4) << 4);
}
#endif // __HUGE_OR_UNREAL__

#ifdef _DPMI
#include "idpmi.h"
#endif // _DPMI

#endif // _DOS


#ifdef _LINUX

static
char* SysBrk(char* newBreak)
{
  asm("mov eax, 45\n" // sys_brk
      "mov ebx, [ebp + 8]\n"
      "int 0x80");
}

static char* CurBreak;

void* __sbrk(int increment)
{
  char *p;

  if (!CurBreak)
  {
    CurBreak = SysBrk(0);
    if ((unsigned)CurBreak + 1 <= 1) // error if SysBrk() returns -1 or 0
    {
      CurBreak = 0;
      return (void*)-1;
    }
  }

  if (increment >= 0)
  {
    if ((unsigned)CurBreak + increment < (unsigned)CurBreak)
    {
      return (void*)-1;
    }
  }
  else
  {
    if ((unsigned)CurBreak + increment >= (unsigned)CurBreak)
    {
      return (void*)-1;
    }
  }

  p = SysBrk(CurBreak + increment);
  if (p != CurBreak + increment)
    return (void*)-1;

  return (CurBreak += increment) - increment;
}

#endif // _LINUX


#ifndef __HUGE_OR_UNREAL__
#ifndef _WINDOWS

#include "mm.h"

unsigned __heap_start;
unsigned __heap_stop;

#ifdef _DOS

static
int init(void)
{
#ifndef _DPMI
  unsigned start = (unsigned)&_stop_alldata__;
  unsigned stop = (unsigned)&_start_stack__;
#else
  unsigned start = (unsigned)__dpmi_heap_start;
  unsigned stop = (unsigned)__dpmi_heap_stop;
#endif
  unsigned heapsz;

  //
  // We'll be allocating blocks that are multiple of 8 bytes in size, naturally aligned.
  // Every block will have a header and a footer on its sides.
  //
  // Memory and block layout:
  //
  // address 0
  //
  // +-------------------------------------------------------------------------------+
  // .                 PREVIOUS BLOCKS WITH HEADERS AND FOOTERS                      .
  // +-------------------------------------------------------------------------------+
  //
  // +-------------------------------------------------------------------------------+
  // | unsigned size;            // size (divisible by 8) of the data area           |
  // +---------------- HEADER -------------------------------------------------------+
  // | unsigned allocated;       // 0 if free, non-zero if allocated                 |
  // +-------------------------------------------------------------------------------+
  // |                                                                               |
  // | unsigned char data[size]; // data area; malloc() returns pointer to this part |
  // |                              (8-byte-aligned)                                 |
  // +-------------------------------------------------------------------------------+
  // | unsigned allocated;       // 0 if free, non-zero if allocated                 |
  // +---------------- FOOTER -------------------------------------------------------+
  // | unsigned size;            // size (divisible by 8) of the data area           |
  // +-------------------------------------------------------------------------------+
  //
  // +-------------------------------------------------------------------------------+
  // .                 NEXT BLOCKS WITH HEADERS AND FOOTERS                          .
  // +-------------------------------------------------------------------------------+
  //
  // address 0xFFFF
  //
  //
  // The above is given for 16-bit versions of malloc()/realloc()/free in the tiny and small
  // memory models in DOS.
  //
  // In 32-bit DPMI and (s)brk-based version in Linux, the layout is the same, but the header/footer
  // size is doubled. The alignment is doubled to 16 bytes as well.
  //

  start = ((start + HEADER_FOOTER_SZ - 1) & -HEADER_FOOTER_SZ) | HEADER_FOOTER_SZ; // start or next odd multiple of 4; if we add 4 to it, it will be a multiple of 8
  stop = ((stop - HEADER_FOOTER_SZ) & -HEADER_FOOTER_SZ) | HEADER_FOOTER_SZ; // stop or previous odd multiple of 4

  if (
#ifndef _DPMI
      start < (unsigned)&_stop_alldata__ ||
      stop > (unsigned)&_start_stack__ ||
#endif
      start > stop ||
      stop - start < 2*HEADER_FOOTER_SZ)
    return -1;

  heapsz = stop - start - 2*HEADER_FOOTER_SZ;

  *((unsigned*)start + 0) = heapsz;
  *((unsigned*)start + 1) = 0; // free
  *((unsigned*)stop - 2) = 0; // free
  *((unsigned*)stop - 1) = heapsz;

  __heap_start = start;
  __heap_stop = stop;
  return 0;
}

#endif // _DOS

#ifdef _LINUX

static
int init(void)
{
  unsigned start0, start, stop;

  start0 = (unsigned)__sbrk(0);
  if ((int)start0 == -1)
    return -1;

  // Create an initial block of zero size with a header and a footer

  start = ((start0 + HEADER_FOOTER_SZ - 1) & -HEADER_FOOTER_SZ) | HEADER_FOOTER_SZ; // start or next odd multiple of 8; if we add 8 to it, it will be a multiple of 16
  stop = start + 2*HEADER_FOOTER_SZ;

  if ((int)__sbrk((start - start0) + 2*HEADER_FOOTER_SZ) == -1)
    return -1;

  *((unsigned*)start + 0) = 0;
  *((unsigned*)start + 1) = 0; // free
  *((unsigned*)stop - 2) = 0; // free
  *((unsigned*)stop - 1) = 0;

  __heap_start = start;
  __heap_stop = stop;

  return 0;
}

#endif // _LINUX

#ifdef _MACOS

static
unsigned buffer[64/4 * 1024 * 1024]; // 64MB heap in .bss

static
int init(void)
{
  __heap_start = buffer;
  __heap_stop = __heap_start + sizeof(buffer);

  unsigned heapsz = __heap_stop - __heap_start - 2*HEADER_FOOTER_SZ;

  *((unsigned*)__heap_start + 0) = heapsz;
  *((unsigned*)__heap_start + 1) = 0; // free
  *((unsigned*)__heap_stop - 2) = 0; // free
  *((unsigned*)__heap_stop - 1) = heapsz;

  return 0;
}

#endif // _MACOS

void* malloc(unsigned size)
{
  static int uninitialized = -1;
  unsigned* blk;
#ifdef _LINUX
  unsigned* last;
  unsigned togrow;
#endif

  if (uninitialized)
  {
    uninitialized = init();
    if (uninitialized)
      return 0;
  }

  if (!size || size > -2*(unsigned)HEADER_FOOTER_SZ) // too small or too large
    return 0;

  size = (size + 2*HEADER_FOOTER_SZ - 1) & -2*HEADER_FOOTER_SZ;

#ifdef _LINUX
  last =
#endif
  blk = (unsigned*)__heap_start;

  while ((unsigned)blk < __heap_stop)
  {
    unsigned sz = blk[0];
    unsigned* nxtblk = (unsigned*)((unsigned)blk + 2*HEADER_FOOTER_SZ + sz);

    if (sz >= size && !blk[1]) // free block of sufficient size
    {
      if (sz == size) // if perfect fit, no split possible
      {
        blk[1] = 1; // allocated
        nxtblk[-2] = 1; // allocated
      }
      else
      {
        // Shrink/split the block
        unsigned* mid = (unsigned*)((unsigned)blk + 2*HEADER_FOOTER_SZ + size);
        blk[0] = size;
        blk[1] = 1; // allocated
        mid[-2] = 1; // allocated
        mid[-1] = size;
        sz -= size + 2*HEADER_FOOTER_SZ;
        mid[0] = sz;
        mid[1] = 0; // free
        nxtblk[-1] = sz;
      }
      return (void*)((unsigned)blk + HEADER_FOOTER_SZ);
    }

#ifdef _LINUX
    last = blk;
#endif
    blk = nxtblk;
  }

#ifdef _LINUX
  if (!last[1]) // if last block is free, it will be reused
  {
    togrow = size - last[0];
    blk = last;
  }
  else
  {
    togrow = size + 2*HEADER_FOOTER_SZ;
    if ((int)togrow <= 0)
      return 0;
    blk = (unsigned*)__heap_stop;
  }

  if ((int)__sbrk(togrow) != -1)
  {
    unsigned* nxtblk = (unsigned*)((unsigned)blk + 2*HEADER_FOOTER_SZ + size);
    blk[0] = size;
    blk[1] = 1; // allocated
    nxtblk[-2] = 1; // allocated
    nxtblk[-1] = size;
    __heap_stop += togrow;
    return (void*)((unsigned)blk + HEADER_FOOTER_SZ);
  }
#endif

  return 0;
}

#endif // !_WINDOWS
#endif // !__HUGE_OR_UNREAL__

#ifdef _WINDOWS

#include "iwin32.h"

void* malloc(unsigned size)
{
  return __HeapAlloc(__GetProcessHeap(), 0, size); // 8-byte-aligned
}

#endif // _WINDOWS
