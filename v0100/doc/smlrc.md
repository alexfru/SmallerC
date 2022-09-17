# Smaller C Core Compiler

## Table of contents

[About this document](#about-this-document)

[What is Smaller C?](#what-is-smaller-c)

[Why yet another compiler?](#why-yet-another-compiler)

[What features are supported by Smaller C?](#what-features-are-supported-by-smaller-c)

[What features are NOT supported by Smaller C?](#what-features-are-not-supported-by-smaller-c)

[Calling conventions](#calling-conventions)

[Limitations and implementation details](#limitations-and-implementation-details)

[How do I compile Smaller C on/for x86?](#how-do-i-compile-smaller-c-onfor-x86)

[How do I compile Smaller C for MIPS?](#how-do-i-compile-smaller-c-for-mips)

[How do I run Smaller C?](#how-do-i-run-smaller-c)

[How do I compile Smaller C with itself?](#how-do-i-compile-smaller-c-with-itself)

[Miscellaneous](#miscellaneous)

## About this document

This document reflects the current state of the Smaller C core compiler. It
is a live document and it is updated regularly (typically, with every code
change).

## What is Smaller C?

Smaller C is a simple and small single-pass C compiler, currently supporting
most of the C language common between C89/ANSI C and C99 (minus some C89 and
plus some C99 features).

Currently it generates 16-bit and 32-bit 80386+ assembly code for NASM that
can then be assembled and linked into DOS, Windows, Linux and MacOS programs.

Code generation for MIPS CPUs is also supported.

The core compiler is capable of compiling its own source code.

Smaller C is not an optimizing compiler, but it does the job better than the
typical _small C_ implementation.

## Why yet another compiler?

*   I always wanted to write one, to see what it takes and how it is and I
    have now got enough knowledge and time to finally do it
*   It's a good programming exercise and the project is small enough to be
    manageable by one person and to be functional in just a few months (in
    comparison, I haven't yet been able to finish my OS project. I think, it
    is just a little too big for me)
*   There are a number of old implementations of _small C_ by Ron Cain, James
    Hendrix and others (see also _SubC_ by Nils Holm) which I could have used
    as a foundation, but I wanted something less limited, something
    supporting modern C syntax and both 16-bit and 32-bit x86 targets and
    still fitting into ~64-128 KB of RAM for code and data and being
    self-compilable (which is why there are no external lexers and parsers
    used)
*   It may be useful as a simple and small (cross-) compiler for DOS,
    RetroBSD or other OSes, including hobby OSes
*   It's fun!

## What features are supported by Smaller C?

*   decimal, octal and hexadecimal integer constants, e.g. **15**, **017**,
    **0xF**, **32768u**
*   floating-point constants, e.g. **1.5e5**, **.5f**, **.5L**
*   character constants, e.g. **'a'**, **'\\''**, **'\n'**, **'\0'**,
    **'\x41'**
*   _multi-character_ character constants, e.g. **'ab'**
*   string literals, e.g. **"string"**
*   _wide_ character constants and _wide_ string literals, e.g. **L'a'**,
    **L"string"**
*   **void**
*   **char** (signed by default, can be changed to unsigned via a
    command-line option)
*   **signed char**, **unsigned char**
*   **short**, **unsigned short**
*   **int**, **unsigned int**
*   **long**, **unsigned long** (only in 32-bit, huge and unreal mode(l)s)
*   **float**, **double**, **long double** (only in 32-bit, huge and unreal
    mode(l)s; **double** and **long double** are aliases for **float**)
*   **struct**, **union**
*   **#pragma pack()** (mostly useless for MIPS because it can't access
    misaligned memory locations and the MIPS code generator doesn't provide a
    solution for that)
*   **enum**
*   _functions_
*   _arrays_ (including multidimensional) and _pointers_ of/to each other and
    of/to the above
*   _expressions_
*   all _operators_
*   **sizeof** _expression_, **sizeof**( _type_ )
*   type _casts_, e.g. **int x = (int)&x;**
*   global and local _declarations_ and _function prototypes_
*   **extern**
*   **static**
*   **typedef**
*   **\_\_func\_\_**
*   _initialization_ of variables
*   _incomplete types/arrays_, e.g. **extern int array[][2];** or
    **int main(int argc, char\* argv[]);**
*   _declarations_ of variables _after statements_ (C99/C++-style), e.g.
    **{ int a = 1; printf("a=%d\n", a); int b = 2; printf("b=%d\n", b); }**
*   _implicit function declarations_, e.g. you can call printf() without
    first declaring it or including stdio.h
*   _variadic_ functions with optional parameters represented as **...**
    similar to **printf()** (unfortunately, the **va_something** macros
    aren't currently supported)
*   the _compound statement_, **{}**
*   **if**, **else**
*   **goto**
*   **while**, **do**, **for** (C99/C++-style, supporting variable
    declaration as in **for(int i=0;;)**), **break**, **continue**
*   **switch**, **case**, **default**
*   **return**
*   **asm("assembly code");** The inline assembly code is output verbatim to
    the output file.
*   **#line**, e.g. **#line 123**, **#line 234 "file1.c"** (or gcc-style:
    **#123**, **#234 "file1.c"**)
*   **\_\_interrupt** functions (experimental; x86/huge and unreal only)
*   _comments_, e.g. **/* comment */** and **// comment**
*   **#define**, e.g. **#define TEN 10** ( _parametrized_ macros like
    **#define DOUBLE(x) ((x)\*2)** aren't currently supported)
*   **#undef**
*   **#ifdef**, **#ifndef**, **#else**, **#endif**
*   **#include**, e.g. **#include "somefile"** or **#include \<somefile\>**
*   **\_\_FILE\_\_**
*   **\_\_LINE\_\_**

## What features are NOT supported by Smaller C?

*   most of the _preprocessor_. The core compiler (smlrc) relies on an
    external preprocessor (smlrpp (which is a version of ucpp adapted for use
    with Smaller C) or gcc).
*   **long long**
*   _designated initializers_, _compound literals_
*   structure/union _bit-fields_ and _flexible array members_
*   **const**, **volatile** (they are treated as white space; everything is
    de facto volatile-ish); if you want a read-only automatic/local variable
    to not consume stack space, use **static** instead of or in addition to
    **const**
*   _tentative declarations_ (if you don't know what they are, you shouldn't
    probably worry)
*   _variable-length arrays_ (AKA **VLAs**)
*   K&R-style function declarations (that is, with *identifier-list* instead
    of *parameter-type-list*), e.g.
    **int add(a, b) int a; int b; { return a + b; }**
*   _Implicit int_, e.g. **static x = 1; const y = 2; main(void) {}** must be
    **static int x = 1; const int y = 2; int main(void) {}**.
*   _complex-valued_ arithmetic, **_Complex**, **_Imaginary**
*   **auto**, **register**, **restrict** (treated as white space)
*   **inline**, **_Bool**
*   probably, whatever I've forgotten to mention

## Calling conventions

*   x86: stack-based calling convention: all arguments (including
    floating-point) go onto the stack (order: the first argument is on top of
    the stack), the caller cleans up the stack after the call, the return
    value is in **(e)ax** (including floating-point).
*   MIPS: standard stack-based calling convention: the first 4 arguments
    (including floating-point) go into **a0**-**a3** (stack space is always
    reserved for the first 4 arguments (even if none passed) as if they were
    passed on the stack), the rest go onto the stack (order: the first
    argument, if it was pushed, would appear on top of the stack), the caller
    cleans up the stack after the call, the return value is in **v0**
    (including floating-point).
*   When you pass a structure to a function by value, the entire structure is
    pushed onto the stack, where it occupies an integral number of machine
    words (that is, some padding may be added at the end so as to preserve
    argument alignment on the stack). In order to receive a structure by
    value from a function, an implicit/hidden argument is passed to the
    function before function's first formal argument/parameter (if any) and
    this implicit argument points to the location where the function will
    store its return value.

## Limitations and implementation details

*   Error and warning messages emitted by Smaller C indicate approximate
    error location in the source file. For example, an error at 7:15 would
    mean that the error is on line 7 in position 15 or before position 15,
    most probably somewhere in the declaration or expression ending at 7:15
*   All char types (**char**, **signed char**, **unsigned char**) are 8-bit
*   **short** and **unsigned short** are 16-bit
*   **int** and **unsigned int** are either 16-bit or 32-bit, depending on
    the mode(l)
*   **wchar_t** is either unsigned or signed, 16-bit or 32-bit, depending on
    the relevant options
*   Wide string literals can't be concatenated with adjacent plain string
    literals
*   Non-ASCII chars may not appear in wide characters or wide string
    literals, use hexadecimal escape sequences to work around this, e.g.
    **L'\xF1'** for Latin small letter N with tilde
*   struct/union members are naturally aligned by default, that is, 16-bit
    types are 2-byte-aligned and 32-bit types are 4-byte-aligned. Use
    **#pragma pack()** if necessary
*   **sizeof(int)** = **sizeof(void\*)** = **sizeof(void(\*)())**, IOW, ints
    and pointers are same size, _far pointers_ are not supported (except in
    the **huge** and **unreal** memory models, more on this later)
*   **long** and **unsigned long** are 32-bit (if supported by the mode(l))
*   **float**, **double** and **long double** are 32-bit single-precision
    (if supported by the mode(l))
*   **enum** types and constants are always of type and size of **int**
*   operators **++**, **--**, **+=**, **-=**, **\*=**, **/=** are not
    supported with floating-point operands at the moment
*   Run-time checks for stack overflow aren't generated and compile-time
    checks are virtually nonexistent. Be careful with recursion and passing
    and returning structures by value. Note, a temporary object is always
    allocated on the stack for receiving (by value) a structure from a
    function even if the function's return value is immediately assigned to
    another structure, e.g. in a situation like this
    **{ static struct S s; s = f(); }** a temporary object receives the value
    returned by **f()** and then the temporary object is copied to **s**. A
    temporary object exists until the end of the expression, in which it is
    created. Even so, it's advised to pass and return by value only
    relatively small structures
*   Large decimal integer constants without a **U** suffix (such as 32768 in
    16-bit mode(l)s and 2147483648 or 2147483648L in 32-bit mode(l)s) not
    fitting into type signed int may cause compilation errors. Long story
    short, you'll probably have to append the **U** suffix to the constant
    (e.g. 32768U, 2147483648U, 2147483648UL) recompile the code and forget
    about it. Now, the long story. If a decimal constant has no suffix, its
    type must be either int or long or, depending on the version of the C
    standard that the compiler implements, a) unsigned long (ANSI C/C89) or
    b) long long (C99). The compiler chooses the first type from this list
    that can represent the constant. If the decimal constant has an **L**
    suffix only, its type must be either long or, depending on the version of
    the C standard that the compiler implements, a) unsigned long (ANSI C/
    C89) or b) long long (C99). Again, the compiler chooses the first type
    that can represent the constant. If the decimal constant has the **U**
    suffix only, its type must be either unsigned int or unsigned long or
    unsigned long long (long long is C99 only). As usual, the compiler
    chooses the first type that can represent the constant. If the decimal
    constant has the **U** suffix and the **L** suffix (just one L), its type
    must be either unsigned long or unsigned long long (long long is C99
    only). And the compiler still chooses the first type from this list that
    can represent the constant. As you can see, there's ambiguity as to what
    type a large decimal constant should be. In ANSI C/C89 it may be of type
    unsigned long, while in C99 it may be of type long long. In some cases
    this ambiguity can lead to changing the behavior of the code and thus to
    its breakage. Smaller C does not support long long as of now and while it
    might seem reasonable to adopt the ANSI C approach here, it would hide a
    portability issue that is easily detectable and correctable. I chose to
    turn this portability issue into a compilation error. Another reason why
    you can run into this compilation error is that in 16-bit modes Smaller C
    does not support type long (which, btw, has to have 32 bits or more per
    the language standard) and what could've become long simply can't because
    there's no type for it.
*   16-bit versions of the compiler (except if compiled with the **-huge**
    and **-unreal** options) will not compile your C code into 32-bit
    assembly
*   redeclaration/redefinition checks are imperfect
*   specifically, _composite types_ can be constructed for arrays but not
    always for functions/prototypes (parameter specification can't change
    from specified to unspecified, that is, you can't have **void f(int);**
    followed by **void f();**, but you can have the two in reverse order)
*   there are no checks for the missing **return** statement at the end of
    the function
*   there are minimal type checks in the assignment operator **=** and in
    function argument passing. Values of types **char**, **int**, **void**\*,
    **struct someTag**\*, **_type_**\*, etc can be freely assigned to one
    another or passed as one another or returned as one another
*   functions returning **char**, **signed char**, **unsigned char**,
    **short** and **unsigned short** have to zero- or sign-extend (depending
    on _signedness_ of the particular **char** or **short** type) the return
    value to fill the entire _ax_ or _eax_ register ( **x86**; _ax_ for
    16-bit code, _eax_ for 32-bit code) or the _v0_ register ( **MIPS** ).
*   Smaller C's functions do not preserve **x86** registers (other than
    **(e)sp** and **(e)bp**). Because of that they may not work when used as
    callbacks from standard library functions such as **bsearch()**,
    **qsort()**, **atexit()** if those expect (per the calling convention)
    register preservation in callback functions. This problem exists only
    with standard libraries borrowed as object/library files from other
    compilers. The problem does not exist if you're using Smaller C's
    standard library or if you recompile a borrowed library from its source
    with Smaller C. It is possible to preserve all or most registers, but
    there isn't a single widely supported calling convention, so currently
    this is left unimplemented. You may be able to work-around this with
    **asm("assembly code");**, e.g. as the very first thing in a callback
    function you could do
    **asm("push ebx\npush ecx\npush edx\npush esi\npush edi");** and then
    just before returning from it do the complementary
    **asm("pop edi\npop esi\npop edx\npop ecx\npop ebx");**.
*   Smaller C's functions do not require nor guarantee that the stack is
    aligned on two machine words. Code compiled with other compilers (e.g.
    gcc) may require and attempt to maintain such alignment. Therefore, there
    may be interoperability issues between code compiled with Smaller C and
    code compiled with another compiler if the two are linked together.
    However, this problem typically arises only when scalar types of the size
    of two machine words are used (e.g. long long, double), none of which are
    currently supported by Smaller C itself.
*   Currently, Smaller C uses statically allocated arrays (instead of
    dynamically allocated memory buffers) to maintain tables of known macros,
    declarations, enums, identifiers, etc and so large C files may exhaust
    those arrays and therefore they may need to be split up into several
    smaller ones. Alternatively, Smaller C can be recompiled with larger
    arrays to accommodate large C files (there are a few macros in the code
    that define the sizes of the various arrays).

## How do I compile Smaller C on/for x86?

With Turbo C++ 1.01 in DOS/DosBox:
> tcc.exe -esmlrc.exe smlrc.c

With DJGPP (gcc 3.3.4 for DOS) in DOS/DosBox:
> gcc.exe -Wall -O2 smlrc.c -o smlrc.exe

With Open Watcom C/C++ 1.9 in Windows:
> wcl386.exe /q /we /wx /j smlrc.c /fe=smlrc.exe

With 32-bit MinGW (gcc 4.6.2) in Windows:
> gcc.exe -Wall -Wextra -O2 smlrc.c -o smlrc.exe

With 32-bit gcc in Linux:
> gcc -Wall -Wextra -O2 smlrc.c -o smlrc

## How do I compile Smaller C for MIPS?

The compilation steps are pretty much the same as for x86. If you want to
compile it with MIPS code generation instead of x86 code generation, you need
to define the **MIPS** macro at compile time. For example, with gcc you'd do
it like this:

> gcc -Wall -Wextra -DMIPS -O2 smlrc.c -o smlrc

If you want to compile Smaller C for [RetroBSD (MIPS)](http://retrobsd.org/),
you can do it like so (you'll need the
[ice2aout](https://github.com/alexfru/icacheMips) tool):

> pic32-gcc -nostdinc -nostartfiles -ffreestanding -nostdlib -nodefaultlibs -mno-peripheral-libs -X -T smlrcrb.ld -DNO_ANNOTATIONS -DNO_PREPROCESSOR -DNO_PPACK -DNO_EXTRA_WARNS -DNO_STRUCT_BY_VAL -DSYNTAX_STACK_MAX=2568 -DSTATIC -D__SMALLER_C__ -D__SMALLER_C_SCHAR__ -D__SMALLER_C_32__ -D_RETROBSD -DMIPS smlrcrb.s lb.c smlrc.c -Os -o smlrcrb.elf

> ice2aout smlrcrb.elf smlrc

> chmod +x smlrc

## How do I run Smaller C?

You invoke it like this (in DOS and Windows):
> smlrc.exe [options] somefile.c somefile.asm

or like this (in Linux):
> ./smlrc [options] somefile.c somefile.asm

**Options**:
*   **-8086** (x86 only) This chooses output 8086 compatible instructions
    only, use this flag only with **-seg16** .
*   **-seg16** (x86 only) This chooses 16-bit output and wraps code and data
    into separate generic **SECTION** blocks. This is the **default**. Note:
    does not support **long**, **float**, **double**, **long double**.
    Predefines **\_\_SMALLER\_C\_16\_\_**.
*   **-seg32** (x86 only) This chooses 32-bit output and wraps code and data
    into separate generic **SECTION** blocks. Predefines
    **\_\_SMALLER\_C\_32\_\_**.
*   **-huge** (x86 only) This is similar to **-seg32** in that ints and
    pointers are 32-bit. However, the generated code is to be executed in the
    16-bit *real-address* or *virtual-8086* mode (i.e. targeting DOS). The
    pointers are 32-bit physical addresses and they get converted into far
    pointers (16-bit segment:16-bit offset pairs) completely transparently.
    This memory model is similar to the **huge** memory model encountered in
    16-bit Borland C/C++ compilers. This model helps porting code to DOS and
    eases writing code for DOS, liberating the programmer from the need to
    deal with segments explicitly if more than 64KB of memory needs to be
    used. With this model you can have more than 64KB of code and more than
    64KB of data. Individual data objects can be larger than 64KB as well
    (e.g. you can have large arrays). You're only limited by the amount of
    free "conventional" memory in DOS (e.g. up to some 500KB). Currently, in
    this model the stack is limited to 64KB and the cumulative size of local
    variables is limited to 32KB (this is a per-function limit). Individual
    functions are limited to approximately 64KB of code size. These
    limitations should not pose problems normally. Predefines
    **\_\_SMALLER\_C\_32\_\_** and **\_\_HUGE\_\_**.
*   **-unreal** (x86 only) This is similar to **-seg32** in that ints and
    pointers are 32-bit. However, the generated code is to be executed in the
    16-bit *unreal* (AKA *big real*) mode (i.e. targeting DOS). The pointers
    are 32-bit physical addresses. The segment registers **DS** and **ES**
    must be loaded with 0 in order to use 32-bit pointers. The stack is still
    limited to at most 64KB (and the cumulative size of local variables is
    limited to 32KB (this is a per-function limit)) as in regular 16-bit
    *real-address* mode and so **SS** and **SP** should be set up normally.
    Individual functions are limited to approximately 64KB of code size and
    code can reside only in "conventional" DOS memory (first 640KB). These
    limitations should not pose problems normally. To access memory above the
    1MB mark the A20 gate must be enabled. Enabling *unreal* mode can only be
    done when no DOS memory managers such as QEMM, EMM386, etc are loaded.
    Note that *unreal* mode is enabled in *System Management Mode* (SMM).
    Predefines **\_\_SMALLER\_C\_32\_\_** and **\_\_UNREAL\_\_**.
*   **-winstack** (x86 only) This option is to be used together with
    **-seg32**. It causes proper stack growth on Windows by calling an
    equivalent of the Visual C++ **_chkstk()** function to touch/probe stack
    pages and move the process guard page whenever necessary (when a function
    allocates 4096 or more bytes for local variables). If the guard page
    isn't moved, stack accesses beyond it will cause the process to crash.
*   **-no-externs** suppresses generation of **global** and **extern**. This
    may be useful when compiling one or more C files into one or more
    assembly files, concatenating all the assembly files into one and
    assembling it directly into an executable binary without using a linker
    (e.g. using NASM's **-f bin** option).
*   **-label \<number\>** takes the initial number (non-negative integer;
    without the angle brackets) for numbered labels in the generated assembly
    code. Again, this may be useful when compiling one or more C files into
    assembly code and assembling it (possibly, after concatenation of
    multiple assembly files into one) as a single assembly file directly into
    an executable binary without using a linker (e.g. using NASM's **-f bin**
    option). The generated assembly has at its end the **Next label number:**
    string followed by the label number that can be safely used as an input
    into **-label**. This lets you get unique numbered labels in the output
    of multiple runs of the compiler. Beware, **static** variables and
    functions will collide in concatenated assembly files if the same name is
    declared more than once. This option is to be used together with
    **-no-externs**.
*   **-signed-char** This makes **char** signed. This is the **default**.
*   **-unsigned-char** This makes **char** unsigned.
*   **-signed-wchar** This makes **wchar_t** signed.
*   **-unsigned-wchar** This makes **wchar_t** unsigned. This is the
    **default**.
*   **-short-wchar** This makes **wchar_t** short/16-bit. This is the
    **default**.
*   **-long-wchar** This makes **wchar_t** long/32-bit (only in 32-bit, huge
    and unreal mode(l)s).
*   **-leading-underscore** (x86 only) This prefixes global C identifiers
    with an underscore, so you get labels like **_main** for **main()** and
    **_printf** for **printf()** in the assembly code. This is the
    **default**.
*   **-no-leading-underscore** (x86 only; default for **MIPS** ) This results
    in no underscore prefixing of global C identifiers and you get assembly
    labels **main** and **printf** for **main()** and **printf()**
    respectively. This may be useful for compilation using the **ELF** format
    in **Linux**.
*   **-nobss** This causes static variables that are implicitly initialized
    with 0 to be put into the **.data** section instead of the **.bss**
    section.
*   **-I dir** This adds a directory to the include file search path. Can be
    repeated multiple times. Header files in double quotes, e.g.
    **#include "myfile.h"**, are first looked for in the current directory
    (note that the current directory isn't necessarily the same directory
    that contains the file that does #include "myfile.h"), then in the
    directories specified with the **-I** option, then in the directories
    specified with the **-SI** option.
*   **-SI dir** This adds a directory to the system include file search path.
    Can be repeated multiple times. Required for inclusion of system headers
    using angle brackets, e.g. **#include \<stdio.h\>**.
*   **-D macro[=expansion text]** This defines a macro. When the
    **=expansion text** part is omitted, the macro is defined as **1**. Can
    be repeated multiple times.
*   **-Wall** will cause printing of warnings
*   **-verbose** will cause printing of the names of the functions being
    compiled, also includes the **-Wall** option

## How do I compile Smaller C with itself?

It is recommended to compile it via smlrcc (use pre-compiled smlrcc, smlrc,
smlrl and libraries), e.g:

For DOS (huge model):
> smlrcc -dosh -Wall smlrc.c -o smlrcdh.exe

or (DPMI):
> smlrcc -dosp -Wall smlrc.c -o smlrcdp.exe

For Windows:
> smlrcc -win -Wall smlrc.c -o smlrcw.exe

For Linux:
> smlrcc -linux -Wall smlrc.c -o smlrcl

For Linux gcc, targeting **MIPS**:
> smlrcc -linux -D MIPS -Wall smlrc.c -o smlrclmips

**ALSO**, you can now (re)compile Smaller C into a **16-bit DOS .EXE** with a
precompiled/crosscompiled Smaller C, say smlrc.exe, and NASM,
**without any linker**, like this:

> smlrc.exe -nobss -seg16 -no-externs lb.c lb.asm

> smlrc.exe -nobss -seg16 -no-externs -label 1001 -D NO_ANNOTATIONS -D NO_EXTRAS smlrc.c smlrc.asm

> nasm -f bin smlrc16.asm -o smlrc16.exe

The above will produce a DOS executable not supporting the **-seg32**,
**-huge** and **-unreal** options, the **long** integer types, floating-point
types, **typedef**, **enum**, **#pragma pack()**, **\_\_func\_\_**,
declarations in clause-1 of the **for()** statement and passing/returning
structures by value. If you need 32-bit support in Smaller C for DOS or those
features, you can compile it like this instead:

> smlrc.exe -nobss -huge -no-externs lb.c lb.asm

> smlrc.exe -nobss -huge -no-externs -label 1001 smlrc.c smlrc.asm

> nasm -f bin smlrchg.asm -o smlrchg.exe

Similarly, you can now (re)compile Smaller C into a **32-bit Windows .EXE**
with a precompiled/crosscompiled Smaller C, say smlrc.exe, and NASM,
**without any linker**, like this:

> smlrc -nobss -seg32 -no-externs -D _WIN32 lb.c lb.asm

> smlrc -nobss -seg32 -no-externs -label 1001 smlrc.c smlrc.asm

> nasm -f bin mzstub.asm -o mzstub.bin

> nasm -f bin smlrcw.asm -o smlrcw.exe

Likewise, you can now (re)compile Smaller C into a
**32-bit Linux ELF executable** with a precompiled/crosscompiled Smaller C,
say smlrc, and NASM, **without any linker**, like this:

> smlrc -nobss -seg32 -no-externs -D _LINUX lb.c lb.asm

> smlrc -nobss -seg32 -no-externs -label 1001 smlrc.c smlrc.asm

> nasm -f bin smlrcl.asm -o smlrcl

> chmod +x smlrcl

**Note**: If you can't (re)compile Smaller C because it gets too big (e.g.
the code doesn't fit into a 64KB segment when compiling using **-seg16**),
you may want to compile it with several macros pre-defined at compile time.
See those macros below in the miscellaneous section.

To reduce the data size further, compile with the **SYNTAX_STACK_MAX** macro
defined with a smaller number than in the source code (this will limit the
maximum number of declarations supported in a translation unit).

## Miscellaneous

*   If you dislike the annotations that the compiler puts into the assembly
    code that it generates, you can suppress them. Compile the compiler with
    the **NO_ANNOTATIONS** macro defined. This will also reduce the size of
    the compiler.
*   You can disable the primitive preprocessor in smlrc by compiling it with
    the **NO_PREPROCESSOR** macro defined. This may be useful if you're using
    an external preprocessor (which is the case now: smlrpp is invoked for
    preprocessing by default). This will also reduce the size of the core
    compiler.
*   Macro **NO_EXTRA_WARNS** excludes support for generation of extra
    warnings.
*   Macro **NO_TYPEDEF_ENUM** excludes support (and code) for **typedef**/
    **enum**.
*   Macro **NO_FUNC_** excludes support for **\_\_func\_\_**.
*   Macro **NO_PPACK** excludes support for **#pragma pack()**.
*   Macro **NO_FOR_DECL** excludes support for declarations in clause-1 of
    **for()**.
*   Macro **NO_STRUCT_BY_VAL** excludes support for passing and returning
    structures by value.
*   Macro **NO_FP** excludes support for floating point.
*   Macro **NO_EXTRAS** has the effect of defining all of **NO_EXTRA_WARNS**,
    **NO_TYPEDEF_ENUM**, **NO_FUNC_**, **NO_PPACK**, **NO_FOR_DECL**,
    **NO_STRUCT_BY_VAL** and **NO_FP**.
