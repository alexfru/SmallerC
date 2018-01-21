bits 16

org 0x100
; glb main : (void) int
; glb start : (void) void
section .text
	global	_start
_start:
	push	bp
	mov	bp, sp
	;sub	sp,          0
; RPN'ized expression: "( main ) "
; Expanded expression: " main ()0 "
; Fused expression:    "( main )0 "
	call	_main
L1:
	leave
	ret

; RPN'ized expression: "40 25 * "
; Expanded expression: "1000 "
; Expression value: 1000
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
; glb snake : [1000u] [2u] unsigned
section .data
	align 2
	global	_snake
_snake:
	times	4000 db 0

; glb length : unsigned
section .data
	align 2
	global	_length
_length:
	times	2 db 0

; glb direction : unsigned
section .data
	align 2
	global	_direction
_direction:
	times	2 db 0

; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
; glb target : [2u] unsigned
section .data
	align 2
	global	_target
_target:
	times	4 db 0

; glb score : unsigned
section .data
	align 2
	global	_score
_score:
	times	2 db 0

; glb BiosKeyAvailable : (void) int
section .text
	global	_BiosKeyAvailable
_BiosKeyAvailable:
	push	bp
	mov	bp, sp
	;sub	sp,          0
mov   ah, 1
int   0x16
setnz al
cbw
L3:
	leave
	ret

; glb BiosReadKey : (void) unsigned
section .text
	global	_BiosReadKey
_BiosReadKey:
	push	bp
	mov	bp, sp
	;sub	sp,          0
mov ah, 0
int 0x16
L5:
	leave
	ret

; glb BiosSetGfxMode : (
; prm     mode : unsigned
;     ) void
section .text
	global	_BiosSetGfxMode
_BiosSetGfxMode:
	push	bp
	mov	bp, sp
	;sub	sp,          0
; loc     mode : (@4) : unsigned
mov ah, 0
mov al, [bp + 4]
int 0x10
L7:
	leave
	ret

; glb pokeb : (
; prm     seg : unsigned
; prm     ofs : unsigned
; prm     val : unsigned char
;     ) void
section .text
	global	_pokeb
_pokeb:
	push	bp
	mov	bp, sp
	;sub	sp,          0
; loc     seg : (@4) : unsigned
; loc     ofs : (@6) : unsigned
; loc     val : (@8) : unsigned char
push ds
mov  ds, [bp + 4]
mov  bx, [bp + 6]
mov  al, [bp + 8]
mov  [bx], al
pop  ds
L9:
	leave
	ret

; glb poke : (
; prm     seg : unsigned
; prm     ofs : unsigned
; prm     val : unsigned
;     ) void
section .text
	global	_poke
_poke:
	push	bp
	mov	bp, sp
	;sub	sp,          0
; loc     seg : (@4) : unsigned
; loc     ofs : (@6) : unsigned
; loc     val : (@8) : unsigned
push ds
mov  ds, [bp + 4]
mov  bx, [bp + 6]
mov  ax, [bp + 8]
mov  [bx], ax
pop  ds
L11:
	leave
	ret

; glb peekb : (
; prm     seg : unsigned
; prm     ofs : unsigned
;     ) unsigned char
section .text
	global	_peekb
_peekb:
	push	bp
	mov	bp, sp
	;sub	sp,          0
; loc     seg : (@4) : unsigned
; loc     ofs : (@6) : unsigned
push ds
mov  ds, [bp + 4]
mov  bx, [bp + 6]
mov  al, [bx]
mov  ah, 0
pop  ds
L13:
	leave
	ret

; glb peek : (
; prm     seg : unsigned
; prm     ofs : unsigned
;     ) unsigned
section .text
	global	_peek
_peek:
	push	bp
	mov	bp, sp
	;sub	sp,          0
; loc     seg : (@4) : unsigned
; loc     ofs : (@6) : unsigned
push ds
mov  ds, [bp + 4]
mov  bx, [bp + 6]
mov  ax, [bx]
pop  ds
L15:
	leave
	ret

; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
; glb BiosGetTicks : (
; prm     ticks : * unsigned
;     ) void
section .text
	global	_BiosGetTicks
_BiosGetTicks:
	push	bp
	mov	bp, sp
	 sub	sp,          6
; loc     ticks : (@4) : * unsigned
; loc     low : (@-2) : unsigned
; loc     high1 : (@-4) : unsigned
; loc     high2 : (@-6) : unsigned
; RPN'ized expression: "high2 ( 110 , 64 peek ) = "
; Expanded expression: "(@-6)  110  64  peek ()4 =(2) "
; Fused expression:    "( 110 , 64 , peek )4 =(170) *(@-6) ax "
	push	110
	push	64
	call	_peek
	sub	sp, -4
	mov	[bp-6], ax
; do
L19:
; {
; RPN'ized expression: "high1 high2 = "
; Expanded expression: "(@-4) (@-6) *(2) =(2) "
; Fused expression:    "=(170) *(@-4) *(@-6) "
	mov	ax, [bp-6]
	mov	[bp-4], ax
; RPN'ized expression: "low ( 108 , 64 peek ) = "
; Expanded expression: "(@-2)  108  64  peek ()4 =(2) "
; Fused expression:    "( 108 , 64 , peek )4 =(170) *(@-2) ax "
	push	108
	push	64
	call	_peek
	sub	sp, -4
	mov	[bp-2], ax
; RPN'ized expression: "high2 ( 110 , 64 peek ) = "
; Expanded expression: "(@-6)  110  64  peek ()4 =(2) "
; Fused expression:    "( 110 , 64 , peek )4 =(170) *(@-6) ax "
	push	110
	push	64
	call	_peek
	sub	sp, -4
	mov	[bp-6], ax
; }
; while
; RPN'ized expression: "high1 high2 != "
; Expanded expression: "(@-4) *(2) (@-6) *(2) != "
L20:
; Fused expression:    "!= *(@-4) *(@-6) IF "
	mov	ax, [bp-4]
	cmp	ax, [bp-6]
	jne	L19
L21:
; RPN'ized expression: "ticks 0 + *u low = "
; Expanded expression: "(@4) *(2) 0 + (@-2) *(2) =(2) "
; Fused expression:    "+ *(@4) 0 =(170) *ax *(@-2) "
	mov	ax, [bp+4]
	mov	bx, ax
	mov	ax, [bp-2]
	mov	[bx], ax
; RPN'ized expression: "ticks 1 + *u high2 = "
; Expanded expression: "(@4) *(2) 2 + (@-6) *(2) =(2) "
; Fused expression:    "+ *(@4) 2 =(170) *ax *(@-6) "
	mov	ax, [bp+4]
	add	ax, 2
	mov	bx, ax
	mov	ax, [bp-6]
	mov	[bx], ax
L17:
	leave
	ret

; glb delay : (
; prm     milliseconds : unsigned
;     ) void
section .text
	global	_delay
_delay:
	push	bp
	mov	bp, sp
	 sub	sp,         10
; loc     milliseconds : (@4) : unsigned
; loc     tcnt : (@-2) : unsigned
; RPN'ized expression: "tcnt milliseconds 27 + 55 / = "
; Expanded expression: "(@-2) (@4) *(2) 27 + 55 /u =(2) "
; Fused expression:    "+ *(@4) 27 /u ax 55 =(170) *(@-2) ax "
	mov	ax, [bp+4]
	add	ax, 27
	mov	dx, 0
	mov	cx, 55
	div	cx
	mov	[bp-2], ax
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
; loc     ticks : (@-10) : [2u] [2u] unsigned
; RPN'ized expression: "( ticks 0 + *u BiosGetTicks ) "
; Expanded expression: " (@-10)  BiosGetTicks ()2 "
; Fused expression:    "( (@-10) , BiosGetTicks )2 "
	lea	ax, [bp-10]
	push	ax
	call	_BiosGetTicks
	sub	sp, -2
; for
L24:
; {
; RPN'ized expression: "( ticks 1 + *u BiosGetTicks ) "
; Expanded expression: " (@-6)  BiosGetTicks ()2 "
; Fused expression:    "( (@-6) , BiosGetTicks )2 "
	lea	ax, [bp-6]
	push	ax
	call	_BiosGetTicks
	sub	sp, -2
; if
; RPN'ized expression: "ticks 1 + *u 0 + *u ticks 0 + *u 0 + *u < "
; Expanded expression: "(@-6) *(2) (@-10) *(2) <u "
; Fused expression:    "<u *(@-6) *(@-10) IF! "
	mov	ax, [bp-6]
	cmp	ax, [bp-10]
	jae	L28
; RPN'ized expression: "ticks 1 + *u 1 + *u -- "
; Expanded expression: "(@-4) --(2) "
; Fused expression:    "--(2) *(@-4) "
	dec	word [bp-4]
	mov	ax, [bp-4]
L28:
; RPN'ized expression: "ticks 1 + *u 0 + *u ticks 0 + *u 0 + *u -= "
; Expanded expression: "(@-6) (@-10) *(2) -=(2) "
; Fused expression:    "-=(170) *(@-6) *(@-10) "
	mov	ax, [bp-6]
	sub	ax, [bp-10]
	mov	[bp-6], ax
; RPN'ized expression: "ticks 1 + *u 1 + *u ticks 0 + *u 1 + *u -= "
; Expanded expression: "(@-4) (@-8) *(2) -=(2) "
; Fused expression:    "-=(170) *(@-4) *(@-8) "
	mov	ax, [bp-4]
	sub	ax, [bp-8]
	mov	[bp-4], ax
; if
; RPN'ized expression: "ticks 1 + *u 0 + *u tcnt >= ticks 1 + *u 1 + *u || "
; Expanded expression: "(@-6) *(2) (@-2) *(2) >=u [sh||->32] (@-4) *(2) _Bool ||[32] "
; Fused expression:    ">=u *(@-6) *(@-2) [sh||->32] *(2) (@-4) _Bool ||[32]  "
	mov	ax, [bp-6]
	cmp	ax, [bp-2]
	setae	al
	cbw
; JumpIfNotZero
	test	ax, ax
	jne	L32
	mov	ax, [bp-4]
	test	ax, ax
	setne	al
	cbw
L32:
; JumpIfZero
	test	ax, ax
	je	L30
; break
	jmp	L27
L30:
; }
	jmp	L24
L27:
L22:
	leave
	ret

; glb lineh : (
; prm     x : unsigned
; prm     y : unsigned
; prm     w : unsigned
; prm     chr : unsigned
; prm     color : unsigned
;     ) void
section .text
	global	_lineh
_lineh:
	push	bp
	mov	bp, sp
	 sub	sp,          4
; loc     x : (@4) : unsigned
; loc     y : (@6) : unsigned
; loc     w : (@8) : unsigned
; loc     chr : (@10) : unsigned
; loc     color : (@12) : unsigned
; loc     ofs : (@-2) : unsigned
; RPN'ized expression: "ofs y 40 * x + 2 * = "
; Expanded expression: "(@-2) (@6) *(2) 40 * (@4) *(2) + 2 * =(2) "
; Fused expression:    "* *(@6) 40 + ax *(@4) * ax 2 =(170) *(@-2) ax "
	mov	ax, [bp+6]
	imul	ax, ax, 40
	add	ax, [bp+4]
	imul	ax, ax, 2
	mov	[bp-2], ax
; loc     v : (@-4) : unsigned
; RPN'ized expression: "v color 8 << chr | = "
; Expanded expression: "(@-4) (@12) *(2) 8 << (@10) *(2) | =(2) "
; Fused expression:    "<< *(@12) 8 | ax *(@10) =(170) *(@-4) ax "
	mov	ax, [bp+12]
	shl	ax, 8
	or	ax, [bp+10]
	mov	[bp-4], ax
; while
; RPN'ized expression: "w --p "
; Expanded expression: "(@8) --p(2) "
L35:
; Fused expression:    "--p(2) *(@8)  "
	mov	ax, [bp+8]
	dec	word [bp+8]
; JumpIfZero
	test	ax, ax
	je	L36
; {
; RPN'ized expression: "( v , ofs , 47104u poke ) "
; Expanded expression: " (@-4) *(2)  (@-2) *(2)  47104u  poke ()6 "
; Fused expression:    "( *(2) (@-4) , *(2) (@-2) , 47104u , poke )6 "
	push	word [bp-4]
	push	word [bp-2]
	push	-18432
	call	_poke
	sub	sp, -6
; RPN'ized expression: "ofs 2 += "
; Expanded expression: "(@-2) 2 +=(2) "
; Fused expression:    "+=(170) *(@-2) 2 "
	mov	ax, [bp-2]
	add	ax, 2
	mov	[bp-2], ax
; }
	jmp	L35
L36:
L33:
	leave
	ret

; glb linev : (
; prm     x : unsigned
; prm     y : unsigned
; prm     h : unsigned
; prm     chr : unsigned
; prm     color : unsigned
;     ) void
section .text
	global	_linev
_linev:
	push	bp
	mov	bp, sp
	 sub	sp,          4
; loc     x : (@4) : unsigned
; loc     y : (@6) : unsigned
; loc     h : (@8) : unsigned
; loc     chr : (@10) : unsigned
; loc     color : (@12) : unsigned
; loc     ofs : (@-2) : unsigned
; RPN'ized expression: "ofs y 40 * x + 2 * = "
; Expanded expression: "(@-2) (@6) *(2) 40 * (@4) *(2) + 2 * =(2) "
; Fused expression:    "* *(@6) 40 + ax *(@4) * ax 2 =(170) *(@-2) ax "
	mov	ax, [bp+6]
	imul	ax, ax, 40
	add	ax, [bp+4]
	imul	ax, ax, 2
	mov	[bp-2], ax
; loc     v : (@-4) : unsigned
; RPN'ized expression: "v color 8 << chr | = "
; Expanded expression: "(@-4) (@12) *(2) 8 << (@10) *(2) | =(2) "
; Fused expression:    "<< *(@12) 8 | ax *(@10) =(170) *(@-4) ax "
	mov	ax, [bp+12]
	shl	ax, 8
	or	ax, [bp+10]
	mov	[bp-4], ax
; while
; RPN'ized expression: "h --p "
; Expanded expression: "(@8) --p(2) "
L39:
; Fused expression:    "--p(2) *(@8)  "
	mov	ax, [bp+8]
	dec	word [bp+8]
; JumpIfZero
	test	ax, ax
	je	L40
; {
; RPN'ized expression: "( v , ofs , 47104u poke ) "
; Expanded expression: " (@-4) *(2)  (@-2) *(2)  47104u  poke ()6 "
; Fused expression:    "( *(2) (@-4) , *(2) (@-2) , 47104u , poke )6 "
	push	word [bp-4]
	push	word [bp-2]
	push	-18432
	call	_poke
	sub	sp, -6
; RPN'ized expression: "ofs 40 2 * += "
; Expanded expression: "(@-2) 80 +=(2) "
; Fused expression:    "+=(170) *(@-2) 80 "
	mov	ax, [bp-2]
	add	ax, 80
	mov	[bp-2], ax
; }
	jmp	L39
L40:
L37:
	leave
	ret

; glb box : (
; prm     x : unsigned
; prm     y : unsigned
; prm     w : unsigned
; prm     h : unsigned
; prm     chr : unsigned
; prm     color : unsigned
; prm     solid : unsigned
;     ) void
section .text
	global	_box
_box:
	push	bp
	mov	bp, sp
	;sub	sp,          0
; loc     x : (@4) : unsigned
; loc     y : (@6) : unsigned
; loc     w : (@8) : unsigned
; loc     h : (@10) : unsigned
; loc     chr : (@12) : unsigned
; loc     color : (@14) : unsigned
; loc     solid : (@16) : unsigned
; if
; RPN'ized expression: "solid "
; Expanded expression: "(@16) *(2) "
; Fused expression:    "*(2) (@16)  "
	mov	ax, [bp+16]
; JumpIfZero
	test	ax, ax
	je	L43
; {
; while
; RPN'ized expression: "h --p "
; Expanded expression: "(@10) --p(2) "
L45:
; Fused expression:    "--p(2) *(@10)  "
	mov	ax, [bp+10]
	dec	word [bp+10]
; JumpIfZero
	test	ax, ax
	je	L46
; RPN'ized expression: "( color , chr , w , y ++p , x lineh ) "
; Expanded expression: " (@14) *(2)  (@12) *(2)  (@8) *(2)  (@6) ++p(2)  (@4) *(2)  lineh ()10 "
; Fused expression:    "( *(2) (@14) , *(2) (@12) , *(2) (@8) , ++p(2) *(@6) , *(2) (@4) , lineh )10 "
	push	word [bp+14]
	push	word [bp+12]
	push	word [bp+8]
	mov	ax, [bp+6]
	inc	word [bp+6]
	push	ax
	push	word [bp+4]
	call	_lineh
	sub	sp, -10
	jmp	L45
L46:
; }
	jmp	L44
L43:
; else
; {
; RPN'ized expression: "( color , chr , w , y , x lineh ) "
; Expanded expression: " (@14) *(2)  (@12) *(2)  (@8) *(2)  (@6) *(2)  (@4) *(2)  lineh ()10 "
; Fused expression:    "( *(2) (@14) , *(2) (@12) , *(2) (@8) , *(2) (@6) , *(2) (@4) , lineh )10 "
	push	word [bp+14]
	push	word [bp+12]
	push	word [bp+8]
	push	word [bp+6]
	push	word [bp+4]
	call	_lineh
	sub	sp, -10
; RPN'ized expression: "( color , chr , h , y , x w + 1 - linev ) "
; Expanded expression: " (@14) *(2)  (@12) *(2)  (@10) *(2)  (@6) *(2)  (@4) *(2) (@8) *(2) + 1 -  linev ()10 "
; Fused expression:    "( *(2) (@14) , *(2) (@12) , *(2) (@10) , *(2) (@6) , + *(@4) *(@8) - ax 1 , linev )10 "
	push	word [bp+14]
	push	word [bp+12]
	push	word [bp+10]
	push	word [bp+6]
	mov	ax, [bp+4]
	add	ax, [bp+8]
	dec	ax
	push	ax
	call	_linev
	sub	sp, -10
; RPN'ized expression: "( color , chr , w , y h + 1 - , x lineh ) "
; Expanded expression: " (@14) *(2)  (@12) *(2)  (@8) *(2)  (@6) *(2) (@10) *(2) + 1 -  (@4) *(2)  lineh ()10 "
; Fused expression:    "( *(2) (@14) , *(2) (@12) , *(2) (@8) , + *(@6) *(@10) - ax 1 , *(2) (@4) , lineh )10 "
	push	word [bp+14]
	push	word [bp+12]
	push	word [bp+8]
	mov	ax, [bp+6]
	add	ax, [bp+10]
	dec	ax
	push	ax
	push	word [bp+4]
	call	_lineh
	sub	sp, -10
; RPN'ized expression: "( color , chr , h , y , x linev ) "
; Expanded expression: " (@14) *(2)  (@12) *(2)  (@10) *(2)  (@6) *(2)  (@4) *(2)  linev ()10 "
; Fused expression:    "( *(2) (@14) , *(2) (@12) , *(2) (@10) , *(2) (@6) , *(2) (@4) , linev )10 "
	push	word [bp+14]
	push	word [bp+12]
	push	word [bp+10]
	push	word [bp+6]
	push	word [bp+4]
	call	_linev
	sub	sp, -10
; }
L44:
L41:
	leave
	ret

; glb text : (
; prm     x : unsigned
; prm     y : unsigned
; prm     s : * char
; prm     color : unsigned
;     ) void
section .text
	global	_text
_text:
	push	bp
	mov	bp, sp
	 sub	sp,          4
; loc     x : (@4) : unsigned
; loc     y : (@6) : unsigned
; loc     s : (@8) : * char
; loc     color : (@10) : unsigned
; loc     ofs : (@-2) : unsigned
; RPN'ized expression: "ofs y 40 * x + 2 * = "
; Expanded expression: "(@-2) (@6) *(2) 40 * (@4) *(2) + 2 * =(2) "
; Fused expression:    "* *(@6) 40 + ax *(@4) * ax 2 =(170) *(@-2) ax "
	mov	ax, [bp+6]
	imul	ax, ax, 40
	add	ax, [bp+4]
	imul	ax, ax, 2
	mov	[bp-2], ax
; while
; RPN'ized expression: "s *u "
; Expanded expression: "(@8) *(2) *(-1) "
L49:
; Fused expression:    "*(2) (@8) *(-1) ax  "
	mov	ax, [bp+8]
	mov	bx, ax
	mov	al, [bx]
	cbw
; JumpIfZero
	test	ax, ax
	je	L50
; {
; loc         v : (@-4) : unsigned
; RPN'ized expression: "v color 8 << s ++p *u | = "
; Expanded expression: "(@-4) (@10) *(2) 8 << (@8) ++p(2) *(-1) | =(2) "
; Fused expression:    "<< *(@10) 8 push-ax ++p(2) *(@8) | *sp *ax =(170) *(@-4) ax "
	mov	ax, [bp+10]
	shl	ax, 8
	push	ax
	mov	ax, [bp+8]
	inc	word [bp+8]
	mov	bx, ax
	movsx	cx, byte [bx]
	pop	ax
	or	ax, cx
	mov	[bp-4], ax
; RPN'ized expression: "( v , ofs , 47104u poke ) "
; Expanded expression: " (@-4) *(2)  (@-2) *(2)  47104u  poke ()6 "
; Fused expression:    "( *(2) (@-4) , *(2) (@-2) , 47104u , poke )6 "
	push	word [bp-4]
	push	word [bp-2]
	push	-18432
	call	_poke
	sub	sp, -6
; RPN'ized expression: "ofs 2 += "
; Expanded expression: "(@-2) 2 +=(2) "
; Fused expression:    "+=(170) *(@-2) 2 "
	mov	ax, [bp-2]
	add	ax, 2
	mov	[bp-2], ax
; }
	jmp	L49
L50:
L47:
	leave
	ret

; glb number : (
; prm     x : unsigned
; prm     y : unsigned
; prm     n : unsigned
; prm     color : unsigned
;     ) void
section .text
	global	_number
_number:
	push	bp
	mov	bp, sp
	 sub	sp,          8
; loc     x : (@4) : unsigned
; loc     y : (@6) : unsigned
; loc     n : (@8) : unsigned
; loc     color : (@10) : unsigned
; RPN'ized expression: "6 "
; Expanded expression: "6 "
; Expression value: 6
; loc     s : (@-6) : [6u] char
; loc     i : (@-8) : int
; for
; RPN'ized expression: "i 4 = "
; Expanded expression: "(@-8) 4 =(2) "
; Fused expression:    "=(170) *(@-8) 4 "
	mov	ax, 4
	mov	[bp-8], ax
L53:
; RPN'ized expression: "i 0 >= "
; Expanded expression: "(@-8) *(2) 0 >= "
; Fused expression:    ">= *(@-8) 0 IF! "
	mov	ax, [bp-8]
	cmp	ax, 0
	jl	L56
; RPN'ized expression: "i -- "
; Expanded expression: "(@-8) --(2) "
; {
; RPN'ized expression: "s i + *u 48 n 10 % + = "
; Expanded expression: "(@-6) (@-8) *(2) + 48 (@8) *(2) 10 %u + =(-1) "
; Fused expression:    "+ (@-6) *(@-8) push-ax %u *(@8) 10 + 48 ax =(122) **sp ax "
	lea	ax, [bp-6]
	add	ax, [bp-8]
	push	ax
	mov	ax, [bp+8]
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
; RPN'ized expression: "n 10 /= "
; Expanded expression: "(@8) 10 /=u(2) "
; Fused expression:    "/=u(170) *(@8) 10 "
	mov	ax, [bp+8]
	mov	dx, 0
	mov	cx, 10
	div	cx
	mov	[bp+8], ax
; }
L54:
; Fused expression:    "--(2) *(@-8) "
	dec	word [bp-8]
	mov	ax, [bp-8]
	jmp	L53
L56:
; RPN'ized expression: "s 5 + *u 0 = "
; Expanded expression: "(@-1) 0 =(-1) "
; Fused expression:    "=(122) *(@-1) 0 "
	mov	ax, 0
	mov	[bp-1], al
	cbw
; RPN'ized expression: "( color , s , y , x text ) "
; Expanded expression: " (@10) *(2)  (@-6)  (@6) *(2)  (@4) *(2)  text ()8 "
; Fused expression:    "( *(2) (@10) , (@-6) , *(2) (@6) , *(2) (@4) , text )8 "
	push	word [bp+10]
	lea	ax, [bp-6]
	push	ax
	push	word [bp+6]
	push	word [bp+4]
	call	_text
	sub	sp, -8
L51:
	leave
	ret

; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
; glb rand_next : [2u] unsigned
section .data
	align 2
	global	_rand_next
_rand_next:
; =
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
	dw	1
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
	dw	0

; glb rand : (void) int
section .text
	global	_rand
_rand:
	push	bp
	mov	bp, sp
	;sub	sp,          0
mov  eax, [_rand_next]
imul eax, eax, 1103515245
add  eax, 12345
mov  [_rand_next], eax
shr  eax, 16
and  ax, 0x7FFF

L57:
	leave
	ret

; glb srand : (
; prm     seed : unsigned
;     ) void
section .text
	global	_srand
_srand:
	push	bp
	mov	bp, sp
	;sub	sp,          0
; loc     seed : (@4) : unsigned
; RPN'ized expression: "rand_next 0 + *u seed = "
; Expanded expression: "rand_next 0 + (@4) *(2) =(2) "
; Fused expression:    "+ rand_next 0 =(170) *ax *(@4) "
	mov	ax, _rand_next
	mov	bx, ax
	mov	ax, [bp+4]
	mov	[bx], ax
L59:
	leave
	ret

; glb play : (void) void
; glb main : (void) int
section .text
	global	_main
_main:
	push	bp
	mov	bp, sp
	 sub	sp,          4
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
; loc     ticks : (@-4) : [2u] unsigned
; RPN'ized expression: "( 1 BiosSetGfxMode ) "
; Expanded expression: " 1  BiosSetGfxMode ()2 "
; Fused expression:    "( 1 , BiosSetGfxMode )2 "
	push	1
	call	_BiosSetGfxMode
	sub	sp, -2

section .rodata
L63:
	db	"Press a key to start"
	times	1 db 0

section .text
; RPN'ized expression: "( 0 15 | , L63 , 25 2 / , 40 20 - 2 / text ) "
; Expanded expression: " 15  L63  12  10  text ()8 "
; Fused expression:    "( 15 , L63 , 12 , 10 , text )8 "
	push	15
	push	L63
	push	12
	push	10
	call	_text
	sub	sp, -8
; while
; RPN'ized expression: "( BiosKeyAvailable ) "
; Expanded expression: " BiosKeyAvailable ()0 "
L64:
; Fused expression:    "( BiosKeyAvailable )0  "
	call	_BiosKeyAvailable
; JumpIfZero
	test	ax, ax
	je	L65
; RPN'ized expression: "( BiosReadKey ) "
; Expanded expression: " BiosReadKey ()0 "
; Fused expression:    "( BiosReadKey )0 "
	call	_BiosReadKey
	jmp	L64
L65:
; RPN'ized expression: "( BiosReadKey ) "
; Expanded expression: " BiosReadKey ()0 "
; Fused expression:    "( BiosReadKey )0 "
	call	_BiosReadKey
; RPN'ized expression: "( ticks BiosGetTicks ) "
; Expanded expression: " (@-4)  BiosGetTicks ()2 "
; Fused expression:    "( (@-4) , BiosGetTicks )2 "
	lea	ax, [bp-4]
	push	ax
	call	_BiosGetTicks
	sub	sp, -2
; RPN'ized expression: "( ticks 0 + *u srand ) "
; Expanded expression: " (@-4) *(2)  srand ()2 "
; Fused expression:    "( *(2) (@-4) , srand )2 "
	push	word [bp-4]
	call	_srand
	sub	sp, -2
; RPN'ized expression: "( play ) "
; Expanded expression: " play ()0 "
; Fused expression:    "( play )0 "
	call	_play
; RPN'ized expression: "( 3 BiosSetGfxMode ) "
; Expanded expression: " 3  BiosSetGfxMode ()2 "
; Fused expression:    "( 3 , BiosSetGfxMode )2 "
	push	3
	call	_BiosSetGfxMode
	sub	sp, -2
; return
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "0  "
	mov	ax, 0
	jmp	L61
; Fused expression:    "0  "
	mov	ax, 0
L61:
	leave
	ret

; glb newtarget : (void) void
section .text
	global	_newtarget
_newtarget:
	push	bp
	mov	bp, sp
	 sub	sp,          4
; for
L68:
; {
; loc         bit : (@-2) : unsigned
; RPN'ized expression: "bit 0 = "
; Expanded expression: "(@-2) 0 =(2) "
; Fused expression:    "=(170) *(@-2) 0 "
	mov	ax, 0
	mov	[bp-2], ax
; loc         i : (@-4) : unsigned
; RPN'ized expression: "i ( rand ) 40 2 - 25 2 - * % = "
; Expanded expression: "(@-4)  rand ()0 874 % =(2) "
; Fused expression:    "( rand )0 % ax 874 =(170) *(@-4) ax "
	call	_rand
	cwd
	mov	cx, 874
	idiv	cx
	mov	ax, dx
	mov	[bp-4], ax
; RPN'ized expression: "target 0 + *u 1 i 40 2 - % + = "
; Expanded expression: "target 0 + 1 (@-4) *(2) 38 %u + =(2) "
; Fused expression:    "+ target 0 push-ax %u *(@-4) 38 + 1 ax =(170) **sp ax "
	mov	ax, _target
	push	ax
	mov	ax, [bp-4]
	mov	dx, 0
	mov	cx, 38
	div	cx
	mov	ax, dx
	mov	cx, ax
	mov	ax, 1
	add	ax, cx
	pop	bx
	mov	[bx], ax
; RPN'ized expression: "target 1 + *u 1 i 40 2 - / + = "
; Expanded expression: "target 2 + 1 (@-4) *(2) 38 /u + =(2) "
; Fused expression:    "+ target 2 push-ax /u *(@-4) 38 + 1 ax =(170) **sp ax "
	mov	ax, _target
	add	ax, 2
	push	ax
	mov	ax, [bp-4]
	mov	dx, 0
	mov	cx, 38
	div	cx
	mov	cx, ax
	mov	ax, 1
	add	ax, cx
	pop	bx
	mov	[bx], ax
; for
; RPN'ized expression: "i 0 = "
; Expanded expression: "(@-4) 0 =(2) "
; Fused expression:    "=(170) *(@-4) 0 "
	mov	ax, 0
	mov	[bp-4], ax
L72:
; RPN'ized expression: "i length < "
; Expanded expression: "(@-4) *(2) length *(2) <u "
; Fused expression:    "<u *(@-4) *length IF! "
	mov	ax, [bp-4]
	cmp	ax, [_length]
	jae	L75
; RPN'ized expression: "i ++ "
; Expanded expression: "(@-4) ++(2) "
; {
; if
; RPN'ized expression: "target 0 + *u snake i + *u 0 + *u == target 1 + *u snake i + *u 1 + *u == && "
; Expanded expression: "target 0 + *(2) snake (@-4) *(2) 4 * + 0 + *(2) == [sh&&->78] target 2 + *(2) snake (@-4) *(2) 4 * + 2 + *(2) == &&[78] "
; Fused expression:    "+ target 0 push-ax * *(@-4) 4 + snake ax + ax 0 == **sp *ax [sh&&->78] + target 2 push-ax * *(@-4) 4 + snake ax + ax 2 == **sp *ax &&[78]  "
	mov	ax, _target
	push	ax
	mov	ax, [bp-4]
	imul	ax, ax, 4
	mov	cx, ax
	mov	ax, _snake
	add	ax, cx
	mov	bx, ax
	mov	cx, [bx]
	pop	bx
	mov	ax, [bx]
	cmp	ax, cx
	sete	al
	cbw
; JumpIfZero
	test	ax, ax
	je	L78
	mov	ax, _target
	add	ax, 2
	push	ax
	mov	ax, [bp-4]
	imul	ax, ax, 4
	mov	cx, ax
	mov	ax, _snake
	add	ax, cx
	add	ax, 2
	mov	bx, ax
	mov	cx, [bx]
	pop	bx
	mov	ax, [bx]
	cmp	ax, cx
	sete	al
	cbw
L78:
; JumpIfZero
	test	ax, ax
	je	L76
; {
; RPN'ized expression: "bit 1 = "
; Expanded expression: "(@-2) 1 =(2) "
; Fused expression:    "=(170) *(@-2) 1 "
	mov	ax, 1
	mov	[bp-2], ax
; break
	jmp	L75
; }
L76:
; }
L73:
; Fused expression:    "++(2) *(@-4) "
	inc	word [bp-4]
	mov	ax, [bp-4]
	jmp	L72
L75:
; if
; RPN'ized expression: "bit 0 == "
; Expanded expression: "(@-2) *(2) 0 == "
; Fused expression:    "== *(@-2) 0 IF! "
	mov	ax, [bp-2]
	cmp	ax, 0
	jne	L79
; break
	jmp	L71
L79:
; }
	jmp	L68
L71:

section .rodata
L81:
	db	"$"
	times	1 db 0

section .text
; RPN'ized expression: "( 32 14 | , L81 , target 1 + *u , target 0 + *u text ) "
; Expanded expression: " 46  L81  target 2 + *(2)  target 0 + *(2)  text ()8 "
; Fused expression:    "( 46 , L81 , + target 2 *(2) ax , + target 0 *(2) ax , text )8 "
	push	46
	push	L81
	mov	ax, _target
	add	ax, 2
	mov	bx, ax
	push	word [bx]
	mov	ax, _target
	mov	bx, ax
	push	word [bx]
	call	_text
	sub	sp, -8
L66:
	leave
	ret

; glb play : (void) void
section .text
	global	_play
_play:
	push	bp
	mov	bp, sp
	 sub	sp,          6
; loc     i : (@-2) : unsigned
; loc     key : (@-4) : unsigned
; RPN'ized expression: "( 1 , 32 14 | , 32 , 25 , 40 , 0 , 0 box ) "
; Expanded expression: " 1  46  32  25  40  0  0  box ()14 "
; Fused expression:    "( 1 , 46 , 32 , 25 , 40 , 0 , 0 , box )14 "
	push	1
	push	46
	push	32
	push	25
	push	40
	push	0
	push	0
	call	_box
	sub	sp, -14
; RPN'ized expression: "( 0 , 96 0 | , 32 , 25 , 40 , 0 , 0 box ) "
; Expanded expression: " 0  96  32  25  40  0  0  box ()14 "
; Fused expression:    "( 0 , 96 , 32 , 25 , 40 , 0 , 0 , box )14 "
	push	0
	push	96
	push	32
	push	25
	push	40
	push	0
	push	0
	call	_box
	sub	sp, -14

section .rodata
L84:
	db	"Score: "
	times	1 db 0

section .text
; RPN'ized expression: "( 96 0 | , L84 , 0 , 40 12 - 2 / text ) "
; Expanded expression: " 96  L84  0  14  text ()8 "
; Fused expression:    "( 96 , L84 , 0 , 14 , text )8 "
	push	96
	push	L84
	push	0
	push	14
	call	_text
	sub	sp, -8
; RPN'ized expression: "score 0 = "
; Expanded expression: "score 0 =(2) "
; Fused expression:    "=(170) *score 0 "
	mov	ax, 0
	mov	[_score], ax
; RPN'ized expression: "( 96 0 | , score , 0 , 40 12 - 2 / 7 + number ) "
; Expanded expression: " 96  score *(2)  0  21  number ()8 "
; Fused expression:    "( 96 , *(2) score , 0 , 21 , number )8 "
	push	96
	push	word [_score]
	push	0
	push	21
	call	_number
	sub	sp, -8
; for
; RPN'ized expression: "length 0 = "
; Expanded expression: "length 0 =(2) "
; Fused expression:    "=(170) *length 0 "
	mov	ax, 0
	mov	[_length], ax
L85:
; RPN'ized expression: "length 6 < "
; Expanded expression: "length *(2) 6 <u "
; Fused expression:    "<u *length 6 IF! "
	mov	ax, [_length]
	cmp	ax, 6
	jae	L88
; RPN'ized expression: "length ++ "
; Expanded expression: "length ++(2) "
; {
; RPN'ized expression: "snake length + *u 0 + *u 40 2 / = "
; Expanded expression: "snake length *(2) 4 * + 0 + 20 =(2) "
; Fused expression:    "* *length 4 + snake ax + ax 0 =(170) *ax 20 "
	mov	ax, [_length]
	imul	ax, ax, 4
	mov	cx, ax
	mov	ax, _snake
	add	ax, cx
	mov	bx, ax
	mov	ax, 20
	mov	[bx], ax
; RPN'ized expression: "snake length + *u 1 + *u 25 1 - 6 - length + = "
; Expanded expression: "snake length *(2) 4 * + 2 + 18 length *(2) + =(2) "
; Fused expression:    "* *length 4 + snake ax + ax 2 push-ax + 18 *length =(170) **sp ax "
	mov	ax, [_length]
	imul	ax, ax, 4
	mov	cx, ax
	mov	ax, _snake
	add	ax, cx
	add	ax, 2
	push	ax
	mov	ax, 18
	add	ax, [_length]
	pop	bx
	mov	[bx], ax

section .rodata
L89:
	db	"O"
	times	1 db 0

section .text
; RPN'ized expression: "( 32 14 | , L89 , snake length + *u 1 + *u , snake length + *u 0 + *u text ) "
; Expanded expression: " 46  L89  snake length *(2) 4 * + 2 + *(2)  snake length *(2) 4 * + 0 + *(2)  text ()8 "
; Fused expression:    "( 46 , L89 , * *length 4 + snake ax + ax 2 *(2) ax , * *length 4 + snake ax + ax 0 *(2) ax , text )8 "
	push	46
	push	L89
	mov	ax, [_length]
	imul	ax, ax, 4
	mov	cx, ax
	mov	ax, _snake
	add	ax, cx
	add	ax, 2
	mov	bx, ax
	push	word [bx]
	mov	ax, [_length]
	imul	ax, ax, 4
	mov	cx, ax
	mov	ax, _snake
	add	ax, cx
	mov	bx, ax
	push	word [bx]
	call	_text
	sub	sp, -8
; }
L86:
; Fused expression:    "++(2) *length "
	inc	word [_length]
	mov	ax, [_length]
	jmp	L85
L88:
; RPN'ized expression: "direction 18432 = "
; Expanded expression: "direction 18432 =(2) "
; Fused expression:    "=(170) *direction 18432 "
	mov	ax, 18432
	mov	[_direction], ax
; RPN'ized expression: "( newtarget ) "
; Expanded expression: " newtarget ()0 "
; Fused expression:    "( newtarget )0 "
	call	_newtarget
; for
L90:
; {
; RPN'ized expression: "key 0 = "
; Expanded expression: "(@-4) 0 =(2) "
; Fused expression:    "=(170) *(@-4) 0 "
	mov	ax, 0
	mov	[bp-4], ax
; if
; RPN'ized expression: "( BiosKeyAvailable ) "
; Expanded expression: " BiosKeyAvailable ()0 "
; Fused expression:    "( BiosKeyAvailable )0  "
	call	_BiosKeyAvailable
; JumpIfZero
	test	ax, ax
	je	L94
; RPN'ized expression: "key ( BiosReadKey ) = "
; Expanded expression: "(@-4)  BiosReadKey ()0 =(2) "
; Fused expression:    "( BiosReadKey )0 =(170) *(@-4) ax "
	call	_BiosReadKey
	mov	[bp-4], ax
L94:
; RPN'ized expression: "( 150 delay ) "
; Expanded expression: " 150  delay ()2 "
; Fused expression:    "( 150 , delay )2 "
	push	150
	call	_delay
	sub	sp, -2
; switch
; RPN'ized expression: "key "
; Expanded expression: "(@-4) *(2) "
; Fused expression:    "*(2) (@-4)  "
	mov	ax, [bp-4]
	jmp	L97
; {
; case
; RPN'ized expression: "283 "
; Expanded expression: "283 "
; Expression value: 283
L98:
; return
	jmp	L82
; case
; RPN'ized expression: "19200 "
; Expanded expression: "19200 "
; Expression value: 19200
L99:
; if
; RPN'ized expression: "direction 19712 != "
; Expanded expression: "direction *(2) 19712 != "
; Fused expression:    "!= *direction 19712 IF! "
	mov	ax, [_direction]
	cmp	ax, 19712
	je	L100
; RPN'ized expression: "direction key = "
; Expanded expression: "direction (@-4) *(2) =(2) "
; Fused expression:    "=(170) *direction *(@-4) "
	mov	ax, [bp-4]
	mov	[_direction], ax
L100:
; break
	jmp	L96
; case
; RPN'ized expression: "19712 "
; Expanded expression: "19712 "
; Expression value: 19712
L102:
; if
; RPN'ized expression: "direction 19200 != "
; Expanded expression: "direction *(2) 19200 != "
; Fused expression:    "!= *direction 19200 IF! "
	mov	ax, [_direction]
	cmp	ax, 19200
	je	L103
; RPN'ized expression: "direction key = "
; Expanded expression: "direction (@-4) *(2) =(2) "
; Fused expression:    "=(170) *direction *(@-4) "
	mov	ax, [bp-4]
	mov	[_direction], ax
L103:
; break
	jmp	L96
; case
; RPN'ized expression: "18432 "
; Expanded expression: "18432 "
; Expression value: 18432
L105:
; if
; RPN'ized expression: "direction 20480 != "
; Expanded expression: "direction *(2) 20480 != "
; Fused expression:    "!= *direction 20480 IF! "
	mov	ax, [_direction]
	cmp	ax, 20480
	je	L106
; RPN'ized expression: "direction key = "
; Expanded expression: "direction (@-4) *(2) =(2) "
; Fused expression:    "=(170) *direction *(@-4) "
	mov	ax, [bp-4]
	mov	[_direction], ax
L106:
; break
	jmp	L96
; case
; RPN'ized expression: "20480 "
; Expanded expression: "20480 "
; Expression value: 20480
L108:
; if
; RPN'ized expression: "direction 18432 != "
; Expanded expression: "direction *(2) 18432 != "
; Fused expression:    "!= *direction 18432 IF! "
	mov	ax, [_direction]
	cmp	ax, 18432
	je	L109
; RPN'ized expression: "direction key = "
; Expanded expression: "direction (@-4) *(2) =(2) "
; Fused expression:    "=(170) *direction *(@-4) "
	mov	ax, [bp-4]
	mov	[_direction], ax
L109:
; break
	jmp	L96
; }
	jmp	L96
L97:
	cmp	ax, 283
	je	L98
	cmp	ax, 19200
	je	L99
	cmp	ax, 19712
	je	L102
	cmp	ax, 18432
	je	L105
	cmp	ax, 20480
	je	L108
L96:

section .rodata
L111:
	db	" "
	times	1 db 0

section .text
; RPN'ized expression: "( 32 14 | , L111 , snake length 1 - + *u 1 + *u , snake length 1 - + *u 0 + *u text ) "
; Expanded expression: " 46  L111  snake length *(2) 1 - 4 * + 2 + *(2)  snake length *(2) 1 - 4 * + 0 + *(2)  text ()8 "
; Fused expression:    "( 46 , L111 , - *length 1 * ax 4 + snake ax + ax 2 *(2) ax , - *length 1 * ax 4 + snake ax + ax 0 *(2) ax , text )8 "
	push	46
	push	L111
	mov	ax, [_length]
	dec	ax
	imul	ax, ax, 4
	mov	cx, ax
	mov	ax, _snake
	add	ax, cx
	add	ax, 2
	mov	bx, ax
	push	word [bx]
	mov	ax, [_length]
	dec	ax
	imul	ax, ax, 4
	mov	cx, ax
	mov	ax, _snake
	add	ax, cx
	mov	bx, ax
	push	word [bx]
	call	_text
	sub	sp, -8
; for
; RPN'ized expression: "i length 1 - = "
; Expanded expression: "(@-2) length *(2) 1 - =(2) "
; Fused expression:    "- *length 1 =(170) *(@-2) ax "
	mov	ax, [_length]
	dec	ax
	mov	[bp-2], ax
L112:
; RPN'ized expression: "i 0 > "
; Expanded expression: "(@-2) *(2) 0 >u "
; Fused expression:    ">u *(@-2) 0 IF! "
	mov	ax, [bp-2]
	cmp	ax, 0
	jbe	L115
; RPN'ized expression: "i -- "
; Expanded expression: "(@-2) --(2) "
; {
; RPN'ized expression: "snake i + *u 0 + *u snake i 1 - + *u 0 + *u = "
; Expanded expression: "snake (@-2) *(2) 4 * + 0 + snake (@-2) *(2) 1 - 4 * + 0 + *(2) =(2) "
; Fused expression:    "* *(@-2) 4 + snake ax + ax 0 push-ax - *(@-2) 1 * ax 4 + snake ax + ax 0 =(170) **sp *ax "
	mov	ax, [bp-2]
	imul	ax, ax, 4
	mov	cx, ax
	mov	ax, _snake
	add	ax, cx
	push	ax
	mov	ax, [bp-2]
	dec	ax
	imul	ax, ax, 4
	mov	cx, ax
	mov	ax, _snake
	add	ax, cx
	mov	bx, ax
	mov	ax, [bx]
	pop	bx
	mov	[bx], ax
; RPN'ized expression: "snake i + *u 1 + *u snake i 1 - + *u 1 + *u = "
; Expanded expression: "snake (@-2) *(2) 4 * + 2 + snake (@-2) *(2) 1 - 4 * + 2 + *(2) =(2) "
; Fused expression:    "* *(@-2) 4 + snake ax + ax 2 push-ax - *(@-2) 1 * ax 4 + snake ax + ax 2 =(170) **sp *ax "
	mov	ax, [bp-2]
	imul	ax, ax, 4
	mov	cx, ax
	mov	ax, _snake
	add	ax, cx
	add	ax, 2
	push	ax
	mov	ax, [bp-2]
	dec	ax
	imul	ax, ax, 4
	mov	cx, ax
	mov	ax, _snake
	add	ax, cx
	add	ax, 2
	mov	bx, ax
	mov	ax, [bx]
	pop	bx
	mov	[bx], ax
; }
L113:
; Fused expression:    "--(2) *(@-2) "
	dec	word [bp-2]
	mov	ax, [bp-2]
	jmp	L112
L115:
; switch
; RPN'ized expression: "direction "
; Expanded expression: "direction *(2) "
; Fused expression:    "*(2) direction  "
	mov	ax, [_direction]
	jmp	L117
; {
; case
; RPN'ized expression: "19200 "
; Expanded expression: "19200 "
; Expression value: 19200
L118:
; RPN'ized expression: "snake 0 + *u 0 + *u -- "
; Expanded expression: "snake 0 + --(2) "
; Fused expression:    "+ snake 0 --(2) *ax "
	mov	ax, _snake
	mov	bx, ax
	dec	word [bx]
	mov	ax, [bx]
; break
	jmp	L116
; case
; RPN'ized expression: "19712 "
; Expanded expression: "19712 "
; Expression value: 19712
L119:
; RPN'ized expression: "snake 0 + *u 0 + *u ++ "
; Expanded expression: "snake 0 + ++(2) "
; Fused expression:    "+ snake 0 ++(2) *ax "
	mov	ax, _snake
	mov	bx, ax
	inc	word [bx]
	mov	ax, [bx]
; break
	jmp	L116
; case
; RPN'ized expression: "18432 "
; Expanded expression: "18432 "
; Expression value: 18432
L120:
; RPN'ized expression: "snake 0 + *u 1 + *u -- "
; Expanded expression: "snake 2 + --(2) "
; Fused expression:    "+ snake 2 --(2) *ax "
	mov	ax, _snake
	add	ax, 2
	mov	bx, ax
	dec	word [bx]
	mov	ax, [bx]
; break
	jmp	L116
; case
; RPN'ized expression: "20480 "
; Expanded expression: "20480 "
; Expression value: 20480
L121:
; RPN'ized expression: "snake 0 + *u 1 + *u ++ "
; Expanded expression: "snake 2 + ++(2) "
; Fused expression:    "+ snake 2 ++(2) *ax "
	mov	ax, _snake
	add	ax, 2
	mov	bx, ax
	inc	word [bx]
	mov	ax, [bx]
; break
	jmp	L116
; }
	jmp	L116
L117:
	cmp	ax, 19200
	je	L118
	cmp	ax, 19712
	je	L119
	cmp	ax, 18432
	je	L120
	cmp	ax, 20480
	je	L121
L116:

section .rodata
L122:
	db	"O"
	times	1 db 0

section .text
; RPN'ized expression: "( 32 14 | , L122 , snake 0 + *u 1 + *u , snake 0 + *u 0 + *u text ) "
; Expanded expression: " 46  L122  snake 2 + *(2)  snake 0 + *(2)  text ()8 "
; Fused expression:    "( 46 , L122 , + snake 2 *(2) ax , + snake 0 *(2) ax , text )8 "
	push	46
	push	L122
	mov	ax, _snake
	add	ax, 2
	mov	bx, ax
	push	word [bx]
	mov	ax, _snake
	mov	bx, ax
	push	word [bx]
	call	_text
	sub	sp, -8
; if
; RPN'ized expression: "snake 0 + *u 0 + *u 1 < snake 0 + *u 0 + *u 40 1 - >= || snake 0 + *u 1 + *u 1 < || snake 0 + *u 1 + *u 25 1 - >= || "
; Expanded expression: "snake 0 + *(2) 1 <u [sh||->127] snake 0 + *(2) 39 >=u ||[127] _Bool [sh||->126] snake 2 + *(2) 1 <u ||[126] _Bool [sh||->125] snake 2 + *(2) 24 >=u ||[125] "
; Fused expression:    "+ snake 0 <u *ax 1 [sh||->127] + snake 0 >=u *ax 39 ||[127] _Bool [sh||->126] + snake 2 <u *ax 1 ||[126] _Bool [sh||->125] + snake 2 >=u *ax 24 ||[125]  "
	mov	ax, _snake
	mov	bx, ax
	mov	ax, [bx]
	cmp	ax, 1
	setb	al
	cbw
; JumpIfNotZero
	test	ax, ax
	jne	L127
	mov	ax, _snake
	mov	bx, ax
	mov	ax, [bx]
	cmp	ax, 39
	setae	al
	cbw
L127:
	test	ax, ax
	setne	al
	cbw
; JumpIfNotZero
	test	ax, ax
	jne	L126
	mov	ax, _snake
	add	ax, 2
	mov	bx, ax
	mov	ax, [bx]
	cmp	ax, 1
	setb	al
	cbw
L126:
	test	ax, ax
	setne	al
	cbw
; JumpIfNotZero
	test	ax, ax
	jne	L125
	mov	ax, _snake
	add	ax, 2
	mov	bx, ax
	mov	ax, [bx]
	cmp	ax, 24
	setae	al
	cbw
L125:
; JumpIfZero
	test	ax, ax
	je	L123
; break
	jmp	L93
L123:
; {
; loc             bit : (@-6) : unsigned
; RPN'ized expression: "bit 0 = "
; Expanded expression: "(@-6) 0 =(2) "
; Fused expression:    "=(170) *(@-6) 0 "
	mov	ax, 0
	mov	[bp-6], ax
; for
; RPN'ized expression: "i 1 = "
; Expanded expression: "(@-2) 1 =(2) "
; Fused expression:    "=(170) *(@-2) 1 "
	mov	ax, 1
	mov	[bp-2], ax
L128:
; RPN'ized expression: "i length < "
; Expanded expression: "(@-2) *(2) length *(2) <u "
; Fused expression:    "<u *(@-2) *length IF! "
	mov	ax, [bp-2]
	cmp	ax, [_length]
	jae	L131
; RPN'ized expression: "i ++ "
; Expanded expression: "(@-2) ++(2) "
; {
; if
; RPN'ized expression: "snake 0 + *u 0 + *u snake i + *u 0 + *u == snake 0 + *u 1 + *u snake i + *u 1 + *u == && "
; Expanded expression: "snake 0 + *(2) snake (@-2) *(2) 4 * + 0 + *(2) == [sh&&->134] snake 2 + *(2) snake (@-2) *(2) 4 * + 2 + *(2) == &&[134] "
; Fused expression:    "+ snake 0 push-ax * *(@-2) 4 + snake ax + ax 0 == **sp *ax [sh&&->134] + snake 2 push-ax * *(@-2) 4 + snake ax + ax 2 == **sp *ax &&[134]  "
	mov	ax, _snake
	push	ax
	mov	ax, [bp-2]
	imul	ax, ax, 4
	mov	cx, ax
	mov	ax, _snake
	add	ax, cx
	mov	bx, ax
	mov	cx, [bx]
	pop	bx
	mov	ax, [bx]
	cmp	ax, cx
	sete	al
	cbw
; JumpIfZero
	test	ax, ax
	je	L134
	mov	ax, _snake
	add	ax, 2
	push	ax
	mov	ax, [bp-2]
	imul	ax, ax, 4
	mov	cx, ax
	mov	ax, _snake
	add	ax, cx
	add	ax, 2
	mov	bx, ax
	mov	cx, [bx]
	pop	bx
	mov	ax, [bx]
	cmp	ax, cx
	sete	al
	cbw
L134:
; JumpIfZero
	test	ax, ax
	je	L132
; {
; RPN'ized expression: "bit 1 = "
; Expanded expression: "(@-6) 1 =(2) "
; Fused expression:    "=(170) *(@-6) 1 "
	mov	ax, 1
	mov	[bp-6], ax
; break
	jmp	L131
; }
L132:
; }
L129:
; Fused expression:    "++(2) *(@-2) "
	inc	word [bp-2]
	mov	ax, [bp-2]
	jmp	L128
L131:
; if
; RPN'ized expression: "bit "
; Expanded expression: "(@-6) *(2) "
; Fused expression:    "*(2) (@-6)  "
	mov	ax, [bp-6]
; JumpIfZero
	test	ax, ax
	je	L135
; break
	jmp	L93
L135:
; }
; if
; RPN'ized expression: "snake 0 + *u 0 + *u target 0 + *u == snake 0 + *u 1 + *u target 1 + *u == && "
; Expanded expression: "snake 0 + *(2) target 0 + *(2) == [sh&&->139] snake 2 + *(2) target 2 + *(2) == &&[139] "
; Fused expression:    "+ snake 0 push-ax + target 0 == **sp *ax [sh&&->139] + snake 2 push-ax + target 2 == **sp *ax &&[139]  "
	mov	ax, _snake
	push	ax
	mov	ax, _target
	mov	bx, ax
	mov	cx, [bx]
	pop	bx
	mov	ax, [bx]
	cmp	ax, cx
	sete	al
	cbw
; JumpIfZero
	test	ax, ax
	je	L139
	mov	ax, _snake
	add	ax, 2
	push	ax
	mov	ax, _target
	add	ax, 2
	mov	bx, ax
	mov	cx, [bx]
	pop	bx
	mov	ax, [bx]
	cmp	ax, cx
	sete	al
	cbw
L139:
; JumpIfZero
	test	ax, ax
	je	L137
; {
; RPN'ized expression: "snake length + *u 0 + *u snake length 1 - + *u 0 + *u = "
; Expanded expression: "snake length *(2) 4 * + 0 + snake length *(2) 1 - 4 * + 0 + *(2) =(2) "
; Fused expression:    "* *length 4 + snake ax + ax 0 push-ax - *length 1 * ax 4 + snake ax + ax 0 =(170) **sp *ax "
	mov	ax, [_length]
	imul	ax, ax, 4
	mov	cx, ax
	mov	ax, _snake
	add	ax, cx
	push	ax
	mov	ax, [_length]
	dec	ax
	imul	ax, ax, 4
	mov	cx, ax
	mov	ax, _snake
	add	ax, cx
	mov	bx, ax
	mov	ax, [bx]
	pop	bx
	mov	[bx], ax
; RPN'ized expression: "snake length + *u 1 + *u snake length 1 - + *u 1 + *u = "
; Expanded expression: "snake length *(2) 4 * + 2 + snake length *(2) 1 - 4 * + 2 + *(2) =(2) "
; Fused expression:    "* *length 4 + snake ax + ax 2 push-ax - *length 1 * ax 4 + snake ax + ax 2 =(170) **sp *ax "
	mov	ax, [_length]
	imul	ax, ax, 4
	mov	cx, ax
	mov	ax, _snake
	add	ax, cx
	add	ax, 2
	push	ax
	mov	ax, [_length]
	dec	ax
	imul	ax, ax, 4
	mov	cx, ax
	mov	ax, _snake
	add	ax, cx
	add	ax, 2
	mov	bx, ax
	mov	ax, [bx]
	pop	bx
	mov	[bx], ax
; RPN'ized expression: "length ++ "
; Expanded expression: "length ++(2) "
; Fused expression:    "++(2) *length "
	inc	word [_length]
	mov	ax, [_length]
; RPN'ized expression: "score ++ "
; Expanded expression: "score ++(2) "
; Fused expression:    "++(2) *score "
	inc	word [_score]
	mov	ax, [_score]
; RPN'ized expression: "( 96 0 | , score , 0 , 40 12 - 2 / 7 + number ) "
; Expanded expression: " 96  score *(2)  0  21  number ()8 "
; Fused expression:    "( 96 , *(2) score , 0 , 21 , number )8 "
	push	96
	push	word [_score]
	push	0
	push	21
	call	_number
	sub	sp, -8
; RPN'ized expression: "( newtarget ) "
; Expanded expression: " newtarget ()0 "
; Fused expression:    "( newtarget )0 "
	call	_newtarget
; }
L137:
; }
	jmp	L90
L93:

section .rodata
L140:
	db	"Game Over!"
	times	1 db 0

section .text
; RPN'ized expression: "( 0 15 | , L140 , 25 2 / , 40 10 - 2 / text ) "
; Expanded expression: " 15  L140  12  15  text ()8 "
; Fused expression:    "( 15 , L140 , 12 , 15 , text )8 "
	push	15
	push	L140
	push	12
	push	15
	call	_text
	sub	sp, -8
; RPN'ized expression: "( 1000 delay ) "
; Expanded expression: " 1000  delay ()2 "
; Fused expression:    "( 1000 , delay )2 "
	push	1000
	call	_delay
	sub	sp, -2
; while
; RPN'ized expression: "( BiosKeyAvailable ) "
; Expanded expression: " BiosKeyAvailable ()0 "
L141:
; Fused expression:    "( BiosKeyAvailable )0  "
	call	_BiosKeyAvailable
; JumpIfZero
	test	ax, ax
	je	L142
; RPN'ized expression: "( BiosReadKey ) "
; Expanded expression: " BiosReadKey ()0 "
; Fused expression:    "( BiosReadKey )0 "
	call	_BiosReadKey
	jmp	L141
L142:
; RPN'ized expression: "( BiosReadKey ) "
; Expanded expression: " BiosReadKey ()0 "
; Fused expression:    "( BiosReadKey )0 "
	call	_BiosReadKey
L82:
	leave
	ret



; Syntax/declaration table/stack:
; Bytes used: 1100/15360


; Macro table:
; Macro __SMALLER_C__ = `0x0100`
; Macro __SMALLER_C_16__ = ``
; Macro __SMALLER_C_SCHAR__ = ``
; Macro DELAY = `150`
; Macro VMODE = `1`
; Macro VSEG = `0xB800`
; Macro VWIDTH = `40`
; Macro VHEIGHT = `25`
; Macro FORE_BLACK = `0x00`
; Macro FORE_BLUE = `0x01`
; Macro FORE_GREEN = `0x02`
; Macro FORE_CYAN = `0x03`
; Macro FORE_RED = `0x04`
; Macro FORE_MAGENTA = `0x05`
; Macro FORE_BROWN = `0x06`
; Macro FORE_WHITE = `0x07`
; Macro FORE_GRAY = `0x08`
; Macro FORE_BRIGHT_BLUE = `0x09`
; Macro FORE_BRIGHT_GREEN = `0x0A`
; Macro FORE_BRIGHT_CYAN = `0x0B`
; Macro FORE_BRIGHT_RED = `0x0C`
; Macro FORE_BRIGHT_MAGENTA = `0x0D`
; Macro FORE_YELLOW = `0x0E`
; Macro FORE_BRIGHT_WHITE = `0x0F`
; Macro BACK_BLACK = `0x00`
; Macro BACK_BLUE = `0x10`
; Macro BACK_GREEN = `0x20`
; Macro BACK_CYAN = `0x30`
; Macro BACK_RED = `0x40`
; Macro BACK_MAGENTA = `0x50`
; Macro BACK_BROWN = `0x60`
; Macro BACK_WHITE = `0x70`
; Macro KEY_ESCAPE = `0x011B`
; Macro KEY_ENTER = `0x1C0D`
; Macro KEY_UP = `0x4800`
; Macro KEY_LEFT = `0x4B00`
; Macro KEY_RIGHT = `0x4D00`
; Macro KEY_DOWN = `0x5000`
; Macro MIN_LENGTH = `6`
; Macro MAX_LENGTH = `(VWIDTH * VHEIGHT)`
; Macro RAND_MAX = `0x7FFF`
; Bytes used: 729/5120


; Identifier table:
; Ident 
; Ident __floatsisf
; Ident __floatunsisf
; Ident __fixsfsi
; Ident __fixunssfsi
; Ident __addsf3
; Ident __subsf3
; Ident __negsf2
; Ident __mulsf3
; Ident __divsf3
; Ident __lesf2
; Ident __gesf2
; Ident main
; Ident <something>
; Ident start
; Ident snake
; Ident length
; Ident direction
; Ident target
; Ident score
; Ident BiosKeyAvailable
; Ident BiosReadKey
; Ident BiosSetGfxMode
; Ident mode
; Ident pokeb
; Ident seg
; Ident ofs
; Ident val
; Ident poke
; Ident peekb
; Ident peek
; Ident BiosGetTicks
; Ident ticks
; Ident delay
; Ident milliseconds
; Ident lineh
; Ident x
; Ident y
; Ident w
; Ident chr
; Ident color
; Ident linev
; Ident h
; Ident box
; Ident solid
; Ident text
; Ident s
; Ident number
; Ident n
; Ident rand_next
; Ident rand
; Ident srand
; Ident seed
; Ident play
; Ident newtarget
; Bytes used: 443/5632

; Next label number: 143
; Compilation succeeded.
