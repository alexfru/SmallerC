/*
Copyright (c) 2012-2013, Alexey Frunze
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met: 

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer. 
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies, 
either expressed or implied, of the FreeBSD Project.
*/

/*****************************************************************************/
/*                                                                           */
/*                                Smaller C                                  */
/*                                                                           */
/*       A simple and small single-pass C compiler ("small C" class).        */
/*                                                                           */
/*            Produces 16/32-bit 80386 assembly output for NASM.             */
/*             Produces 32-bit MIPS assembly output for gcc/as.              */
/*                                                                           */
/*                              Main/x86 file                                */
/*                                                                           */
/*****************************************************************************/

//#ifdef __TURBOC__
// You need to declare __setargv__ as an extern symbol when bootstrapping with
// Turbo C++ in order to access main()'s argc and argv params.
extern char _setargv__;
//#endif

#define EXTERN extern
//#define EXTERN

//#define PROTO extern
#define PROTO


#ifndef __SMALLER_C__

#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#else // #ifndef __SMALLER_C__

#define NULL 0
#define size_t unsigned int

#define CHAR_BIT (8)

#ifdef __SMALLER_C_SCHAR__
#define CHAR_MIN (-128)
#define CHAR_MAX (127)
#endif
#ifdef __SMALLER_C_UCHAR__
#define CHAR_MIN (0)
#define CHAR_MAX (255)
#endif

#ifdef __SMALLER_C_16__
#define INT_MAX (32767)
#define INT_MIN (-32767-1)
#define UINT_MAX (65535u)
#define UINT_MIN (0u)
#endif
#ifdef __SMALLER_C_32__
#define INT_MAX (2147483647)
#define INT_MIN (-2147483647-1)
#define UINT_MAX (4294967295u)
#define UINT_MIN (0u)
#endif

EXTERN void exit(int);
EXTERN int atoi(char*);

EXTERN size_t strlen(char*);
EXTERN char* strcpy(char*, char*);
EXTERN char* strchr(char*, int);
EXTERN int strcmp(char*, char*);
EXTERN int strncmp(char*, char*, size_t);
EXTERN void* memmove(void*, void*, size_t);
EXTERN void* memcpy(void*, void*, size_t);
EXTERN void* memset(void*, int, size_t);

EXTERN int isspace(int);
EXTERN int isdigit(int);
EXTERN int isalpha(int);
EXTERN int isalnum(int);

#define FILE void
#define EOF (-1)
EXTERN int putchar(int);
EXTERN FILE* fopen(char*, char*);
EXTERN int fclose(FILE*);
EXTERN int fgetc(FILE*);
EXTERN int puts(char*);
EXTERN int printf(char*, ...);
EXTERN int sprintf(char*, char*, ...);
//EXTERN int vprintf(char*, va_list);
EXTERN int vprintf(char*, void*);
//EXTERN int vsprintf(char*, char*, va_list);
EXTERN int vsprintf(char*, char*, void*);

#endif // #ifndef __SMALLER_C__


////////////////////////////////////////////////////////////////////////////////

// all public macros

#define MAX_IDENT_LEN        31
#define MAX_STRING_LEN       127
#define MAX_CHAR_QUEUE_LEN   256
#define MAX_MACRO_TABLE_LEN  4096
#define MAX_STRING_TABLE_LEN 512
#define MAX_IDENT_TABLE_LEN  4096
#define MAX_INCLUDES         8
#define MAX_FILE_NAME_LEN    95
#define PREP_STACK_SIZE      8
#define MAX_SEARCH_PATH      256

/* +-~* /% &|^! << >> && || < <= > >= == !=  () *[] ++ -- = += -= ~= *= /= %= &= |= ^= <<= >>= {} ,;: -> ... */

#define tokEof        0
#define tokNumInt     1
#define tokNumUint    2
#define tokLitStr     3

#define tokLShift     4
#define tokRShift     5
#define tokLogAnd     6
#define tokLogOr      7
#define tokEQ         8
#define tokNEQ        9
#define tokLEQ        10
#define tokGEQ        11
#define tokInc        12
#define tokDec        13
#define tokArrow      14
#define tokEllipsis   15

#define tokIdent      16
#define tokVoid       17
#define tokChar       18
#define tokInt        19
#define tokReturn     20
#define tokGoto       21
#define tokIf         22
#define tokElse       23
#define tokWhile      24
#define tokCont       25
#define tokBreak      26
#define tokSizeof     27

#define tokAssignMul  'A'
#define tokAssignDiv  'B'
#define tokAssignMod  'C'
#define tokAssignAdd  'D'
#define tokAssignSub  'E'
#define tokAssignLSh  'F'
#define tokAssignRSh  'G'
#define tokAssignAnd  'H'
#define tokAssignXor  'I'
#define tokAssignOr   'J'

#define tokFloat      'a'
#define tokDouble     'b'
#define tokLong       'c'
#define tokShort      'd'
#define tokUnsigned   'e'
#define tokSigned     'f'
#define tokConst      'g'
#define tokVolatile   'h'
#define tokRestrict   'i'
#define tokStatic     'j'
#define tokInline     'k'
#define tokExtern     'l'
#define tokAuto       'm'
#define tokRegister   'n'
#define tokTypedef    'o'
#define tokEnum       'p'
#define tokStruct     'q'
#define tokUnion      'r'
#define tokDo         's'
#define tokFor        't'
#define tokSwitch     'u'
#define tokCase       'v'
#define tokDefault    'w'
#define tok_Bool      'x'
#define tok_Complex   'y'
#define tok_Imagin    'z'

#define tok_Asm       '`'

/* Pseudo-tokens (converted from others or generated) */
#define tokURShift    28
#define tokUDiv       29
#define tokUMod       30
#define tokAssignURSh 31
#define tokAssignUDiv '@'
#define tokAssignUMod 'K'
#define tokComma      '0'

#define tokIfNot      'L'

#define tokUnaryAnd   'M'
#define tokUnaryStar  'N'
#define tokUnaryPlus  'O'
#define tokUnaryMinus 'P'

#define tokPostInc    'Q'
#define tokPostDec    'R'
#define tokPostAdd    'S'
#define tokPostSub    'T'

#define tokULess      'U'
#define tokUGreater   'V'
#define tokULEQ       'W'
#define tokUGEQ       'X'

#define tokLocalOfs   'Y'
#define tokShortCirc  'Z'

#define FormatFlat      0
#define FormatSegmented 1

#define SYNTAX_STACK_MAX 2048
#define SymVoidSynPtr 0
#define SymIntSynPtr 1
#define SymUintSynPtr 2

#define STACK_SIZE 128

#define SymFxn       1
#define SymGlobalVar 2
#define SymGlobalArr 3
#define SymLocalVar  4
#define SymLocalArr  5

// all public prototypes
PROTO int uint2int(unsigned);
PROTO unsigned truncUint(unsigned);
PROTO int truncInt(int);

PROTO int GetToken(void);
PROTO char* GetTokenName(int token);

PROTO int GetTokenValueInt(void);

PROTO char* GetTokenValueString(void);
PROTO int GetTokenValueStringLength(void);

PROTO char* GetTokenIdentName(void);

PROTO void DumpMacroTable(void);

PROTO void PurgeStringTable(void);
PROTO void AddString(int label, char* str, int len);
PROTO char* FindString(int label);

PROTO int AddIdent(char* name);
PROTO int FindIdent(char* name);
PROTO void DumpIdentTable(void);

PROTO void GenInit(void);
PROTO int GenInitParams(int argc, char** argv, int* idx);
PROTO void GenInitFinalize(void);
PROTO void GenStartCommentLine(void);
PROTO void GenWordAlignment(void);
PROTO void GenLabel(char* Label);
PROTO void GenExtern(char* Label);
PROTO void GenNumLabel(int Label);
PROTO void GenZeroData(unsigned Size);
PROTO void GenIntData(int Size, int Val);
PROTO void GenStartAsciiString(void);
PROTO void GenAddrData(int Size, char* Label);

PROTO void GenJumpUncond(int Label);
PROTO void GenJumpIfZero(int Label);
PROTO void GenJumpIfNotZero(int Label);
PROTO void GenJumpIfNotEqual(int val, int Label);

PROTO void GenFxnProlog(void);
PROTO void GenPrintCallFxn(char* name);
PROTO void GenFxnEpilog(void);

PROTO void GenLocalAlloc(int Size);

PROTO void GenStrData(int insertJump);
PROTO void GenExpr(void);

PROTO void PushSyntax(int t);
PROTO void PushSyntax2(int t, int v);

PROTO void DumpSynDecls(void);

PROTO void push2(int v, int v2);
PROTO void ins2(int pos, int v, int v2);
PROTO void ins(int pos, int v);
PROTO void del(int pos, int cnt);

PROTO int TokenStartsDeclaration(int t, int params);
PROTO int ParseDecl(int tok);

PROTO void ShiftChar(void);
PROTO void error(char* format, ...);

PROTO int FindSymbol(char* s);
PROTO int SymType(int SynPtr);
PROTO int GetDeclSize(int SyntaxPtr);

PROTO int ParseExpr(int tok, int* GotUnary, int* ExprTypeSynPtr, int* ConstExpr, int* ConstVal, int commaSeparator);
PROTO int GetFxnInfo(int ExprTypeSynPtr, int* MinParams, int* MaxParams, int* ReturnExprTypeSynPtr);

// all data

// avoids signed-to-unsigned comparison warnings with unsigned sizeof(int)
int intSize = sizeof(int);

// indicates whether or not constant subexpressions can be folded
int canSimplify = 0;

// prep.c data

int TokenValueInt = 0;
char TokenIdentName[MAX_IDENT_LEN + 1];
int TokenIdentNameLen = 0;
char TokenValueString[MAX_STRING_LEN + 1];
int TokenStringLen = 0;
int LineNo = 1;
int LinePos = 1;
char CharQueue[MAX_CHAR_QUEUE_LEN];
int CharQueueLen = 0;

/*
  Macro table entry format:
    idlen char:     identifier length (<= 127)
    id char[idlen]: identifier (ASCIIZ)
    exlen char:     length of what the identifier expands into (<= 127)
    ex char[exlen]: what the identifier expands into (ASCII)
*/
char MacroTable[MAX_MACRO_TABLE_LEN];
int MacroTableLen = 0;

/*
  String table entry format:
    int label:      temporary identifier's (char*) label number
    len char:       string length (<= 127)
    str char[len]:  string (ASCII)
*/
char StringTable[MAX_STRING_TABLE_LEN];
int StringTableLen = 0;

/*
  Identifier table entry format:
    id char[idlen]: string (ASCIIZ)
    idlen char:     string length (<= 127)
*/
char IdentTable[MAX_IDENT_TABLE_LEN];
int IdentTableLen = 0;

// Data structures to support #include
int FileCnt = 0;
char FileNames[MAX_INCLUDES][MAX_FILE_NAME_LEN + 1];
FILE* Files[MAX_INCLUDES];
char CharQueues[MAX_INCLUDES][3];
int LineNos[MAX_INCLUDES];
int LinePoss[MAX_INCLUDES];
char SearchPaths[MAX_SEARCH_PATH];
int SearchPathsLen = 0;

// Data structures to support #ifdef/#ifndef,#else,#endif
int PrepDontSkipTokens = 1;
int PrepStack[PREP_STACK_SIZE][2];
int PrepSp = 0;

// expr.c data

int ExprLevel = 0;

// TBD!!! merge expression and operator stacks into one
int stack[STACK_SIZE][2];
int sp = 0;

#define OPERATOR_STACK_SIZE STACK_SIZE
int opstack[OPERATOR_STACK_SIZE][2];
int opsp = 0;

// smc.c data

//int OutputFormat = FormatFlat;
int OutputFormat = FormatSegmented;

// Name of the function to call in main()'s prolog to construct C++ objects/init data.
// gcc calls __main().
char* MainPrologCtorFxn = NULL;

// Names of C functions and variables are usually prefixed with an underscore.
// One notable exception is the ELF format used by gcc in Linux.
// Global C identifiers in the ELF format should not be predixed with an underscore.
int UseLeadingUnderscores = 1;

char* FileHeader = "";
char* CodeHeader = "";
char* CodeFooter = "";
char* DataHeader = "";
char* DataFooter = "";

int CharIsSigned = 1;
int SizeOfWord = 2; // in chars (char can be a multiple of octets); ints and pointers are of word size

// TBD!!! implement a function to allocate N labels with overflow checks
int LabelCnt = 1; // label counter for jumps

// call stack (from higher to lower addresses):
//   param n
//   ...
//   param 1
//   return address
//   saved xbp register
//   local var 1
//   ...
//   local var n
int CurFxnSyntaxPtr = 0;
int CurFxnParamCnt = 0;
int CurFxnParamCntMin = 0;
int CurFxnParamCntMax = 0;
int CurFxnParamOfs = 0; // positive
int CurFxnLocalOfs = 0; // negative
int CurFxnMinLocalOfs = 0; // negative

int CurFxnReturnExprTypeSynPtr = 0;
int CurFxnEpilogLabel = 0;

int ParseLevel = 0; // Parse level/scope (file:0, fxn:1+)

int SyntaxStack[SYNTAX_STACK_MAX][2];
int SyntaxStackCnt = 0;

// all code

int uint2int(unsigned n)
{
  int r;
  // Convert n to (int)n in such a way that (unsigned)(int)n == n,
  // IOW, avoid signed overflows in (int)n.
  // We're assuming ints are 2's complement.

  // "n < INT_MAX + 1u" is equivalent to "n <= INT_MAX" without the
  // possible warning about comparing signed and unsigned types
  if (n < INT_MAX + 1u)
  {
    r = n;
  }
  else
  {
    n = n - INT_MAX - 1; // Now, 0 <= n <= INT_MAX, n is representable in int
    r = n;
    r = r - INT_MAX - 1; // Now, INT_MIN <= r <= -1
  }

  return r;
}

unsigned truncUint(unsigned n)
{
  // Truncate n to SizeOfWord * 8 bits
  if (SizeOfWord == 2)
    n &= ~(~0u << 8 << 8);
  else if (SizeOfWord == 4)
    n &= ~(~0u << 8 << 12 << 12);
  return n;
}

int truncInt(int n)
{
  // Truncate n to SizeOfWord * 8 bits and then sign-extend it
  unsigned un = n;
  if (SizeOfWord == 2)
  {
    un &= ~(~0u << 8 << 8);
    un |= (((un >> 8 >> 7) & 1) * ~0u) << 8 << 8;
  }
  else if (SizeOfWord == 4)
  {
    un &= ~(~0u << 8 << 12 << 12);
    un |= (((un >> 8 >> 12 >> 11) & 1) * ~0u) << 8 << 12 << 12;
  }
  return uint2int(un);
}

// prep.c code

int FindMacro(char* name)
{
  int i;

  for (i = 0; i < MacroTableLen; )
  {
    if (!strcmp(MacroTable + i + 1, name))
      return i + 1 + MacroTable[i];

    i = i + 1 + MacroTable[i]; // skip id
    i = i + 1 + MacroTable[i]; // skip ex
  }

  return -1;
}

int UndefineMacro(char* name)
{
  int i;

  for (i = 0; i < MacroTableLen; )
  {
    if (!strcmp(MacroTable + i + 1, name))
    {
      int len = 1 + MacroTable[i]; // id part len
      len = len + 1 + MacroTable[i + len]; // + ex part len

      memmove(MacroTable + i,
              MacroTable + i + len,
              MacroTableLen - i - len);
      MacroTableLen -= len;

      return 1;
    }

    i = i + 1 + MacroTable[i]; // skip id
    i = i + 1 + MacroTable[i]; // skip ex
  }

  return 0;
}

void AddMacroIdent(char* name)
{
  int l = strlen(name);

  if (l >= 127)
    error("Error: Macro identifier too long '%s'\n", name);

  if (MAX_MACRO_TABLE_LEN - MacroTableLen < l + 3)
    error("Error: Macro table full\n");

  MacroTable[MacroTableLen++] = l + 1; // idlen
  strcpy(MacroTable + MacroTableLen, name);
  MacroTableLen += l + 1;

  MacroTable[MacroTableLen] = 0; // exlen
}

void AddMacroExpansionChar(char e)
{
  if (e == '\0')
  {
    // finalize macro definition entry
    // remove trailing space first
    while (MacroTable[MacroTableLen] &&
           strchr(" \t", MacroTable[MacroTableLen + MacroTable[MacroTableLen]]))
      MacroTable[MacroTableLen]--;
    MacroTableLen += 1 + MacroTable[MacroTableLen];
    return;
  }

  if (MacroTableLen + 1 + MacroTable[MacroTableLen] >= MAX_MACRO_TABLE_LEN)
    error("Error: Macro table full\n");

  if (MacroTable[MacroTableLen] >= 127)
    error("Error: Macro definition too long\n");

  MacroTable[MacroTableLen + 1 + MacroTable[MacroTableLen]] = e;
  MacroTable[MacroTableLen]++;
}

void DefineMacro(char* name, char* expansion)
{
  AddMacroIdent(name);
  while (*expansion != '\0')
    AddMacroExpansionChar(*expansion++);
  AddMacroExpansionChar('\0');
}

void DumpMacroTable(void)
{
#ifndef NO_ANNOTATIONS
  int i, j;

  puts("");
  GenStartCommentLine(); printf("Macro table:\n");
  for (i = 0; i < MacroTableLen; )
  {
    GenStartCommentLine(); printf("Macro %s = ", MacroTable + i + 1);
    i = i + 1 + MacroTable[i]; // skip id
    printf("`");
    j = MacroTable[i++];
    while (j--)
      printf("%c", MacroTable[i++]);
    printf("`\n");
  }
  GenStartCommentLine(); printf("Bytes used: %d/%d\n\n", MacroTableLen, MAX_MACRO_TABLE_LEN);
#endif
}

void PurgeStringTable(void)
{
  StringTableLen = 0;
}

void AddString(int label, char* str, int len)
{
  if (len > 127)
    error("Error: String too long\n");

  if (MAX_STRING_TABLE_LEN - StringTableLen < /*sizeof(label)*/intSize + 1 + len)
    error("Error: String table full\n");

  memcpy(StringTable + StringTableLen, &label, sizeof(label));
  StringTableLen += sizeof(label);

  StringTable[StringTableLen++] = len;
  memcpy(StringTable + StringTableLen, str, len);
  StringTableLen += len;
}

char* FindString(int label)
{
  int i;

  for (i = 0; i < StringTableLen; )
  {
    int lab;

    memcpy(&lab, StringTable + i, sizeof(lab));
    if (lab == label)
      return StringTable + i + sizeof(lab);

    i += sizeof(lab);
    i += 1 + StringTable[i];
  }

  return NULL;
}

int FindIdent(char* name)
{
  int i;
  for (i = IdentTableLen; i > 0; )
  {
    i -= 1 + IdentTable[i - 1];
    if (!strcmp(IdentTable + i, name))
      return i;
  }
  return -1;
}

int AddIdent(char* name)
{
  int i, len;

  if ((i = FindIdent(name)) >= 0)
    return i;

  i = IdentTableLen;
  len = strlen(name);

  if (len >= 127)
    error("Error: Identifier table too long\n");

  if (MAX_IDENT_TABLE_LEN - IdentTableLen < len + 2)
    error("Error: Identifier table full\n");

  strcpy(IdentTable + IdentTableLen, name);
  IdentTableLen += len + 1;
  IdentTable[IdentTableLen++] = len + 1;

  return i;
}

void DumpIdentTable(void)
{
#ifndef NO_ANNOTATIONS
  int i;
  puts("");
  GenStartCommentLine(); printf("Identifier table:\n");
  for (i = 0; i < IdentTableLen; )
  {
    GenStartCommentLine(); printf("Ident %s\n", IdentTable + i);
    i += strlen(IdentTable + i) + 2;
  }
  GenStartCommentLine(); printf("Bytes used: %d/%d\n\n", IdentTableLen, MAX_IDENT_TABLE_LEN);
#endif
}

int GetTokenByWord(char* word)
{
  if (!strcmp(word, "break")) return tokBreak;
  if (!strcmp(word, "case")) return tokCase;
  if (!strcmp(word, "char")) return tokChar;
  if (!strcmp(word, "continue")) return tokCont;
  if (!strcmp(word, "default")) return tokDefault;
  if (!strcmp(word, "do")) return tokDo;
  if (!strcmp(word, "else")) return tokElse;
  if (!strcmp(word, "extern")) return tokExtern;
  if (!strcmp(word, "for")) return tokFor;
  if (!strcmp(word, "if")) return tokIf;
  if (!strcmp(word, "int")) return tokInt;
  if (!strcmp(word, "return")) return tokReturn;
  if (!strcmp(word, "signed")) return tokSigned;
  if (!strcmp(word, "sizeof")) return tokSizeof;
  if (!strcmp(word, "switch")) return tokSwitch;
  if (!strcmp(word, "unsigned")) return tokUnsigned;
  if (!strcmp(word, "void")) return tokVoid;
  if (!strcmp(word, "while")) return tokWhile;
  if (!strcmp(word, "asm")) return tok_Asm;

  if (!strcmp(word, "auto")) return tokAuto;
  if (!strcmp(word, "const")) return tokConst;
  if (!strcmp(word, "double")) return tokDouble;
  if (!strcmp(word, "enum")) return tokEnum;
  if (!strcmp(word, "float")) return tokFloat;
  if (!strcmp(word, "goto")) return tokGoto;
  if (!strcmp(word, "inline")) return tokInline;
  if (!strcmp(word, "long")) return tokLong;
  if (!strcmp(word, "register")) return tokRegister;
  if (!strcmp(word, "restrict")) return tokRestrict;
  if (!strcmp(word, "short")) return tokShort;
  if (!strcmp(word, "static")) return tokStatic;
  if (!strcmp(word, "struct")) return tokStruct;
  if (!strcmp(word, "typedef")) return tokTypedef;
  if (!strcmp(word, "union")) return tokUnion;
  if (!strcmp(word, "volatile")) return tokVolatile;
  if (!strcmp(word, "_Bool")) return tok_Bool;
  if (!strcmp(word, "_Complex")) return tok_Complex;
  if (!strcmp(word, "_Imaginary")) return tok_Imagin;

  return tokIdent;
}

char* GetTokenName(int token)
{
  switch (token)
  {
  case tokEof: return "<EOF>";
/* +-~* /% &|^! << >> && || < <= > >= == !=  () *[] ++ -- = += -= ~= *= /= %= &= |= ^= <<= >>= {} ,;: -> ... */
  // Single-character operators and punctuators:
  case '+': return "+";                  case '-': return "-";
  case '~': return "~";                  case '*': return "*";
  case '/': return "/";                  case '%': return "%";
  case '&': return "&";                  case '|': return "|";
  case '^': return "^";                  case '!': return "!";
  case '<': return "<";                  case '>': return ">";
  case '(': return "(";                  case ')': return ")";
  case '[': return "[";                  case ']': return "]";
  case '{': return "{";                  case '}': return "}";
  case '=': return "=";                  case ',': return ",";
  case ';': return ";";                  case ':': return ":";
  case '.': return ".";                  case '?': return "?";
  // Multi-character operators and punctuators:
  case tokLShift: return "<<";           case tokRShift: return ">>";
  case tokLogAnd: return "&&";           case tokLogOr: return "||";
  case tokEQ: return "==";               case tokNEQ: return "!=";
  case tokLEQ: return "<=";              case tokGEQ: return ">=";
  case tokInc: return "++";              case tokDec: return "--";
  case tokArrow: return "->";            case tokEllipsis: return "...";
  case tokAssignMul: return "*=";        case tokAssignDiv: return "/=";
  case tokAssignMod: return "%=";        case tokAssignAdd: return "+=";
  case tokAssignSub: return "-=";        case tokAssignLSh: return "<<=";
  case tokAssignRSh: return ">>=";       case tokAssignAnd: return "&=";
  case tokAssignXor: return "^=";        case tokAssignOr: return "|=";

  // Some of the above tokens get converted into these in the process:
  case tokUnaryAnd: return "&u";         case tokUnaryStar: return "*u";
  case tokUnaryPlus: return "+u";        case tokUnaryMinus: return "-u";
  case tokPostInc: return "++p";         case tokPostDec: return "--p";
  case tokPostAdd: return "+=p";         case tokPostSub: return "-=p";
  case tokULess: return "<u";            case tokUGreater: return ">u";
  case tokULEQ: return "<=u";            case tokUGEQ: return ">=u";
  case tokURShift: return ">>u";         case tokAssignURSh: return ">>=u";
  case tokUDiv: return "/u";             case tokAssignUDiv: return "/=u";
  case tokUMod: return "%u";             case tokAssignUMod: return "%=u";
  case tokComma: return ",b";

  // Reserved keywords:
  case tokVoid: return "void";           case tokChar: return "char";
  case tokInt: return "int";             case tokReturn: return "return";
  case tokGoto: return "goto";           case tokIf: return "if";
  case tokElse: return "else";           case tokWhile: return "while";
  case tokCont: return "continue";       case tokBreak: return "break";
  case tokSizeof: return "sizeof";       case tokFloat: return "float";
  case tokDouble: return "double";       case tokLong: return "long";
  case tokShort: return "short";         case tokUnsigned: return "unsigned";
  case tokSigned: return "signed";       case tokConst: return "const";
  case tokVolatile: return "volatile";   case tokRestrict: return "restrict";
  case tokStatic: return "static";       case tokInline: return "inline";
  case tokExtern: return "extern";       case tokAuto: return "auto";
  case tokRegister: return "register";   case tokTypedef: return "typedef";
  case tokEnum: return "enum";           case tokStruct: return "struct";
  case tokUnion: return "union";         case tokDo: return "do";
  case tokFor: return "for";             case tokSwitch: return "switch";
  case tokCase: return "case";           case tokDefault: return "default";
  case tok_Bool: return "_Bool";         case tok_Complex: return "_Complex";
  case tok_Imagin: return "_Imaginary";  case tok_Asm: return "asm";

  // Helper (pseudo-)tokens:
  case tokNumInt: return "<NumInt>";     case tokNumUint: return "<NumUint>";
  case tokLitStr: return "<LitStr>";     case tokIdent: return "<Ident>";
  case tokLocalOfs: return "<LocalOfs>"; case tokShortCirc: return "<ShortCirc>";
  }

  error("Internal Error: GetTokenName(): Invalid token %d\n", token);
  return "";
}

int GetTokenValueInt(void)
{
  return TokenValueInt;
}

char* GetTokenValueString(void)
{
  return TokenValueString;
}

int GetTokenValueStringLength(void)
{
  return TokenStringLen;
}

char* GetTokenIdentName(void)
{
  return TokenIdentName;
}

int GetNextChar(void)
{
  int ch = EOF;

  if (FileCnt && Files[FileCnt - 1])
  {
    if ((ch = fgetc(Files[FileCnt - 1])) == EOF)
    {
      fclose(Files[FileCnt - 1]);
      Files[FileCnt - 1] = NULL;

      // store the last line/pos, they may still be needed later
      LineNos[FileCnt - 1] = LineNo;
      LinePoss[FileCnt - 1] = LinePos;

      // don't drop the file record just yet
    }
  }

  return ch;
}

void ShiftChar(void)
{
  if (CharQueueLen)
    memmove(CharQueue, CharQueue + 1, --CharQueueLen);

  // make sure there always are at least 3 chars in the queue
  while (CharQueueLen < 3)
  {
    int ch = GetNextChar();
    if (ch == EOF)
      ch = '\0';
    CharQueue[CharQueueLen++] = ch;
  }
}

void ShiftCharN(int n)
{
  while (n-- > 0)
  {
    ShiftChar();
    LinePos++;
  }
}

void IncludeFile(int quot)
{
  int nlen = strlen(TokenValueString);

  if (CharQueueLen != 3)
    error("Error: #include parsing error\n");

  if (FileCnt >= MAX_INCLUDES)
    error("Error: Too many include files\n");

  // store the including file's position and buffered chars
  LineNos[FileCnt - 1] = LineNo;
  LinePoss[FileCnt - 1] = LinePos;
  memcpy(CharQueues[FileCnt - 1], CharQueue, CharQueueLen);

  // open the included file

  if (nlen > MAX_FILE_NAME_LEN)
    error("Error: File name too long\n");

  // DONE: differentiate between quot == '\"' and quot == '<'

  // first, try opening "file" in the current directory
  if (quot == '\"')
  {
    strcpy(FileNames[FileCnt], TokenValueString);
    Files[FileCnt] = fopen(FileNames[FileCnt], "rt");
  }

  // next, iterate the search paths trying to open "file" or <file>
  if (Files[FileCnt] == NULL)
  {
    int i;
    for (i = 0; i < SearchPathsLen; )
    {
      int plen = strlen(SearchPaths + i);
      if (plen + 1 + nlen < MAX_FILE_NAME_LEN)
      {
        strcpy(FileNames[FileCnt], SearchPaths + i);
        strcpy(FileNames[FileCnt] + plen + 1, TokenValueString);
        // first, try '/' as a separator (Linux/Unix)
        FileNames[FileCnt][plen] = '/';
        if ((Files[FileCnt] = fopen(FileNames[FileCnt], "rt")) == NULL)
        {
          // next, try '\\' as a separator (DOS/Windows)
          FileNames[FileCnt][plen] = '\\';
          Files[FileCnt] = fopen(FileNames[FileCnt], "rt");
        }
        if (Files[FileCnt])
          break;
      }
      i += plen + 1;
    }
  }

  if (Files[FileCnt] == NULL)
  {
    if (quot == '<' && !SearchPathsLen)
      error("Error: Cannot open file \"%s\", include search path unspecified\n", TokenValueString);

    error("Error: Cannot open file \"%s\"\n", TokenValueString);
  }

  // reset line/pos and empty the char queue
  CharQueueLen = 0;
  LineNo = LinePos = 1;
  FileCnt++;

  // fill the char queue with file data
  ShiftChar();
}

int EndOfFiles(void)
{
  // if there are no including files, we're done
  if (!--FileCnt)
    return 1;

  // restore the including file's position and buffered chars
  LineNo = LineNos[FileCnt - 1];
  LinePos = LinePoss[FileCnt - 1];
  CharQueueLen = 3;
  memcpy(CharQueue, CharQueues[FileCnt - 1], CharQueueLen);

  return 0;
}

void SkipSpace(int SkipNewLines)
{
  char* p = CharQueue;

  while (*p != '\0')
  {
    if (strchr(" \t\f\v", *p) != NULL)
    {
      ShiftCharN(1);
      continue;
    }

    if (strchr("\r\n", *p))
    {
      if (!SkipNewLines)
        return;

      if (*p == '\r' && p[1] == '\n')
        ShiftChar();

      ShiftChar();
      LineNo++;
      LinePos = 1;
      continue;
    }

    if (*p == '/')
    {
      if (p[1] == '/')
      {
        // // comment
        ShiftCharN(2);
        while (!strchr("\r\n", *p))
          ShiftCharN(1);
        continue;
      }
      else if (p[1] == '*')
      {
        // /**/ comment
        ShiftCharN(2);
        while (*p != '\0' && !(*p == '*' && p[1] == '/'))
        {
          if (strchr("\r\n", *p))
          {
            if (!SkipNewLines)
              error("Error: Invalid comment\n");

            if (*p == '\r' && p[1] == '\n')
              ShiftChar();

            ShiftChar();
            LineNo++;
            LinePos = 1;
          }
          else
          {
            ShiftCharN(1);
          }
        }
        if (*p == '\0')
          error("Error: Invalid comment\n");
        ShiftCharN(2);
        continue;
      }
    } // endof if (*p == '/')

    break;
  } // endof while (*p != '\0')
}

void GetIdent(void)
{
  char* p = CharQueue;

  if (*p != '_' && !isalpha(*p))
    error("Error: Identifier expected\n");

  if ((*p == 'L' || *p == 'l') &&
      (p[1] == '\'' || p[1] == '\"'))
    error("Error: Wide characters and strings not supported\n");

  TokenIdentNameLen = 0;
  TokenIdentName[TokenIdentNameLen++] = *p;
  TokenIdentName[TokenIdentNameLen] = '\0';
  ShiftCharN(1);

  while (*p == '_' || isalnum(*p))
  {
    if (TokenIdentNameLen == MAX_IDENT_LEN)
      error("Error: Identifier name too long '%s'\n", TokenIdentName);
    TokenIdentName[TokenIdentNameLen++] = *p;
    TokenIdentName[TokenIdentNameLen] = '\0';
    ShiftCharN(1);
  }
}

void GetString(char terminator, int SkipNewLines)
{
  char* p = CharQueue;
  char ch;

  TokenStringLen = 0;
  TokenValueString[TokenStringLen] = '\0';

  for (;;)
  {
    ShiftCharN(1);
    while (!(*p == terminator || strchr("\a\b\f\n\r\t\v", *p)))
    {
      ch = *p;
      if (ch == '\\')
      {
        ShiftCharN(1);
        ch = *p;
        if (strchr("\a\b\f\n\r\t\v", ch))
          break;
        switch (ch)
        {
        case 'a': ch = '\a'; ShiftCharN(1); break;
        case 'b': ch = '\b'; ShiftCharN(1); break;
        case 'f': ch = '\f'; ShiftCharN(1); break;
        case 'n': ch = '\n'; ShiftCharN(1); break;
        case 'r': ch = '\r'; ShiftCharN(1); break;
        case 't': ch = '\t'; ShiftCharN(1); break;
        case 'v': ch = '\v'; ShiftCharN(1); break;
        // DONE: \nnn, \xnn
        case 'x':
          {
            // hexadecimal character codes \xN+
            int cnt = 0;
            int c = 0;
            ShiftCharN(1);
            while (*p != '\0' && (isdigit(*p) || strchr("abcdefABCDEF", *p)))
            {
              c = (c * 16) & 0xFF;
              if (*p >= 'a') c += *p - 'a' + 10;
              else if (*p >= 'A') c += *p - 'A' + 10;
              else c += *p - '0';
              ShiftCharN(1);
              cnt++;
            }
            if (!cnt)
              error("Error: Unsupported or invalid character/string constant\n");
            c -= (c >= 0x80 && CHAR_MIN) * 0x100;
            ch = c;
          }
          break;
        default:
          if (*p >= '0' && *p <= '7')
          {
            // octal character codes \N+
            int cnt = 0;
            int c = 0;
            while (*p >= '0' && *p <= '7')
            {
              c = (c * 8) & 0xFF;
              c += *p - '0';
              ShiftCharN(1);
              cnt++;
            }
            if (!cnt)
              error("Error: Unsupported or invalid character/string constant\n");
            c -= (c >= 0x80 && CHAR_MIN) * 0x100;
            ch = c;
          }
          else
          {
            ShiftCharN(1);
          }
          break;
        } // endof switch (ch)
      } // endof if (ch == '\\')
      else
      {
        ShiftCharN(1);
      }

      if (terminator == '\'')
      {
        if (TokenStringLen != 0)
          error("Error: Character constant too long\n");
      }
      else if (TokenStringLen == MAX_STRING_LEN)
        error("Error: String constant too long\n");

      TokenValueString[TokenStringLen++] = ch;
      TokenValueString[TokenStringLen] = '\0';
    } // endof while (!(*p == '\0' || *p == terminator || strchr("\a\b\f\n\r\t\v", *p)))

    if (*p != terminator)
      error("Error: Unsupported or invalid character/string constant\n");

    ShiftCharN(1);

    if (terminator != '\"')
      break; // done with character constants

    // Concatenate this string literal with all following ones, if any
    SkipSpace(SkipNewLines);
    if (*p != '\"')
      break; // nothing to concatenate with
    // Continue consuming string characters
  } // endof for (;;)
}

void pushPrep(int NoSkip)
{
  if (PrepSp >= PREP_STACK_SIZE) error("Error: too many #if(n)def's\n");
  PrepStack[PrepSp][0] = PrepDontSkipTokens;
  PrepStack[PrepSp++][1] = NoSkip;
  PrepDontSkipTokens &= NoSkip;
}

int popPrep(void)
{
  if (PrepSp <= 0) error("Error: #else or #endif without #if(n)def\n");
  PrepDontSkipTokens = PrepStack[--PrepSp][0];
  return PrepStack[PrepSp][1];
}

int GetNumber(void)
{
  char* p = CharQueue;
  int ch = *p;
  unsigned n = 0;
  int type = 0;
  int uSuffix = 0;

  if (ch == '0')
  {
    // this is either an octal or a hex constant
    type = 'o';
    ShiftCharN(1);
    if ((ch = *p) == 'x' || ch == 'X')
    {
      // this is a hex constant
      int cnt = 0;
      ShiftCharN(1);
      while ((ch = *p) != '\0' && (isdigit(ch) || strchr("abcdefABCDEF", ch)))
      {
        if (ch >= 'a') ch -= 'a' - 10;
        else if (ch >= 'A') ch -= 'A' - 10;
        else ch -= '0';
        if (PrepDontSkipTokens && (n * 16 / 16 != n || n * 16 + ch < n * 16))
          error("Error: Constant too big\n");
        n = n * 16 + ch;
        ShiftCharN(1);
        cnt++;
      }
      if (!cnt)
        error("Error: Invalid hexadecimal constant\n");
      type = 'h';
    }
    // this is an octal constant
    else while ((ch = *p) >= '0' && ch <= '7')
    {
      ch -= '0';
      if (PrepDontSkipTokens && (n * 8 / 8 != n || n * 8 + ch < n * 8))
        error("Error: Constant too big\n");
      n = n * 8 + ch;
      ShiftCharN(1);
    }
  }
  // this is a decimal constant
  else
  {
    type = 'd';
    while ((ch = *p) >= '0' && ch <= '9')
    {
      ch -= '0';
      if (PrepDontSkipTokens && (n * 10 / 10 != n || n * 10 + ch < n * 10))
        error("Error: Constant too big\n");
      n = n * 10 + ch;
      ShiftCharN(1);
    }
  }

  if ((ch = *p) == 'u' || ch == 'U')
  {
    uSuffix = 1;
    ShiftCharN(1);
  }

  if (!PrepDontSkipTokens)
  {
    // Don't fail on big constants when skipping tokens under #if
    TokenValueInt = 0;
    return tokNumInt;
  }

  // Ensure the constant fits into 16(32) bits
  if ((SizeOfWord == 2 && n >> 8 >> 8) || // equiv. to SizeOfWord == 2 && n > 0xFFFF
      (SizeOfWord == 4 && n >> 8 >> 12 >> 12)) // equiv. to SizeOfWord == 4 && n > 0xFFFFFFFF
    error("Error: Constant too big for %d-bit type\n", SizeOfWord * 8);

  TokenValueInt = uint2int(n);

  // Unsuffixed (with 'u') integer constants (octal, decimal, hex)
  // fitting into 15(31) out of 16(32) bits are signed ints
  if (!uSuffix &&
      ((SizeOfWord == 2 && !(n >> 8 >> 7)) || // equiv. to SizeOfWord == 2 && n <= 0x7FFF
       (SizeOfWord == 4 && !(n >> 8 >> 12 >> 11)))) // equiv. to SizeOfWord == 4 && n <= 0x7FFFFFFF
    return tokNumInt;

  // Unlike octal and hex constants, decimal constants are always
  // a signed type. Error out when a decimal constant doesn't fit
  // into an int since currently there's no next bigger signed type
  // (e.g. long) to use instead of int.
  if (!uSuffix && type == 'd')
    error("Error: Constant too big for %d-bit signed type\n", SizeOfWord * 8);

  return tokNumUint;
}

int GetTokenInner(void)
{
  char* p = CharQueue;
  int ch = *p;

  // these single-character tokens/operators need no further processing
  if (strchr(",;:()[]{}~", ch) != NULL)
  {
    ShiftCharN(1);
    return ch;
  }

  // parse multi-character tokens/operators

  // DONE: other assignment operators
  switch (ch)
  {
  case '+':
    if (p[1] == '+') { ShiftCharN(2); return tokInc; }
    if (p[1] == '=') { ShiftCharN(2); return tokAssignAdd; }
    ShiftCharN(1); return ch;
  case '-':
    if (p[1] == '-') { ShiftCharN(2); return tokDec; }
    if (p[1] == '=') { ShiftCharN(2); return tokAssignSub; }
    if (p[1] == '>') { ShiftCharN(2); return tokArrow; }
    ShiftCharN(1); return ch;
  case '!':
    if (p[1] == '=') { ShiftCharN(2); return tokNEQ; }
    ShiftCharN(1); return ch;
  case '=':
    if (p[1] == '=') { ShiftCharN(2); return tokEQ; }
    ShiftCharN(1); return ch;
  case '<':
    if (p[1] == '=') { ShiftCharN(2); return tokLEQ; }
    if (p[1] == '<') { ShiftCharN(2); if (p[0] != '=') return tokLShift; ShiftCharN(1); return tokAssignLSh; }
    ShiftCharN(1); return ch;
  case '>':
    if (p[1] == '=') { ShiftCharN(2); return tokGEQ; }
    if (p[1] == '>') { ShiftCharN(2); if (p[0] != '=') return tokRShift; ShiftCharN(1); return tokAssignRSh; }
    ShiftCharN(1); return ch;
  case '&':
    if (p[1] == '&') { ShiftCharN(2); return tokLogAnd; }
    if (p[1] == '=') { ShiftCharN(2); return tokAssignAnd; }
    ShiftCharN(1); return ch;
  case '|':
    if (p[1] == '|') { ShiftCharN(2); return tokLogOr; }
    if (p[1] == '=') { ShiftCharN(2); return tokAssignOr; }
    ShiftCharN(1); return ch;
  case '^':
    if (p[1] == '=') { ShiftCharN(2); return tokAssignXor; }
    ShiftCharN(1); return ch;
  case '.':
    if (p[1] == '.' && p[2] == '.') { ShiftCharN(3); return tokEllipsis; }
    ShiftCharN(1); return ch;
  case '*':
    if (p[1] == '=') { ShiftCharN(2); return tokAssignMul; }
    ShiftCharN(1); return ch;
  case '%':
    if (p[1] == '=') { ShiftCharN(2); return tokAssignMod; }
    ShiftCharN(1); return ch;
  case '/':
    if (p[1] == '=') { ShiftCharN(2); return tokAssignDiv; }
    // if (p[1] == '/' || p[1] == '*') { SkipSpace(1); continue; } // already taken care of
    ShiftCharN(1); return ch;
  }

  // DONE: hex and octal constants
  if (isdigit(ch))
    return GetNumber();

  // parse character and string constants
  if (ch == '\'' || ch == '\"')
  {
    GetString(ch, 1);

    if (ch == '\'')
    {
      if (TokenStringLen != 1)
        error("Error: Character constant too short\n");

      TokenValueInt = TokenValueString[0] & 0xFF;
      TokenValueInt -= (CharIsSigned && TokenValueInt >= 0x80) * 0x100;
      return tokNumInt;
    }

    return tokLitStr;
  } // endof if (ch == '\'' || ch == '\"')

  return tokEof;
}

// TBD!!! implement file I/O for input source code and output code (use fxn ptrs/wrappers to make librarization possible)
// DONE: support string literals
int GetToken(void)
{
  char* p = CharQueue;
  int ch;
  int tok;

  for (;;)
  {
/* +-~* /% &|^! << >> && || < <= > >= == !=  () *[] ++ -- = += -= ~= *= /= %= &= |= ^= <<= >>= {} ,;: -> ... */

    // skip white space and comments
    SkipSpace(1);

    if ((ch = *p) == '\0')
    {
      // done with the current file, drop its record,
      // pick up the including files (if any) or terminate
      if (EndOfFiles())
        break;
      continue;
    }

    if ((tok = GetTokenInner()) != tokEof)
    {
      if (PrepDontSkipTokens)
        return tok;
      continue;
    }

    // parse identifiers and reserved keywords
    if (ch == '_' || isalpha(ch))
    {
      int midx;

      GetIdent();

      if (!PrepDontSkipTokens)
        continue;

      tok = GetTokenByWord(TokenIdentName);

      // TBD!!! think of expanding macros in the context of concatenating string literals,
      // maybe factor out this piece of code
      if ((midx = FindMacro(TokenIdentName)) >= 0)
      {
        // this is a macro identifier, need to expand it
        int len = MacroTable[midx];

        if (MAX_CHAR_QUEUE_LEN - CharQueueLen < len + 1)
          error("Error: Macro expansion is too long at '%s'\n", TokenIdentName);

        memmove(CharQueue + len + 1, CharQueue, CharQueueLen);

        memcpy(CharQueue, MacroTable + midx + 1, len);
        CharQueue[len] = ' '; // space to avoid concatenation

        CharQueueLen += len + 1;

        continue;
      }

      return tok;
    } // endof if (ch == '_' || isalpha(ch))

    // parse preprocessor directives
    if (ch == '#')
    {
      ShiftCharN(1);

      // Skip space and get preprocessor directive
      SkipSpace(0);
      GetIdent();

      if (!strcmp(TokenIdentName, "define"))
      {
        // Skip space and get macro name
        SkipSpace(0);
        GetIdent();

        if (!PrepDontSkipTokens)
        {
          SkipSpace(0);
          while (!strchr("\r\n", *p))
            ShiftCharN(1);
          continue;
        }

        if (FindMacro(TokenIdentName) >= 0)
          error("Error: Redefinition of macro '%s'\n", TokenIdentName);
        if (*p == '(')
          error("Error: Unsupported type of macro '%s'\n", TokenIdentName);

        AddMacroIdent(TokenIdentName);

        SkipSpace(0);

        // accumulate the macro expansion text
        while (!strchr("\r\n", *p))
        {
          AddMacroExpansionChar(*p);
          ShiftCharN(1);
          if (*p != '\0' && (strchr(" \t", *p) || (*p == '/' && (p[1] == '/' || p[1] == '*'))))
          {
            SkipSpace(0);
            AddMacroExpansionChar(' ');
          }
        }
        AddMacroExpansionChar('\0');

        continue;
      }
      else if (!strcmp(TokenIdentName, "undef"))
      {
        // Skip space and get macro name
        SkipSpace(0);
        GetIdent();

        if (PrepDontSkipTokens)
          UndefineMacro(TokenIdentName);

        SkipSpace(0);
        if (!strchr("\r\n", *p))
          error("Error: Invalid preprocessor directive\n");
        continue;
      }
      else if (!strcmp(TokenIdentName, "include"))
      {
        int quot;

        // Skip space and get file name
        SkipSpace(0);

        quot = *p;
        if (*p == '\"')
          GetString('\"', 0);
        else if (*p == '<')
          GetString('>', 0);
        else
          error("Error: Invalid file name\n");

        SkipSpace(0);
        if (!strchr("\r\n", *p))
          error("Error: Unsupported or invalid preprocessor directive\n");

        if (PrepDontSkipTokens)
          IncludeFile(quot);

        continue;
      }
      else if (!strcmp(TokenIdentName, "ifdef"))
      {
        int def;
        // Skip space and get macro name
        SkipSpace(0);
        GetIdent();
        def = FindMacro(TokenIdentName) >= 0;
        SkipSpace(0);
        if (!strchr("\r\n", *p))
          error("Error: Invalid preprocessor directive\n");
        pushPrep(def);
        continue;
      }
      else if (!strcmp(TokenIdentName, "ifndef"))
      {
        int def;
        // Skip space and get macro name
        SkipSpace(0);
        GetIdent();
        def = FindMacro(TokenIdentName) >= 0;
        SkipSpace(0);
        if (!strchr("\r\n", *p))
          error("Error: Invalid preprocessor directive\n");
        pushPrep(!def);
        continue;
      }
      else if (!strcmp(TokenIdentName, "else"))
      {
        int def;
        SkipSpace(0);
        if (!strchr("\r\n", *p))
          error("Error: Invalid preprocessor directive\n");
        def = popPrep();
        if (def >= 2)
          error("Error: #else without #if(n)def\n");
        pushPrep(2 + !def); // #else works in opposite way to its preceding #if(n)def
        continue;
      }
      else if (!strcmp(TokenIdentName, "endif"))
      {
        SkipSpace(0);
        if (!strchr("\r\n", *p))
          error("Error: Invalid preprocessor directive\n");
        popPrep();
        continue;
      }

      error("Error: Unsupported or invalid preprocessor directive\n");
    } // endof if (ch == '#')

    error("Error: Unsupported or invalid character '%c'\n", *p);
  } // endof for (;;)

  return tokEof;
}

#ifdef MIPS
#include "cgmips.c"
#else
// cgx86.c code

// TBD!!! compress/clean up

void GenInit(void)
{
  // initialization of target-specific code generator
  SizeOfWord = 2;
  OutputFormat = FormatSegmented;
  UseLeadingUnderscores = 1;
}

int GenInitParams(int argc, char** argv, int* idx)
{
#ifndef __SMALLER_C__
  (void)argc;
#endif
  // initialization of target-specific code generator with parameters

  if (!strcmp(argv[*idx], "-seg16"))
  {
    // this is the default option for x86
    OutputFormat = FormatSegmented; SizeOfWord = 2;
    return 1;
  }
  else if (!strcmp(argv[*idx], "-seg32"))
  {
    OutputFormat = FormatSegmented; SizeOfWord = 4;
    return 1;
  }
  else if (!strcmp(argv[*idx], "-flat16"))
  {
    OutputFormat = FormatFlat; SizeOfWord = 2;
    return 1;
  }
  else if (!strcmp(argv[*idx], "-flat32"))
  {
    OutputFormat = FormatFlat; SizeOfWord = 4;
    return 1;
  }

  return 0;
}

void GenInitFinalize(void)
{
  // finalization of initialization of target-specific code generator

  // Change the output assembly format/content according to the options
  if (OutputFormat == FormatSegmented)
  {
    if (SizeOfWord == 2)
    {
      FileHeader = "SEGMENT _TEXT PUBLIC CLASS=CODE USE16\n"
                   "SEGMENT _DATA PUBLIC CLASS=DATA\n";
      CodeHeader = "SEGMENT _TEXT";
      CodeFooter = "; SEGMENT _TEXT";
      DataHeader = "SEGMENT _DATA";
      DataFooter = "; SEGMENT _DATA";
    }
    else
    {
      CodeHeader = "section .text";
      DataHeader = "section .data";
    }
  }
  else
  {
    if (SizeOfWord == 2)
      FileHeader = "BITS 16";
    else
      FileHeader = "bits 32";
  }
}

void GenStartCommentLine(void)
{
  printf("; ");
}

void GenWordAlignment(void)
{
// TBD??? enable alignment on x86?
//  printf("\talign %d\n", SizeOfWord);
}

void GenLabel(char* Label)
{
  if (UseLeadingUnderscores)
  {
    if (OutputFormat != FormatFlat)
      printf("\tglobal\t_%s\n", Label);
    printf("_%s:\n", Label);
  }
  else
  {
    if (OutputFormat != FormatFlat)
      printf("\tglobal\t$%s\n", Label);
    printf("$%s:\n", Label);
  }
}

void GenExtern(char* Label)
{
  if (OutputFormat != FormatFlat)
  {
    if (UseLeadingUnderscores)
      printf("\textern\t_%s\n", Label);
    else
      printf("\textern\t$%s\n", Label);
  }
}

void GenPrintLabel(char* Label)
{
  if (UseLeadingUnderscores)
  {
    if (isdigit(*Label))
      printf("L%s", Label);
    else
      printf("_%s", Label);
  }
  else
  {
    if (isdigit(*Label))
      printf("..@L%s", Label);
    else
      printf("$%s", Label);
  }
}

void GenNumLabel(int Label)
{
  if (UseLeadingUnderscores)
    printf("L%d:\n", Label);
  else
    printf("..@L%d:\n", Label);
}

void GenPrintNumLabel(int label)
{
  if (UseLeadingUnderscores)
    printf("L%d", label);
  else
    printf("..@L%d", label);
}

void GenZeroData(unsigned Size)
{
  printf("\ttimes\t%u db 0\n", truncUint(Size));
}

void GenIntData(int Size, int Val)
{
  Val = truncInt(Val);
  if (Size == 1)
    printf("\tdb\t%d\n", Val);
  else if (Size == 2)
    printf("\tdw\t%d\n", Val);
  else if (Size == 4)
    printf("\tdd\t%d\n", Val);
}

void GenStartAsciiString(void)
{
  printf("\tdb\t");
}

void GenAddrData(int Size, char* Label)
{
  if (Size == 1)
    printf("\tdb\t");
  else if (Size == 2)
    printf("\tdw\t");
  else if (Size == 4)
    printf("\tdd\t");
  GenPrintLabel(Label); puts("");
}

#define X86InstrMov    0x00
#define X86InstrMovSx  0x01
#define X86InstrMovZx  0x02
#define X86InstrXchg   0x03
#define X86InstrLea    0x04
#define X86InstrPush   0x05
#define X86InstrPop    0x06
#define X86InstrInc    0x07
#define X86InstrDec    0x08
#define X86InstrAdd    0x09
#define X86InstrSub    0x0A
#define X86InstrAnd    0x0B
#define X86InstrXor    0x0C
#define X86InstrOr     0x0D
#define X86InstrCmp    0x0E
#define X86InstrTest   0x0F
#define X86InstrMul    0x10
#define X86InstrImul   0x11
#define X86InstrIdiv   0x12
#define X86InstrDiv    0x13
#define X86InstrShl    0x14
#define X86InstrSar    0x15
#define X86InstrShr    0x16
#define X86InstrNeg    0x17
#define X86InstrNot    0x18
#define X86InstrCbw    0x19
#define X86InstrCwd    0x1A
#define X86InstrCdq    0x1B
#define X86InstrSetCc  0x1C
#define X86InstrJcc    0x1D
#define X86InstrJNotCc 0x1E
#define X86InstrLeave  0x1F
#define X86InstrCall   0x20
#define X86InstrRet    0x21
#define X86InstrJmp    0x22

void GenPrintInstr(int instr, int val)
{
  char* p = "";

  switch (instr)
  {
  case X86InstrMov: p = "mov"; break;
  case X86InstrMovSx: p = "movsx"; break;
  case X86InstrMovZx: p = "movzx"; break;
  case X86InstrXchg: p = "xchg"; break;
  case X86InstrLea: p = "lea"; break;
  case X86InstrPush: p = "push"; break;
  case X86InstrPop: p = "pop"; break;
  case X86InstrInc: p = "inc"; break;
  case X86InstrDec: p = "dec"; break;
  case X86InstrAdd: p = "add"; break;
  case X86InstrSub: p = "sub"; break;
  case X86InstrAnd: p = "and"; break;
  case X86InstrXor: p = "xor"; break;
  case X86InstrOr: p = "or"; break;
  case X86InstrCmp: p = "cmp"; break;
  case X86InstrTest: p = "test"; break;
  case X86InstrMul: p = "mul"; break;
  case X86InstrImul: p = "imul"; break;
  case X86InstrIdiv: p = "idiv"; break;
  case X86InstrDiv: p = "div"; break;
  case X86InstrShl: p = "shl"; break;
  case X86InstrSar: p = "sar"; break;
  case X86InstrShr: p = "shr"; break;
  case X86InstrNeg: p = "neg"; break;
  case X86InstrNot: p = "not"; break;
  case X86InstrCbw: p = "cbw"; break;
  case X86InstrCwd: p = "cwd"; break;
  case X86InstrCdq: p = "cdq"; break;
  case X86InstrLeave: p = "leave"; break;
  case X86InstrCall: p = "call"; break;
  case X86InstrRet: p = "ret"; break;
  case X86InstrJmp: p = "jmp"; break;

  case X86InstrJcc:
    switch (val)
    {
    case '<':         p = "jl"; break;
    case tokULess:    p = "jb"; break;
    case '>':         p = "jg"; break;
    case tokUGreater: p = "ja"; break;
    case tokLEQ:      p = "jle"; break;
    case tokULEQ:     p = "jbe"; break;
    case tokGEQ:      p = "jge"; break;
    case tokUGEQ:     p = "jae"; break;
    case tokEQ:       p = "je"; break;
    case tokNEQ:      p = "jne"; break;
    }
    break;
  case X86InstrJNotCc:
    switch (val)
    {
    case '<':         p = "jge"; break;
    case tokULess:    p = "jae"; break;
    case '>':         p = "jle"; break;
    case tokUGreater: p = "jbe"; break;
    case tokLEQ:      p = "jg"; break;
    case tokULEQ:     p = "ja"; break;
    case tokGEQ:      p = "jl"; break;
    case tokUGEQ:     p = "jb"; break;
    case tokEQ:       p = "jne"; break;
    case tokNEQ:      p = "je"; break;
    }
    break;

  case X86InstrSetCc:
    switch (val)
    {
    case '<':         p = "setl"; break;
    case tokULess:    p = "setb"; break;
    case '>':         p = "setg"; break;
    case tokUGreater: p = "seta"; break;
    case tokLEQ:      p = "setle"; break;
    case tokULEQ:     p = "setbe"; break;
    case tokGEQ:      p = "setge"; break;
    case tokUGEQ:     p = "setae"; break;
    case tokEQ:       p = "sete"; break;
    case tokNEQ:      p = "setne"; break;
    }
    break;
  }

  switch (instr)
  {
  case X86InstrCbw:
  case X86InstrCwd:
  case X86InstrCdq:
  case X86InstrLeave:
  case X86InstrRet:
    printf("\t%s", p);
    break;
  default:
    printf("\t%s\t", p);
    break;
  }
}

#define X86OpRegAByte                   0x00
#define X86OpRegAByteHigh               0x01
#define X86OpRegCByte                   0x02
#define X86OpRegAWord                   0x03
#define X86OpRegBWord                   0x04
#define X86OpRegCWord                   0x05
#define X86OpRegDWord                   0x06
#define X86OpRegBpWord                  0x07
#define X86OpRegSpWord                  0x08
#define X86OpRegAByteOrWord             0x09
#define X86OpRegCByteOrWord             0x0A
#define X86OpConst                      0x0B
#define X86OpLabel                      0x0C
#define X86OpNumLabel                   0x0D
#define X86OpIndLabel                   0x0E
#define X86OpIndLabelExplicitByte       0x0F
#define X86OpIndLabelExplicitWord       0x10
#define X86OpIndLabelExplicitByteOrWord 0x11
#define X86OpIndLocal                   0x12
#define X86OpIndLocalExplicitByte       0x13
#define X86OpIndLocalExplicitWord       0x14
#define X86OpIndLocalExplicitByteOrWord 0x15
#define X86OpIndRegB                    0x16
#define X86OpIndRegBExplicitByte        0x17
#define X86OpIndRegBExplicitWord        0x18
#define X86OpIndRegBExplicitByteOrWord  0x19

int GenSelectByteOrWord(int op, int opSz)
{
  switch (op)
  {
  case X86OpRegAByteOrWord:
    op = X86OpRegAByte;
    if (opSz != 1)
      op = X86OpRegAWord;
    break;
  case X86OpRegCByteOrWord:
    op = X86OpRegCByte;
    if (opSz != 1)
      op = X86OpRegCWord;
    break;
  case X86OpIndLabelExplicitByteOrWord:
    op = X86OpIndLabelExplicitByte;
    if (opSz != 1)
      op = X86OpIndLabelExplicitWord;
    break;
  case X86OpIndLocalExplicitByteOrWord:
    op = X86OpIndLocalExplicitByte;
    if (opSz != 1)
      op = X86OpIndLocalExplicitWord;
    break;
  case X86OpIndRegBExplicitByteOrWord:
    op = X86OpIndRegBExplicitByte;
    if (opSz != 1)
      op = X86OpIndRegBExplicitWord;
    break;
  }
  return op;
}

void GenPrintOperand(int op, int val)
{
  if (SizeOfWord == 2)
  {
    switch (op)
    {
    case X86OpRegAByte: printf("al"); break;
    case X86OpRegAByteHigh: printf("ah"); break;
    case X86OpRegCByte: printf("cl"); break;
    case X86OpRegAWord: printf("ax"); break;
    case X86OpRegBWord: printf("bx"); break;
    case X86OpRegCWord: printf("cx"); break;
    case X86OpRegDWord: printf("dx"); break;
    case X86OpRegBpWord: printf("bp"); break;
    case X86OpRegSpWord: printf("sp"); break;
    case X86OpConst: printf("%d", truncInt(val)); break;
    case X86OpLabel: GenPrintLabel(IdentTable + val); break;
    case X86OpNumLabel: GenPrintNumLabel(val); break;
    case X86OpIndLabel: printf("["); GenPrintLabel(IdentTable + val); printf("]"); break;
    case X86OpIndLabelExplicitByte: printf("byte ["); GenPrintLabel(IdentTable + val); printf("]"); break;
    case X86OpIndLabelExplicitWord: printf("word ["); GenPrintLabel(IdentTable + val); printf("]"); break;
    case X86OpIndLocal: printf("[bp%+d]", val); break;
    case X86OpIndLocalExplicitByte: printf("byte [bp%+d]", val); break;
    case X86OpIndLocalExplicitWord: printf("word [bp%+d]", val); break;
    case X86OpIndRegB: printf("[bx]"); break;
    case X86OpIndRegBExplicitByte: printf("byte [bx]"); break;
    case X86OpIndRegBExplicitWord: printf("word [bx]"); break;
    }
  }
  else
  {
    switch (op)
    {
    case X86OpRegAByte: printf("al"); break;
    case X86OpRegAByteHigh: printf("ah"); break;
    case X86OpRegCByte: printf("cl"); break;
    case X86OpRegAWord: printf("eax"); break;
    case X86OpRegBWord: printf("ebx"); break;
    case X86OpRegCWord: printf("ecx"); break;
    case X86OpRegDWord: printf("edx"); break;
    case X86OpRegBpWord: printf("ebp"); break;
    case X86OpRegSpWord: printf("esp"); break;
    case X86OpConst: printf("%d", truncInt(val)); break;
    case X86OpLabel: GenPrintLabel(IdentTable + val); break;
    case X86OpNumLabel: GenPrintNumLabel(val); break;
    case X86OpIndLabel: printf("["); GenPrintLabel(IdentTable + val); printf("]"); break;
    case X86OpIndLabelExplicitByte: printf("byte ["); GenPrintLabel(IdentTable + val); printf("]"); break;
    case X86OpIndLabelExplicitWord: printf("dword ["); GenPrintLabel(IdentTable + val); printf("]"); break;
    case X86OpIndLocal: printf("[ebp%+d]", val); break;
    case X86OpIndLocalExplicitByte: printf("byte [ebp%+d]", val); break;
    case X86OpIndLocalExplicitWord: printf("dword [ebp%+d]", val); break;
    case X86OpIndRegB: printf("[ebx]"); break;
    case X86OpIndRegBExplicitByte: printf("byte [ebx]"); break;
    case X86OpIndRegBExplicitWord: printf("dword [ebx]"); break;
    }
  }
}

void GenPrintOperandSeparator(void)
{
  printf(", ");
}

void GenPrintNewLine(void)
{
  puts("");
}

void GenPrintInstrNoOperand(int instr)
{
  GenPrintInstr(instr, 0);
  GenPrintNewLine();
}

void GenPrintCallFxn(char* name)
{
  GenPrintInstr(X86InstrCall, 0);
  GenPrintLabel(name);
  GenPrintNewLine();
}

void GenPrintInstr1Operand(int instr, int instrval, int operand, int operandval)
{
  GenPrintInstr(instr, instrval);
  GenPrintOperand(operand, operandval);
  GenPrintNewLine();
}

void GenPrintInstr2Operands(int instr, int instrval, int operand1, int operand1val, int operand2, int operand2val)
{
  if (operand2 == X86OpConst && operand2val == 0 &&
      (instr == X86InstrAdd || instr == X86InstrSub))
    return;

  if (operand2 == X86OpConst &&
      (operand2val == 1 || operand2val == -1) &&
      (instr == X86InstrAdd || instr == X86InstrSub))
  {
    if ((operand2val == 1 && instr == X86InstrAdd) ||
        (operand2val == -1 && instr == X86InstrSub))
      GenPrintInstr(X86InstrInc, 0);
    else
      GenPrintInstr(X86InstrDec, 0);
    GenPrintOperand(operand1, operand1val);
    GenPrintNewLine();
    return;
  }

  GenPrintInstr(instr, instrval);
  GenPrintOperand(operand1, operand1val);
  GenPrintOperandSeparator();
  GenPrintOperand(operand2, operand2val);
  GenPrintNewLine();
}

void GenPrintInstr3Operands(int instr, int instrval,
                            int operand1, int operand1val,
                            int operand2, int operand2val,
                            int operand3, int operand3val)
{
  GenPrintInstr(instr, instrval);
  GenPrintOperand(operand1, operand1val);
  GenPrintOperandSeparator();
  GenPrintOperand(operand2, operand2val);
  GenPrintOperandSeparator();
  GenPrintOperand(operand3, operand3val);
  GenPrintNewLine();
}

void GenExtendRegAIfNeeded(int opSz)
{
  if (opSz == 1)
  {
    if (SizeOfWord == 2)
    {
      if (CharIsSigned)
        GenPrintInstrNoOperand(X86InstrCbw);
      else
        GenPrintInstr2Operands(X86InstrMov, 0,
                               X86OpRegAByteHigh, 0,
                               X86OpConst, 0);
    }
    else
    {
      if (CharIsSigned)
        GenPrintInstr2Operands(X86InstrMovSx, 0,
                               X86OpRegAWord, 0,
                               X86OpRegAByte, 0);
      else
        GenPrintInstr2Operands(X86InstrMovZx, 0,
                               X86OpRegAWord, 0,
                               X86OpRegAByte, 0);
    }
  }
}

void GenJumpUncond(int label)
{
  GenPrintInstr1Operand(X86InstrJmp, 0,
                        X86OpNumLabel, label);
}

void GenJumpIfNotEqual(int val, int label)
{
  GenPrintInstr2Operands(X86InstrCmp, 0,
                         X86OpRegAWord, 0,
                         X86OpConst, val);
  GenPrintInstr1Operand(X86InstrJcc, tokNEQ,
                        X86OpNumLabel, label);
}

void GenJumpIfZero(int label)
{
#ifndef NO_ANNOTATIONS
  GenStartCommentLine(); printf("JumpIfZero\n");
#endif
  GenPrintInstr2Operands(X86InstrTest, 0,
                         X86OpRegAWord, 0,
                         X86OpRegAWord, 0);
  GenPrintInstr1Operand(X86InstrJcc, tokEQ,
                        X86OpNumLabel, label);
}

void GenJumpIfNotZero(int label)
{
#ifndef NO_ANNOTATIONS
  GenStartCommentLine(); printf("JumpIfNotZero\n");
#endif
  GenPrintInstr2Operands(X86InstrTest, 0,
                         X86OpRegAWord, 0,
                         X86OpRegAWord, 0);
  GenPrintInstr1Operand(X86InstrJcc, tokNEQ,
                        X86OpNumLabel, label);
}

void GenFxnProlog(void)
{
  GenPrintInstr1Operand(X86InstrPush, 0,
                        X86OpRegBpWord, 0);
  GenPrintInstr2Operands(X86InstrMov, 0,
                         X86OpRegBpWord, 0,
                         X86OpRegSpWord, 0);
}

void GenLocalAlloc(int size)
{
  GenPrintInstr2Operands(X86InstrSub, 0,
                         X86OpRegSpWord, 0,
                         X86OpConst, size);
}

void GenFxnEpilog(void)
{
  GenPrintInstrNoOperand(X86InstrLeave);
  GenPrintInstrNoOperand(X86InstrRet);
}

void GenReadIdent(int opSz, int label)
{
  GenPrintInstr2Operands(X86InstrMov, 0,
                         GenSelectByteOrWord(X86OpRegAByteOrWord, opSz), 0,
                         X86OpIndLabel, label);
  GenExtendRegAIfNeeded(opSz);
}

void GenReadLocal(int opSz, int ofs)
{
  GenPrintInstr2Operands(X86InstrMov, 0,
                         GenSelectByteOrWord(X86OpRegAByteOrWord, opSz), 0,
                         X86OpIndLocal, ofs);
  GenExtendRegAIfNeeded(opSz);
}

void GenReadIndirect(int opSz)
{
  GenPrintInstr2Operands(X86InstrMov, 0,
                         X86OpRegBWord, 0,
                         X86OpRegAWord, 0);
  GenPrintInstr2Operands(X86InstrMov, 0,
                         GenSelectByteOrWord(X86OpRegAByteOrWord, opSz), 0,
                         X86OpIndRegB, 0);
  GenExtendRegAIfNeeded(opSz);
}

void GenReadCRegIdent(int opSz, int label)
{
  if (opSz == 1)
  {
    if (CharIsSigned)
      GenPrintInstr2Operands(X86InstrMovSx, 0,
                             X86OpRegCWord, 0,
                             X86OpIndLabelExplicitByte, label);
    else
      GenPrintInstr2Operands(X86InstrMovZx, 0,
                             X86OpRegCWord, 0,
                             X86OpIndLabelExplicitByte, label);
  }
  else
    GenPrintInstr2Operands(X86InstrMov, 0,
                           X86OpRegCWord, 0,
                           X86OpIndLabel, label);
}

void GenReadCRegLocal(int opSz, int ofs)
{
  if (opSz == 1)
  {
    if (CharIsSigned)
      GenPrintInstr2Operands(X86InstrMovSx, 0,
                             X86OpRegCWord, 0,
                             X86OpIndLocalExplicitByte, ofs);
    else
      GenPrintInstr2Operands(X86InstrMovZx, 0,
                             X86OpRegCWord, 0,
                             X86OpIndLocalExplicitByte, ofs);
  }
  else
    GenPrintInstr2Operands(X86InstrMov, 0,
                           X86OpRegCWord, 0,
                           X86OpIndLocal, ofs);
}

void GenReadCRegIndirect(int opSz)
{
  GenPrintInstr2Operands(X86InstrMov, 0,
                         X86OpRegBWord, 0,
                         X86OpRegAWord, 0);
  if (opSz == 1)
  {
    if (CharIsSigned)
      GenPrintInstr2Operands(X86InstrMovSx, 0,
                             X86OpRegCWord, 0,
                             X86OpIndRegBExplicitByte, 0);
    else
      GenPrintInstr2Operands(X86InstrMovZx, 0,
                             X86OpRegCWord, 0,
                             X86OpIndRegBExplicitByte, 0);
  }
  else
    GenPrintInstr2Operands(X86InstrMov, 0,
                           X86OpRegCWord, 0,
                           X86OpIndRegB, 0);
}

void GenIncDecIdent(int opSz, int label, int tok)
{
  int instr = X86InstrInc;

  if (tok != tokInc)
    instr = X86InstrDec;

  GenPrintInstr1Operand(instr, 0,
                        GenSelectByteOrWord(X86OpIndLabelExplicitByteOrWord, opSz), label);
  GenPrintInstr2Operands(X86InstrMov, 0,
                         GenSelectByteOrWord(X86OpRegAByteOrWord, opSz), 0,
                         X86OpIndLabel, label);
  GenExtendRegAIfNeeded(opSz);
}

void GenIncDecLocal(int opSz, int ofs, int tok)
{
  int instr = X86InstrInc;

  if (tok != tokInc)
    instr = X86InstrDec;

  GenPrintInstr1Operand(instr, 0,
                        GenSelectByteOrWord(X86OpIndLocalExplicitByteOrWord, opSz), ofs);
  GenPrintInstr2Operands(X86InstrMov, 0,
                         GenSelectByteOrWord(X86OpRegAByteOrWord, opSz), 0,
                         X86OpIndLocal, ofs);
  GenExtendRegAIfNeeded(opSz);
}

void GenIncDecIndirect(int opSz, int tok)
{
  int instr = X86InstrInc;

  if (tok != tokInc)
    instr = X86InstrDec;

  GenPrintInstr2Operands(X86InstrMov, 0,
                         X86OpRegBWord, 0,
                         X86OpRegAWord, 0);
  GenPrintInstr1Operand(instr, 0,
                        GenSelectByteOrWord(X86OpIndRegBExplicitByteOrWord, opSz), 0);
  GenPrintInstr2Operands(X86InstrMov, 0,
                         GenSelectByteOrWord(X86OpRegAByteOrWord, opSz), 0,
                         X86OpIndRegB, 0);
  GenExtendRegAIfNeeded(opSz);
}

void GenPostIncDecIdent(int opSz, int label, int tok)
{
  int instr = X86InstrInc;

  if (tok != tokPostInc)
    instr = X86InstrDec;

  GenPrintInstr2Operands(X86InstrMov, 0,
                         GenSelectByteOrWord(X86OpRegAByteOrWord, opSz), 0,
                         X86OpIndLabel, label);
  GenExtendRegAIfNeeded(opSz);
  GenPrintInstr1Operand(instr, 0,
                        GenSelectByteOrWord(X86OpIndLabelExplicitByteOrWord, opSz), label);
}

void GenPostIncDecLocal(int opSz, int ofs, int tok)
{
  int instr = X86InstrInc;

  if (tok != tokPostInc)
    instr = X86InstrDec;

  GenPrintInstr2Operands(X86InstrMov, 0,
                         GenSelectByteOrWord(X86OpRegAByteOrWord, opSz), 0,
                         X86OpIndLocal, ofs);
  GenExtendRegAIfNeeded(opSz);
  GenPrintInstr1Operand(instr, 0,
                        GenSelectByteOrWord(X86OpIndLocalExplicitByteOrWord, opSz), ofs);
}

void GenPostIncDecIndirect(int opSz, int tok)
{
  int instr = X86InstrInc;

  if (tok != tokPostInc)
    instr = X86InstrDec;

  GenPrintInstr2Operands(X86InstrMov, 0,
                         X86OpRegBWord, 0,
                         X86OpRegAWord, 0);
  GenPrintInstr2Operands(X86InstrMov, 0,
                         GenSelectByteOrWord(X86OpRegAByteOrWord, opSz), 0,
                         X86OpIndRegB, 0);
  GenExtendRegAIfNeeded(opSz);
  GenPrintInstr1Operand(instr, 0,
                        GenSelectByteOrWord(X86OpIndRegBExplicitByteOrWord, opSz), 0);
}

void GenPostAddSubIdent(int opSz, int val, int label, int tok)
{
  int instr = X86InstrAdd;

  if (tok != tokPostAdd)
    instr = X86InstrSub;

  GenPrintInstr2Operands(X86InstrMov, 0,
                         GenSelectByteOrWord(X86OpRegAByteOrWord, opSz), 0,
                         X86OpIndLabel, label);
  GenExtendRegAIfNeeded(opSz);
  GenPrintInstr2Operands(instr, 0,
                         GenSelectByteOrWord(X86OpIndLabelExplicitByteOrWord, opSz), label,
                         X86OpConst, val);
}

void GenPostAddSubLocal(int opSz, int val, int ofs, int tok)
{
  int instr = X86InstrAdd;

  if (tok != tokPostAdd)
    instr = X86InstrSub;

  GenPrintInstr2Operands(X86InstrMov, 0,
                         GenSelectByteOrWord(X86OpRegAByteOrWord, opSz), 0,
                         X86OpIndLocal, ofs);
  GenExtendRegAIfNeeded(opSz);
  GenPrintInstr2Operands(instr, 0,
                         GenSelectByteOrWord(X86OpIndLocalExplicitByteOrWord, opSz), ofs,
                         X86OpConst, val);
}

void GenPostAddSubIndirect(int opSz, int val, int tok)
{
  int instr = X86InstrAdd;

  if (tok != tokPostAdd)
    instr = X86InstrSub;

  GenPrintInstr2Operands(X86InstrMov, 0,
                         X86OpRegBWord, 0,
                         X86OpRegAWord, 0);
  GenPrintInstr2Operands(X86InstrMov, 0,
                         GenSelectByteOrWord(X86OpRegAByteOrWord, opSz), 0,
                         X86OpIndRegB, 0);
  GenExtendRegAIfNeeded(opSz);
  GenPrintInstr2Operands(instr, 0,
                         GenSelectByteOrWord(X86OpIndRegBExplicitByteOrWord, opSz), 0,
                         X86OpConst, val);
}

#define tokOpNumInt      0x100
#define tokOpNumUint     0x101
#define tokOpIdent       0x102
#define tokOpLocalOfs    0x103
#define tokOpAcc         0x104
#define tokOpIndIdent    0x105
#define tokOpIndLocalOfs 0x106
#define tokOpIndAcc      0x107
#define tokOpStack       0x108
#define tokOpIndStack    0x109

#define tokPushAcc       0x200

int GetOperandInfo(int idx, int lvalSize, int* val, int* size, int* delDeref)
{
  int idx0 = idx;

  *delDeref = 0;

  while (stack[idx][0] >= tokOpNumInt && stack[idx][0] <= tokOpIndAcc)
    idx--;

  if (stack[idx][0] == tokUnaryStar)
  {
    if (lvalSize)
    {
      // lvalue dereference is implied for the left operand of =
      // and for operands of ++/--, these operands contain the
      // lvalue address
      *size = lvalSize;
      *val = 0;
      return tokOpIndAcc;
    }

    *size = stack[idx][1]; // take size from tokUnaryStar

    *delDeref = 1;
    *val = stack[idx + 1][1]; // operand "value" is in tokUnaryStar's operand
    return stack[idx + 1][0] + tokOpIndIdent - tokOpIdent; // add indirection
  }

  idx = idx0;

  if (lvalSize)
  {
    // lvalue dereference is implied for the left operand of =
    // and for operands of ++/--
    *size = lvalSize;
    *val = stack[idx][1];

    switch (stack[idx][0])
    {
    case tokIdent:
      return tokOpIndIdent;
    case tokLocalOfs:
      return tokOpIndLocalOfs;

    default:
      *val = 0;
      return tokOpIndAcc;
    }
  }

  *size = SizeOfWord;
  *val = stack[idx][1];

  switch (stack[idx][0])
  {
  case tokNumInt:
    return tokOpNumInt;
  case tokNumUint:
    return tokOpNumUint;
  case tokIdent:
    return tokOpIdent;
  case tokLocalOfs:
    return tokOpLocalOfs;

  default:
    *val = 0;
    return tokOpAcc;
  }
}

void GenFuse(int* idx)
{
  int tok;
  int oldIdxRight, oldSpRight;
  int oldIdxLeft, oldSpLeft;
  int opSzRight, opSzLeft;
  int opTypRight, opTypLeft;
  int opValRight, opValLeft;
  int delDerefRight, delDerefLeft;
  int num, lvalSize;

  if (*idx < 0)
    error("GenFuse(): idx < 0\n");

  tok = stack[*idx][0];

  --*idx;

  oldIdxRight = *idx;
  oldSpRight = sp;

  switch (tok)
  {
  case tokNumInt:
  case tokNumUint:
  case tokIdent:
  case tokLocalOfs:
    break;

  case tokShortCirc:
    GenFuse(idx);
    break;

  case tokUnaryStar:
    opSzRight = stack[*idx + 1][1];
    GenFuse(idx);
    oldIdxRight -= oldSpRight - sp;

    switch (stack[oldIdxRight][0])
    {
    case tokIdent:
    case tokLocalOfs:
      if (stack[oldIdxRight][0] == tokIdent)
        stack[oldIdxRight + 1][0] = tokOpIdent;
      else
        stack[oldIdxRight + 1][0] = tokOpLocalOfs;
      stack[oldIdxRight + 1][1] = stack[oldIdxRight][1];
      stack[oldIdxRight][0] = tok;
      stack[oldIdxRight][1] = opSzRight;
      break;
    default:
      ins(oldIdxRight + 2, tokOpAcc);
      break;
    }
    break;

  case tokInc:
  case tokDec:
  case tokPostInc:
  case tokPostDec:
    opSzRight = stack[*idx + 1][1];
    GenFuse(idx);
    oldIdxRight -= oldSpRight - sp;

    switch (stack[oldIdxRight][0])
    {
    case tokIdent:
    case tokLocalOfs:
      if (stack[oldIdxRight][0] == tokIdent)
        stack[oldIdxRight + 1][0] = tokOpIndIdent;
      else
        stack[oldIdxRight + 1][0] = tokOpIndLocalOfs;
      stack[oldIdxRight + 1][1] = stack[oldIdxRight][1];
      stack[oldIdxRight][0] = tok;
      stack[oldIdxRight][1] = opSzRight;
      break;
    default:
      ins(oldIdxRight + 2, tokOpIndAcc);
      break;
    }
    break;

  case '~':
  case tokUnaryPlus:
  case tokUnaryMinus:
  case tok_Bool:
  case tokVoid:
    GenFuse(idx);
    oldIdxRight -= oldSpRight - sp;
    if (tok == tokUnaryPlus)
      del(oldIdxRight + 1, 1);
    break;

  case tokPostAdd:
  case tokPostSub:
    opSzRight = stack[*idx + 1][1];
    num = stack[*idx][1];
    oldIdxRight = --*idx; // skip tokNum
    GenFuse(idx);
    oldIdxRight -= oldSpRight - sp;
    switch (stack[oldIdxRight][0])
    {
    case tokIdent:
    case tokLocalOfs:
      stack[oldIdxRight + 2][0] = tokOpNumInt;
      stack[oldIdxRight + 2][1] = num;
      if (stack[oldIdxRight][0] == tokIdent)
        stack[oldIdxRight + 1][0] = tokOpIndIdent;
      else
        stack[oldIdxRight + 1][0] = tokOpIndLocalOfs;
      stack[oldIdxRight + 1][1] = stack[oldIdxRight][1];
      stack[oldIdxRight][0] = tok;
      stack[oldIdxRight][1] = opSzRight;
      break;
    default:
      stack[oldIdxRight + 1][0] = tok;
      stack[oldIdxRight + 1][1] = opSzRight;
      stack[oldIdxRight + 2][0] = tokOpIndAcc;
      ins2(oldIdxRight + 3, tokOpNumInt, num);
      break;
    }
    break;

/*
  Operator-operand fusion:

  ac = lft:       ac op= rht:        lft = ac:
  (load)          ("execute")        (store)

  *(id/l)         *(id/l)            *(id/l)
    mov a?,mlft     op a?,mrht         mov mlft,a?
                    ---
                    mov cl,mrht
                    shift ax,cl
                    ---
                    mov c?,mrht
                    cwd
                    idiv cx
                    opt: mov ax,dx

  *ac             *ac                *ac
    mov bx,ax       < mov bx,ax        ; bx preserved
    mov a?,[bx]     < mov c?,[bx]      mov [bx],a?
                    op ax,cx(cl)

  *ac-stack       n/a                *ac-stack
    pop bx                             ; bx preserved
    mov a?,[bx]                        mov [bx],a?

  id/num          id/num
    mov ax,ilft     op ax,irht
                    ---
                    mov cx,irht
                    op ax,cx

  l               l
    lea ax,llft     lea cx,lrht
                    op ax,cx

  ac              ac
    nop             < mov cx,ax
                    op ax,cx

  ac-stack        n/a
    pop ax

  lft (*)ac -> lft (*)ac-stack IFF rht is (*)ac

  Legend:
  - lft/rht - left/right operand
  - num - number
  - id - global/static identifier/location
  - l - local variable location
  - * - dereference operator
  - m - memory operand at address id/l
  - i - immediate/number/constant operand
  - ac - accumulator (al or ax)
  - a? - accumulator (al or ax), depending on operand size
  - b? - bl or bx, depending on operand size
  - >push axlft - need to insert "push ax" at the end of the left operand evaluation

    instruction operand combinations (dst/lft, src/rht):
    - r/m, r/imm
    - r, m

    special instructions:
    - lea r, m
    - shl/sar
    - mul/imul/idiv
    - cbw/cwd
    - movsx/movzx
*/

  case '=':
  case tokAssignAdd:
  case tokAssignSub:
  case tokAssignMul:
  case tokAssignDiv:
  case tokAssignUDiv:
  case tokAssignMod:
  case tokAssignUMod:
  case tokAssignLSh:
  case tokAssignRSh:
  case tokAssignURSh:
  case tokAssignAnd:
  case tokAssignXor:
  case tokAssignOr:
  case '+':
  case '-':
  case '*':
  case '/':
  case tokUDiv:
  case '%':
  case tokUMod:
  case tokLShift:
  case tokRShift:
  case tokURShift:
  case '&':
  case '^':
  case '|':
  case '<':
  case '>':
  case tokLEQ:
  case tokGEQ:
  case tokEQ:
  case tokNEQ:
  case tokULess:
  case tokUGreater:
  case tokULEQ:
  case tokUGEQ:
  case tokLogAnd:
  case tokLogOr:
  case tokComma:
    switch (tok)
    {
    case '=':
    case tokAssignAdd:
    case tokAssignSub:
    case tokAssignMul:
    case tokAssignDiv:
    case tokAssignUDiv:
    case tokAssignMod:
    case tokAssignUMod:
    case tokAssignLSh:
    case tokAssignRSh:
    case tokAssignURSh:
    case tokAssignAnd:
    case tokAssignXor:
    case tokAssignOr:
      lvalSize = stack[*idx + 1][1];
      break;
    default:
      lvalSize = 0;
      break;
    }

    GenFuse(idx);
    oldIdxRight -= oldSpRight - sp;
    opTypRight = GetOperandInfo(oldIdxRight, 0, &opValRight, &opSzRight, &delDerefRight);

    oldIdxLeft = *idx; oldSpLeft = sp;
    GenFuse(idx);
    oldIdxLeft -= oldSpLeft - sp;
    oldIdxRight -= oldSpLeft - sp;
    opTypLeft = GetOperandInfo(oldIdxLeft, lvalSize, &opValLeft, &opSzLeft, &delDerefLeft);

    // operands of &&, || and comma aren't to be fused into &&, || and comma
    if (tok == tokLogAnd || tok == tokLogOr || tok == tokComma)
      break;

    if (opTypLeft != tokOpAcc && opTypLeft != tokOpIndAcc)
    {
      // the left operand will be fully fused into the operator, remove it
      int cnt = oldIdxLeft - *idx;
      del(*idx + 1, cnt);
      oldIdxLeft -= cnt;
      oldIdxRight -= cnt;
    }
    else if (opTypRight == tokOpAcc || opTypRight == tokOpIndAcc)
    {
      // preserve ax after the evaluation of the left operand
      // because the right operand's value ends up in ax as well
      ins(++oldIdxLeft, tokPushAcc);
      oldIdxRight++;
      // adjust the left operand "type"/location
      if (opTypLeft == tokOpAcc)
        opTypLeft = tokOpStack;
      else
        opTypLeft = tokOpIndStack;
      if (delDerefLeft)
      {
        // remove the dereference, fusing will take care of it
        del(oldIdxLeft -= 2, 2);
        oldIdxRight -= 2;
      }
    }
    else if (delDerefLeft)
    {
      // remove the dereference, fusing will take care of it
      del(oldIdxLeft - 1, 2);
      oldIdxLeft -= 2;
      oldIdxRight -= 2;
    }

    if (opTypRight != tokOpAcc && opTypRight != tokOpIndAcc)
    {
      // the right operand will be fully fused into the operator, remove it
      int cnt = oldIdxRight - oldIdxLeft;
      del(oldIdxLeft + 1, cnt);
      oldIdxRight -= cnt;
    }
    else if (delDerefRight)
    {
      // remove the dereference, fusing will take care of it
      del(oldIdxRight - 1, 2);
      oldIdxRight -= 2;
    }

    // store the operand sizes into the operator
    stack[oldIdxRight + 1][1] = opSzLeft * 16 + opSzRight;

    // fuse the operands into the operator
    ins2(oldIdxRight + 2, opTypRight, opValRight);
    ins2(oldIdxRight + 2, opTypLeft, opValLeft);
    break;

  case ')':
    while (stack[*idx][0] != '(')
    {
      GenFuse(idx);
      if (stack[*idx][0] == ',')
        --*idx;
    }
    --*idx;
    break;

  default:
    error("GenFuse: unexpected token %s\n", GetTokenName(tok));
  }
}

int GenGetBinaryOperatorInstr(int tok)
{
  switch (tok)
  {
  case tokPostAdd:
  case tokAssignAdd:
  case '+':
    return X86InstrAdd;
  case tokPostSub:
  case tokAssignSub:
  case '-':
    return X86InstrSub;
  case '&':
  case tokAssignAnd:
    return X86InstrAnd;
  case '^':
  case tokAssignXor:
    return X86InstrXor;
  case '|':
  case tokAssignOr:
    return X86InstrOr;
  case '<':
  case '>':
  case tokLEQ:
  case tokGEQ:
  case tokEQ:
  case tokNEQ:
  case tokULess:
  case tokUGreater:
  case tokULEQ:
  case tokUGEQ:
    return X86InstrCmp;
  case '*':
  case tokAssignMul:
    return X86InstrMul;
  case '/':
  case '%':
  case tokAssignDiv:
  case tokAssignMod:
    return X86InstrIdiv;
  case tokUDiv:
  case tokUMod:
  case tokAssignUDiv:
  case tokAssignUMod:
    return X86InstrDiv;
  case tokLShift:
  case tokAssignLSh:
    return X86InstrShl;
  case tokRShift:
  case tokAssignRSh:
    return X86InstrSar;
  case tokURShift:
  case tokAssignURSh:
    return X86InstrShr;

  default:
    error("Error: Invalid operator\n");
    return 0;
  }
}

// Newer, less stack-dependent code generator,
// generates more compact code (~30% less) than the stack-based generator
#ifndef CG_STACK_BASED
void GenExpr1(void)
{
  int s = sp - 1;
  int i;

  if (stack[s][0] == tokIf || stack[s][0] == tokIfNot)
    s--;
  GenFuse(&s);

#ifndef NO_ANNOTATIONS
  printf("; Fused expression:    \"");
  for (i = 0; i < sp; i++)
  {
    int tok = stack[i][0];
    switch (tok)
    {
    case tokNumInt:
    case tokOpNumInt:
      printf("%d", truncInt(stack[i][1]));
      break;
    case tokNumUint:
    case tokOpNumUint:
      printf("%uu", truncUint(stack[i][1]));
      break;
    case tokIdent:
    case tokOpIdent:
      {
        char* p = IdentTable + stack[i][1];
        if (isdigit(*p))
          printf("L");
        printf("%s", p);
      }
      break;
    case tokOpIndIdent:
      printf("*%s", IdentTable + stack[i][1]);
      break;
    case tokShortCirc:
      if (stack[i][1] >= 0)
        printf("[sh&&->%d]", stack[i][1]);
      else
        printf("[sh||->%d]", -stack[i][1]);
      break;
    case tokLocalOfs:
    case tokOpLocalOfs:
      printf("(@%d)", stack[i][1]);
      break;
    case tokOpIndLocalOfs:
      printf("*(@%d)", stack[i][1]);
      break;
    case tokUnaryStar:
      printf("*(%d)", stack[i][1]);
      break;
    case '(': case ',':
      printf("%c", tok);
      break;
    case ')':
      printf(")%d", stack[i][1]);
      break;
    case tokOpAcc:
      printf("ax");
      break;
    case tokOpIndAcc:
      printf("*ax");
      break;
    case tokOpStack:
      printf("*sp");
      break;
    case tokOpIndStack:
      printf("**sp");
      break;
    case tokPushAcc:
      printf("push-ax");
      break;
    case tokIf:
      printf("IF");
      break;
    case tokIfNot:
      printf("IF!");
      break;
    default:
      printf("%s", GetTokenName(tok));
      switch (tok)
      {
      case tokLogOr: case tokLogAnd:
        printf("[%d]", stack[i][1]);
        break;
      case '=':
      case tokInc: case tokDec:
      case tokPostInc: case tokPostDec:
      case tokAssignAdd: case tokAssignSub:
      case tokPostAdd: case tokPostSub:
      case tokAssignMul: case tokAssignDiv: case tokAssignMod:
      case tokAssignUDiv: case tokAssignUMod:
      case tokAssignLSh: case tokAssignRSh: case tokAssignURSh:
      case tokAssignAnd: case tokAssignXor: case tokAssignOr:
        printf("(%d)", stack[i][1]);
        break;
      }
      break;
    }
    printf(" ");
  }
  printf("\"\n");
#endif

  for (i = 0; i < sp; i++)
  {
    int tok = stack[i][0];
    int v = stack[i][1];
    int instr;

    switch (tok)
    {
    case tokNumInt:
    case tokNumUint:
      // Don't load operand into ax when ax is going to be pushed next, push it directly
      if (!(i + 1 < sp && stack[i + 1][0] == ','))
        GenPrintInstr2Operands(X86InstrMov, 0,
                               X86OpRegAWord, 0,
                               X86OpConst, v);
      break;
    case tokIdent:
      // Don't load operand into ax when ax is going to be pushed next, push it directly
      if (!(i + 1 < sp && (stack[i + 1][0] == ',' || stack[i + 1][0] == ')')))
        GenPrintInstr2Operands(X86InstrMov, 0,
                               X86OpRegAWord, 0,
                               X86OpLabel, v);
      break;
    case tokLocalOfs:
      GenPrintInstr2Operands(X86InstrLea, 0,
                             X86OpRegAWord, 0,
                             X86OpIndLocal, v);
      break;

    case '~':
      GenPrintInstr1Operand(X86InstrNot, 0,
                            X86OpRegAWord, 0);
      break;
    case tokUnaryMinus:
      GenPrintInstr1Operand(X86InstrNeg, 0,
                            X86OpRegAWord, 0);
      break;
    case tok_Bool:
      GenPrintInstr2Operands(X86InstrTest, 0,
                             X86OpRegAWord, 0,
                             X86OpRegAWord, 0);
      GenPrintInstr1Operand(X86InstrSetCc, tokNEQ,
                            X86OpRegAByte, 0);
      if (SizeOfWord == 2)
        GenPrintInstrNoOperand(X86InstrCbw);
      else
        GenPrintInstr2Operands(X86InstrMovZx, 0,
                               X86OpRegAWord, 0,
                               X86OpRegAByte, 0);
      break;

    case tokShortCirc:
      if (v >= 0)
        GenJumpIfZero(v); // &&
      else
        GenJumpIfNotZero(-v); // ||
      break;
    case tokLogAnd:
      GenNumLabel(v);
      break;
    case tokLogOr:
      GenNumLabel(v);
      break;

    case tokPushAcc:
      // TBD??? handle similarly to ','???
      GenPrintInstr1Operand(X86InstrPush, 0,
                            X86OpRegAWord, 0);
      break;

    case ',':
      // push operand directly if it hasn't been loaded into ax
      if (stack[i - 2][0] == tokUnaryStar && stack[i - 2][1] != 1)
      {
        switch (stack[i - 1][0])
        {
        case tokOpIdent:
          GenPrintInstr1Operand(X86InstrPush, 0,
                                X86OpIndLabelExplicitWord, stack[i - 1][1]);
          break;
        case tokOpLocalOfs:
          GenPrintInstr1Operand(X86InstrPush, 0,
                                X86OpIndLocalExplicitWord, stack[i - 1][1]);
          break;
        case tokOpAcc:
          GenPrintInstr2Operands(X86InstrMov, 0,
                                 X86OpRegBWord, 0,
                                 X86OpRegAWord, 0);
          GenPrintInstr1Operand(X86InstrPush, 0,
                                X86OpIndRegBExplicitWord, 0);
          break;
        }
      }
      else
      {
        switch (stack[i - 1][0])
        {
        case tokNumInt:
        case tokNumUint:
          GenPrintInstr1Operand(X86InstrPush, 0,
                                X86OpConst, stack[i - 1][1]);
          break;
        case tokIdent:
          GenPrintInstr1Operand(X86InstrPush, 0,
                                X86OpLabel, stack[i - 1][1]);
          break;
        default:
          GenPrintInstr1Operand(X86InstrPush, 0,
                                X86OpRegAWord, 0);
          break;
        }
      }
      break;

    case tokUnaryStar:
      // Don't load operand into ax when ax is going to be pushed next, push it directly
      if (!(v != 1 && i + 2 < sp && stack[i + 2][0] == ','))
      {
        switch (stack[i + 1][0])
        {
        case tokOpIdent:
          GenReadIdent(v, stack[i + 1][1]);
          break;
        case tokOpLocalOfs:
          GenReadLocal(v, stack[i + 1][1]);
          break;
        case tokOpAcc:
          GenReadIndirect(v);
          break;
        }
      }
      i++;
      break;

    case tokInc:
    case tokDec:
      switch (stack[i + 1][0])
      {
      case tokOpIndIdent:
        GenIncDecIdent(v, stack[i + 1][1], tok);
        break;
      case tokOpIndLocalOfs:
        GenIncDecLocal(v, stack[i + 1][1], tok);
        break;
      case tokOpIndAcc:
        GenIncDecIndirect(v, tok);
        break;
      }
      i++;
      break;

    case tokPostInc:
    case tokPostDec:
      switch (stack[i + 1][0])
      {
      case tokOpIndIdent:
        GenPostIncDecIdent(v, stack[i + 1][1], tok);
        break;
      case tokOpIndLocalOfs:
        GenPostIncDecLocal(v, stack[i + 1][1], tok);
        break;
      case tokOpIndAcc:
        GenPostIncDecIndirect(v, tok);
        break;
      }
      i++;
      break;

    case tokPostAdd:
    case tokPostSub:
      switch (stack[i + 1][0])
      {
      case tokOpIndIdent:
        GenPostAddSubIdent(v, stack[i + 2][1], stack[i + 1][1], tok);
        break;
      case tokOpIndLocalOfs:
        GenPostAddSubLocal(v, stack[i + 2][1], stack[i + 1][1], tok);
        break;
      case tokOpIndAcc:
        GenPostAddSubIndirect(v, stack[i + 2][1], tok);
        break;
      }
      i += 2;
      break;

    case '=':
    case tokAssignAdd:
    case tokAssignSub:
    case tokAssignMul:
    case tokAssignDiv:
    case tokAssignUDiv:
    case tokAssignMod:
    case tokAssignUMod:
    case tokAssignLSh:
    case tokAssignRSh:
    case tokAssignURSh:
    case tokAssignAnd:
    case tokAssignXor:
    case tokAssignOr:
    case '+':
    case '-':
    case '*':
    case '/':
    case tokUDiv:
    case '%':
    case tokUMod:
    case tokLShift:
    case tokRShift:
    case tokURShift:
    case '&':
    case '^':
    case '|':
    case '<':
    case '>':
    case tokLEQ:
    case tokGEQ:
    case tokEQ:
    case tokNEQ:
    case tokULess:
    case tokUGreater:
    case tokULEQ:
    case tokUGEQ:
      // save the right operand from ax in cx, so it's not
      // overwritten by the left operand in ax
      if (tok != '=')
      {
        if (stack[i + 2][0] == tokOpAcc)
        {
          GenPrintInstr2Operands(X86InstrMov, 0,
                                 X86OpRegCWord, 0,
                                 X86OpRegAWord, 0);
        }
        else if (stack[i + 2][0] == tokOpIndAcc)
        {
          GenReadCRegIndirect(v % 16);
        }
      }

      // load the left operand into ax (or the right operand if it's '=')

      if (tok == '=')
      {
        if (stack[i + 1][0] == tokOpIndAcc)
          GenPrintInstr2Operands(X86InstrMov, 0,
                                 X86OpRegBWord, 0,
                                 X86OpRegAWord, 0);
        // "swap" left and right operands
        i++;
        v = v / 16 + v % 16 * 16;
      }

      switch (stack[i + 1][0])
      {
      case tokOpNumInt:
      case tokOpNumUint:
        GenPrintInstr2Operands(X86InstrMov, 0,
                               X86OpRegAWord, 0,
                               X86OpConst, stack[i + 1][1]);
        break;
      case tokOpIdent:
        GenPrintInstr2Operands(X86InstrMov, 0,
                               X86OpRegAWord, 0,
                               X86OpLabel, stack[i + 1][1]);
        break;
      case tokOpLocalOfs:
        GenPrintInstr2Operands(X86InstrLea, 0,
                               X86OpRegAWord, 0,
                               X86OpIndLocal, stack[i + 1][1]);
        break;
      case tokOpAcc:
        break;
      case tokOpIndIdent:
        GenReadIdent(v / 16, stack[i + 1][1]);
        break;
      case tokOpIndLocalOfs:
        GenReadLocal(v / 16, stack[i + 1][1]);
        break;
      case tokOpIndAcc:
        GenReadIndirect(v / 16);
        break;
      case tokOpStack:
        GenPrintInstr1Operand(X86InstrPop, 0,
                              X86OpRegAWord, 0);
        break;
      case tokOpIndStack:
        GenPrintInstr1Operand(X86InstrPop, 0,
                              X86OpRegBWord, 0);
        GenPrintInstr2Operands(X86InstrMov, 0,
                               GenSelectByteOrWord(X86OpRegAByteOrWord, v / 16), 0,
                               X86OpIndRegB, 0);
        GenExtendRegAIfNeeded(v / 16);
        break;
      }

      if (tok == '=')
      {
        // "unswap" left and right operands
        i--;
        v = v / 16 + v % 16 * 16;

        if (stack[i + 1][0] == tokOpIndStack)
          GenPrintInstr1Operand(X86InstrPop, 0,
                                X86OpRegBWord, 0);
      }

      // operator
      switch (tok)
      {
      case tokAssignAdd:
      case tokAssignSub:
      case tokAssignAnd:
      case tokAssignXor:
      case tokAssignOr:
      case '+':
      case '-':
      case '&':
      case '^':
      case '|':
      case '<':
      case '>':
      case tokLEQ:
      case tokGEQ:
      case tokEQ:
      case tokNEQ:
      case tokULess:
      case tokUGreater:
      case tokULEQ:
      case tokUGEQ:
        instr = GenGetBinaryOperatorInstr(tok);

        switch (stack[i + 2][0])
        {
        case tokOpNumInt:
        case tokOpNumUint:
          GenPrintInstr2Operands(instr, 0,
                                 X86OpRegAWord, 0,
                                 X86OpConst, stack[i + 2][1]);
          break;
        case tokOpIdent:
          GenPrintInstr2Operands(instr, 0,
                                 X86OpRegAWord, 0,
                                 X86OpLabel, stack[i + 2][1]);
          break;
        case tokOpLocalOfs:
          GenPrintInstr2Operands(X86InstrLea, 0,
                                 X86OpRegCWord, 0,
                                 X86OpIndLocal, stack[i + 2][1]);
          GenPrintInstr2Operands(instr, 0,
                                 X86OpRegAWord, 0,
                                 X86OpRegCWord, 0);
          break;
        case tokOpAcc:
        case tokOpIndAcc:
          // right operand in cx already
          GenPrintInstr2Operands(instr, 0,
                                 X86OpRegAWord, 0,
                                 X86OpRegCWord, 0);
          break;
        case tokOpIndIdent:
          if (v % 16 == 1)
          {
            GenReadCRegIdent(v % 16, stack[i + 2][1]);
            GenPrintInstr2Operands(instr, 0,
                                   X86OpRegAWord, 0,
                                   X86OpRegCWord, 0);
          }
          else
          {
            GenPrintInstr2Operands(instr, 0,
                                   X86OpRegAWord, 0,
                                   X86OpIndLabel, stack[i + 2][1]);
          }
          break;
        case tokOpIndLocalOfs:
          if (v % 16 == 1)
          {
            GenReadCRegLocal(v % 16, stack[i + 2][1]);
            GenPrintInstr2Operands(instr, 0,
                                   X86OpRegAWord, 0,
                                   X86OpRegCWord, 0);
          }
          else
          {
            GenPrintInstr2Operands(instr, 0,
                                   X86OpRegAWord, 0,
                                   X86OpIndLocal, stack[i + 2][1]);
          }
          break;
        }

        if (i + 3 < sp && (stack[i + 3][0] == tokIf || stack[i + 3][0] == tokIfNot))
        {
          switch (tok)
          {
          case '<':
          case tokULess:
          case '>':
          case tokUGreater:
          case tokLEQ:
          case tokULEQ:
          case tokGEQ:
          case tokUGEQ:
          case tokEQ:
          case tokNEQ:
            if (stack[i + 3][0] == tokIf)
              GenPrintInstr1Operand(X86InstrJcc, tok,
                                    X86OpNumLabel, stack[i + 3][1]);
            else
              GenPrintInstr1Operand(X86InstrJNotCc, tok,
                                    X86OpNumLabel, stack[i + 3][1]);
            break;
          }
        }
        else
        {
          switch (tok)
          {
          case '<':
          case tokULess:
          case '>':
          case tokUGreater:
          case tokLEQ:
          case tokULEQ:
          case tokGEQ:
          case tokUGEQ:
          case tokEQ:
          case tokNEQ:
            GenPrintInstr1Operand(X86InstrSetCc, tok,
                                  X86OpRegAByte, 0);
            if (SizeOfWord == 2)
              GenPrintInstrNoOperand(X86InstrCbw);
            else
              GenPrintInstr2Operands(X86InstrMovZx, 0,
                                     X86OpRegAWord, 0,
                                     X86OpRegAByte, 0);
            break;
          }
        }
        break;

      case '*':
      case tokAssignMul:
        instr = GenGetBinaryOperatorInstr(tok);

        switch (stack[i + 2][0])
        {
        case tokOpNumInt:
        case tokOpNumUint:
          GenPrintInstr3Operands(X86InstrImul, 0,
                                 X86OpRegAWord, 0,
                                 X86OpRegAWord, 0,
                                 X86OpConst, stack[i + 2][1]);
          break;
        case tokOpIdent:
          GenPrintInstr3Operands(X86InstrImul, 0,
                                 X86OpRegAWord, 0,
                                 X86OpRegAWord, 0,
                                 X86OpLabel, stack[i + 2][1]);
          break;
        case tokOpLocalOfs:
          GenPrintInstr2Operands(X86InstrLea, 0,
                                 X86OpRegCWord, 0,
                                 X86OpIndLocal, stack[i + 2][1]);
          GenPrintInstr1Operand(instr, 0,
                                X86OpRegCWord, 0);
          break;
        case tokOpAcc:
        case tokOpIndAcc:
          // right operand in cx already
          GenPrintInstr1Operand(instr, 0,
                                X86OpRegCWord, 0);
          break;
        case tokOpIndIdent:
          if (v % 16 == 1)
          {
            GenReadCRegIdent(v % 16, stack[i + 2][1]);
            GenPrintInstr1Operand(instr, 0,
                                  X86OpRegCWord, 0);
          }
          else
          {
            GenPrintInstr1Operand(instr, 0,
                                  X86OpIndLabelExplicitWord, stack[i + 2][1]);
          }
          break;
        case tokOpIndLocalOfs:
          if (v % 16 == 1)
          {
            GenReadCRegLocal(v % 16, stack[i + 2][1]);
            GenPrintInstr1Operand(instr, 0,
                                  X86OpRegCWord, 0);
          }
          else
          {
            GenPrintInstr1Operand(instr, 0,
                                  X86OpIndLocalExplicitWord, stack[i + 2][1]);
          }
          break;
        }
        break;

      case '/':
      case tokUDiv:
      case '%':
      case tokUMod:
      case tokAssignDiv:
      case tokAssignUDiv:
      case tokAssignMod:
      case tokAssignUMod:
        instr = GenGetBinaryOperatorInstr(tok);

        switch (tok)
        {
        case '/':
        case '%':
        case tokAssignDiv:
        case tokAssignMod:
          if (SizeOfWord == 2)
            GenPrintInstrNoOperand(X86InstrCwd);
          else
            GenPrintInstrNoOperand(X86InstrCdq);
          break;
        default:
          GenPrintInstr2Operands(X86InstrMov, 0,
                                 X86OpRegDWord, 0,
                                 X86OpConst, 0);
          break;
        }

        switch (stack[i + 2][0])
        {
        case tokOpNumInt:
        case tokOpNumUint:
          GenPrintInstr2Operands(X86InstrMov, 0,
                                 X86OpRegCWord, 0,
                                 X86OpConst, stack[i + 2][1]);
          GenPrintInstr1Operand(instr, 0,
                                X86OpRegCWord, 0);
          break;
        case tokOpIdent:
          GenPrintInstr2Operands(X86InstrMov, 0,
                                 X86OpRegCWord, 0,
                                 X86OpLabel, stack[i + 2][1]);
          GenPrintInstr1Operand(instr, 0,
                                X86OpRegCWord, 0);
          break;
        case tokOpLocalOfs:
          GenPrintInstr2Operands(X86InstrLea, 0,
                                 X86OpRegCWord, 0,
                                 X86OpIndLocal, stack[i + 2][1]);
          GenPrintInstr1Operand(instr, 0,
                                X86OpRegCWord, 0);
          break;
        case tokOpAcc:
        case tokOpIndAcc:
          // right operand in cx already
          GenPrintInstr1Operand(instr, 0,
                                X86OpRegCWord, 0);
          break;
        case tokOpIndIdent:
          if (v % 16 == 1)
          {
            GenReadCRegIdent(v % 16, stack[i + 2][1]);
            GenPrintInstr1Operand(instr, 0,
                                  X86OpRegCWord, 0);
          }
          else
          {
            GenPrintInstr1Operand(instr, 0,
                                  X86OpIndLabelExplicitWord, stack[i + 2][1]);
          }
          break;
        case tokOpIndLocalOfs:
          if (v % 16 == 1)
          {
            GenReadCRegLocal(v % 16, stack[i + 2][1]);
            GenPrintInstr1Operand(instr, 0,
                                  X86OpRegCWord, 0);
          }
          else
          {
            GenPrintInstr1Operand(instr, 0,
                                  X86OpIndLocalExplicitWord, stack[i + 2][1]);
          }
        }

        if (tok == '%' || tok == tokAssignMod ||
            tok == tokUMod || tok == tokAssignUMod)
          GenPrintInstr2Operands(X86InstrMov, 0,
                                 X86OpRegAWord, 0,
                                 X86OpRegDWord, 0);
        break;

      case tokLShift:
      case tokRShift:
      case tokURShift:
      case tokAssignLSh:
      case tokAssignRSh:
      case tokAssignURSh:
        instr = GenGetBinaryOperatorInstr(tok);

        switch (stack[i + 2][0])
        {
        case tokOpNumInt:
        case tokOpNumUint:
          GenPrintInstr2Operands(instr, 0,
                                 X86OpRegAWord, 0,
                                 X86OpConst, stack[i + 2][1]);
          break;
        case tokOpIdent:
          GenPrintInstr2Operands(instr, 0,
                                 X86OpRegAWord, 0,
                                 X86OpLabel, stack[i + 2][1]);
          break;
        case tokOpLocalOfs:
          GenPrintInstr2Operands(X86InstrLea, 0,
                                 X86OpRegCWord, 0,
                                 X86OpIndLocal, stack[i + 2][1]);
          GenPrintInstr2Operands(instr, 0,
                                 X86OpRegAWord, 0,
                                 X86OpRegCByte, 0);
          break;
        case tokOpAcc:
        case tokOpIndAcc:
          // right operand in cx already
          GenPrintInstr2Operands(instr, 0,
                                 X86OpRegAWord, 0,
                                 X86OpRegCByte, 0);
          break;
        case tokOpIndIdent:
          GenPrintInstr2Operands(X86InstrMov, 0,
                                 X86OpRegCByte, 0,
                                 X86OpIndLabel, stack[i + 2][1]);
          GenPrintInstr2Operands(instr, 0,
                                 X86OpRegAWord, 0,
                                 X86OpRegCByte, 0);
          break;
        case tokOpIndLocalOfs:
          GenPrintInstr2Operands(X86InstrMov, 0,
                                 X86OpRegCByte, 0,
                                 X86OpIndLocal, stack[i + 2][1]);
          GenPrintInstr2Operands(instr, 0,
                                 X86OpRegAWord, 0,
                                 X86OpRegCByte, 0);
          break;
        }
        break;

      case '=':
        break;

      default:
        error("Error: Internal Error: GenExpr1() a: unexpected token %s\n", GetTokenName(tok));
        break;
      }

      // store ax into the left operand, if needed
      switch (tok)
      {
      case '=':
      case tokAssignAdd:
      case tokAssignSub:
      case tokAssignMul:
      case tokAssignDiv:
      case tokAssignUDiv:
      case tokAssignMod:
      case tokAssignUMod:
      case tokAssignLSh:
      case tokAssignRSh:
      case tokAssignURSh:
      case tokAssignAnd:
      case tokAssignXor:
      case tokAssignOr:
        switch (stack[i + 1][0])
        {
        case tokOpIndIdent:
          GenPrintInstr2Operands(X86InstrMov, 0,
                                 X86OpIndLabel, stack[i + 1][1],
                                 GenSelectByteOrWord(X86OpRegAByteOrWord, v / 16), 0);
          break;
        case tokOpIndLocalOfs:
          GenPrintInstr2Operands(X86InstrMov, 0,
                                 X86OpIndLocal, stack[i + 1][1],
                                 GenSelectByteOrWord(X86OpRegAByteOrWord, v / 16), 0);
          break;
        case tokOpIndAcc:
        case tokOpIndStack:
          GenPrintInstr2Operands(X86InstrMov, 0,
                                 X86OpIndRegB, 0,
                                 GenSelectByteOrWord(X86OpRegAByteOrWord, v / 16), 0);
          break;
        }
        // the result of the expression is of type of the
        // left lvalue operand, so, "truncate" it if needed
        GenExtendRegAIfNeeded(v / 16);
      }
      i += 2;
      break;

    case ')':
      // DONE: "call ident"
      if (stack[i - 1][0] == tokIdent)
      {
        GenPrintInstr1Operand(X86InstrCall, 0,
                              X86OpLabel, stack[i - 1][1]);
      }
      else
      {
        GenPrintInstr1Operand(X86InstrCall, 0,
                              X86OpRegAWord, 0);
      }
      if (v)
        GenLocalAlloc(-v);
      break;

    case '(':
    case tokIf:
    case tokIfNot:
      break;

    case tokVoid:
    case tokComma:
      break;

    default:
      error("Error: Internal Error: GenExpr1() b: unexpected token %s\n", GetTokenName(tok));
      break;
    }
  }
}
#else // #ifndef CG_STACK_BASED
// Original, primitive stack-based code generator
// DONE: test 32-bit code generation
void GenExpr0(void)
{
  int i;
  int gotUnary = 0;

  for (i = 0; i < sp; i++)
  {
    int tok = stack[i][0];
    int v = stack[i][1];

#ifndef NO_ANNOTATIONS
    switch (tok)
    {
    case tokNumInt: printf("; %d\n", truncInt(v)); break;
    case tokNumUint: printf("; %uu\n", truncUint(v)); break;
    case tokIdent: printf("; %s\n", IdentTable + v); break;
    case tokLocalOfs: printf("; local ofs\n"); break;
    case ')': printf("; ) fxn call\n"); break;
    case tokUnaryStar: printf("; * (read dereference)\n"); break;
    case '=': printf("; = (write dereference)\n"); break;
    case tokShortCirc: printf("; short-circuit "); break;
    case tokLogAnd: printf("; short-circuit && target\n"); break;
    case tokLogOr: printf("; short-circuit || target\n"); break;
    case tokIf: case tokIfNot: break;
    default: printf("; %s\n", GetTokenName(tok)); break;
    }
#endif

    switch (tok)
    {
    case tokNumInt:
    case tokNumUint:
      if (gotUnary)
        GenPrintInstr1Operand(X86InstrPush, 0,
                              X86OpRegAWord, 0);
      GenPrintInstr2Operands(X86InstrMov, 0,
                             X86OpRegAWord, 0,
                             X86OpConst, v);
      gotUnary = 1;
      break;

    case tokIdent:
      if (gotUnary)
        GenPrintInstr1Operand(X86InstrPush, 0,
                              X86OpRegAWord, 0);
      GenPrintInstr2Operands(X86InstrMov, 0,
                             X86OpRegAWord, 0,
                             X86OpLabel, v);
      gotUnary = 1;
      break;

    case tokLocalOfs:
      if (gotUnary)
        GenPrintInstr1Operand(X86InstrPush, 0,
                              X86OpRegAWord, 0);
      GenPrintInstr2Operands(X86InstrLea, 0,
                             X86OpRegAWord, 0,
                             X86OpIndLocal, v);
      gotUnary = 1;
      break;

    case ')':
      GenPrintInstr1Operand(X86InstrCall, 0,
                            X86OpRegAWord, 0);
      if (v)
        GenLocalAlloc(-v);
      break;

    case tokUnaryStar:
      GenReadIndirect(v);
      break;

    case tokUnaryPlus:
      break;
    case '~':
      GenPrintInstr1Operand(X86InstrNot, 0,
                            X86OpRegAWord, 0);
      break;
    case tokUnaryMinus:
      GenPrintInstr1Operand(X86InstrNeg, 0,
                            X86OpRegAWord, 0);
      break;

    case '+':
    case '-':
    case '*':
    case '&':
    case '^':
    case '|':
      {
        int instr = GenGetBinaryOperatorInstr(tok);
        GenPrintInstr1Operand(X86InstrPop, 0,
                              X86OpRegBWord, 0);
        if (tok == '-')
          GenPrintInstr2Operands(X86InstrXchg, 0,
                                 X86OpRegAWord, 0,
                                 X86OpRegBWord, 0);
        if (tok != '*')
          GenPrintInstr2Operands(instr, 0,
                                 X86OpRegAWord, 0,
                                 X86OpRegBWord, 0);
        else
          GenPrintInstr1Operand(instr, 0,
                                X86OpRegBWord, 0);
      }
      break;

    case '/':
    case tokUDiv:
    case '%':
    case tokUMod:
      GenPrintInstr1Operand(X86InstrPop, 0,
                            X86OpRegBWord, 0);
      GenPrintInstr2Operands(X86InstrXchg, 0,
                             X86OpRegAWord, 0,
                             X86OpRegBWord, 0);
      if (tok == '/' || tok == '%')
      {
        if (SizeOfWord == 2)
          GenPrintInstrNoOperand(X86InstrCwd);
        else
          GenPrintInstrNoOperand(X86InstrCdq);
        GenPrintInstr1Operand(X86InstrIdiv, 0,
                              X86OpRegBWord, 0);
      }
      else
      {
        GenPrintInstr2Operands(X86InstrMov, 0,
                               X86OpRegDWord, 0,
                               X86OpConst, 0);
        GenPrintInstr1Operand(X86InstrDiv, 0,
                              X86OpRegBWord, 0);
      }
      if (tok == '%' || tok == tokUMod)
        GenPrintInstr2Operands(X86InstrMov, 0,
                               X86OpRegAWord, 0,
                               X86OpRegDWord, 0);
      break;

    case tokLShift:
    case tokRShift:
    case tokURShift:
      {
        int instr = GenGetBinaryOperatorInstr(tok);
        GenPrintInstr1Operand(X86InstrPop, 0,
                              X86OpRegCWord, 0);
        GenPrintInstr2Operands(X86InstrXchg, 0,
                               X86OpRegAWord, 0,
                               X86OpRegCWord, 0);
        GenPrintInstr2Operands(instr, 0,
                               X86OpRegAWord, 0,
                               X86OpRegCByte, 0);
      }
      break;

    case tokInc:
      GenIncDecIndirect(v, tok);
      break;
    case tokDec:
      GenIncDecIndirect(v, tok);
      break;
    case tokPostInc:
      GenPostIncDecIndirect(v, tok);
      break;
    case tokPostDec:
      GenPostIncDecIndirect(v, tok);
      break;

    case tokPostAdd:
    case tokPostSub:
      {
        int instr = GenGetBinaryOperatorInstr(tok);
        GenPrintInstr1Operand(X86InstrPop, 0,
                              X86OpRegBWord, 0);
        GenPrintInstr2Operands(X86InstrMov, 0,
                               X86OpRegCWord, 0,
                               X86OpRegAWord, 0);
        GenPrintInstr2Operands(X86InstrMov, 0,
                               GenSelectByteOrWord(X86OpRegAByteOrWord, v), 0,
                               X86OpIndRegB, 0);
        GenPrintInstr2Operands(instr, 0,
                               X86OpIndRegB, 0,
                               GenSelectByteOrWord(X86OpRegCByteOrWord, v), 0);
        GenExtendRegAIfNeeded(v);
      }
      break;

    case tokAssignAdd:
    case tokAssignSub:
    case tokAssignMul:
    case tokAssignAnd:
    case tokAssignXor:
    case tokAssignOr:
      {
        int instr = GenGetBinaryOperatorInstr(tok);
        GenPrintInstr1Operand(X86InstrPop, 0,
                              X86OpRegBWord, 0);
        if (tok != tokAssignMul)
        {
          GenPrintInstr2Operands(instr, 0,
                                 X86OpIndRegB, 0,
                                 GenSelectByteOrWord(X86OpRegAByteOrWord, v), 0);
          GenPrintInstr2Operands(X86InstrMov, 0,
                                 GenSelectByteOrWord(X86OpRegAByteOrWord, v), 0,
                                 X86OpIndRegB, 0);
        }
        else
        {
          GenPrintInstr1Operand(instr, 0,
                                GenSelectByteOrWord(X86OpIndRegBExplicitByteOrWord, v), 0);
          GenPrintInstr2Operands(X86InstrMov, 0,
                                 X86OpIndRegB, 0,
                                 GenSelectByteOrWord(X86OpRegAByteOrWord, v), 0);
        }
        GenExtendRegAIfNeeded(v);
      }
      break;

    case tokAssignDiv:
    case tokAssignUDiv:
    case tokAssignMod:
    case tokAssignUMod:
      GenPrintInstr1Operand(X86InstrPop, 0,
                            X86OpRegBWord, 0);
      GenPrintInstr2Operands(X86InstrMov, 0,
                             X86OpRegCWord, 0,
                             X86OpRegAWord, 0);
      GenPrintInstr2Operands(X86InstrMov, 0,
                             GenSelectByteOrWord(X86OpRegAByteOrWord, v), 0,
                             X86OpIndRegB, 0);
      GenExtendRegAIfNeeded(v);
      if (tok == tokAssignDiv || tok == tokAssignMod)
      {
        if (SizeOfWord == 2)
          GenPrintInstrNoOperand(X86InstrCwd);
        else
          GenPrintInstrNoOperand(X86InstrCdq);
        GenPrintInstr1Operand(X86InstrIdiv, 0,
                              X86OpRegCWord, 0);
      }
      else
      {
        GenPrintInstr2Operands(X86InstrMov, 0,
                               X86OpRegDWord, 0,
                               X86OpConst, 0);
        GenPrintInstr1Operand(X86InstrDiv, 0,
                              X86OpRegCWord, 0);
      }
      if (tok == tokAssignMod || tok == tokAssignUMod)
        GenPrintInstr2Operands(X86InstrMov, 0,
                               X86OpRegAWord, 0,
                               X86OpRegDWord, 0);
      GenPrintInstr2Operands(X86InstrMov, 0,
                             X86OpIndRegB, 0,
                             GenSelectByteOrWord(X86OpRegAByteOrWord, v), 0);
      GenExtendRegAIfNeeded(v);
      break;

    case tokAssignLSh:
    case tokAssignRSh:
    case tokAssignURSh:
      {
        int instr = GenGetBinaryOperatorInstr(tok);
        GenPrintInstr1Operand(X86InstrPop, 0,
                              X86OpRegBWord, 0);
        GenPrintInstr2Operands(X86InstrMov, 0,
                               X86OpRegCWord, 0,
                               X86OpRegAWord, 0);
        GenPrintInstr2Operands(instr, 0,
                               GenSelectByteOrWord(X86OpIndRegBExplicitByteOrWord, v), 0,
                               X86OpRegCByte, 0);
        GenPrintInstr2Operands(X86InstrMov, 0,
                               GenSelectByteOrWord(X86OpRegAByteOrWord, v), 0,
                               X86OpIndRegB, 0);
        GenExtendRegAIfNeeded(v);
      }
      break;

    case '=':
      GenPrintInstr1Operand(X86InstrPop, 0,
                            X86OpRegBWord, 0);
      GenPrintInstr2Operands(X86InstrMov, 0,
                             X86OpIndRegB, 0,
                             GenSelectByteOrWord(X86OpRegAByteOrWord, v), 0);
      GenExtendRegAIfNeeded(v);
      break;

    case '<':
    case tokULess:
    case '>':
    case tokUGreater:
    case tokLEQ:
    case tokULEQ:
    case tokGEQ:
    case tokUGEQ:
    case tokEQ:
    case tokNEQ:
      GenPrintInstr1Operand(X86InstrPop, 0,
                            X86OpRegBWord, 0);
      GenPrintInstr2Operands(X86InstrCmp, 0,
                             X86OpRegBWord, 0,
                             X86OpRegAWord, 0);
      GenPrintInstr1Operand(X86InstrSetCc, tok,
                            X86OpRegAByte, 0);
      if (SizeOfWord == 2)
        GenPrintInstrNoOperand(X86InstrCbw);
      else
        GenPrintInstr2Operands(X86InstrMovZx, 0,
                               X86OpRegAWord, 0,
                               X86OpRegAByte, 0);
      break;

    case tok_Bool:
      GenPrintInstr2Operands(X86InstrTest, 0,
                             X86OpRegAWord, 0,
                             X86OpRegAWord, 0);
      GenPrintInstr1Operand(X86InstrSetCc, tokNEQ,
                            X86OpRegAByte, 0);
      if (SizeOfWord == 2)
        GenPrintInstrNoOperand(X86InstrCbw);
      else
        GenPrintInstr2Operands(X86InstrMovZx, 0,
                               X86OpRegAWord, 0,
                               X86OpRegAByte, 0);
      break;

    case tokShortCirc:
#ifndef NO_ANNOTATIONS
      if (v >= 0)
        printf("&&\n");
      else
        printf("||\n");
#endif
      if (v >= 0)
        GenJumpIfZero(v); // &&
      else
        GenJumpIfNotZero(-v); // ||
      gotUnary = 0;
      break;

    case tokLogAnd:
      GenNumLabel(v);
      break;
    case tokLogOr:
      GenNumLabel(v);
      break;

    case tokVoid:
      gotUnary = 0;
      break;

    case tokComma:
    case ',':
    case '(':
      break;

    case tokIf:
      GenJumpIfNotZero(stack[i][1]);
      break;
    case tokIfNot:
      GenJumpIfZero(stack[i][1]);
      break;

    default:
      error("Error: Internal Error: GenExpr0(): unexpected token %s\n", GetTokenName(tok));
      break;
    }
  }
}
#endif // #ifndef CG_STACK_BASED

void GenStrData(int insertJump)
{
  int i;

  // insert string literals into the code
  for (i = 0; i < sp; i++)
  {
    int tok = stack[i][0];
    char* p = IdentTable + stack[i][1];
    if (tok == tokIdent && isdigit(*p))
    {
      int label = atoi(p);
      int quot = 0;
      int len;

      p = FindString(label);
      len = *p++;

      if (OutputFormat == FormatFlat)
      {
        if (insertJump)
          GenJumpUncond(label + 1);
      }
      else
      {
        if (insertJump)
          puts(CodeFooter);
        puts(DataHeader);
      }
      GenNumLabel(label);

      GenStartAsciiString();
      while (len--)
      {
        // quote ASCII chars for better readability
        if (*p >= 0x20 && *p <= 0x7E && *p != '\"')
        {
          if (!quot)
          {
            quot = 1;
            printf("\"");
          }
          printf("%c", *p);
        }
        else
        {
          if (quot)
          {
            quot = 0;
            printf("\",");
          }
          printf("%d", *p);
          if (len)
            printf(",");
        }
        p++;
      }
      if (quot)
        printf("\"");
      puts("");

      if (OutputFormat == FormatFlat)
      {
        if (insertJump)
          GenNumLabel(label + 1);
      }
      else
      {
        puts(DataFooter);
        if (insertJump)
          puts(CodeHeader);
      }
    }
  }
}

void GenExpr(void)
{
  GenStrData(1);
#ifndef CG_STACK_BASED
  GenExpr1();
#else
  GenExpr0();
#endif
}
#endif // #ifdef MIPS

// expr.c code

void push2(int v, int v2)
{
  if (sp >= STACK_SIZE) error("Error: expression stack overflow!\n");
  stack[sp][0] = v;
  stack[sp++][1] = v2;
}

void push(int v)
{
  push2(v, 0);
}

int stacktop()
{
  if (sp == 0) error("Error: expression stack underflow!\n");
  return stack[sp - 1][0];
}

int pop2(int* v2)
{
  int v = stacktop();
  *v2 = stack[sp - 1][1];
  sp--;
  return v;
}

int pop()
{
  int v2;
  return pop2(&v2);
}

void ins2(int pos, int v, int v2)
{
  if (sp >= STACK_SIZE) error("Error: expression stack overflow!\n");
  memmove(&stack[pos + 1], &stack[pos], sizeof(stack[0]) * (sp - pos));
  stack[pos][0] = v;
  stack[pos][1] = v2;
  sp++;
}

void ins(int pos, int v)
{
  ins2(pos, v, 0);
}

void del(int pos, int cnt)
{
  memmove(stack[pos],
          stack[pos + cnt],
          sizeof(stack[0]) * (sp - (pos + cnt)));
  sp -= cnt;
}

void pushop2(int v, int v2)
{
  if (opsp >= OPERATOR_STACK_SIZE) error("Error: operator stack overflow!\n");
  opstack[opsp][0] = v;
  opstack[opsp++][1] = v2;
}

void pushop(int v)
{
  pushop2(v, 0);
}

int opstacktop()
{
  if (opsp == 0) error("Error: operator stack underflow!\n");
  return opstack[opsp - 1][0];
}

int popop2(int* v2)
{
  int v = opstacktop();
  *v2 = opstack[opsp - 1][1];
  opsp--;
  return v;
}

int popop()
{
  int v2;
  return popop2(&v2);
}

int isop(int tok)
{
  switch (tok)
  {
  case '!':
  case '~':
  case '&':
  case '*':
  case '/': case '%':
  case '+': case '-':
  case '|': case '^':
  case '<': case '>':
  case '=':
  case tokLogOr: case tokLogAnd:
  case tokEQ: case tokNEQ:
  case tokLEQ: case tokGEQ:
  case tokLShift: case tokRShift:
  case tokInc: case tokDec:
  case tokSizeof:
  case tokAssignMul: case tokAssignDiv: case tokAssignMod:
  case tokAssignAdd: case tokAssignSub:
  case tokAssignLSh: case tokAssignRSh:
  case tokAssignAnd: case tokAssignXor: case tokAssignOr:
  case tokComma:
    return 1;
  default:
    return 0;
  }
}

int isunary(int tok)
{
  return tok == '!' || tok == '~' || tok == tokInc || tok == tokDec || tok == tokSizeof;
}

int preced(int tok)
{
  switch (tok)
  {
  case '*': case '/': case '%': return 12;
  case '+': case '-': return 11;
  case tokLShift: case tokRShift: return 10;
  case '<': case '>': case tokLEQ: case tokGEQ: return 9;
  case tokEQ: case tokNEQ: return 8;
  case '&': return 7;
  case '^': return 6;
  case '|': return 5;
  case tokLogAnd: return 4;
  case tokLogOr: return 3;
  case '=':
  case tokAssignMul: case tokAssignDiv: case tokAssignMod:
  case tokAssignAdd: case tokAssignSub:
  case tokAssignLSh: case tokAssignRSh:
  case tokAssignAnd: case tokAssignXor: case tokAssignOr:
    return 2;
  case tokComma:
    return 1;
  }
  return 0;
}

int precedGEQ(int lfttok, int rhttok)
{
  // DONE: rethink the comma operator as it could be implemented similarly
  // DONE: is this correct:???
  int pl = preced(lfttok);
  int pr = preced(rhttok);
  // assignment is right-associative
  if (pl == 2 && pr >= 2)
    pl = 0;
  return pl >= pr;
}

int expr(int tok, int* gotUnary, int commaSeparator);

int exprUnary(int tok, int* gotUnary, int commaSeparator)
{
  int decl = 0;
  *gotUnary = 0;

  if (isop(tok) && (isunary(tok) || strchr("&*+-", tok) != NULL))
  {
    int lastTok = tok;
    tok = exprUnary(GetToken(), gotUnary, commaSeparator);
    if (!*gotUnary)
      error("exprUnary(): primary expression expected after token %s\n", GetTokenName(lastTok));
    switch (lastTok)
    {
    // DONE: remove all collapsing of all unary operators.
    // It's wrong because type checking must occur before any optimizations.
    // WRONG: DONE: collapse alternating & and * (e.g. "*&*&x" "&*&*x")
    // WRONGISH: DONE: replace prefix ++/-- with +=1/-=1
    case '&':
      push(tokUnaryAnd);
      break;
    case '*':
      push(tokUnaryStar);
      break;
    case '+':
      push(tokUnaryPlus);
      break;
    case '-':
      push(tokUnaryMinus);
      break;
    case '!':
      // replace "!" with "== 0"
      push2(tokNumInt, 0);
      push(tokEQ);
      break;
    default:
      push(lastTok);
      break;
    }
  }
  else
  {
    int inspos = sp;

    if (tok == tokNumInt || tok == tokNumUint)
    {
      push2(tok, GetTokenValueInt());
      *gotUnary = 1;
      tok = GetToken();
    }
    else if (tok == tokLitStr)
    {
      int lbl = (LabelCnt += 2) - 2; // 1 extra label for the jump over the string
      int len, i, id;
      char s[1 + (2 + CHAR_BIT * sizeof lbl) / 3];
      char *p = s + sizeof s;

      // imitate definition: char #[len] = "...";

      AddString(lbl, GetTokenValueString(), len = 1 + GetTokenValueStringLength());

      *--p = '\0';

      i = lbl;
      do
      {
        *--p = '0' + i % 10;
        i /= 10;
      } while (i);

      // DONE: can this break incomplete yet declarations???, e.g.: int x[sizeof("az")][5];
      PushSyntax2(tokIdent, id = AddIdent(p));
      PushSyntax('[');
      PushSyntax2(tokNumUint, len);
      PushSyntax(']');
      PushSyntax(tokChar);

      push2(tokIdent, id);
      *gotUnary = 1;
      tok = GetToken();
    }
    else if (TokenStartsDeclaration(tok, 0))
    {
      int synPtr;
      int lbl = LabelCnt++;
      int i;
      char s[1 + (2 + CHAR_BIT * sizeof lbl) / 3 + sizeof "<something>" - 1];
      char *p = s + sizeof s;

      tok = ParseDecl(tok);
      if (tok != ')')
        error("exprUnary(): ')' expected, unexpected token %s\n", GetTokenName(tok));
      synPtr = FindSymbol("<something>");

      // Rename "<something>" to "<something#>", where # is lbl.
      // This makes the nameless declaration uniquely identifiable by name.

      *--p = '\0';
      *--p = '>';

      i = lbl;
      do
      {
        *--p = '0' + i % 10;
        i /= 10;
      } while (i);

      p -= sizeof "<something>" - 1 - 1;
      memcpy(p, "<something", sizeof "<something" - 1);

      SyntaxStack[synPtr][1] = AddIdent(p);
      push2(tokIdent, SyntaxStack[synPtr][1]);
      decl = *gotUnary = 1;
    }
    else if (tok == tokIdent)
    {
      int synPtr = FindSymbol(GetTokenIdentName());
      if (synPtr < 0)
        error("exprUnary(): undefined identifier '%s'\n", GetTokenIdentName());
      push2(tok, SyntaxStack[synPtr][1]);
      *gotUnary = 1;
      tok = GetToken();
    }
    else if (tok == '(')
    {
      tok = expr(GetToken(), gotUnary, 0);
      if (tok != ')')
        error("exprUnary(): ')' expected, unexpected token %s\n", GetTokenName(tok));
      if (!*gotUnary)
        error("exprUnary(): primary expression expected in '()'\n");
      tok = GetToken();
    }

    while (*gotUnary && !decl)
    {
      // DONE: f(args1)(args2) and the like: need stack order: args2, args1, f, (), ()
      // DONE: reverse the order of evaluation of groups of args in
      //       f(args1)(args2)(args3)
      // DONE: reverse the order of function argument evaluation for variadic functions
      //       we want 1st arg to be the closest to the stack top.
      // DONE: (args)[index] can be repeated interchangeably indefinitely
      // DONE: (expr)() & (expr)[]
      // DONE: [index] can be followed by ++/--, which can be followed by [index] and so on...
      // DONE: postfix ++/-- & differentiate from prefix ++/--

      while (tok == '(' || tok == '[')
      {
        int brak = tok;

        if (brak == '(')
        {
          int acnt = 0;
          ins(inspos, '(');
          for (;;)
          {
            int pos2 = sp;

            tok = GetToken();
            tok = expr(tok, gotUnary, 1);

            // Reverse the order of argument evaluation, which is important for
            // variadic functions like printf():
            // we want 1st arg to be the closest to the stack top.
            // This also reverses the order of evaluation of all groups of
            // arguments.
            while (pos2 < sp)
            {
              // TBD??? not quite efficient
              int v, v2;
              v = pop2(&v2);
              ins2(inspos + 1, v, v2);
              pos2++;
            }

            if (tok == ',')
            {
              if (!*gotUnary)
                error("exprUnary(): primary expression (fxn argument) expected before ','\n");
              acnt++;
              ins(inspos + 1, ','); // helper argument separator (hint for expression evaluator)
              continue; // off to next arg
            }
            if (tok == ')')
            {
              if (acnt && !*gotUnary)
                error("exprUnary(): primary expression (fxn argument) expected between ',' and ')'\n");
              *gotUnary = 1; // don't fail for 0 args in ()
              break; // end of args
            }
            // DONE: think of inserting special arg pseudo tokens for verification purposes
            error("exprUnary(): ',' or ')' expected, unexpected token %s\n", GetTokenName(tok));
          } // endof for(;;) for fxn args
        }
        else // if (brak == '[')
        {
          for (;;)
          {
            tok = GetToken();
            tok = expr(tok, gotUnary, 0);
            if (!*gotUnary)
              error("exprUnary(): primary expression expected in '[]'\n");
            if (tok == ']') break; // end of index
            error("exprUnary(): ']' expected, unexpected token %s\n", GetTokenName(tok));
          }
        }

        tok = GetToken();

        if (brak == '(')
          push(')');
        else
        {
          // TBD??? add implicit casts to size_t of array indicies.
          // E1[E2] -> *(E1 + E2)
          // push('[');
          push('+');
          push(tokUnaryStar);
        }
      } // endof while (tok == '(' || tok == '[')

      if (tok == tokInc || tok == tokDec)
      {
        // WRONG: DONE: replace postfix ++/-- with (+=1)-1/(-=1)+1
        if (tok == tokInc)
          push(tokPostInc);
        else
          push(tokPostDec);
        tok = GetToken();
      }
      else
      {
        break;
      }
    } // endof while (*gotUnary)
  }

  if (tok == ',' && !commaSeparator)
    tok = tokComma;

  return tok;
}

int expr(int tok, int* gotUnary, int commaSeparator)
{
  *gotUnary = 0;

  pushop(tokEof);

  tok = exprUnary(tok, gotUnary, commaSeparator);

  while (tok != tokEof && strchr(",;:)]", tok) == NULL && *gotUnary)
  {
    if (isop(tok) && !isunary(tok))
    {
      int lastTok = tok;

      while (precedGEQ(opstacktop(), tok))
      {
        int v, v2;
        v = popop2(&v2);
        push2(v, v2);
      }

      // here: preced(postacktop()) < preced(tok)
      pushop(tok);

      tok = exprUnary(GetToken(), gotUnary, commaSeparator);
      // DONE: figure out a check to see if exprUnary() fails to add a rhs operand
      if (!*gotUnary)
        error("expr(): primary expression expected after token %s\n", GetTokenName(lastTok));
      continue;
    }

    error("expr(): Unexpected token %s\n", GetTokenName(tok));
  }

  while (opstacktop() != tokEof)
  {
    int v, v2;
    v = popop2(&v2);
    push2(v, v2);
  }

  popop();

  return tok;
}

void decayArray(int* ExprTypeSynPtr, int arithmetic)
{
  // Dacay arrays to pointers to their first elements in
  // binary + and - operators
  if (*ExprTypeSynPtr >= 0 && SyntaxStack[*ExprTypeSynPtr][0] == '[')
  {
    while (SyntaxStack[*ExprTypeSynPtr][0] != ']')
      ++*ExprTypeSynPtr;
    ++*ExprTypeSynPtr;
    *ExprTypeSynPtr = -*ExprTypeSynPtr;
  }
  // Also, to simplify code, return all other pointers as
  // negative expression stack syntax indices/pointers
  else if (*ExprTypeSynPtr >= 0 && SyntaxStack[*ExprTypeSynPtr][0] == '*')
  {
    ++*ExprTypeSynPtr;
    *ExprTypeSynPtr = -*ExprTypeSynPtr;
  }

  // DONE: disallow arithmetic on pointers to void
  // DONE: disallow function pointers
  if (arithmetic)
  {
    if (*ExprTypeSynPtr < 0)
    {
      if (SyntaxStack[-*ExprTypeSynPtr][0] == tokVoid)
        error("Error: decayArray(): cannot do pointer arithmetic on a pointer to 'void'\n");
      if (SyntaxStack[-*ExprTypeSynPtr][0] == '(')
        error("Error: decayArray(): cannot do pointer arithmetic on a pointer to a function\n");
    }
    else
    {
      if (SyntaxStack[*ExprTypeSynPtr][0] == '(')
        error("Error: decayArray(): cannot do arithmetic on a function\n");
    }
  }
}

void nonVoidTypeCheck(int ExprTypeSynPtr, int tok)
{
  if (ExprTypeSynPtr >= 0 && SyntaxStack[ExprTypeSynPtr][0] == tokVoid)
    error("Error: nonVoidTypeCheck(): unexpected operand type 'void' for operator '%s'\n",
          GetTokenName(tok));
}

void numericTypeCheck(int ExprTypeSynPtr, int tok)
{
  if (ExprTypeSynPtr >= 0 &&
      (SyntaxStack[ExprTypeSynPtr][0] == tokChar ||
       SyntaxStack[ExprTypeSynPtr][0] == tokInt ||
       SyntaxStack[ExprTypeSynPtr][0] == tokUnsigned))
    return;
  error("Error: numericTypeCheck(): unexpected operand type for operator '%s', numeric type expected\n",
        GetTokenName(tok));
}

void promoteType(int* ExprTypeSynPtr, int* TheOtherExprTypeSynPtr)
{
  // chars must be promoted to ints in expressions as the very first thing
  if (*ExprTypeSynPtr >= 0 && SyntaxStack[*ExprTypeSynPtr][0] == tokChar)
    *ExprTypeSynPtr = SymIntSynPtr;

  // ints must be converted to unsigned ints if they are used in binary
  // operators whose other operand is unsigned int (except <<,>>,<<=,>>=)
  if (*ExprTypeSynPtr >= 0 && SyntaxStack[*ExprTypeSynPtr][0] == tokInt &&
      *TheOtherExprTypeSynPtr >= 0 && SyntaxStack[*TheOtherExprTypeSynPtr][0] == tokUnsigned)
    *ExprTypeSynPtr = SymUintSynPtr;
}

int GetFxnInfo(int ExprTypeSynPtr, int* MinParams, int* MaxParams, int* ReturnExprTypeSynPtr)
{
  int ptr = 0;

  *MaxParams = *MinParams = 0;

  if (ExprTypeSynPtr < 0)
  {
    ptr = 1;
    ExprTypeSynPtr = -ExprTypeSynPtr;
  }

  while (SyntaxStack[ExprTypeSynPtr][0] == tokIdent || SyntaxStack[ExprTypeSynPtr][0] == tokLocalOfs)
    ExprTypeSynPtr++;

  if (!(SyntaxStack[ExprTypeSynPtr][0] == '(' ||
        (!ptr && SyntaxStack[ExprTypeSynPtr][0] == '*' && SyntaxStack[ExprTypeSynPtr + 1][0] == '(')))
    return 0;

  // DONE: return syntax pointer to the function's return type

  // Count params

  while (SyntaxStack[ExprTypeSynPtr][0] != '(')
    ExprTypeSynPtr++;
  ExprTypeSynPtr++;

  if (SyntaxStack[ExprTypeSynPtr][0] == ')')
  {
    // "fxn()": unspecified parameters, so, there can be any number of them
    *MaxParams = 32767; // INT_MAX;
    *ReturnExprTypeSynPtr = ExprTypeSynPtr + 1;
    return 1;
  }

  if (SyntaxStack[ExprTypeSynPtr + 1][0] == tokVoid)
  {
    // "fxn(void)": 0 parameters
    *ReturnExprTypeSynPtr = ExprTypeSynPtr + 3;
    return 1;
  }

  for (;;)
  {
    int tok = SyntaxStack[ExprTypeSynPtr][0];

    if (tok == tokIdent)
    {
      if (SyntaxStack[ExprTypeSynPtr + 1][0] != tokEllipsis)
      {
        ++*MinParams;
        ++*MaxParams;
      }
      else
      {
        *MaxParams = 32767; // INT_MAX;
      }
    }
    else if (tok == '(')
    {
      // skip parameters in parameters
      int c = 1;
      while (c && ExprTypeSynPtr < SyntaxStackCnt)
      {
        tok = SyntaxStack[++ExprTypeSynPtr][0];
        c += (tok == '(') - (tok == ')');
      }
    }
    else if (tok == ')')
    {
      ExprTypeSynPtr++;
      break;
    }

    ExprTypeSynPtr++;
  }

  // get the function's return type
  *ReturnExprTypeSynPtr = ExprTypeSynPtr;

  return 1;
}

void simplifyConstExpr(int val, int isConst, int* ExprTypeSynPtr, int top, int bottom)
{
  if (!isConst || stack[top][0] == tokNumInt || stack[top][0] == tokNumUint)
    return;

  if (SyntaxStack[*ExprTypeSynPtr][0] == tokUnsigned)
    stack[top][0] = tokNumUint;
  else
    stack[top][0] = tokNumInt;
  stack[top][1] = val;

  del(bottom, top - bottom);
}

// DONE: sizeof(type)
// DONE: "sizeof expr"
// DONE: constant expressions
// DONE: collapse constant subexpressions into constants
int exprval(int* idx, int* ExprTypeSynPtr, int* ConstExpr)
{
  int tok;
  int s;
  int RightExprTypeSynPtr;
  int oldIdxRight;
  int oldSpRight;
  int constExpr[2];

  if (*idx < 0)
    error("exprval(): idx < 0\n");

  tok = stack[*idx][0];
  s = stack[*idx][1];

  --*idx;

  oldIdxRight = *idx;
  oldSpRight = sp;

  switch (tok)
  {
  // Constants
  case tokNumInt:
    // return the constant's type: int
    *ExprTypeSynPtr = SymIntSynPtr;
    *ConstExpr = 1;
    break;
  case tokNumUint:
    // return the constant's type: unsigned int
    *ExprTypeSynPtr = SymUintSynPtr;
    *ConstExpr = 1;
    break;

  // Identifiers
  case tokIdent:
    {
      int synPtr = FindSymbol(IdentTable + s);
      int type = SymType(synPtr);

      if (!strncmp(IdentTable + SyntaxStack[synPtr][1], "<something", sizeof "<something>" - 1 - 1) &&
          ((*idx + 2 >= sp) || stack[*idx + 2][0] != tokSizeof))
        error("Error: exprval(): unexpected type declaration\n");

      if (type == SymLocalVar || type == SymLocalArr)
      {
        // replace local variables/arrays with their local addresses
        // (global variables/arrays' addresses are their names)
        stack[*idx + 1][0] = tokLocalOfs;
        stack[*idx + 1][1] = SyntaxStack[synPtr + 1][1];
      }
      if (type == SymLocalVar || type == SymGlobalVar)
      {
        // add implicit dereferences for local/global variables
        ins2(*idx + 2, tokUnaryStar, GetDeclSize(synPtr));
      }

      // return the identifier's type
      while (SyntaxStack[synPtr][0] == tokIdent || SyntaxStack[synPtr][0] == tokLocalOfs)
        synPtr++;
      *ExprTypeSynPtr = synPtr;
    }
    *ConstExpr = 0;
    break;

  // sizeof operator
  case tokSizeof:
    s = exprval(idx, ExprTypeSynPtr, ConstExpr);

    if (*ExprTypeSynPtr >= 0)
      s = GetDeclSize(*ExprTypeSynPtr);
    else
      s = SizeOfWord;
    if (s == 0)
      error("Error: exprval(): sizeof of incomplete type (e.g. 'void')\n");

    // replace sizeof with its numeric value
    stack[oldIdxRight + 1 - (oldSpRight - sp)][0] = tokNumUint;
    stack[oldIdxRight + 1 - (oldSpRight - sp)][1] = s;

    // remove the sizeof's subexpression
    del(*idx + 1, oldIdxRight - (oldSpRight - sp) - *idx);

    *ExprTypeSynPtr = SymUintSynPtr;
    *ConstExpr = 1;
    break;

  // Address unary operator
  case tokUnaryAnd:
    exprval(idx, ExprTypeSynPtr, ConstExpr);

    if (*ExprTypeSynPtr >= 0 && SyntaxStack[*ExprTypeSynPtr][0] == '[')
    {
      // convert an array into a pointer to the array,
      // remove the reference
      *ExprTypeSynPtr = -*ExprTypeSynPtr;
      del(oldIdxRight + 1 - (oldSpRight - sp), 1);
    }
    else if (*ExprTypeSynPtr >= 0 && SyntaxStack[*ExprTypeSynPtr][0] == '(')
    {
      // convert a function into a pointer to the function,
      // remove the reference
      *ExprTypeSynPtr = -*ExprTypeSynPtr;
      del(oldIdxRight + 1 - (oldSpRight - sp), 1);
    }
    else if (*ExprTypeSynPtr >= 0 &&
             oldIdxRight - (oldSpRight - sp) >= 0 &&
             stack[oldIdxRight - (oldSpRight - sp)][0] == tokUnaryStar)
    {
      // it's an lvalue (with implicit or explicit dereference),
      // convert it into its address,
      // collapse/remove the reference and the dereference
      *ExprTypeSynPtr = -*ExprTypeSynPtr;
      del(oldIdxRight - (oldSpRight - sp), 2);
    }
    else
      error("Error: exprval(): lvalue expected after '&'\n");

    *ConstExpr = 0;
    break;

  // Indirection unary operator
  case tokUnaryStar:
    exprval(idx, ExprTypeSynPtr, ConstExpr);

    if (*ExprTypeSynPtr < 0 || SyntaxStack[*ExprTypeSynPtr][0] == '*')
    {
      // type is a pointer to something,
      // transform it into that something
      if (*ExprTypeSynPtr < 0)
        *ExprTypeSynPtr = -*ExprTypeSynPtr;
      else
        ++*ExprTypeSynPtr;
      if (SyntaxStack[*ExprTypeSynPtr][0] == tokVoid)
        error("Error: exprval(): cannot dereference a pointer to 'void'\n");
      // remove the dereference if that something is an array
      if (SyntaxStack[*ExprTypeSynPtr][0] == '[')
        del(oldIdxRight + 1 - (oldSpRight - sp), 1);
      // remove the dereference if that something is a function
      if (SyntaxStack[*ExprTypeSynPtr][0] == '(')
        del(oldIdxRight + 1 - (oldSpRight - sp), 1);
      // else add dereference size in bytes
      else
        stack[oldIdxRight + 1 - (oldSpRight - sp)][1] = GetDeclSize(*ExprTypeSynPtr);
    }
    else if (SyntaxStack[*ExprTypeSynPtr][0] == '[')
    {
      // type is an array,
      // transform it into the array's first element
      // (a subarray, if type is a multidimensional array)
      while (SyntaxStack[*ExprTypeSynPtr][0] != ']')
        ++*ExprTypeSynPtr;
      ++*ExprTypeSynPtr;
      // remove the dereference if that element is an array
      if (SyntaxStack[*ExprTypeSynPtr][0] == '[')
        del(oldIdxRight + 1 - (oldSpRight - sp), 1);
      // else add dereference size in bytes
      else
        stack[oldIdxRight + 1 - (oldSpRight - sp)][1] = GetDeclSize(*ExprTypeSynPtr);
    }
    else
      error("Error: exprval(): pointer/array expected before '*' or '[]'\n");

    *ConstExpr = 0;
    break;

  // Additive binary operators
  case '+':
  case '-':
  // WRONGISH: DONE: replace prefix ++/-- with +=1/-=1
  // WRONG: DONE: replace postfix ++/-- with (+=1)-1/(-=1)+1
    {
      int ptrmask;
      int oldIdxLeft, oldSpLeft;
      int sl, sr;
      int incSize;
      sr = exprval(idx, &RightExprTypeSynPtr, &constExpr[1]);
      oldIdxLeft = *idx;
      oldSpLeft = sp;
      sl = exprval(idx, ExprTypeSynPtr, &constExpr[0]);

      if (tok == '+')
        s = uint2int(sl + 0u + sr);
      else
        s = uint2int(sl + 0u - sr);

      nonVoidTypeCheck(RightExprTypeSynPtr, tok);
      nonVoidTypeCheck(*ExprTypeSynPtr, tok);

      // Decay arrays to pointers to their first elements
      decayArray(&RightExprTypeSynPtr, 1);
      decayArray(ExprTypeSynPtr, 1);

      ptrmask = (RightExprTypeSynPtr < 0) + (*ExprTypeSynPtr < 0) * 2;

      // DONE: index/subscript scaling
      if (ptrmask == 1 && tok == '+') // right-hand expression
      {
        incSize = GetDeclSize(-RightExprTypeSynPtr);

        if (constExpr[0])
        {
          stack[oldIdxLeft - (oldSpLeft - sp)][1] *= incSize;
          s = sl * incSize + sr;
        }
        else if (incSize != 1)
        {
          ins2(oldIdxLeft + 1 - (oldSpLeft - sp), tokNumInt, incSize);
          ins(oldIdxLeft + 1 - (oldSpLeft - sp), '*');
        }

        *ExprTypeSynPtr = RightExprTypeSynPtr;
      }
      else if (ptrmask == 2) // left-hand expression
      {
        incSize = GetDeclSize(-*ExprTypeSynPtr);
        if (constExpr[1])
        {
          stack[oldIdxRight - (oldSpRight - sp)][1] *= incSize;
          s = sl + sr * incSize * ((tok == '+') - (tok == '-'));
        }
        else if (incSize != 1)
        {
          ins2(oldIdxRight + 1 - (oldSpRight - sp), tokNumInt, incSize);
          ins(oldIdxRight + 1 - (oldSpRight - sp), '*');
        }
      }
      else if (ptrmask == 3 && tok == '-')
      {
        incSize = GetDeclSize(-*ExprTypeSynPtr);
        // TBD!!! "ptr1-ptr2": better pointer compatibility test needed
        if (incSize != GetDeclSize(-RightExprTypeSynPtr))
          error("Error: exprval(): incompatible pointers\n");
        if (incSize != 1)
        {
          ins2(oldIdxRight + 2 - (oldSpRight - sp), tokNumInt, incSize);
          ins(oldIdxRight + 2 - (oldSpRight - sp), '/');
        }
        *ExprTypeSynPtr = SymIntSynPtr;
      }
      else if (ptrmask)
        error("Error: exprval(): invalid combination of operands for '+' or '-'\n");

      // Promote the result from char to int (and from int to unsigned) if necessary
      promoteType(ExprTypeSynPtr, &RightExprTypeSynPtr);

      *ConstExpr = constExpr[0] && constExpr[1] && canSimplify;
      simplifyConstExpr(s, *ConstExpr, ExprTypeSynPtr, oldIdxRight + 1 - (oldSpRight - sp), *idx + 1);
    }
    break;

  // Prefix/postfix increment/decrement unary operators
  case tokInc:
  case tokDec:
  case tokPostInc:
  case tokPostDec:
    {
      int incSize = 1;
      int inc = tok == tokInc || tok == tokPostInc;
      int post = tok == tokPostInc || tok == tokPostDec;
      int opSize;

      exprval(idx, ExprTypeSynPtr, ConstExpr);

      nonVoidTypeCheck(*ExprTypeSynPtr, tok);

      decayArray(ExprTypeSynPtr, 1);

      // lvalue check for ++, --
      if (!(oldIdxRight - (oldSpRight - sp) >= 0 &&
            stack[oldIdxRight - (oldSpRight - sp)][0] == tokUnaryStar))
        error("Error: exprval(): lvalue expected for '++' or '--'\n");

      // "remove" the lvalue dereference as we don't need
      // to read the value and forget its location. We need to
      // keep the lvalue location.
      // Remember the operand size.
      opSize = stack[oldIdxRight - (oldSpRight - sp)][1];
      del(oldIdxRight - (oldSpRight - sp), 1);

      if (*ExprTypeSynPtr < 0)
        incSize = GetDeclSize(-*ExprTypeSynPtr);

      if (incSize == 1)
      {
        // store the operand size in the operator
        stack[oldIdxRight + 1 - (oldSpRight - sp)][1] = opSize;
      }
      else
      {
        // replace ++/-- with "postfix" +=/-= incSize when incSize != 1
        if (inc)
        {
          if (post)
            stack[oldIdxRight + 1 - (oldSpRight - sp)][0] = tokPostAdd;
          else
            stack[oldIdxRight + 1 - (oldSpRight - sp)][0] = tokAssignAdd;
        }
        else
        {
          if (post)
            stack[oldIdxRight + 1 - (oldSpRight - sp)][0] = tokPostSub;
          else
            stack[oldIdxRight + 1 - (oldSpRight - sp)][0] = tokAssignSub;
        }
        // store the operand size in the operator
        stack[oldIdxRight + 1 - (oldSpRight - sp)][1] = opSize;

        ins2(oldIdxRight + 1 - (oldSpRight - sp), tokNumInt, incSize);
      }

      *ConstExpr = 0;
    }
    break;

  // Assignment binary operator
  case '=':
    {
      int oldIdxLeft, oldSpLeft;
      int opSize;

      exprval(idx, &RightExprTypeSynPtr, ConstExpr);
      oldIdxLeft = *idx;
      oldSpLeft = sp;
      exprval(idx, ExprTypeSynPtr, ConstExpr);

      nonVoidTypeCheck(RightExprTypeSynPtr, tok);
      nonVoidTypeCheck(*ExprTypeSynPtr, tok);

      decayArray(&RightExprTypeSynPtr, 0);
      decayArray(ExprTypeSynPtr, 0);

      if (!(oldIdxLeft - (oldSpLeft - sp) >= 0 &&
            stack[oldIdxLeft - (oldSpLeft - sp)][0] == tokUnaryStar))
        error("Error: exprval(): lvalue expected before '='\n");

      // "remove" the lvalue dereference as we don't need
      // to read the value and forget its location. We need to
      // keep the lvalue location.
      opSize = stack[oldIdxLeft - (oldSpLeft - sp)][1];
      // store the operand size in the operator
      stack[oldIdxRight + 1 - (oldSpRight - sp)][1] = opSize;
      del(oldIdxLeft - (oldSpLeft - sp), 1);

      *ConstExpr = 0;
    }
    break;

  // DONE: other assignment operators

  // Arithmetic and bitwise unary operators
  case '~':
  case tokUnaryPlus:
  case tokUnaryMinus:
    s = exprval(idx, ExprTypeSynPtr, ConstExpr);
    nonVoidTypeCheck(*ExprTypeSynPtr, tok);
    numericTypeCheck(*ExprTypeSynPtr, tok);
    switch (tok)
    {
    case '~':           s = ~s; break;
    case tokUnaryPlus:  s = +s; break;
    case tokUnaryMinus: s = uint2int(~(s - 1u)); break;
    }
    promoteType(ExprTypeSynPtr, ExprTypeSynPtr);
    *ConstExpr &= canSimplify;
    simplifyConstExpr(s, *ConstExpr, ExprTypeSynPtr, oldIdxRight + 1 - (oldSpRight - sp), *idx + 1);
    break;

  // Arithmetic and bitwise binary operators
  case '*':
  case '/':
  case '%':
  case tokLShift:
  case tokRShift:
  case '&':
  case '^':
  case '|':
    {
      // int oldIdxLeft, oldSpLeft;
      int sr, sl;
      int Unsigned;
      sr = exprval(idx, &RightExprTypeSynPtr, &constExpr[1]);
      // oldIdxLeft = *idx;
      // oldSpLeft = sp;
      sl = exprval(idx, ExprTypeSynPtr, &constExpr[0]);

      nonVoidTypeCheck(RightExprTypeSynPtr, tok);
      nonVoidTypeCheck(*ExprTypeSynPtr, tok);

      numericTypeCheck(RightExprTypeSynPtr, tok);
      numericTypeCheck(*ExprTypeSynPtr, tok);

      *ConstExpr = constExpr[0] && constExpr[1] && canSimplify;

      Unsigned = SyntaxStack[*ExprTypeSynPtr][0] == tokUnsigned || SyntaxStack[RightExprTypeSynPtr][0] == tokUnsigned;

      switch (tok)
      {
      // DONE: check for division overflows
      case '/':
      case '%':
        if (*ConstExpr)
        {
          if (!Unsigned)
          {
            sl = truncInt(sl);
            sr = truncInt(sr);
            if (sr == 0 || (sl == INT_MIN && sr == -1) || sl / sr != truncInt(sl / sr))
              error("Error: exprval(): division overflow\n");
            if (tok == '/')
              sl /= sr;
            else
              sl %= sr;
          }
          else
          {
            if (truncUint(sr) == 0)
              error("Error: exprval(): division overflow\n");
            if (tok == '/')
              sl = uint2int(truncUint(sl) / truncUint(sr));
            else
              sl = uint2int(truncUint(sl) % truncUint(sr));
          }
        }

        if (Unsigned)
        {
          if (tok == '/')
            stack[oldIdxRight + 1 - (oldSpRight - sp)][0] = tokUDiv;
          else
            stack[oldIdxRight + 1 - (oldSpRight - sp)][0] = tokUMod;
        }
        break;

      case '*':
        sl = uint2int((sl + 0u) * sr);
        break;

      case tokLShift:
      case tokRShift:
        if (*ConstExpr)
        {
          if (SyntaxStack[RightExprTypeSynPtr][0] != tokUnsigned)
            sr = truncInt(sr);
          else
            sr = uint2int(truncUint(sr));
          // can't shift by a negative count and by a count exceeding
          // the number of bits in int
          if ((SyntaxStack[RightExprTypeSynPtr][0] != tokUnsigned && sr < 0) ||
              (sr + 0u) >= CHAR_BIT * sizeof(int) ||
              (sr + 0u) >= 8u * SizeOfWord)
            error("Error: exprval(): Invalid shift count\n");
          if (tok == tokLShift)
          {
            // left shift is the same for signed and unsigned ints
            sl = uint2int((sl + 0u) << sr);
          }
          else
          {
            if (SyntaxStack[*ExprTypeSynPtr][0] == tokUnsigned)
            {
              // right shift for unsigned ints
              sl = uint2int(truncUint(sl) >> sr);
            }
            else if (sr)
            {
              // right shift for signed ints is arithmetic, sign-bit-preserving
              // don't depend on the compiler's implementation, do it "manually"
              sl = truncInt(sl);
              sl = uint2int((truncUint(sl) >> sr) |
                            ((sl < 0) * (~0u << (8 * SizeOfWord - sr))));
            }
          }
        }

        if (SyntaxStack[*ExprTypeSynPtr][0] == tokUnsigned && tok == tokRShift)
            stack[oldIdxRight + 1 - (oldSpRight - sp)][0] = tokURShift;

        // ignore RightExprTypeSynPtr for the purpose of promotion/conversion of the result of <</>>
        RightExprTypeSynPtr = SymIntSynPtr;
        break;

      case '&': sl &= sr; break;
      case '^': sl ^= sr; break;
      case '|': sl |= sr; break;
      }

      s = sl;
      promoteType(ExprTypeSynPtr, &RightExprTypeSynPtr);
      simplifyConstExpr(s, *ConstExpr, ExprTypeSynPtr, oldIdxRight + 1 - (oldSpRight - sp), *idx + 1);
    }
    break;

  // Relational binary operators
  // DONE: add (sub)tokens for unsigned >, >=, <, <= for pointers
  case '<':
  case '>':
  case tokLEQ:
  case tokGEQ:
  case tokEQ:
  case tokNEQ:
    {
      int ptrmask;
      int sr, sl;
      int Unsigned;
      sr = exprval(idx, &RightExprTypeSynPtr, &constExpr[1]);
      sl = exprval(idx, ExprTypeSynPtr, &constExpr[0]);

      nonVoidTypeCheck(RightExprTypeSynPtr, tok);
      nonVoidTypeCheck(*ExprTypeSynPtr, tok);

      decayArray(&RightExprTypeSynPtr, 0);
      decayArray(ExprTypeSynPtr, 0);

      ptrmask = (RightExprTypeSynPtr < 0) + (*ExprTypeSynPtr < 0) * 2;

      // Disallow >, <, >=, <= between a pointer and a number
      if (ptrmask >= 1 && ptrmask <= 2 &&
          tok != tokEQ && tok != tokNEQ)
        error("Error: exprval(): Invalid/unsupported combination of compared operands\n");

      *ConstExpr = constExpr[0] && constExpr[1] && canSimplify;

      Unsigned = !ptrmask &&
        (SyntaxStack[*ExprTypeSynPtr][0] == tokUnsigned || SyntaxStack[RightExprTypeSynPtr][0] == tokUnsigned);

      if (*ConstExpr)
      {
        if (!Unsigned)
        {
          sl = truncInt(sl);
          sr = truncInt(sr);
          switch (tok)
          {
          case '<':    sl = sl <  sr; break;
          case '>':    sl = sl >  sr; break;
          case tokLEQ: sl = sl <= sr; break;
          case tokGEQ: sl = sl >= sr; break;
          case tokEQ:  sl = sl == sr; break;
          case tokNEQ: sl = sl != sr; break;
          }
        }
        else
        {
          sl = uint2int(truncUint(sl));
          sr = uint2int(truncUint(sr));
          switch (tok)
          {
          case '<':    sl = sl + 0u <  sr + 0u; break;
          case '>':    sl = sl + 0u >  sr + 0u; break;
          case tokLEQ: sl = sl + 0u <= sr + 0u; break;
          case tokGEQ: sl = sl + 0u >= sr + 0u; break;
          case tokEQ:  sl = sl == sr; break;
          case tokNEQ: sl = sl != sr; break;
          }
        }
      }

      if (ptrmask || Unsigned)
      {
        // Pointer comparison should be unsigned
        int t = tok;
        switch (tok)
        {
        case '<': t = tokULess; break;
        case '>': t = tokUGreater; break;
        case tokLEQ: t = tokULEQ; break;
        case tokGEQ: t = tokUGEQ; break;
        }
        if (t != tok)
          stack[oldIdxRight + 1 - (oldSpRight - sp)][0] = t;
      }

      s = sl;
      *ExprTypeSynPtr = SymIntSynPtr;
      simplifyConstExpr(s, *ConstExpr, ExprTypeSynPtr, oldIdxRight + 1 - (oldSpRight - sp), *idx + 1);
    }
    break;

  // implicit pseudo-conversion to _Bool of operands of && and ||
  case tok_Bool:
    s = exprval(idx, ExprTypeSynPtr, ConstExpr) != 0;
    nonVoidTypeCheck(*ExprTypeSynPtr, tok);
    decayArray(ExprTypeSynPtr, 0);
    *ExprTypeSynPtr = SymIntSynPtr;
    *ConstExpr &= canSimplify;
    simplifyConstExpr(s, *ConstExpr, ExprTypeSynPtr, oldIdxRight + 1 - (oldSpRight - sp), *idx + 1);
    break;

  // Logical binary operators
  case tokLogAnd: // DONE: short-circuit
  case tokLogOr: // DONE: short-circuit
    {
      int sr, sl;

      // DONE: think of pushing a special short-circuit (jump-to) token
      // to skip the rhs operand evaluation in && and ||
      // DONE: add implicit "casts to _Bool" of && and || operands,
      // do the same for control statements of if() while() and for(;;).

      int sc = LabelCnt++;
      // tag the logical operator as a numbered short-circuit jump target
      stack[*idx + 1][1] = sc;

      // insert "!= 0" for right-hand operand
      switch (stack[*idx][0])
      {
      case '<':
      case tokULess:
      case '>':
      case tokUGreater:
      case tokLEQ:
      case tokULEQ:
      case tokGEQ:
      case tokUGEQ:
      case tokEQ:
      case tokNEQ:
        break;
      default:
        ins(++*idx, tok_Bool);
        break;
      }

      sr = exprval(idx, &RightExprTypeSynPtr, &constExpr[1]);

      // insert a reference to the short-circuit jump target
      if (tok == tokLogAnd)
        ins2(++*idx, tokShortCirc, sc);
      else
        ins2(++*idx, tokShortCirc, -sc);
      // insert "!= 0" for left-hand operand
      switch (stack[*idx - 1][0])
      {
      case '<':
      case tokULess:
      case '>':
      case tokUGreater:
      case tokLEQ:
      case tokULEQ:
      case tokGEQ:
      case tokUGEQ:
      case tokEQ:
      case tokNEQ:
        --*idx;
        break;
      default:
        ins(*idx, tok_Bool);
        break;
      }

      sl = exprval(idx, ExprTypeSynPtr, &constExpr[0]);

      if (tok == tokLogAnd)
        sl = sl && sr;
      else
        sl = sl || sr;

      s = sl;
      *ExprTypeSynPtr = SymIntSynPtr;
      *ConstExpr = constExpr[0] && constExpr[1] && canSimplify;
      simplifyConstExpr(s, *ConstExpr, ExprTypeSynPtr, oldIdxRight + 1 - (oldSpRight - sp), *idx + 1);
    }
    break;

  // Function call
  case ')':
    {
      int tmpSynPtr, c;
      int minParams, maxParams;
      exprval(idx, ExprTypeSynPtr, ConstExpr);

      if (!GetFxnInfo(*ExprTypeSynPtr, &minParams, &maxParams, ExprTypeSynPtr))
        error("exprval(): function or function pointer expected\n");

      // DONE: validate the number of function parameters
      // TBD??? warnings/errors on int<->pointer substitution in params

      // evaluate function parameters
      c = 0;
      while (stack[*idx][0] != '(')
      {
        // add a comma after the first (last to be pushed) parameter,
        // so all parameters can be pushed whenever a comma is encountered
        if (!c)
          ins(*idx + 1, ',');

        exprval(idx, &tmpSynPtr, ConstExpr);

        if (tmpSynPtr >= 0 && SyntaxStack[tmpSynPtr][0] == tokVoid)
          error("exprval(): function parameters cannot be of type 'void'\n");

        if (++c > maxParams)
          error("exprval(): too many function parameters\n");

        if (stack[*idx][0] == ',')
          --*idx;
      }
      --*idx;

      if (c < minParams)
        error("exprval(): too few function parameters\n");

      // store the cumulative parameter size in the function call operators
      stack[1 + *idx][1] = stack[oldIdxRight + 1 - (oldSpRight - sp)][1] = c * SizeOfWord;

      *ConstExpr = 0;
    }
    break;

  case tokComma:
    {
      int oldIdxLeft, oldSpLeft;
      s = exprval(idx, &RightExprTypeSynPtr, &constExpr[1]);
      oldIdxLeft = *idx;
      oldSpLeft = sp;

      // Signify uselessness of the result of the left operand's value
      ins(*idx + 1, tokVoid);

      exprval(idx, ExprTypeSynPtr, &constExpr[0]);
      *ConstExpr = constExpr[0] && constExpr[1];
      *ExprTypeSynPtr = RightExprTypeSynPtr;
      if (*ConstExpr)
      {
        // both subexprs are const, remove both and comma
        simplifyConstExpr(s, *ConstExpr, ExprTypeSynPtr, oldIdxRight + 1 - (oldSpRight - sp), *idx + 1);
      }
      else if (constExpr[0])
      {
        // only left subexpr is const, remove it and comma
        del(*idx + 1, oldIdxLeft - (oldSpLeft - sp) - *idx);
        del(oldIdxRight + 1 - (oldSpRight - sp), 1);
      }
    }
    break;

  case tokAssignMul: case tokAssignDiv: case tokAssignMod:
  case tokAssignAdd: case tokAssignSub:
  case tokAssignLSh: case tokAssignRSh:
  case tokAssignAnd: case tokAssignXor: case tokAssignOr:
    {
      int ptrmask;
      int oldIdxLeft, oldSpLeft;
      int incSize;
      int opSize;
      int Unsigned;
      exprval(idx, &RightExprTypeSynPtr, &constExpr[1]);
      oldIdxLeft = *idx;
      oldSpLeft = sp;
      exprval(idx, ExprTypeSynPtr, &constExpr[0]);

      nonVoidTypeCheck(RightExprTypeSynPtr, tok);
      nonVoidTypeCheck(*ExprTypeSynPtr, tok);

      decayArray(&RightExprTypeSynPtr, 1);
      decayArray(ExprTypeSynPtr, 1);

      if (!(oldIdxLeft - (oldSpLeft - sp) >= 0 &&
            stack[oldIdxLeft - (oldSpLeft - sp)][0] == tokUnaryStar))
        error("Error: exprval(): lvalue expected before %s\n", GetTokenName(tok));

      // "remove" the lvalue dereference as we don't need
      // to read the value and forget its location. We need to
      // keep the lvalue location.
      opSize = stack[oldIdxLeft - (oldSpLeft - sp)][1];
      // store the operand size in the operator
      stack[oldIdxRight + 1 - (oldSpRight - sp)][1] = opSize;
      del(oldIdxLeft - (oldSpLeft - sp), 1);

      ptrmask = (RightExprTypeSynPtr < 0) + (*ExprTypeSynPtr < 0) * 2;

      Unsigned = !ptrmask &&
        (SyntaxStack[*ExprTypeSynPtr][0] == tokUnsigned || SyntaxStack[RightExprTypeSynPtr][0] == tokUnsigned);

      if (tok != tokAssignAdd && tok != tokAssignSub)
      {
        if (ptrmask)
          error("Error: exprval(): invalid combination of operands for %s\n", GetTokenName(tok));
      }
      else
      {
        // No pointer to the right of += and -=
        if (ptrmask & 1)
          error("Error: exprval(): invalid combination of operands for %s\n", GetTokenName(tok));
      }

      // TBD??? replace +=/-= with prefix ++/-- if incSize == 1
      if (ptrmask == 2) // left-hand expression
      {
        incSize = GetDeclSize(-*ExprTypeSynPtr);
        if (constExpr[1])
        {
          stack[oldIdxRight - (oldSpRight - sp)][1] *= incSize;
        }
        else if (incSize != 1)
        {
          ins2(oldIdxRight + 1 - (oldSpRight - sp), tokNumInt, incSize);
          ins(oldIdxRight + 1 - (oldSpRight - sp), '*');
        }
      }
      else if (Unsigned)
      {
        int t = tok;
        switch (tok)
        {
        case tokAssignDiv: t = tokAssignUDiv; break;
        case tokAssignMod: t = tokAssignUMod; break;
        case tokAssignRSh: t = tokAssignURSh; break;
        }
        if (t != tok)
          stack[oldIdxRight + 1 - (oldSpRight - sp)][0] = t;
      }

      *ConstExpr = 0;
    }
    break;

  default:
    error("exprval(): Unexpected token %s\n", GetTokenName(tok));
  }

  return s;
}

int ParseExpr(int tok, int* GotUnary, int* ExprTypeSynPtr, int* ConstExpr, int* ConstVal, int commaSeparator)
{
  *ConstVal = *ConstExpr = 0;
  *ExprTypeSynPtr = SymVoidSynPtr;

  if (!ExprLevel++)
  {
    opsp = sp = 0;
    PurgeStringTable();
  }

  tok = expr(tok, GotUnary, commaSeparator);

  if (tok == tokEof || strchr(",;:)]", tok) == NULL)
    error("Error: ParseExpr(): Unexpected token %s\n", GetTokenName(tok));

  if (*GotUnary)
  {
    int j;
    // Do this twice so we can see the stack before
    // and after manipulations
    for (j = 0; j < 2; j++)
    {
#ifndef NO_ANNOTATIONS
      int i;
      GenStartCommentLine();
      if (j) printf("Expanded");
      else printf("RPN'ized");
      printf(" expression: \"");
      for (i = 0; i < sp; i++)
      {
        int tok = stack[i][0];
        switch (tok)
        {
        case tokNumInt:
          printf("%d", truncInt(stack[i][1]));
          break;
        case tokNumUint:
          printf("%uu", truncUint(stack[i][1]));
          break;
        case tokIdent:
          {
            char* p = IdentTable + stack[i][1];
            if (isdigit(*p))
              printf("L");
            printf("%s", p);
          }
          break;
        case tokShortCirc:
          if (stack[i][1] >= 0)
            printf("[sh&&->%d]", stack[i][1]);
          else
            printf("[sh||->%d]", -stack[i][1]);
          break;
        case tokLocalOfs:
          printf("(@%d)", stack[i][1]);
          break;
        case tokUnaryStar:
          if (j) printf("*(%d)", stack[i][1]);
          else printf("*u");
          break;
        case '(': case ',':
          if (!j) printf("%c", tok);
          // else printf("\b");
          break;
        case ')':
          if (j) printf("(");
          printf("%c", tok);
          if (j) printf("%d", stack[i][1]);
          break;
        default:
          printf("%s", GetTokenName(tok));
          if (j)
          {
            switch (tok)
            {
            case tokLogOr: case tokLogAnd:
              printf("[%d]", stack[i][1]);
              break;
            case '=':
            case tokInc: case tokDec:
            case tokPostInc: case tokPostDec:
            case tokAssignAdd: case tokAssignSub:
            case tokPostAdd: case tokPostSub:
            case tokAssignMul: case tokAssignDiv: case tokAssignMod:
            case tokAssignLSh: case tokAssignRSh:
            case tokAssignAnd: case tokAssignXor: case tokAssignOr:
              printf("(%d)", stack[i][1]);
              break;
            }
          }
          break;
        }
        printf(" ");
      }
      printf("\"\n");
#endif
      if (!j)
      {
        int idx = sp - 1;
        *ConstVal = exprval(&idx, ExprTypeSynPtr, ConstExpr);
      }
#ifndef NO_ANNOTATIONS
      else if (*ConstExpr)
      {
        GenStartCommentLine();
        printf("Expression value: %d\n", *ConstVal);
      }
#endif
    }
  }

  ExprLevel--;

  return tok;
}

// smc.c code

void error(char* format, ...)
{
  int i, fidx = FileCnt - 1 + !FileCnt;
#ifndef __SMALLER_C__
  va_list vl;
  va_start(vl, format);
#else
  void* vl = &format + 1;
  void* testptr[2];
  // hopefully enough space to sprintf() 3 pointers using "%p"
  char testbuf[3][CHAR_BIT * sizeof(void*) + 1];
#endif

  for (i = 0; i < FileCnt; i++)
    if (Files[i])
      fclose(Files[i]);

  puts("");

  DumpSynDecls();
  DumpMacroTable();
  DumpIdentTable();

  GenStartCommentLine(); printf("Compilation failed.\n");

  printf("Error in \"%s\" (%d:%d)\n", FileNames[fidx], LineNo, LinePos);

#ifndef __SMALLER_C__
  vprintf(format, vl);
#else
  // TBD!!! This is not good. Really need the va_something macros.
  // Test whether va_list is a pointer to the first optional parameter or
  // an array of one element containing said pointer
  testptr[0] = &testptr[1];
  testptr[1] = &testptr[0];
  memset(testbuf, '\0', sizeof(testbuf));
  sprintf(testbuf[0], "%p", testptr[0]);
  sprintf(testbuf[1], "%p", testptr[1]);
  vsprintf(testbuf[2], "%p", &testptr[0]);
  if (!strcmp(testbuf[2], testbuf[0]))
  {
    // va_list is a pointer
    // (typical for Turbo C++, x86 gcc)
    vprintf(format, vl);
  }
  else if (!strcmp(testbuf[2], testbuf[1]))
  {
    // va_list is a one-element array containing a pointer
    // (typical for x86 Open Watcom C/C++)
    vprintf(format, &vl);
  }
  else
  {
    // va_list is something else, and
    // the code may have long crashed by now
    printf("%s", format);
  }
#endif

#ifndef __SMALLER_C__
  va_end(vl);
#endif
  exit(-1);
}

int TokenStartsDeclaration(int t, int params)
{
  return t == tokVoid || t == tokChar || t == tokInt ||
         t == tokSigned || t == tokUnsigned ||
         (!params && t == tokExtern);
}

void PushSyntax2(int t, int v)
{
  if (SyntaxStackCnt >= SYNTAX_STACK_MAX)
    error("Internal error: Too many declarations\n");
  SyntaxStack[SyntaxStackCnt][0] = t;
  SyntaxStack[SyntaxStackCnt++][1] = v;
}

void PushSyntax(int t)
{
  PushSyntax2(t, 0);
}

void InsertSyntax2(int pos, int t, int v)
{
  if (SyntaxStackCnt >= SYNTAX_STACK_MAX)
    error("Internal error: Too many declarations\n");
  memmove(SyntaxStack[pos + 1],
          SyntaxStack[pos],
          sizeof(SyntaxStack[0]) * (SyntaxStackCnt - pos));
  SyntaxStack[pos][0] = t;
  SyntaxStack[pos][1] = v;
  SyntaxStackCnt++;
}

void InsertSyntax(int pos, int t)
{
  InsertSyntax2(pos, t, 0);
}

void DeleteSyntax(int pos, int cnt)
{
  memmove(SyntaxStack[pos],
          SyntaxStack[pos + cnt],
          sizeof(SyntaxStack[0]) * (SyntaxStackCnt - (pos + cnt)));
  SyntaxStackCnt -= cnt;
}

int FindSymbol(char* s)
{
  int i;

  // TBD!!! return declaration scope number so
  // redeclarations can be reported if occur in the same scope.
  for (i = SyntaxStackCnt - 1; i >= 0; i--)
  {
    if (SyntaxStack[i][0] == tokIdent &&
        !strcmp(IdentTable + SyntaxStack[i][1], s))
    {
      return i;
    }
    else if (SyntaxStack[i][0] == ')')
    {
      // Skip over the function params
      int c = -1;
      while (c)
      {
        int t = SyntaxStack[--i][0];
        c += (t == '(') - (t == ')');
      }
    }
  }

  return -1;
}

int SymType(int SynPtr)
{
  int local = 0;

  if (SyntaxStack[SynPtr][0] == tokIdent)
    SynPtr++;

  if ((local = SyntaxStack[SynPtr][0] == tokLocalOfs) != 0)
    SynPtr++;

  switch (SyntaxStack[SynPtr][0])
  {
  case '(':
    return SymFxn;

  case '[':
    if (local)
      return SymLocalArr;
    return SymGlobalArr;

  default:
    if (local)
      return SymLocalVar;
    return SymGlobalVar;
  }
}

int GetDeclSize(int SyntaxPtr)
{
  int i;
  unsigned size = 1;

  if (SyntaxPtr < 0)
    return 0;

  for (i = SyntaxPtr; i < SyntaxStackCnt; i++)
  {
    int tok = SyntaxStack[i][0];
    switch (tok)
    {
    case tokIdent: // skip leading identifiers, if any
    case tokLocalOfs: // skip local var offset, too
      break;
    case tokChar:
      return size;
    case tokInt:
    case tokUnsigned:
    case '*':
    case '(': // size of fxn = size of ptr for now
      if (size * SizeOfWord / SizeOfWord != size)
        error("Error: Variable too big\n");
      size *= SizeOfWord;
      if (size != truncUint(size))
        error("Error: Variable too big\n");
      return uint2int(size);
    case '[':
      if (SyntaxStack[i + 1][0] != tokNumInt && SyntaxStack[i + 1][0] != tokNumUint)
        return 0;
      if (size * SyntaxStack[i + 1][1] / SyntaxStack[i + 1][1] != size)
        error("Error: Variable too big\n");
      size *= SyntaxStack[i + 1][1];
      if (size != truncUint(size))
        error("Error: Variable too big\n");
      i += 2;
      break;
    default:
      return 0;
    }
  }

  return 0;
}

void DumpDecl(int SyntaxPtr, int IsParam)
{
#ifndef NO_ANNOTATIONS
  int i;
  int icnt = 0;

  if (SyntaxPtr < 0)
    return;

  for (i = SyntaxPtr; i < SyntaxStackCnt; i++)
  {
    int tok = SyntaxStack[i][0];
    int v = SyntaxStack[i][1];
    switch (tok)
    {
    case tokLocalOfs:
      printf("(@%d): ", v);
      break;

    case tokIdent:
      if (++icnt > 1 && !IsParam) // show at most one declaration, except params
        return;

      GenStartCommentLine();

      if (ParseLevel == 0)
        printf("glb ");
      else if (IsParam)
        printf("prm ");
      else
        printf("loc ");

      {
        int j;
        for (j = 0; j < ParseLevel * 4; j++)
          printf(" ");
      }

      if (IsParam && !strcmp(IdentTable + v, "<something>") && (i + 1 < SyntaxStackCnt))
      {
        if (SyntaxStack[i + 1][0] == tokEllipsis)
          continue;
      }

      printf("%s : ", IdentTable + v);
      break;

    case '[':
      printf("[");
      break;

    case tokNumInt:
      printf("%d", truncInt(v));
      break;
    case tokNumUint:
      printf("%uu", truncUint(v));
      break;

    case ']':
      printf("] ");
      break;

    case '(':
      {
        int noparams;
        // Skip over the params to the base type
        int j = ++i, c = 1;
        while (c)
        {
          int t = SyntaxStack[j++][0];
          c += (t == '(') - (t == ')');
        }

        noparams = (i + 1 == j) || (SyntaxStack[i + 1][0] == tokVoid);

        printf("(");

        // Print the params (recursively)
        if (noparams)
        {
          // Don't recurse if it's "fxn()" or "fxn(void)"
          if (i + 1 != j)
            printf("void");
        }
        else
        {
          puts("");
          ParseLevel++;
          DumpDecl(i, 1);
          ParseLevel--;
        }

        // Continue normally
        i = j - 1;
        if (!noparams)
        {
          GenStartCommentLine();
          printf("    ");
          {
            int j;
            for (j = 0; j < ParseLevel * 4; j++)
              printf(" ");
          }
        }

        printf(") ");
      }
      break;

    case ')': // end of param list
      return;

    default:
      switch (tok)
      {
      case tokVoid:
      case tokChar:
      case tokInt:
      case tokUnsigned:
      case tokEllipsis:
        printf("%s\n", GetTokenName(tok));
        break;
      default:
        printf("%s ", GetTokenName(tok));
        break;
      }
      break;
    }
  }
#endif
#ifndef __SMALLER_C__
  (void)SyntaxPtr;
  (void)IsParam;
#endif
}

void DumpSynDecls(void)
{
#ifndef NO_ANNOTATIONS
  int used = SyntaxStackCnt * sizeof SyntaxStack[0];
  int total = SYNTAX_STACK_MAX * sizeof SyntaxStack[0];
  puts("");
  GenStartCommentLine(); printf("Syntax/declaration table/stack:\n");
  GenStartCommentLine(); printf("Bytes used: %d/%d\n\n", used, total);
#endif
}

int ParseArrayDimension(void)
{
  int tok;
  int gotUnary, synPtr, constExpr, exprVal;
  unsigned exprValU;
  int oldssp, oldesp, undoIdents;

  tok = GetToken();
  // DONE: support arbitrary constant expressions
  oldssp = SyntaxStackCnt;
  oldesp = sp;
  undoIdents = IdentTableLen;
  tok = ParseExpr(tok, &gotUnary, &synPtr, &constExpr, &exprVal, 0);
  IdentTableLen = undoIdents; // remove all temporary identifier names from e.g. "sizeof"
  SyntaxStackCnt = oldssp; // undo any temporary declarations from e.g. "sizeof" in the expression
  sp = oldesp;

  if (tok != ']')
    error("Error: ParseArrayDimension(): Unsupported or invalid array dimension (token %s)\n",
          GetTokenName(tok));

  if (!constExpr)
    error("Error: ParseArrayDimension(): non-constant array dimension\n");

  exprValU = exprVal;
  if ((synPtr == SymIntSynPtr && exprVal < 1) || (synPtr == SymUintSynPtr && exprValU < 1))
    error("Error: ParseArrayDimension(): array dimension less than 1\n");

  if (exprValU != truncUint(exprValU))
    error("Error: ParseArrayDimension(): array dimension too big\n");

  PushSyntax2(tokNumUint, exprVal);
  return tok;
}

void ParseFxnParams(void);
int ParseBlock(int BrkCntSwchTarget[4], int switchBody);
void AddFxnParamSymbols(int SyntaxPtr);

int ParseBase(int tok, int* base)
{
  if (tok == tokVoid || tok == tokChar || tok == tokInt)
  {
    *base = tok;
    tok = GetToken();
  }
  else if (tok == tokSigned || tok == tokUnsigned)
  {
    int sign = tok;
    tok = GetToken();

    if (tok == tokChar)
      error("Error: ParseBase(): 'signed char' and 'unsigned char' not supported\n");

    if (tok == tokInt)
      tok = GetToken();

    if (sign == tokUnsigned)
      *base = tokUnsigned;
    else
      *base = tokInt;
  }

  if (!tok || !(strchr("*([,)", tok) || tok == tokIdent))
    error("Error: ParseBase(): Invalid or unsupported type\n");

  return tok;
}

/*
  base * name []  ->  name : [] * base
  base *2 (*1 name []1) []2  ->  name : []1 *1 []2 *2 base
  base *3 (*2 (*1 name []1) []2) []3  ->  name : []1 *1 []2 *2 []3 *3 base
*/

int ParseDerived(int tok)
{
  int stars = 0;
  int lastSyntaxPtr = SyntaxStackCnt;

  while (tok == '*')
  {
    stars++;
    tok = GetToken();
  }

  if (tok == '(')
  {
    tok = GetToken();
    tok = ParseDerived(tok);
    if (tok != ')')
      error("Error: ParseDerived(): ')' expected\n");
    tok = GetToken();
  }
  else if (tok == tokIdent)
  {
    PushSyntax2(tok, AddIdent(GetTokenIdentName()));
    tok = GetToken();
  }
  else
  {
    PushSyntax2(tokIdent, AddIdent("<something>"));
  }

  if (tok == '[')
  {
    // TBD!!! allow first [] to go without the dimension in function parameters
    while (tok == '[')
    {
      int oldsp = SyntaxStackCnt;
      PushSyntax(tokVoid); // prevent cases like "int arr[arr];" and "int arr[arr[0]];"
      PushSyntax(tok);
      tok = ParseArrayDimension();
      if (tok != ']')
        error("Error: ParseDerived(): ']' expected\n");
      PushSyntax(']');
      tok = GetToken();
      DeleteSyntax(oldsp, 1);
    }
  }
  else if (tok == '(')
  {
    PushSyntax(tok);
    ParseLevel++;
    ParseFxnParams();
    ParseLevel--;
    PushSyntax(')');
    tok = GetToken();
  }

  while (stars--)
    PushSyntax('*');

  // TBD??? balance parens
  if (tok == ')')
    return tok;

  if (tok == '{')
  {
    // This can be the beginning of a function body, is this a function?
    int fxn = (lastSyntaxPtr + 1 < SyntaxStackCnt &&
               SyntaxStack[lastSyntaxPtr + 1][0] == '(');

    if (!fxn || ExprLevel)
      error("Error: ParseDerived(): '{' unexpected\n");
    if (ParseLevel)
      error("Error: ParseDerived(): Cannot define a nested function\n");
  }

  if (!tok || !strchr(",;{=", tok))
    error("Error: ParseDerived(): unexpected token %s\n", GetTokenName(tok));

  return tok;
}

// DONE: support extern
// DONE: support basic initialization
// DONE: support simple non-array initializations with string literals
// DONE: global/static data allocations
int ParseDecl(int tok)
{
  int base;
  int lastSyntaxPtr;
  int external = tok == tokExtern;

  if (external)
  {
    tok = GetToken();
    if (!TokenStartsDeclaration(tok, 1))
      error("Error: ParseDecl(): unexpected token %s\n", GetTokenName(tok));
  }
  tok = ParseBase(tok, &base);

  for (;;)
  {
    lastSyntaxPtr = SyntaxStackCnt;

    /* derived type */
    tok = ParseDerived(tok);

    /* base type */
    PushSyntax(base);

    if ((tok && strchr(",;{=", tok)) || (tok == ')' && ExprLevel))
    {
      int localAllocSize = 0;
      int globalAllocSize = 0;

      // Disallow void variables and arrays of void
      if (base == tokVoid)
      {
        int t = SyntaxStack[SyntaxStackCnt - 2][0];
        if (t != '*' && t != ')')
          error("Error: ParseDecl(): Cannot declare a variable ('%s') of type 'void'\n",
                IdentTable + SyntaxStack[lastSyntaxPtr][1]);
      }

      if (SyntaxStack[lastSyntaxPtr + 1][0] != '(')
      {
        int sz = GetDeclSize(lastSyntaxPtr);
        if (sz == 0)
          error("Error: ParseDecl(): GetDeclSize() = 0 (incomplete types aren't supported)\n");

        if (ParseLevel && !external && !ExprLevel)
        {
          int oldOfs;
          // It's a local variable, let's calculate its relative on-stack location
          oldOfs = CurFxnLocalOfs;

          CurFxnLocalOfs = uint2int((CurFxnLocalOfs + 0u - sz) & ~(SizeOfWord - 1u));
          if (CurFxnLocalOfs >= oldOfs || CurFxnLocalOfs != truncInt(CurFxnLocalOfs))
            error("Error: ParseDecl(): Local variables take too much space\n");

          // Insert a local var offset token
          InsertSyntax2(lastSyntaxPtr + 1, tokLocalOfs, CurFxnLocalOfs);

          localAllocSize = oldOfs - CurFxnLocalOfs;
          if (CurFxnMinLocalOfs > CurFxnLocalOfs)
            CurFxnMinLocalOfs = CurFxnLocalOfs;
        }
        else
        {
          // It's a global variable
          globalAllocSize = sz;
        }
      }

      // TBD!!! de-uglify
      if (!strcmp(IdentTable + SyntaxStack[lastSyntaxPtr][1], "<something>"))
      {
        // Disallow nameless variables and prototypes.
        if (!ExprLevel)
          error("Error: ParseDecl(): Identifier name expected\n");
      }
      else
      {
        // Disallow named variables and prototypes.
        if (ExprLevel)
          error("Error: ParseDecl(): Identifier name unexpected\n");
      }

      DumpDecl(lastSyntaxPtr, 0);

      if (ExprLevel)
        return tok;

      if (globalAllocSize && !external)
      {
        if (OutputFormat != FormatFlat)
          puts(DataHeader);
        GenWordAlignment();
        GenLabel(IdentTable + SyntaxStack[lastSyntaxPtr][1]);
      }

      if (external)
      {
        GenExtern(IdentTable + SyntaxStack[lastSyntaxPtr][1]);
      }
      // Handle initialization
      else if (tok == '=')
      {
        int gotUnary, synPtr,  constExpr, exprVal;
        int p;
        int oldssp, undoIdents;
#ifndef NO_ANNOTATIONS
        GenStartCommentLine(); printf("=\n");
#endif

        p = lastSyntaxPtr;
        while (SyntaxStack[p][0] == tokIdent || SyntaxStack[p][0] == tokLocalOfs)
          p++;

        oldssp = SyntaxStackCnt;
        undoIdents = IdentTableLen;

        if (strchr("([", SyntaxStack[p][0]))
          error("Error: ParseDecl(): invalid/unsupported initialization of array or function\n");

        tok = GetToken();
        tok = ParseExpr(tok, &gotUnary, &synPtr, &constExpr, &exprVal, 1);
        if (!tok || !strchr(",;", tok))
          error("Error: ParseDecl(): unexpected token %s after '='\n", GetTokenName(tok));

        if (!gotUnary)
          error("Error: ParseDecl(): missing initialization expression after '='\n");

        if (!ParseLevel)
        {
          if (constExpr)
          {
            GenIntData(globalAllocSize, exprVal);
            if (OutputFormat != FormatFlat)
              puts(DataFooter);
          }
          else if (globalAllocSize == SizeOfWord && stack[sp - 1][0] == tokIdent)
          {
            char* p = IdentTable + stack[sp - 1][1];
            GenAddrData(globalAllocSize, p);
            if (OutputFormat != FormatFlat)
              puts(DataFooter);
            // if the initializer is a literal string, also generate string data
            if (isdigit(*p))
              GenStrData(0);
          }
          else
            error("Error: ParseDecl(): cannot initialize a global variable with a non-constant expression\n");
        }
        else
        {
          if (synPtr >= 0 && SyntaxStack[synPtr][0] == tokVoid)
            error("Error: ParseDecl(): cannot initialize a variable with a 'void' expression\n");
          // transform the current expression stack into:
          //   tokLocalOfs(...), original expression stack, =(localAllocSize)
          // this will simulate assignment
          ins2(0, tokLocalOfs, SyntaxStack[lastSyntaxPtr + 1][1]);
          push2('=', localAllocSize);
          GenExpr();
        }

        IdentTableLen = undoIdents; // remove all temporary identifier names from e.g. "sizeof" or "str"
        SyntaxStackCnt = oldssp; // undo any temporary declarations from e.g. "sizeof" or "str" in the expression
      }
      else if (globalAllocSize)
      {
        GenZeroData(globalAllocSize);
        if (OutputFormat != FormatFlat)
          puts(DataFooter);
      }
      else if (tok == '{')
      {
        // It's a function body. Let's add function parameters as
        // local variables to the symbol table and parse the body.
        int undoSymbolsPtr = SyntaxStackCnt;
        int undoIdents = IdentTableLen;
        int locAllocLabel = (LabelCnt += 2) - 2;

        ParseLevel++;
        GetFxnInfo(lastSyntaxPtr, &CurFxnParamCntMin, &CurFxnParamCntMax, &CurFxnReturnExprTypeSynPtr); // get return type

        if (OutputFormat != FormatFlat)
          puts(CodeHeader);
        GenLabel(IdentTable + SyntaxStack[lastSyntaxPtr][1]);
        CurFxnEpilogLabel = LabelCnt++;
        GenFxnProlog();
        GenJumpUncond(locAllocLabel + 1);
        GenNumLabel(locAllocLabel);

        AddFxnParamSymbols(lastSyntaxPtr);
        if (!strcmp(IdentTable + SyntaxStack[lastSyntaxPtr][1], "main") && MainPrologCtorFxn)
        {
          GenExtern(MainPrologCtorFxn);
          GenPrintCallFxn(MainPrologCtorFxn);
        }
        tok = ParseBlock(NULL, 0);
        ParseLevel--;
        if (tok != '}')
          error("Error: ParseDecl(): '}' expected\n");
        IdentTableLen = undoIdents; // remove all identifier names
        SyntaxStackCnt = undoSymbolsPtr; // remove all params and locals

        GenNumLabel(CurFxnEpilogLabel);
        GenFxnEpilog();
        GenNumLabel(locAllocLabel + 1);
        if (CurFxnMinLocalOfs)
          GenLocalAlloc(-CurFxnMinLocalOfs);
        GenJumpUncond(locAllocLabel);
        if (OutputFormat != FormatFlat)
          puts(CodeFooter);
      }

      if (tok == ';' || tok == '}')
        break;

      tok = GetToken();
      continue;
    }

    error("Error: ParseDecl(): unexpected token %s\n", GetTokenName(tok));
  }

  tok = GetToken();
  return tok;
}

void ParseFxnParams(void)
{
  int tok, base;
  int lastSyntaxPtr;
  int cnt = 0;
  int ellCnt = 0;

  for (;;)
  {
    lastSyntaxPtr = SyntaxStackCnt;

    tok = GetToken();

    if (tok == ')') /* unspecified params */
      break;

    if (!TokenStartsDeclaration(tok, 1))
    {
      if (tok == tokEllipsis)
      {
        // "..." cannot be the first parameter and
        // it can be only one
        if (!cnt || ellCnt)
          error("Error: ParseFxnParams(): '...' unexpected here\n");
        ellCnt++;
      }
      else
        error("Error: ParseFxnParams(): Unexpected token %s\n", GetTokenName(tok));
      base = tok; // "..."
      PushSyntax2(tokIdent, AddIdent("<something>"));
      tok = GetToken();
    }
    else
    {
      if (ellCnt)
        error("Error: ParseFxnParams(): '...' must be the last in the parameter list\n");

      /* base type */
      tok = ParseBase(tok, &base);

      /* derived type */
      tok = ParseDerived(tok);
    }

    /* base type */
    PushSyntax(base);

    /* Decay arrays to pointers */
    lastSyntaxPtr++; /* skip name */
    if (SyntaxStack[lastSyntaxPtr][0] == '[')
    {
      DeleteSyntax(lastSyntaxPtr, 1);
      if (SyntaxStack[lastSyntaxPtr][0] == tokNumInt ||
          SyntaxStack[lastSyntaxPtr][0] == tokNumUint)
        DeleteSyntax(lastSyntaxPtr, 1);
      SyntaxStack[lastSyntaxPtr][0] = '*';
    }
    /* "(Un)decay" functions to function pointers */
    else if (SyntaxStack[lastSyntaxPtr][0] == '(')
    {
      InsertSyntax(lastSyntaxPtr, '*');
    }
    lastSyntaxPtr--; /* "unskip" name */

    cnt++;

    if (tok == ')' || tok == ',')
    {
      if (base == tokVoid)
      {
        int t = SyntaxStack[SyntaxStackCnt - 2][0];
        // Disallow void variables and arrays of void. TBD!!! de-uglify
        if (t != '*' && t != ')' &&
            !(cnt == 1 && tok == ')' && !strcmp(IdentTable + SyntaxStack[lastSyntaxPtr][1], "<something>")))
          error("Error: ParseFxnParams(): Cannot declare a variable ('%s') of type 'void'\n",
                IdentTable + SyntaxStack[lastSyntaxPtr][1]);
      }

      if (tok == ')')
        break;

      continue;
    }

    error("Error: ParseFxnParams(): Unexpected token %s\n", GetTokenName(tok));
  }
}

void AddFxnParamSymbols(int SyntaxPtr)
{
  int i;

  if (SyntaxPtr < 0 ||
      SyntaxPtr > SyntaxStackCnt - 3 ||
      SyntaxStack[SyntaxPtr][0] != tokIdent ||
      SyntaxStack[SyntaxPtr + 1][0] != '(')
    error("Internal error: AddFxnParamSymbols(): Invalid input\n");

  CurFxnSyntaxPtr = SyntaxPtr;
  CurFxnParamCnt = 0;
  CurFxnParamOfs = 2 * SizeOfWord; // ret addr, xbp
  CurFxnLocalOfs = 0;
  CurFxnMinLocalOfs = 0;

  SyntaxPtr += 2; // skip "ident("

  for (i = SyntaxPtr; i < SyntaxStackCnt; i++)
  {
    int tok = SyntaxStack[i][0];

    if (tok == tokIdent)
    {
      int sz;
      int paramPtr;

      if (i + 1 >= SyntaxStackCnt)
        error("Internal error: AddFxnParamSymbols(): Invalid input\n");

      if (SyntaxStack[i + 1][0] == tokVoid) // "ident(void)" = no params
        break;
      if (SyntaxStack[i + 1][0] == tokEllipsis) // "ident(something,...)" = no more params
        break;

      sz = GetDeclSize(i);
      if (sz == 0)
        error("Internal error: AddFxnParamSymbols(): GetDeclSize() = 0\n");

      // Let's calculate this parameter's relative on-stack location
      CurFxnParamOfs = (CurFxnParamOfs + SizeOfWord - 1) / SizeOfWord * SizeOfWord;
      paramPtr = SyntaxStackCnt;
      PushSyntax2(SyntaxStack[i][0], SyntaxStack[i][1]);
      PushSyntax2(tokLocalOfs, CurFxnParamOfs);
      CurFxnParamOfs += sz;

      // Duplicate this parameter in the symbol table
      i++;
      while (i < SyntaxStackCnt)
      {
        tok = SyntaxStack[i][0];
        if (tok == tokIdent || tok == ')')
        {
          CurFxnParamCnt++;
          DumpDecl(paramPtr, 0);
          i--;
          break;
        }
        else if (tok == '(')
        {
          int c = 1;
          i++;
          PushSyntax(tok);
          while (c && i < SyntaxStackCnt)
          {
            tok = SyntaxStack[i][0];
            c += (tok == '(') - (tok == ')');
            PushSyntax2(SyntaxStack[i][0], SyntaxStack[i][1]);
            i++;
          }
        }
        else
        {
          PushSyntax2(SyntaxStack[i][0], SyntaxStack[i][1]);
          i++;
        }
      }
    }
    else if (tok == ')') // endof "ident(" ... ")"
      break;
    else
      error("Internal error: AddFxnParamSymbols(): Unexpected token %s\n", GetTokenName(tok));
  }
}

int ParseStatement(int tok, int BrkCntSwchTarget[4], int switchBody)
{
/*
  labeled statements:
  - ident : statement
  + case const-expr : statement
  + default : statement

  compound statement:
  + { declaration(s)/statement(s)-opt }

  expression statement:
  + expression-opt ;

  selection statements:
  + if ( expression ) statement
  + if ( expression ) statement else statement
  + switch ( expression ) { statement(s)-opt }

  iteration statements:
  + while ( expression ) statement
  + do statement while ( expression ) ;
  + for ( expression-opt ; expression-opt ; expression-opt ) statement

  jump statements:
  - goto ident ;
  + continue ;
  + break ;
  + return expression-opt ;
*/
  int gotUnary, synPtr,  constExpr, exprVal;
  int brkCntSwchTarget[4];

  if (tok == ';')
  {
    tok = GetToken();
  }
  else if (tok == '{')
  {
    // A new {} block begins in the function body
    int undoSymbolsPtr = SyntaxStackCnt;
    int undoLocalOfs = CurFxnLocalOfs;
    int undoIdents = IdentTableLen;
#ifndef NO_ANNOTATIONS
    GenStartCommentLine(); printf("{\n");
#endif
    ParseLevel++;
    tok = ParseBlock(BrkCntSwchTarget, switchBody / 2);
    ParseLevel--;
    if (tok != '}')
      error("Error: ParseStatement(): '}' expected. Unexpected token %s\n", GetTokenName(tok));
    IdentTableLen = undoIdents; // remove all identifier names
    SyntaxStackCnt = undoSymbolsPtr; // remove all params and locals
    CurFxnLocalOfs = undoLocalOfs; // destroy on-stack local variables
#ifndef NO_ANNOTATIONS
    GenStartCommentLine(); printf("}\n");
#endif
    tok = GetToken();
  }
  else if (tok == tokReturn)
  {
    // DONE: functions returning void vs non-void
#ifndef NO_ANNOTATIONS
    GenStartCommentLine(); printf("return\n");
#endif
    tok = GetToken();
    if (ParseExpr(tok, &gotUnary, &synPtr, &constExpr, &exprVal, 0) != ';')
      error("Error: ParseStatement(): ';' expected\n");
    if (CurFxnReturnExprTypeSynPtr >= 0 &&
        SyntaxStack[CurFxnReturnExprTypeSynPtr][0] == tokVoid)
    {
      if (gotUnary)
        error("Error: ParseStatement(): cannot return a value from a function returning 'void'\n");
    }
    else
    {
      if (!gotUnary)
        error("Error: ParseStatement(): missing return value\n");
    }
    if (gotUnary)
      GenExpr();
    GenJumpUncond(CurFxnEpilogLabel);
    tok = GetToken();
  }
  else if (tok == tokWhile)
  {
    int labelBefore = LabelCnt++;
    int labelAfter = LabelCnt++;
#ifndef NO_ANNOTATIONS
    GenStartCommentLine(); printf("while\n");
#endif

    tok = GetToken();
    if (tok != '(')
      error("Error: ParseStatement(): '(' expected after 'while'\n");

    tok = GetToken();
    if (ParseExpr(tok, &gotUnary, &synPtr, &constExpr, &exprVal, 0) != ')')
      error("Error: ParseStatement(): ')' expected after 'while ( expression'\n");

    if (!gotUnary)
      error("Error: ParseStatement(): expression expected in 'while ( expression )'\n");

    // DONE: void control expressions
    if (synPtr >= 0 && SyntaxStack[synPtr][0] == tokVoid)
      error("Error: ParseStatement(): unexpected 'void' expression in 'while ( expression )'\n");

    GenNumLabel(labelBefore);

    switch (stack[sp - 1][0])
    {
    case '<':
    case '>':
    case tokEQ:
    case tokNEQ:
    case tokLEQ:
    case tokGEQ:
    case tokULess:
    case tokUGreater:
    case tokULEQ:
    case tokUGEQ:
      push2(tokIfNot, labelAfter);
      GenExpr();
      break;
    default:
      GenExpr();
      GenJumpIfZero(labelAfter);
      break;
    }

    tok = GetToken();
    brkCntSwchTarget[0] = labelAfter; // break target
    brkCntSwchTarget[1] = labelBefore; // continue target
    tok = ParseStatement(tok, brkCntSwchTarget, 0);

    GenJumpUncond(labelBefore);
    GenNumLabel(labelAfter);
  }
  else if (tok == tokDo)
  {
    int labelBefore = LabelCnt++;
    int labelWhile = LabelCnt++;
    int labelAfter = LabelCnt++;
#ifndef NO_ANNOTATIONS
    GenStartCommentLine(); printf("do\n");
#endif
    GenNumLabel(labelBefore);

    tok = GetToken();
    brkCntSwchTarget[0] = labelAfter; // break target
    brkCntSwchTarget[1] = labelWhile; // continue target
    tok = ParseStatement(tok, brkCntSwchTarget, 0);
    if (tok != tokWhile)
      error("Error: ParseStatement(): 'while' expected after 'do statement'\n");

#ifndef NO_ANNOTATIONS
    GenStartCommentLine(); printf("while\n");
#endif
    tok = GetToken();
    if (tok != '(')
      error("Error: ParseStatement(): '(' expected after 'while'\n");

    tok = GetToken();
    if (ParseExpr(tok, &gotUnary, &synPtr, &constExpr, &exprVal, 0) != ')')
      error("Error: ParseStatement(): ')' expected after 'while ( expression'\n");

    if (!gotUnary)
      error("Error: ParseStatement(): expression expected in 'while ( expression )'\n");

    tok = GetToken();
    if (tok != ';')
      error("Error: ParseStatement(): ';' expected after 'do statement while ( expression )'\n");

    // DONE: void control expressions
    if (synPtr >= 0 && SyntaxStack[synPtr][0] == tokVoid)
      error("Error: ParseStatement(): unexpected 'void' expression in 'while ( expression )'\n");

    GenNumLabel(labelWhile);

    switch (stack[sp - 1][0])
    {
    case '<':
    case '>':
    case tokEQ:
    case tokNEQ:
    case tokLEQ:
    case tokGEQ:
    case tokULess:
    case tokUGreater:
    case tokULEQ:
    case tokUGEQ:
      push2(tokIf, labelBefore);
      GenExpr();
      break;
    default:
      GenExpr();
      GenJumpIfNotZero(labelBefore);
      break;
    }

    GenNumLabel(labelAfter);

    tok = GetToken();
  }
  else if (tok == tokIf)
  {
    int labelAfterIf = LabelCnt++;
    int labelAfterElse = LabelCnt++;
#ifndef NO_ANNOTATIONS
    GenStartCommentLine(); printf("if\n");
#endif

    tok = GetToken();
    if (tok != '(')
      error("Error: ParseStatement(): '(' expected after 'if'\n");

    tok = GetToken();
    if (ParseExpr(tok, &gotUnary, &synPtr, &constExpr, &exprVal, 0) != ')')
      error("Error: ParseStatement(): ')' expected after 'if ( expression'\n");

    if (!gotUnary)
      error("Error: ParseStatement(): expression expected in 'if ( expression )'\n");

    // DONE: void control expressions
    if (synPtr >= 0 && SyntaxStack[synPtr][0] == tokVoid)
      error("Error: ParseStatement(): unexpected 'void' expression in 'if ( expression )'\n");

    switch (stack[sp - 1][0])
    {
    case '<':
    case '>':
    case tokEQ:
    case tokNEQ:
    case tokLEQ:
    case tokGEQ:
    case tokULess:
    case tokUGreater:
    case tokULEQ:
    case tokUGEQ:
      push2(tokIfNot, labelAfterIf);
      GenExpr();
      break;
    default:
      GenExpr();
      GenJumpIfZero(labelAfterIf);
      break;
    }

    tok = GetToken();
    tok = ParseStatement(tok, BrkCntSwchTarget, 0);

    // DONE: else
    if (tok == tokElse)
    {
      GenJumpUncond(labelAfterElse);
      GenNumLabel(labelAfterIf);
#ifndef NO_ANNOTATIONS
      GenStartCommentLine(); printf("else\n");
#endif
      tok = GetToken();
      tok = ParseStatement(tok, BrkCntSwchTarget, 0);
      GenNumLabel(labelAfterElse);
    }
    else
    {
      GenNumLabel(labelAfterIf);
    }
  }
  else if (tok == tokFor)
  {
    int labelBefore = LabelCnt++;
    int labelExpr3 = LabelCnt++;
    int labelBody = LabelCnt++;
    int labelAfter = LabelCnt++;
#ifndef NO_ANNOTATIONS
    GenStartCommentLine(); printf("for\n");
#endif
    tok = GetToken();
    if (tok != '(')
      error("Error: ParseStatement(): '(' expected after 'for'\n");

    tok = GetToken();
    if (ParseExpr(tok, &gotUnary, &synPtr, &constExpr, &exprVal, 0) != ';')
      error("Error: ParseStatement(): ';' expected after 'for ( expression'\n");
    if (gotUnary)
    {
      GenExpr();
    }

    GenNumLabel(labelBefore);
    tok = GetToken();
    if (ParseExpr(tok, &gotUnary, &synPtr, &constExpr, &exprVal, 0) != ';')
      error("Error: ParseStatement(): ';' expected after 'for ( expression ; expression'\n");
    if (gotUnary)
    {
      // DONE: void control expressions
      if (synPtr >= 0 && SyntaxStack[synPtr][0] == tokVoid)
        error("Error: ParseStatement(): unexpected 'void' expression in 'for ( ; expression ; )'\n");

      switch (stack[sp - 1][0])
      {
      case '<':
      case '>':
      case tokEQ:
      case tokNEQ:
      case tokLEQ:
      case tokGEQ:
      case tokULess:
      case tokUGreater:
      case tokULEQ:
      case tokUGEQ:
        push2(tokIfNot, labelAfter);
        GenExpr();
        break;
      default:
        GenExpr();
        GenJumpIfZero(labelAfter);
        break;
      }
    }
    GenJumpUncond(labelBody);

    GenNumLabel(labelExpr3);
    tok = GetToken();
    if (ParseExpr(tok, &gotUnary, &synPtr, &constExpr, &exprVal, 0) != ')')
      error("Error: ParseStatement(): ')' expected after 'for ( expression ; expression ; expression'\n");
    if (gotUnary)
    {
      GenExpr();
    }
    GenJumpUncond(labelBefore);

    GenNumLabel(labelBody);
    tok = GetToken();
    brkCntSwchTarget[0] = labelAfter; // break target
    brkCntSwchTarget[1] = labelExpr3; // continue target
    tok = ParseStatement(tok, brkCntSwchTarget, 0);
    GenJumpUncond(labelExpr3);

    GenNumLabel(labelAfter);
  }
  else if (tok == tokBreak)
  {
#ifndef NO_ANNOTATIONS
    GenStartCommentLine(); printf("break\n");
#endif
    if (GetToken() != ';')
      error("Error: ParseStatement(): ';' expected\n");
    tok = GetToken();
    if (BrkCntSwchTarget == NULL)
      error("Error: ParseStatement(): 'break' must be within 'while', 'for' or 'switch' statement\n");
    GenJumpUncond(BrkCntSwchTarget[0]);
  }
  else if (tok == tokCont)
  {
#ifndef NO_ANNOTATIONS
    GenStartCommentLine(); printf("continue\n");
#endif
    if (GetToken() != ';')
      error("Error: ParseStatement(): ';' expected\n");
    tok = GetToken();
    if (BrkCntSwchTarget == NULL || BrkCntSwchTarget[1] == 0)
      error("Error: ParseStatement(): 'continue' must be within 'while' or 'for' statement\n");
    GenJumpUncond(BrkCntSwchTarget[1]);
  }
  else if (tok == tokSwitch)
  {
#ifndef NO_ANNOTATIONS
    GenStartCommentLine(); printf("switch\n");
#endif

    tok = GetToken();
    if (tok != '(')
      error("Error: ParseStatement(): '(' expected after 'switch'\n");

    tok = GetToken();
    if (ParseExpr(tok, &gotUnary, &synPtr, &constExpr, &exprVal, 0) != ')')
      error("Error: ParseStatement(): ')' expected after 'switch ( expression'\n");

    if (!gotUnary)
      error("Error: ParseStatement(): expression expected in 'switch ( expression )'\n");

    // DONE: void control expressions
    if (synPtr >= 0 && SyntaxStack[synPtr][0] == tokVoid)
      error("Error: ParseStatement(): unexpected 'void' expression in 'switch ( expression )'\n");

    GenExpr();

    tok = GetToken();
    if (tok != '{')
      error("Error: ParseStatement(): '{' expected after 'switch ( expression )'\n");

    brkCntSwchTarget[0] = LabelCnt++; // break target
    brkCntSwchTarget[1] = 0; // continue target
    if (BrkCntSwchTarget != NULL)
    {
      // preserve the continue target
      brkCntSwchTarget[1] = BrkCntSwchTarget[1]; // continue target
    }
    brkCntSwchTarget[2] = LabelCnt++; // default target
    brkCntSwchTarget[3] = (LabelCnt += 2) - 2; // next case target
/*
  ParseBlock(0)
    ParseStatement(0)
      switch
        ParseStatement(2)            // 2 needed to disallow new locals
          {                          // { in switch(expr){
            ParseBlock(1)            // new locals are allocated here
              ParseStatement(1)      // 1 needed for case/default
                {                    // inner {} in switch(expr){{}}
                  ParseBlock(0)
                  ...
                switch               // another switch
                  ParseStatement(2)  // needed to disallow new locals
                  ...
*/
    GenJumpUncond(brkCntSwchTarget[3]); // next case target

    tok = ParseStatement(tok, brkCntSwchTarget, 2);

    // force 'break' if the last 'case'/'default' doesn't end with 'break'
    GenJumpUncond(brkCntSwchTarget[0]);

    // next, non-existent case (reached after none of the 'cases' have matched)
    GenNumLabel(brkCntSwchTarget[3]);

    // if there's 'default', 'goto default;' after all unmatched 'cases'
    if (brkCntSwchTarget[2] < 0)
      GenJumpUncond(-brkCntSwchTarget[2]);

    GenNumLabel(brkCntSwchTarget[0]); // break label
  }
  else if (tok == tokCase)
  {
    int lnext;
#ifndef NO_ANNOTATIONS
    GenStartCommentLine(); printf("case\n");
#endif

    if (!switchBody)
      error("Error: ParseStatement(): 'case' must be within 'switch' statement\n");

    tok = GetToken();
    if (ParseExpr(tok, &gotUnary, &synPtr, &constExpr, &exprVal, 0) != ':')
      error("Error: ParseStatement(): ':' expected after 'case expression'\n");

    if (!gotUnary || !constExpr || (synPtr >= 0 && SyntaxStack[synPtr][0] == tokVoid))
      error("Error: ParseStatement(): constant integer expression expected in 'case expression :'\n");

    tok = GetToken();

    lnext = (LabelCnt += 2) - 2;

    GenJumpUncond(BrkCntSwchTarget[3] + 1); // fallthrough
    GenNumLabel(BrkCntSwchTarget[3]);
    GenJumpIfNotEqual(exprVal, lnext);
    GenNumLabel(BrkCntSwchTarget[3] + 1);

    BrkCntSwchTarget[3] = lnext;
  }
  else if (tok == tokDefault)
  {
#ifndef NO_ANNOTATIONS
    GenStartCommentLine(); printf("default\n");
#endif

    if (!switchBody)
      error("Error: ParseStatement(): 'default' must be within 'switch' statement\n");

    tok = GetToken();
    if (tok != ':')
      error("Error: ParseStatement(): ':' expected after 'default'\n");

    if (BrkCntSwchTarget[2] < 0)
      error("Error: ParseStatement(): only one 'default' allowed in 'switch'\n");

    tok = GetToken();

    GenNumLabel(BrkCntSwchTarget[2]); // default:

    BrkCntSwchTarget[2] *= -1; // remember presence of default:
  }
  else if (tok == tok_Asm)
  {
    tok = GetToken();
    if (tok != '(')
      error("Error: ParseStatement(): '(' expected after 'asm'\n");

    tok = GetToken();
    if (ParseExpr(tok, &gotUnary, &synPtr, &constExpr, &exprVal, 0) != ')')
      error("Error: ParseStatement(): ')' expected after 'asm ( expression'\n");

    if (!gotUnary || tok != tokLitStr)
      error("Error: ParseStatement(): string literal expression expected in 'asm ( expression )'\n");

    puts(GetTokenValueString());

    tok = GetToken();
    if (tok != ';')
      error("Error: ParseStatement(): ';' expected after 'asm ( expression )'\n");

    tok = GetToken();
  }
  else
  {
    if (ParseExpr(tok, &gotUnary, &synPtr, &constExpr, &exprVal, 0) != ';')
      error("Error: ParseStatement(): ';' expected\n");
    if (gotUnary)
    {
      GenExpr();
    }
    tok = GetToken();
  }

  return tok;
}

// TBD!!! think of ways of getting rid of switchBody
int ParseBlock(int BrkCntSwchTarget[4], int switchBody)
{
  int tok = GetToken();

  for (;;)
  {
    if (tok == 0)
      return tok;

    if (tok == '}' && ParseLevel > 0)
      return tok;

    if (TokenStartsDeclaration(tok, 0))
    {
      tok = ParseDecl(tok);
    }
    else if (ParseLevel > 0)
    {
      tok = ParseStatement(tok, BrkCntSwchTarget, switchBody);
    }
    else
      error("Error: ParseBlock(): Unexpected token %s\n", GetTokenName(tok));
  }
}

int main(int argc, char** argv)
{
  // gcc/MinGW inserts a call to __main() here.
  int i;

  GenInit();

  // Parse the command line parameters
  for (i = 1; i < argc; i++)
  {
    // DONE: move code-generator-specific options to
    // the code generator
    if (GenInitParams(argc, argv, &i))
    {
      continue;
    }
    else if (!strcmp(argv[i], "-signed-char"))
    {
      // this is the default option
      CharIsSigned = 1;
      continue;
    }
    else if (!strcmp(argv[i], "-unsigned-char"))
    {
      CharIsSigned = 0;
      continue;
    }
    else if (!strcmp(argv[i], "-ctor-fxn"))
    {
      if (i + 1 < argc)
      {
        MainPrologCtorFxn = argv[++i];
        continue;
      }
    }
    else if (!strcmp(argv[i], "-leading-underscore"))
    {
      // this is the default option for x86
      UseLeadingUnderscores = 1;
      continue;
    }
    else if (!strcmp(argv[i], "-no-leading-underscore"))
    {
      // this is the default option for MIPS
      UseLeadingUnderscores = 0;
      continue;
    }
    else if (!strcmp(argv[i], "-I"))
    {
      if (i + 1 < argc)
      {
        int len = strlen(argv[++i]);
        if (MAX_SEARCH_PATH - SearchPathsLen < len + 1)
          error("Error: Path name too long\n");
        strcpy(SearchPaths + SearchPathsLen, argv[i]);
        SearchPathsLen += len + 1;
        continue;
      }
    }
    // DONE: '-D macro[=expansion]': '#define macro 1' when there's no '=expansion'
    else if (!strcmp(argv[i], "-D"))
    {
      if (i + 1 < argc)
      {
        char id[MAX_IDENT_LEN + 1];
        char* e = strchr(argv[++i], '=');
        int len;
        if (e)
        {
          len = e - argv[i];
          e++;
        }
        else
        {
          len = strlen(argv[i]);
          e = "1";
        }
        if (len > 0 && len <= MAX_IDENT_LEN)
        {
          int j, bad = 1;
          memcpy(id, argv[i], len);
          id[len] = '\0';
          for (j = 0; j < len; j++)
            if ((bad = !(id[j] == '_' || (!j * isalpha(id[j]) + j * isalnum(id[j])))) != 0)
              break;
          if (!bad)
          {
            DefineMacro(id, e);
            continue;
          }
        }
      }
    }
    else if (!FileCnt)
    {
      // If it's none of the known options,
      // assume it's the source code file name
      if (strlen(argv[i]) > MAX_FILE_NAME_LEN)
        error("Error: File name too long\n");
      strcpy(FileNames[0], argv[i]);
      if ((Files[0] = fopen(FileNames[0], "rt")) == NULL)
        error("Error: Cannot open file \"%s\"\n", FileNames[0]);
      LineNos[0] = LineNo;
      LinePoss[0] = LinePos;
      FileCnt++;
      continue;
    }  

    error("Error: Invalid/unsupported command line option(s)\n");
  }

  if (!FileCnt)
    error("Error: Input source code file not specified.\n");

  GenInitFinalize();

  // some manual initialization because there's no array initialization yet
  SyntaxStack[SyntaxStackCnt][0] = tokVoid;
  SyntaxStack[SyntaxStackCnt++][1] = 0;
  SyntaxStack[SyntaxStackCnt][0] = tokInt;
  SyntaxStack[SyntaxStackCnt++][1] = 0;
  SyntaxStack[SyntaxStackCnt][0] = tokUnsigned;
  SyntaxStack[SyntaxStackCnt++][1] = 0;

  // Define a few macros useful for conditional compilation
  DefineMacro("__SMALLER_C__", "0x0100");
  if (SizeOfWord == 2)
    DefineMacro("__SMALLER_C_16__", "");
  else if (SizeOfWord == 4)
    DefineMacro("__SMALLER_C_32__", "");
  if (CharIsSigned)
    DefineMacro("__SMALLER_C_SCHAR__", "");
  else
    DefineMacro("__SMALLER_C_UCHAR__", "");

  // When generating 32-bit assembly code with 16-bit compiler
  // output may be incorrect if constant subexpressions are folded
  // (because 32-bit constants get truncated to 16-bit).
  // Disable constant subexpression simplification if needed.
  canSimplify = !(SizeOfWord == 4 && sizeof(int) * CHAR_BIT < 32u);

  // populate CharQueue[] with the initial file characters
  ShiftChar();

  puts(FileHeader);

  // compile
  ParseBlock(NULL, 0);

  DumpSynDecls();
  DumpMacroTable();
  DumpIdentTable();

  GenStartCommentLine(); printf("Compilation succeeded.\n");

  return 0;
}
