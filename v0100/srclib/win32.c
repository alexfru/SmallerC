/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _WINDOWS

#include "iwin32.h"

typedef struct
{
  union
  {
    unsigned Characteristics;
    unsigned OrdinalFirstThunk;
  } u;
  unsigned TimeDateStamp;
  unsigned ForwarderChain;
  unsigned Name;
  unsigned FirstThunk;
} tPeImageImportDescriptor;

static char h_ExitProcess            [] = "\0\0ExitProcess";
static char h_GetCommandLineA        [] = "\0\0GetCommandLineA";
static char h_GetStdHandle           [] = "\0\0GetStdHandle";
static char h_GetFileType            [] = "\0\0GetFileType";
static char h_CloseHandle            [] = "\0\0CloseHandle";
static char h_GetLastError           [] = "\0\0GetLastError";
static char h_SetLastError           [] = "\0\0SetLastError";
static char h_GetProcessHeap         [] = "\0\0GetProcessHeap";
static char h_HeapAlloc              [] = "\0\0HeapAlloc";
static char h_HeapFree               [] = "\0\0HeapFree";
static char h_HeapReAlloc            [] = "\0\0HeapReAlloc";
static char h_CreateFileA            [] = "\0\0CreateFileA";
static char h_DeleteFileA            [] = "\0\0DeleteFileA";
static char h_MoveFileA              [] = "\0\0MoveFileA";
static char h_ReadFile               [] = "\0\0ReadFile";
static char h_WriteFile              [] = "\0\0WriteFile";
static char h_SetFilePointer         [] = "\0\0SetFilePointer";
static char h_GetFileAttributesA     [] = "\0\0GetFileAttributesA";
static char h_GetEnvironmentVariableA[] = "\0\0GetEnvironmentVariableA";
static char h_GetTickCount           [] = "\0\0GetTickCount";
static char h_GetSystemTime          [] = "\0\0GetSystemTime";
static char h_SystemTimeToTzSpecificLocalTime[] = "\0\0SystemTimeToTzSpecificLocalTime";
static char h_TzSpecificLocalTimeToSystemTime[] = "\0\0TzSpecificLocalTimeToSystemTime";
static char h_CreateProcessA         [] = "\0\0CreateProcessA";
static char h_GetExitCodeProcess     [] = "\0\0GetExitCodeProcess";
static char h_WaitForSingleObject    [] = "\0\0WaitForSingleObject";
static char h_SetUnhandledExceptionFilter    [] = "\0\0SetUnhandledExceptionFilter";

static void* hints[] =
{
  h_ExitProcess,
  h_GetCommandLineA,
  h_GetStdHandle,
  h_GetFileType,
  h_CloseHandle,
  h_GetLastError,
  h_SetLastError,
  h_GetProcessHeap,
  h_HeapAlloc,
  h_HeapFree,
  h_HeapReAlloc,
  h_CreateFileA,
  h_DeleteFileA,
  h_MoveFileA,
  h_ReadFile,
  h_WriteFile,
  h_SetFilePointer,
  h_GetFileAttributesA,
  h_GetEnvironmentVariableA,
  h_GetTickCount,
  h_GetSystemTime,
  h_SystemTimeToTzSpecificLocalTime,
  h_TzSpecificLocalTimeToSystemTime,
  h_CreateProcessA,
  h_GetExitCodeProcess,
  h_WaitForSingleObject,
  h_SetUnhandledExceptionFilter,
  0
};

static void* iat[] =
{
  h_ExitProcess,
  h_GetCommandLineA,
  h_GetStdHandle,
  h_GetFileType,
  h_CloseHandle,
  h_GetLastError,
  h_SetLastError,
  h_GetProcessHeap,
  h_HeapAlloc,
  h_HeapFree,
  h_HeapReAlloc,
  h_CreateFileA,
  h_DeleteFileA,
  h_MoveFileA,
  h_ReadFile,
  h_WriteFile,
  h_SetFilePointer,
  h_GetFileAttributesA,
  h_GetEnvironmentVariableA,
  h_GetTickCount,
  h_GetSystemTime,
  h_SystemTimeToTzSpecificLocalTime,
  h_TzSpecificLocalTimeToSystemTime,
  h_CreateProcessA,
  h_GetExitCodeProcess,
  h_WaitForSingleObject,
  h_SetUnhandledExceptionFilter,
  0
};

// TBD??? Place these function wrappers into separate files and
// import only those functions from the system DLLs that are needed.
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

char* GetCommandLineA(void)
{
  asm("call [_iat + 4*1]");
}

unsigned GetStdHandle(unsigned nStdHandle)
{
  asm("push dword [ebp+8]\n"
      "call [_iat + 4*2]");
}

unsigned GetFileType(unsigned Handle)
{
  asm("push dword [ebp+8]\n"
      "call [_iat + 4*3]");
}

int CloseHandle(unsigned Handle)
{
  asm("push dword [ebp+8]\n"
      "call [_iat + 4*4]");
}

unsigned GetLastError(void)
{
  asm("call [_iat + 4*5]");
}

void SetLastError(unsigned Error)
{
  asm("push dword [ebp+8]\n"
      "call [_iat + 4*6]");
}

unsigned GetProcessHeap(void)
{
  asm("call [_iat + 4*7]");
}

void* HeapAlloc(unsigned hHeap,
                unsigned dwFlags,
                unsigned dwBytes)
{
  asm("push dword [ebp+16]\n"
      "push dword [ebp+12]\n"
      "push dword [ebp+8]\n"
      "call [_iat + 4*8]");
}

int HeapFree(unsigned hHeap,
             unsigned dwFlags,
             void* lpMem)
{
  asm("push dword [ebp+16]\n"
      "push dword [ebp+12]\n"
      "push dword [ebp+8]\n"
      "call [_iat + 4*9]");
}

void* HeapReAlloc(unsigned hHeap,
                  unsigned dwFlags,
                  void* lpMem,
                  unsigned dwBytes)
{
  asm("push dword [ebp+20]\n"
      "push dword [ebp+16]\n"
      "push dword [ebp+12]\n"
      "push dword [ebp+8]\n"
      "call [_iat + 4*10]");
}

unsigned CreateFileA(char* FileName,
                     unsigned DesiredAccess,
                     unsigned ShareMode,
                     void* SecurityAttributes,
                     unsigned CreationDisposition,
                     unsigned FlagsAndAttributes,
                     unsigned TemplateFile)
{
  asm("push dword [ebp+32]\n"
      "push dword [ebp+28]\n"
      "push dword [ebp+24]\n"
      "push dword [ebp+20]\n"
      "push dword [ebp+16]\n"
      "push dword [ebp+12]\n"
      "push dword [ebp+8]\n"
      "call [_iat + 4*11]");
}

int DeleteFileA(char*)
{
  asm("push dword [ebp+8]\n"
      "call [_iat + 4*12]");
}

int MoveFileA(char* lpExistingFileName, char* lpNewFileName)
{
  asm("push dword [ebp+12]\n"
      "push dword [ebp+8]\n"
      "call [_iat + 4*13]");
}

int ReadFile(unsigned Handle,
             void* Buffer,
             unsigned NumberOfBytesToRead,
             unsigned* NumberOfBytesRead,
             void* Overlapped)
{
  asm("push dword [ebp+24]\n"
      "push dword [ebp+20]\n"
      "push dword [ebp+16]\n"
      "push dword [ebp+12]\n"
      "push dword [ebp+8]\n"
      "call [_iat + 4*14]");
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
      "call [_iat + 4*15]");
}

unsigned SetFilePointer(unsigned hFile,
                        int lDistanceToMove,
                        int* lpDistanceToMoveHigh,
                        unsigned dwMoveMethod)
{
  asm("push dword [ebp+20]\n"
      "push dword [ebp+16]\n"
      "push dword [ebp+12]\n"
      "push dword [ebp+8]\n"
      "call [_iat + 4*16]");
}

unsigned GetFileAttributesA(char* lpFileName)
{
  asm("push dword [ebp+8]\n"
      "call [_iat + 4*17]");
}

unsigned GetEnvironmentVariableA(char* lpName,
                                 char* lpBuffer,
                                 unsigned nSize)
{
  asm("push dword [ebp+16]\n"
      "push dword [ebp+12]\n"
      "push dword [ebp+8]\n"
      "call [_iat + 4*18]");
}

unsigned GetTickCount(void)
{
  asm("call [_iat + 4*19]");
}

void GetSystemTime(struct _SYSTEMTIME* pSystemTime)
{
  asm("push dword [ebp+8]\n"
      "call [_iat + 4*20]");
}

int SystemTimeToTzSpecificLocalTime(struct _TIME_ZONE_INFORMATION* lpTimeZoneInformation,
                                    struct _SYSTEMTIME* lpLocalTime,
                                    struct _SYSTEMTIME* lpUniversalTime)
{
  asm("push dword [ebp+16]\n"
      "push dword [ebp+12]\n"
      "push dword [ebp+8]\n"
      "call [_iat + 4*21]");
}

int TzSpecificLocalTimeToSystemTime(struct _TIME_ZONE_INFORMATION* lpTimeZoneInformation,
                                    struct _SYSTEMTIME* lpLocalTime,
                                    struct _SYSTEMTIME* lpUniversalTime)
{
  asm("push dword [ebp+16]\n"
      "push dword [ebp+12]\n"
      "push dword [ebp+8]\n"
      "call [_iat + 4*22]");
}

int CreateProcessA(char* lpApplicationName,
                   char* lpCommandLine,
                   struct _SECURITY_ATTRIBUTES* lpProcessAttributes,
                   struct _SECURITY_ATTRIBUTES* lpThreadAttributes,
                   int bInheritHandles,
                   unsigned dwCreationFlags,
                   void* lpEnvironment,
                   char* lpCurrentDirectory,
                   struct _STARTUPINFO* lpStartupInfo,
                   struct _PROCESS_INFORMATION* lpProcessInformation)
{
  asm("push dword [ebp+44]\n"
      "push dword [ebp+40]\n"
      "push dword [ebp+36]\n"
      "push dword [ebp+32]\n"
      "push dword [ebp+28]\n"
      "push dword [ebp+24]\n"
      "push dword [ebp+20]\n"
      "push dword [ebp+16]\n"
      "push dword [ebp+12]\n"
      "push dword [ebp+8]\n"
      "call [_iat + 4*23]");
}

int GetExitCodeProcess(unsigned hProcess, unsigned* lpExitCode)
{
  asm("push dword [ebp+12]\n"
      "push dword [ebp+8]\n"
      "call [_iat + 4*24]");
}

unsigned WaitForSingleObject(unsigned hHandle, unsigned dwMilliseconds)
{
  asm("push dword [ebp+12]\n"
      "push dword [ebp+8]\n"
      "call [_iat + 4*25]");
}

TOP_LEVEL_EXCEPTION_FILTER* SetUnhandledExceptionFilter(TOP_LEVEL_EXCEPTION_FILTER* lpTopLevelExceptionFilter)
{
  asm("push dword [ebp+8]\n"
      "call [_iat + 4*26]");
}

#endif // _WINDOWS
