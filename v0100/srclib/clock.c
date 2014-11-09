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
  static unsigned initialized, initticks;
  if (initialized)
    return helper() - initticks;
  initticks = helper();
  initialized = 1;
  return 0;
}
#endif

#endif // _DOS

#ifdef _WINDOWS

#include "iwin32.h"

clock_t clock(void)
{
  static unsigned initialized, initticks;
  if (initialized)
    return GetTickCount() - initticks;
  initticks = GetTickCount();
  initialized = 1;
  return 0;
}

#endif // _WINDOWS
