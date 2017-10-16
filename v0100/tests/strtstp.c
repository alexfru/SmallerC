/*
  Demonstration of how to obtain section start and stop addresses.

  How to compile for DOS (all mode(l)s: tiny/.COM, small/.EXE, huge/.EXE, unreal/.EXE, 32-bit DPMI/.EXE):
    smlrcc -dost strtstp.c -o strtstpt.com
    smlrcc -doss strtstp.c -o strtstps.exe
    smlrcc -dosh strtstp.c -o strtstph.exe
    smlrcc -dosu strtstp.c -o strtstpu.exe
    smlrcc -dosp strtstp.c -o strtstpp.exe

  How to compile for Windows:
    smlrcc -win strtstp.c -o strtstpw.exe

  How to compile for Linux:
    smlrcc -linux strtstp.c -o strtstpl

  How to compile for MacOS:
    smlrcc -macos strtstp.c -o strtstpm
*/

#ifndef __SMALLER_C__
#error Must be compiled with Smaller C
#endif

#include <stdio.h>
#include <inttypes.h>

extern char _start__text;
extern char _stop__text;
extern char _start__rodata;
extern char _stop__rodata;
extern char _start__data;
extern char _stop__data;
extern char _start__bss;
extern char _stop__bss;
extern char _start_allcode__;
extern char _stop_allcode__;
extern char _start_alldata__;
extern char _stop_alldata__;

int main(void)
{
  printf("0x%08" PRIXPTR " - 0x%08" PRIXPTR " all code:\n",
         &_start_allcode__, &_stop_allcode__ - 1);
  printf("0x%08" PRIXPTR " - 0x%08" PRIXPTR "   .text\n",
         &_start__text, &_stop__text - 1);
  printf("0x%08" PRIXPTR " - 0x%08" PRIXPTR " all data:\n",
         &_start_alldata__, &_stop_alldata__ - 1);
  printf("0x%08" PRIXPTR " - 0x%08" PRIXPTR "   .rodata\n",
         &_start__rodata, &_stop__rodata - 1);
  printf("0x%08" PRIXPTR " - 0x%08" PRIXPTR "   .data\n",
         &_start__data, &_stop__data - 1);
  printf("0x%08" PRIXPTR " - 0x%08" PRIXPTR "   .bss\n",
         &_start__bss, &_stop__bss - 1);
  return 0;
}
