/*
Copyright (c) 2014, Alexey Frunze
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
/*                             Smaller C driver                              */
/*                                                                           */
/*     Invokes the core Smaller C compiler, the assembler (NASM) and the     */
/*     Smaller C linker.                                                     */
/*                                                                           */
/*     The command line options are similar to those of gcc.                 */
/*                                                                           */
/*                                 Main file                                 */
/*                                                                           */
/*****************************************************************************/

#ifndef HOST_LINUX
#ifndef HOST_WINDOWS
#ifndef HOST_DOS
#error HOST_LINUX or HOST_WINDOWS or HOST_DOS must be defined
#endif
#endif
#endif

#ifndef PATH_PREFIX
#define PATH_PREFIX "/usr/local"
#endif

#ifndef __SMALLER_C__

#include <limits.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#else

#ifndef __SMALLER_C_32__
#error must be compiled for 32-bit or huge mode(l)
#endif

#define NULL 0
typedef void FILE;
#define EOF (-1)
#define SEEK_SET 0
#define CHAR_BIT 8
#define INT_MAX 0x7FFFFFFF
#define LONG_MAX 0x7FFFFFFF
typedef unsigned size_t;

char* strtok(char*, char*);

void exit(int);

size_t strlen(char*);
char* strcpy(char*, char*);
char* strcat(char*, char*);
char* strchr(char*, int);
char* strrchr(char*, int);
int strcmp(char*, char*);
int strncmp(char*, char*, size_t);
char* strpbrk(char*, char*);
void* memcpy(void*, void*, size_t);
void* memset(void*, int, size_t);
void* memmove(void*, void*, size_t);

FILE* fopen(char*, char*);
int fclose(FILE*);
int fgetc(FILE*);
int puts(char*);
int sprintf(char*, char*, ...);
//int vsprintf(char*, char*, va_list);
int vsprintf(char*, char*, void*);
int printf(char*, ...);
int fprintf(FILE*, char*, ...);
//int vprintf(char*, va_list);
int vprintf(char*, void*);
size_t fread(void*, size_t, size_t, FILE*);
size_t fwrite(void*, size_t, size_t, FILE*);
int fseek(FILE*, long, int);
int remove(char*);

char* tmpnam(char*);

void* malloc(size_t);
void* realloc(void*, size_t);
void free(void*);

int system(char*);
char* getenv(char*);
#endif

typedef unsigned uint;
typedef unsigned long ulong;

typedef struct
{
  void** Buf;
  size_t Reserved;
  size_t Used;
} tDynArr;

typedef struct
{
  char name[16];
  char date[12];
  char uid[6];
  char gid[6];
  char mode[8];
  char size[10];
  char fmag[2];
} tArchiveFileHeader;

#define FBUF_SIZE 1024

char* OutName;

#define FormatDosComTiny  1
#define FormatDosExeSmall 2
#define FormatDosExeHuge  3
#define FormatFlat16      4
#define FormatFlat32      5
#define FormatWinPe32     6
#define FormatElf32       7
int OutputFormat = 0;

const char* LibName[] =
{
  NULL,
  "lcds.a", // FormatDosComTiny
  "lcds.a", // FormatDosExeSmall
  "lcdh.a", // FormatDosExeHuge
  NULL,     // FormatFlat16
  NULL,     // FormatFlat32
  "lcw.a",  // FormatWinPe32
  "lcl.a",  // FormatElf32
};

int verbose = 0;

int PreprocessWithGcc = 0;
int UseExternalPreprocessor = 0;

int DontLink = 0;

int CompileToAsm = 0;

int LinkStdLib = 0;
char* StdLibPath;
char* StdLib;

int DoArchive = 0;

char* PrepOptions;
size_t PrepOptionsLen;

char* CompilerOptions;
size_t CompilerOptionsLen;

char* AssemblerOptions;
size_t AssemblerOptionsLen;

char* LinkerOptions;
size_t LinkerOptionsLen;

char* ArchiveFiles;
size_t ArchiveFilesLen;

char* TemporaryFiles;
size_t TemporaryFilesLen;

int InputFileCnt = 0;

tDynArr OpenFiles;

#ifdef __SMALLER_C__
#ifdef DETERMINE_VA_LIST
// 2 if va_list is a one-element array containing a pointer
//   (typical for x86 Open Watcom C/C++)
// 1 if va_list is a pointer
//   (typical for Turbo C++, x86 gcc)
// 0 if va_list is something else, and
//   the code may have long crashed by now
int VaListType = 0;

// Attempts to determine the type of va_list as
// expected by the standard library
void DetermineVaListType(void)
{
  void* testptr[2];
  // hopefully enough space to sprintf() 3 pointers using "%p"
  char testbuf[3][CHAR_BIT * sizeof(void*) + 1];

  // TBD!!! This is not good. Really need the va_something macros.
  // Test whether va_list is a pointer to the first optional parameter or
  // an array of one element containing said pointer
  testptr[0] = &testptr[1];
  testptr[1] = &testptr[0];
  memset(testbuf, '\0', sizeof(testbuf));
  sprintf(testbuf[0], "%p", testptr[0]);
  sprintf(testbuf[1], "%p", testptr[1]);
  vsprintf(testbuf[2], "%p", &testptr[0]);
  if (!strcmp(testbuf[2], testbuf[0]))
  {
    // va_list is a pointer
    VaListType = 1;
  }
  else if (!strcmp(testbuf[2], testbuf[1]))
  {
    // va_list is a one-element array containing a pointer
    VaListType = 2;
  }
  else
  {
    // va_list is something else, and
    // the code may have long crashed by now
    printf("Internal error: Indeterminate underlying type of va_list\n");
    exit(-1);
  }
}
#endif // DETERMINE_VA_LIST
#endif // __SMALLER_C__

void DeleteTemporaryFiles(void)
{
  size_t i;
  for (i = 0; i < TemporaryFilesLen; )
  {
    size_t len = strlen(TemporaryFiles + i);
    remove(TemporaryFiles + i);
    i += len + 1;
  }
}

void error(char* format, ...)
{
  size_t i;
#ifndef __SMALLER_C__
  va_list vl;
  va_start(vl, format);
#else
  void* vl = &format + 1;
#endif

  // Make sure all files get closed if compilation fails (DOS doesn't like leaked file handles)
  for (i = 0; i < OpenFiles.Reserved; i++)
    if (OpenFiles.Buf[i])
      fclose(OpenFiles.Buf[i]);

  if (OutName)
    remove(OutName);
  DeleteTemporaryFiles();

  puts("");

#ifndef __SMALLER_C__
  vprintf(format, vl);
#else
  // TBD!!! This is not good. Really need the va_something macros.
#ifdef DETERMINE_VA_LIST
  if (VaListType == 2)
  {
    // va_list is a one-element array containing a pointer
    vprintf(format, &vl);
  }
  else // if (VaListType == 1)
  // fallthrough
#endif // DETERMINE_VA_LIST
  {
    // va_list is a pointer
    vprintf(format, vl);
  }
#endif // __SMALLER_C__

#ifndef __SMALLER_C__
  va_end(vl);
#endif

  exit(-1);
}

void errMem(void)
{
  error("Out of memory\n");
}

void* Malloc(size_t size)
{
  void* p = malloc(size);
  if (!p)
    errMem();
  return p;
}

void* Realloc(void* ptr, size_t size)
{
  void* p = realloc(ptr, size);
  if (!p)
    errMem();
  return p;
}

void** DynArrFindSpot(tDynArr* pArr)
{
  size_t i, oldcnt, oldsz, newcnt, newsz;
  void* p = NULL;

  if (pArr->Used < pArr->Reserved)
    for (i = 0; i < pArr->Reserved; i++)
      if (!pArr->Buf[i])
        return pArr->Buf + i;

  oldcnt = pArr->Reserved;
  oldsz = oldcnt * sizeof pArr->Buf[0];
  newcnt = oldcnt ? oldcnt * 2 : 1;
  newsz = newcnt * sizeof pArr->Buf[0];

  if (newcnt < oldcnt ||
      newsz / sizeof pArr->Buf[0] != newcnt ||
      !(p = realloc(pArr->Buf, newsz)))
    errMem();

  pArr->Buf = p;
  pArr->Reserved = newcnt;
  memset(pArr->Buf + oldcnt, 0, newsz - oldsz);
  return pArr->Buf + oldcnt;
}

void DynArrFillSpot(tDynArr* pArr, void** spot, void* p)
{
  *spot = p;
  pArr->Used++;
}

void DynArrVacateSpot(tDynArr* pArr, void* p)
{
  size_t i;

  for (i = 0; i < pArr->Reserved; i++)
    if (pArr->Buf[i] == p)
    {
      pArr->Buf[i] = NULL;
      pArr->Used--;
      break;
    }
}

FILE* Fopen(const char* filename, const char* mode)
{
  void** spot = DynArrFindSpot(&OpenFiles);
  FILE* stream = fopen(filename, mode);
  if (!stream)
    error("Can't open/create file '%s'\n", filename);
  DynArrFillSpot(&OpenFiles, spot, stream);
  return stream;
}

void Fclose(FILE* stream)
{
  DynArrVacateSpot(&OpenFiles, stream);
  if (fclose(stream))
    error("Can't close a file\n");
}

void Fseek(FILE* stream, long offset, int whence)
{
  int r = fseek(stream, offset, whence);
  if (r)
    error("Can't seek a file\n");
}

void Fread(void* ptr, size_t size, FILE* stream)
{
  size_t r = fread(ptr, 1, size, stream);
  if (r != size)
    error("Can't read a file\n");
}

void Fwrite(const void* ptr, size_t size, FILE* stream)
{
  size_t r = fwrite(ptr, 1, size, stream);
  if (r != size)
    error("Can't write a file\n");
}

// Determines binary file size portably (when stat()/fstat() aren't available)
long fsize(FILE* binaryStream)
{
  long ofs, ofs2;
  int result;

  if (fseek(binaryStream, 0, SEEK_SET) != 0 ||
      fgetc(binaryStream) == EOF)
    return 0;

  ofs = 1;

  while ((result = fseek(binaryStream, ofs, SEEK_SET)) == 0 &&
         (result = (fgetc(binaryStream) == EOF)) == 0 &&
         ofs <= LONG_MAX / 4 + 1)
    ofs *= 2;

  // If the last seek failed, back up to the last successfully seekable offset
  if (result != 0)
    ofs /= 2;

  for (ofs2 = ofs / 2; ofs2 != 0; ofs2 /= 2)
    if (fseek(binaryStream, ofs + ofs2, SEEK_SET) == 0 &&
        fgetc(binaryStream) != EOF)
      ofs += ofs2;

  // Return -1 for files longer than LONG_MAX
  if (ofs == LONG_MAX)
    return -1;

  return ofs + 1;
}

// Expands "@filename" in program arguments into arguments contained within file "filename".
// This is a workaround for short DOS command lines limited to 126 characters.
// Note, the expansion is NOT recursive.
// TBD!!! parse the file the same way as the command line.
void fatargs(int* pargc, char*** pargv)
{
  int i, j = 0;
  char** pp;
  int pcnt = *pargc;

  if (pcnt < 2)
    return;

  for (i = 1; i < pcnt; i++)
    if ((*pargv)[i][0] == '@')
      break;
  if (i >= pcnt)
    return;

  if ((pp = malloc(++pcnt * sizeof(char*))) == NULL) // there's supposed to be one more NULL pointer argument
  {
    errMem();
  }

  pp[j++] = (*pargv)[0]; // skip program name

  for (i = 1; i < *pargc; i++)
    if ((*pargv)[i][0] != '@')
    {
      pp[j++] = (*pargv)[i]; // it's not an name of a file with arguments, treat it as an argument
    }
    else
    {
      FILE* f;
      long fsz;
      if (!(f = fopen((*pargv)[i] + 1, "rb")))
      {
        pp[j++] = (*pargv)[i]; // there's no file by this name, treat it as an argument
        continue;
      }
      if ((fsz = fsize(f)) < 0)
      {
        fclose(f);
        errMem();
      }
      if (fsz > 0)
      {
        size_t sz;
        char* buf;
        if ((sz = fsz) == (ulong)fsz &&
            sz + 1 > sz &&
            (buf = malloc(sz + 1)) != NULL)
        {
          static const char* const sep = "\f\n\r\t\v ";
          char* p;
          memset(buf, '\0', sz + 1);
          fseek(f, 0, SEEK_SET);
          buf[fread(buf, 1, sz, f)] = '\0';
          p = strtok(buf, sep);
          pcnt--; // don't count the file name as an argument, count only what's inside
          while (p)
          {
            size_t s;
            if (++pcnt == INT_MAX ||
                (s = (unsigned)pcnt * sizeof(char*)) / sizeof(char*) != (unsigned)pcnt ||
                (pp = realloc(pp, s)) == NULL)
            {
              fclose(f);
              errMem();
            }
            pp[j++] = p;
            p = strtok(NULL, sep);
          }
        }
        else
        {
          fclose(f);
          errMem();
        }
      }
      fclose(f);
    }

  pp[j] = NULL; // there's supposed to be one more NULL pointer argument
  *pargc = j;
  *pargv = pp;
}

int EscapingNeeded(char* s)
{
  // Looks like DOS' COMMAND.COM and Windows' cmd.exe handle %
  // specially even inside double quotes (e.g. %path% would always expand).
  return *s == '\0' || strpbrk(s, " \t\"<>&|^") != NULL;
}

// TBD!!! I should probably abandon the idea of launching subordinates via
// shell (using system()) and instead use exec*()/CreateProcess() and such 
// to avoid this quoting/escaping mess.
size_t Escape(char* out, char* in, size_t outsz)
{
  size_t sz = 0;
  int c;
  size_t slashes = 0;

  if (sz++ < outsz)
    *out++ = '"';

  while ((c = *in++) != '\0')
  {
    if (c == '\\')
    {
      do
      {
        slashes++;
      } while ((c = *in++) == '\\');

      if (c == '"' || c == '\0')
        slashes <<= 1;
    }

    while (slashes)
    {
      if (sz++ < outsz)
        *out++ = '\\';
      slashes--;
    }

    if (c == '\0')
      break;

    if (c == '"')
    {
      if (sz++ < outsz)
        *out++ = '\\';
    }

    if (sz++ < outsz)
      *out++ = c;
  }

  if (sz++ < outsz)
    *out++ = '"';

  if (sz++ < outsz)
    *out++ = '\0';

  return sz;
}

void AddOptionInner(char** options, size_t* len, char* option, int escape)
{
  size_t l = strlen(option);
  char* escaped = NULL;

  if (escape && EscapingNeeded(option))
  {
    size_t sz = Escape(NULL, option, 0);
    escaped = Malloc(sz);
    Escape(escaped, option, sz);
    option = escaped;
    l = sz - 1;
  }

  if (!*options)
  {
    *options = Malloc(l + 1);
    strcpy(*options, option);
    *len = l;
  }
  else
  {
    *options = Realloc(*options, *len + 1/*space*/ + l + 1/*NUL*/);
    (*options)[*len] = ' ';
    strcpy(*options + *len + 1, option);
    (*len) += 1 + l;
  }

  if (escaped)
    free(escaped);
}

// Adds a command-line option, escaping it if needed
void AddOption(char** options, size_t* len, char* option)
{
  AddOptionInner(options, len, option, 1);
}

// Adds a command-line option (or several, space-delimited), without escaping
void AddOptions(char** options, size_t* len, char* optionz)
{
  AddOptionInner(options, len, optionz, 0);
}

void AddFile(char** files, size_t* len, char* file)
{
  size_t l = strlen(file);
  if (!*files)
  {
    *files = Malloc(l + 1);
    strcpy(*files, file);
    *len = l;
  }
  else
  {
    *files = Realloc(*files, *len + 1/*NUL*/ + l + 1/*NUL*/);
    strcpy(*files + *len + 1, file);
    (*len) += 1 + l;
  }
}

void System(char* cmd)
{
  size_t len;
  int res;

  if (!cmd || !(len = strlen(cmd)))
    error("Bad command '%s'\n", cmd ? cmd : "");

  if (verbose)
    printf("%s\n", cmd);

#ifdef HOST_DOS
  // Commands in DOS are typically executed as "%COMSPEC% /C COMMAND"
  // with the system call receiving an '\r'-terminated string "#/C COMMAND\r",
  // where the '#' char is actually the length of the string (excluding '#' and '\r').
  // The entire "#/C COMMAND\r" cannot be longer than 128 bytes or, equivalently,
  // "/C COMMAND" cannot be longer than 126 bytes or, equivalently,
  // "COMMAND" cannot be longer than 123 bytes.
  // When "COMMAND" is longer than 123 bytes, create a temporary file containing
  // COMMAND's params and pass its name as @name instead of the params.
  if (len > 123)
  {
    char* p = strchr(cmd, ' ');
    size_t l;
    char* ntmp = tmpnam(NULL);
    FILE* ftmp;
    char* cmd2;

    if (!p)
      error("Bad command '%s'\n", cmd);
    l = p + 1 - cmd;

    if (!ntmp)
      error("Failed to generate temporary file name\n");
    // DOS is not multi-tasking and so there shouldn't be any race condition
    // between doing tmpnam() and fopen().
    ftmp = Fopen(ntmp, "wb");
    AddFile(&TemporaryFiles, &TemporaryFilesLen, ntmp);
    if (len > l)
      Fwrite(p + 1, len - l, ftmp);
    Fclose(ftmp);

    cmd2 = Malloc(l/*name and space*/ + 1/*@*/ + strlen(ntmp) + 1/*NUL*/);
    memcpy(cmd2, cmd, l);
    cmd2[l] = '@';
    strcpy(cmd2 + l + 1, ntmp);

    if (verbose)
      printf("%s\n", cmd2);

    res = system(cmd2); // typically returns 0 in DOS even when an error occurs, oops

    free(cmd2);

    remove(ntmp);
  }
  else
  // fallthrough
#endif
  {
    res = system(cmd); // typically returns 0 in DOS even when an error occurs, oops
  }

  if (res)
  {
    if (verbose)
      error("Executed command failed\n");
    else
      error("Failed command '%s'\n", cmd);
  }
}

void Compile(char* name)
{
  size_t len = strlen(name);
  int type = 0, subtype = 0;
  char* iName = NULL;
  char* asmName = NULL;

  if (len > 4 && name[len - 4] == '.')
  {
    if ((name[len-3] == 'A' || name[len-3] == 'a') &&
        (name[len-2] == 'S' || name[len-2] == 's') &&
        (name[len-1] == 'M' || name[len-1] == 'm'))
      type = 'a';
  }
  if (len > 2 && name[len - 2] == '.')
  {
    switch (name[len - 1])
    {
    case 'c': case 'C':
      type = 'c';
      subtype = 'c';
      break;
    case 'i': case 'I':
      type = 'c';
      subtype = 'i';
      break;
    case 'o': case 'O':
      type = 'O';
      break;
    case 'a': case 'A':
      type = 'A';
      break;
    }
  }

  if (!type)
    error("Unknown type of file '%s'\n", name);

  if (type == 'O' || type == 'A')
  {
    // Nothing to do with object and library files (.o and .a)
    if (!DontLink)
      AddOption(&LinkerOptions, &LinkerOptionsLen, name);
    else if (DoArchive && type == 'O')
      AddFile(&ArchiveFiles, &ArchiveFilesLen, name);
    return;
  }

  // Preprocess first, if needed
  if (UseExternalPreprocessor && subtype == 'c')
  {
    char* cmd = NULL;
    size_t cmdlen = 0;

    iName = Malloc(len + 1/*NUL*/);
    strcpy(iName, name);
    iName[len - 1] = 'i'; // .c -> .i

    AddOptions(&cmd, &cmdlen, PrepOptions);
    AddOption(&cmd, &cmdlen, name);
    AddOption(&cmd, &cmdlen, "-o");
    AddOption(&cmd, &cmdlen, iName);

    AddFile(&TemporaryFiles, &TemporaryFilesLen, iName);
    System(cmd);

    free(cmd);

    name = iName;
  }

  if (type == 'c')
  {
    char* cmd = NULL;
    size_t cmdlen = 0;

    if (InputFileCnt == 1 && OutName && CompileToAsm)
    {
      // Compiling one C file to an assembly file with a given name
      asmName = OutName;
    }
    else
    {
      asmName = Malloc(len + 2/*.c -> .asm*/ + 1/*NUL*/);
      strcpy(asmName, name);
      strcpy(asmName + len - 1, "asm");
    }

    AddOptions(&cmd, &cmdlen, CompilerOptions);
    AddOption(&cmd, &cmdlen, name);
    AddOption(&cmd, &cmdlen, asmName);

    AddFile(&TemporaryFiles, &TemporaryFilesLen, asmName);
    // TBD!!! also, if CompileToAsm==0, add .o file to temps here
    System(cmd);

    free(cmd);

    if (CompileToAsm)
    {
      if (iName)
      {
        remove(iName);
        free(iName);
      }
      if (asmName != OutName)
        free(asmName);
      return;
    }
    // fallthrough
  }

  if (!CompileToAsm)
  {
    char* objName;
    char* cmd = NULL;
    size_t cmdlen = 0;

    if (InputFileCnt == 1 && OutName && DontLink && !DoArchive)
    {
      // Compiling one C or assembly file to an object file with a given name
      objName = OutName;
    }
    else
    {
      objName = Malloc(len + 1/*NUL*/);
      strcpy(objName, name);
      if (asmName)
        objName[len - 1] = 'o'; // .c -> .o
      else
        strcpy(objName + len - 3, "o"); // .asm -> .o
    }

    AddOptions(&cmd, &cmdlen, AssemblerOptions);
    AddOption(&cmd, &cmdlen, asmName ? asmName : name);
    AddOption(&cmd, &cmdlen, "-o");
    AddOption(&cmd, &cmdlen, objName);

    System(cmd);

    free(cmd);

    if (asmName)
    {
      remove(asmName); // remove temporary asm file
      free(asmName);
    }

    if (!DontLink)
    {
      AddOption(&LinkerOptions, &LinkerOptionsLen, objName);
      // Temporary object files will be removed at the end
      AddFile(&TemporaryFiles, &TemporaryFilesLen, objName);
    }
    else if (DoArchive)
    {
      AddFile(&ArchiveFiles, &ArchiveFilesLen, objName);
      AddFile(&TemporaryFiles, &TemporaryFilesLen, objName);
    }

    if (objName != OutName)
      free(objName);
  }

  if (iName)
  {
    remove(iName);
    free(iName);
  }
}

void Link(void)
{
  if (StdLib)
    AddOption(&LinkerOptions, &LinkerOptionsLen, StdLib);

  if (OutName)
  {
    AddOption(&LinkerOptions, &LinkerOptionsLen, "-o");
    AddOption(&LinkerOptions, &LinkerOptionsLen, OutName);
  }

  System(LinkerOptions);

#ifdef HOST_LINUX
  if (OutputFormat == FormatElf32 && OutName)
  {
    char* cmd = NULL;
    size_t cmdlen = 0;
    AddOptions(&cmd, &cmdlen, "chmod +x");
    AddOption(&cmd, &cmdlen, OutName);
    System(cmd);
    free(cmd);
  }
#endif

  DeleteTemporaryFiles();
}

void Archive(void)
{
  static unsigned char buf[FBUF_SIZE];
  size_t i;
  FILE* fout = Fopen(OutName, "wb");

  Fwrite("!<arch>\n", 8, fout);

  for (i = 0; i < ArchiveFilesLen; )
  {
    char* name = ArchiveFiles + i;
    char* name2 = name;
    size_t len = strlen(name);
    size_t len2;
    char* pslash = strrchr(name, '/');
    char* pbackslash = strrchr(name, '\\');
    FILE* f = Fopen(name, "rb");
    long sz = fsize(f);
    ulong sz2 = 0;
    tArchiveFileHeader fh;
    if (sz < 0 || sz > 0x20000000) // 512MB cap to simplify overflow handling, should be enough for all purposes
      error("File '%s' too large\n", name);

    // Find where the file path ends in the file name

    // In DOS/Windows paths can contain either '\\' or '/' as a separator between directories,
    // choose the right-most
    if (pslash && pbackslash)
    {
      if (pslash < pbackslash)
        pslash = pbackslash;
    }
    else if (!pslash)
    {
      pslash = pbackslash;
    }

#ifndef HOST_LINUX
    // If there's no slash, it could be "c:file" in DOS/Windows
    if (!pslash && ((*name >= 'A' && *name <= 'Z') || (*name >= 'a' && *name <= 'z')) && name[1] == ':')
      pslash = name + 1;
#endif

    if (pslash)
      name2 = pslash + 1;

    len2 = strlen(name2);

    memset(&fh, ' ', sizeof fh);
    if (len2 <= 15)
    {
      memcpy(fh.name, name2, len2);
      fh.name[len2] = '/';
    }
    else
    {
      ulong l = len2;
      fh.name[sprintf(fh.name, "#1/%lu", l)] = ' '; // Use BSD(in-place) format for long names
    }
    memcpy(fh.date, "1388534400", sizeof "1388534400" - 1); // TBD??? use actual file date/time???
    fh.uid[0] = '0';
    fh.gid[0] = '0';
    memcpy(fh.mode, "100666", sizeof "100666" - 1); // S_IFREG | rw-rw-rw-
    if (len2 <= 15)
    {
      ulong l = sz;
      fh.size[sprintf(fh.size, "%lu", l)] = ' ';
    }
    else
    {
      ulong l = sz;
      l += len2;
      fh.size[sprintf(fh.size, "%lu", l)] = ' ';
    }
    fh.fmag[0] = 0x60;
    fh.fmag[1] = 0x0A;

    Fwrite(&fh, sizeof fh, fout);

    if (len2 > 15)
      Fwrite(name2, len2, fout);

    Fseek(f, 0, SEEK_SET);

    for (;;)
    {
      size_t csz = fread(buf, 1, FBUF_SIZE, f);
      if (!csz)
        break;
      Fwrite(buf, csz, fout);
      sz2 += csz;
    }
    if ((ulong)sz != sz2)
      error("Failed to archive file '%s'\n", name);

    if (len2 > 15)
      sz2 += len2;
    if (sz2 & 1)
      Fwrite("\n", 1, fout);

    Fclose(f);
    i += len + 1;
  }

  Fclose(fout);

  DeleteTemporaryFiles();
}

#ifndef HOST_LINUX
// Returns the path to the executable in forms like these (not an exhaustive list):
// - "c:\\path"
// - "c:"
// - "."
char* exepath(char* argv0)
{
  char* name = argv0;
  char* pslash = strrchr(name, '/');
  char* pbackslash = strrchr(name, '\\');
  size_t len;
  FILE* f;
  char* p;
  char* epaths;
  char* paths;
  char* sep;
  char* path;

  // First, try to extract the path from argv[0]

  // In DOS/Windows paths can contain either '\\' or '/' as a separator between directories,
  // choose the right-most
  if (pslash && pbackslash)
  {
    if (pslash < pbackslash)
      pslash = pbackslash;
  }
  else if (!pslash)
  {
    pslash = pbackslash;
  }

  // If there's no slash, it could be "c:file"
  if (!pslash && ((*name >= 'A' && *name <= 'Z') || (*name >= 'a' && *name <= 'z')) && name[1] == ':')
    pslash = name + 2 /* keep an extra char to retain the colon */;

  // If there's a slash or a colon, we're done
  if (pslash)
  {
    len = pslash - name;
    p = Malloc(len + 1/*NUL*/);
    memcpy(p, name, len);
    p[len] = '\0';
    return p;
  }

  // If there's no path in argv[0], the file can be found either in the
  // current directory or in one of the paths specified in the "PATH"
  // environment variable.

  // Note: I could've used GetModuleFileNameA(NULL) on Windows, but that would
  // create an explicit dependency on <windows.h> and Windows XP or later.

  // Append ".exe" if necessary
  // (".com" applies to DOS only, and DOS programs get the full path in the PSP,
  //  which should have just been handled by the code above)
  len = strlen(name);
  if (!(len > 4 &&
        name[len-4] == '.' &&
        (name[len-3] == 'E' || name[len-3] == 'e') &&
        (name[len-2] == 'X' || name[len-2] == 'x') &&
        (name[len-1] == 'E' || name[len-1] == 'e')))
  {
    len += sizeof ".exe" - 1/*NUL*/;
    name = Malloc(len + 1/*NUL*/);
    strcpy(name, argv0);
    strcat(name, ".exe");
  }

  // Check the current directory
  if ((f = fopen(name, "rb")) != NULL)
  {
    fclose(f);
    if (name != argv0)
      free(name);
    p = Malloc(sizeof ".");
    strcpy(p, ".");
    return p;
  }

  // All that's left is to try %PATH%

  if (!(epaths = getenv("PATH")))
  {
    if (name != argv0)
      free(name);
    return NULL;
  }

  paths = Malloc(strlen(epaths) + 1/*NUL*/);
  strcpy(paths, epaths);

  sep = ";";
  path = strtok(paths, sep);
  while (path)
  {
    size_t plen = strlen(path);
    p = Malloc(plen + 1/*slash*/ + len + 1/*NUL*/);

    strcpy(p, path);
    if (path[plen-1] != '\\' && path[plen-1] != '/')
    {
      strcat(p, "\\");
      plen++;
    }
    strcat(p, name);

    if ((f = fopen(p, "rb")) != NULL)
    {
      fclose(f);
      free(paths);
      if (name != argv0)
        free(name);
      p[--plen] = '\0';
      return p;
    }

    free(p);

    path = strtok(NULL, sep);
  }

  free(paths);
  if (name != argv0)
    free(name);

  return NULL;
}
#endif

char* SystemFileExists(const char* path, int slash, const char* pathsuffix, const char* name)
{
  size_t plen = strlen(path);
  char* p = Malloc(plen + 1/*slash*/ + (pathsuffix ? strlen(pathsuffix) : 0) + strlen(name) + 1/*NUL*/);
  FILE* f;
  strcpy(p, path);
  if (slash && plen && path[plen-1] != '/' && path[plen-1] != '\\')
    p[plen] = slash, p[plen+1] = '\0';
  if (pathsuffix)
    strcat(p, pathsuffix);
  strcat(p, name);
  if ((f = fopen(p, "rb")) != NULL)
  {
    fclose(f);
    return p;
  }
  free(p);
  return NULL;
}

void Pass2Prep(char* s);

void AddSystemPaths(char* argv0)
{
  char* epath;
  char* pinclude = NULL;

  (void)argv0;

  if (LinkStdLib && StdLibPath)
    StdLib = SystemFileExists(StdLibPath, '/', NULL, LibName[OutputFormat]);

  for (int n = 0;; n++) {
    switch (n) {
    case 0:
      epath = getenv("SMLRC");
      break;
#ifdef HOST_LINUX
    case 1:
      epath = getenv("HOME");
      break;
    case 2:
      epath = PATH_PREFIX;
      break;
#else
    case 1:
      epath = exepath(argv0);
      break;
#endif
    default:
      goto endsearch;
    }
    if (!epath)
      continue;
    if (!pinclude)
    {
      pinclude = SystemFileExists(epath, '/', "smlrc/include/", "limits.h");
      if (pinclude)
        *strrchr(pinclude, '/') = '\0';
    }
    if (LinkStdLib && !StdLib)
      StdLib = SystemFileExists(epath, '/', "smlrc/lib/", LibName[OutputFormat]);

    if (pinclude && (StdLib || !LinkStdLib))
      goto endsearch;
  }

endsearch:

  if (pinclude)
  {
    Pass2Prep(PreprocessWithGcc ? "-isystem" : "-SI");
    Pass2Prep(pinclude);
  }

  // TBD??? Issue a warning if the location of the system headers and libraries was niether provided nor found???
}

void Pass2Prep(char* s)
{
  if (!UseExternalPreprocessor)
    AddOption(&CompilerOptions, &CompilerOptionsLen, s);
  else
    AddOption(&PrepOptions, &PrepOptionsLen, s);
}

void DefineMacro(char* s)
{
  Pass2Prep("-D");
  Pass2Prep(s);
}

int main(int argc, char* argv[])
{
  int i;
  int UnsignedChar = 0;

#ifdef __SMALLER_C__
#ifdef DETERMINE_VA_LIST
  DetermineVaListType();
#endif
#endif

  fatargs(&argc, &argv);

#ifdef HOST_LINUX
  AddOption(&CompilerOptions, &CompilerOptionsLen, "smlrc");
  AddOptions(&AssemblerOptions, &AssemblerOptionsLen, "nasm -f elf");
  AddOption(&LinkerOptions, &LinkerOptionsLen, "smlrl");
#else
  // Use explicit extensions (".exe") to let system() know that
  // these commands are not COMMAND.COM's internal commands and
  // should be executed directly and not via "COMMAND.COM /C command",
  // if possible.
  // This helps recover the program exit status under DOS and thus
  // stop compilation as soon as one compilation stage fails.
  AddOption(&CompilerOptions, &CompilerOptionsLen, "smlrc.exe");
  AddOptions(&AssemblerOptions, &AssemblerOptionsLen, "nasm.exe -f elf");
  AddOption(&LinkerOptions, &LinkerOptionsLen, "smlrl.exe");
#endif

  // Detect that gcc's preprocessor is to be used.
  // Do this early as other options will depend on it.
  // This is ugly.
  UseExternalPreprocessor = PreprocessWithGcc = getenv("SMLRPPG") != NULL;
  for (i = 1; i < argc; i++)
  {
    if (!strcmp(argv[i], "-ppg"))
    {
      UseExternalPreprocessor = PreprocessWithGcc = 1;
      memmove(argv + i, argv + i + 1, (argc - i) * sizeof(char*));
      argc--;
      break;
    }
  }
  if (PreprocessWithGcc)
  {
#ifdef HOST_LINUX
    AddOptions(&PrepOptions, &PrepOptionsLen, "gcc -E -nostdinc");
#else
    AddOptions(&PrepOptions, &PrepOptionsLen, "gcc.exe -E -nostdinc");
#endif
  }

  for (i = 1; i < argc; i++)
  {
    if (!strcmp(argv[i], "-verbose") || !strcmp(argv[i], "-v"))
    {
      verbose = 1;
      argv[i] = NULL;
      continue;
    }
    else if (!strcmp(argv[i], "-o"))
    {
      if (i + 1 < argc)
      {
        argv[i++] = NULL;
        OutName = argv[i];
        argv[i] = NULL;
        continue;
      }
    }
    else if (!strcmp(argv[i], "-map") ||
             !strcmp(argv[i], "-entry") ||
             !strcmp(argv[i], "-origin") ||
             !strcmp(argv[i], "-stack"))
    {
      if (i + 1 < argc)
      {
        AddOption(&LinkerOptions, &LinkerOptionsLen, argv[i]);
        argv[i++] = NULL;
        AddOption(&LinkerOptions, &LinkerOptionsLen, argv[i]);
        argv[i] = NULL;
        continue;
      }
    }
    else if (!strcmp(argv[i], "-signed-char") ||
             !strcmp(argv[i], "-unsigned-char") ||
             !strcmp(argv[i], "-leading-underscore") ||
             !strcmp(argv[i], "-no-leading-underscore") ||
             !strcmp(argv[i], "-winstack") ||
             !strcmp(argv[i], "-Wall"))
    {
      if (!strcmp(argv[i], "-unsigned-char"))
        UnsignedChar = 1;
      else if (!strcmp(argv[i], "-signed-char"))
        UnsignedChar = 0;
      AddOption(&CompilerOptions, &CompilerOptionsLen, argv[i]);
      argv[i] = NULL;
      continue;
    }
    else if (!strcmp(argv[i], "-nobss"))
    {
      AddOption(&CompilerOptions, &CompilerOptionsLen, argv[i]);
      AddOption(&LinkerOptions, &LinkerOptionsLen, argv[i]);
      argv[i] = NULL;
      continue;
    }
    else if (!strcmp(argv[i], "-tiny"))
    {
      OutputFormat = FormatDosComTiny;
      AddOption(&CompilerOptions, &CompilerOptionsLen, "-seg16");
      AddOption(&LinkerOptions, &LinkerOptionsLen, argv[i]);
      argv[i] = NULL;
      continue;
    }
    else if (!strcmp(argv[i], "-dost"))
    {
      OutputFormat = FormatDosComTiny;
      AddOption(&CompilerOptions, &CompilerOptionsLen, "-seg16");
      DefineMacro("_DOS");
      AddOption(&LinkerOptions, &LinkerOptionsLen, "-tiny");
      LinkStdLib = 1;
      argv[i] = NULL;
      continue;
    }
    else if (!strcmp(argv[i], "-small"))
    {
      OutputFormat = FormatDosExeSmall;
      AddOption(&CompilerOptions, &CompilerOptionsLen, "-seg16");
      AddOption(&LinkerOptions, &LinkerOptionsLen, argv[i]);
      argv[i] = NULL;
      continue;
    }
    else if (!strcmp(argv[i], "-doss"))
    {
      OutputFormat = FormatDosExeSmall;
      AddOption(&CompilerOptions, &CompilerOptionsLen, "-seg16");
      DefineMacro("_DOS");
      AddOption(&LinkerOptions, &LinkerOptionsLen, "-small");
      LinkStdLib = 1;
      argv[i] = NULL;
      continue;
    }
    else if (!strcmp(argv[i], "-huge"))
    {
      OutputFormat = FormatDosExeHuge;
      AddOption(&CompilerOptions, &CompilerOptionsLen, argv[i]);
      AddOption(&LinkerOptions, &LinkerOptionsLen, argv[i]);
      argv[i] = NULL;
      continue;
    }
    else if (!strcmp(argv[i], "-dosh"))
    {
      OutputFormat = FormatDosExeHuge;
      AddOption(&CompilerOptions, &CompilerOptionsLen, "-huge");
      DefineMacro("_DOS");
      AddOption(&LinkerOptions, &LinkerOptionsLen, "-huge");
      LinkStdLib = 1;
      argv[i] = NULL;
      continue;
    }
    else if (!strcmp(argv[i], "-pe"))
    {
      OutputFormat = FormatWinPe32;
      AddOption(&CompilerOptions, &CompilerOptionsLen, "-seg32");
      AddOption(&LinkerOptions, &LinkerOptionsLen, argv[i]);
      argv[i] = NULL;
      continue;
    }
    else if (!strcmp(argv[i], "-win"))
    {
      OutputFormat = FormatWinPe32;
      AddOption(&CompilerOptions, &CompilerOptionsLen, "-seg32");
      AddOption(&CompilerOptions, &CompilerOptionsLen, "-winstack");
      DefineMacro("_WINDOWS");
      AddOption(&LinkerOptions, &LinkerOptionsLen, "-pe");
      LinkStdLib = 1;
      argv[i] = NULL;
      continue;
    }
    else if (!strcmp(argv[i], "-elf"))
    {
      OutputFormat = FormatElf32;
      AddOption(&CompilerOptions, &CompilerOptionsLen, "-seg32");
      AddOption(&LinkerOptions, &LinkerOptionsLen, argv[i]);
      argv[i] = NULL;
      continue;
    }
    else if (!strcmp(argv[i], "-linux"))
    {
      OutputFormat = FormatElf32;
      AddOption(&CompilerOptions, &CompilerOptionsLen, "-seg32");
      DefineMacro("_LINUX");
      AddOption(&LinkerOptions, &LinkerOptionsLen, "-elf");
      argv[i] = NULL;
      LinkStdLib = 1;
      continue;
    }
    else if (!strcmp(argv[i], "-flat16"))
    {
      OutputFormat = FormatFlat16;
      AddOption(&CompilerOptions, &CompilerOptionsLen, "-seg16");
      AddOption(&LinkerOptions, &LinkerOptionsLen, argv[i]);
      argv[i] = NULL;
      continue;
    }
    else if (!strcmp(argv[i], "-flat32"))
    {
      OutputFormat = FormatFlat32;
      AddOption(&CompilerOptions, &CompilerOptionsLen, "-seg32");
      AddOption(&LinkerOptions, &LinkerOptionsLen, argv[i]);
      argv[i] = NULL;
      continue;
    }
    else if (!strcmp(argv[i], "-c"))
    {
      DontLink = 1;
      argv[i] = NULL;
      continue;
    }
    else if (!strcmp(argv[i], "-S"))
    {
      DontLink = CompileToAsm = 1;
      argv[i] = NULL;
      continue;
    }
    else if (argv[i][0] == '-' &&
             (argv[i][1] == 'D'/*-D*/ ||
              argv[i][1] == 'I'/*-I*/ ||
              (argv[i][1] == 'S' && argv[i][2] == 'I')/*-SI*/))
    {
      int len = 2 + (argv[i][1] == 'S');
      char opt[3/*longest is -SI*/+1/*NUL*/], *popt = opt;
      char* pparam = argv[i] + len;
      int err = 0;

      if (argv[i][len] != '\0')
      {
        // Handle "-Dmacro", "-Ipath", "-SIpath"
        memcpy(opt, argv[i], len);
        opt[len] = '\0';
        argv[i] = NULL;
      }
      else if (i + 1 < argc)
      {
        // Handle "-D macro", "-I path", "-SI path"
        popt = argv[i];
        argv[i++] = NULL;
        pparam = argv[i];
        argv[i] = NULL;
      }
      else
      {
        err = 1;
      }

      if (!err)
      {
        Pass2Prep((PreprocessWithGcc && !strcmp(popt, "-SI")) ? "-isystem" : popt);
        Pass2Prep(pparam);
        continue;
      }
    }
    else if (!strncmp(argv[i], "-SL", 3))
    {
      if (argv[i][3] != '\0')
      {
        // Handle "-SLpath"
        StdLibPath = argv[i] + 3;
        argv[i] = NULL;
        continue;
      }
      else if (i + 1 < argc)
      {
        // Handle "-SL path"
        argv[i++] = NULL;
        StdLibPath = argv[i];
        argv[i] = NULL;
        continue;
      }
    }

    if (argv[i][0] == '-')
      error("Invalid or unsupported command line option '%s'\n", argv[i]);

    InputFileCnt++;
  }

  if (!InputFileCnt)
    error("No inputs\n");

  if (!OutputFormat)
  {
#ifdef HOST_LINUX
    OutputFormat = FormatElf32;
    AddOption(&CompilerOptions, &CompilerOptionsLen, "-seg32");
    DefineMacro("_LINUX");
    AddOption(&LinkerOptions, &LinkerOptionsLen, "-elf");
    LinkStdLib = 1;
#else
#ifdef HOST_WINDOWS
    OutputFormat = FormatWinPe32;
    AddOption(&CompilerOptions, &CompilerOptionsLen, "-seg32");
    AddOption(&CompilerOptions, &CompilerOptionsLen, "-winstack");
    DefineMacro("_WINDOWS");
    AddOption(&LinkerOptions, &LinkerOptionsLen, "-pe");
    LinkStdLib = 1;
#else
#ifdef HOST_DOS
    OutputFormat = FormatDosExeHuge;
    AddOption(&CompilerOptions, &CompilerOptionsLen, "-huge");
    DefineMacro("_DOS");
    AddOption(&LinkerOptions, &LinkerOptionsLen, "-huge");
    LinkStdLib = 1;
#endif
#endif
#endif
  }

  // Choose a default executable name if not specified explicitly
  if (!DontLink && !OutName)
  {
    switch (OutputFormat)
    {
    case FormatDosComTiny:
      OutName = "aout.com";
      break;
    case FormatDosExeSmall:
    case FormatDosExeHuge:
    case FormatWinPe32:
      OutName = "aout.exe";
      break;
    case FormatElf32:
      OutName = "a.out";
      break;
    case FormatFlat16:
    case FormatFlat32:
      OutName = "aout.bin";
      break;
    }
  }

  // Figure out if we need to create a library ('-c -o file.a' specified)
  if (DontLink && !CompileToAsm && OutName)
  {
    size_t len = strlen(OutName);
    if (len > 2 && OutName[len-2] == '.' &&
        (OutName[len-1] == 'a' || OutName[len-1] == 'A'))
      DoArchive = 1;
  }

  AddSystemPaths(argv[0]);

  // Pass to the external preprocessor what would otherwise be defined by smlrc
  if (UseExternalPreprocessor)
  {
    DefineMacro("__SMALLER_C__");
    switch (OutputFormat)
    {
    case FormatDosComTiny:
      DefineMacro("__SMALLER_C_16__");
      break;
    case FormatDosExeSmall:
      DefineMacro("__SMALLER_C_16__");
      break;
    case FormatDosExeHuge:
      DefineMacro("__SMALLER_C_32__");
      DefineMacro("__HUGE__");
      break;
    case FormatWinPe32:
      DefineMacro("__SMALLER_C_32__");
      break;
    case FormatElf32:
      DefineMacro("__SMALLER_C_32__");
      break;
    case FormatFlat16:
      DefineMacro("__SMALLER_C_16__");
      break;
    case FormatFlat32:
      DefineMacro("__SMALLER_C_32__");
      break;
    }
    if (UnsignedChar)
      DefineMacro("__SMALLER_C_UCHAR__");
    else
      DefineMacro("__SMALLER_C_SCHAR__");
    DefineMacro("__SMALLER_PP__");
  }

  for (i = 1; i < argc; i++)
    if (argv[i])
      Compile(argv[i]);

  if (!DontLink)
    Link();
  else if (DoArchive)
    Archive();

  return 0;
}
