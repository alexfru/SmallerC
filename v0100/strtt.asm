; startup code to build .COM programs with Smaller C and NASM

; compile your C program with the compiler and append the program's ASM code
; at the end of this file, then use NASM to compile it to a .COM program, e.g.
;   nasm.exe -f bin test.asm -o test.com

; code (startup) goes first in .COM programs
SEGMENT _TEXT PUBLIC CLASS=CODE USE16
bits 16
org 0x100

    jmp _main

; data goes last in .COM programs
SEGMENT _DATA PUBLIC CLASS=DATA
SEGMENT _TEXT

; int putchar(int c);
_putchar:
    push    bp
    mov     bp, sp

    mov     ah, 2
    mov     dl, [bp+4]
    cmp     dl, 0x0A ; '\n'
    jne     .0

    mov     dl, 0x0D ; '\r'
    int     0x21
    mov     dl, [bp+4]
.0:
    int     0x21

    mov     ax, [bp+4]

    pop     bp
    ret

; int getchar(void);
_getchar:
    mov     ah, 1
    int     0x21
    cmp     al, 0x0D ; '\r'
    jne     .0
    mov     al, 0x0A ; '\n'
.0:
    mov     ah, 0
    ret

; int puts(const char *s);
; char *gets(char *s);

; void gfxmode(int mode);
_gfxmode:
    push    bp
    mov     bp, sp
    mov     ah, 0
    mov     al, [bp+4]
    int     0x10
    pop     bp
    ret

; dos.h:
; void pokeb(int seg, int ofs, char val);
; void poke(int seg, int ofs, int val);
; char peekb(int seg, int ofs);
; int peek(int seg, int ofs);
_pokeb:
    push    bp
    mov     bp, sp

    push    ds
    mov     ds, [bp+4]
    mov     bx, [bp+6]
    mov     al, [bp+8]
    mov     [bx], al
    pop     ds

    pop     bp
    ret
_poke:
    push    bp
    mov     bp, sp

    push    ds
    mov     ds, [bp+4]
    mov     bx, [bp+6]
    mov     ax, [bp+8]
    mov     [bx], ax
    pop     ds

    pop     bp
    ret
_peekb:
    push    bp
    mov     bp, sp

    push    ds
    mov     ds, [bp+4]
    mov     bx, [bp+6]
    mov     al, [bx]
    cbw
    pop     ds

    pop     bp
    ret
_peek:
    push    bp
    mov     bp, sp

    push    ds
    mov     ds, [bp+4]
    mov     bx, [bp+6]
    mov     ax, [bx]
    pop     ds

    pop     bp
    ret
