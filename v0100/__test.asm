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
; void pokeb(unsigned seg, unsigned ofs, char val);
; void poke(unsigned seg, unsigned ofs, int val);
; char peekb(unsigned seg, int unsigned);
; int peek(unsigned seg, unsigned ofs);
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
; prm     seg : unsigned
; prm     ofs : unsigned
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
;     ) unsigned
SEGMENT _TEXT
    global  _strlen
_strlen:
    push    bp
    mov     bp, sp
    jmp     L7
L6:
; loc     s : (@4): * char
; loc     l : (@-2): unsigned
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
; Expanded expression: "(@4) *(2) 32 == [sh||->31] (@4) *(2) 12 == ||[31] _Bool [sh||->30] (@4) *(2) 10 == ||[30] _Bool [sh||->29] (@4) *(2) 13 == ||[29] _Bool [sh||->28] (@4) *(2) 9 == ||[28] _Bool [sh||->27] (@4) *(2) 11 == ||[27] "
; Fused expression:    "== *(@4) 32 [sh||->31] == *(@4) 12 ||[31] _Bool [sh||->30] == *(@4) 10 ||[30] _Bool [sh||->29] == *(@4) 13 ||[29] _Bool [sh||->28] == *(@4) 9 ||[28] _Bool [sh||->27] == *(@4) 11 ||[27] "
    mov     ax, [bp+4]
    cmp     ax, 32
    sete    al
    cbw
; JumpIfNotZero
    test    ax, ax
    jne     L31
    mov     ax, [bp+4]
    cmp     ax, 12
    sete    al
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
; Expanded expression: "(@4) *(2) 48 >= [sh&&->35] (@4) *(2) 57 <= &&[35] "
; Fused expression:    ">= *(@4) 48 [sh&&->35] <= *(@4) 57 &&[35] "
    mov     ax, [bp+4]
    cmp     ax, 48
    setge   al
    cbw
; JumpIfZero
    test    ax, ax
    je      L35
    mov     ax, [bp+4]
    cmp     ax, 57
    setle   al
    cbw
L35:
    jmp     L34
L34:
    leave
    ret
L33:
    jmp     L32
; SEGMENT _TEXT
; glb vprintf : (
; prm     fmt : * char
; prm     vl : * void
;     ) int
SEGMENT _TEXT
    global  _vprintf
_vprintf:
    push    bp
    mov     bp, sp
    jmp     L37
L36:
; loc     fmt : (@4): * char
; loc     vl : (@6): * void
; loc     pp : (@-2): * int
; =
; RPN'ized expression: "vl "
; Expanded expression: "(@6) *(2) "
; Fused expression:    "=(34) *(@-2) *(@6) "
    mov     ax, [bp+6]
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
; loc     s : (@-20): [12u] char
; loc     pc : (@-22): * char
; loc     n : (@-24): int
; loc     sign : (@-26): int
; loc     msign : (@-28): int
; loc     minlen : (@-30): int
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "=(34) *(@-30) 0 "
    mov     ax, 0
    mov     [bp-30], ax
; loc     len : (@-32): int
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
; Expanded expression: "(@-6) *(2) *(1) 37 != [sh||->47] (@-6) *(2) 1 + *(1) 37 == ||[47] "
; Fused expression:    "*(2) (@-6) != *ax 37 [sh||->47] + *(@-6) 1 == *ax 37 ||[47] "
    mov     ax, [bp-6]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 37
    setne   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jne     L47
    mov     ax, [bp-6]
    inc     ax
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 37
    sete    al
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
; Expanded expression: "(@-30) 0 =(2) "
; Fused expression:    "=(34) *(@-30) 0 "
    mov     ax, 0
    mov     [bp-30], ax
; RPN'ized expression: "msign 0 = "
; Expanded expression: "(@-28) 0 =(2) "
; Fused expression:    "=(34) *(@-28) 0 "
    mov     ax, 0
    mov     [bp-28], ax
; if
; RPN'ized expression: "p *u 43 == "
; Expanded expression: "(@-6) *(2) *(1) 43 == "
; Fused expression:    "*(2) (@-6) == *ax 43 IF! "
    mov     ax, [bp-6]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 43
    jne     L48
; {
; RPN'ized expression: "msign 1 = "
; Expanded expression: "(@-28) 1 =(2) "
; Fused expression:    "=(34) *(@-28) 1 "
    mov     ax, 1
    mov     [bp-28], ax
; RPN'ized expression: "p ++p "
; Expanded expression: "(@-6) ++p(2) "
; Fused expression:    "++p(2) *(@-6) "
    mov     ax, [bp-6]
    inc     word [bp-6]
; }
    jmp     L49
L48:
; else
; if
; RPN'ized expression: "p *u 45 == "
; Expanded expression: "(@-6) *(2) *(1) 45 == "
; Fused expression:    "*(2) (@-6) == *ax 45 IF! "
    mov     ax, [bp-6]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 45
    jne     L50
; {
; RPN'ized expression: "msign 1 -u = "
; Expanded expression: "(@-28) -1 =(2) "
; Fused expression:    "=(34) *(@-28) -1 "
    mov     ax, -1
    mov     [bp-28], ax
; RPN'ized expression: "p ++p "
; Expanded expression: "(@-6) ++p(2) "
; Fused expression:    "++p(2) *(@-6) "
    mov     ax, [bp-6]
    inc     word [bp-6]
; }
L50:
L49:
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
    je      L52
; {
; while
; RPN'ized expression: "( p *u isdigit ) "
; Expanded expression: " (@-6) *(2) *(1)  isdigit ()2 "
L54:
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
    je      L55
; RPN'ized expression: "minlen minlen 10 * p ++p *u + 48 - = "
; Expanded expression: "(@-30) (@-30) *(2) 10 * (@-6) ++p(2) *(1) + 48 - =(2) "
; Fused expression:    "* *(@-30) 10 push-ax ++p(2) *(@-6) + *sp *ax - ax 48 =(34) *(@-30) ax "
    mov     ax, [bp-30]
    imul    ax, ax, 10
    push    ax
    mov     ax, [bp-6]
    inc     word [bp-6]
    mov     bx, ax
    movsx   cx, byte [bx]
    pop     ax
    add     ax, cx
    sub     ax, 48
    mov     [bp-30], ax
    jmp     L54
L55:
; if
; RPN'ized expression: "msign 0 < "
; Expanded expression: "(@-28) *(2) 0 < "
; Fused expression:    "< *(@-28) 0 IF! "
    mov     ax, [bp-28]
    cmp     ax, 0
    jge     L56
; RPN'ized expression: "minlen minlen -u = "
; Expanded expression: "(@-30) (@-30) *(2) -u =(2) "
; Fused expression:    "*(2) (@-30) -u =(34) *(@-30) ax "
    mov     ax, [bp-30]
    neg     ax
    mov     [bp-30], ax
L56:
; RPN'ized expression: "msign 0 = "
; Expanded expression: "(@-28) 0 =(2) "
; Fused expression:    "=(34) *(@-28) 0 "
    mov     ax, 0
    mov     [bp-28], ax
; }
L52:
; if
; RPN'ized expression: "msign 0 == "
; Expanded expression: "(@-28) *(2) 0 == "
; Fused expression:    "== *(@-28) 0 IF! "
    mov     ax, [bp-28]
    cmp     ax, 0
    jne     L58
; {
; if
; RPN'ized expression: "p *u 43 == "
; Expanded expression: "(@-6) *(2) *(1) 43 == "
; Fused expression:    "*(2) (@-6) == *ax 43 IF! "
    mov     ax, [bp-6]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 43
    jne     L60
; {
; RPN'ized expression: "msign 1 = "
; Expanded expression: "(@-28) 1 =(2) "
; Fused expression:    "=(34) *(@-28) 1 "
    mov     ax, 1
    mov     [bp-28], ax
; RPN'ized expression: "p ++p "
; Expanded expression: "(@-6) ++p(2) "
; Fused expression:    "++p(2) *(@-6) "
    mov     ax, [bp-6]
    inc     word [bp-6]
; }
    jmp     L61
L60:
; else
; if
; RPN'ized expression: "p *u 45 == "
; Expanded expression: "(@-6) *(2) *(1) 45 == "
; Fused expression:    "*(2) (@-6) == *ax 45 IF! "
    mov     ax, [bp-6]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 45
    jne     L62
; {
; RPN'ized expression: "msign 1 -u = "
; Expanded expression: "(@-28) -1 =(2) "
; Fused expression:    "=(34) *(@-28) -1 "
    mov     ax, -1
    mov     [bp-28], ax
; RPN'ized expression: "p ++p "
; Expanded expression: "(@-6) ++p(2) "
; Fused expression:    "++p(2) *(@-6) "
    mov     ax, [bp-6]
    inc     word [bp-6]
; }
L62:
L61:
; }
L58:
; switch
; RPN'ized expression: "p *u "
; Expanded expression: "(@-6) *(2) *(1) "
; Fused expression:    "*(2) (@-6) *(1) ax "
    mov     ax, [bp-6]
    mov     bx, ax
    mov     al, [bx]
    cbw
    jmp     L66
; {
; case
; RPN'ized expression: "99 "
; Expanded expression: "99 "
; Expression value: 99
    jmp     L67
L66:
    cmp     ax, 99
    jne     L68
L67:
; while
; RPN'ized expression: "minlen 1 > "
; Expanded expression: "(@-30) *(2) 1 > "
L70:
; Fused expression:    "> *(@-30) 1 IF! "
    mov     ax, [bp-30]
    cmp     ax, 1
    jle     L71
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
; Expanded expression: "(@-30) --p(2) "
; Fused expression:    "--p(2) *(@-30) "
    mov     ax, [bp-30]
    dec     word [bp-30]
; }
    jmp     L70
L71:
; RPN'ized expression: "( pp ++p *u putchar ) "
; Expanded expression: " (@-2) 2 +=p(2) *(2)  putchar ()2 "
; Fused expression:    "( +=p(2) *(@-2) 2 *(2) ax , putchar )2 "
    mov     ax, [bp-2]
    add     word [bp-2], 2
    mov     bx, ax
    push    word [bx]
    call    _putchar
    sub     sp, -2
; while
; RPN'ized expression: "minlen -u 1 > "
; Expanded expression: "(@-30) *(2) -u 1 > "
L72:
; Fused expression:    "*(2) (@-30) -u > ax 1 IF! "
    mov     ax, [bp-30]
    neg     ax
    cmp     ax, 1
    jle     L73
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
; RPN'ized expression: "minlen ++p "
; Expanded expression: "(@-30) ++p(2) "
; Fused expression:    "++p(2) *(@-30) "
    mov     ax, [bp-30]
    inc     word [bp-30]
; }
    jmp     L72
L73:
; RPN'ized expression: "cnt ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
    mov     ax, [bp-4]
    inc     word [bp-4]
; break
    jmp     L64
; case
; RPN'ized expression: "115 "
; Expanded expression: "115 "
; Expression value: 115
    jmp     L69
L68:
    cmp     ax, 115
    jne     L74
L69:
; RPN'ized expression: "pc pp ++p *u = "
; Expanded expression: "(@-22) (@-2) 2 +=p(2) *(2) =(2) "
; Fused expression:    "+=p(2) *(@-2) 2 =(34) *(@-22) *ax "
    mov     ax, [bp-2]
    add     word [bp-2], 2
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-22], ax
; RPN'ized expression: "len 0 = "
; Expanded expression: "(@-32) 0 =(2) "
; Fused expression:    "=(34) *(@-32) 0 "
    mov     ax, 0
    mov     [bp-32], ax
; if
; RPN'ized expression: "pc "
; Expanded expression: "(@-22) *(2) "
; Fused expression:    "*(2) (@-22) "
    mov     ax, [bp-22]
; JumpIfZero
    test    ax, ax
    je      L76
; RPN'ized expression: "len ( pc strlen ) = "
; Expanded expression: "(@-32)  (@-22) *(2)  strlen ()2 =(2) "
; Fused expression:    "( *(2) (@-22) , strlen )2 =(34) *(@-32) ax "
    push    word [bp-22]
    call    _strlen
    sub     sp, -2
    mov     [bp-32], ax
L76:
; while
; RPN'ized expression: "minlen len > "
; Expanded expression: "(@-30) *(2) (@-32) *(2) > "
L78:
; Fused expression:    "> *(@-30) *(@-32) IF! "
    mov     ax, [bp-30]
    cmp     ax, [bp-32]
    jle     L79
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
; Expanded expression: "(@-30) --p(2) "
; Fused expression:    "--p(2) *(@-30) "
    mov     ax, [bp-30]
    dec     word [bp-30]
; }
    jmp     L78
L79:
; if
; RPN'ized expression: "len "
; Expanded expression: "(@-32) *(2) "
; Fused expression:    "*(2) (@-32) "
    mov     ax, [bp-32]
; JumpIfZero
    test    ax, ax
    je      L80
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
L80:
; while
; RPN'ized expression: "minlen -u len > "
; Expanded expression: "(@-30) *(2) -u (@-32) *(2) > "
L84:
; Fused expression:    "*(2) (@-30) -u > ax *(@-32) IF! "
    mov     ax, [bp-30]
    neg     ax
    cmp     ax, [bp-32]
    jle     L85
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
; RPN'ized expression: "minlen ++p "
; Expanded expression: "(@-30) ++p(2) "
; Fused expression:    "++p(2) *(@-30) "
    mov     ax, [bp-30]
    inc     word [bp-30]
; }
    jmp     L84
L85:
; break
    jmp     L64
; case
; RPN'ized expression: "105 "
; Expanded expression: "105 "
; Expression value: 105
    jmp     L75
L74:
    cmp     ax, 105
    jne     L86
L75:
; case
; RPN'ized expression: "100 "
; Expanded expression: "100 "
; Expression value: 100
    jmp     L87
L86:
    cmp     ax, 100
    jne     L88
L87:
; RPN'ized expression: "pc s s sizeof 1 - + *u &u = "
; Expanded expression: "(@-22) (@-20) 11u + =(2) "
; Fused expression:    "+ (@-20) 11u =(34) *(@-22) ax "
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
; Expanded expression: "(@-32) 0 =(2) "
; Fused expression:    "=(34) *(@-32) 0 "
    mov     ax, 0
    mov     [bp-32], ax
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
L90:
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
; Expanded expression: "(@-32) ++p(2) "
; Fused expression:    "++p(2) *(@-32) "
    mov     ax, [bp-32]
    inc     word [bp-32]
; }
; while
; RPN'ized expression: "n "
; Expanded expression: "(@-24) *(2) "
L91:
; Fused expression:    "*(2) (@-24) "
    mov     ax, [bp-24]
; JumpIfNotZero
    test    ax, ax
    jne     L90
L92:
; if
; RPN'ized expression: "sign 0 < "
; Expanded expression: "(@-26) *(2) 0 < "
; Fused expression:    "< *(@-26) 0 IF! "
    mov     ax, [bp-26]
    cmp     ax, 0
    jge     L93
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
; Expanded expression: "(@-32) ++p(2) "
; Fused expression:    "++p(2) *(@-32) "
    mov     ax, [bp-32]
    inc     word [bp-32]
; }
    jmp     L94
L93:
; else
; if
; RPN'ized expression: "msign 0 > "
; Expanded expression: "(@-28) *(2) 0 > "
; Fused expression:    "> *(@-28) 0 IF! "
    mov     ax, [bp-28]
    cmp     ax, 0
    jle     L95
; {
; RPN'ized expression: "pc -- *u 43 = "
; Expanded expression: "(@-22) --(2) 43 =(1) "
; Fused expression:    "--(2) *(@-22) =(18) *ax 43 "
    dec     word [bp-22]
    mov     ax, [bp-22]
    mov     bx, ax
    mov     ax, 43
    mov     [bx], al
    cbw
; RPN'ized expression: "len ++p "
; Expanded expression: "(@-32) ++p(2) "
; Fused expression:    "++p(2) *(@-32) "
    mov     ax, [bp-32]
    inc     word [bp-32]
; RPN'ized expression: "msign 0 = "
; Expanded expression: "(@-28) 0 =(2) "
; Fused expression:    "=(34) *(@-28) 0 "
    mov     ax, 0
    mov     [bp-28], ax
; }
L95:
L94:
; while
; RPN'ized expression: "minlen len > "
; Expanded expression: "(@-30) *(2) (@-32) *(2) > "
L97:
; Fused expression:    "> *(@-30) *(@-32) IF! "
    mov     ax, [bp-30]
    cmp     ax, [bp-32]
    jle     L98
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
; Expanded expression: "(@-30) --p(2) "
; Fused expression:    "--p(2) *(@-30) "
    mov     ax, [bp-30]
    dec     word [bp-30]
; }
    jmp     L97
L98:
; while
; RPN'ized expression: "pc *u 0 != "
; Expanded expression: "(@-22) *(2) *(1) 0 != "
L99:
; Fused expression:    "*(2) (@-22) != *ax 0 IF! "
    mov     ax, [bp-22]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 0
    je      L100
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
    jmp     L99
L100:
; while
; RPN'ized expression: "minlen -u len > "
; Expanded expression: "(@-30) *(2) -u (@-32) *(2) > "
L101:
; Fused expression:    "*(2) (@-30) -u > ax *(@-32) IF! "
    mov     ax, [bp-30]
    neg     ax
    cmp     ax, [bp-32]
    jle     L102
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
; RPN'ized expression: "minlen ++p "
; Expanded expression: "(@-30) ++p(2) "
; Fused expression:    "++p(2) *(@-30) "
    mov     ax, [bp-30]
    inc     word [bp-30]
; }
    jmp     L101
L102:
; break
    jmp     L64
; case
; RPN'ized expression: "117 "
; Expanded expression: "117 "
; Expression value: 117
    jmp     L89
L88:
    cmp     ax, 117
    jne     L103
L89:
; RPN'ized expression: "pc s s sizeof 1 - + *u &u = "
; Expanded expression: "(@-22) (@-20) 11u + =(2) "
; Fused expression:    "+ (@-20) 11u =(34) *(@-22) ax "
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
; Expanded expression: "(@-32) 0 =(2) "
; Fused expression:    "=(34) *(@-32) 0 "
    mov     ax, 0
    mov     [bp-32], ax
; RPN'ized expression: "n pp ++p *u = "
; Expanded expression: "(@-24) (@-2) 2 +=p(2) *(2) =(2) "
; Fused expression:    "+=p(2) *(@-2) 2 =(34) *(@-24) *ax "
    mov     ax, [bp-2]
    add     word [bp-2], 2
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-24], ax
; do
L105:
; {
; loc                 nn : (@-34): unsigned
; =
; RPN'ized expression: "n "
; Expanded expression: "(@-24) *(2) "
; Fused expression:    "=(34) *(@-34) *(@-24) "
    mov     ax, [bp-24]
    mov     [bp-34], ax
; RPN'ized expression: "pc -- *u 48 nn 10 % + = "
; Expanded expression: "(@-22) --(2) 48 (@-34) *(2) 10 %u + =(1) "
; Fused expression:    "--(2) *(@-22) push-ax %u *(@-34) 10 + 48 ax =(18) **sp ax "
    dec     word [bp-22]
    mov     ax, [bp-22]
    push    ax
    mov     ax, [bp-34]
    mov     dx, 0
    mov     cx, 10
    div     cx
    mov     ax, dx
    mov     cx, ax
    mov     ax, 48
    add     ax, cx
    pop     bx
    mov     [bx], al
    cbw
; RPN'ized expression: "n nn 10 / = "
; Expanded expression: "(@-24) (@-34) *(2) 10 /u =(2) "
; Fused expression:    "/u *(@-34) 10 =(34) *(@-24) ax "
    mov     ax, [bp-34]
    mov     dx, 0
    mov     cx, 10
    div     cx
    mov     [bp-24], ax
; RPN'ized expression: "len ++p "
; Expanded expression: "(@-32) ++p(2) "
; Fused expression:    "++p(2) *(@-32) "
    mov     ax, [bp-32]
    inc     word [bp-32]
; }
; while
; RPN'ized expression: "n "
; Expanded expression: "(@-24) *(2) "
L106:
; Fused expression:    "*(2) (@-24) "
    mov     ax, [bp-24]
; JumpIfNotZero
    test    ax, ax
    jne     L105
L107:
; if
; RPN'ized expression: "msign 0 > "
; Expanded expression: "(@-28) *(2) 0 > "
; Fused expression:    "> *(@-28) 0 IF! "
    mov     ax, [bp-28]
    cmp     ax, 0
    jle     L108
; {
; RPN'ized expression: "pc -- *u 43 = "
; Expanded expression: "(@-22) --(2) 43 =(1) "
; Fused expression:    "--(2) *(@-22) =(18) *ax 43 "
    dec     word [bp-22]
    mov     ax, [bp-22]
    mov     bx, ax
    mov     ax, 43
    mov     [bx], al
    cbw
; RPN'ized expression: "len ++p "
; Expanded expression: "(@-32) ++p(2) "
; Fused expression:    "++p(2) *(@-32) "
    mov     ax, [bp-32]
    inc     word [bp-32]
; RPN'ized expression: "msign 0 = "
; Expanded expression: "(@-28) 0 =(2) "
; Fused expression:    "=(34) *(@-28) 0 "
    mov     ax, 0
    mov     [bp-28], ax
; }
L108:
; while
; RPN'ized expression: "minlen len > "
; Expanded expression: "(@-30) *(2) (@-32) *(2) > "
L110:
; Fused expression:    "> *(@-30) *(@-32) IF! "
    mov     ax, [bp-30]
    cmp     ax, [bp-32]
    jle     L111
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
; Expanded expression: "(@-30) --p(2) "
; Fused expression:    "--p(2) *(@-30) "
    mov     ax, [bp-30]
    dec     word [bp-30]
; }
    jmp     L110
L111:
; while
; RPN'ized expression: "pc *u 0 != "
; Expanded expression: "(@-22) *(2) *(1) 0 != "
L112:
; Fused expression:    "*(2) (@-22) != *ax 0 IF! "
    mov     ax, [bp-22]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 0
    je      L113
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
    jmp     L112
L113:
; while
; RPN'ized expression: "minlen -u len > "
; Expanded expression: "(@-30) *(2) -u (@-32) *(2) > "
L114:
; Fused expression:    "*(2) (@-30) -u > ax *(@-32) IF! "
    mov     ax, [bp-30]
    neg     ax
    cmp     ax, [bp-32]
    jle     L115
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
; RPN'ized expression: "minlen ++p "
; Expanded expression: "(@-30) ++p(2) "
; Fused expression:    "++p(2) *(@-30) "
    mov     ax, [bp-30]
    inc     word [bp-30]
; }
    jmp     L114
L115:
; break
    jmp     L64
; case
; RPN'ized expression: "88 "
; Expanded expression: "88 "
; Expression value: 88
    jmp     L104
L103:
    cmp     ax, 88
    jne     L116
L104:
; RPN'ized expression: "phex L118 = "
; Expanded expression: "(@-8) L118 =(2) "
; SEGMENT _TEXT
SEGMENT _DATA
L118:
    db  "0123456789ABCDEF",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "=(34) *(@-8) L118 "
    mov     ax, L118
    mov     [bp-8], ax
; case
; RPN'ized expression: "112 "
; Expanded expression: "112 "
; Expression value: 112
    jmp     L117
L116:
    cmp     ax, 112
    jne     L120
L117:
; case
; RPN'ized expression: "120 "
; Expanded expression: "120 "
; Expression value: 120
    jmp     L121
L120:
    cmp     ax, 120
    jne     L122
L121:
; RPN'ized expression: "pc s s sizeof 1 - + *u &u = "
; Expanded expression: "(@-22) (@-20) 11u + =(2) "
; Fused expression:    "+ (@-20) 11u =(34) *(@-22) ax "
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
; Expanded expression: "(@-32) 0 =(2) "
; Fused expression:    "=(34) *(@-32) 0 "
    mov     ax, 0
    mov     [bp-32], ax
; RPN'ized expression: "n pp ++p *u = "
; Expanded expression: "(@-24) (@-2) 2 +=p(2) *(2) =(2) "
; Fused expression:    "+=p(2) *(@-2) 2 =(34) *(@-24) *ax "
    mov     ax, [bp-2]
    add     word [bp-2], 2
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-24], ax
; do
L124:
; {
; loc                 nn : (@-34): unsigned
; =
; RPN'ized expression: "n "
; Expanded expression: "(@-24) *(2) "
; Fused expression:    "=(34) *(@-34) *(@-24) "
    mov     ax, [bp-24]
    mov     [bp-34], ax
; RPN'ized expression: "pc -- *u phex nn 15 & + *u = "
; Expanded expression: "(@-22) --(2) (@-8) *(2) (@-34) *(2) 15 & + *(1) =(1) "
; Fused expression:    "--(2) *(@-22) push-ax & *(@-34) 15 + *(@-8) ax =(17) **sp *ax "
    dec     word [bp-22]
    mov     ax, [bp-22]
    push    ax
    mov     ax, [bp-34]
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
; RPN'ized expression: "n nn 4 >> = "
; Expanded expression: "(@-24) (@-34) *(2) 4 >>u =(2) "
; Fused expression:    ">>u *(@-34) 4 =(34) *(@-24) ax "
    mov     ax, [bp-34]
    shr     ax, 4
    mov     [bp-24], ax
; RPN'ized expression: "len ++p "
; Expanded expression: "(@-32) ++p(2) "
; Fused expression:    "++p(2) *(@-32) "
    mov     ax, [bp-32]
    inc     word [bp-32]
; }
; while
; RPN'ized expression: "n "
; Expanded expression: "(@-24) *(2) "
L125:
; Fused expression:    "*(2) (@-24) "
    mov     ax, [bp-24]
; JumpIfNotZero
    test    ax, ax
    jne     L124
L126:
; while
; RPN'ized expression: "minlen len > "
; Expanded expression: "(@-30) *(2) (@-32) *(2) > "
L127:
; Fused expression:    "> *(@-30) *(@-32) IF! "
    mov     ax, [bp-30]
    cmp     ax, [bp-32]
    jle     L128
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
; Expanded expression: "(@-30) --p(2) "
; Fused expression:    "--p(2) *(@-30) "
    mov     ax, [bp-30]
    dec     word [bp-30]
; }
    jmp     L127
L128:
; while
; RPN'ized expression: "pc *u 0 != "
; Expanded expression: "(@-22) *(2) *(1) 0 != "
L129:
; Fused expression:    "*(2) (@-22) != *ax 0 IF! "
    mov     ax, [bp-22]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 0
    je      L130
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
    jmp     L129
L130:
; while
; RPN'ized expression: "minlen -u len > "
; Expanded expression: "(@-30) *(2) -u (@-32) *(2) > "
L131:
; Fused expression:    "*(2) (@-30) -u > ax *(@-32) IF! "
    mov     ax, [bp-30]
    neg     ax
    cmp     ax, [bp-32]
    jle     L132
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
; RPN'ized expression: "minlen ++p "
; Expanded expression: "(@-30) ++p(2) "
; Fused expression:    "++p(2) *(@-30) "
    mov     ax, [bp-30]
    inc     word [bp-30]
; }
    jmp     L131
L132:
; break
    jmp     L64
; case
; RPN'ized expression: "111 "
; Expanded expression: "111 "
; Expression value: 111
    jmp     L123
L122:
    cmp     ax, 111
    jne     L133
L123:
; RPN'ized expression: "pc s s sizeof 1 - + *u &u = "
; Expanded expression: "(@-22) (@-20) 11u + =(2) "
; Fused expression:    "+ (@-20) 11u =(34) *(@-22) ax "
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
; Expanded expression: "(@-32) 0 =(2) "
; Fused expression:    "=(34) *(@-32) 0 "
    mov     ax, 0
    mov     [bp-32], ax
; RPN'ized expression: "n pp ++p *u = "
; Expanded expression: "(@-24) (@-2) 2 +=p(2) *(2) =(2) "
; Fused expression:    "+=p(2) *(@-2) 2 =(34) *(@-24) *ax "
    mov     ax, [bp-2]
    add     word [bp-2], 2
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-24], ax
; do
L135:
; {
; loc                 nn : (@-34): unsigned
; =
; RPN'ized expression: "n "
; Expanded expression: "(@-24) *(2) "
; Fused expression:    "=(34) *(@-34) *(@-24) "
    mov     ax, [bp-24]
    mov     [bp-34], ax
; RPN'ized expression: "pc -- *u 48 nn 7 & + = "
; Expanded expression: "(@-22) --(2) 48 (@-34) *(2) 7 & + =(1) "
; Fused expression:    "--(2) *(@-22) push-ax & *(@-34) 7 + 48 ax =(18) **sp ax "
    dec     word [bp-22]
    mov     ax, [bp-22]
    push    ax
    mov     ax, [bp-34]
    and     ax, 7
    mov     cx, ax
    mov     ax, 48
    add     ax, cx
    pop     bx
    mov     [bx], al
    cbw
; RPN'ized expression: "n nn 3 >> = "
; Expanded expression: "(@-24) (@-34) *(2) 3 >>u =(2) "
; Fused expression:    ">>u *(@-34) 3 =(34) *(@-24) ax "
    mov     ax, [bp-34]
    shr     ax, 3
    mov     [bp-24], ax
; RPN'ized expression: "len ++p "
; Expanded expression: "(@-32) ++p(2) "
; Fused expression:    "++p(2) *(@-32) "
    mov     ax, [bp-32]
    inc     word [bp-32]
; }
; while
; RPN'ized expression: "n "
; Expanded expression: "(@-24) *(2) "
L136:
; Fused expression:    "*(2) (@-24) "
    mov     ax, [bp-24]
; JumpIfNotZero
    test    ax, ax
    jne     L135
L137:
; while
; RPN'ized expression: "minlen len > "
; Expanded expression: "(@-30) *(2) (@-32) *(2) > "
L138:
; Fused expression:    "> *(@-30) *(@-32) IF! "
    mov     ax, [bp-30]
    cmp     ax, [bp-32]
    jle     L139
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
; Expanded expression: "(@-30) --p(2) "
; Fused expression:    "--p(2) *(@-30) "
    mov     ax, [bp-30]
    dec     word [bp-30]
; }
    jmp     L138
L139:
; while
; RPN'ized expression: "pc *u 0 != "
; Expanded expression: "(@-22) *(2) *(1) 0 != "
L140:
; Fused expression:    "*(2) (@-22) != *ax 0 IF! "
    mov     ax, [bp-22]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 0
    je      L141
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
    jmp     L140
L141:
; while
; RPN'ized expression: "minlen -u len > "
; Expanded expression: "(@-30) *(2) -u (@-32) *(2) > "
L142:
; Fused expression:    "*(2) (@-30) -u > ax *(@-32) IF! "
    mov     ax, [bp-30]
    neg     ax
    cmp     ax, [bp-32]
    jle     L143
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
; RPN'ized expression: "minlen ++p "
; Expanded expression: "(@-30) ++p(2) "
; Fused expression:    "++p(2) *(@-30) "
    mov     ax, [bp-30]
    inc     word [bp-30]
; }
    jmp     L142
L143:
; break
    jmp     L64
; default
L65:
; return
; RPN'ized expression: "1 -u "
; Expanded expression: "-1 "
; Expression value: -1
; Fused expression:    "-1 "
    mov     ax, -1
    jmp     L38
; }
    jmp     L64
L133:
    jmp     L65
L64:
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
    sub     sp, 34
    jmp     L36
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
    jmp     L145
L144:
; loc     fmt : (@4): * char
; loc     pp : (@-2): * * void
; =
; RPN'ized expression: "fmt &u "
; Expanded expression: "(@4) "
; Fused expression:    "=(34) *(@-2) (@4) "
    lea     ax, [bp+4]
    mov     [bp-2], ax
; return
; RPN'ized expression: "( pp 1 + , fmt vprintf ) "
; Expanded expression: " (@-2) *(2) 2 +  (@4) *(2)  vprintf ()4 "
; Fused expression:    "( + *(@-2) 2 , *(2) (@4) , vprintf )4 "
    mov     ax, [bp-2]
    add     ax, 2
    push    ax
    push    word [bp+4]
    call    _vprintf
    sub     sp, -4
    jmp     L146
L146:
    leave
    ret
L145:
    sub     sp, 2
    jmp     L144
; SEGMENT _TEXT
; glb putdec : (
; prm     n : int
;     ) void
SEGMENT _TEXT
    global  _putdec
_putdec:
    push    bp
    mov     bp, sp
    jmp     L148
L147:
; loc     n : (@4): int
; loc     r : (@-2): int
; if
; RPN'ized expression: "n 0 < "
; Expanded expression: "(@4) *(2) 0 < "
; Fused expression:    "< *(@4) 0 IF! "
    mov     ax, [bp+4]
    cmp     ax, 0
    jge     L150
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
    jmp     L151
L150:
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
L151:
; if
; RPN'ized expression: "n "
; Expanded expression: "(@4) *(2) "
; Fused expression:    "*(2) (@4) "
    mov     ax, [bp+4]
; JumpIfZero
    test    ax, ax
    je      L152
; RPN'ized expression: "( n putdec ) "
; Expanded expression: " (@4) *(2)  putdec ()2 "
; Fused expression:    "( *(2) (@4) , putdec )2 "
    push    word [bp+4]
    call    _putdec
    sub     sp, -2
L152:
; RPN'ized expression: "( 48 r + putchar ) "
; Expanded expression: " 48 (@-2) *(2) +  putchar ()2 "
; Fused expression:    "( + 48 *(@-2) , putchar )2 "
    mov     ax, 48
    add     ax, [bp-2]
    push    ax
    call    _putchar
    sub     sp, -2
L149:
    leave
    ret
L148:
    sub     sp, 2
    jmp     L147
; SEGMENT _TEXT
; glb putdecu : (
; prm     n : unsigned
;     ) void
SEGMENT _TEXT
    global  _putdecu
_putdecu:
    push    bp
    mov     bp, sp
    jmp     L155
L154:
; loc     n : (@4): unsigned
; loc     r : (@-2): int
; RPN'ized expression: "r n 10 % = "
; Expanded expression: "(@-2) (@4) *(2) 10 %u =(2) "
; Fused expression:    "%u *(@4) 10 =(34) *(@-2) ax "
    mov     ax, [bp+4]
    mov     dx, 0
    mov     cx, 10
    div     cx
    mov     ax, dx
    mov     [bp-2], ax
; RPN'ized expression: "n n 10 / = "
; Expanded expression: "(@4) (@4) *(2) 10 /u =(2) "
; Fused expression:    "/u *(@4) 10 =(34) *(@4) ax "
    mov     ax, [bp+4]
    mov     dx, 0
    mov     cx, 10
    div     cx
    mov     [bp+4], ax
; if
; RPN'ized expression: "n "
; Expanded expression: "(@4) *(2) "
; Fused expression:    "*(2) (@4) "
    mov     ax, [bp+4]
; JumpIfZero
    test    ax, ax
    je      L157
; RPN'ized expression: "( n putdecu ) "
; Expanded expression: " (@4) *(2)  putdecu ()2 "
; Fused expression:    "( *(2) (@4) , putdecu )2 "
    push    word [bp+4]
    call    _putdecu
    sub     sp, -2
L157:
; RPN'ized expression: "( 48 r + putchar ) "
; Expanded expression: " 48 (@-2) *(2) +  putchar ()2 "
; Fused expression:    "( + 48 *(@-2) , putchar )2 "
    mov     ax, 48
    add     ax, [bp-2]
    push    ax
    call    _putchar
    sub     sp, -2
L156:
    leave
    ret
L155:
    sub     sp, 2
    jmp     L154
; SEGMENT _TEXT
; glb fact : (
; prm     x : int
;     ) int
SEGMENT _TEXT
    global  _fact
_fact:
    push    bp
    mov     bp, sp
    jmp     L160
L159:
; loc     x : (@4): int
; if
; RPN'ized expression: "x 1 <= "
; Expanded expression: "(@4) *(2) 1 <= "
; Fused expression:    "<= *(@4) 1 IF! "
    mov     ax, [bp+4]
    cmp     ax, 1
    jg      L162
; return
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
    mov     ax, 1
    jmp     L161
L162:
; return
; RPN'ized expression: "x ( x 1 - fact ) * "
; Expanded expression: "(@4) *(2)  (@4) *(2) 1 -  fact ()2 * "
; Fused expression:    "( - *(@4) 1 , fact )2 * *(@4) ax "
    mov     ax, [bp+4]
    dec     ax
    push    ax
    call    _fact
    sub     sp, -2
    mov     cx, ax
    mov     ax, [bp+4]
    mul     cx
    jmp     L161
L161:
    leave
    ret
L160:
    jmp     L159
; SEGMENT _TEXT
; glb fib : (
; prm     x : int
;     ) int
SEGMENT _TEXT
    global  _fib
_fib:
    push    bp
    mov     bp, sp
    jmp     L165
L164:
; loc     x : (@4): int
; if
; RPN'ized expression: "x 0 <= "
; Expanded expression: "(@4) *(2) 0 <= "
; Fused expression:    "<= *(@4) 0 IF! "
    mov     ax, [bp+4]
    cmp     ax, 0
    jg      L167
; return
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "0 "
    mov     ax, 0
    jmp     L166
    jmp     L168
L167:
; else
; if
; RPN'ized expression: "x 1 == "
; Expanded expression: "(@4) *(2) 1 == "
; Fused expression:    "== *(@4) 1 IF! "
    mov     ax, [bp+4]
    cmp     ax, 1
    jne     L169
; return
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
    mov     ax, 1
    jmp     L166
L169:
L168:
; return
; RPN'ized expression: "( x 1 - fib ) ( x 2 - fib ) + "
; Expanded expression: " (@4) *(2) 1 -  fib ()2  (@4) *(2) 2 -  fib ()2 + "
; Fused expression:    "( - *(@4) 1 , fib )2 push-ax ( - *(@4) 2 , fib )2 + *sp ax "
    mov     ax, [bp+4]
    dec     ax
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
    jmp     L166
L166:
    leave
    ret
L165:
    jmp     L164
; SEGMENT _TEXT
; glb breakCont : (void) void
SEGMENT _TEXT
    global  _breakCont
_breakCont:
    push    bp
    mov     bp, sp
    jmp     L172
L171:
; loc     i : (@-2): int
; for
; RPN'ized expression: "i 0 = "
; Expanded expression: "(@-2) 0 =(2) "
; Fused expression:    "=(34) *(@-2) 0 "
    mov     ax, 0
    mov     [bp-2], ax
L174:
; RPN'ized expression: "i 10 < "
; Expanded expression: "(@-2) *(2) 10 < "
; Fused expression:    "< *(@-2) 10 IF! "
    mov     ax, [bp-2]
    cmp     ax, 10
    jge     L177
    jmp     L176
L175:
; RPN'ized expression: "i ++p "
; Expanded expression: "(@-2) ++p(2) "
; Fused expression:    "++p(2) *(@-2) "
    mov     ax, [bp-2]
    inc     word [bp-2]
    jmp     L174
L176:
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
    jne     L178
; continue
    jmp     L175
L178:
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
    jne     L180
; break
    jmp     L177
L180:
; }
    jmp     L175
L177:
; RPN'ized expression: "( 10 putchar ) "
; Expanded expression: " 10  putchar ()2 "
; Fused expression:    "( 10 , putchar )2 "
    push    10
    call    _putchar
    sub     sp, -2
L173:
    leave
    ret
L172:
    sub     sp, 4
    jmp     L171
; SEGMENT _TEXT
; glb PointerStew : (void) void
SEGMENT _TEXT
    global  _PointerStew
_PointerStew:
    push    bp
    mov     bp, sp
    jmp     L183
L182:
; RPN'ized expression: "4 "
; Expanded expression: "4 "
; Expression value: 4
; loc     c : (@-8): [4u] * char
; RPN'ized expression: "4 "
; Expanded expression: "4 "
; Expression value: 4
; loc     cp : (@-16): [4u] * * char
; loc     cpp : (@-18): * * * char
; =
; RPN'ized expression: "cp "
; Expanded expression: "(@-16) "
; Fused expression:    "=(34) *(@-18) (@-16) "
    lea     ax, [bp-16]
    mov     [bp-18], ax
; RPN'ized expression: "c 0 + *u L185 = "
; Expanded expression: "(@-8) 0 + L185 =(2) "
; SEGMENT _TEXT
SEGMENT _DATA
L185:
    db  "ENTER",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "+ (@-8) 0 =(34) *ax L185 "
    lea     ax, [bp-8]
    mov     bx, ax
    mov     ax, L185
    mov     [bx], ax
; RPN'ized expression: "c 1 + *u L187 = "
; Expanded expression: "(@-8) 2 + L187 =(2) "
; SEGMENT _TEXT
SEGMENT _DATA
L187:
    db  "NEW",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "+ (@-8) 2 =(34) *ax L187 "
    lea     ax, [bp-8]
    add     ax, 2
    mov     bx, ax
    mov     ax, L187
    mov     [bx], ax
; RPN'ized expression: "c 2 + *u L189 = "
; Expanded expression: "(@-8) 4 + L189 =(2) "
; SEGMENT _TEXT
SEGMENT _DATA
L189:
    db  "POINT",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "+ (@-8) 4 =(34) *ax L189 "
    lea     ax, [bp-8]
    add     ax, 4
    mov     bx, ax
    mov     ax, L189
    mov     [bx], ax
; RPN'ized expression: "c 3 + *u L191 = "
; Expanded expression: "(@-8) 6 + L191 =(2) "
; SEGMENT _TEXT
SEGMENT _DATA
L191:
    db  "FIRST",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "+ (@-8) 6 =(34) *ax L191 "
    lea     ax, [bp-8]
    add     ax, 6
    mov     bx, ax
    mov     ax, L191
    mov     [bx], ax
; RPN'ized expression: "cp 0 + *u c 3 + = "
; Expanded expression: "(@-16) 0 + (@-8) 6 + =(2) "
; Fused expression:    "+ (@-16) 0 push-ax + (@-8) 6 =(34) **sp ax "
    lea     ax, [bp-16]
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
; RPN'ized expression: "( cpp ++ *u *u , L193 printf ) "
; Expanded expression: " (@-18) 2 +=(2) *(2) *(2)  L193  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L193:
    db  "%s",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( +=(34) *(@-18) 2 *(2) ax *(2) ax , L193 , printf )4 "
    mov     ax, [bp-18]
    add     ax, 2
    mov     [bp-18], ax
    mov     bx, ax
    mov     ax, [bx]
    mov     bx, ax
    push    word [bx]
    push    L193
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( cpp ++ *u -- *u 3 + , L195 printf ) "
; Expanded expression: " (@-18) 2 +=(2) 2 -=(2) *(2) 3 +  L195  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L195:
    db  "%s ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( +=(34) *(@-18) 2 -=(34) *ax 2 + *ax 3 , L195 , printf )4 "
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
    push    L195
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( cpp 2 -u + *u *u 3 + , L197 printf ) "
; Expanded expression: " (@-18) *(2) -4 + *(2) *(2) 3 +  L197  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L197:
    db  "%s",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( + *(@-18) -4 *(2) ax + *ax 3 , L197 , printf )4 "
    mov     ax, [bp-18]
    add     ax, -4
    mov     bx, ax
    mov     ax, [bx]
    mov     bx, ax
    mov     ax, [bx]
    add     ax, 3
    push    ax
    push    L197
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( cpp 1 -u + *u 1 -u + *u 1 + , L199 printf ) "
; Expanded expression: " (@-18) *(2) -2 + *(2) -2 + *(2) 1 +  L199  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L199:
    db  "%s",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( + *(@-18) -2 + *ax -2 + *ax 1 , L199 , printf )4 "
    mov     ax, [bp-18]
    add     ax, -2
    mov     bx, ax
    mov     ax, [bx]
    add     ax, -2
    mov     bx, ax
    mov     ax, [bx]
    inc     ax
    push    ax
    push    L199
    call    _printf
    sub     sp, -4
L184:
    leave
    ret
L183:
    sub     sp, 18
    jmp     L182
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
    jmp     L202
L201:
; loc     Str : (@4): * char
; RPN'ized expression: "( Str , L204 printf ) "
; Expanded expression: " (@4) *(2)  L204  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L204:
    db  "%s",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@4) , L204 , printf )4 "
    push    word [bp+4]
    push    L204
    call    _printf
    sub     sp, -4
; return
; RPN'ized expression: "Print8 &u "
; Expanded expression: "Print8 "
; Fused expression:    "Print8 "
    mov     ax, _Print8
    jmp     L203
L203:
    leave
    ret
L202:
    jmp     L201
; SEGMENT _TEXT
; glb macros : (void) void
SEGMENT _TEXT
    global  _macros
_macros:
    push    bp
    mov     bp, sp
    jmp     L207
L206:
; RPN'ized expression: "( L211 , 42 , L209 printf ) "
; Expanded expression: " L211  42  L209  printf ()6 "
; SEGMENT _TEXT
SEGMENT _DATA
L211:
    db  "42",0
; SEGMENT _DATA
SEGMENT _TEXT
; SEGMENT _TEXT
SEGMENT _DATA
L209:
    db  "SOMETHING=%d, SOMETHING_2=",34,"%s",34,10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L211 , 42 , L209 , printf )6 "
    push    L211
    push    42
    push    L209
    call    _printf
    sub     sp, -6
L208:
    leave
    ret
L207:
    jmp     L206
; SEGMENT _TEXT
; glb Hola : * char
SEGMENT _DATA
    global  _Hola
_Hola:
; =
; RPN'ized expression: "L213 "
; Expanded expression: "L213 "
    dw  L213
; SEGMENT _DATA
SEGMENT _DATA
L213:
    db  "iHola!",0
; SEGMENT _DATA
; glb main : (void) int
SEGMENT _TEXT
    global  _main
_main:
    push    bp
    mov     bp, sp
    jmp     L216
L215:
; RPN'ized expression: "16 "
; Expanded expression: "16 "
; Expression value: 16
; loc     hws : (@-16): [16u] char
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
; RPN'ized expression: "( ( hws strlen ) , hws , L218 printf ) "
; Expanded expression: "  (@-16)  strlen ()2  (@-16)  L218  printf ()6 "
; SEGMENT _TEXT
SEGMENT _DATA
L218:
    db  "hws=",34,"%s",34,", strlen(hws)=%u",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( (@-16) , strlen )2 , (@-16) , L218 , printf )6 "
    lea     ax, [bp-16]
    push    ax
    call    _strlen
    sub     sp, -2
    push    ax
    lea     ax, [bp-16]
    push    ax
    push    L218
    call    _printf
    sub     sp, -6
; RPN'ized expression: "( L220 puts ) "
; Expanded expression: " L220  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L220:
    db  "Buongiorno!",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L220 , puts )2 "
    push    L220
    call    _puts
    sub     sp, -2
; RPN'ized expression: "( Hola puts ) "
; Expanded expression: " Hola *(2)  puts ()2 "
; Fused expression:    "( *(2) Hola , puts )2 "
    push    word [_Hola]
    call    _puts
    sub     sp, -2
; RPN'ized expression: "( 65535u , 32767 -u 1 - , L226 , 122 , 43690u , 32767 , L224 , 97 , L222 printf ) "
; Expanded expression: " 65535u  -32768  L226  122  43690u  32767  L224  97  L222  printf ()18 "
; SEGMENT _TEXT
SEGMENT _DATA
L226:
    db  "xyz",0
; SEGMENT _DATA
SEGMENT _TEXT
; SEGMENT _TEXT
SEGMENT _DATA
L224:
    db  "abc",0
; SEGMENT _DATA
SEGMENT _TEXT
; SEGMENT _TEXT
SEGMENT _DATA
L222:
    db  "%% char='%c' str=",34,"%s",34," dec=%d hex=%x %% char='%c' str=",34,"%s",34," dec=%d hex=%X",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 65535u , -32768 , L226 , 122 , 43690u , 32767 , L224 , 97 , L222 , printf )18 "
    push    -1
    push    -32768
    push    L226
    push    122
    push    -21846
    push    32767
    push    L224
    push    97
    push    L222
    call    _printf
    sub     sp, -18
; RPN'ized expression: "( 4095 , 4095 , 4095 , L228 printf ) "
; Expanded expression: " 4095  4095  4095  L228  printf ()8 "
; SEGMENT _TEXT
SEGMENT _DATA
L228:
    db  "07777=%d, 0xFff=%d, 4095=0%o",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 4095 , 4095 , 4095 , L228 , printf )8 "
    push    4095
    push    4095
    push    4095
    push    L228
    call    _printf
    sub     sp, -8
; RPN'ized expression: "( -1 , -1 , 127 , 0 , 127 , 0 , L230 printf ) "
; Expanded expression: " -1  -1  127  0  127  0  L230  printf ()14 "
; SEGMENT _TEXT
SEGMENT _DATA
L230:
    db  "'\x0'=%X, '\x7F'=%X, '\0'=%o, '\177'=%o, '\xFf'=%X, '\377'=%o",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( -1 , -1 , 127 , 0 , 127 , 0 , L230 , printf )14 "
    push    -1
    push    -1
    push    127
    push    0
    push    127
    push    0
    push    L230
    call    _printf
    sub     sp, -14
; RPN'ized expression: "( L236 sizeof , L234 2 + *u , L232 printf ) "
; Expanded expression: " 3u  L234 2 + *(1)  L232  printf ()6 "
; SEGMENT _TEXT
SEGMENT _DATA
L234:
    db  "xyz",0
; SEGMENT _DATA
SEGMENT _TEXT
; SEGMENT _TEXT
SEGMENT _DATA
L232:
    db  34,"xyz",34,"[2]='%c', sizeof ",34,"az",34,"=%u",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 3u , + L234 2 *(1) ax , L232 , printf )6 "
    push    3
    mov     ax, L234
    add     ax, 2
    mov     bx, ax
    mov     al, [bx]
    cbw
    push    ax
    push    L232
    call    _printf
    sub     sp, -6
; RPN'ized expression: "( ( 10 fib ) , ( 7 fact ) , L238 printf ) "
; Expanded expression: "  10  fib ()2   7  fact ()2  L238  printf ()6 "
; SEGMENT _TEXT
SEGMENT _DATA
L238:
    db  "fact(7)=%d, fib(10)=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( 10 , fib )2 , ( 7 , fact )2 , L238 , printf )6 "
    push    10
    call    _fib
    sub     sp, -2
    push    ax
    push    7
    call    _fact
    sub     sp, -2
    push    ax
    push    L238
    call    _printf
    sub     sp, -6
; RPN'ized expression: "( L242 , L240 printf ) "
; Expanded expression: " L242  L240  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L242:
    db  "pea",0,"nut",0
; SEGMENT _DATA
SEGMENT _TEXT
; SEGMENT _TEXT
SEGMENT _DATA
L240:
    db  "printf(",34,"pea\0nut",34,"): ",34,"%s",34,10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L242 , L240 , printf )4 "
    push    L242
    push    L240
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( L246 3 + , L244 printf ) "
; Expanded expression: " L246 3 +  L244  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L246:
    db  "peanut",0
; SEGMENT _DATA
SEGMENT _TEXT
; SEGMENT _TEXT
SEGMENT _DATA
L244:
    db  "printf(",34,"peanut",34," + 3): ",34,"%s",34,10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( + L246 3 , L244 , printf )4 "
    mov     ax, L246
    add     ax, 3
    push    ax
    push    L244
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( L248 puts ) "
; Expanded expression: " L248  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L248:
    db  "press a key...",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L248 , puts )2 "
    push    L248
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
; Expanded expression: "2u "
; Expression value: 2
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
; loc     yy : (@-28): [2u] [2u] int
; RPN'ized expression: "L250 sizeof "
; Expanded expression: "3u "
; Expression value: 3
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
; loc     zz : (@-40): [3u] [2u] int
; loc     Switch : (void) void
; RPN'ized expression: "( Switch ) "
; Expanded expression: " Switch ()0 "
; Fused expression:    "( Switch )0 "
    call    _Switch
; loc     pgb : (@-42): * char
; =
; RPN'ized expression: "L252 "
; Expanded expression: "L252 "
; SEGMENT _TEXT
SEGMENT _DATA
L252:
    db  "Green on Black!",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "=(34) *(@-42) L252 "
    mov     ax, L252
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
L254:
; RPN'ized expression: "y 25 < "
; Expanded expression: "(@-46) *(2) 25 < "
; Fused expression:    "< *(@-46) 25 IF! "
    mov     ax, [bp-46]
    cmp     ax, 25
    jge     L257
    jmp     L256
L255:
; RPN'ized expression: "y ++p "
; Expanded expression: "(@-46) ++p(2) "
; Fused expression:    "++p(2) *(@-46) "
    mov     ax, [bp-46]
    inc     word [bp-46]
    jmp     L254
L256:
; for
; RPN'ized expression: "x 0 = "
; Expanded expression: "(@-44) 0 =(2) "
; Fused expression:    "=(34) *(@-44) 0 "
    mov     ax, 0
    mov     [bp-44], ax
L258:
; RPN'ized expression: "x 80 < "
; Expanded expression: "(@-44) *(2) 80 < "
; Fused expression:    "< *(@-44) 80 IF! "
    mov     ax, [bp-44]
    cmp     ax, 80
    jge     L261
    jmp     L260
L259:
; RPN'ized expression: "x ++p "
; Expanded expression: "(@-44) ++p(2) "
; Fused expression:    "++p(2) *(@-44) "
    mov     ax, [bp-44]
    inc     word [bp-44]
    jmp     L258
L260:
; RPN'ized expression: "( 2 , y 80 * x + 2 * 1 + , 47104u pokeb ) "
; Expanded expression: " 2  (@-46) *(2) 80 * (@-44) *(2) + 2 * 1 +  47104u  pokeb ()6 "
; Fused expression:    "( 2 , * *(@-46) 80 + ax *(@-44) * ax 2 + ax 1 , 47104u , pokeb )6 "
    push    2
    mov     ax, [bp-46]
    imul    ax, ax, 80
    add     ax, [bp-44]
    imul    ax, ax, 2
    inc     ax
    push    ax
    push    -18432
    call    _pokeb
    sub     sp, -6
    jmp     L259
L261:
    jmp     L255
L257:
; RPN'ized expression: "( L262 puts ) "
; Expanded expression: " L262  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L262:
    db  "press a key once for graphics mode and then another time for text mode...",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L262 , puts )2 "
    push    L262
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
L264:
; RPN'ized expression: "y 200 < "
; Expanded expression: "(@-46) *(2) 200 < "
; Fused expression:    "< *(@-46) 200 IF! "
    mov     ax, [bp-46]
    cmp     ax, 200
    jge     L267
    jmp     L266
L265:
; RPN'ized expression: "y ++p "
; Expanded expression: "(@-46) ++p(2) "
; Fused expression:    "++p(2) *(@-46) "
    mov     ax, [bp-46]
    inc     word [bp-46]
    jmp     L264
L266:
; for
; RPN'ized expression: "x 0 = "
; Expanded expression: "(@-44) 0 =(2) "
; Fused expression:    "=(34) *(@-44) 0 "
    mov     ax, 0
    mov     [bp-44], ax
L268:
; RPN'ized expression: "x 320 < "
; Expanded expression: "(@-44) *(2) 320 < "
; Fused expression:    "< *(@-44) 320 IF! "
    mov     ax, [bp-44]
    cmp     ax, 320
    jge     L271
    jmp     L270
L269:
; RPN'ized expression: "x ++p "
; Expanded expression: "(@-44) ++p(2) "
; Fused expression:    "++p(2) *(@-44) "
    mov     ax, [bp-44]
    inc     word [bp-44]
    jmp     L268
L270:
; RPN'ized expression: "( x y + 15 & , y 320 * x + , 40960u pokeb ) "
; Expanded expression: " (@-44) *(2) (@-46) *(2) + 15 &  (@-46) *(2) 320 * (@-44) *(2) +  40960u  pokeb ()6 "
; Fused expression:    "( + *(@-44) *(@-46) & ax 15 , * *(@-46) 320 + ax *(@-44) , 40960u , pokeb )6 "
    mov     ax, [bp-44]
    add     ax, [bp-46]
    and     ax, 15
    push    ax
    mov     ax, [bp-46]
    imul    ax, ax, 320
    add     ax, [bp-44]
    push    ax
    push    -24576
    call    _pokeb
    sub     sp, -6
    jmp     L269
L271:
    jmp     L265
L267:
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
; RPN'ized expression: "( <something> sizeof , L272 printf ) "
; Expanded expression: " 1u  L272  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L272:
    db  "sizeof(char)=%u",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 1u , L272 , printf )4 "
    push    1
    push    L272
    call    _printf
    sub     sp, -4
; loc     <something> : int
; RPN'ized expression: "( <something> sizeof , L274 printf ) "
; Expanded expression: " 2u  L274  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L274:
    db  "sizeof(int)=%u",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 2u , L274 , printf )4 "
    push    2
    push    L274
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( , L276 printf 3 "
; Expanded expression: "  L276 printf 3 "
; Expression value: 3
; loc     <something> : [3u] char
; RPN'ized expression: "( <something> sizeof , L276 printf ) "
; Expanded expression: " 3u  L276  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L276:
    db  "sizeof(char[3])=%u",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 3u , L276 , printf )4 "
    push    3
    push    L276
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( , L278 printf 5 "
; Expanded expression: "  L278 printf 5 "
; Expression value: 5
; loc     <something> : [5u] * () char
; RPN'ized expression: "( <something> sizeof , L278 printf ) "
; Expanded expression: " 10u  L278  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L278:
    db  "sizeof char(*[5])()=%u",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 10u , L278 , printf )4 "
    push    10
    push    L278
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( , L280 printf 3 "
; Expanded expression: "  L280 printf 3 "
; Expression value: 3
; loc     <something> : [3u] int
; RPN'ized expression: "( , L280 printf <something> sizeof "
; Expanded expression: "  L280 printf 6u "
; Expression value: 6
; loc     <something> : [6u] int
; RPN'ized expression: "( , L280 printf <something> sizeof "
; Expanded expression: "  L280 printf 12u "
; Expression value: 12
; loc     <something> : [12u] int
; RPN'ized expression: "( <something> sizeof , L280 printf ) "
; Expanded expression: " 24u  L280  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L280:
    db  "sizeof(int[sizeof(int[sizeof(int[3])])])=%u",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 24u , L280 , printf )4 "
    push    24
    push    L280
    call    _printf
    sub     sp, -4
; RPN'ized expression: "3 "
; Expanded expression: "3 "
; Expression value: 3
; loc     <something> : [3u] int
; RPN'ized expression: "<something> sizeof "
; Expanded expression: "6u "
; Expression value: 6
; loc     <something> : [6u] int
; RPN'ized expression: "<something> sizeof "
; Expanded expression: "12u "
; Expression value: 12
; loc     <something> : [12u] int
; RPN'ized expression: "<something> sizeof "
; Expanded expression: "24u "
; Expression value: 24
; loc     yui : (@-70): [24u] char
; loc     <something> : * () char
; RPN'ized expression: "( <something> sizeof , L282 printf ) "
; Expanded expression: " 2u  L282  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L282:
    db  "sizeof(char(*)())=%u",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 2u , L282 , printf )4 "
    push    2
    push    L282
    call    _printf
    sub     sp, -4
; loc     <something> : char
; RPN'ized expression: "( <something> sizeof , L284 printf ) "
; Expanded expression: " 1u  L284  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L284:
    db  "sizeof(char())=%u",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 1u , L284 , printf )4 "
    push    1
    push    L284
    call    _printf
    sub     sp, -4
; loc     <something> : * char
; RPN'ized expression: "( <something> sizeof , L286 printf ) "
; Expanded expression: " 2u  L286  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L286:
    db  "sizeof(char*())=%u",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 2u , L286 , printf )4 "
    push    2
    push    L286
    call    _printf
    sub     sp, -4
; loc     <something> : int
; RPN'ized expression: "( <something> sizeof , L288 printf ) "
; Expanded expression: " 2u  L288  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L288:
    db  "sizeof(int())=%u",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 2u , L288 , printf )4 "
    push    2
    push    L288
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( main sizeof , L290 printf ) "
; Expanded expression: " 2u  L290  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L290:
    db  "sizeof main=%u",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 2u , L290 , printf )4 "
    push    2
    push    L290
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( ( main ) sizeof , L292 printf ) "
; Expanded expression: " 2u  L292  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L292:
    db  "sizeof main()=%u",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 2u , L292 , printf )4 "
    push    2
    push    L292
    call    _printf
    sub     sp, -4
; loc     <something> : () void
; RPN'ized expression: "( <something> sizeof , L294 printf ) "
; Expanded expression: " 2u  L294  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L294:
    db  "sizeof(void()())=%u",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 2u , L294 , printf )4 "
    push    2
    push    L294
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( , L296 printf 7 "
; Expanded expression: "  L296 printf 7 "
; Expression value: 7
; loc     <something> : [7u] char
; RPN'ized expression: "( <something> sizeof , L296 printf ) "
; Expanded expression: " 7u  L296  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L296:
    db  "sizeof((char[7]))=%u",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 7u , L296 , printf )4 "
    push    7
    push    L296
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( PointerStew ) "
; Expanded expression: " PointerStew ()0 "
; Fused expression:    "( PointerStew )0 "
    call    _PointerStew
; RPN'ized expression: "( L306 ( L304 ( L302 ( L300 ( L298 Print8 ) ) ) ) ) "
; Expanded expression: " L306   L304   L302   L300   L298  Print8 ()2 ()2 ()2 ()2 ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L306:
    db  10,0
; SEGMENT _DATA
SEGMENT _TEXT
; SEGMENT _TEXT
SEGMENT _DATA
L304:
    db  "!",0
; SEGMENT _DATA
SEGMENT _TEXT
; SEGMENT _TEXT
SEGMENT _DATA
L302:
    db  "world",0
; SEGMENT _DATA
SEGMENT _TEXT
; SEGMENT _TEXT
SEGMENT _DATA
L300:
    db  " ",0
; SEGMENT _DATA
SEGMENT _TEXT
; SEGMENT _TEXT
SEGMENT _DATA
L298:
    db  "hello",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L306 , ( L304 , ( L302 , ( L300 , ( L298 , Print8 )2 )2 )2 )2 )2 "
    push    L306
    push    L304
    push    L302
    push    L300
    push    L298
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
; RPN'ized expression: "( L308 printf ) "
; Expanded expression: " L308  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L308:
    db  "These are six concatenated string literals!",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L308 , printf )2 "
    push    L308
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( L312 , L310 printf ) "
; Expanded expression: " L312  L310  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L312:
    db  "ABC012abc",0
; SEGMENT _DATA
SEGMENT _TEXT
; SEGMENT _TEXT
SEGMENT _DATA
L310:
    db  34,"\x41\x42\x43\60\61\62abc",34," = ",34,"%s",34,10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L312 , L310 , printf )4 "
    push    L312
    push    L310
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( L314 puts ) "
; Expanded expression: " L314  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L314:
    db  "press a key...",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L314 , puts )2 "
    push    L314
    call    _puts
    sub     sp, -2
; RPN'ized expression: "( getchar ) "
; Expanded expression: " getchar ()0 "
; Fused expression:    "( getchar )0 "
    call    _getchar
; RPN'ized expression: "3 "
; Expanded expression: "3 "
; Expression value: 3
; loc     arr : (@-76): [3u] int
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
; RPN'ized expression: "( p 1 -= *u , L316 printf ) "
; Expanded expression: " (@-78) 2 -=(2) *(2)  L316  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L316:
    db  "arr[0]=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( -=(34) *(@-78) 2 *(2) ax , L316 , printf )4 "
    mov     ax, [bp-78]
    sub     ax, 2
    mov     [bp-78], ax
    mov     bx, ax
    push    word [bx]
    push    L316
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( p 1 += *u , L318 printf ) "
; Expanded expression: " (@-78) 2 +=(2) *(2)  L318  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L318:
    db  "arr[1]=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( +=(34) *(@-78) 2 *(2) ax , L318 , printf )4 "
    mov     ax, [bp-78]
    add     ax, 2
    mov     [bp-78], ax
    mov     bx, ax
    push    word [bx]
    push    L318
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( p 1 += *u , L320 printf ) "
; Expanded expression: " (@-78) 2 +=(2) *(2)  L320  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L320:
    db  "arr[2]=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( +=(34) *(@-78) 2 *(2) ax , L320 , printf )4 "
    mov     ax, [bp-78]
    add     ax, 2
    mov     [bp-78], ax
    mov     bx, ax
    push    word [bx]
    push    L320
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( L322 printf ) "
; Expanded expression: " L322  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L322:
    db  "arr[0] *= arr[1] *= arr[2];",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L322 , printf )2 "
    push    L322
    call    _printf
    sub     sp, -2
; RPN'ized expression: "arr 0 + *u arr 1 + *u arr 2 + *u *= *= "
; Expanded expression: "(@-76) 0 + (@-76) 2 + (@-76) 4 + *(2) *=(2) *=(2) "
; Fused expression:    "+ (@-76) 0 push-ax + (@-76) 2 push-ax + (@-76) 4 *=(34) **sp *ax *=(34) **sp ax "
    lea     ax, [bp-76]
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
; RPN'ized expression: "( arr 2 + *u , arr 1 + *u , arr 0 + *u , L324 printf ) "
; Expanded expression: " (@-76) 4 + *(2)  (@-76) 2 + *(2)  (@-76) 0 + *(2)  L324  printf ()8 "
; SEGMENT _TEXT
SEGMENT _DATA
L324:
    db  "arr[0]=%d",10,"arr[1]=%d",10,"arr[2]=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( + (@-76) 4 *(2) ax , + (@-76) 2 *(2) ax , + (@-76) 0 *(2) ax , L324 , printf )8 "
    lea     ax, [bp-76]
    add     ax, 4
    mov     bx, ax
    push    word [bx]
    lea     ax, [bp-76]
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    lea     ax, [bp-76]
    mov     bx, ax
    push    word [bx]
    push    L324
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
; RPN'ized expression: "( c 127 *= sizeof , c 127 * sizeof , L326 printf ) "
; Expanded expression: " 1u  2u  L326  printf ()6 "
; SEGMENT _TEXT
SEGMENT _DATA
L326:
    db  "char c = 127; sizeof(c * 127)=%d; sizeof(c *= 127)=%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 1u , 2u , L326 , printf )6 "
    push    1
    push    2
    push    L326
    call    _printf
    sub     sp, -6
; RPN'ized expression: "( c 127 * , L328 printf ) "
; Expanded expression: " (@-80) *(1) 127 *  L328  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L328:
    db  "printf(",34,"%%d\n",34,", c * 127): %d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( * *(@-80) 127 , L328 , printf )4 "
    mov     al, [bp-80]
    cbw
    imul    ax, ax, 127
    push    ax
    push    L328
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( c 127 *= , L330 printf ) "
; Expanded expression: " (@-80) 127 *=(1)  L330  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L330:
    db  "printf(",34,"%%d\n",34,", c *= 127): %d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *=(18) *(@-80) 127 , L330 , printf )4 "
    mov     al, [bp-80]
    cbw
    imul    ax, ax, 127
    mov     [bp-80], al
    cbw
    push    ax
    push    L330
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
; RPN'ized expression: "( 32768u putdecu ) "
; Expanded expression: " 32768u  putdecu ()2 "
; Fused expression:    "( 32768u , putdecu )2 "
    push    -32768
    call    _putdecu
    sub     sp, -2
; RPN'ized expression: "( 10 putchar ) "
; Expanded expression: " 10  putchar ()2 "
; Fused expression:    "( 10 , putchar )2 "
    push    10
    call    _putchar
    sub     sp, -2
; RPN'ized expression: "( 32769u putdecu ) "
; Expanded expression: " 32769u  putdecu ()2 "
; Fused expression:    "( 32769u , putdecu )2 "
    push    -32767
    call    _putdecu
    sub     sp, -2
; RPN'ized expression: "( 10 putchar ) "
; Expanded expression: " 10  putchar ()2 "
; Fused expression:    "( 10 , putchar )2 "
    push    10
    call    _putchar
    sub     sp, -2
; RPN'ized expression: "( 32770u putdecu ) "
; Expanded expression: " 32770u  putdecu ()2 "
; Fused expression:    "( 32770u , putdecu )2 "
    push    -32766
    call    _putdecu
    sub     sp, -2
; RPN'ized expression: "( 10 putchar ) "
; Expanded expression: " 10  putchar ()2 "
; Fused expression:    "( 10 , putchar )2 "
    push    10
    call    _putchar
    sub     sp, -2
; RPN'ized expression: "( 65533u putdecu ) "
; Expanded expression: " 65533u  putdecu ()2 "
; Fused expression:    "( 65533u , putdecu )2 "
    push    -3
    call    _putdecu
    sub     sp, -2
; RPN'ized expression: "( 10 putchar ) "
; Expanded expression: " 10  putchar ()2 "
; Fused expression:    "( 10 , putchar )2 "
    push    10
    call    _putchar
    sub     sp, -2
; RPN'ized expression: "( 65534u putdecu ) "
; Expanded expression: " 65534u  putdecu ()2 "
; Fused expression:    "( 65534u , putdecu )2 "
    push    -2
    call    _putdecu
    sub     sp, -2
; RPN'ized expression: "( 10 putchar ) "
; Expanded expression: " 10  putchar ()2 "
; Fused expression:    "( 10 , putchar )2 "
    push    10
    call    _putchar
    sub     sp, -2
; RPN'ized expression: "( 65535u , L332 printf ) "
; Expanded expression: " 65535u  L332  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L332:
    db  "%u",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 65535u , L332 , printf )4 "
    push    -1
    push    L332
    call    _printf
    sub     sp, -4
; return
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "0 "
    mov     ax, 0
    jmp     L217
L217:
    leave
    ret
L216:
    sub     sp, 80
    jmp     L215
; SEGMENT _TEXT
; glb Switch : (void) void
SEGMENT _TEXT
    global  _Switch
_Switch:
    push    bp
    mov     bp, sp
    jmp     L335
L334:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
    mov     ax, 1
    jmp     L339
; {
; default
L338:
; }
    jmp     L337
L339:
    jmp     L338
L337:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
    mov     ax, 1
    jmp     L343
; {
; case
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
    jmp     L344
L343:
    cmp     ax, 0
    jne     L345
L344:
; }
    jmp     L341
L345:
L341:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
    mov     ax, 1
    jmp     L349
; {
; case
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
    jmp     L350
L349:
    cmp     ax, 1
    jne     L351
L350:
; }
    jmp     L347
L351:
L347:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
    mov     ax, 1
    jmp     L355
; {
; {
; loc             i : (@-2): int
; }
; }
    jmp     L353
L355:
L353:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
    mov     ax, 1
    jmp     L359
; {
; RPN'ized expression: "( L361 puts ) "
; Expanded expression: " L361  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L361:
    db  "never printed",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L361 , puts )2 "
    push    L361
    call    _puts
    sub     sp, -2
; case
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
    jmp     L360
L359:
    cmp     ax, 0
    jne     L363
L360:
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
    jmp     L357
; case
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
    jmp     L364
L363:
    cmp     ax, 1
    jne     L367
L364:
; RPN'ized expression: "( L369 puts ) "
; Expanded expression: " L369  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L369:
    db  "1",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L369 , puts )2 "
    push    L369
    call    _puts
    sub     sp, -2
; break
    jmp     L357
; case
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
    jmp     L368
L367:
    cmp     ax, 2
    jne     L371
L368:
; RPN'ized expression: "( L373 puts ) "
; Expanded expression: " L373  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L373:
    db  "2",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L373 , puts )2 "
    push    L373
    call    _puts
    sub     sp, -2
; break
    jmp     L357
; default
L358:
; RPN'ized expression: "( L375 puts ) "
; Expanded expression: " L375  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L375:
    db  "default",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L375 , puts )2 "
    push    L375
    call    _puts
    sub     sp, -2
; break
    jmp     L357
; }
    jmp     L357
L371:
    jmp     L358
L357:
; switch
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
; Fused expression:    "2 "
    mov     ax, 2
    jmp     L379
; {
; case
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
    jmp     L380
L379:
    cmp     ax, 2
    jne     L381
L380:
; RPN'ized expression: "( L383 puts ) "
; Expanded expression: " L383  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L383:
    db  "2",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L383 , puts )2 "
    push    L383
    call    _puts
    sub     sp, -2
; break
    jmp     L377
; }
    jmp     L377
L381:
L377:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
    mov     ax, 1
    jmp     L387
; {
; default
L386:
; RPN'ized expression: "( L389 puts ) "
; Expanded expression: " L389  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L389:
    db  "default",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L389 , puts )2 "
    push    L389
    call    _puts
    sub     sp, -2
; break
    jmp     L385
; }
    jmp     L385
L387:
    jmp     L386
L385:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
    mov     ax, 1
    jmp     L393
; {
; default
L392:
; RPN'ized expression: "( L395 puts ) "
; Expanded expression: " L395  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L395:
    db  "default",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L395 , puts )2 "
    push    L395
    call    _puts
    sub     sp, -2
; break
    jmp     L391
; case
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
    jmp     L394
L393:
    cmp     ax, 0
    jne     L397
L394:
; RPN'ized expression: "( L399 puts ) "
; Expanded expression: " L399  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L399:
    db  "0",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L399 , puts )2 "
    push    L399
    call    _puts
    sub     sp, -2
; break
    jmp     L391
; }
    jmp     L391
L397:
    jmp     L392
L391:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
    mov     ax, 1
    jmp     L403
; {
; case
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
    jmp     L404
L403:
    cmp     ax, 0
    jne     L405
L404:
; RPN'ized expression: "( L407 puts ) "
; Expanded expression: " L407  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L407:
    db  "0",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L407 , puts )2 "
    push    L407
    call    _puts
    sub     sp, -2
; break
    jmp     L401
; default
L402:
; RPN'ized expression: "( L409 puts ) "
; Expanded expression: " L409  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L409:
    db  "default",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L409 , puts )2 "
    push    L409
    call    _puts
    sub     sp, -2
; break
    jmp     L401
; }
    jmp     L401
L405:
    jmp     L402
L401:
; switch
; RPN'ized expression: "3 "
; Expanded expression: "3 "
; Expression value: 3
; Fused expression:    "3 "
    mov     ax, 3
    jmp     L413
; {
; case
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
    jmp     L414
L413:
    cmp     ax, 2
    jne     L415
L414:
; RPN'ized expression: "( L417 puts ) "
; Expanded expression: " L417  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L417:
    db  "2 & fallthru",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L417 , puts )2 "
    push    L417
    call    _puts
    sub     sp, -2
; case
; RPN'ized expression: "3 "
; Expanded expression: "3 "
; Expression value: 3
    jmp     L416
L415:
    cmp     ax, 3
    jne     L419
L416:
; RPN'ized expression: "( L421 puts ) "
; Expanded expression: " L421  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L421:
    db  "3 & fallthru",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L421 , puts )2 "
    push    L421
    call    _puts
    sub     sp, -2
; case
; RPN'ized expression: "4 "
; Expanded expression: "4 "
; Expression value: 4
    jmp     L420
L419:
    cmp     ax, 4
    jne     L423
L420:
; RPN'ized expression: "( L425 puts ) "
; Expanded expression: " L425  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L425:
    db  "4 & fallthru",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L425 , puts )2 "
    push    L425
    call    _puts
    sub     sp, -2
; default
L412:
; RPN'ized expression: "( L427 puts ) "
; Expanded expression: " L427  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L427:
    db  "default & fallthru",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L427 , puts )2 "
    push    L427
    call    _puts
    sub     sp, -2
; }
    jmp     L411
L423:
    jmp     L412
L411:
; switch
; RPN'ized expression: "5 "
; Expanded expression: "5 "
; Expression value: 5
; Fused expression:    "5 "
    mov     ax, 5
    jmp     L431
; {
; default
L430:
; RPN'ized expression: "( L433 puts ) "
; Expanded expression: " L433  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L433:
    db  "default & fallthru",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L433 , puts )2 "
    push    L433
    call    _puts
    sub     sp, -2
; case
; RPN'ized expression: "4 "
; Expanded expression: "4 "
; Expression value: 4
    jmp     L432
L431:
    cmp     ax, 4
    jne     L435
L432:
; RPN'ized expression: "( L437 puts ) "
; Expanded expression: " L437  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L437:
    db  "4 & fallthru",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L437 , puts )2 "
    push    L437
    call    _puts
    sub     sp, -2
; case
; RPN'ized expression: "3 "
; Expanded expression: "3 "
; Expression value: 3
    jmp     L436
L435:
    cmp     ax, 3
    jne     L439
L436:
; RPN'ized expression: "( L441 puts ) "
; Expanded expression: " L441  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L441:
    db  "3 & fallthru",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L441 , puts )2 "
    push    L441
    call    _puts
    sub     sp, -2
; case
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
    jmp     L440
L439:
    cmp     ax, 2
    jne     L443
L440:
; RPN'ized expression: "( L445 puts ) "
; Expanded expression: " L445  puts ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L445:
    db  "2 & fallthru",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L445 , puts )2 "
    push    L445
    call    _puts
    sub     sp, -2
; }
    jmp     L429
L443:
    jmp     L430
L429:
; loc     i : (@-2): int
; for
; RPN'ized expression: "i 1 = "
; Expanded expression: "(@-2) 1 =(2) "
; Fused expression:    "=(34) *(@-2) 1 "
    mov     ax, 1
    mov     [bp-2], ax
L447:
; RPN'ized expression: "i 5 <= "
; Expanded expression: "(@-2) *(2) 5 <= "
; Fused expression:    "<= *(@-2) 5 IF! "
    mov     ax, [bp-2]
    cmp     ax, 5
    jg      L450
    jmp     L449
L448:
; RPN'ized expression: "i ++p "
; Expanded expression: "(@-2) ++p(2) "
; Fused expression:    "++p(2) *(@-2) "
    mov     ax, [bp-2]
    inc     word [bp-2]
    jmp     L447
L449:
; switch
; RPN'ized expression: "i "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
    mov     ax, [bp-2]
    jmp     L453
; {
; case
; RPN'ized expression: "3 "
; Expanded expression: "3 "
; Expression value: 3
    jmp     L454
L453:
    cmp     ax, 3
    jne     L455
L454:
; continue
    jmp     L448
; default
L452:
; RPN'ized expression: "( i , L457 printf ) "
; Expanded expression: " (@-2) *(2)  L457  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L457:
    db  "%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-2) , L457 , printf )4 "
    push    word [bp-2]
    push    L457
    call    _printf
    sub     sp, -4
; break
    jmp     L451
; }
    jmp     L451
L455:
    jmp     L452
L451:
    jmp     L448
L450:
; return
    jmp     L336
L336:
    leave
    ret
L335:
    sub     sp, 2
    jmp     L334
; SEGMENT _TEXT

; Syntax/declaration table/stack:
; Bytes used: 788/8192


; Macro table:
; Macro __SMALLER_C__ = `0x0100`
; Macro __SMALLER_C_16__ = ``
; Macro __SMALLER_C_SCHAR__ = ``
; Macro SOMETHING = `42`
; Macro NOTHING = ``
; Macro SOMETHING_2 = `"42"`
; Bytes used: 105/4096


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
; Ident vprintf
; Ident fmt
; Ident vl
; Ident printf
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
; Bytes used: 240/4096

