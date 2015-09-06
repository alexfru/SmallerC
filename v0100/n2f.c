/*
  Copyright (c) 2015, Alexey Frunze
  2-clause BSD license.
*/
/*
  Wrapper around FASM to simulate NASM.

  How to use:
  - get FASM
  - compile this program and rename it to nasm.exe or nasm (as appropriate for
    your OS)
  - make both nasm[.exe] (this program) and fasm available via the PATH
    environment variable
  - use smlrcc as usual, it will invoke nasm[.exe] (this program), which will
    convert the input assembly file to the format compatible with FASM and
    invoke FASM on the conversion result

  Command line format for n2f (er, "nasm"):
    n2f <-f format> input.asm [-o output<.asm|.bin|.o>]
  Supported formats:
    asm  performs assembly conversion only
    bin  performs conversion and assembles with FASM (default, if format isn't
         specified)
    elf  same as bin, except inserts "format elf" at the beginning of the
         converted file (smlrcc invokes nasm with "-f elf")

  Limitations:
  - FASM doesn't support 16-bit relocations in the ELF object format, so this
    is only good for compiling 32-bit protected mode, namely DOS/DPMI32,
    Windows and Linux
  - Conversion may be slow (prefer compiling small C/asm files)
  - Conversion temporarily produces another assembly file, so you should have
    enough free space on the disk
  - The maximum number of section fragments and distinct sections, the maximum
    section name length (see the code)
  - tmpnam() is used to create the intermediate file with the converted
    assembly code, this may cause race conditions in multitasking OSes (see
    the code)
  - For speed, compatibility with DOSBox and ease of use prefer DPMI versions
    of this program and of Smaller C (DPMI version of smlrcc.exe will load
    CWSDPMI.EXE (DPMI host), which will be available to FASM, no need for
    unreal/bigreal/voodoo/whatever CPU mode tricks; DPMI is faster than huge
    memory model in real mode)

  How conversion works:
  - "format elf" is inserted at the beginning of the converted assembly file
    when invoked with the "-f elf" option (Smaller C works with ELF files)
  - fragmets of the same section are combined under the same section header
    (FASM puts fragments into separate sections, so without combining you end
    up with multiple .text (or .data or .bss or .rodata) sections in the ELF
    file, which isn't something Smaller C expects; NASM combines section
    fragments for us)
  - 'section .text' -> 'section ".text" executable'
  - 'section .rodata' -> 'section ".rodata"'
  - 'section .data' -> 'section ".data" writable'
  - 'section .bss' -> 'section ".bss" writable'
  - 'section .something_else' -> 'section ".something_else"'
  - 'bits 32/16' -> 'use32/use16'
  - 'alignb number' -> 'align number'
  - 'global symbol' -> 'public symbol'
  - 'resb/resw/resd number' -> 'rb/rw/rd number'
  - 'extern symbol' -> 'extrn symbol'

  How to compile for DOS:
    smlrcc -dosp n2f.c -o nasm.exe
   OR
    smlrcc -dosh n2f.c -o nasm.exe

  How to compile for Windows:
    smlrcc -win n2f.c -o nasm.exe

  How to compile for Linux:
    smlrcc -linux n2f.c -o nasm
*/

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FRAGS 3000
#define MAX_SECS  32
#define MAX_SEC_NAME_LEN 32

char* InName;
char* IntermidName;
char* OutName;
char* OutputFormat;
FILE *fin, *fout;
int DontAssemble;

void error(char* format, ...)
{
#ifndef __SMALLER_C__
  va_list vl;
  va_start(vl, format);
#else
  void* vl = &format + 1;
#endif

  if (fout)
    fclose(fout);
  if (fin)
    fclose(fin);
  if (OutName)
    remove(OutName);
  if (IntermidName)
    remove(IntermidName);

  puts("");

  vprintf(format, vl);

#ifndef __SMALLER_C__
  va_end(vl);
#endif

  exit(EXIT_FAILURE);
}

typedef struct
{
  long start;
  long end;
  unsigned sec;
  unsigned line;
} tFrag;

tFrag frag[MAX_FRAGS];
unsigned fragCnt;
long frag_1end; // end of the fragment before the first section fragment

char secName[MAX_SECS][MAX_SEC_NAME_LEN + 1];
unsigned secCnt;

unsigned line; // input file line number

unsigned addSection(char* name)
{
  unsigned i;
  if (secCnt >= MAX_SECS)
    error("Too many sections\n");
  for (i = 0; i < MAX_SECS; i++)
    if (!strcmp(secName[i], name))
      return i;
  strcpy(secName[secCnt], name);
  return secCnt++;
}

void beginFrag(long start, char* name, unsigned line)
{
  unsigned sec;
  if (fragCnt >= MAX_FRAGS)
    error("Too many section fragments\n");
  sec = addSection(name);
  frag[fragCnt].start = start;
  frag[fragCnt].sec = sec;
  frag[fragCnt++].line = line;
}

void endFrag(long end)
{
  if (fragCnt)
    frag[fragCnt - 1].end = end;
  else
    frag_1end = end;
}

int fragCmp(const void* p1_, const void* p2_)
{
  const tFrag *p1 = (const tFrag*)p1_, *p2 = (const tFrag*)p2_;
  if (p1->sec < p2->sec)
    return -1;
  if (p1->sec > p2->sec)
    return +1;
  if (p1->start < p2->start)
    return -1;
  if (p1->start > p2->start)
    return +1;
  return 0;
}

unsigned skipSpaces(FILE* f)
{
  unsigned cnt = 0;
  int c;
  while ((c = fgetc(f)) != EOF && (c == ' ' || c == '\t'))
    cnt += (c == '\t') ? 8 : 1; // ugly
  if (c != EOF)
    ungetc(c, f);
  return cnt;
}

void skipLine(FILE* f)
{
  int c;
  while ((c = fgetc(f)) != EOF && c != '\r' && c != '\n');
  if (c == '\r' && (c = fgetc(f)) != EOF && c != '\n')
    ungetc(c, f);
}

unsigned readNonspace(FILE* f, char buf[/*len + 1*/], unsigned len)
{
  unsigned cnt = 0;
  int c;
  while (cnt < len && (c = fgetc(f)) != EOF)
  {
    switch (c)
    {
    default:
      buf[cnt++] = c;
      continue;
    case ' ': case '\t': case '\r': case '\n':
      ungetc(c, f);
      // fallthrough
    }
    break;
  }
  buf[cnt] = '\0';

  return cnt;
}

void copyLine(FILE* fin, FILE* fout)
{
  int c;
  while ((c = fgetc(fin)) != EOF && c != '\r' && c != '\n')
    fputc(c, fout);
  if (c == '\r' && (c = fgetc(fin)) != EOF && c != '\n')
    ungetc(c, fin);
  fputc('\n', fout);
}

void findFrags(FILE* f)
{
  long end;

  line = 1;

  do
  {
    union
    {
      char ident[sizeof "section" + 1/*+1 in case it's longer, e.g. "sections"; space for NUL included in sizeof*/];
      char name[MAX_SEC_NAME_LEN + 1/*+1 in case it's longer*/ + 1/*NUL*/];
    } u;

    end = ftell(f);

    skipSpaces(f);
    readNonspace(f, u.ident, sizeof u.ident - 1);

    if (!strcmp(u.ident, "section"))
    {
      unsigned len;
      long start;

      skipSpaces(f);
      len = readNonspace(f, u.name, sizeof u.name - 1);
      if (len > MAX_SEC_NAME_LEN)
        error("Section name too long\n");
      if (len == 0)
        error("Section name missing\n");

      skipLine(f);
      start = ftell(f);
      endFrag(end);
      beginFrag(start, u.name, line + 1); // fragment actually begins on the next line
    }
    else
    {
      skipLine(f);
    }

    line++;
  } while (!feof(f) && !ferror(f)); // ferror(): prevent infinite loop if read/seek fails

  end = ftell(f);
  endFrag(end);

  qsort(frag, fragCnt, sizeof(frag[0]), &fragCmp);
}

void n2f1(FILE* fin, long start, long end, FILE* fout)
{
  fseek(fin, start, SEEK_SET);

  while (start >= 0 && start < end) // ensure start>=0: prevent infinite loop if ftell() fails
  {
    char ident[sizeof "extern"/*longest of directives being replaced*/ +
               1/*+1 in case it's longer, e.g. "externs"; space for NUL included in sizeof*/];
    unsigned spc;

    spc = skipSpaces(fin);

    readNonspace(fin, ident, sizeof ident - 1);

    if (*ident == ';')
    {
      // skip lines beginning with a comment
      skipLine(fin);
    }
    else
    {
      // emit leading tabs and/or spaces if there were any
      while (spc)
        if (spc >= 8)
          fputc('\t', fout), spc -= 8;
        else
          fputc(' ', fout), spc--;

      // replace NASM directives with FASM equivalents
      if (!strcmp(ident, "alignb"))
        fputs("align", fout);
      else if (!strcmp(ident, "global"))
        fputs("public", fout);
      else if (!strcmp(ident, "resb"))
        fputs("rb", fout);
      else if (!strcmp(ident, "resw"))
        fputs("rw", fout);
      else if (!strcmp(ident, "resd"))
        fputs("rd", fout);
      else if (!strcmp(ident, "extern"))
        fputs("extrn", fout);
      else if (!strcmp(ident, "bits"))
        fputs("use", fout), skipSpaces(fin);
      else
        fputs(ident, fout); // pass unknown things through

      // copy the rest of the line as-is
      copyLine(fin, fout);
    }

    line++;
    start = ftell(fin);
  }
}

void n2f(FILE* fin, FILE* fout)
{
  unsigned i, lastSec = secCnt, sec;

  if (!strcmp(OutputFormat, "elf"))
    fputs("format elf\n", fout);

  // fragment before the first section fragment
  line = 1;
  n2f1(fin, 0, frag_1end, fout);

  // combined section fragments
  for (i = 0; i < fragCnt; i++)
  {
    sec = frag[i].sec;
    line = frag[i].line;

    if (lastSec != sec)
    {
      char* attrs = "";
      lastSec = sec;
      // new section header
      if (!strcmp(secName[sec], ".text"))
        attrs = " executable";
      else if (!strcmp(secName[sec], ".data") || !strcmp(secName[sec], ".bss"))
        attrs = " writable";
      fprintf(fout, "section \"%s\"%s\n", secName[sec], attrs);
    }

    n2f1(fin, frag[i].start, frag[i].end, fout);
  }
}

void convert(void)
{
  char* out;

  if (DontAssemble)
  {
    // "-f asm"
    out = OutName;
  }
  else
  {
    // Not "-f asm", so we need an intermediate file
    if ((out = tmpnam(NULL)) == NULL) // TBD??? race condition possible
      error("Failed to generate temporary file name\n");
    IntermidName = out;
  }

  // TBD??? ensure file buffers of at least 4KB???

  if ((fin = fopen(InName, "rb")) == NULL)
    error("Can't open file '%s'\n", InName);

  if ((fout = fopen(out, "w")) == NULL)
    error("Can't create file '%s'\n", out);

  findFrags(fin);

  n2f(fin, fout);

  if (ferror(fin))
    error("Failed to read file '%s'\n", InName);

  if (ferror(fout))
    error("Failed to write file '%s'\n", out);

  fclose(fin);
  fin = NULL;
  fclose(fout);
  fout = NULL;
}

void fassemble(char* argv0)
{
  size_t argv0l = strlen(argv0);
  size_t cmdsz = strlen(IntermidName) + (OutName ? 1 + strlen(OutName) : 0) + 1/*NUL*/;
  char* pfasm;
  char* cmd;
  int res;

  // If this runs in DOS, prefer the full name fasm.exe, system() may execute it directly
  // without invoking COMMAND.COM, in which case abnormal fasm.exe termination can be caught
  // here ("COMMAND.COM /C command" typically terminates with status 0 even if the command
  // fails).
  if (argv0l > 4 &&
      argv0[argv0l-4] == '.' &&
      (argv0[argv0l-3] == 'E' || argv0[argv0l-3] == 'e') &&
      (argv0[argv0l-2] == 'X' || argv0[argv0l-2] == 'x') &&
      (argv0[argv0l-1] == 'E' || argv0[argv0l-1] == 'e'))
    pfasm = "fasm.exe";
  else
    pfasm = "fasm";

  cmdsz += strlen(pfasm) + 1;
  if ((cmd = malloc(cmdsz)) == NULL)
    error("Out of memory\n");

  strcpy(cmd, pfasm);
  strcat(cmd, " ");
  strcat(cmd, IntermidName);
  if (OutName)
  {
    strcat(cmd, " ");
    strcat(cmd, OutName);
  }

  res = system(cmd);

  if (res)
    error("Failed command '%s'\n", cmd);
}

int main(int argc, char** argv)
{
  int i, InputFileCnt = 0;

  for (i = 1; i < argc; i++)
  {
    if (!strcmp(argv[i], "-f"))
    {
      if (i + 1 < argc)
      {
        argv[i++] = NULL;
        OutputFormat = argv[i];
        argv[i] = NULL;
        if (strcmp(OutputFormat, "bin") && // convert and assemble
            strcmp(OutputFormat, "elf") && // convert, insert "format elf" and assemble
            strcmp(OutputFormat, "asm")) // just convert
          error("Invalid or unsupported output format '%s'\n", OutputFormat);
        DontAssemble = !strcmp(OutputFormat, "asm");
        continue;
      }
    }
    else if (!strcmp(argv[i], "-o"))
    {
      if (i + 1 < argc)
      {
        OutName = argv[++i];
        continue;
      }
    }

    if (argv[i][0] == '-')
      error("Invalid or unsupported command line option '%s'\n", argv[i]);

    InName = argv[i];
    InputFileCnt++;
  }

  if (InputFileCnt != 1)
    error("Too many or no inputs\n");

  if (!OutputFormat)
    OutputFormat = "bin";

  if (!OutName && DontAssemble)
    error("Output name required\n");

  convert();

  if (!DontAssemble)
  {
    fassemble(argv[0]);
    if (IntermidName)
      remove(IntermidName);
  }

  return 0;
}
