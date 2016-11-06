/*
  How to compile for DOS (huge/.EXE, unreal/.EXE):
    smlrcc -dosh isr.c -o isrh.exe
    smlrcc -dosu isr.c -o isru.exe
*/

#ifndef __HUGE__
#ifndef __UNREAL__
#error This program requires the huge or unreal mode(l)
#endif
#endif

#include <stdio.h>
#include <string.h>

static
unsigned peek16(unsigned seg, unsigned ofs)
{
  return *((unsigned short*)(seg * 16 + ofs));
}

static
void poke16(unsigned seg, unsigned ofs, unsigned val)
{
  *((unsigned short*)(seg * 16 + ofs)) = val;
}

static
void setvect(int intno, void __interrupt isr())
{
  unsigned addr = (unsigned)isr;
  unsigned ofs = (addr >> 20 << 4) | (addr & 0xF);
  unsigned seg = (addr >> 4) & 0xFFFF;
  asm("pushfd");
  asm("cli");
  poke16(0, intno * 4, ofs);
  poke16(0, intno * 4 + 2, seg);
  asm("popfd");
}

static
void __interrupt (*getvect(int intno))()
{
  asm("pushfd");
  asm("cli");
  unsigned ofs = peek16(0, intno * 4);
  unsigned seg = peek16(0, intno * 4 + 2);
  unsigned addr = (ofs & 0xF) | (seg << 4) | (ofs >> 4 << 20);
  asm("popfd");
  return (void __interrupt (*)())addr;
}

// Calls the old ISR from the new ISR
void callisr(void __interrupt isr())
{
  asm("pushfd");
  asm("cli");
  asm("rol dword [bp + 8], 12");
  asm("rol word [bp + 8], 4");
  asm("pushf");
  asm("call far [bp + 8]");
  asm("popfd");
}

struct INTREGS
{
  unsigned short gs, fs, es, ds;
  unsigned edi, esi, ebp, esp, ebx, edx, ecx, eax;
  unsigned short ss, ip, cs, flags;
};

struct TASKSTACK
{
  unsigned char stack[4096];
  struct INTREGS regs;
} task2stack;

struct INTREGS* taskSps[2];
unsigned curTaskIdx = 0;

void __interrupt (*orig_isr_irq0)();

void __interrupt isr_irq0(struct INTREGS** ppRegs)
{
  // **ppRegs (input/output values of registers) can be modified to handle software interrupts requested via the int instruction
  // *ppRegs (stack pointer) can be modified to return to a different location & implement preemptive scheduling
  static int cnt = 0;

  // Blink an asterisk
  cnt++;
  if (cnt < 9)
  {
    *(unsigned char*)0xB8000 = ' ';
    *(unsigned char*)0xB8001 = 0x1F;
  }
  else if (cnt < 18)
  {
    *(unsigned char*)0xB8000 = '*';
    *(unsigned char*)0xB8001 = 0x1F;
  }
  else
  {
    cnt = 0;
  }

  // Switch between the two tasks
  taskSps[curTaskIdx] = *ppRegs;
  curTaskIdx ^= 1;
  *ppRegs = taskSps[curTaskIdx];

  // Call the old ISR
  callisr(orig_isr_irq0);
}

void task2(void)
{
  memcpy((char*)0xB8000 + 2, "t a s k 2   c o u n t e r :   0 0 0 0 0 0 0 0 ", 46);

  // Continuously increment the counter
  for (;;)
  {
    int carry = 1;
    unsigned char* pdigit = (unsigned char*)(0xB8000 + 2 + 44);
    int n;
    for (n = 0; n < 8; n++)
    {
      int digit = *pdigit + carry;
      carry = digit > '9';
      if (carry)
        digit = '0';
      *pdigit = digit;
      pdigit -= 2;
    }
  }
}

void __interrupt fxniret()
{
  printf("\n%s() called\n", __func__);
}

int main(void)
{
  // Set mode 3 (80x25 color) to clear the screen and
  // force Windows XP to emulate the actual video device
  asm("mov ax, 3");
  asm("int 0x10");

  // Test callisr()
  callisr(fxniret);
  puts("Press Enter to continue.");
  getchar();

  // Set up task2's initial state
  task2stack.regs.cs = (unsigned)&task2 >> 4;
  task2stack.regs.ip = (unsigned)&task2 & 0xF;
  task2stack.regs.flags = 0x202;
  task2stack.regs.ss = (unsigned)&task2stack >> 4;
  task2stack.regs.esp = ((unsigned)&task2stack & 0xF) + (unsigned)&((struct TASKSTACK*)0)->regs.ss;
  taskSps[1] = &task2stack.regs;

  orig_isr_irq0 = getvect(8);

  puts("Press Enter to stop and exit.");

  setvect(8, isr_irq0);

  // Switch tasks until Enter is pressed
  getchar();

  setvect(8, orig_isr_irq0);
}
