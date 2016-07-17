Smaller C is a simple and small single-pass C compiler,
currently supporting most of the C language common between C89/ANSI C
and C99 (minus some C89 and plus some C99 features).

Currently it generates 16-bit and 32-bit 80386+ assembly code for NASM
that can then be assembled and linked into DOS, Windows and Linux programs.
(You may use YASM or FASM instead of NASM)

Code generation for MIPS CPUs is also supported (primarily for RetroBSD).

Code generation for the TR3200 CPU and VASM is supported (see Trillek).

The compiler is capable of compiling itself.

The core compiler comes with a preprocessor (ucpp), a linker and a compiler
driver (the driver invokes the preprocessor, the core compiler, the assembler,
and the linker and supports options similar to those of gcc).

The standard C library is work-in-progress and it's close to completion.

See the Wiki for more up-to-date details:
http://github.com/alexfru/SmallerC/wiki

For the lack of a better place, you can discuss Smaller C here:
https://hackaday.io/project/5569-smaller-c

Links:
NASM: http://nasm.us/
YASM: http://yasm.tortall.net/
FASM: http://flatassembler.net/
CWSDPMI: http://homer.rice.edu/~sandmann/cwsdpmi/
HX DOS Extender: https://web.archive.org/web/20141003032346/http://www.japheth.de/
RetroBSD: http://retrobsd.org/
VASM: http://sun.hasenbraten.de/vasm/
Trillek: http://trillek.org/

Other projects based on/using Smaller C:
NewBasic Compiler: http://fysnet.net/nbc.htm
Sweet32 CPU and toolchain: https://github.com/Basman74/Sweet32-CPU

Normative and other useful documents on C:
C99 + TC1 + TC2 + TC3, WG14 N1256:
  http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1256.pdf
Dave Prosser's C preprocessing algorithm annotated by Diomidis D. Spinellis:
  http://www.spinellis.gr/blog/20060626/index.html
Rationale for C99:
  http://www.open-std.org/jtc1/sc22/wg14/www/docs/C99RationaleV5.10.pdf
The New C Standard: An Economic and Cultural Commentary:
  http://www.knosof.co.uk/cbook/cbook.html
The Development of the C Language by Dennis M. Ritchie:
  https://www.bell-labs.com/usr/dmr/www/chist.html
