/*
  Copyright (c) 2014-2016, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

asm(
  "section .kernel32_hints\n"
  "dd _hint_TzSpecificLocalTimeToSystemTime"
);

asm(
  "section .kernel32_iat\n"
  "__imp__TzSpecificLocalTimeToSystemTime: dd _hint_TzSpecificLocalTimeToSystemTime"
);

static char hint_TzSpecificLocalTimeToSystemTime[] = "\0\0TzSpecificLocalTimeToSystemTime";

extern char _kernel32_dll__[];
static char* pdll = _kernel32_dll__; // pull trailers for sections .kernel32_hints and .kernel32_iat

struct _TIME_ZONE_INFORMATION;
struct _SYSTEMTIME;

int TzSpecificLocalTimeToSystemTime(struct _TIME_ZONE_INFORMATION* lpTimeZoneInformation,
                                    struct _SYSTEMTIME* lpLocalTime,
                                    struct _SYSTEMTIME* lpUniversalTime)
{
  asm(
    "push dword [ebp+16]\n"
    "push dword [ebp+12]\n"
    "push dword [ebp+8]\n"
    "call dword [__imp__TzSpecificLocalTimeToSystemTime]"
  );
}

#endif // _WINDOWS
