SmallerC is a simple and small single-pass C compiler.

Currently it generates 16-bit 80386+ assembly code for NASM,
which can later be assembled and linked into DOS .COM or .EXE programs.

The compiler is capable of compiling its own source code.

Supported Features: 
- void
- char
- int
- functions
- arrays & pointers of/to those
- sizeof expression, sizeof(type)
- char/string literals (with limited concatenation of adjacent string literals: "str" MACRO doesn't work when MACRO is "str2")
- decimal/octal/hex constants
- all "normal" operators (except ?: and comma)
- simple constant initialization of global variables (again, except arrays)
- variadic functions (w/o va_something macros)
- global/local declarations and prototypes
- expressions
- {}-statement
- if/else
- while/do/for/break/continue
- switch/case/default (simplified to only support what you usually see or write, no weird stuff)
- return
- limited #define

Currently Unsupported Features and Limitations:
- sizeof(int) = sizeof(void*) = sizeof(void(*)()), IOW, ints and pointers are same size
- most of the preprocessor
- enums/longs/(un)signeds
- floating-point
- constant prefixes and suffixes (U, L, F)
- casts
- typedef/struct/union
- const/volatile/static
- array initialization
- complex initialization of global pointers (e.g. p = &array[3]; )
- comma operator
- ?:
- goto
- weird switch() statements
- variable declarations inside for(here;; )
- redeclaration checks (int i, i; is valid, first i is obscured by second)
- duplicate case const: checks
- difference between 2 pointers
- checks for missing return at function end
- incomplete types/arrays (e.g. extern int blah[]; )
- type checks in assignment and parameter passing (char, int, T* can be assigned to one another or passed as one another)
- VLAs
- K&R syntax

How to compile the compiler with Turbo C++ 1.01 in DOS/DosBox:
 1. Just do it:
    tcc.exe __cmplr.c

How to compile the compiler with itself:
 1. Compile __cmplr.c with a C compiler of your choice (Turbo C/C++, Open Watcom C/C++, etc)
    and get the executable, e.g. __cmplr_OpenWatcom.exe
 2. Compile the compiler with itself, e.g.:
    __cmplr_OpenWatcom.exe __cmplr.c >__cmplr.asm
 3. Assemble the compiler's asm code with NASM:
    nasm.exe -g -f obj __cmplr.asm
 4. Use Turbo C++ 1.01 (effectively, its libraries and Turbo Linker) to make the .EXE:
    tcc.exe __cmplr.obj
