;
; Small linker test for nasm and smlrl.
;
;
; How to compile for DOS using the tiny memory model:
;
;   smlrcc -dost lnktst1.asm lnktst1b.asm -o lnktst1t.com -map lnktst1t.map
; or
;   nasm -f elf lnktst1.asm -o lnktst1.o
;   nasm -f elf lnktst1b.asm -o lnktst1b.o
;   smlrl -tiny lnktst1.o lnktst1b.o -o lnktst1t.com -map lnktst1t.map
;
;
; How to compile for DOS using the small memory model:
;
;   smlrcc -doss lnktst1.asm lnktst1b.asm -o lnktst1s.exe -map lnktst1s.map
; or
;   nasm -f elf lnktst1.asm -o lnktst1.o
;   nasm -f elf lnktst1b.asm -o lnktst1b.o
;   smlrl -small lnktst1.o lnktst1b.o -o lnktst1s.exe -map lnktst1s.map
;

bits 16

extern func

section .text

    global __start
__start:
    ; these 3 lines are only needed for .EXEs, but not .COMs
    mov ax, ss
    mov ds, ax ; DS=ES=SS in small model .EXEs and in tiny model .COMs
    mov es, ax

    call func

    mov ax, 0x4c00
    int 0x21

section .data

    global msg
msg db "Linker test!",13,10,"$"
