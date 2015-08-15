/*
  Copyright (c) 2015, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _DPMI
#include "idpmi.h"

unsigned long __dpmi_exit_addr;
void* __dpmi_psp;
void* __dpmi_env;
void* __dpmi_stubInfo;
void* __dpmi_iobuf;
void* __dpmi_heap_start;
void* __dpmi_heap_stop;

void __dpmi_terminate(int status)
{
  asm("mov eax, [ebp + 8]\n"
      "push dword [___dpmi_exit_addr]\n"
      "db 0x66\n"
      "retf");
}

int __dpmi_int(int intno, __dpmi_int_regs* regs)
{
  asm("mov edi, [ebp + 12]\n"
      "mov ax, 0x300\n"
      "xor ebx, ebx\n"
      "mov bl, [ebp + 8]\n"
      "xor ecx, ecx\n"
      "int 0x31\n"
      "sbb eax, eax");
}

#endif
