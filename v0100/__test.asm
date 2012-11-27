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
SEGMENT _TEXT PUBLIC CLASS=CODE USE16
SEGMENT _DATA PUBLIC CLASS=DATA

; glb putchar : (
; prm     c : int
;     ) int
; glb getchar : (void) int
; glb pokeb : (
; prm     seg : int
; prm     ofs : int
; prm     val : char
;     ) void
; glb strcpy : (
; prm     s1 : * char
; prm     s2 : * char
;     ) * char
SEGMENT _TEXT
    global  _strcpy
_strcpy:
    push    bp
    mov     bp, sp
; loc     s1 : (@4): * char
; loc     s2 : (@6): * char
; loc     tmp : (@-2): * char
    sub     sp, 2
; =
; RPN'ized expression: "s1 "
; Expanded expression: "(@4) *(2) "
; Fused expression:    "=(34) *(@-2) *(@4) "
    mov     ax, [bp+4]
    mov     [bp-2], ax
; while
; RPN'ized expression: "s1 ++p *u s2 ++p *u = "
; Expanded expression: "(@4) ++p(2) (@6) ++p(2) *(1) =(1) "
L2:
; Fused expression:    "++p(2) *(@4) push-ax ++p(2) *(@6) =(17) **sp *ax "
    mov     ax, [bp+4]
    inc     word [bp+4]
    push    ax
    mov     ax, [bp+6]
    inc     word [bp+6]
    mov     bx, ax
    mov     al, [bx]
    cbw
    pop     bx
    mov     [bx], al
    cbw
; JumpIfZero
    test    ax, ax
    je      L3
    jmp     L2
L3:
; return
; RPN'ized expression: "tmp "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
    mov     ax, [bp-2]
    jmp     L1
L1:
    leave
    ret
; SEGMENT _TEXT
; glb strlen : (
; prm     s : * char
;     ) int
SEGMENT _TEXT
    global  _strlen
_strlen:
    push    bp
    mov     bp, sp
; loc     s : (@4): * char
; loc     l : (@-2): int
    sub     sp, 2
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "=(34) *(@-2) 0 "
    mov     ax, 0
    mov     [bp-2], ax
; while
; RPN'ized expression: "s ++p *u "
; Expanded expression: "(@4) ++p(2) *(1) "
L5:
; Fused expression:    "++p(2) *(@4) *(1) ax "
    mov     ax, [bp+4]
    inc     word [bp+4]
    mov     bx, ax
    mov     al, [bx]
    cbw
; JumpIfZero
    test    ax, ax
    je      L6
; RPN'ized expression: "l ++ "
; Expanded expression: "(@-2) ++(2) "
; Fused expression:    "++(2) *(@-2) "
    inc     word [bp-2]
    mov     ax, [bp-2]
    jmp     L5
L6:
; return
; RPN'ized expression: "l "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
    mov     ax, [bp-2]
    jmp     L4
L4:
    leave
    ret
; SEGMENT _TEXT
; glb strchr : (
; prm     s : * char
; prm     c : int
;     ) * char
SEGMENT _TEXT
    global  _strchr
_strchr:
    push    bp
    mov     bp, sp
; loc     s : (@4): * char
; loc     c : (@6): int
; do
L8:
; {
; if
; RPN'ized expression: "s *u c == "
; Expanded expression: "(@4) *(2) *(1) (@6) *(2) == "
; Fused expression:    "*(2) (@4) == *ax *(@6) IF! "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, [bp+6]
    jne     L11
; return
; RPN'ized expression: "s "
; Expanded expression: "(@4) *(2) "
; Fused expression:    "*(2) (@4) "
    mov     ax, [bp+4]
    jmp     L7
L11:
; }
; while
; RPN'ized expression: "s ++p *u 0 != "
; Expanded expression: "(@4) ++p(2) *(1) 0 != "
L9:
; Fused expression:    "++p(2) *(@4) != *ax 0 IF "
    mov     ax, [bp+4]
    inc     word [bp+4]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 0
    jne     L8
L10:
; return
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "0 "
    mov     ax, 0
    jmp     L7
L7:
    leave
    ret
; SEGMENT _TEXT
; glb puts : (
; prm     s : * char
;     ) int
SEGMENT _TEXT
    global  _puts
_puts:
    push    bp
    mov     bp, sp
; loc     s : (@4): * char
; while
; RPN'ized expression: "s *u "
; Expanded expression: "(@4) *(2) *(1) "
L14:
; Fused expression:    "*(2) (@4) *(1) ax "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     al, [bx]
    cbw
; JumpIfZero
    test    ax, ax
    je      L15
; RPN'ized expression: "( s ++p *u putchar ) "
; Expanded expression: " (@4) ++p(2) *(1)  putchar ()2 "
; Fused expression:    "( ++p(2) *(@4) *(1) ax , putchar )2 "
    mov     ax, [bp+4]
    inc     word [bp+4]
    mov     bx, ax
    mov     al, [bx]
    cbw
    push    ax
    call    _putchar
    sub     sp, -2
    jmp     L14
L15:
; RPN'ized expression: "( 10 putchar ) "
; Expanded expression: " 10  putchar ()2 "
; Fused expression:    "( 10 , putchar )2 "
    push    10
    call    _putchar
    sub     sp, -2
; return
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "0 "
    mov     ax, 0
    jmp     L13
L13:
    leave
    ret
; SEGMENT _TEXT
; glb isspace : (
; prm     c : int
;     ) int
SEGMENT _TEXT
    global  _isspace
_isspace:
    push    bp
    mov     bp, sp
; loc     c : (@4): int
; return
; RPN'ized expression: "c 32 == c 12 == || c 10 == || c 13 == || c 9 == || c 11 == || "
; Expanded expression: "(@4) *(2) 32 == _Bool [sh||->21] (@4) *(2) 12 == _Bool ||[21] _Bool [sh||->20] (@4) *(2) 10 == _Bool ||[20] _Bool [sh||->19] (@4) *(2) 13 == _Bool ||[19] _Bool [sh||->18] (@4) *(2) 9 == _Bool ||[18] _Bool [sh||->17] (@4) *(2) 11 == _Bool ||[17] "
; Fused expression:    "== *(@4) 32 _Bool [sh||->21] == *(@4) 12 _Bool ||[21] _Bool [sh||->20] == *(@4) 10 _Bool ||[20] _Bool [sh||->19] == *(@4) 13 _Bool ||[19] _Bool [sh||->18] == *(@4) 9 _Bool ||[18] _Bool [sh||->17] == *(@4) 11 _Bool ||[17] "
    mov     ax, [bp+4]
    cmp     ax, 32
    sete    al
    cbw
    test    ax, ax
    setne   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jne     L21
    mov     ax, [bp+4]
    cmp     ax, 12
    sete    al
    cbw
    test    ax, ax
    setne   al
    cbw
L21:
    test    ax, ax
    setne   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jne     L20
    mov     ax, [bp+4]
    cmp     ax, 10
    sete    al
    cbw
    test    ax, ax
    setne   al
    cbw
L20:
    test    ax, ax
    setne   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jne     L19
    mov     ax, [bp+4]
    cmp     ax, 13
    sete    al
    cbw
    test    ax, ax
    setne   al
    cbw
L19:
    test    ax, ax
    setne   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jne     L18
    mov     ax, [bp+4]
    cmp     ax, 9
    sete    al
    cbw
    test    ax, ax
    setne   al
    cbw
L18:
    test    ax, ax
    setne   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jne     L17
    mov     ax, [bp+4]
    cmp     ax, 11
    sete    al
    cbw
    test    ax, ax
    setne   al
    cbw
L17:
    jmp     L16
L16:
    leave
    ret
; SEGMENT _TEXT
; glb isdigit : (
; prm     c : int
;     ) int
SEGMENT _TEXT
    global  _isdigit
_isdigit:
    push    bp
    mov     bp, sp
; loc     c : (@4): int
; return
; RPN'ized expression: "c 48 >= c 57 <= && "
; Expanded expression: "(@4) *(2) 48 >= _Bool [sh&&->23] (@4) *(2) 57 <= _Bool &&[23] "
; Fused expression:    ">= *(@4) 48 _Bool [sh&&->23] <= *(@4) 57 _Bool &&[23] "
    mov     ax, [bp+4]
    cmp     ax, 48
    setge   al
    cbw
    test    ax, ax
    setne   al
    cbw
; JumpIfZero
    test    ax, ax
    je      L23
    mov     ax, [bp+4]
    cmp     ax, 57
    setle   al
    cbw
    test    ax, ax
    setne   al
    cbw
L23:
    jmp     L22
L22:
    leave
    ret
; SEGMENT _TEXT
; glb printf : (
; prm     fmt : * char
; prm     ...
;     ) int
SEGMENT _TEXT
    global  _printf
_printf:
    push    bp
    mov     bp, sp
; loc     fmt : (@4): * char
; loc     pp : (@-2): * int
    sub     sp, 2
; =
; RPN'ized expression: "fmt &u "
; Expanded expression: "(@4) "
; Fused expression:    "=(34) *(@-2) (@4) "
    lea     ax, [bp+4]
    mov     [bp-2], ax
; loc     cnt : (@-4): int
    sub     sp, 2
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "=(34) *(@-4) 0 "
    mov     ax, 0
    mov     [bp-4], ax
; loc     p : (@-6): * char
    sub     sp, 2
; loc     phex : (@-8): * char
    sub     sp, 2
; =
; RPN'ized expression: "L25 "
; Expanded expression: "L25 "
; SEGMENT _TEXT
SEGMENT _DATA
L25:
    db  "0123456789abcdef",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "=(34) *(@-8) L25 "
    mov     ax, L25
    mov     [bp-8], ax
; RPN'ized expression: "1 10 + 1 + "
; Expanded expression: "12 "
; Expression value: 12
; loc     s : (@-20): [12] char
    sub     sp, 12
; loc     pc : (@-22): * char
    sub     sp, 2
; loc     n : (@-24): int
    sub     sp, 2
; loc     sign : (@-26): int
    sub     sp, 2
; loc     minlen : (@-28): int
    sub     sp, 2
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "=(34) *(@-28) 0 "
    mov     ax, 0
    mov     [bp-28], ax
; loc     len : (@-30): int
    sub     sp, 2
; RPN'ized expression: "pp ++p "
; Expanded expression: "(@-2) 2 +=p(2) "
; Fused expression:    "+=p(2) *(@-2) 2 "
    mov     ax, [bp-2]
    add     word [bp-2], 2
; for
; RPN'ized expression: "p fmt = "
; Expanded expression: "(@-6) (@4) *(2) =(2) "
; Fused expression:    "=(34) *(@-6) *(@4) "
    mov     ax, [bp+4]
    mov     [bp-6], ax
L27:
; RPN'ized expression: "p *u 0 != "
; Expanded expression: "(@-6) *(2) *(1) 0 != "
; Fused expression:    "*(2) (@-6) != *ax 0 IF! "
    mov     ax, [bp-6]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 0
    je      L30
    jmp     L29
L28:
; RPN'ized expression: "p ++p "
; Expanded expression: "(@-6) ++p(2) "
; Fused expression:    "++p(2) *(@-6) "
    mov     ax, [bp-6]
    inc     word [bp-6]
    jmp     L27
L29:
; {
; if
; RPN'ized expression: "p *u 37 != p 1 + *u 37 == || "
; Expanded expression: "(@-6) *(2) *(1) 37 != _Bool [sh||->33] (@-6) *(2) 1 + *(1) 37 == _Bool ||[33] "
; Fused expression:    "*(2) (@-6) != *ax 37 _Bool [sh||->33] + *(@-6) 1 == *ax 37 _Bool ||[33] "
    mov     ax, [bp-6]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 37
    setne   al
    cbw
    test    ax, ax
    setne   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jne     L33
    mov     ax, [bp-6]
    add     ax, 1
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 37
    sete    al
    cbw
    test    ax, ax
    setne   al
    cbw
L33:
; JumpIfZero
    test    ax, ax
    je      L31
; {
; RPN'ized expression: "( p *u putchar ) "
; Expanded expression: " (@-6) *(2) *(1)  putchar ()2 "
; Fused expression:    "( *(2) (@-6) *(1) ax , putchar )2 "
    mov     ax, [bp-6]
    mov     bx, ax
    mov     al, [bx]
    cbw
    push    ax
    call    _putchar
    sub     sp, -2
; RPN'ized expression: "p p p *u 37 == + = "
; Expanded expression: "(@-6) (@-6) *(2) (@-6) *(2) *(1) 37 == + =(2) "
; Fused expression:    "*(2) (@-6) == *ax 37 + *(@-6) ax =(34) *(@-6) ax "
    mov     ax, [bp-6]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 37
    sete    al
    cbw
    mov     cx, ax
    mov     ax, [bp-6]
    add     ax, cx
    mov     [bp-6], ax
; RPN'ized expression: "cnt ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
    mov     ax, [bp-4]
    inc     word [bp-4]
; continue
    jmp     L28
; }
L31:
; RPN'ized expression: "p ++p "
; Expanded expression: "(@-6) ++p(2) "
; Fused expression:    "++p(2) *(@-6) "
    mov     ax, [bp-6]
    inc     word [bp-6]
; RPN'ized expression: "minlen 0 = "
; Expanded expression: "(@-28) 0 =(2) "
; Fused expression:    "=(34) *(@-28) 0 "
    mov     ax, 0
    mov     [bp-28], ax
; if
; RPN'ized expression: "( p *u isdigit ) "
; Expanded expression: " (@-6) *(2) *(1)  isdigit ()2 "
; Fused expression:    "( *(2) (@-6) *(1) ax , isdigit )2 "
    mov     ax, [bp-6]
    mov     bx, ax
    mov     al, [bx]
    cbw
    push    ax
    call    _isdigit
    sub     sp, -2
; JumpIfZero
    test    ax, ax
    je      L34
; {
; while
; RPN'ized expression: "( p *u isdigit ) "
; Expanded expression: " (@-6) *(2) *(1)  isdigit ()2 "
L36:
; Fused expression:    "( *(2) (@-6) *(1) ax , isdigit )2 "
    mov     ax, [bp-6]
    mov     bx, ax
    mov     al, [bx]
    cbw
    push    ax
    call    _isdigit
    sub     sp, -2
; JumpIfZero
    test    ax, ax
    je      L37
; RPN'ized expression: "minlen minlen 10 * p ++p *u + 48 - = "
; Expanded expression: "(@-28) (@-28) *(2) 10 * (@-6) ++p(2) *(1) + 48 - =(2) "
; Fused expression:    "* *(@-28) 10 push-ax ++p(2) *(@-6) + *sp *ax - ax 48 =(34) *(@-28) ax "
    mov     ax, [bp-28]
    imul    ax, ax, 10
    push    ax
    mov     ax, [bp-6]
    inc     word [bp-6]
    mov     bx, ax
    movsx   cx, byte [bx]
    pop     ax
    add     ax, cx
    sub     ax, 48
    mov     [bp-28], ax
    jmp     L36
L37:
; }
L34:
; switch
; RPN'ized expression: "p *u "
; Expanded expression: "(@-6) *(2) *(1) "
; Fused expression:    "*(2) (@-6) *(1) ax "
    mov     ax, [bp-6]
    mov     bx, ax
    mov     al, [bx]
    cbw
    jmp     L40
; {
; case
; RPN'ized expression: "99 "
; Expanded expression: "99 "
; Expression value: 99
    jmp     L41
L40:
    cmp     ax, 99
    jne     L42
L41:
; while
; RPN'ized expression: "minlen 1 > "
; Expanded expression: "(@-28) *(2) 1 > "
L44:
; Fused expression:    "> *(@-28) 1 IF! "
    mov     ax, [bp-28]
    cmp     ax, 1
    jle     L45
; {
; RPN'ized expression: "( 32 putchar ) "
; Expanded expression: " 32  putchar ()2 "
; Fused expression:    "( 32 , putchar )2 "
    push    32
    call    _putchar
    sub     sp, -2
; RPN'ized expression: "cnt ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
    mov     ax, [bp-4]
    inc     word [bp-4]
; RPN'ized expression: "minlen --p "
; Expanded expression: "(@-28) --p(2) "
; Fused expression:    "--p(2) *(@-28) "
    mov     ax, [bp-28]
    dec     word [bp-28]
; }
    jmp     L44
L45:
; RPN'ized expression: "( pp ++p *u putchar ) "
; Expanded expression: " (@-2) 2 +=p(2) *(2)  putchar ()2 "
; Fused expression:    "( +=p(2) *(@-2) 2 *(2) ax , putchar )2 "
    mov     ax, [bp-2]
    add     word [bp-2], 2
    mov     bx, ax
    push    word [bx]
    call    _putchar
    sub     sp, -2
; RPN'ized expression: "cnt ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
    mov     ax, [bp-4]
    inc     word [bp-4]
; break
    jmp     L38
; case
; RPN'ized expression: "115 "
; Expanded expression: "115 "
; Expression value: 115
    jmp     L43
L42:
    cmp     ax, 115
    jne     L46
L43:
; RPN'ized expression: "pc pp ++p *u = "
; Expanded expression: "(@-22) (@-2) 2 +=p(2) *(2) =(2) "
; Fused expression:    "+=p(2) *(@-2) 2 =(34) *(@-22) *ax "
    mov     ax, [bp-2]
    add     word [bp-2], 2
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-22], ax
; RPN'ized expression: "len 0 = "
; Expanded expression: "(@-30) 0 =(2) "
; Fused expression:    "=(34) *(@-30) 0 "
    mov     ax, 0
    mov     [bp-30], ax
; if
; RPN'ized expression: "pc "
; Expanded expression: "(@-22) *(2) "
; Fused expression:    "*(2) (@-22) "
    mov     ax, [bp-22]
; JumpIfZero
    test    ax, ax
    je      L48
; RPN'ized expression: "len ( pc strlen ) = "
; Expanded expression: "(@-30)  (@-22) *(2)  strlen ()2 =(2) "
; Fused expression:    "( *(2) (@-22) , strlen )2 =(34) *(@-30) ax "
    push    word [bp-22]
    call    _strlen
    sub     sp, -2
    mov     [bp-30], ax
L48:
; while
; RPN'ized expression: "minlen len > "
; Expanded expression: "(@-28) *(2) (@-30) *(2) > "
L50:
; Fused expression:    "> *(@-28) *(@-30) IF! "
    mov     ax, [bp-28]
    cmp     ax, [bp-30]
    jle     L51
; {
; RPN'ized expression: "( 32 putchar ) "
; Expanded expression: " 32  putchar ()2 "
; Fused expression:    "( 32 , putchar )2 "
    push    32
    call    _putchar
    sub     sp, -2
; RPN'ized expression: "cnt ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
    mov     ax, [bp-4]
    inc     word [bp-4]
; RPN'ized expression: "minlen --p "
; Expanded expression: "(@-28) --p(2) "
; Fused expression:    "--p(2) *(@-28) "
    mov     ax, [bp-28]
    dec     word [bp-28]
; }
    jmp     L50
L51:
; if
; RPN'ized expression: "len "
; Expanded expression: "(@-30) *(2) "
; Fused expression:    "*(2) (@-30) "
    mov     ax, [bp-30]
; JumpIfZero
    test    ax, ax
    je      L52
; while
; RPN'ized expression: "pc *u 0 != "
; Expanded expression: "(@-22) *(2) *(1) 0 != "
L54:
; Fused expression:    "*(2) (@-22) != *ax 0 IF! "
    mov     ax, [bp-22]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 0
    je      L55
; {
; RPN'ized expression: "( pc ++p *u putchar ) "
; Expanded expression: " (@-22) ++p(2) *(1)  putchar ()2 "
; Fused expression:    "( ++p(2) *(@-22) *(1) ax , putchar )2 "
    mov     ax, [bp-22]
    inc     word [bp-22]
    mov     bx, ax
    mov     al, [bx]
    cbw
    push    ax
    call    _putchar
    sub     sp, -2
; RPN'ized expression: "cnt ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
    mov     ax, [bp-4]
    inc     word [bp-4]
; }
    jmp     L54
L55:
L52:
; break
    jmp     L38
; case
; RPN'ized expression: "105 "
; Expanded expression: "105 "
; Expression value: 105
    jmp     L47
L46:
    cmp     ax, 105
    jne     L56
L47:
; case
; RPN'ized expression: "100 "
; Expanded expression: "100 "
; Expression value: 100
    jmp     L57
L56:
    cmp     ax, 100
    jne     L58
L57:
; RPN'ized expression: "pc s s sizeof 1 - + *u &u = "
; Expanded expression: "(@-22) (@-20) 11 + =(2) "
; Fused expression:    "+ (@-20) 11 =(34) *(@-22) ax "
    lea     ax, [bp-20]
    add     ax, 11
    mov     [bp-22], ax
; RPN'ized expression: "pc *u 0 = "
; Expanded expression: "(@-22) *(2) 0 =(1) "
; Fused expression:    "*(2) (@-22) =(18) *ax 0 "
    mov     ax, [bp-22]
    mov     bx, ax
    mov     ax, 0
    mov     [bx], al
    cbw
; RPN'ized expression: "len 0 = "
; Expanded expression: "(@-30) 0 =(2) "
; Fused expression:    "=(34) *(@-30) 0 "
    mov     ax, 0
    mov     [bp-30], ax
; RPN'ized expression: "n pp ++p *u = "
; Expanded expression: "(@-24) (@-2) 2 +=p(2) *(2) =(2) "
; Fused expression:    "+=p(2) *(@-2) 2 =(34) *(@-24) *ax "
    mov     ax, [bp-2]
    add     word [bp-2], 2
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-24], ax
; RPN'ized expression: "sign 1 2 n 0 < * - = "
; Expanded expression: "(@-26) 1 2 (@-24) *(2) 0 < * - =(2) "
; Fused expression:    "< *(@-24) 0 * 2 ax - 1 ax =(34) *(@-26) ax "
    mov     ax, [bp-24]
    cmp     ax, 0
    setl    al
    cbw
    mov     cx, ax
    mov     ax, 2
    mul     cx
    mov     cx, ax
    mov     ax, 1
    sub     ax, cx
    mov     [bp-26], ax
; do
L60:
; {
; RPN'ized expression: "pc -- *u 48 n n 10 / 10 * - sign * + = "
; Expanded expression: "(@-22) --(2) 48 (@-24) *(2) (@-24) *(2) 10 / 10 * - (@-26) *(2) * + =(1) "
; Fused expression:    "--(2) *(@-22) push-ax / *(@-24) 10 * ax 10 - *(@-24) ax * ax *(@-26) + 48 ax =(18) **sp ax "
    dec     word [bp-22]
    mov     ax, [bp-22]
    push    ax
    mov     ax, [bp-24]
    cwd
    mov     cx, 10
    idiv    cx
    imul    ax, ax, 10
    mov     cx, ax
    mov     ax, [bp-24]
    sub     ax, cx
    mul     word [bp-26]
    mov     cx, ax
    mov     ax, 48
    add     ax, cx
    pop     bx
    mov     [bx], al
    cbw
; RPN'ized expression: "n n 10 / = "
; Expanded expression: "(@-24) (@-24) *(2) 10 / =(2) "
; Fused expression:    "/ *(@-24) 10 =(34) *(@-24) ax "
    mov     ax, [bp-24]
    cwd
    mov     cx, 10
    idiv    cx
    mov     [bp-24], ax
; RPN'ized expression: "len ++p "
; Expanded expression: "(@-30) ++p(2) "
; Fused expression:    "++p(2) *(@-30) "
    mov     ax, [bp-30]
    inc     word [bp-30]
; }
; while
; RPN'ized expression: "n "
; Expanded expression: "(@-24) *(2) "
L61:
; Fused expression:    "*(2) (@-24) "
    mov     ax, [bp-24]
; JumpIfNotZero
    test    ax, ax
    jne     L60
L62:
; if
; RPN'ized expression: "sign 0 < "
; Expanded expression: "(@-26) *(2) 0 < "
; Fused expression:    "< *(@-26) 0 IF! "
    mov     ax, [bp-26]
    cmp     ax, 0
    jge     L63
; {
; RPN'ized expression: "pc -- *u 45 = "
; Expanded expression: "(@-22) --(2) 45 =(1) "
; Fused expression:    "--(2) *(@-22) =(18) *ax 45 "
    dec     word [bp-22]
    mov     ax, [bp-22]
    mov     bx, ax
    mov     ax, 45
    mov     [bx], al
    cbw
; RPN'ized expression: "len ++p "
; Expanded expression: "(@-30) ++p(2) "
; Fused expression:    "++p(2) *(@-30) "
    mov     ax, [bp-30]
    inc     word [bp-30]
; }
L63:
; while
; RPN'ized expression: "minlen len > "
; Expanded expression: "(@-28) *(2) (@-30) *(2) > "
L65:
; Fused expression:    "> *(@-28) *(@-30) IF! "
    mov     ax, [bp-28]
    cmp     ax, [bp-30]
    jle     L66
; {
; RPN'ized expression: "( 32 putchar ) "
; Expanded expression: " 32  putchar ()2 "
; Fused expression:    "( 32 , putchar )2 "
    push    32
    call    _putchar
    sub     sp, -2
; RPN'ized expression: "cnt ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
    mov     ax, [bp-4]
    inc     word [bp-4]
; RPN'ized expression: "minlen --p "
; Expanded expression: "(@-28) --p(2) "
; Fused expression:    "--p(2) *(@-28) "
    mov     ax, [bp-28]
    dec     word [bp-28]
; }
    jmp     L65
L66:
; while
; RPN'ized expression: "pc *u 0 != "
; Expanded expression: "(@-22) *(2) *(1) 0 != "
L67:
; Fused expression:    "*(2) (@-22) != *ax 0 IF! "
    mov     ax, [bp-22]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 0
    je      L68
; {
; RPN'ized expression: "( pc ++p *u putchar ) "
; Expanded expression: " (@-22) ++p(2) *(1)  putchar ()2 "
; Fused expression:    "( ++p(2) *(@-22) *(1) ax , putchar )2 "
    mov     ax, [bp-22]
    inc     word [bp-22]
    mov     bx, ax
    mov     al, [bx]
    cbw
    push    ax
    call    _putchar
    sub     sp, -2
; RPN'ized expression: "cnt ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
    mov     ax, [bp-4]
    inc     word [bp-4]
; }
    jmp     L67
L68:
; break
    jmp     L38
; case
; RPN'ized expression: "88 "
; Expanded expression: "88 "
; Expression value: 88
    jmp     L59
L58:
    cmp     ax, 88
    jne     L69
L59:
; RPN'ized expression: "phex L71 = "
; Expanded expression: "(@-8) L71 =(2) "
; SEGMENT _TEXT
SEGMENT _DATA
L71:
    db  "0123456789ABCDEF",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "=(34) *(@-8) L71 "
    mov     ax, L71
    mov     [bp-8], ax
; case
; RPN'ized expression: "112 "
; Expanded expression: "112 "
; Expression value: 112
    jmp     L70
L69:
    cmp     ax, 112
    jne     L73
L70:
; case
; RPN'ized expression: "120 "
; Expanded expression: "120 "
; Expression value: 120
    jmp     L74
L73:
    cmp     ax, 120
    jne     L75
L74:
; RPN'ized expression: "pc s s sizeof 1 - + *u &u = "
; Expanded expression: "(@-22) (@-20) 11 + =(2) "
; Fused expression:    "+ (@-20) 11 =(34) *(@-22) ax "
    lea     ax, [bp-20]
    add     ax, 11
    mov     [bp-22], ax
; RPN'ized expression: "pc *u 0 = "
; Expanded expression: "(@-22) *(2) 0 =(1) "
; Fused expression:    "*(2) (@-22) =(18) *ax 0 "
    mov     ax, [bp-22]
    mov     bx, ax
    mov     ax, 0
    mov     [bx], al
    cbw
; RPN'ized expression: "len 0 = "
; Expanded expression: "(@-30) 0 =(2) "
; Fused expression:    "=(34) *(@-30) 0 "
    mov     ax, 0
    mov     [bp-30], ax
; RPN'ized expression: "n pp ++p *u = "
; Expanded expression: "(@-24) (@-2) 2 +=p(2) *(2) =(2) "
; Fused expression:    "+=p(2) *(@-2) 2 =(34) *(@-24) *ax "
    mov     ax, [bp-2]
    add     word [bp-2], 2
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-24], ax
; do
L77:
; {
; RPN'ized expression: "pc -- *u phex n 15 & + *u = "
; Expanded expression: "(@-22) --(2) (@-8) *(2) (@-24) *(2) 15 & + *(1) =(1) "
; Fused expression:    "--(2) *(@-22) push-ax & *(@-24) 15 + *(@-8) ax =(17) **sp *ax "
    dec     word [bp-22]
    mov     ax, [bp-22]
    push    ax
    mov     ax, [bp-24]
    and     ax, 15
    mov     cx, ax
    mov     ax, [bp-8]
    add     ax, cx
    mov     bx, ax
    mov     al, [bx]
    cbw
    pop     bx
    mov     [bx], al
    cbw
; RPN'ized expression: "n n 4 >> 1 8 n sizeof * 4 - << 1 - & = "
; Expanded expression: "(@-24) (@-24) *(2) 4 >> 4095 & =(2) "
; Fused expression:    ">> *(@-24) 4 & ax 4095 =(34) *(@-24) ax "
    mov     ax, [bp-24]
    sar     ax, 4
    and     ax, 4095
    mov     [bp-24], ax
; RPN'ized expression: "len ++p "
; Expanded expression: "(@-30) ++p(2) "
; Fused expression:    "++p(2) *(@-30) "
    mov     ax, [bp-30]
    inc     word [bp-30]
; }
; while
; RPN'ized expression: "n "
; Expanded expression: "(@-24) *(2) "
L78:
; Fused expression:    "*(2) (@-24) "
    mov     ax, [bp-24]
; JumpIfNotZero
    test    ax, ax
    jne     L77
L79:
; while
; RPN'ized expression: "minlen len > "
; Expanded expression: "(@-28) *(2) (@-30) *(2) > "
L80:
; Fused expression:    "> *(@-28) *(@-30) IF! "
    mov     ax, [bp-28]
    cmp     ax, [bp-30]
    jle     L81
; {
; RPN'ized expression: "( 32 putchar ) "
; Expanded expression: " 32  putchar ()2 "
; Fused expression:    "( 32 , putchar )2 "
    push    32
    call    _putchar
    sub     sp, -2
; RPN'ized expression: "cnt ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
    mov     ax, [bp-4]
    inc     word [bp-4]
; RPN'ized expression: "minlen --p "
; Expanded expression: "(@-28) --p(2) "
; Fused expression:    "--p(2) *(@-28) "
    mov     ax, [bp-28]
    dec     word [bp-28]
; }
    jmp     L80
L81:
; while
; RPN'ized expression: "pc *u 0 != "
; Expanded expression: "(@-22) *(2) *(1) 0 != "
L82:
; Fused expression:    "*(2) (@-22) != *ax 0 IF! "
    mov     ax, [bp-22]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 0
    je      L83
; {
; RPN'ized expression: "( pc ++p *u putchar ) "
; Expanded expression: " (@-22) ++p(2) *(1)  putchar ()2 "
; Fused expression:    "( ++p(2) *(@-22) *(1) ax , putchar )2 "
    mov     ax, [bp-22]
    inc     word [bp-22]
    mov     bx, ax
    mov     al, [bx]
    cbw
    push    ax
    call    _putchar
    sub     sp, -2
; RPN'ized expression: "cnt ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
    mov     ax, [bp-4]
    inc     word [bp-4]
; }
    jmp     L82
L83:
; break
    jmp     L38
; case
; RPN'ized expression: "111 "
; Expanded expression: "111 "
; Expression value: 111
    jmp     L76
L75:
    cmp     ax, 111
    jne     L84
L76:
; RPN'ized expression: "pc s s sizeof 1 - + *u &u = "
; Expanded expression: "(@-22) (@-20) 11 + =(2) "
; Fused expression:    "+ (@-20) 11 =(34) *(@-22) ax "
    lea     ax, [bp-20]
    add     ax, 11
    mov     [bp-22], ax
; RPN'ized expression: "pc *u 0 = "
; Expanded expression: "(@-22) *(2) 0 =(1) "
; Fused expression:    "*(2) (@-22) =(18) *ax 0 "
    mov     ax, [bp-22]
    mov     bx, ax
    mov     ax, 0
    mov     [bx], al
    cbw
; RPN'ized expression: "len 0 = "
; Expanded expression: "(@-30) 0 =(2) "
; Fused expression:    "=(34) *(@-30) 0 "
    mov     ax, 0
    mov     [bp-30], ax
; RPN'ized expression: "n pp ++p *u = "
; Expanded expression: "(@-24) (@-2) 2 +=p(2) *(2) =(2) "
; Fused expression:    "+=p(2) *(@-2) 2 =(34) *(@-24) *ax "
    mov     ax, [bp-2]
    add     word [bp-2], 2
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-24], ax
; do
L86:
; {
; RPN'ized expression: "pc -- *u 48 n 7 & + = "
; Expanded expression: "(@-22) --(2) 48 (@-24) *(2) 7 & + =(1) "
; Fused expression:    "--(2) *(@-22) push-ax & *(@-24) 7 + 48 ax =(18) **sp ax "
    dec     word [bp-22]
    mov     ax, [bp-22]
    push    ax
    mov     ax, [bp-24]
    and     ax, 7
    mov     cx, ax
    mov     ax, 48
    add     ax, cx
    pop     bx
    mov     [bx], al
    cbw
; RPN'ized expression: "n n 3 >> 1 8 n sizeof * 3 - << 1 - & = "
; Expanded expression: "(@-24) (@-24) *(2) 3 >> 8191 & =(2) "
; Fused expression:    ">> *(@-24) 3 & ax 8191 =(34) *(@-24) ax "
    mov     ax, [bp-24]
    sar     ax, 3
    and     ax, 8191
    mov     [bp-24], ax
; RPN'ized expression: "len ++p "
; Expanded expression: "(@-30) ++p(2) "
; Fused expression:    "++p(2) *(@-30) "
    mov     ax, [bp-30]
    inc     word [bp-30]
; }
; while
; RPN'ized expression: "n "
; Expanded expression: "(@-24) *(2) "
L87:
; Fused expression:    "*(2) (@-24) "
    mov     ax, [bp-24]
; JumpIfNotZero
    test    ax, ax
    jne     L86
L88:
; while
; RPN'ized expression: "minlen len > "
; Expanded expression: "(@-28) *(2) (@-30) *(2) > "
L89:
; Fused expression:    "> *(@-28) *(@-30) IF! "
    mov     ax, [bp-28]
    cmp     ax, [bp-30]
    jle     L90
; {
; RPN'ized expression: "( 32 putchar ) "
; Expanded expression: " 32  putchar ()2 "
; Fused expression:    "( 32 , putchar )2 "
    push    32
    call    _putchar
    sub     sp, -2
; RPN'ized expression: "cnt ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
    mov     ax, [bp-4]
    inc     word [bp-4]
; RPN'ized expression: "minlen --p "
; Expanded expression: "(@-28) --p(2) "
; Fused expression:    "--p(2) *(@-28) "
    mov     ax, [bp-28]
    dec     word [bp-28]
; }
    jmp     L89
L90:
; while
; RPN'ized expression: "pc *u 0 != "
; Expanded expression: "(@-22) *(2) *(1) 0 != "
L91:
; Fused expression:    "*(2) (@-22) != *ax 0 IF! "
    mov     ax, [bp-22]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 0
    je      L92
; {
; RPN'ized expression: "( pc ++p *u putchar ) "
; Expanded expression: " (@-22) ++p(2) *(1)  putchar ()2 "
; Fused expression:    "( ++p(2) *(@-22) *(1) ax , putchar )2 "
    mov     ax, [bp-22]
    inc     word [bp-22]
    mov     bx, ax
    mov     al, [bx]
    cbw
    push    ax
    call    _putchar
    sub     sp, -2
; RPN'ized expression: "cnt ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
    mov     ax, [bp-4]
    inc     word [bp-4]
; }
    jmp     L91
L92:
; break
    jmp     L38
; default
L39:
; return
; RPN'ized expression: "1 -u "
; Expanded expression: "-1 "
; Expression value: -1
; Fused expression:    "-1 "
    mov     ax, -1
    jmp     L24
; }
    jmp     L38
L84:
    jmp     L39
L38:
; }
    jmp     L28
L30:
; return
; RPN'ized expression: "cnt "
; Expanded expression: "(@-4) *(2) "
; Fused expression:    "*(2) (@-4) "
    mov     ax, [bp-4]
    jmp     L24
L24:
    leave
    ret
; SEGMENT _TEXT
; glb putdec : (
; prm     n : int
;     ) void
SEGMENT _TEXT
    global  _putdec
_putdec:
    push    bp
    mov     bp, sp
; loc     n : (@4): int
; loc     r : (@-2): int
    sub     sp, 2
; if
; RPN'ized expression: "n 0 < "
; Expanded expression: "(@4) *(2) 0 < "
; Fused expression:    "< *(@4) 0 IF! "
    mov     ax, [bp+4]
    cmp     ax, 0
    jge     L94
; {
; RPN'ized expression: "( 45 putchar ) "
; Expanded expression: " 45  putchar ()2 "
; Fused expression:    "( 45 , putchar )2 "
    push    45
    call    _putchar
    sub     sp, -2
; RPN'ized expression: "r n 10 / 10 * n - = "
; Expanded expression: "(@-2) (@4) *(2) 10 / 10 * (@4) *(2) - =(2) "
; Fused expression:    "/ *(@4) 10 * ax 10 - ax *(@4) =(34) *(@-2) ax "
    mov     ax, [bp+4]
    cwd
    mov     cx, 10
    idiv    cx
    imul    ax, ax, 10
    sub     ax, [bp+4]
    mov     [bp-2], ax
; RPN'ized expression: "n n 10 -u / = "
; Expanded expression: "(@4) (@4) *(2) -10 / =(2) "
; Fused expression:    "/ *(@4) -10 =(34) *(@4) ax "
    mov     ax, [bp+4]
    cwd
    mov     cx, -10
    idiv    cx
    mov     [bp+4], ax
; }
    jmp     L95
L94:
; else
; {
; RPN'ized expression: "r n 10 % = "
; Expanded expression: "(@-2) (@4) *(2) 10 % =(2) "
; Fused expression:    "% *(@4) 10 =(34) *(@-2) ax "
    mov     ax, [bp+4]
    cwd
    mov     cx, 10
    idiv    cx
    mov     ax, dx
    mov     [bp-2], ax
; RPN'ized expression: "n n 10 / = "
; Expanded expression: "(@4) (@4) *(2) 10 / =(2) "
; Fused expression:    "/ *(@4) 10 =(34) *(@4) ax "
    mov     ax, [bp+4]
    cwd
    mov     cx, 10
    idiv    cx
    mov     [bp+4], ax
; }
L95:
; if
; RPN'ized expression: "n "
; Expanded expression: "(@4) *(2) "
; Fused expression:    "*(2) (@4) "
    mov     ax, [bp+4]
; JumpIfZero
    test    ax, ax
    je      L96
; RPN'ized expression: "( n putdec ) "
; Expanded expression: " (@4) *(2)  putdec ()2 "
; Fused expression:    "( *(2) (@4) , putdec )2 "
    push    word [bp+4]
    call    _putdec
    sub     sp, -2
L96:
; RPN'ized expression: "( 48 r + putchar ) "
; Expanded expression: " 48 (@-2) *(2) +  putchar ()2 "
; Fused expression:    "( + 48 *(@-2) , putchar )2 "
    mov     ax, 48
    add     ax, [bp-2]
    push    ax
    call    _putchar
    sub     sp, -2
L93:
    leave
    ret
; SEGMENT _TEXT
; glb putdecu : (
; prm     n : int
;     ) void
SEGMENT _TEXT
    global  _putdecu
_putdecu:
    push    bp
    mov     bp, sp
; loc     n : (@4): int
; loc     r : (@-2): int
    sub     sp, 2
; if
; RPN'ized expression: "n 0 < "
; Expanded expression: "(@4) *(2) 0 < "
; Fused expression:    "< *(@4) 0 IF! "
    mov     ax, [bp+4]
    cmp     ax, 0
    jge     L99
; {
; loc         n2 : (@-4): int
    sub     sp, 2
; =
; RPN'ized expression: "n 1 >> 1 8 n sizeof * 1 - << 1 - & 5 / "
; Expanded expression: "(@4) *(2) 1 >> 32767 & 5 / "
; Fused expression:    ">> *(@4) 1 & ax 32767 / ax 5 =(34) *(@-4) ax "
    mov     ax, [bp+4]
    sar     ax, 1
    and     ax, 32767
    cwd
    mov     cx, 5
    idiv    cx
    mov     [bp-4], ax
; RPN'ized expression: "r n n2 10 * - = "
; Expanded expression: "(@-2) (@4) *(2) (@-4) *(2) 10 * - =(2) "
; Fused expression:    "* *(@-4) 10 - *(@4) ax =(34) *(@-2) ax "
    mov     ax, [bp-4]
    imul    ax, ax, 10
    mov     cx, ax
    mov     ax, [bp+4]
    sub     ax, cx
    mov     [bp-2], ax
; RPN'ized expression: "n n2 = "
; Expanded expression: "(@4) (@-4) *(2) =(2) "
; Fused expression:    "=(34) *(@4) *(@-4) "
    mov     ax, [bp-4]
    mov     [bp+4], ax
    sub     sp, -2
; }
    jmp     L100
L99:
; else
; {
; RPN'ized expression: "r n 10 % = "
; Expanded expression: "(@-2) (@4) *(2) 10 % =(2) "
; Fused expression:    "% *(@4) 10 =(34) *(@-2) ax "
    mov     ax, [bp+4]
    cwd
    mov     cx, 10
    idiv    cx
    mov     ax, dx
    mov     [bp-2], ax
; RPN'ized expression: "n n 10 / = "
; Expanded expression: "(@4) (@4) *(2) 10 / =(2) "
; Fused expression:    "/ *(@4) 10 =(34) *(@4) ax "
    mov     ax, [bp+4]
    cwd
    mov     cx, 10
    idiv    cx
    mov     [bp+4], ax
; }
L100:
; if
; RPN'ized expression: "n "
; Expanded expression: "(@4) *(2) "
; Fused expression:    "*(2) (@4) "
    mov     ax, [bp+4]
; JumpIfZero
    test    ax, ax
    je      L101
; RPN'ized expression: "( n putdecu ) "
; Expanded expression: " (@4) *(2)  putdecu ()2 "
; Fused expression:    "( *(2) (@4) , putdecu )2 "
    push    word [bp+4]
    call    _putdecu
    sub     sp, -2
L101:
; RPN'ized expression: "( 48 r + putchar ) "
; Expanded expression: " 48 (@-2) *(2) +  putchar ()2 "
; Fused expression:    "( + 48 *(@-2) , putchar )2 "
    mov     ax, 48
    add     ax, [bp-2]
    push    ax
    call    _putchar
    sub     sp, -2
L98:
    leave
    ret
; SEGMENT _TEXT
; glb fact : (
; prm     x : int
;     ) int
SEGMENT _TEXT
    global  _fact
_fact:
    push    bp
    mov     bp, sp
; loc     x : (@4): int
; if
; RPN'ized expression: "x 1 <= "
; Expanded expression: "(@4) *(2) 1 <= "
; Fused expression:    "<= *(@4) 1 IF! "
    mov     ax, [bp+4]
    cmp     ax, 1
    jg      L104
; return
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
    mov     ax, 1
    jmp     L103
L104:
; return
; RPN'ized expression: "x ( x 1 - fact ) * "
; Expanded expression: "(@4) *(2)  (@4) *(2) 1 -  fact ()2 * "
; Fused expression:    "( - *(@4) 1 , fact )2 * *(@4) ax "
    mov     ax, [bp+4]
    sub     ax, 1
    push    ax
    call    _fact
    sub     sp, -2
    mov     cx, ax
    mov     ax, [bp+4]
    mul     cx
    jmp     L103
L103:
    leave
    ret
; SEGMENT _TEXT
; glb fib : (
; prm     x : int
;     ) int
SEGMENT _TEXT
    global  _fib
_fib:
    push    bp
    mov     bp, sp
; loc     x : (@4): int
; if
; RPN'ized expression: "x 0 <= "
; Expanded expression: "(@4) *(2) 0 <= "
; Fused expression:    "<= *(@4) 0 IF! "
    mov     ax, [bp+4]
    cmp     ax, 0
    jg      L107
; return
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "0 "
    mov     ax, 0
    jmp     L106
    jmp     L108
L107:
; else
; if
; RPN'ized expression: "x 1 == "
; Expanded expression: "(@4) *(2) 1 == "
; Fused expression:    "== *(@4) 1 IF! "
    mov     ax, [bp+4]
    cmp     ax, 1
    jne     L109
; return
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
    mov     ax, 1
    jmp     L106
L109:
L108:
; return
; RPN'ized expression: "( x 1 - fib ) ( x 2 - fib ) + "
; Expanded expression: " (@4) *(2) 1 -  fib ()2  (@4) *(2) 2 -  fib ()2 + "
; Fused expression:    "( - *(@4) 1 , fib )2 push-ax ( - *(@4) 2 , fib )2 + *sp ax "
    mov     ax, [bp+4]
    sub     ax, 1
    push    ax
    call    _fib
    sub     sp, -2
    push    ax
    mov     ax, [bp+4]
    sub     ax, 2
    push    ax
    call    _fib
    sub     sp, -2
    mov     cx, ax
    pop     ax
    add     ax, cx
    jmp     L106
L106:
    leave
    ret
; SEGMENT _TEXT
; glb breakCont : (void) void
SEGMENT _TEXT
    global  _breakCont
_breakCont:
    push    bp
    mov     bp, sp
; loc     i : (@-2): int
    sub     sp, 2
; for
; RPN'ized expression: "i 0 = "
; Expanded expression: "(@-2) 0 =(2) "
; Fused expression:    "=(34) *(@-2) 0 "
    mov     ax, 0
    mov     [bp-2], ax
L112:
; RPN'ized expression: "i 10 < "
; Expanded expression: "(@-2) *(2) 10 < "
; Fused expression:    "< *(@-2) 10 IF! "
    mov     ax, [bp-2]
    cmp     ax, 10
    jge     L115
    jmp     L114
L113:
; RPN'ized expression: "i ++p "
; Expanded expression: "(@-2) ++p(2) "
; Fused expression:    "++p(2) *(@-2) "
    mov     ax, [bp-2]
    inc     word [bp-2]
    jmp     L112
L114:
; {
; loc         j : (@-4): int
    sub     sp, 2
; =
; RPN'ized expression: "i "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "=(34) *(@-4) *(@-2) "
    mov     ax, [bp-2]
    mov     [bp-4], ax
; if
; RPN'ized expression: "j 1 == "
; Expanded expression: "(@-4) *(2) 1 == "
; Fused expression:    "== *(@-4) 1 IF! "
    mov     ax, [bp-4]
    cmp     ax, 1
    jne     L116
; continue
    sub     sp, -2
    jmp     L113
L116:
; RPN'ized expression: "( j putdec ) "
; Expanded expression: " (@-4) *(2)  putdec ()2 "
; Fused expression:    "( *(2) (@-4) , putdec )2 "
    push    word [bp-4]
    call    _putdec
    sub     sp, -2
; if
; RPN'ized expression: "j 7 == "
; Expanded expression: "(@-4) *(2) 7 == "
; Fused expression:    "== *(@-4) 7 IF! "
    mov     ax, [bp-4]
    cmp     ax, 7
    jne     L118
; break
    sub     sp, -2
    jmp     L115
L118:
    sub     sp, -2
; }
    jmp     L113
L115:
; RPN'ized expression: "( 10 putchar ) "
; Expanded expression: " 10  putchar ()2 "
; Fused expression:    "( 10 , putchar )2 "
    push    10
    call    _putchar
    sub     sp, -2
L111:
    leave
    ret
; SEGMENT _TEXT
; glb PointerStew : (void) void
SEGMENT _TEXT
    global  _PointerStew
_PointerStew:
    push    bp
    mov     bp, sp
; RPN'ized expression: "4 "
; Expanded expression: "4 "
; Expression value: 4
; loc     c : (@-8): [4] * char
    sub     sp, 8
; RPN'ized expression: "4 "
; Expanded expression: "4 "
; Expression value: 4
; loc     cp : (@-16): [4] * * char
    sub     sp, 8
; loc     cpp : (@-18): * * * char
    sub     sp, 2
; =
; RPN'ized expression: "cp "
; Expanded expression: "(@-16) "
; Fused expression:    "=(34) *(@-18) (@-16) "
    lea     ax, [bp-16]
    mov     [bp-18], ax
; RPN'ized expression: "c 0 + *u L121 = "
; Expanded expression: "(@-8) 0 + L121 =(2) "
; SEGMENT _TEXT
SEGMENT _DATA
L121:
    db  "ENTER",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "+ (@-8) 0 =(34) *ax L121 "
    lea     ax, [bp-8]
    add     ax, 0
    mov     bx, ax
    mov     ax, L121
    mov     [bx], ax
; RPN'ized expression: "c 1 + *u L123 = "
; Expanded expression: "(@-8) 2 + L123 =(2) "
; SEGMENT _TEXT
SEGMENT _DATA
L123:
    db  "NEW",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "+ (@-8) 2 =(34) *ax L123 "
    lea     ax, [bp-8]
    add     ax, 2
    mov     bx, ax
    mov     ax, L123
    mov     [bx], ax
; RPN'ized expression: "c 2 + *u L125 = "
; Expanded expression: "(@-8) 4 + L125 =(2) "
; SEGMENT _TEXT
SEGMENT _DATA
L125:
    db  "POINT",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "+ (@-8) 4 =(34) *ax L125 "
    lea     ax, [bp-8]
    add     ax, 4
    mov     bx, ax
    mov     ax, L125
    mov     [bx], ax
; RPN'ized expression: "c 3 + *u L127 = "
; Expanded expression: "(@-8) 6 + L127 =(2) "
; SEGMENT _TEXT
SEGMENT _DATA
L127:
    db  "FIRST",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "+ (@-8) 6 =(34) *ax L127 "
    lea     ax, [bp-8]
    add     ax, 6
    mov     bx, ax
    mov     ax, L127
    mov     [bx], ax
; RPN'ized expression: "cp 0 + *u c 3 + = "
; Expanded expression: "(@-16) 0 + (@-8) 6 + =(2) "
; Fused expression:    "+ (@-16) 0 push-ax + (@-8) 6 =(34) **sp ax "
    lea     ax, [bp-16]
    add     ax, 0
    push    ax
    lea     ax, [bp-8]
    add     ax, 6
    pop     bx
    mov     [bx], ax
; RPN'ized expression: "cp 1 + *u c 2 + = "
; Expanded expression: "(@-16) 2 + (@-8) 4 + =(2) "
; Fused expression:    "+ (@-16) 2 push-ax + (@-8) 4 =(34) **sp ax "
    lea     ax, [bp-16]
    add     ax, 2
    push    ax
    lea     ax, [bp-8]
    add     ax, 4
    pop     bx
    mov     [bx], ax
; RPN'ized expression: "cp 2 + *u c 1 + = "
; Expanded expression: "(@-16) 4 + (@-8) 2 + =(2) "
; Fused expression:    "+ (@-16) 4 push-ax + (@-8) 2 =(34) **sp ax "
    lea     ax, [bp-16]
    add     ax, 4
    push    ax
    lea     ax, [bp-8]
    add     ax, 2
    pop     bx
    mov     [bx], ax
; RPN'ized expression: "cp 3 + *u c = "
; Expanded expression: "(@-16) 6 + (@-8) =(2) "
; Fused expression:    "+ (@-16) 6 =(34) *ax (@-8) "
    lea     ax, [bp-16]
    add     ax, 6
    mov     bx, ax
    lea     ax, [bp-8]
    mov     [bx], ax
; RPN'ized expression: "( cpp ++ *u *u , L129 printf ) "
; Expanded expression: " (@-18) 2 +=(2) *(2) *(2)  L129  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L129:
    db  "%s",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( +=(34) *(@-18) 2 *(2) ax *(2) ax , L129 , printf )4 "
    mov     ax, [bp-18]
    add     ax, 2
    mov     [bp-18], ax
    mov     bx, ax
    mov     ax, [bx]
    mov     bx, ax
    push    word [bx]
    push    L129
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( cpp ++ *u -- *u 3 + , L131 printf ) "
; Expanded expression: " (@-18) 2 +=(2) 2 -=(2) *(2) 3 +  L131  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L131:
    db  "%s ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( +=(34) *(@-18) 2 -=(34) *ax 2 + *ax 3 , L131 , printf )4 "
    mov     ax, [bp-18]
    add     ax, 2
    mov     [bp-18], ax
    mov     bx, ax
    mov     ax, [bx]
    sub     ax, 2
    mov     [bx], ax
    mov     bx, ax
    mov     ax, [bx]
    add     ax, 3
    push    ax
    push    L131
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( cpp 2 -u + *u *u 3 + , L133 printf ) "
; Expanded expression: " (@-18) *(2) -4 + *(2) *(2) 3 +  L133  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L133:
    db  "%s",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( + *(@-18) -4 *(2) ax + *ax 3 , L133 , printf )4 "
    mov     ax, [bp-18]
    add     ax, -4
    mov     bx, ax
    mov     ax, [bx]
    mov     bx, ax
    mov     ax, [bx]
    add     ax, 3
    push    ax
    push    L133
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( cpp 1 -u + *u 1 -u + *u 1 + , L135 printf ) "
; Expanded expression: " (@-18) *(2) -2 + *(2) -2 + *(2) 1 +  L135  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L135:
    db  "%s",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( + *(@-18) -2 + *ax -2 + *ax 1 , L135 , printf )4 "
    mov     ax, [bp-18]
    add     ax, -2
    mov     bx, ax
    mov     ax, [bx]
    add     ax, -2
    mov     bx, ax
    mov     ax, [bx]
    add     ax, 1
    push    ax
    push    L135
    call    _printf
    sub     sp, -4
L120:
    leave
    ret
; SEGMENT _TEXT
; glb Print8 : (
; prm     Str : * char
;     ) * (
; prm     <something> : * char
;     ) * (
; prm     <something> : * char
;     ) * (
; prm     <something> : * char
;     ) * (
; prm     <something> : * char
;     ) * (
; prm     <something> : * char
;     ) * (
; prm     <something> : * char
;     ) * (
; prm     <something> : * char
;     ) void
SEGMENT _TEXT
    global  _Print8
_Print8:
    push    bp
    mov     bp, sp
; loc     Str : (@4): * char
; RPN'ized expression: "( Str , L138 printf ) "
; Expanded expression: " (@4) *(2)  L138  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L138:
    db  "%s",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@4) , L138 , printf )4 "
    push    word [bp+4]
    push    L138
    call    _printf
    sub     sp, -4
; return
; RPN'ized expression: "Print8 &u "
; Expanded expression: "Print8 "
; Fused expression:    "Print8 "
    mov     ax, _Print8
    jmp     L137
L137:
    leave
    ret
; SEGMENT _TEXT
; glb macros : (void) void
SEGMENT _TEXT
    global  _macros
_macros:
    push    bp
    mov     bp, sp
; RPN'ized expression: "( L143 , 42 , L141 printf ) "
; Expanded expression: " L143  42  L141  printf ()6 "
; SEGMENT _TEXT
SEGMENT _DATA
L143:
    db  "42",0
; SEGMENT _DATA
SEGMENT _TEXT
; SEGMENT _TEXT
SEGMENT _DATA
L141:
    db  "SOMETHING=%d, SOMETHING_2=",34,"%s",34,10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L143 , 42 , L141 , printf )6 "
    push    L143
    push    42
    push    L141
    call    _printf
    sub     sp, -6
L140:
    leave
    ret
; SEGMENT _TEXT
; glb Hola : * char
SEGMENT _DATA
    global  _Hola
_Hola:
; =
; RPN'ized expression: "L145 "
; Expanded expression: "L145 "
    dw  L145
; SEGMENT _DATA
SEGMENT _DATA
L145:
    db  "iHola!",0
; SEGMENT _DATA
; glb main : (void) int
SEGMENT _TEXT
    global  _main
_main:
    push    bp
    mov     bp, sp
; RPN'ized expression: "16 "
; Expanded expression: "16 "
; Expression value: 16
; loc     hws : (@-16): [16] char
    sub     sp, 16
; loc     phw : (@-18): * char
    sub     sp, 2
; =
; RPN'ized expression: "hws "
; Expanded expression: "(@-16) "
; Fused expression:    "=(34) *(@-18) (@-16) "
    lea     ax, [bp-16]
    mov     [bp-18], ax
; RPN'ized expression: "phw ++p *u 72 = "
; Expanded expression: "(@-18) ++p(2) 72 =(1) "
; Fused expression:    "++p(2) *(@-18) =(18) *ax 72 "
    mov     ax, [bp-18]
    inc     word [bp-18]
    mov     bx, ax
    mov     ax, 72
    mov     [bx], al
    cbw
; RPN'ized expression: "phw ++p *u 101 = "
; Expanded expression: "(@-18) ++p(2) 101 =(1) "
; Fused expression:    "++p(2) *(@-18) =(18) *ax 101 "
    mov     ax, [bp-18]
    inc     word [bp-18]
    mov     bx, ax
    mov     ax, 101
    mov     [bx], al
    cbw
; RPN'ized expression: "phw ++p *u 108 = "
; Expanded expression: "(@-18) ++p(2) 108 =(1) "
; Fused expression:    "++p(2) *(@-18) =(18) *ax 108 "
    mov     ax, [bp-18]
    inc     word [bp-18]
    mov     bx, ax
    mov     ax, 108
    mov     [bx], al
    cbw
; RPN'ized expression: "phw ++p *u 108 = "
; Expanded expression: "(@-18) ++p(2) 108 =(1) "
; Fused expression:    "++p(2) *(@-18) =(18) *ax 108 "
    mov     ax, [bp-18]
    inc     word [bp-18]
    mov     bx, ax
    mov     ax, 108
    mov     [bx], al
    cbw
; RPN'ized expression: "phw ++p *u 111 = "
; Expanded expression: "(@-18) ++p(2) 111 =(1) "
; Fused expression:    "++p(2) *(@-18) =(18) *ax 111 "
    mov     ax, [bp-18]
    inc     word [bp-18]
    mov     bx, ax
    mov     ax, 111
    mov     [bx], al
    cbw
; RPN'ized expression: "phw ++p *u 32 = "
; Expanded expression: "(@-18) ++p(2) 32 =(1) "
; Fused expression:    "++p(2) *(@-18) =(18) *ax 32 "
    mov     ax, [bp-18]
    inc     word [bp-18]
    mov     bx, ax
    mov     ax, 32
    mov     [bx], al
    cbw
; RPN'ized expression: "phw ++p *u 87 = "
; Expanded expression: "(@-18) ++p(2) 87 =(1) "
; Fused expression:    "++p(2) *(@-18) =(18) *ax 87 "
    mov     ax, [bp-18]
    inc     word [bp-18]
    mov     bx, ax
    mov     ax, 87
    mov     [bx], al
    cbw
; RPN'ized expression: "phw ++p *u 111 = "
; Expanded expression: "(@-18) ++p(2) 111 =(1) "
; Fused expression:    "++p(2) *(@-18) =(18) *ax 111 "
    mov     ax, [bp-18]
    inc     word [bp-18]
    mov     bx, ax
    mov     ax, 111
    mov     [bx], al
    cbw
; RPN'ized expression: "phw ++p *u 114 = "
; Expanded expression: "(@-18) ++p(2) 114 =(1) "
; Fused expression:    "++p(2) *(@-18) =(18) *ax 114 "
    mov     ax, [bp-18]
    inc     word [bp-18]
    mov     bx, ax
    mov     ax, 114
    mov     [bx], al
    cbw
; RPN'ized expression: "phw ++p *u 108 = "
; Expanded expression: "(@-18) ++p(2) 108 =(1) "
; Fused expression:    "++p(2) *(@-18) =(18) *ax 108 "
    mov     ax, [bp-18]
    inc     word [bp-18]
    mov     bx, ax
    mov     ax, 108
    mov     [bx], al
    cbw
; RPN'ized expression: "phw ++p *u 100 = "
; Expanded expression: "(@-18) ++p(2) 100 =(1) "
; Fused expression:    "++p(2) *(@-18) =(18) *ax 100 "
    mov     ax, [bp-18]
    inc     word [bp-18]
    mov     bx, ax
    mov     ax, 100
    mov     [bx], al
    cbw
; RPN'ized expression: "phw ++p *u 33 = "
; Expanded expression: "(@-18) ++p(2) 33 =(1) "
; Fused expression:    "++p(2) *(@-18) =(18) *ax 33 "
    mov     ax, [bp-18]
    inc     word [bp-18]
    mov     bx, ax
    mov     ax, 33
    mov     [bx], al
    cbw
; RPN'ized expression: "phw ++p *u 0 = "
; Expanded expression: "(@-18) ++p(2) 0 =(1) "
; Fused expression:    "++p(2) *(@-18) =(18) *ax 0 "
    mov     ax, [bp-18]
    inc     word [bp-18]
    mov     bx, ax
    mov     ax, 0
    mov     [bx], al
    cbw
; RPN'ized expression: "( ( hws strlen ) , hws , L148 printf ) "
; Expanded expression: "  (@-16)  strlen ()2  (@-16)  L148  printf ()6 "
; SEGMENT _TEXT
SEGMENT _DATA
L148:
    db  "hws=",34,"%s",34,", strlen(hws)=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( (@-16) , strlen )2 , (@-16) , L148 , printf )6 "
    lea     ax, [bp-16]
    push    ax
    call    _strlen
    sub     sp, -2
    push    ax
    lea     ax, [bp-16]
    push    ax
    push    L148
    call    _printf
    sub     sp, -6
; RPN'ized expression: "( L150 puts ) "
; Expanded expression: " L150  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L150:
    db  "Buongiorno!",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L150 , puts )2 "
    push    L150
    call    _puts
    sub     sp, -2
; RPN'ized expression: "( Hola puts ) "
; Expanded expression: " Hola *(2)  puts ()2 "
; Fused expression:    "( *(2) Hola , puts )2 "
    push    word [_Hola]
    call    _puts
    sub     sp, -2
; RPN'ized expression: "( 65535 , 32767 -u 1 - , L156 , 122 , 43690 , 32767 , L154 , 97 , L152 printf ) "
; Expanded expression: " 65535  -32768  L156  122  43690  32767  L154  97  L152  printf ()18 "
; SEGMENT _TEXT
SEGMENT _DATA
L156:
    db  "xyz",0
; SEGMENT _DATA
SEGMENT _TEXT
; SEGMENT _TEXT
SEGMENT _DATA
L154:
    db  "abc",0
; SEGMENT _DATA
SEGMENT _TEXT
; SEGMENT _TEXT
SEGMENT _DATA
L152:
    db  "%% char='%c' str=",34,"%s",34," dec=%d hex=%x %% char='%c' str=",34,"%s",34," dec=%d hex=%X",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 65535 , -32768 , L156 , 122 , 43690 , 32767 , L154 , 97 , L152 , printf )18 "
    push    65535
    push    -32768
    push    L156
    push    122
    push    43690
    push    32767
    push    L154
    push    97
    push    L152
    call    _printf
    sub     sp, -18
; RPN'ized expression: "( 4095 , 4095 , 4095 , L158 printf ) "
; Expanded expression: " 4095  4095  4095  L158  printf ()8 "
; SEGMENT _TEXT
SEGMENT _DATA
L158:
    db  "07777=%d, 0xFff=%d, 4095=0%o",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 4095 , 4095 , 4095 , L158 , printf )8 "
    push    4095
    push    4095
    push    4095
    push    L158
    call    _printf
    sub     sp, -8
; RPN'ized expression: "( -1 , -1 , 127 , 0 , 127 , 0 , L160 printf ) "
; Expanded expression: " -1  -1  127  0  127  0  L160  printf ()14 "
; SEGMENT _TEXT
SEGMENT _DATA
L160:
    db  "'\x0'=%X, '\x7F'=%X, '\0'=%o, '\177'=%o, '\xFf'=%X, '\377'=%o",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( -1 , -1 , 127 , 0 , 127 , 0 , L160 , printf )14 "
    push    -1
    push    -1
    push    127
    push    0
    push    127
    push    0
    push    L160
    call    _printf
    sub     sp, -14
; RPN'ized expression: "( L166 sizeof , L164 2 + *u , L162 printf ) "
; Expanded expression: " 3  L164 2 + *(1)  L162  printf ()6 "
; SEGMENT _TEXT
SEGMENT _DATA
L164:
    db  "xyz",0
; SEGMENT _DATA
SEGMENT _TEXT
; SEGMENT _TEXT
SEGMENT _DATA
L162:
    db  34,"xyz",34,"[2]='%c', sizeof ",34,"az",34,"=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 3 , + L164 2 *(1) ax , L162 , printf )6 "
    push    3
    mov     ax, L164
    add     ax, 2
    mov     bx, ax
    mov     al, [bx]
    cbw
    push    ax
    push    L162
    call    _printf
    sub     sp, -6
; RPN'ized expression: "( ( 10 fib ) , ( 7 fact ) , L168 printf ) "
; Expanded expression: "  10  fib ()2   7  fact ()2  L168  printf ()6 "
; SEGMENT _TEXT
SEGMENT _DATA
L168:
    db  "fact(7)=%d, fib(10)=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( 10 , fib )2 , ( 7 , fact )2 , L168 , printf )6 "
    push    10
    call    _fib
    sub     sp, -2
    push    ax
    push    7
    call    _fact
    sub     sp, -2
    push    ax
    push    L168
    call    _printf
    sub     sp, -6
; RPN'ized expression: "( L172 , L170 printf ) "
; Expanded expression: " L172  L170  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L172:
    db  "pea",0,"nut",0
; SEGMENT _DATA
SEGMENT _TEXT
; SEGMENT _TEXT
SEGMENT _DATA
L170:
    db  "printf(",34,"pea\0nut",34,"): ",34,"%s",34,10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L172 , L170 , printf )4 "
    push    L172
    push    L170
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( L176 3 + , L174 printf ) "
; Expanded expression: " L176 3 +  L174  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L176:
    db  "peanut",0
; SEGMENT _DATA
SEGMENT _TEXT
; SEGMENT _TEXT
SEGMENT _DATA
L174:
    db  "printf(",34,"peanut",34," + 3): ",34,"%s",34,10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( + L176 3 , L174 , printf )4 "
    mov     ax, L176
    add     ax, 3
    push    ax
    push    L174
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( L178 puts ) "
; Expanded expression: " L178  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L178:
    db  "press a key...",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L178 , puts )2 "
    push    L178
    call    _puts
    sub     sp, -2
; RPN'ized expression: "( getchar ) "
; Expanded expression: " getchar ()0 "
; Fused expression:    "( getchar )0 "
    call    _getchar
; RPN'ized expression: "( breakCont ) "
; Expanded expression: " breakCont ()0 "
; Fused expression:    "( breakCont )0 "
    call    _breakCont
; loc     xx : (@-20): int
    sub     sp, 2
; RPN'ized expression: "xx sizeof "
; Expanded expression: "2 "
; Expression value: 2
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
; loc     yy : (@-28): [2] [2] int
    sub     sp, 8
; RPN'ized expression: "L180 sizeof "
; Expanded expression: "3 "
; Expression value: 3
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
; loc     zz : (@-40): [3] [2] int
    sub     sp, 12
; loc     Switch : (void) void
; RPN'ized expression: "( Switch ) "
; Expanded expression: " Switch ()0 "
; Fused expression:    "( Switch )0 "
    call    _Switch
; loc     pgb : (@-42): * char
    sub     sp, 2
; =
; RPN'ized expression: "L182 "
; Expanded expression: "L182 "
; SEGMENT _TEXT
SEGMENT _DATA
L182:
    db  "Green on Black!",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "=(34) *(@-42) L182 "
    mov     ax, L182
    mov     [bp-42], ax
; RPN'ized expression: "( pgb puts ) "
; Expanded expression: " (@-42) *(2)  puts ()2 "
; Fused expression:    "( *(2) (@-42) , puts )2 "
    push    word [bp-42]
    call    _puts
    sub     sp, -2
; loc     x : (@-44): int
    sub     sp, 2
; loc     y : (@-46): int
    sub     sp, 2
; for
; RPN'ized expression: "y 0 = "
; Expanded expression: "(@-46) 0 =(2) "
; Fused expression:    "=(34) *(@-46) 0 "
    mov     ax, 0
    mov     [bp-46], ax
L184:
; RPN'ized expression: "y 25 < "
; Expanded expression: "(@-46) *(2) 25 < "
; Fused expression:    "< *(@-46) 25 IF! "
    mov     ax, [bp-46]
    cmp     ax, 25
    jge     L187
    jmp     L186
L185:
; RPN'ized expression: "y ++p "
; Expanded expression: "(@-46) ++p(2) "
; Fused expression:    "++p(2) *(@-46) "
    mov     ax, [bp-46]
    inc     word [bp-46]
    jmp     L184
L186:
; for
; RPN'ized expression: "x 0 = "
; Expanded expression: "(@-44) 0 =(2) "
; Fused expression:    "=(34) *(@-44) 0 "
    mov     ax, 0
    mov     [bp-44], ax
L188:
; RPN'ized expression: "x 80 < "
; Expanded expression: "(@-44) *(2) 80 < "
; Fused expression:    "< *(@-44) 80 IF! "
    mov     ax, [bp-44]
    cmp     ax, 80
    jge     L191
    jmp     L190
L189:
; RPN'ized expression: "x ++p "
; Expanded expression: "(@-44) ++p(2) "
; Fused expression:    "++p(2) *(@-44) "
    mov     ax, [bp-44]
    inc     word [bp-44]
    jmp     L188
L190:
; RPN'ized expression: "( 2 , y 80 * x + 2 * 1 + , 47104 pokeb ) "
; Expanded expression: " 2  (@-46) *(2) 80 * (@-44) *(2) + 2 * 1 +  47104  pokeb ()6 "
; Fused expression:    "( 2 , * *(@-46) 80 + ax *(@-44) * ax 2 + ax 1 , 47104 , pokeb )6 "
    push    2
    mov     ax, [bp-46]
    imul    ax, ax, 80
    add     ax, [bp-44]
    imul    ax, ax, 2
    add     ax, 1
    push    ax
    push    47104
    call    _pokeb
    sub     sp, -6
    jmp     L189
L191:
    jmp     L185
L187:
; RPN'ized expression: "( L192 puts ) "
; Expanded expression: " L192  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L192:
    db  "press a key once for graphics mode and then another time for text mode...",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L192 , puts )2 "
    push    L192
    call    _puts
    sub     sp, -2
; RPN'ized expression: "( getchar ) "
; Expanded expression: " getchar ()0 "
; Fused expression:    "( getchar )0 "
    call    _getchar
; loc     gfxmode : (
; prm         mode : int
;         ) void
; RPN'ized expression: "( 19 gfxmode ) "
; Expanded expression: " 19  gfxmode ()2 "
; Fused expression:    "( 19 , gfxmode )2 "
    push    19
    call    _gfxmode
    sub     sp, -2
; for
; RPN'ized expression: "y 0 = "
; Expanded expression: "(@-46) 0 =(2) "
; Fused expression:    "=(34) *(@-46) 0 "
    mov     ax, 0
    mov     [bp-46], ax
L194:
; RPN'ized expression: "y 200 < "
; Expanded expression: "(@-46) *(2) 200 < "
; Fused expression:    "< *(@-46) 200 IF! "
    mov     ax, [bp-46]
    cmp     ax, 200
    jge     L197
    jmp     L196
L195:
; RPN'ized expression: "y ++p "
; Expanded expression: "(@-46) ++p(2) "
; Fused expression:    "++p(2) *(@-46) "
    mov     ax, [bp-46]
    inc     word [bp-46]
    jmp     L194
L196:
; for
; RPN'ized expression: "x 0 = "
; Expanded expression: "(@-44) 0 =(2) "
; Fused expression:    "=(34) *(@-44) 0 "
    mov     ax, 0
    mov     [bp-44], ax
L198:
; RPN'ized expression: "x 320 < "
; Expanded expression: "(@-44) *(2) 320 < "
; Fused expression:    "< *(@-44) 320 IF! "
    mov     ax, [bp-44]
    cmp     ax, 320
    jge     L201
    jmp     L200
L199:
; RPN'ized expression: "x ++p "
; Expanded expression: "(@-44) ++p(2) "
; Fused expression:    "++p(2) *(@-44) "
    mov     ax, [bp-44]
    inc     word [bp-44]
    jmp     L198
L200:
; RPN'ized expression: "( x y + 15 & , y 320 * x + , 40960 pokeb ) "
; Expanded expression: " (@-44) *(2) (@-46) *(2) + 15 &  (@-46) *(2) 320 * (@-44) *(2) +  40960  pokeb ()6 "
; Fused expression:    "( + *(@-44) *(@-46) & ax 15 , * *(@-46) 320 + ax *(@-44) , 40960 , pokeb )6 "
    mov     ax, [bp-44]
    add     ax, [bp-46]
    and     ax, 15
    push    ax
    mov     ax, [bp-46]
    imul    ax, ax, 320
    add     ax, [bp-44]
    push    ax
    push    40960
    call    _pokeb
    sub     sp, -6
    jmp     L199
L201:
    jmp     L195
L197:
; RPN'ized expression: "( getchar ) "
; Expanded expression: " getchar ()0 "
; Fused expression:    "( getchar )0 "
    call    _getchar
; RPN'ized expression: "( 3 gfxmode ) "
; Expanded expression: " 3  gfxmode ()2 "
; Fused expression:    "( 3 , gfxmode )2 "
    push    3
    call    _gfxmode
    sub     sp, -2
; loc     <something> : char
; RPN'ized expression: "( <something> sizeof , L202 printf ) "
; Expanded expression: " 1  L202  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L202:
    db  "sizeof(char)=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 1 , L202 , printf )4 "
    push    1
    push    L202
    call    _printf
    sub     sp, -4
; loc     <something> : int
; RPN'ized expression: "( <something> sizeof , L204 printf ) "
; Expanded expression: " 2  L204  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L204:
    db  "sizeof(int)=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 2 , L204 , printf )4 "
    push    2
    push    L204
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( , L206 printf 3 "
; Expanded expression: "  L206 printf 3 "
; Expression value: 3
; loc     <something> : [3] char
; RPN'ized expression: "( <something> sizeof , L206 printf ) "
; Expanded expression: " 3  L206  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L206:
    db  "sizeof(char[3])=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 3 , L206 , printf )4 "
    push    3
    push    L206
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( , L208 printf 5 "
; Expanded expression: "  L208 printf 5 "
; Expression value: 5
; loc     <something> : [5] * () char
; RPN'ized expression: "( <something> sizeof , L208 printf ) "
; Expanded expression: " 10  L208  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L208:
    db  "sizeof char(*[5])()=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 10 , L208 , printf )4 "
    push    10
    push    L208
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( , L210 printf 3 "
; Expanded expression: "  L210 printf 3 "
; Expression value: 3
; loc     <something> : [3] int
; RPN'ized expression: "( , L210 printf <something> sizeof "
; Expanded expression: "  L210 printf 6 "
; Expression value: 6
; loc     <something> : [6] int
; RPN'ized expression: "( , L210 printf <something> sizeof "
; Expanded expression: "  L210 printf 12 "
; Expression value: 12
; loc     <something> : [12] int
; RPN'ized expression: "( <something> sizeof , L210 printf ) "
; Expanded expression: " 24  L210  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L210:
    db  "sizeof(int[sizeof(int[sizeof(int[3])])])=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 24 , L210 , printf )4 "
    push    24
    push    L210
    call    _printf
    sub     sp, -4
; RPN'ized expression: "3 "
; Expanded expression: "3 "
; Expression value: 3
; loc     <something> : [3] int
; RPN'ized expression: "<something> sizeof "
; Expanded expression: "6 "
; Expression value: 6
; loc     <something> : [6] int
; RPN'ized expression: "<something> sizeof "
; Expanded expression: "12 "
; Expression value: 12
; loc     <something> : [12] int
; RPN'ized expression: "<something> sizeof "
; Expanded expression: "24 "
; Expression value: 24
; loc     yui : (@-70): [24] char
    sub     sp, 24
; loc     <something> : * () char
; RPN'ized expression: "( <something> sizeof , L212 printf ) "
; Expanded expression: " 2  L212  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L212:
    db  "sizeof(char(*)())=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 2 , L212 , printf )4 "
    push    2
    push    L212
    call    _printf
    sub     sp, -4
; loc     <something> : char
; RPN'ized expression: "( <something> sizeof , L214 printf ) "
; Expanded expression: " 1  L214  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L214:
    db  "sizeof(char())=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 1 , L214 , printf )4 "
    push    1
    push    L214
    call    _printf
    sub     sp, -4
; loc     <something> : * char
; RPN'ized expression: "( <something> sizeof , L216 printf ) "
; Expanded expression: " 2  L216  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L216:
    db  "sizeof(char*())=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 2 , L216 , printf )4 "
    push    2
    push    L216
    call    _printf
    sub     sp, -4
; loc     <something> : int
; RPN'ized expression: "( <something> sizeof , L218 printf ) "
; Expanded expression: " 2  L218  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L218:
    db  "sizeof(int())=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 2 , L218 , printf )4 "
    push    2
    push    L218
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( main sizeof , L220 printf ) "
; Expanded expression: " 2  L220  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L220:
    db  "sizeof main=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 2 , L220 , printf )4 "
    push    2
    push    L220
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( ( main ) sizeof , L222 printf ) "
; Expanded expression: " 2  L222  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L222:
    db  "sizeof main()=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 2 , L222 , printf )4 "
    push    2
    push    L222
    call    _printf
    sub     sp, -4
; loc     <something> : () void
; RPN'ized expression: "( <something> sizeof , L224 printf ) "
; Expanded expression: " 2  L224  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L224:
    db  "sizeof(void()())=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 2 , L224 , printf )4 "
    push    2
    push    L224
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( , L226 printf 7 "
; Expanded expression: "  L226 printf 7 "
; Expression value: 7
; loc     <something> : [7] char
; RPN'ized expression: "( <something> sizeof , L226 printf ) "
; Expanded expression: " 7  L226  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L226:
    db  "sizeof((char[7]))=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 7 , L226 , printf )4 "
    push    7
    push    L226
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( PointerStew ) "
; Expanded expression: " PointerStew ()0 "
; Fused expression:    "( PointerStew )0 "
    call    _PointerStew
; RPN'ized expression: "( L236 ( L234 ( L232 ( L230 ( L228 Print8 ) ) ) ) ) "
; Expanded expression: " L236   L234   L232   L230   L228  Print8 ()2 ()2 ()2 ()2 ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L236:
    db  10,0
; SEGMENT _DATA
SEGMENT _TEXT
; SEGMENT _TEXT
SEGMENT _DATA
L234:
    db  "!",0
; SEGMENT _DATA
SEGMENT _TEXT
; SEGMENT _TEXT
SEGMENT _DATA
L232:
    db  "world",0
; SEGMENT _DATA
SEGMENT _TEXT
; SEGMENT _TEXT
SEGMENT _DATA
L230:
    db  " ",0
; SEGMENT _DATA
SEGMENT _TEXT
; SEGMENT _TEXT
SEGMENT _DATA
L228:
    db  "hello",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L236 , ( L234 , ( L232 , ( L230 , ( L228 , Print8 )2 )2 )2 )2 )2 "
    push    L236
    push    L234
    push    L232
    push    L230
    push    L228
    call    _Print8
    sub     sp, -2
    call    ax
    sub     sp, -2
    call    ax
    sub     sp, -2
    call    ax
    sub     sp, -2
    call    ax
    sub     sp, -2
; RPN'ized expression: "( macros ) "
; Expanded expression: " macros ()0 "
; Fused expression:    "( macros )0 "
    call    _macros
; RPN'ized expression: "( L238 printf ) "
; Expanded expression: " L238  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L238:
    db  "These are six concatenated string literals!",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L238 , printf )2 "
    push    L238
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( L242 , L240 printf ) "
; Expanded expression: " L242  L240  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L242:
    db  "ABC012abc",0
; SEGMENT _DATA
SEGMENT _TEXT
; SEGMENT _TEXT
SEGMENT _DATA
L240:
    db  34,"\x41\x42\x43\60\61\62abc",34," = ",34,"%s",34,10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L242 , L240 , printf )4 "
    push    L242
    push    L240
    call    _printf
    sub     sp, -4
; RPN'ized expression: "3 "
; Expanded expression: "3 "
; Expression value: 3
; loc     arr : (@-76): [3] int
    sub     sp, 6
; loc     p : (@-78): * int
    sub     sp, 2
; =
; RPN'ized expression: "arr 1 + "
; Expanded expression: "(@-76) 2 + "
; Fused expression:    "+ (@-76) 2 =(34) *(@-78) ax "
    lea     ax, [bp-76]
    add     ax, 2
    mov     [bp-78], ax
; RPN'ized expression: "arr 0 + *u 11 = "
; Expanded expression: "(@-76) 0 + 11 =(2) "
; Fused expression:    "+ (@-76) 0 =(34) *ax 11 "
    lea     ax, [bp-76]
    add     ax, 0
    mov     bx, ax
    mov     ax, 11
    mov     [bx], ax
; RPN'ized expression: "arr 1 + *u 22 = "
; Expanded expression: "(@-76) 2 + 22 =(2) "
; Fused expression:    "+ (@-76) 2 =(34) *ax 22 "
    lea     ax, [bp-76]
    add     ax, 2
    mov     bx, ax
    mov     ax, 22
    mov     [bx], ax
; RPN'ized expression: "arr 2 + *u 33 = "
; Expanded expression: "(@-76) 4 + 33 =(2) "
; Fused expression:    "+ (@-76) 4 =(34) *ax 33 "
    lea     ax, [bp-76]
    add     ax, 4
    mov     bx, ax
    mov     ax, 33
    mov     [bx], ax
; RPN'ized expression: "( p 1 -= *u , L244 printf ) "
; Expanded expression: " (@-78) 2 -=(2) *(2)  L244  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L244:
    db  "arr[0]=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( -=(34) *(@-78) 2 *(2) ax , L244 , printf )4 "
    mov     ax, [bp-78]
    sub     ax, 2
    mov     [bp-78], ax
    mov     bx, ax
    push    word [bx]
    push    L244
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( p 1 += *u , L246 printf ) "
; Expanded expression: " (@-78) 2 +=(2) *(2)  L246  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L246:
    db  "arr[1]=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( +=(34) *(@-78) 2 *(2) ax , L246 , printf )4 "
    mov     ax, [bp-78]
    add     ax, 2
    mov     [bp-78], ax
    mov     bx, ax
    push    word [bx]
    push    L246
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( p 1 += *u , L248 printf ) "
; Expanded expression: " (@-78) 2 +=(2) *(2)  L248  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L248:
    db  "arr[2]=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( +=(34) *(@-78) 2 *(2) ax , L248 , printf )4 "
    mov     ax, [bp-78]
    add     ax, 2
    mov     [bp-78], ax
    mov     bx, ax
    push    word [bx]
    push    L248
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( L250 printf ) "
; Expanded expression: " L250  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L250:
    db  "arr[0] *= arr[1] *= arr[2];",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L250 , printf )2 "
    push    L250
    call    _printf
    sub     sp, -2
; RPN'ized expression: "arr 0 + *u arr 1 + *u arr 2 + *u *= *= "
; Expanded expression: "(@-76) 0 + (@-76) 2 + (@-76) 4 + *(2) *=(2) *=(2) "
; Fused expression:    "+ (@-76) 0 push-ax + (@-76) 2 push-ax + (@-76) 4 *=(34) **sp *ax *=(34) **sp ax "
    lea     ax, [bp-76]
    add     ax, 0
    push    ax
    lea     ax, [bp-76]
    add     ax, 2
    push    ax
    lea     ax, [bp-76]
    add     ax, 4
    mov     bx, ax
    mov     cx, [bx]
    pop     bx
    mov     ax, [bx]
    mul     cx
    mov     [bx], ax
    mov     cx, ax
    pop     bx
    mov     ax, [bx]
    mul     cx
    mov     [bx], ax
; RPN'ized expression: "( arr 2 + *u , arr 1 + *u , arr 0 + *u , L252 printf ) "
; Expanded expression: " (@-76) 4 + *(2)  (@-76) 2 + *(2)  (@-76) 0 + *(2)  L252  printf ()8 "
; SEGMENT _TEXT
SEGMENT _DATA
L252:
    db  "arr[0]=%d",10,"arr[1]=%d",10,"arr[2]=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( + (@-76) 4 *(2) ax , + (@-76) 2 *(2) ax , + (@-76) 0 *(2) ax , L252 , printf )8 "
    lea     ax, [bp-76]
    add     ax, 4
    mov     bx, ax
    push    word [bx]
    lea     ax, [bp-76]
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    lea     ax, [bp-76]
    add     ax, 0
    mov     bx, ax
    push    word [bx]
    push    L252
    call    _printf
    sub     sp, -8
; loc     c : (@-80): char
    sub     sp, 2
; =
; RPN'ized expression: "127 "
; Expanded expression: "127 "
; Expression value: 127
; Fused expression:    "=(34) *(@-80) 127 "
    mov     ax, 127
    mov     [bp-80], ax
; RPN'ized expression: "( c 127 *= sizeof , c 127 * sizeof , L254 printf ) "
; Expanded expression: " 1  2  L254  printf ()6 "
; SEGMENT _TEXT
SEGMENT _DATA
L254:
    db  "char c = 127; sizeof(c * 127)=%d; sizeof(c *= 127)=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 1 , 2 , L254 , printf )6 "
    push    1
    push    2
    push    L254
    call    _printf
    sub     sp, -6
; RPN'ized expression: "( c 127 * , L256 printf ) "
; Expanded expression: " (@-80) *(1) 127 *  L256  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L256:
    db  "printf(",34,"%%d\n",34,", c * 127): %d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( * *(@-80) 127 , L256 , printf )4 "
    mov     al, [bp-80]
    cbw
    imul    ax, ax, 127
    push    ax
    push    L256
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( c 127 *= , L258 printf ) "
; Expanded expression: " (@-80) 127 *=(1)  L258  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L258:
    db  "printf(",34,"%%d\n",34,", c *= 127): %d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *=(18) *(@-80) 127 , L258 , printf )4 "
    mov     al, [bp-80]
    cbw
    imul    ax, ax, 127
    mov     [bp-80], al
    cbw
    push    ax
    push    L258
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( 32767 putdecu ) "
; Expanded expression: " 32767  putdecu ()2 "
; Fused expression:    "( 32767 , putdecu )2 "
    push    32767
    call    _putdecu
    sub     sp, -2
; RPN'ized expression: "( 10 putchar ) "
; Expanded expression: " 10  putchar ()2 "
; Fused expression:    "( 10 , putchar )2 "
    push    10
    call    _putchar
    sub     sp, -2
; RPN'ized expression: "( 32767 -u 1 - putdecu ) "
; Expanded expression: " -32768  putdecu ()2 "
; Fused expression:    "( -32768 , putdecu )2 "
    push    -32768
    call    _putdecu
    sub     sp, -2
; RPN'ized expression: "( 10 putchar ) "
; Expanded expression: " 10  putchar ()2 "
; Fused expression:    "( 10 , putchar )2 "
    push    10
    call    _putchar
    sub     sp, -2
; RPN'ized expression: "( 32767 -u putdecu ) "
; Expanded expression: " -32767  putdecu ()2 "
; Fused expression:    "( -32767 , putdecu )2 "
    push    -32767
    call    _putdecu
    sub     sp, -2
; RPN'ized expression: "( 10 putchar ) "
; Expanded expression: " 10  putchar ()2 "
; Fused expression:    "( 10 , putchar )2 "
    push    10
    call    _putchar
    sub     sp, -2
; RPN'ized expression: "( 32767 -u 1 + putdecu ) "
; Expanded expression: " -32766  putdecu ()2 "
; Fused expression:    "( -32766 , putdecu )2 "
    push    -32766
    call    _putdecu
    sub     sp, -2
; RPN'ized expression: "( 10 putchar ) "
; Expanded expression: " 10  putchar ()2 "
; Fused expression:    "( 10 , putchar )2 "
    push    10
    call    _putchar
    sub     sp, -2
; RPN'ized expression: "( 3 -u putdecu ) "
; Expanded expression: " -3  putdecu ()2 "
; Fused expression:    "( -3 , putdecu )2 "
    push    -3
    call    _putdecu
    sub     sp, -2
; RPN'ized expression: "( 10 putchar ) "
; Expanded expression: " 10  putchar ()2 "
; Fused expression:    "( 10 , putchar )2 "
    push    10
    call    _putchar
    sub     sp, -2
; RPN'ized expression: "( 2 -u putdecu ) "
; Expanded expression: " -2  putdecu ()2 "
; Fused expression:    "( -2 , putdecu )2 "
    push    -2
    call    _putdecu
    sub     sp, -2
; RPN'ized expression: "( 10 putchar ) "
; Expanded expression: " 10  putchar ()2 "
; Fused expression:    "( 10 , putchar )2 "
    push    10
    call    _putchar
    sub     sp, -2
; RPN'ized expression: "( 1 -u putdecu ) "
; Expanded expression: " -1  putdecu ()2 "
; Fused expression:    "( -1 , putdecu )2 "
    push    -1
    call    _putdecu
    sub     sp, -2
; RPN'ized expression: "( 10 putchar ) "
; Expanded expression: " 10  putchar ()2 "
; Fused expression:    "( 10 , putchar )2 "
    push    10
    call    _putchar
    sub     sp, -2
; return
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "0 "
    mov     ax, 0
    jmp     L147
L147:
    leave
    ret
; SEGMENT _TEXT
; glb Switch : (void) void
SEGMENT _TEXT
    global  _Switch
_Switch:
    push    bp
    mov     bp, sp
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
    mov     ax, 1
    jmp     L263
; {
; default
L262:
; }
    jmp     L261
L263:
    jmp     L262
L261:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
    mov     ax, 1
    jmp     L267
; {
; case
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
    jmp     L268
L267:
    cmp     ax, 0
    jne     L269
L268:
; }
    jmp     L265
L269:
L265:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
    mov     ax, 1
    jmp     L273
; {
; case
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
    jmp     L274
L273:
    cmp     ax, 1
    jne     L275
L274:
; }
    jmp     L271
L275:
L271:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
    mov     ax, 1
    jmp     L279
; {
; {
; loc             i : (@-2): int
    sub     sp, 2
    sub     sp, -2
; }
; }
    jmp     L277
L279:
L277:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
    mov     ax, 1
    jmp     L283
; {
; RPN'ized expression: "( L285 puts ) "
; Expanded expression: " L285  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L285:
    db  "never printed",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L285 , puts )2 "
    push    L285
    call    _puts
    sub     sp, -2
; case
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
    jmp     L284
L283:
    cmp     ax, 0
    jne     L287
L284:
; RPN'ized expression: "( L289 puts ) "
; Expanded expression: " L289  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L289:
    db  "0",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L289 , puts )2 "
    push    L289
    call    _puts
    sub     sp, -2
; break
    jmp     L281
; case
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
    jmp     L288
L287:
    cmp     ax, 1
    jne     L291
L288:
; RPN'ized expression: "( L293 puts ) "
; Expanded expression: " L293  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L293:
    db  "1",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L293 , puts )2 "
    push    L293
    call    _puts
    sub     sp, -2
; break
    jmp     L281
; case
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
    jmp     L292
L291:
    cmp     ax, 2
    jne     L295
L292:
; RPN'ized expression: "( L297 puts ) "
; Expanded expression: " L297  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L297:
    db  "2",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L297 , puts )2 "
    push    L297
    call    _puts
    sub     sp, -2
; break
    jmp     L281
; default
L282:
; RPN'ized expression: "( L299 puts ) "
; Expanded expression: " L299  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L299:
    db  "default",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L299 , puts )2 "
    push    L299
    call    _puts
    sub     sp, -2
; break
    jmp     L281
; }
    jmp     L281
L295:
    jmp     L282
L281:
; switch
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
; Fused expression:    "2 "
    mov     ax, 2
    jmp     L303
; {
; case
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
    jmp     L304
L303:
    cmp     ax, 2
    jne     L305
L304:
; RPN'ized expression: "( L307 puts ) "
; Expanded expression: " L307  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L307:
    db  "2",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L307 , puts )2 "
    push    L307
    call    _puts
    sub     sp, -2
; break
    jmp     L301
; }
    jmp     L301
L305:
L301:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
    mov     ax, 1
    jmp     L311
; {
; default
L310:
; RPN'ized expression: "( L313 puts ) "
; Expanded expression: " L313  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L313:
    db  "default",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L313 , puts )2 "
    push    L313
    call    _puts
    sub     sp, -2
; break
    jmp     L309
; }
    jmp     L309
L311:
    jmp     L310
L309:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
    mov     ax, 1
    jmp     L317
; {
; default
L316:
; RPN'ized expression: "( L319 puts ) "
; Expanded expression: " L319  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L319:
    db  "default",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L319 , puts )2 "
    push    L319
    call    _puts
    sub     sp, -2
; break
    jmp     L315
; case
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
    jmp     L318
L317:
    cmp     ax, 0
    jne     L321
L318:
; RPN'ized expression: "( L323 puts ) "
; Expanded expression: " L323  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L323:
    db  "0",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L323 , puts )2 "
    push    L323
    call    _puts
    sub     sp, -2
; break
    jmp     L315
; }
    jmp     L315
L321:
    jmp     L316
L315:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
    mov     ax, 1
    jmp     L327
; {
; case
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
    jmp     L328
L327:
    cmp     ax, 0
    jne     L329
L328:
; RPN'ized expression: "( L331 puts ) "
; Expanded expression: " L331  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L331:
    db  "0",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L331 , puts )2 "
    push    L331
    call    _puts
    sub     sp, -2
; break
    jmp     L325
; default
L326:
; RPN'ized expression: "( L333 puts ) "
; Expanded expression: " L333  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L333:
    db  "default",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L333 , puts )2 "
    push    L333
    call    _puts
    sub     sp, -2
; break
    jmp     L325
; }
    jmp     L325
L329:
    jmp     L326
L325:
; switch
; RPN'ized expression: "3 "
; Expanded expression: "3 "
; Expression value: 3
; Fused expression:    "3 "
    mov     ax, 3
    jmp     L337
; {
; case
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
    jmp     L338
L337:
    cmp     ax, 2
    jne     L339
L338:
; RPN'ized expression: "( L341 puts ) "
; Expanded expression: " L341  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L341:
    db  "2 & fallthru",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L341 , puts )2 "
    push    L341
    call    _puts
    sub     sp, -2
; case
; RPN'ized expression: "3 "
; Expanded expression: "3 "
; Expression value: 3
    jmp     L340
L339:
    cmp     ax, 3
    jne     L343
L340:
; RPN'ized expression: "( L345 puts ) "
; Expanded expression: " L345  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L345:
    db  "3 & fallthru",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L345 , puts )2 "
    push    L345
    call    _puts
    sub     sp, -2
; case
; RPN'ized expression: "4 "
; Expanded expression: "4 "
; Expression value: 4
    jmp     L344
L343:
    cmp     ax, 4
    jne     L347
L344:
; RPN'ized expression: "( L349 puts ) "
; Expanded expression: " L349  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L349:
    db  "4 & fallthru",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L349 , puts )2 "
    push    L349
    call    _puts
    sub     sp, -2
; default
L336:
; RPN'ized expression: "( L351 puts ) "
; Expanded expression: " L351  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L351:
    db  "default & fallthru",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L351 , puts )2 "
    push    L351
    call    _puts
    sub     sp, -2
; }
    jmp     L335
L347:
    jmp     L336
L335:
; switch
; RPN'ized expression: "5 "
; Expanded expression: "5 "
; Expression value: 5
; Fused expression:    "5 "
    mov     ax, 5
    jmp     L355
; {
; default
L354:
; RPN'ized expression: "( L357 puts ) "
; Expanded expression: " L357  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L357:
    db  "default & fallthru",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L357 , puts )2 "
    push    L357
    call    _puts
    sub     sp, -2
; case
; RPN'ized expression: "4 "
; Expanded expression: "4 "
; Expression value: 4
    jmp     L356
L355:
    cmp     ax, 4
    jne     L359
L356:
; RPN'ized expression: "( L361 puts ) "
; Expanded expression: " L361  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L361:
    db  "4 & fallthru",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L361 , puts )2 "
    push    L361
    call    _puts
    sub     sp, -2
; case
; RPN'ized expression: "3 "
; Expanded expression: "3 "
; Expression value: 3
    jmp     L360
L359:
    cmp     ax, 3
    jne     L363
L360:
; RPN'ized expression: "( L365 puts ) "
; Expanded expression: " L365  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L365:
    db  "3 & fallthru",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L365 , puts )2 "
    push    L365
    call    _puts
    sub     sp, -2
; case
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
    jmp     L364
L363:
    cmp     ax, 2
    jne     L367
L364:
; RPN'ized expression: "( L369 puts ) "
; Expanded expression: " L369  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L369:
    db  "2 & fallthru",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L369 , puts )2 "
    push    L369
    call    _puts
    sub     sp, -2
; }
    jmp     L353
L367:
    jmp     L354
L353:
; loc     i : (@-2): int
    sub     sp, 2
; for
; RPN'ized expression: "i 1 = "
; Expanded expression: "(@-2) 1 =(2) "
; Fused expression:    "=(34) *(@-2) 1 "
    mov     ax, 1
    mov     [bp-2], ax
L371:
; RPN'ized expression: "i 5 <= "
; Expanded expression: "(@-2) *(2) 5 <= "
; Fused expression:    "<= *(@-2) 5 IF! "
    mov     ax, [bp-2]
    cmp     ax, 5
    jg      L374
    jmp     L373
L372:
; RPN'ized expression: "i ++p "
; Expanded expression: "(@-2) ++p(2) "
; Fused expression:    "++p(2) *(@-2) "
    mov     ax, [bp-2]
    inc     word [bp-2]
    jmp     L371
L373:
; switch
; RPN'ized expression: "i "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
    mov     ax, [bp-2]
    jmp     L377
; {
; case
; RPN'ized expression: "3 "
; Expanded expression: "3 "
; Expression value: 3
    jmp     L378
L377:
    cmp     ax, 3
    jne     L379
L378:
; continue
    jmp     L372
; default
L376:
; RPN'ized expression: "( i , L381 printf ) "
; Expanded expression: " (@-2) *(2)  L381  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L381:
    db  "%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-2) , L381 , printf )4 "
    push    word [bp-2]
    push    L381
    call    _printf
    sub     sp, -4
; break
    jmp     L375
; }
    jmp     L375
L379:
    jmp     L376
L375:
    jmp     L372
L374:
; return
    jmp     L260
L260:
    leave
    ret
; SEGMENT _TEXT

; Syntax/declaration table/stack:
; Bytes used: 1488/16384


; Macro table:
; Macro SOMETHING = `42`
; Macro NOTHING = ``
; Macro SOMETHING_2 = `"42"`
; Bytes used: 42/4096


; Identifier table:
; Ident putchar
; Ident c
; Ident getchar
; Ident <something>
; Ident pokeb
; Ident seg
; Ident ofs
; Ident val
; Ident strcpy
; Ident s1
; Ident s2
; Ident strlen
; Ident s
; Ident strchr
; Ident puts
; Ident isspace
; Ident isdigit
; Ident printf
; Ident fmt
; Ident putdec
; Ident n
; Ident putdecu
; Ident fact
; Ident x
; Ident fib
; Ident breakCont
; Ident PointerStew
; Ident Print8
; Ident Str
; Ident macros
; Ident Hola
; Ident main
; Ident Switch
; Bytes used: 227/4096

