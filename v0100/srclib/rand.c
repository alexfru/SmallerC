/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#ifdef __SMALLER_C_32__
unsigned __Seed = 1;

int rand(void)
{
  __Seed = __Seed * 1103515245 + 12345;
  return (__Seed >> 16) & 0x7FFF;
}
#endif

#ifdef __SMALLER_C_16__
unsigned short __Seed[2] = { 1 };

static void helper(unsigned short seed[2])
{
  asm("mov bx, [bp+4]");
  #ifdef __SMALLER_C_8086__
  asm("mov ax, [bx]");
  asm("mov cx, 15245");
  asm("imul cx");
  asm("add ax, 12345");
  asm("mov [bx], ax");
  #else
  asm("mov eax, [bx]");
  asm("imul eax, eax, 1103515245");
  asm("add eax, 12345");
  asm("mov [bx], eax");
  #endif
}

int rand(void)
{
  helper(__Seed);
  return __Seed[1] & 0x7FFF;
}
#endif
