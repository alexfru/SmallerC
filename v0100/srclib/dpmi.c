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

void __dpmi_terminate(int status)
{
  asm("mov eax, [ebp + 8]\n"
      "push dword [___dpmi_exit_addr]\n"
      "db 0x66\n"
      "retf");
}

void* __dpmi_alloc(unsigned size, unsigned* id)
{
  asm("mov cx, [ebp + 8]\n"
      "mov bx, [ebp + 10]\n"
      "mov ax, 0x501\n"
      "int 0x31\n"

      "sbb edx, edx\n"
      "not edx\n"

      "mov eax, ebx\n"
      "shl eax, 16\n"
      "mov ax, cx\n"
      "and eax, edx\n"

      "shl esi, 16\n"
      "mov si, di\n"
      "and esi, edx\n"
      "mov edi, [ebp + 12]\n"
      "mov [edi], esi");
}

int __dpmi_free(unsigned id)
{
  asm("mov di, [ebp + 8]\n"
      "mov si, [ebp + 10]\n"
      "mov ax, 0x502\n"
      "int 0x31\n"
      "sbb eax, eax");
}

//#define DEBUG_DPMI_INT
#ifdef DEBUG_DPMI_INT
static
unsigned ss(void)
{
  asm("xor eax, eax\n"
      "mov ax, ss");
}

static
void printc(int c)
{
  asm("mov dl, [ebp + 8]\n"
      "mov ah, 2\n"
      "int 0x21");
}

static
void prints(char* s)
{
  while (*s)
    printc(*s++);
}

static
void printeol(void)
{
  prints("\r\n");
}

static
void printh(unsigned n)
{
  int i;
  for (i = 0; i < 8; i++)
  {
    int d = n >> 28;
    n <<= 4;
    printc("0123456789abcdef"[d]);
  }
}

static
void print_regs(int intno, __dpmi_int_regs* regs)
{
  prints("int "); printh(intno); prints(" regs @ "); printh((unsigned)regs);
  prints(" ss:esp @ "); printh(ss()); printc(':'); printh((unsigned)&intno); prints(" : \r\n");
  prints(" edi:"); printh(regs->edi); prints(" esi:"); printh(regs->esi); prints(" ebp:"); printh(regs->ebp);
  prints(" ebx:"); printh(regs->ebx); prints(" edx:"); printh(regs->edx); prints(" ecx:"); printh(regs->ecx); printeol();
  prints(" eax:"); printh(regs->eax); prints(" flg:"); printh(regs->flags); prints("  es:"); printh(regs->es);
  prints("  ds:"); printh(regs->ds); prints("  fs:"); printh(regs->fs); prints("  gs:"); printh(regs->gs); printeol();
}
#endif

int __dpmi_int(int intno, __dpmi_int_regs* regs)
{
#ifdef DEBUG_DPMI_INT
  print_regs(intno, regs);
#endif
  asm("mov edi, [ebp + 12]\n"
      "mov ax, 0x300\n"
      "xor ebx, ebx\n"
      "mov bl, [ebp + 8]\n"
      "xor ecx, ecx\n"
      "int 0x31\n"
      "sbb eax, eax");
}

#endif
