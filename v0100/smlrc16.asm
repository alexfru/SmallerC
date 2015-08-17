; /*
; Copyright (c) 2013-2015, Alexey Frunze
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
; /*  Just enough code for Smaller C to compile itself into a 16-bit DOS .EXE. */
; /*                                                                           */
; /*****************************************************************************/
;
; Compile:
;   smlrc -nobss -seg16 -no-externs lb.c lb.asm
;   smlrc -nobss -seg16 -no-externs -label 1001 smlrc.c smlrc.asm
;   nasm -f bin smlrc16.asm -o smlrc16.exe
; 

bits 16
org 0

section .text

; _text_start_: file offset = 0, IP = file offset & 0xFFFF = 0
_text_start_:
    db  "MZ"
    dw  0 ; size of the last partial page
    dw  256 ; exe image size in 512-byte pages, including header; 128K
    dw  0 ; number of entries in the relocation table
    dw  2 ; size of the header in 16-byte paragraphs AKA (relative) image base (will be added to CS and SS)
    dw  0 ; min RAM needed in paragraphs after the image
    dw  0 ; max RAM needed in paragraphs after the image
    dw  4096 - 2 ; initial SS (exactly 64K after the beginning of the code segment)
    dw  0xFFFE ; initial SP, can't be 0 (if it is, td.exe and debug.exe screw up SS (while trying to somehow "correct" the stack?))
    dw  0 ; checksum (nobody really cares about it)
    dw  _exe_start_ ; initial IP
    dw  -2 ; initial CS (initial CS:0 will correspond to _text_start_)
    dw  _exe_header_relo_ ; file offset of 1st relocation entry
    dw  0 ; overlay number
_exe_header_relo_:
    dw  0 ; fake relocation entry, just to pad the header to a multiple of 16 bytes in size
    dw  0
; _exe_start_: file offset = 0x20, IP = file offset & 0xFFFF = 0x20
_exe_start_:
    mov ax, ss
    mov ds, ax ; DS=ES=SS:0 to point to CS:0 + 64K
    mov es, ax
    jmp ___start__ ; __start__() will set up argc and argv for main() and call exit(main(argc, argv))

section .rodata

; _rodata_start_: file offset = 0x10000, SP = file offset & 0xFFFF = 0
_rodata_start_:
    db  "NULL" ; reserve several bytes so that variables don't appear at address/offset 0 (NULL)

section .data
_data_start_:

;;;;;;;;;;;;;;;;

%include "lb.asm"
%include "smlrc.asm"

;;;;;;;;;;;;;;;;

section .text

    times (0x10000 - ($ - _text_start_)) db 0xCC ; int3

section .rodata
align 4, db 0
_rodata_end_:

section .data

    times (0x10000 - (_rodata_end_ - _rodata_start_) - ($ - _data_start_)) db 0xCC ; int3

; file end: file offset = 0x20000
