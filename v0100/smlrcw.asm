; /*
; Copyright (c) 2014-2017, Alexey Frunze
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
; /*Just enough code for Smaller C to compile itself into a 32-bit Windows EXE.*/
; /*                                                                           */
; /*****************************************************************************/
;
; Compile:
;   smlrc -nobss -seg32 -no-externs -D _WIN32 lb.c lb.asm
;   smlrc -nobss -seg32 -no-externs -label 1001 smlrc.c smlrc.asm
;   nasm -f bin mzstub.asm -o mzstub.bin
;   nasm -f bin smlrcw.asm -o smlrcw.exe
;

ImageBase         equ 0x00400000
FileAlignment     equ 512
SectionAlignment  equ 4096

_text_size_      equ (_text_end_ - _text_start_)
_data_size_      equ ((_rodata_end_ - _rodata_start_) + (_data_end_ - _data_start_))
ImageSize        equ (HeadersSize + GapSize + _text_size_ + _data_size_)

bits 32
org ImageBase

section .text
; 16-bit DOS MZ .EXE stub
    incbin  "mzstub.bin"

; PE header and optional header
    db "PE", 0, 0                   ; PE signature
    dw 0x014C                       ; Machine (Intel 80386)
    dw NumberOfSections             ; NumberOfSections
    dd 0x52C3CB00                   ; TimeDateStamp
    dd 0                            ; PointerToSymbolTable
    dd 0                            ; NumberOfSymbols
    dw OptionalHeaderSize           ; SizeOfOptionalHeader
    dw 0x30F                        ; Characteristics (no symbol/debug info, fixed/no relocations, executable, 32-bit)
OptionalHeader:
    dw 0x10B                        ; Magic (PE32)
    db 8                            ; MajorLinkerVersion
    db 0                            ; MinorLinkerVersion
    dd _text_size_                  ; SizeOfCode
    dd _data_size_                  ; SizeOfInitializedData
    dd 0                            ; SizeOfUninitializedData
    dd Entry - ImageBase            ; AddressOfEntryPoint
    dd _text_start_ - ImageBase     ; BaseOfCode
    dd _rodata_start_ - ImageBase   ; BaseOfData
    dd ImageBase                    ; ImageBase
    dd SectionAlignment             ; SectionAlignment
    dd FileAlignment                ; FileAlignment
    dw 4                            ; MajorOperatingSystemVersion
    dw 0                            ; MinorOperatingSystemVersion
    dw 0                            ; MajorImageVersion
    dw 0                            ; MinorImageVersion
    dw 4                            ; MajorSubsystemVersion
    dw 0                            ; MinorSubsystemVersion
    dd 0                            ; Win32VersionValue
    dd ImageSize                    ; SizeOfImage
    dd HeadersSize                  ; SizeOfHeaders
    dd 0                            ; CheckSum
    dw 3                            ; Subsystem (Windows CUI)
    dw 0x400                        ; DllCharacteristics
    dd 0x100000                     ; SizeOfStackReserve
    dd 0x10000                      ; SizeOfStackCommit
    dd 0x100000                     ; SizeOfHeapReserve
    dd 0x1000                       ; SizeOfHeapCommit
    dd 0                            ; LoaderFlags
    dd 16                           ; NumberOfRvaAndSizes
; Data directories
    dd 0, 0                         ; Export Table
    dd ImportsStart - ImageBase, 0  ; Import Table
    dd 0, 0                         ; Resource Table
    dd 0, 0                         ; Exception Table
    dd 0, 0                         ; Security Table
    dd 0, 0                         ; Relocation Table
    dd 0, 0                         ; Debug Info
    dd 0, 0                         ; Description
    dd 0, 0                         ; Machine-specific
    dd 0, 0                         ; TLS
    dd 0, 0                         ; Load Configuration
    dd 0, 0                         ; Bound Import Table
    dd 0, 0                         ; Import Address Table
    dd 0, 0                         ; Delay Import Table
    dd 0, 0                         ; COM+
    dd 0, 0                         ; Reserved
OptionalHeaderSize equ $ - OptionalHeader

; PE section descriptors
SectionDescriptors:
    db ".text", 0, 0, 0         ; Name
    dd _text_size_              ; VirtualSize
    dd _text_start_ - ImageBase ; VirtualAddress
    dd _text_size_              ; SizeOfRawData
    dd _text_start_ - ImageBase ; PointerToRawData
    dd 0                        ; PointerToRelocations
    dd 0                        ; PointerToLinenumbers
    dw 0                        ; NumberOfRelocations
    dw 0                        ; NumberOfLinenumbers
    dd 0x60000020               ; Characteristics (code, executable, readable)

    db ".data", 0, 0, 0         ; Name
    dd _data_size_              ; VirtualSize
    dd _rodata_start_ - ImageBase ; VirtualAddress
    dd _data_size_              ; SizeOfRawData
    dd _rodata_start_ - ImageBase ; PointerToRawData
    dd 0                        ; PointerToRelocations
    dd 0                        ; PointerToLinenumbers
    dw 0                        ; NumberOfRelocations
    dw 0                        ; NumberOfLinenumbers
    dd 0xc0000040               ; Characteristics (data, readable, writable)
NumberOfSections equ ($ - SectionDescriptors) / 40

align FileAlignment, db 0
HeadersSize equ $ - $$

GapSize equ _text_start_ - $

align SectionAlignment, db 0
_text_start_:
Entry:
    jmp ___start__ ; __start__() will set up argc and argv for main() and call exit(main(argc, argv))

section .rodata
align SectionAlignment, db 0
_rodata_start_:

section .data
align SectionAlignment, db 0
_data_start_:

ImportsStart:
    dd Kernel32Hints - ImageBase, 0, 0, Kernel32name - ImageBase, Kernel32IatStart - ImageBase
    dd 0, 0, 0, 0, 0

Kernel32Hints:
                        dd hint_ExitProcess - ImageBase
                        dd hint_GetCommandLineA - ImageBase
                        dd hint_GetStdHandle - ImageBase
                        dd hint_CreateFileA - ImageBase
                        dd hint_CloseHandle - ImageBase
                        dd hint_ReadFile - ImageBase
                        dd hint_WriteFile - ImageBase
                        dd hint_SetFilePointer - ImageBase
                        dd 0

Kernel32IatStart:
__imp__ExitProcess      dd hint_ExitProcess - ImageBase
__imp__GetCommandLineA  dd hint_GetCommandLineA - ImageBase
__imp__GetStdHandle     dd hint_GetStdHandle - ImageBase
__imp__CreateFileA      dd hint_CreateFileA - ImageBase
__imp__CloseHandle      dd hint_CloseHandle - ImageBase
__imp__ReadFile         dd hint_ReadFile - ImageBase
__imp__WriteFile        dd hint_WriteFile - ImageBase
__imp__SetFilePointer   dd hint_SetFilePointer - ImageBase
                        dd 0

hint_ExitProcess        db 0, 0, "ExitProcess", 0
hint_GetCommandLineA    db 0, 0, "GetCommandLineA", 0
hint_GetStdHandle       db 0, 0, "GetStdHandle", 0
hint_CreateFileA        db 0, 0, "CreateFileA", 0
hint_CloseHandle        db 0, 0, "CloseHandle", 0
hint_ReadFile           db 0, 0, "ReadFile", 0
hint_WriteFile          db 0, 0, "WriteFile", 0
hint_SetFilePointer     db 0, 0, "SetFilePointer", 0

Kernel32name            db "kernel32.dll", 0

align 4, db 0

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
