;
;  Copyright (c) 2015, Alexey Frunze
;  2-clause BSD license.
;

; This is a stub for 32-bit DPMI programs.
; It loads CWSDPMI.EXE if necessary, switches to protected mode, loads the rest
; of the .exe file (a stub info structure and an a.out image with relocations are
; appended to the stub to make it a valid DPMI .exe), performs relocation and
; transfers control to the 32-bit code from the a.out part.

; Compile:
;     smlrcc -small dpstub.asm -o dpstub.exe
;   OR
;     nasm -f elf dpstub.asm -o dpstub.o
;     smlrl -small dpstub.o -o dpstub.exe

bits 16

FBUFSZ equ (48*1024) ; Don't change this! Must be a multiple of 8. Shared with 32-bit code.

section .text

        global __start
__start:
        mov     ax, ss
        mov     ds, ax
        mov     [ds_seg], ax
        mov     [psp_seg], es
        mov     [cs_seg], cs

        ; find %PATH% and argv[0]
        mov     es, [es:0x2c]   ; es = environment segment
        mov     [env_seg], es
        xor     di, di
env_search:
        cmp     word [es:di], 0x4150 ; "PA" ?
        jne     var_skip
        cmp     word [es:di + 2], 0x4854 ; "TH" ?
        jne     var_skip
        cmp     byte [es:di + 4], '=' ; '=' ?
        jne     var_skip
        add     di, 5
        mov     [path_ofs], di
var_skip:
        cmp     byte [es:di], 0 ; end of "VARIABLE=VALUE" ?
        je      var_end
        inc     di
        jmp     var_skip
var_end:
        inc     di
        cmp     byte [es:di], 0 ; end of all variables?
        jne     env_search
        add     di, 3
        mov     si, argv0
cpy_argv0:
        mov     al, [es:di]
        mov     [si], al
        inc     si
        inc     di
        or      al, al
        jnz     cpy_argv0

        ; check if a 32-bit DPMI host is available, try to load CWSDPMI.EXE (as TSR) if not
        call    dpmi_detect
        jz      got_dpmi32
        call    dpmi_load
        call    dpmi_detect
        jnz     err_nodpmi32
got_dpmi32:

        ; open the .exe file
        mov     dx, argv0
        mov     ax, 0x3d00
        int     0x21
        jc      err_openself
        mov     [fhandle], ax
        mov     bx, ax

        ; read the .exe header
        mov     dx, exe_header
        mov     cx, exe_header_len
        mov     ah, 0x3f
        int     0x21
        jc      err_invalid_exe
        cmp     ax, exe_header_len
        jne     err_invalid_exe
        cmp     word [exe_header_sig], 0x5a4d ; "MZ" ?
        jne     err_invalid_exe

        ; locate the end of the stub and seek to it
        mov     dx, [exe_header_page_cnt]
        shl     dx, 9
        mov     ax, [exe_header_part_page]
        add     dx, ax
        neg     ax
        and     ax, 512
        sub     dx, ax
        xor     cx, cx
        mov     ax, 0x4200
        int     0x21
        jc      err_invalid_exe

        ; load the stub info
        mov     dx, stub_info
        mov     cx, stub_info_len
        mov     ah, 0x3f
        int     0x21
        jc      err_invalid_exe
        cmp     ax, stub_info_len
        jne     err_invalid_exe
        cmp     dword [stub_info_magic], 0x21245044 ; "DP$!" ?
        jne     err_invalid_exe

        ; load the a.out header
        mov     dx, aout_header
        mov     cx, aout_header_len
        mov     ah, 0x3f
        int     0x21
        jc      err_invalid_exe
        cmp     ax, aout_header_len
        jne     err_invalid_exe
        cmp     dword [aout_header_magic], 0x00640107 ; OMAGIC ?
        jne     err_invalid_exe

        ; TBD??? additional stub info & a.out header validation?

        ; allocate memory for the DPMI host
        mov     bx, [pm_entry_sz]
        or      bx, 1
        mov     ah, 0x48
        int     0x21
        jc      err_nomem
        mov     [pm_entry_seg], ax

        ; enter 32-bit protected mode
        mov     es, [pm_entry_seg]
        mov     ax, 1
        call    far [pm_entry]
        jc      err_nodpmi32

        ; Finalize the code and data descriptors.
        ; We'll have a flat 4GB address space.
        ; Using DPMI function 0xc instead of functions 7,8,9 because Windows XP
        ; does not seem very happy about segment limits greater than or equal to
        ; 1MB supplied to function 8. But it is somehow OK with large limits in
        ; segment descriptors supplied to function 0xc (as evidenced with the LSL
        ; instruction, Windows XP reduces the effective limit from 4GB-1 to
        ; something less than 2GB, but doesn't complain).
        ; CWSDPMI.EXE is fine with both methods.
        ; DOSBox seems to be OK.
        ; NOTE: Windows 3.xx/9x/Me/NT/2k or other DPMI hosts / DOS extenders not tried.
        mov     cx, cs
        and     cl, 3 ; use cs.RPL (AKA CPL) as DPL
        shl     cl, 5
        or      [code32_descr + 5], cl
        or      [data32_descr + 5], cl
        push    ds
        pop     es

        ; allocate a code segment descriptor and a selector for it
        mov     ax, 0
        mov     cx, 1
        int     0x31
        jc      err_alloc_ldt
        mov     [code32_sel], ax
        mov     bx, ax

        ; set the code segment descriptor
        mov     ax, 0xc
        mov     edi, code32_descr
        int     0x31
        jc      err_set_descr

        ; allocate a data segment descriptor and a selector for it
        mov     ax, 0
        mov     cx, 1
        int     0x31
        jc      err_alloc_ldt
        mov     [data32_sel], ax
        mov     bx, ax

        ; set the data segment descriptor
        mov     ax, 0xc
        mov     edi, data32_descr
        int     0x31
        jc      err_set_descr

        ; allocate memory for the program (text, data, bss, stack, heap)
        mov     eax, [aout_header_text]
        or      eax, eax
        jz      err_invalid_exe
        add     eax, [aout_header_data]
        jc      err_invalid_exe
        add     eax, [aout_header_bss]
        jc      err_invalid_exe
        mov     ebx, [stub_info_stack]
        cmp     ebx, 65536
        jc      err_invalid_exe
        add     eax, ebx
        jc      err_invalid_exe
        add     eax, [stub_info_minheap]
        jc      err_invalid_exe
        add     eax, 4096 ; for page alignment
        jc      err_invalid_exe
        mov     ebx, eax
        sub     ebx, [stub_info_minheap]
        add     ebx, [stub_info_maxheap]
        jc      err_invalid_exe
        call    alloc_max
        jc      err_nodpmimem
        sub     dword [mem_size], 4096
        mov     ecx, [image_base]
        add     ecx, 4095 ; page-align
        and     ecx, -4096
        mov     [image_base], ecx

        ; memory layout:
        ;   0
        ;     ...
        ;     text section
        ;     data section (if any)
        ;     bss section (if any)
        ;     stack
        ;     heap
        ;     ...
        ;   4GB-1

        ; load the text and data sections, zero the bss section
        call    load

        ; relocate text
        mov     ecx, [aout_header_trsize]
        mov     edi, [image_base]
        call    relocate

        ; relocate data
        mov     ecx, [aout_header_drsize]
        mov     edi, [aout_header_text]
        add     edi, [image_base]
        call    relocate

        ; close the .exe file
        mov     bx, [fhandle]
        mov     ah, 0x3e
        int     0x21

        ; jump to the entry point

        mov     cx, [data32_sel]
        mov     es, cx

        movzx   ebx, word [cs_seg]
        shl     ebx, 4
        add     ebx, ds_sel
        mov     [es:ebx], ds ; store ds in [cs:ds_sel] for exit
        mov     [exit_sp], sp ; store sp for exit

        mov     ebx, [image_base]

        mov     eax, [aout_header_text]
        add     eax, [aout_header_data]
        add     eax, [aout_header_bss]
        add     eax, [stub_info_stack]
        mov     ss, cx
        lea     esp, [ebx + eax]
        and     esp, -4 ; align esp on machine word boundary

        mov     edx, ebx
        add     edx, [mem_size]
        push    edx ; pass heap stop

        add     eax, ebx
        push    eax ; pass heap start

        movzx   edx, word [ds_seg]
        shl     edx, 4

        lea     eax, [edx + fbuf] ; pass fbuf
        push    eax

        lea     eax, [edx + stub_info] ; pass stub_info
        push    eax

        lea     eax, [edx + argv0] ; pass argv[0]
        push    eax

        movzx   eax, word [env_seg] ; pass environment location
        shl     eax, 4
        push    eax

        movzx   eax, word [psp_seg] ; pass PSP location
        shl     eax, 4
        push    eax

        mov     ax, cs
        shl     eax, 16
        mov     ax, exit ; pass exit address
        push    eax

        push    eax ; dummy return address, as if this is a call

        movzx   eax, word [code32_sel]
        push    eax
        mov     eax, [aout_header_entry]
        add     eax, ebx
        push    eax

        mov     ds, cx

        db 0x66
        retf

dpmi_detect:
        mov     ax, 0x1687
        int     0x2f
        mov     [pm_entry], di
        mov     [pm_entry + 2], es
        mov     [pm_entry_sz], si
        and     bx, 1
        xor     bx, 1
        or      ax, bx ; ax = 0 (and zf = 1) if 32-bit DPMI
        ret

dpmi_load:
        ; try the directory of the stub: give the program a chance to use its own DPMI host
        push    ds
        pop     es
        mov     di, exec_name
        mov     bx, di
        mov     si, argv0 ; extract path from argv[0]
        cld
dpmi_load1:
        lodsb
        stosb
        cmp     al, '\'
        jne     dpmi_load2
        mov     bx, di ; record last slash position
dpmi_load2:
        or      al, al ; end of argv[0]?
        jnz     dpmi_load1
        mov     di, bx
        mov     si, host_name
        mov     cx, host_name_len + 1
        rep     movsb ; append host_name after last slash

        call    exec
        jz      dpmi_load_end

        ; try %PATH%: is the host perhaps shared by multiple programs?
        push    ds
        pop     es
        mov     si, [path_ofs]
        mov     ds, [env_seg]
        mov     al, [si]
        or      al, al ; empty %PATH% ?
        jnz     dpmi_load3
        push    es
        pop     ds
        jmp     dpmi_load7
dpmi_load3:
        mov     di, exec_name
        xor     al, al
        cld
dpmi_load4:
        mov     ah, al ; keep previous character
        lodsb
        cmp     al, ';'
        je      dpmi_load5
        or      al, al
        jz      dpmi_load5
        stosb
        jmp     dpmi_load4
dpmi_load5:
        cmp     ah, '\' ; append a slash unless we just got one
        je      dpmi_load6
        mov     byte [es:di], '\'
        inc     di
dpmi_load6:
        push    es
        pop     ds
        push    si
        mov     si, host_name
        mov     cx, host_name_len + 1
        rep     movsb
        pop     si

        call    exec
        jz      dpmi_load_end

        or      al, al ; last path in %PATH% ?
        jz      dpmi_load7
        push    ds
        pop     es
        mov     ds, [env_seg]
        jmp     dpmi_load3

dpmi_load7:
        ; try the current directory: last chance
        push    ds
        pop     es
        mov     di, exec_name
        mov     si, host_name
        mov     cx, host_name_len + 1
        cld
        rep     movsb
        call    exec

dpmi_load_end:
        ret

probe_alloc:
        ; ecx = size to try to allocate and immediately free
        ; ebx = size cap
        pushad
        cmp     ebx, ecx
        jc      probe_alloc_end
        mov     ebx, ecx
        shr     ebx, 16
        mov     ax, 0x501
        int     0x31
        jc      probe_alloc_end
        mov     ax, 0x502
        int     0x31
        clc
probe_alloc_end:
        ; carry = 1 IFF failed
        popad
        ret

alloc:
        ; ecx = size to allocate
        pushad
        mov     [mem_size], ecx
        mov     ebx, ecx
        shr     ebx, 16
        mov     ax, 0x501
        int     0x31
        mov     [image_base], cx
        mov     [image_base + 2], bx
        mov     [mem_handle], di
        mov     [mem_handle + 2], si
        ; carry = 1 IFF failed
        popad
        ret

alloc_max:
        ; eax = in: Min
        ; ebx = in: Max
        ; ecx = temp: try size for probe_alloc and alloc
        ; esi = temp: size
        ; edx = temp: addend

        ; If Max isn't larger than Min, go for Min
        mov     esi, eax
        cmp     ebx, eax
        jbe     alloc_found_size

        ; Give it a shot, try Max first
        mov     ecx, ebx
        call    alloc
        jnc     alloc_max_end

        ; Still here? Try to find the new max below Max

        xor     esi, esi ; size = 0
        bsr     ecx, ebx
        mov     edx, 1
        shl     edx, cl ; addend = 1u << bsr(Max)

alloc_max_try:
        ; Probe size + addend with a cap of Max
        lea     ecx, [esi + edx]
        call    probe_alloc
        cmc
        sbb     ecx, ecx
        and     ecx, edx
        add     esi, ecx ; size += addend if probe succeeded
        shr     edx, 1 ; addend /= 2
        jnz     alloc_max_try

        cmp     esi, eax
        jae     alloc_found_size ; jump if size >= Min

        ; Still here? There's probably not enough memory, but try Min at last
        mov     esi, eax

alloc_found_size:
        mov     ecx, esi
        call    alloc

alloc_max_end:
        ; carry = 1 IFF failed
        ret

exec:
        push    ds
        pusha
        mov     word [exec_params_env_seg], 0
        mov     word [exec_params_params + 0], exec_args
        mov     word [exec_params_params + 2], ds
        mov     word [exec_params_fcb1 + 0], fcb1
        mov     word [exec_params_fcb1 + 2], ds
        mov     word [exec_params_fcb2 + 0], fcb2
        mov     word [exec_params_fcb2 + 2], ds
        mov     dx, exec_name
        push    ds
        pop     es
        mov     bx, exec_params
        mov     [cs:save_ss], ss
        mov     [cs:save_sp], sp
        mov     ax, 0x4b00
        int     0x21
        mov     ss, [cs:save_ss]
        mov     sp, [cs:save_sp]
        sbb     ax, ax ; ax = 0 (and zf = 1) IFF success
        jnz     exec_end
        mov     ah, 0x4d
        int     0x21
        xor     ax, 0x0300 ; ax = 0 (and zf = 1) IFF terminated successfully as TSR
exec_end:
        popa
        pop     ds
        ret
        ; function 0x4b of int 0x21 may trash even ss:sp, so we
        ; will preserve them in the code segment
        save_sp dw 0
        save_ss dw 0

load_buf:
        or      eax, eax
        jz      load_buf_end
        pushad
        push    es
        call    zero_regs
        mov     [regs_ecx], ax
        mov     ax, [ds_seg]
        mov     [regs_ds], ax
        mov     word [regs_edx], fbuf
        mov     ax, [fhandle]
        mov     word [regs_ebx], ax
        mov     word [regs_eax], 0x3f00
        push    ds
        pop     es
        mov     edi, regs
        mov     ax, 0x300
        mov     bx, 0x21
        xor     cx, cx
        int     0x31
        jc      err_invalid_exe
        mov     ah, [regs_flags]
        sahf
        jc      err_invalid_exe
        pop     es
        popad
        cmp     ax, [regs_eax]
        jne     err_invalid_exe
load_buf_end:
        ret

load:
        mov     es, [data32_sel]
        mov     edi, [image_base]
        mov     ecx, [aout_header_text]
        add     ecx, [aout_header_data]
load1:
        mov     eax, FBUFSZ ; loading in chunks of FBUFSZ bytes
        cmp     ecx, eax
        jnc     load2
        mov     eax, ecx
load2:
        or      eax, eax
        jz      load3
        call    load_buf
        push    ecx
        mov     ecx, eax
        mov     esi, fbuf
        cld
        db 0x67
        rep     movsb
        pop     ecx
        sub     ecx, eax
        jmp     load1
load3:
        mov     ecx, [aout_header_bss]
        add     ecx, [stub_info_stack]
        xor     al, al
        cld
        db 0x67
        rep     stosb
        ret

relocate:
        mov     es, [data32_sel]
        mov     ebx, [image_base]
relocate1:
        mov     eax, FBUFSZ ; loading in chunks of FBUFSZ bytes
        cmp     ecx, eax
        jnc     relocate2
        mov     eax, ecx
relocate2:
        or      eax, eax
        jz      relocate3
        call    load_buf
        sub     ecx, eax
        mov     si, fbuf
relocate4:
        mov     ebp, [si] ; address
        mov     edx, [si + 4] ; info

        and     edx, 0x01ffffff
        cmp     edx, 0x01000002 ; pcrel + N_ABS ?
        mov     edx, [si + 4]
        je      relabs
        test    edx, 0x04000000 ; 32-bit ?
        jz      rel16
        add     [es:edi+ebp], ebx
        jmp     rel5
rel16:
        add     [es:edi+ebp], bx
        jmp     rel5
relabs:
        test    edx, 0x04000000 ; 32-bit ?
        jz      relabs16
        sub     [es:edi+ebp], ebx
        jmp     rel5
relabs16:
        sub     [es:edi+ebp], bx

rel5:
        add     si, 8
        sub     eax, 8
        jnz     relocate4
        jmp     relocate1
relocate3:
        ret

zero_regs:
        push    es
        pusha
        push    ds
        pop     es
        mov     di, regs
        mov     cx, regs_len
        cld
        xor     al, al
        rep     stosb
        popa
        pop     es
        ret

exit:
        ; 32-bit code should jump here to terminate instead of invoking
        ; fxn 0x4c of int 0x21, we'll free the 32-bit code and data
        ; selectors/descriptors allocated earlier to reduce LDT descriptor
        ; leaks, which are possible under Windows and some (0.9?) DPMI hosts
        cli
        mov     cx, [cs:ds_sel]
        mov     ds, cx
        mov     es, cx
        mov     ss, cx
        movzx   esp, word [exit_sp]
        push    ax ; save status
        mov     di, [mem_handle]
        mov     si, [mem_handle + 2]
        mov     ax, 0x502
        int     0x31
        mov     bx, [data32_sel]
        mov     ax, 1
        int     0x31
        mov     bx, [code32_sel]
        mov     ax, 1
        int     0x31
        pop     ax
        mov     ah, 0x4c
        int     0x21
ds_sel  dw      0x9090

err_nodpmi32:
        mov     dx, msg_nodpmi32
        jmp     error

err_nomem:
        mov     dx, msg_nomem
        jmp     error

err_nodpmimem:
        mov     dx, msg_nodpmimem
        jmp     error

err_openself:
        mov     dx, argv0
        call    pmsg
        mov     dx, msg_open
        jmp     error

err_invalid_exe:
        mov     dx, argv0
        call    pmsg
        mov     dx, msg_invalid
        jmp     error

err_alloc_ldt:
        mov     dx, msg_alloc_ldt
        jmp     error

err_set_descr:
        mov     dx, msg_set_descr
        jmp     error

error:
        call    pmsg
        mov     dx, msg_crlf
        call    pmsg
        mov     ax, 0x4c01
        int     0x21

; DOS can output single characters or a buffer of them.
; CWSDPMI.EXE is only a DPMI host but not a full DOS extender
; and therefore it does not translate protected mode selectors
; to real mode segments when simulating int 0x21.
; We choose to output messages character by character to
; avoid selector/segment manipulations and have a common
; message printing routine for both real and protected modes.
pmsg:
        pushad
        mov     bx, dx
pmsg0:
        mov     dl, [bx]
        or      dl, dl
        jz      pmsg1
        mov     ah, 2
        int     0x21
        inc     bx
        jmp     pmsg0
pmsg1:
        popad
        ret

%if 0
err_ok:
        mov     ax, 0x4c00
        int     0x21

printh:
        pushad
        mov     ecx, 8
        mov     esi, eax
        mov     bx, hex_digits
printh1:
        rol     esi, 4
        mov     ax, si
        and     al, 15
        xlat
        mov     dl, al
        mov     ah, 2
        int     0x21
        loop    printh1
        popad
        ret

printcrlf:
        pushad
        mov     dl, 13
        mov     ah, 2
        int     0x21
        mov     dl, 10
        mov     ah, 2
        int     0x21
        popad
        ret
%endif

align 16

section .data

; page-granular, big/32-bit, present, code, readable, base = 0, limit = 4GB-1
code32_descr: dd 0x0000ffff, 0x00cf9a00
; page-granular, big/32-bit, present, data, writable, base = 0, limit = 4GB-1
data32_descr: dd 0x0000ffff, 0x00cf9200

host_name   db "CWSDPMI.EXE", 0
host_name_len equ $ - host_name - 1

exec_args   db 0, 13 ; no host arguments, CR-terminated

%if 0
hex_digits  db "0123456789abcdef"
%endif

msg_crlf        db 13, 10, 0
msg_nodpmi32    db "No 32-bit DPMI! Get CWSDPMI.EXE!", 0
msg_nomem       db "Not enough memory!", 0
msg_nodpmimem   db "Not enough DPMI memory!", 0
msg_open        db " can't be opened!", 0
msg_invalid     db " isn't a valid DPMI program!", 0
msg_alloc_ldt   db "Can't allocate LDT descriptor!", 0
msg_set_descr   db "Can't set descriptor!", 0

align 16

section .bss ; Note, we aren't zeroing .bss!

cs_seg      resw 1
ds_seg      resw 1
psp_seg     resw 1
env_seg     resw 1
path_ofs    resw 1

exit_sp     resw 1

argv0       resb 81 ; shared with 32-bit code

pm_entry    resd 1
pm_entry_sz resw 1
pm_entry_seg resw 1

exec_params:
exec_params_env_seg     resw 1
exec_params_params      resd 1
exec_params_fcb1        resd 1
exec_params_fcb2        resd 1

fcb1        resb 37
fcb2        resb 37
exec_name   resb 81

exe_header:
exe_header_sig          resw 1
exe_header_part_page    resw 1
exe_header_page_cnt     resw 1
                        resb 26
exe_header_len equ $ - exe_header

stub_info: ; shared with 32-bit code
stub_info_magic    resd 1
stub_info_stack    resd 1
stub_info_minheap  resd 1
stub_info_maxheap  resd 1
                   resd 12
stub_info_len equ $ - stub_info

aout_header:
aout_header_magic  resd 1
aout_header_text   resd 1
aout_header_data   resd 1
aout_header_bss    resd 1
aout_header_syms   resd 1
aout_header_entry  resd 1
aout_header_trsize resd 1
aout_header_drsize resd 1
aout_header_len equ $ - aout_header

fhandle     resw 1

code32_sel  resw 1
data32_sel  resw 1

image_base  resd 1
mem_size    resd 1
mem_handle  resd 1

regs:
regs_edi    resd 1
regs_esi    resd 1
regs_ebp    resd 1
regs_resrvd resd 1
regs_ebx    resd 1
regs_edx    resd 1
regs_ecx    resd 1
regs_eax    resd 1
regs_flags  resw 1
regs_es     resw 1
regs_ds     resw 1
regs_fs     resw 1
regs_gs     resw 1
regs_ip     resw 1
regs_cs     resw 1
regs_sp     resw 1
regs_ss     resw 1
regs_len equ $ - regs

fbuf        resb FBUFSZ ; shared with 32-bit code

alignb 16
