/*
  Copyright (c) 2014-2018, Alexey Frunze
  2-clause BSD license.
*/
#ifndef __IWIN32_H
#define __IWIN32_H

#define STD_INPUT_HANDLE  (-10u)
#define STD_OUTPUT_HANDLE (-11u)
#define STD_ERROR_HANDLE  (-12u)

#define INVALID_HANDLE_VALUE     (-1)
#define INVALID_SET_FILE_POINTER 0xFFFFFFFFL
#define INVALID_FILE_ATTRIBUTES  0xFFFFFFFF

#define GENERIC_WRITE            0x40000000u
#define GENERIC_READ             0x80000000u
#define FILE_SHARE_READ          1
#define CREATE_NEW               1
#define CREATE_ALWAYS            2
#define OPEN_EXISTING            3
#define OPEN_ALWAYS              4
#define TRUNCATE_EXISTING        5
#define FILE_ATTRIBUTE_READONLY  0x01
#define FILE_ATTRIBUTE_DIRECTORY 0x10
#define FILE_ATTRIBUTE_NORMAL    0x80

#define FILE_TYPE_CHAR        2

#define INFINITE              0xFFFFFFFF

#define EXCEPTION_CONTINUE_SEARCH     0x0
#define EXCEPTION_EXECUTE_HANDLER     0x1
#define EXCEPTION_CONTINUE_EXECUTION  0xFFFFFFFF

#define ERROR_FILE_NOT_FOUND  2

typedef struct _SYSTEMTIME
{
  unsigned short wYear;
  unsigned short wMonth;
  unsigned short wDayOfWeek;
  unsigned short wDay;
  unsigned short wHour;
  unsigned short wMinute;
  unsigned short wSecond;
  unsigned short wMilliseconds;
} SYSTEMTIME;

struct _TIME_ZONE_INFORMATION;
struct _SECURITY_ATTRIBUTES;

typedef struct _STARTUPINFO
{
  unsigned       cb;
  char*          lpReserved;
  char*          lpDesktop;
  char*          lpTitle;
  unsigned       dwX;
  unsigned       dwY;
  unsigned       dwXSize;
  unsigned       dwYSize;
  unsigned       dwXCountChars;
  unsigned       dwYCountChars;
  unsigned       dwFillAttribute;
  unsigned       dwFlags;
  unsigned short wShowWindow;
  unsigned short cbReserved2;
  void*          lpReserved2;
  unsigned       hStdInput;
  unsigned       hStdOutput;
  unsigned       hStdError;
} STARTUPINFO;

typedef struct _PROCESS_INFORMATION
{
  unsigned hProcess;
  unsigned hThread;
  unsigned dwProcessId;
  unsigned dwThreadId;
} PROCESS_INFORMATION;

struct _EXCEPTION_POINTERS;
typedef int (*TOP_LEVEL_EXCEPTION_FILTER)(struct _EXCEPTION_POINTERS*);

void __ExitProcess(unsigned);

char* __GetCommandLineA(void);

unsigned __GetStdHandle(unsigned);
unsigned __GetFileType(unsigned);

int __CloseHandle(unsigned);

unsigned __GetLastError(void);
void __SetLastError(unsigned);

unsigned __GetProcessHeap(void);
void* __HeapAlloc(unsigned,
                  unsigned,
                  unsigned);
int __HeapFree(unsigned,
               unsigned,
               void*);
void* __HeapReAlloc(unsigned,
                    unsigned,
                    void*,
                    unsigned);

unsigned __CreateFileA(char*,
                       unsigned,
                       unsigned,
                       void*,
                       unsigned,
                       unsigned,
                       unsigned);
int __DeleteFileA(char*);
int __MoveFileA(char*, char*);

int __ReadFile(unsigned,
               void*,
               unsigned,
               unsigned*,
               void*);
int __WriteFile(unsigned,
                void*,
                unsigned,
                unsigned*,
                void*);

unsigned __SetFilePointer(unsigned,
                          int,
                          int*,
                          unsigned);

unsigned __GetFileAttributesA(char*);

unsigned __GetEnvironmentVariableA(char*,
                                   char*,
                                   unsigned);

unsigned __GetTickCount(void);
void __GetSystemTime(struct _SYSTEMTIME*);
int __SystemTimeToTzSpecificLocalTime(struct _TIME_ZONE_INFORMATION*,
                                      struct _SYSTEMTIME*,
                                      struct _SYSTEMTIME*);
int __TzSpecificLocalTimeToSystemTime(struct _TIME_ZONE_INFORMATION*,
                                      struct _SYSTEMTIME*,
                                      struct _SYSTEMTIME*);

int __CreateProcessA(char*,
                     char*,
                     struct _SECURITY_ATTRIBUTES*,
                     struct _SECURITY_ATTRIBUTES*,
                     int,
                     unsigned,
                     void*,
                     char*,
                     struct _STARTUPINFO*,
                     struct _PROCESS_INFORMATION*);
int __GetExitCodeProcess(unsigned, unsigned*);

unsigned __WaitForSingleObject(unsigned, unsigned);

TOP_LEVEL_EXCEPTION_FILTER* __SetUnhandledExceptionFilter(TOP_LEVEL_EXCEPTION_FILTER*);

void* __LoadLibraryExA(char*, unsigned, unsigned);
int __FreeLibrary(void*);
void (*__GetProcAddress(void*, char*))();

#endif
