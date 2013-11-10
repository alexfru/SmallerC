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
/*                           x86 code generator                              */
/*                                                                           */
/*****************************************************************************/

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
  printf2("; ");
}

void GenWordAlignment(void)
{
  printf2("\talign %d\n", SizeOfWord);
}

void GenLabel(char* Label, int Static)
{
  if (UseLeadingUnderscores)
  {
    if (OutputFormat != FormatFlat && !Static)
      printf2("\tglobal\t_%s\n", Label);
    printf2("_%s:\n", Label);
  }
  else
  {
    if (OutputFormat != FormatFlat && !Static)
      printf2("\tglobal\t$%s\n", Label);
    printf2("$%s:\n", Label);
  }
}

void GenExtern(char* Label)
{
  if (OutputFormat != FormatFlat)
  {
    if (UseLeadingUnderscores)
      printf2("\textern\t_%s\n", Label);
    else
      printf2("\textern\t$%s\n", Label);
  }
}

void GenPrintLabel(char* Label)
{
  if (UseLeadingUnderscores)
  {
    if (isdigit(*Label))
      printf2("L%s", Label);
    else
      printf2("_%s", Label);
  }
  else
  {
    if (isdigit(*Label))
      printf2("..@L%s", Label);
    else
      printf2("$%s", Label);
  }
}

void GenNumLabel(int Label)
{
  if (UseLeadingUnderscores)
    printf2("L%d:\n", Label);
  else
    printf2("..@L%d:\n", Label);
}

void GenPrintNumLabel(int label)
{
  if (UseLeadingUnderscores)
    printf2("L%d", label);
  else
    printf2("..@L%d", label);
}

void GenZeroData(unsigned Size)
{
  printf2("\ttimes\t%u db 0\n", truncUint(Size));
}

void GenIntData(int Size, int Val)
{
  Val = truncInt(Val);
  if (Size == 1)
    printf2("\tdb\t%d\n", Val);
  else if (Size == 2)
    printf2("\tdw\t%d\n", Val);
  else if (Size == 4)
    printf2("\tdd\t%d\n", Val);
}

void GenStartAsciiString(void)
{
  printf2("\tdb\t");
}

void GenAddrData(int Size, char* Label)
{
  if (Size == 1)
    printf2("\tdb\t");
  else if (Size == 2)
    printf2("\tdw\t");
  else if (Size == 4)
    printf2("\tdd\t");
  GenPrintLabel(Label); puts2("");
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
    printf2("\t%s", p);
    break;
  default:
    printf2("\t%s\t", p);
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
    case X86OpRegAByte: printf2("al"); break;
    case X86OpRegAByteHigh: printf2("ah"); break;
    case X86OpRegCByte: printf2("cl"); break;
    case X86OpRegAWord: printf2("ax"); break;
    case X86OpRegBWord: printf2("bx"); break;
    case X86OpRegCWord: printf2("cx"); break;
    case X86OpRegDWord: printf2("dx"); break;
    case X86OpRegBpWord: printf2("bp"); break;
    case X86OpRegSpWord: printf2("sp"); break;
    case X86OpConst: printf2("%d", truncInt(val)); break;
    case X86OpLabel: GenPrintLabel(IdentTable + val); break;
    case X86OpNumLabel: GenPrintNumLabel(val); break;
    case X86OpIndLabel: printf2("["); GenPrintLabel(IdentTable + val); printf2("]"); break;
    case X86OpIndLabelExplicitByte: printf2("byte ["); GenPrintLabel(IdentTable + val); printf2("]"); break;
    case X86OpIndLabelExplicitWord: printf2("word ["); GenPrintLabel(IdentTable + val); printf2("]"); break;
    case X86OpIndLocal: printf2("[bp%+d]", val); break;
    case X86OpIndLocalExplicitByte: printf2("byte [bp%+d]", val); break;
    case X86OpIndLocalExplicitWord: printf2("word [bp%+d]", val); break;
    case X86OpIndRegB: printf2("[bx]"); break;
    case X86OpIndRegBExplicitByte: printf2("byte [bx]"); break;
    case X86OpIndRegBExplicitWord: printf2("word [bx]"); break;
    }
  }
  else
  {
    switch (op)
    {
    case X86OpRegAByte: printf2("al"); break;
    case X86OpRegAByteHigh: printf2("ah"); break;
    case X86OpRegCByte: printf2("cl"); break;
    case X86OpRegAWord: printf2("eax"); break;
    case X86OpRegBWord: printf2("ebx"); break;
    case X86OpRegCWord: printf2("ecx"); break;
    case X86OpRegDWord: printf2("edx"); break;
    case X86OpRegBpWord: printf2("ebp"); break;
    case X86OpRegSpWord: printf2("esp"); break;
    case X86OpConst: printf2("%d", truncInt(val)); break;
    case X86OpLabel: GenPrintLabel(IdentTable + val); break;
    case X86OpNumLabel: GenPrintNumLabel(val); break;
    case X86OpIndLabel: printf2("["); GenPrintLabel(IdentTable + val); printf2("]"); break;
    case X86OpIndLabelExplicitByte: printf2("byte ["); GenPrintLabel(IdentTable + val); printf2("]"); break;
    case X86OpIndLabelExplicitWord: printf2("dword ["); GenPrintLabel(IdentTable + val); printf2("]"); break;
    case X86OpIndLocal: printf2("[ebp%+d]", val); break;
    case X86OpIndLocalExplicitByte: printf2("byte [ebp%+d]", val); break;
    case X86OpIndLocalExplicitWord: printf2("dword [ebp%+d]", val); break;
    case X86OpIndRegB: printf2("[ebx]"); break;
    case X86OpIndRegBExplicitByte: printf2("byte [ebx]"); break;
    case X86OpIndRegBExplicitWord: printf2("dword [ebx]"); break;
    }
  }
}

void GenPrintOperandSeparator(void)
{
  printf2(", ");
}

void GenPrintNewLine(void)
{
  puts2("");
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
  GenStartCommentLine(); printf2("JumpIfZero\n");
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
  GenStartCommentLine(); printf2("JumpIfNotZero\n");
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
  printf2("; Fused expression:    \"");
  for (i = 0; i < sp; i++)
  {
    int tok = stack[i][0];
    switch (tok)
    {
    case tokNumInt:
    case tokOpNumInt:
      printf2("%d", truncInt(stack[i][1]));
      break;
    case tokNumUint:
    case tokOpNumUint:
      printf2("%uu", truncUint(stack[i][1]));
      break;
    case tokIdent:
    case tokOpIdent:
      {
        char* p = IdentTable + stack[i][1];
        if (isdigit(*p))
          printf2("L");
        printf2("%s", p);
      }
      break;
    case tokOpIndIdent:
      printf2("*%s", IdentTable + stack[i][1]);
      break;
    case tokShortCirc:
      if (stack[i][1] >= 0)
        printf2("[sh&&->%d]", stack[i][1]);
      else
        printf2("[sh||->%d]", -stack[i][1]);
      break;
    case tokLocalOfs:
    case tokOpLocalOfs:
      printf2("(@%d)", stack[i][1]);
      break;
    case tokOpIndLocalOfs:
      printf2("*(@%d)", stack[i][1]);
      break;
    case tokUnaryStar:
      printf2("*(%d)", stack[i][1]);
      break;
    case '(': case ',':
      printf2("%c", tok);
      break;
    case ')':
      printf2(")%d", stack[i][1]);
      break;
    case tokOpAcc:
      printf2("ax");
      break;
    case tokOpIndAcc:
      printf2("*ax");
      break;
    case tokOpStack:
      printf2("*sp");
      break;
    case tokOpIndStack:
      printf2("**sp");
      break;
    case tokPushAcc:
      printf2("push-ax");
      break;
    case tokIf:
      printf2("IF");
      break;
    case tokIfNot:
      printf2("IF!");
      break;
    default:
      printf2("%s", GetTokenName(tok));
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
      case tokAssignUDiv: case tokAssignUMod:
      case tokAssignLSh: case tokAssignRSh: case tokAssignURSh:
      case tokAssignAnd: case tokAssignXor: case tokAssignOr:
        printf2("(%d)", stack[i][1]);
        break;
      }
      break;
    }
    printf2(" ");
  }
  printf2("\"\n");
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
    case tokNumInt: printf2("; %d\n", truncInt(v)); break;
    case tokNumUint: printf2("; %uu\n", truncUint(v)); break;
    case tokIdent: printf2("; %s\n", IdentTable + v); break;
    case tokLocalOfs: printf2("; local ofs\n"); break;
    case ')': printf2("; ) fxn call\n"); break;
    case tokUnaryStar: printf2("; * (read dereference)\n"); break;
    case '=': printf2("; = (write dereference)\n"); break;
    case tokShortCirc: printf2("; short-circuit "); break;
    case tokLogAnd: printf2("; short-circuit && target\n"); break;
    case tokLogOr: printf2("; short-circuit || target\n"); break;
    case tokIf: case tokIfNot: break;
    default: printf2("; %s\n", GetTokenName(tok)); break;
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
        printf2("&&\n");
      else
        printf2("||\n");
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

unsigned GenStrData(int generatingCode, unsigned requiredLen)
{
  int i;
  unsigned total = 0;

  // insert string literals into the code
  for (i = 0; i < sp; i++)
  {
    int tok = stack[i][0];
    char* p = IdentTable + stack[i][1];
    if (tok == tokIdent && isdigit(*p))
    {
      int label = atoi(p);
      int quot = 0;
      unsigned len;

      p = FindString(label);
      len = *p++;

      // If this is a string literal initializing an array of char,
      // truncate or pad it as necessary.
      if (requiredLen)
      {
        if (len >= requiredLen)
        {
          len = requiredLen; // copy count
          requiredLen = 0; // count to be zeroed out
        }
        else
        {
          requiredLen -= len; // count to be zeroed out
        }
      }
      // Also, calculate its real size for incompletely typed arrays.
      total = len + requiredLen;

      if (generatingCode)
      {
        if (OutputFormat == FormatFlat)
        {
          GenJumpUncond(label + 1);
        }
        else
        {
          puts2(CodeFooter);
          puts2(DataHeader);
        }
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
            printf2("\"");
          }
          printf2("%c", *p);
        }
        else
        {
          if (quot)
          {
            quot = 0;
            printf2("\",");
          }
          printf2("%u", *p & 0xFFu);
          if (len || requiredLen)
            printf2(",");
        }
        p++;
      }
      if (quot)
      {
        printf2("\"");
        if (requiredLen)
          printf2(",");
      }
      while (requiredLen)
      {
        printf2("0");
        if (--requiredLen)
          printf2(",");
      }
      puts2("");

      if (generatingCode)
      {
        if (OutputFormat == FormatFlat)
        {
          GenNumLabel(label + 1);
        }
        else
        {
          puts2(DataFooter);
          puts2(CodeHeader);
        }
      }
    }
  }

  return total;
}

void GenExpr(void)
{
  GenStrData(1, 0);
#ifndef CG_STACK_BASED
  GenExpr1();
#else
  GenExpr0();
#endif
}
