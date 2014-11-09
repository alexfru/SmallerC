/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include <string.h>
#include "itime.h"

#ifdef _DOS

#ifdef __HUGE__
static
void DosGetDate(unsigned short d[3/*[0]-year,[1]-month,[2]-day*/])
{
  asm("mov ah, 0x2a\n"
      "mov esi, [bp + 8]\n"
      "ror esi, 4\n"
      "mov ds, si\n"
      "shr esi, 28\n"
      "int 0x21");
  asm("xor al, al\n"
      "mov [si], cx\n"
      "mov [si+2], dh\n"
      "mov [si+3], al\n"
      "mov [si+4], dl\n"
      "mov [si+5], al");
}

static
void DosGetTime(unsigned short t[3/*[0]-hour,[1]-minutes,[2]-seconds*/])
{
  asm("mov ah, 0x2c\n"
      "mov esi, [bp + 8]\n"
      "ror esi, 4\n"
      "mov ds, si\n"
      "shr esi, 28\n"
      "int 0x21");
  asm("xor al, al\n"
      "mov [si], ch\n"
      "mov [si+1], al\n"
      "mov [si+2], cl\n"
      "mov [si+3], al\n"
      "mov [si+4], dh\n"
      "mov [si+5], al");
}

// time() must return UTC/GMT time
time_t time(time_t* t)
{
  unsigned short d0[3], t1[3], d1[3];
  struct tm tm;
  time_t res;

  DosGetDate(d0);
  DosGetTime(t1);
  DosGetDate(d1);
  while (memcmp(d0, d1, sizeof d0)) // while dates differ/account for date roll-over
  {
    memcpy(d0, d1, sizeof d0); // copy the date
    DosGetTime(t1);
    DosGetDate(d1);
  }

  tm.tm_year = d1[0] - 1900;
  tm.tm_mon  = d1[1] - 1;
  tm.tm_mday = d1[2];
  tm.tm_hour = t1[0];
  tm.tm_min  = t1[1];
  tm.tm_sec  = t1[2];
  tm.tm_isdst = 0;

  // There's no sane way to support time zones in DOS. Pretend to have local time=UTC/GMT.
  res = __buildtime(&tm);

  if (t)
    *t = res;
  return res;
}
#endif // __HUGE__

#endif // _DOS

#ifdef _WINDOWS

#include "iwin32.h"

// time() must return UTC/GMT time
time_t time(time_t* t)
{
  SYSTEMTIME st;
  struct tm tm;
  time_t res;

  GetSystemTime(&st);
  tm.tm_year = st.wYear - 1900;
  tm.tm_mon  = st.wMonth - 1;
  tm.tm_mday = st.wDay;
  tm.tm_hour = st.wHour;
  tm.tm_min  = st.wMinute;
  tm.tm_sec  = st.wSecond;
  tm.tm_isdst = 0;

  res = __buildtime(&tm);

  if (t)
    *t = res;
  return res;
}

#endif // _WINDOWS
