/*
Copyright (c) 2013-2016, Alexey Frunze
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*****************************************************************************/
/*                                                                           */
/*                             minimal stdlibc                               */
/*                                                                           */
/*            Just enough code for Smaller C to compile into a               */
/*               16/32-bit DOS/Windows/Linux/RetroBSD "EXE".                 */
/*                                                                           */
/*****************************************************************************/

#ifndef __SMALLER_C__
#error must be compiled with Smaller C
#endif

#ifndef __SMALLER_C_SCHAR__
#ifndef __SMALLER_C_UCHAR__
#error __SMALLER_C_SCHAR__ or __SMALLER_C_UCHAR__ must be defined
#endif
#endif

#ifndef __SMALLER_C_16__
#ifndef __SMALLER_C_32__
#error __SMALLER_C_16__ or __SMALLER_C_32__ must be defined
#endif
#endif

#ifndef _RETROBSD
#ifndef _LINUX
#ifndef _WIN32
#ifndef _DOS
#define _DOS
#endif
#endif
#endif
#endif

#define NULL 0
#define EOF (-1)
#define FILE void

extern int main(int argc, char** argv);
void exit(int);

#ifdef __SMALLER_C_32__
extern void __x87init(void);
#endif

#ifdef _RETROBSD
void __start__(int argc, char** argv)
{
  exit(main(argc, argv));
}
#else
#ifdef _LINUX
void __start__(int argc, char** argv)
{
  __x87init();
  exit(main(argc, argv));
}
#else
void __setargs__(int* pargc, char*** pargv);

void __start__(void)
{
  int argc;
  char** argv;
  __setargs__(&argc, &argv);
#ifdef __SMALLER_C_32__
  __x87init();
#endif
  exit(main(argc, argv));
}
#endif
#endif

unsigned char __chartype__[1 + 256] =
{
  0x00, // for EOF=-1
  0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01, 0x01,0x03,0x03,0x03,0x03,0x03,0x01,0x01,
  0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01, 0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
  0x02,0x04,0x04,0x04,0x04,0x04,0x04,0x04, 0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,
  0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08, 0x08,0x08,0x04,0x04,0x04,0x04,0x04,0x04,
  0x04,0x50,0x50,0x50,0x50,0x50,0x50,0x10, 0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
  0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10, 0x10,0x10,0x10,0x04,0x04,0x04,0x04,0x04,
  0x04,0x60,0x60,0x60,0x60,0x60,0x60,0x20, 0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
  0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20, 0x20,0x20,0x20,0x04,0x04,0x04,0x04,0x01,
};

int isspace(int c)
{
  return __chartype__[c + 1] & 0x02;
}

int isdigit(int c)
{
  return __chartype__[c + 1] & 0x08;
}

int isalpha(int c)
{
  return __chartype__[c + 1] & 0x30;
}

int isalnum(int c)
{
  return __chartype__[c + 1] & 0x38;
}

int atoi(char* s)
{
  // simplified version
  int r = 0;
  int neg = 0;
  if (*s == '-')
  {
    neg = 1;
    ++s;
  }
  else if (*s == '+')
  {
    ++s;
  }
  while (isdigit(*s & 0xFFu))
    r = r * 10u + *s++ - '0';
  if (neg)
    r = -r;
  return r;
}

unsigned strlen(char* str)
{
#ifndef __SMALLER_C_16__
  char* s;

  if (str == NULL)
    return 0;

  for (s = str; *s; ++s);

  return s - str;
#else
  asm("mov di, [bp+4]\n"
      "mov cx, -1\n"
      "xor al, al\n"
      "cld\n"
      "repnz scasb\n"
      "mov ax, cx\n"
      "not ax\n"
      "dec ax");
#endif
}

char* strcpy(char* dst, char* src)
{
#ifndef __SMALLER_C_16__
  char* p = dst;

  while ((*p++ = *src++) != 0);
#else
  asm("mov di, [bp+6]\n"
      "mov si, di\n"
      "mov cx, -1\n"
      "xor al, al\n"
      "cld\n"
      "repnz scasb\n"
      "not cx\n"
      "mov di, [bp+4]\n"
      "rep movsb");
#endif

  return dst;
}

char* strchr(char* s, int c)
{
#ifndef __SMALLER_C_16__
  char ch = c;

  while (*s)
  {
    if (*s == ch)
      return s;
    ++s;
  }

  if (!ch)
    return s;

  return NULL;
#else
  asm("mov si, [bp+4]\n"
      "mov bl, [bp+6]\n"
      "xor ax, ax\n"
      "cld\n"
      "strchrlp:\n"
      "lodsb\n"
      "cmp al, bl\n"
      "je strchrmch\n"
      "or al, al\n"
      "jnz strchrlp\n"
      "jmp strchrend");
  asm("strchrmch:\n"
      "lea ax, [si-1]\n"
      "strchrend:");
#endif
}

int strcmp(char* s1, char* s2)
{
#ifndef __SMALLER_C_16__
  while (*s1 == *s2)
  {
    if (!*s1)
      return 0;
    ++s1;
    ++s2;
  }

  return (*s1 & 0xFF) - (*s2 & 0xFF);
#else
  asm("mov di, [bp+6]\n"
      "mov si, di\n"
      "mov cx, -1\n"
      "xor ax, ax\n"
      "mov bx, ax\n"
      "cld\n"
      "repnz scasb\n"
      "not cx");
  asm("mov di, [bp+4]\n"
      "repe cmpsb\n"
      "mov al, [di-1]\n"
      "mov bl, [si-1]\n"
      "sub ax, bx");
#endif
}

int strncmp(char* s1, char* s2, unsigned n)
{
#ifndef __SMALLER_C_16__
  if (!n)
    return 0;

  do
  {
    if (*s1 != *s2++)
      return (*s1 & 0xFF) - (*--s2 & 0xFF);
    if (!*s1++)
      break;
  } while (--n);

  return 0;
#else
  asm("mov cx, [bp+8]\n"
      "xor ax, ax\n"
      "jcxz strncmpend\n"
      "mov bx, ax\n"
      "mov di, [bp+6]\n"
      "mov si, di\n"
      "cld\n"
      "repnz scasb\n"
      "sub cx, [bp+8]\n"
      "neg cx");
  asm("mov di, [bp+4]\n"
      "repe cmpsb\n"
      "mov al, [di-1]\n"
      "mov bl, [si-1]\n"
      "sub ax, bx\n"
      "strncmpend:");
#endif
}

void* memmove(void* dst, void* src, unsigned n)
{
#ifndef __SMALLER_C_16__
  char* d = dst;
  char* s = src;

  if (s < d)
  {
    s += n;
    d += n;
    while (n--)
      *--d = *--s;
  }
  else
  {
    while (n--)
      *d++ = *s++;
  }
#else
  if (src < dst)
  {
    asm("mov di, [bp+4]\n"
        "mov si, [bp+6]\n"
        "mov cx, [bp+8]\n"
        "add di, cx\n"
        "dec di\n"
        "add si, cx\n"
        "dec si\n"
        "std\n"
        "rep movsb");
  }
  else
  {
    asm("mov di, [bp+4]\n"
        "mov si, [bp+6]\n"
        "mov cx, [bp+8]\n"
        "cld\n"
        "rep movsb");
  }
#endif
  return dst;
}

void* memcpy(void* dst, void* src, unsigned n)
{
#ifndef __SMALLER_C_16__
  char* p1 = dst;
  char* p2 = src;

  while (n--)
    *p1++ = *p2++;
#else
  asm("mov di, [bp+4]\n"
      "mov si, [bp+6]\n"
      "mov cx, [bp+8]\n"
      "shr cx, 1\n"
      "cld\n"
      "rep movsw\n"
      "rcl cx, 1\n"
      "rep movsb");
#endif
  return dst;
}

void* memset(void* s, int c, unsigned n)
{
#ifndef __SMALLER_C_16__
  char* p = s;

  while (n--)
    *p++ = c;
#else
  asm("mov di, [bp+4]\n"
      "mov al, [bp+6]\n"
      "mov ah, al\n"
      "mov cx, [bp+8]\n"
      "shr cx, 1\n"
      "cld\n"
      "rep stosw\n"
      "rcl cx, 1\n"
      "rep stosb");
#endif
  return s;
}

#ifdef __SMALLER_C_32__
int memcmp(void* s1, void* s2, unsigned n)
{
  if (n)
  {
    unsigned char *p1 = s1, *p2 = s2;
    do
    {
      if (*p1++ != *p2++)
        return (*--p1 - *--p2);
    } while (--n);
  }
  return 0;
}
#endif

int fputc(int c, FILE* stream);
int putchar(int c);

int __putchar__(char** buf, FILE* stream, int c)
{
  if (buf)
  {
    *(*buf)++ = c;
  }
  else if (stream)
  {
    fputc(c, stream);
  }
  else
  {
    putchar(c);
  }
  return 1;
}

int __vsprintf__(char** buf, FILE* stream, char* fmt, void* vl)
{
  // Simplified version!
  // No I/O error checking!
  int* pp = vl;
  int cnt = 0;
  char* p;
  char* phex;
  char s[1/*sign*/+10/*magnitude*/+1/*\0*/]; // up to 11 octal digits in 32-bit numbers
  char* pc;
  int n, sign, msign;
  int minlen, len;
  int leadchar = ' ';

  for (p = fmt; *p != '\0'; ++p)
  {
    if (*p != '%' || p[1] == '%')
    {
      __putchar__(buf, stream, *p);
      p = p + (*p == '%');
      ++cnt;
      continue;
    }
    ++p;
    minlen = 0;
    msign = 0;
    if (*p == '+') { msign = 1; ++p; }
    else if (*p == '-') { msign = -1; ++p; }
    if (isdigit(*p & 0xFFu))
    {
      if (*p == '0')
        leadchar = '0';
      else
        leadchar = ' ';
      while (isdigit(*p & 0xFFu))
        minlen = minlen * 10 + *p++ - '0';
      if (msign < 0)
        minlen = -minlen;
      msign = 0;
    }
    if (!msign)
    {
      if (*p == '+') { msign = 1; ++p; }
      else if (*p == '-') { msign = -1; ++p; }
    }
    phex = "0123456789abcdef";
    switch (*p)
    {
    case 'c':
      while (minlen > 1) { __putchar__(buf, stream, ' '); ++cnt; --minlen; }
      __putchar__(buf, stream, *pp++);
      while (-minlen > 1) { __putchar__(buf, stream, ' '); ++cnt; ++minlen; }
      ++cnt;
      break;
    case 's':
      pc = (char*)*pp++;
      len = 0;
      if (pc)
        len = strlen(pc);
      while (minlen > len) { __putchar__(buf, stream, ' '); ++cnt; --minlen; }
      if (len)
        while (*pc != '\0')
        {
          __putchar__(buf, stream, *pc++);
          ++cnt;
        }
      while (-minlen > len) { __putchar__(buf, stream, ' '); ++cnt; ++minlen; }
      break;
    case 'i':
    case 'd':
      pc = &s[sizeof s - 1];
      *pc = '\0';
      len = 0;
      n = *pp++;
      sign = 1 - 2 * (n < 0);
      do
      {
        *--pc = '0' + (n - n / 10 * 10) * sign;
        n = n / 10;
        ++len;
      } while (n);
      if (sign < 0)
      {
        *--pc = '-';
        ++len;
      }
      else if (msign > 0)
      {
        *--pc = '+';
        ++len;
        msign = 0;
      }
      while (minlen > len) { __putchar__(buf, stream, leadchar); ++cnt; --minlen; }
      while (*pc != '\0')
      {
        __putchar__(buf, stream, *pc++);
        ++cnt;
      }
      while (-minlen > len) { __putchar__(buf, stream, ' '); ++cnt; ++minlen; }
      break;
    case 'u':
      pc = &s[sizeof s - 1];
      *pc = '\0';
      len = 0;
      n = *pp++;
      do
      {
        unsigned nn = n;
        *--pc = '0' + nn % 10;
        n = nn / 10;
        ++len;
      } while (n);
      if (msign > 0)
      {
        *--pc = '+';
        ++len;
        msign = 0;
      }
      while (minlen > len) { __putchar__(buf, stream, leadchar); ++cnt; --minlen; }
      while (*pc != '\0')
      {
        __putchar__(buf, stream, *pc++);
        ++cnt;
      }
      while (-minlen > len) { __putchar__(buf, stream, ' '); ++cnt; ++minlen; }
      break;
    case 'X':
      phex = "0123456789ABCDEF";
      // fallthrough
    case 'p':
    case 'x':
      pc = &s[sizeof s - 1];
      *pc = '\0';
      len = 0;
      n = *pp++;
      do
      {
        *--pc = phex[n & 0xF];
        n = (n >> 4) & ((1 << (8 * sizeof n - 4)) - 1); // drop sign-extended bits
        ++len;
      } while (n);
      while (minlen > len) { __putchar__(buf, stream, leadchar); ++cnt; --minlen; }
      while (*pc != '\0')
      {
        __putchar__(buf, stream, *pc++);
        ++cnt;
      }
      while (-minlen > len) { __putchar__(buf, stream, ' '); ++cnt; ++minlen; }
      break;
    case 'o':
      pc = &s[sizeof s - 1];
      *pc = '\0';
      len = 0;
      n = *pp++;
      do
      {
        *--pc = '0' + (n & 7);
        n = (n >> 3) & ((1 << (8 * sizeof n - 3)) - 1); // drop sign-extended bits
        ++len;
      } while (n);
      while (minlen > len) { __putchar__(buf, stream, leadchar); ++cnt; --minlen; }
      while (*pc != '\0')
      {
        __putchar__(buf, stream, *pc++);
        ++cnt;
      }
      while (-minlen > len) { __putchar__(buf, stream, ' '); ++cnt; ++minlen; }
      break;
    default:
      return -1;
    }
  }

  return cnt;
}

int vprintf(char* fmt, void* vl)
{
  return __vsprintf__(NULL, NULL, fmt, vl);
}

int printf(char* fmt, ...)
{
  void** pp = (void**)&fmt;
  return vprintf(fmt, pp + 1);
}

int vsprintf(char* buf, char* fmt, void* vl)
{
  return __vsprintf__(&buf, NULL, fmt, vl);
}

int sprintf(char* buf, char* fmt, ...)
{
  void** pp = (void**)&fmt;
  return vsprintf(buf, fmt, pp + 1);
}

#ifdef _DOS
void pokeb(unsigned seg, unsigned ofs, unsigned char val)
{
#ifndef __SMALLER_C_16__
  *((unsigned char*)(seg * 16 + ofs)) = val;
#else
  asm("push ds\n"
      "mov  ds, [bp + 4]\n"
      "mov  bx, [bp + 6]\n"
      "mov  al, [bp + 8]\n"
      "mov  [bx], al\n"
      "pop  ds");
#endif
}

unsigned char peekb(unsigned seg, unsigned ofs)
{
#ifndef __SMALLER_C_16__
  return *((unsigned char*)(seg * 16 + ofs));
#else
  asm("push ds\n"
      "mov  ds, [bp + 4]\n"
      "mov  bx, [bp + 6]\n"
      "mov  al, [bx]\n"
      "mov  ah, 0\n"
      "pop  ds");
#endif
}

void poke(unsigned seg, unsigned ofs, unsigned val)
{
#ifndef __SMALLER_C_16__
  *((unsigned short*)(seg * 16 + ofs)) = val;
#else
  asm("push ds\n"
      "mov  ds, [bp + 4]\n"
      "mov  bx, [bp + 6]\n"
      "mov  ax, [bp + 8]\n"
      "mov  [bx], ax\n"
      "pop  ds");
#endif
}

unsigned peek(unsigned seg, unsigned ofs)
{
#ifndef __SMALLER_C_16__
  return *((unsigned short*)(seg * 16 + ofs));
#else
  asm("push ds\n"
      "mov  ds, [bp + 4]\n"
      "mov  bx, [bp + 6]\n"
      "mov  ax, [bx]\n"
      "pop  ds");
#endif
}
#endif // _DOS

#ifdef _WIN32
#define INVALID_HANDLE_VALUE  (-1)
#define GENERIC_WRITE         0x40000000u
#define GENERIC_READ          0x80000000u
#define FILE_SHARE_READ       1
#define CREATE_ALWAYS         2
#define OPEN_EXISTING         3
#define FILE_ATTRIBUTE_NORMAL 0x80
#define STD_OUTPUT_HANDLE     (-11u)

extern void (*_imp__ExitProcess)(unsigned ExitCode);
void ExitProcess(unsigned ExitCode)
{
  asm("push dword [ebp+8]\n"
      "call [__imp__ExitProcess]");
}

extern char* (*_imp__GetCommandLineA)(void);
char* GetCommandLineA(void)
{
  asm("call [__imp__GetCommandLineA]");
}

extern unsigned (*_imp__GetStdHandle)(unsigned nStdHandle);
unsigned GetStdHandle(unsigned nStdHandle)
{
  asm("push dword [ebp+8]\n"
      "call [__imp__GetStdHandle]");
}

extern unsigned (*_imp__CreateFileA)(char* FileName,
                                     unsigned DesiredAccess,
                                     unsigned ShareMode,
                                     void* SecurityAttributes,
                                     unsigned CreationDisposition,
                                     unsigned FlagsAndAttributes,
                                     unsigned TemplateFile);
unsigned CreateFileA(char* FileName,
                     unsigned DesiredAccess,
                     unsigned ShareMode,
                     void* SecurityAttributes,
                     unsigned CreationDisposition,
                     unsigned FlagsAndAttributes,
                     unsigned TemplateFile)
{
  asm("push dword [ebp+32]\n"
      "push dword [ebp+28]\n"
      "push dword [ebp+24]\n"
      "push dword [ebp+20]");
  asm("push dword [ebp+16]\n"
      "push dword [ebp+12]\n"
      "push dword [ebp+8]\n"
      "call [__imp__CreateFileA]");
}

extern int (*_imp__CloseHandle)(unsigned Handle);
int CloseHandle(unsigned Handle)
{
  asm("push dword [ebp+8]\n"
      "call [__imp__CloseHandle]");
}

extern int (*_imp__ReadFile)(unsigned Handle,
                             void* Buffer,
                             unsigned NumberOfBytesToRead,
                             unsigned* NumberOfBytesRead,
                             void* Overlapped);
int ReadFile(unsigned Handle,
             void* Buffer,
             unsigned NumberOfBytesToRead,
             unsigned* NumberOfBytesRead,
             void* Overlapped)
{
  asm("push dword [ebp+24]\n"
      "push dword [ebp+20]\n"
      "push dword [ebp+16]\n"
      "push dword [ebp+12]\n"
      "push dword [ebp+8]\n"
      "call [__imp__ReadFile]");
}

extern int (*_imp__WriteFile)(unsigned Handle,
                              void* Buffer,
                              unsigned NumberOfBytesToWrite,
                              unsigned* NumberOfBytesWritten,
                              void* Overlapped);
int WriteFile(unsigned Handle,
              void* Buffer,
              unsigned NumberOfBytesToWrite,
              unsigned* NumberOfBytesWritten,
              void* Overlapped)
{
  asm("push dword [ebp+24]\n"
      "push dword [ebp+20]\n"
      "push dword [ebp+16]\n"
      "push dword [ebp+12]\n"
      "push dword [ebp+8]\n"
      "call [__imp__WriteFile]");
}

extern unsigned (*_imp__SetFilePointer)(unsigned Handle,
                                        int lDistanceToMove,
                                        int* lpDistanceToMoveHigh,
                                        unsigned dwMoveMethod);
unsigned SetFilePointer(unsigned Handle,
                        int lDistanceToMove,
                        int* lpDistanceToMoveHigh,
                        unsigned dwMoveMethod)
{
  asm("push dword [ebp+20]\n"
      "push dword [ebp+16]\n"
      "push dword [ebp+12]\n"
      "push dword [ebp+8]\n"
      "call [__imp__SetFilePointer]");
}
#endif // _WIN32

#ifdef _RETROBSD
// flags for RetroBSD's open():
#define O_RDONLY 0x0000
#define O_WRONLY 0x0001
#define O_RDWR   0x0002
#define O_APPEND 0x0008
#define O_CREAT  0x0200
#define O_TRUNC  0x0400
#define O_TEXT   0x0000
#define O_BINARY 0x0000
#endif

int OsCreateOrTruncate(char* name)
{
#ifdef _RETROBSD
  int fd;
  int oflags = O_TRUNC | O_CREAT | O_WRONLY;
  int mode = 0664; // rw-rw-r--
  asm volatile ("move $4, %1\n"
                "move $5, %2\n"
                "move $6, %3\n"
                "syscall 5\n" // SYS_open
                "nop\n"
                "nop\n"
                "move %0, $2\n"
                : "=r" (fd)
                : "r" (name), "r" (oflags), "r" (mode)
                : "$2", "$4", "$5", "$6");
  if (fd < 0)
    fd = -1;
  return fd;
#else
#ifdef _LINUX
  asm("mov eax, 5\n" // sys_open
      "mov ebx, [ebp + 8]\n"
      "mov ecx, 0x241\n" // truncate if exists, else create, writing only
      "mov edx, 664o\n" // rw-rw-r--
      "int 0x80\n"
      "mov ebx, eax\n"
      "sar ebx, 31\n"
      "or  eax, ebx");
#else
#ifdef _WIN32
  unsigned h = CreateFileA(name,
                           GENERIC_WRITE,
                           FILE_SHARE_READ,
                           NULL,
                           CREATE_ALWAYS,
                           FILE_ATTRIBUTE_NORMAL,
                           NULL);
  return h;
#else
#ifndef __SMALLER_C_16__
  asm("mov ah, 0x3c\n"
      "xor cx, cx\n"
      "mov edx, [bp + 8]\n"
      "ror edx, 4\n"
      "mov ds, dx\n"
      "shr edx, 28\n"
      "int 0x21\n"
      "sbb ebx, ebx\n"
      "and eax, 0xffff\n"
      "or  eax, ebx");
#else
  asm("mov ah, 0x3c\n"
      "xor cx, cx\n"
      "mov dx, [bp + 4]\n"
      "int 0x21\n"
      "sbb bx, bx\n"
      "or  ax, bx");
#endif
#endif
#endif
#endif
}

int OsOpen(char* name)
{
#ifdef _RETROBSD
  int fd;
  int oflags = O_RDONLY;
  int mode = 0444; // r--r--r-- (ignored)
  asm volatile ("move $4, %1\n"
                "move $5, %2\n"
                "move $6, %3\n"
                "syscall 5\n" // SYS_open
                "nop\n"
                "nop\n"
                "move %0, $2\n"
                : "=r" (fd)
                : "r" (name), "r" (oflags), "r" (mode)
                : "$2", "$4", "$5", "$6");
  if (fd < 0)
    fd = -1;
  return fd;
#else
#ifdef _LINUX
  asm("mov eax, 5\n" // sys_open
      "mov ebx, [ebp + 8]\n"
      "mov ecx, 0\n" // reading only
      "mov edx, 444o\n" // r--r--r-- (ignored)
      "int 0x80\n"
      "mov ebx, eax\n"
      "sar ebx, 31\n"
      "or  eax, ebx");
#else
#ifdef _WIN32
  unsigned h = CreateFileA(name,
                           GENERIC_READ,
                           FILE_SHARE_READ,
                           NULL,
                           OPEN_EXISTING,
                           FILE_ATTRIBUTE_NORMAL,
                           NULL);
  return h;
#else
#ifndef __SMALLER_C_16__
  asm("mov ax, 0x3d00\n"
      "mov edx, [bp + 8]\n"
      "ror edx, 4\n"
      "mov ds, dx\n"
      "shr edx, 28\n"
      "int 0x21\n"
      "sbb ebx, ebx\n"
      "and eax, 0xffff\n"
      "or  eax, ebx");
#else
  asm("mov ax, 0x3d00\n"
      "mov dx, [bp + 4]\n"
      "int 0x21\n"
      "sbb bx, bx\n"
      "or  ax, bx");
#endif
#endif
#endif
#endif
}

int OsClose(int fd)
{
#ifdef _RETROBSD
  int err;
  asm volatile ("move $4, %1\n"
                "syscall 6\n" // SYS_close
                "nop\n"
                "nop\n"
                "move %0, $2\n"
                : "=r" (err)
                : "r" (fd)
                : "$2", "$4");
  return err;
#else
#ifdef _LINUX
  asm("mov eax, 6\n" // sys_close
      "mov ebx, [ebp + 8]\n"
      "int 0x80");
#else
#ifdef _WIN32
  return CloseHandle(fd) ? 0 : -1;
#else
#ifndef __SMALLER_C_16__
  asm("mov ah, 0x3e\n"
      "mov bx, [bp + 8]\n"
      "int 0x21\n"
      "sbb eax, eax");
#else
  asm("mov ah, 0x3e\n"
      "mov bx, [bp + 4]\n"
      "int 0x21\n"
      "sbb ax, ax");
#endif
#endif
#endif
#endif
}

int OsRead(int fd, void* p, unsigned s)
{
#ifdef _RETROBSD
  int sz;
  asm volatile ("move $4, %1\n"
                "move $5, %2\n"
                "move $6, %3\n"
                "syscall 3\n" // SYS_read
                "nop\n"
                "nop\n"
                "move %0, $2\n"
                : "=r" (sz)
                : "r" (fd), "r" (p), "r" (s)
                : "$2", "$4", "$5", "$6", "memory");
  return sz;
#else
#ifdef _LINUX
  asm("mov eax, 3\n" // sys_read
      "mov ebx, [ebp + 8]\n"
      "mov ecx, [ebp + 12]\n"
      "mov edx, [ebp + 16]\n"
      "int 0x80");
#else
#ifdef _WIN32
  unsigned NumberOfBytesRead;
  ReadFile(fd,
           p,
           s,
           &NumberOfBytesRead,
           NULL);
  return NumberOfBytesRead;
#else
#ifndef __SMALLER_C_16__
  asm("mov ah, 0x3f\n"
      "mov bx, [bp + 8]\n"
      "mov edx, [bp + 12]\n"
      "ror edx, 4\n"
      "mov ds, dx\n"
      "shr edx, 28\n"
      "mov cx, [bp + 16]\n"
      "int 0x21");
  asm("sbb ebx, ebx\n"
      "and eax, 0xffff\n"
      "or  eax, ebx");
#else
  asm("mov ah, 0x3f\n"
      "mov bx, [bp + 4]\n"
      "mov dx, [bp + 6]\n"
      "mov cx, [bp + 8]\n"
      "int 0x21\n"
      "sbb bx, bx\n"
      "or  ax, bx");
#endif
#endif
#endif
#endif
}

int OsWrite(int fd, void* p, unsigned s)
{
#ifdef _RETROBSD
  int sz;
  asm volatile ("move $4, %1\n"
                "move $5, %2\n"
                "move $6, %3\n"
                "syscall 4\n" // SYS_write
                "nop\n"
                "nop\n"
                "move %0, $2\n"
                : "=r" (sz)
                : "r" (fd), "r" (p), "r" (s)
                : "$2", "$4", "$5", "$6", "memory"); // WTF? I shouldn't need "memory" here !!!
  return sz;
#else
#ifdef _LINUX
  asm("mov eax, 4\n" // sys_write
      "mov ebx, [ebp + 8]\n"
      "mov ecx, [ebp + 12]\n"
      "mov edx, [ebp + 16]\n"
      "int 0x80");
#else
#ifdef _WIN32
  unsigned NumberOfBytesWritten;
  WriteFile(fd,
            p,
            s,
            &NumberOfBytesWritten,
            NULL);
  return NumberOfBytesWritten;
#else
#ifndef __SMALLER_C_16__
  asm("mov cx, [bp + 16]\n"
      "test cx, cx\n"
      "jnz DosWriteCont\n"
      "xor eax, eax\n"
      "jmp DosWriteEnd");
  asm("DosWriteCont:\n"
      "mov ah, 0x40\n"
      "mov bx, [bp + 8]\n"
      "mov edx, [bp + 12]\n"
      "ror edx, 4\n"
      "mov ds, dx\n"
      "shr edx, 28\n"
      "int 0x21");
  asm("sbb ebx, ebx\n"
      "and eax, 0xffff\n"
      "or  eax, ebx\n"
      "DosWriteEnd:");
#else
  asm("mov cx, [bp + 8]\n"
      "test cx, cx\n"
      "jnz DosWriteCont\n"
      "xor ax, ax\n"
      "jmp DosWriteEnd");
  asm("DosWriteCont:\n"
      "mov ah, 0x40\n"
      "mov bx, [bp + 4]\n"
      "mov dx, [bp + 6]\n"
      "int 0x21\n"
      "sbb bx, bx\n"
      "or  ax, bx\n"
      "DosWriteEnd:");
#endif
#endif
#endif
#endif
}

#ifndef __SMALLER_C_16__
long OsLseek(int fd, long ofs, int whence)
{
#ifdef _RETROBSD
  long pos;
  asm volatile ("move $4, %1\n"
                "move $5, %2\n"
                "move $6, %3\n"
                "syscall 19\n" // SYS_lseek
                "nop\n"
                "nop\n"
                "move %0, $2\n"
                : "=r" (pos)
                : "r" (fd), "r" (ofs), "r" (whence)
                : "$2", "$4", "$5", "$6");
  return pos;
#else
#ifdef _LINUX
  asm("mov eax, 19\n" // sys_lseek
      "mov ebx, [ebp + 8]\n"
      "mov ecx, [ebp + 12]\n"
      "mov edx, [ebp + 16]\n"
      "int 0x80");
#else
#ifdef _WIN32
  return SetFilePointer(fd, ofs, 0, whence);
#else
  asm("mov ah, 0x42\n"
      "mov bx, [bp + 8]\n"
      "mov dx, [bp + 12]\n"
      "mov cx, [bp + 12 + 2]\n"
      "mov al, [bp + 16]\n"
      "int 0x21");
  asm("sbb ebx, ebx\n"
      "and eax, 0xffff\n"
      "shl edx, 16\n"
      "or  eax, edx\n"
      "or  eax, ebx");
#endif
#endif
#endif
}
#else
int OsLseek16(int fd, unsigned short ofs[2], int whence)
{
  asm("mov ah, 0x42\n"
      "mov bx, [bp + 4]\n"
      "mov si, [bp + 6]");
  asm("mov dx, [si]\n"
      "mov cx, [si + 2]\n"
      "mov al, [bp + 8]\n"
      "int 0x21");
  asm("sbb bx, bx\n"
      "or  ax, bx\n"
      "or  dx, bx\n"
      "mov [si], ax\n"
      "mov [si + 2], dx\n"
      "mov ax, bx");
}
#endif

#ifdef _DOS
unsigned DosGetPspSeg(void)
{
#ifndef __SMALLER_C_16__
  asm("mov ah, 0x51\n"
      "int 0x21\n"
      "movzx eax, bx");
#else
  asm("mov ah, 0x51\n"
      "int 0x21\n"
      "mov ax, bx");
#endif
}
#endif // _DOS

void exit(int e)
{
#ifdef _RETROBSD
  asm volatile ("move $4, %0\n"
                "syscall 1" // SYS_exit
                :
                : "r" (e)
                : "$2", "$4");
  __builtin_unreachable();
#else
#ifdef _LINUX
  asm("mov eax, 1\n"
      "mov ebx, [ebp + 8]\n"
      "int 0x80");
#else
#ifdef _WIN32
  ExitProcess(e);
#else
#ifndef __SMALLER_C_16__
  asm("mov ah, 0x4c\n"
      "mov al, [bp + 8]\n"
      "int 0x21");
#else
  asm("mov ah, 0x4c\n"
      "mov al, [bp + 4]\n"
      "int 0x21");
#endif
#endif
#endif
#endif
}

#ifdef _DOS
char __ProgName__[128];
char __ProgParams__[128];
int __argc__ = 1;
char* __argv__[64] = { "" };
#endif
#ifdef _WIN32
char __ProgParams__[1024];
int __argc__ = 1;
char* __argv__[512] = { "" };
#endif

int __StdOutHandle__ = 1; // 1 for DOS/Linux/RetroBSD, GetStdHandle(STD_OUTPUT_HANDLE) for Windows

#ifdef _DOS
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
#endif
#ifdef _WIN32
void __setargs__(int* pargc, char*** pargv)
{
  unsigned i, j, len;
  char* p = GetCommandLineA();
  j = i = 0;
  len = strlen(p);
  __argc__ = 0;
  while (i < len)
  {
    char c;
    if ((c = p[i]) == ' ')
    {
      ++i;
      continue;
    }
    __argv__[__argc__++] = __ProgParams__ + j;
    __ProgParams__[j++] = c;
    ++i;
    while (i < len)
    {
      if ((c = p[i]) == ' ')
        break;
      __ProgParams__[j++] = c;
      ++i;
    }
    __ProgParams__[j++] = 0;
  }

  *pargc = __argc__;
  *pargv = __argv__;

  __StdOutHandle__ = GetStdHandle(STD_OUTPUT_HANDLE);
}
#endif

// TBD??? Not sure if this limited buffering actually improves performance.
#ifndef NO_PREPROCESSOR
#define MAX_FILES 10
#else
#define MAX_FILES 2
#endif
#define FILE_BUF_SIZE (512*1)
unsigned __FileCnt__ = 0;
unsigned __FileHandles__[MAX_FILES];
unsigned char __FileBufs__[MAX_FILES][FILE_BUF_SIZE];
char __FileBufDirty__[MAX_FILES];
unsigned __FileBufSize__[MAX_FILES];
unsigned __FileBufPos__[MAX_FILES];

FILE* fopen(char* name, char* mode)
{
  FILE* f = NULL;
  unsigned i, fd = -1;

  if (strchr(mode, 'a') || strchr(mode, '+') || strchr(mode, 'b'))
    return f;

  if (__FileCnt__ >= MAX_FILES)
    return f;

  if (strchr(mode, 'r'))
  {
    fd = OsOpen(name);
  }
  else if (strchr(mode, 'w'))
  {
    fd = OsCreateOrTruncate(name);
  }

  if (fd != (unsigned)-1)
  {
    for (i = 0; i < MAX_FILES; ++i)
      if (!__FileHandles__[i])
      {
        __FileHandles__[i] = fd;
        __FileBufDirty__[i] = 0;
        __FileBufSize__[i] = 0;
        __FileBufPos__[i] = 0;
        ++__FileCnt__;
        f = (FILE*)(i + 1);
        break;
      }
  }

  return f;
}

int putchar(int c)
{
  unsigned char ch = c;

#ifndef _RETROBSD
#ifndef _LINUX
  if (c == '\n')
  {
    if (putchar('\r') == EOF)
      return EOF;
  }
#endif
#endif

  if (OsWrite(__StdOutHandle__, &ch, 1) != 1)
    return EOF;

  return ch;
}

int puts(char *s)
{
  int c;

  while ((c = *s++) != '\0')
    if (putchar(c) == EOF)
      return EOF;

  return putchar('\n');
}

int fputs(char* s, FILE* stream)
{
  int c;

  while ((c = *s++) != '\0')
    if (fputc(c, stream) == EOF)
      return EOF;

  return 0;
}

int vfprintf(FILE* stream, char* fmt, void* vl)
{
  return __vsprintf__(NULL, stream, fmt, vl);
}

int fprintf(FILE* stream, char* fmt, ...)
{
  void** pp = (void**)&fmt;
  return vfprintf(stream, fmt, pp + 1);
}

int fgetc(FILE* stream)
{
  unsigned char ch;
  unsigned i = (unsigned)stream, fd, pos;

  fd = __FileHandles__[--i];

  if ((pos = __FileBufPos__[i]) >= __FileBufSize__[i])
  {
    unsigned sz;
    sz = OsRead(fd, __FileBufs__[i], FILE_BUF_SIZE);
    if (!sz || sz == (unsigned)-1)
      return EOF;
    __FileBufSize__[i] = sz;
    pos = 0;
  }

  ch = __FileBufs__[i][pos++];
  __FileBufPos__[i] = pos;

  return ch;
}

int fputc(int c, FILE* stream)
{
  unsigned char ch = c;
  unsigned i = (unsigned)stream, fd, pos;

#ifndef _RETROBSD
#ifndef _LINUX
  if (c == '\n')
  {
    if (fputc('\r', stream) == EOF)
      return EOF;
  }
#endif
#endif

  fd = __FileHandles__[--i];

  __FileBufDirty__[i] = 1;
  pos = __FileBufPos__[i];
  __FileBufs__[i][pos++] = ch;

  if (pos >= FILE_BUF_SIZE)
  {
    if (OsWrite(fd, __FileBufs__[i], FILE_BUF_SIZE) != FILE_BUF_SIZE)
      return EOF;
    __FileBufDirty__[i] = 0;
    __FileBufSize__[i] = -1;
    __FileBufPos__[i] = -1;
  }

  ++__FileBufSize__[i];
  ++__FileBufPos__[i];

  return ch;
}

int fclose(FILE* stream)
{
  unsigned i = (unsigned)stream, fd;

  fd = __FileHandles__[--i];

  if (__FileBufDirty__[i])
  {
    unsigned sz = __FileBufSize__[i];
    if ((unsigned)OsWrite(fd, __FileBufs__[i], sz) != sz)
    {
      __FileHandles__[i] = 0;
      --__FileCnt__;
      OsClose(fd);
      return EOF;
    }
  }

  __FileHandles__[i] = 0;
  --__FileCnt__;
  return OsClose(fd);
}

struct fpos_t_
{
  union
  {
    unsigned short halves[2]; // for 16-bit memory models without 32-bit longs
    int align; // for alignment on machine word boundary
  } u;
}; // keep in sync with stdio.h !!!
#define fpos_t struct fpos_t_

// Note, these fgetpos() and fsetpos() are implemented for write-only files

int fgetpos(FILE* stream, fpos_t* pos)
{
  unsigned i = (unsigned)stream, fd;

  fd = __FileHandles__[--i];

#ifndef __SMALLER_C_16__
{
  long p;
  if ((p = OsLseek(fd, 0, 1/*SEEK_CUR*/)) < 0)
    return -1;

  p += __FileBufPos__[i];
  pos->u.align = p;
}
#else
{
  unsigned short p[2];
  p[0] = p[1] = 0;
  if (OsLseek16(fd, p, 1/*SEEK_CUR*/) < 0)
    return -1;
  p[1] += __FileBufPos__[i] > 0xFFFF - p[0];
  p[0] += __FileBufPos__[i];
  pos->u.halves[0] = p[0];
  pos->u.halves[1] = p[1];
}
#endif
  return 0;
}

int fsetpos(FILE* stream, fpos_t* pos)
{
  unsigned i = (unsigned)stream, fd;
  unsigned sz;

  fd = __FileHandles__[--i];

  // flush
  sz = __FileBufPos__[i];
  if (sz)
  {
    if ((unsigned)OsWrite(fd, __FileBufs__[i], sz) != sz)
      return -1;
  }

  // seek
#ifndef __SMALLER_C_16__
{
  long p = pos->u.align;
  if ((p = OsLseek(fd, p, 0/*SEEK_SET*/)) < 0)
    return -1;
}
#else
{
  if (OsLseek16(fd, pos->u.halves, 0/*SEEK_SET*/) < 0)
    return -1;
}
#endif

  __FileBufDirty__[i] = 0;
  __FileBufSize__[i] = __FileBufPos__[i] = 0;

  return 0;
}

#ifdef __SMALLER_C_32__
#ifndef _RETROBSD

#ifdef __HUGE__
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
#endif
