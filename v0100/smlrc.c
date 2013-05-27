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
/*                                Main file                                  */
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
EXTERN FILE* fopen(char*, char*);
EXTERN int fclose(FILE*);
EXTERN int putchar(int);
EXTERN int fputc(int, FILE*);
EXTERN int fgetc(FILE*);
EXTERN int puts(char*);
EXTERN int fputs(char*, FILE*);
EXTERN int sprintf(char*, char*, ...);
//EXTERN int vsprintf(char*, char*, va_list);
EXTERN int vsprintf(char*, char*, void*);
EXTERN int printf(char*, ...);
EXTERN int fprintf(FILE*, char*, ...);
//EXTERN int vprintf(char*, va_list);
EXTERN int vprintf(char*, void*);
//EXTERN int vfprintf(FILE*, char*, va_list);
EXTERN int vfprintf(FILE*, char*, void*);

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

#ifndef NO_PREPROCESSOR
PROTO void DumpMacroTable(void);
#endif

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
PROTO int puts2(char*);
PROTO int printf2(char*, ...);
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

#ifndef NO_PREPROCESSOR
/*
  Macro table entry format:
    idlen char:     identifier length (<= 127)
    id char[idlen]: identifier (ASCIIZ)
    exlen char:     length of what the identifier expands into (<= 127)
    ex char[exlen]: what the identifier expands into (ASCII)
*/
char MacroTable[MAX_MACRO_TABLE_LEN];
int MacroTableLen = 0;
#endif

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
FILE* OutFile;
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

#ifndef NO_PREPROCESSOR
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

  puts2("");
  GenStartCommentLine(); printf2("Macro table:\n");
  for (i = 0; i < MacroTableLen; )
  {
    GenStartCommentLine(); printf2("Macro %s = ", MacroTable + i + 1);
    i = i + 1 + MacroTable[i]; // skip id
    printf2("`");
    j = MacroTable[i++];
    while (j--)
      printf2("%c", MacroTable[i++]);
    printf2("`\n");
  }
  GenStartCommentLine(); printf2("Bytes used: %d/%d\n\n", MacroTableLen, MAX_MACRO_TABLE_LEN);
#endif
}
#endif // #ifndef NO_PREPROCESSOR

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
  puts2("");
  GenStartCommentLine(); printf2("Identifier table:\n");
  for (i = 0; i < IdentTableLen; )
  {
    GenStartCommentLine(); printf2("Ident %s\n", IdentTable + i);
    i += strlen(IdentTable + i) + 2;
  }
  GenStartCommentLine(); printf2("Bytes used: %d/%d\n\n", IdentTableLen, MAX_IDENT_TABLE_LEN);
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

#ifndef NO_PREPROCESSOR
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
    Files[FileCnt] = fopen(FileNames[FileCnt], "r");
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
        if ((Files[FileCnt] = fopen(FileNames[FileCnt], "r")) == NULL)
        {
          // next, try '\\' as a separator (DOS/Windows)
          FileNames[FileCnt][plen] = '\\';
          Files[FileCnt] = fopen(FileNames[FileCnt], "r");
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
#endif // #ifndef NO_PREPROCESSOR

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

#ifndef NO_PREPROCESSOR
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
#endif

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
#ifndef NO_PREPROCESSOR
      int midx;
#endif

      GetIdent();

      if (!PrepDontSkipTokens)
        continue;

      tok = GetTokenByWord(TokenIdentName);

#ifndef NO_PREPROCESSOR
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
#endif

      return tok;
    } // endof if (ch == '_' || isalpha(ch))

#ifndef NO_PREPROCESSOR
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
#else // #ifndef NO_PREPROCESSOR
    if (ch == '#')
    {
      int line;

      ShiftCharN(1);

      // Support for external, gcc-like, preprocessor output:
      //   # linenum filename flags
      //
      // no flags, flag = 1 -- start of a file
      //           flag = 2 -- return to a file after #include
      //        other flags -- uninteresting

      SkipSpace(0);

      if (!isdigit(*p) || GetNumber() != tokNumInt)
        error("Error: Invalid line number in preprocessor output\n");
      line = GetTokenValueInt();

      SkipSpace(0);

      if (*p == '\"')
        GetString('\"', 0);
      else if (*p == '<')
        GetString('>', 0);
      else
        error("Error: Invalid file name in preprocessor output\n");

      if (strlen(GetTokenValueString()) > MAX_FILE_NAME_LEN)
        error("Error: File name too long in preprocessor output\n");

      SkipSpace(0);

      while (!strchr("\r\n", *p))
      {
        if (!isdigit(*p) || GetNumber() != tokNumInt)
          error("Error: Invalid flag in preprocessor output\n");
        SkipSpace(0);
      }

      LineNo = line - 1; // "line" is the number of the next line
      LinePos = 1;
      strcpy(FileNames[0], GetTokenValueString());

      continue;
    } // endof if (ch == '#')
#endif // #ifndef NO_PREPROCESSOR

    error("Error: Unsupported or invalid character '%c'\n", *p);
  } // endof for (;;)

  return tokEof;
}

#ifdef MIPS
#include "cgmips.c"
#else
#include "cgx86.c"
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
      if (j) printf2("Expanded");
      else printf2("RPN'ized");
      printf2(" expression: \"");
      for (i = 0; i < sp; i++)
      {
        int tok = stack[i][0];
        switch (tok)
        {
        case tokNumInt:
          printf2("%d", truncInt(stack[i][1]));
          break;
        case tokNumUint:
          printf2("%uu", truncUint(stack[i][1]));
          break;
        case tokIdent:
          {
            char* p = IdentTable + stack[i][1];
            if (isdigit(*p))
              printf2("L");
            printf2("%s", p);
          }
          break;
        case tokShortCirc:
          if (stack[i][1] >= 0)
            printf2("[sh&&->%d]", stack[i][1]);
          else
            printf2("[sh||->%d]", -stack[i][1]);
          break;
        case tokLocalOfs:
          printf2("(@%d)", stack[i][1]);
          break;
        case tokUnaryStar:
          if (j) printf2("*(%d)", stack[i][1]);
          else printf2("*u");
          break;
        case '(': case ',':
          if (!j) printf2("%c", tok);
          // else printf2("\b");
          break;
        case ')':
          if (j) printf2("(");
          printf2("%c", tok);
          if (j) printf2("%d", stack[i][1]);
          break;
        default:
          printf2("%s", GetTokenName(tok));
          if (j)
          {
            switch (tok)
            {
            case tokLogOr: case tokLogAnd:
              printf2("[%d]", stack[i][1]);
              break;
            case '=':
            case tokInc: case tokDec:
            case tokPostInc: case tokPostDec:
            case tokAssignAdd: case tokAssignSub:
            case tokPostAdd: case tokPostSub:
            case tokAssignMul: case tokAssignDiv: case tokAssignMod:
            case tokAssignLSh: case tokAssignRSh:
            case tokAssignAnd: case tokAssignXor: case tokAssignOr:
              printf2("(%d)", stack[i][1]);
              break;
            }
          }
          break;
        }
        printf2(" ");
      }
      printf2("\"\n");
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
        printf2("Expression value: %d\n", *ConstVal);
      }
#endif
    }
  }

  ExprLevel--;

  return tok;
}

// smc.c code

#ifdef __SMALLER_C__
// 2 if va_list is a one-element array containing a pointer
//   (typical for x86 Open Watcom C/C++)
// 1 if va_list is a pointer
//   (typical for Turbo C++, x86 gcc)
// 0 if va_list is something else, and
//   the code may have long crashed by now
int VaListType = 0;

// Attempts to determine the type of va_list as
// expected by the standard library
void DetermineVaListType(void)
{
  void* testptr[2];
  // hopefully enough space to sprintf() 3 pointers using "%p"
  char testbuf[3][CHAR_BIT * sizeof(void*) + 1];

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
    VaListType = 1;
  }
  else if (!strcmp(testbuf[2], testbuf[1]))
  {
    // va_list is a one-element array containing a pointer
    VaListType = 2;
  }
  else
  {
    // va_list is something else, and
    // the code may have long crashed by now
    printf("Internal Error: va_list type indeterminate.\n");
    exit(-1);
  }
}
#endif

// Equivalent to puts() but outputs to OutFile
// if it's not NULL.
int puts2(char* s)
{
  int res;
  if (OutFile != NULL)
  {
    if ((res = fputs(s, OutFile)) >= 0)
    {
      // unlike puts(), fputs() doesn't append '\n', append it manually
      res = fputc('\n', OutFile);
    }
  }
  else
  {
    res = puts(s);
  }
  return res;
}

// Equivalent to printf() but outputs to OutFile
// if it's not NULL.
int printf2(char* format, ...)
{
  int res;

#ifndef __SMALLER_C__
  va_list vl;
  va_start(vl, format);
#else
  void* vl = &format + 1;
#endif

#ifndef __SMALLER_C__
  if (OutFile != NULL)
    res = vfprintf(OutFile, format, vl);
  else
    res = vprintf(format, vl);
#else
  // TBD!!! This is not good. Really need the va_something macros.
  if (VaListType == 1)
  {
    // va_list is a pointer
    if (OutFile != NULL)
      res = vfprintf(OutFile, format, vl);
    else
      res = vprintf(format, vl);
  }
  else // if (VaListType == 2)
  {
    // va_list is a one-element array containing a pointer
    if (OutFile != NULL)
      res = vfprintf(OutFile, format, &vl);
    else
      res = vprintf(format, &vl);
  }
#endif

#ifndef __SMALLER_C__
  va_end(vl);
#endif

  return res;
}

void error(char* format, ...)
{
  int i, fidx = FileCnt - 1 + !FileCnt;
#ifndef __SMALLER_C__
  va_list vl;
  va_start(vl, format);
#else
  void* vl = &format + 1;
#endif

  for (i = 0; i < FileCnt; i++)
    if (Files[i])
      fclose(Files[i]);

  puts2("");

  DumpSynDecls();
#ifndef NO_PREPROCESSOR
  DumpMacroTable();
#endif
  DumpIdentTable();

  // using stdout implicitly instead of stderr explicitly because:
  // - stderr can be a macro and it's unknown if standard headers
  //   aren't included (which is the case when SmallerC is compiled
  //   with itself and linked with some other compiler's standard
  //   libraries)
  // - output to stderr can interfere/overlap with buffered
  //   output to stdout and the result may literally look ugly

  GenStartCommentLine(); printf2("Compilation failed.\n");

  if (OutFile != NULL)
    fclose(OutFile);

  printf("Error in \"%s\" (%d:%d)\n", FileNames[fidx], LineNo, LinePos);

#ifndef __SMALLER_C__
  vprintf(format, vl);
#else
  // TBD!!! This is not good. Really need the va_something macros.
  if (VaListType == 1)
  {
    // va_list is a pointer
    vprintf(format, vl);
  }
  else // if (VaListType == 2)
  {
    // va_list is a one-element array containing a pointer
    vprintf(format, &vl);
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
      printf2("(@%d): ", v);
      break;

    case tokIdent:
      if (++icnt > 1 && !IsParam) // show at most one declaration, except params
        return;

      GenStartCommentLine();

      if (ParseLevel == 0)
        printf2("glb ");
      else if (IsParam)
        printf2("prm ");
      else
        printf2("loc ");

      {
        int j;
        for (j = 0; j < ParseLevel * 4; j++)
          printf2(" ");
      }

      if (IsParam && !strcmp(IdentTable + v, "<something>") && (i + 1 < SyntaxStackCnt))
      {
        if (SyntaxStack[i + 1][0] == tokEllipsis)
          continue;
      }

      printf2("%s : ", IdentTable + v);
      break;

    case '[':
      printf2("[");
      break;

    case tokNumInt:
      printf2("%d", truncInt(v));
      break;
    case tokNumUint:
      printf2("%uu", truncUint(v));
      break;

    case ']':
      printf2("] ");
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

        printf2("(");

        // Print the params (recursively)
        if (noparams)
        {
          // Don't recurse if it's "fxn()" or "fxn(void)"
          if (i + 1 != j)
            printf2("void");
        }
        else
        {
          puts2("");
          ParseLevel++;
          DumpDecl(i, 1);
          ParseLevel--;
        }

        // Continue normally
        i = j - 1;
        if (!noparams)
        {
          GenStartCommentLine();
          printf2("    ");
          {
            int j;
            for (j = 0; j < ParseLevel * 4; j++)
              printf2(" ");
          }
        }

        printf2(") ");
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
        printf2("%s\n", GetTokenName(tok));
        break;
      default:
        printf2("%s ", GetTokenName(tok));
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
  puts2("");
  GenStartCommentLine(); printf2("Syntax/declaration table/stack:\n");
  GenStartCommentLine(); printf2("Bytes used: %d/%d\n\n", used, total);
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
          puts2(DataHeader);
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
        GenStartCommentLine(); printf2("=\n");
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
              puts2(DataFooter);
          }
          else if (globalAllocSize == SizeOfWord && stack[sp - 1][0] == tokIdent)
          {
            char* p = IdentTable + stack[sp - 1][1];
            GenAddrData(globalAllocSize, p);
            if (OutputFormat != FormatFlat)
              puts2(DataFooter);
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
          puts2(DataFooter);
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
          puts2(CodeHeader);
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
          puts2(CodeFooter);
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
    GenStartCommentLine(); printf2("{\n");
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
    GenStartCommentLine(); printf2("}\n");
#endif
    tok = GetToken();
  }
  else if (tok == tokReturn)
  {
    // DONE: functions returning void vs non-void
#ifndef NO_ANNOTATIONS
    GenStartCommentLine(); printf2("return\n");
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
    GenStartCommentLine(); printf2("while\n");
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
    GenStartCommentLine(); printf2("do\n");
#endif
    GenNumLabel(labelBefore);

    tok = GetToken();
    brkCntSwchTarget[0] = labelAfter; // break target
    brkCntSwchTarget[1] = labelWhile; // continue target
    tok = ParseStatement(tok, brkCntSwchTarget, 0);
    if (tok != tokWhile)
      error("Error: ParseStatement(): 'while' expected after 'do statement'\n");

#ifndef NO_ANNOTATIONS
    GenStartCommentLine(); printf2("while\n");
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
    GenStartCommentLine(); printf2("if\n");
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
      GenStartCommentLine(); printf2("else\n");
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
    GenStartCommentLine(); printf2("for\n");
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
    GenStartCommentLine(); printf2("break\n");
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
    GenStartCommentLine(); printf2("continue\n");
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
    GenStartCommentLine(); printf2("switch\n");
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
    GenStartCommentLine(); printf2("case\n");
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
    GenStartCommentLine(); printf2("default\n");
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
    if (tok != tokLitStr)
      error("Error: ParseStatement(): string literal expression expected in 'asm ( expression )'\n");

    puts2(GetTokenValueString());

    tok = GetToken();
    if (tok != ')')
      error("Error: ParseStatement(): ')' expected after 'asm ( expression'\n");

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

#ifdef __SMALLER_C__
  DetermineVaListType();
#endif

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
#ifndef NO_PREPROCESSOR
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
#endif // #ifndef NO_PREPROCESSOR
    else if (FileCnt == 0)
    {
      // If it's none of the known options,
      // assume it's the source code file name
      if (strlen(argv[i]) > MAX_FILE_NAME_LEN)
        error("Error: File name too long\n");
      strcpy(FileNames[0], argv[i]);
      if ((Files[0] = fopen(FileNames[0], "r")) == NULL)
        error("Error: Cannot open file \"%s\"\n", FileNames[0]);
      LineNos[0] = LineNo;
      LinePoss[0] = LinePos;
      FileCnt++;
      continue;
    }  
    else if (FileCnt == 1 && OutFile == NULL)
    {
      // This should be the output file name
      if ((OutFile = fopen(argv[i], "w")) == NULL)
        error("Error: Cannot open output file \"%s\"\n", argv[i]);
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

#ifndef NO_PREPROCESSOR
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
#endif

  // When generating 32-bit assembly code with 16-bit compiler
  // output may be incorrect if constant subexpressions are folded
  // (because 32-bit constants get truncated to 16-bit).
  // Disable constant subexpression simplification if needed.
  canSimplify = !(SizeOfWord == 4 && sizeof(int) * CHAR_BIT < 32u);

  // populate CharQueue[] with the initial file characters
  ShiftChar();

  puts2(FileHeader);

  // compile
  ParseBlock(NULL, 0);

  DumpSynDecls();
#ifndef NO_PREPROCESSOR
  DumpMacroTable();
#endif
  DumpIdentTable();

  GenStartCommentLine(); printf2("Compilation succeeded.\n");

  if (OutFile != NULL)
    fclose(OutFile);

  return 0;
}
