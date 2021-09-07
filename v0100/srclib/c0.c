/*
  Copyright (c) 2014-2018, Alexey Frunze
  2-clause BSD license.
*/
#ifdef __HUGE__
#define __HUGE_OR_UNREAL__
#endif
#ifdef __UNREAL__
#define __HUGE_OR_UNREAL__
#endif

#ifdef _LINUX
#define UNIX_LIKE
#endif
#ifdef _MACOS
#define UNIX_LIKE
#endif

extern int main(int argc, char** argv);
extern void exit(int);

#ifdef __SMALLER_C_32__
extern void __x87init(void);
#endif

#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef UNIX_LIKE
// Implements the logic of __getmainargs() from msvcrt.dll, msvcr70.dll ... msvcr120.dll.
//static
int __ArgParser__(char* in, char* out, char** argv)
{
  int cnt = 0;
  enum
  {
    WHITE,
    QUOT,
    PLAIN
  } state = WHITE;
  int c;
  unsigned slashes = 0;

  while ((c = *in++) != '\0')
  {
    if (state == WHITE)
    {
      if (c == '"')
      {
        state = QUOT;
      }
      else if (c != ' ' && c != '\t')
      {
        in--;
        state = PLAIN;
      }
      if (state != WHITE)
      {
        slashes = 0;
        argv[cnt++] = out;
      }
    }
    else if (c == '\\')
    {
      slashes++;
    }
    else if (c == '"')
    {
      unsigned scnt = slashes >> 1;
      while (scnt--)
        *out++ = '\\';
      if (slashes & 1)
      {
        *out++ = '"';
      }
      else
      {
        if (state == QUOT)
        {
          if (*in == '"')
            *out++ = *in++;
          // Comment out this else line (only it, don't touch the one right after it)
          // to get the behavior of msvcrt.dll, msvcr70.dll ... msvcr80.dll.
          // Uncommented else line gets you the behavior of msvcr90.dll ... msvcr120.dll.
          else
            state = PLAIN;
        }
        else // if (state == PLAIN)
        {
          state = QUOT;
        }
      }
      slashes = 0;
    }
    else if (slashes)
    {
      while (slashes--)
        *out++ = '\\';
      slashes = 0;
      in--;
    }
    else if (state == PLAIN && (c == ' ' || c == '\t'))
    {
      *out++ = '\0';
      state = WHITE;
    }
    else
    {
      *out++ = c;
    }
  }
  if (state != WHITE)
  {
    while (slashes--)
      *out++ = '\\';
    *out = '\0';
  }

  argv[cnt] = NULL; // trailing NULL after last argv[]

  return cnt;
}
#endif

#ifdef _DOS

#include "idos.h"

#ifdef __HUGE_OR_UNREAL__
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

#ifdef __HUGE_OR_UNREAL__
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
#ifdef __HUGE_OR_UNREAL__
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

#ifdef __HUGE_OR_UNREAL__
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

// TBD??? Don't use int 0x21 functions 0x25 & 0x35 for IVT manipulations???
#ifdef __HUGE_OR_UNREAL__
void __DosGetVect(int intno, unsigned short farptr[2])
{
  asm("mov  ah, 0x35\n"
      "mov  al, [bp + 8]\n"
      "int  0x21\n"
      "mov  esi, [bp + 12]");
#ifdef __HUGE__
  asm("ror  esi, 4\n"
      "mov  ds, si\n"
      "shr  esi, 28\n"
      "mov  [si], bx\n"
      "mov  [si + 2], es");
#else
  asm("mov  [esi], bx\n"
      "mov  [esi + 2], es\n"
      "push word 0\n"
      "pop  es");
#endif
}
void __DosSetVect(int intno, unsigned short farptr[2])
{
  asm("mov  ah, 0x25\n"
      "mov  al, [bp + 8]\n"
      "mov  esi, [bp + 12]");
#ifdef __HUGE__
  asm("ror  esi, 4\n"
      "mov  ds, si\n"
      "shr  esi, 28\n"
      "lds  dx, [si]\n"
      "int  0x21");
#else
  asm("lds  dx, [esi]\n"
      "int  0x21\n"
      "push word 0\n"
      "pop  ds");
#endif
}
#endif
#ifdef __SMALLER_C_16__
void __DosGetVect(int intno, unsigned short farptr[2])
{
  asm("push es\n"
      "mov  ah, 0x35\n"
      "mov  al, [bp + 4]\n"
      "int  0x21\n"
      "mov  si, [bp + 6]\n"
      "mov  [si], bx\n"
      "mov  [si + 2], es\n"
      "pop  es");
}
void __DosSetVect(int intno, unsigned short farptr[2])
{
  asm("push ds\n"
      "mov  ah, 0x25\n"
      "mov  al, [bp + 4]\n"
      "mov  si, [bp + 6]\n"
      "lds  dx, [si]\n"
      "int  0x21\n"
      "pop  ds");
}
#endif

#ifdef __HUGE_OR_UNREAL__
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

static char line[80/*executable name*/ + 128/*parameters*/];
static char* argvs[1/*executable name*/ + 128/2/*parameters*/ + 1/*NULL*/] = { "" };

#ifndef _DPMI
static
int setargs(int* pargc, char*** pargv)
{
  unsigned psp = DosGetPspSeg();
  unsigned env = peek(psp, 0x2c);
  unsigned i, len;
  char* p = line;
  char* params;

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
    i += 2;
    // The first one is the full program name.
    while ((*p++ = peekb(env, i++)) != '\0');
    argvs[0] = line;
  }

  params = p;

  // Next, extract program arguments from the PSP.

  len = peekb(psp, 0x80);
  i = 0;
  while (i < len)
    *p++ = peekb(psp, 0x81 + i++);
  *p = '\0';

  // Finally, parse them

  *pargc = 1 + __ArgParser__(params, params, argvs + 1);
  *pargv = argvs;

  return 1;
}

unsigned short __Int00DE[2];
//unsigned short __Int01DB[2];
//unsigned short __Int03BP[2];
unsigned short __Int04OF[2];
unsigned short __Int06UD[2];
#endif

#ifdef _DPMI
#include <string.h>
#include <stdlib.h>
#include "idpmi.h"
#include "istdio.h"

static
int setargs(int* pargc, char*** pargv, void* psp, char* argv0)
{
  unsigned char* p = (unsigned char*)psp + 0x80;
  unsigned len = *p++;
  // First, store the full program name.
  argvs[0] = argv0;
  // Next, copy program arguments from the PSP.
  memcpy(line, p, len);
  line[len] = '\0';
  // Finally, parse them
  *pargc = 1 + __ArgParser__(line, line, argvs + 1);
  *pargv = argvs;
  return 1;
}
#endif

#ifdef __HUGE_OR_UNREAL__
void __interrupt __ExcIsr(void)
{
  static char msg[] = "\r\nUnhandled exception!\r\n";
  __write(STDERR_FILENO, msg, sizeof msg - 1);
  _Exit(EXIT_FAILURE);
}

void __interrupt __CtrlCIsr(void)
{
  // It looks like DOS will terminate the app on Ctrl+C even without a custom int 0x23 handler.
  // But let's keep the code as I might transform Ctrl+C into SIGINT in the future.
  _Exit(EXIT_FAILURE);
}
#endif

#ifndef _DPMI
void __start__(void)
{
  int argc;
  char** argv;
  unsigned short farptr[2];

  // Register exception handlers

  __DosGetVect(0, __Int00DE);
//  __DosGetVect(1, __Int01DB);
//  __DosGetVect(3, __Int03BP);
  __DosGetVect(4, __Int04OF);
  __DosGetVect(6, __Int06UD);

#ifdef __HUGE_OR_UNREAL__
  farptr[0] = (unsigned)&__ExcIsr & 0xF;
  farptr[1] = (unsigned)&__ExcIsr >> 4;
#endif
#ifdef __SMALLER_C_16__
extern unsigned short __getCS(void);
  farptr[0] = (unsigned)&__ExcIsr;
  farptr[1] = __getCS();
#endif
  __DosSetVect(0, farptr);
//  __DosSetVect(1, farptr);
//  __DosSetVect(3, farptr);
  __DosSetVect(4, farptr);
  __DosSetVect(6, farptr);

  // Register int 0x23/Ctrl+C handler

#ifdef __HUGE_OR_UNREAL__
  farptr[0] = (unsigned)&__CtrlCIsr & 0xF;
  farptr[1] = (unsigned)&__CtrlCIsr >> 4;
#endif
#ifdef __SMALLER_C_16__
extern unsigned short __getCS(void);
  farptr[0] = (unsigned)&__CtrlCIsr;
  farptr[1] = __getCS();
#endif
  __DosSetVect(0x23, farptr);

  // Set argc and argv
  setargs(&argc, &argv);

#ifdef __HUGE_OR_UNREAL__
  // Start counting ticks now
  clock();
#endif

#ifdef __SMALLER_C_32__
  __x87init();
#endif

  exit(main(argc, argv));
}
#endif

#ifdef _DPMI
void _start(unsigned long exitAddr, void* psp, void* env, char* argv0,
            void* stubInfo, void* fbuf, void* heapStart, void* heapStop)
{
  int argc;
  char** argv;

  __dpmi_exit_addr = exitAddr;
  __dpmi_psp = psp;
  __dpmi_env = env;
  __dpmi_stubInfo = stubInfo;
  __dpmi_iobuf = fbuf;
  __dpmi_heap_start = heapStart;
  __dpmi_heap_stop = heapStop;

  // Set argc and argv
  setargs(&argc, &argv, psp, argv0);

  // Start counting ticks now
  clock();

  __x87init();

  exit(main(argc, argv));
}
#endif

#endif // _DOS

#ifdef _WINDOWS

#include <string.h>
#include <stdlib.h>
#include "iwin32.h"
#include "istdio.h"

static char emptyarg[] = "", *emptyargv[2] = { emptyarg, NULL };

// Import something from msvcrt.dll to reduce false positives in anti-virus software.
extern int __msvcrt_abs(int);
static int (*pabs)(int) = &__msvcrt_abs;

static
int setargs(int* pargc, char*** pargv)
{
  char* line = __GetCommandLineA();
  unsigned len = strlen(line);
  char* buf = malloc(len + 1); // receptacle for *argv[] chars because *GetCommandLineA() is read-only
  char** ptrbuf = malloc(((len + 1) / 2 + 1) * sizeof(char*)); // receptacle for argv[] pointers
  int cnt;

  if (!buf || !ptrbuf)
    goto error;

  if ((cnt = __ArgParser__(line, buf, ptrbuf)) == 0)
    goto error;

  *pargc = cnt;
  *pargv = ptrbuf;

  return 1;

error:

  *pargc = 1;
  *pargv = emptyargv;

  if (buf)
    free(buf);

  if (ptrbuf)
    free(ptrbuf);

  return 0;
}

static
int UnhandledExceptionHandler(struct _EXCEPTION_POINTERS* ExceptionInfo)
{
  static char msg[] = "\r\nUnhandled exception!\r\n";
  unsigned NumberOfBytesWritten;

  (void)ExceptionInfo;

  // TBD??? Dump the register state???
  __WriteFile(__GetStdHandle(STD_ERROR_HANDLE), msg, sizeof msg - 1, &NumberOfBytesWritten, 0);

  // Terminate immediately w/o invoking Dr. Watson or Windows Error Reporting (WER)
  __ExitProcess(EXIT_FAILURE);

  // The following is not reached because of ExitProcess()

//  return EXCEPTION_CONTINUE_SEARCH;
  // remove the parameter from the stack since this function is supposed to have the WINAPI calling convention
  asm("mov   eax, 0\n"
      "leave\n"
      "ret   4");
}

void __start__(void)
{
  int argc;
  char** argv;

  // Windows doesn't use file handles 0,1,2 for stdin,stdout,stderr.
  __stdin->fd = __GetStdHandle(STD_INPUT_HANDLE);
  __stdout->fd = __GetStdHandle(STD_OUTPUT_HANDLE);
  __stderr->fd = __GetStdHandle(STD_ERROR_HANDLE);

  // Register exception handlers
  __SetUnhandledExceptionFilter(&UnhandledExceptionHandler);

  // Set argc and argv
  setargs(&argc, &argv);

  // Start counting ticks now
  clock();

  __x87init();

  exit(main(argc, argv));
}

#endif // _WINDOWS

#ifdef UNIX_LIKE

char** __environ;

void __start__(int argc, char** argv)
{
  __environ = argv + argc + 1;

  __x87init();

  exit(main(argc, argv));
}

#endif // UNIX_LIKE
