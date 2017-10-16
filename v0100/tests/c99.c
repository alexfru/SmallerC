/*
  How to compile for DOS (all mode(l)s: tiny/.COM, small/.EXE, huge/.EXE, unreal/.EXE, 32-bit DPMI/.EXE):
    smlrcc -dost c99.c -o c99dt.com
    smlrcc -doss c99.c -o c99ds.exe
    smlrcc -dosh c99.c -o c99dh.exe
    smlrcc -dosu c99.c -o c99du.exe
    smlrcc -dosp c99.c -o c99dp.exe

  How to compile for Windows:
    smlrcc -win c99.c -o c99w.exe

  How to compile for Linux:
    smlrcc -linux c99.c -o c99l

  How to compile for MacOS:
    smlrcc -macos c99.c -o c99m
*/

#include <stdio.h>
#include <stdint.h> // C99

uint8_t u8 = -1;
uint16_t u16 = -1;
#ifdef __SMALLER_C_32__
uint32_t u32 = -1;
#endif

// C99: // comments

// C99: trailing comma allowed in enum declarations
enum { EZERO, };

int main(void)
{
  // C99: __func__ predefined identifier
  printf("Hello from %s()\n", __func__);

  printf("u8=%u, u16=%u", (unsigned)u8, (unsigned)u16);
#ifdef __SMALLER_C_32__
  printf(", u32=%u", (unsigned)u32);
#endif
  printf("\n");

  // C99: variable declaration(s) in for loop's clause-1
  for (int i = 0; i < 10; i++)
    printf("%d", i);
  printf("\n");

  // C99: mixed declarations and code
  static int call = EZERO;

  switch (call)
  {
  case 0:
    for (int i = 0; i < 2; i++)
    {
      printf("\ncalling main()...\n\n");
      call++;
      printf("\nmain() returned %d (expected %d)\n", main(), i);
    }
    return 0;
  case 1:
    break;
  case 2:
    return 1;
  }

  (void)3; // trying to fool the compiler into returning 3

  // C99: reaching the } that terminates the main function returns a value of 0
}
