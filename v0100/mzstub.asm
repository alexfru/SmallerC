; /*
; Copyright (c) 2014, Alexey Frunze
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
; /*   Just enough code for Smaller C to compile itself into a Win32 PE .EXE.  */
; /*                                                                           */
; /*****************************************************************************/
;
; Compile:
;   nasm -f bin mzstub.asm -o mzstub.bin
;

bits 16
org 0

_exe_size_      equ (_text_end_ - _text_start_)

section .text

; _text_start_: file offset = 0, IP = file offset & 0xFFFF = 0
_text_start_:
    db  "MZ"
    dw  _exe_size_ % 512 ; size of the last partial page
    dw  (_exe_size_ + 511) / 512 ; exe image size in 512-byte pages, including header
    dw  0 ; number of entries in the relocation table
    dw  4 ; size of the header in 16-byte paragraphs AKA (relative) image base (will be added to CS and SS)
    dw  4096 ; min RAM needed in paragraphs after the image (64K stack)
    dw  4096 ; max RAM needed in paragraphs after the image
    dw  _exe_size_ / 16 - 4 ; initial SS
    dw  0xFFFC ; initial SP
    dw  0 ; checksum (nobody really cares about it)
    dw  _exe_start_ ; initial IP
    dw  -4 ; initial CS (initial CS:0 will correspond to _text_start_)
    dw  _exe_header_relo_ ; file offset of 1st relocation entry
    dw  0 ; overlay number
; standard MZ header ends here and a few PE-related things begin here
    times 16 dw 0
    dd  _text_end_ ; PE header location in the file (right after the end of this binary)
_exe_header_relo_:
; _exe_start_: file offset = 0x40, IP = file offset & 0xFFFF = 0x40
_exe_start_:

    push    cs
    pop     ds
    mov     dx, ErrMsgDos
    mov     ah, 9
    int     0x21
    mov     ax, 0x4c01
    int     0x21
ErrMsgDos   db "This program cannot be run in DOS mode.", 13, 13, 10, "$"

    times (128 - ($ - _text_start_)) db 0

_text_end_:
; file end
