/*
  How to compile for DOS (small/.EXE, huge/.EXE, unreal/.EXE, 32-bit DPMI/.EXE):
    smlrcc -doss exc.c -o exc.exe
    smlrcc -dosh exc.c -o exc.exe
    smlrcc -dosu exc.c -o exc.exe
    smlrcc -dosp exc.c -o exc.exe

  How to compile for Windows:
    smlrcc -win exc.c -o exc.exe

  How to compile for Linux:
    smlrcc -linux exc.c -o exc

  How to compile for MacOS:
    smlrcc -macos exc.c -o exc
*/

#include <stdio.h>

static volatile int zero = 0, one = 1;

int main(int argc, char* argv[])
{
  int i;

  if (argc > 1)
  {
    for (i = 1; i <= 3; i++)
    {
      printf("Iteration %d of 3\n", i);

      if (i == 2)
      {
        printf("Invoking #%s...\n", argv[1]);

        if (!strcmp(argv[1], "DE"))
        {
          one /= zero; // #DE
        }
/*
        else if (!strcmp(argv[1], "BP"))
        {
          asm("int3"); // #BP
        }
*/
        else if (!strcmp(argv[1], "OF"))
        {
          asm("mov al, 0x7f\n"
              "add al, al\n"
              "into"); // #OF
        }
        else if (!strcmp(argv[1], "UD"))
        {
          asm("ud2"); // #UD
        }
      }
    }
  }
  else
  {
#if !defined(_LINUX) && !defined(_MACOS)
    system("exc.exe DE");
//    system("exc.exe BP");
    system("exc.exe OF");
    system("exc.exe UD");
#else
    system("./exc DE");
//    system("./exc BP");
    system("./exc OF");
    system("./exc UD");
#endif
  }

  return 0;
}
