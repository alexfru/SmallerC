/*
  Copyright (c) 2014-2018, Alexey Frunze
  2-clause BSD license.
*/
#include <unistd.h>

#ifdef __HUGE__
#define __HUGE_OR_UNREAL__
#endif
#ifdef __UNREAL__
#define __HUGE_OR_UNREAL__
#endif

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

#ifdef __HUGE_OR_UNREAL__
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
      "mov esi, [bp + 12]");
#ifdef __HUGE__
  asm("ror esi, 4\n"
      "mov ds, si\n"
      "shr esi, 28\n"
      "mov [si], ebx");
#else
  asm("mov [esi], ebx");
#endif
}
#endif

#ifdef _DPMI
static
int DosQueryDevFileFlags(int handle, unsigned* flagsOrError)
{
  asm("mov ax, 0x4400\n"
      "mov bx, [ebp + 8]\n"
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
      "mov esi, [ebp + 12]\n"
      "mov [esi], ebx");
}
#endif // _DPMI

int __isatty(int fd)
{
  unsigned flagsOrError;
  // Check if fd is a device handle
  if (DosQueryDevFileFlags(fd, &flagsOrError) && (flagsOrError & 0x80))
    return 1;
  return 0;
}

#endif // _DOS

#ifdef _WINDOWS

#include "iwin32.h"

int __isatty(int fd)
{
  // TBD??? Fix this hack???
  // GetStdHandle(STD_INPUT_HANDLE), GetStdHandle(STD_OUTPUT_HANDLE) and GetStdHandle(STD_ERROR_HANDLE)
  // appear to always return 3, 7 and 11 when there's no redirection. Other handles (e.g. those of files)
  // appear to have values that are multiples of 4. I'm not sure if GetStdHandle() can ever return values
  // 0, 1 and 2 or if any other valid handle can ever be equal to 0, 1 or 2.
  // If 0, 1 and 2 can be valid handles in the system, I'll need to renumber/translate handles in the C library.
  if (fd >= STDIN_FILENO && fd <= STDERR_FILENO)
    fd = __GetStdHandle(STD_INPUT_HANDLE - fd);
  return __GetFileType(fd) == FILE_TYPE_CHAR;
}

#endif // _WINDOWS

#ifdef _LINUX

static
int SysIoctl(int fd, int cmd, ...)
{
  asm("mov eax, 54\n" // sys_ioctl
      "mov ebx, [ebp + 8]\n"
      "mov ecx, [ebp + 12]\n"
      "mov edx, [ebp + 16]\n" // may read garbage, but shouldn't crash
      "int 0x80");
}

int __isatty(int fd)
{
  unsigned char termios[60/*sizeof(struct termios)*/];
  return SysIoctl(fd, 0x00005401/*TCGETS*/, termios) == 0;
}

#endif // _LINUX

#ifdef _MACOS

static
int SysIoctl(int fd, int cmd, ...)
{
  asm("mov eax, 54\n" // sys_ioctl
      "push dword [ebp + 16]\n"
      "push dword [ebp + 12]\n"
      "push dword [ebp + 8]\n" // may read garbage, but shouldn't crash
      "sub esp,4\n"
      "int 0x80");
}

int __isatty(int fd)
{
  unsigned char termios[44/*sizeof(struct termios)*/];
  return SysIoctl(fd, 0x402C7413/*TIOCGETA*/, termios) == 0;
}

#endif // _MACOS
