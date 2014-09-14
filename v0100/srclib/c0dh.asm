;
;  Copyright (c) 2014, Alexey Frunze
;  2-clause BSD license.
;
bits 16

    extern ___start__
    extern __start__relot, __stop__relot
    extern __start__relod, __stop__relod

section .text

    global __start
__start:

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

    ; make sure there's no garbage in the 16 most significant bits of EBP and ESP
    xor     ebp, ebp
    and     esp, 0xFFFF

    mov     eax, ___start__
    add     eax, ebx
    shl     eax, 12
    rol     ax, 4
    push    eax
    retf        ; __start__() will set up argc and argv for main() and call exit(main(argc, argv))
