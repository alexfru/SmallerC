/*
  How to compile for DOS (all mode(l)s: tiny/.COM, small/.EXE, huge/.EXE):
    smlrcc -dost hw.c -o hwdt.com
    smlrcc -doss hw.c -o hwds.exe
    smlrcc -dosh hw.c -o hwdh.exe

  How to compile for Windows:
    smlrcc -win hw.c -o hww.exe

  How to compile for Linux:
    smlrcc -linux hw.c -o hwl
*/

#include <stdio.h>

int main(void)
{
  puts("Hello, World!");
  return 0;
}
