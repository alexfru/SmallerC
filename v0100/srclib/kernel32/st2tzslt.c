/*
  Copyright (c) 2014-2019, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

#define DLL "kernel32"
#define FXN "SystemTimeToTzSpecificLocalTime"
#include "../dimports.h"

struct _TIME_ZONE_INFORMATION;
struct _SYSTEMTIME;

int __SystemTimeToTzSpecificLocalTime(struct _TIME_ZONE_INFORMATION* lpTimeZoneInformation,
                                      struct _SYSTEMTIME* lpLocalTime,
                                      struct _SYSTEMTIME* lpUniversalTime)
{
  asm(
    "push dword [ebp+16]\n"
    "push dword [ebp+12]\n"
    "push dword [ebp+8]\n"
    "call dword [__imp__SystemTimeToTzSpecificLocalTime]"
  );
}

#endif // _WINDOWS
