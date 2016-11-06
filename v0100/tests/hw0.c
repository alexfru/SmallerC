/*
  How to compile for DOS (tiny/.COM, small/.EXE, huge/.EXE):
    smlrcc -dost -nobss hw0.c -o hw0dt.com
    smlrcc -doss -nobss hw0.c -o hw0ds.exe
    smlrcc -dosh -nobss hw0.c -o hw0dh.exe

  How to compile for Windows:
    smlrcc -win -norel -nobss hw0.c -o hw0w.exe

  How to compile for Linux:
    smlrcc -linux -nobss hw0.c -o hw0l
*/

#ifdef _WINDOWS
typedef unsigned uint32;

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

static char hint_ExitProcess[] = "\0\0ExitProcess";
static char hint_GetStdHandle[] = "\0\0GetStdHandle";
static char hint_WriteFile[] = "\0\0WriteFile";

static void* hints[] =
{
  hint_ExitProcess,
  hint_GetStdHandle,
  hint_WriteFile,
  0
};

static void* iat[] =
{
  hint_ExitProcess,
  hint_GetStdHandle,
  hint_WriteFile,
  0
};

tPeImageImportDescriptor _dll_imports[] =
{
  {
    { hints },
    0,
    0,
    "kernel32.dll",
    iat
  },
  {
    { 0 }
  }
};

void ExitProcess(unsigned ExitCode)
{
  asm("push dword [ebp+8]\n"
      "call [_iat + 4*0]");
}

unsigned GetStdHandle(unsigned nStdHandle)
{
  asm("push dword [ebp+8]\n"
      "call [_iat + 4*1]");
}

int WriteFile(unsigned Handle,
              void* Buffer,
              unsigned NumberOfBytesToWrite,
              unsigned* NumberOfBytesWritten,
              void* Overlapped)
{
  asm("push dword [ebp+24]\n"
      "push dword [ebp+20]\n"
      "push dword [ebp+16]\n"
      "push dword [ebp+12]\n"
      "push dword [ebp+8]\n"
      "call [_iat + 4*2]");
}

#define STD_OUTPUT_HANDLE (-11u)

void _start(void)
{
  char hwmsg[] = "Hello, World!\r\n";
  unsigned h = GetStdHandle(STD_OUTPUT_HANDLE);
  unsigned NumberOfBytesWritten;
  WriteFile(h, hwmsg, sizeof hwmsg - 1, &NumberOfBytesWritten, 0);
  ExitProcess(0);
}
#endif

#ifdef _LINUX
void exit(int e)
{
  asm("mov eax, 1\n"
      "mov ebx, [ebp + 8]\n"
      "int 0x80");
}

int write(int fd, void* p, unsigned s)
{
  asm("mov eax, 4\n" // sys_write
      "mov ebx, [ebp + 8]\n"
      "mov ecx, [ebp + 12]\n"
      "mov edx, [ebp + 16]\n"
      "int 0x80");
}

void _start(void)
{
  char hwmsg[] = "Hello, World!\r\n";
  write(1, hwmsg, sizeof hwmsg - 1);
  exit(0);
}
#endif

#ifdef _DOS
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

int write(int fd, void* p, unsigned s)
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

void __start__(void);

#ifdef __SMALLER_C_16__
void _start(void)
{
  // DS and ES must be explicitly initialized in DOS .EXEs in the small memory model
  // (.COM/tiny and .EXE/huge don't need that)
  asm("push ss");
  asm("push ss");
  asm("pop ds");
  asm("pop es");
  __start__();
}
#else
void _start(void)
{
  // perform code/data relocations

  asm("extern __start__relot");
  asm("extern __stop__relot");
  asm("extern __start__relod");
  asm("extern __stop__relod");

  asm("call    labnext");
asm("labnext:");
  asm("xor     ebx, ebx");
  asm("mov     bx, cs");
  asm("shl     ebx, 4");
  asm("xor     eax, eax");
  asm("pop     ax");
  asm("add     ebx, eax");
  asm("sub     ebx, labnext"); // ebx = base physical address

  asm("mov     esi, __start__relot");
asm("relo_text_loop:");
  asm("cmp     esi, __stop__relot");
  asm("jae     relo_text_done");

  asm("lea     edi, [ebx + esi]"); // edi = physical address of a relocation table element

  asm("ror     edi, 4");
  asm("mov     ds, di");
  asm("shr     edi, 28");

  asm("mov     edi, [di]");
  asm("add     edi, ebx"); // edi = physical address of a dword to which to add ebx and which then to transform into seg:ofs far pointer

  asm("ror     edi, 4");
  asm("mov     ds, di");
  asm("shr     edi, 28");

  asm("mov     eax, [di]");
  asm("add     eax, ebx");

  asm("shl     eax, 12");
  asm("rol     ax, 4");

  asm("mov     [di], eax");

  asm("add     esi, 4");
  asm("jmp     relo_text_loop");
asm("relo_text_done:");

  asm("mov     esi, __start__relod");
asm("relo_data_loop:");
  asm("cmp     esi, __stop__relod");
  asm("jae     relo_data_done");

  asm("lea     edi, [ebx + esi]"); // edi = physical address of a relocation table element

  asm("ror     edi, 4");
  asm("mov     ds, di");
  asm("shr     edi, 28");

  asm("mov     edi, [di]");
  asm("add     edi, ebx"); // edi = physical address of a dword to which to add ebx

  asm("ror     edi, 4");
  asm("mov     ds, di");
  asm("shr     edi, 28");

  asm("add     [di], ebx"); // actual relocation

  asm("add     esi, 4");
  asm("jmp     relo_data_loop");
asm("relo_data_done:");

  __start__();
}
#endif

void __start__(void)
{
  char hwmsg[] = "Hello, World!\r\n";
  write(1, hwmsg, sizeof hwmsg - 1);
  exit(0);
}
#endif
