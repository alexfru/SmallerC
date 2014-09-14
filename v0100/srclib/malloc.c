/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _DOS
#ifdef __HUGE__

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

#endif // __HUGE__

#ifdef __SMALLER_C_16__
#include "mm.h"

unsigned __heap_start;
unsigned __heap_stop;

static int init(void)
{
  unsigned start = (unsigned)&_stop_alldata__;
  unsigned stop = (unsigned)&_start_stack__;
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

  start = ((start + HEADER_FOOTER_SZ - 1) & -HEADER_FOOTER_SZ) | HEADER_FOOTER_SZ; // start or next odd multiple of 4; if we add 4 to it, it will be a multiple of 8
  stop = ((stop - HEADER_FOOTER_SZ) & -HEADER_FOOTER_SZ) | HEADER_FOOTER_SZ; // stop or previous odd multiple of 4

  if (start < (unsigned)&_stop_alldata__ ||
      stop > (unsigned)&_start_stack__ ||
      start > stop ||
      stop - start < 2*HEADER_FOOTER_SZ)
    return -1;

  heapsz = stop - start - 2*HEADER_FOOTER_SZ;

  *((unsigned*)start + 0) = heapsz;
  *((unsigned*)start + 1) = 0;
  *((unsigned*)stop - 2) = 0;
  *((unsigned*)stop - 1) = heapsz;

  __heap_start = start;
  __heap_stop = stop;
  return 0;
}

void* malloc(unsigned size)
{
  static int uninitialized = -1;
  unsigned* blk;

  if (uninitialized)
  {
    uninitialized = init();
    if (uninitialized)
      return 0;
  }

  if (!size || size > -2*(unsigned)HEADER_FOOTER_SZ) // too small or too large
    return 0;

  size = (size + 2*HEADER_FOOTER_SZ - 1) & -2*HEADER_FOOTER_SZ;

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

    blk = nxtblk;
  }

  return 0;
}
#endif
#endif // _DOS
