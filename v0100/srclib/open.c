/*
  Copyright (c) 2014-2018, Alexey Frunze
  2-clause BSD license.
*/
#include <fcntl.h>
#include <unistd.h>

#ifdef __HUGE__
#define __HUGE_OR_UNREAL__
#endif
#ifdef __UNREAL__
#define __HUGE_OR_UNREAL__
#endif

#ifdef _DOS

#ifdef __HUGE_OR_UNREAL__
#ifdef USE_EXT_OPEN
int __DosExtOpen(char* name, int mode, int attr, int action, unsigned* handleOrError)
{
  asm("mov ah, 0x6c\n"
      "mov esi, [bp + 8]\n"
      "ror esi, 4\n"
      "mov ds, si\n"
      "shr esi, 28\n"
      "mov bx, [bp + 12]\n"
      "mov cx, [bp + 16]\n"
      "mov dx, [bp + 20]\n"
      "int 0x21");
  asm("movzx ebx, ax\n"
      "cmc\n"
      "sbb ax, ax\n"
      "and eax, 1\n"
      "mov esi, [bp + 24]");
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
#else
static
int DosCreateOrOpen(char* name, unsigned ax, unsigned cx, unsigned* handleOrError)
{
  asm("mov ax, [bp + 12]\n"
      "mov cx, [bp + 16]\n"
      "mov edx, [bp + 8]\n"
      "ror edx, 4\n"
      "mov ds, dx\n"
      "shr edx, 28\n"
      "int 0x21");
  asm("movzx ebx, ax\n"
      "cmc\n"
      "sbb ax, ax\n"
      "and eax, 1\n"
      "mov esi, [bp + 20]");
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
#endif
#endif // __HUGE_OR_UNREAL__

#ifdef __SMALLER_C_16__
#ifdef USE_EXT_OPEN
int __DosExtOpen(char* name, int mode, int attr, int action, unsigned* handleOrError)
{
  asm("mov ah, 0x6c\n"
      "mov si, [bp + 4]\n"
      "mov bx, [bp + 6]\n"
      "mov cx, [bp + 8]\n"
      "mov dx, [bp + 10]\n"
      "int 0x21");
  asm("mov bx, ax\n"
      "cmc\n"
      "sbb ax, ax\n"
      "and ax, 1\n"
      "mov si, [bp + 12]\n"
      "mov [si], bx");
}
#else
static
int DosCreateOrOpen(char* name, unsigned ax, unsigned cx, unsigned* handleOrError)
{
  asm("mov ax, [bp + 6]\n"
      "mov dx, [bp + 4]\n"
      "mov cx, [bp + 8]\n"
      "int 0x21");
  asm("mov bx, ax\n"
      "cmc\n"
      "sbb ax, ax\n"
      "and ax, 1\n"
      "mov si, [bp + 10]\n"
      "mov [si], bx");
}
#endif
#endif // __SMALLER_C_16__

#ifdef _DPMI
#include <string.h>
#include "idpmi.h"
#ifdef USE_EXT_OPEN
int __DosExtOpen(char* name, int mode, int attr, int action, unsigned* handleOrError)
{
  __dpmi_int_regs regs;
  unsigned nlen = strlen(name) + 1;
  if (nlen > __DPMI_IOFBUFSZ)
  {
    *handleOrError = -1;
    return 0;
  }
  memcpy(__dpmi_iobuf, name, nlen);
  memset(&regs, 0, sizeof regs);
  regs.eax = 0x6c00;
  regs.ebx = mode;
  regs.ecx = attr;
  regs.edx = action;
  regs.esi = (unsigned)__dpmi_iobuf & 0xF;
  regs.ds = (unsigned)__dpmi_iobuf >> 4;
  if (__dpmi_int(0x21, &regs))
  {
    *handleOrError = -1;
    return 0;
  }
  *handleOrError = regs.eax & 0xFFFF;
  return (regs.flags & 1) ^ 1; // carry
}
#else
static
int DosCreateOrOpen(char* name, unsigned ax, unsigned cx, unsigned* handleOrError)
{
  __dpmi_int_regs regs;
  unsigned nlen = strlen(name) + 1;
  if (nlen > __DPMI_IOFBUFSZ)
  {
    *handleOrError = -1;
    return 0;
  }
  memcpy(__dpmi_iobuf, name, nlen);
  memset(&regs, 0, sizeof regs);
  regs.eax = ax;
  regs.ecx = cx;
  regs.edx = (unsigned)__dpmi_iobuf & 0xF;
  regs.ds = (unsigned)__dpmi_iobuf >> 4;
  if (__dpmi_int(0x21, &regs))
  {
    *handleOrError = -1;
    return 0;
  }
  *handleOrError = regs.eax & 0xFFFF;
  return (regs.flags & 1) ^ 1; // carry
}
#endif
#endif // _DPMI

#ifndef USE_EXT_OPEN
int __DosWrite(int handle, void* buf, unsigned size, unsigned* sizeOrError);

// Implementation of function 0x6c in terms of functions 0x3c, 0x3d, 0x5b.
int __DosExtOpen(char* name, int mode, int attr, int action, unsigned* handleOrError)
{
  switch (action)
  {
  case 0x10: // O_CREAT && O_EXCL: fail if exists, else create and open
    return DosCreateOrOpen(name, 0x5b00, attr, handleOrError);
  case 0x12: // O_CREAT && O_TRUNC: if exists, truncate and open, else create and open
    return DosCreateOrOpen(name, 0x3c00, attr, handleOrError);
  case 0x11: // O_CREAT && !O_TRUNC: if exists, just open, else create and open
    for (;;)
    {
      // First, try opening an existing file...
      int res = DosCreateOrOpen(name, 0x3d00 | mode, attr, handleOrError);
      if (res)
        return 1;

      if (*handleOrError != 2) // done if not "file not found" error
        break;

      // Last, try creating a new file...
      res = DosCreateOrOpen(name, 0x5b00, attr, handleOrError);
      if (res)
        return 1;

      if (*handleOrError != 80) // done if not "file already exists" error
        break;

      // If we're here, there's a race going on.
      // Repeat the open & create sequence until success or failure...
    }
    return 0;
  case 0x02: // !O_CREAT && O_TRUNC: if exists, truncate and open, else fail
    if (DosCreateOrOpen(name, 0x3d00 | mode, attr, handleOrError))
    {
      unsigned sizeOrError;
      // Truncate the file using a zero-sized write.
      if (!__DosWrite(*handleOrError, /*buf*/NULL, /*size*/0, &sizeOrError))
      {
        __close(*handleOrError);
        *handleOrError = sizeOrError;
        return 0;
      }
      return 1;
    }
    return 0;
  case 0x01: // !O_CREAT && !O_TRUNC: if exists, just open, else fail
    return DosCreateOrOpen(name, 0x3d00 | mode, attr, handleOrError);
  default:
    *handleOrError = -1;
    return 0;
  }
}
#endif

int __open(char* name, int oflag, ...)
{
  mode_t* psmode = (oflag & O_CREAT) ? (&oflag + 1) : 0;
  int omode = oflag & O_ACCMODE;
  int attr = 0x20; // archive attribute = 1 = not backed up
  int action;
  unsigned handle;

  if ((oflag & (O_CREAT | O_EXCL)) == (O_CREAT | O_EXCL))
  {
    action = 0x10; // fail if exists, else create and open
  }
  else
  {
    if (oflag & O_TRUNC)
      action = 0x02; // if exists, truncate and open
    else
      action = 0x01; // if exists, just open

    if (oflag & O_CREAT)
      action |= 0x10; // if doesn't exist, create and open
  }

  if (psmode && (*psmode & S_IWUSR) == 0)
    attr |= 1; // read-only attribute

  if (__DosExtOpen(name, omode, attr, action, &handle))
  {
    // Problem: DOS does not support the append mode directly
    // (e.g. writes only going to the end of the file and reads allowed anywhere in the file).
    // Any solution other than maintaining somewhere O_APPEND flag associated with every DOS handle???
    // TBD??? How about returning the handle with a high bit set to reflect O_APPEND???
    // But that won't probably work with 16-bit handles if DOS can return handle values using
    // all (or most?) of the 16 bits of a handle.
    if (oflag & O_APPEND)
    {
#ifdef __SMALLER_C_16__
      fpos_t pos;
      pos.halves[1] = pos.halves[0] = 0;
      if (__lseekp(handle, &pos, SEEK_END))
      {
        __close(handle);
        return -1;
      }
#else
      if (__lseek(handle, 0, SEEK_END) == -1)
      {
        __close(handle);
        return -1;
      }
#endif
    }
    return handle;
  }

  return -1;
}

#endif // _DOS

#ifdef _WINDOWS

#include "iwin32.h"

int __open(char* name, int oflag, ...)
{
  mode_t* psmode = (oflag & O_CREAT) ? (&oflag + 1) : 0;
  int omode = oflag & O_ACCMODE;
  int attr = FILE_ATTRIBUTE_NORMAL; // archive attribute = 1 = not backed up
  int action;
  unsigned handle;

  switch (omode)
  {
  default:
  case O_RDONLY:
    omode = GENERIC_READ;
    break;
  case O_WRONLY:
    omode = GENERIC_WRITE;
    break;
  case O_RDWR:
    omode = GENERIC_READ | GENERIC_WRITE;
    break;
  }

  if ((oflag & (O_CREAT | O_EXCL)) == (O_CREAT | O_EXCL))
  {
    action = CREATE_NEW; // fail if exists, else create and open
  }
  else if (oflag & O_CREAT)
  {
    if (oflag & O_TRUNC)
      action = CREATE_ALWAYS; // if exists, truncate and open, else create and open
    else
      action = OPEN_ALWAYS; // if exists, just open, else create and open
  }
  else
  {
    if (oflag & O_TRUNC)
      action = TRUNCATE_EXISTING; // if exists, truncate and open, else fail
    else
      action = OPEN_EXISTING; // if exists, just open, else fail
  }

  if (psmode && (*psmode & S_IWUSR) == 0)
    attr = FILE_ATTRIBUTE_READONLY; // read-only attribute

  handle = __CreateFileA(name,
                         omode,
                         FILE_SHARE_READ,
                         NULL,
                         action,
                         attr,
                         NULL);
  if (handle != INVALID_HANDLE_VALUE)
  {
    // Problem: Windows does not support the append mode directly
    // (e.g. writes only going to the end of the file and reads allowed anywhere in the file).
    // Any solution other than maintaining somewhere O_APPEND flag associated with every Windows handle???
    if (oflag & O_APPEND)
    {
      if (__lseek(handle, 0, SEEK_END) == -1)
      {
        __close(handle);
        return -1;
      }
    }
    return handle;
  }

  return -1;
}

#endif // _WINDOWS

#ifdef _LINUX

int __open(char* name, int oflag, ...)
{
  asm("mov eax, 5\n" // sys_open
      "mov ebx, [ebp + 8]\n"
      "mov ecx, [ebp + 12]\n"
      "mov edx, [ebp + 16]\n" // may read garbage, but shouldn't crash
      "int 0x80\n"
      "add eax, 0\n"
      "jns .done\n"
      "mov eax, -1\n" // should really return -1 on error. TBD??? set errno?
      ".done:");
}

#endif // _LINUX

#ifdef _MACOS

int __open(char* name, int oflag, ...)
{
  asm("mov  eax, 5\n" // sys_open
      "push dword [ebp + 16]\n" // may read garbage, but shouldn't crash
      "push dword [ebp + 12]\n"
      "push dword [ebp + 8]\n"
      "sub  esp, 4\n"
      "int  0x80\n"
      "jnc  .done\n"
      "mov  eax, -1\n" // should really return -1 on error. TBD??? set errno?
      ".done:");
}

#endif // _MACOS
