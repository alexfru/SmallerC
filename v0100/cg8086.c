/*
Copyright (c) 2012-2018, Alexey Frunze
Copyright (c) 2023-2024, Humberto Costa dos Santos Junior
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
/*                                Smaller C                                  */
/*                                                                           */
/*                 A simple and small single-pass C compiler                 */
/*                                                                           */
/*                         Generic code generator                            */
/*                                                                           */
/*****************************************************************************/

#define MAX_GLOBALS_TABLE_LEN MAX_IDENT_TABLE_LEN

/*
  Globals table entry format:
    use char:       use: bit 0 = defined, bit 1 = used
    idlen char:     string length (<= 127)
    id char[idlen]: string (ASCIIZ)
*/
char GlobalsTable[MAX_GLOBALS_TABLE_LEN];
int GlobalsTableLen = 0;

STATIC
void GenAddGlobal(char* s, int use)
{
  int i = 0;
  int l;
  if (GenExterns)
  {
    while (i < GlobalsTableLen)
    {
      if (!strcmp(GlobalsTable + i + 2, s))
      {
        if (GlobalsTable[i] & use & 1)
          errorRedecl(s); // the assembler would error-out in this case as well
        GlobalsTable[i] |= use;
        return;
      }
      i += GlobalsTable[i + 1] + 2;
    }
    l = strlen(s) + 1;
    if (GlobalsTableLen + l + 2 > MAX_GLOBALS_TABLE_LEN)
      error("Globals tbl exhausted\n");
    GlobalsTable[GlobalsTableLen++] = use;
    GlobalsTable[GlobalsTableLen++] = l;
    memcpy(GlobalsTable + GlobalsTableLen, s, l);
    GlobalsTableLen += l;
  }
}

STATIC
void GenInit(void)
{
  // initialization of target-specific code generator
  SizeOfWord = 2;
  OutputFormat = FormatSegmented;
  UseLeadingUnderscores = 1;
}

STATIC
int GenInitParams(int argc, char** argv, int* idx)
{
  (void)argc;
  // initialization of target-specific code generator with parameters

  if (!strcmp(argv[*idx], "-nobss"))
  {
    UseBss = 0;
    return 1;
  }
  else if (!strcmp(argv[*idx], "-seg16"))
  {
    // this is the default option for x86
    OutputFormat = FormatSegmented; SizeOfWord = 2;
    return 1;
  }

  return 0;
}

STATIC
void GenInitFinalize(void)
{
  // finalization of initialization of target-specific code generator

  // Change the output assembly format/content according to the options
  CodeHeaderFooter[0] = "section .text";
  DataHeaderFooter[0] = "section .data";
  RoDataHeaderFooter[0] = "section .rodata";
  BssHeaderFooter[0] = "section .bss";
  FileHeader = "bits 16\ncpu 8086\n";
}

STATIC
void GenStartCommentLine(void)
{
  printf2("; ");
}

STATIC
void GenWordAlignment(int bss)
{
  printf2(bss ? "\talignb %d\n" : "\talign %d\n", SizeOfWord);
}

STATIC
void GenLabel(char* Label, int Static)
{
  if (UseLeadingUnderscores)
  {
    if (!Static && GenExterns)
      printf2("\tglobal\t_%s\n", Label);
    printf2("_%s:\n", Label);
  }
  else
  {
    if (!Static && GenExterns)
      printf2("\tglobal\t$%s\n", Label);
    printf2("$%s:\n", Label);
  }
  GenAddGlobal(Label, 1);
}

STATIC
void GenPrintLabel(char* Label)
{
  if (UseLeadingUnderscores)
  {
    printf2(isdigit(*Label) ? "L%s" : "_%s", Label);
  }
  else
  {
    printf2(isdigit(*Label) ? "..@L%s" : "$%s", Label);
  }
}

STATIC
void GenNumLabel(int Label)
{
  printf2(UseLeadingUnderscores ? "L%d:\n" :"..@L%d:\n", Label);
}

STATIC
void GenPrintNumLabel(int label)
{
  printf2(UseLeadingUnderscores ? "L%d" : "..@L%d", label);
}

STATIC
void GenZeroData(unsigned Size, int bss)
{
  printf2(bss ? "\tresb\t%u\n" : "\ttimes\t%u db 0\n", truncUint(Size));
}

STATIC
void GenIntData(int Size, int Val)
{
  Val = truncInt(Val);
    printf2(Size == 1 ? "\tdb\t%d\n" : "\tdw\t%d\n", Val);
}

STATIC
void GenStartAsciiString(void)
{
  printf2("\tdb\t");
}

STATIC
void GenAddrData(int Size, char* Label, int ofs)
{
  ofs = truncInt(ofs);
    printf2(Size == 1 ? "\tdb\t" : "\tdw\t");
  GenPrintLabel(Label);
  if (ofs)
    printf2(" %+d", ofs);
  puts2("");
  if (!isdigit(*Label))
    GenAddGlobal(Label, 2);
}

STATIC
int GenFxnSizeNeeded(void)
{
  return 0;
}

STATIC
void GenRecordFxnSize(char* startLabelName, int endLabelNo)
{
  // In the huge mode(l) individual functions must each fit into a 64KB segment.
  // A special non-allocated section, ".fxnsz", will hold function sizes and
  // the linker will check them.
  (void)startLabelName;
  (void)endLabelNo;
}

#define I8086InstrMov    0x00
#define I8086InstrXchg   0x03
#define I8086InstrLea    0x04
#define I8086InstrPush   0x05
#define I8086InstrPop    0x06
#define I8086InstrInc    0x07
#define I8086InstrDec    0x08
#define I8086InstrAdd    0x09
#define I8086InstrSub    0x0A
#define I8086InstrAnd    0x0B
#define I8086InstrXor    0x0C
#define I8086InstrOr     0x0D
#define I8086InstrCmp    0x0E
#define I8086InstrTest   0x0F
#define I8086InstrMul    0x10
#define I8086InstrImul   0x11
#define I8086InstrIdiv   0x12
#define I8086InstrDiv    0x13
#define I8086InstrShl    0x14
#define I8086InstrSar    0x15
#define I8086InstrShr    0x16
#define I8086InstrNeg    0x17
#define I8086InstrNot    0x18
#define I8086InstrCbw    0x19
#define I8086InstrCwd    0x1A
#define I8086InstrCdq    0x1B
#define I8086InstrSetCc  0x1C
#define I8086InstrJcc    0x1D
#define I8086InstrJNotCc 0x1E
#define I8086InstrLeave  0x1F
#define I8086InstrCall   0x20
#define I8086InstrRet    0x21
#define I8086InstrJmp    0x22

char* winstrs[] =
{
  "mov",
  0,
  0,
  "xchg",
  "lea",
  "push",
  "pop",
  "inc",
  "dec",
  "add",
  "sub",
  "and",
  "xor",
  "or",
  "cmp",
  "test",
  "mul",
  "imul",
  "idiv",
  "div",
  "shl",
  "sar",
  "shr",
  "neg",
  "not",
  "cbw",
  "cwd",
  "cdq",
  0, // setcc
  0, // jcc
  0, // j!cc
  0, // leave
  "call",
  0, // ret
  "jmp",
};

STATIC
void GenPrintInstr(int instr, int val)
{
  char* p = "";

  switch (instr)
  {
  case I8086InstrLeave:
    p = (OutputFormat != FormatSegHuge && OutputFormat != FormatSegUnreal) ? "leave" : "db\t0x66\n\tleave";
    break;

  case I8086InstrRet:
    p = (OutputFormat != FormatSegHuge && OutputFormat != FormatSegUnreal) ? "ret" : "retf";
    break;

  case I8086InstrJcc:
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
  case I8086InstrJNotCc:
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

  case I8086InstrSetCc:
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

  default:
    p = winstrs[instr];
    break;
  }

  switch (instr)
  {
  case I8086InstrCbw:
  case I8086InstrCwd:
  case I8086InstrLeave:
  case I8086InstrRet:
    printf2("\t%s", p);
    break;
  default:
    printf2("\t%s\t", p);
    break;
  }
}

#define I8086OpRegAByte                   0x00
#define I8086OpRegAByteHigh               0x01
#define I8086OpRegCByte                   0x02
#define I8086OpRegAWord                   0x03
#define I8086OpRegBWord                   0x04
#define I8086OpRegCWord                   0x05
#define I8086OpRegDWord                   0x06
#define I8086OpRegBpWord                  0x09
#define I8086OpRegSpWord                  0x0A
#define I8086OpRegAByteOrWord             0x0B
#define I8086OpRegCByteOrWord             0x0C
#define I8086OpConst                      0x0D
#define I8086OpLabel                      0x0E
#define I8086OpNumLabel                   0x0F
#define I8086OpIndLabel                   0x10
#define I8086OpIndLabelExplicitByte       0x11
#define I8086OpIndLabelExplicitWord       0x12
#define I8086OpIndLabelExplicitByteOrWord 0x14
#define I8086OpIndLocal                   0x15
#define I8086OpIndLocalExplicitByte       0x16
#define I8086OpIndLocalExplicitWord       0x17
#define I8086OpIndLocalExplicitByteOrWord 0x19
#define I8086OpIndRegB                    0x1A
#define I8086OpIndRegBExplicitByte        0x1B
#define I8086OpIndRegBExplicitWord        0x1C
#define I8086OpIndRegBExplicitByteOrWord  0x1E
#define I8086OpRegCByteHigh               0x1F

STATIC
int GenSelectByteOrWord(int op, int opSz)
{
  int tmp = opSz == 2;
  switch (op)
  {
  case I8086OpRegAByteOrWord:
    return tmp ? I8086OpRegAWord: I8086OpRegAByte;
  case I8086OpRegCByteOrWord:
    return tmp ? I8086OpRegCWord : I8086OpRegCByte;
  case I8086OpIndLabelExplicitByteOrWord:
    return tmp ? I8086OpIndLabelExplicitWord : I8086OpIndLabelExplicitByte;
  case I8086OpIndLocalExplicitByteOrWord:
    return tmp ? I8086OpIndLocalExplicitWord : I8086OpIndLocalExplicitByte;
  case I8086OpIndRegBExplicitByteOrWord:
    return tmp ? I8086OpIndRegBExplicitWord: I8086OpIndRegBExplicitByte;
  }
  return op;
}

STATIC
void GenPrintOperand(int op, int val)
{
  switch (op)
  {
  case I8086OpRegAByte: printf2("al"); break;
  case I8086OpRegAByteHigh: printf2("ah"); break;
  case I8086OpRegCByte: printf2("cl"); break;
  case I8086OpRegCByteHigh: printf2("ch"); break;
  case I8086OpRegAWord: printf2("ax"); break;
  case I8086OpRegBWord: printf2("bx"); break;
  case I8086OpRegCWord: printf2("cx"); break;
  case I8086OpRegDWord: printf2("dx"); break;
  case I8086OpRegBpWord: printf2("bp"); break;
  case I8086OpRegSpWord: printf2("sp"); break;
  case I8086OpConst: printf2("%d", truncInt(val)); break;
  case I8086OpLabel: GenPrintLabel(IdentTable + val); break;
  case I8086OpNumLabel: GenPrintNumLabel(val); break;
  case I8086OpIndLabel: printf2("["); GenPrintLabel(IdentTable + val); printf2("]"); break;
  case I8086OpIndLabelExplicitByte: printf2("byte ["); GenPrintLabel(IdentTable + val); printf2("]"); break;
  case I8086OpIndLabelExplicitWord: printf2("word ["); GenPrintLabel(IdentTable + val); printf2("]"); break;
  case I8086OpIndLocal: printf2("[bp%+d]", truncInt(val)); break;
  case I8086OpIndLocalExplicitByte: printf2("byte [bp%+d]", truncInt(val)); break;
  case I8086OpIndLocalExplicitWord: printf2("word [bp%+d]", truncInt(val)); break;
  case I8086OpIndRegB: printf2("[bx]"); break;
  case I8086OpIndRegBExplicitByte: printf2("byte [bx]"); break;
  case I8086OpIndRegBExplicitWord: printf2("word [bx]"); break;
  }
}

STATIC
void GenPrintOperandSeparator(void)
{
  printf2(", ");
}

STATIC
void GenPrintNewLine(void)
{
  puts2("");
}

STATIC
void GenPrintInstrNoOperand(int instr)
{
  GenPrintInstr(instr, 0);
  GenPrintNewLine();
}

STATIC
void GenPrintInstr1Operand(int instr, int instrval, int operand, int operandval)
{
  GenPrintInstr(instr, instrval);
  GenPrintOperand(operand, operandval);
  GenPrintNewLine();
}

STATIC
void GenPrintInstr2Operands(int instr, int instrval, int operand1, int operand1val, int operand2, int operand2val)
{
  /*
  if (operand2 == I8086OpConst && truncUint(operand2val) == 0 &&
      (instr == I8086InstrAdd || instr == I8086InstrSub))
    return;

  if (operand2 == I8086OpConst &&
      (operand2val == 1 || operand2val == -1) &&
      (instr == I8086InstrAdd || instr == I8086InstrSub))
  {
    if ((operand2val == 1 && instr == I8086InstrAdd) ||
        (operand2val == -1 && instr == I8086InstrSub))
      GenPrintInstr(I8086InstrInc, 0);
    else
      GenPrintInstr(I8086InstrDec, 0);
      
    GenPrintOperand(operand1, operand1val);
    GenPrintNewLine();
    return;
  }
  */

  GenPrintInstr(instr, instrval);
  GenPrintOperand(operand1, operand1val);
  GenPrintOperandSeparator();
  GenPrintOperand(operand2, operand2val);
  GenPrintNewLine();
}

STATIC
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

STATIC
void GenExtendRegAIfNeeded(int opSz)
{
    if (opSz == -1)
      GenPrintInstrNoOperand(I8086InstrCbw);
    else if (opSz == 1)
      GenPrintInstr2Operands(I8086InstrMov, 0,
                             I8086OpRegAByteHigh, 0,
                             I8086OpConst, 0);
   
}

STATIC
void GenJumpUncond(int label)
{
  GenPrintInstr1Operand(I8086InstrJmp, 0,
                        I8086OpNumLabel, label);
}

STATIC
void GenJumpIfEqual(int val, int label)
{
  GenPrintInstr2Operands(I8086InstrCmp, 0,
                         I8086OpRegAWord, 0,
                         I8086OpConst, val);
  GenPrintInstr1Operand(I8086InstrJcc, tokEQ,
                        I8086OpNumLabel, label);
}


STATIC
void GenJumpIfZero(int label)
{
  printf2(UseLeadingUnderscores ? "\ttest ax, ax\n\tje L%d\n" : "\ttest ax, ax\n\tje ..@L%d\n", label);
}

STATIC
void GenJumpIfNotZero(int label)
{
  printf2(UseLeadingUnderscores ? "\ttest ax, ax\n\tjne L%d\n" : "\ttest ax, ax\n\tjne ..@L%d\n", label);
}

fpos_t GenPrologPos;

STATIC
void GenWriteFrameSize(void)
{
  unsigned size = -CurFxnMinLocalOfs;
  int pfx = size ? ' ' : ';';
  if (SizeOfWord == 2 || OutputFormat == FormatSegHuge || OutputFormat == FormatSegUnreal)
    printf2("\t%csub\tsp, %10u\n", pfx, size); // 10 chars are enough for 32-bit unsigned ints
}

STATIC
void GenUpdateFrameSize(void)
{
  fpos_t pos;
  fgetpos(OutFile, &pos);
  fsetpos(OutFile, &GenPrologPos);
  GenWriteFrameSize();
  fsetpos(OutFile, &pos);
}

STATIC
void GenFxnProlog(void)
{
  GenPrintInstr1Operand(I8086InstrPush, 0,
                        I8086OpRegBpWord, 0);
    GenPrintInstr2Operands(I8086InstrMov, 0,
                           I8086OpRegBpWord, 0,
                           I8086OpRegSpWord, 0);
  fgetpos(OutFile, &GenPrologPos);
  GenWriteFrameSize();
}

STATIC
void GenGrowStack(int size)
{
  if (!size)
    return;
  GenPrintInstr2Operands(I8086InstrSub, 0,
                         I8086OpRegSpWord, 0,
                         I8086OpConst, size);
}

STATIC
void GenFxnEpilog(void)
{
  GenUpdateFrameSize();
    GenPrintInstr2Operands(I8086InstrMov,0,
                          I8086OpRegSpWord, 0,
                          I8086OpRegBpWord, 0);
    GenPrintInstr1Operand(I8086InstrPop,0,
                          I8086OpRegBpWord, 0);
  GenPrintInstrNoOperand(I8086InstrRet);
}

STATIC
int GenMaxLocalsSize(void)
{
  return 0x7FFF;
}


STATIC
void GenReadIdent(int opSz, int label)
{
  GenPrintInstr2Operands(I8086InstrMov, 0,
                         GenSelectByteOrWord(I8086OpRegAByteOrWord, opSz), 0,
                         I8086OpIndLabel, label);
  GenExtendRegAIfNeeded(opSz);
}

STATIC
void GenReadLocal(int opSz, int ofs)
{
  GenPrintInstr2Operands(I8086InstrMov, 0,
                         GenSelectByteOrWord(I8086OpRegAByteOrWord, opSz), 0,
                         I8086OpIndLocal, ofs);
  GenExtendRegAIfNeeded(opSz);
}

STATIC
void GenReadIndirect(int opSz)
{
  GenPrintInstr2Operands(I8086InstrMov, 0,
                         I8086OpRegBWord, 0,
                         I8086OpRegAWord, 0);
  
  GenPrintInstr2Operands(I8086InstrMov, 0,
                         GenSelectByteOrWord(I8086OpRegAByteOrWord, opSz), 0,
                         I8086OpIndRegB, 0);
  GenExtendRegAIfNeeded(opSz);
}

STATIC
void GenReadCRegIdent(int opSz, int label)
{
  if (opSz == -1)
  {

      GenPrintInstr1Operand(I8086InstrPush, 0,
                            I8086OpRegAWord, 0);
      GenPrintInstr2Operands(I8086InstrMov, 0,
                            I8086OpRegAByte, 0,
                            I8086OpIndLabelExplicitByte, label);
      GenPrintInstrNoOperand(I8086InstrCbw);
      GenPrintInstr2Operands(I8086InstrMov, 0,
                            I8086OpRegCWord, 0,
                            I8086OpRegAWord, 0);
      GenPrintInstr1Operand(I8086InstrPop, 0,
                            I8086OpRegAWord, 0);
  }
  else if (opSz == 1)
  {
      GenPrintInstr2Operands(I8086InstrMov, 0,
                            I8086OpRegCByte, 0,
                            I8086OpIndLabelExplicitByte, label);
      GenPrintInstr2Operands(I8086InstrXor, 0,
                            I8086OpRegCByteHigh, 0,
                            I8086OpRegCByteHigh, 0);
  }
  else
    GenPrintInstr2Operands(I8086InstrMov, 0,
                           I8086OpRegCWord, 0,
                           I8086OpIndLabel, label);
}

STATIC
void GenReadCRegLocal(int opSz, int ofs)
{
  if (opSz == -1)
  {

      GenPrintInstr1Operand(I8086InstrPush, 0,
                            I8086OpRegAWord, 0);
      GenPrintInstr2Operands(I8086InstrMov, 0,
                            I8086OpRegAByte, 0,
                            I8086OpIndLocalExplicitByte, ofs);
      GenPrintInstrNoOperand(I8086InstrCbw);
      GenPrintInstr2Operands(I8086InstrMov, 0,
                            I8086OpRegCWord, 0,
                            I8086OpRegAWord, 0);
      GenPrintInstr1Operand(I8086InstrPop, 0,
                            I8086OpRegAWord, 0);
  }
  else if (opSz == 1)
  {
      GenPrintInstr2Operands(I8086InstrMov, 0,
                            I8086OpRegCByte, 0,
                            I8086OpIndLocalExplicitByte, ofs);
      GenPrintInstr2Operands(I8086InstrXor, 0,
                            I8086OpRegCByteHigh, 0,
                            I8086OpRegCByteHigh, 0);
  }
  else
    GenPrintInstr2Operands(I8086InstrMov, 0,
                           I8086OpRegCWord, 0,
                           I8086OpIndLocal, ofs);
}

STATIC
void GenReadCRegIndirect(int opSz)
{
  GenPrintInstr2Operands(I8086InstrMov, 0,
                         I8086OpRegBWord, 0,
                         I8086OpRegAWord, 0);

  if (opSz == -1)
  {

      GenPrintInstr1Operand(I8086InstrPush, 0,
                            I8086OpRegAWord, 0);
      GenPrintInstr2Operands(I8086InstrMov, 0,
                            I8086OpRegAByte, 0,
                            I8086OpIndRegBExplicitByte, 0);
      GenPrintInstrNoOperand(I8086InstrCbw);
      GenPrintInstr2Operands(I8086InstrMov, 0,
                            I8086OpRegCWord, 0,
                            I8086OpRegAWord, 0);
      GenPrintInstr1Operand(I8086InstrPop, 0,
                            I8086OpRegAWord, 0);
  }
  else if (opSz == 1)
  {
      GenPrintInstr2Operands(I8086InstrMov, 0,
                            I8086OpRegCByte, 0,
                            I8086OpIndRegBExplicitByte, 0);
      GenPrintInstr2Operands(I8086InstrXor, 0,
                            I8086OpRegCByteHigh, 0,
                            I8086OpRegCByteHigh, 0);
  }
  else
    GenPrintInstr2Operands(I8086InstrMov, 0,
                           I8086OpRegCWord, 0,
                           I8086OpIndRegB, 0);
}

STATIC
void GenIncDecIdent(int opSz, int label, int tok)
{
  int instr = I8086InstrInc;

  if (tok != tokInc)
    instr = I8086InstrDec;

  GenPrintInstr1Operand(instr, 0,
                        GenSelectByteOrWord(I8086OpIndLabelExplicitByteOrWord, opSz), label);
  GenPrintInstr2Operands(I8086InstrMov, 0,
                         GenSelectByteOrWord(I8086OpRegAByteOrWord, opSz), 0,
                         I8086OpIndLabel, label);
  GenExtendRegAIfNeeded(opSz);
}

STATIC
void GenIncDecLocal(int opSz, int ofs, int tok)
{
  int instr = I8086InstrInc;

  if (tok != tokInc)
    instr = I8086InstrDec;

  GenPrintInstr1Operand(instr, 0,
                        GenSelectByteOrWord(I8086OpIndLocalExplicitByteOrWord, opSz), ofs);
  GenPrintInstr2Operands(I8086InstrMov, 0,
                         GenSelectByteOrWord(I8086OpRegAByteOrWord, opSz), 0,
                         I8086OpIndLocal, ofs);
  GenExtendRegAIfNeeded(opSz);
}

STATIC
void GenIncDecIndirect(int opSz, int tok)
{
  int instr = I8086InstrInc;

  if (tok != tokInc)
    instr = I8086InstrDec;

  GenPrintInstr2Operands(I8086InstrMov, 0,
                         I8086OpRegBWord, 0,
                         I8086OpRegAWord, 0);

  GenPrintInstr1Operand(instr, 0,
                        GenSelectByteOrWord(I8086OpIndRegBExplicitByteOrWord, opSz), 0);
  GenPrintInstr2Operands(I8086InstrMov, 0,
                         GenSelectByteOrWord(I8086OpRegAByteOrWord, opSz), 0,
                         I8086OpIndRegB, 0);
  GenExtendRegAIfNeeded(opSz);
}

STATIC
void GenPostIncDecIdent(int opSz, int label, int tok)
{
  int instr = I8086InstrInc;

  if (tok != tokPostInc)
    instr = I8086InstrDec;

  GenPrintInstr2Operands(I8086InstrMov, 0,
                         GenSelectByteOrWord(I8086OpRegAByteOrWord, opSz), 0,
                         I8086OpIndLabel, label);
  GenExtendRegAIfNeeded(opSz);
  GenPrintInstr1Operand(instr, 0,
                        GenSelectByteOrWord(I8086OpIndLabelExplicitByteOrWord, opSz), label);
}

STATIC
void GenPostIncDecLocal(int opSz, int ofs, int tok)
{
  int instr = I8086InstrInc;

  if (tok != tokPostInc)
    instr = I8086InstrDec;

  GenPrintInstr2Operands(I8086InstrMov, 0,
                         GenSelectByteOrWord(I8086OpRegAByteOrWord, opSz), 0,
                         I8086OpIndLocal, ofs);
  GenExtendRegAIfNeeded(opSz);
  GenPrintInstr1Operand(instr, 0,
                        GenSelectByteOrWord(I8086OpIndLocalExplicitByteOrWord, opSz), ofs);
}

STATIC
void GenPostIncDecIndirect(int opSz, int tok)
{
  int instr = I8086InstrInc;

  if (tok != tokPostInc)
    instr = I8086InstrDec;

  GenPrintInstr2Operands(I8086InstrMov, 0,
                         I8086OpRegBWord, 0,
                         I8086OpRegAWord, 0);

  GenPrintInstr2Operands(I8086InstrMov, 0,
                         GenSelectByteOrWord(I8086OpRegAByteOrWord, opSz), 0,
                         I8086OpIndRegB, 0);
  GenExtendRegAIfNeeded(opSz);
  GenPrintInstr1Operand(instr, 0,
                        GenSelectByteOrWord(I8086OpIndRegBExplicitByteOrWord, opSz), 0);
}

STATIC
void GenPostAddSubIdent(int opSz, int val, int label, int tok)
{
  int instr = I8086InstrAdd;

  if (tok != tokPostAdd)
    instr = I8086InstrSub;

  GenPrintInstr2Operands(I8086InstrMov, 0,
                         GenSelectByteOrWord(I8086OpRegAByteOrWord, opSz), 0,
                         I8086OpIndLabel, label);
  GenExtendRegAIfNeeded(opSz);
  GenPrintInstr2Operands(instr, 0,
                         GenSelectByteOrWord(I8086OpIndLabelExplicitByteOrWord, opSz), label,
                         I8086OpConst, val);
}

STATIC
void GenPostAddSubLocal(int opSz, int val, int ofs, int tok)
{
  int instr = I8086InstrAdd;

  if (tok != tokPostAdd)
    instr = I8086InstrSub;

  GenPrintInstr2Operands(I8086InstrMov, 0,
                         GenSelectByteOrWord(I8086OpRegAByteOrWord, opSz), 0,
                         I8086OpIndLocal, ofs);
  GenExtendRegAIfNeeded(opSz);
  GenPrintInstr2Operands(instr, 0,
                         GenSelectByteOrWord(I8086OpIndLocalExplicitByteOrWord, opSz), ofs,
                         I8086OpConst, val);
}

STATIC
void GenPostAddSubIndirect(int opSz, int val, int tok)
{
  int instr = I8086InstrAdd;

  if (tok != tokPostAdd)
    instr = I8086InstrSub;

  GenPrintInstr2Operands(I8086InstrMov, 0,
                         I8086OpRegBWord, 0,
                         I8086OpRegAWord, 0);

  GenPrintInstr2Operands(I8086InstrMov, 0,
                         GenSelectByteOrWord(I8086OpRegAByteOrWord, opSz), 0,
                         I8086OpIndRegB, 0);
  GenExtendRegAIfNeeded(opSz);
  GenPrintInstr2Operands(instr, 0,
                         GenSelectByteOrWord(I8086OpIndRegBExplicitByteOrWord, opSz), 0,
                         I8086OpConst, val);
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

STATIC
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

STATIC
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
    //error("GenFuse(): idx < 0\n");
    errorInternal(100);

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
  case tokGoto:
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
  case tokUChar:
  case tokSChar:
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
    stack[oldIdxRight + 1][1] = (opSzLeft + 8) * 16 + (opSzRight + 8);

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
    //error("GenFuse: unexpected token %s\n", GetTokenName(tok));
    errorInternal(101);
  }
}

STATIC
int GenGetBinaryOperatorInstr(int tok)
{
  switch (tok)
  {
  case tokPostAdd:
  case tokAssignAdd:
  case '+':
    return I8086InstrAdd;
  case tokPostSub:
  case tokAssignSub:
  case '-':
    return I8086InstrSub;
  case '&':
  case tokAssignAnd:
    return I8086InstrAnd;
  case '^':
  case tokAssignXor:
    return I8086InstrXor;
  case '|':
  case tokAssignOr:
    return I8086InstrOr;
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
    return I8086InstrCmp;
  case '*':
  case tokAssignMul:
    return I8086InstrMul;
  case '/':
  case '%':
  case tokAssignDiv:
  case tokAssignMod:
    return I8086InstrIdiv;
  case tokUDiv:
  case tokUMod:
  case tokAssignUDiv:
  case tokAssignUMod:
    return I8086InstrDiv;
  case tokLShift:
  case tokAssignLSh:
    return I8086InstrShl;
  case tokRShift:
  case tokAssignRSh:
    return I8086InstrSar;
  case tokURShift:
  case tokAssignURSh:
    return I8086InstrShr;

  default:
    //error("Error: Invalid operator\n");
    errorInternal(102);
    return 0;
  }
}

// Newer, less stack-dependent code generator,
// generates more compact code (~30% less) than the stack-based generator
#ifndef CG_STACK_BASED
STATIC
void GenExpr1(void)
{
  int s = sp - 1;
  int i;

  if (stack[s][0] == tokIf || stack[s][0] == tokIfNot || stack[s][0] == tokReturn)
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
    case tokGoto:
        printf2("[goto->%d]", stack[i][1]);
      break;
    case tokLocalOfs:
    case tokOpLocalOfs:
      printf2("(@%d)", truncInt(stack[i][1]));
      break;
    case tokOpIndLocalOfs:
      printf2("*(@%d)", truncInt(stack[i][1]));
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
    case tokReturn:
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
        GenPrintInstr2Operands(I8086InstrMov, 0,
                               I8086OpRegAWord, 0,
                               I8086OpConst, v);
      break;
    case tokIdent:
      // Don't load operand into ax when ax is going to be pushed next, push it directly
      if (!(i + 1 < sp && (stack[i + 1][0] == ',' || stack[i + 1][0] == ')')))
        GenPrintInstr2Operands(I8086InstrMov, 0,
                               I8086OpRegAWord, 0,
                               I8086OpLabel, v);
      break;
    case tokLocalOfs:
      GenPrintInstr2Operands(I8086InstrLea, 0,
                             I8086OpRegAWord, 0,
                             I8086OpIndLocal, v);
      break;

    case '~':
      GenPrintInstr1Operand(I8086InstrNot, 0,
                            I8086OpRegAWord, 0);
      break;
    case tokUnaryMinus:
      GenPrintInstr1Operand(I8086InstrNeg, 0,
                            I8086OpRegAWord, 0);
      break;
    case tok_Bool:
      GenPrintInstr2Operands(I8086InstrTest, 0,
                             I8086OpRegAWord, 0,
                             I8086OpRegAWord, 0);
        int labelCC = LabelCnt++;
        int labelCCAfter = LabelCnt++;
        GenPrintInstr1Operand(I8086InstrJcc, tokNEQ,
                              I8086OpNumLabel, labelCC);
        GenPrintInstr2Operands(I8086InstrMov, 0,
                              I8086OpRegAByte, 0,
                              I8086OpConst, 0);
        GenPrintInstr1Operand(I8086InstrJmp, 0,
                              I8086OpNumLabel, labelCCAfter);
        GenNumLabel(labelCC);
        GenPrintInstr2Operands(I8086InstrMov, 0,
                              I8086OpRegAByte, 0,
                              I8086OpConst, 1);
        GenNumLabel(labelCCAfter);

      // fallthrough
    case tokSChar:
        GenPrintInstrNoOperand(I8086InstrCbw);
      break;
    case tokUChar:
      GenPrintInstr2Operands(I8086InstrAnd, 0,
                             I8086OpRegAWord, 0,
                             I8086OpConst, 0xFF);
      break;

    case tokShortCirc:
      if (v >= 0)
        GenJumpIfZero(v); // &&
      else
        GenJumpIfNotZero(-v); // ||
      break;
    case tokGoto:
      GenJumpUncond(v);
      break;
    case tokLogAnd:
    case tokLogOr:
      GenNumLabel(v);
      break;

    case tokPushAcc:
      // TBD??? handle similarly to ','???
      GenPrintInstr1Operand(I8086InstrPush, 0,
                            I8086OpRegAWord, 0);
      break;

    case ',':
      // push operand directly if it hasn't been loaded into ax
      if (stack[i - 2][0] == tokUnaryStar && stack[i - 2][1] == SizeOfWord)
      {
        switch (stack[i - 1][0])
        {
        case tokOpIdent:
          GenPrintInstr1Operand(I8086InstrPush, 0,
                                I8086OpIndLabelExplicitWord, stack[i - 1][1]);
          break;
        case tokOpLocalOfs:
          GenPrintInstr1Operand(I8086InstrPush, 0,
                                I8086OpIndLocalExplicitWord, stack[i - 1][1]);
          break;
        case tokOpAcc:
          GenPrintInstr2Operands(I8086InstrMov, 0,
                                 I8086OpRegBWord, 0,
                                 I8086OpRegAWord, 0);
          GenPrintInstr1Operand(I8086InstrPush, 0,
                                I8086OpIndRegBExplicitWord, 0);
          break;
        }
      }
      else
      {
        switch (stack[i - 1][0])
        {
        case tokNumInt:
        case tokNumUint:
            GenPrintInstr2Operands(I8086InstrMov, 0,
                                  I8086OpRegAWord, 0,
                                  I8086OpConst, stack[i - 1][1]);
            GenPrintInstr1Operand(I8086InstrPush, 0,
                                  I8086OpRegAWord, 0);
          break;
        case tokIdent:
            GenPrintInstr2Operands(I8086InstrMov, 0,
                                  I8086OpRegAWord, 0,
                                  I8086OpLabel, stack[i - 1][1]);
            GenPrintInstr1Operand(I8086InstrPush, 0,
                                  I8086OpRegAWord, 0);
          break;
        default:
          GenPrintInstr1Operand(I8086InstrPush, 0,
                                I8086OpRegAWord, 0);
          break;
        }
      }
      break;

    case tokUnaryStar:
      // Don't load operand into ax when ax is going to be pushed next, push it directly
      if (!(v == SizeOfWord && i + 2 < sp && stack[i + 2][0] == ','))
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
          GenPrintInstr2Operands(I8086InstrMov, 0,
                                 I8086OpRegCWord, 0,
                                 I8086OpRegAWord, 0);
        }
        else if (stack[i + 2][0] == tokOpIndAcc)
        {
          GenReadCRegIndirect(v % 16 - 8);
        }
      }

      // load the left operand into ax (or the right operand if it's '=')

      if (tok == '=')
      {
        if (stack[i + 1][0] == tokOpIndAcc)
          GenPrintInstr2Operands(I8086InstrMov, 0,
                                 I8086OpRegBWord, 0,
                                 I8086OpRegAWord, 0);
        // "swap" left and right operands
        i++;
        v = v / 16 + v % 16 * 16;
      }

      switch (stack[i + 1][0])
      {
      case tokOpNumInt:
      case tokOpNumUint:
        GenPrintInstr2Operands(I8086InstrMov, 0,
                               I8086OpRegAWord, 0,
                               I8086OpConst, stack[i + 1][1]);
        break;
      case tokOpIdent:
        GenPrintInstr2Operands(I8086InstrMov, 0,
                               I8086OpRegAWord, 0,
                               I8086OpLabel, stack[i + 1][1]);
        break;
      case tokOpLocalOfs:
        GenPrintInstr2Operands(I8086InstrLea, 0,
                               I8086OpRegAWord, 0,
                               I8086OpIndLocal, stack[i + 1][1]);
        break;
      case tokOpAcc:
        break;
      case tokOpIndIdent:
        GenReadIdent(v / 16 - 8, stack[i + 1][1]);
        break;
      case tokOpIndLocalOfs:
        GenReadLocal(v / 16 - 8, stack[i + 1][1]);
        break;
      case tokOpIndAcc:
        GenReadIndirect(v / 16 - 8);
        break;
      case tokOpStack:
        GenPrintInstr1Operand(I8086InstrPop, 0,
                              I8086OpRegAWord, 0);
        break;
      case tokOpIndStack:
        GenPrintInstr1Operand(I8086InstrPop, 0,
                              I8086OpRegBWord, 0);
        GenPrintInstr2Operands(I8086InstrMov, 0,
                               GenSelectByteOrWord(I8086OpRegAByteOrWord, v / 16 - 8), 0,
                               I8086OpIndRegB, 0);
        GenExtendRegAIfNeeded(v / 16 - 8);
        break;
      }

      if (tok == '=')
      {
        // "unswap" left and right operands
        i--;
        v = v / 16 + v % 16 * 16;

        if (stack[i + 1][0] == tokOpIndStack)
          GenPrintInstr1Operand(I8086InstrPop, 0,
                                I8086OpRegBWord, 0);
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
                                 I8086OpRegAWord, 0,
                                 I8086OpConst, stack[i + 2][1]);
          break;
        case tokOpIdent:
          GenPrintInstr2Operands(instr, 0,
                                 I8086OpRegAWord, 0,
                                 I8086OpLabel, stack[i + 2][1]);
          break;
        case tokOpLocalOfs:
          GenPrintInstr2Operands(I8086InstrLea, 0,
                                 I8086OpRegCWord, 0,
                                 I8086OpIndLocal, stack[i + 2][1]);
          GenPrintInstr2Operands(instr, 0,
                                 I8086OpRegAWord, 0,
                                 I8086OpRegCWord, 0);
          break;
        case tokOpAcc:
        case tokOpIndAcc:
          // right operand in cx already
          GenPrintInstr2Operands(instr, 0,
                                 I8086OpRegAWord, 0,
                                 I8086OpRegCWord, 0);
          break;
        case tokOpIndIdent:
          if (v % 16 - 8 != SizeOfWord)
          {
            GenReadCRegIdent(v % 16 - 8, stack[i + 2][1]);
            GenPrintInstr2Operands(instr, 0,
                                   I8086OpRegAWord, 0,
                                   I8086OpRegCWord, 0);
          }
          else
          {
            GenPrintInstr2Operands(instr, 0,
                                   I8086OpRegAWord, 0,
                                   I8086OpIndLabel, stack[i + 2][1]);
          }
          break;
        case tokOpIndLocalOfs:
          if (v % 16 - 8 != SizeOfWord)
          {
            GenReadCRegLocal(v % 16 - 8, stack[i + 2][1]);
            GenPrintInstr2Operands(instr, 0,
                                   I8086OpRegAWord, 0,
                                   I8086OpRegCWord, 0);
          }
          else
          {
            GenPrintInstr2Operands(instr, 0,
                                   I8086OpRegAWord, 0,
                                   I8086OpIndLocal, stack[i + 2][1]);
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
              GenPrintInstr1Operand(I8086InstrJcc, tok,
                                    I8086OpNumLabel, stack[i + 3][1]);
            else
              GenPrintInstr1Operand(I8086InstrJNotCc, tok,
                                    I8086OpNumLabel, stack[i + 3][1]);
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
            {
              int labelCC = LabelCnt++;
              int labelCCAfter = LabelCnt++;
              GenPrintInstr1Operand(I8086InstrJcc, tok,
                                    I8086OpNumLabel, labelCC);
              GenPrintInstr2Operands(I8086InstrMov, 0,
                                    I8086OpRegAByte, 0,
                                    I8086OpConst, 0);
              GenPrintInstr1Operand(I8086InstrJmp, 0,
                                    I8086OpNumLabel, labelCCAfter);
              GenNumLabel(labelCC);
              GenPrintInstr2Operands(I8086InstrMov, 0,
                                    I8086OpRegAByte, 0,
                                    I8086OpConst, 1);
              GenNumLabel(labelCCAfter);
            
              GenPrintInstrNoOperand(I8086InstrCbw);
            }
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
            GenPrintInstr2Operands(I8086InstrMov, 0,
                                  I8086OpRegBWord, 0,
                                  I8086OpConst, stack[i + 2][1]);
            GenPrintInstr1Operand(I8086InstrImul, 0,
                                  I8086OpRegBWord, 0);
          break;
        case tokOpIdent:
            GenPrintInstr2Operands(I8086InstrMov, 0,
                                  I8086OpRegBWord, 0,
                                  I8086OpLabel, stack[i + 2][1]);
            GenPrintInstr1Operand(I8086InstrImul, 0,
                                  I8086OpRegBWord, 0);
          break;
        case tokOpLocalOfs:
          GenPrintInstr2Operands(I8086InstrLea, 0,
                                 I8086OpRegCWord, 0,
                                 I8086OpIndLocal, stack[i + 2][1]);
          GenPrintInstr1Operand(instr, 0,
                                I8086OpRegCWord, 0);
          break;
        case tokOpAcc:
        case tokOpIndAcc:
          // right operand in cx already
          GenPrintInstr1Operand(instr, 0,
                                I8086OpRegCWord, 0);
          break;
        case tokOpIndIdent:
          if (v % 16 - 8 != SizeOfWord)
          {
            GenReadCRegIdent(v % 16 - 8, stack[i + 2][1]);
            GenPrintInstr1Operand(instr, 0,
                                  I8086OpRegCWord, 0);
          }
          else
          {
            GenPrintInstr1Operand(instr, 0,
                                  I8086OpIndLabelExplicitWord, stack[i + 2][1]);
          }
          break;
        case tokOpIndLocalOfs:
          if (v % 16 - 8 != SizeOfWord)
          {
            GenReadCRegLocal(v % 16 - 8, stack[i + 2][1]);
            GenPrintInstr1Operand(instr, 0,
                                  I8086OpRegCWord, 0);
          }
          else
          {
            GenPrintInstr1Operand(instr, 0,
                                  I8086OpIndLocalExplicitWord, stack[i + 2][1]);
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
          
          GenPrintInstrNoOperand(I8086InstrCwd);
          break;
        default:
          GenPrintInstr2Operands(I8086InstrMov, 0,
                                 I8086OpRegDWord, 0,
                                 I8086OpConst, 0);
          break;
        }

        switch (stack[i + 2][0])
        {
        case tokOpNumInt:
        case tokOpNumUint:
          GenPrintInstr2Operands(I8086InstrMov, 0,
                                 I8086OpRegCWord, 0,
                                 I8086OpConst, stack[i + 2][1]);
          GenPrintInstr1Operand(instr, 0,
                                I8086OpRegCWord, 0);
          break;
        case tokOpIdent:
          GenPrintInstr2Operands(I8086InstrMov, 0,
                                 I8086OpRegCWord, 0,
                                 I8086OpLabel, stack[i + 2][1]);
          GenPrintInstr1Operand(instr, 0,
                                I8086OpRegCWord, 0);
          break;
        case tokOpLocalOfs:
          GenPrintInstr2Operands(I8086InstrLea, 0,
                                 I8086OpRegCWord, 0,
                                 I8086OpIndLocal, stack[i + 2][1]);
          GenPrintInstr1Operand(instr, 0,
                                I8086OpRegCWord, 0);
          break;
        case tokOpAcc:
        case tokOpIndAcc:
          // right operand in cx already
          GenPrintInstr1Operand(instr, 0,
                                I8086OpRegCWord, 0);
          break;
        case tokOpIndIdent:
          if (v % 16 - 8 != SizeOfWord)
          {
            GenReadCRegIdent(v % 16 - 8, stack[i + 2][1]);
            GenPrintInstr1Operand(instr, 0,
                                  I8086OpRegCWord, 0);
          }
          else
          {
            GenPrintInstr1Operand(instr, 0,
                                  I8086OpIndLabelExplicitWord, stack[i + 2][1]);
          }
          break;
        case tokOpIndLocalOfs:
          if (v % 16 - 8 != SizeOfWord)
          {
            GenReadCRegLocal(v % 16 - 8, stack[i + 2][1]);
            GenPrintInstr1Operand(instr, 0,
                                  I8086OpRegCWord, 0);
          }
          else
          {
            GenPrintInstr1Operand(instr, 0,
                                  I8086OpIndLocalExplicitWord, stack[i + 2][1]);
          }
        }

        if (tok == '%' || tok == tokAssignMod ||
            tok == tokUMod || tok == tokAssignUMod)
          GenPrintInstr2Operands(I8086InstrMov, 0,
                                 I8086OpRegAWord, 0,
                                 I8086OpRegDWord, 0);
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
            GenPrintInstr2Operands(I8086InstrMov, 0,
                                  I8086OpRegCByte, 0,
                                  I8086OpConst, stack[i + 2][1]);
            GenPrintInstr2Operands(instr, 0,
                                  I8086OpRegAWord, 0,
                                  I8086OpRegCByte, 0);
          break;
        case tokOpIdent:
            GenPrintInstr2Operands(I8086InstrMov, 0,
                                  I8086OpRegCByte, 0,
                                  I8086OpLabel, stack[i + 2][1]);
            GenPrintInstr2Operands(instr, 0,
                                  I8086OpRegAWord, 0,
                                  I8086OpRegCByte, 0);
          break;
        case tokOpLocalOfs:
          GenPrintInstr2Operands(I8086InstrLea, 0,
                                 I8086OpRegCWord, 0,
                                 I8086OpIndLocal, stack[i + 2][1]);
          GenPrintInstr2Operands(instr, 0,
                                 I8086OpRegAWord, 0,
                                 I8086OpRegCByte, 0);
          break;
        case tokOpAcc:
        case tokOpIndAcc:
          // right operand in cx already
          GenPrintInstr2Operands(instr, 0,
                                 I8086OpRegAWord, 0,
                                 I8086OpRegCByte, 0);
          break;
        case tokOpIndIdent:
          GenPrintInstr2Operands(I8086InstrMov, 0,
                                 I8086OpRegCByte, 0,
                                 I8086OpIndLabel, stack[i + 2][1]);
          GenPrintInstr2Operands(instr, 0,
                                 I8086OpRegAWord, 0,
                                 I8086OpRegCByte, 0);
          break;
        case tokOpIndLocalOfs:
          GenPrintInstr2Operands(I8086InstrMov, 0,
                                 I8086OpRegCByte, 0,
                                 I8086OpIndLocal, stack[i + 2][1]);
          GenPrintInstr2Operands(instr, 0,
                                 I8086OpRegAWord, 0,
                                 I8086OpRegCByte, 0);
          break;
        }
        break;

      case '=':
        break;

      default:
        //error("Error: Internal Error: GenExpr1() a: unexpected token %s\n", GetTokenName(tok));
        errorInternal(103);
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
          GenPrintInstr2Operands(I8086InstrMov, 0,
                                 I8086OpIndLabel, stack[i + 1][1],
                                 GenSelectByteOrWord(I8086OpRegAByteOrWord, v / 16 - 8), 0);
          break;
        case tokOpIndLocalOfs:
          GenPrintInstr2Operands(I8086InstrMov, 0,
                                 I8086OpIndLocal, stack[i + 1][1],
                                 GenSelectByteOrWord(I8086OpRegAByteOrWord, v / 16 - 8), 0);
          break;
        case tokOpIndAcc:
        case tokOpIndStack:
          GenPrintInstr2Operands(I8086InstrMov, 0,
                                 I8086OpIndRegB, 0,
                                 GenSelectByteOrWord(I8086OpRegAByteOrWord, v / 16 - 8), 0);
          break;
        }
        // the result of the expression is of type of the
        // left lvalue operand, so, "truncate" it if needed
        GenExtendRegAIfNeeded(v / 16 - 8);
      }
      i += 2;
      break;

    case ')':
      // DONE: "call ident"
      if (stack[i - 1][0] == tokIdent)
      {
          GenPrintInstr1Operand(I8086InstrCall, 0,
                                I8086OpLabel, stack[i - 1][1]);
      }
      else
      {
          GenPrintInstr1Operand(I8086InstrCall, 0,
                                I8086OpRegAWord, 0);
      }
      GenGrowStack(-v);
      break;

    case '(':
    case tokIf:
    case tokIfNot:
    case tokReturn:
      break;

    case tokVoid:
    case tokComma:
      break;

    default:
      //error("Error: Internal Error: GenExpr1() b: unexpected token %s\n", GetTokenName(tok));
      errorInternal(104);
      break;
    }
  }
}
#else // #ifndef CG_STACK_BASED
// Original, primitive stack-based code generator
// DONE: test 32-bit code generation
STATIC
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
    case tokGoto: printf2("; sh-circ-goto "); break;
    case tokLogAnd: printf2("; short-circuit && target\n"); break;
    case tokLogOr: printf2("; short-circuit || target\n"); break;
    case tokIf: case tokIfNot: case tokReturn: break;
    default: printf2("; %s\n", GetTokenName(tok)); break;
    }
#endif

    switch (tok)
    {
    case tokNumInt:
    case tokNumUint:
      if (gotUnary)
        GenPrintInstr1Operand(I8086InstrPush, 0,
                              I8086OpRegAWord, 0);
      GenPrintInstr2Operands(I8086InstrMov, 0,
                             I8086OpRegAWord, 0,
                             I8086OpConst, v);
      gotUnary = 1;
      break;

    case tokIdent:
      if (gotUnary)
        GenPrintInstr1Operand(I8086InstrPush, 0,
                              I8086OpRegAWord, 0);
      GenPrintInstr2Operands(I8086InstrMov, 0,
                             I8086OpRegAWord, 0,
                             I8086OpLabel, v);
      gotUnary = 1;
      break;

    case tokLocalOfs:
      if (gotUnary)
        GenPrintInstr1Operand(I8086InstrPush, 0,
                              I8086OpRegAWord, 0);
      GenPrintInstr2Operands(I8086InstrLea, 0,
                             I8086OpRegAWord, 0,
                             I8086OpIndLocal, v);
      gotUnary = 1;
      break;

    case ')':
        GenPrintInstr1Operand(I8086InstrCall, 0,
                              I8086OpRegAWord, 0);
      GenGrowStack(-v);
      break;

    case tokUnaryStar:
      GenReadIndirect(v);
      break;

    case tokUnaryPlus:
      break;
    case '~':
      GenPrintInstr1Operand(I8086InstrNot, 0,
                            I8086OpRegAWord, 0);
      break;
    case tokUnaryMinus:
      GenPrintInstr1Operand(I8086InstrNeg, 0,
                            I8086OpRegAWord, 0);
      break;

    case '+':
    case '-':
    case '*':
    case '&':
    case '^':
    case '|':
      {
        int instr = GenGetBinaryOperatorInstr(tok);
        GenPrintInstr1Operand(I8086InstrPop, 0,
                              I8086OpRegBWord, 0);
        if (tok == '-')
          GenPrintInstr2Operands(I8086InstrXchg, 0,
                                 I8086OpRegAWord, 0,
                                 I8086OpRegBWord, 0);
        if (tok != '*')
          GenPrintInstr2Operands(instr, 0,
                                 I8086OpRegAWord, 0,
                                 I8086OpRegBWord, 0);
        else
          GenPrintInstr1Operand(instr, 0,
                                I8086OpRegBWord, 0);
      }
      break;

    case '/':
    case tokUDiv:
    case '%':
    case tokUMod:
      GenPrintInstr1Operand(I8086InstrPop, 0,
                            I8086OpRegBWord, 0);
      GenPrintInstr2Operands(I8086InstrXchg, 0,
                             I8086OpRegAWord, 0,
                             I8086OpRegBWord, 0);
      if (tok == '/' || tok == '%')
      {
        
        GenPrintInstrNoOperand(I8086InstrCwd);
        GenPrintInstr1Operand(I8086InstrIdiv, 0,
                              I8086OpRegBWord, 0);
      }
      else
      {
        GenPrintInstr2Operands(I8086InstrMov, 0,
                               I8086OpRegDWord, 0,
                               I8086OpConst, 0);
        GenPrintInstr1Operand(I8086InstrDiv, 0,
                              I8086OpRegBWord, 0);
      }
      if (tok == '%' || tok == tokUMod)
        GenPrintInstr2Operands(I8086InstrMov, 0,
                               I8086OpRegAWord, 0,
                               I8086OpRegDWord, 0);
      break;

    case tokLShift:
    case tokRShift:
    case tokURShift:
      {
        int instr = GenGetBinaryOperatorInstr(tok);
        GenPrintInstr1Operand(I8086InstrPop, 0,
                              I8086OpRegCWord, 0);
        GenPrintInstr2Operands(I8086InstrXchg, 0,
                               I8086OpRegAWord, 0,
                               I8086OpRegCWord, 0);
        GenPrintInstr2Operands(instr, 0,
                               I8086OpRegAWord, 0,
                               I8086OpRegCByte, 0);
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
        GenPrintInstr1Operand(I8086InstrPop, 0,
                              I8086OpRegBWord, 0);
        GenPrintInstr2Operands(I8086InstrMov, 0,
                               I8086OpRegCWord, 0,
                               I8086OpRegAWord, 0);
        GenPrintInstr2Operands(I8086InstrMov, 0,
                               GenSelectByteOrWord(I8086OpRegAByteOrWord, v), 0,
                               I8086OpIndRegB, 0);
        GenPrintInstr2Operands(instr, 0,
                               I8086OpIndRegB, 0,
                               GenSelectByteOrWord(I8086OpRegCByteOrWord, v), 0);
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
        GenPrintInstr1Operand(I8086InstrPop, 0,
                              I8086OpRegBWord, 0);
        if (tok != tokAssignMul)
        {
          GenPrintInstr2Operands(instr, 0,
                                 I8086OpIndRegB, 0,
                                 GenSelectByteOrWord(I8086OpRegAByteOrWord, v), 0);
          GenPrintInstr2Operands(I8086InstrMov, 0,
                                 GenSelectByteOrWord(I8086OpRegAByteOrWord, v), 0,
                                 I8086OpIndRegB, 0);
        }
        else
        {
          GenPrintInstr1Operand(instr, 0,
                                GenSelectByteOrWord(I8086OpIndRegBExplicitByteOrWord, v), 0);
          GenPrintInstr2Operands(I8086InstrMov, 0,
                                 I8086OpIndRegB, 0,
                                 GenSelectByteOrWord(I8086OpRegAByteOrWord, v), 0);
        }
        GenExtendRegAIfNeeded(v);
      }
      break;

    case tokAssignDiv:
    case tokAssignUDiv:
    case tokAssignMod:
    case tokAssignUMod:
      GenPrintInstr1Operand(I8086InstrPop, 0,
                            I8086OpRegBWord, 0);
      GenPrintInstr2Operands(I8086InstrMov, 0,
                             I8086OpRegCWord, 0,
                             I8086OpRegAWord, 0);
      GenPrintInstr2Operands(I8086InstrMov, 0,
                             GenSelectByteOrWord(I8086OpRegAByteOrWord, v), 0,
                             I8086OpIndRegB, 0);
      GenExtendRegAIfNeeded(v);
      if (tok == tokAssignDiv || tok == tokAssignMod)
      {
        
        GenPrintInstrNoOperand(I8086InstrCwd);
        GenPrintInstr1Operand(I8086InstrIdiv, 0,
                              I8086OpRegCWord, 0);
      }
      else
      {
        GenPrintInstr2Operands(I8086InstrMov, 0,
                               I8086OpRegDWord, 0,
                               I8086OpConst, 0);
        GenPrintInstr1Operand(I8086InstrDiv, 0,
                              I8086OpRegCWord, 0);
      }
      if (tok == tokAssignMod || tok == tokAssignUMod)
        GenPrintInstr2Operands(I8086InstrMov, 0,
                               I8086OpRegAWord, 0,
                               I8086OpRegDWord, 0);
      GenPrintInstr2Operands(I8086InstrMov, 0,
                             I8086OpIndRegB, 0,
                             GenSelectByteOrWord(I8086OpRegAByteOrWord, v), 0);
      GenExtendRegAIfNeeded(v);
      break;

    case tokAssignLSh:
    case tokAssignRSh:
    case tokAssignURSh:
      {
        int instr = GenGetBinaryOperatorInstr(tok);
        GenPrintInstr1Operand(I8086InstrPop, 0,
                              I8086OpRegBWord, 0);
        GenPrintInstr2Operands(I8086InstrMov, 0,
                               I8086OpRegCWord, 0,
                               I8086OpRegAWord, 0);
        GenPrintInstr2Operands(I8086InstrMov, 0,
                               GenSelectByteOrWord(I8086OpRegAByteOrWord, v), 0,
                               I8086OpIndRegB, 0);
        GenExtendRegAIfNeeded(v);
        GenPrintInstr2Operands(instr, 0,
                               I8086OpRegAWord, 0,
                               I8086OpRegCByte, 0);
        GenPrintInstr2Operands(I8086InstrMov, 0,
                               I8086OpIndRegB, 0,
                               GenSelectByteOrWord(I8086OpRegAByteOrWord, v), 0);
        GenExtendRegAIfNeeded(v);
      }
      break;

    case '=':
      GenPrintInstr1Operand(I8086InstrPop, 0,
                            I8086OpRegBWord, 0);
      GenPrintInstr2Operands(I8086InstrMov, 0,
                             I8086OpIndRegB, 0,
                             GenSelectByteOrWord(I8086OpRegAByteOrWord, v), 0);
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
      GenPrintInstr1Operand(I8086InstrPop, 0,
                            I8086OpRegBWord, 0);
      GenPrintInstr2Operands(I8086InstrCmp, 0,
                             I8086OpRegBWord, 0,
                             I8086OpRegAWord, 0);
      GenPrintInstr1Operand(I8086InstrSetCc, tok,
                            I8086OpRegAByte, 0);
      
      GenPrintInstrNoOperand(I8086InstrCbw);
      break;

    case tok_Bool:
      GenPrintInstr2Operands(I8086InstrTest, 0,
                             I8086OpRegAWord, 0,
                             I8086OpRegAWord, 0);
      GenPrintInstr1Operand(I8086InstrSetCc, tokNEQ,
                            I8086OpRegAByte, 0);
      // fallthrough
    case tokSChar:
      
      GenPrintInstrNoOperand(I8086InstrCbw);
      break;
    case tokUChar:
      GenPrintInstr2Operands(I8086InstrAnd, 0,
                             I8086OpRegAWord, 0,
                             I8086OpConst, 0xFF);
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
    case tokGoto:
#ifndef NO_ANNOTATIONS
      printf2("goto\n");
#endif
      GenJumpUncond(v);
      gotUnary = 0;
      break;
    case tokLogAnd:
    case tokLogOr:
      GenNumLabel(v);
      break;

    case tokVoid:
      gotUnary = 0;
      break;

    case tokComma:
    case ',':
    case '(':
    case tokReturn:
      break;

    case tokIf:
      GenJumpIfNotZero(stack[i][1]);
      break;
    case tokIfNot:
      GenJumpIfZero(stack[i][1]);
      break;

    default:
      //error("Error: Internal Error: GenExpr0(): unexpected token %s\n", GetTokenName(tok));
      errorInternal(105);
      break;
    }
  }
}
#endif // #ifndef CG_STACK_BASED

STATIC
void GenDumpChar(int ch)
{
  static int quot = 0;

  if (ch < 0)
  {
    if (quot)
    {
      printf2("\"");
      quot = 0;
    }
    if (TokenStringLen)
      printf2("\n");
    return;
  }

  if (TokenStringLen == 0)
    GenStartAsciiString();

  // quote ASCII chars for better readability
  if (ch >= 0x20 && ch <= 0x7E && ch != '"')
  {
    if (!quot)
    {
      quot = 1;
      if (TokenStringLen)
        printf2(",");
      printf2("\"");
    }
    printf2("%c", ch);
  }
  else
  {
    if (quot)
    {
      quot = 0;
      printf2("\"");
    }
    if (TokenStringLen)
      printf2(",");
    printf2("%u", ch & 0xFFu);
  }
}

STATIC
void GenExpr(void)
{
  if (GenExterns)
  {
    int i;
    for (i = 0; i < sp; i++)
      if (stack[i][0] == tokIdent && !isdigit(IdentTable[stack[i][1]]))
        GenAddGlobal(IdentTable + stack[i][1], 2);
  }
#ifndef CG_STACK_BASED
  GenExpr1();
#else
  GenExpr0();
#endif
}

STATIC
void GenFin(void)
{
  if (StructCpyLabel)
  {
    puts2(CodeHeaderFooter[0]);

    GenNumLabel(StructCpyLabel);
    CurFxnMinLocalOfs = 0;
    GenFxnProlog();

      puts2("\tmov\tdi, [bp+8]\n"
            "\tmov\tsi, [bp+6]\n"
            "\tmov\tcx, [bp+4]\n"
            "\tcld\n"
            "\trep\tmovsb\n"
            "\tmov\tax, [bp+8]");

    GenFxnEpilog();

    puts2(CodeHeaderFooter[1]);
  }

#ifndef NO_STRUCT_BY_VAL
  if (StructPushLabel)
  {
    puts2(CodeHeaderFooter[0]);

    GenNumLabel(StructPushLabel);
    CurFxnMinLocalOfs = 0;
    GenFxnProlog();

      puts2("\tmov\tdx, [bp+2]\n" // dx = return address
            "\tmov\tsi, [bp+4]\n" // si = &struct
            "\tmov\tcx, [bp+6]\n" // cx = sizeof(struct)
            "\tmov\tbp, [bp]\n"   // restore bp

            "\tmov\tax, cx\n"  // ax = sizeof(struct)
            "\tinc\tax\n"      // ax = sizeof(struct) + 1
            "\tand\tax, -2\n"  // ax = sizeof(struct) rounded up to multiple of 2 bytes
            "\tadd\tsp, 4*2\n" // remove bp, return address and 2 args from stack
            "\tsub\tsp, ax");  // allocate stack space for struct
      
        puts2("\tmov\tdi, sp\n" // di = where struct should be copied to
              "\tcld\n"
              "\trep\tmovsb\n"  // copy

              "\tpop\tax\n"  // return first 2 bytes of struct in ax
              "\tpush\tax\n"
              "\txor\tcx, cx\n" // Set 0 in cx to push (8086 cant push numbers in stack)
              "\tpush\tcx\n"  // caller will remove this 0 and first 2 bytes of struct from stack (as 2 args)
              "\tpush\tdx\n" //   and then it will push ax (first 2 bytes of struct) back
              "\tret");      // actually return to return address saved in dx
     

//    GenFxnEpilog();

    puts2(CodeHeaderFooter[1]);
  }
#endif


  if (GenExterns)
  {
    int i = 0;

    puts2("");
    while (i < GlobalsTableLen)
    {
      if (GlobalsTable[i] == 2)
      {
        printf2("\textern\t");
        GenPrintLabel(GlobalsTable + i + 2);
        puts2("");
      }
      i += GlobalsTable[i + 1] + 2;
    }
  }
}

#ifdef CAN_COMPILE_32BIT

void GenIsrProlog(void)
{
  error("Not supported in this platform");
}

void GenIsrEpilog(void)
{
  error("Not supported in this platform");
}
#endif