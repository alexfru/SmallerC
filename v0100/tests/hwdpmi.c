/*
  How to compile for DOS/DPMI:
    smlrcc -dosp hwdpmi.c -o hwdpmi.exe
*/

// TBD??? move into hw0.c???

void printc(int c)
{
  asm("mov dl, [ebp + 8]\n"
      "mov ah, 2\n"
      "int 0x21");
}

void prints(char* s)
{
  while (*s)
    printc(*s++);
}

void printeol(void)
{
  prints("\r\n");
}

void printh(unsigned n)
{
  int i;
  prints("0x");
  for (i = 0; i < 8; i++)
  {
    int d = n >> 28;
    n <<= 4;
    printc("0123456789abcdef"[d]);
  }
}

unsigned esp(void)
{
  int a;
  return &a;
}

void _start(unsigned long exitAddr, void* psp, void* env, char* argv0,
            void* stubInfo, void* fbuf, void* heapStart, void* heapStop)
{
  char* args = (char*)psp + 0x80;
  int argsLen = *args++;
  int i;
  char* sig = stubInfo;

  prints("Hello from ");
    prints(__func__); prints("() at "); printh(&_start);
    prints(" in 32-bit protected mode!"); printeol();

  prints("ESP at: ");
    printh(esp()); printeol();

  prints("Executable name: ");
    prints(argv0); printeol();

  prints("Arguments:");
    while (argsLen--) printc(*args++); printeol();

  prints("DPMI stub info signature: \"");
    for (i = 0; i < 4; i++) printc(sig[i]); prints("\""); printeol();

  prints("PSP at: ");
    printh(psp); printeol();

  prints("Environment at: ");
    printh(env); printeol();

  for (i = 0; i < 48*1024; i++) *((char*)fbuf + i) = 0;
  prints("48KB I/O buffer for DOS at: ");
    printh(fbuf); printeol();

  prints("Heap at: ");
    printh(heapStart); prints(" size: "); printh((unsigned)heapStop - (unsigned)heapStart); printeol();

  asm("mov ax, 0x4c00\n"
      "int 0x21");
}
