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
	jmp	L6
L5:
; loc     c : (@4): int
mov ah, 2
mov dl, [bp + 4]
int 0x21
L7:
	leave
	ret
L6:
	jmp	L5
; glb dosgetch : (void) int
_dosgetch:
	push	bp
	mov	bp, sp
	jmp	L10
L9:
mov ah, 1
int 0x21
mov ah, 0
L11:
	leave
	ret
L10:
	jmp	L9
; glb putchar : (
; prm     c : int
;     ) int
_putchar:
	push	bp
	mov	bp, sp
	jmp	L14
L13:
; loc     c : (@4): int
; if
; RPN'ized expression: "c 10 == "
; Expanded expression: "(@4) *(2) 10 == "
; Fused expression:    "== *(@4) 10 IF! "
	mov	ax, [bp+4]
	cmp	ax, 10
	jne	L17
; RPN'ized expression: "( 13 dosputch ) "
; Expanded expression: " 13  dosputch ()2 "
; Fused expression:    "( 13 , dosputch )2 "
	push	13
	call	_dosputch
	sub	sp, -2
L17:
; RPN'ized expression: "( c dosputch ) "
; Expanded expression: " (@4) *(2)  dosputch ()2 "
; Fused expression:    "( *(2) (@4) , dosputch )2 "
	push	word [bp+4]
	call	_dosputch
	sub	sp, -2
L15:
	leave
	ret
L14:
	jmp	L13
; glb getchar : (void) int
_getchar:
	push	bp
	mov	bp, sp
	jmp	L20
L19:
; loc     c : (@-2): int
; RPN'ized expression: "c ( dosgetch ) = "
; Expanded expression: "(@-2)  dosgetch ()0 =(2) "
; Fused expression:    "( dosgetch )0 =(170) *(@-2) ax "
	call	_dosgetch
	mov	[bp-2], ax
; if
; RPN'ized expression: "c 13 == "
; Expanded expression: "(@-2) *(2) 13 == "
; Fused expression:    "== *(@-2) 13 IF! "
	mov	ax, [bp-2]
	cmp	ax, 13
	jne	L23
; RPN'ized expression: "c 10 = "
; Expanded expression: "(@-2) 10 =(2) "
; Fused expression:    "=(170) *(@-2) 10 "
	mov	ax, 10
	mov	[bp-2], ax
L23:
; return
; RPN'ized expression: "c "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
	mov	ax, [bp-2]
	jmp	L21
L21:
	leave
	ret
L20:
	sub	sp, 2
	jmp	L19
; glb gfxmode : (
; prm     mode : int
;     ) void
_gfxmode:
	push	bp
	mov	bp, sp
	jmp	L26
L25:
; loc     mode : (@4): int
mov ah, 0
mov al, [bp + 4]
int 0x10
L27:
	leave
	ret
L26:
	jmp	L25
; glb pokeb : (
; prm     seg : unsigned
; prm     ofs : unsigned
; prm     val : unsigned char
;     ) void
_pokeb:
	push	bp
	mov	bp, sp
	jmp	L30
L29:
; loc     seg : (@4): unsigned
; loc     ofs : (@6): unsigned
; loc     val : (@8): unsigned char
push ds
mov  ds, [bp + 4]
mov  bx, [bp + 6]
mov  al, [bp + 8]
mov  [bx], al
pop  ds
L31:
	leave
	ret
L30:
	jmp	L29
; glb poke : (
; prm     seg : unsigned
; prm     ofs : unsigned
; prm     val : unsigned
;     ) void
_poke:
	push	bp
	mov	bp, sp
	jmp	L34
L33:
; loc     seg : (@4): unsigned
; loc     ofs : (@6): unsigned
; loc     val : (@8): unsigned
push ds
mov  ds, [bp + 4]
mov  bx, [bp + 6]
mov  ax, [bp + 8]
mov  [bx], ax
pop  ds
L35:
	leave
	ret
L34:
	jmp	L33
; glb peekb : (
; prm     seg : unsigned
; prm     ofs : unsigned
;     ) unsigned char
_peekb:
	push	bp
	mov	bp, sp
	jmp	L38
L37:
; loc     seg : (@4): unsigned
; loc     ofs : (@6): unsigned
push ds
mov  ds, [bp + 4]
mov  bx, [bp + 6]
mov  al, [bx]
mov  ah, 0
pop  ds
L39:
	leave
	ret
L38:
	jmp	L37
; glb peek : (
; prm     seg : unsigned
; prm     ofs : unsigned
;     ) unsigned
_peek:
	push	bp
	mov	bp, sp
	jmp	L42
L41:
; loc     seg : (@4): unsigned
; loc     ofs : (@6): unsigned
push ds
mov  ds, [bp + 4]
mov  bx, [bp + 6]
mov  ax, [bx]
pop  ds
L43:
	leave
	ret
L42:
	jmp	L41
; glb strcpy : (
; prm     s1 : * char
; prm     s2 : * char
;     ) * char
_strcpy:
	push	bp
	mov	bp, sp
	jmp	L46
L45:
; loc     s1 : (@4): * char
; loc     s2 : (@6): * char
; loc     tmp : (@-2): * char
; RPN'ized expression: "tmp s1 = "
; Expanded expression: "(@-2) (@4) *(2) =(2) "
; Fused expression:    "=(170) *(@-2) *(@4) "
	mov	ax, [bp+4]
	mov	[bp-2], ax
; while
; RPN'ized expression: "s1 ++p *u s2 ++p *u = "
; Expanded expression: "(@4) ++p(2) (@6) ++p(2) *(-1) =(-1) "
L49:
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
	je	L50
	jmp	L49
L50:
; return
; RPN'ized expression: "tmp "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
	mov	ax, [bp-2]
	jmp	L47
L47:
	leave
	ret
L46:
	sub	sp, 2
	jmp	L45
; glb strlen : (
; prm     s : * char
;     ) unsigned
_strlen:
	push	bp
	mov	bp, sp
	jmp	L52
L51:
; loc     s : (@4): * char
; loc     l : (@-2): unsigned
; RPN'ized expression: "l 0 = "
; Expanded expression: "(@-2) 0 =(2) "
; Fused expression:    "=(170) *(@-2) 0 "
	mov	ax, 0
	mov	[bp-2], ax
; while
; RPN'ized expression: "s ++p *u "
; Expanded expression: "(@4) ++p(2) *(-1) "
L55:
; Fused expression:    "++p(2) *(@4) *(-1) ax "
	mov	ax, [bp+4]
	inc	word [bp+4]
	mov	bx, ax
	mov	al, [bx]
	cbw
; JumpIfZero
	test	ax, ax
	je	L56
; RPN'ized expression: "l ++ "
; Expanded expression: "(@-2) ++(2) "
; Fused expression:    "++(2) *(@-2) "
	inc	word [bp-2]
	mov	ax, [bp-2]
	jmp	L55
L56:
; return
; RPN'ized expression: "l "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
	mov	ax, [bp-2]
	jmp	L53
L53:
	leave
	ret
L52:
	sub	sp, 2
	jmp	L51
; glb strchr : (
; prm     s : * char
; prm     c : int
;     ) * char
_strchr:
	push	bp
	mov	bp, sp
	jmp	L58
L57:
; loc     s : (@4): * char
; loc     c : (@6): int
; do
L61:
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
	jne	L64
; return
; RPN'ized expression: "s "
; Expanded expression: "(@4) *(2) "
; Fused expression:    "*(2) (@4) "
	mov	ax, [bp+4]
	jmp	L59
L64:
; }
; while
; RPN'ized expression: "s ++p *u 0 != "
; Expanded expression: "(@4) ++p(2) *(-1) 0 != "
L62:
; Fused expression:    "++p(2) *(@4) != *ax 0 IF "
	mov	ax, [bp+4]
	inc	word [bp+4]
	mov	bx, ax
	mov	al, [bx]
	cbw
	cmp	ax, 0
	jne	L61
L63:
; return
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "0 "
	mov	ax, 0
	jmp	L59
L59:
	leave
	ret
L58:
	jmp	L57
; glb puts : (
; prm     s : * char
;     ) int
_puts:
	push	bp
	mov	bp, sp
	jmp	L67
L66:
; loc     s : (@4): * char
; while
; RPN'ized expression: "s *u "
; Expanded expression: "(@4) *(2) *(-1) "
L70:
; Fused expression:    "*(2) (@4) *(-1) ax "
	mov	ax, [bp+4]
	mov	bx, ax
	mov	al, [bx]
	cbw
; JumpIfZero
	test	ax, ax
	je	L71
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
	jmp	L70
L71:
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
	jmp	L68
L68:
	leave
	ret
L67:
	jmp	L66
; glb isspace : (
; prm     c : int
;     ) int
_isspace:
	push	bp
	mov	bp, sp
	jmp	L73
L72:
; loc     c : (@4): int
; return
; RPN'ized expression: "c 32 == c 12 == || c 10 == || c 13 == || c 9 == || c 11 == || "
; Expanded expression: "(@4) *(2) 32 == [sh||->80] (@4) *(2) 12 == ||[80] _Bool [sh||->79] (@4) *(2) 10 == ||[79] _Bool [sh||->78] (@4) *(2) 13 == ||[78] _Bool [sh||->77] (@4) *(2) 9 == ||[77] _Bool [sh||->76] (@4) *(2) 11 == ||[76] "
; Fused expression:    "== *(@4) 32 [sh||->80] == *(@4) 12 ||[80] _Bool [sh||->79] == *(@4) 10 ||[79] _Bool [sh||->78] == *(@4) 13 ||[78] _Bool [sh||->77] == *(@4) 9 ||[77] _Bool [sh||->76] == *(@4) 11 ||[76] "
	mov	ax, [bp+4]
	cmp	ax, 32
	sete	al
	cbw
; JumpIfNotZero
	test	ax, ax
	jne	L80
	mov	ax, [bp+4]
	cmp	ax, 12
	sete	al
	cbw
L80:
	test	ax, ax
	setne	al
	cbw
; JumpIfNotZero
	test	ax, ax
	jne	L79
	mov	ax, [bp+4]
	cmp	ax, 10
	sete	al
	cbw
L79:
	test	ax, ax
	setne	al
	cbw
; JumpIfNotZero
	test	ax, ax
	jne	L78
	mov	ax, [bp+4]
	cmp	ax, 13
	sete	al
	cbw
L78:
	test	ax, ax
	setne	al
	cbw
; JumpIfNotZero
	test	ax, ax
	jne	L77
	mov	ax, [bp+4]
	cmp	ax, 9
	sete	al
	cbw
L77:
	test	ax, ax
	setne	al
	cbw
; JumpIfNotZero
	test	ax, ax
	jne	L76
	mov	ax, [bp+4]
	cmp	ax, 11
	sete	al
	cbw
L76:
	jmp	L74
L74:
	leave
	ret
L73:
	jmp	L72
; glb isdigit : (
; prm     c : int
;     ) int
_isdigit:
	push	bp
	mov	bp, sp
	jmp	L82
L81:
; loc     c : (@4): int
; return
; RPN'ized expression: "c 48 >= c 57 <= && "
; Expanded expression: "(@4) *(2) 48 >= [sh&&->85] (@4) *(2) 57 <= &&[85] "
; Fused expression:    ">= *(@4) 48 [sh&&->85] <= *(@4) 57 &&[85] "
	mov	ax, [bp+4]
	cmp	ax, 48
	setge	al
	cbw
; JumpIfZero
	test	ax, ax
	je	L85
	mov	ax, [bp+4]
	cmp	ax, 57
	setle	al
	cbw
L85:
	jmp	L83
L83:
	leave
	ret
L82:
	jmp	L81
; glb vprintf : (
; prm     fmt : * char
; prm     vl : * void
;     ) int
_vprintf:
	push	bp
	mov	bp, sp
	jmp	L87
L86:
; loc     fmt : (@4): * char
; loc     vl : (@6): * void
; loc     pp : (@-2): * int
; RPN'ized expression: "pp vl = "
; Expanded expression: "(@-2) (@6) *(2) =(2) "
; Fused expression:    "=(170) *(@-2) *(@6) "
	mov	ax, [bp+6]
	mov	[bp-2], ax
; loc     cnt : (@-4): int
; RPN'ized expression: "cnt 0 = "
; Expanded expression: "(@-4) 0 =(2) "
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
; RPN'ized expression: "minlen 0 = "
; Expanded expression: "(@-30) 0 =(2) "
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
L90:
; RPN'ized expression: "p *u 0 != "
; Expanded expression: "(@-6) *(2) *(-1) 0 != "
; Fused expression:    "*(2) (@-6) != *ax 0 IF! "
	mov	ax, [bp-6]
	mov	bx, ax
	mov	al, [bx]
	cbw
	cmp	ax, 0
	je	L93
	jmp	L92
L91:
; RPN'ized expression: "p ++p "
; Expanded expression: "(@-6) ++p(2) "
; Fused expression:    "++p(2) *(@-6) "
	mov	ax, [bp-6]
	inc	word [bp-6]
	jmp	L90
L92:
; {
; if
; RPN'ized expression: "p *u 37 != p 1 + *u 37 == || "
; Expanded expression: "(@-6) *(2) *(-1) 37 != [sh||->96] (@-6) *(2) 1 + *(-1) 37 == ||[96] "
; Fused expression:    "*(2) (@-6) != *ax 37 [sh||->96] + *(@-6) 1 == *ax 37 ||[96] "
	mov	ax, [bp-6]
	mov	bx, ax
	mov	al, [bx]
	cbw
	cmp	ax, 37
	setne	al
	cbw
; JumpIfNotZero
	test	ax, ax
	jne	L96
	mov	ax, [bp-6]
	inc	ax
	mov	bx, ax
	mov	al, [bx]
	cbw
	cmp	ax, 37
	sete	al
	cbw
L96:
; JumpIfZero
	test	ax, ax
	je	L94
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
	jmp	L91
; }
L94:
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
	jne	L97
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
	jmp	L98
L97:
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
	jne	L99
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
L99:
L98:
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
	je	L101
; {
; while
; RPN'ized expression: "( p *u isdigit ) "
; Expanded expression: " (@-6) *(2) *(-1)  isdigit ()2 "
L103:
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
	je	L104
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
	jmp	L103
L104:
; if
; RPN'ized expression: "msign 0 < "
; Expanded expression: "(@-28) *(2) 0 < "
; Fused expression:    "< *(@-28) 0 IF! "
	mov	ax, [bp-28]
	cmp	ax, 0
	jge	L105
; RPN'ized expression: "minlen minlen -u = "
; Expanded expression: "(@-30) (@-30) *(2) -u =(2) "
; Fused expression:    "*(2) (@-30) -u =(170) *(@-30) ax "
	mov	ax, [bp-30]
	neg	ax
	mov	[bp-30], ax
L105:
; RPN'ized expression: "msign 0 = "
; Expanded expression: "(@-28) 0 =(2) "
; Fused expression:    "=(170) *(@-28) 0 "
	mov	ax, 0
	mov	[bp-28], ax
; }
L101:
; if
; RPN'ized expression: "msign 0 == "
; Expanded expression: "(@-28) *(2) 0 == "
; Fused expression:    "== *(@-28) 0 IF! "
	mov	ax, [bp-28]
	cmp	ax, 0
	jne	L107
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
	jne	L109
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
	jmp	L110
L109:
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
	jne	L111
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
L111:
L110:
; }
L107:
; RPN'ized expression: "phex L113 = "
; Expanded expression: "(@-8) L113 =(2) "
	jmp	L114
L113:
	db	"0123456789abcdef",0
L114:
; Fused expression:    "=(170) *(@-8) L113 "
	mov	ax, L113
	mov	[bp-8], ax
; switch
; RPN'ized expression: "p *u "
; Expanded expression: "(@-6) *(2) *(-1) "
; Fused expression:    "*(2) (@-6) *(-1) ax "
	mov	ax, [bp-6]
	mov	bx, ax
	mov	al, [bx]
	cbw
	jmp	L117
; {
; case
; RPN'ized expression: "99 "
; Expanded expression: "99 "
; Expression value: 99
	jmp	L118
L117:
	cmp	ax, 99
	jne	L119
L118:
; while
; RPN'ized expression: "minlen 1 > "
; Expanded expression: "(@-30) *(2) 1 > "
L121:
; Fused expression:    "> *(@-30) 1 IF! "
	mov	ax, [bp-30]
	cmp	ax, 1
	jle	L122
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
	jmp	L121
L122:
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
L123:
; Fused expression:    "*(2) (@-30) -u > ax 1 IF! "
	mov	ax, [bp-30]
	neg	ax
	cmp	ax, 1
	jle	L124
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
	jmp	L123
L124:
; RPN'ized expression: "cnt ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
	mov	ax, [bp-4]
	inc	word [bp-4]
; break
	jmp	L115
; case
; RPN'ized expression: "115 "
; Expanded expression: "115 "
; Expression value: 115
	jmp	L120
L119:
	cmp	ax, 115
	jne	L125
L120:
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
	je	L127
; RPN'ized expression: "len ( pc strlen ) = "
; Expanded expression: "(@-32)  (@-22) *(2)  strlen ()2 =(2) "
; Fused expression:    "( *(2) (@-22) , strlen )2 =(170) *(@-32) ax "
	push	word [bp-22]
	call	_strlen
	sub	sp, -2
	mov	[bp-32], ax
L127:
; while
; RPN'ized expression: "minlen len > "
; Expanded expression: "(@-30) *(2) (@-32) *(2) > "
L129:
; Fused expression:    "> *(@-30) *(@-32) IF! "
	mov	ax, [bp-30]
	cmp	ax, [bp-32]
	jle	L130
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
	jmp	L129
L130:
; if
; RPN'ized expression: "len "
; Expanded expression: "(@-32) *(2) "
; Fused expression:    "*(2) (@-32) "
	mov	ax, [bp-32]
; JumpIfZero
	test	ax, ax
	je	L131
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
L131:
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
	jmp	L115
; case
; RPN'ized expression: "105 "
; Expanded expression: "105 "
; Expression value: 105
	jmp	L126
L125:
	cmp	ax, 105
	jne	L137
L126:
; case
; RPN'ized expression: "100 "
; Expanded expression: "100 "
; Expression value: 100
	jmp	L138
L137:
	cmp	ax, 100
	jne	L139
L138:
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
L141:
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
L142:
; Fused expression:    "*(2) (@-24) "
	mov	ax, [bp-24]
; JumpIfNotZero
	test	ax, ax
	jne	L141
L143:
; if
; RPN'ized expression: "sign 0 < "
; Expanded expression: "(@-26) *(2) 0 < "
; Fused expression:    "< *(@-26) 0 IF! "
	mov	ax, [bp-26]
	cmp	ax, 0
	jge	L144
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
	jmp	L145
L144:
; else
; if
; RPN'ized expression: "msign 0 > "
; Expanded expression: "(@-28) *(2) 0 > "
; Fused expression:    "> *(@-28) 0 IF! "
	mov	ax, [bp-28]
	cmp	ax, 0
	jle	L146
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
L146:
L145:
; while
; RPN'ized expression: "minlen len > "
; Expanded expression: "(@-30) *(2) (@-32) *(2) > "
L148:
; Fused expression:    "> *(@-30) *(@-32) IF! "
	mov	ax, [bp-30]
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
; RPN'ized expression: "minlen --p "
; Expanded expression: "(@-30) --p(2) "
; Fused expression:    "--p(2) *(@-30) "
	mov	ax, [bp-30]
	dec	word [bp-30]
; }
	jmp	L148
L149:
; while
; RPN'ized expression: "pc *u 0 != "
; Expanded expression: "(@-22) *(2) *(-1) 0 != "
L150:
; Fused expression:    "*(2) (@-22) != *ax 0 IF! "
	mov	ax, [bp-22]
	mov	bx, ax
	mov	al, [bx]
	cbw
	cmp	ax, 0
	je	L151
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
	jmp	L150
L151:
; while
; RPN'ized expression: "minlen -u len > "
; Expanded expression: "(@-30) *(2) -u (@-32) *(2) > "
L152:
; Fused expression:    "*(2) (@-30) -u > ax *(@-32) IF! "
	mov	ax, [bp-30]
	neg	ax
	cmp	ax, [bp-32]
	jle	L153
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
	jmp	L152
L153:
; break
	jmp	L115
; case
; RPN'ized expression: "117 "
; Expanded expression: "117 "
; Expression value: 117
	jmp	L140
L139:
	cmp	ax, 117
	jne	L154
L140:
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
L156:
; {
; loc                 nn : (@-34): unsigned
; RPN'ized expression: "nn n = "
; Expanded expression: "(@-34) (@-24) *(2) =(2) "
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
L157:
; Fused expression:    "*(2) (@-24) "
	mov	ax, [bp-24]
; JumpIfNotZero
	test	ax, ax
	jne	L156
L158:
; if
; RPN'ized expression: "msign 0 > "
; Expanded expression: "(@-28) *(2) 0 > "
; Fused expression:    "> *(@-28) 0 IF! "
	mov	ax, [bp-28]
	cmp	ax, 0
	jle	L159
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
L159:
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
	jmp	L115
; case
; RPN'ized expression: "88 "
; Expanded expression: "88 "
; Expression value: 88
	jmp	L155
L154:
	cmp	ax, 88
	jne	L167
L155:
; RPN'ized expression: "phex L169 = "
; Expanded expression: "(@-8) L169 =(2) "
	jmp	L170
L169:
	db	"0123456789ABCDEF",0
L170:
; Fused expression:    "=(170) *(@-8) L169 "
	mov	ax, L169
	mov	[bp-8], ax
; case
; RPN'ized expression: "112 "
; Expanded expression: "112 "
; Expression value: 112
	jmp	L168
L167:
	cmp	ax, 112
	jne	L171
L168:
; case
; RPN'ized expression: "120 "
; Expanded expression: "120 "
; Expression value: 120
	jmp	L172
L171:
	cmp	ax, 120
	jne	L173
L172:
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
L175:
; {
; loc                 nn : (@-34): unsigned
; RPN'ized expression: "nn n = "
; Expanded expression: "(@-34) (@-24) *(2) =(2) "
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
L176:
; Fused expression:    "*(2) (@-24) "
	mov	ax, [bp-24]
; JumpIfNotZero
	test	ax, ax
	jne	L175
L177:
; while
; RPN'ized expression: "minlen len > "
; Expanded expression: "(@-30) *(2) (@-32) *(2) > "
L178:
; Fused expression:    "> *(@-30) *(@-32) IF! "
	mov	ax, [bp-30]
	cmp	ax, [bp-32]
	jle	L179
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
	jmp	L178
L179:
; while
; RPN'ized expression: "pc *u 0 != "
; Expanded expression: "(@-22) *(2) *(-1) 0 != "
L180:
; Fused expression:    "*(2) (@-22) != *ax 0 IF! "
	mov	ax, [bp-22]
	mov	bx, ax
	mov	al, [bx]
	cbw
	cmp	ax, 0
	je	L181
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
	jmp	L180
L181:
; while
; RPN'ized expression: "minlen -u len > "
; Expanded expression: "(@-30) *(2) -u (@-32) *(2) > "
L182:
; Fused expression:    "*(2) (@-30) -u > ax *(@-32) IF! "
	mov	ax, [bp-30]
	neg	ax
	cmp	ax, [bp-32]
	jle	L183
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
	jmp	L182
L183:
; break
	jmp	L115
; case
; RPN'ized expression: "111 "
; Expanded expression: "111 "
; Expression value: 111
	jmp	L174
L173:
	cmp	ax, 111
	jne	L184
L174:
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
L186:
; {
; loc                 nn : (@-34): unsigned
; RPN'ized expression: "nn n = "
; Expanded expression: "(@-34) (@-24) *(2) =(2) "
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
L187:
; Fused expression:    "*(2) (@-24) "
	mov	ax, [bp-24]
; JumpIfNotZero
	test	ax, ax
	jne	L186
L188:
; while
; RPN'ized expression: "minlen len > "
; Expanded expression: "(@-30) *(2) (@-32) *(2) > "
L189:
; Fused expression:    "> *(@-30) *(@-32) IF! "
	mov	ax, [bp-30]
	cmp	ax, [bp-32]
	jle	L190
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
	jmp	L189
L190:
; while
; RPN'ized expression: "pc *u 0 != "
; Expanded expression: "(@-22) *(2) *(-1) 0 != "
L191:
; Fused expression:    "*(2) (@-22) != *ax 0 IF! "
	mov	ax, [bp-22]
	mov	bx, ax
	mov	al, [bx]
	cbw
	cmp	ax, 0
	je	L192
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
	jmp	L191
L192:
; while
; RPN'ized expression: "minlen -u len > "
; Expanded expression: "(@-30) *(2) -u (@-32) *(2) > "
L193:
; Fused expression:    "*(2) (@-30) -u > ax *(@-32) IF! "
	mov	ax, [bp-30]
	neg	ax
	cmp	ax, [bp-32]
	jle	L194
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
	jmp	L193
L194:
; break
	jmp	L115
; default
L116:
; return
; RPN'ized expression: "1 -u "
; Expanded expression: "-1 "
; Expression value: -1
; Fused expression:    "-1 "
	mov	ax, -1
	jmp	L88
; }
	jmp	L115
L184:
	jmp	L116
L115:
; }
	jmp	L91
L93:
; return
; RPN'ized expression: "cnt "
; Expanded expression: "(@-4) *(2) "
; Fused expression:    "*(2) (@-4) "
	mov	ax, [bp-4]
	jmp	L88
L88:
	leave
	ret
L87:
	sub	sp, 34
	jmp	L86
; glb printf : (
; prm     fmt : * char
; prm     ...
;     ) int
_printf:
	push	bp
	mov	bp, sp
	jmp	L196
L195:
; loc     fmt : (@4): * char
; loc     pp : (@-2): * * void
; RPN'ized expression: "pp fmt &u = "
; Expanded expression: "(@-2) (@4) =(2) "
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
	jmp	L197
L197:
	leave
	ret
L196:
	sub	sp, 2
	jmp	L195
; glb putdec : (
; prm     n : int
;     ) void
_putdec:
	push	bp
	mov	bp, sp
	jmp	L200
L199:
; loc     n : (@4): int
; loc     r : (@-2): int
; if
; RPN'ized expression: "n 0 < "
; Expanded expression: "(@4) *(2) 0 < "
; Fused expression:    "< *(@4) 0 IF! "
	mov	ax, [bp+4]
	cmp	ax, 0
	jge	L203
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
	jmp	L204
L203:
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
L204:
; if
; RPN'ized expression: "n "
; Expanded expression: "(@4) *(2) "
; Fused expression:    "*(2) (@4) "
	mov	ax, [bp+4]
; JumpIfZero
	test	ax, ax
	je	L205
; RPN'ized expression: "( n putdec ) "
; Expanded expression: " (@4) *(2)  putdec ()2 "
; Fused expression:    "( *(2) (@4) , putdec )2 "
	push	word [bp+4]
	call	_putdec
	sub	sp, -2
L205:
; RPN'ized expression: "( 48 r + putchar ) "
; Expanded expression: " 48 (@-2) *(2) +  putchar ()2 "
; Fused expression:    "( + 48 *(@-2) , putchar )2 "
	mov	ax, 48
	add	ax, [bp-2]
	push	ax
	call	_putchar
	sub	sp, -2
L201:
	leave
	ret
L200:
	sub	sp, 2
	jmp	L199
; glb putdecu : (
; prm     n : unsigned
;     ) void
_putdecu:
	push	bp
	mov	bp, sp
	jmp	L208
L207:
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
	je	L211
; RPN'ized expression: "( n putdecu ) "
; Expanded expression: " (@4) *(2)  putdecu ()2 "
; Fused expression:    "( *(2) (@4) , putdecu )2 "
	push	word [bp+4]
	call	_putdecu
	sub	sp, -2
L211:
; RPN'ized expression: "( 48 r + putchar ) "
; Expanded expression: " 48 (@-2) *(2) +  putchar ()2 "
; Fused expression:    "( + 48 *(@-2) , putchar )2 "
	mov	ax, 48
	add	ax, [bp-2]
	push	ax
	call	_putchar
	sub	sp, -2
L209:
	leave
	ret
L208:
	sub	sp, 2
	jmp	L207
; glb fact : (
; prm     x : int
;     ) int
_fact:
	push	bp
	mov	bp, sp
	jmp	L214
L213:
; loc     x : (@4): int
; if
; RPN'ized expression: "x 1 <= "
; Expanded expression: "(@4) *(2) 1 <= "
; Fused expression:    "<= *(@4) 1 IF! "
	mov	ax, [bp+4]
	cmp	ax, 1
	jg	L217
; return
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
	mov	ax, 1
	jmp	L215
L217:
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
	jmp	L215
L215:
	leave
	ret
L214:
	jmp	L213
; glb fib : (
; prm     x : int
;     ) int
_fib:
	push	bp
	mov	bp, sp
	jmp	L220
L219:
; loc     x : (@4): int
; if
; RPN'ized expression: "x 0 <= "
; Expanded expression: "(@4) *(2) 0 <= "
; Fused expression:    "<= *(@4) 0 IF! "
	mov	ax, [bp+4]
	cmp	ax, 0
	jg	L223
; return
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "0 "
	mov	ax, 0
	jmp	L221
	jmp	L224
L223:
; else
; if
; RPN'ized expression: "x 1 == "
; Expanded expression: "(@4) *(2) 1 == "
; Fused expression:    "== *(@4) 1 IF! "
	mov	ax, [bp+4]
	cmp	ax, 1
	jne	L225
; return
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
	mov	ax, 1
	jmp	L221
L225:
L224:
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
	jmp	L221
L221:
	leave
	ret
L220:
	jmp	L219
; glb breakCont : (void) void
_breakCont:
	push	bp
	mov	bp, sp
	jmp	L228
L227:
; loc     i : (@-2): int
; for
; RPN'ized expression: "i 0 = "
; Expanded expression: "(@-2) 0 =(2) "
; Fused expression:    "=(170) *(@-2) 0 "
	mov	ax, 0
	mov	[bp-2], ax
L231:
; RPN'ized expression: "i 10 < "
; Expanded expression: "(@-2) *(2) 10 < "
; Fused expression:    "< *(@-2) 10 IF! "
	mov	ax, [bp-2]
	cmp	ax, 10
	jge	L234
	jmp	L233
L232:
; RPN'ized expression: "i ++p "
; Expanded expression: "(@-2) ++p(2) "
; Fused expression:    "++p(2) *(@-2) "
	mov	ax, [bp-2]
	inc	word [bp-2]
	jmp	L231
L233:
; {
; loc         j : (@-4): int
; RPN'ized expression: "j i = "
; Expanded expression: "(@-4) (@-2) *(2) =(2) "
; Fused expression:    "=(170) *(@-4) *(@-2) "
	mov	ax, [bp-2]
	mov	[bp-4], ax
; if
; RPN'ized expression: "j 1 == "
; Expanded expression: "(@-4) *(2) 1 == "
; Fused expression:    "== *(@-4) 1 IF! "
	mov	ax, [bp-4]
	cmp	ax, 1
	jne	L235
; continue
	jmp	L232
L235:
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
	jne	L237
; break
	jmp	L234
L237:
; }
	jmp	L232
L234:
; RPN'ized expression: "( 10 putchar ) "
; Expanded expression: " 10  putchar ()2 "
; Fused expression:    "( 10 , putchar )2 "
	push	10
	call	_putchar
	sub	sp, -2
L229:
	leave
	ret
L228:
	sub	sp, 4
	jmp	L227
; glb PointerStew : (void) void
_PointerStew:
	push	bp
	mov	bp, sp
	jmp	L240
L239:
; RPN'ized expression: "4 "
; Expanded expression: "4 "
; Expression value: 4
; loc     c : (@-8): [4u] * char
; RPN'ized expression: "4 "
; Expanded expression: "4 "
; Expression value: 4
; loc     cp : (@-16): [4u] * * char
; loc     cpp : (@-18): * * * char
; RPN'ized expression: "cpp cp = "
; Expanded expression: "(@-18) (@-16) =(2) "
; Fused expression:    "=(170) *(@-18) (@-16) "
	lea	ax, [bp-16]
	mov	[bp-18], ax
; RPN'ized expression: "c 0 + *u L243 = "
; Expanded expression: "(@-8) L243 =(2) "
	jmp	L244
L243:
	db	"ENTER",0
L244:
; Fused expression:    "=(170) *(@-8) L243 "
	mov	ax, L243
	mov	[bp-8], ax
; RPN'ized expression: "c 1 + *u L245 = "
; Expanded expression: "(@-6) L245 =(2) "
	jmp	L246
L245:
	db	"NEW",0
L246:
; Fused expression:    "=(170) *(@-6) L245 "
	mov	ax, L245
	mov	[bp-6], ax
; RPN'ized expression: "c 2 + *u L247 = "
; Expanded expression: "(@-4) L247 =(2) "
	jmp	L248
L247:
	db	"POINT",0
L248:
; Fused expression:    "=(170) *(@-4) L247 "
	mov	ax, L247
	mov	[bp-4], ax
; RPN'ized expression: "c 3 + *u L249 = "
; Expanded expression: "(@-2) L249 =(2) "
	jmp	L250
L249:
	db	"FIRST",0
L250:
; Fused expression:    "=(170) *(@-2) L249 "
	mov	ax, L249
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
; RPN'ized expression: "( cpp ++ *u *u , L251 printf ) "
; Expanded expression: " (@-18) 2 +=(2) *(2) *(2)  L251  printf ()4 "
	jmp	L252
L251:
	db	"%s",0
L252:
; Fused expression:    "( +=(170) *(@-18) 2 *(2) ax *(2) ax , L251 , printf )4 "
	mov	ax, [bp-18]
	add	ax, 2
	mov	[bp-18], ax
	mov	bx, ax
	mov	ax, [bx]
	mov	bx, ax
	push	word [bx]
	push	L251
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( cpp ++ *u -- *u 3 + , L253 printf ) "
; Expanded expression: " (@-18) 2 +=(2) 2 -=(2) *(2) 3 +  L253  printf ()4 "
	jmp	L254
L253:
	db	"%s ",0
L254:
; Fused expression:    "( +=(170) *(@-18) 2 -=(170) *ax 2 + *ax 3 , L253 , printf )4 "
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
	push	L253
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( cpp 2 -u + *u *u 3 + , L255 printf ) "
; Expanded expression: " (@-18) *(2) -4 + *(2) *(2) 3 +  L255  printf ()4 "
	jmp	L256
L255:
	db	"%s",0
L256:
; Fused expression:    "( + *(@-18) -4 *(2) ax + *ax 3 , L255 , printf )4 "
	mov	ax, [bp-18]
	add	ax, -4
	mov	bx, ax
	mov	ax, [bx]
	mov	bx, ax
	mov	ax, [bx]
	add	ax, 3
	push	ax
	push	L255
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( cpp 1 -u + *u 1 -u + *u 1 + , L257 printf ) "
; Expanded expression: " (@-18) *(2) -2 + *(2) -2 + *(2) 1 +  L257  printf ()4 "
	jmp	L258
L257:
	db	"%s",10,0
L258:
; Fused expression:    "( + *(@-18) -2 + *ax -2 + *ax 1 , L257 , printf )4 "
	mov	ax, [bp-18]
	add	ax, -2
	mov	bx, ax
	mov	ax, [bx]
	add	ax, -2
	mov	bx, ax
	mov	ax, [bx]
	inc	ax
	push	ax
	push	L257
	call	_printf
	sub	sp, -4
L241:
	leave
	ret
L240:
	sub	sp, 18
	jmp	L239
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
	jmp	L260
L259:
; loc     Str : (@4): * char
; RPN'ized expression: "( Str , L263 printf ) "
; Expanded expression: " (@4) *(2)  L263  printf ()4 "
	jmp	L264
L263:
	db	"%s",0
L264:
; Fused expression:    "( *(2) (@4) , L263 , printf )4 "
	push	word [bp+4]
	push	L263
	call	_printf
	sub	sp, -4
; return
; RPN'ized expression: "Print8 &u "
; Expanded expression: "Print8 "
; Fused expression:    "Print8 "
	mov	ax, _Print8
	jmp	L261
L261:
	leave
	ret
L260:
	jmp	L259
; glb macros : (void) void
_macros:
	push	bp
	mov	bp, sp
	jmp	L266
L265:
; RPN'ized expression: "( L271 , 42 , L269 printf ) "
; Expanded expression: " L271  42  L269  printf ()6 "
	jmp	L272
L271:
	db	"42",0
L272:
	jmp	L270
L269:
	db	"SOMETHING=%d, SOMETHING_2=",34,"%s",34,10,0
L270:
; Fused expression:    "( L271 , 42 , L269 , printf )6 "
	push	L271
	push	42
	push	L269
	call	_printf
	sub	sp, -6
L267:
	leave
	ret
L266:
	jmp	L265
; glb Hola : * char
	align 2
_Hola:
; =
; RPN'ized expression: "L273 "
; Expanded expression: "L273 "
	dw	L273
L273:
	db	"iHola!",0
; glb main : (void) int
_main:
	push	bp
	mov	bp, sp
	jmp	L276
L275:
; RPN'ized expression: "16 "
; Expanded expression: "16 "
; Expression value: 16
; loc     hws : (@-16): [16u] char
; loc     phw : (@-18): * char
; RPN'ized expression: "phw hws = "
; Expanded expression: "(@-18) (@-16) =(2) "
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
; RPN'ized expression: "( ( hws strlen ) , hws , L279 printf ) "
; Expanded expression: "  (@-16)  strlen ()2  (@-16)  L279  printf ()6 "
	jmp	L280
L279:
	db	"hws=",34,"%s",34,", strlen(hws)=%u",10,0
L280:
; Fused expression:    "( ( (@-16) , strlen )2 , (@-16) , L279 , printf )6 "
	lea	ax, [bp-16]
	push	ax
	call	_strlen
	sub	sp, -2
	push	ax
	lea	ax, [bp-16]
	push	ax
	push	L279
	call	_printf
	sub	sp, -6
; RPN'ized expression: "( L281 puts ) "
; Expanded expression: " L281  puts ()2 "
	jmp	L282
L281:
	db	"Buongiorno!",0
L282:
; Fused expression:    "( L281 , puts )2 "
	push	L281
	call	_puts
	sub	sp, -2
; RPN'ized expression: "( Hola puts ) "
; Expanded expression: " Hola *(2)  puts ()2 "
; Fused expression:    "( *(2) Hola , puts )2 "
	push	word [_Hola]
	call	_puts
	sub	sp, -2
; RPN'ized expression: "( 65535u , 32767 -u 1 - , L287 , 122 , 43690u , 32767 , L285 , 97 , L283 printf ) "
; Expanded expression: " 65535u  -32768  L287  122  43690u  32767  L285  97  L283  printf ()18 "
	jmp	L288
L287:
	db	"xyz",0
L288:
	jmp	L286
L285:
	db	"abc",0
L286:
	jmp	L284
L283:
	db	"%% char='%c' str=",34,"%s",34," dec=%d hex=%x %% char='%c' str=",34,"%s",34," dec=%d hex=%X",10,0
L284:
; Fused expression:    "( 65535u , -32768 , L287 , 122 , 43690u , 32767 , L285 , 97 , L283 , printf )18 "
	push	-1
	push	-32768
	push	L287
	push	122
	push	-21846
	push	32767
	push	L285
	push	97
	push	L283
	call	_printf
	sub	sp, -18
; RPN'ized expression: "( 4095 , 4095 , 4095 , L289 printf ) "
; Expanded expression: " 4095  4095  4095  L289  printf ()8 "
	jmp	L290
L289:
	db	"07777=%d, 0xFff=%d, 4095=0%o",10,0
L290:
; Fused expression:    "( 4095 , 4095 , 4095 , L289 , printf )8 "
	push	4095
	push	4095
	push	4095
	push	L289
	call	_printf
	sub	sp, -8
; RPN'ized expression: "( -1 , -1 , 127 , 0 , 127 , 0 , L291 printf ) "
; Expanded expression: " -1  -1  127  0  127  0  L291  printf ()14 "
	jmp	L292
L291:
	db	"'\x0'=%X, '\x7F'=%X, '\0'=%o, '\177'=%o, '\xFf'=%X, '\377'=%o",10,0
L292:
; Fused expression:    "( -1 , -1 , 127 , 0 , 127 , 0 , L291 , printf )14 "
	push	-1
	push	-1
	push	127
	push	0
	push	127
	push	0
	push	L291
	call	_printf
	sub	sp, -14
; RPN'ized expression: "( L297 sizeof , L295 2 + *u , L293 printf ) "
; Expanded expression: " 3u  L295 2 + *(-1)  L293  printf ()6 "
	jmp	L296
L295:
	db	"xyz",0
L296:
	jmp	L294
L293:
	db	34,"xyz",34,"[2]='%c', sizeof ",34,"az",34,"=%u",10,0
L294:
; Fused expression:    "( 3u , + L295 2 *(-1) ax , L293 , printf )6 "
	push	3
	mov	ax, L295
	add	ax, 2
	mov	bx, ax
	mov	al, [bx]
	cbw
	push	ax
	push	L293
	call	_printf
	sub	sp, -6
; RPN'ized expression: "( ( 10 fib ) , ( 7 fact ) , L299 printf ) "
; Expanded expression: "  10  fib ()2   7  fact ()2  L299  printf ()6 "
	jmp	L300
L299:
	db	"fact(7)=%d, fib(10)=%d",10,0
L300:
; Fused expression:    "( ( 10 , fib )2 , ( 7 , fact )2 , L299 , printf )6 "
	push	10
	call	_fib
	sub	sp, -2
	push	ax
	push	7
	call	_fact
	sub	sp, -2
	push	ax
	push	L299
	call	_printf
	sub	sp, -6
; RPN'ized expression: "( L303 , L301 printf ) "
; Expanded expression: " L303  L301  printf ()4 "
	jmp	L304
L303:
	db	"pea",0,"nut",0
L304:
	jmp	L302
L301:
	db	"printf(",34,"pea\0nut",34,"): ",34,"%s",34,10,0
L302:
; Fused expression:    "( L303 , L301 , printf )4 "
	push	L303
	push	L301
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( L307 3 + , L305 printf ) "
; Expanded expression: " L307 3 +  L305  printf ()4 "
	jmp	L308
L307:
	db	"peanut",0
L308:
	jmp	L306
L305:
	db	"printf(",34,"peanut",34," + 3): ",34,"%s",34,10,0
L306:
; Fused expression:    "( + L307 3 , L305 , printf )4 "
	mov	ax, L307
	add	ax, 3
	push	ax
	push	L305
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( L309 puts ) "
; Expanded expression: " L309  puts ()2 "
	jmp	L310
L309:
	db	"press a key...",0
L310:
; Fused expression:    "( L309 , puts )2 "
	push	L309
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
; RPN'ized expression: "L311 sizeof "
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
; RPN'ized expression: "pgb L313 = "
; Expanded expression: "(@-42) L313 =(2) "
	jmp	L314
L313:
	db	"Green on Black!",0
L314:
; Fused expression:    "=(170) *(@-42) L313 "
	mov	ax, L313
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
L315:
; RPN'ized expression: "y 25 < "
; Expanded expression: "(@-46) *(2) 25 < "
; Fused expression:    "< *(@-46) 25 IF! "
	mov	ax, [bp-46]
	cmp	ax, 25
	jge	L318
	jmp	L317
L316:
; RPN'ized expression: "y ++p "
; Expanded expression: "(@-46) ++p(2) "
; Fused expression:    "++p(2) *(@-46) "
	mov	ax, [bp-46]
	inc	word [bp-46]
	jmp	L315
L317:
; for
; RPN'ized expression: "x 0 = "
; Expanded expression: "(@-44) 0 =(2) "
; Fused expression:    "=(170) *(@-44) 0 "
	mov	ax, 0
	mov	[bp-44], ax
L319:
; RPN'ized expression: "x 80 < "
; Expanded expression: "(@-44) *(2) 80 < "
; Fused expression:    "< *(@-44) 80 IF! "
	mov	ax, [bp-44]
	cmp	ax, 80
	jge	L322
	jmp	L321
L320:
; RPN'ized expression: "x ++p "
; Expanded expression: "(@-44) ++p(2) "
; Fused expression:    "++p(2) *(@-44) "
	mov	ax, [bp-44]
	inc	word [bp-44]
	jmp	L319
L321:
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
	jmp	L320
L322:
	jmp	L316
L318:
; RPN'ized expression: "( L323 puts ) "
; Expanded expression: " L323  puts ()2 "
	jmp	L324
L323:
	db	"press a key once for graphics mode and then another time for text mode...",0
L324:
; Fused expression:    "( L323 , puts )2 "
	push	L323
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
L325:
; RPN'ized expression: "y 200 < "
; Expanded expression: "(@-46) *(2) 200 < "
; Fused expression:    "< *(@-46) 200 IF! "
	mov	ax, [bp-46]
	cmp	ax, 200
	jge	L328
	jmp	L327
L326:
; RPN'ized expression: "y ++p "
; Expanded expression: "(@-46) ++p(2) "
; Fused expression:    "++p(2) *(@-46) "
	mov	ax, [bp-46]
	inc	word [bp-46]
	jmp	L325
L327:
; for
; RPN'ized expression: "x 0 = "
; Expanded expression: "(@-44) 0 =(2) "
; Fused expression:    "=(170) *(@-44) 0 "
	mov	ax, 0
	mov	[bp-44], ax
L329:
; RPN'ized expression: "x 320 < "
; Expanded expression: "(@-44) *(2) 320 < "
; Fused expression:    "< *(@-44) 320 IF! "
	mov	ax, [bp-44]
	cmp	ax, 320
	jge	L332
	jmp	L331
L330:
; RPN'ized expression: "x ++p "
; Expanded expression: "(@-44) ++p(2) "
; Fused expression:    "++p(2) *(@-44) "
	mov	ax, [bp-44]
	inc	word [bp-44]
	jmp	L329
L331:
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
	jmp	L330
L332:
	jmp	L326
L328:
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
; RPN'ized expression: "( <something335> sizeof , L333 printf ) "
; Expanded expression: " 1u  L333  printf ()4 "
	jmp	L334
L333:
	db	"sizeof(char)=%u",10,0
L334:
; Fused expression:    "( 1u , L333 , printf )4 "
	push	1
	push	L333
	call	_printf
	sub	sp, -4
; loc     <something> : int
; RPN'ized expression: "( <something338> sizeof , L336 printf ) "
; Expanded expression: " 2u  L336  printf ()4 "
	jmp	L337
L336:
	db	"sizeof(int)=%u",10,0
L337:
; Fused expression:    "( 2u , L336 , printf )4 "
	push	2
	push	L336
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( , L339 printf 3 "
; Expanded expression: "  L339 printf 3 "
; Expression value: 3
; loc     <something> : [3u] char
; RPN'ized expression: "( <something341> sizeof , L339 printf ) "
; Expanded expression: " 3u  L339  printf ()4 "
	jmp	L340
L339:
	db	"sizeof(char[3])=%u",10,0
L340:
; Fused expression:    "( 3u , L339 , printf )4 "
	push	3
	push	L339
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( , L342 printf 5 "
; Expanded expression: "  L342 printf 5 "
; Expression value: 5
; loc     <something> : [5u] * () char
; RPN'ized expression: "( <something344> sizeof , L342 printf ) "
; Expanded expression: " 10u  L342  printf ()4 "
	jmp	L343
L342:
	db	"sizeof(char(*[5])())=%u",10,0
L343:
; Fused expression:    "( 10u , L342 , printf )4 "
	push	10
	push	L342
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( , L345 printf 3 "
; Expanded expression: "  L345 printf 3 "
; Expression value: 3
; loc     <something> : [3u] int
; RPN'ized expression: "( , L345 printf <something349> sizeof "
; Expanded expression: "  L345 printf 6u "
; Expression value: 6u
; loc     <something> : [6u] int
; RPN'ized expression: "( , L345 printf <something348> sizeof "
; Expanded expression: "  L345 printf 12u "
; Expression value: 12u
; loc     <something> : [12u] int
; RPN'ized expression: "( <something347> sizeof , L345 printf ) "
; Expanded expression: " 24u  L345  printf ()4 "
	jmp	L346
L345:
	db	"sizeof(int[sizeof(int[sizeof(int[3])])])=%u",10,0
L346:
; Fused expression:    "( 24u , L345 , printf )4 "
	push	24
	push	L345
	call	_printf
	sub	sp, -4
; RPN'ized expression: "3 "
; Expanded expression: "3 "
; Expression value: 3
; loc     <something> : [3u] int
; RPN'ized expression: "<something352> sizeof "
; Expanded expression: "6u "
; Expression value: 6u
; loc     <something> : [6u] int
; RPN'ized expression: "<something351> sizeof "
; Expanded expression: "12u "
; Expression value: 12u
; loc     <something> : [12u] int
; RPN'ized expression: "<something350> sizeof "
; Expanded expression: "24u "
; Expression value: 24u
; loc     yui : (@-70): [24u] char
; loc     <something> : * () char
; RPN'ized expression: "( <something355> sizeof , L353 printf ) "
; Expanded expression: " 2u  L353  printf ()4 "
	jmp	L354
L353:
	db	"sizeof(char(*)())=%u",10,0
L354:
; Fused expression:    "( 2u , L353 , printf )4 "
	push	2
	push	L353
	call	_printf
	sub	sp, -4
; loc     <something> : () char
; RPN'ized expression: "( <something358> sizeof , L356 printf ) "
; Expanded expression: " 2u  L356  printf ()4 "
	jmp	L357
L356:
	db	"sizeof(char())=%u",10,0
L357:
; Fused expression:    "( 2u , L356 , printf )4 "
	push	2
	push	L356
	call	_printf
	sub	sp, -4
; loc     <something> : () * char
; RPN'ized expression: "( <something361> sizeof , L359 printf ) "
; Expanded expression: " 2u  L359  printf ()4 "
	jmp	L360
L359:
	db	"sizeof(char*())=%u",10,0
L360:
; Fused expression:    "( 2u , L359 , printf )4 "
	push	2
	push	L359
	call	_printf
	sub	sp, -4
; loc     <something> : () int
; RPN'ized expression: "( <something364> sizeof , L362 printf ) "
; Expanded expression: " 2u  L362  printf ()4 "
	jmp	L363
L362:
	db	"sizeof(int())=%u",10,0
L363:
; Fused expression:    "( 2u , L362 , printf )4 "
	push	2
	push	L362
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( main sizeof , L365 printf ) "
; Expanded expression: " 2u  L365  printf ()4 "
	jmp	L366
L365:
	db	"sizeof main=%u",10,0
L366:
; Fused expression:    "( 2u , L365 , printf )4 "
	push	2
	push	L365
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( ( main ) sizeof , L367 printf ) "
; Expanded expression: " 2u  L367  printf ()4 "
	jmp	L368
L367:
	db	"sizeof main()=%u",10,0
L368:
; Fused expression:    "( 2u , L367 , printf )4 "
	push	2
	push	L367
	call	_printf
	sub	sp, -4
; loc     <something> : () void
; RPN'ized expression: "( <something371> sizeof , L369 printf ) "
; Expanded expression: " 2u  L369  printf ()4 "
	jmp	L370
L369:
	db	"sizeof(void())=%u",10,0
L370:
; Fused expression:    "( 2u , L369 , printf )4 "
	push	2
	push	L369
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( , L372 printf 7 "
; Expanded expression: "  L372 printf 7 "
; Expression value: 7
; loc     <something> : [7u] char
; RPN'ized expression: "( <something374> sizeof , L372 printf ) "
; Expanded expression: " 7u  L372  printf ()4 "
	jmp	L373
L372:
	db	"sizeof(char[7])=%u",10,0
L373:
; Fused expression:    "( 7u , L372 , printf )4 "
	push	7
	push	L372
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( , L379 , L377 , L375 printf 3 "
; Expanded expression: "  L379  L377  L375 printf 3 "
; Expression value: 3
; loc     <something> : [3u] int
; RPN'ized expression: "( , L379 , L377 , L375 printf <something384> sizeof 5 "
; Expanded expression: "  L379  L377  L375 printf <something384> sizeof 5 "
; Expression value: 5
; loc     <something> : [5u] int
; RPN'ized expression: "( , L379 , L377 , L375 printf <something384> sizeof <something385> sizeof + "
; Expanded expression: "  L379  L377  L375 printf 16u "
; Expression value: 16u
; loc     <something> : [16u] int
; RPN'ized expression: "( , L379 , L377 , L375 printf <something383> sizeof "
; Expanded expression: "  L379  L377  L375 printf 32u "
; Expression value: 32u
; loc     <something> : [32u] int
; RPN'ized expression: "( , L379 , L377 , L375 printf <something382> sizeof 7 "
; Expanded expression: "  L379  L377  L375 printf <something382> sizeof 7 "
; Expression value: 7
; loc     <something> : [7u] int
; RPN'ized expression: "( , L379 , L377 , L375 printf <something382> sizeof <something388> sizeof 9 "
; Expanded expression: "  L379  L377  L375 printf <something382> sizeof <something388> sizeof 9 "
; Expression value: 9
; loc     <something> : [9u] int
; RPN'ized expression: "( , L379 , L377 , L375 printf <something382> sizeof <something388> sizeof <something389> sizeof + "
; Expanded expression: "  L379  L377  L375 printf <something382> sizeof 32u "
; Expression value: 32u
; loc     <something> : [32u] int
; RPN'ized expression: "( , L379 , L377 , L375 printf <something382> sizeof <something387> sizeof "
; Expanded expression: "  L379  L377  L375 printf <something382> sizeof 64u "
; Expression value: 64u
; loc     <something> : [64u] int
; RPN'ized expression: "( , L379 , L377 , L375 printf <something382> sizeof <something386> sizeof + "
; Expanded expression: "  L379  L377  L375 printf 192u "
; Expression value: 192u
; loc     <something> : [192u] int
; RPN'ized expression: "( <something381> sizeof , L379 , L377 , L375 printf ) "
; Expanded expression: " 384u  L379  L377  L375  printf ()8 "
	jmp	L380
L379:
	db	"sizeof(int[sizeof(int[sizeof(int[7])+sizeof(int[9])])])])",0
L380:
	jmp	L378
L377:
	db	"sizeof(int[sizeof(int[sizeof(int[sizeof(int[3])+sizeof(int[5])])])+",0
L378:
	jmp	L376
L375:
	db	"%s%s=%u",10,0
L376:
; Fused expression:    "( 384u , L379 , L377 , L375 , printf )8 "
	push	384
	push	L379
	push	L377
	push	L375
	call	_printf
	sub	sp, -8
; RPN'ized expression: "( PointerStew ) "
; Expanded expression: " PointerStew ()0 "
; Fused expression:    "( PointerStew )0 "
	call	_PointerStew
; RPN'ized expression: "( L398 ( L396 ( L394 ( L392 ( L390 Print8 ) ) ) ) ) "
; Expanded expression: " L398   L396   L394   L392   L390  Print8 ()2 ()2 ()2 ()2 ()2 "
	jmp	L399
L398:
	db	10,0
L399:
	jmp	L397
L396:
	db	"!",0
L397:
	jmp	L395
L394:
	db	"world",0
L395:
	jmp	L393
L392:
	db	" ",0
L393:
	jmp	L391
L390:
	db	"hello",0
L391:
; Fused expression:    "( L398 , ( L396 , ( L394 , ( L392 , ( L390 , Print8 )2 )2 )2 )2 )2 "
	push	L398
	push	L396
	push	L394
	push	L392
	push	L390
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
; RPN'ized expression: "( L400 printf ) "
; Expanded expression: " L400  printf ()2 "
	jmp	L401
L400:
	db	"These are six concatenated string literals!",10,0
L401:
; Fused expression:    "( L400 , printf )2 "
	push	L400
	call	_printf
	sub	sp, -2
; RPN'ized expression: "( L404 , L402 printf ) "
; Expanded expression: " L404  L402  printf ()4 "
	jmp	L405
L404:
	db	"ABC012abc",0
L405:
	jmp	L403
L402:
	db	34,"\x41\x42\x43\60\61\62abc",34," = ",34,"%s",34,10,0
L403:
; Fused expression:    "( L404 , L402 , printf )4 "
	push	L404
	push	L402
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( L406 puts ) "
; Expanded expression: " L406  puts ()2 "
	jmp	L407
L406:
	db	"press a key...",0
L407:
; Fused expression:    "( L406 , puts )2 "
	push	L406
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
; RPN'ized expression: "p arr 1 + = "
; Expanded expression: "(@-78) (@-74) =(2) "
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
; RPN'ized expression: "( p 1 -= *u , L408 printf ) "
; Expanded expression: " (@-78) 2 -=(2) *(2)  L408  printf ()4 "
	jmp	L409
L408:
	db	"arr[0]=%d",10,0
L409:
; Fused expression:    "( -=(170) *(@-78) 2 *(2) ax , L408 , printf )4 "
	mov	ax, [bp-78]
	sub	ax, 2
	mov	[bp-78], ax
	mov	bx, ax
	push	word [bx]
	push	L408
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( p 1 += *u , L410 printf ) "
; Expanded expression: " (@-78) 2 +=(2) *(2)  L410  printf ()4 "
	jmp	L411
L410:
	db	"arr[1]=%d",10,0
L411:
; Fused expression:    "( +=(170) *(@-78) 2 *(2) ax , L410 , printf )4 "
	mov	ax, [bp-78]
	add	ax, 2
	mov	[bp-78], ax
	mov	bx, ax
	push	word [bx]
	push	L410
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( p 1 += *u , L412 printf ) "
; Expanded expression: " (@-78) 2 +=(2) *(2)  L412  printf ()4 "
	jmp	L413
L412:
	db	"arr[2]=%d",10,0
L413:
; Fused expression:    "( +=(170) *(@-78) 2 *(2) ax , L412 , printf )4 "
	mov	ax, [bp-78]
	add	ax, 2
	mov	[bp-78], ax
	mov	bx, ax
	push	word [bx]
	push	L412
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( L414 printf ) "
; Expanded expression: " L414  printf ()2 "
	jmp	L415
L414:
	db	"arr[0] *= arr[1] *= arr[2];",10,0
L415:
; Fused expression:    "( L414 , printf )2 "
	push	L414
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
; RPN'ized expression: "( arr 2 + *u , arr 1 + *u , arr 0 + *u , L416 printf ) "
; Expanded expression: " (@-72) *(2)  (@-74) *(2)  (@-76) *(2)  L416  printf ()8 "
	jmp	L417
L416:
	db	"arr[0]=%d",10,"arr[1]=%d",10,"arr[2]=%d",10,0
L417:
; Fused expression:    "( *(2) (@-72) , *(2) (@-74) , *(2) (@-76) , L416 , printf )8 "
	push	word [bp-72]
	push	word [bp-74]
	push	word [bp-76]
	push	L416
	call	_printf
	sub	sp, -8
; loc     c : (@-80): char
; RPN'ized expression: "c 127 = "
; Expanded expression: "(@-80) 127 =(-1) "
; Fused expression:    "=(170) *(@-80) 127 "
	mov	ax, 127
	mov	[bp-80], ax
; RPN'ized expression: "( c 127 *= sizeof , c 127 * sizeof , L418 printf ) "
; Expanded expression: " 1u  2u  L418  printf ()6 "
	jmp	L419
L418:
	db	"char c = 127; sizeof(c * 127)=%d; sizeof(c *= 127)=%d",10,0
L419:
; Fused expression:    "( 1u , 2u , L418 , printf )6 "
	push	1
	push	2
	push	L418
	call	_printf
	sub	sp, -6
; RPN'ized expression: "( c 127 * , L420 printf ) "
; Expanded expression: " (@-80) *(-1) 127 *  L420  printf ()4 "
	jmp	L421
L420:
	db	"printf(",34,"%%d\n",34,", c * 127): %d",10,0
L421:
; Fused expression:    "( * *(@-80) 127 , L420 , printf )4 "
	mov	al, [bp-80]
	cbw
	imul	ax, ax, 127
	push	ax
	push	L420
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( c 127 *= , L422 printf ) "
; Expanded expression: " (@-80) 127 *=(-1)  L422  printf ()4 "
	jmp	L423
L422:
	db	"printf(",34,"%%d\n",34,", c *= 127): %d",10,0
L423:
; Fused expression:    "( *=(122) *(@-80) 127 , L422 , printf )4 "
	mov	al, [bp-80]
	cbw
	imul	ax, ax, 127
	mov	[bp-80], al
	cbw
	push	ax
	push	L422
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
; RPN'ized expression: "( 65535u , L424 printf ) "
; Expanded expression: " 65535u  L424  printf ()4 "
	jmp	L425
L424:
	db	"%u",10,0
L425:
; Fused expression:    "( 65535u , L424 , printf )4 "
	push	-1
	push	L424
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( L426 puts ) "
; Expanded expression: " L426  puts ()2 "
	jmp	L427
L426:
	db	"press a key...",0
L427:
; Fused expression:    "( L426 , puts )2 "
	push	L426
	call	_puts
	sub	sp, -2
; RPN'ized expression: "( getchar ) "
; Expanded expression: " getchar ()0 "
; Fused expression:    "( getchar )0 "
	call	_getchar
; RPN'ized expression: "0 1 ,b ( arr 3 + *u &u 3 4 ,b arr 0 + *u &u ,b - , 2 L428 ,b printf ) ,b 5 ,b 6 ( arr 0 + *u &u arr 3 + *u &u - , L430 printf ) ,b 7 8 ,b ,b ,b "
; Expanded expression: " (@-70) (@-76) - 2 /  L428  printf ()4 void 5 ,b void  (@-76) (@-70) - 2 /  L430  printf ()4 void 8 ,b ,b "
	jmp	L429
L428:
	db	"&arr[3]-&arr[0]=%d ",0
L429:
	jmp	L431
L430:
	db	"&arr[0]-&arr[3]=%d",10,0
L431:
; Fused expression:    "( - (@-70) (@-76) / ax 2 , L428 , printf )4 void 5 ,b void ( - (@-76) (@-70) / ax 2 , L430 , printf )4 void 8 ,b ,b "
	lea	ax, [bp-70]
	lea	cx, [bp-76]
	sub	ax, cx
	cwd
	mov	cx, 2
	idiv	cx
	push	ax
	push	L428
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
	push	L430
	call	_printf
	sub	sp, -4
	mov	ax, 8
; RPN'ized expression: "( arr 16383 + *u &u arr 0 + *u &u - , L432 printf ) "
; Expanded expression: " (@32690) (@-76) - 2 /  L432  printf ()4 "
	jmp	L433
L432:
	db	"&arr[16383]-&arr[0]=%d ",0
L433:
; Fused expression:    "( - (@32690) (@-76) / ax 2 , L432 , printf )4 "
	lea	ax, [bp+32690]
	lea	cx, [bp-76]
	sub	ax, cx
	cwd
	mov	cx, 2
	idiv	cx
	push	ax
	push	L432
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( arr 0 + *u &u arr 16383 + *u &u - , L434 printf ) "
; Expanded expression: " (@-76) (@32690) - 2 /  L434  printf ()4 "
	jmp	L435
L434:
	db	"&arr[0]-&arr[16383]=%d",10,0
L435:
; Fused expression:    "( - (@-76) (@32690) / ax 2 , L434 , printf )4 "
	lea	ax, [bp-76]
	lea	cx, [bp+32690]
	sub	ax, cx
	cwd
	mov	cx, 2
	idiv	cx
	push	ax
	push	L434
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( arr 16384 + *u &u arr 0 + *u &u - , L436 printf ) "
; Expanded expression: " (@32692) (@-76) - 2 /  L436  printf ()4 "
	jmp	L437
L436:
	db	"&arr[16384]-&arr[0]=%d ",0
L437:
; Fused expression:    "( - (@32692) (@-76) / ax 2 , L436 , printf )4 "
	lea	ax, [bp+32692]
	lea	cx, [bp-76]
	sub	ax, cx
	cwd
	mov	cx, 2
	idiv	cx
	push	ax
	push	L436
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( arr 0 + *u &u arr 16384 + *u &u - , L438 printf ) "
; Expanded expression: " (@-76) (@32692) - 2 /  L438  printf ()4 "
	jmp	L439
L438:
	db	"&arr[0]-&arr[16384]=%d",10,0
L439:
; Fused expression:    "( - (@-76) (@32692) / ax 2 , L438 , printf )4 "
	lea	ax, [bp-76]
	lea	cx, [bp+32692]
	sub	ax, cx
	cwd
	mov	cx, 2
	idiv	cx
	push	ax
	push	L438
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( arr 32768u + *u &u arr 0 + *u &u - , L440 printf ) "
; Expanded expression: " (@-76) (@-76) - 2 /  L440  printf ()4 "
	jmp	L441
L440:
	db	"&arr[32768u]-&arr[0]=%d ",0
L441:
; Fused expression:    "( - (@-76) (@-76) / ax 2 , L440 , printf )4 "
	lea	ax, [bp-76]
	lea	cx, [bp-76]
	sub	ax, cx
	cwd
	mov	cx, 2
	idiv	cx
	push	ax
	push	L440
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( arr 0 + *u &u arr 32768u + *u &u - , L442 printf ) "
; Expanded expression: " (@-76) (@-76) - 2 /  L442  printf ()4 "
	jmp	L443
L442:
	db	"&arr[0]-&arr[32768u]=%d",10,0
L443:
; Fused expression:    "( - (@-76) (@-76) / ax 2 , L442 , printf )4 "
	lea	ax, [bp-76]
	lea	cx, [bp-76]
	sub	ax, cx
	cwd
	mov	cx, 2
	idiv	cx
	push	ax
	push	L442
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( arr 32769u + *u &u arr 0 + *u &u - , L444 printf ) "
; Expanded expression: " (@-74) (@-76) - 2 /  L444  printf ()4 "
	jmp	L445
L444:
	db	"&arr[32769u]-&arr[0]=%d ",0
L445:
; Fused expression:    "( - (@-74) (@-76) / ax 2 , L444 , printf )4 "
	lea	ax, [bp-74]
	lea	cx, [bp-76]
	sub	ax, cx
	cwd
	mov	cx, 2
	idiv	cx
	push	ax
	push	L444
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( arr 0 + *u &u arr 32769u + *u &u - , L446 printf ) "
; Expanded expression: " (@-76) (@-74) - 2 /  L446  printf ()4 "
	jmp	L447
L446:
	db	"&arr[0]-&arr[32769u]=%d",10,0
L447:
; Fused expression:    "( - (@-76) (@-74) / ax 2 , L446 , printf )4 "
	lea	ax, [bp-76]
	lea	cx, [bp-74]
	sub	ax, cx
	cwd
	mov	cx, 2
	idiv	cx
	push	ax
	push	L446
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( arr 65535u + *u &u arr 0 + *u &u - , L448 printf ) "
; Expanded expression: " (@-78) (@-76) - 2 /  L448  printf ()4 "
	jmp	L449
L448:
	db	"&arr[65535u]-&arr[0]=%d ",0
L449:
; Fused expression:    "( - (@-78) (@-76) / ax 2 , L448 , printf )4 "
	lea	ax, [bp-78]
	lea	cx, [bp-76]
	sub	ax, cx
	cwd
	mov	cx, 2
	idiv	cx
	push	ax
	push	L448
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( arr 0 + *u &u arr 65535u + *u &u - , L450 printf ) "
; Expanded expression: " (@-76) (@-78) - 2 /  L450  printf ()4 "
	jmp	L451
L450:
	db	"&arr[0]-&arr[65535u]=%d",10,0
L451:
; Fused expression:    "( - (@-76) (@-78) / ax 2 , L450 , printf )4 "
	lea	ax, [bp-76]
	lea	cx, [bp-78]
	sub	ax, cx
	cwd
	mov	cx, 2
	idiv	cx
	push	ax
	push	L450
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( arr 1 -u + *u &u arr 0 + *u &u - , L452 printf ) "
; Expanded expression: " (@-78) (@-76) - 2 /  L452  printf ()4 "
	jmp	L453
L452:
	db	"&arr[-1]-&arr[0]=%d ",0
L453:
; Fused expression:    "( - (@-78) (@-76) / ax 2 , L452 , printf )4 "
	lea	ax, [bp-78]
	lea	cx, [bp-76]
	sub	ax, cx
	cwd
	mov	cx, 2
	idiv	cx
	push	ax
	push	L452
	call	_printf
	sub	sp, -4
; RPN'ized expression: "( arr 0 + *u &u arr 1 -u + *u &u - , L454 printf ) "
; Expanded expression: " (@-76) (@-78) - 2 /  L454  printf ()4 "
	jmp	L455
L454:
	db	"&arr[0]-&arr[-1]=%d",10,0
L455:
; Fused expression:    "( - (@-76) (@-78) / ax 2 , L454 , printf )4 "
	lea	ax, [bp-76]
	lea	cx, [bp-78]
	sub	ax, cx
	cwd
	mov	cx, 2
	idiv	cx
	push	ax
	push	L454
	call	_printf
	sub	sp, -4
; return
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "0 "
	mov	ax, 0
	jmp	L277
; Fused expression:    "0 "
	mov	ax, 0
L277:
	leave
	ret
L276:
	sub	sp, 80
	jmp	L275
; glb Switch : (void) void
_Switch:
	push	bp
	mov	bp, sp
	jmp	L457
L456:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
	mov	ax, 1
	jmp	L462
; {
; default
L461:
; }
	jmp	L460
L462:
	jmp	L461
L460:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
	mov	ax, 1
	jmp	L466
; {
; case
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
	jmp	L467
L466:
	cmp	ax, 0
	jne	L468
L467:
; }
	jmp	L464
L468:
L464:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
	mov	ax, 1
	jmp	L472
; {
; case
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
	jmp	L473
L472:
	cmp	ax, 1
	jne	L474
L473:
; }
	jmp	L470
L474:
L470:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
	mov	ax, 1
	jmp	L478
; {
; {
; loc             i : (@-2): int
; }
; }
	jmp	L476
L478:
L476:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
	mov	ax, 1
	jmp	L482
; {
; RPN'ized expression: "( L484 puts ) "
; Expanded expression: " L484  puts ()2 "
	jmp	L485
L484:
	db	"never printed",0
L485:
; Fused expression:    "( L484 , puts )2 "
	push	L484
	call	_puts
	sub	sp, -2
; case
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
	jmp	L483
L482:
	cmp	ax, 0
	jne	L486
L483:
; RPN'ized expression: "( L488 puts ) "
; Expanded expression: " L488  puts ()2 "
	jmp	L489
L488:
	db	"0",0
L489:
; Fused expression:    "( L488 , puts )2 "
	push	L488
	call	_puts
	sub	sp, -2
; break
	jmp	L480
; case
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
	jmp	L487
L486:
	cmp	ax, 1
	jne	L490
L487:
; RPN'ized expression: "( L492 puts ) "
; Expanded expression: " L492  puts ()2 "
	jmp	L493
L492:
	db	"1",0
L493:
; Fused expression:    "( L492 , puts )2 "
	push	L492
	call	_puts
	sub	sp, -2
; break
	jmp	L480
; case
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
	jmp	L491
L490:
	cmp	ax, 2
	jne	L494
L491:
; RPN'ized expression: "( L496 puts ) "
; Expanded expression: " L496  puts ()2 "
	jmp	L497
L496:
	db	"2",0
L497:
; Fused expression:    "( L496 , puts )2 "
	push	L496
	call	_puts
	sub	sp, -2
; break
	jmp	L480
; default
L481:
; RPN'ized expression: "( L498 puts ) "
; Expanded expression: " L498  puts ()2 "
	jmp	L499
L498:
	db	"default",0
L499:
; Fused expression:    "( L498 , puts )2 "
	push	L498
	call	_puts
	sub	sp, -2
; break
	jmp	L480
; }
	jmp	L480
L494:
	jmp	L481
L480:
; switch
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
; Fused expression:    "2 "
	mov	ax, 2
	jmp	L502
; {
; case
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
	jmp	L503
L502:
	cmp	ax, 2
	jne	L504
L503:
; RPN'ized expression: "( L506 puts ) "
; Expanded expression: " L506  puts ()2 "
	jmp	L507
L506:
	db	"2",0
L507:
; Fused expression:    "( L506 , puts )2 "
	push	L506
	call	_puts
	sub	sp, -2
; break
	jmp	L500
; }
	jmp	L500
L504:
L500:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
	mov	ax, 1
	jmp	L510
; {
; default
L509:
; RPN'ized expression: "( L512 puts ) "
; Expanded expression: " L512  puts ()2 "
	jmp	L513
L512:
	db	"default",0
L513:
; Fused expression:    "( L512 , puts )2 "
	push	L512
	call	_puts
	sub	sp, -2
; break
	jmp	L508
; }
	jmp	L508
L510:
	jmp	L509
L508:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
	mov	ax, 1
	jmp	L516
; {
; default
L515:
; RPN'ized expression: "( L518 puts ) "
; Expanded expression: " L518  puts ()2 "
	jmp	L519
L518:
	db	"default",0
L519:
; Fused expression:    "( L518 , puts )2 "
	push	L518
	call	_puts
	sub	sp, -2
; break
	jmp	L514
; case
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
	jmp	L517
L516:
	cmp	ax, 0
	jne	L520
L517:
; RPN'ized expression: "( L522 puts ) "
; Expanded expression: " L522  puts ()2 "
	jmp	L523
L522:
	db	"0",0
L523:
; Fused expression:    "( L522 , puts )2 "
	push	L522
	call	_puts
	sub	sp, -2
; break
	jmp	L514
; }
	jmp	L514
L520:
	jmp	L515
L514:
; switch
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
	mov	ax, 1
	jmp	L526
; {
; case
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
	jmp	L527
L526:
	cmp	ax, 0
	jne	L528
L527:
; RPN'ized expression: "( L530 puts ) "
; Expanded expression: " L530  puts ()2 "
	jmp	L531
L530:
	db	"0",0
L531:
; Fused expression:    "( L530 , puts )2 "
	push	L530
	call	_puts
	sub	sp, -2
; break
	jmp	L524
; default
L525:
; RPN'ized expression: "( L532 puts ) "
; Expanded expression: " L532  puts ()2 "
	jmp	L533
L532:
	db	"default",0
L533:
; Fused expression:    "( L532 , puts )2 "
	push	L532
	call	_puts
	sub	sp, -2
; break
	jmp	L524
; }
	jmp	L524
L528:
	jmp	L525
L524:
; switch
; RPN'ized expression: "3 "
; Expanded expression: "3 "
; Expression value: 3
; Fused expression:    "3 "
	mov	ax, 3
	jmp	L536
; {
; case
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
	jmp	L537
L536:
	cmp	ax, 2
	jne	L538
L537:
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
; case
; RPN'ized expression: "3 "
; Expanded expression: "3 "
; Expression value: 3
	jmp	L539
L538:
	cmp	ax, 3
	jne	L542
L539:
; RPN'ized expression: "( L544 puts ) "
; Expanded expression: " L544  puts ()2 "
	jmp	L545
L544:
	db	"3 & fallthru",0
L545:
; Fused expression:    "( L544 , puts )2 "
	push	L544
	call	_puts
	sub	sp, -2
; case
; RPN'ized expression: "4 "
; Expanded expression: "4 "
; Expression value: 4
	jmp	L543
L542:
	cmp	ax, 4
	jne	L546
L543:
; RPN'ized expression: "( L548 puts ) "
; Expanded expression: " L548  puts ()2 "
	jmp	L549
L548:
	db	"4 & fallthru",0
L549:
; Fused expression:    "( L548 , puts )2 "
	push	L548
	call	_puts
	sub	sp, -2
; default
L535:
; RPN'ized expression: "( L550 puts ) "
; Expanded expression: " L550  puts ()2 "
	jmp	L551
L550:
	db	"default & fallthru",0
L551:
; Fused expression:    "( L550 , puts )2 "
	push	L550
	call	_puts
	sub	sp, -2
; }
	jmp	L534
L546:
	jmp	L535
L534:
; switch
; RPN'ized expression: "5 "
; Expanded expression: "5 "
; Expression value: 5
; Fused expression:    "5 "
	mov	ax, 5
	jmp	L554
; {
; default
L553:
; RPN'ized expression: "( L556 puts ) "
; Expanded expression: " L556  puts ()2 "
	jmp	L557
L556:
	db	"default & fallthru",0
L557:
; Fused expression:    "( L556 , puts )2 "
	push	L556
	call	_puts
	sub	sp, -2
; case
; RPN'ized expression: "4 "
; Expanded expression: "4 "
; Expression value: 4
	jmp	L555
L554:
	cmp	ax, 4
	jne	L558
L555:
; RPN'ized expression: "( L560 puts ) "
; Expanded expression: " L560  puts ()2 "
	jmp	L561
L560:
	db	"4 & fallthru",0
L561:
; Fused expression:    "( L560 , puts )2 "
	push	L560
	call	_puts
	sub	sp, -2
; case
; RPN'ized expression: "3 "
; Expanded expression: "3 "
; Expression value: 3
	jmp	L559
L558:
	cmp	ax, 3
	jne	L562
L559:
; RPN'ized expression: "( L564 puts ) "
; Expanded expression: " L564  puts ()2 "
	jmp	L565
L564:
	db	"3 & fallthru",0
L565:
; Fused expression:    "( L564 , puts )2 "
	push	L564
	call	_puts
	sub	sp, -2
; case
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
	jmp	L563
L562:
	cmp	ax, 2
	jne	L566
L563:
; RPN'ized expression: "( L568 puts ) "
; Expanded expression: " L568  puts ()2 "
	jmp	L569
L568:
	db	"2 & fallthru",0
L569:
; Fused expression:    "( L568 , puts )2 "
	push	L568
	call	_puts
	sub	sp, -2
; }
	jmp	L552
L566:
	jmp	L553
L552:
; loc     i : (@-2): int
; for
; RPN'ized expression: "i 1 = "
; Expanded expression: "(@-2) 1 =(2) "
; Fused expression:    "=(170) *(@-2) 1 "
	mov	ax, 1
	mov	[bp-2], ax
L570:
; RPN'ized expression: "i 5 <= "
; Expanded expression: "(@-2) *(2) 5 <= "
; Fused expression:    "<= *(@-2) 5 IF! "
	mov	ax, [bp-2]
	cmp	ax, 5
	jg	L573
	jmp	L572
L571:
; RPN'ized expression: "i ++p "
; Expanded expression: "(@-2) ++p(2) "
; Fused expression:    "++p(2) *(@-2) "
	mov	ax, [bp-2]
	inc	word [bp-2]
	jmp	L570
L572:
; switch
; RPN'ized expression: "i "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
	mov	ax, [bp-2]
	jmp	L576
; {
; case
; RPN'ized expression: "3 "
; Expanded expression: "3 "
; Expression value: 3
	jmp	L577
L576:
	cmp	ax, 3
	jne	L578
L577:
; continue
	jmp	L571
; default
L575:
; RPN'ized expression: "( i , L580 printf ) "
; Expanded expression: " (@-2) *(2)  L580  printf ()4 "
	jmp	L581
L580:
	db	"%d",10,0
L581:
; Fused expression:    "( *(2) (@-2) , L580 , printf )4 "
	push	word [bp-2]
	push	L580
	call	_printf
	sub	sp, -4
; break
	jmp	L574
; }
	jmp	L574
L578:
	jmp	L575
L574:
	jmp	L571
L573:
; return
	jmp	L458
L458:
	leave
	ret
L457:
	sub	sp, 2
	jmp	L456

; Syntax/declaration table/stack:
; Bytes used: 2072/20736


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
; Bytes used: 301/4752

; Next label number: 582
; Compilation succeeded.
