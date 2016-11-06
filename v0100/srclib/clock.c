/*
  Copyright (c) 2014-2016, Alexey Frunze
  2-clause BSD license.
*/
#include <time.h>

#ifdef __HUGE__
#define __HUGE_OR_UNREAL__
#endif
#ifdef __UNREAL__
#define __HUGE_OR_UNREAL__
#endif

#ifdef _DOS

#ifdef __HUGE_OR_UNREAL__
static
unsigned long helper(void)
{
#ifdef __HUGE__
  asm("mov ax, 0x40\n"
      "mov ds, ax\n"
      "mov eax, [0x6c]");
#else
  asm("mov eax, [0x46c]");
#endif
  asm("mov ecx, 90\n"
      "mul ecx\n"
      "inc ecx\n"
      "div ecx");
}
#endif // __HUGE__

#ifdef _DPMI
static
unsigned long helper(void)
{
  asm("mov eax, [0x46c]\n"
      "mov ecx, 90\n"
      "mul ecx\n"
      "inc ecx\n"
      "div ecx");
}
#endif // _DPMI

#ifdef __SMALLER_C_32__
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

#ifdef _LINUX

struct tms
{
  clock_t tms_utime;
  clock_t tms_stime;
  clock_t tms_cutime;
  clock_t tms_cstime;
};

static
clock_t SysTimes(struct tms* buf)
{
  asm("mov eax, 43\n" // sys_times
      "mov ebx, [ebp + 8]\n"
      "int 0x80");
}

clock_t clock(void)
{
  struct tms tms;
  if (SysTimes(&tms) == (clock_t)-1)
    return (clock_t)-1;
  // tms members are in clock ticks, there are sysconf(_SC_CLK_TCK) (always 100?) clock ticks per second in Linux.
  // OTOH, CLOCKS_PER_SEC is 1000000 (mandated by POSIX).
  // TBD??? Can sysconf(_SC_CLK_TCK) be obtained somehow w/o being hard-coded here and w/o including system headers?
  return (tms.tms_utime + tms.tms_stime) * (CLOCKS_PER_SEC / 100);
}

#endif // _LINUX
