;
;  Copyright (c) 2014, Alexey Frunze
;  2-clause BSD license.
;
bits 16

    extern ___start__

section .text

    global __start
__start:
    mov ax, ss
    mov [cs:_ss], ax ; preserve SS as the data segment, which we may need to access from ISRs
    mov ds, ax ; DS=ES=SS in small model .EXEs and in tiny model .COMs
    mov es, ax
    mov bx, cs
    cmp ax, bx
    jne exe
    ; CS=SS means it's a .COM program.
    ; .COM programs get all available memory allocated to them.
    ; Shrink the PSP block to 64KB.
    mov ah, 0x4a
    mov bx, 4096
    int 0x21
exe:
    jmp ___start__ ; __start__() will set up argc and argv for main() and call exit(main(argc, argv))

    global ___getCS
___getCS:
    mov ax, cs
    ret

    global ___getSS
___getSS:
    mov ax, [cs:_ss]
    ret
_ss dw 0
