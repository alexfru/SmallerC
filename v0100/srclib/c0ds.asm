;
;  Copyright (c) 2014-2015, Alexey Frunze
;  2-clause BSD license.
;
bits 16

    extern ___start__
    extern __start__bss
    extern __stop__bss

section .text

cpu 8086

    global __start
__start:
    call    check_dos3

    mov     ax, ss
    mov     [cs:_ss], ax ; preserve SS as the data segment, which we may need to access from ISRs
    mov     ds, ax ; DS=ES=SS in small model .EXEs and in tiny model .COMs
    mov     es, ax

    mov     bx, cs
    cmp     ax, bx
    jne     init_bss

    ; CS=SS means it's a .COM program.
    ; .COM programs get all available memory allocated to them.
    ; Shrink the PSP block to 64KB.
    mov     ah, 0x4a
    mov     bx, 4096
    int     0x21
    jnc     init_bss
    ; .COM programs may receive less than 64KB of memory just as well, bail out if it's the case
    mov     ah, 9
    push    cs
    pop     ds
    mov     dx, msg_64kb
    int     0x21
    jmp     terminate

init_bss:
    ; Init .bss
    mov     di, __start__bss
    mov     cx, __stop__bss
    sub     cx, di
    xor     al, al
    cld
    rep     stosb

    jmp     ___start__ ; __start__() will set up argc and argv for main() and call exit(main(argc, argv))

check_dos3:
    ; Expects ES=PSP.
    mov     ax, 0x3000 ; al = 0 in case it's DOS prior to 2.0 and doesn't have this function
    int     0x21
    cmp     al, 3
    jc      .not_dos3 ; fail if DOS prior to 3.0
    ret
.not_dos3:
    mov     ah, 9
    push    cs
    pop     ds
    mov     dx, msg_dos3
    int     0x21
    ; Jump to PSP:0, which has "int 0x20" that will properly terminate on DOS prior to 2.0
    ; (properly is when CS=PSP).
    push    es
    xor     ax, ax
    push    ax
    retf

    global ___getCS
___getCS:
    mov     ax, cs
    ret

    global ___getSS
___getSS:
    mov     ax, [cs:_ss]
    ret
_ss dw 0x9090

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
    mov     ah, 9
    push    cs
    pop     ds
    mov     dx, msg_exc
    int     0x21
    ; fallthrough

    ; It looks like DOS will terminate the app on Ctrl+C even without a custom int 0x23 handler.
    ; But let's keep the code as I might transform Ctrl+C into SIGINT in the future.
    global ___CtrlCIsr
___CtrlCIsr:

    mov     ax, [cs:_ss]
    mov     ds, ax
    mov     es, ax

    mov     ax, ___Int00DE
    push    ax
    xor     ax, ax
    push    ax
    call    ___DosSetVect
;    mov     ax, ___Int01DB
;    push    ax
;    mov     ax, 1
;    push    ax
;    call    ___DosSetVect
;    mov     ax, ___Int03BP
;    push    ax
;    mov     ax, 3
;    push    ax
;    call    ___DosSetVect
    mov     ax, ___Int04OF
    push    ax
    mov     ax, 4
    push    ax
    call    ___DosSetVect
    mov     ax, ___Int06UD
    push    ax
    mov     ax, 6
    push    ax
    call    ___DosSetVect

terminate:
    mov     ax, 0x4c01
    int     0x21

; N.B. these messages are in the code segment
; (that is, separate from the data/stack segment, if it's an .EXE).

msg_exc db 13,10,"Unhandled exception!",13,10,"$"

msg_64kb db "Not enough memory!",13,10,"$"

msg_dos3 db "DOS 3+ required!",13,10,"$"

section .bss
    ; .bss must exist for __start__bss and __stop__bss to also exist
    resw    1
