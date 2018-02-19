/*
  Copyright (c) 2014-2018, Alexey Frunze
  2-clause BSD license.
*/
#include <unistd.h>

#ifdef __HUGE__
#define __HUGE_OR_UNREAL__
#endif
#ifdef __UNREAL__
#define __HUGE_OR_UNREAL__
#endif

#ifdef _DOS

#ifdef __HUGE_OR_UNREAL__
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
#ifdef __UNREAL__
  asm("push word 0\n"
      "pop ds");
#endif
}
#endif // __HUGE_OR_UNREAL__

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

#ifdef _DPMI
static
int __DosSeek(int handle, unsigned short offset[2], int whence)
{
  asm("mov ah, 0x42\n"
      "mov bx, [ebp + 8]\n"
      "mov esi, [ebp + 12]");
  asm("mov dx, [esi]\n"
      "mov cx, [esi + 2]\n"
      "mov al, [ebp + 16]\n"
      "int 0x21");
  asm("mov bx, ax\n"
      "cmc\n"
      "sbb ax, ax\n"
      "and dx, ax\n"
      "and eax, 1");
  asm("mov [esi], bx\n" // offset[0] will have error code on failure
      "mov [esi + 2], dx"); // else offset[] will be replaced with new position
}
#endif // _DPMI

int __lseekp(int fd, fpos_t* offset, int whence)
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

#ifndef _DOS

int __lseekp(int fd, fpos_t* offset, int whence)
{
  union
  {
    fpos_t fo;
    off_t o;
  } u;
  u.fo = *offset;

  if ((u.o = __lseek(fd, u.o, whence)) != -1)
  {
    *offset = u.fo;
    return 0;
  }
  return -1;
}

#endif // !_DOS
