/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include <stdlib.h>
#include "istdio.h"
#include <ctype.h>
#include <string.h>

#ifdef _DOS

#ifdef __SMALLER_C_16__
extern unsigned short __getSS(void);
#endif

struct fcb
{
  unsigned char drive;
  char name[8];
  char ext[3];
  char misc[25];
};

struct execparams
{
  unsigned short EnvSeg;
  unsigned short ParamsOfs;
  unsigned short ParamsSeg;
  unsigned short Fcb1Ofs;
  unsigned short Fcb1Seg;
  unsigned short Fcb2Ofs;
  unsigned short Fcb2Seg;
};

#ifdef __HUGE__
static
int DosExec(char* comspec, struct execparams* p, unsigned* error)
{
  asm("section .relot");
  asm("dd     rel1");
  asm("section .text");
  asm("db     0x66, 0xB8"); // mov eax, relocated savearea (far address: seg:ofs)
  asm("rel1:");
  asm("dd     savearea");
  asm("mov    bx, ax");
  asm("shr    eax, 16");
  asm("mov    ds, ax");
  asm("mov    [bx], ebp");
  asm("mov    [bx+4], esp");
  asm("mov    [bx+8], ss");
  asm("jmp    skipdata");
  asm("savearea:");
  asm("dw     0,0,0,0,0");
  asm("skipdata:");

  asm("mov ax, 0x4b00\n"
      "mov edx, [bp + 8]\n"
      "ror edx, 4\n"
      "mov ds, dx\n"
      "shr edx, 28");
  asm("mov ebx, [bp + 12]\n"
      "ror ebx, 4\n"
      "mov es, bx\n"
      "shr ebx, 28\n"
      "int 0x21");

  asm("cli"); // ss:sp may have been destroyed by int 0x21, prevent ISRs from using bad stack by disabling interrupts
  asm("mov    cx, ax"); // save error code in cx
  asm("rcl    dx, 1"); // save carry flag in dx bit 0
  asm("section .relot");
  asm("dd     rel2");
  asm("section .text");
  asm("db     0x66, 0xB8"); // mov eax, relocated savearea (far address: seg:ofs)
  asm("rel2:");
  asm("dd     savearea");
  asm("mov    bx, ax");
  asm("shr    eax, 16");
  asm("mov    ds, ax");
  asm("mov    ss, [bx+8]");
  asm("mov    esp, [bx+4]");
  asm("sti"); // it's safe to enable interrupts now
  asm("mov    ebp, [bx]");
  asm("mov    ax, cx"); // restore error code in ax
  asm("rcr    dx, 1"); // restore carry flag from dx bit 0

  asm("movzx ebx, ax\n"
      "cmc\n"
      "sbb ax, ax\n"
      "and eax, 1\n"
      "mov esi, [bp + 16]\n"
      "ror esi, 4\n"
      "mov ds, si\n"
      "shr esi, 28\n"
      "mov [si], ebx");
}

static
unsigned DosGetExitCode(void)
{
  asm("mov ah, 0x4d\n"
      "int 0x21\n"
      "and eax, 0xFFFF");
}
#endif // __HUGE__

#ifdef __SMALLER_C_16__
static
int DosExec(char* comspec, struct execparams* p, unsigned* error)
{
  asm("mov [cs:saveebp], ebp");
  asm("mov [cs:saveesp], esp");
  asm("mov [cs:savess], ss");
  asm("jmp skipdata");
  asm("saveebp dd 0");
  asm("saveesp dd 0");
  asm("savess dw 0");
  asm("skipdata:");

  asm("mov ax, 0x4b00\n"
      "mov dx, [bp + 4]\n"
      "mov bx, [bp + 6]\n"
      "int 0x21");

  asm("mov ss, [cs:savess]");
  asm("mov esp, [cs:saveesp]");
  asm("mov ebp, [cs:saveebp]");
  asm("mov ds, [cs:savess]");
  asm("mov es, [cs:savess]");

  asm("mov bx, ax\n"
      "cmc\n"
      "sbb ax, ax\n"
      "and ax, 1\n"
      "mov si, [bp + 8]\n"
      "mov [si], bx");
}

static
unsigned DosGetExitCode(void)
{
  asm("mov ah, 0x4d\n"
      "int 0x21");
}
#endif // __SMALLER_C_16__

extern char* __strtoklast;

static int helper(char exe[FILENAME_MAX], char** cmd)
{
  char *start, *end;
  int haspath = 0;
  unsigned clen;

  *exe = '\0';

  // Find command start and end

  start = *cmd;
  while (*start == ' ') start++; // skip leading spaces, if any

  end = start;
  while (*end != '\0' && *end != ' ')
  {
    if (*end == ':' || *end == '/' || *end == '\\')
      haspath = 1;
    // If there's a '%', it may be an environment variable, pass the
    // command to COMMAND.COM as-is. Also, bail out on some reserved characters.
    if (strchr("\"%*+,;<=>?[]|", *end))
      return 0;
    end++;
  }

  // If the command doesn't contain an executable filename extension,
  // it may be an internal command of COMMAND.COM.
  // Treat it as such for simplicity, don't do anything special, pass it
  // to COMMAND.COM as-is.

  clen = end - start;
  if (clen <= 4 || clen >= FILENAME_MAX || end[-4] != '.')
    return 0;

  if (!((toupper((unsigned char)end[-3]) == 'E' &&
         toupper((unsigned char)end[-2]) == 'X' &&
         toupper((unsigned char)end[-1]) == 'E') ||
        (toupper((unsigned char)end[-3]) == 'C' &&
         toupper((unsigned char)end[-2]) == 'O' &&
         toupper((unsigned char)end[-1]) == 'M')))
    return 0;

  while (*end == ' ') end++;
  *cmd = end; // move the pointer to the first parameter of the command, if any

  if (strpbrk(end, "<>|")) // Bail out on redirection
    return 0;

  // If there hasn't been any path delimiter (slash or colon), look for
  // this .COM/.EXE in the current directory and then in the directories
  // listed in the PATH environment variable.

  if (!haspath)
  {
    FILE* f;
    char* ev;
    char* paths;
    char* sep;
    char* path;
    char* lasttok;

    // Check the current directory

    memcpy(exe, start, clen);
    exe[clen] = '\0';
    // TBD!!! use another method to check whether or not the file exists, e.g. try getting its attributes
    if ((f = fopen(exe, "rb")) != NULL)
    {
      fclose(f);
      return 0;
    }

    // All that's left is to try %PATH%

    *exe = '\0';

    ev = __EnvVar;
    __EnvVar = NULL;
    paths = getenv("PATH");
    __EnvVar = ev; // restore the string previously returned by getenv()
    if (!paths)
    {
      return -1;
    }

    lasttok = __strtoklast; // save and reset strtok() state
    __strtoklast = NULL;
    sep = ";";
    for (path = strtok(paths, sep); path; path = strtok(NULL, sep))
    {
      size_t plen = strlen(path);

      if (plen && path[plen-1] != '\\' && path[plen-1] != '/')
        path[plen++] = '\\';

      if (plen + clen >= FILENAME_MAX)
        continue;

      memcpy(exe, path, plen);
      memcpy(exe + plen, start, clen);
      exe[plen + clen] = '\0';

      // TBD!!! use another method to check whether or not the file exists, e.g. try getting its attributes
      if ((f = fopen(exe, "rb")) != NULL)
        break;
    }

    free(paths);
    __strtoklast = lasttok; // restore strtok() state
    if (f)
    {
      fclose(f);
      return 0;
    }
    return -1;
  }
  else
  {
    FILE* f;
    memcpy(exe, start, clen);
    exe[clen] = '\0';
    // TBD!!! use another method to check whether or not the file exists, e.g. try getting its attributes
    if ((f = fopen(exe, "rb")) != NULL)
    {
      fclose(f);
      return 0;
    }
    return -1;
  }
}

int system(char* cmd)
{
  char *ev, *comspec, *params = NULL;
  unsigned clen, plen;
  int res = -1;
  struct fcb fcb1 = { 0, "        ", "   " }; // Don't know FCBs, don't care
  struct fcb fcb2 = { 0, "        ", "   " };
  struct execparams eparams;
  unsigned error;
  char exe[FILENAME_MAX];
  char* cmdparams;

  ev = __EnvVar;
  __EnvVar = NULL;
  comspec = getenv("COMSPEC");
  __EnvVar = ev; // restore the string previously returned by getenv()

  if (!cmd)
  {
    if (comspec)
    {
      free(comspec);
      return 1;
    }
    return 0;
  }

  if (!comspec)
  {
    goto end;
  }

  // If the command ends in .COM or .EXE, we'll execute this command/executable directly
  // (as opposed to using "COMMAND.COM /C command") in order to be able to get its exit code
  // and not the exit code of the command processor (which is typically 0 in DOS).

  cmdparams = cmd;
  if (helper(exe, &cmdparams))
  {
    goto end;
  }
  if (*exe)
  {
    comspec = exe;
    cmd = cmdparams;
  }

  clen = strlen(cmd);
  plen = 1/*params length*/ + 3*(comspec != exe)/*"/C "*/ + clen + 1/*'\r'*/;
  if (plen > 128)
  {
    goto end;
  }
  params = malloc(plen);
  if (!params)
  {
    goto end;
  }

  if (clen)
  {
    unsigned start;
    params[0] = plen - 2;
    if (comspec != exe)
    {
      memcpy(params + 1, "/C ", 3);
      start = 4;
    }
    else
    {
      start = 1;
    }
    memcpy(params + start, cmd, clen);
    params[plen - 1] = '\r';

    // Convert UNIX current directory prefix ("./") to DOS current directory prefix (".\\") if needed.
    // COMMAND.COM may mistakenly recognize "./foo.exe" as program "." with parameters "/foo.exe",
    // which would be an error anyway.
    if (params[start] == '.' && params[start+1] == '/')
      params[start+1] = '\\';
  }
  else
  {
    // If the command is empty, just launch COMMAND.COM and wait for the user to type the EXIT command
    params[0] = 0;
    params[1] = '\r';
  }
  // Convert UNIX current directory prefix ("./") to DOS current directory prefix (".\\") if needed.
  // COMMAND.COM may mistakenly recognize "./foo.exe" as program "." with parameters "/foo.exe",
  // which would be an error anyway.
  if (comspec == exe && *exe == '.' && exe[1] == '/')
    exe[1] = '\\';

  eparams.EnvSeg = 0; // create and use a copy of the current environment
#ifdef __SMALLER_C_16__
  eparams.ParamsOfs = params;
  eparams.ParamsSeg = __getSS();
  eparams.Fcb1Ofs = &fcb1;
  eparams.Fcb1Seg = __getSS();
  eparams.Fcb2Ofs = &fcb2;
  eparams.Fcb2Seg = __getSS();
#endif
#ifdef __HUGE__
  eparams.ParamsOfs = (unsigned)params & 0xF;
  eparams.ParamsSeg = (unsigned)params >> 4;
  eparams.Fcb1Ofs = (unsigned)&fcb1 & 0xF;
  eparams.Fcb1Seg = (unsigned)&fcb1 >> 4;
  eparams.Fcb2Ofs = (unsigned)&fcb2 & 0xF;
  eparams.Fcb2Seg = (unsigned)&fcb2 >> 4;
#endif

  // Flush everything
  fflush(NULL);

  if (DosExec(comspec, &eparams, &error))
  {
    res = DosGetExitCode();
  }
  else
  {
  }

end:

  if (comspec && comspec != exe)
    free(comspec);
  if (params)
    free(params);

  return res;
}

#endif // _DOS

#ifdef _WINDOWS

#include "iwin32.h"

int system(char* cmd)
{
  char *ev, *comspec = NULL, *params = NULL;
  unsigned len;
  int res = -1;
  STARTUPINFO si;
  PROCESS_INFORMATION pi;

  ev = __EnvVar;
  __EnvVar = NULL;
  comspec = getenv("COMSPEC");
  __EnvVar = ev; // restore the string previously returned by getenv()

  if (!cmd)
  {
    res = comspec != NULL;
    goto end;
  }

  if (!comspec)
  {
    goto end;
  }

  memset(&si, 0, sizeof si);
  memset(&pi, 0, sizeof pi);
  si.cb = sizeof si;

  if ((len = strlen(cmd)) != 0)
  {
    if ((params = malloc(len + sizeof "/C ")) == NULL)
      goto end;
    strcpy(params, "/C ");
    strcat(params, cmd);
  }

  if (!CreateProcessA(comspec, params, NULL, NULL, 0, 0, NULL, NULL, &si, &pi))
  {
    goto end;
  }

  WaitForSingleObject(pi.hProcess, INFINITE);
  GetExitCodeProcess(pi.hProcess, &res);
  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);

end:

  if (comspec)
    free(comspec);

  if (params)
    free(params);

  return res;
}

#endif // _WINDOWS

#ifdef _LINUX

#include <sys/types.h>

static
pid_t SysFork(void)
{
  asm("mov eax, 2\n" // sys_fork
      "int 0x80");
}

static
pid_t SysWaitpid(pid_t pid, int* status, int options)
{
  asm("mov eax, 7\n" // sys_waitpid
      "mov ebx, [ebp + 8]\n"
      "mov ecx, [ebp + 12]\n"
      "mov edx, [ebp + 16]\n"
      "int 0x80");
}

static
int SysExecve(char* path, char* argv[], char* envp[])
{
  asm("mov eax, 11\n" // sys_execve
      "mov ebx, [ebp + 8]\n"
      "mov ecx, [ebp + 12]\n"
      "mov edx, [ebp + 16]\n"
      "int 0x80");
}

extern char** __environ;

int system(char* cmd)
{
  char *comspec;
  int res = -1;
  char* argv[4] = { 0 };
  pid_t pid;
  int status;

  comspec = getenv("SHELL");

  if (!cmd)
  {
    res = comspec != NULL;
    goto end;
  }

  if (!comspec)
  {
    goto end;
  }

  if ((pid = SysFork()) == -1)
  {
    goto end;
  }

  if (pid)
  {
    if (SysWaitpid(-1, &status, 0) != pid)
    {
      goto end;
    }

    // The caller will need to apply WEXITSTATUS() to the value to get process exit status,
    // IOW, take bits 8 through 15 of the value returned by system().
    res = status;
  }
  else
  {
    argv[0] = comspec;
    if (*cmd)
    {
      argv[1] = "-c";
      argv[2] = cmd;
    }
    SysExecve(argv[0], argv, __environ);
    _Exit(-1);
  }

end:

  return res;
}

#endif // _LINUX
