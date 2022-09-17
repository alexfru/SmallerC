/*
Copyright (c) 2012-2020, Alexey Frunze
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
*/

/*****************************************************************************/
/*                                                                           */
/*                                 Smaller C                                 */
/*                                                                           */
/*                 A simple and small single-pass C compiler                 */
/*                                                                           */
/*            Produces 16/32-bit 80386 assembly output for NASM.             */
/*             Produces 32-bit MIPS assembly output for gcc/as.              */
/*                                                                           */
/*                                 Main file                                 */
/*                                                                           */
/*****************************************************************************/

// Making most functions static helps with code optimization,
// use that to further reduce compiler's code size on RetroBSD.
#ifndef STATIC
#define STATIC
#else
#undef STATIC
#define STATIC static
#endif

#ifdef NO_EXTRAS
#define NO_PPACK
#define NO_TYPEDEF_ENUM
#define NO_FUNC_
#define NO_EXTRA_WARNS
#define NO_FOR_DECL
#define NO_STRUCT_BY_VAL
#define NO_FP
#define NO_WCHAR
#endif

#ifndef __SMALLER_C__

#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#if UINT_MAX >= 0xFFFFFFFF
#define CAN_COMPILE_32BIT
#endif

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

#ifndef __SMALLER_C_SCHAR__
#ifndef __SMALLER_C_UCHAR__
#error __SMALLER_C_SCHAR__ or __SMALLER_C_UCHAR__ must be defined
#endif
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
#define CAN_COMPILE_32BIT
#endif

#ifndef __SMALLER_C_16__
#ifndef __SMALLER_C_32__
#error __SMALLER_C_16__ or __SMALLER_C_32__ must be defined
#endif
#endif

#define EXIT_FAILURE 1

void exit(int);
int atoi(char*);

size_t strlen(char*);
char* strcpy(char*, char*);
char* strchr(char*, int);
int strcmp(char*, char*);
int strncmp(char*, char*, size_t);
void* memmove(void*, void*, size_t);
void* memcpy(void*, void*, size_t);
void* memset(void*, int, size_t);
int memcmp(void*, void*, size_t);

int isspace(int);
int isdigit(int);
int isalpha(int);
int isalnum(int);

#define FILE void
#define EOF (-1)
FILE* fopen(char*, char*);
int fclose(FILE*);
int putchar(int);
int fputc(int, FILE*);
int fgetc(FILE*);
int puts(char*);
int fputs(char*, FILE*);
int sprintf(char*, char*, ...);
//int vsprintf(char*, char*, va_list);
int vsprintf(char*, char*, void*);
int printf(char*, ...);
int fprintf(FILE*, char*, ...);
//int vprintf(char*, va_list);
int vprintf(char*, void*);
//int vfprintf(FILE*, char*, va_list);
int vfprintf(FILE*, char*, void*);
struct fpos_t_
{
  union
  {
    unsigned short halves[2]; // for 16-bit memory models without 32-bit longs
    int align; // for alignment on machine word boundary
  } u;
}; // keep in sync with stdio.h !!!
#define fpos_t struct fpos_t_
int fgetpos(FILE*, fpos_t*);
int fsetpos(FILE*, fpos_t*);

#endif // #ifndef __SMALLER_C__

// Floating point requires 32 bits
#ifndef CAN_COMPILE_32BIT
#ifndef NO_FP
#define NO_FP
#endif
#endif

////////////////////////////////////////////////////////////////////////////////

// all public macros

#ifndef MAX_IDENT_LEN
#define MAX_IDENT_LEN        63
#endif

#ifndef MAX_STRING_LEN
#define MAX_STRING_LEN       255
#endif
#define MAX_CHAR_QUEUE_LEN   (MAX_STRING_LEN + 1)

#ifndef MAX_MACRO_TABLE_LEN
#define MAX_MACRO_TABLE_LEN  (4096+1024)
#endif

#ifndef MAX_IDENT_TABLE_LEN
#define MAX_IDENT_TABLE_LEN  (4096+1024+512) // must be greater than MAX_IDENT_LEN
#endif

#ifndef SYNTAX_STACK_MAX
#define SYNTAX_STACK_MAX (2048+1024)
#endif

#ifndef MAX_FILE_NAME_LEN
#define MAX_FILE_NAME_LEN    95
#endif

#ifndef NO_PREPROCESSOR
#define MAX_INCLUDES         8
#define PREP_STACK_SIZE      8
#define MAX_SEARCH_PATH      256
#else
#define MAX_INCLUDES         1
#define PREP_STACK_SIZE      1
#define MAX_SEARCH_PATH      1
#undef MAX_STRING_LEN
#define MAX_STRING_LEN       (MAX_FILE_NAME_LEN + 3)
#endif

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

#define tokSChar      0x80
#define tokUChar      0x81
#define tokUShort     0x82
#define tokULong      0x83
//#define tokLongLong   0x84
//#define tokULongLong  0x85
//#define tokLongDbl    0x86
#define tokGotoLabel  0x8F
#define tokStructPtr  0x90
#define tokTag        0x91
#define tokMemberIdent 0x92
#define tokEnumPtr    0x93
#define tokIntr       0x94
#define tokNumFloat   0x95
#define tokNumCharWide 0x96
#define tokLitStrWide 0x97

//#define FormatFlat      0
#define FormatSegmented 1
//#define FormatSegTurbo  2
#define FormatSegHuge   3
#define FormatSegUnreal 4

#define SymVoidSynPtr 0
#define SymIntSynPtr  1
#define SymUintSynPtr 2
#define SymWideCharSynPtr 3
#define SymFloatSynPtr 4
#define SymFuncPtr    5

#ifndef STACK_SIZE
#define STACK_SIZE 129
#endif

#define SymFxn       1
#define SymGlobalVar 2
#define SymGlobalArr 3
#define SymLocalVar  4
#define SymLocalArr  5

// all public prototypes
STATIC
unsigned truncUint(unsigned);
STATIC
int truncInt(int);

STATIC
int GetToken(void);
STATIC
char* GetTokenName(int token);

#ifndef NO_PREPROCESSOR
#ifndef NO_ANNOTATIONS
STATIC
void DumpMacroTable(void);
#endif
#endif

STATIC
int AddIdent(char* name);
STATIC
int FindIdent(char* name);
#ifndef NO_ANNOTATIONS
STATIC
void DumpIdentTable(void);
#endif
STATIC
char* lab2str(char* p, int n);

STATIC
void GenInit(void);
STATIC
void GenFin(void);
STATIC
int GenInitParams(int argc, char** argv, int* idx);
STATIC
void GenInitFinalize(void);
STATIC
void GenStartCommentLine(void);
STATIC
void GenWordAlignment(int bss);
STATIC
void GenLabel(char* Label, int Static);
STATIC
void GenNumLabel(int Label);
STATIC
void GenZeroData(unsigned Size, int bss);
STATIC
void GenIntData(int Size, int Val);
STATIC
void GenStartAsciiString(void);
STATIC
void GenAddrData(int Size, char* Label, int ofs);

STATIC
void GenJumpUncond(int Label);
STATIC
void GenJumpIfZero(int Label);
STATIC
void GenJumpIfNotZero(int Label);
STATIC
void GenJumpIfEqual(int val, int Label);

STATIC
void GenFxnProlog(void);
STATIC
void GenFxnEpilog(void);
void GenIsrProlog(void);
void GenIsrEpilog(void);

STATIC
int GenMaxLocalsSize(void);

STATIC
void GenDumpChar(int ch);
STATIC
void GenExpr(void);

STATIC
void PushSyntax(int t);
STATIC
void PushSyntax2(int t, int v);

#ifndef NO_ANNOTATIONS
STATIC
void DumpSynDecls(void);
#endif

STATIC
void push2(int v, int v2);
STATIC
void ins2(int pos, int v, int v2);
STATIC
void ins(int pos, int v);
STATIC
void del(int pos, int cnt);

STATIC
int TokenStartsDeclaration(int t, int params);
STATIC
int ParseDecl(int tok, unsigned structInfo[4], int cast, int label);

STATIC
void ShiftChar(void);
STATIC
int puts2(char*);
STATIC
int printf2(char*, ...);

STATIC
void error(char* format, ...);
STATIC
void warning(char* format, ...);
STATIC
void errorFile(char* n);
STATIC
void errorFileName(void);
STATIC
void errorInternal(int n);
STATIC
void errorChrStr(void);
#ifndef NO_WCHAR
STATIC
void errorWideNonWide(void);
#endif
STATIC
void errorStrLen(void);
STATIC
void errorUnexpectedToken(int tok);
STATIC
void errorDirective(void);
STATIC
void errorCtrlOutOfScope(void);
STATIC
void errorDecl(void);
STATIC
void errorVarSize(void);
STATIC
void errorInit(void);
STATIC
void errorUnexpectedVoid(void);
STATIC
void errorOpType(void);
STATIC
void errorNotLvalue(void);
STATIC
void errorNotConst(void);
STATIC
void errorLongExpr(void);
#ifndef NO_FP
STATIC
void warnFloat2Int(void);
#endif

STATIC
int FindSymbol(char* s);
STATIC
int SymType(int SynPtr);
STATIC
int FindTaggedDecl(char* s, int start, int* CurScope);
#ifndef NO_TYPEDEF_ENUM
STATIC
int FindTypedef(char* s);
#endif
STATIC
int GetDeclSize(int SyntaxPtr, int SizeForDeref);

STATIC
int ParseExpr(int tok, int* GotUnary, int* ExprTypeSynPtr, int* ConstExpr, int* ConstVal, int option, int option2);
STATIC
int GetFxnInfo(int ExprTypeSynPtr, int* MinParams, int* MaxParams, int* ReturnExprTypeSynPtr, int* FirstParamSynPtr);

// all data

int verbose = 0;
int warnings = 0;
int warnCnt = 0;

// prep.c data

// TBD!!! get rid of TokenIdentName[] and TokenValueString[]
// and work with CharQueue[] directly
int TokenValueInt = 0;
char TokenIdentName[MAX_IDENT_LEN + 1];
int TokenIdentNameLen = 0;
char TokenValueString[MAX_STRING_LEN + 1];
unsigned TokenStringLen = 0;
unsigned TokenStringSize = 0; // TokenStringLen * sizeof(char/wchar_t)
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
  Identifier table entry format:
    id char[idlen]: string (ASCIIZ)
    idlen char:     string length (<= 127)
*/
char IdentTable[MAX_IDENT_TABLE_LEN];
int IdentTableLen = 0;
int DummyIdent; // corresponds to empty string

#ifndef MAX_GOTO_LABELS
#define MAX_GOTO_LABELS 16
#endif
int gotoLabels[MAX_GOTO_LABELS][2];
// gotoLabStat[]: bit 1 = used (by "goto label;"), bit 0 = defined (with "label:")
char gotoLabStat[MAX_GOTO_LABELS];
int gotoLabCnt = 0;

#ifndef MAX_CASES
#define MAX_CASES 128
#endif
int Cases[MAX_CASES][2]; // [0] is case constant, [1] is case label number
int CasesCnt = 0;

// Data structures to support #include
int FileCnt = 0;
char FileNames[MAX_INCLUDES][MAX_FILE_NAME_LEN + 1];
FILE* Files[MAX_INCLUDES];
FILE* OutFile;
char CharQueues[MAX_INCLUDES][3];
int LineNos[MAX_INCLUDES];
int LinePoss[MAX_INCLUDES];
char SysSearchPaths[MAX_SEARCH_PATH];
int SysSearchPathsLen = 0;
char SearchPaths[MAX_SEARCH_PATH];
int SearchPathsLen = 0;

// Data structures to support #ifdef/#ifndef,#else,#endif
int PrepDontSkipTokens = 1;
int PrepStack[PREP_STACK_SIZE][2];
int PrepSp = 0;

// Data structures to support #pragma pack(...)
#ifndef NO_PPACK
#define PPACK_STACK_SIZE 16
int PragmaPackValue;
int PragmaPackValues[PPACK_STACK_SIZE];
int PragmaPackSp = 0;
#endif

// expr.c data

int ExprLevel = 0;

// TBD??? merge expression and operator stacks into one
int stack[STACK_SIZE][2];
int sp = 0;

#define OPERATOR_STACK_SIZE STACK_SIZE
int opstack[OPERATOR_STACK_SIZE][2];
int opsp = 0;

// smc.c data

int OutputFormat = FormatSegmented;
int GenExterns = 1;
int UseBss = 1;

// Names of C functions and variables are usually prefixed with an underscore.
// One notable exception is the ELF format used by gcc in Linux.
// Global C identifiers in the ELF format should not be predixed with an underscore.
int UseLeadingUnderscores = 1;

char* FileHeader = "";
char* CodeHeaderFooter[2] = { "", "" };
char* DataHeaderFooter[2] = { "", "" };
char* RoDataHeaderFooter[2] = { "", "" };
char* BssHeaderFooter[2] = { "", "" };
char** CurHeaderFooter;

int CharIsSigned = 1;
int SizeOfWord = 2; // in chars (char can be a multiple of octets); ints and pointers are of word size
int SizeOfWideChar = 2; // in chars/bytes, 2 or 4
int WideCharIsSigned = 0; // 0 or 1
int WideCharType1;
int WideCharType2; // (un)signed counterpart of WideCharType1

// TBD??? implement a function to allocate N labels with overflow checks
int LabelCnt = 1; // label counter for jumps
int StructCpyLabel = 0; // label of the function to copy structures/unions
int StructPushLabel = 0; // label of the function to push structures/unions onto the stack

// call stack (from higher to lower addresses):
//   arg n
//   ...
//   arg 1
//   return address
//   saved xbp register
//   local var 1
//   ...
//   local var n
int CurFxnSyntaxPtr = 0;
int CurFxnParamCntMin = 0;
int CurFxnParamCntMax = 0;
int CurFxnLocalOfs = 0; // negative
int CurFxnMinLocalOfs = 0; // negative

int CurFxnReturnExprTypeSynPtr = 0;
int CurFxnEpilogLabel = 0;

char* CurFxnName = NULL;
#ifndef NO_FUNC_
int CurFxnNameLabel = 0;
#endif
int IsMain; // if inside main()

int ParseLevel = 0; // Parse level/scope (file:0, fxn:1+)
int ParamLevel = 0; // 1+ if parsing params, 0 otherwise

unsigned char SyntaxStack0[SYNTAX_STACK_MAX];
int SyntaxStack1[SYNTAX_STACK_MAX];
int SyntaxStackCnt;

// all code

STATIC
unsigned truncUint(unsigned n)
{
  // Truncate n to SizeOfWord * 8 bits
  if (SizeOfWord == 2)
    n &= ~(~0u << 8 << 8);
#ifdef CAN_COMPILE_32BIT
  else if (SizeOfWord == 4)
    n &= ~(~0u << 8 << 12 << 12);
#endif
  return n;
}

STATIC
int truncInt(int n)
{
  // Truncate n to SizeOfWord * 8 bits and then sign-extend it
  unsigned un = n;
  if (SizeOfWord == 2)
  {
    un &= ~(~0u << 8 << 8);
    un |= (((un >> 8 >> 7) & 1) * ~0u) << 8 << 8;
  }
#ifdef CAN_COMPILE_32BIT
  else if (SizeOfWord == 4)
  {
    un &= ~(~0u << 8 << 12 << 12);
    un |= (((un >> 8 >> 12 >> 11) & 1) * ~0u) << 8 << 12 << 12;
  }
#endif
  return (int)un;
}

// prep.c code

#ifndef NO_PREPROCESSOR
STATIC
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

STATIC
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

STATIC
void AddMacroIdent(char* name)
{
  int l = strlen(name);

  if (l >= 127)
    error("Macro identifier too long '%s'\n", name);

  if (MAX_MACRO_TABLE_LEN - MacroTableLen < l + 3)
    error("Macro table exhausted\n");

  MacroTable[MacroTableLen++] = l + 1; // idlen
  strcpy(MacroTable + MacroTableLen, name);
  MacroTableLen += l + 1;

  MacroTable[MacroTableLen] = 0; // exlen
}

STATIC
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
    error("Macro table exhausted\n");

  if (MacroTable[MacroTableLen] >= 127)
    error("Macro definition too long\n");

  MacroTable[MacroTableLen + 1 + MacroTable[MacroTableLen]] = e;
  MacroTable[MacroTableLen]++;
}

STATIC
void DefineMacro(char* name, char* expansion)
{
  AddMacroIdent(name);
  do
  {
    AddMacroExpansionChar(*expansion);
  } while (*expansion++ != '\0');
}

#ifndef NO_ANNOTATIONS
STATIC
void DumpMacroTable(void)
{
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
}
#endif
#endif // #ifndef NO_PREPROCESSOR

STATIC
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

STATIC
int AddIdent(char* name)
{
  int i, len;

  if ((i = FindIdent(name)) >= 0)
    return i;

  i = IdentTableLen;
  len = strlen(name);

  if (len >= 127)
    error("Identifier too long\n");

  if (MAX_IDENT_TABLE_LEN - IdentTableLen < len + 2)
    error("Identifier table exhausted\n");

  strcpy(IdentTable + IdentTableLen, name);
  IdentTableLen += len + 1;
  IdentTable[IdentTableLen++] = len + 1;

  return i;
}

STATIC
int AddNumericIdent(int n)
{
  char s[1 + (2 + CHAR_BIT * sizeof n) / 3];
  char *p = s + sizeof s;
  *--p = '\0';
  p = lab2str(p, n);
  return AddIdent(p);
}

STATIC
int AddGotoLabel(char* name, int label)
{
  int i;
  for (i = 0; i < gotoLabCnt; i++)
  {
    if (!strcmp(IdentTable + gotoLabels[i][0], name))
    {
      if (gotoLabStat[i] & label)
        error("Redefinition of label '%s'\n", name);
      gotoLabStat[i] |= 2*!label + label;
      return gotoLabels[i][1];
    }
  }
  if (gotoLabCnt >= MAX_GOTO_LABELS)
    error("Goto table exhausted\n");
  gotoLabels[gotoLabCnt][0] = AddIdent(name);
  gotoLabels[gotoLabCnt][1] = LabelCnt++;
  gotoLabStat[gotoLabCnt] = 2*!label + label;
  return gotoLabels[gotoLabCnt++][1];
}

STATIC
void UndoNonLabelIdents(int len)
{
  int i;
  IdentTableLen = len;
  for (i = 0; i < gotoLabCnt; i++)
    if (gotoLabels[i][0] >= len)
    {
      char* pfrom = IdentTable + gotoLabels[i][0];
      char* pto = IdentTable + IdentTableLen;
      int l = strlen(pfrom) + 2;
      memmove(pto, pfrom, l);
      IdentTableLen += l;
      gotoLabels[i][0] = pto - IdentTable;
    }
}

STATIC
void AddCase(int val, int label)
{
  if (CasesCnt >= MAX_CASES)
    error("Case table exhausted\n");

  Cases[CasesCnt][0] = val;
  Cases[CasesCnt++][1] = label;
}

#ifndef NO_ANNOTATIONS
STATIC
void DumpIdentTable(void)
{
  int i;
  puts2("");
  GenStartCommentLine(); printf2("Identifier table:\n");
  for (i = 0; i < IdentTableLen; )
  {
    GenStartCommentLine(); printf2("Ident %s\n", IdentTable + i);
    i += strlen(IdentTable + i) + 2;
  }
  GenStartCommentLine(); printf2("Bytes used: %d/%d\n\n", IdentTableLen, MAX_IDENT_TABLE_LEN);
}
#endif

char* rws[] =
{
  "break", "case", "char", "continue", "default", "do", "else",
  "extern", "for", "if", "int", "return", "signed", "sizeof",
  "static", "switch", "unsigned", "void", "while", "asm", "auto",
  "const", "double", "enum", "float", "goto", "inline", "long",
  "register", "restrict", "short", "struct", "typedef", "union",
  "volatile", "_Bool", "_Complex", "_Imaginary",
  "__interrupt"
};

unsigned char rwtk[] =
{
  tokBreak, tokCase, tokChar, tokCont, tokDefault, tokDo, tokElse,
  tokExtern, tokFor, tokIf, tokInt, tokReturn, tokSigned, tokSizeof,
  tokStatic, tokSwitch, tokUnsigned, tokVoid, tokWhile, tok_Asm, tokAuto,
  tokConst, tokDouble, tokEnum, tokFloat, tokGoto, tokInline, tokLong,
  tokRegister, tokRestrict, tokShort, tokStruct, tokTypedef, tokUnion,
  tokVolatile, tok_Bool, tok_Complex, tok_Imagin,
  tokIntr
};

STATIC
int GetTokenByWord(char* word)
{
  unsigned i;

  for (i = 0; i < sizeof rws / sizeof rws[0]; i++)
    if (!strcmp(rws[i], word))
      return rwtk[i];

  return tokIdent;
}

unsigned char tktk[] =
{
  tokEof,
  // Single-character operators and punctuators:
  '+', '-', '~', '*', '/', '%', '&', '|', '^', '!',
  '<', '>', '(', ')', '[', ']',
  '{', '}', '=', ',', ';', ':', '.', '?',
  // Multi-character operators and punctuators:
  tokLShift, tokLogAnd, tokEQ, tokLEQ, tokInc, tokArrow, tokAssignMul,
  tokAssignMod, tokAssignSub, tokAssignRSh, tokAssignXor,
  tokRShift, tokLogOr, tokNEQ, tokGEQ, tokDec, tokEllipsis,
  tokAssignDiv, tokAssignAdd, tokAssignLSh, tokAssignAnd, tokAssignOr,
  // Some of the above tokens get converted into these in the process:
  tokUnaryAnd, tokUnaryPlus, tokPostInc, tokPostAdd,
  tokULess, tokULEQ, tokURShift, tokUDiv, tokUMod, tokComma,
  tokUnaryStar, tokUnaryMinus, tokPostDec, tokPostSub,
  tokUGreater, tokUGEQ, tokAssignURSh, tokAssignUDiv, tokAssignUMod,
  // Helper (pseudo-)tokens:
  tokNumInt, tokLitStr, tokLocalOfs, tokNumUint, tokIdent, tokShortCirc,
  tokSChar, tokShort, tokLong, tokUChar, tokUShort, tokULong, tokNumFloat,
  tokNumCharWide, tokLitStrWide
};

char* tks[] =
{
  "<EOF>",
  // Single-character operators and punctuators:
  "+", "-", "~", "*", "/", "%", "&", "|", "^", "!",
  "<", ">", "(", ")", "[", "]",
  "{", "}", "=", ",", ";", ":", ".", "?",
  // Multi-character operators and punctuators:
  "<<", "&&", "==", "<=", "++", "->", "*=",
  "%=", "-=", ">>=", "^=",
  ">>", "||", "!=", ">=", "--", "...",
  "/=", "+=", "<<=", "&=", "|=",
  // Some of the above tokens get converted into these in the process:
  "&u", "+u", "++p", "+=p",
  "<u", "<=u", ">>u", "/u", "%u", ",b",
  "*u", "-u", "--p", "-=p",
  ">u", ">=u", ">>=u", "/=u", "%=u",
  // Helper (pseudo-)tokens:
  "<NumInt>",  "<LitStr>", "<LocalOfs>", "<NumUint>", "<Ident>", "<ShortCirc>",
  "signed char", "short", "long", "unsigned char", "unsigned short", "unsigned long", "float",
  "<NumCharWide>", "<LitStrWide>"
};

STATIC
char* GetTokenName(int token)
{
  unsigned i;

/* +-~* /% &|^! << >> && || < <= > >= == !=  () *[] ++ -- = += -= ~= *= /= %= &= |= ^= <<= >>= {} ,;: -> ... */

  // Tokens other than reserved keywords:
  for (i = 0; i < sizeof tktk / sizeof tktk[0]; i++)
    if (tktk[i] == token)
      return tks[i];

  // Reserved keywords:
  for (i = 0; i < sizeof rws / sizeof rws[0]; i++)
    if (rwtk[i] == token)
      return rws[i];

  //error("Internal Error: GetTokenName(): Invalid token %d\n", token);
  errorInternal(1);
  return "";
}

STATIC
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

STATIC
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

STATIC
void ShiftCharN(int n)
{
  while (n-- > 0)
  {
    ShiftChar();
    LinePos++;
  }
}

#ifndef NO_PREPROCESSOR
STATIC
void IncludeFile(int quot)
{
  int nlen = strlen(TokenValueString);

  if (CharQueueLen != 3)
    //error("#include parsing error\n");
    errorInternal(2);

  if (FileCnt >= MAX_INCLUDES)
    error("Too many include files\n");

  // store the including file's position and buffered chars
  LineNos[FileCnt - 1] = LineNo;
  LinePoss[FileCnt - 1] = LinePos;
  memcpy(CharQueues[FileCnt - 1], CharQueue, CharQueueLen);

  // open the included file

  if (nlen > MAX_FILE_NAME_LEN)
    //error("File name too long\n");
    errorFileName();

  // DONE: differentiate between quot == '"' and quot == '<'

  // First, try opening "file" in the current directory
  // (Open Watcom C/C++ 1.9, Turbo C++ 1.01 use the current directory,
  // unlike gcc, which uses the same directory as the current file)
  if (quot == '"')
  {
    strcpy(FileNames[FileCnt], TokenValueString);
    Files[FileCnt] = fopen(FileNames[FileCnt], "r");
  }

  // Next, iterate the search paths trying to open "file" or <file>.
  // "file" is first searched using the list provided by the -I option.
  // "file" is then searched using the list provided by the -SI option.
  // <file> is searched using the list provided by the -SI option.
  if (Files[FileCnt] == NULL)
  {
    int i;
    char *paths = SearchPaths;
    int pl = SearchPathsLen;
    for (;;)
    {
      if (quot == '<')
      {
        paths = SysSearchPaths;
        pl = SysSearchPathsLen;
      }
      for (i = 0; i < pl; )
      {
        int plen = strlen(paths + i);
        if (plen + 1 + nlen < MAX_FILE_NAME_LEN)
        {
          strcpy(FileNames[FileCnt], paths + i);
          strcpy(FileNames[FileCnt] + plen + 1, TokenValueString);
          // Use '/' as a separator, typical for Linux/Unix,
          // but also supported by file APIs in DOS/Windows just as '\\'
          FileNames[FileCnt][plen] = '/';
          if ((Files[FileCnt] = fopen(FileNames[FileCnt], "r")) != NULL)
            break;
        }
        i += plen + 1;
      }
      if (Files[FileCnt] || quot == '<')
        break;
      quot = '<';
    }
  }

  if (Files[FileCnt] == NULL)
  {
    //error("Cannot open file \"%s\"\n", TokenValueString);
    errorFile(TokenValueString);
  }

  // reset line/pos and empty the char queue
  CharQueueLen = 0;
  LineNo = LinePos = 1;
  FileCnt++;

  // fill the char queue with file data
  ShiftChar();
}
#endif // #ifndef NO_PREPROCESSOR

STATIC
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

STATIC
void SkipSpace(int SkipNewLines)
{
  char* p = CharQueue;

  while (*p != '\0')
  {
    if (strchr(" \t\f\v", *p))
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

#ifndef NO_PREPROCESSOR
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
              error("Invalid comment\n");

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
          error("Invalid comment\n");
        ShiftCharN(2);
        continue;
      }
    } // endof if (*p == '/')
#endif

    break;
  } // endof while (*p != '\0')
}

#ifndef NO_PREPROCESSOR
STATIC
void SkipLine(void)
{
  char* p = CharQueue;

  while (*p != '\0')
  {
    if (strchr("\r\n", *p))
    {
      if (*p == '\r' && p[1] == '\n')
        ShiftChar();

      ShiftChar();
      LineNo++;
      LinePos = 1;
      break;
    }
    else
    {
      ShiftCharN(1);
    }
  }
}
#endif

STATIC
void GetIdent(void)
{
  char* p = CharQueue;

  if (*p != '_' && !isalpha(*p & 0xFFu))
    error("Identifier expected\n");

#ifdef NO_WCHAR
  if (*p == 'L' &&
      (p[1] == '\'' || p[1] == '"'))
    //error("Wide characters and strings not supported\n");
    errorChrStr();
#endif

  TokenIdentNameLen = 0;
  TokenIdentName[TokenIdentNameLen++] = *p;
  TokenIdentName[TokenIdentNameLen] = '\0';
  ShiftCharN(1);

  while (*p == '_' || isalnum(*p & 0xFFu))
  {
    if (TokenIdentNameLen == MAX_IDENT_LEN)
      error("Identifier too long '%s'\n", TokenIdentName);
    TokenIdentName[TokenIdentNameLen++] = *p;
    TokenIdentName[TokenIdentNameLen] = '\0';
    ShiftCharN(1);
  }
}

STATIC
unsigned GetCharValue(int wide)
{
  char* p = CharQueue;
  unsigned ch = 0;
  int cnt = 0;
#ifdef NO_WCHAR
  (void)wide;
#endif
  if (*p == '\\')
  {
    ShiftCharN(1);
    if (strchr("\n\r", *p))
      goto lerr;
    if (*p == 'x')
    {
      // hexadecimal character codes \xN+
      // hexadecimal escape sequence is not limited in length per se
      // (may have many leading zeroes)
      static char digs[] = "0123456789ABCDEFabcdef";
      static char vals[] =
      {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
        10, 11, 12, 13, 14, 15,
        10, 11, 12, 13, 14, 15
      };
      char* pp;
      int zeroes = 0;
      ShiftCharN(1);
      if (strchr("\n\r", *p))
        goto lerr;
      if (*p == '0')
      {
        do
        {
          ShiftCharN(1);
        } while (*p == '0');
        zeroes = 1;
      }
      while (*p && (pp = strchr(digs, *p)) != NULL)
      {
        ch <<= 4;
        ch |= vals[pp - digs];
        ShiftCharN(1);
#ifndef NO_WCHAR
        if (++cnt > (wide ? SizeOfWideChar * 2 : 2))
#else
        if (++cnt > 2)
#endif
        {
          if (PrepDontSkipTokens)
            goto lerr;
        }
      }
      if (zeroes + cnt == 0)
        goto lerr;
    }
    else if (*p >= '0' && *p <= '7')
    {
      // octal character codes \N+
      // octal escape sequence is terminated after three octal digits
      do
      {
        ch <<= 3;
        ch |= *p - '0';
        ShiftCharN(1);
        ++cnt;
      } while (*p >= '0' && *p <= '7' && cnt < 3);
      if (ch >> 8)
        goto lerr;
    }
    else
    {
      switch (*p)
      {
      case 'a': ch = '\a'; ShiftCharN(1); break;
      case 'b': ch = '\b'; ShiftCharN(1); break;
      case 'f': ch = '\f'; ShiftCharN(1); break;
      case 'n': ch = '\n'; ShiftCharN(1); break;
      case 'r': ch = '\r'; ShiftCharN(1); break;
      case 't': ch = '\t'; ShiftCharN(1); break;
      case 'v': ch = '\v'; ShiftCharN(1); break;
      default:
        goto lself;
      }
    }
  }
  else
  {
lself:
    if (strchr("\n\r", *p))
    {
lerr:
      //error("Unsupported or invalid character/string constant\n");
      errorChrStr();
    }
    ch = *p & 0xFFu;
#ifndef NO_WCHAR
    if (wide && ch > 0x7F && PrepDontSkipTokens)
      error("Only ASCII chars supported as wide chars\n");
#endif
    ShiftCharN(1);
  }
  return ch;
}

STATIC
void GetString(char terminator, int wide, int option)
{
  char* p = CharQueue;
  unsigned ch = '\0';
#ifndef NO_WCHAR
  unsigned chsz = wide ? SizeOfWideChar : 1;
#else
  unsigned chsz = 1;
#endif
  int i;

  TokenStringLen = 0;
  TokenStringSize = 0;
  TokenValueString[TokenStringLen] = '\0';

  ShiftCharN(1);
  while (!(*p == terminator || strchr("\n\r", *p)))
  {
    ch = GetCharValue(wide);
    switch (option)
    {
    case '#': // string literal (with file name) for #line and #include
      if (TokenStringLen == MAX_STRING_LEN)
        errorStrLen();
      TokenValueString[TokenStringLen++] = ch;
      TokenValueString[TokenStringLen] = '\0';
      TokenStringSize += chsz;
      break;
    case 'a': // string literal for asm()
      printf2("%c", ch);
      break;
    case 'd': // string literal / array of char in expression or initializer
      // Dump the char data to the appropriate data section
      for (i = 0; i < chsz; i++)
      {
        GenDumpChar(ch & 0xFFu);
        ch >>= 8;
        TokenStringLen++; // GenDumpChar() expects it to grow, doesn't know about wchar_t
      }
      TokenStringLen -= chsz;
      // fallthrough
    default: // skipped string literal (we may still need the size)
      if (TokenStringSize > UINT_MAX - chsz)
        errorStrLen();
      TokenStringSize += chsz;
      TokenStringLen++;
      break;
    } // endof switch (option)
  } // endof while (!(*p == '\0' || *p == terminator || strchr("\n\r", *p)))

  if (*p != terminator)
    //error("Unsupported or invalid character/string constant\n");
    errorChrStr();

  if (option == 'd')
    GenDumpChar(-1);

  ShiftCharN(1);

  SkipSpace(option != '#');
}

#ifndef NO_PREPROCESSOR
STATIC
void pushPrep(int NoSkip)
{
  if (PrepSp >= PREP_STACK_SIZE)
    error("Too many #if(n)def's\n");
  PrepStack[PrepSp][0] = PrepDontSkipTokens;
  PrepStack[PrepSp++][1] = NoSkip;
  PrepDontSkipTokens &= NoSkip;
}

STATIC
int popPrep(void)
{
  if (PrepSp <= 0)
    error("#else or #endif without #if(n)def\n");
  PrepDontSkipTokens = PrepStack[--PrepSp][0];
  return PrepStack[PrepSp][1];
}
#endif

#ifndef NO_FP
#include "fp.c"

#define FXNI2F    0
#define FXNU2F    1
#define FXNF2I    2
#define FXNF2U    3
#define FXNFADD   4
#define FXNFSUB   5
#define FXNFNEG   6
#define FXNFMUL   7
#define FXNFDIV   8
#define FXNFCMPL  9
#define FXNFCMPG 10
// Names of external functions for floating point arithmetic
char* FpFxnName[] =
{
  /*FXNI2F  */ "__floatsisf",
  /*FXNU2F  */ "__floatunsisf",
  /*FXNF2I  */ "__fixsfsi",
  /*FXNF2U  */ "__fixunssfsi",
  /*FXNFADD */ "__addsf3",
  /*FXNFSUB */ "__subsf3",
  /*FXNFNEG */ "__negsf2",
  /*FXNFMUL */ "__mulsf3",
  /*FXNFDIV */ "__divsf3",
  /*FXNFCMPL*/ "__lesf2",
  /*FXNFCMPG*/ "__gesf2"
};
#endif

STATIC
int GetNumber(void)
{
  char* p = CharQueue;
  int ch = *p;
  int leadingZero = (ch == '0');
  unsigned n = 0;
  int type = 0;
  int uSuffix = 0;
#ifdef CAN_COMPILE_32BIT
  int lSuffix = 0;
#endif
#ifndef NO_FP
  int mcnt = 0, eexp = 0;
#endif
  char* eTooBig = "Constant too big\n";

  // First, detect and handle hex constants. Octals can't be detected immediately
  // because floating-point constants also may begin with the digit 0.

  if (leadingZero && (p[1] == 'x' || p[1] == 'X'))
  {
    // this is a hex constant
    int cnt = 0;
    type = 'h';
    ShiftCharN(1);
    ShiftCharN(1);
    while ((ch = *p) != '\0' && (isdigit(ch & 0xFFu) || strchr("abcdefABCDEF", ch)))
    {
      if (ch >= 'a') ch -= 'a' - 10;
      else if (ch >= 'A') ch -= 'A' - 10;
      else ch -= '0';
      if (PrepDontSkipTokens && (n * 16 / 16 != n || n * 16 + ch < n * 16))
        error(eTooBig);
      n = n * 16 + ch;
      ShiftCharN(1);
      cnt++;
    }
    if (!cnt)
      error("Invalid hexadecimal constant\n");
  }
#ifndef NO_FP
  else
  {
    // this is a decimal (possibly floating-point) or an octal constant, parse as decimal
    int mexp = 0, dot = 0;
    int ecnt = 0;
    type = 'd';
    // skip leading zeroes, if any
    while (*p == '0')
      ShiftCharN(1);
    // get digits of integral part, if any
    while (isdigit((ch = *p) & 0xFFu))
    {
      if (mcnt < MAX_CONST_DIGITS)
        ConstDigits[mcnt++] = ch - '0';
      else
        mexp++; // TBD??? overflow
      ShiftCharN(1);
    }
    // get dot and digits of fractional part, if any
    if (*p == '.')
    {
      dot = 1;
      ShiftCharN(1);
      // if the integral part is 0, skip leading zeroes in the fractional part, if any
      if (!mcnt)
        while (*p == '0')
          ShiftCharN(1), mexp--; // TBD??? overflow
      while (isdigit((ch = *p) & 0xFFu))
      {
        if (mcnt < MAX_CONST_DIGITS)
          ConstDigits[mcnt++] = ch - '0';
        mexp--; // TBD??? overflow
        ShiftCharN(1);
      }
    }
    // get exponent part, if any
    if (*p == 'e' || *p == 'E')
    {
      int esign = '+';
      ShiftCharN(1);
      if (*p == '+' || *p == '-')
        esign = *p, ShiftCharN(1);
      while (isdigit((ch = *p) & 0xFFu))
      {
        ch -= '0';
        if (n * 10 / 10 != n ||
            n * 10 + ch < n * 10 ||
            n * 10 + ch > UINT_MAX / 2)
        {
          if (PrepDontSkipTokens)
            error(eTooBig);
          n = 0;
        }
        n = n * 10 + ch;
        ShiftCharN(1);
        ecnt++;
      }
      if (!ecnt)
        error("Invalid float constant\n");
      eexp = n;
      if (esign == '-')
        eexp = -eexp;
    }
    if (dot || ecnt)
    {
      // this is a float constant (has either a dot or an exponent)
      // get float suffix, if any
      type = 'f';
      if (*p == 'f' || *p == 'F' || *p == 'l' || *p == 'L')
        ShiftCharN(1);
      // also drop trailing zeroes, if any
      while (mcnt)
      {
        if (ConstDigits[mcnt - 1])
          break;
        mexp++; // TBD??? overflow
        mcnt--;
      }
      if (!mcnt)
        ConstDigits[mcnt++] = 0, mexp = 0;
      if ((mexp >= 0 && eexp > INT_MAX - mexp) ||
          (mexp < 0 && eexp <= INT_MIN - (mexp + 1)))
      {
        if (PrepDontSkipTokens)
          error(eTooBig);
      }
      else
        eexp += mexp;
    }
    else
    {
      // handle decimal and octal integers
      int base = leadingZero ? 8 : 10;
      int i;
      type = leadingZero ? 'o' : 'd';
      for (i = 0; i < mcnt; i++)
      {
        ch = ConstDigits[i];
        if (ch >= base)
          error("Invalid octal constant\n");
        if (PrepDontSkipTokens && (n * base / base != n || n * base + ch < n * base))
          error(eTooBig);
        n = n * base + ch;
      }
    }
  }
#else
  else
  {
    // handle decimal and octal integers
    int base = leadingZero ? 8 : 10;
    type = leadingZero ? 'o' : 'd';
    while ((ch = *p) >= '0' && ch < base + '0')
    {
      ch -= '0';
      if (PrepDontSkipTokens && (n * base / base != n || n * base + ch < n * base))
        error(eTooBig);
      n = n * base + ch;
      ShiftCharN(1);
    }
  }
#endif

  // possible combinations of integer suffixes:
  //   none
  //   U
  //   UL
  //   L
  //   LU
#ifndef NO_FP
  if (type != 'f')
#endif
  {
    if ((ch = *p) == 'u' || ch == 'U')
    {
      uSuffix = 1;
      ShiftCharN(1);
    }
#ifdef CAN_COMPILE_32BIT
    if ((ch = *p) == 'l' || ch == 'L')
    {
      lSuffix = 1;
      ShiftCharN(1);
      if (!uSuffix && ((ch = *p) == 'u' || ch == 'U'))
      {
        uSuffix = 1;
        ShiftCharN(1);
      }
    }
#endif
  }

  if (!PrepDontSkipTokens)
  {
    // Don't fail on big constants when skipping tokens under #if
    TokenValueInt = 0;
    return tokNumInt;
  }

#ifndef NO_FP
  if (type == 'f')
  {
    TokenValueInt = d2f(ConstDigits, mcnt, eexp);
    return tokNumFloat;
  }
#endif

  // Ensure the constant fits into 16(32) bits
  if (
      (SizeOfWord == 2 && n >> 8 >> 8) // equiv. to SizeOfWord == 2 && n > 0xFFFF
#ifdef CAN_COMPILE_32BIT
      || (SizeOfWord == 2 && lSuffix) // long (which must have at least 32 bits) isn't supported in 16-bit models
      || (SizeOfWord == 4 && n >> 8 >> 12 >> 12) // equiv. to SizeOfWord == 4 && n > 0xFFFFFFFF
#endif
     )
    error("Constant too big for %d-bit type\n", SizeOfWord * 8);

  TokenValueInt = (int)n;

  // Unsuffixed (with 'u') integer constants (octal, decimal, hex)
  // fitting into 15(31) out of 16(32) bits are signed ints
  if (!uSuffix &&
      (
       (SizeOfWord == 2 && !(n >> 15)) // equiv. to SizeOfWord == 2 && n <= 0x7FFF
#ifdef CAN_COMPILE_32BIT
       || (SizeOfWord == 4 && !(n >> 8 >> 12 >> 11)) // equiv. to SizeOfWord == 4 && n <= 0x7FFFFFFF
#endif
      )
     )
    return tokNumInt;

  // Unlike octal and hex constants, decimal constants are always
  // a signed type. Error out when a decimal constant doesn't fit
  // into an int since currently there's no next bigger signed type
  // (e.g. long) to use instead of int.
  if (!uSuffix && type == 'd')
    error("Constant too big for %d-bit signed type\n", SizeOfWord * 8);

  return tokNumUint;
}

STATIC
int GetTokenInner(void)
{
  char* p = CharQueue;
  int ch = *p;
  int wide = 0;

  // these single-character tokens/operators need no further processing
  if (strchr(",;:()[]{}~?", ch))
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
#ifndef NO_FP
    if (isdigit(p[1] & 0xFFu)) { return GetNumber(); }
#endif
    ShiftCharN(1); return ch;
  case '*':
    if (p[1] == '=') { ShiftCharN(2); return tokAssignMul; }
    ShiftCharN(1); return ch;
  case '%':
    if (p[1] == '=') { ShiftCharN(2); return tokAssignMod; }
    ShiftCharN(1); return ch;
  case '/':
    if (p[1] == '=') { ShiftCharN(2); return tokAssignDiv; }
    ShiftCharN(1); return ch;
  }

  // DONE: hex and octal constants
  if (isdigit(ch & 0xFFu))
    return GetNumber();

  // parse character and string constants
#ifndef NO_WCHAR
  if (ch == 'L' && (p[1] == '\'' || p[1] == '"'))
  {
    wide = 1; ShiftCharN(1); ch = *p;
  }
#endif
  if (ch == '\'')
  {
    unsigned v = 0;
    int cnt = 0;
#ifndef NO_WCHAR
    int max_cnt = wide ? 1 : SizeOfWord;
#else
    int max_cnt = SizeOfWord;
#endif
    ShiftCharN(1);
    if (strchr("'\n\r", *p))
      //error("Character constant too short\n");
      errorChrStr();
    do
    {
      v <<= 8;
      v |= GetCharValue(wide);
      if (++cnt > max_cnt)
        //error("Character constant too long\n");
        errorChrStr();
    } while (!strchr("'\n\r", *p));
    if (*p != '\'')
      //error("Unsupported or invalid character/string constant\n");
      errorChrStr();
    ShiftCharN(1);
#ifndef NO_WCHAR
    if (wide)
    {
      TokenValueInt = v;
#ifdef CAN_COMPILE_32BIT
      TokenValueInt -= (WideCharIsSigned && SizeOfWideChar == 2 &&
                        TokenValueInt >= 0x8000) * 0x10000;
#endif
      return tokNumCharWide;
    }
    else
#endif
    {
      if (cnt == 1)
      {
        TokenValueInt = v;
        TokenValueInt -= (CharIsSigned && TokenValueInt >= 0x80) * 0x100;
      }
      else
      {
        TokenValueInt = v;
#ifdef CAN_COMPILE_32BIT
        TokenValueInt -= (SizeOfWord == 2 && TokenValueInt >= 0x8000) * 0x10000;
#endif
      }
      return tokNumInt;
    }
  }
  else if (ch == '"')
  {
    // The caller of GetTokenInner()/GetToken() will call GetString('"', wide, 'd')
    // to complete string literal parsing and storing as appropriate
#ifndef NO_WCHAR
    return wide ? tokLitStrWide : tokLitStr;
#else
    return tokLitStr;
#endif
  }

  return tokEof;
}

#ifndef NO_PREPROCESSOR
STATIC
void Reserve4Expansion(char* name, int len)
{
  if (MAX_CHAR_QUEUE_LEN - CharQueueLen < len + 1)
    error("Too long expansion of macro '%s'\n", name);

  memmove(CharQueue + len + 1, CharQueue, CharQueueLen);

  CharQueue[len] = ' '; // space to avoid concatenation

  CharQueueLen += len + 1;
}
#endif

// TBD??? implement file I/O for input source code and output code (use fxn ptrs/wrappers to make librarization possible)
// DONE: support string literals
STATIC
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
      if (tok == tokLitStr)
        GetString('"', 0, 0);
#ifndef NO_WCHAR
      else if (tok == tokLitStrWide)
        GetString('"', 1, 0);
#endif
      continue;
    }

    // parse identifiers and reserved keywords
    if (ch == '_' || isalpha(ch & 0xFFu))
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
      if (!strcmp(TokenIdentName, "__FILE__"))
      {
        char* p = FileNames[FileCnt - 1];
        int len = strlen(p);
        Reserve4Expansion(TokenIdentName, len + 2);
        *CharQueue = '"';
        memcpy(CharQueue + 1, p, len);
        CharQueue[len + 1] = '"';
        continue;
      }
      else if (!strcmp(TokenIdentName, "__LINE__"))
      {
        char s[(2 + CHAR_BIT * sizeof LineNo) / 3];
        char *p = lab2str(s + sizeof s, LineNo);
        int len = s + sizeof s - p;
        Reserve4Expansion(TokenIdentName, len);
        memcpy(CharQueue, p, len);
        continue;
      }
      else if ((midx = FindMacro(TokenIdentName)) >= 0)
      {
        // this is a macro identifier, need to expand it
        int len = MacroTable[midx];
        Reserve4Expansion(TokenIdentName, len);
        memcpy(CharQueue, MacroTable + midx + 1, len);
        continue;
      }
#endif

      // treat keywords auto, const, register, restrict and volatile as white space for now
      if ((tok == tokConst) | (tok == tokVolatile) |
          (tok == tokAuto) | (tok == tokRegister) |
          (tok == tokRestrict))
        continue;

      return tok;
    } // endof if (ch == '_' || isalpha(ch))

    // parse preprocessor directives
    if (ch == '#')
    {
      int line = 0;

      ShiftCharN(1);

      // Skip space
      SkipSpace(0);

      // Allow # not followed by a directive
      if (strchr("\r\n", *p))
        continue;

      // Get preprocessor directive
      if (isdigit(*p & 0xFFu))
      {
        // gcc-style #line directive without "line"
        line = 1;
      }
      else
      {
        GetIdent();
        if (!strcmp(TokenIdentName, "line"))
        {
          // C89-style #line directive
          SkipSpace(0);
          if (!isdigit(*p & 0xFFu))
            errorDirective();
          line = 1;
        }
      }

      if (line)
      {
        // Support for external, gcc-like, preprocessor output:
        //   # linenum filename flags
        //
        // no flags, flag = 1 -- start of a file
        //           flag = 2 -- return to a file after #include
        //        other flags -- uninteresting

        // DONE: should also support the following C89 form:
        // # line linenum filename-opt

        if (GetNumber() != tokNumInt)
          //error("Invalid line number in preprocessor output\n");
          errorDirective();
        line = TokenValueInt;

        SkipSpace(0);

        if (*p == '"' || *p == '<')
        {
          if (*p == '"')
            GetString('"', 0, '#');
          else
            GetString('>', 0, '#');

          if (strlen(TokenValueString) > MAX_FILE_NAME_LEN)
            //error("File name too long in preprocessor output\n");
            errorFileName();
          strcpy(FileNames[FileCnt - 1], TokenValueString);
        }

        // Ignore gcc-style #line's flags, if any
        while (!strchr("\r\n", *p))
          ShiftCharN(1);

        LineNo = line - 1; // "line" is the number of the next line
        LinePos = 1;

        continue;
      } // endof if (line)

#ifndef NO_PPACK
      if (!strcmp(TokenIdentName, "pragma"))
      {
        int canHaveNumber = 1, hadNumber = 0;

        if (!PrepDontSkipTokens)
        {
          while (!strchr("\r\n", *p))
            ShiftCharN(1);
          continue;
        }

        SkipSpace(0);
        GetIdent();
        if (strcmp(TokenIdentName, "pack"))
          errorDirective();
        // TBD??? fail if inside a structure declaration
        SkipSpace(0);
        if (*p == '(')
          ShiftCharN(1);
        SkipSpace(0);

        if (*p == 'p')
        {
          GetIdent();
          if (!strcmp(TokenIdentName, "push"))
          {
            SkipSpace(0);
            if (*p == ',')
            {
              ShiftCharN(1);
              SkipSpace(0);
              if (!isdigit(*p & 0xFFu) || GetNumber() != tokNumInt)
                errorDirective();
              hadNumber = 1;
            }
            if (PragmaPackSp >= PPACK_STACK_SIZE)
              error("#pragma pack stack overflow\n");
            PragmaPackValues[PragmaPackSp++] = PragmaPackValue;
          }
          else if (!strcmp(TokenIdentName, "pop"))
          {
            if (PragmaPackSp <= 0)
              error("#pragma pack stack underflow\n");
            PragmaPackValue = PragmaPackValues[--PragmaPackSp];
          }
          else
            errorDirective();
          SkipSpace(0);
          canHaveNumber = 0;
        }

        if (canHaveNumber && isdigit(*p & 0xFFu))
        {
          if (GetNumber() != tokNumInt)
            errorDirective();
          hadNumber = 1;
          SkipSpace(0);
        }

        if (hadNumber)
        {
          PragmaPackValue = TokenValueInt;
          if (PragmaPackValue <= 0 ||
              PragmaPackValue > SizeOfWord ||
              PragmaPackValue & (PragmaPackValue - 1))
            error("Invalid alignment value\n");
        }
        else if (canHaveNumber)
        {
          PragmaPackValue = SizeOfWord;
        }

        if (*p != ')')
          errorDirective();
        ShiftCharN(1);

        SkipSpace(0);
        if (!strchr("\r\n", *p))
          errorDirective();
        continue;
      }
#endif

#ifndef NO_PREPROCESSOR
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
          error("Redefinition of macro '%s'\n", TokenIdentName);
        if (*p == '(')
          //error("Unsupported type of macro '%s'\n", TokenIdentName);
          errorDirective();

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
          //error("Invalid preprocessor directive\n");
          errorDirective();
        continue;
      }
      else if (!strcmp(TokenIdentName, "include"))
      {
        int quot;

        // Skip space and get file name
        SkipSpace(0);

        quot = *p;
        if (*p == '"')
          GetString('"', 0, '#');
        else if (*p == '<')
          GetString('>', 0, '#');
        else
          //error("Invalid file name\n");
          errorFileName();

        SkipSpace(0);
        if (!strchr("\r\n", *p))
          //error("Unsupported or invalid preprocessor directive\n");
          errorDirective();

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
          //error("Invalid preprocessor directive\n");
          errorDirective();
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
          //error("Invalid preprocessor directive\n");
          errorDirective();
        pushPrep(!def);
        continue;
      }
      else if (!strcmp(TokenIdentName, "else"))
      {
        int def;
        SkipSpace(0);
        if (!strchr("\r\n", *p))
          //error("Invalid preprocessor directive\n");
          errorDirective();
        def = popPrep();
        if (def >= 2)
          error("#else or #endif without #if(n)def\n");
        pushPrep(2 + !def); // #else works in opposite way to its preceding #if(n)def
        continue;
      }
      else if (!strcmp(TokenIdentName, "endif"))
      {
        SkipSpace(0);
        if (!strchr("\r\n", *p))
          //error("Invalid preprocessor directive\n");
          errorDirective();
        popPrep();
        continue;
      }

      if (!PrepDontSkipTokens)
      {
        // If skipping code and directives under #ifdef/#ifndef/#else,
        // ignore unsupported directives #if, #elif, #error (no error checking)
        if (!strcmp(TokenIdentName, "if"))
          pushPrep(0);
        else if (!strcmp(TokenIdentName, "elif"))
          popPrep(), pushPrep(0);
        SkipLine();
        continue;
      }
#endif // #ifndef NO_PREPROCESSOR

      //error("Unsupported or invalid preprocessor directive\n");
      errorDirective();
    } // endof if (ch == '#')

    error("Invalid or unsupported character with code 0x%02X\n", *p & 0xFFu);
  } // endof for (;;)

  return tokEof;
}

STATIC
void errorRedecl(char* s)
{
  error("Invalid or unsupported redeclaration of '%s'\n", s);
}

#ifdef MIPS
  #ifndef CAN_COMPILE_32BIT
    #error MIPS target requires a 32-bit compiler
  #endif
  #include "cgmips.c"
#else
  #include "cgx86.c"
#endif // #ifdef MIPS

// expr.c code

STATIC
void push2(int v, int v2)
{
  if (sp >= STACK_SIZE)
    //error("expression stack overflow!\n");
    errorLongExpr();
  stack[sp][0] = v;
  stack[sp++][1] = v2;
}

STATIC
void push(int v)
{
  push2(v, 0);
}

STATIC
int stacktop()
{
  if (sp == 0)
    //error("expression stack underflow!\n");
    errorInternal(3);
  return stack[sp - 1][0];
}

STATIC
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

STATIC
void ins2(int pos, int v, int v2)
{
  if (sp >= STACK_SIZE)
    //error("expression stack overflow!\n");
    errorLongExpr();
  memmove(&stack[pos + 1], &stack[pos], sizeof(stack[0]) * (sp - pos));
  stack[pos][0] = v;
  stack[pos][1] = v2;
  sp++;
}

STATIC
void ins(int pos, int v)
{
  ins2(pos, v, 0);
}

STATIC
void del(int pos, int cnt)
{
  memmove(stack[pos],
          stack[pos + cnt],
          sizeof(stack[0]) * (sp - (pos + cnt)));
  sp -= cnt;
}

#ifndef NO_FP
STATIC
void rev(int pos, int cnt)
{
  // reverse cnt items at pos on the stack
  int (*p1)[2] = stack + pos, (*p2)[2] = p1 + cnt - 1;
  while (p1 < p2)
  {
    int t0 = **p1;
    int t1 = (*p1)[1];
    **p1 = **p2;
    (*p1++)[1] = (*p2)[1];
    **p2 = t0;
    (*p2--)[1] = t1;
  }
}

STATIC
void swap(int pos, int cntlo, int cnthi)
{
  // swap cntlo items at pos with cnthi items at pos + cntlo
  rev(pos, cntlo);
  rev(pos + cntlo, cnthi);
  rev(pos, cntlo + cnthi);
}
#endif

STATIC
void pushop2(int v, int v2)
{
  if (opsp >= OPERATOR_STACK_SIZE)
    //error("operator stack overflow!\n");
    errorLongExpr();
  opstack[opsp][0] = v;
  opstack[opsp++][1] = v2;
}

STATIC
void pushop(int v)
{
  pushop2(v, 0);
}

STATIC
int opstacktop()
{
  if (opsp == 0)
    //error("operator stack underflow!\n");
    errorInternal(4);
  return opstack[opsp - 1][0];
}

STATIC
int popop2(int* v2)
{
  int v = opstacktop();
  *v2 = opstack[opsp - 1][1];
  opsp--;
  return v;
}

STATIC
int popop()
{
  int v2;
  return popop2(&v2);
}

STATIC
int isop(int tok)
{
  static unsigned char toks[] =
  {
    '!',
    '~',
    '&',
    '*',
    '/', '%',
    '+', '-',
    '|', '^',
    '<', '>',
    '=',
    tokLogOr, tokLogAnd,
    tokEQ, tokNEQ,
    tokLEQ, tokGEQ,
    tokLShift, tokRShift,
    tokInc, tokDec,
    tokSizeof,
    tokAssignMul, tokAssignDiv, tokAssignMod,
    tokAssignAdd, tokAssignSub,
    tokAssignLSh, tokAssignRSh,
    tokAssignAnd, tokAssignXor, tokAssignOr,
    tokComma,
    '?'
  };
  unsigned i;
  for (i = 0; i < sizeof toks / sizeof toks[0]; i++)
    if (toks[i] == tok)
      return 1;
  return 0;
}

STATIC
int isunary(int tok)
{
  return (tok == '!') | (tok == '~') | (tok == tokInc) | (tok == tokDec) | (tok == tokSizeof);
}

STATIC
int preced(int tok)
{
  switch (tok)
  {
  case '*': case '/': case '%': return 13;
  case '+': case '-': return 12;
  case tokLShift: case tokRShift: return 11;
  case '<': case '>': case tokLEQ: case tokGEQ: return 10;
  case tokEQ: case tokNEQ: return 9;
  case '&': return 8;
  case '^': return 7;
  case '|': return 6;
  case tokLogAnd: return 5;
  case tokLogOr: return 4;
  case '?': case ':': return 3;
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

STATIC
int precedGEQ(int lfttok, int rhttok)
{
  // DONE: rethink the comma operator as it could be implemented similarly
  // DONE: is this correct:???
  int pl = preced(lfttok);
  int pr = preced(rhttok);
  // ternary/conditional operator ?: is right-associative
  if (pl == 3 && pr >= 3)
    pl = 0;
  // assignment is right-associative
  if (pl == 2 && pr >= 2)
    pl = 0;
  return pl >= pr;
}

STATIC
int expr(int tok, int* gotUnary, int commaSeparator);

STATIC
char* lab2str(char* p, int n)
{
  do
  {
    *--p = '0' + n % 10;
    n /= 10;
  } while (n);

  return p;
}

STATIC
int exprUnary(int tok, int* gotUnary, int commaSeparator, int argOfSizeOf)
{
  static int sizeofLevel = 0;

  int decl = 0;
  *gotUnary = 0;

  if (isop(tok) && (isunary(tok) || strchr("&*+-", tok)))
  {
    int lastTok = tok;
    int sizeofLevelInc = lastTok == tokSizeof;

    sizeofLevel += sizeofLevelInc;
    tok = exprUnary(GetToken(), gotUnary, commaSeparator, sizeofLevelInc);
    sizeofLevel -= sizeofLevelInc;

    if (!*gotUnary)
      //error("exprUnary(): primary expression expected after token %s\n", GetTokenName(lastTok));
      errorUnexpectedToken(tok);
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
      push(tokNumInt);
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

    if (tok == tokNumInt ||
#ifndef NO_FP
        tok == tokNumFloat ||
#endif
#ifndef NO_WCHAR
        tok == tokNumCharWide ||
#endif
        tok == tokNumUint)
    {
      push2(tok, TokenValueInt);
      *gotUnary = 1;
      tok = GetToken();
    }
    else if (tok == tokLitStr
#ifndef NO_WCHAR
             || tok == tokLitStrWide
#endif
            )
    {
      int lbl = LabelCnt++;
      int id;
      int ltok = tok;
#ifndef NO_WCHAR
      int wide = tok == tokLitStrWide;
      unsigned chsz = wide ? SizeOfWideChar : 1;
#else
      int wide = 0;
      unsigned chsz = 1;
#endif
      unsigned sz = chsz;

      // imitate definition: char #[len] = "...";

      if (!sizeofLevel)
      {
        if (CurHeaderFooter)
          puts2(CurHeaderFooter[1]);
        puts2(RoDataHeaderFooter[0]);

#ifndef NO_WCHAR
        if (wide)
          GenWordAlignment(0);
#endif
        GenNumLabel(lbl);
      }

      do
      {
        GetString('"', wide, sizeofLevel ? 0 : 'd'); // throw away string data inside sizeof, e.g. sizeof "a" or sizeof("a" + 1)
        if (sz + TokenStringSize < sz ||
            sz + TokenStringSize >= truncUint(-1))
          errorStrLen();
        sz += TokenStringSize;
        tok = GetToken();
      } while (tok == ltok); // concatenate adjacent string literals

#ifndef NO_WCHAR
      if ((ltok ^ (tokLitStr ^ tokLitStrWide)) == tok)
        errorWideNonWide();
#endif

      if (!sizeofLevel)
      {
        GenZeroData(chsz, 0);

        puts2(RoDataHeaderFooter[1]);
        if (CurHeaderFooter)
          puts2(CurHeaderFooter[0]);
      }

      // DONE: can this break incomplete yet declarations???, e.g.: int x[sizeof("az")][5];
      PushSyntax2(tokIdent, id = AddNumericIdent(lbl));
      PushSyntax('[');
      PushSyntax2(tokNumUint, sz / chsz);
      PushSyntax(']');
#ifndef NO_WCHAR
      PushSyntax(wide ? WideCharType1 : tokChar);
#else
      PushSyntax(tokChar);
#endif

      push2(tokIdent, id);
      *gotUnary = 1;
    }
    else if (tok == tokIdent)
    {
      push2(tok, AddIdent(TokenIdentName));
      *gotUnary = 1;
      tok = GetToken();
    }
    else if (tok == '(')
    {
      tok = GetToken();
      decl = TokenStartsDeclaration(tok, 1);

      if (decl)
      {
        int synPtr;
        int lbl = LabelCnt++;
        char s[1 + (2 + CHAR_BIT * sizeof lbl) / 3 + sizeof "<something>" - 1];
        char *p = s + sizeof s;

        tok = ParseDecl(tok, NULL, !argOfSizeOf, 0);
        if (tok != ')')
          //error("exprUnary(): ')' expected, unexpected token %s\n", GetTokenName(tok));
          errorUnexpectedToken(tok);
        synPtr = FindSymbol("<something>");

        // Rename "<something>" to "<something#>", where # is lbl.
        // This makes the nameless declaration uniquely identifiable by name.

        *--p = '\0';
        *--p = ")>"[argOfSizeOf]; // differentiate casts (something#) from not casts <something#>

        p = lab2str(p, lbl);

        p -= sizeof "<something>" - 2 - 1;
        memcpy(p, "something", sizeof "something" - 1);

        *--p = "(<"[argOfSizeOf]; // differentiate casts (something#) from not casts <something#>

        SyntaxStack1[synPtr] = AddIdent(p);
        tok = GetToken();
        if (argOfSizeOf)
        {
          // expression: sizeof(type)
          *gotUnary = 1;
        }
        else
        {
          // unary type cast operator: (type)
          decl = 0;
          tok = exprUnary(tok, gotUnary, commaSeparator, 0);
          if (!*gotUnary)
            //error("exprUnary(): primary expression expected after '(type)'\n");
            errorUnexpectedToken(tok);
        }
        push2(tokIdent, SyntaxStack1[synPtr]);
      }
      else
      {
        tok = expr(tok, gotUnary, 0);
        if (tok != ')')
          //error("exprUnary(): ')' expected, unexpected token %s\n", GetTokenName(tok));
          errorUnexpectedToken(tok);
        if (!*gotUnary)
          //error("exprUnary(): primary expression expected in '()'\n");
          errorUnexpectedToken(tok);
        tok = GetToken();
      }
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

      if (tok == '(')
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
              //error("exprUnary(): primary expression (fxn argument) expected before ','\n");
              errorUnexpectedToken(tok);
            acnt++;
            ins(inspos + 1, ','); // helper argument separator (hint for expression evaluator)
            continue; // off to next arg
          }
          if (tok == ')')
          {
            if (acnt && !*gotUnary)
              //error("exprUnary(): primary expression (fxn argument) expected between ',' and ')'\n");
              errorUnexpectedToken(tok);
            *gotUnary = 1; // don't fail for 0 args in ()
            break; // end of args
          }
          // DONE: think of inserting special arg pseudo tokens for verification purposes
          //error("exprUnary(): ',' or ')' expected, unexpected token %s\n", GetTokenName(tok));
          errorUnexpectedToken(tok);
        } // endof for(;;) for fxn args
        push(')');
      }
      else if (tok == '[')
      {
        tok = GetToken();
        tok = expr(tok, gotUnary, 0);
        if (!*gotUnary)
          //error("exprUnary(): primary expression expected in '[]'\n");
          errorUnexpectedToken(tok);
        if (tok != ']')
          //error("exprUnary(): ']' expected, unexpected token %s\n", GetTokenName(tok));
          errorUnexpectedToken(tok);
        // TBD??? add implicit casts to size_t of array indicies.
        // E1[E2] -> *(E1 + E2)
        // push('[');
        push('+');
        push(tokUnaryStar);
      }
      // WRONG: DONE: replace postfix ++/-- with (+=1)-1/(-=1)+1
      else if (tok == tokInc)
      {
        push(tokPostInc);
      }
      else if (tok == tokDec)
      {
        push(tokPostDec);
      }
      else if (tok == '.' || tok == tokArrow)
      {
        // transform a.b into (&a)->b
        if (tok == '.')
          push(tokUnaryAnd);
        tok = GetToken();
        if (tok != tokIdent)
          errorUnexpectedToken(tok);
        push2(tok, AddIdent(TokenIdentName));
        // "->" in "a->b" will function as "+" in "*(type_of_b*)((char*)a + offset_of_b_in_a)"
        push(tokArrow);
        push(tokUnaryStar);
      }
      else
      {
        break;
      }
      tok = GetToken();
    } // endof while (*gotUnary)
  }

  if (tok == ',' && !commaSeparator)
    tok = tokComma;

  return tok;
}

STATIC
int expr(int tok, int* gotUnary, int commaSeparator)
{
  *gotUnary = 0;
  pushop(tokEof);

  tok = exprUnary(tok, gotUnary, commaSeparator, 0);

  while (tok != tokEof && strchr(",;:)]}", tok) == NULL && *gotUnary)
  {
    if (isop(tok) && !isunary(tok))
    {
      while (precedGEQ(opstacktop(), tok))
      {
        int v, v2;
        v = popop2(&v2);
        // move ?expr: as a whole to the expression stack as "expr?"
        if (v == '?')
        {
          int cnt = v2;
          while (cnt--)
          {
            v = popop2(&v2);
            push2(v, v2);
          }
          v = '?';
          v2 = 0;
        }
        push2(v, v2);
      }

      // here: preced(postacktop()) < preced(tok)

      // treat the ternary/conditional operator ?expr: as a pseudo binary operator
      if (tok == '?')
      {
        int ssp = sp;
        int cnt;

        tok = expr(GetToken(), gotUnary, 0);
        if (!*gotUnary || tok != ':')
          errorUnexpectedToken(tok);

        // move ?expr: as a whole to the operator stack
        // this is beautiful and ugly at the same time
        cnt = sp - ssp;
        while (sp > ssp)
        {
          int v, v2;
          v = pop2(&v2);
          pushop2(v, v2);
        }

        // remember the length of the expression between ? and :
        pushop2('?', cnt);
      }
      else
      {
        pushop(tok);
      }

      tok = exprUnary(GetToken(), gotUnary, commaSeparator, 0);
      // DONE: figure out a check to see if exprUnary() fails to add a rhs operand
      if (!*gotUnary)
        //error("expr(): primary expression expected after token %s\n", GetTokenName(lastTok));
        errorUnexpectedToken(tok);

      continue;
    }

    //error("expr(): Unexpected token %s\n", GetTokenName(tok));
    errorUnexpectedToken(tok);
  }

  while (opstacktop() != tokEof)
  {
    int v, v2;
    v = popop2(&v2);
    // move ?expr: as a whole to the expression stack as "expr?"
    if (v == '?')
    {
      int cnt = v2;
      while (cnt--)
      {
        v = popop2(&v2);
        push2(v, v2);
      }
      v = '?';
      v2 = 0;
    }
    push2(v, v2);
  }

  popop();
  return tok;
}

STATIC
int isAnyPtr(int ExprTypeSynPtr)
{
  if (ExprTypeSynPtr < 0)
    return 1;
  switch (SyntaxStack0[ExprTypeSynPtr])
  {
  case '*':
  case '[':
  case '(':
    return 1;
  }
  return 0;
}

STATIC
int derefAnyPtr(int ExprTypeSynPtr)
{
  if (ExprTypeSynPtr < 0)
    return -ExprTypeSynPtr;
  switch (SyntaxStack0[ExprTypeSynPtr])
  {
  case '*':
    return ExprTypeSynPtr + 1;
  case '[':
    return ExprTypeSynPtr + 3;
  case '(':
    return ExprTypeSynPtr;
  }
  errorInternal(22);
  return -1;
}

STATIC
void decayArray(int* ExprTypeSynPtr, int arithmetic)
{
  // Dacay arrays to pointers to their first elements
  if (*ExprTypeSynPtr >= 0 && SyntaxStack0[*ExprTypeSynPtr] == '[')
  {
    (*ExprTypeSynPtr) += 3;
    // we cannot insert another '*' into the type to make it a pointer
    // to the first element, so make the index into the type negative
    *ExprTypeSynPtr = -*ExprTypeSynPtr;
  }

  // DONE: disallow arithmetic on pointers to void
  // DONE: disallow function pointers
  if (arithmetic && isAnyPtr(*ExprTypeSynPtr))
  {
    int pointee = derefAnyPtr(*ExprTypeSynPtr);
    switch (SyntaxStack0[pointee])
    {
    case tokVoid:
      //error("decayArray(): cannot do pointer arithmetic on a pointer to 'void'\n");
      errorUnexpectedVoid();
    default:
      //error("decayArray(): cannot do pointer arithmetic on a pointer to an incomplete type\n");
      if (!GetDeclSize(pointee, 0))
      // "fallthrough"
    case '(':
        //error("decayArray(): cannot do pointer arithmetic on a pointer to a function\n");
        errorOpType();
    }
  }
}

STATIC
void lvalueCheck(int ExprTypeSynPtr, int pos)
{
  if (ExprTypeSynPtr >= 0 &&
      (SyntaxStack0[ExprTypeSynPtr] == '[' || SyntaxStack0[ExprTypeSynPtr] == '('))
  {
    // we can have arrays formed by dereference, e.g.
    //   char (*pac)[1]; // *pac is array of 1 char
    //                   // ++*pac or (*pac)-- are not allowed
    // and likewise functions, e.g.
    //   int (*pf)(int); // *pf is a function taking int and returning int
    //                   // *pf = 0; is not allowed
    // and that dereference shouldn't be confused for lvalue,
    // hence explicitly checking for array and function types
    //error("exprval(): lvalue expected\n");
    errorNotLvalue();
  }
  // lvalue is a dereferenced address, check for a dereference
  if (stack[pos][0] != tokUnaryStar)
    //error("exprval(): lvalue expected\n");
    errorNotLvalue();
}

STATIC
void nonVoidTypeCheck(int ExprTypeSynPtr)
{
  if (ExprTypeSynPtr >= 0 && SyntaxStack0[ExprTypeSynPtr] == tokVoid)
    //error("nonVoidTypeCheck(): unexpected operand type 'void' for operator '%s'\n", GetTokenName(tok));
    errorUnexpectedVoid();
}

STATIC
void scalarTypeCheck(int ExprTypeSynPtr)
{
  nonVoidTypeCheck(ExprTypeSynPtr);

  if (ExprTypeSynPtr >= 0 && SyntaxStack0[ExprTypeSynPtr] == tokStructPtr)
    errorOpType();
}

STATIC
void numericTypeCheck(int ExprTypeSynPtr)
{
  if (ExprTypeSynPtr >= 0)
    switch (SyntaxStack0[ExprTypeSynPtr])
    {
    case tokChar:
    case tokSChar:
    case tokUChar:
#ifdef CAN_COMPILE_32BIT
    case tokShort:
    case tokUShort:
#endif
    case tokInt:
    case tokUnsigned:
#ifndef NO_FP
    case tokFloat:
#endif
      return;
    }
  //error("numericTypeCheck(): unexpected operand type for operator '%s', numeric type expected\n", GetTokenName(tok));
  errorOpType();
}

#ifndef NO_FP
STATIC
void nonFloatTypeCheck(int ExprTypeSynPtr)
{
  if (ExprTypeSynPtr >= 0 && SyntaxStack0[ExprTypeSynPtr] == tokFloat)
    errorOpType();
}
#endif

STATIC
void anyIntTypeCheck(int ExprTypeSynPtr)
{
  // Check for any integer type
  numericTypeCheck(ExprTypeSynPtr);
#ifndef NO_FP
  nonFloatTypeCheck(ExprTypeSynPtr);
#endif
}

#ifndef NO_FP
STATIC
int isFloat(int ExprTypeSynPtr)
{
  return ExprTypeSynPtr >= 0 && SyntaxStack0[ExprTypeSynPtr] == tokFloat;
}
#endif

STATIC
int isUint(int ExprTypeSynPtr)
{
  return ExprTypeSynPtr >= 0 && SyntaxStack0[ExprTypeSynPtr] == tokUnsigned;
}

STATIC
void compatCheck(int* ExprTypeSynPtr, int TheOtherExprTypeSynPtr, int ConstExpr[2], int lidx, int ridx)
{
  int exprTypeSynPtr = *ExprTypeSynPtr;
  int c = 0;
  int lptr, rptr, lnum, rnum;

  // (un)decay/convert functions to pointers to functions
  // and to simplify matters convert all '*' pointers to negative type indices
  if (exprTypeSynPtr >= 0)
  {
    switch (SyntaxStack0[exprTypeSynPtr])
    {
    case '*':
      exprTypeSynPtr++;
      // fallthrough
    case '(':
      exprTypeSynPtr = -exprTypeSynPtr;
    }
    *ExprTypeSynPtr = exprTypeSynPtr;
  }
  if (TheOtherExprTypeSynPtr >= 0)
  {
    switch (SyntaxStack0[TheOtherExprTypeSynPtr])
    {
    case '*':
      TheOtherExprTypeSynPtr++;
      // fallthrough
    case '(':
      TheOtherExprTypeSynPtr = -TheOtherExprTypeSynPtr;
    }
  }
  lptr = exprTypeSynPtr < 0;
  rptr = TheOtherExprTypeSynPtr < 0;
  lnum = !lptr && (SyntaxStack0[exprTypeSynPtr] == tokInt ||
#ifndef NO_FP
                   SyntaxStack0[exprTypeSynPtr] == tokFloat ||
#endif
                   SyntaxStack0[exprTypeSynPtr] == tokUnsigned);
  rnum = !rptr && (SyntaxStack0[TheOtherExprTypeSynPtr] == tokInt ||
#ifndef NO_FP
                   SyntaxStack0[TheOtherExprTypeSynPtr] == tokFloat ||
#endif
                   SyntaxStack0[TheOtherExprTypeSynPtr] == tokUnsigned);

  // both operands have arithmetic type
  // (arithmetic operands have been already promoted):
  if (lnum && rnum)
    return;

  // both operands have void type:
  if (!lptr && SyntaxStack0[exprTypeSynPtr] == tokVoid &&
      !rptr && SyntaxStack0[TheOtherExprTypeSynPtr] == tokVoid)
    return;

  // one operand is a pointer and the other is NULL constant
  // ((void*)0 is also a valid null pointer constant),
  // the type of the expression is that of the pointer:
  if (lptr &&
      ((rnum && ConstExpr[1] && truncInt(stack[ridx][1]) == 0) ||
       (rptr && SyntaxStack0[-TheOtherExprTypeSynPtr] == tokVoid &&
        (stack[ridx][0] == tokNumInt || stack[ridx][0] == tokNumUint) &&
        truncInt(stack[ridx][1]) == 0)))
    return;
  if (rptr &&
      ((lnum && ConstExpr[0] && truncInt(stack[lidx][1]) == 0) ||
       (lptr && SyntaxStack0[-exprTypeSynPtr] == tokVoid &&
        (stack[lidx][0] == tokNumInt || stack[lidx][0] == tokNumUint) &&
        truncInt(stack[lidx][1]) == 0)))
  {
    *ExprTypeSynPtr = TheOtherExprTypeSynPtr;
    return;
  }

  // not expecting non-pointers beyond this point
  if (!(lptr && rptr))
    errorOpType();

  // one operand is a pointer and the other is a pointer to void
  // (except (void*)0 (AKA NULL), which is different from other pointers to void),
  // the type of the expression is pointer to void:
  if (SyntaxStack0[-exprTypeSynPtr] == tokVoid)
    return;
  if (SyntaxStack0[-TheOtherExprTypeSynPtr] == tokVoid)
  {
    *ExprTypeSynPtr = TheOtherExprTypeSynPtr;
    return;
  }

  // both operands are pointers to compatible types:

  if (exprTypeSynPtr == TheOtherExprTypeSynPtr)
    return;

  exprTypeSynPtr = -exprTypeSynPtr;
  TheOtherExprTypeSynPtr = -TheOtherExprTypeSynPtr;

  for (;;)
  {
    int tok = SyntaxStack0[exprTypeSynPtr];
    if (tok != SyntaxStack0[TheOtherExprTypeSynPtr])
      errorOpType();

    if (tok != tokIdent &&
        SyntaxStack1[exprTypeSynPtr] != SyntaxStack1[TheOtherExprTypeSynPtr])
      errorOpType();

    c += (tok == '(') - (tok == ')') + (tok == '[') - (tok == ']');

    if (!c)
    {
      switch (tok)
      {
      case tokVoid:
      case tokChar: case tokSChar: case tokUChar:
#ifdef CAN_COMPILE_32BIT
      case tokShort: case tokUShort:
#endif
      case tokInt: case tokUnsigned:
#ifndef NO_FP
      case tokFloat:
#endif
      case tokStructPtr:
        return;
      }
    }

    exprTypeSynPtr++;
    TheOtherExprTypeSynPtr++;
  }
}

STATIC
void shiftCountCheck(int *psr, int idx, int ExprTypeSynPtr)
{
  int sr = *psr;
  // can't shift by a negative count and by a count exceeding
  // the number of bits in int
  if ((SyntaxStack0[ExprTypeSynPtr] != tokUnsigned && sr < 0) ||
      (unsigned)sr >= CHAR_BIT * sizeof(int) ||
      (unsigned)sr >= 8u * SizeOfWord)
  {
    //error("exprval(): Invalid shift count\n");
    warning("Shift count out of range\n");
    // truncate the count, so the assembler doesn't get an invalid count
    sr &= SizeOfWord * 8 - 1;
    *psr = sr;
    stack[idx][1] = sr;
  }
}

STATIC
int divCheckAndCalc(int tok, int* psl, int sr, int Unsigned, int ConstExpr[2])
{
  int div0 = 0;
  int sl = *psl;

  if (!ConstExpr[1])
    return !div0;

  if (Unsigned)
  {
    sl = (int)truncUint(sl);
    sr = (int)truncUint(sr);
  }
  else
  {
    sl = truncInt(sl);
    sr = truncInt(sr);
  }

  if (sr == 0)
  {
    div0 = 1;
  }
  else if (!ConstExpr[0])
  {
    return !div0;
  }
  else if (!Unsigned && ((sl == INT_MIN && sr == -1) || sl / sr != truncInt(sl / sr)))
  {
    div0 = 1;
  }
  else
  {
    if (Unsigned)
    {
      if (tok == '/')
        sl = (int)((unsigned)sl / sr);
      else
        sl = (int)((unsigned)sl % sr);
    }
    else
    {
      // TBD!!! C89 gives freedom in how exactly division of negative integers
      // can be implemented w.r.t. rounding and w.r.t. the sign of the remainder.
      // A stricter, C99-conforming implementation, non-dependent on the
      // compiler used to compile Smaller C is needed.
      if (tok == '/')
        sl /= sr;
      else
        sl %= sr;
    }
    *psl = sl;
  }

  if (div0)
    warning("Division by 0 or division overflow\n");

  return !div0;
}

STATIC
void promoteType(int* ExprTypeSynPtr, int* TheOtherExprTypeSynPtr)
{
  // Integer promotion to signed int or unsigned int from smaller types
  // (all kinds of char and short). Promotion to unsigned int occurs
  // only if the other operand (of a binary operator) is already an
  // unsigned int. Effectively, this promotion to unsigned int performs
  // usual arithmetic conversion for integers.
  if (*ExprTypeSynPtr >= 0)
  {
    // chars must be promoted to ints in expressions as the very first thing
    switch (SyntaxStack0[*ExprTypeSynPtr])
    {
    case tokChar:
#ifdef CAN_COMPILE_32BIT
    case tokShort:
    case tokUShort:
#endif
    case tokSChar:
    case tokUChar:
      *ExprTypeSynPtr = SymIntSynPtr;
    }
    if (*TheOtherExprTypeSynPtr >= 0)
    {
      // ints must be converted to unsigned ints if they are used in binary
      // operators whose other operand is unsigned int (except <<,>>,<<=,>>=)
      if (SyntaxStack0[*ExprTypeSynPtr] == tokInt &&
          SyntaxStack0[*TheOtherExprTypeSynPtr] == tokUnsigned)
        *ExprTypeSynPtr = SymUintSynPtr;
    }
  }
}

STATIC
int GetFxnInfo(int ExprTypeSynPtr, int* MinParams, int* MaxParams, int* ReturnExprTypeSynPtr, int* FirstParamSynPtr)
{
  *MaxParams = *MinParams = 0;

  if (ExprTypeSynPtr < 0)
  {
    ExprTypeSynPtr = -ExprTypeSynPtr;
  }
  else
  {
    while (SyntaxStack0[ExprTypeSynPtr] == tokIdent || SyntaxStack0[ExprTypeSynPtr] == tokLocalOfs)
      ExprTypeSynPtr++;
    if (SyntaxStack0[ExprTypeSynPtr] == '*')
      ExprTypeSynPtr++;
  }

  if (SyntaxStack0[ExprTypeSynPtr] != '(')
    return 0;

  // DONE: return syntax pointer to the function's return type

  // Count params

  ExprTypeSynPtr++;

  if (FirstParamSynPtr)
    *FirstParamSynPtr = ExprTypeSynPtr;

  if (SyntaxStack0[ExprTypeSynPtr] == ')')
  {
    // "fxn()": unspecified parameters, so, there can be any number of them
    *MaxParams = 32767; // INT_MAX;
    *ReturnExprTypeSynPtr = ExprTypeSynPtr + 1;
    return 1;
  }

  if (SyntaxStack0[ExprTypeSynPtr + 1] == tokVoid)
  {
    // "fxn(void)": 0 parameters
    *ReturnExprTypeSynPtr = ExprTypeSynPtr + 3;
    return 1;
  }

  for (;;)
  {
    int tok = SyntaxStack0[ExprTypeSynPtr];

    if (tok == tokIdent)
    {
      if (SyntaxStack0[ExprTypeSynPtr + 1] != tokEllipsis)
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
        tok = SyntaxStack0[++ExprTypeSynPtr];
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

STATIC
void simplifyConstExpr(int val, int isConst, int* ExprTypeSynPtr, int top, int bottom)
{
  // If non-const, nothing to do.
  // If const and already a number behind the scenes, nothing to do
  // (val must not differ from the number!).
  if (!isConst || stack[top][0] == tokNumInt || stack[top][0] == tokNumUint)
    return;

  // Const, but not a number yet. Reduce to a number equal val.
  if (SyntaxStack0[*ExprTypeSynPtr] == tokUnsigned)
    stack[top][0] = tokNumUint;
  else
    stack[top][0] = tokNumInt;
  stack[top][1] = val;

  del(bottom, top - bottom);
}

STATIC
int AllocLocal(unsigned size)
{
  // Let's calculate variable's relative on-stack location
  int oldOfs = CurFxnLocalOfs;

  // Note: local vars are word-aligned on the stack
  CurFxnLocalOfs = (int)((CurFxnLocalOfs - size) & ~(SizeOfWord - 1u));
  if (CurFxnLocalOfs >= oldOfs ||
      CurFxnLocalOfs != truncInt(CurFxnLocalOfs) ||
      CurFxnLocalOfs < -GenMaxLocalsSize())
    //error("AllocLocal(): Local variables take too much space\n");
    errorVarSize();

  if (CurFxnMinLocalOfs > CurFxnLocalOfs)
    CurFxnMinLocalOfs = CurFxnLocalOfs;

  return CurFxnLocalOfs;
}

// DONE: sizeof(type)
// DONE: "sizeof expr"
// DONE: constant expressions
// DONE: collapse constant subexpressions into constants
STATIC
int exprval(int* idx, int* ExprTypeSynPtr, int* ConstExpr)
{
  int tok;
  int s;
  int RightExprTypeSynPtr;
  int oldIdxRight;
  int oldSpRight;
  int constExpr[3];

  if (*idx < 0)
    //error("exprval(): idx < 0\n");
    errorInternal(5);

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
#ifndef NO_WCHAR
  case tokNumCharWide:
    // recode tokNumCharWide to tokNumInt to minimize changes in the CGs
    stack[*idx + 1][0] = tokNumInt;
    // return the constant's type: wchar_t
    *ExprTypeSynPtr = SymWideCharSynPtr;
    *ConstExpr = 1;
    break;
#endif
#ifndef NO_FP
  case tokNumFloat:
    // recode tokNumFloat to tokNumInt to minimize changes in the CGs
    stack[*idx + 1][0] = tokNumInt;
    // return the constant's type: float
    *ExprTypeSynPtr = SymFloatSynPtr;
    *ConstExpr = 1;
    break;
#endif

  // Identifiers
  case tokIdent:
    {
      // DONE: support __func__
      char* ident = IdentTable + s;
      int synPtr, type;
#ifndef NO_FUNC_
      if (CurFxnName && !strcmp(ident, "__func__"))
      {
        if (CurFxnNameLabel >= 0)
          CurFxnNameLabel = -CurFxnNameLabel;
        stack[*idx + 1][1] = SyntaxStack1[SymFuncPtr];
        synPtr = SymFuncPtr;
      }
      else
#endif
      {
        synPtr = FindSymbol(ident);
        // "Rename" static vars in function scope
        if (synPtr >= 0 && synPtr + 1 < SyntaxStackCnt && SyntaxStack0[synPtr + 1] == tokIdent)
        {
          s = stack[*idx + 1][1] = SyntaxStack1[++synPtr];
          ident = IdentTable + s;
        }
      }

      if (synPtr < 0)
      {
        if ((*idx + 2 >= sp) || stack[*idx + 2][0] != ')')
          error("Undeclared identifier '%s'\n", ident);
        else
        {
          warning("Call to undeclared function '%s()'\n", ident);
          // Implicitly declare "extern int ident();"
          PushSyntax2(tokIdent, s);
          PushSyntax('(');
          PushSyntax(')');
          PushSyntax(tokInt);
          synPtr = FindSymbol(ident);
        }
      }

#ifndef NO_TYPEDEF_ENUM
      if (synPtr + 1 < SyntaxStackCnt &&
          SyntaxStack0[synPtr + 1] == tokNumInt)
      {
        // this is an enum constant
        stack[*idx + 1][0] = tokNumInt;
        s = stack[*idx + 1][1] = SyntaxStack1[synPtr + 1];
        *ExprTypeSynPtr = SymIntSynPtr;
        *ConstExpr = 1;
        break;
      }
#endif

      // DONE: this declaration is actually a type cast
      if (!strncmp(IdentTable + SyntaxStack1[synPtr], "(something", sizeof "(something)" - 1 - 1))
      {
#ifndef NO_FP
        int fmask;
        int ptrmask;
#endif
        int castSize;

        if (SyntaxStack0[++synPtr] == tokLocalOfs) // TBD!!! is this really needed???
          synPtr++;

        s = exprval(idx, ExprTypeSynPtr, ConstExpr);

        // can't cast void or structure/union to anything (except void)
        if (*ExprTypeSynPtr >= 0 &&
            (SyntaxStack0[*ExprTypeSynPtr] == tokVoid ||
             SyntaxStack0[*ExprTypeSynPtr] == tokStructPtr) &&
            SyntaxStack0[synPtr] != tokVoid)
          errorOpType();

        // can't cast to function, array or structure/union
        if (SyntaxStack0[synPtr] == '(' ||
            SyntaxStack0[synPtr] == '[' ||
            SyntaxStack0[synPtr] == tokStructPtr)
          errorOpType();

#ifndef NO_FP
        ptrmask = isAnyPtr(synPtr) * 2 + isAnyPtr(*ExprTypeSynPtr);
        fmask = isFloat(synPtr) * 2 + isFloat(*ExprTypeSynPtr);
        if (ptrmask && fmask) // pointers and floats don't mix
          errorOpType();
#endif

        // will try to propagate constants through casts
        if (!*ConstExpr &&
            (stack[oldIdxRight - (oldSpRight - sp)][0] == tokNumInt ||
             stack[oldIdxRight - (oldSpRight - sp)][0] == tokNumUint))
        {
          s = stack[oldIdxRight - (oldSpRight - sp)][1];
          *ConstExpr = 1;
        }

        castSize = GetDeclSize(synPtr, 1); // 0 for cast to void

#ifndef NO_FP
        if (castSize && fmask == 1)
        {
          // cast from float to any int
          int u = isUint(synPtr);
          if (*ConstExpr)
          {
            s = u ? f2u(s) : f2i(s, castSize);
          }
          else
          {
            // insert a call to convert float to [unsigned] int
            int above = oldIdxRight + 1 - (oldSpRight - sp);
            int below = *idx + 1;
            ins2(above, ')', SizeOfWord);
            ins2(above, tokIdent, FindIdent(FpFxnName[u ? FXNF2U : FXNF2I]));
            ins(above, ',');
            ins2(below, '(', SizeOfWord);
          }
        }
#endif

        // insertion of tokUChar, tokSChar and tokUnaryPlus transforms
        // lvalues (values formed by dereferences) into rvalues
        // (by hiding the dereferences), just as casts should do
        switch (castSize)
        {
        case 1:
          // cast to unsigned char
          stack[oldIdxRight + 1 - (oldSpRight - sp)][0] = tokUChar;
          s &= 0xFFu;
          break;
        case -1:
          // cast to signed char
          stack[oldIdxRight + 1 - (oldSpRight - sp)][0] = tokSChar;
          if ((s &= 0xFFu) >= 0x80)
            s -= 0x100;
          break;
        default:
#ifdef CAN_COMPILE_32BIT
          if (castSize && castSize != SizeOfWord)
          {
            // cast not to void and not to word-sized type (int/unsigned/pointer/float)
            if (castSize == 2)
            {
              // cast to unsigned short
              stack[oldIdxRight + 1 - (oldSpRight - sp)][0] = tokUShort;
              s &= 0xFFFFu;
            }
            else
            {
              // cast to signed short
              stack[oldIdxRight + 1 - (oldSpRight - sp)][0] = tokShort;
              if ((s &= 0xFFFFu) >= 0x8000)
                s -= 0x10000;
            }
          }
          else // fallthrough
#endif
          {
            // cast to void or word-sized type (int/unsigned/pointer/float)
#ifndef NO_FP
            if (fmask == 2)
            {
              // cast from any int to float
              int u = isUint(*ExprTypeSynPtr);
              if (*ConstExpr)
              {
                s = u ? u2f(s) : i2f(s);
              }
              else
              {
                // insert a call to convert [unsigned] int to float
                int above = oldIdxRight + 1 - (oldSpRight - sp);
                int below = *idx + 1;
                ins2(above, ')', SizeOfWord);
                ins2(above, tokIdent, FindIdent(FpFxnName[u ? FXNU2F : FXNI2F]));
                ins(above, ',');
                ins2(below, '(', SizeOfWord);
              }
            }
#endif
            if (stack[oldIdxRight - (oldSpRight - sp)][0] == tokUnaryStar)
              // hide the dereference
              stack[oldIdxRight + 1 - (oldSpRight - sp)][0] = tokUnaryPlus;
          }
          break;
        }

        if (*ConstExpr)
          stack[oldIdxRight - (oldSpRight - sp)][1] = s;

        *ExprTypeSynPtr = synPtr;
        simplifyConstExpr(s, *ConstExpr, ExprTypeSynPtr, oldIdxRight + 1 - (oldSpRight - sp), *idx + 1);

        if (!*ConstExpr && stack[oldIdxRight + 1 - (oldSpRight - sp)][0] == tokIdent)
          // nothing to hide, remove the cast
          del(oldIdxRight + 1 - (oldSpRight - sp), 1);

        switch (SyntaxStack0[synPtr])
        {
        case tokChar:
        case tokSChar:
        case tokUChar:
#ifdef CAN_COMPILE_32BIT
        case tokShort:
        case tokUShort:
#endif
        case tokInt:
        case tokUnsigned:
#ifndef NO_FP
        case tokFloat:
#endif
          break;
        default:
          // only numeric types can be const
          *ConstExpr = 0;
          break;
        }

        break;
      }

      // Finally, not __func__, not enum, not cast.

      type = SymType(synPtr);

      if (type == SymLocalVar || type == SymLocalArr)
      {
        // replace local variables/arrays with their local addresses
        // (global variables/arrays' addresses are their names)
        stack[*idx + 1][0] = tokLocalOfs;
        stack[*idx + 1][1] = SyntaxStack1[synPtr + 1];
      }
      if (type == SymLocalVar || type == SymGlobalVar)
      {
        // add implicit dereferences for local/global variables
        ins2(*idx + 2, tokUnaryStar, GetDeclSize(synPtr, 1));
      }

      // return the identifier's type
      while (SyntaxStack0[synPtr] == tokIdent || SyntaxStack0[synPtr] == tokLocalOfs)
        synPtr++;
      *ExprTypeSynPtr = synPtr;
    }
    *ConstExpr = 0;
    break;

  // sizeof operator
  case tokSizeof:
    exprval(idx, ExprTypeSynPtr, ConstExpr);
    s = GetDeclSize(*ExprTypeSynPtr, 0);
    if (s == 0)
      error("sizeof of incomplete type\n");

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

    if (*ExprTypeSynPtr >= 0 &&
        (SyntaxStack0[*ExprTypeSynPtr] == '[' || SyntaxStack0[*ExprTypeSynPtr] == '('))
    {
      // convert an array into a pointer to the array,
      // convert a function into a pointer to the function,
      // remove the reference
      del(oldIdxRight + 1 - (oldSpRight - sp), 1);
    }
    else if (*ExprTypeSynPtr >= 0 &&
             stack[oldIdxRight - (oldSpRight - sp)][0] == tokUnaryStar)
    {
      // it's an lvalue (with implicit or explicit dereference),
      // convert it into its address by
      // collapsing/removing the reference and the dereference
      del(oldIdxRight - (oldSpRight - sp), 2);
    }
    else
      //error("exprval(): lvalue expected after '&'\n");
      errorNotLvalue();

    // we cannot insert another '*' into the type to make it a pointer
    // to an array/function/etc, so make the index into the type negative
    *ExprTypeSynPtr = -*ExprTypeSynPtr;

    *ConstExpr = 0;
    break;

  // Indirection unary operator
  case tokUnaryStar:
    exprval(idx, ExprTypeSynPtr, ConstExpr);

    if (*ExprTypeSynPtr < 0 || SyntaxStack0[*ExprTypeSynPtr] == '*')
    {
      // type is a pointer to something,
      // transform it into that something
      if (*ExprTypeSynPtr < 0)
        *ExprTypeSynPtr = -*ExprTypeSynPtr;
      else
        ++*ExprTypeSynPtr;
      nonVoidTypeCheck(*ExprTypeSynPtr);
      if (SyntaxStack0[*ExprTypeSynPtr] == tokStructPtr && !GetDeclSize(*ExprTypeSynPtr, 0))
        // incomplete structure/union type
        errorOpType();
      // remove the dereference if that something is an array or a function
      if (SyntaxStack0[*ExprTypeSynPtr] == '[' ||
          SyntaxStack0[*ExprTypeSynPtr] == '(')
        del(oldIdxRight + 1 - (oldSpRight - sp), 1);
      // else attach dereference size in bytes
      else
        stack[oldIdxRight + 1 - (oldSpRight - sp)][1] = GetDeclSize(*ExprTypeSynPtr, 1);
    }
    else if (SyntaxStack0[*ExprTypeSynPtr] == '[')
    {
      // type is an array,
      // transform it into the array's first element
      // (a subarray, if type is a multidimensional array)
      (*ExprTypeSynPtr) += 3;
      // remove the dereference if that element is an array
      if (SyntaxStack0[*ExprTypeSynPtr] == '[')
        del(oldIdxRight + 1 - (oldSpRight - sp), 1);
      // else attach dereference size in bytes
      else
        stack[oldIdxRight + 1 - (oldSpRight - sp)][1] = GetDeclSize(*ExprTypeSynPtr, 1);
    }
    else
      //error("exprval(): pointer/array expected after '*' / before '[]'\n");
      errorOpType();

    *ConstExpr = 0;
    break;

  // Additive binary operators
  case '+':
  case '-':
  // WRONGISH: DONE: replace prefix ++/-- with +=1/-=1
  // WRONG: DONE: replace postfix ++/-- with (+=1)-1/(-=1)+1
    {
      int ptrmask;
#ifndef NO_FP
      int fmask;
#endif
      int oldIdxLeft, oldSpLeft;
      int sl, sr;
      int incSize;
      sr = exprval(idx, &RightExprTypeSynPtr, &constExpr[1]);
      oldIdxLeft = *idx;
      oldSpLeft = sp;
      sl = exprval(idx, ExprTypeSynPtr, &constExpr[0]);

      // Decay arrays to pointers to their first elements
      // and ensure that the pointers are suitable for pointer arithmetic
      // (not pointers to functions, sizes of pointees are known and non-zero)
      decayArray(&RightExprTypeSynPtr, 1);
      decayArray(ExprTypeSynPtr, 1);

      // Bar void and struct/union
      scalarTypeCheck(RightExprTypeSynPtr);
      scalarTypeCheck(*ExprTypeSynPtr);

      ptrmask = isAnyPtr(RightExprTypeSynPtr) + isAnyPtr(*ExprTypeSynPtr) * 2;
#ifndef NO_FP
      fmask = isFloat(RightExprTypeSynPtr) + isFloat(*ExprTypeSynPtr) * 2;
      if (ptrmask && fmask) // pointers and floats don't mix
        errorOpType();
#endif

      // DONE: index/subscript scaling
      if (ptrmask == 1 && tok == '+') // pointer in right-hand expression
      {
        incSize = GetDeclSize(derefAnyPtr(RightExprTypeSynPtr), 0);

        if (constExpr[0]) // integer constant in left-hand expression
        {
          s = (int)((unsigned)sl * incSize);
          stack[oldIdxLeft - (oldSpLeft - sp)][1] = s;
          // optimize a little if possible
          {
            int i = oldIdxRight - (oldSpRight - sp);
            // Skip any type cast markers
            while (stack[i][0] == tokUnaryPlus || stack[i][0] == '+')
              i--;
            // See if the pointer is an integer constant or a local variable offset
            // and if it is, adjust it here instead of generating code for
            // addition/subtraction
            if (stack[i][0] == tokNumInt || stack[i][0] == tokNumUint || stack[i][0] == tokLocalOfs)
            {
              s = (int)((unsigned)stack[i][1] + s);
              stack[i][1] = s; // TBD!!! need extra truncation?
              del(oldIdxLeft - (oldSpLeft - sp), 1);
              del(oldIdxRight - (oldSpRight - sp) + 1, 1);
            }
          }
        }
        else if (incSize != 1)
        {
          ins2(oldIdxLeft + 1 - (oldSpLeft - sp), tokNumInt, incSize);
          ins(oldIdxLeft + 1 - (oldSpLeft - sp), '*');
        }

        *ExprTypeSynPtr = RightExprTypeSynPtr;
      }
      else if (ptrmask == 2) // pointer in left-hand expression
      {
        incSize = GetDeclSize(derefAnyPtr(*ExprTypeSynPtr), 0);
        if (constExpr[1]) // integer constant in right-hand expression
        {
          s = (int)((unsigned)sr * incSize);
          stack[oldIdxRight - (oldSpRight - sp)][1] = s;
          // optimize a little if possible
          {
            int i = oldIdxLeft - (oldSpLeft - sp);
            // Skip any type cast markers
            while (stack[i][0] == tokUnaryPlus || stack[i][0] == '+')
              i--;
            // See if the pointer is an integer constant or a local variable offset
            // and if it is, adjust it here instead of generating code for
            // addition/subtraction
            if (stack[i][0] == tokNumInt || stack[i][0] == tokNumUint || stack[i][0] == tokLocalOfs)
            {
              if (tok == '-')
                s = (int)~(s - 1u);
              s = (int)((unsigned)stack[i][1] + s);
              stack[i][1] = s; // TBD!!! need extra truncation?
              del(oldIdxRight - (oldSpRight - sp), 2);
            }
          }
        }
        else if (incSize != 1)
        {
          ins2(oldIdxRight + 1 - (oldSpRight - sp), tokNumInt, incSize);
          ins(oldIdxRight + 1 - (oldSpRight - sp), '*');
        }
      }
      else if (ptrmask == 3 && tok == '-') // pointers in both expressions
      {
        incSize = GetDeclSize(derefAnyPtr(*ExprTypeSynPtr), 0);
        // TBD!!! "ptr1-ptr2": better pointer type compatibility test needed, like compatCheck()?
        if (incSize != GetDeclSize(derefAnyPtr(RightExprTypeSynPtr), 0))
          //error("exprval(): incompatible pointers\n");
          errorOpType();
        if (incSize != 1)
        {
          ins2(oldIdxRight + 2 - (oldSpRight - sp), tokNumInt, incSize);
          ins(oldIdxRight + 2 - (oldSpRight - sp), '/');
        }
        *ExprTypeSynPtr = SymIntSynPtr;
      }
      else if (ptrmask)
        //error("exprval(): invalid combination of operands for '+' or '-'\n");
        errorOpType();

      // Promote the result from char to int (and from int to unsigned) if necessary
      promoteType(ExprTypeSynPtr, &RightExprTypeSynPtr);

      *ConstExpr = constExpr[0] && constExpr[1];

#ifndef NO_FP
      if (fmask)
      {
        if (fmask == 2)
        {
          int u = isUint(RightExprTypeSynPtr);
          if (constExpr[1])
          {
            // convert int constant to float
            sr = u ? u2f(sr) : i2f(sr);
            stack[oldIdxRight - (oldSpRight - sp)][1] = sr;
          }
          else
          {
            // insert a call to convert int to float
            int above = oldIdxRight + 1 - (oldSpRight - sp);
            int below = oldIdxLeft + 1 - (oldSpLeft - sp);
            ins2(above, ')', SizeOfWord);
            ins2(above, tokIdent, FindIdent(FpFxnName[u ? FXNU2F : FXNI2F]));
            ins(above, ',');
            ins2(below, '(', SizeOfWord);
            oldSpLeft += 4;
          }
        }
        if (fmask == 1)
        {
          int u = isUint(*ExprTypeSynPtr);
          if (constExpr[0])
          {
            // convert int constant to float
            sl = u ? u2f(sl) : i2f(sl);
            stack[oldIdxLeft - (oldSpLeft - sp)][1] = sl;
          }
          else
          {
            // insert a call to convert int to float
            int above = oldIdxLeft + 1 - (oldSpLeft - sp);
            int below = *idx + 1;
            ins2(above, ')', SizeOfWord);
            ins2(above, tokIdent, FindIdent(FpFxnName[u ? FXNU2F : FXNI2F]));
            ins(above, ',');
            ins2(below, '(', SizeOfWord);
          }
        }
        if (*ConstExpr)
        {
          if (tok == '+')
            s = fadd(sl, sr);
          else
            s = fsub(sl, sr);
        }
        else
        {
          // insert a call to add/subtract floats
          int above = oldIdxRight + 1 - (oldSpRight - sp);
          int mid = oldIdxLeft + 1 - (oldSpLeft - sp);
          int below = *idx + 1;
          if (tok == '-')
          {
            // minuend must be the first argument, swap
            swap(below, mid - below, above - mid);
            mid = above - mid + below;
          }
          stack[above][0] = ')'; // replace '+'/'-' with function call
          stack[above][1] = SizeOfWord * 2;
          ins2(above, tokIdent, FindIdent(FpFxnName[(tok == '+') ? FXNFADD : FXNFSUB]));
          ins(above, ',');
          ins(mid, ',');
          ins2(below, '(', SizeOfWord * 2);
        }
        *ExprTypeSynPtr = SymFloatSynPtr;
      }
      else
#endif
      {
        if (tok == '+')
          s = (int)((unsigned)sl + sr);
        else
          s = (int)((unsigned)sl - sr);
      }

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

      lvalueCheck(*ExprTypeSynPtr, oldIdxRight - (oldSpRight - sp));

      // if it's a pointer, ensure that it's suitable for pointer arithmetic
      // (not pointer to function, pointee size is known and non-zero)
      decayArray(ExprTypeSynPtr, 1); // no actual decay here, just a type check

      // Bar void and struct/union
      scalarTypeCheck(*ExprTypeSynPtr);

#ifndef NO_FP
      // TBD!!! support floats with these operators
      if (isFloat(*ExprTypeSynPtr))
        error("Increment/decrement not supported with floats\n");
#endif

      // "remove" the lvalue dereference as we don't need
      // to read the value while forgetting its location.
      // We need to keep the lvalue location.
      // Remember the operand size.
      opSize = stack[oldIdxRight - (oldSpRight - sp)][1];
      del(oldIdxRight - (oldSpRight - sp), 1);

      if (isAnyPtr(*ExprTypeSynPtr))
        incSize = GetDeclSize(derefAnyPtr(*ExprTypeSynPtr), 0);

      if (incSize == 1)
      {
        // store the operand size in the operator
        stack[oldIdxRight + 1 - (oldSpRight - sp)][1] = opSize;
      }
      else
      {
        // replace ++/-- with "postfix" +=/-= incSize when incSize != 1
        stack[oldIdxRight + 1 - (oldSpRight - sp)][0] =
          inc ? (post ? tokPostAdd : tokAssignAdd) :
                (post ? tokPostSub : tokAssignSub);
        // store the operand size in the operator
        stack[oldIdxRight + 1 - (oldSpRight - sp)][1] = opSize;
        ins2(oldIdxRight + 1 - (oldSpRight - sp), tokNumInt, incSize);
      }

      *ConstExpr = 0;
    }
    break;

  // Simple assignment binary operator
  case '=':
    {
      int oldIdxLeft, oldSpLeft;
      int opSize;
      int structs;
#ifndef NO_FP
      int ptrmask;
      int fmask;
      int sr =
#endif
        exprval(idx, &RightExprTypeSynPtr, &constExpr[1]);
      oldIdxLeft = *idx;
      oldSpLeft = sp;
      exprval(idx, ExprTypeSynPtr, &constExpr[0]);

      lvalueCheck(*ExprTypeSynPtr, oldIdxLeft - (oldSpLeft - sp));

      nonVoidTypeCheck(RightExprTypeSynPtr);
      nonVoidTypeCheck(*ExprTypeSynPtr);

      structs = (*ExprTypeSynPtr >= 0 && SyntaxStack0[*ExprTypeSynPtr] == tokStructPtr) * 2 +
                (RightExprTypeSynPtr >= 0 && SyntaxStack0[RightExprTypeSynPtr] == tokStructPtr);
#ifndef NO_FP
      ptrmask = isAnyPtr(*ExprTypeSynPtr) * 2 + isAnyPtr(RightExprTypeSynPtr);
      fmask = isFloat(*ExprTypeSynPtr) * 2 + isFloat(RightExprTypeSynPtr);
      if (fmask && (structs | ptrmask)) // floats don't mix with pointers or structs/unions
        errorOpType();
#endif

      if (structs)
      {
        int sz;

        if (structs != 3 ||
            SyntaxStack1[RightExprTypeSynPtr] != SyntaxStack1[*ExprTypeSynPtr])
          errorOpType();

        // TBD??? (a = b) should be an rvalue and so &(a = b) and (&(a = b))->c shouldn't be
        // allowed, while (a = b).c should be allowed.

        // transform "*psleft = *psright" into "*fxn(sizeof *psright, psright, psleft)"
/*
        if (stack[oldIdxLeft - (oldSpLeft - sp)][0] != tokUnaryStar ||
            stack[oldIdxRight - (oldSpRight - sp)][0] != tokUnaryStar)
          errorInternal(18);
*/
        stack[oldIdxLeft - (oldSpLeft - sp)][0] = ','; // replace '*' with ','
        stack[oldIdxRight - (oldSpRight - sp)][0] = ','; // replace '*' with ','

        sz = GetDeclSize(RightExprTypeSynPtr, 0);

        stack[oldIdxRight + 1 - (oldSpRight - sp)][0] = tokNumUint; // replace '=' with "sizeof *psright"
        stack[oldIdxRight + 1 - (oldSpRight - sp)][1] = sz;

        ins(oldIdxRight + 2 - (oldSpRight - sp), ',');

        if (!StructCpyLabel)
          StructCpyLabel = LabelCnt++;
        ins2(oldIdxRight + 2 - (oldSpRight - sp), tokIdent, AddNumericIdent(StructCpyLabel));

        ins2(oldIdxRight + 2 - (oldSpRight - sp), ')', SizeOfWord * 3);
        ins2(oldIdxRight + 2 - (oldSpRight - sp), tokUnaryStar, 0); // use 0 deref size to drop meaningless dereferences

        ins2(*idx + 1, '(', SizeOfWord * 3);
      }
      else
      {
#ifndef NO_FP
        if (fmask == 1 || fmask == 2)
        {
          int u = isUint((fmask == 1) ? *ExprTypeSynPtr : RightExprTypeSynPtr);
          if (constExpr[1])
          {
            // convert between float and [unsigned] int
            if (fmask == 1)
              sr = u ? f2u(sr) : f2i(sr, GetDeclSize(*ExprTypeSynPtr, 1));
            else
              sr = u ? u2f(sr) : i2f(sr);
            stack[oldIdxRight - (oldSpRight - sp)][1] = sr;
          }
          else
          {
            // insert a call to convert between float and [unsigned] int
            int above = oldIdxRight + 1 - (oldSpRight - sp);
            int below = oldIdxLeft + 1 - (oldSpLeft - sp);
            ins2(above, ')', SizeOfWord);
            ins2(above, tokIdent, FindIdent(FpFxnName[(fmask == 1) ? (u ? FXNF2U : FXNF2I) :
                                                                     (u ? FXNU2F : FXNI2F)]));
            ins(above, ',');
            ins2(below, '(', SizeOfWord);
            oldSpLeft += 4;
          }
        }
#endif
        // "remove" the lvalue dereference as we don't need
        // to read the value while forgetting its location.
        // We need to keep the lvalue location.
        // Remember the operand size.
        opSize = stack[oldIdxLeft - (oldSpLeft - sp)][1];
        // store the operand size in the operator
        stack[oldIdxRight + 1 - (oldSpRight - sp)][1] = opSize;
        del(oldIdxLeft - (oldSpLeft - sp), 1);
      }

      *ConstExpr = 0;
    }
    break;

  // DONE: other assignment operators

  // Arithmetic and bitwise unary operators
  case '~':
  case tokUnaryPlus:
  case tokUnaryMinus:
    s = exprval(idx, ExprTypeSynPtr, ConstExpr);
    numericTypeCheck(*ExprTypeSynPtr);
    promoteType(ExprTypeSynPtr, ExprTypeSynPtr);
    switch (tok)
    {
    case '~':
#ifndef NO_FP
      nonFloatTypeCheck(*ExprTypeSynPtr);
#endif
      s = ~s;
      break;
    case tokUnaryPlus:
      break;
    case tokUnaryMinus:
#ifndef NO_FP
      if (isFloat(*ExprTypeSynPtr))
      {
        if (*ConstExpr)
        {
          s = fneg(s);
        }
        else
        {
          // insert a call to float negate
          int above = oldIdxRight + 1 - (oldSpRight - sp);
          int below = *idx + 1;
          stack[above][0] = ')'; // replace tokUnaryMinus with function call
          stack[above][1] = SizeOfWord;
          ins2(above, tokIdent, FindIdent(FpFxnName[FXNFNEG]));
          ins(above, ',');
          ins2(below, '(', SizeOfWord);
        }
      }
      else
#endif
      {
        s = (int)~(s - 1u);
      }
      break;
    }
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
#ifndef NO_FP
      int fmask;
      int oldIdxLeft, oldSpLeft;
#endif
      int sr, sl;
      int Unsigned;
      sr = exprval(idx, &RightExprTypeSynPtr, &constExpr[1]);
#ifndef NO_FP
      oldIdxLeft = *idx;
      oldSpLeft = sp;
#endif
      sl = exprval(idx, ExprTypeSynPtr, &constExpr[0]);

      numericTypeCheck(RightExprTypeSynPtr);
      numericTypeCheck(*ExprTypeSynPtr);
#ifndef NO_FP
      if (tok != '*' && tok != '/')
      {
        nonFloatTypeCheck(RightExprTypeSynPtr);
        nonFloatTypeCheck(*ExprTypeSynPtr);
      }
#endif

      *ConstExpr = constExpr[0] && constExpr[1];

      Unsigned = SyntaxStack0[*ExprTypeSynPtr] == tokUnsigned || SyntaxStack0[RightExprTypeSynPtr] == tokUnsigned;

#ifndef NO_FP
      fmask = isFloat(RightExprTypeSynPtr) + isFloat(*ExprTypeSynPtr) * 2;

      if (fmask)
      {
        if (fmask == 2)
        {
          int u = isUint(RightExprTypeSynPtr);
          if (constExpr[1])
          {
            // convert int constant to float
            sr = u ? u2f(sr) : i2f(sr);
            stack[oldIdxRight - (oldSpRight - sp)][1] = sr;
          }
          else
          {
            // insert a call to convert int to float
            int above = oldIdxRight + 1 - (oldSpRight - sp);
            int below = oldIdxLeft + 1 - (oldSpLeft - sp);
            ins2(above, ')', SizeOfWord);
            ins2(above, tokIdent, FindIdent(FpFxnName[u ? FXNU2F : FXNI2F]));
            ins(above, ',');
            ins2(below, '(', SizeOfWord);
            oldSpLeft += 4;
          }
        }
        if (fmask == 1)
        {
          int u = isUint(*ExprTypeSynPtr);
          if (constExpr[0])
          {
            // convert int constant to float
            sl = u ? u2f(sl) : i2f(sl);
            stack[oldIdxLeft - (oldSpLeft - sp)][1] = sl;
          }
          else
          {
            // insert a call to convert int to float
            int above = oldIdxLeft + 1 - (oldSpLeft - sp);
            int below = *idx + 1;
            ins2(above, ')', SizeOfWord);
            ins2(above, tokIdent, FindIdent(FpFxnName[u ? FXNU2F : FXNI2F]));
            ins(above, ',');
            ins2(below, '(', SizeOfWord);
          }
        }
        if (*ConstExpr)
        {
          if (tok == '*')
            s = fmul(sl, sr);
          else
            s = fdiv(sl, sr);
        }
        else
        {
          // insert a call to multiply/divide floats
          int above = oldIdxRight + 1 - (oldSpRight - sp);
          int mid = oldIdxLeft + 1 - (oldSpLeft - sp);
          int below = *idx + 1;
          if (tok == '/')
          {
            // dividend must be the first argument, swap
            swap(below, mid - below, above - mid);
            mid = above - mid + below;
          }
          stack[above][0] = ')'; // replace '*'/'/' with function call
          stack[above][1] = SizeOfWord * 2;
          ins2(above, tokIdent, FindIdent(FpFxnName[(tok == '*') ? FXNFMUL : FXNFDIV]));
          ins(above, ',');
          ins(mid, ',');
          ins2(below, '(', SizeOfWord * 2);
        }
        *ExprTypeSynPtr = SymFloatSynPtr;
      }
      else
#endif
      {
        switch (tok)
        {
        // DONE: check for division overflows
        case '/':
        case '%':
          *ConstExpr &= divCheckAndCalc(tok, &sl, sr, Unsigned, constExpr);

          if (Unsigned)
          {
            if (tok == '/')
              stack[oldIdxRight + 1 - (oldSpRight - sp)][0] = tokUDiv;
            else
              stack[oldIdxRight + 1 - (oldSpRight - sp)][0] = tokUMod;
          }
          break;

        case '*':
          sl = (int)((unsigned)sl * sr);
          break;

        case tokLShift:
        case tokRShift:
          if (constExpr[1])
          {
            if (SyntaxStack0[RightExprTypeSynPtr] != tokUnsigned)
              sr = truncInt(sr);
            else
              sr = (int)truncUint(sr);
            shiftCountCheck(&sr, oldIdxRight - (oldSpRight - sp), RightExprTypeSynPtr);
          }
          if (*ConstExpr)
          {
            if (tok == tokLShift)
            {
              // left shift is the same for signed and unsigned ints
              sl = (int)((unsigned)sl << sr);
            }
            else
            {
              if (SyntaxStack0[*ExprTypeSynPtr] == tokUnsigned)
              {
                // right shift for unsigned ints
                sl = (int)(truncUint(sl) >> sr);
              }
              else if (sr)
              {
                // right shift for signed ints is arithmetic, sign-bit-preserving
                // don't depend on the compiler's implementation, do it "manually"
                sl = truncInt(sl);
                sl = (int)((truncUint(sl) >> sr) |
                           ((sl < 0) * (~0u << (8 * SizeOfWord - sr))));
              }
            }
          }

          if (SyntaxStack0[*ExprTypeSynPtr] == tokUnsigned && tok == tokRShift)
            stack[oldIdxRight + 1 - (oldSpRight - sp)][0] = tokURShift;

          // ignore RightExprTypeSynPtr for the purpose of promotion/conversion of the result of <</>>
          RightExprTypeSynPtr = SymIntSynPtr;
          break;

        case '&': sl &= sr; break;
        case '^': sl ^= sr; break;
        case '|': sl |= sr; break;
        }
        s = sl;
      }
      promoteType(ExprTypeSynPtr, &RightExprTypeSynPtr);
      simplifyConstExpr(s, *ConstExpr, ExprTypeSynPtr, oldIdxRight + 1 - (oldSpRight - sp), *idx + 1);
    }
    break;

  // Relational and equality binary operators
  // DONE: add (sub)tokens for unsigned >, >=, <, <= for pointers
  case '<':
  case '>':
  case tokLEQ:
  case tokGEQ:
  case tokEQ:
  case tokNEQ:
    {
      int ptrmask;
#ifndef NO_FP
      int fmask;
      int oldIdxLeft, oldSpLeft;
#endif
      int sr, sl;
      sr = exprval(idx, &RightExprTypeSynPtr, &constExpr[1]);
#ifndef NO_FP
      oldIdxLeft = *idx;
      oldSpLeft = sp;
#endif
      sl = exprval(idx, ExprTypeSynPtr, &constExpr[0]);

      // Bar void and struct/union
      scalarTypeCheck(RightExprTypeSynPtr);
      scalarTypeCheck(*ExprTypeSynPtr);

      ptrmask = isAnyPtr(RightExprTypeSynPtr) + isAnyPtr(*ExprTypeSynPtr) * 2;
#ifndef NO_FP
      fmask = isFloat(RightExprTypeSynPtr) + isFloat(*ExprTypeSynPtr) * 2;
      if (ptrmask && fmask) // pointers and floats don't mix
        errorOpType();
#endif

      // TBD??? stricter type checks???
      if (tok != tokEQ && tok != tokNEQ)
      {
        // Disallow >, <, >=, <= between a pointer and a number
        if (ptrmask == 1 || ptrmask == 2)
          //error("exprval(): Invalid/unsupported combination of compared operands\n");
          errorOpType();
        // Disallow >, <, >=, <= with pointers to functions
        if (((ptrmask & 1) && SyntaxStack0[derefAnyPtr(RightExprTypeSynPtr)] == '(') ||
            ((ptrmask & 2) && SyntaxStack0[derefAnyPtr(*ExprTypeSynPtr)] == '('))
          errorOpType();
      }
      else
      {
        // Disallow == and != between a pointer and a number other than constant 0 (AKA NULL)
        if ((ptrmask == 1 && !(constExpr[0] && !truncInt(sl))) ||
            (ptrmask == 2 && !(constExpr[1] && !truncInt(sr))))
          errorOpType();
      }

      *ConstExpr = constExpr[0] && constExpr[1];

#ifndef NO_FP
      if (fmask)
      {
        if (fmask == 2)
        {
          int u = isUint(RightExprTypeSynPtr);
          if (constExpr[1])
          {
            // convert int constant to float
            sr = u ? u2f(sr) : i2f(sr);
            stack[oldIdxRight - (oldSpRight - sp)][1] = sr;
          }
          else
          {
            // insert a call to convert int to float
            int above = oldIdxRight + 1 - (oldSpRight - sp);
            int below = oldIdxLeft + 1 - (oldSpLeft - sp);
            ins2(above, ')', SizeOfWord);
            ins2(above, tokIdent, FindIdent(FpFxnName[u ? FXNU2F : FXNI2F]));
            ins(above, ',');
            ins2(below, '(', SizeOfWord);
            oldSpLeft += 4;
          }
        }
        if (fmask == 1)
        {
          int u = isUint(*ExprTypeSynPtr);
          if (constExpr[0])
          {
            // convert int constant to float
            sl = u ? u2f(sl) : i2f(sl);
            stack[oldIdxLeft - (oldSpLeft - sp)][1] = sl;
          }
          else
          {
            // insert a call to convert int to float
            int above = oldIdxLeft + 1 - (oldSpLeft - sp);
            int below = *idx + 1;
            ins2(above, ')', SizeOfWord);
            ins2(above, tokIdent, FindIdent(FpFxnName[u ? FXNU2F : FXNI2F]));
            ins(above, ',');
            ins2(below, '(', SizeOfWord);
          }
        }
        if (*ConstExpr)
        {
          sl = fcmp(sl, sr, (tok == tokGEQ || tok == '>') ? -1 : +1);
          switch (tok)
          {
          case '<':    sl = sl <  0; break;
          case '>':    sl = sl >  0; break;
          case tokLEQ: sl = sl <= 0; break;
          case tokGEQ: sl = sl >= 0; break;
          case tokEQ:  sl = sl == 0; break;
          case tokNEQ: sl = sl != 0; break;
          }
        }
        else
        {
          // insert a call to compare floats
          int above = oldIdxRight + 1 - (oldSpRight - sp);
          int mid = oldIdxLeft + 1 - (oldSpLeft - sp);
          int below = *idx + 1;
          // left operand must be the first argument, swap
          swap(below, mid - below, above - mid);
          mid = above - mid + below;
          // we'll compare the returned value against 0:
          // -1 if left  < right
          //  0 if left == right
          // +1 if left  > right
          ins2(above, tokNumInt, 0);
          ins2(above, ')', SizeOfWord * 2);
          ins2(above, tokIdent, FindIdent(FpFxnName[(tok == tokGEQ || tok == '>') ? FXNFCMPG : FXNFCMPL]));
          ins(above, ',');
          ins(mid, ',');
          ins2(below, '(', SizeOfWord * 2);
        }
      }
      else
#endif
      {
        int Unsigned = isUint(*ExprTypeSynPtr) || isUint(RightExprTypeSynPtr);

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
            sl = (int)truncUint(sl);
            sr = (int)truncUint(sr);
            switch (tok)
            {
            case '<':    sl = (unsigned)sl <  (unsigned)sr; break;
            case '>':    sl = (unsigned)sl >  (unsigned)sr; break;
            case tokLEQ: sl = (unsigned)sl <= (unsigned)sr; break;
            case tokGEQ: sl = (unsigned)sl >= (unsigned)sr; break;
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
          stack[oldIdxRight + 1 - (oldSpRight - sp)][0] = t;
        }
      }

      s = sl;
      *ExprTypeSynPtr = SymIntSynPtr;
      simplifyConstExpr(s, *ConstExpr, ExprTypeSynPtr, oldIdxRight + 1 - (oldSpRight - sp), *idx + 1);
    }
    break;

  // implicit pseudo-conversion to _Bool of operands of && and ||
  case tok_Bool:
    s = exprval(idx, ExprTypeSynPtr, ConstExpr);
    // Bar void and struct/union
    scalarTypeCheck(*ExprTypeSynPtr);
#ifndef NO_FP
    if (isFloat(*ExprTypeSynPtr))
    {
      if (*ConstExpr)
      {
        s = fcmp(s, i2f(0), -1) != 0;
      }
      else
      {
        // insert a call to compare the float with 0.0
        int above = oldIdxRight + 1 - (oldSpRight - sp);
        int below = *idx + 1;
        // the returned value will be one of -1,0,+1, we need its least significant bit
        stack[above][0] = '&';
        ins2(above, tokNumInt, 1);
        ins2(above, ')', SizeOfWord * 2);
        ins2(above, tokIdent, FindIdent(FpFxnName[FXNFCMPL]));
        ins(above, ',');
        ins(below, ',');
        ins2(below, tokNumInt, i2f(0));
        ins2(below, '(', SizeOfWord * 2);
      }
    }
    else
#endif
    {
      s = truncInt(s) != 0;
    }
    *ExprTypeSynPtr = SymIntSynPtr;
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
        s = sl && sr;
      else
        s = sl || sr;

      *ExprTypeSynPtr = SymIntSynPtr;
      *ConstExpr = constExpr[0] && constExpr[1];
      if (constExpr[0])
      {
        if (tok == tokLogAnd)
        {
          if (!sl)
            *ConstExpr = 1, s = 0;
          // TBD??? else can drop LHS expression
        }
        else
        {
          if (sl)
            *ConstExpr = s = 1;
          // TBD??? else can drop LHS expression
        }
      }
      simplifyConstExpr(s, *ConstExpr, ExprTypeSynPtr, oldIdxRight + 1 - (oldSpRight - sp), *idx + 1);
    }
    break;

  // Function call
  case ')':
    {
      int tmpSynPtr, c;
      int minParams, maxParams;
      int firstParamSynPtr;
      int oldIdx, oldSp;
#ifndef NO_STRUCT_BY_VAL
      unsigned structSize = 0;
      int retStruct = 0;
      int retOfs = 0;
#endif
      exprval(idx, ExprTypeSynPtr, ConstExpr);

      if (!GetFxnInfo(*ExprTypeSynPtr, &minParams, &maxParams, ExprTypeSynPtr, &firstParamSynPtr))
        //error("exprval(): function or function pointer expected\n");
        errorOpType();

      // DONE: validate the number of function arguments
      // DONE: warnings on int<->pointer substitution in params/args

#ifndef NO_STRUCT_BY_VAL
      // If a structure is returned, allocate space for it on the stack
      // and pass its location as the first (implicit) argument.
      if (ParseLevel &&
          *ExprTypeSynPtr >= 0 &&
          SyntaxStack0[*ExprTypeSynPtr] == tokStructPtr)
      {
        unsigned sz = GetDeclSize(*ExprTypeSynPtr, 0);
        // Make sure the return structure type is complete
        if (!sz)
          errorOpType();
        retOfs = AllocLocal(sz);
        // Transform fxn(args) into fxn(pretval, args)
        ins(*idx + 1, ',');
        ins2(*idx + 1, tokLocalOfs, retOfs);
        retStruct = 1;
      }
#endif

      // evaluate function arguments
      c = 0;
      while (stack[*idx][0] != '(')
      {
#ifndef NO_FP
        int fmask;
#endif
        int ptrmask;
#ifndef NO_STRUCT_BY_VAL
        int gotStructs;
#endif

        // add a comma after the first (last to be pushed) argument,
        // so all arguments can be pushed whenever a comma is encountered
        if (!c)
          ins(*idx + 1, ',');

        oldIdx = *idx;
        oldSp = sp;
        (void)oldIdx;
        (void)oldSp;

        exprval(idx, &tmpSynPtr, ConstExpr);
        //error("exprval(): function arguments cannot be of type 'void'\n");

        if (c >= maxParams)
          error("Too many function arguments\n");

        // Find the type of the formal parameter in the function declaration
        if (c < minParams)
        {
          int t;
          while ((t = SyntaxStack0[firstParamSynPtr]) != tokIdent)
          {
            if (t == '(')
            {
              // skip parameters in parameters
              int c = 1;
              while (c)
              {
                t = SyntaxStack0[++firstParamSynPtr];
                c += (t == '(') - (t == ')');
              }
            }
            firstParamSynPtr++;
          }
          firstParamSynPtr++;
        }
        else
        {
          firstParamSynPtr = SymVoidSynPtr;
        }

        ptrmask = isAnyPtr(firstParamSynPtr) * 2 + isAnyPtr(tmpSynPtr);
        (void)ptrmask;
#ifndef NO_FP
        fmask = isFloat(firstParamSynPtr) * 2 + isFloat(tmpSynPtr);
#endif
#ifndef NO_STRUCT_BY_VAL
        gotStructs = (SyntaxStack0[firstParamSynPtr] == tokStructPtr) * 2 +
                     (tmpSynPtr >= 0 && SyntaxStack0[tmpSynPtr] == tokStructPtr);
#endif

#ifndef NO_STRUCT_BY_VAL
        // Bar void
        nonVoidTypeCheck(tmpSynPtr);
#else
        // Bar void and struct/union
        scalarTypeCheck(tmpSynPtr);
#endif
        // if there's a formal parameter for this argument, check the types
        if (c < minParams)
        {
#ifndef NO_FP
          // floats don't mix with pointers
          if (fmask && ptrmask)
            errorOpType();
#endif
#ifndef NO_STRUCT_BY_VAL
          // Structures must be of the same type
          if (gotStructs &&
              (gotStructs != 3 || SyntaxStack1[tmpSynPtr] != SyntaxStack1[firstParamSynPtr]))
            errorOpType();
#endif
#ifndef NO_EXTRA_WARNS
          // Issue a warning if the argument has to be a pointer but isn't and vice versa.
          // TBD??? Compare pointer types deeply as in compatCheck()???
          // TBD??? Issue a similar warning for return values and initializers???
          if (ptrmask == 1 ||
              (ptrmask == 2 &&
              // Make an exception for integer constants equal to 0, treat them as NULL pointers
              !(*ConstExpr && !truncInt(stack[*idx + 1][1]))))
            warning("Expected %spointer in argument %d\n", (ptrmask == 2) ? "" : "non-", c + 1);
#endif
        }

#ifndef NO_STRUCT_BY_VAL
        // If the argument is a structure, push it by calling a dedicated function
        if (gotStructs)
        {
          unsigned sz = GetDeclSize(tmpSynPtr, 0);
          int i = oldIdx - (oldSp - sp);
          stack[i][0] = ')';
          stack[i][1] = SizeOfWord * 2;

          if (!StructPushLabel)
            StructPushLabel = LabelCnt++;

          // The code generator expects functions to return values.
          // If a function argument is a value produced by another function,
          // as is the case here, the code generator will naturally
          // want/need to push something of the size of the machine word.
          // This works perfectly with non-structures.
          // But we only want to push the structure without pushing any other words.
          // In order to avoid involving changes in the code generator,
          // we make the function that pushes structures onto the stack
          // push all words but the first one. The dedicated function will
          // return this word and the code generator will push it.
          // This is ugly.

          ins2(i, tokIdent, AddNumericIdent(StructPushLabel));
          ins(i, ',');
          i = *idx + 1;
          ins(i, ',');
          ins2(i, tokNumUint, (int)sz);
          ins2(i, '(', SizeOfWord * 2);

          if (sz > (unsigned)GenMaxLocalsSize())
            errorVarSize();
          // Structures will be padded to machine word boundary when pushed
          sz = (sz + SizeOfWord - 1) & ~(SizeOfWord - 1u);
          // Count the cumulative size of the pushed structures, excluding
          // the first words that will be pushed by the code generator
          if (structSize + sz < structSize)
            errorVarSize();
          structSize += sz - SizeOfWord;
          if (structSize > (unsigned)GenMaxLocalsSize())
            errorVarSize();
          // TBD??? complete overflow checks (an expression may contain more than one call)?
        }
#endif

#ifndef NO_FP
        // if there's a formal parameter for this argument, we may need to convert from/to float
        if (c < minParams && (fmask == 1 || fmask == 2))
        {
          int u = isUint((fmask == 1) ? firstParamSynPtr : tmpSynPtr);
          if (*ConstExpr)
          {
            int val = stack[*idx + 1][1];
            // convert between float and [unsigned] int
            if (fmask == 1)
              val = u ? f2u(val) : f2i(val, GetDeclSize(firstParamSynPtr, 1));
            else
              val = u ? u2f(val) : i2f(val);
            stack[*idx + 1][1] = val;
          }
          else
          {
            // insert a call to convert between float and [unsigned] int
            int above = oldIdx + 1 - (oldSp - sp);
            int below = *idx + 1;
            ins2(above, ')', SizeOfWord);
            ins2(above, tokIdent, FindIdent(FpFxnName[(fmask == 1) ? (u ? FXNF2U : FXNF2I) :
                                                                     (u ? FXNU2F : FXNI2F)]));
            ins(above, ',');
            ins2(below, '(', SizeOfWord);
          }
        }
#endif

        c++;

        if (stack[*idx][0] == ',')
          --*idx;
      }
      --*idx;

      if (c < minParams)
        error("Too few function arguments\n");

      // store the cumulative argument size in the function call operators
      {
        int i = oldIdxRight + 1 - (oldSpRight - sp);
#ifndef NO_STRUCT_BY_VAL
        // Count the implicit param/arg for returned structure
        c += retStruct;
        // Correct the value by which the stack pointer
        // will be incremented after the call
        c += structSize / SizeOfWord;
#endif
        stack[1 + *idx][1] = stack[i][1] = c * SizeOfWord;
#ifndef NO_STRUCT_BY_VAL
        // If a structure is returned, transform
        // fxn(pretval, args) into *(fxn(pretval, args), pretval)
        if (retStruct)
        {
          ins(i + 1, tokUnaryStar);
          ins(i + 1, tokComma);
          ins2(i + 1, tokLocalOfs, retOfs);
          ins(i + 1, tokVoid);
        }
#endif
      }

      *ConstExpr = 0;
    }
    break;

  // Binary comma operator
  case tokComma:
    {
      int oldIdxLeft, oldSpLeft;
      int retStruct = 0;
      s = exprval(idx, &RightExprTypeSynPtr, &constExpr[1]);
      oldIdxLeft = *idx;
      oldSpLeft = sp;

      // Signify uselessness of the result of the left operand's value
      ins(*idx + 1, tokVoid);

      exprval(idx, ExprTypeSynPtr, &constExpr[0]);
      *ConstExpr = constExpr[0] && constExpr[1];
      *ExprTypeSynPtr = RightExprTypeSynPtr;
      retStruct = RightExprTypeSynPtr >= 0 && SyntaxStack0[RightExprTypeSynPtr] == tokStructPtr;

      if (*ConstExpr)
      {
        // both subexprs are const, remove both and comma
        simplifyConstExpr(s, *ConstExpr, ExprTypeSynPtr, oldIdxRight + 1 - (oldSpRight - sp), *idx + 1);
      }
      else if (constExpr[0])
      {
        // only left subexpr is const, remove it
        del(*idx + 1, oldIdxLeft - (oldSpLeft - sp) - *idx);

        if (!retStruct)
          // Ensure non-lvalue-ness of the result by changing comma to unary plus
          // and thus hiding dereference, if any
          stack[oldIdxRight + 1 - (oldSpRight - sp)][0] = tokUnaryPlus;
        else
          // However, (something, struct).member should still be allowed,
          // so, comma needs to produce lvalue
          del(oldIdxRight + 1 - (oldSpRight - sp), 1);
      }
      else if (retStruct)
      {
        // However, (something, struct).member should still be allowed,
        // so, comma needs to produce lvalue. Swap comma and structure dereference.
        int i = oldIdxRight + 1 - (oldSpRight - sp);
        stack[i][0] = tokUnaryStar;
        stack[i][1] = stack[i - 1][1];
        stack[i - 1][0] = tokComma;
      }
    }
    break;

  // Compound assignment operators
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
      int sr = exprval(idx, &RightExprTypeSynPtr, &constExpr[1]);
      oldIdxLeft = *idx;
      oldSpLeft = sp;
      exprval(idx, ExprTypeSynPtr, &constExpr[0]);

      lvalueCheck(*ExprTypeSynPtr, oldIdxLeft - (oldSpLeft - sp));

      // if it's a pointer, ensure that it's suitable for pointer arithmetic
      // (not pointer to function, pointee size is known and non-zero)
      decayArray(ExprTypeSynPtr, 1); // no actual decay here, just a type check

      // Bar void and struct/union
      scalarTypeCheck(RightExprTypeSynPtr);
      scalarTypeCheck(*ExprTypeSynPtr);

#ifndef NO_FP
      // TBD!!! tokAssignMul, tokAssignDiv, tokAssignAdd, tokAssignSub with floats
      if (isFloat(RightExprTypeSynPtr) || isFloat(*ExprTypeSynPtr))
      {
        switch (tok)
        {
        case tokAssignMul:
        case tokAssignDiv:
        case tokAssignAdd:
        case tokAssignSub:
          error("Compound assignment not supported with floats\n");
        default:
          errorOpType();
        }
      }
#endif

      // "remove" the lvalue dereference as we don't need
      // to read the value while forgetting its location.
      // We need to keep the lvalue location.
      // Remember the operand size.
      opSize = stack[oldIdxLeft - (oldSpLeft - sp)][1];
      // store the operand size in the operator
      stack[oldIdxRight + 1 - (oldSpRight - sp)][1] = opSize;
      del(oldIdxLeft - (oldSpLeft - sp), 1);

      ptrmask = isAnyPtr(*ExprTypeSynPtr) * 2 + isAnyPtr(RightExprTypeSynPtr);

      Unsigned = isUint(*ExprTypeSynPtr) * 2 + isUint(RightExprTypeSynPtr);

      if (tok != tokAssignAdd && tok != tokAssignSub)
      {
        if (ptrmask)
          //error("exprval(): invalid combination of operands for %s\n", GetTokenName(tok));
          errorOpType();
      }
      else
      {
        // No pointer to the right of += and -=
        if (ptrmask & 1)
          //error("exprval(): invalid combination of operands for %s\n", GetTokenName(tok));
          errorOpType();
      }

      if (tok == tokAssignLSh || tok == tokAssignRSh)
      {
        if (constExpr[1])
        {
          if (Unsigned & 1)
            sr = (int)truncUint(sr);
          else
            sr = truncInt(sr);
          shiftCountCheck(&sr, oldIdxRight - (oldSpRight - sp), RightExprTypeSynPtr);
        }
      }

      if (tok == tokAssignDiv || tok == tokAssignMod)
      {
        int t, sl = 0;
        if (tok == tokAssignDiv)
          t = '/';
        else
          t = '%';
        divCheckAndCalc(t, &sl, sr, 1, constExpr);
      }

      // TBD??? replace +=/-= with prefix ++/-- if incSize == 1
      if (ptrmask == 2) // left-hand expression
      {
        incSize = GetDeclSize(derefAnyPtr(*ExprTypeSynPtr), 0);
        if (constExpr[1])
        {
          int t = (int)(stack[oldIdxRight - (oldSpRight - sp)][1] * (unsigned)incSize);
          stack[oldIdxRight - (oldSpRight - sp)][1] = t;
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
        case tokAssignRSh:
          if (Unsigned & 2)
            t = tokAssignURSh;
          break;
        }
        stack[oldIdxRight + 1 - (oldSpRight - sp)][0] = t;
      }

      *ConstExpr = 0;
    }
    break;

  // Ternary/conditional operator
  case '?':
    {
      int oldIdxLeft, oldSpLeft;
      int oldIdxCond, oldSpCond;
      int sr, sl, smid;
      int condTypeSynPtr;
      int sc = (LabelCnt += 2) - 2;
      int structs;
#ifndef NO_FP
      int ptrmask;
      int fmask;
#endif

      // "exprL ? exprMID : exprR" appears on the stack as
      // "exprL exprR exprMID ?"

      // label at the end of ?:
      stack[*idx + 1][0] = tokLogAnd; // piggyback on && for CG (ugly, but simple)
      stack[*idx + 1][1] = sc + 1;

      smid = exprval(idx, ExprTypeSynPtr, &constExpr[1]);

      oldIdxLeft = *idx;
      oldSpLeft = sp;
      sr = exprval(idx, &RightExprTypeSynPtr, &constExpr[2]);

      decayArray(&RightExprTypeSynPtr, 0);
      decayArray(ExprTypeSynPtr, 0);
      promoteType(&RightExprTypeSynPtr, ExprTypeSynPtr);
      promoteType(ExprTypeSynPtr, &RightExprTypeSynPtr);

      structs = (*ExprTypeSynPtr >= 0 && SyntaxStack0[*ExprTypeSynPtr] == tokStructPtr) * 2 +
                (RightExprTypeSynPtr >= 0 && SyntaxStack0[RightExprTypeSynPtr] == tokStructPtr);
#ifndef NO_FP
      ptrmask = isAnyPtr(*ExprTypeSynPtr) * 2 + isAnyPtr(RightExprTypeSynPtr);
      fmask = isFloat(*ExprTypeSynPtr) * 2 + isFloat(RightExprTypeSynPtr);
      if (fmask && (structs | ptrmask)) // floats don't mix with pointers or structs/unions
        errorOpType();

      if (fmask)
      {
        if (fmask == 1)
        {
          int u = isUint(*ExprTypeSynPtr);
          if (constExpr[1])
          {
            // convert int constant to float
            smid = u ? u2f(smid) : i2f(smid);
            stack[oldIdxRight - (oldSpRight - sp)][1] = smid;
          }
          else
          {
            // insert a call to convert int to float
            int above = oldIdxRight + 1 - (oldSpRight - sp);
            int below = oldIdxLeft + 1 - (oldSpLeft - sp);
            ins2(above, ')', SizeOfWord);
            ins2(above, tokIdent, FindIdent(FpFxnName[u ? FXNU2F : FXNI2F]));
            ins(above, ',');
            ins2(below, '(', SizeOfWord);
            oldSpLeft += 4;
          }
        }
        if (fmask == 2)
        {
          int u = isUint(RightExprTypeSynPtr);
          if (constExpr[2])
          {
            // convert int constant to float
            sr = u ? u2f(sr) : i2f(sr);
            stack[oldIdxLeft - (oldSpLeft - sp)][1] = sr;
          }
          else
          {
            // insert a call to convert int to float
            int above = oldIdxLeft + 1 - (oldSpLeft - sp);
            int below = *idx + 1;
            ins2(above, ')', SizeOfWord);
            ins2(above, tokIdent, FindIdent(FpFxnName[u ? FXNU2F : FXNI2F]));
            ins(above, ',');
            ins2(below, '(', SizeOfWord);
          }
        }
        *ExprTypeSynPtr = SymFloatSynPtr;
      }
#endif

      // TBD??? move struct/union-related checks into compatChecks()

      if (structs)
      {
        if (structs != 3 ||
            SyntaxStack1[RightExprTypeSynPtr] != SyntaxStack1[*ExprTypeSynPtr])
          errorOpType();

        // transform "cond ? a : b" into "*(cond ? &a : &b)"
/*
        if (stack[oldIdxLeft - (oldSpLeft - sp)][0] != tokUnaryStar ||
            stack[oldIdxRight - (oldSpRight - sp)][0] != tokUnaryStar)
          errorInternal(19);
*/
        del(oldIdxLeft - (oldSpLeft - sp), 1); // delete '*'
        del(oldIdxRight - (oldSpRight - sp), 1); // delete '*'
        oldSpLeft--;
        // '*' will be inserted at the end
      }
      else
      {
        compatCheck(ExprTypeSynPtr,
                    RightExprTypeSynPtr,
                    &constExpr[1],
                    oldIdxRight - (oldSpRight - sp),
                    oldIdxLeft - (oldSpLeft - sp));
      }

      // label at the start of exprMID
      ins2(oldIdxLeft + 1 - (oldSpLeft - sp), tokLogAnd, sc); // piggyback on && for CG (ugly, but simple)
      // jump from the end of exprR over exprMID to the end of ?:
      ins2(oldIdxLeft - (oldSpLeft - sp), tokGoto, sc + 1);
      // jump to exprMID if exprL is non-zero
      ins2(*idx + 1, tokShortCirc, -sc);

      oldIdxCond = *idx;
      oldSpCond = sp;
      sl = exprval(idx, &condTypeSynPtr, &constExpr[0]);

      // Bar void and struct/union
      scalarTypeCheck(condTypeSynPtr);

#ifndef NO_FP
      if (isFloat(condTypeSynPtr))
      {
        // insert a call to compare the float with 0.0
        int above = oldIdxCond + 1 - (oldSpCond - sp);
        int below = *idx + 1;
        // the returned value will be one of -1,0,+1, that is, 0 if 0, +/-1 otherwise,
        // IOW, suitable for conditional jump on zero/non-zero
        ins2(above, ')', SizeOfWord * 2);
        ins2(above, tokIdent, FindIdent(FpFxnName[FXNFCMPL]));
        ins(above, ',');
        ins(below, ',');
        ins2(below, tokNumInt, i2f(0));
        ins2(below, '(', SizeOfWord * 2);
      }
#endif

      *ConstExpr = s = 0;

      if (constExpr[0])
      {
        int c1 = 0, c2 = 0;
        // Stack now: exprL tokShortCirc exprR tokGoto tokLogAnd exprMID ?/tokLogAnd
        if (
#ifndef NO_FP
            isFloat(condTypeSynPtr) ?
              fcmp(sl, i2f(0), -1) != 0 :
#endif
              (truncUint(sl) != 0))
        {
          if (constExpr[1])
          {
            *ConstExpr = 1, s = smid;
          }
          else
          {
            // Drop exprL and exprR subexpressions
            c1 = oldIdxLeft - (oldSpLeft - sp) - *idx; // includes tokShortCirc, tokGoto, tokLogAnd
            c2 = 1; // include '?'/tokLogAnd
          }
        }
        else
        {
          if (constExpr[2])
          {
            *ConstExpr = 1, s = sr;
          }
          else
          {
            // Drop exprL and exprMID subexpressions
            c1 = oldIdxCond - (oldSpCond - sp) - *idx + 1; // includes tokShortCirc
            c2 = (oldIdxRight - (oldSpRight - sp)) -
                 (oldIdxLeft - (oldSpLeft - sp)) + 3; // includes tokGoto, tokLogAnd, '?'/tokLogAnd
          }
        }
        if (c1)
        {
          int pos = oldIdxRight - (oldSpRight - sp) + 2 - c2;
          if (!structs && stack[pos - 1][0] == tokUnaryStar)
            stack[pos++][0] = tokUnaryPlus, c2--; // ensure non-lvalue-ness by hiding the dereference
          del(pos, c2);
          del(*idx + 1, c1);
        }
      }
      // finish transforming "cond ? a : b" into "*(cond ? &a : &b)", insert '*'
      if (structs)
        ins2(oldIdxRight + 2 - (oldSpRight - sp), tokUnaryStar, 0); // use 0 deref size to drop meaningless dereferences
      simplifyConstExpr(s, *ConstExpr, ExprTypeSynPtr, oldIdxRight + 1 - (oldSpRight - sp), *idx + 1);
    }
    break;

  // Postfix indirect structure/union member selection operator
  case tokArrow:
    {
      int member, i = 0, j = 0, c = 1, ofs = 0;

      stack[*idx + 1][0] = '+'; // replace -> with +
      member = stack[*idx][1]; // keep the member name, it will be replaced with member offset
      stack[*idx][0] = tokNumInt;

      --*idx;
      exprval(idx, ExprTypeSynPtr, ConstExpr);

      if (!isAnyPtr(*ExprTypeSynPtr) ||
          SyntaxStack0[i = derefAnyPtr(*ExprTypeSynPtr)] != tokStructPtr)
        error("Pointer to or structure or union expected\n");

      i = SyntaxStack1[i];
      if (i + 2 > SyntaxStackCnt ||
          (SyntaxStack0[i] != tokStruct && SyntaxStack0[i] != tokUnion) ||
          SyntaxStack0[i + 1] != tokTag)
        errorInternal(20);

      if (!GetDeclSize(i, 0))
        // incomplete structure/union type
        errorOpType();

      i += 5; // step inside the {} body of the struct/union
      while (c)
      {
        int t = SyntaxStack0[i];
        c += (t == '(') - (t == ')') + (t == '{') - (t == '}');
        if (c == 1 &&
            t == tokMemberIdent && SyntaxStack1[i] == member &&
            SyntaxStack0[i + 1] == tokLocalOfs)
        {
          j = i;
          ofs = SyntaxStack1[i + 1];
          break;
        }
        i++;
      }
      if (!j)
        error("Undefined structure or union member '%s'\n", IdentTable + member);

      j += 2;
      // we cannot insert another '*' into the type to make it a pointer,
      // so make the index into the type negative
      *ExprTypeSynPtr = -j; // type: pointer to member's type

      stack[oldIdxRight - (oldSpRight - sp)][1] = ofs; // member offset within structure/union

      // optimize a little, if possible
      {
        int i = oldIdxRight - (oldSpRight - sp) - 1;
        // Skip any type cast markers
        while (stack[i][0] == tokUnaryPlus)
          i--;
        // See if the pointer is an integer constant or a local variable offset
        // and if it is, adjust it here instead of generating code for
        // addition/subtraction
        if (stack[i][0] == tokNumInt || stack[i][0] == tokNumUint || stack[i][0] == tokLocalOfs)
        {
          stack[i][1] = (int)((unsigned)stack[i][1] + ofs); // TBD!!! need extra truncation?
          del(oldIdxRight - (oldSpRight - sp), 2);
        }
      }

      *ConstExpr = 0;
    }
    break;

  default:
    //error("exprval(): Unexpected token %s\n", GetTokenName(tok));
    errorInternal(21);
  }

  return s;
}

STATIC
int ParseExpr(int tok, int* GotUnary, int* ExprTypeSynPtr, int* ConstExpr, int* ConstVal, int option, int option2)
{
  int identFirst = tok == tokIdent;
#ifndef NO_STRUCT_BY_VAL
  int oldOfs = CurFxnLocalOfs;
#endif
  *ConstVal = *ConstExpr = 0;
  *ExprTypeSynPtr = SymVoidSynPtr;

  if (!ExprLevel++)
  {
    opsp = sp = 0;
  }

  if (option == '=')
    push2(tokIdent, option2);

  tok = expr(tok, GotUnary, option == ',' || option == '=');

  if (tok == tokEof || strchr(",;:)]}", tok) == NULL)
    //error("ParseExpr(): Unexpected token %s\n", GetTokenName(tok));
    errorUnexpectedToken(tok);

  if (option == '=')
  {
    push('=');
  }
  else if (option == tokGotoLabel && identFirst && tok == ':' && *GotUnary && sp == 1 && stack[sp - 1][0] == tokIdent)
  {
    // This is a label.
    ExprLevel--;
    return tokGotoLabel;
  }

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
#ifndef NO_FP
        case tokNumFloat:
          printf2("%df", truncInt(stack[i][1]));
          break;
#endif
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
          printf2("(@%d)", truncInt(stack[i][1]));
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
            case tokAssignMul:
            case tokAssignDiv: case tokAssignMod:
            case tokAssignUDiv: case tokAssignUMod:
            case tokAssignLSh: case tokAssignRSh: case tokAssignURSh:
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
        // remove the unneeded unary +'s that have served their cast-substitute purpose
        // also remove dereferences of size 0 (dereferences of pointers to structures)
        for (idx = sp - 1; idx >= 0; idx--)
          if (stack[idx][0] == tokUnaryPlus ||
              (stack[idx][0] == tokUnaryStar && !stack[idx][1]))
            del(idx, 1);
      }
#ifndef NO_ANNOTATIONS
      else if (*ConstExpr)
      {
        GenStartCommentLine();

        switch (SyntaxStack0[*ExprTypeSynPtr])
        {
        case tokChar:
        case tokSChar:
        case tokUChar:
#ifdef CAN_COMPILE_32BIT
        case tokShort:
        case tokUShort:
#endif
        case tokInt:
          printf2("Expression value: %d\n", truncInt(*ConstVal));
          break;
#ifndef NO_FP
        case tokFloat:
          printf2("Expression value: %df\n", truncInt(*ConstVal));
          break;
#endif
        default:
        case tokUnsigned:
          printf2("Expression value: %uu\n", truncUint(*ConstVal));
          break;
        }
      }
#endif
    }
  }

  ExprLevel--;
#ifndef NO_STRUCT_BY_VAL
  // Reclaim stack space used by temporary structure/union objects
  // returned by functions
  CurFxnLocalOfs = oldOfs;
#endif

  return tok;
}

// smc.c code

#ifdef __SMALLER_C__
#ifdef DETERMINE_VA_LIST
// 2 if va_list is a one-element array containing a pointer
//   (typical for x86 Open Watcom C/C++)
// 1 if va_list is a pointer
//   (typical for Turbo C++, x86 gcc)
// 0 if va_list is something else, and
//   the code may have long crashed by now
int VaListType = 0;

// Attempts to determine the type of va_list as
// expected by the standard library
STATIC
void DetermineVaListType(void)
{
  void* testptr[2];
  // hopefully enough space to sprintf() 3 pointers using "%p"
  char testbuf[3][CHAR_BIT * sizeof(void*) + 1];

  // TBD!!! This is not good. Really need the va_something macros.
  // Test whether va_list is a pointer to the first optional argument or
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
    printf("Internal error: Indeterminate underlying type of va_list\n");
    exit(EXIT_FAILURE);
  }
}
#endif // DETERMINE_VA_LIST
#endif // __SMALLER_C__

// Equivalent to puts() but outputs to OutFile.
STATIC
int puts2(char* s)
{
  int res;
  if (!OutFile)
    return 0;
  // Turbo C++ 1.01's fputs() returns EOF if s is empty, which is wrong.
  // Hence the workaround.
  if (*s == '\0' || (res = fputs(s, OutFile)) >= 0)
  {
    // unlike puts(), fputs() doesn't append '\n', append it manually
    res = fputc('\n', OutFile);
  }
  return res;
}

// Equivalent to printf() but outputs to OutFile.
STATIC
int printf2(char* format, ...)
{
  int res;

#ifndef __SMALLER_C__
  va_list vl;
  va_start(vl, format);
#else
  void* vl = &format + 1;
#endif

  if (!OutFile)
  {
    va_end(vl);
    return 0;
  }
#ifndef __SMALLER_C__
  res = vfprintf(OutFile, format, vl);
#else
  // TBD!!! This is not good. Really need the va_something macros.
#ifdef DETERMINE_VA_LIST
  if (VaListType == 2)
  {
    // va_list is a one-element array containing a pointer
    res = vfprintf(OutFile, format, &vl);
  }
  else // if (VaListType == 1)
  // fallthrough
#endif // DETERMINE_VA_LIST
  {
    // va_list is a pointer
    res = vfprintf(OutFile, format, vl);
  }
#endif // __SMALLER_C__

#ifndef __SMALLER_C__
  va_end(vl);
#endif

  return res;
}

STATIC
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

#ifndef NO_ANNOTATIONS
  DumpSynDecls();
#endif
#ifndef NO_PREPROCESSOR
#ifndef NO_ANNOTATIONS
  DumpMacroTable();
#endif
#endif
#ifndef NO_ANNOTATIONS
  DumpIdentTable();
#endif

  // using stdout implicitly instead of stderr explicitly because:
  // - stderr can be a macro and it's unknown if standard headers
  //   aren't included (which is the case when SmallerC is compiled
  //   with itself and linked with some other compiler's standard
  //   libraries)
  // - output to stderr can interfere/overlap with buffered
  //   output to stdout and the result may literally look ugly

  GenStartCommentLine(); printf2("Compilation failed.\n");

  if (OutFile)
    fclose(OutFile);

  printf("Error in \"%s\" (%d:%d)\n", FileNames[fidx], LineNo, LinePos);

#ifndef __SMALLER_C__
  vprintf(format, vl);
#else
  // TBD!!! This is not good. Really need the va_something macros.
#ifdef DETERMINE_VA_LIST
  if (VaListType == 2)
  {
    // va_list is a one-element array containing a pointer
    vprintf(format, &vl);
  }
  else // if (VaListType == 1)
  // fallthrough
#endif // DETERMINE_VA_LIST
  {
    // va_list is a pointer
    vprintf(format, vl);
  }
#endif // __SMALLER_C__

#ifndef __SMALLER_C__
  va_end(vl);
#endif

  exit(EXIT_FAILURE);
}

STATIC
void warning(char* format, ...)
{
  int fidx = FileCnt - 1 + !FileCnt;
#ifndef __SMALLER_C__
  va_list vl;
  va_start(vl, format);
#else
  void* vl = &format + 1;
#endif

  warnCnt++;

  if (!warnings)
  {
    va_end(vl);
    return;
  }

  printf("Warning in \"%s\" (%d:%d)\n", FileNames[fidx], LineNo, LinePos);

#ifndef __SMALLER_C__
  vprintf(format, vl);
#else
  // TBD!!! This is not good. Really need the va_something macros.
#ifdef DETERMINE_VA_LIST
  if (VaListType == 2)
  {
    // va_list is a one-element array containing a pointer
    vprintf(format, &vl);
  }
  else // if (VaListType == 1)
  // fallthrough
#endif // DETERMINE_VA_LIST
  {
    // va_list is a pointer
    vprintf(format, vl);
  }
#endif // __SMALLER_C__

#ifndef __SMALLER_C__
  va_end(vl);
#endif
}

STATIC
void errorFile(char* n)
{
  error("Unable to open, read, write or close file \"%s\"\n", n);
}

STATIC
void errorFileName(void)
{
  error("Invalid or too long file name or path name\n");
}

STATIC
void errorInternal(int n)
{
  error("%d (internal)\n", n);
}

STATIC
void errorChrStr(void)
{
  error("Invalid or unsupported character constant or string literal\n");
}

#ifndef NO_WCHAR
STATIC
void errorWideNonWide(void)
{
  error("Unsupported concatenation of wide and non-wide string literals\n");
}
#endif

STATIC
void errorStrLen(void)
{
  error("String literal too long\n");
}

STATIC
void errorUnexpectedToken(int tok)
{
  error("Unexpected token %s\n", (tok == tokIdent) ? TokenIdentName : GetTokenName(tok));
}

STATIC
void errorDirective(void)
{
  error("Invalid or unsupported preprocessor directive\n");
}

STATIC
void errorCtrlOutOfScope(void)
{
  error("break, continue, case or default in wrong scope\n");
}

STATIC
void errorDecl(void)
{
  error("Invalid or unsupported declaration\n");
}

STATIC
void errorTagRedef(int ident)
{
  error("Redefinition of type tagged '%s'\n", IdentTable + ident);
}

STATIC
void errorVarSize(void)
{
  error("Variable(s) take(s) too much space\n");
}

STATIC
void errorInit(void)
{
  error("Invalid or unsupported initialization\n");
}

STATIC
void errorUnexpectedVoid(void)
{
  error("Unexpected declaration or expression of type void\n");
}

STATIC
void errorOpType(void)
{
  error("Unexpected operand type\n");
}

STATIC
void errorNotLvalue(void)
{
  error("lvalue expected\n");
}

STATIC
void errorNotConst(void)
{
  error("Non-constant expression\n");
}

STATIC
void errorLongExpr(void)
{
  error("Expression too long\n");
}

#ifndef NO_FP
STATIC
void warnFloat2Int(void)
{
  warning("Float constant non-convertible to integer\n");
}
#endif

int tsd[] =
{
  tokVoid, tokChar, tokInt,
  tokSigned, tokUnsigned, tokShort,
#ifndef NO_FP
  tokFloat, tokDouble,
#endif
  tokStruct, tokUnion,
};

STATIC
int TokenStartsDeclaration(int t, int params)
{
  unsigned i;

  for (i = 0; i < sizeof tsd / sizeof tsd[0]; i++)
    if (tsd[i] == t)
      return 1;

  return
#ifdef CAN_COMPILE_32BIT
         (SizeOfWord != 2 && t == tokLong) ||
#endif
#ifndef NO_TYPEDEF_ENUM
         t == tokEnum ||
         (t == tokIdent && FindTypedef(TokenIdentName) >= 0) ||
#endif
         (!params && (t == tokExtern ||
#ifndef NO_TYPEDEF_ENUM
                      t == tokTypedef ||
#endif
                      t == tokStatic));
}

STATIC
void PushSyntax2(int t, int v)
{
  if (SyntaxStackCnt >= SYNTAX_STACK_MAX)
    error("Symbol table exhausted\n");
  SyntaxStack0[SyntaxStackCnt] = t;
  SyntaxStack1[SyntaxStackCnt++] = v;
}

STATIC
void PushSyntax(int t)
{
  PushSyntax2(t, 0);
}

STATIC
void InsertSyntax2(int pos, int t, int v)
{
  if (SyntaxStackCnt >= SYNTAX_STACK_MAX)
    error("Symbol table exhausted\n");
  memmove(&SyntaxStack0[pos + 1],
          &SyntaxStack0[pos],
          sizeof(SyntaxStack0[0]) * (SyntaxStackCnt - pos));
  memmove(&SyntaxStack1[pos + 1],
          &SyntaxStack1[pos],
          sizeof(SyntaxStack1[0]) * (SyntaxStackCnt - pos));
  SyntaxStack0[pos] = t;
  SyntaxStack1[pos] = v;
  SyntaxStackCnt++;
}

STATIC
void InsertSyntax(int pos, int t)
{
  InsertSyntax2(pos, t, 0);
}

STATIC
void DeleteSyntax(int pos, int cnt)
{
  memmove(&SyntaxStack0[pos],
          &SyntaxStack0[pos + cnt],
          sizeof(SyntaxStack0[0]) * (SyntaxStackCnt - (pos + cnt)));
  memmove(&SyntaxStack1[pos],
          &SyntaxStack1[pos + cnt],
          sizeof(SyntaxStack1[0]) * (SyntaxStackCnt - (pos + cnt)));
  SyntaxStackCnt -= cnt;
}

STATIC
int FindSymbol(char* s)
{
  int i;

  // TBD!!! return declaration scope number so
  // redeclarations can be reported if occur in the same scope.

  // TBD??? Also, I could first use FindIdent() and then just look for the
  // index into IdentTable[] instead of doing strcmp()

  for (i = SyntaxStackCnt - 1; i >= 0; i--)
  {
    int t = SyntaxStack0[i];
    if (t == tokIdent &&
        !strcmp(IdentTable + SyntaxStack1[i], s))
    {
      return i;
    }

    if (t == ')')
    {
      // Skip over the function params
      int c = -1;
      while (c)
      {
        t = SyntaxStack0[--i];
        c += (t == '(') - (t == ')');
      }
    }
  }

  return -1;
}

STATIC
int SymType(int SynPtr)
{
  int local = 0;

  if (SyntaxStack0[SynPtr] == tokIdent)
    SynPtr++;

  if ((local = SyntaxStack0[SynPtr] == tokLocalOfs) != 0)
    SynPtr++;

  switch (SyntaxStack0[SynPtr])
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

STATIC
int FindTaggedDecl(char* s, int start, int* CurScope)
{
  int i;

  *CurScope = 1;

  for (i = start; i >= 0; i--)
  {
    int t = SyntaxStack0[i];
    if (t == tokTag &&
        !strcmp(IdentTable + SyntaxStack1[i], s))
    {
      return i - 1;
    }
    else if (t == ')')
    {
      // Skip over the function params
      int c = -1;
      while (c)
      {
        t = SyntaxStack0[--i];
        c += (t == '(') - (t == ')');
      }
    }
    else if (t == '#')
    {
      // the scope has changed to the outer scope
      *CurScope = 0;
    }
  }

  return -1;
}

#ifndef NO_TYPEDEF_ENUM
// TBD??? rename this fxn? Cleanup/unify search functions?
STATIC
int FindTypedef(char* s)
{
  int i;

  for (i = SyntaxStackCnt - 1; i >= 0; i--)
  {
    int t = SyntaxStack0[i];
    if ((t == tokTypedef || t == tokIdent) &&
        !strcmp(IdentTable + SyntaxStack1[i], s))
    {
      // if the closest declaration isn't from typedef,
      // (i.e. if it's a variable/function declaration),
      // then the type is unknown for the purpose of
      // declaring a variable of this type
      return (t == tokIdent) ? -1 : i;
    }

    if (t == ')')
    {
      // Skip over the function params
      int c = -1;
      while (c)
      {
        t = SyntaxStack0[--i];
        c += (t == '(') - (t == ')');
      }
    }
  }

  return -1;
}
#endif

STATIC
int GetDeclSize(int SyntaxPtr, int SizeForDeref)
{
  int i;
  unsigned size = 1;
  int arr = 0;

  if (SyntaxPtr < 0) // pointer?
    return SizeOfWord;

  for (i = SyntaxPtr; i < SyntaxStackCnt; i++)
  {
    int tok = SyntaxStack0[i];
    switch (tok)
    {
    case tokIdent: // skip leading identifiers, if any
    case tokLocalOfs: // skip local var offset, too
      break;
    case tokChar:
    case tokSChar:
      if (!arr && ((tok == tokSChar) || CharIsSigned) && SizeForDeref)
        return -1; // 1 byte, needing sign extension when converted to int/unsigned int
      // fallthrough
    case tokUChar:
      return (int)size;
#ifdef CAN_COMPILE_32BIT
    case tokShort:
      if (!arr && SizeForDeref)
        return -2; // 2 bytes, needing sign extension when converted to int/unsigned int
      // fallthrough
    case tokUShort:
      if (size * 2 / 2 != size)
        //error("Variable too big\n");
        errorVarSize();
      size *= 2;
      if (size != truncUint(size))
        //error("Variable too big\n");
        errorVarSize();
      return (int)size;
#endif
    case tokInt:
    case tokUnsigned:
#ifndef NO_FP
    case tokFloat:
#endif
    case '*':
    case '(': // size of fxn = size of ptr for now
      if (size * SizeOfWord / SizeOfWord != size)
        //error("Variable too big\n");
        errorVarSize();
      size *= SizeOfWord;
      if (size != truncUint(size))
        //error("Variable too big\n");
        errorVarSize();
      return (int)size;
    case '[':
      if (SyntaxStack0[i + 1] != tokNumInt && SyntaxStack0[i + 1] != tokNumUint)
        errorInternal(11);
      if (SyntaxStack1[i + 1] &&
          size * SyntaxStack1[i + 1] / SyntaxStack1[i + 1] != size)
        //error("Variable too big\n");
        errorVarSize();
      size *= SyntaxStack1[i + 1];
      if (size != truncUint(size))
        //error("Variable too big\n");
        errorVarSize();
      i += 2;
      arr = 1;
      break;
    case tokStructPtr:
      // follow the "type pointer"
      i = SyntaxStack1[i] - 1;
      break;
    case tokStruct:
    case tokUnion:
      if (i + 2 < SyntaxStackCnt && SyntaxStack0[i + 2] == tokSizeof && !SizeForDeref)
      {
        unsigned s = SyntaxStack1[i + 2];
        if (s && size * s / s != size)
          errorVarSize();
        size *= s;
        if (size != truncUint(size))
          errorVarSize();
        return (int)size;
      }
      return 0;
    case tokVoid:
      return 0;
    default:
      errorInternal(12);
    }
  }

  errorInternal(13);
  return 0;
}

STATIC
int GetDeclAlignment(int SyntaxPtr)
{
  int i;

  if (SyntaxPtr < 0) // pointer?
    return SizeOfWord;

  for (i = SyntaxPtr; i < SyntaxStackCnt; i++)
  {
    int tok = SyntaxStack0[i];
    switch (tok)
    {
    case tokIdent: // skip leading identifiers, if any
    case tokLocalOfs: // skip local var offset, too
      break;
    case tokChar:
    case tokSChar:
    case tokUChar:
      return 1;
#ifdef CAN_COMPILE_32BIT
    case tokShort:
    case tokUShort:
      return 2;
#endif
    case tokInt:
    case tokUnsigned:
#ifndef NO_FP
    case tokFloat:
#endif
    case '*':
    case '(':
      return SizeOfWord;
    case '[':
      if (SyntaxStack0[i + 1] != tokNumInt && SyntaxStack0[i + 1] != tokNumUint)
        errorInternal(15);
      i += 2;
      break;
    case tokStructPtr:
      // follow the "type pointer"
      i = SyntaxStack1[i] - 1;
      break;
    case tokStruct:
    case tokUnion:
      if (i + 3 < SyntaxStackCnt && SyntaxStack0[i + 2] == tokSizeof)
      {
        return SyntaxStack1[i + 3];
      }
      return 1;
    case tokVoid:
      return 1;
    default:
      errorInternal(16);
    }
  }

  errorInternal(17);
  return 0;
}

#ifndef NO_ANNOTATIONS
STATIC
void DumpDecl(int SyntaxPtr, int IsParam)
{
  int i;
  int icnt = 0;

  if (SyntaxPtr < 0)
    return;

  for (i = SyntaxPtr; i < SyntaxStackCnt; i++)
  {
    int tok = SyntaxStack0[i];
    int v = SyntaxStack1[i];
    switch (tok)
    {
    case tokLocalOfs:
      printf2("(@%d) : ", truncInt(v));
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
        if (SyntaxStack0[i + 1] == tokEllipsis)
          continue;
      }

      printf2("%s : ", IdentTable + v);
      if (!IsParam && (i + 1 < SyntaxStackCnt) && SyntaxStack0[i + 1] == tokIdent)
      {
        // renamed local static variable
        GenPrintLabel(IdentTable + SyntaxStack1[++i]);
        printf2(" : ");
      }
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
          int t = SyntaxStack0[j++];
          c += (t == '(') - (t == ')');
        }

        noparams = (i + 1 == j) || (SyntaxStack0[i + 1] == tokVoid);

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

    case tokStructPtr:
      DumpDecl(v, 0);
      break;

    default:
      switch (tok)
      {
      case tokVoid:
      case tokChar:
      case tokSChar:
      case tokUChar:
#ifdef CAN_COMPILE_32BIT
      case tokShort:
      case tokUShort:
#endif
      case tokInt:
      case tokUnsigned:
#ifndef NO_FP
      case tokFloat:
#endif
      case tokEllipsis:
        printf2("%s\n", GetTokenName(tok));
        break;
      default:
        printf2("%s ", GetTokenName(tok));
        break;
      case tokTag:
        printf2("%s\n", IdentTable + v);
        return;
      }
      break;
    }
  }
}
#endif

#ifndef NO_ANNOTATIONS
STATIC
void DumpSynDecls(void)
{
  int used = SyntaxStackCnt * (sizeof SyntaxStack0[0] + sizeof SyntaxStack1[0]);
  int total = SYNTAX_STACK_MAX * (sizeof SyntaxStack0[0] + sizeof SyntaxStack1[0]);
  puts2("");
  GenStartCommentLine(); printf2("Syntax/declaration table/stack:\n");
  GenStartCommentLine(); printf2("Bytes used: %d/%d\n\n", used, total);
}
#endif

STATIC
int ParseArrayDimension(int AllowEmptyDimension)
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
  tok = ParseExpr(tok, &gotUnary, &synPtr, &constExpr, &exprVal, 0, 0);
  IdentTableLen = undoIdents; // remove all temporary identifier names from e.g. "sizeof"
  SyntaxStackCnt = oldssp; // undo any temporary declarations from e.g. "sizeof" in the expression
  sp = oldesp;

  if (tok != ']')
    //error("ParseArrayDimension(): Unsupported or invalid array dimension (token %s)\n", GetTokenName(tok));
    errorUnexpectedToken(tok);

  if (!gotUnary)
  {
    if (!AllowEmptyDimension)
      //error("ParseArrayDimension(): missing array dimension\n");
      errorUnexpectedToken(tok);
    // Empty dimension is dimension of 0
    exprVal = 0;
  }
  else
  {
    if (!constExpr)
      //error("ParseArrayDimension(): non-constant array dimension\n");
      errorNotConst();

    exprValU = truncUint(exprVal);
    exprVal = truncInt(exprVal);

    promoteType(&synPtr, &synPtr);
    anyIntTypeCheck(synPtr);
    if ((SyntaxStack0[synPtr] == tokInt && exprVal < 1) || (SyntaxStack0[synPtr] == tokUnsigned && exprValU < 1))
      error("Array dimension less than 1\n");

    exprVal = (int)exprValU;
  }

  PushSyntax2(tokNumUint, exprVal);
  return tok;
}

STATIC
void ParseFxnParams(int tok);
static int BrkCntTargetFxn[2];
STATIC
int ParseBlock(int BrkCntTarget[2], int casesIdx);
STATIC
void AddFxnParamSymbols(int SyntaxPtr);
STATIC
void CheckRedecl(int lastSyntaxPtr);

STATIC
int ParseBase(int tok, int base[2])
{
  int valid = 1;
  base[1] = 0;

  switch (tok)
  {
#ifndef NO_FP
  case tokFloat:
#endif
  case tokVoid:
    *base = tok;
    tok = GetToken();
    break;

#ifndef NO_FP
  case tokDouble:
#endif
  case tokChar:
  case tokInt:
  case tokShort:
#ifdef CAN_COMPILE_32BIT
  case tokLong:
#endif
  case tokSigned:
  case tokUnsigned:
  {
    int allowedMask = 0x7F; // double:0x40 unsigned:0x20 signed:0x10 long:0x08 int:0x04 short:0x02 char:0x01
    int typeMask = 0;
    int tokMask, disallowedMask;

lcont:
    switch (tok)
    {
    case tokChar:
      tokMask = 0x01; disallowedMask = 0x4E; break; // disallows double, long, int, short
    case tokShort:
      tokMask = 0x02; disallowedMask = 0x49; break; // disallows double, long, char
    case tokInt:
      tokMask = 0x04; disallowedMask = 0x41; break; // disallows double, char
#ifdef CAN_COMPILE_32BIT
    case tokLong:
      tokMask = 0x08; disallowedMask = 0x03; break; // disallows short, char
#endif
    case tokSigned:
      tokMask = 0x10; disallowedMask = 0x60; break; // disallows double, unsigned
    case tokUnsigned:
      tokMask = 0x20; disallowedMask = 0x50; break; // disallows double, signed
#ifndef NO_FP
    case tokDouble:
      tokMask = 0x40; disallowedMask = 0x37; break; // disallows all except long
#endif
    default:
      tokMask = disallowedMask = 0; break;
    }

    if (allowedMask & tokMask)
    {
      typeMask |= tokMask;
      allowedMask &= ~(disallowedMask | tokMask);
      tok = GetToken();
      goto lcont;
    }

    switch (typeMask)
    {
    case 0x01: typeMask = tokChar; break;
    case 0x11: typeMask = tokSChar; break;
    case 0x21: typeMask = tokUChar; break;
    case 0x02: case 0x12: case 0x06: case 0x16: typeMask = tokShort; break;
    case 0x22: case 0x26: typeMask = tokUShort; break;
    case 0x04: case 0x10: case 0x14: typeMask = tokInt; break;
    case 0x20: case 0x24: typeMask = tokUnsigned; break;
#ifdef CAN_COMPILE_32BIT
    case 0x08: case 0x18: case 0x0C: case 0x1C: typeMask = tokLong; break;
    case 0x28: case 0x2C: typeMask = tokULong; break;
#endif
#ifndef NO_FP
    case 0x40: case 0x48: typeMask = tokFloat; break; // (long) double is alias for float
#endif
    default:
      errorDecl();
    }
    *base = typeMask;
  }
    break;

  case tokStruct:
  case tokUnion:
#ifndef NO_TYPEDEF_ENUM
  case tokEnum:
#endif
  {
    int structType = tok;
    int empty = 1;
    int typePtr = SyntaxStackCnt;
    int gotTag = 0, tagIdent = 0, declPtr = -1, curScope = 0;

    tok = GetToken();

    if (tok == tokIdent)
    {
      // this is a structure/union/enum tag
      gotTag = 1;
      declPtr = FindTaggedDecl(TokenIdentName, SyntaxStackCnt - 1, &curScope);
      tagIdent = AddIdent(TokenIdentName);

      if (declPtr >= 0)
      {
        // Within the same scope we can't declare more than one union, structure or enum
        // with the same tag.
        // There's one common tag namespace for structures, unions and enumerations.
        if (curScope && SyntaxStack0[declPtr] != structType)
          errorTagRedef(tagIdent);
      }
      else if (ParamLevel)
      {
        // new structure/union/enum declarations aren't supported in function parameters
        errorDecl();
      }

      tok = GetToken();
    }
    else
    {
      // structure/union/enum declarations aren't supported in expressions
      if (ExprLevel)
        errorDecl();
      PushSyntax(structType);
      PushSyntax2(tokTag, AddIdent("<something>"));
    }

    if (tok == '{')
    {
      unsigned structInfo[4], sz, alignment, tmp;

      // new structure/union/enum declarations aren't supported in expressions and function parameters
      if (ExprLevel || ParamLevel)
        errorDecl();

      if (gotTag)
      {
        // Cannot redefine a tagged structure/union/enum within the same scope
        if (declPtr >= 0 &&
            curScope &&
            ((declPtr + 2 < SyntaxStackCnt && SyntaxStack0[declPtr + 2] == tokSizeof)
#ifndef NO_TYPEDEF_ENUM
             || structType == tokEnum
#endif
            ))
          errorTagRedef(tagIdent);

        PushSyntax(structType);
        PushSyntax2(tokTag, tagIdent);
      }

#ifndef NO_TYPEDEF_ENUM
      if (structType == tokEnum)
      {
        int lastVal = -1, val = 0;
        int maxVal = (int)(truncUint(~0u) >> 1); // max positive signed int
        char* erange = "Enumeration constant out of range\n";

        tok = GetToken();
        while (tok != '}')
        {
          char* s;
          int ident;
          int lastSyntaxPtr;

          if (tok != tokIdent)
            errorUnexpectedToken(tok);

          s = TokenIdentName;
          ident = AddIdent(s);
          empty = 0;

          tok = GetToken();
          if (tok == '=')
          {
            int gotUnary, synPtr, constExpr;
            int oldssp, oldesp, undoIdents;

            oldssp = SyntaxStackCnt;
            oldesp = sp;
            undoIdents = IdentTableLen;

            tok = ParseExpr(GetToken(), &gotUnary, &synPtr, &constExpr, &val, ',', 0);

            IdentTableLen = undoIdents; // remove all temporary identifier names from e.g. "sizeof"
            SyntaxStackCnt = oldssp; // undo any temporary declarations from e.g. "sizeof" in the expression
            sp = oldesp;

            if (!gotUnary)
              errorUnexpectedToken(tok);
            anyIntTypeCheck(synPtr);
            if (!constExpr)
              errorNotConst();
            if (SyntaxStack0[synPtr] == tokUnsigned && truncUint(val) > (unsigned)maxVal)
              error(erange);
            lastVal = val = truncInt(val);
          }
          else
          {
            if (lastVal == maxVal)
              error(erange);
            lastVal = val = lastVal + 1;
          }

          lastSyntaxPtr = SyntaxStackCnt;
          PushSyntax2(tokIdent, ident);
          PushSyntax2(tokNumInt, val);

          if (tok == ',')
            tok = GetToken();
          else if (tok != '}')
            errorUnexpectedToken(tok);

          CheckRedecl(lastSyntaxPtr);
        }

        if (empty)
          errorUnexpectedToken('}');

        base[0] = tokEnumPtr;
        base[1] = typePtr;

        tok = GetToken();
        return tok;
      }
      else
#endif
      {
        structInfo[0] = structType;
        structInfo[1] = 1; // initial member alignment
        structInfo[2] = 0; // initial member offset
        structInfo[3] = 0; // initial max member size (for unions)

        PushSyntax(tokSizeof); // 0 = initial structure/union size, to be updated
        PushSyntax2(tokSizeof, 1); // 1 = initial structure/union alignment, to be updated

        PushSyntax('{');

        tok = GetToken();
        while (tok != '}')
        {
          if (!TokenStartsDeclaration(tok, 1))
            errorUnexpectedToken(tok);
          tok = ParseDecl(tok, structInfo, 0, 0);
          empty = 0;
        }

        if (empty)
          errorUnexpectedToken('}');

        PushSyntax('}');

        // Update structure/union alignment
        alignment = structInfo[1];
        SyntaxStack1[typePtr + 3] = alignment;

        // Update structure/union size and include trailing padding if needed
        sz = structInfo[2] + structInfo[3];
        tmp = sz;
        sz = (sz + alignment - 1) & ~(alignment - 1);
        if (sz < tmp || sz != truncUint(sz))
          errorVarSize();
        SyntaxStack1[typePtr + 2] = (int)sz;

        tok = GetToken();
      }
    }
    else
    {
#ifndef NO_TYPEDEF_ENUM
      if (structType == tokEnum)
      {
        if (!gotTag || declPtr < 0)
          errorDecl(); // TBD!!! different error when enum tag is not found

        base[0] = tokEnumPtr;
        base[1] = declPtr;
        return tok;
      }
#endif

      if (gotTag)
      {
        if (declPtr >= 0 &&
            SyntaxStack0[declPtr] == structType)
        {
          base[0] = tokStructPtr;
          base[1] = declPtr;
          return tok;
        }

        PushSyntax(structType);
        PushSyntax2(tokTag, tagIdent);

        empty = 0;
      }
    }

    if (empty)
      errorDecl();

    base[0] = tokStructPtr;
    base[1] = typePtr;

    // If we've just defined a structure/union and there are
    // preceding references to this tag within this scope,
    // IOW references to an incomplete type, complete the
    // type in the references
    if (gotTag && SyntaxStack0[SyntaxStackCnt - 1] == '}')
    {
      int i;
      for (i = SyntaxStackCnt - 1; i >= 0; i--)
        if (SyntaxStack0[i] == tokStructPtr)
        {
          int j = SyntaxStack1[i];
          if (SyntaxStack1[j + 1] == tagIdent && !GetDeclSize(i, 0))
            SyntaxStack1[i] = typePtr;
        }
        else if (SyntaxStack0[i] == '#')
        {
          // reached the beginning of the current scope
          break;
        }
    }
  }
    break;

#ifndef NO_TYPEDEF_ENUM
  case tokIdent:
    if ((base[1] = FindTypedef(TokenIdentName)) >= 0)
    {
      base[0] = tokTypedef;
      tok = GetToken();
      break;
    }
    // fallthrough to default
#endif

  default:
    valid = 0;
    break;
  }

#ifdef CAN_COMPILE_32BIT
  if (SizeOfWord == 2 &&
      (*base == tokLong || *base == tokULong))
    valid = 0;
  // to simplify matters, treat long and unsigned long as aliases for int and unsigned int
  // in 32-bit and huge mode(l)s
  if (*base == tokLong)
    *base = tokInt;
  if (*base == tokULong)
    *base = tokUnsigned;
#endif

  if (SizeOfWord == 2)
  {
    // to simplify matters, treat short and unsigned short as aliases for int and unsigned int
    // in 16-bit mode
    if (*base == tokShort)
      *base = tokInt;
    if (*base == tokUShort)
      *base = tokUnsigned;
  }

  // TBD!!! review/test this fxn
//  if (!valid || !tok || !(strchr("*([,)", tok) || tok == tokIdent))
  if (!valid | !tok)
    //error("ParseBase(): Invalid or unsupported type\n");
    error("Invalid or unsupported type\n");

  return tok;
}

/*
  base * name []  ->  name : [] * base
  base *2 (*1 name []1) []2  ->  name : []1 *1 []2 *2 base
  base *3 (*2 (*1 name []1) []2) []3  ->  name : []1 *1 []2 *2 []3 *3 base
*/

STATIC
int ParseDerived(int tok)
{
  int stars = 0;
  int params = 0;
#ifndef MIPS
#ifdef CAN_COMPILE_32BIT
  int isInterrupt = 0;
#endif
#endif

  while (tok == '*')
  {
    stars++;
    tok = GetToken();
  }

#ifndef MIPS
#ifdef CAN_COMPILE_32BIT
  if (tok == tokIntr)
  {
    // __interrupt is supported in the huge and unreal mode(l)s only
    if (OutputFormat != FormatSegHuge && OutputFormat != FormatSegUnreal)
      errorDecl();
    isInterrupt = 1;
    tok = GetToken();
  }
#endif
#endif

  if (tok == '(')
  {
    tok = GetToken();
    if (tok != ')' && !TokenStartsDeclaration(tok, 1))
    {
      tok = ParseDerived(tok);
      if (tok != ')')
        //error("ParseDerived(): ')' expected\n");
        errorUnexpectedToken(tok);
      tok = GetToken();
    }
    else
    {
      params = 1;
    }
  }
  else if (tok == tokIdent)
  {
    PushSyntax2(tok, AddIdent(TokenIdentName));
    tok = GetToken();
  }
  else
  {
    PushSyntax2(tokIdent, AddIdent("<something>"));
  }

  if (params | (tok == '('))
  {
    int t = SyntaxStack0[SyntaxStackCnt - 1];
    if ((t == ')') | (t == ']'))
      errorUnexpectedToken('('); // array of functions or function returning function
    if (!params)
      tok = GetToken();
    else
      PushSyntax2(tokIdent, AddIdent("<something>"));
#ifndef MIPS
#ifdef CAN_COMPILE_32BIT
    if (isInterrupt)
      PushSyntax2('(', 1);
    else // fallthrough
#endif
#endif
    PushSyntax('(');

    ParseLevel++;
    ParamLevel++;
    ParseFxnParams(tok);
    ParamLevel--;
    ParseLevel--;
    PushSyntax(')');
    tok = GetToken();
  }
  else if (tok == '[')
  {
    // DONE!!! allow the first [] without the dimension in function parameters
    int allowEmptyDimension = 1;
    if (SyntaxStack0[SyntaxStackCnt - 1] == ')')
      errorUnexpectedToken('['); // function returning array
    while (tok == '[')
    {
      int oldsp = SyntaxStackCnt;
      PushSyntax(tokVoid); // prevent cases like "int arr[arr];" and "int arr[arr[0]];"
      PushSyntax(tok);
      tok = ParseArrayDimension(allowEmptyDimension);
      if (tok != ']')
        //error("ParseDerived(): ']' expected\n");
        errorUnexpectedToken(tok);
      PushSyntax(']');
      tok = GetToken();
      DeleteSyntax(oldsp, 1);
      allowEmptyDimension = 0;
    }
  }

  while (stars--)
    PushSyntax('*');

  if (!tok || !strchr(",;{=)", tok))
    //error("ParseDerived(): unexpected token %s\n", GetTokenName(tok));
    errorUnexpectedToken(tok);

  return tok;
}

STATIC
void PushBase(int base[2])
{
#ifndef NO_TYPEDEF_ENUM
  if (base[0] == tokTypedef)
  {
    int ptr = base[1];
    int c = 0, copying = 1;

    while (copying)
    {
      int tok = SyntaxStack0[++ptr];
      int t = SyntaxStack0[SyntaxStackCnt - 1];

      // Cannot have:
      //   function returning function
      //   array of functions
      //   function returning array
      if (((t == ')' || t == ']') && tok == '(') ||
          (t == ')' && tok == '['))
        errorDecl();

      PushSyntax2(tok, SyntaxStack1[ptr]);

      c += (tok == '(') - (tok == ')') + (tok == '[') - (tok == ']');

      if (!c)
      {
        switch (tok)
        {
        case tokVoid:
        case tokChar: case tokSChar: case tokUChar:
#ifdef CAN_COMPILE_32BIT
        case tokShort: case tokUShort:
#endif
        case tokInt: case tokUnsigned:
#ifndef NO_FP
        case tokFloat:
#endif
        case tokStructPtr:
          copying = 0;
        }
      }
    }
  }
  else
#endif
  {
    PushSyntax2(base[0], base[1]);
  }

  // Cannot have array of void
  if (SyntaxStack0[SyntaxStackCnt - 1] == tokVoid &&
      SyntaxStack0[SyntaxStackCnt - 2] == ']')
    errorUnexpectedVoid();
}

STATIC
int InitScalar(int synPtr, int tok);
STATIC
int InitArray(int synPtr, int tok);
STATIC
int InitStruct(int synPtr, int tok);

STATIC
int InitVar(int synPtr, int tok)
{
  int p = synPtr, t;
  int undoIdents = IdentTableLen;

  while ((t = SyntaxStack0[p]), (t == tokIdent) | (t == tokLocalOfs))
    p++;

  switch (t)
  {
  case '[':
    // Initializers for aggregates must be enclosed in braces,
    // except for arrays of char initialized with string literals,
    // in which case braces are optional
    if (tok != '{')
    {
      t = SyntaxStack0[p + 3];
      if (((tok != tokLitStr) | ((t != tokChar) & (t != tokUChar) & (t != tokSChar)))
#ifndef NO_WCHAR
          & ((tok != tokLitStrWide) | ((t != WideCharType1) & (t != WideCharType2)))
#endif
         )
        errorUnexpectedToken(tok);
    }
    tok = InitArray(p, tok);
    break;
  case tokStructPtr:
    // Initializers for aggregates must be enclosed in braces
    if (tok != '{')
      errorUnexpectedToken(tok);
    tok = InitStruct(p, tok);
    break;
  default:
    tok = InitScalar(p, tok);
    break;
  }

  if (!strchr(",;", tok))
    errorUnexpectedToken(tok);

  IdentTableLen = undoIdents; // remove all temporary identifier names from e.g. "sizeof" or "str"

  return tok;
}

STATIC
int InitScalar(int synPtr, int tok)
{
  unsigned elementSz = GetDeclSize(synPtr, 0);
  int gotUnary, synPtr2, constExpr, exprVal;
  int oldssp = SyntaxStackCnt;
  int undoIdents = IdentTableLen;
  int ttop;
  int braces = 0;
#ifndef NO_FP
  int ptrmask;
  int fmask;
#endif

  // Initializers for scalars can be optionally enclosed in braces
  if (tok == '{')
  {
    braces = 1;
    tok = GetToken();
  }

  tok = ParseExpr(tok, &gotUnary, &synPtr2, &constExpr, &exprVal, ',', 0);

  if (!gotUnary)
    errorUnexpectedToken(tok);

  if (braces)
  {
    if (tok != '}')
      errorUnexpectedToken(tok);
    tok = GetToken();
  }

  // Bar void and struct/union
  scalarTypeCheck(synPtr2);

#ifndef NO_FP
  ptrmask = isAnyPtr(synPtr) * 2 + isAnyPtr(synPtr2);
  fmask = isFloat(synPtr) * 2 + isFloat(synPtr2);
  if (ptrmask && fmask) // pointers and floats don't mix
    errorOpType();
#endif

  ttop = stack[sp - 1][0];
  if (ttop == tokNumInt || ttop == tokNumUint)
  {
    int val = stack[sp - 1][1];
#ifndef NO_FP
    if (fmask == 1 || fmask == 2)
    {
      int u = isUint((fmask == 1) ? synPtr : synPtr2);
      // convert between float and [unsigned] int
      if (fmask == 1)
        val = u ? f2u(val) : f2i(val, GetDeclSize(synPtr, 1));
      else
        val = u ? u2f(val) : i2f(val);
    }
#endif
    // TBD??? truncate values for types smaller than int (e.g. char and short),
    // so they are always in range for the assembler?
    GenIntData(elementSz, val);
  }
  else if (elementSz == (unsigned)SizeOfWord)
  {
    if (ttop == tokIdent)
    {
      GenAddrData(elementSz, IdentTable + stack[sp - 1][1], 0);
    }
    else if (ttop == '+' || ttop == '-')
    {
      int tleft = stack[sp - 3][0];
      int tright = stack[sp - 2][0];
      if (tleft == tokIdent &&
          (tright == tokNumInt || tright == tokNumUint))
      {
        GenAddrData(elementSz, IdentTable + stack[sp - 3][1], (ttop == '+') ? stack[sp - 2][1] : -stack[sp - 2][1]);
      }
      else if (ttop == '+' &&
               tright == tokIdent &&
               (tleft == tokNumInt || tleft == tokNumUint))
      {
        GenAddrData(elementSz, IdentTable + stack[sp - 2][1], stack[sp - 3][1]);
      }
      else
        errorNotConst();
    }
    else
      errorNotConst();
    // Defer storage of string literal data (if any) until the end.
    // This will let us generate the contiguous array of pointers to
    // string literals unperturbed by the string literal data
    // (e.g. "char* colors[] = { "red", "green", "blue" };").
  }
  else
    //error("ParseDecl(): cannot initialize a global variable with a non-constant expression\n");
    errorNotConst();

  IdentTableLen = undoIdents; // remove all temporary identifier names from e.g. "sizeof" or "str"
  SyntaxStackCnt = oldssp; // undo any temporary declarations from e.g. "sizeof" or "str" in the expression
  return tok;
}

STATIC
int InitArray(int synPtr, int tok)
{
  int elementTypePtr = synPtr + 3;
  int elementType = SyntaxStack0[elementTypePtr];
  unsigned elementSz = GetDeclSize(elementTypePtr, 0);
  int braces = 0;
  unsigned elementCnt = 0;
  unsigned elementsRequired = SyntaxStack1[synPtr + 1];
  int arrOfChar = (elementType == tokChar) | (elementType == tokUChar) | (elementType == tokSChar);
#ifndef NO_WCHAR
  int arrOfWideChar = (elementType == WideCharType1) | (elementType == WideCharType2);
#endif

  if (tok == '{')
  {
    braces = 1;
    tok = GetToken();
  }

  if ((arrOfChar & (tok == tokLitStr))
#ifndef NO_WCHAR
      | (arrOfWideChar & (tok == tokLitStrWide))
#endif
     )
  {
    int ltok = tok;
    unsigned sz = 0;
    // this is 'someArray[someCountIfAny] = "some string"' or
    // 'someArray[someCountIfAny] = { "some string" }'
    do
    {
#ifndef NO_WCHAR
      GetString('"', arrOfWideChar, 'd');
#else
      GetString('"', 0, 'd');
#endif
      if (sz + TokenStringSize < sz ||
          sz + TokenStringSize >= truncUint(-1))
        errorStrLen();
      sz += TokenStringSize;
      elementCnt += TokenStringLen;
      tok = GetToken();
    } while (tok == ltok); // concatenate adjacent string literals

#ifndef NO_WCHAR
    if ((ltok ^ (tokLitStr ^ tokLitStrWide)) == tok)
      errorWideNonWide();
#endif

    if (elementsRequired && elementCnt > elementsRequired)
      errorStrLen();

    if (elementCnt < elementsRequired)
#ifndef NO_WCHAR
      GenZeroData((elementsRequired - elementCnt) * elementSz, 0);
#else
      GenZeroData(elementsRequired - elementCnt, 0);
#endif

    if (!elementsRequired)
      GenZeroData(elementSz, 0), elementCnt++;

    if (braces)
    {
      if (tok != '}')
        errorUnexpectedToken(tok);
      tok = GetToken();
    }
  }
  else
  {
    while (tok != '}')
    {
      if (elementType == '[')
      {
        tok = InitArray(elementTypePtr, tok);
      }
      else if (elementType == tokStructPtr)
      {
        tok = InitStruct(elementTypePtr, tok);
      }
      else
      {
        tok = InitScalar(elementTypePtr, tok);
      }

      // Last element?
      if (++elementCnt >= elementsRequired && elementsRequired)
      {
        if (braces & (tok == ','))
          tok = GetToken();
        break;
      }

      if (tok == ',')
        tok = GetToken();
      else if (tok != '}')
        errorUnexpectedToken(tok);
    }

    if (braces)
    {
      if ((!elementCnt) | (tok != '}'))
        errorUnexpectedToken(tok);
      tok = GetToken();
    }

    if (elementCnt < elementsRequired)
      GenZeroData((elementsRequired - elementCnt) * elementSz, 0);
  }

  // Store the element count if it's an incomplete array
  if (!elementsRequired)
    SyntaxStack1[synPtr + 1] = elementCnt;

  return tok;
}

STATIC
int InitStruct(int synPtr, int tok)
{
  int isUnion;
  unsigned size, ofs = 0;
  int braces = 0;
  int c = 1;

  synPtr = SyntaxStack1[synPtr];
  isUnion = SyntaxStack0[synPtr++] == tokUnion;
  size = SyntaxStack1[++synPtr];
  synPtr += 3; // step inside the {} body of the struct/union

  if (tok == '{')
  {
    braces = 1;
    tok = GetToken();
  }

  // Find the first member
  while (c)
  {
    int t = SyntaxStack0[synPtr];
    c += (t == '(') - (t == ')') + (t == '{') - (t == '}');
    if (c == 1 && t == tokMemberIdent)
      break;
    synPtr++;
  }

  while (tok != '}')
  {
    int c = 1;
    int elementTypePtr, elementType;
    unsigned elementOfs, elementSz;

    elementOfs = SyntaxStack1[++synPtr];
    elementTypePtr = ++synPtr;
    elementType = SyntaxStack0[elementTypePtr];
    elementSz = GetDeclSize(elementTypePtr, 0);

    // Alignment
    if (ofs < elementOfs)
      GenZeroData(elementOfs - ofs, 0);

    if (elementType == '[')
    {
      tok = InitArray(elementTypePtr, tok);
    }
    else if (elementType == tokStructPtr)
    {
      tok = InitStruct(elementTypePtr, tok);
    }
    else
    {
      tok = InitScalar(elementTypePtr, tok);
    }

    ofs = elementOfs + elementSz;

    // Find the next member or the closing brace
    while (c)
    {
      int t = SyntaxStack0[synPtr];
      c += (t == '(') - (t == ')') + (t == '{') - (t == '}');
      if (c == 1 && t == tokMemberIdent)
        break;
      synPtr++;
    }

    // Last member?
    // Only one member (first) is initialized in unions explicitly
    if ((!c) | isUnion)
    {
      if (braces & (tok == ','))
        tok = GetToken();
      break;
    }

    if (tok == ',')
      tok = GetToken();
    else if (tok != '}')
      errorUnexpectedToken(tok);
  }

  if (braces)
  {
    if ((!ofs) | (tok != '}'))
      errorUnexpectedToken(tok);
    tok = GetToken();
  }

  // Implicit initialization of the rest and trailing padding
  if (ofs < size)
    GenZeroData(size - ofs, 0);

  return tok;
}

STATIC
int compatCheck2(int lastSyntaxPtr, int i)
{
  int res = 0;
  int c = 0;
  int t;
  for (;;)
  {
    t = SyntaxStack0[lastSyntaxPtr];
    if (t != SyntaxStack0[i])
    {
      if (SyntaxStack0[i] == ')' && SyntaxStack0[i - 1] == '(')
      {
        // Complete a previously incomplete parameter specification
        int c1 = 1;
        // Skip over the function params
        do
        {
          t = SyntaxStack0[lastSyntaxPtr++];
          c1 += (t == '(') - (t == ')');
        } while (c1);
        lastSyntaxPtr--;
      }
      else if (t == ')' &&
               SyntaxStack0[i - 1] == '(' && SyntaxStack0[i] == tokIdent &&
               SyntaxStack0[i + 1] == tokVoid && SyntaxStack0[i + 2] == ')')
      {
        // As an exception allow foo(void) to be redeclared as foo()
        // since this happens very often in code.
        // This weakens our redeclaration checks, however. Warn about it.
        i += 2;
        warning("Redeclaration from no parameters to unspecified parameters.\n");
      }
      else
        goto lend;
    }

    if (t != tokIdent &&
        SyntaxStack1[lastSyntaxPtr] != SyntaxStack1[i])
    {
      if (SyntaxStack0[lastSyntaxPtr - 1] == '[')
      {
        // Complete an incomplete array dimension or check for dimension mismatch
        if (SyntaxStack1[lastSyntaxPtr] == 0)
          SyntaxStack1[lastSyntaxPtr] = SyntaxStack1[i];
        else if (SyntaxStack1[i])
          goto lend;
      }
      else
        goto lend;
    }

    c += (t == '(') - (t == ')') + (t == '[') - (t == ']');

    if (!c)
    {
      switch (t)
      {
      case tokVoid:
      case tokChar: case tokSChar: case tokUChar:
#ifdef CAN_COMPILE_32BIT
      case tokShort: case tokUShort:
#endif
      case tokInt: case tokUnsigned:
#ifndef NO_FP
      case tokFloat:
#endif
      case tokStructPtr:
        goto lok;
      }
    }

    lastSyntaxPtr++;
    i++;
  }

lok:
  res = 1;

lend:
  return res;
}

STATIC
void CheckRedecl(int lastSyntaxPtr)
{
  int tid, id, external = 0;
  int i;
  int curScopeOnly;
  int level = ParseLevel;

  tid = SyntaxStack0[lastSyntaxPtr];
  id = SyntaxStack1[lastSyntaxPtr];
  switch (tid)
  {
  case tokIdent:
    switch (SyntaxStack0[lastSyntaxPtr + 1])
    {
#ifndef NO_TYPEDEF_ENUM
    case tokNumInt:
      tid = tokEnumPtr;
      break;
#endif

    default:
      external = 1;
      // fallthrough
    case tokLocalOfs: // block-scope auto
    case tokIdent: // block-scope static
      ;
    }
    // fallthrough

  case tokTypedef:
    break;

  case tokMemberIdent:
    {
      int c = 1;
      i = lastSyntaxPtr - 1;
      do
      {
        int t = SyntaxStack0[i];
        c -= (t == '(') - (t == ')') + (t == '{') - (t == '}');
        if (c == 1 &&
            t == tokMemberIdent && SyntaxStack1[i] == id &&
            SyntaxStack0[i + 1] == tokLocalOfs)
          errorRedecl(IdentTable + id);
        i--;
      } while (c);
    }
    return;

  default:
    errorInternal(23);
  }

  // limit search to current scope for typedef and enum,
  // ditto for non-external declarations
  curScopeOnly = tid != tokIdent || !external;

  for (i = lastSyntaxPtr - 1; i >= 0; i--)
  {
    int t = SyntaxStack0[i];

    switch (t)
    {
    case ')':
      {
        // Skip over the function params
        int c = -1;
        while (c)
        {
          t = SyntaxStack0[--i];
          c += (t == '(') - (t == ')');
        }
      }
      break;

    case '#':
      // the scope has changed to the outer scope
      if (curScopeOnly)
        return;
      level--;
      break;

    case tokTypedef:
    case tokIdent:
      if (SyntaxStack1[i] == id)
      {
#ifndef NO_TYPEDEF_ENUM
        if (t == tokIdent && SyntaxStack0[i + 1] == tokNumInt)
          t = tokEnumPtr;
#endif
        if (level == ParseLevel)
        {
#ifndef NO_TYPEDEF_ENUM
          // within the current scope typedefs and enum constants
          // can't be redefined nor can clash with anything else
          if (tid != tokIdent || t != tokIdent)
            errorRedecl(IdentTable + id);
#endif
          // block scope:
          //   can differentiate between auto(tokLocalOfs), static(tokIdent),
          //   extern/proto(nothing) in SyntaxStack*[], hence dup checks and
          //   type match checks needed here
          // file scope:
          //   can't differentiate between static(nothing), extern(nothing),
          //   neither(nothing) in SyntaxStack*[], but duplicate definitions
          //   are taken care of (in CG), hence only type match checks needed
          //   here
          if (level) // block scope: check for bad dups
          {
            switch (SyntaxStack0[i + 1])
            {
            case tokLocalOfs: // block-scope auto
            case tokIdent: // block-scope static
              // auto and static can't be redefined in block scope
              errorRedecl(IdentTable + id);
            default:
              // extern can't be redefined as non-extern in block scope
              if (!external)
                errorRedecl(IdentTable + id);
            }
            // extern/proto type match check follows
          }

          if (compatCheck2(lastSyntaxPtr, i))
            return;
          errorRedecl(IdentTable + id);
        }
        else // elseof if (level == ParseLevel)
        {
          // The new decl is extern/proto.
          // Ignore typedef and enum
          if (t == tokIdent)
          {
            switch (SyntaxStack0[i + 1])
            {
            case tokLocalOfs: // block-scope auto
            case tokIdent: // block-scope static
              // Ignore auto and static
              break;
            default:
              // extern/proto
              if (compatCheck2(lastSyntaxPtr, i))
                return;
              errorRedecl(IdentTable + id);
            }
          }
        }
      } // endof if (SyntaxStack1[i] == id)
      break;
    } // endof switch (t)
  } // endof for (i = lastSyntaxPtr - 1; i >= 0; i--)
}

// DONE: support extern
// DONE: support static
// DONE: support basic initialization
// DONE: support simple non-array initializations with string literals
// DONE: support basic 1-d array initialization
// DONE: global/static data allocations
STATIC
int ParseDecl(int tok, unsigned structInfo[4], int cast, int label)
{
  int base[2];
  int lastSyntaxPtr;
  int external = tok == tokExtern;
  int Static = tok == tokStatic;
#ifndef NO_TYPEDEF_ENUM
  int typeDef = tok == tokTypedef;
#else
  (void)label;
#endif

  if (external |
#ifndef NO_TYPEDEF_ENUM
      typeDef |
#endif
      Static)
  {
    tok = GetToken();
    if (!TokenStartsDeclaration(tok, 1))
      //error("ParseDecl(): unexpected token %s\n", GetTokenName(tok));
      // Implicit int (as in "extern x; static y;") isn't supported
      errorUnexpectedToken(tok);
  }
  tok = ParseBase(tok, base);

#ifndef NO_TYPEDEF_ENUM
  if (label && tok == ':' && base[0] == tokTypedef &&
      !(external | Static | typeDef) && ParseLevel)
  {
    // This is a label.
    return tokGotoLabel;
  }
#endif

  for (;;)
  {
    lastSyntaxPtr = SyntaxStackCnt;

    /* derived type */
    tok = ParseDerived(tok);

    /* base type */
    PushBase(base);

    if ((tok && strchr(",;{=", tok)) || (tok == ')' && ExprLevel))
    {
      int isLocal = 0, isGlobal = 0, isFxn, isStruct, isArray, isIncompleteArr;
      unsigned alignment = 0;
      int staticLabel = 0;

      // Disallow void variables
      if (SyntaxStack0[SyntaxStackCnt - 1] == tokVoid)
      {
        if (SyntaxStack0[SyntaxStackCnt - 2] == tokIdent &&
            !(cast
#ifndef NO_TYPEDEF_ENUM
              | typeDef
#endif
             ))
          //error("ParseDecl(): Cannot declare a variable ('%s') of type 'void'\n", IdentTable + SyntaxStack1[lastSyntaxPtr]);
          errorUnexpectedVoid();
      }

      isFxn = SyntaxStack0[lastSyntaxPtr + 1] == '(';

#ifdef NO_STRUCT_BY_VAL
      if (isFxn &&
          SyntaxStack0[SyntaxStackCnt - 1] == tokStructPtr &&
          SyntaxStack0[SyntaxStackCnt - 2] == ')')
        // structure returning isn't supported currently
        errorDecl();
#endif

      isArray = SyntaxStack0[lastSyntaxPtr + 1] == '[';
      isIncompleteArr = isArray && SyntaxStack1[lastSyntaxPtr + 2] == 0;

      isStruct = SyntaxStack0[lastSyntaxPtr + 1] == tokStructPtr;

      if (!(ExprLevel || structInfo) &&
          !(external |
#ifndef NO_TYPEDEF_ENUM
            typeDef |
#endif
            Static) &&
          !strcmp(IdentTable + SyntaxStack1[lastSyntaxPtr], "<something>") &&
          tok == ';')
      {
        if (isStruct)
        {
          // This is either an incomplete tagged structure/union declaration, e.g. "struct sometag;",
          // or a tagged complete structure/union declaration, e.g. "struct sometag { ... };", without an instance variable,
          // or an untagged complete structure/union declaration, e.g. "struct { ... };", without an instance variable
          int declPtr, curScope;
          int j = SyntaxStack1[lastSyntaxPtr + 1];

          if (j + 2 < SyntaxStackCnt &&
              IdentTable[SyntaxStack1[j + 1]] == '<' && // without tag
              SyntaxStack0[j + 2] == tokSizeof) // but with the {} "body"
            errorDecl();

          // If a structure/union with this tag has been declared in an outer scope,
          // this new declaration should override it
          declPtr = FindTaggedDecl(IdentTable + SyntaxStack1[j + 1], lastSyntaxPtr - 1, &curScope);
          if (declPtr >= 0 && !curScope)
          {
            // If that's the case, unbind this declaration from the old declaration
            // and make it a new incomplete declaration
            PushSyntax(SyntaxStack0[j]); // tokStruct or tokUnion
            PushSyntax2(tokTag, SyntaxStack1[j + 1]);
            SyntaxStack1[lastSyntaxPtr + 1] = SyntaxStackCnt - 2;
          }
          return GetToken();
        }
#ifndef NO_TYPEDEF_ENUM
        else if (SyntaxStack0[lastSyntaxPtr + 1] == tokEnumPtr)
        {
          return GetToken();
        }
#endif
      }

#ifndef NO_TYPEDEF_ENUM
      // Convert enums into ints
      if (SyntaxStack0[SyntaxStackCnt - 1] == tokEnumPtr)
      {
        SyntaxStack0[SyntaxStackCnt - 1] = tokInt;
        SyntaxStack1[SyntaxStackCnt - 1] = 0;
      }
#endif

      // Structure/union members can't be initialized nor be functions nor
      // be incompletely typed arrays inside structure/union declarations
      if (structInfo && ((tok == '=') | isFxn | (tok == '{') | isIncompleteArr))
        errorDecl();

#ifndef NO_TYPEDEF_ENUM
      if (typeDef & ((tok == '=') | (tok == '{')))
        errorDecl();
#endif

      // Error conditions in declarations(/definitions/initializations):
      // Legend:
      //   +  error
      //   -  no error
      //
      // file scope          fxn   fxn {}  var   arr[]   arr[]...[]   arr[incomplete]   arr[incomplete]...[]
      //                     -     -       -     -       -            +                 +
      // file scope          fxn=          var=  arr[]=  arr[]...[]=  arr[incomplete]=  arr[incomplete]...[]=
      //                     +             -     -       +            -                 +
      // file scope  extern  fxn   fxn {}  var   arr[]   arr[]...[]   arr[incomplete]   arr[incomplete]...[]
      //                     -     -       -     -       -            -                 -
      // file scope  extern  fxn=          var=  arr[]=  arr[]...[]=  arr[incomplete]=  arr[incomplete]...[]=
      //                     +             +     +       +            +                 +
      // file scope  static  fxn   fxn {}  var   arr[]   arr[]...[]   arr[incomplete]   arr[incomplete]...[]
      //                     -     -       -     -       -            +                 +
      // file scope  static  fxn=          var=  arr[]=  arr[]...[]=  arr[incomplete]=  arr[incomplete]...[]=
      //                     +             -     -       +            -                 +
      // fxn scope           fxn   fxn {}  var   arr[]   arr[]...[]   arr[incomplete]   arr[incomplete]...[]
      //                     -     +       -     -       -            +                 +
      // fxn scope           fxn=          var=  arr[]=  arr[]...[]=  arr[incomplete]=  arr[incomplete]...[]=
      //                     +             -     +       +            +                 +
      // fxn scope   extern  fxn   fxn {}  var   arr[]   arr[]...[]   arr[incomplete]   arr[incomplete]...[]
      //                     -     +       -     -       -            -                 -
      // fxn scope   extern  fxn=          var=  arr[]=  arr[]...[]=  arr[incomplete]=  arr[incomplete]...[]=
      //                     +             +     +       +            +                 +
      // fxn scope   static  fxn   fxn {}  var   arr[]   arr[]...[]   arr[incomplete]   arr[incomplete]...[]
      //                     +     +       +     +       +            +                 +
      // fxn scope   static  fxn=          var=  arr[]=  arr[]...[]=  arr[incomplete]=  arr[incomplete]...[]=
      //                     +             +     +       +            +                 +

      if (isFxn & (tok == '='))
        //error("ParseDecl(): cannot initialize a function\n");
        errorInit();

      if ((isFxn & (tok == '{')) && ParseLevel)
        //error("ParseDecl(): cannot define a nested function\n");
        errorDecl();

      if ((isFxn & Static) && ParseLevel)
        //error("ParseDecl(): cannot declare a static function in this scope\n");
        errorDecl();

      if (external & (tok == '='))
        //error("ParseDecl(): cannot initialize an external variable\n");
        errorInit();

      if (isIncompleteArr & !(external |
#ifndef NO_TYPEDEF_ENUM
                              typeDef |
#endif
                              (tok == '=')))
        //error("ParseDecl(): cannot define an array of incomplete type\n");
        errorDecl();

      // TBD!!! de-uglify
      if (!strcmp(IdentTable + SyntaxStack1[lastSyntaxPtr], "<something>"))
      {
        // Disallow nameless variables, prototypes, structure/union members and typedefs.
        if (structInfo ||
#ifndef NO_TYPEDEF_ENUM
            typeDef ||
#endif
            !ExprLevel)
          error("Identifier expected in declaration\n");
      }
      else
      {
        // Disallow named variables and prototypes in sizeof(typedecl) and (typedecl).
        if (ExprLevel && !structInfo)
          error("Identifier unexpected in declaration\n");
      }

      if (!isFxn
#ifndef NO_TYPEDEF_ENUM
          && !typeDef
#endif
         )
      {
        // This is a variable or a variable (member) in a struct/union declaration
        int sz = GetDeclSize(lastSyntaxPtr, 0);

        if (!((sz | isIncompleteArr) || ExprLevel)) // incomplete type
          errorDecl(); // TBD!!! different error when struct/union tag is not found

        if (isArray && !GetDeclSize(lastSyntaxPtr + 4, 0))
          // incomplete type of array element (e.g. struct/union)
          errorDecl();

        alignment = GetDeclAlignment(lastSyntaxPtr);

        if (structInfo)
        {
          // It's a variable (member) in a struct/union declaration
          unsigned tmp;
          unsigned newAlignment = alignment;
#ifndef NO_PPACK
          if (alignment > (unsigned)PragmaPackValue)
            newAlignment = PragmaPackValue;
#endif
          // Update structure/union alignment
          if (structInfo[1] < newAlignment)
            structInfo[1] = newAlignment;
          // Align structure member
          tmp = structInfo[2];
          structInfo[2] = (structInfo[2] + newAlignment - 1) & ~(newAlignment - 1);
          if (structInfo[2] < tmp || structInfo[2] != truncUint(structInfo[2]))
            errorVarSize();
          // Change tokIdent to tokMemberIdent and insert a local var offset token
          SyntaxStack0[lastSyntaxPtr] = tokMemberIdent;
          InsertSyntax2(lastSyntaxPtr + 1, tokLocalOfs, (int)structInfo[2]);

          // Advance member offset for structures, keep it zero for unions
          if (structInfo[0] == tokStruct)
          {
            tmp = structInfo[2];
            structInfo[2] += sz;
            if (structInfo[2] < tmp || structInfo[2] != truncUint(structInfo[2]))
              errorVarSize();
          }
          // Update max member size for unions
          else if (structInfo[3] < (unsigned)sz)
          {
            structInfo[3] = sz;
          }
        }
        else if (ParseLevel && !((external | Static) || ExprLevel))
        {
          // It's a local variable
          isLocal = 1;
          // Defer size calculation until initialization
          // Insert a local var offset token, the offset is to be updated
          InsertSyntax2(lastSyntaxPtr + 1, tokLocalOfs, 0);
        }
        else if (!ExprLevel)
        {
          // It's a global variable (external, static or neither)
          isGlobal = 1;
          if (Static && ParseLevel)
          {
            // It's a static variable in function scope, "rename" it by providing
            // an alternative unique numeric identifier right next to it and use it
            staticLabel = LabelCnt++;
            InsertSyntax2(lastSyntaxPtr + 1, tokIdent, AddNumericIdent(staticLabel));
          }
        }
      }

      // If it's a type declaration in a sizeof(typedecl) expression or
      // in an expression with a cast, e.g. (typedecl)expr, we're done
      if (ExprLevel && !structInfo)
      {
#ifndef NO_ANNOTATIONS
        DumpDecl(lastSyntaxPtr, 0);
#endif
        return tok;
      }

#ifndef NO_TYPEDEF_ENUM
      if (typeDef)
      {
#ifndef NO_ANNOTATIONS
        DumpDecl(lastSyntaxPtr, 0);
#endif
        SyntaxStack0[lastSyntaxPtr] = 0; // hide tokIdent for now
        SyntaxStack0[lastSyntaxPtr] = tokTypedef; // change tokIdent to tokTypedef
      }
      else
      // fallthrough
#endif
      if (isLocal | isGlobal)
      {
        int hasInit = tok == '=';
        int needsGlobalInit = isGlobal & !external;
        int sz = GetDeclSize(lastSyntaxPtr, 0);
        int initLabel = 0;
        int bss = (!hasInit) & UseBss;

#ifndef NO_ANNOTATIONS
        if (isGlobal)
          DumpDecl(lastSyntaxPtr, 0);
#endif

        if (hasInit)
        {
          tok = GetToken();
        }

        if (isLocal & hasInit)
          needsGlobalInit = isArray | (isStruct & (tok == '{'));

        if (needsGlobalInit)
        {
          char** oldHeaderFooter = CurHeaderFooter;
          if (oldHeaderFooter)
            puts2(oldHeaderFooter[1]);
          CurHeaderFooter = bss ? BssHeaderFooter : DataHeaderFooter;
          puts2(CurHeaderFooter[0]);

          // DONE: imperfect condition for alignment
          if (alignment != 1)
            GenWordAlignment(bss);

          if (isGlobal)
          {
            if (Static && ParseLevel)
              GenNumLabel(staticLabel);
            else
              GenLabel(IdentTable + SyntaxStack1[lastSyntaxPtr], Static);
          }
          else
          {
            // Generate numeric labels for global initializers of local vars
            GenNumLabel(initLabel = LabelCnt++);
          }

          // Generate global initializers
          if (hasInit)
          {
#ifndef NO_ANNOTATIONS
            if (isGlobal)
            {
              GenStartCommentLine(); printf2("=\n");
            }
#endif
            tok = InitVar(lastSyntaxPtr, tok);
            // Update the size in case it's an incomplete array
            sz = GetDeclSize(lastSyntaxPtr, 0);
          }
          else
          {
            GenZeroData(sz, bss);
          }

          puts2(CurHeaderFooter[1]);
          if (oldHeaderFooter)
            puts2(oldHeaderFooter[0]);
          CurHeaderFooter = oldHeaderFooter;
        }

        if (isLocal)
        {
          // Now that the size of the local is certainly known,
          // update its offset in the offset token
          SyntaxStack1[lastSyntaxPtr + 1] = AllocLocal(sz);

#ifndef NO_ANNOTATIONS
          DumpDecl(lastSyntaxPtr, 0);
#endif
        }

        // Copy global initializers into local vars
        if (isLocal & needsGlobalInit)
        {
#ifndef NO_ANNOTATIONS
          GenStartCommentLine(); printf2("=\n");
#endif
          if (!StructCpyLabel)
            StructCpyLabel = LabelCnt++;

          sp = 0;

          push2('(', SizeOfWord * 3);
          push2(tokLocalOfs, SyntaxStack1[lastSyntaxPtr + 1]);
          push(',');
          push2(tokIdent, AddNumericIdent(initLabel));
          push(',');
          push2(tokNumUint, sz);
          push(',');
          push2(tokIdent, AddNumericIdent(StructCpyLabel));
          push2(')', SizeOfWord * 3);

          GenExpr();
        }
        // Initialize local vars with expressions
        else if (hasInit & !needsGlobalInit)
        {
          int gotUnary, synPtr, constExpr, exprVal;
          int brace = 0;

          // Initializers for scalars can be optionally enclosed in braces
          if ((!isStruct) & (tok == '{'))
          {
            brace = 1;
            tok = GetToken();
          }

          // ParseExpr() will transform the initializer expression into an assignment expression here
          tok = ParseExpr(tok, &gotUnary, &synPtr, &constExpr, &exprVal, '=', SyntaxStack1[lastSyntaxPtr]);

          if (!gotUnary)
            errorUnexpectedToken(tok);

          if (brace)
          {
            if (tok != '}')
              errorUnexpectedToken(tok);
            tok = GetToken();
          }

          if (!isStruct)
          {
            // This is a special case for initialization of integers smaller than int.
            // Since a local integer variable always takes as much space as a whole int,
            // we can optimize code generation a bit by storing the initializer as an int.
            // This is an old accidental optimization and I preserve it for now.
            // Note, this implies a little-endian CPU.
            stack[sp - 1][1] = SizeOfWord;
          }

          // Storage of string literal data from the initializing expression
          // occurs here.
          GenExpr();
        }
      }
      else if (tok == '{')
      {
        // It's a function body. Let's add function parameters as
        // local variables to the symbol table and parse the body.
        int undoSymbolsPtr = SyntaxStackCnt;
        int undoIdents = IdentTableLen;
        int i;
        int endLabel = 0;

#ifndef NO_ANNOTATIONS
        DumpDecl(lastSyntaxPtr, 0);
#endif

        CurFxnName = IdentTable + SyntaxStack1[lastSyntaxPtr];
        IsMain = !strcmp(CurFxnName, "main");

        gotoLabCnt = 0;

        if (verbose)
          printf("%s()\n", CurFxnName);

        ParseLevel++;
        GetFxnInfo(lastSyntaxPtr, &CurFxnParamCntMin, &CurFxnParamCntMax, &CurFxnReturnExprTypeSynPtr, NULL); // get return type

#ifndef NO_STRUCT_BY_VAL
        // Make sure the return structure type is complete
        if (CurFxnReturnExprTypeSynPtr >= 0 &&
            SyntaxStack0[CurFxnReturnExprTypeSynPtr] == tokStructPtr &&
            !GetDeclSize(CurFxnReturnExprTypeSynPtr, 0))
          errorDecl();
#endif

        CurHeaderFooter = CodeHeaderFooter;
        puts2(CurHeaderFooter[0]);

        GenLabel(CurFxnName, Static);

#ifndef MIPS
#ifdef CAN_COMPILE_32BIT
        if (SyntaxStack1[lastSyntaxPtr + 1] & 1)
          GenIsrProlog();
        else // fallthrough
#endif
#endif
        GenFxnProlog();
        CurFxnEpilogLabel = LabelCnt++;

        // A new scope begins before the function parameters
        PushSyntax('#');
        AddFxnParamSymbols(lastSyntaxPtr);

#ifndef NO_FUNC_
        {
          CurFxnNameLabel = LabelCnt++;
          SyntaxStack1[SymFuncPtr] = AddNumericIdent(CurFxnNameLabel);
          SyntaxStack1[SymFuncPtr + 2] = strlen(CurFxnName) + 1;
        }
#endif

        // The block doesn't begin yet another new scope.
        // This is to catch redeclarations of the function parameters.
        tok = ParseBlock(BrkCntTargetFxn, 0);
        ParseLevel--;
        if (tok != '}')
          //error("ParseDecl(): '}' expected\n");
          errorUnexpectedToken(tok);

        for (i = 0; i < gotoLabCnt; i++)
          if (gotoLabStat[i] == 2)
            error("Undeclared label '%s'\n", IdentTable + gotoLabels[i][0]);

        // DONE: if execution of main() reaches here, before the epilog (i.e. without using return),
        // main() should return 0.
        if (IsMain)
        {
          sp = 0;
          push(tokNumInt);
          push(tokReturn); // value produced by generated code is used
          GenExpr();
        }

        GenNumLabel(CurFxnEpilogLabel);

#ifndef MIPS
#ifdef CAN_COMPILE_32BIT
        if (SyntaxStack1[lastSyntaxPtr + 1] & 1)
          GenIsrEpilog();
        else // fallthrough
#endif
#endif
        GenFxnEpilog();

        if (GenFxnSizeNeeded())
          GenNumLabel(endLabel = LabelCnt++);

        puts2(CurHeaderFooter[1]);
        CurHeaderFooter = NULL;

        if (GenFxnSizeNeeded())
          GenRecordFxnSize(CurFxnName, endLabel);

#ifndef NO_FUNC_
        if (CurFxnNameLabel < 0)
        {
          puts2(RoDataHeaderFooter[0]);

          GenNumLabel(-CurFxnNameLabel);

          GenStartAsciiString();
          printf2("\"%s\"\n", CurFxnName);
          GenZeroData(1, 0);

          puts2(RoDataHeaderFooter[1]);

          CurFxnNameLabel = 0;
        }
#endif

        CurFxnName = NULL;
        IdentTableLen = undoIdents; // remove all identifier names
        SyntaxStackCnt = undoSymbolsPtr; // remove all params and locals
        SyntaxStack1[SymFuncPtr] = DummyIdent;
      }
#ifndef NO_ANNOTATIONS
      else if (isFxn)
      {
        // function prototype
        DumpDecl(lastSyntaxPtr, 0);
      }
#endif

      CheckRedecl(lastSyntaxPtr);

      if ((tok == ';') | (tok == '}'))
        break;

      tok = GetToken();
      continue;
    }

    //error("ParseDecl(): unexpected token %s\n", GetTokenName(tok));
    errorUnexpectedToken(tok);
  }

  tok = GetToken();
  return tok;
}

STATIC
void ParseFxnParams(int tok)
{
  int base[2];
  int lastSyntaxPtr;
  int cnt = 0;
  int ellCnt = 0;

  for (;;)
  {
    lastSyntaxPtr = SyntaxStackCnt;

    if (tok == ')') /* unspecified params */
      break;

    if (!TokenStartsDeclaration(tok, 1))
    {
      if (tok == tokEllipsis)
      {
        // "..." cannot be the first parameter and
        // it can be only one
        if (!cnt || ellCnt)
          //error("ParseFxnParams(): '...' unexpected here\n");
          errorUnexpectedToken(tok);
        ellCnt++;
      }
      else
        //error("ParseFxnParams(): Unexpected token %s\n", GetTokenName(tok));
        errorUnexpectedToken(tok);
      base[0] = tok; // "..."
      base[1] = 0;
      PushSyntax2(tokIdent, AddIdent("<something>"));
      tok = GetToken();
    }
    else
    {
      if (ellCnt)
        //error("ParseFxnParams(): '...' must be the last in the parameter list\n");
        errorUnexpectedToken(tok);

      /* base type */
      tok = ParseBase(tok, base);

      /* derived type */
      tok = ParseDerived(tok);
    }

    /* base type */
    PushBase(base);

#ifndef NO_TYPEDEF_ENUM
    // Convert enums into ints
    if (SyntaxStack0[SyntaxStackCnt - 1] == tokEnumPtr)
    {
      SyntaxStack0[SyntaxStackCnt - 1] = tokInt;
      SyntaxStack1[SyntaxStackCnt - 1] = 0;
    }
#endif

    /* Decay arrays to pointers */
    lastSyntaxPtr++; /* skip name */
    if (SyntaxStack0[lastSyntaxPtr] == '[')
    {
      int t;
      DeleteSyntax(lastSyntaxPtr, 1);
      t = SyntaxStack0[lastSyntaxPtr];
      if (t == tokNumInt || t == tokNumUint)
        DeleteSyntax(lastSyntaxPtr, 1);
      SyntaxStack0[lastSyntaxPtr] = '*';
    }
    /* "(Un)decay" functions to function pointers */
    else if (SyntaxStack0[lastSyntaxPtr] == '(')
    {
      InsertSyntax(lastSyntaxPtr, '*');
    }
    lastSyntaxPtr--; /* "unskip" name */

    cnt++;

    if (tok == ')' || tok == ',')
    {
      int t = SyntaxStack0[SyntaxStackCnt - 2];
      if (SyntaxStack0[SyntaxStackCnt - 1] == tokVoid)
      {
        // Disallow void variables. TBD!!! de-uglify
        if (t == tokIdent &&
            !(!strcmp(IdentTable + SyntaxStack1[SyntaxStackCnt - 2], "<something>") &&
              cnt == 1 && tok == ')'))
          //error("ParseFxnParams(): Cannot declare a variable ('%s') of type 'void'\n", IdentTable + SyntaxStack1[lastSyntaxPtr]);
          errorUnexpectedVoid();
      }

#ifdef NO_STRUCT_BY_VAL
      if (SyntaxStack0[SyntaxStackCnt - 1] == tokStructPtr &&
          t != '*' &&
          t != ']')
        // structure passing and returning isn't supported currently
        errorDecl();
#endif

      if (tok == ')')
        break;

      tok = GetToken();
      continue;
    }

    //error("ParseFxnParams(): Unexpected token %s\n", GetTokenName(tok));
    errorUnexpectedToken(tok);
  }
}

STATIC
void AddFxnParamSymbols(int SyntaxPtr)
{
  int i;
  unsigned paramOfs = 2 * SizeOfWord; // ret addr, xbp

  if (SyntaxPtr < 0 ||
      SyntaxPtr > SyntaxStackCnt - 3 ||
      SyntaxStack0[SyntaxPtr] != tokIdent ||
      SyntaxStack0[SyntaxPtr + 1] != '(')
    //error("Internal error: AddFxnParamSymbols(): Invalid input\n");
    errorInternal(6);

  CurFxnSyntaxPtr = SyntaxPtr;
  CurFxnLocalOfs = 0;
  CurFxnMinLocalOfs = 0;

#ifndef NO_STRUCT_BY_VAL
  if (CurFxnReturnExprTypeSynPtr >= 0 &&
      SyntaxStack0[CurFxnReturnExprTypeSynPtr] == tokStructPtr)
  {
    // The function returns a struct/union via an implicit param/arg (pointer to struct/union)
    // before its first formal param/arg, add this implicit param/arg
#ifndef NO_ANNOTATIONS
    int paramPtr = SyntaxStackCnt;
#endif
    PushSyntax2(tokIdent, AddIdent("@")); // special implicit param/arg (pretval) pointing to structure receptacle
    PushSyntax2(tokLocalOfs, paramOfs);
    PushSyntax('*');
    PushSyntax2(tokStructPtr, SyntaxStack1[CurFxnReturnExprTypeSynPtr]);
    paramOfs += SizeOfWord;
#ifndef NO_ANNOTATIONS
    DumpDecl(paramPtr, 0);
#endif
  }
#endif

  SyntaxPtr += 2; // skip "ident("

  for (i = SyntaxPtr; i < SyntaxStackCnt; i++)
  {
    int tok = SyntaxStack0[i];

    if (tok == tokIdent)
    {
      unsigned sz;
      int paramPtr;

      if (i + 1 >= SyntaxStackCnt)
        //error("Internal error: AddFxnParamSymbols(): Invalid input\n");
        errorInternal(7);

      if (SyntaxStack0[i + 1] == tokVoid) // "ident(void)" = no params
        break;
      if (SyntaxStack0[i + 1] == tokEllipsis) // "ident(something,...)" = no more params
        break;

      // Make sure the parameter is not an incomplete structure
      sz = GetDeclSize(i, 0);
      if (sz == 0)
        //error("Internal error: AddFxnParamSymbols(): GetDeclSize() = 0\n");
        //errorInternal(8);
        errorDecl();

      // Let's calculate this parameter's relative on-stack location
      paramPtr = SyntaxStackCnt;
      PushSyntax2(SyntaxStack0[i], SyntaxStack1[i]);
      PushSyntax2(tokLocalOfs, paramOfs);

      if (sz + SizeOfWord - 1 < sz)
        errorVarSize();
      sz = (sz + SizeOfWord - 1) & ~(SizeOfWord - 1u);
      if (paramOfs + sz < paramOfs)
        errorVarSize();
      paramOfs += sz;
      if (paramOfs > (unsigned)GenMaxLocalsSize())
        errorVarSize();

      // Duplicate this parameter in the symbol table
      i++;
      while (i < SyntaxStackCnt)
      {
        tok = SyntaxStack0[i];
        if (tok == tokIdent || tok == ')')
        {
#ifndef NO_ANNOTATIONS
          DumpDecl(paramPtr, 0);
#endif
          if (IdentTable[SyntaxStack1[paramPtr]] == '<')
            error("Parameter name expected\n");
          CheckRedecl(paramPtr);
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
            tok = SyntaxStack0[i];
            c += (tok == '(') - (tok == ')');
            PushSyntax2(SyntaxStack0[i], SyntaxStack1[i]);
            i++;
          }
        }
        else
        {
          PushSyntax2(SyntaxStack0[i], SyntaxStack1[i]);
          i++;
        }
      }
    }
    else if (tok == ')') // endof "ident(" ... ")"
      break;
    else
      //error("Internal error: AddFxnParamSymbols(): Unexpected token %s\n", GetTokenName(tok));
      errorInternal(9);
  }
}

STATIC
int ParseStatement(int tok, int BrkCntTarget[2], int casesIdx)
{
/*
  labeled statements:
  + ident : statement
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
  + goto ident ;
  + continue ;
  + break ;
  + return expression-opt ;
*/
  int gotUnary, synPtr,  constExpr, exprVal;
  int brkCntTarget[2];
  int statementNeeded;

  do
  {
    statementNeeded = 0;

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
      tok = ParseBlock(BrkCntTarget, casesIdx);
      ParseLevel--;
      if (tok != '}')
        //error("ParseStatement(): '}' expected. Unexpected token %s\n", GetTokenName(tok));
        errorUnexpectedToken(tok);
      UndoNonLabelIdents(undoIdents); // remove all identifier names, except those of labels
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
      int retVoid = CurFxnReturnExprTypeSynPtr >= 0 &&
                    SyntaxStack0[CurFxnReturnExprTypeSynPtr] == tokVoid;
#ifndef NO_ANNOTATIONS
      GenStartCommentLine(); printf2("return\n");
#endif
      tok = GetToken();
      if (tok == ';')
      {
        gotUnary = 0;
        if (!retVoid)
          //error("ParseStatement(): missing return value\n");
          errorUnexpectedToken(tok);
      }
      else
      {
        if (retVoid)
          //error("Error: ParseStatement(): cannot return a value from a function returning 'void'\n");
          errorUnexpectedToken(tok);
        if ((tok = ParseExpr(tok, &gotUnary, &synPtr, &constExpr, &exprVal, 0, 0)) != ';')
          //error("ParseStatement(): ';' expected\n");
          errorUnexpectedToken(tok);
        if (gotUnary)
          //error("ParseStatement(): cannot return a value of type 'void'\n");
#ifdef NO_STRUCT_BY_VAL
          // Bar void and struct/union
          scalarTypeCheck(synPtr);
#else
          // Bar void
          nonVoidTypeCheck(synPtr);
#endif
      }
      if (gotUnary)
      {
#ifndef NO_FP
        int ptrmask;
        int fmask;
#endif
#ifndef NO_STRUCT_BY_VAL
        int structs;
#endif
        decayArray(&synPtr, 0);
#ifndef NO_FP
        ptrmask = isAnyPtr(CurFxnReturnExprTypeSynPtr) * 2 + isAnyPtr(synPtr);
        fmask = isFloat(CurFxnReturnExprTypeSynPtr) * 2 + isFloat(synPtr);
        if (fmask && ptrmask) // floats don't mix with pointers
          errorOpType();
#endif
#ifndef NO_STRUCT_BY_VAL
        structs = (synPtr >= 0 && SyntaxStack0[synPtr] == tokStructPtr) +
          (CurFxnReturnExprTypeSynPtr >= 0 && SyntaxStack0[CurFxnReturnExprTypeSynPtr] == tokStructPtr) * 2;

        if (structs)
        {
          if (structs != 3 ||
              SyntaxStack1[synPtr] != SyntaxStack1[CurFxnReturnExprTypeSynPtr])
            errorOpType();

          // Transform "return *pstruct" into structure assignment ("*pretval = *pstruct")
          // via function call "fxn(sizeof *pretval, pstruct, pretval)".

          // There are a couple of differences to how this is implemented in the assignment operator:
          // - the structure dereference has already been dropped from *pstruct by ParseExpr(),
          //   so it isn't removed here
          // - we don't add the structure dereference on top of the value returned by "fxn()"
          //   because the return statement is not an expression that can be an operand into another
          //   operator

          ins(0, ',');
          ins2(0, tokUnaryStar, SizeOfWord); // dereference to extract the implicit param/arg (pretval) from the stack
          ins2(0, tokLocalOfs, SyntaxStack1[FindSymbol("@") + 1]); // special implicit param/arg (pretval) pointing to structure receptacle
          ins2(0, '(', SizeOfWord * 3);
          push(',');
          push2(tokNumUint, GetDeclSize(synPtr, 0));
          push(',');
          if (!StructCpyLabel)
            StructCpyLabel = LabelCnt++;
          push2(tokIdent, AddNumericIdent(StructCpyLabel));
          push2(')', SizeOfWord * 3);
        }
        else // fallthrough
#endif
        {
          int castSize = GetDeclSize(CurFxnReturnExprTypeSynPtr, 1);
#ifndef NO_FP
          if (fmask == 1 || fmask == 2)
          {
            int u = isUint((fmask == 1) ? CurFxnReturnExprTypeSynPtr : synPtr);
            if (constExpr)
            {
              // convert between float and [unsigned] int
              if (fmask == 1)
                exprVal = u ? f2u(exprVal) : f2i(exprVal, castSize);
              else
                exprVal = u ? u2f(exprVal) : i2f(exprVal);
            }
            else
            {
              // insert a call to convert between float and [unsigned] int
              ins2(0, '(', SizeOfWord);
              push(',');
              push2(tokIdent, FindIdent(FpFxnName[(fmask == 1) ? (u ? FXNF2U : FXNF2I) :
                                                                 (u ? FXNU2F : FXNI2F)]));
              push2(')', SizeOfWord);
            }
          }
#endif

          // If return value (per function declaration) is a scalar type smaller than machine word,
          // properly zero- or sign-extend the returned value to machine word size.
          // TBD??? Move this cast to the caller?
          if (castSize != SizeOfWord && castSize != GetDeclSize(synPtr, 1))
          {
            if (constExpr)
            {
              switch (castSize)
              {
              case 1:
                exprVal &= 0xFFu;
                break;
              case -1:
                if ((exprVal &= 0xFFu) >= 0x80)
                  exprVal -= 0x100;
                break;
#ifdef CAN_COMPILE_32BIT
              case 2:
                exprVal &= 0xFFFFu;
                break;
              case -2:
                if ((exprVal &= 0xFFFFu) >= 0x8000)
                  exprVal -= 0x10000;
                break;
#endif
              }
            }
            else
            {
              switch (castSize)
              {
              case 1:
                push(tokUChar);
                break;
              case -1:
                push(tokSChar);
                break;
#ifdef CAN_COMPILE_32BIT
              case 2:
                push(tokUShort);
                break;
              case -2:
                push(tokShort);
                break;
#endif
              }
            }
          }
        }
        if (constExpr)
          stack[0][1] = exprVal;
        push(tokReturn); // value produced by generated code is used
        GenExpr();
      }
      tok = GetToken();
      // If this return is the last statement in the function, the epilogue immediately
      // follows and there's no need to jump to it.
      if (!(tok == '}' && ParseLevel == 1 && !IsMain))
        GenJumpUncond(CurFxnEpilogLabel);
    }
    else if (tok == tokWhile)
    {
      int labelBefore = LabelCnt++;
      int labelAfter = LabelCnt++;
      int forever = 0;
#ifndef NO_ANNOTATIONS
      GenStartCommentLine(); printf2("while\n");
#endif

      tok = GetToken();
      if (tok != '(')
        //error("ParseStatement(): '(' expected after 'while'\n");
        errorUnexpectedToken(tok);

      tok = GetToken();
      if ((tok = ParseExpr(tok, &gotUnary, &synPtr, &constExpr, &exprVal, 0, 0)) != ')')
        //error("ParseStatement(): ')' expected after 'while ( expression'\n");
        errorUnexpectedToken(tok);

      if (!gotUnary)
        //error("ParseStatement(): expression expected in 'while ( expression )'\n");
        errorUnexpectedToken(tok);

      // DONE: void control expressions
      //error("ParseStatement(): unexpected 'void' expression in 'while ( expression )'\n");
      // Bar void and struct/union
      scalarTypeCheck(synPtr);

      GenNumLabel(labelBefore);

      if (constExpr)
      {
#ifndef NO_FP
        if (isFloat(synPtr))
          exprVal = fcmp(exprVal, i2f(0), -1);
#endif
        // Special cases for while(0) and while(1)
        if (!(forever = truncInt(exprVal)))
          GenJumpUncond(labelAfter);
      }
      else
      {
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
#ifndef NO_FP
          if (isFloat(synPtr))
          {
            // insert a call to compare the float with 0.0
            // the returned value will be one of -1,0,+1, that is, 0 if 0, +/-1 otherwise,
            // IOW, suitable for conditional jump on zero/non-zero
            ins(0, ',');
            ins2(0, tokNumInt, i2f(0));
            ins2(0, '(', SizeOfWord * 2);
            push(',');
            push2(tokIdent, FindIdent(FpFxnName[FXNFCMPL]));
            push2(')', SizeOfWord * 2);
          }
#endif
          push(tokReturn); // value produced by generated code is used
          GenExpr();
          GenJumpIfZero(labelAfter);
          break;
        }
      }

      tok = GetToken();
      brkCntTarget[0] = labelAfter; // break target
      brkCntTarget[1] = labelBefore; // continue target
      tok = ParseStatement(tok, brkCntTarget, casesIdx);

      // Special case for while(0)
      if (!(constExpr && !forever))
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
      brkCntTarget[0] = labelAfter; // break target
      brkCntTarget[1] = labelWhile; // continue target
      tok = ParseStatement(tok, brkCntTarget, casesIdx);
      if (tok != tokWhile)
        //error("ParseStatement(): 'while' expected after 'do statement'\n");
        errorUnexpectedToken(tok);

#ifndef NO_ANNOTATIONS
      GenStartCommentLine(); printf2("while\n");
#endif
      tok = GetToken();
      if (tok != '(')
        //error("ParseStatement(): '(' expected after 'while'\n");
        errorUnexpectedToken(tok);

      tok = GetToken();
      if ((tok = ParseExpr(tok, &gotUnary, &synPtr, &constExpr, &exprVal, 0, 0)) != ')')
        //error("ParseStatement(): ')' expected after 'while ( expression'\n");
        errorUnexpectedToken(tok);

      if (!gotUnary)
        //error("ParseStatement(): expression expected in 'while ( expression )'\n");
        errorUnexpectedToken(tok);

      tok = GetToken();
      if (tok != ';')
        //error("ParseStatement(): ';' expected after 'do statement while ( expression )'\n");
        errorUnexpectedToken(tok);

      // DONE: void control expressions
      //error("ParseStatement(): unexpected 'void' expression in 'while ( expression )'\n");
      // Bar void and struct/union
      scalarTypeCheck(synPtr);

      GenNumLabel(labelWhile);

      if (constExpr)
      {
#ifndef NO_FP
        if (isFloat(synPtr))
          exprVal = fcmp(exprVal, i2f(0), -1);
#endif
        // Special cases for while(0) and while(1)
        if (truncInt(exprVal))
          GenJumpUncond(labelBefore);
      }
      else
      {
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
#ifndef NO_FP
          if (isFloat(synPtr))
          {
            // insert a call to compare the float with 0.0
            // the returned value will be one of -1,0,+1, that is, 0 if 0, +/-1 otherwise,
            // IOW, suitable for conditional jump on zero/non-zero
            ins(0, ',');
            ins2(0, tokNumInt, i2f(0));
            ins2(0, '(', SizeOfWord * 2);
            push(',');
            push2(tokIdent, FindIdent(FpFxnName[FXNFCMPL]));
            push2(')', SizeOfWord * 2);
          }
#endif
          push(tokReturn); // value produced by generated code is used
          GenExpr();
          GenJumpIfNotZero(labelBefore);
          break;
        }
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
        //error("ParseStatement(): '(' expected after 'if'\n");
        errorUnexpectedToken(tok);

      tok = GetToken();
      if ((tok = ParseExpr(tok, &gotUnary, &synPtr, &constExpr, &exprVal, 0, 0)) != ')')
        //error("ParseStatement(): ')' expected after 'if ( expression'\n");
        errorUnexpectedToken(tok);

      if (!gotUnary)
        //error("ParseStatement(): expression expected in 'if ( expression )'\n");
        errorUnexpectedToken(tok);

      // DONE: void control expressions
      //error("ParseStatement(): unexpected 'void' expression in 'if ( expression )'\n");
      // Bar void and struct/union
      scalarTypeCheck(synPtr);

      if (constExpr)
      {
#ifndef NO_FP
        if (isFloat(synPtr))
          exprVal = fcmp(exprVal, i2f(0), -1);
#endif
        // Special cases for if(0) and if(1)
        if (!truncInt(exprVal))
          GenJumpUncond(labelAfterIf);
      }
      else
      {
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
#ifndef NO_FP
          if (isFloat(synPtr))
          {
            // insert a call to compare the float with 0.0
            // the returned value will be one of -1,0,+1, that is, 0 if 0, +/-1 otherwise,
            // IOW, suitable for conditional jump on zero/non-zero
            ins(0, ',');
            ins2(0, tokNumInt, i2f(0));
            ins2(0, '(', SizeOfWord * 2);
            push(',');
            push2(tokIdent, FindIdent(FpFxnName[FXNFCMPL]));
            push2(')', SizeOfWord * 2);
          }
#endif
          push(tokReturn); // value produced by generated code is used
          GenExpr();
          GenJumpIfZero(labelAfterIf);
          break;
        }
      }

      tok = GetToken();
      tok = ParseStatement(tok, BrkCntTarget, casesIdx);

      // DONE: else
      if (tok == tokElse)
      {
        GenJumpUncond(labelAfterElse);
        GenNumLabel(labelAfterIf);
#ifndef NO_ANNOTATIONS
        GenStartCommentLine(); printf2("else\n");
#endif
        tok = GetToken();
        tok = ParseStatement(tok, BrkCntTarget, casesIdx);
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
      int cond = -1;
      static int expr3Stack[STACK_SIZE / 2][2];
      static int expr3Sp;
#ifndef NO_FOR_DECL
      int decl = 0;
      int undoSymbolsPtr = 0, undoLocalOfs = 0, undoIdents = 0;
#endif
#ifndef NO_ANNOTATIONS
      GenStartCommentLine(); printf2("for\n");
#endif
      tok = GetToken();
      if (tok != '(')
        //error("ParseStatement(): '(' expected after 'for'\n");
        errorUnexpectedToken(tok);

      tok = GetToken();
#ifndef NO_FOR_DECL
      if (TokenStartsDeclaration(tok, 1))
      {
        decl = 1;
        undoSymbolsPtr = SyntaxStackCnt;
        undoLocalOfs = CurFxnLocalOfs;
        undoIdents = IdentTableLen;
        // Declarations made in the first clause of for should not:
        // - collide with previous outer declarations
        // - be visible/exist outside for
        // For this reason the declaration gets its own subscope.
        PushSyntax('#'); // mark the beginning of a new scope
        tok = ParseDecl(tok, NULL, 0, 0);
      }
      else
      // fallthrough
#endif
      {
        if ((tok = ParseExpr(tok, &gotUnary, &synPtr, &constExpr, &exprVal, 0, 0)) != ';')
          //error("ParseStatement(): ';' expected after 'for ( expression'\n");
          errorUnexpectedToken(tok);
        if (gotUnary)
        {
          GenExpr();
        }
        tok = GetToken();
      }

      GenNumLabel(labelBefore);
      if ((tok = ParseExpr(tok, &gotUnary, &synPtr, &constExpr, &exprVal, 0, 0)) != ';')
        //error("ParseStatement(): ';' expected after 'for ( expression ; expression'\n");
        errorUnexpectedToken(tok);
      if (gotUnary)
      {
        // DONE: void control expressions
        //error("ParseStatement(): unexpected 'void' expression in 'for ( ; expression ; )'\n");
        // Bar void and struct/union
        scalarTypeCheck(synPtr);

        if (constExpr)
        {
#ifndef NO_FP
          if (isFloat(synPtr))
            exprVal = fcmp(exprVal, i2f(0), -1);
#endif
          // Special cases for for(...; 0; ...) and for(...; 1; ...)
          cond = truncInt(exprVal) != 0;
        }
        else
        {
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
#ifndef NO_FP
            if (isFloat(synPtr))
            {
              // insert a call to compare the float with 0.0
              // the returned value will be one of -1,0,+1, that is, 0 if 0, +/-1 otherwise,
              // IOW, suitable for conditional jump on zero/non-zero
              ins(0, ',');
              ins2(0, tokNumInt, i2f(0));
              ins2(0, '(', SizeOfWord * 2);
              push(',');
              push2(tokIdent, FindIdent(FpFxnName[FXNFCMPL]));
              push2(')', SizeOfWord * 2);
            }
#endif
            push(tokReturn); // value produced by generated code is used
            GenExpr();
            GenJumpIfZero(labelAfter);
            break;
          }
        }
      }
      else
      {
        // Special case for for(...; ; ...)
        cond = 1;
      }
      if (!cond)
        // Special case for for(...; 0; ...)
        GenJumpUncond(labelAfter);

      tok = GetToken();
      if ((tok = ParseExpr(tok, &gotUnary, &synPtr, &constExpr, &exprVal, 0, 0)) != ')')
        //error("ParseStatement(): ')' expected after 'for ( expression ; expression ; expression'\n");
        errorUnexpectedToken(tok);

      // Try to reorder expr3 with body to reduce the number of jumps, favor small expr3's
      if (gotUnary && sp <= 16 && (unsigned)sp <= sizeof expr3Stack / sizeof expr3Stack[0] - expr3Sp)
      {
        int cnt = sp;
        // Stash the stack containing expr3
        memcpy(expr3Stack + expr3Sp, stack, cnt * sizeof stack[0]);
        expr3Sp += cnt;

        // Body
        tok = GetToken();
        brkCntTarget[0] = labelAfter; // break target
        brkCntTarget[1] = labelExpr3; // continue target
        tok = ParseStatement(tok, brkCntTarget, casesIdx);

        // Unstash expr3 and generate code for it
        expr3Sp -= cnt;
        memcpy(stack, expr3Stack + expr3Sp, cnt * sizeof stack[0]);
        sp = cnt;
        GenNumLabel(labelExpr3);
        GenExpr();

        // Special case for for(...; 0; ...)
        if (cond)
          GenJumpUncond(labelBefore);
      }
      else
      {
        if (gotUnary)
        {
          GenJumpUncond(labelBody);
          // expr3
          GenNumLabel(labelExpr3);
          GenExpr();
          GenJumpUncond(labelBefore);
          GenNumLabel(labelBody);
        }

        // Body
        tok = GetToken();
        brkCntTarget[0] = labelAfter; // break target
        brkCntTarget[1] = gotUnary ? labelExpr3 : (cond ? labelBefore : labelAfter); // continue target
        tok = ParseStatement(tok, brkCntTarget, casesIdx);

        // Special case for for(...; 0; ...)
        if (brkCntTarget[1] != labelAfter)
          GenJumpUncond(brkCntTarget[1]);
      }

      GenNumLabel(labelAfter);

#ifndef NO_FOR_DECL
      // undo any declarations made in the first clause of for
      if (decl)
      {
        UndoNonLabelIdents(undoIdents); // remove all identifier names, except those of labels
        SyntaxStackCnt = undoSymbolsPtr; // remove all params and locals
        CurFxnLocalOfs = undoLocalOfs; // destroy on-stack local variables
      } 
#endif
    }
    else if (tok == tokBreak)
    {
#ifndef NO_ANNOTATIONS
      GenStartCommentLine(); printf2("break\n");
#endif
      if ((tok = GetToken()) != ';')
        //error("ParseStatement(): ';' expected\n");
        errorUnexpectedToken(tok);
      tok = GetToken();
      if (BrkCntTarget == NULL)
        //error("ParseStatement(): 'break' must be within 'while', 'for' or 'switch' statement\n");
        errorCtrlOutOfScope();
      GenJumpUncond(BrkCntTarget[0]);
    }
    else if (tok == tokCont)
    {
#ifndef NO_ANNOTATIONS
      GenStartCommentLine(); printf2("continue\n");
#endif
      if ((tok = GetToken()) != ';')
        //error("ParseStatement(): ';' expected\n");
        errorUnexpectedToken(tok);
      tok = GetToken();
      if (BrkCntTarget == NULL || BrkCntTarget[1] == 0)
        //error("ParseStatement(): 'continue' must be within 'while' or 'for' statement\n");
        errorCtrlOutOfScope();
      GenJumpUncond(BrkCntTarget[1]);
    }
    else if (tok == tokSwitch)
    {
      int undoCases = CasesCnt;
      int brkLabel = LabelCnt++;
      int lbl = LabelCnt++;
      int i;
#ifndef NO_ANNOTATIONS
      GenStartCommentLine(); printf2("switch\n");
#endif

      tok = GetToken();
      if (tok != '(')
        //error("ParseStatement(): '(' expected after 'switch'\n");
        errorUnexpectedToken(tok);

      tok = GetToken();
      if ((tok = ParseExpr(tok, &gotUnary, &synPtr, &constExpr, &exprVal, 0, 0)) != ')')
        //error("ParseStatement(): ')' expected after 'switch ( expression'\n");
        errorUnexpectedToken(tok);

      if (!gotUnary)
        //error("ParseStatement(): expression expected in 'switch ( expression )'\n");
        errorUnexpectedToken(tok);

      // DONE: void control expressions
      //error("ParseStatement(): unexpected 'void' expression in 'switch ( expression )'\n");
      anyIntTypeCheck(synPtr);

      push(tokReturn); // value produced by generated code is used
      GenExpr();

      tok = GetToken();

      // Skip the code for the cases
      GenJumpUncond(lbl);

      brkCntTarget[0] = brkLabel; // break target
      brkCntTarget[1] = 0; // continue target
      if (BrkCntTarget)
      {
        // Preserve the continue target
        brkCntTarget[1] = BrkCntTarget[1]; // continue target
      }

      // Reserve a slot in the case table for the default label
      AddCase(0, 0);

      tok = ParseStatement(tok, brkCntTarget, CasesCnt);

      // If there's no default target, will use the break target as default
      if (!Cases[undoCases][1])
        Cases[undoCases][1] = brkLabel;

      // End of switch reached (not via break), skip conditional jumps
      GenJumpUncond(brkLabel);
      // Generate conditional jumps
      GenNumLabel(lbl);
      for (i = undoCases + 1; i < CasesCnt; i++)
      {
        GenJumpIfEqual(Cases[i][0], Cases[i][1]);
      }
      // If none of the cases matches, take the default case
      if (Cases[undoCases][1] != brkLabel)
        GenJumpUncond(Cases[undoCases][1]);
      GenNumLabel(brkLabel); // break label

      CasesCnt = undoCases;
    }
    else if (tok == tokCase)
    {
      int i;
#ifndef NO_ANNOTATIONS
      GenStartCommentLine(); printf2("case\n");
#endif

      if (!casesIdx)
        //error("ParseStatement(): 'case' must be within 'switch' statement\n");
        errorCtrlOutOfScope();

      tok = GetToken();
      if ((tok = ParseExpr(tok, &gotUnary, &synPtr, &constExpr, &exprVal, 0, 0)) != ':')
        //error("ParseStatement(): ':' expected after 'case expression'\n");
        errorUnexpectedToken(tok);

      if (!gotUnary)
        errorUnexpectedToken(tok);

      anyIntTypeCheck(synPtr);
      if (!constExpr)
        //error("ParseStatement(): constant integer expression expected in 'case expression :'\n");
        errorNotConst();

      // Check for dups
      exprVal = truncInt(exprVal);
      for (i = casesIdx; i < CasesCnt; i++)
        if (Cases[i][0] == exprVal)
          error("Duplicate case value\n");

      AddCase(exprVal, LabelCnt);
      GenNumLabel(LabelCnt++); // case exprVal:

      tok = GetToken();

      // a statement is needed after "case:"
      statementNeeded = 1;
    }
    else if (tok == tokDefault)
    {
#ifndef NO_ANNOTATIONS
      GenStartCommentLine(); printf2("default\n");
#endif

      if (!casesIdx)
        //error("ParseStatement(): 'default' must be within 'switch' statement\n");
        errorCtrlOutOfScope();

      if (Cases[casesIdx - 1][1])
        //error("ParseStatement(): only one 'default' allowed in 'switch'\n");
        errorUnexpectedToken(tok);

      tok = GetToken();
      if (tok != ':')
        //error("ParseStatement(): ':' expected after 'default'\n");
        errorUnexpectedToken(tok);

      tok = GetToken();

      GenNumLabel(Cases[casesIdx - 1][1] = LabelCnt++); // default:

      // a statement is needed after "default:"
      statementNeeded = 1;
    }
    else if (tok == tok_Asm)
    {
      tok = GetToken();
      if (tok != '(')
        //error("ParseStatement(): '(' expected after 'asm'\n");
        errorUnexpectedToken(tok);

      tok = GetToken();
      if (tok != tokLitStr)
        //error("ParseStatement(): string literal expression expected in 'asm ( expression )'\n");
        errorUnexpectedToken(tok);

      do
      {
        GetString('"', 0, 'a');
        tok = GetToken();
      } while (tok == tokLitStr); // concatenate adjacent string literals
      printf2("\n");

      if (tok != ')')
        //error("ParseStatement(): ')' expected after 'asm ( expression'\n");
        errorUnexpectedToken(tok);

      tok = GetToken();
      if (tok != ';')
        //error("ParseStatement(): ';' expected after 'asm ( expression )'\n");
        errorUnexpectedToken(tok);

      tok = GetToken();
    }
    else if (tok == tokGoto)
    {
      if ((tok = GetToken()) != tokIdent)
        errorUnexpectedToken(tok);
#ifndef NO_ANNOTATIONS
      GenStartCommentLine(); printf2("goto %s\n", TokenIdentName);
#endif
      GenJumpUncond(AddGotoLabel(TokenIdentName, 0));
      if ((tok = GetToken()) != ';')
        errorUnexpectedToken(tok);
      tok = GetToken();
    }
    else
    {
      tok = ParseExpr(tok, &gotUnary, &synPtr, &constExpr, &exprVal, tokGotoLabel, 0);
      if (tok == tokGotoLabel)
      {
        // found a label
#ifndef NO_ANNOTATIONS
        GenStartCommentLine(); printf2("%s:\n", IdentTable + stack[0][1]);
#endif
        GenNumLabel(AddGotoLabel(IdentTable + stack[0][1], 1));
        // a statement is needed after "label:"
        statementNeeded = 1;
      }
      else
      {
        if (tok != ';')
          //error("ParseStatement(): ';' expected\n");
          errorUnexpectedToken(tok);
        if (gotUnary)
          GenExpr();
      }
      tok = GetToken();
    }
  } while (statementNeeded);

  return tok;
}

// TBD!!! think of ways of getting rid of casesIdx
STATIC
int ParseBlock(int BrkCntTarget[2], int casesIdx)
{
  int tok = GetToken();

  // Catch redeclarations of function parameters by not
  // beginning a new scope if this block begins a function
  // (the caller of ParseBlock() must've begun a new scope
  // already, before the function parameters).
  if (BrkCntTarget == BrkCntTargetFxn)
    BrkCntTarget = NULL;
  else
  // Otherwise begin a new scope.
    PushSyntax('#');

  for (;;)
  {
    if (tok == 0)
      return tok;

    if (tok == '}' && ParseLevel > 0)
      return tok;

    if (TokenStartsDeclaration(tok, 0))
    {
      tok = ParseDecl(tok, NULL, 0, 1);
#ifndef NO_TYPEDEF_ENUM
      if (tok == tokGotoLabel)
      {
        // found a label
#ifndef NO_ANNOTATIONS
        GenStartCommentLine(); printf2("%s:\n", TokenIdentName);
#endif
        GenNumLabel(AddGotoLabel(TokenIdentName, 1));
        tok = GetToken();
        // a statement is needed after "label:"
        tok = ParseStatement(tok, BrkCntTarget, casesIdx);
      }
#endif
    }
    else if (ParseLevel > 0 || tok == tok_Asm)
    {
      tok = ParseStatement(tok, BrkCntTarget, casesIdx);
    }
    else
      //error("ParseBlock(): Unexpected token %s\n", GetTokenName(tok));
      errorUnexpectedToken(tok);
  }
}

int main(int argc, char** argv)
{
  // gcc/MinGW inserts a call to __main() here.
  int i;

  // Run-time initializer for SyntaxStack0[] to reduce
  // executable file size (SyntaxStack0[] will be in .bss)
  static unsigned char SyntaxStackInit[] =
  {
    tokVoid,     // SymVoidSynPtr
    tokInt,      // SymIntSynPtr
    tokUnsigned, // SymUintSynPtr
    tokVoid,     // SymWideCharSynPtr
    tokFloat,    // SymFloatSynPtr
    tokIdent,    // SymFuncPtr
    '[',
    tokNumUint,
    ']',
    tokChar
  }; // SyntaxStackCnt must be initialized to the number of elements in SyntaxStackInit[]
  memcpy(SyntaxStack0, SyntaxStackInit, sizeof SyntaxStackInit);
  SyntaxStackCnt = sizeof SyntaxStackInit / sizeof SyntaxStackInit[0];

#ifdef __SMALLER_C__
#ifdef DETERMINE_VA_LIST
  DetermineVaListType();
#endif
#endif

  SyntaxStack1[SymFuncPtr] = DummyIdent = AddIdent("");

#ifndef NO_FP
  {
    static float testFloat = -5915522.0f * 1.5f;
    static unsigned testUint = 0xCB076543; // expected representation of the above
    if (memcmp(&testFloat, &testUint, sizeof testFloat))
      error("IEEE 754 floating point required on host\n");
  }
  for (i = 0; (unsigned)i < sizeof FpFxnName / sizeof FpFxnName[0]; i++)
    AddIdent(FpFxnName[i]);
#endif

  GenInit();

  // Parse the command line arguments
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
#ifndef NO_WCHAR
    else if (!strcmp(argv[i], "-signed-wchar"))
    {
      WideCharIsSigned = 1;
      continue;
    }
    else if (!strcmp(argv[i], "-unsigned-wchar"))
    {
      // this is the default option
      WideCharIsSigned = 0;
      continue;
    }
    else if (!strcmp(argv[i], "-short-wchar"))
    {
      // this is the default option
      SizeOfWideChar = 2;
      continue;
    }
#ifdef CAN_COMPILE_32BIT
    else if (!strcmp(argv[i], "-long-wchar"))
    {
      SizeOfWideChar = 4;
      continue;
    }
#endif
#endif
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
    else if (!strcmp(argv[i], "-label"))
    {
      if (i + 1 < argc)
      {
        LabelCnt = atoi(argv[++i]);
        continue;
      }
    }
    else if (!strcmp(argv[i], "-no-externs"))
    {
      GenExterns = 0;
      continue;
    }
    else if (!strcmp(argv[i], "-verbose"))
    {
      warnings = verbose = 1;
      continue;
    }
    else if (!strcmp(argv[i], "-Wall"))
    {
      warnings = 1;
      continue;
    }
#ifndef NO_PREPROCESSOR
    else if (!strcmp(argv[i], "-I") || !strcmp(argv[i], "-SI"))
    {
      if (i + 1 < argc)
      {
        int len = strlen(argv[++i]) + 1;
        if (argv[i - 1][1] == 'I')
        {
          if (MAX_SEARCH_PATH - SearchPathsLen < len)
            //error("Path name too long\n");
            errorFileName();
          strcpy(SearchPaths + SearchPathsLen, argv[i]);
          SearchPathsLen += len;
        }
        else
        {
          if (MAX_SEARCH_PATH - SysSearchPathsLen < len)
            //error("Path name too long\n");
            errorFileName();
          strcpy(SysSearchPaths + SysSearchPathsLen, argv[i]);
          SysSearchPathsLen += len;
        }
        continue;
      }
    }
    else if (!strcmp(argv[i], "-nopp"))
    {
      // TBD!!! don't do preprocessing when this option is present
      continue;
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
            if ((bad = !(id[j] == '_' || (!j * isalpha(id[j] & 0xFFu) + j * isalnum(id[j] & 0xFFu)))) != 0)
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
    else if (argv[i][0] == '-')
    {
      // unknown option
    }
    else if (FileCnt == 0)
    {
      // If it's none of the known options,
      // assume it's the source code file name
      if (strlen(argv[i]) > MAX_FILE_NAME_LEN)
        //error("File name too long\n");
        errorFileName();
      strcpy(FileNames[0], argv[i]);
      if ((Files[0] = fopen(FileNames[0], "r")) == NULL)
        //error("Cannot open file \"%s\"\n", FileNames[0]);
        errorFile(FileNames[0]);
      LineNos[0] = LineNo;
      LinePoss[0] = LinePos;
      FileCnt++;
      continue;
    }
    else if (FileCnt == 1 && OutFile == NULL)
    {
      // This should be the output file name
      if ((OutFile = fopen(argv[i], "w")) == NULL)
        //error("Cannot open output file \"%s\"\n", argv[i]);
        errorFile(argv[i]);
      continue;
    }

    error("Invalid or unsupported command line option\n");
  }

  if (!FileCnt)
    error("Input file not specified\n");
  if (!OutFile)
    error("Output file not specified\n");

#ifndef NO_WCHAR
  WideCharType1 = WideCharIsSigned ? tokInt : tokUnsigned;
  WideCharType2 = WideCharType1 ^ tokInt ^ tokUnsigned;
#ifdef CAN_COMPILE_32BIT
  if (SizeOfWideChar > SizeOfWord)
    error("Wide char too wide\n");
  if (SizeOfWord == 4 && SizeOfWideChar == 2)
  {
    WideCharType1 = WideCharIsSigned ? tokShort : tokUShort;
    WideCharType2 = WideCharType1 ^ tokShort ^ tokUShort;
  }
#endif
  SyntaxStack0[SymWideCharSynPtr] = WideCharType1;
#endif

  GenInitFinalize();

#ifndef NO_PREPROCESSOR
  // Define a few macros useful for conditional compilation
  DefineMacro("__SMALLER_C__", "0x0100");
  if (SizeOfWord == 2)
    DefineMacro("__SMALLER_C_16__", "");
#ifdef CAN_COMPILE_32BIT
  else if (SizeOfWord == 4)
    DefineMacro("__SMALLER_C_32__", "");
#endif
#ifdef CAN_COMPILE_32BIT
  if (OutputFormat == FormatSegHuge)
    DefineMacro("__HUGE__", "");
  if (OutputFormat == FormatSegUnreal)
    DefineMacro("__UNREAL__", "");
#endif
  if (CharIsSigned)
    DefineMacro("__SMALLER_C_SCHAR__", "");
  else
    DefineMacro("__SMALLER_C_UCHAR__", "");
#ifndef NO_WCHAR
  if (WideCharIsSigned)
    DefineMacro("__SMALLER_C_SWCHAR__", "");
  else
    DefineMacro("__SMALLER_C_UWCHAR__", "");
#ifdef CAN_COMPILE_32BIT
  if (SizeOfWideChar == 4)
    DefineMacro("__SMALLER_C_WCHAR32__", "");
  else
#endif
    DefineMacro("__SMALLER_C_WCHAR16__", "");
#endif
#endif // NO_PREPROCESSOR

  // populate CharQueue[] with the initial file characters
  ShiftChar();

  puts2(FileHeader);

  // compile
#ifndef NO_PPACK
  PragmaPackValue = SizeOfWord;
#endif
  ParseBlock(NULL, 0);

  GenFin();

#ifndef NO_ANNOTATIONS
  DumpSynDecls();
#endif
#ifndef NO_PREPROCESSOR
#ifndef NO_ANNOTATIONS
  DumpMacroTable();
#endif
#endif
#ifndef NO_ANNOTATIONS
  DumpIdentTable();
#endif

  GenStartCommentLine(); printf2("Next label number: %d\n", LabelCnt);

  if (warnings && warnCnt)
    printf("%d warnings\n", warnCnt);
  GenStartCommentLine(); printf2("Compilation succeeded.\n");

  if (OutFile)
    fclose(OutFile);

  return 0;
}
