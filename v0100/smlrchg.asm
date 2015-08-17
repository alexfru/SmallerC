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
; /*Just enough code for Smaller C to compile itself into a 16/32-bit DOS .EXE.*/
; /*                                                                           */
; /*****************************************************************************/
;
; Compile:
;   smlrc -nobss -huge -no-externs lb.c lb.asm
;   smlrc -nobss -huge -no-externs -label 1001 smlrc.c smlrc.asm
;   nasm -f bin smlrchg.asm -o smlrchg.exe
;

bits 16
org 0

_text_size_      equ ((_text_end_ - _text_start_ + 3) & ~3)
_rodata_size_    equ ((_rodata_end_ - _rodata_start_ + 3) & ~3)
_data_size_      equ ((_data_end_ - _data_start_ + 3) & ~3)
_relo_text_size_ equ ((_relo_text_end_ - _relo_text_start_ + 3) & ~3)
_relo_data_size_ equ ((_relo_data_end_ - _relo_data_start_ + 3) & ~3)
_stack_size_     equ ((_stack_end_ - _stack_start_ + 3) & ~3)
_exe_size_       equ (_text_size_ + _rodata_size_ + _data_size_ + _relo_text_size_ + _relo_data_size_ + _stack_size_)

section .text align=4

; _text_start_: file offset = 0, IP = file offset & 0xFFFF = 0
_text_start_:
    db  "MZ"
    dw  _exe_size_ % 512 ; size of the last partial page
    dw  (_exe_size_ + 511) / 512 ; exe image size in 512-byte pages, including header
    dw  0 ; number of entries in the relocation table
    dw  2 ; size of the header in 16-byte paragraphs AKA (relative) image base (will be added to CS and SS)
    dw  4096 ; min RAM needed in paragraphs after the image (64K stack)
    dw  4096 ; max RAM needed in paragraphs after the image
    dw  (_exe_size_ - _stack_size_ + 15) / 16 - 2 ; initial SS
    dw  0xFFFC ; initial SP
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

    ; perform code/data relocations

    xor     ebx, ebx
    mov     bx, cs
    shl     ebx, 4 ; ebx = base physical address

    mov     esi, _relo_text_start_
relo_text_loop:
    cmp     esi, _relo_text_end_
    jae     relo_text_done

    lea     edi, [ebx + esi] ; edi = physical address of a relocation table element

    ror     edi, 4
    mov     ds, di
    shr     edi, 28

    mov     edi, [di]
    add     edi, ebx ; edi = physical address of a dword to which to add ebx and which then to transform into seg:ofs far pointer

    ror     edi, 4
    mov     ds, di
    shr     edi, 28

    mov     eax, [di]
    add     eax, ebx

    shl     eax, 12
    rol     ax, 4

    mov     [di], eax

    add     esi, 4
    jmp     relo_text_loop
relo_text_done:

    mov     esi, _relo_data_start_
relo_data_loop:
    cmp     esi, _relo_data_end_
    jae     relo_data_done

    lea     edi, [ebx + esi] ; edi = physical address of a relocation table element

    ror     edi, 4
    mov     ds, di
    shr     edi, 28

    mov     edi, [di]
    add     edi, ebx ; edi = physical address of a dword to which to add ebx

    ror     edi, 4
    mov     ds, di
    shr     edi, 28

    add     [di], ebx ; actual relocation

    add     esi, 4
    jmp     relo_data_loop
relo_data_done:

    ; make sure there's no garbage in the 16 most significant bits of EBP and ESP
    xor     ebp, ebp
    and     esp, 0xFFFF

    mov     eax, ___start__
    add     eax, ebx
    shl     eax, 12
    rol     ax, 4
    push    eax
    retf        ; __start__() will set up argc and argv for main() and call exit(main(argc, argv))

section .rodata align=4
_rodata_start_:

section .data align=4
_data_start_:

section .relot align=4
_relo_text_start_:

section .relod align=4
_relo_data_start_:

;;;;;;;;;;;;;;;;

%include "lb.asm"
%include "smlrc.asm"

;;;;;;;;;;;;;;;;

section .text
_text_end_:

section .rodata
_rodata_end_:

section .data
_data_end_:

section .relot
_relo_text_end_:

section .relod
_relo_data_end_:

section .stack align=4
_stack_start_:
    times 16 db 0 ; this is only the stack beginning
_stack_end_:

; file end
