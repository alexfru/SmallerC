/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include <unistd.h>

#ifdef _DOS
#ifdef __HUGE__
static
int DosSeek(int handle, unsigned offset, int whence, unsigned* offsetOrError)
{
  asm("mov ah, 0x42\n"
      "mov bx, [bp + 8]\n"
      "mov dx, [bp + 12]\n"
      "mov cx, [bp + 12 + 2]\n"
      "mov al, [bp + 16]\n"
      "int 0x21");
  asm("mov bx, ax\n"
      "cmc\n"
      "sbb ax, ax\n"
      "and dx, ax\n"
      "and eax, 1");
  asm("mov esi, [bp + 20]\n"
      "ror esi, 4\n"
      "mov ds, si\n"
      "shr esi, 28\n"
      "mov [si], bx\n"
      "mov [si + 2], dx");
}

off_t lseek(int fd, off_t offset, int whence)
{
  unsigned offsetOrError;
  if (DosSeek(fd, offset, whence, &offsetOrError))
    return offsetOrError;
  return -1;
}
#endif // __HUGE__
#endif // _DOS
