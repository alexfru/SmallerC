/*
  Quick and dirty test to ensure that all functions are actually in the library.

  How to compile for DOS (all mode(l)s: tiny/.COM, small/.EXE, huge/.EXE, unreal/.EXE, 32-bit DPMI/.EXE):
    smlrcc -dost libf.c -o libfdt.com
    smlrcc -doss libf.c -o libfds.exe
    smlrcc -dosh libf.c -o libfdh.exe
    smlrcc -dosu libf.c -o libfdu.exe
    smlrcc -dosp libf.c -o libfdp.exe

  How to compile for Windows:
    smlrcc -win libf.c -o libfw.exe

  How to compile for Linux:
    smlrcc -linux libf.c -o libfl

  How to compile for MacOS:
    smlrcc -macos libf.c -o libfm
*/
#include <assert.h>
#include <stdint.h>
#include <ctype.h>
#include <locale.h>
#include <math.h>
#include <setjmp.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <fcntl.h>
#include <unistd.h>

#include <sys/lng.h>

#ifdef _WINDOWS
void __ExitProcess();
void ExitProcess();
char* __GetCommandLineA();
char* GetCommandLineA();
unsigned __GetStdHandle();
unsigned GetStdHandle();
unsigned __GetFileType();
unsigned GetFileType();
int __CloseHandle();
int CloseHandle();
unsigned __GetLastError();
unsigned GetLastError();
void __SetLastError();
void SetLastError();
unsigned __GetProcessHeap();
unsigned GetProcessHeap();
void* __HeapAlloc();
void* HeapAlloc();
int __HeapFree();
int HeapFree();
void* __HeapReAlloc();
void* HeapReAlloc();
unsigned __CreateFileA();
unsigned CreateFileA();
int __DeleteFileA();
int DeleteFileA();
int __MoveFileA();
int MoveFileA();
int __ReadFile();
int ReadFile();
int __WriteFile();
int WriteFile();
unsigned __SetFilePointer();
unsigned SetFilePointer();
unsigned __GetFileAttributesA();
unsigned GetFileAttributesA();
unsigned __GetEnvironmentVariableA();
unsigned GetEnvironmentVariableA();
unsigned __GetTickCount();
unsigned GetTickCount();
void __GetSystemTime();
void GetSystemTime();
int __SystemTimeToTzSpecificLocalTime();
int SystemTimeToTzSpecificLocalTime();
int __TzSpecificLocalTimeToSystemTime();
int TzSpecificLocalTimeToSystemTime();
int __CreateProcessA();
int CreateProcessA();
int __GetExitCodeProcess();
int GetExitCodeProcess();
unsigned __WaitForSingleObject();
unsigned WaitForSingleObject();
void* __SetUnhandledExceptionFilter();
void* SetUnhandledExceptionFilter();
void* __LoadLibraryExA();
void* LoadLibraryExA();
int __FreeLibrary();
int FreeLibrary();
void (*__GetProcAddress())();
void (*GetProcAddress())();
#endif

uintptr_t must_be_present[] =
{
  // <ctype.h>
  isalnum,
  isalpha,
  isblank,
  iscntrl,
  isdigit,
  isgraph,
  islower,
  isprint,
  ispunct,
  isspace,
  isupper,
  isxdigit,
  tolower,
  toupper,

  // <locale.h>
  setlocale,
  localeconv,

  // <math.h>
#ifdef __SMALLER_C_32__
  frexp,
  frexpf,
  ldexp,
  ldexpf,
  modf,
  modff,
  fabs,
  fabsf,
  ceil,
  ceilf,
  floor,
  floorf,
  round,
  roundf,
  trunc,
  truncf,
  sqrt,
  sqrtf,
  hypot,
  hypotf,
  exp,
  expf,
  exp2,
  exp2f,
  expm1,
  expm1f,
  pow,
  powf,
  log,
  logf,
  log2,
  log2f,
  log10,
  log10f,
  sin,
  sinf,
  cos,
  cosf,
  tan,
  tanf,
  atan2,
  atan2f,
  atan,
  atanf,
  acos,
  acosf,
  asin,
  asinf,
  fmod,
  fmodf,
  cosh,
  coshf,
  sinh,
  sinhf,
  tanh,
  tanhf,
#endif

  // <setjmp.h>
  setjmp,
  longjmp,

  // <signal.h>
  signal,
  raise,

  // <stdio.h>
  fopen,
  freopen,
  fflush,
  fclose,
  remove,
  rename,
  fread,
  fgetc,
  getc,
  getchar,
  fgets,
  gets,
  ungetc,
  fwrite,
  fputc,
  putc,
  putchar,
  fputs,
  puts,
  perror,
#ifdef __SMALLER_C_32__
  ftell,
  fseek,
#endif
  __ftell,
  __fseek,
  rewind,
  fgetpos,
  fsetpos,
  clearerr,
  ferror,
  feof,
  setvbuf,
  setbuf,
  __fileno,
  fileno,
  tmpnam,
  tmpfile,
  vfprintf,
  fprintf,
  vprintf,
  printf,
  vsprintf,
  sprintf,
  vsnprintf,
  snprintf,
  vfscanf,
  fscanf,
  vscanf,
  scanf,
  vsscanf,
  sscanf,

  // <stdlib.h>
  abort,
  _Exit,
  exit,
  atexit,
  malloc,
  calloc,
  free,
  realloc,
  abs,
#ifdef __SMALLER_C_32__
  labs,
#endif
  div,
#ifdef __SMALLER_C_32__
  ldiv,
#endif
  atoi,
#ifdef __SMALLER_C_32__
  atol,
  strtol,
  strtoul,
  strtof,
  strtod,
  atof,
#endif
  rand,
  srand,
  bsearch,
  qsort,
  getenv,
  system,

  // <string.h>
  memset,
  memcpy,
  memmove,
  memchr,
  memcmp,
  strcpy,
  strncpy,
  strxfrm,
  strcat,
  strncat,
  strlen,
  strchr,
  strrchr,
  strstr,
  strspn,
  strcspn,
  strpbrk,
  strtok,
  strcmp,
  strncmp,
  strcoll,
  strerror,

  // <time.h>
#ifdef __SMALLER_C_32__
  clock,
  time,
  gmtime,
  localtime,
  mktime,
  ctime,
  difftime,
#endif
  asctime,
  strftime,

  // <fcntl.h>
  __creat,
  creat,
  __open,
  open,

  // <unistd.h>
  __close,
  close,
#ifdef __SMALLER_C_32__
  __lseek,
  lseek,
#endif
  __lseekp,
  __read,
  read,
  __write,
  write,
  __unlink,
  unlink,
  __isatty,
  isatty,

  // <sys/lng.h>
  __lngFromUnsigned,
  __lngFromSigned,
  __lngToUnsigned,
  __lngToSigned,
  __lngAdd,
  __lngSub,
  __lngEq,
  __lngUnsignedLess,
  __lngSignedLess,
  __lngLessThan0,

#ifdef _WINDOWS
  __ExitProcess,
  ExitProcess,
  __GetCommandLineA,
  GetCommandLineA,
  __GetStdHandle,
  GetStdHandle,
  __GetFileType,
  GetFileType,
  __CloseHandle,
  CloseHandle,
  __GetLastError,
  GetLastError,
  __SetLastError,
  SetLastError,
  __GetProcessHeap,
  GetProcessHeap,
  __HeapAlloc,
  HeapAlloc,
  __HeapFree,
  HeapFree,
  __HeapReAlloc,
  HeapReAlloc,
  __CreateFileA,
  CreateFileA,
  __DeleteFileA,
  DeleteFileA,
  __MoveFileA,
  MoveFileA,
  __ReadFile,
  ReadFile,
  __WriteFile,
  WriteFile,
  __SetFilePointer,
  SetFilePointer,
  __GetFileAttributesA,
  GetFileAttributesA,
  __GetEnvironmentVariableA,
  GetEnvironmentVariableA,
  __GetTickCount,
  GetTickCount,
  __GetSystemTime,
  GetSystemTime,
  __SystemTimeToTzSpecificLocalTime,
  SystemTimeToTzSpecificLocalTime,
  __TzSpecificLocalTimeToSystemTime,
  TzSpecificLocalTimeToSystemTime,
  __CreateProcessA,
  CreateProcessA,
  __GetExitCodeProcess,
  GetExitCodeProcess,
  __WaitForSingleObject,
  WaitForSingleObject,
  __SetUnhandledExceptionFilter,
  SetUnhandledExceptionFilter,
  __LoadLibraryExA,
  LoadLibraryExA,
  __FreeLibrary,
  FreeLibrary,
  __GetProcAddress,
  GetProcAddress,
#endif
};

uintptr_t aliases[][2] =
{
  __fileno,
  fileno,
  __creat,
  creat,
  __open,
  open,
  __close,
  close,
#ifdef __SMALLER_C_32__
  __lseek,
  lseek,
#endif
  __read,
  read,
  __write,
  write,
  __unlink,
  unlink,
  __isatty,
  isatty,
#ifdef _WINDOWS
  __ExitProcess,
  ExitProcess,
  __GetCommandLineA,
  GetCommandLineA,
  __GetStdHandle,
  GetStdHandle,
  __GetFileType,
  GetFileType,
  __CloseHandle,
  CloseHandle,
  __GetLastError,
  GetLastError,
  __SetLastError,
  SetLastError,
  __GetProcessHeap,
  GetProcessHeap,
  __HeapAlloc,
  HeapAlloc,
  __HeapFree,
  HeapFree,
  __HeapReAlloc,
  HeapReAlloc,
  __CreateFileA,
  CreateFileA,
  __DeleteFileA,
  DeleteFileA,
  __MoveFileA,
  MoveFileA,
  __ReadFile,
  ReadFile,
  __WriteFile,
  WriteFile,
  __SetFilePointer,
  SetFilePointer,
  __GetFileAttributesA,
  GetFileAttributesA,
  __GetEnvironmentVariableA,
  GetEnvironmentVariableA,
  __GetTickCount,
  GetTickCount,
  __GetSystemTime,
  GetSystemTime,
  __SystemTimeToTzSpecificLocalTime,
  SystemTimeToTzSpecificLocalTime,
  __TzSpecificLocalTimeToSystemTime,
  TzSpecificLocalTimeToSystemTime,
  __CreateProcessA,
  CreateProcessA,
  __GetExitCodeProcess,
  GetExitCodeProcess,
  __WaitForSingleObject,
  WaitForSingleObject,
  __SetUnhandledExceptionFilter,
  SetUnhandledExceptionFilter,
  __LoadLibraryExA,
  LoadLibraryExA,
  __FreeLibrary,
  FreeLibrary,
  __GetProcAddress,
  GetProcAddress,
#endif
};

#ifdef __HUGE__
#define __HUGE_OR_UNREAL__
#endif
#ifdef __UNREAL__
#define __HUGE_OR_UNREAL__
#endif

int main(void)
{
  unsigned i;
#ifdef __SMALLER_C_16__
  extern unsigned short __getCS(void);
  extern unsigned short __getSS(void);
  // In Small Model .EXE programs code and data/stack are in two
  // different segments and so instructions can't be accessed as data. 
  if (__getCS() == __getSS())
  // fallthrough
#endif
  for (i = 0; i < sizeof aliases / sizeof aliases[0]; i++)
  {
    uintptr_t impl = aliases[i][0];
    uintptr_t wrap = aliases[i][1];
    uint8_t* p = wrap;
    uintptr_t target;
#ifdef __HUGE_OR_UNREAL__
    assert(*p == 0xEA); // jmp sel16:ofs16
    memcpy(&target, p + 1, sizeof target);
    target = ((target >> 16) << 4) + (target & 0xFFFF);
#else
    assert(*p == 0xE9); // jmp rel16/32
    memcpy(&target, p + 1, sizeof target);
    p += target + 1 + sizeof target;
    target = p;
#endif
    assert(target == impl);
  }
  puts("All functions present!");
  return 0;
}
