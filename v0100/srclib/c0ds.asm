;
;  Copyright (c) 2014-2015, Alexey Frunze
;  2-clause BSD license.
;
bits 16

    extern ___start__
    extern __start__bss
    extern __stop__bss

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
    jnc exe
    ; .COM programs may receive less than 64KB of memory just as well, bail out if it's the case
    mov ah, 0x40
    mov bx, 2 ; stderr
    mov dx, _64kbmsg
    mov cx, _64kbmsg_end - _64kbmsg
    int 0x21
    jmp terminate

exe:
    ; Init .bss
    mov di, __start__bss
    mov cx, __stop__bss
    sub cx, di
    xor al, al
    cld
    rep stosb

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

    extern ___DosSetVect
    extern ___Int00DE, ___Int04OF, ___Int06UD
;    extern ___Int01DB
;    extern ___Int03BP

    ; These ISRs may be called on the stack that does not belong to the app
    ; (e.g. it could be internal DOS stack).
    ;
    ; In the small and tiny memory models the compiler generates code in the
    ; assumption that DS=SS and supports no form of far pointers and has no
    ; way of distinguishing a near 16-bit pointer from one pointing to a
    ; global variable and one pointing to a local on-stack variable as both
    ; are expected to be in the same segment, hence DS=SS.
    ;
    ; Because of this, implementing ISRs in C or calling C functions from
    ; ISRs written in asm is difficult in the small and tiny memory models.
    ;
    ; For C code to work in the context of an ISR, we need to switch to the
    ; original stack (whose top we can't always know) or use a dedicated
    ; ISR stack area within the same data/stack segment of the small/tiny
    ; app.
    ;
    ; Transforming exceptions and Ctrl+C into signals is thus difficult in
    ; the small and tiny memory models and the only thing that can be done
    ; easily if one occurs is terminate the app, which is what we're doing
    ; here.
    ;
    ; Note, this technical problem does not exist in the huge memory model
    ; since all pointers in it include segment information, which is used
    ; when dereferencing pointers.
    global ___ExcIsr
___ExcIsr:
    mov ah, 0x40
    mov bx, 2 ; stderr
    push cs
    pop ds
    mov dx, _excmsg
    mov cx, _excmsg_end - _excmsg
    int 0x21
    ; fallthrough

    ; It looks like DOS will terminate the app on Ctrl+C even without a custom int 0x23 handler.
    ; But let's keep the code as I might transform Ctrl+C into SIGINT in the future.
    global ___CtrlCIsr
___CtrlCIsr:

    mov ax, [cs:_ss]
    mov ds, ax
    mov es, ax

    push ___Int00DE
    push 0
    call ___DosSetVect
;    push ___Int01DB
;    push 1
;    call ___DosSetVect
;    push ___Int03BP
;    push 3
;    call ___DosSetVect
    push ___Int04OF
    push 4
    call ___DosSetVect
    push ___Int06UD
    push 6
    call ___DosSetVect

terminate:
    mov ax, 0x4c01
    int 0x21

_excmsg db 13,10,"Unhandled exception!",13,10
_excmsg_end:

_64kbmsg db "Not enough memory!",13,10
_64kbmsg_end:


section .bss
    ; .bss must exist for __start__bss and __stop__bss to also exist
    resw    1
