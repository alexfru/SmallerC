/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include <unistd.h>

#ifdef _DOS

#ifdef __HUGE__
static
int __DosSeek(int handle, unsigned short offset[2], int whence)
{
  asm("mov ah, 0x42\n"
      "mov bx, [bp + 8]\n"
      "mov esi, [bp + 12]\n"
      "ror esi, 4\n"
      "mov ds, si\n"
      "shr esi, 28");
  asm("mov dx, [si]\n"
      "mov cx, [si + 2]\n"
      "mov al, [bp + 16]\n"
      "int 0x21");
  asm("mov bx, ax\n"
      "cmc\n"
      "sbb ax, ax\n"
      "and dx, ax\n"
      "and eax, 1");
  asm("mov [si], bx\n" // offset[0] will have error code on failure
      "mov [si + 2], dx"); // else offset[] will be replaced with new position
}
#endif // __HUGE__

#ifdef __SMALLER_C_16__
static
int __DosSeek(int handle, unsigned short offset[2], int whence)
{
  asm("mov ah, 0x42\n"
      "mov bx, [bp + 4]\n"
      "mov si, [bp + 6]");
  asm("mov dx, [si]\n"
      "mov cx, [si + 2]\n"
      "mov al, [bp + 8]\n"
      "int 0x21");
  asm("mov bx, ax\n"
      "cmc\n"
      "sbb ax, ax\n"
      "and dx, ax\n"
      "and ax, 1");
  asm("mov [si], bx\n" // offset[0] will have error code on failure
      "mov [si + 2], dx"); // else offset[] will be replaced with new position
}
#endif // __SMALLER_C_16__

int __lseek(int fd, fpos_t* offset, int whence)
{
  fpos_t o = *offset;
  if (__DosSeek(fd, &o, whence))
  {
    *offset = o;
    return 0;
  }
  return -1;
}

#endif // _DOS

#ifdef _WINDOWS

#include "iwin32.h"

int __lseek(int fd, fpos_t* offset, int whence)
{
  union
  {
    fpos_t fo;
    off_t o;
  } u;
  u.fo = *offset;

  if ((u.o = lseek(fd, u.o, whence)) != -1)
  {
    *offset = u.fo;
    return 0;
  }
  return -1;
}

#endif // _WINDOWS
