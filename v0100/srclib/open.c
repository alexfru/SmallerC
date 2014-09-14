/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include <fcntl.h>
#include <unistd.h>

#ifdef _DOS

#ifdef __HUGE__
static
int DosExtOpen(char* name, int mode, int attr, int action, unsigned* handleOrError)
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
      "mov esi, [bp + 24]\n"
      "ror esi, 4\n"
      "mov ds, si\n"
      "shr esi, 28\n"
      "mov [si], ebx");
}
#endif // __HUGE__

#ifdef __SMALLER_C_16__
static
int DosExtOpen(char* name, int mode, int attr, int action, unsigned* handleOrError)
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
#endif // __SMALLER_C_16__

int open(char* name, int oflag, ...)
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

  // TBD??? use int 0x21 functions 0x3d, 0x3c, 0x5b for oder versions of DOS???
  if (DosExtOpen(name, omode, attr, action, &handle))
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
      if (__lseek(handle, &pos, SEEK_END))
      {
        close(handle);
        return -1;
      }
#else
      if (lseek(handle, 0, SEEK_END) == -1)
      {
        close(handle);
        return -1;
      }
#endif
    }
    return handle;
  }

  return -1;
}
#endif // _DOS
