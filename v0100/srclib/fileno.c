/*
  Copyright (c) 2014-2018, Alexey Frunze
  2-clause BSD license.
*/
#include "istdio.h"

#ifndef _WINDOWS

int __fileno(FILE* f)
{
  if (!f)
  {
    return -1;
  }
  return f->fd;
}

#endif // !_WINDOWS

#ifdef _WINDOWS

#include <unistd.h>
#include "iwin32.h"

int __fileno(FILE* f)
{
  int fd;

  if (!f)
  {
    return -1;
  }

  fd = f->fd;

  // TBD??? Fix this hack???
  // GetStdHandle(STD_INPUT_HANDLE), GetStdHandle(STD_OUTPUT_HANDLE) and GetStdHandle(STD_ERROR_HANDLE)
  // appear to always return 3, 7 and 11 when there's no redirection. Other handles (e.g. those of files)
  // appear to have values that are multiples of 4. I'm not sure if GetStdHandle() can ever return values
  // 0, 1 and 2 or if any other valid handle can ever be equal to 0, 1 or 2.
  // If 0, 1 and 2 can be valid handles in the system, I'll need to renumber/translate handles in the C library.
  if (fd == __GetStdHandle(STD_INPUT_HANDLE))
    fd = STDIN_FILENO;
  else if (fd == __GetStdHandle(STD_OUTPUT_HANDLE))
    fd = STDOUT_FILENO;
  else if (fd == __GetStdHandle(STD_ERROR_HANDLE))
    fd = STDERR_FILENO;

  return fd;
}

#endif // _WINDOWS
