# Smaller C Compiler Driver

## Table of contents

[What is Smaller C Compiler Driver?](#what-is-smaller-c-compiler-driver)

[What features does Smaller C Compiler Driver have?](#what-features-does-smaller-c-compiler-driver-have)

[How do I compile Smaller C Compiler Driver?](#how-do-i-compile-smaller-c-compiler-driver)

[How do I run Smaller C Compiler Driver?](#how-do-i-run-smaller-c-compiler-driver)

[Limitations and implementation details](#limitations-and-implementation-details)

## What is Smaller C Compiler Driver?

Smaller C Compiler Driver (henceforth, driver) is a utility that simplifies
the use of the Smaller C Core Compiler. It invokes the preprocessor (smlrpp
by default), the core compiler (smlrc), the assembler (nasm by default) and
the linker (smlrl) as necessary and with appropriate parameters, making it
easier to do common compilation tasks. It is expected to be the primary user
interface for the compiler as a whole.

## What features does Smaller C Compiler Driver have?

The driver functions similarly to gcc, letting the user:
*   Compile, or, more appropriately, translate C files into assembly files
    for further compilation into object files or for inspection and
    troubleshooting
*   Compile C and assembly files into object (x86 ELF) files, optionally
    storing the object files into a standard archive file that can then be
    used as a library
*   Link object and archive files into DOS, Windows, Linux, MacOS and flat
    executables
*   Compile and link C, assembly, object and archive files into executables,
    all in one command
*   Specify compilation options and define macros at compile time (as opposed
    to defining the macros in the source code)

## How do I compile Smaller C Compiler Driver?

Use your favorite C compiler (or Smaller C itself). You will need to define
one of the following macros at compile time to compile for the host platform
of the choice: HOST_DOS, HOST_WINDOWS, HOST_LINUX, HOST_MACOS. The host
platform is the platform, where you intend to run the driver and the entire
Smaller C. For example, you could do it like this:

> gcc -Wall -Wextra -O2 -DHOST_LINUX smlrcc.c -o smlrcc

or

> smlrcc -Wall -dosh -DHOST_DOS smlrcc.c -o smlrcc.exe

Irrespective of the host platform, the driver and the rest of Smaller C are
able to target (that is, compile and link for) all other platforms.

## How do I run Smaller C Compiler Driver?

Typically, you run it like this:

> smlrcc [option(s)] \<input file(s)\>

If there are many input files, you can create a special text file listing all
those input files and instead provide that file's name prefixed with the at
(@) character. This is especially useful when compiling in DOS, where command
lines are restricted to some 120+ characters, and when creating an archive
file (library) out of many files. You can store the options in this file as
well. The options and the file names must be separated by white space
(spaces, tabs or new line characters, whichever you choose). Note: currently,
spaces in file names aren't supported inside @-files.

Some basic examples follow.

Compile several source files (and link together with the standard library)
into a DOS executable:

> smlrcc -dosh file1.c file2.asm -o file12.exe

Compile one or more source files into object files:

> smlrcc -dosh -c file1.c -o file1.o

> smlrcc -dosh -c file1.c file2.asm

Link several object files (together with the standard library) into a
Windows executable:

> smlrcc -win file3.o file4.o -o file34.exe

Compile several source files into a DOS library (note the -c option and the
.a extension):

> smlrcc -dosh -c file5.c file6.c file7.asm -o lib567.a

Compile one or more C files into assembly files (note the -S option):

> smlrcc -linux -c -S file8.c -o file8.asm

> smlrcc -linux -c -S file8.c file9.c

**Input file types**:
*   **.c**: C source code (unpreprocessed C code, will be preprocessed with
    smlrpp, can be preprocessed with gcc alternatively)
*   **.i**: C source code (preprocessed C code)
*   **.asm**: assembly source code (for NASM/YASM/n2f)
*   **.o**: 16/32-bit x86 ELF object file (produced with NASM's/YASM's/n2f's
    **-f elf** option)
*   **.a**: library/archive containing **.o** files

**Options**:
*   **-ppg** Invokes gcc to preprocess C files. Alternatively, you can set
    the environment variable **SMLRPPG** to avoid passing -ppg to smlrcc
    every time. The variable's value doesn't matter an the moment, but you
    may set **SMLRPPG=gcc**. You shouldn't need to use this option now that
    Smaller C comes with a preprocessor of its own, smlrpp (a version of ucpp
    adapted for Smaller C).
*   **-nopp** Suppresses preprocessing with the external preprocessor (smlrpp
    or gcc) and relies on the primitive preprocessor in smlrc. You shouldn't
    normally use this option, however it may save time when compiling the
    Smaller C standard library, which needs very little preprocessing.
*   **-o \<output assembly/object/archive/executable file\>** Specifies the
    name of the output file. If you're making an executable and this option
    isn't given, the executable file will be named **aout.com** (if you use
    **-dost** or **-tiny**), **aout.exe** (if you use **-doss**, **-small**,
    **-dosh**, **-huge**, **-dosu**, **-unreal**, **-dosp**, **-win** or
    **-pe**), **a.out** (if you use **-aout**, **-linux**, **-elf** or
    **-macos**) or **aout.bin** (if you use **-flat16** or **-flat32**). If
    you're compiling to an object file and this option isn't given, the
    object file will be named the same as the input file but will have the
    **.o** extension. Likewise, if you're translating C code to assembly code
    (for that you need the **-c** and **-S** options) and this option isn't
    given, the assembly file will be named the same as the C file but will
    have the **.asm** extension.
*   **-stack \<number\>** (passed to the linker) Specifies the stack size (in
    bytes) for the tiny, small, huge and unreal DOS memory models. To be used
    with the options **-dost**, **-tiny**, **-doss**, **-small**, **-dosh**,
    **-huge**, **-dosu**, **-unreal**, **-dosp**. If the option isn't given,
    the linker assumes **8192** for the tiny and small memory models,
    **32768** for the huge and unreal memory models and **65536** for DPMI.
    The number can be decimal, hex or octal (e.g. 8192, 0x2000 and 020000
    would all specify the same value).
*   **-minheap \<number\>** Specifies the minimum heap size (in bytes) for
    DPMI programs. To be used with option **-dosp**. If the option isn't
    given, the linker assumes **524288** (512KB). The number can be decimal,
    hex or octal. If there isn't this much free DPMI memory for the heap, the
    program will abort before reaching \_\_start or main().
*   **-maxheap \<number\>** Specifies the maximum heap size (in bytes) for
    DPMI programs. To be used with option **-dosp**. If the option isn't
    given, the linker assumes **16777216** (16MB). The number can be decimal,
    hex or octal. The program may receive a heap whose size is smaller than
    this number (e.g. if there isn't this much free DPMI memory; Windows XP
    can provide up to ~1GB of DPMI memory while Windows Vista/7 is known to
    limit DPMI memory to 32MB).
*   **-map \<somefile.map\>** (passed to the linker) Creates a map file of
    the output executable listing the sections and global public symbols and
    their locations in memory and in the executable. This option is only
    useful for debugging.
*   **-entry \<name\>** (passed to the linker) Specifies the name of the
    entry point symbol. If this option isn't given, the entry point is
    assumed to be **\_\_start**. Note the two leading underscore characters.
    If you want a C function to be the default entry point, it must be named
    as either **_start** (Smaller C prepends an underscore character by
    default) or **\_\_start** (if using Smaller C with the option
    **-no-leading-underscore**).
*   **-origin \<number\>** (passed to the linker) Specifies the origin for
    the executable file as an integer constant, decimal, hex or octal (e.g.
    10, 0xA or 012 would all specify the same value). In Windows/PE,
    Linux/ELF and MacOS/Mach-O executables it's the image base address, the
    address in memory at which the PE/ELF/Mach-O headers will be loaded,
    which then will be followed by the code and data sections. In flat
    executables it's the address/offset in memory at which the first byte of
    the file will be loaded for execution. The (E)IP register is expected to
    have this address/offset at start. The first byte in flat executables is
    part of the first executable instruction. Example: when linking into DOS
    .COM executables, the implicit origin is naturally set to 0x100 by the
    linker itself. This option should typically be used only when making flat
    executables (see options **-flat16** and **-flat32**). In other cases the
    default origin value chosen by the linker should be sufficient.
*   **-nobss** This option will be passed down to the core compiler and to
    the linker. The net effect will be that of having no run-time-initialized
    **.bss** section and having load-time initialization like in the
    **.data** section with all data taken by the loader from the executable.
*   **-v** or **-verbose** prints commands executed during compilation (i.e.
    commands that invoke the core compiler, the assembler and the linker).
    May be useful for troubleshooting or monitoring compilation progress.
*   **-signed-char** (passed to the core compiler) This makes **char**
    signed. This is the **default**.
*   **-unsigned-char** (passed to the core compiler) This makes **char**
    unsigned.
*   **-signed-wchar** (passed to the core compiler) This makes **wchar_t**
    signed. This is the **default** for **-elf**, **-linux**, **-macos**.
*   **-unsigned-wchar** (passed to the core compiler) This makes **wchar_t**
    unsigned. This is the **default** for **-tiny**, **-dost**, **-small**,
    **-doss**, **-huge**, **-dosh**, **-unreal**, **-dosu**, **-aout**,
    **-dosp**, **-pe**, **-win**, **-flat16**, **-flat32**.
*   **-short-wchar** (passed to the core compiler) This makes **wchar_t**
    short/16-bit. This is the **default** for **-tiny**, **-dost**,
    **-small**, **-doss**, **-huge**, **-dosh**, **-unreal**, **-dosu**,
    **-aout**, **-dosp**, **-pe**, **-win**, **-flat16**, **-flat32**.
*   **-long-wchar** (passed to the core compiler) This makes **wchar_t**
    long/32-bit (only in 32-bit, huge and unreal mode(l)s). This is the
    **default** for **-elf**, **-linux**, **-macos**.
*   **-leading-underscore** (passed to the core compiler) This prefixes
    global C identifiers with an underscore, so you get labels like **_main**
    for **main()** and **_printf** for **printf()** in the generated assembly
    and object code. This is the **default**.
*   **-no-leading-underscore** (passed to the core compiler) This results in
    no underscore prefixing of global C identifiers and you get assembly
    labels **main** and **printf** for **main()** and **printf()**
    respectively. This may be useful for compilation using the ELF format in
    Linux. This makes object/library files compatible with gcc on Linux.
*   **-winstack** (passed to the core compiler) This option is to be used
    together with **-pe** and is automatically included by the **-win**
    option. It causes proper stack growth on Windows by calling an equivalent
    of the Visual C++ **_chkstk()** function to touch/probe stack pages and
    move the process guard page whenever necessary (when a function allocates
    4096 or more bytes for local variables). If the guard page isn't moved,
    stack accesses beyond it will cause the process to crash.
*   **-Wall** (passed to the core compiler) will cause printing of
    compilation warnings.
*   **-8086** On 16-bit modes generate 8086 compatible instructions insted of
    386 instructions.
*   **-dost** Selects the tiny memory model for DOS .COM programs
    (CS=DS=ES=SS, all code, data and stack are in the same segment). The
    types **long**, **float**, **double** aren't available in this model.
    Passes **-seg16** to the core compiler and **-tiny** to the linker.
    Additionally passes **-D _DOS** to the compiler and, if you're making an
    executable, it causes the standard library (**lcds.a**) to be linked in.
*   **-tiny** Same as **-dost**, except **-D _DOS** isn't passed to the
    compiler and the standard library isn't linked.
*   **-doss** Selects the small memory model for DOS .EXE programs (DS=ES=SS,
    all data and stack are in the same segment, but the code is in a separate
    segment, CS≠SS). The types **long**, **float**, **double** aren't
    available in this model. Passes **-seg16** to the core compiler and
    **-small** to the linker. Additionally passes **-D _DOS** to the compiler
    and, if you're making an executable, it causes the standard library
    (**lcds.a**) to be linked in.
*   **-small** Same as **-doss**, except **-D _DOS** isn't passed to the
    compiler and the standard library isn't linked.
*   **-dosh** Selects the huge memory model for DOS .EXE programs. This model
    is specific to Smaller C and isn't compatible with huge models supported
    by other DOS compilers. Passes **-huge** to the core compiler and
    **-huge** to the linker. Additionally passes **-D _DOS** to the compiler
    and, if you're making an executable, it causes the standard library
    (**lcdh.a**) to be linked in.
*   **-huge** Same as **-dosh**, except **-D _DOS** isn't passed to the
    compiler and the standard library isn't linked.
*   **-dosu** Selects the unreal memory model for DOS .EXE programs. This
    model is specific to Smaller C. Passes **-unreal** to the core compiler
    and **-unreal** to the linker. Additionally passes **-D \_\_UNREAL\_\_**
    and **-D _DOS** to the compiler and, if you're making an executable, it
    causes the standard library (**lcdu.a**) to be linked in.
*   **-unreal** Same as **-dosu**, except **-D _DOS** isn't passed to the
    compiler and the standard library isn't linked.
*   **-dosp** Selects compilation into a 32-bit DOS DPMI .EXE program. Passes
    **-aout** and **-stub \<path\>dpstub.exe** to the linker. Additionally
    passes **-D _DOS** and **-D _DPMI** to the compiler and, if you're making
    an executable, it causes the standard library (**lcdp.a**) to be linked
    in.
*   **-stub \<filename\>** Specifies the name of an alternative (to
    **dpstub.exe**) MZ .EXE stub for 32-bit DOS DPMI programs. To be used
    with option **-dosp**.
*   **-win** Selects Windows .EXE as the target. Passes **-seg32** and
    **-winstack** to the core compiler and **-pe** to the linker.
    Additionally passes **-D _WINDOWS** to the compiler and, if you're making
    an executable, it causes the standard library (**lcw.a**) to be linked
    in.
*   **-pe** Same as **-win**, except neither **-winstack** nor
    **-D _WINDOWS** is passed to the compiler and the standard library isn't
    linked.
*   **-gui** Makes a GUI executable instead of CUI (console). Merely sets the
    PE subsystem to 2 instead of the default 3. To be used with the options
    **-pe** or **-win**. Passes **-gui** to the linker.
*   **-pesubsys \<number\>** Sets the PE subsystem to a given number.
    Primarily for UEFI apps/drivers. To be used with the options **-pe** or
    **-win**. Passes **-pesubsys \<number\>** to the linker.
*   **-linux** Selects Linux/ELF as the target. Passes **-seg32** to the core
    compiler and **-elf** to the linker. Additionally passes **-D _LINUX** to
    the compiler and, if you're making an executable, it causes the standard
    library (**lcl.a**) to be linked in.
*   **-elf** Same as **-linux**, except **-D _LINUX** isn't passed to the
    compiler and the standard library isn't linked.
*   **-macos** Selects MacOS/Mach-O as the target. Passes **-seg32** to the
    core compiler and **-mach** to the linker. Additionally passes
    **-D _MACOS** to the compiler and, if you're making an executable, it
    causes the standard library (**lcm.a**) to be linked in.
*   **-norel** Suppresses generation of relocation info in Windows .EXE/PE
    programs (ELFs and Macho-Os are still non-relocatable). Passes **-norel**
    to the linker.
*   **-flat16** Similar to **-tiny** and is useful for making flat 16-bit
    binaries similar to DOS .COM programs having the tiny memory model
    (CS=DS=ES=SS, all code, data and stack are in the same segment). The
    default origin is 0, but can be changed (see the **-origin** option). The
    types **long**, **float**, **double** aren't available in this model.
    Passes **-seg16** to the core compiler and **-flat16** to the linker. If
    the entry point is not at the very beginning, the linker will insert at
    the beginning a jump instruction to the entry point. The standard library
    isn't linked.
*   **-flat32** Similar to **-flat16**, but 32-bit and the types **long**,
    **float**, **double** are available in this model. Can be useful for
    creating simple 32-bit hobby OSes or something similar. The default
    origin is 0, but can be changed (see the **-origin** option). Passes
    **-seg32** to the core compiler and **-flat32** to the linker. If the
    entry point is not at the very beginning, the linker will insert at the
    beginning a jump instruction to the entry point. The standard library
    isn't linked.
*   **-aout** Selects compilation into 32-bit relocatable executables in the
    OMAGIC a.out format (this is what's behind the **-dosp** option). The
    format contains relocation records. If you ignore the relocations, the
    image of the .text and .data sections will appear as ready for loading at
    address 0; so, you can either relocate or just load the image of the two
    sections at the beginning of the segment (it's assumed that the code and
    the data segments overlap and have the same base address, IOW, flat
    configuration). Passes **-seg32** to the core compiler and **-aout** to
    the linker. The standard library isn't linked. Can be useful for creating
    simple 32-bit hobby OSes or something similar.
*   **-asm \<assembler\>** chooses the assembler to use. You can specify
    nasm\[.exe\], yasm\[.exe\] or n2f\[.exe\] (n2f is a wrapper around
    fasm\[.exe\], which makes fasm usable as nasm). You can also set the
    **SMLRASM** environment variable to the assembler name to free yourself
    from having to use the -asm option explicitly every type. Note that -asm
    takes precedence over SMLRASM. If neither method is in use, the good old
    default nasm\[.exe\] is in effect. In DOS don't omit the **.exe**
    extension (this helps the compiler driver to detect compilation errors in
    subordinate executables and stop compilation as soon as possible).
*   **-c** Skip linking, compile only. If used together with the **-o**
    option and the output name ends in **.a**, a library is created out of
    the object files.
*   **-S** Compile to assembly instead of to object file(s). To be used with
    **-c**.
*   **-I\<path\>** (passed to the core compiler) This adds a directory to the
    include file search path. This is for **#include "file.h"** kind of
    includes.
*   **-SI\<path\>** (passed to the core compiler) This adds a directory to
    the system include file search path. This is for **#include \<stdio.h\>**
    kind of includes. Paths provided using this option take precedence over
    (are searched by the core compiler before) the path that the driver may
    find using the environment variables and the path to smlrcc.exe.
*   **-D\<macro[=expansion text]\>** (passed to the core compiler) This
    defines a macro. When the **=expansion text** part is omitted, the macro
    is defined as **1**.
*   **-SL\<path\>** This tells the driver where to look for the standard
    library (**lcds.a**, **lcdh.a**, **lcdu.a**, **lcdp.a**, **lcw.a**,
    **lcl.a** or **lcm.a**) and the default DPMI stub (**dpstub.exe**)
    instead of the default location. The linker doesn't perform any search
    and must be given all input files explicitly.

If you don't specify any of the file format options (**-dost**, **-tiny**,
**-doss**, **-small**, **-dosh**, **-huge**, **-dosu**, **-unreal**,
**-dosp**, **-win**, **-pe**, **-linux**, **-elf**, **-macos**, **-flat16**,
**-flat32**, **-aout**), smlrcc will act as if you specified **-dosh** or
**-win** or **-linux** or **-macos**, depending on how smlrcc was compiled
(with **HOST_DOS**, **HOST_WINDOWS**, **HOST_LINUX** or **HOST_MACOS** macro
defined). IOW, by default smlrcc will target the host platform, where it's
running.

## Limitations and implementation details

*   **File names**: Avoid using non-alphanumeric characters (i.e. other than
    0-9, a-z, A-Z, _), especially spaces in input and output file names and
    paths. This may not work due to command expansion in the shell.
*   **Lengths of file and path names**: Avoid using long paths or putting
    Smaller C files far away from the root directory of the disk. Paths are
    naturally short in DOS and so is the DOS command line. Further, the
    lengths of file names in the core compiler are currently fixed. Placing
    Smaller C files in C:\\SMLRC\\BIND, C:\\SMLRC\\INCLUDE, C:\\SMLRC\\LIB
    should work fine in DOS. Stick with that.
*   **Intermediate/temporary files**: Unless you specify the name of the
    output assembly/object file for every file you compile with smlrcc,
    smlrcc will by default create the assembly/object file in the same
    directory as the input C/assembly file and name it the same way, except
    for the name extension. This means two things. First, the project
    directory with the source code must be writable and must have enough
    space (generated assembly files can get as large as hundreds of kilobytes
    or a couple of megabytes). Second, you should avoid naming your C and
    assembly source files in exactly the same way, e.g. file123.c and
    file123.asm. file123.asm will be overwritten during compilation of
    file123.c.
*   **#include "header.h"**: the file header.h will be first searched for in
    the current directory and only then at locations provided with the **-I**
    and **-SI** options. Note that the current directory isn't necessarily
    the same directory that contains the file that does #include "header.h".
*   **Location of system header and library files** under **DOS** and
    **Windows**: smlrcc will first look for files **limits.h** and **lc\*.a**
    under **%SMLRC%/include** and **%SMLRC%/lib**, where %SMLRC% is the value
    of the environment variable SMLRC. If it doesn't find them there, it will
    look for them under **SMLRCC_PATH/../include**, **SMLRCC_PATH/../lib**,
    where SMLRCC_PATH is the location of smlrcc.exe itself. If limits.h isn't
    found, smlrcc won't pass **-SI\<path_to_limits.h\>** to the core
    compiler, which will likely result in a compilation error, unless the
    proper **-SI\<path\>** option is given to smlrcc. If the standard library
    isn't found and the **-SL\<path\>** option isn't given to smlrcc, the
    standard library won't be linked in, potentially causing a linking error.
    **Note** also, if you compile smlrcc.c into smlrcc.exe in the current
    directory and the compilation succeeds, the next invocation of smlrcc.exe
    may fail if smlrcc.exe from the current directory starts looking for the
    system files relatively to the current directory and fails to find them
    and the proper **-SI\<path\>** option isn't given to smlrcc.exe. You may
    need to use a different output name for the executable or prefix it with
    a path to a directory other than the current to avoid this issue. You
    could rename or move the freshly compiled smlrcc.exe as well.
*   **Location of system header and library files** under **Linux** and
    **MacOS**: smlrcc will first look for files **limits.h** and **lc\*.a**
    under **$SMLRC/include** and **$SMLRC/lib**, where $SMLRC is the value of
    the environment variable SMLRC. If it doesn't find them there, it will
    next look for them under **$HOME/smlrc/include** and **$HOME/smlrc/lib**,
    where $HOME is the value of the environment variable HOME, IOW, the
    user's home directory. If it doesn't find them there, it will look for
    them under **/usr/local/smlrc/include** and **/usr/local/smlrc/lib**. If
    limits.h isn't found, smlrcc won't pass **-SI\<path_to_limits.h\>** to
    the core compiler, which will likely result in a compilation error,
    unless the proper **-SI\<path\>** option is given to smlrcc. If the
    standard library isn't found and the **-SL\<path\>** option isn't given
    to smlrcc, the standard library won't be linked in, potentially causing
    a linking error.
*   **NASM**: you need NASM **2.03** or better (as it will be able to choose
    the short and the long forms of jumps automatically as necessary).
*   **YASM**: you need YASM **1.3.0** or better. YASM is noticeably faster on
    large files than NASM (probably because of its "*fast jump size
    optimizer*").
*   **FASM**: you need FASM **1.71.22** or better. FASM is faster than NASM
    and much smaller than NASM and YASM. However, FASM won't assemble 16-bit
    code into ELF, which makes it impossible to use with Smaller C for the
    tiny, small, huge and unreal DOS memory models. FASM is only suitable for
    compiling 32-bit protected mode code, namely DOS/DPMI32, Windows, Linux
    and MacOS.
*   **CWSDPMI**: you may need CWSDPMI 1.5 or better to run the DPMI version
    of the compiler under DOS and to run DPMI programs produced with it
    (option **-dosp**). Alternatively you may use
    [Japheth's HX DOS Extender (HDPMI32.EXE) 2.16 or 2.17](https://web.archive.org/web/20141003032346/http://www.japheth.de/).
