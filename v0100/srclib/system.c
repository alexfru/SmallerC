/*
  Copyright (c) 2014-2018, Alexey Frunze
  2-clause BSD license.
*/
#include <stdlib.h>
#include "istdio.h"
#include <ctype.h>
#include <string.h>

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

#ifdef __SMALLER_C_32__
extern void __x87init(void);
#endif

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

#ifdef __HUGE_OR_UNREAL__
static
int DosExec(char* comspec, struct execparams* p, unsigned* error)
{
  asm("section .relot\n"
      "dd      rel1\n"
      "section .text\n"
      "db      0x66, 0xB8\n" // mov eax, relocated savearea (far address: seg:ofs)
      "rel1:\n"
      "dd      savearea\n"
      "mov     bx, ax\n"
      "shr     eax, 16\n"
      "mov     ds, ax\n"
      "mov     [bx], ebp\n"
      "mov     [bx+4], esp\n"
      "mov     [bx+8], ss\n"
      "jmp     skipdata\n"
      "savearea:\n"
      "dw      0,0,0,0,0\n"
      "skipdata:\n"

      "mov     ax, 0x4b00\n"
      "mov     edx, [bp + 8]\n"
      "ror     edx, 4\n"
      "mov     ds, dx\n"
      "shr     edx, 28\n"
      "mov     ebx, [bp + 12]\n"
      "ror     ebx, 4\n"
      "mov     es, bx\n"
      "shr     ebx, 28\n"
      "int     0x21\n"

      "cli\n" // ss:sp may have been destroyed by int 0x21, prevent ISRs from using bad stack by disabling interrupts
      "mov     cx, ax\n" // save error code in cx
      "rcl     dx, 1\n" // save carry flag in dx bit 0
      "section .relot\n"
      "dd      rel2\n"
      "section .text\n"
      "db      0x66, 0xB8\n" // mov eax, relocated savearea (far address: seg:ofs)
      "rel2:\n"
      "dd      savearea\n"
      "mov     bx, ax\n"
      "shr     eax, 16\n"
      "mov     ds, ax\n"
      "mov     ss, [bx+8]\n"
      "mov     esp, [bx+4]\n"
      "sti\n" // it's safe to enable interrupts now
      "mov     ebp, [bx]\n"
      "mov     ax, cx\n" // restore error code in ax
      "rcr     dx, 1\n" // restore carry flag from dx bit 0

      "movzx   ebx, ax\n"
      "cmc\n"
      "sbb     ax, ax\n"
      "and     eax, 1\n"
      "mov     esi, [bp + 16]\n"
      "ror     esi, 4\n"
      "mov     ds, si\n"
      "shr     esi, 28\n"
      "mov     [si], ebx");
#ifdef __UNREAL__
  asm("push    dword 0\n"
      "pop     es\n"
      "pop     ds");
  // Just in case set up unreal mode again, don't depend on #GP handler to do it.
  extern void __setup_unreal(void);
  __setup_unreal();
#endif
}
#endif // __HUGE_OR_UNREAL__

#ifdef __HUGE_OR_UNREAL__
static
unsigned DosGetExitCode(void)
{
  asm("mov ah, 0x4d\n"
      "int 0x21\n"
      "and eax, 0xFFFF");
}
#endif // __HUGE_OR_UNREAL__

#ifdef __SMALLER_C_16__
static
int DosExec(char* comspec, struct execparams* p, unsigned* error)
{
  asm("mov     [cs:saveebp], ebp\n"
      "mov     [cs:saveesp], esp\n"
      "mov     [cs:savess], ss\n"
      "jmp     skipdata\n"
      "saveebp dd 0\n"
      "saveesp dd 0\n"
      "savess  dw 0\n"
      "skipdata:\n"

      "mov     ax, 0x4b00\n"
      "mov     dx, [bp + 4]\n"
      "mov     bx, [bp + 6]\n"
      "int     0x21\n"

      "mov     ss, [cs:savess]\n"
      "mov     esp, [cs:saveesp]\n"
      "mov     ebp, [cs:saveebp]\n"
      "mov     ds, [cs:savess]\n"
      "mov     es, [cs:savess]\n"

      "mov     bx, ax\n"
      "cmc\n"
      "sbb     ax, ax\n"
      "and     ax, 1\n"
      "mov     si, [bp + 8]\n"
      "mov     [si], bx");
}

static
unsigned DosGetExitCode(void)
{
  asm("mov ah, 0x4d\n"
      "int 0x21");
}
#endif // __SMALLER_C_16__

#ifdef _DPMI
#include <string.h>
#include "idpmi.h"

static
unsigned cs(void)
{
  asm("xor eax, eax\n"
      "mov ax, cs");
}

static
int DpmiGetLdtDescr(int sel, unsigned long descr[2])
{
  asm("mov ebx, [ebp + 8]\n"
      "mov edi, [ebp + 12]\n"
      "mov ax, 0xb\n"
      "int 0x31\n"
      "sbb eax, eax");
}

static
int DpmiFreeLdtDescr(int sel)
{
  asm("mov ebx, [ebp + 8]\n"
      "mov ax, 1\n"
      "int 0x31\n"
      "sbb eax, eax");
}

static
int DosExec(char* comspec, char* params, unsigned* error)
{
  unsigned short* penvsel = (unsigned short*)((char*)__dpmi_psp + 0x2c);
  unsigned short envsel = *penvsel;
  unsigned clen = strlen(comspec) + 1;
  unsigned plen = strlen(params) + 1;
  struct fcb fcbinit = { 0, "        ", "   " }; // Don't know FCBs, don't care

  struct fcb* pfcb1 = (struct fcb*)__dpmi_iobuf;
  struct fcb* pfcb2 = pfcb1 + 1;
  struct execparams* peparams = (struct execparams*)(pfcb2 + 1);
  char* pparams = (char*)(peparams + 1);
  char* pcomspec = pparams;

  __dpmi_int_regs regs;
  int e;

  if (plen > (__DPMI_IOFBUFSZ - 2*sizeof(struct fcb) - sizeof(struct execparams)) ||
      clen > (__DPMI_IOFBUFSZ - 2*sizeof(struct fcb) - sizeof(struct execparams)) - plen)
  {
    *error = -1;
    return 0;
  }

  *pfcb2 = *pfcb1 = fcbinit;
  peparams->EnvSeg = 0;
  peparams->ParamsOfs = (unsigned)pparams & 0xF;
  peparams->ParamsSeg = (unsigned)pparams >> 4;
  peparams->Fcb1Ofs = (unsigned)pfcb1 & 0xF;
  peparams->Fcb1Seg = (unsigned)pfcb1 >> 4;
  peparams->Fcb2Ofs = (unsigned)pfcb2 & 0xF;
  peparams->Fcb2Seg = (unsigned)pfcb2 >> 4;
  memcpy(pparams, params, plen);
  memcpy(pcomspec += plen, comspec, clen);

  memset(&regs, 0, sizeof regs);
  regs.eax = 0x4b00;
  regs.edx = (unsigned)pcomspec & 0xF;
  regs.ds = (unsigned)pcomspec >> 4;
  regs.ebx = (unsigned)peparams & 0xF;
  regs.es = (unsigned)peparams >> 4;

  // Windows XP's NTVDM leaks LDT descriptors of child DPMI processes and eventually
  // runs out of available ones in the LDT, which limits the number of DPMI child
  // processes. Here we try to work around this issue by first noting which
  // descriptors are allocated before starting a new child and then we see again
  // which are allocated and compare the two sets. If there are any new descriptors,
  // we free them. We look only at a relatively small number of descriptors in the
  // vicinity of the descriptor of the current code segment. LDT descriptors tend
  // to be allocated more or less sequentially.
#define DESCR_COUNT 64
  static int first = 1;
  static unsigned short startsel;
  static char unused[DESCR_COUNT];
  unsigned long descr[2];
  int i, count;
  unsigned short sel;

  if (first)
  {
    startsel = (cs() - (DESCR_COUNT / 2 * 8)) | 7; // 7: ldt, dpl=3
    sel = startsel;
    i = 0;
    count = DESCR_COUNT;
    while (count--)
    {
      unused[i++] = DpmiGetLdtDescr(sel, descr);
      sel += 8;
    }
    first = 0;
  }

  // DPMI hosts convert the environment segment inside the PSP to a selector
  // Temporarily change the selector back to the original segment so DOS can
  // use it to create a copy of the current environment.
  *penvsel = (unsigned)__dpmi_env >> 4;
  e = __dpmi_int(0x21, &regs);
  *penvsel = envsel;

  // Workaround the problem described in DJGPP's __maybe_fix_w2k_ntvdm_bug(),
  // which prevents execution of child DPMI processes under Windows.
  // It looks like on Windows XP it's sufficient to simply read the current PSP
  // using function 0x51 of int 0x21 and NTVDM will update the internal value
  // of PSP.
  asm("mov ah, 0x51\n"
      "int 0x21");

  // Free the leaked descriptors.
  // TBD??? This probably breaks DPMI TSRs. Can we do anything about it?
  sel = startsel;
  i = 0;
  count = DESCR_COUNT;
  while (count--)
  {
    if (unused[i++] && !DpmiGetLdtDescr(sel, descr))
      DpmiFreeLdtDescr(sel);
    sel += 8;
  }

  if (e)
  {
    *error = -1;
    return 0;
  }

  *error = regs.eax & 0xFFFF;
  return (regs.flags & 1) ^ 1; // carry
}

static
unsigned DosGetExitCode(void)
{
  asm("mov ah, 0x4d\n"
      "int 0x21\n"
      "and eax, 0xFFFF");
}
#endif // _DPMI

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
#ifndef _DPMI
  struct fcb fcb1 = { 0, "        ", "   " }; // Don't know FCBs, don't care
  struct fcb fcb2 = { 0, "        ", "   " };
  struct execparams eparams;
#endif
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

#ifndef _DPMI
  eparams.EnvSeg = 0; // create and use a copy of the current environment
#ifdef __SMALLER_C_16__
  eparams.ParamsOfs = params;
  eparams.ParamsSeg = __getSS();
  eparams.Fcb1Ofs = &fcb1;
  eparams.Fcb1Seg = __getSS();
  eparams.Fcb2Ofs = &fcb2;
  eparams.Fcb2Seg = __getSS();
#endif
#ifdef __HUGE_OR_UNREAL__
  eparams.ParamsOfs = (unsigned)params & 0xF;
  eparams.ParamsSeg = (unsigned)params >> 4;
  eparams.Fcb1Ofs = (unsigned)&fcb1 & 0xF;
  eparams.Fcb1Seg = (unsigned)&fcb1 >> 4;
  eparams.Fcb2Ofs = (unsigned)&fcb2 & 0xF;
  eparams.Fcb2Seg = (unsigned)&fcb2 >> 4;
#endif
#endif

  // Flush everything
  fflush(NULL);

#ifndef _DPMI
  if (DosExec(comspec, &eparams, &error))
  {
    res = DosGetExitCode();
  }
#else
  if (DosExec(comspec, params, &error))
  {
    res = DosGetExitCode();
  }
#endif
  else
  {
  }

end:

  if (comspec && comspec != exe)
    free(comspec);
  if (params)
    free(params);

#ifdef __SMALLER_C_32__
  __x87init();
#endif

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

  if (!__CreateProcessA(comspec, params, NULL, NULL, 0, 0, NULL, NULL, &si, &pi))
  {
    goto end;
  }

  __WaitForSingleObject(pi.hProcess, INFINITE);
  __GetExitCodeProcess(pi.hProcess, &res);
  __CloseHandle(pi.hProcess);
  __CloseHandle(pi.hThread);

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
      "int 0x80\n"
      "add eax, 0\n"
      "jns .done\n"
      "mov eax, -1\n" // error
      ".done:");
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
#endif  // _LINUX

#ifdef _MACOS

#include <sys/types.h>

static
pid_t SysFork(void)
{
  asm("mov eax, 2\n" // sys_fork
      "sub esp, 4\n"
      "int 0x80\n"
      "jnc .diff\n"

      "mov eax, -1\n" // error
      "jmp .done\n"

      ".diff:\n"
      "or  edx, edx\n"
      "jz  .done\n" // parent: eax = pid of child

      "xor eax, eax\n" // child: eax = 0

      ".done:\n");
}

static
pid_t SysWaitpid(pid_t pid, int* status, int options)
{
  asm("mov  eax, 7\n" // sys_wait4
      "push dword 0\n"
      "push dword [ebp + 16]\n"
      "push dword [ebp + 12]\n"
      "push dword [ebp + 8]\n"
      "sub  esp, 4\n"
      "int  0x80");
}

static
int SysExecve(char* path, char* argv[], char* envp[])
{
  asm("mov  eax, 59\n" // sys_execve
      "push dword [ebp + 16]\n"
      "push dword [ebp + 12]\n"
      "push dword [ebp + 8]\n"
      "sub  esp, 4\n"
      "int  0x80");
}
#endif  // _MACOS

#ifdef UNIX_LIKE
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

#endif // UNIX_LIKE
