/*
Copyright (c) 2013-2014, Alexey Frunze
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

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies, 
either expressed or implied, of the FreeBSD Project.
*/

/*****************************************************************************/
/*                                                                           */
/*                             minimal stdlibc                               */
/*                                                                           */
/*  Just enough code for Smaller C to compile itself into a 16-bit DOS .EXE. */
/*                                                                           */
/*****************************************************************************/

#ifndef __SMALLER_C__
#error must be compiled with Smaller C
#endif

#define NULL 0
#define EOF (-1)
#define FILE void

void __setargs__(int* pargc, char*** pargv);
extern int main(int argc, char** argv);
void exit(int);

void __start__(void)
{
  int argc;
  char** argv;
  __setargs__(&argc, &argv);
  exit(main(argc, argv));
}

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
  int leadchar;

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
      pc = *pp++;
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
  void** pp = &fmt;
  return vprintf(fmt, pp + 1);
}

int vsprintf(char* buf, char* fmt, void* vl)
{
  return __vsprintf__(&buf, NULL, fmt, vl);
}

int sprintf(char* buf, char* fmt, ...)
{
  void** pp = &fmt;
  return vsprintf(buf, fmt, pp + 1);
}

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
  unsigned char* p = seg * 16 + ofs;
  p[0] = val;
  p[1] = val >> 8;
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
  unsigned char* p = seg * 16 + ofs;
  return (p[1] << 8) + p[0];
#else
  asm("push ds\n"
      "mov  ds, [bp + 4]\n"
      "mov  bx, [bp + 6]\n"
      "mov  ax, [bx]\n"
      "pop  ds");
#endif
}

int DosCreateOrTruncate(char* name)
{
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
}

int DosOpen(char* name)
{
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
}

int DosClose(int fd)
{
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
}

int DosRead(int fd, void* p, unsigned s)
{
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
}

int DosWrite(int fd, void* p, unsigned s)
{
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
}

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

void exit(int e)
{
#ifndef __SMALLER_C_16__
  asm("mov ah, 0x4c\n"
      "mov al, [bp + 8]\n"
      "int 0x21");
#else
  asm("mov ah, 0x4c\n"
      "mov al, [bp + 4]\n"
      "int 0x21");
#endif
}

char __ProgName__[128];
char __ProgParams__[128];

int __argc__ = 1;
char* __argv__[64] = { "" };

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

// TBD??? Not sure if this limited buffering actually improves performance.
#define MAX_FILES 10
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

  if (strchr(mode, 'a') || strchr(mode, '+'))
    return f;

  if (__FileCnt__ >= MAX_FILES)
    return f;

  if (strchr(mode, 'r'))
  {
    fd = DosOpen(name);
  }
  else if (strchr(mode, 'w'))
  {
    fd = DosCreateOrTruncate(name);
  }

  if (fd != -1)
  {
    for (i = 0; i < MAX_FILES; ++i)
      if (!__FileHandles__[i])
      {
        __FileHandles__[i] = fd;
        __FileBufDirty__[i] = 0;
        __FileBufSize__[i] = 0;
        __FileBufPos__[i] = 0;
        ++__FileCnt__;
        f = i + 1;
        break;
      }
  }

  return f;
}

int putchar(int c)
{
  unsigned char ch = c;

  if (c == '\n')
  {
    if (putchar('\r') == EOF)
      return EOF;
  }

  if (DosWrite(1, &ch, 1) != 1)
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
  int c, err = 0;

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
  void** pp = &fmt;
  return vfprintf(stream, fmt, pp + 1);
}

int fgetc(FILE* stream)
{
  unsigned char ch;
  unsigned i = stream, fd, pos;

  fd = __FileHandles__[--i];

  if ((pos = __FileBufPos__[i]) >= __FileBufSize__[i])
  {
    unsigned sz;
    sz = DosRead(fd, __FileBufs__[i], FILE_BUF_SIZE);
    if (!sz || sz == -1)
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
  unsigned i = stream, fd, pos;

  if (c == '\n')
  {
    if (fputc('\r', stream) == EOF)
      return EOF;
  }

  fd = __FileHandles__[--i];

  __FileBufDirty__[i] = 1;
  pos = __FileBufPos__[i];
  __FileBufs__[i][pos++] = ch;

  if (pos >= FILE_BUF_SIZE)
  {
    if (DosWrite(fd, __FileBufs__[i], FILE_BUF_SIZE) != FILE_BUF_SIZE)
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
  unsigned i = stream, fd;

  fd = __FileHandles__[--i];

  if (__FileBufDirty__[i])
  {
    unsigned sz = __FileBufSize__[i];
    if (DosWrite(fd, __FileBufs__[i], sz) != sz)
    {
      __FileHandles__[i] = 0;
      --__FileCnt__;
      DosClose(fd);
      return EOF;
    }
  }

  __FileHandles__[i] = 0;
  --__FileCnt__;
  return DosClose(fd);
}
