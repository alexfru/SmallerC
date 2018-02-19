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

#ifdef __HUGE_OR_UNREAL__
static
int DosWrite(int handle, void* buf, unsigned size, unsigned* sizeOrError)
{
  asm("mov ah, 0x40\n"
      "mov bx, [bp + 8]\n"
      "mov edx, [bp + 12]\n"
      "ror edx, 4\n"
      "mov ds, dx\n"
      "shr edx, 28\n"
      "mov cx, [bp + 16]\n"
      "int 0x21");
  asm("movzx ebx, ax\n"
      "cmc\n"
      "sbb ax, ax\n"
      "and eax, 1\n"
      "mov esi, [bp + 20]");
#ifdef __HUGE__
  asm("ror esi, 4\n"
      "mov ds, si\n"
      "shr esi, 28\n"
      "mov [si], ebx");
#else
  asm("push word 0\n"
      "pop  ds\n"
      "mov  [esi], ebx");
#endif
}
#endif // __HUGE_OR_UNREAL__

#ifdef __SMALLER_C_16__
static
int DosWrite(int handle, void* buf, unsigned size, unsigned* sizeOrError)
{
  asm("mov ah, 0x40\n"
      "mov bx, [bp + 4]\n"
      "mov dx, [bp + 6]\n"
      "mov cx, [bp + 8]\n"
      "int 0x21");
  asm("mov bx, ax\n"
      "cmc\n"
      "sbb ax, ax\n"
      "and ax, 1\n"
      "mov si, [bp + 10]\n"
      "mov [si], bx");
}
#endif // __SMALLER_C_16__

#ifdef _DPMI
#include <string.h>
#include "idpmi.h"
static
int DosWrite(int handle, void* buf, unsigned size, unsigned* sizeOrError)
{
  __dpmi_int_regs regs;
  memcpy(__dpmi_iobuf, buf, size);
  memset(&regs, 0, sizeof regs);
  regs.eax = 0x4000;
  regs.ebx = handle;
  regs.ecx = size;
  regs.edx = (unsigned)__dpmi_iobuf & 0xF;
  regs.ds = (unsigned)__dpmi_iobuf >> 4;
  if (__dpmi_int(0x21, &regs))
  {
    *sizeOrError = -1;
    return 0;
  }
  *sizeOrError = regs.eax & 0xFFFF;
  return (regs.flags & 1) ^ 1; // carry
}
#endif // _DPMI

ssize_t __write(int fd, void* buf, size_t size)
{
  ssize_t cnt = 0;
  char* p = buf;

  if ((ssize_t)size < 0)
  {
    return -1;
  }

  while (size)
  {
#ifdef __HUGE_OR_UNREAL__
    // DOS can read/write at most 65535 bytes at a time.
    // An arbitrary 20-bit physical address can be transformed
    // into a segment:offset pair such that offset is always <= 15
    // (which is what we do under the hood in the huge mode(l))
    // and therefore the size is additionally limited by this
    // offset that can be as high as 15 and DOS will only have
    // the range from this offset (at most 15(0xF)) to 65535(0xFFFF)
    // within a segment. So, cap the size at 0xFFF0.
    unsigned sz = (size > 0xFFF0) ? 0xFFF0 : size;
#endif
#ifdef _DPMI
    // Similarly to huge, the DPMI I/O buffer size is also smaller than 64KB.
    unsigned sz = (size > __DPMI_IOFBUFSZ) ? __DPMI_IOFBUFSZ : size;
#endif
#ifndef __HUGE_OR_UNREAL__
#ifndef _DPMI
    unsigned sz = size;
#endif
#endif
    unsigned writtenOrError;
    if (DosWrite(fd, p, sz, &writtenOrError))
    {
      p += writtenOrError;
      cnt += writtenOrError;
      size -= writtenOrError;
      if (writtenOrError < sz)
        return cnt;
    }
    else
    {
      return -1;
    }
  }

  return cnt;
}

#endif // _DOS

#ifdef _WINDOWS

#include "iwin32.h"

ssize_t __write(int fd, void* buf, size_t size)
{
  unsigned writtenOrError;

  if ((ssize_t)size < 0)
  {
    return -1;
  }

  if (!size)
    return 0;

  // TBD??? Fix this hack???
  // GetStdHandle(STD_INPUT_HANDLE), GetStdHandle(STD_OUTPUT_HANDLE) and GetStdHandle(STD_ERROR_HANDLE)
  // appear to always return 3, 7 and 11 when there's no redirection. Other handles (e.g. those of files)
  // appear to have values that are multiples of 4. I'm not sure if GetStdHandle() can ever return values
  // 0, 1 and 2 or if any other valid handle can ever be equal to 0, 1 or 2.
  // If 0, 1 and 2 can be valid handles in the system, I'll need to renumber/translate handles in the C library.
  if (fd >= STDIN_FILENO && fd <= STDERR_FILENO)
    fd = __GetStdHandle(STD_INPUT_HANDLE - fd);

  if (__WriteFile(fd, buf, size, &writtenOrError, 0))
  {
    return writtenOrError;
  }
  else
  {
    return -1;
  }
}

#endif // _WINDOWS

#ifdef _LINUX

ssize_t __write(int fd, void* buf, size_t size)
{
  asm("mov eax, 4\n" // sys_write
      "mov ebx, [ebp + 8]\n"
      "mov ecx, [ebp + 12]\n"
      "mov edx, [ebp + 16]\n"
      "int 0x80\n"
      "add eax, 0\n"
      "jns .done\n"
      "mov eax, -1\n" // should really return -1 on error. TBD??? set errno?
      ".done:");
}

#endif // _LINUX

#ifdef _MACOS

ssize_t __write(int fd, void* buf, size_t size)
{
  asm("mov  eax, 4\n" // sys_write
      "push dword [ebp + 16]\n"
      "push dword [ebp + 12]\n"
      "push dword [ebp + 8]\n"
      "sub  esp, 4\n"
      "int  0x80\n"
      "jnc  .done\n"
      "mov  eax, -1\n" // should really return -1 on error. TBD??? set errno?
      ".done:");
}

#endif // _MACOS
