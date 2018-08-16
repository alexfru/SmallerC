# Smaller C Standard Library

## Table of contents

[Current status](#current-status)

[Minimum OS versions](#minimum-os-versions)

[Supported headers and functions](#supported-headers-and-functions)

[Unsupported headers](#unsupported-headers)

[POSIX compatibility](#posix-compatibility)

[DOS compatibility](#dos-compatibility)

[System call exposure](#system-call-exposure)

[Multithreading](#multithreading)

[Recompiling](#recompiling)

## Current status

The standard library is mostly complete for DOS, Windows, Linux and MacOS and
is already usable. In fact, the precompiled Smaller C binaries have been
compiled with Smaller C and linked with the Smaller C standard library. Most
of the compiler tests in this repository also successfully work with the
library. This shows some maturity.

## Minimum OS versions

The library is implemented on top of system calls of DOS, Windows, Linux and
MacOS. (Strictly speaking, kernel32.dll is used on Windows and not
syscall-invoking instructions.)

The DOS version of the library requires one of:
*   MS-DOS 4.01 or better, i80386 CPU & i80387 FPU or better
*   Windows 95/98/Me/2000/XP or 32-bit Windows Vista/7
*   DOSBox 0.74 or better

The Windows version of the library requires one of:
*   Client OS: Windows XP or better
*   Server OS: Windows Server 2003 or better

The Linux version of the library requires:
*   Ubuntu 12.04 LTS or better (none of the other distros has been tested)

The MacOS version of the library requires:
*   Mac OS X 10.6 (Snow Leopard) or better

## Supported headers and functions

### assert.h

NDEBUG

assert()

### ctype.h

isalnum(), isalpha(), isblank(), iscntrl(), isdigit(), isgraph(), islower()

isprint(), ispunct(), isspace(), isupper(), isxdigit(), tolower(), toupper()

### errno.h

EDOM, ERANGE

errno

Note that the C standard does not define most of the E\* macros, which are
system-specific. As of now, there's only EDOM and ERANGE are supported and
errno is never set to anything other than 0, EDOM and ERANGE.

### fcntl.h (POSIX)

O_RDONLY, O_WRONLY, O_RDWR, O_ACCMODE

O_CREAT, O_EXCL, O_TRUNC, O_APPEND

mode_t

off_t

creat()

open() (doesn't fully support O_APPEND since it's not directly supported by
DOS/Windows system calls)

### float.h

FLT_RADIX, FLT_EVAL_METHOD, FLT_ROUNDS

DECIMAL_DIG

FLT_MANT_DIG, FLT_EPSILON, FLT_DIG, FLT_MIN_EXP, FLT_MIN, FLT_MIN_10_EXP,
FLT_MAX_EXP, FLT_MAX, FLT_MAX_10_EXP

DBL_MANT_DIG, DBL_EPSILON, DBL_DIG, DBL_MIN_EXP, DBL_MIN, DBL_MIN_10_EXP,
DBL_MAX_EXP, DBL_MAX, DBL_MAX_10_EXP (defined same as the above FLT_\* macros
because double and float are 32-bit single-precision types)

LDBL_MANT_DIG, LDBL_EPSILON, LDBL_DIG, LDBL_MIN_EXP, LDBL_MIN,
LDBL_MIN_10_EXP, LDBL_MAX_EXP, LDBL_MAX, LDBL_MAX_10_EXP (defined same as the
above FLT_\* macros because long double and float are 32-bit single-precision
types)

### inttypes.h (C99)

PRId\<N\>, PRIdLEAST\<N\>, PRIdFAST\<N\>, PRIdMAX, PRIdPTR,

PRIi\<N\>, PRIiLEAST\<N\>, PRIiFAST\<N\>, PRIiMAX, PRIiPTR,

PRIo\<N\>, PRIoLEAST\<N\>, PRIoFAST\<N\>, PRIoMAX, PRIoPTR,

PRIu\<N\>, PRIuLEAST\<N\>, PRIuFAST\<N\>, PRIuMAX, PRIuPTR,

PRIx\<N\>, PRIxLEAST\<N\>, PRIxFAST\<N\>, PRIxMAX, PRIxPTR,

PRIX\<N\>, PRIXLEAST\<N\>, PRIXFAST\<N\>, PRIXMAX, PRIXPTR,

SCNd\<N\>, SCNdLEAST\<N\>, SCNdFAST\<N\>, SCNdMAX, SCNdPTR,

SCNi\<N\>, SCNiLEAST\<N\>, SCNiFAST\<N\>, SCNiMAX, SCNiPTR,

SCNo\<N\>, SCNoLEAST\<N\>, SCNoFAST\<N\>, SCNoMAX, SCNoPTR,

SCNu\<N\>, SCNuLEAST\<N\>, SCNuFAST\<N\>, SCNuMAX, SCNuPTR,

SCNx\<N\>, SCNxLEAST\<N\>, SCNxFAST\<N\>, SCNxMAX, SCNxPTR,

where \<N\> is 8, 16 and 32.

imaxdiv_t

### iso646.h (C99)

and, and_eq, bitand, bitor, compl, not, not_eq, or, or_eq, xor, xor_eq

### limits.h

CHAR_BIT, CHAR_MIN, CHAR_MAX (char is signed by default)

SCHAR_MIN, SCHAR_MAX, UCHAR_MAX

SHRT_MIN, SHRT_MAX, USHRT_MAX

INT_MIN, INT_MAX, UINT_MAX

LONG_MIN, LONG_MAX, ULONG_MAX

Note that long/32-bit types available in 32-bit, huge and unreal memory
models only.

### locale.h

NULL

LC_ALL, LC_COLLATE, LC_CTYPE, LC_MONETARY, LC_NUMERIC, LC_TIME

struct lconv

setlocale(), localeconv()

Note that only the "C" locale is supported.

### math.h

HUGE_VAL, HUGE_VALF, HUGE_VALL, INFINITY, NAN

MATH_ERRNO, MATH_ERREXCEPT, math_errhandling

frexp(), ldexp(), modf()

fmod(), fabs()

ceil(), floor(), round(), trunc()

sqrt(), hypot()

exp(), exp2(), expm1(), pow(), log(), log2(), log10()

sin(), cos(), tan(), atan2(), atan(), asin(), acos()

sinh(), cosh(), tanh()

Note that the single precision counterparts of the above functions (e.g.
fabsf()) exist as well. Both do the same thing since float and double are
32-bit single-precision types.

### setjmp.h

jmp_buf

setjmp(), longjmp()

### signal.h

sig_atomic_t

SIG_DFL, SIG_ERR, SIG_IGN

SIGABRT, SIGFPE, SIGILL, SIGINT, SIGSEGV, SIGTERM

signal(), raise()

Note that currently signal() and raise() do nothing and return an error.

### stdarg.h

va_list

va_start(), va_arg(), va_end()

### stddef.h

NULL

size_t, ptrdiff_t, wchar_t

offsetof()

### stdint.h (C99)

intptr_t, uintptr_t

INTPTR_MIN, INTPTR_MAX, UINTPTR_MAX

PTRDIFF_MIN, PTRDIFF_MAX

SIZE_MAX

intmax_t, uintmax_t

INTMAX_MIN, INTMAX_MAX, UINTMAX_MAX

Note that [u]intmax_t is not a 64-bit or larger type, which it should be.
It's a 16-bit integer in 16-bit memory models (tiny and small) and 32-bit in
32-bit, huge and unreal memory models.

int8_t, int_least8_t, int_fast8_t

uint8_t, uint_least8_t, uint_fast8_t

int16_t, int_least16_t, int_fast16_t

uint16_t, uint_least16_t, uint_fast16_t

int32_t, int_least32_t, int_fast32_t (32-bit types available in 32-bit, huge
and unreal memory models only)

uint32_t, uint_least32_t, uint_fast32_t

[U]INT_\*8_MIN, [U]INT_\*8_MAX

[U]INT_\*16_MIN, [U]INT_\*16_MAX

[U]INT_\*32_MIN, [U]INT_\*32_MAX

[U]INT8_C(), [U]INT16_C(), [U]INT32_C(), [U]INTMAX_C()

Note there are no [u]int64_t types.

WCHAR_MIN, WCHAR_MAX

### stdio.h

NULL

size_t

EOF

SEEK_SET, SEEK_CUR, SEEK_END

**fpos_t** (contains **unsigned short halves[2]**, the least significant
(halves[0]) and the most significant (halves[1]) 16 bits of 32-bit file
offsets/positions)

FILE

stdin, stdout, stderr

_IOFBF, _IONBF, _IOLBF, BUFSIZ

FOPEN_MAX, TMP_MAX

FILENAME_MAX, L_tmpnam

fopen() (doesn't support "a+" mode because it's not supported by DOS/Windows
directly. "a" should work, though)

freopen() (doesn't support "a+"; doesn't support changing file mode when
filename==NULL)

fflush()

fclose()

remove(), rename()

fread(), fwrite()

fgetc(), getc(), getchar()

ungetc() (you must first successfully read a character before calling
ungetc())

fgets(), gets()

fputc(), putc(), putchar()

fputs(), puts()

ftell(), fseek() (available in 32-bit, huge and unreal memory models only
since they provide the long/32-bit type, but you might use \_\_ftell() and
\_\_fseek() instead, however, these two latter functions have not been
thoroughly tested; also you may use fgetpos() and fsetpos() instead)

fgetpos(), fsetpos()

rewind()

clearerr(), ferror(), feof()

perror() (always prints "Unknown error \<value of errno\>")

setvbuf(), setbuf()

tmpnam(), tmpfile() (On DOS and Windows the following directories will be
checked for existence in order: %TEMP%, %TMP%, C:\\, the current directory,
and the temporary file will be in the first directory that's found to exist
and it will be named TMP00000.$$$, where there may be a different number
instead of the zeroes. Similarly, on Linux and MacOS the following
directories will be checked for existence in order: /tmp, the current
directory, and the temporary file will be in the first directory that's found
to exist and it will be named tmp00000.tmp, where there may be a different
number instead of the zeroes.)

vfprintf(), fprintf()

vprintf(), printf()

vsprintf(), sprintf()

vsnprintf(), snprintf()

vfscanf(), fscanf()  (scanf functions do not support ranges, e.g. "[a-z]")

vscanf(), scanf()

vsscanf(), sscanf()

fileno() (POSIX)

\_\_ftell(), \_\_fseek() (Smaller C-specific; these are similar to ftell()
and fseek(), but offsets are passed/returned via a pointer to fpos_t and
fpos_t consists of 2 16-bit integers as opposed to 1 32-bit integer; these
functions are intended for the tiny and small memory models in which
32-bit/long types aren't supported; these two functions haven't been
thoroughly tested)

### stdlib.h

NULL

size_t, wchar_t

div_t, ldiv_t

EXIT_SUCCESS, EXIT_FAILURE

abort() (uses **exit(EXIT_FAILURE)** instead of **raise(SIGABRT)**)

_Exit() (does not flush/close open files)

exit()

atexit()

malloc(), calloc(), free(), realloc()

abs()

labs() (available in 32-bit, huge and unreal memory models only)

div()

ldiv() (available in 32-bit, huge and unreal memory models only)

atoi()

atol(), strtol(), strtoul() (available in 32-bit, huge and unreal memory
models only)

strtof(), strtod(), atof() (available in 32-bit, huge and unreal memory
models only)

rand(), srand()

bsearch(), qsort()

getenv()

system() (the DOS version will try to execute your .COM/.EXE directly, not
via COMMAND.COM; this was done in order to receive termination status from
smlrc.exe, smlrl.exe and nasm.exe since "COMMAND.COM /C program" would always
terminate with status 0, no matter how the program exits)

### string.h

NULL

size_t

memset(), memcpy(), memmove()

memchr(), memcmp()

strcpy(), strncpy()

strxfrm()

strcat(), strncat()

strlen()

strchr(), strrchr(), strstr()

strcmp(), strncmp(), strcoll() (strcoll() is the same as strcmp())

strspn(), strcspn(), strpbrk()

strtok()

strerror() (always returns "Unknown error \<value of errno\>")

### time.h

NULL

size_t

time_t, clock_t

CLOCKS_PER_SEC

struct tm

clock() (on Linux uses times()'s tms_utime + tms_stime and assumes
sysconf(_SC_CLK_TCK)==100; on MacOS currently returns (clock_t)-1)

time()

gmtime(), localtime()

mktime()

ctime()

asctime()

strftime()

difftime()

Note that most of functions operate with the type time_t, which is 32-bit.
32-bit/long and floating types are available in 32-bit, huge and unreal
memory models only and so are most of the functions in time.h.

Note that DOS implementations of all time functions operate with local time
(and never UTC/GMT) since there's no standard way to set and maintain time
zones and such in DOS. In the future these functions could be re-implemented
to rely on the value of the environment variable **TZ**, commonly found in
UNIX-like systems.

Windows implementations of localtime() and mktime() use
SystemTimeToTzSpecificLocalTime() and TzSpecificLocalTimeToSystemTime() and
no other data sources to perform local to/from UTC/GMT time conversions.

Linux implementations of localtime() and mktime() use the gettimeofday system
call and no other data sources to perform local to/from UTC/GMT time
conversions.

MacOS implementations of localtime() and mktime() currently do not perform
local to/from UTC/GMT time conversions and operate with UTC/GMT time like
time().

### unistd.h (POSIX)

NULL

size_t, ssize_t

intptr_t

off_t

SEEK_SET, SEEK_CUR, SEEK_END

STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO

lseek() (available in 32-bit, huge and unreal memory models only since they
provide the long/32-bit type, but you might use \_\_lseekp() instead, however,
the latter has not been tested)

read(), write()

unlink() (has basic semantics of remove())

isatty()

\_\_lseekp() (Smaller C-specific; similar to lseek() but offsets are
passed/returned via a pointer to fpos_t and fpos_t consists of 2 16-bit
integers as opposed to 1 32-bit integer; this function is intended for the
tiny and small memory models in which 32-bit/long types aren't supported;
this function hasn't been thoroughly tested)

### sys/stat.h (POSIX)

S_IR\*, S_IW\*, S_IX\*, S_IRWX\*

mode_t

off_t

time_t

### sys/types.h (POSIX)

mode_t

off_t

fpos_t

size_t, ssize_t

time_t

### sys/lng.h (Smaller C)

The following functions implement poor-man's 32-bit arithmetic using pairs of
16-bit short unsigned ints.

\_\_lngFromUnsigned() (creates a 32-bit value in 2 unsigned shorts from 1
unsigned int)

\_\_lngFromSigned() (creates a 32-bit value in 2 unsigned shorts from 1
signed int)

\_\_lngToUnsigned() (converts/truncates 32-bit value of a pair of 2 unsigned
shorts to an unsigned int)

\_\_lngToSigned() (converts/truncates 32-bit value of a pair of 2 unsigned
shorts to a signed int)

\_\_lngAdd() (adds 2 pairs of 2 unsigned shorts as 32-bit integers)

\_\_lngSub() (subtracts 2 pairs of 2 unsigned shorts as 32-bit integers)

\_\_lngEq() (compares 2 pairs of 2 unsigned shorts for equality)

\_\_lngUnsignedLess() (tests if the first pair of 2 unsigned shorts is less
than the second pair; the 32-bit values are treated as unsigned)

\_\_lngSignedLess() (tests if the first pair of 2 unsigned shorts is less
than the second pair; the 32-bit values are treated as signed)

\_\_lngLessThan0() (tests the 32-bit value of a pair of 2 unsigned shorts is
less than zero; the 32-bit value is treated as signed)

Note, these functions haven't been thoroughly tested.

## Unsupported headers

### complex.h (C99)

Complex types aren't supported by Smaller C.

### fenv.h (C99)

Floating-point environment isn't supported by Smaller C.

### stdbool.h (C99)

The type bool requires a special type, _Bool, to be supported by the compiler
internally. This may be implemented in the future.

### tgmath.h (C99)

Type-generic math isn't supported by Smaller C.

### wchar.h (C99)

Not implemented (yet?), although wide characters and wide string literals are
supported (wchar_t is defined in stddef.h and stdlib.h; WCHAR_MIN and
WCHAR_MAX are defined in stdint.h).

### wctype.h (C99)

Not implemented (yet?), although wide characters and wide string literals are
supported (wchar_t is defined in stddef.h and stdlib.h).

## POSIX compatibility

POSIX compatibility is rudimentary. It is not planned to extend it much
beyond what's already supported. Some basic functions like access(), stat(),
chmod(), opendir(), readdir(), etc may be implemented in the future.

## DOS compatibility

Some of conio.h, dos.h, etc functionality (e.g. clrscr(), kbhit(), getche(),
intr(), etc), commonly found in compilers for DOS such as
Borland/Turbo C/C++, Open Watcom C/C++ and Microsoft C/Visual C++, may be
implemented in the future.

## System call exposure

DOS, Windows, Linux and MacOS provide a lot of system calls with documented
public APIs. Many of them are usually accessible with other compilers via
dedicated system header files. However, there's no goal to make all of them
accessible via e.g. \<Windows.h\> in the library or in some other way. The
primary focus of Smaller C is on what's defined in the language standard and
thus on what is required in the standard library. Everything else is
secondary.

## Multithreading

The library is not multithreading-safe.

## Recompiling

You can recompile the library. First, make sure you can successfully compile
a hello-world-type of simple application. If that works, that means the
compiler can successfully find system header files, which will be needed.

Change the current directory to srclib and then do:

> smlrcc -small dpstub.asm -o dpstub.exe

> smlrcc @lcdp.txt

> smlrcc @lcdh.txt

> smlrcc @lcdu.txt

> smlrcc @lcds.txt

> smlrcc @lcw.txt

> smlrcc @lcl.txt

> smlrcc @lcm.txt

This will produce files dpstub.exe, lcdp.a, lcdh.a, lcdu.a, lcds.a, lcw.a,
lcl.a and lcm.a. You can then copy them into directory lib and try to use.
