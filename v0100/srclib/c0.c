/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
extern int main(int argc, char** argv);
extern void exit(int);

#ifdef _DOS

#ifdef __HUGE__
static
unsigned char peekb(unsigned seg, unsigned ofs)
{
  return *((unsigned char*)(seg * 16 + ofs));
}
#endif
#ifdef __SMALLER_C_16__
static
unsigned char peekb(unsigned seg, unsigned ofs)
{
  asm("push ds\n"
      "mov  ds, [bp + 4]\n"
      "mov  bx, [bp + 6]\n"
      "mov  al, [bx]\n"
      "mov  ah, 0\n"
      "pop  ds");
}
#endif

#ifdef __HUGE__
static
unsigned peek(unsigned seg, unsigned ofs)
{
  return *((unsigned short*)(seg * 16 + ofs));
}
#endif
#ifdef __SMALLER_C_16__
static
unsigned peek(unsigned seg, unsigned ofs)
{
  asm("push ds\n"
      "mov  ds, [bp + 4]\n"
      "mov  bx, [bp + 6]\n"
      "mov  ax, [bx]\n"
      "pop  ds");
}
#endif

/*
#ifdef __HUGE__
static
void pokeb(unsigned seg, unsigned ofs, unsigned char val)
{
  *((unsigned char*)(seg * 16 + ofs)) = val;
}
#endif
#ifdef __SMALLER_C_16__
static
void pokeb(unsigned seg, unsigned ofs, unsigned char val)
{
  asm("push ds\n"
      "mov  ds, [bp + 4]\n"
      "mov  bx, [bp + 6]\n"
      "mov  al, [bp + 8]\n"
      "mov  [bx], al\n"
      "pop  ds");
}
#endif

#ifdef __HUGE__
static
void poke(unsigned seg, unsigned ofs, unsigned val)
{
  *((unsigned short*)(seg * 16 + ofs)) = val;
}
#endif
#ifdef __SMALLER_C_16__
static
void poke(unsigned seg, unsigned ofs, unsigned val)
{
  asm("push ds\n"
      "mov  ds, [bp + 4]\n"
      "mov  bx, [bp + 6]\n"
      "mov  ax, [bp + 8]\n"
      "mov  [bx], ax\n"
      "pop  ds");
}
#endif
*/

#ifdef __HUGE__
static
unsigned DosGetPspSeg(void)
{
  asm("mov ah, 0x51\n"
      "int 0x21\n"
      "movzx eax, bx");
}
#endif
#ifdef __SMALLER_C_16__
static
unsigned DosGetPspSeg(void)
{
  asm("mov ah, 0x51\n"
      "int 0x21\n"
      "mov ax, bx");
}
#endif

static char __ProgName__[128];
static char __ProgParams__[128];
static int __argc__ = 1;
static char* __argv__[64] = { "" };

static
void __setargs__(int* pargc, char*** pargv)
{
  unsigned psp = DosGetPspSeg();
  unsigned env = peek(psp, 0x2c);
  unsigned i, j, len;

  // First, try to extract the full program name.

  // Skip past the environment strings.
  i = 0;
  for (;;)
  {
    if ((peekb(env, i) | peekb(env, i + 1)) == 0)
    {
      i += 2;
      break;
    }
    ++i;
  }

  // Are there any other strings afterwards?
  if (peekb(env, i) | peekb(env, i + 1))
  {
    j = 0;
    i += 2;
    // The first one is the full program name.
    while ((__ProgName__[j++] = peekb(env, i++)) != 0);
    __argv__[0] = __ProgName__;
  }

  // Next, extract program arguments from the PSP.

  j = i = 0;
  len = peekb(psp, 0x80);
  while (i < len)
  {
    char c;
    if ((c = peekb(psp, 0x81 + i)) == ' ')
    {
      ++i;
      continue;
    }
    __argv__[__argc__++] = __ProgParams__ + j;
    __ProgParams__[j++] = c;
    ++i;
    while (i < len)
    {
      if ((c = peekb(psp, 0x81 + i)) == ' ')
        break;
      __ProgParams__[j++] = c;
      ++i;
    }
    __ProgParams__[j++] = 0;
  }

  *pargc = __argc__;
  *pargv = __argv__;
}

void __start__(void)
{
  int argc;
  char** argv;
  __setargs__(&argc, &argv);
  exit(main(argc, argv));
}

#endif // _DOS
