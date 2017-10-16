/*
  How to compile for DOS (all mode(l)s: tiny/.COM, small/.EXE, huge/.EXE, unreal/.EXE, 32-bit DPMI/.EXE):
    smlrcc -dost hw.c -o hwdt.com
    smlrcc -doss hw.c -o hwds.exe
    smlrcc -dosh hw.c -o hwdh.exe
    smlrcc -dosu hw.c -o hwdu.exe
    smlrcc -dosp hw.c -o hwdp.exe

  How to compile for Windows:
    smlrcc -win hw.c -o hww.exe

  How to compile for Linux:
    smlrcc -linux hw.c -o hwl

  How to compile for MacOS:
    smlrcc -macos hw.c -o hwm
*/

#include <stdio.h>

int main(void)
{
  puts("Hello, World!");
  return 0;
}
