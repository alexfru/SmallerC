; /*
; Copyright (c) 2014-2015, Alexey Frunze
; All rights reserved.
;
; Redistribution and use in source and binary forms, with or without
; modification, are permitted provided that the following conditions are met:
;
; 1. Redistributions of source code must retain the above copyright notice, this
;    list of conditions and the following disclaimer.
; 2. Redistributions in binary form must reproduce the above copyright notice,
;    this list of conditions and the following disclaimer in the documentation
;    and/or other materials provided with the distribution.
;
; THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
; ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
; WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
; DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
; ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
; (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
; ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
; (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
; SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
; */
;
; /*****************************************************************************/
; /*                                                                           */
; /*                             minimal stdlibc                               */
; /*                                                                           */
; /*Just enough code for Smaller C to compile itself into a 32-bit Linux "EXE".*/
; /*                                                                           */
; /*****************************************************************************/
;
; Compile:
;   smlrc -nobss -seg32 -no-externs -D _LINUX lb.c lb.asm
;   smlrc -nobss -seg32 -no-externs -label 1001 smlrc.c smlrc.asm
;   nasm -f bin smlrcl.asm -o smlrcl
;   chmod +x smlrcl
;

ImageBase         equ 0x08048000
SectionAlignment  equ 4096

_text_size_     equ (_text_end_ - _text_start_)
_data_size_      equ ((_rodata_end_ - _rodata_start_) + (_data_end_ - _data_start_))

bits 32
org ImageBase

section .text
; ELF header
    db 0x7F,"ELF",1,1,1,0,0,0,0,0,0,0,0,0   ; e_ident (32-bit objects, little-endian, current version)
    dw 2                                    ; e_type (executable)
    dw 3                                    ; e_machine (Intel 80386)
    dd 1                                    ; e_version (current version)
    dd Entry                                ; e_entry
    dd ProgHeaders - $$                     ; e_phoff
    dd 0                                    ; e_shoff
    dd 0                                    ; e_flags
    dw 52                                   ; e_ehsize
    dw 32                                   ; e_phentsize
    dw ProgHeadersSize / 32                 ; e_phnum
    dw 0                                    ; e_shentsize
    dw 0                                    ; e_shnum
    dw 0                                    ; e_shstrndx
; Program headers
ProgHeaders:
; .text
    dd 1                                    ; p_type (load)
    dd _text_start_ - ImageBase             ; p_offset
    dd _text_start_                         ; p_vaddr
    dd _text_start_                         ; p_paddr
    dd _text_size_                          ; p_filesz
    dd _text_size_                          ; p_memsz
    dd 5                                    ; p_flags (readable, executable)
    dd SectionAlignment                     ; p_align
; .data
    dd 1                                    ; p_type (load)
    dd _rodata_start_ - ImageBase           ; p_offset
    dd _rodata_start_                       ; p_vaddr
    dd _rodata_start_                       ; p_paddr
    dd _data_size_                          ; p_filesz
    dd _data_size_                          ; p_memsz
    dd 6                                    ; p_flags (readable, writable)
    dd SectionAlignment                     ; p_align
ProgHeadersSize equ $ - ProgHeaders

align SectionAlignment, db 0
_text_start_:
Entry:
    pop  eax ; argc
    push esp ; argv
    push eax ; argc
    call ___start__ ; __start__(arc, argv) will call exit(main(argc, argv))

section .rodata
align SectionAlignment, db 0
_rodata_start_:

section .data
align SectionAlignment, db 0
_data_start_:

;;;;;;;;;;;;;;;;

%include "lb.asm"
%include "smlrc.asm"

;;;;;;;;;;;;;;;;

section .text
align SectionAlignment, db 0
_text_end_:

section .rodata
align SectionAlignment, db 0
_rodata_end_:

section .data
align SectionAlignment, db 0
_data_end_:

; file end
