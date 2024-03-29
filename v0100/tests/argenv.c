/*
  How to compile for DOS (all mode(l)s: tiny/.COM, small/.EXE, huge/.EXE, unreal/.EXE, 32-bit DPMI/.EXE):
    smlrcc -dost argenv.c -o argenvdt.com
    smlrcc -doss argenv.c -o argenvds.exe
    smlrcc -dosh argenv.c -o argenvdh.exe
    smlrcc -dosu argenv.c -o argenvdu.exe
    smlrcc -dosp argenv.c -o argenvdp.exe

  How to compile for Windows:
    smlrcc -win argenv.c -o argenvw.exe

  How to compile for Linux:
    smlrcc -linux argenv.c -o argenvl

  How to compile for MacOS:
    smlrcc -macos argenv.c -o argenvm
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
  int i = 0;

  printf("Arguments:\n");
  for (i = 0; i < argc; i++)
    printf("argv[%d]=\"%s\"\n", i, argv[i]);

  printf("\nThese arguments in the environment:\n");
  for (i = 0; i < argc; i++)
  {
    char* p;
    if ((p = getenv(argv[i])) != NULL)
      printf("\"%s\"=\"%s\"\n", argv[i], p);
  }

  printf("\n");

  return 0;
}
