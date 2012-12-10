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
    jmp     L2
L1:
; loc     s1 : (@4): * char
; loc     s2 : (@6): * char
; loc     tmp : (@-2): * char
; =
; RPN'ized expression: "s1 "
; Expanded expression: "(@4) *(2) "
; Fused expression:    "=(34) *(@-2) *(@4) "
    mov     ax, [bp+4]
    mov     [bp-2], ax
; while
; RPN'ized expression: "s1 ++p *u s2 ++p *u = "
; Expanded expression: "(@4) ++p(2) (@6) ++p(2) *(1) =(1) "
L4:
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
    je      L5
    jmp     L4
L5:
; return
; RPN'ized expression: "tmp "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
    mov     ax, [bp-2]
    jmp     L3
L3:
    leave
    ret
L2:
    sub     sp, 2
    jmp     L1
; SEGMENT _TEXT
; glb strlen : (
; prm     s : * char
;     ) int
SEGMENT _TEXT
    global  _strlen
_strlen:
    push    bp
    mov     bp, sp
    jmp     L7
L6:
; loc     s : (@4): * char
; loc     l : (@-2): int
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
L9:
; Fused expression:    "++p(2) *(@4) *(1) ax "
    mov     ax, [bp+4]
    inc     word [bp+4]
    mov     bx, ax
    mov     al, [bx]
    cbw
; JumpIfZero
    test    ax, ax
    je      L10
; RPN'ized expression: "l ++ "
; Expanded expression: "(@-2) ++(2) "
; Fused expression:    "++(2) *(@-2) "
    inc     word [bp-2]
    mov     ax, [bp-2]
    jmp     L9
L10:
; return
; RPN'ized expression: "l "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
    mov     ax, [bp-2]
    jmp     L8
L8:
    leave
    ret
L7:
    sub     sp, 2
    jmp     L6
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
    jmp     L12
L11:
; loc     s : (@4): * char
; loc     c : (@6): int
; do
L14:
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
    jne     L17
; return
; RPN'ized expression: "s "
; Expanded expression: "(@4) *(2) "
; Fused expression:    "*(2) (@4) "
    mov     ax, [bp+4]
    jmp     L13
L17:
; }
; while
; RPN'ized expression: "s ++p *u 0 != "
; Expanded expression: "(@4) ++p(2) *(1) 0 != "
L15:
; Fused expression:    "++p(2) *(@4) != *ax 0 IF "
    mov     ax, [bp+4]
    inc     word [bp+4]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 0
    jne     L14
L16:
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
L12:
    jmp     L11
; SEGMENT _TEXT
; glb puts : (
; prm     s : * char
;     ) int
SEGMENT _TEXT
    global  _puts
_puts:
    push    bp
    mov     bp, sp
    jmp     L20
L19:
; loc     s : (@4): * char
; while
; RPN'ized expression: "s *u "
; Expanded expression: "(@4) *(2) *(1) "
L22:
; Fused expression:    "*(2) (@4) *(1) ax "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     al, [bx]
    cbw
; JumpIfZero
    test    ax, ax
    je      L23
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
    jmp     L22
L23:
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
    jmp     L21
L21:
    leave
    ret
L20:
    jmp     L19
; SEGMENT _TEXT
; glb isspace : (
; prm     c : int
;     ) int
SEGMENT _TEXT
    global  _isspace
_isspace:
    push    bp
    mov     bp, sp
    jmp     L25
L24:
; loc     c : (@4): int
; return
; RPN'ized expression: "c 32 == c 12 == || c 10 == || c 13 == || c 9 == || c 11 == || "
; Expanded expression: "(@4) *(2) 32 == _Bool [sh||->31] (@4) *(2) 12 == _Bool ||[31] _Bool [sh||->30] (@4) *(2) 10 == _Bool ||[30] _Bool [sh||->29] (@4) *(2) 13 == _Bool ||[29] _Bool [sh||->28] (@4) *(2) 9 == _Bool ||[28] _Bool [sh||->27] (@4) *(2) 11 == _Bool ||[27] "
; Fused expression:    "== *(@4) 32 _Bool [sh||->31] == *(@4) 12 _Bool ||[31] _Bool [sh||->30] == *(@4) 10 _Bool ||[30] _Bool [sh||->29] == *(@4) 13 _Bool ||[29] _Bool [sh||->28] == *(@4) 9 _Bool ||[28] _Bool [sh||->27] == *(@4) 11 _Bool ||[27] "
    mov     ax, [bp+4]
    cmp     ax, 32
    sete    al
    cbw
    test    ax, ax
    setne   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jne     L31
    mov     ax, [bp+4]
    cmp     ax, 12
    sete    al
    cbw
    test    ax, ax
    setne   al
    cbw
L31:
    test    ax, ax
    setne   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jne     L30
    mov     ax, [bp+4]
    cmp     ax, 10
    sete    al
    cbw
    test    ax, ax
    setne   al
    cbw
L30:
    test    ax, ax
    setne   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jne     L29
    mov     ax, [bp+4]
    cmp     ax, 13
    sete    al
    cbw
    test    ax, ax
    setne   al
    cbw
L29:
    test    ax, ax
    setne   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jne     L28
    mov     ax, [bp+4]
    cmp     ax, 9
    sete    al
    cbw
    test    ax, ax
    setne   al
    cbw
L28:
    test    ax, ax
    setne   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jne     L27
    mov     ax, [bp+4]
    cmp     ax, 11
    sete    al
    cbw
    test    ax, ax
    setne   al
    cbw
L27:
    jmp     L26
L26:
    leave
    ret
L25:
    jmp     L24
; SEGMENT _TEXT
; glb isdigit : (
; prm     c : int
;     ) int
SEGMENT _TEXT
    global  _isdigit
_isdigit:
    push    bp
    mov     bp, sp
    jmp     L33
L32:
; loc     c : (@4): int
; return
; RPN'ized expression: "c 48 >= c 57 <= && "
; Expanded expression: "(@4) *(2) 48 >= _Bool [sh&&->35] (@4) *(2) 57 <= _Bool &&[35] "
; Fused expression:    ">= *(@4) 48 _Bool [sh&&->35] <= *(@4) 57 _Bool &&[35] "
    mov     ax, [bp+4]
    cmp     ax, 48
    setge   al
    cbw
    test    ax, ax
    setne   al
    cbw
; JumpIfZero
    test    ax, ax
    je      L35
    mov     ax, [bp+4]
    cmp     ax, 57
    setle   al
    cbw
    test    ax, ax
    setne   al
    cbw
L35:
    jmp     L34
L34:
    leave
    ret
L33:
    jmp     L32
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
    jmp     L37
L36:
; loc     fmt : (@4): * char
; loc     pp : (@-2): * int
; =
; RPN'ized expression: "fmt &u "
; Expanded expression: "(@4) "
; Fused expression:    "=(34) *(@-2) (@4) "
    lea     ax, [bp+4]
    mov     [bp-2], ax
; loc     cnt : (@-4): int
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "=(34) *(@-4) 0 "
    mov     ax, 0
    mov     [bp-4], ax
; loc     p : (@-6): * char
; loc     phex : (@-8): * char
; =
; RPN'ized expression: "L39 "
; Expanded expression: "L39 "
; SEGMENT _TEXT
SEGMENT _DATA
L39:
    db  "0123456789abcdef",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "=(34) *(@-8) L39 "
    mov     ax, L39
    mov     [bp-8], ax
; RPN'ized expression: "1 10 + 1 + "
; Expanded expression: "12 "
; Expression value: 12
; loc     s : (@-20): [12] char
; loc     pc : (@-22): * char
; loc     n : (@-24): int
; loc     sign : (@-26): int
; loc     minlen : (@-28): int
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "=(34) *(@-28) 0 "
    mov     ax, 0
    mov     [bp-28], ax
; loc     len : (@-30): int
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
L41:
; RPN'ized expression: "p *u 0 != "
; Expanded expression: "(@-6) *(2) *(1) 0 != "
; Fused expression:    "*(2) (@-6) != *ax 0 IF! "
    mov     ax, [bp-6]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 0
    je      L44
    jmp     L43
L42:
; RPN'ized expression: "p ++p "
; Expanded expression: "(@-6) ++p(2) "
; Fused expression:    "++p(2) *(@-6) "
    mov     ax, [bp-6]
    inc     word [bp-6]
    jmp     L41
L43:
; {
; if
; RPN'ized expression: "p *u 37 != p 1 + *u 37 == || "
; Expanded expression: "(@-6) *(2) *(1) 37 != _Bool [sh||->47] (@-6) *(2) 1 + *(1) 37 == _Bool ||[47] "
; Fused expression:    "*(2) (@-6) != *ax 37 _Bool [sh||->47] + *(@-6) 1 == *ax 37 _Bool ||[47] "
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
    jne     L47
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
L47:
; JumpIfZero
    test    ax, ax
    je      L45
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
    jmp     L42
; }
L45:
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
    je      L48
; {
; while
; RPN'ized expression: "( p *u isdigit ) "
; Expanded expression: " (@-6) *(2) *(1)  isdigit ()2 "
L50:
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
    je      L51
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
    jmp     L50
L51:
; }
L48:
; switch
; RPN'ized expression: "p *u "
; Expanded expression: "(@-6) *(2) *(1) "
; Fused expression:    "*(2) (@-6) *(1) ax "
    mov     ax, [bp-6]
    mov     bx, ax
    mov     al, [bx]
    cbw
    jmp     L54
; {
; case
; RPN'ized expression: "99 "
; Expanded expression: "99 "
; Expression value: 99
    jmp     L55
L54:
    cmp     ax, 99
    jne     L56
L55:
; while
; RPN'ized expression: "minlen 1 > "
; Expanded expression: "(@-28) *(2) 1 > "
L58:
; Fused expression:    "> *(@-28) 1 IF! "
    mov     ax, [bp-28]
    cmp     ax, 1
    jle     L59
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
    jmp     L58
L59:
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
    jmp     L52
; case
; RPN'ized expression: "115 "
; Expanded expression: "115 "
; Expression value: 115
    jmp     L57
L56:
    cmp     ax, 115
    jne     L60
L57:
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
    je      L62
; RPN'ized expression: "len ( pc strlen ) = "
; Expanded expression: "(@-30)  (@-22) *(2)  strlen ()2 =(2) "
; Fused expression:    "( *(2) (@-22) , strlen )2 =(34) *(@-30) ax "
    push    word [bp-22]
    call    _strlen
    sub     sp, -2
    mov     [bp-30], ax
L62:
; while
; RPN'ized expression: "minlen len > "
; Expanded expression: "(@-28) *(2) (@-30) *(2) > "
L64:
; Fused expression:    "> *(@-28) *(@-30) IF! "
    mov     ax, [bp-28]
    cmp     ax, [bp-30]
    jle     L65
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
    jmp     L64
L65:
; if
; RPN'ized expression: "len "
; Expanded expression: "(@-30) *(2) "
; Fused expression:    "*(2) (@-30) "
    mov     ax, [bp-30]
; JumpIfZero
    test    ax, ax
    je      L66
; while
; RPN'ized expression: "pc *u 0 != "
; Expanded expression: "(@-22) *(2) *(1) 0 != "
L68:
; Fused expression:    "*(2) (@-22) != *ax 0 IF! "
    mov     ax, [bp-22]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 0
    je      L69
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
    jmp     L68
L69:
L66:
; break
    jmp     L52
; case
; RPN'ized expression: "105 "
; Expanded expression: "105 "
; Expression value: 105
    jmp     L61
L60:
    cmp     ax, 105
    jne     L70
L61:
; case
; RPN'ized expression: "100 "
; Expanded expression: "100 "
; Expression value: 100
    jmp     L71
L70:
    cmp     ax, 100
    jne     L72
L71:
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
L74:
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
L75:
; Fused expression:    "*(2) (@-24) "
    mov     ax, [bp-24]
; JumpIfNotZero
    test    ax, ax
    jne     L74
L76:
; if
; RPN'ized expression: "sign 0 < "
; Expanded expression: "(@-26) *(2) 0 < "
; Fused expression:    "< *(@-26) 0 IF! "
    mov     ax, [bp-26]
    cmp     ax, 0
    jge     L77
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
L77:
; while
; RPN'ized expression: "minlen len > "
; Expanded expression: "(@-28) *(2) (@-30) *(2) > "
L79:
; Fused expression:    "> *(@-28) *(@-30) IF! "
    mov     ax, [bp-28]
    cmp     ax, [bp-30]
    jle     L80
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
    jmp     L79
L80:
; while
; RPN'ized expression: "pc *u 0 != "
; Expanded expression: "(@-22) *(2) *(1) 0 != "
L81:
; Fused expression:    "*(2) (@-22) != *ax 0 IF! "
    mov     ax, [bp-22]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 0
    je      L82
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
    jmp     L81
L82:
; break
    jmp     L52
; case
; RPN'ized expression: "88 "
; Expanded expression: "88 "
; Expression value: 88
    jmp     L73
L72:
    cmp     ax, 88
    jne     L83
L73:
; RPN'ized expression: "phex L85 = "
; Expanded expression: "(@-8) L85 =(2) "
; SEGMENT _TEXT
SEGMENT _DATA
L85:
    db  "0123456789ABCDEF",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "=(34) *(@-8) L85 "
    mov     ax, L85
    mov     [bp-8], ax
; case
; RPN'ized expression: "112 "
; Expanded expression: "112 "
; Expression value: 112
    jmp     L84
L83:
    cmp     ax, 112
    jne     L87
L84:
; case
; RPN'ized expression: "120 "
; Expanded expression: "120 "
; Expression value: 120
    jmp     L88
L87:
    cmp     ax, 120
    jne     L89
L88:
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
L91:
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
L92:
; Fused expression:    "*(2) (@-24) "
    mov     ax, [bp-24]
; JumpIfNotZero
    test    ax, ax
    jne     L91
L93:
; while
; RPN'ized expression: "minlen len > "
; Expanded expression: "(@-28) *(2) (@-30) *(2) > "
L94:
; Fused expression:    "> *(@-28) *(@-30) IF! "
    mov     ax, [bp-28]
    cmp     ax, [bp-30]
    jle     L95
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
    jmp     L94
L95:
; while
; RPN'ized expression: "pc *u 0 != "
; Expanded expression: "(@-22) *(2) *(1) 0 != "
L96:
; Fused expression:    "*(2) (@-22) != *ax 0 IF! "
    mov     ax, [bp-22]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 0
    je      L97
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
    jmp     L96
L97:
; break
    jmp     L52
; case
; RPN'ized expression: "111 "
; Expanded expression: "111 "
; Expression value: 111
    jmp     L90
L89:
    cmp     ax, 111
    jne     L98
L90:
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
L100:
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
L101:
; Fused expression:    "*(2) (@-24) "
    mov     ax, [bp-24]
; JumpIfNotZero
    test    ax, ax
    jne     L100
L102:
; while
; RPN'ized expression: "minlen len > "
; Expanded expression: "(@-28) *(2) (@-30) *(2) > "
L103:
; Fused expression:    "> *(@-28) *(@-30) IF! "
    mov     ax, [bp-28]
    cmp     ax, [bp-30]
    jle     L104
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
    jmp     L103
L104:
; while
; RPN'ized expression: "pc *u 0 != "
; Expanded expression: "(@-22) *(2) *(1) 0 != "
L105:
; Fused expression:    "*(2) (@-22) != *ax 0 IF! "
    mov     ax, [bp-22]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 0
    je      L106
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
    jmp     L105
L106:
; break
    jmp     L52
; default
L53:
; return
; RPN'ized expression: "1 -u "
; Expanded expression: "-1 "
; Expression value: -1
; Fused expression:    "-1 "
    mov     ax, -1
    jmp     L38
; }
    jmp     L52
L98:
    jmp     L53
L52:
; }
    jmp     L42
L44:
; return
; RPN'ized expression: "cnt "
; Expanded expression: "(@-4) *(2) "
; Fused expression:    "*(2) (@-4) "
    mov     ax, [bp-4]
    jmp     L38
L38:
    leave
    ret
L37:
    sub     sp, 30
    jmp     L36
; SEGMENT _TEXT
; glb putdec : (
; prm     n : int
;     ) void
SEGMENT _TEXT
    global  _putdec
_putdec:
    push    bp
    mov     bp, sp
    jmp     L108
L107:
; loc     n : (@4): int
; loc     r : (@-2): int
; if
; RPN'ized expression: "n 0 < "
; Expanded expression: "(@4) *(2) 0 < "
; Fused expression:    "< *(@4) 0 IF! "
    mov     ax, [bp+4]
    cmp     ax, 0
    jge     L110
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
    jmp     L111
L110:
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
L111:
; if
; RPN'ized expression: "n "
; Expanded expression: "(@4) *(2) "
; Fused expression:    "*(2) (@4) "
    mov     ax, [bp+4]
; JumpIfZero
    test    ax, ax
    je      L112
; RPN'ized expression: "( n putdec ) "
; Expanded expression: " (@4) *(2)  putdec ()2 "
; Fused expression:    "( *(2) (@4) , putdec )2 "
    push    word [bp+4]
    call    _putdec
    sub     sp, -2
L112:
; RPN'ized expression: "( 48 r + putchar ) "
; Expanded expression: " 48 (@-2) *(2) +  putchar ()2 "
; Fused expression:    "( + 48 *(@-2) , putchar )2 "
    mov     ax, 48
    add     ax, [bp-2]
    push    ax
    call    _putchar
    sub     sp, -2
L109:
    leave
    ret
L108:
    sub     sp, 2
    jmp     L107
; SEGMENT _TEXT
; glb putdecu : (
; prm     n : int
;     ) void
SEGMENT _TEXT
    global  _putdecu
_putdecu:
    push    bp
    mov     bp, sp
    jmp     L115
L114:
; loc     n : (@4): int
; loc     r : (@-2): int
; if
; RPN'ized expression: "n 0 < "
; Expanded expression: "(@4) *(2) 0 < "
; Fused expression:    "< *(@4) 0 IF! "
    mov     ax, [bp+4]
    cmp     ax, 0
    jge     L117
; {
; loc         n2 : (@-4): int
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
; }
    jmp     L118
L117:
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
L118:
; if
; RPN'ized expression: "n "
; Expanded expression: "(@4) *(2) "
; Fused expression:    "*(2) (@4) "
    mov     ax, [bp+4]
; JumpIfZero
    test    ax, ax
    je      L119
; RPN'ized expression: "( n putdecu ) "
; Expanded expression: " (@4) *(2)  putdecu ()2 "
; Fused expression:    "( *(2) (@4) , putdecu )2 "
    push    word [bp+4]
    call    _putdecu
    sub     sp, -2
L119:
; RPN'ized expression: "( 48 r + putchar ) "
; Expanded expression: " 48 (@-2) *(2) +  putchar ()2 "
; Fused expression:    "( + 48 *(@-2) , putchar )2 "
    mov     ax, 48
    add     ax, [bp-2]
    push    ax
    call    _putchar
    sub     sp, -2
L116:
    leave
    ret
L115:
    sub     sp, 4
    jmp     L114
; SEGMENT _TEXT
; glb fact : (
; prm     x : int
;     ) int
SEGMENT _TEXT
    global  _fact
_fact:
    push    bp
    mov     bp, sp
    jmp     L122
L121:
; loc     x : (@4): int
; if
; RPN'ized expression: "x 1 <= "
; Expanded expression: "(@4) *(2) 1 <= "
; Fused expression:    "<= *(@4) 1 IF! "
    mov     ax, [bp+4]
    cmp     ax, 1
    jg      L124
; return
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
    mov     ax, 1
    jmp     L123
L124:
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
    jmp     L123
L123:
    leave
    ret
L122:
    jmp     L121
; SEGMENT _TEXT
; glb fib : (
; prm     x : int
;     ) int
SEGMENT _TEXT
    global  _fib
_fib:
    push    bp
    mov     bp, sp
    jmp     L127
L126:
; loc     x : (@4): int
; if
; RPN'ized expression: "x 0 <= "
; Expanded expression: "(@4) *(2) 0 <= "
; Fused expression:    "<= *(@4) 0 IF! "
    mov     ax, [bp+4]
    cmp     ax, 0
    jg      L129
; return
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "0 "
    mov     ax, 0
    jmp     L128
    jmp     L130
L129:
; else
; if
; RPN'ized expression: "x 1 == "
; Expanded expression: "(@4) *(2) 1 == "
; Fused expression:    "== *(@4) 1 IF! "
    mov     ax, [bp+4]
    cmp     ax, 1
    jne     L131
; return
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
    mov     ax, 1
    jmp     L128
L131:
L130:
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
    jmp     L128
L128:
    leave
    ret
L127:
    jmp     L126
; SEGMENT _TEXT
; glb breakCont : (void) void
SEGMENT _TEXT
    global  _breakCont
_breakCont:
    push    bp
    mov     bp, sp
    jmp     L134
L133:
; loc     i : (@-2): int
; for
; RPN'ized expression: "i 0 = "
; Expanded expression: "(@-2) 0 =(2) "
; Fused expression:    "=(34) *(@-2) 0 "
    mov     ax, 0
    mov     [bp-2], ax
L136:
; RPN'ized expression: "i 10 < "
; Expanded expression: "(@-2) *(2) 10 < "
; Fused expression:    "< *(@-2) 10 IF! "
    mov     ax, [bp-2]
    cmp     ax, 10
    jge     L139
    jmp     L138
L137:
; RPN'ized expression: "i ++p "
; Expanded expression: "(@-2) ++p(2) "
; Fused expression:    "++p(2) *(@-2) "
    mov     ax, [bp-2]
    inc     word [bp-2]
    jmp     L136
L138:
; {
; loc         j : (@-4): int
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
    jne     L140
; continue
    jmp     L137
L140:
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
    jne     L142
; break
    jmp     L139
L142:
; }
    jmp     L137
L139:
; RPN'ized expression: "( 10 putchar ) "
; Expanded expression: " 10  putchar ()2 "
; Fused expression:    "( 10 , putchar )2 "
    push    10
    call    _putchar
    sub     sp, -2
L135:
    leave
    ret
L134:
    sub     sp, 4
    jmp     L133
; SEGMENT _TEXT
; glb PointerStew : (void) void
SEGMENT _TEXT
    global  _PointerStew
_PointerStew:
    push    bp
    mov     bp, sp
    jmp     L145
L144:
; RPN'ized expression: "4 "
; Expanded expression: "4 "
; Expression value: 4
; loc     c : (@-8): [4] * char
; RPN'ized expression: "4 "
; Expanded expression: "4 "
; Expression value: 4
; loc     cp : (@-16): [4] * * char
; loc     cpp : (@-18): * * * char
; =
; RPN'ized expression: "cp "
; Expanded expression: "(@-16) "
; Fused expression:    "=(34) *(@-18) (@-16) "
    lea     ax, [bp-16]
    mov     [bp-18], ax
; RPN'ized expression: "c 0 + *u L147 = "
; Expanded expression: "(@-8) 0 + L147 =(2) "
; SEGMENT _TEXT
SEGMENT _DATA
L147:
    db  "ENTER",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "+ (@-8) 0 =(34) *ax L147 "
    lea     ax, [bp-8]
    add     ax, 0
    mov     bx, ax
    mov     ax, L147
    mov     [bx], ax
; RPN'ized expression: "c 1 + *u L149 = "
; Expanded expression: "(@-8) 2 + L149 =(2) "
; SEGMENT _TEXT
SEGMENT _DATA
L149:
    db  "NEW",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "+ (@-8) 2 =(34) *ax L149 "
    lea     ax, [bp-8]
    add     ax, 2
    mov     bx, ax
    mov     ax, L149
    mov     [bx], ax
; RPN'ized expression: "c 2 + *u L151 = "
; Expanded expression: "(@-8) 4 + L151 =(2) "
; SEGMENT _TEXT
SEGMENT _DATA
L151:
    db  "POINT",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "+ (@-8) 4 =(34) *ax L151 "
    lea     ax, [bp-8]
    add     ax, 4
    mov     bx, ax
    mov     ax, L151
    mov     [bx], ax
; RPN'ized expression: "c 3 + *u L153 = "
; Expanded expression: "(@-8) 6 + L153 =(2) "
; SEGMENT _TEXT
SEGMENT _DATA
L153:
    db  "FIRST",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "+ (@-8) 6 =(34) *ax L153 "
    lea     ax, [bp-8]
    add     ax, 6
    mov     bx, ax
    mov     ax, L153
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
; RPN'ized expression: "( cpp ++ *u *u , L155 printf ) "
; Expanded expression: " (@-18) 2 +=(2) *(2) *(2)  L155  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L155:
    db  "%s",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( +=(34) *(@-18) 2 *(2) ax *(2) ax , L155 , printf )4 "
    mov     ax, [bp-18]
    add     ax, 2
    mov     [bp-18], ax
    mov     bx, ax
    mov     ax, [bx]
    mov     bx, ax
    push    word [bx]
    push    L155
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( cpp ++ *u -- *u 3 + , L157 printf ) "
; Expanded expression: " (@-18) 2 +=(2) 2 -=(2) *(2) 3 +  L157  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L157:
    db  "%s ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( +=(34) *(@-18) 2 -=(34) *ax 2 + *ax 3 , L157 , printf )4 "
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
    push    L157
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( cpp 2 -u + *u *u 3 + , L159 printf ) "
; Expanded expression: " (@-18) *(2) -4 + *(2) *(2) 3 +  L159  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L159:
    db  "%s",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( + *(@-18) -4 *(2) ax + *ax 3 , L159 , printf )4 "
    mov     ax, [bp-18]
    add     ax, -4
    mov     bx, ax
    mov     ax, [bx]
    mov     bx, ax
    mov     ax, [bx]
    add     ax, 3
    push    ax
    push    L159
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( cpp 1 -u + *u 1 -u + *u 1 + , L161 printf ) "
; Expanded expression: " (@-18) *(2) -2 + *(2) -2 + *(2) 1 +  L161  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L161:
    db  "%s",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( + *(@-18) -2 + *ax -2 + *ax 1 , L161 , printf )4 "
    mov     ax, [bp-18]
    add     ax, -2
    mov     bx, ax
    mov     ax, [bx]
    add     ax, -2
    mov     bx, ax
    mov     ax, [bx]
    add     ax, 1
    push    ax
    push    L161
    call    _printf
    sub     sp, -4
L146:
    leave
    ret
L145:
    sub     sp, 18
    jmp     L144
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
    jmp     L164
L163:
; loc     Str : (@4): * char
; RPN'ized expression: "( Str , L166 printf ) "
; Expanded expression: " (@4) *(2)  L166  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L166:
    db  "%s",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@4) , L166 , printf )4 "
    push    word [bp+4]
    push    L166
    call    _printf
    sub     sp, -4
; return
; RPN'ized expression: "Print8 &u "
; Expanded expression: "Print8 "
; Fused expression:    "Print8 "
    mov     ax, _Print8
    jmp     L165
L165:
    leave
    ret
L164:
    jmp     L163
; SEGMENT _TEXT
; glb macros : (void) void
SEGMENT _TEXT
    global  _macros
_macros:
    push    bp
    mov     bp, sp
    jmp     L169
L168:
; RPN'ized expression: "( L173 , 42 , L171 printf ) "
; Expanded expression: " L173  42  L171  printf ()6 "
; SEGMENT _TEXT
SEGMENT _DATA
L173:
    db  "42",0
; SEGMENT _DATA
SEGMENT _TEXT
; SEGMENT _TEXT
SEGMENT _DATA
L171:
    db  "SOMETHING=%d, SOMETHING_2=",34,"%s",34,10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L173 , 42 , L171 , printf )6 "
    push    L173
    push    42
    push    L171
    call    _printf
    sub     sp, -6
L170:
    leave
    ret
L169:
    jmp     L168
; SEGMENT _TEXT
; glb Hola : * char
SEGMENT _DATA
    global  _Hola
_Hola:
; =
; RPN'ized expression: "L175 "
; Expanded expression: "L175 "
    dw  L175
; SEGMENT _DATA
SEGMENT _DATA
L175:
    db  "iHola!",0
; SEGMENT _DATA
; glb main : (void) int
SEGMENT _TEXT
    global  _main
_main:
    push    bp
    mov     bp, sp
    jmp     L178
L177:
; RPN'ized expression: "16 "
; Expanded expression: "16 "
; Expression value: 16
; loc     hws : (@-16): [16] char
; loc     phw : (@-18): * char
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
; RPN'ized expression: "( ( hws strlen ) , hws , L180 printf ) "
; Expanded expression: "  (@-16)  strlen ()2  (@-16)  L180  printf ()6 "
; SEGMENT _TEXT
SEGMENT _DATA
L180:
    db  "hws=",34,"%s",34,", strlen(hws)=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( (@-16) , strlen )2 , (@-16) , L180 , printf )6 "
    lea     ax, [bp-16]
    push    ax
    call    _strlen
    sub     sp, -2
    push    ax
    lea     ax, [bp-16]
    push    ax
    push    L180
    call    _printf
    sub     sp, -6
; RPN'ized expression: "( L182 puts ) "
; Expanded expression: " L182  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L182:
    db  "Buongiorno!",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L182 , puts )2 "
    push    L182
    call    _puts
    sub     sp, -2
; RPN'ized expression: "( Hola puts ) "
; Expanded expression: " Hola *(2)  puts ()2 "
; Fused expression:    "( *(2) Hola , puts )2 "
    push    word [_Hola]
    call    _puts
    sub     sp, -2
; RPN'ized expression: "( 65535 , 32767 -u 1 - , L188 , 122 , 43690 , 32767 , L186 , 97 , L184 printf ) "
; Expanded expression: " 65535  -32768  L188  122  43690  32767  L186  97  L184  printf ()18 "
; SEGMENT _TEXT
SEGMENT _DATA
L188:
    db  "xyz",0
; SEGMENT _DATA
SEGMENT _TEXT
; SEGMENT _TEXT
SEGMENT _DATA
L186:
    db  "abc",0
; SEGMENT _DATA
SEGMENT _TEXT
; SEGMENT _TEXT
SEGMENT _DATA
L184:
    db  "%% char='%c' str=",34,"%s",34," dec=%d hex=%x %% char='%c' str=",34,"%s",34," dec=%d hex=%X",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 65535 , -32768 , L188 , 122 , 43690 , 32767 , L186 , 97 , L184 , printf )18 "
    push    65535
    push    -32768
    push    L188
    push    122
    push    43690
    push    32767
    push    L186
    push    97
    push    L184
    call    _printf
    sub     sp, -18
; RPN'ized expression: "( 4095 , 4095 , 4095 , L190 printf ) "
; Expanded expression: " 4095  4095  4095  L190  printf ()8 "
; SEGMENT _TEXT
SEGMENT _DATA
L190:
    db  "07777=%d, 0xFff=%d, 4095=0%o",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 4095 , 4095 , 4095 , L190 , printf )8 "
    push    4095
    push    4095
    push    4095
    push    L190
    call    _printf
    sub     sp, -8
; RPN'ized expression: "( -1 , -1 , 127 , 0 , 127 , 0 , L192 printf ) "
; Expanded expression: " -1  -1  127  0  127  0  L192  printf ()14 "
; SEGMENT _TEXT
SEGMENT _DATA
L192:
    db  "'\x0'=%X, '\x7F'=%X, '\0'=%o, '\177'=%o, '\xFf'=%X, '\377'=%o",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( -1 , -1 , 127 , 0 , 127 , 0 , L192 , printf )14 "
    push    -1
    push    -1
    push    127
    push    0
    push    127
    push    0
    push    L192
    call    _printf
    sub     sp, -14
; RPN'ized expression: "( L198 sizeof , L196 2 + *u , L194 printf ) "
; Expanded expression: " 3  L196 2 + *(1)  L194  printf ()6 "
; SEGMENT _TEXT
SEGMENT _DATA
L196:
    db  "xyz",0
; SEGMENT _DATA
SEGMENT _TEXT
; SEGMENT _TEXT
SEGMENT _DATA
L194:
    db  34,"xyz",34,"[2]='%c', sizeof ",34,"az",34,"=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 3 , + L196 2 *(1) ax , L194 , printf )6 "
    push    3
    mov     ax, L196
    add     ax, 2
    mov     bx, ax
    mov     al, [bx]
    cbw
    push    ax
    push    L194
    call    _printf
    sub     sp, -6
; RPN'ized expression: "( ( 10 fib ) , ( 7 fact ) , L200 printf ) "
; Expanded expression: "  10  fib ()2   7  fact ()2  L200  printf ()6 "
; SEGMENT _TEXT
SEGMENT _DATA
L200:
    db  "fact(7)=%d, fib(10)=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( 10 , fib )2 , ( 7 , fact )2 , L200 , printf )6 "
    push    10
    call    _fib
    sub     sp, -2
    push    ax
    push    7
    call    _fact
    sub     sp, -2
    push    ax
    push    L200
    call    _printf
    sub     sp, -6
; RPN'ized expression: "( L204 , L202 printf ) "
; Expanded expression: " L204  L202  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L204:
    db  "pea",0,"nut",0
; SEGMENT _DATA
SEGMENT _TEXT
; SEGMENT _TEXT
SEGMENT _DATA
L202:
    db  "printf(",34,"pea\0nut",34,"): ",34,"%s",34,10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L204 , L202 , printf )4 "
    push    L204
    push    L202
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( L208 3 + , L206 printf ) "
; Expanded expression: " L208 3 +  L206  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L208:
    db  "peanut",0
; SEGMENT _DATA
SEGMENT _TEXT
; SEGMENT _TEXT
SEGMENT _DATA
L206:
    db  "printf(",34,"peanut",34," + 3): ",34,"%s",34,10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( + L208 3 , L206 , printf )4 "
    mov     ax, L208
    add     ax, 3
    push    ax
    push    L206
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( L210 puts ) "
; Expanded expression: " L210  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L210:
    db  "press a key...",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L210 , puts )2 "
    push    L210
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
; RPN'ized expression: "xx sizeof "
; Expanded expression: "2 "
; Expression value: 2
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
; loc     yy : (@-28): [2] [2] int
; RPN'ized expression: "L212 sizeof "
; Expanded expression: "3 "
; Expression value: 3
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
; loc     zz : (@-40): [3] [2] int
; loc     Switch : (void) void
; RPN'ized expression: "( Switch ) "
; Expanded expression: " Switch ()0 "
; Fused expression:    "( Switch )0 "
    call    _Switch
; loc     pgb : (@-42): * char
; =
; RPN'ized expression: "L214 "
; Expanded expression: "L214 "
; SEGMENT _TEXT
SEGMENT _DATA
L214:
    db  "Green on Black!",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "=(34) *(@-42) L214 "
    mov     ax, L214
    mov     [bp-42], ax
; RPN'ized expression: "( pgb puts ) "
; Expanded expression: " (@-42) *(2)  puts ()2 "
; Fused expression:    "( *(2) (@-42) , puts )2 "
    push    word [bp-42]
    call    _puts
    sub     sp, -2
; loc     x : (@-44): int
; loc     y : (@-46): int
; for
; RPN'ized expression: "y 0 = "
; Expanded expression: "(@-46) 0 =(2) "
; Fused expression:    "=(34) *(@-46) 0 "
    mov     ax, 0
    mov     [bp-46], ax
L216:
; RPN'ized expression: "y 25 < "
; Expanded expression: "(@-46) *(2) 25 < "
; Fused expression:    "< *(@-46) 25 IF! "
    mov     ax, [bp-46]
    cmp     ax, 25
    jge     L219
    jmp     L218
L217:
; RPN'ized expression: "y ++p "
; Expanded expression: "(@-46) ++p(2) "
; Fused expression:    "++p(2) *(@-46) "
    mov     ax, [bp-46]
    inc     word [bp-46]
    jmp     L216
L218:
; for
; RPN'ized expression: "x 0 = "
; Expanded expression: "(@-44) 0 =(2) "
; Fused expression:    "=(34) *(@-44) 0 "
    mov     ax, 0
    mov     [bp-44], ax
L220:
; RPN'ized expression: "x 80 < "
; Expanded expression: "(@-44) *(2) 80 < "
; Fused expression:    "< *(@-44) 80 IF! "
    mov     ax, [bp-44]
    cmp     ax, 80
    jge     L223
    jmp     L222
L221:
; RPN'ized expression: "x ++p "
; Expanded expression: "(@-44) ++p(2) "
; Fused expression:    "++p(2) *(@-44) "
    mov     ax, [bp-44]
    inc     word [bp-44]
    jmp     L220
L222:
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
    jmp     L221
L223:
    jmp     L217
L219:
; RPN'ized expression: "( L224 puts ) "
; Expanded expression: " L224  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L224:
    db  "press a key once for graphics mode and then another time for text mode...",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L224 , puts )2 "
    push    L224
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
L226:
; RPN'ized expression: "y 200 < "
; Expanded expression: "(@-46) *(2) 200 < "
; Fused expression:    "< *(@-46) 200 IF! "
    mov     ax, [bp-46]
    cmp     ax, 200
    jge     L229
    jmp     L228
L227:
; RPN'ized expression: "y ++p "
; Expanded expression: "(@-46) ++p(2) "
; Fused expression:    "++p(2) *(@-46) "
    mov     ax, [bp-46]
    inc     word [bp-46]
    jmp     L226
L228:
; for
; RPN'ized expression: "x 0 = "
; Expanded expression: "(@-44) 0 =(2) "
; Fused expression:    "=(34) *(@-44) 0 "
    mov     ax, 0
    mov     [bp-44], ax
L230:
; RPN'ized expression: "x 320 < "
; Expanded expression: "(@-44) *(2) 320 < "
; Fused expression:    "< *(@-44) 320 IF! "
    mov     ax, [bp-44]
    cmp     ax, 320
    jge     L233
    jmp     L232
L231:
; RPN'ized expression: "x ++p "
; Expanded expression: "(@-44) ++p(2) "
; Fused expression:    "++p(2) *(@-44) "
    mov     ax, [bp-44]
    inc     word [bp-44]
    jmp     L230
L232:
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
    jmp     L231
L233:
    jmp     L227
L229:
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
; RPN'ized expression: "( <something> sizeof , L234 printf ) "
; Expanded expression: " 1  L234  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L234:
    db  "sizeof(char)=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 1 , L234 , printf )4 "
    push    1
    push    L234
    call    _printf
    sub     sp, -4
; loc     <something> : int
; RPN'ized expression: "( <something> sizeof , L236 printf ) "
; Expanded expression: " 2  L236  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L236:
    db  "sizeof(int)=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 2 , L236 , printf )4 "
    push    2
    push    L236
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( , L238 printf 3 "
; Expanded expression: "  L238 printf 3 "
; Expression value: 3
; loc     <something> : [3] char
; RPN'ized expression: "( <something> sizeof , L238 printf ) "
; Expanded expression: " 3  L238  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L238:
    db  "sizeof(char[3])=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 3 , L238 , printf )4 "
    push    3
    push    L238
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( , L240 printf 5 "
; Expanded expression: "  L240 printf 5 "
; Expression value: 5
; loc     <something> : [5] * () char
; RPN'ized expression: "( <something> sizeof , L240 printf ) "
; Expanded expression: " 10  L240  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L240:
    db  "sizeof char(*[5])()=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 10 , L240 , printf )4 "
    push    10
    push    L240
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( , L242 printf 3 "
; Expanded expression: "  L242 printf 3 "
; Expression value: 3
; loc     <something> : [3] int
; RPN'ized expression: "( , L242 printf <something> sizeof "
; Expanded expression: "  L242 printf 6 "
; Expression value: 6
; loc     <something> : [6] int
; RPN'ized expression: "( , L242 printf <something> sizeof "
; Expanded expression: "  L242 printf 12 "
; Expression value: 12
; loc     <something> : [12] int
; RPN'ized expression: "( <something> sizeof , L242 printf ) "
; Expanded expression: " 24  L242  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L242:
    db  "sizeof(int[sizeof(int[sizeof(int[3])])])=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 24 , L242 , printf )4 "
    push    24
    push    L242
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
; loc     <something> : * () char
; RPN'ized expression: "( <something> sizeof , L244 printf ) "
; Expanded expression: " 2  L244  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L244:
    db  "sizeof(char(*)())=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 2 , L244 , printf )4 "
    push    2
    push    L244
    call    _printf
    sub     sp, -4
; loc     <something> : char
; RPN'ized expression: "( <something> sizeof , L246 printf ) "
; Expanded expression: " 1  L246  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L246:
    db  "sizeof(char())=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 1 , L246 , printf )4 "
    push    1
    push    L246
    call    _printf
    sub     sp, -4
; loc     <something> : * char
; RPN'ized expression: "( <something> sizeof , L248 printf ) "
; Expanded expression: " 2  L248  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L248:
    db  "sizeof(char*())=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 2 , L248 , printf )4 "
    push    2
    push    L248
    call    _printf
    sub     sp, -4
; loc     <something> : int
; RPN'ized expression: "( <something> sizeof , L250 printf ) "
; Expanded expression: " 2  L250  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L250:
    db  "sizeof(int())=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 2 , L250 , printf )4 "
    push    2
    push    L250
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( main sizeof , L252 printf ) "
; Expanded expression: " 2  L252  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L252:
    db  "sizeof main=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 2 , L252 , printf )4 "
    push    2
    push    L252
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( ( main ) sizeof , L254 printf ) "
; Expanded expression: " 2  L254  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L254:
    db  "sizeof main()=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 2 , L254 , printf )4 "
    push    2
    push    L254
    call    _printf
    sub     sp, -4
; loc     <something> : () void
; RPN'ized expression: "( <something> sizeof , L256 printf ) "
; Expanded expression: " 2  L256  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L256:
    db  "sizeof(void()())=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 2 , L256 , printf )4 "
    push    2
    push    L256
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( , L258 printf 7 "
; Expanded expression: "  L258 printf 7 "
; Expression value: 7
; loc     <something> : [7] char
; RPN'ized expression: "( <something> sizeof , L258 printf ) "
; Expanded expression: " 7  L258  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L258:
    db  "sizeof((char[7]))=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 7 , L258 , printf )4 "
    push    7
    push    L258
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( PointerStew ) "
; Expanded expression: " PointerStew ()0 "
; Fused expression:    "( PointerStew )0 "
    call    _PointerStew
; RPN'ized expression: "( L268 ( L266 ( L264 ( L262 ( L260 Print8 ) ) ) ) ) "
; Expanded expression: " L268   L266   L264   L262   L260  Print8 ()2 ()2 ()2 ()2 ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L268:
    db  10,0
; SEGMENT _DATA
SEGMENT _TEXT
; SEGMENT _TEXT
SEGMENT _DATA
L266:
    db  "!",0
; SEGMENT _DATA
SEGMENT _TEXT
; SEGMENT _TEXT
SEGMENT _DATA
L264:
    db  "world",0
; SEGMENT _DATA
SEGMENT _TEXT
; SEGMENT _TEXT
SEGMENT _DATA
L262:
    db  " ",0
; SEGMENT _DATA
SEGMENT _TEXT
; SEGMENT _TEXT
SEGMENT _DATA
L260:
    db  "hello",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L268 , ( L266 , ( L264 , ( L262 , ( L260 , Print8 )2 )2 )2 )2 )2 "
    push    L268
    push    L266
    push    L264
    push    L262
    push    L260
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
; RPN'ized expression: "( L270 printf ) "
; Expanded expression: " L270  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L270:
    db  "These are six concatenated string literals!",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L270 , printf )2 "
    push    L270
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( L274 , L272 printf ) "
; Expanded expression: " L274  L272  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L274:
    db  "ABC012abc",0
; SEGMENT _DATA
SEGMENT _TEXT
; SEGMENT _TEXT
SEGMENT _DATA
L272:
    db  34,"\x41\x42\x43\60\61\62abc",34," = ",34,"%s",34,10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L274 , L272 , printf )4 "
    push    L274
    push    L272
    call    _printf
    sub     sp, -4
; RPN'ized expression: "3 "
; Expanded expression: "3 "
; Expression value: 3
; loc     arr : (@-76): [3] int
; loc     p : (@-78): * int
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
; RPN'ized expression: "( p 1 -= *u , L276 printf ) "
; Expanded expression: " (@-78) 2 -=(2) *(2)  L276  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L276:
    db  "arr[0]=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( -=(34) *(@-78) 2 *(2) ax , L276 , printf )4 "
    mov     ax, [bp-78]
    sub     ax, 2
    mov     [bp-78], ax
    mov     bx, ax
    push    word [bx]
    push    L276
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( p 1 += *u , L278 printf ) "
; Expanded expression: " (@-78) 2 +=(2) *(2)  L278  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L278:
    db  "arr[1]=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( +=(34) *(@-78) 2 *(2) ax , L278 , printf )4 "
    mov     ax, [bp-78]
    add     ax, 2
    mov     [bp-78], ax
    mov     bx, ax
    push    word [bx]
    push    L278
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( p 1 += *u , L280 printf ) "
; Expanded expression: " (@-78) 2 +=(2) *(2)  L280  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L280:
    db  "arr[2]=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( +=(34) *(@-78) 2 *(2) ax , L280 , printf )4 "
    mov     ax, [bp-78]
    add     ax, 2
    mov     [bp-78], ax
    mov     bx, ax
    push    word [bx]
    push    L280
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( L282 printf ) "
; Expanded expression: " L282  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L282:
    db  "arr[0] *= arr[1] *= arr[2];",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L282 , printf )2 "
    push    L282
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
; RPN'ized expression: "( arr 2 + *u , arr 1 + *u , arr 0 + *u , L284 printf ) "
; Expanded expression: " (@-76) 4 + *(2)  (@-76) 2 + *(2)  (@-76) 0 + *(2)  L284  printf ()8 "
; SEGMENT _TEXT
SEGMENT _DATA
L284:
    db  "arr[0]=%d",10,"arr[1]=%d",10,"arr[2]=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( + (@-76) 4 *(2) ax , + (@-76) 2 *(2) ax , + (@-76) 0 *(2) ax , L284 , printf )8 "
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
    push    L284
    call    _printf
    sub     sp, -8
; loc     c : (@-80): char
; =
; RPN'ized expression: "127 "
; Expanded expression: "127 "
; Expression value: 127
; Fused expression:    "=(34) *(@-80) 127 "
    mov     ax, 127
    mov     [bp-80], ax
; RPN'ized expression: "( c 127 *= sizeof , c 127 * sizeof , L286 printf ) "
; Expanded expression: " 1  2  L286  printf ()6 "
; SEGMENT _TEXT
SEGMENT _DATA
L286:
    db  "char c = 127; sizeof(c * 127)=%d; sizeof(c *= 127)=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 1 , 2 , L286 , printf )6 "
    push    1
    push    2
    push    L286
    call    _printf
    sub     sp, -6
; RPN'ized expression: "( c 127 * , L288 printf ) "
; Expanded expression: " (@-80) *(1) 127 *  L288  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L288:
    db  "printf(",34,"%%d\n",34,", c * 127): %d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( * *(@-80) 127 , L288 , printf )4 "
    mov     al, [bp-80]
    cbw
    imul    ax, ax, 127
    push    ax
    push    L288
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( c 127 *= , L290 printf ) "
; Expanded expression: " (@-80) 127 *=(1)  L290  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L290:
    db  "printf(",34,"%%d\n",34,", c *= 127): %d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *=(18) *(@-80) 127 , L290 , printf )4 "
    mov     al, [bp-80]
    cbw
    imul    ax, ax, 127
    mov     [bp-80], al
    cbw
    push    ax
    push    L290
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
    jmp     L179
L179:
    leave
    ret
L178:
    sub     sp, 80
    jmp     L177
; SEGMENT _TEXT
; glb Switch : (void) void
SEGMENT _TEXT
    global  _Switch
_Switch:
    push    bp
    mov     bp, sp
    jmp     L293
L292:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
    mov     ax, 1
    jmp     L297
; {
; default
L296:
; }
    jmp     L295
L297:
    jmp     L296
L295:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
    mov     ax, 1
    jmp     L301
; {
; case
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
    jmp     L302
L301:
    cmp     ax, 0
    jne     L303
L302:
; }
    jmp     L299
L303:
L299:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
    mov     ax, 1
    jmp     L307
; {
; case
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
    jmp     L308
L307:
    cmp     ax, 1
    jne     L309
L308:
; }
    jmp     L305
L309:
L305:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
    mov     ax, 1
    jmp     L313
; {
; {
; loc             i : (@-2): int
; }
; }
    jmp     L311
L313:
L311:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
    mov     ax, 1
    jmp     L317
; {
; RPN'ized expression: "( L319 puts ) "
; Expanded expression: " L319  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L319:
    db  "never printed",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L319 , puts )2 "
    push    L319
    call    _puts
    sub     sp, -2
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
; case
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
    jmp     L322
L321:
    cmp     ax, 1
    jne     L325
L322:
; RPN'ized expression: "( L327 puts ) "
; Expanded expression: " L327  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L327:
    db  "1",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L327 , puts )2 "
    push    L327
    call    _puts
    sub     sp, -2
; break
    jmp     L315
; case
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
    jmp     L326
L325:
    cmp     ax, 2
    jne     L329
L326:
; RPN'ized expression: "( L331 puts ) "
; Expanded expression: " L331  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L331:
    db  "2",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L331 , puts )2 "
    push    L331
    call    _puts
    sub     sp, -2
; break
    jmp     L315
; default
L316:
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
    jmp     L315
; }
    jmp     L315
L329:
    jmp     L316
L315:
; switch
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
; Fused expression:    "2 "
    mov     ax, 2
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
    db  "2",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L341 , puts )2 "
    push    L341
    call    _puts
    sub     sp, -2
; break
    jmp     L335
; }
    jmp     L335
L339:
L335:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
    mov     ax, 1
    jmp     L345
; {
; default
L344:
; RPN'ized expression: "( L347 puts ) "
; Expanded expression: " L347  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L347:
    db  "default",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L347 , puts )2 "
    push    L347
    call    _puts
    sub     sp, -2
; break
    jmp     L343
; }
    jmp     L343
L345:
    jmp     L344
L343:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
    mov     ax, 1
    jmp     L351
; {
; default
L350:
; RPN'ized expression: "( L353 puts ) "
; Expanded expression: " L353  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L353:
    db  "default",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L353 , puts )2 "
    push    L353
    call    _puts
    sub     sp, -2
; break
    jmp     L349
; case
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
    jmp     L352
L351:
    cmp     ax, 0
    jne     L355
L352:
; RPN'ized expression: "( L357 puts ) "
; Expanded expression: " L357  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L357:
    db  "0",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L357 , puts )2 "
    push    L357
    call    _puts
    sub     sp, -2
; break
    jmp     L349
; }
    jmp     L349
L355:
    jmp     L350
L349:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
    mov     ax, 1
    jmp     L361
; {
; case
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
    jmp     L362
L361:
    cmp     ax, 0
    jne     L363
L362:
; RPN'ized expression: "( L365 puts ) "
; Expanded expression: " L365  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L365:
    db  "0",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L365 , puts )2 "
    push    L365
    call    _puts
    sub     sp, -2
; break
    jmp     L359
; default
L360:
; RPN'ized expression: "( L367 puts ) "
; Expanded expression: " L367  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L367:
    db  "default",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L367 , puts )2 "
    push    L367
    call    _puts
    sub     sp, -2
; break
    jmp     L359
; }
    jmp     L359
L363:
    jmp     L360
L359:
; switch
; RPN'ized expression: "3 "
; Expanded expression: "3 "
; Expression value: 3
; Fused expression:    "3 "
    mov     ax, 3
    jmp     L371
; {
; case
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
    jmp     L372
L371:
    cmp     ax, 2
    jne     L373
L372:
; RPN'ized expression: "( L375 puts ) "
; Expanded expression: " L375  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L375:
    db  "2 & fallthru",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L375 , puts )2 "
    push    L375
    call    _puts
    sub     sp, -2
; case
; RPN'ized expression: "3 "
; Expanded expression: "3 "
; Expression value: 3
    jmp     L374
L373:
    cmp     ax, 3
    jne     L377
L374:
; RPN'ized expression: "( L379 puts ) "
; Expanded expression: " L379  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L379:
    db  "3 & fallthru",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L379 , puts )2 "
    push    L379
    call    _puts
    sub     sp, -2
; case
; RPN'ized expression: "4 "
; Expanded expression: "4 "
; Expression value: 4
    jmp     L378
L377:
    cmp     ax, 4
    jne     L381
L378:
; RPN'ized expression: "( L383 puts ) "
; Expanded expression: " L383  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L383:
    db  "4 & fallthru",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L383 , puts )2 "
    push    L383
    call    _puts
    sub     sp, -2
; default
L370:
; RPN'ized expression: "( L385 puts ) "
; Expanded expression: " L385  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L385:
    db  "default & fallthru",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L385 , puts )2 "
    push    L385
    call    _puts
    sub     sp, -2
; }
    jmp     L369
L381:
    jmp     L370
L369:
; switch
; RPN'ized expression: "5 "
; Expanded expression: "5 "
; Expression value: 5
; Fused expression:    "5 "
    mov     ax, 5
    jmp     L389
; {
; default
L388:
; RPN'ized expression: "( L391 puts ) "
; Expanded expression: " L391  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L391:
    db  "default & fallthru",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L391 , puts )2 "
    push    L391
    call    _puts
    sub     sp, -2
; case
; RPN'ized expression: "4 "
; Expanded expression: "4 "
; Expression value: 4
    jmp     L390
L389:
    cmp     ax, 4
    jne     L393
L390:
; RPN'ized expression: "( L395 puts ) "
; Expanded expression: " L395  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L395:
    db  "4 & fallthru",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L395 , puts )2 "
    push    L395
    call    _puts
    sub     sp, -2
; case
; RPN'ized expression: "3 "
; Expanded expression: "3 "
; Expression value: 3
    jmp     L394
L393:
    cmp     ax, 3
    jne     L397
L394:
; RPN'ized expression: "( L399 puts ) "
; Expanded expression: " L399  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L399:
    db  "3 & fallthru",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L399 , puts )2 "
    push    L399
    call    _puts
    sub     sp, -2
; case
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
    jmp     L398
L397:
    cmp     ax, 2
    jne     L401
L398:
; RPN'ized expression: "( L403 puts ) "
; Expanded expression: " L403  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L403:
    db  "2 & fallthru",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L403 , puts )2 "
    push    L403
    call    _puts
    sub     sp, -2
; }
    jmp     L387
L401:
    jmp     L388
L387:
; loc     i : (@-2): int
; for
; RPN'ized expression: "i 1 = "
; Expanded expression: "(@-2) 1 =(2) "
; Fused expression:    "=(34) *(@-2) 1 "
    mov     ax, 1
    mov     [bp-2], ax
L405:
; RPN'ized expression: "i 5 <= "
; Expanded expression: "(@-2) *(2) 5 <= "
; Fused expression:    "<= *(@-2) 5 IF! "
    mov     ax, [bp-2]
    cmp     ax, 5
    jg      L408
    jmp     L407
L406:
; RPN'ized expression: "i ++p "
; Expanded expression: "(@-2) ++p(2) "
; Fused expression:    "++p(2) *(@-2) "
    mov     ax, [bp-2]
    inc     word [bp-2]
    jmp     L405
L407:
; switch
; RPN'ized expression: "i "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
    mov     ax, [bp-2]
    jmp     L411
; {
; case
; RPN'ized expression: "3 "
; Expanded expression: "3 "
; Expression value: 3
    jmp     L412
L411:
    cmp     ax, 3
    jne     L413
L412:
; continue
    jmp     L406
; default
L410:
; RPN'ized expression: "( i , L415 printf ) "
; Expanded expression: " (@-2) *(2)  L415  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L415:
    db  "%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-2) , L415 , printf )4 "
    push    word [bp-2]
    push    L415
    call    _printf
    sub     sp, -4
; break
    jmp     L409
; }
    jmp     L409
L413:
    jmp     L410
L409:
    jmp     L406
L408:
; return
    jmp     L294
L294:
    leave
    ret
L293:
    sub     sp, 2
    jmp     L292
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

