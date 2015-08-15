/*
  Copyright (c) 2015, Alexey Frunze
  2-clause BSD license.
*/
#ifndef __IDPMI_H
#define __IDPMI_H
#ifdef _DPMI

// Size of the buffer within dpstub.exe that we can use for I/O with BIOS/DOS
#define __DPMI_IOFBUFSZ 49152 // keep in sync with FBUFSZ in dpstub.asm!
// Pointer to the buffer
extern void* __dpmi_iobuf;

// Far pointer (sel16:ofs16) to the exit routine in dpstub.exe
extern unsigned long __dpmi_exit_addr;

// Pointer to the PSP of dpstub.exe
extern void* __dpmi_psp;

// Pointer to the environment of dpstub.exe
extern void* __dpmi_env;

// Pointer to the DPMI stub info within dpstub.exe
extern void* __dpmi_stubInfo;

// Pointers to the start and stop of the heap
extern void* __dpmi_heap_start;
extern void* __dpmi_heap_stop;

typedef struct
{
  unsigned long  edi;
  unsigned long  esi;
  unsigned long  ebp;
  unsigned long  resrvd;
  unsigned long  ebx;
  unsigned long  edx;
  unsigned long  ecx;
  unsigned long  eax;
  unsigned short flags;
  unsigned short es;
  unsigned short ds;
  unsigned short fs;
  unsigned short gs;
  unsigned short ip;
  unsigned short cs;
  unsigned short sp;
  unsigned short ss;
} __dpmi_int_regs;

void __dpmi_terminate(int);
int __dpmi_int(int, __dpmi_int_regs*);

#endif
#endif
