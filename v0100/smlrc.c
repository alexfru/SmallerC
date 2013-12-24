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

// You need to declare __setargv__ as an extern symbol when bootstrapping with
// Turbo C++ in order to access main()'s argc and argv params.
extern char _setargv__;

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

#ifndef MAX_MACRO_TABLE_LEN
#define MAX_MACRO_TABLE_LEN  4096
#endif

#ifndef MAX_STRING_TABLE_LEN
#define MAX_STRING_TABLE_LEN 512
#endif

#ifndef MAX_IDENT_TABLE_LEN
#define MAX_IDENT_TABLE_LEN  (4096+288)
#endif

#define MAX_FILE_NAME_LEN    95

#ifndef NO_PREPROCESSOR
#define MAX_INCLUDES         8
#define PREP_STACK_SIZE      8
#define MAX_SEARCH_PATH      256
#else
#define MAX_INCLUDES         1
#define PREP_STACK_SIZE      1
#define MAX_SEARCH_PATH      1
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

#define FormatFlat      0
#define FormatSegmented 1
#define FormatSegTurbo  2

#ifndef SYNTAX_STACK_MAX
#define SYNTAX_STACK_MAX (2048+384)
#endif

#define SymVoidSynPtr 0
#define SymIntSynPtr  1
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
PROTO void GenLabel(char* Label, int Static);
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

PROTO unsigned GenStrData(int generatingCode, unsigned requiredLen);
PROTO void GenExpr(void);

PROTO void PushSyntax(int t);
PROTO void PushSyntax2(int t, int v);

PROTO void DumpSynDecls(void);

PROTO void push2(int v, int v2);
PROTO void ins2(int pos, int v, int v2);
PROTO void ins(int pos, int v);
PROTO void del(int pos, int cnt);

PROTO int TokenStartsDeclaration(int t, int params);
PROTO int ParseDecl(int tok, int cast);

PROTO void ShiftChar(void);
PROTO int puts2(char*);
PROTO int printf2(char*, ...);

PROTO void error(char* format, ...);
PROTO void warning(char* format, ...);
PROTO void errorFile(char* n);
PROTO void errorFileName(void);
PROTO void errorInternal(int n);
PROTO void errorChrStr(void);
PROTO void errorUnexpectedToken(int tok);
PROTO void errorDirective(void);
PROTO void errorCtrlOutOfScope(void);
PROTO void errorDecl(void);
PROTO void errorVarSize(void);
PROTO void errorInit(void);
PROTO void errorUnexpectedVoid(void);
PROTO void errorOpType(void);
PROTO void errorNotLvalue(void);
PROTO void errorNotConst(void);
PROTO void errorLongExpr(void);

PROTO int FindSymbol(char* s);
PROTO int SymType(int SynPtr);
PROTO int GetDeclSize(int SyntaxPtr, int SizeForDeref);

PROTO int ParseExpr(int tok, int* GotUnary, int* ExprTypeSynPtr, int* ConstExpr, int* ConstVal, int commaSeparator, int label);
PROTO int GetFxnInfo(int ExprTypeSynPtr, int* MinParams, int* MaxParams, int* ReturnExprTypeSynPtr);

// all data

int verbose = 0;
int warnCnt = 0;

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
    labell uchar:   temporary identifier's (char*) label number low 8 bits
    labelh uchar:   temporary identifier's (char*) label number high 8 bits
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

#define MAX_GOTO_LABELS 16
int gotoLabels[MAX_GOTO_LABELS][2];
// gotoLabStat[]: bit 1 = used (by "goto label;"), bit 0 = defined (with "label:")
char gotoLabStat[MAX_GOTO_LABELS];
int gotoLabCnt = 0;

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

// TBD??? merge expression and operator stacks into one
int stack[STACK_SIZE][2];
int sp = 0;

#define OPERATOR_STACK_SIZE STACK_SIZE
int opstack[OPERATOR_STACK_SIZE][2];
int opsp = 0;

// smc.c data

int OutputFormat = FormatSegmented;
int GenExterns = 1;

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

// TBD??? implement a function to allocate N labels with overflow checks
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
    error("Macro identifier too long '%s'\n", name);

  if (MAX_MACRO_TABLE_LEN - MacroTableLen < l + 3)
    error("Macro table exhausted\n");

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
    error("Macro table exhausted\n");

  if (MacroTable[MacroTableLen] >= 127)
    error("Macro definition too long\n");

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

int KeepStringTable = 0;

void PurgeStringTable(void)
{
  if (!KeepStringTable)
    StringTableLen = 0;
}

void AddString(int label, char* str, int len)
{
  if (len > 127)
    error("String literal too long\n");

  if (MAX_STRING_TABLE_LEN - StringTableLen < 2 + 1 + len)
    error("String table exhausted\n");

  StringTable[StringTableLen++] = label & 0xFF;
  StringTable[StringTableLen++] = (label >> 8) & 0xFF;

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

    lab = StringTable[i] & 0xFF;
    lab += (StringTable[i + 1] & 0xFFu) << 8;

    if (lab == label)
      return StringTable + i + 2;

    i += 2;
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
    error("Identifier too long\n");

  if (MAX_IDENT_TABLE_LEN - IdentTableLen < len + 2)
    error("Identifier table exhausted\n");

  strcpy(IdentTable + IdentTableLen, name);
  IdentTableLen += len + 1;
  IdentTable[IdentTableLen++] = len + 1;

  return i;
}

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

char* rws[] =
{
  "break", "case", "char", "continue", "default", "do", "else",
  "extern", "for", "if", "int", "return", "signed", "sizeof",
  "static", "switch", "unsigned", "void", "while", "asm", "auto",
  "const", "double", "enum", "float", "goto", "inline", "long",
  "register", "restrict", "short", "struct", "typedef", "union",
  "volatile", "_Bool", "_Complex", "_Imaginary"
};

unsigned char rwtk[] =
{
  tokBreak, tokCase, tokChar, tokCont, tokDefault, tokDo, tokElse,
  tokExtern, tokFor, tokIf, tokInt, tokReturn, tokSigned, tokSizeof,
  tokStatic, tokSwitch, tokUnsigned, tokVoid, tokWhile, tok_Asm, tokAuto,
  tokConst, tokDouble, tokEnum, tokFloat, tokGoto, tokInline, tokLong,
  tokRegister, tokRestrict, tokShort, tokStruct, tokTypedef, tokUnion,
  tokVolatile, tok_Bool, tok_Complex, tok_Imagin
};

int GetTokenByWord(char* word)
{
  unsigned i;

  for (i = 0; i < sizeof rws / sizeof rws[0]; i++)
    if (!strcmp(rws[i], word))
      return rwtk[i];

  return tokIdent;
}

char* GetTokenName(int token)
{
  unsigned i;

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

  // Helper (pseudo-)tokens:
  case tokNumInt: return "<NumInt>";     case tokNumUint: return "<NumUint>";
  case tokLitStr: return "<LitStr>";     case tokIdent: return "<Ident>";
  case tokLocalOfs: return "<LocalOfs>"; case tokShortCirc: return "<ShortCirc>";

  case tokSChar: return "signed char";   case tokUChar: return "unsigned char";
  }

  // Reserved keywords:
  for (i = 0; i < sizeof rws / sizeof rws[0]; i++)
    if (rwtk[i] == token)
      return rws[i];

  //error("Internal Error: GetTokenName(): Invalid token %d\n", token);
  errorInternal(1);
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
    //if (quot == '<' && !SearchPathsLen)
    //  error("Cannot open file \"%s\", include search path unspecified\n", TokenValueString);

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

void GetIdent(void)
{
  char* p = CharQueue;

  if (*p != '_' && !isalpha(*p & 0xFFu))
    error("Identifier expected\n");

  if ((*p == 'L' || *p == 'l') &&
      (p[1] == '\'' || p[1] == '\"'))
    //error("Wide characters and strings not supported\n");
    errorChrStr();

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
            while (*p != '\0' && (isdigit(*p & 0xFFu) || strchr("abcdefABCDEF", *p)))
            {
              c = (c * 16) & 0xFF;
              if (*p >= 'a') c += *p - 'a' + 10;
              else if (*p >= 'A') c += *p - 'A' + 10;
              else c += *p - '0';
              ShiftCharN(1);
              cnt++;
            }
            if (!cnt)
              //error("Unsupported or invalid character/string constant\n");
              errorChrStr();
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
              //error("Unsupported or invalid character/string constant\n");
              errorChrStr();
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
          //error("Character constant too long\n");
          errorChrStr();
      }
      else if (TokenStringLen == MAX_STRING_LEN)
        error("String literal too long\n");

      TokenValueString[TokenStringLen++] = ch;
      TokenValueString[TokenStringLen] = '\0';
    } // endof while (!(*p == '\0' || *p == terminator || strchr("\a\b\f\n\r\t\v", *p)))

    if (*p != terminator)
      //error("Unsupported or invalid character/string constant\n");
      errorChrStr();

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
  if (PrepSp >= PREP_STACK_SIZE)
    error("Too many #if(n)def's\n");
  PrepStack[PrepSp][0] = PrepDontSkipTokens;
  PrepStack[PrepSp++][1] = NoSkip;
  PrepDontSkipTokens &= NoSkip;
}

int popPrep(void)
{
  if (PrepSp <= 0)
    error("#else or #endif without #if(n)def\n");
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
  char* eTooBig = "Constant too big\n";

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
      type = 'h';
    }
    // this is an octal constant
    else while ((ch = *p) >= '0' && ch <= '7')
    {
      ch -= '0';
      if (PrepDontSkipTokens && (n * 8 / 8 != n || n * 8 + ch < n * 8))
        error(eTooBig);
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
        error(eTooBig);
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
    error("Constant too big for %d-bit type\n", SizeOfWord * 8);

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
    error("Constant too big for %d-bit signed type\n", SizeOfWord * 8);

  return tokNumUint;
}

int GetTokenInner(void)
{
  char* p = CharQueue;
  int ch = *p;

  // these single-character tokens/operators need no further processing
  if (strchr(",;:()[]{}~?", ch) != NULL)
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
  if (isdigit(ch & 0xFFu))
    return GetNumber();

  // parse character and string constants
  if (ch == '\'' || ch == '\"')
  {
    GetString(ch, 1);

    if (ch == '\'')
    {
      if (TokenStringLen != 1)
        //error("Character constant too short\n");
        errorChrStr();

      TokenValueInt = TokenValueString[0] & 0xFF;
      TokenValueInt -= (CharIsSigned && TokenValueInt >= 0x80) * 0x100;
      return tokNumInt;
    }

    return tokLitStr;
  } // endof if (ch == '\'' || ch == '\"')

  return tokEof;
}

// TBD??? implement file I/O for input source code and output code (use fxn ptrs/wrappers to make librarization possible)
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
      if ((midx = FindMacro(TokenIdentName)) >= 0)
      {
        // this is a macro identifier, need to expand it
        int len = MacroTable[midx];

        if (MAX_CHAR_QUEUE_LEN - CharQueueLen < len + 1)
          error("Too long expansion of macro '%s'\n", TokenIdentName);

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
        if (*p == '\"')
          GetString('\"', 0);
        else if (*p == '<')
          GetString('>', 0);
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

      //error("Unsupported or invalid preprocessor directive\n");
      errorDirective();
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

      // TBD!!! should also support the following C89 form:
      // # line linenum filename-opt

      SkipSpace(0);

      if (!isdigit(*p & 0xFFu) || GetNumber() != tokNumInt)
        //error("Invalid line number in preprocessor output\n");
        errorDirective();
      line = GetTokenValueInt();

      SkipSpace(0);

      if (*p == '\"')
        GetString('\"', 0);
      else if (*p == '<')
        GetString('>', 0);
      else
        //error("Invalid file name in preprocessor output\n");
        errorFileName();

      if (strlen(GetTokenValueString()) > MAX_FILE_NAME_LEN)
        //error("File name too long in preprocessor output\n");
        errorFileName();

      SkipSpace(0);

      while (!strchr("\r\n", *p))
      {
        if (!isdigit(*p & 0xFFu) || GetNumber() != tokNumInt)
          //error("Invalid flag in preprocessor output\n");
          errorDirective();
        SkipSpace(0);
      }

      LineNo = line - 1; // "line" is the number of the next line
      LinePos = 1;
      strcpy(FileNames[0], GetTokenValueString());

      continue;
    } // endof if (ch == '#')
#endif // #ifndef NO_PREPROCESSOR

    error("Invalid or unsupported character with code 0x%02X\n", *p & 0xFFu);
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
  if (sp >= STACK_SIZE)
    //error("expression stack overflow!\n");
    errorLongExpr();
  stack[sp][0] = v;
  stack[sp++][1] = v2;
}

void push(int v)
{
  push2(v, 0);
}

int stacktop()
{
  if (sp == 0)
    //error("expression stack underflow!\n");
    errorInternal(3);
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
  if (sp >= STACK_SIZE)
    //error("expression stack overflow!\n");
    errorLongExpr();
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
  if (opsp >= OPERATOR_STACK_SIZE)
    //error("operator stack overflow!\n");
    errorLongExpr();
  opstack[opsp][0] = v;
  opstack[opsp++][1] = v2;
}

void pushop(int v)
{
  pushop2(v, 0);
}

int opstacktop()
{
  if (opsp == 0)
    //error("operator stack underflow!\n");
    errorInternal(4);
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
  case '?':
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

int expr(int tok, int* gotUnary, int commaSeparator);

char* lab2str(char* p, int n)
{
  do
  {
    *--p = '0' + n % 10;
    n /= 10;
  } while (n);

  return p;
}

int exprUnary(int tok, int* gotUnary, int commaSeparator, int argOfSizeOf)
{
  int decl = 0;
  *gotUnary = 0;

  if (isop(tok) && (isunary(tok) || strchr("&*+-", tok) != NULL))
  {
    int lastTok = tok;
    tok = exprUnary(GetToken(), gotUnary, commaSeparator, lastTok == tokSizeof);
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
      int len, id;
      char s[1 + (2 + CHAR_BIT * sizeof lbl) / 3];
      char *p = s + sizeof s;

      // imitate definition: char #[len] = "...";

      AddString(lbl, GetTokenValueString(), len = 1 + GetTokenValueStringLength());

      *--p = '\0';
      p = lab2str(p, lbl);

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
    else if (tok == tokIdent)
    {
      push2(tok, AddIdent(GetTokenIdentName()));
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

        tok = ParseDecl(tok, !argOfSizeOf);
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

        SyntaxStack[synPtr][1] = AddIdent(p);
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
        push2(tokIdent, SyntaxStack[synPtr][1]);
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
        }
        else // if (brak == '[')
        {
          for (;;)
          {
            tok = GetToken();
            tok = expr(tok, gotUnary, 0);
            if (!*gotUnary)
              //error("exprUnary(): primary expression expected in '[]'\n");
              errorUnexpectedToken(tok);
            if (tok == ']') break; // end of index
            //error("exprUnary(): ']' expected, unexpected token %s\n", GetTokenName(tok));
            errorUnexpectedToken(tok);
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

  tok = exprUnary(tok, gotUnary, commaSeparator, 0);

  while (tok != tokEof && strchr(",;:)]}", tok) == NULL && *gotUnary)
  {
    if (isop(tok) && !isunary(tok))
    {
      //int lastTok = tok;

      while (precedGEQ(opstacktop(), tok))
      {
        int v, v2;
        int c = 0;
        // move ?expr: as a whole to the expression stack as "expr?"
        do
        {
          v = popop2(&v2);
          if (v != ':')
            push2(v, v2);
          c += (v == ':') - (v == '?');
        } while (c);
      }

      // here: preced(postacktop()) < preced(tok)
      pushop(tok);

      // treat the ternary/conditional operator ?expr: as a pseudo binary operator
      if (tok == '?')
      {
        int ssp = sp;

        tok = expr(GetToken(), gotUnary, 0);
        if (!*gotUnary || tok != ':')
          errorUnexpectedToken(tok);

        // move ?expr: as a whole to the operator stack
        // this is beautiful and ugly at the same time
        while (sp > ssp)
        {
          int v, v2;
          v = pop2(&v2);
          pushop2(v, v2);
        }

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
    if (v != ':')
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
        //error("decayArray(): cannot do pointer arithmetic on a pointer to 'void'\n");
        errorUnexpectedVoid();
      if (SyntaxStack[-*ExprTypeSynPtr][0] == '(')
        //error("decayArray(): cannot do pointer arithmetic on a pointer to a function\n");
        errorOpType();
    }
    else
    {
      if (SyntaxStack[*ExprTypeSynPtr][0] == '(')
        //error("decayArray(): cannot do arithmetic on a function\n");
        errorOpType();
    }
  }
}

void nonVoidTypeCheck(int ExprTypeSynPtr, int tok)
{
  (void)tok;
  if (ExprTypeSynPtr >= 0 && SyntaxStack[ExprTypeSynPtr][0] == tokVoid)
    //error("nonVoidTypeCheck(): unexpected operand type 'void' for operator '%s'\n", GetTokenName(tok));
    errorUnexpectedVoid();
}

void numericTypeCheck(int ExprTypeSynPtr, int tok)
{
  (void)tok;
  if (ExprTypeSynPtr >= 0 &&
      (SyntaxStack[ExprTypeSynPtr][0] == tokChar ||
       SyntaxStack[ExprTypeSynPtr][0] == tokSChar ||
       SyntaxStack[ExprTypeSynPtr][0] == tokUChar ||
       SyntaxStack[ExprTypeSynPtr][0] == tokInt ||
       SyntaxStack[ExprTypeSynPtr][0] == tokUnsigned))
    return;
  //error("numericTypeCheck(): unexpected operand type for operator '%s', numeric type expected\n", GetTokenName(tok));
  errorOpType();
}

void compatCheck(int* ExprTypeSynPtr, int TheOtherExprTypeSynPtr, int ConstExpr[2], int lidx, int ridx)
{
  int exprTypeSynPtr = *ExprTypeSynPtr;
  int c = 0;
  int lptr, rptr, lnum, rnum;

  // convert functions to pointers to functions
  if (exprTypeSynPtr >= 0 && SyntaxStack[exprTypeSynPtr][0] == '(')
    *ExprTypeSynPtr = exprTypeSynPtr = -exprTypeSynPtr;
  if (TheOtherExprTypeSynPtr >= 0 && SyntaxStack[TheOtherExprTypeSynPtr][0] == '(')
    TheOtherExprTypeSynPtr = -TheOtherExprTypeSynPtr;

  lptr = exprTypeSynPtr < 0;
  rptr = TheOtherExprTypeSynPtr < 0;
  lnum = !lptr && (SyntaxStack[exprTypeSynPtr][0] == tokInt ||
                   SyntaxStack[exprTypeSynPtr][0] == tokUnsigned);
  rnum = !rptr && (SyntaxStack[TheOtherExprTypeSynPtr][0] == tokInt ||
                   SyntaxStack[TheOtherExprTypeSynPtr][0] == tokUnsigned);

  // both operands have arithmetic type
  // (arithmetic operands have been already promoted):
  if (lnum && rnum)
    return;

  // both operands have void type:
  if (!lptr && SyntaxStack[exprTypeSynPtr][0] == tokVoid &&
      !rptr && SyntaxStack[TheOtherExprTypeSynPtr][0] == tokVoid)
    return;

  // TBD??? check for exact 0?
  // one operand is a pointer and the other is NULL constant
  // ((void*)0 is also a valid null pointer constant),
  // the type of the expression is that of the pointer:
  if (lptr &&
      ((rnum && ConstExpr[1]) ||
       (rptr && SyntaxStack[-TheOtherExprTypeSynPtr][0] == tokVoid &&
        stack[ridx][0] == tokUnaryPlus && // "(type*)constant" appears as "constant +(unary)"
        (stack[ridx - 1][0] == tokNumInt || stack[ridx - 1][0] == tokNumUint))))
    return;
  if (rptr &&
      ((lnum && ConstExpr[0]) ||
       (lptr && SyntaxStack[-exprTypeSynPtr][0] == tokVoid &&
        stack[lidx][0] == tokUnaryPlus && // "(type*)constant" appears as "constant +(unary)"
        (stack[lidx - 1][0] == tokNumInt || stack[lidx - 1][0] == tokNumUint))))
  {
    *ExprTypeSynPtr = TheOtherExprTypeSynPtr;
    return;
  }

  // not expecting non-pointers beyond this point
  if (!(lptr && rptr))
    errorOpType();

  // one operand is a pointer and the other is a pointer to void
  // (except (void*)0, which is different from other pointers to void),
  // the type of the expression is pointer to void:
  if (SyntaxStack[-exprTypeSynPtr][0] == tokVoid)
    return;
  if (SyntaxStack[-TheOtherExprTypeSynPtr][0] == tokVoid)
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
    int tok = SyntaxStack[exprTypeSynPtr][0];
    if (tok != SyntaxStack[TheOtherExprTypeSynPtr][0])
      errorOpType();

    if (tok != tokIdent &&
        SyntaxStack[exprTypeSynPtr][1] != SyntaxStack[TheOtherExprTypeSynPtr][1])
      errorOpType();

    c += (tok == '(') - (tok == ')') + (tok == '[') - (tok == ']');

    switch (tok)
    {
    case tokVoid:
    case tokChar: case tokSChar: case tokUChar:
    case tokInt: case tokUnsigned:
      if (!c)
        return;
    }

    exprTypeSynPtr++;
    TheOtherExprTypeSynPtr++;
  }
}

void shiftCountCheck(int *psr, int idx, int ExprTypeSynPtr)
{
  int sr = *psr;
  // can't shift by a negative count and by a count exceeding
  // the number of bits in int
  if ((SyntaxStack[ExprTypeSynPtr][0] != tokUnsigned && sr < 0) ||
      (sr + 0u) >= CHAR_BIT * sizeof(int) ||
      (sr + 0u) >= 8u * SizeOfWord)
  {
    //error("exprval(): Invalid shift count\n");
    warning("Shift count out of range\n");
    // truncate the count, so the assembler doesn't get an invalid count
    sr &= SizeOfWord * 8 - 1;
    *psr = sr;
    stack[idx][1] = sr;
  }
}

int divCheckAndCalc(int tok, int* psl, int sr, int Unsigned, int ConstExpr[2])
{
  int div0 = 0;
  int sl = *psl;

  if (!ConstExpr[1])
    return !div0;

  if (Unsigned)
  {
    sl = uint2int(truncUint(sl));
    sr = uint2int(truncUint(sr));
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
        sl = uint2int((sl + 0u) / sr);
      else
        sl = uint2int((sl + 0u) % sr);
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

void promoteType(int* ExprTypeSynPtr, int* TheOtherExprTypeSynPtr)
{
  // chars must be promoted to ints in expressions as the very first thing
  if (*ExprTypeSynPtr >= 0 &&
      (SyntaxStack[*ExprTypeSynPtr][0] == tokChar ||
       SyntaxStack[*ExprTypeSynPtr][0] == tokSChar ||
       SyntaxStack[*ExprTypeSynPtr][0] == tokUChar))
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

  // Identifiers
  case tokIdent:
    {
      int synPtr = FindSymbol(IdentTable + s);
      int type;
      if (synPtr < 0)
      {
        if ((*idx + 2 >= sp) || stack[*idx + 2][0] != ')')
          error("Undeclared identifier '%s'\n", IdentTable + s);
        else
        {
          warning("Call to undeclared function '%s()'\n", IdentTable + s);
          // Implicitly declare "extern int ident();"
          GenExtern(IdentTable + s);
          PushSyntax2(tokIdent, s);
          PushSyntax('(');
          PushSyntax(')');
          PushSyntax(tokInt);
          synPtr = FindSymbol(IdentTable + s);
        }
      }

      // DONE: this declaration is actually a type cast
      if (!strncmp(IdentTable + SyntaxStack[synPtr][1], "(something", sizeof "(something)" - 1 - 1))
      {
        if (SyntaxStack[++synPtr][0] == tokLocalOfs) // TBD!!! is this really needed???
          synPtr++;

        s = exprval(idx, ExprTypeSynPtr, ConstExpr);

        // can't cast void to anything (except void)
        if (*ExprTypeSynPtr >= 0 && SyntaxStack[*ExprTypeSynPtr][0] == tokVoid &&
            SyntaxStack[synPtr][0] != tokVoid)
          errorOpType();

        // can't cast to a function or an array
        if (SyntaxStack[synPtr][0] == '(' || SyntaxStack[synPtr][0] == '[')
          errorOpType();

        // insertion of tokUChar, tokSChar and tokUnaryPlus
        // transforms lvalues into rvalues, just as casts should do
        switch (GetDeclSize(synPtr, 1))
        {
        case 1:
          // cast to unsigned char, resulting type is int
          stack[oldIdxRight + 1 - (oldSpRight - sp)][0] = tokUChar;
          *ExprTypeSynPtr = SymIntSynPtr;
          s &= 0xFFu;
          break;
        case -1:
          // cast to signed char, resulting type is int
          stack[oldIdxRight + 1 - (oldSpRight - sp)][0] = tokSChar;
          *ExprTypeSynPtr = SymIntSynPtr;
          if ((s &= 0xFFu) >= 0x80)
            s -= 0x100;
          break;
        default:
          // don't do anything, but indicate rvalue/cast
          stack[oldIdxRight + 1 - (oldSpRight - sp)][0] = tokUnaryPlus;
          *ExprTypeSynPtr = synPtr;
          break;
        }

        *ConstExpr &= SyntaxStack[*ExprTypeSynPtr][0] == tokInt || SyntaxStack[*ExprTypeSynPtr][0] == tokUnsigned;
        simplifyConstExpr(s, *ConstExpr, ExprTypeSynPtr, oldIdxRight + 1 - (oldSpRight - sp), *idx + 1);
        break;
      }

      type = SymType(synPtr);

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
        ins2(*idx + 2, tokUnaryStar, GetDeclSize(synPtr, 1));
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
      s = GetDeclSize(*ExprTypeSynPtr, 0);
    else
      s = SizeOfWord;
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
      //error("exprval(): lvalue expected after '&'\n");
      errorNotLvalue();

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
        //error("exprval(): cannot dereference a pointer to 'void'\n");
        errorUnexpectedVoid();
      // remove the dereference if that something is an array
      if (SyntaxStack[*ExprTypeSynPtr][0] == '[')
        del(oldIdxRight + 1 - (oldSpRight - sp), 1);
      // remove the dereference if that something is a function
      if (SyntaxStack[*ExprTypeSynPtr][0] == '(')
        del(oldIdxRight + 1 - (oldSpRight - sp), 1);
      // else add dereference size in bytes
      else
        stack[oldIdxRight + 1 - (oldSpRight - sp)][1] = GetDeclSize(*ExprTypeSynPtr, 1);
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
        incSize = GetDeclSize(-RightExprTypeSynPtr, 0);

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
        incSize = GetDeclSize(-*ExprTypeSynPtr, 0);
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
        incSize = GetDeclSize(-*ExprTypeSynPtr, 0);
        // TBD!!! "ptr1-ptr2": better pointer compatibility test needed
        if (incSize != GetDeclSize(-RightExprTypeSynPtr, 0))
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
        //error("exprval(): lvalue expected for '++' or '--'\n");
        errorNotLvalue();

      // "remove" the lvalue dereference as we don't need
      // to read the value and forget its location. We need to
      // keep the lvalue location.
      // Remember the operand size.
      opSize = stack[oldIdxRight - (oldSpRight - sp)][1];
      del(oldIdxRight - (oldSpRight - sp), 1);

      if (*ExprTypeSynPtr < 0)
        incSize = GetDeclSize(-*ExprTypeSynPtr, 0);

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
        //error("exprval(): lvalue expected before '='\n");
        errorNotLvalue();

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
        sl = uint2int((sl + 0u) * sr);
        break;

      case tokLShift:
      case tokRShift:
        if (constExpr[1])
        {
          if (SyntaxStack[RightExprTypeSynPtr][0] != tokUnsigned)
            sr = truncInt(sr);
          else
            sr = uint2int(truncUint(sr));
          shiftCountCheck(&sr, oldIdxRight - (oldSpRight - sp), RightExprTypeSynPtr);
        }
        if (*ConstExpr)
        {
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
        //error("exprval(): Invalid/unsupported combination of compared operands\n");
        errorOpType();

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
    s = exprval(idx, ExprTypeSynPtr, ConstExpr);
    s = truncInt(s) != 0;
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
        s = sl && sr;
      else
        s = sl || sr;

      *ExprTypeSynPtr = SymIntSynPtr;
      *ConstExpr = constExpr[0] && constExpr[1] && canSimplify;
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
      exprval(idx, ExprTypeSynPtr, ConstExpr);

      if (!GetFxnInfo(*ExprTypeSynPtr, &minParams, &maxParams, ExprTypeSynPtr))
        //error("exprval(): function or function pointer expected\n");
        errorOpType();

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
          //error("exprval(): function parameters cannot be of type 'void'\n");
          errorUnexpectedVoid();

        if (++c > maxParams)
          error("Too many function parameters\n");

        if (stack[*idx][0] == ',')
          --*idx;
      }
      --*idx;

      if (c < minParams)
        error("Too few function parameters\n");

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
      int sr = exprval(idx, &RightExprTypeSynPtr, &constExpr[1]);
      oldIdxLeft = *idx;
      oldSpLeft = sp;
      exprval(idx, ExprTypeSynPtr, &constExpr[0]);

      nonVoidTypeCheck(RightExprTypeSynPtr, tok);
      nonVoidTypeCheck(*ExprTypeSynPtr, tok);

      decayArray(&RightExprTypeSynPtr, 1);
      decayArray(ExprTypeSynPtr, 1);

      if (!(oldIdxLeft - (oldSpLeft - sp) >= 0 &&
            stack[oldIdxLeft - (oldSpLeft - sp)][0] == tokUnaryStar))
        //error("exprval(): lvalue expected before %s\n", GetTokenName(tok));
        errorNotLvalue();

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
          if (SyntaxStack[RightExprTypeSynPtr][0] != tokUnsigned)
            sr = truncInt(sr);
          else
            sr = uint2int(truncUint(sr));
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
        incSize = GetDeclSize(-*ExprTypeSynPtr, 0);
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

  case '?':
    {
      int oldIdxLeft, oldSpLeft;
      int sr, sl, smid;
      int condTypeSynPtr;
      int sc = (LabelCnt += 2) - 2;

      // "exprL ? exprMID : exprR" appears on the stack as
      // "exprL exprR exprMID ?"

      stack[*idx + 1][0] = tokLogAnd; // piggyback on && for CG (ugly, but simple)
      stack[*idx + 1][1] = sc + 1;
      smid = exprval(idx, ExprTypeSynPtr, &constExpr[1]);

      ins2(*idx + 1, tokLogAnd, sc); // piggyback on && for CG (ugly, but simple)

      ins2(*idx + 1, tokGoto, sc + 1); // jump to end of ?:
      oldIdxLeft = *idx;
      oldSpLeft = sp;
      sr = exprval(idx, &RightExprTypeSynPtr, &constExpr[2]);

      ins2(*idx + 1, tokShortCirc, -sc); // jump to mid if left is non-zero
      sl = exprval(idx, &condTypeSynPtr, &constExpr[0]);

      nonVoidTypeCheck(condTypeSynPtr, '?');

      decayArray(&RightExprTypeSynPtr, 0);
      decayArray(ExprTypeSynPtr, 0);
      promoteType(&RightExprTypeSynPtr, ExprTypeSynPtr);
      promoteType(ExprTypeSynPtr, &RightExprTypeSynPtr);

      compatCheck(ExprTypeSynPtr,
                  RightExprTypeSynPtr,
                  &constExpr[1],
                  oldIdxRight - (oldSpRight - sp),
                  oldIdxLeft - (oldSpLeft - sp));

      *ConstExpr = s = 0;

      if (constExpr[0])
      {
        if (truncUint(sl))
        {
          if (constExpr[1])
            *ConstExpr = 1, s = smid;
          // TBD??? else can drop LHS and RHS expressions
        }
        else
        {
          if (constExpr[2])
            *ConstExpr = 1, s = sr;
          // TBD??? else can drop LHS and MID expressions
        }
      }
      simplifyConstExpr(s, *ConstExpr, ExprTypeSynPtr, oldIdxRight + 1 - (oldSpRight - sp), *idx + 1);
    }
    break;

  default:
    //error("exprval(): Unexpected token %s\n", GetTokenName(tok));
    errorUnexpectedToken(tok);
  }

  return s;
}

int ParseExpr(int tok, int* GotUnary, int* ExprTypeSynPtr, int* ConstExpr, int* ConstVal, int commaSeparator, int label)
{
  *ConstVal = *ConstExpr = 0;
  *ExprTypeSynPtr = SymVoidSynPtr;

  if (!ExprLevel++)
  {
    opsp = sp = 0;
    PurgeStringTable();
  }

  tok = expr(tok, GotUnary, commaSeparator);

  if (tok == tokEof || strchr(",;:)]}", tok) == NULL)
    //error("ParseExpr(): Unexpected token %s\n", GetTokenName(tok));
    errorUnexpectedToken(tok);

  if (label && tok == ':' && *GotUnary && sp == 1 && stack[sp - 1][0] == tokIdent)
  {
    ExprLevel--;
    return tokGoto;
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
        for (idx = sp - 1; idx >= 0; idx--)
          if (stack[idx][0] == tokUnaryPlus)
            del(idx, 1);
        // if the expression has reduced to an integer, enforce it being a const expression
        // to aid variable initialization and code generation
        if (sp)
          *ConstExpr |= stack[sp - 1][0] == tokNumInt || stack[sp - 1][0] == tokNumUint;
      }
#ifndef NO_ANNOTATIONS
      else if (*ConstExpr)
      {
        GenStartCommentLine();

        switch (SyntaxStack[*ExprTypeSynPtr][0])
        {
        case tokInt:
          printf2("Expression value: %d\n", truncInt(*ConstVal));
          break;
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
    printf("Internal error: Indeterminate underlying type of va_list\n");
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
    // Turbo C++ 1.01's fputs() returns EOF if s is empty, which is wrong.
    // Hence the workaround.
    if (*s == '\0' || (res = fputs(s, OutFile)) >= 0)
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

  if (!(verbose && OutFile))
    return;

  printf("Warning in \"%s\" (%d:%d)\n", FileNames[fidx], LineNo, LinePos);

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
}

void errorFile(char* n)
{
  error("Unable to open, read, write or close file \"%s\"\n", n);
}

void errorFileName(void)
{
  error("Invalid or too long file name or path name\n");
}

void errorInternal(int n)
{
  error("%d (internal)\n", n);
}

void errorChrStr(void)
{
  error("Invalid or unsupported character constant or string literal\n");
}

void errorUnexpectedToken(int tok)
{
  error("Unexpected token %s\n", GetTokenName(tok));
}

void errorDirective(void)
{
  error("Invalid or unsupported preprocessor directive\n");
}

void errorCtrlOutOfScope(void)
{
  error("break, continue, case or default in wrong scope\n");
}

void errorDecl(void)
{
  error("Invalid or unsupported declaration\n");
}

void errorVarSize(void)
{
  error("Variable(s) take(s) too much space\n");
}

void errorInit(void)
{
  error("Invalid or unsupported initialization\n");
}

void errorUnexpectedVoid(void)
{
  error("Unexpected declaration or expression of type void\n");
}

void errorOpType(void)
{
  error("Unexpected operand type\n");
}

void errorNotLvalue(void)
{
  error("lvalue expected\n");
}

void errorNotConst(void)
{
  error("Non-constant expression\n");
}

void errorLongExpr(void)
{
  error("Too long expression\n");
}

int TokenStartsDeclaration(int t, int params)
{
  return t == tokVoid ||
         t == tokChar || t == tokSChar || t == tokUChar ||
         t == tokInt || t == tokSigned || t == tokUnsigned ||
         (!params && (t == tokExtern || t == tokStatic));
}

void PushSyntax2(int t, int v)
{
  if (SyntaxStackCnt >= SYNTAX_STACK_MAX)
    error("Symbol table exhausted\n");
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
    error("Symbol table exhausted\n");
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

  // TBD??? Also, I could first use FindIdent() and then just look for the
  // index into IdentTable[] instead of doing strcmp()

  for (i = SyntaxStackCnt - 1; i >= 0; i--)
  {
    if (SyntaxStack[i][0] == tokIdent &&
        !strcmp(IdentTable + SyntaxStack[i][1], s))
    {
      return i;
    }

    if (SyntaxStack[i][0] == ')')
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

int GetDeclSize(int SyntaxPtr, int SizeForDeref)
{
  int i;
  unsigned size = 1;
  int arr = 0;

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
    case tokSChar:
      if (!arr && ((tok == tokSChar) || CharIsSigned) && SizeForDeref)
        return -1; // 1 byte, needing sign extension when converted to int/unsigned int
    case tokUChar:
      return uint2int(size);
    case tokInt:
    case tokUnsigned:
    case '*':
    case '(': // size of fxn = size of ptr for now
      if (size * SizeOfWord / SizeOfWord != size)
        //error("Variable too big\n");
        errorVarSize();
      size *= SizeOfWord;
      if (size != truncUint(size))
        //error("Variable too big\n");
        errorVarSize();
      return uint2int(size);
    case '[':
      if (SyntaxStack[i + 1][0] != tokNumInt && SyntaxStack[i + 1][0] != tokNumUint)
        return 0;
      if (SyntaxStack[i + 1][1] &&
          size * SyntaxStack[i + 1][1] / SyntaxStack[i + 1][1] != size)
        //error("Variable too big\n");
        errorVarSize();
      size *= SyntaxStack[i + 1][1];
      if (size != truncUint(size))
        //error("Variable too big\n");
        errorVarSize();
      i += 2;
      arr = 1;
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
      case tokSChar:
      case tokUChar:
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
  (void)SyntaxPtr;
  (void)IsParam;
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

    if ((synPtr == SymIntSynPtr && exprVal < 1) || (synPtr == SymUintSynPtr && exprValU < 1))
      error("Array dimension less than 1\n");
  }

  PushSyntax2(tokNumUint, exprVal);
  return tok;
}

void ParseFxnParams(int tok);
int ParseBlock(int BrkCntSwchTarget[4], int switchBody);
void AddFxnParamSymbols(int SyntaxPtr);

int ParseBase(int tok, int* base)
{
  int valid = 1;
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
    {
      if (sign == tokUnsigned)
        *base = tokUChar;
      else
        *base = tokSChar;
      tok = GetToken();
    }
    else
    {
      if (sign == tokUnsigned)
        *base = tokUnsigned;
      else
        *base = tokInt;
      if (tok == tokInt)
        tok = GetToken();
    }
  }
  else
  {
    valid = 0;
  }

  // TBD!!! review/test this fxn
  if (!valid || !tok || !(strchr("*([,)", tok) || tok == tokIdent))
    //error("ParseBase(): Invalid or unsupported type\n");
    error("Invalid or unsupported type\n");

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
  int params = 0;

  while (tok == '*')
  {
    stars++;
    tok = GetToken();
  }

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
    PushSyntax2(tok, AddIdent(GetTokenIdentName()));
    tok = GetToken();
  }
  else
  {
    PushSyntax2(tokIdent, AddIdent("<something>"));
  }

  if (params || tok == '(')
  {
    if (!params)
      tok = GetToken();
    else
      PushSyntax2(tokIdent, AddIdent("<something>"));
    PushSyntax('(');
    ParseLevel++;
    ParseFxnParams(tok);
    ParseLevel--;
    PushSyntax(')');
    tok = GetToken();
  }
  else if (tok == '[')
  {
    // DONE!!! allow the first [] without the dimension in function parameters
    int allowEmptyDimension = 1;
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

// DONE: support extern
// DONE: support static
// DONE: support basic initialization
// DONE: support simple non-array initializations with string literals
// DONE: support basic 1-d array initialization
// DONE: global/static data allocations
int ParseDecl(int tok, int cast)
{
  int base;
  int lastSyntaxPtr;
  int external = tok == tokExtern;
  int Static = tok == tokStatic;

  if (external || Static)
  {
    tok = GetToken();
    if (!TokenStartsDeclaration(tok, 1))
      //error("ParseDecl(): unexpected token %s\n", GetTokenName(tok));
      errorUnexpectedToken(tok);
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
      int isFxn, isArray, isMultiDimArray, isIncompleteArr;
      unsigned elementSz = 0;

      // Disallow void variables and arrays of void
      if (base == tokVoid && !cast)
      {
        int t = SyntaxStack[SyntaxStackCnt - 2][0];
        if (t != '*' && t != ')')
          //error("ParseDecl(): Cannot declare a variable ('%s') of type 'void'\n", IdentTable + SyntaxStack[lastSyntaxPtr][1]);
          errorUnexpectedVoid();
      }

      isFxn = SyntaxStack[lastSyntaxPtr + 1][0] == '(';
      isArray = SyntaxStack[lastSyntaxPtr + 1][0] == '[';
      isMultiDimArray = isArray && SyntaxStack[lastSyntaxPtr + 4][0] == '[';
      isIncompleteArr = isArray && SyntaxStack[lastSyntaxPtr + 2][1] == 0;

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

      if (isFxn && tok == '=')
        //error("ParseDecl(): cannot initialize a function\n");
        errorInit();

      if (isFxn && tok == '{' && ParseLevel)
        //error("ParseDecl(): cannot define a nested function\n");
        errorDecl();

      if (isFxn && Static && ParseLevel)
        //error("ParseDecl(): cannot declare a static function in this scope\n");
        errorDecl();

      if (external && tok == '=')
        //error("ParseDecl(): cannot initialize an external variable\n");
        errorInit();

      if (isIncompleteArr && !(external || tok == '='))
        //error("ParseDecl(): cannot define an array of incomplete type\n");
        errorDecl();

      if (Static && ParseLevel)
        //error("ParseDecl(): static not supported in this scope\n");
        errorDecl();

      if (isMultiDimArray && tok == '=')
        //error("ParseDecl(): multidimensional array initialization not supported\n");
        errorInit();

      if (isArray && tok == '=' && ParseLevel)
        //error("ParseDecl(): array initialization not supported in this scope\n");
        errorInit();

      // TBD!!! de-uglify
      if (!strcmp(IdentTable + SyntaxStack[lastSyntaxPtr][1], "<something>"))
      {
        // Disallow nameless variables and prototypes.
        if (!ExprLevel)
          error("Identifier expected in declaration\n");
      }
      else
      {
        // Disallow named variables and prototypes.
        if (ExprLevel)
          error("Identifier unexpected in declaration\n");
      }

      if (!isFxn)
      {
        int sz = GetDeclSize(lastSyntaxPtr, 0);

        if (isArray)
          elementSz = GetDeclSize(lastSyntaxPtr + 4, 0);
        else
          elementSz = sz;

        if (ParseLevel && !external && !Static && !ExprLevel)
        {
          int oldOfs;
          // It's a local variable, let's calculate its relative on-stack location
          oldOfs = CurFxnLocalOfs;

          CurFxnLocalOfs = uint2int((CurFxnLocalOfs + 0u - sz) & ~(SizeOfWord - 1u));
          if (CurFxnLocalOfs >= oldOfs || CurFxnLocalOfs != truncInt(CurFxnLocalOfs))
            //error("ParseDecl(): Local variables take too much space\n");
            errorVarSize();

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

      DumpDecl(lastSyntaxPtr, 0);

      if (ExprLevel)
        return tok;

      if ((globalAllocSize || isIncompleteArr) && !external)
      {
        if (OutputFormat != FormatFlat)
          puts2(DataHeader);
        // TBD??? imperfect condition for alignment
        if (elementSz % SizeOfWord == 0)
          GenWordAlignment();
        GenLabel(IdentTable + SyntaxStack[lastSyntaxPtr][1], Static);
      }

      if (external && !(isFxn && tok == '{'))
      {
        GenExtern(IdentTable + SyntaxStack[lastSyntaxPtr][1]);
      }
      // Handle initialization
      else if (tok == '=')
      {
        int gotUnary, synPtr, constExpr, exprVal;
        int p;
        int oldssp, undoIdents;
        int braces = 0;
        unsigned elementCnt = 0;
        unsigned elementsRequired = 0;
        int strLitAllowed = 1;
        int nonStrLitAllowed = 1;
        int arrOfChar = isArray && elementSz == 1;
#ifndef NO_ANNOTATIONS
        GenStartCommentLine(); printf2("=\n");
#endif

        p = lastSyntaxPtr;
        while (SyntaxStack[p][0] == tokIdent || SyntaxStack[p][0] == tokLocalOfs)
          p++;

        oldssp = SyntaxStackCnt;
        undoIdents = IdentTableLen;

        if (isArray)
          elementsRequired = SyntaxStack[p + 1][1];

        tok = GetToken();
        // Interestingly, scalars can be legally initialized with braced
        // initializers just like arrays, e.g. "int a = { 1 };".
        // Also, "int i[];" must have 1 element.
        // Let's not support that!
        if (isArray && tok == '{')
        {
          braces = 1;
          tok = GetToken();
        }

        PurgeStringTable();
        KeepStringTable = 1;

        for (;;)
        {
          int strLitInitializer;

          if (braces && tok == '}')
          {
            tok = GetToken();
            if (!tok || !strchr(",;", tok))
              //error("ParseDecl(): unexpected token %s\n", GetTokenName(tok));
              errorUnexpectedToken(tok);
            break;
          }

          tok = ParseExpr(tok, &gotUnary, &synPtr, &constExpr, &exprVal, 1, 0);
          if (!gotUnary)
            //error("ParseDecl(): missing initialization expression\n");
            errorUnexpectedToken(tok);

          nonVoidTypeCheck(synPtr, '=');

          if (!tok ||
              (braces && !strchr(",}", tok)) ||
              (!braces && !strchr(",;", tok)))
            //error("ParseDecl(): unexpected token %s\n", GetTokenName(tok));
            errorUnexpectedToken(tok);

          strLitInitializer = stack[sp - 1][0] == tokIdent &&
                              isdigit(IdentTable[stack[sp - 1][1]]);

          // Prohibit initializers like in "int a[1] = 1;" and "char* a[1] = "abc";"
          if (isArray && !braces && (!strLitInitializer || !arrOfChar))
            //error("ParseDecl(): array initializers must be in braces\n");
            errorInit();

          // Prohibit the following character array initializations:
          // char a[] = { 'a', "b" };
          // char a[] = { "a", 'b' };
          // char a[] = { "a", "b" };
          if (arrOfChar)
          {
            if (!strLitInitializer)
              strLitAllowed = 0;
            else
              nonStrLitAllowed = 0;
            if ((strLitInitializer && !strLitAllowed) ||
                (!strLitInitializer && !nonStrLitAllowed))
              //error("ParseDecl(): invalid initialization\n");
              errorInit();
            if (strLitInitializer)
              strLitAllowed = 0;
          }

          elementCnt++;

          if (braces && elementsRequired && elementCnt > elementsRequired)
            error("Too many array initializers\n");

          if (!ParseLevel)
          {
            if (constExpr)
            {
              GenIntData(elementSz, exprVal);
            }
            else if (elementSz == SizeOfWord + 0u && stack[sp - 1][0] == tokIdent)
            {
              GenAddrData(elementSz, IdentTable + stack[sp - 1][1]);
              // Defer storage of string literal data (if any) until the end.
              // This will let us generate the contiguous array of pointers to
              // string literals unperturbed by the string literal data
              // (e.g. "char* colors[] = { "red", "green", "blue" };").
            }
            else if (arrOfChar && strLitInitializer)
            {
                // Defer storage of string literal data until the end.
                // Now simply remember that the character array has buffered string data.
                arrOfChar++;
            }
            else
              //error("ParseDecl(): cannot initialize a global variable with a non-constant expression\n");
              errorNotConst();
          }
          else
          {
            if (synPtr >= 0 && SyntaxStack[synPtr][0] == tokVoid)
              //error("ParseDecl(): cannot initialize a variable with a 'void' expression\n");
              errorUnexpectedVoid();
            // transform the current expression stack into:
            //   tokLocalOfs(...), original expression stack, =(localAllocSize)
            // this will simulate assignment
            ins2(0, tokLocalOfs, SyntaxStack[lastSyntaxPtr + 1][1]);
            push2('=', localAllocSize); // TBD??? should use elementSz instead?
            // Storage of string literal data from the initializing expression
            // occurs here.
            GenExpr();
          }

          if (braces)
          {
            if (tok == ',')
              tok = GetToken();
          }
          else
            break;
        } // for (;;)

        if (!ParseLevel)
        {
          if (arrOfChar == 2)
            elementCnt = GenStrData(0, elementsRequired);

          if (isArray)
          {
            // Implicit initialization with 0 of what's not initialized explicitly
            if (elementCnt < elementsRequired)
              GenZeroData((elementsRequired - elementCnt) * elementSz);

            // The number of elements is now known
            if (isIncompleteArr)
              SyntaxStack[p + 1][1] = elementCnt;
          }

          if (!arrOfChar)
          {
            int lab;
            char s[1 + (2 + CHAR_BIT * sizeof lab) / 3];
            int i = 0;

            // Construct an expression for each buffered string for GenStrData()
            sp = 1;
            stack[0][0] = tokIdent;

            // Dump all buffered strings, one by one, the ugly way
            while (i < StringTableLen)
            {
              char *p = s + sizeof s;

              lab = StringTable[i] & 0xFF;
              lab += (StringTable[i + 1] & 0xFFu) << 8;

              // Reconstruct the identifier for the definition: char #[len] = "...";
              *--p = '\0';
              p = lab2str(p, lab);
              stack[0][1] = AddIdent(p);

              GenStrData(0, 0);

              // Drop the identifier from the identifier table so as not to
              // potentially overflow it when there are many initializing
              // string literals and the table is nearly full.
              IdentTableLen = undoIdents; // remove all temporary identifier names from e.g. "sizeof" or "str"

              i += 2;
              i += 1 + StringTable[i];
            }
          }
        }

        PurgeStringTable();
        KeepStringTable = 0;

        if (!ParseLevel && OutputFormat != FormatFlat)
          puts2(DataFooter);

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
        int i;

        gotoLabCnt = 0;

        if (verbose && OutFile)
          printf("%s()\n", IdentTable + SyntaxStack[lastSyntaxPtr][1]);

        ParseLevel++;
        GetFxnInfo(lastSyntaxPtr, &CurFxnParamCntMin, &CurFxnParamCntMax, &CurFxnReturnExprTypeSynPtr); // get return type

        if (OutputFormat != FormatFlat)
          puts2(CodeHeader);
        GenLabel(IdentTable + SyntaxStack[lastSyntaxPtr][1], Static);
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
          //error("ParseDecl(): '}' expected\n");
          errorUnexpectedToken(tok);
        IdentTableLen = undoIdents; // remove all identifier names
        SyntaxStackCnt = undoSymbolsPtr; // remove all params and locals

        for (i = 0; i < gotoLabCnt; i++)
          if (gotoLabStat[i] == 2)
            error("Undeclared label '%s'\n", IdentTable + gotoLabels[i][0]);

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

    //error("ParseDecl(): unexpected token %s\n", GetTokenName(tok));
    errorUnexpectedToken(tok);
  }

  tok = GetToken();
  return tok;
}

void ParseFxnParams(int tok)
{
  int base;
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
      base = tok; // "..."
      PushSyntax2(tokIdent, AddIdent("<something>"));
      tok = GetToken();
    }
    else
    {
      if (ellCnt)
        //error("ParseFxnParams(): '...' must be the last in the parameter list\n");
        errorUnexpectedToken(tok);

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
          //error("ParseFxnParams(): Cannot declare a variable ('%s') of type 'void'\n", IdentTable + SyntaxStack[lastSyntaxPtr][1]);
          errorUnexpectedVoid();
      }

      if (tok == ')')
        break;

      tok = GetToken();
      continue;
    }

    //error("ParseFxnParams(): Unexpected token %s\n", GetTokenName(tok));
    errorUnexpectedToken(tok);
  }
}

void AddFxnParamSymbols(int SyntaxPtr)
{
  int i;

  if (SyntaxPtr < 0 ||
      SyntaxPtr > SyntaxStackCnt - 3 ||
      SyntaxStack[SyntaxPtr][0] != tokIdent ||
      SyntaxStack[SyntaxPtr + 1][0] != '(')
    //error("Internal error: AddFxnParamSymbols(): Invalid input\n");
    errorInternal(6);

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
        //error("Internal error: AddFxnParamSymbols(): Invalid input\n");
        errorInternal(7);

      if (SyntaxStack[i + 1][0] == tokVoid) // "ident(void)" = no params
        break;
      if (SyntaxStack[i + 1][0] == tokEllipsis) // "ident(something,...)" = no more params
        break;

      sz = GetDeclSize(i, 0);
      if (sz == 0)
        //error("Internal error: AddFxnParamSymbols(): GetDeclSize() = 0\n");
        errorInternal(8);

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
      //error("Internal error: AddFxnParamSymbols(): Unexpected token %s\n", GetTokenName(tok));
      errorInternal(9);
  }
}

int ParseStatement(int tok, int BrkCntSwchTarget[4], int switchBody)
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
  int brkCntSwchTarget[4];
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
      tok = ParseBlock(BrkCntSwchTarget, switchBody / 2);
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
      // TBD??? functions returning void should be able to return void
      //        return values from other functions returning void
      int retVoid = CurFxnReturnExprTypeSynPtr >= 0 &&
                    SyntaxStack[CurFxnReturnExprTypeSynPtr][0] == tokVoid;
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
        if (gotUnary &&
            synPtr >= 0 && SyntaxStack[synPtr][0] == tokVoid)
            //error("ParseStatement(): cannot return a value of type 'void'\n");
            errorUnexpectedVoid();
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
      if (synPtr >= 0 && SyntaxStack[synPtr][0] == tokVoid)
        //error("ParseStatement(): unexpected 'void' expression in 'while ( expression )'\n");
        errorUnexpectedVoid();

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
      if (synPtr >= 0 && SyntaxStack[synPtr][0] == tokVoid)
        //error("ParseStatement(): unexpected 'void' expression in 'while ( expression )'\n");
        errorUnexpectedVoid();

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
      if (synPtr >= 0 && SyntaxStack[synPtr][0] == tokVoid)
        //error("ParseStatement(): unexpected 'void' expression in 'if ( expression )'\n");
        errorUnexpectedVoid();

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
        //error("ParseStatement(): '(' expected after 'for'\n");
        errorUnexpectedToken(tok);

      tok = GetToken();
      if ((tok = ParseExpr(tok, &gotUnary, &synPtr, &constExpr, &exprVal, 0, 0)) != ';')
        //error("ParseStatement(): ';' expected after 'for ( expression'\n");
        errorUnexpectedToken(tok);
      if (gotUnary)
      {
        GenExpr();
      }

      GenNumLabel(labelBefore);
      tok = GetToken();
      if ((tok = ParseExpr(tok, &gotUnary, &synPtr, &constExpr, &exprVal, 0, 0)) != ';')
        //error("ParseStatement(): ';' expected after 'for ( expression ; expression'\n");
        errorUnexpectedToken(tok);
      if (gotUnary)
      {
        // DONE: void control expressions
        if (synPtr >= 0 && SyntaxStack[synPtr][0] == tokVoid)
          //error("ParseStatement(): unexpected 'void' expression in 'for ( ; expression ; )'\n");
          errorUnexpectedVoid();

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
      if ((tok = ParseExpr(tok, &gotUnary, &synPtr, &constExpr, &exprVal, 0, 0)) != ')')
        //error("ParseStatement(): ')' expected after 'for ( expression ; expression ; expression'\n");
        errorUnexpectedToken(tok);
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
      if ((tok = GetToken()) != ';')
        //error("ParseStatement(): ';' expected\n");
        errorUnexpectedToken(tok);
      tok = GetToken();
      if (BrkCntSwchTarget == NULL)
        //error("ParseStatement(): 'break' must be within 'while', 'for' or 'switch' statement\n");
        errorCtrlOutOfScope();
      GenJumpUncond(BrkCntSwchTarget[0]);
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
      if (BrkCntSwchTarget == NULL || BrkCntSwchTarget[1] == 0)
        //error("ParseStatement(): 'continue' must be within 'while' or 'for' statement\n");
        errorCtrlOutOfScope();
      GenJumpUncond(BrkCntSwchTarget[1]);
    }
    else if (tok == tokSwitch)
    {
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
      if (synPtr >= 0 && SyntaxStack[synPtr][0] == tokVoid)
        //error("ParseStatement(): unexpected 'void' expression in 'switch ( expression )'\n");
        errorUnexpectedVoid();

      GenExpr();

      tok = GetToken();
      if (tok != '{')
        //error("ParseStatement(): '{' expected after 'switch ( expression )'\n");
        errorUnexpectedToken(tok);

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
        //error("ParseStatement(): 'case' must be within 'switch' statement\n");
        errorCtrlOutOfScope();

      tok = GetToken();
      if ((tok = ParseExpr(tok, &gotUnary, &synPtr, &constExpr, &exprVal, 0, 0)) != ':')
        //error("ParseStatement(): ':' expected after 'case expression'\n");
        errorUnexpectedToken(tok);

      if (!gotUnary || !constExpr || (synPtr >= 0 && SyntaxStack[synPtr][0] == tokVoid))
        //error("ParseStatement(): constant integer expression expected in 'case expression :'\n");
        errorNotConst();

      tok = GetToken();

      lnext = (LabelCnt += 2) - 2;

      GenJumpUncond(BrkCntSwchTarget[3] + 1); // fallthrough
      GenNumLabel(BrkCntSwchTarget[3]);
      GenJumpIfNotEqual(exprVal, lnext);
      GenNumLabel(BrkCntSwchTarget[3] + 1);

      BrkCntSwchTarget[3] = lnext;

      // a statement is needed after "case:"
      statementNeeded = 1;
    }
    else if (tok == tokDefault)
    {
#ifndef NO_ANNOTATIONS
      GenStartCommentLine(); printf2("default\n");
#endif

      if (!switchBody)
        //error("ParseStatement(): 'default' must be within 'switch' statement\n");
        errorCtrlOutOfScope();

      tok = GetToken();
      if (tok != ':')
        //error("ParseStatement(): ':' expected after 'default'\n");
        errorUnexpectedToken(tok);

      if (BrkCntSwchTarget[2] < 0)
        //error("ParseStatement(): only one 'default' allowed in 'switch'\n");
        errorUnexpectedToken(tokDefault);

      tok = GetToken();

      GenNumLabel(BrkCntSwchTarget[2]); // default:

      BrkCntSwchTarget[2] *= -1; // remember presence of default:

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

      puts2(GetTokenValueString());

      tok = GetToken();
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
      GenStartCommentLine(); printf2("goto %s\n", GetTokenIdentName());
#endif
      GenJumpUncond(AddGotoLabel(GetTokenIdentName(), 0));
      if ((tok = GetToken()) != ';')
        errorUnexpectedToken(tok);
      tok = GetToken();
    }
    else
    {
      tok = ParseExpr(tok, &gotUnary, &synPtr, &constExpr, &exprVal, 0, 1);
      if (tok == tokGoto)
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
      tok = ParseDecl(tok, 0);
    }
    else if (ParseLevel > 0 || tok == tok_Asm)
    {
      tok = ParseStatement(tok, BrkCntSwchTarget, switchBody);
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
      verbose = 1;
      continue;
    }
#ifndef NO_PREPROCESSOR
    else if (!strcmp(argv[i], "-I"))
    {
      if (i + 1 < argc)
      {
        int len = strlen(argv[++i]);
        if (MAX_SEARCH_PATH - SearchPathsLen < len + 1)
          //error("Path name too long\n");
          errorFileName();
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

  GenInitFinalize();

  // some manual initialization because there's no 2d array initialization yet
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

  GenStartCommentLine(); printf2("Next label: "); GenNumLabel(LabelCnt);

  if (verbose && warnCnt && OutFile)
    printf("%d warnings\n", warnCnt);
  GenStartCommentLine(); printf2("Compilation succeeded.\n");

  if (OutFile != NULL)
    fclose(OutFile);

  return 0;
}
