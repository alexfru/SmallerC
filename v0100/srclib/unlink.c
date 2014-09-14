/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _DOS

#ifdef __HUGE__
static
int DosDelete(char* name, unsigned* error)
{
  asm("mov ah, 0x41\n"
      "mov edx, [bp + 8]\n"
      "ror edx, 4\n"
      "mov ds, dx\n"
      "shr edx, 28\n"
      "int 0x21");
  asm("movzx ebx, ax\n"
      "cmc\n"
      "sbb ax, ax\n"
      "and eax, 1\n"
      "mov esi, [bp + 12]\n"
      "ror esi, 4\n"
      "mov ds, si\n"
      "shr esi, 28\n"
      "mov [si], ebx");
}
#endif // __HUGE__

#ifdef __SMALLER_C_16__
static
int DosDelete(char* name, unsigned* error)
{
  asm("mov ah, 0x41\n"
      "mov dx, [bp + 4]\n"
      "int 0x21");
  asm("mov bx, ax\n"
      "cmc\n"
      "sbb ax, ax\n"
      "and ax, 1\n"
      "mov si, [bp + 6]\n"
      "mov [si], bx");
}
#endif // __SMALLER_C_16__

int unlink(char* name)
{
  unsigned error;
  if (DosDelete(name, &error))
    return 0;
  return -1;
}
#endif // _DOS
