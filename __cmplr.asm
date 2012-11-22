SEGMENT _TEXT PUBLIC CLASS=CODE USE16
SEGMENT _DATA PUBLIC CLASS=DATA

; glb _setargv__ : char
    extern  __setargv__
; glb exit : (
; prm     status : int
;     ) void
    extern  _exit
; glb malloc : (
; prm     s : int
;     ) * void
    extern  _malloc
; glb free : (
; prm     <something> : * void
;     ) void
    extern  _free
; glb atoi : (
; prm     <something> : * char
;     ) int
    extern  _atoi
; glb strlen : (
; prm     s : * char
;     ) int
    extern  _strlen
; glb strcpy : (
; prm     s1 : * char
; prm     s2 : * char
;     ) * char
    extern  _strcpy
; glb strchr : (
; prm     s : * char
; prm     c : int
;     ) * char
    extern  _strchr
; glb strcmp : (
; prm     s1 : * char
; prm     s2 : * char
;     ) int
    extern  _strcmp
; glb memmove : (
; prm     <something> : * void
; prm     <something> : * void
; prm     <something> : int
;     ) * void
    extern  _memmove
; glb memcpy : (
; prm     <something> : * void
; prm     <something> : * void
; prm     <something> : int
;     ) * void
    extern  _memcpy
; glb isspace : (
; prm     c : int
;     ) int
    extern  _isspace
; glb isdigit : (
; prm     c : int
;     ) int
    extern  _isdigit
; glb isalpha : (
; prm     c : int
;     ) int
    extern  _isalpha
; glb isalnum : (
; prm     c : int
;     ) int
    extern  _isalnum
; glb putchar : (
; prm     c : int
;     ) int
    extern  _putchar
; glb fopen : (
; prm     <something> : * char
; prm     <something> : * char
;     ) * int
    extern  _fopen
; glb fclose : (
; prm     <something> : * int
;     ) int
    extern  _fclose
; glb fgetc : (
; prm     <something> : * int
;     ) int
    extern  _fgetc
; glb printf : (
; prm     fmt : * char
; prm     ...
;     ) int
    extern  _printf
; glb GetToken : (void) int
; glb GetTokenName : (
; prm     token : int
;     ) * char
; glb GetTokenValueInt : (void) int
; glb GetTokenValueString : (void) * char
; glb GetTokenValueStringLength : (void) int
; glb GetTokenIdentName : (void) * char
; glb GetTokenFileName : (void) * char
; glb GetTokenFileLineNo : (void) int
; glb GetTokenFileLinePos : (void) int
; glb DumpMacroTable : (void) void
; glb PurgeStringTable : (void) void
; glb AddString : (
; prm     label : int
; prm     str : * char
; prm     len : int
;     ) void
; glb FindString : (
; prm     label : int
;     ) * char
; glb AddIdent : (
; prm     name : * char
;     ) int
; glb FindIdent : (
; prm     name : * char
;     ) int
; glb DumpIdentTable : (void) void
; glb GenLabel : (
; prm     Label : * char
;     ) void
; glb GenExtern : (
; prm     Label : * char
;     ) void
; glb GenNumLabel : (
; prm     Label : int
;     ) void
; glb GenZeroData : (
; prm     Size : int
;     ) void
; glb GenIntData : (
; prm     Size : int
; prm     Val : int
;     ) void
; glb GenAddrData : (
; prm     Size : int
; prm     Label : * char
;     ) void
; glb GenJumpUncond : (
; prm     Label : int
;     ) void
; glb GenJumpIfZero : (
; prm     Label : int
;     ) void
; glb GenJumpIfNotZero : (
; prm     Label : int
;     ) void
; glb GenJumpIfNotEqual : (
; prm     val : int
; prm     Label : int
;     ) void
; glb GenFxnProlog : (void) void
; glb GenFxnEpilog : (void) void
; glb GenLocalAlloc : (
; prm     Size : int
;     ) void
; glb GenStrData : (
; prm     insertJump : int
;     ) void
; glb GenExpr : (void) void
; glb PushSyntax : (
; prm     t : int
;     ) void
; glb PushSyntax2 : (
; prm     t : int
; prm     v : int
;     ) void
; glb DumpSynDecls : (void) void
; glb push2 : (
; prm     v : int
; prm     v2 : int
;     ) void
; glb ins2 : (
; prm     pos : int
; prm     v : int
; prm     v2 : int
;     ) void
; glb ins : (
; prm     pos : int
; prm     v : int
;     ) void
; glb del : (
; prm     pos : int
; prm     cnt : int
;     ) void
; glb TokenStartsDeclaration : (
; prm     t : int
; prm     params : int
;     ) int
; glb ParseDecl : (
; prm     tok : int
;     ) int
; glb ShiftChar : (void) void
; glb error : (
; prm     format : * char
; prm     ...
;     ) void
; glb FindSymbol : (
; prm     s : * char
;     ) int
; glb SymType : (
; prm     SynPtr : int
;     ) int
; glb GetDeclSize : (
; prm     SyntaxPtr : int
;     ) int
; glb ParseExpr : (
; prm     tok : int
; prm     GotUnary : * int
; prm     ExprTypeSynPtr : * int
; prm     ConstExpr : * int
; prm     ConstVal : * int
;     ) int
; glb GetFxnInfo : (
; prm     ExprTypeSynPtr : int
; prm     MinParams : * int
; prm     MaxParams : * int
; prm     ReturnExprTypeSynPtr : * int
;     ) int
; glb TokenValueInt : int
SEGMENT _DATA
    global  _TokenValueInt
_TokenValueInt:
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
    dw  0
; SEGMENT _DATA
; RPN'ized expression: "31 1 + "
; Expanded expression: "32 "
; Expression value: 32
; glb TokenIdentName : [32] char
SEGMENT _DATA
    global  _TokenIdentName
_TokenIdentName:
    times 32 db 0
; SEGMENT _DATA
; glb TokenIdentNameLen : int
SEGMENT _DATA
    global  _TokenIdentNameLen
_TokenIdentNameLen:
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
    dw  0
; SEGMENT _DATA
; RPN'ized expression: "127 1 + "
; Expanded expression: "128 "
; Expression value: 128
; glb TokenValueString : [128] char
SEGMENT _DATA
    global  _TokenValueString
_TokenValueString:
    times 128 db 0
; SEGMENT _DATA
; glb TokenStringLen : int
SEGMENT _DATA
    global  _TokenStringLen
_TokenStringLen:
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
    dw  0
; SEGMENT _DATA
; glb LineNo : int
SEGMENT _DATA
    global  _LineNo
_LineNo:
; =
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
    dw  1
; SEGMENT _DATA
; glb LinePos : int
SEGMENT _DATA
    global  _LinePos
_LinePos:
; =
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
    dw  1
; SEGMENT _DATA
; glb CurFileName : * char
SEGMENT _DATA
    global  _CurFileName
_CurFileName:
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
    dw  0
; SEGMENT _DATA
; glb CurFile : * int
SEGMENT _DATA
    global  _CurFile
_CurFile:
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
    dw  0
; SEGMENT _DATA
; RPN'ized expression: "256 "
; Expanded expression: "256 "
; Expression value: 256
; glb CharQueue : [256] char
SEGMENT _DATA
    global  _CharQueue
_CharQueue:
    times 256 db 0
; SEGMENT _DATA
; glb CharQueueLen : int
SEGMENT _DATA
    global  _CharQueueLen
_CharQueueLen:
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
    dw  0
; SEGMENT _DATA
; RPN'ized expression: "4096 "
; Expanded expression: "4096 "
; Expression value: 4096
; glb MacroTable : [4096] char
SEGMENT _DATA
    global  _MacroTable
_MacroTable:
    times 4096 db 0
; SEGMENT _DATA
; glb MacroTableLen : int
SEGMENT _DATA
    global  _MacroTableLen
_MacroTableLen:
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
    dw  0
; SEGMENT _DATA
; RPN'ized expression: "512 "
; Expanded expression: "512 "
; Expression value: 512
; glb StringTable : [512] char
SEGMENT _DATA
    global  _StringTable
_StringTable:
    times 512 db 0
; SEGMENT _DATA
; glb StringTableLen : int
SEGMENT _DATA
    global  _StringTableLen
_StringTableLen:
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
    dw  0
; SEGMENT _DATA
; RPN'ized expression: "4096 "
; Expanded expression: "4096 "
; Expression value: 4096
; glb IdentTable : [4096] char
SEGMENT _DATA
    global  _IdentTable
_IdentTable:
    times 4096 db 0
; SEGMENT _DATA
; glb IdentTableLen : int
SEGMENT _DATA
    global  _IdentTableLen
_IdentTableLen:
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
    dw  0
; SEGMENT _DATA
; glb ExprLevel : int
SEGMENT _DATA
    global  _ExprLevel
_ExprLevel:
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
    dw  0
; SEGMENT _DATA
; RPN'ized expression: "100 "
; Expanded expression: "100 "
; Expression value: 100
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
; glb stack : [100] [2] int
SEGMENT _DATA
    global  _stack
_stack:
    times 400 db 0
; SEGMENT _DATA
; glb sp : int
SEGMENT _DATA
    global  _sp
_sp:
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
    dw  0
; SEGMENT _DATA
; RPN'ized expression: "100 "
; Expanded expression: "100 "
; Expression value: 100
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
; glb opstack : [100] [2] int
SEGMENT _DATA
    global  _opstack
_opstack:
    times 400 db 0
; SEGMENT _DATA
; glb opsp : int
SEGMENT _DATA
    global  _opsp
_opsp:
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
    dw  0
; SEGMENT _DATA
; glb OutputFormat : int
SEGMENT _DATA
    global  _OutputFormat
_OutputFormat:
; =
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
    dw  1
; SEGMENT _DATA
; glb FileHeader : * char
SEGMENT _DATA
    global  _FileHeader
_FileHeader:
; =
; RPN'ized expression: "L1 "
; Expanded expression: "L1 "
    dw  L1
; SEGMENT _DATA
SEGMENT _DATA
L1:
    db  0
; SEGMENT _DATA
; glb CodeHeader : * char
SEGMENT _DATA
    global  _CodeHeader
_CodeHeader:
; =
; RPN'ized expression: "L3 "
; Expanded expression: "L3 "
    dw  L3
; SEGMENT _DATA
SEGMENT _DATA
L3:
    db  0
; SEGMENT _DATA
; glb CodeFooter : * char
SEGMENT _DATA
    global  _CodeFooter
_CodeFooter:
; =
; RPN'ized expression: "L5 "
; Expanded expression: "L5 "
    dw  L5
; SEGMENT _DATA
SEGMENT _DATA
L5:
    db  0
; SEGMENT _DATA
; glb DataHeader : * char
SEGMENT _DATA
    global  _DataHeader
_DataHeader:
; =
; RPN'ized expression: "L7 "
; Expanded expression: "L7 "
    dw  L7
; SEGMENT _DATA
SEGMENT _DATA
L7:
    db  0
; SEGMENT _DATA
; glb DataFooter : * char
SEGMENT _DATA
    global  _DataFooter
_DataFooter:
; =
; RPN'ized expression: "L9 "
; Expanded expression: "L9 "
    dw  L9
; SEGMENT _DATA
SEGMENT _DATA
L9:
    db  0
; SEGMENT _DATA
; glb SizeOfChar : int
SEGMENT _DATA
    global  _SizeOfChar
_SizeOfChar:
; =
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
    dw  1
; SEGMENT _DATA
; glb CharIsSigned : int
SEGMENT _DATA
    global  _CharIsSigned
_CharIsSigned:
; =
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
    dw  1
; SEGMENT _DATA
; glb SizeOfWord : int
SEGMENT _DATA
    global  _SizeOfWord
_SizeOfWord:
; =
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
    dw  2
; SEGMENT _DATA
; glb LabelCnt : int
SEGMENT _DATA
    global  _LabelCnt
_LabelCnt:
; =
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
    dw  1
; SEGMENT _DATA
; glb CurFxnSyntaxPtr : int
SEGMENT _DATA
    global  _CurFxnSyntaxPtr
_CurFxnSyntaxPtr:
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
    dw  0
; SEGMENT _DATA
; glb CurFxnParamCnt : int
SEGMENT _DATA
    global  _CurFxnParamCnt
_CurFxnParamCnt:
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
    dw  0
; SEGMENT _DATA
; glb CurFxnParamOfs : int
SEGMENT _DATA
    global  _CurFxnParamOfs
_CurFxnParamOfs:
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
    dw  0
; SEGMENT _DATA
; glb CurFxnLocalOfs : int
SEGMENT _DATA
    global  _CurFxnLocalOfs
_CurFxnLocalOfs:
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
    dw  0
; SEGMENT _DATA
; glb CurFxnReturnExprTypeSynPtr : int
SEGMENT _DATA
    global  _CurFxnReturnExprTypeSynPtr
_CurFxnReturnExprTypeSynPtr:
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
    dw  0
; SEGMENT _DATA
; glb CurFxnEpilogLabel : int
SEGMENT _DATA
    global  _CurFxnEpilogLabel
_CurFxnEpilogLabel:
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
    dw  0
; SEGMENT _DATA
; glb ParseLevel : int
SEGMENT _DATA
    global  _ParseLevel
_ParseLevel:
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
    dw  0
; SEGMENT _DATA
; RPN'ized expression: "2048 "
; Expanded expression: "2048 "
; Expression value: 2048
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
; glb SyntaxStack : [2048] [2] int
SEGMENT _DATA
    global  _SyntaxStack
_SyntaxStack:
    times 8192 db 0
; SEGMENT _DATA
; glb SyntaxStackCnt : int
SEGMENT _DATA
    global  _SyntaxStackCnt
_SyntaxStackCnt:
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
    dw  0
; SEGMENT _DATA
; glb FindMacro : (
; prm     name : * char
;     ) int
SEGMENT _TEXT
    global  _FindMacro
_FindMacro:
    push    bp
    mov     bp, sp
; loc     name : (@4): * char
; loc     i : (@-2): int
    sub     sp, 2
; for
; RPN'ized expression: "i 0 = "
; Expanded expression: "(@-2) 0 =(2) "
; Fused expression:    "=(34) *(@-2) 0 "
    mov     ax, 0
    mov     [bp-2], ax
L12:
; RPN'ized expression: "i MacroTableLen < "
; Expanded expression: "(@-2) *(2) MacroTableLen *(2) < "
; Fused expression:    "< *(@-2) *MacroTableLen IF! "
    mov     ax, [bp-2]
    cmp     ax, [_MacroTableLen]
    jge     L15
    jmp     L14
L13:
    jmp     L12
L14:
; {
; if
; RPN'ized expression: "( name , MacroTable i + 1 + strcmp ) 0 == "
; Expanded expression: " (@4) *(2)  MacroTable (@-2) *(2) + 1 +  strcmp ()4 0 == "
; Fused expression:    "( *(2) (@4) , + MacroTable *(@-2) + ax 1 , strcmp )4 == ax 0 IF! "
    push    word [bp+4]
    mov     ax, _MacroTable
    add     ax, [bp-2]
    add     ax, 1
    push    ax
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L16
; return
; RPN'ized expression: "i 1 + MacroTable i + *u + "
; Expanded expression: "(@-2) *(2) 1 + MacroTable (@-2) *(2) + *(1) + "
; Fused expression:    "+ *(@-2) 1 push-ax + MacroTable *(@-2) + *sp *ax "
    mov     ax, [bp-2]
    add     ax, 1
    push    ax
    mov     ax, _MacroTable
    add     ax, [bp-2]
    mov     bx, ax
    movsx   cx, byte [bx]
    pop     ax
    add     ax, cx
    jmp     L11
L16:
; RPN'ized expression: "i i 1 + MacroTable i + *u + = "
; Expanded expression: "(@-2) (@-2) *(2) 1 + MacroTable (@-2) *(2) + *(1) + =(2) "
; Fused expression:    "+ *(@-2) 1 push-ax + MacroTable *(@-2) + *sp *ax =(34) *(@-2) ax "
    mov     ax, [bp-2]
    add     ax, 1
    push    ax
    mov     ax, _MacroTable
    add     ax, [bp-2]
    mov     bx, ax
    movsx   cx, byte [bx]
    pop     ax
    add     ax, cx
    mov     [bp-2], ax
; RPN'ized expression: "i i 1 + MacroTable i + *u + = "
; Expanded expression: "(@-2) (@-2) *(2) 1 + MacroTable (@-2) *(2) + *(1) + =(2) "
; Fused expression:    "+ *(@-2) 1 push-ax + MacroTable *(@-2) + *sp *ax =(34) *(@-2) ax "
    mov     ax, [bp-2]
    add     ax, 1
    push    ax
    mov     ax, _MacroTable
    add     ax, [bp-2]
    mov     bx, ax
    movsx   cx, byte [bx]
    pop     ax
    add     ax, cx
    mov     [bp-2], ax
; }
    jmp     L13
L15:
; return
; RPN'ized expression: "1 -u "
; Expanded expression: "-1 "
; Expression value: -1
; Fused expression:    "-1 "
    mov     ax, -1
    jmp     L11
L11:
    leave
    ret
; SEGMENT _TEXT
; glb AddMacroIdent : (
; prm     name : * char
;     ) void
SEGMENT _TEXT
    global  _AddMacroIdent
_AddMacroIdent:
    push    bp
    mov     bp, sp
; loc     name : (@4): * char
; loc     l : (@-2): int
    sub     sp, 2
; =
; RPN'ized expression: "( name strlen ) "
; Expanded expression: " (@4) *(2)  strlen ()2 "
; Fused expression:    "( *(2) (@4) , strlen )2 =(34) *(@-2) ax "
    push    word [bp+4]
    call    _strlen
    sub     sp, -2
    mov     [bp-2], ax
; if
; RPN'ized expression: "l 127 >= "
; Expanded expression: "(@-2) *(2) 127 >= "
; Fused expression:    ">= *(@-2) 127 IF! "
    mov     ax, [bp-2]
    cmp     ax, 127
    jl      L19
; RPN'ized expression: "( name , L21 error ) "
; Expanded expression: " (@4) *(2)  L21  error ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L21:
    db  "Error: Macro identifier too long '%s'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@4) , L21 , error )4 "
    push    word [bp+4]
    push    L21
    call    _error
    sub     sp, -4
L19:
; if
; RPN'ized expression: "4096 MacroTableLen - l 3 + < "
; Expanded expression: "4096 MacroTableLen *(2) - (@-2) *(2) 3 + < "
; Fused expression:    "- 4096 *MacroTableLen push-ax + *(@-2) 3 < *sp ax IF! "
    mov     ax, 4096
    sub     ax, [_MacroTableLen]
    push    ax
    mov     ax, [bp-2]
    add     ax, 3
    mov     cx, ax
    pop     ax
    cmp     ax, cx
    jge     L23
; RPN'ized expression: "( L25 error ) "
; Expanded expression: " L25  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L25:
    db  "Error: Macro table full",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L25 , error )2 "
    push    L25
    call    _error
    sub     sp, -2
L23:
; RPN'ized expression: "MacroTable MacroTableLen ++p + *u l 1 + = "
; Expanded expression: "MacroTable MacroTableLen ++p(2) + (@-2) *(2) 1 + =(1) "
; Fused expression:    "++p(2) *MacroTableLen + MacroTable ax push-ax + *(@-2) 1 =(18) **sp ax "
    mov     ax, [_MacroTableLen]
    inc     word [_MacroTableLen]
    mov     cx, ax
    mov     ax, _MacroTable
    add     ax, cx
    push    ax
    mov     ax, [bp-2]
    add     ax, 1
    pop     bx
    mov     [bx], al
    cbw
; RPN'ized expression: "( name , MacroTable MacroTableLen + strcpy ) "
; Expanded expression: " (@4) *(2)  MacroTable MacroTableLen *(2) +  strcpy ()4 "
; Fused expression:    "( *(2) (@4) , + MacroTable *MacroTableLen , strcpy )4 "
    push    word [bp+4]
    mov     ax, _MacroTable
    add     ax, [_MacroTableLen]
    push    ax
    call    _strcpy
    sub     sp, -4
; RPN'ized expression: "MacroTableLen l 1 + += "
; Expanded expression: "MacroTableLen (@-2) *(2) 1 + +=(2) "
; Fused expression:    "+ *(@-2) 1 +=(34) *MacroTableLen ax "
    mov     ax, [bp-2]
    add     ax, 1
    mov     cx, ax
    mov     ax, [_MacroTableLen]
    add     ax, cx
    mov     [_MacroTableLen], ax
; RPN'ized expression: "MacroTable MacroTableLen + *u 0 = "
; Expanded expression: "MacroTable MacroTableLen *(2) + 0 =(1) "
; Fused expression:    "+ MacroTable *MacroTableLen =(18) *ax 0 "
    mov     ax, _MacroTable
    add     ax, [_MacroTableLen]
    mov     bx, ax
    mov     ax, 0
    mov     [bx], al
    cbw
L18:
    leave
    ret
; SEGMENT _TEXT
; glb AddMacroExpansionChar : (
; prm     e : char
;     ) void
SEGMENT _TEXT
    global  _AddMacroExpansionChar
_AddMacroExpansionChar:
    push    bp
    mov     bp, sp
; loc     e : (@4): char
; if
; RPN'ized expression: "e 0 == "
; Expanded expression: "(@4) *(1) 0 == "
; Fused expression:    "== *(@4) 0 IF! "
    mov     al, [bp+4]
    cbw
    cmp     ax, 0
    jne     L28
; {
; while
; RPN'ized expression: "MacroTable MacroTableLen + *u ( MacroTable MacroTableLen MacroTable MacroTableLen + *u + + *u , L32 strchr ) && "
; Expanded expression: "MacroTable MacroTableLen *(2) + *(1) _Bool [sh&&->34]  MacroTable MacroTableLen *(2) MacroTable MacroTableLen *(2) + *(1) + + *(1)  L32  strchr ()4 _Bool &&[34] "
L30:
; SEGMENT _TEXT
SEGMENT _DATA
L32:
    db  " ",9,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "+ MacroTable *MacroTableLen *(1) ax _Bool [sh&&->34] ( + MacroTable *MacroTableLen + *MacroTableLen *ax + MacroTable ax *(1) ax , L32 , strchr )4 _Bool &&[34] "
    mov     ax, _MacroTable
    add     ax, [_MacroTableLen]
    mov     bx, ax
    mov     al, [bx]
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L34
    mov     ax, _MacroTable
    add     ax, [_MacroTableLen]
    mov     bx, ax
    movsx   cx, byte [bx]
    mov     ax, [_MacroTableLen]
    add     ax, cx
    mov     cx, ax
    mov     ax, _MacroTable
    add     ax, cx
    mov     bx, ax
    mov     al, [bx]
    cbw
    push    ax
    push    L32
    call    _strchr
    sub     sp, -4
    test    ax, ax
    setnz   al
    cbw
L34:
; JumpIfZero
    test    ax, ax
    jz      L31
; RPN'ized expression: "MacroTable MacroTableLen + *u --p "
; Expanded expression: "MacroTable MacroTableLen *(2) + --p(1) "
; Fused expression:    "+ MacroTable *MacroTableLen --p(1) *ax "
    mov     ax, _MacroTable
    add     ax, [_MacroTableLen]
    mov     bx, ax
    mov     al, [bx]
    cbw
    dec     byte [bx]
    jmp     L30
L31:
; RPN'ized expression: "MacroTableLen 1 MacroTable MacroTableLen + *u + += "
; Expanded expression: "MacroTableLen 1 MacroTable MacroTableLen *(2) + *(1) + +=(2) "
; Fused expression:    "+ MacroTable *MacroTableLen + 1 *ax +=(34) *MacroTableLen ax "
    mov     ax, _MacroTable
    add     ax, [_MacroTableLen]
    mov     bx, ax
    movsx   cx, byte [bx]
    mov     ax, 1
    add     ax, cx
    mov     cx, ax
    mov     ax, [_MacroTableLen]
    add     ax, cx
    mov     [_MacroTableLen], ax
; return
    jmp     L27
; }
L28:
; if
; RPN'ized expression: "MacroTableLen 1 + MacroTable MacroTableLen + *u + 4096 >= "
; Expanded expression: "MacroTableLen *(2) 1 + MacroTable MacroTableLen *(2) + *(1) + 4096 >= "
; Fused expression:    "+ *MacroTableLen 1 push-ax + MacroTable *MacroTableLen + *sp *ax >= ax 4096 IF! "
    mov     ax, [_MacroTableLen]
    add     ax, 1
    push    ax
    mov     ax, _MacroTable
    add     ax, [_MacroTableLen]
    mov     bx, ax
    movsx   cx, byte [bx]
    pop     ax
    add     ax, cx
    cmp     ax, 4096
    jl      L35
; RPN'ized expression: "( L37 error ) "
; Expanded expression: " L37  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L37:
    db  "Error: Macro table full",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L37 , error )2 "
    push    L37
    call    _error
    sub     sp, -2
L35:
; if
; RPN'ized expression: "MacroTable MacroTableLen + *u 127 >= "
; Expanded expression: "MacroTable MacroTableLen *(2) + *(1) 127 >= "
; Fused expression:    "+ MacroTable *MacroTableLen >= *ax 127 IF! "
    mov     ax, _MacroTable
    add     ax, [_MacroTableLen]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 127
    jl      L39
; RPN'ized expression: "( L41 error ) "
; Expanded expression: " L41  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L41:
    db  "Error: Macro definition too long",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L41 , error )2 "
    push    L41
    call    _error
    sub     sp, -2
L39:
; RPN'ized expression: "MacroTable MacroTableLen 1 + MacroTable MacroTableLen + *u + + *u e = "
; Expanded expression: "MacroTable MacroTableLen *(2) 1 + MacroTable MacroTableLen *(2) + *(1) + + (@4) *(1) =(1) "
; Fused expression:    "+ *MacroTableLen 1 push-ax + MacroTable *MacroTableLen + *sp *ax + MacroTable ax =(17) *ax *(@4) "
    mov     ax, [_MacroTableLen]
    add     ax, 1
    push    ax
    mov     ax, _MacroTable
    add     ax, [_MacroTableLen]
    mov     bx, ax
    movsx   cx, byte [bx]
    pop     ax
    add     ax, cx
    mov     cx, ax
    mov     ax, _MacroTable
    add     ax, cx
    mov     bx, ax
    mov     al, [bp+4]
    cbw
    mov     [bx], al
    cbw
; RPN'ized expression: "MacroTable MacroTableLen + *u ++p "
; Expanded expression: "MacroTable MacroTableLen *(2) + ++p(1) "
; Fused expression:    "+ MacroTable *MacroTableLen ++p(1) *ax "
    mov     ax, _MacroTable
    add     ax, [_MacroTableLen]
    mov     bx, ax
    mov     al, [bx]
    cbw
    inc     byte [bx]
L27:
    leave
    ret
; SEGMENT _TEXT
; glb DumpMacroTable : (void) void
SEGMENT _TEXT
    global  _DumpMacroTable
_DumpMacroTable:
    push    bp
    mov     bp, sp
; loc     i : (@-2): int
    sub     sp, 2
; loc     j : (@-4): int
    sub     sp, 2
; RPN'ized expression: "( L44 printf ) "
; Expanded expression: " L44  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L44:
    db  10,"; Macro table:",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L44 , printf )2 "
    push    L44
    call    _printf
    sub     sp, -2
; for
; RPN'ized expression: "i 0 = "
; Expanded expression: "(@-2) 0 =(2) "
; Fused expression:    "=(34) *(@-2) 0 "
    mov     ax, 0
    mov     [bp-2], ax
L46:
; RPN'ized expression: "i MacroTableLen < "
; Expanded expression: "(@-2) *(2) MacroTableLen *(2) < "
; Fused expression:    "< *(@-2) *MacroTableLen IF! "
    mov     ax, [bp-2]
    cmp     ax, [_MacroTableLen]
    jge     L49
    jmp     L48
L47:
    jmp     L46
L48:
; {
; RPN'ized expression: "( MacroTable i + 1 + , L50 printf ) "
; Expanded expression: " MacroTable (@-2) *(2) + 1 +  L50  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L50:
    db  "; Macro %s = ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( + MacroTable *(@-2) + ax 1 , L50 , printf )4 "
    mov     ax, _MacroTable
    add     ax, [bp-2]
    add     ax, 1
    push    ax
    push    L50
    call    _printf
    sub     sp, -4
; RPN'ized expression: "i i 1 + MacroTable i + *u + = "
; Expanded expression: "(@-2) (@-2) *(2) 1 + MacroTable (@-2) *(2) + *(1) + =(2) "
; Fused expression:    "+ *(@-2) 1 push-ax + MacroTable *(@-2) + *sp *ax =(34) *(@-2) ax "
    mov     ax, [bp-2]
    add     ax, 1
    push    ax
    mov     ax, _MacroTable
    add     ax, [bp-2]
    mov     bx, ax
    movsx   cx, byte [bx]
    pop     ax
    add     ax, cx
    mov     [bp-2], ax
; RPN'ized expression: "( L52 printf ) "
; Expanded expression: " L52  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L52:
    db  "`",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L52 , printf )2 "
    push    L52
    call    _printf
    sub     sp, -2
; RPN'ized expression: "j MacroTable i ++p + *u = "
; Expanded expression: "(@-4) MacroTable (@-2) ++p(2) + *(1) =(2) "
; Fused expression:    "++p(2) *(@-2) + MacroTable ax =(33) *(@-4) *ax "
    mov     ax, [bp-2]
    inc     word [bp-2]
    mov     cx, ax
    mov     ax, _MacroTable
    add     ax, cx
    mov     bx, ax
    mov     al, [bx]
    cbw
    mov     [bp-4], ax
; while
; RPN'ized expression: "j --p "
; Expanded expression: "(@-4) --p(2) "
L54:
; Fused expression:    "--p(2) *(@-4) "
    mov     ax, [bp-4]
    dec     word [bp-4]
; JumpIfZero
    test    ax, ax
    jz      L55
; RPN'ized expression: "( MacroTable i ++p + *u , L56 printf ) "
; Expanded expression: " MacroTable (@-2) ++p(2) + *(1)  L56  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L56:
    db  "%c",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ++p(2) *(@-2) + MacroTable ax *(1) ax , L56 , printf )4 "
    mov     ax, [bp-2]
    inc     word [bp-2]
    mov     cx, ax
    mov     ax, _MacroTable
    add     ax, cx
    mov     bx, ax
    mov     al, [bx]
    cbw
    push    ax
    push    L56
    call    _printf
    sub     sp, -4
    jmp     L54
L55:
; RPN'ized expression: "( L58 printf ) "
; Expanded expression: " L58  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L58:
    db  "`",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L58 , printf )2 "
    push    L58
    call    _printf
    sub     sp, -2
; }
    jmp     L47
L49:
; RPN'ized expression: "( 4096 , MacroTableLen , L60 printf ) "
; Expanded expression: " 4096  MacroTableLen *(2)  L60  printf ()6 "
; SEGMENT _TEXT
SEGMENT _DATA
L60:
    db  "; Bytes used: %d/%d",10,10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 4096 , *(2) MacroTableLen , L60 , printf )6 "
    push    4096
    push    word [_MacroTableLen]
    push    L60
    call    _printf
    sub     sp, -6
L43:
    leave
    ret
; SEGMENT _TEXT
; glb PurgeStringTable : (void) void
SEGMENT _TEXT
    global  _PurgeStringTable
_PurgeStringTable:
    push    bp
    mov     bp, sp
; RPN'ized expression: "StringTableLen 0 = "
; Expanded expression: "StringTableLen 0 =(2) "
; Fused expression:    "=(34) *StringTableLen 0 "
    mov     ax, 0
    mov     [_StringTableLen], ax
L62:
    leave
    ret
; SEGMENT _TEXT
; glb AddString : (
; prm     label : int
; prm     str : * char
; prm     len : int
;     ) void
SEGMENT _TEXT
    global  _AddString
_AddString:
    push    bp
    mov     bp, sp
; loc     label : (@4): int
; loc     str : (@6): * char
; loc     len : (@8): int
; if
; RPN'ized expression: "len 127 > "
; Expanded expression: "(@8) *(2) 127 > "
; Fused expression:    "> *(@8) 127 IF! "
    mov     ax, [bp+8]
    cmp     ax, 127
    jle     L64
; RPN'ized expression: "( L66 error ) "
; Expanded expression: " L66  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L66:
    db  "Error: String too long",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L66 , error )2 "
    push    L66
    call    _error
    sub     sp, -2
L64:
; if
; RPN'ized expression: "512 StringTableLen - label sizeof 1 + len + < "
; Expanded expression: "512 StringTableLen *(2) - 3 (@8) *(2) + < "
; Fused expression:    "- 512 *StringTableLen push-ax + 3 *(@8) < *sp ax IF! "
    mov     ax, 512
    sub     ax, [_StringTableLen]
    push    ax
    mov     ax, 3
    add     ax, [bp+8]
    mov     cx, ax
    pop     ax
    cmp     ax, cx
    jge     L68
; RPN'ized expression: "( L70 error ) "
; Expanded expression: " L70  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L70:
    db  "Error: String table full",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L70 , error )2 "
    push    L70
    call    _error
    sub     sp, -2
L68:
; RPN'ized expression: "( label sizeof , label &u , StringTable StringTableLen + memcpy ) "
; Expanded expression: " 2  (@4)  StringTable StringTableLen *(2) +  memcpy ()6 "
; Fused expression:    "( 2 , (@4) , + StringTable *StringTableLen , memcpy )6 "
    push    2
    lea     ax, [bp+4]
    push    ax
    mov     ax, _StringTable
    add     ax, [_StringTableLen]
    push    ax
    call    _memcpy
    sub     sp, -6
; RPN'ized expression: "StringTableLen label sizeof += "
; Expanded expression: "StringTableLen 2 +=(2) "
; Fused expression:    "+=(34) *StringTableLen 2 "
    mov     ax, [_StringTableLen]
    add     ax, 2
    mov     [_StringTableLen], ax
; RPN'ized expression: "StringTable StringTableLen ++p + *u len = "
; Expanded expression: "StringTable StringTableLen ++p(2) + (@8) *(2) =(1) "
; Fused expression:    "++p(2) *StringTableLen + StringTable ax =(18) *ax *(@8) "
    mov     ax, [_StringTableLen]
    inc     word [_StringTableLen]
    mov     cx, ax
    mov     ax, _StringTable
    add     ax, cx
    mov     bx, ax
    mov     ax, [bp+8]
    mov     [bx], al
    cbw
; RPN'ized expression: "( len , str , StringTable StringTableLen + memcpy ) "
; Expanded expression: " (@8) *(2)  (@6) *(2)  StringTable StringTableLen *(2) +  memcpy ()6 "
; Fused expression:    "( *(2) (@8) , *(2) (@6) , + StringTable *StringTableLen , memcpy )6 "
    push    word [bp+8]
    push    word [bp+6]
    mov     ax, _StringTable
    add     ax, [_StringTableLen]
    push    ax
    call    _memcpy
    sub     sp, -6
; RPN'ized expression: "StringTableLen len += "
; Expanded expression: "StringTableLen (@8) *(2) +=(2) "
; Fused expression:    "+=(34) *StringTableLen *(@8) "
    mov     ax, [_StringTableLen]
    add     ax, [bp+8]
    mov     [_StringTableLen], ax
L63:
    leave
    ret
; SEGMENT _TEXT
; glb FindString : (
; prm     label : int
;     ) * char
SEGMENT _TEXT
    global  _FindString
_FindString:
    push    bp
    mov     bp, sp
; loc     label : (@4): int
; loc     i : (@-2): int
    sub     sp, 2
; for
; RPN'ized expression: "i 0 = "
; Expanded expression: "(@-2) 0 =(2) "
; Fused expression:    "=(34) *(@-2) 0 "
    mov     ax, 0
    mov     [bp-2], ax
L73:
; RPN'ized expression: "i StringTableLen < "
; Expanded expression: "(@-2) *(2) StringTableLen *(2) < "
; Fused expression:    "< *(@-2) *StringTableLen IF! "
    mov     ax, [bp-2]
    cmp     ax, [_StringTableLen]
    jge     L76
    jmp     L75
L74:
    jmp     L73
L75:
; {
; loc         lab : (@-4): int
    sub     sp, 2
; RPN'ized expression: "( lab sizeof , StringTable i + , lab &u memcpy ) "
; Expanded expression: " 2  StringTable (@-2) *(2) +  (@-4)  memcpy ()6 "
; Fused expression:    "( 2 , + StringTable *(@-2) , (@-4) , memcpy )6 "
    push    2
    mov     ax, _StringTable
    add     ax, [bp-2]
    push    ax
    lea     ax, [bp-4]
    push    ax
    call    _memcpy
    sub     sp, -6
; if
; RPN'ized expression: "lab label == "
; Expanded expression: "(@-4) *(2) (@4) *(2) == "
; Fused expression:    "== *(@-4) *(@4) IF! "
    mov     ax, [bp-4]
    cmp     ax, [bp+4]
    jne     L77
; return
; RPN'ized expression: "StringTable i + lab sizeof + "
; Expanded expression: "StringTable (@-2) *(2) + 2 + "
; Fused expression:    "+ StringTable *(@-2) + ax 2 "
    mov     ax, _StringTable
    add     ax, [bp-2]
    add     ax, 2
    jmp     L72
L77:
; RPN'ized expression: "i lab sizeof += "
; Expanded expression: "(@-2) 2 +=(2) "
; Fused expression:    "+=(34) *(@-2) 2 "
    mov     ax, [bp-2]
    add     ax, 2
    mov     [bp-2], ax
; RPN'ized expression: "i 1 StringTable i + *u + += "
; Expanded expression: "(@-2) 1 StringTable (@-2) *(2) + *(1) + +=(2) "
; Fused expression:    "+ StringTable *(@-2) + 1 *ax +=(34) *(@-2) ax "
    mov     ax, _StringTable
    add     ax, [bp-2]
    mov     bx, ax
    movsx   cx, byte [bx]
    mov     ax, 1
    add     ax, cx
    mov     cx, ax
    mov     ax, [bp-2]
    add     ax, cx
    mov     [bp-2], ax
    sub     sp, -2
; }
    jmp     L74
L76:
; return
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "0 "
    mov     ax, 0
    jmp     L72
L72:
    leave
    ret
; SEGMENT _TEXT
; glb FindIdent : (
; prm     name : * char
;     ) int
SEGMENT _TEXT
    global  _FindIdent
_FindIdent:
    push    bp
    mov     bp, sp
; loc     name : (@4): * char
; loc     i : (@-2): int
    sub     sp, 2
; for
; RPN'ized expression: "i IdentTableLen = "
; Expanded expression: "(@-2) IdentTableLen *(2) =(2) "
; Fused expression:    "=(34) *(@-2) *IdentTableLen "
    mov     ax, [_IdentTableLen]
    mov     [bp-2], ax
L80:
; RPN'ized expression: "i 0 > "
; Expanded expression: "(@-2) *(2) 0 > "
; Fused expression:    "> *(@-2) 0 IF! "
    mov     ax, [bp-2]
    cmp     ax, 0
    jle     L83
    jmp     L82
L81:
    jmp     L80
L82:
; {
; RPN'ized expression: "i 1 IdentTable i 1 - + *u + -= "
; Expanded expression: "(@-2) 1 IdentTable (@-2) *(2) 1 - + *(1) + -=(2) "
; Fused expression:    "- *(@-2) 1 + IdentTable ax + 1 *ax -=(34) *(@-2) ax "
    mov     ax, [bp-2]
    sub     ax, 1
    mov     cx, ax
    mov     ax, _IdentTable
    add     ax, cx
    mov     bx, ax
    movsx   cx, byte [bx]
    mov     ax, 1
    add     ax, cx
    mov     cx, ax
    mov     ax, [bp-2]
    sub     ax, cx
    mov     [bp-2], ax
; if
; RPN'ized expression: "( name , IdentTable i + strcmp ) 0 == "
; Expanded expression: " (@4) *(2)  IdentTable (@-2) *(2) +  strcmp ()4 0 == "
; Fused expression:    "( *(2) (@4) , + IdentTable *(@-2) , strcmp )4 == ax 0 IF! "
    push    word [bp+4]
    mov     ax, _IdentTable
    add     ax, [bp-2]
    push    ax
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L84
; return
; RPN'ized expression: "i "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
    mov     ax, [bp-2]
    jmp     L79
L84:
; }
    jmp     L81
L83:
; return
; RPN'ized expression: "1 -u "
; Expanded expression: "-1 "
; Expression value: -1
; Fused expression:    "-1 "
    mov     ax, -1
    jmp     L79
L79:
    leave
    ret
; SEGMENT _TEXT
; glb AddIdent : (
; prm     name : * char
;     ) int
SEGMENT _TEXT
    global  _AddIdent
_AddIdent:
    push    bp
    mov     bp, sp
; loc     name : (@4): * char
; loc     i : (@-2): int
    sub     sp, 2
; loc     len : (@-4): int
    sub     sp, 2
; if
; RPN'ized expression: "i ( name FindIdent ) = 0 >= "
; Expanded expression: "(@-2)  (@4) *(2)  FindIdent ()2 =(2) 0 >= "
; Fused expression:    "( *(2) (@4) , FindIdent )2 =(34) *(@-2) ax >= ax 0 IF! "
    push    word [bp+4]
    call    _FindIdent
    sub     sp, -2
    mov     [bp-2], ax
    cmp     ax, 0
    jl      L87
; return
; RPN'ized expression: "i "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
    mov     ax, [bp-2]
    jmp     L86
L87:
; RPN'ized expression: "i IdentTableLen = "
; Expanded expression: "(@-2) IdentTableLen *(2) =(2) "
; Fused expression:    "=(34) *(@-2) *IdentTableLen "
    mov     ax, [_IdentTableLen]
    mov     [bp-2], ax
; RPN'ized expression: "len ( name strlen ) = "
; Expanded expression: "(@-4)  (@4) *(2)  strlen ()2 =(2) "
; Fused expression:    "( *(2) (@4) , strlen )2 =(34) *(@-4) ax "
    push    word [bp+4]
    call    _strlen
    sub     sp, -2
    mov     [bp-4], ax
; if
; RPN'ized expression: "len 127 >= "
; Expanded expression: "(@-4) *(2) 127 >= "
; Fused expression:    ">= *(@-4) 127 IF! "
    mov     ax, [bp-4]
    cmp     ax, 127
    jl      L89
; RPN'ized expression: "( L91 error ) "
; Expanded expression: " L91  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L91:
    db  "Error: Identifier table too long",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L91 , error )2 "
    push    L91
    call    _error
    sub     sp, -2
L89:
; if
; RPN'ized expression: "4096 IdentTableLen - len 2 + < "
; Expanded expression: "4096 IdentTableLen *(2) - (@-4) *(2) 2 + < "
; Fused expression:    "- 4096 *IdentTableLen push-ax + *(@-4) 2 < *sp ax IF! "
    mov     ax, 4096
    sub     ax, [_IdentTableLen]
    push    ax
    mov     ax, [bp-4]
    add     ax, 2
    mov     cx, ax
    pop     ax
    cmp     ax, cx
    jge     L93
; RPN'ized expression: "( L95 error ) "
; Expanded expression: " L95  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L95:
    db  "Error: Identifier table full",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L95 , error )2 "
    push    L95
    call    _error
    sub     sp, -2
L93:
; RPN'ized expression: "( name , IdentTable IdentTableLen + strcpy ) "
; Expanded expression: " (@4) *(2)  IdentTable IdentTableLen *(2) +  strcpy ()4 "
; Fused expression:    "( *(2) (@4) , + IdentTable *IdentTableLen , strcpy )4 "
    push    word [bp+4]
    mov     ax, _IdentTable
    add     ax, [_IdentTableLen]
    push    ax
    call    _strcpy
    sub     sp, -4
; RPN'ized expression: "IdentTableLen len 1 + += "
; Expanded expression: "IdentTableLen (@-4) *(2) 1 + +=(2) "
; Fused expression:    "+ *(@-4) 1 +=(34) *IdentTableLen ax "
    mov     ax, [bp-4]
    add     ax, 1
    mov     cx, ax
    mov     ax, [_IdentTableLen]
    add     ax, cx
    mov     [_IdentTableLen], ax
; RPN'ized expression: "IdentTable IdentTableLen ++p + *u len 1 + = "
; Expanded expression: "IdentTable IdentTableLen ++p(2) + (@-4) *(2) 1 + =(1) "
; Fused expression:    "++p(2) *IdentTableLen + IdentTable ax push-ax + *(@-4) 1 =(18) **sp ax "
    mov     ax, [_IdentTableLen]
    inc     word [_IdentTableLen]
    mov     cx, ax
    mov     ax, _IdentTable
    add     ax, cx
    push    ax
    mov     ax, [bp-4]
    add     ax, 1
    pop     bx
    mov     [bx], al
    cbw
; return
; RPN'ized expression: "i "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
    mov     ax, [bp-2]
    jmp     L86
L86:
    leave
    ret
; SEGMENT _TEXT
; glb DumpIdentTable : (void) void
SEGMENT _TEXT
    global  _DumpIdentTable
_DumpIdentTable:
    push    bp
    mov     bp, sp
; loc     i : (@-2): int
    sub     sp, 2
; RPN'ized expression: "( L98 printf ) "
; Expanded expression: " L98  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L98:
    db  10,"; Identifier table:",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L98 , printf )2 "
    push    L98
    call    _printf
    sub     sp, -2
; for
; RPN'ized expression: "i 0 = "
; Expanded expression: "(@-2) 0 =(2) "
; Fused expression:    "=(34) *(@-2) 0 "
    mov     ax, 0
    mov     [bp-2], ax
L100:
; RPN'ized expression: "i IdentTableLen < "
; Expanded expression: "(@-2) *(2) IdentTableLen *(2) < "
; Fused expression:    "< *(@-2) *IdentTableLen IF! "
    mov     ax, [bp-2]
    cmp     ax, [_IdentTableLen]
    jge     L103
    jmp     L102
L101:
    jmp     L100
L102:
; {
; RPN'ized expression: "( IdentTable i + , L104 printf ) "
; Expanded expression: " IdentTable (@-2) *(2) +  L104  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L104:
    db  "; Ident %s",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( + IdentTable *(@-2) , L104 , printf )4 "
    mov     ax, _IdentTable
    add     ax, [bp-2]
    push    ax
    push    L104
    call    _printf
    sub     sp, -4
; RPN'ized expression: "i ( IdentTable i + strlen ) 2 + += "
; Expanded expression: "(@-2)  IdentTable (@-2) *(2) +  strlen ()2 2 + +=(2) "
; Fused expression:    "( + IdentTable *(@-2) , strlen )2 + ax 2 +=(34) *(@-2) ax "
    mov     ax, _IdentTable
    add     ax, [bp-2]
    push    ax
    call    _strlen
    sub     sp, -2
    add     ax, 2
    mov     cx, ax
    mov     ax, [bp-2]
    add     ax, cx
    mov     [bp-2], ax
; }
    jmp     L101
L103:
; RPN'ized expression: "( 4096 , IdentTableLen , L106 printf ) "
; Expanded expression: " 4096  IdentTableLen *(2)  L106  printf ()6 "
; SEGMENT _TEXT
SEGMENT _DATA
L106:
    db  "; Bytes used: %d/%d",10,10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 4096 , *(2) IdentTableLen , L106 , printf )6 "
    push    4096
    push    word [_IdentTableLen]
    push    L106
    call    _printf
    sub     sp, -6
L97:
    leave
    ret
; SEGMENT _TEXT
; glb GetTokenByWord : (
; prm     word : * char
;     ) int
SEGMENT _TEXT
    global  _GetTokenByWord
_GetTokenByWord:
    push    bp
    mov     bp, sp
; loc     word : (@4): * char
; if
; RPN'ized expression: "( L111 , word strcmp ) 0 == "
; Expanded expression: " L111  (@4) *(2)  strcmp ()4 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L111:
    db  "break",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L111 , *(2) (@4) , strcmp )4 == ax 0 IF! "
    push    L111
    push    word [bp+4]
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L109
; return
; RPN'ized expression: "26 "
; Expanded expression: "26 "
; Expression value: 26
; Fused expression:    "26 "
    mov     ax, 26
    jmp     L108
L109:
; if
; RPN'ized expression: "( L115 , word strcmp ) 0 == "
; Expanded expression: " L115  (@4) *(2)  strcmp ()4 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L115:
    db  "case",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L115 , *(2) (@4) , strcmp )4 == ax 0 IF! "
    push    L115
    push    word [bp+4]
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L113
; return
; RPN'ized expression: "118 "
; Expanded expression: "118 "
; Expression value: 118
; Fused expression:    "118 "
    mov     ax, 118
    jmp     L108
L113:
; if
; RPN'ized expression: "( L119 , word strcmp ) 0 == "
; Expanded expression: " L119  (@4) *(2)  strcmp ()4 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L119:
    db  "char",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L119 , *(2) (@4) , strcmp )4 == ax 0 IF! "
    push    L119
    push    word [bp+4]
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L117
; return
; RPN'ized expression: "18 "
; Expanded expression: "18 "
; Expression value: 18
; Fused expression:    "18 "
    mov     ax, 18
    jmp     L108
L117:
; if
; RPN'ized expression: "( L123 , word strcmp ) 0 == "
; Expanded expression: " L123  (@4) *(2)  strcmp ()4 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L123:
    db  "continue",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L123 , *(2) (@4) , strcmp )4 == ax 0 IF! "
    push    L123
    push    word [bp+4]
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L121
; return
; RPN'ized expression: "25 "
; Expanded expression: "25 "
; Expression value: 25
; Fused expression:    "25 "
    mov     ax, 25
    jmp     L108
L121:
; if
; RPN'ized expression: "( L127 , word strcmp ) 0 == "
; Expanded expression: " L127  (@4) *(2)  strcmp ()4 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L127:
    db  "default",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L127 , *(2) (@4) , strcmp )4 == ax 0 IF! "
    push    L127
    push    word [bp+4]
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L125
; return
; RPN'ized expression: "119 "
; Expanded expression: "119 "
; Expression value: 119
; Fused expression:    "119 "
    mov     ax, 119
    jmp     L108
L125:
; if
; RPN'ized expression: "( L131 , word strcmp ) 0 == "
; Expanded expression: " L131  (@4) *(2)  strcmp ()4 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L131:
    db  "do",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L131 , *(2) (@4) , strcmp )4 == ax 0 IF! "
    push    L131
    push    word [bp+4]
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L129
; return
; RPN'ized expression: "115 "
; Expanded expression: "115 "
; Expression value: 115
; Fused expression:    "115 "
    mov     ax, 115
    jmp     L108
L129:
; if
; RPN'ized expression: "( L135 , word strcmp ) 0 == "
; Expanded expression: " L135  (@4) *(2)  strcmp ()4 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L135:
    db  "else",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L135 , *(2) (@4) , strcmp )4 == ax 0 IF! "
    push    L135
    push    word [bp+4]
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L133
; return
; RPN'ized expression: "23 "
; Expanded expression: "23 "
; Expression value: 23
; Fused expression:    "23 "
    mov     ax, 23
    jmp     L108
L133:
; if
; RPN'ized expression: "( L139 , word strcmp ) 0 == "
; Expanded expression: " L139  (@4) *(2)  strcmp ()4 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L139:
    db  "extern",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L139 , *(2) (@4) , strcmp )4 == ax 0 IF! "
    push    L139
    push    word [bp+4]
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L137
; return
; RPN'ized expression: "108 "
; Expanded expression: "108 "
; Expression value: 108
; Fused expression:    "108 "
    mov     ax, 108
    jmp     L108
L137:
; if
; RPN'ized expression: "( L143 , word strcmp ) 0 == "
; Expanded expression: " L143  (@4) *(2)  strcmp ()4 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L143:
    db  "for",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L143 , *(2) (@4) , strcmp )4 == ax 0 IF! "
    push    L143
    push    word [bp+4]
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L141
; return
; RPN'ized expression: "116 "
; Expanded expression: "116 "
; Expression value: 116
; Fused expression:    "116 "
    mov     ax, 116
    jmp     L108
L141:
; if
; RPN'ized expression: "( L147 , word strcmp ) 0 == "
; Expanded expression: " L147  (@4) *(2)  strcmp ()4 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L147:
    db  "if",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L147 , *(2) (@4) , strcmp )4 == ax 0 IF! "
    push    L147
    push    word [bp+4]
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L145
; return
; RPN'ized expression: "22 "
; Expanded expression: "22 "
; Expression value: 22
; Fused expression:    "22 "
    mov     ax, 22
    jmp     L108
L145:
; if
; RPN'ized expression: "( L151 , word strcmp ) 0 == "
; Expanded expression: " L151  (@4) *(2)  strcmp ()4 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L151:
    db  "int",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L151 , *(2) (@4) , strcmp )4 == ax 0 IF! "
    push    L151
    push    word [bp+4]
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L149
; return
; RPN'ized expression: "19 "
; Expanded expression: "19 "
; Expression value: 19
; Fused expression:    "19 "
    mov     ax, 19
    jmp     L108
L149:
; if
; RPN'ized expression: "( L155 , word strcmp ) 0 == "
; Expanded expression: " L155  (@4) *(2)  strcmp ()4 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L155:
    db  "return",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L155 , *(2) (@4) , strcmp )4 == ax 0 IF! "
    push    L155
    push    word [bp+4]
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L153
; return
; RPN'ized expression: "20 "
; Expanded expression: "20 "
; Expression value: 20
; Fused expression:    "20 "
    mov     ax, 20
    jmp     L108
L153:
; if
; RPN'ized expression: "( L159 , word strcmp ) 0 == "
; Expanded expression: " L159  (@4) *(2)  strcmp ()4 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L159:
    db  "sizeof",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L159 , *(2) (@4) , strcmp )4 == ax 0 IF! "
    push    L159
    push    word [bp+4]
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L157
; return
; RPN'ized expression: "27 "
; Expanded expression: "27 "
; Expression value: 27
; Fused expression:    "27 "
    mov     ax, 27
    jmp     L108
L157:
; if
; RPN'ized expression: "( L163 , word strcmp ) 0 == "
; Expanded expression: " L163  (@4) *(2)  strcmp ()4 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L163:
    db  "switch",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L163 , *(2) (@4) , strcmp )4 == ax 0 IF! "
    push    L163
    push    word [bp+4]
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L161
; return
; RPN'ized expression: "117 "
; Expanded expression: "117 "
; Expression value: 117
; Fused expression:    "117 "
    mov     ax, 117
    jmp     L108
L161:
; if
; RPN'ized expression: "( L167 , word strcmp ) 0 == "
; Expanded expression: " L167  (@4) *(2)  strcmp ()4 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L167:
    db  "void",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L167 , *(2) (@4) , strcmp )4 == ax 0 IF! "
    push    L167
    push    word [bp+4]
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L165
; return
; RPN'ized expression: "17 "
; Expanded expression: "17 "
; Expression value: 17
; Fused expression:    "17 "
    mov     ax, 17
    jmp     L108
L165:
; if
; RPN'ized expression: "( L171 , word strcmp ) 0 == "
; Expanded expression: " L171  (@4) *(2)  strcmp ()4 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L171:
    db  "while",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L171 , *(2) (@4) , strcmp )4 == ax 0 IF! "
    push    L171
    push    word [bp+4]
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L169
; return
; RPN'ized expression: "24 "
; Expanded expression: "24 "
; Expression value: 24
; Fused expression:    "24 "
    mov     ax, 24
    jmp     L108
L169:
; if
; RPN'ized expression: "( L175 , word strcmp ) 0 == "
; Expanded expression: " L175  (@4) *(2)  strcmp ()4 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L175:
    db  "auto",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L175 , *(2) (@4) , strcmp )4 == ax 0 IF! "
    push    L175
    push    word [bp+4]
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L173
; return
; RPN'ized expression: "109 "
; Expanded expression: "109 "
; Expression value: 109
; Fused expression:    "109 "
    mov     ax, 109
    jmp     L108
L173:
; if
; RPN'ized expression: "( L179 , word strcmp ) 0 == "
; Expanded expression: " L179  (@4) *(2)  strcmp ()4 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L179:
    db  "const",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L179 , *(2) (@4) , strcmp )4 == ax 0 IF! "
    push    L179
    push    word [bp+4]
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L177
; return
; RPN'ized expression: "103 "
; Expanded expression: "103 "
; Expression value: 103
; Fused expression:    "103 "
    mov     ax, 103
    jmp     L108
L177:
; if
; RPN'ized expression: "( L183 , word strcmp ) 0 == "
; Expanded expression: " L183  (@4) *(2)  strcmp ()4 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L183:
    db  "double",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L183 , *(2) (@4) , strcmp )4 == ax 0 IF! "
    push    L183
    push    word [bp+4]
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L181
; return
; RPN'ized expression: "98 "
; Expanded expression: "98 "
; Expression value: 98
; Fused expression:    "98 "
    mov     ax, 98
    jmp     L108
L181:
; if
; RPN'ized expression: "( L187 , word strcmp ) 0 == "
; Expanded expression: " L187  (@4) *(2)  strcmp ()4 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L187:
    db  "enum",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L187 , *(2) (@4) , strcmp )4 == ax 0 IF! "
    push    L187
    push    word [bp+4]
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L185
; return
; RPN'ized expression: "112 "
; Expanded expression: "112 "
; Expression value: 112
; Fused expression:    "112 "
    mov     ax, 112
    jmp     L108
L185:
; if
; RPN'ized expression: "( L191 , word strcmp ) 0 == "
; Expanded expression: " L191  (@4) *(2)  strcmp ()4 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L191:
    db  "float",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L191 , *(2) (@4) , strcmp )4 == ax 0 IF! "
    push    L191
    push    word [bp+4]
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L189
; return
; RPN'ized expression: "97 "
; Expanded expression: "97 "
; Expression value: 97
; Fused expression:    "97 "
    mov     ax, 97
    jmp     L108
L189:
; if
; RPN'ized expression: "( L195 , word strcmp ) 0 == "
; Expanded expression: " L195  (@4) *(2)  strcmp ()4 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L195:
    db  "goto",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L195 , *(2) (@4) , strcmp )4 == ax 0 IF! "
    push    L195
    push    word [bp+4]
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L193
; return
; RPN'ized expression: "21 "
; Expanded expression: "21 "
; Expression value: 21
; Fused expression:    "21 "
    mov     ax, 21
    jmp     L108
L193:
; if
; RPN'ized expression: "( L199 , word strcmp ) 0 == "
; Expanded expression: " L199  (@4) *(2)  strcmp ()4 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L199:
    db  "inline",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L199 , *(2) (@4) , strcmp )4 == ax 0 IF! "
    push    L199
    push    word [bp+4]
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L197
; return
; RPN'ized expression: "107 "
; Expanded expression: "107 "
; Expression value: 107
; Fused expression:    "107 "
    mov     ax, 107
    jmp     L108
L197:
; if
; RPN'ized expression: "( L203 , word strcmp ) 0 == "
; Expanded expression: " L203  (@4) *(2)  strcmp ()4 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L203:
    db  "long",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L203 , *(2) (@4) , strcmp )4 == ax 0 IF! "
    push    L203
    push    word [bp+4]
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L201
; return
; RPN'ized expression: "99 "
; Expanded expression: "99 "
; Expression value: 99
; Fused expression:    "99 "
    mov     ax, 99
    jmp     L108
L201:
; if
; RPN'ized expression: "( L207 , word strcmp ) 0 == "
; Expanded expression: " L207  (@4) *(2)  strcmp ()4 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L207:
    db  "register",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L207 , *(2) (@4) , strcmp )4 == ax 0 IF! "
    push    L207
    push    word [bp+4]
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L205
; return
; RPN'ized expression: "110 "
; Expanded expression: "110 "
; Expression value: 110
; Fused expression:    "110 "
    mov     ax, 110
    jmp     L108
L205:
; if
; RPN'ized expression: "( L211 , word strcmp ) 0 == "
; Expanded expression: " L211  (@4) *(2)  strcmp ()4 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L211:
    db  "restrict",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L211 , *(2) (@4) , strcmp )4 == ax 0 IF! "
    push    L211
    push    word [bp+4]
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L209
; return
; RPN'ized expression: "105 "
; Expanded expression: "105 "
; Expression value: 105
; Fused expression:    "105 "
    mov     ax, 105
    jmp     L108
L209:
; if
; RPN'ized expression: "( L215 , word strcmp ) 0 == "
; Expanded expression: " L215  (@4) *(2)  strcmp ()4 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L215:
    db  "short",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L215 , *(2) (@4) , strcmp )4 == ax 0 IF! "
    push    L215
    push    word [bp+4]
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L213
; return
; RPN'ized expression: "100 "
; Expanded expression: "100 "
; Expression value: 100
; Fused expression:    "100 "
    mov     ax, 100
    jmp     L108
L213:
; if
; RPN'ized expression: "( L219 , word strcmp ) 0 == "
; Expanded expression: " L219  (@4) *(2)  strcmp ()4 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L219:
    db  "signed",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L219 , *(2) (@4) , strcmp )4 == ax 0 IF! "
    push    L219
    push    word [bp+4]
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L217
; return
; RPN'ized expression: "102 "
; Expanded expression: "102 "
; Expression value: 102
; Fused expression:    "102 "
    mov     ax, 102
    jmp     L108
L217:
; if
; RPN'ized expression: "( L223 , word strcmp ) 0 == "
; Expanded expression: " L223  (@4) *(2)  strcmp ()4 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L223:
    db  "static",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L223 , *(2) (@4) , strcmp )4 == ax 0 IF! "
    push    L223
    push    word [bp+4]
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L221
; return
; RPN'ized expression: "106 "
; Expanded expression: "106 "
; Expression value: 106
; Fused expression:    "106 "
    mov     ax, 106
    jmp     L108
L221:
; if
; RPN'ized expression: "( L227 , word strcmp ) 0 == "
; Expanded expression: " L227  (@4) *(2)  strcmp ()4 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L227:
    db  "struct",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L227 , *(2) (@4) , strcmp )4 == ax 0 IF! "
    push    L227
    push    word [bp+4]
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L225
; return
; RPN'ized expression: "113 "
; Expanded expression: "113 "
; Expression value: 113
; Fused expression:    "113 "
    mov     ax, 113
    jmp     L108
L225:
; if
; RPN'ized expression: "( L231 , word strcmp ) 0 == "
; Expanded expression: " L231  (@4) *(2)  strcmp ()4 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L231:
    db  "typedef",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L231 , *(2) (@4) , strcmp )4 == ax 0 IF! "
    push    L231
    push    word [bp+4]
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L229
; return
; RPN'ized expression: "111 "
; Expanded expression: "111 "
; Expression value: 111
; Fused expression:    "111 "
    mov     ax, 111
    jmp     L108
L229:
; if
; RPN'ized expression: "( L235 , word strcmp ) 0 == "
; Expanded expression: " L235  (@4) *(2)  strcmp ()4 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L235:
    db  "union",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L235 , *(2) (@4) , strcmp )4 == ax 0 IF! "
    push    L235
    push    word [bp+4]
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L233
; return
; RPN'ized expression: "114 "
; Expanded expression: "114 "
; Expression value: 114
; Fused expression:    "114 "
    mov     ax, 114
    jmp     L108
L233:
; if
; RPN'ized expression: "( L239 , word strcmp ) 0 == "
; Expanded expression: " L239  (@4) *(2)  strcmp ()4 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L239:
    db  "unsigned",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L239 , *(2) (@4) , strcmp )4 == ax 0 IF! "
    push    L239
    push    word [bp+4]
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L237
; return
; RPN'ized expression: "101 "
; Expanded expression: "101 "
; Expression value: 101
; Fused expression:    "101 "
    mov     ax, 101
    jmp     L108
L237:
; if
; RPN'ized expression: "( L243 , word strcmp ) 0 == "
; Expanded expression: " L243  (@4) *(2)  strcmp ()4 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L243:
    db  "volatile",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L243 , *(2) (@4) , strcmp )4 == ax 0 IF! "
    push    L243
    push    word [bp+4]
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L241
; return
; RPN'ized expression: "104 "
; Expanded expression: "104 "
; Expression value: 104
; Fused expression:    "104 "
    mov     ax, 104
    jmp     L108
L241:
; if
; RPN'ized expression: "( L247 , word strcmp ) 0 == "
; Expanded expression: " L247  (@4) *(2)  strcmp ()4 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L247:
    db  "_Bool",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L247 , *(2) (@4) , strcmp )4 == ax 0 IF! "
    push    L247
    push    word [bp+4]
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L245
; return
; RPN'ized expression: "120 "
; Expanded expression: "120 "
; Expression value: 120
; Fused expression:    "120 "
    mov     ax, 120
    jmp     L108
L245:
; if
; RPN'ized expression: "( L251 , word strcmp ) 0 == "
; Expanded expression: " L251  (@4) *(2)  strcmp ()4 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L251:
    db  "_Complex",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L251 , *(2) (@4) , strcmp )4 == ax 0 IF! "
    push    L251
    push    word [bp+4]
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L249
; return
; RPN'ized expression: "121 "
; Expanded expression: "121 "
; Expression value: 121
; Fused expression:    "121 "
    mov     ax, 121
    jmp     L108
L249:
; if
; RPN'ized expression: "( L255 , word strcmp ) 0 == "
; Expanded expression: " L255  (@4) *(2)  strcmp ()4 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L255:
    db  "_Imaginary",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L255 , *(2) (@4) , strcmp )4 == ax 0 IF! "
    push    L255
    push    word [bp+4]
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L253
; return
; RPN'ized expression: "122 "
; Expanded expression: "122 "
; Expression value: 122
; Fused expression:    "122 "
    mov     ax, 122
    jmp     L108
L253:
; return
; RPN'ized expression: "16 "
; Expanded expression: "16 "
; Expression value: 16
; Fused expression:    "16 "
    mov     ax, 16
    jmp     L108
L108:
    leave
    ret
; SEGMENT _TEXT
; glb GetTokenName : (
; prm     token : int
;     ) * char
SEGMENT _TEXT
    global  _GetTokenName
_GetTokenName:
    push    bp
    mov     bp, sp
; loc     token : (@4): int
; switch
; RPN'ized expression: "token "
; Expanded expression: "(@4) *(2) "
; Fused expression:    "*(2) (@4) "
    mov     ax, [bp+4]
    jmp     L260
; {
; case
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
    jmp     L261
L260:
    cmp     ax, 0
    jne     L262
L261:
; return
; RPN'ized expression: "L264 "
; Expanded expression: "L264 "
; SEGMENT _TEXT
SEGMENT _DATA
L264:
    db  "<EOF>",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L264 "
    mov     ax, L264
    jmp     L257
; case
; RPN'ized expression: "43 "
; Expanded expression: "43 "
; Expression value: 43
    jmp     L263
L262:
    cmp     ax, 43
    jne     L266
L263:
; return
; RPN'ized expression: "L268 "
; Expanded expression: "L268 "
; SEGMENT _TEXT
SEGMENT _DATA
L268:
    db  "+",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L268 "
    mov     ax, L268
    jmp     L257
; case
; RPN'ized expression: "45 "
; Expanded expression: "45 "
; Expression value: 45
    jmp     L267
L266:
    cmp     ax, 45
    jne     L270
L267:
; return
; RPN'ized expression: "L272 "
; Expanded expression: "L272 "
; SEGMENT _TEXT
SEGMENT _DATA
L272:
    db  "-",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L272 "
    mov     ax, L272
    jmp     L257
; case
; RPN'ized expression: "126 "
; Expanded expression: "126 "
; Expression value: 126
    jmp     L271
L270:
    cmp     ax, 126
    jne     L274
L271:
; return
; RPN'ized expression: "L276 "
; Expanded expression: "L276 "
; SEGMENT _TEXT
SEGMENT _DATA
L276:
    db  "~",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L276 "
    mov     ax, L276
    jmp     L257
; case
; RPN'ized expression: "42 "
; Expanded expression: "42 "
; Expression value: 42
    jmp     L275
L274:
    cmp     ax, 42
    jne     L278
L275:
; return
; RPN'ized expression: "L280 "
; Expanded expression: "L280 "
; SEGMENT _TEXT
SEGMENT _DATA
L280:
    db  "*",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L280 "
    mov     ax, L280
    jmp     L257
; case
; RPN'ized expression: "47 "
; Expanded expression: "47 "
; Expression value: 47
    jmp     L279
L278:
    cmp     ax, 47
    jne     L282
L279:
; return
; RPN'ized expression: "L284 "
; Expanded expression: "L284 "
; SEGMENT _TEXT
SEGMENT _DATA
L284:
    db  "/",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L284 "
    mov     ax, L284
    jmp     L257
; case
; RPN'ized expression: "37 "
; Expanded expression: "37 "
; Expression value: 37
    jmp     L283
L282:
    cmp     ax, 37
    jne     L286
L283:
; return
; RPN'ized expression: "L288 "
; Expanded expression: "L288 "
; SEGMENT _TEXT
SEGMENT _DATA
L288:
    db  "%",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L288 "
    mov     ax, L288
    jmp     L257
; case
; RPN'ized expression: "38 "
; Expanded expression: "38 "
; Expression value: 38
    jmp     L287
L286:
    cmp     ax, 38
    jne     L290
L287:
; return
; RPN'ized expression: "L292 "
; Expanded expression: "L292 "
; SEGMENT _TEXT
SEGMENT _DATA
L292:
    db  "&",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L292 "
    mov     ax, L292
    jmp     L257
; case
; RPN'ized expression: "124 "
; Expanded expression: "124 "
; Expression value: 124
    jmp     L291
L290:
    cmp     ax, 124
    jne     L294
L291:
; return
; RPN'ized expression: "L296 "
; Expanded expression: "L296 "
; SEGMENT _TEXT
SEGMENT _DATA
L296:
    db  "|",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L296 "
    mov     ax, L296
    jmp     L257
; case
; RPN'ized expression: "94 "
; Expanded expression: "94 "
; Expression value: 94
    jmp     L295
L294:
    cmp     ax, 94
    jne     L298
L295:
; return
; RPN'ized expression: "L300 "
; Expanded expression: "L300 "
; SEGMENT _TEXT
SEGMENT _DATA
L300:
    db  "^",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L300 "
    mov     ax, L300
    jmp     L257
; case
; RPN'ized expression: "33 "
; Expanded expression: "33 "
; Expression value: 33
    jmp     L299
L298:
    cmp     ax, 33
    jne     L302
L299:
; return
; RPN'ized expression: "L304 "
; Expanded expression: "L304 "
; SEGMENT _TEXT
SEGMENT _DATA
L304:
    db  "!",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L304 "
    mov     ax, L304
    jmp     L257
; case
; RPN'ized expression: "60 "
; Expanded expression: "60 "
; Expression value: 60
    jmp     L303
L302:
    cmp     ax, 60
    jne     L306
L303:
; return
; RPN'ized expression: "L308 "
; Expanded expression: "L308 "
; SEGMENT _TEXT
SEGMENT _DATA
L308:
    db  "<",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L308 "
    mov     ax, L308
    jmp     L257
; case
; RPN'ized expression: "62 "
; Expanded expression: "62 "
; Expression value: 62
    jmp     L307
L306:
    cmp     ax, 62
    jne     L310
L307:
; return
; RPN'ized expression: "L312 "
; Expanded expression: "L312 "
; SEGMENT _TEXT
SEGMENT _DATA
L312:
    db  ">",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L312 "
    mov     ax, L312
    jmp     L257
; case
; RPN'ized expression: "40 "
; Expanded expression: "40 "
; Expression value: 40
    jmp     L311
L310:
    cmp     ax, 40
    jne     L314
L311:
; return
; RPN'ized expression: "L316 "
; Expanded expression: "L316 "
; SEGMENT _TEXT
SEGMENT _DATA
L316:
    db  "(",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L316 "
    mov     ax, L316
    jmp     L257
; case
; RPN'ized expression: "41 "
; Expanded expression: "41 "
; Expression value: 41
    jmp     L315
L314:
    cmp     ax, 41
    jne     L318
L315:
; return
; RPN'ized expression: "L320 "
; Expanded expression: "L320 "
; SEGMENT _TEXT
SEGMENT _DATA
L320:
    db  ")",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L320 "
    mov     ax, L320
    jmp     L257
; case
; RPN'ized expression: "91 "
; Expanded expression: "91 "
; Expression value: 91
    jmp     L319
L318:
    cmp     ax, 91
    jne     L322
L319:
; return
; RPN'ized expression: "L324 "
; Expanded expression: "L324 "
; SEGMENT _TEXT
SEGMENT _DATA
L324:
    db  "[",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L324 "
    mov     ax, L324
    jmp     L257
; case
; RPN'ized expression: "93 "
; Expanded expression: "93 "
; Expression value: 93
    jmp     L323
L322:
    cmp     ax, 93
    jne     L326
L323:
; return
; RPN'ized expression: "L328 "
; Expanded expression: "L328 "
; SEGMENT _TEXT
SEGMENT _DATA
L328:
    db  "]",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L328 "
    mov     ax, L328
    jmp     L257
; case
; RPN'ized expression: "123 "
; Expanded expression: "123 "
; Expression value: 123
    jmp     L327
L326:
    cmp     ax, 123
    jne     L330
L327:
; return
; RPN'ized expression: "L332 "
; Expanded expression: "L332 "
; SEGMENT _TEXT
SEGMENT _DATA
L332:
    db  "{",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L332 "
    mov     ax, L332
    jmp     L257
; case
; RPN'ized expression: "125 "
; Expanded expression: "125 "
; Expression value: 125
    jmp     L331
L330:
    cmp     ax, 125
    jne     L334
L331:
; return
; RPN'ized expression: "L336 "
; Expanded expression: "L336 "
; SEGMENT _TEXT
SEGMENT _DATA
L336:
    db  "}",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L336 "
    mov     ax, L336
    jmp     L257
; case
; RPN'ized expression: "61 "
; Expanded expression: "61 "
; Expression value: 61
    jmp     L335
L334:
    cmp     ax, 61
    jne     L338
L335:
; return
; RPN'ized expression: "L340 "
; Expanded expression: "L340 "
; SEGMENT _TEXT
SEGMENT _DATA
L340:
    db  "=",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L340 "
    mov     ax, L340
    jmp     L257
; case
; RPN'ized expression: "44 "
; Expanded expression: "44 "
; Expression value: 44
    jmp     L339
L338:
    cmp     ax, 44
    jne     L342
L339:
; return
; RPN'ized expression: "L344 "
; Expanded expression: "L344 "
; SEGMENT _TEXT
SEGMENT _DATA
L344:
    db  ",",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L344 "
    mov     ax, L344
    jmp     L257
; case
; RPN'ized expression: "59 "
; Expanded expression: "59 "
; Expression value: 59
    jmp     L343
L342:
    cmp     ax, 59
    jne     L346
L343:
; return
; RPN'ized expression: "L348 "
; Expanded expression: "L348 "
; SEGMENT _TEXT
SEGMENT _DATA
L348:
    db  ";",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L348 "
    mov     ax, L348
    jmp     L257
; case
; RPN'ized expression: "58 "
; Expanded expression: "58 "
; Expression value: 58
    jmp     L347
L346:
    cmp     ax, 58
    jne     L350
L347:
; return
; RPN'ized expression: "L352 "
; Expanded expression: "L352 "
; SEGMENT _TEXT
SEGMENT _DATA
L352:
    db  ":",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L352 "
    mov     ax, L352
    jmp     L257
; case
; RPN'ized expression: "46 "
; Expanded expression: "46 "
; Expression value: 46
    jmp     L351
L350:
    cmp     ax, 46
    jne     L354
L351:
; return
; RPN'ized expression: "L356 "
; Expanded expression: "L356 "
; SEGMENT _TEXT
SEGMENT _DATA
L356:
    db  ".",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L356 "
    mov     ax, L356
    jmp     L257
; case
; RPN'ized expression: "63 "
; Expanded expression: "63 "
; Expression value: 63
    jmp     L355
L354:
    cmp     ax, 63
    jne     L358
L355:
; return
; RPN'ized expression: "L360 "
; Expanded expression: "L360 "
; SEGMENT _TEXT
SEGMENT _DATA
L360:
    db  "?",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L360 "
    mov     ax, L360
    jmp     L257
; case
; RPN'ized expression: "4 "
; Expanded expression: "4 "
; Expression value: 4
    jmp     L359
L358:
    cmp     ax, 4
    jne     L362
L359:
; return
; RPN'ized expression: "L364 "
; Expanded expression: "L364 "
; SEGMENT _TEXT
SEGMENT _DATA
L364:
    db  "<<",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L364 "
    mov     ax, L364
    jmp     L257
; case
; RPN'ized expression: "5 "
; Expanded expression: "5 "
; Expression value: 5
    jmp     L363
L362:
    cmp     ax, 5
    jne     L366
L363:
; return
; RPN'ized expression: "L368 "
; Expanded expression: "L368 "
; SEGMENT _TEXT
SEGMENT _DATA
L368:
    db  ">>",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L368 "
    mov     ax, L368
    jmp     L257
; case
; RPN'ized expression: "6 "
; Expanded expression: "6 "
; Expression value: 6
    jmp     L367
L366:
    cmp     ax, 6
    jne     L370
L367:
; return
; RPN'ized expression: "L372 "
; Expanded expression: "L372 "
; SEGMENT _TEXT
SEGMENT _DATA
L372:
    db  "&&",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L372 "
    mov     ax, L372
    jmp     L257
; case
; RPN'ized expression: "7 "
; Expanded expression: "7 "
; Expression value: 7
    jmp     L371
L370:
    cmp     ax, 7
    jne     L374
L371:
; return
; RPN'ized expression: "L376 "
; Expanded expression: "L376 "
; SEGMENT _TEXT
SEGMENT _DATA
L376:
    db  "||",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L376 "
    mov     ax, L376
    jmp     L257
; case
; RPN'ized expression: "8 "
; Expanded expression: "8 "
; Expression value: 8
    jmp     L375
L374:
    cmp     ax, 8
    jne     L378
L375:
; return
; RPN'ized expression: "L380 "
; Expanded expression: "L380 "
; SEGMENT _TEXT
SEGMENT _DATA
L380:
    db  "==",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L380 "
    mov     ax, L380
    jmp     L257
; case
; RPN'ized expression: "9 "
; Expanded expression: "9 "
; Expression value: 9
    jmp     L379
L378:
    cmp     ax, 9
    jne     L382
L379:
; return
; RPN'ized expression: "L384 "
; Expanded expression: "L384 "
; SEGMENT _TEXT
SEGMENT _DATA
L384:
    db  "!=",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L384 "
    mov     ax, L384
    jmp     L257
; case
; RPN'ized expression: "10 "
; Expanded expression: "10 "
; Expression value: 10
    jmp     L383
L382:
    cmp     ax, 10
    jne     L386
L383:
; return
; RPN'ized expression: "L388 "
; Expanded expression: "L388 "
; SEGMENT _TEXT
SEGMENT _DATA
L388:
    db  "<=",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L388 "
    mov     ax, L388
    jmp     L257
; case
; RPN'ized expression: "11 "
; Expanded expression: "11 "
; Expression value: 11
    jmp     L387
L386:
    cmp     ax, 11
    jne     L390
L387:
; return
; RPN'ized expression: "L392 "
; Expanded expression: "L392 "
; SEGMENT _TEXT
SEGMENT _DATA
L392:
    db  ">=",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L392 "
    mov     ax, L392
    jmp     L257
; case
; RPN'ized expression: "12 "
; Expanded expression: "12 "
; Expression value: 12
    jmp     L391
L390:
    cmp     ax, 12
    jne     L394
L391:
; return
; RPN'ized expression: "L396 "
; Expanded expression: "L396 "
; SEGMENT _TEXT
SEGMENT _DATA
L396:
    db  "++",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L396 "
    mov     ax, L396
    jmp     L257
; case
; RPN'ized expression: "13 "
; Expanded expression: "13 "
; Expression value: 13
    jmp     L395
L394:
    cmp     ax, 13
    jne     L398
L395:
; return
; RPN'ized expression: "L400 "
; Expanded expression: "L400 "
; SEGMENT _TEXT
SEGMENT _DATA
L400:
    db  "--",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L400 "
    mov     ax, L400
    jmp     L257
; case
; RPN'ized expression: "14 "
; Expanded expression: "14 "
; Expression value: 14
    jmp     L399
L398:
    cmp     ax, 14
    jne     L402
L399:
; return
; RPN'ized expression: "L404 "
; Expanded expression: "L404 "
; SEGMENT _TEXT
SEGMENT _DATA
L404:
    db  "->",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L404 "
    mov     ax, L404
    jmp     L257
; case
; RPN'ized expression: "15 "
; Expanded expression: "15 "
; Expression value: 15
    jmp     L403
L402:
    cmp     ax, 15
    jne     L406
L403:
; return
; RPN'ized expression: "L408 "
; Expanded expression: "L408 "
; SEGMENT _TEXT
SEGMENT _DATA
L408:
    db  "...",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L408 "
    mov     ax, L408
    jmp     L257
; case
; RPN'ized expression: "65 "
; Expanded expression: "65 "
; Expression value: 65
    jmp     L407
L406:
    cmp     ax, 65
    jne     L410
L407:
; return
; RPN'ized expression: "L412 "
; Expanded expression: "L412 "
; SEGMENT _TEXT
SEGMENT _DATA
L412:
    db  "*=",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L412 "
    mov     ax, L412
    jmp     L257
; case
; RPN'ized expression: "66 "
; Expanded expression: "66 "
; Expression value: 66
    jmp     L411
L410:
    cmp     ax, 66
    jne     L414
L411:
; return
; RPN'ized expression: "L416 "
; Expanded expression: "L416 "
; SEGMENT _TEXT
SEGMENT _DATA
L416:
    db  "/=",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L416 "
    mov     ax, L416
    jmp     L257
; case
; RPN'ized expression: "67 "
; Expanded expression: "67 "
; Expression value: 67
    jmp     L415
L414:
    cmp     ax, 67
    jne     L418
L415:
; return
; RPN'ized expression: "L420 "
; Expanded expression: "L420 "
; SEGMENT _TEXT
SEGMENT _DATA
L420:
    db  "%=",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L420 "
    mov     ax, L420
    jmp     L257
; case
; RPN'ized expression: "68 "
; Expanded expression: "68 "
; Expression value: 68
    jmp     L419
L418:
    cmp     ax, 68
    jne     L422
L419:
; return
; RPN'ized expression: "L424 "
; Expanded expression: "L424 "
; SEGMENT _TEXT
SEGMENT _DATA
L424:
    db  "+=",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L424 "
    mov     ax, L424
    jmp     L257
; case
; RPN'ized expression: "69 "
; Expanded expression: "69 "
; Expression value: 69
    jmp     L423
L422:
    cmp     ax, 69
    jne     L426
L423:
; return
; RPN'ized expression: "L428 "
; Expanded expression: "L428 "
; SEGMENT _TEXT
SEGMENT _DATA
L428:
    db  "-=",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L428 "
    mov     ax, L428
    jmp     L257
; case
; RPN'ized expression: "70 "
; Expanded expression: "70 "
; Expression value: 70
    jmp     L427
L426:
    cmp     ax, 70
    jne     L430
L427:
; return
; RPN'ized expression: "L432 "
; Expanded expression: "L432 "
; SEGMENT _TEXT
SEGMENT _DATA
L432:
    db  "<<=",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L432 "
    mov     ax, L432
    jmp     L257
; case
; RPN'ized expression: "71 "
; Expanded expression: "71 "
; Expression value: 71
    jmp     L431
L430:
    cmp     ax, 71
    jne     L434
L431:
; return
; RPN'ized expression: "L436 "
; Expanded expression: "L436 "
; SEGMENT _TEXT
SEGMENT _DATA
L436:
    db  ">>=",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L436 "
    mov     ax, L436
    jmp     L257
; case
; RPN'ized expression: "72 "
; Expanded expression: "72 "
; Expression value: 72
    jmp     L435
L434:
    cmp     ax, 72
    jne     L438
L435:
; return
; RPN'ized expression: "L440 "
; Expanded expression: "L440 "
; SEGMENT _TEXT
SEGMENT _DATA
L440:
    db  "&=",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L440 "
    mov     ax, L440
    jmp     L257
; case
; RPN'ized expression: "73 "
; Expanded expression: "73 "
; Expression value: 73
    jmp     L439
L438:
    cmp     ax, 73
    jne     L442
L439:
; return
; RPN'ized expression: "L444 "
; Expanded expression: "L444 "
; SEGMENT _TEXT
SEGMENT _DATA
L444:
    db  "^=",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L444 "
    mov     ax, L444
    jmp     L257
; case
; RPN'ized expression: "74 "
; Expanded expression: "74 "
; Expression value: 74
    jmp     L443
L442:
    cmp     ax, 74
    jne     L446
L443:
; return
; RPN'ized expression: "L448 "
; Expanded expression: "L448 "
; SEGMENT _TEXT
SEGMENT _DATA
L448:
    db  "|=",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L448 "
    mov     ax, L448
    jmp     L257
; case
; RPN'ized expression: "77 "
; Expanded expression: "77 "
; Expression value: 77
    jmp     L447
L446:
    cmp     ax, 77
    jne     L450
L447:
; return
; RPN'ized expression: "L452 "
; Expanded expression: "L452 "
; SEGMENT _TEXT
SEGMENT _DATA
L452:
    db  "&u",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L452 "
    mov     ax, L452
    jmp     L257
; case
; RPN'ized expression: "78 "
; Expanded expression: "78 "
; Expression value: 78
    jmp     L451
L450:
    cmp     ax, 78
    jne     L454
L451:
; return
; RPN'ized expression: "L456 "
; Expanded expression: "L456 "
; SEGMENT _TEXT
SEGMENT _DATA
L456:
    db  "*u",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L456 "
    mov     ax, L456
    jmp     L257
; case
; RPN'ized expression: "79 "
; Expanded expression: "79 "
; Expression value: 79
    jmp     L455
L454:
    cmp     ax, 79
    jne     L458
L455:
; return
; RPN'ized expression: "L460 "
; Expanded expression: "L460 "
; SEGMENT _TEXT
SEGMENT _DATA
L460:
    db  "+u",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L460 "
    mov     ax, L460
    jmp     L257
; case
; RPN'ized expression: "80 "
; Expanded expression: "80 "
; Expression value: 80
    jmp     L459
L458:
    cmp     ax, 80
    jne     L462
L459:
; return
; RPN'ized expression: "L464 "
; Expanded expression: "L464 "
; SEGMENT _TEXT
SEGMENT _DATA
L464:
    db  "-u",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L464 "
    mov     ax, L464
    jmp     L257
; case
; RPN'ized expression: "81 "
; Expanded expression: "81 "
; Expression value: 81
    jmp     L463
L462:
    cmp     ax, 81
    jne     L466
L463:
; return
; RPN'ized expression: "L468 "
; Expanded expression: "L468 "
; SEGMENT _TEXT
SEGMENT _DATA
L468:
    db  "++p",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L468 "
    mov     ax, L468
    jmp     L257
; case
; RPN'ized expression: "82 "
; Expanded expression: "82 "
; Expression value: 82
    jmp     L467
L466:
    cmp     ax, 82
    jne     L470
L467:
; return
; RPN'ized expression: "L472 "
; Expanded expression: "L472 "
; SEGMENT _TEXT
SEGMENT _DATA
L472:
    db  "--p",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L472 "
    mov     ax, L472
    jmp     L257
; case
; RPN'ized expression: "83 "
; Expanded expression: "83 "
; Expression value: 83
    jmp     L471
L470:
    cmp     ax, 83
    jne     L474
L471:
; return
; RPN'ized expression: "L476 "
; Expanded expression: "L476 "
; SEGMENT _TEXT
SEGMENT _DATA
L476:
    db  "+=p",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L476 "
    mov     ax, L476
    jmp     L257
; case
; RPN'ized expression: "84 "
; Expanded expression: "84 "
; Expression value: 84
    jmp     L475
L474:
    cmp     ax, 84
    jne     L478
L475:
; return
; RPN'ized expression: "L480 "
; Expanded expression: "L480 "
; SEGMENT _TEXT
SEGMENT _DATA
L480:
    db  "-=p",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L480 "
    mov     ax, L480
    jmp     L257
; case
; RPN'ized expression: "85 "
; Expanded expression: "85 "
; Expression value: 85
    jmp     L479
L478:
    cmp     ax, 85
    jne     L482
L479:
; return
; RPN'ized expression: "L484 "
; Expanded expression: "L484 "
; SEGMENT _TEXT
SEGMENT _DATA
L484:
    db  "<u",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L484 "
    mov     ax, L484
    jmp     L257
; case
; RPN'ized expression: "86 "
; Expanded expression: "86 "
; Expression value: 86
    jmp     L483
L482:
    cmp     ax, 86
    jne     L486
L483:
; return
; RPN'ized expression: "L488 "
; Expanded expression: "L488 "
; SEGMENT _TEXT
SEGMENT _DATA
L488:
    db  ">u",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L488 "
    mov     ax, L488
    jmp     L257
; case
; RPN'ized expression: "87 "
; Expanded expression: "87 "
; Expression value: 87
    jmp     L487
L486:
    cmp     ax, 87
    jne     L490
L487:
; return
; RPN'ized expression: "L492 "
; Expanded expression: "L492 "
; SEGMENT _TEXT
SEGMENT _DATA
L492:
    db  "<=u",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L492 "
    mov     ax, L492
    jmp     L257
; case
; RPN'ized expression: "88 "
; Expanded expression: "88 "
; Expression value: 88
    jmp     L491
L490:
    cmp     ax, 88
    jne     L494
L491:
; return
; RPN'ized expression: "L496 "
; Expanded expression: "L496 "
; SEGMENT _TEXT
SEGMENT _DATA
L496:
    db  ">=u",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L496 "
    mov     ax, L496
    jmp     L257
; case
; RPN'ized expression: "17 "
; Expanded expression: "17 "
; Expression value: 17
    jmp     L495
L494:
    cmp     ax, 17
    jne     L498
L495:
; return
; RPN'ized expression: "L500 "
; Expanded expression: "L500 "
; SEGMENT _TEXT
SEGMENT _DATA
L500:
    db  "void",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L500 "
    mov     ax, L500
    jmp     L257
; case
; RPN'ized expression: "18 "
; Expanded expression: "18 "
; Expression value: 18
    jmp     L499
L498:
    cmp     ax, 18
    jne     L502
L499:
; return
; RPN'ized expression: "L504 "
; Expanded expression: "L504 "
; SEGMENT _TEXT
SEGMENT _DATA
L504:
    db  "char",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L504 "
    mov     ax, L504
    jmp     L257
; case
; RPN'ized expression: "19 "
; Expanded expression: "19 "
; Expression value: 19
    jmp     L503
L502:
    cmp     ax, 19
    jne     L506
L503:
; return
; RPN'ized expression: "L508 "
; Expanded expression: "L508 "
; SEGMENT _TEXT
SEGMENT _DATA
L508:
    db  "int",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L508 "
    mov     ax, L508
    jmp     L257
; case
; RPN'ized expression: "20 "
; Expanded expression: "20 "
; Expression value: 20
    jmp     L507
L506:
    cmp     ax, 20
    jne     L510
L507:
; return
; RPN'ized expression: "L512 "
; Expanded expression: "L512 "
; SEGMENT _TEXT
SEGMENT _DATA
L512:
    db  "return",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L512 "
    mov     ax, L512
    jmp     L257
; case
; RPN'ized expression: "21 "
; Expanded expression: "21 "
; Expression value: 21
    jmp     L511
L510:
    cmp     ax, 21
    jne     L514
L511:
; return
; RPN'ized expression: "L516 "
; Expanded expression: "L516 "
; SEGMENT _TEXT
SEGMENT _DATA
L516:
    db  "goto",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L516 "
    mov     ax, L516
    jmp     L257
; case
; RPN'ized expression: "22 "
; Expanded expression: "22 "
; Expression value: 22
    jmp     L515
L514:
    cmp     ax, 22
    jne     L518
L515:
; return
; RPN'ized expression: "L520 "
; Expanded expression: "L520 "
; SEGMENT _TEXT
SEGMENT _DATA
L520:
    db  "if",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L520 "
    mov     ax, L520
    jmp     L257
; case
; RPN'ized expression: "23 "
; Expanded expression: "23 "
; Expression value: 23
    jmp     L519
L518:
    cmp     ax, 23
    jne     L522
L519:
; return
; RPN'ized expression: "L524 "
; Expanded expression: "L524 "
; SEGMENT _TEXT
SEGMENT _DATA
L524:
    db  "else",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L524 "
    mov     ax, L524
    jmp     L257
; case
; RPN'ized expression: "24 "
; Expanded expression: "24 "
; Expression value: 24
    jmp     L523
L522:
    cmp     ax, 24
    jne     L526
L523:
; return
; RPN'ized expression: "L528 "
; Expanded expression: "L528 "
; SEGMENT _TEXT
SEGMENT _DATA
L528:
    db  "while",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L528 "
    mov     ax, L528
    jmp     L257
; case
; RPN'ized expression: "25 "
; Expanded expression: "25 "
; Expression value: 25
    jmp     L527
L526:
    cmp     ax, 25
    jne     L530
L527:
; return
; RPN'ized expression: "L532 "
; Expanded expression: "L532 "
; SEGMENT _TEXT
SEGMENT _DATA
L532:
    db  "continue",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L532 "
    mov     ax, L532
    jmp     L257
; case
; RPN'ized expression: "26 "
; Expanded expression: "26 "
; Expression value: 26
    jmp     L531
L530:
    cmp     ax, 26
    jne     L534
L531:
; return
; RPN'ized expression: "L536 "
; Expanded expression: "L536 "
; SEGMENT _TEXT
SEGMENT _DATA
L536:
    db  "break",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L536 "
    mov     ax, L536
    jmp     L257
; case
; RPN'ized expression: "27 "
; Expanded expression: "27 "
; Expression value: 27
    jmp     L535
L534:
    cmp     ax, 27
    jne     L538
L535:
; return
; RPN'ized expression: "L540 "
; Expanded expression: "L540 "
; SEGMENT _TEXT
SEGMENT _DATA
L540:
    db  "sizeof",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L540 "
    mov     ax, L540
    jmp     L257
; case
; RPN'ized expression: "97 "
; Expanded expression: "97 "
; Expression value: 97
    jmp     L539
L538:
    cmp     ax, 97
    jne     L542
L539:
; return
; RPN'ized expression: "L544 "
; Expanded expression: "L544 "
; SEGMENT _TEXT
SEGMENT _DATA
L544:
    db  "float",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L544 "
    mov     ax, L544
    jmp     L257
; case
; RPN'ized expression: "98 "
; Expanded expression: "98 "
; Expression value: 98
    jmp     L543
L542:
    cmp     ax, 98
    jne     L546
L543:
; return
; RPN'ized expression: "L548 "
; Expanded expression: "L548 "
; SEGMENT _TEXT
SEGMENT _DATA
L548:
    db  "double",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L548 "
    mov     ax, L548
    jmp     L257
; case
; RPN'ized expression: "99 "
; Expanded expression: "99 "
; Expression value: 99
    jmp     L547
L546:
    cmp     ax, 99
    jne     L550
L547:
; return
; RPN'ized expression: "L552 "
; Expanded expression: "L552 "
; SEGMENT _TEXT
SEGMENT _DATA
L552:
    db  "long",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L552 "
    mov     ax, L552
    jmp     L257
; case
; RPN'ized expression: "100 "
; Expanded expression: "100 "
; Expression value: 100
    jmp     L551
L550:
    cmp     ax, 100
    jne     L554
L551:
; return
; RPN'ized expression: "L556 "
; Expanded expression: "L556 "
; SEGMENT _TEXT
SEGMENT _DATA
L556:
    db  "short",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L556 "
    mov     ax, L556
    jmp     L257
; case
; RPN'ized expression: "101 "
; Expanded expression: "101 "
; Expression value: 101
    jmp     L555
L554:
    cmp     ax, 101
    jne     L558
L555:
; return
; RPN'ized expression: "L560 "
; Expanded expression: "L560 "
; SEGMENT _TEXT
SEGMENT _DATA
L560:
    db  "unsigned",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L560 "
    mov     ax, L560
    jmp     L257
; case
; RPN'ized expression: "102 "
; Expanded expression: "102 "
; Expression value: 102
    jmp     L559
L558:
    cmp     ax, 102
    jne     L562
L559:
; return
; RPN'ized expression: "L564 "
; Expanded expression: "L564 "
; SEGMENT _TEXT
SEGMENT _DATA
L564:
    db  "signed",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L564 "
    mov     ax, L564
    jmp     L257
; case
; RPN'ized expression: "103 "
; Expanded expression: "103 "
; Expression value: 103
    jmp     L563
L562:
    cmp     ax, 103
    jne     L566
L563:
; return
; RPN'ized expression: "L568 "
; Expanded expression: "L568 "
; SEGMENT _TEXT
SEGMENT _DATA
L568:
    db  "const",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L568 "
    mov     ax, L568
    jmp     L257
; case
; RPN'ized expression: "104 "
; Expanded expression: "104 "
; Expression value: 104
    jmp     L567
L566:
    cmp     ax, 104
    jne     L570
L567:
; return
; RPN'ized expression: "L572 "
; Expanded expression: "L572 "
; SEGMENT _TEXT
SEGMENT _DATA
L572:
    db  "volatile",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L572 "
    mov     ax, L572
    jmp     L257
; case
; RPN'ized expression: "105 "
; Expanded expression: "105 "
; Expression value: 105
    jmp     L571
L570:
    cmp     ax, 105
    jne     L574
L571:
; return
; RPN'ized expression: "L576 "
; Expanded expression: "L576 "
; SEGMENT _TEXT
SEGMENT _DATA
L576:
    db  "restrict",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L576 "
    mov     ax, L576
    jmp     L257
; case
; RPN'ized expression: "106 "
; Expanded expression: "106 "
; Expression value: 106
    jmp     L575
L574:
    cmp     ax, 106
    jne     L578
L575:
; return
; RPN'ized expression: "L580 "
; Expanded expression: "L580 "
; SEGMENT _TEXT
SEGMENT _DATA
L580:
    db  "static",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L580 "
    mov     ax, L580
    jmp     L257
; case
; RPN'ized expression: "107 "
; Expanded expression: "107 "
; Expression value: 107
    jmp     L579
L578:
    cmp     ax, 107
    jne     L582
L579:
; return
; RPN'ized expression: "L584 "
; Expanded expression: "L584 "
; SEGMENT _TEXT
SEGMENT _DATA
L584:
    db  "inline",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L584 "
    mov     ax, L584
    jmp     L257
; case
; RPN'ized expression: "108 "
; Expanded expression: "108 "
; Expression value: 108
    jmp     L583
L582:
    cmp     ax, 108
    jne     L586
L583:
; return
; RPN'ized expression: "L588 "
; Expanded expression: "L588 "
; SEGMENT _TEXT
SEGMENT _DATA
L588:
    db  "extern",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L588 "
    mov     ax, L588
    jmp     L257
; case
; RPN'ized expression: "109 "
; Expanded expression: "109 "
; Expression value: 109
    jmp     L587
L586:
    cmp     ax, 109
    jne     L590
L587:
; return
; RPN'ized expression: "L592 "
; Expanded expression: "L592 "
; SEGMENT _TEXT
SEGMENT _DATA
L592:
    db  "auto",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L592 "
    mov     ax, L592
    jmp     L257
; case
; RPN'ized expression: "110 "
; Expanded expression: "110 "
; Expression value: 110
    jmp     L591
L590:
    cmp     ax, 110
    jne     L594
L591:
; return
; RPN'ized expression: "L596 "
; Expanded expression: "L596 "
; SEGMENT _TEXT
SEGMENT _DATA
L596:
    db  "register",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L596 "
    mov     ax, L596
    jmp     L257
; case
; RPN'ized expression: "111 "
; Expanded expression: "111 "
; Expression value: 111
    jmp     L595
L594:
    cmp     ax, 111
    jne     L598
L595:
; return
; RPN'ized expression: "L600 "
; Expanded expression: "L600 "
; SEGMENT _TEXT
SEGMENT _DATA
L600:
    db  "typedef",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L600 "
    mov     ax, L600
    jmp     L257
; case
; RPN'ized expression: "112 "
; Expanded expression: "112 "
; Expression value: 112
    jmp     L599
L598:
    cmp     ax, 112
    jne     L602
L599:
; return
; RPN'ized expression: "L604 "
; Expanded expression: "L604 "
; SEGMENT _TEXT
SEGMENT _DATA
L604:
    db  "enum",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L604 "
    mov     ax, L604
    jmp     L257
; case
; RPN'ized expression: "113 "
; Expanded expression: "113 "
; Expression value: 113
    jmp     L603
L602:
    cmp     ax, 113
    jne     L606
L603:
; return
; RPN'ized expression: "L608 "
; Expanded expression: "L608 "
; SEGMENT _TEXT
SEGMENT _DATA
L608:
    db  "struct",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L608 "
    mov     ax, L608
    jmp     L257
; case
; RPN'ized expression: "114 "
; Expanded expression: "114 "
; Expression value: 114
    jmp     L607
L606:
    cmp     ax, 114
    jne     L610
L607:
; return
; RPN'ized expression: "L612 "
; Expanded expression: "L612 "
; SEGMENT _TEXT
SEGMENT _DATA
L612:
    db  "union",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L612 "
    mov     ax, L612
    jmp     L257
; case
; RPN'ized expression: "115 "
; Expanded expression: "115 "
; Expression value: 115
    jmp     L611
L610:
    cmp     ax, 115
    jne     L614
L611:
; return
; RPN'ized expression: "L616 "
; Expanded expression: "L616 "
; SEGMENT _TEXT
SEGMENT _DATA
L616:
    db  "do",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L616 "
    mov     ax, L616
    jmp     L257
; case
; RPN'ized expression: "116 "
; Expanded expression: "116 "
; Expression value: 116
    jmp     L615
L614:
    cmp     ax, 116
    jne     L618
L615:
; return
; RPN'ized expression: "L620 "
; Expanded expression: "L620 "
; SEGMENT _TEXT
SEGMENT _DATA
L620:
    db  "for",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L620 "
    mov     ax, L620
    jmp     L257
; case
; RPN'ized expression: "117 "
; Expanded expression: "117 "
; Expression value: 117
    jmp     L619
L618:
    cmp     ax, 117
    jne     L622
L619:
; return
; RPN'ized expression: "L624 "
; Expanded expression: "L624 "
; SEGMENT _TEXT
SEGMENT _DATA
L624:
    db  "switch",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L624 "
    mov     ax, L624
    jmp     L257
; case
; RPN'ized expression: "118 "
; Expanded expression: "118 "
; Expression value: 118
    jmp     L623
L622:
    cmp     ax, 118
    jne     L626
L623:
; return
; RPN'ized expression: "L628 "
; Expanded expression: "L628 "
; SEGMENT _TEXT
SEGMENT _DATA
L628:
    db  "case",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L628 "
    mov     ax, L628
    jmp     L257
; case
; RPN'ized expression: "119 "
; Expanded expression: "119 "
; Expression value: 119
    jmp     L627
L626:
    cmp     ax, 119
    jne     L630
L627:
; return
; RPN'ized expression: "L632 "
; Expanded expression: "L632 "
; SEGMENT _TEXT
SEGMENT _DATA
L632:
    db  "default",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L632 "
    mov     ax, L632
    jmp     L257
; case
; RPN'ized expression: "120 "
; Expanded expression: "120 "
; Expression value: 120
    jmp     L631
L630:
    cmp     ax, 120
    jne     L634
L631:
; return
; RPN'ized expression: "L636 "
; Expanded expression: "L636 "
; SEGMENT _TEXT
SEGMENT _DATA
L636:
    db  "_Bool",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L636 "
    mov     ax, L636
    jmp     L257
; case
; RPN'ized expression: "121 "
; Expanded expression: "121 "
; Expression value: 121
    jmp     L635
L634:
    cmp     ax, 121
    jne     L638
L635:
; return
; RPN'ized expression: "L640 "
; Expanded expression: "L640 "
; SEGMENT _TEXT
SEGMENT _DATA
L640:
    db  "_Complex",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L640 "
    mov     ax, L640
    jmp     L257
; case
; RPN'ized expression: "122 "
; Expanded expression: "122 "
; Expression value: 122
    jmp     L639
L638:
    cmp     ax, 122
    jne     L642
L639:
; return
; RPN'ized expression: "L644 "
; Expanded expression: "L644 "
; SEGMENT _TEXT
SEGMENT _DATA
L644:
    db  "_Imaginary",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L644 "
    mov     ax, L644
    jmp     L257
; case
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
    jmp     L643
L642:
    cmp     ax, 1
    jne     L646
L643:
; return
; RPN'ized expression: "L648 "
; Expanded expression: "L648 "
; SEGMENT _TEXT
SEGMENT _DATA
L648:
    db  "<Num>",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L648 "
    mov     ax, L648
    jmp     L257
; case
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
    jmp     L647
L646:
    cmp     ax, 2
    jne     L650
L647:
; return
; RPN'ized expression: "L652 "
; Expanded expression: "L652 "
; SEGMENT _TEXT
SEGMENT _DATA
L652:
    db  "<LitChar>",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L652 "
    mov     ax, L652
    jmp     L257
; case
; RPN'ized expression: "3 "
; Expanded expression: "3 "
; Expression value: 3
    jmp     L651
L650:
    cmp     ax, 3
    jne     L654
L651:
; return
; RPN'ized expression: "L656 "
; Expanded expression: "L656 "
; SEGMENT _TEXT
SEGMENT _DATA
L656:
    db  "<LitStr>",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L656 "
    mov     ax, L656
    jmp     L257
; case
; RPN'ized expression: "16 "
; Expanded expression: "16 "
; Expression value: 16
    jmp     L655
L654:
    cmp     ax, 16
    jne     L658
L655:
; return
; RPN'ized expression: "L660 "
; Expanded expression: "L660 "
; SEGMENT _TEXT
SEGMENT _DATA
L660:
    db  "<Ident>",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L660 "
    mov     ax, L660
    jmp     L257
; case
; RPN'ized expression: "89 "
; Expanded expression: "89 "
; Expression value: 89
    jmp     L659
L658:
    cmp     ax, 89
    jne     L662
L659:
; return
; RPN'ized expression: "L664 "
; Expanded expression: "L664 "
; SEGMENT _TEXT
SEGMENT _DATA
L664:
    db  "<LocalOfs>",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L664 "
    mov     ax, L664
    jmp     L257
; case
; RPN'ized expression: "90 "
; Expanded expression: "90 "
; Expression value: 90
    jmp     L663
L662:
    cmp     ax, 90
    jne     L666
L663:
; return
; RPN'ized expression: "L668 "
; Expanded expression: "L668 "
; SEGMENT _TEXT
SEGMENT _DATA
L668:
    db  "<ShortCirc>",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L668 "
    mov     ax, L668
    jmp     L257
; }
    jmp     L258
L666:
L258:
; RPN'ized expression: "( token , L670 error ) "
; Expanded expression: " (@4) *(2)  L670  error ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L670:
    db  "Internal Error: GetTokenName(): Invalid token %d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@4) , L670 , error )4 "
    push    word [bp+4]
    push    L670
    call    _error
    sub     sp, -4
; return
; RPN'ized expression: "L672 "
; Expanded expression: "L672 "
; SEGMENT _TEXT
SEGMENT _DATA
L672:
    db  0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L672 "
    mov     ax, L672
    jmp     L257
L257:
    leave
    ret
; SEGMENT _TEXT
; glb GetTokenValueInt : (void) int
SEGMENT _TEXT
    global  _GetTokenValueInt
_GetTokenValueInt:
    push    bp
    mov     bp, sp
; return
; RPN'ized expression: "TokenValueInt "
; Expanded expression: "TokenValueInt *(2) "
; Fused expression:    "*(2) TokenValueInt "
    mov     ax, [_TokenValueInt]
    jmp     L674
L674:
    leave
    ret
; SEGMENT _TEXT
; glb GetTokenValueString : (void) * char
SEGMENT _TEXT
    global  _GetTokenValueString
_GetTokenValueString:
    push    bp
    mov     bp, sp
; return
; RPN'ized expression: "TokenValueString "
; Expanded expression: "TokenValueString "
; Fused expression:    "TokenValueString "
    mov     ax, _TokenValueString
    jmp     L675
L675:
    leave
    ret
; SEGMENT _TEXT
; glb GetTokenValueStringLength : (void) int
SEGMENT _TEXT
    global  _GetTokenValueStringLength
_GetTokenValueStringLength:
    push    bp
    mov     bp, sp
; return
; RPN'ized expression: "TokenStringLen "
; Expanded expression: "TokenStringLen *(2) "
; Fused expression:    "*(2) TokenStringLen "
    mov     ax, [_TokenStringLen]
    jmp     L676
L676:
    leave
    ret
; SEGMENT _TEXT
; glb GetTokenIdentName : (void) * char
SEGMENT _TEXT
    global  _GetTokenIdentName
_GetTokenIdentName:
    push    bp
    mov     bp, sp
; return
; RPN'ized expression: "TokenIdentName "
; Expanded expression: "TokenIdentName "
; Fused expression:    "TokenIdentName "
    mov     ax, _TokenIdentName
    jmp     L677
L677:
    leave
    ret
; SEGMENT _TEXT
; glb GetTokenFileName : (void) * char
SEGMENT _TEXT
    global  _GetTokenFileName
_GetTokenFileName:
    push    bp
    mov     bp, sp
; return
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "0 "
    mov     ax, 0
    jmp     L678
L678:
    leave
    ret
; SEGMENT _TEXT
; glb GetTokenFileLineNo : (void) int
SEGMENT _TEXT
    global  _GetTokenFileLineNo
_GetTokenFileLineNo:
    push    bp
    mov     bp, sp
; return
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "0 "
    mov     ax, 0
    jmp     L679
L679:
    leave
    ret
; SEGMENT _TEXT
; glb GetTokenFileLinePos : (void) int
SEGMENT _TEXT
    global  _GetTokenFileLinePos
_GetTokenFileLinePos:
    push    bp
    mov     bp, sp
; return
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "0 "
    mov     ax, 0
    jmp     L680
L680:
    leave
    ret
; SEGMENT _TEXT
; glb ShiftChar : (void) void
; glb GetNextChar : (void) int
SEGMENT _TEXT
    global  _GetNextChar
_GetNextChar:
    push    bp
    mov     bp, sp
; loc     ch : (@-2): int
    sub     sp, 2
; if
; RPN'ized expression: "CurFile 0 == "
; Expanded expression: "CurFile *(2) 0 == "
; Fused expression:    "== *CurFile 0 IF! "
    mov     ax, [_CurFile]
    cmp     ax, 0
    jne     L682
; {
; if
; RPN'ized expression: "CurFile ( L686 , CurFileName fopen ) = 0 == "
; Expanded expression: "CurFile  L686  CurFileName *(2)  fopen ()4 =(2) 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L686:
    db  "rt",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L686 , *(2) CurFileName , fopen )4 =(34) *CurFile ax == ax 0 IF! "
    push    L686
    push    word [_CurFileName]
    call    _fopen
    sub     sp, -4
    mov     [_CurFile], ax
    cmp     ax, 0
    jne     L684
; RPN'ized expression: "( CurFileName , L688 error ) "
; Expanded expression: " CurFileName *(2)  L688  error ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L688:
    db  "Cannot open file ",34,"%s",34,10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) CurFileName , L688 , error )4 "
    push    word [_CurFileName]
    push    L688
    call    _error
    sub     sp, -4
L684:
; }
L682:
; if
; RPN'ized expression: "ch ( CurFile fgetc ) = 1 -u == "
; Expanded expression: "(@-2)  CurFile *(2)  fgetc ()2 =(2) -1 == "
; Fused expression:    "( *(2) CurFile , fgetc )2 =(34) *(@-2) ax == ax -1 IF! "
    push    word [_CurFile]
    call    _fgetc
    sub     sp, -2
    mov     [bp-2], ax
    cmp     ax, -1
    jne     L690
; {
; RPN'ized expression: "( CurFile fclose ) "
; Expanded expression: " CurFile *(2)  fclose ()2 "
; Fused expression:    "( *(2) CurFile , fclose )2 "
    push    word [_CurFile]
    call    _fclose
    sub     sp, -2
; RPN'ized expression: "CurFile 0 = "
; Expanded expression: "CurFile 0 =(2) "
; Fused expression:    "=(34) *CurFile 0 "
    mov     ax, 0
    mov     [_CurFile], ax
; }
L690:
; return
; RPN'ized expression: "ch "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
    mov     ax, [bp-2]
    jmp     L681
L681:
    leave
    ret
; SEGMENT _TEXT
; glb ShiftChar : (void) void
SEGMENT _TEXT
    global  _ShiftChar
_ShiftChar:
    push    bp
    mov     bp, sp
; loc     eof : (@-2): int
    sub     sp, 2
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "=(34) *(@-2) 0 "
    mov     ax, 0
    mov     [bp-2], ax
; if
; RPN'ized expression: "CharQueueLen "
; Expanded expression: "CharQueueLen *(2) "
; Fused expression:    "*(2) CharQueueLen "
    mov     ax, [_CharQueueLen]
; JumpIfZero
    test    ax, ax
    jz      L693
; {
; RPN'ized expression: "( CharQueueLen -- , CharQueue 1 + , CharQueue memmove ) "
; Expanded expression: " CharQueueLen --(2)  CharQueue 1 +  CharQueue  memmove ()6 "
; Fused expression:    "( --(2) *CharQueueLen , + CharQueue 1 , CharQueue , memmove )6 "
    dec     word [_CharQueueLen]
    mov     ax, [_CharQueueLen]
    push    ax
    mov     ax, _CharQueue
    add     ax, 1
    push    ax
    push    _CharQueue
    call    _memmove
    sub     sp, -6
; RPN'ized expression: "eof CharQueue CharQueueLen + *u 0 == = "
; Expanded expression: "(@-2) CharQueue CharQueueLen *(2) + *(1) 0 == =(2) "
; Fused expression:    "+ CharQueue *CharQueueLen == *ax 0 =(34) *(@-2) ax "
    mov     ax, _CharQueue
    add     ax, [_CharQueueLen]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 0
    sete    al
    cbw
    mov     [bp-2], ax
; }
L693:
; while
; RPN'ized expression: "CharQueueLen 4 < "
; Expanded expression: "CharQueueLen *(2) 4 < "
L695:
; Fused expression:    "< *CharQueueLen 4 IF! "
    mov     ax, [_CharQueueLen]
    cmp     ax, 4
    jge     L696
; {
; if
; RPN'ized expression: "eof 0 == "
; Expanded expression: "(@-2) *(2) 0 == "
; Fused expression:    "== *(@-2) 0 IF! "
    mov     ax, [bp-2]
    cmp     ax, 0
    jne     L697
; {
; loc             ch : (@-4): int
    sub     sp, 2
; =
; RPN'ized expression: "( GetNextChar ) "
; Expanded expression: " GetNextChar ()0 "
; Fused expression:    "( GetNextChar )0 =(34) *(@-4) ax "
    call    _GetNextChar
    mov     [bp-4], ax
; RPN'ized expression: "CharQueue CharQueueLen + *u ch = "
; Expanded expression: "CharQueue CharQueueLen *(2) + (@-4) *(2) =(1) "
; Fused expression:    "+ CharQueue *CharQueueLen =(18) *ax *(@-4) "
    mov     ax, _CharQueue
    add     ax, [_CharQueueLen]
    mov     bx, ax
    mov     ax, [bp-4]
    mov     [bx], al
    cbw
; RPN'ized expression: "eof ch 1 -u == = "
; Expanded expression: "(@-2) (@-4) *(2) -1 == =(2) "
; Fused expression:    "== *(@-4) -1 =(34) *(@-2) ax "
    mov     ax, [bp-4]
    cmp     ax, -1
    sete    al
    cbw
    mov     [bp-2], ax
    sub     sp, -2
; }
L697:
; if
; RPN'ized expression: "eof "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
    mov     ax, [bp-2]
; JumpIfZero
    test    ax, ax
    jz      L699
; RPN'ized expression: "CharQueue CharQueueLen + *u 0 = "
; Expanded expression: "CharQueue CharQueueLen *(2) + 0 =(1) "
; Fused expression:    "+ CharQueue *CharQueueLen =(18) *ax 0 "
    mov     ax, _CharQueue
    add     ax, [_CharQueueLen]
    mov     bx, ax
    mov     ax, 0
    mov     [bx], al
    cbw
L699:
; RPN'ized expression: "CharQueueLen ++p "
; Expanded expression: "CharQueueLen ++p(2) "
; Fused expression:    "++p(2) *CharQueueLen "
    mov     ax, [_CharQueueLen]
    inc     word [_CharQueueLen]
; }
    jmp     L695
L696:
L692:
    leave
    ret
; SEGMENT _TEXT
; glb ShiftCharN : (
; prm     n : int
;     ) void
SEGMENT _TEXT
    global  _ShiftCharN
_ShiftCharN:
    push    bp
    mov     bp, sp
; loc     n : (@4): int
; while
; RPN'ized expression: "n --p 0 > "
; Expanded expression: "(@4) --p(2) 0 > "
L702:
; Fused expression:    "--p(2) *(@4) > ax 0 IF! "
    mov     ax, [bp+4]
    dec     word [bp+4]
    cmp     ax, 0
    jle     L703
; {
; RPN'ized expression: "( ShiftChar ) "
; Expanded expression: " ShiftChar ()0 "
; Fused expression:    "( ShiftChar )0 "
    call    _ShiftChar
; RPN'ized expression: "LinePos ++p "
; Expanded expression: "LinePos ++p(2) "
; Fused expression:    "++p(2) *LinePos "
    mov     ax, [_LinePos]
    inc     word [_LinePos]
; }
    jmp     L702
L703:
L701:
    leave
    ret
; SEGMENT _TEXT
; glb SkipSpace : (
; prm     SkipNewLines : int
;     ) void
SEGMENT _TEXT
    global  _SkipSpace
_SkipSpace:
    push    bp
    mov     bp, sp
; loc     SkipNewLines : (@4): int
; loc     p : (@-2): * char
    sub     sp, 2
; =
; RPN'ized expression: "CharQueue "
; Expanded expression: "CharQueue "
; Fused expression:    "=(34) *(@-2) CharQueue "
    mov     ax, _CharQueue
    mov     [bp-2], ax
; while
; RPN'ized expression: "p *u 0 != "
; Expanded expression: "(@-2) *(2) *(1) 0 != "
L705:
; Fused expression:    "*(2) (@-2) != *ax 0 IF! "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 0
    je      L706
; {
; if
; RPN'ized expression: "( p *u , L709 strchr ) 0 != "
; Expanded expression: " (@-2) *(2) *(1)  L709  strchr ()4 0 != "
; SEGMENT _TEXT
SEGMENT _DATA
L709:
    db  " ",9,12,11,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-2) *(1) ax , L709 , strchr )4 != ax 0 IF! "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    push    ax
    push    L709
    call    _strchr
    sub     sp, -4
    cmp     ax, 0
    je      L707
; {
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; continue
    jmp     L705
; }
L707:
; if
; RPN'ized expression: "( p *u , L713 strchr ) "
; Expanded expression: " (@-2) *(2) *(1)  L713  strchr ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L713:
    db  13,10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-2) *(1) ax , L713 , strchr )4 "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    push    ax
    push    L713
    call    _strchr
    sub     sp, -4
; JumpIfZero
    test    ax, ax
    jz      L711
; {
; if
; RPN'ized expression: "SkipNewLines 0 == "
; Expanded expression: "(@4) *(2) 0 == "
; Fused expression:    "== *(@4) 0 IF! "
    mov     ax, [bp+4]
    cmp     ax, 0
    jne     L715
; return
    jmp     L704
L715:
; if
; RPN'ized expression: "p *u 13 == p 1 + *u 10 == && "
; Expanded expression: "(@-2) *(2) *(1) 13 == _Bool [sh&&->719] (@-2) *(2) 1 + *(1) 10 == _Bool &&[719] "
; Fused expression:    "*(2) (@-2) == *ax 13 _Bool [sh&&->719] + *(@-2) 1 == *ax 10 _Bool &&[719] "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 13
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L719
    mov     ax, [bp-2]
    add     ax, 1
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 10
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L719:
; JumpIfZero
    test    ax, ax
    jz      L717
; RPN'ized expression: "( ShiftChar ) "
; Expanded expression: " ShiftChar ()0 "
; Fused expression:    "( ShiftChar )0 "
    call    _ShiftChar
L717:
; RPN'ized expression: "( ShiftChar ) "
; Expanded expression: " ShiftChar ()0 "
; Fused expression:    "( ShiftChar )0 "
    call    _ShiftChar
; RPN'ized expression: "LineNo ++p "
; Expanded expression: "LineNo ++p(2) "
; Fused expression:    "++p(2) *LineNo "
    mov     ax, [_LineNo]
    inc     word [_LineNo]
; RPN'ized expression: "LinePos 1 = "
; Expanded expression: "LinePos 1 =(2) "
; Fused expression:    "=(34) *LinePos 1 "
    mov     ax, 1
    mov     [_LinePos], ax
; continue
    jmp     L705
; }
L711:
; if
; RPN'ized expression: "p *u 47 == "
; Expanded expression: "(@-2) *(2) *(1) 47 == "
; Fused expression:    "*(2) (@-2) == *ax 47 IF! "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 47
    jne     L720
; {
; if
; RPN'ized expression: "p 1 + *u 47 == "
; Expanded expression: "(@-2) *(2) 1 + *(1) 47 == "
; Fused expression:    "+ *(@-2) 1 == *ax 47 IF! "
    mov     ax, [bp-2]
    add     ax, 1
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 47
    jne     L722
; {
; RPN'ized expression: "( 2 ShiftCharN ) "
; Expanded expression: " 2  ShiftCharN ()2 "
; Fused expression:    "( 2 , ShiftCharN )2 "
    push    2
    call    _ShiftCharN
    sub     sp, -2
; while
; RPN'ized expression: "( p *u , L726 strchr ) 0 == "
; Expanded expression: " (@-2) *(2) *(1)  L726  strchr ()4 0 == "
L724:
; SEGMENT _TEXT
SEGMENT _DATA
L726:
    db  13,10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-2) *(1) ax , L726 , strchr )4 == ax 0 IF! "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    push    ax
    push    L726
    call    _strchr
    sub     sp, -4
    cmp     ax, 0
    jne     L725
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
    jmp     L724
L725:
; continue
    jmp     L705
; }
    jmp     L723
L722:
; else
; if
; RPN'ized expression: "p 1 + *u 42 == "
; Expanded expression: "(@-2) *(2) 1 + *(1) 42 == "
; Fused expression:    "+ *(@-2) 1 == *ax 42 IF! "
    mov     ax, [bp-2]
    add     ax, 1
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 42
    jne     L728
; {
; RPN'ized expression: "( 2 ShiftCharN ) "
; Expanded expression: " 2  ShiftCharN ()2 "
; Fused expression:    "( 2 , ShiftCharN )2 "
    push    2
    call    _ShiftCharN
    sub     sp, -2
; while
; RPN'ized expression: "p *u 0 != p *u 42 == p 1 + *u 47 == && 0 == && "
; Expanded expression: "(@-2) *(2) *(1) 0 != _Bool [sh&&->732] (@-2) *(2) *(1) 42 == _Bool [sh&&->733] (@-2) *(2) 1 + *(1) 47 == _Bool &&[733] 0 == _Bool &&[732] "
L730:
; Fused expression:    "*(2) (@-2) != *ax 0 _Bool [sh&&->732] *(2) (@-2) == *ax 42 _Bool [sh&&->733] + *(@-2) 1 == *ax 47 _Bool &&[733] == ax 0 _Bool &&[732] "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 0
    setne   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L732
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 42
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L733
    mov     ax, [bp-2]
    add     ax, 1
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 47
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L733:
    cmp     ax, 0
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L732:
; JumpIfZero
    test    ax, ax
    jz      L731
; {
; if
; RPN'ized expression: "( p *u , L736 strchr ) "
; Expanded expression: " (@-2) *(2) *(1)  L736  strchr ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L736:
    db  13,10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-2) *(1) ax , L736 , strchr )4 "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    push    ax
    push    L736
    call    _strchr
    sub     sp, -4
; JumpIfZero
    test    ax, ax
    jz      L734
; {
; if
; RPN'ized expression: "SkipNewLines 0 == "
; Expanded expression: "(@4) *(2) 0 == "
; Fused expression:    "== *(@4) 0 IF! "
    mov     ax, [bp+4]
    cmp     ax, 0
    jne     L738
; RPN'ized expression: "( L740 error ) "
; Expanded expression: " L740  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L740:
    db  "Error: Invalid comment",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L740 , error )2 "
    push    L740
    call    _error
    sub     sp, -2
L738:
; if
; RPN'ized expression: "p *u 13 == p 1 + *u 10 == && "
; Expanded expression: "(@-2) *(2) *(1) 13 == _Bool [sh&&->744] (@-2) *(2) 1 + *(1) 10 == _Bool &&[744] "
; Fused expression:    "*(2) (@-2) == *ax 13 _Bool [sh&&->744] + *(@-2) 1 == *ax 10 _Bool &&[744] "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 13
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L744
    mov     ax, [bp-2]
    add     ax, 1
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 10
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L744:
; JumpIfZero
    test    ax, ax
    jz      L742
; RPN'ized expression: "( ShiftChar ) "
; Expanded expression: " ShiftChar ()0 "
; Fused expression:    "( ShiftChar )0 "
    call    _ShiftChar
L742:
; RPN'ized expression: "( ShiftChar ) "
; Expanded expression: " ShiftChar ()0 "
; Fused expression:    "( ShiftChar )0 "
    call    _ShiftChar
; RPN'ized expression: "LineNo ++p "
; Expanded expression: "LineNo ++p(2) "
; Fused expression:    "++p(2) *LineNo "
    mov     ax, [_LineNo]
    inc     word [_LineNo]
; RPN'ized expression: "LinePos 1 = "
; Expanded expression: "LinePos 1 =(2) "
; Fused expression:    "=(34) *LinePos 1 "
    mov     ax, 1
    mov     [_LinePos], ax
; }
    jmp     L735
L734:
; else
; {
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; }
L735:
; }
    jmp     L730
L731:
; if
; RPN'ized expression: "p *u 0 == "
; Expanded expression: "(@-2) *(2) *(1) 0 == "
; Fused expression:    "*(2) (@-2) == *ax 0 IF! "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 0
    jne     L745
; RPN'ized expression: "( L747 error ) "
; Expanded expression: " L747  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L747:
    db  "Error: Invalid comment",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L747 , error )2 "
    push    L747
    call    _error
    sub     sp, -2
L745:
; RPN'ized expression: "( 2 ShiftCharN ) "
; Expanded expression: " 2  ShiftCharN ()2 "
; Fused expression:    "( 2 , ShiftCharN )2 "
    push    2
    call    _ShiftCharN
    sub     sp, -2
; continue
    jmp     L705
; }
L728:
L723:
; }
L720:
; break
    jmp     L706
; }
    jmp     L705
L706:
L704:
    leave
    ret
; SEGMENT _TEXT
; glb GetIdent : (void) void
SEGMENT _TEXT
    global  _GetIdent
_GetIdent:
    push    bp
    mov     bp, sp
; loc     p : (@-2): * char
    sub     sp, 2
; =
; RPN'ized expression: "CharQueue "
; Expanded expression: "CharQueue "
; Fused expression:    "=(34) *(@-2) CharQueue "
    mov     ax, _CharQueue
    mov     [bp-2], ax
; if
; RPN'ized expression: "p *u 95 != ( p *u isalpha ) 0 == && "
; Expanded expression: "(@-2) *(2) *(1) 95 != _Bool [sh&&->752]  (@-2) *(2) *(1)  isalpha ()2 0 == _Bool &&[752] "
; Fused expression:    "*(2) (@-2) != *ax 95 _Bool [sh&&->752] ( *(2) (@-2) *(1) ax , isalpha )2 == ax 0 _Bool &&[752] "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 95
    setne   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L752
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    push    ax
    call    _isalpha
    sub     sp, -2
    cmp     ax, 0
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L752:
; JumpIfZero
    test    ax, ax
    jz      L750
; RPN'ized expression: "( L753 error ) "
; Expanded expression: " L753  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L753:
    db  "Error: Identifier expected",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L753 , error )2 "
    push    L753
    call    _error
    sub     sp, -2
L750:
; if
; RPN'ized expression: "p *u 76 == p *u 108 == || p 1 + *u 39 == p 1 + *u 34 == || && "
; Expanded expression: "(@-2) *(2) *(1) 76 == _Bool [sh||->759] (@-2) *(2) *(1) 108 == _Bool ||[759] _Bool [sh&&->757] (@-2) *(2) 1 + *(1) 39 == _Bool [sh||->758] (@-2) *(2) 1 + *(1) 34 == _Bool ||[758] _Bool &&[757] "
; Fused expression:    "*(2) (@-2) == *ax 76 _Bool [sh||->759] *(2) (@-2) == *ax 108 _Bool ||[759] _Bool [sh&&->757] + *(@-2) 1 == *ax 39 _Bool [sh||->758] + *(@-2) 1 == *ax 34 _Bool ||[758] _Bool &&[757] "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 76
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L759
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 108
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L759:
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L757
    mov     ax, [bp-2]
    add     ax, 1
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 39
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L758
    mov     ax, [bp-2]
    add     ax, 1
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 34
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L758:
    test    ax, ax
    setnz   al
    cbw
L757:
; JumpIfZero
    test    ax, ax
    jz      L755
; RPN'ized expression: "( L760 error ) "
; Expanded expression: " L760  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L760:
    db  "Error: Wide characters and strings not supported",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L760 , error )2 "
    push    L760
    call    _error
    sub     sp, -2
L755:
; RPN'ized expression: "TokenIdentNameLen 0 = "
; Expanded expression: "TokenIdentNameLen 0 =(2) "
; Fused expression:    "=(34) *TokenIdentNameLen 0 "
    mov     ax, 0
    mov     [_TokenIdentNameLen], ax
; RPN'ized expression: "TokenIdentName TokenIdentNameLen ++p + *u p *u = "
; Expanded expression: "TokenIdentName TokenIdentNameLen ++p(2) + (@-2) *(2) *(1) =(1) "
; Fused expression:    "++p(2) *TokenIdentNameLen + TokenIdentName ax push-ax *(2) (@-2) =(17) **sp *ax "
    mov     ax, [_TokenIdentNameLen]
    inc     word [_TokenIdentNameLen]
    mov     cx, ax
    mov     ax, _TokenIdentName
    add     ax, cx
    push    ax
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    pop     bx
    mov     [bx], al
    cbw
; RPN'ized expression: "TokenIdentName TokenIdentNameLen + *u 0 = "
; Expanded expression: "TokenIdentName TokenIdentNameLen *(2) + 0 =(1) "
; Fused expression:    "+ TokenIdentName *TokenIdentNameLen =(18) *ax 0 "
    mov     ax, _TokenIdentName
    add     ax, [_TokenIdentNameLen]
    mov     bx, ax
    mov     ax, 0
    mov     [bx], al
    cbw
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; while
; RPN'ized expression: "p *u 95 == ( p *u isalnum ) || "
; Expanded expression: "(@-2) *(2) *(1) 95 == _Bool [sh||->764]  (@-2) *(2) *(1)  isalnum ()2 _Bool ||[764] "
L762:
; Fused expression:    "*(2) (@-2) == *ax 95 _Bool [sh||->764] ( *(2) (@-2) *(1) ax , isalnum )2 _Bool ||[764] "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 95
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L764
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    push    ax
    call    _isalnum
    sub     sp, -2
    test    ax, ax
    setnz   al
    cbw
L764:
; JumpIfZero
    test    ax, ax
    jz      L763
; {
; if
; RPN'ized expression: "TokenIdentNameLen 31 == "
; Expanded expression: "TokenIdentNameLen *(2) 31 == "
; Fused expression:    "== *TokenIdentNameLen 31 IF! "
    mov     ax, [_TokenIdentNameLen]
    cmp     ax, 31
    jne     L765
; RPN'ized expression: "( TokenIdentName , L767 error ) "
; Expanded expression: " TokenIdentName  L767  error ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L767:
    db  "Error: Identifier name too long '%s'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( TokenIdentName , L767 , error )4 "
    push    _TokenIdentName
    push    L767
    call    _error
    sub     sp, -4
L765:
; RPN'ized expression: "TokenIdentName TokenIdentNameLen ++p + *u p *u = "
; Expanded expression: "TokenIdentName TokenIdentNameLen ++p(2) + (@-2) *(2) *(1) =(1) "
; Fused expression:    "++p(2) *TokenIdentNameLen + TokenIdentName ax push-ax *(2) (@-2) =(17) **sp *ax "
    mov     ax, [_TokenIdentNameLen]
    inc     word [_TokenIdentNameLen]
    mov     cx, ax
    mov     ax, _TokenIdentName
    add     ax, cx
    push    ax
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    pop     bx
    mov     [bx], al
    cbw
; RPN'ized expression: "TokenIdentName TokenIdentNameLen + *u 0 = "
; Expanded expression: "TokenIdentName TokenIdentNameLen *(2) + 0 =(1) "
; Fused expression:    "+ TokenIdentName *TokenIdentNameLen =(18) *ax 0 "
    mov     ax, _TokenIdentName
    add     ax, [_TokenIdentNameLen]
    mov     bx, ax
    mov     ax, 0
    mov     [bx], al
    cbw
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; }
    jmp     L762
L763:
L749:
    leave
    ret
; SEGMENT _TEXT
; glb GetToken : (void) int
SEGMENT _TEXT
    global  _GetToken
_GetToken:
    push    bp
    mov     bp, sp
; loc     p : (@-2): * char
    sub     sp, 2
; =
; RPN'ized expression: "CharQueue "
; Expanded expression: "CharQueue "
; Fused expression:    "=(34) *(@-2) CharQueue "
    mov     ax, _CharQueue
    mov     [bp-2], ax
; loc     ch : (@-4): int
    sub     sp, 2
; while
; RPN'ized expression: "ch p *u = 0 != "
; Expanded expression: "(@-4) (@-2) *(2) *(1) =(2) 0 != "
L770:
; Fused expression:    "*(2) (@-2) =(33) *(@-4) *ax != ax 0 IF! "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    mov     [bp-4], ax
    cmp     ax, 0
    je      L771
; {
; RPN'ized expression: "( 1 SkipSpace ) "
; Expanded expression: " 1  SkipSpace ()2 "
; Fused expression:    "( 1 , SkipSpace )2 "
    push    1
    call    _SkipSpace
    sub     sp, -2
; if
; RPN'ized expression: "ch p *u = 0 == "
; Expanded expression: "(@-4) (@-2) *(2) *(1) =(2) 0 == "
; Fused expression:    "*(2) (@-2) =(33) *(@-4) *ax == ax 0 IF! "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    mov     [bp-4], ax
    cmp     ax, 0
    jne     L772
; break
    jmp     L771
L772:
; if
; RPN'ized expression: "( ch , L776 strchr ) 0 != "
; Expanded expression: " (@-4) *(2)  L776  strchr ()4 0 != "
; SEGMENT _TEXT
SEGMENT _DATA
L776:
    db  ",;:()[]{}~",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-4) , L776 , strchr )4 != ax 0 IF! "
    push    word [bp-4]
    push    L776
    call    _strchr
    sub     sp, -4
    cmp     ax, 0
    je      L774
; {
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; return
; RPN'ized expression: "ch "
; Expanded expression: "(@-4) *(2) "
; Fused expression:    "*(2) (@-4) "
    mov     ax, [bp-4]
    jmp     L769
; }
L774:
; switch
; RPN'ized expression: "ch "
; Expanded expression: "(@-4) *(2) "
; Fused expression:    "*(2) (@-4) "
    mov     ax, [bp-4]
    jmp     L780
; {
; case
; RPN'ized expression: "43 "
; Expanded expression: "43 "
; Expression value: 43
    jmp     L781
L780:
    cmp     ax, 43
    jne     L782
L781:
; if
; RPN'ized expression: "p 1 + *u 43 == "
; Expanded expression: "(@-2) *(2) 1 + *(1) 43 == "
; Fused expression:    "+ *(@-2) 1 == *ax 43 IF! "
    mov     ax, [bp-2]
    add     ax, 1
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 43
    jne     L784
; {
; RPN'ized expression: "( 2 ShiftCharN ) "
; Expanded expression: " 2  ShiftCharN ()2 "
; Fused expression:    "( 2 , ShiftCharN )2 "
    push    2
    call    _ShiftCharN
    sub     sp, -2
; return
; RPN'ized expression: "12 "
; Expanded expression: "12 "
; Expression value: 12
; Fused expression:    "12 "
    mov     ax, 12
    jmp     L769
; }
L784:
; if
; RPN'ized expression: "p 1 + *u 61 == "
; Expanded expression: "(@-2) *(2) 1 + *(1) 61 == "
; Fused expression:    "+ *(@-2) 1 == *ax 61 IF! "
    mov     ax, [bp-2]
    add     ax, 1
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 61
    jne     L786
; {
; RPN'ized expression: "( 2 ShiftCharN ) "
; Expanded expression: " 2  ShiftCharN ()2 "
; Fused expression:    "( 2 , ShiftCharN )2 "
    push    2
    call    _ShiftCharN
    sub     sp, -2
; return
; RPN'ized expression: "68 "
; Expanded expression: "68 "
; Expression value: 68
; Fused expression:    "68 "
    mov     ax, 68
    jmp     L769
; }
L786:
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; return
; RPN'ized expression: "ch "
; Expanded expression: "(@-4) *(2) "
; Fused expression:    "*(2) (@-4) "
    mov     ax, [bp-4]
    jmp     L769
; case
; RPN'ized expression: "45 "
; Expanded expression: "45 "
; Expression value: 45
    jmp     L783
L782:
    cmp     ax, 45
    jne     L788
L783:
; if
; RPN'ized expression: "p 1 + *u 45 == "
; Expanded expression: "(@-2) *(2) 1 + *(1) 45 == "
; Fused expression:    "+ *(@-2) 1 == *ax 45 IF! "
    mov     ax, [bp-2]
    add     ax, 1
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 45
    jne     L790
; {
; RPN'ized expression: "( 2 ShiftCharN ) "
; Expanded expression: " 2  ShiftCharN ()2 "
; Fused expression:    "( 2 , ShiftCharN )2 "
    push    2
    call    _ShiftCharN
    sub     sp, -2
; return
; RPN'ized expression: "13 "
; Expanded expression: "13 "
; Expression value: 13
; Fused expression:    "13 "
    mov     ax, 13
    jmp     L769
; }
L790:
; if
; RPN'ized expression: "p 1 + *u 61 == "
; Expanded expression: "(@-2) *(2) 1 + *(1) 61 == "
; Fused expression:    "+ *(@-2) 1 == *ax 61 IF! "
    mov     ax, [bp-2]
    add     ax, 1
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 61
    jne     L792
; {
; RPN'ized expression: "( 2 ShiftCharN ) "
; Expanded expression: " 2  ShiftCharN ()2 "
; Fused expression:    "( 2 , ShiftCharN )2 "
    push    2
    call    _ShiftCharN
    sub     sp, -2
; return
; RPN'ized expression: "69 "
; Expanded expression: "69 "
; Expression value: 69
; Fused expression:    "69 "
    mov     ax, 69
    jmp     L769
; }
L792:
; if
; RPN'ized expression: "p 1 + *u 62 == "
; Expanded expression: "(@-2) *(2) 1 + *(1) 62 == "
; Fused expression:    "+ *(@-2) 1 == *ax 62 IF! "
    mov     ax, [bp-2]
    add     ax, 1
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 62
    jne     L794
; {
; RPN'ized expression: "( 2 ShiftCharN ) "
; Expanded expression: " 2  ShiftCharN ()2 "
; Fused expression:    "( 2 , ShiftCharN )2 "
    push    2
    call    _ShiftCharN
    sub     sp, -2
; return
; RPN'ized expression: "14 "
; Expanded expression: "14 "
; Expression value: 14
; Fused expression:    "14 "
    mov     ax, 14
    jmp     L769
; }
L794:
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; return
; RPN'ized expression: "ch "
; Expanded expression: "(@-4) *(2) "
; Fused expression:    "*(2) (@-4) "
    mov     ax, [bp-4]
    jmp     L769
; case
; RPN'ized expression: "33 "
; Expanded expression: "33 "
; Expression value: 33
    jmp     L789
L788:
    cmp     ax, 33
    jne     L796
L789:
; if
; RPN'ized expression: "p 1 + *u 61 == "
; Expanded expression: "(@-2) *(2) 1 + *(1) 61 == "
; Fused expression:    "+ *(@-2) 1 == *ax 61 IF! "
    mov     ax, [bp-2]
    add     ax, 1
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 61
    jne     L798
; {
; RPN'ized expression: "( 2 ShiftCharN ) "
; Expanded expression: " 2  ShiftCharN ()2 "
; Fused expression:    "( 2 , ShiftCharN )2 "
    push    2
    call    _ShiftCharN
    sub     sp, -2
; return
; RPN'ized expression: "9 "
; Expanded expression: "9 "
; Expression value: 9
; Fused expression:    "9 "
    mov     ax, 9
    jmp     L769
; }
L798:
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; return
; RPN'ized expression: "ch "
; Expanded expression: "(@-4) *(2) "
; Fused expression:    "*(2) (@-4) "
    mov     ax, [bp-4]
    jmp     L769
; case
; RPN'ized expression: "61 "
; Expanded expression: "61 "
; Expression value: 61
    jmp     L797
L796:
    cmp     ax, 61
    jne     L800
L797:
; if
; RPN'ized expression: "p 1 + *u 61 == "
; Expanded expression: "(@-2) *(2) 1 + *(1) 61 == "
; Fused expression:    "+ *(@-2) 1 == *ax 61 IF! "
    mov     ax, [bp-2]
    add     ax, 1
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 61
    jne     L802
; {
; RPN'ized expression: "( 2 ShiftCharN ) "
; Expanded expression: " 2  ShiftCharN ()2 "
; Fused expression:    "( 2 , ShiftCharN )2 "
    push    2
    call    _ShiftCharN
    sub     sp, -2
; return
; RPN'ized expression: "8 "
; Expanded expression: "8 "
; Expression value: 8
; Fused expression:    "8 "
    mov     ax, 8
    jmp     L769
; }
L802:
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; return
; RPN'ized expression: "ch "
; Expanded expression: "(@-4) *(2) "
; Fused expression:    "*(2) (@-4) "
    mov     ax, [bp-4]
    jmp     L769
; case
; RPN'ized expression: "60 "
; Expanded expression: "60 "
; Expression value: 60
    jmp     L801
L800:
    cmp     ax, 60
    jne     L804
L801:
; if
; RPN'ized expression: "p 1 + *u 61 == "
; Expanded expression: "(@-2) *(2) 1 + *(1) 61 == "
; Fused expression:    "+ *(@-2) 1 == *ax 61 IF! "
    mov     ax, [bp-2]
    add     ax, 1
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 61
    jne     L806
; {
; RPN'ized expression: "( 2 ShiftCharN ) "
; Expanded expression: " 2  ShiftCharN ()2 "
; Fused expression:    "( 2 , ShiftCharN )2 "
    push    2
    call    _ShiftCharN
    sub     sp, -2
; return
; RPN'ized expression: "10 "
; Expanded expression: "10 "
; Expression value: 10
; Fused expression:    "10 "
    mov     ax, 10
    jmp     L769
; }
L806:
; if
; RPN'ized expression: "p 1 + *u 60 == "
; Expanded expression: "(@-2) *(2) 1 + *(1) 60 == "
; Fused expression:    "+ *(@-2) 1 == *ax 60 IF! "
    mov     ax, [bp-2]
    add     ax, 1
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 60
    jne     L808
; {
; RPN'ized expression: "( 2 ShiftCharN ) "
; Expanded expression: " 2  ShiftCharN ()2 "
; Fused expression:    "( 2 , ShiftCharN )2 "
    push    2
    call    _ShiftCharN
    sub     sp, -2
; if
; RPN'ized expression: "p 0 + *u 61 != "
; Expanded expression: "(@-2) *(2) 0 + *(1) 61 != "
; Fused expression:    "+ *(@-2) 0 != *ax 61 IF! "
    mov     ax, [bp-2]
    add     ax, 0
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 61
    je      L810
; return
; RPN'ized expression: "4 "
; Expanded expression: "4 "
; Expression value: 4
; Fused expression:    "4 "
    mov     ax, 4
    jmp     L769
L810:
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; return
; RPN'ized expression: "70 "
; Expanded expression: "70 "
; Expression value: 70
; Fused expression:    "70 "
    mov     ax, 70
    jmp     L769
; }
L808:
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; return
; RPN'ized expression: "ch "
; Expanded expression: "(@-4) *(2) "
; Fused expression:    "*(2) (@-4) "
    mov     ax, [bp-4]
    jmp     L769
; case
; RPN'ized expression: "62 "
; Expanded expression: "62 "
; Expression value: 62
    jmp     L805
L804:
    cmp     ax, 62
    jne     L812
L805:
; if
; RPN'ized expression: "p 1 + *u 61 == "
; Expanded expression: "(@-2) *(2) 1 + *(1) 61 == "
; Fused expression:    "+ *(@-2) 1 == *ax 61 IF! "
    mov     ax, [bp-2]
    add     ax, 1
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 61
    jne     L814
; {
; RPN'ized expression: "( 2 ShiftCharN ) "
; Expanded expression: " 2  ShiftCharN ()2 "
; Fused expression:    "( 2 , ShiftCharN )2 "
    push    2
    call    _ShiftCharN
    sub     sp, -2
; return
; RPN'ized expression: "11 "
; Expanded expression: "11 "
; Expression value: 11
; Fused expression:    "11 "
    mov     ax, 11
    jmp     L769
; }
L814:
; if
; RPN'ized expression: "p 1 + *u 62 == "
; Expanded expression: "(@-2) *(2) 1 + *(1) 62 == "
; Fused expression:    "+ *(@-2) 1 == *ax 62 IF! "
    mov     ax, [bp-2]
    add     ax, 1
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 62
    jne     L816
; {
; RPN'ized expression: "( 2 ShiftCharN ) "
; Expanded expression: " 2  ShiftCharN ()2 "
; Fused expression:    "( 2 , ShiftCharN )2 "
    push    2
    call    _ShiftCharN
    sub     sp, -2
; if
; RPN'ized expression: "p 0 + *u 61 != "
; Expanded expression: "(@-2) *(2) 0 + *(1) 61 != "
; Fused expression:    "+ *(@-2) 0 != *ax 61 IF! "
    mov     ax, [bp-2]
    add     ax, 0
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 61
    je      L818
; return
; RPN'ized expression: "5 "
; Expanded expression: "5 "
; Expression value: 5
; Fused expression:    "5 "
    mov     ax, 5
    jmp     L769
L818:
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; return
; RPN'ized expression: "71 "
; Expanded expression: "71 "
; Expression value: 71
; Fused expression:    "71 "
    mov     ax, 71
    jmp     L769
; }
L816:
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; return
; RPN'ized expression: "ch "
; Expanded expression: "(@-4) *(2) "
; Fused expression:    "*(2) (@-4) "
    mov     ax, [bp-4]
    jmp     L769
; case
; RPN'ized expression: "38 "
; Expanded expression: "38 "
; Expression value: 38
    jmp     L813
L812:
    cmp     ax, 38
    jne     L820
L813:
; if
; RPN'ized expression: "p 1 + *u 38 == "
; Expanded expression: "(@-2) *(2) 1 + *(1) 38 == "
; Fused expression:    "+ *(@-2) 1 == *ax 38 IF! "
    mov     ax, [bp-2]
    add     ax, 1
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 38
    jne     L822
; {
; RPN'ized expression: "( 2 ShiftCharN ) "
; Expanded expression: " 2  ShiftCharN ()2 "
; Fused expression:    "( 2 , ShiftCharN )2 "
    push    2
    call    _ShiftCharN
    sub     sp, -2
; return
; RPN'ized expression: "6 "
; Expanded expression: "6 "
; Expression value: 6
; Fused expression:    "6 "
    mov     ax, 6
    jmp     L769
; }
L822:
; if
; RPN'ized expression: "p 1 + *u 61 == "
; Expanded expression: "(@-2) *(2) 1 + *(1) 61 == "
; Fused expression:    "+ *(@-2) 1 == *ax 61 IF! "
    mov     ax, [bp-2]
    add     ax, 1
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 61
    jne     L824
; {
; RPN'ized expression: "( 2 ShiftCharN ) "
; Expanded expression: " 2  ShiftCharN ()2 "
; Fused expression:    "( 2 , ShiftCharN )2 "
    push    2
    call    _ShiftCharN
    sub     sp, -2
; return
; RPN'ized expression: "72 "
; Expanded expression: "72 "
; Expression value: 72
; Fused expression:    "72 "
    mov     ax, 72
    jmp     L769
; }
L824:
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; return
; RPN'ized expression: "ch "
; Expanded expression: "(@-4) *(2) "
; Fused expression:    "*(2) (@-4) "
    mov     ax, [bp-4]
    jmp     L769
; case
; RPN'ized expression: "124 "
; Expanded expression: "124 "
; Expression value: 124
    jmp     L821
L820:
    cmp     ax, 124
    jne     L826
L821:
; if
; RPN'ized expression: "p 1 + *u 124 == "
; Expanded expression: "(@-2) *(2) 1 + *(1) 124 == "
; Fused expression:    "+ *(@-2) 1 == *ax 124 IF! "
    mov     ax, [bp-2]
    add     ax, 1
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 124
    jne     L828
; {
; RPN'ized expression: "( 2 ShiftCharN ) "
; Expanded expression: " 2  ShiftCharN ()2 "
; Fused expression:    "( 2 , ShiftCharN )2 "
    push    2
    call    _ShiftCharN
    sub     sp, -2
; return
; RPN'ized expression: "7 "
; Expanded expression: "7 "
; Expression value: 7
; Fused expression:    "7 "
    mov     ax, 7
    jmp     L769
; }
L828:
; if
; RPN'ized expression: "p 1 + *u 61 == "
; Expanded expression: "(@-2) *(2) 1 + *(1) 61 == "
; Fused expression:    "+ *(@-2) 1 == *ax 61 IF! "
    mov     ax, [bp-2]
    add     ax, 1
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 61
    jne     L830
; {
; RPN'ized expression: "( 2 ShiftCharN ) "
; Expanded expression: " 2  ShiftCharN ()2 "
; Fused expression:    "( 2 , ShiftCharN )2 "
    push    2
    call    _ShiftCharN
    sub     sp, -2
; return
; RPN'ized expression: "74 "
; Expanded expression: "74 "
; Expression value: 74
; Fused expression:    "74 "
    mov     ax, 74
    jmp     L769
; }
L830:
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; return
; RPN'ized expression: "ch "
; Expanded expression: "(@-4) *(2) "
; Fused expression:    "*(2) (@-4) "
    mov     ax, [bp-4]
    jmp     L769
; case
; RPN'ized expression: "94 "
; Expanded expression: "94 "
; Expression value: 94
    jmp     L827
L826:
    cmp     ax, 94
    jne     L832
L827:
; if
; RPN'ized expression: "p 1 + *u 61 == "
; Expanded expression: "(@-2) *(2) 1 + *(1) 61 == "
; Fused expression:    "+ *(@-2) 1 == *ax 61 IF! "
    mov     ax, [bp-2]
    add     ax, 1
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 61
    jne     L834
; {
; RPN'ized expression: "( 2 ShiftCharN ) "
; Expanded expression: " 2  ShiftCharN ()2 "
; Fused expression:    "( 2 , ShiftCharN )2 "
    push    2
    call    _ShiftCharN
    sub     sp, -2
; return
; RPN'ized expression: "73 "
; Expanded expression: "73 "
; Expression value: 73
; Fused expression:    "73 "
    mov     ax, 73
    jmp     L769
; }
L834:
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; return
; RPN'ized expression: "ch "
; Expanded expression: "(@-4) *(2) "
; Fused expression:    "*(2) (@-4) "
    mov     ax, [bp-4]
    jmp     L769
; case
; RPN'ized expression: "46 "
; Expanded expression: "46 "
; Expression value: 46
    jmp     L833
L832:
    cmp     ax, 46
    jne     L836
L833:
; if
; RPN'ized expression: "p 1 + *u 46 == p 2 + *u 46 == && "
; Expanded expression: "(@-2) *(2) 1 + *(1) 46 == _Bool [sh&&->840] (@-2) *(2) 2 + *(1) 46 == _Bool &&[840] "
; Fused expression:    "+ *(@-2) 1 == *ax 46 _Bool [sh&&->840] + *(@-2) 2 == *ax 46 _Bool &&[840] "
    mov     ax, [bp-2]
    add     ax, 1
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 46
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L840
    mov     ax, [bp-2]
    add     ax, 2
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 46
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L840:
; JumpIfZero
    test    ax, ax
    jz      L838
; {
; RPN'ized expression: "( 3 ShiftCharN ) "
; Expanded expression: " 3  ShiftCharN ()2 "
; Fused expression:    "( 3 , ShiftCharN )2 "
    push    3
    call    _ShiftCharN
    sub     sp, -2
; return
; RPN'ized expression: "15 "
; Expanded expression: "15 "
; Expression value: 15
; Fused expression:    "15 "
    mov     ax, 15
    jmp     L769
; }
L838:
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; return
; RPN'ized expression: "ch "
; Expanded expression: "(@-4) *(2) "
; Fused expression:    "*(2) (@-4) "
    mov     ax, [bp-4]
    jmp     L769
; case
; RPN'ized expression: "42 "
; Expanded expression: "42 "
; Expression value: 42
    jmp     L837
L836:
    cmp     ax, 42
    jne     L841
L837:
; if
; RPN'ized expression: "p 1 + *u 61 == "
; Expanded expression: "(@-2) *(2) 1 + *(1) 61 == "
; Fused expression:    "+ *(@-2) 1 == *ax 61 IF! "
    mov     ax, [bp-2]
    add     ax, 1
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 61
    jne     L843
; {
; RPN'ized expression: "( 2 ShiftCharN ) "
; Expanded expression: " 2  ShiftCharN ()2 "
; Fused expression:    "( 2 , ShiftCharN )2 "
    push    2
    call    _ShiftCharN
    sub     sp, -2
; return
; RPN'ized expression: "65 "
; Expanded expression: "65 "
; Expression value: 65
; Fused expression:    "65 "
    mov     ax, 65
    jmp     L769
; }
L843:
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; return
; RPN'ized expression: "ch "
; Expanded expression: "(@-4) *(2) "
; Fused expression:    "*(2) (@-4) "
    mov     ax, [bp-4]
    jmp     L769
; case
; RPN'ized expression: "37 "
; Expanded expression: "37 "
; Expression value: 37
    jmp     L842
L841:
    cmp     ax, 37
    jne     L845
L842:
; if
; RPN'ized expression: "p 1 + *u 61 == "
; Expanded expression: "(@-2) *(2) 1 + *(1) 61 == "
; Fused expression:    "+ *(@-2) 1 == *ax 61 IF! "
    mov     ax, [bp-2]
    add     ax, 1
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 61
    jne     L847
; {
; RPN'ized expression: "( 2 ShiftCharN ) "
; Expanded expression: " 2  ShiftCharN ()2 "
; Fused expression:    "( 2 , ShiftCharN )2 "
    push    2
    call    _ShiftCharN
    sub     sp, -2
; return
; RPN'ized expression: "67 "
; Expanded expression: "67 "
; Expression value: 67
; Fused expression:    "67 "
    mov     ax, 67
    jmp     L769
; }
L847:
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; return
; RPN'ized expression: "ch "
; Expanded expression: "(@-4) *(2) "
; Fused expression:    "*(2) (@-4) "
    mov     ax, [bp-4]
    jmp     L769
; case
; RPN'ized expression: "47 "
; Expanded expression: "47 "
; Expression value: 47
    jmp     L846
L845:
    cmp     ax, 47
    jne     L849
L846:
; if
; RPN'ized expression: "p 1 + *u 61 == "
; Expanded expression: "(@-2) *(2) 1 + *(1) 61 == "
; Fused expression:    "+ *(@-2) 1 == *ax 61 IF! "
    mov     ax, [bp-2]
    add     ax, 1
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 61
    jne     L851
; {
; RPN'ized expression: "( 2 ShiftCharN ) "
; Expanded expression: " 2  ShiftCharN ()2 "
; Fused expression:    "( 2 , ShiftCharN )2 "
    push    2
    call    _ShiftCharN
    sub     sp, -2
; return
; RPN'ized expression: "66 "
; Expanded expression: "66 "
; Expression value: 66
; Fused expression:    "66 "
    mov     ax, 66
    jmp     L769
; }
L851:
; if
; RPN'ized expression: "p 1 + *u 47 == p 1 + *u 42 == || "
; Expanded expression: "(@-2) *(2) 1 + *(1) 47 == _Bool [sh||->855] (@-2) *(2) 1 + *(1) 42 == _Bool ||[855] "
; Fused expression:    "+ *(@-2) 1 == *ax 47 _Bool [sh||->855] + *(@-2) 1 == *ax 42 _Bool ||[855] "
    mov     ax, [bp-2]
    add     ax, 1
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 47
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L855
    mov     ax, [bp-2]
    add     ax, 1
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 42
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L855:
; JumpIfZero
    test    ax, ax
    jz      L853
; {
; RPN'ized expression: "( 1 SkipSpace ) "
; Expanded expression: " 1  SkipSpace ()2 "
; Fused expression:    "( 1 , SkipSpace )2 "
    push    1
    call    _SkipSpace
    sub     sp, -2
; continue
    jmp     L770
; }
L853:
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; return
; RPN'ized expression: "ch "
; Expanded expression: "(@-4) *(2) "
; Fused expression:    "*(2) (@-4) "
    mov     ax, [bp-4]
    jmp     L769
; }
    jmp     L778
L849:
L778:
; if
; RPN'ized expression: "( p *u isdigit ) "
; Expanded expression: " (@-2) *(2) *(1)  isdigit ()2 "
; Fused expression:    "( *(2) (@-2) *(1) ax , isdigit )2 "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    push    ax
    call    _isdigit
    sub     sp, -2
; JumpIfZero
    test    ax, ax
    jz      L856
; {
; RPN'ized expression: "TokenValueInt 0 = "
; Expanded expression: "TokenValueInt 0 =(2) "
; Fused expression:    "=(34) *TokenValueInt 0 "
    mov     ax, 0
    mov     [_TokenValueInt], ax
; if
; RPN'ized expression: "p *u 48 == "
; Expanded expression: "(@-2) *(2) *(1) 48 == "
; Fused expression:    "*(2) (@-2) == *ax 48 IF! "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 48
    jne     L858
; {
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; if
; RPN'ized expression: "p *u 120 == p *u 88 == || "
; Expanded expression: "(@-2) *(2) *(1) 120 == _Bool [sh||->862] (@-2) *(2) *(1) 88 == _Bool ||[862] "
; Fused expression:    "*(2) (@-2) == *ax 120 _Bool [sh||->862] *(2) (@-2) == *ax 88 _Bool ||[862] "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 120
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L862
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 88
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L862:
; JumpIfZero
    test    ax, ax
    jz      L860
; {
; loc                     ch : (@-6): int
    sub     sp, 2
; loc                     cnt : (@-8): int
    sub     sp, 2
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "=(34) *(@-8) 0 "
    mov     ax, 0
    mov     [bp-8], ax
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; while
; RPN'ized expression: "ch p *u = 0 != ( ch isdigit ) ( ch , L865 strchr ) || && "
; Expanded expression: "(@-6) (@-2) *(2) *(1) =(2) 0 != _Bool [sh&&->867]  (@-6) *(2)  isdigit ()2 _Bool [sh||->868]  (@-6) *(2)  L865  strchr ()4 _Bool ||[868] _Bool &&[867] "
L863:
; SEGMENT _TEXT
SEGMENT _DATA
L865:
    db  "abcdefABCDEF",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "*(2) (@-2) =(33) *(@-6) *ax != ax 0 _Bool [sh&&->867] ( *(2) (@-6) , isdigit )2 _Bool [sh||->868] ( *(2) (@-6) , L865 , strchr )4 _Bool ||[868] _Bool &&[867] "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    mov     [bp-6], ax
    cmp     ax, 0
    setne   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L867
    push    word [bp-6]
    call    _isdigit
    sub     sp, -2
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L868
    push    word [bp-6]
    push    L865
    call    _strchr
    sub     sp, -4
    test    ax, ax
    setnz   al
    cbw
L868:
    test    ax, ax
    setnz   al
    cbw
L867:
; JumpIfZero
    test    ax, ax
    jz      L864
; {
; if
; RPN'ized expression: "ch 97 >= "
; Expanded expression: "(@-6) *(2) 97 >= "
; Fused expression:    ">= *(@-6) 97 IF! "
    mov     ax, [bp-6]
    cmp     ax, 97
    jl      L869
; RPN'ized expression: "ch 97 10 - -= "
; Expanded expression: "(@-6) 87 -=(2) "
; Fused expression:    "-=(34) *(@-6) 87 "
    mov     ax, [bp-6]
    sub     ax, 87
    mov     [bp-6], ax
    jmp     L870
L869:
; else
; if
; RPN'ized expression: "ch 65 >= "
; Expanded expression: "(@-6) *(2) 65 >= "
; Fused expression:    ">= *(@-6) 65 IF! "
    mov     ax, [bp-6]
    cmp     ax, 65
    jl      L871
; RPN'ized expression: "ch 65 10 - -= "
; Expanded expression: "(@-6) 55 -=(2) "
; Fused expression:    "-=(34) *(@-6) 55 "
    mov     ax, [bp-6]
    sub     ax, 55
    mov     [bp-6], ax
    jmp     L872
L871:
; else
; RPN'ized expression: "ch 48 -= "
; Expanded expression: "(@-6) 48 -=(2) "
; Fused expression:    "-=(34) *(@-6) 48 "
    mov     ax, [bp-6]
    sub     ax, 48
    mov     [bp-6], ax
L872:
L870:
; RPN'ized expression: "TokenValueInt 16 *= "
; Expanded expression: "TokenValueInt 16 *=(2) "
; Fused expression:    "*=(34) *TokenValueInt 16 "
    mov     ax, [_TokenValueInt]
    imul    ax, ax, 16
    mov     [_TokenValueInt], ax
; RPN'ized expression: "TokenValueInt ch += "
; Expanded expression: "TokenValueInt (@-6) *(2) +=(2) "
; Fused expression:    "+=(34) *TokenValueInt *(@-6) "
    mov     ax, [_TokenValueInt]
    add     ax, [bp-6]
    mov     [_TokenValueInt], ax
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; RPN'ized expression: "cnt ++p "
; Expanded expression: "(@-8) ++p(2) "
; Fused expression:    "++p(2) *(@-8) "
    mov     ax, [bp-8]
    inc     word [bp-8]
; }
    jmp     L863
L864:
; if
; RPN'ized expression: "cnt 0 == "
; Expanded expression: "(@-8) *(2) 0 == "
; Fused expression:    "== *(@-8) 0 IF! "
    mov     ax, [bp-8]
    cmp     ax, 0
    jne     L873
; RPN'ized expression: "( L875 error ) "
; Expanded expression: " L875  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L875:
    db  "Error: Invalid hexadecimal constant",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L875 , error )2 "
    push    L875
    call    _error
    sub     sp, -2
L873:
    sub     sp, -4
; }
    jmp     L861
L860:
; else
; while
; RPN'ized expression: "p *u 48 >= p *u 55 <= && "
; Expanded expression: "(@-2) *(2) *(1) 48 >= _Bool [sh&&->879] (@-2) *(2) *(1) 55 <= _Bool &&[879] "
L877:
; Fused expression:    "*(2) (@-2) >= *ax 48 _Bool [sh&&->879] *(2) (@-2) <= *ax 55 _Bool &&[879] "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 48
    setge   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L879
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 55
    setle   al
    cbw
    test    ax, ax
    setnz   al
    cbw
L879:
; JumpIfZero
    test    ax, ax
    jz      L878
; {
; RPN'ized expression: "TokenValueInt 8 *= "
; Expanded expression: "TokenValueInt 8 *=(2) "
; Fused expression:    "*=(34) *TokenValueInt 8 "
    mov     ax, [_TokenValueInt]
    imul    ax, ax, 8
    mov     [_TokenValueInt], ax
; RPN'ized expression: "TokenValueInt p *u 48 - += "
; Expanded expression: "TokenValueInt (@-2) *(2) *(1) 48 - +=(2) "
; Fused expression:    "*(2) (@-2) - *ax 48 +=(34) *TokenValueInt ax "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    sub     ax, 48
    mov     cx, ax
    mov     ax, [_TokenValueInt]
    add     ax, cx
    mov     [_TokenValueInt], ax
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; }
    jmp     L877
L878:
L861:
; }
    jmp     L859
L858:
; else
; while
; RPN'ized expression: "p *u 48 >= p *u 57 <= && "
; Expanded expression: "(@-2) *(2) *(1) 48 >= _Bool [sh&&->882] (@-2) *(2) *(1) 57 <= _Bool &&[882] "
L880:
; Fused expression:    "*(2) (@-2) >= *ax 48 _Bool [sh&&->882] *(2) (@-2) <= *ax 57 _Bool &&[882] "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 48
    setge   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L882
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 57
    setle   al
    cbw
    test    ax, ax
    setnz   al
    cbw
L882:
; JumpIfZero
    test    ax, ax
    jz      L881
; {
; RPN'ized expression: "TokenValueInt 10 *= "
; Expanded expression: "TokenValueInt 10 *=(2) "
; Fused expression:    "*=(34) *TokenValueInt 10 "
    mov     ax, [_TokenValueInt]
    imul    ax, ax, 10
    mov     [_TokenValueInt], ax
; RPN'ized expression: "TokenValueInt p *u 48 - += "
; Expanded expression: "TokenValueInt (@-2) *(2) *(1) 48 - +=(2) "
; Fused expression:    "*(2) (@-2) - *ax 48 +=(34) *TokenValueInt ax "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    sub     ax, 48
    mov     cx, ax
    mov     ax, [_TokenValueInt]
    add     ax, cx
    mov     [_TokenValueInt], ax
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; }
    jmp     L880
L881:
L859:
; return
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
    mov     ax, 1
    jmp     L769
; }
L856:
; if
; RPN'ized expression: "p *u 39 == p *u 34 == || "
; Expanded expression: "(@-2) *(2) *(1) 39 == _Bool [sh||->885] (@-2) *(2) *(1) 34 == _Bool ||[885] "
; Fused expression:    "*(2) (@-2) == *ax 39 _Bool [sh||->885] *(2) (@-2) == *ax 34 _Bool ||[885] "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 39
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L885
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 34
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L885:
; JumpIfZero
    test    ax, ax
    jz      L883
; {
; loc             terminator : (@-6): char
    sub     sp, 2
; =
; RPN'ized expression: "p *u "
; Expanded expression: "(@-2) *(2) *(1) "
; Fused expression:    "*(2) (@-2) =(33) *(@-6) *ax "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    mov     [bp-6], ax
; loc             ch : (@-8): char
    sub     sp, 2
; RPN'ized expression: "TokenStringLen 0 = "
; Expanded expression: "TokenStringLen 0 =(2) "
; Fused expression:    "=(34) *TokenStringLen 0 "
    mov     ax, 0
    mov     [_TokenStringLen], ax
; RPN'ized expression: "TokenValueString TokenStringLen + *u 0 = "
; Expanded expression: "TokenValueString TokenStringLen *(2) + 0 =(1) "
; Fused expression:    "+ TokenValueString *TokenStringLen =(18) *ax 0 "
    mov     ax, _TokenValueString
    add     ax, [_TokenStringLen]
    mov     bx, ax
    mov     ax, 0
    mov     [bx], al
    cbw
; for
L886:
    jmp     L888
L887:
    jmp     L886
L888:
; {
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; while
; RPN'ized expression: "p *u 0 == p *u terminator == || ( p *u , L892 strchr ) || 0 == "
; Expanded expression: "(@-2) *(2) *(1) 0 == _Bool [sh||->895] (@-2) *(2) *(1) (@-6) *(1) == _Bool ||[895] _Bool [sh||->894]  (@-2) *(2) *(1)  L892  strchr ()4 _Bool ||[894] 0 == "
L890:
; SEGMENT _TEXT
SEGMENT _DATA
L892:
    db  7,8,12,10,13,9,11,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "*(2) (@-2) == *ax 0 _Bool [sh||->895] *(2) (@-2) == *ax *(@-6) _Bool ||[895] _Bool [sh||->894] ( *(2) (@-2) *(1) ax , L892 , strchr )4 _Bool ||[894] == ax 0 IF! "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 0
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L895
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    movsx   cx, byte [bp-6]
    cmp     ax, cx
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L895:
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L894
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    push    ax
    push    L892
    call    _strchr
    sub     sp, -4
    test    ax, ax
    setnz   al
    cbw
L894:
    cmp     ax, 0
    jne     L891
; {
; RPN'ized expression: "ch p *u = "
; Expanded expression: "(@-8) (@-2) *(2) *(1) =(1) "
; Fused expression:    "*(2) (@-2) =(17) *(@-8) *ax "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    mov     [bp-8], al
    cbw
; if
; RPN'ized expression: "ch 92 == "
; Expanded expression: "(@-8) *(1) 92 == "
; Fused expression:    "== *(@-8) 92 IF! "
    mov     al, [bp-8]
    cbw
    cmp     ax, 92
    jne     L896
; {
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; RPN'ized expression: "ch p *u = "
; Expanded expression: "(@-8) (@-2) *(2) *(1) =(1) "
; Fused expression:    "*(2) (@-2) =(17) *(@-8) *ax "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    mov     [bp-8], al
    cbw
; if
; RPN'ized expression: "ch 0 == ( ch , L900 strchr ) || "
; Expanded expression: "(@-8) *(1) 0 == _Bool [sh||->902]  (@-8) *(1)  L900  strchr ()4 _Bool ||[902] "
; SEGMENT _TEXT
SEGMENT _DATA
L900:
    db  7,8,12,10,13,9,11,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "== *(@-8) 0 _Bool [sh||->902] ( *(1) (@-8) , L900 , strchr )4 _Bool ||[902] "
    mov     al, [bp-8]
    cbw
    cmp     ax, 0
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L902
    mov     al, [bp-8]
    cbw
    push    ax
    push    L900
    call    _strchr
    sub     sp, -4
    test    ax, ax
    setnz   al
    cbw
L902:
; JumpIfZero
    test    ax, ax
    jz      L898
; break
    jmp     L891
L898:
; switch
; RPN'ized expression: "ch "
; Expanded expression: "(@-8) *(1) "
; Fused expression:    "*(1) (@-8) "
    mov     al, [bp-8]
    cbw
    jmp     L905
; {
; case
; RPN'ized expression: "97 "
; Expanded expression: "97 "
; Expression value: 97
    jmp     L906
L905:
    cmp     ax, 97
    jne     L907
L906:
; RPN'ized expression: "ch 7 = "
; Expanded expression: "(@-8) 7 =(1) "
; Fused expression:    "=(18) *(@-8) 7 "
    mov     ax, 7
    mov     [bp-8], al
    cbw
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; break
    jmp     L903
; case
; RPN'ized expression: "98 "
; Expanded expression: "98 "
; Expression value: 98
    jmp     L908
L907:
    cmp     ax, 98
    jne     L909
L908:
; RPN'ized expression: "ch 8 = "
; Expanded expression: "(@-8) 8 =(1) "
; Fused expression:    "=(18) *(@-8) 8 "
    mov     ax, 8
    mov     [bp-8], al
    cbw
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; break
    jmp     L903
; case
; RPN'ized expression: "102 "
; Expanded expression: "102 "
; Expression value: 102
    jmp     L910
L909:
    cmp     ax, 102
    jne     L911
L910:
; RPN'ized expression: "ch 12 = "
; Expanded expression: "(@-8) 12 =(1) "
; Fused expression:    "=(18) *(@-8) 12 "
    mov     ax, 12
    mov     [bp-8], al
    cbw
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; break
    jmp     L903
; case
; RPN'ized expression: "110 "
; Expanded expression: "110 "
; Expression value: 110
    jmp     L912
L911:
    cmp     ax, 110
    jne     L913
L912:
; RPN'ized expression: "ch 10 = "
; Expanded expression: "(@-8) 10 =(1) "
; Fused expression:    "=(18) *(@-8) 10 "
    mov     ax, 10
    mov     [bp-8], al
    cbw
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; break
    jmp     L903
; case
; RPN'ized expression: "114 "
; Expanded expression: "114 "
; Expression value: 114
    jmp     L914
L913:
    cmp     ax, 114
    jne     L915
L914:
; RPN'ized expression: "ch 13 = "
; Expanded expression: "(@-8) 13 =(1) "
; Fused expression:    "=(18) *(@-8) 13 "
    mov     ax, 13
    mov     [bp-8], al
    cbw
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; break
    jmp     L903
; case
; RPN'ized expression: "116 "
; Expanded expression: "116 "
; Expression value: 116
    jmp     L916
L915:
    cmp     ax, 116
    jne     L917
L916:
; RPN'ized expression: "ch 9 = "
; Expanded expression: "(@-8) 9 =(1) "
; Fused expression:    "=(18) *(@-8) 9 "
    mov     ax, 9
    mov     [bp-8], al
    cbw
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; break
    jmp     L903
; case
; RPN'ized expression: "118 "
; Expanded expression: "118 "
; Expression value: 118
    jmp     L918
L917:
    cmp     ax, 118
    jne     L919
L918:
; RPN'ized expression: "ch 11 = "
; Expanded expression: "(@-8) 11 =(1) "
; Fused expression:    "=(18) *(@-8) 11 "
    mov     ax, 11
    mov     [bp-8], al
    cbw
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; break
    jmp     L903
; case
; RPN'ized expression: "120 "
; Expanded expression: "120 "
; Expression value: 120
    jmp     L920
L919:
    cmp     ax, 120
    jne     L921
L920:
; {
; loc                                 cnt : (@-10): int
    sub     sp, 2
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "=(34) *(@-10) 0 "
    mov     ax, 0
    mov     [bp-10], ax
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; RPN'ized expression: "ch 0 = "
; Expanded expression: "(@-8) 0 =(1) "
; Fused expression:    "=(18) *(@-8) 0 "
    mov     ax, 0
    mov     [bp-8], al
    cbw
; while
; RPN'ized expression: "p *u 0 != ( p *u isdigit ) ( p *u , L925 strchr ) || && "
; Expanded expression: "(@-2) *(2) *(1) 0 != _Bool [sh&&->927]  (@-2) *(2) *(1)  isdigit ()2 _Bool [sh||->928]  (@-2) *(2) *(1)  L925  strchr ()4 _Bool ||[928] _Bool &&[927] "
L923:
; SEGMENT _TEXT
SEGMENT _DATA
L925:
    db  "abcdefABCDEF",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "*(2) (@-2) != *ax 0 _Bool [sh&&->927] ( *(2) (@-2) *(1) ax , isdigit )2 _Bool [sh||->928] ( *(2) (@-2) *(1) ax , L925 , strchr )4 _Bool ||[928] _Bool &&[927] "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 0
    setne   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L927
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    push    ax
    call    _isdigit
    sub     sp, -2
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L928
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    push    ax
    push    L925
    call    _strchr
    sub     sp, -4
    test    ax, ax
    setnz   al
    cbw
L928:
    test    ax, ax
    setnz   al
    cbw
L927:
; JumpIfZero
    test    ax, ax
    jz      L924
; {
; RPN'ized expression: "ch 16 *= "
; Expanded expression: "(@-8) 16 *=(1) "
; Fused expression:    "*=(18) *(@-8) 16 "
    mov     al, [bp-8]
    cbw
    imul    ax, ax, 16
    mov     [bp-8], al
    cbw
; if
; RPN'ized expression: "p *u 97 >= "
; Expanded expression: "(@-2) *(2) *(1) 97 >= "
; Fused expression:    "*(2) (@-2) >= *ax 97 IF! "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 97
    jl      L929
; RPN'ized expression: "ch p *u 97 - 10 + += "
; Expanded expression: "(@-8) (@-2) *(2) *(1) 97 - 10 + +=(1) "
; Fused expression:    "*(2) (@-2) - *ax 97 + ax 10 +=(18) *(@-8) ax "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    sub     ax, 97
    add     ax, 10
    mov     cx, ax
    mov     al, [bp-8]
    cbw
    add     ax, cx
    mov     [bp-8], al
    cbw
    jmp     L930
L929:
; else
; if
; RPN'ized expression: "p *u 65 >= "
; Expanded expression: "(@-2) *(2) *(1) 65 >= "
; Fused expression:    "*(2) (@-2) >= *ax 65 IF! "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 65
    jl      L931
; RPN'ized expression: "ch p *u 65 - 10 + += "
; Expanded expression: "(@-8) (@-2) *(2) *(1) 65 - 10 + +=(1) "
; Fused expression:    "*(2) (@-2) - *ax 65 + ax 10 +=(18) *(@-8) ax "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    sub     ax, 65
    add     ax, 10
    mov     cx, ax
    mov     al, [bp-8]
    cbw
    add     ax, cx
    mov     [bp-8], al
    cbw
    jmp     L932
L931:
; else
; RPN'ized expression: "ch p *u 48 - += "
; Expanded expression: "(@-8) (@-2) *(2) *(1) 48 - +=(1) "
; Fused expression:    "*(2) (@-2) - *ax 48 +=(18) *(@-8) ax "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    sub     ax, 48
    mov     cx, ax
    mov     al, [bp-8]
    cbw
    add     ax, cx
    mov     [bp-8], al
    cbw
L932:
L930:
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; RPN'ized expression: "cnt ++p "
; Expanded expression: "(@-10) ++p(2) "
; Fused expression:    "++p(2) *(@-10) "
    mov     ax, [bp-10]
    inc     word [bp-10]
; }
    jmp     L923
L924:
; if
; RPN'ized expression: "cnt 0 == "
; Expanded expression: "(@-10) *(2) 0 == "
; Fused expression:    "== *(@-10) 0 IF! "
    mov     ax, [bp-10]
    cmp     ax, 0
    jne     L933
; RPN'ized expression: "( L935 error ) "
; Expanded expression: " L935  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L935:
    db  "Error: Unsupported or invalid character/string constant",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L935 , error )2 "
    push    L935
    call    _error
    sub     sp, -2
L933:
    sub     sp, -2
; }
; break
    jmp     L903
; default
L904:
; if
; RPN'ized expression: "p *u 48 >= p *u 55 <= && "
; Expanded expression: "(@-2) *(2) *(1) 48 >= _Bool [sh&&->939] (@-2) *(2) *(1) 55 <= _Bool &&[939] "
; Fused expression:    "*(2) (@-2) >= *ax 48 _Bool [sh&&->939] *(2) (@-2) <= *ax 55 _Bool &&[939] "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 48
    setge   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L939
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 55
    setle   al
    cbw
    test    ax, ax
    setnz   al
    cbw
L939:
; JumpIfZero
    test    ax, ax
    jz      L937
; {
; loc                                 cnt : (@-10): int
    sub     sp, 2
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "=(34) *(@-10) 0 "
    mov     ax, 0
    mov     [bp-10], ax
; RPN'ized expression: "ch 0 = "
; Expanded expression: "(@-8) 0 =(1) "
; Fused expression:    "=(18) *(@-8) 0 "
    mov     ax, 0
    mov     [bp-8], al
    cbw
; while
; RPN'ized expression: "p *u 48 >= p *u 55 <= && "
; Expanded expression: "(@-2) *(2) *(1) 48 >= _Bool [sh&&->942] (@-2) *(2) *(1) 55 <= _Bool &&[942] "
L940:
; Fused expression:    "*(2) (@-2) >= *ax 48 _Bool [sh&&->942] *(2) (@-2) <= *ax 55 _Bool &&[942] "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 48
    setge   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L942
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 55
    setle   al
    cbw
    test    ax, ax
    setnz   al
    cbw
L942:
; JumpIfZero
    test    ax, ax
    jz      L941
; {
; RPN'ized expression: "ch ch 8 * p *u + 48 - = "
; Expanded expression: "(@-8) (@-8) *(1) 8 * (@-2) *(2) *(1) + 48 - =(1) "
; Fused expression:    "* *(@-8) 8 push-ax *(2) (@-2) + *sp *ax - ax 48 =(18) *(@-8) ax "
    mov     al, [bp-8]
    cbw
    imul    ax, ax, 8
    push    ax
    mov     ax, [bp-2]
    mov     bx, ax
    movsx   cx, byte [bx]
    pop     ax
    add     ax, cx
    sub     ax, 48
    mov     [bp-8], al
    cbw
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; RPN'ized expression: "cnt ++p "
; Expanded expression: "(@-10) ++p(2) "
; Fused expression:    "++p(2) *(@-10) "
    mov     ax, [bp-10]
    inc     word [bp-10]
; }
    jmp     L940
L941:
; if
; RPN'ized expression: "cnt 0 == "
; Expanded expression: "(@-10) *(2) 0 == "
; Fused expression:    "== *(@-10) 0 IF! "
    mov     ax, [bp-10]
    cmp     ax, 0
    jne     L943
; RPN'ized expression: "( L945 error ) "
; Expanded expression: " L945  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L945:
    db  "Error: Unsupported or invalid character/string constant",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L945 , error )2 "
    push    L945
    call    _error
    sub     sp, -2
L943:
    sub     sp, -2
; }
    jmp     L938
L937:
; else
; {
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; }
L938:
; break
    jmp     L903
; }
    jmp     L903
L921:
    jmp     L904
L903:
; }
    jmp     L897
L896:
; else
; {
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; }
L897:
; if
; RPN'ized expression: "terminator 39 == "
; Expanded expression: "(@-6) *(1) 39 == "
; Fused expression:    "== *(@-6) 39 IF! "
    mov     al, [bp-6]
    cbw
    cmp     ax, 39
    jne     L947
; {
; if
; RPN'ized expression: "TokenStringLen 0 != "
; Expanded expression: "TokenStringLen *(2) 0 != "
; Fused expression:    "!= *TokenStringLen 0 IF! "
    mov     ax, [_TokenStringLen]
    cmp     ax, 0
    je      L949
; RPN'ized expression: "( L951 error ) "
; Expanded expression: " L951  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L951:
    db  "Error: Character constant too long",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L951 , error )2 "
    push    L951
    call    _error
    sub     sp, -2
L949:
; }
    jmp     L948
L947:
; else
; if
; RPN'ized expression: "TokenStringLen 127 == "
; Expanded expression: "TokenStringLen *(2) 127 == "
; Fused expression:    "== *TokenStringLen 127 IF! "
    mov     ax, [_TokenStringLen]
    cmp     ax, 127
    jne     L953
; RPN'ized expression: "( L955 error ) "
; Expanded expression: " L955  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L955:
    db  "Error: String constant too long",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L955 , error )2 "
    push    L955
    call    _error
    sub     sp, -2
L953:
L948:
; RPN'ized expression: "TokenValueString TokenStringLen ++p + *u ch = "
; Expanded expression: "TokenValueString TokenStringLen ++p(2) + (@-8) *(1) =(1) "
; Fused expression:    "++p(2) *TokenStringLen + TokenValueString ax =(17) *ax *(@-8) "
    mov     ax, [_TokenStringLen]
    inc     word [_TokenStringLen]
    mov     cx, ax
    mov     ax, _TokenValueString
    add     ax, cx
    mov     bx, ax
    mov     al, [bp-8]
    cbw
    mov     [bx], al
    cbw
; RPN'ized expression: "TokenValueString TokenStringLen + *u 0 = "
; Expanded expression: "TokenValueString TokenStringLen *(2) + 0 =(1) "
; Fused expression:    "+ TokenValueString *TokenStringLen =(18) *ax 0 "
    mov     ax, _TokenValueString
    add     ax, [_TokenStringLen]
    mov     bx, ax
    mov     ax, 0
    mov     [bx], al
    cbw
; }
    jmp     L890
L891:
; if
; RPN'ized expression: "p *u terminator != "
; Expanded expression: "(@-2) *(2) *(1) (@-6) *(1) != "
; Fused expression:    "*(2) (@-2) != *ax *(@-6) IF! "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    movsx   cx, byte [bp-6]
    cmp     ax, cx
    je      L957
; RPN'ized expression: "( L959 error ) "
; Expanded expression: " L959  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L959:
    db  "Error: Unsupported or invalid character/string constant",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L959 , error )2 "
    push    L959
    call    _error
    sub     sp, -2
L957:
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; if
; RPN'ized expression: "terminator 34 != "
; Expanded expression: "(@-6) *(1) 34 != "
; Fused expression:    "!= *(@-6) 34 IF! "
    mov     al, [bp-6]
    cbw
    cmp     ax, 34
    je      L961
; break
    jmp     L889
L961:
; RPN'ized expression: "( 1 SkipSpace ) "
; Expanded expression: " 1  SkipSpace ()2 "
; Fused expression:    "( 1 , SkipSpace )2 "
    push    1
    call    _SkipSpace
    sub     sp, -2
; if
; RPN'ized expression: "p *u 34 != "
; Expanded expression: "(@-2) *(2) *(1) 34 != "
; Fused expression:    "*(2) (@-2) != *ax 34 IF! "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 34
    je      L963
; break
    jmp     L889
L963:
; }
    jmp     L887
L889:
; if
; RPN'ized expression: "terminator 39 == "
; Expanded expression: "(@-6) *(1) 39 == "
; Fused expression:    "== *(@-6) 39 IF! "
    mov     al, [bp-6]
    cbw
    cmp     ax, 39
    jne     L965
; {
; if
; RPN'ized expression: "TokenStringLen 1 != "
; Expanded expression: "TokenStringLen *(2) 1 != "
; Fused expression:    "!= *TokenStringLen 1 IF! "
    mov     ax, [_TokenStringLen]
    cmp     ax, 1
    je      L967
; RPN'ized expression: "( L969 error ) "
; Expanded expression: " L969  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L969:
    db  "Error: Character constant too short",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L969 , error )2 "
    push    L969
    call    _error
    sub     sp, -2
L967:
; RPN'ized expression: "TokenValueInt TokenValueString 0 + *u = "
; Expanded expression: "TokenValueInt TokenValueString 0 + *(1) =(2) "
; Fused expression:    "+ TokenValueString 0 =(33) *TokenValueInt *ax "
    mov     ax, _TokenValueString
    add     ax, 0
    mov     bx, ax
    mov     al, [bx]
    cbw
    mov     [_TokenValueInt], ax
; return
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
; Fused expression:    "2 "
    mov     ax, 2
    jmp     L769
; }
L965:
; return
; RPN'ized expression: "3 "
; Expanded expression: "3 "
; Expression value: 3
; Fused expression:    "3 "
    mov     ax, 3
    jmp     L769
    sub     sp, -4
; }
L883:
; if
; RPN'ized expression: "p *u 95 == ( p *u isalpha ) || "
; Expanded expression: "(@-2) *(2) *(1) 95 == _Bool [sh||->973]  (@-2) *(2) *(1)  isalpha ()2 _Bool ||[973] "
; Fused expression:    "*(2) (@-2) == *ax 95 _Bool [sh||->973] ( *(2) (@-2) *(1) ax , isalpha )2 _Bool ||[973] "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 95
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L973
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    push    ax
    call    _isalpha
    sub     sp, -2
    test    ax, ax
    setnz   al
    cbw
L973:
; JumpIfZero
    test    ax, ax
    jz      L971
; {
; loc             tok : (@-6): int
    sub     sp, 2
; loc             midx : (@-8): int
    sub     sp, 2
; RPN'ized expression: "( GetIdent ) "
; Expanded expression: " GetIdent ()0 "
; Fused expression:    "( GetIdent )0 "
    call    _GetIdent
; RPN'ized expression: "tok ( TokenIdentName GetTokenByWord ) = "
; Expanded expression: "(@-6)  TokenIdentName  GetTokenByWord ()2 =(2) "
; Fused expression:    "( TokenIdentName , GetTokenByWord )2 =(34) *(@-6) ax "
    push    _TokenIdentName
    call    _GetTokenByWord
    sub     sp, -2
    mov     [bp-6], ax
; if
; RPN'ized expression: "midx ( TokenIdentName FindMacro ) = 0 >= "
; Expanded expression: "(@-8)  TokenIdentName  FindMacro ()2 =(2) 0 >= "
; Fused expression:    "( TokenIdentName , FindMacro )2 =(34) *(@-8) ax >= ax 0 IF! "
    push    _TokenIdentName
    call    _FindMacro
    sub     sp, -2
    mov     [bp-8], ax
    cmp     ax, 0
    jl      L974
; {
; loc                 len : (@-10): int
    sub     sp, 2
; =
; RPN'ized expression: "MacroTable midx + *u "
; Expanded expression: "MacroTable (@-8) *(2) + *(1) "
; Fused expression:    "+ MacroTable *(@-8) =(33) *(@-10) *ax "
    mov     ax, _MacroTable
    add     ax, [bp-8]
    mov     bx, ax
    mov     al, [bx]
    cbw
    mov     [bp-10], ax
; if
; RPN'ized expression: "256 CharQueueLen - len 1 + < "
; Expanded expression: "256 CharQueueLen *(2) - (@-10) *(2) 1 + < "
; Fused expression:    "- 256 *CharQueueLen push-ax + *(@-10) 1 < *sp ax IF! "
    mov     ax, 256
    sub     ax, [_CharQueueLen]
    push    ax
    mov     ax, [bp-10]
    add     ax, 1
    mov     cx, ax
    pop     ax
    cmp     ax, cx
    jge     L976
; RPN'ized expression: "( TokenIdentName , L978 error ) "
; Expanded expression: " TokenIdentName  L978  error ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L978:
    db  "Error: Macro expansion is too long at '%s'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( TokenIdentName , L978 , error )4 "
    push    _TokenIdentName
    push    L978
    call    _error
    sub     sp, -4
L976:
; RPN'ized expression: "( CharQueueLen , CharQueue , CharQueue len + 1 + memmove ) "
; Expanded expression: " CharQueueLen *(2)  CharQueue  CharQueue (@-10) *(2) + 1 +  memmove ()6 "
; Fused expression:    "( *(2) CharQueueLen , CharQueue , + CharQueue *(@-10) + ax 1 , memmove )6 "
    push    word [_CharQueueLen]
    push    _CharQueue
    mov     ax, _CharQueue
    add     ax, [bp-10]
    add     ax, 1
    push    ax
    call    _memmove
    sub     sp, -6
; RPN'ized expression: "( len , MacroTable midx + 1 + , CharQueue memcpy ) "
; Expanded expression: " (@-10) *(2)  MacroTable (@-8) *(2) + 1 +  CharQueue  memcpy ()6 "
; Fused expression:    "( *(2) (@-10) , + MacroTable *(@-8) + ax 1 , CharQueue , memcpy )6 "
    push    word [bp-10]
    mov     ax, _MacroTable
    add     ax, [bp-8]
    add     ax, 1
    push    ax
    push    _CharQueue
    call    _memcpy
    sub     sp, -6
; RPN'ized expression: "CharQueue len + *u 32 = "
; Expanded expression: "CharQueue (@-10) *(2) + 32 =(1) "
; Fused expression:    "+ CharQueue *(@-10) =(18) *ax 32 "
    mov     ax, _CharQueue
    add     ax, [bp-10]
    mov     bx, ax
    mov     ax, 32
    mov     [bx], al
    cbw
; RPN'ized expression: "CharQueueLen len 1 + += "
; Expanded expression: "CharQueueLen (@-10) *(2) 1 + +=(2) "
; Fused expression:    "+ *(@-10) 1 +=(34) *CharQueueLen ax "
    mov     ax, [bp-10]
    add     ax, 1
    mov     cx, ax
    mov     ax, [_CharQueueLen]
    add     ax, cx
    mov     [_CharQueueLen], ax
; continue
    sub     sp, -6
    jmp     L770
    sub     sp, -2
; }
L974:
; return
; RPN'ized expression: "tok "
; Expanded expression: "(@-6) *(2) "
; Fused expression:    "*(2) (@-6) "
    mov     ax, [bp-6]
    jmp     L769
    sub     sp, -4
; }
L971:
; if
; RPN'ized expression: "p *u 35 == "
; Expanded expression: "(@-2) *(2) *(1) 35 == "
; Fused expression:    "*(2) (@-2) == *ax 35 IF! "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 35
    jne     L980
; {
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; RPN'ized expression: "( 0 SkipSpace ) "
; Expanded expression: " 0  SkipSpace ()2 "
; Fused expression:    "( 0 , SkipSpace )2 "
    push    0
    call    _SkipSpace
    sub     sp, -2
; RPN'ized expression: "( GetIdent ) "
; Expanded expression: " GetIdent ()0 "
; Fused expression:    "( GetIdent )0 "
    call    _GetIdent
; if
; RPN'ized expression: "( L984 , TokenIdentName strcmp ) "
; Expanded expression: " L984  TokenIdentName  strcmp ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L984:
    db  "define",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L984 , TokenIdentName , strcmp )4 "
    push    L984
    push    _TokenIdentName
    call    _strcmp
    sub     sp, -4
; JumpIfZero
    test    ax, ax
    jz      L982
; RPN'ized expression: "( L986 error ) "
; Expanded expression: " L986  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L986:
    db  "Error: Unsupported or invalid preprocessor directive",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L986 , error )2 "
    push    L986
    call    _error
    sub     sp, -2
L982:
; RPN'ized expression: "( 0 SkipSpace ) "
; Expanded expression: " 0  SkipSpace ()2 "
; Fused expression:    "( 0 , SkipSpace )2 "
    push    0
    call    _SkipSpace
    sub     sp, -2
; RPN'ized expression: "( GetIdent ) "
; Expanded expression: " GetIdent ()0 "
; Fused expression:    "( GetIdent )0 "
    call    _GetIdent
; if
; RPN'ized expression: "( TokenIdentName FindMacro ) 0 >= "
; Expanded expression: " TokenIdentName  FindMacro ()2 0 >= "
; Fused expression:    "( TokenIdentName , FindMacro )2 >= ax 0 IF! "
    push    _TokenIdentName
    call    _FindMacro
    sub     sp, -2
    cmp     ax, 0
    jl      L988
; RPN'ized expression: "( TokenIdentName , L990 error ) "
; Expanded expression: " TokenIdentName  L990  error ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L990:
    db  "Error: Redefinition of macro '%s'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( TokenIdentName , L990 , error )4 "
    push    _TokenIdentName
    push    L990
    call    _error
    sub     sp, -4
L988:
; if
; RPN'ized expression: "p *u 40 == "
; Expanded expression: "(@-2) *(2) *(1) 40 == "
; Fused expression:    "*(2) (@-2) == *ax 40 IF! "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 40
    jne     L992
; RPN'ized expression: "( TokenIdentName , L994 error ) "
; Expanded expression: " TokenIdentName  L994  error ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L994:
    db  "Error: Unsupported type of macro '%s'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( TokenIdentName , L994 , error )4 "
    push    _TokenIdentName
    push    L994
    call    _error
    sub     sp, -4
L992:
; RPN'ized expression: "( TokenIdentName AddMacroIdent ) "
; Expanded expression: " TokenIdentName  AddMacroIdent ()2 "
; Fused expression:    "( TokenIdentName , AddMacroIdent )2 "
    push    _TokenIdentName
    call    _AddMacroIdent
    sub     sp, -2
; RPN'ized expression: "( 0 SkipSpace ) "
; Expanded expression: " 0  SkipSpace ()2 "
; Fused expression:    "( 0 , SkipSpace )2 "
    push    0
    call    _SkipSpace
    sub     sp, -2
; while
; RPN'ized expression: "( p *u , L998 strchr ) 0 == "
; Expanded expression: " (@-2) *(2) *(1)  L998  strchr ()4 0 == "
L996:
; SEGMENT _TEXT
SEGMENT _DATA
L998:
    db  13,10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-2) *(1) ax , L998 , strchr )4 == ax 0 IF! "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    push    ax
    push    L998
    call    _strchr
    sub     sp, -4
    cmp     ax, 0
    jne     L997
; {
; RPN'ized expression: "( p *u AddMacroExpansionChar ) "
; Expanded expression: " (@-2) *(2) *(1)  AddMacroExpansionChar ()2 "
; Fused expression:    "( *(2) (@-2) *(1) ax , AddMacroExpansionChar )2 "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    push    ax
    call    _AddMacroExpansionChar
    sub     sp, -2
; RPN'ized expression: "( 1 ShiftCharN ) "
; Expanded expression: " 1  ShiftCharN ()2 "
; Fused expression:    "( 1 , ShiftCharN )2 "
    push    1
    call    _ShiftCharN
    sub     sp, -2
; if
; RPN'ized expression: "p *u 0 != ( p *u , L1002 strchr ) p *u 47 == p 1 + *u 47 == p 1 + *u 42 == || && || && "
; Expanded expression: "(@-2) *(2) *(1) 0 != _Bool [sh&&->1004]  (@-2) *(2) *(1)  L1002  strchr ()4 _Bool [sh||->1005] (@-2) *(2) *(1) 47 == _Bool [sh&&->1006] (@-2) *(2) 1 + *(1) 47 == _Bool [sh||->1007] (@-2) *(2) 1 + *(1) 42 == _Bool ||[1007] _Bool &&[1006] _Bool ||[1005] _Bool &&[1004] "
; SEGMENT _TEXT
SEGMENT _DATA
L1002:
    db  " ",9,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "*(2) (@-2) != *ax 0 _Bool [sh&&->1004] ( *(2) (@-2) *(1) ax , L1002 , strchr )4 _Bool [sh||->1005] *(2) (@-2) == *ax 47 _Bool [sh&&->1006] + *(@-2) 1 == *ax 47 _Bool [sh||->1007] + *(@-2) 1 == *ax 42 _Bool ||[1007] _Bool &&[1006] _Bool ||[1005] _Bool &&[1004] "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 0
    setne   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L1004
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    push    ax
    push    L1002
    call    _strchr
    sub     sp, -4
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L1005
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 47
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L1006
    mov     ax, [bp-2]
    add     ax, 1
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 47
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L1007
    mov     ax, [bp-2]
    add     ax, 1
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 42
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L1007:
    test    ax, ax
    setnz   al
    cbw
L1006:
    test    ax, ax
    setnz   al
    cbw
L1005:
    test    ax, ax
    setnz   al
    cbw
L1004:
; JumpIfZero
    test    ax, ax
    jz      L1000
; {
; RPN'ized expression: "( 0 SkipSpace ) "
; Expanded expression: " 0  SkipSpace ()2 "
; Fused expression:    "( 0 , SkipSpace )2 "
    push    0
    call    _SkipSpace
    sub     sp, -2
; RPN'ized expression: "( 32 AddMacroExpansionChar ) "
; Expanded expression: " 32  AddMacroExpansionChar ()2 "
; Fused expression:    "( 32 , AddMacroExpansionChar )2 "
    push    32
    call    _AddMacroExpansionChar
    sub     sp, -2
; }
L1000:
; }
    jmp     L996
L997:
; RPN'ized expression: "( 0 AddMacroExpansionChar ) "
; Expanded expression: " 0  AddMacroExpansionChar ()2 "
; Fused expression:    "( 0 , AddMacroExpansionChar )2 "
    push    0
    call    _AddMacroExpansionChar
    sub     sp, -2
; continue
    jmp     L770
; }
L980:
; RPN'ized expression: "( p *u , L1008 error ) "
; Expanded expression: " (@-2) *(2) *(1)  L1008  error ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1008:
    db  "Error: Unsupported or invalid character '%c'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-2) *(1) ax , L1008 , error )4 "
    mov     ax, [bp-2]
    mov     bx, ax
    mov     al, [bx]
    cbw
    push    ax
    push    L1008
    call    _error
    sub     sp, -4
; }
    jmp     L770
L771:
; return
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "0 "
    mov     ax, 0
    jmp     L769
L769:
    leave
    ret
; SEGMENT _TEXT
; glb GenLabel : (
; prm     Label : * char
;     ) void
SEGMENT _TEXT
    global  _GenLabel
_GenLabel:
    push    bp
    mov     bp, sp
; loc     Label : (@4): * char
; if
; RPN'ized expression: "OutputFormat 0 != "
; Expanded expression: "OutputFormat *(2) 0 != "
; Fused expression:    "!= *OutputFormat 0 IF! "
    mov     ax, [_OutputFormat]
    cmp     ax, 0
    je      L1011
; RPN'ized expression: "( Label , L1013 printf ) "
; Expanded expression: " (@4) *(2)  L1013  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1013:
    db  "    global  _%s",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@4) , L1013 , printf )4 "
    push    word [bp+4]
    push    L1013
    call    _printf
    sub     sp, -4
L1011:
; RPN'ized expression: "( Label , L1015 printf ) "
; Expanded expression: " (@4) *(2)  L1015  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1015:
    db  "_%s:",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@4) , L1015 , printf )4 "
    push    word [bp+4]
    push    L1015
    call    _printf
    sub     sp, -4
L1010:
    leave
    ret
; SEGMENT _TEXT
; glb GenExtern : (
; prm     Label : * char
;     ) void
SEGMENT _TEXT
    global  _GenExtern
_GenExtern:
    push    bp
    mov     bp, sp
; loc     Label : (@4): * char
; if
; RPN'ized expression: "OutputFormat 0 != "
; Expanded expression: "OutputFormat *(2) 0 != "
; Fused expression:    "!= *OutputFormat 0 IF! "
    mov     ax, [_OutputFormat]
    cmp     ax, 0
    je      L1018
; RPN'ized expression: "( Label , L1020 printf ) "
; Expanded expression: " (@4) *(2)  L1020  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1020:
    db  "    extern  _%s",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@4) , L1020 , printf )4 "
    push    word [bp+4]
    push    L1020
    call    _printf
    sub     sp, -4
L1018:
L1017:
    leave
    ret
; SEGMENT _TEXT
; glb GenPrintLabel : (
; prm     Label : * char
;     ) void
SEGMENT _TEXT
    global  _GenPrintLabel
_GenPrintLabel:
    push    bp
    mov     bp, sp
; loc     Label : (@4): * char
; if
; RPN'ized expression: "( Label *u isdigit ) "
; Expanded expression: " (@4) *(2) *(1)  isdigit ()2 "
; Fused expression:    "( *(2) (@4) *(1) ax , isdigit )2 "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     al, [bx]
    cbw
    push    ax
    call    _isdigit
    sub     sp, -2
; JumpIfZero
    test    ax, ax
    jz      L1023
; RPN'ized expression: "( Label , L1025 printf ) "
; Expanded expression: " (@4) *(2)  L1025  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1025:
    db  "L%s",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@4) , L1025 , printf )4 "
    push    word [bp+4]
    push    L1025
    call    _printf
    sub     sp, -4
    jmp     L1024
L1023:
; else
; RPN'ized expression: "( Label , L1027 printf ) "
; Expanded expression: " (@4) *(2)  L1027  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1027:
    db  "_%s",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@4) , L1027 , printf )4 "
    push    word [bp+4]
    push    L1027
    call    _printf
    sub     sp, -4
L1024:
L1022:
    leave
    ret
; SEGMENT _TEXT
; glb GenNumLabel : (
; prm     Label : int
;     ) void
SEGMENT _TEXT
    global  _GenNumLabel
_GenNumLabel:
    push    bp
    mov     bp, sp
; loc     Label : (@4): int
; RPN'ized expression: "( Label , L1030 printf ) "
; Expanded expression: " (@4) *(2)  L1030  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1030:
    db  "L%d:",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@4) , L1030 , printf )4 "
    push    word [bp+4]
    push    L1030
    call    _printf
    sub     sp, -4
L1029:
    leave
    ret
; SEGMENT _TEXT
; glb GenZeroData : (
; prm     Size : int
;     ) void
SEGMENT _TEXT
    global  _GenZeroData
_GenZeroData:
    push    bp
    mov     bp, sp
; loc     Size : (@4): int
; RPN'ized expression: "( Size , L1033 printf ) "
; Expanded expression: " (@4) *(2)  L1033  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1033:
    db  "    times %d db 0",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@4) , L1033 , printf )4 "
    push    word [bp+4]
    push    L1033
    call    _printf
    sub     sp, -4
L1032:
    leave
    ret
; SEGMENT _TEXT
; glb GenIntData : (
; prm     Size : int
; prm     Val : int
;     ) void
SEGMENT _TEXT
    global  _GenIntData
_GenIntData:
    push    bp
    mov     bp, sp
; loc     Size : (@4): int
; loc     Val : (@6): int
; if
; RPN'ized expression: "Size 1 == "
; Expanded expression: "(@4) *(2) 1 == "
; Fused expression:    "== *(@4) 1 IF! "
    mov     ax, [bp+4]
    cmp     ax, 1
    jne     L1036
; RPN'ized expression: "( Val , L1038 printf ) "
; Expanded expression: " (@6) *(2)  L1038  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1038:
    db  "    db  %d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@6) , L1038 , printf )4 "
    push    word [bp+6]
    push    L1038
    call    _printf
    sub     sp, -4
    jmp     L1037
L1036:
; else
; if
; RPN'ized expression: "Size 2 == "
; Expanded expression: "(@4) *(2) 2 == "
; Fused expression:    "== *(@4) 2 IF! "
    mov     ax, [bp+4]
    cmp     ax, 2
    jne     L1040
; RPN'ized expression: "( Val , L1042 printf ) "
; Expanded expression: " (@6) *(2)  L1042  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1042:
    db  "    dw  %d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@6) , L1042 , printf )4 "
    push    word [bp+6]
    push    L1042
    call    _printf
    sub     sp, -4
L1040:
L1037:
L1035:
    leave
    ret
; SEGMENT _TEXT
; glb GenAddrData : (
; prm     Size : int
; prm     Label : * char
;     ) void
SEGMENT _TEXT
    global  _GenAddrData
_GenAddrData:
    push    bp
    mov     bp, sp
; loc     Size : (@4): int
; loc     Label : (@6): * char
; if
; RPN'ized expression: "Size 1 == "
; Expanded expression: "(@4) *(2) 1 == "
; Fused expression:    "== *(@4) 1 IF! "
    mov     ax, [bp+4]
    cmp     ax, 1
    jne     L1045
; RPN'ized expression: "( L1047 printf ) "
; Expanded expression: " L1047  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1047:
    db  "    db  ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1047 , printf )2 "
    push    L1047
    call    _printf
    sub     sp, -2
    jmp     L1046
L1045:
; else
; if
; RPN'ized expression: "Size 2 == "
; Expanded expression: "(@4) *(2) 2 == "
; Fused expression:    "== *(@4) 2 IF! "
    mov     ax, [bp+4]
    cmp     ax, 2
    jne     L1049
; RPN'ized expression: "( L1051 printf ) "
; Expanded expression: " L1051  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1051:
    db  "    dw  ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1051 , printf )2 "
    push    L1051
    call    _printf
    sub     sp, -2
L1049:
L1046:
; RPN'ized expression: "( Label GenPrintLabel ) "
; Expanded expression: " (@6) *(2)  GenPrintLabel ()2 "
; Fused expression:    "( *(2) (@6) , GenPrintLabel )2 "
    push    word [bp+6]
    call    _GenPrintLabel
    sub     sp, -2
; RPN'ized expression: "( L1053 printf ) "
; Expanded expression: " L1053  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1053:
    db  10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1053 , printf )2 "
    push    L1053
    call    _printf
    sub     sp, -2
L1044:
    leave
    ret
; SEGMENT _TEXT
; glb GenJumpUncond : (
; prm     Label : int
;     ) void
SEGMENT _TEXT
    global  _GenJumpUncond
_GenJumpUncond:
    push    bp
    mov     bp, sp
; loc     Label : (@4): int
; RPN'ized expression: "( Label , L1056 printf ) "
; Expanded expression: " (@4) *(2)  L1056  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1056:
    db  "    jmp     L%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@4) , L1056 , printf )4 "
    push    word [bp+4]
    push    L1056
    call    _printf
    sub     sp, -4
L1055:
    leave
    ret
; SEGMENT _TEXT
; glb GenJumpIfNotEqual : (
; prm     val : int
; prm     Label : int
;     ) void
SEGMENT _TEXT
    global  _GenJumpIfNotEqual
_GenJumpIfNotEqual:
    push    bp
    mov     bp, sp
; loc     val : (@4): int
; loc     Label : (@6): int
; RPN'ized expression: "( Label , val , L1059 printf ) "
; Expanded expression: " (@6) *(2)  (@4) *(2)  L1059  printf ()6 "
; SEGMENT _TEXT
SEGMENT _DATA
L1059:
    db  "    cmp     ax, %d",10,"    jne     L%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@6) , *(2) (@4) , L1059 , printf )6 "
    push    word [bp+6]
    push    word [bp+4]
    push    L1059
    call    _printf
    sub     sp, -6
L1058:
    leave
    ret
; SEGMENT _TEXT
; glb GenJumpIfZero : (
; prm     Label : int
;     ) void
SEGMENT _TEXT
    global  _GenJumpIfZero
_GenJumpIfZero:
    push    bp
    mov     bp, sp
; loc     Label : (@4): int
; RPN'ized expression: "( L1062 printf ) "
; Expanded expression: " L1062  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1062:
    db  "; JumpIfZero",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1062 , printf )2 "
    push    L1062
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( Label , L1064 printf ) "
; Expanded expression: " (@4) *(2)  L1064  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1064:
    db  "    test    ax, ax",10,"    jz      L%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@4) , L1064 , printf )4 "
    push    word [bp+4]
    push    L1064
    call    _printf
    sub     sp, -4
L1061:
    leave
    ret
; SEGMENT _TEXT
; glb GenJumpIfNotZero : (
; prm     Label : int
;     ) void
SEGMENT _TEXT
    global  _GenJumpIfNotZero
_GenJumpIfNotZero:
    push    bp
    mov     bp, sp
; loc     Label : (@4): int
; RPN'ized expression: "( L1067 printf ) "
; Expanded expression: " L1067  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1067:
    db  "; JumpIfNotZero",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1067 , printf )2 "
    push    L1067
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( Label , L1069 printf ) "
; Expanded expression: " (@4) *(2)  L1069  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1069:
    db  "    test    ax, ax",10,"    jnz     L%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@4) , L1069 , printf )4 "
    push    word [bp+4]
    push    L1069
    call    _printf
    sub     sp, -4
L1066:
    leave
    ret
; SEGMENT _TEXT
; glb GenFxnProlog : (void) void
SEGMENT _TEXT
    global  _GenFxnProlog
_GenFxnProlog:
    push    bp
    mov     bp, sp
; RPN'ized expression: "( L1072 printf ) "
; Expanded expression: " L1072  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1072:
    db  "    push    bp",10,"    mov     bp, sp",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1072 , printf )2 "
    push    L1072
    call    _printf
    sub     sp, -2
L1071:
    leave
    ret
; SEGMENT _TEXT
; glb GenFxnEpilog : (void) void
SEGMENT _TEXT
    global  _GenFxnEpilog
_GenFxnEpilog:
    push    bp
    mov     bp, sp
; RPN'ized expression: "( L1075 printf ) "
; Expanded expression: " L1075  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1075:
    db  "    leave",10,"    ret",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1075 , printf )2 "
    push    L1075
    call    _printf
    sub     sp, -2
L1074:
    leave
    ret
; SEGMENT _TEXT
; glb GenLocalAlloc : (
; prm     Size : int
;     ) void
SEGMENT _TEXT
    global  _GenLocalAlloc
_GenLocalAlloc:
    push    bp
    mov     bp, sp
; loc     Size : (@4): int
; RPN'ized expression: "( Size , L1078 printf ) "
; Expanded expression: " (@4) *(2)  L1078  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1078:
    db  "    sub     sp, %d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@4) , L1078 , printf )4 "
    push    word [bp+4]
    push    L1078
    call    _printf
    sub     sp, -4
L1077:
    leave
    ret
; SEGMENT _TEXT
; glb GenExtendAlAx : (void) void
SEGMENT _TEXT
    global  _GenExtendAlAx
_GenExtendAlAx:
    push    bp
    mov     bp, sp
; if
; RPN'ized expression: "CharIsSigned "
; Expanded expression: "CharIsSigned *(2) "
; Fused expression:    "*(2) CharIsSigned "
    mov     ax, [_CharIsSigned]
; JumpIfZero
    test    ax, ax
    jz      L1081
; RPN'ized expression: "( L1083 printf ) "
; Expanded expression: " L1083  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1083:
    db  "    cbw",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1083 , printf )2 "
    push    L1083
    call    _printf
    sub     sp, -2
    jmp     L1082
L1081:
; else
; RPN'ized expression: "( L1085 printf ) "
; Expanded expression: " L1085  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1085:
    db  "    mov     ah, 0",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1085 , printf )2 "
    push    L1085
    call    _printf
    sub     sp, -2
L1082:
L1080:
    leave
    ret
; SEGMENT _TEXT
; glb GenReadIdent : (
; prm     OpSz : int
; prm     Label : * char
;     ) void
SEGMENT _TEXT
    global  _GenReadIdent
_GenReadIdent:
    push    bp
    mov     bp, sp
; loc     OpSz : (@4): int
; loc     Label : (@6): * char
; if
; RPN'ized expression: "OpSz 1 == "
; Expanded expression: "(@4) *(2) 1 == "
; Fused expression:    "== *(@4) 1 IF! "
    mov     ax, [bp+4]
    cmp     ax, 1
    jne     L1088
; {
; RPN'ized expression: "( L1090 printf ) "
; Expanded expression: " L1090  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1090:
    db  "    mov     al, [",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1090 , printf )2 "
    push    L1090
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( Label GenPrintLabel ) "
; Expanded expression: " (@6) *(2)  GenPrintLabel ()2 "
; Fused expression:    "( *(2) (@6) , GenPrintLabel )2 "
    push    word [bp+6]
    call    _GenPrintLabel
    sub     sp, -2
; RPN'ized expression: "( L1092 printf ) "
; Expanded expression: " L1092  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1092:
    db  "]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1092 , printf )2 "
    push    L1092
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( GenExtendAlAx ) "
; Expanded expression: " GenExtendAlAx ()0 "
; Fused expression:    "( GenExtendAlAx )0 "
    call    _GenExtendAlAx
; }
    jmp     L1089
L1088:
; else
; if
; RPN'ized expression: "OpSz 2 == "
; Expanded expression: "(@4) *(2) 2 == "
; Fused expression:    "== *(@4) 2 IF! "
    mov     ax, [bp+4]
    cmp     ax, 2
    jne     L1094
; {
; RPN'ized expression: "( L1096 printf ) "
; Expanded expression: " L1096  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1096:
    db  "    mov     ax, [",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1096 , printf )2 "
    push    L1096
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( Label GenPrintLabel ) "
; Expanded expression: " (@6) *(2)  GenPrintLabel ()2 "
; Fused expression:    "( *(2) (@6) , GenPrintLabel )2 "
    push    word [bp+6]
    call    _GenPrintLabel
    sub     sp, -2
; RPN'ized expression: "( L1098 printf ) "
; Expanded expression: " L1098  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1098:
    db  "]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1098 , printf )2 "
    push    L1098
    call    _printf
    sub     sp, -2
; }
L1094:
L1089:
L1087:
    leave
    ret
; SEGMENT _TEXT
; glb GenReadLocal : (
; prm     OpSz : int
; prm     Ofs : int
;     ) void
SEGMENT _TEXT
    global  _GenReadLocal
_GenReadLocal:
    push    bp
    mov     bp, sp
; loc     OpSz : (@4): int
; loc     Ofs : (@6): int
; if
; RPN'ized expression: "OpSz 1 == "
; Expanded expression: "(@4) *(2) 1 == "
; Fused expression:    "== *(@4) 1 IF! "
    mov     ax, [bp+4]
    cmp     ax, 1
    jne     L1101
; {
; RPN'ized expression: "( Ofs , L1103 printf ) "
; Expanded expression: " (@6) *(2)  L1103  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1103:
    db  "    mov     al, [bp%+d]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@6) , L1103 , printf )4 "
    push    word [bp+6]
    push    L1103
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( GenExtendAlAx ) "
; Expanded expression: " GenExtendAlAx ()0 "
; Fused expression:    "( GenExtendAlAx )0 "
    call    _GenExtendAlAx
; }
    jmp     L1102
L1101:
; else
; if
; RPN'ized expression: "OpSz 2 == "
; Expanded expression: "(@4) *(2) 2 == "
; Fused expression:    "== *(@4) 2 IF! "
    mov     ax, [bp+4]
    cmp     ax, 2
    jne     L1105
; RPN'ized expression: "( Ofs , L1107 printf ) "
; Expanded expression: " (@6) *(2)  L1107  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1107:
    db  "    mov     ax, [bp%+d]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@6) , L1107 , printf )4 "
    push    word [bp+6]
    push    L1107
    call    _printf
    sub     sp, -4
L1105:
L1102:
L1100:
    leave
    ret
; SEGMENT _TEXT
; glb GenReadIndirect : (
; prm     OpSz : int
;     ) void
SEGMENT _TEXT
    global  _GenReadIndirect
_GenReadIndirect:
    push    bp
    mov     bp, sp
; loc     OpSz : (@4): int
; RPN'ized expression: "( L1110 printf ) "
; Expanded expression: " L1110  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1110:
    db  "    mov     bx, ax",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1110 , printf )2 "
    push    L1110
    call    _printf
    sub     sp, -2
; if
; RPN'ized expression: "OpSz 1 == "
; Expanded expression: "(@4) *(2) 1 == "
; Fused expression:    "== *(@4) 1 IF! "
    mov     ax, [bp+4]
    cmp     ax, 1
    jne     L1112
; {
; RPN'ized expression: "( L1114 printf ) "
; Expanded expression: " L1114  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1114:
    db  "    mov     al, [bx]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1114 , printf )2 "
    push    L1114
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( GenExtendAlAx ) "
; Expanded expression: " GenExtendAlAx ()0 "
; Fused expression:    "( GenExtendAlAx )0 "
    call    _GenExtendAlAx
; }
    jmp     L1113
L1112:
; else
; if
; RPN'ized expression: "OpSz 2 == "
; Expanded expression: "(@4) *(2) 2 == "
; Fused expression:    "== *(@4) 2 IF! "
    mov     ax, [bp+4]
    cmp     ax, 2
    jne     L1116
; RPN'ized expression: "( L1118 printf ) "
; Expanded expression: " L1118  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1118:
    db  "    mov     ax, [bx]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1118 , printf )2 "
    push    L1118
    call    _printf
    sub     sp, -2
L1116:
L1113:
L1109:
    leave
    ret
; SEGMENT _TEXT
; glb GenIncDecIdent : (
; prm     OpSz : int
; prm     Label : * char
; prm     tok : int
;     ) void
SEGMENT _TEXT
    global  _GenIncDecIdent
_GenIncDecIdent:
    push    bp
    mov     bp, sp
; loc     OpSz : (@4): int
; loc     Label : (@6): * char
; loc     tok : (@8): int
; if
; RPN'ized expression: "OpSz 1 == "
; Expanded expression: "(@4) *(2) 1 == "
; Fused expression:    "== *(@4) 1 IF! "
    mov     ax, [bp+4]
    cmp     ax, 1
    jne     L1121
; {
; if
; RPN'ized expression: "tok 12 == "
; Expanded expression: "(@8) *(2) 12 == "
; Fused expression:    "== *(@8) 12 IF! "
    mov     ax, [bp+8]
    cmp     ax, 12
    jne     L1123
; RPN'ized expression: "( L1125 printf ) "
; Expanded expression: " L1125  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1125:
    db  "    inc     byte [",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1125 , printf )2 "
    push    L1125
    call    _printf
    sub     sp, -2
    jmp     L1124
L1123:
; else
; RPN'ized expression: "( L1127 printf ) "
; Expanded expression: " L1127  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1127:
    db  "    dec     byte [",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1127 , printf )2 "
    push    L1127
    call    _printf
    sub     sp, -2
L1124:
; RPN'ized expression: "( Label GenPrintLabel ) "
; Expanded expression: " (@6) *(2)  GenPrintLabel ()2 "
; Fused expression:    "( *(2) (@6) , GenPrintLabel )2 "
    push    word [bp+6]
    call    _GenPrintLabel
    sub     sp, -2
; RPN'ized expression: "( L1129 printf ) "
; Expanded expression: " L1129  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1129:
    db  "]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1129 , printf )2 "
    push    L1129
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( L1131 printf ) "
; Expanded expression: " L1131  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1131:
    db  "    mov     al, [",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1131 , printf )2 "
    push    L1131
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( Label GenPrintLabel ) "
; Expanded expression: " (@6) *(2)  GenPrintLabel ()2 "
; Fused expression:    "( *(2) (@6) , GenPrintLabel )2 "
    push    word [bp+6]
    call    _GenPrintLabel
    sub     sp, -2
; RPN'ized expression: "( L1133 printf ) "
; Expanded expression: " L1133  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1133:
    db  "]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1133 , printf )2 "
    push    L1133
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( GenExtendAlAx ) "
; Expanded expression: " GenExtendAlAx ()0 "
; Fused expression:    "( GenExtendAlAx )0 "
    call    _GenExtendAlAx
; }
    jmp     L1122
L1121:
; else
; if
; RPN'ized expression: "OpSz 2 == "
; Expanded expression: "(@4) *(2) 2 == "
; Fused expression:    "== *(@4) 2 IF! "
    mov     ax, [bp+4]
    cmp     ax, 2
    jne     L1135
; {
; if
; RPN'ized expression: "tok 12 == "
; Expanded expression: "(@8) *(2) 12 == "
; Fused expression:    "== *(@8) 12 IF! "
    mov     ax, [bp+8]
    cmp     ax, 12
    jne     L1137
; RPN'ized expression: "( L1139 printf ) "
; Expanded expression: " L1139  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1139:
    db  "    inc     word [",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1139 , printf )2 "
    push    L1139
    call    _printf
    sub     sp, -2
    jmp     L1138
L1137:
; else
; RPN'ized expression: "( L1141 printf ) "
; Expanded expression: " L1141  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1141:
    db  "    dec     word [",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1141 , printf )2 "
    push    L1141
    call    _printf
    sub     sp, -2
L1138:
; RPN'ized expression: "( Label GenPrintLabel ) "
; Expanded expression: " (@6) *(2)  GenPrintLabel ()2 "
; Fused expression:    "( *(2) (@6) , GenPrintLabel )2 "
    push    word [bp+6]
    call    _GenPrintLabel
    sub     sp, -2
; RPN'ized expression: "( L1143 printf ) "
; Expanded expression: " L1143  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1143:
    db  "]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1143 , printf )2 "
    push    L1143
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( L1145 printf ) "
; Expanded expression: " L1145  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1145:
    db  "    mov     ax, [",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1145 , printf )2 "
    push    L1145
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( Label GenPrintLabel ) "
; Expanded expression: " (@6) *(2)  GenPrintLabel ()2 "
; Fused expression:    "( *(2) (@6) , GenPrintLabel )2 "
    push    word [bp+6]
    call    _GenPrintLabel
    sub     sp, -2
; RPN'ized expression: "( L1147 printf ) "
; Expanded expression: " L1147  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1147:
    db  "]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1147 , printf )2 "
    push    L1147
    call    _printf
    sub     sp, -2
; }
L1135:
L1122:
L1120:
    leave
    ret
; SEGMENT _TEXT
; glb GenIncDecLocal : (
; prm     OpSz : int
; prm     Ofs : int
; prm     tok : int
;     ) void
SEGMENT _TEXT
    global  _GenIncDecLocal
_GenIncDecLocal:
    push    bp
    mov     bp, sp
; loc     OpSz : (@4): int
; loc     Ofs : (@6): int
; loc     tok : (@8): int
; if
; RPN'ized expression: "OpSz 1 == "
; Expanded expression: "(@4) *(2) 1 == "
; Fused expression:    "== *(@4) 1 IF! "
    mov     ax, [bp+4]
    cmp     ax, 1
    jne     L1150
; {
; if
; RPN'ized expression: "tok 12 == "
; Expanded expression: "(@8) *(2) 12 == "
; Fused expression:    "== *(@8) 12 IF! "
    mov     ax, [bp+8]
    cmp     ax, 12
    jne     L1152
; RPN'ized expression: "( Ofs , L1154 printf ) "
; Expanded expression: " (@6) *(2)  L1154  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1154:
    db  "    inc     byte [bp%+d]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@6) , L1154 , printf )4 "
    push    word [bp+6]
    push    L1154
    call    _printf
    sub     sp, -4
    jmp     L1153
L1152:
; else
; RPN'ized expression: "( Ofs , L1156 printf ) "
; Expanded expression: " (@6) *(2)  L1156  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1156:
    db  "    dec     byte [bp%+d]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@6) , L1156 , printf )4 "
    push    word [bp+6]
    push    L1156
    call    _printf
    sub     sp, -4
L1153:
; RPN'ized expression: "( Ofs , L1158 printf ) "
; Expanded expression: " (@6) *(2)  L1158  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1158:
    db  "    mov     al, [bp%+d]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@6) , L1158 , printf )4 "
    push    word [bp+6]
    push    L1158
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( GenExtendAlAx ) "
; Expanded expression: " GenExtendAlAx ()0 "
; Fused expression:    "( GenExtendAlAx )0 "
    call    _GenExtendAlAx
; }
    jmp     L1151
L1150:
; else
; if
; RPN'ized expression: "OpSz 2 == "
; Expanded expression: "(@4) *(2) 2 == "
; Fused expression:    "== *(@4) 2 IF! "
    mov     ax, [bp+4]
    cmp     ax, 2
    jne     L1160
; {
; if
; RPN'ized expression: "tok 12 == "
; Expanded expression: "(@8) *(2) 12 == "
; Fused expression:    "== *(@8) 12 IF! "
    mov     ax, [bp+8]
    cmp     ax, 12
    jne     L1162
; RPN'ized expression: "( Ofs , L1164 printf ) "
; Expanded expression: " (@6) *(2)  L1164  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1164:
    db  "    inc     word [bp%+d]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@6) , L1164 , printf )4 "
    push    word [bp+6]
    push    L1164
    call    _printf
    sub     sp, -4
    jmp     L1163
L1162:
; else
; RPN'ized expression: "( Ofs , L1166 printf ) "
; Expanded expression: " (@6) *(2)  L1166  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1166:
    db  "    dec     word [bp%+d]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@6) , L1166 , printf )4 "
    push    word [bp+6]
    push    L1166
    call    _printf
    sub     sp, -4
L1163:
; RPN'ized expression: "( Ofs , L1168 printf ) "
; Expanded expression: " (@6) *(2)  L1168  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1168:
    db  "    mov     ax, [bp%+d]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@6) , L1168 , printf )4 "
    push    word [bp+6]
    push    L1168
    call    _printf
    sub     sp, -4
; }
L1160:
L1151:
L1149:
    leave
    ret
; SEGMENT _TEXT
; glb GenIncDecIndirect : (
; prm     OpSz : int
; prm     tok : int
;     ) void
SEGMENT _TEXT
    global  _GenIncDecIndirect
_GenIncDecIndirect:
    push    bp
    mov     bp, sp
; loc     OpSz : (@4): int
; loc     tok : (@6): int
; RPN'ized expression: "( L1171 printf ) "
; Expanded expression: " L1171  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1171:
    db  "    mov     bx, ax",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1171 , printf )2 "
    push    L1171
    call    _printf
    sub     sp, -2
; if
; RPN'ized expression: "OpSz 1 == "
; Expanded expression: "(@4) *(2) 1 == "
; Fused expression:    "== *(@4) 1 IF! "
    mov     ax, [bp+4]
    cmp     ax, 1
    jne     L1173
; {
; if
; RPN'ized expression: "tok 12 == "
; Expanded expression: "(@6) *(2) 12 == "
; Fused expression:    "== *(@6) 12 IF! "
    mov     ax, [bp+6]
    cmp     ax, 12
    jne     L1175
; RPN'ized expression: "( L1177 printf ) "
; Expanded expression: " L1177  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1177:
    db  "    inc     byte [bx]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1177 , printf )2 "
    push    L1177
    call    _printf
    sub     sp, -2
    jmp     L1176
L1175:
; else
; RPN'ized expression: "( L1179 printf ) "
; Expanded expression: " L1179  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1179:
    db  "    dec     byte [bx]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1179 , printf )2 "
    push    L1179
    call    _printf
    sub     sp, -2
L1176:
; RPN'ized expression: "( L1181 printf ) "
; Expanded expression: " L1181  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1181:
    db  "    mov     al, [bx]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1181 , printf )2 "
    push    L1181
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( GenExtendAlAx ) "
; Expanded expression: " GenExtendAlAx ()0 "
; Fused expression:    "( GenExtendAlAx )0 "
    call    _GenExtendAlAx
; }
    jmp     L1174
L1173:
; else
; if
; RPN'ized expression: "OpSz 2 == "
; Expanded expression: "(@4) *(2) 2 == "
; Fused expression:    "== *(@4) 2 IF! "
    mov     ax, [bp+4]
    cmp     ax, 2
    jne     L1183
; {
; if
; RPN'ized expression: "tok 12 == "
; Expanded expression: "(@6) *(2) 12 == "
; Fused expression:    "== *(@6) 12 IF! "
    mov     ax, [bp+6]
    cmp     ax, 12
    jne     L1185
; RPN'ized expression: "( L1187 printf ) "
; Expanded expression: " L1187  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1187:
    db  "    inc     word [bx]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1187 , printf )2 "
    push    L1187
    call    _printf
    sub     sp, -2
    jmp     L1186
L1185:
; else
; RPN'ized expression: "( L1189 printf ) "
; Expanded expression: " L1189  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1189:
    db  "    dec     word [bx]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1189 , printf )2 "
    push    L1189
    call    _printf
    sub     sp, -2
L1186:
; RPN'ized expression: "( L1191 printf ) "
; Expanded expression: " L1191  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1191:
    db  "    mov     ax, [bx]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1191 , printf )2 "
    push    L1191
    call    _printf
    sub     sp, -2
; }
L1183:
L1174:
L1170:
    leave
    ret
; SEGMENT _TEXT
; glb GenPostIncDecIdent : (
; prm     OpSz : int
; prm     Label : * char
; prm     tok : int
;     ) void
SEGMENT _TEXT
    global  _GenPostIncDecIdent
_GenPostIncDecIdent:
    push    bp
    mov     bp, sp
; loc     OpSz : (@4): int
; loc     Label : (@6): * char
; loc     tok : (@8): int
; if
; RPN'ized expression: "OpSz 1 == "
; Expanded expression: "(@4) *(2) 1 == "
; Fused expression:    "== *(@4) 1 IF! "
    mov     ax, [bp+4]
    cmp     ax, 1
    jne     L1194
; {
; RPN'ized expression: "( L1196 printf ) "
; Expanded expression: " L1196  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1196:
    db  "    mov     al, [",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1196 , printf )2 "
    push    L1196
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( Label GenPrintLabel ) "
; Expanded expression: " (@6) *(2)  GenPrintLabel ()2 "
; Fused expression:    "( *(2) (@6) , GenPrintLabel )2 "
    push    word [bp+6]
    call    _GenPrintLabel
    sub     sp, -2
; RPN'ized expression: "( L1198 printf ) "
; Expanded expression: " L1198  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1198:
    db  "]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1198 , printf )2 "
    push    L1198
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( GenExtendAlAx ) "
; Expanded expression: " GenExtendAlAx ()0 "
; Fused expression:    "( GenExtendAlAx )0 "
    call    _GenExtendAlAx
; if
; RPN'ized expression: "tok 81 == "
; Expanded expression: "(@8) *(2) 81 == "
; Fused expression:    "== *(@8) 81 IF! "
    mov     ax, [bp+8]
    cmp     ax, 81
    jne     L1200
; RPN'ized expression: "( L1202 printf ) "
; Expanded expression: " L1202  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1202:
    db  "    inc     byte [",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1202 , printf )2 "
    push    L1202
    call    _printf
    sub     sp, -2
    jmp     L1201
L1200:
; else
; RPN'ized expression: "( L1204 printf ) "
; Expanded expression: " L1204  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1204:
    db  "    dec     byte [",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1204 , printf )2 "
    push    L1204
    call    _printf
    sub     sp, -2
L1201:
; RPN'ized expression: "( Label GenPrintLabel ) "
; Expanded expression: " (@6) *(2)  GenPrintLabel ()2 "
; Fused expression:    "( *(2) (@6) , GenPrintLabel )2 "
    push    word [bp+6]
    call    _GenPrintLabel
    sub     sp, -2
; RPN'ized expression: "( L1206 printf ) "
; Expanded expression: " L1206  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1206:
    db  "]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1206 , printf )2 "
    push    L1206
    call    _printf
    sub     sp, -2
; }
    jmp     L1195
L1194:
; else
; if
; RPN'ized expression: "OpSz 2 == "
; Expanded expression: "(@4) *(2) 2 == "
; Fused expression:    "== *(@4) 2 IF! "
    mov     ax, [bp+4]
    cmp     ax, 2
    jne     L1208
; {
; RPN'ized expression: "( L1210 printf ) "
; Expanded expression: " L1210  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1210:
    db  "    mov     ax, [",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1210 , printf )2 "
    push    L1210
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( Label GenPrintLabel ) "
; Expanded expression: " (@6) *(2)  GenPrintLabel ()2 "
; Fused expression:    "( *(2) (@6) , GenPrintLabel )2 "
    push    word [bp+6]
    call    _GenPrintLabel
    sub     sp, -2
; RPN'ized expression: "( L1212 printf ) "
; Expanded expression: " L1212  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1212:
    db  "]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1212 , printf )2 "
    push    L1212
    call    _printf
    sub     sp, -2
; if
; RPN'ized expression: "tok 81 == "
; Expanded expression: "(@8) *(2) 81 == "
; Fused expression:    "== *(@8) 81 IF! "
    mov     ax, [bp+8]
    cmp     ax, 81
    jne     L1214
; RPN'ized expression: "( L1216 printf ) "
; Expanded expression: " L1216  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1216:
    db  "    inc     word [",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1216 , printf )2 "
    push    L1216
    call    _printf
    sub     sp, -2
    jmp     L1215
L1214:
; else
; RPN'ized expression: "( L1218 printf ) "
; Expanded expression: " L1218  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1218:
    db  "    dec     word [",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1218 , printf )2 "
    push    L1218
    call    _printf
    sub     sp, -2
L1215:
; RPN'ized expression: "( Label GenPrintLabel ) "
; Expanded expression: " (@6) *(2)  GenPrintLabel ()2 "
; Fused expression:    "( *(2) (@6) , GenPrintLabel )2 "
    push    word [bp+6]
    call    _GenPrintLabel
    sub     sp, -2
; RPN'ized expression: "( L1220 printf ) "
; Expanded expression: " L1220  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1220:
    db  "]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1220 , printf )2 "
    push    L1220
    call    _printf
    sub     sp, -2
; }
L1208:
L1195:
L1193:
    leave
    ret
; SEGMENT _TEXT
; glb GenPostIncDecLocal : (
; prm     OpSz : int
; prm     Ofs : int
; prm     tok : int
;     ) void
SEGMENT _TEXT
    global  _GenPostIncDecLocal
_GenPostIncDecLocal:
    push    bp
    mov     bp, sp
; loc     OpSz : (@4): int
; loc     Ofs : (@6): int
; loc     tok : (@8): int
; if
; RPN'ized expression: "OpSz 1 == "
; Expanded expression: "(@4) *(2) 1 == "
; Fused expression:    "== *(@4) 1 IF! "
    mov     ax, [bp+4]
    cmp     ax, 1
    jne     L1223
; {
; RPN'ized expression: "( Ofs , L1225 printf ) "
; Expanded expression: " (@6) *(2)  L1225  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1225:
    db  "    mov     al, [bp%+d]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@6) , L1225 , printf )4 "
    push    word [bp+6]
    push    L1225
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( GenExtendAlAx ) "
; Expanded expression: " GenExtendAlAx ()0 "
; Fused expression:    "( GenExtendAlAx )0 "
    call    _GenExtendAlAx
; if
; RPN'ized expression: "tok 81 == "
; Expanded expression: "(@8) *(2) 81 == "
; Fused expression:    "== *(@8) 81 IF! "
    mov     ax, [bp+8]
    cmp     ax, 81
    jne     L1227
; RPN'ized expression: "( Ofs , L1229 printf ) "
; Expanded expression: " (@6) *(2)  L1229  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1229:
    db  "    inc     byte [bp%+d]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@6) , L1229 , printf )4 "
    push    word [bp+6]
    push    L1229
    call    _printf
    sub     sp, -4
    jmp     L1228
L1227:
; else
; RPN'ized expression: "( Ofs , L1231 printf ) "
; Expanded expression: " (@6) *(2)  L1231  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1231:
    db  "    dec     byte [bp%+d]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@6) , L1231 , printf )4 "
    push    word [bp+6]
    push    L1231
    call    _printf
    sub     sp, -4
L1228:
; }
    jmp     L1224
L1223:
; else
; if
; RPN'ized expression: "OpSz 2 == "
; Expanded expression: "(@4) *(2) 2 == "
; Fused expression:    "== *(@4) 2 IF! "
    mov     ax, [bp+4]
    cmp     ax, 2
    jne     L1233
; {
; RPN'ized expression: "( Ofs , L1235 printf ) "
; Expanded expression: " (@6) *(2)  L1235  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1235:
    db  "    mov     ax, [bp%+d]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@6) , L1235 , printf )4 "
    push    word [bp+6]
    push    L1235
    call    _printf
    sub     sp, -4
; if
; RPN'ized expression: "tok 81 == "
; Expanded expression: "(@8) *(2) 81 == "
; Fused expression:    "== *(@8) 81 IF! "
    mov     ax, [bp+8]
    cmp     ax, 81
    jne     L1237
; RPN'ized expression: "( Ofs , L1239 printf ) "
; Expanded expression: " (@6) *(2)  L1239  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1239:
    db  "    inc     word [bp%+d]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@6) , L1239 , printf )4 "
    push    word [bp+6]
    push    L1239
    call    _printf
    sub     sp, -4
    jmp     L1238
L1237:
; else
; RPN'ized expression: "( Ofs , L1241 printf ) "
; Expanded expression: " (@6) *(2)  L1241  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1241:
    db  "    dec     word [bp%+d]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@6) , L1241 , printf )4 "
    push    word [bp+6]
    push    L1241
    call    _printf
    sub     sp, -4
L1238:
; }
L1233:
L1224:
L1222:
    leave
    ret
; SEGMENT _TEXT
; glb GenPostIncDecIndirect : (
; prm     OpSz : int
; prm     tok : int
;     ) void
SEGMENT _TEXT
    global  _GenPostIncDecIndirect
_GenPostIncDecIndirect:
    push    bp
    mov     bp, sp
; loc     OpSz : (@4): int
; loc     tok : (@6): int
; RPN'ized expression: "( L1244 printf ) "
; Expanded expression: " L1244  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1244:
    db  "    mov     bx, ax",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1244 , printf )2 "
    push    L1244
    call    _printf
    sub     sp, -2
; if
; RPN'ized expression: "OpSz 1 == "
; Expanded expression: "(@4) *(2) 1 == "
; Fused expression:    "== *(@4) 1 IF! "
    mov     ax, [bp+4]
    cmp     ax, 1
    jne     L1246
; {
; RPN'ized expression: "( L1248 printf ) "
; Expanded expression: " L1248  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1248:
    db  "    mov     al, [bx]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1248 , printf )2 "
    push    L1248
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( GenExtendAlAx ) "
; Expanded expression: " GenExtendAlAx ()0 "
; Fused expression:    "( GenExtendAlAx )0 "
    call    _GenExtendAlAx
; if
; RPN'ized expression: "tok 81 == "
; Expanded expression: "(@6) *(2) 81 == "
; Fused expression:    "== *(@6) 81 IF! "
    mov     ax, [bp+6]
    cmp     ax, 81
    jne     L1250
; RPN'ized expression: "( L1252 printf ) "
; Expanded expression: " L1252  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1252:
    db  "    inc     byte [bx]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1252 , printf )2 "
    push    L1252
    call    _printf
    sub     sp, -2
    jmp     L1251
L1250:
; else
; RPN'ized expression: "( L1254 printf ) "
; Expanded expression: " L1254  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1254:
    db  "    dec     byte [bx]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1254 , printf )2 "
    push    L1254
    call    _printf
    sub     sp, -2
L1251:
; }
    jmp     L1247
L1246:
; else
; if
; RPN'ized expression: "OpSz 2 == "
; Expanded expression: "(@4) *(2) 2 == "
; Fused expression:    "== *(@4) 2 IF! "
    mov     ax, [bp+4]
    cmp     ax, 2
    jne     L1256
; {
; RPN'ized expression: "( L1258 printf ) "
; Expanded expression: " L1258  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1258:
    db  "    mov     ax, [bx]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1258 , printf )2 "
    push    L1258
    call    _printf
    sub     sp, -2
; if
; RPN'ized expression: "tok 81 == "
; Expanded expression: "(@6) *(2) 81 == "
; Fused expression:    "== *(@6) 81 IF! "
    mov     ax, [bp+6]
    cmp     ax, 81
    jne     L1260
; RPN'ized expression: "( L1262 printf ) "
; Expanded expression: " L1262  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1262:
    db  "    inc     word [bx]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1262 , printf )2 "
    push    L1262
    call    _printf
    sub     sp, -2
    jmp     L1261
L1260:
; else
; RPN'ized expression: "( L1264 printf ) "
; Expanded expression: " L1264  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1264:
    db  "    dec     word [bx]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1264 , printf )2 "
    push    L1264
    call    _printf
    sub     sp, -2
L1261:
; }
L1256:
L1247:
L1243:
    leave
    ret
; SEGMENT _TEXT
; glb GenPostAddSubIdent : (
; prm     OpSz : int
; prm     val : int
; prm     Label : * char
; prm     tok : int
;     ) void
SEGMENT _TEXT
    global  _GenPostAddSubIdent
_GenPostAddSubIdent:
    push    bp
    mov     bp, sp
; loc     OpSz : (@4): int
; loc     val : (@6): int
; loc     Label : (@8): * char
; loc     tok : (@10): int
; if
; RPN'ized expression: "OpSz 1 == "
; Expanded expression: "(@4) *(2) 1 == "
; Fused expression:    "== *(@4) 1 IF! "
    mov     ax, [bp+4]
    cmp     ax, 1
    jne     L1267
; {
; RPN'ized expression: "( L1269 printf ) "
; Expanded expression: " L1269  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1269:
    db  "    mov     al, [",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1269 , printf )2 "
    push    L1269
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( Label GenPrintLabel ) "
; Expanded expression: " (@8) *(2)  GenPrintLabel ()2 "
; Fused expression:    "( *(2) (@8) , GenPrintLabel )2 "
    push    word [bp+8]
    call    _GenPrintLabel
    sub     sp, -2
; RPN'ized expression: "( L1271 printf ) "
; Expanded expression: " L1271  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1271:
    db  "]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1271 , printf )2 "
    push    L1271
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( GenExtendAlAx ) "
; Expanded expression: " GenExtendAlAx ()0 "
; Fused expression:    "( GenExtendAlAx )0 "
    call    _GenExtendAlAx
; if
; RPN'ized expression: "tok 83 == "
; Expanded expression: "(@10) *(2) 83 == "
; Fused expression:    "== *(@10) 83 IF! "
    mov     ax, [bp+10]
    cmp     ax, 83
    jne     L1273
; RPN'ized expression: "( L1275 printf ) "
; Expanded expression: " L1275  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1275:
    db  "    add     byte [",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1275 , printf )2 "
    push    L1275
    call    _printf
    sub     sp, -2
    jmp     L1274
L1273:
; else
; RPN'ized expression: "( L1277 printf ) "
; Expanded expression: " L1277  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1277:
    db  "    sub     byte [",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1277 , printf )2 "
    push    L1277
    call    _printf
    sub     sp, -2
L1274:
; RPN'ized expression: "( Label GenPrintLabel ) "
; Expanded expression: " (@8) *(2)  GenPrintLabel ()2 "
; Fused expression:    "( *(2) (@8) , GenPrintLabel )2 "
    push    word [bp+8]
    call    _GenPrintLabel
    sub     sp, -2
; RPN'ized expression: "( val , L1279 printf ) "
; Expanded expression: " (@6) *(2)  L1279  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1279:
    db  "], %d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@6) , L1279 , printf )4 "
    push    word [bp+6]
    push    L1279
    call    _printf
    sub     sp, -4
; }
    jmp     L1268
L1267:
; else
; if
; RPN'ized expression: "OpSz 2 == "
; Expanded expression: "(@4) *(2) 2 == "
; Fused expression:    "== *(@4) 2 IF! "
    mov     ax, [bp+4]
    cmp     ax, 2
    jne     L1281
; {
; RPN'ized expression: "( L1283 printf ) "
; Expanded expression: " L1283  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1283:
    db  "    mov     ax, [",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1283 , printf )2 "
    push    L1283
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( Label GenPrintLabel ) "
; Expanded expression: " (@8) *(2)  GenPrintLabel ()2 "
; Fused expression:    "( *(2) (@8) , GenPrintLabel )2 "
    push    word [bp+8]
    call    _GenPrintLabel
    sub     sp, -2
; RPN'ized expression: "( L1285 printf ) "
; Expanded expression: " L1285  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1285:
    db  "]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1285 , printf )2 "
    push    L1285
    call    _printf
    sub     sp, -2
; if
; RPN'ized expression: "tok 83 == "
; Expanded expression: "(@10) *(2) 83 == "
; Fused expression:    "== *(@10) 83 IF! "
    mov     ax, [bp+10]
    cmp     ax, 83
    jne     L1287
; RPN'ized expression: "( L1289 printf ) "
; Expanded expression: " L1289  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1289:
    db  "    add     word [",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1289 , printf )2 "
    push    L1289
    call    _printf
    sub     sp, -2
    jmp     L1288
L1287:
; else
; RPN'ized expression: "( L1291 printf ) "
; Expanded expression: " L1291  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1291:
    db  "    sub     word [",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1291 , printf )2 "
    push    L1291
    call    _printf
    sub     sp, -2
L1288:
; RPN'ized expression: "( Label GenPrintLabel ) "
; Expanded expression: " (@8) *(2)  GenPrintLabel ()2 "
; Fused expression:    "( *(2) (@8) , GenPrintLabel )2 "
    push    word [bp+8]
    call    _GenPrintLabel
    sub     sp, -2
; RPN'ized expression: "( val , L1293 printf ) "
; Expanded expression: " (@6) *(2)  L1293  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1293:
    db  "], %d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@6) , L1293 , printf )4 "
    push    word [bp+6]
    push    L1293
    call    _printf
    sub     sp, -4
; }
L1281:
L1268:
L1266:
    leave
    ret
; SEGMENT _TEXT
; glb GenPostAddSubLocal : (
; prm     OpSz : int
; prm     val : int
; prm     Ofs : int
; prm     tok : int
;     ) void
SEGMENT _TEXT
    global  _GenPostAddSubLocal
_GenPostAddSubLocal:
    push    bp
    mov     bp, sp
; loc     OpSz : (@4): int
; loc     val : (@6): int
; loc     Ofs : (@8): int
; loc     tok : (@10): int
; if
; RPN'ized expression: "OpSz 1 == "
; Expanded expression: "(@4) *(2) 1 == "
; Fused expression:    "== *(@4) 1 IF! "
    mov     ax, [bp+4]
    cmp     ax, 1
    jne     L1296
; {
; RPN'ized expression: "( Ofs , L1298 printf ) "
; Expanded expression: " (@8) *(2)  L1298  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1298:
    db  "    mov     al, [bp%+d]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@8) , L1298 , printf )4 "
    push    word [bp+8]
    push    L1298
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( GenExtendAlAx ) "
; Expanded expression: " GenExtendAlAx ()0 "
; Fused expression:    "( GenExtendAlAx )0 "
    call    _GenExtendAlAx
; if
; RPN'ized expression: "tok 83 == "
; Expanded expression: "(@10) *(2) 83 == "
; Fused expression:    "== *(@10) 83 IF! "
    mov     ax, [bp+10]
    cmp     ax, 83
    jne     L1300
; RPN'ized expression: "( val , Ofs , L1302 printf ) "
; Expanded expression: " (@6) *(2)  (@8) *(2)  L1302  printf ()6 "
; SEGMENT _TEXT
SEGMENT _DATA
L1302:
    db  "    add     byte [bp%+d], %d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@6) , *(2) (@8) , L1302 , printf )6 "
    push    word [bp+6]
    push    word [bp+8]
    push    L1302
    call    _printf
    sub     sp, -6
    jmp     L1301
L1300:
; else
; RPN'ized expression: "( val , Ofs , L1304 printf ) "
; Expanded expression: " (@6) *(2)  (@8) *(2)  L1304  printf ()6 "
; SEGMENT _TEXT
SEGMENT _DATA
L1304:
    db  "    sub     byte [bp%+d], %d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@6) , *(2) (@8) , L1304 , printf )6 "
    push    word [bp+6]
    push    word [bp+8]
    push    L1304
    call    _printf
    sub     sp, -6
L1301:
; }
    jmp     L1297
L1296:
; else
; if
; RPN'ized expression: "OpSz 2 == "
; Expanded expression: "(@4) *(2) 2 == "
; Fused expression:    "== *(@4) 2 IF! "
    mov     ax, [bp+4]
    cmp     ax, 2
    jne     L1306
; {
; RPN'ized expression: "( Ofs , L1308 printf ) "
; Expanded expression: " (@8) *(2)  L1308  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1308:
    db  "    mov     ax, [bp%+d]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@8) , L1308 , printf )4 "
    push    word [bp+8]
    push    L1308
    call    _printf
    sub     sp, -4
; if
; RPN'ized expression: "tok 83 == "
; Expanded expression: "(@10) *(2) 83 == "
; Fused expression:    "== *(@10) 83 IF! "
    mov     ax, [bp+10]
    cmp     ax, 83
    jne     L1310
; RPN'ized expression: "( val , Ofs , L1312 printf ) "
; Expanded expression: " (@6) *(2)  (@8) *(2)  L1312  printf ()6 "
; SEGMENT _TEXT
SEGMENT _DATA
L1312:
    db  "    add     word [bp%+d], %d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@6) , *(2) (@8) , L1312 , printf )6 "
    push    word [bp+6]
    push    word [bp+8]
    push    L1312
    call    _printf
    sub     sp, -6
    jmp     L1311
L1310:
; else
; RPN'ized expression: "( val , Ofs , L1314 printf ) "
; Expanded expression: " (@6) *(2)  (@8) *(2)  L1314  printf ()6 "
; SEGMENT _TEXT
SEGMENT _DATA
L1314:
    db  "    sub     word [bp%+d], %d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@6) , *(2) (@8) , L1314 , printf )6 "
    push    word [bp+6]
    push    word [bp+8]
    push    L1314
    call    _printf
    sub     sp, -6
L1311:
; }
L1306:
L1297:
L1295:
    leave
    ret
; SEGMENT _TEXT
; glb GenPostAddSubIndirect : (
; prm     OpSz : int
; prm     val : int
; prm     tok : int
;     ) void
SEGMENT _TEXT
    global  _GenPostAddSubIndirect
_GenPostAddSubIndirect:
    push    bp
    mov     bp, sp
; loc     OpSz : (@4): int
; loc     val : (@6): int
; loc     tok : (@8): int
; RPN'ized expression: "( L1317 printf ) "
; Expanded expression: " L1317  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1317:
    db  "    mov     bx, ax",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1317 , printf )2 "
    push    L1317
    call    _printf
    sub     sp, -2
; if
; RPN'ized expression: "OpSz 1 == "
; Expanded expression: "(@4) *(2) 1 == "
; Fused expression:    "== *(@4) 1 IF! "
    mov     ax, [bp+4]
    cmp     ax, 1
    jne     L1319
; {
; RPN'ized expression: "( L1321 printf ) "
; Expanded expression: " L1321  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1321:
    db  "    mov     al, [bx]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1321 , printf )2 "
    push    L1321
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( GenExtendAlAx ) "
; Expanded expression: " GenExtendAlAx ()0 "
; Fused expression:    "( GenExtendAlAx )0 "
    call    _GenExtendAlAx
; if
; RPN'ized expression: "tok 83 == "
; Expanded expression: "(@8) *(2) 83 == "
; Fused expression:    "== *(@8) 83 IF! "
    mov     ax, [bp+8]
    cmp     ax, 83
    jne     L1323
; RPN'ized expression: "( val , L1325 printf ) "
; Expanded expression: " (@6) *(2)  L1325  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1325:
    db  "    add     byte [bx], %d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@6) , L1325 , printf )4 "
    push    word [bp+6]
    push    L1325
    call    _printf
    sub     sp, -4
    jmp     L1324
L1323:
; else
; RPN'ized expression: "( val , L1327 printf ) "
; Expanded expression: " (@6) *(2)  L1327  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1327:
    db  "    sub     byte [bx], %d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@6) , L1327 , printf )4 "
    push    word [bp+6]
    push    L1327
    call    _printf
    sub     sp, -4
L1324:
; }
    jmp     L1320
L1319:
; else
; if
; RPN'ized expression: "OpSz 2 == "
; Expanded expression: "(@4) *(2) 2 == "
; Fused expression:    "== *(@4) 2 IF! "
    mov     ax, [bp+4]
    cmp     ax, 2
    jne     L1329
; {
; RPN'ized expression: "( L1331 printf ) "
; Expanded expression: " L1331  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1331:
    db  "    mov     ax, [bx]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1331 , printf )2 "
    push    L1331
    call    _printf
    sub     sp, -2
; if
; RPN'ized expression: "tok 83 == "
; Expanded expression: "(@8) *(2) 83 == "
; Fused expression:    "== *(@8) 83 IF! "
    mov     ax, [bp+8]
    cmp     ax, 83
    jne     L1333
; RPN'ized expression: "( val , L1335 printf ) "
; Expanded expression: " (@6) *(2)  L1335  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1335:
    db  "    add     word [bx], %d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@6) , L1335 , printf )4 "
    push    word [bp+6]
    push    L1335
    call    _printf
    sub     sp, -4
    jmp     L1334
L1333:
; else
; RPN'ized expression: "( val , L1337 printf ) "
; Expanded expression: " (@6) *(2)  L1337  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1337:
    db  "    sub     word [bx], %d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@6) , L1337 , printf )4 "
    push    word [bp+6]
    push    L1337
    call    _printf
    sub     sp, -4
L1334:
; }
L1329:
L1320:
L1316:
    leave
    ret
; SEGMENT _TEXT
; glb GetOperandInfo : (
; prm     idx : int
; prm     lvalSize : int
; prm     val : * int
; prm     size : * int
; prm     delDeref : * int
;     ) int
SEGMENT _TEXT
    global  _GetOperandInfo
_GetOperandInfo:
    push    bp
    mov     bp, sp
; loc     idx : (@4): int
; loc     lvalSize : (@6): int
; loc     val : (@8): * int
; loc     size : (@10): * int
; loc     delDeref : (@12): * int
; loc     idx0 : (@-2): int
    sub     sp, 2
; =
; RPN'ized expression: "idx "
; Expanded expression: "(@4) *(2) "
; Fused expression:    "=(34) *(@-2) *(@4) "
    mov     ax, [bp+4]
    mov     [bp-2], ax
; RPN'ized expression: "delDeref *u 0 = "
; Expanded expression: "(@12) *(2) 0 =(2) "
; Fused expression:    "*(2) (@12) =(34) *ax 0 "
    mov     ax, [bp+12]
    mov     bx, ax
    mov     ax, 0
    mov     [bx], ax
; while
; RPN'ized expression: "stack idx + *u 0 + *u 256 >= stack idx + *u 0 + *u 262 <= && "
; Expanded expression: "stack (@4) *(2) 4 * + 0 + *(2) 256 >= _Bool [sh&&->1342] stack (@4) *(2) 4 * + 0 + *(2) 262 <= _Bool &&[1342] "
L1340:
; Fused expression:    "* *(@4) 4 + stack ax + ax 0 >= *ax 256 _Bool [sh&&->1342] * *(@4) 4 + stack ax + ax 0 <= *ax 262 _Bool &&[1342] "
    mov     ax, [bp+4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 256
    setge   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L1342
    mov     ax, [bp+4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 262
    setle   al
    cbw
    test    ax, ax
    setnz   al
    cbw
L1342:
; JumpIfZero
    test    ax, ax
    jz      L1341
; RPN'ized expression: "idx --p "
; Expanded expression: "(@4) --p(2) "
; Fused expression:    "--p(2) *(@4) "
    mov     ax, [bp+4]
    dec     word [bp+4]
    jmp     L1340
L1341:
; if
; RPN'ized expression: "stack idx + *u 0 + *u 78 == "
; Expanded expression: "stack (@4) *(2) 4 * + 0 + *(2) 78 == "
; Fused expression:    "* *(@4) 4 + stack ax + ax 0 == *ax 78 IF! "
    mov     ax, [bp+4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 78
    jne     L1343
; {
; if
; RPN'ized expression: "lvalSize "
; Expanded expression: "(@6) *(2) "
; Fused expression:    "*(2) (@6) "
    mov     ax, [bp+6]
; JumpIfZero
    test    ax, ax
    jz      L1345
; {
; RPN'ized expression: "size *u lvalSize = "
; Expanded expression: "(@10) *(2) (@6) *(2) =(2) "
; Fused expression:    "*(2) (@10) =(34) *ax *(@6) "
    mov     ax, [bp+10]
    mov     bx, ax
    mov     ax, [bp+6]
    mov     [bx], ax
; RPN'ized expression: "val *u 0 = "
; Expanded expression: "(@8) *(2) 0 =(2) "
; Fused expression:    "*(2) (@8) =(34) *ax 0 "
    mov     ax, [bp+8]
    mov     bx, ax
    mov     ax, 0
    mov     [bx], ax
; return
; RPN'ized expression: "262 "
; Expanded expression: "262 "
; Expression value: 262
; Fused expression:    "262 "
    mov     ax, 262
    jmp     L1339
; }
L1345:
; RPN'ized expression: "size *u stack idx + *u 1 + *u = "
; Expanded expression: "(@10) *(2) stack (@4) *(2) 4 * + 2 + *(2) =(2) "
; Fused expression:    "*(2) (@10) push-ax * *(@4) 4 + stack ax + ax 2 =(34) **sp *ax "
    mov     ax, [bp+10]
    push    ax
    mov     ax, [bp+4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bx]
    pop     bx
    mov     [bx], ax
; RPN'ized expression: "delDeref *u 1 = "
; Expanded expression: "(@12) *(2) 1 =(2) "
; Fused expression:    "*(2) (@12) =(34) *ax 1 "
    mov     ax, [bp+12]
    mov     bx, ax
    mov     ax, 1
    mov     [bx], ax
; RPN'ized expression: "val *u stack idx 1 + + *u 1 + *u = "
; Expanded expression: "(@8) *(2) stack (@4) *(2) 1 + 4 * + 2 + *(2) =(2) "
; Fused expression:    "*(2) (@8) push-ax + *(@4) 1 * ax 4 + stack ax + ax 2 =(34) **sp *ax "
    mov     ax, [bp+8]
    push    ax
    mov     ax, [bp+4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bx]
    pop     bx
    mov     [bx], ax
; return
; RPN'ized expression: "stack idx 1 + + *u 0 + *u 260 + 257 - "
; Expanded expression: "stack (@4) *(2) 1 + 4 * + 0 + *(2) 260 + 257 - "
; Fused expression:    "+ *(@4) 1 * ax 4 + stack ax + ax 0 + *ax 260 - ax 257 "
    mov     ax, [bp+4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    add     ax, 260
    sub     ax, 257
    jmp     L1339
; }
L1343:
; RPN'ized expression: "idx idx0 = "
; Expanded expression: "(@4) (@-2) *(2) =(2) "
; Fused expression:    "=(34) *(@4) *(@-2) "
    mov     ax, [bp-2]
    mov     [bp+4], ax
; if
; RPN'ized expression: "lvalSize "
; Expanded expression: "(@6) *(2) "
; Fused expression:    "*(2) (@6) "
    mov     ax, [bp+6]
; JumpIfZero
    test    ax, ax
    jz      L1347
; {
; RPN'ized expression: "size *u lvalSize = "
; Expanded expression: "(@10) *(2) (@6) *(2) =(2) "
; Fused expression:    "*(2) (@10) =(34) *ax *(@6) "
    mov     ax, [bp+10]
    mov     bx, ax
    mov     ax, [bp+6]
    mov     [bx], ax
; RPN'ized expression: "val *u stack idx + *u 1 + *u = "
; Expanded expression: "(@8) *(2) stack (@4) *(2) 4 * + 2 + *(2) =(2) "
; Fused expression:    "*(2) (@8) push-ax * *(@4) 4 + stack ax + ax 2 =(34) **sp *ax "
    mov     ax, [bp+8]
    push    ax
    mov     ax, [bp+4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bx]
    pop     bx
    mov     [bx], ax
; switch
; RPN'ized expression: "stack idx + *u 0 + *u "
; Expanded expression: "stack (@4) *(2) 4 * + 0 + *(2) "
; Fused expression:    "* *(@4) 4 + stack ax + ax 0 *(2) ax "
    mov     ax, [bp+4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    jmp     L1351
; {
; case
; RPN'ized expression: "16 "
; Expanded expression: "16 "
; Expression value: 16
    jmp     L1352
L1351:
    cmp     ax, 16
    jne     L1353
L1352:
; return
; RPN'ized expression: "260 "
; Expanded expression: "260 "
; Expression value: 260
; Fused expression:    "260 "
    mov     ax, 260
    jmp     L1339
; case
; RPN'ized expression: "89 "
; Expanded expression: "89 "
; Expression value: 89
    jmp     L1354
L1353:
    cmp     ax, 89
    jne     L1355
L1354:
; return
; RPN'ized expression: "261 "
; Expanded expression: "261 "
; Expression value: 261
; Fused expression:    "261 "
    mov     ax, 261
    jmp     L1339
; default
L1350:
; RPN'ized expression: "val *u 0 = "
; Expanded expression: "(@8) *(2) 0 =(2) "
; Fused expression:    "*(2) (@8) =(34) *ax 0 "
    mov     ax, [bp+8]
    mov     bx, ax
    mov     ax, 0
    mov     [bx], ax
; return
; RPN'ized expression: "262 "
; Expanded expression: "262 "
; Expression value: 262
; Fused expression:    "262 "
    mov     ax, 262
    jmp     L1339
; }
    jmp     L1349
L1355:
    jmp     L1350
L1349:
; }
L1347:
; RPN'ized expression: "size *u SizeOfWord = "
; Expanded expression: "(@10) *(2) SizeOfWord *(2) =(2) "
; Fused expression:    "*(2) (@10) =(34) *ax *SizeOfWord "
    mov     ax, [bp+10]
    mov     bx, ax
    mov     ax, [_SizeOfWord]
    mov     [bx], ax
; RPN'ized expression: "val *u stack idx + *u 1 + *u = "
; Expanded expression: "(@8) *(2) stack (@4) *(2) 4 * + 2 + *(2) =(2) "
; Fused expression:    "*(2) (@8) push-ax * *(@4) 4 + stack ax + ax 2 =(34) **sp *ax "
    mov     ax, [bp+8]
    push    ax
    mov     ax, [bp+4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bx]
    pop     bx
    mov     [bx], ax
; switch
; RPN'ized expression: "stack idx + *u 0 + *u "
; Expanded expression: "stack (@4) *(2) 4 * + 0 + *(2) "
; Fused expression:    "* *(@4) 4 + stack ax + ax 0 *(2) ax "
    mov     ax, [bp+4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    jmp     L1359
; {
; case
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
    jmp     L1360
L1359:
    cmp     ax, 1
    jne     L1361
L1360:
; case
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
    jmp     L1362
L1361:
    cmp     ax, 2
    jne     L1363
L1362:
; return
; RPN'ized expression: "256 "
; Expanded expression: "256 "
; Expression value: 256
; Fused expression:    "256 "
    mov     ax, 256
    jmp     L1339
; case
; RPN'ized expression: "16 "
; Expanded expression: "16 "
; Expression value: 16
    jmp     L1364
L1363:
    cmp     ax, 16
    jne     L1365
L1364:
; return
; RPN'ized expression: "257 "
; Expanded expression: "257 "
; Expression value: 257
; Fused expression:    "257 "
    mov     ax, 257
    jmp     L1339
; case
; RPN'ized expression: "89 "
; Expanded expression: "89 "
; Expression value: 89
    jmp     L1366
L1365:
    cmp     ax, 89
    jne     L1367
L1366:
; return
; RPN'ized expression: "258 "
; Expanded expression: "258 "
; Expression value: 258
; Fused expression:    "258 "
    mov     ax, 258
    jmp     L1339
; default
L1358:
; RPN'ized expression: "val *u 0 = "
; Expanded expression: "(@8) *(2) 0 =(2) "
; Fused expression:    "*(2) (@8) =(34) *ax 0 "
    mov     ax, [bp+8]
    mov     bx, ax
    mov     ax, 0
    mov     [bx], ax
; return
; RPN'ized expression: "259 "
; Expanded expression: "259 "
; Expression value: 259
; Fused expression:    "259 "
    mov     ax, 259
    jmp     L1339
; }
    jmp     L1357
L1367:
    jmp     L1358
L1357:
L1339:
    leave
    ret
; SEGMENT _TEXT
; glb GenFuse : (
; prm     idx : * int
;     ) void
SEGMENT _TEXT
    global  _GenFuse
_GenFuse:
    push    bp
    mov     bp, sp
; loc     idx : (@4): * int
; loc     tok : (@-2): int
    sub     sp, 2
; loc     oldIdxRight : (@-4): int
    sub     sp, 2
; loc     oldSpRight : (@-6): int
    sub     sp, 2
; loc     oldIdxLeft : (@-8): int
    sub     sp, 2
; loc     oldSpLeft : (@-10): int
    sub     sp, 2
; loc     opSzRight : (@-12): int
    sub     sp, 2
; loc     opSzLeft : (@-14): int
    sub     sp, 2
; loc     opTypRight : (@-16): int
    sub     sp, 2
; loc     opTypLeft : (@-18): int
    sub     sp, 2
; loc     opValRight : (@-20): int
    sub     sp, 2
; loc     opValLeft : (@-22): int
    sub     sp, 2
; loc     delDerefRight : (@-24): int
    sub     sp, 2
; loc     delDerefLeft : (@-26): int
    sub     sp, 2
; loc     num : (@-28): int
    sub     sp, 2
; loc     lvalSize : (@-30): int
    sub     sp, 2
; if
; RPN'ized expression: "idx *u 0 < "
; Expanded expression: "(@4) *(2) *(2) 0 < "
; Fused expression:    "*(2) (@4) < *ax 0 IF! "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 0
    jge     L1370
; RPN'ized expression: "( L1372 error ) "
; Expanded expression: " L1372  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1372:
    db  "GenFuse(): idx < 0",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1372 , error )2 "
    push    L1372
    call    _error
    sub     sp, -2
L1370:
; RPN'ized expression: "tok stack idx *u + *u 0 + *u = "
; Expanded expression: "(@-2) stack (@4) *(2) *(2) 4 * + 0 + *(2) =(2) "
; Fused expression:    "*(2) (@4) * *ax 4 + stack ax + ax 0 =(34) *(@-2) *ax "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-2], ax
; RPN'ized expression: "idx *u -- "
; Expanded expression: "(@4) *(2) --(2) "
; Fused expression:    "*(2) (@4) --(2) *ax "
    mov     ax, [bp+4]
    mov     bx, ax
    dec     word [bx]
    mov     ax, [bx]
; RPN'ized expression: "oldIdxRight idx *u = "
; Expanded expression: "(@-4) (@4) *(2) *(2) =(2) "
; Fused expression:    "*(2) (@4) =(34) *(@-4) *ax "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-4], ax
; RPN'ized expression: "oldSpRight sp = "
; Expanded expression: "(@-6) sp *(2) =(2) "
; Fused expression:    "=(34) *(@-6) *sp "
    mov     ax, [_sp]
    mov     [bp-6], ax
; switch
; RPN'ized expression: "tok "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
    mov     ax, [bp-2]
    jmp     L1376
; {
; case
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
    jmp     L1377
L1376:
    cmp     ax, 2
    jne     L1378
L1377:
; case
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
    jmp     L1379
L1378:
    cmp     ax, 1
    jne     L1380
L1379:
; case
; RPN'ized expression: "16 "
; Expanded expression: "16 "
; Expression value: 16
    jmp     L1381
L1380:
    cmp     ax, 16
    jne     L1382
L1381:
; case
; RPN'ized expression: "89 "
; Expanded expression: "89 "
; Expression value: 89
    jmp     L1383
L1382:
    cmp     ax, 89
    jne     L1384
L1383:
; break
    jmp     L1374
; case
; RPN'ized expression: "90 "
; Expanded expression: "90 "
; Expression value: 90
    jmp     L1385
L1384:
    cmp     ax, 90
    jne     L1386
L1385:
; RPN'ized expression: "( idx GenFuse ) "
; Expanded expression: " (@4) *(2)  GenFuse ()2 "
; Fused expression:    "( *(2) (@4) , GenFuse )2 "
    push    word [bp+4]
    call    _GenFuse
    sub     sp, -2
; break
    jmp     L1374
; case
; RPN'ized expression: "78 "
; Expanded expression: "78 "
; Expression value: 78
    jmp     L1387
L1386:
    cmp     ax, 78
    jne     L1388
L1387:
; RPN'ized expression: "opSzRight stack idx *u 1 + + *u 1 + *u = "
; Expanded expression: "(@-12) stack (@4) *(2) *(2) 1 + 4 * + 2 + *(2) =(2) "
; Fused expression:    "*(2) (@4) + *ax 1 * ax 4 + stack ax + ax 2 =(34) *(@-12) *ax "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-12], ax
; RPN'ized expression: "( idx GenFuse ) "
; Expanded expression: " (@4) *(2)  GenFuse ()2 "
; Fused expression:    "( *(2) (@4) , GenFuse )2 "
    push    word [bp+4]
    call    _GenFuse
    sub     sp, -2
; RPN'ized expression: "oldIdxRight oldSpRight sp - -= "
; Expanded expression: "(@-4) (@-6) *(2) sp *(2) - -=(2) "
; Fused expression:    "- *(@-6) *sp -=(34) *(@-4) ax "
    mov     ax, [bp-6]
    sub     ax, [_sp]
    mov     cx, ax
    mov     ax, [bp-4]
    sub     ax, cx
    mov     [bp-4], ax
; switch
; RPN'ized expression: "stack oldIdxRight + *u 0 + *u "
; Expanded expression: "stack (@-4) *(2) 4 * + 0 + *(2) "
; Fused expression:    "* *(@-4) 4 + stack ax + ax 0 *(2) ax "
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    jmp     L1392
; {
; case
; RPN'ized expression: "16 "
; Expanded expression: "16 "
; Expression value: 16
    jmp     L1393
L1392:
    cmp     ax, 16
    jne     L1394
L1393:
; case
; RPN'ized expression: "89 "
; Expanded expression: "89 "
; Expression value: 89
    jmp     L1395
L1394:
    cmp     ax, 89
    jne     L1396
L1395:
; if
; RPN'ized expression: "stack oldIdxRight + *u 0 + *u 16 == "
; Expanded expression: "stack (@-4) *(2) 4 * + 0 + *(2) 16 == "
; Fused expression:    "* *(@-4) 4 + stack ax + ax 0 == *ax 16 IF! "
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 16
    jne     L1398
; RPN'ized expression: "stack oldIdxRight 1 + + *u 0 + *u 257 = "
; Expanded expression: "stack (@-4) *(2) 1 + 4 * + 0 + 257 =(2) "
; Fused expression:    "+ *(@-4) 1 * ax 4 + stack ax + ax 0 =(34) *ax 257 "
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, 257
    mov     [bx], ax
    jmp     L1399
L1398:
; else
; RPN'ized expression: "stack oldIdxRight 1 + + *u 0 + *u 258 = "
; Expanded expression: "stack (@-4) *(2) 1 + 4 * + 0 + 258 =(2) "
; Fused expression:    "+ *(@-4) 1 * ax 4 + stack ax + ax 0 =(34) *ax 258 "
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, 258
    mov     [bx], ax
L1399:
; RPN'ized expression: "stack oldIdxRight 1 + + *u 1 + *u stack oldIdxRight + *u 1 + *u = "
; Expanded expression: "stack (@-4) *(2) 1 + 4 * + 2 + stack (@-4) *(2) 4 * + 2 + *(2) =(2) "
; Fused expression:    "+ *(@-4) 1 * ax 4 + stack ax + ax 2 push-ax * *(@-4) 4 + stack ax + ax 2 =(34) **sp *ax "
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    push    ax
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bx]
    pop     bx
    mov     [bx], ax
; RPN'ized expression: "stack oldIdxRight + *u 0 + *u tok = "
; Expanded expression: "stack (@-4) *(2) 4 * + 0 + (@-2) *(2) =(2) "
; Fused expression:    "* *(@-4) 4 + stack ax + ax 0 =(34) *ax *(@-2) "
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bp-2]
    mov     [bx], ax
; RPN'ized expression: "stack oldIdxRight + *u 1 + *u opSzRight = "
; Expanded expression: "stack (@-4) *(2) 4 * + 2 + (@-12) *(2) =(2) "
; Fused expression:    "* *(@-4) 4 + stack ax + ax 2 =(34) *ax *(@-12) "
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bp-12]
    mov     [bx], ax
; break
    jmp     L1390
; default
L1391:
; RPN'ized expression: "( 259 , oldIdxRight 2 + ins ) "
; Expanded expression: " 259  (@-4) *(2) 2 +  ins ()4 "
; Fused expression:    "( 259 , + *(@-4) 2 , ins )4 "
    push    259
    mov     ax, [bp-4]
    add     ax, 2
    push    ax
    call    _ins
    sub     sp, -4
; break
    jmp     L1390
; }
    jmp     L1390
L1396:
    jmp     L1391
L1390:
; break
    jmp     L1374
; case
; RPN'ized expression: "12 "
; Expanded expression: "12 "
; Expression value: 12
    jmp     L1389
L1388:
    cmp     ax, 12
    jne     L1400
L1389:
; case
; RPN'ized expression: "13 "
; Expanded expression: "13 "
; Expression value: 13
    jmp     L1401
L1400:
    cmp     ax, 13
    jne     L1402
L1401:
; case
; RPN'ized expression: "81 "
; Expanded expression: "81 "
; Expression value: 81
    jmp     L1403
L1402:
    cmp     ax, 81
    jne     L1404
L1403:
; case
; RPN'ized expression: "82 "
; Expanded expression: "82 "
; Expression value: 82
    jmp     L1405
L1404:
    cmp     ax, 82
    jne     L1406
L1405:
; RPN'ized expression: "opSzRight stack idx *u 1 + + *u 1 + *u = "
; Expanded expression: "(@-12) stack (@4) *(2) *(2) 1 + 4 * + 2 + *(2) =(2) "
; Fused expression:    "*(2) (@4) + *ax 1 * ax 4 + stack ax + ax 2 =(34) *(@-12) *ax "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-12], ax
; RPN'ized expression: "( idx GenFuse ) "
; Expanded expression: " (@4) *(2)  GenFuse ()2 "
; Fused expression:    "( *(2) (@4) , GenFuse )2 "
    push    word [bp+4]
    call    _GenFuse
    sub     sp, -2
; RPN'ized expression: "oldIdxRight oldSpRight sp - -= "
; Expanded expression: "(@-4) (@-6) *(2) sp *(2) - -=(2) "
; Fused expression:    "- *(@-6) *sp -=(34) *(@-4) ax "
    mov     ax, [bp-6]
    sub     ax, [_sp]
    mov     cx, ax
    mov     ax, [bp-4]
    sub     ax, cx
    mov     [bp-4], ax
; switch
; RPN'ized expression: "stack oldIdxRight + *u 0 + *u "
; Expanded expression: "stack (@-4) *(2) 4 * + 0 + *(2) "
; Fused expression:    "* *(@-4) 4 + stack ax + ax 0 *(2) ax "
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    jmp     L1410
; {
; case
; RPN'ized expression: "16 "
; Expanded expression: "16 "
; Expression value: 16
    jmp     L1411
L1410:
    cmp     ax, 16
    jne     L1412
L1411:
; case
; RPN'ized expression: "89 "
; Expanded expression: "89 "
; Expression value: 89
    jmp     L1413
L1412:
    cmp     ax, 89
    jne     L1414
L1413:
; if
; RPN'ized expression: "stack oldIdxRight + *u 0 + *u 16 == "
; Expanded expression: "stack (@-4) *(2) 4 * + 0 + *(2) 16 == "
; Fused expression:    "* *(@-4) 4 + stack ax + ax 0 == *ax 16 IF! "
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 16
    jne     L1416
; RPN'ized expression: "stack oldIdxRight 1 + + *u 0 + *u 260 = "
; Expanded expression: "stack (@-4) *(2) 1 + 4 * + 0 + 260 =(2) "
; Fused expression:    "+ *(@-4) 1 * ax 4 + stack ax + ax 0 =(34) *ax 260 "
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, 260
    mov     [bx], ax
    jmp     L1417
L1416:
; else
; RPN'ized expression: "stack oldIdxRight 1 + + *u 0 + *u 261 = "
; Expanded expression: "stack (@-4) *(2) 1 + 4 * + 0 + 261 =(2) "
; Fused expression:    "+ *(@-4) 1 * ax 4 + stack ax + ax 0 =(34) *ax 261 "
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, 261
    mov     [bx], ax
L1417:
; RPN'ized expression: "stack oldIdxRight 1 + + *u 1 + *u stack oldIdxRight + *u 1 + *u = "
; Expanded expression: "stack (@-4) *(2) 1 + 4 * + 2 + stack (@-4) *(2) 4 * + 2 + *(2) =(2) "
; Fused expression:    "+ *(@-4) 1 * ax 4 + stack ax + ax 2 push-ax * *(@-4) 4 + stack ax + ax 2 =(34) **sp *ax "
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    push    ax
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bx]
    pop     bx
    mov     [bx], ax
; RPN'ized expression: "stack oldIdxRight + *u 0 + *u tok = "
; Expanded expression: "stack (@-4) *(2) 4 * + 0 + (@-2) *(2) =(2) "
; Fused expression:    "* *(@-4) 4 + stack ax + ax 0 =(34) *ax *(@-2) "
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bp-2]
    mov     [bx], ax
; RPN'ized expression: "stack oldIdxRight + *u 1 + *u opSzRight = "
; Expanded expression: "stack (@-4) *(2) 4 * + 2 + (@-12) *(2) =(2) "
; Fused expression:    "* *(@-4) 4 + stack ax + ax 2 =(34) *ax *(@-12) "
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bp-12]
    mov     [bx], ax
; break
    jmp     L1408
; default
L1409:
; RPN'ized expression: "( 262 , oldIdxRight 2 + ins ) "
; Expanded expression: " 262  (@-4) *(2) 2 +  ins ()4 "
; Fused expression:    "( 262 , + *(@-4) 2 , ins )4 "
    push    262
    mov     ax, [bp-4]
    add     ax, 2
    push    ax
    call    _ins
    sub     sp, -4
; break
    jmp     L1408
; }
    jmp     L1408
L1414:
    jmp     L1409
L1408:
; break
    jmp     L1374
; case
; RPN'ized expression: "126 "
; Expanded expression: "126 "
; Expression value: 126
    jmp     L1407
L1406:
    cmp     ax, 126
    jne     L1418
L1407:
; case
; RPN'ized expression: "79 "
; Expanded expression: "79 "
; Expression value: 79
    jmp     L1419
L1418:
    cmp     ax, 79
    jne     L1420
L1419:
; case
; RPN'ized expression: "80 "
; Expanded expression: "80 "
; Expression value: 80
    jmp     L1421
L1420:
    cmp     ax, 80
    jne     L1422
L1421:
; case
; RPN'ized expression: "120 "
; Expanded expression: "120 "
; Expression value: 120
    jmp     L1423
L1422:
    cmp     ax, 120
    jne     L1424
L1423:
; RPN'ized expression: "( idx GenFuse ) "
; Expanded expression: " (@4) *(2)  GenFuse ()2 "
; Fused expression:    "( *(2) (@4) , GenFuse )2 "
    push    word [bp+4]
    call    _GenFuse
    sub     sp, -2
; RPN'ized expression: "oldIdxRight oldSpRight sp - -= "
; Expanded expression: "(@-4) (@-6) *(2) sp *(2) - -=(2) "
; Fused expression:    "- *(@-6) *sp -=(34) *(@-4) ax "
    mov     ax, [bp-6]
    sub     ax, [_sp]
    mov     cx, ax
    mov     ax, [bp-4]
    sub     ax, cx
    mov     [bp-4], ax
; if
; RPN'ized expression: "tok 79 == "
; Expanded expression: "(@-2) *(2) 79 == "
; Fused expression:    "== *(@-2) 79 IF! "
    mov     ax, [bp-2]
    cmp     ax, 79
    jne     L1426
; RPN'ized expression: "( 1 , oldIdxRight 1 + del ) "
; Expanded expression: " 1  (@-4) *(2) 1 +  del ()4 "
; Fused expression:    "( 1 , + *(@-4) 1 , del )4 "
    push    1
    mov     ax, [bp-4]
    add     ax, 1
    push    ax
    call    _del
    sub     sp, -4
L1426:
; break
    jmp     L1374
; case
; RPN'ized expression: "83 "
; Expanded expression: "83 "
; Expression value: 83
    jmp     L1425
L1424:
    cmp     ax, 83
    jne     L1428
L1425:
; case
; RPN'ized expression: "84 "
; Expanded expression: "84 "
; Expression value: 84
    jmp     L1429
L1428:
    cmp     ax, 84
    jne     L1430
L1429:
; RPN'ized expression: "opSzRight stack idx *u 1 + + *u 1 + *u = "
; Expanded expression: "(@-12) stack (@4) *(2) *(2) 1 + 4 * + 2 + *(2) =(2) "
; Fused expression:    "*(2) (@4) + *ax 1 * ax 4 + stack ax + ax 2 =(34) *(@-12) *ax "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-12], ax
; RPN'ized expression: "num stack idx *u + *u 1 + *u = "
; Expanded expression: "(@-28) stack (@4) *(2) *(2) 4 * + 2 + *(2) =(2) "
; Fused expression:    "*(2) (@4) * *ax 4 + stack ax + ax 2 =(34) *(@-28) *ax "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-28], ax
; RPN'ized expression: "oldIdxRight idx *u -- = "
; Expanded expression: "(@-4) (@4) *(2) --(2) =(2) "
; Fused expression:    "*(2) (@4) --(2) *ax =(34) *(@-4) ax "
    mov     ax, [bp+4]
    mov     bx, ax
    dec     word [bx]
    mov     ax, [bx]
    mov     [bp-4], ax
; RPN'ized expression: "( idx GenFuse ) "
; Expanded expression: " (@4) *(2)  GenFuse ()2 "
; Fused expression:    "( *(2) (@4) , GenFuse )2 "
    push    word [bp+4]
    call    _GenFuse
    sub     sp, -2
; RPN'ized expression: "oldIdxRight oldSpRight sp - -= "
; Expanded expression: "(@-4) (@-6) *(2) sp *(2) - -=(2) "
; Fused expression:    "- *(@-6) *sp -=(34) *(@-4) ax "
    mov     ax, [bp-6]
    sub     ax, [_sp]
    mov     cx, ax
    mov     ax, [bp-4]
    sub     ax, cx
    mov     [bp-4], ax
; switch
; RPN'ized expression: "stack oldIdxRight + *u 0 + *u "
; Expanded expression: "stack (@-4) *(2) 4 * + 0 + *(2) "
; Fused expression:    "* *(@-4) 4 + stack ax + ax 0 *(2) ax "
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    jmp     L1434
; {
; case
; RPN'ized expression: "16 "
; Expanded expression: "16 "
; Expression value: 16
    jmp     L1435
L1434:
    cmp     ax, 16
    jne     L1436
L1435:
; case
; RPN'ized expression: "89 "
; Expanded expression: "89 "
; Expression value: 89
    jmp     L1437
L1436:
    cmp     ax, 89
    jne     L1438
L1437:
; RPN'ized expression: "stack oldIdxRight 2 + + *u 0 + *u 256 = "
; Expanded expression: "stack (@-4) *(2) 2 + 4 * + 0 + 256 =(2) "
; Fused expression:    "+ *(@-4) 2 * ax 4 + stack ax + ax 0 =(34) *ax 256 "
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, 256
    mov     [bx], ax
; RPN'ized expression: "stack oldIdxRight 2 + + *u 1 + *u num = "
; Expanded expression: "stack (@-4) *(2) 2 + 4 * + 2 + (@-28) *(2) =(2) "
; Fused expression:    "+ *(@-4) 2 * ax 4 + stack ax + ax 2 =(34) *ax *(@-28) "
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bp-28]
    mov     [bx], ax
; if
; RPN'ized expression: "stack oldIdxRight + *u 0 + *u 16 == "
; Expanded expression: "stack (@-4) *(2) 4 * + 0 + *(2) 16 == "
; Fused expression:    "* *(@-4) 4 + stack ax + ax 0 == *ax 16 IF! "
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 16
    jne     L1440
; RPN'ized expression: "stack oldIdxRight 1 + + *u 0 + *u 260 = "
; Expanded expression: "stack (@-4) *(2) 1 + 4 * + 0 + 260 =(2) "
; Fused expression:    "+ *(@-4) 1 * ax 4 + stack ax + ax 0 =(34) *ax 260 "
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, 260
    mov     [bx], ax
    jmp     L1441
L1440:
; else
; RPN'ized expression: "stack oldIdxRight 1 + + *u 0 + *u 261 = "
; Expanded expression: "stack (@-4) *(2) 1 + 4 * + 0 + 261 =(2) "
; Fused expression:    "+ *(@-4) 1 * ax 4 + stack ax + ax 0 =(34) *ax 261 "
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, 261
    mov     [bx], ax
L1441:
; RPN'ized expression: "stack oldIdxRight 1 + + *u 1 + *u stack oldIdxRight + *u 1 + *u = "
; Expanded expression: "stack (@-4) *(2) 1 + 4 * + 2 + stack (@-4) *(2) 4 * + 2 + *(2) =(2) "
; Fused expression:    "+ *(@-4) 1 * ax 4 + stack ax + ax 2 push-ax * *(@-4) 4 + stack ax + ax 2 =(34) **sp *ax "
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    push    ax
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bx]
    pop     bx
    mov     [bx], ax
; RPN'ized expression: "stack oldIdxRight + *u 0 + *u tok = "
; Expanded expression: "stack (@-4) *(2) 4 * + 0 + (@-2) *(2) =(2) "
; Fused expression:    "* *(@-4) 4 + stack ax + ax 0 =(34) *ax *(@-2) "
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bp-2]
    mov     [bx], ax
; RPN'ized expression: "stack oldIdxRight + *u 1 + *u opSzRight = "
; Expanded expression: "stack (@-4) *(2) 4 * + 2 + (@-12) *(2) =(2) "
; Fused expression:    "* *(@-4) 4 + stack ax + ax 2 =(34) *ax *(@-12) "
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bp-12]
    mov     [bx], ax
; break
    jmp     L1432
; default
L1433:
; RPN'ized expression: "stack oldIdxRight 1 + + *u 0 + *u tok = "
; Expanded expression: "stack (@-4) *(2) 1 + 4 * + 0 + (@-2) *(2) =(2) "
; Fused expression:    "+ *(@-4) 1 * ax 4 + stack ax + ax 0 =(34) *ax *(@-2) "
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bp-2]
    mov     [bx], ax
; RPN'ized expression: "stack oldIdxRight 1 + + *u 1 + *u opSzRight = "
; Expanded expression: "stack (@-4) *(2) 1 + 4 * + 2 + (@-12) *(2) =(2) "
; Fused expression:    "+ *(@-4) 1 * ax 4 + stack ax + ax 2 =(34) *ax *(@-12) "
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bp-12]
    mov     [bx], ax
; RPN'ized expression: "stack oldIdxRight 2 + + *u 0 + *u 262 = "
; Expanded expression: "stack (@-4) *(2) 2 + 4 * + 0 + 262 =(2) "
; Fused expression:    "+ *(@-4) 2 * ax 4 + stack ax + ax 0 =(34) *ax 262 "
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, 262
    mov     [bx], ax
; RPN'ized expression: "( num , 256 , oldIdxRight 3 + ins2 ) "
; Expanded expression: " (@-28) *(2)  256  (@-4) *(2) 3 +  ins2 ()6 "
; Fused expression:    "( *(2) (@-28) , 256 , + *(@-4) 3 , ins2 )6 "
    push    word [bp-28]
    push    256
    mov     ax, [bp-4]
    add     ax, 3
    push    ax
    call    _ins2
    sub     sp, -6
; break
    jmp     L1432
; }
    jmp     L1432
L1438:
    jmp     L1433
L1432:
; break
    jmp     L1374
; case
; RPN'ized expression: "61 "
; Expanded expression: "61 "
; Expression value: 61
    jmp     L1431
L1430:
    cmp     ax, 61
    jne     L1442
L1431:
; case
; RPN'ized expression: "68 "
; Expanded expression: "68 "
; Expression value: 68
    jmp     L1443
L1442:
    cmp     ax, 68
    jne     L1444
L1443:
; case
; RPN'ized expression: "69 "
; Expanded expression: "69 "
; Expression value: 69
    jmp     L1445
L1444:
    cmp     ax, 69
    jne     L1446
L1445:
; case
; RPN'ized expression: "65 "
; Expanded expression: "65 "
; Expression value: 65
    jmp     L1447
L1446:
    cmp     ax, 65
    jne     L1448
L1447:
; case
; RPN'ized expression: "66 "
; Expanded expression: "66 "
; Expression value: 66
    jmp     L1449
L1448:
    cmp     ax, 66
    jne     L1450
L1449:
; case
; RPN'ized expression: "67 "
; Expanded expression: "67 "
; Expression value: 67
    jmp     L1451
L1450:
    cmp     ax, 67
    jne     L1452
L1451:
; case
; RPN'ized expression: "70 "
; Expanded expression: "70 "
; Expression value: 70
    jmp     L1453
L1452:
    cmp     ax, 70
    jne     L1454
L1453:
; case
; RPN'ized expression: "71 "
; Expanded expression: "71 "
; Expression value: 71
    jmp     L1455
L1454:
    cmp     ax, 71
    jne     L1456
L1455:
; case
; RPN'ized expression: "72 "
; Expanded expression: "72 "
; Expression value: 72
    jmp     L1457
L1456:
    cmp     ax, 72
    jne     L1458
L1457:
; case
; RPN'ized expression: "73 "
; Expanded expression: "73 "
; Expression value: 73
    jmp     L1459
L1458:
    cmp     ax, 73
    jne     L1460
L1459:
; case
; RPN'ized expression: "74 "
; Expanded expression: "74 "
; Expression value: 74
    jmp     L1461
L1460:
    cmp     ax, 74
    jne     L1462
L1461:
; case
; RPN'ized expression: "43 "
; Expanded expression: "43 "
; Expression value: 43
    jmp     L1463
L1462:
    cmp     ax, 43
    jne     L1464
L1463:
; case
; RPN'ized expression: "45 "
; Expanded expression: "45 "
; Expression value: 45
    jmp     L1465
L1464:
    cmp     ax, 45
    jne     L1466
L1465:
; case
; RPN'ized expression: "42 "
; Expanded expression: "42 "
; Expression value: 42
    jmp     L1467
L1466:
    cmp     ax, 42
    jne     L1468
L1467:
; case
; RPN'ized expression: "47 "
; Expanded expression: "47 "
; Expression value: 47
    jmp     L1469
L1468:
    cmp     ax, 47
    jne     L1470
L1469:
; case
; RPN'ized expression: "37 "
; Expanded expression: "37 "
; Expression value: 37
    jmp     L1471
L1470:
    cmp     ax, 37
    jne     L1472
L1471:
; case
; RPN'ized expression: "4 "
; Expanded expression: "4 "
; Expression value: 4
    jmp     L1473
L1472:
    cmp     ax, 4
    jne     L1474
L1473:
; case
; RPN'ized expression: "5 "
; Expanded expression: "5 "
; Expression value: 5
    jmp     L1475
L1474:
    cmp     ax, 5
    jne     L1476
L1475:
; case
; RPN'ized expression: "38 "
; Expanded expression: "38 "
; Expression value: 38
    jmp     L1477
L1476:
    cmp     ax, 38
    jne     L1478
L1477:
; case
; RPN'ized expression: "94 "
; Expanded expression: "94 "
; Expression value: 94
    jmp     L1479
L1478:
    cmp     ax, 94
    jne     L1480
L1479:
; case
; RPN'ized expression: "124 "
; Expanded expression: "124 "
; Expression value: 124
    jmp     L1481
L1480:
    cmp     ax, 124
    jne     L1482
L1481:
; case
; RPN'ized expression: "60 "
; Expanded expression: "60 "
; Expression value: 60
    jmp     L1483
L1482:
    cmp     ax, 60
    jne     L1484
L1483:
; case
; RPN'ized expression: "62 "
; Expanded expression: "62 "
; Expression value: 62
    jmp     L1485
L1484:
    cmp     ax, 62
    jne     L1486
L1485:
; case
; RPN'ized expression: "10 "
; Expanded expression: "10 "
; Expression value: 10
    jmp     L1487
L1486:
    cmp     ax, 10
    jne     L1488
L1487:
; case
; RPN'ized expression: "11 "
; Expanded expression: "11 "
; Expression value: 11
    jmp     L1489
L1488:
    cmp     ax, 11
    jne     L1490
L1489:
; case
; RPN'ized expression: "8 "
; Expanded expression: "8 "
; Expression value: 8
    jmp     L1491
L1490:
    cmp     ax, 8
    jne     L1492
L1491:
; case
; RPN'ized expression: "9 "
; Expanded expression: "9 "
; Expression value: 9
    jmp     L1493
L1492:
    cmp     ax, 9
    jne     L1494
L1493:
; case
; RPN'ized expression: "85 "
; Expanded expression: "85 "
; Expression value: 85
    jmp     L1495
L1494:
    cmp     ax, 85
    jne     L1496
L1495:
; case
; RPN'ized expression: "86 "
; Expanded expression: "86 "
; Expression value: 86
    jmp     L1497
L1496:
    cmp     ax, 86
    jne     L1498
L1497:
; case
; RPN'ized expression: "87 "
; Expanded expression: "87 "
; Expression value: 87
    jmp     L1499
L1498:
    cmp     ax, 87
    jne     L1500
L1499:
; case
; RPN'ized expression: "88 "
; Expanded expression: "88 "
; Expression value: 88
    jmp     L1501
L1500:
    cmp     ax, 88
    jne     L1502
L1501:
; case
; RPN'ized expression: "6 "
; Expanded expression: "6 "
; Expression value: 6
    jmp     L1503
L1502:
    cmp     ax, 6
    jne     L1504
L1503:
; case
; RPN'ized expression: "7 "
; Expanded expression: "7 "
; Expression value: 7
    jmp     L1505
L1504:
    cmp     ax, 7
    jne     L1506
L1505:
; switch
; RPN'ized expression: "tok "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
    mov     ax, [bp-2]
    jmp     L1510
; {
; case
; RPN'ized expression: "61 "
; Expanded expression: "61 "
; Expression value: 61
    jmp     L1511
L1510:
    cmp     ax, 61
    jne     L1512
L1511:
; case
; RPN'ized expression: "68 "
; Expanded expression: "68 "
; Expression value: 68
    jmp     L1513
L1512:
    cmp     ax, 68
    jne     L1514
L1513:
; case
; RPN'ized expression: "69 "
; Expanded expression: "69 "
; Expression value: 69
    jmp     L1515
L1514:
    cmp     ax, 69
    jne     L1516
L1515:
; case
; RPN'ized expression: "65 "
; Expanded expression: "65 "
; Expression value: 65
    jmp     L1517
L1516:
    cmp     ax, 65
    jne     L1518
L1517:
; case
; RPN'ized expression: "66 "
; Expanded expression: "66 "
; Expression value: 66
    jmp     L1519
L1518:
    cmp     ax, 66
    jne     L1520
L1519:
; case
; RPN'ized expression: "67 "
; Expanded expression: "67 "
; Expression value: 67
    jmp     L1521
L1520:
    cmp     ax, 67
    jne     L1522
L1521:
; case
; RPN'ized expression: "70 "
; Expanded expression: "70 "
; Expression value: 70
    jmp     L1523
L1522:
    cmp     ax, 70
    jne     L1524
L1523:
; case
; RPN'ized expression: "71 "
; Expanded expression: "71 "
; Expression value: 71
    jmp     L1525
L1524:
    cmp     ax, 71
    jne     L1526
L1525:
; case
; RPN'ized expression: "72 "
; Expanded expression: "72 "
; Expression value: 72
    jmp     L1527
L1526:
    cmp     ax, 72
    jne     L1528
L1527:
; case
; RPN'ized expression: "73 "
; Expanded expression: "73 "
; Expression value: 73
    jmp     L1529
L1528:
    cmp     ax, 73
    jne     L1530
L1529:
; case
; RPN'ized expression: "74 "
; Expanded expression: "74 "
; Expression value: 74
    jmp     L1531
L1530:
    cmp     ax, 74
    jne     L1532
L1531:
; RPN'ized expression: "lvalSize stack idx *u 1 + + *u 1 + *u = "
; Expanded expression: "(@-30) stack (@4) *(2) *(2) 1 + 4 * + 2 + *(2) =(2) "
; Fused expression:    "*(2) (@4) + *ax 1 * ax 4 + stack ax + ax 2 =(34) *(@-30) *ax "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-30], ax
; break
    jmp     L1508
; default
L1509:
; RPN'ized expression: "lvalSize 0 = "
; Expanded expression: "(@-30) 0 =(2) "
; Fused expression:    "=(34) *(@-30) 0 "
    mov     ax, 0
    mov     [bp-30], ax
; break
    jmp     L1508
; }
    jmp     L1508
L1532:
    jmp     L1509
L1508:
; RPN'ized expression: "( idx GenFuse ) "
; Expanded expression: " (@4) *(2)  GenFuse ()2 "
; Fused expression:    "( *(2) (@4) , GenFuse )2 "
    push    word [bp+4]
    call    _GenFuse
    sub     sp, -2
; RPN'ized expression: "oldIdxRight oldSpRight sp - -= "
; Expanded expression: "(@-4) (@-6) *(2) sp *(2) - -=(2) "
; Fused expression:    "- *(@-6) *sp -=(34) *(@-4) ax "
    mov     ax, [bp-6]
    sub     ax, [_sp]
    mov     cx, ax
    mov     ax, [bp-4]
    sub     ax, cx
    mov     [bp-4], ax
; RPN'ized expression: "opTypRight ( delDerefRight &u , opSzRight &u , opValRight &u , 0 , oldIdxRight GetOperandInfo ) = "
; Expanded expression: "(@-16)  (@-24)  (@-12)  (@-20)  0  (@-4) *(2)  GetOperandInfo ()10 =(2) "
; Fused expression:    "( (@-24) , (@-12) , (@-20) , 0 , *(2) (@-4) , GetOperandInfo )10 =(34) *(@-16) ax "
    lea     ax, [bp-24]
    push    ax
    lea     ax, [bp-12]
    push    ax
    lea     ax, [bp-20]
    push    ax
    push    0
    push    word [bp-4]
    call    _GetOperandInfo
    sub     sp, -10
    mov     [bp-16], ax
; RPN'ized expression: "oldIdxLeft idx *u = "
; Expanded expression: "(@-8) (@4) *(2) *(2) =(2) "
; Fused expression:    "*(2) (@4) =(34) *(@-8) *ax "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-8], ax
; RPN'ized expression: "oldSpLeft sp = "
; Expanded expression: "(@-10) sp *(2) =(2) "
; Fused expression:    "=(34) *(@-10) *sp "
    mov     ax, [_sp]
    mov     [bp-10], ax
; RPN'ized expression: "( idx GenFuse ) "
; Expanded expression: " (@4) *(2)  GenFuse ()2 "
; Fused expression:    "( *(2) (@4) , GenFuse )2 "
    push    word [bp+4]
    call    _GenFuse
    sub     sp, -2
; RPN'ized expression: "oldIdxLeft oldSpLeft sp - -= "
; Expanded expression: "(@-8) (@-10) *(2) sp *(2) - -=(2) "
; Fused expression:    "- *(@-10) *sp -=(34) *(@-8) ax "
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    mov     ax, [bp-8]
    sub     ax, cx
    mov     [bp-8], ax
; RPN'ized expression: "oldIdxRight oldSpLeft sp - -= "
; Expanded expression: "(@-4) (@-10) *(2) sp *(2) - -=(2) "
; Fused expression:    "- *(@-10) *sp -=(34) *(@-4) ax "
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    mov     ax, [bp-4]
    sub     ax, cx
    mov     [bp-4], ax
; RPN'ized expression: "opTypLeft ( delDerefLeft &u , opSzLeft &u , opValLeft &u , lvalSize , oldIdxLeft GetOperandInfo ) = "
; Expanded expression: "(@-18)  (@-26)  (@-14)  (@-22)  (@-30) *(2)  (@-8) *(2)  GetOperandInfo ()10 =(2) "
; Fused expression:    "( (@-26) , (@-14) , (@-22) , *(2) (@-30) , *(2) (@-8) , GetOperandInfo )10 =(34) *(@-18) ax "
    lea     ax, [bp-26]
    push    ax
    lea     ax, [bp-14]
    push    ax
    lea     ax, [bp-22]
    push    ax
    push    word [bp-30]
    push    word [bp-8]
    call    _GetOperandInfo
    sub     sp, -10
    mov     [bp-18], ax
; if
; RPN'ized expression: "tok 6 == tok 7 == || "
; Expanded expression: "(@-2) *(2) 6 == _Bool [sh||->1536] (@-2) *(2) 7 == _Bool ||[1536] "
; Fused expression:    "== *(@-2) 6 _Bool [sh||->1536] == *(@-2) 7 _Bool ||[1536] "
    mov     ax, [bp-2]
    cmp     ax, 6
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L1536
    mov     ax, [bp-2]
    cmp     ax, 7
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L1536:
; JumpIfZero
    test    ax, ax
    jz      L1534
; break
    jmp     L1374
L1534:
; if
; RPN'ized expression: "opTypLeft 259 != opTypLeft 262 != && "
; Expanded expression: "(@-18) *(2) 259 != _Bool [sh&&->1539] (@-18) *(2) 262 != _Bool &&[1539] "
; Fused expression:    "!= *(@-18) 259 _Bool [sh&&->1539] != *(@-18) 262 _Bool &&[1539] "
    mov     ax, [bp-18]
    cmp     ax, 259
    setne   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L1539
    mov     ax, [bp-18]
    cmp     ax, 262
    setne   al
    cbw
    test    ax, ax
    setnz   al
    cbw
L1539:
; JumpIfZero
    test    ax, ax
    jz      L1537
; {
; loc             cnt : (@-32): int
    sub     sp, 2
; =
; RPN'ized expression: "oldIdxLeft idx *u - "
; Expanded expression: "(@-8) *(2) (@4) *(2) *(2) - "
; Fused expression:    "*(2) (@4) - *(@-8) *ax =(34) *(@-32) ax "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, [bp-8]
    sub     ax, cx
    mov     [bp-32], ax
; RPN'ized expression: "( cnt , idx *u 1 + del ) "
; Expanded expression: " (@-32) *(2)  (@4) *(2) *(2) 1 +  del ()4 "
; Fused expression:    "( *(2) (@-32) , *(2) (@4) + *ax 1 , del )4 "
    push    word [bp-32]
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    add     ax, 1
    push    ax
    call    _del
    sub     sp, -4
; RPN'ized expression: "oldIdxLeft cnt -= "
; Expanded expression: "(@-8) (@-32) *(2) -=(2) "
; Fused expression:    "-=(34) *(@-8) *(@-32) "
    mov     ax, [bp-8]
    sub     ax, [bp-32]
    mov     [bp-8], ax
; RPN'ized expression: "oldIdxRight cnt -= "
; Expanded expression: "(@-4) (@-32) *(2) -=(2) "
; Fused expression:    "-=(34) *(@-4) *(@-32) "
    mov     ax, [bp-4]
    sub     ax, [bp-32]
    mov     [bp-4], ax
    sub     sp, -2
; }
    jmp     L1538
L1537:
; else
; if
; RPN'ized expression: "opTypRight 259 == opTypRight 262 == || "
; Expanded expression: "(@-16) *(2) 259 == _Bool [sh||->1542] (@-16) *(2) 262 == _Bool ||[1542] "
; Fused expression:    "== *(@-16) 259 _Bool [sh||->1542] == *(@-16) 262 _Bool ||[1542] "
    mov     ax, [bp-16]
    cmp     ax, 259
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L1542
    mov     ax, [bp-16]
    cmp     ax, 262
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L1542:
; JumpIfZero
    test    ax, ax
    jz      L1540
; {
; RPN'ized expression: "( 512 , oldIdxLeft ++ ins ) "
; Expanded expression: " 512  (@-8) ++(2)  ins ()4 "
; Fused expression:    "( 512 , ++(2) *(@-8) , ins )4 "
    push    512
    inc     word [bp-8]
    mov     ax, [bp-8]
    push    ax
    call    _ins
    sub     sp, -4
; RPN'ized expression: "oldIdxRight ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
    mov     ax, [bp-4]
    inc     word [bp-4]
; if
; RPN'ized expression: "opTypLeft 259 == "
; Expanded expression: "(@-18) *(2) 259 == "
; Fused expression:    "== *(@-18) 259 IF! "
    mov     ax, [bp-18]
    cmp     ax, 259
    jne     L1543
; RPN'ized expression: "opTypLeft 263 = "
; Expanded expression: "(@-18) 263 =(2) "
; Fused expression:    "=(34) *(@-18) 263 "
    mov     ax, 263
    mov     [bp-18], ax
    jmp     L1544
L1543:
; else
; RPN'ized expression: "opTypLeft 264 = "
; Expanded expression: "(@-18) 264 =(2) "
; Fused expression:    "=(34) *(@-18) 264 "
    mov     ax, 264
    mov     [bp-18], ax
L1544:
; if
; RPN'ized expression: "delDerefLeft "
; Expanded expression: "(@-26) *(2) "
; Fused expression:    "*(2) (@-26) "
    mov     ax, [bp-26]
; JumpIfZero
    test    ax, ax
    jz      L1545
; {
; RPN'ized expression: "( 2 , oldIdxLeft 2 -= del ) "
; Expanded expression: " 2  (@-8) 2 -=(2)  del ()4 "
; Fused expression:    "( 2 , -=(34) *(@-8) 2 , del )4 "
    push    2
    mov     ax, [bp-8]
    sub     ax, 2
    mov     [bp-8], ax
    push    ax
    call    _del
    sub     sp, -4
; RPN'ized expression: "oldIdxRight 2 -= "
; Expanded expression: "(@-4) 2 -=(2) "
; Fused expression:    "-=(34) *(@-4) 2 "
    mov     ax, [bp-4]
    sub     ax, 2
    mov     [bp-4], ax
; }
L1545:
; }
    jmp     L1541
L1540:
; else
; if
; RPN'ized expression: "delDerefLeft "
; Expanded expression: "(@-26) *(2) "
; Fused expression:    "*(2) (@-26) "
    mov     ax, [bp-26]
; JumpIfZero
    test    ax, ax
    jz      L1547
; {
; RPN'ized expression: "( 2 , oldIdxLeft 1 - del ) "
; Expanded expression: " 2  (@-8) *(2) 1 -  del ()4 "
; Fused expression:    "( 2 , - *(@-8) 1 , del )4 "
    push    2
    mov     ax, [bp-8]
    sub     ax, 1
    push    ax
    call    _del
    sub     sp, -4
; RPN'ized expression: "oldIdxLeft 2 -= "
; Expanded expression: "(@-8) 2 -=(2) "
; Fused expression:    "-=(34) *(@-8) 2 "
    mov     ax, [bp-8]
    sub     ax, 2
    mov     [bp-8], ax
; RPN'ized expression: "oldIdxRight 2 -= "
; Expanded expression: "(@-4) 2 -=(2) "
; Fused expression:    "-=(34) *(@-4) 2 "
    mov     ax, [bp-4]
    sub     ax, 2
    mov     [bp-4], ax
; }
L1547:
L1541:
L1538:
; if
; RPN'ized expression: "opTypRight 259 != opTypRight 262 != && "
; Expanded expression: "(@-16) *(2) 259 != _Bool [sh&&->1551] (@-16) *(2) 262 != _Bool &&[1551] "
; Fused expression:    "!= *(@-16) 259 _Bool [sh&&->1551] != *(@-16) 262 _Bool &&[1551] "
    mov     ax, [bp-16]
    cmp     ax, 259
    setne   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L1551
    mov     ax, [bp-16]
    cmp     ax, 262
    setne   al
    cbw
    test    ax, ax
    setnz   al
    cbw
L1551:
; JumpIfZero
    test    ax, ax
    jz      L1549
; {
; loc             cnt : (@-32): int
    sub     sp, 2
; =
; RPN'ized expression: "oldIdxRight oldIdxLeft - "
; Expanded expression: "(@-4) *(2) (@-8) *(2) - "
; Fused expression:    "- *(@-4) *(@-8) =(34) *(@-32) ax "
    mov     ax, [bp-4]
    sub     ax, [bp-8]
    mov     [bp-32], ax
; RPN'ized expression: "( cnt , oldIdxLeft 1 + del ) "
; Expanded expression: " (@-32) *(2)  (@-8) *(2) 1 +  del ()4 "
; Fused expression:    "( *(2) (@-32) , + *(@-8) 1 , del )4 "
    push    word [bp-32]
    mov     ax, [bp-8]
    add     ax, 1
    push    ax
    call    _del
    sub     sp, -4
; RPN'ized expression: "oldIdxRight cnt -= "
; Expanded expression: "(@-4) (@-32) *(2) -=(2) "
; Fused expression:    "-=(34) *(@-4) *(@-32) "
    mov     ax, [bp-4]
    sub     ax, [bp-32]
    mov     [bp-4], ax
    sub     sp, -2
; }
    jmp     L1550
L1549:
; else
; if
; RPN'ized expression: "delDerefRight "
; Expanded expression: "(@-24) *(2) "
; Fused expression:    "*(2) (@-24) "
    mov     ax, [bp-24]
; JumpIfZero
    test    ax, ax
    jz      L1552
; {
; RPN'ized expression: "( 2 , oldIdxRight 1 - del ) "
; Expanded expression: " 2  (@-4) *(2) 1 -  del ()4 "
; Fused expression:    "( 2 , - *(@-4) 1 , del )4 "
    push    2
    mov     ax, [bp-4]
    sub     ax, 1
    push    ax
    call    _del
    sub     sp, -4
; RPN'ized expression: "oldIdxRight 2 -= "
; Expanded expression: "(@-4) 2 -=(2) "
; Fused expression:    "-=(34) *(@-4) 2 "
    mov     ax, [bp-4]
    sub     ax, 2
    mov     [bp-4], ax
; }
L1552:
L1550:
; RPN'ized expression: "stack oldIdxRight 1 + + *u 1 + *u opSzLeft 16 * opSzRight + = "
; Expanded expression: "stack (@-4) *(2) 1 + 4 * + 2 + (@-14) *(2) 16 * (@-12) *(2) + =(2) "
; Fused expression:    "+ *(@-4) 1 * ax 4 + stack ax + ax 2 push-ax * *(@-14) 16 + ax *(@-12) =(34) **sp ax "
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    push    ax
    mov     ax, [bp-14]
    imul    ax, ax, 16
    add     ax, [bp-12]
    pop     bx
    mov     [bx], ax
; RPN'ized expression: "( opValRight , opTypRight , oldIdxRight 2 + ins2 ) "
; Expanded expression: " (@-20) *(2)  (@-16) *(2)  (@-4) *(2) 2 +  ins2 ()6 "
; Fused expression:    "( *(2) (@-20) , *(2) (@-16) , + *(@-4) 2 , ins2 )6 "
    push    word [bp-20]
    push    word [bp-16]
    mov     ax, [bp-4]
    add     ax, 2
    push    ax
    call    _ins2
    sub     sp, -6
; RPN'ized expression: "( opValLeft , opTypLeft , oldIdxRight 2 + ins2 ) "
; Expanded expression: " (@-22) *(2)  (@-18) *(2)  (@-4) *(2) 2 +  ins2 ()6 "
; Fused expression:    "( *(2) (@-22) , *(2) (@-18) , + *(@-4) 2 , ins2 )6 "
    push    word [bp-22]
    push    word [bp-18]
    mov     ax, [bp-4]
    add     ax, 2
    push    ax
    call    _ins2
    sub     sp, -6
; break
    jmp     L1374
; case
; RPN'ized expression: "41 "
; Expanded expression: "41 "
; Expression value: 41
    jmp     L1507
L1506:
    cmp     ax, 41
    jne     L1554
L1507:
; while
; RPN'ized expression: "stack idx *u + *u 0 + *u 40 != "
; Expanded expression: "stack (@4) *(2) *(2) 4 * + 0 + *(2) 40 != "
L1556:
; Fused expression:    "*(2) (@4) * *ax 4 + stack ax + ax 0 != *ax 40 IF! "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 40
    je      L1557
; {
; RPN'ized expression: "( idx GenFuse ) "
; Expanded expression: " (@4) *(2)  GenFuse ()2 "
; Fused expression:    "( *(2) (@4) , GenFuse )2 "
    push    word [bp+4]
    call    _GenFuse
    sub     sp, -2
; if
; RPN'ized expression: "stack idx *u + *u 0 + *u 44 == "
; Expanded expression: "stack (@4) *(2) *(2) 4 * + 0 + *(2) 44 == "
; Fused expression:    "*(2) (@4) * *ax 4 + stack ax + ax 0 == *ax 44 IF! "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 44
    jne     L1558
; RPN'ized expression: "idx *u -- "
; Expanded expression: "(@4) *(2) --(2) "
; Fused expression:    "*(2) (@4) --(2) *ax "
    mov     ax, [bp+4]
    mov     bx, ax
    dec     word [bx]
    mov     ax, [bx]
L1558:
; }
    jmp     L1556
L1557:
; RPN'ized expression: "idx *u -- "
; Expanded expression: "(@4) *(2) --(2) "
; Fused expression:    "*(2) (@4) --(2) *ax "
    mov     ax, [bp+4]
    mov     bx, ax
    dec     word [bx]
    mov     ax, [bx]
; break
    jmp     L1374
; default
L1375:
; RPN'ized expression: "( ( tok GetTokenName ) , L1560 error ) "
; Expanded expression: "  (@-2) *(2)  GetTokenName ()2  L1560  error ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1560:
    db  "GenFuse: unexpected token %s",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( *(2) (@-2) , GetTokenName )2 , L1560 , error )4 "
    push    word [bp-2]
    call    _GetTokenName
    sub     sp, -2
    push    ax
    push    L1560
    call    _error
    sub     sp, -4
; }
    jmp     L1374
L1554:
    jmp     L1375
L1374:
L1369:
    leave
    ret
; SEGMENT _TEXT
; glb GenGetBinaryOperatorInstr : (
; prm     tok : int
;     ) * char
SEGMENT _TEXT
    global  _GenGetBinaryOperatorInstr
_GenGetBinaryOperatorInstr:
    push    bp
    mov     bp, sp
; loc     tok : (@4): int
; switch
; RPN'ized expression: "tok "
; Expanded expression: "(@4) *(2) "
; Fused expression:    "*(2) (@4) "
    mov     ax, [bp+4]
    jmp     L1565
; {
; case
; RPN'ized expression: "68 "
; Expanded expression: "68 "
; Expression value: 68
    jmp     L1566
L1565:
    cmp     ax, 68
    jne     L1567
L1566:
; case
; RPN'ized expression: "43 "
; Expanded expression: "43 "
; Expression value: 43
    jmp     L1568
L1567:
    cmp     ax, 43
    jne     L1569
L1568:
; return
; RPN'ized expression: "L1571 "
; Expanded expression: "L1571 "
; SEGMENT _TEXT
SEGMENT _DATA
L1571:
    db  "add",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L1571 "
    mov     ax, L1571
    jmp     L1562
; case
; RPN'ized expression: "69 "
; Expanded expression: "69 "
; Expression value: 69
    jmp     L1570
L1569:
    cmp     ax, 69
    jne     L1573
L1570:
; case
; RPN'ized expression: "45 "
; Expanded expression: "45 "
; Expression value: 45
    jmp     L1574
L1573:
    cmp     ax, 45
    jne     L1575
L1574:
; return
; RPN'ized expression: "L1577 "
; Expanded expression: "L1577 "
; SEGMENT _TEXT
SEGMENT _DATA
L1577:
    db  "sub",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L1577 "
    mov     ax, L1577
    jmp     L1562
; case
; RPN'ized expression: "38 "
; Expanded expression: "38 "
; Expression value: 38
    jmp     L1576
L1575:
    cmp     ax, 38
    jne     L1579
L1576:
; case
; RPN'ized expression: "72 "
; Expanded expression: "72 "
; Expression value: 72
    jmp     L1580
L1579:
    cmp     ax, 72
    jne     L1581
L1580:
; return
; RPN'ized expression: "L1583 "
; Expanded expression: "L1583 "
; SEGMENT _TEXT
SEGMENT _DATA
L1583:
    db  "and",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L1583 "
    mov     ax, L1583
    jmp     L1562
; case
; RPN'ized expression: "94 "
; Expanded expression: "94 "
; Expression value: 94
    jmp     L1582
L1581:
    cmp     ax, 94
    jne     L1585
L1582:
; case
; RPN'ized expression: "73 "
; Expanded expression: "73 "
; Expression value: 73
    jmp     L1586
L1585:
    cmp     ax, 73
    jne     L1587
L1586:
; return
; RPN'ized expression: "L1589 "
; Expanded expression: "L1589 "
; SEGMENT _TEXT
SEGMENT _DATA
L1589:
    db  "xor",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L1589 "
    mov     ax, L1589
    jmp     L1562
; case
; RPN'ized expression: "124 "
; Expanded expression: "124 "
; Expression value: 124
    jmp     L1588
L1587:
    cmp     ax, 124
    jne     L1591
L1588:
; case
; RPN'ized expression: "74 "
; Expanded expression: "74 "
; Expression value: 74
    jmp     L1592
L1591:
    cmp     ax, 74
    jne     L1593
L1592:
; return
; RPN'ized expression: "L1595 "
; Expanded expression: "L1595 "
; SEGMENT _TEXT
SEGMENT _DATA
L1595:
    db  "or",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L1595 "
    mov     ax, L1595
    jmp     L1562
; case
; RPN'ized expression: "60 "
; Expanded expression: "60 "
; Expression value: 60
    jmp     L1594
L1593:
    cmp     ax, 60
    jne     L1597
L1594:
; case
; RPN'ized expression: "62 "
; Expanded expression: "62 "
; Expression value: 62
    jmp     L1598
L1597:
    cmp     ax, 62
    jne     L1599
L1598:
; case
; RPN'ized expression: "10 "
; Expanded expression: "10 "
; Expression value: 10
    jmp     L1600
L1599:
    cmp     ax, 10
    jne     L1601
L1600:
; case
; RPN'ized expression: "11 "
; Expanded expression: "11 "
; Expression value: 11
    jmp     L1602
L1601:
    cmp     ax, 11
    jne     L1603
L1602:
; case
; RPN'ized expression: "8 "
; Expanded expression: "8 "
; Expression value: 8
    jmp     L1604
L1603:
    cmp     ax, 8
    jne     L1605
L1604:
; case
; RPN'ized expression: "9 "
; Expanded expression: "9 "
; Expression value: 9
    jmp     L1606
L1605:
    cmp     ax, 9
    jne     L1607
L1606:
; case
; RPN'ized expression: "85 "
; Expanded expression: "85 "
; Expression value: 85
    jmp     L1608
L1607:
    cmp     ax, 85
    jne     L1609
L1608:
; case
; RPN'ized expression: "86 "
; Expanded expression: "86 "
; Expression value: 86
    jmp     L1610
L1609:
    cmp     ax, 86
    jne     L1611
L1610:
; case
; RPN'ized expression: "87 "
; Expanded expression: "87 "
; Expression value: 87
    jmp     L1612
L1611:
    cmp     ax, 87
    jne     L1613
L1612:
; case
; RPN'ized expression: "88 "
; Expanded expression: "88 "
; Expression value: 88
    jmp     L1614
L1613:
    cmp     ax, 88
    jne     L1615
L1614:
; return
; RPN'ized expression: "L1617 "
; Expanded expression: "L1617 "
; SEGMENT _TEXT
SEGMENT _DATA
L1617:
    db  "cmp",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L1617 "
    mov     ax, L1617
    jmp     L1562
; case
; RPN'ized expression: "42 "
; Expanded expression: "42 "
; Expression value: 42
    jmp     L1616
L1615:
    cmp     ax, 42
    jne     L1619
L1616:
; case
; RPN'ized expression: "65 "
; Expanded expression: "65 "
; Expression value: 65
    jmp     L1620
L1619:
    cmp     ax, 65
    jne     L1621
L1620:
; return
; RPN'ized expression: "L1623 "
; Expanded expression: "L1623 "
; SEGMENT _TEXT
SEGMENT _DATA
L1623:
    db  "mul",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L1623 "
    mov     ax, L1623
    jmp     L1562
; case
; RPN'ized expression: "47 "
; Expanded expression: "47 "
; Expression value: 47
    jmp     L1622
L1621:
    cmp     ax, 47
    jne     L1625
L1622:
; case
; RPN'ized expression: "37 "
; Expanded expression: "37 "
; Expression value: 37
    jmp     L1626
L1625:
    cmp     ax, 37
    jne     L1627
L1626:
; case
; RPN'ized expression: "66 "
; Expanded expression: "66 "
; Expression value: 66
    jmp     L1628
L1627:
    cmp     ax, 66
    jne     L1629
L1628:
; case
; RPN'ized expression: "67 "
; Expanded expression: "67 "
; Expression value: 67
    jmp     L1630
L1629:
    cmp     ax, 67
    jne     L1631
L1630:
; return
; RPN'ized expression: "L1633 "
; Expanded expression: "L1633 "
; SEGMENT _TEXT
SEGMENT _DATA
L1633:
    db  "idiv",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L1633 "
    mov     ax, L1633
    jmp     L1562
; case
; RPN'ized expression: "4 "
; Expanded expression: "4 "
; Expression value: 4
    jmp     L1632
L1631:
    cmp     ax, 4
    jne     L1635
L1632:
; case
; RPN'ized expression: "70 "
; Expanded expression: "70 "
; Expression value: 70
    jmp     L1636
L1635:
    cmp     ax, 70
    jne     L1637
L1636:
; return
; RPN'ized expression: "L1639 "
; Expanded expression: "L1639 "
; SEGMENT _TEXT
SEGMENT _DATA
L1639:
    db  "shl",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L1639 "
    mov     ax, L1639
    jmp     L1562
; case
; RPN'ized expression: "5 "
; Expanded expression: "5 "
; Expression value: 5
    jmp     L1638
L1637:
    cmp     ax, 5
    jne     L1641
L1638:
; case
; RPN'ized expression: "71 "
; Expanded expression: "71 "
; Expression value: 71
    jmp     L1642
L1641:
    cmp     ax, 71
    jne     L1643
L1642:
; return
; RPN'ized expression: "L1645 "
; Expanded expression: "L1645 "
; SEGMENT _TEXT
SEGMENT _DATA
L1645:
    db  "sar",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L1645 "
    mov     ax, L1645
    jmp     L1562
; default
L1564:
; return
; RPN'ized expression: "L1647 "
; Expanded expression: "L1647 "
; SEGMENT _TEXT
SEGMENT _DATA
L1647:
    db  0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "L1647 "
    mov     ax, L1647
    jmp     L1562
; }
    jmp     L1563
L1643:
    jmp     L1564
L1563:
L1562:
    leave
    ret
; SEGMENT _TEXT
; glb GenExpr1 : (void) void
SEGMENT _TEXT
    global  _GenExpr1
_GenExpr1:
    push    bp
    mov     bp, sp
; loc     s : (@-2): int
    sub     sp, 2
; =
; RPN'ized expression: "sp 1 - "
; Expanded expression: "sp *(2) 1 - "
; Fused expression:    "- *sp 1 =(34) *(@-2) ax "
    mov     ax, [_sp]
    sub     ax, 1
    mov     [bp-2], ax
; loc     i : (@-4): int
    sub     sp, 2
; if
; RPN'ized expression: "stack s + *u 0 + *u 22 == stack s + *u 0 + *u 76 == || "
; Expanded expression: "stack (@-2) *(2) 4 * + 0 + *(2) 22 == _Bool [sh||->1652] stack (@-2) *(2) 4 * + 0 + *(2) 76 == _Bool ||[1652] "
; Fused expression:    "* *(@-2) 4 + stack ax + ax 0 == *ax 22 _Bool [sh||->1652] * *(@-2) 4 + stack ax + ax 0 == *ax 76 _Bool ||[1652] "
    mov     ax, [bp-2]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 22
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L1652
    mov     ax, [bp-2]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 76
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L1652:
; JumpIfZero
    test    ax, ax
    jz      L1650
; RPN'ized expression: "s --p "
; Expanded expression: "(@-2) --p(2) "
; Fused expression:    "--p(2) *(@-2) "
    mov     ax, [bp-2]
    dec     word [bp-2]
L1650:
; RPN'ized expression: "( s &u GenFuse ) "
; Expanded expression: " (@-2)  GenFuse ()2 "
; Fused expression:    "( (@-2) , GenFuse )2 "
    lea     ax, [bp-2]
    push    ax
    call    _GenFuse
    sub     sp, -2
; RPN'ized expression: "( L1653 printf ) "
; Expanded expression: " L1653  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1653:
    db  "; Fused expression:    ",34,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1653 , printf )2 "
    push    L1653
    call    _printf
    sub     sp, -2
; for
; RPN'ized expression: "i 0 = "
; Expanded expression: "(@-4) 0 =(2) "
; Fused expression:    "=(34) *(@-4) 0 "
    mov     ax, 0
    mov     [bp-4], ax
L1655:
; RPN'ized expression: "i sp < "
; Expanded expression: "(@-4) *(2) sp *(2) < "
; Fused expression:    "< *(@-4) *sp IF! "
    mov     ax, [bp-4]
    cmp     ax, [_sp]
    jge     L1658
    jmp     L1657
L1656:
; RPN'ized expression: "i ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
    mov     ax, [bp-4]
    inc     word [bp-4]
    jmp     L1655
L1657:
; {
; loc         tok : (@-6): int
    sub     sp, 2
; =
; RPN'ized expression: "stack i + *u 0 + *u "
; Expanded expression: "stack (@-4) *(2) 4 * + 0 + *(2) "
; Fused expression:    "* *(@-4) 4 + stack ax + ax 0 =(34) *(@-6) *ax "
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-6], ax
; switch
; RPN'ized expression: "tok "
; Expanded expression: "(@-6) *(2) "
; Fused expression:    "*(2) (@-6) "
    mov     ax, [bp-6]
    jmp     L1661
; {
; case
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
    jmp     L1662
L1661:
    cmp     ax, 1
    jne     L1663
L1662:
; case
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
    jmp     L1664
L1663:
    cmp     ax, 2
    jne     L1665
L1664:
; case
; RPN'ized expression: "256 "
; Expanded expression: "256 "
; Expression value: 256
    jmp     L1666
L1665:
    cmp     ax, 256
    jne     L1667
L1666:
; RPN'ized expression: "( stack i + *u 1 + *u , L1669 printf ) "
; Expanded expression: " stack (@-4) *(2) 4 * + 2 + *(2)  L1669  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1669:
    db  "%d",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( * *(@-4) 4 + stack ax + ax 2 *(2) ax , L1669 , printf )4 "
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    L1669
    call    _printf
    sub     sp, -4
; break
    jmp     L1659
; case
; RPN'ized expression: "16 "
; Expanded expression: "16 "
; Expression value: 16
    jmp     L1668
L1667:
    cmp     ax, 16
    jne     L1671
L1668:
; case
; RPN'ized expression: "257 "
; Expanded expression: "257 "
; Expression value: 257
    jmp     L1672
L1671:
    cmp     ax, 257
    jne     L1673
L1672:
; {
; loc                 p : (@-8): * char
    sub     sp, 2
; =
; RPN'ized expression: "IdentTable stack i + *u 1 + *u + "
; Expanded expression: "IdentTable stack (@-4) *(2) 4 * + 2 + *(2) + "
; Fused expression:    "* *(@-4) 4 + stack ax + ax 2 + IdentTable *ax =(34) *(@-8) ax "
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, _IdentTable
    add     ax, cx
    mov     [bp-8], ax
; if
; RPN'ized expression: "( p *u isdigit ) "
; Expanded expression: " (@-8) *(2) *(1)  isdigit ()2 "
; Fused expression:    "( *(2) (@-8) *(1) ax , isdigit )2 "
    mov     ax, [bp-8]
    mov     bx, ax
    mov     al, [bx]
    cbw
    push    ax
    call    _isdigit
    sub     sp, -2
; JumpIfZero
    test    ax, ax
    jz      L1675
; RPN'ized expression: "( L1677 printf ) "
; Expanded expression: " L1677  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1677:
    db  "L",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1677 , printf )2 "
    push    L1677
    call    _printf
    sub     sp, -2
L1675:
; RPN'ized expression: "( p , L1679 printf ) "
; Expanded expression: " (@-8) *(2)  L1679  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1679:
    db  "%s",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-8) , L1679 , printf )4 "
    push    word [bp-8]
    push    L1679
    call    _printf
    sub     sp, -4
    sub     sp, -2
; }
; break
    jmp     L1659
; case
; RPN'ized expression: "260 "
; Expanded expression: "260 "
; Expression value: 260
    jmp     L1674
L1673:
    cmp     ax, 260
    jne     L1681
L1674:
; RPN'ized expression: "( IdentTable stack i + *u 1 + *u + , L1683 printf ) "
; Expanded expression: " IdentTable stack (@-4) *(2) 4 * + 2 + *(2) +  L1683  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1683:
    db  "*%s",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( * *(@-4) 4 + stack ax + ax 2 + IdentTable *ax , L1683 , printf )4 "
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, _IdentTable
    add     ax, cx
    push    ax
    push    L1683
    call    _printf
    sub     sp, -4
; break
    jmp     L1659
; case
; RPN'ized expression: "90 "
; Expanded expression: "90 "
; Expression value: 90
    jmp     L1682
L1681:
    cmp     ax, 90
    jne     L1685
L1682:
; if
; RPN'ized expression: "stack i + *u 1 + *u 0 >= "
; Expanded expression: "stack (@-4) *(2) 4 * + 2 + *(2) 0 >= "
; Fused expression:    "* *(@-4) 4 + stack ax + ax 2 >= *ax 0 IF! "
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 0
    jl      L1687
; RPN'ized expression: "( stack i + *u 1 + *u , L1689 printf ) "
; Expanded expression: " stack (@-4) *(2) 4 * + 2 + *(2)  L1689  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1689:
    db  "[sh&&->%d]",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( * *(@-4) 4 + stack ax + ax 2 *(2) ax , L1689 , printf )4 "
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    L1689
    call    _printf
    sub     sp, -4
    jmp     L1688
L1687:
; else
; RPN'ized expression: "( stack i + *u 1 + *u -u , L1691 printf ) "
; Expanded expression: " stack (@-4) *(2) 4 * + 2 + *(2) -u  L1691  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1691:
    db  "[sh||->%d]",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( * *(@-4) 4 + stack ax + ax 2 *(2) ax -u , L1691 , printf )4 "
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bx]
    neg     ax
    push    ax
    push    L1691
    call    _printf
    sub     sp, -4
L1688:
; break
    jmp     L1659
; case
; RPN'ized expression: "89 "
; Expanded expression: "89 "
; Expression value: 89
    jmp     L1686
L1685:
    cmp     ax, 89
    jne     L1693
L1686:
; case
; RPN'ized expression: "258 "
; Expanded expression: "258 "
; Expression value: 258
    jmp     L1694
L1693:
    cmp     ax, 258
    jne     L1695
L1694:
; RPN'ized expression: "( stack i + *u 1 + *u , L1697 printf ) "
; Expanded expression: " stack (@-4) *(2) 4 * + 2 + *(2)  L1697  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1697:
    db  "(@%d)",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( * *(@-4) 4 + stack ax + ax 2 *(2) ax , L1697 , printf )4 "
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    L1697
    call    _printf
    sub     sp, -4
; break
    jmp     L1659
; case
; RPN'ized expression: "261 "
; Expanded expression: "261 "
; Expression value: 261
    jmp     L1696
L1695:
    cmp     ax, 261
    jne     L1699
L1696:
; RPN'ized expression: "( stack i + *u 1 + *u , L1701 printf ) "
; Expanded expression: " stack (@-4) *(2) 4 * + 2 + *(2)  L1701  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1701:
    db  "*(@%d)",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( * *(@-4) 4 + stack ax + ax 2 *(2) ax , L1701 , printf )4 "
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    L1701
    call    _printf
    sub     sp, -4
; break
    jmp     L1659
; case
; RPN'ized expression: "78 "
; Expanded expression: "78 "
; Expression value: 78
    jmp     L1700
L1699:
    cmp     ax, 78
    jne     L1703
L1700:
; RPN'ized expression: "( stack i + *u 1 + *u , L1705 printf ) "
; Expanded expression: " stack (@-4) *(2) 4 * + 2 + *(2)  L1705  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1705:
    db  "*(%d)",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( * *(@-4) 4 + stack ax + ax 2 *(2) ax , L1705 , printf )4 "
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    L1705
    call    _printf
    sub     sp, -4
; break
    jmp     L1659
; case
; RPN'ized expression: "40 "
; Expanded expression: "40 "
; Expression value: 40
    jmp     L1704
L1703:
    cmp     ax, 40
    jne     L1707
L1704:
; case
; RPN'ized expression: "44 "
; Expanded expression: "44 "
; Expression value: 44
    jmp     L1708
L1707:
    cmp     ax, 44
    jne     L1709
L1708:
; RPN'ized expression: "( tok , L1711 printf ) "
; Expanded expression: " (@-6) *(2)  L1711  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1711:
    db  "%c",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-6) , L1711 , printf )4 "
    push    word [bp-6]
    push    L1711
    call    _printf
    sub     sp, -4
; break
    jmp     L1659
; case
; RPN'ized expression: "41 "
; Expanded expression: "41 "
; Expression value: 41
    jmp     L1710
L1709:
    cmp     ax, 41
    jne     L1713
L1710:
; RPN'ized expression: "( stack i + *u 1 + *u , L1715 printf ) "
; Expanded expression: " stack (@-4) *(2) 4 * + 2 + *(2)  L1715  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1715:
    db  ")%d",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( * *(@-4) 4 + stack ax + ax 2 *(2) ax , L1715 , printf )4 "
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    L1715
    call    _printf
    sub     sp, -4
; break
    jmp     L1659
; case
; RPN'ized expression: "259 "
; Expanded expression: "259 "
; Expression value: 259
    jmp     L1714
L1713:
    cmp     ax, 259
    jne     L1717
L1714:
; RPN'ized expression: "( L1719 printf ) "
; Expanded expression: " L1719  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1719:
    db  "ax",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1719 , printf )2 "
    push    L1719
    call    _printf
    sub     sp, -2
; break
    jmp     L1659
; case
; RPN'ized expression: "262 "
; Expanded expression: "262 "
; Expression value: 262
    jmp     L1718
L1717:
    cmp     ax, 262
    jne     L1721
L1718:
; RPN'ized expression: "( L1723 printf ) "
; Expanded expression: " L1723  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1723:
    db  "*ax",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1723 , printf )2 "
    push    L1723
    call    _printf
    sub     sp, -2
; break
    jmp     L1659
; case
; RPN'ized expression: "263 "
; Expanded expression: "263 "
; Expression value: 263
    jmp     L1722
L1721:
    cmp     ax, 263
    jne     L1725
L1722:
; RPN'ized expression: "( L1727 printf ) "
; Expanded expression: " L1727  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1727:
    db  "*sp",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1727 , printf )2 "
    push    L1727
    call    _printf
    sub     sp, -2
; break
    jmp     L1659
; case
; RPN'ized expression: "264 "
; Expanded expression: "264 "
; Expression value: 264
    jmp     L1726
L1725:
    cmp     ax, 264
    jne     L1729
L1726:
; RPN'ized expression: "( L1731 printf ) "
; Expanded expression: " L1731  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1731:
    db  "**sp",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1731 , printf )2 "
    push    L1731
    call    _printf
    sub     sp, -2
; break
    jmp     L1659
; case
; RPN'ized expression: "512 "
; Expanded expression: "512 "
; Expression value: 512
    jmp     L1730
L1729:
    cmp     ax, 512
    jne     L1733
L1730:
; RPN'ized expression: "( L1735 printf ) "
; Expanded expression: " L1735  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1735:
    db  "push-ax",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1735 , printf )2 "
    push    L1735
    call    _printf
    sub     sp, -2
; break
    jmp     L1659
; case
; RPN'ized expression: "22 "
; Expanded expression: "22 "
; Expression value: 22
    jmp     L1734
L1733:
    cmp     ax, 22
    jne     L1737
L1734:
; RPN'ized expression: "( L1739 printf ) "
; Expanded expression: " L1739  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1739:
    db  "IF",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1739 , printf )2 "
    push    L1739
    call    _printf
    sub     sp, -2
; break
    jmp     L1659
; case
; RPN'ized expression: "76 "
; Expanded expression: "76 "
; Expression value: 76
    jmp     L1738
L1737:
    cmp     ax, 76
    jne     L1741
L1738:
; RPN'ized expression: "( L1743 printf ) "
; Expanded expression: " L1743  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1743:
    db  "IF!",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1743 , printf )2 "
    push    L1743
    call    _printf
    sub     sp, -2
; break
    jmp     L1659
; default
L1660:
; RPN'ized expression: "( ( tok GetTokenName ) , L1745 printf ) "
; Expanded expression: "  (@-6) *(2)  GetTokenName ()2  L1745  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1745:
    db  "%s",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( *(2) (@-6) , GetTokenName )2 , L1745 , printf )4 "
    push    word [bp-6]
    call    _GetTokenName
    sub     sp, -2
    push    ax
    push    L1745
    call    _printf
    sub     sp, -4
; switch
; RPN'ized expression: "tok "
; Expanded expression: "(@-6) *(2) "
; Fused expression:    "*(2) (@-6) "
    mov     ax, [bp-6]
    jmp     L1749
; {
; case
; RPN'ized expression: "7 "
; Expanded expression: "7 "
; Expression value: 7
    jmp     L1750
L1749:
    cmp     ax, 7
    jne     L1751
L1750:
; case
; RPN'ized expression: "6 "
; Expanded expression: "6 "
; Expression value: 6
    jmp     L1752
L1751:
    cmp     ax, 6
    jne     L1753
L1752:
; RPN'ized expression: "( stack i + *u 1 + *u , L1755 printf ) "
; Expanded expression: " stack (@-4) *(2) 4 * + 2 + *(2)  L1755  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1755:
    db  "[%d]",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( * *(@-4) 4 + stack ax + ax 2 *(2) ax , L1755 , printf )4 "
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    L1755
    call    _printf
    sub     sp, -4
; break
    jmp     L1747
; case
; RPN'ized expression: "61 "
; Expanded expression: "61 "
; Expression value: 61
    jmp     L1754
L1753:
    cmp     ax, 61
    jne     L1757
L1754:
; case
; RPN'ized expression: "12 "
; Expanded expression: "12 "
; Expression value: 12
    jmp     L1758
L1757:
    cmp     ax, 12
    jne     L1759
L1758:
; case
; RPN'ized expression: "13 "
; Expanded expression: "13 "
; Expression value: 13
    jmp     L1760
L1759:
    cmp     ax, 13
    jne     L1761
L1760:
; case
; RPN'ized expression: "81 "
; Expanded expression: "81 "
; Expression value: 81
    jmp     L1762
L1761:
    cmp     ax, 81
    jne     L1763
L1762:
; case
; RPN'ized expression: "82 "
; Expanded expression: "82 "
; Expression value: 82
    jmp     L1764
L1763:
    cmp     ax, 82
    jne     L1765
L1764:
; case
; RPN'ized expression: "68 "
; Expanded expression: "68 "
; Expression value: 68
    jmp     L1766
L1765:
    cmp     ax, 68
    jne     L1767
L1766:
; case
; RPN'ized expression: "69 "
; Expanded expression: "69 "
; Expression value: 69
    jmp     L1768
L1767:
    cmp     ax, 69
    jne     L1769
L1768:
; case
; RPN'ized expression: "83 "
; Expanded expression: "83 "
; Expression value: 83
    jmp     L1770
L1769:
    cmp     ax, 83
    jne     L1771
L1770:
; case
; RPN'ized expression: "84 "
; Expanded expression: "84 "
; Expression value: 84
    jmp     L1772
L1771:
    cmp     ax, 84
    jne     L1773
L1772:
; case
; RPN'ized expression: "65 "
; Expanded expression: "65 "
; Expression value: 65
    jmp     L1774
L1773:
    cmp     ax, 65
    jne     L1775
L1774:
; case
; RPN'ized expression: "66 "
; Expanded expression: "66 "
; Expression value: 66
    jmp     L1776
L1775:
    cmp     ax, 66
    jne     L1777
L1776:
; case
; RPN'ized expression: "67 "
; Expanded expression: "67 "
; Expression value: 67
    jmp     L1778
L1777:
    cmp     ax, 67
    jne     L1779
L1778:
; case
; RPN'ized expression: "70 "
; Expanded expression: "70 "
; Expression value: 70
    jmp     L1780
L1779:
    cmp     ax, 70
    jne     L1781
L1780:
; case
; RPN'ized expression: "71 "
; Expanded expression: "71 "
; Expression value: 71
    jmp     L1782
L1781:
    cmp     ax, 71
    jne     L1783
L1782:
; case
; RPN'ized expression: "72 "
; Expanded expression: "72 "
; Expression value: 72
    jmp     L1784
L1783:
    cmp     ax, 72
    jne     L1785
L1784:
; case
; RPN'ized expression: "73 "
; Expanded expression: "73 "
; Expression value: 73
    jmp     L1786
L1785:
    cmp     ax, 73
    jne     L1787
L1786:
; case
; RPN'ized expression: "74 "
; Expanded expression: "74 "
; Expression value: 74
    jmp     L1788
L1787:
    cmp     ax, 74
    jne     L1789
L1788:
; RPN'ized expression: "( stack i + *u 1 + *u , L1791 printf ) "
; Expanded expression: " stack (@-4) *(2) 4 * + 2 + *(2)  L1791  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1791:
    db  "(%d)",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( * *(@-4) 4 + stack ax + ax 2 *(2) ax , L1791 , printf )4 "
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    L1791
    call    _printf
    sub     sp, -4
; break
    jmp     L1747
; }
    jmp     L1747
L1789:
L1747:
; break
    jmp     L1659
; }
    jmp     L1659
L1741:
    jmp     L1660
L1659:
; RPN'ized expression: "( L1793 printf ) "
; Expanded expression: " L1793  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1793:
    db  " ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1793 , printf )2 "
    push    L1793
    call    _printf
    sub     sp, -2
    sub     sp, -2
; }
    jmp     L1656
L1658:
; RPN'ized expression: "( L1795 printf ) "
; Expanded expression: " L1795  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1795:
    db  34,10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1795 , printf )2 "
    push    L1795
    call    _printf
    sub     sp, -2
; for
; RPN'ized expression: "i 0 = "
; Expanded expression: "(@-4) 0 =(2) "
; Fused expression:    "=(34) *(@-4) 0 "
    mov     ax, 0
    mov     [bp-4], ax
L1797:
; RPN'ized expression: "i sp < "
; Expanded expression: "(@-4) *(2) sp *(2) < "
; Fused expression:    "< *(@-4) *sp IF! "
    mov     ax, [bp-4]
    cmp     ax, [_sp]
    jge     L1800
    jmp     L1799
L1798:
; RPN'ized expression: "i ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
    mov     ax, [bp-4]
    inc     word [bp-4]
    jmp     L1797
L1799:
; {
; loc         tok : (@-6): int
    sub     sp, 2
; =
; RPN'ized expression: "stack i + *u 0 + *u "
; Expanded expression: "stack (@-4) *(2) 4 * + 0 + *(2) "
; Fused expression:    "* *(@-4) 4 + stack ax + ax 0 =(34) *(@-6) *ax "
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-6], ax
; loc         v : (@-8): int
    sub     sp, 2
; =
; RPN'ized expression: "stack i + *u 1 + *u "
; Expanded expression: "stack (@-4) *(2) 4 * + 2 + *(2) "
; Fused expression:    "* *(@-4) 4 + stack ax + ax 2 =(34) *(@-8) *ax "
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-8], ax
; loc         instr : (@-10): * char
    sub     sp, 2
; switch
; RPN'ized expression: "tok "
; Expanded expression: "(@-6) *(2) "
; Fused expression:    "*(2) (@-6) "
    mov     ax, [bp-6]
    jmp     L1803
; {
; case
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
    jmp     L1804
L1803:
    cmp     ax, 1
    jne     L1805
L1804:
; case
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
    jmp     L1806
L1805:
    cmp     ax, 2
    jne     L1807
L1806:
; if
; RPN'ized expression: "i 1 + sp < stack i 1 + + *u 0 + *u 44 == && 0 == "
; Expanded expression: "(@-4) *(2) 1 + sp *(2) < _Bool [sh&&->1811] stack (@-4) *(2) 1 + 4 * + 0 + *(2) 44 == _Bool &&[1811] 0 == "
; Fused expression:    "+ *(@-4) 1 < ax *sp _Bool [sh&&->1811] + *(@-4) 1 * ax 4 + stack ax + ax 0 == *ax 44 _Bool &&[1811] == ax 0 IF! "
    mov     ax, [bp-4]
    add     ax, 1
    cmp     ax, [_sp]
    setl    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L1811
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 44
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L1811:
    cmp     ax, 0
    jne     L1809
; RPN'ized expression: "( v , L1812 printf ) "
; Expanded expression: " (@-8) *(2)  L1812  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1812:
    db  "    mov     ax, %d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-8) , L1812 , printf )4 "
    push    word [bp-8]
    push    L1812
    call    _printf
    sub     sp, -4
L1809:
; break
    jmp     L1801
; case
; RPN'ized expression: "16 "
; Expanded expression: "16 "
; Expression value: 16
    jmp     L1808
L1807:
    cmp     ax, 16
    jne     L1814
L1808:
; if
; RPN'ized expression: "i 1 + sp < stack i 1 + + *u 0 + *u 44 == stack i 1 + + *u 0 + *u 41 == || && 0 == "
; Expanded expression: "(@-4) *(2) 1 + sp *(2) < _Bool [sh&&->1818] stack (@-4) *(2) 1 + 4 * + 0 + *(2) 44 == _Bool [sh||->1819] stack (@-4) *(2) 1 + 4 * + 0 + *(2) 41 == _Bool ||[1819] _Bool &&[1818] 0 == "
; Fused expression:    "+ *(@-4) 1 < ax *sp _Bool [sh&&->1818] + *(@-4) 1 * ax 4 + stack ax + ax 0 == *ax 44 _Bool [sh||->1819] + *(@-4) 1 * ax 4 + stack ax + ax 0 == *ax 41 _Bool ||[1819] _Bool &&[1818] == ax 0 IF! "
    mov     ax, [bp-4]
    add     ax, 1
    cmp     ax, [_sp]
    setl    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L1818
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 44
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L1819
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 41
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L1819:
    test    ax, ax
    setnz   al
    cbw
L1818:
    cmp     ax, 0
    jne     L1816
; {
; RPN'ized expression: "( L1820 printf ) "
; Expanded expression: " L1820  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1820:
    db  "    mov     ax, ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1820 , printf )2 "
    push    L1820
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( IdentTable v + GenPrintLabel ) "
; Expanded expression: " IdentTable (@-8) *(2) +  GenPrintLabel ()2 "
; Fused expression:    "( + IdentTable *(@-8) , GenPrintLabel )2 "
    mov     ax, _IdentTable
    add     ax, [bp-8]
    push    ax
    call    _GenPrintLabel
    sub     sp, -2
; RPN'ized expression: "( L1822 printf ) "
; Expanded expression: " L1822  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1822:
    db  10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1822 , printf )2 "
    push    L1822
    call    _printf
    sub     sp, -2
; }
L1816:
; break
    jmp     L1801
; case
; RPN'ized expression: "89 "
; Expanded expression: "89 "
; Expression value: 89
    jmp     L1815
L1814:
    cmp     ax, 89
    jne     L1824
L1815:
; RPN'ized expression: "( v , L1826 printf ) "
; Expanded expression: " (@-8) *(2)  L1826  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1826:
    db  "    lea     ax, [bp%+d]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-8) , L1826 , printf )4 "
    push    word [bp-8]
    push    L1826
    call    _printf
    sub     sp, -4
; break
    jmp     L1801
; case
; RPN'ized expression: "126 "
; Expanded expression: "126 "
; Expression value: 126
    jmp     L1825
L1824:
    cmp     ax, 126
    jne     L1828
L1825:
; RPN'ized expression: "( L1830 printf ) "
; Expanded expression: " L1830  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1830:
    db  "    not     ax",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1830 , printf )2 "
    push    L1830
    call    _printf
    sub     sp, -2
; break
    jmp     L1801
; case
; RPN'ized expression: "80 "
; Expanded expression: "80 "
; Expression value: 80
    jmp     L1829
L1828:
    cmp     ax, 80
    jne     L1832
L1829:
; RPN'ized expression: "( L1834 printf ) "
; Expanded expression: " L1834  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1834:
    db  "    neg     ax",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1834 , printf )2 "
    push    L1834
    call    _printf
    sub     sp, -2
; break
    jmp     L1801
; case
; RPN'ized expression: "120 "
; Expanded expression: "120 "
; Expression value: 120
    jmp     L1833
L1832:
    cmp     ax, 120
    jne     L1836
L1833:
; RPN'ized expression: "( L1838 printf ) "
; Expanded expression: " L1838  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1838:
    db  "    test    ax, ax",10,"    setnz   al",10,"    cbw",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1838 , printf )2 "
    push    L1838
    call    _printf
    sub     sp, -2
; break
    jmp     L1801
; case
; RPN'ized expression: "90 "
; Expanded expression: "90 "
; Expression value: 90
    jmp     L1837
L1836:
    cmp     ax, 90
    jne     L1840
L1837:
; if
; RPN'ized expression: "v 0 >= "
; Expanded expression: "(@-8) *(2) 0 >= "
; Fused expression:    ">= *(@-8) 0 IF! "
    mov     ax, [bp-8]
    cmp     ax, 0
    jl      L1842
; RPN'ized expression: "( v GenJumpIfZero ) "
; Expanded expression: " (@-8) *(2)  GenJumpIfZero ()2 "
; Fused expression:    "( *(2) (@-8) , GenJumpIfZero )2 "
    push    word [bp-8]
    call    _GenJumpIfZero
    sub     sp, -2
    jmp     L1843
L1842:
; else
; RPN'ized expression: "( v -u GenJumpIfNotZero ) "
; Expanded expression: " (@-8) *(2) -u  GenJumpIfNotZero ()2 "
; Fused expression:    "( *(2) (@-8) -u , GenJumpIfNotZero )2 "
    mov     ax, [bp-8]
    neg     ax
    push    ax
    call    _GenJumpIfNotZero
    sub     sp, -2
L1843:
; break
    jmp     L1801
; case
; RPN'ized expression: "6 "
; Expanded expression: "6 "
; Expression value: 6
    jmp     L1841
L1840:
    cmp     ax, 6
    jne     L1844
L1841:
; RPN'ized expression: "( v GenNumLabel ) "
; Expanded expression: " (@-8) *(2)  GenNumLabel ()2 "
; Fused expression:    "( *(2) (@-8) , GenNumLabel )2 "
    push    word [bp-8]
    call    _GenNumLabel
    sub     sp, -2
; break
    jmp     L1801
; case
; RPN'ized expression: "7 "
; Expanded expression: "7 "
; Expression value: 7
    jmp     L1845
L1844:
    cmp     ax, 7
    jne     L1846
L1845:
; RPN'ized expression: "( v GenNumLabel ) "
; Expanded expression: " (@-8) *(2)  GenNumLabel ()2 "
; Fused expression:    "( *(2) (@-8) , GenNumLabel )2 "
    push    word [bp-8]
    call    _GenNumLabel
    sub     sp, -2
; break
    jmp     L1801
; case
; RPN'ized expression: "512 "
; Expanded expression: "512 "
; Expression value: 512
    jmp     L1847
L1846:
    cmp     ax, 512
    jne     L1848
L1847:
; RPN'ized expression: "( L1850 printf ) "
; Expanded expression: " L1850  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1850:
    db  "    push    ax",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1850 , printf )2 "
    push    L1850
    call    _printf
    sub     sp, -2
; break
    jmp     L1801
; case
; RPN'ized expression: "44 "
; Expanded expression: "44 "
; Expression value: 44
    jmp     L1849
L1848:
    cmp     ax, 44
    jne     L1852
L1849:
; if
; RPN'ized expression: "stack i 2 - + *u 0 + *u 78 == stack i 2 - + *u 1 + *u 2 == && "
; Expanded expression: "stack (@-4) *(2) 2 - 4 * + 0 + *(2) 78 == _Bool [sh&&->1856] stack (@-4) *(2) 2 - 4 * + 2 + *(2) 2 == _Bool &&[1856] "
; Fused expression:    "- *(@-4) 2 * ax 4 + stack ax + ax 0 == *ax 78 _Bool [sh&&->1856] - *(@-4) 2 * ax 4 + stack ax + ax 2 == *ax 2 _Bool &&[1856] "
    mov     ax, [bp-4]
    sub     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 78
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L1856
    mov     ax, [bp-4]
    sub     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 2
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L1856:
; JumpIfZero
    test    ax, ax
    jz      L1854
; {
; switch
; RPN'ized expression: "stack i 1 - + *u 0 + *u "
; Expanded expression: "stack (@-4) *(2) 1 - 4 * + 0 + *(2) "
; Fused expression:    "- *(@-4) 1 * ax 4 + stack ax + ax 0 *(2) ax "
    mov     ax, [bp-4]
    sub     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    jmp     L1859
; {
; case
; RPN'ized expression: "257 "
; Expanded expression: "257 "
; Expression value: 257
    jmp     L1860
L1859:
    cmp     ax, 257
    jne     L1861
L1860:
; RPN'ized expression: "( L1863 printf ) "
; Expanded expression: " L1863  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1863:
    db  "    push    word [",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1863 , printf )2 "
    push    L1863
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( IdentTable stack i 1 - + *u 1 + *u + GenPrintLabel ) "
; Expanded expression: " IdentTable stack (@-4) *(2) 1 - 4 * + 2 + *(2) +  GenPrintLabel ()2 "
; Fused expression:    "( - *(@-4) 1 * ax 4 + stack ax + ax 2 + IdentTable *ax , GenPrintLabel )2 "
    mov     ax, [bp-4]
    sub     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, _IdentTable
    add     ax, cx
    push    ax
    call    _GenPrintLabel
    sub     sp, -2
; RPN'ized expression: "( L1865 printf ) "
; Expanded expression: " L1865  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1865:
    db  "]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1865 , printf )2 "
    push    L1865
    call    _printf
    sub     sp, -2
; break
    jmp     L1857
; case
; RPN'ized expression: "258 "
; Expanded expression: "258 "
; Expression value: 258
    jmp     L1862
L1861:
    cmp     ax, 258
    jne     L1867
L1862:
; RPN'ized expression: "( stack i 1 - + *u 1 + *u , L1869 printf ) "
; Expanded expression: " stack (@-4) *(2) 1 - 4 * + 2 + *(2)  L1869  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1869:
    db  "    push    word [bp%+d]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( - *(@-4) 1 * ax 4 + stack ax + ax 2 *(2) ax , L1869 , printf )4 "
    mov     ax, [bp-4]
    sub     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    L1869
    call    _printf
    sub     sp, -4
; break
    jmp     L1857
; case
; RPN'ized expression: "259 "
; Expanded expression: "259 "
; Expression value: 259
    jmp     L1868
L1867:
    cmp     ax, 259
    jne     L1871
L1868:
; RPN'ized expression: "( L1873 printf ) "
; Expanded expression: " L1873  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1873:
    db  "    mov     bx, ax",10,"    push    word [bx]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1873 , printf )2 "
    push    L1873
    call    _printf
    sub     sp, -2
; break
    jmp     L1857
; }
    jmp     L1857
L1871:
L1857:
; }
    jmp     L1855
L1854:
; else
; {
; switch
; RPN'ized expression: "stack i 1 - + *u 0 + *u "
; Expanded expression: "stack (@-4) *(2) 1 - 4 * + 0 + *(2) "
; Fused expression:    "- *(@-4) 1 * ax 4 + stack ax + ax 0 *(2) ax "
    mov     ax, [bp-4]
    sub     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    jmp     L1877
; {
; case
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
    jmp     L1878
L1877:
    cmp     ax, 1
    jne     L1879
L1878:
; case
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
    jmp     L1880
L1879:
    cmp     ax, 2
    jne     L1881
L1880:
; RPN'ized expression: "( stack i 1 - + *u 1 + *u , L1883 printf ) "
; Expanded expression: " stack (@-4) *(2) 1 - 4 * + 2 + *(2)  L1883  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L1883:
    db  "    push    %d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( - *(@-4) 1 * ax 4 + stack ax + ax 2 *(2) ax , L1883 , printf )4 "
    mov     ax, [bp-4]
    sub     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    L1883
    call    _printf
    sub     sp, -4
; break
    jmp     L1875
; case
; RPN'ized expression: "16 "
; Expanded expression: "16 "
; Expression value: 16
    jmp     L1882
L1881:
    cmp     ax, 16
    jne     L1885
L1882:
; RPN'ized expression: "( L1887 printf ) "
; Expanded expression: " L1887  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1887:
    db  "    push    ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1887 , printf )2 "
    push    L1887
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( IdentTable stack i 1 - + *u 1 + *u + GenPrintLabel ) "
; Expanded expression: " IdentTable stack (@-4) *(2) 1 - 4 * + 2 + *(2) +  GenPrintLabel ()2 "
; Fused expression:    "( - *(@-4) 1 * ax 4 + stack ax + ax 2 + IdentTable *ax , GenPrintLabel )2 "
    mov     ax, [bp-4]
    sub     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, _IdentTable
    add     ax, cx
    push    ax
    call    _GenPrintLabel
    sub     sp, -2
; RPN'ized expression: "( L1889 printf ) "
; Expanded expression: " L1889  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1889:
    db  10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1889 , printf )2 "
    push    L1889
    call    _printf
    sub     sp, -2
; break
    jmp     L1875
; default
L1876:
; RPN'ized expression: "( L1891 printf ) "
; Expanded expression: " L1891  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L1891:
    db  "    push    ax",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L1891 , printf )2 "
    push    L1891
    call    _printf
    sub     sp, -2
; break
    jmp     L1875
; }
    jmp     L1875
L1885:
    jmp     L1876
L1875:
; }
L1855:
; break
    jmp     L1801
; case
; RPN'ized expression: "78 "
; Expanded expression: "78 "
; Expression value: 78
    jmp     L1853
L1852:
    cmp     ax, 78
    jne     L1893
L1853:
; if
; RPN'ized expression: "v 2 == i 2 + sp < && stack i 2 + + *u 0 + *u 44 == && 0 == "
; Expanded expression: "(@-8) *(2) 2 == _Bool [sh&&->1898] (@-4) *(2) 2 + sp *(2) < _Bool &&[1898] _Bool [sh&&->1897] stack (@-4) *(2) 2 + 4 * + 0 + *(2) 44 == _Bool &&[1897] 0 == "
; Fused expression:    "== *(@-8) 2 _Bool [sh&&->1898] + *(@-4) 2 < ax *sp _Bool &&[1898] _Bool [sh&&->1897] + *(@-4) 2 * ax 4 + stack ax + ax 0 == *ax 44 _Bool &&[1897] == ax 0 IF! "
    mov     ax, [bp-8]
    cmp     ax, 2
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L1898
    mov     ax, [bp-4]
    add     ax, 2
    cmp     ax, [_sp]
    setl    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L1898:
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L1897
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 44
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L1897:
    cmp     ax, 0
    jne     L1895
; {
; switch
; RPN'ized expression: "stack i 1 + + *u 0 + *u "
; Expanded expression: "stack (@-4) *(2) 1 + 4 * + 0 + *(2) "
; Fused expression:    "+ *(@-4) 1 * ax 4 + stack ax + ax 0 *(2) ax "
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    jmp     L1901
; {
; case
; RPN'ized expression: "257 "
; Expanded expression: "257 "
; Expression value: 257
    jmp     L1902
L1901:
    cmp     ax, 257
    jne     L1903
L1902:
; RPN'ized expression: "( IdentTable stack i 1 + + *u 1 + *u + , v GenReadIdent ) "
; Expanded expression: " IdentTable stack (@-4) *(2) 1 + 4 * + 2 + *(2) +  (@-8) *(2)  GenReadIdent ()4 "
; Fused expression:    "( + *(@-4) 1 * ax 4 + stack ax + ax 2 + IdentTable *ax , *(2) (@-8) , GenReadIdent )4 "
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, _IdentTable
    add     ax, cx
    push    ax
    push    word [bp-8]
    call    _GenReadIdent
    sub     sp, -4
; break
    jmp     L1899
; case
; RPN'ized expression: "258 "
; Expanded expression: "258 "
; Expression value: 258
    jmp     L1904
L1903:
    cmp     ax, 258
    jne     L1905
L1904:
; RPN'ized expression: "( stack i 1 + + *u 1 + *u , v GenReadLocal ) "
; Expanded expression: " stack (@-4) *(2) 1 + 4 * + 2 + *(2)  (@-8) *(2)  GenReadLocal ()4 "
; Fused expression:    "( + *(@-4) 1 * ax 4 + stack ax + ax 2 *(2) ax , *(2) (@-8) , GenReadLocal )4 "
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    word [bp-8]
    call    _GenReadLocal
    sub     sp, -4
; break
    jmp     L1899
; case
; RPN'ized expression: "259 "
; Expanded expression: "259 "
; Expression value: 259
    jmp     L1906
L1905:
    cmp     ax, 259
    jne     L1907
L1906:
; RPN'ized expression: "( v GenReadIndirect ) "
; Expanded expression: " (@-8) *(2)  GenReadIndirect ()2 "
; Fused expression:    "( *(2) (@-8) , GenReadIndirect )2 "
    push    word [bp-8]
    call    _GenReadIndirect
    sub     sp, -2
; break
    jmp     L1899
; }
    jmp     L1899
L1907:
L1899:
; }
L1895:
; RPN'ized expression: "i ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
    mov     ax, [bp-4]
    inc     word [bp-4]
; break
    jmp     L1801
; case
; RPN'ized expression: "12 "
; Expanded expression: "12 "
; Expression value: 12
    jmp     L1894
L1893:
    cmp     ax, 12
    jne     L1909
L1894:
; case
; RPN'ized expression: "13 "
; Expanded expression: "13 "
; Expression value: 13
    jmp     L1910
L1909:
    cmp     ax, 13
    jne     L1911
L1910:
; switch
; RPN'ized expression: "stack i 1 + + *u 0 + *u "
; Expanded expression: "stack (@-4) *(2) 1 + 4 * + 0 + *(2) "
; Fused expression:    "+ *(@-4) 1 * ax 4 + stack ax + ax 0 *(2) ax "
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    jmp     L1915
; {
; case
; RPN'ized expression: "260 "
; Expanded expression: "260 "
; Expression value: 260
    jmp     L1916
L1915:
    cmp     ax, 260
    jne     L1917
L1916:
; RPN'ized expression: "( tok , IdentTable stack i 1 + + *u 1 + *u + , v GenIncDecIdent ) "
; Expanded expression: " (@-6) *(2)  IdentTable stack (@-4) *(2) 1 + 4 * + 2 + *(2) +  (@-8) *(2)  GenIncDecIdent ()6 "
; Fused expression:    "( *(2) (@-6) , + *(@-4) 1 * ax 4 + stack ax + ax 2 + IdentTable *ax , *(2) (@-8) , GenIncDecIdent )6 "
    push    word [bp-6]
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, _IdentTable
    add     ax, cx
    push    ax
    push    word [bp-8]
    call    _GenIncDecIdent
    sub     sp, -6
; break
    jmp     L1913
; case
; RPN'ized expression: "261 "
; Expanded expression: "261 "
; Expression value: 261
    jmp     L1918
L1917:
    cmp     ax, 261
    jne     L1919
L1918:
; RPN'ized expression: "( tok , stack i 1 + + *u 1 + *u , v GenIncDecLocal ) "
; Expanded expression: " (@-6) *(2)  stack (@-4) *(2) 1 + 4 * + 2 + *(2)  (@-8) *(2)  GenIncDecLocal ()6 "
; Fused expression:    "( *(2) (@-6) , + *(@-4) 1 * ax 4 + stack ax + ax 2 *(2) ax , *(2) (@-8) , GenIncDecLocal )6 "
    push    word [bp-6]
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    word [bp-8]
    call    _GenIncDecLocal
    sub     sp, -6
; break
    jmp     L1913
; case
; RPN'ized expression: "262 "
; Expanded expression: "262 "
; Expression value: 262
    jmp     L1920
L1919:
    cmp     ax, 262
    jne     L1921
L1920:
; RPN'ized expression: "( tok , v GenIncDecIndirect ) "
; Expanded expression: " (@-6) *(2)  (@-8) *(2)  GenIncDecIndirect ()4 "
; Fused expression:    "( *(2) (@-6) , *(2) (@-8) , GenIncDecIndirect )4 "
    push    word [bp-6]
    push    word [bp-8]
    call    _GenIncDecIndirect
    sub     sp, -4
; break
    jmp     L1913
; }
    jmp     L1913
L1921:
L1913:
; RPN'ized expression: "i ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
    mov     ax, [bp-4]
    inc     word [bp-4]
; break
    jmp     L1801
; case
; RPN'ized expression: "81 "
; Expanded expression: "81 "
; Expression value: 81
    jmp     L1912
L1911:
    cmp     ax, 81
    jne     L1923
L1912:
; case
; RPN'ized expression: "82 "
; Expanded expression: "82 "
; Expression value: 82
    jmp     L1924
L1923:
    cmp     ax, 82
    jne     L1925
L1924:
; switch
; RPN'ized expression: "stack i 1 + + *u 0 + *u "
; Expanded expression: "stack (@-4) *(2) 1 + 4 * + 0 + *(2) "
; Fused expression:    "+ *(@-4) 1 * ax 4 + stack ax + ax 0 *(2) ax "
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    jmp     L1929
; {
; case
; RPN'ized expression: "260 "
; Expanded expression: "260 "
; Expression value: 260
    jmp     L1930
L1929:
    cmp     ax, 260
    jne     L1931
L1930:
; RPN'ized expression: "( tok , IdentTable stack i 1 + + *u 1 + *u + , v GenPostIncDecIdent ) "
; Expanded expression: " (@-6) *(2)  IdentTable stack (@-4) *(2) 1 + 4 * + 2 + *(2) +  (@-8) *(2)  GenPostIncDecIdent ()6 "
; Fused expression:    "( *(2) (@-6) , + *(@-4) 1 * ax 4 + stack ax + ax 2 + IdentTable *ax , *(2) (@-8) , GenPostIncDecIdent )6 "
    push    word [bp-6]
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, _IdentTable
    add     ax, cx
    push    ax
    push    word [bp-8]
    call    _GenPostIncDecIdent
    sub     sp, -6
; break
    jmp     L1927
; case
; RPN'ized expression: "261 "
; Expanded expression: "261 "
; Expression value: 261
    jmp     L1932
L1931:
    cmp     ax, 261
    jne     L1933
L1932:
; RPN'ized expression: "( tok , stack i 1 + + *u 1 + *u , v GenPostIncDecLocal ) "
; Expanded expression: " (@-6) *(2)  stack (@-4) *(2) 1 + 4 * + 2 + *(2)  (@-8) *(2)  GenPostIncDecLocal ()6 "
; Fused expression:    "( *(2) (@-6) , + *(@-4) 1 * ax 4 + stack ax + ax 2 *(2) ax , *(2) (@-8) , GenPostIncDecLocal )6 "
    push    word [bp-6]
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    word [bp-8]
    call    _GenPostIncDecLocal
    sub     sp, -6
; break
    jmp     L1927
; case
; RPN'ized expression: "262 "
; Expanded expression: "262 "
; Expression value: 262
    jmp     L1934
L1933:
    cmp     ax, 262
    jne     L1935
L1934:
; RPN'ized expression: "( tok , v GenPostIncDecIndirect ) "
; Expanded expression: " (@-6) *(2)  (@-8) *(2)  GenPostIncDecIndirect ()4 "
; Fused expression:    "( *(2) (@-6) , *(2) (@-8) , GenPostIncDecIndirect )4 "
    push    word [bp-6]
    push    word [bp-8]
    call    _GenPostIncDecIndirect
    sub     sp, -4
; break
    jmp     L1927
; }
    jmp     L1927
L1935:
L1927:
; RPN'ized expression: "i ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
    mov     ax, [bp-4]
    inc     word [bp-4]
; break
    jmp     L1801
; case
; RPN'ized expression: "83 "
; Expanded expression: "83 "
; Expression value: 83
    jmp     L1926
L1925:
    cmp     ax, 83
    jne     L1937
L1926:
; case
; RPN'ized expression: "84 "
; Expanded expression: "84 "
; Expression value: 84
    jmp     L1938
L1937:
    cmp     ax, 84
    jne     L1939
L1938:
; switch
; RPN'ized expression: "stack i 1 + + *u 0 + *u "
; Expanded expression: "stack (@-4) *(2) 1 + 4 * + 0 + *(2) "
; Fused expression:    "+ *(@-4) 1 * ax 4 + stack ax + ax 0 *(2) ax "
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    jmp     L1943
; {
; case
; RPN'ized expression: "260 "
; Expanded expression: "260 "
; Expression value: 260
    jmp     L1944
L1943:
    cmp     ax, 260
    jne     L1945
L1944:
; RPN'ized expression: "( tok , IdentTable stack i 1 + + *u 1 + *u + , stack i 2 + + *u 1 + *u , v GenPostAddSubIdent ) "
; Expanded expression: " (@-6) *(2)  IdentTable stack (@-4) *(2) 1 + 4 * + 2 + *(2) +  stack (@-4) *(2) 2 + 4 * + 2 + *(2)  (@-8) *(2)  GenPostAddSubIdent ()8 "
; Fused expression:    "( *(2) (@-6) , + *(@-4) 1 * ax 4 + stack ax + ax 2 + IdentTable *ax , + *(@-4) 2 * ax 4 + stack ax + ax 2 *(2) ax , *(2) (@-8) , GenPostAddSubIdent )8 "
    push    word [bp-6]
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, _IdentTable
    add     ax, cx
    push    ax
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    word [bp-8]
    call    _GenPostAddSubIdent
    sub     sp, -8
; break
    jmp     L1941
; case
; RPN'ized expression: "261 "
; Expanded expression: "261 "
; Expression value: 261
    jmp     L1946
L1945:
    cmp     ax, 261
    jne     L1947
L1946:
; RPN'ized expression: "( tok , stack i 1 + + *u 1 + *u , stack i 2 + + *u 1 + *u , v GenPostAddSubLocal ) "
; Expanded expression: " (@-6) *(2)  stack (@-4) *(2) 1 + 4 * + 2 + *(2)  stack (@-4) *(2) 2 + 4 * + 2 + *(2)  (@-8) *(2)  GenPostAddSubLocal ()8 "
; Fused expression:    "( *(2) (@-6) , + *(@-4) 1 * ax 4 + stack ax + ax 2 *(2) ax , + *(@-4) 2 * ax 4 + stack ax + ax 2 *(2) ax , *(2) (@-8) , GenPostAddSubLocal )8 "
    push    word [bp-6]
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    word [bp-8]
    call    _GenPostAddSubLocal
    sub     sp, -8
; break
    jmp     L1941
; case
; RPN'ized expression: "262 "
; Expanded expression: "262 "
; Expression value: 262
    jmp     L1948
L1947:
    cmp     ax, 262
    jne     L1949
L1948:
; RPN'ized expression: "( tok , stack i 2 + + *u 1 + *u , v GenPostAddSubIndirect ) "
; Expanded expression: " (@-6) *(2)  stack (@-4) *(2) 2 + 4 * + 2 + *(2)  (@-8) *(2)  GenPostAddSubIndirect ()6 "
; Fused expression:    "( *(2) (@-6) , + *(@-4) 2 * ax 4 + stack ax + ax 2 *(2) ax , *(2) (@-8) , GenPostAddSubIndirect )6 "
    push    word [bp-6]
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    word [bp-8]
    call    _GenPostAddSubIndirect
    sub     sp, -6
; break
    jmp     L1941
; }
    jmp     L1941
L1949:
L1941:
; RPN'ized expression: "i 2 += "
; Expanded expression: "(@-4) 2 +=(2) "
; Fused expression:    "+=(34) *(@-4) 2 "
    mov     ax, [bp-4]
    add     ax, 2
    mov     [bp-4], ax
; break
    jmp     L1801
; case
; RPN'ized expression: "61 "
; Expanded expression: "61 "
; Expression value: 61
    jmp     L1940
L1939:
    cmp     ax, 61
    jne     L1951
L1940:
; case
; RPN'ized expression: "68 "
; Expanded expression: "68 "
; Expression value: 68
    jmp     L1952
L1951:
    cmp     ax, 68
    jne     L1953
L1952:
; case
; RPN'ized expression: "69 "
; Expanded expression: "69 "
; Expression value: 69
    jmp     L1954
L1953:
    cmp     ax, 69
    jne     L1955
L1954:
; case
; RPN'ized expression: "65 "
; Expanded expression: "65 "
; Expression value: 65
    jmp     L1956
L1955:
    cmp     ax, 65
    jne     L1957
L1956:
; case
; RPN'ized expression: "66 "
; Expanded expression: "66 "
; Expression value: 66
    jmp     L1958
L1957:
    cmp     ax, 66
    jne     L1959
L1958:
; case
; RPN'ized expression: "67 "
; Expanded expression: "67 "
; Expression value: 67
    jmp     L1960
L1959:
    cmp     ax, 67
    jne     L1961
L1960:
; case
; RPN'ized expression: "70 "
; Expanded expression: "70 "
; Expression value: 70
    jmp     L1962
L1961:
    cmp     ax, 70
    jne     L1963
L1962:
; case
; RPN'ized expression: "71 "
; Expanded expression: "71 "
; Expression value: 71
    jmp     L1964
L1963:
    cmp     ax, 71
    jne     L1965
L1964:
; case
; RPN'ized expression: "72 "
; Expanded expression: "72 "
; Expression value: 72
    jmp     L1966
L1965:
    cmp     ax, 72
    jne     L1967
L1966:
; case
; RPN'ized expression: "73 "
; Expanded expression: "73 "
; Expression value: 73
    jmp     L1968
L1967:
    cmp     ax, 73
    jne     L1969
L1968:
; case
; RPN'ized expression: "74 "
; Expanded expression: "74 "
; Expression value: 74
    jmp     L1970
L1969:
    cmp     ax, 74
    jne     L1971
L1970:
; case
; RPN'ized expression: "43 "
; Expanded expression: "43 "
; Expression value: 43
    jmp     L1972
L1971:
    cmp     ax, 43
    jne     L1973
L1972:
; case
; RPN'ized expression: "45 "
; Expanded expression: "45 "
; Expression value: 45
    jmp     L1974
L1973:
    cmp     ax, 45
    jne     L1975
L1974:
; case
; RPN'ized expression: "42 "
; Expanded expression: "42 "
; Expression value: 42
    jmp     L1976
L1975:
    cmp     ax, 42
    jne     L1977
L1976:
; case
; RPN'ized expression: "47 "
; Expanded expression: "47 "
; Expression value: 47
    jmp     L1978
L1977:
    cmp     ax, 47
    jne     L1979
L1978:
; case
; RPN'ized expression: "37 "
; Expanded expression: "37 "
; Expression value: 37
    jmp     L1980
L1979:
    cmp     ax, 37
    jne     L1981
L1980:
; case
; RPN'ized expression: "4 "
; Expanded expression: "4 "
; Expression value: 4
    jmp     L1982
L1981:
    cmp     ax, 4
    jne     L1983
L1982:
; case
; RPN'ized expression: "5 "
; Expanded expression: "5 "
; Expression value: 5
    jmp     L1984
L1983:
    cmp     ax, 5
    jne     L1985
L1984:
; case
; RPN'ized expression: "38 "
; Expanded expression: "38 "
; Expression value: 38
    jmp     L1986
L1985:
    cmp     ax, 38
    jne     L1987
L1986:
; case
; RPN'ized expression: "94 "
; Expanded expression: "94 "
; Expression value: 94
    jmp     L1988
L1987:
    cmp     ax, 94
    jne     L1989
L1988:
; case
; RPN'ized expression: "124 "
; Expanded expression: "124 "
; Expression value: 124
    jmp     L1990
L1989:
    cmp     ax, 124
    jne     L1991
L1990:
; case
; RPN'ized expression: "60 "
; Expanded expression: "60 "
; Expression value: 60
    jmp     L1992
L1991:
    cmp     ax, 60
    jne     L1993
L1992:
; case
; RPN'ized expression: "62 "
; Expanded expression: "62 "
; Expression value: 62
    jmp     L1994
L1993:
    cmp     ax, 62
    jne     L1995
L1994:
; case
; RPN'ized expression: "10 "
; Expanded expression: "10 "
; Expression value: 10
    jmp     L1996
L1995:
    cmp     ax, 10
    jne     L1997
L1996:
; case
; RPN'ized expression: "11 "
; Expanded expression: "11 "
; Expression value: 11
    jmp     L1998
L1997:
    cmp     ax, 11
    jne     L1999
L1998:
; case
; RPN'ized expression: "8 "
; Expanded expression: "8 "
; Expression value: 8
    jmp     L2000
L1999:
    cmp     ax, 8
    jne     L2001
L2000:
; case
; RPN'ized expression: "9 "
; Expanded expression: "9 "
; Expression value: 9
    jmp     L2002
L2001:
    cmp     ax, 9
    jne     L2003
L2002:
; case
; RPN'ized expression: "85 "
; Expanded expression: "85 "
; Expression value: 85
    jmp     L2004
L2003:
    cmp     ax, 85
    jne     L2005
L2004:
; case
; RPN'ized expression: "86 "
; Expanded expression: "86 "
; Expression value: 86
    jmp     L2006
L2005:
    cmp     ax, 86
    jne     L2007
L2006:
; case
; RPN'ized expression: "87 "
; Expanded expression: "87 "
; Expression value: 87
    jmp     L2008
L2007:
    cmp     ax, 87
    jne     L2009
L2008:
; case
; RPN'ized expression: "88 "
; Expanded expression: "88 "
; Expression value: 88
    jmp     L2010
L2009:
    cmp     ax, 88
    jne     L2011
L2010:
; if
; RPN'ized expression: "tok 61 != "
; Expanded expression: "(@-6) *(2) 61 != "
; Fused expression:    "!= *(@-6) 61 IF! "
    mov     ax, [bp-6]
    cmp     ax, 61
    je      L2013
; {
; if
; RPN'ized expression: "stack i 2 + + *u 0 + *u 259 == "
; Expanded expression: "stack (@-4) *(2) 2 + 4 * + 0 + *(2) 259 == "
; Fused expression:    "+ *(@-4) 2 * ax 4 + stack ax + ax 0 == *ax 259 IF! "
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 259
    jne     L2015
; {
; RPN'ized expression: "( L2017 printf ) "
; Expanded expression: " L2017  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2017:
    db  "    mov     cx, ax",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2017 , printf )2 "
    push    L2017
    call    _printf
    sub     sp, -2
; }
    jmp     L2016
L2015:
; else
; if
; RPN'ized expression: "stack i 2 + + *u 0 + *u 262 == "
; Expanded expression: "stack (@-4) *(2) 2 + 4 * + 0 + *(2) 262 == "
; Fused expression:    "+ *(@-4) 2 * ax 4 + stack ax + ax 0 == *ax 262 IF! "
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 262
    jne     L2019
; {
; RPN'ized expression: "( L2021 printf ) "
; Expanded expression: " L2021  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2021:
    db  "    mov     bx, ax",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2021 , printf )2 "
    push    L2021
    call    _printf
    sub     sp, -2
; if
; RPN'ized expression: "v 16 % 1 == "
; Expanded expression: "(@-8) *(2) 16 % 1 == "
; Fused expression:    "% *(@-8) 16 == ax 1 IF! "
    mov     ax, [bp-8]
    cwd
    mov     cx, 16
    idiv    cx
    mov     ax, dx
    cmp     ax, 1
    jne     L2023
; {
; if
; RPN'ized expression: "CharIsSigned "
; Expanded expression: "CharIsSigned *(2) "
; Fused expression:    "*(2) CharIsSigned "
    mov     ax, [_CharIsSigned]
; JumpIfZero
    test    ax, ax
    jz      L2025
; RPN'ized expression: "( L2027 printf ) "
; Expanded expression: " L2027  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2027:
    db  "    movsx   cx, byte [bx]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2027 , printf )2 "
    push    L2027
    call    _printf
    sub     sp, -2
    jmp     L2026
L2025:
; else
; RPN'ized expression: "( L2029 printf ) "
; Expanded expression: " L2029  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2029:
    db  "    movzx   cx, byte [bx]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2029 , printf )2 "
    push    L2029
    call    _printf
    sub     sp, -2
L2026:
; }
    jmp     L2024
L2023:
; else
; if
; RPN'ized expression: "v 16 % 2 == "
; Expanded expression: "(@-8) *(2) 16 % 2 == "
; Fused expression:    "% *(@-8) 16 == ax 2 IF! "
    mov     ax, [bp-8]
    cwd
    mov     cx, 16
    idiv    cx
    mov     ax, dx
    cmp     ax, 2
    jne     L2031
; RPN'ized expression: "( L2033 printf ) "
; Expanded expression: " L2033  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2033:
    db  "    mov     cx, [bx]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2033 , printf )2 "
    push    L2033
    call    _printf
    sub     sp, -2
L2031:
L2024:
; }
L2019:
L2016:
; }
L2013:
; if
; RPN'ized expression: "tok 61 == "
; Expanded expression: "(@-6) *(2) 61 == "
; Fused expression:    "== *(@-6) 61 IF! "
    mov     ax, [bp-6]
    cmp     ax, 61
    jne     L2035
; {
; if
; RPN'ized expression: "stack i 1 + + *u 0 + *u 262 == "
; Expanded expression: "stack (@-4) *(2) 1 + 4 * + 0 + *(2) 262 == "
; Fused expression:    "+ *(@-4) 1 * ax 4 + stack ax + ax 0 == *ax 262 IF! "
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 262
    jne     L2037
; RPN'ized expression: "( L2039 printf ) "
; Expanded expression: " L2039  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2039:
    db  "    mov     bx, ax",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2039 , printf )2 "
    push    L2039
    call    _printf
    sub     sp, -2
L2037:
; RPN'ized expression: "i ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
    mov     ax, [bp-4]
    inc     word [bp-4]
; RPN'ized expression: "v v 16 / v 16 % 16 * + = "
; Expanded expression: "(@-8) (@-8) *(2) 16 / (@-8) *(2) 16 % 16 * + =(2) "
; Fused expression:    "/ *(@-8) 16 push-ax % *(@-8) 16 * ax 16 + *sp ax =(34) *(@-8) ax "
    mov     ax, [bp-8]
    cwd
    mov     cx, 16
    idiv    cx
    push    ax
    mov     ax, [bp-8]
    cwd
    mov     cx, 16
    idiv    cx
    mov     ax, dx
    imul    ax, ax, 16
    mov     cx, ax
    pop     ax
    add     ax, cx
    mov     [bp-8], ax
; }
L2035:
; switch
; RPN'ized expression: "stack i 1 + + *u 0 + *u "
; Expanded expression: "stack (@-4) *(2) 1 + 4 * + 0 + *(2) "
; Fused expression:    "+ *(@-4) 1 * ax 4 + stack ax + ax 0 *(2) ax "
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    jmp     L2043
; {
; case
; RPN'ized expression: "256 "
; Expanded expression: "256 "
; Expression value: 256
    jmp     L2044
L2043:
    cmp     ax, 256
    jne     L2045
L2044:
; RPN'ized expression: "( stack i 1 + + *u 1 + *u , L2047 printf ) "
; Expanded expression: " stack (@-4) *(2) 1 + 4 * + 2 + *(2)  L2047  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2047:
    db  "    mov     ax, %d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( + *(@-4) 1 * ax 4 + stack ax + ax 2 *(2) ax , L2047 , printf )4 "
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    L2047
    call    _printf
    sub     sp, -4
; break
    jmp     L2041
; case
; RPN'ized expression: "257 "
; Expanded expression: "257 "
; Expression value: 257
    jmp     L2046
L2045:
    cmp     ax, 257
    jne     L2049
L2046:
; RPN'ized expression: "( L2051 printf ) "
; Expanded expression: " L2051  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2051:
    db  "    mov     ax, ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2051 , printf )2 "
    push    L2051
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( IdentTable stack i 1 + + *u 1 + *u + GenPrintLabel ) "
; Expanded expression: " IdentTable stack (@-4) *(2) 1 + 4 * + 2 + *(2) +  GenPrintLabel ()2 "
; Fused expression:    "( + *(@-4) 1 * ax 4 + stack ax + ax 2 + IdentTable *ax , GenPrintLabel )2 "
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, _IdentTable
    add     ax, cx
    push    ax
    call    _GenPrintLabel
    sub     sp, -2
; RPN'ized expression: "( L2053 printf ) "
; Expanded expression: " L2053  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2053:
    db  10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2053 , printf )2 "
    push    L2053
    call    _printf
    sub     sp, -2
; break
    jmp     L2041
; case
; RPN'ized expression: "258 "
; Expanded expression: "258 "
; Expression value: 258
    jmp     L2050
L2049:
    cmp     ax, 258
    jne     L2055
L2050:
; RPN'ized expression: "( stack i 1 + + *u 1 + *u , L2057 printf ) "
; Expanded expression: " stack (@-4) *(2) 1 + 4 * + 2 + *(2)  L2057  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2057:
    db  "    lea     ax, [bp%+d]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( + *(@-4) 1 * ax 4 + stack ax + ax 2 *(2) ax , L2057 , printf )4 "
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    L2057
    call    _printf
    sub     sp, -4
; break
    jmp     L2041
; case
; RPN'ized expression: "259 "
; Expanded expression: "259 "
; Expression value: 259
    jmp     L2056
L2055:
    cmp     ax, 259
    jne     L2059
L2056:
; break
    jmp     L2041
; case
; RPN'ized expression: "260 "
; Expanded expression: "260 "
; Expression value: 260
    jmp     L2060
L2059:
    cmp     ax, 260
    jne     L2061
L2060:
; if
; RPN'ized expression: "v 16 / 1 == "
; Expanded expression: "(@-8) *(2) 16 / 1 == "
; Fused expression:    "/ *(@-8) 16 == ax 1 IF! "
    mov     ax, [bp-8]
    cwd
    mov     cx, 16
    idiv    cx
    cmp     ax, 1
    jne     L2063
; {
; RPN'ized expression: "( L2065 printf ) "
; Expanded expression: " L2065  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2065:
    db  "    mov     al, [",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2065 , printf )2 "
    push    L2065
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( IdentTable stack i 1 + + *u 1 + *u + GenPrintLabel ) "
; Expanded expression: " IdentTable stack (@-4) *(2) 1 + 4 * + 2 + *(2) +  GenPrintLabel ()2 "
; Fused expression:    "( + *(@-4) 1 * ax 4 + stack ax + ax 2 + IdentTable *ax , GenPrintLabel )2 "
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, _IdentTable
    add     ax, cx
    push    ax
    call    _GenPrintLabel
    sub     sp, -2
; RPN'ized expression: "( L2067 printf ) "
; Expanded expression: " L2067  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2067:
    db  "]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2067 , printf )2 "
    push    L2067
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( GenExtendAlAx ) "
; Expanded expression: " GenExtendAlAx ()0 "
; Fused expression:    "( GenExtendAlAx )0 "
    call    _GenExtendAlAx
; }
    jmp     L2064
L2063:
; else
; if
; RPN'ized expression: "v 16 / 2 == "
; Expanded expression: "(@-8) *(2) 16 / 2 == "
; Fused expression:    "/ *(@-8) 16 == ax 2 IF! "
    mov     ax, [bp-8]
    cwd
    mov     cx, 16
    idiv    cx
    cmp     ax, 2
    jne     L2069
; {
; RPN'ized expression: "( L2071 printf ) "
; Expanded expression: " L2071  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2071:
    db  "    mov     ax, [",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2071 , printf )2 "
    push    L2071
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( IdentTable stack i 1 + + *u 1 + *u + GenPrintLabel ) "
; Expanded expression: " IdentTable stack (@-4) *(2) 1 + 4 * + 2 + *(2) +  GenPrintLabel ()2 "
; Fused expression:    "( + *(@-4) 1 * ax 4 + stack ax + ax 2 + IdentTable *ax , GenPrintLabel )2 "
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, _IdentTable
    add     ax, cx
    push    ax
    call    _GenPrintLabel
    sub     sp, -2
; RPN'ized expression: "( L2073 printf ) "
; Expanded expression: " L2073  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2073:
    db  "]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2073 , printf )2 "
    push    L2073
    call    _printf
    sub     sp, -2
; }
L2069:
L2064:
; break
    jmp     L2041
; case
; RPN'ized expression: "261 "
; Expanded expression: "261 "
; Expression value: 261
    jmp     L2062
L2061:
    cmp     ax, 261
    jne     L2075
L2062:
; if
; RPN'ized expression: "v 16 / 1 == "
; Expanded expression: "(@-8) *(2) 16 / 1 == "
; Fused expression:    "/ *(@-8) 16 == ax 1 IF! "
    mov     ax, [bp-8]
    cwd
    mov     cx, 16
    idiv    cx
    cmp     ax, 1
    jne     L2077
; {
; RPN'ized expression: "( stack i 1 + + *u 1 + *u , L2079 printf ) "
; Expanded expression: " stack (@-4) *(2) 1 + 4 * + 2 + *(2)  L2079  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2079:
    db  "    mov     al, [bp%+d]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( + *(@-4) 1 * ax 4 + stack ax + ax 2 *(2) ax , L2079 , printf )4 "
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    L2079
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( GenExtendAlAx ) "
; Expanded expression: " GenExtendAlAx ()0 "
; Fused expression:    "( GenExtendAlAx )0 "
    call    _GenExtendAlAx
; }
    jmp     L2078
L2077:
; else
; if
; RPN'ized expression: "v 16 / 2 == "
; Expanded expression: "(@-8) *(2) 16 / 2 == "
; Fused expression:    "/ *(@-8) 16 == ax 2 IF! "
    mov     ax, [bp-8]
    cwd
    mov     cx, 16
    idiv    cx
    cmp     ax, 2
    jne     L2081
; RPN'ized expression: "( stack i 1 + + *u 1 + *u , L2083 printf ) "
; Expanded expression: " stack (@-4) *(2) 1 + 4 * + 2 + *(2)  L2083  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2083:
    db  "    mov     ax, [bp%+d]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( + *(@-4) 1 * ax 4 + stack ax + ax 2 *(2) ax , L2083 , printf )4 "
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    L2083
    call    _printf
    sub     sp, -4
L2081:
L2078:
; break
    jmp     L2041
; case
; RPN'ized expression: "262 "
; Expanded expression: "262 "
; Expression value: 262
    jmp     L2076
L2075:
    cmp     ax, 262
    jne     L2085
L2076:
; RPN'ized expression: "( L2087 printf ) "
; Expanded expression: " L2087  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2087:
    db  "    mov     bx, ax",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2087 , printf )2 "
    push    L2087
    call    _printf
    sub     sp, -2
; if
; RPN'ized expression: "v 16 / 1 == "
; Expanded expression: "(@-8) *(2) 16 / 1 == "
; Fused expression:    "/ *(@-8) 16 == ax 1 IF! "
    mov     ax, [bp-8]
    cwd
    mov     cx, 16
    idiv    cx
    cmp     ax, 1
    jne     L2089
; {
; RPN'ized expression: "( L2091 printf ) "
; Expanded expression: " L2091  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2091:
    db  "    mov     al, [bx]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2091 , printf )2 "
    push    L2091
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( GenExtendAlAx ) "
; Expanded expression: " GenExtendAlAx ()0 "
; Fused expression:    "( GenExtendAlAx )0 "
    call    _GenExtendAlAx
; }
    jmp     L2090
L2089:
; else
; if
; RPN'ized expression: "v 16 / 2 == "
; Expanded expression: "(@-8) *(2) 16 / 2 == "
; Fused expression:    "/ *(@-8) 16 == ax 2 IF! "
    mov     ax, [bp-8]
    cwd
    mov     cx, 16
    idiv    cx
    cmp     ax, 2
    jne     L2093
; RPN'ized expression: "( L2095 printf ) "
; Expanded expression: " L2095  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2095:
    db  "    mov     ax, [bx]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2095 , printf )2 "
    push    L2095
    call    _printf
    sub     sp, -2
L2093:
L2090:
; break
    jmp     L2041
; case
; RPN'ized expression: "263 "
; Expanded expression: "263 "
; Expression value: 263
    jmp     L2086
L2085:
    cmp     ax, 263
    jne     L2097
L2086:
; RPN'ized expression: "( L2099 printf ) "
; Expanded expression: " L2099  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2099:
    db  "    pop     ax",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2099 , printf )2 "
    push    L2099
    call    _printf
    sub     sp, -2
; break
    jmp     L2041
; case
; RPN'ized expression: "264 "
; Expanded expression: "264 "
; Expression value: 264
    jmp     L2098
L2097:
    cmp     ax, 264
    jne     L2101
L2098:
; RPN'ized expression: "( L2103 printf ) "
; Expanded expression: " L2103  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2103:
    db  "    pop     bx",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2103 , printf )2 "
    push    L2103
    call    _printf
    sub     sp, -2
; if
; RPN'ized expression: "v 16 / 1 == "
; Expanded expression: "(@-8) *(2) 16 / 1 == "
; Fused expression:    "/ *(@-8) 16 == ax 1 IF! "
    mov     ax, [bp-8]
    cwd
    mov     cx, 16
    idiv    cx
    cmp     ax, 1
    jne     L2105
; {
; RPN'ized expression: "( L2107 printf ) "
; Expanded expression: " L2107  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2107:
    db  "    mov     al, [bx]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2107 , printf )2 "
    push    L2107
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( GenExtendAlAx ) "
; Expanded expression: " GenExtendAlAx ()0 "
; Fused expression:    "( GenExtendAlAx )0 "
    call    _GenExtendAlAx
; }
    jmp     L2106
L2105:
; else
; if
; RPN'ized expression: "v 16 / 2 == "
; Expanded expression: "(@-8) *(2) 16 / 2 == "
; Fused expression:    "/ *(@-8) 16 == ax 2 IF! "
    mov     ax, [bp-8]
    cwd
    mov     cx, 16
    idiv    cx
    cmp     ax, 2
    jne     L2109
; RPN'ized expression: "( L2111 printf ) "
; Expanded expression: " L2111  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2111:
    db  "    mov     ax, [bx]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2111 , printf )2 "
    push    L2111
    call    _printf
    sub     sp, -2
L2109:
L2106:
; break
    jmp     L2041
; }
    jmp     L2041
L2101:
L2041:
; if
; RPN'ized expression: "tok 61 == "
; Expanded expression: "(@-6) *(2) 61 == "
; Fused expression:    "== *(@-6) 61 IF! "
    mov     ax, [bp-6]
    cmp     ax, 61
    jne     L2113
; {
; RPN'ized expression: "i --p "
; Expanded expression: "(@-4) --p(2) "
; Fused expression:    "--p(2) *(@-4) "
    mov     ax, [bp-4]
    dec     word [bp-4]
; RPN'ized expression: "v v 16 / v 16 % 16 * + = "
; Expanded expression: "(@-8) (@-8) *(2) 16 / (@-8) *(2) 16 % 16 * + =(2) "
; Fused expression:    "/ *(@-8) 16 push-ax % *(@-8) 16 * ax 16 + *sp ax =(34) *(@-8) ax "
    mov     ax, [bp-8]
    cwd
    mov     cx, 16
    idiv    cx
    push    ax
    mov     ax, [bp-8]
    cwd
    mov     cx, 16
    idiv    cx
    mov     ax, dx
    imul    ax, ax, 16
    mov     cx, ax
    pop     ax
    add     ax, cx
    mov     [bp-8], ax
; if
; RPN'ized expression: "stack i 1 + + *u 0 + *u 264 == "
; Expanded expression: "stack (@-4) *(2) 1 + 4 * + 0 + *(2) 264 == "
; Fused expression:    "+ *(@-4) 1 * ax 4 + stack ax + ax 0 == *ax 264 IF! "
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 264
    jne     L2115
; RPN'ized expression: "( L2117 printf ) "
; Expanded expression: " L2117  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2117:
    db  "    pop     bx",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2117 , printf )2 "
    push    L2117
    call    _printf
    sub     sp, -2
L2115:
; }
L2113:
; switch
; RPN'ized expression: "tok "
; Expanded expression: "(@-6) *(2) "
; Fused expression:    "*(2) (@-6) "
    mov     ax, [bp-6]
    jmp     L2121
; {
; case
; RPN'ized expression: "68 "
; Expanded expression: "68 "
; Expression value: 68
    jmp     L2122
L2121:
    cmp     ax, 68
    jne     L2123
L2122:
; case
; RPN'ized expression: "69 "
; Expanded expression: "69 "
; Expression value: 69
    jmp     L2124
L2123:
    cmp     ax, 69
    jne     L2125
L2124:
; case
; RPN'ized expression: "72 "
; Expanded expression: "72 "
; Expression value: 72
    jmp     L2126
L2125:
    cmp     ax, 72
    jne     L2127
L2126:
; case
; RPN'ized expression: "73 "
; Expanded expression: "73 "
; Expression value: 73
    jmp     L2128
L2127:
    cmp     ax, 73
    jne     L2129
L2128:
; case
; RPN'ized expression: "74 "
; Expanded expression: "74 "
; Expression value: 74
    jmp     L2130
L2129:
    cmp     ax, 74
    jne     L2131
L2130:
; case
; RPN'ized expression: "43 "
; Expanded expression: "43 "
; Expression value: 43
    jmp     L2132
L2131:
    cmp     ax, 43
    jne     L2133
L2132:
; case
; RPN'ized expression: "45 "
; Expanded expression: "45 "
; Expression value: 45
    jmp     L2134
L2133:
    cmp     ax, 45
    jne     L2135
L2134:
; case
; RPN'ized expression: "38 "
; Expanded expression: "38 "
; Expression value: 38
    jmp     L2136
L2135:
    cmp     ax, 38
    jne     L2137
L2136:
; case
; RPN'ized expression: "94 "
; Expanded expression: "94 "
; Expression value: 94
    jmp     L2138
L2137:
    cmp     ax, 94
    jne     L2139
L2138:
; case
; RPN'ized expression: "124 "
; Expanded expression: "124 "
; Expression value: 124
    jmp     L2140
L2139:
    cmp     ax, 124
    jne     L2141
L2140:
; case
; RPN'ized expression: "60 "
; Expanded expression: "60 "
; Expression value: 60
    jmp     L2142
L2141:
    cmp     ax, 60
    jne     L2143
L2142:
; case
; RPN'ized expression: "62 "
; Expanded expression: "62 "
; Expression value: 62
    jmp     L2144
L2143:
    cmp     ax, 62
    jne     L2145
L2144:
; case
; RPN'ized expression: "10 "
; Expanded expression: "10 "
; Expression value: 10
    jmp     L2146
L2145:
    cmp     ax, 10
    jne     L2147
L2146:
; case
; RPN'ized expression: "11 "
; Expanded expression: "11 "
; Expression value: 11
    jmp     L2148
L2147:
    cmp     ax, 11
    jne     L2149
L2148:
; case
; RPN'ized expression: "8 "
; Expanded expression: "8 "
; Expression value: 8
    jmp     L2150
L2149:
    cmp     ax, 8
    jne     L2151
L2150:
; case
; RPN'ized expression: "9 "
; Expanded expression: "9 "
; Expression value: 9
    jmp     L2152
L2151:
    cmp     ax, 9
    jne     L2153
L2152:
; case
; RPN'ized expression: "85 "
; Expanded expression: "85 "
; Expression value: 85
    jmp     L2154
L2153:
    cmp     ax, 85
    jne     L2155
L2154:
; case
; RPN'ized expression: "86 "
; Expanded expression: "86 "
; Expression value: 86
    jmp     L2156
L2155:
    cmp     ax, 86
    jne     L2157
L2156:
; case
; RPN'ized expression: "87 "
; Expanded expression: "87 "
; Expression value: 87
    jmp     L2158
L2157:
    cmp     ax, 87
    jne     L2159
L2158:
; case
; RPN'ized expression: "88 "
; Expanded expression: "88 "
; Expression value: 88
    jmp     L2160
L2159:
    cmp     ax, 88
    jne     L2161
L2160:
; RPN'ized expression: "instr ( tok GenGetBinaryOperatorInstr ) = "
; Expanded expression: "(@-10)  (@-6) *(2)  GenGetBinaryOperatorInstr ()2 =(2) "
; Fused expression:    "( *(2) (@-6) , GenGetBinaryOperatorInstr )2 =(34) *(@-10) ax "
    push    word [bp-6]
    call    _GenGetBinaryOperatorInstr
    sub     sp, -2
    mov     [bp-10], ax
; switch
; RPN'ized expression: "stack i 2 + + *u 0 + *u "
; Expanded expression: "stack (@-4) *(2) 2 + 4 * + 0 + *(2) "
; Fused expression:    "+ *(@-4) 2 * ax 4 + stack ax + ax 0 *(2) ax "
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    jmp     L2165
; {
; case
; RPN'ized expression: "256 "
; Expanded expression: "256 "
; Expression value: 256
    jmp     L2166
L2165:
    cmp     ax, 256
    jne     L2167
L2166:
; RPN'ized expression: "( stack i 2 + + *u 1 + *u , instr , L2169 printf ) "
; Expanded expression: " stack (@-4) *(2) 2 + 4 * + 2 + *(2)  (@-10) *(2)  L2169  printf ()6 "
; SEGMENT _TEXT
SEGMENT _DATA
L2169:
    db  "    %-4s    ax, %d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( + *(@-4) 2 * ax 4 + stack ax + ax 2 *(2) ax , *(2) (@-10) , L2169 , printf )6 "
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    word [bp-10]
    push    L2169
    call    _printf
    sub     sp, -6
; break
    jmp     L2163
; case
; RPN'ized expression: "257 "
; Expanded expression: "257 "
; Expression value: 257
    jmp     L2168
L2167:
    cmp     ax, 257
    jne     L2171
L2168:
; RPN'ized expression: "( instr , L2173 printf ) "
; Expanded expression: " (@-10) *(2)  L2173  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2173:
    db  "    %-4s    ax, ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-10) , L2173 , printf )4 "
    push    word [bp-10]
    push    L2173
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( IdentTable stack i 2 + + *u 1 + *u + GenPrintLabel ) "
; Expanded expression: " IdentTable stack (@-4) *(2) 2 + 4 * + 2 + *(2) +  GenPrintLabel ()2 "
; Fused expression:    "( + *(@-4) 2 * ax 4 + stack ax + ax 2 + IdentTable *ax , GenPrintLabel )2 "
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, _IdentTable
    add     ax, cx
    push    ax
    call    _GenPrintLabel
    sub     sp, -2
; RPN'ized expression: "( L2175 printf ) "
; Expanded expression: " L2175  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2175:
    db  10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2175 , printf )2 "
    push    L2175
    call    _printf
    sub     sp, -2
; break
    jmp     L2163
; case
; RPN'ized expression: "258 "
; Expanded expression: "258 "
; Expression value: 258
    jmp     L2172
L2171:
    cmp     ax, 258
    jne     L2177
L2172:
; RPN'ized expression: "( instr , stack i 2 + + *u 1 + *u , L2179 printf ) "
; Expanded expression: " (@-10) *(2)  stack (@-4) *(2) 2 + 4 * + 2 + *(2)  L2179  printf ()6 "
; SEGMENT _TEXT
SEGMENT _DATA
L2179:
    db  "    lea     cx, [bp%+d]",10,"    %-4s    ax, cx",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-10) , + *(@-4) 2 * ax 4 + stack ax + ax 2 *(2) ax , L2179 , printf )6 "
    push    word [bp-10]
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    L2179
    call    _printf
    sub     sp, -6
; break
    jmp     L2163
; case
; RPN'ized expression: "259 "
; Expanded expression: "259 "
; Expression value: 259
    jmp     L2178
L2177:
    cmp     ax, 259
    jne     L2181
L2178:
; case
; RPN'ized expression: "262 "
; Expanded expression: "262 "
; Expression value: 262
    jmp     L2182
L2181:
    cmp     ax, 262
    jne     L2183
L2182:
; RPN'ized expression: "( instr , L2185 printf ) "
; Expanded expression: " (@-10) *(2)  L2185  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2185:
    db  "    %-4s    ax, cx",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-10) , L2185 , printf )4 "
    push    word [bp-10]
    push    L2185
    call    _printf
    sub     sp, -4
; break
    jmp     L2163
; case
; RPN'ized expression: "260 "
; Expanded expression: "260 "
; Expression value: 260
    jmp     L2184
L2183:
    cmp     ax, 260
    jne     L2187
L2184:
; if
; RPN'ized expression: "v 16 % 1 == "
; Expanded expression: "(@-8) *(2) 16 % 1 == "
; Fused expression:    "% *(@-8) 16 == ax 1 IF! "
    mov     ax, [bp-8]
    cwd
    mov     cx, 16
    idiv    cx
    mov     ax, dx
    cmp     ax, 1
    jne     L2189
; {
; if
; RPN'ized expression: "CharIsSigned "
; Expanded expression: "CharIsSigned *(2) "
; Fused expression:    "*(2) CharIsSigned "
    mov     ax, [_CharIsSigned]
; JumpIfZero
    test    ax, ax
    jz      L2191
; RPN'ized expression: "( L2193 printf ) "
; Expanded expression: " L2193  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2193:
    db  "    movsx   cx, byte [",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2193 , printf )2 "
    push    L2193
    call    _printf
    sub     sp, -2
    jmp     L2192
L2191:
; else
; RPN'ized expression: "( L2195 printf ) "
; Expanded expression: " L2195  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2195:
    db  "    movzx   cx, byte [",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2195 , printf )2 "
    push    L2195
    call    _printf
    sub     sp, -2
L2192:
; RPN'ized expression: "( IdentTable stack i 2 + + *u 1 + *u + GenPrintLabel ) "
; Expanded expression: " IdentTable stack (@-4) *(2) 2 + 4 * + 2 + *(2) +  GenPrintLabel ()2 "
; Fused expression:    "( + *(@-4) 2 * ax 4 + stack ax + ax 2 + IdentTable *ax , GenPrintLabel )2 "
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, _IdentTable
    add     ax, cx
    push    ax
    call    _GenPrintLabel
    sub     sp, -2
; RPN'ized expression: "( L2197 printf ) "
; Expanded expression: " L2197  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2197:
    db  "]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2197 , printf )2 "
    push    L2197
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( instr , L2199 printf ) "
; Expanded expression: " (@-10) *(2)  L2199  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2199:
    db  "    %-4s    ax, cx",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-10) , L2199 , printf )4 "
    push    word [bp-10]
    push    L2199
    call    _printf
    sub     sp, -4
; }
    jmp     L2190
L2189:
; else
; if
; RPN'ized expression: "v 16 % 2 == "
; Expanded expression: "(@-8) *(2) 16 % 2 == "
; Fused expression:    "% *(@-8) 16 == ax 2 IF! "
    mov     ax, [bp-8]
    cwd
    mov     cx, 16
    idiv    cx
    mov     ax, dx
    cmp     ax, 2
    jne     L2201
; {
; RPN'ized expression: "( instr , L2203 printf ) "
; Expanded expression: " (@-10) *(2)  L2203  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2203:
    db  "    %-4s    ax, [",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-10) , L2203 , printf )4 "
    push    word [bp-10]
    push    L2203
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( IdentTable stack i 2 + + *u 1 + *u + GenPrintLabel ) "
; Expanded expression: " IdentTable stack (@-4) *(2) 2 + 4 * + 2 + *(2) +  GenPrintLabel ()2 "
; Fused expression:    "( + *(@-4) 2 * ax 4 + stack ax + ax 2 + IdentTable *ax , GenPrintLabel )2 "
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, _IdentTable
    add     ax, cx
    push    ax
    call    _GenPrintLabel
    sub     sp, -2
; RPN'ized expression: "( L2205 printf ) "
; Expanded expression: " L2205  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2205:
    db  "]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2205 , printf )2 "
    push    L2205
    call    _printf
    sub     sp, -2
; }
L2201:
L2190:
; break
    jmp     L2163
; case
; RPN'ized expression: "261 "
; Expanded expression: "261 "
; Expression value: 261
    jmp     L2188
L2187:
    cmp     ax, 261
    jne     L2207
L2188:
; if
; RPN'ized expression: "v 16 % 1 == "
; Expanded expression: "(@-8) *(2) 16 % 1 == "
; Fused expression:    "% *(@-8) 16 == ax 1 IF! "
    mov     ax, [bp-8]
    cwd
    mov     cx, 16
    idiv    cx
    mov     ax, dx
    cmp     ax, 1
    jne     L2209
; {
; if
; RPN'ized expression: "CharIsSigned "
; Expanded expression: "CharIsSigned *(2) "
; Fused expression:    "*(2) CharIsSigned "
    mov     ax, [_CharIsSigned]
; JumpIfZero
    test    ax, ax
    jz      L2211
; RPN'ized expression: "( stack i 2 + + *u 1 + *u , L2213 printf ) "
; Expanded expression: " stack (@-4) *(2) 2 + 4 * + 2 + *(2)  L2213  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2213:
    db  "    movsx   cx, byte [bp%+d]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( + *(@-4) 2 * ax 4 + stack ax + ax 2 *(2) ax , L2213 , printf )4 "
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    L2213
    call    _printf
    sub     sp, -4
    jmp     L2212
L2211:
; else
; RPN'ized expression: "( stack i 2 + + *u 1 + *u , L2215 printf ) "
; Expanded expression: " stack (@-4) *(2) 2 + 4 * + 2 + *(2)  L2215  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2215:
    db  "    movzx   cx, byte [bp%+d]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( + *(@-4) 2 * ax 4 + stack ax + ax 2 *(2) ax , L2215 , printf )4 "
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    L2215
    call    _printf
    sub     sp, -4
L2212:
; RPN'ized expression: "( instr , L2217 printf ) "
; Expanded expression: " (@-10) *(2)  L2217  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2217:
    db  "    %-4s    ax, cx",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-10) , L2217 , printf )4 "
    push    word [bp-10]
    push    L2217
    call    _printf
    sub     sp, -4
; }
    jmp     L2210
L2209:
; else
; if
; RPN'ized expression: "v 16 % 2 == "
; Expanded expression: "(@-8) *(2) 16 % 2 == "
; Fused expression:    "% *(@-8) 16 == ax 2 IF! "
    mov     ax, [bp-8]
    cwd
    mov     cx, 16
    idiv    cx
    mov     ax, dx
    cmp     ax, 2
    jne     L2219
; RPN'ized expression: "( stack i 2 + + *u 1 + *u , instr , L2221 printf ) "
; Expanded expression: " stack (@-4) *(2) 2 + 4 * + 2 + *(2)  (@-10) *(2)  L2221  printf ()6 "
; SEGMENT _TEXT
SEGMENT _DATA
L2221:
    db  "    %-4s    ax, [bp%+d]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( + *(@-4) 2 * ax 4 + stack ax + ax 2 *(2) ax , *(2) (@-10) , L2221 , printf )6 "
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    word [bp-10]
    push    L2221
    call    _printf
    sub     sp, -6
L2219:
L2210:
; break
    jmp     L2163
; }
    jmp     L2163
L2207:
L2163:
; if
; RPN'ized expression: "i 3 + sp < stack i 3 + + *u 0 + *u 22 == stack i 3 + + *u 0 + *u 76 == || && "
; Expanded expression: "(@-4) *(2) 3 + sp *(2) < _Bool [sh&&->2225] stack (@-4) *(2) 3 + 4 * + 0 + *(2) 22 == _Bool [sh||->2226] stack (@-4) *(2) 3 + 4 * + 0 + *(2) 76 == _Bool ||[2226] _Bool &&[2225] "
; Fused expression:    "+ *(@-4) 3 < ax *sp _Bool [sh&&->2225] + *(@-4) 3 * ax 4 + stack ax + ax 0 == *ax 22 _Bool [sh||->2226] + *(@-4) 3 * ax 4 + stack ax + ax 0 == *ax 76 _Bool ||[2226] _Bool &&[2225] "
    mov     ax, [bp-4]
    add     ax, 3
    cmp     ax, [_sp]
    setl    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L2225
    mov     ax, [bp-4]
    add     ax, 3
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 22
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L2226
    mov     ax, [bp-4]
    add     ax, 3
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 76
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L2226:
    test    ax, ax
    setnz   al
    cbw
L2225:
; JumpIfZero
    test    ax, ax
    jz      L2223
; {
; if
; RPN'ized expression: "stack i 3 + + *u 0 + *u 22 == "
; Expanded expression: "stack (@-4) *(2) 3 + 4 * + 0 + *(2) 22 == "
; Fused expression:    "+ *(@-4) 3 * ax 4 + stack ax + ax 0 == *ax 22 IF! "
    mov     ax, [bp-4]
    add     ax, 3
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 22
    jne     L2227
; {
; switch
; RPN'ized expression: "tok "
; Expanded expression: "(@-6) *(2) "
; Fused expression:    "*(2) (@-6) "
    mov     ax, [bp-6]
    jmp     L2231
; {
; case
; RPN'ized expression: "60 "
; Expanded expression: "60 "
; Expression value: 60
    jmp     L2232
L2231:
    cmp     ax, 60
    jne     L2233
L2232:
; RPN'ized expression: "( L2235 printf ) "
; Expanded expression: " L2235  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2235:
    db  "    jl      ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2235 , printf )2 "
    push    L2235
    call    _printf
    sub     sp, -2
; break
    jmp     L2229
; case
; RPN'ized expression: "85 "
; Expanded expression: "85 "
; Expression value: 85
    jmp     L2234
L2233:
    cmp     ax, 85
    jne     L2237
L2234:
; RPN'ized expression: "( L2239 printf ) "
; Expanded expression: " L2239  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2239:
    db  "    jb      ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2239 , printf )2 "
    push    L2239
    call    _printf
    sub     sp, -2
; break
    jmp     L2229
; case
; RPN'ized expression: "62 "
; Expanded expression: "62 "
; Expression value: 62
    jmp     L2238
L2237:
    cmp     ax, 62
    jne     L2241
L2238:
; RPN'ized expression: "( L2243 printf ) "
; Expanded expression: " L2243  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2243:
    db  "    jg      ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2243 , printf )2 "
    push    L2243
    call    _printf
    sub     sp, -2
; break
    jmp     L2229
; case
; RPN'ized expression: "86 "
; Expanded expression: "86 "
; Expression value: 86
    jmp     L2242
L2241:
    cmp     ax, 86
    jne     L2245
L2242:
; RPN'ized expression: "( L2247 printf ) "
; Expanded expression: " L2247  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2247:
    db  "    ja      ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2247 , printf )2 "
    push    L2247
    call    _printf
    sub     sp, -2
; break
    jmp     L2229
; case
; RPN'ized expression: "10 "
; Expanded expression: "10 "
; Expression value: 10
    jmp     L2246
L2245:
    cmp     ax, 10
    jne     L2249
L2246:
; RPN'ized expression: "( L2251 printf ) "
; Expanded expression: " L2251  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2251:
    db  "    jle     ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2251 , printf )2 "
    push    L2251
    call    _printf
    sub     sp, -2
; break
    jmp     L2229
; case
; RPN'ized expression: "87 "
; Expanded expression: "87 "
; Expression value: 87
    jmp     L2250
L2249:
    cmp     ax, 87
    jne     L2253
L2250:
; RPN'ized expression: "( L2255 printf ) "
; Expanded expression: " L2255  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2255:
    db  "    jbe     ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2255 , printf )2 "
    push    L2255
    call    _printf
    sub     sp, -2
; break
    jmp     L2229
; case
; RPN'ized expression: "11 "
; Expanded expression: "11 "
; Expression value: 11
    jmp     L2254
L2253:
    cmp     ax, 11
    jne     L2257
L2254:
; RPN'ized expression: "( L2259 printf ) "
; Expanded expression: " L2259  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2259:
    db  "    jge     ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2259 , printf )2 "
    push    L2259
    call    _printf
    sub     sp, -2
; break
    jmp     L2229
; case
; RPN'ized expression: "88 "
; Expanded expression: "88 "
; Expression value: 88
    jmp     L2258
L2257:
    cmp     ax, 88
    jne     L2261
L2258:
; RPN'ized expression: "( L2263 printf ) "
; Expanded expression: " L2263  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2263:
    db  "    jae     ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2263 , printf )2 "
    push    L2263
    call    _printf
    sub     sp, -2
; break
    jmp     L2229
; case
; RPN'ized expression: "8 "
; Expanded expression: "8 "
; Expression value: 8
    jmp     L2262
L2261:
    cmp     ax, 8
    jne     L2265
L2262:
; RPN'ized expression: "( L2267 printf ) "
; Expanded expression: " L2267  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2267:
    db  "    je      ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2267 , printf )2 "
    push    L2267
    call    _printf
    sub     sp, -2
; break
    jmp     L2229
; case
; RPN'ized expression: "9 "
; Expanded expression: "9 "
; Expression value: 9
    jmp     L2266
L2265:
    cmp     ax, 9
    jne     L2269
L2266:
; RPN'ized expression: "( L2271 printf ) "
; Expanded expression: " L2271  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2271:
    db  "    jne     ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2271 , printf )2 "
    push    L2271
    call    _printf
    sub     sp, -2
; break
    jmp     L2229
; }
    jmp     L2229
L2269:
L2229:
; }
    jmp     L2228
L2227:
; else
; {
; switch
; RPN'ized expression: "tok "
; Expanded expression: "(@-6) *(2) "
; Fused expression:    "*(2) (@-6) "
    mov     ax, [bp-6]
    jmp     L2275
; {
; case
; RPN'ized expression: "60 "
; Expanded expression: "60 "
; Expression value: 60
    jmp     L2276
L2275:
    cmp     ax, 60
    jne     L2277
L2276:
; RPN'ized expression: "( L2279 printf ) "
; Expanded expression: " L2279  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2279:
    db  "    jge     ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2279 , printf )2 "
    push    L2279
    call    _printf
    sub     sp, -2
; break
    jmp     L2273
; case
; RPN'ized expression: "85 "
; Expanded expression: "85 "
; Expression value: 85
    jmp     L2278
L2277:
    cmp     ax, 85
    jne     L2281
L2278:
; RPN'ized expression: "( L2283 printf ) "
; Expanded expression: " L2283  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2283:
    db  "    jae     ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2283 , printf )2 "
    push    L2283
    call    _printf
    sub     sp, -2
; break
    jmp     L2273
; case
; RPN'ized expression: "62 "
; Expanded expression: "62 "
; Expression value: 62
    jmp     L2282
L2281:
    cmp     ax, 62
    jne     L2285
L2282:
; RPN'ized expression: "( L2287 printf ) "
; Expanded expression: " L2287  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2287:
    db  "    jle     ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2287 , printf )2 "
    push    L2287
    call    _printf
    sub     sp, -2
; break
    jmp     L2273
; case
; RPN'ized expression: "86 "
; Expanded expression: "86 "
; Expression value: 86
    jmp     L2286
L2285:
    cmp     ax, 86
    jne     L2289
L2286:
; RPN'ized expression: "( L2291 printf ) "
; Expanded expression: " L2291  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2291:
    db  "    jbe     ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2291 , printf )2 "
    push    L2291
    call    _printf
    sub     sp, -2
; break
    jmp     L2273
; case
; RPN'ized expression: "10 "
; Expanded expression: "10 "
; Expression value: 10
    jmp     L2290
L2289:
    cmp     ax, 10
    jne     L2293
L2290:
; RPN'ized expression: "( L2295 printf ) "
; Expanded expression: " L2295  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2295:
    db  "    jg      ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2295 , printf )2 "
    push    L2295
    call    _printf
    sub     sp, -2
; break
    jmp     L2273
; case
; RPN'ized expression: "87 "
; Expanded expression: "87 "
; Expression value: 87
    jmp     L2294
L2293:
    cmp     ax, 87
    jne     L2297
L2294:
; RPN'ized expression: "( L2299 printf ) "
; Expanded expression: " L2299  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2299:
    db  "    ja      ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2299 , printf )2 "
    push    L2299
    call    _printf
    sub     sp, -2
; break
    jmp     L2273
; case
; RPN'ized expression: "11 "
; Expanded expression: "11 "
; Expression value: 11
    jmp     L2298
L2297:
    cmp     ax, 11
    jne     L2301
L2298:
; RPN'ized expression: "( L2303 printf ) "
; Expanded expression: " L2303  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2303:
    db  "    jl      ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2303 , printf )2 "
    push    L2303
    call    _printf
    sub     sp, -2
; break
    jmp     L2273
; case
; RPN'ized expression: "88 "
; Expanded expression: "88 "
; Expression value: 88
    jmp     L2302
L2301:
    cmp     ax, 88
    jne     L2305
L2302:
; RPN'ized expression: "( L2307 printf ) "
; Expanded expression: " L2307  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2307:
    db  "    jb      ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2307 , printf )2 "
    push    L2307
    call    _printf
    sub     sp, -2
; break
    jmp     L2273
; case
; RPN'ized expression: "8 "
; Expanded expression: "8 "
; Expression value: 8
    jmp     L2306
L2305:
    cmp     ax, 8
    jne     L2309
L2306:
; RPN'ized expression: "( L2311 printf ) "
; Expanded expression: " L2311  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2311:
    db  "    jne     ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2311 , printf )2 "
    push    L2311
    call    _printf
    sub     sp, -2
; break
    jmp     L2273
; case
; RPN'ized expression: "9 "
; Expanded expression: "9 "
; Expression value: 9
    jmp     L2310
L2309:
    cmp     ax, 9
    jne     L2313
L2310:
; RPN'ized expression: "( L2315 printf ) "
; Expanded expression: " L2315  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2315:
    db  "    je      ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2315 , printf )2 "
    push    L2315
    call    _printf
    sub     sp, -2
; break
    jmp     L2273
; }
    jmp     L2273
L2313:
L2273:
; }
L2228:
; RPN'ized expression: "( stack i 3 + + *u 1 + *u , L2317 printf ) "
; Expanded expression: " stack (@-4) *(2) 3 + 4 * + 2 + *(2)  L2317  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2317:
    db  "L%d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( + *(@-4) 3 * ax 4 + stack ax + ax 2 *(2) ax , L2317 , printf )4 "
    mov     ax, [bp-4]
    add     ax, 3
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    L2317
    call    _printf
    sub     sp, -4
; }
    jmp     L2224
L2223:
; else
; {
; switch
; RPN'ized expression: "tok "
; Expanded expression: "(@-6) *(2) "
; Fused expression:    "*(2) (@-6) "
    mov     ax, [bp-6]
    jmp     L2321
; {
; case
; RPN'ized expression: "60 "
; Expanded expression: "60 "
; Expression value: 60
    jmp     L2322
L2321:
    cmp     ax, 60
    jne     L2323
L2322:
; RPN'ized expression: "( L2325 printf ) "
; Expanded expression: " L2325  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2325:
    db  "    setl    al",10,"    cbw",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2325 , printf )2 "
    push    L2325
    call    _printf
    sub     sp, -2
; break
    jmp     L2319
; case
; RPN'ized expression: "85 "
; Expanded expression: "85 "
; Expression value: 85
    jmp     L2324
L2323:
    cmp     ax, 85
    jne     L2327
L2324:
; RPN'ized expression: "( L2329 printf ) "
; Expanded expression: " L2329  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2329:
    db  "    setb    al",10,"    cbw",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2329 , printf )2 "
    push    L2329
    call    _printf
    sub     sp, -2
; break
    jmp     L2319
; case
; RPN'ized expression: "62 "
; Expanded expression: "62 "
; Expression value: 62
    jmp     L2328
L2327:
    cmp     ax, 62
    jne     L2331
L2328:
; RPN'ized expression: "( L2333 printf ) "
; Expanded expression: " L2333  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2333:
    db  "    setg    al",10,"    cbw",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2333 , printf )2 "
    push    L2333
    call    _printf
    sub     sp, -2
; break
    jmp     L2319
; case
; RPN'ized expression: "86 "
; Expanded expression: "86 "
; Expression value: 86
    jmp     L2332
L2331:
    cmp     ax, 86
    jne     L2335
L2332:
; RPN'ized expression: "( L2337 printf ) "
; Expanded expression: " L2337  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2337:
    db  "    seta    al",10,"    cbw",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2337 , printf )2 "
    push    L2337
    call    _printf
    sub     sp, -2
; break
    jmp     L2319
; case
; RPN'ized expression: "10 "
; Expanded expression: "10 "
; Expression value: 10
    jmp     L2336
L2335:
    cmp     ax, 10
    jne     L2339
L2336:
; RPN'ized expression: "( L2341 printf ) "
; Expanded expression: " L2341  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2341:
    db  "    setle   al",10,"    cbw",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2341 , printf )2 "
    push    L2341
    call    _printf
    sub     sp, -2
; break
    jmp     L2319
; case
; RPN'ized expression: "87 "
; Expanded expression: "87 "
; Expression value: 87
    jmp     L2340
L2339:
    cmp     ax, 87
    jne     L2343
L2340:
; RPN'ized expression: "( L2345 printf ) "
; Expanded expression: " L2345  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2345:
    db  "    setbe   al",10,"    cbw",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2345 , printf )2 "
    push    L2345
    call    _printf
    sub     sp, -2
; break
    jmp     L2319
; case
; RPN'ized expression: "11 "
; Expanded expression: "11 "
; Expression value: 11
    jmp     L2344
L2343:
    cmp     ax, 11
    jne     L2347
L2344:
; RPN'ized expression: "( L2349 printf ) "
; Expanded expression: " L2349  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2349:
    db  "    setge   al",10,"    cbw",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2349 , printf )2 "
    push    L2349
    call    _printf
    sub     sp, -2
; break
    jmp     L2319
; case
; RPN'ized expression: "88 "
; Expanded expression: "88 "
; Expression value: 88
    jmp     L2348
L2347:
    cmp     ax, 88
    jne     L2351
L2348:
; RPN'ized expression: "( L2353 printf ) "
; Expanded expression: " L2353  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2353:
    db  "    setae   al",10,"    cbw",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2353 , printf )2 "
    push    L2353
    call    _printf
    sub     sp, -2
; break
    jmp     L2319
; case
; RPN'ized expression: "8 "
; Expanded expression: "8 "
; Expression value: 8
    jmp     L2352
L2351:
    cmp     ax, 8
    jne     L2355
L2352:
; RPN'ized expression: "( L2357 printf ) "
; Expanded expression: " L2357  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2357:
    db  "    sete    al",10,"    cbw",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2357 , printf )2 "
    push    L2357
    call    _printf
    sub     sp, -2
; break
    jmp     L2319
; case
; RPN'ized expression: "9 "
; Expanded expression: "9 "
; Expression value: 9
    jmp     L2356
L2355:
    cmp     ax, 9
    jne     L2359
L2356:
; RPN'ized expression: "( L2361 printf ) "
; Expanded expression: " L2361  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2361:
    db  "    setne   al",10,"    cbw",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2361 , printf )2 "
    push    L2361
    call    _printf
    sub     sp, -2
; break
    jmp     L2319
; }
    jmp     L2319
L2359:
L2319:
; }
L2224:
; break
    jmp     L2119
; case
; RPN'ized expression: "42 "
; Expanded expression: "42 "
; Expression value: 42
    jmp     L2162
L2161:
    cmp     ax, 42
    jne     L2363
L2162:
; case
; RPN'ized expression: "65 "
; Expanded expression: "65 "
; Expression value: 65
    jmp     L2364
L2363:
    cmp     ax, 65
    jne     L2365
L2364:
; RPN'ized expression: "instr ( tok GenGetBinaryOperatorInstr ) = "
; Expanded expression: "(@-10)  (@-6) *(2)  GenGetBinaryOperatorInstr ()2 =(2) "
; Fused expression:    "( *(2) (@-6) , GenGetBinaryOperatorInstr )2 =(34) *(@-10) ax "
    push    word [bp-6]
    call    _GenGetBinaryOperatorInstr
    sub     sp, -2
    mov     [bp-10], ax
; switch
; RPN'ized expression: "stack i 2 + + *u 0 + *u "
; Expanded expression: "stack (@-4) *(2) 2 + 4 * + 0 + *(2) "
; Fused expression:    "+ *(@-4) 2 * ax 4 + stack ax + ax 0 *(2) ax "
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    jmp     L2369
; {
; case
; RPN'ized expression: "256 "
; Expanded expression: "256 "
; Expression value: 256
    jmp     L2370
L2369:
    cmp     ax, 256
    jne     L2371
L2370:
; RPN'ized expression: "( stack i 2 + + *u 1 + *u , L2373 printf ) "
; Expanded expression: " stack (@-4) *(2) 2 + 4 * + 2 + *(2)  L2373  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2373:
    db  "    imul    ax, ax, %d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( + *(@-4) 2 * ax 4 + stack ax + ax 2 *(2) ax , L2373 , printf )4 "
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    L2373
    call    _printf
    sub     sp, -4
; break
    jmp     L2367
; case
; RPN'ized expression: "257 "
; Expanded expression: "257 "
; Expression value: 257
    jmp     L2372
L2371:
    cmp     ax, 257
    jne     L2375
L2372:
; RPN'ized expression: "( L2377 printf ) "
; Expanded expression: " L2377  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2377:
    db  "    imul    ax, ax, ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2377 , printf )2 "
    push    L2377
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( IdentTable stack i 2 + + *u 1 + *u + GenPrintLabel ) "
; Expanded expression: " IdentTable stack (@-4) *(2) 2 + 4 * + 2 + *(2) +  GenPrintLabel ()2 "
; Fused expression:    "( + *(@-4) 2 * ax 4 + stack ax + ax 2 + IdentTable *ax , GenPrintLabel )2 "
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, _IdentTable
    add     ax, cx
    push    ax
    call    _GenPrintLabel
    sub     sp, -2
; RPN'ized expression: "( L2379 printf ) "
; Expanded expression: " L2379  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2379:
    db  10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2379 , printf )2 "
    push    L2379
    call    _printf
    sub     sp, -2
; break
    jmp     L2367
; case
; RPN'ized expression: "258 "
; Expanded expression: "258 "
; Expression value: 258
    jmp     L2376
L2375:
    cmp     ax, 258
    jne     L2381
L2376:
; RPN'ized expression: "( instr , stack i 2 + + *u 1 + *u , L2383 printf ) "
; Expanded expression: " (@-10) *(2)  stack (@-4) *(2) 2 + 4 * + 2 + *(2)  L2383  printf ()6 "
; SEGMENT _TEXT
SEGMENT _DATA
L2383:
    db  "    lea     cx, [bp%+d]",10,"    %-4s    cx",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-10) , + *(@-4) 2 * ax 4 + stack ax + ax 2 *(2) ax , L2383 , printf )6 "
    push    word [bp-10]
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    L2383
    call    _printf
    sub     sp, -6
; break
    jmp     L2367
; case
; RPN'ized expression: "259 "
; Expanded expression: "259 "
; Expression value: 259
    jmp     L2382
L2381:
    cmp     ax, 259
    jne     L2385
L2382:
; case
; RPN'ized expression: "262 "
; Expanded expression: "262 "
; Expression value: 262
    jmp     L2386
L2385:
    cmp     ax, 262
    jne     L2387
L2386:
; RPN'ized expression: "( instr , L2389 printf ) "
; Expanded expression: " (@-10) *(2)  L2389  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2389:
    db  "    %-4s    cx",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-10) , L2389 , printf )4 "
    push    word [bp-10]
    push    L2389
    call    _printf
    sub     sp, -4
; break
    jmp     L2367
; case
; RPN'ized expression: "260 "
; Expanded expression: "260 "
; Expression value: 260
    jmp     L2388
L2387:
    cmp     ax, 260
    jne     L2391
L2388:
; if
; RPN'ized expression: "v 16 % 1 == "
; Expanded expression: "(@-8) *(2) 16 % 1 == "
; Fused expression:    "% *(@-8) 16 == ax 1 IF! "
    mov     ax, [bp-8]
    cwd
    mov     cx, 16
    idiv    cx
    mov     ax, dx
    cmp     ax, 1
    jne     L2393
; {
; if
; RPN'ized expression: "CharIsSigned "
; Expanded expression: "CharIsSigned *(2) "
; Fused expression:    "*(2) CharIsSigned "
    mov     ax, [_CharIsSigned]
; JumpIfZero
    test    ax, ax
    jz      L2395
; RPN'ized expression: "( L2397 printf ) "
; Expanded expression: " L2397  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2397:
    db  "    movsx   cx, byte [",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2397 , printf )2 "
    push    L2397
    call    _printf
    sub     sp, -2
    jmp     L2396
L2395:
; else
; RPN'ized expression: "( L2399 printf ) "
; Expanded expression: " L2399  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2399:
    db  "    movzx   cx, byte [",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2399 , printf )2 "
    push    L2399
    call    _printf
    sub     sp, -2
L2396:
; RPN'ized expression: "( IdentTable stack i 2 + + *u 1 + *u + GenPrintLabel ) "
; Expanded expression: " IdentTable stack (@-4) *(2) 2 + 4 * + 2 + *(2) +  GenPrintLabel ()2 "
; Fused expression:    "( + *(@-4) 2 * ax 4 + stack ax + ax 2 + IdentTable *ax , GenPrintLabel )2 "
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, _IdentTable
    add     ax, cx
    push    ax
    call    _GenPrintLabel
    sub     sp, -2
; RPN'ized expression: "( L2401 printf ) "
; Expanded expression: " L2401  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2401:
    db  "]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2401 , printf )2 "
    push    L2401
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( instr , L2403 printf ) "
; Expanded expression: " (@-10) *(2)  L2403  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2403:
    db  "    %-4s    cx",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-10) , L2403 , printf )4 "
    push    word [bp-10]
    push    L2403
    call    _printf
    sub     sp, -4
; }
    jmp     L2394
L2393:
; else
; if
; RPN'ized expression: "v 16 % 2 == "
; Expanded expression: "(@-8) *(2) 16 % 2 == "
; Fused expression:    "% *(@-8) 16 == ax 2 IF! "
    mov     ax, [bp-8]
    cwd
    mov     cx, 16
    idiv    cx
    mov     ax, dx
    cmp     ax, 2
    jne     L2405
; {
; RPN'ized expression: "( instr , L2407 printf ) "
; Expanded expression: " (@-10) *(2)  L2407  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2407:
    db  "    %-4s    word [",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-10) , L2407 , printf )4 "
    push    word [bp-10]
    push    L2407
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( IdentTable stack i 2 + + *u 1 + *u + GenPrintLabel ) "
; Expanded expression: " IdentTable stack (@-4) *(2) 2 + 4 * + 2 + *(2) +  GenPrintLabel ()2 "
; Fused expression:    "( + *(@-4) 2 * ax 4 + stack ax + ax 2 + IdentTable *ax , GenPrintLabel )2 "
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, _IdentTable
    add     ax, cx
    push    ax
    call    _GenPrintLabel
    sub     sp, -2
; RPN'ized expression: "( L2409 printf ) "
; Expanded expression: " L2409  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2409:
    db  "]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2409 , printf )2 "
    push    L2409
    call    _printf
    sub     sp, -2
; }
L2405:
L2394:
; break
    jmp     L2367
; case
; RPN'ized expression: "261 "
; Expanded expression: "261 "
; Expression value: 261
    jmp     L2392
L2391:
    cmp     ax, 261
    jne     L2411
L2392:
; if
; RPN'ized expression: "v 16 % 1 == "
; Expanded expression: "(@-8) *(2) 16 % 1 == "
; Fused expression:    "% *(@-8) 16 == ax 1 IF! "
    mov     ax, [bp-8]
    cwd
    mov     cx, 16
    idiv    cx
    mov     ax, dx
    cmp     ax, 1
    jne     L2413
; {
; if
; RPN'ized expression: "CharIsSigned "
; Expanded expression: "CharIsSigned *(2) "
; Fused expression:    "*(2) CharIsSigned "
    mov     ax, [_CharIsSigned]
; JumpIfZero
    test    ax, ax
    jz      L2415
; RPN'ized expression: "( stack i 2 + + *u 1 + *u , L2417 printf ) "
; Expanded expression: " stack (@-4) *(2) 2 + 4 * + 2 + *(2)  L2417  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2417:
    db  "    movsx   cx, byte [bp%+d]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( + *(@-4) 2 * ax 4 + stack ax + ax 2 *(2) ax , L2417 , printf )4 "
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    L2417
    call    _printf
    sub     sp, -4
    jmp     L2416
L2415:
; else
; RPN'ized expression: "( stack i 2 + + *u 1 + *u , L2419 printf ) "
; Expanded expression: " stack (@-4) *(2) 2 + 4 * + 2 + *(2)  L2419  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2419:
    db  "    movzx   cx, byte [bp%+d]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( + *(@-4) 2 * ax 4 + stack ax + ax 2 *(2) ax , L2419 , printf )4 "
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    L2419
    call    _printf
    sub     sp, -4
L2416:
; RPN'ized expression: "( instr , L2421 printf ) "
; Expanded expression: " (@-10) *(2)  L2421  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2421:
    db  "    %-4s    cx",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-10) , L2421 , printf )4 "
    push    word [bp-10]
    push    L2421
    call    _printf
    sub     sp, -4
; }
    jmp     L2414
L2413:
; else
; if
; RPN'ized expression: "v 16 % 2 == "
; Expanded expression: "(@-8) *(2) 16 % 2 == "
; Fused expression:    "% *(@-8) 16 == ax 2 IF! "
    mov     ax, [bp-8]
    cwd
    mov     cx, 16
    idiv    cx
    mov     ax, dx
    cmp     ax, 2
    jne     L2423
; RPN'ized expression: "( stack i 2 + + *u 1 + *u , instr , L2425 printf ) "
; Expanded expression: " stack (@-4) *(2) 2 + 4 * + 2 + *(2)  (@-10) *(2)  L2425  printf ()6 "
; SEGMENT _TEXT
SEGMENT _DATA
L2425:
    db  "    %-4s    word [bp%+d]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( + *(@-4) 2 * ax 4 + stack ax + ax 2 *(2) ax , *(2) (@-10) , L2425 , printf )6 "
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    word [bp-10]
    push    L2425
    call    _printf
    sub     sp, -6
L2423:
L2414:
; break
    jmp     L2367
; }
    jmp     L2367
L2411:
L2367:
; break
    jmp     L2119
; case
; RPN'ized expression: "47 "
; Expanded expression: "47 "
; Expression value: 47
    jmp     L2366
L2365:
    cmp     ax, 47
    jne     L2427
L2366:
; case
; RPN'ized expression: "37 "
; Expanded expression: "37 "
; Expression value: 37
    jmp     L2428
L2427:
    cmp     ax, 37
    jne     L2429
L2428:
; case
; RPN'ized expression: "66 "
; Expanded expression: "66 "
; Expression value: 66
    jmp     L2430
L2429:
    cmp     ax, 66
    jne     L2431
L2430:
; case
; RPN'ized expression: "67 "
; Expanded expression: "67 "
; Expression value: 67
    jmp     L2432
L2431:
    cmp     ax, 67
    jne     L2433
L2432:
; RPN'ized expression: "instr ( tok GenGetBinaryOperatorInstr ) = "
; Expanded expression: "(@-10)  (@-6) *(2)  GenGetBinaryOperatorInstr ()2 =(2) "
; Fused expression:    "( *(2) (@-6) , GenGetBinaryOperatorInstr )2 =(34) *(@-10) ax "
    push    word [bp-6]
    call    _GenGetBinaryOperatorInstr
    sub     sp, -2
    mov     [bp-10], ax
; RPN'ized expression: "( L2435 printf ) "
; Expanded expression: " L2435  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2435:
    db  "    cwd",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2435 , printf )2 "
    push    L2435
    call    _printf
    sub     sp, -2
; switch
; RPN'ized expression: "stack i 2 + + *u 0 + *u "
; Expanded expression: "stack (@-4) *(2) 2 + 4 * + 0 + *(2) "
; Fused expression:    "+ *(@-4) 2 * ax 4 + stack ax + ax 0 *(2) ax "
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    jmp     L2439
; {
; case
; RPN'ized expression: "256 "
; Expanded expression: "256 "
; Expression value: 256
    jmp     L2440
L2439:
    cmp     ax, 256
    jne     L2441
L2440:
; RPN'ized expression: "( instr , stack i 2 + + *u 1 + *u , L2443 printf ) "
; Expanded expression: " (@-10) *(2)  stack (@-4) *(2) 2 + 4 * + 2 + *(2)  L2443  printf ()6 "
; SEGMENT _TEXT
SEGMENT _DATA
L2443:
    db  "    mov     cx, %d",10,"    %-4s    cx",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-10) , + *(@-4) 2 * ax 4 + stack ax + ax 2 *(2) ax , L2443 , printf )6 "
    push    word [bp-10]
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    L2443
    call    _printf
    sub     sp, -6
; break
    jmp     L2437
; case
; RPN'ized expression: "257 "
; Expanded expression: "257 "
; Expression value: 257
    jmp     L2442
L2441:
    cmp     ax, 257
    jne     L2445
L2442:
; RPN'ized expression: "( L2447 printf ) "
; Expanded expression: " L2447  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2447:
    db  "    mov     cx, ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2447 , printf )2 "
    push    L2447
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( IdentTable stack i 2 + + *u 1 + *u + GenPrintLabel ) "
; Expanded expression: " IdentTable stack (@-4) *(2) 2 + 4 * + 2 + *(2) +  GenPrintLabel ()2 "
; Fused expression:    "( + *(@-4) 2 * ax 4 + stack ax + ax 2 + IdentTable *ax , GenPrintLabel )2 "
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, _IdentTable
    add     ax, cx
    push    ax
    call    _GenPrintLabel
    sub     sp, -2
; RPN'ized expression: "( L2449 printf ) "
; Expanded expression: " L2449  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2449:
    db  10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2449 , printf )2 "
    push    L2449
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( instr , L2451 printf ) "
; Expanded expression: " (@-10) *(2)  L2451  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2451:
    db  "    %-4s    cx",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-10) , L2451 , printf )4 "
    push    word [bp-10]
    push    L2451
    call    _printf
    sub     sp, -4
; break
    jmp     L2437
; case
; RPN'ized expression: "258 "
; Expanded expression: "258 "
; Expression value: 258
    jmp     L2446
L2445:
    cmp     ax, 258
    jne     L2453
L2446:
; RPN'ized expression: "( instr , stack i 2 + + *u 1 + *u , L2455 printf ) "
; Expanded expression: " (@-10) *(2)  stack (@-4) *(2) 2 + 4 * + 2 + *(2)  L2455  printf ()6 "
; SEGMENT _TEXT
SEGMENT _DATA
L2455:
    db  "    lea     cx, [bp%+d]",10,"    %-4s    cx",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-10) , + *(@-4) 2 * ax 4 + stack ax + ax 2 *(2) ax , L2455 , printf )6 "
    push    word [bp-10]
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    L2455
    call    _printf
    sub     sp, -6
; break
    jmp     L2437
; case
; RPN'ized expression: "259 "
; Expanded expression: "259 "
; Expression value: 259
    jmp     L2454
L2453:
    cmp     ax, 259
    jne     L2457
L2454:
; case
; RPN'ized expression: "262 "
; Expanded expression: "262 "
; Expression value: 262
    jmp     L2458
L2457:
    cmp     ax, 262
    jne     L2459
L2458:
; RPN'ized expression: "( instr , L2461 printf ) "
; Expanded expression: " (@-10) *(2)  L2461  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2461:
    db  "    %-4s    cx",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-10) , L2461 , printf )4 "
    push    word [bp-10]
    push    L2461
    call    _printf
    sub     sp, -4
; break
    jmp     L2437
; case
; RPN'ized expression: "260 "
; Expanded expression: "260 "
; Expression value: 260
    jmp     L2460
L2459:
    cmp     ax, 260
    jne     L2463
L2460:
; if
; RPN'ized expression: "v 16 % 1 == "
; Expanded expression: "(@-8) *(2) 16 % 1 == "
; Fused expression:    "% *(@-8) 16 == ax 1 IF! "
    mov     ax, [bp-8]
    cwd
    mov     cx, 16
    idiv    cx
    mov     ax, dx
    cmp     ax, 1
    jne     L2465
; {
; if
; RPN'ized expression: "CharIsSigned "
; Expanded expression: "CharIsSigned *(2) "
; Fused expression:    "*(2) CharIsSigned "
    mov     ax, [_CharIsSigned]
; JumpIfZero
    test    ax, ax
    jz      L2467
; RPN'ized expression: "( L2469 printf ) "
; Expanded expression: " L2469  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2469:
    db  "    movsx   cx, byte [",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2469 , printf )2 "
    push    L2469
    call    _printf
    sub     sp, -2
    jmp     L2468
L2467:
; else
; RPN'ized expression: "( L2471 printf ) "
; Expanded expression: " L2471  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2471:
    db  "    movzx   cx, byte [",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2471 , printf )2 "
    push    L2471
    call    _printf
    sub     sp, -2
L2468:
; RPN'ized expression: "( IdentTable stack i 2 + + *u 1 + *u + GenPrintLabel ) "
; Expanded expression: " IdentTable stack (@-4) *(2) 2 + 4 * + 2 + *(2) +  GenPrintLabel ()2 "
; Fused expression:    "( + *(@-4) 2 * ax 4 + stack ax + ax 2 + IdentTable *ax , GenPrintLabel )2 "
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, _IdentTable
    add     ax, cx
    push    ax
    call    _GenPrintLabel
    sub     sp, -2
; RPN'ized expression: "( L2473 printf ) "
; Expanded expression: " L2473  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2473:
    db  "]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2473 , printf )2 "
    push    L2473
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( instr , L2475 printf ) "
; Expanded expression: " (@-10) *(2)  L2475  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2475:
    db  "    %-4s    cx",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-10) , L2475 , printf )4 "
    push    word [bp-10]
    push    L2475
    call    _printf
    sub     sp, -4
; }
    jmp     L2466
L2465:
; else
; if
; RPN'ized expression: "v 16 % 2 == "
; Expanded expression: "(@-8) *(2) 16 % 2 == "
; Fused expression:    "% *(@-8) 16 == ax 2 IF! "
    mov     ax, [bp-8]
    cwd
    mov     cx, 16
    idiv    cx
    mov     ax, dx
    cmp     ax, 2
    jne     L2477
; {
; RPN'ized expression: "( instr , L2479 printf ) "
; Expanded expression: " (@-10) *(2)  L2479  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2479:
    db  "    %-4s    word [",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-10) , L2479 , printf )4 "
    push    word [bp-10]
    push    L2479
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( IdentTable stack i 2 + + *u 1 + *u + GenPrintLabel ) "
; Expanded expression: " IdentTable stack (@-4) *(2) 2 + 4 * + 2 + *(2) +  GenPrintLabel ()2 "
; Fused expression:    "( + *(@-4) 2 * ax 4 + stack ax + ax 2 + IdentTable *ax , GenPrintLabel )2 "
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, _IdentTable
    add     ax, cx
    push    ax
    call    _GenPrintLabel
    sub     sp, -2
; RPN'ized expression: "( L2481 printf ) "
; Expanded expression: " L2481  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2481:
    db  "]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2481 , printf )2 "
    push    L2481
    call    _printf
    sub     sp, -2
; }
L2477:
L2466:
; break
    jmp     L2437
; case
; RPN'ized expression: "261 "
; Expanded expression: "261 "
; Expression value: 261
    jmp     L2464
L2463:
    cmp     ax, 261
    jne     L2483
L2464:
; if
; RPN'ized expression: "v 16 % 1 == "
; Expanded expression: "(@-8) *(2) 16 % 1 == "
; Fused expression:    "% *(@-8) 16 == ax 1 IF! "
    mov     ax, [bp-8]
    cwd
    mov     cx, 16
    idiv    cx
    mov     ax, dx
    cmp     ax, 1
    jne     L2485
; {
; if
; RPN'ized expression: "CharIsSigned "
; Expanded expression: "CharIsSigned *(2) "
; Fused expression:    "*(2) CharIsSigned "
    mov     ax, [_CharIsSigned]
; JumpIfZero
    test    ax, ax
    jz      L2487
; RPN'ized expression: "( stack i 2 + + *u 1 + *u , L2489 printf ) "
; Expanded expression: " stack (@-4) *(2) 2 + 4 * + 2 + *(2)  L2489  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2489:
    db  "    movsx   cx, byte [bp%+d]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( + *(@-4) 2 * ax 4 + stack ax + ax 2 *(2) ax , L2489 , printf )4 "
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    L2489
    call    _printf
    sub     sp, -4
    jmp     L2488
L2487:
; else
; RPN'ized expression: "( stack i 2 + + *u 1 + *u , L2491 printf ) "
; Expanded expression: " stack (@-4) *(2) 2 + 4 * + 2 + *(2)  L2491  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2491:
    db  "    movzx   cx, byte [bp%+d]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( + *(@-4) 2 * ax 4 + stack ax + ax 2 *(2) ax , L2491 , printf )4 "
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    L2491
    call    _printf
    sub     sp, -4
L2488:
; RPN'ized expression: "( instr , L2493 printf ) "
; Expanded expression: " (@-10) *(2)  L2493  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2493:
    db  "    %-4s    cx",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-10) , L2493 , printf )4 "
    push    word [bp-10]
    push    L2493
    call    _printf
    sub     sp, -4
; }
    jmp     L2486
L2485:
; else
; if
; RPN'ized expression: "v 16 % 2 == "
; Expanded expression: "(@-8) *(2) 16 % 2 == "
; Fused expression:    "% *(@-8) 16 == ax 2 IF! "
    mov     ax, [bp-8]
    cwd
    mov     cx, 16
    idiv    cx
    mov     ax, dx
    cmp     ax, 2
    jne     L2495
; RPN'ized expression: "( stack i 2 + + *u 1 + *u , instr , L2497 printf ) "
; Expanded expression: " stack (@-4) *(2) 2 + 4 * + 2 + *(2)  (@-10) *(2)  L2497  printf ()6 "
; SEGMENT _TEXT
SEGMENT _DATA
L2497:
    db  "    %-4s    word [bp%+d]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( + *(@-4) 2 * ax 4 + stack ax + ax 2 *(2) ax , *(2) (@-10) , L2497 , printf )6 "
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    word [bp-10]
    push    L2497
    call    _printf
    sub     sp, -6
L2495:
L2486:
; break
    jmp     L2437
; }
    jmp     L2437
L2483:
L2437:
; if
; RPN'ized expression: "tok 37 == tok 67 == || "
; Expanded expression: "(@-6) *(2) 37 == _Bool [sh||->2501] (@-6) *(2) 67 == _Bool ||[2501] "
; Fused expression:    "== *(@-6) 37 _Bool [sh||->2501] == *(@-6) 67 _Bool ||[2501] "
    mov     ax, [bp-6]
    cmp     ax, 37
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L2501
    mov     ax, [bp-6]
    cmp     ax, 67
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L2501:
; JumpIfZero
    test    ax, ax
    jz      L2499
; RPN'ized expression: "( L2502 printf ) "
; Expanded expression: " L2502  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2502:
    db  "    mov     ax, dx",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2502 , printf )2 "
    push    L2502
    call    _printf
    sub     sp, -2
L2499:
; break
    jmp     L2119
; case
; RPN'ized expression: "4 "
; Expanded expression: "4 "
; Expression value: 4
    jmp     L2434
L2433:
    cmp     ax, 4
    jne     L2504
L2434:
; case
; RPN'ized expression: "5 "
; Expanded expression: "5 "
; Expression value: 5
    jmp     L2505
L2504:
    cmp     ax, 5
    jne     L2506
L2505:
; case
; RPN'ized expression: "70 "
; Expanded expression: "70 "
; Expression value: 70
    jmp     L2507
L2506:
    cmp     ax, 70
    jne     L2508
L2507:
; case
; RPN'ized expression: "71 "
; Expanded expression: "71 "
; Expression value: 71
    jmp     L2509
L2508:
    cmp     ax, 71
    jne     L2510
L2509:
; RPN'ized expression: "instr ( tok GenGetBinaryOperatorInstr ) = "
; Expanded expression: "(@-10)  (@-6) *(2)  GenGetBinaryOperatorInstr ()2 =(2) "
; Fused expression:    "( *(2) (@-6) , GenGetBinaryOperatorInstr )2 =(34) *(@-10) ax "
    push    word [bp-6]
    call    _GenGetBinaryOperatorInstr
    sub     sp, -2
    mov     [bp-10], ax
; switch
; RPN'ized expression: "stack i 2 + + *u 0 + *u "
; Expanded expression: "stack (@-4) *(2) 2 + 4 * + 0 + *(2) "
; Fused expression:    "+ *(@-4) 2 * ax 4 + stack ax + ax 0 *(2) ax "
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    jmp     L2514
; {
; case
; RPN'ized expression: "256 "
; Expanded expression: "256 "
; Expression value: 256
    jmp     L2515
L2514:
    cmp     ax, 256
    jne     L2516
L2515:
; RPN'ized expression: "( stack i 2 + + *u 1 + *u , instr , L2518 printf ) "
; Expanded expression: " stack (@-4) *(2) 2 + 4 * + 2 + *(2)  (@-10) *(2)  L2518  printf ()6 "
; SEGMENT _TEXT
SEGMENT _DATA
L2518:
    db  "    %-4s    ax, %d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( + *(@-4) 2 * ax 4 + stack ax + ax 2 *(2) ax , *(2) (@-10) , L2518 , printf )6 "
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    word [bp-10]
    push    L2518
    call    _printf
    sub     sp, -6
; break
    jmp     L2512
; case
; RPN'ized expression: "257 "
; Expanded expression: "257 "
; Expression value: 257
    jmp     L2517
L2516:
    cmp     ax, 257
    jne     L2520
L2517:
; RPN'ized expression: "( instr , L2522 printf ) "
; Expanded expression: " (@-10) *(2)  L2522  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2522:
    db  "    %-4s    ax, ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-10) , L2522 , printf )4 "
    push    word [bp-10]
    push    L2522
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( IdentTable stack i 2 + + *u 1 + *u + GenPrintLabel ) "
; Expanded expression: " IdentTable stack (@-4) *(2) 2 + 4 * + 2 + *(2) +  GenPrintLabel ()2 "
; Fused expression:    "( + *(@-4) 2 * ax 4 + stack ax + ax 2 + IdentTable *ax , GenPrintLabel )2 "
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, _IdentTable
    add     ax, cx
    push    ax
    call    _GenPrintLabel
    sub     sp, -2
; RPN'ized expression: "( L2524 printf ) "
; Expanded expression: " L2524  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2524:
    db  10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2524 , printf )2 "
    push    L2524
    call    _printf
    sub     sp, -2
; break
    jmp     L2512
; case
; RPN'ized expression: "258 "
; Expanded expression: "258 "
; Expression value: 258
    jmp     L2521
L2520:
    cmp     ax, 258
    jne     L2526
L2521:
; RPN'ized expression: "( instr , stack i 2 + + *u 1 + *u , L2528 printf ) "
; Expanded expression: " (@-10) *(2)  stack (@-4) *(2) 2 + 4 * + 2 + *(2)  L2528  printf ()6 "
; SEGMENT _TEXT
SEGMENT _DATA
L2528:
    db  "    lea     cx, [bp%+d]",10,"    %-4s    ax, cl",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-10) , + *(@-4) 2 * ax 4 + stack ax + ax 2 *(2) ax , L2528 , printf )6 "
    push    word [bp-10]
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    L2528
    call    _printf
    sub     sp, -6
; break
    jmp     L2512
; case
; RPN'ized expression: "259 "
; Expanded expression: "259 "
; Expression value: 259
    jmp     L2527
L2526:
    cmp     ax, 259
    jne     L2530
L2527:
; case
; RPN'ized expression: "262 "
; Expanded expression: "262 "
; Expression value: 262
    jmp     L2531
L2530:
    cmp     ax, 262
    jne     L2532
L2531:
; RPN'ized expression: "( instr , L2534 printf ) "
; Expanded expression: " (@-10) *(2)  L2534  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2534:
    db  "    %-4s    ax, cl",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-10) , L2534 , printf )4 "
    push    word [bp-10]
    push    L2534
    call    _printf
    sub     sp, -4
; break
    jmp     L2512
; case
; RPN'ized expression: "260 "
; Expanded expression: "260 "
; Expression value: 260
    jmp     L2533
L2532:
    cmp     ax, 260
    jne     L2536
L2533:
; RPN'ized expression: "( L2538 printf ) "
; Expanded expression: " L2538  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2538:
    db  "    mov     cl, [",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2538 , printf )2 "
    push    L2538
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( IdentTable stack i 2 + + *u 1 + *u + GenPrintLabel ) "
; Expanded expression: " IdentTable stack (@-4) *(2) 2 + 4 * + 2 + *(2) +  GenPrintLabel ()2 "
; Fused expression:    "( + *(@-4) 2 * ax 4 + stack ax + ax 2 + IdentTable *ax , GenPrintLabel )2 "
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, _IdentTable
    add     ax, cx
    push    ax
    call    _GenPrintLabel
    sub     sp, -2
; RPN'ized expression: "( L2540 printf ) "
; Expanded expression: " L2540  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2540:
    db  "]",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2540 , printf )2 "
    push    L2540
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( instr , L2542 printf ) "
; Expanded expression: " (@-10) *(2)  L2542  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2542:
    db  "    %-4s    ax, cl",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-10) , L2542 , printf )4 "
    push    word [bp-10]
    push    L2542
    call    _printf
    sub     sp, -4
; break
    jmp     L2512
; case
; RPN'ized expression: "261 "
; Expanded expression: "261 "
; Expression value: 261
    jmp     L2537
L2536:
    cmp     ax, 261
    jne     L2544
L2537:
; RPN'ized expression: "( instr , stack i 2 + + *u 1 + *u , L2546 printf ) "
; Expanded expression: " (@-10) *(2)  stack (@-4) *(2) 2 + 4 * + 2 + *(2)  L2546  printf ()6 "
; SEGMENT _TEXT
SEGMENT _DATA
L2546:
    db  "    mov     cl, [bp%+d]",10,"    %-4s    ax, cl",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-10) , + *(@-4) 2 * ax 4 + stack ax + ax 2 *(2) ax , L2546 , printf )6 "
    push    word [bp-10]
    mov     ax, [bp-4]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    L2546
    call    _printf
    sub     sp, -6
; break
    jmp     L2512
; }
    jmp     L2512
L2544:
L2512:
; break
    jmp     L2119
; case
; RPN'ized expression: "61 "
; Expanded expression: "61 "
; Expression value: 61
    jmp     L2511
L2510:
    cmp     ax, 61
    jne     L2548
L2511:
; break
    jmp     L2119
; default
L2120:
; RPN'ized expression: "( ( tok GetTokenName ) , L2550 error ) "
; Expanded expression: "  (@-6) *(2)  GetTokenName ()2  L2550  error ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2550:
    db  "WTF?! unexpected token %s",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( *(2) (@-6) , GetTokenName )2 , L2550 , error )4 "
    push    word [bp-6]
    call    _GetTokenName
    sub     sp, -2
    push    ax
    push    L2550
    call    _error
    sub     sp, -4
; break
    jmp     L2119
; }
    jmp     L2119
L2548:
    jmp     L2120
L2119:
; switch
; RPN'ized expression: "tok "
; Expanded expression: "(@-6) *(2) "
; Fused expression:    "*(2) (@-6) "
    mov     ax, [bp-6]
    jmp     L2554
; {
; case
; RPN'ized expression: "61 "
; Expanded expression: "61 "
; Expression value: 61
    jmp     L2555
L2554:
    cmp     ax, 61
    jne     L2556
L2555:
; case
; RPN'ized expression: "68 "
; Expanded expression: "68 "
; Expression value: 68
    jmp     L2557
L2556:
    cmp     ax, 68
    jne     L2558
L2557:
; case
; RPN'ized expression: "69 "
; Expanded expression: "69 "
; Expression value: 69
    jmp     L2559
L2558:
    cmp     ax, 69
    jne     L2560
L2559:
; case
; RPN'ized expression: "65 "
; Expanded expression: "65 "
; Expression value: 65
    jmp     L2561
L2560:
    cmp     ax, 65
    jne     L2562
L2561:
; case
; RPN'ized expression: "66 "
; Expanded expression: "66 "
; Expression value: 66
    jmp     L2563
L2562:
    cmp     ax, 66
    jne     L2564
L2563:
; case
; RPN'ized expression: "67 "
; Expanded expression: "67 "
; Expression value: 67
    jmp     L2565
L2564:
    cmp     ax, 67
    jne     L2566
L2565:
; case
; RPN'ized expression: "70 "
; Expanded expression: "70 "
; Expression value: 70
    jmp     L2567
L2566:
    cmp     ax, 70
    jne     L2568
L2567:
; case
; RPN'ized expression: "71 "
; Expanded expression: "71 "
; Expression value: 71
    jmp     L2569
L2568:
    cmp     ax, 71
    jne     L2570
L2569:
; case
; RPN'ized expression: "72 "
; Expanded expression: "72 "
; Expression value: 72
    jmp     L2571
L2570:
    cmp     ax, 72
    jne     L2572
L2571:
; case
; RPN'ized expression: "73 "
; Expanded expression: "73 "
; Expression value: 73
    jmp     L2573
L2572:
    cmp     ax, 73
    jne     L2574
L2573:
; case
; RPN'ized expression: "74 "
; Expanded expression: "74 "
; Expression value: 74
    jmp     L2575
L2574:
    cmp     ax, 74
    jne     L2576
L2575:
; switch
; RPN'ized expression: "stack i 1 + + *u 0 + *u "
; Expanded expression: "stack (@-4) *(2) 1 + 4 * + 0 + *(2) "
; Fused expression:    "+ *(@-4) 1 * ax 4 + stack ax + ax 0 *(2) ax "
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    jmp     L2580
; {
; case
; RPN'ized expression: "260 "
; Expanded expression: "260 "
; Expression value: 260
    jmp     L2581
L2580:
    cmp     ax, 260
    jne     L2582
L2581:
; RPN'ized expression: "( L2584 printf ) "
; Expanded expression: " L2584  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2584:
    db  "    mov     [",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2584 , printf )2 "
    push    L2584
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( IdentTable stack i 1 + + *u 1 + *u + GenPrintLabel ) "
; Expanded expression: " IdentTable stack (@-4) *(2) 1 + 4 * + 2 + *(2) +  GenPrintLabel ()2 "
; Fused expression:    "( + *(@-4) 1 * ax 4 + stack ax + ax 2 + IdentTable *ax , GenPrintLabel )2 "
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, _IdentTable
    add     ax, cx
    push    ax
    call    _GenPrintLabel
    sub     sp, -2
; RPN'ized expression: "( L2586 printf ) "
; Expanded expression: " L2586  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2586:
    db  "]",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2586 , printf )2 "
    push    L2586
    call    _printf
    sub     sp, -2
; if
; RPN'ized expression: "v 16 / 1 == "
; Expanded expression: "(@-8) *(2) 16 / 1 == "
; Fused expression:    "/ *(@-8) 16 == ax 1 IF! "
    mov     ax, [bp-8]
    cwd
    mov     cx, 16
    idiv    cx
    cmp     ax, 1
    jne     L2588
; RPN'ized expression: "( L2590 printf ) "
; Expanded expression: " L2590  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2590:
    db  ", al",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2590 , printf )2 "
    push    L2590
    call    _printf
    sub     sp, -2
    jmp     L2589
L2588:
; else
; if
; RPN'ized expression: "v 16 / 2 == "
; Expanded expression: "(@-8) *(2) 16 / 2 == "
; Fused expression:    "/ *(@-8) 16 == ax 2 IF! "
    mov     ax, [bp-8]
    cwd
    mov     cx, 16
    idiv    cx
    cmp     ax, 2
    jne     L2592
; RPN'ized expression: "( L2594 printf ) "
; Expanded expression: " L2594  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2594:
    db  ", ax",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2594 , printf )2 "
    push    L2594
    call    _printf
    sub     sp, -2
L2592:
L2589:
; break
    jmp     L2578
; case
; RPN'ized expression: "261 "
; Expanded expression: "261 "
; Expression value: 261
    jmp     L2583
L2582:
    cmp     ax, 261
    jne     L2596
L2583:
; if
; RPN'ized expression: "v 16 / 1 == "
; Expanded expression: "(@-8) *(2) 16 / 1 == "
; Fused expression:    "/ *(@-8) 16 == ax 1 IF! "
    mov     ax, [bp-8]
    cwd
    mov     cx, 16
    idiv    cx
    cmp     ax, 1
    jne     L2598
; RPN'ized expression: "( stack i 1 + + *u 1 + *u , L2600 printf ) "
; Expanded expression: " stack (@-4) *(2) 1 + 4 * + 2 + *(2)  L2600  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2600:
    db  "    mov     [bp%+d], al",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( + *(@-4) 1 * ax 4 + stack ax + ax 2 *(2) ax , L2600 , printf )4 "
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    L2600
    call    _printf
    sub     sp, -4
    jmp     L2599
L2598:
; else
; if
; RPN'ized expression: "v 16 / 2 == "
; Expanded expression: "(@-8) *(2) 16 / 2 == "
; Fused expression:    "/ *(@-8) 16 == ax 2 IF! "
    mov     ax, [bp-8]
    cwd
    mov     cx, 16
    idiv    cx
    cmp     ax, 2
    jne     L2602
; RPN'ized expression: "( stack i 1 + + *u 1 + *u , L2604 printf ) "
; Expanded expression: " stack (@-4) *(2) 1 + 4 * + 2 + *(2)  L2604  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2604:
    db  "    mov     [bp%+d], ax",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( + *(@-4) 1 * ax 4 + stack ax + ax 2 *(2) ax , L2604 , printf )4 "
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    L2604
    call    _printf
    sub     sp, -4
L2602:
L2599:
; break
    jmp     L2578
; case
; RPN'ized expression: "262 "
; Expanded expression: "262 "
; Expression value: 262
    jmp     L2597
L2596:
    cmp     ax, 262
    jne     L2606
L2597:
; case
; RPN'ized expression: "264 "
; Expanded expression: "264 "
; Expression value: 264
    jmp     L2607
L2606:
    cmp     ax, 264
    jne     L2608
L2607:
; if
; RPN'ized expression: "v 16 / 1 == "
; Expanded expression: "(@-8) *(2) 16 / 1 == "
; Fused expression:    "/ *(@-8) 16 == ax 1 IF! "
    mov     ax, [bp-8]
    cwd
    mov     cx, 16
    idiv    cx
    cmp     ax, 1
    jne     L2610
; RPN'ized expression: "( L2612 printf ) "
; Expanded expression: " L2612  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2612:
    db  "    mov     [bx], al",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2612 , printf )2 "
    push    L2612
    call    _printf
    sub     sp, -2
    jmp     L2611
L2610:
; else
; if
; RPN'ized expression: "v 16 / 2 == "
; Expanded expression: "(@-8) *(2) 16 / 2 == "
; Fused expression:    "/ *(@-8) 16 == ax 2 IF! "
    mov     ax, [bp-8]
    cwd
    mov     cx, 16
    idiv    cx
    cmp     ax, 2
    jne     L2614
; RPN'ized expression: "( L2616 printf ) "
; Expanded expression: " L2616  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2616:
    db  "    mov     [bx], ax",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2616 , printf )2 "
    push    L2616
    call    _printf
    sub     sp, -2
L2614:
L2611:
; break
    jmp     L2578
; }
    jmp     L2578
L2608:
L2578:
; if
; RPN'ized expression: "v 16 / 1 == "
; Expanded expression: "(@-8) *(2) 16 / 1 == "
; Fused expression:    "/ *(@-8) 16 == ax 1 IF! "
    mov     ax, [bp-8]
    cwd
    mov     cx, 16
    idiv    cx
    cmp     ax, 1
    jne     L2618
; RPN'ized expression: "( GenExtendAlAx ) "
; Expanded expression: " GenExtendAlAx ()0 "
; Fused expression:    "( GenExtendAlAx )0 "
    call    _GenExtendAlAx
L2618:
; }
    jmp     L2552
L2576:
L2552:
; RPN'ized expression: "i 2 += "
; Expanded expression: "(@-4) 2 +=(2) "
; Fused expression:    "+=(34) *(@-4) 2 "
    mov     ax, [bp-4]
    add     ax, 2
    mov     [bp-4], ax
; break
    jmp     L1801
; case
; RPN'ized expression: "41 "
; Expanded expression: "41 "
; Expression value: 41
    jmp     L2012
L2011:
    cmp     ax, 41
    jne     L2620
L2012:
; if
; RPN'ized expression: "stack i 1 - + *u 0 + *u 16 == "
; Expanded expression: "stack (@-4) *(2) 1 - 4 * + 0 + *(2) 16 == "
; Fused expression:    "- *(@-4) 1 * ax 4 + stack ax + ax 0 == *ax 16 IF! "
    mov     ax, [bp-4]
    sub     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 16
    jne     L2622
; {
; RPN'ized expression: "( L2624 printf ) "
; Expanded expression: " L2624  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2624:
    db  "    call    ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2624 , printf )2 "
    push    L2624
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( IdentTable stack i 1 - + *u 1 + *u + GenPrintLabel ) "
; Expanded expression: " IdentTable stack (@-4) *(2) 1 - 4 * + 2 + *(2) +  GenPrintLabel ()2 "
; Fused expression:    "( - *(@-4) 1 * ax 4 + stack ax + ax 2 + IdentTable *ax , GenPrintLabel )2 "
    mov     ax, [bp-4]
    sub     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, _IdentTable
    add     ax, cx
    push    ax
    call    _GenPrintLabel
    sub     sp, -2
; RPN'ized expression: "( L2626 printf ) "
; Expanded expression: " L2626  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2626:
    db  10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2626 , printf )2 "
    push    L2626
    call    _printf
    sub     sp, -2
; }
    jmp     L2623
L2622:
; else
; {
; RPN'ized expression: "( L2628 printf ) "
; Expanded expression: " L2628  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2628:
    db  "    call    ax",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2628 , printf )2 "
    push    L2628
    call    _printf
    sub     sp, -2
; }
L2623:
; if
; RPN'ized expression: "v "
; Expanded expression: "(@-8) *(2) "
; Fused expression:    "*(2) (@-8) "
    mov     ax, [bp-8]
; JumpIfZero
    test    ax, ax
    jz      L2630
; RPN'ized expression: "( v -u GenLocalAlloc ) "
; Expanded expression: " (@-8) *(2) -u  GenLocalAlloc ()2 "
; Fused expression:    "( *(2) (@-8) -u , GenLocalAlloc )2 "
    mov     ax, [bp-8]
    neg     ax
    push    ax
    call    _GenLocalAlloc
    sub     sp, -2
L2630:
; break
    jmp     L1801
; case
; RPN'ized expression: "40 "
; Expanded expression: "40 "
; Expression value: 40
    jmp     L2621
L2620:
    cmp     ax, 40
    jne     L2632
L2621:
; case
; RPN'ized expression: "22 "
; Expanded expression: "22 "
; Expression value: 22
    jmp     L2633
L2632:
    cmp     ax, 22
    jne     L2634
L2633:
; case
; RPN'ized expression: "76 "
; Expanded expression: "76 "
; Expression value: 76
    jmp     L2635
L2634:
    cmp     ax, 76
    jne     L2636
L2635:
; break
    jmp     L1801
; default
L1802:
; RPN'ized expression: "( ( tok GetTokenName ) , L2638 error ) "
; Expanded expression: "  (@-6) *(2)  GetTokenName ()2  L2638  error ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2638:
    db  "WTF?! unexpected token %s",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( *(2) (@-6) , GetTokenName )2 , L2638 , error )4 "
    push    word [bp-6]
    call    _GetTokenName
    sub     sp, -2
    push    ax
    push    L2638
    call    _error
    sub     sp, -4
; break
    jmp     L1801
; }
    jmp     L1801
L2636:
    jmp     L1802
L1801:
    sub     sp, -6
; }
    jmp     L1798
L1800:
L1649:
    leave
    ret
; SEGMENT _TEXT
; glb GenStrData : (
; prm     insertJump : int
;     ) void
SEGMENT _TEXT
    global  _GenStrData
_GenStrData:
    push    bp
    mov     bp, sp
; loc     insertJump : (@4): int
; loc     i : (@-2): int
    sub     sp, 2
; for
; RPN'ized expression: "i 0 = "
; Expanded expression: "(@-2) 0 =(2) "
; Fused expression:    "=(34) *(@-2) 0 "
    mov     ax, 0
    mov     [bp-2], ax
L2641:
; RPN'ized expression: "i sp < "
; Expanded expression: "(@-2) *(2) sp *(2) < "
; Fused expression:    "< *(@-2) *sp IF! "
    mov     ax, [bp-2]
    cmp     ax, [_sp]
    jge     L2644
    jmp     L2643
L2642:
; RPN'ized expression: "i ++p "
; Expanded expression: "(@-2) ++p(2) "
; Fused expression:    "++p(2) *(@-2) "
    mov     ax, [bp-2]
    inc     word [bp-2]
    jmp     L2641
L2643:
; {
; loc         tok : (@-4): int
    sub     sp, 2
; =
; RPN'ized expression: "stack i + *u 0 + *u "
; Expanded expression: "stack (@-2) *(2) 4 * + 0 + *(2) "
; Fused expression:    "* *(@-2) 4 + stack ax + ax 0 =(34) *(@-4) *ax "
    mov     ax, [bp-2]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-4], ax
; loc         p : (@-6): * char
    sub     sp, 2
; =
; RPN'ized expression: "IdentTable stack i + *u 1 + *u + "
; Expanded expression: "IdentTable stack (@-2) *(2) 4 * + 2 + *(2) + "
; Fused expression:    "* *(@-2) 4 + stack ax + ax 2 + IdentTable *ax =(34) *(@-6) ax "
    mov     ax, [bp-2]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, _IdentTable
    add     ax, cx
    mov     [bp-6], ax
; if
; RPN'ized expression: "tok 16 == ( p *u isdigit ) && "
; Expanded expression: "(@-4) *(2) 16 == _Bool [sh&&->2647]  (@-6) *(2) *(1)  isdigit ()2 _Bool &&[2647] "
; Fused expression:    "== *(@-4) 16 _Bool [sh&&->2647] ( *(2) (@-6) *(1) ax , isdigit )2 _Bool &&[2647] "
    mov     ax, [bp-4]
    cmp     ax, 16
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L2647
    mov     ax, [bp-6]
    mov     bx, ax
    mov     al, [bx]
    cbw
    push    ax
    call    _isdigit
    sub     sp, -2
    test    ax, ax
    setnz   al
    cbw
L2647:
; JumpIfZero
    test    ax, ax
    jz      L2645
; {
; loc             label : (@-8): int
    sub     sp, 2
; =
; RPN'ized expression: "( p atoi ) "
; Expanded expression: " (@-6) *(2)  atoi ()2 "
; Fused expression:    "( *(2) (@-6) , atoi )2 =(34) *(@-8) ax "
    push    word [bp-6]
    call    _atoi
    sub     sp, -2
    mov     [bp-8], ax
; loc             quot : (@-10): int
    sub     sp, 2
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "=(34) *(@-10) 0 "
    mov     ax, 0
    mov     [bp-10], ax
; loc             len : (@-12): int
    sub     sp, 2
; RPN'ized expression: "p ( label FindString ) = "
; Expanded expression: "(@-6)  (@-8) *(2)  FindString ()2 =(2) "
; Fused expression:    "( *(2) (@-8) , FindString )2 =(34) *(@-6) ax "
    push    word [bp-8]
    call    _FindString
    sub     sp, -2
    mov     [bp-6], ax
; RPN'ized expression: "len p ++p *u = "
; Expanded expression: "(@-12) (@-6) ++p(2) *(1) =(2) "
; Fused expression:    "++p(2) *(@-6) =(33) *(@-12) *ax "
    mov     ax, [bp-6]
    inc     word [bp-6]
    mov     bx, ax
    mov     al, [bx]
    cbw
    mov     [bp-12], ax
; if
; RPN'ized expression: "OutputFormat 0 == "
; Expanded expression: "OutputFormat *(2) 0 == "
; Fused expression:    "== *OutputFormat 0 IF! "
    mov     ax, [_OutputFormat]
    cmp     ax, 0
    jne     L2648
; {
; if
; RPN'ized expression: "insertJump "
; Expanded expression: "(@4) *(2) "
; Fused expression:    "*(2) (@4) "
    mov     ax, [bp+4]
; JumpIfZero
    test    ax, ax
    jz      L2650
; RPN'ized expression: "( label 1 + GenJumpUncond ) "
; Expanded expression: " (@-8) *(2) 1 +  GenJumpUncond ()2 "
; Fused expression:    "( + *(@-8) 1 , GenJumpUncond )2 "
    mov     ax, [bp-8]
    add     ax, 1
    push    ax
    call    _GenJumpUncond
    sub     sp, -2
L2650:
; }
    jmp     L2649
L2648:
; else
; {
; if
; RPN'ized expression: "insertJump "
; Expanded expression: "(@4) *(2) "
; Fused expression:    "*(2) (@4) "
    mov     ax, [bp+4]
; JumpIfZero
    test    ax, ax
    jz      L2652
; RPN'ized expression: "( CodeFooter printf ) "
; Expanded expression: " CodeFooter *(2)  printf ()2 "
; Fused expression:    "( *(2) CodeFooter , printf )2 "
    push    word [_CodeFooter]
    call    _printf
    sub     sp, -2
L2652:
; RPN'ized expression: "( DataHeader printf ) "
; Expanded expression: " DataHeader *(2)  printf ()2 "
; Fused expression:    "( *(2) DataHeader , printf )2 "
    push    word [_DataHeader]
    call    _printf
    sub     sp, -2
; }
L2649:
; RPN'ized expression: "( label GenNumLabel ) "
; Expanded expression: " (@-8) *(2)  GenNumLabel ()2 "
; Fused expression:    "( *(2) (@-8) , GenNumLabel )2 "
    push    word [bp-8]
    call    _GenNumLabel
    sub     sp, -2
; RPN'ized expression: "( L2654 printf ) "
; Expanded expression: " L2654  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2654:
    db  "    db  ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2654 , printf )2 "
    push    L2654
    call    _printf
    sub     sp, -2
; while
; RPN'ized expression: "len --p "
; Expanded expression: "(@-12) --p(2) "
L2656:
; Fused expression:    "--p(2) *(@-12) "
    mov     ax, [bp-12]
    dec     word [bp-12]
; JumpIfZero
    test    ax, ax
    jz      L2657
; {
; if
; RPN'ized expression: "p *u 32 >= p *u 126 <= && p *u 34 != && "
; Expanded expression: "(@-6) *(2) *(1) 32 >= _Bool [sh&&->2661] (@-6) *(2) *(1) 126 <= _Bool &&[2661] _Bool [sh&&->2660] (@-6) *(2) *(1) 34 != _Bool &&[2660] "
; Fused expression:    "*(2) (@-6) >= *ax 32 _Bool [sh&&->2661] *(2) (@-6) <= *ax 126 _Bool &&[2661] _Bool [sh&&->2660] *(2) (@-6) != *ax 34 _Bool &&[2660] "
    mov     ax, [bp-6]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 32
    setge   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L2661
    mov     ax, [bp-6]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 126
    setle   al
    cbw
    test    ax, ax
    setnz   al
    cbw
L2661:
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L2660
    mov     ax, [bp-6]
    mov     bx, ax
    mov     al, [bx]
    cbw
    cmp     ax, 34
    setne   al
    cbw
    test    ax, ax
    setnz   al
    cbw
L2660:
; JumpIfZero
    test    ax, ax
    jz      L2658
; {
; if
; RPN'ized expression: "quot 0 == "
; Expanded expression: "(@-10) *(2) 0 == "
; Fused expression:    "== *(@-10) 0 IF! "
    mov     ax, [bp-10]
    cmp     ax, 0
    jne     L2662
; {
; RPN'ized expression: "quot 1 = "
; Expanded expression: "(@-10) 1 =(2) "
; Fused expression:    "=(34) *(@-10) 1 "
    mov     ax, 1
    mov     [bp-10], ax
; RPN'ized expression: "( L2664 printf ) "
; Expanded expression: " L2664  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2664:
    db  34,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2664 , printf )2 "
    push    L2664
    call    _printf
    sub     sp, -2
; }
L2662:
; RPN'ized expression: "( p *u , L2666 printf ) "
; Expanded expression: " (@-6) *(2) *(1)  L2666  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2666:
    db  "%c",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-6) *(1) ax , L2666 , printf )4 "
    mov     ax, [bp-6]
    mov     bx, ax
    mov     al, [bx]
    cbw
    push    ax
    push    L2666
    call    _printf
    sub     sp, -4
; }
    jmp     L2659
L2658:
; else
; {
; if
; RPN'ized expression: "quot "
; Expanded expression: "(@-10) *(2) "
; Fused expression:    "*(2) (@-10) "
    mov     ax, [bp-10]
; JumpIfZero
    test    ax, ax
    jz      L2668
; {
; RPN'ized expression: "quot 0 = "
; Expanded expression: "(@-10) 0 =(2) "
; Fused expression:    "=(34) *(@-10) 0 "
    mov     ax, 0
    mov     [bp-10], ax
; RPN'ized expression: "( L2670 printf ) "
; Expanded expression: " L2670  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2670:
    db  34,",",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2670 , printf )2 "
    push    L2670
    call    _printf
    sub     sp, -2
; }
L2668:
; RPN'ized expression: "( p *u , L2672 printf ) "
; Expanded expression: " (@-6) *(2) *(1)  L2672  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2672:
    db  "%d",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-6) *(1) ax , L2672 , printf )4 "
    mov     ax, [bp-6]
    mov     bx, ax
    mov     al, [bx]
    cbw
    push    ax
    push    L2672
    call    _printf
    sub     sp, -4
; if
; RPN'ized expression: "len "
; Expanded expression: "(@-12) *(2) "
; Fused expression:    "*(2) (@-12) "
    mov     ax, [bp-12]
; JumpIfZero
    test    ax, ax
    jz      L2674
; RPN'ized expression: "( L2676 printf ) "
; Expanded expression: " L2676  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2676:
    db  ",",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2676 , printf )2 "
    push    L2676
    call    _printf
    sub     sp, -2
L2674:
; }
L2659:
; RPN'ized expression: "p ++p "
; Expanded expression: "(@-6) ++p(2) "
; Fused expression:    "++p(2) *(@-6) "
    mov     ax, [bp-6]
    inc     word [bp-6]
; }
    jmp     L2656
L2657:
; if
; RPN'ized expression: "quot "
; Expanded expression: "(@-10) *(2) "
; Fused expression:    "*(2) (@-10) "
    mov     ax, [bp-10]
; JumpIfZero
    test    ax, ax
    jz      L2678
; RPN'ized expression: "( L2680 printf ) "
; Expanded expression: " L2680  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2680:
    db  34,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2680 , printf )2 "
    push    L2680
    call    _printf
    sub     sp, -2
L2678:
; RPN'ized expression: "( L2682 printf ) "
; Expanded expression: " L2682  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2682:
    db  10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2682 , printf )2 "
    push    L2682
    call    _printf
    sub     sp, -2
; if
; RPN'ized expression: "OutputFormat 0 == "
; Expanded expression: "OutputFormat *(2) 0 == "
; Fused expression:    "== *OutputFormat 0 IF! "
    mov     ax, [_OutputFormat]
    cmp     ax, 0
    jne     L2684
; {
; if
; RPN'ized expression: "insertJump "
; Expanded expression: "(@4) *(2) "
; Fused expression:    "*(2) (@4) "
    mov     ax, [bp+4]
; JumpIfZero
    test    ax, ax
    jz      L2686
; RPN'ized expression: "( label 1 + GenNumLabel ) "
; Expanded expression: " (@-8) *(2) 1 +  GenNumLabel ()2 "
; Fused expression:    "( + *(@-8) 1 , GenNumLabel )2 "
    mov     ax, [bp-8]
    add     ax, 1
    push    ax
    call    _GenNumLabel
    sub     sp, -2
L2686:
; }
    jmp     L2685
L2684:
; else
; {
; RPN'ized expression: "( DataFooter printf ) "
; Expanded expression: " DataFooter *(2)  printf ()2 "
; Fused expression:    "( *(2) DataFooter , printf )2 "
    push    word [_DataFooter]
    call    _printf
    sub     sp, -2
; if
; RPN'ized expression: "insertJump "
; Expanded expression: "(@4) *(2) "
; Fused expression:    "*(2) (@4) "
    mov     ax, [bp+4]
; JumpIfZero
    test    ax, ax
    jz      L2688
; RPN'ized expression: "( CodeHeader printf ) "
; Expanded expression: " CodeHeader *(2)  printf ()2 "
; Fused expression:    "( *(2) CodeHeader , printf )2 "
    push    word [_CodeHeader]
    call    _printf
    sub     sp, -2
L2688:
; }
L2685:
    sub     sp, -6
; }
L2645:
    sub     sp, -4
; }
    jmp     L2642
L2644:
L2640:
    leave
    ret
; SEGMENT _TEXT
; glb GenExpr : (void) void
SEGMENT _TEXT
    global  _GenExpr
_GenExpr:
    push    bp
    mov     bp, sp
; RPN'ized expression: "( 1 GenStrData ) "
; Expanded expression: " 1  GenStrData ()2 "
; Fused expression:    "( 1 , GenStrData )2 "
    push    1
    call    _GenStrData
    sub     sp, -2
; RPN'ized expression: "( GenExpr1 ) "
; Expanded expression: " GenExpr1 ()0 "
; Fused expression:    "( GenExpr1 )0 "
    call    _GenExpr1
L2690:
    leave
    ret
; SEGMENT _TEXT
; glb push2 : (
; prm     v : int
; prm     v2 : int
;     ) void
SEGMENT _TEXT
    global  _push2
_push2:
    push    bp
    mov     bp, sp
; loc     v : (@4): int
; loc     v2 : (@6): int
; if
; RPN'ized expression: "sp 100 >= "
; Expanded expression: "sp *(2) 100 >= "
; Fused expression:    ">= *sp 100 IF! "
    mov     ax, [_sp]
    cmp     ax, 100
    jl      L2692
; RPN'ized expression: "( L2694 error ) "
; Expanded expression: " L2694  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2694:
    db  "stack overflow!",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2694 , error )2 "
    push    L2694
    call    _error
    sub     sp, -2
L2692:
; RPN'ized expression: "stack sp + *u 0 + *u v = "
; Expanded expression: "stack sp *(2) 4 * + 0 + (@4) *(2) =(2) "
; Fused expression:    "* *sp 4 + stack ax + ax 0 =(34) *ax *(@4) "
    mov     ax, [_sp]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bp+4]
    mov     [bx], ax
; RPN'ized expression: "stack sp ++p + *u 1 + *u v2 = "
; Expanded expression: "stack sp ++p(2) 4 * + 2 + (@6) *(2) =(2) "
; Fused expression:    "++p(2) *sp * ax 4 + stack ax + ax 2 =(34) *ax *(@6) "
    mov     ax, [_sp]
    inc     word [_sp]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bp+6]
    mov     [bx], ax
L2691:
    leave
    ret
; SEGMENT _TEXT
; glb push : (
; prm     v : int
;     ) void
SEGMENT _TEXT
    global  _push
_push:
    push    bp
    mov     bp, sp
; loc     v : (@4): int
; RPN'ized expression: "( 0 , v push2 ) "
; Expanded expression: " 0  (@4) *(2)  push2 ()4 "
; Fused expression:    "( 0 , *(2) (@4) , push2 )4 "
    push    0
    push    word [bp+4]
    call    _push2
    sub     sp, -4
L2696:
    leave
    ret
; SEGMENT _TEXT
; glb stacktop : () int
SEGMENT _TEXT
    global  _stacktop
_stacktop:
    push    bp
    mov     bp, sp
; if
; RPN'ized expression: "sp 0 == "
; Expanded expression: "sp *(2) 0 == "
; Fused expression:    "== *sp 0 IF! "
    mov     ax, [_sp]
    cmp     ax, 0
    jne     L2698
; RPN'ized expression: "( L2700 error ) "
; Expanded expression: " L2700  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2700:
    db  "stack underflow!",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2700 , error )2 "
    push    L2700
    call    _error
    sub     sp, -2
L2698:
; return
; RPN'ized expression: "stack sp 1 - + *u 0 + *u "
; Expanded expression: "stack sp *(2) 1 - 4 * + 0 + *(2) "
; Fused expression:    "- *sp 1 * ax 4 + stack ax + ax 0 *(2) ax "
    mov     ax, [_sp]
    sub     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    jmp     L2697
L2697:
    leave
    ret
; SEGMENT _TEXT
; glb pop2 : (
; prm     v2 : * int
;     ) int
SEGMENT _TEXT
    global  _pop2
_pop2:
    push    bp
    mov     bp, sp
; loc     v2 : (@4): * int
; loc     v : (@-2): int
    sub     sp, 2
; =
; RPN'ized expression: "( stacktop ) "
; Expanded expression: " stacktop ()0 "
; Fused expression:    "( stacktop )0 =(34) *(@-2) ax "
    call    _stacktop
    mov     [bp-2], ax
; RPN'ized expression: "v2 *u stack sp 1 - + *u 1 + *u = "
; Expanded expression: "(@4) *(2) stack sp *(2) 1 - 4 * + 2 + *(2) =(2) "
; Fused expression:    "*(2) (@4) push-ax - *sp 1 * ax 4 + stack ax + ax 2 =(34) **sp *ax "
    mov     ax, [bp+4]
    push    ax
    mov     ax, [_sp]
    sub     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bx]
    pop     bx
    mov     [bx], ax
; RPN'ized expression: "sp --p "
; Expanded expression: "sp --p(2) "
; Fused expression:    "--p(2) *sp "
    mov     ax, [_sp]
    dec     word [_sp]
; return
; RPN'ized expression: "v "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
    mov     ax, [bp-2]
    jmp     L2702
L2702:
    leave
    ret
; SEGMENT _TEXT
; glb pop : () int
SEGMENT _TEXT
    global  _pop
_pop:
    push    bp
    mov     bp, sp
; loc     v2 : (@-2): int
    sub     sp, 2
; return
; RPN'ized expression: "( v2 &u pop2 ) "
; Expanded expression: " (@-2)  pop2 ()2 "
; Fused expression:    "( (@-2) , pop2 )2 "
    lea     ax, [bp-2]
    push    ax
    call    _pop2
    sub     sp, -2
    jmp     L2703
L2703:
    leave
    ret
; SEGMENT _TEXT
; glb ins2 : (
; prm     pos : int
; prm     v : int
; prm     v2 : int
;     ) void
SEGMENT _TEXT
    global  _ins2
_ins2:
    push    bp
    mov     bp, sp
; loc     pos : (@4): int
; loc     v : (@6): int
; loc     v2 : (@8): int
; if
; RPN'ized expression: "sp 100 >= "
; Expanded expression: "sp *(2) 100 >= "
; Fused expression:    ">= *sp 100 IF! "
    mov     ax, [_sp]
    cmp     ax, 100
    jl      L2705
; RPN'ized expression: "( L2707 error ) "
; Expanded expression: " L2707  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2707:
    db  "stack overflow!",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2707 , error )2 "
    push    L2707
    call    _error
    sub     sp, -2
L2705:
; RPN'ized expression: "( stack 0 + *u sizeof sp pos - * , stack pos + *u &u , stack pos 1 + + *u &u memmove ) "
; Expanded expression: " 4 sp *(2) (@4) *(2) - *  stack (@4) *(2) 4 * +  stack (@4) *(2) 1 + 4 * +  memmove ()6 "
; Fused expression:    "( - *sp *(@4) * 4 ax , * *(@4) 4 + stack ax , + *(@4) 1 * ax 4 + stack ax , memmove )6 "
    mov     ax, [_sp]
    sub     ax, [bp+4]
    mov     cx, ax
    mov     ax, 4
    mul     cx
    push    ax
    mov     ax, [bp+4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    push    ax
    mov     ax, [bp+4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    push    ax
    call    _memmove
    sub     sp, -6
; RPN'ized expression: "stack pos + *u 0 + *u v = "
; Expanded expression: "stack (@4) *(2) 4 * + 0 + (@6) *(2) =(2) "
; Fused expression:    "* *(@4) 4 + stack ax + ax 0 =(34) *ax *(@6) "
    mov     ax, [bp+4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bp+6]
    mov     [bx], ax
; RPN'ized expression: "stack pos + *u 1 + *u v2 = "
; Expanded expression: "stack (@4) *(2) 4 * + 2 + (@8) *(2) =(2) "
; Fused expression:    "* *(@4) 4 + stack ax + ax 2 =(34) *ax *(@8) "
    mov     ax, [bp+4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bp+8]
    mov     [bx], ax
; RPN'ized expression: "sp ++p "
; Expanded expression: "sp ++p(2) "
; Fused expression:    "++p(2) *sp "
    mov     ax, [_sp]
    inc     word [_sp]
L2704:
    leave
    ret
; SEGMENT _TEXT
; glb ins : (
; prm     pos : int
; prm     v : int
;     ) void
SEGMENT _TEXT
    global  _ins
_ins:
    push    bp
    mov     bp, sp
; loc     pos : (@4): int
; loc     v : (@6): int
; RPN'ized expression: "( 0 , v , pos ins2 ) "
; Expanded expression: " 0  (@6) *(2)  (@4) *(2)  ins2 ()6 "
; Fused expression:    "( 0 , *(2) (@6) , *(2) (@4) , ins2 )6 "
    push    0
    push    word [bp+6]
    push    word [bp+4]
    call    _ins2
    sub     sp, -6
L2709:
    leave
    ret
; SEGMENT _TEXT
; glb del : (
; prm     pos : int
; prm     cnt : int
;     ) void
SEGMENT _TEXT
    global  _del
_del:
    push    bp
    mov     bp, sp
; loc     pos : (@4): int
; loc     cnt : (@6): int
; RPN'ized expression: "( stack 0 + *u sizeof sp pos cnt + - * , stack pos cnt + + *u , stack pos + *u memmove ) "
; Expanded expression: " 4 sp *(2) (@4) *(2) (@6) *(2) + - *  stack (@4) *(2) (@6) *(2) + 4 * +  stack (@4) *(2) 4 * +  memmove ()6 "
; Fused expression:    "( + *(@4) *(@6) - *sp ax * 4 ax , + *(@4) *(@6) * ax 4 + stack ax , * *(@4) 4 + stack ax , memmove )6 "
    mov     ax, [bp+4]
    add     ax, [bp+6]
    mov     cx, ax
    mov     ax, [_sp]
    sub     ax, cx
    mov     cx, ax
    mov     ax, 4
    mul     cx
    push    ax
    mov     ax, [bp+4]
    add     ax, [bp+6]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    push    ax
    mov     ax, [bp+4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    push    ax
    call    _memmove
    sub     sp, -6
; RPN'ized expression: "sp cnt -= "
; Expanded expression: "sp (@6) *(2) -=(2) "
; Fused expression:    "-=(34) *sp *(@6) "
    mov     ax, [_sp]
    sub     ax, [bp+6]
    mov     [_sp], ax
L2710:
    leave
    ret
; SEGMENT _TEXT
; glb pushop2 : (
; prm     v : int
; prm     v2 : int
;     ) void
SEGMENT _TEXT
    global  _pushop2
_pushop2:
    push    bp
    mov     bp, sp
; loc     v : (@4): int
; loc     v2 : (@6): int
; if
; RPN'ized expression: "opsp 100 >= "
; Expanded expression: "opsp *(2) 100 >= "
; Fused expression:    ">= *opsp 100 IF! "
    mov     ax, [_opsp]
    cmp     ax, 100
    jl      L2712
; RPN'ized expression: "( L2714 error ) "
; Expanded expression: " L2714  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2714:
    db  "operator stack overflow!",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2714 , error )2 "
    push    L2714
    call    _error
    sub     sp, -2
L2712:
; RPN'ized expression: "opstack opsp + *u 0 + *u v = "
; Expanded expression: "opstack opsp *(2) 4 * + 0 + (@4) *(2) =(2) "
; Fused expression:    "* *opsp 4 + opstack ax + ax 0 =(34) *ax *(@4) "
    mov     ax, [_opsp]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _opstack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bp+4]
    mov     [bx], ax
; RPN'ized expression: "opstack opsp ++p + *u 1 + *u v2 = "
; Expanded expression: "opstack opsp ++p(2) 4 * + 2 + (@6) *(2) =(2) "
; Fused expression:    "++p(2) *opsp * ax 4 + opstack ax + ax 2 =(34) *ax *(@6) "
    mov     ax, [_opsp]
    inc     word [_opsp]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _opstack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bp+6]
    mov     [bx], ax
L2711:
    leave
    ret
; SEGMENT _TEXT
; glb pushop : (
; prm     v : int
;     ) void
SEGMENT _TEXT
    global  _pushop
_pushop:
    push    bp
    mov     bp, sp
; loc     v : (@4): int
; RPN'ized expression: "( 0 , v pushop2 ) "
; Expanded expression: " 0  (@4) *(2)  pushop2 ()4 "
; Fused expression:    "( 0 , *(2) (@4) , pushop2 )4 "
    push    0
    push    word [bp+4]
    call    _pushop2
    sub     sp, -4
L2716:
    leave
    ret
; SEGMENT _TEXT
; glb opstacktop : () int
SEGMENT _TEXT
    global  _opstacktop
_opstacktop:
    push    bp
    mov     bp, sp
; if
; RPN'ized expression: "opsp 0 == "
; Expanded expression: "opsp *(2) 0 == "
; Fused expression:    "== *opsp 0 IF! "
    mov     ax, [_opsp]
    cmp     ax, 0
    jne     L2718
; RPN'ized expression: "( L2720 error ) "
; Expanded expression: " L2720  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2720:
    db  "operator stack underflow!",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2720 , error )2 "
    push    L2720
    call    _error
    sub     sp, -2
L2718:
; return
; RPN'ized expression: "opstack opsp 1 - + *u 0 + *u "
; Expanded expression: "opstack opsp *(2) 1 - 4 * + 0 + *(2) "
; Fused expression:    "- *opsp 1 * ax 4 + opstack ax + ax 0 *(2) ax "
    mov     ax, [_opsp]
    sub     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _opstack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    jmp     L2717
L2717:
    leave
    ret
; SEGMENT _TEXT
; glb popop2 : (
; prm     v2 : * int
;     ) int
SEGMENT _TEXT
    global  _popop2
_popop2:
    push    bp
    mov     bp, sp
; loc     v2 : (@4): * int
; loc     v : (@-2): int
    sub     sp, 2
; =
; RPN'ized expression: "( opstacktop ) "
; Expanded expression: " opstacktop ()0 "
; Fused expression:    "( opstacktop )0 =(34) *(@-2) ax "
    call    _opstacktop
    mov     [bp-2], ax
; RPN'ized expression: "v2 *u opstack opsp 1 - + *u 1 + *u = "
; Expanded expression: "(@4) *(2) opstack opsp *(2) 1 - 4 * + 2 + *(2) =(2) "
; Fused expression:    "*(2) (@4) push-ax - *opsp 1 * ax 4 + opstack ax + ax 2 =(34) **sp *ax "
    mov     ax, [bp+4]
    push    ax
    mov     ax, [_opsp]
    sub     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _opstack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bx]
    pop     bx
    mov     [bx], ax
; RPN'ized expression: "opsp --p "
; Expanded expression: "opsp --p(2) "
; Fused expression:    "--p(2) *opsp "
    mov     ax, [_opsp]
    dec     word [_opsp]
; return
; RPN'ized expression: "v "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
    mov     ax, [bp-2]
    jmp     L2722
L2722:
    leave
    ret
; SEGMENT _TEXT
; glb popop : () int
SEGMENT _TEXT
    global  _popop
_popop:
    push    bp
    mov     bp, sp
; loc     v2 : (@-2): int
    sub     sp, 2
; return
; RPN'ized expression: "( v2 &u popop2 ) "
; Expanded expression: " (@-2)  popop2 ()2 "
; Fused expression:    "( (@-2) , popop2 )2 "
    lea     ax, [bp-2]
    push    ax
    call    _popop2
    sub     sp, -2
    jmp     L2723
L2723:
    leave
    ret
; SEGMENT _TEXT
; glb isop : (
; prm     tok : int
;     ) int
SEGMENT _TEXT
    global  _isop
_isop:
    push    bp
    mov     bp, sp
; loc     tok : (@4): int
; switch
; RPN'ized expression: "tok "
; Expanded expression: "(@4) *(2) "
; Fused expression:    "*(2) (@4) "
    mov     ax, [bp+4]
    jmp     L2727
; {
; case
; RPN'ized expression: "33 "
; Expanded expression: "33 "
; Expression value: 33
    jmp     L2728
L2727:
    cmp     ax, 33
    jne     L2729
L2728:
; case
; RPN'ized expression: "126 "
; Expanded expression: "126 "
; Expression value: 126
    jmp     L2730
L2729:
    cmp     ax, 126
    jne     L2731
L2730:
; case
; RPN'ized expression: "38 "
; Expanded expression: "38 "
; Expression value: 38
    jmp     L2732
L2731:
    cmp     ax, 38
    jne     L2733
L2732:
; case
; RPN'ized expression: "42 "
; Expanded expression: "42 "
; Expression value: 42
    jmp     L2734
L2733:
    cmp     ax, 42
    jne     L2735
L2734:
; case
; RPN'ized expression: "47 "
; Expanded expression: "47 "
; Expression value: 47
    jmp     L2736
L2735:
    cmp     ax, 47
    jne     L2737
L2736:
; case
; RPN'ized expression: "37 "
; Expanded expression: "37 "
; Expression value: 37
    jmp     L2738
L2737:
    cmp     ax, 37
    jne     L2739
L2738:
; case
; RPN'ized expression: "43 "
; Expanded expression: "43 "
; Expression value: 43
    jmp     L2740
L2739:
    cmp     ax, 43
    jne     L2741
L2740:
; case
; RPN'ized expression: "45 "
; Expanded expression: "45 "
; Expression value: 45
    jmp     L2742
L2741:
    cmp     ax, 45
    jne     L2743
L2742:
; case
; RPN'ized expression: "124 "
; Expanded expression: "124 "
; Expression value: 124
    jmp     L2744
L2743:
    cmp     ax, 124
    jne     L2745
L2744:
; case
; RPN'ized expression: "94 "
; Expanded expression: "94 "
; Expression value: 94
    jmp     L2746
L2745:
    cmp     ax, 94
    jne     L2747
L2746:
; case
; RPN'ized expression: "60 "
; Expanded expression: "60 "
; Expression value: 60
    jmp     L2748
L2747:
    cmp     ax, 60
    jne     L2749
L2748:
; case
; RPN'ized expression: "62 "
; Expanded expression: "62 "
; Expression value: 62
    jmp     L2750
L2749:
    cmp     ax, 62
    jne     L2751
L2750:
; case
; RPN'ized expression: "61 "
; Expanded expression: "61 "
; Expression value: 61
    jmp     L2752
L2751:
    cmp     ax, 61
    jne     L2753
L2752:
; case
; RPN'ized expression: "7 "
; Expanded expression: "7 "
; Expression value: 7
    jmp     L2754
L2753:
    cmp     ax, 7
    jne     L2755
L2754:
; case
; RPN'ized expression: "6 "
; Expanded expression: "6 "
; Expression value: 6
    jmp     L2756
L2755:
    cmp     ax, 6
    jne     L2757
L2756:
; case
; RPN'ized expression: "8 "
; Expanded expression: "8 "
; Expression value: 8
    jmp     L2758
L2757:
    cmp     ax, 8
    jne     L2759
L2758:
; case
; RPN'ized expression: "9 "
; Expanded expression: "9 "
; Expression value: 9
    jmp     L2760
L2759:
    cmp     ax, 9
    jne     L2761
L2760:
; case
; RPN'ized expression: "10 "
; Expanded expression: "10 "
; Expression value: 10
    jmp     L2762
L2761:
    cmp     ax, 10
    jne     L2763
L2762:
; case
; RPN'ized expression: "11 "
; Expanded expression: "11 "
; Expression value: 11
    jmp     L2764
L2763:
    cmp     ax, 11
    jne     L2765
L2764:
; case
; RPN'ized expression: "4 "
; Expanded expression: "4 "
; Expression value: 4
    jmp     L2766
L2765:
    cmp     ax, 4
    jne     L2767
L2766:
; case
; RPN'ized expression: "5 "
; Expanded expression: "5 "
; Expression value: 5
    jmp     L2768
L2767:
    cmp     ax, 5
    jne     L2769
L2768:
; case
; RPN'ized expression: "12 "
; Expanded expression: "12 "
; Expression value: 12
    jmp     L2770
L2769:
    cmp     ax, 12
    jne     L2771
L2770:
; case
; RPN'ized expression: "13 "
; Expanded expression: "13 "
; Expression value: 13
    jmp     L2772
L2771:
    cmp     ax, 13
    jne     L2773
L2772:
; case
; RPN'ized expression: "27 "
; Expanded expression: "27 "
; Expression value: 27
    jmp     L2774
L2773:
    cmp     ax, 27
    jne     L2775
L2774:
; case
; RPN'ized expression: "65 "
; Expanded expression: "65 "
; Expression value: 65
    jmp     L2776
L2775:
    cmp     ax, 65
    jne     L2777
L2776:
; case
; RPN'ized expression: "66 "
; Expanded expression: "66 "
; Expression value: 66
    jmp     L2778
L2777:
    cmp     ax, 66
    jne     L2779
L2778:
; case
; RPN'ized expression: "67 "
; Expanded expression: "67 "
; Expression value: 67
    jmp     L2780
L2779:
    cmp     ax, 67
    jne     L2781
L2780:
; case
; RPN'ized expression: "68 "
; Expanded expression: "68 "
; Expression value: 68
    jmp     L2782
L2781:
    cmp     ax, 68
    jne     L2783
L2782:
; case
; RPN'ized expression: "69 "
; Expanded expression: "69 "
; Expression value: 69
    jmp     L2784
L2783:
    cmp     ax, 69
    jne     L2785
L2784:
; case
; RPN'ized expression: "70 "
; Expanded expression: "70 "
; Expression value: 70
    jmp     L2786
L2785:
    cmp     ax, 70
    jne     L2787
L2786:
; case
; RPN'ized expression: "71 "
; Expanded expression: "71 "
; Expression value: 71
    jmp     L2788
L2787:
    cmp     ax, 71
    jne     L2789
L2788:
; case
; RPN'ized expression: "72 "
; Expanded expression: "72 "
; Expression value: 72
    jmp     L2790
L2789:
    cmp     ax, 72
    jne     L2791
L2790:
; case
; RPN'ized expression: "73 "
; Expanded expression: "73 "
; Expression value: 73
    jmp     L2792
L2791:
    cmp     ax, 73
    jne     L2793
L2792:
; case
; RPN'ized expression: "74 "
; Expanded expression: "74 "
; Expression value: 74
    jmp     L2794
L2793:
    cmp     ax, 74
    jne     L2795
L2794:
; return
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
    mov     ax, 1
    jmp     L2724
; default
L2726:
; return
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "0 "
    mov     ax, 0
    jmp     L2724
; }
    jmp     L2725
L2795:
    jmp     L2726
L2725:
L2724:
    leave
    ret
; SEGMENT _TEXT
; glb isunary : (
; prm     tok : int
;     ) int
SEGMENT _TEXT
    global  _isunary
_isunary:
    push    bp
    mov     bp, sp
; loc     tok : (@4): int
; return
; RPN'ized expression: "tok 33 == tok 126 == || tok 12 == || tok 13 == || tok 27 == || "
; Expanded expression: "(@4) *(2) 33 == _Bool [sh||->2801] (@4) *(2) 126 == _Bool ||[2801] _Bool [sh||->2800] (@4) *(2) 12 == _Bool ||[2800] _Bool [sh||->2799] (@4) *(2) 13 == _Bool ||[2799] _Bool [sh||->2798] (@4) *(2) 27 == _Bool ||[2798] "
; Fused expression:    "== *(@4) 33 _Bool [sh||->2801] == *(@4) 126 _Bool ||[2801] _Bool [sh||->2800] == *(@4) 12 _Bool ||[2800] _Bool [sh||->2799] == *(@4) 13 _Bool ||[2799] _Bool [sh||->2798] == *(@4) 27 _Bool ||[2798] "
    mov     ax, [bp+4]
    cmp     ax, 33
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L2801
    mov     ax, [bp+4]
    cmp     ax, 126
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L2801:
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L2800
    mov     ax, [bp+4]
    cmp     ax, 12
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L2800:
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L2799
    mov     ax, [bp+4]
    cmp     ax, 13
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L2799:
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L2798
    mov     ax, [bp+4]
    cmp     ax, 27
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L2798:
    jmp     L2797
L2797:
    leave
    ret
; SEGMENT _TEXT
; glb preced : (
; prm     tok : int
;     ) int
SEGMENT _TEXT
    global  _preced
_preced:
    push    bp
    mov     bp, sp
; loc     tok : (@4): int
; switch
; RPN'ized expression: "tok "
; Expanded expression: "(@4) *(2) "
; Fused expression:    "*(2) (@4) "
    mov     ax, [bp+4]
    jmp     L2805
; {
; case
; RPN'ized expression: "42 "
; Expanded expression: "42 "
; Expression value: 42
    jmp     L2806
L2805:
    cmp     ax, 42
    jne     L2807
L2806:
; case
; RPN'ized expression: "47 "
; Expanded expression: "47 "
; Expression value: 47
    jmp     L2808
L2807:
    cmp     ax, 47
    jne     L2809
L2808:
; case
; RPN'ized expression: "37 "
; Expanded expression: "37 "
; Expression value: 37
    jmp     L2810
L2809:
    cmp     ax, 37
    jne     L2811
L2810:
; return
; RPN'ized expression: "11 "
; Expanded expression: "11 "
; Expression value: 11
; Fused expression:    "11 "
    mov     ax, 11
    jmp     L2802
; case
; RPN'ized expression: "43 "
; Expanded expression: "43 "
; Expression value: 43
    jmp     L2812
L2811:
    cmp     ax, 43
    jne     L2813
L2812:
; case
; RPN'ized expression: "45 "
; Expanded expression: "45 "
; Expression value: 45
    jmp     L2814
L2813:
    cmp     ax, 45
    jne     L2815
L2814:
; return
; RPN'ized expression: "10 "
; Expanded expression: "10 "
; Expression value: 10
; Fused expression:    "10 "
    mov     ax, 10
    jmp     L2802
; case
; RPN'ized expression: "4 "
; Expanded expression: "4 "
; Expression value: 4
    jmp     L2816
L2815:
    cmp     ax, 4
    jne     L2817
L2816:
; case
; RPN'ized expression: "5 "
; Expanded expression: "5 "
; Expression value: 5
    jmp     L2818
L2817:
    cmp     ax, 5
    jne     L2819
L2818:
; return
; RPN'ized expression: "9 "
; Expanded expression: "9 "
; Expression value: 9
; Fused expression:    "9 "
    mov     ax, 9
    jmp     L2802
; case
; RPN'ized expression: "60 "
; Expanded expression: "60 "
; Expression value: 60
    jmp     L2820
L2819:
    cmp     ax, 60
    jne     L2821
L2820:
; case
; RPN'ized expression: "62 "
; Expanded expression: "62 "
; Expression value: 62
    jmp     L2822
L2821:
    cmp     ax, 62
    jne     L2823
L2822:
; case
; RPN'ized expression: "10 "
; Expanded expression: "10 "
; Expression value: 10
    jmp     L2824
L2823:
    cmp     ax, 10
    jne     L2825
L2824:
; case
; RPN'ized expression: "11 "
; Expanded expression: "11 "
; Expression value: 11
    jmp     L2826
L2825:
    cmp     ax, 11
    jne     L2827
L2826:
; return
; RPN'ized expression: "8 "
; Expanded expression: "8 "
; Expression value: 8
; Fused expression:    "8 "
    mov     ax, 8
    jmp     L2802
; case
; RPN'ized expression: "8 "
; Expanded expression: "8 "
; Expression value: 8
    jmp     L2828
L2827:
    cmp     ax, 8
    jne     L2829
L2828:
; case
; RPN'ized expression: "9 "
; Expanded expression: "9 "
; Expression value: 9
    jmp     L2830
L2829:
    cmp     ax, 9
    jne     L2831
L2830:
; return
; RPN'ized expression: "7 "
; Expanded expression: "7 "
; Expression value: 7
; Fused expression:    "7 "
    mov     ax, 7
    jmp     L2802
; case
; RPN'ized expression: "38 "
; Expanded expression: "38 "
; Expression value: 38
    jmp     L2832
L2831:
    cmp     ax, 38
    jne     L2833
L2832:
; return
; RPN'ized expression: "6 "
; Expanded expression: "6 "
; Expression value: 6
; Fused expression:    "6 "
    mov     ax, 6
    jmp     L2802
; case
; RPN'ized expression: "94 "
; Expanded expression: "94 "
; Expression value: 94
    jmp     L2834
L2833:
    cmp     ax, 94
    jne     L2835
L2834:
; return
; RPN'ized expression: "5 "
; Expanded expression: "5 "
; Expression value: 5
; Fused expression:    "5 "
    mov     ax, 5
    jmp     L2802
; case
; RPN'ized expression: "124 "
; Expanded expression: "124 "
; Expression value: 124
    jmp     L2836
L2835:
    cmp     ax, 124
    jne     L2837
L2836:
; return
; RPN'ized expression: "4 "
; Expanded expression: "4 "
; Expression value: 4
; Fused expression:    "4 "
    mov     ax, 4
    jmp     L2802
; case
; RPN'ized expression: "6 "
; Expanded expression: "6 "
; Expression value: 6
    jmp     L2838
L2837:
    cmp     ax, 6
    jne     L2839
L2838:
; return
; RPN'ized expression: "3 "
; Expanded expression: "3 "
; Expression value: 3
; Fused expression:    "3 "
    mov     ax, 3
    jmp     L2802
; case
; RPN'ized expression: "7 "
; Expanded expression: "7 "
; Expression value: 7
    jmp     L2840
L2839:
    cmp     ax, 7
    jne     L2841
L2840:
; return
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
; Fused expression:    "2 "
    mov     ax, 2
    jmp     L2802
; case
; RPN'ized expression: "61 "
; Expanded expression: "61 "
; Expression value: 61
    jmp     L2842
L2841:
    cmp     ax, 61
    jne     L2843
L2842:
; case
; RPN'ized expression: "65 "
; Expanded expression: "65 "
; Expression value: 65
    jmp     L2844
L2843:
    cmp     ax, 65
    jne     L2845
L2844:
; case
; RPN'ized expression: "66 "
; Expanded expression: "66 "
; Expression value: 66
    jmp     L2846
L2845:
    cmp     ax, 66
    jne     L2847
L2846:
; case
; RPN'ized expression: "67 "
; Expanded expression: "67 "
; Expression value: 67
    jmp     L2848
L2847:
    cmp     ax, 67
    jne     L2849
L2848:
; case
; RPN'ized expression: "68 "
; Expanded expression: "68 "
; Expression value: 68
    jmp     L2850
L2849:
    cmp     ax, 68
    jne     L2851
L2850:
; case
; RPN'ized expression: "69 "
; Expanded expression: "69 "
; Expression value: 69
    jmp     L2852
L2851:
    cmp     ax, 69
    jne     L2853
L2852:
; case
; RPN'ized expression: "70 "
; Expanded expression: "70 "
; Expression value: 70
    jmp     L2854
L2853:
    cmp     ax, 70
    jne     L2855
L2854:
; case
; RPN'ized expression: "71 "
; Expanded expression: "71 "
; Expression value: 71
    jmp     L2856
L2855:
    cmp     ax, 71
    jne     L2857
L2856:
; case
; RPN'ized expression: "72 "
; Expanded expression: "72 "
; Expression value: 72
    jmp     L2858
L2857:
    cmp     ax, 72
    jne     L2859
L2858:
; case
; RPN'ized expression: "73 "
; Expanded expression: "73 "
; Expression value: 73
    jmp     L2860
L2859:
    cmp     ax, 73
    jne     L2861
L2860:
; case
; RPN'ized expression: "74 "
; Expanded expression: "74 "
; Expression value: 74
    jmp     L2862
L2861:
    cmp     ax, 74
    jne     L2863
L2862:
; return
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
    mov     ax, 1
    jmp     L2802
; }
    jmp     L2803
L2863:
L2803:
; return
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "0 "
    mov     ax, 0
    jmp     L2802
L2802:
    leave
    ret
; SEGMENT _TEXT
; glb precedGEQ : (
; prm     lfttok : int
; prm     rhttok : int
;     ) int
SEGMENT _TEXT
    global  _precedGEQ
_precedGEQ:
    push    bp
    mov     bp, sp
; loc     lfttok : (@4): int
; loc     rhttok : (@6): int
; switch
; RPN'ized expression: "lfttok "
; Expanded expression: "(@4) *(2) "
; Fused expression:    "*(2) (@4) "
    mov     ax, [bp+4]
    jmp     L2868
; {
; case
; RPN'ized expression: "61 "
; Expanded expression: "61 "
; Expression value: 61
    jmp     L2869
L2868:
    cmp     ax, 61
    jne     L2870
L2869:
; case
; RPN'ized expression: "65 "
; Expanded expression: "65 "
; Expression value: 65
    jmp     L2871
L2870:
    cmp     ax, 65
    jne     L2872
L2871:
; case
; RPN'ized expression: "66 "
; Expanded expression: "66 "
; Expression value: 66
    jmp     L2873
L2872:
    cmp     ax, 66
    jne     L2874
L2873:
; case
; RPN'ized expression: "67 "
; Expanded expression: "67 "
; Expression value: 67
    jmp     L2875
L2874:
    cmp     ax, 67
    jne     L2876
L2875:
; case
; RPN'ized expression: "68 "
; Expanded expression: "68 "
; Expression value: 68
    jmp     L2877
L2876:
    cmp     ax, 68
    jne     L2878
L2877:
; case
; RPN'ized expression: "69 "
; Expanded expression: "69 "
; Expression value: 69
    jmp     L2879
L2878:
    cmp     ax, 69
    jne     L2880
L2879:
; case
; RPN'ized expression: "70 "
; Expanded expression: "70 "
; Expression value: 70
    jmp     L2881
L2880:
    cmp     ax, 70
    jne     L2882
L2881:
; case
; RPN'ized expression: "71 "
; Expanded expression: "71 "
; Expression value: 71
    jmp     L2883
L2882:
    cmp     ax, 71
    jne     L2884
L2883:
; case
; RPN'ized expression: "72 "
; Expanded expression: "72 "
; Expression value: 72
    jmp     L2885
L2884:
    cmp     ax, 72
    jne     L2886
L2885:
; case
; RPN'ized expression: "73 "
; Expanded expression: "73 "
; Expression value: 73
    jmp     L2887
L2886:
    cmp     ax, 73
    jne     L2888
L2887:
; case
; RPN'ized expression: "74 "
; Expanded expression: "74 "
; Expression value: 74
    jmp     L2889
L2888:
    cmp     ax, 74
    jne     L2890
L2889:
; return
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "0 "
    mov     ax, 0
    jmp     L2865
; }
    jmp     L2866
L2890:
L2866:
; return
; RPN'ized expression: "( lfttok preced ) ( rhttok preced ) >= "
; Expanded expression: " (@4) *(2)  preced ()2  (@6) *(2)  preced ()2 >= "
; Fused expression:    "( *(2) (@4) , preced )2 push-ax ( *(2) (@6) , preced )2 >= *sp ax "
    push    word [bp+4]
    call    _preced
    sub     sp, -2
    push    ax
    push    word [bp+6]
    call    _preced
    sub     sp, -2
    mov     cx, ax
    pop     ax
    cmp     ax, cx
    setge   al
    cbw
    jmp     L2865
L2865:
    leave
    ret
; SEGMENT _TEXT
; glb expr : (
; prm     tok : int
; prm     gotUnary : * int
;     ) int
; glb exprUnary : (
; prm     tok : int
; prm     gotUnary : * int
;     ) int
SEGMENT _TEXT
    global  _exprUnary
_exprUnary:
    push    bp
    mov     bp, sp
; loc     tok : (@4): int
; loc     gotUnary : (@6): * int
; loc     decl : (@-2): int
    sub     sp, 2
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "=(34) *(@-2) 0 "
    mov     ax, 0
    mov     [bp-2], ax
; RPN'ized expression: "gotUnary *u 0 = "
; Expanded expression: "(@6) *(2) 0 =(2) "
; Fused expression:    "*(2) (@6) =(34) *ax 0 "
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, 0
    mov     [bx], ax
; if
; RPN'ized expression: "( tok isop ) ( tok isunary ) ( tok , L2895 strchr ) 0 != || && "
; Expanded expression: " (@4) *(2)  isop ()2 _Bool [sh&&->2897]  (@4) *(2)  isunary ()2 _Bool [sh||->2898]  (@4) *(2)  L2895  strchr ()4 0 != _Bool ||[2898] _Bool &&[2897] "
; SEGMENT _TEXT
SEGMENT _DATA
L2895:
    db  "&*+-",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@4) , isop )2 _Bool [sh&&->2897] ( *(2) (@4) , isunary )2 _Bool [sh||->2898] ( *(2) (@4) , L2895 , strchr )4 != ax 0 _Bool ||[2898] _Bool &&[2897] "
    push    word [bp+4]
    call    _isop
    sub     sp, -2
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L2897
    push    word [bp+4]
    call    _isunary
    sub     sp, -2
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L2898
    push    word [bp+4]
    push    L2895
    call    _strchr
    sub     sp, -4
    cmp     ax, 0
    setne   al
    cbw
    test    ax, ax
    setnz   al
    cbw
L2898:
    test    ax, ax
    setnz   al
    cbw
L2897:
; JumpIfZero
    test    ax, ax
    jz      L2893
; {
; loc         lastTok : (@-4): int
    sub     sp, 2
; =
; RPN'ized expression: "tok "
; Expanded expression: "(@4) *(2) "
; Fused expression:    "=(34) *(@-4) *(@4) "
    mov     ax, [bp+4]
    mov     [bp-4], ax
; RPN'ized expression: "tok ( gotUnary , ( GetToken ) exprUnary ) = "
; Expanded expression: "(@4)  (@6) *(2)   GetToken ()0  exprUnary ()4 =(2) "
; Fused expression:    "( *(2) (@6) , ( GetToken )0 , exprUnary )4 =(34) *(@4) ax "
    push    word [bp+6]
    call    _GetToken
    push    ax
    call    _exprUnary
    sub     sp, -4
    mov     [bp+4], ax
; if
; RPN'ized expression: "gotUnary *u 0 == "
; Expanded expression: "(@6) *(2) *(2) 0 == "
; Fused expression:    "*(2) (@6) == *ax 0 IF! "
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 0
    jne     L2899
; RPN'ized expression: "( ( lastTok GetTokenName ) , L2901 error ) "
; Expanded expression: "  (@-4) *(2)  GetTokenName ()2  L2901  error ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2901:
    db  "exprUnary(): primary expression expected after token %s",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( *(2) (@-4) , GetTokenName )2 , L2901 , error )4 "
    push    word [bp-4]
    call    _GetTokenName
    sub     sp, -2
    push    ax
    push    L2901
    call    _error
    sub     sp, -4
L2899:
; switch
; RPN'ized expression: "lastTok "
; Expanded expression: "(@-4) *(2) "
; Fused expression:    "*(2) (@-4) "
    mov     ax, [bp-4]
    jmp     L2905
; {
; case
; RPN'ized expression: "38 "
; Expanded expression: "38 "
; Expression value: 38
    jmp     L2906
L2905:
    cmp     ax, 38
    jne     L2907
L2906:
; RPN'ized expression: "( 77 push ) "
; Expanded expression: " 77  push ()2 "
; Fused expression:    "( 77 , push )2 "
    push    77
    call    _push
    sub     sp, -2
; break
    jmp     L2903
; case
; RPN'ized expression: "42 "
; Expanded expression: "42 "
; Expression value: 42
    jmp     L2908
L2907:
    cmp     ax, 42
    jne     L2909
L2908:
; RPN'ized expression: "( 78 push ) "
; Expanded expression: " 78  push ()2 "
; Fused expression:    "( 78 , push )2 "
    push    78
    call    _push
    sub     sp, -2
; break
    jmp     L2903
; case
; RPN'ized expression: "43 "
; Expanded expression: "43 "
; Expression value: 43
    jmp     L2910
L2909:
    cmp     ax, 43
    jne     L2911
L2910:
; RPN'ized expression: "( 79 push ) "
; Expanded expression: " 79  push ()2 "
; Fused expression:    "( 79 , push )2 "
    push    79
    call    _push
    sub     sp, -2
; break
    jmp     L2903
; case
; RPN'ized expression: "45 "
; Expanded expression: "45 "
; Expression value: 45
    jmp     L2912
L2911:
    cmp     ax, 45
    jne     L2913
L2912:
; RPN'ized expression: "( 80 push ) "
; Expanded expression: " 80  push ()2 "
; Fused expression:    "( 80 , push )2 "
    push    80
    call    _push
    sub     sp, -2
; break
    jmp     L2903
; case
; RPN'ized expression: "33 "
; Expanded expression: "33 "
; Expression value: 33
    jmp     L2914
L2913:
    cmp     ax, 33
    jne     L2915
L2914:
; RPN'ized expression: "( 0 , 1 push2 ) "
; Expanded expression: " 0  1  push2 ()4 "
; Fused expression:    "( 0 , 1 , push2 )4 "
    push    0
    push    1
    call    _push2
    sub     sp, -4
; RPN'ized expression: "( 8 push ) "
; Expanded expression: " 8  push ()2 "
; Fused expression:    "( 8 , push )2 "
    push    8
    call    _push
    sub     sp, -2
; break
    jmp     L2903
; default
L2904:
; RPN'ized expression: "( lastTok push ) "
; Expanded expression: " (@-4) *(2)  push ()2 "
; Fused expression:    "( *(2) (@-4) , push )2 "
    push    word [bp-4]
    call    _push
    sub     sp, -2
; break
    jmp     L2903
; }
    jmp     L2903
L2915:
    jmp     L2904
L2903:
    sub     sp, -2
; }
    jmp     L2894
L2893:
; else
; {
; loc         inspos : (@-4): int
    sub     sp, 2
; =
; RPN'ized expression: "sp "
; Expanded expression: "sp *(2) "
; Fused expression:    "=(34) *(@-4) *sp "
    mov     ax, [_sp]
    mov     [bp-4], ax
; if
; RPN'ized expression: "tok 1 == tok 2 == || "
; Expanded expression: "(@4) *(2) 1 == _Bool [sh||->2919] (@4) *(2) 2 == _Bool ||[2919] "
; Fused expression:    "== *(@4) 1 _Bool [sh||->2919] == *(@4) 2 _Bool ||[2919] "
    mov     ax, [bp+4]
    cmp     ax, 1
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L2919
    mov     ax, [bp+4]
    cmp     ax, 2
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L2919:
; JumpIfZero
    test    ax, ax
    jz      L2917
; {
; RPN'ized expression: "( ( GetTokenValueInt ) , tok push2 ) "
; Expanded expression: "  GetTokenValueInt ()0  (@4) *(2)  push2 ()4 "
; Fused expression:    "( ( GetTokenValueInt )0 , *(2) (@4) , push2 )4 "
    call    _GetTokenValueInt
    push    ax
    push    word [bp+4]
    call    _push2
    sub     sp, -4
; RPN'ized expression: "gotUnary *u 1 = "
; Expanded expression: "(@6) *(2) 1 =(2) "
; Fused expression:    "*(2) (@6) =(34) *ax 1 "
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, 1
    mov     [bx], ax
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
; }
    jmp     L2918
L2917:
; else
; if
; RPN'ized expression: "tok 3 == "
; Expanded expression: "(@4) *(2) 3 == "
; Fused expression:    "== *(@4) 3 IF! "
    mov     ax, [bp+4]
    cmp     ax, 3
    jne     L2920
; {
; loc             lbl : (@-6): int
    sub     sp, 2
; =
; RPN'ized expression: "LabelCnt 2 += 2 - "
; Expanded expression: "LabelCnt 2 +=(2) 2 - "
; Fused expression:    "+=(34) *LabelCnt 2 - ax 2 =(34) *(@-6) ax "
    mov     ax, [_LabelCnt]
    add     ax, 2
    mov     [_LabelCnt], ax
    sub     ax, 2
    mov     [bp-6], ax
; loc             len : (@-8): int
    sub     sp, 2
; loc             i : (@-10): int
    sub     sp, 2
; loc             id : (@-12): int
    sub     sp, 2
; RPN'ized expression: "1 2 8 lbl sizeof * + 3 / + "
; Expanded expression: "7 "
; Expression value: 7
; loc             s : (@-20): [7] char
    sub     sp, 8
; loc             p : (@-22): * char
    sub     sp, 2
; =
; RPN'ized expression: "s s sizeof + "
; Expanded expression: "(@-20) 7 + "
; Fused expression:    "+ (@-20) 7 =(34) *(@-22) ax "
    lea     ax, [bp-20]
    add     ax, 7
    mov     [bp-22], ax
; RPN'ized expression: "( len 1 ( GetTokenValueStringLength ) + = , ( GetTokenValueString ) , lbl AddString ) "
; Expanded expression: " (@-8) 1  GetTokenValueStringLength ()0 + =(2)   GetTokenValueString ()0  (@-6) *(2)  AddString ()6 "
; Fused expression:    "( ( GetTokenValueStringLength )0 + 1 ax =(34) *(@-8) ax , ( GetTokenValueString )0 , *(2) (@-6) , AddString )6 "
    call    _GetTokenValueStringLength
    mov     cx, ax
    mov     ax, 1
    add     ax, cx
    mov     [bp-8], ax
    push    ax
    call    _GetTokenValueString
    push    ax
    push    word [bp-6]
    call    _AddString
    sub     sp, -6
; RPN'ized expression: "p -- *u 0 = "
; Expanded expression: "(@-22) --(2) 0 =(1) "
; Fused expression:    "--(2) *(@-22) =(18) *ax 0 "
    dec     word [bp-22]
    mov     ax, [bp-22]
    mov     bx, ax
    mov     ax, 0
    mov     [bx], al
    cbw
; RPN'ized expression: "i lbl = "
; Expanded expression: "(@-10) (@-6) *(2) =(2) "
; Fused expression:    "=(34) *(@-10) *(@-6) "
    mov     ax, [bp-6]
    mov     [bp-10], ax
; do
L2922:
; {
; RPN'ized expression: "p -- *u 48 i 10 % + = "
; Expanded expression: "(@-22) --(2) 48 (@-10) *(2) 10 % + =(1) "
; Fused expression:    "--(2) *(@-22) push-ax % *(@-10) 10 + 48 ax =(18) **sp ax "
    dec     word [bp-22]
    mov     ax, [bp-22]
    push    ax
    mov     ax, [bp-10]
    cwd
    mov     cx, 10
    idiv    cx
    mov     ax, dx
    mov     cx, ax
    mov     ax, 48
    add     ax, cx
    pop     bx
    mov     [bx], al
    cbw
; RPN'ized expression: "i 10 /= "
; Expanded expression: "(@-10) 10 /=(2) "
; Fused expression:    "/=(34) *(@-10) 10 "
    mov     ax, [bp-10]
    cwd
    mov     cx, 10
    idiv    cx
    mov     [bp-10], ax
; }
; while
; RPN'ized expression: "i "
; Expanded expression: "(@-10) *(2) "
L2923:
; Fused expression:    "*(2) (@-10) "
    mov     ax, [bp-10]
; JumpIfNotZero
    test    ax, ax
    jnz     L2922
L2924:
; RPN'ized expression: "( id ( p AddIdent ) = , 16 PushSyntax2 ) "
; Expanded expression: " (@-12)  (@-22) *(2)  AddIdent ()2 =(2)  16  PushSyntax2 ()4 "
; Fused expression:    "( ( *(2) (@-22) , AddIdent )2 =(34) *(@-12) ax , 16 , PushSyntax2 )4 "
    push    word [bp-22]
    call    _AddIdent
    sub     sp, -2
    mov     [bp-12], ax
    push    ax
    push    16
    call    _PushSyntax2
    sub     sp, -4
; RPN'ized expression: "( 91 PushSyntax ) "
; Expanded expression: " 91  PushSyntax ()2 "
; Fused expression:    "( 91 , PushSyntax )2 "
    push    91
    call    _PushSyntax
    sub     sp, -2
; RPN'ized expression: "( len , 1 PushSyntax2 ) "
; Expanded expression: " (@-8) *(2)  1  PushSyntax2 ()4 "
; Fused expression:    "( *(2) (@-8) , 1 , PushSyntax2 )4 "
    push    word [bp-8]
    push    1
    call    _PushSyntax2
    sub     sp, -4
; RPN'ized expression: "( 93 PushSyntax ) "
; Expanded expression: " 93  PushSyntax ()2 "
; Fused expression:    "( 93 , PushSyntax )2 "
    push    93
    call    _PushSyntax
    sub     sp, -2
; RPN'ized expression: "( 18 PushSyntax ) "
; Expanded expression: " 18  PushSyntax ()2 "
; Fused expression:    "( 18 , PushSyntax )2 "
    push    18
    call    _PushSyntax
    sub     sp, -2
; RPN'ized expression: "( id , 16 push2 ) "
; Expanded expression: " (@-12) *(2)  16  push2 ()4 "
; Fused expression:    "( *(2) (@-12) , 16 , push2 )4 "
    push    word [bp-12]
    push    16
    call    _push2
    sub     sp, -4
; RPN'ized expression: "gotUnary *u 1 = "
; Expanded expression: "(@6) *(2) 1 =(2) "
; Fused expression:    "*(2) (@6) =(34) *ax 1 "
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, 1
    mov     [bx], ax
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
    sub     sp, -18
; }
    jmp     L2921
L2920:
; else
; if
; RPN'ized expression: "( 0 , tok TokenStartsDeclaration ) "
; Expanded expression: " 0  (@4) *(2)  TokenStartsDeclaration ()4 "
; Fused expression:    "( 0 , *(2) (@4) , TokenStartsDeclaration )4 "
    push    0
    push    word [bp+4]
    call    _TokenStartsDeclaration
    sub     sp, -4
; JumpIfZero
    test    ax, ax
    jz      L2925
; {
; loc             synPtr : (@-6): int
    sub     sp, 2
; RPN'ized expression: "tok ( tok ParseDecl ) = "
; Expanded expression: "(@4)  (@4) *(2)  ParseDecl ()2 =(2) "
; Fused expression:    "( *(2) (@4) , ParseDecl )2 =(34) *(@4) ax "
    push    word [bp+4]
    call    _ParseDecl
    sub     sp, -2
    mov     [bp+4], ax
; if
; RPN'ized expression: "tok 41 != "
; Expanded expression: "(@4) *(2) 41 != "
; Fused expression:    "!= *(@4) 41 IF! "
    mov     ax, [bp+4]
    cmp     ax, 41
    je      L2927
; RPN'ized expression: "( ( tok GetTokenName ) , L2929 error ) "
; Expanded expression: "  (@4) *(2)  GetTokenName ()2  L2929  error ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2929:
    db  "exprUnary(): ')' expected, unexpected token %s",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( *(2) (@4) , GetTokenName )2 , L2929 , error )4 "
    push    word [bp+4]
    call    _GetTokenName
    sub     sp, -2
    push    ax
    push    L2929
    call    _error
    sub     sp, -4
L2927:
; RPN'ized expression: "synPtr ( L2931 FindSymbol ) = "
; Expanded expression: "(@-6)  L2931  FindSymbol ()2 =(2) "
; SEGMENT _TEXT
SEGMENT _DATA
L2931:
    db  "<something>",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2931 , FindSymbol )2 =(34) *(@-6) ax "
    push    L2931
    call    _FindSymbol
    sub     sp, -2
    mov     [bp-6], ax
; RPN'ized expression: "( SyntaxStack synPtr + *u 1 + *u , 16 push2 ) "
; Expanded expression: " SyntaxStack (@-6) *(2) 4 * + 2 + *(2)  16  push2 ()4 "
; Fused expression:    "( * *(@-6) 4 + SyntaxStack ax + ax 2 *(2) ax , 16 , push2 )4 "
    mov     ax, [bp-6]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    16
    call    _push2
    sub     sp, -4
; RPN'ized expression: "decl gotUnary *u 1 = = "
; Expanded expression: "(@-2) (@6) *(2) 1 =(2) =(2) "
; Fused expression:    "*(2) (@6) =(34) *ax 1 =(34) *(@-2) ax "
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, 1
    mov     [bx], ax
    mov     [bp-2], ax
    sub     sp, -2
; }
    jmp     L2926
L2925:
; else
; if
; RPN'ized expression: "tok 16 == "
; Expanded expression: "(@4) *(2) 16 == "
; Fused expression:    "== *(@4) 16 IF! "
    mov     ax, [bp+4]
    cmp     ax, 16
    jne     L2933
; {
; loc             synPtr : (@-6): int
    sub     sp, 2
; =
; RPN'ized expression: "( ( GetTokenIdentName ) FindSymbol ) "
; Expanded expression: "  GetTokenIdentName ()0  FindSymbol ()2 "
; Fused expression:    "( ( GetTokenIdentName )0 , FindSymbol )2 =(34) *(@-6) ax "
    call    _GetTokenIdentName
    push    ax
    call    _FindSymbol
    sub     sp, -2
    mov     [bp-6], ax
; if
; RPN'ized expression: "synPtr 0 < "
; Expanded expression: "(@-6) *(2) 0 < "
; Fused expression:    "< *(@-6) 0 IF! "
    mov     ax, [bp-6]
    cmp     ax, 0
    jge     L2935
; RPN'ized expression: "( ( GetTokenIdentName ) , L2937 error ) "
; Expanded expression: "  GetTokenIdentName ()0  L2937  error ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2937:
    db  "exprUnary(): undefined identifier '%s'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( GetTokenIdentName )0 , L2937 , error )4 "
    call    _GetTokenIdentName
    push    ax
    push    L2937
    call    _error
    sub     sp, -4
L2935:
; RPN'ized expression: "( SyntaxStack synPtr + *u 1 + *u , tok push2 ) "
; Expanded expression: " SyntaxStack (@-6) *(2) 4 * + 2 + *(2)  (@4) *(2)  push2 ()4 "
; Fused expression:    "( * *(@-6) 4 + SyntaxStack ax + ax 2 *(2) ax , *(2) (@4) , push2 )4 "
    mov     ax, [bp-6]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    word [bp+4]
    call    _push2
    sub     sp, -4
; RPN'ized expression: "gotUnary *u 1 = "
; Expanded expression: "(@6) *(2) 1 =(2) "
; Fused expression:    "*(2) (@6) =(34) *ax 1 "
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, 1
    mov     [bx], ax
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
    sub     sp, -2
; }
    jmp     L2934
L2933:
; else
; if
; RPN'ized expression: "tok 40 == "
; Expanded expression: "(@4) *(2) 40 == "
; Fused expression:    "== *(@4) 40 IF! "
    mov     ax, [bp+4]
    cmp     ax, 40
    jne     L2939
; {
; RPN'ized expression: "tok ( gotUnary , ( GetToken ) expr ) = "
; Expanded expression: "(@4)  (@6) *(2)   GetToken ()0  expr ()4 =(2) "
; Fused expression:    "( *(2) (@6) , ( GetToken )0 , expr )4 =(34) *(@4) ax "
    push    word [bp+6]
    call    _GetToken
    push    ax
    call    _expr
    sub     sp, -4
    mov     [bp+4], ax
; if
; RPN'ized expression: "tok 41 != "
; Expanded expression: "(@4) *(2) 41 != "
; Fused expression:    "!= *(@4) 41 IF! "
    mov     ax, [bp+4]
    cmp     ax, 41
    je      L2941
; RPN'ized expression: "( ( tok GetTokenName ) , L2943 error ) "
; Expanded expression: "  (@4) *(2)  GetTokenName ()2  L2943  error ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2943:
    db  "exprUnary(): ')' expected, unexpected token %s",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( *(2) (@4) , GetTokenName )2 , L2943 , error )4 "
    push    word [bp+4]
    call    _GetTokenName
    sub     sp, -2
    push    ax
    push    L2943
    call    _error
    sub     sp, -4
L2941:
; if
; RPN'ized expression: "gotUnary *u 0 == "
; Expanded expression: "(@6) *(2) *(2) 0 == "
; Fused expression:    "*(2) (@6) == *ax 0 IF! "
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 0
    jne     L2945
; RPN'ized expression: "( L2947 error ) "
; Expanded expression: " L2947  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2947:
    db  "exprUnary(): primary expression expected in '()'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2947 , error )2 "
    push    L2947
    call    _error
    sub     sp, -2
L2945:
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
; }
L2939:
L2934:
L2926:
L2921:
L2918:
; while
; RPN'ized expression: "gotUnary *u decl 0 == && "
; Expanded expression: "(@6) *(2) *(2) _Bool [sh&&->2951] (@-2) *(2) 0 == _Bool &&[2951] "
L2949:
; Fused expression:    "*(2) (@6) *(2) ax _Bool [sh&&->2951] == *(@-2) 0 _Bool &&[2951] "
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, [bx]
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L2951
    mov     ax, [bp-2]
    cmp     ax, 0
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L2951:
; JumpIfZero
    test    ax, ax
    jz      L2950
; {
; while
; RPN'ized expression: "tok 40 == tok 91 == || "
; Expanded expression: "(@4) *(2) 40 == _Bool [sh||->2954] (@4) *(2) 91 == _Bool ||[2954] "
L2952:
; Fused expression:    "== *(@4) 40 _Bool [sh||->2954] == *(@4) 91 _Bool ||[2954] "
    mov     ax, [bp+4]
    cmp     ax, 40
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L2954
    mov     ax, [bp+4]
    cmp     ax, 91
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L2954:
; JumpIfZero
    test    ax, ax
    jz      L2953
; {
; loc                 brak : (@-6): int
    sub     sp, 2
; =
; RPN'ized expression: "tok "
; Expanded expression: "(@4) *(2) "
; Fused expression:    "=(34) *(@-6) *(@4) "
    mov     ax, [bp+4]
    mov     [bp-6], ax
; if
; RPN'ized expression: "brak 40 == "
; Expanded expression: "(@-6) *(2) 40 == "
; Fused expression:    "== *(@-6) 40 IF! "
    mov     ax, [bp-6]
    cmp     ax, 40
    jne     L2955
; {
; loc                     acnt : (@-8): int
    sub     sp, 2
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "=(34) *(@-8) 0 "
    mov     ax, 0
    mov     [bp-8], ax
; RPN'ized expression: "( 40 , inspos ins ) "
; Expanded expression: " 40  (@-4) *(2)  ins ()4 "
; Fused expression:    "( 40 , *(2) (@-4) , ins )4 "
    push    40
    push    word [bp-4]
    call    _ins
    sub     sp, -4
; for
L2957:
    jmp     L2959
L2958:
    jmp     L2957
L2959:
; {
; loc                         pos2 : (@-10): int
    sub     sp, 2
; =
; RPN'ized expression: "sp "
; Expanded expression: "sp *(2) "
; Fused expression:    "=(34) *(@-10) *sp "
    mov     ax, [_sp]
    mov     [bp-10], ax
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
; RPN'ized expression: "tok ( gotUnary , tok expr ) = "
; Expanded expression: "(@4)  (@6) *(2)  (@4) *(2)  expr ()4 =(2) "
; Fused expression:    "( *(2) (@6) , *(2) (@4) , expr )4 =(34) *(@4) ax "
    push    word [bp+6]
    push    word [bp+4]
    call    _expr
    sub     sp, -4
    mov     [bp+4], ax
; while
; RPN'ized expression: "pos2 sp < "
; Expanded expression: "(@-10) *(2) sp *(2) < "
L2961:
; Fused expression:    "< *(@-10) *sp IF! "
    mov     ax, [bp-10]
    cmp     ax, [_sp]
    jge     L2962
; {
; loc                             v : (@-12): int
    sub     sp, 2
; loc                             v2 : (@-14): int
    sub     sp, 2
; RPN'ized expression: "v ( v2 &u pop2 ) = "
; Expanded expression: "(@-12)  (@-14)  pop2 ()2 =(2) "
; Fused expression:    "( (@-14) , pop2 )2 =(34) *(@-12) ax "
    lea     ax, [bp-14]
    push    ax
    call    _pop2
    sub     sp, -2
    mov     [bp-12], ax
; RPN'ized expression: "( v2 , v , inspos 1 + ins2 ) "
; Expanded expression: " (@-14) *(2)  (@-12) *(2)  (@-4) *(2) 1 +  ins2 ()6 "
; Fused expression:    "( *(2) (@-14) , *(2) (@-12) , + *(@-4) 1 , ins2 )6 "
    push    word [bp-14]
    push    word [bp-12]
    mov     ax, [bp-4]
    add     ax, 1
    push    ax
    call    _ins2
    sub     sp, -6
; RPN'ized expression: "pos2 ++p "
; Expanded expression: "(@-10) ++p(2) "
; Fused expression:    "++p(2) *(@-10) "
    mov     ax, [bp-10]
    inc     word [bp-10]
    sub     sp, -4
; }
    jmp     L2961
L2962:
; if
; RPN'ized expression: "tok 44 == "
; Expanded expression: "(@4) *(2) 44 == "
; Fused expression:    "== *(@4) 44 IF! "
    mov     ax, [bp+4]
    cmp     ax, 44
    jne     L2963
; {
; if
; RPN'ized expression: "gotUnary *u 0 == "
; Expanded expression: "(@6) *(2) *(2) 0 == "
; Fused expression:    "*(2) (@6) == *ax 0 IF! "
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 0
    jne     L2965
; RPN'ized expression: "( L2967 error ) "
; Expanded expression: " L2967  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2967:
    db  "exprUnary(): primary expression (fxn argument) expected before ','",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2967 , error )2 "
    push    L2967
    call    _error
    sub     sp, -2
L2965:
; RPN'ized expression: "acnt ++p "
; Expanded expression: "(@-8) ++p(2) "
; Fused expression:    "++p(2) *(@-8) "
    mov     ax, [bp-8]
    inc     word [bp-8]
; RPN'ized expression: "( 44 , inspos 1 + ins ) "
; Expanded expression: " 44  (@-4) *(2) 1 +  ins ()4 "
; Fused expression:    "( 44 , + *(@-4) 1 , ins )4 "
    push    44
    mov     ax, [bp-4]
    add     ax, 1
    push    ax
    call    _ins
    sub     sp, -4
; continue
    sub     sp, -2
    jmp     L2958
; }
L2963:
; if
; RPN'ized expression: "tok 41 == "
; Expanded expression: "(@4) *(2) 41 == "
; Fused expression:    "== *(@4) 41 IF! "
    mov     ax, [bp+4]
    cmp     ax, 41
    jne     L2969
; {
; if
; RPN'ized expression: "acnt gotUnary *u 0 == && "
; Expanded expression: "(@-8) *(2) _Bool [sh&&->2973] (@6) *(2) *(2) 0 == _Bool &&[2973] "
; Fused expression:    "*(2) (@-8) _Bool [sh&&->2973] *(2) (@6) == *ax 0 _Bool &&[2973] "
    mov     ax, [bp-8]
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L2973
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 0
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L2973:
; JumpIfZero
    test    ax, ax
    jz      L2971
; RPN'ized expression: "( L2974 error ) "
; Expanded expression: " L2974  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2974:
    db  "exprUnary(): primary expression (fxn argument) expected between ',' and ')'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2974 , error )2 "
    push    L2974
    call    _error
    sub     sp, -2
L2971:
; RPN'ized expression: "gotUnary *u 1 = "
; Expanded expression: "(@6) *(2) 1 =(2) "
; Fused expression:    "*(2) (@6) =(34) *ax 1 "
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, 1
    mov     [bx], ax
; break
    sub     sp, -2
    jmp     L2960
; }
L2969:
; RPN'ized expression: "( ( tok GetTokenName ) , L2976 error ) "
; Expanded expression: "  (@4) *(2)  GetTokenName ()2  L2976  error ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2976:
    db  "exprUnary(): ',' or ')' expected, unexpected token %s",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( *(2) (@4) , GetTokenName )2 , L2976 , error )4 "
    push    word [bp+4]
    call    _GetTokenName
    sub     sp, -2
    push    ax
    push    L2976
    call    _error
    sub     sp, -4
    sub     sp, -2
; }
    jmp     L2958
L2960:
    sub     sp, -2
; }
    jmp     L2956
L2955:
; else
; {
; for
L2978:
    jmp     L2980
L2979:
    jmp     L2978
L2980:
; {
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
; RPN'ized expression: "tok ( gotUnary , tok expr ) = "
; Expanded expression: "(@4)  (@6) *(2)  (@4) *(2)  expr ()4 =(2) "
; Fused expression:    "( *(2) (@6) , *(2) (@4) , expr )4 =(34) *(@4) ax "
    push    word [bp+6]
    push    word [bp+4]
    call    _expr
    sub     sp, -4
    mov     [bp+4], ax
; if
; RPN'ized expression: "gotUnary *u 0 == "
; Expanded expression: "(@6) *(2) *(2) 0 == "
; Fused expression:    "*(2) (@6) == *ax 0 IF! "
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 0
    jne     L2982
; RPN'ized expression: "( L2984 error ) "
; Expanded expression: " L2984  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L2984:
    db  "exprUnary(): primary expression expected in '[]'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L2984 , error )2 "
    push    L2984
    call    _error
    sub     sp, -2
L2982:
; if
; RPN'ized expression: "tok 93 == "
; Expanded expression: "(@4) *(2) 93 == "
; Fused expression:    "== *(@4) 93 IF! "
    mov     ax, [bp+4]
    cmp     ax, 93
    jne     L2986
; break
    jmp     L2981
L2986:
; RPN'ized expression: "( ( tok GetTokenName ) , L2988 error ) "
; Expanded expression: "  (@4) *(2)  GetTokenName ()2  L2988  error ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L2988:
    db  "exprUnary(): ']' expected, unexpected token %s",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( *(2) (@4) , GetTokenName )2 , L2988 , error )4 "
    push    word [bp+4]
    call    _GetTokenName
    sub     sp, -2
    push    ax
    push    L2988
    call    _error
    sub     sp, -4
; }
    jmp     L2979
L2981:
; }
L2956:
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
; if
; RPN'ized expression: "brak 40 == "
; Expanded expression: "(@-6) *(2) 40 == "
; Fused expression:    "== *(@-6) 40 IF! "
    mov     ax, [bp-6]
    cmp     ax, 40
    jne     L2990
; RPN'ized expression: "( 41 push ) "
; Expanded expression: " 41  push ()2 "
; Fused expression:    "( 41 , push )2 "
    push    41
    call    _push
    sub     sp, -2
    jmp     L2991
L2990:
; else
; {
; RPN'ized expression: "( 43 push ) "
; Expanded expression: " 43  push ()2 "
; Fused expression:    "( 43 , push )2 "
    push    43
    call    _push
    sub     sp, -2
; RPN'ized expression: "( 78 push ) "
; Expanded expression: " 78  push ()2 "
; Fused expression:    "( 78 , push )2 "
    push    78
    call    _push
    sub     sp, -2
; }
L2991:
    sub     sp, -2
; }
    jmp     L2952
L2953:
; if
; RPN'ized expression: "tok 12 == tok 13 == || "
; Expanded expression: "(@4) *(2) 12 == _Bool [sh||->2994] (@4) *(2) 13 == _Bool ||[2994] "
; Fused expression:    "== *(@4) 12 _Bool [sh||->2994] == *(@4) 13 _Bool ||[2994] "
    mov     ax, [bp+4]
    cmp     ax, 12
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L2994
    mov     ax, [bp+4]
    cmp     ax, 13
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L2994:
; JumpIfZero
    test    ax, ax
    jz      L2992
; {
; if
; RPN'ized expression: "tok 12 == "
; Expanded expression: "(@4) *(2) 12 == "
; Fused expression:    "== *(@4) 12 IF! "
    mov     ax, [bp+4]
    cmp     ax, 12
    jne     L2995
; RPN'ized expression: "( 81 push ) "
; Expanded expression: " 81  push ()2 "
; Fused expression:    "( 81 , push )2 "
    push    81
    call    _push
    sub     sp, -2
    jmp     L2996
L2995:
; else
; RPN'ized expression: "( 82 push ) "
; Expanded expression: " 82  push ()2 "
; Fused expression:    "( 82 , push )2 "
    push    82
    call    _push
    sub     sp, -2
L2996:
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
; }
    jmp     L2993
L2992:
; else
; {
; break
    jmp     L2950
; }
L2993:
; }
    jmp     L2949
L2950:
    sub     sp, -2
; }
L2894:
; return
; RPN'ized expression: "tok "
; Expanded expression: "(@4) *(2) "
; Fused expression:    "*(2) (@4) "
    mov     ax, [bp+4]
    jmp     L2892
L2892:
    leave
    ret
; SEGMENT _TEXT
; glb expr : (
; prm     tok : int
; prm     gotUnary : * int
;     ) int
SEGMENT _TEXT
    global  _expr
_expr:
    push    bp
    mov     bp, sp
; loc     tok : (@4): int
; loc     gotUnary : (@6): * int
; RPN'ized expression: "gotUnary *u 0 = "
; Expanded expression: "(@6) *(2) 0 =(2) "
; Fused expression:    "*(2) (@6) =(34) *ax 0 "
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, 0
    mov     [bx], ax
; RPN'ized expression: "( 0 pushop ) "
; Expanded expression: " 0  pushop ()2 "
; Fused expression:    "( 0 , pushop )2 "
    push    0
    call    _pushop
    sub     sp, -2
; RPN'ized expression: "tok ( gotUnary , tok exprUnary ) = "
; Expanded expression: "(@4)  (@6) *(2)  (@4) *(2)  exprUnary ()4 =(2) "
; Fused expression:    "( *(2) (@6) , *(2) (@4) , exprUnary )4 =(34) *(@4) ax "
    push    word [bp+6]
    push    word [bp+4]
    call    _exprUnary
    sub     sp, -4
    mov     [bp+4], ax
; while
; RPN'ized expression: "tok 0 != ( tok , L3000 strchr ) 0 == && gotUnary *u && "
; Expanded expression: "(@4) *(2) 0 != _Bool [sh&&->3003]  (@4) *(2)  L3000  strchr ()4 0 == _Bool &&[3003] _Bool [sh&&->3002] (@6) *(2) *(2) _Bool &&[3002] "
L2998:
; SEGMENT _TEXT
SEGMENT _DATA
L3000:
    db  ",;:)]",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "!= *(@4) 0 _Bool [sh&&->3003] ( *(2) (@4) , L3000 , strchr )4 == ax 0 _Bool &&[3003] _Bool [sh&&->3002] *(2) (@6) *(2) ax _Bool &&[3002] "
    mov     ax, [bp+4]
    cmp     ax, 0
    setne   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3003
    push    word [bp+4]
    push    L3000
    call    _strchr
    sub     sp, -4
    cmp     ax, 0
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3003:
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3002
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, [bx]
    test    ax, ax
    setnz   al
    cbw
L3002:
; JumpIfZero
    test    ax, ax
    jz      L2999
; {
; if
; RPN'ized expression: "( tok isop ) ( tok isunary ) 0 == && "
; Expanded expression: " (@4) *(2)  isop ()2 _Bool [sh&&->3006]  (@4) *(2)  isunary ()2 0 == _Bool &&[3006] "
; Fused expression:    "( *(2) (@4) , isop )2 _Bool [sh&&->3006] ( *(2) (@4) , isunary )2 == ax 0 _Bool &&[3006] "
    push    word [bp+4]
    call    _isop
    sub     sp, -2
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3006
    push    word [bp+4]
    call    _isunary
    sub     sp, -2
    cmp     ax, 0
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3006:
; JumpIfZero
    test    ax, ax
    jz      L3004
; {
; loc             lastTok : (@-2): int
    sub     sp, 2
; =
; RPN'ized expression: "tok "
; Expanded expression: "(@4) *(2) "
; Fused expression:    "=(34) *(@-2) *(@4) "
    mov     ax, [bp+4]
    mov     [bp-2], ax
; while
; RPN'ized expression: "( tok , ( opstacktop ) precedGEQ ) "
; Expanded expression: " (@4) *(2)   opstacktop ()0  precedGEQ ()4 "
L3007:
; Fused expression:    "( *(2) (@4) , ( opstacktop )0 , precedGEQ )4 "
    push    word [bp+4]
    call    _opstacktop
    push    ax
    call    _precedGEQ
    sub     sp, -4
; JumpIfZero
    test    ax, ax
    jz      L3008
; {
; loc                 v : (@-4): int
    sub     sp, 2
; loc                 v2 : (@-6): int
    sub     sp, 2
; RPN'ized expression: "v ( v2 &u popop2 ) = "
; Expanded expression: "(@-4)  (@-6)  popop2 ()2 =(2) "
; Fused expression:    "( (@-6) , popop2 )2 =(34) *(@-4) ax "
    lea     ax, [bp-6]
    push    ax
    call    _popop2
    sub     sp, -2
    mov     [bp-4], ax
; RPN'ized expression: "( v2 , v push2 ) "
; Expanded expression: " (@-6) *(2)  (@-4) *(2)  push2 ()4 "
; Fused expression:    "( *(2) (@-6) , *(2) (@-4) , push2 )4 "
    push    word [bp-6]
    push    word [bp-4]
    call    _push2
    sub     sp, -4
    sub     sp, -4
; }
    jmp     L3007
L3008:
; RPN'ized expression: "( tok pushop ) "
; Expanded expression: " (@4) *(2)  pushop ()2 "
; Fused expression:    "( *(2) (@4) , pushop )2 "
    push    word [bp+4]
    call    _pushop
    sub     sp, -2
; RPN'ized expression: "tok ( gotUnary , ( GetToken ) exprUnary ) = "
; Expanded expression: "(@4)  (@6) *(2)   GetToken ()0  exprUnary ()4 =(2) "
; Fused expression:    "( *(2) (@6) , ( GetToken )0 , exprUnary )4 =(34) *(@4) ax "
    push    word [bp+6]
    call    _GetToken
    push    ax
    call    _exprUnary
    sub     sp, -4
    mov     [bp+4], ax
; if
; RPN'ized expression: "gotUnary *u 0 == "
; Expanded expression: "(@6) *(2) *(2) 0 == "
; Fused expression:    "*(2) (@6) == *ax 0 IF! "
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 0
    jne     L3009
; RPN'ized expression: "( ( lastTok GetTokenName ) , L3011 error ) "
; Expanded expression: "  (@-2) *(2)  GetTokenName ()2  L3011  error ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3011:
    db  "expr(): primary expression expected after token %s",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( *(2) (@-2) , GetTokenName )2 , L3011 , error )4 "
    push    word [bp-2]
    call    _GetTokenName
    sub     sp, -2
    push    ax
    push    L3011
    call    _error
    sub     sp, -4
L3009:
; continue
    sub     sp, -2
    jmp     L2998
    sub     sp, -2
; }
L3004:
; RPN'ized expression: "( ( tok GetTokenName ) , L3013 error ) "
; Expanded expression: "  (@4) *(2)  GetTokenName ()2  L3013  error ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3013:
    db  "expr(): Unexpected token %s",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( *(2) (@4) , GetTokenName )2 , L3013 , error )4 "
    push    word [bp+4]
    call    _GetTokenName
    sub     sp, -2
    push    ax
    push    L3013
    call    _error
    sub     sp, -4
; }
    jmp     L2998
L2999:
; while
; RPN'ized expression: "( opstacktop ) 0 != "
; Expanded expression: " opstacktop ()0 0 != "
L3015:
; Fused expression:    "( opstacktop )0 != ax 0 IF! "
    call    _opstacktop
    cmp     ax, 0
    je      L3016
; {
; loc         v : (@-2): int
    sub     sp, 2
; loc         v2 : (@-4): int
    sub     sp, 2
; RPN'ized expression: "v ( v2 &u popop2 ) = "
; Expanded expression: "(@-2)  (@-4)  popop2 ()2 =(2) "
; Fused expression:    "( (@-4) , popop2 )2 =(34) *(@-2) ax "
    lea     ax, [bp-4]
    push    ax
    call    _popop2
    sub     sp, -2
    mov     [bp-2], ax
; RPN'ized expression: "( v2 , v push2 ) "
; Expanded expression: " (@-4) *(2)  (@-2) *(2)  push2 ()4 "
; Fused expression:    "( *(2) (@-4) , *(2) (@-2) , push2 )4 "
    push    word [bp-4]
    push    word [bp-2]
    call    _push2
    sub     sp, -4
    sub     sp, -4
; }
    jmp     L3015
L3016:
; RPN'ized expression: "( popop ) "
; Expanded expression: " popop ()0 "
; Fused expression:    "( popop )0 "
    call    _popop
; return
; RPN'ized expression: "tok "
; Expanded expression: "(@4) *(2) "
; Fused expression:    "*(2) (@4) "
    mov     ax, [bp+4]
    jmp     L2997
L2997:
    leave
    ret
; SEGMENT _TEXT
; glb decayArray : (
; prm     ExprTypeSynPtr : * int
; prm     arithmetic : int
;     ) void
SEGMENT _TEXT
    global  _decayArray
_decayArray:
    push    bp
    mov     bp, sp
; loc     ExprTypeSynPtr : (@4): * int
; loc     arithmetic : (@6): int
; if
; RPN'ized expression: "ExprTypeSynPtr *u 0 >= SyntaxStack ExprTypeSynPtr *u + *u 0 + *u 91 == && "
; Expanded expression: "(@4) *(2) *(2) 0 >= _Bool [sh&&->3020] SyntaxStack (@4) *(2) *(2) 4 * + 0 + *(2) 91 == _Bool &&[3020] "
; Fused expression:    "*(2) (@4) >= *ax 0 _Bool [sh&&->3020] *(2) (@4) * *ax 4 + SyntaxStack ax + ax 0 == *ax 91 _Bool &&[3020] "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 0
    setge   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3020
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 91
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3020:
; JumpIfZero
    test    ax, ax
    jz      L3018
; {
; while
; RPN'ized expression: "SyntaxStack ExprTypeSynPtr *u + *u 0 + *u 93 != "
; Expanded expression: "SyntaxStack (@4) *(2) *(2) 4 * + 0 + *(2) 93 != "
L3021:
; Fused expression:    "*(2) (@4) * *ax 4 + SyntaxStack ax + ax 0 != *ax 93 IF! "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 93
    je      L3022
; RPN'ized expression: "ExprTypeSynPtr *u ++ "
; Expanded expression: "(@4) *(2) ++(2) "
; Fused expression:    "*(2) (@4) ++(2) *ax "
    mov     ax, [bp+4]
    mov     bx, ax
    inc     word [bx]
    mov     ax, [bx]
    jmp     L3021
L3022:
; RPN'ized expression: "ExprTypeSynPtr *u ++ "
; Expanded expression: "(@4) *(2) ++(2) "
; Fused expression:    "*(2) (@4) ++(2) *ax "
    mov     ax, [bp+4]
    mov     bx, ax
    inc     word [bx]
    mov     ax, [bx]
; RPN'ized expression: "ExprTypeSynPtr *u ExprTypeSynPtr *u -u = "
; Expanded expression: "(@4) *(2) (@4) *(2) *(2) -u =(2) "
; Fused expression:    "*(2) (@4) push-ax *(2) (@4) *(2) ax -u =(34) **sp ax "
    mov     ax, [bp+4]
    push    ax
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    neg     ax
    pop     bx
    mov     [bx], ax
; }
    jmp     L3019
L3018:
; else
; if
; RPN'ized expression: "ExprTypeSynPtr *u 0 >= SyntaxStack ExprTypeSynPtr *u + *u 0 + *u 42 == && "
; Expanded expression: "(@4) *(2) *(2) 0 >= _Bool [sh&&->3025] SyntaxStack (@4) *(2) *(2) 4 * + 0 + *(2) 42 == _Bool &&[3025] "
; Fused expression:    "*(2) (@4) >= *ax 0 _Bool [sh&&->3025] *(2) (@4) * *ax 4 + SyntaxStack ax + ax 0 == *ax 42 _Bool &&[3025] "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 0
    setge   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3025
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 42
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3025:
; JumpIfZero
    test    ax, ax
    jz      L3023
; {
; RPN'ized expression: "ExprTypeSynPtr *u ++ "
; Expanded expression: "(@4) *(2) ++(2) "
; Fused expression:    "*(2) (@4) ++(2) *ax "
    mov     ax, [bp+4]
    mov     bx, ax
    inc     word [bx]
    mov     ax, [bx]
; RPN'ized expression: "ExprTypeSynPtr *u ExprTypeSynPtr *u -u = "
; Expanded expression: "(@4) *(2) (@4) *(2) *(2) -u =(2) "
; Fused expression:    "*(2) (@4) push-ax *(2) (@4) *(2) ax -u =(34) **sp ax "
    mov     ax, [bp+4]
    push    ax
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    neg     ax
    pop     bx
    mov     [bx], ax
; }
L3023:
L3019:
; if
; RPN'ized expression: "arithmetic "
; Expanded expression: "(@6) *(2) "
; Fused expression:    "*(2) (@6) "
    mov     ax, [bp+6]
; JumpIfZero
    test    ax, ax
    jz      L3026
; {
; if
; RPN'ized expression: "ExprTypeSynPtr *u 0 < "
; Expanded expression: "(@4) *(2) *(2) 0 < "
; Fused expression:    "*(2) (@4) < *ax 0 IF! "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 0
    jge     L3028
; {
; if
; RPN'ized expression: "SyntaxStack ExprTypeSynPtr *u -u + *u 0 + *u 17 == "
; Expanded expression: "SyntaxStack (@4) *(2) *(2) -u 4 * + 0 + *(2) 17 == "
; Fused expression:    "*(2) (@4) *(2) ax -u * ax 4 + SyntaxStack ax + ax 0 == *ax 17 IF! "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    neg     ax
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 17
    jne     L3030
; RPN'ized expression: "( L3032 error ) "
; Expanded expression: " L3032  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3032:
    db  "Error: decayArray(): cannot do pointer arithmetic on a pointer to 'void'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3032 , error )2 "
    push    L3032
    call    _error
    sub     sp, -2
L3030:
; if
; RPN'ized expression: "SyntaxStack ExprTypeSynPtr *u -u + *u 0 + *u 40 == "
; Expanded expression: "SyntaxStack (@4) *(2) *(2) -u 4 * + 0 + *(2) 40 == "
; Fused expression:    "*(2) (@4) *(2) ax -u * ax 4 + SyntaxStack ax + ax 0 == *ax 40 IF! "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    neg     ax
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 40
    jne     L3034
; RPN'ized expression: "( L3036 error ) "
; Expanded expression: " L3036  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3036:
    db  "Error: decayArray(): cannot do pointer arithmetic on a pointer to a function",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3036 , error )2 "
    push    L3036
    call    _error
    sub     sp, -2
L3034:
; }
    jmp     L3029
L3028:
; else
; {
; if
; RPN'ized expression: "SyntaxStack ExprTypeSynPtr *u + *u 0 + *u 40 == "
; Expanded expression: "SyntaxStack (@4) *(2) *(2) 4 * + 0 + *(2) 40 == "
; Fused expression:    "*(2) (@4) * *ax 4 + SyntaxStack ax + ax 0 == *ax 40 IF! "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 40
    jne     L3038
; RPN'ized expression: "( L3040 error ) "
; Expanded expression: " L3040  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3040:
    db  "Error: decayArray(): cannot do arithmetic on a function",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3040 , error )2 "
    push    L3040
    call    _error
    sub     sp, -2
L3038:
; }
L3029:
; }
L3026:
L3017:
    leave
    ret
; SEGMENT _TEXT
; glb nonVoidTypeCheck : (
; prm     ExprTypeSynPtr : int
; prm     tok : int
;     ) void
SEGMENT _TEXT
    global  _nonVoidTypeCheck
_nonVoidTypeCheck:
    push    bp
    mov     bp, sp
; loc     ExprTypeSynPtr : (@4): int
; loc     tok : (@6): int
; if
; RPN'ized expression: "ExprTypeSynPtr 0 >= SyntaxStack ExprTypeSynPtr + *u 0 + *u 17 == && "
; Expanded expression: "(@4) *(2) 0 >= _Bool [sh&&->3045] SyntaxStack (@4) *(2) 4 * + 0 + *(2) 17 == _Bool &&[3045] "
; Fused expression:    ">= *(@4) 0 _Bool [sh&&->3045] * *(@4) 4 + SyntaxStack ax + ax 0 == *ax 17 _Bool &&[3045] "
    mov     ax, [bp+4]
    cmp     ax, 0
    setge   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3045
    mov     ax, [bp+4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 17
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3045:
; JumpIfZero
    test    ax, ax
    jz      L3043
; RPN'ized expression: "( ( tok GetTokenName ) , L3046 error ) "
; Expanded expression: "  (@6) *(2)  GetTokenName ()2  L3046  error ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3046:
    db  "Error: nonVoidTypeCheck(): unexpected operand type 'void' for operator '%s'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( *(2) (@6) , GetTokenName )2 , L3046 , error )4 "
    push    word [bp+6]
    call    _GetTokenName
    sub     sp, -2
    push    ax
    push    L3046
    call    _error
    sub     sp, -4
L3043:
L3042:
    leave
    ret
; SEGMENT _TEXT
; glb numericTypeCheck : (
; prm     ExprTypeSynPtr : int
; prm     tok : int
;     ) void
SEGMENT _TEXT
    global  _numericTypeCheck
_numericTypeCheck:
    push    bp
    mov     bp, sp
; loc     ExprTypeSynPtr : (@4): int
; loc     tok : (@6): int
; if
; RPN'ized expression: "ExprTypeSynPtr 0 >= SyntaxStack ExprTypeSynPtr + *u 0 + *u 18 == SyntaxStack ExprTypeSynPtr + *u 0 + *u 19 == || && "
; Expanded expression: "(@4) *(2) 0 >= _Bool [sh&&->3051] SyntaxStack (@4) *(2) 4 * + 0 + *(2) 18 == _Bool [sh||->3052] SyntaxStack (@4) *(2) 4 * + 0 + *(2) 19 == _Bool ||[3052] _Bool &&[3051] "
; Fused expression:    ">= *(@4) 0 _Bool [sh&&->3051] * *(@4) 4 + SyntaxStack ax + ax 0 == *ax 18 _Bool [sh||->3052] * *(@4) 4 + SyntaxStack ax + ax 0 == *ax 19 _Bool ||[3052] _Bool &&[3051] "
    mov     ax, [bp+4]
    cmp     ax, 0
    setge   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3051
    mov     ax, [bp+4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 18
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L3052
    mov     ax, [bp+4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 19
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3052:
    test    ax, ax
    setnz   al
    cbw
L3051:
; JumpIfZero
    test    ax, ax
    jz      L3049
; return
    jmp     L3048
L3049:
; RPN'ized expression: "( ( tok GetTokenName ) , L3053 error ) "
; Expanded expression: "  (@6) *(2)  GetTokenName ()2  L3053  error ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3053:
    db  "Error: numericTypeCheck(): unexpected operand type for operator '%s', numeric type expected",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( *(2) (@6) , GetTokenName )2 , L3053 , error )4 "
    push    word [bp+6]
    call    _GetTokenName
    sub     sp, -2
    push    ax
    push    L3053
    call    _error
    sub     sp, -4
L3048:
    leave
    ret
; SEGMENT _TEXT
; glb promoteType : (
; prm     ExprTypeSynPtr : * int
;     ) void
SEGMENT _TEXT
    global  _promoteType
_promoteType:
    push    bp
    mov     bp, sp
; loc     ExprTypeSynPtr : (@4): * int
; if
; RPN'ized expression: "ExprTypeSynPtr *u 0 >= SyntaxStack ExprTypeSynPtr *u + *u 0 + *u 18 == && "
; Expanded expression: "(@4) *(2) *(2) 0 >= _Bool [sh&&->3058] SyntaxStack (@4) *(2) *(2) 4 * + 0 + *(2) 18 == _Bool &&[3058] "
; Fused expression:    "*(2) (@4) >= *ax 0 _Bool [sh&&->3058] *(2) (@4) * *ax 4 + SyntaxStack ax + ax 0 == *ax 18 _Bool &&[3058] "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 0
    setge   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3058
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 18
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3058:
; JumpIfZero
    test    ax, ax
    jz      L3056
; RPN'ized expression: "ExprTypeSynPtr *u 1 = "
; Expanded expression: "(@4) *(2) 1 =(2) "
; Fused expression:    "*(2) (@4) =(34) *ax 1 "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, 1
    mov     [bx], ax
L3056:
L3055:
    leave
    ret
; SEGMENT _TEXT
; glb GetFxnInfo : (
; prm     ExprTypeSynPtr : int
; prm     MinParams : * int
; prm     MaxParams : * int
; prm     ReturnExprTypeSynPtr : * int
;     ) int
SEGMENT _TEXT
    global  _GetFxnInfo
_GetFxnInfo:
    push    bp
    mov     bp, sp
; loc     ExprTypeSynPtr : (@4): int
; loc     MinParams : (@6): * int
; loc     MaxParams : (@8): * int
; loc     ReturnExprTypeSynPtr : (@10): * int
; loc     ptr : (@-2): int
    sub     sp, 2
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "=(34) *(@-2) 0 "
    mov     ax, 0
    mov     [bp-2], ax
; RPN'ized expression: "MaxParams *u MinParams *u 0 = = "
; Expanded expression: "(@8) *(2) (@6) *(2) 0 =(2) =(2) "
; Fused expression:    "*(2) (@8) push-ax *(2) (@6) =(34) *ax 0 =(34) **sp ax "
    mov     ax, [bp+8]
    push    ax
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, 0
    mov     [bx], ax
    pop     bx
    mov     [bx], ax
; if
; RPN'ized expression: "ExprTypeSynPtr 0 < "
; Expanded expression: "(@4) *(2) 0 < "
; Fused expression:    "< *(@4) 0 IF! "
    mov     ax, [bp+4]
    cmp     ax, 0
    jge     L3060
; {
; RPN'ized expression: "ptr 1 = "
; Expanded expression: "(@-2) 1 =(2) "
; Fused expression:    "=(34) *(@-2) 1 "
    mov     ax, 1
    mov     [bp-2], ax
; RPN'ized expression: "ExprTypeSynPtr ExprTypeSynPtr -u = "
; Expanded expression: "(@4) (@4) *(2) -u =(2) "
; Fused expression:    "*(2) (@4) -u =(34) *(@4) ax "
    mov     ax, [bp+4]
    neg     ax
    mov     [bp+4], ax
; }
L3060:
; while
; RPN'ized expression: "SyntaxStack ExprTypeSynPtr + *u 0 + *u 16 == SyntaxStack ExprTypeSynPtr + *u 0 + *u 89 == || "
; Expanded expression: "SyntaxStack (@4) *(2) 4 * + 0 + *(2) 16 == _Bool [sh||->3064] SyntaxStack (@4) *(2) 4 * + 0 + *(2) 89 == _Bool ||[3064] "
L3062:
; Fused expression:    "* *(@4) 4 + SyntaxStack ax + ax 0 == *ax 16 _Bool [sh||->3064] * *(@4) 4 + SyntaxStack ax + ax 0 == *ax 89 _Bool ||[3064] "
    mov     ax, [bp+4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 16
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L3064
    mov     ax, [bp+4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 89
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3064:
; JumpIfZero
    test    ax, ax
    jz      L3063
; RPN'ized expression: "ExprTypeSynPtr ++p "
; Expanded expression: "(@4) ++p(2) "
; Fused expression:    "++p(2) *(@4) "
    mov     ax, [bp+4]
    inc     word [bp+4]
    jmp     L3062
L3063:
; if
; RPN'ized expression: "SyntaxStack ExprTypeSynPtr + *u 0 + *u 40 == ptr 0 == SyntaxStack ExprTypeSynPtr + *u 0 + *u 42 == && SyntaxStack ExprTypeSynPtr 1 + + *u 0 + *u 40 == && || 0 == "
; Expanded expression: "SyntaxStack (@4) *(2) 4 * + 0 + *(2) 40 == _Bool [sh||->3067] (@-2) *(2) 0 == _Bool [sh&&->3069] SyntaxStack (@4) *(2) 4 * + 0 + *(2) 42 == _Bool &&[3069] _Bool [sh&&->3068] SyntaxStack (@4) *(2) 1 + 4 * + 0 + *(2) 40 == _Bool &&[3068] _Bool ||[3067] 0 == "
; Fused expression:    "* *(@4) 4 + SyntaxStack ax + ax 0 == *ax 40 _Bool [sh||->3067] == *(@-2) 0 _Bool [sh&&->3069] * *(@4) 4 + SyntaxStack ax + ax 0 == *ax 42 _Bool &&[3069] _Bool [sh&&->3068] + *(@4) 1 * ax 4 + SyntaxStack ax + ax 0 == *ax 40 _Bool &&[3068] _Bool ||[3067] == ax 0 IF! "
    mov     ax, [bp+4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 40
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L3067
    mov     ax, [bp-2]
    cmp     ax, 0
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3069
    mov     ax, [bp+4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 42
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3069:
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3068
    mov     ax, [bp+4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 40
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3068:
    test    ax, ax
    setnz   al
    cbw
L3067:
    cmp     ax, 0
    jne     L3065
; return
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "0 "
    mov     ax, 0
    jmp     L3059
L3065:
; while
; RPN'ized expression: "SyntaxStack ExprTypeSynPtr + *u 0 + *u 40 != "
; Expanded expression: "SyntaxStack (@4) *(2) 4 * + 0 + *(2) 40 != "
L3070:
; Fused expression:    "* *(@4) 4 + SyntaxStack ax + ax 0 != *ax 40 IF! "
    mov     ax, [bp+4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 40
    je      L3071
; RPN'ized expression: "ExprTypeSynPtr ++p "
; Expanded expression: "(@4) ++p(2) "
; Fused expression:    "++p(2) *(@4) "
    mov     ax, [bp+4]
    inc     word [bp+4]
    jmp     L3070
L3071:
; RPN'ized expression: "ExprTypeSynPtr ++p "
; Expanded expression: "(@4) ++p(2) "
; Fused expression:    "++p(2) *(@4) "
    mov     ax, [bp+4]
    inc     word [bp+4]
; if
; RPN'ized expression: "SyntaxStack ExprTypeSynPtr + *u 0 + *u 41 == "
; Expanded expression: "SyntaxStack (@4) *(2) 4 * + 0 + *(2) 41 == "
; Fused expression:    "* *(@4) 4 + SyntaxStack ax + ax 0 == *ax 41 IF! "
    mov     ax, [bp+4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 41
    jne     L3072
; {
; RPN'ized expression: "MaxParams *u 32767 = "
; Expanded expression: "(@8) *(2) 32767 =(2) "
; Fused expression:    "*(2) (@8) =(34) *ax 32767 "
    mov     ax, [bp+8]
    mov     bx, ax
    mov     ax, 32767
    mov     [bx], ax
; RPN'ized expression: "ReturnExprTypeSynPtr *u ExprTypeSynPtr 1 + = "
; Expanded expression: "(@10) *(2) (@4) *(2) 1 + =(2) "
; Fused expression:    "*(2) (@10) push-ax + *(@4) 1 =(34) **sp ax "
    mov     ax, [bp+10]
    push    ax
    mov     ax, [bp+4]
    add     ax, 1
    pop     bx
    mov     [bx], ax
; return
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
    mov     ax, 1
    jmp     L3059
; }
L3072:
; if
; RPN'ized expression: "SyntaxStack ExprTypeSynPtr 1 + + *u 0 + *u 17 == "
; Expanded expression: "SyntaxStack (@4) *(2) 1 + 4 * + 0 + *(2) 17 == "
; Fused expression:    "+ *(@4) 1 * ax 4 + SyntaxStack ax + ax 0 == *ax 17 IF! "
    mov     ax, [bp+4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 17
    jne     L3074
; {
; RPN'ized expression: "ReturnExprTypeSynPtr *u ExprTypeSynPtr 3 + = "
; Expanded expression: "(@10) *(2) (@4) *(2) 3 + =(2) "
; Fused expression:    "*(2) (@10) push-ax + *(@4) 3 =(34) **sp ax "
    mov     ax, [bp+10]
    push    ax
    mov     ax, [bp+4]
    add     ax, 3
    pop     bx
    mov     [bx], ax
; return
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
    mov     ax, 1
    jmp     L3059
; }
L3074:
; for
L3076:
    jmp     L3078
L3077:
    jmp     L3076
L3078:
; {
; loc         tok : (@-4): int
    sub     sp, 2
; =
; RPN'ized expression: "SyntaxStack ExprTypeSynPtr + *u 0 + *u "
; Expanded expression: "SyntaxStack (@4) *(2) 4 * + 0 + *(2) "
; Fused expression:    "* *(@4) 4 + SyntaxStack ax + ax 0 =(34) *(@-4) *ax "
    mov     ax, [bp+4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-4], ax
; if
; RPN'ized expression: "tok 16 == "
; Expanded expression: "(@-4) *(2) 16 == "
; Fused expression:    "== *(@-4) 16 IF! "
    mov     ax, [bp-4]
    cmp     ax, 16
    jne     L3080
; {
; if
; RPN'ized expression: "SyntaxStack ExprTypeSynPtr 1 + + *u 0 + *u 15 != "
; Expanded expression: "SyntaxStack (@4) *(2) 1 + 4 * + 0 + *(2) 15 != "
; Fused expression:    "+ *(@4) 1 * ax 4 + SyntaxStack ax + ax 0 != *ax 15 IF! "
    mov     ax, [bp+4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 15
    je      L3082
; {
; RPN'ized expression: "MinParams *u ++ "
; Expanded expression: "(@6) *(2) ++(2) "
; Fused expression:    "*(2) (@6) ++(2) *ax "
    mov     ax, [bp+6]
    mov     bx, ax
    inc     word [bx]
    mov     ax, [bx]
; RPN'ized expression: "MaxParams *u ++ "
; Expanded expression: "(@8) *(2) ++(2) "
; Fused expression:    "*(2) (@8) ++(2) *ax "
    mov     ax, [bp+8]
    mov     bx, ax
    inc     word [bx]
    mov     ax, [bx]
; }
    jmp     L3083
L3082:
; else
; {
; RPN'ized expression: "MaxParams *u 32767 = "
; Expanded expression: "(@8) *(2) 32767 =(2) "
; Fused expression:    "*(2) (@8) =(34) *ax 32767 "
    mov     ax, [bp+8]
    mov     bx, ax
    mov     ax, 32767
    mov     [bx], ax
; }
L3083:
; }
    jmp     L3081
L3080:
; else
; if
; RPN'ized expression: "tok 40 == "
; Expanded expression: "(@-4) *(2) 40 == "
; Fused expression:    "== *(@-4) 40 IF! "
    mov     ax, [bp-4]
    cmp     ax, 40
    jne     L3084
; {
; loc             c : (@-6): int
    sub     sp, 2
; =
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "=(34) *(@-6) 1 "
    mov     ax, 1
    mov     [bp-6], ax
; while
; RPN'ized expression: "c ExprTypeSynPtr SyntaxStackCnt < && "
; Expanded expression: "(@-6) *(2) _Bool [sh&&->3088] (@4) *(2) SyntaxStackCnt *(2) < _Bool &&[3088] "
L3086:
; Fused expression:    "*(2) (@-6) _Bool [sh&&->3088] < *(@4) *SyntaxStackCnt _Bool &&[3088] "
    mov     ax, [bp-6]
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3088
    mov     ax, [bp+4]
    cmp     ax, [_SyntaxStackCnt]
    setl    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3088:
; JumpIfZero
    test    ax, ax
    jz      L3087
; {
; RPN'ized expression: "tok SyntaxStack ExprTypeSynPtr ++ + *u 0 + *u = "
; Expanded expression: "(@-4) SyntaxStack (@4) ++(2) 4 * + 0 + *(2) =(2) "
; Fused expression:    "++(2) *(@4) * ax 4 + SyntaxStack ax + ax 0 =(34) *(@-4) *ax "
    inc     word [bp+4]
    mov     ax, [bp+4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-4], ax
; RPN'ized expression: "c tok 40 == tok 41 == - += "
; Expanded expression: "(@-6) (@-4) *(2) 40 == (@-4) *(2) 41 == - +=(2) "
; Fused expression:    "== *(@-4) 40 push-ax == *(@-4) 41 - *sp ax +=(34) *(@-6) ax "
    mov     ax, [bp-4]
    cmp     ax, 40
    sete    al
    cbw
    push    ax
    mov     ax, [bp-4]
    cmp     ax, 41
    sete    al
    cbw
    mov     cx, ax
    pop     ax
    sub     ax, cx
    mov     cx, ax
    mov     ax, [bp-6]
    add     ax, cx
    mov     [bp-6], ax
; }
    jmp     L3086
L3087:
    sub     sp, -2
; }
    jmp     L3085
L3084:
; else
; if
; RPN'ized expression: "tok 41 == "
; Expanded expression: "(@-4) *(2) 41 == "
; Fused expression:    "== *(@-4) 41 IF! "
    mov     ax, [bp-4]
    cmp     ax, 41
    jne     L3089
; {
; RPN'ized expression: "ExprTypeSynPtr ++p "
; Expanded expression: "(@4) ++p(2) "
; Fused expression:    "++p(2) *(@4) "
    mov     ax, [bp+4]
    inc     word [bp+4]
; break
    sub     sp, -2
    jmp     L3079
; }
L3089:
L3085:
L3081:
; RPN'ized expression: "ExprTypeSynPtr ++p "
; Expanded expression: "(@4) ++p(2) "
; Fused expression:    "++p(2) *(@4) "
    mov     ax, [bp+4]
    inc     word [bp+4]
    sub     sp, -2
; }
    jmp     L3077
L3079:
; RPN'ized expression: "ReturnExprTypeSynPtr *u ExprTypeSynPtr = "
; Expanded expression: "(@10) *(2) (@4) *(2) =(2) "
; Fused expression:    "*(2) (@10) =(34) *ax *(@4) "
    mov     ax, [bp+10]
    mov     bx, ax
    mov     ax, [bp+4]
    mov     [bx], ax
; return
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
    mov     ax, 1
    jmp     L3059
L3059:
    leave
    ret
; SEGMENT _TEXT
; glb simplifyConstExpr : (
; prm     val : int
; prm     isConst : int
; prm     top : int
; prm     bottom : int
;     ) void
SEGMENT _TEXT
    global  _simplifyConstExpr
_simplifyConstExpr:
    push    bp
    mov     bp, sp
; loc     val : (@4): int
; loc     isConst : (@6): int
; loc     top : (@8): int
; loc     bottom : (@10): int
; if
; RPN'ized expression: "isConst 0 == stack top + *u 0 + *u 1 == || "
; Expanded expression: "(@6) *(2) 0 == _Bool [sh||->3094] stack (@8) *(2) 4 * + 0 + *(2) 1 == _Bool ||[3094] "
; Fused expression:    "== *(@6) 0 _Bool [sh||->3094] * *(@8) 4 + stack ax + ax 0 == *ax 1 _Bool ||[3094] "
    mov     ax, [bp+6]
    cmp     ax, 0
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L3094
    mov     ax, [bp+8]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 1
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3094:
; JumpIfZero
    test    ax, ax
    jz      L3092
; return
    jmp     L3091
L3092:
; RPN'ized expression: "stack top + *u 0 + *u 1 = "
; Expanded expression: "stack (@8) *(2) 4 * + 0 + 1 =(2) "
; Fused expression:    "* *(@8) 4 + stack ax + ax 0 =(34) *ax 1 "
    mov     ax, [bp+8]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, 1
    mov     [bx], ax
; RPN'ized expression: "stack top + *u 1 + *u val = "
; Expanded expression: "stack (@8) *(2) 4 * + 2 + (@4) *(2) =(2) "
; Fused expression:    "* *(@8) 4 + stack ax + ax 2 =(34) *ax *(@4) "
    mov     ax, [bp+8]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bp+4]
    mov     [bx], ax
; RPN'ized expression: "( top bottom - , bottom del ) "
; Expanded expression: " (@8) *(2) (@10) *(2) -  (@10) *(2)  del ()4 "
; Fused expression:    "( - *(@8) *(@10) , *(2) (@10) , del )4 "
    mov     ax, [bp+8]
    sub     ax, [bp+10]
    push    ax
    push    word [bp+10]
    call    _del
    sub     sp, -4
L3091:
    leave
    ret
; SEGMENT _TEXT
; glb exprval : (
; prm     idx : * int
; prm     ExprTypeSynPtr : * int
; prm     ConstExpr : * int
;     ) int
SEGMENT _TEXT
    global  _exprval
_exprval:
    push    bp
    mov     bp, sp
; loc     idx : (@4): * int
; loc     ExprTypeSynPtr : (@6): * int
; loc     ConstExpr : (@8): * int
; loc     tok : (@-2): int
    sub     sp, 2
; loc     s : (@-4): int
    sub     sp, 2
; loc     RightExprTypeSynPtr : (@-6): int
    sub     sp, 2
; loc     oldIdxRight : (@-8): int
    sub     sp, 2
; loc     oldSpRight : (@-10): int
    sub     sp, 2
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
; loc     constExpr : (@-14): [2] int
    sub     sp, 4
; if
; RPN'ized expression: "idx *u 0 < "
; Expanded expression: "(@4) *(2) *(2) 0 < "
; Fused expression:    "*(2) (@4) < *ax 0 IF! "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 0
    jge     L3096
; RPN'ized expression: "( L3098 error ) "
; Expanded expression: " L3098  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3098:
    db  "exprval(): idx < 0",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3098 , error )2 "
    push    L3098
    call    _error
    sub     sp, -2
L3096:
; RPN'ized expression: "tok stack idx *u + *u 0 + *u = "
; Expanded expression: "(@-2) stack (@4) *(2) *(2) 4 * + 0 + *(2) =(2) "
; Fused expression:    "*(2) (@4) * *ax 4 + stack ax + ax 0 =(34) *(@-2) *ax "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-2], ax
; RPN'ized expression: "s stack idx *u + *u 1 + *u = "
; Expanded expression: "(@-4) stack (@4) *(2) *(2) 4 * + 2 + *(2) =(2) "
; Fused expression:    "*(2) (@4) * *ax 4 + stack ax + ax 2 =(34) *(@-4) *ax "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-4], ax
; RPN'ized expression: "idx *u -- "
; Expanded expression: "(@4) *(2) --(2) "
; Fused expression:    "*(2) (@4) --(2) *ax "
    mov     ax, [bp+4]
    mov     bx, ax
    dec     word [bx]
    mov     ax, [bx]
; RPN'ized expression: "oldIdxRight idx *u = "
; Expanded expression: "(@-8) (@4) *(2) *(2) =(2) "
; Fused expression:    "*(2) (@4) =(34) *(@-8) *ax "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-8], ax
; RPN'ized expression: "oldSpRight sp = "
; Expanded expression: "(@-10) sp *(2) =(2) "
; Fused expression:    "=(34) *(@-10) *sp "
    mov     ax, [_sp]
    mov     [bp-10], ax
; switch
; RPN'ized expression: "tok "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
    mov     ax, [bp-2]
    jmp     L3102
; {
; case
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
    jmp     L3103
L3102:
    cmp     ax, 1
    jne     L3104
L3103:
; case
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
    jmp     L3105
L3104:
    cmp     ax, 2
    jne     L3106
L3105:
; RPN'ized expression: "ExprTypeSynPtr *u 1 = "
; Expanded expression: "(@6) *(2) 1 =(2) "
; Fused expression:    "*(2) (@6) =(34) *ax 1 "
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, 1
    mov     [bx], ax
; RPN'ized expression: "ConstExpr *u 1 = "
; Expanded expression: "(@8) *(2) 1 =(2) "
; Fused expression:    "*(2) (@8) =(34) *ax 1 "
    mov     ax, [bp+8]
    mov     bx, ax
    mov     ax, 1
    mov     [bx], ax
; break
    jmp     L3100
; case
; RPN'ized expression: "16 "
; Expanded expression: "16 "
; Expression value: 16
    jmp     L3107
L3106:
    cmp     ax, 16
    jne     L3108
L3107:
; {
; loc             synPtr : (@-16): int
    sub     sp, 2
; =
; RPN'ized expression: "( IdentTable s + FindSymbol ) "
; Expanded expression: " IdentTable (@-4) *(2) +  FindSymbol ()2 "
; Fused expression:    "( + IdentTable *(@-4) , FindSymbol )2 =(34) *(@-16) ax "
    mov     ax, _IdentTable
    add     ax, [bp-4]
    push    ax
    call    _FindSymbol
    sub     sp, -2
    mov     [bp-16], ax
; loc             type : (@-18): int
    sub     sp, 2
; =
; RPN'ized expression: "( synPtr SymType ) "
; Expanded expression: " (@-16) *(2)  SymType ()2 "
; Fused expression:    "( *(2) (@-16) , SymType )2 =(34) *(@-18) ax "
    push    word [bp-16]
    call    _SymType
    sub     sp, -2
    mov     [bp-18], ax
; if
; RPN'ized expression: "( L3112 , IdentTable SyntaxStack synPtr + *u 1 + *u + strcmp ) 0 == idx *u 2 + sp >= stack idx *u 2 + + *u 0 + *u 27 != || && "
; Expanded expression: " L3112  IdentTable SyntaxStack (@-16) *(2) 4 * + 2 + *(2) +  strcmp ()4 0 == _Bool [sh&&->3114] (@4) *(2) *(2) 2 + sp *(2) >= _Bool [sh||->3115] stack (@4) *(2) *(2) 2 + 4 * + 0 + *(2) 27 != _Bool ||[3115] _Bool &&[3114] "
; SEGMENT _TEXT
SEGMENT _DATA
L3112:
    db  "<something>",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3112 , * *(@-16) 4 + SyntaxStack ax + ax 2 + IdentTable *ax , strcmp )4 == ax 0 _Bool [sh&&->3114] *(2) (@4) + *ax 2 >= ax *sp _Bool [sh||->3115] *(2) (@4) + *ax 2 * ax 4 + stack ax + ax 0 != *ax 27 _Bool ||[3115] _Bool &&[3114] "
    push    L3112
    mov     ax, [bp-16]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, _IdentTable
    add     ax, cx
    push    ax
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3114
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    add     ax, 2
    cmp     ax, [_sp]
    setge   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L3115
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    add     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 27
    setne   al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3115:
    test    ax, ax
    setnz   al
    cbw
L3114:
; JumpIfZero
    test    ax, ax
    jz      L3110
; RPN'ized expression: "( L3116 error ) "
; Expanded expression: " L3116  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3116:
    db  "Error: exprval(): unexpected type declaration",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3116 , error )2 "
    push    L3116
    call    _error
    sub     sp, -2
L3110:
; if
; RPN'ized expression: "type 4 == type 5 == || "
; Expanded expression: "(@-18) *(2) 4 == _Bool [sh||->3120] (@-18) *(2) 5 == _Bool ||[3120] "
; Fused expression:    "== *(@-18) 4 _Bool [sh||->3120] == *(@-18) 5 _Bool ||[3120] "
    mov     ax, [bp-18]
    cmp     ax, 4
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L3120
    mov     ax, [bp-18]
    cmp     ax, 5
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3120:
; JumpIfZero
    test    ax, ax
    jz      L3118
; {
; RPN'ized expression: "stack idx *u 1 + + *u 0 + *u 89 = "
; Expanded expression: "stack (@4) *(2) *(2) 1 + 4 * + 0 + 89 =(2) "
; Fused expression:    "*(2) (@4) + *ax 1 * ax 4 + stack ax + ax 0 =(34) *ax 89 "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, 89
    mov     [bx], ax
; RPN'ized expression: "stack idx *u 1 + + *u 1 + *u SyntaxStack synPtr 1 + + *u 1 + *u = "
; Expanded expression: "stack (@4) *(2) *(2) 1 + 4 * + 2 + SyntaxStack (@-16) *(2) 1 + 4 * + 2 + *(2) =(2) "
; Fused expression:    "*(2) (@4) + *ax 1 * ax 4 + stack ax + ax 2 push-ax + *(@-16) 1 * ax 4 + SyntaxStack ax + ax 2 =(34) **sp *ax "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    push    ax
    mov     ax, [bp-16]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bx]
    pop     bx
    mov     [bx], ax
; }
L3118:
; if
; RPN'ized expression: "type 4 == type 2 == || "
; Expanded expression: "(@-18) *(2) 4 == _Bool [sh||->3123] (@-18) *(2) 2 == _Bool ||[3123] "
; Fused expression:    "== *(@-18) 4 _Bool [sh||->3123] == *(@-18) 2 _Bool ||[3123] "
    mov     ax, [bp-18]
    cmp     ax, 4
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L3123
    mov     ax, [bp-18]
    cmp     ax, 2
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3123:
; JumpIfZero
    test    ax, ax
    jz      L3121
; {
; RPN'ized expression: "( ( synPtr GetDeclSize ) , 78 , idx *u 2 + ins2 ) "
; Expanded expression: "  (@-16) *(2)  GetDeclSize ()2  78  (@4) *(2) *(2) 2 +  ins2 ()6 "
; Fused expression:    "( ( *(2) (@-16) , GetDeclSize )2 , 78 , *(2) (@4) + *ax 2 , ins2 )6 "
    push    word [bp-16]
    call    _GetDeclSize
    sub     sp, -2
    push    ax
    push    78
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    add     ax, 2
    push    ax
    call    _ins2
    sub     sp, -6
; }
L3121:
; while
; RPN'ized expression: "SyntaxStack synPtr + *u 0 + *u 16 == SyntaxStack synPtr + *u 0 + *u 89 == || "
; Expanded expression: "SyntaxStack (@-16) *(2) 4 * + 0 + *(2) 16 == _Bool [sh||->3126] SyntaxStack (@-16) *(2) 4 * + 0 + *(2) 89 == _Bool ||[3126] "
L3124:
; Fused expression:    "* *(@-16) 4 + SyntaxStack ax + ax 0 == *ax 16 _Bool [sh||->3126] * *(@-16) 4 + SyntaxStack ax + ax 0 == *ax 89 _Bool ||[3126] "
    mov     ax, [bp-16]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 16
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L3126
    mov     ax, [bp-16]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 89
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3126:
; JumpIfZero
    test    ax, ax
    jz      L3125
; RPN'ized expression: "synPtr ++p "
; Expanded expression: "(@-16) ++p(2) "
; Fused expression:    "++p(2) *(@-16) "
    mov     ax, [bp-16]
    inc     word [bp-16]
    jmp     L3124
L3125:
; RPN'ized expression: "ExprTypeSynPtr *u synPtr = "
; Expanded expression: "(@6) *(2) (@-16) *(2) =(2) "
; Fused expression:    "*(2) (@6) =(34) *ax *(@-16) "
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, [bp-16]
    mov     [bx], ax
    sub     sp, -4
; }
; RPN'ized expression: "ConstExpr *u 0 = "
; Expanded expression: "(@8) *(2) 0 =(2) "
; Fused expression:    "*(2) (@8) =(34) *ax 0 "
    mov     ax, [bp+8]
    mov     bx, ax
    mov     ax, 0
    mov     [bx], ax
; break
    jmp     L3100
; case
; RPN'ized expression: "27 "
; Expanded expression: "27 "
; Expression value: 27
    jmp     L3109
L3108:
    cmp     ax, 27
    jne     L3127
L3109:
; RPN'ized expression: "s ( ConstExpr , ExprTypeSynPtr , idx exprval ) = "
; Expanded expression: "(@-4)  (@8) *(2)  (@6) *(2)  (@4) *(2)  exprval ()6 =(2) "
; Fused expression:    "( *(2) (@8) , *(2) (@6) , *(2) (@4) , exprval )6 =(34) *(@-4) ax "
    push    word [bp+8]
    push    word [bp+6]
    push    word [bp+4]
    call    _exprval
    sub     sp, -6
    mov     [bp-4], ax
; if
; RPN'ized expression: "ExprTypeSynPtr *u 0 >= "
; Expanded expression: "(@6) *(2) *(2) 0 >= "
; Fused expression:    "*(2) (@6) >= *ax 0 IF! "
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 0
    jl      L3129
; RPN'ized expression: "s ( ExprTypeSynPtr *u GetDeclSize ) = "
; Expanded expression: "(@-4)  (@6) *(2) *(2)  GetDeclSize ()2 =(2) "
; Fused expression:    "( *(2) (@6) *(2) ax , GetDeclSize )2 =(34) *(@-4) ax "
    mov     ax, [bp+6]
    mov     bx, ax
    push    word [bx]
    call    _GetDeclSize
    sub     sp, -2
    mov     [bp-4], ax
    jmp     L3130
L3129:
; else
; RPN'ized expression: "s SizeOfWord = "
; Expanded expression: "(@-4) SizeOfWord *(2) =(2) "
; Fused expression:    "=(34) *(@-4) *SizeOfWord "
    mov     ax, [_SizeOfWord]
    mov     [bp-4], ax
L3130:
; if
; RPN'ized expression: "s 0 <= "
; Expanded expression: "(@-4) *(2) 0 <= "
; Fused expression:    "<= *(@-4) 0 IF! "
    mov     ax, [bp-4]
    cmp     ax, 0
    jg      L3131
; RPN'ized expression: "( L3133 error ) "
; Expanded expression: " L3133  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3133:
    db  "Error: exprval(): sizeof of incomplete type (e.g. 'void')",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3133 , error )2 "
    push    L3133
    call    _error
    sub     sp, -2
L3131:
; RPN'ized expression: "stack oldIdxRight 1 + oldSpRight sp - - + *u 0 + *u 1 = "
; Expanded expression: "stack (@-8) *(2) 1 + (@-10) *(2) sp *(2) - - 4 * + 0 + 1 =(2) "
; Fused expression:    "+ *(@-8) 1 push-ax - *(@-10) *sp - *sp ax * ax 4 + stack ax + ax 0 =(34) *ax 1 "
    mov     ax, [bp-8]
    add     ax, 1
    push    ax
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    pop     ax
    sub     ax, cx
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, 1
    mov     [bx], ax
; RPN'ized expression: "stack oldIdxRight 1 + oldSpRight sp - - + *u 1 + *u s = "
; Expanded expression: "stack (@-8) *(2) 1 + (@-10) *(2) sp *(2) - - 4 * + 2 + (@-4) *(2) =(2) "
; Fused expression:    "+ *(@-8) 1 push-ax - *(@-10) *sp - *sp ax * ax 4 + stack ax + ax 2 =(34) *ax *(@-4) "
    mov     ax, [bp-8]
    add     ax, 1
    push    ax
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    pop     ax
    sub     ax, cx
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bp-4]
    mov     [bx], ax
; RPN'ized expression: "( oldIdxRight oldSpRight sp - - idx *u - , idx *u 1 + del ) "
; Expanded expression: " (@-8) *(2) (@-10) *(2) sp *(2) - - (@4) *(2) *(2) -  (@4) *(2) *(2) 1 +  del ()4 "
; Fused expression:    "( - *(@-10) *sp - *(@-8) ax push-ax *(2) (@4) - *sp *ax , *(2) (@4) + *ax 1 , del )4 "
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    mov     ax, [bp-8]
    sub     ax, cx
    push    ax
    mov     ax, [bp+4]
    mov     bx, ax
    mov     cx, [bx]
    pop     ax
    sub     ax, cx
    push    ax
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    add     ax, 1
    push    ax
    call    _del
    sub     sp, -4
; RPN'ized expression: "ExprTypeSynPtr *u 1 = "
; Expanded expression: "(@6) *(2) 1 =(2) "
; Fused expression:    "*(2) (@6) =(34) *ax 1 "
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, 1
    mov     [bx], ax
; RPN'ized expression: "ConstExpr *u 1 = "
; Expanded expression: "(@8) *(2) 1 =(2) "
; Fused expression:    "*(2) (@8) =(34) *ax 1 "
    mov     ax, [bp+8]
    mov     bx, ax
    mov     ax, 1
    mov     [bx], ax
; break
    jmp     L3100
; case
; RPN'ized expression: "77 "
; Expanded expression: "77 "
; Expression value: 77
    jmp     L3128
L3127:
    cmp     ax, 77
    jne     L3135
L3128:
; RPN'ized expression: "( ConstExpr , ExprTypeSynPtr , idx exprval ) "
; Expanded expression: " (@8) *(2)  (@6) *(2)  (@4) *(2)  exprval ()6 "
; Fused expression:    "( *(2) (@8) , *(2) (@6) , *(2) (@4) , exprval )6 "
    push    word [bp+8]
    push    word [bp+6]
    push    word [bp+4]
    call    _exprval
    sub     sp, -6
; if
; RPN'ized expression: "ExprTypeSynPtr *u 0 >= SyntaxStack ExprTypeSynPtr *u + *u 0 + *u 91 == && "
; Expanded expression: "(@6) *(2) *(2) 0 >= _Bool [sh&&->3139] SyntaxStack (@6) *(2) *(2) 4 * + 0 + *(2) 91 == _Bool &&[3139] "
; Fused expression:    "*(2) (@6) >= *ax 0 _Bool [sh&&->3139] *(2) (@6) * *ax 4 + SyntaxStack ax + ax 0 == *ax 91 _Bool &&[3139] "
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 0
    setge   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3139
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, [bx]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 91
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3139:
; JumpIfZero
    test    ax, ax
    jz      L3137
; {
; RPN'ized expression: "ExprTypeSynPtr *u ExprTypeSynPtr *u -u = "
; Expanded expression: "(@6) *(2) (@6) *(2) *(2) -u =(2) "
; Fused expression:    "*(2) (@6) push-ax *(2) (@6) *(2) ax -u =(34) **sp ax "
    mov     ax, [bp+6]
    push    ax
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, [bx]
    neg     ax
    pop     bx
    mov     [bx], ax
; RPN'ized expression: "( 1 , oldIdxRight 1 + oldSpRight sp - - del ) "
; Expanded expression: " 1  (@-8) *(2) 1 + (@-10) *(2) sp *(2) - -  del ()4 "
; Fused expression:    "( 1 , + *(@-8) 1 push-ax - *(@-10) *sp - *sp ax , del )4 "
    push    1
    mov     ax, [bp-8]
    add     ax, 1
    push    ax
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    pop     ax
    sub     ax, cx
    push    ax
    call    _del
    sub     sp, -4
; }
    jmp     L3138
L3137:
; else
; if
; RPN'ized expression: "ExprTypeSynPtr *u 0 >= SyntaxStack ExprTypeSynPtr *u + *u 0 + *u 40 == && "
; Expanded expression: "(@6) *(2) *(2) 0 >= _Bool [sh&&->3142] SyntaxStack (@6) *(2) *(2) 4 * + 0 + *(2) 40 == _Bool &&[3142] "
; Fused expression:    "*(2) (@6) >= *ax 0 _Bool [sh&&->3142] *(2) (@6) * *ax 4 + SyntaxStack ax + ax 0 == *ax 40 _Bool &&[3142] "
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 0
    setge   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3142
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, [bx]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 40
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3142:
; JumpIfZero
    test    ax, ax
    jz      L3140
; {
; RPN'ized expression: "ExprTypeSynPtr *u ExprTypeSynPtr *u -u = "
; Expanded expression: "(@6) *(2) (@6) *(2) *(2) -u =(2) "
; Fused expression:    "*(2) (@6) push-ax *(2) (@6) *(2) ax -u =(34) **sp ax "
    mov     ax, [bp+6]
    push    ax
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, [bx]
    neg     ax
    pop     bx
    mov     [bx], ax
; RPN'ized expression: "( 1 , oldIdxRight 1 + oldSpRight sp - - del ) "
; Expanded expression: " 1  (@-8) *(2) 1 + (@-10) *(2) sp *(2) - -  del ()4 "
; Fused expression:    "( 1 , + *(@-8) 1 push-ax - *(@-10) *sp - *sp ax , del )4 "
    push    1
    mov     ax, [bp-8]
    add     ax, 1
    push    ax
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    pop     ax
    sub     ax, cx
    push    ax
    call    _del
    sub     sp, -4
; }
    jmp     L3141
L3140:
; else
; if
; RPN'ized expression: "ExprTypeSynPtr *u 0 >= oldIdxRight oldSpRight sp - - 0 >= && stack oldIdxRight oldSpRight sp - - + *u 0 + *u 78 == && "
; Expanded expression: "(@6) *(2) *(2) 0 >= _Bool [sh&&->3146] (@-8) *(2) (@-10) *(2) sp *(2) - - 0 >= _Bool &&[3146] _Bool [sh&&->3145] stack (@-8) *(2) (@-10) *(2) sp *(2) - - 4 * + 0 + *(2) 78 == _Bool &&[3145] "
; Fused expression:    "*(2) (@6) >= *ax 0 _Bool [sh&&->3146] - *(@-10) *sp - *(@-8) ax >= ax 0 _Bool &&[3146] _Bool [sh&&->3145] - *(@-10) *sp - *(@-8) ax * ax 4 + stack ax + ax 0 == *ax 78 _Bool &&[3145] "
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 0
    setge   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3146
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    mov     ax, [bp-8]
    sub     ax, cx
    cmp     ax, 0
    setge   al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3146:
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3145
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    mov     ax, [bp-8]
    sub     ax, cx
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 78
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3145:
; JumpIfZero
    test    ax, ax
    jz      L3143
; {
; RPN'ized expression: "ExprTypeSynPtr *u ExprTypeSynPtr *u -u = "
; Expanded expression: "(@6) *(2) (@6) *(2) *(2) -u =(2) "
; Fused expression:    "*(2) (@6) push-ax *(2) (@6) *(2) ax -u =(34) **sp ax "
    mov     ax, [bp+6]
    push    ax
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, [bx]
    neg     ax
    pop     bx
    mov     [bx], ax
; RPN'ized expression: "( 2 , oldIdxRight oldSpRight sp - - del ) "
; Expanded expression: " 2  (@-8) *(2) (@-10) *(2) sp *(2) - -  del ()4 "
; Fused expression:    "( 2 , - *(@-10) *sp - *(@-8) ax , del )4 "
    push    2
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    mov     ax, [bp-8]
    sub     ax, cx
    push    ax
    call    _del
    sub     sp, -4
; }
    jmp     L3144
L3143:
; else
; RPN'ized expression: "( L3147 error ) "
; Expanded expression: " L3147  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3147:
    db  "Error: exprval(): lvalue expected after '&'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3147 , error )2 "
    push    L3147
    call    _error
    sub     sp, -2
L3144:
L3141:
L3138:
; RPN'ized expression: "ConstExpr *u 0 = "
; Expanded expression: "(@8) *(2) 0 =(2) "
; Fused expression:    "*(2) (@8) =(34) *ax 0 "
    mov     ax, [bp+8]
    mov     bx, ax
    mov     ax, 0
    mov     [bx], ax
; break
    jmp     L3100
; case
; RPN'ized expression: "78 "
; Expanded expression: "78 "
; Expression value: 78
    jmp     L3136
L3135:
    cmp     ax, 78
    jne     L3149
L3136:
; RPN'ized expression: "( ConstExpr , ExprTypeSynPtr , idx exprval ) "
; Expanded expression: " (@8) *(2)  (@6) *(2)  (@4) *(2)  exprval ()6 "
; Fused expression:    "( *(2) (@8) , *(2) (@6) , *(2) (@4) , exprval )6 "
    push    word [bp+8]
    push    word [bp+6]
    push    word [bp+4]
    call    _exprval
    sub     sp, -6
; if
; RPN'ized expression: "ExprTypeSynPtr *u 0 < SyntaxStack ExprTypeSynPtr *u + *u 0 + *u 42 == || "
; Expanded expression: "(@6) *(2) *(2) 0 < _Bool [sh||->3153] SyntaxStack (@6) *(2) *(2) 4 * + 0 + *(2) 42 == _Bool ||[3153] "
; Fused expression:    "*(2) (@6) < *ax 0 _Bool [sh||->3153] *(2) (@6) * *ax 4 + SyntaxStack ax + ax 0 == *ax 42 _Bool ||[3153] "
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 0
    setl    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L3153
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, [bx]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 42
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3153:
; JumpIfZero
    test    ax, ax
    jz      L3151
; {
; if
; RPN'ized expression: "ExprTypeSynPtr *u 0 < "
; Expanded expression: "(@6) *(2) *(2) 0 < "
; Fused expression:    "*(2) (@6) < *ax 0 IF! "
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 0
    jge     L3154
; RPN'ized expression: "ExprTypeSynPtr *u ExprTypeSynPtr *u -u = "
; Expanded expression: "(@6) *(2) (@6) *(2) *(2) -u =(2) "
; Fused expression:    "*(2) (@6) push-ax *(2) (@6) *(2) ax -u =(34) **sp ax "
    mov     ax, [bp+6]
    push    ax
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, [bx]
    neg     ax
    pop     bx
    mov     [bx], ax
    jmp     L3155
L3154:
; else
; RPN'ized expression: "ExprTypeSynPtr *u ++ "
; Expanded expression: "(@6) *(2) ++(2) "
; Fused expression:    "*(2) (@6) ++(2) *ax "
    mov     ax, [bp+6]
    mov     bx, ax
    inc     word [bx]
    mov     ax, [bx]
L3155:
; if
; RPN'ized expression: "SyntaxStack ExprTypeSynPtr *u + *u 0 + *u 17 == "
; Expanded expression: "SyntaxStack (@6) *(2) *(2) 4 * + 0 + *(2) 17 == "
; Fused expression:    "*(2) (@6) * *ax 4 + SyntaxStack ax + ax 0 == *ax 17 IF! "
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, [bx]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 17
    jne     L3156
; RPN'ized expression: "( L3158 error ) "
; Expanded expression: " L3158  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3158:
    db  "Error: exprval(): cannot dereference a pointer to 'void'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3158 , error )2 "
    push    L3158
    call    _error
    sub     sp, -2
L3156:
; if
; RPN'ized expression: "SyntaxStack ExprTypeSynPtr *u + *u 0 + *u 91 == "
; Expanded expression: "SyntaxStack (@6) *(2) *(2) 4 * + 0 + *(2) 91 == "
; Fused expression:    "*(2) (@6) * *ax 4 + SyntaxStack ax + ax 0 == *ax 91 IF! "
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, [bx]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 91
    jne     L3160
; RPN'ized expression: "( 1 , oldIdxRight 1 + oldSpRight sp - - del ) "
; Expanded expression: " 1  (@-8) *(2) 1 + (@-10) *(2) sp *(2) - -  del ()4 "
; Fused expression:    "( 1 , + *(@-8) 1 push-ax - *(@-10) *sp - *sp ax , del )4 "
    push    1
    mov     ax, [bp-8]
    add     ax, 1
    push    ax
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    pop     ax
    sub     ax, cx
    push    ax
    call    _del
    sub     sp, -4
L3160:
; if
; RPN'ized expression: "SyntaxStack ExprTypeSynPtr *u + *u 0 + *u 40 == "
; Expanded expression: "SyntaxStack (@6) *(2) *(2) 4 * + 0 + *(2) 40 == "
; Fused expression:    "*(2) (@6) * *ax 4 + SyntaxStack ax + ax 0 == *ax 40 IF! "
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, [bx]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 40
    jne     L3162
; RPN'ized expression: "( 1 , oldIdxRight 1 + oldSpRight sp - - del ) "
; Expanded expression: " 1  (@-8) *(2) 1 + (@-10) *(2) sp *(2) - -  del ()4 "
; Fused expression:    "( 1 , + *(@-8) 1 push-ax - *(@-10) *sp - *sp ax , del )4 "
    push    1
    mov     ax, [bp-8]
    add     ax, 1
    push    ax
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    pop     ax
    sub     ax, cx
    push    ax
    call    _del
    sub     sp, -4
    jmp     L3163
L3162:
; else
; RPN'ized expression: "stack oldIdxRight 1 + oldSpRight sp - - + *u 1 + *u ( ExprTypeSynPtr *u GetDeclSize ) = "
; Expanded expression: "stack (@-8) *(2) 1 + (@-10) *(2) sp *(2) - - 4 * + 2 +  (@6) *(2) *(2)  GetDeclSize ()2 =(2) "
; Fused expression:    "+ *(@-8) 1 push-ax - *(@-10) *sp - *sp ax * ax 4 + stack ax + ax 2 push-ax ( *(2) (@6) *(2) ax , GetDeclSize )2 =(34) **sp ax "
    mov     ax, [bp-8]
    add     ax, 1
    push    ax
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    pop     ax
    sub     ax, cx
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    push    ax
    mov     ax, [bp+6]
    mov     bx, ax
    push    word [bx]
    call    _GetDeclSize
    sub     sp, -2
    pop     bx
    mov     [bx], ax
L3163:
; }
    jmp     L3152
L3151:
; else
; if
; RPN'ized expression: "SyntaxStack ExprTypeSynPtr *u + *u 0 + *u 91 == "
; Expanded expression: "SyntaxStack (@6) *(2) *(2) 4 * + 0 + *(2) 91 == "
; Fused expression:    "*(2) (@6) * *ax 4 + SyntaxStack ax + ax 0 == *ax 91 IF! "
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, [bx]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 91
    jne     L3164
; {
; while
; RPN'ized expression: "SyntaxStack ExprTypeSynPtr *u + *u 0 + *u 93 != "
; Expanded expression: "SyntaxStack (@6) *(2) *(2) 4 * + 0 + *(2) 93 != "
L3166:
; Fused expression:    "*(2) (@6) * *ax 4 + SyntaxStack ax + ax 0 != *ax 93 IF! "
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, [bx]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 93
    je      L3167
; RPN'ized expression: "ExprTypeSynPtr *u ++ "
; Expanded expression: "(@6) *(2) ++(2) "
; Fused expression:    "*(2) (@6) ++(2) *ax "
    mov     ax, [bp+6]
    mov     bx, ax
    inc     word [bx]
    mov     ax, [bx]
    jmp     L3166
L3167:
; RPN'ized expression: "ExprTypeSynPtr *u ++ "
; Expanded expression: "(@6) *(2) ++(2) "
; Fused expression:    "*(2) (@6) ++(2) *ax "
    mov     ax, [bp+6]
    mov     bx, ax
    inc     word [bx]
    mov     ax, [bx]
; if
; RPN'ized expression: "SyntaxStack ExprTypeSynPtr *u + *u 0 + *u 91 == "
; Expanded expression: "SyntaxStack (@6) *(2) *(2) 4 * + 0 + *(2) 91 == "
; Fused expression:    "*(2) (@6) * *ax 4 + SyntaxStack ax + ax 0 == *ax 91 IF! "
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, [bx]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 91
    jne     L3168
; RPN'ized expression: "( 1 , oldIdxRight 1 + oldSpRight sp - - del ) "
; Expanded expression: " 1  (@-8) *(2) 1 + (@-10) *(2) sp *(2) - -  del ()4 "
; Fused expression:    "( 1 , + *(@-8) 1 push-ax - *(@-10) *sp - *sp ax , del )4 "
    push    1
    mov     ax, [bp-8]
    add     ax, 1
    push    ax
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    pop     ax
    sub     ax, cx
    push    ax
    call    _del
    sub     sp, -4
    jmp     L3169
L3168:
; else
; RPN'ized expression: "stack oldIdxRight 1 + oldSpRight sp - - + *u 1 + *u ( ExprTypeSynPtr *u GetDeclSize ) = "
; Expanded expression: "stack (@-8) *(2) 1 + (@-10) *(2) sp *(2) - - 4 * + 2 +  (@6) *(2) *(2)  GetDeclSize ()2 =(2) "
; Fused expression:    "+ *(@-8) 1 push-ax - *(@-10) *sp - *sp ax * ax 4 + stack ax + ax 2 push-ax ( *(2) (@6) *(2) ax , GetDeclSize )2 =(34) **sp ax "
    mov     ax, [bp-8]
    add     ax, 1
    push    ax
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    pop     ax
    sub     ax, cx
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    push    ax
    mov     ax, [bp+6]
    mov     bx, ax
    push    word [bx]
    call    _GetDeclSize
    sub     sp, -2
    pop     bx
    mov     [bx], ax
L3169:
; }
    jmp     L3165
L3164:
; else
; RPN'ized expression: "( L3170 error ) "
; Expanded expression: " L3170  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3170:
    db  "Error: exprval(): pointer/array expected before '*' or '[]'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3170 , error )2 "
    push    L3170
    call    _error
    sub     sp, -2
L3165:
L3152:
; RPN'ized expression: "ConstExpr *u 0 = "
; Expanded expression: "(@8) *(2) 0 =(2) "
; Fused expression:    "*(2) (@8) =(34) *ax 0 "
    mov     ax, [bp+8]
    mov     bx, ax
    mov     ax, 0
    mov     [bx], ax
; break
    jmp     L3100
; case
; RPN'ized expression: "43 "
; Expanded expression: "43 "
; Expression value: 43
    jmp     L3150
L3149:
    cmp     ax, 43
    jne     L3172
L3150:
; case
; RPN'ized expression: "45 "
; Expanded expression: "45 "
; Expression value: 45
    jmp     L3173
L3172:
    cmp     ax, 45
    jne     L3174
L3173:
; {
; loc             ptrmask : (@-16): int
    sub     sp, 2
; loc             oldIdxLeft : (@-18): int
    sub     sp, 2
; loc             oldSpLeft : (@-20): int
    sub     sp, 2
; loc             sl : (@-22): int
    sub     sp, 2
; loc             sr : (@-24): int
    sub     sp, 2
; loc             incSize : (@-26): int
    sub     sp, 2
; RPN'ized expression: "sr ( constExpr 1 + *u &u , RightExprTypeSynPtr &u , idx exprval ) = "
; Expanded expression: "(@-24)  (@-14) 2 +  (@-6)  (@4) *(2)  exprval ()6 =(2) "
; Fused expression:    "( + (@-14) 2 , (@-6) , *(2) (@4) , exprval )6 =(34) *(@-24) ax "
    lea     ax, [bp-14]
    add     ax, 2
    push    ax
    lea     ax, [bp-6]
    push    ax
    push    word [bp+4]
    call    _exprval
    sub     sp, -6
    mov     [bp-24], ax
; RPN'ized expression: "oldIdxLeft idx *u = "
; Expanded expression: "(@-18) (@4) *(2) *(2) =(2) "
; Fused expression:    "*(2) (@4) =(34) *(@-18) *ax "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-18], ax
; RPN'ized expression: "oldSpLeft sp = "
; Expanded expression: "(@-20) sp *(2) =(2) "
; Fused expression:    "=(34) *(@-20) *sp "
    mov     ax, [_sp]
    mov     [bp-20], ax
; RPN'ized expression: "sl ( constExpr 0 + *u &u , ExprTypeSynPtr , idx exprval ) = "
; Expanded expression: "(@-22)  (@-14) 0 +  (@6) *(2)  (@4) *(2)  exprval ()6 =(2) "
; Fused expression:    "( + (@-14) 0 , *(2) (@6) , *(2) (@4) , exprval )6 =(34) *(@-22) ax "
    lea     ax, [bp-14]
    add     ax, 0
    push    ax
    push    word [bp+6]
    push    word [bp+4]
    call    _exprval
    sub     sp, -6
    mov     [bp-22], ax
; RPN'ized expression: "s sl tok 43 == sr * + tok 45 == sr * - = "
; Expanded expression: "(@-4) (@-22) *(2) (@-2) *(2) 43 == (@-24) *(2) * + (@-2) *(2) 45 == (@-24) *(2) * - =(2) "
; Fused expression:    "== *(@-2) 43 * ax *(@-24) + *(@-22) ax push-ax == *(@-2) 45 * ax *(@-24) - *sp ax =(34) *(@-4) ax "
    mov     ax, [bp-2]
    cmp     ax, 43
    sete    al
    cbw
    mul     word [bp-24]
    mov     cx, ax
    mov     ax, [bp-22]
    add     ax, cx
    push    ax
    mov     ax, [bp-2]
    cmp     ax, 45
    sete    al
    cbw
    mul     word [bp-24]
    mov     cx, ax
    pop     ax
    sub     ax, cx
    mov     [bp-4], ax
; RPN'ized expression: "( tok , RightExprTypeSynPtr nonVoidTypeCheck ) "
; Expanded expression: " (@-2) *(2)  (@-6) *(2)  nonVoidTypeCheck ()4 "
; Fused expression:    "( *(2) (@-2) , *(2) (@-6) , nonVoidTypeCheck )4 "
    push    word [bp-2]
    push    word [bp-6]
    call    _nonVoidTypeCheck
    sub     sp, -4
; RPN'ized expression: "( tok , ExprTypeSynPtr *u nonVoidTypeCheck ) "
; Expanded expression: " (@-2) *(2)  (@6) *(2) *(2)  nonVoidTypeCheck ()4 "
; Fused expression:    "( *(2) (@-2) , *(2) (@6) *(2) ax , nonVoidTypeCheck )4 "
    push    word [bp-2]
    mov     ax, [bp+6]
    mov     bx, ax
    push    word [bx]
    call    _nonVoidTypeCheck
    sub     sp, -4
; RPN'ized expression: "( 1 , RightExprTypeSynPtr &u decayArray ) "
; Expanded expression: " 1  (@-6)  decayArray ()4 "
; Fused expression:    "( 1 , (@-6) , decayArray )4 "
    push    1
    lea     ax, [bp-6]
    push    ax
    call    _decayArray
    sub     sp, -4
; RPN'ized expression: "( 1 , ExprTypeSynPtr decayArray ) "
; Expanded expression: " 1  (@6) *(2)  decayArray ()4 "
; Fused expression:    "( 1 , *(2) (@6) , decayArray )4 "
    push    1
    push    word [bp+6]
    call    _decayArray
    sub     sp, -4
; RPN'ized expression: "ptrmask RightExprTypeSynPtr 0 < ExprTypeSynPtr *u 0 < 2 * + = "
; Expanded expression: "(@-16) (@-6) *(2) 0 < (@6) *(2) *(2) 0 < 2 * + =(2) "
; Fused expression:    "< *(@-6) 0 push-ax *(2) (@6) < *ax 0 * ax 2 + *sp ax =(34) *(@-16) ax "
    mov     ax, [bp-6]
    cmp     ax, 0
    setl    al
    cbw
    push    ax
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 0
    setl    al
    cbw
    imul    ax, ax, 2
    mov     cx, ax
    pop     ax
    add     ax, cx
    mov     [bp-16], ax
; if
; RPN'ized expression: "ptrmask 1 == tok 43 == && "
; Expanded expression: "(@-16) *(2) 1 == _Bool [sh&&->3178] (@-2) *(2) 43 == _Bool &&[3178] "
; Fused expression:    "== *(@-16) 1 _Bool [sh&&->3178] == *(@-2) 43 _Bool &&[3178] "
    mov     ax, [bp-16]
    cmp     ax, 1
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3178
    mov     ax, [bp-2]
    cmp     ax, 43
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3178:
; JumpIfZero
    test    ax, ax
    jz      L3176
; {
; RPN'ized expression: "incSize ( RightExprTypeSynPtr -u GetDeclSize ) = "
; Expanded expression: "(@-26)  (@-6) *(2) -u  GetDeclSize ()2 =(2) "
; Fused expression:    "( *(2) (@-6) -u , GetDeclSize )2 =(34) *(@-26) ax "
    mov     ax, [bp-6]
    neg     ax
    push    ax
    call    _GetDeclSize
    sub     sp, -2
    mov     [bp-26], ax
; if
; RPN'ized expression: "constExpr 0 + *u "
; Expanded expression: "(@-14) 0 + *(2) "
; Fused expression:    "+ (@-14) 0 *(2) ax "
    lea     ax, [bp-14]
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
; JumpIfZero
    test    ax, ax
    jz      L3179
; {
; RPN'ized expression: "stack oldIdxLeft oldSpLeft sp - - + *u 1 + *u incSize *= "
; Expanded expression: "stack (@-18) *(2) (@-20) *(2) sp *(2) - - 4 * + 2 + (@-26) *(2) *=(2) "
; Fused expression:    "- *(@-20) *sp - *(@-18) ax * ax 4 + stack ax + ax 2 *=(34) *ax *(@-26) "
    mov     ax, [bp-20]
    sub     ax, [_sp]
    mov     cx, ax
    mov     ax, [bp-18]
    sub     ax, cx
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bx]
    mul     word [bp-26]
    mov     [bx], ax
; RPN'ized expression: "s sl incSize * sr + = "
; Expanded expression: "(@-4) (@-22) *(2) (@-26) *(2) * (@-24) *(2) + =(2) "
; Fused expression:    "* *(@-22) *(@-26) + ax *(@-24) =(34) *(@-4) ax "
    mov     ax, [bp-22]
    mul     word [bp-26]
    add     ax, [bp-24]
    mov     [bp-4], ax
; }
    jmp     L3180
L3179:
; else
; if
; RPN'ized expression: "incSize 1 != "
; Expanded expression: "(@-26) *(2) 1 != "
; Fused expression:    "!= *(@-26) 1 IF! "
    mov     ax, [bp-26]
    cmp     ax, 1
    je      L3181
; {
; RPN'ized expression: "( incSize , 1 , oldIdxLeft 1 + oldSpLeft sp - - ins2 ) "
; Expanded expression: " (@-26) *(2)  1  (@-18) *(2) 1 + (@-20) *(2) sp *(2) - -  ins2 ()6 "
; Fused expression:    "( *(2) (@-26) , 1 , + *(@-18) 1 push-ax - *(@-20) *sp - *sp ax , ins2 )6 "
    push    word [bp-26]
    push    1
    mov     ax, [bp-18]
    add     ax, 1
    push    ax
    mov     ax, [bp-20]
    sub     ax, [_sp]
    mov     cx, ax
    pop     ax
    sub     ax, cx
    push    ax
    call    _ins2
    sub     sp, -6
; RPN'ized expression: "( 42 , oldIdxLeft 1 + oldSpLeft sp - - ins ) "
; Expanded expression: " 42  (@-18) *(2) 1 + (@-20) *(2) sp *(2) - -  ins ()4 "
; Fused expression:    "( 42 , + *(@-18) 1 push-ax - *(@-20) *sp - *sp ax , ins )4 "
    push    42
    mov     ax, [bp-18]
    add     ax, 1
    push    ax
    mov     ax, [bp-20]
    sub     ax, [_sp]
    mov     cx, ax
    pop     ax
    sub     ax, cx
    push    ax
    call    _ins
    sub     sp, -4
; }
L3181:
L3180:
; RPN'ized expression: "ExprTypeSynPtr *u RightExprTypeSynPtr = "
; Expanded expression: "(@6) *(2) (@-6) *(2) =(2) "
; Fused expression:    "*(2) (@6) =(34) *ax *(@-6) "
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, [bp-6]
    mov     [bx], ax
; }
    jmp     L3177
L3176:
; else
; if
; RPN'ized expression: "ptrmask 2 == "
; Expanded expression: "(@-16) *(2) 2 == "
; Fused expression:    "== *(@-16) 2 IF! "
    mov     ax, [bp-16]
    cmp     ax, 2
    jne     L3183
; {
; RPN'ized expression: "incSize ( ExprTypeSynPtr *u -u GetDeclSize ) = "
; Expanded expression: "(@-26)  (@6) *(2) *(2) -u  GetDeclSize ()2 =(2) "
; Fused expression:    "( *(2) (@6) *(2) ax -u , GetDeclSize )2 =(34) *(@-26) ax "
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, [bx]
    neg     ax
    push    ax
    call    _GetDeclSize
    sub     sp, -2
    mov     [bp-26], ax
; if
; RPN'ized expression: "constExpr 1 + *u "
; Expanded expression: "(@-14) 2 + *(2) "
; Fused expression:    "+ (@-14) 2 *(2) ax "
    lea     ax, [bp-14]
    add     ax, 2
    mov     bx, ax
    mov     ax, [bx]
; JumpIfZero
    test    ax, ax
    jz      L3185
; {
; RPN'ized expression: "stack oldIdxRight oldSpRight sp - - + *u 1 + *u incSize *= "
; Expanded expression: "stack (@-8) *(2) (@-10) *(2) sp *(2) - - 4 * + 2 + (@-26) *(2) *=(2) "
; Fused expression:    "- *(@-10) *sp - *(@-8) ax * ax 4 + stack ax + ax 2 *=(34) *ax *(@-26) "
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    mov     ax, [bp-8]
    sub     ax, cx
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bx]
    mul     word [bp-26]
    mov     [bx], ax
; RPN'ized expression: "s sl sr incSize * tok 43 == tok 45 == - * + = "
; Expanded expression: "(@-4) (@-22) *(2) (@-24) *(2) (@-26) *(2) * (@-2) *(2) 43 == (@-2) *(2) 45 == - * + =(2) "
; Fused expression:    "* *(@-24) *(@-26) push-ax == *(@-2) 43 push-ax == *(@-2) 45 - *sp ax * *sp ax + *(@-22) ax =(34) *(@-4) ax "
    mov     ax, [bp-24]
    mul     word [bp-26]
    push    ax
    mov     ax, [bp-2]
    cmp     ax, 43
    sete    al
    cbw
    push    ax
    mov     ax, [bp-2]
    cmp     ax, 45
    sete    al
    cbw
    mov     cx, ax
    pop     ax
    sub     ax, cx
    mov     cx, ax
    pop     ax
    mul     cx
    mov     cx, ax
    mov     ax, [bp-22]
    add     ax, cx
    mov     [bp-4], ax
; }
    jmp     L3186
L3185:
; else
; if
; RPN'ized expression: "incSize 1 != "
; Expanded expression: "(@-26) *(2) 1 != "
; Fused expression:    "!= *(@-26) 1 IF! "
    mov     ax, [bp-26]
    cmp     ax, 1
    je      L3187
; {
; RPN'ized expression: "( incSize , 1 , oldIdxRight 1 + oldSpRight sp - - ins2 ) "
; Expanded expression: " (@-26) *(2)  1  (@-8) *(2) 1 + (@-10) *(2) sp *(2) - -  ins2 ()6 "
; Fused expression:    "( *(2) (@-26) , 1 , + *(@-8) 1 push-ax - *(@-10) *sp - *sp ax , ins2 )6 "
    push    word [bp-26]
    push    1
    mov     ax, [bp-8]
    add     ax, 1
    push    ax
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    pop     ax
    sub     ax, cx
    push    ax
    call    _ins2
    sub     sp, -6
; RPN'ized expression: "( 42 , oldIdxRight 1 + oldSpRight sp - - ins ) "
; Expanded expression: " 42  (@-8) *(2) 1 + (@-10) *(2) sp *(2) - -  ins ()4 "
; Fused expression:    "( 42 , + *(@-8) 1 push-ax - *(@-10) *sp - *sp ax , ins )4 "
    push    42
    mov     ax, [bp-8]
    add     ax, 1
    push    ax
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    pop     ax
    sub     ax, cx
    push    ax
    call    _ins
    sub     sp, -4
; }
L3187:
L3186:
; }
    jmp     L3184
L3183:
; else
; if
; RPN'ized expression: "ptrmask "
; Expanded expression: "(@-16) *(2) "
; Fused expression:    "*(2) (@-16) "
    mov     ax, [bp-16]
; JumpIfZero
    test    ax, ax
    jz      L3189
; RPN'ized expression: "( L3191 error ) "
; Expanded expression: " L3191  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3191:
    db  "Error: exprval(): invalid/unsupported combination of operands for '+' or '-'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3191 , error )2 "
    push    L3191
    call    _error
    sub     sp, -2
L3189:
L3184:
L3177:
; RPN'ized expression: "( ExprTypeSynPtr promoteType ) "
; Expanded expression: " (@6) *(2)  promoteType ()2 "
; Fused expression:    "( *(2) (@6) , promoteType )2 "
    push    word [bp+6]
    call    _promoteType
    sub     sp, -2
; RPN'ized expression: "ConstExpr *u constExpr 0 + *u constExpr 1 + *u && = "
; Expanded expression: "(@8) *(2) (@-14) 0 + *(2) _Bool [sh&&->3193] (@-14) 2 + *(2) _Bool &&[3193] =(2) "
; Fused expression:    "*(2) (@8) push-ax + (@-14) 0 *(2) ax _Bool [sh&&->3193] + (@-14) 2 *(2) ax _Bool &&[3193] =(34) **sp ax "
    mov     ax, [bp+8]
    push    ax
    lea     ax, [bp-14]
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3193
    lea     ax, [bp-14]
    add     ax, 2
    mov     bx, ax
    mov     ax, [bx]
    test    ax, ax
    setnz   al
    cbw
L3193:
    pop     bx
    mov     [bx], ax
; RPN'ized expression: "( idx *u 1 + , oldIdxRight 1 + oldSpRight sp - - , ConstExpr *u , s simplifyConstExpr ) "
; Expanded expression: " (@4) *(2) *(2) 1 +  (@-8) *(2) 1 + (@-10) *(2) sp *(2) - -  (@8) *(2) *(2)  (@-4) *(2)  simplifyConstExpr ()8 "
; Fused expression:    "( *(2) (@4) + *ax 1 , + *(@-8) 1 push-ax - *(@-10) *sp - *sp ax , *(2) (@8) *(2) ax , *(2) (@-4) , simplifyConstExpr )8 "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    add     ax, 1
    push    ax
    mov     ax, [bp-8]
    add     ax, 1
    push    ax
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    pop     ax
    sub     ax, cx
    push    ax
    mov     ax, [bp+8]
    mov     bx, ax
    push    word [bx]
    push    word [bp-4]
    call    _simplifyConstExpr
    sub     sp, -8
    sub     sp, -12
; }
; break
    jmp     L3100
; case
; RPN'ized expression: "12 "
; Expanded expression: "12 "
; Expression value: 12
    jmp     L3175
L3174:
    cmp     ax, 12
    jne     L3194
L3175:
; case
; RPN'ized expression: "13 "
; Expanded expression: "13 "
; Expression value: 13
    jmp     L3195
L3194:
    cmp     ax, 13
    jne     L3196
L3195:
; case
; RPN'ized expression: "81 "
; Expanded expression: "81 "
; Expression value: 81
    jmp     L3197
L3196:
    cmp     ax, 81
    jne     L3198
L3197:
; case
; RPN'ized expression: "82 "
; Expanded expression: "82 "
; Expression value: 82
    jmp     L3199
L3198:
    cmp     ax, 82
    jne     L3200
L3199:
; {
; loc             incSize : (@-16): int
    sub     sp, 2
; =
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "=(34) *(@-16) 1 "
    mov     ax, 1
    mov     [bp-16], ax
; loc             inc : (@-18): int
    sub     sp, 2
; =
; RPN'ized expression: "tok 12 == tok 81 == || "
; Expanded expression: "(@-2) *(2) 12 == _Bool [sh||->3202] (@-2) *(2) 81 == _Bool ||[3202] "
; Fused expression:    "== *(@-2) 12 _Bool [sh||->3202] == *(@-2) 81 _Bool ||[3202] =(34) *(@-18) ax "
    mov     ax, [bp-2]
    cmp     ax, 12
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L3202
    mov     ax, [bp-2]
    cmp     ax, 81
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3202:
    mov     [bp-18], ax
; loc             post : (@-20): int
    sub     sp, 2
; =
; RPN'ized expression: "tok 81 == tok 82 == || "
; Expanded expression: "(@-2) *(2) 81 == _Bool [sh||->3203] (@-2) *(2) 82 == _Bool ||[3203] "
; Fused expression:    "== *(@-2) 81 _Bool [sh||->3203] == *(@-2) 82 _Bool ||[3203] =(34) *(@-20) ax "
    mov     ax, [bp-2]
    cmp     ax, 81
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L3203
    mov     ax, [bp-2]
    cmp     ax, 82
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3203:
    mov     [bp-20], ax
; loc             opSize : (@-22): int
    sub     sp, 2
; RPN'ized expression: "( ConstExpr , ExprTypeSynPtr , idx exprval ) "
; Expanded expression: " (@8) *(2)  (@6) *(2)  (@4) *(2)  exprval ()6 "
; Fused expression:    "( *(2) (@8) , *(2) (@6) , *(2) (@4) , exprval )6 "
    push    word [bp+8]
    push    word [bp+6]
    push    word [bp+4]
    call    _exprval
    sub     sp, -6
; RPN'ized expression: "( tok , ExprTypeSynPtr *u nonVoidTypeCheck ) "
; Expanded expression: " (@-2) *(2)  (@6) *(2) *(2)  nonVoidTypeCheck ()4 "
; Fused expression:    "( *(2) (@-2) , *(2) (@6) *(2) ax , nonVoidTypeCheck )4 "
    push    word [bp-2]
    mov     ax, [bp+6]
    mov     bx, ax
    push    word [bx]
    call    _nonVoidTypeCheck
    sub     sp, -4
; RPN'ized expression: "( 1 , ExprTypeSynPtr decayArray ) "
; Expanded expression: " 1  (@6) *(2)  decayArray ()4 "
; Fused expression:    "( 1 , *(2) (@6) , decayArray )4 "
    push    1
    push    word [bp+6]
    call    _decayArray
    sub     sp, -4
; if
; RPN'ized expression: "oldIdxRight oldSpRight sp - - 0 >= stack oldIdxRight oldSpRight sp - - + *u 0 + *u 78 == && 0 == "
; Expanded expression: "(@-8) *(2) (@-10) *(2) sp *(2) - - 0 >= _Bool [sh&&->3206] stack (@-8) *(2) (@-10) *(2) sp *(2) - - 4 * + 0 + *(2) 78 == _Bool &&[3206] 0 == "
; Fused expression:    "- *(@-10) *sp - *(@-8) ax >= ax 0 _Bool [sh&&->3206] - *(@-10) *sp - *(@-8) ax * ax 4 + stack ax + ax 0 == *ax 78 _Bool &&[3206] == ax 0 IF! "
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    mov     ax, [bp-8]
    sub     ax, cx
    cmp     ax, 0
    setge   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3206
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    mov     ax, [bp-8]
    sub     ax, cx
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 78
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3206:
    cmp     ax, 0
    jne     L3204
; RPN'ized expression: "( L3207 error ) "
; Expanded expression: " L3207  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3207:
    db  "Error: exprval(): lvalue expected for '++' or '--'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3207 , error )2 "
    push    L3207
    call    _error
    sub     sp, -2
L3204:
; RPN'ized expression: "opSize stack oldIdxRight oldSpRight sp - - + *u 1 + *u = "
; Expanded expression: "(@-22) stack (@-8) *(2) (@-10) *(2) sp *(2) - - 4 * + 2 + *(2) =(2) "
; Fused expression:    "- *(@-10) *sp - *(@-8) ax * ax 4 + stack ax + ax 2 =(34) *(@-22) *ax "
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    mov     ax, [bp-8]
    sub     ax, cx
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-22], ax
; RPN'ized expression: "( 1 , oldIdxRight oldSpRight sp - - del ) "
; Expanded expression: " 1  (@-8) *(2) (@-10) *(2) sp *(2) - -  del ()4 "
; Fused expression:    "( 1 , - *(@-10) *sp - *(@-8) ax , del )4 "
    push    1
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    mov     ax, [bp-8]
    sub     ax, cx
    push    ax
    call    _del
    sub     sp, -4
; if
; RPN'ized expression: "ExprTypeSynPtr *u 0 < "
; Expanded expression: "(@6) *(2) *(2) 0 < "
; Fused expression:    "*(2) (@6) < *ax 0 IF! "
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 0
    jge     L3209
; RPN'ized expression: "incSize ( ExprTypeSynPtr *u -u GetDeclSize ) = "
; Expanded expression: "(@-16)  (@6) *(2) *(2) -u  GetDeclSize ()2 =(2) "
; Fused expression:    "( *(2) (@6) *(2) ax -u , GetDeclSize )2 =(34) *(@-16) ax "
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, [bx]
    neg     ax
    push    ax
    call    _GetDeclSize
    sub     sp, -2
    mov     [bp-16], ax
L3209:
; if
; RPN'ized expression: "incSize 1 == "
; Expanded expression: "(@-16) *(2) 1 == "
; Fused expression:    "== *(@-16) 1 IF! "
    mov     ax, [bp-16]
    cmp     ax, 1
    jne     L3211
; {
; RPN'ized expression: "stack oldIdxRight 1 + oldSpRight sp - - + *u 1 + *u opSize = "
; Expanded expression: "stack (@-8) *(2) 1 + (@-10) *(2) sp *(2) - - 4 * + 2 + (@-22) *(2) =(2) "
; Fused expression:    "+ *(@-8) 1 push-ax - *(@-10) *sp - *sp ax * ax 4 + stack ax + ax 2 =(34) *ax *(@-22) "
    mov     ax, [bp-8]
    add     ax, 1
    push    ax
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    pop     ax
    sub     ax, cx
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bp-22]
    mov     [bx], ax
; }
    jmp     L3212
L3211:
; else
; {
; if
; RPN'ized expression: "inc "
; Expanded expression: "(@-18) *(2) "
; Fused expression:    "*(2) (@-18) "
    mov     ax, [bp-18]
; JumpIfZero
    test    ax, ax
    jz      L3213
; {
; if
; RPN'ized expression: "post "
; Expanded expression: "(@-20) *(2) "
; Fused expression:    "*(2) (@-20) "
    mov     ax, [bp-20]
; JumpIfZero
    test    ax, ax
    jz      L3215
; RPN'ized expression: "stack oldIdxRight 1 + oldSpRight sp - - + *u 0 + *u 83 = "
; Expanded expression: "stack (@-8) *(2) 1 + (@-10) *(2) sp *(2) - - 4 * + 0 + 83 =(2) "
; Fused expression:    "+ *(@-8) 1 push-ax - *(@-10) *sp - *sp ax * ax 4 + stack ax + ax 0 =(34) *ax 83 "
    mov     ax, [bp-8]
    add     ax, 1
    push    ax
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    pop     ax
    sub     ax, cx
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, 83
    mov     [bx], ax
    jmp     L3216
L3215:
; else
; RPN'ized expression: "stack oldIdxRight 1 + oldSpRight sp - - + *u 0 + *u 68 = "
; Expanded expression: "stack (@-8) *(2) 1 + (@-10) *(2) sp *(2) - - 4 * + 0 + 68 =(2) "
; Fused expression:    "+ *(@-8) 1 push-ax - *(@-10) *sp - *sp ax * ax 4 + stack ax + ax 0 =(34) *ax 68 "
    mov     ax, [bp-8]
    add     ax, 1
    push    ax
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    pop     ax
    sub     ax, cx
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, 68
    mov     [bx], ax
L3216:
; }
    jmp     L3214
L3213:
; else
; {
; if
; RPN'ized expression: "post "
; Expanded expression: "(@-20) *(2) "
; Fused expression:    "*(2) (@-20) "
    mov     ax, [bp-20]
; JumpIfZero
    test    ax, ax
    jz      L3217
; RPN'ized expression: "stack oldIdxRight 1 + oldSpRight sp - - + *u 0 + *u 84 = "
; Expanded expression: "stack (@-8) *(2) 1 + (@-10) *(2) sp *(2) - - 4 * + 0 + 84 =(2) "
; Fused expression:    "+ *(@-8) 1 push-ax - *(@-10) *sp - *sp ax * ax 4 + stack ax + ax 0 =(34) *ax 84 "
    mov     ax, [bp-8]
    add     ax, 1
    push    ax
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    pop     ax
    sub     ax, cx
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, 84
    mov     [bx], ax
    jmp     L3218
L3217:
; else
; RPN'ized expression: "stack oldIdxRight 1 + oldSpRight sp - - + *u 0 + *u 69 = "
; Expanded expression: "stack (@-8) *(2) 1 + (@-10) *(2) sp *(2) - - 4 * + 0 + 69 =(2) "
; Fused expression:    "+ *(@-8) 1 push-ax - *(@-10) *sp - *sp ax * ax 4 + stack ax + ax 0 =(34) *ax 69 "
    mov     ax, [bp-8]
    add     ax, 1
    push    ax
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    pop     ax
    sub     ax, cx
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, 69
    mov     [bx], ax
L3218:
; }
L3214:
; RPN'ized expression: "stack oldIdxRight 1 + oldSpRight sp - - + *u 1 + *u opSize = "
; Expanded expression: "stack (@-8) *(2) 1 + (@-10) *(2) sp *(2) - - 4 * + 2 + (@-22) *(2) =(2) "
; Fused expression:    "+ *(@-8) 1 push-ax - *(@-10) *sp - *sp ax * ax 4 + stack ax + ax 2 =(34) *ax *(@-22) "
    mov     ax, [bp-8]
    add     ax, 1
    push    ax
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    pop     ax
    sub     ax, cx
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bp-22]
    mov     [bx], ax
; RPN'ized expression: "( incSize , 1 , oldIdxRight 1 + oldSpRight sp - - ins2 ) "
; Expanded expression: " (@-16) *(2)  1  (@-8) *(2) 1 + (@-10) *(2) sp *(2) - -  ins2 ()6 "
; Fused expression:    "( *(2) (@-16) , 1 , + *(@-8) 1 push-ax - *(@-10) *sp - *sp ax , ins2 )6 "
    push    word [bp-16]
    push    1
    mov     ax, [bp-8]
    add     ax, 1
    push    ax
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    pop     ax
    sub     ax, cx
    push    ax
    call    _ins2
    sub     sp, -6
; }
L3212:
; RPN'ized expression: "ConstExpr *u 0 = "
; Expanded expression: "(@8) *(2) 0 =(2) "
; Fused expression:    "*(2) (@8) =(34) *ax 0 "
    mov     ax, [bp+8]
    mov     bx, ax
    mov     ax, 0
    mov     [bx], ax
    sub     sp, -8
; }
; break
    jmp     L3100
; case
; RPN'ized expression: "61 "
; Expanded expression: "61 "
; Expression value: 61
    jmp     L3201
L3200:
    cmp     ax, 61
    jne     L3219
L3201:
; {
; loc             oldIdxLeft : (@-16): int
    sub     sp, 2
; loc             oldSpLeft : (@-18): int
    sub     sp, 2
; loc             opSize : (@-20): int
    sub     sp, 2
; RPN'ized expression: "( ConstExpr , RightExprTypeSynPtr &u , idx exprval ) "
; Expanded expression: " (@8) *(2)  (@-6)  (@4) *(2)  exprval ()6 "
; Fused expression:    "( *(2) (@8) , (@-6) , *(2) (@4) , exprval )6 "
    push    word [bp+8]
    lea     ax, [bp-6]
    push    ax
    push    word [bp+4]
    call    _exprval
    sub     sp, -6
; RPN'ized expression: "oldIdxLeft idx *u = "
; Expanded expression: "(@-16) (@4) *(2) *(2) =(2) "
; Fused expression:    "*(2) (@4) =(34) *(@-16) *ax "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-16], ax
; RPN'ized expression: "oldSpLeft sp = "
; Expanded expression: "(@-18) sp *(2) =(2) "
; Fused expression:    "=(34) *(@-18) *sp "
    mov     ax, [_sp]
    mov     [bp-18], ax
; RPN'ized expression: "( ConstExpr , ExprTypeSynPtr , idx exprval ) "
; Expanded expression: " (@8) *(2)  (@6) *(2)  (@4) *(2)  exprval ()6 "
; Fused expression:    "( *(2) (@8) , *(2) (@6) , *(2) (@4) , exprval )6 "
    push    word [bp+8]
    push    word [bp+6]
    push    word [bp+4]
    call    _exprval
    sub     sp, -6
; RPN'ized expression: "( tok , RightExprTypeSynPtr nonVoidTypeCheck ) "
; Expanded expression: " (@-2) *(2)  (@-6) *(2)  nonVoidTypeCheck ()4 "
; Fused expression:    "( *(2) (@-2) , *(2) (@-6) , nonVoidTypeCheck )4 "
    push    word [bp-2]
    push    word [bp-6]
    call    _nonVoidTypeCheck
    sub     sp, -4
; RPN'ized expression: "( tok , ExprTypeSynPtr *u nonVoidTypeCheck ) "
; Expanded expression: " (@-2) *(2)  (@6) *(2) *(2)  nonVoidTypeCheck ()4 "
; Fused expression:    "( *(2) (@-2) , *(2) (@6) *(2) ax , nonVoidTypeCheck )4 "
    push    word [bp-2]
    mov     ax, [bp+6]
    mov     bx, ax
    push    word [bx]
    call    _nonVoidTypeCheck
    sub     sp, -4
; RPN'ized expression: "( 0 , RightExprTypeSynPtr &u decayArray ) "
; Expanded expression: " 0  (@-6)  decayArray ()4 "
; Fused expression:    "( 0 , (@-6) , decayArray )4 "
    push    0
    lea     ax, [bp-6]
    push    ax
    call    _decayArray
    sub     sp, -4
; RPN'ized expression: "( 0 , ExprTypeSynPtr decayArray ) "
; Expanded expression: " 0  (@6) *(2)  decayArray ()4 "
; Fused expression:    "( 0 , *(2) (@6) , decayArray )4 "
    push    0
    push    word [bp+6]
    call    _decayArray
    sub     sp, -4
; if
; RPN'ized expression: "oldIdxLeft oldSpLeft sp - - 0 >= stack oldIdxLeft oldSpLeft sp - - + *u 0 + *u 78 == && 0 == "
; Expanded expression: "(@-16) *(2) (@-18) *(2) sp *(2) - - 0 >= _Bool [sh&&->3223] stack (@-16) *(2) (@-18) *(2) sp *(2) - - 4 * + 0 + *(2) 78 == _Bool &&[3223] 0 == "
; Fused expression:    "- *(@-18) *sp - *(@-16) ax >= ax 0 _Bool [sh&&->3223] - *(@-18) *sp - *(@-16) ax * ax 4 + stack ax + ax 0 == *ax 78 _Bool &&[3223] == ax 0 IF! "
    mov     ax, [bp-18]
    sub     ax, [_sp]
    mov     cx, ax
    mov     ax, [bp-16]
    sub     ax, cx
    cmp     ax, 0
    setge   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3223
    mov     ax, [bp-18]
    sub     ax, [_sp]
    mov     cx, ax
    mov     ax, [bp-16]
    sub     ax, cx
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 78
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3223:
    cmp     ax, 0
    jne     L3221
; RPN'ized expression: "( L3224 error ) "
; Expanded expression: " L3224  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3224:
    db  "Error: exprval(): lvalue expected before '='",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3224 , error )2 "
    push    L3224
    call    _error
    sub     sp, -2
L3221:
; RPN'ized expression: "opSize stack oldIdxLeft oldSpLeft sp - - + *u 1 + *u = "
; Expanded expression: "(@-20) stack (@-16) *(2) (@-18) *(2) sp *(2) - - 4 * + 2 + *(2) =(2) "
; Fused expression:    "- *(@-18) *sp - *(@-16) ax * ax 4 + stack ax + ax 2 =(34) *(@-20) *ax "
    mov     ax, [bp-18]
    sub     ax, [_sp]
    mov     cx, ax
    mov     ax, [bp-16]
    sub     ax, cx
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-20], ax
; RPN'ized expression: "stack oldIdxRight 1 + oldSpRight sp - - + *u 1 + *u opSize = "
; Expanded expression: "stack (@-8) *(2) 1 + (@-10) *(2) sp *(2) - - 4 * + 2 + (@-20) *(2) =(2) "
; Fused expression:    "+ *(@-8) 1 push-ax - *(@-10) *sp - *sp ax * ax 4 + stack ax + ax 2 =(34) *ax *(@-20) "
    mov     ax, [bp-8]
    add     ax, 1
    push    ax
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    pop     ax
    sub     ax, cx
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bp-20]
    mov     [bx], ax
; RPN'ized expression: "( 1 , oldIdxLeft oldSpLeft sp - - del ) "
; Expanded expression: " 1  (@-16) *(2) (@-18) *(2) sp *(2) - -  del ()4 "
; Fused expression:    "( 1 , - *(@-18) *sp - *(@-16) ax , del )4 "
    push    1
    mov     ax, [bp-18]
    sub     ax, [_sp]
    mov     cx, ax
    mov     ax, [bp-16]
    sub     ax, cx
    push    ax
    call    _del
    sub     sp, -4
; RPN'ized expression: "ConstExpr *u 0 = "
; Expanded expression: "(@8) *(2) 0 =(2) "
; Fused expression:    "*(2) (@8) =(34) *ax 0 "
    mov     ax, [bp+8]
    mov     bx, ax
    mov     ax, 0
    mov     [bx], ax
    sub     sp, -6
; }
; break
    jmp     L3100
; case
; RPN'ized expression: "126 "
; Expanded expression: "126 "
; Expression value: 126
    jmp     L3220
L3219:
    cmp     ax, 126
    jne     L3226
L3220:
; case
; RPN'ized expression: "79 "
; Expanded expression: "79 "
; Expression value: 79
    jmp     L3227
L3226:
    cmp     ax, 79
    jne     L3228
L3227:
; case
; RPN'ized expression: "80 "
; Expanded expression: "80 "
; Expression value: 80
    jmp     L3229
L3228:
    cmp     ax, 80
    jne     L3230
L3229:
; RPN'ized expression: "s ( ConstExpr , ExprTypeSynPtr , idx exprval ) = "
; Expanded expression: "(@-4)  (@8) *(2)  (@6) *(2)  (@4) *(2)  exprval ()6 =(2) "
; Fused expression:    "( *(2) (@8) , *(2) (@6) , *(2) (@4) , exprval )6 =(34) *(@-4) ax "
    push    word [bp+8]
    push    word [bp+6]
    push    word [bp+4]
    call    _exprval
    sub     sp, -6
    mov     [bp-4], ax
; RPN'ized expression: "( tok , ExprTypeSynPtr *u nonVoidTypeCheck ) "
; Expanded expression: " (@-2) *(2)  (@6) *(2) *(2)  nonVoidTypeCheck ()4 "
; Fused expression:    "( *(2) (@-2) , *(2) (@6) *(2) ax , nonVoidTypeCheck )4 "
    push    word [bp-2]
    mov     ax, [bp+6]
    mov     bx, ax
    push    word [bx]
    call    _nonVoidTypeCheck
    sub     sp, -4
; RPN'ized expression: "( tok , ExprTypeSynPtr *u numericTypeCheck ) "
; Expanded expression: " (@-2) *(2)  (@6) *(2) *(2)  numericTypeCheck ()4 "
; Fused expression:    "( *(2) (@-2) , *(2) (@6) *(2) ax , numericTypeCheck )4 "
    push    word [bp-2]
    mov     ax, [bp+6]
    mov     bx, ax
    push    word [bx]
    call    _numericTypeCheck
    sub     sp, -4
; switch
; RPN'ized expression: "tok "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
    mov     ax, [bp-2]
    jmp     L3234
; {
; case
; RPN'ized expression: "126 "
; Expanded expression: "126 "
; Expression value: 126
    jmp     L3235
L3234:
    cmp     ax, 126
    jne     L3236
L3235:
; RPN'ized expression: "s s ~ = "
; Expanded expression: "(@-4) (@-4) *(2) ~ =(2) "
; Fused expression:    "*(2) (@-4) ~ =(34) *(@-4) ax "
    mov     ax, [bp-4]
    not     ax
    mov     [bp-4], ax
; break
    jmp     L3232
; case
; RPN'ized expression: "79 "
; Expanded expression: "79 "
; Expression value: 79
    jmp     L3237
L3236:
    cmp     ax, 79
    jne     L3238
L3237:
; RPN'ized expression: "s s +u = "
; Expanded expression: "(@-4) (@-4) *(2) +u =(2) "
; Fused expression:    "=(34) *(@-4) *(@-4) "
    mov     ax, [bp-4]
    mov     [bp-4], ax
; break
    jmp     L3232
; case
; RPN'ized expression: "80 "
; Expanded expression: "80 "
; Expression value: 80
    jmp     L3239
L3238:
    cmp     ax, 80
    jne     L3240
L3239:
; RPN'ized expression: "s s -u = "
; Expanded expression: "(@-4) (@-4) *(2) -u =(2) "
; Fused expression:    "*(2) (@-4) -u =(34) *(@-4) ax "
    mov     ax, [bp-4]
    neg     ax
    mov     [bp-4], ax
; break
    jmp     L3232
; }
    jmp     L3232
L3240:
L3232:
; RPN'ized expression: "( ExprTypeSynPtr promoteType ) "
; Expanded expression: " (@6) *(2)  promoteType ()2 "
; Fused expression:    "( *(2) (@6) , promoteType )2 "
    push    word [bp+6]
    call    _promoteType
    sub     sp, -2
; RPN'ized expression: "( idx *u 1 + , oldIdxRight 1 + oldSpRight sp - - , ConstExpr *u , s simplifyConstExpr ) "
; Expanded expression: " (@4) *(2) *(2) 1 +  (@-8) *(2) 1 + (@-10) *(2) sp *(2) - -  (@8) *(2) *(2)  (@-4) *(2)  simplifyConstExpr ()8 "
; Fused expression:    "( *(2) (@4) + *ax 1 , + *(@-8) 1 push-ax - *(@-10) *sp - *sp ax , *(2) (@8) *(2) ax , *(2) (@-4) , simplifyConstExpr )8 "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    add     ax, 1
    push    ax
    mov     ax, [bp-8]
    add     ax, 1
    push    ax
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    pop     ax
    sub     ax, cx
    push    ax
    mov     ax, [bp+8]
    mov     bx, ax
    push    word [bx]
    push    word [bp-4]
    call    _simplifyConstExpr
    sub     sp, -8
; break
    jmp     L3100
; case
; RPN'ized expression: "42 "
; Expanded expression: "42 "
; Expression value: 42
    jmp     L3231
L3230:
    cmp     ax, 42
    jne     L3242
L3231:
; case
; RPN'ized expression: "47 "
; Expanded expression: "47 "
; Expression value: 47
    jmp     L3243
L3242:
    cmp     ax, 47
    jne     L3244
L3243:
; case
; RPN'ized expression: "37 "
; Expanded expression: "37 "
; Expression value: 37
    jmp     L3245
L3244:
    cmp     ax, 37
    jne     L3246
L3245:
; case
; RPN'ized expression: "4 "
; Expanded expression: "4 "
; Expression value: 4
    jmp     L3247
L3246:
    cmp     ax, 4
    jne     L3248
L3247:
; case
; RPN'ized expression: "5 "
; Expanded expression: "5 "
; Expression value: 5
    jmp     L3249
L3248:
    cmp     ax, 5
    jne     L3250
L3249:
; case
; RPN'ized expression: "38 "
; Expanded expression: "38 "
; Expression value: 38
    jmp     L3251
L3250:
    cmp     ax, 38
    jne     L3252
L3251:
; case
; RPN'ized expression: "94 "
; Expanded expression: "94 "
; Expression value: 94
    jmp     L3253
L3252:
    cmp     ax, 94
    jne     L3254
L3253:
; case
; RPN'ized expression: "124 "
; Expanded expression: "124 "
; Expression value: 124
    jmp     L3255
L3254:
    cmp     ax, 124
    jne     L3256
L3255:
; {
; loc             oldIdxLeft : (@-16): int
    sub     sp, 2
; loc             oldSpLeft : (@-18): int
    sub     sp, 2
; loc             sr : (@-20): int
    sub     sp, 2
; loc             sl : (@-22): int
    sub     sp, 2
; RPN'ized expression: "sr ( constExpr 1 + *u &u , RightExprTypeSynPtr &u , idx exprval ) = "
; Expanded expression: "(@-20)  (@-14) 2 +  (@-6)  (@4) *(2)  exprval ()6 =(2) "
; Fused expression:    "( + (@-14) 2 , (@-6) , *(2) (@4) , exprval )6 =(34) *(@-20) ax "
    lea     ax, [bp-14]
    add     ax, 2
    push    ax
    lea     ax, [bp-6]
    push    ax
    push    word [bp+4]
    call    _exprval
    sub     sp, -6
    mov     [bp-20], ax
; RPN'ized expression: "oldIdxLeft idx *u = "
; Expanded expression: "(@-16) (@4) *(2) *(2) =(2) "
; Fused expression:    "*(2) (@4) =(34) *(@-16) *ax "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-16], ax
; RPN'ized expression: "oldSpLeft sp = "
; Expanded expression: "(@-18) sp *(2) =(2) "
; Fused expression:    "=(34) *(@-18) *sp "
    mov     ax, [_sp]
    mov     [bp-18], ax
; RPN'ized expression: "sl ( constExpr 0 + *u &u , ExprTypeSynPtr , idx exprval ) = "
; Expanded expression: "(@-22)  (@-14) 0 +  (@6) *(2)  (@4) *(2)  exprval ()6 =(2) "
; Fused expression:    "( + (@-14) 0 , *(2) (@6) , *(2) (@4) , exprval )6 =(34) *(@-22) ax "
    lea     ax, [bp-14]
    add     ax, 0
    push    ax
    push    word [bp+6]
    push    word [bp+4]
    call    _exprval
    sub     sp, -6
    mov     [bp-22], ax
; RPN'ized expression: "( tok , RightExprTypeSynPtr nonVoidTypeCheck ) "
; Expanded expression: " (@-2) *(2)  (@-6) *(2)  nonVoidTypeCheck ()4 "
; Fused expression:    "( *(2) (@-2) , *(2) (@-6) , nonVoidTypeCheck )4 "
    push    word [bp-2]
    push    word [bp-6]
    call    _nonVoidTypeCheck
    sub     sp, -4
; RPN'ized expression: "( tok , ExprTypeSynPtr *u nonVoidTypeCheck ) "
; Expanded expression: " (@-2) *(2)  (@6) *(2) *(2)  nonVoidTypeCheck ()4 "
; Fused expression:    "( *(2) (@-2) , *(2) (@6) *(2) ax , nonVoidTypeCheck )4 "
    push    word [bp-2]
    mov     ax, [bp+6]
    mov     bx, ax
    push    word [bx]
    call    _nonVoidTypeCheck
    sub     sp, -4
; RPN'ized expression: "( tok , RightExprTypeSynPtr numericTypeCheck ) "
; Expanded expression: " (@-2) *(2)  (@-6) *(2)  numericTypeCheck ()4 "
; Fused expression:    "( *(2) (@-2) , *(2) (@-6) , numericTypeCheck )4 "
    push    word [bp-2]
    push    word [bp-6]
    call    _numericTypeCheck
    sub     sp, -4
; RPN'ized expression: "( tok , ExprTypeSynPtr *u numericTypeCheck ) "
; Expanded expression: " (@-2) *(2)  (@6) *(2) *(2)  numericTypeCheck ()4 "
; Fused expression:    "( *(2) (@-2) , *(2) (@6) *(2) ax , numericTypeCheck )4 "
    push    word [bp-2]
    mov     ax, [bp+6]
    mov     bx, ax
    push    word [bx]
    call    _numericTypeCheck
    sub     sp, -4
; RPN'ized expression: "ConstExpr *u constExpr 0 + *u constExpr 1 + *u && = "
; Expanded expression: "(@8) *(2) (@-14) 0 + *(2) _Bool [sh&&->3258] (@-14) 2 + *(2) _Bool &&[3258] =(2) "
; Fused expression:    "*(2) (@8) push-ax + (@-14) 0 *(2) ax _Bool [sh&&->3258] + (@-14) 2 *(2) ax _Bool &&[3258] =(34) **sp ax "
    mov     ax, [bp+8]
    push    ax
    lea     ax, [bp-14]
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3258
    lea     ax, [bp-14]
    add     ax, 2
    mov     bx, ax
    mov     ax, [bx]
    test    ax, ax
    setnz   al
    cbw
L3258:
    pop     bx
    mov     [bx], ax
; switch
; RPN'ized expression: "tok "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
    mov     ax, [bp-2]
    jmp     L3261
; {
; case
; RPN'ized expression: "47 "
; Expanded expression: "47 "
; Expression value: 47
    jmp     L3262
L3261:
    cmp     ax, 47
    jne     L3263
L3262:
; if
; RPN'ized expression: "ConstExpr *u "
; Expanded expression: "(@8) *(2) *(2) "
; Fused expression:    "*(2) (@8) *(2) ax "
    mov     ax, [bp+8]
    mov     bx, ax
    mov     ax, [bx]
; JumpIfZero
    test    ax, ax
    jz      L3265
; {
; if
; RPN'ized expression: "sr 0 == 32767 -u 32767 -u 1 - != sl 32767 -u 1 - == && sr 1 -u == && || "
; Expanded expression: "(@-20) *(2) 0 == _Bool [sh||->3269] 1 [sh&&->3271] (@-22) *(2) -32768 == _Bool &&[3271] _Bool [sh&&->3270] (@-20) *(2) -1 == _Bool &&[3270] _Bool ||[3269] "
; Fused expression:    "== *(@-20) 0 _Bool [sh||->3269] 1 [sh&&->3271] == *(@-22) -32768 _Bool &&[3271] _Bool [sh&&->3270] == *(@-20) -1 _Bool &&[3270] _Bool ||[3269] "
    mov     ax, [bp-20]
    cmp     ax, 0
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L3269
    mov     ax, 1
; JumpIfZero
    test    ax, ax
    jz      L3271
    mov     ax, [bp-22]
    cmp     ax, -32768
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3271:
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3270
    mov     ax, [bp-20]
    cmp     ax, -1
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3270:
    test    ax, ax
    setnz   al
    cbw
L3269:
; JumpIfZero
    test    ax, ax
    jz      L3267
; RPN'ized expression: "( L3272 error ) "
; Expanded expression: " L3272  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3272:
    db  "Error: exprval(): division overflow",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3272 , error )2 "
    push    L3272
    call    _error
    sub     sp, -2
L3267:
; RPN'ized expression: "sl sr /= "
; Expanded expression: "(@-22) (@-20) *(2) /=(2) "
; Fused expression:    "/=(34) *(@-22) *(@-20) "
    mov     ax, [bp-22]
    cwd
    idiv    word [bp-20]
    mov     [bp-22], ax
; }
L3265:
; break
    jmp     L3259
; case
; RPN'ized expression: "37 "
; Expanded expression: "37 "
; Expression value: 37
    jmp     L3264
L3263:
    cmp     ax, 37
    jne     L3274
L3264:
; if
; RPN'ized expression: "ConstExpr *u "
; Expanded expression: "(@8) *(2) *(2) "
; Fused expression:    "*(2) (@8) *(2) ax "
    mov     ax, [bp+8]
    mov     bx, ax
    mov     ax, [bx]
; JumpIfZero
    test    ax, ax
    jz      L3276
; {
; if
; RPN'ized expression: "sr 0 == 32767 -u 32767 -u 1 - != sl 32767 -u 1 - == && sr 1 -u == && || "
; Expanded expression: "(@-20) *(2) 0 == _Bool [sh||->3280] 1 [sh&&->3282] (@-22) *(2) -32768 == _Bool &&[3282] _Bool [sh&&->3281] (@-20) *(2) -1 == _Bool &&[3281] _Bool ||[3280] "
; Fused expression:    "== *(@-20) 0 _Bool [sh||->3280] 1 [sh&&->3282] == *(@-22) -32768 _Bool &&[3282] _Bool [sh&&->3281] == *(@-20) -1 _Bool &&[3281] _Bool ||[3280] "
    mov     ax, [bp-20]
    cmp     ax, 0
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L3280
    mov     ax, 1
; JumpIfZero
    test    ax, ax
    jz      L3282
    mov     ax, [bp-22]
    cmp     ax, -32768
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3282:
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3281
    mov     ax, [bp-20]
    cmp     ax, -1
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3281:
    test    ax, ax
    setnz   al
    cbw
L3280:
; JumpIfZero
    test    ax, ax
    jz      L3278
; RPN'ized expression: "( L3283 error ) "
; Expanded expression: " L3283  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3283:
    db  "Error: exprval(): division overflow",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3283 , error )2 "
    push    L3283
    call    _error
    sub     sp, -2
L3278:
; RPN'ized expression: "sl sr %= "
; Expanded expression: "(@-22) (@-20) *(2) %=(2) "
; Fused expression:    "%=(34) *(@-22) *(@-20) "
    mov     ax, [bp-22]
    cwd
    idiv    word [bp-20]
    mov     ax, dx
    mov     [bp-22], ax
; }
L3276:
; break
    jmp     L3259
; case
; RPN'ized expression: "42 "
; Expanded expression: "42 "
; Expression value: 42
    jmp     L3275
L3274:
    cmp     ax, 42
    jne     L3285
L3275:
; RPN'ized expression: "sl sr *= "
; Expanded expression: "(@-22) (@-20) *(2) *=(2) "
; Fused expression:    "*=(34) *(@-22) *(@-20) "
    mov     ax, [bp-22]
    mul     word [bp-20]
    mov     [bp-22], ax
; break
    jmp     L3259
; case
; RPN'ized expression: "4 "
; Expanded expression: "4 "
; Expression value: 4
    jmp     L3286
L3285:
    cmp     ax, 4
    jne     L3287
L3286:
; RPN'ized expression: "sl sr <<= "
; Expanded expression: "(@-22) (@-20) *(2) <<=(2) "
; Fused expression:    "<<=(34) *(@-22) *(@-20) "
    mov     ax, [bp-22]
    mov     cl, [bp-20]
    shl     ax, cl
    mov     [bp-22], ax
; break
    jmp     L3259
; case
; RPN'ized expression: "5 "
; Expanded expression: "5 "
; Expression value: 5
    jmp     L3288
L3287:
    cmp     ax, 5
    jne     L3289
L3288:
; RPN'ized expression: "sl sr >>= "
; Expanded expression: "(@-22) (@-20) *(2) >>=(2) "
; Fused expression:    ">>=(34) *(@-22) *(@-20) "
    mov     ax, [bp-22]
    mov     cl, [bp-20]
    sar     ax, cl
    mov     [bp-22], ax
; break
    jmp     L3259
; case
; RPN'ized expression: "38 "
; Expanded expression: "38 "
; Expression value: 38
    jmp     L3290
L3289:
    cmp     ax, 38
    jne     L3291
L3290:
; RPN'ized expression: "sl sr &= "
; Expanded expression: "(@-22) (@-20) *(2) &=(2) "
; Fused expression:    "&=(34) *(@-22) *(@-20) "
    mov     ax, [bp-22]
    and     ax, [bp-20]
    mov     [bp-22], ax
; break
    jmp     L3259
; case
; RPN'ized expression: "94 "
; Expanded expression: "94 "
; Expression value: 94
    jmp     L3292
L3291:
    cmp     ax, 94
    jne     L3293
L3292:
; RPN'ized expression: "sl sr ^= "
; Expanded expression: "(@-22) (@-20) *(2) ^=(2) "
; Fused expression:    "^=(34) *(@-22) *(@-20) "
    mov     ax, [bp-22]
    xor     ax, [bp-20]
    mov     [bp-22], ax
; break
    jmp     L3259
; case
; RPN'ized expression: "124 "
; Expanded expression: "124 "
; Expression value: 124
    jmp     L3294
L3293:
    cmp     ax, 124
    jne     L3295
L3294:
; RPN'ized expression: "sl sr |= "
; Expanded expression: "(@-22) (@-20) *(2) |=(2) "
; Fused expression:    "|=(34) *(@-22) *(@-20) "
    mov     ax, [bp-22]
    or      ax, [bp-20]
    mov     [bp-22], ax
; break
    jmp     L3259
; }
    jmp     L3259
L3295:
L3259:
; RPN'ized expression: "s sl = "
; Expanded expression: "(@-4) (@-22) *(2) =(2) "
; Fused expression:    "=(34) *(@-4) *(@-22) "
    mov     ax, [bp-22]
    mov     [bp-4], ax
; RPN'ized expression: "( ExprTypeSynPtr promoteType ) "
; Expanded expression: " (@6) *(2)  promoteType ()2 "
; Fused expression:    "( *(2) (@6) , promoteType )2 "
    push    word [bp+6]
    call    _promoteType
    sub     sp, -2
; RPN'ized expression: "( idx *u 1 + , oldIdxRight 1 + oldSpRight sp - - , ConstExpr *u , s simplifyConstExpr ) "
; Expanded expression: " (@4) *(2) *(2) 1 +  (@-8) *(2) 1 + (@-10) *(2) sp *(2) - -  (@8) *(2) *(2)  (@-4) *(2)  simplifyConstExpr ()8 "
; Fused expression:    "( *(2) (@4) + *ax 1 , + *(@-8) 1 push-ax - *(@-10) *sp - *sp ax , *(2) (@8) *(2) ax , *(2) (@-4) , simplifyConstExpr )8 "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    add     ax, 1
    push    ax
    mov     ax, [bp-8]
    add     ax, 1
    push    ax
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    pop     ax
    sub     ax, cx
    push    ax
    mov     ax, [bp+8]
    mov     bx, ax
    push    word [bx]
    push    word [bp-4]
    call    _simplifyConstExpr
    sub     sp, -8
    sub     sp, -8
; }
; break
    jmp     L3100
; case
; RPN'ized expression: "60 "
; Expanded expression: "60 "
; Expression value: 60
    jmp     L3257
L3256:
    cmp     ax, 60
    jne     L3297
L3257:
; case
; RPN'ized expression: "62 "
; Expanded expression: "62 "
; Expression value: 62
    jmp     L3298
L3297:
    cmp     ax, 62
    jne     L3299
L3298:
; case
; RPN'ized expression: "10 "
; Expanded expression: "10 "
; Expression value: 10
    jmp     L3300
L3299:
    cmp     ax, 10
    jne     L3301
L3300:
; case
; RPN'ized expression: "11 "
; Expanded expression: "11 "
; Expression value: 11
    jmp     L3302
L3301:
    cmp     ax, 11
    jne     L3303
L3302:
; case
; RPN'ized expression: "8 "
; Expanded expression: "8 "
; Expression value: 8
    jmp     L3304
L3303:
    cmp     ax, 8
    jne     L3305
L3304:
; case
; RPN'ized expression: "9 "
; Expanded expression: "9 "
; Expression value: 9
    jmp     L3306
L3305:
    cmp     ax, 9
    jne     L3307
L3306:
; {
; loc             ptrmask : (@-16): int
    sub     sp, 2
; loc             oldIdxLeft : (@-18): int
    sub     sp, 2
; loc             oldSpLeft : (@-20): int
    sub     sp, 2
; loc             sr : (@-22): int
    sub     sp, 2
; loc             sl : (@-24): int
    sub     sp, 2
; RPN'ized expression: "sr ( constExpr 1 + *u &u , RightExprTypeSynPtr &u , idx exprval ) = "
; Expanded expression: "(@-22)  (@-14) 2 +  (@-6)  (@4) *(2)  exprval ()6 =(2) "
; Fused expression:    "( + (@-14) 2 , (@-6) , *(2) (@4) , exprval )6 =(34) *(@-22) ax "
    lea     ax, [bp-14]
    add     ax, 2
    push    ax
    lea     ax, [bp-6]
    push    ax
    push    word [bp+4]
    call    _exprval
    sub     sp, -6
    mov     [bp-22], ax
; RPN'ized expression: "oldIdxLeft idx *u = "
; Expanded expression: "(@-18) (@4) *(2) *(2) =(2) "
; Fused expression:    "*(2) (@4) =(34) *(@-18) *ax "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-18], ax
; RPN'ized expression: "oldSpLeft sp = "
; Expanded expression: "(@-20) sp *(2) =(2) "
; Fused expression:    "=(34) *(@-20) *sp "
    mov     ax, [_sp]
    mov     [bp-20], ax
; RPN'ized expression: "sl ( constExpr 0 + *u &u , ExprTypeSynPtr , idx exprval ) = "
; Expanded expression: "(@-24)  (@-14) 0 +  (@6) *(2)  (@4) *(2)  exprval ()6 =(2) "
; Fused expression:    "( + (@-14) 0 , *(2) (@6) , *(2) (@4) , exprval )6 =(34) *(@-24) ax "
    lea     ax, [bp-14]
    add     ax, 0
    push    ax
    push    word [bp+6]
    push    word [bp+4]
    call    _exprval
    sub     sp, -6
    mov     [bp-24], ax
; RPN'ized expression: "( tok , RightExprTypeSynPtr nonVoidTypeCheck ) "
; Expanded expression: " (@-2) *(2)  (@-6) *(2)  nonVoidTypeCheck ()4 "
; Fused expression:    "( *(2) (@-2) , *(2) (@-6) , nonVoidTypeCheck )4 "
    push    word [bp-2]
    push    word [bp-6]
    call    _nonVoidTypeCheck
    sub     sp, -4
; RPN'ized expression: "( tok , ExprTypeSynPtr *u nonVoidTypeCheck ) "
; Expanded expression: " (@-2) *(2)  (@6) *(2) *(2)  nonVoidTypeCheck ()4 "
; Fused expression:    "( *(2) (@-2) , *(2) (@6) *(2) ax , nonVoidTypeCheck )4 "
    push    word [bp-2]
    mov     ax, [bp+6]
    mov     bx, ax
    push    word [bx]
    call    _nonVoidTypeCheck
    sub     sp, -4
; RPN'ized expression: "( 0 , RightExprTypeSynPtr &u decayArray ) "
; Expanded expression: " 0  (@-6)  decayArray ()4 "
; Fused expression:    "( 0 , (@-6) , decayArray )4 "
    push    0
    lea     ax, [bp-6]
    push    ax
    call    _decayArray
    sub     sp, -4
; RPN'ized expression: "( 0 , ExprTypeSynPtr decayArray ) "
; Expanded expression: " 0  (@6) *(2)  decayArray ()4 "
; Fused expression:    "( 0 , *(2) (@6) , decayArray )4 "
    push    0
    push    word [bp+6]
    call    _decayArray
    sub     sp, -4
; RPN'ized expression: "ptrmask RightExprTypeSynPtr 0 < ExprTypeSynPtr *u 0 < 2 * + = "
; Expanded expression: "(@-16) (@-6) *(2) 0 < (@6) *(2) *(2) 0 < 2 * + =(2) "
; Fused expression:    "< *(@-6) 0 push-ax *(2) (@6) < *ax 0 * ax 2 + *sp ax =(34) *(@-16) ax "
    mov     ax, [bp-6]
    cmp     ax, 0
    setl    al
    cbw
    push    ax
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 0
    setl    al
    cbw
    imul    ax, ax, 2
    mov     cx, ax
    pop     ax
    add     ax, cx
    mov     [bp-16], ax
; if
; RPN'ized expression: "ptrmask 1 >= ptrmask 2 <= && tok 8 != && tok 9 != && "
; Expanded expression: "(@-16) *(2) 1 >= _Bool [sh&&->3313] (@-16) *(2) 2 <= _Bool &&[3313] _Bool [sh&&->3312] (@-2) *(2) 8 != _Bool &&[3312] _Bool [sh&&->3311] (@-2) *(2) 9 != _Bool &&[3311] "
; Fused expression:    ">= *(@-16) 1 _Bool [sh&&->3313] <= *(@-16) 2 _Bool &&[3313] _Bool [sh&&->3312] != *(@-2) 8 _Bool &&[3312] _Bool [sh&&->3311] != *(@-2) 9 _Bool &&[3311] "
    mov     ax, [bp-16]
    cmp     ax, 1
    setge   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3313
    mov     ax, [bp-16]
    cmp     ax, 2
    setle   al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3313:
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3312
    mov     ax, [bp-2]
    cmp     ax, 8
    setne   al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3312:
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3311
    mov     ax, [bp-2]
    cmp     ax, 9
    setne   al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3311:
; JumpIfZero
    test    ax, ax
    jz      L3309
; RPN'ized expression: "( L3314 error ) "
; Expanded expression: " L3314  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3314:
    db  "Error: exprval(): invalid/unsupported combination of compared operands",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3314 , error )2 "
    push    L3314
    call    _error
    sub     sp, -2
L3309:
; if
; RPN'ized expression: "ptrmask "
; Expanded expression: "(@-16) *(2) "
; Fused expression:    "*(2) (@-16) "
    mov     ax, [bp-16]
; JumpIfZero
    test    ax, ax
    jz      L3316
; {
; loc                 t : (@-26): int
    sub     sp, 2
; =
; RPN'ized expression: "tok "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "=(34) *(@-26) *(@-2) "
    mov     ax, [bp-2]
    mov     [bp-26], ax
; switch
; RPN'ized expression: "tok "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
    mov     ax, [bp-2]
    jmp     L3320
; {
; case
; RPN'ized expression: "60 "
; Expanded expression: "60 "
; Expression value: 60
    jmp     L3321
L3320:
    cmp     ax, 60
    jne     L3322
L3321:
; RPN'ized expression: "t 85 = "
; Expanded expression: "(@-26) 85 =(2) "
; Fused expression:    "=(34) *(@-26) 85 "
    mov     ax, 85
    mov     [bp-26], ax
; break
    jmp     L3318
; case
; RPN'ized expression: "62 "
; Expanded expression: "62 "
; Expression value: 62
    jmp     L3323
L3322:
    cmp     ax, 62
    jne     L3324
L3323:
; RPN'ized expression: "t 86 = "
; Expanded expression: "(@-26) 86 =(2) "
; Fused expression:    "=(34) *(@-26) 86 "
    mov     ax, 86
    mov     [bp-26], ax
; break
    jmp     L3318
; case
; RPN'ized expression: "10 "
; Expanded expression: "10 "
; Expression value: 10
    jmp     L3325
L3324:
    cmp     ax, 10
    jne     L3326
L3325:
; RPN'ized expression: "t 87 = "
; Expanded expression: "(@-26) 87 =(2) "
; Fused expression:    "=(34) *(@-26) 87 "
    mov     ax, 87
    mov     [bp-26], ax
; break
    jmp     L3318
; case
; RPN'ized expression: "11 "
; Expanded expression: "11 "
; Expression value: 11
    jmp     L3327
L3326:
    cmp     ax, 11
    jne     L3328
L3327:
; RPN'ized expression: "t 88 = "
; Expanded expression: "(@-26) 88 =(2) "
; Fused expression:    "=(34) *(@-26) 88 "
    mov     ax, 88
    mov     [bp-26], ax
; break
    jmp     L3318
; }
    jmp     L3318
L3328:
L3318:
; if
; RPN'ized expression: "t tok != "
; Expanded expression: "(@-26) *(2) (@-2) *(2) != "
; Fused expression:    "!= *(@-26) *(@-2) IF! "
    mov     ax, [bp-26]
    cmp     ax, [bp-2]
    je      L3330
; RPN'ized expression: "stack oldIdxRight 1 + oldSpRight sp - - + *u 0 + *u t = "
; Expanded expression: "stack (@-8) *(2) 1 + (@-10) *(2) sp *(2) - - 4 * + 0 + (@-26) *(2) =(2) "
; Fused expression:    "+ *(@-8) 1 push-ax - *(@-10) *sp - *sp ax * ax 4 + stack ax + ax 0 =(34) *ax *(@-26) "
    mov     ax, [bp-8]
    add     ax, 1
    push    ax
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    pop     ax
    sub     ax, cx
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bp-26]
    mov     [bx], ax
L3330:
    sub     sp, -2
; }
L3316:
; switch
; RPN'ized expression: "tok "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
    mov     ax, [bp-2]
    jmp     L3334
; {
; case
; RPN'ized expression: "60 "
; Expanded expression: "60 "
; Expression value: 60
    jmp     L3335
L3334:
    cmp     ax, 60
    jne     L3336
L3335:
; RPN'ized expression: "sl sl sr < = "
; Expanded expression: "(@-24) (@-24) *(2) (@-22) *(2) < =(2) "
; Fused expression:    "< *(@-24) *(@-22) =(34) *(@-24) ax "
    mov     ax, [bp-24]
    cmp     ax, [bp-22]
    setl    al
    cbw
    mov     [bp-24], ax
; break
    jmp     L3332
; case
; RPN'ized expression: "62 "
; Expanded expression: "62 "
; Expression value: 62
    jmp     L3337
L3336:
    cmp     ax, 62
    jne     L3338
L3337:
; RPN'ized expression: "sl sl sr > = "
; Expanded expression: "(@-24) (@-24) *(2) (@-22) *(2) > =(2) "
; Fused expression:    "> *(@-24) *(@-22) =(34) *(@-24) ax "
    mov     ax, [bp-24]
    cmp     ax, [bp-22]
    setg    al
    cbw
    mov     [bp-24], ax
; break
    jmp     L3332
; case
; RPN'ized expression: "10 "
; Expanded expression: "10 "
; Expression value: 10
    jmp     L3339
L3338:
    cmp     ax, 10
    jne     L3340
L3339:
; RPN'ized expression: "sl sl sr <= = "
; Expanded expression: "(@-24) (@-24) *(2) (@-22) *(2) <= =(2) "
; Fused expression:    "<= *(@-24) *(@-22) =(34) *(@-24) ax "
    mov     ax, [bp-24]
    cmp     ax, [bp-22]
    setle   al
    cbw
    mov     [bp-24], ax
; break
    jmp     L3332
; case
; RPN'ized expression: "11 "
; Expanded expression: "11 "
; Expression value: 11
    jmp     L3341
L3340:
    cmp     ax, 11
    jne     L3342
L3341:
; RPN'ized expression: "sl sl sr >= = "
; Expanded expression: "(@-24) (@-24) *(2) (@-22) *(2) >= =(2) "
; Fused expression:    ">= *(@-24) *(@-22) =(34) *(@-24) ax "
    mov     ax, [bp-24]
    cmp     ax, [bp-22]
    setge   al
    cbw
    mov     [bp-24], ax
; break
    jmp     L3332
; case
; RPN'ized expression: "8 "
; Expanded expression: "8 "
; Expression value: 8
    jmp     L3343
L3342:
    cmp     ax, 8
    jne     L3344
L3343:
; RPN'ized expression: "sl sl sr == = "
; Expanded expression: "(@-24) (@-24) *(2) (@-22) *(2) == =(2) "
; Fused expression:    "== *(@-24) *(@-22) =(34) *(@-24) ax "
    mov     ax, [bp-24]
    cmp     ax, [bp-22]
    sete    al
    cbw
    mov     [bp-24], ax
; break
    jmp     L3332
; case
; RPN'ized expression: "9 "
; Expanded expression: "9 "
; Expression value: 9
    jmp     L3345
L3344:
    cmp     ax, 9
    jne     L3346
L3345:
; RPN'ized expression: "sl sl sr != = "
; Expanded expression: "(@-24) (@-24) *(2) (@-22) *(2) != =(2) "
; Fused expression:    "!= *(@-24) *(@-22) =(34) *(@-24) ax "
    mov     ax, [bp-24]
    cmp     ax, [bp-22]
    setne   al
    cbw
    mov     [bp-24], ax
; break
    jmp     L3332
; }
    jmp     L3332
L3346:
L3332:
; RPN'ized expression: "s sl = "
; Expanded expression: "(@-4) (@-24) *(2) =(2) "
; Fused expression:    "=(34) *(@-4) *(@-24) "
    mov     ax, [bp-24]
    mov     [bp-4], ax
; RPN'ized expression: "ExprTypeSynPtr *u 1 = "
; Expanded expression: "(@6) *(2) 1 =(2) "
; Fused expression:    "*(2) (@6) =(34) *ax 1 "
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, 1
    mov     [bx], ax
; RPN'ized expression: "ConstExpr *u constExpr 0 + *u constExpr 1 + *u && = "
; Expanded expression: "(@8) *(2) (@-14) 0 + *(2) _Bool [sh&&->3348] (@-14) 2 + *(2) _Bool &&[3348] =(2) "
; Fused expression:    "*(2) (@8) push-ax + (@-14) 0 *(2) ax _Bool [sh&&->3348] + (@-14) 2 *(2) ax _Bool &&[3348] =(34) **sp ax "
    mov     ax, [bp+8]
    push    ax
    lea     ax, [bp-14]
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3348
    lea     ax, [bp-14]
    add     ax, 2
    mov     bx, ax
    mov     ax, [bx]
    test    ax, ax
    setnz   al
    cbw
L3348:
    pop     bx
    mov     [bx], ax
; RPN'ized expression: "( idx *u 1 + , oldIdxRight 1 + oldSpRight sp - - , ConstExpr *u , s simplifyConstExpr ) "
; Expanded expression: " (@4) *(2) *(2) 1 +  (@-8) *(2) 1 + (@-10) *(2) sp *(2) - -  (@8) *(2) *(2)  (@-4) *(2)  simplifyConstExpr ()8 "
; Fused expression:    "( *(2) (@4) + *ax 1 , + *(@-8) 1 push-ax - *(@-10) *sp - *sp ax , *(2) (@8) *(2) ax , *(2) (@-4) , simplifyConstExpr )8 "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    add     ax, 1
    push    ax
    mov     ax, [bp-8]
    add     ax, 1
    push    ax
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    pop     ax
    sub     ax, cx
    push    ax
    mov     ax, [bp+8]
    mov     bx, ax
    push    word [bx]
    push    word [bp-4]
    call    _simplifyConstExpr
    sub     sp, -8
    sub     sp, -10
; }
; break
    jmp     L3100
; case
; RPN'ized expression: "120 "
; Expanded expression: "120 "
; Expression value: 120
    jmp     L3308
L3307:
    cmp     ax, 120
    jne     L3349
L3308:
; RPN'ized expression: "s ( ConstExpr , ExprTypeSynPtr , idx exprval ) 0 != = "
; Expanded expression: "(@-4)  (@8) *(2)  (@6) *(2)  (@4) *(2)  exprval ()6 0 != =(2) "
; Fused expression:    "( *(2) (@8) , *(2) (@6) , *(2) (@4) , exprval )6 != ax 0 =(34) *(@-4) ax "
    push    word [bp+8]
    push    word [bp+6]
    push    word [bp+4]
    call    _exprval
    sub     sp, -6
    cmp     ax, 0
    setne   al
    cbw
    mov     [bp-4], ax
; RPN'ized expression: "( tok , ExprTypeSynPtr *u nonVoidTypeCheck ) "
; Expanded expression: " (@-2) *(2)  (@6) *(2) *(2)  nonVoidTypeCheck ()4 "
; Fused expression:    "( *(2) (@-2) , *(2) (@6) *(2) ax , nonVoidTypeCheck )4 "
    push    word [bp-2]
    mov     ax, [bp+6]
    mov     bx, ax
    push    word [bx]
    call    _nonVoidTypeCheck
    sub     sp, -4
; RPN'ized expression: "( 0 , ExprTypeSynPtr decayArray ) "
; Expanded expression: " 0  (@6) *(2)  decayArray ()4 "
; Fused expression:    "( 0 , *(2) (@6) , decayArray )4 "
    push    0
    push    word [bp+6]
    call    _decayArray
    sub     sp, -4
; RPN'ized expression: "ExprTypeSynPtr *u 1 = "
; Expanded expression: "(@6) *(2) 1 =(2) "
; Fused expression:    "*(2) (@6) =(34) *ax 1 "
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, 1
    mov     [bx], ax
; RPN'ized expression: "( idx *u 1 + , oldIdxRight 1 + oldSpRight sp - - , ConstExpr *u , s simplifyConstExpr ) "
; Expanded expression: " (@4) *(2) *(2) 1 +  (@-8) *(2) 1 + (@-10) *(2) sp *(2) - -  (@8) *(2) *(2)  (@-4) *(2)  simplifyConstExpr ()8 "
; Fused expression:    "( *(2) (@4) + *ax 1 , + *(@-8) 1 push-ax - *(@-10) *sp - *sp ax , *(2) (@8) *(2) ax , *(2) (@-4) , simplifyConstExpr )8 "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    add     ax, 1
    push    ax
    mov     ax, [bp-8]
    add     ax, 1
    push    ax
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    pop     ax
    sub     ax, cx
    push    ax
    mov     ax, [bp+8]
    mov     bx, ax
    push    word [bx]
    push    word [bp-4]
    call    _simplifyConstExpr
    sub     sp, -8
; break
    jmp     L3100
; case
; RPN'ized expression: "6 "
; Expanded expression: "6 "
; Expression value: 6
    jmp     L3350
L3349:
    cmp     ax, 6
    jne     L3351
L3350:
; case
; RPN'ized expression: "7 "
; Expanded expression: "7 "
; Expression value: 7
    jmp     L3352
L3351:
    cmp     ax, 7
    jne     L3353
L3352:
; {
; loc             sr : (@-16): int
    sub     sp, 2
; loc             sl : (@-18): int
    sub     sp, 2
; loc             sc : (@-20): int
    sub     sp, 2
; =
; RPN'ized expression: "LabelCnt ++p "
; Expanded expression: "LabelCnt ++p(2) "
; Fused expression:    "++p(2) *LabelCnt =(34) *(@-20) ax "
    mov     ax, [_LabelCnt]
    inc     word [_LabelCnt]
    mov     [bp-20], ax
; RPN'ized expression: "stack idx *u 1 + + *u 1 + *u sc = "
; Expanded expression: "stack (@4) *(2) *(2) 1 + 4 * + 2 + (@-20) *(2) =(2) "
; Fused expression:    "*(2) (@4) + *ax 1 * ax 4 + stack ax + ax 2 =(34) *ax *(@-20) "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bp-20]
    mov     [bx], ax
; RPN'ized expression: "( 120 , idx *u ++ ins ) "
; Expanded expression: " 120  (@4) *(2) ++(2)  ins ()4 "
; Fused expression:    "( 120 , *(2) (@4) ++(2) *ax , ins )4 "
    push    120
    mov     ax, [bp+4]
    mov     bx, ax
    inc     word [bx]
    mov     ax, [bx]
    push    ax
    call    _ins
    sub     sp, -4
; RPN'ized expression: "sr ( constExpr 1 + *u &u , RightExprTypeSynPtr &u , idx exprval ) = "
; Expanded expression: "(@-16)  (@-14) 2 +  (@-6)  (@4) *(2)  exprval ()6 =(2) "
; Fused expression:    "( + (@-14) 2 , (@-6) , *(2) (@4) , exprval )6 =(34) *(@-16) ax "
    lea     ax, [bp-14]
    add     ax, 2
    push    ax
    lea     ax, [bp-6]
    push    ax
    push    word [bp+4]
    call    _exprval
    sub     sp, -6
    mov     [bp-16], ax
; if
; RPN'ized expression: "tok 6 == "
; Expanded expression: "(@-2) *(2) 6 == "
; Fused expression:    "== *(@-2) 6 IF! "
    mov     ax, [bp-2]
    cmp     ax, 6
    jne     L3355
; RPN'ized expression: "( sc , 90 , idx *u ++ ins2 ) "
; Expanded expression: " (@-20) *(2)  90  (@4) *(2) ++(2)  ins2 ()6 "
; Fused expression:    "( *(2) (@-20) , 90 , *(2) (@4) ++(2) *ax , ins2 )6 "
    push    word [bp-20]
    push    90
    mov     ax, [bp+4]
    mov     bx, ax
    inc     word [bx]
    mov     ax, [bx]
    push    ax
    call    _ins2
    sub     sp, -6
    jmp     L3356
L3355:
; else
; RPN'ized expression: "( sc -u , 90 , idx *u ++ ins2 ) "
; Expanded expression: " (@-20) *(2) -u  90  (@4) *(2) ++(2)  ins2 ()6 "
; Fused expression:    "( *(2) (@-20) -u , 90 , *(2) (@4) ++(2) *ax , ins2 )6 "
    mov     ax, [bp-20]
    neg     ax
    push    ax
    push    90
    mov     ax, [bp+4]
    mov     bx, ax
    inc     word [bx]
    mov     ax, [bx]
    push    ax
    call    _ins2
    sub     sp, -6
L3356:
; RPN'ized expression: "( 120 , idx *u ins ) "
; Expanded expression: " 120  (@4) *(2) *(2)  ins ()4 "
; Fused expression:    "( 120 , *(2) (@4) *(2) ax , ins )4 "
    push    120
    mov     ax, [bp+4]
    mov     bx, ax
    push    word [bx]
    call    _ins
    sub     sp, -4
; RPN'ized expression: "sl ( constExpr 0 + *u &u , ExprTypeSynPtr , idx exprval ) = "
; Expanded expression: "(@-18)  (@-14) 0 +  (@6) *(2)  (@4) *(2)  exprval ()6 =(2) "
; Fused expression:    "( + (@-14) 0 , *(2) (@6) , *(2) (@4) , exprval )6 =(34) *(@-18) ax "
    lea     ax, [bp-14]
    add     ax, 0
    push    ax
    push    word [bp+6]
    push    word [bp+4]
    call    _exprval
    sub     sp, -6
    mov     [bp-18], ax
; if
; RPN'ized expression: "tok 6 == "
; Expanded expression: "(@-2) *(2) 6 == "
; Fused expression:    "== *(@-2) 6 IF! "
    mov     ax, [bp-2]
    cmp     ax, 6
    jne     L3357
; RPN'ized expression: "sl sl sr && = "
; Expanded expression: "(@-18) (@-18) *(2) _Bool [sh&&->3359] (@-16) *(2) _Bool &&[3359] =(2) "
; Fused expression:    "*(2) (@-18) _Bool [sh&&->3359] *(2) (@-16) _Bool &&[3359] =(34) *(@-18) ax "
    mov     ax, [bp-18]
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3359
    mov     ax, [bp-16]
    test    ax, ax
    setnz   al
    cbw
L3359:
    mov     [bp-18], ax
    jmp     L3358
L3357:
; else
; RPN'ized expression: "sl sl sr || = "
; Expanded expression: "(@-18) (@-18) *(2) _Bool [sh||->3360] (@-16) *(2) _Bool ||[3360] =(2) "
; Fused expression:    "*(2) (@-18) _Bool [sh||->3360] *(2) (@-16) _Bool ||[3360] =(34) *(@-18) ax "
    mov     ax, [bp-18]
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L3360
    mov     ax, [bp-16]
    test    ax, ax
    setnz   al
    cbw
L3360:
    mov     [bp-18], ax
L3358:
; RPN'ized expression: "s sl = "
; Expanded expression: "(@-4) (@-18) *(2) =(2) "
; Fused expression:    "=(34) *(@-4) *(@-18) "
    mov     ax, [bp-18]
    mov     [bp-4], ax
; RPN'ized expression: "ExprTypeSynPtr *u 1 = "
; Expanded expression: "(@6) *(2) 1 =(2) "
; Fused expression:    "*(2) (@6) =(34) *ax 1 "
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, 1
    mov     [bx], ax
; RPN'ized expression: "ConstExpr *u constExpr 0 + *u constExpr 1 + *u && = "
; Expanded expression: "(@8) *(2) (@-14) 0 + *(2) _Bool [sh&&->3361] (@-14) 2 + *(2) _Bool &&[3361] =(2) "
; Fused expression:    "*(2) (@8) push-ax + (@-14) 0 *(2) ax _Bool [sh&&->3361] + (@-14) 2 *(2) ax _Bool &&[3361] =(34) **sp ax "
    mov     ax, [bp+8]
    push    ax
    lea     ax, [bp-14]
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3361
    lea     ax, [bp-14]
    add     ax, 2
    mov     bx, ax
    mov     ax, [bx]
    test    ax, ax
    setnz   al
    cbw
L3361:
    pop     bx
    mov     [bx], ax
; RPN'ized expression: "( idx *u 1 + , oldIdxRight 1 + oldSpRight sp - - , ConstExpr *u , s simplifyConstExpr ) "
; Expanded expression: " (@4) *(2) *(2) 1 +  (@-8) *(2) 1 + (@-10) *(2) sp *(2) - -  (@8) *(2) *(2)  (@-4) *(2)  simplifyConstExpr ()8 "
; Fused expression:    "( *(2) (@4) + *ax 1 , + *(@-8) 1 push-ax - *(@-10) *sp - *sp ax , *(2) (@8) *(2) ax , *(2) (@-4) , simplifyConstExpr )8 "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    add     ax, 1
    push    ax
    mov     ax, [bp-8]
    add     ax, 1
    push    ax
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    pop     ax
    sub     ax, cx
    push    ax
    mov     ax, [bp+8]
    mov     bx, ax
    push    word [bx]
    push    word [bp-4]
    call    _simplifyConstExpr
    sub     sp, -8
    sub     sp, -6
; }
; break
    jmp     L3100
; case
; RPN'ized expression: "41 "
; Expanded expression: "41 "
; Expression value: 41
    jmp     L3354
L3353:
    cmp     ax, 41
    jne     L3362
L3354:
; {
; loc             tmpSynPtr : (@-16): int
    sub     sp, 2
; loc             c : (@-18): int
    sub     sp, 2
; loc             minParams : (@-20): int
    sub     sp, 2
; loc             maxParams : (@-22): int
    sub     sp, 2
; RPN'ized expression: "( ConstExpr , ExprTypeSynPtr , idx exprval ) "
; Expanded expression: " (@8) *(2)  (@6) *(2)  (@4) *(2)  exprval ()6 "
; Fused expression:    "( *(2) (@8) , *(2) (@6) , *(2) (@4) , exprval )6 "
    push    word [bp+8]
    push    word [bp+6]
    push    word [bp+4]
    call    _exprval
    sub     sp, -6
; if
; RPN'ized expression: "( ExprTypeSynPtr , maxParams &u , minParams &u , ExprTypeSynPtr *u GetFxnInfo ) 0 == "
; Expanded expression: " (@6) *(2)  (@-22)  (@-20)  (@6) *(2) *(2)  GetFxnInfo ()8 0 == "
; Fused expression:    "( *(2) (@6) , (@-22) , (@-20) , *(2) (@6) *(2) ax , GetFxnInfo )8 == ax 0 IF! "
    push    word [bp+6]
    lea     ax, [bp-22]
    push    ax
    lea     ax, [bp-20]
    push    ax
    mov     ax, [bp+6]
    mov     bx, ax
    push    word [bx]
    call    _GetFxnInfo
    sub     sp, -8
    cmp     ax, 0
    jne     L3364
; RPN'ized expression: "( L3366 error ) "
; Expanded expression: " L3366  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3366:
    db  "exprval(): function or function pointer expected",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3366 , error )2 "
    push    L3366
    call    _error
    sub     sp, -2
L3364:
; RPN'ized expression: "c 0 = "
; Expanded expression: "(@-18) 0 =(2) "
; Fused expression:    "=(34) *(@-18) 0 "
    mov     ax, 0
    mov     [bp-18], ax
; while
; RPN'ized expression: "stack idx *u + *u 0 + *u 40 != "
; Expanded expression: "stack (@4) *(2) *(2) 4 * + 0 + *(2) 40 != "
L3368:
; Fused expression:    "*(2) (@4) * *ax 4 + stack ax + ax 0 != *ax 40 IF! "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 40
    je      L3369
; {
; if
; RPN'ized expression: "c 0 == "
; Expanded expression: "(@-18) *(2) 0 == "
; Fused expression:    "== *(@-18) 0 IF! "
    mov     ax, [bp-18]
    cmp     ax, 0
    jne     L3370
; RPN'ized expression: "( 44 , idx *u 1 + ins ) "
; Expanded expression: " 44  (@4) *(2) *(2) 1 +  ins ()4 "
; Fused expression:    "( 44 , *(2) (@4) + *ax 1 , ins )4 "
    push    44
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    add     ax, 1
    push    ax
    call    _ins
    sub     sp, -4
L3370:
; RPN'ized expression: "( ConstExpr , tmpSynPtr &u , idx exprval ) "
; Expanded expression: " (@8) *(2)  (@-16)  (@4) *(2)  exprval ()6 "
; Fused expression:    "( *(2) (@8) , (@-16) , *(2) (@4) , exprval )6 "
    push    word [bp+8]
    lea     ax, [bp-16]
    push    ax
    push    word [bp+4]
    call    _exprval
    sub     sp, -6
; if
; RPN'ized expression: "tmpSynPtr 0 >= SyntaxStack tmpSynPtr + *u 0 + *u 17 == && "
; Expanded expression: "(@-16) *(2) 0 >= _Bool [sh&&->3374] SyntaxStack (@-16) *(2) 4 * + 0 + *(2) 17 == _Bool &&[3374] "
; Fused expression:    ">= *(@-16) 0 _Bool [sh&&->3374] * *(@-16) 4 + SyntaxStack ax + ax 0 == *ax 17 _Bool &&[3374] "
    mov     ax, [bp-16]
    cmp     ax, 0
    setge   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3374
    mov     ax, [bp-16]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 17
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3374:
; JumpIfZero
    test    ax, ax
    jz      L3372
; RPN'ized expression: "( L3375 error ) "
; Expanded expression: " L3375  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3375:
    db  "exprval(): function parameters cannot be of type 'void'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3375 , error )2 "
    push    L3375
    call    _error
    sub     sp, -2
L3372:
; if
; RPN'ized expression: "c ++ maxParams > "
; Expanded expression: "(@-18) ++(2) (@-22) *(2) > "
; Fused expression:    "++(2) *(@-18) > ax *(@-22) IF! "
    inc     word [bp-18]
    mov     ax, [bp-18]
    cmp     ax, [bp-22]
    jle     L3377
; RPN'ized expression: "( L3379 error ) "
; Expanded expression: " L3379  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3379:
    db  "exprval(): too many function parameters",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3379 , error )2 "
    push    L3379
    call    _error
    sub     sp, -2
L3377:
; if
; RPN'ized expression: "stack idx *u + *u 0 + *u 44 == "
; Expanded expression: "stack (@4) *(2) *(2) 4 * + 0 + *(2) 44 == "
; Fused expression:    "*(2) (@4) * *ax 4 + stack ax + ax 0 == *ax 44 IF! "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 44
    jne     L3381
; RPN'ized expression: "idx *u -- "
; Expanded expression: "(@4) *(2) --(2) "
; Fused expression:    "*(2) (@4) --(2) *ax "
    mov     ax, [bp+4]
    mov     bx, ax
    dec     word [bx]
    mov     ax, [bx]
L3381:
; }
    jmp     L3368
L3369:
; RPN'ized expression: "idx *u -- "
; Expanded expression: "(@4) *(2) --(2) "
; Fused expression:    "*(2) (@4) --(2) *ax "
    mov     ax, [bp+4]
    mov     bx, ax
    dec     word [bx]
    mov     ax, [bx]
; if
; RPN'ized expression: "c minParams < "
; Expanded expression: "(@-18) *(2) (@-20) *(2) < "
; Fused expression:    "< *(@-18) *(@-20) IF! "
    mov     ax, [bp-18]
    cmp     ax, [bp-20]
    jge     L3383
; RPN'ized expression: "( L3385 error ) "
; Expanded expression: " L3385  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3385:
    db  "exprval(): too few function parameters",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3385 , error )2 "
    push    L3385
    call    _error
    sub     sp, -2
L3383:
; RPN'ized expression: "stack oldIdxRight 1 + oldSpRight sp - - + *u 1 + *u c SizeOfWord * = "
; Expanded expression: "stack (@-8) *(2) 1 + (@-10) *(2) sp *(2) - - 4 * + 2 + (@-18) *(2) SizeOfWord *(2) * =(2) "
; Fused expression:    "+ *(@-8) 1 push-ax - *(@-10) *sp - *sp ax * ax 4 + stack ax + ax 2 push-ax * *(@-18) *SizeOfWord =(34) **sp ax "
    mov     ax, [bp-8]
    add     ax, 1
    push    ax
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    pop     ax
    sub     ax, cx
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    push    ax
    mov     ax, [bp-18]
    mul     word [_SizeOfWord]
    pop     bx
    mov     [bx], ax
; RPN'ized expression: "ConstExpr *u 0 = "
; Expanded expression: "(@8) *(2) 0 =(2) "
; Fused expression:    "*(2) (@8) =(34) *ax 0 "
    mov     ax, [bp+8]
    mov     bx, ax
    mov     ax, 0
    mov     [bx], ax
    sub     sp, -8
; }
; break
    jmp     L3100
; case
; RPN'ized expression: "65 "
; Expanded expression: "65 "
; Expression value: 65
    jmp     L3363
L3362:
    cmp     ax, 65
    jne     L3387
L3363:
; case
; RPN'ized expression: "66 "
; Expanded expression: "66 "
; Expression value: 66
    jmp     L3388
L3387:
    cmp     ax, 66
    jne     L3389
L3388:
; case
; RPN'ized expression: "67 "
; Expanded expression: "67 "
; Expression value: 67
    jmp     L3390
L3389:
    cmp     ax, 67
    jne     L3391
L3390:
; case
; RPN'ized expression: "68 "
; Expanded expression: "68 "
; Expression value: 68
    jmp     L3392
L3391:
    cmp     ax, 68
    jne     L3393
L3392:
; case
; RPN'ized expression: "69 "
; Expanded expression: "69 "
; Expression value: 69
    jmp     L3394
L3393:
    cmp     ax, 69
    jne     L3395
L3394:
; case
; RPN'ized expression: "70 "
; Expanded expression: "70 "
; Expression value: 70
    jmp     L3396
L3395:
    cmp     ax, 70
    jne     L3397
L3396:
; case
; RPN'ized expression: "71 "
; Expanded expression: "71 "
; Expression value: 71
    jmp     L3398
L3397:
    cmp     ax, 71
    jne     L3399
L3398:
; case
; RPN'ized expression: "72 "
; Expanded expression: "72 "
; Expression value: 72
    jmp     L3400
L3399:
    cmp     ax, 72
    jne     L3401
L3400:
; case
; RPN'ized expression: "73 "
; Expanded expression: "73 "
; Expression value: 73
    jmp     L3402
L3401:
    cmp     ax, 73
    jne     L3403
L3402:
; case
; RPN'ized expression: "74 "
; Expanded expression: "74 "
; Expression value: 74
    jmp     L3404
L3403:
    cmp     ax, 74
    jne     L3405
L3404:
; {
; loc             ptrmask : (@-16): int
    sub     sp, 2
; loc             oldIdxLeft : (@-18): int
    sub     sp, 2
; loc             oldSpLeft : (@-20): int
    sub     sp, 2
; loc             incSize : (@-22): int
    sub     sp, 2
; loc             opSize : (@-24): int
    sub     sp, 2
; RPN'ized expression: "( constExpr 1 + *u &u , RightExprTypeSynPtr &u , idx exprval ) "
; Expanded expression: " (@-14) 2 +  (@-6)  (@4) *(2)  exprval ()6 "
; Fused expression:    "( + (@-14) 2 , (@-6) , *(2) (@4) , exprval )6 "
    lea     ax, [bp-14]
    add     ax, 2
    push    ax
    lea     ax, [bp-6]
    push    ax
    push    word [bp+4]
    call    _exprval
    sub     sp, -6
; RPN'ized expression: "oldIdxLeft idx *u = "
; Expanded expression: "(@-18) (@4) *(2) *(2) =(2) "
; Fused expression:    "*(2) (@4) =(34) *(@-18) *ax "
    mov     ax, [bp+4]
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-18], ax
; RPN'ized expression: "oldSpLeft sp = "
; Expanded expression: "(@-20) sp *(2) =(2) "
; Fused expression:    "=(34) *(@-20) *sp "
    mov     ax, [_sp]
    mov     [bp-20], ax
; RPN'ized expression: "( constExpr 0 + *u &u , ExprTypeSynPtr , idx exprval ) "
; Expanded expression: " (@-14) 0 +  (@6) *(2)  (@4) *(2)  exprval ()6 "
; Fused expression:    "( + (@-14) 0 , *(2) (@6) , *(2) (@4) , exprval )6 "
    lea     ax, [bp-14]
    add     ax, 0
    push    ax
    push    word [bp+6]
    push    word [bp+4]
    call    _exprval
    sub     sp, -6
; RPN'ized expression: "( tok , RightExprTypeSynPtr nonVoidTypeCheck ) "
; Expanded expression: " (@-2) *(2)  (@-6) *(2)  nonVoidTypeCheck ()4 "
; Fused expression:    "( *(2) (@-2) , *(2) (@-6) , nonVoidTypeCheck )4 "
    push    word [bp-2]
    push    word [bp-6]
    call    _nonVoidTypeCheck
    sub     sp, -4
; RPN'ized expression: "( tok , ExprTypeSynPtr *u nonVoidTypeCheck ) "
; Expanded expression: " (@-2) *(2)  (@6) *(2) *(2)  nonVoidTypeCheck ()4 "
; Fused expression:    "( *(2) (@-2) , *(2) (@6) *(2) ax , nonVoidTypeCheck )4 "
    push    word [bp-2]
    mov     ax, [bp+6]
    mov     bx, ax
    push    word [bx]
    call    _nonVoidTypeCheck
    sub     sp, -4
; RPN'ized expression: "( 1 , RightExprTypeSynPtr &u decayArray ) "
; Expanded expression: " 1  (@-6)  decayArray ()4 "
; Fused expression:    "( 1 , (@-6) , decayArray )4 "
    push    1
    lea     ax, [bp-6]
    push    ax
    call    _decayArray
    sub     sp, -4
; RPN'ized expression: "( 1 , ExprTypeSynPtr decayArray ) "
; Expanded expression: " 1  (@6) *(2)  decayArray ()4 "
; Fused expression:    "( 1 , *(2) (@6) , decayArray )4 "
    push    1
    push    word [bp+6]
    call    _decayArray
    sub     sp, -4
; if
; RPN'ized expression: "oldIdxLeft oldSpLeft sp - - 0 >= stack oldIdxLeft oldSpLeft sp - - + *u 0 + *u 78 == && 0 == "
; Expanded expression: "(@-18) *(2) (@-20) *(2) sp *(2) - - 0 >= _Bool [sh&&->3409] stack (@-18) *(2) (@-20) *(2) sp *(2) - - 4 * + 0 + *(2) 78 == _Bool &&[3409] 0 == "
; Fused expression:    "- *(@-20) *sp - *(@-18) ax >= ax 0 _Bool [sh&&->3409] - *(@-20) *sp - *(@-18) ax * ax 4 + stack ax + ax 0 == *ax 78 _Bool &&[3409] == ax 0 IF! "
    mov     ax, [bp-20]
    sub     ax, [_sp]
    mov     cx, ax
    mov     ax, [bp-18]
    sub     ax, cx
    cmp     ax, 0
    setge   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3409
    mov     ax, [bp-20]
    sub     ax, [_sp]
    mov     cx, ax
    mov     ax, [bp-18]
    sub     ax, cx
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 78
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3409:
    cmp     ax, 0
    jne     L3407
; RPN'ized expression: "( ( tok GetTokenName ) , L3410 error ) "
; Expanded expression: "  (@-2) *(2)  GetTokenName ()2  L3410  error ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3410:
    db  "Error: exprval(): lvalue expected before %s",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( *(2) (@-2) , GetTokenName )2 , L3410 , error )4 "
    push    word [bp-2]
    call    _GetTokenName
    sub     sp, -2
    push    ax
    push    L3410
    call    _error
    sub     sp, -4
L3407:
; RPN'ized expression: "opSize stack oldIdxLeft oldSpLeft sp - - + *u 1 + *u = "
; Expanded expression: "(@-24) stack (@-18) *(2) (@-20) *(2) sp *(2) - - 4 * + 2 + *(2) =(2) "
; Fused expression:    "- *(@-20) *sp - *(@-18) ax * ax 4 + stack ax + ax 2 =(34) *(@-24) *ax "
    mov     ax, [bp-20]
    sub     ax, [_sp]
    mov     cx, ax
    mov     ax, [bp-18]
    sub     ax, cx
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-24], ax
; RPN'ized expression: "stack oldIdxRight 1 + oldSpRight sp - - + *u 1 + *u opSize = "
; Expanded expression: "stack (@-8) *(2) 1 + (@-10) *(2) sp *(2) - - 4 * + 2 + (@-24) *(2) =(2) "
; Fused expression:    "+ *(@-8) 1 push-ax - *(@-10) *sp - *sp ax * ax 4 + stack ax + ax 2 =(34) *ax *(@-24) "
    mov     ax, [bp-8]
    add     ax, 1
    push    ax
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    pop     ax
    sub     ax, cx
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bp-24]
    mov     [bx], ax
; RPN'ized expression: "( 1 , oldIdxLeft oldSpLeft sp - - del ) "
; Expanded expression: " 1  (@-18) *(2) (@-20) *(2) sp *(2) - -  del ()4 "
; Fused expression:    "( 1 , - *(@-20) *sp - *(@-18) ax , del )4 "
    push    1
    mov     ax, [bp-20]
    sub     ax, [_sp]
    mov     cx, ax
    mov     ax, [bp-18]
    sub     ax, cx
    push    ax
    call    _del
    sub     sp, -4
; RPN'ized expression: "ptrmask RightExprTypeSynPtr 0 < ExprTypeSynPtr *u 0 < 2 * + = "
; Expanded expression: "(@-16) (@-6) *(2) 0 < (@6) *(2) *(2) 0 < 2 * + =(2) "
; Fused expression:    "< *(@-6) 0 push-ax *(2) (@6) < *ax 0 * ax 2 + *sp ax =(34) *(@-16) ax "
    mov     ax, [bp-6]
    cmp     ax, 0
    setl    al
    cbw
    push    ax
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 0
    setl    al
    cbw
    imul    ax, ax, 2
    mov     cx, ax
    pop     ax
    add     ax, cx
    mov     [bp-16], ax
; if
; RPN'ized expression: "tok 68 != tok 69 != && "
; Expanded expression: "(@-2) *(2) 68 != _Bool [sh&&->3414] (@-2) *(2) 69 != _Bool &&[3414] "
; Fused expression:    "!= *(@-2) 68 _Bool [sh&&->3414] != *(@-2) 69 _Bool &&[3414] "
    mov     ax, [bp-2]
    cmp     ax, 68
    setne   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3414
    mov     ax, [bp-2]
    cmp     ax, 69
    setne   al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3414:
; JumpIfZero
    test    ax, ax
    jz      L3412
; {
; if
; RPN'ized expression: "ptrmask "
; Expanded expression: "(@-16) *(2) "
; Fused expression:    "*(2) (@-16) "
    mov     ax, [bp-16]
; JumpIfZero
    test    ax, ax
    jz      L3415
; RPN'ized expression: "( ( tok GetTokenName ) , L3417 error ) "
; Expanded expression: "  (@-2) *(2)  GetTokenName ()2  L3417  error ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3417:
    db  "Error: exprval(): invalid combination of operands for %s",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( *(2) (@-2) , GetTokenName )2 , L3417 , error )4 "
    push    word [bp-2]
    call    _GetTokenName
    sub     sp, -2
    push    ax
    push    L3417
    call    _error
    sub     sp, -4
L3415:
; }
    jmp     L3413
L3412:
; else
; {
; if
; RPN'ized expression: "ptrmask 1 & "
; Expanded expression: "(@-16) *(2) 1 & "
; Fused expression:    "& *(@-16) 1 "
    mov     ax, [bp-16]
    and     ax, 1
; JumpIfZero
    test    ax, ax
    jz      L3419
; RPN'ized expression: "( ( tok GetTokenName ) , L3421 error ) "
; Expanded expression: "  (@-2) *(2)  GetTokenName ()2  L3421  error ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3421:
    db  "Error: exprval(): invalid combination of operands for %s",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( *(2) (@-2) , GetTokenName )2 , L3421 , error )4 "
    push    word [bp-2]
    call    _GetTokenName
    sub     sp, -2
    push    ax
    push    L3421
    call    _error
    sub     sp, -4
L3419:
; }
L3413:
; if
; RPN'ized expression: "ptrmask 2 == "
; Expanded expression: "(@-16) *(2) 2 == "
; Fused expression:    "== *(@-16) 2 IF! "
    mov     ax, [bp-16]
    cmp     ax, 2
    jne     L3423
; {
; RPN'ized expression: "incSize ( ExprTypeSynPtr *u -u GetDeclSize ) = "
; Expanded expression: "(@-22)  (@6) *(2) *(2) -u  GetDeclSize ()2 =(2) "
; Fused expression:    "( *(2) (@6) *(2) ax -u , GetDeclSize )2 =(34) *(@-22) ax "
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, [bx]
    neg     ax
    push    ax
    call    _GetDeclSize
    sub     sp, -2
    mov     [bp-22], ax
; if
; RPN'ized expression: "constExpr 1 + *u "
; Expanded expression: "(@-14) 2 + *(2) "
; Fused expression:    "+ (@-14) 2 *(2) ax "
    lea     ax, [bp-14]
    add     ax, 2
    mov     bx, ax
    mov     ax, [bx]
; JumpIfZero
    test    ax, ax
    jz      L3425
; {
; RPN'ized expression: "stack oldIdxRight oldSpRight sp - - + *u 1 + *u incSize *= "
; Expanded expression: "stack (@-8) *(2) (@-10) *(2) sp *(2) - - 4 * + 2 + (@-22) *(2) *=(2) "
; Fused expression:    "- *(@-10) *sp - *(@-8) ax * ax 4 + stack ax + ax 2 *=(34) *ax *(@-22) "
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    mov     ax, [bp-8]
    sub     ax, cx
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bx]
    mul     word [bp-22]
    mov     [bx], ax
; }
    jmp     L3426
L3425:
; else
; if
; RPN'ized expression: "incSize 1 != "
; Expanded expression: "(@-22) *(2) 1 != "
; Fused expression:    "!= *(@-22) 1 IF! "
    mov     ax, [bp-22]
    cmp     ax, 1
    je      L3427
; {
; RPN'ized expression: "( incSize , 1 , oldIdxRight 1 + oldSpRight sp - - ins2 ) "
; Expanded expression: " (@-22) *(2)  1  (@-8) *(2) 1 + (@-10) *(2) sp *(2) - -  ins2 ()6 "
; Fused expression:    "( *(2) (@-22) , 1 , + *(@-8) 1 push-ax - *(@-10) *sp - *sp ax , ins2 )6 "
    push    word [bp-22]
    push    1
    mov     ax, [bp-8]
    add     ax, 1
    push    ax
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    pop     ax
    sub     ax, cx
    push    ax
    call    _ins2
    sub     sp, -6
; RPN'ized expression: "( 42 , oldIdxRight 1 + oldSpRight sp - - ins ) "
; Expanded expression: " 42  (@-8) *(2) 1 + (@-10) *(2) sp *(2) - -  ins ()4 "
; Fused expression:    "( 42 , + *(@-8) 1 push-ax - *(@-10) *sp - *sp ax , ins )4 "
    push    42
    mov     ax, [bp-8]
    add     ax, 1
    push    ax
    mov     ax, [bp-10]
    sub     ax, [_sp]
    mov     cx, ax
    pop     ax
    sub     ax, cx
    push    ax
    call    _ins
    sub     sp, -4
; }
L3427:
L3426:
; }
L3423:
; RPN'ized expression: "ConstExpr *u 0 = "
; Expanded expression: "(@8) *(2) 0 =(2) "
; Fused expression:    "*(2) (@8) =(34) *ax 0 "
    mov     ax, [bp+8]
    mov     bx, ax
    mov     ax, 0
    mov     [bx], ax
    sub     sp, -10
; }
; break
    jmp     L3100
; default
L3101:
; RPN'ized expression: "( ( tok GetTokenName ) , L3429 error ) "
; Expanded expression: "  (@-2) *(2)  GetTokenName ()2  L3429  error ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3429:
    db  "exprval(): Unexpected token %s",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( *(2) (@-2) , GetTokenName )2 , L3429 , error )4 "
    push    word [bp-2]
    call    _GetTokenName
    sub     sp, -2
    push    ax
    push    L3429
    call    _error
    sub     sp, -4
; }
    jmp     L3100
L3405:
    jmp     L3101
L3100:
; return
; RPN'ized expression: "s "
; Expanded expression: "(@-4) *(2) "
; Fused expression:    "*(2) (@-4) "
    mov     ax, [bp-4]
    jmp     L3095
L3095:
    leave
    ret
; SEGMENT _TEXT
; glb ParseExpr : (
; prm     tok : int
; prm     GotUnary : * int
; prm     ExprTypeSynPtr : * int
; prm     ConstExpr : * int
; prm     ConstVal : * int
;     ) int
SEGMENT _TEXT
    global  _ParseExpr
_ParseExpr:
    push    bp
    mov     bp, sp
; loc     tok : (@4): int
; loc     GotUnary : (@6): * int
; loc     ExprTypeSynPtr : (@8): * int
; loc     ConstExpr : (@10): * int
; loc     ConstVal : (@12): * int
; loc     i : (@-2): int
    sub     sp, 2
; RPN'ized expression: "ConstVal *u ConstExpr *u 0 = = "
; Expanded expression: "(@12) *(2) (@10) *(2) 0 =(2) =(2) "
; Fused expression:    "*(2) (@12) push-ax *(2) (@10) =(34) *ax 0 =(34) **sp ax "
    mov     ax, [bp+12]
    push    ax
    mov     ax, [bp+10]
    mov     bx, ax
    mov     ax, 0
    mov     [bx], ax
    pop     bx
    mov     [bx], ax
; RPN'ized expression: "ExprTypeSynPtr *u 0 = "
; Expanded expression: "(@8) *(2) 0 =(2) "
; Fused expression:    "*(2) (@8) =(34) *ax 0 "
    mov     ax, [bp+8]
    mov     bx, ax
    mov     ax, 0
    mov     [bx], ax
; if
; RPN'ized expression: "ExprLevel ++p 0 == "
; Expanded expression: "ExprLevel ++p(2) 0 == "
; Fused expression:    "++p(2) *ExprLevel == ax 0 IF! "
    mov     ax, [_ExprLevel]
    inc     word [_ExprLevel]
    cmp     ax, 0
    jne     L3432
; {
; RPN'ized expression: "opsp sp 0 = = "
; Expanded expression: "opsp sp 0 =(2) =(2) "
; Fused expression:    "=(34) *sp 0 =(34) *opsp ax "
    mov     ax, 0
    mov     [_sp], ax
    mov     [_opsp], ax
; RPN'ized expression: "( PurgeStringTable ) "
; Expanded expression: " PurgeStringTable ()0 "
; Fused expression:    "( PurgeStringTable )0 "
    call    _PurgeStringTable
; }
L3432:
; RPN'ized expression: "tok ( GotUnary , tok expr ) = "
; Expanded expression: "(@4)  (@6) *(2)  (@4) *(2)  expr ()4 =(2) "
; Fused expression:    "( *(2) (@6) , *(2) (@4) , expr )4 =(34) *(@4) ax "
    push    word [bp+6]
    push    word [bp+4]
    call    _expr
    sub     sp, -4
    mov     [bp+4], ax
; if
; RPN'ized expression: "tok 0 == ( tok , L3436 strchr ) 0 == || "
; Expanded expression: "(@4) *(2) 0 == _Bool [sh||->3438]  (@4) *(2)  L3436  strchr ()4 0 == _Bool ||[3438] "
; SEGMENT _TEXT
SEGMENT _DATA
L3436:
    db  ",;:)]",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "== *(@4) 0 _Bool [sh||->3438] ( *(2) (@4) , L3436 , strchr )4 == ax 0 _Bool ||[3438] "
    mov     ax, [bp+4]
    cmp     ax, 0
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L3438
    push    word [bp+4]
    push    L3436
    call    _strchr
    sub     sp, -4
    cmp     ax, 0
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3438:
; JumpIfZero
    test    ax, ax
    jz      L3434
; RPN'ized expression: "( ( tok GetTokenName ) , L3439 error ) "
; Expanded expression: "  (@4) *(2)  GetTokenName ()2  L3439  error ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3439:
    db  "Error: ParseExpr(): Unexpected token %s",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( *(2) (@4) , GetTokenName )2 , L3439 , error )4 "
    push    word [bp+4]
    call    _GetTokenName
    sub     sp, -2
    push    ax
    push    L3439
    call    _error
    sub     sp, -4
L3434:
; if
; RPN'ized expression: "GotUnary *u "
; Expanded expression: "(@6) *(2) *(2) "
; Fused expression:    "*(2) (@6) *(2) ax "
    mov     ax, [bp+6]
    mov     bx, ax
    mov     ax, [bx]
; JumpIfZero
    test    ax, ax
    jz      L3441
; {
; loc         j : (@-4): int
    sub     sp, 2
; for
; RPN'ized expression: "j 0 = "
; Expanded expression: "(@-4) 0 =(2) "
; Fused expression:    "=(34) *(@-4) 0 "
    mov     ax, 0
    mov     [bp-4], ax
L3443:
; RPN'ized expression: "j 2 < "
; Expanded expression: "(@-4) *(2) 2 < "
; Fused expression:    "< *(@-4) 2 IF! "
    mov     ax, [bp-4]
    cmp     ax, 2
    jge     L3446
    jmp     L3445
L3444:
; RPN'ized expression: "j ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
    mov     ax, [bp-4]
    inc     word [bp-4]
    jmp     L3443
L3445:
; {
; if
; RPN'ized expression: "j "
; Expanded expression: "(@-4) *(2) "
; Fused expression:    "*(2) (@-4) "
    mov     ax, [bp-4]
; JumpIfZero
    test    ax, ax
    jz      L3447
; RPN'ized expression: "( L3449 printf ) "
; Expanded expression: " L3449  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3449:
    db  "; Expanded",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3449 , printf )2 "
    push    L3449
    call    _printf
    sub     sp, -2
    jmp     L3448
L3447:
; else
; RPN'ized expression: "( L3451 printf ) "
; Expanded expression: " L3451  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3451:
    db  "; RPN'ized",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3451 , printf )2 "
    push    L3451
    call    _printf
    sub     sp, -2
L3448:
; RPN'ized expression: "( L3453 printf ) "
; Expanded expression: " L3453  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3453:
    db  " expression: ",34,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3453 , printf )2 "
    push    L3453
    call    _printf
    sub     sp, -2
; for
; RPN'ized expression: "i 0 = "
; Expanded expression: "(@-2) 0 =(2) "
; Fused expression:    "=(34) *(@-2) 0 "
    mov     ax, 0
    mov     [bp-2], ax
L3455:
; RPN'ized expression: "i sp < "
; Expanded expression: "(@-2) *(2) sp *(2) < "
; Fused expression:    "< *(@-2) *sp IF! "
    mov     ax, [bp-2]
    cmp     ax, [_sp]
    jge     L3458
    jmp     L3457
L3456:
; RPN'ized expression: "i ++p "
; Expanded expression: "(@-2) ++p(2) "
; Fused expression:    "++p(2) *(@-2) "
    mov     ax, [bp-2]
    inc     word [bp-2]
    jmp     L3455
L3457:
; {
; loc                 tok : (@-6): int
    sub     sp, 2
; =
; RPN'ized expression: "stack i + *u 0 + *u "
; Expanded expression: "stack (@-2) *(2) 4 * + 0 + *(2) "
; Fused expression:    "* *(@-2) 4 + stack ax + ax 0 =(34) *(@-6) *ax "
    mov     ax, [bp-2]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-6], ax
; switch
; RPN'ized expression: "tok "
; Expanded expression: "(@-6) *(2) "
; Fused expression:    "*(2) (@-6) "
    mov     ax, [bp-6]
    jmp     L3461
; {
; case
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
    jmp     L3462
L3461:
    cmp     ax, 1
    jne     L3463
L3462:
; case
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
    jmp     L3464
L3463:
    cmp     ax, 2
    jne     L3465
L3464:
; RPN'ized expression: "( stack i + *u 1 + *u , L3467 printf ) "
; Expanded expression: " stack (@-2) *(2) 4 * + 2 + *(2)  L3467  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3467:
    db  "%d",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( * *(@-2) 4 + stack ax + ax 2 *(2) ax , L3467 , printf )4 "
    mov     ax, [bp-2]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    L3467
    call    _printf
    sub     sp, -4
; break
    jmp     L3459
; case
; RPN'ized expression: "16 "
; Expanded expression: "16 "
; Expression value: 16
    jmp     L3466
L3465:
    cmp     ax, 16
    jne     L3469
L3466:
; {
; loc                         p : (@-8): * char
    sub     sp, 2
; =
; RPN'ized expression: "IdentTable stack i + *u 1 + *u + "
; Expanded expression: "IdentTable stack (@-2) *(2) 4 * + 2 + *(2) + "
; Fused expression:    "* *(@-2) 4 + stack ax + ax 2 + IdentTable *ax =(34) *(@-8) ax "
    mov     ax, [bp-2]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, _IdentTable
    add     ax, cx
    mov     [bp-8], ax
; if
; RPN'ized expression: "( p *u isdigit ) "
; Expanded expression: " (@-8) *(2) *(1)  isdigit ()2 "
; Fused expression:    "( *(2) (@-8) *(1) ax , isdigit )2 "
    mov     ax, [bp-8]
    mov     bx, ax
    mov     al, [bx]
    cbw
    push    ax
    call    _isdigit
    sub     sp, -2
; JumpIfZero
    test    ax, ax
    jz      L3471
; RPN'ized expression: "( L3473 printf ) "
; Expanded expression: " L3473  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3473:
    db  "L",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3473 , printf )2 "
    push    L3473
    call    _printf
    sub     sp, -2
L3471:
; RPN'ized expression: "( p , L3475 printf ) "
; Expanded expression: " (@-8) *(2)  L3475  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3475:
    db  "%s",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-8) , L3475 , printf )4 "
    push    word [bp-8]
    push    L3475
    call    _printf
    sub     sp, -4
    sub     sp, -2
; }
; break
    jmp     L3459
; case
; RPN'ized expression: "90 "
; Expanded expression: "90 "
; Expression value: 90
    jmp     L3470
L3469:
    cmp     ax, 90
    jne     L3477
L3470:
; if
; RPN'ized expression: "stack i + *u 1 + *u 0 >= "
; Expanded expression: "stack (@-2) *(2) 4 * + 2 + *(2) 0 >= "
; Fused expression:    "* *(@-2) 4 + stack ax + ax 2 >= *ax 0 IF! "
    mov     ax, [bp-2]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 0
    jl      L3479
; RPN'ized expression: "( stack i + *u 1 + *u , L3481 printf ) "
; Expanded expression: " stack (@-2) *(2) 4 * + 2 + *(2)  L3481  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3481:
    db  "[sh&&->%d]",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( * *(@-2) 4 + stack ax + ax 2 *(2) ax , L3481 , printf )4 "
    mov     ax, [bp-2]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    L3481
    call    _printf
    sub     sp, -4
    jmp     L3480
L3479:
; else
; RPN'ized expression: "( stack i + *u 1 + *u -u , L3483 printf ) "
; Expanded expression: " stack (@-2) *(2) 4 * + 2 + *(2) -u  L3483  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3483:
    db  "[sh||->%d]",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( * *(@-2) 4 + stack ax + ax 2 *(2) ax -u , L3483 , printf )4 "
    mov     ax, [bp-2]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bx]
    neg     ax
    push    ax
    push    L3483
    call    _printf
    sub     sp, -4
L3480:
; break
    jmp     L3459
; case
; RPN'ized expression: "89 "
; Expanded expression: "89 "
; Expression value: 89
    jmp     L3478
L3477:
    cmp     ax, 89
    jne     L3485
L3478:
; RPN'ized expression: "( stack i + *u 1 + *u , L3487 printf ) "
; Expanded expression: " stack (@-2) *(2) 4 * + 2 + *(2)  L3487  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3487:
    db  "(@%d)",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( * *(@-2) 4 + stack ax + ax 2 *(2) ax , L3487 , printf )4 "
    mov     ax, [bp-2]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    L3487
    call    _printf
    sub     sp, -4
; break
    jmp     L3459
; case
; RPN'ized expression: "78 "
; Expanded expression: "78 "
; Expression value: 78
    jmp     L3486
L3485:
    cmp     ax, 78
    jne     L3489
L3486:
; if
; RPN'ized expression: "j "
; Expanded expression: "(@-4) *(2) "
; Fused expression:    "*(2) (@-4) "
    mov     ax, [bp-4]
; JumpIfZero
    test    ax, ax
    jz      L3491
; RPN'ized expression: "( stack i + *u 1 + *u , L3493 printf ) "
; Expanded expression: " stack (@-2) *(2) 4 * + 2 + *(2)  L3493  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3493:
    db  "*(%d)",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( * *(@-2) 4 + stack ax + ax 2 *(2) ax , L3493 , printf )4 "
    mov     ax, [bp-2]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    L3493
    call    _printf
    sub     sp, -4
    jmp     L3492
L3491:
; else
; RPN'ized expression: "( L3495 printf ) "
; Expanded expression: " L3495  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3495:
    db  "*u",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3495 , printf )2 "
    push    L3495
    call    _printf
    sub     sp, -2
L3492:
; break
    jmp     L3459
; case
; RPN'ized expression: "40 "
; Expanded expression: "40 "
; Expression value: 40
    jmp     L3490
L3489:
    cmp     ax, 40
    jne     L3497
L3490:
; case
; RPN'ized expression: "44 "
; Expanded expression: "44 "
; Expression value: 44
    jmp     L3498
L3497:
    cmp     ax, 44
    jne     L3499
L3498:
; if
; RPN'ized expression: "j 0 == "
; Expanded expression: "(@-4) *(2) 0 == "
; Fused expression:    "== *(@-4) 0 IF! "
    mov     ax, [bp-4]
    cmp     ax, 0
    jne     L3501
; RPN'ized expression: "( tok , L3503 printf ) "
; Expanded expression: " (@-6) *(2)  L3503  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3503:
    db  "%c",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-6) , L3503 , printf )4 "
    push    word [bp-6]
    push    L3503
    call    _printf
    sub     sp, -4
L3501:
; break
    jmp     L3459
; case
; RPN'ized expression: "41 "
; Expanded expression: "41 "
; Expression value: 41
    jmp     L3500
L3499:
    cmp     ax, 41
    jne     L3505
L3500:
; if
; RPN'ized expression: "j "
; Expanded expression: "(@-4) *(2) "
; Fused expression:    "*(2) (@-4) "
    mov     ax, [bp-4]
; JumpIfZero
    test    ax, ax
    jz      L3507
; RPN'ized expression: "( L3509 printf ) "
; Expanded expression: " L3509  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3509:
    db  "(",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3509 , printf )2 "
    push    L3509
    call    _printf
    sub     sp, -2
L3507:
; RPN'ized expression: "( tok , L3511 printf ) "
; Expanded expression: " (@-6) *(2)  L3511  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3511:
    db  "%c",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-6) , L3511 , printf )4 "
    push    word [bp-6]
    push    L3511
    call    _printf
    sub     sp, -4
; if
; RPN'ized expression: "j "
; Expanded expression: "(@-4) *(2) "
; Fused expression:    "*(2) (@-4) "
    mov     ax, [bp-4]
; JumpIfZero
    test    ax, ax
    jz      L3513
; RPN'ized expression: "( stack i + *u 1 + *u , L3515 printf ) "
; Expanded expression: " stack (@-2) *(2) 4 * + 2 + *(2)  L3515  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3515:
    db  "%d",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( * *(@-2) 4 + stack ax + ax 2 *(2) ax , L3515 , printf )4 "
    mov     ax, [bp-2]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    L3515
    call    _printf
    sub     sp, -4
L3513:
; break
    jmp     L3459
; default
L3460:
; RPN'ized expression: "( ( tok GetTokenName ) , L3517 printf ) "
; Expanded expression: "  (@-6) *(2)  GetTokenName ()2  L3517  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3517:
    db  "%s",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( *(2) (@-6) , GetTokenName )2 , L3517 , printf )4 "
    push    word [bp-6]
    call    _GetTokenName
    sub     sp, -2
    push    ax
    push    L3517
    call    _printf
    sub     sp, -4
; if
; RPN'ized expression: "j "
; Expanded expression: "(@-4) *(2) "
; Fused expression:    "*(2) (@-4) "
    mov     ax, [bp-4]
; JumpIfZero
    test    ax, ax
    jz      L3519
; {
; switch
; RPN'ized expression: "tok "
; Expanded expression: "(@-6) *(2) "
; Fused expression:    "*(2) (@-6) "
    mov     ax, [bp-6]
    jmp     L3523
; {
; case
; RPN'ized expression: "7 "
; Expanded expression: "7 "
; Expression value: 7
    jmp     L3524
L3523:
    cmp     ax, 7
    jne     L3525
L3524:
; case
; RPN'ized expression: "6 "
; Expanded expression: "6 "
; Expression value: 6
    jmp     L3526
L3525:
    cmp     ax, 6
    jne     L3527
L3526:
; RPN'ized expression: "( stack i + *u 1 + *u , L3529 printf ) "
; Expanded expression: " stack (@-2) *(2) 4 * + 2 + *(2)  L3529  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3529:
    db  "[%d]",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( * *(@-2) 4 + stack ax + ax 2 *(2) ax , L3529 , printf )4 "
    mov     ax, [bp-2]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    L3529
    call    _printf
    sub     sp, -4
; break
    jmp     L3521
; case
; RPN'ized expression: "61 "
; Expanded expression: "61 "
; Expression value: 61
    jmp     L3528
L3527:
    cmp     ax, 61
    jne     L3531
L3528:
; case
; RPN'ized expression: "12 "
; Expanded expression: "12 "
; Expression value: 12
    jmp     L3532
L3531:
    cmp     ax, 12
    jne     L3533
L3532:
; case
; RPN'ized expression: "13 "
; Expanded expression: "13 "
; Expression value: 13
    jmp     L3534
L3533:
    cmp     ax, 13
    jne     L3535
L3534:
; case
; RPN'ized expression: "81 "
; Expanded expression: "81 "
; Expression value: 81
    jmp     L3536
L3535:
    cmp     ax, 81
    jne     L3537
L3536:
; case
; RPN'ized expression: "82 "
; Expanded expression: "82 "
; Expression value: 82
    jmp     L3538
L3537:
    cmp     ax, 82
    jne     L3539
L3538:
; case
; RPN'ized expression: "68 "
; Expanded expression: "68 "
; Expression value: 68
    jmp     L3540
L3539:
    cmp     ax, 68
    jne     L3541
L3540:
; case
; RPN'ized expression: "69 "
; Expanded expression: "69 "
; Expression value: 69
    jmp     L3542
L3541:
    cmp     ax, 69
    jne     L3543
L3542:
; case
; RPN'ized expression: "83 "
; Expanded expression: "83 "
; Expression value: 83
    jmp     L3544
L3543:
    cmp     ax, 83
    jne     L3545
L3544:
; case
; RPN'ized expression: "84 "
; Expanded expression: "84 "
; Expression value: 84
    jmp     L3546
L3545:
    cmp     ax, 84
    jne     L3547
L3546:
; case
; RPN'ized expression: "65 "
; Expanded expression: "65 "
; Expression value: 65
    jmp     L3548
L3547:
    cmp     ax, 65
    jne     L3549
L3548:
; case
; RPN'ized expression: "66 "
; Expanded expression: "66 "
; Expression value: 66
    jmp     L3550
L3549:
    cmp     ax, 66
    jne     L3551
L3550:
; case
; RPN'ized expression: "67 "
; Expanded expression: "67 "
; Expression value: 67
    jmp     L3552
L3551:
    cmp     ax, 67
    jne     L3553
L3552:
; case
; RPN'ized expression: "70 "
; Expanded expression: "70 "
; Expression value: 70
    jmp     L3554
L3553:
    cmp     ax, 70
    jne     L3555
L3554:
; case
; RPN'ized expression: "71 "
; Expanded expression: "71 "
; Expression value: 71
    jmp     L3556
L3555:
    cmp     ax, 71
    jne     L3557
L3556:
; case
; RPN'ized expression: "72 "
; Expanded expression: "72 "
; Expression value: 72
    jmp     L3558
L3557:
    cmp     ax, 72
    jne     L3559
L3558:
; case
; RPN'ized expression: "73 "
; Expanded expression: "73 "
; Expression value: 73
    jmp     L3560
L3559:
    cmp     ax, 73
    jne     L3561
L3560:
; case
; RPN'ized expression: "74 "
; Expanded expression: "74 "
; Expression value: 74
    jmp     L3562
L3561:
    cmp     ax, 74
    jne     L3563
L3562:
; RPN'ized expression: "( stack i + *u 1 + *u , L3565 printf ) "
; Expanded expression: " stack (@-2) *(2) 4 * + 2 + *(2)  L3565  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3565:
    db  "(%d)",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( * *(@-2) 4 + stack ax + ax 2 *(2) ax , L3565 , printf )4 "
    mov     ax, [bp-2]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    L3565
    call    _printf
    sub     sp, -4
; break
    jmp     L3521
; }
    jmp     L3521
L3563:
L3521:
; }
L3519:
; break
    jmp     L3459
; }
    jmp     L3459
L3505:
    jmp     L3460
L3459:
; RPN'ized expression: "( L3567 printf ) "
; Expanded expression: " L3567  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3567:
    db  " ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3567 , printf )2 "
    push    L3567
    call    _printf
    sub     sp, -2
    sub     sp, -2
; }
    jmp     L3456
L3458:
; RPN'ized expression: "( L3569 printf ) "
; Expanded expression: " L3569  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3569:
    db  34,10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3569 , printf )2 "
    push    L3569
    call    _printf
    sub     sp, -2
; if
; RPN'ized expression: "j 0 == "
; Expanded expression: "(@-4) *(2) 0 == "
; Fused expression:    "== *(@-4) 0 IF! "
    mov     ax, [bp-4]
    cmp     ax, 0
    jne     L3571
; {
; loc                 idx : (@-6): int
    sub     sp, 2
; =
; RPN'ized expression: "sp 1 - "
; Expanded expression: "sp *(2) 1 - "
; Fused expression:    "- *sp 1 =(34) *(@-6) ax "
    mov     ax, [_sp]
    sub     ax, 1
    mov     [bp-6], ax
; RPN'ized expression: "ConstVal *u ( ConstExpr , ExprTypeSynPtr , idx &u exprval ) = "
; Expanded expression: "(@12) *(2)  (@10) *(2)  (@8) *(2)  (@-6)  exprval ()6 =(2) "
; Fused expression:    "*(2) (@12) push-ax ( *(2) (@10) , *(2) (@8) , (@-6) , exprval )6 =(34) **sp ax "
    mov     ax, [bp+12]
    push    ax
    push    word [bp+10]
    push    word [bp+8]
    lea     ax, [bp-6]
    push    ax
    call    _exprval
    sub     sp, -6
    pop     bx
    mov     [bx], ax
    sub     sp, -2
; }
    jmp     L3572
L3571:
; else
; if
; RPN'ized expression: "ConstExpr *u "
; Expanded expression: "(@10) *(2) *(2) "
; Fused expression:    "*(2) (@10) *(2) ax "
    mov     ax, [bp+10]
    mov     bx, ax
    mov     ax, [bx]
; JumpIfZero
    test    ax, ax
    jz      L3573
; RPN'ized expression: "( ConstVal *u , L3575 printf ) "
; Expanded expression: " (@12) *(2) *(2)  L3575  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3575:
    db  "; Expression value: %d",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@12) *(2) ax , L3575 , printf )4 "
    mov     ax, [bp+12]
    mov     bx, ax
    push    word [bx]
    push    L3575
    call    _printf
    sub     sp, -4
L3573:
L3572:
; }
    jmp     L3444
L3446:
    sub     sp, -2
; }
L3441:
; RPN'ized expression: "ExprLevel --p "
; Expanded expression: "ExprLevel --p(2) "
; Fused expression:    "--p(2) *ExprLevel "
    mov     ax, [_ExprLevel]
    dec     word [_ExprLevel]
; return
; RPN'ized expression: "tok "
; Expanded expression: "(@4) *(2) "
; Fused expression:    "*(2) (@4) "
    mov     ax, [bp+4]
    jmp     L3431
L3431:
    leave
    ret
; SEGMENT _TEXT
; glb error : (
; prm     format : * char
; prm     ...
;     ) void
SEGMENT _TEXT
    global  _error
_error:
    push    bp
    mov     bp, sp
; loc     format : (@4): * char
; RPN'ized expression: "( L3578 printf ) "
; Expanded expression: " L3578  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3578:
    db  10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3578 , printf )2 "
    push    L3578
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( DumpSynDecls ) "
; Expanded expression: " DumpSynDecls ()0 "
; Fused expression:    "( DumpSynDecls )0 "
    call    _DumpSynDecls
; RPN'ized expression: "( DumpMacroTable ) "
; Expanded expression: " DumpMacroTable ()0 "
; Fused expression:    "( DumpMacroTable )0 "
    call    _DumpMacroTable
; RPN'ized expression: "( DumpIdentTable ) "
; Expanded expression: " DumpIdentTable ()0 "
; Fused expression:    "( DumpIdentTable )0 "
    call    _DumpIdentTable
; RPN'ized expression: "( LinePos , LineNo , CurFileName , L3580 printf ) "
; Expanded expression: " LinePos *(2)  LineNo *(2)  CurFileName *(2)  L3580  printf ()8 "
; SEGMENT _TEXT
SEGMENT _DATA
L3580:
    db  "Error in ",34,"%s",34," (%d:%d)",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) LinePos , *(2) LineNo , *(2) CurFileName , L3580 , printf )8 "
    push    word [_LinePos]
    push    word [_LineNo]
    push    word [_CurFileName]
    push    L3580
    call    _printf
    sub     sp, -8
; RPN'ized expression: "( format , L3582 printf ) "
; Expanded expression: " (@4) *(2)  L3582  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3582:
    db  "%s",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@4) , L3582 , printf )4 "
    push    word [bp+4]
    push    L3582
    call    _printf
    sub     sp, -4
; RPN'ized expression: "( 1 -u exit ) "
; Expanded expression: " -1  exit ()2 "
; Fused expression:    "( -1 , exit )2 "
    push    -1
    call    _exit
    sub     sp, -2
L3577:
    leave
    ret
; SEGMENT _TEXT
; glb TokenStartsDeclaration : (
; prm     t : int
; prm     params : int
;     ) int
SEGMENT _TEXT
    global  _TokenStartsDeclaration
_TokenStartsDeclaration:
    push    bp
    mov     bp, sp
; loc     t : (@4): int
; loc     params : (@6): int
; return
; RPN'ized expression: "t 17 == t 18 == || t 19 == || params 0 == t 108 == && || "
; Expanded expression: "(@4) *(2) 17 == _Bool [sh||->3588] (@4) *(2) 18 == _Bool ||[3588] _Bool [sh||->3587] (@4) *(2) 19 == _Bool ||[3587] _Bool [sh||->3585] (@6) *(2) 0 == _Bool [sh&&->3586] (@4) *(2) 108 == _Bool &&[3586] _Bool ||[3585] "
; Fused expression:    "== *(@4) 17 _Bool [sh||->3588] == *(@4) 18 _Bool ||[3588] _Bool [sh||->3587] == *(@4) 19 _Bool ||[3587] _Bool [sh||->3585] == *(@6) 0 _Bool [sh&&->3586] == *(@4) 108 _Bool &&[3586] _Bool ||[3585] "
    mov     ax, [bp+4]
    cmp     ax, 17
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L3588
    mov     ax, [bp+4]
    cmp     ax, 18
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3588:
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L3587
    mov     ax, [bp+4]
    cmp     ax, 19
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3587:
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L3585
    mov     ax, [bp+6]
    cmp     ax, 0
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3586
    mov     ax, [bp+4]
    cmp     ax, 108
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3586:
    test    ax, ax
    setnz   al
    cbw
L3585:
    jmp     L3584
L3584:
    leave
    ret
; SEGMENT _TEXT
; glb PushSyntax2 : (
; prm     t : int
; prm     v : int
;     ) void
SEGMENT _TEXT
    global  _PushSyntax2
_PushSyntax2:
    push    bp
    mov     bp, sp
; loc     t : (@4): int
; loc     v : (@6): int
; if
; RPN'ized expression: "SyntaxStackCnt 2048 >= "
; Expanded expression: "SyntaxStackCnt *(2) 2048 >= "
; Fused expression:    ">= *SyntaxStackCnt 2048 IF! "
    mov     ax, [_SyntaxStackCnt]
    cmp     ax, 2048
    jl      L3590
; RPN'ized expression: "( L3592 error ) "
; Expanded expression: " L3592  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3592:
    db  "Internal error: Too many declarations",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3592 , error )2 "
    push    L3592
    call    _error
    sub     sp, -2
L3590:
; RPN'ized expression: "SyntaxStack SyntaxStackCnt + *u 0 + *u t = "
; Expanded expression: "SyntaxStack SyntaxStackCnt *(2) 4 * + 0 + (@4) *(2) =(2) "
; Fused expression:    "* *SyntaxStackCnt 4 + SyntaxStack ax + ax 0 =(34) *ax *(@4) "
    mov     ax, [_SyntaxStackCnt]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bp+4]
    mov     [bx], ax
; RPN'ized expression: "SyntaxStack SyntaxStackCnt ++p + *u 1 + *u v = "
; Expanded expression: "SyntaxStack SyntaxStackCnt ++p(2) 4 * + 2 + (@6) *(2) =(2) "
; Fused expression:    "++p(2) *SyntaxStackCnt * ax 4 + SyntaxStack ax + ax 2 =(34) *ax *(@6) "
    mov     ax, [_SyntaxStackCnt]
    inc     word [_SyntaxStackCnt]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bp+6]
    mov     [bx], ax
L3589:
    leave
    ret
; SEGMENT _TEXT
; glb PushSyntax : (
; prm     t : int
;     ) void
SEGMENT _TEXT
    global  _PushSyntax
_PushSyntax:
    push    bp
    mov     bp, sp
; loc     t : (@4): int
; RPN'ized expression: "( 0 , t PushSyntax2 ) "
; Expanded expression: " 0  (@4) *(2)  PushSyntax2 ()4 "
; Fused expression:    "( 0 , *(2) (@4) , PushSyntax2 )4 "
    push    0
    push    word [bp+4]
    call    _PushSyntax2
    sub     sp, -4
L3594:
    leave
    ret
; SEGMENT _TEXT
; glb InsertSyntax2 : (
; prm     pos : int
; prm     t : int
; prm     v : int
;     ) void
SEGMENT _TEXT
    global  _InsertSyntax2
_InsertSyntax2:
    push    bp
    mov     bp, sp
; loc     pos : (@4): int
; loc     t : (@6): int
; loc     v : (@8): int
; if
; RPN'ized expression: "SyntaxStackCnt 2048 >= "
; Expanded expression: "SyntaxStackCnt *(2) 2048 >= "
; Fused expression:    ">= *SyntaxStackCnt 2048 IF! "
    mov     ax, [_SyntaxStackCnt]
    cmp     ax, 2048
    jl      L3596
; RPN'ized expression: "( L3598 error ) "
; Expanded expression: " L3598  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3598:
    db  "Internal error: Too many declarations",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3598 , error )2 "
    push    L3598
    call    _error
    sub     sp, -2
L3596:
; RPN'ized expression: "( SyntaxStack 0 + *u sizeof SyntaxStackCnt pos - * , SyntaxStack pos + *u , SyntaxStack pos 1 + + *u memmove ) "
; Expanded expression: " 4 SyntaxStackCnt *(2) (@4) *(2) - *  SyntaxStack (@4) *(2) 4 * +  SyntaxStack (@4) *(2) 1 + 4 * +  memmove ()6 "
; Fused expression:    "( - *SyntaxStackCnt *(@4) * 4 ax , * *(@4) 4 + SyntaxStack ax , + *(@4) 1 * ax 4 + SyntaxStack ax , memmove )6 "
    mov     ax, [_SyntaxStackCnt]
    sub     ax, [bp+4]
    mov     cx, ax
    mov     ax, 4
    mul     cx
    push    ax
    mov     ax, [bp+4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    push    ax
    mov     ax, [bp+4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    push    ax
    call    _memmove
    sub     sp, -6
; RPN'ized expression: "SyntaxStack pos + *u 0 + *u t = "
; Expanded expression: "SyntaxStack (@4) *(2) 4 * + 0 + (@6) *(2) =(2) "
; Fused expression:    "* *(@4) 4 + SyntaxStack ax + ax 0 =(34) *ax *(@6) "
    mov     ax, [bp+4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bp+6]
    mov     [bx], ax
; RPN'ized expression: "SyntaxStack pos + *u 1 + *u v = "
; Expanded expression: "SyntaxStack (@4) *(2) 4 * + 2 + (@8) *(2) =(2) "
; Fused expression:    "* *(@4) 4 + SyntaxStack ax + ax 2 =(34) *ax *(@8) "
    mov     ax, [bp+4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bp+8]
    mov     [bx], ax
; RPN'ized expression: "SyntaxStackCnt ++p "
; Expanded expression: "SyntaxStackCnt ++p(2) "
; Fused expression:    "++p(2) *SyntaxStackCnt "
    mov     ax, [_SyntaxStackCnt]
    inc     word [_SyntaxStackCnt]
L3595:
    leave
    ret
; SEGMENT _TEXT
; glb InsertSyntax : (
; prm     pos : int
; prm     t : int
;     ) void
SEGMENT _TEXT
    global  _InsertSyntax
_InsertSyntax:
    push    bp
    mov     bp, sp
; loc     pos : (@4): int
; loc     t : (@6): int
; RPN'ized expression: "( 0 , t , pos InsertSyntax2 ) "
; Expanded expression: " 0  (@6) *(2)  (@4) *(2)  InsertSyntax2 ()6 "
; Fused expression:    "( 0 , *(2) (@6) , *(2) (@4) , InsertSyntax2 )6 "
    push    0
    push    word [bp+6]
    push    word [bp+4]
    call    _InsertSyntax2
    sub     sp, -6
L3600:
    leave
    ret
; SEGMENT _TEXT
; glb DeleteSyntax : (
; prm     pos : int
; prm     cnt : int
;     ) void
SEGMENT _TEXT
    global  _DeleteSyntax
_DeleteSyntax:
    push    bp
    mov     bp, sp
; loc     pos : (@4): int
; loc     cnt : (@6): int
; RPN'ized expression: "( SyntaxStack 0 + *u sizeof SyntaxStackCnt pos cnt + - * , SyntaxStack pos cnt + + *u , SyntaxStack pos + *u memmove ) "
; Expanded expression: " 4 SyntaxStackCnt *(2) (@4) *(2) (@6) *(2) + - *  SyntaxStack (@4) *(2) (@6) *(2) + 4 * +  SyntaxStack (@4) *(2) 4 * +  memmove ()6 "
; Fused expression:    "( + *(@4) *(@6) - *SyntaxStackCnt ax * 4 ax , + *(@4) *(@6) * ax 4 + SyntaxStack ax , * *(@4) 4 + SyntaxStack ax , memmove )6 "
    mov     ax, [bp+4]
    add     ax, [bp+6]
    mov     cx, ax
    mov     ax, [_SyntaxStackCnt]
    sub     ax, cx
    mov     cx, ax
    mov     ax, 4
    mul     cx
    push    ax
    mov     ax, [bp+4]
    add     ax, [bp+6]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    push    ax
    mov     ax, [bp+4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    push    ax
    call    _memmove
    sub     sp, -6
; RPN'ized expression: "SyntaxStackCnt cnt -= "
; Expanded expression: "SyntaxStackCnt (@6) *(2) -=(2) "
; Fused expression:    "-=(34) *SyntaxStackCnt *(@6) "
    mov     ax, [_SyntaxStackCnt]
    sub     ax, [bp+6]
    mov     [_SyntaxStackCnt], ax
L3601:
    leave
    ret
; SEGMENT _TEXT
; glb FindSymbol : (
; prm     s : * char
;     ) int
SEGMENT _TEXT
    global  _FindSymbol
_FindSymbol:
    push    bp
    mov     bp, sp
; loc     s : (@4): * char
; loc     i : (@-2): int
    sub     sp, 2
; for
; RPN'ized expression: "i SyntaxStackCnt 1 - = "
; Expanded expression: "(@-2) SyntaxStackCnt *(2) 1 - =(2) "
; Fused expression:    "- *SyntaxStackCnt 1 =(34) *(@-2) ax "
    mov     ax, [_SyntaxStackCnt]
    sub     ax, 1
    mov     [bp-2], ax
L3603:
; RPN'ized expression: "i 0 >= "
; Expanded expression: "(@-2) *(2) 0 >= "
; Fused expression:    ">= *(@-2) 0 IF! "
    mov     ax, [bp-2]
    cmp     ax, 0
    jl      L3606
    jmp     L3605
L3604:
; RPN'ized expression: "i --p "
; Expanded expression: "(@-2) --p(2) "
; Fused expression:    "--p(2) *(@-2) "
    mov     ax, [bp-2]
    dec     word [bp-2]
    jmp     L3603
L3605:
; {
; if
; RPN'ized expression: "SyntaxStack i + *u 0 + *u 16 == ( s , IdentTable SyntaxStack i + *u 1 + *u + strcmp ) 0 == && "
; Expanded expression: "SyntaxStack (@-2) *(2) 4 * + 0 + *(2) 16 == _Bool [sh&&->3609]  (@4) *(2)  IdentTable SyntaxStack (@-2) *(2) 4 * + 2 + *(2) +  strcmp ()4 0 == _Bool &&[3609] "
; Fused expression:    "* *(@-2) 4 + SyntaxStack ax + ax 0 == *ax 16 _Bool [sh&&->3609] ( *(2) (@4) , * *(@-2) 4 + SyntaxStack ax + ax 2 + IdentTable *ax , strcmp )4 == ax 0 _Bool &&[3609] "
    mov     ax, [bp-2]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 16
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3609
    push    word [bp+4]
    mov     ax, [bp-2]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, _IdentTable
    add     ax, cx
    push    ax
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3609:
; JumpIfZero
    test    ax, ax
    jz      L3607
; {
; return
; RPN'ized expression: "i "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
    mov     ax, [bp-2]
    jmp     L3602
; }
    jmp     L3608
L3607:
; else
; if
; RPN'ized expression: "SyntaxStack i + *u 0 + *u 41 == "
; Expanded expression: "SyntaxStack (@-2) *(2) 4 * + 0 + *(2) 41 == "
; Fused expression:    "* *(@-2) 4 + SyntaxStack ax + ax 0 == *ax 41 IF! "
    mov     ax, [bp-2]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 41
    jne     L3610
; {
; loc             c : (@-4): int
    sub     sp, 2
; =
; RPN'ized expression: "1 -u "
; Expanded expression: "-1 "
; Expression value: -1
; Fused expression:    "=(34) *(@-4) -1 "
    mov     ax, -1
    mov     [bp-4], ax
; while
; RPN'ized expression: "c "
; Expanded expression: "(@-4) *(2) "
L3612:
; Fused expression:    "*(2) (@-4) "
    mov     ax, [bp-4]
; JumpIfZero
    test    ax, ax
    jz      L3613
; {
; loc                 t : (@-6): int
    sub     sp, 2
; =
; RPN'ized expression: "SyntaxStack i -- + *u 0 + *u "
; Expanded expression: "SyntaxStack (@-2) --(2) 4 * + 0 + *(2) "
; Fused expression:    "--(2) *(@-2) * ax 4 + SyntaxStack ax + ax 0 =(34) *(@-6) *ax "
    dec     word [bp-2]
    mov     ax, [bp-2]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-6], ax
; RPN'ized expression: "c t 40 == t 41 == - += "
; Expanded expression: "(@-4) (@-6) *(2) 40 == (@-6) *(2) 41 == - +=(2) "
; Fused expression:    "== *(@-6) 40 push-ax == *(@-6) 41 - *sp ax +=(34) *(@-4) ax "
    mov     ax, [bp-6]
    cmp     ax, 40
    sete    al
    cbw
    push    ax
    mov     ax, [bp-6]
    cmp     ax, 41
    sete    al
    cbw
    mov     cx, ax
    pop     ax
    sub     ax, cx
    mov     cx, ax
    mov     ax, [bp-4]
    add     ax, cx
    mov     [bp-4], ax
    sub     sp, -2
; }
    jmp     L3612
L3613:
    sub     sp, -2
; }
L3610:
L3608:
; }
    jmp     L3604
L3606:
; return
; RPN'ized expression: "1 -u "
; Expanded expression: "-1 "
; Expression value: -1
; Fused expression:    "-1 "
    mov     ax, -1
    jmp     L3602
L3602:
    leave
    ret
; SEGMENT _TEXT
; glb SymType : (
; prm     SynPtr : int
;     ) int
SEGMENT _TEXT
    global  _SymType
_SymType:
    push    bp
    mov     bp, sp
; loc     SynPtr : (@4): int
; loc     local : (@-2): int
    sub     sp, 2
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "=(34) *(@-2) 0 "
    mov     ax, 0
    mov     [bp-2], ax
; if
; RPN'ized expression: "SyntaxStack SynPtr + *u 0 + *u 16 == "
; Expanded expression: "SyntaxStack (@4) *(2) 4 * + 0 + *(2) 16 == "
; Fused expression:    "* *(@4) 4 + SyntaxStack ax + ax 0 == *ax 16 IF! "
    mov     ax, [bp+4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 16
    jne     L3615
; RPN'ized expression: "SynPtr ++p "
; Expanded expression: "(@4) ++p(2) "
; Fused expression:    "++p(2) *(@4) "
    mov     ax, [bp+4]
    inc     word [bp+4]
L3615:
; if
; RPN'ized expression: "local SyntaxStack SynPtr + *u 0 + *u 89 == = 0 != "
; Expanded expression: "(@-2) SyntaxStack (@4) *(2) 4 * + 0 + *(2) 89 == =(2) 0 != "
; Fused expression:    "* *(@4) 4 + SyntaxStack ax + ax 0 == *ax 89 =(34) *(@-2) ax != ax 0 IF! "
    mov     ax, [bp+4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 89
    sete    al
    cbw
    mov     [bp-2], ax
    cmp     ax, 0
    je      L3617
; RPN'ized expression: "SynPtr ++p "
; Expanded expression: "(@4) ++p(2) "
; Fused expression:    "++p(2) *(@4) "
    mov     ax, [bp+4]
    inc     word [bp+4]
L3617:
; switch
; RPN'ized expression: "SyntaxStack SynPtr + *u 0 + *u "
; Expanded expression: "SyntaxStack (@4) *(2) 4 * + 0 + *(2) "
; Fused expression:    "* *(@4) 4 + SyntaxStack ax + ax 0 *(2) ax "
    mov     ax, [bp+4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    jmp     L3621
; {
; case
; RPN'ized expression: "40 "
; Expanded expression: "40 "
; Expression value: 40
    jmp     L3622
L3621:
    cmp     ax, 40
    jne     L3623
L3622:
; return
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "1 "
    mov     ax, 1
    jmp     L3614
; case
; RPN'ized expression: "91 "
; Expanded expression: "91 "
; Expression value: 91
    jmp     L3624
L3623:
    cmp     ax, 91
    jne     L3625
L3624:
; if
; RPN'ized expression: "local "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
    mov     ax, [bp-2]
; JumpIfZero
    test    ax, ax
    jz      L3627
; return
; RPN'ized expression: "5 "
; Expanded expression: "5 "
; Expression value: 5
; Fused expression:    "5 "
    mov     ax, 5
    jmp     L3614
L3627:
; return
; RPN'ized expression: "3 "
; Expanded expression: "3 "
; Expression value: 3
; Fused expression:    "3 "
    mov     ax, 3
    jmp     L3614
; default
L3620:
; if
; RPN'ized expression: "local "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
    mov     ax, [bp-2]
; JumpIfZero
    test    ax, ax
    jz      L3629
; return
; RPN'ized expression: "4 "
; Expanded expression: "4 "
; Expression value: 4
; Fused expression:    "4 "
    mov     ax, 4
    jmp     L3614
L3629:
; return
; RPN'ized expression: "2 "
; Expanded expression: "2 "
; Expression value: 2
; Fused expression:    "2 "
    mov     ax, 2
    jmp     L3614
; }
    jmp     L3619
L3625:
    jmp     L3620
L3619:
L3614:
    leave
    ret
; SEGMENT _TEXT
; glb GetDeclSize : (
; prm     SyntaxPtr : int
;     ) int
SEGMENT _TEXT
    global  _GetDeclSize
_GetDeclSize:
    push    bp
    mov     bp, sp
; loc     SyntaxPtr : (@4): int
; loc     i : (@-2): int
    sub     sp, 2
; loc     size : (@-4): int
    sub     sp, 2
; =
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "=(34) *(@-4) 1 "
    mov     ax, 1
    mov     [bp-4], ax
; if
; RPN'ized expression: "SyntaxPtr 0 < "
; Expanded expression: "(@4) *(2) 0 < "
; Fused expression:    "< *(@4) 0 IF! "
    mov     ax, [bp+4]
    cmp     ax, 0
    jge     L3632
; return
; RPN'ized expression: "1 -u "
; Expanded expression: "-1 "
; Expression value: -1
; Fused expression:    "-1 "
    mov     ax, -1
    jmp     L3631
L3632:
; for
; RPN'ized expression: "i SyntaxPtr = "
; Expanded expression: "(@-2) (@4) *(2) =(2) "
; Fused expression:    "=(34) *(@-2) *(@4) "
    mov     ax, [bp+4]
    mov     [bp-2], ax
L3634:
; RPN'ized expression: "i SyntaxStackCnt < "
; Expanded expression: "(@-2) *(2) SyntaxStackCnt *(2) < "
; Fused expression:    "< *(@-2) *SyntaxStackCnt IF! "
    mov     ax, [bp-2]
    cmp     ax, [_SyntaxStackCnt]
    jge     L3637
    jmp     L3636
L3635:
; RPN'ized expression: "i ++p "
; Expanded expression: "(@-2) ++p(2) "
; Fused expression:    "++p(2) *(@-2) "
    mov     ax, [bp-2]
    inc     word [bp-2]
    jmp     L3634
L3636:
; {
; loc         tok : (@-6): int
    sub     sp, 2
; =
; RPN'ized expression: "SyntaxStack i + *u 0 + *u "
; Expanded expression: "SyntaxStack (@-2) *(2) 4 * + 0 + *(2) "
; Fused expression:    "* *(@-2) 4 + SyntaxStack ax + ax 0 =(34) *(@-6) *ax "
    mov     ax, [bp-2]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-6], ax
; switch
; RPN'ized expression: "tok "
; Expanded expression: "(@-6) *(2) "
; Fused expression:    "*(2) (@-6) "
    mov     ax, [bp-6]
    jmp     L3640
; {
; case
; RPN'ized expression: "16 "
; Expanded expression: "16 "
; Expression value: 16
    jmp     L3641
L3640:
    cmp     ax, 16
    jne     L3642
L3641:
; case
; RPN'ized expression: "89 "
; Expanded expression: "89 "
; Expression value: 89
    jmp     L3643
L3642:
    cmp     ax, 89
    jne     L3644
L3643:
; break
    jmp     L3638
; case
; RPN'ized expression: "18 "
; Expanded expression: "18 "
; Expression value: 18
    jmp     L3645
L3644:
    cmp     ax, 18
    jne     L3646
L3645:
; return
; RPN'ized expression: "size "
; Expanded expression: "(@-4) *(2) "
; Fused expression:    "*(2) (@-4) "
    mov     ax, [bp-4]
    jmp     L3631
; case
; RPN'ized expression: "19 "
; Expanded expression: "19 "
; Expression value: 19
    jmp     L3647
L3646:
    cmp     ax, 19
    jne     L3648
L3647:
; return
; RPN'ized expression: "size SizeOfWord * "
; Expanded expression: "(@-4) *(2) SizeOfWord *(2) * "
; Fused expression:    "* *(@-4) *SizeOfWord "
    mov     ax, [bp-4]
    mul     word [_SizeOfWord]
    jmp     L3631
; case
; RPN'ized expression: "42 "
; Expanded expression: "42 "
; Expression value: 42
    jmp     L3649
L3648:
    cmp     ax, 42
    jne     L3650
L3649:
; return
; RPN'ized expression: "size SizeOfWord * "
; Expanded expression: "(@-4) *(2) SizeOfWord *(2) * "
; Fused expression:    "* *(@-4) *SizeOfWord "
    mov     ax, [bp-4]
    mul     word [_SizeOfWord]
    jmp     L3631
; case
; RPN'ized expression: "40 "
; Expanded expression: "40 "
; Expression value: 40
    jmp     L3651
L3650:
    cmp     ax, 40
    jne     L3652
L3651:
; return
; RPN'ized expression: "size SizeOfWord * "
; Expanded expression: "(@-4) *(2) SizeOfWord *(2) * "
; Fused expression:    "* *(@-4) *SizeOfWord "
    mov     ax, [bp-4]
    mul     word [_SizeOfWord]
    jmp     L3631
; case
; RPN'ized expression: "91 "
; Expanded expression: "91 "
; Expression value: 91
    jmp     L3653
L3652:
    cmp     ax, 91
    jne     L3654
L3653:
; if
; RPN'ized expression: "SyntaxStack i 1 + + *u 0 + *u 1 != "
; Expanded expression: "SyntaxStack (@-2) *(2) 1 + 4 * + 0 + *(2) 1 != "
; Fused expression:    "+ *(@-2) 1 * ax 4 + SyntaxStack ax + ax 0 != *ax 1 IF! "
    mov     ax, [bp-2]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 1
    je      L3656
; return
; RPN'ized expression: "1 -u "
; Expanded expression: "-1 "
; Expression value: -1
; Fused expression:    "-1 "
    mov     ax, -1
    jmp     L3631
L3656:
; RPN'ized expression: "size SyntaxStack i 1 + + *u 1 + *u *= "
; Expanded expression: "(@-4) SyntaxStack (@-2) *(2) 1 + 4 * + 2 + *(2) *=(2) "
; Fused expression:    "+ *(@-2) 1 * ax 4 + SyntaxStack ax + ax 2 *=(34) *(@-4) *ax "
    mov     ax, [bp-2]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, [bp-4]
    mul     cx
    mov     [bp-4], ax
; RPN'ized expression: "i 2 += "
; Expanded expression: "(@-2) 2 +=(2) "
; Fused expression:    "+=(34) *(@-2) 2 "
    mov     ax, [bp-2]
    add     ax, 2
    mov     [bp-2], ax
; break
    jmp     L3638
; default
L3639:
; return
; RPN'ized expression: "1 -u "
; Expanded expression: "-1 "
; Expression value: -1
; Fused expression:    "-1 "
    mov     ax, -1
    jmp     L3631
; }
    jmp     L3638
L3654:
    jmp     L3639
L3638:
    sub     sp, -2
; }
    jmp     L3635
L3637:
; return
; RPN'ized expression: "1 -u "
; Expanded expression: "-1 "
; Expression value: -1
; Fused expression:    "-1 "
    mov     ax, -1
    jmp     L3631
L3631:
    leave
    ret
; SEGMENT _TEXT
; glb ShowDecl : (
; prm     SyntaxPtr : int
; prm     IsParam : int
;     ) void
SEGMENT _TEXT
    global  _ShowDecl
_ShowDecl:
    push    bp
    mov     bp, sp
; loc     SyntaxPtr : (@4): int
; loc     IsParam : (@6): int
; loc     i : (@-2): int
    sub     sp, 2
; loc     icnt : (@-4): int
    sub     sp, 2
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "=(34) *(@-4) 0 "
    mov     ax, 0
    mov     [bp-4], ax
; if
; RPN'ized expression: "SyntaxPtr 0 < "
; Expanded expression: "(@4) *(2) 0 < "
; Fused expression:    "< *(@4) 0 IF! "
    mov     ax, [bp+4]
    cmp     ax, 0
    jge     L3659
; return
    jmp     L3658
L3659:
; for
; RPN'ized expression: "i SyntaxPtr = "
; Expanded expression: "(@-2) (@4) *(2) =(2) "
; Fused expression:    "=(34) *(@-2) *(@4) "
    mov     ax, [bp+4]
    mov     [bp-2], ax
L3661:
; RPN'ized expression: "i SyntaxStackCnt < "
; Expanded expression: "(@-2) *(2) SyntaxStackCnt *(2) < "
; Fused expression:    "< *(@-2) *SyntaxStackCnt IF! "
    mov     ax, [bp-2]
    cmp     ax, [_SyntaxStackCnt]
    jge     L3664
    jmp     L3663
L3662:
; RPN'ized expression: "i ++p "
; Expanded expression: "(@-2) ++p(2) "
; Fused expression:    "++p(2) *(@-2) "
    mov     ax, [bp-2]
    inc     word [bp-2]
    jmp     L3661
L3663:
; {
; loc         tok : (@-6): int
    sub     sp, 2
; =
; RPN'ized expression: "SyntaxStack i + *u 0 + *u "
; Expanded expression: "SyntaxStack (@-2) *(2) 4 * + 0 + *(2) "
; Fused expression:    "* *(@-2) 4 + SyntaxStack ax + ax 0 =(34) *(@-6) *ax "
    mov     ax, [bp-2]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-6], ax
; loc         v : (@-8): int
    sub     sp, 2
; =
; RPN'ized expression: "SyntaxStack i + *u 1 + *u "
; Expanded expression: "SyntaxStack (@-2) *(2) 4 * + 2 + *(2) "
; Fused expression:    "* *(@-2) 4 + SyntaxStack ax + ax 2 =(34) *(@-8) *ax "
    mov     ax, [bp-2]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-8], ax
; switch
; RPN'ized expression: "tok "
; Expanded expression: "(@-6) *(2) "
; Fused expression:    "*(2) (@-6) "
    mov     ax, [bp-6]
    jmp     L3667
; {
; case
; RPN'ized expression: "89 "
; Expanded expression: "89 "
; Expression value: 89
    jmp     L3668
L3667:
    cmp     ax, 89
    jne     L3669
L3668:
; RPN'ized expression: "( v , L3671 printf ) "
; Expanded expression: " (@-8) *(2)  L3671  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3671:
    db  "(@%d): ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-8) , L3671 , printf )4 "
    push    word [bp-8]
    push    L3671
    call    _printf
    sub     sp, -4
; break
    jmp     L3665
; case
; RPN'ized expression: "16 "
; Expanded expression: "16 "
; Expression value: 16
    jmp     L3670
L3669:
    cmp     ax, 16
    jne     L3673
L3670:
; if
; RPN'ized expression: "icnt ++ 1 > IsParam 0 == && "
; Expanded expression: "(@-4) ++(2) 1 > _Bool [sh&&->3677] (@6) *(2) 0 == _Bool &&[3677] "
; Fused expression:    "++(2) *(@-4) > ax 1 _Bool [sh&&->3677] == *(@6) 0 _Bool &&[3677] "
    inc     word [bp-4]
    mov     ax, [bp-4]
    cmp     ax, 1
    setg    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3677
    mov     ax, [bp+6]
    cmp     ax, 0
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3677:
; JumpIfZero
    test    ax, ax
    jz      L3675
; return
    jmp     L3658
L3675:
; RPN'ized expression: "( L3678 printf ) "
; Expanded expression: " L3678  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3678:
    db  "; ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3678 , printf )2 "
    push    L3678
    call    _printf
    sub     sp, -2
; if
; RPN'ized expression: "ParseLevel 0 == "
; Expanded expression: "ParseLevel *(2) 0 == "
; Fused expression:    "== *ParseLevel 0 IF! "
    mov     ax, [_ParseLevel]
    cmp     ax, 0
    jne     L3680
; RPN'ized expression: "( L3682 printf ) "
; Expanded expression: " L3682  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3682:
    db  "glb ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3682 , printf )2 "
    push    L3682
    call    _printf
    sub     sp, -2
    jmp     L3681
L3680:
; else
; if
; RPN'ized expression: "IsParam "
; Expanded expression: "(@6) *(2) "
; Fused expression:    "*(2) (@6) "
    mov     ax, [bp+6]
; JumpIfZero
    test    ax, ax
    jz      L3684
; RPN'ized expression: "( L3686 printf ) "
; Expanded expression: " L3686  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3686:
    db  "prm ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3686 , printf )2 "
    push    L3686
    call    _printf
    sub     sp, -2
    jmp     L3685
L3684:
; else
; RPN'ized expression: "( L3688 printf ) "
; Expanded expression: " L3688  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3688:
    db  "loc ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3688 , printf )2 "
    push    L3688
    call    _printf
    sub     sp, -2
L3685:
L3681:
; {
; loc                 j : (@-10): int
    sub     sp, 2
; for
; RPN'ized expression: "j 0 = "
; Expanded expression: "(@-10) 0 =(2) "
; Fused expression:    "=(34) *(@-10) 0 "
    mov     ax, 0
    mov     [bp-10], ax
L3690:
; RPN'ized expression: "j ParseLevel 4 * < "
; Expanded expression: "(@-10) *(2) ParseLevel *(2) 4 * < "
; Fused expression:    "* *ParseLevel 4 < *(@-10) ax IF! "
    mov     ax, [_ParseLevel]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, [bp-10]
    cmp     ax, cx
    jge     L3693
    jmp     L3692
L3691:
; RPN'ized expression: "j ++p "
; Expanded expression: "(@-10) ++p(2) "
; Fused expression:    "++p(2) *(@-10) "
    mov     ax, [bp-10]
    inc     word [bp-10]
    jmp     L3690
L3692:
; RPN'ized expression: "( L3694 printf ) "
; Expanded expression: " L3694  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3694:
    db  " ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3694 , printf )2 "
    push    L3694
    call    _printf
    sub     sp, -2
    jmp     L3691
L3693:
    sub     sp, -2
; }
; if
; RPN'ized expression: "IsParam ( L3698 , IdentTable v + strcmp ) 0 == && i 1 + SyntaxStackCnt < && "
; Expanded expression: "(@6) *(2) _Bool [sh&&->3701]  L3698  IdentTable (@-8) *(2) +  strcmp ()4 0 == _Bool &&[3701] _Bool [sh&&->3700] (@-2) *(2) 1 + SyntaxStackCnt *(2) < _Bool &&[3700] "
; SEGMENT _TEXT
SEGMENT _DATA
L3698:
    db  "<something>",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "*(2) (@6) _Bool [sh&&->3701] ( L3698 , + IdentTable *(@-8) , strcmp )4 == ax 0 _Bool &&[3701] _Bool [sh&&->3700] + *(@-2) 1 < ax *SyntaxStackCnt _Bool &&[3700] "
    mov     ax, [bp+6]
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3701
    push    L3698
    mov     ax, _IdentTable
    add     ax, [bp-8]
    push    ax
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3701:
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3700
    mov     ax, [bp-2]
    add     ax, 1
    cmp     ax, [_SyntaxStackCnt]
    setl    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3700:
; JumpIfZero
    test    ax, ax
    jz      L3696
; {
; if
; RPN'ized expression: "SyntaxStack i 1 + + *u 0 + *u 15 == "
; Expanded expression: "SyntaxStack (@-2) *(2) 1 + 4 * + 0 + *(2) 15 == "
; Fused expression:    "+ *(@-2) 1 * ax 4 + SyntaxStack ax + ax 0 == *ax 15 IF! "
    mov     ax, [bp-2]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 15
    jne     L3702
; continue
    sub     sp, -4
    jmp     L3662
L3702:
; }
L3696:
; RPN'ized expression: "( IdentTable v + , L3704 printf ) "
; Expanded expression: " IdentTable (@-8) *(2) +  L3704  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3704:
    db  "%s : ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( + IdentTable *(@-8) , L3704 , printf )4 "
    mov     ax, _IdentTable
    add     ax, [bp-8]
    push    ax
    push    L3704
    call    _printf
    sub     sp, -4
; break
    jmp     L3665
; case
; RPN'ized expression: "91 "
; Expanded expression: "91 "
; Expression value: 91
    jmp     L3674
L3673:
    cmp     ax, 91
    jne     L3706
L3674:
; RPN'ized expression: "( L3708 printf ) "
; Expanded expression: " L3708  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3708:
    db  "[",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3708 , printf )2 "
    push    L3708
    call    _printf
    sub     sp, -2
; break
    jmp     L3665
; case
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
    jmp     L3707
L3706:
    cmp     ax, 1
    jne     L3710
L3707:
; RPN'ized expression: "( v , L3712 printf ) "
; Expanded expression: " (@-8) *(2)  L3712  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3712:
    db  "%d",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( *(2) (@-8) , L3712 , printf )4 "
    push    word [bp-8]
    push    L3712
    call    _printf
    sub     sp, -4
; break
    jmp     L3665
; case
; RPN'ized expression: "93 "
; Expanded expression: "93 "
; Expression value: 93
    jmp     L3711
L3710:
    cmp     ax, 93
    jne     L3714
L3711:
; RPN'ized expression: "( L3716 printf ) "
; Expanded expression: " L3716  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3716:
    db  "] ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3716 , printf )2 "
    push    L3716
    call    _printf
    sub     sp, -2
; break
    jmp     L3665
; case
; RPN'ized expression: "40 "
; Expanded expression: "40 "
; Expression value: 40
    jmp     L3715
L3714:
    cmp     ax, 40
    jne     L3718
L3715:
; {
; loc                 noparams : (@-10): int
    sub     sp, 2
; loc                 j : (@-12): int
    sub     sp, 2
; =
; RPN'ized expression: "i ++ "
; Expanded expression: "(@-2) ++(2) "
; Fused expression:    "++(2) *(@-2) =(34) *(@-12) ax "
    inc     word [bp-2]
    mov     ax, [bp-2]
    mov     [bp-12], ax
; loc                 c : (@-14): int
    sub     sp, 2
; =
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "=(34) *(@-14) 1 "
    mov     ax, 1
    mov     [bp-14], ax
; while
; RPN'ized expression: "c "
; Expanded expression: "(@-14) *(2) "
L3720:
; Fused expression:    "*(2) (@-14) "
    mov     ax, [bp-14]
; JumpIfZero
    test    ax, ax
    jz      L3721
; {
; loc                     t : (@-16): int
    sub     sp, 2
; =
; RPN'ized expression: "SyntaxStack j ++p + *u 0 + *u "
; Expanded expression: "SyntaxStack (@-12) ++p(2) 4 * + 0 + *(2) "
; Fused expression:    "++p(2) *(@-12) * ax 4 + SyntaxStack ax + ax 0 =(34) *(@-16) *ax "
    mov     ax, [bp-12]
    inc     word [bp-12]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-16], ax
; RPN'ized expression: "c t 40 == t 41 == - += "
; Expanded expression: "(@-14) (@-16) *(2) 40 == (@-16) *(2) 41 == - +=(2) "
; Fused expression:    "== *(@-16) 40 push-ax == *(@-16) 41 - *sp ax +=(34) *(@-14) ax "
    mov     ax, [bp-16]
    cmp     ax, 40
    sete    al
    cbw
    push    ax
    mov     ax, [bp-16]
    cmp     ax, 41
    sete    al
    cbw
    mov     cx, ax
    pop     ax
    sub     ax, cx
    mov     cx, ax
    mov     ax, [bp-14]
    add     ax, cx
    mov     [bp-14], ax
    sub     sp, -2
; }
    jmp     L3720
L3721:
; RPN'ized expression: "noparams i 1 + j == SyntaxStack i 1 + + *u 0 + *u 17 == || = "
; Expanded expression: "(@-10) (@-2) *(2) 1 + (@-12) *(2) == _Bool [sh||->3722] SyntaxStack (@-2) *(2) 1 + 4 * + 0 + *(2) 17 == _Bool ||[3722] =(2) "
; Fused expression:    "+ *(@-2) 1 == ax *(@-12) _Bool [sh||->3722] + *(@-2) 1 * ax 4 + SyntaxStack ax + ax 0 == *ax 17 _Bool ||[3722] =(34) *(@-10) ax "
    mov     ax, [bp-2]
    add     ax, 1
    cmp     ax, [bp-12]
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L3722
    mov     ax, [bp-2]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 17
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3722:
    mov     [bp-10], ax
; RPN'ized expression: "( L3723 printf ) "
; Expanded expression: " L3723  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3723:
    db  "(",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3723 , printf )2 "
    push    L3723
    call    _printf
    sub     sp, -2
; if
; RPN'ized expression: "noparams "
; Expanded expression: "(@-10) *(2) "
; Fused expression:    "*(2) (@-10) "
    mov     ax, [bp-10]
; JumpIfZero
    test    ax, ax
    jz      L3725
; {
; if
; RPN'ized expression: "i 1 + j != "
; Expanded expression: "(@-2) *(2) 1 + (@-12) *(2) != "
; Fused expression:    "+ *(@-2) 1 != ax *(@-12) IF! "
    mov     ax, [bp-2]
    add     ax, 1
    cmp     ax, [bp-12]
    je      L3727
; RPN'ized expression: "( L3729 printf ) "
; Expanded expression: " L3729  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3729:
    db  "void",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3729 , printf )2 "
    push    L3729
    call    _printf
    sub     sp, -2
L3727:
; }
    jmp     L3726
L3725:
; else
; {
; RPN'ized expression: "( L3731 printf ) "
; Expanded expression: " L3731  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3731:
    db  10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3731 , printf )2 "
    push    L3731
    call    _printf
    sub     sp, -2
; RPN'ized expression: "ParseLevel ++p "
; Expanded expression: "ParseLevel ++p(2) "
; Fused expression:    "++p(2) *ParseLevel "
    mov     ax, [_ParseLevel]
    inc     word [_ParseLevel]
; RPN'ized expression: "( 1 , i ShowDecl ) "
; Expanded expression: " 1  (@-2) *(2)  ShowDecl ()4 "
; Fused expression:    "( 1 , *(2) (@-2) , ShowDecl )4 "
    push    1
    push    word [bp-2]
    call    _ShowDecl
    sub     sp, -4
; RPN'ized expression: "ParseLevel --p "
; Expanded expression: "ParseLevel --p(2) "
; Fused expression:    "--p(2) *ParseLevel "
    mov     ax, [_ParseLevel]
    dec     word [_ParseLevel]
; }
L3726:
; RPN'ized expression: "i j 1 - = "
; Expanded expression: "(@-2) (@-12) *(2) 1 - =(2) "
; Fused expression:    "- *(@-12) 1 =(34) *(@-2) ax "
    mov     ax, [bp-12]
    sub     ax, 1
    mov     [bp-2], ax
; if
; RPN'ized expression: "noparams 0 == "
; Expanded expression: "(@-10) *(2) 0 == "
; Fused expression:    "== *(@-10) 0 IF! "
    mov     ax, [bp-10]
    cmp     ax, 0
    jne     L3733
; {
; RPN'ized expression: "( L3735 printf ) "
; Expanded expression: " L3735  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3735:
    db  "; ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3735 , printf )2 "
    push    L3735
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( L3737 printf ) "
; Expanded expression: " L3737  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3737:
    db  "    ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3737 , printf )2 "
    push    L3737
    call    _printf
    sub     sp, -2
; {
; loc                         j : (@-16): int
    sub     sp, 2
; for
; RPN'ized expression: "j 0 = "
; Expanded expression: "(@-16) 0 =(2) "
; Fused expression:    "=(34) *(@-16) 0 "
    mov     ax, 0
    mov     [bp-16], ax
L3739:
; RPN'ized expression: "j ParseLevel 4 * < "
; Expanded expression: "(@-16) *(2) ParseLevel *(2) 4 * < "
; Fused expression:    "* *ParseLevel 4 < *(@-16) ax IF! "
    mov     ax, [_ParseLevel]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, [bp-16]
    cmp     ax, cx
    jge     L3742
    jmp     L3741
L3740:
; RPN'ized expression: "j ++p "
; Expanded expression: "(@-16) ++p(2) "
; Fused expression:    "++p(2) *(@-16) "
    mov     ax, [bp-16]
    inc     word [bp-16]
    jmp     L3739
L3741:
; RPN'ized expression: "( L3743 printf ) "
; Expanded expression: " L3743  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3743:
    db  " ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3743 , printf )2 "
    push    L3743
    call    _printf
    sub     sp, -2
    jmp     L3740
L3742:
    sub     sp, -2
; }
; }
L3733:
; RPN'ized expression: "( L3745 printf ) "
; Expanded expression: " L3745  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3745:
    db  ") ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3745 , printf )2 "
    push    L3745
    call    _printf
    sub     sp, -2
    sub     sp, -6
; }
; break
    jmp     L3665
; case
; RPN'ized expression: "41 "
; Expanded expression: "41 "
; Expression value: 41
    jmp     L3719
L3718:
    cmp     ax, 41
    jne     L3747
L3719:
; return
    jmp     L3658
; default
L3666:
; switch
; RPN'ized expression: "tok "
; Expanded expression: "(@-6) *(2) "
; Fused expression:    "*(2) (@-6) "
    mov     ax, [bp-6]
    jmp     L3751
; {
; case
; RPN'ized expression: "17 "
; Expanded expression: "17 "
; Expression value: 17
    jmp     L3752
L3751:
    cmp     ax, 17
    jne     L3753
L3752:
; case
; RPN'ized expression: "18 "
; Expanded expression: "18 "
; Expression value: 18
    jmp     L3754
L3753:
    cmp     ax, 18
    jne     L3755
L3754:
; case
; RPN'ized expression: "19 "
; Expanded expression: "19 "
; Expression value: 19
    jmp     L3756
L3755:
    cmp     ax, 19
    jne     L3757
L3756:
; case
; RPN'ized expression: "15 "
; Expanded expression: "15 "
; Expression value: 15
    jmp     L3758
L3757:
    cmp     ax, 15
    jne     L3759
L3758:
; RPN'ized expression: "( ( tok GetTokenName ) , L3761 printf ) "
; Expanded expression: "  (@-6) *(2)  GetTokenName ()2  L3761  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3761:
    db  "%s",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( *(2) (@-6) , GetTokenName )2 , L3761 , printf )4 "
    push    word [bp-6]
    call    _GetTokenName
    sub     sp, -2
    push    ax
    push    L3761
    call    _printf
    sub     sp, -4
; break
    jmp     L3749
; default
L3750:
; RPN'ized expression: "( ( tok GetTokenName ) , L3763 printf ) "
; Expanded expression: "  (@-6) *(2)  GetTokenName ()2  L3763  printf ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3763:
    db  "%s ",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( *(2) (@-6) , GetTokenName )2 , L3763 , printf )4 "
    push    word [bp-6]
    call    _GetTokenName
    sub     sp, -2
    push    ax
    push    L3763
    call    _printf
    sub     sp, -4
; break
    jmp     L3749
; }
    jmp     L3749
L3759:
    jmp     L3750
L3749:
; break
    jmp     L3665
; }
    jmp     L3665
L3747:
    jmp     L3666
L3665:
    sub     sp, -4
; }
    jmp     L3662
L3664:
L3658:
    leave
    ret
; SEGMENT _TEXT
; glb DumpSynDecls : (void) void
SEGMENT _TEXT
    global  _DumpSynDecls
_DumpSynDecls:
    push    bp
    mov     bp, sp
; RPN'ized expression: "( L3766 printf ) "
; Expanded expression: " L3766  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3766:
    db  10,"; Syntax/declaration table/stack:",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3766 , printf )2 "
    push    L3766
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( 2048 SyntaxStack 0 + *u sizeof * , SyntaxStackCnt SyntaxStack 0 + *u sizeof * , L3768 printf ) "
; Expanded expression: " 8192  SyntaxStackCnt *(2) 4 *  L3768  printf ()6 "
; SEGMENT _TEXT
SEGMENT _DATA
L3768:
    db  "; Bytes used: %d/%d",10,10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( 8192 , * *SyntaxStackCnt 4 , L3768 , printf )6 "
    push    8192
    mov     ax, [_SyntaxStackCnt]
    imul    ax, ax, 4
    push    ax
    push    L3768
    call    _printf
    sub     sp, -6
L3765:
    leave
    ret
; SEGMENT _TEXT
; glb ParseArrayDimension : (void) int
SEGMENT _TEXT
    global  _ParseArrayDimension
_ParseArrayDimension:
    push    bp
    mov     bp, sp
; loc     tok : (@-2): int
    sub     sp, 2
; loc     gotUnary : (@-4): int
    sub     sp, 2
; loc     synPtr : (@-6): int
    sub     sp, 2
; loc     constExpr : (@-8): int
    sub     sp, 2
; loc     exprVal : (@-10): int
    sub     sp, 2
; loc     oldssp : (@-12): int
    sub     sp, 2
; loc     oldesp : (@-14): int
    sub     sp, 2
; loc     undoIdents : (@-16): int
    sub     sp, 2
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@-2)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@-2) ax "
    call    _GetToken
    mov     [bp-2], ax
; RPN'ized expression: "oldssp SyntaxStackCnt = "
; Expanded expression: "(@-12) SyntaxStackCnt *(2) =(2) "
; Fused expression:    "=(34) *(@-12) *SyntaxStackCnt "
    mov     ax, [_SyntaxStackCnt]
    mov     [bp-12], ax
; RPN'ized expression: "oldesp sp = "
; Expanded expression: "(@-14) sp *(2) =(2) "
; Fused expression:    "=(34) *(@-14) *sp "
    mov     ax, [_sp]
    mov     [bp-14], ax
; RPN'ized expression: "undoIdents IdentTableLen = "
; Expanded expression: "(@-16) IdentTableLen *(2) =(2) "
; Fused expression:    "=(34) *(@-16) *IdentTableLen "
    mov     ax, [_IdentTableLen]
    mov     [bp-16], ax
; RPN'ized expression: "tok ( exprVal &u , constExpr &u , synPtr &u , gotUnary &u , tok ParseExpr ) = "
; Expanded expression: "(@-2)  (@-10)  (@-8)  (@-6)  (@-4)  (@-2) *(2)  ParseExpr ()10 =(2) "
; Fused expression:    "( (@-10) , (@-8) , (@-6) , (@-4) , *(2) (@-2) , ParseExpr )10 =(34) *(@-2) ax "
    lea     ax, [bp-10]
    push    ax
    lea     ax, [bp-8]
    push    ax
    lea     ax, [bp-6]
    push    ax
    lea     ax, [bp-4]
    push    ax
    push    word [bp-2]
    call    _ParseExpr
    sub     sp, -10
    mov     [bp-2], ax
; RPN'ized expression: "IdentTableLen undoIdents = "
; Expanded expression: "IdentTableLen (@-16) *(2) =(2) "
; Fused expression:    "=(34) *IdentTableLen *(@-16) "
    mov     ax, [bp-16]
    mov     [_IdentTableLen], ax
; RPN'ized expression: "SyntaxStackCnt oldssp = "
; Expanded expression: "SyntaxStackCnt (@-12) *(2) =(2) "
; Fused expression:    "=(34) *SyntaxStackCnt *(@-12) "
    mov     ax, [bp-12]
    mov     [_SyntaxStackCnt], ax
; RPN'ized expression: "sp oldesp = "
; Expanded expression: "sp (@-14) *(2) =(2) "
; Fused expression:    "=(34) *sp *(@-14) "
    mov     ax, [bp-14]
    mov     [_sp], ax
; if
; RPN'ized expression: "tok 93 != "
; Expanded expression: "(@-2) *(2) 93 != "
; Fused expression:    "!= *(@-2) 93 IF! "
    mov     ax, [bp-2]
    cmp     ax, 93
    je      L3771
; RPN'ized expression: "( ( tok GetTokenName ) , L3773 error ) "
; Expanded expression: "  (@-2) *(2)  GetTokenName ()2  L3773  error ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3773:
    db  "Error: ParseArrayDimension(): Unsupported or invalid array dimension (token %s)",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( *(2) (@-2) , GetTokenName )2 , L3773 , error )4 "
    push    word [bp-2]
    call    _GetTokenName
    sub     sp, -2
    push    ax
    push    L3773
    call    _error
    sub     sp, -4
L3771:
; if
; RPN'ized expression: "constExpr 0 == "
; Expanded expression: "(@-8) *(2) 0 == "
; Fused expression:    "== *(@-8) 0 IF! "
    mov     ax, [bp-8]
    cmp     ax, 0
    jne     L3775
; RPN'ized expression: "( L3777 error ) "
; Expanded expression: " L3777  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3777:
    db  "Error: ParseArrayDimension(): non-constant array dimension",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3777 , error )2 "
    push    L3777
    call    _error
    sub     sp, -2
L3775:
; if
; RPN'ized expression: "exprVal 1 < "
; Expanded expression: "(@-10) *(2) 1 < "
; Fused expression:    "< *(@-10) 1 IF! "
    mov     ax, [bp-10]
    cmp     ax, 1
    jge     L3779
; RPN'ized expression: "( L3781 error ) "
; Expanded expression: " L3781  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3781:
    db  "Error: ParseArrayDimension(): array dimension less than 1",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3781 , error )2 "
    push    L3781
    call    _error
    sub     sp, -2
L3779:
; RPN'ized expression: "( exprVal , 1 PushSyntax2 ) "
; Expanded expression: " (@-10) *(2)  1  PushSyntax2 ()4 "
; Fused expression:    "( *(2) (@-10) , 1 , PushSyntax2 )4 "
    push    word [bp-10]
    push    1
    call    _PushSyntax2
    sub     sp, -4
; return
; RPN'ized expression: "tok "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
    mov     ax, [bp-2]
    jmp     L3770
L3770:
    leave
    ret
; SEGMENT _TEXT
; glb ParseFxnParams : (void) void
; RPN'ized expression: "6 "
; Expanded expression: "6 "
; Expression value: 6
; glb ParseBlock : (
; prm     BrkCntSwchTarget : * int
; prm     switchBody : int
;     ) int
; glb AddFxnParamSymbols : (
; prm     SyntaxPtr : int
;     ) void
; glb ParseDerived : (void) int
SEGMENT _TEXT
    global  _ParseDerived
_ParseDerived:
    push    bp
    mov     bp, sp
; loc     tok : (@-2): int
    sub     sp, 2
; loc     stars : (@-4): int
    sub     sp, 2
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "=(34) *(@-4) 0 "
    mov     ax, 0
    mov     [bp-4], ax
; loc     lastSyntaxPtr : (@-6): int
    sub     sp, 2
; =
; RPN'ized expression: "SyntaxStackCnt "
; Expanded expression: "SyntaxStackCnt *(2) "
; Fused expression:    "=(34) *(@-6) *SyntaxStackCnt "
    mov     ax, [_SyntaxStackCnt]
    mov     [bp-6], ax
; while
; RPN'ized expression: "tok ( GetToken ) = 42 == "
; Expanded expression: "(@-2)  GetToken ()0 =(2) 42 == "
L3784:
; Fused expression:    "( GetToken )0 =(34) *(@-2) ax == ax 42 IF! "
    call    _GetToken
    mov     [bp-2], ax
    cmp     ax, 42
    jne     L3785
; RPN'ized expression: "stars ++p "
; Expanded expression: "(@-4) ++p(2) "
; Fused expression:    "++p(2) *(@-4) "
    mov     ax, [bp-4]
    inc     word [bp-4]
    jmp     L3784
L3785:
; if
; RPN'ized expression: "tok 40 == "
; Expanded expression: "(@-2) *(2) 40 == "
; Fused expression:    "== *(@-2) 40 IF! "
    mov     ax, [bp-2]
    cmp     ax, 40
    jne     L3786
; {
; RPN'ized expression: "tok ( ParseDerived ) = "
; Expanded expression: "(@-2)  ParseDerived ()0 =(2) "
; Fused expression:    "( ParseDerived )0 =(34) *(@-2) ax "
    call    _ParseDerived
    mov     [bp-2], ax
; if
; RPN'ized expression: "tok 41 != "
; Expanded expression: "(@-2) *(2) 41 != "
; Fused expression:    "!= *(@-2) 41 IF! "
    mov     ax, [bp-2]
    cmp     ax, 41
    je      L3788
; RPN'ized expression: "( L3790 error ) "
; Expanded expression: " L3790  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3790:
    db  "Error: ParseDerived(): ')' expected",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3790 , error )2 "
    push    L3790
    call    _error
    sub     sp, -2
L3788:
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@-2)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@-2) ax "
    call    _GetToken
    mov     [bp-2], ax
; }
    jmp     L3787
L3786:
; else
; if
; RPN'ized expression: "tok 16 == "
; Expanded expression: "(@-2) *(2) 16 == "
; Fused expression:    "== *(@-2) 16 IF! "
    mov     ax, [bp-2]
    cmp     ax, 16
    jne     L3792
; {
; RPN'ized expression: "( ( ( GetTokenIdentName ) AddIdent ) , tok PushSyntax2 ) "
; Expanded expression: "   GetTokenIdentName ()0  AddIdent ()2  (@-2) *(2)  PushSyntax2 ()4 "
; Fused expression:    "( ( ( GetTokenIdentName )0 , AddIdent )2 , *(2) (@-2) , PushSyntax2 )4 "
    call    _GetTokenIdentName
    push    ax
    call    _AddIdent
    sub     sp, -2
    push    ax
    push    word [bp-2]
    call    _PushSyntax2
    sub     sp, -4
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@-2)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@-2) ax "
    call    _GetToken
    mov     [bp-2], ax
; }
    jmp     L3793
L3792:
; else
; {
; RPN'ized expression: "( ( L3794 AddIdent ) , 16 PushSyntax2 ) "
; Expanded expression: "  L3794  AddIdent ()2  16  PushSyntax2 ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3794:
    db  "<something>",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( L3794 , AddIdent )2 , 16 , PushSyntax2 )4 "
    push    L3794
    call    _AddIdent
    sub     sp, -2
    push    ax
    push    16
    call    _PushSyntax2
    sub     sp, -4
; }
L3793:
L3787:
; if
; RPN'ized expression: "tok 91 == "
; Expanded expression: "(@-2) *(2) 91 == "
; Fused expression:    "== *(@-2) 91 IF! "
    mov     ax, [bp-2]
    cmp     ax, 91
    jne     L3796
; {
; while
; RPN'ized expression: "tok 91 == "
; Expanded expression: "(@-2) *(2) 91 == "
L3798:
; Fused expression:    "== *(@-2) 91 IF! "
    mov     ax, [bp-2]
    cmp     ax, 91
    jne     L3799
; {
; loc             oldsp : (@-8): int
    sub     sp, 2
; =
; RPN'ized expression: "SyntaxStackCnt "
; Expanded expression: "SyntaxStackCnt *(2) "
; Fused expression:    "=(34) *(@-8) *SyntaxStackCnt "
    mov     ax, [_SyntaxStackCnt]
    mov     [bp-8], ax
; RPN'ized expression: "( 17 PushSyntax ) "
; Expanded expression: " 17  PushSyntax ()2 "
; Fused expression:    "( 17 , PushSyntax )2 "
    push    17
    call    _PushSyntax
    sub     sp, -2
; RPN'ized expression: "( tok PushSyntax ) "
; Expanded expression: " (@-2) *(2)  PushSyntax ()2 "
; Fused expression:    "( *(2) (@-2) , PushSyntax )2 "
    push    word [bp-2]
    call    _PushSyntax
    sub     sp, -2
; RPN'ized expression: "tok ( ParseArrayDimension ) = "
; Expanded expression: "(@-2)  ParseArrayDimension ()0 =(2) "
; Fused expression:    "( ParseArrayDimension )0 =(34) *(@-2) ax "
    call    _ParseArrayDimension
    mov     [bp-2], ax
; if
; RPN'ized expression: "tok 93 != "
; Expanded expression: "(@-2) *(2) 93 != "
; Fused expression:    "!= *(@-2) 93 IF! "
    mov     ax, [bp-2]
    cmp     ax, 93
    je      L3800
; RPN'ized expression: "( L3802 error ) "
; Expanded expression: " L3802  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3802:
    db  "Error: ParseDerived(): ']' expected",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3802 , error )2 "
    push    L3802
    call    _error
    sub     sp, -2
L3800:
; RPN'ized expression: "( 93 PushSyntax ) "
; Expanded expression: " 93  PushSyntax ()2 "
; Fused expression:    "( 93 , PushSyntax )2 "
    push    93
    call    _PushSyntax
    sub     sp, -2
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@-2)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@-2) ax "
    call    _GetToken
    mov     [bp-2], ax
; RPN'ized expression: "( 1 , oldsp DeleteSyntax ) "
; Expanded expression: " 1  (@-8) *(2)  DeleteSyntax ()4 "
; Fused expression:    "( 1 , *(2) (@-8) , DeleteSyntax )4 "
    push    1
    push    word [bp-8]
    call    _DeleteSyntax
    sub     sp, -4
    sub     sp, -2
; }
    jmp     L3798
L3799:
; }
    jmp     L3797
L3796:
; else
; if
; RPN'ized expression: "tok 40 == "
; Expanded expression: "(@-2) *(2) 40 == "
; Fused expression:    "== *(@-2) 40 IF! "
    mov     ax, [bp-2]
    cmp     ax, 40
    jne     L3804
; {
; RPN'ized expression: "( tok PushSyntax ) "
; Expanded expression: " (@-2) *(2)  PushSyntax ()2 "
; Fused expression:    "( *(2) (@-2) , PushSyntax )2 "
    push    word [bp-2]
    call    _PushSyntax
    sub     sp, -2
; RPN'ized expression: "ParseLevel ++p "
; Expanded expression: "ParseLevel ++p(2) "
; Fused expression:    "++p(2) *ParseLevel "
    mov     ax, [_ParseLevel]
    inc     word [_ParseLevel]
; RPN'ized expression: "( ParseFxnParams ) "
; Expanded expression: " ParseFxnParams ()0 "
; Fused expression:    "( ParseFxnParams )0 "
    call    _ParseFxnParams
; RPN'ized expression: "ParseLevel --p "
; Expanded expression: "ParseLevel --p(2) "
; Fused expression:    "--p(2) *ParseLevel "
    mov     ax, [_ParseLevel]
    dec     word [_ParseLevel]
; RPN'ized expression: "( 41 PushSyntax ) "
; Expanded expression: " 41  PushSyntax ()2 "
; Fused expression:    "( 41 , PushSyntax )2 "
    push    41
    call    _PushSyntax
    sub     sp, -2
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@-2)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@-2) ax "
    call    _GetToken
    mov     [bp-2], ax
; }
L3804:
L3797:
; while
; RPN'ized expression: "stars --p "
; Expanded expression: "(@-4) --p(2) "
L3806:
; Fused expression:    "--p(2) *(@-4) "
    mov     ax, [bp-4]
    dec     word [bp-4]
; JumpIfZero
    test    ax, ax
    jz      L3807
; RPN'ized expression: "( 42 PushSyntax ) "
; Expanded expression: " 42  PushSyntax ()2 "
; Fused expression:    "( 42 , PushSyntax )2 "
    push    42
    call    _PushSyntax
    sub     sp, -2
    jmp     L3806
L3807:
; if
; RPN'ized expression: "tok 41 == "
; Expanded expression: "(@-2) *(2) 41 == "
; Fused expression:    "== *(@-2) 41 IF! "
    mov     ax, [bp-2]
    cmp     ax, 41
    jne     L3808
; return
; RPN'ized expression: "tok "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
    mov     ax, [bp-2]
    jmp     L3783
L3808:
; if
; RPN'ized expression: "tok 123 == "
; Expanded expression: "(@-2) *(2) 123 == "
; Fused expression:    "== *(@-2) 123 IF! "
    mov     ax, [bp-2]
    cmp     ax, 123
    jne     L3810
; {
; loc         fxn : (@-8): int
    sub     sp, 2
; =
; RPN'ized expression: "lastSyntaxPtr 1 + SyntaxStackCnt < SyntaxStack lastSyntaxPtr 1 + + *u 0 + *u 40 == && "
; Expanded expression: "(@-6) *(2) 1 + SyntaxStackCnt *(2) < _Bool [sh&&->3812] SyntaxStack (@-6) *(2) 1 + 4 * + 0 + *(2) 40 == _Bool &&[3812] "
; Fused expression:    "+ *(@-6) 1 < ax *SyntaxStackCnt _Bool [sh&&->3812] + *(@-6) 1 * ax 4 + SyntaxStack ax + ax 0 == *ax 40 _Bool &&[3812] =(34) *(@-8) ax "
    mov     ax, [bp-6]
    add     ax, 1
    cmp     ax, [_SyntaxStackCnt]
    setl    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3812
    mov     ax, [bp-6]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 40
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3812:
    mov     [bp-8], ax
; if
; RPN'ized expression: "fxn 0 == ExprLevel || "
; Expanded expression: "(@-8) *(2) 0 == _Bool [sh||->3815] ExprLevel *(2) _Bool ||[3815] "
; Fused expression:    "== *(@-8) 0 _Bool [sh||->3815] *(2) ExprLevel _Bool ||[3815] "
    mov     ax, [bp-8]
    cmp     ax, 0
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L3815
    mov     ax, [_ExprLevel]
    test    ax, ax
    setnz   al
    cbw
L3815:
; JumpIfZero
    test    ax, ax
    jz      L3813
; RPN'ized expression: "( L3816 error ) "
; Expanded expression: " L3816  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3816:
    db  "Error: ParseDerived(): '{' unexpected",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3816 , error )2 "
    push    L3816
    call    _error
    sub     sp, -2
L3813:
; if
; RPN'ized expression: "ParseLevel "
; Expanded expression: "ParseLevel *(2) "
; Fused expression:    "*(2) ParseLevel "
    mov     ax, [_ParseLevel]
; JumpIfZero
    test    ax, ax
    jz      L3818
; RPN'ized expression: "( L3820 error ) "
; Expanded expression: " L3820  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3820:
    db  "Error: ParseDerived(): Cannot define a nested function",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3820 , error )2 "
    push    L3820
    call    _error
    sub     sp, -2
L3818:
    sub     sp, -2
; }
L3810:
; if
; RPN'ized expression: "tok 0 == ( tok , L3824 strchr ) 0 == || "
; Expanded expression: "(@-2) *(2) 0 == _Bool [sh||->3826]  (@-2) *(2)  L3824  strchr ()4 0 == _Bool ||[3826] "
; SEGMENT _TEXT
SEGMENT _DATA
L3824:
    db  ",;{=",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "== *(@-2) 0 _Bool [sh||->3826] ( *(2) (@-2) , L3824 , strchr )4 == ax 0 _Bool ||[3826] "
    mov     ax, [bp-2]
    cmp     ax, 0
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L3826
    push    word [bp-2]
    push    L3824
    call    _strchr
    sub     sp, -4
    cmp     ax, 0
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3826:
; JumpIfZero
    test    ax, ax
    jz      L3822
; RPN'ized expression: "( ( tok GetTokenName ) , L3827 error ) "
; Expanded expression: "  (@-2) *(2)  GetTokenName ()2  L3827  error ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3827:
    db  "Error: ParseDerived(): unexpected token %s",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( *(2) (@-2) , GetTokenName )2 , L3827 , error )4 "
    push    word [bp-2]
    call    _GetTokenName
    sub     sp, -2
    push    ax
    push    L3827
    call    _error
    sub     sp, -4
L3822:
; return
; RPN'ized expression: "tok "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
    mov     ax, [bp-2]
    jmp     L3783
L3783:
    leave
    ret
; SEGMENT _TEXT
; glb ParseDecl : (
; prm     tok : int
;     ) int
SEGMENT _TEXT
    global  _ParseDecl
_ParseDecl:
    push    bp
    mov     bp, sp
; loc     tok : (@4): int
; loc     base : (@-2): int
    sub     sp, 2
; loc     lastSyntaxPtr : (@-4): int
    sub     sp, 2
; loc     external : (@-6): int
    sub     sp, 2
; =
; RPN'ized expression: "tok 108 == "
; Expanded expression: "(@4) *(2) 108 == "
; Fused expression:    "== *(@4) 108 =(34) *(@-6) ax "
    mov     ax, [bp+4]
    cmp     ax, 108
    sete    al
    cbw
    mov     [bp-6], ax
; if
; RPN'ized expression: "external "
; Expanded expression: "(@-6) *(2) "
; Fused expression:    "*(2) (@-6) "
    mov     ax, [bp-6]
; JumpIfZero
    test    ax, ax
    jz      L3830
; {
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
; if
; RPN'ized expression: "( 1 , tok TokenStartsDeclaration ) 0 == "
; Expanded expression: " 1  (@4) *(2)  TokenStartsDeclaration ()4 0 == "
; Fused expression:    "( 1 , *(2) (@4) , TokenStartsDeclaration )4 == ax 0 IF! "
    push    1
    push    word [bp+4]
    call    _TokenStartsDeclaration
    sub     sp, -4
    cmp     ax, 0
    jne     L3832
; RPN'ized expression: "( ( tok GetTokenName ) , L3834 error ) "
; Expanded expression: "  (@4) *(2)  GetTokenName ()2  L3834  error ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3834:
    db  "Error: ParseDecl(): unexpected token %s",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( *(2) (@4) , GetTokenName )2 , L3834 , error )4 "
    push    word [bp+4]
    call    _GetTokenName
    sub     sp, -2
    push    ax
    push    L3834
    call    _error
    sub     sp, -4
L3832:
; }
L3830:
; RPN'ized expression: "base tok = "
; Expanded expression: "(@-2) (@4) *(2) =(2) "
; Fused expression:    "=(34) *(@-2) *(@4) "
    mov     ax, [bp+4]
    mov     [bp-2], ax
; for
L3836:
    jmp     L3838
L3837:
    jmp     L3836
L3838:
; {
; RPN'ized expression: "lastSyntaxPtr SyntaxStackCnt = "
; Expanded expression: "(@-4) SyntaxStackCnt *(2) =(2) "
; Fused expression:    "=(34) *(@-4) *SyntaxStackCnt "
    mov     ax, [_SyntaxStackCnt]
    mov     [bp-4], ax
; RPN'ized expression: "tok ( ParseDerived ) = "
; Expanded expression: "(@4)  ParseDerived ()0 =(2) "
; Fused expression:    "( ParseDerived )0 =(34) *(@4) ax "
    call    _ParseDerived
    mov     [bp+4], ax
; RPN'ized expression: "( base PushSyntax ) "
; Expanded expression: " (@-2) *(2)  PushSyntax ()2 "
; Fused expression:    "( *(2) (@-2) , PushSyntax )2 "
    push    word [bp-2]
    call    _PushSyntax
    sub     sp, -2
; if
; RPN'ized expression: "tok ( tok , L3842 strchr ) && tok 41 == ExprLevel && || "
; Expanded expression: "(@4) *(2) _Bool [sh&&->3846]  (@4) *(2)  L3842  strchr ()4 _Bool &&[3846] _Bool [sh||->3844] (@4) *(2) 41 == _Bool [sh&&->3845] ExprLevel *(2) _Bool &&[3845] _Bool ||[3844] "
; SEGMENT _TEXT
SEGMENT _DATA
L3842:
    db  ",;{=",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "*(2) (@4) _Bool [sh&&->3846] ( *(2) (@4) , L3842 , strchr )4 _Bool &&[3846] _Bool [sh||->3844] == *(@4) 41 _Bool [sh&&->3845] *(2) ExprLevel _Bool &&[3845] _Bool ||[3844] "
    mov     ax, [bp+4]
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3846
    push    word [bp+4]
    push    L3842
    call    _strchr
    sub     sp, -4
    test    ax, ax
    setnz   al
    cbw
L3846:
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L3844
    mov     ax, [bp+4]
    cmp     ax, 41
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3845
    mov     ax, [_ExprLevel]
    test    ax, ax
    setnz   al
    cbw
L3845:
    test    ax, ax
    setnz   al
    cbw
L3844:
; JumpIfZero
    test    ax, ax
    jz      L3840
; {
; loc             localAllocSize : (@-8): int
    sub     sp, 2
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "=(34) *(@-8) 0 "
    mov     ax, 0
    mov     [bp-8], ax
; loc             globalAllocSize : (@-10): int
    sub     sp, 2
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "=(34) *(@-10) 0 "
    mov     ax, 0
    mov     [bp-10], ax
; if
; RPN'ized expression: "base 17 == "
; Expanded expression: "(@-2) *(2) 17 == "
; Fused expression:    "== *(@-2) 17 IF! "
    mov     ax, [bp-2]
    cmp     ax, 17
    jne     L3847
; {
; loc                 t : (@-12): int
    sub     sp, 2
; =
; RPN'ized expression: "SyntaxStack SyntaxStackCnt 2 - + *u 0 + *u "
; Expanded expression: "SyntaxStack SyntaxStackCnt *(2) 2 - 4 * + 0 + *(2) "
; Fused expression:    "- *SyntaxStackCnt 2 * ax 4 + SyntaxStack ax + ax 0 =(34) *(@-12) *ax "
    mov     ax, [_SyntaxStackCnt]
    sub     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-12], ax
; if
; RPN'ized expression: "t 42 != t 41 != && "
; Expanded expression: "(@-12) *(2) 42 != _Bool [sh&&->3851] (@-12) *(2) 41 != _Bool &&[3851] "
; Fused expression:    "!= *(@-12) 42 _Bool [sh&&->3851] != *(@-12) 41 _Bool &&[3851] "
    mov     ax, [bp-12]
    cmp     ax, 42
    setne   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3851
    mov     ax, [bp-12]
    cmp     ax, 41
    setne   al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3851:
; JumpIfZero
    test    ax, ax
    jz      L3849
; RPN'ized expression: "( IdentTable SyntaxStack lastSyntaxPtr + *u 1 + *u + , L3852 error ) "
; Expanded expression: " IdentTable SyntaxStack (@-4) *(2) 4 * + 2 + *(2) +  L3852  error ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3852:
    db  "Error: ParseDecl(): Cannot declare a variable ('%s') of type 'void'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( * *(@-4) 4 + SyntaxStack ax + ax 2 + IdentTable *ax , L3852 , error )4 "
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, _IdentTable
    add     ax, cx
    push    ax
    push    L3852
    call    _error
    sub     sp, -4
L3849:
    sub     sp, -2
; }
L3847:
; if
; RPN'ized expression: "SyntaxStack lastSyntaxPtr 1 + + *u 0 + *u 40 != "
; Expanded expression: "SyntaxStack (@-4) *(2) 1 + 4 * + 0 + *(2) 40 != "
; Fused expression:    "+ *(@-4) 1 * ax 4 + SyntaxStack ax + ax 0 != *ax 40 IF! "
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 40
    je      L3854
; {
; loc                 sz : (@-12): int
    sub     sp, 2
; =
; RPN'ized expression: "( lastSyntaxPtr GetDeclSize ) "
; Expanded expression: " (@-4) *(2)  GetDeclSize ()2 "
; Fused expression:    "( *(2) (@-4) , GetDeclSize )2 =(34) *(@-12) ax "
    push    word [bp-4]
    call    _GetDeclSize
    sub     sp, -2
    mov     [bp-12], ax
; if
; RPN'ized expression: "sz 0 <= "
; Expanded expression: "(@-12) *(2) 0 <= "
; Fused expression:    "<= *(@-12) 0 IF! "
    mov     ax, [bp-12]
    cmp     ax, 0
    jg      L3856
; RPN'ized expression: "( L3858 error ) "
; Expanded expression: " L3858  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3858:
    db  "Error: ParseDecl(): GetDeclSize() <= 0 (incomplete types aren't supported)",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3858 , error )2 "
    push    L3858
    call    _error
    sub     sp, -2
L3856:
; if
; RPN'ized expression: "ParseLevel external 0 == && ExprLevel 0 == && "
; Expanded expression: "ParseLevel *(2) _Bool [sh&&->3863] (@-6) *(2) 0 == _Bool &&[3863] _Bool [sh&&->3862] ExprLevel *(2) 0 == _Bool &&[3862] "
; Fused expression:    "*(2) ParseLevel _Bool [sh&&->3863] == *(@-6) 0 _Bool &&[3863] _Bool [sh&&->3862] == *ExprLevel 0 _Bool &&[3862] "
    mov     ax, [_ParseLevel]
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3863
    mov     ax, [bp-6]
    cmp     ax, 0
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3863:
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3862
    mov     ax, [_ExprLevel]
    cmp     ax, 0
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3862:
; JumpIfZero
    test    ax, ax
    jz      L3860
; {
; loc                     oldOfs : (@-14): int
    sub     sp, 2
; RPN'ized expression: "oldOfs CurFxnLocalOfs = "
; Expanded expression: "(@-14) CurFxnLocalOfs *(2) =(2) "
; Fused expression:    "=(34) *(@-14) *CurFxnLocalOfs "
    mov     ax, [_CurFxnLocalOfs]
    mov     [bp-14], ax
; RPN'ized expression: "CurFxnLocalOfs sz -= "
; Expanded expression: "CurFxnLocalOfs (@-12) *(2) -=(2) "
; Fused expression:    "-=(34) *CurFxnLocalOfs *(@-12) "
    mov     ax, [_CurFxnLocalOfs]
    sub     ax, [bp-12]
    mov     [_CurFxnLocalOfs], ax
; RPN'ized expression: "CurFxnLocalOfs CurFxnLocalOfs -u SizeOfWord + 1 - SizeOfWord / SizeOfWord * -u = "
; Expanded expression: "CurFxnLocalOfs CurFxnLocalOfs *(2) -u SizeOfWord *(2) + 1 - SizeOfWord *(2) / SizeOfWord *(2) * -u =(2) "
; Fused expression:    "*(2) CurFxnLocalOfs -u + ax *SizeOfWord - ax 1 / ax *SizeOfWord * ax *SizeOfWord -u =(34) *CurFxnLocalOfs ax "
    mov     ax, [_CurFxnLocalOfs]
    neg     ax
    add     ax, [_SizeOfWord]
    sub     ax, 1
    cwd
    idiv    word [_SizeOfWord]
    mul     word [_SizeOfWord]
    neg     ax
    mov     [_CurFxnLocalOfs], ax
; RPN'ized expression: "( CurFxnLocalOfs , 89 , lastSyntaxPtr 1 + InsertSyntax2 ) "
; Expanded expression: " CurFxnLocalOfs *(2)  89  (@-4) *(2) 1 +  InsertSyntax2 ()6 "
; Fused expression:    "( *(2) CurFxnLocalOfs , 89 , + *(@-4) 1 , InsertSyntax2 )6 "
    push    word [_CurFxnLocalOfs]
    push    89
    mov     ax, [bp-4]
    add     ax, 1
    push    ax
    call    _InsertSyntax2
    sub     sp, -6
; RPN'ized expression: "localAllocSize oldOfs CurFxnLocalOfs - = "
; Expanded expression: "(@-8) (@-14) *(2) CurFxnLocalOfs *(2) - =(2) "
; Fused expression:    "- *(@-14) *CurFxnLocalOfs =(34) *(@-8) ax "
    mov     ax, [bp-14]
    sub     ax, [_CurFxnLocalOfs]
    mov     [bp-8], ax
    sub     sp, -2
; }
    jmp     L3861
L3860:
; else
; {
; RPN'ized expression: "globalAllocSize sz = "
; Expanded expression: "(@-10) (@-12) *(2) =(2) "
; Fused expression:    "=(34) *(@-10) *(@-12) "
    mov     ax, [bp-12]
    mov     [bp-10], ax
; }
L3861:
    sub     sp, -2
; }
L3854:
; if
; RPN'ized expression: "( L3866 , IdentTable SyntaxStack lastSyntaxPtr + *u 1 + *u + strcmp ) 0 == "
; Expanded expression: " L3866  IdentTable SyntaxStack (@-4) *(2) 4 * + 2 + *(2) +  strcmp ()4 0 == "
; SEGMENT _TEXT
SEGMENT _DATA
L3866:
    db  "<something>",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3866 , * *(@-4) 4 + SyntaxStack ax + ax 2 + IdentTable *ax , strcmp )4 == ax 0 IF! "
    push    L3866
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, _IdentTable
    add     ax, cx
    push    ax
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    jne     L3864
; {
; if
; RPN'ized expression: "ExprLevel 0 == "
; Expanded expression: "ExprLevel *(2) 0 == "
; Fused expression:    "== *ExprLevel 0 IF! "
    mov     ax, [_ExprLevel]
    cmp     ax, 0
    jne     L3868
; RPN'ized expression: "( L3870 error ) "
; Expanded expression: " L3870  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3870:
    db  "Error: ParseDecl(): Identifier name expected",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3870 , error )2 "
    push    L3870
    call    _error
    sub     sp, -2
L3868:
; }
    jmp     L3865
L3864:
; else
; {
; if
; RPN'ized expression: "ExprLevel "
; Expanded expression: "ExprLevel *(2) "
; Fused expression:    "*(2) ExprLevel "
    mov     ax, [_ExprLevel]
; JumpIfZero
    test    ax, ax
    jz      L3872
; RPN'ized expression: "( L3874 error ) "
; Expanded expression: " L3874  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3874:
    db  "Error: ParseDecl(): Identifier name unexpected",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3874 , error )2 "
    push    L3874
    call    _error
    sub     sp, -2
L3872:
; }
L3865:
; RPN'ized expression: "( 0 , lastSyntaxPtr ShowDecl ) "
; Expanded expression: " 0  (@-4) *(2)  ShowDecl ()4 "
; Fused expression:    "( 0 , *(2) (@-4) , ShowDecl )4 "
    push    0
    push    word [bp-4]
    call    _ShowDecl
    sub     sp, -4
; if
; RPN'ized expression: "ExprLevel "
; Expanded expression: "ExprLevel *(2) "
; Fused expression:    "*(2) ExprLevel "
    mov     ax, [_ExprLevel]
; JumpIfZero
    test    ax, ax
    jz      L3876
; return
; RPN'ized expression: "tok "
; Expanded expression: "(@4) *(2) "
; Fused expression:    "*(2) (@4) "
    mov     ax, [bp+4]
    jmp     L3829
L3876:
; if
; RPN'ized expression: "localAllocSize "
; Expanded expression: "(@-8) *(2) "
; Fused expression:    "*(2) (@-8) "
    mov     ax, [bp-8]
; JumpIfZero
    test    ax, ax
    jz      L3878
; RPN'ized expression: "( localAllocSize GenLocalAlloc ) "
; Expanded expression: " (@-8) *(2)  GenLocalAlloc ()2 "
; Fused expression:    "( *(2) (@-8) , GenLocalAlloc )2 "
    push    word [bp-8]
    call    _GenLocalAlloc
    sub     sp, -2
L3878:
; if
; RPN'ized expression: "globalAllocSize external 0 == && "
; Expanded expression: "(@-10) *(2) _Bool [sh&&->3882] (@-6) *(2) 0 == _Bool &&[3882] "
; Fused expression:    "*(2) (@-10) _Bool [sh&&->3882] == *(@-6) 0 _Bool &&[3882] "
    mov     ax, [bp-10]
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3882
    mov     ax, [bp-6]
    cmp     ax, 0
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3882:
; JumpIfZero
    test    ax, ax
    jz      L3880
; {
; if
; RPN'ized expression: "OutputFormat 0 != "
; Expanded expression: "OutputFormat *(2) 0 != "
; Fused expression:    "!= *OutputFormat 0 IF! "
    mov     ax, [_OutputFormat]
    cmp     ax, 0
    je      L3883
; RPN'ized expression: "( DataHeader printf ) "
; Expanded expression: " DataHeader *(2)  printf ()2 "
; Fused expression:    "( *(2) DataHeader , printf )2 "
    push    word [_DataHeader]
    call    _printf
    sub     sp, -2
L3883:
; RPN'ized expression: "( IdentTable SyntaxStack lastSyntaxPtr + *u 1 + *u + GenLabel ) "
; Expanded expression: " IdentTable SyntaxStack (@-4) *(2) 4 * + 2 + *(2) +  GenLabel ()2 "
; Fused expression:    "( * *(@-4) 4 + SyntaxStack ax + ax 2 + IdentTable *ax , GenLabel )2 "
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, _IdentTable
    add     ax, cx
    push    ax
    call    _GenLabel
    sub     sp, -2
; }
L3880:
; if
; RPN'ized expression: "external "
; Expanded expression: "(@-6) *(2) "
; Fused expression:    "*(2) (@-6) "
    mov     ax, [bp-6]
; JumpIfZero
    test    ax, ax
    jz      L3885
; {
; RPN'ized expression: "( IdentTable SyntaxStack lastSyntaxPtr + *u 1 + *u + GenExtern ) "
; Expanded expression: " IdentTable SyntaxStack (@-4) *(2) 4 * + 2 + *(2) +  GenExtern ()2 "
; Fused expression:    "( * *(@-4) 4 + SyntaxStack ax + ax 2 + IdentTable *ax , GenExtern )2 "
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, _IdentTable
    add     ax, cx
    push    ax
    call    _GenExtern
    sub     sp, -2
; }
    jmp     L3886
L3885:
; else
; if
; RPN'ized expression: "tok 61 == "
; Expanded expression: "(@4) *(2) 61 == "
; Fused expression:    "== *(@4) 61 IF! "
    mov     ax, [bp+4]
    cmp     ax, 61
    jne     L3887
; {
; loc                 gotUnary : (@-12): int
    sub     sp, 2
; loc                 synPtr : (@-14): int
    sub     sp, 2
; loc                 constExpr : (@-16): int
    sub     sp, 2
; loc                 exprVal : (@-18): int
    sub     sp, 2
; loc                 p : (@-20): int
    sub     sp, 2
; loc                 oldssp : (@-22): int
    sub     sp, 2
; loc                 undoIdents : (@-24): int
    sub     sp, 2
; RPN'ized expression: "( L3889 printf ) "
; Expanded expression: " L3889  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3889:
    db  "; =",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3889 , printf )2 "
    push    L3889
    call    _printf
    sub     sp, -2
; RPN'ized expression: "p lastSyntaxPtr = "
; Expanded expression: "(@-20) (@-4) *(2) =(2) "
; Fused expression:    "=(34) *(@-20) *(@-4) "
    mov     ax, [bp-4]
    mov     [bp-20], ax
; while
; RPN'ized expression: "SyntaxStack p + *u 0 + *u 16 == SyntaxStack p + *u 0 + *u 89 == || "
; Expanded expression: "SyntaxStack (@-20) *(2) 4 * + 0 + *(2) 16 == _Bool [sh||->3893] SyntaxStack (@-20) *(2) 4 * + 0 + *(2) 89 == _Bool ||[3893] "
L3891:
; Fused expression:    "* *(@-20) 4 + SyntaxStack ax + ax 0 == *ax 16 _Bool [sh||->3893] * *(@-20) 4 + SyntaxStack ax + ax 0 == *ax 89 _Bool ||[3893] "
    mov     ax, [bp-20]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 16
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L3893
    mov     ax, [bp-20]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 89
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3893:
; JumpIfZero
    test    ax, ax
    jz      L3892
; RPN'ized expression: "p ++p "
; Expanded expression: "(@-20) ++p(2) "
; Fused expression:    "++p(2) *(@-20) "
    mov     ax, [bp-20]
    inc     word [bp-20]
    jmp     L3891
L3892:
; RPN'ized expression: "oldssp SyntaxStackCnt = "
; Expanded expression: "(@-22) SyntaxStackCnt *(2) =(2) "
; Fused expression:    "=(34) *(@-22) *SyntaxStackCnt "
    mov     ax, [_SyntaxStackCnt]
    mov     [bp-22], ax
; RPN'ized expression: "undoIdents IdentTableLen = "
; Expanded expression: "(@-24) IdentTableLen *(2) =(2) "
; Fused expression:    "=(34) *(@-24) *IdentTableLen "
    mov     ax, [_IdentTableLen]
    mov     [bp-24], ax
; if
; RPN'ized expression: "( SyntaxStack p + *u 0 + *u , L3896 strchr ) "
; Expanded expression: " SyntaxStack (@-20) *(2) 4 * + 0 + *(2)  L3896  strchr ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3896:
    db  "([",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( * *(@-20) 4 + SyntaxStack ax + ax 0 *(2) ax , L3896 , strchr )4 "
    mov     ax, [bp-20]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    push    word [bx]
    push    L3896
    call    _strchr
    sub     sp, -4
; JumpIfZero
    test    ax, ax
    jz      L3894
; RPN'ized expression: "( L3898 error ) "
; Expanded expression: " L3898  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3898:
    db  "Error: ParseDecl(): invalid/unsupported initialization of array or function",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3898 , error )2 "
    push    L3898
    call    _error
    sub     sp, -2
L3894:
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
; RPN'ized expression: "tok ( exprVal &u , constExpr &u , synPtr &u , gotUnary &u , tok ParseExpr ) = "
; Expanded expression: "(@4)  (@-18)  (@-16)  (@-14)  (@-12)  (@4) *(2)  ParseExpr ()10 =(2) "
; Fused expression:    "( (@-18) , (@-16) , (@-14) , (@-12) , *(2) (@4) , ParseExpr )10 =(34) *(@4) ax "
    lea     ax, [bp-18]
    push    ax
    lea     ax, [bp-16]
    push    ax
    lea     ax, [bp-14]
    push    ax
    lea     ax, [bp-12]
    push    ax
    push    word [bp+4]
    call    _ParseExpr
    sub     sp, -10
    mov     [bp+4], ax
; if
; RPN'ized expression: "tok 0 == ( tok , L3902 strchr ) 0 == || "
; Expanded expression: "(@4) *(2) 0 == _Bool [sh||->3904]  (@4) *(2)  L3902  strchr ()4 0 == _Bool ||[3904] "
; SEGMENT _TEXT
SEGMENT _DATA
L3902:
    db  ",;",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "== *(@4) 0 _Bool [sh||->3904] ( *(2) (@4) , L3902 , strchr )4 == ax 0 _Bool ||[3904] "
    mov     ax, [bp+4]
    cmp     ax, 0
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L3904
    push    word [bp+4]
    push    L3902
    call    _strchr
    sub     sp, -4
    cmp     ax, 0
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3904:
; JumpIfZero
    test    ax, ax
    jz      L3900
; RPN'ized expression: "( ( tok GetTokenName ) , L3905 error ) "
; Expanded expression: "  (@4) *(2)  GetTokenName ()2  L3905  error ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3905:
    db  "Error: ParseDecl(): unexpected token %s after '='",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( *(2) (@4) , GetTokenName )2 , L3905 , error )4 "
    push    word [bp+4]
    call    _GetTokenName
    sub     sp, -2
    push    ax
    push    L3905
    call    _error
    sub     sp, -4
L3900:
; if
; RPN'ized expression: "gotUnary 0 == "
; Expanded expression: "(@-12) *(2) 0 == "
; Fused expression:    "== *(@-12) 0 IF! "
    mov     ax, [bp-12]
    cmp     ax, 0
    jne     L3907
; RPN'ized expression: "( L3909 error ) "
; Expanded expression: " L3909  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3909:
    db  "Error: ParseDecl(): missing initialization expression after '='",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3909 , error )2 "
    push    L3909
    call    _error
    sub     sp, -2
L3907:
; if
; RPN'ized expression: "ParseLevel 0 == "
; Expanded expression: "ParseLevel *(2) 0 == "
; Fused expression:    "== *ParseLevel 0 IF! "
    mov     ax, [_ParseLevel]
    cmp     ax, 0
    jne     L3911
; {
; if
; RPN'ized expression: "constExpr "
; Expanded expression: "(@-16) *(2) "
; Fused expression:    "*(2) (@-16) "
    mov     ax, [bp-16]
; JumpIfZero
    test    ax, ax
    jz      L3913
; {
; RPN'ized expression: "( exprVal , globalAllocSize GenIntData ) "
; Expanded expression: " (@-18) *(2)  (@-10) *(2)  GenIntData ()4 "
; Fused expression:    "( *(2) (@-18) , *(2) (@-10) , GenIntData )4 "
    push    word [bp-18]
    push    word [bp-10]
    call    _GenIntData
    sub     sp, -4
; if
; RPN'ized expression: "OutputFormat 0 != "
; Expanded expression: "OutputFormat *(2) 0 != "
; Fused expression:    "!= *OutputFormat 0 IF! "
    mov     ax, [_OutputFormat]
    cmp     ax, 0
    je      L3915
; RPN'ized expression: "( DataFooter printf ) "
; Expanded expression: " DataFooter *(2)  printf ()2 "
; Fused expression:    "( *(2) DataFooter , printf )2 "
    push    word [_DataFooter]
    call    _printf
    sub     sp, -2
L3915:
; }
    jmp     L3914
L3913:
; else
; if
; RPN'ized expression: "globalAllocSize SizeOfWord == stack sp 1 - + *u 0 + *u 16 == && "
; Expanded expression: "(@-10) *(2) SizeOfWord *(2) == _Bool [sh&&->3919] stack sp *(2) 1 - 4 * + 0 + *(2) 16 == _Bool &&[3919] "
; Fused expression:    "== *(@-10) *SizeOfWord _Bool [sh&&->3919] - *sp 1 * ax 4 + stack ax + ax 0 == *ax 16 _Bool &&[3919] "
    mov     ax, [bp-10]
    cmp     ax, [_SizeOfWord]
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3919
    mov     ax, [_sp]
    sub     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 16
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3919:
; JumpIfZero
    test    ax, ax
    jz      L3917
; {
; loc                         p : (@-26): * char
    sub     sp, 2
; =
; RPN'ized expression: "IdentTable stack sp 1 - + *u 1 + *u + "
; Expanded expression: "IdentTable stack sp *(2) 1 - 4 * + 2 + *(2) + "
; Fused expression:    "- *sp 1 * ax 4 + stack ax + ax 2 + IdentTable *ax =(34) *(@-26) ax "
    mov     ax, [_sp]
    sub     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, _IdentTable
    add     ax, cx
    mov     [bp-26], ax
; RPN'ized expression: "( p , globalAllocSize GenAddrData ) "
; Expanded expression: " (@-26) *(2)  (@-10) *(2)  GenAddrData ()4 "
; Fused expression:    "( *(2) (@-26) , *(2) (@-10) , GenAddrData )4 "
    push    word [bp-26]
    push    word [bp-10]
    call    _GenAddrData
    sub     sp, -4
; if
; RPN'ized expression: "OutputFormat 0 != "
; Expanded expression: "OutputFormat *(2) 0 != "
; Fused expression:    "!= *OutputFormat 0 IF! "
    mov     ax, [_OutputFormat]
    cmp     ax, 0
    je      L3920
; RPN'ized expression: "( DataFooter printf ) "
; Expanded expression: " DataFooter *(2)  printf ()2 "
; Fused expression:    "( *(2) DataFooter , printf )2 "
    push    word [_DataFooter]
    call    _printf
    sub     sp, -2
L3920:
; if
; RPN'ized expression: "( p *u isdigit ) "
; Expanded expression: " (@-26) *(2) *(1)  isdigit ()2 "
; Fused expression:    "( *(2) (@-26) *(1) ax , isdigit )2 "
    mov     ax, [bp-26]
    mov     bx, ax
    mov     al, [bx]
    cbw
    push    ax
    call    _isdigit
    sub     sp, -2
; JumpIfZero
    test    ax, ax
    jz      L3922
; RPN'ized expression: "( 0 GenStrData ) "
; Expanded expression: " 0  GenStrData ()2 "
; Fused expression:    "( 0 , GenStrData )2 "
    push    0
    call    _GenStrData
    sub     sp, -2
L3922:
    sub     sp, -2
; }
    jmp     L3918
L3917:
; else
; RPN'ized expression: "( L3924 error ) "
; Expanded expression: " L3924  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3924:
    db  "Error: ParseDecl(): cannot initialize a global variable with a non-constant expression",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3924 , error )2 "
    push    L3924
    call    _error
    sub     sp, -2
L3918:
L3914:
; }
    jmp     L3912
L3911:
; else
; {
; if
; RPN'ized expression: "synPtr 0 >= SyntaxStack synPtr + *u 0 + *u 17 == && "
; Expanded expression: "(@-14) *(2) 0 >= _Bool [sh&&->3928] SyntaxStack (@-14) *(2) 4 * + 0 + *(2) 17 == _Bool &&[3928] "
; Fused expression:    ">= *(@-14) 0 _Bool [sh&&->3928] * *(@-14) 4 + SyntaxStack ax + ax 0 == *ax 17 _Bool &&[3928] "
    mov     ax, [bp-14]
    cmp     ax, 0
    setge   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3928
    mov     ax, [bp-14]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 17
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3928:
; JumpIfZero
    test    ax, ax
    jz      L3926
; RPN'ized expression: "( L3929 error ) "
; Expanded expression: " L3929  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3929:
    db  "Error: ParseDecl(): cannot initialize a variable with a 'void' expression",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3929 , error )2 "
    push    L3929
    call    _error
    sub     sp, -2
L3926:
; RPN'ized expression: "( SyntaxStack lastSyntaxPtr 1 + + *u 1 + *u , 89 , 0 ins2 ) "
; Expanded expression: " SyntaxStack (@-4) *(2) 1 + 4 * + 2 + *(2)  89  0  ins2 ()6 "
; Fused expression:    "( + *(@-4) 1 * ax 4 + SyntaxStack ax + ax 2 *(2) ax , 89 , 0 , ins2 )6 "
    mov     ax, [bp-4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    push    89
    push    0
    call    _ins2
    sub     sp, -6
; RPN'ized expression: "( localAllocSize , 61 push2 ) "
; Expanded expression: " (@-8) *(2)  61  push2 ()4 "
; Fused expression:    "( *(2) (@-8) , 61 , push2 )4 "
    push    word [bp-8]
    push    61
    call    _push2
    sub     sp, -4
; RPN'ized expression: "( GenExpr ) "
; Expanded expression: " GenExpr ()0 "
; Fused expression:    "( GenExpr )0 "
    call    _GenExpr
; }
L3912:
; RPN'ized expression: "IdentTableLen undoIdents = "
; Expanded expression: "IdentTableLen (@-24) *(2) =(2) "
; Fused expression:    "=(34) *IdentTableLen *(@-24) "
    mov     ax, [bp-24]
    mov     [_IdentTableLen], ax
; RPN'ized expression: "SyntaxStackCnt oldssp = "
; Expanded expression: "SyntaxStackCnt (@-22) *(2) =(2) "
; Fused expression:    "=(34) *SyntaxStackCnt *(@-22) "
    mov     ax, [bp-22]
    mov     [_SyntaxStackCnt], ax
    sub     sp, -14
; }
    jmp     L3888
L3887:
; else
; if
; RPN'ized expression: "globalAllocSize "
; Expanded expression: "(@-10) *(2) "
; Fused expression:    "*(2) (@-10) "
    mov     ax, [bp-10]
; JumpIfZero
    test    ax, ax
    jz      L3931
; {
; RPN'ized expression: "( globalAllocSize GenZeroData ) "
; Expanded expression: " (@-10) *(2)  GenZeroData ()2 "
; Fused expression:    "( *(2) (@-10) , GenZeroData )2 "
    push    word [bp-10]
    call    _GenZeroData
    sub     sp, -2
; if
; RPN'ized expression: "OutputFormat 0 != "
; Expanded expression: "OutputFormat *(2) 0 != "
; Fused expression:    "!= *OutputFormat 0 IF! "
    mov     ax, [_OutputFormat]
    cmp     ax, 0
    je      L3933
; RPN'ized expression: "( DataFooter printf ) "
; Expanded expression: " DataFooter *(2)  printf ()2 "
; Fused expression:    "( *(2) DataFooter , printf )2 "
    push    word [_DataFooter]
    call    _printf
    sub     sp, -2
L3933:
; }
    jmp     L3932
L3931:
; else
; if
; RPN'ized expression: "tok 123 == "
; Expanded expression: "(@4) *(2) 123 == "
; Fused expression:    "== *(@4) 123 IF! "
    mov     ax, [bp+4]
    cmp     ax, 123
    jne     L3935
; {
; loc                 undoSymbolsPtr : (@-12): int
    sub     sp, 2
; =
; RPN'ized expression: "SyntaxStackCnt "
; Expanded expression: "SyntaxStackCnt *(2) "
; Fused expression:    "=(34) *(@-12) *SyntaxStackCnt "
    mov     ax, [_SyntaxStackCnt]
    mov     [bp-12], ax
; loc                 undoIdents : (@-14): int
    sub     sp, 2
; =
; RPN'ized expression: "IdentTableLen "
; Expanded expression: "IdentTableLen *(2) "
; Fused expression:    "=(34) *(@-14) *IdentTableLen "
    mov     ax, [_IdentTableLen]
    mov     [bp-14], ax
; loc                 tmp : (@-16): int
    sub     sp, 2
; RPN'ized expression: "ParseLevel ++p "
; Expanded expression: "ParseLevel ++p(2) "
; Fused expression:    "++p(2) *ParseLevel "
    mov     ax, [_ParseLevel]
    inc     word [_ParseLevel]
; RPN'ized expression: "( CurFxnReturnExprTypeSynPtr &u , tmp &u , tmp &u , lastSyntaxPtr GetFxnInfo ) "
; Expanded expression: " CurFxnReturnExprTypeSynPtr  (@-16)  (@-16)  (@-4) *(2)  GetFxnInfo ()8 "
; Fused expression:    "( CurFxnReturnExprTypeSynPtr , (@-16) , (@-16) , *(2) (@-4) , GetFxnInfo )8 "
    push    _CurFxnReturnExprTypeSynPtr
    lea     ax, [bp-16]
    push    ax
    lea     ax, [bp-16]
    push    ax
    push    word [bp-4]
    call    _GetFxnInfo
    sub     sp, -8
; if
; RPN'ized expression: "OutputFormat 0 != "
; Expanded expression: "OutputFormat *(2) 0 != "
; Fused expression:    "!= *OutputFormat 0 IF! "
    mov     ax, [_OutputFormat]
    cmp     ax, 0
    je      L3937
; RPN'ized expression: "( CodeHeader printf ) "
; Expanded expression: " CodeHeader *(2)  printf ()2 "
; Fused expression:    "( *(2) CodeHeader , printf )2 "
    push    word [_CodeHeader]
    call    _printf
    sub     sp, -2
L3937:
; RPN'ized expression: "( IdentTable SyntaxStack lastSyntaxPtr + *u 1 + *u + GenLabel ) "
; Expanded expression: " IdentTable SyntaxStack (@-4) *(2) 4 * + 2 + *(2) +  GenLabel ()2 "
; Fused expression:    "( * *(@-4) 4 + SyntaxStack ax + ax 2 + IdentTable *ax , GenLabel )2 "
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, _IdentTable
    add     ax, cx
    push    ax
    call    _GenLabel
    sub     sp, -2
; RPN'ized expression: "CurFxnEpilogLabel LabelCnt ++p = "
; Expanded expression: "CurFxnEpilogLabel LabelCnt ++p(2) =(2) "
; Fused expression:    "++p(2) *LabelCnt =(34) *CurFxnEpilogLabel ax "
    mov     ax, [_LabelCnt]
    inc     word [_LabelCnt]
    mov     [_CurFxnEpilogLabel], ax
; RPN'ized expression: "( GenFxnProlog ) "
; Expanded expression: " GenFxnProlog ()0 "
; Fused expression:    "( GenFxnProlog )0 "
    call    _GenFxnProlog
; RPN'ized expression: "( lastSyntaxPtr AddFxnParamSymbols ) "
; Expanded expression: " (@-4) *(2)  AddFxnParamSymbols ()2 "
; Fused expression:    "( *(2) (@-4) , AddFxnParamSymbols )2 "
    push    word [bp-4]
    call    _AddFxnParamSymbols
    sub     sp, -2
; RPN'ized expression: "tok ( 0 , 0 ParseBlock ) = "
; Expanded expression: "(@4)  0  0  ParseBlock ()4 =(2) "
; Fused expression:    "( 0 , 0 , ParseBlock )4 =(34) *(@4) ax "
    push    0
    push    0
    call    _ParseBlock
    sub     sp, -4
    mov     [bp+4], ax
; RPN'ized expression: "ParseLevel --p "
; Expanded expression: "ParseLevel --p(2) "
; Fused expression:    "--p(2) *ParseLevel "
    mov     ax, [_ParseLevel]
    dec     word [_ParseLevel]
; if
; RPN'ized expression: "tok 125 != "
; Expanded expression: "(@4) *(2) 125 != "
; Fused expression:    "!= *(@4) 125 IF! "
    mov     ax, [bp+4]
    cmp     ax, 125
    je      L3939
; RPN'ized expression: "( L3941 error ) "
; Expanded expression: " L3941  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3941:
    db  "Error: ParseDecl(): '}' expected",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3941 , error )2 "
    push    L3941
    call    _error
    sub     sp, -2
L3939:
; RPN'ized expression: "IdentTableLen undoIdents = "
; Expanded expression: "IdentTableLen (@-14) *(2) =(2) "
; Fused expression:    "=(34) *IdentTableLen *(@-14) "
    mov     ax, [bp-14]
    mov     [_IdentTableLen], ax
; RPN'ized expression: "SyntaxStackCnt undoSymbolsPtr = "
; Expanded expression: "SyntaxStackCnt (@-12) *(2) =(2) "
; Fused expression:    "=(34) *SyntaxStackCnt *(@-12) "
    mov     ax, [bp-12]
    mov     [_SyntaxStackCnt], ax
; RPN'ized expression: "( CurFxnEpilogLabel GenNumLabel ) "
; Expanded expression: " CurFxnEpilogLabel *(2)  GenNumLabel ()2 "
; Fused expression:    "( *(2) CurFxnEpilogLabel , GenNumLabel )2 "
    push    word [_CurFxnEpilogLabel]
    call    _GenNumLabel
    sub     sp, -2
; RPN'ized expression: "( GenFxnEpilog ) "
; Expanded expression: " GenFxnEpilog ()0 "
; Fused expression:    "( GenFxnEpilog )0 "
    call    _GenFxnEpilog
; if
; RPN'ized expression: "OutputFormat 0 != "
; Expanded expression: "OutputFormat *(2) 0 != "
; Fused expression:    "!= *OutputFormat 0 IF! "
    mov     ax, [_OutputFormat]
    cmp     ax, 0
    je      L3943
; RPN'ized expression: "( CodeFooter printf ) "
; Expanded expression: " CodeFooter *(2)  printf ()2 "
; Fused expression:    "( *(2) CodeFooter , printf )2 "
    push    word [_CodeFooter]
    call    _printf
    sub     sp, -2
L3943:
    sub     sp, -6
; }
L3935:
L3932:
L3888:
L3886:
; if
; RPN'ized expression: "tok 59 == tok 125 == || "
; Expanded expression: "(@4) *(2) 59 == _Bool [sh||->3947] (@4) *(2) 125 == _Bool ||[3947] "
; Fused expression:    "== *(@4) 59 _Bool [sh||->3947] == *(@4) 125 _Bool ||[3947] "
    mov     ax, [bp+4]
    cmp     ax, 59
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L3947
    mov     ax, [bp+4]
    cmp     ax, 125
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3947:
; JumpIfZero
    test    ax, ax
    jz      L3945
; break
    sub     sp, -4
    jmp     L3839
L3945:
; continue
    sub     sp, -4
    jmp     L3837
    sub     sp, -4
; }
L3840:
; RPN'ized expression: "( ( tok GetTokenName ) , L3948 error ) "
; Expanded expression: "  (@4) *(2)  GetTokenName ()2  L3948  error ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3948:
    db  "Error: ParseDecl(): unexpected token %s",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( *(2) (@4) , GetTokenName )2 , L3948 , error )4 "
    push    word [bp+4]
    call    _GetTokenName
    sub     sp, -2
    push    ax
    push    L3948
    call    _error
    sub     sp, -4
; }
    jmp     L3837
L3839:
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
; return
; RPN'ized expression: "tok "
; Expanded expression: "(@4) *(2) "
; Fused expression:    "*(2) (@4) "
    mov     ax, [bp+4]
    jmp     L3829
L3829:
    leave
    ret
; SEGMENT _TEXT
; glb ParseFxnParams : (void) void
SEGMENT _TEXT
    global  _ParseFxnParams
_ParseFxnParams:
    push    bp
    mov     bp, sp
; loc     tok : (@-2): int
    sub     sp, 2
; loc     base : (@-4): int
    sub     sp, 2
; loc     lastSyntaxPtr : (@-6): int
    sub     sp, 2
; loc     cnt : (@-8): int
    sub     sp, 2
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "=(34) *(@-8) 0 "
    mov     ax, 0
    mov     [bp-8], ax
; loc     ellCnt : (@-10): int
    sub     sp, 2
; =
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "=(34) *(@-10) 0 "
    mov     ax, 0
    mov     [bp-10], ax
; for
L3951:
    jmp     L3953
L3952:
    jmp     L3951
L3953:
; {
; RPN'ized expression: "lastSyntaxPtr SyntaxStackCnt = "
; Expanded expression: "(@-6) SyntaxStackCnt *(2) =(2) "
; Fused expression:    "=(34) *(@-6) *SyntaxStackCnt "
    mov     ax, [_SyntaxStackCnt]
    mov     [bp-6], ax
; RPN'ized expression: "base tok ( GetToken ) = = "
; Expanded expression: "(@-4) (@-2)  GetToken ()0 =(2) =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@-2) ax =(34) *(@-4) ax "
    call    _GetToken
    mov     [bp-2], ax
    mov     [bp-4], ax
; if
; RPN'ized expression: "tok 41 == "
; Expanded expression: "(@-2) *(2) 41 == "
; Fused expression:    "== *(@-2) 41 IF! "
    mov     ax, [bp-2]
    cmp     ax, 41
    jne     L3955
; break
    jmp     L3954
L3955:
; if
; RPN'ized expression: "( 1 , tok TokenStartsDeclaration ) 0 == "
; Expanded expression: " 1  (@-2) *(2)  TokenStartsDeclaration ()4 0 == "
; Fused expression:    "( 1 , *(2) (@-2) , TokenStartsDeclaration )4 == ax 0 IF! "
    push    1
    push    word [bp-2]
    call    _TokenStartsDeclaration
    sub     sp, -4
    cmp     ax, 0
    jne     L3957
; {
; if
; RPN'ized expression: "tok 15 == "
; Expanded expression: "(@-2) *(2) 15 == "
; Fused expression:    "== *(@-2) 15 IF! "
    mov     ax, [bp-2]
    cmp     ax, 15
    jne     L3959
; {
; if
; RPN'ized expression: "cnt 0 == ellCnt || "
; Expanded expression: "(@-8) *(2) 0 == _Bool [sh||->3963] (@-10) *(2) _Bool ||[3963] "
; Fused expression:    "== *(@-8) 0 _Bool [sh||->3963] *(2) (@-10) _Bool ||[3963] "
    mov     ax, [bp-8]
    cmp     ax, 0
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L3963
    mov     ax, [bp-10]
    test    ax, ax
    setnz   al
    cbw
L3963:
; JumpIfZero
    test    ax, ax
    jz      L3961
; RPN'ized expression: "( L3964 error ) "
; Expanded expression: " L3964  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3964:
    db  "Error: ParseFxnParams(): '...' unexpected here",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3964 , error )2 "
    push    L3964
    call    _error
    sub     sp, -2
L3961:
; RPN'ized expression: "ellCnt ++p "
; Expanded expression: "(@-10) ++p(2) "
; Fused expression:    "++p(2) *(@-10) "
    mov     ax, [bp-10]
    inc     word [bp-10]
; }
    jmp     L3960
L3959:
; else
; RPN'ized expression: "( ( tok GetTokenName ) , L3966 error ) "
; Expanded expression: "  (@-2) *(2)  GetTokenName ()2  L3966  error ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3966:
    db  "Error: ParseFxnParams(): Unexpected token %s",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( *(2) (@-2) , GetTokenName )2 , L3966 , error )4 "
    push    word [bp-2]
    call    _GetTokenName
    sub     sp, -2
    push    ax
    push    L3966
    call    _error
    sub     sp, -4
L3960:
; }
    jmp     L3958
L3957:
; else
; if
; RPN'ized expression: "ellCnt "
; Expanded expression: "(@-10) *(2) "
; Fused expression:    "*(2) (@-10) "
    mov     ax, [bp-10]
; JumpIfZero
    test    ax, ax
    jz      L3968
; RPN'ized expression: "( L3970 error ) "
; Expanded expression: " L3970  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L3970:
    db  "Error: ParseFxnParams(): '...' must be the last in the parameter list",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L3970 , error )2 "
    push    L3970
    call    _error
    sub     sp, -2
L3968:
L3958:
; RPN'ized expression: "tok ( ParseDerived ) = "
; Expanded expression: "(@-2)  ParseDerived ()0 =(2) "
; Fused expression:    "( ParseDerived )0 =(34) *(@-2) ax "
    call    _ParseDerived
    mov     [bp-2], ax
; RPN'ized expression: "( base PushSyntax ) "
; Expanded expression: " (@-4) *(2)  PushSyntax ()2 "
; Fused expression:    "( *(2) (@-4) , PushSyntax )2 "
    push    word [bp-4]
    call    _PushSyntax
    sub     sp, -2
; RPN'ized expression: "lastSyntaxPtr ++p "
; Expanded expression: "(@-6) ++p(2) "
; Fused expression:    "++p(2) *(@-6) "
    mov     ax, [bp-6]
    inc     word [bp-6]
; if
; RPN'ized expression: "SyntaxStack lastSyntaxPtr + *u 0 + *u 91 == "
; Expanded expression: "SyntaxStack (@-6) *(2) 4 * + 0 + *(2) 91 == "
; Fused expression:    "* *(@-6) 4 + SyntaxStack ax + ax 0 == *ax 91 IF! "
    mov     ax, [bp-6]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 91
    jne     L3972
; {
; RPN'ized expression: "( 1 , lastSyntaxPtr DeleteSyntax ) "
; Expanded expression: " 1  (@-6) *(2)  DeleteSyntax ()4 "
; Fused expression:    "( 1 , *(2) (@-6) , DeleteSyntax )4 "
    push    1
    push    word [bp-6]
    call    _DeleteSyntax
    sub     sp, -4
; if
; RPN'ized expression: "SyntaxStack lastSyntaxPtr + *u 0 + *u 1 == "
; Expanded expression: "SyntaxStack (@-6) *(2) 4 * + 0 + *(2) 1 == "
; Fused expression:    "* *(@-6) 4 + SyntaxStack ax + ax 0 == *ax 1 IF! "
    mov     ax, [bp-6]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 1
    jne     L3974
; RPN'ized expression: "( 1 , lastSyntaxPtr DeleteSyntax ) "
; Expanded expression: " 1  (@-6) *(2)  DeleteSyntax ()4 "
; Fused expression:    "( 1 , *(2) (@-6) , DeleteSyntax )4 "
    push    1
    push    word [bp-6]
    call    _DeleteSyntax
    sub     sp, -4
L3974:
; RPN'ized expression: "SyntaxStack lastSyntaxPtr + *u 0 + *u 42 = "
; Expanded expression: "SyntaxStack (@-6) *(2) 4 * + 0 + 42 =(2) "
; Fused expression:    "* *(@-6) 4 + SyntaxStack ax + ax 0 =(34) *ax 42 "
    mov     ax, [bp-6]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, 42
    mov     [bx], ax
; }
    jmp     L3973
L3972:
; else
; if
; RPN'ized expression: "SyntaxStack lastSyntaxPtr + *u 0 + *u 40 == "
; Expanded expression: "SyntaxStack (@-6) *(2) 4 * + 0 + *(2) 40 == "
; Fused expression:    "* *(@-6) 4 + SyntaxStack ax + ax 0 == *ax 40 IF! "
    mov     ax, [bp-6]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 40
    jne     L3976
; {
; RPN'ized expression: "( 42 , lastSyntaxPtr InsertSyntax ) "
; Expanded expression: " 42  (@-6) *(2)  InsertSyntax ()4 "
; Fused expression:    "( 42 , *(2) (@-6) , InsertSyntax )4 "
    push    42
    push    word [bp-6]
    call    _InsertSyntax
    sub     sp, -4
; }
L3976:
L3973:
; RPN'ized expression: "lastSyntaxPtr --p "
; Expanded expression: "(@-6) --p(2) "
; Fused expression:    "--p(2) *(@-6) "
    mov     ax, [bp-6]
    dec     word [bp-6]
; RPN'ized expression: "cnt ++p "
; Expanded expression: "(@-8) ++p(2) "
; Fused expression:    "++p(2) *(@-8) "
    mov     ax, [bp-8]
    inc     word [bp-8]
; if
; RPN'ized expression: "tok 41 == tok 44 == || "
; Expanded expression: "(@-2) *(2) 41 == _Bool [sh||->3980] (@-2) *(2) 44 == _Bool ||[3980] "
; Fused expression:    "== *(@-2) 41 _Bool [sh||->3980] == *(@-2) 44 _Bool ||[3980] "
    mov     ax, [bp-2]
    cmp     ax, 41
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L3980
    mov     ax, [bp-2]
    cmp     ax, 44
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3980:
; JumpIfZero
    test    ax, ax
    jz      L3978
; {
; if
; RPN'ized expression: "base 17 == "
; Expanded expression: "(@-4) *(2) 17 == "
; Fused expression:    "== *(@-4) 17 IF! "
    mov     ax, [bp-4]
    cmp     ax, 17
    jne     L3981
; {
; loc                 t : (@-12): int
    sub     sp, 2
; =
; RPN'ized expression: "SyntaxStack SyntaxStackCnt 2 - + *u 0 + *u "
; Expanded expression: "SyntaxStack SyntaxStackCnt *(2) 2 - 4 * + 0 + *(2) "
; Fused expression:    "- *SyntaxStackCnt 2 * ax 4 + SyntaxStack ax + ax 0 =(34) *(@-12) *ax "
    mov     ax, [_SyntaxStackCnt]
    sub     ax, 2
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-12], ax
; if
; RPN'ized expression: "t 42 != t 41 != && cnt 1 == tok 41 == && ( L3985 , IdentTable SyntaxStack lastSyntaxPtr + *u 1 + *u + strcmp ) 0 == && 0 == && "
; Expanded expression: "(@-12) *(2) 42 != _Bool [sh&&->3990] (@-12) *(2) 41 != _Bool &&[3990] _Bool [sh&&->3987] (@-8) *(2) 1 == _Bool [sh&&->3989] (@-2) *(2) 41 == _Bool &&[3989] _Bool [sh&&->3988]  L3985  IdentTable SyntaxStack (@-6) *(2) 4 * + 2 + *(2) +  strcmp ()4 0 == _Bool &&[3988] 0 == _Bool &&[3987] "
; SEGMENT _TEXT
SEGMENT _DATA
L3985:
    db  "<something>",0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "!= *(@-12) 42 _Bool [sh&&->3990] != *(@-12) 41 _Bool &&[3990] _Bool [sh&&->3987] == *(@-8) 1 _Bool [sh&&->3989] == *(@-2) 41 _Bool &&[3989] _Bool [sh&&->3988] ( L3985 , * *(@-6) 4 + SyntaxStack ax + ax 2 + IdentTable *ax , strcmp )4 == ax 0 _Bool &&[3988] == ax 0 _Bool &&[3987] "
    mov     ax, [bp-12]
    cmp     ax, 42
    setne   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3990
    mov     ax, [bp-12]
    cmp     ax, 41
    setne   al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3990:
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3987
    mov     ax, [bp-8]
    cmp     ax, 1
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3989
    mov     ax, [bp-2]
    cmp     ax, 41
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3989:
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L3988
    push    L3985
    mov     ax, [bp-6]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, _IdentTable
    add     ax, cx
    push    ax
    call    _strcmp
    sub     sp, -4
    cmp     ax, 0
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3988:
    cmp     ax, 0
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L3987:
; JumpIfZero
    test    ax, ax
    jz      L3983
; RPN'ized expression: "( IdentTable SyntaxStack lastSyntaxPtr + *u 1 + *u + , L3991 error ) "
; Expanded expression: " IdentTable SyntaxStack (@-6) *(2) 4 * + 2 + *(2) +  L3991  error ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3991:
    db  "Error: ParseFxnParams(): Cannot declare a variable ('%s') of type 'void'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( * *(@-6) 4 + SyntaxStack ax + ax 2 + IdentTable *ax , L3991 , error )4 "
    mov     ax, [bp-6]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, _IdentTable
    add     ax, cx
    push    ax
    push    L3991
    call    _error
    sub     sp, -4
L3983:
    sub     sp, -2
; }
L3981:
; if
; RPN'ized expression: "tok 41 == "
; Expanded expression: "(@-2) *(2) 41 == "
; Fused expression:    "== *(@-2) 41 IF! "
    mov     ax, [bp-2]
    cmp     ax, 41
    jne     L3993
; break
    jmp     L3954
L3993:
; continue
    jmp     L3952
; }
L3978:
; RPN'ized expression: "( ( tok GetTokenName ) , L3995 error ) "
; Expanded expression: "  (@-2) *(2)  GetTokenName ()2  L3995  error ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L3995:
    db  "Error: ParseFxnParams(): Unexpected token %s",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( *(2) (@-2) , GetTokenName )2 , L3995 , error )4 "
    push    word [bp-2]
    call    _GetTokenName
    sub     sp, -2
    push    ax
    push    L3995
    call    _error
    sub     sp, -4
; }
    jmp     L3952
L3954:
L3950:
    leave
    ret
; SEGMENT _TEXT
; glb AddFxnParamSymbols : (
; prm     SyntaxPtr : int
;     ) void
SEGMENT _TEXT
    global  _AddFxnParamSymbols
_AddFxnParamSymbols:
    push    bp
    mov     bp, sp
; loc     SyntaxPtr : (@4): int
; loc     i : (@-2): int
    sub     sp, 2
; if
; RPN'ized expression: "SyntaxPtr 0 < SyntaxPtr SyntaxStackCnt 3 - > || SyntaxStack SyntaxPtr + *u 0 + *u 16 != || SyntaxStack SyntaxPtr 1 + + *u 0 + *u 40 != || "
; Expanded expression: "(@4) *(2) 0 < _Bool [sh||->4002] (@4) *(2) SyntaxStackCnt *(2) 3 - > _Bool ||[4002] _Bool [sh||->4001] SyntaxStack (@4) *(2) 4 * + 0 + *(2) 16 != _Bool ||[4001] _Bool [sh||->4000] SyntaxStack (@4) *(2) 1 + 4 * + 0 + *(2) 40 != _Bool ||[4000] "
; Fused expression:    "< *(@4) 0 _Bool [sh||->4002] - *SyntaxStackCnt 3 > *(@4) ax _Bool ||[4002] _Bool [sh||->4001] * *(@4) 4 + SyntaxStack ax + ax 0 != *ax 16 _Bool ||[4001] _Bool [sh||->4000] + *(@4) 1 * ax 4 + SyntaxStack ax + ax 0 != *ax 40 _Bool ||[4000] "
    mov     ax, [bp+4]
    cmp     ax, 0
    setl    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L4002
    mov     ax, [_SyntaxStackCnt]
    sub     ax, 3
    mov     cx, ax
    mov     ax, [bp+4]
    cmp     ax, cx
    setg    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L4002:
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L4001
    mov     ax, [bp+4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 16
    setne   al
    cbw
    test    ax, ax
    setnz   al
    cbw
L4001:
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L4000
    mov     ax, [bp+4]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 40
    setne   al
    cbw
    test    ax, ax
    setnz   al
    cbw
L4000:
; JumpIfZero
    test    ax, ax
    jz      L3998
; RPN'ized expression: "( L4003 error ) "
; Expanded expression: " L4003  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4003:
    db  "Internal error: AddFxnParamSymbols(): Invalid input",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4003 , error )2 "
    push    L4003
    call    _error
    sub     sp, -2
L3998:
; RPN'ized expression: "CurFxnSyntaxPtr SyntaxPtr = "
; Expanded expression: "CurFxnSyntaxPtr (@4) *(2) =(2) "
; Fused expression:    "=(34) *CurFxnSyntaxPtr *(@4) "
    mov     ax, [bp+4]
    mov     [_CurFxnSyntaxPtr], ax
; RPN'ized expression: "CurFxnParamCnt 0 = "
; Expanded expression: "CurFxnParamCnt 0 =(2) "
; Fused expression:    "=(34) *CurFxnParamCnt 0 "
    mov     ax, 0
    mov     [_CurFxnParamCnt], ax
; RPN'ized expression: "CurFxnParamOfs 2 SizeOfWord * = "
; Expanded expression: "CurFxnParamOfs 2 SizeOfWord *(2) * =(2) "
; Fused expression:    "* 2 *SizeOfWord =(34) *CurFxnParamOfs ax "
    mov     ax, 2
    mul     word [_SizeOfWord]
    mov     [_CurFxnParamOfs], ax
; RPN'ized expression: "CurFxnLocalOfs 0 = "
; Expanded expression: "CurFxnLocalOfs 0 =(2) "
; Fused expression:    "=(34) *CurFxnLocalOfs 0 "
    mov     ax, 0
    mov     [_CurFxnLocalOfs], ax
; RPN'ized expression: "SyntaxPtr 2 += "
; Expanded expression: "(@4) 2 +=(2) "
; Fused expression:    "+=(34) *(@4) 2 "
    mov     ax, [bp+4]
    add     ax, 2
    mov     [bp+4], ax
; for
; RPN'ized expression: "i SyntaxPtr = "
; Expanded expression: "(@-2) (@4) *(2) =(2) "
; Fused expression:    "=(34) *(@-2) *(@4) "
    mov     ax, [bp+4]
    mov     [bp-2], ax
L4005:
; RPN'ized expression: "i SyntaxStackCnt < "
; Expanded expression: "(@-2) *(2) SyntaxStackCnt *(2) < "
; Fused expression:    "< *(@-2) *SyntaxStackCnt IF! "
    mov     ax, [bp-2]
    cmp     ax, [_SyntaxStackCnt]
    jge     L4008
    jmp     L4007
L4006:
; RPN'ized expression: "i ++p "
; Expanded expression: "(@-2) ++p(2) "
; Fused expression:    "++p(2) *(@-2) "
    mov     ax, [bp-2]
    inc     word [bp-2]
    jmp     L4005
L4007:
; {
; loc         tok : (@-4): int
    sub     sp, 2
; =
; RPN'ized expression: "SyntaxStack i + *u 0 + *u "
; Expanded expression: "SyntaxStack (@-2) *(2) 4 * + 0 + *(2) "
; Fused expression:    "* *(@-2) 4 + SyntaxStack ax + ax 0 =(34) *(@-4) *ax "
    mov     ax, [bp-2]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-4], ax
; if
; RPN'ized expression: "tok 16 == "
; Expanded expression: "(@-4) *(2) 16 == "
; Fused expression:    "== *(@-4) 16 IF! "
    mov     ax, [bp-4]
    cmp     ax, 16
    jne     L4009
; {
; loc             sz : (@-6): int
    sub     sp, 2
; loc             paramPtr : (@-8): int
    sub     sp, 2
; if
; RPN'ized expression: "i 1 + SyntaxStackCnt >= "
; Expanded expression: "(@-2) *(2) 1 + SyntaxStackCnt *(2) >= "
; Fused expression:    "+ *(@-2) 1 >= ax *SyntaxStackCnt IF! "
    mov     ax, [bp-2]
    add     ax, 1
    cmp     ax, [_SyntaxStackCnt]
    jl      L4011
; RPN'ized expression: "( L4013 error ) "
; Expanded expression: " L4013  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4013:
    db  "Internal error: AddFxnParamSymbols(): Invalid input",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4013 , error )2 "
    push    L4013
    call    _error
    sub     sp, -2
L4011:
; if
; RPN'ized expression: "SyntaxStack i 1 + + *u 0 + *u 17 == "
; Expanded expression: "SyntaxStack (@-2) *(2) 1 + 4 * + 0 + *(2) 17 == "
; Fused expression:    "+ *(@-2) 1 * ax 4 + SyntaxStack ax + ax 0 == *ax 17 IF! "
    mov     ax, [bp-2]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 17
    jne     L4015
; break
    sub     sp, -6
    jmp     L4008
L4015:
; if
; RPN'ized expression: "SyntaxStack i 1 + + *u 0 + *u 15 == "
; Expanded expression: "SyntaxStack (@-2) *(2) 1 + 4 * + 0 + *(2) 15 == "
; Fused expression:    "+ *(@-2) 1 * ax 4 + SyntaxStack ax + ax 0 == *ax 15 IF! "
    mov     ax, [bp-2]
    add     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 15
    jne     L4017
; break
    sub     sp, -6
    jmp     L4008
L4017:
; RPN'ized expression: "sz ( i GetDeclSize ) = "
; Expanded expression: "(@-6)  (@-2) *(2)  GetDeclSize ()2 =(2) "
; Fused expression:    "( *(2) (@-2) , GetDeclSize )2 =(34) *(@-6) ax "
    push    word [bp-2]
    call    _GetDeclSize
    sub     sp, -2
    mov     [bp-6], ax
; if
; RPN'ized expression: "sz 0 <= "
; Expanded expression: "(@-6) *(2) 0 <= "
; Fused expression:    "<= *(@-6) 0 IF! "
    mov     ax, [bp-6]
    cmp     ax, 0
    jg      L4019
; RPN'ized expression: "( L4021 error ) "
; Expanded expression: " L4021  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4021:
    db  "Internal error: AddFxnParamSymbols(): GetDeclSize()",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4021 , error )2 "
    push    L4021
    call    _error
    sub     sp, -2
L4019:
; RPN'ized expression: "CurFxnParamOfs CurFxnParamOfs SizeOfWord + 1 - SizeOfWord / SizeOfWord * = "
; Expanded expression: "CurFxnParamOfs CurFxnParamOfs *(2) SizeOfWord *(2) + 1 - SizeOfWord *(2) / SizeOfWord *(2) * =(2) "
; Fused expression:    "+ *CurFxnParamOfs *SizeOfWord - ax 1 / ax *SizeOfWord * ax *SizeOfWord =(34) *CurFxnParamOfs ax "
    mov     ax, [_CurFxnParamOfs]
    add     ax, [_SizeOfWord]
    sub     ax, 1
    cwd
    idiv    word [_SizeOfWord]
    mul     word [_SizeOfWord]
    mov     [_CurFxnParamOfs], ax
; RPN'ized expression: "paramPtr SyntaxStackCnt = "
; Expanded expression: "(@-8) SyntaxStackCnt *(2) =(2) "
; Fused expression:    "=(34) *(@-8) *SyntaxStackCnt "
    mov     ax, [_SyntaxStackCnt]
    mov     [bp-8], ax
; RPN'ized expression: "( SyntaxStack i + *u 1 + *u , SyntaxStack i + *u 0 + *u PushSyntax2 ) "
; Expanded expression: " SyntaxStack (@-2) *(2) 4 * + 2 + *(2)  SyntaxStack (@-2) *(2) 4 * + 0 + *(2)  PushSyntax2 ()4 "
; Fused expression:    "( * *(@-2) 4 + SyntaxStack ax + ax 2 *(2) ax , * *(@-2) 4 + SyntaxStack ax + ax 0 *(2) ax , PushSyntax2 )4 "
    mov     ax, [bp-2]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    mov     ax, [bp-2]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    push    word [bx]
    call    _PushSyntax2
    sub     sp, -4
; RPN'ized expression: "( CurFxnParamOfs , 89 PushSyntax2 ) "
; Expanded expression: " CurFxnParamOfs *(2)  89  PushSyntax2 ()4 "
; Fused expression:    "( *(2) CurFxnParamOfs , 89 , PushSyntax2 )4 "
    push    word [_CurFxnParamOfs]
    push    89
    call    _PushSyntax2
    sub     sp, -4
; RPN'ized expression: "CurFxnParamOfs sz += "
; Expanded expression: "CurFxnParamOfs (@-6) *(2) +=(2) "
; Fused expression:    "+=(34) *CurFxnParamOfs *(@-6) "
    mov     ax, [_CurFxnParamOfs]
    add     ax, [bp-6]
    mov     [_CurFxnParamOfs], ax
; RPN'ized expression: "i ++p "
; Expanded expression: "(@-2) ++p(2) "
; Fused expression:    "++p(2) *(@-2) "
    mov     ax, [bp-2]
    inc     word [bp-2]
; while
; RPN'ized expression: "i SyntaxStackCnt < "
; Expanded expression: "(@-2) *(2) SyntaxStackCnt *(2) < "
L4023:
; Fused expression:    "< *(@-2) *SyntaxStackCnt IF! "
    mov     ax, [bp-2]
    cmp     ax, [_SyntaxStackCnt]
    jge     L4024
; {
; RPN'ized expression: "tok SyntaxStack i + *u 0 + *u = "
; Expanded expression: "(@-4) SyntaxStack (@-2) *(2) 4 * + 0 + *(2) =(2) "
; Fused expression:    "* *(@-2) 4 + SyntaxStack ax + ax 0 =(34) *(@-4) *ax "
    mov     ax, [bp-2]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-4], ax
; if
; RPN'ized expression: "tok 16 == tok 41 == || "
; Expanded expression: "(@-4) *(2) 16 == _Bool [sh||->4027] (@-4) *(2) 41 == _Bool ||[4027] "
; Fused expression:    "== *(@-4) 16 _Bool [sh||->4027] == *(@-4) 41 _Bool ||[4027] "
    mov     ax, [bp-4]
    cmp     ax, 16
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L4027
    mov     ax, [bp-4]
    cmp     ax, 41
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L4027:
; JumpIfZero
    test    ax, ax
    jz      L4025
; {
; RPN'ized expression: "CurFxnParamCnt ++p "
; Expanded expression: "CurFxnParamCnt ++p(2) "
; Fused expression:    "++p(2) *CurFxnParamCnt "
    mov     ax, [_CurFxnParamCnt]
    inc     word [_CurFxnParamCnt]
; RPN'ized expression: "( 0 , paramPtr ShowDecl ) "
; Expanded expression: " 0  (@-8) *(2)  ShowDecl ()4 "
; Fused expression:    "( 0 , *(2) (@-8) , ShowDecl )4 "
    push    0
    push    word [bp-8]
    call    _ShowDecl
    sub     sp, -4
; RPN'ized expression: "i --p "
; Expanded expression: "(@-2) --p(2) "
; Fused expression:    "--p(2) *(@-2) "
    mov     ax, [bp-2]
    dec     word [bp-2]
; break
    jmp     L4024
; }
    jmp     L4026
L4025:
; else
; if
; RPN'ized expression: "tok 40 == "
; Expanded expression: "(@-4) *(2) 40 == "
; Fused expression:    "== *(@-4) 40 IF! "
    mov     ax, [bp-4]
    cmp     ax, 40
    jne     L4028
; {
; loc                     c : (@-10): int
    sub     sp, 2
; =
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
; Fused expression:    "=(34) *(@-10) 1 "
    mov     ax, 1
    mov     [bp-10], ax
; RPN'ized expression: "i ++p "
; Expanded expression: "(@-2) ++p(2) "
; Fused expression:    "++p(2) *(@-2) "
    mov     ax, [bp-2]
    inc     word [bp-2]
; RPN'ized expression: "( tok PushSyntax ) "
; Expanded expression: " (@-4) *(2)  PushSyntax ()2 "
; Fused expression:    "( *(2) (@-4) , PushSyntax )2 "
    push    word [bp-4]
    call    _PushSyntax
    sub     sp, -2
; while
; RPN'ized expression: "c i SyntaxStackCnt < && "
; Expanded expression: "(@-10) *(2) _Bool [sh&&->4032] (@-2) *(2) SyntaxStackCnt *(2) < _Bool &&[4032] "
L4030:
; Fused expression:    "*(2) (@-10) _Bool [sh&&->4032] < *(@-2) *SyntaxStackCnt _Bool &&[4032] "
    mov     ax, [bp-10]
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L4032
    mov     ax, [bp-2]
    cmp     ax, [_SyntaxStackCnt]
    setl    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L4032:
; JumpIfZero
    test    ax, ax
    jz      L4031
; {
; RPN'ized expression: "tok SyntaxStack i + *u 0 + *u = "
; Expanded expression: "(@-4) SyntaxStack (@-2) *(2) 4 * + 0 + *(2) =(2) "
; Fused expression:    "* *(@-2) 4 + SyntaxStack ax + ax 0 =(34) *(@-4) *ax "
    mov     ax, [bp-2]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    mov     [bp-4], ax
; RPN'ized expression: "c tok 40 == tok 41 == - += "
; Expanded expression: "(@-10) (@-4) *(2) 40 == (@-4) *(2) 41 == - +=(2) "
; Fused expression:    "== *(@-4) 40 push-ax == *(@-4) 41 - *sp ax +=(34) *(@-10) ax "
    mov     ax, [bp-4]
    cmp     ax, 40
    sete    al
    cbw
    push    ax
    mov     ax, [bp-4]
    cmp     ax, 41
    sete    al
    cbw
    mov     cx, ax
    pop     ax
    sub     ax, cx
    mov     cx, ax
    mov     ax, [bp-10]
    add     ax, cx
    mov     [bp-10], ax
; RPN'ized expression: "( SyntaxStack i + *u 1 + *u , SyntaxStack i + *u 0 + *u PushSyntax2 ) "
; Expanded expression: " SyntaxStack (@-2) *(2) 4 * + 2 + *(2)  SyntaxStack (@-2) *(2) 4 * + 0 + *(2)  PushSyntax2 ()4 "
; Fused expression:    "( * *(@-2) 4 + SyntaxStack ax + ax 2 *(2) ax , * *(@-2) 4 + SyntaxStack ax + ax 0 *(2) ax , PushSyntax2 )4 "
    mov     ax, [bp-2]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    mov     ax, [bp-2]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    push    word [bx]
    call    _PushSyntax2
    sub     sp, -4
; RPN'ized expression: "i ++p "
; Expanded expression: "(@-2) ++p(2) "
; Fused expression:    "++p(2) *(@-2) "
    mov     ax, [bp-2]
    inc     word [bp-2]
; }
    jmp     L4030
L4031:
    sub     sp, -2
; }
    jmp     L4029
L4028:
; else
; {
; RPN'ized expression: "( SyntaxStack i + *u 1 + *u , SyntaxStack i + *u 0 + *u PushSyntax2 ) "
; Expanded expression: " SyntaxStack (@-2) *(2) 4 * + 2 + *(2)  SyntaxStack (@-2) *(2) 4 * + 0 + *(2)  PushSyntax2 ()4 "
; Fused expression:    "( * *(@-2) 4 + SyntaxStack ax + ax 2 *(2) ax , * *(@-2) 4 + SyntaxStack ax + ax 0 *(2) ax , PushSyntax2 )4 "
    mov     ax, [bp-2]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    mov     ax, [bp-2]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    push    word [bx]
    call    _PushSyntax2
    sub     sp, -4
; RPN'ized expression: "i ++p "
; Expanded expression: "(@-2) ++p(2) "
; Fused expression:    "++p(2) *(@-2) "
    mov     ax, [bp-2]
    inc     word [bp-2]
; }
L4029:
L4026:
; }
    jmp     L4023
L4024:
    sub     sp, -4
; }
    jmp     L4010
L4009:
; else
; if
; RPN'ized expression: "tok 41 == "
; Expanded expression: "(@-4) *(2) 41 == "
; Fused expression:    "== *(@-4) 41 IF! "
    mov     ax, [bp-4]
    cmp     ax, 41
    jne     L4033
; break
    sub     sp, -2
    jmp     L4008
    jmp     L4034
L4033:
; else
; RPN'ized expression: "( ( tok GetTokenName ) , L4035 error ) "
; Expanded expression: "  (@-4) *(2)  GetTokenName ()2  L4035  error ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L4035:
    db  "Internal error: AddFxnParamSymbols(): Unexpected token %s",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( *(2) (@-4) , GetTokenName )2 , L4035 , error )4 "
    push    word [bp-4]
    call    _GetTokenName
    sub     sp, -2
    push    ax
    push    L4035
    call    _error
    sub     sp, -4
L4034:
L4010:
    sub     sp, -2
; }
    jmp     L4006
L4008:
L3997:
    leave
    ret
; SEGMENT _TEXT
; RPN'ized expression: "6 "
; Expanded expression: "6 "
; Expression value: 6
; glb ParseStatement : (
; prm     tok : int
; prm     BrkCntSwchTarget : * int
; prm     switchBody : int
;     ) int
SEGMENT _TEXT
    global  _ParseStatement
_ParseStatement:
    push    bp
    mov     bp, sp
; loc     tok : (@4): int
; loc     BrkCntSwchTarget : (@6): * int
; loc     switchBody : (@8): int
; loc     gotUnary : (@-2): int
    sub     sp, 2
; loc     synPtr : (@-4): int
    sub     sp, 2
; loc     constExpr : (@-6): int
    sub     sp, 2
; loc     exprVal : (@-8): int
    sub     sp, 2
; RPN'ized expression: "6 "
; Expanded expression: "6 "
; Expression value: 6
; loc     brkCntSwchTarget : (@-20): [6] int
    sub     sp, 12
; if
; RPN'ized expression: "tok 59 == "
; Expanded expression: "(@4) *(2) 59 == "
; Fused expression:    "== *(@4) 59 IF! "
    mov     ax, [bp+4]
    cmp     ax, 59
    jne     L4038
; {
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
; }
    jmp     L4039
L4038:
; else
; if
; RPN'ized expression: "tok 123 == "
; Expanded expression: "(@4) *(2) 123 == "
; Fused expression:    "== *(@4) 123 IF! "
    mov     ax, [bp+4]
    cmp     ax, 123
    jne     L4040
; {
; loc         undoSymbolsPtr : (@-22): int
    sub     sp, 2
; =
; RPN'ized expression: "SyntaxStackCnt "
; Expanded expression: "SyntaxStackCnt *(2) "
; Fused expression:    "=(34) *(@-22) *SyntaxStackCnt "
    mov     ax, [_SyntaxStackCnt]
    mov     [bp-22], ax
; loc         undoLocalOfs : (@-24): int
    sub     sp, 2
; =
; RPN'ized expression: "CurFxnLocalOfs "
; Expanded expression: "CurFxnLocalOfs *(2) "
; Fused expression:    "=(34) *(@-24) *CurFxnLocalOfs "
    mov     ax, [_CurFxnLocalOfs]
    mov     [bp-24], ax
; loc         undoIdents : (@-26): int
    sub     sp, 2
; =
; RPN'ized expression: "IdentTableLen "
; Expanded expression: "IdentTableLen *(2) "
; Fused expression:    "=(34) *(@-26) *IdentTableLen "
    mov     ax, [_IdentTableLen]
    mov     [bp-26], ax
; RPN'ized expression: "( L4042 printf ) "
; Expanded expression: " L4042  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4042:
    db  "; {",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4042 , printf )2 "
    push    L4042
    call    _printf
    sub     sp, -2
; RPN'ized expression: "ParseLevel ++p "
; Expanded expression: "ParseLevel ++p(2) "
; Fused expression:    "++p(2) *ParseLevel "
    mov     ax, [_ParseLevel]
    inc     word [_ParseLevel]
; RPN'ized expression: "tok ( switchBody 2 / , BrkCntSwchTarget ParseBlock ) = "
; Expanded expression: "(@4)  (@8) *(2) 2 /  (@6) *(2)  ParseBlock ()4 =(2) "
; Fused expression:    "( / *(@8) 2 , *(2) (@6) , ParseBlock )4 =(34) *(@4) ax "
    mov     ax, [bp+8]
    cwd
    mov     cx, 2
    idiv    cx
    push    ax
    push    word [bp+6]
    call    _ParseBlock
    sub     sp, -4
    mov     [bp+4], ax
; RPN'ized expression: "ParseLevel --p "
; Expanded expression: "ParseLevel --p(2) "
; Fused expression:    "--p(2) *ParseLevel "
    mov     ax, [_ParseLevel]
    dec     word [_ParseLevel]
; if
; RPN'ized expression: "tok 125 != "
; Expanded expression: "(@4) *(2) 125 != "
; Fused expression:    "!= *(@4) 125 IF! "
    mov     ax, [bp+4]
    cmp     ax, 125
    je      L4044
; RPN'ized expression: "( ( tok GetTokenName ) , L4046 error ) "
; Expanded expression: "  (@4) *(2)  GetTokenName ()2  L4046  error ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L4046:
    db  "Error: ParseStatement(): '}' expected. Unexpected token %s",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( *(2) (@4) , GetTokenName )2 , L4046 , error )4 "
    push    word [bp+4]
    call    _GetTokenName
    sub     sp, -2
    push    ax
    push    L4046
    call    _error
    sub     sp, -4
L4044:
; RPN'ized expression: "IdentTableLen undoIdents = "
; Expanded expression: "IdentTableLen (@-26) *(2) =(2) "
; Fused expression:    "=(34) *IdentTableLen *(@-26) "
    mov     ax, [bp-26]
    mov     [_IdentTableLen], ax
; RPN'ized expression: "SyntaxStackCnt undoSymbolsPtr = "
; Expanded expression: "SyntaxStackCnt (@-22) *(2) =(2) "
; Fused expression:    "=(34) *SyntaxStackCnt *(@-22) "
    mov     ax, [bp-22]
    mov     [_SyntaxStackCnt], ax
; if
; RPN'ized expression: "CurFxnLocalOfs undoLocalOfs != "
; Expanded expression: "CurFxnLocalOfs *(2) (@-24) *(2) != "
; Fused expression:    "!= *CurFxnLocalOfs *(@-24) IF! "
    mov     ax, [_CurFxnLocalOfs]
    cmp     ax, [bp-24]
    je      L4048
; RPN'ized expression: "( CurFxnLocalOfs undoLocalOfs - GenLocalAlloc ) "
; Expanded expression: " CurFxnLocalOfs *(2) (@-24) *(2) -  GenLocalAlloc ()2 "
; Fused expression:    "( - *CurFxnLocalOfs *(@-24) , GenLocalAlloc )2 "
    mov     ax, [_CurFxnLocalOfs]
    sub     ax, [bp-24]
    push    ax
    call    _GenLocalAlloc
    sub     sp, -2
L4048:
; RPN'ized expression: "CurFxnLocalOfs undoLocalOfs = "
; Expanded expression: "CurFxnLocalOfs (@-24) *(2) =(2) "
; Fused expression:    "=(34) *CurFxnLocalOfs *(@-24) "
    mov     ax, [bp-24]
    mov     [_CurFxnLocalOfs], ax
; RPN'ized expression: "( L4050 printf ) "
; Expanded expression: " L4050  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4050:
    db  "; }",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4050 , printf )2 "
    push    L4050
    call    _printf
    sub     sp, -2
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
    sub     sp, -6
; }
    jmp     L4041
L4040:
; else
; if
; RPN'ized expression: "tok 20 == "
; Expanded expression: "(@4) *(2) 20 == "
; Fused expression:    "== *(@4) 20 IF! "
    mov     ax, [bp+4]
    cmp     ax, 20
    jne     L4052
; {
; RPN'ized expression: "( L4054 printf ) "
; Expanded expression: " L4054  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4054:
    db  "; return",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4054 , printf )2 "
    push    L4054
    call    _printf
    sub     sp, -2
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
; if
; RPN'ized expression: "( exprVal &u , constExpr &u , synPtr &u , gotUnary &u , tok ParseExpr ) 59 != "
; Expanded expression: " (@-8)  (@-6)  (@-4)  (@-2)  (@4) *(2)  ParseExpr ()10 59 != "
; Fused expression:    "( (@-8) , (@-6) , (@-4) , (@-2) , *(2) (@4) , ParseExpr )10 != ax 59 IF! "
    lea     ax, [bp-8]
    push    ax
    lea     ax, [bp-6]
    push    ax
    lea     ax, [bp-4]
    push    ax
    lea     ax, [bp-2]
    push    ax
    push    word [bp+4]
    call    _ParseExpr
    sub     sp, -10
    cmp     ax, 59
    je      L4056
; RPN'ized expression: "( L4058 error ) "
; Expanded expression: " L4058  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4058:
    db  "Error: ParseStatement(): ';' expected",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4058 , error )2 "
    push    L4058
    call    _error
    sub     sp, -2
L4056:
; if
; RPN'ized expression: "CurFxnReturnExprTypeSynPtr 0 >= SyntaxStack CurFxnReturnExprTypeSynPtr + *u 0 + *u 17 == && "
; Expanded expression: "CurFxnReturnExprTypeSynPtr *(2) 0 >= _Bool [sh&&->4062] SyntaxStack CurFxnReturnExprTypeSynPtr *(2) 4 * + 0 + *(2) 17 == _Bool &&[4062] "
; Fused expression:    ">= *CurFxnReturnExprTypeSynPtr 0 _Bool [sh&&->4062] * *CurFxnReturnExprTypeSynPtr 4 + SyntaxStack ax + ax 0 == *ax 17 _Bool &&[4062] "
    mov     ax, [_CurFxnReturnExprTypeSynPtr]
    cmp     ax, 0
    setge   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L4062
    mov     ax, [_CurFxnReturnExprTypeSynPtr]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 17
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L4062:
; JumpIfZero
    test    ax, ax
    jz      L4060
; {
; if
; RPN'ized expression: "gotUnary "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
    mov     ax, [bp-2]
; JumpIfZero
    test    ax, ax
    jz      L4063
; RPN'ized expression: "( L4065 error ) "
; Expanded expression: " L4065  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4065:
    db  "Error: ParseStatement(): cannot return a value from a function returning 'void'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4065 , error )2 "
    push    L4065
    call    _error
    sub     sp, -2
L4063:
; }
    jmp     L4061
L4060:
; else
; {
; if
; RPN'ized expression: "gotUnary 0 == "
; Expanded expression: "(@-2) *(2) 0 == "
; Fused expression:    "== *(@-2) 0 IF! "
    mov     ax, [bp-2]
    cmp     ax, 0
    jne     L4067
; RPN'ized expression: "( L4069 error ) "
; Expanded expression: " L4069  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4069:
    db  "Error: ParseStatement(): missing return value",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4069 , error )2 "
    push    L4069
    call    _error
    sub     sp, -2
L4067:
; }
L4061:
; if
; RPN'ized expression: "gotUnary "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
    mov     ax, [bp-2]
; JumpIfZero
    test    ax, ax
    jz      L4071
; RPN'ized expression: "( GenExpr ) "
; Expanded expression: " GenExpr ()0 "
; Fused expression:    "( GenExpr )0 "
    call    _GenExpr
L4071:
; RPN'ized expression: "( CurFxnEpilogLabel GenJumpUncond ) "
; Expanded expression: " CurFxnEpilogLabel *(2)  GenJumpUncond ()2 "
; Fused expression:    "( *(2) CurFxnEpilogLabel , GenJumpUncond )2 "
    push    word [_CurFxnEpilogLabel]
    call    _GenJumpUncond
    sub     sp, -2
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
; }
    jmp     L4053
L4052:
; else
; if
; RPN'ized expression: "tok 24 == "
; Expanded expression: "(@4) *(2) 24 == "
; Fused expression:    "== *(@4) 24 IF! "
    mov     ax, [bp+4]
    cmp     ax, 24
    jne     L4073
; {
; loc         labelBefore : (@-22): int
    sub     sp, 2
; =
; RPN'ized expression: "LabelCnt ++p "
; Expanded expression: "LabelCnt ++p(2) "
; Fused expression:    "++p(2) *LabelCnt =(34) *(@-22) ax "
    mov     ax, [_LabelCnt]
    inc     word [_LabelCnt]
    mov     [bp-22], ax
; loc         labelAfter : (@-24): int
    sub     sp, 2
; =
; RPN'ized expression: "LabelCnt ++p "
; Expanded expression: "LabelCnt ++p(2) "
; Fused expression:    "++p(2) *LabelCnt =(34) *(@-24) ax "
    mov     ax, [_LabelCnt]
    inc     word [_LabelCnt]
    mov     [bp-24], ax
; RPN'ized expression: "( L4075 printf ) "
; Expanded expression: " L4075  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4075:
    db  "; while",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4075 , printf )2 "
    push    L4075
    call    _printf
    sub     sp, -2
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
; if
; RPN'ized expression: "tok 40 != "
; Expanded expression: "(@4) *(2) 40 != "
; Fused expression:    "!= *(@4) 40 IF! "
    mov     ax, [bp+4]
    cmp     ax, 40
    je      L4077
; RPN'ized expression: "( L4079 error ) "
; Expanded expression: " L4079  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4079:
    db  "Error: ParseStatement(): '(' expected after 'while'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4079 , error )2 "
    push    L4079
    call    _error
    sub     sp, -2
L4077:
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
; if
; RPN'ized expression: "( exprVal &u , constExpr &u , synPtr &u , gotUnary &u , tok ParseExpr ) 41 != "
; Expanded expression: " (@-8)  (@-6)  (@-4)  (@-2)  (@4) *(2)  ParseExpr ()10 41 != "
; Fused expression:    "( (@-8) , (@-6) , (@-4) , (@-2) , *(2) (@4) , ParseExpr )10 != ax 41 IF! "
    lea     ax, [bp-8]
    push    ax
    lea     ax, [bp-6]
    push    ax
    lea     ax, [bp-4]
    push    ax
    lea     ax, [bp-2]
    push    ax
    push    word [bp+4]
    call    _ParseExpr
    sub     sp, -10
    cmp     ax, 41
    je      L4081
; RPN'ized expression: "( L4083 error ) "
; Expanded expression: " L4083  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4083:
    db  "Error: ParseStatement(): ')' expected after 'while ( expression'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4083 , error )2 "
    push    L4083
    call    _error
    sub     sp, -2
L4081:
; if
; RPN'ized expression: "gotUnary 0 == "
; Expanded expression: "(@-2) *(2) 0 == "
; Fused expression:    "== *(@-2) 0 IF! "
    mov     ax, [bp-2]
    cmp     ax, 0
    jne     L4085
; RPN'ized expression: "( L4087 error ) "
; Expanded expression: " L4087  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4087:
    db  "Error: ParseStatement(): expression expected in 'while ( expression )'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4087 , error )2 "
    push    L4087
    call    _error
    sub     sp, -2
L4085:
; if
; RPN'ized expression: "synPtr 0 >= SyntaxStack synPtr + *u 0 + *u 17 == && "
; Expanded expression: "(@-4) *(2) 0 >= _Bool [sh&&->4091] SyntaxStack (@-4) *(2) 4 * + 0 + *(2) 17 == _Bool &&[4091] "
; Fused expression:    ">= *(@-4) 0 _Bool [sh&&->4091] * *(@-4) 4 + SyntaxStack ax + ax 0 == *ax 17 _Bool &&[4091] "
    mov     ax, [bp-4]
    cmp     ax, 0
    setge   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L4091
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 17
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L4091:
; JumpIfZero
    test    ax, ax
    jz      L4089
; RPN'ized expression: "( L4092 error ) "
; Expanded expression: " L4092  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4092:
    db  "Error: ParseStatement(): unexpected 'void' expression in 'while ( expression )'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4092 , error )2 "
    push    L4092
    call    _error
    sub     sp, -2
L4089:
; RPN'ized expression: "( labelBefore GenNumLabel ) "
; Expanded expression: " (@-22) *(2)  GenNumLabel ()2 "
; Fused expression:    "( *(2) (@-22) , GenNumLabel )2 "
    push    word [bp-22]
    call    _GenNumLabel
    sub     sp, -2
; switch
; RPN'ized expression: "stack sp 1 - + *u 0 + *u "
; Expanded expression: "stack sp *(2) 1 - 4 * + 0 + *(2) "
; Fused expression:    "- *sp 1 * ax 4 + stack ax + ax 0 *(2) ax "
    mov     ax, [_sp]
    sub     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    jmp     L4096
; {
; case
; RPN'ized expression: "60 "
; Expanded expression: "60 "
; Expression value: 60
    jmp     L4097
L4096:
    cmp     ax, 60
    jne     L4098
L4097:
; case
; RPN'ized expression: "62 "
; Expanded expression: "62 "
; Expression value: 62
    jmp     L4099
L4098:
    cmp     ax, 62
    jne     L4100
L4099:
; case
; RPN'ized expression: "8 "
; Expanded expression: "8 "
; Expression value: 8
    jmp     L4101
L4100:
    cmp     ax, 8
    jne     L4102
L4101:
; case
; RPN'ized expression: "9 "
; Expanded expression: "9 "
; Expression value: 9
    jmp     L4103
L4102:
    cmp     ax, 9
    jne     L4104
L4103:
; case
; RPN'ized expression: "10 "
; Expanded expression: "10 "
; Expression value: 10
    jmp     L4105
L4104:
    cmp     ax, 10
    jne     L4106
L4105:
; case
; RPN'ized expression: "11 "
; Expanded expression: "11 "
; Expression value: 11
    jmp     L4107
L4106:
    cmp     ax, 11
    jne     L4108
L4107:
; case
; RPN'ized expression: "85 "
; Expanded expression: "85 "
; Expression value: 85
    jmp     L4109
L4108:
    cmp     ax, 85
    jne     L4110
L4109:
; case
; RPN'ized expression: "86 "
; Expanded expression: "86 "
; Expression value: 86
    jmp     L4111
L4110:
    cmp     ax, 86
    jne     L4112
L4111:
; case
; RPN'ized expression: "87 "
; Expanded expression: "87 "
; Expression value: 87
    jmp     L4113
L4112:
    cmp     ax, 87
    jne     L4114
L4113:
; case
; RPN'ized expression: "88 "
; Expanded expression: "88 "
; Expression value: 88
    jmp     L4115
L4114:
    cmp     ax, 88
    jne     L4116
L4115:
; RPN'ized expression: "( labelAfter , 76 push2 ) "
; Expanded expression: " (@-24) *(2)  76  push2 ()4 "
; Fused expression:    "( *(2) (@-24) , 76 , push2 )4 "
    push    word [bp-24]
    push    76
    call    _push2
    sub     sp, -4
; RPN'ized expression: "( GenExpr ) "
; Expanded expression: " GenExpr ()0 "
; Fused expression:    "( GenExpr )0 "
    call    _GenExpr
; break
    jmp     L4094
; default
L4095:
; RPN'ized expression: "( GenExpr ) "
; Expanded expression: " GenExpr ()0 "
; Fused expression:    "( GenExpr )0 "
    call    _GenExpr
; RPN'ized expression: "( labelAfter GenJumpIfZero ) "
; Expanded expression: " (@-24) *(2)  GenJumpIfZero ()2 "
; Fused expression:    "( *(2) (@-24) , GenJumpIfZero )2 "
    push    word [bp-24]
    call    _GenJumpIfZero
    sub     sp, -2
; break
    jmp     L4094
; }
    jmp     L4094
L4116:
    jmp     L4095
L4094:
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
; RPN'ized expression: "brkCntSwchTarget 0 + *u labelAfter = "
; Expanded expression: "(@-20) 0 + (@-24) *(2) =(2) "
; Fused expression:    "+ (@-20) 0 =(34) *ax *(@-24) "
    lea     ax, [bp-20]
    add     ax, 0
    mov     bx, ax
    mov     ax, [bp-24]
    mov     [bx], ax
; RPN'ized expression: "brkCntSwchTarget 1 + *u labelBefore = "
; Expanded expression: "(@-20) 2 + (@-22) *(2) =(2) "
; Fused expression:    "+ (@-20) 2 =(34) *ax *(@-22) "
    lea     ax, [bp-20]
    add     ax, 2
    mov     bx, ax
    mov     ax, [bp-22]
    mov     [bx], ax
; RPN'ized expression: "brkCntSwchTarget 2 + *u CurFxnLocalOfs = "
; Expanded expression: "(@-20) 4 + CurFxnLocalOfs *(2) =(2) "
; Fused expression:    "+ (@-20) 4 =(34) *ax *CurFxnLocalOfs "
    lea     ax, [bp-20]
    add     ax, 4
    mov     bx, ax
    mov     ax, [_CurFxnLocalOfs]
    mov     [bx], ax
; RPN'ized expression: "brkCntSwchTarget 3 + *u CurFxnLocalOfs = "
; Expanded expression: "(@-20) 6 + CurFxnLocalOfs *(2) =(2) "
; Fused expression:    "+ (@-20) 6 =(34) *ax *CurFxnLocalOfs "
    lea     ax, [bp-20]
    add     ax, 6
    mov     bx, ax
    mov     ax, [_CurFxnLocalOfs]
    mov     [bx], ax
; RPN'ized expression: "tok ( 0 , brkCntSwchTarget , tok ParseStatement ) = "
; Expanded expression: "(@4)  0  (@-20)  (@4) *(2)  ParseStatement ()6 =(2) "
; Fused expression:    "( 0 , (@-20) , *(2) (@4) , ParseStatement )6 =(34) *(@4) ax "
    push    0
    lea     ax, [bp-20]
    push    ax
    push    word [bp+4]
    call    _ParseStatement
    sub     sp, -6
    mov     [bp+4], ax
; RPN'ized expression: "( labelBefore GenJumpUncond ) "
; Expanded expression: " (@-22) *(2)  GenJumpUncond ()2 "
; Fused expression:    "( *(2) (@-22) , GenJumpUncond )2 "
    push    word [bp-22]
    call    _GenJumpUncond
    sub     sp, -2
; RPN'ized expression: "( labelAfter GenNumLabel ) "
; Expanded expression: " (@-24) *(2)  GenNumLabel ()2 "
; Fused expression:    "( *(2) (@-24) , GenNumLabel )2 "
    push    word [bp-24]
    call    _GenNumLabel
    sub     sp, -2
    sub     sp, -4
; }
    jmp     L4074
L4073:
; else
; if
; RPN'ized expression: "tok 115 == "
; Expanded expression: "(@4) *(2) 115 == "
; Fused expression:    "== *(@4) 115 IF! "
    mov     ax, [bp+4]
    cmp     ax, 115
    jne     L4118
; {
; loc         labelBefore : (@-22): int
    sub     sp, 2
; =
; RPN'ized expression: "LabelCnt ++p "
; Expanded expression: "LabelCnt ++p(2) "
; Fused expression:    "++p(2) *LabelCnt =(34) *(@-22) ax "
    mov     ax, [_LabelCnt]
    inc     word [_LabelCnt]
    mov     [bp-22], ax
; loc         labelWhile : (@-24): int
    sub     sp, 2
; =
; RPN'ized expression: "LabelCnt ++p "
; Expanded expression: "LabelCnt ++p(2) "
; Fused expression:    "++p(2) *LabelCnt =(34) *(@-24) ax "
    mov     ax, [_LabelCnt]
    inc     word [_LabelCnt]
    mov     [bp-24], ax
; loc         labelAfter : (@-26): int
    sub     sp, 2
; =
; RPN'ized expression: "LabelCnt ++p "
; Expanded expression: "LabelCnt ++p(2) "
; Fused expression:    "++p(2) *LabelCnt =(34) *(@-26) ax "
    mov     ax, [_LabelCnt]
    inc     word [_LabelCnt]
    mov     [bp-26], ax
; RPN'ized expression: "( L4120 printf ) "
; Expanded expression: " L4120  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4120:
    db  "; do",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4120 , printf )2 "
    push    L4120
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( labelBefore GenNumLabel ) "
; Expanded expression: " (@-22) *(2)  GenNumLabel ()2 "
; Fused expression:    "( *(2) (@-22) , GenNumLabel )2 "
    push    word [bp-22]
    call    _GenNumLabel
    sub     sp, -2
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
; RPN'ized expression: "brkCntSwchTarget 0 + *u labelAfter = "
; Expanded expression: "(@-20) 0 + (@-26) *(2) =(2) "
; Fused expression:    "+ (@-20) 0 =(34) *ax *(@-26) "
    lea     ax, [bp-20]
    add     ax, 0
    mov     bx, ax
    mov     ax, [bp-26]
    mov     [bx], ax
; RPN'ized expression: "brkCntSwchTarget 1 + *u labelWhile = "
; Expanded expression: "(@-20) 2 + (@-24) *(2) =(2) "
; Fused expression:    "+ (@-20) 2 =(34) *ax *(@-24) "
    lea     ax, [bp-20]
    add     ax, 2
    mov     bx, ax
    mov     ax, [bp-24]
    mov     [bx], ax
; RPN'ized expression: "brkCntSwchTarget 2 + *u CurFxnLocalOfs = "
; Expanded expression: "(@-20) 4 + CurFxnLocalOfs *(2) =(2) "
; Fused expression:    "+ (@-20) 4 =(34) *ax *CurFxnLocalOfs "
    lea     ax, [bp-20]
    add     ax, 4
    mov     bx, ax
    mov     ax, [_CurFxnLocalOfs]
    mov     [bx], ax
; RPN'ized expression: "brkCntSwchTarget 3 + *u CurFxnLocalOfs = "
; Expanded expression: "(@-20) 6 + CurFxnLocalOfs *(2) =(2) "
; Fused expression:    "+ (@-20) 6 =(34) *ax *CurFxnLocalOfs "
    lea     ax, [bp-20]
    add     ax, 6
    mov     bx, ax
    mov     ax, [_CurFxnLocalOfs]
    mov     [bx], ax
; RPN'ized expression: "tok ( 0 , brkCntSwchTarget , tok ParseStatement ) = "
; Expanded expression: "(@4)  0  (@-20)  (@4) *(2)  ParseStatement ()6 =(2) "
; Fused expression:    "( 0 , (@-20) , *(2) (@4) , ParseStatement )6 =(34) *(@4) ax "
    push    0
    lea     ax, [bp-20]
    push    ax
    push    word [bp+4]
    call    _ParseStatement
    sub     sp, -6
    mov     [bp+4], ax
; if
; RPN'ized expression: "tok 24 != "
; Expanded expression: "(@4) *(2) 24 != "
; Fused expression:    "!= *(@4) 24 IF! "
    mov     ax, [bp+4]
    cmp     ax, 24
    je      L4122
; RPN'ized expression: "( L4124 error ) "
; Expanded expression: " L4124  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4124:
    db  "Error: ParseStatement(): 'while' expected after 'do statement'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4124 , error )2 "
    push    L4124
    call    _error
    sub     sp, -2
L4122:
; RPN'ized expression: "( L4126 printf ) "
; Expanded expression: " L4126  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4126:
    db  "; while",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4126 , printf )2 "
    push    L4126
    call    _printf
    sub     sp, -2
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
; if
; RPN'ized expression: "tok 40 != "
; Expanded expression: "(@4) *(2) 40 != "
; Fused expression:    "!= *(@4) 40 IF! "
    mov     ax, [bp+4]
    cmp     ax, 40
    je      L4128
; RPN'ized expression: "( L4130 error ) "
; Expanded expression: " L4130  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4130:
    db  "Error: ParseStatement(): '(' expected after 'while'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4130 , error )2 "
    push    L4130
    call    _error
    sub     sp, -2
L4128:
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
; if
; RPN'ized expression: "( exprVal &u , constExpr &u , synPtr &u , gotUnary &u , tok ParseExpr ) 41 != "
; Expanded expression: " (@-8)  (@-6)  (@-4)  (@-2)  (@4) *(2)  ParseExpr ()10 41 != "
; Fused expression:    "( (@-8) , (@-6) , (@-4) , (@-2) , *(2) (@4) , ParseExpr )10 != ax 41 IF! "
    lea     ax, [bp-8]
    push    ax
    lea     ax, [bp-6]
    push    ax
    lea     ax, [bp-4]
    push    ax
    lea     ax, [bp-2]
    push    ax
    push    word [bp+4]
    call    _ParseExpr
    sub     sp, -10
    cmp     ax, 41
    je      L4132
; RPN'ized expression: "( L4134 error ) "
; Expanded expression: " L4134  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4134:
    db  "Error: ParseStatement(): ')' expected after 'while ( expression'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4134 , error )2 "
    push    L4134
    call    _error
    sub     sp, -2
L4132:
; if
; RPN'ized expression: "gotUnary 0 == "
; Expanded expression: "(@-2) *(2) 0 == "
; Fused expression:    "== *(@-2) 0 IF! "
    mov     ax, [bp-2]
    cmp     ax, 0
    jne     L4136
; RPN'ized expression: "( L4138 error ) "
; Expanded expression: " L4138  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4138:
    db  "Error: ParseStatement(): expression expected in 'while ( expression )'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4138 , error )2 "
    push    L4138
    call    _error
    sub     sp, -2
L4136:
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
; if
; RPN'ized expression: "tok 59 != "
; Expanded expression: "(@4) *(2) 59 != "
; Fused expression:    "!= *(@4) 59 IF! "
    mov     ax, [bp+4]
    cmp     ax, 59
    je      L4140
; RPN'ized expression: "( L4142 error ) "
; Expanded expression: " L4142  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4142:
    db  "Error: ParseStatement(): ';' expected after 'do statement while ( expression )'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4142 , error )2 "
    push    L4142
    call    _error
    sub     sp, -2
L4140:
; if
; RPN'ized expression: "synPtr 0 >= SyntaxStack synPtr + *u 0 + *u 17 == && "
; Expanded expression: "(@-4) *(2) 0 >= _Bool [sh&&->4146] SyntaxStack (@-4) *(2) 4 * + 0 + *(2) 17 == _Bool &&[4146] "
; Fused expression:    ">= *(@-4) 0 _Bool [sh&&->4146] * *(@-4) 4 + SyntaxStack ax + ax 0 == *ax 17 _Bool &&[4146] "
    mov     ax, [bp-4]
    cmp     ax, 0
    setge   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L4146
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 17
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L4146:
; JumpIfZero
    test    ax, ax
    jz      L4144
; RPN'ized expression: "( L4147 error ) "
; Expanded expression: " L4147  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4147:
    db  "Error: ParseStatement(): unexpected 'void' expression in 'while ( expression )'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4147 , error )2 "
    push    L4147
    call    _error
    sub     sp, -2
L4144:
; RPN'ized expression: "( labelWhile GenNumLabel ) "
; Expanded expression: " (@-24) *(2)  GenNumLabel ()2 "
; Fused expression:    "( *(2) (@-24) , GenNumLabel )2 "
    push    word [bp-24]
    call    _GenNumLabel
    sub     sp, -2
; switch
; RPN'ized expression: "stack sp 1 - + *u 0 + *u "
; Expanded expression: "stack sp *(2) 1 - 4 * + 0 + *(2) "
; Fused expression:    "- *sp 1 * ax 4 + stack ax + ax 0 *(2) ax "
    mov     ax, [_sp]
    sub     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    jmp     L4151
; {
; case
; RPN'ized expression: "60 "
; Expanded expression: "60 "
; Expression value: 60
    jmp     L4152
L4151:
    cmp     ax, 60
    jne     L4153
L4152:
; case
; RPN'ized expression: "62 "
; Expanded expression: "62 "
; Expression value: 62
    jmp     L4154
L4153:
    cmp     ax, 62
    jne     L4155
L4154:
; case
; RPN'ized expression: "8 "
; Expanded expression: "8 "
; Expression value: 8
    jmp     L4156
L4155:
    cmp     ax, 8
    jne     L4157
L4156:
; case
; RPN'ized expression: "9 "
; Expanded expression: "9 "
; Expression value: 9
    jmp     L4158
L4157:
    cmp     ax, 9
    jne     L4159
L4158:
; case
; RPN'ized expression: "10 "
; Expanded expression: "10 "
; Expression value: 10
    jmp     L4160
L4159:
    cmp     ax, 10
    jne     L4161
L4160:
; case
; RPN'ized expression: "11 "
; Expanded expression: "11 "
; Expression value: 11
    jmp     L4162
L4161:
    cmp     ax, 11
    jne     L4163
L4162:
; case
; RPN'ized expression: "85 "
; Expanded expression: "85 "
; Expression value: 85
    jmp     L4164
L4163:
    cmp     ax, 85
    jne     L4165
L4164:
; case
; RPN'ized expression: "86 "
; Expanded expression: "86 "
; Expression value: 86
    jmp     L4166
L4165:
    cmp     ax, 86
    jne     L4167
L4166:
; case
; RPN'ized expression: "87 "
; Expanded expression: "87 "
; Expression value: 87
    jmp     L4168
L4167:
    cmp     ax, 87
    jne     L4169
L4168:
; case
; RPN'ized expression: "88 "
; Expanded expression: "88 "
; Expression value: 88
    jmp     L4170
L4169:
    cmp     ax, 88
    jne     L4171
L4170:
; RPN'ized expression: "( labelBefore , 22 push2 ) "
; Expanded expression: " (@-22) *(2)  22  push2 ()4 "
; Fused expression:    "( *(2) (@-22) , 22 , push2 )4 "
    push    word [bp-22]
    push    22
    call    _push2
    sub     sp, -4
; RPN'ized expression: "( GenExpr ) "
; Expanded expression: " GenExpr ()0 "
; Fused expression:    "( GenExpr )0 "
    call    _GenExpr
; break
    jmp     L4149
; default
L4150:
; RPN'ized expression: "( GenExpr ) "
; Expanded expression: " GenExpr ()0 "
; Fused expression:    "( GenExpr )0 "
    call    _GenExpr
; RPN'ized expression: "( labelBefore GenJumpIfNotZero ) "
; Expanded expression: " (@-22) *(2)  GenJumpIfNotZero ()2 "
; Fused expression:    "( *(2) (@-22) , GenJumpIfNotZero )2 "
    push    word [bp-22]
    call    _GenJumpIfNotZero
    sub     sp, -2
; break
    jmp     L4149
; }
    jmp     L4149
L4171:
    jmp     L4150
L4149:
; RPN'ized expression: "( labelAfter GenNumLabel ) "
; Expanded expression: " (@-26) *(2)  GenNumLabel ()2 "
; Fused expression:    "( *(2) (@-26) , GenNumLabel )2 "
    push    word [bp-26]
    call    _GenNumLabel
    sub     sp, -2
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
    sub     sp, -6
; }
    jmp     L4119
L4118:
; else
; if
; RPN'ized expression: "tok 22 == "
; Expanded expression: "(@4) *(2) 22 == "
; Fused expression:    "== *(@4) 22 IF! "
    mov     ax, [bp+4]
    cmp     ax, 22
    jne     L4173
; {
; loc         labelAfterIf : (@-22): int
    sub     sp, 2
; =
; RPN'ized expression: "LabelCnt ++p "
; Expanded expression: "LabelCnt ++p(2) "
; Fused expression:    "++p(2) *LabelCnt =(34) *(@-22) ax "
    mov     ax, [_LabelCnt]
    inc     word [_LabelCnt]
    mov     [bp-22], ax
; loc         labelAfterElse : (@-24): int
    sub     sp, 2
; =
; RPN'ized expression: "LabelCnt ++p "
; Expanded expression: "LabelCnt ++p(2) "
; Fused expression:    "++p(2) *LabelCnt =(34) *(@-24) ax "
    mov     ax, [_LabelCnt]
    inc     word [_LabelCnt]
    mov     [bp-24], ax
; RPN'ized expression: "( L4175 printf ) "
; Expanded expression: " L4175  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4175:
    db  "; if",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4175 , printf )2 "
    push    L4175
    call    _printf
    sub     sp, -2
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
; if
; RPN'ized expression: "tok 40 != "
; Expanded expression: "(@4) *(2) 40 != "
; Fused expression:    "!= *(@4) 40 IF! "
    mov     ax, [bp+4]
    cmp     ax, 40
    je      L4177
; RPN'ized expression: "( L4179 error ) "
; Expanded expression: " L4179  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4179:
    db  "Error: ParseStatement(): '(' expected after 'if'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4179 , error )2 "
    push    L4179
    call    _error
    sub     sp, -2
L4177:
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
; if
; RPN'ized expression: "( exprVal &u , constExpr &u , synPtr &u , gotUnary &u , tok ParseExpr ) 41 != "
; Expanded expression: " (@-8)  (@-6)  (@-4)  (@-2)  (@4) *(2)  ParseExpr ()10 41 != "
; Fused expression:    "( (@-8) , (@-6) , (@-4) , (@-2) , *(2) (@4) , ParseExpr )10 != ax 41 IF! "
    lea     ax, [bp-8]
    push    ax
    lea     ax, [bp-6]
    push    ax
    lea     ax, [bp-4]
    push    ax
    lea     ax, [bp-2]
    push    ax
    push    word [bp+4]
    call    _ParseExpr
    sub     sp, -10
    cmp     ax, 41
    je      L4181
; RPN'ized expression: "( L4183 error ) "
; Expanded expression: " L4183  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4183:
    db  "Error: ParseStatement(): ')' expected after 'if ( expression'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4183 , error )2 "
    push    L4183
    call    _error
    sub     sp, -2
L4181:
; if
; RPN'ized expression: "gotUnary 0 == "
; Expanded expression: "(@-2) *(2) 0 == "
; Fused expression:    "== *(@-2) 0 IF! "
    mov     ax, [bp-2]
    cmp     ax, 0
    jne     L4185
; RPN'ized expression: "( L4187 error ) "
; Expanded expression: " L4187  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4187:
    db  "Error: ParseStatement(): expression expected in 'if ( expression )'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4187 , error )2 "
    push    L4187
    call    _error
    sub     sp, -2
L4185:
; if
; RPN'ized expression: "synPtr 0 >= SyntaxStack synPtr + *u 0 + *u 17 == && "
; Expanded expression: "(@-4) *(2) 0 >= _Bool [sh&&->4191] SyntaxStack (@-4) *(2) 4 * + 0 + *(2) 17 == _Bool &&[4191] "
; Fused expression:    ">= *(@-4) 0 _Bool [sh&&->4191] * *(@-4) 4 + SyntaxStack ax + ax 0 == *ax 17 _Bool &&[4191] "
    mov     ax, [bp-4]
    cmp     ax, 0
    setge   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L4191
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 17
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L4191:
; JumpIfZero
    test    ax, ax
    jz      L4189
; RPN'ized expression: "( L4192 error ) "
; Expanded expression: " L4192  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4192:
    db  "Error: ParseStatement(): unexpected 'void' expression in 'if ( expression )'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4192 , error )2 "
    push    L4192
    call    _error
    sub     sp, -2
L4189:
; switch
; RPN'ized expression: "stack sp 1 - + *u 0 + *u "
; Expanded expression: "stack sp *(2) 1 - 4 * + 0 + *(2) "
; Fused expression:    "- *sp 1 * ax 4 + stack ax + ax 0 *(2) ax "
    mov     ax, [_sp]
    sub     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    jmp     L4196
; {
; case
; RPN'ized expression: "60 "
; Expanded expression: "60 "
; Expression value: 60
    jmp     L4197
L4196:
    cmp     ax, 60
    jne     L4198
L4197:
; case
; RPN'ized expression: "62 "
; Expanded expression: "62 "
; Expression value: 62
    jmp     L4199
L4198:
    cmp     ax, 62
    jne     L4200
L4199:
; case
; RPN'ized expression: "8 "
; Expanded expression: "8 "
; Expression value: 8
    jmp     L4201
L4200:
    cmp     ax, 8
    jne     L4202
L4201:
; case
; RPN'ized expression: "9 "
; Expanded expression: "9 "
; Expression value: 9
    jmp     L4203
L4202:
    cmp     ax, 9
    jne     L4204
L4203:
; case
; RPN'ized expression: "10 "
; Expanded expression: "10 "
; Expression value: 10
    jmp     L4205
L4204:
    cmp     ax, 10
    jne     L4206
L4205:
; case
; RPN'ized expression: "11 "
; Expanded expression: "11 "
; Expression value: 11
    jmp     L4207
L4206:
    cmp     ax, 11
    jne     L4208
L4207:
; case
; RPN'ized expression: "85 "
; Expanded expression: "85 "
; Expression value: 85
    jmp     L4209
L4208:
    cmp     ax, 85
    jne     L4210
L4209:
; case
; RPN'ized expression: "86 "
; Expanded expression: "86 "
; Expression value: 86
    jmp     L4211
L4210:
    cmp     ax, 86
    jne     L4212
L4211:
; case
; RPN'ized expression: "87 "
; Expanded expression: "87 "
; Expression value: 87
    jmp     L4213
L4212:
    cmp     ax, 87
    jne     L4214
L4213:
; case
; RPN'ized expression: "88 "
; Expanded expression: "88 "
; Expression value: 88
    jmp     L4215
L4214:
    cmp     ax, 88
    jne     L4216
L4215:
; RPN'ized expression: "( labelAfterIf , 76 push2 ) "
; Expanded expression: " (@-22) *(2)  76  push2 ()4 "
; Fused expression:    "( *(2) (@-22) , 76 , push2 )4 "
    push    word [bp-22]
    push    76
    call    _push2
    sub     sp, -4
; RPN'ized expression: "( GenExpr ) "
; Expanded expression: " GenExpr ()0 "
; Fused expression:    "( GenExpr )0 "
    call    _GenExpr
; break
    jmp     L4194
; default
L4195:
; RPN'ized expression: "( GenExpr ) "
; Expanded expression: " GenExpr ()0 "
; Fused expression:    "( GenExpr )0 "
    call    _GenExpr
; RPN'ized expression: "( labelAfterIf GenJumpIfZero ) "
; Expanded expression: " (@-22) *(2)  GenJumpIfZero ()2 "
; Fused expression:    "( *(2) (@-22) , GenJumpIfZero )2 "
    push    word [bp-22]
    call    _GenJumpIfZero
    sub     sp, -2
; break
    jmp     L4194
; }
    jmp     L4194
L4216:
    jmp     L4195
L4194:
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
; RPN'ized expression: "tok ( 0 , BrkCntSwchTarget , tok ParseStatement ) = "
; Expanded expression: "(@4)  0  (@6) *(2)  (@4) *(2)  ParseStatement ()6 =(2) "
; Fused expression:    "( 0 , *(2) (@6) , *(2) (@4) , ParseStatement )6 =(34) *(@4) ax "
    push    0
    push    word [bp+6]
    push    word [bp+4]
    call    _ParseStatement
    sub     sp, -6
    mov     [bp+4], ax
; if
; RPN'ized expression: "tok 23 == "
; Expanded expression: "(@4) *(2) 23 == "
; Fused expression:    "== *(@4) 23 IF! "
    mov     ax, [bp+4]
    cmp     ax, 23
    jne     L4218
; {
; RPN'ized expression: "( labelAfterElse GenJumpUncond ) "
; Expanded expression: " (@-24) *(2)  GenJumpUncond ()2 "
; Fused expression:    "( *(2) (@-24) , GenJumpUncond )2 "
    push    word [bp-24]
    call    _GenJumpUncond
    sub     sp, -2
; RPN'ized expression: "( labelAfterIf GenNumLabel ) "
; Expanded expression: " (@-22) *(2)  GenNumLabel ()2 "
; Fused expression:    "( *(2) (@-22) , GenNumLabel )2 "
    push    word [bp-22]
    call    _GenNumLabel
    sub     sp, -2
; RPN'ized expression: "( L4220 printf ) "
; Expanded expression: " L4220  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4220:
    db  "; else",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4220 , printf )2 "
    push    L4220
    call    _printf
    sub     sp, -2
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
; RPN'ized expression: "tok ( 0 , BrkCntSwchTarget , tok ParseStatement ) = "
; Expanded expression: "(@4)  0  (@6) *(2)  (@4) *(2)  ParseStatement ()6 =(2) "
; Fused expression:    "( 0 , *(2) (@6) , *(2) (@4) , ParseStatement )6 =(34) *(@4) ax "
    push    0
    push    word [bp+6]
    push    word [bp+4]
    call    _ParseStatement
    sub     sp, -6
    mov     [bp+4], ax
; RPN'ized expression: "( labelAfterElse GenNumLabel ) "
; Expanded expression: " (@-24) *(2)  GenNumLabel ()2 "
; Fused expression:    "( *(2) (@-24) , GenNumLabel )2 "
    push    word [bp-24]
    call    _GenNumLabel
    sub     sp, -2
; }
    jmp     L4219
L4218:
; else
; {
; RPN'ized expression: "( labelAfterIf GenNumLabel ) "
; Expanded expression: " (@-22) *(2)  GenNumLabel ()2 "
; Fused expression:    "( *(2) (@-22) , GenNumLabel )2 "
    push    word [bp-22]
    call    _GenNumLabel
    sub     sp, -2
; }
L4219:
    sub     sp, -4
; }
    jmp     L4174
L4173:
; else
; if
; RPN'ized expression: "tok 116 == "
; Expanded expression: "(@4) *(2) 116 == "
; Fused expression:    "== *(@4) 116 IF! "
    mov     ax, [bp+4]
    cmp     ax, 116
    jne     L4222
; {
; loc         labelBefore : (@-22): int
    sub     sp, 2
; =
; RPN'ized expression: "LabelCnt ++p "
; Expanded expression: "LabelCnt ++p(2) "
; Fused expression:    "++p(2) *LabelCnt =(34) *(@-22) ax "
    mov     ax, [_LabelCnt]
    inc     word [_LabelCnt]
    mov     [bp-22], ax
; loc         labelExpr3 : (@-24): int
    sub     sp, 2
; =
; RPN'ized expression: "LabelCnt ++p "
; Expanded expression: "LabelCnt ++p(2) "
; Fused expression:    "++p(2) *LabelCnt =(34) *(@-24) ax "
    mov     ax, [_LabelCnt]
    inc     word [_LabelCnt]
    mov     [bp-24], ax
; loc         labelBody : (@-26): int
    sub     sp, 2
; =
; RPN'ized expression: "LabelCnt ++p "
; Expanded expression: "LabelCnt ++p(2) "
; Fused expression:    "++p(2) *LabelCnt =(34) *(@-26) ax "
    mov     ax, [_LabelCnt]
    inc     word [_LabelCnt]
    mov     [bp-26], ax
; loc         labelAfter : (@-28): int
    sub     sp, 2
; =
; RPN'ized expression: "LabelCnt ++p "
; Expanded expression: "LabelCnt ++p(2) "
; Fused expression:    "++p(2) *LabelCnt =(34) *(@-28) ax "
    mov     ax, [_LabelCnt]
    inc     word [_LabelCnt]
    mov     [bp-28], ax
; RPN'ized expression: "( L4224 printf ) "
; Expanded expression: " L4224  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4224:
    db  "; for",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4224 , printf )2 "
    push    L4224
    call    _printf
    sub     sp, -2
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
; if
; RPN'ized expression: "tok 40 != "
; Expanded expression: "(@4) *(2) 40 != "
; Fused expression:    "!= *(@4) 40 IF! "
    mov     ax, [bp+4]
    cmp     ax, 40
    je      L4226
; RPN'ized expression: "( L4228 error ) "
; Expanded expression: " L4228  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4228:
    db  "Error: ParseStatement(): '(' expected after 'for'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4228 , error )2 "
    push    L4228
    call    _error
    sub     sp, -2
L4226:
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
; if
; RPN'ized expression: "( exprVal &u , constExpr &u , synPtr &u , gotUnary &u , tok ParseExpr ) 59 != "
; Expanded expression: " (@-8)  (@-6)  (@-4)  (@-2)  (@4) *(2)  ParseExpr ()10 59 != "
; Fused expression:    "( (@-8) , (@-6) , (@-4) , (@-2) , *(2) (@4) , ParseExpr )10 != ax 59 IF! "
    lea     ax, [bp-8]
    push    ax
    lea     ax, [bp-6]
    push    ax
    lea     ax, [bp-4]
    push    ax
    lea     ax, [bp-2]
    push    ax
    push    word [bp+4]
    call    _ParseExpr
    sub     sp, -10
    cmp     ax, 59
    je      L4230
; RPN'ized expression: "( L4232 error ) "
; Expanded expression: " L4232  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4232:
    db  "Error: ParseStatement(): ';' expected after 'for ( expression'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4232 , error )2 "
    push    L4232
    call    _error
    sub     sp, -2
L4230:
; if
; RPN'ized expression: "gotUnary "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
    mov     ax, [bp-2]
; JumpIfZero
    test    ax, ax
    jz      L4234
; {
; RPN'ized expression: "( GenExpr ) "
; Expanded expression: " GenExpr ()0 "
; Fused expression:    "( GenExpr )0 "
    call    _GenExpr
; }
L4234:
; RPN'ized expression: "( labelBefore GenNumLabel ) "
; Expanded expression: " (@-22) *(2)  GenNumLabel ()2 "
; Fused expression:    "( *(2) (@-22) , GenNumLabel )2 "
    push    word [bp-22]
    call    _GenNumLabel
    sub     sp, -2
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
; if
; RPN'ized expression: "( exprVal &u , constExpr &u , synPtr &u , gotUnary &u , tok ParseExpr ) 59 != "
; Expanded expression: " (@-8)  (@-6)  (@-4)  (@-2)  (@4) *(2)  ParseExpr ()10 59 != "
; Fused expression:    "( (@-8) , (@-6) , (@-4) , (@-2) , *(2) (@4) , ParseExpr )10 != ax 59 IF! "
    lea     ax, [bp-8]
    push    ax
    lea     ax, [bp-6]
    push    ax
    lea     ax, [bp-4]
    push    ax
    lea     ax, [bp-2]
    push    ax
    push    word [bp+4]
    call    _ParseExpr
    sub     sp, -10
    cmp     ax, 59
    je      L4236
; RPN'ized expression: "( L4238 error ) "
; Expanded expression: " L4238  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4238:
    db  "Error: ParseStatement(): ';' expected after 'for ( expression ; expression'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4238 , error )2 "
    push    L4238
    call    _error
    sub     sp, -2
L4236:
; if
; RPN'ized expression: "gotUnary "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
    mov     ax, [bp-2]
; JumpIfZero
    test    ax, ax
    jz      L4240
; {
; if
; RPN'ized expression: "synPtr 0 >= SyntaxStack synPtr + *u 0 + *u 17 == && "
; Expanded expression: "(@-4) *(2) 0 >= _Bool [sh&&->4244] SyntaxStack (@-4) *(2) 4 * + 0 + *(2) 17 == _Bool &&[4244] "
; Fused expression:    ">= *(@-4) 0 _Bool [sh&&->4244] * *(@-4) 4 + SyntaxStack ax + ax 0 == *ax 17 _Bool &&[4244] "
    mov     ax, [bp-4]
    cmp     ax, 0
    setge   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L4244
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 17
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L4244:
; JumpIfZero
    test    ax, ax
    jz      L4242
; RPN'ized expression: "( L4245 error ) "
; Expanded expression: " L4245  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4245:
    db  "Error: ParseStatement(): unexpected 'void' expression in 'for ( ; expression ; )'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4245 , error )2 "
    push    L4245
    call    _error
    sub     sp, -2
L4242:
; switch
; RPN'ized expression: "stack sp 1 - + *u 0 + *u "
; Expanded expression: "stack sp *(2) 1 - 4 * + 0 + *(2) "
; Fused expression:    "- *sp 1 * ax 4 + stack ax + ax 0 *(2) ax "
    mov     ax, [_sp]
    sub     ax, 1
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _stack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    jmp     L4249
; {
; case
; RPN'ized expression: "60 "
; Expanded expression: "60 "
; Expression value: 60
    jmp     L4250
L4249:
    cmp     ax, 60
    jne     L4251
L4250:
; case
; RPN'ized expression: "62 "
; Expanded expression: "62 "
; Expression value: 62
    jmp     L4252
L4251:
    cmp     ax, 62
    jne     L4253
L4252:
; case
; RPN'ized expression: "8 "
; Expanded expression: "8 "
; Expression value: 8
    jmp     L4254
L4253:
    cmp     ax, 8
    jne     L4255
L4254:
; case
; RPN'ized expression: "9 "
; Expanded expression: "9 "
; Expression value: 9
    jmp     L4256
L4255:
    cmp     ax, 9
    jne     L4257
L4256:
; case
; RPN'ized expression: "10 "
; Expanded expression: "10 "
; Expression value: 10
    jmp     L4258
L4257:
    cmp     ax, 10
    jne     L4259
L4258:
; case
; RPN'ized expression: "11 "
; Expanded expression: "11 "
; Expression value: 11
    jmp     L4260
L4259:
    cmp     ax, 11
    jne     L4261
L4260:
; case
; RPN'ized expression: "85 "
; Expanded expression: "85 "
; Expression value: 85
    jmp     L4262
L4261:
    cmp     ax, 85
    jne     L4263
L4262:
; case
; RPN'ized expression: "86 "
; Expanded expression: "86 "
; Expression value: 86
    jmp     L4264
L4263:
    cmp     ax, 86
    jne     L4265
L4264:
; case
; RPN'ized expression: "87 "
; Expanded expression: "87 "
; Expression value: 87
    jmp     L4266
L4265:
    cmp     ax, 87
    jne     L4267
L4266:
; case
; RPN'ized expression: "88 "
; Expanded expression: "88 "
; Expression value: 88
    jmp     L4268
L4267:
    cmp     ax, 88
    jne     L4269
L4268:
; RPN'ized expression: "( labelAfter , 76 push2 ) "
; Expanded expression: " (@-28) *(2)  76  push2 ()4 "
; Fused expression:    "( *(2) (@-28) , 76 , push2 )4 "
    push    word [bp-28]
    push    76
    call    _push2
    sub     sp, -4
; RPN'ized expression: "( GenExpr ) "
; Expanded expression: " GenExpr ()0 "
; Fused expression:    "( GenExpr )0 "
    call    _GenExpr
; break
    jmp     L4247
; default
L4248:
; RPN'ized expression: "( GenExpr ) "
; Expanded expression: " GenExpr ()0 "
; Fused expression:    "( GenExpr )0 "
    call    _GenExpr
; RPN'ized expression: "( labelAfter GenJumpIfZero ) "
; Expanded expression: " (@-28) *(2)  GenJumpIfZero ()2 "
; Fused expression:    "( *(2) (@-28) , GenJumpIfZero )2 "
    push    word [bp-28]
    call    _GenJumpIfZero
    sub     sp, -2
; break
    jmp     L4247
; }
    jmp     L4247
L4269:
    jmp     L4248
L4247:
; }
L4240:
; RPN'ized expression: "( labelBody GenJumpUncond ) "
; Expanded expression: " (@-26) *(2)  GenJumpUncond ()2 "
; Fused expression:    "( *(2) (@-26) , GenJumpUncond )2 "
    push    word [bp-26]
    call    _GenJumpUncond
    sub     sp, -2
; RPN'ized expression: "( labelExpr3 GenNumLabel ) "
; Expanded expression: " (@-24) *(2)  GenNumLabel ()2 "
; Fused expression:    "( *(2) (@-24) , GenNumLabel )2 "
    push    word [bp-24]
    call    _GenNumLabel
    sub     sp, -2
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
; if
; RPN'ized expression: "( exprVal &u , constExpr &u , synPtr &u , gotUnary &u , tok ParseExpr ) 41 != "
; Expanded expression: " (@-8)  (@-6)  (@-4)  (@-2)  (@4) *(2)  ParseExpr ()10 41 != "
; Fused expression:    "( (@-8) , (@-6) , (@-4) , (@-2) , *(2) (@4) , ParseExpr )10 != ax 41 IF! "
    lea     ax, [bp-8]
    push    ax
    lea     ax, [bp-6]
    push    ax
    lea     ax, [bp-4]
    push    ax
    lea     ax, [bp-2]
    push    ax
    push    word [bp+4]
    call    _ParseExpr
    sub     sp, -10
    cmp     ax, 41
    je      L4271
; RPN'ized expression: "( L4273 error ) "
; Expanded expression: " L4273  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4273:
    db  "Error: ParseStatement(): ')' expected after 'for ( expression ; expression ; expression'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4273 , error )2 "
    push    L4273
    call    _error
    sub     sp, -2
L4271:
; if
; RPN'ized expression: "gotUnary "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
    mov     ax, [bp-2]
; JumpIfZero
    test    ax, ax
    jz      L4275
; {
; RPN'ized expression: "( GenExpr ) "
; Expanded expression: " GenExpr ()0 "
; Fused expression:    "( GenExpr )0 "
    call    _GenExpr
; }
L4275:
; RPN'ized expression: "( labelBefore GenJumpUncond ) "
; Expanded expression: " (@-22) *(2)  GenJumpUncond ()2 "
; Fused expression:    "( *(2) (@-22) , GenJumpUncond )2 "
    push    word [bp-22]
    call    _GenJumpUncond
    sub     sp, -2
; RPN'ized expression: "( labelBody GenNumLabel ) "
; Expanded expression: " (@-26) *(2)  GenNumLabel ()2 "
; Fused expression:    "( *(2) (@-26) , GenNumLabel )2 "
    push    word [bp-26]
    call    _GenNumLabel
    sub     sp, -2
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
; RPN'ized expression: "brkCntSwchTarget 0 + *u labelAfter = "
; Expanded expression: "(@-20) 0 + (@-28) *(2) =(2) "
; Fused expression:    "+ (@-20) 0 =(34) *ax *(@-28) "
    lea     ax, [bp-20]
    add     ax, 0
    mov     bx, ax
    mov     ax, [bp-28]
    mov     [bx], ax
; RPN'ized expression: "brkCntSwchTarget 1 + *u labelExpr3 = "
; Expanded expression: "(@-20) 2 + (@-24) *(2) =(2) "
; Fused expression:    "+ (@-20) 2 =(34) *ax *(@-24) "
    lea     ax, [bp-20]
    add     ax, 2
    mov     bx, ax
    mov     ax, [bp-24]
    mov     [bx], ax
; RPN'ized expression: "brkCntSwchTarget 2 + *u CurFxnLocalOfs = "
; Expanded expression: "(@-20) 4 + CurFxnLocalOfs *(2) =(2) "
; Fused expression:    "+ (@-20) 4 =(34) *ax *CurFxnLocalOfs "
    lea     ax, [bp-20]
    add     ax, 4
    mov     bx, ax
    mov     ax, [_CurFxnLocalOfs]
    mov     [bx], ax
; RPN'ized expression: "brkCntSwchTarget 3 + *u CurFxnLocalOfs = "
; Expanded expression: "(@-20) 6 + CurFxnLocalOfs *(2) =(2) "
; Fused expression:    "+ (@-20) 6 =(34) *ax *CurFxnLocalOfs "
    lea     ax, [bp-20]
    add     ax, 6
    mov     bx, ax
    mov     ax, [_CurFxnLocalOfs]
    mov     [bx], ax
; RPN'ized expression: "tok ( 0 , brkCntSwchTarget , tok ParseStatement ) = "
; Expanded expression: "(@4)  0  (@-20)  (@4) *(2)  ParseStatement ()6 =(2) "
; Fused expression:    "( 0 , (@-20) , *(2) (@4) , ParseStatement )6 =(34) *(@4) ax "
    push    0
    lea     ax, [bp-20]
    push    ax
    push    word [bp+4]
    call    _ParseStatement
    sub     sp, -6
    mov     [bp+4], ax
; RPN'ized expression: "( labelExpr3 GenJumpUncond ) "
; Expanded expression: " (@-24) *(2)  GenJumpUncond ()2 "
; Fused expression:    "( *(2) (@-24) , GenJumpUncond )2 "
    push    word [bp-24]
    call    _GenJumpUncond
    sub     sp, -2
; RPN'ized expression: "( labelAfter GenNumLabel ) "
; Expanded expression: " (@-28) *(2)  GenNumLabel ()2 "
; Fused expression:    "( *(2) (@-28) , GenNumLabel )2 "
    push    word [bp-28]
    call    _GenNumLabel
    sub     sp, -2
    sub     sp, -8
; }
    jmp     L4223
L4222:
; else
; if
; RPN'ized expression: "tok 26 == "
; Expanded expression: "(@4) *(2) 26 == "
; Fused expression:    "== *(@4) 26 IF! "
    mov     ax, [bp+4]
    cmp     ax, 26
    jne     L4277
; {
; RPN'ized expression: "( L4279 printf ) "
; Expanded expression: " L4279  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4279:
    db  "; break",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4279 , printf )2 "
    push    L4279
    call    _printf
    sub     sp, -2
; if
; RPN'ized expression: "( GetToken ) 59 != "
; Expanded expression: " GetToken ()0 59 != "
; Fused expression:    "( GetToken )0 != ax 59 IF! "
    call    _GetToken
    cmp     ax, 59
    je      L4281
; RPN'ized expression: "( L4283 error ) "
; Expanded expression: " L4283  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4283:
    db  "Error: ParseStatement(): ';' expected",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4283 , error )2 "
    push    L4283
    call    _error
    sub     sp, -2
L4281:
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
; if
; RPN'ized expression: "BrkCntSwchTarget 0 == "
; Expanded expression: "(@6) *(2) 0 == "
; Fused expression:    "== *(@6) 0 IF! "
    mov     ax, [bp+6]
    cmp     ax, 0
    jne     L4285
; RPN'ized expression: "( L4287 error ) "
; Expanded expression: " L4287  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4287:
    db  "Error: ParseStatement(): 'break' must be within 'while', 'for' or 'switch' statement",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4287 , error )2 "
    push    L4287
    call    _error
    sub     sp, -2
L4285:
; if
; RPN'ized expression: "BrkCntSwchTarget 2 + *u CurFxnLocalOfs != "
; Expanded expression: "(@6) *(2) 4 + *(2) CurFxnLocalOfs *(2) != "
; Fused expression:    "+ *(@6) 4 != *ax *CurFxnLocalOfs IF! "
    mov     ax, [bp+6]
    add     ax, 4
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, [_CurFxnLocalOfs]
    je      L4289
; RPN'ized expression: "( CurFxnLocalOfs BrkCntSwchTarget 2 + *u - GenLocalAlloc ) "
; Expanded expression: " CurFxnLocalOfs *(2) (@6) *(2) 4 + *(2) -  GenLocalAlloc ()2 "
; Fused expression:    "( + *(@6) 4 - *CurFxnLocalOfs *ax , GenLocalAlloc )2 "
    mov     ax, [bp+6]
    add     ax, 4
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, [_CurFxnLocalOfs]
    sub     ax, cx
    push    ax
    call    _GenLocalAlloc
    sub     sp, -2
L4289:
; RPN'ized expression: "( BrkCntSwchTarget 0 + *u GenJumpUncond ) "
; Expanded expression: " (@6) *(2) 0 + *(2)  GenJumpUncond ()2 "
; Fused expression:    "( + *(@6) 0 *(2) ax , GenJumpUncond )2 "
    mov     ax, [bp+6]
    add     ax, 0
    mov     bx, ax
    push    word [bx]
    call    _GenJumpUncond
    sub     sp, -2
; }
    jmp     L4278
L4277:
; else
; if
; RPN'ized expression: "tok 25 == "
; Expanded expression: "(@4) *(2) 25 == "
; Fused expression:    "== *(@4) 25 IF! "
    mov     ax, [bp+4]
    cmp     ax, 25
    jne     L4291
; {
; RPN'ized expression: "( L4293 printf ) "
; Expanded expression: " L4293  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4293:
    db  "; continue",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4293 , printf )2 "
    push    L4293
    call    _printf
    sub     sp, -2
; if
; RPN'ized expression: "( GetToken ) 59 != "
; Expanded expression: " GetToken ()0 59 != "
; Fused expression:    "( GetToken )0 != ax 59 IF! "
    call    _GetToken
    cmp     ax, 59
    je      L4295
; RPN'ized expression: "( L4297 error ) "
; Expanded expression: " L4297  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4297:
    db  "Error: ParseStatement(): ';' expected",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4297 , error )2 "
    push    L4297
    call    _error
    sub     sp, -2
L4295:
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
; if
; RPN'ized expression: "BrkCntSwchTarget 0 == BrkCntSwchTarget 1 + *u 0 == || "
; Expanded expression: "(@6) *(2) 0 == _Bool [sh||->4301] (@6) *(2) 2 + *(2) 0 == _Bool ||[4301] "
; Fused expression:    "== *(@6) 0 _Bool [sh||->4301] + *(@6) 2 == *ax 0 _Bool ||[4301] "
    mov     ax, [bp+6]
    cmp     ax, 0
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L4301
    mov     ax, [bp+6]
    add     ax, 2
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 0
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L4301:
; JumpIfZero
    test    ax, ax
    jz      L4299
; RPN'ized expression: "( L4302 error ) "
; Expanded expression: " L4302  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4302:
    db  "Error: ParseStatement(): 'continue' must be within 'while' or 'for' statement",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4302 , error )2 "
    push    L4302
    call    _error
    sub     sp, -2
L4299:
; if
; RPN'ized expression: "BrkCntSwchTarget 3 + *u CurFxnLocalOfs != "
; Expanded expression: "(@6) *(2) 6 + *(2) CurFxnLocalOfs *(2) != "
; Fused expression:    "+ *(@6) 6 != *ax *CurFxnLocalOfs IF! "
    mov     ax, [bp+6]
    add     ax, 6
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, [_CurFxnLocalOfs]
    je      L4304
; RPN'ized expression: "( CurFxnLocalOfs BrkCntSwchTarget 3 + *u - GenLocalAlloc ) "
; Expanded expression: " CurFxnLocalOfs *(2) (@6) *(2) 6 + *(2) -  GenLocalAlloc ()2 "
; Fused expression:    "( + *(@6) 6 - *CurFxnLocalOfs *ax , GenLocalAlloc )2 "
    mov     ax, [bp+6]
    add     ax, 6
    mov     bx, ax
    mov     cx, [bx]
    mov     ax, [_CurFxnLocalOfs]
    sub     ax, cx
    push    ax
    call    _GenLocalAlloc
    sub     sp, -2
L4304:
; RPN'ized expression: "( BrkCntSwchTarget 1 + *u GenJumpUncond ) "
; Expanded expression: " (@6) *(2) 2 + *(2)  GenJumpUncond ()2 "
; Fused expression:    "( + *(@6) 2 *(2) ax , GenJumpUncond )2 "
    mov     ax, [bp+6]
    add     ax, 2
    mov     bx, ax
    push    word [bx]
    call    _GenJumpUncond
    sub     sp, -2
; }
    jmp     L4292
L4291:
; else
; if
; RPN'ized expression: "tok 117 == "
; Expanded expression: "(@4) *(2) 117 == "
; Fused expression:    "== *(@4) 117 IF! "
    mov     ax, [bp+4]
    cmp     ax, 117
    jne     L4306
; {
; RPN'ized expression: "( L4308 printf ) "
; Expanded expression: " L4308  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4308:
    db  "; switch",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4308 , printf )2 "
    push    L4308
    call    _printf
    sub     sp, -2
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
; if
; RPN'ized expression: "tok 40 != "
; Expanded expression: "(@4) *(2) 40 != "
; Fused expression:    "!= *(@4) 40 IF! "
    mov     ax, [bp+4]
    cmp     ax, 40
    je      L4310
; RPN'ized expression: "( L4312 error ) "
; Expanded expression: " L4312  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4312:
    db  "Error: ParseStatement(): '(' expected after 'switch'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4312 , error )2 "
    push    L4312
    call    _error
    sub     sp, -2
L4310:
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
; if
; RPN'ized expression: "( exprVal &u , constExpr &u , synPtr &u , gotUnary &u , tok ParseExpr ) 41 != "
; Expanded expression: " (@-8)  (@-6)  (@-4)  (@-2)  (@4) *(2)  ParseExpr ()10 41 != "
; Fused expression:    "( (@-8) , (@-6) , (@-4) , (@-2) , *(2) (@4) , ParseExpr )10 != ax 41 IF! "
    lea     ax, [bp-8]
    push    ax
    lea     ax, [bp-6]
    push    ax
    lea     ax, [bp-4]
    push    ax
    lea     ax, [bp-2]
    push    ax
    push    word [bp+4]
    call    _ParseExpr
    sub     sp, -10
    cmp     ax, 41
    je      L4314
; RPN'ized expression: "( L4316 error ) "
; Expanded expression: " L4316  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4316:
    db  "Error: ParseStatement(): ')' expected after 'switch ( expression'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4316 , error )2 "
    push    L4316
    call    _error
    sub     sp, -2
L4314:
; if
; RPN'ized expression: "gotUnary 0 == "
; Expanded expression: "(@-2) *(2) 0 == "
; Fused expression:    "== *(@-2) 0 IF! "
    mov     ax, [bp-2]
    cmp     ax, 0
    jne     L4318
; RPN'ized expression: "( L4320 error ) "
; Expanded expression: " L4320  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4320:
    db  "Error: ParseStatement(): expression expected in 'switch ( expression )'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4320 , error )2 "
    push    L4320
    call    _error
    sub     sp, -2
L4318:
; if
; RPN'ized expression: "synPtr 0 >= SyntaxStack synPtr + *u 0 + *u 17 == && "
; Expanded expression: "(@-4) *(2) 0 >= _Bool [sh&&->4324] SyntaxStack (@-4) *(2) 4 * + 0 + *(2) 17 == _Bool &&[4324] "
; Fused expression:    ">= *(@-4) 0 _Bool [sh&&->4324] * *(@-4) 4 + SyntaxStack ax + ax 0 == *ax 17 _Bool &&[4324] "
    mov     ax, [bp-4]
    cmp     ax, 0
    setge   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L4324
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 17
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L4324:
; JumpIfZero
    test    ax, ax
    jz      L4322
; RPN'ized expression: "( L4325 error ) "
; Expanded expression: " L4325  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4325:
    db  "Error: ParseStatement(): unexpected 'void' expression in 'switch ( expression )'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4325 , error )2 "
    push    L4325
    call    _error
    sub     sp, -2
L4322:
; RPN'ized expression: "( GenExpr ) "
; Expanded expression: " GenExpr ()0 "
; Fused expression:    "( GenExpr )0 "
    call    _GenExpr
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
; if
; RPN'ized expression: "tok 123 != "
; Expanded expression: "(@4) *(2) 123 != "
; Fused expression:    "!= *(@4) 123 IF! "
    mov     ax, [bp+4]
    cmp     ax, 123
    je      L4327
; RPN'ized expression: "( L4329 error ) "
; Expanded expression: " L4329  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4329:
    db  "Error: ParseStatement(): '{' expected after 'switch ( expression )'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4329 , error )2 "
    push    L4329
    call    _error
    sub     sp, -2
L4327:
; RPN'ized expression: "brkCntSwchTarget 0 + *u LabelCnt ++p = "
; Expanded expression: "(@-20) 0 + LabelCnt ++p(2) =(2) "
; Fused expression:    "+ (@-20) 0 push-ax ++p(2) *LabelCnt =(34) **sp ax "
    lea     ax, [bp-20]
    add     ax, 0
    push    ax
    mov     ax, [_LabelCnt]
    inc     word [_LabelCnt]
    pop     bx
    mov     [bx], ax
; RPN'ized expression: "brkCntSwchTarget 1 + *u 0 = "
; Expanded expression: "(@-20) 2 + 0 =(2) "
; Fused expression:    "+ (@-20) 2 =(34) *ax 0 "
    lea     ax, [bp-20]
    add     ax, 2
    mov     bx, ax
    mov     ax, 0
    mov     [bx], ax
; RPN'ized expression: "brkCntSwchTarget 2 + *u CurFxnLocalOfs = "
; Expanded expression: "(@-20) 4 + CurFxnLocalOfs *(2) =(2) "
; Fused expression:    "+ (@-20) 4 =(34) *ax *CurFxnLocalOfs "
    lea     ax, [bp-20]
    add     ax, 4
    mov     bx, ax
    mov     ax, [_CurFxnLocalOfs]
    mov     [bx], ax
; RPN'ized expression: "brkCntSwchTarget 3 + *u 0 = "
; Expanded expression: "(@-20) 6 + 0 =(2) "
; Fused expression:    "+ (@-20) 6 =(34) *ax 0 "
    lea     ax, [bp-20]
    add     ax, 6
    mov     bx, ax
    mov     ax, 0
    mov     [bx], ax
; if
; RPN'ized expression: "BrkCntSwchTarget 0 != "
; Expanded expression: "(@6) *(2) 0 != "
; Fused expression:    "!= *(@6) 0 IF! "
    mov     ax, [bp+6]
    cmp     ax, 0
    je      L4331
; {
; RPN'ized expression: "brkCntSwchTarget 1 + *u BrkCntSwchTarget 1 + *u = "
; Expanded expression: "(@-20) 2 + (@6) *(2) 2 + *(2) =(2) "
; Fused expression:    "+ (@-20) 2 push-ax + *(@6) 2 =(34) **sp *ax "
    lea     ax, [bp-20]
    add     ax, 2
    push    ax
    mov     ax, [bp+6]
    add     ax, 2
    mov     bx, ax
    mov     ax, [bx]
    pop     bx
    mov     [bx], ax
; RPN'ized expression: "brkCntSwchTarget 3 + *u BrkCntSwchTarget 3 + *u = "
; Expanded expression: "(@-20) 6 + (@6) *(2) 6 + *(2) =(2) "
; Fused expression:    "+ (@-20) 6 push-ax + *(@6) 6 =(34) **sp *ax "
    lea     ax, [bp-20]
    add     ax, 6
    push    ax
    mov     ax, [bp+6]
    add     ax, 6
    mov     bx, ax
    mov     ax, [bx]
    pop     bx
    mov     [bx], ax
; }
L4331:
; RPN'ized expression: "brkCntSwchTarget 4 + *u LabelCnt ++p = "
; Expanded expression: "(@-20) 8 + LabelCnt ++p(2) =(2) "
; Fused expression:    "+ (@-20) 8 push-ax ++p(2) *LabelCnt =(34) **sp ax "
    lea     ax, [bp-20]
    add     ax, 8
    push    ax
    mov     ax, [_LabelCnt]
    inc     word [_LabelCnt]
    pop     bx
    mov     [bx], ax
; RPN'ized expression: "brkCntSwchTarget 5 + *u LabelCnt 2 += 2 - = "
; Expanded expression: "(@-20) 10 + LabelCnt 2 +=(2) 2 - =(2) "
; Fused expression:    "+ (@-20) 10 push-ax +=(34) *LabelCnt 2 - ax 2 =(34) **sp ax "
    lea     ax, [bp-20]
    add     ax, 10
    push    ax
    mov     ax, [_LabelCnt]
    add     ax, 2
    mov     [_LabelCnt], ax
    sub     ax, 2
    pop     bx
    mov     [bx], ax
; RPN'ized expression: "( brkCntSwchTarget 5 + *u GenJumpUncond ) "
; Expanded expression: " (@-20) 10 + *(2)  GenJumpUncond ()2 "
; Fused expression:    "( + (@-20) 10 *(2) ax , GenJumpUncond )2 "
    lea     ax, [bp-20]
    add     ax, 10
    mov     bx, ax
    push    word [bx]
    call    _GenJumpUncond
    sub     sp, -2
; RPN'ized expression: "tok ( 2 , brkCntSwchTarget , tok ParseStatement ) = "
; Expanded expression: "(@4)  2  (@-20)  (@4) *(2)  ParseStatement ()6 =(2) "
; Fused expression:    "( 2 , (@-20) , *(2) (@4) , ParseStatement )6 =(34) *(@4) ax "
    push    2
    lea     ax, [bp-20]
    push    ax
    push    word [bp+4]
    call    _ParseStatement
    sub     sp, -6
    mov     [bp+4], ax
; RPN'ized expression: "( brkCntSwchTarget 0 + *u GenJumpUncond ) "
; Expanded expression: " (@-20) 0 + *(2)  GenJumpUncond ()2 "
; Fused expression:    "( + (@-20) 0 *(2) ax , GenJumpUncond )2 "
    lea     ax, [bp-20]
    add     ax, 0
    mov     bx, ax
    push    word [bx]
    call    _GenJumpUncond
    sub     sp, -2
; RPN'ized expression: "( brkCntSwchTarget 5 + *u GenNumLabel ) "
; Expanded expression: " (@-20) 10 + *(2)  GenNumLabel ()2 "
; Fused expression:    "( + (@-20) 10 *(2) ax , GenNumLabel )2 "
    lea     ax, [bp-20]
    add     ax, 10
    mov     bx, ax
    push    word [bx]
    call    _GenNumLabel
    sub     sp, -2
; if
; RPN'ized expression: "brkCntSwchTarget 4 + *u 0 < "
; Expanded expression: "(@-20) 8 + *(2) 0 < "
; Fused expression:    "+ (@-20) 8 < *ax 0 IF! "
    lea     ax, [bp-20]
    add     ax, 8
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 0
    jge     L4333
; RPN'ized expression: "( brkCntSwchTarget 4 + *u -u GenJumpUncond ) "
; Expanded expression: " (@-20) 8 + *(2) -u  GenJumpUncond ()2 "
; Fused expression:    "( + (@-20) 8 *(2) ax -u , GenJumpUncond )2 "
    lea     ax, [bp-20]
    add     ax, 8
    mov     bx, ax
    mov     ax, [bx]
    neg     ax
    push    ax
    call    _GenJumpUncond
    sub     sp, -2
L4333:
; RPN'ized expression: "( brkCntSwchTarget 0 + *u GenNumLabel ) "
; Expanded expression: " (@-20) 0 + *(2)  GenNumLabel ()2 "
; Fused expression:    "( + (@-20) 0 *(2) ax , GenNumLabel )2 "
    lea     ax, [bp-20]
    add     ax, 0
    mov     bx, ax
    push    word [bx]
    call    _GenNumLabel
    sub     sp, -2
; }
    jmp     L4307
L4306:
; else
; if
; RPN'ized expression: "tok 118 == "
; Expanded expression: "(@4) *(2) 118 == "
; Fused expression:    "== *(@4) 118 IF! "
    mov     ax, [bp+4]
    cmp     ax, 118
    jne     L4335
; {
; loc         lnext : (@-22): int
    sub     sp, 2
; RPN'ized expression: "( L4337 printf ) "
; Expanded expression: " L4337  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4337:
    db  "; case",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4337 , printf )2 "
    push    L4337
    call    _printf
    sub     sp, -2
; if
; RPN'ized expression: "switchBody 0 == "
; Expanded expression: "(@8) *(2) 0 == "
; Fused expression:    "== *(@8) 0 IF! "
    mov     ax, [bp+8]
    cmp     ax, 0
    jne     L4339
; RPN'ized expression: "( L4341 error ) "
; Expanded expression: " L4341  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4341:
    db  "Error: ParseStatement(): 'case' must be within 'switch' statement",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4341 , error )2 "
    push    L4341
    call    _error
    sub     sp, -2
L4339:
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
; if
; RPN'ized expression: "( exprVal &u , constExpr &u , synPtr &u , gotUnary &u , tok ParseExpr ) 58 != "
; Expanded expression: " (@-8)  (@-6)  (@-4)  (@-2)  (@4) *(2)  ParseExpr ()10 58 != "
; Fused expression:    "( (@-8) , (@-6) , (@-4) , (@-2) , *(2) (@4) , ParseExpr )10 != ax 58 IF! "
    lea     ax, [bp-8]
    push    ax
    lea     ax, [bp-6]
    push    ax
    lea     ax, [bp-4]
    push    ax
    lea     ax, [bp-2]
    push    ax
    push    word [bp+4]
    call    _ParseExpr
    sub     sp, -10
    cmp     ax, 58
    je      L4343
; RPN'ized expression: "( L4345 error ) "
; Expanded expression: " L4345  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4345:
    db  "Error: ParseStatement(): ':' expected after 'case expression'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4345 , error )2 "
    push    L4345
    call    _error
    sub     sp, -2
L4343:
; if
; RPN'ized expression: "gotUnary 0 == constExpr 0 == || synPtr 0 >= SyntaxStack synPtr + *u 0 + *u 17 == && || "
; Expanded expression: "(@-2) *(2) 0 == _Bool [sh||->4351] (@-6) *(2) 0 == _Bool ||[4351] _Bool [sh||->4349] (@-4) *(2) 0 >= _Bool [sh&&->4350] SyntaxStack (@-4) *(2) 4 * + 0 + *(2) 17 == _Bool &&[4350] _Bool ||[4349] "
; Fused expression:    "== *(@-2) 0 _Bool [sh||->4351] == *(@-6) 0 _Bool ||[4351] _Bool [sh||->4349] >= *(@-4) 0 _Bool [sh&&->4350] * *(@-4) 4 + SyntaxStack ax + ax 0 == *ax 17 _Bool &&[4350] _Bool ||[4349] "
    mov     ax, [bp-2]
    cmp     ax, 0
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L4351
    mov     ax, [bp-6]
    cmp     ax, 0
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L4351:
    test    ax, ax
    setnz   al
    cbw
; JumpIfNotZero
    test    ax, ax
    jnz     L4349
    mov     ax, [bp-4]
    cmp     ax, 0
    setge   al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L4350
    mov     ax, [bp-4]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 17
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L4350:
    test    ax, ax
    setnz   al
    cbw
L4349:
; JumpIfZero
    test    ax, ax
    jz      L4347
; RPN'ized expression: "( L4352 error ) "
; Expanded expression: " L4352  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4352:
    db  "Error: ParseStatement(): constant integer expression expected in 'case expression :'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4352 , error )2 "
    push    L4352
    call    _error
    sub     sp, -2
L4347:
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
; RPN'ized expression: "lnext LabelCnt 2 += 2 - = "
; Expanded expression: "(@-22) LabelCnt 2 +=(2) 2 - =(2) "
; Fused expression:    "+=(34) *LabelCnt 2 - ax 2 =(34) *(@-22) ax "
    mov     ax, [_LabelCnt]
    add     ax, 2
    mov     [_LabelCnt], ax
    sub     ax, 2
    mov     [bp-22], ax
; RPN'ized expression: "( BrkCntSwchTarget 5 + *u 1 + GenJumpUncond ) "
; Expanded expression: " (@6) *(2) 10 + *(2) 1 +  GenJumpUncond ()2 "
; Fused expression:    "( + *(@6) 10 + *ax 1 , GenJumpUncond )2 "
    mov     ax, [bp+6]
    add     ax, 10
    mov     bx, ax
    mov     ax, [bx]
    add     ax, 1
    push    ax
    call    _GenJumpUncond
    sub     sp, -2
; RPN'ized expression: "( BrkCntSwchTarget 5 + *u GenNumLabel ) "
; Expanded expression: " (@6) *(2) 10 + *(2)  GenNumLabel ()2 "
; Fused expression:    "( + *(@6) 10 *(2) ax , GenNumLabel )2 "
    mov     ax, [bp+6]
    add     ax, 10
    mov     bx, ax
    push    word [bx]
    call    _GenNumLabel
    sub     sp, -2
; RPN'ized expression: "( lnext , exprVal GenJumpIfNotEqual ) "
; Expanded expression: " (@-22) *(2)  (@-8) *(2)  GenJumpIfNotEqual ()4 "
; Fused expression:    "( *(2) (@-22) , *(2) (@-8) , GenJumpIfNotEqual )4 "
    push    word [bp-22]
    push    word [bp-8]
    call    _GenJumpIfNotEqual
    sub     sp, -4
; RPN'ized expression: "( BrkCntSwchTarget 5 + *u 1 + GenNumLabel ) "
; Expanded expression: " (@6) *(2) 10 + *(2) 1 +  GenNumLabel ()2 "
; Fused expression:    "( + *(@6) 10 + *ax 1 , GenNumLabel )2 "
    mov     ax, [bp+6]
    add     ax, 10
    mov     bx, ax
    mov     ax, [bx]
    add     ax, 1
    push    ax
    call    _GenNumLabel
    sub     sp, -2
; RPN'ized expression: "BrkCntSwchTarget 5 + *u lnext = "
; Expanded expression: "(@6) *(2) 10 + (@-22) *(2) =(2) "
; Fused expression:    "+ *(@6) 10 =(34) *ax *(@-22) "
    mov     ax, [bp+6]
    add     ax, 10
    mov     bx, ax
    mov     ax, [bp-22]
    mov     [bx], ax
    sub     sp, -2
; }
    jmp     L4336
L4335:
; else
; if
; RPN'ized expression: "tok 119 == "
; Expanded expression: "(@4) *(2) 119 == "
; Fused expression:    "== *(@4) 119 IF! "
    mov     ax, [bp+4]
    cmp     ax, 119
    jne     L4354
; {
; RPN'ized expression: "( L4356 printf ) "
; Expanded expression: " L4356  printf ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4356:
    db  "; default",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4356 , printf )2 "
    push    L4356
    call    _printf
    sub     sp, -2
; if
; RPN'ized expression: "switchBody 0 == "
; Expanded expression: "(@8) *(2) 0 == "
; Fused expression:    "== *(@8) 0 IF! "
    mov     ax, [bp+8]
    cmp     ax, 0
    jne     L4358
; RPN'ized expression: "( L4360 error ) "
; Expanded expression: " L4360  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4360:
    db  "Error: ParseStatement(): 'default' must be within 'switch' statement",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4360 , error )2 "
    push    L4360
    call    _error
    sub     sp, -2
L4358:
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
; if
; RPN'ized expression: "tok 58 != "
; Expanded expression: "(@4) *(2) 58 != "
; Fused expression:    "!= *(@4) 58 IF! "
    mov     ax, [bp+4]
    cmp     ax, 58
    je      L4362
; RPN'ized expression: "( L4364 error ) "
; Expanded expression: " L4364  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4364:
    db  "Error: ParseStatement(): ':' expected after 'default'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4364 , error )2 "
    push    L4364
    call    _error
    sub     sp, -2
L4362:
; if
; RPN'ized expression: "BrkCntSwchTarget 4 + *u 0 < "
; Expanded expression: "(@6) *(2) 8 + *(2) 0 < "
; Fused expression:    "+ *(@6) 8 < *ax 0 IF! "
    mov     ax, [bp+6]
    add     ax, 8
    mov     bx, ax
    mov     ax, [bx]
    cmp     ax, 0
    jge     L4366
; RPN'ized expression: "( L4368 error ) "
; Expanded expression: " L4368  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4368:
    db  "Error: ParseStatement(): only one 'default' allowed in 'switch'",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4368 , error )2 "
    push    L4368
    call    _error
    sub     sp, -2
L4366:
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
; RPN'ized expression: "( BrkCntSwchTarget 4 + *u GenNumLabel ) "
; Expanded expression: " (@6) *(2) 8 + *(2)  GenNumLabel ()2 "
; Fused expression:    "( + *(@6) 8 *(2) ax , GenNumLabel )2 "
    mov     ax, [bp+6]
    add     ax, 8
    mov     bx, ax
    push    word [bx]
    call    _GenNumLabel
    sub     sp, -2
; RPN'ized expression: "BrkCntSwchTarget 4 + *u 1 -u *= "
; Expanded expression: "(@6) *(2) 8 + -1 *=(2) "
; Fused expression:    "+ *(@6) 8 *=(34) *ax -1 "
    mov     ax, [bp+6]
    add     ax, 8
    mov     bx, ax
    mov     ax, [bx]
    imul    ax, ax, -1
    mov     [bx], ax
; }
    jmp     L4355
L4354:
; else
; {
; if
; RPN'ized expression: "( exprVal &u , constExpr &u , synPtr &u , gotUnary &u , tok ParseExpr ) 59 != "
; Expanded expression: " (@-8)  (@-6)  (@-4)  (@-2)  (@4) *(2)  ParseExpr ()10 59 != "
; Fused expression:    "( (@-8) , (@-6) , (@-4) , (@-2) , *(2) (@4) , ParseExpr )10 != ax 59 IF! "
    lea     ax, [bp-8]
    push    ax
    lea     ax, [bp-6]
    push    ax
    lea     ax, [bp-4]
    push    ax
    lea     ax, [bp-2]
    push    ax
    push    word [bp+4]
    call    _ParseExpr
    sub     sp, -10
    cmp     ax, 59
    je      L4370
; RPN'ized expression: "( L4372 error ) "
; Expanded expression: " L4372  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4372:
    db  "Error: ParseStatement(): ';' expected",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4372 , error )2 "
    push    L4372
    call    _error
    sub     sp, -2
L4370:
; if
; RPN'ized expression: "gotUnary "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
    mov     ax, [bp-2]
; JumpIfZero
    test    ax, ax
    jz      L4374
; {
; RPN'ized expression: "( GenExpr ) "
; Expanded expression: " GenExpr ()0 "
; Fused expression:    "( GenExpr )0 "
    call    _GenExpr
; }
L4374:
; RPN'ized expression: "tok ( GetToken ) = "
; Expanded expression: "(@4)  GetToken ()0 =(2) "
; Fused expression:    "( GetToken )0 =(34) *(@4) ax "
    call    _GetToken
    mov     [bp+4], ax
; }
L4355:
L4336:
L4307:
L4292:
L4278:
L4223:
L4174:
L4119:
L4074:
L4053:
L4041:
L4039:
; return
; RPN'ized expression: "tok "
; Expanded expression: "(@4) *(2) "
; Fused expression:    "*(2) (@4) "
    mov     ax, [bp+4]
    jmp     L4037
L4037:
    leave
    ret
; SEGMENT _TEXT
; RPN'ized expression: "6 "
; Expanded expression: "6 "
; Expression value: 6
; glb ParseBlock : (
; prm     BrkCntSwchTarget : * int
; prm     switchBody : int
;     ) int
SEGMENT _TEXT
    global  _ParseBlock
_ParseBlock:
    push    bp
    mov     bp, sp
; loc     BrkCntSwchTarget : (@4): * int
; loc     switchBody : (@6): int
; loc     tok : (@-2): int
    sub     sp, 2
; =
; RPN'ized expression: "( GetToken ) "
; Expanded expression: " GetToken ()0 "
; Fused expression:    "( GetToken )0 =(34) *(@-2) ax "
    call    _GetToken
    mov     [bp-2], ax
; for
L4377:
    jmp     L4379
L4378:
    jmp     L4377
L4379:
; {
; if
; RPN'ized expression: "tok 0 == "
; Expanded expression: "(@-2) *(2) 0 == "
; Fused expression:    "== *(@-2) 0 IF! "
    mov     ax, [bp-2]
    cmp     ax, 0
    jne     L4381
; return
; RPN'ized expression: "tok "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
    mov     ax, [bp-2]
    jmp     L4376
L4381:
; if
; RPN'ized expression: "tok 125 == ParseLevel 0 > && "
; Expanded expression: "(@-2) *(2) 125 == _Bool [sh&&->4385] ParseLevel *(2) 0 > _Bool &&[4385] "
; Fused expression:    "== *(@-2) 125 _Bool [sh&&->4385] > *ParseLevel 0 _Bool &&[4385] "
    mov     ax, [bp-2]
    cmp     ax, 125
    sete    al
    cbw
    test    ax, ax
    setnz   al
    cbw
; JumpIfZero
    test    ax, ax
    jz      L4385
    mov     ax, [_ParseLevel]
    cmp     ax, 0
    setg    al
    cbw
    test    ax, ax
    setnz   al
    cbw
L4385:
; JumpIfZero
    test    ax, ax
    jz      L4383
; return
; RPN'ized expression: "tok "
; Expanded expression: "(@-2) *(2) "
; Fused expression:    "*(2) (@-2) "
    mov     ax, [bp-2]
    jmp     L4376
L4383:
; if
; RPN'ized expression: "( 0 , tok TokenStartsDeclaration ) "
; Expanded expression: " 0  (@-2) *(2)  TokenStartsDeclaration ()4 "
; Fused expression:    "( 0 , *(2) (@-2) , TokenStartsDeclaration )4 "
    push    0
    push    word [bp-2]
    call    _TokenStartsDeclaration
    sub     sp, -4
; JumpIfZero
    test    ax, ax
    jz      L4386
; {
; if
; RPN'ized expression: "switchBody "
; Expanded expression: "(@6) *(2) "
; Fused expression:    "*(2) (@6) "
    mov     ax, [bp+6]
; JumpIfZero
    test    ax, ax
    jz      L4388
; RPN'ized expression: "( L4390 error ) "
; Expanded expression: " L4390  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4390:
    db  "Error: ParseBlock(): Declarations aren't supported in 'switch' body",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4390 , error )2 "
    push    L4390
    call    _error
    sub     sp, -2
L4388:
; RPN'ized expression: "tok ( tok ParseDecl ) = "
; Expanded expression: "(@-2)  (@-2) *(2)  ParseDecl ()2 =(2) "
; Fused expression:    "( *(2) (@-2) , ParseDecl )2 =(34) *(@-2) ax "
    push    word [bp-2]
    call    _ParseDecl
    sub     sp, -2
    mov     [bp-2], ax
; }
    jmp     L4387
L4386:
; else
; if
; RPN'ized expression: "ParseLevel 0 > "
; Expanded expression: "ParseLevel *(2) 0 > "
; Fused expression:    "> *ParseLevel 0 IF! "
    mov     ax, [_ParseLevel]
    cmp     ax, 0
    jle     L4392
; {
; RPN'ized expression: "tok ( switchBody , BrkCntSwchTarget , tok ParseStatement ) = "
; Expanded expression: "(@-2)  (@6) *(2)  (@4) *(2)  (@-2) *(2)  ParseStatement ()6 =(2) "
; Fused expression:    "( *(2) (@6) , *(2) (@4) , *(2) (@-2) , ParseStatement )6 =(34) *(@-2) ax "
    push    word [bp+6]
    push    word [bp+4]
    push    word [bp-2]
    call    _ParseStatement
    sub     sp, -6
    mov     [bp-2], ax
; }
    jmp     L4393
L4392:
; else
; RPN'ized expression: "( ( tok GetTokenName ) , L4394 error ) "
; Expanded expression: "  (@-2) *(2)  GetTokenName ()2  L4394  error ()4 "
; SEGMENT _TEXT
SEGMENT _DATA
L4394:
    db  "Error: ParseBlock(): Unexpected token %s",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( ( *(2) (@-2) , GetTokenName )2 , L4394 , error )4 "
    push    word [bp-2]
    call    _GetTokenName
    sub     sp, -2
    push    ax
    push    L4394
    call    _error
    sub     sp, -4
L4393:
L4387:
; }
    jmp     L4378
L4380:
L4376:
    leave
    ret
; SEGMENT _TEXT
; glb main : (
; prm     argc : int
; prm     argv : * * char
;     ) int
SEGMENT _TEXT
    global  _main
_main:
    push    bp
    mov     bp, sp
; loc     argc : (@4): int
; loc     argv : (@6): * * char
; if
; RPN'ized expression: "argc 2 != "
; Expanded expression: "(@4) *(2) 2 != "
; Fused expression:    "!= *(@4) 2 IF! "
    mov     ax, [bp+4]
    cmp     ax, 2
    je      L4397
; {
; RPN'ized expression: "CurFileName L4399 = "
; Expanded expression: "CurFileName L4399 =(2) "
; SEGMENT _TEXT
SEGMENT _DATA
L4399:
    db  0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "=(34) *CurFileName L4399 "
    mov     ax, L4399
    mov     [_CurFileName], ax
; RPN'ized expression: "( L4401 error ) "
; Expanded expression: " L4401  error ()2 "
; SEGMENT _TEXT
SEGMENT _DATA
L4401:
    db  "Error: Wrong command line parameters, just a filename expected",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "( L4401 , error )2 "
    push    L4401
    call    _error
    sub     sp, -2
; }
L4397:
; RPN'ized expression: "CurFileName argv 1 + *u = "
; Expanded expression: "CurFileName (@6) *(2) 2 + *(2) =(2) "
; Fused expression:    "+ *(@6) 2 =(34) *CurFileName *ax "
    mov     ax, [bp+6]
    add     ax, 2
    mov     bx, ax
    mov     ax, [bx]
    mov     [_CurFileName], ax
; RPN'ized expression: "SyntaxStack SyntaxStackCnt + *u 0 + *u 17 = "
; Expanded expression: "SyntaxStack SyntaxStackCnt *(2) 4 * + 0 + 17 =(2) "
; Fused expression:    "* *SyntaxStackCnt 4 + SyntaxStack ax + ax 0 =(34) *ax 17 "
    mov     ax, [_SyntaxStackCnt]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, 17
    mov     [bx], ax
; RPN'ized expression: "SyntaxStack SyntaxStackCnt ++p + *u 1 + *u 0 = "
; Expanded expression: "SyntaxStack SyntaxStackCnt ++p(2) 4 * + 2 + 0 =(2) "
; Fused expression:    "++p(2) *SyntaxStackCnt * ax 4 + SyntaxStack ax + ax 2 =(34) *ax 0 "
    mov     ax, [_SyntaxStackCnt]
    inc     word [_SyntaxStackCnt]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, 0
    mov     [bx], ax
; RPN'ized expression: "SyntaxStack SyntaxStackCnt + *u 0 + *u 19 = "
; Expanded expression: "SyntaxStack SyntaxStackCnt *(2) 4 * + 0 + 19 =(2) "
; Fused expression:    "* *SyntaxStackCnt 4 + SyntaxStack ax + ax 0 =(34) *ax 19 "
    mov     ax, [_SyntaxStackCnt]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 0
    mov     bx, ax
    mov     ax, 19
    mov     [bx], ax
; RPN'ized expression: "SyntaxStack SyntaxStackCnt ++p + *u 1 + *u 0 = "
; Expanded expression: "SyntaxStack SyntaxStackCnt ++p(2) 4 * + 2 + 0 =(2) "
; Fused expression:    "++p(2) *SyntaxStackCnt * ax 4 + SyntaxStack ax + ax 2 =(34) *ax 0 "
    mov     ax, [_SyntaxStackCnt]
    inc     word [_SyntaxStackCnt]
    imul    ax, ax, 4
    mov     cx, ax
    mov     ax, _SyntaxStack
    add     ax, cx
    add     ax, 2
    mov     bx, ax
    mov     ax, 0
    mov     [bx], ax
; if
; RPN'ized expression: "OutputFormat 1 == "
; Expanded expression: "OutputFormat *(2) 1 == "
; Fused expression:    "== *OutputFormat 1 IF! "
    mov     ax, [_OutputFormat]
    cmp     ax, 1
    jne     L4403
; {
; RPN'ized expression: "FileHeader L4405 = "
; Expanded expression: "FileHeader L4405 =(2) "
; SEGMENT _TEXT
SEGMENT _DATA
L4405:
    db  "SEGMENT _TEXT PUBLIC CLASS=CODE USE16",10,"SEGMENT _DATA PUBLIC CLASS=DATA",10,10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "=(34) *FileHeader L4405 "
    mov     ax, L4405
    mov     [_FileHeader], ax
; RPN'ized expression: "CodeHeader L4407 = "
; Expanded expression: "CodeHeader L4407 =(2) "
; SEGMENT _TEXT
SEGMENT _DATA
L4407:
    db  "SEGMENT _TEXT",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "=(34) *CodeHeader L4407 "
    mov     ax, L4407
    mov     [_CodeHeader], ax
; RPN'ized expression: "CodeFooter L4409 = "
; Expanded expression: "CodeFooter L4409 =(2) "
; SEGMENT _TEXT
SEGMENT _DATA
L4409:
    db  "; SEGMENT _TEXT",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "=(34) *CodeFooter L4409 "
    mov     ax, L4409
    mov     [_CodeFooter], ax
; RPN'ized expression: "DataHeader L4411 = "
; Expanded expression: "DataHeader L4411 =(2) "
; SEGMENT _TEXT
SEGMENT _DATA
L4411:
    db  "SEGMENT _DATA",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "=(34) *DataHeader L4411 "
    mov     ax, L4411
    mov     [_DataHeader], ax
; RPN'ized expression: "DataFooter L4413 = "
; Expanded expression: "DataFooter L4413 =(2) "
; SEGMENT _TEXT
SEGMENT _DATA
L4413:
    db  "; SEGMENT _DATA",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "=(34) *DataFooter L4413 "
    mov     ax, L4413
    mov     [_DataFooter], ax
; }
    jmp     L4404
L4403:
; else
; {
; RPN'ized expression: "FileHeader L4415 = "
; Expanded expression: "FileHeader L4415 =(2) "
; SEGMENT _TEXT
SEGMENT _DATA
L4415:
    db  "BITS 16",10,0
; SEGMENT _DATA
SEGMENT _TEXT
; Fused expression:    "=(34) *FileHeader L4415 "
    mov     ax, L4415
    mov     [_FileHeader], ax
; }
L4404:
; RPN'ized expression: "( ShiftChar ) "
; Expanded expression: " ShiftChar ()0 "
; Fused expression:    "( ShiftChar )0 "
    call    _ShiftChar
; RPN'ized expression: "( FileHeader printf ) "
; Expanded expression: " FileHeader *(2)  printf ()2 "
; Fused expression:    "( *(2) FileHeader , printf )2 "
    push    word [_FileHeader]
    call    _printf
    sub     sp, -2
; RPN'ized expression: "( 0 , 0 ParseBlock ) "
; Expanded expression: " 0  0  ParseBlock ()4 "
; Fused expression:    "( 0 , 0 , ParseBlock )4 "
    push    0
    push    0
    call    _ParseBlock
    sub     sp, -4
; RPN'ized expression: "( DumpSynDecls ) "
; Expanded expression: " DumpSynDecls ()0 "
; Fused expression:    "( DumpSynDecls )0 "
    call    _DumpSynDecls
; RPN'ized expression: "( DumpMacroTable ) "
; Expanded expression: " DumpMacroTable ()0 "
; Fused expression:    "( DumpMacroTable )0 "
    call    _DumpMacroTable
; RPN'ized expression: "( DumpIdentTable ) "
; Expanded expression: " DumpIdentTable ()0 "
; Fused expression:    "( DumpIdentTable )0 "
    call    _DumpIdentTable
; return
; RPN'ized expression: "0 "
; Expanded expression: "0 "
; Expression value: 0
; Fused expression:    "0 "
    mov     ax, 0
    jmp     L4396
L4396:
    leave
    ret
; SEGMENT _TEXT

; Syntax/declaration table/stack:
; Bytes used: 11680/16384


; Macro table:
; Macro EXTERN = `extern`
; Macro PROTO = ``
; Macro NULL = `0`
; Macro size_t = `int`
; Macro CHAR_BIT = `(8)`
; Macro INT_MAX = `(32767)`
; Macro INT_MIN = `(-32767-1)`
; Macro FILE = `int`
; Macro EOF = `(-1)`
; Macro MAX_IDENT_LEN = `31`
; Macro MAX_STRING_LEN = `127`
; Macro MAX_CHAR_QUEUE_LEN = `256`
; Macro MAX_MACRO_TABLE_LEN = `4096`
; Macro MAX_STRING_TABLE_LEN = `512`
; Macro MAX_IDENT_TABLE_LEN = `4096`
; Macro tokEof = `0`
; Macro tokNum = `1`
; Macro tokLitChar = `2`
; Macro tokLitStr = `3`
; Macro tokLShift = `4`
; Macro tokRShift = `5`
; Macro tokLogAnd = `6`
; Macro tokLogOr = `7`
; Macro tokEQ = `8`
; Macro tokNEQ = `9`
; Macro tokLEQ = `10`
; Macro tokGEQ = `11`
; Macro tokInc = `12`
; Macro tokDec = `13`
; Macro tokArrow = `14`
; Macro tokEllipsis = `15`
; Macro tokIdent = `16`
; Macro tokVoid = `17`
; Macro tokChar = `18`
; Macro tokInt = `19`
; Macro tokReturn = `20`
; Macro tokGoto = `21`
; Macro tokIf = `22`
; Macro tokElse = `23`
; Macro tokWhile = `24`
; Macro tokCont = `25`
; Macro tokBreak = `26`
; Macro tokSizeof = `27`
; Macro tokAssignMul = `'A'`
; Macro tokAssignDiv = `'B'`
; Macro tokAssignMod = `'C'`
; Macro tokAssignAdd = `'D'`
; Macro tokAssignSub = `'E'`
; Macro tokAssignLSh = `'F'`
; Macro tokAssignRSh = `'G'`
; Macro tokAssignAnd = `'H'`
; Macro tokAssignXor = `'I'`
; Macro tokAssignOr = `'J'`
; Macro tokFloat = `'a'`
; Macro tokDouble = `'b'`
; Macro tokLong = `'c'`
; Macro tokShort = `'d'`
; Macro tokUnsigned = `'e'`
; Macro tokSigned = `'f'`
; Macro tokConst = `'g'`
; Macro tokVolatile = `'h'`
; Macro tokRestrict = `'i'`
; Macro tokStatic = `'j'`
; Macro tokInline = `'k'`
; Macro tokExtern = `'l'`
; Macro tokAuto = `'m'`
; Macro tokRegister = `'n'`
; Macro tokTypedef = `'o'`
; Macro tokEnum = `'p'`
; Macro tokStruct = `'q'`
; Macro tokUnion = `'r'`
; Macro tokDo = `'s'`
; Macro tokFor = `'t'`
; Macro tokSwitch = `'u'`
; Macro tokCase = `'v'`
; Macro tokDefault = `'w'`
; Macro tok_Bool = `'x'`
; Macro tok_Complex = `'y'`
; Macro tok_Imagin = `'z'`
; Macro tokIfNot = `'L'`
; Macro tokUnaryAnd = `'M'`
; Macro tokUnaryStar = `'N'`
; Macro tokUnaryPlus = `'O'`
; Macro tokUnaryMinus = `'P'`
; Macro tokPostInc = `'Q'`
; Macro tokPostDec = `'R'`
; Macro tokPostAdd = `'S'`
; Macro tokPostSub = `'T'`
; Macro tokULess = `'U'`
; Macro tokUGreater = `'V'`
; Macro tokULEQ = `'W'`
; Macro tokUGEQ = `'X'`
; Macro tokLocalOfs = `'Y'`
; Macro tokShortCirc = `'Z'`
; Macro FormatFlat = `0`
; Macro FormatSegmented = `1`
; Macro SYNTAX_STACK_MAX = `2048`
; Macro SymVoidSynPtr = `0`
; Macro SymIntSynPtr = `1`
; Macro STACK_SIZE = `100`
; Macro SymFxn = `1`
; Macro SymGlobalVar = `2`
; Macro SymGlobalArr = `3`
; Macro SymLocalVar = `4`
; Macro SymLocalArr = `5`
; Macro OPERATOR_STACK_SIZE = `100`
; Macro tokOpNum = `0x100`
; Macro tokOpIdent = `0x101`
; Macro tokOpLocalOfs = `0x102`
; Macro tokOpAcc = `0x103`
; Macro tokOpIndIdent = `0x104`
; Macro tokOpIndLocalOfs = `0x105`
; Macro tokOpIndAcc = `0x106`
; Macro tokOpStack = `0x107`
; Macro tokOpIndStack = `0x108`
; Macro tokPushAcc = `0x200`
; Bytes used: 1790/4096


; Identifier table:
; Ident _setargv__
; Ident exit
; Ident status
; Ident malloc
; Ident s
; Ident free
; Ident <something>
; Ident atoi
; Ident strlen
; Ident strcpy
; Ident s1
; Ident s2
; Ident strchr
; Ident c
; Ident strcmp
; Ident memmove
; Ident memcpy
; Ident isspace
; Ident isdigit
; Ident isalpha
; Ident isalnum
; Ident putchar
; Ident fopen
; Ident fclose
; Ident fgetc
; Ident printf
; Ident fmt
; Ident GetToken
; Ident GetTokenName
; Ident token
; Ident GetTokenValueInt
; Ident GetTokenValueString
; Ident GetTokenValueStringLength
; Ident GetTokenIdentName
; Ident GetTokenFileName
; Ident GetTokenFileLineNo
; Ident GetTokenFileLinePos
; Ident DumpMacroTable
; Ident PurgeStringTable
; Ident AddString
; Ident label
; Ident str
; Ident len
; Ident FindString
; Ident AddIdent
; Ident name
; Ident FindIdent
; Ident DumpIdentTable
; Ident GenLabel
; Ident Label
; Ident GenExtern
; Ident GenNumLabel
; Ident GenZeroData
; Ident Size
; Ident GenIntData
; Ident Val
; Ident GenAddrData
; Ident GenJumpUncond
; Ident GenJumpIfZero
; Ident GenJumpIfNotZero
; Ident GenJumpIfNotEqual
; Ident val
; Ident GenFxnProlog
; Ident GenFxnEpilog
; Ident GenLocalAlloc
; Ident GenStrData
; Ident insertJump
; Ident GenExpr
; Ident PushSyntax
; Ident t
; Ident PushSyntax2
; Ident v
; Ident DumpSynDecls
; Ident push2
; Ident v2
; Ident ins2
; Ident pos
; Ident ins
; Ident del
; Ident cnt
; Ident TokenStartsDeclaration
; Ident params
; Ident ParseDecl
; Ident tok
; Ident ShiftChar
; Ident error
; Ident format
; Ident FindSymbol
; Ident SymType
; Ident SynPtr
; Ident GetDeclSize
; Ident SyntaxPtr
; Ident ParseExpr
; Ident GotUnary
; Ident ExprTypeSynPtr
; Ident ConstExpr
; Ident ConstVal
; Ident GetFxnInfo
; Ident MinParams
; Ident MaxParams
; Ident ReturnExprTypeSynPtr
; Ident TokenValueInt
; Ident TokenIdentName
; Ident TokenIdentNameLen
; Ident TokenValueString
; Ident TokenStringLen
; Ident LineNo
; Ident LinePos
; Ident CurFileName
; Ident CurFile
; Ident CharQueue
; Ident CharQueueLen
; Ident MacroTable
; Ident MacroTableLen
; Ident StringTable
; Ident StringTableLen
; Ident IdentTable
; Ident IdentTableLen
; Ident ExprLevel
; Ident stack
; Ident sp
; Ident opstack
; Ident opsp
; Ident OutputFormat
; Ident FileHeader
; Ident CodeHeader
; Ident CodeFooter
; Ident DataHeader
; Ident DataFooter
; Ident SizeOfChar
; Ident CharIsSigned
; Ident SizeOfWord
; Ident LabelCnt
; Ident CurFxnSyntaxPtr
; Ident CurFxnParamCnt
; Ident CurFxnParamOfs
; Ident CurFxnLocalOfs
; Ident CurFxnReturnExprTypeSynPtr
; Ident CurFxnEpilogLabel
; Ident ParseLevel
; Ident SyntaxStack
; Ident SyntaxStackCnt
; Ident FindMacro
; Ident AddMacroIdent
; Ident AddMacroExpansionChar
; Ident e
; Ident GetTokenByWord
; Ident word
; Ident GetNextChar
; Ident ShiftCharN
; Ident n
; Ident SkipSpace
; Ident SkipNewLines
; Ident GetIdent
; Ident GenPrintLabel
; Ident GenExtendAlAx
; Ident GenReadIdent
; Ident OpSz
; Ident GenReadLocal
; Ident Ofs
; Ident GenReadIndirect
; Ident GenIncDecIdent
; Ident GenIncDecLocal
; Ident GenIncDecIndirect
; Ident GenPostIncDecIdent
; Ident GenPostIncDecLocal
; Ident GenPostIncDecIndirect
; Ident GenPostAddSubIdent
; Ident GenPostAddSubLocal
; Ident GenPostAddSubIndirect
; Ident GetOperandInfo
; Ident idx
; Ident lvalSize
; Ident size
; Ident delDeref
; Ident GenFuse
; Ident GenGetBinaryOperatorInstr
; Ident GenExpr1
; Ident push
; Ident stacktop
; Ident pop2
; Ident pop
; Ident pushop2
; Ident pushop
; Ident opstacktop
; Ident popop2
; Ident popop
; Ident isop
; Ident isunary
; Ident preced
; Ident precedGEQ
; Ident lfttok
; Ident rhttok
; Ident expr
; Ident gotUnary
; Ident exprUnary
; Ident decayArray
; Ident arithmetic
; Ident nonVoidTypeCheck
; Ident numericTypeCheck
; Ident promoteType
; Ident simplifyConstExpr
; Ident isConst
; Ident top
; Ident bottom
; Ident exprval
; Ident InsertSyntax2
; Ident InsertSyntax
; Ident DeleteSyntax
; Ident ShowDecl
; Ident IsParam
; Ident ParseArrayDimension
; Ident ParseFxnParams
; Ident ParseBlock
; Ident BrkCntSwchTarget
; Ident switchBody
; Ident AddFxnParamSymbols
; Ident ParseDerived
; Ident ParseStatement
; Ident main
; Ident argc
; Ident argv
; Bytes used: 2571/4096

