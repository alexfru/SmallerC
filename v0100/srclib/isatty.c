/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _DOS

#ifdef __SMALLER_C_16__
static
int DosQueryDevFileFlags(int handle, unsigned* flagsOrError)
{
  asm("mov ax, 0x4400\n"
      "mov bx, [bp + 4]\n"
      "int 0x21");
  asm("mov bx, ax\n"
      "cmc\n"
      "sbb ax, ax");
  asm("and dx, ax\n"
      "mov cx, ax\n"
      "not cx\n"
      "and bx, cx\n"
      "or  bx, dx");
  asm("and ax, 1\n"
      "mov si, [bp + 6]\n"
      "mov [si], bx");
}
#endif
#ifdef __HUGE__
static
int DosQueryDevFileFlags(int handle, unsigned* flagsOrError)
{
  asm("mov ax, 0x4400\n"
      "mov bx, [bp + 8]\n"
      "int 0x21");
  asm("movzx ebx, ax\n"
      "cmc\n"
      "sbb ax, ax");
  asm("and dx, ax\n"
      "mov cx, ax\n"
      "not cx\n"
      "and bx, cx\n"
      "or  bx, dx");
  asm("and eax, 1\n"
      "mov esi, [bp + 12]\n"
      "ror esi, 4\n"
      "mov ds, si\n"
      "shr esi, 28\n"
      "mov [si], ebx");
}
#endif

int isatty(int fd)
{
  unsigned flagsOrError;
  // Check if fd is a device handle
  if (DosQueryDevFileFlags(fd, &flagsOrError) && (flagsOrError & 0x80))
    return 1;
  return 0;
}
#endif
