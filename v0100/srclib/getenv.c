/*
  Copyright (c) 2014-2018, Alexey Frunze
  2-clause BSD license.
*/
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

char* __EnvVar;

#ifdef _DOS

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

#ifndef _DPMI
char* getenv(char* name)
{
  unsigned psp = DosGetPspSeg();
  unsigned env = peek(psp, 0x2c);
  unsigned nlen = strlen(name);
  unsigned i, start;

  for (start = i = 0; ; i++)
  {
    int c = peekb(env, i);
    if (c == '=')
    {
      unsigned vlen = 0, match = 0;
      if (i - start == nlen)
      {
        unsigned j;
        match = 1;
        for (j = 0; j < nlen; j++)
          if (peekb(env, start + j) != (unsigned char)name[j])
          {
            match = 0;
            break;
          }
      }
      i++;
      while (peekb(env, i + vlen) != '\0')
        vlen++;
      if (match)
      {
        char* p;
        unsigned j = i;
        if (__EnvVar)
          free(__EnvVar);
        if (!(p = __EnvVar = malloc(vlen + 1)))
        {
          return 0;
        }
        while ((*p++ = peekb(env, j++)) != '\0');
        return __EnvVar;
      }
      i += vlen;
      c = '\0';
    }

    if (c == '\0')
    {
      start = i + 1;
      if (peekb(env, start) == '\0')
      {
        // Reached the end of the list of environment variables
        return 0;
      }
    }
  }
}
#endif
#ifdef _DPMI
#include "idpmi.h"
char* getenv(char* name)
{
  unsigned char* env = __dpmi_env;
  unsigned nlen = strlen(name);
  unsigned i, start;

  for (start = i = 0; ; i++)
  {
    int c = env[i];
    if (c == '=')
    {
      unsigned vlen = 0, match = 0;
      if (i - start == nlen)
      {
        unsigned j;
        match = 1;
        for (j = 0; j < nlen; j++)
          if (env[start + j] != (unsigned char)name[j])
          {
            match = 0;
            break;
          }
      }
      i++;
      while (env[i + vlen] != '\0')
        vlen++;
      if (match)
      {
        char* p;
        unsigned j = i;
        if (__EnvVar)
          free(__EnvVar);
        if (!(p = __EnvVar = malloc(vlen + 1)))
        {
          return 0;
        }
        while ((*p++ = env[j++]) != '\0');
        return __EnvVar;
      }
      i += vlen;
      c = '\0';
    }

    if (c == '\0')
    {
      start = i + 1;
      if (env[start] == '\0')
      {
        // Reached the end of the list of environment variables
        return 0;
      }
    }
  }
}
#endif

#endif // _DOS

#ifdef _WINDOWS

#include "iwin32.h"

char* getenv(char* name)
{
  unsigned sz = 3, len;
  char *p = NULL, *p2;

  while (sz <= 32767)
  {
    if ((p2 = realloc(p, sz)) == NULL)
    {
      goto err;
    }
    p = p2;

    len = __GetEnvironmentVariableA(name, p, sz);

    if (len == 0)
    {
      goto err;
    }
    else if (len > sz)
    {
      sz = (sz << 1) + 1;
    }
    else
    {
      if (__EnvVar)
        free(__EnvVar);
      return (__EnvVar = p);
    }
  }

err:

  if (p)
    free(p);
  return NULL;
}

#endif // _WINDOWS

#ifdef UNIX_LIKE

extern char** __environ;

char* getenv(char* name)
{
  char** p = __environ;
  size_t l = strlen(name);
  while (*p)
    if (strlen(*p) > l &&
        !strncmp(*p, name, l) &&
        (*p)[l] == '=')
      return *p + l + 1;
    else
      ++p;
  return NULL;
}

#endif // UNIX_LIKE
