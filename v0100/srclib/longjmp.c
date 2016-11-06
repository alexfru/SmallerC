/*
  Copyright (c) 2014-2016, Alexey Frunze
  2-clause BSD license.
*/
#include <setjmp.h>
/*
typedef struct
{
  unsigned xip;    // ip / cs:ip / eip
  unsigned xflags; // (e)flags
  unsigned xbp;    // (e)bp
  unsigned xsp;    // (e)sp
} jmp_buf[1];
*/

#ifdef __SMALLER_C_16__

int setjmp(jmp_buf jb)
{
  asm("mov bx, [bp+4]"); // jb

  // ip
  asm("mov ax, [bp+2]"); // return address
  asm("mov [bx], ax");
  // flags (mainly for IF)
  asm("pushf");
  asm("pop word [bx+2]");
  // bp
  asm("mov ax, [bp]"); // caller's bp
  asm("mov [bx+4], ax");
  // sp
  asm("lea ax, [bp+2*2]"); // caller's sp
  asm("mov [bx+6], ax");

  // return 0
  asm("xor ax, ax");
}

void longjmp(jmp_buf jb, int val)
{
  asm("mov ax, [bp+6]"); // val
  // if val is 0, make it 1
  asm("or ax, ax");
  asm("setz bl");
  asm("or al, bl");

  asm("mov bx, [bp+4]"); // jb

  // sp
  asm("mov sp, [bx+6]");
  // bp
  asm("mov bp, [bx+4]");
  // flags (mainly for IF)
  asm("push word [bx+2]");
  // cs
  asm("push cs");
  // ip
  asm("push word [bx]");

  // return val
  asm("iret");
}

#endif // __SMALLER_C_16__

#ifdef __SMALLER_C_32__

#ifdef __HUGE__

int setjmp(jmp_buf jb)
{
  asm("mov ebx, [bp+8]\n" // jb
      "ror ebx, 4\n"
      "mov ds, bx\n"
      "shr ebx, 28");

  // cs:ip in xip
  asm("mov eax, [bp+4]"); // return address
  asm("mov [bx], eax");
  // flags (mainly for IF)
  asm("pushfd");
  asm("pop dword [bx+4]");
  // ebp
  asm("mov eax, [bp]"); // caller's ebp
  asm("mov [bx+8], eax");
  // sp
  asm("lea eax, [bp+2*4]"); // caller's sp
  asm("mov [bx+12], eax");

  // return 0
  asm("xor eax, eax");
}

void longjmp(jmp_buf jb, int val)
{
  asm("mov eax, [bp+12]"); // val
  // if val is 0, make it 1
  asm("or eax, eax");
  asm("setz bl");
  asm("or al, bl");

  asm("mov ebx, [bp+8]\n" // jb
      "ror ebx, 4\n"
      "mov ds, bx\n"
      "shr ebx, 28");

  // sp
  asm("mov sp, [bx+12]");
  // ebp
  asm("mov ebp, [bx+8]");
  // flags (mainly for IF)
  asm("push word [bx+4]");
  // cs:ip in xip
  asm("push dword [bx]");

  // return val
  asm("iret");
}

#else // and now __SMALLER_C_32__, not __HUGE__

#ifdef __UNREAL__

int setjmp(jmp_buf jb)
{
  asm("mov ebx, [bp+8]"); // jb

  // cs:ip in xip
  asm("mov eax, [bp+4]"); // return address
  asm("mov [ebx], eax");
  // flags (mainly for IF)
  asm("pushfd");
  asm("pop dword [ebx+4]");
  // ebp
  asm("mov eax, [bp]"); // caller's ebp
  asm("mov [ebx+8], eax");
  // sp
  asm("lea eax, [bp+2*4]"); // caller's sp
  asm("mov [ebx+12], eax");

  // return 0
  asm("xor eax, eax");
}

void longjmp(jmp_buf jb, int val)
{
  asm("mov eax, [bp+12]"); // val
  // if val is 0, make it 1
  asm("or eax, eax");
  asm("setz bl");
  asm("or al, bl");

  asm("mov ebx, [bp+8]"); // jb

  // sp
  asm("mov sp, [ebx+12]");
  // ebp
  asm("mov ebp, [ebx+8]");
  // flags (mainly for IF)
  asm("push word [ebx+4]");
  // cs:ip in xip
  asm("push dword [ebx]");

  // return val
  asm("iret");
}

#else // and now __SMALLER_C_32__, not __HUGE__, not __UNREAL__

int setjmp(jmp_buf jb)
{
  asm("mov ebx, [ebp+8]"); // jb

  // eip
  asm("mov eax, [ebp+4]"); // return address
  asm("mov [ebx], eax");
  // flags (mainly for IF)
  asm("pushfd");
  asm("pop dword [ebx+4]");
  // ebp
  asm("mov eax, [ebp]"); // caller's ebp
  asm("mov [ebx+8], eax");
  // esp
  asm("lea eax, [ebp+4*2]"); // caller's esp
  asm("mov [ebx+12], eax");

  // return 0
  asm("xor eax, eax");
}

void longjmp(jmp_buf jb, int val)
{
  asm("mov eax, [ebp+12]"); // val
  // if val is 0, make it 1
  asm("or eax, eax");
  asm("setz bl");
  asm("or al, bl");

  asm("mov ebx, [ebp+8]"); // jb

  // esp
  asm("mov esp, [ebx+12]");
  // ebp
  asm("mov ebp, [ebx+8]");
  // flags (mainly for IF)
  asm("push dword [ebx+4]");
  // cs
  asm("push cs");
  // eip
  asm("push dword [ebx]");

  // return val
  asm("iretd");
}

#endif // __UNREAL__

#endif // __HUGE__

#endif // __SMALLER_C_32__
