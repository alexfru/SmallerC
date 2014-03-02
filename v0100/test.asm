bits 16

org 0x100
; glb main : (void) int
; glb start : (void) void
_start:
	push	bp
	mov	bp, sp
	jmp	L2
L1:
; RPN'ized expression: "( main ) "
; Expanded expression: " main ()0 "
; Fused expression:    "( main )0 "
	call	_main
L3:
	leave
	ret
L2:
	jmp	L1
; glb dosputch : (
; prm     c : int
;     ) void
_dosputch:
	push	bp
	mov	bp, sp
	jmp	L5
L4:
; loc     c : (@4): int
mov ah, 2
mov dl, [bp + 4]
int 0x21
L6:
	leave
	ret
L5:
	jmp	L4
; glb dosgetch : (void) int
_dosgetch:
	push	bp
	mov	bp, sp
	jmp	L8
L7:
mov ah, 1
int 0x21
mov ah, 0
L9:
	leave
	ret
L8:
	jmp	L7
; glb putchar : (
; prm     c : int
;     ) int
_putchar:
	push	bp
	mov	bp, sp
	jmp	L11
L10:
; loc     c : (@4): int
; if
; RPN'ized expression: "c 10 == "
; Expanded expression: "(@4) *(2) 10 == "
; Fused expression:    "== *(@4) 10 IF! "
	mov	ax, [bp+4]
	cmp	ax, 10
	jne	L13
; RPN'ized expression: "( 13 dosputch ) "
; Expanded expression: " 13  dosputch ()2 "
; Fused expression:    "( 13 , dosputch )2 "
	push	13
	call	_dosputch
	sub	sp, -2
L13:
; RPN'ized expression: "( c dosputch ) "
; Expanded expression: " (@4) *(2)  dosputch ()2 "
; Fused expression:    "( *(2) (@4) , dosputch )2 "
	push	word [bp+4]
	call	_dosputch
	sub	sp, -2
L12:
	leave
	ret
L11:
	jmp	L10
; glb getchar : (void) int
_getchar:
	push	bp
	mov	bp, sp
	jmp	L16
L15:
; loc     c : (@-2): int
; =
; RPN'ized expression: "( dosgetch ) "
; Expanded expression: " dosgetch ()0 "
; Fused expression:    "( dosgetch )0 =(170) *(@-2) ax "
	call	_dosgetch
	mov	[bp-2], ax
; if
; RPN'ized expression: "c 13 == "
; Expanded expression: "(@-2) *(2) 13 == "
; Fused expression:    "== *(@-2) 13 IF! "
	mov	ax, [bp-2]
	cmp	ax, 13
	jne	L18
; RPN'ized expression: "c 10 = "
; Expanded expression: "(@-2) 10 =(2) "
; Fused expression:    "=(170) *(@-2) 10 "
	mov	ax, 10
	mov	[bp-2], ax
L18:
; return
; RPN'ized expression: "c "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
	mov	ax, [bp-2]
	jmp	L17
L17:
	leave
	ret
L16:
	sub	sp, 2
	jmp	L15
; glb gfxmode : (
; prm     mode : int
;     ) void
_gfxmode:
	push	bp
	mov	bp, sp
	jmp	L21
L20:
; loc     mode : (@4): int
mov ah, 0
mov al, [bp + 4]
int 0x10
L22:
	leave
	ret
L21:
	jmp	L20
; glb pokeb : (
; prm     seg : unsigned
; prm     ofs : unsigned
; prm     val : unsigned char
;     ) void
_pokeb:
	push	bp
	mov	bp, sp
	jmp	L24
L23:
; loc     seg : (@4): unsigned
; loc     ofs : (@6): unsigned
; loc     val : (@8): unsigned char
push ds
mov  ds, [bp + 4]
mov  bx, [bp + 6]
mov  al, [bp + 8]
mov  [bx], al
pop  ds
L25:
	leave
	ret
L24:
	jmp	L23
; glb poke : (
; prm     seg : unsigned
; prm     ofs : unsigned
; prm     val : unsigned
;     ) void
_poke:
	push	bp
	mov	bp, sp
	jmp	L27
L26:
; loc     seg : (@4): unsigned
; loc     ofs : (@6): unsigned
; loc     val : (@8): unsigned
push ds
mov  ds, [bp + 4]
mov  bx, [bp + 6]
mov  ax, [bp + 8]
mov  [bx], ax
pop  ds
L28:
	leave
	ret
L27:
	jmp	L26
; glb peekb : (
; prm     seg : unsigned
; prm     ofs : unsigned
;     ) unsigned char
_peekb:
	push	bp
	mov	bp, sp
	jmp	L30
L29:
; loc     seg : (@4): unsigned
; loc     ofs : (@6): unsigned
push ds
mov  ds, [bp + 4]
mov  bx, [bp + 6]
mov  al, [bx]
mov  ah, 0
pop  ds
L31:
	leave
	ret
L30:
	jmp	L29
; glb peek : (
; prm     seg : unsigned
; prm     ofs : unsigned
;     ) unsigned
_peek:
	push	bp
	mov	bp, sp
	jmp	L33
L32:
; loc     seg : (@4): unsigned
; loc     ofs : (@6): unsigned
push ds
mov  ds, [bp + 4]
mov  bx, [bp + 6]
mov  ax, [bx]
pop  ds
L34:
	leave
	ret
L33:
	jmp	L32
; glb strcpy : (
; prm     s1 : * char
; prm     s2 : * char
;     ) * char
_strcpy:
	push	bp
	mov	bp, sp
	jmp	L36
L35:
; loc     s1 : (@4): * char
; loc     s2 : (@6): * char
; loc     tmp : (@-2): * char
; =
; RPN'ized expression: "s1 "
; Expanded expression: "(@4) *(2) "
; Fused expression:    "=(170) *(@-2) *(@4) "
	mov	ax, [bp+4]
	mov	[bp-2], ax
; while
; RPN'ized expression: "s1 ++p *u s2 ++p *u = "
; Expanded expression: "(@4) ++p(2) (@6) ++p(2) *(-1) =(-1) "
L38:
; Fused expression:    "++p(2) *(@4) push-ax ++p(2) *(@6) =(119) **sp *ax "
	mov	ax, [bp+4]
	inc	word [bp+4]
	push	ax
	mov	ax, [bp+6]
	inc	word [bp+6]
	mov	bx, ax
	mov	al, [bx]
	cbw
	pop	bx
	mov	[bx], al
	cbw
; JumpIfZero
	test	ax, ax
	je	L39
	jmp	L38
L39:
; return
; RPN'ized expression: "tmp "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
	mov	ax, [bp-2]
	jmp	L37
L37:
	leave
	ret
L36:
	sub	sp, 2
	jmp	L35
; glb strlen : (
; prm     s : * char
;     ) unsigned
_strlen:
	push	bp
	mov	bp, sp
	jmp	L41
L40:
; loc     s : (@4): * char
; loc     l : (@-2): unsigned
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "=(170) *(@-2) 0 "
	mov	ax, 0
	mov	[bp-2], ax
; while
; RPN'ized expression: "s ++p *u "
; Expanded expression: "(@4) ++p(2) *(-1) "
L43:
; Fused expression:    "++p(2) *(@4) *(-1) ax "
	mov	ax, [bp+4]
	inc	word [bp+4]
	mov	bx, ax
	mov	al, [bx]
	cbw
; JumpIfZero
	test	ax, ax
	je	L44
; RPN'ized expression: "l ++ "
; Expanded expression: "(@-2) ++(2) "
; Fused expression:    "++(2) *(@-2) "
	inc	word [bp-2]
	mov	ax, [bp-2]
	jmp	L43
L44:
; return
; RPN'ized expression: "l "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
	mov	ax, [bp-2]
	jmp	L42
L42:
	leave
	ret
L41:
	sub	sp, 2
	jmp	L40
; glb strchr : (
; prm     s : * char
; prm     c : int
;     ) * char
_strchr:
	push	bp
	mov	bp, sp
	jmp	L46
L45:
; loc     s : (@4): * char
; loc     c : (@6): int
; do
L48:
; {
; if
; RPN'ized expression: "s *u c == "
; Expanded expression: "(@4) *(2) *(-1) (@6) *(2) == "
; Fused expression:    "*(2) (@4) == *ax *(@6) IF! "
	mov	ax, [bp+4]
	mov	bx, ax
	mov	al, [bx]
	cbw
	cmp	ax, [bp+6]
	jne	L51
; return
; RPN'ized expression: "s "
; Expanded expression: "(@4) *(2) "
; Fused expression:    "*(2) (@4) "
	mov	ax, [bp+4]
	jmp	L47
L51:
; }
; while
; RPN'ized expression: "s ++p *u 0 != "
; Expanded expression: "(@4) ++p(2) *(-1) 0 != "
L49:
; Fused expression:    "++p(2) *(@4) != *ax 0 IF "
	mov	ax, [bp+4]
	inc	word [bp+4]
	mov	bx, ax
	mov	al, [bx]
	cbw
	cmp	ax, 0
	jne	L48
L50:
; return
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "0 "
	mov	ax, 0
	jmp	L47
L47:
	leave
	ret
L46:
	jmp	L45
; glb puts : (
; prm     s : * char
;     ) int
_puts:
	push	bp
	mov	bp, sp
	jmp	L54
L53:
; loc     s : (@4): * char
; while
; RPN'ized expression: "s *u "
; Expanded expression: "(@4) *(2) *(-1) "
L56:
; Fused expression:    "*(2) (@4) *(-1) ax "
	mov	ax, [bp+4]
	mov	bx, ax
	mov	al, [bx]
	cbw
; JumpIfZero
	test	ax, ax
	je	L57
; RPN'ized expression: "( s ++p *u putchar ) "
; Expanded expression: " (@4) ++p(2) *(-1)  putchar ()2 "
; Fused expression:    "( ++p(2) *(@4) *(-1) ax , putchar )2 "
	mov	ax, [bp+4]
	inc	word [bp+4]
	mov	bx, ax
	mov	al, [bx]
	cbw
	push	ax
	call	_putchar
	sub	sp, -2
	jmp	L56
L57:
; RPN'ized expression: "( 10 putchar ) "
; Expanded expression: " 10  putchar ()2 "
; Fused expression:    "( 10 , putchar )2 "
	push	10
	call	_putchar
	sub	sp, -2
; return
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "0 "
	mov	ax, 0
	jmp	L55
L55:
	leave
	ret
L54:
	jmp	L53
; glb isspace : (
; prm     c : int
;     ) int
_isspace:
	push	bp
	mov	bp, sp
	jmp	L59
L58:
; loc     c : (@4): int
; return
; RPN'ized expression: "c 32 == c 12 == || c 10 == || c 13 == || c 9 == || c 11 == || "
; Expanded expression: "(@4) *(2) 32 == [sh||->65] (@4) *(2) 12 == ||[65] _Bool [sh||->64] (@4) *(2) 10 == ||[64] _Bool [sh||->63] (@4) *(2) 13 == ||[63] _Bool [sh||->62] (@4) *(2) 9 == ||[62] _Bool [sh||->61] (@4) *(2) 11 == ||[61] "
; Fused expression:    "== *(@4) 32 [sh||->65] == *(@4) 12 ||[65] _Bool [sh||->64] == *(@4) 10 ||[64] _Bool [sh||->63] == *(@4) 13 ||[63] _Bool [sh||->62] == *(@4) 9 ||[62] _Bool [sh||->61] == *(@4) 11 ||[61] "
	mov	ax, [bp+4]
	cmp	ax, 32
	sete	al
	cbw
; JumpIfNotZero
	test	ax, ax
	jne	L65
	mov	ax, [bp+4]
	cmp	ax, 12
	sete	al
	cbw
L65:
	test	ax, ax
	setne	al
	cbw
; JumpIfNotZero
	test	ax, ax
	jne	L64
	mov	ax, [bp+4]
	cmp	ax, 10
	sete	al
	cbw
L64:
	test	ax, ax
	setne	al
	cbw
; JumpIfNotZero
	test	ax, ax
	jne	L63
	mov	ax, [bp+4]
	cmp	ax, 13
	sete	al
	cbw
L63:
	test	ax, ax
	setne	al
	cbw
; JumpIfNotZero
	test	ax, ax
	jne	L62
	mov	ax, [bp+4]
	cmp	ax, 9
	sete	al
	cbw
L62:
	test	ax, ax
	setne	al
	cbw
; JumpIfNotZero
	test	ax, ax
	jne	L61
	mov	ax, [bp+4]
	cmp	ax, 11
	sete	al
	cbw
L61:
	jmp	L60
L60:
	leave
	ret
L59:
	jmp	L58
; glb isdigit : (
; prm     c : int
;     ) int
_isdigit:
	push	bp
	mov	bp, sp
	jmp	L67
L66:
; loc     c : (@4): int
; return
; RPN'ized expression: "c 48 >= c 57 <= && "
; Expanded expression: "(@4) *(2) 48 >= [sh&&->69] (@4) *(2) 57 <= &&[69] "
; Fused expression:    ">= *(@4) 48 [sh&&->69] <= *(@4) 57 &&[69] "
	mov	ax, [bp+4]
	cmp	ax, 48
	setge	al
	cbw
; JumpIfZero
	test	ax, ax
	je	L69
	mov	ax, [bp+4]
	cmp	ax, 57
	setle	al
	cbw
L69:
	jmp	L68
L68:
	leave
	ret
L67:
	jmp	L66
; glb vprintf : (
; prm     fmt : * char
; prm     vl : * void
;     ) int
_vprintf:
	push	bp
	mov	bp, sp
	jmp	L71
L70:
; loc     fmt : (@4): * char
; loc     vl : (@6): * void
; loc     pp : (@-2): * int
; =
; RPN'ized expression: "vl "
; Expanded expression: "(@6) *(2) "
; Fused expression:    "=(170) *(@-2) *(@6) "
	mov	ax, [bp+6]
	mov	[bp-2], ax
; loc     cnt : (@-4): int
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "=(170) *(@-4) 0 "
	mov	ax, 0
	mov	[bp-4], ax
; loc     p : (@-6): * char
; loc     phex : (@-8): * char
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
; Fused expression:    "=(170) *(@-30) 0 "
	mov	ax, 0
	mov	[bp-30], ax
; loc     len : (@-32): int
; for
; RPN'ized expression: "p fmt = "
; Expanded expression: "(@-6) (@4) *(2) =(2) "
; Fused expression:    "=(170) *(@-6) *(@4) "
	mov	ax, [bp+4]
	mov	[bp-6], ax
L73:
; RPN'ized expression: "p *u 0 != "
; Expanded expression: "(@-6) *(2) *(-1) 0 != "
; Fused expression:    "*(2) (@-6) != *ax 0 IF! "
	mov	ax, [bp-6]
	mov	bx, ax
	mov	al, [bx]
	cbw
	cmp	ax, 0
	je	L76
	jmp	L75
L74:
; RPN'ized expression: "p ++p "
; Expanded expression: "(@-6) ++p(2) "
; Fused expression:    "++p(2) *(@-6) "
	mov	ax, [bp-6]
	inc	word [bp-6]
	jmp	L73
L75:
; {
; if
; RPN'ized expression: "p *u 37 != p 1 + *u 37 == || "
; Expanded expression: "(@-6) *(2) *(-1) 37 != [sh||->79] (@-6) *(2) 1 + *(-1) 37 == ||[79] "
; Fused expression:    "*(2) (@-6) != *ax 37 [sh||->79] + *(@-6) 1 == *ax 37 ||[79] "
	mov	ax, [bp-6]
	mov	bx, ax
	mov	al, [bx]
	cbw
	cmp	ax, 37
	setne	al
	cbw
; JumpIfNotZero
	test	ax, ax
	jne	L79
	mov	ax, [bp-6]
	inc	ax
	mov	bx, ax
	mov	al, [bx]
	cbw
	cmp	ax, 37
	sete	al
	cbw
L79:
; JumpIfZero
	test	ax, ax
	je	L77
; {
; RPN'ized expression: "( p *u putchar ) "
; Expanded expression: " (@-6) *(2) *(-1)  putchar ()2 "
; Fused expression:    "( *(2) (@-6) *(-1) ax , putchar )2 "
	mov	ax, [bp-6]
	mov	bx, ax
	mov	al, [bx]
	cbw
	push	ax
	call	_putchar
	sub	sp, -2
; RPN'ized expression: "p p p *u 37 == + = "
; Expanded expression: "(@-6) (@-6) *(2) (@-6) *(2) *(-1) 37 == + =(2) "
; Fused expression:    "*(2) (@-6) == *ax 37 + *(@-6) ax =(170) *(@-6) ax "
	mov	ax, [bp-6]
	mov	bx, ax
	mov	al, [bx]
	cbw
	cmp	ax, 37
	sete	al
	cbw
	mov	cx, ax
	mov	ax, [bp-6]
	add	ax, cx
	mov	[bp-6], ax
; RPN'ized expression: "cnt ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
	mov	ax, [bp-4]
	inc	word [bp-4]
; continue
	jmp	L74
; }
L77:
; RPN'ized expression: "p ++p "
; Expanded expression: "(@-6) ++p(2) "
; Fused expression:    "++p(2) *(@-6) "
	mov	ax, [bp-6]
	inc	word [bp-6]
; RPN'ized expression: "minlen 0 = "
; Expanded expression: "(@-30) 0 =(2) "
; Fused expression:    "=(170) *(@-30) 0 "
	mov	ax, 0
	mov	[bp-30], ax
; RPN'ized expression: "msign 0 = "
; Expanded expression: "(@-28) 0 =(2) "
; Fused expression:    "=(170) *(@-28) 0 "
	mov	ax, 0
	mov	[bp-28], ax
; if
; RPN'ized expression: "p *u 43 == "
; Expanded expression: "(@-6) *(2) *(-1) 43 == "
; Fused expression:    "*(2) (@-6) == *ax 43 IF! "
	mov	ax, [bp-6]
	mov	bx, ax
	mov	al, [bx]
	cbw
	cmp	ax, 43
	jne	L80
; {
; RPN'ized expression: "msign 1 = "
; Expanded expression: "(@-28) 1 =(2) "
; Fused expression:    "=(170) *(@-28) 1 "
	mov	ax, 1
	mov	[bp-28], ax
; RPN'ized expression: "p ++p "
; Expanded expression: "(@-6) ++p(2) "
; Fused expression:    "++p(2) *(@-6) "
	mov	ax, [bp-6]
	inc	word [bp-6]
; }
	jmp	L81
L80:
; else
; if
; RPN'ized expression: "p *u 45 == "
; Expanded expression: "(@-6) *(2) *(-1) 45 == "
; Fused expression:    "*(2) (@-6) == *ax 45 IF! "
	mov	ax, [bp-6]
	mov	bx, ax
	mov	al, [bx]
	cbw
	cmp	ax, 45
	jne	L82
; {
; RPN'ized expression: "msign 1 -u = "
; Expanded expression: "(@-28) -1 =(2) "
; Fused expression:    "=(170) *(@-28) -1 "
	mov	ax, -1
	mov	[bp-28], ax
; RPN'ized expression: "p ++p "
; Expanded expression: "(@-6) ++p(2) "
; Fused expression:    "++p(2) *(@-6) "
	mov	ax, [bp-6]
	inc	word [bp-6]
; }
L82:
L81:
; if
; RPN'ized expression: "( p *u isdigit ) "
; Expanded expression: " (@-6) *(2) *(-1)  isdigit ()2 "
; Fused expression:    "( *(2) (@-6) *(-1) ax , isdigit )2 "
	mov	ax, [bp-6]
	mov	bx, ax
	mov	al, [bx]
	cbw
	push	ax
	call	_isdigit
	sub	sp, -2
; JumpIfZero
	test	ax, ax
	je	L84
; {
; while
; RPN'ized expression: "( p *u isdigit ) "
; Expanded expression: " (@-6) *(2) *(-1)  isdigit ()2 "
L86:
; Fused expression:    "( *(2) (@-6) *(-1) ax , isdigit )2 "
	mov	ax, [bp-6]
	mov	bx, ax
	mov	al, [bx]
	cbw
	push	ax
	call	_isdigit
	sub	sp, -2
; JumpIfZero
	test	ax, ax
	je	L87
; RPN'ized expression: "minlen minlen 10 * p ++p *u + 48 - = "
; Expanded expression: "(@-30) (@-30) *(2) 10 * (@-6) ++p(2) *(-1) + 48 - =(2) "
; Fused expression:    "* *(@-30) 10 push-ax ++p(2) *(@-6) + *sp *ax - ax 48 =(170) *(@-30) ax "
	mov	ax, [bp-30]
	imul	ax, ax, 10
	push	ax
	mov	ax, [bp-6]
	inc	word [bp-6]
	mov	bx, ax
	movsx	cx, byte [bx]
	pop	ax
	add	ax, cx
	sub	ax, 48
	mov	[bp-30], ax
	jmp	L86
L87:
; if
; RPN'ized expression: "msign 0 < "
; Expanded expression: "(@-28) *(2) 0 < "
; Fused expression:    "< *(@-28) 0 IF! "
	mov	ax, [bp-28]
	cmp	ax, 0
	jge	L88
; RPN'ized expression: "minlen minlen -u = "
; Expanded expression: "(@-30) (@-30) *(2) -u =(2) "
; Fused expression:    "*(2) (@-30) -u =(170) *(@-30) ax "
	mov	ax, [bp-30]
	neg	ax
	mov	[bp-30], ax
L88:
; RPN'ized expression: "msign 0 = "
; Expanded expression: "(@-28) 0 =(2) "
; Fused expression:    "=(170) *(@-28) 0 "
	mov	ax, 0
	mov	[bp-28], ax
; }
L84:
; if
; RPN'ized expression: "msign 0 == "
; Expanded expression: "(@-28) *(2) 0 == "
; Fused expression:    "== *(@-28) 0 IF! "
	mov	ax, [bp-28]
	cmp	ax, 0
	jne	L90
; {
; if
; RPN'ized expression: "p *u 43 == "
; Expanded expression: "(@-6) *(2) *(-1) 43 == "
; Fused expression:    "*(2) (@-6) == *ax 43 IF! "
	mov	ax, [bp-6]
	mov	bx, ax
	mov	al, [bx]
	cbw
	cmp	ax, 43
	jne	L92
; {
; RPN'ized expression: "msign 1 = "
; Expanded expression: "(@-28) 1 =(2) "
; Fused expression:    "=(170) *(@-28) 1 "
	mov	ax, 1
	mov	[bp-28], ax
; RPN'ized expression: "p ++p "
; Expanded expression: "(@-6) ++p(2) "
; Fused expression:    "++p(2) *(@-6) "
	mov	ax, [bp-6]
	inc	word [bp-6]
; }
	jmp	L93
L92:
; else
; if
; RPN'ized expression: "p *u 45 == "
; Expanded expression: "(@-6) *(2) *(-1) 45 == "
; Fused expression:    "*(2) (@-6) == *ax 45 IF! "
	mov	ax, [bp-6]
	mov	bx, ax
	mov	al, [bx]
	cbw
	cmp	ax, 45
	jne	L94
; {
; RPN'ized expression: "msign 1 -u = "
; Expanded expression: "(@-28) -1 =(2) "
; Fused expression:    "=(170) *(@-28) -1 "
	mov	ax, -1
	mov	[bp-28], ax
; RPN'ized expression: "p ++p "
; Expanded expression: "(@-6) ++p(2) "
; Fused expression:    "++p(2) *(@-6) "
	mov	ax, [bp-6]
	inc	word [bp-6]
; }
L94:
L93:
; }
L90:
; RPN'ized expression: "phex L96 = "
; Expanded expression: "(@-8) L96 =(2) "
	jmp	L97
L96:
	db	"0123456789abcdef",0
L97:
; Fused expression:    "=(170) *(@-8) L96 "
	mov	ax, L96
	mov	[bp-8], ax
; switch
; RPN'ized expression: "p *u "
; Expanded expression: "(@-6) *(2) *(-1) "
; Fused expression:    "*(2) (@-6) *(-1) ax "
	mov	ax, [bp-6]
	mov	bx, ax
	mov	al, [bx]
	cbw
	jmp	L100
; {
; case
; RPN'ized expression: "99 "
; Expanded expression: "99 "
; Expression value: 99
	jmp	L101
L100:
	cmp	ax, 99
	jne	L102
L101:
; while
; RPN'ized expression: "minlen 1 > "
; Expanded expression: "(@-30) *(2) 1 > "
L104:
; Fused expression:    "> *(@-30) 1 IF! "
	mov	ax, [bp-30]
	cmp	ax, 1
	jle	L105
; {
; RPN'ized expression: "( 32 putchar ) "
; Expanded expression: " 32  putchar ()2 "
; Fused expression:    "( 32 , putchar )2 "
	push	32
	call	_putchar
	sub	sp, -2
; RPN'ized expression: "cnt ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
	mov	ax, [bp-4]
	inc	word [bp-4]
; RPN'ized expression: "minlen --p "
; Expanded expression: "(@-30) --p(2) "
; Fused expression:    "--p(2) *(@-30) "
	mov	ax, [bp-30]
	dec	word [bp-30]
; }
	jmp	L104
L105:
; RPN'ized expression: "( pp ++p *u putchar ) "
; Expanded expression: " (@-2) 2 +=p(2) *(2)  putchar ()2 "
; Fused expression:    "( +=p(2) *(@-2) 2 *(2) ax , putchar )2 "
	mov	ax, [bp-2]
	add	word [bp-2], 2
	mov	bx, ax
	push	word [bx]
	call	_putchar
	sub	sp, -2
; while
; RPN'ized expression: "minlen -u 1 > "
; Expanded expression: "(@-30) *(2) -u 1 > "
L106:
; Fused expression:    "*(2) (@-30) -u > ax 1 IF! "
	mov	ax, [bp-30]
	neg	ax
	cmp	ax, 1
	jle	L107
; {
; RPN'ized expression: "( 32 putchar ) "
; Expanded expression: " 32  putchar ()2 "
; Fused expression:    "( 32 , putchar )2 "
	push	32
	call	_putchar
	sub	sp, -2
; RPN'ized expression: "cnt ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
	mov	ax, [bp-4]
	inc	word [bp-4]
; RPN'ized expression: "minlen ++p "
; Expanded expression: "(@-30) ++p(2) "
; Fused expression:    "++p(2) *(@-30) "
	mov	ax, [bp-30]
	inc	word [bp-30]
; }
	jmp	L106
L107:
; RPN'ized expression: "cnt ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
	mov	ax, [bp-4]
	inc	word [bp-4]
; break
	jmp	L98
; case
; RPN'ized expression: "115 "
; Expanded expression: "115 "
; Expression value: 115
	jmp	L103
L102:
	cmp	ax, 115
	jne	L108
L103:
; RPN'ized expression: "pc pp ++p *u = "
; Expanded expression: "(@-22) (@-2) 2 +=p(2) *(2) =(2) "
; Fused expression:    "+=p(2) *(@-2) 2 =(170) *(@-22) *ax "
	mov	ax, [bp-2]
	add	word [bp-2], 2
	mov	bx, ax
	mov	ax, [bx]
	mov	[bp-22], ax
; RPN'ized expression: "len 0 = "
; Expanded expression: "(@-32) 0 =(2) "
; Fused expression:    "=(170) *(@-32) 0 "
	mov	ax, 0
	mov	[bp-32], ax
; if
; RPN'ized expression: "pc "
; Expanded expression: "(@-22) *(2) "
; Fused expression:    "*(2) (@-22) "
	mov	ax, [bp-22]
; JumpIfZero
	test	ax, ax
	je	L110
; RPN'ized expression: "len ( pc strlen ) = "
; Expanded expression: "(@-32)  (@-22) *(2)  strlen ()2 =(2) "
; Fused expression:    "( *(2) (@-22) , strlen )2 =(170) *(@-32) ax "
	push	word [bp-22]
	call	_strlen
	sub	sp, -2
	mov	[bp-32], ax
L110:
; while
; RPN'ized expression: "minlen len > "
; Expanded expression: "(@-30) *(2) (@-32) *(2) > "
L112:
; Fused expression:    "> *(@-30) *(@-32) IF! "
	mov	ax, [bp-30]
	cmp	ax, [bp-32]
	jle	L113
; {
; RPN'ized expression: "( 32 putchar ) "
; Expanded expression: " 32  putchar ()2 "
; Fused expression:    "( 32 , putchar )2 "
	push	32
	call	_putchar
	sub	sp, -2
; RPN'ized expression: "cnt ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
	mov	ax, [bp-4]
	inc	word [bp-4]
; RPN'ized expression: "minlen --p "
; Expanded expression: "(@-30) --p(2) "
; Fused expression:    "--p(2) *(@-30) "
	mov	ax, [bp-30]
	dec	word [bp-30]
; }
	jmp	L112
L113:
; if
; RPN'ized expression: "len "
; Expanded expression: "(@-32) *(2) "
; Fused expression:    "*(2) (@-32) "
	mov	ax, [bp-32]
; JumpIfZero
	test	ax, ax
	je	L114
; while
; RPN'ized expression: "pc *u 0 != "
; Expanded expression: "(@-22) *(2) *(-1) 0 != "
L116:
; Fused expression:    "*(2) (@-22) != *ax 0 IF! "
	mov	ax, [bp-22]
	mov	bx, ax
	mov	al, [bx]
	cbw
	cmp	ax, 0
	je	L117
; {
; RPN'ized expression: "( pc ++p *u putchar ) "
; Expanded expression: " (@-22) ++p(2) *(-1)  putchar ()2 "
; Fused expression:    "( ++p(2) *(@-22) *(-1) ax , putchar )2 "
	mov	ax, [bp-22]
	inc	word [bp-22]
	mov	bx, ax
	mov	al, [bx]
	cbw
	push	ax
	call	_putchar
	sub	sp, -2
; RPN'ized expression: "cnt ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
	mov	ax, [bp-4]
	inc	word [bp-4]
; }
	jmp	L116
L117:
L114:
; while
; RPN'ized expression: "minlen -u len > "
; Expanded expression: "(@-30) *(2) -u (@-32) *(2) > "
L118:
; Fused expression:    "*(2) (@-30) -u > ax *(@-32) IF! "
	mov	ax, [bp-30]
	neg	ax
	cmp	ax, [bp-32]
	jle	L119
; {
; RPN'ized expression: "( 32 putchar ) "
; Expanded expression: " 32  putchar ()2 "
; Fused expression:    "( 32 , putchar )2 "
	push	32
	call	_putchar
	sub	sp, -2
; RPN'ized expression: "cnt ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
	mov	ax, [bp-4]
	inc	word [bp-4]
; RPN'ized expression: "minlen ++p "
; Expanded expression: "(@-30) ++p(2) "
; Fused expression:    "++p(2) *(@-30) "
	mov	ax, [bp-30]
	inc	word [bp-30]
; }
	jmp	L118
L119:
; break
	jmp	L98
; case
; RPN'ized expression: "105 "
; Expanded expression: "105 "
; Expression value: 105
	jmp	L109
L108:
	cmp	ax, 105
	jne	L120
L109:
; case
; RPN'ized expression: "100 "
; Expanded expression: "100 "
; Expression value: 100
	jmp	L121
L120:
	cmp	ax, 100
	jne	L122
L121:
; RPN'ized expression: "pc s s sizeof 1 - + *u &u = "
; Expanded expression: "(@-22) (@-9) =(2) "
; Fused expression:    "=(170) *(@-22) (@-9) "
	lea	ax, [bp-9]
	mov	[bp-22], ax
; RPN'ized expression: "pc *u 0 = "
; Expanded expression: "(@-22) *(2) 0 =(-1) "
; Fused expression:    "*(2) (@-22) =(122) *ax 0 "
	mov	ax, [bp-22]
	mov	bx, ax
	mov	ax, 0
	mov	[bx], al
	cbw
; RPN'ized expression: "len 0 = "
; Expanded expression: "(@-32) 0 =(2) "
; Fused expression:    "=(170) *(@-32) 0 "
	mov	ax, 0
	mov	[bp-32], ax
; RPN'ized expression: "n pp ++p *u = "
; Expanded expression: "(@-24) (@-2) 2 +=p(2) *(2) =(2) "
; Fused expression:    "+=p(2) *(@-2) 2 =(170) *(@-24) *ax "
	mov	ax, [bp-2]
	add	word [bp-2], 2
	mov	bx, ax
	mov	ax, [bx]
	mov	[bp-24], ax
; RPN'ized expression: "sign 1 2 n 0 < * - = "
; Expanded expression: "(@-26) 1 2 (@-24) *(2) 0 < * - =(2) "
; Fused expression:    "< *(@-24) 0 * 2 ax - 1 ax =(170) *(@-26) ax "
	mov	ax, [bp-24]
	cmp	ax, 0
	setl	al
	cbw
	mov	cx, ax
	mov	ax, 2
	mul	cx
	mov	cx, ax
	mov	ax, 1
	sub	ax, cx
	mov	[bp-26], ax
; do
L124:
; {
; RPN'ized expression: "pc -- *u 48 n n 10 / 10 * - sign * + = "
; Expanded expression: "(@-22) --(2) 48 (@-24) *(2) (@-24) *(2) 10 / 10 * - (@-26) *(2) * + =(-1) "
; Fused expression:    "--(2) *(@-22) push-ax / *(@-24) 10 * ax 10 - *(@-24) ax * ax *(@-26) + 48 ax =(122) **sp ax "
	dec	word [bp-22]
	mov	ax, [bp-22]
	push	ax
	mov	ax, [bp-24]
	cwd
	mov	cx, 10
	idiv	cx
	imul	ax, ax, 10
	mov	cx, ax
	mov	ax, [bp-24]
	sub	ax, cx
	mul	word [bp-26]
	mov	cx, ax
	mov	ax, 48
	add	ax, cx
	pop	bx
	mov	[bx], al
	cbw
; RPN'ized expression: "n n 10 / = "
; Expanded expression: "(@-24) (@-24) *(2) 10 / =(2) "
; Fused expression:    "/ *(@-24) 10 =(170) *(@-24) ax "
	mov	ax, [bp-24]
	cwd
	mov	cx, 10
	idiv	cx
	mov	[bp-24], ax
; RPN'ized expression: "len ++p "
; Expanded expression: "(@-32) ++p(2) "
; Fused expression:    "++p(2) *(@-32) "
	mov	ax, [bp-32]
	inc	word [bp-32]
; }
; while
; RPN'ized expression: "n "
; Expanded expression: "(@-24) *(2) "
L125:
; Fused expression:    "*(2) (@-24) "
	mov	ax, [bp-24]
; JumpIfNotZero
	test	ax, ax
	jne	L124
L126:
; if
; RPN'ized expression: "sign 0 < "
; Expanded expression: "(@-26) *(2) 0 < "
; Fused expression:    "< *(@-26) 0 IF! "
	mov	ax, [bp-26]
	cmp	ax, 0
	jge	L127
; {
; RPN'ized expression: "pc -- *u 45 = "
; Expanded expression: "(@-22) --(2) 45 =(-1) "
; Fused expression:    "--(2) *(@-22) =(122) *ax 45 "
	dec	word [bp-22]
	mov	ax, [bp-22]
	mov	bx, ax
	mov	ax, 45
	mov	[bx], al
	cbw
; RPN'ized expression: "len ++p "
; Expanded expression: "(@-32) ++p(2) "
; Fused expression:    "++p(2) *(@-32) "
	mov	ax, [bp-32]
	inc	word [bp-32]
; }
	jmp	L128
L127:
; else
; if
; RPN'ized expression: "msign 0 > "
; Expanded expression: "(@-28) *(2) 0 > "
; Fused expression:    "> *(@-28) 0 IF! "
	mov	ax, [bp-28]
	cmp	ax, 0
	jle	L129
; {
; RPN'ized expression: "pc -- *u 43 = "
; Expanded expression: "(@-22) --(2) 43 =(-1) "
; Fused expression:    "--(2) *(@-22) =(122) *ax 43 "
	dec	word [bp-22]
	mov	ax, [bp-22]
	mov	bx, ax
	mov	ax, 43
	mov	[bx], al
	cbw
; RPN'ized expression: "len ++p "
; Expanded expression: "(@-32) ++p(2) "
; Fused expression:    "++p(2) *(@-32) "
	mov	ax, [bp-32]
	inc	word [bp-32]
; RPN'ized expression: "msign 0 = "
; Expanded expression: "(@-28) 0 =(2) "
; Fused expression:    "=(170) *(@-28) 0 "
	mov	ax, 0
	mov	[bp-28], ax
; }
L129:
L128:
; while
; RPN'ized expression: "minlen len > "
; Expanded expression: "(@-30) *(2) (@-32) *(2) > "
L131:
; Fused expression:    "> *(@-30) *(@-32) IF! "
	mov	ax, [bp-30]
	cmp	ax, [bp-32]
	jle	L132
; {
; RPN'ized expression: "( 32 putchar ) "
; Expanded expression: " 32  putchar ()2 "
; Fused expression:    "( 32 , putchar )2 "
	push	32
	call	_putchar
	sub	sp, -2
; RPN'ized expression: "cnt ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
	mov	ax, [bp-4]
	inc	word [bp-4]
; RPN'ized expression: "minlen --p "
; Expanded expression: "(@-30) --p(2) "
; Fused expression:    "--p(2) *(@-30) "
	mov	ax, [bp-30]
	dec	word [bp-30]
; }
	jmp	L131
L132:
; while
; RPN'ized expression: "pc *u 0 != "
; Expanded expression: "(@-22) *(2) *(-1) 0 != "
L133:
; Fused expression:    "*(2) (@-22) != *ax 0 IF! "
	mov	ax, [bp-22]
	mov	bx, ax
	mov	al, [bx]
	cbw
	cmp	ax, 0
	je	L134
; {
; RPN'ized expression: "( pc ++p *u putchar ) "
; Expanded expression: " (@-22) ++p(2) *(-1)  putchar ()2 "
; Fused expression:    "( ++p(2) *(@-22) *(-1) ax , putchar )2 "
	mov	ax, [bp-22]
	inc	word [bp-22]
	mov	bx, ax
	mov	al, [bx]
	cbw
	push	ax
	call	_putchar
	sub	sp, -2
; RPN'ized expression: "cnt ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
	mov	ax, [bp-4]
	inc	word [bp-4]
; }
	jmp	L133
L134:
; while
; RPN'ized expression: "minlen -u len > "
; Expanded expression: "(@-30) *(2) -u (@-32) *(2) > "
L135:
; Fused expression:    "*(2) (@-30) -u > ax *(@-32) IF! "
	mov	ax, [bp-30]
	neg	ax
	cmp	ax, [bp-32]
	jle	L136
; {
; RPN'ized expression: "( 32 putchar ) "
; Expanded expression: " 32  putchar ()2 "
; Fused expression:    "( 32 , putchar )2 "
	push	32
	call	_putchar
	sub	sp, -2
; RPN'ized expression: "cnt ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
	mov	ax, [bp-4]
	inc	word [bp-4]
; RPN'ized expression: "minlen ++p "
; Expanded expression: "(@-30) ++p(2) "
; Fused expression:    "++p(2) *(@-30) "
	mov	ax, [bp-30]
	inc	word [bp-30]
; }
	jmp	L135
L136:
; break
	jmp	L98
; case
; RPN'ized expression: "117 "
; Expanded expression: "117 "
; Expression value: 117
	jmp	L123
L122:
	cmp	ax, 117
	jne	L137
L123:
; RPN'ized expression: "pc s s sizeof 1 - + *u &u = "
; Expanded expression: "(@-22) (@-9) =(2) "
; Fused expression:    "=(170) *(@-22) (@-9) "
	lea	ax, [bp-9]
	mov	[bp-22], ax
; RPN'ized expression: "pc *u 0 = "
; Expanded expression: "(@-22) *(2) 0 =(-1) "
; Fused expression:    "*(2) (@-22) =(122) *ax 0 "
	mov	ax, [bp-22]
	mov	bx, ax
	mov	ax, 0
	mov	[bx], al
	cbw
; RPN'ized expression: "len 0 = "
; Expanded expression: "(@-32) 0 =(2) "
; Fused expression:    "=(170) *(@-32) 0 "
	mov	ax, 0
	mov	[bp-32], ax
; RPN'ized expression: "n pp ++p *u = "
; Expanded expression: "(@-24) (@-2) 2 +=p(2) *(2) =(2) "
; Fused expression:    "+=p(2) *(@-2) 2 =(170) *(@-24) *ax "
	mov	ax, [bp-2]
	add	word [bp-2], 2
	mov	bx, ax
	mov	ax, [bx]
	mov	[bp-24], ax
; do
L139:
; {
; loc                 nn : (@-34): unsigned
; =
; RPN'ized expression: "n "
; Expanded expression: "(@-24) *(2) "
; Fused expression:    "=(170) *(@-34) *(@-24) "
	mov	ax, [bp-24]
	mov	[bp-34], ax
; RPN'ized expression: "pc -- *u 48 nn 10 % + = "
; Expanded expression: "(@-22) --(2) 48 (@-34) *(2) 10 %u + =(-1) "
; Fused expression:    "--(2) *(@-22) push-ax %u *(@-34) 10 + 48 ax =(122) **sp ax "
	dec	word [bp-22]
	mov	ax, [bp-22]
	push	ax
	mov	ax, [bp-34]
	mov	dx, 0
	mov	cx, 10
	div	cx
	mov	ax, dx
	mov	cx, ax
	mov	ax, 48
	add	ax, cx
	pop	bx
	mov	[bx], al
	cbw
; RPN'ized expression: "n nn 10 / = "
; Expanded expression: "(@-24) (@-34) *(2) 10 /u =(2) "
; Fused expression:    "/u *(@-34) 10 =(170) *(@-24) ax "
	mov	ax, [bp-34]
	mov	dx, 0
	mov	cx, 10
	div	cx
	mov	[bp-24], ax
; RPN'ized expression: "len ++p "
; Expanded expression: "(@-32) ++p(2) "
; Fused expression:    "++p(2) *(@-32) "
	mov	ax, [bp-32]
	inc	word [bp-32]
; }
; while
; RPN'ized expression: "n "
; Expanded expression: "(@-24) *(2) "
L140:
; Fused expression:    "*(2) (@-24) "
	mov	ax, [bp-24]
; JumpIfNotZero
	test	ax, ax
	jne	L139
L141:
; if
; RPN'ized expression: "msign 0 > "
; Expanded expression: "(@-28) *(2) 0 > "
; Fused expression:    "> *(@-28) 0 IF! "
	mov	ax, [bp-28]
	cmp	ax, 0
	jle	L142
; {
; RPN'ized expression: "pc -- *u 43 = "
; Expanded expression: "(@-22) --(2) 43 =(-1) "
; Fused expression:    "--(2) *(@-22) =(122) *ax 43 "
	dec	word [bp-22]
	mov	ax, [bp-22]
	mov	bx, ax
	mov	ax, 43
	mov	[bx], al
	cbw
; RPN'ized expression: "len ++p "
; Expanded expression: "(@-32) ++p(2) "
; Fused expression:    "++p(2) *(@-32) "
	mov	ax, [bp-32]
	inc	word [bp-32]
; RPN'ized expression: "msign 0 = "
; Expanded expression: "(@-28) 0 =(2) "
; Fused expression:    "=(170) *(@-28) 0 "
	mov	ax, 0
	mov	[bp-28], ax
; }
L142:
; while
; RPN'ized expression: "minlen len > "
; Expanded expression: "(@-30) *(2) (@-32) *(2) > "
L144:
; Fused expression:    "> *(@-30) *(@-32) IF! "
	mov	ax, [bp-30]
	cmp	ax, [bp-32]
	jle	L145
; {
; RPN'ized expression: "( 32 putchar ) "
; Expanded expression: " 32  putchar ()2 "
; Fused expression:    "( 32 , putchar )2 "
	push	32
	call	_putchar
	sub	sp, -2
; RPN'ized expression: "cnt ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
	mov	ax, [bp-4]
	inc	word [bp-4]
; RPN'ized expression: "minlen --p "
; Expanded expression: "(@-30) --p(2) "
; Fused expression:    "--p(2) *(@-30) "
	mov	ax, [bp-30]
	dec	word [bp-30]
; }
	jmp	L144
L145:
; while
; RPN'ized expression: "pc *u 0 != "
; Expanded expression: "(@-22) *(2) *(-1) 0 != "
L146:
; Fused expression:    "*(2) (@-22) != *ax 0 IF! "
	mov	ax, [bp-22]
	mov	bx, ax
	mov	al, [bx]
	cbw
	cmp	ax, 0
	je	L147
; {
; RPN'ized expression: "( pc ++p *u putchar ) "
; Expanded expression: " (@-22) ++p(2) *(-1)  putchar ()2 "
; Fused expression:    "( ++p(2) *(@-22) *(-1) ax , putchar )2 "
	mov	ax, [bp-22]
	inc	word [bp-22]
	mov	bx, ax
	mov	al, [bx]
	cbw
	push	ax
	call	_putchar
	sub	sp, -2
; RPN'ized expression: "cnt ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
	mov	ax, [bp-4]
	inc	word [bp-4]
; }
	jmp	L146
L147:
; while
; RPN'ized expression: "minlen -u len > "
; Expanded expression: "(@-30) *(2) -u (@-32) *(2) > "
L148:
; Fused expression:    "*(2) (@-30) -u > ax *(@-32) IF! "
	mov	ax, [bp-30]
	neg	ax
	cmp	ax, [bp-32]
	jle	L149
; {
; RPN'ized expression: "( 32 putchar ) "
; Expanded expression: " 32  putchar ()2 "
; Fused expression:    "( 32 , putchar )2 "
	push	32
	call	_putchar
	sub	sp, -2
; RPN'ized expression: "cnt ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
	mov	ax, [bp-4]
	inc	word [bp-4]
; RPN'ized expression: "minlen ++p "
; Expanded expression: "(@-30) ++p(2) "
; Fused expression:    "++p(2) *(@-30) "
	mov	ax, [bp-30]
	inc	word [bp-30]
; }
	jmp	L148
L149:
; break
	jmp	L98
; case
; RPN'ized expression: "88 "
; Expanded expression: "88 "
; Expression value: 88
	jmp	L138
L137:
	cmp	ax, 88
	jne	L150
L138:
; RPN'ized expression: "phex L152 = "
; Expanded expression: "(@-8) L152 =(2) "
	jmp	L153
L152:
	db	"0123456789ABCDEF",0
L153:
; Fused expression:    "=(170) *(@-8) L152 "
	mov	ax, L152
	mov	[bp-8], ax
; case
; RPN'ized expression: "112 "
; Expanded expression: "112 "
; Expression value: 112
	jmp	L151
L150:
	cmp	ax, 112
	jne	L154
L151:
; case
; RPN'ized expression: "120 "
; Expanded expression: "120 "
; Expression value: 120
	jmp	L155
L154:
	cmp	ax, 120
	jne	L156
L155:
; RPN'ized expression: "pc s s sizeof 1 - + *u &u = "
; Expanded expression: "(@-22) (@-9) =(2) "
; Fused expression:    "=(170) *(@-22) (@-9) "
	lea	ax, [bp-9]
	mov	[bp-22], ax
; RPN'ized expression: "pc *u 0 = "
; Expanded expression: "(@-22) *(2) 0 =(-1) "
; Fused expression:    "*(2) (@-22) =(122) *ax 0 "
	mov	ax, [bp-22]
	mov	bx, ax
	mov	ax, 0
	mov	[bx], al
	cbw
; RPN'ized expression: "len 0 = "
; Expanded expression: "(@-32) 0 =(2) "
; Fused expression:    "=(170) *(@-32) 0 "
	mov	ax, 0
	mov	[bp-32], ax
; RPN'ized expression: "n pp ++p *u = "
; Expanded expression: "(@-24) (@-2) 2 +=p(2) *(2) =(2) "
; Fused expression:    "+=p(2) *(@-2) 2 =(170) *(@-24) *ax "
	mov	ax, [bp-2]
	add	word [bp-2], 2
	mov	bx, ax
	mov	ax, [bx]
	mov	[bp-24], ax
; do
L158:
; {
; loc                 nn : (@-34): unsigned
; =
; RPN'ized expression: "n "
; Expanded expression: "(@-24) *(2) "
; Fused expression:    "=(170) *(@-34) *(@-24) "
	mov	ax, [bp-24]
	mov	[bp-34], ax
; RPN'ized expression: "pc -- *u phex nn 15 & + *u = "
; Expanded expression: "(@-22) --(2) (@-8) *(2) (@-34) *(2) 15 & + *(-1) =(-1) "
; Fused expression:    "--(2) *(@-22) push-ax & *(@-34) 15 + *(@-8) ax =(119) **sp *ax "
	dec	word [bp-22]
	mov	ax, [bp-22]
	push	ax
	mov	ax, [bp-34]
	and	ax, 15
	mov	cx, ax
	mov	ax, [bp-8]
	add	ax, cx
	mov	bx, ax
	mov	al, [bx]
	cbw
	pop	bx
	mov	[bx], al
	cbw
; RPN'ized expression: "n nn 4 >> = "
; Expanded expression: "(@-24) (@-34) *(2) 4 >>u =(2) "
; Fused expression:    ">>u *(@-34) 4 =(170) *(@-24) ax "
	mov	ax, [bp-34]
	shr	ax, 4
	mov	[bp-24], ax
; RPN'ized expression: "len ++p "
; Expanded expression: "(@-32) ++p(2) "
; Fused expression:    "++p(2) *(@-32) "
	mov	ax, [bp-32]
	inc	word [bp-32]
; }
; while
; RPN'ized expression: "n "
; Expanded expression: "(@-24) *(2) "
L159:
; Fused expression:    "*(2) (@-24) "
	mov	ax, [bp-24]
; JumpIfNotZero
	test	ax, ax
	jne	L158
L160:
; while
; RPN'ized expression: "minlen len > "
; Expanded expression: "(@-30) *(2) (@-32) *(2) > "
L161:
; Fused expression:    "> *(@-30) *(@-32) IF! "
	mov	ax, [bp-30]
	cmp	ax, [bp-32]
	jle	L162
; {
; RPN'ized expression: "( 32 putchar ) "
; Expanded expression: " 32  putchar ()2 "
; Fused expression:    "( 32 , putchar )2 "
	push	32
	call	_putchar
	sub	sp, -2
; RPN'ized expression: "cnt ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
	mov	ax, [bp-4]
	inc	word [bp-4]
; RPN'ized expression: "minlen --p "
; Expanded expression: "(@-30) --p(2) "
; Fused expression:    "--p(2) *(@-30) "
	mov	ax, [bp-30]
	dec	word [bp-30]
; }
	jmp	L161
L162:
; while
; RPN'ized expression: "pc *u 0 != "
; Expanded expression: "(@-22) *(2) *(-1) 0 != "
L163:
; Fused expression:    "*(2) (@-22) != *ax 0 IF! "
	mov	ax, [bp-22]
	mov	bx, ax
	mov	al, [bx]
	cbw
	cmp	ax, 0
	je	L164
; {
; RPN'ized expression: "( pc ++p *u putchar ) "
; Expanded expression: " (@-22) ++p(2) *(-1)  putchar ()2 "
; Fused expression:    "( ++p(2) *(@-22) *(-1) ax , putchar )2 "
	mov	ax, [bp-22]
	inc	word [bp-22]
	mov	bx, ax
	mov	al, [bx]
	cbw
	push	ax
	call	_putchar
	sub	sp, -2
; RPN'ized expression: "cnt ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
	mov	ax, [bp-4]
	inc	word [bp-4]
; }
	jmp	L163
L164:
; while
; RPN'ized expression: "minlen -u len > "
; Expanded expression: "(@-30) *(2) -u (@-32) *(2) > "
L165:
; Fused expression:    "*(2) (@-30) -u > ax *(@-32) IF! "
	mov	ax, [bp-30]
	neg	ax
	cmp	ax, [bp-32]
	jle	L166
; {
; RPN'ized expression: "( 32 putchar ) "
; Expanded expression: " 32  putchar ()2 "
; Fused expression:    "( 32 , putchar )2 "
	push	32
	call	_putchar
	sub	sp, -2
; RPN'ized expression: "cnt ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
	mov	ax, [bp-4]
	inc	word [bp-4]
; RPN'ized expression: "minlen ++p "
; Expanded expression: "(@-30) ++p(2) "
; Fused expression:    "++p(2) *(@-30) "
	mov	ax, [bp-30]
	inc	word [bp-30]
; }
	jmp	L165
L166:
; break
	jmp	L98
; case
; RPN'ized expression: "111 "
; Expanded expression: "111 "
; Expression value: 111
	jmp	L157
L156:
	cmp	ax, 111
	jne	L167
L157:
; RPN'ized expression: "pc s s sizeof 1 - + *u &u = "
; Expanded expression: "(@-22) (@-9) =(2) "
; Fused expression:    "=(170) *(@-22) (@-9) "
	lea	ax, [bp-9]
	mov	[bp-22], ax
; RPN'ized expression: "pc *u 0 = "
; Expanded expression: "(@-22) *(2) 0 =(-1) "
; Fused expression:    "*(2) (@-22) =(122) *ax 0 "
	mov	ax, [bp-22]
	mov	bx, ax
	mov	ax, 0
	mov	[bx], al
	cbw
; RPN'ized expression: "len 0 = "
; Expanded expression: "(@-32) 0 =(2) "
; Fused expression:    "=(170) *(@-32) 0 "
	mov	ax, 0
	mov	[bp-32], ax
; RPN'ized expression: "n pp ++p *u = "
; Expanded expression: "(@-24) (@-2) 2 +=p(2) *(2) =(2) "
; Fused expression:    "+=p(2) *(@-2) 2 =(170) *(@-24) *ax "
	mov	ax, [bp-2]
	add	word [bp-2], 2
	mov	bx, ax
	mov	ax, [bx]
	mov	[bp-24], ax
; do
L169:
; {
; loc                 nn : (@-34): unsigned
; =
; RPN'ized expression: "n "
; Expanded expression: "(@-24) *(2) "
; Fused expression:    "=(170) *(@-34) *(@-24) "
	mov	ax, [bp-24]
	mov	[bp-34], ax
; RPN'ized expression: "pc -- *u 48 nn 7 & + = "
; Expanded expression: "(@-22) --(2) 48 (@-34) *(2) 7 & + =(-1) "
; Fused expression:    "--(2) *(@-22) push-ax & *(@-34) 7 + 48 ax =(122) **sp ax "
	dec	word [bp-22]
	mov	ax, [bp-22]
	push	ax
	mov	ax, [bp-34]
	and	ax, 7
	mov	cx, ax
	mov	ax, 48
	add	ax, cx
	pop	bx
	mov	[bx], al
	cbw
; RPN'ized expression: "n nn 3 >> = "
; Expanded expression: "(@-24) (@-34) *(2) 3 >>u =(2) "
; Fused expression:    ">>u *(@-34) 3 =(170) *(@-24) ax "
	mov	ax, [bp-34]
	shr	ax, 3
	mov	[bp-24], ax
; RPN'ized expression: "len ++p "
; Expanded expression: "(@-32) ++p(2) "
; Fused expression:    "++p(2) *(@-32) "
	mov	ax, [bp-32]
	inc	word [bp-32]
; }
; while
; RPN'ized expression: "n "
; Expanded expression: "(@-24) *(2) "
L170:
; Fused expression:    "*(2) (@-24) "
	mov	ax, [bp-24]
; JumpIfNotZero
	test	ax, ax
	jne	L169
L171:
; while
; RPN'ized expression: "minlen len > "
; Expanded expression: "(@-30) *(2) (@-32) *(2) > "
L172:
; Fused expression:    "> *(@-30) *(@-32) IF! "
	mov	ax, [bp-30]
	cmp	ax, [bp-32]
	jle	L173
; {
; RPN'ized expression: "( 32 putchar ) "
; Expanded expression: " 32  putchar ()2 "
; Fused expression:    "( 32 , putchar )2 "
	push	32
	call	_putchar
	sub	sp, -2
; RPN'ized expression: "cnt ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
	mov	ax, [bp-4]
	inc	word [bp-4]
; RPN'ized expression: "minlen --p "
; Expanded expression: "(@-30) --p(2) "
; Fused expression:    "--p(2) *(@-30) "
	mov	ax, [bp-30]
	dec	word [bp-30]
; }
	jmp	L172
L173:
; while
; RPN'ized expression: "pc *u 0 != "
; Expanded expression: "(@-22) *(2) *(-1) 0 != "
L174:
; Fused expression:    "*(2) (@-22) != *ax 0 IF! "
	mov	ax, [bp-22]
	mov	bx, ax
	mov	al, [bx]
	cbw
	cmp	ax, 0
	je	L175
; {
; RPN'ized expression: "( pc ++p *u putchar ) "
; Expanded expression: " (@-22) ++p(2) *(-1)  putchar ()2 "
; Fused expression:    "( ++p(2) *(@-22) *(-1) ax , putchar )2 "
	mov	ax, [bp-22]
	inc	word [bp-22]
	mov	bx, ax
	mov	al, [bx]
	cbw
	push	ax
	call	_putchar
	sub	sp, -2
; RPN'ized expression: "cnt ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
	mov	ax, [bp-4]
	inc	word [bp-4]
; }
	jmp	L174
L175:
; while
; RPN'ized expression: "minlen -u len > "
; Expanded expression: "(@-30) *(2) -u (@-32) *(2) > "
L176:
; Fused expression:    "*(2) (@-30) -u > ax *(@-32) IF! "
	mov	ax, [bp-30]
	neg	ax
	cmp	ax, [bp-32]
	jle	L177
; {
; RPN'ized expression: "( 32 putchar ) "
; Expanded expression: " 32  putchar ()2 "
; Fused expression:    "( 32 , putchar )2 "
	push	32
	call	_putchar
	sub	sp, -2
; RPN'ized expression: "cnt ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
	mov	ax, [bp-4]
	inc	word [bp-4]
; RPN'ized expression: "minlen ++p "
; Expanded expression: "(@-30) ++p(2) "
; Fused expression:    "++p(2) *(@-30) "
	mov	ax, [bp-30]
	inc	word [bp-30]
; }
	jmp	L176
L177:
; break
	jmp	L98
; default
L99:
; return
; RPN'ized expression: "1 -u "
; Expanded expression: "-1 "
; Expression value: -1
; Fused expression:    "-1 "
	mov	ax, -1
	jmp	L72
; }
	jmp	L98
L167:
	jmp	L99
L98:
; }
	jmp	L74
L76:
; return
; RPN'ized expression: "cnt "
; Expanded expression: "(@-4) *(2) "
; Fused expression:    "*(2) (@-4) "
	mov	ax, [bp-4]
	jmp	L72
L72:
	leave
	ret
L71:
	sub	sp, 34
	jmp	L70
; glb printf : (
; prm     fmt : * char
; prm     ...
;     ) int
_printf:
	push	bp
	mov	bp, sp
	jmp	L179
L178:
; loc     fmt : (@4): * char
; loc     pp : (@-2): * * void
; =
; RPN'ized expression: "fmt &u "
; Expanded expression: "(@4) "
; Fused expression:    "=(170) *(@-2) (@4) "
	lea	ax, [bp+4]
	mov	[bp-2], ax
; return
; RPN'ized expression: "( pp 1 + , fmt vprintf ) "
; Expanded expression: " (@-2) *(2) 2 +  (@4) *(2)  vprintf ()4 "
; Fused expression:    "( + *(@-2) 2 , *(2) (@4) , vprintf )4 "
	mov	ax, [bp-2]
	add	ax, 2
	push	ax
	push	word [bp+4]
	call	_vprintf
	sub	sp, -4
	jmp	L180
L180:
	leave
	ret
L179:
	sub	sp, 2
	jmp	L178
; glb putdec : (
; prm     n : int
;     ) void
_putdec:
	push	bp
	mov	bp, sp
	jmp	L182
L181:
; loc     n : (@4): int
; loc     r : (@-2): int
; if
; RPN'ized expression: "n 0 < "
; Expanded expression: "(@4) *(2) 0 < "
; Fused expression:    "< *(@4) 0 IF! "
	mov	ax, [bp+4]
	cmp	ax, 0
	jge	L184
; {
; RPN'ized expression: "( 45 putchar ) "
; Expanded expression: " 45  putchar ()2 "
; Fused expression:    "( 45 , putchar )2 "
	push	45
	call	_putchar
	sub	sp, -2
; RPN'ized expression: "r n 10 / 10 * n - = "
; Expanded expression: "(@-2) (@4) *(2) 10 / 10 * (@4) *(2) - =(2) "
; Fused expression:    "/ *(@4) 10 * ax 10 - ax *(@4) =(170) *(@-2) ax "
	mov	ax, [bp+4]
	cwd
	mov	cx, 10
	idiv	cx
	imul	ax, ax, 10
	sub	ax, [bp+4]
	mov	[bp-2], ax
; RPN'ized expression: "n n 10 -u / = "
; Expanded expression: "(@4) (@4) *(2) -10 / =(2) "
; Fused expression:    "/ *(@4) -10 =(170) *(@4) ax "
	mov	ax, [bp+4]
	cwd
	mov	cx, -10
	idiv	cx
	mov	[bp+4], ax
; }
	jmp	L185
L184:
; else
; {
; RPN'ized expression: "r n 10 % = "
; Expanded expression: "(@-2) (@4) *(2) 10 % =(2) "
; Fused expression:    "% *(@4) 10 =(170) *(@-2) ax "
	mov	ax, [bp+4]
	cwd
	mov	cx, 10
	idiv	cx
	mov	ax, dx
	mov	[bp-2], ax
; RPN'ized expression: "n n 10 / = "
; Expanded expression: "(@4) (@4) *(2) 10 / =(2) "
; Fused expression:    "/ *(@4) 10 =(170) *(@4) ax "
	mov	ax, [bp+4]
	cwd
	mov	cx, 10
	idiv	cx
	mov	[bp+4], ax
; }
L185:
; if
; RPN'ized expression: "n "
; Expanded expression: "(@4) *(2) "
; Fused expression:    "*(2) (@4) "
	mov	ax, [bp+4]
; JumpIfZero
	test	ax, ax
	je	L186
; RPN'ized expression: "( n putdec ) "
; Expanded expression: " (@4) *(2)  putdec ()2 "
; Fused expression:    "( *(2) (@4) , putdec )2 "
	push	word [bp+4]
	call	_putdec
	sub	sp, -2
L186:
; RPN'ized expression: "( 48 r + putchar ) "
; Expanded expression: " 48 (@-2) *(2) +  putchar ()2 "
; Fused expression:    "( + 48 *(@-2) , putchar )2 "
	mov	ax, 48
	add	ax, [bp-2]
	push	ax
	call	_putchar
	sub	sp, -2
L183:
	leave
	ret
L182:
	sub	sp, 2
	jmp	L181
; glb putdecu : (
; prm     n : unsigned
;     ) void
_putdecu:
	push	bp
	mov	bp, sp
	jmp	L189
L188:
; loc     n : (@4): unsigned
; loc     r : (@-2): int
; RPN'ized expression: "r n 10 % = "
; Expanded expression: "(@-2) (@4) *(2) 10 %u =(2) "
; Fused expression:    "%u *(@4) 10 =(170) *(@-2) ax "
	mov	ax, [bp+4]
	mov	dx, 0
	mov	cx, 10
	div	cx
	mov	ax, dx
	mov	[bp-2], ax
; RPN'ized expression: "n n 10 / = "
; Expanded expression: "(@4) (@4) *(2) 10 /u =(2) "
; Fused expression:    "/u *(@4) 10 =(170) *(@4) ax "
	mov	ax, [bp+4]
	mov	dx, 0
	mov	cx, 10
	div	cx
	mov	[bp+4], ax
; if
; RPN'ized expression: "n "
; Expanded expression: "(@4) *(2) "
; Fused expression:    "*(2) (@4) "
	mov	ax, [bp+4]
; JumpIfZero
	test	ax, ax
	je	L191
; RPN'ized expression: "( n putdecu ) "
; Expanded expression: " (@4) *(2)  putdecu ()2 "
; Fused expression:    "( *(2) (@4) , putdecu )2 "
	push	word [bp+4]
	call	_putdecu
	sub	sp, -2
L191:
; RPN'ized expression: "( 48 r + putchar ) "
; Expanded expression: " 48 (@-2) *(2) +  putchar ()2 "
; Fused expression:    "( + 48 *(@-2) , putchar )2 "
	mov	ax, 48
	add	ax, [bp-2]
	push	ax
	call	_putchar
	sub	sp, -2
L190:
	leave
	ret
L189:
	sub	sp, 2
	jmp	L188
; glb fact : (
; prm     x : int
;     ) int
_fact:
	push	bp
	mov	bp, sp
	jmp	L194
L193:
; loc     x : (@4): int
; if
; RPN'ized expression: "x 1 <= "
; Expanded expression: "(@4) *(2) 1 <= "
; Fused expression:    "<= *(@4) 1 IF! "
	mov	ax, [bp+4]
	cmp	ax, 1
	jg	L196
; return
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
	mov	ax, 1
	jmp	L195
L196:
; return
; RPN'ized expression: "x ( x 1 - fact ) * "
; Expanded expression: "(@4) *(2)  (@4) *(2) 1 -  fact ()2 * "
; Fused expression:    "( - *(@4) 1 , fact )2 * *(@4) ax "
	mov	ax, [bp+4]
	dec	ax
	push	ax
	call	_fact
	sub	sp, -2
	mov	cx, ax
	mov	ax, [bp+4]
	mul	cx
	jmp	L195
L195:
	leave
	ret
L194:
	jmp	L193
; glb fib : (
; prm     x : int
;     ) int
_fib:
	push	bp
	mov	bp, sp
	jmp	L199
L198:
; loc     x : (@4): int
; if
; RPN'ized expression: "x 0 <= "
; Expanded expression: "(@4) *(2) 0 <= "
; Fused expression:    "<= *(@4) 0 IF! "
	mov	ax, [bp+4]
	cmp	ax, 0
	jg	L201
; return
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "0 "
	mov	ax, 0
	jmp	L200
	jmp	L202
L201:
; else
; if
; RPN'ized expression: "x 1 == "
; Expanded expression: "(@4) *(2) 1 == "
; Fused expression:    "== *(@4) 1 IF! "
	mov	ax, [bp+4]
	cmp	ax, 1
	jne	L203
; return
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
	mov	ax, 1
	jmp	L200
L203:
L202:
; return
; RPN'ized expression: "( x 1 - fib ) ( x 2 - fib ) + "
; Expanded expression: " (@4) *(2) 1 -  fib ()2  (@4) *(2) 2 -  fib ()2 + "
; Fused expression:    "( - *(@4) 1 , fib )2 push-ax ( - *(@4) 2 , fib )2 + *sp ax "
	mov	ax, [bp+4]
	dec	ax
	push	ax
	call	_fib
	sub	sp, -2
	push	ax
	mov	ax, [bp+4]
	sub	ax, 2
	push	ax
	call	_fib
	sub	sp, -2
	mov	cx, ax
	pop	ax
	add	ax, cx
	jmp	L200
L200:
	leave
	ret
L199:
	jmp	L198
; glb breakCont : (void) void
_breakCont:
	push	bp
	mov	bp, sp
	jmp	L206
L205:
; loc     i : (@-2): int
; for
; RPN'ized expression: "i 0 = "
; Expanded expression: "(@-2) 0 =(2) "
; Fused expression:    "=(170) *(@-2) 0 "
	mov	ax, 0
	mov	[bp-2], ax
L208:
; RPN'ized expression: "i 10 < "
; Expanded expression: "(@-2) *(2) 10 < "
; Fused expression:    "< *(@-2) 10 IF! "
	mov	ax, [bp-2]
	cmp	ax, 10
	jge	L211
	jmp	L210
L209:
; RPN'ized expression: "i ++p "
; Expanded expression: "(@-2) ++p(2) "
; Fused expression:    "++p(2) *(@-2) "
	mov	ax, [bp-2]
	inc	word [bp-2]
	jmp	L208
L210:
; {
; loc         j : (@-4): int
; =
; RPN'ized expression: "i "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "=(170) *(@-4) *(@-2) "
	mov	ax, [bp-2]
	mov	[bp-4], ax
; if
; RPN'ized expression: "j 1 == "
; Expanded expression: "(@-4) *(2) 1 == "
; Fused expression:    "== *(@-4) 1 IF! "
	mov	ax, [bp-4]
	cmp	ax, 1
	jne	L212
; continue
	jmp	L209
L212:
; RPN'ized expression: "( j putdec ) "
; Expanded expression: " (@-4) *(2)  putdec ()2 "
; Fused expression:    "( *(2) (@-4) , putdec )2 "
	push	word [bp-4]
	call	_putdec
	sub	sp, -2
; if
; RPN'ized expression: "j 7 == "
; Expanded expression: "(@-4) *(2) 7 == "
; Fused expression:    "== *(@-4) 7 IF! "
	mov	ax, [bp-4]
	cmp	ax, 7
	jne	L214
; break
	jmp	L211
L214:
; }
	jmp	L209
L211:
; RPN'ized expression: "( 10 putchar ) "
; Expanded expression: " 10  putchar ()2 "
; Fused expression:    "( 10 , putchar )2 "
	push	10
	call	_putchar
	sub	sp, -2
L207:
	leave
	ret
L206:
	sub	sp, 4
	jmp	L205
; glb PointerStew : (void) void
_PointerStew:
	push	bp
	mov	bp, sp
	jmp	L217
L216:
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
; Fused expression:    "=(170) *(@-18) (@-16) "
	lea	ax, [bp-16]
	mov	[bp-18], ax
; RPN'ized expression: "c 0 + *u L219 = "
; Expanded expression: "(@-8) L219 =(2) "
	jmp	L220
L219:
	db	"ENTER",0
L220:
; Fused expression:    "=(170) *(@-8) L219 "
	mov	ax, L219
	mov	[bp-8], ax
; RPN'ized expression: "c 1 + *u L221 = "
; Expanded expression: "(@-6) L221 =(2) "
	jmp	L222
L221:
	db	"NEW",0
L222:
; Fused expression:    "=(170) *(@-6) L221 "
	mov	ax, L221
	mov	[bp-6], ax
; RPN'ized expression: "c 2 + *u L223 = "
; Expanded expression: "(@-4) L223 =(2) "
	jmp	L224
L223:
	db	"POINT",0
L224:
; Fused expression:    "=(170) *(@-4) L223 "
	mov	ax, L223
	mov	[bp-4], ax
; RPN'ized expression: "c 3 + *u L225 = "
; Expanded expression: "(@-2) L225 =(2) "
	jmp	L226
L225:
	db	"FIRST",0
L226:
; Fused expression:    "=(170) *(@-2) L225 "
	mov	ax, L225
	mov	[bp-2], ax
; RPN'ized expression: "cp 0 + *u c 3 + = "
; Expanded expression: "(@-16) (@-2) =(2) "
; Fused expression:    "=(170) *(@-16) (@-2) "
	lea	ax, [bp-2]
	mov	[bp-16], ax
; RPN'ized expression: "cp 1 + *u c 2 + = "
; Expanded expression: "(@-14) (@-4) =(2) "
; Fused expression:    "=(170) *(@-14) (@-4) "
	lea	ax, [bp-4]
	mov	[bp-14], ax
; RPN'ized expression: "cp 2 + *u c 1 + = "
; Expanded expression: "(@-12) (@-6) =(2) "
; Fused expression:    "=(170) *(@-12) (@-6) "
	lea	ax, [bp-6]
	mov	[bp-12], ax
; RPN'ized expression: "cp 3 + *u c = "
; Expanded expression: "(@-10) (@-8) =(2) "
; Fused expression:    "=(170) *(@-10) (@-8) "
	lea	ax, [bp-8]
	mov	[bp-10], ax
; RPN'ized expression: "( cpp ++ *u *u , L227 printf ) "
; Expanded expression: " (@-18) 2 +=(2) *(2) *(2)  L227  printf ()4 "
	jmp	L228
L227:
	db	"%s",0
L228:
; Fused expression:    "( +=(170) *(@-18) 2 *(2) ax *(2) ax , L227 , printf )4 "
	mov	ax, [bp-18]
	add	ax, 2
	mov	[bp-18], ax
	mov	bx, ax
	mov	ax, [bx]
	mov	bx, ax
	push	word [bx]
	push	L227
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( cpp ++ *u -- *u 3 + , L229 printf ) "
; Expanded expression: " (@-18) 2 +=(2) 2 -=(2) *(2) 3 +  L229  printf ()4 "
	jmp	L230
L229:
	db	"%s ",0
L230:
; Fused expression:    "( +=(170) *(@-18) 2 -=(170) *ax 2 + *ax 3 , L229 , printf )4 "
	mov	ax, [bp-18]
	add	ax, 2
	mov	[bp-18], ax
	mov	bx, ax
	mov	ax, [bx]
	sub	ax, 2
	mov	[bx], ax
	mov	bx, ax
	mov	ax, [bx]
	add	ax, 3
	push	ax
	push	L229
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( cpp 2 -u + *u *u 3 + , L231 printf ) "
; Expanded expression: " (@-18) *(2) -4 + *(2) *(2) 3 +  L231  printf ()4 "
	jmp	L232
L231:
	db	"%s",0
L232:
; Fused expression:    "( + *(@-18) -4 *(2) ax + *ax 3 , L231 , printf )4 "
	mov	ax, [bp-18]
	add	ax, -4
	mov	bx, ax
	mov	ax, [bx]
	mov	bx, ax
	mov	ax, [bx]
	add	ax, 3
	push	ax
	push	L231
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( cpp 1 -u + *u 1 -u + *u 1 + , L233 printf ) "
; Expanded expression: " (@-18) *(2) -2 + *(2) -2 + *(2) 1 +  L233  printf ()4 "
	jmp	L234
L233:
	db	"%s",10,0
L234:
; Fused expression:    "( + *(@-18) -2 + *ax -2 + *ax 1 , L233 , printf )4 "
	mov	ax, [bp-18]
	add	ax, -2
	mov	bx, ax
	mov	ax, [bx]
	add	ax, -2
	mov	bx, ax
	mov	ax, [bx]
	inc	ax
	push	ax
	push	L233
	call	_printf
	sub	sp, -4
L218:
	leave
	ret
L217:
	sub	sp, 18
	jmp	L216
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
_Print8:
	push	bp
	mov	bp, sp
	jmp	L236
L235:
; loc     Str : (@4): * char
; RPN'ized expression: "( Str , L238 printf ) "
; Expanded expression: " (@4) *(2)  L238  printf ()4 "
	jmp	L239
L238:
	db	"%s",0
L239:
; Fused expression:    "( *(2) (@4) , L238 , printf )4 "
	push	word [bp+4]
	push	L238
	call	_printf
	sub	sp, -4
; return
; RPN'ized expression: "Print8 &u "
; Expanded expression: "Print8 "
; Fused expression:    "Print8 "
	mov	ax, _Print8
	jmp	L237
L237:
	leave
	ret
L236:
	jmp	L235
; glb macros : (void) void
_macros:
	push	bp
	mov	bp, sp
	jmp	L241
L240:
; RPN'ized expression: "( L245 , 42 , L243 printf ) "
; Expanded expression: " L245  42  L243  printf ()6 "
	jmp	L246
L245:
	db	"42",0
L246:
	jmp	L244
L243:
	db	"SOMETHING=%d, SOMETHING_2=",34,"%s",34,10,0
L244:
; Fused expression:    "( L245 , 42 , L243 , printf )6 "
	push	L245
	push	42
	push	L243
	call	_printf
	sub	sp, -6
L242:
	leave
	ret
L241:
	jmp	L240
; glb Hola : * char
	align 2
_Hola:
; =
; RPN'ized expression: "L247 "
; Expanded expression: "L247 "
	dw	L247
L247:
	db	"iHola!",0
; glb main : (void) int
_main:
	push	bp
	mov	bp, sp
	jmp	L250
L249:
; RPN'ized expression: "16 "
; Expanded expression: "16 "
; Expression value: 16
; loc     hws : (@-16): [16u] char
; loc     phw : (@-18): * char
; =
; RPN'ized expression: "hws "
; Expanded expression: "(@-16) "
; Fused expression:    "=(170) *(@-18) (@-16) "
	lea	ax, [bp-16]
	mov	[bp-18], ax
; RPN'ized expression: "phw ++p *u 72 = "
; Expanded expression: "(@-18) ++p(2) 72 =(-1) "
; Fused expression:    "++p(2) *(@-18) =(122) *ax 72 "
	mov	ax, [bp-18]
	inc	word [bp-18]
	mov	bx, ax
	mov	ax, 72
	mov	[bx], al
	cbw
; RPN'ized expression: "phw ++p *u 101 = "
; Expanded expression: "(@-18) ++p(2) 101 =(-1) "
; Fused expression:    "++p(2) *(@-18) =(122) *ax 101 "
	mov	ax, [bp-18]
	inc	word [bp-18]
	mov	bx, ax
	mov	ax, 101
	mov	[bx], al
	cbw
; RPN'ized expression: "phw ++p *u 108 = "
; Expanded expression: "(@-18) ++p(2) 108 =(-1) "
; Fused expression:    "++p(2) *(@-18) =(122) *ax 108 "
	mov	ax, [bp-18]
	inc	word [bp-18]
	mov	bx, ax
	mov	ax, 108
	mov	[bx], al
	cbw
; RPN'ized expression: "phw ++p *u 108 = "
; Expanded expression: "(@-18) ++p(2) 108 =(-1) "
; Fused expression:    "++p(2) *(@-18) =(122) *ax 108 "
	mov	ax, [bp-18]
	inc	word [bp-18]
	mov	bx, ax
	mov	ax, 108
	mov	[bx], al
	cbw
; RPN'ized expression: "phw ++p *u 111 = "
; Expanded expression: "(@-18) ++p(2) 111 =(-1) "
; Fused expression:    "++p(2) *(@-18) =(122) *ax 111 "
	mov	ax, [bp-18]
	inc	word [bp-18]
	mov	bx, ax
	mov	ax, 111
	mov	[bx], al
	cbw
; RPN'ized expression: "phw ++p *u 32 = "
; Expanded expression: "(@-18) ++p(2) 32 =(-1) "
; Fused expression:    "++p(2) *(@-18) =(122) *ax 32 "
	mov	ax, [bp-18]
	inc	word [bp-18]
	mov	bx, ax
	mov	ax, 32
	mov	[bx], al
	cbw
; RPN'ized expression: "phw ++p *u 87 = "
; Expanded expression: "(@-18) ++p(2) 87 =(-1) "
; Fused expression:    "++p(2) *(@-18) =(122) *ax 87 "
	mov	ax, [bp-18]
	inc	word [bp-18]
	mov	bx, ax
	mov	ax, 87
	mov	[bx], al
	cbw
; RPN'ized expression: "phw ++p *u 111 = "
; Expanded expression: "(@-18) ++p(2) 111 =(-1) "
; Fused expression:    "++p(2) *(@-18) =(122) *ax 111 "
	mov	ax, [bp-18]
	inc	word [bp-18]
	mov	bx, ax
	mov	ax, 111
	mov	[bx], al
	cbw
; RPN'ized expression: "phw ++p *u 114 = "
; Expanded expression: "(@-18) ++p(2) 114 =(-1) "
; Fused expression:    "++p(2) *(@-18) =(122) *ax 114 "
	mov	ax, [bp-18]
	inc	word [bp-18]
	mov	bx, ax
	mov	ax, 114
	mov	[bx], al
	cbw
; RPN'ized expression: "phw ++p *u 108 = "
; Expanded expression: "(@-18) ++p(2) 108 =(-1) "
; Fused expression:    "++p(2) *(@-18) =(122) *ax 108 "
	mov	ax, [bp-18]
	inc	word [bp-18]
	mov	bx, ax
	mov	ax, 108
	mov	[bx], al
	cbw
; RPN'ized expression: "phw ++p *u 100 = "
; Expanded expression: "(@-18) ++p(2) 100 =(-1) "
; Fused expression:    "++p(2) *(@-18) =(122) *ax 100 "
	mov	ax, [bp-18]
	inc	word [bp-18]
	mov	bx, ax
	mov	ax, 100
	mov	[bx], al
	cbw
; RPN'ized expression: "phw ++p *u 33 = "
; Expanded expression: "(@-18) ++p(2) 33 =(-1) "
; Fused expression:    "++p(2) *(@-18) =(122) *ax 33 "
	mov	ax, [bp-18]
	inc	word [bp-18]
	mov	bx, ax
	mov	ax, 33
	mov	[bx], al
	cbw
; RPN'ized expression: "phw ++p *u 0 = "
; Expanded expression: "(@-18) ++p(2) 0 =(-1) "
; Fused expression:    "++p(2) *(@-18) =(122) *ax 0 "
	mov	ax, [bp-18]
	inc	word [bp-18]
	mov	bx, ax
	mov	ax, 0
	mov	[bx], al
	cbw
; RPN'ized expression: "( ( hws strlen ) , hws , L252 printf ) "
; Expanded expression: "  (@-16)  strlen ()2  (@-16)  L252  printf ()6 "
	jmp	L253
L252:
	db	"hws=",34,"%s",34,", strlen(hws)=%u",10,0
L253:
; Fused expression:    "( ( (@-16) , strlen )2 , (@-16) , L252 , printf )6 "
	lea	ax, [bp-16]
	push	ax
	call	_strlen
	sub	sp, -2
	push	ax
	lea	ax, [bp-16]
	push	ax
	push	L252
	call	_printf
	sub	sp, -6
; RPN'ized expression: "( L254 puts ) "
; Expanded expression: " L254  puts ()2 "
	jmp	L255
L254:
	db	"Buongiorno!",0
L255:
; Fused expression:    "( L254 , puts )2 "
	push	L254
	call	_puts
	sub	sp, -2
; RPN'ized expression: "( Hola puts ) "
; Expanded expression: " Hola *(2)  puts ()2 "
; Fused expression:    "( *(2) Hola , puts )2 "
	push	word [_Hola]
	call	_puts
	sub	sp, -2
; RPN'ized expression: "( 65535u , 32767 -u 1 - , L260 , 122 , 43690u , 32767 , L258 , 97 , L256 printf ) "
; Expanded expression: " 65535u  -32768  L260  122  43690u  32767  L258  97  L256  printf ()18 "
	jmp	L261
L260:
	db	"xyz",0
L261:
	jmp	L259
L258:
	db	"abc",0
L259:
	jmp	L257
L256:
	db	"%% char='%c' str=",34,"%s",34," dec=%d hex=%x %% char='%c' str=",34,"%s",34," dec=%d hex=%X",10,0
L257:
; Fused expression:    "( 65535u , -32768 , L260 , 122 , 43690u , 32767 , L258 , 97 , L256 , printf )18 "
	push	-1
	push	-32768
	push	L260
	push	122
	push	-21846
	push	32767
	push	L258
	push	97
	push	L256
	call	_printf
	sub	sp, -18
; RPN'ized expression: "( 4095 , 4095 , 4095 , L262 printf ) "
; Expanded expression: " 4095  4095  4095  L262  printf ()8 "
	jmp	L263
L262:
	db	"07777=%d, 0xFff=%d, 4095=0%o",10,0
L263:
; Fused expression:    "( 4095 , 4095 , 4095 , L262 , printf )8 "
	push	4095
	push	4095
	push	4095
	push	L262
	call	_printf
	sub	sp, -8
; RPN'ized expression: "( -1 , -1 , 127 , 0 , 127 , 0 , L264 printf ) "
; Expanded expression: " -1  -1  127  0  127  0  L264  printf ()14 "
	jmp	L265
L264:
	db	"'\x0'=%X, '\x7F'=%X, '\0'=%o, '\177'=%o, '\xFf'=%X, '\377'=%o",10,0
L265:
; Fused expression:    "( -1 , -1 , 127 , 0 , 127 , 0 , L264 , printf )14 "
	push	-1
	push	-1
	push	127
	push	0
	push	127
	push	0
	push	L264
	call	_printf
	sub	sp, -14
; RPN'ized expression: "( L270 sizeof , L268 2 + *u , L266 printf ) "
; Expanded expression: " 3u  L268 2 + *(-1)  L266  printf ()6 "
	jmp	L269
L268:
	db	"xyz",0
L269:
	jmp	L267
L266:
	db	34,"xyz",34,"[2]='%c', sizeof ",34,"az",34,"=%u",10,0
L267:
; Fused expression:    "( 3u , + L268 2 *(-1) ax , L266 , printf )6 "
	push	3
	mov	ax, L268
	add	ax, 2
	mov	bx, ax
	mov	al, [bx]
	cbw
	push	ax
	push	L266
	call	_printf
	sub	sp, -6
; RPN'ized expression: "( ( 10 fib ) , ( 7 fact ) , L272 printf ) "
; Expanded expression: "  10  fib ()2   7  fact ()2  L272  printf ()6 "
	jmp	L273
L272:
	db	"fact(7)=%d, fib(10)=%d",10,0
L273:
; Fused expression:    "( ( 10 , fib )2 , ( 7 , fact )2 , L272 , printf )6 "
	push	10
	call	_fib
	sub	sp, -2
	push	ax
	push	7
	call	_fact
	sub	sp, -2
	push	ax
	push	L272
	call	_printf
	sub	sp, -6
; RPN'ized expression: "( L276 , L274 printf ) "
; Expanded expression: " L276  L274  printf ()4 "
	jmp	L277
L276:
	db	"pea",0,"nut",0
L277:
	jmp	L275
L274:
	db	"printf(",34,"pea\0nut",34,"): ",34,"%s",34,10,0
L275:
; Fused expression:    "( L276 , L274 , printf )4 "
	push	L276
	push	L274
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( L280 3 + , L278 printf ) "
; Expanded expression: " L280 3 +  L278  printf ()4 "
	jmp	L281
L280:
	db	"peanut",0
L281:
	jmp	L279
L278:
	db	"printf(",34,"peanut",34," + 3): ",34,"%s",34,10,0
L279:
; Fused expression:    "( + L280 3 , L278 , printf )4 "
	mov	ax, L280
	add	ax, 3
	push	ax
	push	L278
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( L282 puts ) "
; Expanded expression: " L282  puts ()2 "
	jmp	L283
L282:
	db	"press a key...",0
L283:
; Fused expression:    "( L282 , puts )2 "
	push	L282
	call	_puts
	sub	sp, -2
; RPN'ized expression: "( getchar ) "
; Expanded expression: " getchar ()0 "
; Fused expression:    "( getchar )0 "
	call	_getchar
; RPN'ized expression: "( breakCont ) "
; Expanded expression: " breakCont ()0 "
; Fused expression:    "( breakCont )0 "
	call	_breakCont
; loc     xx : (@-20): int
; RPN'ized expression: "xx sizeof "
; Expanded expression: "2u "
; Expression value: 2u
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
; loc     yy : (@-28): [2u] [2u] int
; RPN'ized expression: "L284 sizeof "
; Expanded expression: "3u "
; Expression value: 3u
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
; loc     zz : (@-40): [3u] [2u] int
; loc     Switch : (void) void
; RPN'ized expression: "( Switch ) "
; Expanded expression: " Switch ()0 "
; Fused expression:    "( Switch )0 "
	call	_Switch
; loc     pgb : (@-42): * char
; =
; RPN'ized expression: "L286 "
; Expanded expression: "L286 "
	jmp	L287
L286:
	db	"Green on Black!",0
L287:
; Fused expression:    "=(170) *(@-42) L286 "
	mov	ax, L286
	mov	[bp-42], ax
; RPN'ized expression: "( pgb puts ) "
; Expanded expression: " (@-42) *(2)  puts ()2 "
; Fused expression:    "( *(2) (@-42) , puts )2 "
	push	word [bp-42]
	call	_puts
	sub	sp, -2
; loc     x : (@-44): int
; loc     y : (@-46): int
; for
; RPN'ized expression: "y 0 = "
; Expanded expression: "(@-46) 0 =(2) "
; Fused expression:    "=(170) *(@-46) 0 "
	mov	ax, 0
	mov	[bp-46], ax
L288:
; RPN'ized expression: "y 25 < "
; Expanded expression: "(@-46) *(2) 25 < "
; Fused expression:    "< *(@-46) 25 IF! "
	mov	ax, [bp-46]
	cmp	ax, 25
	jge	L291
	jmp	L290
L289:
; RPN'ized expression: "y ++p "
; Expanded expression: "(@-46) ++p(2) "
; Fused expression:    "++p(2) *(@-46) "
	mov	ax, [bp-46]
	inc	word [bp-46]
	jmp	L288
L290:
; for
; RPN'ized expression: "x 0 = "
; Expanded expression: "(@-44) 0 =(2) "
; Fused expression:    "=(170) *(@-44) 0 "
	mov	ax, 0
	mov	[bp-44], ax
L292:
; RPN'ized expression: "x 80 < "
; Expanded expression: "(@-44) *(2) 80 < "
; Fused expression:    "< *(@-44) 80 IF! "
	mov	ax, [bp-44]
	cmp	ax, 80
	jge	L295
	jmp	L294
L293:
; RPN'ized expression: "x ++p "
; Expanded expression: "(@-44) ++p(2) "
; Fused expression:    "++p(2) *(@-44) "
	mov	ax, [bp-44]
	inc	word [bp-44]
	jmp	L292
L294:
; RPN'ized expression: "( 2 , y 80 * x + 2 * 1 + , 47104u pokeb ) "
; Expanded expression: " 2  (@-46) *(2) 80 * (@-44) *(2) + 2 * 1 +  47104u  pokeb ()6 "
; Fused expression:    "( 2 , * *(@-46) 80 + ax *(@-44) * ax 2 + ax 1 , 47104u , pokeb )6 "
	push	2
	mov	ax, [bp-46]
	imul	ax, ax, 80
	add	ax, [bp-44]
	imul	ax, ax, 2
	inc	ax
	push	ax
	push	-18432
	call	_pokeb
	sub	sp, -6
	jmp	L293
L295:
	jmp	L289
L291:
; RPN'ized expression: "( L296 puts ) "
; Expanded expression: " L296  puts ()2 "
	jmp	L297
L296:
	db	"press a key once for graphics mode and then another time for text mode...",0
L297:
; Fused expression:    "( L296 , puts )2 "
	push	L296
	call	_puts
	sub	sp, -2
; RPN'ized expression: "( getchar ) "
; Expanded expression: " getchar ()0 "
; Fused expression:    "( getchar )0 "
	call	_getchar
; loc     gfxmode : (
; prm         mode : int
;         ) void
; RPN'ized expression: "( 19 gfxmode ) "
; Expanded expression: " 19  gfxmode ()2 "
; Fused expression:    "( 19 , gfxmode )2 "
	push	19
	call	_gfxmode
	sub	sp, -2
; for
; RPN'ized expression: "y 0 = "
; Expanded expression: "(@-46) 0 =(2) "
; Fused expression:    "=(170) *(@-46) 0 "
	mov	ax, 0
	mov	[bp-46], ax
L298:
; RPN'ized expression: "y 200 < "
; Expanded expression: "(@-46) *(2) 200 < "
; Fused expression:    "< *(@-46) 200 IF! "
	mov	ax, [bp-46]
	cmp	ax, 200
	jge	L301
	jmp	L300
L299:
; RPN'ized expression: "y ++p "
; Expanded expression: "(@-46) ++p(2) "
; Fused expression:    "++p(2) *(@-46) "
	mov	ax, [bp-46]
	inc	word [bp-46]
	jmp	L298
L300:
; for
; RPN'ized expression: "x 0 = "
; Expanded expression: "(@-44) 0 =(2) "
; Fused expression:    "=(170) *(@-44) 0 "
	mov	ax, 0
	mov	[bp-44], ax
L302:
; RPN'ized expression: "x 320 < "
; Expanded expression: "(@-44) *(2) 320 < "
; Fused expression:    "< *(@-44) 320 IF! "
	mov	ax, [bp-44]
	cmp	ax, 320
	jge	L305
	jmp	L304
L303:
; RPN'ized expression: "x ++p "
; Expanded expression: "(@-44) ++p(2) "
; Fused expression:    "++p(2) *(@-44) "
	mov	ax, [bp-44]
	inc	word [bp-44]
	jmp	L302
L304:
; RPN'ized expression: "( x y + 15 & , y 320 * x + , 40960u pokeb ) "
; Expanded expression: " (@-44) *(2) (@-46) *(2) + 15 &  (@-46) *(2) 320 * (@-44) *(2) +  40960u  pokeb ()6 "
; Fused expression:    "( + *(@-44) *(@-46) & ax 15 , * *(@-46) 320 + ax *(@-44) , 40960u , pokeb )6 "
	mov	ax, [bp-44]
	add	ax, [bp-46]
	and	ax, 15
	push	ax
	mov	ax, [bp-46]
	imul	ax, ax, 320
	add	ax, [bp-44]
	push	ax
	push	-24576
	call	_pokeb
	sub	sp, -6
	jmp	L303
L305:
	jmp	L299
L301:
; RPN'ized expression: "( getchar ) "
; Expanded expression: " getchar ()0 "
; Fused expression:    "( getchar )0 "
	call	_getchar
; RPN'ized expression: "( 3 gfxmode ) "
; Expanded expression: " 3  gfxmode ()2 "
; Fused expression:    "( 3 , gfxmode )2 "
	push	3
	call	_gfxmode
	sub	sp, -2
; loc     <something> : char
; RPN'ized expression: "( <something308> sizeof , L306 printf ) "
; Expanded expression: " 1u  L306  printf ()4 "
	jmp	L307
L306:
	db	"sizeof(char)=%u",10,0
L307:
; Fused expression:    "( 1u , L306 , printf )4 "
	push	1
	push	L306
	call	_printf
	sub	sp, -4
; loc     <something> : int
; RPN'ized expression: "( <something311> sizeof , L309 printf ) "
; Expanded expression: " 2u  L309  printf ()4 "
	jmp	L310
L309:
	db	"sizeof(int)=%u",10,0
L310:
; Fused expression:    "( 2u , L309 , printf )4 "
	push	2
	push	L309
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( , L312 printf 3 "
; Expanded expression: "  L312 printf 3 "
; Expression value: 3
; loc     <something> : [3u] char
; RPN'ized expression: "( <something314> sizeof , L312 printf ) "
; Expanded expression: " 3u  L312  printf ()4 "
	jmp	L313
L312:
	db	"sizeof(char[3])=%u",10,0
L313:
; Fused expression:    "( 3u , L312 , printf )4 "
	push	3
	push	L312
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( , L315 printf 5 "
; Expanded expression: "  L315 printf 5 "
; Expression value: 5
; loc     <something> : [5u] * () char
; RPN'ized expression: "( <something317> sizeof , L315 printf ) "
; Expanded expression: " 10u  L315  printf ()4 "
	jmp	L316
L315:
	db	"sizeof(char(*[5])())=%u",10,0
L316:
; Fused expression:    "( 10u , L315 , printf )4 "
	push	10
	push	L315
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( , L318 printf 3 "
; Expanded expression: "  L318 printf 3 "
; Expression value: 3
; loc     <something> : [3u] int
; RPN'ized expression: "( , L318 printf <something322> sizeof "
; Expanded expression: "  L318 printf 6u "
; Expression value: 6u
; loc     <something> : [6u] int
; RPN'ized expression: "( , L318 printf <something321> sizeof "
; Expanded expression: "  L318 printf 12u "
; Expression value: 12u
; loc     <something> : [12u] int
; RPN'ized expression: "( <something320> sizeof , L318 printf ) "
; Expanded expression: " 24u  L318  printf ()4 "
	jmp	L319
L318:
	db	"sizeof(int[sizeof(int[sizeof(int[3])])])=%u",10,0
L319:
; Fused expression:    "( 24u , L318 , printf )4 "
	push	24
	push	L318
	call	_printf
	sub	sp, -4
; RPN'ized expression: "3 "
; Expanded expression: "3 "
; Expression value: 3
; loc     <something> : [3u] int
; RPN'ized expression: "<something325> sizeof "
; Expanded expression: "6u "
; Expression value: 6u
; loc     <something> : [6u] int
; RPN'ized expression: "<something324> sizeof "
; Expanded expression: "12u "
; Expression value: 12u
; loc     <something> : [12u] int
; RPN'ized expression: "<something323> sizeof "
; Expanded expression: "24u "
; Expression value: 24u
; loc     yui : (@-70): [24u] char
; loc     <something> : * () char
; RPN'ized expression: "( <something328> sizeof , L326 printf ) "
; Expanded expression: " 2u  L326  printf ()4 "
	jmp	L327
L326:
	db	"sizeof(char(*)())=%u",10,0
L327:
; Fused expression:    "( 2u , L326 , printf )4 "
	push	2
	push	L326
	call	_printf
	sub	sp, -4
; loc     <something> : () char
; RPN'ized expression: "( <something331> sizeof , L329 printf ) "
; Expanded expression: " 2u  L329  printf ()4 "
	jmp	L330
L329:
	db	"sizeof(char())=%u",10,0
L330:
; Fused expression:    "( 2u , L329 , printf )4 "
	push	2
	push	L329
	call	_printf
	sub	sp, -4
; loc     <something> : () * char
; RPN'ized expression: "( <something334> sizeof , L332 printf ) "
; Expanded expression: " 2u  L332  printf ()4 "
	jmp	L333
L332:
	db	"sizeof(char*())=%u",10,0
L333:
; Fused expression:    "( 2u , L332 , printf )4 "
	push	2
	push	L332
	call	_printf
	sub	sp, -4
; loc     <something> : () int
; RPN'ized expression: "( <something337> sizeof , L335 printf ) "
; Expanded expression: " 2u  L335  printf ()4 "
	jmp	L336
L335:
	db	"sizeof(int())=%u",10,0
L336:
; Fused expression:    "( 2u , L335 , printf )4 "
	push	2
	push	L335
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( main sizeof , L338 printf ) "
; Expanded expression: " 2u  L338  printf ()4 "
	jmp	L339
L338:
	db	"sizeof main=%u",10,0
L339:
; Fused expression:    "( 2u , L338 , printf )4 "
	push	2
	push	L338
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( ( main ) sizeof , L340 printf ) "
; Expanded expression: " 2u  L340  printf ()4 "
	jmp	L341
L340:
	db	"sizeof main()=%u",10,0
L341:
; Fused expression:    "( 2u , L340 , printf )4 "
	push	2
	push	L340
	call	_printf
	sub	sp, -4
; loc     <something> : () void
; RPN'ized expression: "( <something344> sizeof , L342 printf ) "
; Expanded expression: " 2u  L342  printf ()4 "
	jmp	L343
L342:
	db	"sizeof(void())=%u",10,0
L343:
; Fused expression:    "( 2u , L342 , printf )4 "
	push	2
	push	L342
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( , L345 printf 7 "
; Expanded expression: "  L345 printf 7 "
; Expression value: 7
; loc     <something> : [7u] char
; RPN'ized expression: "( <something347> sizeof , L345 printf ) "
; Expanded expression: " 7u  L345  printf ()4 "
	jmp	L346
L345:
	db	"sizeof(char[7])=%u",10,0
L346:
; Fused expression:    "( 7u , L345 , printf )4 "
	push	7
	push	L345
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( , L352 , L350 , L348 printf 3 "
; Expanded expression: "  L352  L350  L348 printf 3 "
; Expression value: 3
; loc     <something> : [3u] int
; RPN'ized expression: "( , L352 , L350 , L348 printf <something357> sizeof 5 "
; Expanded expression: "  L352  L350  L348 printf <something357> sizeof 5 "
; Expression value: 5
; loc     <something> : [5u] int
; RPN'ized expression: "( , L352 , L350 , L348 printf <something357> sizeof <something358> sizeof + "
; Expanded expression: "  L352  L350  L348 printf 16u "
; Expression value: 16u
; loc     <something> : [16u] int
; RPN'ized expression: "( , L352 , L350 , L348 printf <something356> sizeof "
; Expanded expression: "  L352  L350  L348 printf 32u "
; Expression value: 32u
; loc     <something> : [32u] int
; RPN'ized expression: "( , L352 , L350 , L348 printf <something355> sizeof 7 "
; Expanded expression: "  L352  L350  L348 printf <something355> sizeof 7 "
; Expression value: 7
; loc     <something> : [7u] int
; RPN'ized expression: "( , L352 , L350 , L348 printf <something355> sizeof <something361> sizeof 9 "
; Expanded expression: "  L352  L350  L348 printf <something355> sizeof <something361> sizeof 9 "
; Expression value: 9
; loc     <something> : [9u] int
; RPN'ized expression: "( , L352 , L350 , L348 printf <something355> sizeof <something361> sizeof <something362> sizeof + "
; Expanded expression: "  L352  L350  L348 printf <something355> sizeof 32u "
; Expression value: 32u
; loc     <something> : [32u] int
; RPN'ized expression: "( , L352 , L350 , L348 printf <something355> sizeof <something360> sizeof "
; Expanded expression: "  L352  L350  L348 printf <something355> sizeof 64u "
; Expression value: 64u
; loc     <something> : [64u] int
; RPN'ized expression: "( , L352 , L350 , L348 printf <something355> sizeof <something359> sizeof + "
; Expanded expression: "  L352  L350  L348 printf 192u "
; Expression value: 192u
; loc     <something> : [192u] int
; RPN'ized expression: "( <something354> sizeof , L352 , L350 , L348 printf ) "
; Expanded expression: " 384u  L352  L350  L348  printf ()8 "
	jmp	L353
L352:
	db	"sizeof(int[sizeof(int[sizeof(int[7])+sizeof(int[9])])])])",0
L353:
	jmp	L351
L350:
	db	"sizeof(int[sizeof(int[sizeof(int[sizeof(int[3])+sizeof(int[5])])])+",0
L351:
	jmp	L349
L348:
	db	"%s%s=%u",10,0
L349:
; Fused expression:    "( 384u , L352 , L350 , L348 , printf )8 "
	push	384
	push	L352
	push	L350
	push	L348
	call	_printf
	sub	sp, -8
; RPN'ized expression: "( PointerStew ) "
; Expanded expression: " PointerStew ()0 "
; Fused expression:    "( PointerStew )0 "
	call	_PointerStew
; RPN'ized expression: "( L371 ( L369 ( L367 ( L365 ( L363 Print8 ) ) ) ) ) "
; Expanded expression: " L371   L369   L367   L365   L363  Print8 ()2 ()2 ()2 ()2 ()2 "
	jmp	L372
L371:
	db	10,0
L372:
	jmp	L370
L369:
	db	"!",0
L370:
	jmp	L368
L367:
	db	"world",0
L368:
	jmp	L366
L365:
	db	" ",0
L366:
	jmp	L364
L363:
	db	"hello",0
L364:
; Fused expression:    "( L371 , ( L369 , ( L367 , ( L365 , ( L363 , Print8 )2 )2 )2 )2 )2 "
	push	L371
	push	L369
	push	L367
	push	L365
	push	L363
	call	_Print8
	sub	sp, -2
	call	ax
	sub	sp, -2
	call	ax
	sub	sp, -2
	call	ax
	sub	sp, -2
	call	ax
	sub	sp, -2
; RPN'ized expression: "( macros ) "
; Expanded expression: " macros ()0 "
; Fused expression:    "( macros )0 "
	call	_macros
; RPN'ized expression: "( L373 printf ) "
; Expanded expression: " L373  printf ()2 "
	jmp	L374
L373:
	db	"These are six concatenated string literals!",10,0
L374:
; Fused expression:    "( L373 , printf )2 "
	push	L373
	call	_printf
	sub	sp, -2
; RPN'ized expression: "( L377 , L375 printf ) "
; Expanded expression: " L377  L375  printf ()4 "
	jmp	L378
L377:
	db	"ABC012abc",0
L378:
	jmp	L376
L375:
	db	34,"\x41\x42\x43\60\61\62abc",34," = ",34,"%s",34,10,0
L376:
; Fused expression:    "( L377 , L375 , printf )4 "
	push	L377
	push	L375
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( L379 puts ) "
; Expanded expression: " L379  puts ()2 "
	jmp	L380
L379:
	db	"press a key...",0
L380:
; Fused expression:    "( L379 , puts )2 "
	push	L379
	call	_puts
	sub	sp, -2
; RPN'ized expression: "( getchar ) "
; Expanded expression: " getchar ()0 "
; Fused expression:    "( getchar )0 "
	call	_getchar
; RPN'ized expression: "3 "
; Expanded expression: "3 "
; Expression value: 3
; loc     arr : (@-76): [3u] int
; loc     p : (@-78): * int
; =
; RPN'ized expression: "arr 1 + "
; Expanded expression: "(@-74) "
; Fused expression:    "=(170) *(@-78) (@-74) "
	lea	ax, [bp-74]
	mov	[bp-78], ax
; RPN'ized expression: "arr 0 + *u 11 = "
; Expanded expression: "(@-76) 11 =(2) "
; Fused expression:    "=(170) *(@-76) 11 "
	mov	ax, 11
	mov	[bp-76], ax
; RPN'ized expression: "arr 1 + *u 22 = "
; Expanded expression: "(@-74) 22 =(2) "
; Fused expression:    "=(170) *(@-74) 22 "
	mov	ax, 22
	mov	[bp-74], ax
; RPN'ized expression: "arr 2 + *u 33 = "
; Expanded expression: "(@-72) 33 =(2) "
; Fused expression:    "=(170) *(@-72) 33 "
	mov	ax, 33
	mov	[bp-72], ax
; RPN'ized expression: "( p 1 -= *u , L381 printf ) "
; Expanded expression: " (@-78) 2 -=(2) *(2)  L381  printf ()4 "
	jmp	L382
L381:
	db	"arr[0]=%d",10,0
L382:
; Fused expression:    "( -=(170) *(@-78) 2 *(2) ax , L381 , printf )4 "
	mov	ax, [bp-78]
	sub	ax, 2
	mov	[bp-78], ax
	mov	bx, ax
	push	word [bx]
	push	L381
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( p 1 += *u , L383 printf ) "
; Expanded expression: " (@-78) 2 +=(2) *(2)  L383  printf ()4 "
	jmp	L384
L383:
	db	"arr[1]=%d",10,0
L384:
; Fused expression:    "( +=(170) *(@-78) 2 *(2) ax , L383 , printf )4 "
	mov	ax, [bp-78]
	add	ax, 2
	mov	[bp-78], ax
	mov	bx, ax
	push	word [bx]
	push	L383
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( p 1 += *u , L385 printf ) "
; Expanded expression: " (@-78) 2 +=(2) *(2)  L385  printf ()4 "
	jmp	L386
L385:
	db	"arr[2]=%d",10,0
L386:
; Fused expression:    "( +=(170) *(@-78) 2 *(2) ax , L385 , printf )4 "
	mov	ax, [bp-78]
	add	ax, 2
	mov	[bp-78], ax
	mov	bx, ax
	push	word [bx]
	push	L385
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( L387 printf ) "
; Expanded expression: " L387  printf ()2 "
	jmp	L388
L387:
	db	"arr[0] *= arr[1] *= arr[2];",10,0
L388:
; Fused expression:    "( L387 , printf )2 "
	push	L387
	call	_printf
	sub	sp, -2
; RPN'ized expression: "arr 0 + *u arr 1 + *u arr 2 + *u *= *= "
; Expanded expression: "(@-76) (@-74) (@-72) *(2) *=(2) *=(2) "
; Fused expression:    "*=(170) *(@-74) *(@-72) *=(170) *(@-76) ax "
	mov	ax, [bp-74]
	mul	word [bp-72]
	mov	[bp-74], ax
	mov	cx, ax
	mov	ax, [bp-76]
	mul	cx
	mov	[bp-76], ax
; RPN'ized expression: "( arr 2 + *u , arr 1 + *u , arr 0 + *u , L389 printf ) "
; Expanded expression: " (@-72) *(2)  (@-74) *(2)  (@-76) *(2)  L389  printf ()8 "
	jmp	L390
L389:
	db	"arr[0]=%d",10,"arr[1]=%d",10,"arr[2]=%d",10,0
L390:
; Fused expression:    "( *(2) (@-72) , *(2) (@-74) , *(2) (@-76) , L389 , printf )8 "
	push	word [bp-72]
	push	word [bp-74]
	push	word [bp-76]
	push	L389
	call	_printf
	sub	sp, -8
; loc     c : (@-80): char
; =
; RPN'ized expression: "127 "
; Expanded expression: "127 "
; Expression value: 127
; Fused expression:    "=(170) *(@-80) 127 "
	mov	ax, 127
	mov	[bp-80], ax
; RPN'ized expression: "( c 127 *= sizeof , c 127 * sizeof , L391 printf ) "
; Expanded expression: " 1u  2u  L391  printf ()6 "
	jmp	L392
L391:
	db	"char c = 127; sizeof(c * 127)=%d; sizeof(c *= 127)=%d",10,0
L392:
; Fused expression:    "( 1u , 2u , L391 , printf )6 "
	push	1
	push	2
	push	L391
	call	_printf
	sub	sp, -6
; RPN'ized expression: "( c 127 * , L393 printf ) "
; Expanded expression: " (@-80) *(-1) 127 *  L393  printf ()4 "
	jmp	L394
L393:
	db	"printf(",34,"%%d\n",34,", c * 127): %d",10,0
L394:
; Fused expression:    "( * *(@-80) 127 , L393 , printf )4 "
	mov	al, [bp-80]
	cbw
	imul	ax, ax, 127
	push	ax
	push	L393
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( c 127 *= , L395 printf ) "
; Expanded expression: " (@-80) 127 *=(-1)  L395  printf ()4 "
	jmp	L396
L395:
	db	"printf(",34,"%%d\n",34,", c *= 127): %d",10,0
L396:
; Fused expression:    "( *=(122) *(@-80) 127 , L395 , printf )4 "
	mov	al, [bp-80]
	cbw
	imul	ax, ax, 127
	mov	[bp-80], al
	cbw
	push	ax
	push	L395
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( 32767 putdecu ) "
; Expanded expression: " 32767  putdecu ()2 "
; Fused expression:    "( 32767 , putdecu )2 "
	push	32767
	call	_putdecu
	sub	sp, -2
; RPN'ized expression: "( 10 putchar ) "
; Expanded expression: " 10  putchar ()2 "
; Fused expression:    "( 10 , putchar )2 "
	push	10
	call	_putchar
	sub	sp, -2
; RPN'ized expression: "( 32768u putdecu ) "
; Expanded expression: " 32768u  putdecu ()2 "
; Fused expression:    "( 32768u , putdecu )2 "
	push	-32768
	call	_putdecu
	sub	sp, -2
; RPN'ized expression: "( 10 putchar ) "
; Expanded expression: " 10  putchar ()2 "
; Fused expression:    "( 10 , putchar )2 "
	push	10
	call	_putchar
	sub	sp, -2
; RPN'ized expression: "( 32769u putdecu ) "
; Expanded expression: " 32769u  putdecu ()2 "
; Fused expression:    "( 32769u , putdecu )2 "
	push	-32767
	call	_putdecu
	sub	sp, -2
; RPN'ized expression: "( 10 putchar ) "
; Expanded expression: " 10  putchar ()2 "
; Fused expression:    "( 10 , putchar )2 "
	push	10
	call	_putchar
	sub	sp, -2
; RPN'ized expression: "( 32770u putdecu ) "
; Expanded expression: " 32770u  putdecu ()2 "
; Fused expression:    "( 32770u , putdecu )2 "
	push	-32766
	call	_putdecu
	sub	sp, -2
; RPN'ized expression: "( 10 putchar ) "
; Expanded expression: " 10  putchar ()2 "
; Fused expression:    "( 10 , putchar )2 "
	push	10
	call	_putchar
	sub	sp, -2
; RPN'ized expression: "( 65533u putdecu ) "
; Expanded expression: " 65533u  putdecu ()2 "
; Fused expression:    "( 65533u , putdecu )2 "
	push	-3
	call	_putdecu
	sub	sp, -2
; RPN'ized expression: "( 10 putchar ) "
; Expanded expression: " 10  putchar ()2 "
; Fused expression:    "( 10 , putchar )2 "
	push	10
	call	_putchar
	sub	sp, -2
; RPN'ized expression: "( 65534u putdecu ) "
; Expanded expression: " 65534u  putdecu ()2 "
; Fused expression:    "( 65534u , putdecu )2 "
	push	-2
	call	_putdecu
	sub	sp, -2
; RPN'ized expression: "( 10 putchar ) "
; Expanded expression: " 10  putchar ()2 "
; Fused expression:    "( 10 , putchar )2 "
	push	10
	call	_putchar
	sub	sp, -2
; RPN'ized expression: "( 65535u , L397 printf ) "
; Expanded expression: " 65535u  L397  printf ()4 "
	jmp	L398
L397:
	db	"%u",10,0
L398:
; Fused expression:    "( 65535u , L397 , printf )4 "
	push	-1
	push	L397
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( L399 puts ) "
; Expanded expression: " L399  puts ()2 "
	jmp	L400
L399:
	db	"press a key...",0
L400:
; Fused expression:    "( L399 , puts )2 "
	push	L399
	call	_puts
	sub	sp, -2
; RPN'ized expression: "( getchar ) "
; Expanded expression: " getchar ()0 "
; Fused expression:    "( getchar )0 "
	call	_getchar
; RPN'ized expression: "0 1 ,b ( arr 3 + *u &u 3 4 ,b arr 0 + *u &u ,b - , 2 L401 ,b printf ) ,b 5 ,b 6 ( arr 0 + *u &u arr 3 + *u &u - , L403 printf ) ,b 7 8 ,b ,b ,b "
; Expanded expression: " (@-70) (@-76) - 2 /  L401  printf ()4 void 5 ,b void  (@-76) (@-70) - 2 /  L403  printf ()4 void 8 ,b ,b "
	jmp	L402
L401:
	db	"&arr[3]-&arr[0]=%d ",0
L402:
	jmp	L404
L403:
	db	"&arr[0]-&arr[3]=%d",10,0
L404:
; Fused expression:    "( - (@-70) (@-76) / ax 2 , L401 , printf )4 void 5 ,b void ( - (@-76) (@-70) / ax 2 , L403 , printf )4 void 8 ,b ,b "
	lea	ax, [bp-70]
	lea	cx, [bp-76]
	sub	ax, cx
	cwd
	mov	cx, 2
	idiv	cx
	push	ax
	push	L401
	call	_printf
	sub	sp, -4
	mov	ax, 5
	lea	ax, [bp-76]
	lea	cx, [bp-70]
	sub	ax, cx
	cwd
	mov	cx, 2
	idiv	cx
	push	ax
	push	L403
	call	_printf
	sub	sp, -4
	mov	ax, 8
; RPN'ized expression: "( arr 16383 + *u &u arr 0 + *u &u - , L405 printf ) "
; Expanded expression: " (@32690) (@-76) - 2 /  L405  printf ()4 "
	jmp	L406
L405:
	db	"&arr[16383]-&arr[0]=%d ",0
L406:
; Fused expression:    "( - (@32690) (@-76) / ax 2 , L405 , printf )4 "
	lea	ax, [bp+32690]
	lea	cx, [bp-76]
	sub	ax, cx
	cwd
	mov	cx, 2
	idiv	cx
	push	ax
	push	L405
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( arr 0 + *u &u arr 16383 + *u &u - , L407 printf ) "
; Expanded expression: " (@-76) (@32690) - 2 /  L407  printf ()4 "
	jmp	L408
L407:
	db	"&arr[0]-&arr[16383]=%d",10,0
L408:
; Fused expression:    "( - (@-76) (@32690) / ax 2 , L407 , printf )4 "
	lea	ax, [bp-76]
	lea	cx, [bp+32690]
	sub	ax, cx
	cwd
	mov	cx, 2
	idiv	cx
	push	ax
	push	L407
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( arr 16384 + *u &u arr 0 + *u &u - , L409 printf ) "
; Expanded expression: " (@32692) (@-76) - 2 /  L409  printf ()4 "
	jmp	L410
L409:
	db	"&arr[16384]-&arr[0]=%d ",0
L410:
; Fused expression:    "( - (@32692) (@-76) / ax 2 , L409 , printf )4 "
	lea	ax, [bp+32692]
	lea	cx, [bp-76]
	sub	ax, cx
	cwd
	mov	cx, 2
	idiv	cx
	push	ax
	push	L409
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( arr 0 + *u &u arr 16384 + *u &u - , L411 printf ) "
; Expanded expression: " (@-76) (@32692) - 2 /  L411  printf ()4 "
	jmp	L412
L411:
	db	"&arr[0]-&arr[16384]=%d",10,0
L412:
; Fused expression:    "( - (@-76) (@32692) / ax 2 , L411 , printf )4 "
	lea	ax, [bp-76]
	lea	cx, [bp+32692]
	sub	ax, cx
	cwd
	mov	cx, 2
	idiv	cx
	push	ax
	push	L411
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( arr 32768u + *u &u arr 0 + *u &u - , L413 printf ) "
; Expanded expression: " (@-76) (@-76) - 2 /  L413  printf ()4 "
	jmp	L414
L413:
	db	"&arr[32768u]-&arr[0]=%d ",0
L414:
; Fused expression:    "( - (@-76) (@-76) / ax 2 , L413 , printf )4 "
	lea	ax, [bp-76]
	lea	cx, [bp-76]
	sub	ax, cx
	cwd
	mov	cx, 2
	idiv	cx
	push	ax
	push	L413
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( arr 0 + *u &u arr 32768u + *u &u - , L415 printf ) "
; Expanded expression: " (@-76) (@-76) - 2 /  L415  printf ()4 "
	jmp	L416
L415:
	db	"&arr[0]-&arr[32768u]=%d",10,0
L416:
; Fused expression:    "( - (@-76) (@-76) / ax 2 , L415 , printf )4 "
	lea	ax, [bp-76]
	lea	cx, [bp-76]
	sub	ax, cx
	cwd
	mov	cx, 2
	idiv	cx
	push	ax
	push	L415
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( arr 32769u + *u &u arr 0 + *u &u - , L417 printf ) "
; Expanded expression: " (@-74) (@-76) - 2 /  L417  printf ()4 "
	jmp	L418
L417:
	db	"&arr[32769u]-&arr[0]=%d ",0
L418:
; Fused expression:    "( - (@-74) (@-76) / ax 2 , L417 , printf )4 "
	lea	ax, [bp-74]
	lea	cx, [bp-76]
	sub	ax, cx
	cwd
	mov	cx, 2
	idiv	cx
	push	ax
	push	L417
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( arr 0 + *u &u arr 32769u + *u &u - , L419 printf ) "
; Expanded expression: " (@-76) (@-74) - 2 /  L419  printf ()4 "
	jmp	L420
L419:
	db	"&arr[0]-&arr[32769u]=%d",10,0
L420:
; Fused expression:    "( - (@-76) (@-74) / ax 2 , L419 , printf )4 "
	lea	ax, [bp-76]
	lea	cx, [bp-74]
	sub	ax, cx
	cwd
	mov	cx, 2
	idiv	cx
	push	ax
	push	L419
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( arr 65535u + *u &u arr 0 + *u &u - , L421 printf ) "
; Expanded expression: " (@-78) (@-76) - 2 /  L421  printf ()4 "
	jmp	L422
L421:
	db	"&arr[65535u]-&arr[0]=%d ",0
L422:
; Fused expression:    "( - (@-78) (@-76) / ax 2 , L421 , printf )4 "
	lea	ax, [bp-78]
	lea	cx, [bp-76]
	sub	ax, cx
	cwd
	mov	cx, 2
	idiv	cx
	push	ax
	push	L421
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( arr 0 + *u &u arr 65535u + *u &u - , L423 printf ) "
; Expanded expression: " (@-76) (@-78) - 2 /  L423  printf ()4 "
	jmp	L424
L423:
	db	"&arr[0]-&arr[65535u]=%d",10,0
L424:
; Fused expression:    "( - (@-76) (@-78) / ax 2 , L423 , printf )4 "
	lea	ax, [bp-76]
	lea	cx, [bp-78]
	sub	ax, cx
	cwd
	mov	cx, 2
	idiv	cx
	push	ax
	push	L423
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( arr 1 -u + *u &u arr 0 + *u &u - , L425 printf ) "
; Expanded expression: " (@-78) (@-76) - 2 /  L425  printf ()4 "
	jmp	L426
L425:
	db	"&arr[-1]-&arr[0]=%d ",0
L426:
; Fused expression:    "( - (@-78) (@-76) / ax 2 , L425 , printf )4 "
	lea	ax, [bp-78]
	lea	cx, [bp-76]
	sub	ax, cx
	cwd
	mov	cx, 2
	idiv	cx
	push	ax
	push	L425
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( arr 0 + *u &u arr 1 -u + *u &u - , L427 printf ) "
; Expanded expression: " (@-76) (@-78) - 2 /  L427  printf ()4 "
	jmp	L428
L427:
	db	"&arr[0]-&arr[-1]=%d",10,0
L428:
; Fused expression:    "( - (@-76) (@-78) / ax 2 , L427 , printf )4 "
	lea	ax, [bp-76]
	lea	cx, [bp-78]
	sub	ax, cx
	cwd
	mov	cx, 2
	idiv	cx
	push	ax
	push	L427
	call	_printf
	sub	sp, -4
; return
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "0 "
	mov	ax, 0
	jmp	L251
; Fused expression:    "0 "
	mov	ax, 0
L251:
	leave
	ret
L250:
	sub	sp, 80
	jmp	L249
; glb Switch : (void) void
_Switch:
	push	bp
	mov	bp, sp
	jmp	L430
L429:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
	mov	ax, 1
	jmp	L434
; {
; default
L433:
; }
	jmp	L432
L434:
	jmp	L433
L432:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
	mov	ax, 1
	jmp	L438
; {
; case
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
	jmp	L439
L438:
	cmp	ax, 0
	jne	L440
L439:
; }
	jmp	L436
L440:
L436:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
	mov	ax, 1
	jmp	L444
; {
; case
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
	jmp	L445
L444:
	cmp	ax, 1
	jne	L446
L445:
; }
	jmp	L442
L446:
L442:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
	mov	ax, 1
	jmp	L450
; {
; {
; loc             i : (@-2): int
; }
; }
	jmp	L448
L450:
L448:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
	mov	ax, 1
	jmp	L454
; {
; RPN'ized expression: "( L456 puts ) "
; Expanded expression: " L456  puts ()2 "
	jmp	L457
L456:
	db	"never printed",0
L457:
; Fused expression:    "( L456 , puts )2 "
	push	L456
	call	_puts
	sub	sp, -2
; case
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
	jmp	L455
L454:
	cmp	ax, 0
	jne	L458
L455:
; RPN'ized expression: "( L460 puts ) "
; Expanded expression: " L460  puts ()2 "
	jmp	L461
L460:
	db	"0",0
L461:
; Fused expression:    "( L460 , puts )2 "
	push	L460
	call	_puts
	sub	sp, -2
; break
	jmp	L452
; case
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
	jmp	L459
L458:
	cmp	ax, 1
	jne	L462
L459:
; RPN'ized expression: "( L464 puts ) "
; Expanded expression: " L464  puts ()2 "
	jmp	L465
L464:
	db	"1",0
L465:
; Fused expression:    "( L464 , puts )2 "
	push	L464
	call	_puts
	sub	sp, -2
; break
	jmp	L452
; case
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
	jmp	L463
L462:
	cmp	ax, 2
	jne	L466
L463:
; RPN'ized expression: "( L468 puts ) "
; Expanded expression: " L468  puts ()2 "
	jmp	L469
L468:
	db	"2",0
L469:
; Fused expression:    "( L468 , puts )2 "
	push	L468
	call	_puts
	sub	sp, -2
; break
	jmp	L452
; default
L453:
; RPN'ized expression: "( L470 puts ) "
; Expanded expression: " L470  puts ()2 "
	jmp	L471
L470:
	db	"default",0
L471:
; Fused expression:    "( L470 , puts )2 "
	push	L470
	call	_puts
	sub	sp, -2
; break
	jmp	L452
; }
	jmp	L452
L466:
	jmp	L453
L452:
; switch
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
; Fused expression:    "2 "
	mov	ax, 2
	jmp	L474
; {
; case
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
	jmp	L475
L474:
	cmp	ax, 2
	jne	L476
L475:
; RPN'ized expression: "( L478 puts ) "
; Expanded expression: " L478  puts ()2 "
	jmp	L479
L478:
	db	"2",0
L479:
; Fused expression:    "( L478 , puts )2 "
	push	L478
	call	_puts
	sub	sp, -2
; break
	jmp	L472
; }
	jmp	L472
L476:
L472:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
	mov	ax, 1
	jmp	L482
; {
; default
L481:
; RPN'ized expression: "( L484 puts ) "
; Expanded expression: " L484  puts ()2 "
	jmp	L485
L484:
	db	"default",0
L485:
; Fused expression:    "( L484 , puts )2 "
	push	L484
	call	_puts
	sub	sp, -2
; break
	jmp	L480
; }
	jmp	L480
L482:
	jmp	L481
L480:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
	mov	ax, 1
	jmp	L488
; {
; default
L487:
; RPN'ized expression: "( L490 puts ) "
; Expanded expression: " L490  puts ()2 "
	jmp	L491
L490:
	db	"default",0
L491:
; Fused expression:    "( L490 , puts )2 "
	push	L490
	call	_puts
	sub	sp, -2
; break
	jmp	L486
; case
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
	jmp	L489
L488:
	cmp	ax, 0
	jne	L492
L489:
; RPN'ized expression: "( L494 puts ) "
; Expanded expression: " L494  puts ()2 "
	jmp	L495
L494:
	db	"0",0
L495:
; Fused expression:    "( L494 , puts )2 "
	push	L494
	call	_puts
	sub	sp, -2
; break
	jmp	L486
; }
	jmp	L486
L492:
	jmp	L487
L486:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
	mov	ax, 1
	jmp	L498
; {
; case
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
	jmp	L499
L498:
	cmp	ax, 0
	jne	L500
L499:
; RPN'ized expression: "( L502 puts ) "
; Expanded expression: " L502  puts ()2 "
	jmp	L503
L502:
	db	"0",0
L503:
; Fused expression:    "( L502 , puts )2 "
	push	L502
	call	_puts
	sub	sp, -2
; break
	jmp	L496
; default
L497:
; RPN'ized expression: "( L504 puts ) "
; Expanded expression: " L504  puts ()2 "
	jmp	L505
L504:
	db	"default",0
L505:
; Fused expression:    "( L504 , puts )2 "
	push	L504
	call	_puts
	sub	sp, -2
; break
	jmp	L496
; }
	jmp	L496
L500:
	jmp	L497
L496:
; switch
; RPN'ized expression: "3 "
; Expanded expression: "3 "
; Expression value: 3
; Fused expression:    "3 "
	mov	ax, 3
	jmp	L508
; {
; case
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
	jmp	L509
L508:
	cmp	ax, 2
	jne	L510
L509:
; RPN'ized expression: "( L512 puts ) "
; Expanded expression: " L512  puts ()2 "
	jmp	L513
L512:
	db	"2 & fallthru",0
L513:
; Fused expression:    "( L512 , puts )2 "
	push	L512
	call	_puts
	sub	sp, -2
; case
; RPN'ized expression: "3 "
; Expanded expression: "3 "
; Expression value: 3
	jmp	L511
L510:
	cmp	ax, 3
	jne	L514
L511:
; RPN'ized expression: "( L516 puts ) "
; Expanded expression: " L516  puts ()2 "
	jmp	L517
L516:
	db	"3 & fallthru",0
L517:
; Fused expression:    "( L516 , puts )2 "
	push	L516
	call	_puts
	sub	sp, -2
; case
; RPN'ized expression: "4 "
; Expanded expression: "4 "
; Expression value: 4
	jmp	L515
L514:
	cmp	ax, 4
	jne	L518
L515:
; RPN'ized expression: "( L520 puts ) "
; Expanded expression: " L520  puts ()2 "
	jmp	L521
L520:
	db	"4 & fallthru",0
L521:
; Fused expression:    "( L520 , puts )2 "
	push	L520
	call	_puts
	sub	sp, -2
; default
L507:
; RPN'ized expression: "( L522 puts ) "
; Expanded expression: " L522  puts ()2 "
	jmp	L523
L522:
	db	"default & fallthru",0
L523:
; Fused expression:    "( L522 , puts )2 "
	push	L522
	call	_puts
	sub	sp, -2
; }
	jmp	L506
L518:
	jmp	L507
L506:
; switch
; RPN'ized expression: "5 "
; Expanded expression: "5 "
; Expression value: 5
; Fused expression:    "5 "
	mov	ax, 5
	jmp	L526
; {
; default
L525:
; RPN'ized expression: "( L528 puts ) "
; Expanded expression: " L528  puts ()2 "
	jmp	L529
L528:
	db	"default & fallthru",0
L529:
; Fused expression:    "( L528 , puts )2 "
	push	L528
	call	_puts
	sub	sp, -2
; case
; RPN'ized expression: "4 "
; Expanded expression: "4 "
; Expression value: 4
	jmp	L527
L526:
	cmp	ax, 4
	jne	L530
L527:
; RPN'ized expression: "( L532 puts ) "
; Expanded expression: " L532  puts ()2 "
	jmp	L533
L532:
	db	"4 & fallthru",0
L533:
; Fused expression:    "( L532 , puts )2 "
	push	L532
	call	_puts
	sub	sp, -2
; case
; RPN'ized expression: "3 "
; Expanded expression: "3 "
; Expression value: 3
	jmp	L531
L530:
	cmp	ax, 3
	jne	L534
L531:
; RPN'ized expression: "( L536 puts ) "
; Expanded expression: " L536  puts ()2 "
	jmp	L537
L536:
	db	"3 & fallthru",0
L537:
; Fused expression:    "( L536 , puts )2 "
	push	L536
	call	_puts
	sub	sp, -2
; case
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
	jmp	L535
L534:
	cmp	ax, 2
	jne	L538
L535:
; RPN'ized expression: "( L540 puts ) "
; Expanded expression: " L540  puts ()2 "
	jmp	L541
L540:
	db	"2 & fallthru",0
L541:
; Fused expression:    "( L540 , puts )2 "
	push	L540
	call	_puts
	sub	sp, -2
; }
	jmp	L524
L538:
	jmp	L525
L524:
; loc     i : (@-2): int
; for
; RPN'ized expression: "i 1 = "
; Expanded expression: "(@-2) 1 =(2) "
; Fused expression:    "=(170) *(@-2) 1 "
	mov	ax, 1
	mov	[bp-2], ax
L542:
; RPN'ized expression: "i 5 <= "
; Expanded expression: "(@-2) *(2) 5 <= "
; Fused expression:    "<= *(@-2) 5 IF! "
	mov	ax, [bp-2]
	cmp	ax, 5
	jg	L545
	jmp	L544
L543:
; RPN'ized expression: "i ++p "
; Expanded expression: "(@-2) ++p(2) "
; Fused expression:    "++p(2) *(@-2) "
	mov	ax, [bp-2]
	inc	word [bp-2]
	jmp	L542
L544:
; switch
; RPN'ized expression: "i "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
	mov	ax, [bp-2]
	jmp	L548
; {
; case
; RPN'ized expression: "3 "
; Expanded expression: "3 "
; Expression value: 3
	jmp	L549
L548:
	cmp	ax, 3
	jne	L550
L549:
; continue
	jmp	L543
; default
L547:
; RPN'ized expression: "( i , L552 printf ) "
; Expanded expression: " (@-2) *(2)  L552  printf ()4 "
	jmp	L553
L552:
	db	"%d",10,0
L553:
; Fused expression:    "( *(2) (@-2) , L552 , printf )4 "
	push	word [bp-2]
	push	L552
	call	_printf
	sub	sp, -4
; break
	jmp	L546
; }
	jmp	L546
L550:
	jmp	L547
L546:
	jmp	L543
L545:
; return
	jmp	L431
L431:
	leave
	ret
L430:
	sub	sp, 2
	jmp	L429

; Syntax/declaration table/stack:
; Bytes used: 2072/19968


; Macro table:
; Macro __SMALLER_C__ = `0x0100`
; Macro __SMALLER_C_16__ = ``
; Macro __SMALLER_C_SCHAR__ = ``
; Macro SOMETHING = `42`
; Macro NOTHING = ``
; Macro SOMETHING_2 = `"42"`
; Bytes used: 105/4096


; Identifier table:
; Ident main
; Ident <something>
; Ident start
; Ident dosputch
; Ident c
; Ident dosgetch
; Ident putchar
; Ident getchar
; Ident gfxmode
; Ident mode
; Ident pokeb
; Ident seg
; Ident ofs
; Ident val
; Ident poke
; Ident peekb
; Ident peek
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
; Ident Switch
; Bytes used: 301/4672

; Next label number: 554
; Compilation succeeded.
