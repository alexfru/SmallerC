/*
  Copyright (c) 2014-2018, Alexey Frunze
  2-clause BSD license.
*/
#ifdef __HUGE__
#define __HUGE_OR_UNREAL__
#endif
#ifdef __UNREAL__
#define __HUGE_OR_UNREAL__
#endif

#ifdef _DOS

#ifdef __HUGE_OR_UNREAL__
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
      "mov esi, [bp + 12]");
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

#ifdef _DPMI
#include <string.h>
#include "idpmi.h"
static
int DosDelete(char* name, unsigned* error)
{
  __dpmi_int_regs regs;
  unsigned nlen = strlen(name) + 1;
  if (nlen > __DPMI_IOFBUFSZ)
  {
    *error = -1;
    return 0;
  }
  memcpy(__dpmi_iobuf, name, nlen);
  memset(&regs, 0, sizeof regs);
  regs.eax = 0x4100;
  regs.edx = (unsigned)__dpmi_iobuf & 0xF;
  regs.ds = (unsigned)__dpmi_iobuf >> 4;
  if (__dpmi_int(0x21, &regs))
  {
    *error = -1;
    return 0;
  }
  *error = regs.eax & 0xFFFF;
  return (regs.flags & 1) ^ 1; // carry
}
#endif // _DPMI

int __unlink(char* name)
{
  unsigned error;
  if (DosDelete(name, &error))
    return 0;
  return -1;
}

#endif // _DOS

#ifdef _WINDOWS

#include "iwin32.h"

int __unlink(char* name)
{
  if (__DeleteFileA(name))
    return 0;
  return -1;
}

#endif // _WINDOWS

#ifdef _LINUX

int __unlink(char* name)
{
  asm("mov eax, 10\n" // sys_unlink
      "mov ebx, [ebp + 8]\n"
      "int 0x80\n"
      "add eax, 0\n"
      "jns .done\n"
      "mov eax, -1\n" // should really return -1 on error. TBD??? set errno?
      ".done:");
}

#endif // _LINUX

#ifdef _MACOS

int __unlink(char* name)
{
  asm("mov  eax, 10\n" // sys_unlink
      "push dword [ebp + 8]\n"
      "sub  esp, 4\n"
      "int  0x80\n"
      "jnc  .done\n"
      "mov  eax, -1\n" // should really return -1 on error. TBD??? set errno?
      ".done:");
}

#endif // _MACOS
