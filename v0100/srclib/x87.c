/*
  Copyright (c) 2016, Alexey Frunze
  2-clause BSD license.
*/

#ifdef __SMALLER_C_32__

#ifdef __HUGE__
#define __HUGE_OR_UNREAL__
#endif
#ifdef __UNREAL__
#define __HUGE_OR_UNREAL__
#endif

#ifdef __HUGE_OR_UNREAL__
#define xbp "bp"
#define xsp "sp"
#else
#define xbp "ebp"
#define xsp "esp"
#endif

void __x87init(void)
{
  // Mask all exceptions, set rounding to nearest even and precision to 64 bits.
  // TBD??? Actually check for x87???
  asm("fninit");
}

float __floatsisf(int i)
{
  asm
  (
  "fild dword ["xbp"+8]\n"
  "fstp dword ["xbp"+8]\n"
  "mov  eax, ["xbp"+8]"
  );
}

float __floatunsisf(unsigned i)
{
  asm
  (
  "push dword 0\n"
  "push dword ["xbp"+8]\n"
  "fild qword ["xbp"-8]\n" // load 32-bit unsigned int as 64-bit signed int
  "add  "xsp", 8\n"
  "fstp dword ["xbp"+8]\n"
  "mov  eax, ["xbp"+8]"
  );
}

int __fixsfsi(float f)
{
  asm
  (
  "sub    "xsp", 4\n"
  "fnstcw ["xbp"-2]\n" // save rounding
  "mov    ax, ["xbp"-2]\n"
  "mov    ah, 0x0c\n" // rounding towards 0 (AKA truncate) since we don't have fisttp
  "mov    ["xbp"-4], ax\n"
  "fld    dword ["xbp"+8]\n"
  "fldcw  ["xbp"-4]\n" // rounding = truncation
  "fistp  dword ["xbp"+8]\n"
  "fldcw  ["xbp"-2]\n" // restore rounding
  "add    "xsp", 4\n"
  "mov    eax, ["xbp"+8]"
  );
}

unsigned __fixunssfsi(float f)
{
  asm
  (
  "sub    "xsp", 12\n"
  "fnstcw ["xbp"-2]\n" // save rounding
  "mov    ax, ["xbp"-2]\n"
  "mov    ah, 0x0c\n" // rounding towards 0 (AKA truncate) since we don't have fisttp
  "mov    ["xbp"-4], ax\n"
  "fld    dword ["xbp"+8]\n"
  "fldcw  ["xbp"-4]\n" // rounding = truncation
  "fistp  qword ["xbp"-12]\n" // store 64-bit signed int
  "fldcw  ["xbp"-2]\n" // restore rounding
  "mov    eax, ["xbp"-12]\n" // take low 32 bits
  "add    "xsp", 12"
  );
}

float __addsf3(float a, float b)
{
  asm
  (
  "fld  dword ["xbp"+8]\n"
  "fadd dword ["xbp"+12]\n"
  "fstp dword ["xbp"+8]\n"
  "mov  eax, ["xbp"+8]"
  );
}

float __subsf3(float a, float b)
{
  asm
  (
  "fld  dword ["xbp"+8]\n"
  "fsub dword ["xbp"+12]\n"
  "fstp dword ["xbp"+8]\n"
  "mov  eax, ["xbp"+8]"
  );
}

float __negsf2(float f)
{
  asm
  (
  "mov eax, ["xbp"+8]\n"
  "xor eax, 0x80000000"
  );
}

float __mulsf3(float a, float b)
{
  asm
  (
  "fld  dword ["xbp"+8]\n"
  "fmul dword ["xbp"+12]\n"
  "fstp dword ["xbp"+8]\n"
  "mov  eax, ["xbp"+8]"
  );
}

float __divsf3(float a, float b)
{
  asm
  (
  "fld  dword ["xbp"+8]\n"
  "fdiv dword ["xbp"+12]\n"
  "fstp dword ["xbp"+8]\n"
  "mov  eax, ["xbp"+8]"
  );
}

float __lesf2(float a, float b)
{
  asm
  (
  "fld      dword ["xbp"+12]\n"
  "fld      dword ["xbp"+8]\n"
  "fucompp\n"
  "fstsw    ax\n" // must use these moves since we don't have fucomip
  "sahf\n"
  "jnp      .ordered\n"
  "mov      eax, +1\n" // return +1 if either a or b (or both) is a NaN
  "jmp      .done\n"
  ".ordered:\n"
  "jnz      .unequal\n"
  "xor      eax, eax\n" // return 0 if a == b
  "jmp      .done\n"
  ".unequal:\n"
  "sbb      eax, eax\n"
  "jc       .done\n"    // return -1 if a < b
  "inc      eax\n"      // return +1 if a > b
  ".done:"
  );
}

float __gesf2(float a, float b)
{
  asm
  (
  "fld      dword ["xbp"+12]\n"
  "fld      dword ["xbp"+8]\n"
  "fucompp\n"
  "fstsw    ax\n" // must use these moves since we don't have fucomip
  "sahf\n"
  "jnp      .ordered\n"
  "mov      eax, -1\n" // return -1 if either a or b (or both) is a NaN
  "jmp      .done\n"
  ".ordered:\n"
  "jnz      .unequal\n"
  "xor      eax, eax\n" // return 0 if a == b
  "jmp      .done\n"
  ".unequal:\n"
  "sbb      eax, eax\n"
  "jc       .done\n"    // return -1 if a < b
  "inc      eax\n"      // return +1 if a > b
  ".done:"
  );
}

#endif
