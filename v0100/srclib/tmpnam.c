/*
  Copyright (c) 2014-2018, Alexey Frunze
  2-clause BSD license.
*/
#include "istdio.h"
#include <string.h>
#include <stdlib.h>

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

#ifdef _DOS

#ifdef __HUGE_OR_UNREAL__
static
int DosQueryAttr(char* name, unsigned* attrOrError)
{
  asm("mov ax, 0x4300\n"
      "mov edx, [bp + 8]\n"
      "ror edx, 4\n"
      "mov ds, dx\n"
      "shr edx, 28\n"
      "int 0x21");
  asm("movzx ebx, ax\n"
      "cmc\n"
      "sbb ax, ax");
  asm("and cx, ax\n"
      "mov dx, ax\n"
      "not dx\n"
      "and bx, dx\n"
      "or  bx, cx");
  asm("and eax, 1\n"
      "mov esi, [bp + 12]");
#ifdef __HUGE__
  asm("ror esi, 4\n"
      "mov ds, si\n"
      "shr esi, 28\n"
      "mov [si], ebx");
#else
  asm("push word 0\n"
      "pop  ds\n"
      "mov  [esi], ebx");
#endif
}
#endif // __HUGE_OR_UNREAL__

#ifdef __SMALLER_C_16__
static
int DosQueryAttr(char* name, unsigned* attrOrError)
{
  asm("mov ax, 0x4300\n"
      "mov dx, [bp + 4]\n"
      "int 0x21");
  asm("mov bx, ax\n"
      "cmc\n"
      "sbb ax, ax");
  asm("and cx, ax\n"
      "mov dx, ax\n"
      "not dx\n"
      "and bx, dx\n"
      "or  bx, cx");
  asm("and ax, 1\n"
      "mov si, [bp + 6]\n"
      "mov [si], bx");
}
#endif // __SMALLER_C_16__

#ifdef _DPMI
#include <string.h>
#include "idpmi.h"
static
int DosQueryAttr(char* name, unsigned* attrOrError)
{
  __dpmi_int_regs regs;
  unsigned nlen = strlen(name) + 1;
  if (nlen > __DPMI_IOFBUFSZ)
  {
    *attrOrError = -1;
    return 0;
  }
  memcpy(__dpmi_iobuf, name, nlen);
  memset(&regs, 0, sizeof regs);
  regs.eax = 0x4300;
  regs.edx = (unsigned)__dpmi_iobuf & 0xF;
  regs.ds = (unsigned)__dpmi_iobuf >> 4;
  if (__dpmi_int(0x21, &regs))
  {
    *attrOrError = -1;
    return 0;
  }
  *attrOrError = ((regs.flags & 1) ? regs.eax : regs.ecx) & 0xFFFF;
  return (regs.flags & 1) ^ 1; // carry
}
#endif // _DPMI

#endif // _DOS

#ifdef _WINDOWS

#include "iwin32.h"

#endif // _WINDOWS

static unsigned num;

static char name[L_tmpnam];
static size_t plen;

#ifndef UNIX_LIKE
static
void TryPath(char* path)
{
  unsigned attrOrError;
  int trailingSlash = 0;

  if ((plen = strlen(path)) >= L_tmpnam - (1/*slash*/ + 8+1+3/*8.3 name*/))
    return;

  strcpy(name, path);

  if (name[plen - 1] == '\\' || name[plen - 1] == '/')
    trailingSlash = name[plen - 1];
  // The name of the directory whose existence/attribute we're about to check
  // should end with a slash IFF it's a root directory. Valid: C:\, C:\FOO.
  // Invalid: C:, C:\FOO\.
  if (trailingSlash)
  {
    if (plen > 1 && name[plen - 2] != ':')
      name[--plen] = '\0';
    else
      trailingSlash = 0;
  }
  else
  {
    if (name[plen - 1] == ':')
      strcat(name, "\\"), plen++;
    else
      trailingSlash = '\\';
  }

  // Check if name exists in the file system and is a directory
#ifdef _DOS
  if (!DosQueryAttr(name, &attrOrError) || !(attrOrError & 0x10))
    *name = '\0';
#endif
#ifdef _WINDOWS
  attrOrError = __GetFileAttributesA(name);
  if (attrOrError == INVALID_FILE_ATTRIBUTES || !(attrOrError & FILE_ATTRIBUTE_DIRECTORY))
    *name = '\0';
#endif

  // If it's a directory, append a slash if needed, so a file name can be appended after it
  if (*name && trailingSlash)
  {
    name[plen++] = trailingSlash;
    name[plen] = '\0';
  }
}

static
void TryEnvPath(char* evname)
{
  char* path;
  char* ev = __EnvVar;
  __EnvVar = NULL;
  path = getenv(evname);
  __EnvVar = ev; // restore the string previously returned by getenv()

  if (path)
  {
    if (*path)
      TryPath(path);
    free(path);
  }
}
#else

#ifdef _LINUX
static
int SysAccess(char* name, int amode)
{
  asm("mov eax, 33\n" // sys_access
      "mov ebx, [ebp + 8]\n"
      "mov ecx, [ebp + 12]\n"
      "int 0x80"); // returns -"errno", e.g. -ENOENT.
}
#endif // _LINUX

#ifdef _MACOS
static
int SysAccess(char* name, int amode)
{
  asm("mov  eax, 33\n" // sys_access
      "push dword [ebp + 12]\n"
      "push dword [ebp + 8]\n"
      "sub  esp, 4\n"
      "int  0x80\n" // returns "errno", e.g. ENOENT.
      "neg  eax"); // unify with Linux: change to -"errno".
}
#endif // _MACOS

#endif

char* __tmpnam(char* buf, unsigned iterations)
{
  unsigned attrOrError;
  unsigned i;

  if (!*name)
  {
    // On the first use, determine the directory for temporary files
#ifndef UNIX_LIKE
    TryEnvPath("TEMP");
    if (!*name)
      TryEnvPath("TMP");
    // If neither %TEMP% nor %TMP% is set, try to use the first hard disk
    if (!*name)
      TryPath("C:\\");
    // Otherwise stick to the current directory
    if (!*name)
    {
      // TBD!!! prefix with getcwd(), especially when chdir() is supported
      strcpy(name, ".\\");
      plen = 2;
    }
    strcat(name, "TMP00000.$$$");
#else
    if (SysAccess("/tmp", 0/*F_OK*/) == 0)
    {
      strcpy(name, "/tmp/");
      plen = 5;
    }
    else
    {
      // TBD!!! prefix with getcwd(), especially when chdir() is supported
      strcpy(name, "./");
      plen = 2;
    }
    strcat(name, "tmp00000.tmp");
#endif
  }

  if (buf)
    strcpy(buf, name);
  else
    buf = name;

  for (i = 0; i < iterations; i++)
  {
    char* p = buf + plen + 8/*strlen("TMP00000")*/;
    unsigned j = 5/*strlen("00000")*/;

    unsigned n = num++;
    if (num >= TMP_MAX)
      num = 0;

    while (j--)
    {
      *--p = '0' + n % 10;
      n /= 10;
    }

    // Check if buf does not exist in the file system
#ifdef _DOS
    if (!DosQueryAttr(buf, &attrOrError))
    {
      if (attrOrError == 2)
        return buf;
      break;
    }
#endif
#ifdef _WINDOWS
    attrOrError = __GetFileAttributesA(buf);
    if (attrOrError == INVALID_FILE_ATTRIBUTES)
    {
      if (__GetLastError() == ERROR_FILE_NOT_FOUND)
        return buf;
      break;
    }
#endif
#ifdef UNIX_LIKE
    // SysAccess(), defined above, returns -errno,
    // e.g. -ENOENT on both Linux and MacOS.
    attrOrError = -SysAccess(buf, 0/*F_OK*/);
    if (attrOrError)
    {
      if (attrOrError == 2/*ENOENT*/)
        return buf;
      break;
    }
#endif
  }

  return NULL;
}

char* tmpnam(char* buf)
{
  return __tmpnam(buf, TMP_MAX);
}
