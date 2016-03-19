/*
  Copyright (c) 2014-2016, Alexey Frunze
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

void ExitProcess(unsigned);

char* GetCommandLineA(void);

unsigned GetStdHandle(unsigned);
unsigned GetFileType(unsigned);

int CloseHandle(unsigned);

unsigned GetLastError(void);
void SetLastError(unsigned);

unsigned GetProcessHeap(void);
void* HeapAlloc(unsigned,
                unsigned,
                unsigned);
int HeapFree(unsigned,
             unsigned,
             void*);
void* HeapReAlloc(unsigned,
                  unsigned,
                  void*,
                  unsigned);

unsigned CreateFileA(char*,
                     unsigned,
                     unsigned,
                     void*,
                     unsigned,
                     unsigned,
                     unsigned);
int DeleteFileA(char*);
int MoveFileA(char*, char*);

int ReadFile(unsigned,
             void*,
             unsigned,
             unsigned*,
             void*);
int WriteFile(unsigned,
              void*,
              unsigned,
              unsigned*,
              void*);

unsigned SetFilePointer(unsigned,
                        int,
                        int*,
                        unsigned);

unsigned GetFileAttributesA(char*);

unsigned GetEnvironmentVariableA(char*,
                                 char*,
                                 unsigned);

unsigned GetTickCount(void);
void GetSystemTime(struct _SYSTEMTIME*);
int SystemTimeToTzSpecificLocalTime(struct _TIME_ZONE_INFORMATION*,
                                    struct _SYSTEMTIME*,
                                    struct _SYSTEMTIME*);
int TzSpecificLocalTimeToSystemTime(struct _TIME_ZONE_INFORMATION*,
                                    struct _SYSTEMTIME*,
                                    struct _SYSTEMTIME*);

int CreateProcessA(char*,
                   char*,
                   struct _SECURITY_ATTRIBUTES*,
                   struct _SECURITY_ATTRIBUTES*,
                   int,
                   unsigned,
                   void*,
                   char*,
                   struct _STARTUPINFO*,
                   struct _PROCESS_INFORMATION*);
int GetExitCodeProcess(unsigned, unsigned*);

unsigned WaitForSingleObject(unsigned, unsigned);

TOP_LEVEL_EXCEPTION_FILTER* SetUnhandledExceptionFilter(TOP_LEVEL_EXCEPTION_FILTER*);

void* LoadLibraryExA(char*, unsigned, unsigned);
int FreeLibrary(void*);
void (*GetProcAddress(void*, char*))();

#endif
