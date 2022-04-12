/*
Copyright (c) 2014-2021, Alexey Frunze
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
/*                             Smaller C linker                              */
/*                                                                           */
/*              A simple linker for Smaller C compiler and NASM              */
/*                                                                           */
/*            Consumes ELF32 x86 object files produced with NASM             */
/*                                                                           */
/*          Produces:                                                        */
/*          - 16/32-bit DOS executables                                      */
/*            (tiny model/.COM, small model/.EXE,                            */
/*             huge model/.EXE, unreal model/.EXE,                           */
/*             32-bit DPMI/.EXE)                                             */
/*          - 32-bit PE/Windows executables                                  */
/*          - 32-bit ELF/Linux executables                                   */
/*          - 32-bit Mach-O/Mac OS X executables                             */
/*          - 32-bit OMAGIC a.out executables                                */
/*          - 16/32-bit flat executables                                     */
/*                                                                           */
/*                                 Main file                                 */
/*                                                                           */
/*****************************************************************************/

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
#define SEEK_CUR 1
#define SEEK_END 2
#define CHAR_BIT 8
#define INT_MAX 0x7FFFFFFF
#define LONG_MAX 0x7FFFFFFF
typedef unsigned size_t;

char* strtok(char*, char*);
unsigned long strtoul(char*, char**, int);

void qsort(void*, size_t, size_t, int (*)(void*, void*));

#define EXIT_FAILURE 1

void exit(int);

size_t strlen(char*);
int strcmp(char*, char*);
int strncmp(char*, char*, size_t);
char* strncpy(char*, char*, size_t);
void* memmove(void*, void*, size_t);
void* memcpy(void*, void*, size_t);
void* memset(void*, int, size_t);
int memcmp(void*, void*, size_t);

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
long ftell(FILE*);
int remove(char*);

void* malloc(size_t);
void* realloc(void*, size_t);
void free(void*);
#endif

// By default don't support relocations with local symbols
// other than section symbols in DOS huge memory model.
// This is to conserve memory.
#ifndef SUPPORT_LOCAL_RELS

#ifdef __SMALLER_C__
#ifdef __HUGE__
#define SHOULDNT_SUPPORT_LOCAL_RELS
#endif
#endif

#ifndef SHOULDNT_SUPPORT_LOCAL_RELS
#define SUPPORT_LOCAL_RELS
#endif

#endif // SUPPORT_LOCAL_RELS

typedef unsigned char uchar, uint8;
typedef signed char schar, int8;
typedef unsigned short ushort, uint16;
typedef short int16;
#ifndef __SMALLER_C__
#if UINT_MAX >= 0xFFFFFFFF
typedef unsigned uint32;
typedef int int32;
#else
typedef unsigned long uint32;
typedef long int32;
#endif
#else
typedef unsigned uint32;
typedef int int32;
#endif
typedef unsigned uint;
typedef unsigned long ulong;

#ifndef __SMALLER_C_32__
#define C_ASSERT(expr) extern char CAssertExtern[(expr)?1:-1]
C_ASSERT(CHAR_BIT == 8);
C_ASSERT(sizeof(uint16) == 2);
C_ASSERT(sizeof(uint32) == 4);
C_ASSERT(sizeof(size_t) >= 4); // need a 32-bit compiler
#endif

typedef struct
{
  uint8  e_ident[16];
#define ELFCLASS32  1
#define ELFDATA2LSB 1
  uint16 e_type;
#define ET_REL      1
#define ET_EXEC     2
  uint16 e_machine;
#define EM_386      3
  uint32 e_version;
#define EV_CURRENT  1
  uint32 e_entry;
  uint32 e_phoff;
  uint32 e_shoff;
  uint32 e_flags;
  uint16 e_ehsize;
  uint16 e_phentsize;
  uint16 e_phnum;
  uint16 e_shentsize;
  uint16 e_shnum;
  uint16 e_shstrndx;
#define SHN_UNDEF     0
#define SHN_LORESERVE 0xFF00
#define SHN_COMMON    0xFFF2
} Elf32_Ehdr;

typedef struct
{
  uint32 sh_name;
  uint32 sh_type;
#define SHT_NULL     0
#define SHT_PROGBITS 1
#define SHT_SYMTAB   2
#define SHT_STRTAB   3
#define SHT_RELA     4
#define SHT_HASH     5
#define SHT_DYNAMIC  6
#define SHT_NOTE     7
#define SHT_NOBITS   8
#define SHT_REL      9
#define SHT_SHLIB    10
#define SHT_DYNSYM   11
  uint32 sh_flags;
#define SHF_WRITE     1
#define SHF_ALLOC     2
#define SHF_EXECINSTR 4
  uint32 sh_addr;
  uint32 sh_offset;
  uint32 sh_size;
  uint32 sh_link;
  uint32 sh_info;
  uint32 sh_addralign;
  uint32 sh_entsize;
} Elf32_Shd;

typedef struct
{
  uint32 st_name;
#define STN_UNDEF   0
  uint32 st_value;
  uint32 st_size;
  uint8  st_info;
#define STB_LOCAL   0
#define STB_GLOBAL  1
#define STB_WEAK    2
#define STT_NOTYPE  0
#define STT_OBJECT  1
#define STT_FUNC    2
#define STT_SECTION 3
#define STT_FILE    4
  uint8  st_other;
  uint16 st_shndx;
} Elf32_Sym;

typedef struct
{
  uint32 r_offset;
  uint32 r_info; // bits 0...7: relocation type, bits 8...31: index into the symbol table
                 // relocation section's sh_link is the section index of the symbol section to use
                 // relocation section's sh_info is the section index of the code/data section to make relocations in
                 // symbol section's sh_link is the section index of the string table section containing symbol names
                 // symbol section's sh_info is the number of all local symblols, others (global, weak, etc) follow local ones
                 //   it's a pity that symbols referring to whole sections can be local and thus I can't simply ignore all
                 //   local symbols
#define R_386_32   1
#define R_386_PC32 2
#define R_386_16   20
#define R_386_PC16 21
} Elf32_Rel;

typedef struct
{
  uint32 r_offset;
  uint32 r_info;
  uint32 r_addend;
} Elf32_Rela;

typedef struct
{
  uint32 p_type;
#define PT_NULL    0
#define PT_LOAD    1
#define PT_NOTE    4
#define PT_PHDR    6
  uint32 p_offset;
  uint32 p_vaddr;
  uint32 p_paddr;
  uint32 p_filesz;
  uint32 p_memsz;
  uint32 p_flags;
  uint32 p_align;
} Elf32_Phdr;

#ifndef __SMALLER_C__
C_ASSERT(sizeof(Elf32_Ehdr) == 52);
C_ASSERT(sizeof(Elf32_Shd) == 40);
C_ASSERT(sizeof(Elf32_Sym) == 16);
C_ASSERT(sizeof(Elf32_Rel) == 8);
C_ASSERT(sizeof(Elf32_Rela) == 12);
C_ASSERT(sizeof(Elf32_Phdr) == 32);
#endif

typedef struct
{
#define MACH_MAGIC_32                0xfeedface
  uint32 magic;
#define MACH_CPU_ARCH_ABI32          0x00000000
#define MACH_CPU_TYPE_I386           0x00000007
#define MACH_CPU_TYPE_X86            (MACH_CPU_ARCH_ABI32 | MACH_CPU_TYPE_I386)
  uint32 cputype;
#define MACH_CPU_SUBTYPE_I386_ALL    0x00000003
  uint32 cpusubtype;
#define MACH_EXECUTE                 0x2
  uint32 filetype;
  uint32 ncmds;
  uint32 sizeofcmds;
#define MACH_NOUNDEFS                0x1
  uint32 flags;
} Mach32_Header;

typedef struct
{
#define MACH_LC_SEGMENT       0x1
#define MACH_LC_SYMTAB        0x2
#define MACH_LC_THREAD        0x4
#define MACH_LC_UNIXTHREAD    0x5
  uint32 cmd;
  uint32 cmdsize;
} Mach32_LoadCmd;

typedef struct
{
  uint32 cmd;
  uint32 cmdsize;
  char segname[16];
  uint32 vmaddr;
  uint32 vmsize;
  uint32 fileoff;
  uint32 filesize;
#define MACH_VM_PROT_READ          0x1
#define MACH_VM_PROT_WRITE         0x2
#define MACH_VM_PROT_EXECUTE       0x4
  uint32 maxprot;
  uint32 initprot;
  uint32 nsects;
  uint32 flags;
} Mach32_SegmentCmd;

typedef struct
{
  char sectname[16];
  char segname[16];
  uint32 addr;
  uint32 size;
  uint32 offset;
  uint32 align;
  uint32 reloff;
  uint32 nreloc;
#define S_ATTR_PURE_INSTRUCTIONS 0x80000000
#define S_ATTR_SOME_INSTRUCTIONS 0x400
  uint32 flags;
  uint32 reserved1;
  uint32 reserved2;
} Mach32_Section;

typedef struct
{
  uint32  eax;
  uint32  ebx;
  uint32  ecx;
  uint32  edx;
  uint32  edi;
  uint32  esi;
  uint32  ebp;
  uint32  esp;
  uint32  ss;
  uint32  eflags;
  uint32  eip;
  uint32  cs;
  uint32  ds;
  uint32  es;
  uint32  fs;
  uint32  gs;
} Mach32_ThreadState;

typedef struct
{
  uint32  cmd;            /* MACH_LC_THREAD or MACH_LC_UNIXTHREAD */
  uint32  cmdsize;        /* total size of this command */
#define MACH_X86_THREAD_STATE 0x1
  uint32  flavor;         /* flavor of thread state */
  uint32  count;          /* count of longs in thread state */
  Mach32_ThreadState state;
} Mach32_ThreadCmd;

typedef struct
{
  uint32 cmd;
  uint32 cmdsize;
  uint32 symoff;
  uint32 nsyms;
  uint32 stroff;
  uint32 strsize;
} Mach32_SymtabCmd;

typedef struct
{
  uint32 n_strx;
#define MACH_N_EXT   0x1
#define MACH_N_ABS   0x2
#define MACH_N_SECT  0xe
  uint8 n_type;
  uint8 n_sect;
#define MACH_REFERENCE_FLAG_UNDEFINED_NON_LAZY 0x00
#define MACH_REFERENCED_DYNAMICALLY 0x10
  int16 n_desc;
  uint32 n_value;
} Mach32_Nlist;

typedef struct
{
  uint8  Signature[2];
  uint16 PartPage;
  uint16 PageCnt;
  uint16 ReloCnt;
  uint16 HdrSize;
  uint16 MinAlloc;
  uint16 MaxAlloc;
  uint16 InitSs;
  uint16 InitSp;
  uint16 ChkSum;
  uint16 InitIp;
  uint16 InitCs;
  uint16 ReloOff;
  uint16 OverlayNo;
  uint16 FirstRelo[2];
} tDosExeHeader;

#ifndef __SMALLER_C__
C_ASSERT(sizeof(tDosExeHeader) == 32);
#endif

typedef struct
{
  uint16 Machine;
  uint16 NumberOfSections;
  uint32 TimeDateStamp;
  uint32 PointerToSymbolTable;
  uint32 NumberOfSymbols;
  uint16 SizeOfOptionalHeader;
  uint16 Characteristics;
} tPeImageFileHeader;

typedef struct
{
  uint32 VirtualAddress;
  uint32 Size;
} tPeImageDataDirectory;

typedef struct
{
  uint16 Magic;
  uint8  MajorLinkerVersion;
  uint8  MinorLinkerVersion;
  uint32 SizeOfCode;
  uint32 SizeOfInitializedData;
  uint32 SizeOfUninitializedData;
  uint32 AddressOfEntryPoint;
  uint32 BaseOfCode;
  uint32 BaseOfData;
  uint32 ImageBase;
  uint32 SectionAlignment;
  uint32 FileAlignment;
  uint16 MajorOperatingSystemVersion;
  uint16 MinorOperatingSystemVersion;
  uint16 MajorImageVersion;
  uint16 MinorImageVersion;
  uint16 MajorSubsystemVersion;
  uint16 MinorSubsystemVersion;
  uint32 Win32VersionValue;
  uint32 SizeOfImage;
  uint32 SizeOfHeaders;
  uint32 CheckSum;
  uint16 Subsystem;
  uint16 DllCharacteristics;
  uint32 SizeOfStackReserve;
  uint32 SizeOfStackCommit;
  uint32 SizeOfHeapReserve;
  uint32 SizeOfHeapCommit;
  uint32 LoaderFlags;
  uint32 NumberOfRvaAndSizes;
  tPeImageDataDirectory DataDirectory[16];
} tPeImageOptionalHeader;

typedef struct
{
  uint8 Name[8];
  union
  {
    uint32 PhysicalAddress;
    uint32 VirtualSize;
  } Misc;
  uint32 VirtualAddress;
  uint32 SizeOfRawData;
  uint32 PointerToRawData;
  uint32 PointerToRelocations;
  uint32 PointerToLinenumbers;
  uint16 NumberOfRelocations;
  uint16 NumberOfLinenumbers;
  uint32 Characteristics;
} tPeImageSectionHeader;

typedef struct
{
  union
  {
    uint32 Characteristics;
    uint32 OrdinalFirstThunk;
  } u;
  uint32 TimeDateStamp;
  uint32 ForwarderChain;
  uint32 Name;
  uint32 FirstThunk;
} tPeImageImportDescriptor;

#ifndef __SMALLER_C__
C_ASSERT(sizeof(tPeImageFileHeader) == 20);
C_ASSERT(sizeof(tPeImageDataDirectory) == 8);
C_ASSERT(sizeof(tPeImageOptionalHeader) == 224);
C_ASSERT(sizeof(tPeImageSectionHeader) == 40);
C_ASSERT(sizeof(tPeImageImportDescriptor) == 20);
#endif

typedef struct
{
  uint32 magic; // machine ID and magic
#define OMAGIC 0x107
//#define NMAGIC 0x108
//#define ZMAGIC 0x10B
//#define QMAGIC 0x0CC
  uint32 text;
  uint32 data;
  uint32 bss;
  uint32 syms;
  uint32 entry;
  uint32 trsize;
  uint32 drsize;
} tAout;

typedef struct
{
  uint32 address;
  uint32 info; // bit field:
  //  0-23 symbolnum
#define N_UNDF 0
#define N_ABS  2
#define N_TEXT 4
#define N_DATA 6
#define N_BSS  8
  // 24-24 pcrel
  // 25-26 length: 0 for 8-bit relocations, 1 for 16-bit rel's, 2 for 32-bit rel's
  // 27-27 extern
  // 28-31 nothing
} tAoutRel;

#ifndef __SMALLER_C__
C_ASSERT(sizeof(tAout) == 32);
C_ASSERT(sizeof(tAoutRel) == 8);
#endif

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

#ifndef __SMALLER_C__
C_ASSERT(sizeof(tArchiveFileHeader) == 60);
#endif

typedef struct
{
  void** Buf;
  size_t Reserved;
  size_t Used;
} tDynArr;

typedef struct
{
  Elf32_Shd h;
  union
  {
    void* pData;
    char* pStr; // SHT_STRTAB
    Elf32_Sym* pSym; // SHT_SYMTAB
    Elf32_Rel* pRel; // SHT_REL
    Elf32_Rela* pRela; // SHT_RELA
  } d;

  uint32 OutOffset;
  uint32 OutFileOffset;
} tElfSection;

typedef struct
{
  const char* ElfName;
  uint32 ObjOffset;

  char* pSectNames;
  tElfSection* pSections;
  uint32 SectionCnt;

  int Needed;
} tElfMeta;

typedef struct
{
  const char* pName;
  int32 Attrs;
  uint32 Start;
  uint32 Stop;
} tSectDescr;

typedef struct
{
  const char* pName;
  uint32 SectIdx;
  int IsStop;
} tDeferredSym;

#define FBUF_SIZE 1024

const char* OutName = "a.out";

const char* MapName;

const char* EntryPoint = "__start";

const char* StubName;

#define FormatDosComTiny   1
#define FormatDosExeSmall  2
#define FormatDosExeHuge   3
#define FormatDosExeUnreal 4
#define FormatFlat16       5
#define FormatFlat32       6
#define FormatWinPe32      7
#define FormatElf32        8
#define FormatAout         9
#define FormatMach32       10
int OutputFormat = 0;
int UseBss = 1;
int NoRelocations = 0;

int verbose = 0;

uint32 Origin = 0xFFFFFFFF; // 0xFFFFFFFF means unspecified

uint32 StackSize = 0xFFFFFFFF; // 0xFFFFFFFF means unspecified

uint32 MinHeap = 0xFFFFFFFF; // 0xFFFFFFFF means unspecified
uint32 MaxHeap = 0xFFFFFFFF; // 0xFFFFFFFF means unspecified

tDynArr OpenFiles;

uint32 ObjFileCnt;
tElfMeta* pMetas;

tSectDescr* pSectDescrs;
uint32 SectCnt;

tDeferredSym* pDeferredSyms;
uint32 DeferredSymCnt;

// Size of the .relod section generated by the linker for FormatDosExeUnreal
uint32 UnrealRelodSize;

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
    exit(EXIT_FAILURE);
  }
}
#endif // DETERMINE_VA_LIST
#endif // __SMALLER_C__

size_t StrAnyOf(const char* s, const char* ss)
{
  size_t idx = 1, slen;
  if (!s || !*s || !ss)
    return 0;
  slen = strlen(s);
  for (;;)
  {
    size_t sslen = strlen(ss);
    if (sslen == 0)
      return 0;
    if (slen == sslen && !memcmp(s, ss, slen))
      return idx;
    ss += sslen + 1;
    idx++;
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

  // Make sure all files get closed if linking fails (DOS doesn't like leaked file handles)
  for (i = 0; i < OpenFiles.Reserved; i++)
    if (OpenFiles.Buf[i])
      fclose(OpenFiles.Buf[i]);

  remove(OutName);

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

  exit(EXIT_FAILURE);
}

void errInternal(int n)
{
  error("%d (internal)\n", n);
}

void errMem(void)
{
  error("Out of memory\n");
}

void errSectTooBig(void)
{
  error("Too much code (or data) or too big origin\n");
}

void errStackTooSmall(void)
{
  error("Too small stack\n");
}

void errStackTooBig(void)
{
  error("Too big stack or too much data (or code)\n");
}

void errArchive(void)
{
  error("Corrupted archive\n");
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

void FillWithByte(unsigned char byte, size_t size, FILE* stream)
{
  static unsigned char buf[FBUF_SIZE];
  memset(buf, byte, FBUF_SIZE);
  while (size)
  {
    size_t csz = size;
    if (csz > FBUF_SIZE)
      csz = FBUF_SIZE;
    Fwrite(buf, csz, stream);
    size -= csz;
  }
}

uint32 AlignTo(uint32 ofs, uint32 align)
{
  return (ofs + align - 1) / align * align;
}

int RelCmp(const void* p1_, const void* p2_)
{
  const Elf32_Rel *p1 = (const Elf32_Rel*)p1_, *p2 = (const Elf32_Rel*)p2_;
  if (p1->r_offset < p2->r_offset)
    return -1;
  if (p1->r_offset > p2->r_offset)
    return +1;
  return 0;
}

// TBD??? Thoroughly validate ELF object files, specifically sections
void loadElfObj(tElfMeta* pMeta, const char* ElfName, FILE* file, uint32 objOfs)
{
  Elf32_Ehdr elfHdr;
  Elf32_Shd sectHdr;
  uint32 sectIdx;
  int unsupported = 0;

  memset(pMeta, 0, sizeof *pMeta);

  pMeta->ElfName = ElfName;
  pMeta->ObjOffset = objOfs;

  if (verbose)
    printf("File %s:\n\n", ElfName);

  Fseek(file, objOfs, SEEK_SET);
  Fread(&elfHdr, sizeof elfHdr, file);

  if (memcmp(elfHdr.e_ident, "\x7F""ELF", 4))
    error("Not an ELF file\n");
  if (elfHdr.e_ident[6] != EV_CURRENT)
    error("Not a v1 ELF file\n");
  if (elfHdr.e_ehsize != sizeof elfHdr)
    error("Unexpected ELF header size\n");
  if (elfHdr.e_shentsize != sizeof sectHdr)
    error("Unexpected ELF section size\n");

  if (elfHdr.e_ident[4] != ELFCLASS32)
    error("Not a 32-bit file\n");
  if (elfHdr.e_ident[5] != ELFDATA2LSB)
    error("Not a little-endian file\n");

  if (elfHdr.e_type != ET_REL)
    error("Not a relocatable file\n");
  if (elfHdr.e_machine != EM_386)
    error("Not an x86 file\n");

  if (elfHdr.e_shoff == 0 || elfHdr.e_shstrndx == 0)
    error("Invalid file\n");
  Fseek(file, objOfs + elfHdr.e_shoff + elfHdr.e_shstrndx * sizeof sectHdr, SEEK_SET);
  Fread(&sectHdr, sizeof sectHdr, file);

  pMeta->pSectNames = Malloc(sectHdr.sh_size);

  Fseek(file, objOfs + sectHdr.sh_offset, SEEK_SET);
  Fread(pMeta->pSectNames, sectHdr.sh_size, file);

  pMeta->pSections = Malloc((elfHdr.e_shnum + 1) * sizeof(tElfSection));

  if (verbose)
    printf(" # Type     XAW   FileOffs Align       Size Link Info EnSz Name\n");
  for (sectIdx = 0; sectIdx < elfHdr.e_shnum; sectIdx++)
  {
    const char* typeName = "????????";
    static const char* const typeNames[] =
    {
      "NULL",
      "PROGBITS",
      "SYMTAB",
      "STRTAB",
      "RELA",
      "HASH",
      "DYNAMIC",
      "NOTE",
      "NOBITS",
      "REL",
      "SHLIB",
      "DYNSYM",
    };
    const char* name = "";

    Fseek(file, objOfs + elfHdr.e_shoff + sectIdx * sizeof sectHdr, SEEK_SET);
    Fread(&sectHdr, sizeof sectHdr, file);
    if (sectHdr.sh_type == SHT_NULL)
      memset(&sectHdr, 0, sizeof sectHdr);

    if (sectHdr.sh_name)
      name = pMeta->pSectNames + sectHdr.sh_name;

    unsupported |=
       sectHdr.sh_type != SHT_NULL &&
       sectHdr.sh_type != SHT_PROGBITS &&
       sectHdr.sh_type != SHT_SYMTAB &&
       sectHdr.sh_type != SHT_STRTAB &&
//       sectHdr.sh_type != SHT_RELA &&
//       sectHdr.sh_type != SHT_NOTE &&
       sectHdr.sh_type != SHT_NOBITS &&
       sectHdr.sh_type != SHT_REL;

    if (sectHdr.sh_type < sizeof typeNames / sizeof typeNames[0])
      typeName = typeNames[sectHdr.sh_type];

    if (verbose)
      printf("%2u %-8s %c%c%c 0x%08lX %5lu %10lu %4lu %4lu %4lu %s\n",
             sectIdx,
             typeName,
             "-X"[(sectHdr.sh_flags / SHF_EXECINSTR) & 1],
             "-A"[(sectHdr.sh_flags / SHF_ALLOC) & 1],
             "-W"[(sectHdr.sh_flags / SHF_WRITE) & 1],
             (ulong)sectHdr.sh_offset,
             (ulong)sectHdr.sh_addralign,
             (ulong)sectHdr.sh_size,
             (ulong)sectHdr.sh_link,
             (ulong)sectHdr.sh_info,
             (ulong)sectHdr.sh_entsize,
             name);

    memset(&pMeta->pSections[pMeta->SectionCnt], 0, sizeof pMeta->pSections[pMeta->SectionCnt]);
    pMeta->pSections[pMeta->SectionCnt++].h = sectHdr;
  }

  if (unsupported)
    error("Unsupported section\n");

  for (sectIdx = 1; sectIdx < pMeta->SectionCnt; sectIdx++)
  {
    tElfSection* pSect = &pMeta->pSections[sectIdx];

    switch (pSect->h.sh_type)
    {
    case SHT_SYMTAB:
      {
        uint32 cnt, sz, ofs;
#ifndef SUPPORT_LOCAL_RELS
        uint32 i;
#endif

        cnt = pSect->h.sh_size / sizeof(Elf32_Sym);
        if (!cnt ||
            cnt < pSect->h.sh_info ||
            pSect->h.sh_entsize != sizeof(Elf32_Sym))
          error("Incorrect number of symbols\n");
        pSect->h.sh_entsize = cnt; // repurpose sh_entsize for number of symbols

        // NOTE: can't skip all local symbols (they are the first sh_info symbols)
        // as there can be section symbols :(
        // pMeta->LocalSymsCnt = pSect->h.sh_info;

        sz = cnt * sizeof(Elf32_Sym); // TBD!!! overflow checks
        pSect->d.pSym = Malloc(sz);

        ofs = pSect->h.sh_offset;

        Fseek(file, objOfs + ofs, SEEK_SET);
        Fread(pSect->d.pSym, sz, file);

#ifndef SUPPORT_LOCAL_RELS
        // Collect all local section symbols and throw away other local symbols
        for (cnt = i = 0; i < pSect->h.sh_info; i++)
        {
          Elf32_Sym* pSym = &pSect->d.pSym[i];
          if ((pSym->st_info & 0xF) == STT_SECTION && pSym->st_shndx)
          {
            if (i > cnt)
              pSect->d.pSym[cnt] = *pSym;
            pSect->d.pSym[cnt++].st_value = i; // repurpose st_value for the original index of the section symbol, so it can still be found
          }
        }
        memmove(pSect->d.pSym + cnt, pSect->d.pSym + pSect->h.sh_info, (pSect->h.sh_entsize - pSect->h.sh_info) * sizeof(Elf32_Sym));
        pSect->h.sh_addralign = cnt; // repurpose sh_addralign for the number of the remaining local section symbols
        pSect->h.sh_entsize -= pSect->h.sh_info - cnt; // adjust total symbol count
        if (pSect->h.sh_entsize)
        {
          void* p;
          if ((p = realloc(pSect->d.pSym, pSect->h.sh_entsize * sizeof(Elf32_Sym))) != NULL) // shrink the buffer
            pSect->d.pSym = p;
        }
        else
        {
          free(pSect->d.pSym);
          pSect->d.pSym = NULL;
        }
#endif
      }
      break;

    case SHT_STRTAB:
      pSect->d.pStr = Malloc(pSect->h.sh_size);
      Fseek(file, objOfs + pSect->h.sh_offset, SEEK_SET);
      Fread(pSect->d.pStr, pSect->h.sh_size, file);
      break;

    case SHT_REL:
      if (!pSect->h.sh_size ||
          pSect->h.sh_entsize != sizeof(Elf32_Rel))
          error("Incorrect number of relocations\n");
      pSect->h.sh_entsize = pSect->h.sh_size / sizeof(Elf32_Rel); // repurpose sh_entsize for number of relocations

      pSect->d.pRel = Malloc(pSect->h.sh_size);
      Fseek(file, objOfs + pSect->h.sh_offset, SEEK_SET);
      Fread(pSect->d.pRel, pSect->h.sh_size, file);
      // Sort the relocations by offset, so relocation can be done while copying sections
      qsort(pSect->d.pRel, pSect->h.sh_entsize, sizeof(Elf32_Rel), &RelCmp);
      break;
    }
  } // endof for

  if (verbose)
  {
    puts("");

    puts("Symbols of sections and globals:");

    for (sectIdx = 1; sectIdx < pMeta->SectionCnt; sectIdx++)
    {
      tElfSection* pSect = &pMeta->pSections[sectIdx];

      if (pSect->h.sh_type == SHT_SYMTAB)
      {
        uint32 symIdx;
        for (symIdx = 0; symIdx < pSect->h.sh_entsize; symIdx++)
        {
          Elf32_Sym* pSym = &pSect->d.pSym[symIdx];
          const char* name = NULL;
          if (pSym->st_name)
            name = pMeta->pSections[pSect->h.sh_link].d.pStr + pSym->st_name;
          else if ((pSym->st_info & 0xF) == STT_SECTION && pSym->st_shndx)
            name = pMeta->pSectNames + pMeta->pSections[pSym->st_shndx].h.sh_name;

          if ((pSym->st_info & 0xF) == STT_SECTION)
          {
            printf("      section %s\n",
                   name);
          }
          else if ((pSym->st_info >> 4) == STB_GLOBAL && name)
          {
            printf("%s  global %s\n",
                   pSym->st_shndx ? "     " : "undef",
                   name);
          }
        }
      }
    }
    puts("");
  }
}

// TBD??? Thoroughly validate archive files
void loadMeta(const char* FileName)
{
  FILE* f = Fopen(FileName, "rb");
  char magic[8];
  uint32 ofs = sizeof magic;

  Fread(magic, sizeof magic, f);

  if (!memcmp(magic, "!<arch>\n", sizeof magic))
  {
    for (;;)
    {
      tArchiveFileHeader fh;
      uint32 nlen = 0, fsz = 0, fofs;
      uint i;

      Fseek(f, ofs, SEEK_SET);
      if (fread(&fh, 1, sizeof fh, f) != sizeof fh)
        break;
      if (fh.fmag[0] != 0x60 || fh.fmag[1] != 0x0A)
        errArchive();

      // Special names:
      //
      // - "//              " entry is a string table, containing long file names (GNU)
      // - "/               " entry is a symbol lookup table (GNU)
      // - "/nnn            ", where n's are decimal digits, entry is a file entry with a long name (GNU style)
      //   nnn is an index into the string table
      //
      // - "__.SYMDEF       " entry is a symbol lookup table (BSD)
      // - "#1/nnn          ", where n's are decimal digits, entry is a file entry with a long name (BSD style)
      //   nnn is the length of the long name (prepended to file data; file size includes this length)
      //
      // - otherwise it's a regular file with a short name

      if (!memcmp(fh.name, "#1/", 3))
      {
        for (i = 3; i < sizeof fh.name; i++)
        {
          if (fh.name[i] >= '0' && fh.name[i] <= '9')
            nlen = nlen * 10 + fh.name[i] - '0';
          else
            break;
        }
      }

      for (i = 0; i < sizeof fh.size; i++)
      {
        if (fh.size[i] >= '0' && fh.size[i] <= '9')
          fsz = fsz * 10 + fh.size[i] - '0';
        else
          break;
      }

      if (nlen > fsz)
        errArchive();

      fofs = ofs + sizeof fh + nlen;
      fsz -= nlen;

      // TBD??? load and use symbol lookup tables

      if (memcmp(fh.name, "//              ", sizeof fh.name) &&
          memcmp(fh.name, "/               ", sizeof fh.name) &&
          memcmp(fh.name, "__.SYMDEF       ", sizeof fh.name))
      {
        if (fsz < sizeof(Elf32_Ehdr))
          errArchive();
        pMetas = Realloc(pMetas, (sizeof *pMetas) * (ObjFileCnt + 1));
        // TBD!!! extract object file name and pass it instead of the library file name
        loadElfObj(pMetas + ObjFileCnt, FileName, f, fofs);
        ObjFileCnt++;
      }

      ofs = fofs + fsz;
      ofs += ofs & 1;
    }
  }
  else
  {
    pMetas = Realloc(pMetas, (sizeof *pMetas) * (ObjFileCnt + 1));
    loadElfObj(pMetas + ObjFileCnt, FileName, f, 0);
    ObjFileCnt++;
  }

  Fclose(f);
}

void DeferSymbol(const char* SymName)
{
  uint32 i;
  for (i = 0; i < DeferredSymCnt; i++)
    if (!strcmp(pDeferredSyms[i].pName, SymName))
      return;
  pDeferredSyms = Realloc(pDeferredSyms, (sizeof *pDeferredSyms) * (DeferredSymCnt + 1));
  pDeferredSyms[DeferredSymCnt].pName = SymName;
  pDeferredSyms[DeferredSymCnt++].SectIdx = 0xFFFFFFFF;
}

int FindSymbolByName(const char* SymName)
{
  uint32 cnt = 0, fIdx, sectIdx, symIdx;
  int includedObj = 0;
  for (fIdx = 0; fIdx < ObjFileCnt; fIdx++)
  {
    tElfMeta* pMeta = &pMetas[fIdx];
    for (sectIdx = 0; sectIdx < pMeta->SectionCnt; sectIdx++)
    {
      tElfSection* pSect = &pMeta->pSections[sectIdx];
      if (pSect->h.sh_type != SHT_SYMTAB)
        continue;

#ifdef SUPPORT_LOCAL_RELS
      for (symIdx = pSect->h.sh_info; symIdx < pSect->h.sh_entsize; symIdx++)
#else
      for (symIdx = pSect->h.sh_addralign; symIdx < pSect->h.sh_entsize; symIdx++)
#endif
      {
        Elf32_Sym* pSym = &pSect->d.pSym[symIdx];

        // Check exported symbols
        if ((pSym->st_info >> 4) == STB_GLOBAL &&
            pSym->st_shndx &&
            pSym->st_name &&
            !strcmp(pMeta->pSections[pSect->h.sh_link].d.pStr + pSym->st_name, SymName))
        {
          cnt++;
          if (!pMeta->Needed)
          {
            includedObj = 1;
            pMeta->Needed = 1;
          }
          break;
        }
      }
      if (cnt)
        break;
    }
    if (cnt)
      break;
  }
  if (!cnt)
  {
    // Don't error out on symbols of:
    // - section start, e.g. __start__text (for .text)
    // - section end, e.g. __stop__text (for .text)
    // - stack start, e.g. __start_stack__
    // which aren't defined yet
    if (StrAnyOf(SymName, "__start_allcode__\0"
                          "__stop_allcode__\0"
                          "__start_alldata__\0"
                          "__stop_alldata__\0") ||
        (!strncmp(SymName, "__start_", sizeof "__start_" - 1) && SymName[sizeof "__start_" - 1] != '\0') ||
        (!strncmp(SymName, "__stop_", sizeof "__stop_" - 1) && SymName[sizeof "__stop_" - 1] != '\0'))
      DeferSymbol(SymName);
    else
      error("Symbol '%s' not found\n", SymName);
  }
  return includedObj;
}

void CheckDuplicates(void)
{
  uint32 fIdx, sectIdx, symIdx;
  for (fIdx = 0; fIdx < ObjFileCnt; fIdx++)
  {
    tElfMeta* pMeta = &pMetas[fIdx];
    if (!pMeta->Needed)
      continue;
    for (sectIdx = 0; sectIdx < pMeta->SectionCnt; sectIdx++)
    {
      tElfSection* pSect = &pMeta->pSections[sectIdx];
      if (pSect->h.sh_type != SHT_SYMTAB)
        continue;

#ifdef SUPPORT_LOCAL_RELS
      for (symIdx = pSect->h.sh_info; symIdx < pSect->h.sh_entsize; symIdx++)
#else
      for (symIdx = pSect->h.sh_addralign; symIdx < pSect->h.sh_entsize; symIdx++)
#endif
      {
        Elf32_Sym* pSym = &pSect->d.pSym[symIdx];

        // Check exported symbols
        if ((pSym->st_info >> 4) == STB_GLOBAL &&
            pSym->st_shndx &&
            pSym->st_name)
        {
          uint32 fIdx2, sectIdx2, symIdx2;
          for (fIdx2 = fIdx + 1; fIdx2 < ObjFileCnt; fIdx2++)
          {
            tElfMeta* pMeta2 = &pMetas[fIdx2];
            if (!pMeta2->Needed)
              continue;
            for (sectIdx2 = 0; sectIdx2 < pMeta2->SectionCnt; sectIdx2++)
            {
              tElfSection* pSect2 = &pMeta2->pSections[sectIdx2];
              if (pSect2->h.sh_type != SHT_SYMTAB)
                continue;

#ifdef SUPPORT_LOCAL_RELS
              for (symIdx2 = pSect2->h.sh_info; symIdx2 < pSect2->h.sh_entsize; symIdx2++)
#else
              for (symIdx2 = pSect2->h.sh_addralign; symIdx2 < pSect2->h.sh_entsize; symIdx2++)
#endif
              {
                Elf32_Sym* pSym2 = &pSect2->d.pSym[symIdx2];

                // Check exported symbols
                if ((pSym2->st_info >> 4) == STB_GLOBAL &&
                    pSym2->st_shndx &&
                    pSym2->st_name)
                {
                  if (!strcmp(pMeta->pSections[pSect->h.sh_link].d.pStr + pSym->st_name,
                              pMeta2->pSections[pSect2->h.sh_link].d.pStr + pSym2->st_name))
                    error("Symbol '%s' defined multiple times\n",
                          pMeta->pSections[pSect->h.sh_link].d.pStr + pSym->st_name);
                }
              }
            }
          }
        }
      }
    }
  }
}

void FindAllSymbols(void)
{
  uint32 fIdx, sectIdx, symIdx;
  int includedObj;
  do
  {
    includedObj = 0;

    for (fIdx = 0; fIdx < ObjFileCnt; fIdx++)
    {
      tElfMeta* pMeta = &pMetas[fIdx];
      if (!pMeta->Needed)
        continue;

      for (sectIdx = 0; sectIdx < pMeta->SectionCnt; sectIdx++)
      {
        tElfSection* pSect = &pMeta->pSections[sectIdx];
        if (pSect->h.sh_type != SHT_SYMTAB)
          continue;

#ifdef SUPPORT_LOCAL_RELS
        for (symIdx = pSect->h.sh_info; symIdx < pSect->h.sh_entsize; symIdx++)
#else
        for (symIdx = pSect->h.sh_addralign; symIdx < pSect->h.sh_entsize; symIdx++)
#endif
        {
          Elf32_Sym* pSym = &pSect->d.pSym[symIdx];

          // Check imported symbols
          if ((pSym->st_info >> 4) == STB_GLOBAL &&
              !pSym->st_shndx &&
              pSym->st_name)
          {
            includedObj |= FindSymbolByName(pMeta->pSections[pSect->h.sh_link].d.pStr + pSym->st_name);
          }
        }
      }
    }
  } while (includedObj);
}

int SectDescCmp(const void* p1_, const void* p2_)
{
  const tSectDescr *p1 = (const tSectDescr*)p1_, *p2 = (const tSectDescr*)p2_;
  int i;

  // SHT_NOBITS (e.g. .bss) goes after SHT_PROGBITS (e.g. .text, .rodata, .data)
  if ((p1->Attrs ^ p2->Attrs) & SHT_NOBITS)
    return +((p1->Attrs & SHT_NOBITS) - (p2->Attrs & SHT_NOBITS));

  // code (e.g. .text) goes before data (e.g. .rodata, .data)
  if ((p1->Attrs ^ p2->Attrs) & SHF_EXECINSTR)
    return -((p1->Attrs & SHF_EXECINSTR) - (p2->Attrs & SHF_EXECINSTR));

  // writable data (e.g. .data) goes after read-only data (e.g. .rodata)
  if ((p1->Attrs ^ p2->Attrs) & SHF_WRITE)
    return +((p1->Attrs & SHF_WRITE) - (p2->Attrs & SHF_WRITE));

  // If attributes are equal, order sections by name,
  // but make .text appear before all other code sections (if any)
  i = strcmp(p1->pName, p2->pName);
  if (i && (p1->Attrs & SHF_EXECINSTR))
  {
    if (!strcmp(p1->pName, ".text"))
      return -1;
    if (!strcmp(p2->pName, ".text"))
      return +1;
  }
  // but make .dll_* appear before all other writable data sections (if any)
  if (i && (p1->Attrs & SHF_WRITE))
  {
    int i1 = !strncmp(p1->pName, ".dll_", sizeof ".dll_" - 1);
    int i2 = !strncmp(p2->pName, ".dll_", sizeof ".dll_" - 1);
    if (i1 != i2)
      return i2 - i1;
  }
  return i;
}

void FindAllSections(void)
{
  uint32 fIdx, sectIdx, i;
  for (fIdx = 0; fIdx < ObjFileCnt; fIdx++)
  {
    tElfMeta* pMeta = &pMetas[fIdx];
    if (!pMeta->Needed)
    {
      // TBD??? free the memory used by the unused files.
      continue;
    }

    for (sectIdx = 0; sectIdx < pMeta->SectionCnt; sectIdx++)
    {
      tElfSection* pSect = &pMeta->pSections[sectIdx];
      char* sname = pMeta->pSectNames + pSect->h.sh_name;
      int found = 0;
      if (!(pSect->h.sh_flags & SHF_ALLOC))
      {
        if (OutputFormat == FormatDosExeUnreal &&
            pSect->h.sh_type == SHT_REL)
        {
          // Calculate the size of the new .relod section (count only 32-bit non-PC-relative relocations).
          uint32 relIdx;
          for (relIdx = 0; relIdx < pSect->h.sh_entsize; relIdx++)
          {
            Elf32_Rel* pRel = &pSect->d.pRel[relIdx];
            uint32 symIdx = pRel->r_info >> 8;
            uint32 absSym = symIdx == 0;
            uint32 relType = pRel->r_info & 0xFFu;
            // TBD??? additional error checks
            if (!absSym && relType == R_386_32)
              UnrealRelodSize += 4;
          }
        }
        continue;
      }

      for (i = 0; i < SectCnt; i++)
      {
        if (!strcmp(pSectDescrs[i].pName, sname))
        {
          uint32 oldAttrs = pSectDescrs[i].Attrs;
          uint32 newAttrs = (pSect->h.sh_flags & (SHF_WRITE | SHF_EXECINSTR)) | (pSect->h.sh_type & SHT_NOBITS);
          if ((oldAttrs ^ newAttrs) & (SHF_WRITE | SHF_EXECINSTR | SHT_NOBITS))
            error("Inconsistent section type/flags\n");
          found = 1;
          break;
        }
      }

      if (!found)
      {
        if (OutputFormat == FormatDosExeUnreal && !strcmp(sname, ".relod"))
          error("Unexpected section .relod for unreal format\n");
        pSectDescrs = Realloc(pSectDescrs, (sizeof *pSectDescrs) * (SectCnt + 1));
        memset(&pSectDescrs[SectCnt], 0, sizeof pSectDescrs[SectCnt]);
        pSectDescrs[SectCnt].Attrs = (pSect->h.sh_flags & (SHF_WRITE | SHF_EXECINSTR)) | (pSect->h.sh_type & SHT_NOBITS);
        pSectDescrs[SectCnt++].pName = sname;
      }
    }
  }

  if (UnrealRelodSize)
  {
    pSectDescrs = Realloc(pSectDescrs, (sizeof *pSectDescrs) * (SectCnt + 1));
    memset(&pSectDescrs[SectCnt], 0, sizeof pSectDescrs[SectCnt]);
    pSectDescrs[SectCnt].Attrs = 0;
    pSectDescrs[SectCnt++].pName = ".relod";
  }

  // Sort sections by attributes/names
  qsort(pSectDescrs, SectCnt, sizeof *pSectDescrs, &SectDescCmp);

  if (verbose)
  {
    printf("Sections used:\n");
    for (i = 0; i < SectCnt; i++)
      printf("  %s\n", pSectDescrs[i].pName);
    puts("");
  }

  if (!(pSectDescrs[0].Attrs & SHF_EXECINSTR))
    error("Executable section not found\n");

  for (i = 0; i < SectCnt; i++)
    if ((pSectDescrs[i].Attrs & SHF_EXECINSTR) &&
        (pSectDescrs[i].Attrs & (SHT_NOBITS | SHF_WRITE)))
      error("Inconsistent section type/flags\n");

  // Add 3 hidden pseudo sections:
  // - one for all code sections combined
  // - one for all data sections combined
  // - one for the stack start symbol (only for tiny/.COM and small/.EXE)
  pSectDescrs = Realloc(pSectDescrs, (sizeof *pSectDescrs) * (SectCnt + 3));
  memset(&pSectDescrs[SectCnt], 0, 3 * sizeof pSectDescrs[SectCnt]);
  pSectDescrs[SectCnt + 0].pName = "allcode__";
  pSectDescrs[SectCnt + 1].pName = (pSectDescrs[SectCnt - 1].Attrs & SHF_EXECINSTR) ? "" : "alldata__";
  pSectDescrs[SectCnt + 2].pName = (OutputFormat == FormatDosComTiny || OutputFormat == FormatDosExeSmall) ? "stack__" : "";

  // Link deferred symbols to sections
  for (i = 0; i < DeferredSymCnt; i++)
  {
    const char* p1 = pDeferredSyms[i].pName;
    int isStop = strncmp(p1, "__start_", sizeof "__start_" - 1) != 0;
    size_t pfxLen = isStop ? sizeof "__stop_" - 1 : sizeof "__start_" - 1;
    size_t len = strlen(p1 + pfxLen);
    int found = 0;

    p1 += pfxLen;

    for (sectIdx = 0; sectIdx < SectCnt + 3; sectIdx++)
    {
      const char* p2 = pSectDescrs[sectIdx].pName;
      if (len == strlen(p2))
      {
        size_t i;
        found = 1;
        for (i = 0; i < len; i++)
          if (p1[i] != p2[i] && !(p1[i] == '_' && p2[i] == '.')) // e.g. "__start__text" and "__stop__text" match ".text" section
          {
            found = 0;
            break;
          }
        if (found)
          break;
      }
    }

    if (found)
    {
      pDeferredSyms[i].SectIdx = sectIdx;
      pDeferredSyms[i].IsStop = isStop;
    }
    else
      error("Symbol '%s' not found\n", pDeferredSyms[i].pName);
  }
}

uint32 FindSymbolAddress(const char* SymName)
{
  uint32 fIdx, sectIdx, symIdx;
  uint32 addr = 0;

  // First, check for section start/stop symbols
  for (symIdx = 0; symIdx < DeferredSymCnt; symIdx++)
  {
    if (!strcmp(pDeferredSyms[symIdx].pName, SymName))
      return pDeferredSyms[symIdx].IsStop ?
        pSectDescrs[pDeferredSyms[symIdx].SectIdx].Stop :
        pSectDescrs[pDeferredSyms[symIdx].SectIdx].Start;
  }

  // Do all other symbols
  for (fIdx = 0; fIdx < ObjFileCnt; fIdx++)
  {
    tElfMeta* pMeta = &pMetas[fIdx];
    if (!pMeta->Needed)
      continue;
    for (sectIdx = 0; sectIdx < pMeta->SectionCnt; sectIdx++)
    {
      tElfSection* pSect = &pMeta->pSections[sectIdx];
      if (pSect->h.sh_type != SHT_SYMTAB)
        continue;

#ifdef SUPPORT_LOCAL_RELS
      for (symIdx = pSect->h.sh_info; symIdx < pSect->h.sh_entsize; symIdx++)
#else
      for (symIdx = pSect->h.sh_addralign; symIdx < pSect->h.sh_entsize; symIdx++)
#endif
      {
        Elf32_Sym* pSym = &pSect->d.pSym[symIdx];

        // Check exported symbols
        if ((pSym->st_info >> 4) == STB_GLOBAL &&
            pSym->st_shndx &&
            pSym->st_name &&
            !strcmp(pMeta->pSections[pSect->h.sh_link].d.pStr + pSym->st_name, SymName))
        {
          tElfSection* pSect;
          if (pSym->st_shndx == SHN_COMMON)
            error("Common symbols unsupported\n");
          pSect = &pMeta->pSections[pSym->st_shndx];
          addr = pSect->OutOffset + pSym->st_value;
          return addr;
        }
      }
    }
  }
  // TBD??? error???
  return addr;
}

void Relocate(tElfMeta* pMeta, tElfSection* pRelSect, Elf32_Rel* pRel, unsigned char* buf, uint32 off, uint32 fileOff)
{
  uint32 symIdx = pRel->r_info >> 8;
  uint32 relType = pRel->r_info & 0xFFu;
  tElfSection* pSymSect = &pMeta->pSections[pRelSect->h.sh_link];
  Elf32_Sym* pSym = NULL;
  const char* name = NULL;
  uint32 symAddr = 0;

  if (symIdx == 0)
  {
    // it's an absolute symbol
  }
  else
  {
#ifdef SUPPORT_LOCAL_RELS
    pSym = &pSymSect->d.pSym[symIdx];
#else
    if (symIdx >= pSymSect->h.sh_info)
    {
      // it's a global symbol
      pSym = &pSymSect->d.pSym[symIdx - pSymSect->h.sh_info + pSymSect->h.sh_addralign];
    }
    else
    {
      // it must be a local symbol for a section
      uint32 i;
      for (i = 0; i < pSymSect->h.sh_addralign; i++)
        if (pSymSect->d.pSym[i].st_value == symIdx)
        {
          pSym = &pSymSect->d.pSym[i];
          break;
        }
      if (!pSym)
        goto err;
    }
#endif

    if (pSym->st_name)
      name = pMeta->pSections[pSymSect->h.sh_link].d.pStr + pSym->st_name;
    else if ((pSym->st_info & 0xF) == STT_SECTION && pSym->st_shndx)
      name = pMeta->pSectNames + pMeta->pSections[pSym->st_shndx].h.sh_name;

    if ((pSym->st_info & 0xF) == STT_SECTION)
    {
      symAddr = pMeta->pSections[pSym->st_shndx].OutOffset;
    }
    else if ((pSym->st_info >> 4) == STB_GLOBAL && name)
    {
      symAddr = FindSymbolAddress(name);
    }
#ifdef SUPPORT_LOCAL_RELS
    else if ((pSym->st_info >> 4) == STB_LOCAL)
    {
      symAddr = pMeta->pSections[pSym->st_shndx].OutOffset + pSym->st_value;
    }
#endif
    else
#ifndef SUPPORT_LOCAL_RELS
      err:
#endif
      error("Unsupported relocation symbol type\n");
  }

  if (verbose)
    printf("%08lX  %3lu  %08lX  %s\n", (ulong)fileOff, (ulong)relType, (ulong)symAddr, name ? name : "*ABS*");

  if (relType == R_386_32 || relType == R_386_PC32)
  {
    uint32 dd = buf[0] + ((uint32)buf[1] << 8) + ((uint32)buf[2] << 16) + ((uint32)buf[3] << 24);
    dd += symAddr;
    if (relType == R_386_PC32)
      dd -= off;
    buf[0] = dd; buf[1] = (dd >>= 8); buf[2] = (dd >>= 8); buf[3] = (dd >>= 8);
  }
  else if (relType == R_386_16 || relType == R_386_PC16)
  {
    uint32 dd = buf[0] + ((uint)buf[1] << 8);
    dd += symAddr;
    if (relType == R_386_PC16)
      dd -= off;
    buf[0] = dd; buf[1] = (dd >>= 8);
  }
  else
    error("Unsupported relocation type\n");
}

void RelocateAndWriteSection(FILE* outStream, FILE* inStream, size_t size, tElfMeta* pMeta, tElfSection* pRelSect)
{
  static unsigned char buf[FBUF_SIZE + sizeof(uint32) - 1];
  size_t sz = 0; // how many bytes are in buf[]
  uint32 ofs = 0; // offset within the section corresponding to &buf[0]
  uint32 relIdx = 0;
  int first = 1;
  if (size)
  {
    size_t csz = sizeof(uint32) - 1;
    if (csz > size)
      csz = size;
    Fread(buf, csz, inStream);
    size -= csz;
    sz = csz;
  }
  while (sz)
  {
    size_t csz = size;
    if (csz > FBUF_SIZE)
      csz = FBUF_SIZE;
    if (csz)
    {
      Fread(buf + sz, csz, inStream);
      size -= csz;
      sz += csz;
    }
    if (pRelSect)
    {
      while (relIdx < pRelSect->h.sh_entsize &&
             pRelSect->d.pRel[relIdx].r_offset < ofs + FBUF_SIZE)
      {
        Elf32_Rel* pRel = &pRelSect->d.pRel[relIdx];
        if (verbose && first)
        {
          printf("File Ofs Type  Sym Addr  Sym\n");
          first = 0;
        }
        Relocate(pMeta,
                 pRelSect,
                 pRel,
                 buf + pRel->r_offset - ofs,
                 pRel->r_offset + pMeta->pSections[pRelSect->h.sh_info].OutOffset,
                 pRel->r_offset + pMeta->pSections[pRelSect->h.sh_info].OutFileOffset);
        relIdx++;
      }
    }
    csz = sz;
    if (csz > FBUF_SIZE)
      csz = FBUF_SIZE;
    Fwrite(buf, csz, outStream);
    sz -= csz;
    memcpy(buf, buf + FBUF_SIZE, sz);
    ofs += FBUF_SIZE;
  }
}

tDosExeHeader DosExeHeader =
{
  { "MZ" }, // Signature
  0,        // PartPage
  0,        // PageCnt
  0,        // ReloCnt
  2,        // HdrSize
  0,        // MinAlloc
  0,        // MaxAlloc
  0,        // InitSs
  0xFFFC,   // InitSp
  0,        // ChkSum
  0,        // InitIp
  0,        // InitCs
  28,       // ReloOff
  0,        // OverlayNo
  { 0, 0 }  // FirstRelo
};

uint8 DosMzExeStub[128] =
{
  0x4D, 0x5A, 0x80, 0x00, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x10, 0x00, 0x10, 0x04, 0x00,
  0xFC, 0xFF, 0x00, 0x00, 0x40, 0x00, 0xFC, 0xFF, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00,
  0x0E, 0x1F, 0xBA, 0x4E, 0x00, 0xB4, 0x09, 0xCD, 0x21, 0xB8, 0x01, 0x4C, 0xCD, 0x21, 0x54, 0x68,
  0x69, 0x73, 0x20, 0x70, 0x72, 0x6F, 0x67, 0x72, 0x61, 0x6D, 0x20, 0x63, 0x61, 0x6E, 0x6E, 0x6F,
  0x74, 0x20, 0x62, 0x65, 0x20, 0x72, 0x75, 0x6E, 0x20, 0x69, 0x6E, 0x20, 0x44, 0x4F, 0x53, 0x20,
  0x6D, 0x6F, 0x64, 0x65, 0x2E, 0x0D, 0x0D, 0x0A, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

tPeImageFileHeader PeFileHeader =
{
  0x014C,                         // Machine (Intel 80386)
  1,                              // NumberOfSections
  0x52C3CB00,                     // TimeDateStamp
  0,                              // PointerToSymbolTable
  0,                              // NumberOfSymbols
  sizeof(tPeImageOptionalHeader), // SizeOfOptionalHeader
  0x30F                           // Characteristics (no symbol/debug info, no relocations, executable, 32-bit)
};

tPeImageOptionalHeader PeOptionalHeader =
{
  0x10B,    // Magic (PE32)
  8,        // MajorLinkerVersion
  0,        // MinorLinkerVersion
  0,        // SizeOfCode
  0,        // SizeOfInitializedData
  0,        // SizeOfUninitializedData
  0,        // AddressOfEntryPoint
  0,        // BaseOfCode
  0,        // BaseOfData
  0,        // ImageBase
  4096,     // SectionAlignment
  512,      // FileAlignment
  4,        // MajorOperatingSystemVersion
  0,        // MinorOperatingSystemVersion
  0,        // MajorImageVersion
  0,        // MinorImageVersion
  4,        // MajorSubsystemVersion
  0,        // MinorSubsystemVersion
  0,        // Win32VersionValue
  0,        // SizeOfImage
  4096,     // SizeOfHeaders
  0,        // CheckSum
  3,        // Subsystem (Windows CUI)
  0,        // DllCharacteristics
  0x100000, // SizeOfStackReserve
  0x10000,  // SizeOfStackCommit
  0x4000000,// SizeOfHeapReserve
  0,        // SizeOfHeapCommit
  0,        // LoaderFlags
  16,       // NumberOfRvaAndSizes
  // Data directories
  {
    { 0, 0 }, // Export Table
    { 0, 0 }, // Import Table
    { 0, 0 }, // Resource Table
    { 0, 0 }, // Exception Table
    { 0, 0 }, // Security Table
    { 0, 0 }, // Relocation Table
    { 0, 0 }, // Debug Info
    { 0, 0 }, // Description
    { 0, 0 }, // Machine-specific
    { 0, 0 }, // TLS
    { 0, 0 }, // Load Configuration
    { 0, 0 }, // Bound Import Table
    { 0, 0 }, // Import Address Table
    { 0, 0 }, // Delay Import Table
    { 0, 0 }, // COM+
    { 0, 0 }  // Reserved
  }
};

tPeImageSectionHeader PeSectionHeaderZero;

tPeImageSectionHeader PeSectionHeaderText =
{
  { ".text" }, // Name
  { 0 },       // VirtualSize
  0,           // VirtualAddress
  0,           // SizeOfRawData
  0,           // PointerToRawData
  0,           // PointerToRelocations
  0,           // PointerToLinenumbers
  0,           // NumberOfRelocations
  0,           // NumberOfLinenumbers
  0x60000020   // Characteristics (code, executable, readable)
};

tPeImageSectionHeader PeSectionHeaderRoData =
{
  { ".rdata" }, // Name
  { 0 },       // VirtualSize
  0,           // VirtualAddress
  0,           // SizeOfRawData
  0,           // PointerToRawData
  0,           // PointerToRelocations
  0,           // PointerToLinenumbers
  0,           // NumberOfRelocations
  0,           // NumberOfLinenumbers
  0x40000040   // Characteristics (data, readable)
};

tPeImageSectionHeader PeSectionHeaderImpData =
{
  { ".idata" }, // Name
  { 0 },       // VirtualSize
  0,           // VirtualAddress
  0,           // SizeOfRawData
  0,           // PointerToRawData
  0,           // PointerToRelocations
  0,           // PointerToLinenumbers
  0,           // NumberOfRelocations
  0,           // NumberOfLinenumbers
  0xc0000040   // Characteristics (data, readable, writable)
};

tPeImageSectionHeader PeSectionHeaderData =
{
  { ".data" }, // Name
  { 0 },       // VirtualSize
  0,           // VirtualAddress
  0,           // SizeOfRawData
  0,           // PointerToRawData
  0,           // PointerToRelocations
  0,           // PointerToLinenumbers
  0,           // NumberOfRelocations
  0,           // NumberOfLinenumbers
  0xc0000040   // Characteristics (data, readable, writable)
};

tPeImageSectionHeader PeSectionHeaderReloc =
{
  { ".reloc" }, // Name
  { 0 },       // VirtualSize
  0,           // VirtualAddress
  0,           // SizeOfRawData
  0,           // PointerToRawData
  0,           // PointerToRelocations
  0,           // PointerToLinenumbers
  0,           // NumberOfRelocations
  0,           // NumberOfLinenumbers
  0x42000040   // Characteristics (data, readable, discardable)
};

Elf32_Ehdr ElfHeader =
{
  { "\177ELF\1\1\1" }, // e_ident (32-bit objects, little-endian, current version)
  ET_EXEC,             // e_type (executable)
  EM_386,              // e_machine (Intel 80386)
  1,                   // e_version (current version)
  0,                   // e_entry
  sizeof(Elf32_Ehdr),  // e_phoff
  0,                   // e_shoff
  0,                   // e_flags
  sizeof(Elf32_Ehdr),  // e_ehsize
  sizeof(Elf32_Phdr),  // e_phentsize
  1,                   // e_phnum
  0,                   // e_shentsize
  0,                   // e_shnum
  0                    // e_shstrndx
};

Elf32_Phdr ElfProgramHeaders[2] =
{
  // .text
  {
    1,   // p_type (load)
    0,   // p_offset
    0,   // p_vaddr
    0,   // p_paddr
    0,   // p_filesz
    0,   // p_memsz
    5,   // p_flags (readable, executable)
    4096 // p_align
  },
  // .data
  {
    1,   // p_type (load)
    0,   // p_offset
    0,   // p_vaddr
    0,   // p_paddr
    0,   // p_filesz
    0,   // p_memsz
    6,   // p_flags (readable, writable)
    4096 // p_align
  }
};

Mach32_Header MachHeader =
{
  MACH_MAGIC_32,                // magic
  MACH_CPU_TYPE_X86,            // cputype
  MACH_CPU_SUBTYPE_I386_ALL,    // cpusubtype
  MACH_EXECUTE,                 // filetype
  0,                            // ncmds
  0,                            // sizeofcmds
  MACH_NOUNDEFS,                // flags
};

tAout AoutHeader =
{
  OMAGIC | 0x640000/*80386*/, // magic
  0, // text
  0, // data
  0, // bss
  0, // syms
  0, // entry
  0, // trsize
  0  // drsize
};

void Pass(int pass, FILE* fout, uint32 hdrsz)
{
  uint32 startOfs = Origin;
  uint32 ofs = Origin;
  uint32 written = 0;
  uint32 j, fIdx, sectIdx, relSectIdx;

  // Two passes:
  //   pass 0 (may be repeated for flat binaries) is used to find out section and symbol locations
  //   pass 1 is used to perform actual relocation and write the executable file

  if (!pass)
  {
    // Will use these to find the minimum and maximum offsets/addresses within combined sections/segments
    pSectDescrs[SectCnt].Start = 0xFFFFFFFF;
    pSectDescrs[SectCnt].Stop = 0;
    pSectDescrs[SectCnt + 1].Start = 0xFFFFFFFF;
    pSectDescrs[SectCnt + 1].Stop = 0;
  }

  // Handle individual sections
  for (j = 0; j < SectCnt; j++)
  {
    int isDataSection = !(pSectDescrs[j].Attrs & SHF_EXECINSTR);

    if (!pass)
    {
      // Will use these to find the minimum and maximum offsets/addresses within individual sections/segments
      pSectDescrs[j].Start = 0xFFFFFFFF;
      pSectDescrs[j].Stop = 0;
    }

    for (fIdx = 0; fIdx < ObjFileCnt; fIdx++)
    {
      tElfMeta* pMeta = &pMetas[fIdx];
      if (!pMeta->Needed)
        continue;
      for (sectIdx = 0; sectIdx < pMeta->SectionCnt; sectIdx++)
      {
        tElfSection* pSect = &pMeta->pSections[sectIdx];
        tElfSection* pRelSect = NULL;
        if (strcmp(pSectDescrs[j].pName, pMeta->pSectNames + pSect->h.sh_name))
          continue;
        // Find relocations for this section, if any
        for (relSectIdx = 0; relSectIdx < pMeta->SectionCnt; relSectIdx++)
        {
          if (pMeta->pSections[relSectIdx].h.sh_type == SHT_REL &&
              pMeta->pSections[relSectIdx].h.sh_info == sectIdx)
          {
            pRelSect = &pMeta->pSections[relSectIdx];
            break;
          }
        }

        // Align the section and check for segment overflow
        {
          uint32 newOfs, align = pSect->h.sh_addralign;
          if (align & (align - 1))
            error("Section alignment not a power of 2\n");
          switch (OutputFormat)
          {
          case FormatDosComTiny:
          case FormatFlat16:
          case FormatDosExeSmall:
            // Don't use unreasonably large alignments (greater than 4) in 16-bit code segments
            // (in ELF32 object files produced by NASM, .text sections are 16-byte aligned)
            if (!isDataSection && align > 4)
              align = 4;
            break;
          case FormatDosExeHuge:
            // Force 4-byte alignment of the .relot and .relod relocation sections in the huge mode(l)
            if (StrAnyOf(pMeta->pSectNames + pSect->h.sh_name, ".relot\0"
                                                               ".relod\0"))
              align = 4;
            if (align > 16)
              error("Section alignment larger than paragraph size (16)\n");
            break;
          case FormatWinPe32:
          case FormatElf32:
          case FormatMach32:
            if (align > 4096)
              error("Section alignment larger than page size (4KB)\n");
            break;
          }

          if (align > 1)
          {
            newOfs = AlignTo(ofs, align);
            if (newOfs < ofs)
              errSectTooBig();
            if (pass)
            {
              if (pSect->h.sh_type == SHT_PROGBITS ||
                  !UseBss)
              {
                unsigned char fillByte = 0xCC * !isDataSection; // int3
                FillWithByte(fillByte, newOfs - ofs, fout);
              }
            }
            ofs = newOfs;
          }

          newOfs = ofs + pSect->h.sh_size;
          if (newOfs < ofs)
            errSectTooBig();
          switch (OutputFormat)
          {
          case FormatDosComTiny:
          case FormatFlat16:
          case FormatDosExeSmall:
            if (newOfs > 0x10000)
              errSectTooBig();
            break;
          }
        }

        pSect->OutOffset = ofs;
        pSect->OutFileOffset = hdrsz + written + (ofs - startOfs);

        if (!pass)
        {
          // Calculate start addresses of combined sections
          if (pSectDescrs[j].Start > pSect->OutOffset)
            pSectDescrs[j].Start = pSect->OutOffset;

          if (pSectDescrs[SectCnt + isDataSection].Start > pSectDescrs[j].Start)
            pSectDescrs[SectCnt + isDataSection].Start = pSectDescrs[j].Start;
        }

        if (pass)
        {
          // Relocate (if needed) and write the section
          if (pSect->h.sh_type == SHT_PROGBITS)
          {
            FILE* fin = Fopen(pMeta->ElfName, "rb");
            if (verbose)
              printf("Relocating %s in %s:\n", pMeta->pSectNames + pSect->h.sh_name, pMeta->ElfName);
            Fseek(fin, pMeta->ObjOffset + pSect->h.sh_offset, SEEK_SET);
            RelocateAndWriteSection(fout, fin, pSect->h.sh_size, pMeta, pRelSect);
            Fclose(fin);
            if (verbose)
              puts("");
          }
          else if (!UseBss) // if (pSect->h.sh_type == SHT_NOBITS)
          {
            FillWithByte(0, pSect->h.sh_size, fout);
          }
        }

        ofs += pSect->h.sh_size;

        if (!pass)
        {
          // Calculate stop addresses of combined sections (actually, the addresses right after the end)
          if (pSectDescrs[j].Stop < pSect->OutOffset + pSect->h.sh_size)
            pSectDescrs[j].Stop = pSect->OutOffset + pSect->h.sh_size;

          if (pSectDescrs[SectCnt + isDataSection].Stop < pSectDescrs[j].Stop)
            pSectDescrs[SectCnt + isDataSection].Stop = pSectDescrs[j].Stop;
        }
      } // endof: for (sectIdx = 0; sectIdx < pMeta->SectionCnt; sectIdx++)
    } // endof: for (fIdx = 0; fIdx < ObjFileCnt; fIdx++)

    if (UnrealRelodSize && !strcmp(pSectDescrs[j].pName, ".relod"))
    {
      uint32 newOfs = (ofs + 3) / 4 * 4;
      if (newOfs < ofs)
        errSectTooBig();

      if (pass && newOfs != ofs)
        FillWithByte(0, newOfs - ofs, fout);
      ofs = newOfs;

      newOfs = ofs + UnrealRelodSize;
      if (newOfs < ofs)
        errSectTooBig();

      if (!pass)
      {
        // Calculate start addresses of combined sections
        if (pSectDescrs[j].Start > ofs)
          pSectDescrs[j].Start = ofs;

        if (pSectDescrs[SectCnt + isDataSection].Start > pSectDescrs[j].Start)
          pSectDescrs[SectCnt + isDataSection].Start = pSectDescrs[j].Start;

        // Calculate stop addresses of combined sections (actually, the addresses right after the end)
        if (pSectDescrs[j].Stop < newOfs)
          pSectDescrs[j].Stop = newOfs;

        if (pSectDescrs[SectCnt + isDataSection].Stop < pSectDescrs[j].Stop)
          pSectDescrs[SectCnt + isDataSection].Stop = pSectDescrs[j].Stop;
      }
      else
      {
        uint32 sz = 0;
        for (fIdx = 0; fIdx < ObjFileCnt; fIdx++)
        {
          tElfMeta* pMeta = &pMetas[fIdx];
          if (!pMeta->Needed)
            continue;
          for (sectIdx = 0; sectIdx < pMeta->SectionCnt; sectIdx++)
          {
            tElfSection* pRelSect = &pMeta->pSections[sectIdx];
            if (pRelSect->h.sh_type == SHT_REL)
            {
              // Handle only 32-bit non-PC-relative relocations.
              uint32 relIdx;
              for (relIdx = 0; relIdx < pRelSect->h.sh_entsize; relIdx++)
              {
                Elf32_Rel* pRel = &pRelSect->d.pRel[relIdx];
                uint32 symIdx = pRel->r_info >> 8;
                uint32 absSym = symIdx == 0;
                uint32 relType = pRel->r_info & 0xFFu;
                if (!absSym && relType == R_386_32)
                {
                  uint32 addr = pRel->r_offset + pMeta->pSections[pRelSect->h.sh_info].OutOffset;
                  if (sz >= UnrealRelodSize)
                    errInternal(1);
                  Fwrite(&addr, sizeof addr, fout);
                  sz += 4;
                }
              }
            }
          }
        }
        if (sz != UnrealRelodSize)
          errInternal(2);
      }
      ofs = newOfs;
    } // endof: if (UnrealRelodSize && !strcmp(pSectDescrs[j].pName, ".relod"))

    // Trailing section/segment/executable padding
    switch (OutputFormat)
    {
    case FormatDosExeSmall:
      if (!isDataSection &&
          (j + 1 == SectCnt ||
           !(pSectDescrs[j + 1].Attrs & SHF_EXECINSTR))) // last code section or last code section before first data section
      {
        // The code segment has been written, prepare for writing the data segment.
        // Pad the code segment to an integral number of 16-byte paragraphs
        uint32 newOfs = AlignTo(ofs, 16);
        if (pass)
        {
          FillWithByte(0xCC, newOfs - ofs, fout); // int3
        }
        ofs = newOfs;
        // Reset the offset for the data segment
        written += ofs - startOfs;
        ofs = startOfs = 0;
        // Reserve several bytes so that variables don't appear at address/offset 0 (NULL)
        if (j + 1 != SectCnt)
        {
          if (pass)
          {
            Fwrite("NULL", 4, fout);
          }
          ofs += 4;
        }
      }
      break;
    case FormatWinPe32:
    case FormatElf32:
    case FormatAout:
    case FormatMach32:
      if (!isDataSection &&
          (j + 1 == SectCnt ||
           !(pSectDescrs[j + 1].Attrs & SHF_EXECINSTR))) // last code section or last code section before first data section
      {
        // The code section has been written, prepare for writing the data section.
        // Pad the code section to an integral number of 4KB pages
        uint32 newOfs = AlignTo(ofs, 4096);
        if (newOfs < ofs)
          errSectTooBig();
        if (pass)
        {
          FillWithByte(0xCC, newOfs - ofs, fout); // int3
        }
        ofs = newOfs;
      }
      else
      {
        int lastData =
          (!UseBss && j + 1 == SectCnt) ||
          (UseBss &&
           !(pSectDescrs[j].Attrs & SHT_NOBITS) &&
           (j + 1 == SectCnt ||
            (pSectDescrs[j + 1].Attrs & SHT_NOBITS))); // last written data section
        int lastImpData =
          OutputFormat == FormatWinPe32 &&
          !strncmp(pSectDescrs[j].pName, ".dll_", sizeof ".dll_" - 1) &&
          ((pSectDescrs[j].Attrs & (SHT_NOBITS | SHF_WRITE | SHF_EXECINSTR)) == SHF_WRITE) &&
          (j + 1 == SectCnt ||
           strncmp(pSectDescrs[j + 1].pName, ".dll_", sizeof ".dll_" - 1)); // last import data section in PE
        int lastRoData =
          OutputFormat == FormatWinPe32 &&
          !(pSectDescrs[j].Attrs & (SHT_NOBITS | SHF_WRITE | SHF_EXECINSTR)) &&
          (j + 1 == SectCnt ||
           (pSectDescrs[j + 1].Attrs & SHF_WRITE)); // last read-only data section in PE
        if (lastRoData || lastImpData || lastData)
        {
          // The data section has been written.
          // Pad the data section to an integral number of 4KB pages
          uint32 newOfs = AlignTo(ofs, 4096);
          if (newOfs < ofs)
            errSectTooBig();
          if (pass)
          {
            FillWithByte(0, newOfs - ofs, fout);
          }
          ofs = newOfs;
        }
      }
      break;
    }
  } // endof: for (j = 0; j < SectCnt; j++)
}

void RwFlat(void)
{
  int hasData = !(pSectDescrs[SectCnt - 1].Attrs & SHF_EXECINSTR); // non-executable/data sections, if any, are last
  FILE* fout = Fopen(OutName, "wb+");
  uint32 hdrsz = 0;
  uint32 ip;

  // Based on the file format, figure out:
  // - header sizes
  // - start offsets/base addresses
  // - stack size and location
  switch (OutputFormat)
  {
  case FormatDosComTiny:
    Origin = 0x100;
    if (StackSize == 0xFFFFFFFF)
      StackSize = 8192; // default stack size if unspecified
    if (StackSize < 4096)
      errStackTooSmall();
    if (StackSize > 0xFFFC)
      errStackTooBig();
    pSectDescrs[SectCnt + 2].Start = 0xFFFC - StackSize; // __start_stack__
    pSectDescrs[SectCnt + 2].Stop = 0xFFFC; // __stop_stack__ should be unused
    break;
  case FormatFlat16:
  case FormatFlat32:
    if (Origin == 0xFFFFFFFF)
      Origin = 0; // default origin if unspecified
    if (OutputFormat == FormatFlat16 && Origin > 0xFFFF)
      errSectTooBig();
    break;
  }

  Pass(0, NULL, 0);

  // Ensure the entry point in flat binaries is at the very first byte
  ip = FindSymbolAddress(EntryPoint);
  if (ip != Origin)
  {
    uint32 newOrigin;
    uint32 imm;
    // The entry point is not at the very first byte of the flat binary,
    // start the binary with a jump to the entry point
    hdrsz = (OutputFormat == FormatFlat32) ? 1+4 : 1+2; // size of the jump instruction
    newOrigin = Origin + hdrsz; // adjust origin w.r.t. the jump instruction size
    if (newOrigin < Origin)
      errSectTooBig();
    if (OutputFormat == FormatFlat16 && newOrigin > 0xFFFF)
      errSectTooBig();
    Origin = newOrigin;

    Pass(0, NULL, hdrsz); // repeat pass 0, now with a fake header containing a jump instruction to the entry point

    // It was determined in pass 0 that the entry point was not
    // at the very first byte of the flat binary,
    // a fake header containing a jump instruction to the entry point is needed
    ip = FindSymbolAddress(EntryPoint);
    imm = ip - Origin;
    Fwrite("\xE9", 1, fout); // jmp rel16/32 to entry point
    Fwrite(&imm, hdrsz - 1, fout);
  }

  // Check for code/data colliding with the stack
  if (OutputFormat == FormatDosComTiny &&
      pSectDescrs[SectCnt + hasData].Stop > pSectDescrs[SectCnt + 2].Start)
    errStackTooBig();

  Pass(1, fout, hdrsz);

  Fclose(fout);
}

void RwAout(void)
{
  int hasData = !(pSectDescrs[SectCnt - 1].Attrs & SHF_EXECINSTR); // non-executable/data sections, if any, are last
  FILE* fout = Fopen(OutName, "wb+");
  uint32 start, stop;
  uint32 hdrsz = sizeof AoutHeader;
  uint32 j, fIdx, sectIdx, relSectIdx, relIdx;

  Origin = 0;

  // Copy the DPMI stub
  if (StubName)
  {
    static unsigned char buf[FBUF_SIZE]; // must be larger than tDosExeHeader
    tDosExeHeader h;
    static uint32 stubInfo[16];
    FILE* fin = Fopen(StubName, "rb");
    uint32 sz;
    uint32 header = 0, i = 0;
    memset(&h, 0, sizeof h); // shut gcc up
    while ((sz = fread(buf, 1, sizeof buf, fin)) != 0)
    {
      Fwrite(buf, sz, fout);
      hdrsz += sz;
      if (i == 0 && sz >= sizeof h)
      {
        // Preserve the EXE header for simple validation
        memcpy(&h, buf, sizeof h);
        header = 1;
      }
      i++;
    }
    Fclose(fin);
    if (header)
    {
      // The header must contain the correct size of the stub file.
      // The stub will use the size from the header to locate the extra info and the a.out portion.
      uint32 sz = ((uint32)h.PageCnt - (h.PartPage != 0)) * 512 + h.PartPage;
      if (h.Signature[0] != 'M' || h.Signature[1] != 'Z' ||
          sizeof AoutHeader + sz != hdrsz)
        header = 0;
    }
    if (!header)
      error("Invalid stub\n");

    // Add extra info for the stub to use
    stubInfo[0] = 0x21245044; // magic number ("DP$!")

    if (StackSize == 0xFFFFFFFF || StackSize == 0)
      StackSize = 65536; // default stack size if unspecified
    StackSize = (StackSize + 0xFFF) & 0xFFFFF000;
    stubInfo[1] = StackSize;

    if (MinHeap == 0xFFFFFFFF || MinHeap == 0)
      MinHeap = 0x80000; // default minimum heap size if unspecified
    MinHeap = (MinHeap + 0xFFF) & 0xFFFFF000;
    if (MaxHeap == 0xFFFFFFFF)
      MaxHeap = 0x1000000; // default maximum heap size if unspecified
    MaxHeap = (MaxHeap + 0xFFF) & 0xFFFFF000;
    if (MaxHeap < MinHeap)
      MaxHeap = MinHeap;
    stubInfo[2] = MinHeap;
    stubInfo[3] = MaxHeap;

    Fwrite(stubInfo, sizeof stubInfo, fout);
    hdrsz += sizeof stubInfo;
  }

  // TBD??? insert something (NOPs?) at the beginning to ensure no function is at address/offset 0(NULL)

  Pass(0, NULL, hdrsz);

  AoutHeader.entry = FindSymbolAddress(EntryPoint);
  start = pSectDescrs[SectCnt].Start & 0xFFFFF000;
  stop = (pSectDescrs[SectCnt].Stop + 0xFFF) & 0xFFFFF000;
  AoutHeader.text = stop - start;
  if (hasData)
  {
    start = pSectDescrs[SectCnt + 1].Start & 0xFFFFF000;
    stop = (pSectDescrs[SectCnt + 1].Stop + 0xFFF) & 0xFFFFF000;
    AoutHeader.data = stop - start;
    if ((pSectDescrs[SectCnt - 1].Attrs & SHT_NOBITS) && UseBss)
    {
      uint32 i = SectCnt - 1;
      uint32 datasz = 0;
      while (pSectDescrs[i].Attrs & SHT_NOBITS)
        i--;
      if ((pSectDescrs[i].Attrs & SHF_EXECINSTR) == 0)
        datasz = ((pSectDescrs[i].Stop + 0xFFF) & 0xFFFFF000) - start;
      AoutHeader.bss = AoutHeader.data - datasz;
      AoutHeader.data = datasz;
    }
  }
  Fwrite(&AoutHeader, sizeof AoutHeader, fout);

  Pass(1, fout, hdrsz);

  // Write relocation table

  // Handle individual sections
  for (j = 0; j < SectCnt; j++)
  {
    int isDataSection = !(pSectDescrs[j].Attrs & SHF_EXECINSTR);

    for (fIdx = 0; fIdx < ObjFileCnt; fIdx++)
    {
      tElfMeta* pMeta = &pMetas[fIdx];
      if (!pMeta->Needed)
        continue;
      for (sectIdx = 0; sectIdx < pMeta->SectionCnt; sectIdx++)
      {
        tElfSection* pSect = &pMeta->pSections[sectIdx];
        tElfSection* pRelSect = NULL;
        if (pSect->h.sh_type != SHT_PROGBITS)
          continue;
        if (strcmp(pSectDescrs[j].pName, pMeta->pSectNames + pSect->h.sh_name))
          continue;
        // Find relocations for this section, if any
        for (relSectIdx = 0; relSectIdx < pMeta->SectionCnt; relSectIdx++)
        {
          if (pMeta->pSections[relSectIdx].h.sh_type == SHT_REL &&
              pMeta->pSections[relSectIdx].h.sh_info == sectIdx)
          {
            pRelSect = &pMeta->pSections[relSectIdx];
            break;
          }
        }
        if (!pRelSect)
          continue;

        // Write relocation records
        for (relIdx = 0; relIdx < pRelSect->h.sh_entsize; relIdx++)
        {
          Elf32_Rel* pRel = &pRelSect->d.pRel[relIdx];
          uint32 symIdx = pRel->r_info >> 8;
          uint32 absSym = symIdx == 0;
          uint32 relType = pRel->r_info & 0xFFu;
          uint32 relative = relType == R_386_PC16 || relType == R_386_PC32;
          uint32 length = (relType == R_386_32 || relType == R_386_PC32) * 2 +
                          (relType == R_386_16 || relType == R_386_PC16);
          tAoutRel aoutRel;

          if (absSym != relative)
            continue;

          aoutRel.address = pRel->r_offset + pMeta->pSections[pRelSect->h.sh_info].OutOffset -
            pSectDescrs[SectCnt + isDataSection].Start;
          aoutRel.info = (relative << 24) | (length << 25);
          // TBD??? use N_TEXT, N_DATA and N_BSS instead of N_UNDF
          aoutRel.info |= absSym ? N_ABS : N_UNDF;

          Fwrite(&aoutRel, sizeof aoutRel, fout);

          AoutHeader.trsize += !isDataSection;
          AoutHeader.drsize += isDataSection;
        }
      } // endof: for (sectIdx = 0; sectIdx < pMeta->SectionCnt; sectIdx++)
    } // endof: for (fIdx = 0; fIdx < ObjFileCnt; fIdx++)
  } // endof: for (j = 0; j < SectCnt; j++)

  // update AoutHeader
  AoutHeader.trsize *= sizeof(tAoutRel);
  AoutHeader.drsize *= sizeof(tAoutRel);
  Fseek(fout, hdrsz - sizeof AoutHeader, SEEK_SET);
  Fwrite(&AoutHeader, sizeof AoutHeader, fout);

  Fclose(fout);
}

void CheckFxnSizes(void)
{
  // In the huge mode(l) individual functions must each fit into a 64KB segment.
  // A special non-allocated section, ".fxnsz", holds function sizes. Check them.
  uint32 fIdx, sectIdx;
  for (fIdx = 0; fIdx < ObjFileCnt; fIdx++)
  {
    tElfMeta* pMeta = &pMetas[fIdx];
    if (!pMeta->Needed)
      continue;

    for (sectIdx = 0; sectIdx < pMeta->SectionCnt; sectIdx++)
    {
      tElfSection* pSect = &pMeta->pSections[sectIdx];
      uint32 sz = pSect->h.sh_size;
      if (!(pSect->h.sh_flags & SHF_ALLOC) &&
          sz &&
          !strcmp(pMeta->pSectNames + pSect->h.sh_name, ".fxnsz"))
      {
        FILE* fin = Fopen(pMeta->ElfName, "rb");
        uint32 o, fsz;
        Fseek(fin, pMeta->ObjOffset + pSect->h.sh_offset, SEEK_SET);
        for (o = 0; o < sz; o += sizeof fsz)
        {
          Fread(&fsz, sizeof fsz, fin);
          if (fsz >= 0xFFF0) // allow for imperfect alignment with segment boundary
            error("Function larger than 64KB found in '%s'\n", pMeta->ElfName);
        }
        Fclose(fin);
        continue;
      }
    }
  }
}

void RwDosExe(void)
{
  int hasData = !(pSectDescrs[SectCnt - 1].Attrs & SHF_EXECINSTR); // non-executable/data sections, if any, are last
  FILE* fout = Fopen(OutName, "wb+");
  uint32 hdrsz = 0;

  // Based on the file format, figure out:
  // - header sizes
  // - start offsets/base addresses
  // - stack size and location
  switch (OutputFormat)
  {
  case FormatDosExeSmall:
    Origin = sizeof(tDosExeHeader);
    hdrsz = sizeof(tDosExeHeader);
    if (StackSize == 0xFFFFFFFF)
      StackSize = 8192; // default stack size if unspecified
    if (StackSize < 4096)
      errStackTooSmall();
    if (StackSize > 0xFFFC)
      errStackTooBig();
    pSectDescrs[SectCnt + 2].Start = 0xFFFC - StackSize; // __start_stack__
    pSectDescrs[SectCnt + 2].Stop = 0xFFFC; // __stop_stack__ should be unused
    break;
  case FormatDosExeHuge:
  case FormatDosExeUnreal:
    Origin = sizeof(tDosExeHeader);
    hdrsz = sizeof(tDosExeHeader);
    if (StackSize == 0xFFFFFFFF)
      StackSize = 32768; // default stack size if unspecified
    if (StackSize < 8192)
      errStackTooSmall();
    if (StackSize > 0xFFFC)
      errStackTooBig();
    break;
  }

  Pass(0, NULL, hdrsz);

  // Check for code/data colliding with the stack
  if (OutputFormat == FormatDosExeSmall &&
      pSectDescrs[SectCnt + hasData].Stop > pSectDescrs[SectCnt + 2].Start)
    errStackTooBig();

  switch (OutputFormat)
  {
  case FormatDosExeSmall:
    {
      uint32 dsz = 0, fsz;
      if (hasData)
        dsz = pSectDescrs[SectCnt + 1].Stop; // data size
      fsz = (pSectDescrs[SectCnt].Stop + 15) / 16 * 16; // code size + padding
      if ((pSectDescrs[SectCnt - 1].Attrs & SHT_NOBITS) && UseBss)
      {
        uint32 i = SectCnt - 1;
        while (pSectDescrs[i].Attrs & SHT_NOBITS)
          i--;
        if (!(pSectDescrs[i].Attrs & SHF_EXECINSTR))
        {
          fsz += pSectDescrs[i].Stop; // + non-bss data size (includes "NULL")
          dsz = pSectDescrs[i].Stop;
        }
        else
        {
          fsz += 4; // account for "NULL" at the beginning of the data/stack segment
          dsz = 4;
        }
      }
      else
      {
        fsz += dsz; // + non-bss data size
      }
      DosExeHeader.PartPage = fsz % 512;
      DosExeHeader.PageCnt = (fsz + 511) / 512;
      DosExeHeader.InitIp = FindSymbolAddress(EntryPoint);
      DosExeHeader.InitCs = 0xFFFE;
      DosExeHeader.InitSs = (pSectDescrs[SectCnt].Stop + 15) / 16 - 2; // data/stack segment starts right after code segment's padding
      DosExeHeader.MaxAlloc = DosExeHeader.MinAlloc = 4096 - dsz / 16; // maximum stack size = data segment size - data size
      Fwrite(&DosExeHeader, sizeof DosExeHeader, fout);
    }
    break;
  case FormatDosExeHuge:
  case FormatDosExeUnreal:
    {
      uint32 ip = FindSymbolAddress(EntryPoint);
      uint32 sz = pSectDescrs[SectCnt].Stop; // code size
      uint32 fsz;
      if (hasData)
        sz = pSectDescrs[SectCnt + 1].Stop; // code size + data size
      if (sz > 524288)
        error("Executable too big (bigger than 512KB)\n");
      if ((pSectDescrs[SectCnt - 1].Attrs & SHT_NOBITS) && UseBss)
      {
        uint32 i = SectCnt - 1;
        while (pSectDescrs[i].Attrs & SHT_NOBITS)
          i--;
        fsz = pSectDescrs[i].Stop;
      }
      else
      {
        fsz = sz;
      }
      DosExeHeader.PartPage = fsz % 512;
      DosExeHeader.PageCnt = (fsz + 511) / 512;
      DosExeHeader.InitIp = ip & 0xF;
      DosExeHeader.InitCs = (ip >> 4) - 2;
      DosExeHeader.InitSs = (sz + 15) / 16 - 2; // stack segment starts right after data segment's padding
      DosExeHeader.InitSp = StackSize;
      DosExeHeader.MaxAlloc = DosExeHeader.MinAlloc = (sz - fsz + 15) / 16 + (StackSize + 15) / 16 + 1; // maximum stack size = 64KB
      Fwrite(&DosExeHeader, sizeof DosExeHeader, fout);
    }
    break;
  }

  Pass(1, fout, hdrsz);

  Fclose(fout);
}

void RwMach(void)
{
  int hasData = !(pSectDescrs[SectCnt - 1].Attrs & SHF_EXECINSTR); // non-executable/data sections, if any, are last
  FILE* fout = Fopen(OutName, "wb+");
  uint32 sectionIdx;
  uint32 hdrsz;
  uint32 imageBase;
  int hasPageZero;
  uint32 start, stop;
  uint32 sections_stop, vmaddr_stop;
  uint32 predefinedLinkeditSize = 52;
  Mach32_SegmentCmd linkeditSegmentCmd;
  static const uint32 num_syms = 2;
  static const uint32 strsize = 28;
  Mach32_SymtabCmd symtabCmd;
  Mach32_ThreadCmd unixThreadCmd =
  {
    MACH_LC_UNIXTHREAD,         // cmd
    sizeof(Mach32_ThreadCmd),   // cmdsize
    MACH_X86_THREAD_STATE,      // flavor
    16,                         // count
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // state
  };
  Mach32_Nlist mhExecuteHeaderSym =
  {
    2,                            // n_strx
    MACH_N_EXT | MACH_N_ABS,      // n_type
    0x01,                         // n_sect
    MACH_REFERENCED_DYNAMICALLY,  // n_desc
    0x0,                          // n_value
  };
  Mach32_Nlist startSym =
  {
    22,                                     // n_strx
    MACH_N_EXT | MACH_N_SECT,               // n_type
    0x01,                                   // n_sect
    MACH_REFERENCE_FLAG_UNDEFINED_NON_LAZY, // n_desc
    0,                                      // n_value
  };
  char predefinedStringTable[] = "\x20\x0__mh_execute_header\x0start";
  Mach32_SegmentCmd segz = // unmapped memory to catch NULL pointer dereferences
  {
    MACH_LC_SEGMENT, // cmd
    sizeof(Mach32_SegmentCmd), // cmdsize
    { "__PAGEZERO" }, // segname
    0, // vmaddr
    0, // vmsize
    0, // fileoff
    0, // filesize
    0, // maxprot
    0, // initprot
    0, // nsects
    0, // flags
  };
  // TBD!!! Check if this is still true: using proper segment/section names drives otool crazy.
  Mach32_SegmentCmd seg[2] =
  {
    {
      MACH_LC_SEGMENT, // cmd
      sizeof(Mach32_SegmentCmd) + sizeof(Mach32_Section), // cmdsize
      { "__TEXT" }, // segname
      0, // vmaddr
      0, // vmsize
      0, // fileoff
      0, // filesize
      MACH_VM_PROT_READ | MACH_VM_PROT_EXECUTE | MACH_VM_PROT_WRITE, // maxprot
      MACH_VM_PROT_READ | MACH_VM_PROT_EXECUTE, // initprot
      1, // nsects
      0, // flags
    },
    {
      MACH_LC_SEGMENT, // cmd
      sizeof(Mach32_SegmentCmd) + sizeof(Mach32_Section), // cmdsize
      { "__DATA" }, // segname
      0, // vmaddr
      0, // vmsize
      0, // fileoff
      0, // filesize
      MACH_VM_PROT_READ | MACH_VM_PROT_EXECUTE | MACH_VM_PROT_WRITE, // maxprot
      MACH_VM_PROT_READ | MACH_VM_PROT_WRITE, // initprot
      1, // nsects
      0, // flags
    },
  };
  Mach32_Section sect[2] =
  {
    {
      { "__text" }, // sectname
      { "__TEXT" }, // segname
      0, // addr
      0, // size
      0, // offset
      0, // align
      0, // reloff
      0, // nreloc
      S_ATTR_PURE_INSTRUCTIONS | S_ATTR_SOME_INSTRUCTIONS, // flags
      0, // reserved1
      0, // reserved2
    },
    {
      { "__data" }, // sectname
      { "__DATA" }, // segname
      0, // addr
      0, // size
      0, // offset
      0, // align
      0, // reloff
      0, // nreloc
      0, // flags
      0, // reserved1
      0, // reserved2
    },
  };
  // Note that we create sections (in addition to segments) and
  // a couple of symbols to make the OS and tools happy (there
  // seem to be tighter checks in newer MacOS).
  // They shouldn't be needed otherwise.

  if (Origin == 0xFFFFFFFF)
    imageBase = 0x1000; // default image base if origin is unspecified
  else
    imageBase = Origin & 0xFFFFF000;
  if (imageBase >= 0xFFFFF000)
    errSectTooBig();
  hasPageZero = imageBase != 0;

  MachHeader.ncmds = hasPageZero + 4 + hasData;
  MachHeader.sizeofcmds =
    hasPageZero * sizeof(Mach32_SegmentCmd) +
    (1 + hasData) * (sizeof(Mach32_SegmentCmd) + sizeof(Mach32_Section)) +
    sizeof(Mach32_SegmentCmd) + sizeof(Mach32_SymtabCmd) +
    sizeof(Mach32_ThreadCmd);

  hdrsz = sizeof MachHeader + MachHeader.sizeofcmds;
  Origin = imageBase + hdrsz;

  Pass(0, NULL, hdrsz);

  Fwrite(&MachHeader, sizeof MachHeader, fout);

  // Note that the header is part of the code segment.
  start = imageBase;
  stop = (pSectDescrs[SectCnt].Stop + 0xFFF) & 0xFFFFF000;
  seg[0].filesize = seg[0].vmsize = stop - start;
  seg[0].vmaddr = start;
  sect[0].addr = Origin;
  sect[0].offset = hdrsz;
  sect[0].size = stop - Origin; 

  if (hasData)
  {
    start = pSectDescrs[SectCnt + 1].Start & 0xFFFFF000;
    stop = (pSectDescrs[SectCnt + 1].Stop + 0xFFF) & 0xFFFFF000;

    seg[1].vmsize = stop - start;
    sect[1].addr = seg[1].vmaddr = start;
    sect[1].offset = seg[1].fileoff = start - imageBase;

    if ((pSectDescrs[SectCnt - 1].Attrs & SHT_NOBITS) && UseBss)
    {
      uint32 i = SectCnt - 1;
      while (pSectDescrs[i].Attrs & SHT_NOBITS)
        i--;
      seg[1].filesize = ((pSectDescrs[i].Stop + 0xFFF) & 0xFFFFF000) - start;
    }
    else
    {
      seg[1].filesize = stop - start;
    }

    sect[1].size = seg[1].filesize; 
  }

  if (hasPageZero)
  {
    segz.vmsize = imageBase;
    Fwrite(&segz, sizeof segz, fout);
  }

  for (sectionIdx = 0; sectionIdx <= hasData; ++sectionIdx)
  {
    Fwrite(&seg[sectionIdx], sizeof seg[sectionIdx], fout);
    Fwrite(&sect[sectionIdx], sizeof sect[sectionIdx], fout);
  }

  sections_stop = seg[hasData].fileoff + seg[hasData].filesize;
  vmaddr_stop = seg[hasData].vmaddr + seg[hasData].vmsize;

  linkeditSegmentCmd.cmd = MACH_LC_SEGMENT;
  linkeditSegmentCmd.cmdsize = sizeof(Mach32_SegmentCmd);
  strncpy(linkeditSegmentCmd.segname, "__LINKEDIT", 16);
  linkeditSegmentCmd.vmaddr = vmaddr_stop;
  // TBD???(tilarids): Should we change the vmsize here?
  linkeditSegmentCmd.vmsize = 0x1000;
  linkeditSegmentCmd.fileoff = sections_stop;
  linkeditSegmentCmd.filesize = predefinedLinkeditSize;
  linkeditSegmentCmd.maxprot = MACH_VM_PROT_READ | MACH_VM_PROT_EXECUTE | MACH_VM_PROT_WRITE;
  linkeditSegmentCmd.initprot = MACH_VM_PROT_READ;
  linkeditSegmentCmd.nsects = 0x0;
  linkeditSegmentCmd.flags = 0x0;

  // TBD??? Consider writing a proper symbol table.
  symtabCmd.cmd = MACH_LC_SYMTAB;
  symtabCmd.cmdsize = sizeof(Mach32_SymtabCmd);
  symtabCmd.symoff = sections_stop;
  symtabCmd.nsyms = num_syms;
  symtabCmd.stroff = sections_stop + num_syms * sizeof(Mach32_Nlist);
  symtabCmd.strsize = strsize;

  unixThreadCmd.state.eip = FindSymbolAddress(EntryPoint);

  Fwrite(&linkeditSegmentCmd, sizeof linkeditSegmentCmd, fout);
  Fwrite(&symtabCmd, sizeof symtabCmd, fout);
  Fwrite(&unixThreadCmd, sizeof unixThreadCmd, fout);

  Pass(1, fout, hdrsz);

  // Write the symbol table.
  // TBD??? Write a proper table instead of the predefined one.
  mhExecuteHeaderSym.n_value = imageBase;
  startSym.n_value = FindSymbolAddress(EntryPoint);

  Fwrite(&mhExecuteHeaderSym, sizeof mhExecuteHeaderSym, fout);
  Fwrite(&startSym, sizeof startSym, fout);

  // Write the string table.
  // TBD??? Write a proper string table instead of the predefined one.
  Fwrite(predefinedStringTable, sizeof predefinedStringTable, fout);

  Fclose(fout);
}

void RwPe(void)
{
  FILE* fout = Fopen(OutName, "wb+");
  uint32 hdrsz = 0;
  uint32 imageBase = 0;
  uint32 peImportsStart = 0;
  int j = 0;
  int tmpCnt = SectCnt;
  int textSectCnt = 0;
  int roDataSectCnt = 0;
  int impDataSectCnt = 0;
  int dataSectCnt = 0;
  int bssSectCnt = 0;
  int hasData = 0;

  while (tmpCnt &&
         !(pSectDescrs[j].Attrs & SHT_NOBITS) &&
         (pSectDescrs[j].Attrs & SHF_EXECINSTR) &&
         !(pSectDescrs[j].Attrs & SHF_WRITE))
    tmpCnt--, j++, textSectCnt++;
  while (tmpCnt &&
         !(pSectDescrs[j].Attrs & SHT_NOBITS) &&
         !(pSectDescrs[j].Attrs & SHF_EXECINSTR) &&
         !(pSectDescrs[j].Attrs & SHF_WRITE))
    tmpCnt--, j++, roDataSectCnt++;
  while (tmpCnt &&
         !(pSectDescrs[j].Attrs & SHT_NOBITS) &&
         !(pSectDescrs[j].Attrs & SHF_EXECINSTR) &&
         (pSectDescrs[j].Attrs & SHF_WRITE) &&
         !strncmp(pSectDescrs[j].pName, ".dll_", sizeof ".dll_" - 1))
    tmpCnt--, j++, impDataSectCnt++;
  while (tmpCnt &&
         !(pSectDescrs[j].Attrs & SHT_NOBITS) &&
         !(pSectDescrs[j].Attrs & SHF_EXECINSTR) &&
         (pSectDescrs[j].Attrs & SHF_WRITE))
    tmpCnt--, j++, dataSectCnt++;
  while (tmpCnt &&
         (pSectDescrs[j].Attrs & SHT_NOBITS) &&
         !(pSectDescrs[j].Attrs & SHF_EXECINSTR) &&
         (pSectDescrs[j].Attrs & SHF_WRITE))
    tmpCnt--, j++, bssSectCnt++;

  if (!textSectCnt || tmpCnt)
    errInternal(3);

  hasData = roDataSectCnt || impDataSectCnt || dataSectCnt || bssSectCnt;

  // Figure out:
  // - header sizes
  // - start offsets/base addresses
  // - stack size and location
  if (Origin == 0xFFFFFFFF)
    imageBase = 0x00400000; // default image base if origin is unspecified
  else
    imageBase = Origin & 0xFFFFF000;
  if (imageBase >= 0xFFFFF000)
    errSectTooBig();
  // hdrsz = 4096; // make the first section page-aligned in the file
  hdrsz = 1024; // traditional 1KB size of headers, 1st section isn't page-aligned in file
  Origin = imageBase + 4096;

  PeOptionalHeader.SizeOfHeaders = hdrsz;

  Pass(0, NULL, hdrsz);

    {
      uint32 hsz = sizeof DosMzExeStub +
                   sizeof "PE\0" +
                   sizeof PeFileHeader +
                   sizeof PeOptionalHeader +
                   sizeof(tPeImageSectionHeader) * 5/*.text,.rdata,.idata,.data,.reloc*/;
      uint32 start, stop;

      PeFileHeader.NumberOfSections =
        1 + !!roDataSectCnt + !!impDataSectCnt + (dataSectCnt || bssSectCnt);

      PeOptionalHeader.ImageBase = imageBase;
      PeOptionalHeader.AddressOfEntryPoint = FindSymbolAddress(EntryPoint) - imageBase;

      start = pSectDescrs[SectCnt].Start & 0xFFFFF000;
      stop = (pSectDescrs[SectCnt].Stop + 0xFFF) & 0xFFFFF000;
      PeOptionalHeader.BaseOfCode =
        PeSectionHeaderText.VirtualAddress =
          start - imageBase;
      PeSectionHeaderText.PointerToRawData =
        hdrsz;
      PeSectionHeaderText.Misc.VirtualSize = PeSectionHeaderText.SizeOfRawData =
        PeOptionalHeader.SizeOfCode = stop - start;

      if (hasData)
      {
        start = pSectDescrs[SectCnt + 1].Start & 0xFFFFF000;
        stop = (pSectDescrs[SectCnt + 1].Stop + 0xFFF) & 0xFFFFF000;

        PeOptionalHeader.BaseOfData =
          PeSectionHeaderData.VirtualAddress =
            start - imageBase;
        PeSectionHeaderData.PointerToRawData =
          PeSectionHeaderText.PointerToRawData + PeSectionHeaderText.SizeOfRawData;
        PeSectionHeaderData.Misc.VirtualSize =
          PeOptionalHeader.SizeOfInitializedData = stop - start;

        if ((pSectDescrs[SectCnt - 1].Attrs & SHT_NOBITS) && UseBss)
        {
          uint32 i = SectCnt - 1;
          while (pSectDescrs[i].Attrs & SHT_NOBITS)
            i--;
          PeSectionHeaderData.SizeOfRawData = ((pSectDescrs[i].Stop + 0xFFF) & 0xFFFFF000) - start;
        }
        else
        {
          PeSectionHeaderData.SizeOfRawData = stop - start;
        }

        // Carve out .rodata into its own section
        if (roDataSectCnt)
        {
          PeSectionHeaderRoData.Misc.VirtualSize =
            ((pSectDescrs[textSectCnt + roDataSectCnt - 1].Stop + 0xFFF) & 0xFFFFF000) - start;
          PeSectionHeaderData.Misc.VirtualSize -=
            PeSectionHeaderRoData.Misc.VirtualSize;

          PeSectionHeaderRoData.VirtualAddress =
            PeSectionHeaderData.VirtualAddress;
          PeSectionHeaderData.VirtualAddress +=
            PeSectionHeaderRoData.Misc.VirtualSize;

          PeSectionHeaderRoData.SizeOfRawData =
            PeSectionHeaderRoData.Misc.VirtualSize;
          PeSectionHeaderData.SizeOfRawData -=
            PeSectionHeaderRoData.SizeOfRawData;

          PeSectionHeaderRoData.PointerToRawData =
            PeSectionHeaderData.PointerToRawData;
          PeSectionHeaderData.PointerToRawData +=
            PeSectionHeaderRoData.SizeOfRawData;
        }

        // Carve out .dll_* into the .idata section
        if (impDataSectCnt)
        {
          PeSectionHeaderImpData.Misc.VirtualSize =
            ((pSectDescrs[textSectCnt + roDataSectCnt + impDataSectCnt - 1].Stop + 0xFFF) & 0xFFFFF000) -
            pSectDescrs[textSectCnt + roDataSectCnt].Start & 0xFFFFF000;
          PeSectionHeaderData.Misc.VirtualSize -=
            PeSectionHeaderImpData.Misc.VirtualSize;

          PeSectionHeaderImpData.VirtualAddress =
            PeSectionHeaderData.VirtualAddress;
          PeSectionHeaderData.VirtualAddress +=
            PeSectionHeaderImpData.Misc.VirtualSize;

          PeSectionHeaderImpData.SizeOfRawData =
            PeSectionHeaderImpData.Misc.VirtualSize;
          PeSectionHeaderData.SizeOfRawData -=
            PeSectionHeaderImpData.SizeOfRawData;

          PeSectionHeaderImpData.PointerToRawData =
            PeSectionHeaderData.PointerToRawData;
          PeSectionHeaderData.PointerToRawData +=
            PeSectionHeaderImpData.SizeOfRawData;
        }
      }

      PeOptionalHeader.SizeOfImage = stop - imageBase;

      peImportsStart = FindSymbolAddress("__dll_imports");
      if (peImportsStart)
      {
        uint32 peImportsStop = FindSymbolAddress("__dll_imports_end");
        uint32 peIatsStart = FindSymbolAddress("__dll_iats");
        PeOptionalHeader.DataDirectory[1].VirtualAddress = peImportsStart - imageBase;
        if (peImportsStop)
          PeOptionalHeader.DataDirectory[1].Size = peImportsStop - peImportsStart;
        if (peIatsStart)
        {
          uint32 peIatsStop = FindSymbolAddress("__dll_iats_end");
          PeOptionalHeader.DataDirectory[12].VirtualAddress = peIatsStart - imageBase;
          if (peIatsStop)
            PeOptionalHeader.DataDirectory[12].Size = peIatsStop - peIatsStart;
        }
      }

      Fwrite(DosMzExeStub, sizeof DosMzExeStub, fout);
      Fwrite("PE\0", sizeof "PE\0", fout);
      Fwrite(&PeFileHeader, sizeof PeFileHeader, fout);
      Fwrite(&PeOptionalHeader, sizeof PeOptionalHeader, fout);
      Fwrite(&PeSectionHeaderText, sizeof PeSectionHeaderText, fout);
      if (roDataSectCnt)
        Fwrite(&PeSectionHeaderRoData, sizeof PeSectionHeaderRoData, fout);
      if (impDataSectCnt)
        Fwrite(&PeSectionHeaderImpData, sizeof PeSectionHeaderImpData, fout);
      if (dataSectCnt || bssSectCnt)
        Fwrite(&PeSectionHeaderData, sizeof PeSectionHeaderData, fout);
      if (!roDataSectCnt)
        Fwrite(&PeSectionHeaderZero, sizeof PeSectionHeaderZero, fout);
      if (!impDataSectCnt)
        Fwrite(&PeSectionHeaderZero, sizeof PeSectionHeaderZero, fout);
      if (!(dataSectCnt || bssSectCnt))
        Fwrite(&PeSectionHeaderZero, sizeof PeSectionHeaderZero, fout);
      Fwrite(&PeSectionHeaderZero, sizeof PeSectionHeaderZero, fout);
      FillWithByte(0, hdrsz - hsz, fout);
    }

  Pass(1, fout, hdrsz);

  {
    uint32 pos = ftell(fout); // TBD!!! clean up
    // In PE, some importing-related addresses must be relative to the image base, so make them relative
    if (peImportsStart)
    {
      uint32 iofs;
      for (iofs = peImportsStart; ; iofs += sizeof(tPeImageImportDescriptor))
      {
        tPeImageImportDescriptor id;
        uint32 ofs, v;

        Fseek(fout, iofs - Origin + hdrsz, SEEK_SET);
        Fread(&id, sizeof id, fout);
        if (!id.u.OrdinalFirstThunk || !id.Name || !id.FirstThunk)
          break;
        id.u.OrdinalFirstThunk -= imageBase;
        id.Name -= imageBase;
        id.FirstThunk -= imageBase;
        Fseek(fout, iofs - Origin + hdrsz, SEEK_SET);
        Fwrite(&id, sizeof id, fout);

        for (ofs = id.u.OrdinalFirstThunk; ; ofs += sizeof v)
        {
          Fseek(fout, ofs - 4096 + hdrsz, SEEK_SET);
          Fread(&v, sizeof v, fout);
          if (!v)
            break;
          v -= imageBase;
          Fseek(fout, ofs - 4096 + hdrsz, SEEK_SET);
          Fwrite(&v, sizeof v, fout);
        }

        for (ofs = id.FirstThunk; ; ofs += sizeof v)
        {
          Fseek(fout, ofs - 4096 + hdrsz, SEEK_SET);
          Fread(&v, sizeof v, fout);
          if (!v)
            break;
          v -= imageBase;
          Fseek(fout, ofs - 4096 + hdrsz, SEEK_SET);
          Fwrite(&v, sizeof v, fout);
        }
      }
    }
    // Write relocation table
    if (!NoRelocations)
    {
      uint32 j, fIdx, sectIdx, relSectIdx, relIdx;
      uint32 lastPage = 0xFFFFFFFF, page = 0xFFFFFFFF, blockSize = 0;
      uint32 totalFixupsSize = 0, blockPos = pos;
      Fseek(fout, pos, SEEK_SET);
      // Handle individual sections
      for (j = 0; j < SectCnt; j++)
      {
        for (fIdx = 0; fIdx < ObjFileCnt; fIdx++)
        {
          tElfMeta* pMeta = &pMetas[fIdx];
          if (!pMeta->Needed)
            continue;
          for (sectIdx = 0; sectIdx < pMeta->SectionCnt; sectIdx++)
          {
            tElfSection* pSect = &pMeta->pSections[sectIdx];
            tElfSection* pRelSect = NULL;
            const char* sectName;
            size_t sectNameLen;
            if (pSect->h.sh_type != SHT_PROGBITS)
              continue;
            if (strcmp(pSectDescrs[j].pName, pMeta->pSectNames + pSect->h.sh_name))
              continue;
            // Find relocations for this section, if any
            for (relSectIdx = 0; relSectIdx < pMeta->SectionCnt; relSectIdx++)
            {
              if (pMeta->pSections[relSectIdx].h.sh_type == SHT_REL &&
                  pMeta->pSections[relSectIdx].h.sh_info == sectIdx)
              {
                pRelSect = &pMeta->pSections[relSectIdx];
                break;
              }
            }
            if (!pRelSect)
              continue;

            // Don't create relocations for anything in sections whose names
            // start with ".dll_import" or ".dll_iat".
            sectName = pSectDescrs[j].pName;
            sectNameLen = strlen(sectName);
            if (!strncmp(sectName, ".dll_import", sizeof ".dll_import" - 1) ||
                !strncmp(sectName, ".dll_iat", sizeof ".dll_iat" - 1))
              continue;

            // Write relocation records
            for (relIdx = 0; relIdx < pRelSect->h.sh_entsize; relIdx++)
            {
              Elf32_Rel* pRel = &pRelSect->d.pRel[relIdx];
              uint32 symIdx = pRel->r_info >> 8;
              uint32 absSym = symIdx == 0;
              uint32 relType = pRel->r_info & 0xFFu;
              uint32 relative = relType == R_386_PC16 || relType == R_386_PC32;
              uint32 length = (relType == R_386_32 || relType == R_386_PC32) * 2 +
                              (relType == R_386_16 || relType == R_386_PC16);
              uint32 addr;
              uint16 typeOffs;

              if (absSym)
                error("Unsupported relocation type in PE\n");
              if (relative)
                continue;
              if (length != 2)
                error("Unsupported relocation size in PE\n");

              addr = pRel->r_offset + pMeta->pSections[pRelSect->h.sh_info].OutOffset -
                imageBase;

              page = addr >> 12;
              if (page != lastPage)
              {
                // finish off fixups for the last page, if any
                if (blockSize)
                {
                  if (blockSize & 2)
                  {
                    // pad to 4 bytes
                    typeOffs = 0;
                    Fwrite(&typeOffs, sizeof typeOffs, fout);
                    blockSize += sizeof(typeOffs);
                  }
                  // update block header
                  blockSize += sizeof lastPage + sizeof blockSize;
                  totalFixupsSize += blockSize;
                  // update the filler
                  Fseek(fout, blockPos, SEEK_SET);
                  blockPos += blockSize;
                  lastPage <<= 12;
                  Fwrite(&lastPage, sizeof lastPage, fout);
                  Fwrite(&blockSize, sizeof blockSize, fout);
                  Fseek(fout, blockPos, SEEK_SET);
                }
                // fixups for a new (or first) page
                lastPage = page;
                blockSize = 0;
                // filler for page's RVA and block size
                Fwrite(&lastPage, sizeof lastPage, fout);
                Fwrite(&blockSize, sizeof blockSize, fout);
              }

              typeOffs = (addr & 0xFFF) | (3 << 12);
              Fwrite(&typeOffs, sizeof typeOffs, fout);
              blockSize += sizeof(typeOffs);
            }
          } // endof: for (sectIdx = 0; sectIdx < pMeta->SectionCnt; sectIdx++)
        } // endof: for (fIdx = 0; fIdx < ObjFileCnt; fIdx++)
      } // endof: for (j = 0; j < SectCnt; j++)
      // finish off fixups for the last page, if any
      if (blockSize)
      {
        if (blockSize & 2)
        {
          // pad to 4 bytes
          uint16 typeOffs = 0;
          Fwrite(&typeOffs, sizeof typeOffs, fout);
          blockSize += sizeof(typeOffs);
        }
        // update block header
        blockSize += sizeof lastPage + sizeof blockSize;
        totalFixupsSize += blockSize;
        // update the filler
        Fseek(fout, blockPos, SEEK_SET);
        blockPos += blockSize;
        lastPage <<= 12;
        Fwrite(&lastPage, sizeof lastPage, fout);
        Fwrite(&blockSize, sizeof blockSize, fout);
        Fseek(fout, blockPos, SEEK_SET);
      }
      // if there's nothing to relocate, write a dummy fixup block
      if (!totalFixupsSize)
      {
        static uint32 tmp[3];
        tmp[1] = sizeof tmp;
        Fwrite(tmp, sizeof tmp, fout);
        totalFixupsSize = sizeof tmp;
        blockPos += totalFixupsSize;
      }
      // pad fixup blocks to PeOptionalHeader.FileAlignment (512)
      FillWithByte(0, (512 - totalFixupsSize) & 511, fout);
      // update headers
      {
        uint32 pos = sizeof DosMzExeStub + sizeof "PE\0";
        uint32 idx = PeFileHeader.NumberOfSections++;
        tPeImageSectionHeader* lastHdr =
          (dataSectCnt || bssSectCnt) ? &PeSectionHeaderData :
          (impDataSectCnt ? &PeSectionHeaderImpData :
           (roDataSectCnt ? &PeSectionHeaderRoData : &PeSectionHeaderText));

        PeFileHeader.Characteristics &= ~1; // reset no relocations
        // TBD??? PeFileHeader.Characteristics |= 0x20; // large address aware

        PeOptionalHeader.DllCharacteristics |= 0x40; // ASLR / dynamic base

        // ".reloc"
        PeOptionalHeader.DataDirectory[5].VirtualAddress =
          PeSectionHeaderReloc.VirtualAddress =
            lastHdr->VirtualAddress +
              lastHdr->Misc.VirtualSize;
        PeSectionHeaderReloc.PointerToRawData = blockPos - totalFixupsSize;
        PeOptionalHeader.DataDirectory[5].Size = totalFixupsSize;
        PeSectionHeaderReloc.Misc.VirtualSize =
          PeSectionHeaderReloc.SizeOfRawData =
            (totalFixupsSize + 0x1FF) & 0xFFFFFE00;

        PeOptionalHeader.SizeOfImage += PeSectionHeaderReloc.Misc.VirtualSize;
        PeOptionalHeader.SizeOfImage = (PeOptionalHeader.SizeOfImage + 0xFFF) & 0xFFFFF000;
        PeOptionalHeader.SizeOfInitializedData += PeSectionHeaderReloc.Misc.VirtualSize;

        Fseek(fout, pos, SEEK_SET);
        Fwrite(&PeFileHeader, sizeof PeFileHeader, fout);

        pos += sizeof PeFileHeader;
        Fseek(fout, pos, SEEK_SET);
        Fwrite(&PeOptionalHeader, sizeof PeOptionalHeader, fout);

        pos += sizeof PeOptionalHeader + idx * sizeof(tPeImageSectionHeader);
        Fseek(fout, pos, SEEK_SET);
        Fwrite(&PeSectionHeaderReloc, sizeof PeSectionHeaderReloc, fout);
      }
    }
  }

  Fclose(fout);
}

void RwElf(void)
{
  int hasData = !(pSectDescrs[SectCnt - 1].Attrs & SHF_EXECINSTR); // non-executable/data sections, if any, are last
  FILE* fout = Fopen(OutName, "wb+");
  uint32 hdrsz = 0;
  uint32 imageBase = 0;

  // Figure out:
  // - header sizes
  // - start offsets/base addresses
  // - stack size and location
  if (Origin == 0xFFFFFFFF)
    imageBase = 0x08048000; // default image base if origin is unspecified
  else
    imageBase = Origin & 0xFFFFF000;
  if (imageBase >= 0xFFFFF000)
    errSectTooBig();
  hdrsz = 4096; // make the first section page-aligned
  Origin = imageBase + hdrsz;

  Pass(0, NULL, hdrsz);

    {
      uint32 hsz = sizeof ElfHeader +
                   sizeof ElfProgramHeaders;
      uint32 start, stop;

      ElfHeader.e_phnum = 1 + hasData;

      ElfHeader.e_entry = FindSymbolAddress(EntryPoint);

      start = pSectDescrs[SectCnt].Start & 0xFFFFF000;
      stop = (pSectDescrs[SectCnt].Stop + 0xFFF) & 0xFFFFF000;
      ElfProgramHeaders[0].p_offset = start - imageBase;
      ElfProgramHeaders[0].p_vaddr = ElfProgramHeaders[0].p_paddr = start;
      ElfProgramHeaders[0].p_filesz = ElfProgramHeaders[0].p_memsz = stop - start;

      if (hasData)
      {
        start = pSectDescrs[SectCnt + 1].Start & 0xFFFFF000;
        stop = (pSectDescrs[SectCnt + 1].Stop + 0xFFF) & 0xFFFFF000;
        ElfProgramHeaders[1].p_offset = start - imageBase;
        ElfProgramHeaders[1].p_vaddr = ElfProgramHeaders[1].p_paddr = start;
        ElfProgramHeaders[1].p_memsz = stop - start;

        if ((pSectDescrs[SectCnt - 1].Attrs & SHT_NOBITS) && UseBss)
        {
          uint32 i = SectCnt - 1;
          while (pSectDescrs[i].Attrs & SHT_NOBITS)
            i--;
          ElfProgramHeaders[1].p_filesz = ((pSectDescrs[i].Stop + 0xFFF) & 0xFFFFF000) - start;
        }
        else
        {
          ElfProgramHeaders[1].p_filesz = stop - start;
        }
      }
      else
      {
        memset(&ElfProgramHeaders[1], 0, sizeof ElfProgramHeaders[1]);
      }

      Fwrite(&ElfHeader, sizeof ElfHeader, fout);
      Fwrite(ElfProgramHeaders, sizeof ElfProgramHeaders, fout);
      FillWithByte(0, 4096 - hsz, fout);
    }

  Pass(1, fout, hdrsz);

  Fclose(fout);
}

void RelocateAndWriteAllSections(void)
{
  switch (OutputFormat)
  {
  case FormatDosComTiny:
  case FormatFlat16:
  case FormatFlat32:
    RwFlat();
    break;
  case FormatAout:
    RwAout();
    break;
  case FormatDosExeHuge:
  case FormatDosExeUnreal:
    CheckFxnSizes();
    // fallthrough
  case FormatDosExeSmall:
    RwDosExe();
    break;
  case FormatWinPe32:
    RwPe();
    break;
  case FormatElf32:
    RwElf();
    break;
  case FormatMach32:
    RwMach();
    break;
  }
}

void GenerateMap(void)
{
  uint32 j, fIdx, sectIdx, symIdx;
  FILE* f;

  if (!MapName)
    return;

  f = Fopen(MapName, "w");

  fprintf(f, "File Ofs  Sym Addr  Sym\n\n");

  for (j = 0; j < SectCnt; j++)
  {
    fprintf(f, "          %08lX  section %s:\n", (ulong)pSectDescrs[j].Start, pSectDescrs[j].pName);

    for (symIdx = 0; symIdx < DeferredSymCnt; symIdx++)
      if (pDeferredSyms[symIdx].SectIdx == j && !pDeferredSyms[symIdx].IsStop)
      {
        fprintf(f, "          %08lX  %s\n", (ulong)pSectDescrs[j].Start, pDeferredSyms[symIdx].pName);
        break;
      }

    for (fIdx = 0; fIdx < ObjFileCnt; fIdx++)
    {
      tElfMeta* pMeta = &pMetas[fIdx];
      if (!pMeta->Needed)
        continue;
      for (sectIdx = 0; sectIdx < pMeta->SectionCnt; sectIdx++)
      {
        tElfSection* pSect = &pMeta->pSections[sectIdx];
        if (pSect->h.sh_type != SHT_SYMTAB)
          continue;
#ifdef SUPPORT_LOCAL_RELS
        for (symIdx = pSect->h.sh_info; symIdx < pSect->h.sh_entsize; symIdx++)
#else
        for (symIdx = pSect->h.sh_addralign; symIdx < pSect->h.sh_entsize; symIdx++)
#endif
        {
          Elf32_Sym* pSym = &pSect->d.pSym[symIdx];
          // Check exported symbols
          if ((pSym->st_info >> 4) == STB_GLOBAL &&
              pSym->st_shndx &&
              pSym->st_name)
          {
            tElfSection* pSymSect = &pMeta->pSections[pSym->st_shndx];
            uint32 fofs, addr;
            if (strcmp(pSectDescrs[j].pName, pMeta->pSectNames + pSymSect->h.sh_name))
              continue;
            fofs = pSymSect->OutFileOffset + pSym->st_value;
            addr = pSymSect->OutOffset + pSym->st_value;
            fprintf(f, "%08lX  %08lX  %s\n", (ulong)fofs, (ulong)addr, pMeta->pSections[pSect->h.sh_link].d.pStr + pSym->st_name);
          }
        }
      }
    }

    for (symIdx = 0; symIdx < DeferredSymCnt; symIdx++)
      if (pDeferredSyms[symIdx].SectIdx == j && pDeferredSyms[symIdx].IsStop)
      {
        fprintf(f, "          %08lX  %s\n", (ulong)pSectDescrs[j].Stop, pDeferredSyms[symIdx].pName);
        break;
      }

    fprintf(f, "          %08lX\n\n", (ulong)pSectDescrs[j].Stop);
  }

  Fclose(f);
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

  char** oldpp = pp; // used to free memory on memory errors
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
        free(oldpp);
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
              free(oldpp);
              errMem();
            }
            pp[j++] = p;
            p = strtok(NULL, sep);
          }
        }
        else
        {
          fclose(f);
          free(oldpp);
          errMem();
        }
      }
      fclose(f);
    }

  pp[j] = NULL; // there's supposed to be one more NULL pointer argument
  *pargc = j;
  *pargv = pp;
}

#ifdef SHOW_MEM_USAGE
#ifdef _DOS
void freemem(char* s)
{
  void* ap[160+1];
  unsigned i;
  for (i = 0; i < 160; i++)
    if ((ap[i] = malloc(4096)) == NULL)
    {
      printf("smlrl: free mem (%s): %u\n", s, i * 4096);
      ap[i + 1] = NULL;
      break;
    }
  for (i = 0; i < 160; i++)
    if (ap[i])
      free(ap[i]);
    else
      break;
}
#endif
#endif

int main(int argc, char* argv[])
{
  uint32 ui32 = 0x44434241;
  uint16 ui16 = 0x3231;

#ifdef __SMALLER_C__
#ifdef DETERMINE_VA_LIST
  DetermineVaListType();
#endif
#endif

  if (memcmp(&ui32, "ABCD", sizeof ui32) || memcmp(&ui16, "12", sizeof ui16))
    error("Little-endian platform required\n");

#ifdef SHOW_MEM_USAGE
#ifdef _DOS
  freemem("start");
#endif
#endif

  fatargs(&argc, &argv);

  if (argc > 1)
  {
    int i;
    // Check for -verbose before processing other options
    for (i = 1; i < argc; i++)
    {
      if (!strcmp(argv[i], "-verbose"))
      {
        verbose = 1;
        break;
      }
    }

    for (i = 1; i < argc; i++)
    {
      if (!strcmp(argv[i], "-verbose"))
      {
        continue;
      }
      else if (!strcmp(argv[i], "-o"))
      {
        if (i + 1 < argc)
        {
          OutName = argv[++i];
          continue;
        }
      }
      else if (!strcmp(argv[i], "-map"))
      {
        if (i + 1 < argc)
        {
          MapName = argv[++i];
          continue;
        }
      }
      else if (!strcmp(argv[i], "-entry"))
      {
        if (i + 1 < argc)
        {
          EntryPoint = argv[++i];
          continue;
        }
      }
      else if (!strcmp(argv[i], "-origin"))
      {
        if (i + 1 < argc)
        {
          ++i;
          Origin = strtoul(argv[i], NULL, 0);
          continue;
        }
      }
      else if (!strcmp(argv[i], "-stack"))
      {
        if (i + 1 < argc)
        {
          ++i;
          StackSize = strtoul(argv[i], NULL, 0);
          continue;
        }
      }
      else if (!strcmp(argv[i], "-minheap"))
      {
        if (i + 1 < argc)
        {
          ++i;
          MinHeap = strtoul(argv[i], NULL, 0);
          continue;
        }
      }
      else if (!strcmp(argv[i], "-maxheap"))
      {
        if (i + 1 < argc)
        {
          ++i;
          MaxHeap = strtoul(argv[i], NULL, 0);
          continue;
        }
      }
      else if (!strcmp(argv[i], "-nobss"))
      {
        UseBss = 0;
        continue;
      }
      else if (!strcmp(argv[i], "-tiny"))
      {
        OutputFormat = FormatDosComTiny;
        continue;
      }
      else if (!strcmp(argv[i], "-small"))
      {
        OutputFormat = FormatDosExeSmall;
        continue;
      }
      else if (!strcmp(argv[i], "-huge"))
      {
        OutputFormat = FormatDosExeHuge;
        continue;
      }
      else if (!strcmp(argv[i], "-unreal"))
      {
        OutputFormat = FormatDosExeUnreal;
        continue;
      }
      else if (StrAnyOf(argv[i], "-pe\0"
                                 "-win\0"))
      {
        OutputFormat = FormatWinPe32;
        continue;
      }
      else if (!strcmp(argv[i], "-pesubsys")) // primarily for UEFI subsystems
      {
        if (i + 1 < argc)
        {
          ++i;
          PeOptionalHeader.Subsystem = strtoul(argv[i], NULL, 0);
          continue;
        }
      }
      else if (!strcmp(argv[i], "-gui"))
      {
        PeOptionalHeader.Subsystem = 2; // change the default CUI to GUI
        continue;
      }
      else if (!strcmp(argv[i], "-elf"))
      {
        OutputFormat = FormatElf32;
        continue;
      }
      else if (!strcmp(argv[i], "-mach"))
      {
        OutputFormat = FormatMach32;
        continue;
      }
      else if (!strcmp(argv[i], "-norel"))
      {
        NoRelocations = 1;
        continue;
      }
      else if (!strcmp(argv[i], "-flat16"))
      {
        OutputFormat = FormatFlat16;
        continue;
      }
      else if (!strcmp(argv[i], "-flat32"))
      {
        OutputFormat = FormatFlat32;
        continue;
      }
      else if (!strcmp(argv[i], "-aout"))
      {
        OutputFormat = FormatAout;
        continue;
      }
      else if (!strcmp(argv[i], "-stub"))
      {
        if (i + 1 < argc)
        {
          StubName = argv[++i];
          continue;
        }
      }
      else if (argv[i][0] == '-')
      {
        // Unknown option
      }
      else
      {
        loadMeta(argv[i]);
        continue;
      }

      error("Invalid or unsupported command line option\n");
    }

    if (!OutputFormat)
      error("Output format not specified\n"); // TBD??? switch to a default format when done

    FindSymbolByName(EntryPoint);
    FindAllSymbols();
    CheckDuplicates();
    FindAllSections();
    RelocateAndWriteAllSections();
    GenerateMap();
  }
  else
    error("No inputs\n");

#ifdef SHOW_MEM_USAGE
#ifdef _DOS
  freemem("end");
#endif
#endif

  return 0;
}
