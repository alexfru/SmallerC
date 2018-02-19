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
int DosRename(char* old, char* new, unsigned* error)
{
  asm("mov ah, 0x56\n"
      "mov edx, [bp + 8]\n"
      "ror edx, 4\n"
      "mov ds, dx\n"
      "shr edx, 28");
  asm("mov edi, [bp + 12]\n"
      "ror edi, 4\n"
      "mov es, di\n"
      "shr edi, 28\n"
      "int 0x21");
  asm("movzx ebx, ax\n"
      "cmc\n"
      "sbb ax, ax\n"
      "and eax, 1\n"
      "mov esi, [bp + 16]");
#ifdef __HUGE__
  asm("ror esi, 4\n"
      "mov ds, si\n"
      "shr esi, 28\n"
      "mov [si], ebx");
#else
  asm("push dword 0\n"
      "pop  es\n"
      "pop  ds\n"
      "mov  [esi], ebx");
#endif
}
#endif // __HUGE_OR_UNREAL__

#ifdef __SMALLER_C_16__
static
int DosRename(char* old, char* new, unsigned* error)
{
  asm("mov ah, 0x56\n"
      "mov dx, [bp + 4]\n"
      "mov di, [bp + 6]\n"
      "int 0x21");
  asm("mov bx, ax\n"
      "cmc\n"
      "sbb ax, ax\n"
      "and ax, 1\n"
      "mov si, [bp + 8]\n"
      "mov [si], bx");
}
#endif // __SMALLER_C_16__

#ifdef _DPMI
#include <string.h>
#include "idpmi.h"
static
int DosRename(char* old, char* new, unsigned* error)
{
  __dpmi_int_regs regs;
  unsigned lold = strlen(old) + 1;
  unsigned lnew = strlen(new) + 1;
  char* pnew = __dpmi_iobuf;
  if (lold > __DPMI_IOFBUFSZ || lnew > __DPMI_IOFBUFSZ - lold)
  {
    *error = -1;
    return 0;
  }
  memcpy(__dpmi_iobuf, old, lold);
  memcpy(pnew += lold, new, lnew);
  memset(&regs, 0, sizeof regs);
  regs.eax = 0x5600;
  regs.edx = (unsigned)__dpmi_iobuf & 0xF;
  regs.ds = (unsigned)__dpmi_iobuf >> 4;
  regs.edi = (unsigned)pnew & 0xF;
  regs.es = (unsigned)pnew >> 4;
  if (__dpmi_int(0x21, &regs))
  {
    *error = -1;
    return 0;
  }
  *error = regs.eax & 0xFFFF;
  return (regs.flags & 1) ^ 1; // carry
}
#endif // _DPMI

int rename(char* old, char* new)
{
  unsigned error;
  if (DosRename(old, new, &error))
    return 0;
  return -1;
}

#endif // _DOS

#ifdef _WINDOWS

#include "iwin32.h"

int rename(char* old, char* new)
{
  if (__MoveFileA(old, new))
    return 0;
  return -1;
}

#endif // _WINDOWS

#ifdef _LINUX

int rename(char* old, char* new)
{
  asm("mov eax, 38\n" // sys_rename
      "mov ebx, [ebp + 8]\n"
      "mov ecx, [ebp + 12]\n"
      "int 0x80\n"
      "add eax, 0\n"
      "jns .done\n"
      "mov eax, -1\n" // should really return -1 on error. TBD??? set errno?
      ".done:");
}

#endif // _LINUX

#ifdef _MACOS

int rename(char* old, char* new)
{
  asm("mov  eax, 128\n" // sys_rename
      "push dword [ebp + 12]\n"
      "push dword [ebp + 8]\n"
      "sub  esp, 4\n"
      "int  0x80\n"
      "jnc  .done\n"
      "mov  eax, -1\n" // should really return -1 on error. TBD??? set errno?
      ".done:");
}

#endif // _MACOS
