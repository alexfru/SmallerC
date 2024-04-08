;
;  Copyright (c) 2014-2015, Alexey Frunze
;  2-clause BSD license.
;
bits 16

    extern ___start__
    extern __start__relot, __stop__relot
    extern __start__relod, __stop__relod
    extern __start__bss
    extern __stop__bss

section .text

cpu 8086

    global __start
__start:
    call    check_dos3
    call    check_386

cpu 386

    ; perform code/data relocations

    call    labnext
labnext:
    xor     ebx, ebx
    mov     bx, cs
    shl     ebx, 4
    xor     eax, eax
    pop     ax
    add     ebx, eax
    sub     ebx, labnext ; ebx = base physical address

    mov     esi, __start__relot
relo_text_loop:
    cmp     esi, __stop__relot
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

    mov     esi, __start__relod
relo_data_loop:
    cmp     esi, __stop__relod
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

    ; Init .bss

    push    ebx

    lea     edi, [ebx + __start__bss]
    lea     ebx, [ebx + __stop__bss]
    sub     ebx, edi
    ror     edi, 4
    mov     es, di
    shr     edi, 28
    xor     al, al
    cld

bss1:
    mov     ecx, 32768
    cmp     ebx, ecx
    jc      bss2

    sub     ebx, ecx
    rep     stosb
    and     di, 15
    mov     si, es
    add     si, 2048
    mov     es, si
    jmp     bss1

bss2:
    mov     cx, bx
    rep     stosb

    pop     ebx

    lea     eax, [ebx + ___start__]
    shl     eax, 12
    rol     ax, 4
    push    eax
    retf        ; __start__() will set up argc and argv for main() and call exit(main(argc, argv))

cpu 8086

check_dos3:
    ; Expects ES=PSP.
    mov     ax, 0x3000 ; al = 0 in case it's DOS prior to 2.0 and doesn't have this function
    int     0x21
    cmp     al, 3
    jc      .not_dos3 ; fail if DOS prior to 3.0
    ret
.not_dos3:
    call    .fail
    db      "DOS 3+ required!",13,10,"$"
.fail:
    pop     dx
    push    cs
    pop     ds
    mov     ah, 9
    int     0x21
    ; Jump to PSP:0, which has "int 0x20" that will properly terminate on DOS prior to 2.0
    ; (properly is when CS=PSP).
    push    es
    xor     ax, ax
    push    ax
    retf

check_386:
    ; Below 80286? E.g. 80(1)88/80(1)86 or V-20/V-30?
    push    sp
    pop     ax
    cmp     ax, sp
    jne     .fail

    ; Must be 80286+. 80386+ in virtual 8086 mode?
    ; N.B. expecting cr4.umip (2017+ CPUs) to be 0
    ; (naturally or through emulation).
cpu 286
    smsw    ax
cpu 8086
    and     al, 1 ; 80386+ may have cr0.pe = 1
    jz      .diff286from386
    ret

.diff286from386:
    ; 80286 or 80386+ in real address mode. Which one?
    pushf
    pushf
    pop     cx
    mov     ax, 0x3000
    or      cx, ax ; will try to set FLAGS.IOPL = 3
    push    cx
    popf
    pushf
    pop     cx ; FLAGS.IOPL = 0 on 80286, FLAGS.IOPL = 3 on 80386+.
    popf
    and     cx, ax
    cmp     cx, ax
    jne     .fail
    ret

.fail:
    call    fail_with_msg_sp
    db      "An 80386+ CPU is required!",13,10,"$"

fail_with_msg_sp:
    pop     dx
    push    cs
    pop     ds
    mov     ah, 9
    int     0x21
    mov     ax, 0x4c01
    int     0x21

section .text
rt: dd      rt
section .relot
    dd      rt ; .relot must exist for __start__relot and __stop__relot to also exist

section .data
rd: dd      rd
section .relod
    dd      rd ; .relod must exist for __start__relod and __stop__relod to also exist

section .bss
    ; .bss must exist for __start__bss and __stop__bss to also exist
    resd    1
