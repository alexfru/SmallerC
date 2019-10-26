# Smaller C Linker

## Table of contents

[What is Smaller C linker?](#what-is-smaller-c-linker)

[What features does the linker have?](#what-features-does-the-linker-have)

[How do I compile the linker?](#how-do-i-compile-the-linker)

[How do I run the linker?](#how-do-i-run-the-linker)

[Limitations and implementation details](#limitations-and-implementation-details)

## What is Smaller C linker?

Smaller C linker is a linker specifically designed to statically link x86 ELF
object files produced by the Netwide Assembler (AKA NASM) into executable
files (YASM's and FASM's ELFs appear to work as well). The linker can also
link standard archive files containing such x86 ELF object files. The linker
may be used either as part of Smaller C or as a standalone tool. The output
formats are: .COM, .EXE (for DOS), .EXE/PE (for Windows), ELF (for Linux),
Mach-O (for MacOS) and flat executables.

## What features does the linker have?

The linker can produce so-called "map files" that list the sections, the
global public symbols and their addresses in memory and in the output
executable file. These may be extremely useful for debugging since the linker
does not store any debugging/symbolic information in the produced
executables.

You can specify the stack size for the tiny, small, huge and unreal memory
models in DOS executables.

You can override the default name of the entry point symbol.

You can specify the "origin" for Windows, Linux, MacOS and flat executables.
In Windows/PE, Linux/ELF and MacOS/Mach-O executables it's the image base
address, the address at which the PE/ELF/Mach-O headers will be loaded, which
then will be followed by the code and data sections. In flat executables it's
the address/offset at which the first byte of the file will be loaded for
execution. The first byte in flat executables is part of the first executable
instruction. Example: when linking into DOS .COM executables, the implicit
origin is naturally set to 0x100 by the linker itself.

## How do I compile the linker?

Just compile smlrl.c with your favorite 32-bit (or 64-bit?) compiler for a
little-endian platform. No special compilation options should be needed.

The linker should be compiled with a 32-bit-capable compiler because ELF
object files may have sections larger than 64KB and they may not fit into
memory if the linker is compiled into a 16-bit program. If you compile the
linker with Smaller C, you must compile it using the **-seg32** or **-huge**
or **-unreal** options because Smaller C supports 32-bit integer types only
in those memory mode(l)s and the linker makes use of 32-bit integers.

Currently, the linker lacks byte order conversion and will not work with
little-endian x86 ELF object files on a big-endian platform.

## How do I run the linker?

> smlrl \<option(s)\> \<input file(s)\>

where input files are x86 ELF object files with the file extension ".o"
and/or standard archive files (those that you make with the "ar" utility in
Linux/UNIX) with the file extension ".a" and containing x86 ELF object files
inside.

If there are many input files, you can create a special text file listing all
those input files and instead provide that file's name prefixed with the at
(**@**) character. This is especially useful when linking in DOS, where
command lines are restricted to some 120+ characters. You can store linking
options in this file as well. The options and the file names must be
separated by white space (spaces, tabs or new line characters, whichever you
choose). **Note**: currently, spaces in file names aren't supported inside
@-files.

Since the linker supports many output formats and does not know which one is
expected from it, the output format must always be specified explicitly with
the appropriate option (one of: **-tiny**, **-small**, **-huge**,
**-unreal**, **-pe**, **-win**, **-elf**, **-mach**, **-flat16**,
**-flat32**, **-aout**).

Options:
*   **-o \<output executable file\>** Specifies the name of the executable
    file. If this option isn't given, the executable file will be named
    "a.out".
*   **-tiny** Must be specified when linking into DOS .COM programs using the
    tiny memory model (CS=DS=ES=SS, all code, data and stack are in the same
    segment). **Note**: forces section alignment greater than 4 (x86 ELF
    files usually have 16-byte alignment) to 4 to save space.
*   **-small** Must be specified when linking into DOS .EXE programs using
    the small memory model (DS=ES=SS, all data and stack are in the same
    segment, but the code is in a separate segment, CS≠SS). Your program
    should load registers DS and ES with the value of register SS at the time
    of start. See [this example](../tests/lnktst1.asm) and
    [its second part](../tests/lnktst1b.asm). **Note**: forces section
    alignment greater than 4 (x86 ELF files usually have 16-byte alignment)
    to 4 to save space.
*   **-huge** Must be specified when linking into DOS .EXE programs using the
    huge memory model. This model is specific to Smaller C and isn't
    compatible with huge models supported by other DOS compilers. **Note**:
    forces section alignment greater than 4 (x86 ELF files usually have
    16-byte alignment) to 4 to save space.
*   **-unreal** Must be specified when linking into DOS .EXE programs using
    the unreal memory model. This model is specific to Smaller C.
*   **-pe** or **-win** Must be specified when linking into Windows .EXE/PE
    programs. If the linker finds the symbol **\_\_dll_imports**, it will
    create a proper DLL import table. See [this example](../tests/hw0.c) for
    how you could make that happen.
*   **-gui** Makes a GUI executable instead of CUI (console). Merely sets the
    PE subsystem to 2 instead of the default 3. To be used with the options
    **-pe** or **-win**.
*   **-pesubsys \<number\>** Sets the PE subsystem to a given number.
    Primarily for UEFI apps/drivers. To be used with the options **-pe** or
    **-win**.
*   **-elf** Must be specified when linking into Linux/ELF programs.
*   **-mach** Must be specified when linking into MacOS/Mach-O programs.
*   **-norel** Suppresses generation of relocation info in Windows .EXE/PE
    (ELFs and Mach-Os are still non-relocatable).
*   **-flat16** Must be specified when linking into 16-bit flat executables
    similar to DOS .COM programs. If the entry point is not at the very
    beginning, the linker will insert at the beginning a jump instruction to
    the entry point. **Note**: forces section alignment greater than 4 (x86
    ELF files usually have 16-byte alignment) to 4 to save space.
*   **-flat32** Must be specified when linking into 32-bit flat executables.
    If the entry point is not at the very beginning, the linker will insert
    at the beginning a jump instruction to the entry point.
*   **-aout** Must be specified when linking into 32-bit relocatable
    executables in the OMAGIC a.out format. The primary use of this format is
    for 32-bit DOS DPMI programs. The format contains relocation records. If
    you ignore the relocations, the image of the .text and .data sections
    will appear as ready for loading at address 0; so, you can either
    relocate or just load the image of the two sections at the beginning of
    the segment (it's assumed that the code and the data segments overlap and
    have the same base address, IOW, flat configuration). This a.out format
    can be used to create simple relocatable executables (e.g. for one's
    hobby OS), not only for 32-bit DOS/DPMI programs.
*   **-stub \<filename\>** Specifies the MZ .EXE stub name for 32-bit DOS
    DPMI programs. To be used with option **-aout**. The stub will appear at
    the beginning of the output file, next will come the DPMI stub info
    record (with stack and heap size info) and at the end will be the a.out
    part. If this option isn't given, there will be no stub nor stub info
    record in the output file, just a plain a.out image.
*   **-stack \<number\>** Specifies the stack size (in bytes) for the tiny,
    small, huge and unreal DOS memory models. To be used with the options
    **-tiny**, **-small**, **-huge**, **-unreal** and **-aout** (a.out itself
    doesn't have a record for the stack size, the size will be written into
    the DPMI stub info record placed between the DPMI stub and the a.out
    portion of the .EXE). If the option isn't given, the linker assumes
    **8192** for the tiny and small memory models, **32768** for the huge and
    unreal memory models and **65536** for DPMI. The number can be decimal,
    hex or octal (e.g. 8192, 0x2000 and 020000 would all specify the same
    value).
*   **-minheap \<number\>** Specifies the minimum heap size (in bytes) for
    DPMI programs. To be used with options **-aout** and **-stub**. The size
    will be written into the DPMI stub info record. If the option isn't
    given, the linker assumes **524288** (512KB). The number can be decimal,
    hex or octal. If there isn't this much free DPMI memory for the heap, the
    program will abort before reaching \_\_start or main().
*   **-maxheap \<number\>** Specifies the maximum heap size (in bytes) for
    DPMI programs. To be used with options **-aout** and **-stub**. The size
    will be written into the DPMI stub info record. If the option isn't
    given, the linker assumes **16777216** (16MB). The number can be decimal,
    hex or octal. The program may receive a heap whose size is smaller than
    this number (e.g. if there isn't this much free DPMI memory; Windows XP
    can provide up to ~1GB of DPMI memory while Windows Vista/7 is known to
    limit DPMI memory to 32MB).
*   **-map \<somefile.map\>** Creates a map file with the sections and global
    public symbols and their locations in memory and in the output
    executable. This option is only useful for debugging.
*   **-entry \<name\>** Specifies the name of the entry point symbol. If this
    option isn't given, the entry point is assumed to be **\_\_start**. Note
    the two leading underscore characters. If you want a C function to be the
    default entry point, it must be named as either **\_start** (if the
    compiler prepends an underscore character by default or if using
    Smaller C with the option **-leading-underscore**) or **\_\_start** (if
    the compiler does not prepend any underscore characters or if using
    Smaller C with the option **-no-leading-underscore**).
*   **-origin \<number\>** Specifies the origin for the executable file as an
    integer constant, decimal, hex or octal (e.g. 10, 0xA or 012 would all
    specify the same value). In Windows/PE, Linux/ELF and MacOS/Mach-O
    executables it's the image base address, the address in memory at which
    the PE/ELF/Mach-O headers will be loaded, which then will be followed by
    the code and data sections. In flat executables it's the address/offset
    in memory at which the first byte of the file will be loaded for
    execution. The (E)IP register is expected to have this address/offset at
    start. The first byte in flat executables is part of the first executable
    instruction. Example: when linking into DOS .COM executables, the
    implicit origin is naturally set to 0x100 by the linker itself. This
    option should typically be used only when making flat executables. In
    other cases the default origin value chosen by the linker should be
    sufficient.
*   **-nobss** If the linker encounters uninitialized (implicitly initialized
    with 0) sections like **.bss**, it will store them in the output
    executable file as zero bytes.
*   **-verbose** Causes printing of a lot of linking-related information to
    the standard output. You should probably only use this option when you
    run into some problem and need extra info for troubleshooting. Be
    prepared for a lot of output.

## Limitations and implementation details

*   The linker has only been tested with x86 ELF object files produced by
    NASM, YASM and FASM. It may not support object files produced by e.g.
    GNU as or gcc.
*   The linker supports relocation types **R_386_32** (1), **R_386_PC32** (2)
    and their 16-bit extensions **R_386_16** (20) and **R_386_PC16** (21).
*   The linker does not check or warn when 16-bit and 32-bit relocations are
    present at the same time in the input object files. If you mix and match
    16-bit and 32-bit code, you must know what you're doing.
*   The linker does not support **SHT_RELA** relocation sections.
*   The linker does not support weak symbols (**STB_WEAK**).
*   The linker does not support common symbols (**SHN_COMMON**). If you're
    linking object files produced with gcc, you may suppress generation of
    common symbols with the **-fno-common** option and gcc will explicitly
    use the **.bss** section insted.
*   The linker does not support dynamic linking.
*   The linker does not produce relocateable Linux/ELF or MacOS/Mach-O
    executables as of now. Fortunately, Linux and MacOS support
    non-relocateable executables.
*   The linker sorts sections alphabetically within the same type of section
    (type being a combination of code/data, readable/writable, initialized/
    uninitialized). The sections appear in this order: **".text"** (if
    exists), other code sections, read-only data sections (e.g. ".rodata"),
    writable initialized data sections (e.g. ".data"), uninitialized/
    zero-initialized sections (e.g. ".bss"). If in doubt, generate and
    examine the map file.
*   The linker merges all code sections into one code section and all data
    sections into one data section. This may be problematic on Windows, Linux
    and MacOS if you want to make some code sections writable or some data
    sections read-only or executable.
*   The linker aligns and pads sections to the page size (4096 bytes) in
    memory and in the executable file when linking into Windows/PE, Linux/ELF
    and MacOS/Mach-O executables.
*   The linker supports special symbols that mark the start and the end of a
    section. For example, the **".text"** section start and end addresses can
    be found by taking the addresses of the special symbols
    **\_\_start\_\_text** and **\_\_stop\_\_text**. The end address is
    actually the address of the byte immediately following the last byte of
    the section. The dot character in section names is replaced by the
    underscore character when forming these special symbols.  
    There are special symbols marking the start and the end of combined code
    sections and combined data sections. They are: **\_\_start_allcode\_\_**,
    **\_\_stop_allcode\_\_**, **\_\_start_alldata\_\_**,
    **\_\_stop_alldata\_\_**.  
    There also exist a pseudo section for the stack portion of the data
    segment in the tiny and small 16-bit DOS memory models. Its start address
    can be found by taking the address of the special symbol
    **\_\_start_stack\_\_**. This pseudo section is located at the end of the
    64KB data segment. The **-stack** option affects the address of the
    **\_\_start_stack\_\_** symbol. The symbols **\_\_stop_alldata\_\_** and
    **\_\_start_stack\_\_** can be used to create a memory heap between the
    two locations.
*   When making a Windows/PE executable the linker treats specially sections
    whose names begin with **.dll_import** and **.dll_iat**.
    These sections construct the DLL import tables and the linker won't
    generate relocation information for the data contained in them. Also
    special are symbols **\_\_dll_imports**, **\_\_dll_imports_end**,
    **\_\_dll_iats**, **\_\_dll_iats_end**. Don't use these names.
