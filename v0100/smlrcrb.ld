OUTPUT_FORMAT("elf32-tradlittlemips")
OUTPUT_FORMAT("elf32-tradlittlemips")
OUTPUT_ARCH(pic32mx)

ENTRY(_start)

MEMORY
{
  /* 96K internal CPU RAM */
  cpu_ram   (rwx)  : ORIGIN = 0x7F008000, LENGTH = 0x18000
}

SECTIONS
{
  /* Code Sections */

  . = ORIGIN(cpu_ram);

  .startup : /* contains code */
  {
    KEEP (*(.startup))
  } > cpu_ram

  .text ALIGN(32):
  {
    _text_begin = .;
    *(.text .stub .text.* .gnu.linkonce.t.*)
    KEEP (*(.text.*personality*))
    *(.gnu.warning)
    *(.mips16.fn.*)
    *(.mips16.call.*)
    . = ALIGN(32);
    _text_end = .;
  } > cpu_ram = 0

  /* Various initialization/finalization constructor/destructor sections */

  .init : /* contains code, right? */
  {
    KEEP (*crti.o(.init))
    KEEP (*crtbegin.o(.init))
    KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o *crtn.o ).init))
    KEEP (*crtend.o(.init))
    KEEP (*crtn.o(.init))
  } > cpu_ram

  .fini : /* contains code, right? */
  {
    KEEP (*(.fini))
  } > cpu_ram

  .preinit_array : /* contains data, right? */
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } > cpu_ram

  .init_array : /* contains data, right? */
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array))
    PROVIDE_HIDDEN (__init_array_end = .);
  } > cpu_ram

  .fini_array : /* contains data, right? */
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } > cpu_ram

  .ctors : /* contains data */
  {
    /* gcc uses crtbegin.o to find the start of
       the constructors, so we make sure it is
       first.  Because this is a wildcard, it
       doesn't matter if the user does not
       actually link against crtbegin.o; the
       linker won't look for a file to match a
       wildcard.  The wildcard also means that it
       doesn't matter which directory crtbegin.o
       is in. */
    KEEP (*crtbegin.o(.ctors))
    KEEP (*crtbegin?.o(.ctors))
    /* We don't want to include the .ctor section from
       the crtend.o file until after the sorted ctors.
       The .ctor section from the crtend file contains the
       end of ctors marker and it must be last */
    KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
  } > cpu_ram

  .dtors : /* contains data */
  {
    KEEP (*crtbegin.o(.dtors))
    KEEP (*crtbegin?.o(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
  } > cpu_ram

  .preinit_array : /* contains data, right? */
  {
    KEEP (*(.preinit_array))
  } > cpu_ram

  /* Data Sections */

  /* Read-only sections */

  /*
   * Small initialized constant global and static data can be placed in the
   * .sdata2 section.  This is different from .sdata, which contains small
   * initialized non-constant global and static data.
   */
  .sdata2 ALIGN(4):
  {
    *(.sdata2 .sdata2.* .gnu.linkonce.s2.*)
    . = ALIGN(4);
  } > cpu_ram

  /*
   * Uninitialized constant global and static data (i.e., variables which will
   * always be zero).  Again, this is different from .sbss, which contains
   * small non-initialized, non-constant global and static data.
   */
  .sbss2 ALIGN(4):
  {
    *(.sbss2 .sbss2.* .gnu.linkonce.sb2.*)
    . = ALIGN(4);
  } > cpu_ram

  .dbg_data (NOLOAD):
  {
    . += (DEFINED (_DEBUGGER) ? 0x200 : 0x0);
  } > cpu_ram

  /* Persistent data */
  .persist ALIGN(4):
  {
    _persist_begin = .;
    *(.persist .persist.*)
    . = ALIGN(4);
    _persist_end = .;
  } > cpu_ram

/* !!! .rodata moved from code sections !!! */
  .rodata ALIGN(4):
  {
    *(.rodata .rodata.* .gnu.linkonce.r.*)
    *(.rodata1)
    . = ALIGN(4);
  } > cpu_ram

  _data_begin = .;
  .data ALIGN(4):
  {
    *(.data .data.* .gnu.linkonce.d.*)
    KEEP (*(.gnu.linkonce.d.*personality*))
    *(.data1)
    . = ALIGN(4);
  } > cpu_ram

  . = .;
  _gp = ALIGN(16) + 0x7ff0;
  .got ALIGN(4):
  {
     *(.got.plt) *(.got)
  } > cpu_ram

  /*
   * We want the small data sections together, so single-instruction offsets
   * can access them all, and initialized data all before uninitialized, so
   * we can shorten the on-disk segment size.
   */
  .sdata ALIGN(4):
  {
    _sdata_begin = .;
    *(.sdata .sdata.* .gnu.linkonce.s.*)
    _sdata_end = .;
  } > cpu_ram
  .lit8 :
  {
    *(.lit8)
  } > cpu_ram
  .lit4 :
  {
    *(.lit4)
  } > cpu_ram
  . = ALIGN(4);
  _data_end = .;

  _bss_begin = .;
  .sbss ALIGN(4):
  {
    _sbss_begin = .;
    *(.dynsbss)
    *(.sbss .sbss.* .gnu.linkonce.sb.*)
    *(.scommon)
    . = ALIGN(4);
    _sbss_end = .;
  } > cpu_ram

  .bss ALIGN(4):
  {
    *(.dynbss)
    *(.bss .bss.* .gnu.linkonce.b.*)
    *(COMMON)
    /*
     * Align here to ensure that the .bss section occupies space up to
     * _end.  Align after .bss to ensure correct alignment even if the
     * .bss section disappears because there are no input sections.
     */
    . = ALIGN(4);
  } > cpu_ram
  . = ALIGN(4);
  _bss_end = .;

  _end = .;

  /* The .pdr section belongs in the absolute section */
  /DISCARD/ : { *(.pdr) }
  /* We don't load .reginfo onto the target, so don't locate it
   * in real memory
   */
  /DISCARD/ : { *(.reginfo) }

  /* Stabs debugging sections. */
  .stab          0 : { *(.stab) }
  .stabstr       0 : { *(.stabstr) }
  .stab.excl     0 : { *(.stab.excl) }
  .stab.exclstr  0 : { *(.stab.exclstr) }
  .stab.index    0 : { *(.stab.index) }
  .stab.indexstr 0 : { *(.stab.indexstr) }
  .comment       0 : { *(.comment) }
  /* DWARF debug sections.
     Symbols in the DWARF debugging sections are relative to the beginning
     of the section so we begin them at 0. */
  /* DWARF 1 */
  .debug          0 : { *(.debug) }
  .line           0 : { *(.line) }
  /* GNU DWARF 1 extensions */
  .debug_srcinfo  0 : { *(.debug_srcinfo) }
  .debug_sfnames  0 : { *(.debug_sfnames) }
  /* DWARF 1.1 and DWARF 2 */
  .debug_aranges  0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  /* DWARF 2 */
  .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
  .debug_abbrev   0 : { *(.debug_abbrev) }
  /DISCARD/         : { *(.debug_line) }
  .debug_frame    0 : { *(.debug_frame) }
  .debug_str      0 : { *(.debug_str) }
  /DISCARD/         : { *(.debug_loc) }
  .debug_macinfo  0 : { *(.debug_macinfo) }
  /* SGI/MIPS DWARF 2 extensions */
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames  0 : { *(.debug_varnames) }
  /* DWARF 3 */
  .debug_pubtypes 0 : { *(.debug_pubtypes) }
  .debug_ranges   0 : { *(.debug_ranges) }
  .gnu.attributes 0 : { KEEP (*(.gnu.attributes)) }
  .gptab.sdata : { *(.gptab.data) *(.gptab.sdata) }
  .gptab.sbss : { *(.gptab.bss) *(.gptab.sbss) }
  .mdebug.abi32 : { KEEP(*(.mdebug.abi32)) }
  .mdebug.abiN32 : { KEEP(*(.mdebug.abiN32)) }
  .mdebug.abi64 : { KEEP(*(.mdebug.abi64)) }
  .mdebug.abiO64 : { KEEP(*(.mdebug.abiO64)) }
  .mdebug.eabi32 : { KEEP(*(.mdebug.eabi32)) }
  .mdebug.eabi64 : { KEEP(*(.mdebug.eabi64)) }
  /DISCARD/ : { *(.rel.dyn) }
  /DISCARD/ : { *(.note.GNU-stack) *(.gnu_debuglink) *(.gnu.lto_*) }
}
