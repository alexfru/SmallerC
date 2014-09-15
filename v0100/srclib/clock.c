/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include <time.h>

#ifdef _DOS
#ifdef __HUGE__
static
unsigned long helper(void)
{
  asm("mov ax, 0x40\n"
      "mov ds, ax\n"
      "mov eax, [0x6c]\n"
      "mov ecx, 90\n"
      "mul ecx\n"
      "inc ecx\n"
      "div ecx");
}

clock_t clock(void)
{
  return helper();
}
#endif
