/*
Copyright (c) 2012-2015, Alexey Frunze
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
/*                           MIPS code generator                             */
/*                                                                           */
/*****************************************************************************/

// Works around bugs in RetroBSD's as instruction reordering
//#define REORDER_WORKAROUND

STATIC
void GenInit(void)
{
  // initialization of target-specific code generator
  SizeOfWord = 4;
  OutputFormat = FormatSegmented;
  CodeHeaderFooter[0] = "\t.text";
  DataHeaderFooter[0] = "\t.data";
  RoDataHeaderFooter[0] = "\t.rdata";
  BssHeaderFooter[0] = "\t.bss";
  UseLeadingUnderscores = 0;
#ifdef REORDER_WORKAROUND
  FileHeader = "\t.set\tnoreorder";
#else
  FileHeader = "\t.set\treorder";
#endif
}

STATIC
int GenInitParams(int argc, char** argv, int* idx)
{
  (void)argc;
  // initialization of target-specific code generator with parameters
  if (!strcmp(argv[*idx], "-v"))
  {
    // RetroBSD's cc may supply this parameter. Just need to consume it.
    return 1;
  }

  return 0;
}

STATIC
void GenInitFinalize(void)
{
  // finalization of initialization of target-specific code generator
}

STATIC
void GenStartCommentLine(void)
{
  printf2(" # ");
}

STATIC
void GenWordAlignment(int bss)
{
  (void)bss;
  printf2("\t.align 2\n");
}

STATIC
void GenLabel(char* Label, int Static)
{
  {
    if (!Static && GenExterns)
      printf2("\t.globl\t%s\n", Label);
    printf2("%s:\n", Label);
  }
}

STATIC
void GenPrintLabel(char* Label)
{
  {
    if (isdigit(*Label))
      printf2("$L%s", Label);
    else
      printf2("%s", Label);
  }
}

STATIC
void GenNumLabel(int Label)
{
  printf2("$L%d:\n", Label);
}

STATIC
void GenPrintNumLabel(int label)
{
  printf2("$L%d", label);
}

STATIC
void GenZeroData(unsigned Size, int bss)
{
  (void)bss;
  printf2("\t.space\t%u\n", truncUint(Size)); // or ".fill size"
}

STATIC
void GenIntData(int Size, int Val)
{
  Val = truncInt(Val);
  if (Size == 1)
    printf2("\t.byte\t%d\n", Val);
  else if (Size == 2)
    printf2("\t.half\t%d\n", Val);
  else if (Size == 4)
    printf2("\t.word\t%d\n", Val);
}

STATIC
void GenStartAsciiString(void)
{
  printf2("\t.ascii\t");
}

STATIC
void GenAddrData(int Size, char* Label, int ofs)
{
  ofs = truncInt(ofs);
  if (Size == 1)
    printf2("\t.byte\t");
  else if (Size == 2)
    printf2("\t.half\t");
  else if (Size == 4)
    printf2("\t.word\t");
  GenPrintLabel(Label);
  if (ofs)
    printf2(" %+d", ofs);
  puts2("");
}

STATIC
int GenFxnSizeNeeded(void)
{
  return 0;
}

STATIC
void GenRecordFxnSize(char* startLabelName, int endLabelNo)
{
  (void)startLabelName;
  (void)endLabelNo;
}

#define MipsInstrNop    0x00
#define MipsInstrMov    0x01
#define MipsInstrMfLo   0x02
#define MipsInstrMfHi   0x03
#define MipsInstrLA     0x06
#define MipsInstrLI     0x07
//#define MipsInstrLUI
#define MipsInstrLB     0x08
#define MipsInstrLBU    0x09
#define MipsInstrLH     0x0A
#define MipsInstrLHU    0x0B
#define MipsInstrLW     0x0C
#define MipsInstrSB     0x0D
#define MipsInstrSH     0x0E
#define MipsInstrSW     0x0F
#define MipsInstrAddU   0x10
#define MipsInstrSubU   0x11
#define MipsInstrAnd    0x12
#define MipsInstrOr     0x13
#define MipsInstrXor    0x14
#define MipsInstrNor    0x15
#define MipsInstrSLL    0x16
#define MipsInstrSRL    0x17
#define MipsInstrSRA    0x18
#define MipsInstrMul    0x19
#define MipsInstrDiv    0x1A
#define MipsInstrDivU   0x1B
#define MipsInstrSLT    0x1C
#define MipsInstrSLTU   0x1D
#define MipsInstrJ      0x1E
#define MipsInstrJAL    0x1F
#define MipsInstrBEQ    0x20
#define MipsInstrBNE    0x21
#define MipsInstrBLTZ   0x22
#define MipsInstrBGEZ   0x23
#define MipsInstrBLEZ   0x24
#define MipsInstrBGTZ   0x25
#define MipsInstrSeb    0x26
#define MipsInstrSeh    0x27

STATIC
void GenPrintInstr(int instr, int val)
{
  char* p = "";

  (void)val;

  switch (instr)
  {
  case MipsInstrNop  : p = "nop"; break;
  case MipsInstrMov  : p = "move"; break;
  case MipsInstrMfLo : p = "mflo"; break;
  case MipsInstrMfHi : p = "mfhi"; break;
  case MipsInstrLA   : p = "la"; break;
  case MipsInstrLI   : p = "li"; break;
//  case MipsInstrLUI  : p = "lui"; break;
  case MipsInstrLB   : p = "lb"; break;
  case MipsInstrLBU  : p = "lbu"; break;
  case MipsInstrLH   : p = "lh"; break;
  case MipsInstrLHU  : p = "lhu"; break;
  case MipsInstrLW   : p = "lw"; break;
  case MipsInstrSB   : p = "sb"; break;
  case MipsInstrSH   : p = "sh"; break;
  case MipsInstrSW   : p = "sw"; break;
  case MipsInstrAddU : p = "addu"; break;
  case MipsInstrSubU : p = "subu"; break;
  case MipsInstrAnd  : p = "and"; break;
  case MipsInstrOr   : p = "or"; break;
  case MipsInstrXor  : p = "xor"; break;
  case MipsInstrNor  : p = "nor"; break;
  case MipsInstrSLL  : p = "sll"; break;
  case MipsInstrSRL  : p = "srl"; break;
  case MipsInstrSRA  : p = "sra"; break;
  case MipsInstrMul  : p = "mul"; break;
  case MipsInstrDiv  : p = "div"; break;
  case MipsInstrDivU : p = "divu"; break;
  case MipsInstrSLT  : p = "slt"; break;
  case MipsInstrSLTU : p = "sltu"; break;
  case MipsInstrJ    : p = "j"; break;
  case MipsInstrJAL  : p = "jal"; break;
  case MipsInstrBEQ  : p = "beq"; break;
  case MipsInstrBNE  : p = "bne"; break;
  case MipsInstrBLTZ : p = "bltz"; break;
  case MipsInstrBGEZ : p = "bgez"; break;
  case MipsInstrBLEZ : p = "blez"; break;
  case MipsInstrBGTZ : p = "bgtz"; break;
  case MipsInstrSeb  : p = "seb"; break;
  case MipsInstrSeh  : p = "seh"; break;
  }

  printf2("\t%s\t", p);
}

#define MipsOpRegZero                    0x00
#define MipsOpRegAt                      0x01
#define MipsOpRegV0                      0x02
#define MipsOpRegV1                      0x03
#define MipsOpRegA0                      0x04
#define MipsOpRegA1                      0x05
#define MipsOpRegA2                      0x06
#define MipsOpRegA3                      0x07
#define MipsOpRegT0                      0x08
#define MipsOpRegT1                      0x09
#define MipsOpRegT2                      0x0A
#define MipsOpRegT3                      0x0B
#define MipsOpRegT4                      0x0C
#define MipsOpRegT5                      0x0D
#define MipsOpRegT6                      0x0E
#define MipsOpRegT7                      0x0F
#define MipsOpRegS0                      0x10
#define MipsOpRegS1                      0x11
#define MipsOpRegS2                      0x12
#define MipsOpRegS3                      0x13
#define MipsOpRegS4                      0x14
#define MipsOpRegS5                      0x15
#define MipsOpRegS6                      0x16
#define MipsOpRegS7                      0x17
#define MipsOpRegT8                      0x18
#define MipsOpRegT9                      0x19
#define MipsOpRegSp                      0x1D
#define MipsOpRegFp                      0x1E
#define MipsOpRegRa                      0x1F

#define MipsOpIndRegZero                 0x20
#define MipsOpIndRegAt                   0x21
#define MipsOpIndRegV0                   0x22
#define MipsOpIndRegV1                   0x23
#define MipsOpIndRegA0                   0x24
#define MipsOpIndRegA1                   0x25
#define MipsOpIndRegA2                   0x26
#define MipsOpIndRegA3                   0x27
#define MipsOpIndRegT0                   0x28
#define MipsOpIndRegT1                   0x29
#define MipsOpIndRegSp                   0x3D
#define MipsOpIndRegFp                   0x3E
#define MipsOpIndRegRa                   0x3F

#define MipsOpConst                      0x80
#define MipsOpLabel                      0x81
#define MipsOpNumLabel                   0x82
#define MipsOpLabelLo                    0x83
#define MipsOpIndLocal                   MipsOpIndRegFp

#define MAX_TEMP_REGS 8 // this many temp registers used beginning with T0 to hold subexpression results
#define TEMP_REG_A MipsOpRegT8 // two temporary registers used for momentary operations, similarly to the AT register
#define TEMP_REG_B MipsOpRegT9

#ifdef REORDER_WORKAROUND
STATIC
void GenNop(void)
{
  puts2("\tnop");
}
#endif

STATIC
void GenPrintOperand(int op, int val)
{
  if (op >= MipsOpRegZero && op <= MipsOpRegRa)
  {
    printf2("$%d", op);
  }
  else if (op >= MipsOpIndRegZero && op <= MipsOpIndRegRa)
  {
    printf2("%d($%d)", truncInt(val), op - MipsOpIndRegZero);
  }
  else
  {
    switch (op)
    {
    case MipsOpConst: printf2("%d", truncInt(val)); break;
    case MipsOpLabelLo:
      printf2("%%lo(");
      GenPrintLabel(IdentTable + val);
      printf2(")($1)");
      break;
    case MipsOpLabel: GenPrintLabel(IdentTable + val); break;
    case MipsOpNumLabel: GenPrintNumLabel(val); break;

    default:
      //error("WTF!\n");
      errorInternal(100);
      break;
    }
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
void GenPrintInstr1Operand(int instr, int instrval, int operand, int operandval)
{
  GenPrintInstr(instr, instrval);
  GenPrintOperand(operand, operandval);
  GenPrintNewLine();

#ifdef REORDER_WORKAROUND
  if (instr == MipsInstrJ || instr == MipsInstrJAL)
    GenNop();
#endif
}

STATIC
void GenPrintInstr2Operands(int instr, int instrval, int operand1, int operand1val, int operand2, int operand2val)
{
  if (operand2 == MipsOpConst && operand2val == 0 &&
      (instr == MipsInstrAddU || instr == MipsInstrSubU))
    return;

  GenPrintInstr(instr, instrval);
  GenPrintOperand(operand1, operand1val);
  GenPrintOperandSeparator();
  GenPrintOperand(operand2, operand2val);
  GenPrintNewLine();
#ifdef REORDER_WORKAROUND
  if (instr == MipsInstrBLTZ || instr == MipsInstrBGEZ ||
      instr == MipsInstrBGTZ || instr == MipsInstrBLEZ)
    GenNop();
#endif
}

STATIC
void GenPrintInstr3Operands(int instr, int instrval,
                            int operand1, int operand1val,
                            int operand2, int operand2val,
                            int operand3, int operand3val)
{
  if (operand3 == MipsOpConst && operand3val == 0 &&
      (instr == MipsInstrAddU || instr == MipsInstrSubU) &&
      operand1 == operand2)
    return;

  GenPrintInstr(instr, instrval);
  GenPrintOperand(operand1, operand1val);
  GenPrintOperandSeparator();
  GenPrintOperand(operand2, operand2val);
  GenPrintOperandSeparator();
  GenPrintOperand(operand3, operand3val);
  GenPrintNewLine();

#ifdef REORDER_WORKAROUND
  if (instr == MipsInstrBEQ || instr == MipsInstrBNE)
    GenNop();
#endif
}

STATIC
void GenExtendRegIfNeeded(int reg, int opSz)
{
  if (opSz == -1)
  {
#ifdef DONT_USE_SEH
    GenPrintInstr3Operands(MipsInstrSLL, 0,
                           reg, 0,
                           reg, 0,
                           MipsOpConst, 24);
    GenPrintInstr3Operands(MipsInstrSRA, 0,
                           reg, 0,
                           reg, 0,
                           MipsOpConst, 24);
#else
    GenPrintInstr2Operands(MipsInstrSeb, 0,
                           reg, 0,
                           reg, 0);
#endif
  }
  else if (opSz == 1)
  {
    GenPrintInstr3Operands(MipsInstrAnd, 0,
                           reg, 0,
                           reg, 0,
                           MipsOpConst, 0xFF);
  }
  else if (opSz == -2)
  {
#ifdef DONT_USE_SEH
    GenPrintInstr3Operands(MipsInstrSLL, 0,
                           reg, 0,
                           reg, 0,
                           MipsOpConst, 16);
    GenPrintInstr3Operands(MipsInstrSRA, 0,
                           reg, 0,
                           reg, 0,
                           MipsOpConst, 16);
#else
    GenPrintInstr2Operands(MipsInstrSeh, 0,
                           reg, 0,
                           reg, 0);
#endif
  }
  else if (opSz == 2)
  {
    GenPrintInstr3Operands(MipsInstrAnd, 0,
                           reg, 0,
                           reg, 0,
                           MipsOpConst, 0xFFFF);
  }
}

STATIC
void GenJumpUncond(int label)
{
  GenPrintInstr1Operand(MipsInstrJ, 0,
                        MipsOpNumLabel, label);
}

extern int GenWreg; // GenWreg is defined below

STATIC
void GenJumpIfEqual(int val, int label)
{
  GenPrintInstr2Operands(MipsInstrLI, 0,
                         TEMP_REG_B, 0,
                         MipsOpConst, val);
  GenPrintInstr3Operands(MipsInstrBEQ, 0,
                         GenWreg, 0,
                         TEMP_REG_B, 0,
                         MipsOpNumLabel, label);
}

STATIC
void GenJumpIfZero(int label)
{
#ifndef NO_ANNOTATIONS
  printf2(" # JumpIfZero\n");
#endif
  GenPrintInstr3Operands(MipsInstrBEQ, 0,
                         GenWreg, 0,
                         MipsOpRegZero, 0,
                         MipsOpNumLabel, label);
}

STATIC
void GenJumpIfNotZero(int label)
{
#ifndef NO_ANNOTATIONS
  printf2(" # JumpIfNotZero\n");
#endif
  GenPrintInstr3Operands(MipsInstrBNE, 0,
                         GenWreg, 0,
                         MipsOpRegZero, 0,
                         MipsOpNumLabel, label);
}

fpos_t GenPrologPos;
int GenLeaf;

STATIC
void GenWriteFrameSize(void)
{
  unsigned size = 8/*RA + FP*/ - CurFxnMinLocalOfs;
  printf2("\tsubu\t$29, $29, %10u\n", size); // 10 chars are enough for 32-bit unsigned ints
  printf2("\tsw\t$30, %10u($29)\n", size - 8);
  printf2("\taddu\t$30, $29, %10u\n", size - 8);
  printf2("\t%csw\t$31, 4($30)\n", GenLeaf ? '#' : ' ');
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
  if (CurFxnParamCntMin && CurFxnParamCntMax)
  {
    int i, cnt = CurFxnParamCntMax;
    if (cnt > 4)
      cnt = 4;
    // TBD!!! for structure passing use the cumulative parameter size
    // instead of the number of parameters. Currently this bug is masked
    // by the subroutine that pushes structures on the stack (it copies
    // all words except the first to the stack). But passing structures
    // in registers from assembly code won't always work.
    for (i = 0; i < cnt; i++)
      GenPrintInstr2Operands(MipsInstrSW, 0,
                             MipsOpRegA0 + i, 0,
                             MipsOpIndRegSp, 4 * i);
  }

  GenLeaf = 1; // will be reset to 0 if a call is generated

  fgetpos(OutFile, &GenPrologPos);
  GenWriteFrameSize();
}

STATIC
void GenGrowStack(int size)
{
  if (!size)
    return;
  GenPrintInstr3Operands(MipsInstrSubU, 0,
                         MipsOpRegSp, 0,
                         MipsOpRegSp, 0,
                         MipsOpConst, size);
}

STATIC
void GenFxnEpilog(void)
{
  GenUpdateFrameSize();

  if (!GenLeaf)
    GenPrintInstr2Operands(MipsInstrLW, 0,
                           MipsOpRegRa, 0,
                           MipsOpIndRegFp, 4);

  GenPrintInstr2Operands(MipsInstrLW, 0,
                         MipsOpRegFp, 0,
                         MipsOpIndRegFp, 0);

  GenPrintInstr3Operands(MipsInstrAddU, 0,
                         MipsOpRegSp, 0,
                         MipsOpRegSp, 0,
                         MipsOpConst, 8/*RA + FP*/ - CurFxnMinLocalOfs);

  GenPrintInstr1Operand(MipsInstrJ, 0,
                        MipsOpRegRa, 0);
}

STATIC
int GenMaxLocalsSize(void)
{
  return 0x7FFFFFFF;
}

STATIC
int GenGetBinaryOperatorInstr(int tok)
{
  switch (tok)
  {
  case tokPostAdd:
  case tokAssignAdd:
  case '+':
    return MipsInstrAddU;
  case tokPostSub:
  case tokAssignSub:
  case '-':
    return MipsInstrSubU;
  case '&':
  case tokAssignAnd:
    return MipsInstrAnd;
  case '^':
  case tokAssignXor:
    return MipsInstrXor;
  case '|':
  case tokAssignOr:
    return MipsInstrOr;
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
    return MipsInstrNop;
  case '*':
  case tokAssignMul:
    return MipsInstrMul;
  case '/':
  case '%':
  case tokAssignDiv:
  case tokAssignMod:
    return MipsInstrDiv;
  case tokUDiv:
  case tokUMod:
  case tokAssignUDiv:
  case tokAssignUMod:
    return MipsInstrDivU;
  case tokLShift:
  case tokAssignLSh:
    return MipsInstrSLL;
  case tokRShift:
  case tokAssignRSh:
    return MipsInstrSRA;
  case tokURShift:
  case tokAssignURSh:
    return MipsInstrSRL;

  default:
    //error("Error: Invalid operator\n");
    errorInternal(101);
    return 0;
  }
}

STATIC
void GenPreIdentAccess(int label)
{
  printf2("\t.set\tnoat\n\tlui\t$1, %%hi(");
  GenPrintLabel(IdentTable + label);
  puts2(")");
}

STATIC
void GenPostIdentAccess(void)
{
  puts2("\t.set\tat");
}

STATIC
void GenReadIdent(int regDst, int opSz, int label)
{
  int instr = MipsInstrLW;
  GenPreIdentAccess(label);
  if (opSz == -1)
  {
    instr = MipsInstrLB;
  }
  else if (opSz == 1)
  {
    instr = MipsInstrLBU;
  }
  else if (opSz == -2)
  {
    instr = MipsInstrLH;
  }
  else if (opSz == 2)
  {
    instr = MipsInstrLHU;
  }
  GenPrintInstr2Operands(instr, 0,
                         regDst, 0,
                         MipsOpLabelLo, label);
  GenPostIdentAccess();
}

STATIC
void GenReadLocal(int regDst, int opSz, int ofs)
{
  int instr = MipsInstrLW;
  if (opSz == -1)
  {
    instr = MipsInstrLB;
  }
  else if (opSz == 1)
  {
    instr = MipsInstrLBU;
  }
  else if (opSz == -2)
  {
    instr = MipsInstrLH;
  }
  else if (opSz == 2)
  {
    instr = MipsInstrLHU;
  }
  GenPrintInstr2Operands(instr, 0,
                         regDst, 0,
                         MipsOpIndRegFp, ofs);
}

STATIC
void GenReadIndirect(int regDst, int regSrc, int opSz)
{
  int instr = MipsInstrLW;
  if (opSz == -1)
  {
    instr = MipsInstrLB;
  }
  else if (opSz == 1)
  {
    instr = MipsInstrLBU;
  }
  else if (opSz == -2)
  {
    instr = MipsInstrLH;
  }
  else if (opSz == 2)
  {
    instr = MipsInstrLHU;
  }
  GenPrintInstr2Operands(instr, 0,
                         regDst, 0,
                         regSrc + MipsOpIndRegZero, 0);
}

STATIC
void GenWriteIdent(int regSrc, int opSz, int label)
{
  int instr = MipsInstrSW;
  GenPreIdentAccess(label);
  if (opSz == -1 || opSz == 1)
  {
    instr = MipsInstrSB;
  }
  else if (opSz == -2 || opSz == 2)
  {
    instr = MipsInstrSH;
  }
  GenPrintInstr2Operands(instr, 0,
                         regSrc, 0,
                         MipsOpLabelLo, label);
  GenPostIdentAccess();
}

STATIC
void GenWriteLocal(int regSrc, int opSz, int ofs)
{
  int instr = MipsInstrSW;
  if (opSz == -1 || opSz == 1)
  {
    instr = MipsInstrSB;
  }
  else if (opSz == -2 || opSz == 2)
  {
    instr = MipsInstrSH;
  }
  GenPrintInstr2Operands(instr, 0,
                         regSrc, 0,
                         MipsOpIndRegFp, ofs);
}

STATIC
void GenWriteIndirect(int regDst, int regSrc, int opSz)
{
  int instr = MipsInstrSW;
  if (opSz == -1 || opSz == 1)
  {
    instr = MipsInstrSB;
  }
  else if (opSz == -2 || opSz == 2)
  {
    instr = MipsInstrSH;
  }
  GenPrintInstr2Operands(instr, 0,
                         regSrc, 0,
                         regDst + MipsOpIndRegZero, 0);
}

STATIC
void GenIncDecIdent(int regDst, int opSz, int label, int tok)
{
  int instr = MipsInstrAddU;

  if (tok != tokInc)
    instr = MipsInstrSubU;

  GenReadIdent(regDst, opSz, label);
  GenPrintInstr3Operands(instr, 0,
                         regDst, 0,
                         regDst, 0,
                         MipsOpConst, 1);
  GenWriteIdent(regDst, opSz, label);
  GenExtendRegIfNeeded(regDst, opSz);
}

STATIC
void GenIncDecLocal(int regDst, int opSz, int ofs, int tok)
{
  int instr = MipsInstrAddU;

  if (tok != tokInc)
    instr = MipsInstrSubU;

  GenReadLocal(regDst, opSz, ofs);
  GenPrintInstr3Operands(instr, 0,
                         regDst, 0,
                         regDst, 0,
                         MipsOpConst, 1);
  GenWriteLocal(regDst, opSz, ofs);
  GenExtendRegIfNeeded(regDst, opSz);
}

STATIC
void GenIncDecIndirect(int regDst, int regSrc, int opSz, int tok)
{
  int instr = MipsInstrAddU;

  if (tok != tokInc)
    instr = MipsInstrSubU;

  GenReadIndirect(regDst, regSrc, opSz);
  GenPrintInstr3Operands(instr, 0,
                         regDst, 0,
                         regDst, 0,
                         MipsOpConst, 1);
  GenWriteIndirect(regSrc, regDst, opSz);
  GenExtendRegIfNeeded(regDst, opSz);
}

STATIC
void GenPostIncDecIdent(int regDst, int opSz, int label, int tok)
{
  int instr = MipsInstrAddU;

  if (tok != tokPostInc)
    instr = MipsInstrSubU;

  GenReadIdent(regDst, opSz, label);
  GenPrintInstr3Operands(instr, 0,
                         regDst, 0,
                         regDst, 0,
                         MipsOpConst, 1);
  GenWriteIdent(regDst, opSz, label);
  GenPrintInstr3Operands(instr, 0,
                         regDst, 0,
                         regDst, 0,
                         MipsOpConst, -1);
  GenExtendRegIfNeeded(regDst, opSz);
}

STATIC
void GenPostIncDecLocal(int regDst, int opSz, int ofs, int tok)
{
  int instr = MipsInstrAddU;

  if (tok != tokPostInc)
    instr = MipsInstrSubU;

  GenReadLocal(regDst, opSz, ofs);
  GenPrintInstr3Operands(instr, 0,
                         regDst, 0,
                         regDst, 0,
                         MipsOpConst, 1);
  GenWriteLocal(regDst, opSz, ofs);
  GenPrintInstr3Operands(instr, 0,
                         regDst, 0,
                         regDst, 0,
                         MipsOpConst, -1);
  GenExtendRegIfNeeded(regDst, opSz);
}

STATIC
void GenPostIncDecIndirect(int regDst, int regSrc, int opSz, int tok)
{
  int instr = MipsInstrAddU;

  if (tok != tokPostInc)
    instr = MipsInstrSubU;

  GenReadIndirect(regDst, regSrc, opSz);
  GenPrintInstr3Operands(instr, 0,
                         regDst, 0,
                         regDst, 0,
                         MipsOpConst, 1);
  GenWriteIndirect(regSrc, regDst, opSz);
  GenPrintInstr3Operands(instr, 0,
                         regDst, 0,
                         regDst, 0,
                         MipsOpConst, -1);
  GenExtendRegIfNeeded(regDst, opSz);
}

int CanUseTempRegs;
int TempsUsed;
int GenWreg = MipsOpRegV0; // current working register (V0 or Tn or An)
int GenLreg, GenRreg; // left operand register and right operand register after GenPopReg()

/*
  General idea behind GenWreg, GenLreg, GenRreg:

  - In expressions w/o function calls:

    Subexpressions are evaluated in V0, T0, T1, ..., T<MAX_TEMP_REGS-1>. If those registers
    aren't enough, the stack is used additionally.

    The expression result ends up in V0, which is handy for returning from
    functions.

    In the process, GenWreg is the current working register and is one of: V0, T0, T1, ... .
    All unary operators are evaluated in the current working register.

    GenPushReg() and GenPopReg() advance GenWreg as needed when handling binary operators.

    GenPopReg() sets GenWreg, GenLreg and GenRreg. GenLreg and GenRreg are the registers
    where the left and right operands of a binary operator are.

    When the exression runs out of the temporary registers, the stack is used. While it is being
    used, GenWreg remains equal to the last temporary register, and GenPopReg() sets GenLreg = TEMP_REG_A.
    Hence, after GenPopReg() the operands of the binary operator are always in registers and can be
    directly manipulated with.

    Following GenPopReg(), binary operator evaluation must take the left and right operands from
    GenLreg and GenRreg and write the evaluated result into GenWreg. Care must be taken as GenWreg
    will be the same as either GenLreg (when the popped operand comes from T0-T<MAX_TEMP_REGS-1>)
    or GenRreg (when the popped operand comes from the stack in TEMP_REG_A).

  - In expressions with function calls:

    GenWreg is always V0 in subexpressions that aren't function parameters. These subexpressions
    get automatically pushed onto the stack as necessary.

    GenWreg is always V0 in expressions, where return values from function calls are used as parameters
    into other called functions. IOW, this is the case when the function call depth is greater than 1.
    Subexpressions in such expressions get automatically pushed onto the stack as necessary.

    GenWreg is A0-A3 in subexpressions that are function parameters when the function call depth is 1.
    Basically, while a function parameter is evaluated, it's evaluated in the register from where
    the called function will take it. This avoids some of unnecessary register copies and stack
    manipulations in the most simple and very common cases of function calls.
*/

STATIC
void GenWregInc(int inc)
{
  if (inc > 0)
  {
    // Advance the current working register to the next available temporary register
    if (GenWreg == MipsOpRegV0)
      GenWreg = MipsOpRegT0;
    else
      GenWreg++;
  }
  else
  {
    // Return to the previous current working register
    if (GenWreg == MipsOpRegT0)
      GenWreg = MipsOpRegV0;
    else
      GenWreg--;
  }
}

STATIC
void GenPushReg(void)
{
  if (CanUseTempRegs && TempsUsed < MAX_TEMP_REGS)
  {
    GenWregInc(1);
    TempsUsed++;
    return;
  }

  GenPrintInstr3Operands(MipsInstrSubU, 0,
                         MipsOpRegSp, 0,
                         MipsOpRegSp, 0,
                         MipsOpConst, 4);

  GenPrintInstr2Operands(MipsInstrSW, 0,
                         GenWreg, 0,
                         MipsOpIndRegSp, 0);

  TempsUsed++;
}

STATIC
void GenPopReg(void)
{
  TempsUsed--;

  if (CanUseTempRegs && TempsUsed < MAX_TEMP_REGS)
  {
    GenRreg = GenWreg;
    GenWregInc(-1);
    GenLreg = GenWreg;
    return;
  }

  GenPrintInstr2Operands(MipsInstrLW, 0,
                         TEMP_REG_A, 0,
                         MipsOpIndRegSp, 0);

  GenPrintInstr3Operands(MipsInstrAddU, 0,
                         MipsOpRegSp, 0,
                         MipsOpRegSp, 0,
                         MipsOpConst, 4);
  GenLreg = TEMP_REG_A;
  GenRreg = GenWreg;
}

#define tokRevIdent    0x100
#define tokRevLocalOfs 0x101
#define tokAssign0     0x102
#define tokNum0        0x103

STATIC
void GenPrep(int* idx)
{
  int tok;
  int oldIdxRight, oldIdxLeft, t0, t1;

  if (*idx < 0)
    //error("GenFuse(): idx < 0\n");
    errorInternal(100);

  tok = stack[*idx][0];

  oldIdxRight = --*idx;

  switch (tok)
  {
  case tokUDiv:
  case tokUMod:
  case tokAssignUDiv:
  case tokAssignUMod:
    if (stack[oldIdxRight][0] == tokNumInt || stack[oldIdxRight][0] == tokNumUint)
    {
      // Change unsigned division to right shift and unsigned modulo to bitwise and
      unsigned m = truncUint(stack[oldIdxRight][1]);
      if (m && !(m & (m - 1)))
      {
        if (tok == tokUMod || tok == tokAssignUMod)
        {
          stack[oldIdxRight][1] = (int)(m - 1);
          tok = (tok == tokUMod) ? '&' : tokAssignAnd;
        }
        else
        {
          t1 = 0;
          while (m >>= 1) t1++;
          stack[oldIdxRight][1] = t1;
          tok = (tok == tokUDiv) ? tokURShift : tokAssignURSh;
        }
        stack[oldIdxRight + 1][0] = tok;
      }
    }
  }

  switch (tok)
  {
  case tokNumUint:
    stack[oldIdxRight + 1][0] = tokNumInt; // reduce the number of cases since tokNumInt and tokNumUint are handled the same way
    // fallthrough
  case tokNumInt:
  case tokNum0:
  case tokIdent:
  case tokLocalOfs:
    break;

  case tokPostAdd:
  case tokPostSub:
  case '-':
  case '/':
  case '%':
  case tokUDiv:
  case tokUMod:
  case tokLShift:
  case tokRShift:
  case tokURShift:
  case tokLogAnd:
  case tokLogOr:
  case tokComma:
    GenPrep(idx);
    // fallthrough
  case tokShortCirc:
  case tokGoto:
  case tokUnaryStar:
  case tokInc:
  case tokDec:
  case tokPostInc:
  case tokPostDec:
  case '~':
  case tokUnaryPlus:
  case tokUnaryMinus:
  case tok_Bool:
  case tokVoid:
  case tokUChar:
  case tokSChar:
  case tokShort:
  case tokUShort:
    GenPrep(idx);
    break;

  case '=':
    if (oldIdxRight + 1 == sp - 1 &&
        (stack[oldIdxRight][0] == tokNumInt || stack[oldIdxRight][0] == tokNumUint) &&
        truncUint(stack[oldIdxRight][1]) == 0)
    {
      // Special case for assigning 0 while throwing away the expression result value
      // TBD??? ,
      stack[oldIdxRight][0] = tokNum0; // this zero constant will not be loaded into a register
      stack[oldIdxRight + 1][0] = tokAssign0; // change '=' to tokAssign0
    }
    // fallthrough
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
    GenPrep(idx);
    oldIdxLeft = *idx;
    GenPrep(idx);
    // If the left operand is an identifier (with static or auto storage), swap it with the right operand
    // and mark it specially, so it can be used directly
    if ((t0 = stack[oldIdxLeft][0]) == tokIdent || t0 == tokLocalOfs)
    {
      t1 = stack[oldIdxLeft][1];
      memmove(stack[oldIdxLeft], stack[oldIdxLeft + 1], (oldIdxRight - oldIdxLeft) * sizeof(stack[0]));
      stack[oldIdxRight][0] = (t0 == tokIdent) ? tokRevIdent : tokRevLocalOfs;
      stack[oldIdxRight][1] = t1;
    }
    break;

  case '+':
  case '*':
  case '&':
  case '^':
  case '|':
  case tokEQ:
  case tokNEQ:
  case '<':
  case '>':
  case tokLEQ:
  case tokGEQ:
  case tokULess:
  case tokUGreater:
  case tokULEQ:
  case tokUGEQ:
    GenPrep(idx);
    oldIdxLeft = *idx;
    GenPrep(idx);
    // If the right operand isn't a constant, but the left operand is, swap the operands
    // so the constant can become an immediate right operand in the instruction
    t1 = stack[oldIdxRight][0];
    t0 = stack[oldIdxLeft][0];
    if (t1 != tokNumInt && t0 == tokNumInt)
    {
      int xor;

      t1 = stack[oldIdxLeft][1];
      memmove(stack[oldIdxLeft], stack[oldIdxLeft + 1], (oldIdxRight - oldIdxLeft) * sizeof(stack[0]));
      stack[oldIdxRight][0] = t0;
      stack[oldIdxRight][1] = t1;

      switch (tok)
      {
      case '<':
      case '>':
        xor = '<' ^ '>'; break;
      case tokLEQ:
      case tokGEQ:
        xor = tokLEQ ^ tokGEQ; break;
      case tokULess:
      case tokUGreater:
        xor = tokULess ^ tokUGreater; break;
      case tokULEQ:
      case tokUGEQ:
        xor = tokULEQ ^ tokUGEQ; break;
      default:
        xor = 0; break;
      }
      tok ^= xor;
    }
    // Handle a few special cases and transform the instruction
    if (stack[oldIdxRight][0] == tokNumInt)
    {
      unsigned m = truncUint(stack[oldIdxRight][1]);
      switch (tok)
      {
      case '*':
        // Change multiplication to left shift, this helps indexing arrays of ints/pointers/etc
        if (m && !(m & (m - 1)))
        {
          t1 = 0;
          while (m >>= 1) t1++;
          stack[oldIdxRight][1] = t1;
          tok = tokLShift;
        }
        break;
      case tokLEQ:
        // left <= const will later change to left < const+1, but const+1 must be <=0x7FFFFFFF
        if (m == 0x7FFFFFFF)
        {
          // left <= 0x7FFFFFFF is always true, change to the equivalent left >= 0u
          stack[oldIdxRight][1] = 0;
          tok = tokUGEQ;
        }
        break;
      case tokULEQ:
        // left <= const will later change to left < const+1, but const+1 must be <=0xFFFFFFFFu
        if (m == 0xFFFFFFFF)
        {
          // left <= 0xFFFFFFFFu is always true, change to the equivalent left >= 0u
          stack[oldIdxRight][1] = 0;
          tok = tokUGEQ;
        }
        break;
      case '>':
        // left > const will later change to !(left < const+1), but const+1 must be <=0x7FFFFFFF
        if (m == 0x7FFFFFFF)
        {
          // left > 0x7FFFFFFF is always false, change to the equivalent left & 0
          stack[oldIdxRight][1] = 0;
          tok = '&';
        }
        break;
      case tokUGreater:
        // left > const will later change to !(left < const+1), but const+1 must be <=0xFFFFFFFFu
        if (m == 0xFFFFFFFF)
        {
          // left > 0xFFFFFFFFu is always false, change to the equivalent left & 0
          stack[oldIdxRight][1] = 0;
          tok = '&';
        }
        break;
      }
    }
    stack[oldIdxRight + 1][0] = tok;
    break;

  case ')':
    while (stack[*idx][0] != '(')
    {
      GenPrep(idx);
      if (stack[*idx][0] == ',')
        --*idx;
    }
    --*idx;
    break;

  default:
    //error("GenPrep: unexpected token %s\n", GetTokenName(tok));
    errorInternal(101);
  }
}

/*
;     l <[u] 0       // slt[u] w, w, 0                            "k"
      l <[u] const   // slt[u] w, w, const                        "m"
      l <[u] r       // slt[u] w, l, r                            "i"
* if (l <    0)      // bgez w, Lskip                             "f"
  if (l <[u] const)  // slt[u] w, w, const; beq w, $0, Lskip      "mc"
  if (l <[u] r)      // slt[u] w, l, r; beq w, $0, Lskip          "ic"

;     l <=[u] 0      // slt[u] w, w, 1                            "l"
      l <=[u] const  // slt[u] w, w, const + 1                    "n"
      l <=[u] r      // slt[u] w, r, l; xor w, w, 1               "js"
* if (l <=    0)     // bgtz w, Lskip                             "g"
  if (l <=[u] const) // slt[u] w, w, const + 1; beq w, $0, Lskip  "nc"
  if (l <=[u] r)     // slt[u] w, r, l; bne w, $0, Lskip          "jd"

      l >[u] 0       // slt[u] w, $0, w                           "o"
      l >[u] const   // slt[u] w, w, const + 1; xor w, w, 1       "ns"
      l >[u] r       // slt[u] w, r, l                            "j"
* if (l >    0)      // blez w, Lskip                             "h"
**if (l >u   0)      // beq w, $0, Lskip
  if (l >[u] const)  // slt[u] w, w, const + 1; bne w, $0, Lskip  "nd"
  if (l >[u] r)      // slt[u] w, r, l; beq w, $0, Lskip          "jc"

;     l >=[u] 0      // slt[u] w, w, 0; xor w, w, 1               "ks"
      l >=[u] const  // slt[u] w, w, const; xor w, w, 1           "ms"
      l >=[u] r      // slt[u] w, l, r; xor w, w, 1               "is"
* if (l >=    0)     // bltz w, Lskip                             "e"
  if (l >=[u] const) // slt[u] w, w, const; bne w, $0, Lskip      "md"
  if (l >=[u] r)     // slt[u] w, l, r; bne w, $0, Lskip          "id"

      l == 0         // sltu w, w, 1                              "q"
      l == const     // xor w, w, const; sltu w, w, 1             "tq"
      l == r         // xor w, l, r; sltu w, w, 1                 "rq"
  if (l == 0)        // bne w, $0, Lskip                          "d"
  if (l == const)    // xor w, w, const; bne w, $0, Lskip         "td"
  if (l == r)        // bne l, r, Lskip                           "b"

      l != 0         // sltu w, $0, w                             "p"
      l != const     // xor w, w, const; sltu w, $0, w            "tp"
      l != r         // xor w, l, r; sltu w, $0, w                "rp"
  if (l != 0)        // beq w, $0, Lskip                          "c"
  if (l != const)    // xor w, w, const; beq w, $0, Lskip         "tc"
  if (l != r)        // beq l, r, Lskip                           "a"
*/
char CmpBlocks[6/*op*/][2/*condbranch*/][3/*constness*/][2] =
{
  {
    { "k", "m", "i" },
    { "f", "mc", "ic" }
  },
  {
    { "l", "n", "js" },
    { "g", "nc", "jd" }
  },
  {
    { "o", "ns", "j" },
    { "h", "nd", "jc" }
  },
  {
    { "ks", "ms", "is" },
    { "e", "md", "id" }
  },
  {
    { "q", "tq", "rq" },
    { "d", "td", "b" }
  },
  {
    { "p", "tp", "rp" },
    { "c", "tc", "a" }
  }
};

STATIC
void GenCmp(int* idx, int op)
{
  // constness: 0 = zero const, 1 = non-zero const, 2 = non-const
  int constness = (stack[*idx - 1][0] == tokNumInt) ? (stack[*idx - 1][1] != 0) : 2;
  int constval = (constness == 1) ? truncInt(stack[*idx - 1][1]) : 0;
  // condbranch: 0 = no conditional branch, 1 = branch if true, 2 = branch if false
  int condbranch = (*idx + 1 < sp) ? (stack[*idx + 1][0] == tokIf) + (stack[*idx + 1][0] == tokIfNot) * 2 : 0;
  int unsign = op >> 4;
  int slt = unsign ? MipsInstrSLTU : MipsInstrSLT;
  int label = condbranch ? stack[*idx + 1][1] : 0;
  char* p;
  int i;

  op &= 0xF;
  if (constness == 2)
    GenPopReg();

  // bltz, blez, bgez, bgtz are for signed comparison with 0 only,
  // so for conditional branches on <0u, <=0u, >0u, >=0u use the general method instead
  if (condbranch && op < 4 && constness == 0 && unsign)
  {
    // Except, >0u is more optimal as !=0
    if (op == 2)
      op = 5;
    else
      constness = 1;
  }

  p = CmpBlocks[op][condbranch != 0][constness];

  for (i = 0; i < 2; i++)
  {
    switch (p[i])
    {
    case 'a':
      condbranch ^= 3;
      // fallthrough
    case 'b':
      GenPrintInstr3Operands((condbranch == 1) ? MipsInstrBEQ : MipsInstrBNE, 0,
                             GenLreg, 0,
                             GenRreg, 0,
                             MipsOpNumLabel, label);
      break;
    case 'c':
      condbranch ^= 3;
      // fallthrough
    case 'd':
      GenPrintInstr3Operands((condbranch == 1) ? MipsInstrBEQ : MipsInstrBNE, 0,
                             GenWreg, 0,
                             MipsOpRegZero, 0,
                             MipsOpNumLabel, label);
      break;
    case 'e':
      condbranch ^= 3;
      // fallthrough
    case 'f':
      GenPrintInstr2Operands((condbranch == 1) ? MipsInstrBLTZ : MipsInstrBGEZ, 0,
                             GenWreg, 0,
                             MipsOpNumLabel, label);
      break;
    case 'g':
      condbranch ^= 3;
      // fallthrough
    case 'h':
      GenPrintInstr2Operands((condbranch == 1) ? MipsInstrBGTZ : MipsInstrBLEZ, 0,
                             GenWreg, 0,
                             MipsOpNumLabel, label);
      break;
    case 'i':
      GenPrintInstr3Operands(slt, 0,
                             GenWreg, 0,
                             GenLreg, 0,
                             GenRreg, 0);
      break;
    case 'j':
      GenPrintInstr3Operands(slt, 0,
                             GenWreg, 0,
                             GenRreg, 0,
                             GenLreg, 0);
      break;
    case 'k':
      GenPrintInstr3Operands(slt, 0,
                             GenWreg, 0,
                             GenWreg, 0,
                             MipsOpRegZero, 0);
      break;
    case 'l':
      GenPrintInstr3Operands(slt, 0,
                             GenWreg, 0,
                             GenWreg, 0,
                             MipsOpConst, 1);
      break;
    case 'n':
      constval++;
      // fallthrough
    case 'm':
      GenPrintInstr3Operands(slt, 0,
                             GenWreg, 0,
                             GenWreg, 0,
                             MipsOpConst, constval);
      break;
    case 'o':
      GenPrintInstr3Operands(slt, 0,
                             GenWreg, 0,
                             MipsOpRegZero, 0,
                             GenWreg, 0);
      break;
    case 'p':
      GenPrintInstr3Operands(MipsInstrSLTU, 0,
                             GenWreg, 0,
                             MipsOpRegZero, 0,
                             GenWreg, 0);
      break;
    case 'q':
      GenPrintInstr3Operands(MipsInstrSLTU, 0,
                             GenWreg, 0,
                             GenWreg, 0,
                             MipsOpConst, 1);
      break;
    case 'r':
      GenPrintInstr3Operands(MipsInstrXor, 0,
                             GenWreg, 0,
                             GenLreg, 0,
                             GenRreg, 0);
      break;
    case 's':
      GenPrintInstr3Operands(MipsInstrXor, 0,
                             GenWreg, 0,
                             GenWreg, 0,
                             MipsOpConst, 1);
      break;
    case 't':
      GenPrintInstr3Operands(MipsInstrXor, 0,
                             GenWreg, 0,
                             GenWreg, 0,
                             MipsOpConst, constval);
      break;
    }
  }

  *idx += condbranch != 0;
}

STATIC
int GenIsCmp(int t)
{
  return
    t == '<' ||
    t == '>' ||
    t == tokGEQ ||
    t == tokLEQ ||
    t == tokULess ||
    t == tokUGreater ||
    t == tokUGEQ ||
    t == tokULEQ ||
    t == tokEQ ||
    t == tokNEQ;
}

// Improved register/stack-based code generator
// DONE: test 32-bit code generation
STATIC
void GenExpr0(void)
{
  int i;
  int gotUnary = 0;
  int maxCallDepth = 0;
  int callDepth = 0;
  int paramOfs = 0;
  int t = sp - 1;

  if (stack[t][0] == tokIf || stack[t][0] == tokIfNot || stack[t][0] == tokReturn)
    t--;
  GenPrep(&t);

  for (i = 0; i < sp; i++)
    if (stack[i][0] == '(')
    {
      if (++callDepth > maxCallDepth)
        maxCallDepth = callDepth;
    }
    else if (stack[i][0] == ')')
    {
      callDepth--;
    }

  CanUseTempRegs = maxCallDepth == 0;
  TempsUsed = 0;
  if (GenWreg != MipsOpRegV0)
    errorInternal(102);

  for (i = 0; i < sp; i++)
  {
    int tok = stack[i][0];
    int v = stack[i][1];

#ifndef NO_ANNOTATIONS
    switch (tok)
    {
    case tokNumInt: printf2(" # %d\n", truncInt(v)); break;
    //case tokNumUint: printf2(" # %uu\n", truncUint(v)); break;
    case tokIdent: case tokRevIdent: printf2(" # %s\n", IdentTable + v); break;
    case tokLocalOfs: case tokRevLocalOfs: printf2(" # local ofs\n"); break;
    case ')': printf2(" # ) fxn call\n"); break;
    case tokUnaryStar: printf2(" # * (read dereference)\n"); break;
    case '=': printf2(" # = (write dereference)\n"); break;
    case tokShortCirc: printf2(" # short-circuit "); break;
    case tokGoto: printf2(" # sh-circ-goto "); break;
    case tokLogAnd: printf2(" # short-circuit && target\n"); break;
    case tokLogOr: printf2(" # short-circuit || target\n"); break;
    case tokIf: case tokIfNot: case tokReturn: break;
    case tokNum0: printf2(" # 0\n"); break;
    case tokAssign0:  printf2(" # =\n"); break;
    default: printf2(" # %s\n", GetTokenName(tok)); break;
    }
#endif

    switch (tok)
    {
    case tokNumInt:
      if (!(i + 1 < sp && ((t = stack[i + 1][0]) == '+' ||
                           t == '-' ||
                           t == '&' ||
                           t == '^' ||
                           t == '|' ||
                           t == tokLShift ||
                           t == tokRShift ||
                           t == tokURShift ||
                           GenIsCmp(t))))
      {
        if (gotUnary)
          GenPushReg();

        GenPrintInstr2Operands(MipsInstrLI, 0,
                               GenWreg, 0,
                               MipsOpConst, v);
      }
      gotUnary = 1;
      break;

    case tokIdent:
      if (gotUnary)
        GenPushReg();
      if (!(i + 1 < sp && ((t = stack[i + 1][0]) == ')' ||
                           t == tokUnaryStar ||
                           t == tokInc ||
                           t == tokDec ||
                           t == tokPostInc ||
                           t == tokPostDec)))
      {
        GenPrintInstr2Operands(MipsInstrLA, 0,
                               GenWreg, 0,
                               MipsOpLabel, v);
      }
      gotUnary = 1;
      break;

    case tokLocalOfs:
      if (gotUnary)
        GenPushReg();
      if (!(i + 1 < sp && ((t = stack[i + 1][0]) == tokUnaryStar ||
                           t == tokInc ||
                           t == tokDec ||
                           t == tokPostInc ||
                           t == tokPostDec)))
      {
        GenPrintInstr3Operands(MipsInstrAddU, 0,
                               GenWreg, 0,
                               MipsOpRegFp, 0,
                               MipsOpConst, v);
      }
      gotUnary = 1;
      break;

    case '(':
      if (gotUnary)
        GenPushReg();
      gotUnary = 0;
      if (maxCallDepth != 1 && v < 16)
        GenGrowStack(16 - v);
      paramOfs = v - 4;
      if (maxCallDepth == 1 && paramOfs >= 0 && paramOfs <= 12)
      {
        // Work directly in A0-A3 instead of working in V0 and avoid copying V0 to A0-A3
        GenWreg = MipsOpRegA0 + paramOfs / 4;
      }
      break;

    case ',':
      if (maxCallDepth == 1)
      {
        if (paramOfs == 16)
        {
          // Got the last on-stack parameter, the rest will go in A0-A3
          GenPushReg();
          gotUnary = 0;
          GenWreg = MipsOpRegA3;
        }
        if (paramOfs >= 0 && paramOfs <= 12)
        {
          // Advance to the next An reg or revert to V0
          if (paramOfs)
            GenWreg--;
          else
            GenWreg = MipsOpRegV0;
          gotUnary = 0;
        }
        paramOfs -= 4;
      }
      break;

    case ')':
      GenLeaf = 0;
      if (maxCallDepth != 1)
      {
        if (v >= 4)
          GenPrintInstr2Operands(MipsInstrLW, 0,
                                 MipsOpRegA0, 0,
                                 MipsOpIndRegSp, 0);
        if (v >= 8)
          GenPrintInstr2Operands(MipsInstrLW, 0,
                                 MipsOpRegA1, 0,
                                 MipsOpIndRegSp, 4);
        if (v >= 12)
          GenPrintInstr2Operands(MipsInstrLW, 0,
                                 MipsOpRegA2, 0,
                                 MipsOpIndRegSp, 8);
        if (v >= 16)
          GenPrintInstr2Operands(MipsInstrLW, 0,
                                 MipsOpRegA3, 0,
                                 MipsOpIndRegSp, 12);
      }
      else
      {
        GenGrowStack(16);
      }
      if (stack[i - 1][0] == tokIdent)
      {
        GenPrintInstr1Operand(MipsInstrJAL, 0,
                              MipsOpLabel, stack[i - 1][1]);
      }
      else
      {
        GenPrintInstr1Operand(MipsInstrJAL, 0,
                              GenWreg, 0);
      }
      if (v < 16)
        v = 16;
      GenGrowStack(-v);
      break;

    case tokUnaryStar:
      if (stack[i - 1][0] == tokIdent)
        GenReadIdent(GenWreg, v, stack[i - 1][1]);
      else if (stack[i - 1][0] == tokLocalOfs)
        GenReadLocal(GenWreg, v, stack[i - 1][1]);
      else
        GenReadIndirect(GenWreg, GenWreg, v);
      break;

    case tokUnaryPlus:
      break;
    case '~':
      GenPrintInstr3Operands(MipsInstrNor, 0,
                             GenWreg, 0,
                             GenWreg, 0,
                             GenWreg, 0);
      break;
    case tokUnaryMinus:
      GenPrintInstr3Operands(MipsInstrSubU, 0,
                             GenWreg, 0,
                             MipsOpRegZero, 0,
                             GenWreg, 0);
      break;

    case '+':
    case '-':
    case '*':
    case '&':
    case '^':
    case '|':
    case tokLShift:
    case tokRShift:
    case tokURShift:
      if (stack[i - 1][0] == tokNumInt && tok != '*')
      {
        int instr = GenGetBinaryOperatorInstr(tok);
        GenPrintInstr3Operands(instr, 0,
                               GenWreg, 0,
                               GenWreg, 0,
                               MipsOpConst, stack[i - 1][1]);
      }
      else
      {
        int instr = GenGetBinaryOperatorInstr(tok);
        GenPopReg();
        GenPrintInstr3Operands(instr, 0,
                               GenWreg, 0,
                               GenLreg, 0,
                               GenRreg, 0);
      }
      break;

    case '/':
    case tokUDiv:
    case '%':
    case tokUMod:
      {
        GenPopReg();
        if (tok == '/' || tok == '%')
          GenPrintInstr3Operands(MipsInstrDiv, 0,
                                 MipsOpRegZero, 0,
                                 GenLreg, 0,
                                 GenRreg, 0);
        else
          GenPrintInstr3Operands(MipsInstrDivU, 0,
                                 MipsOpRegZero, 0,
                                 GenLreg, 0,
                                 GenRreg, 0);
        if (tok == '%' || tok == tokUMod)
          GenPrintInstr1Operand(MipsInstrMfHi, 0,
                                GenWreg, 0);
        else
          GenPrintInstr1Operand(MipsInstrMfLo, 0,
                                GenWreg, 0);
      }
      break;

    case tokInc:
    case tokDec:
      if (stack[i - 1][0] == tokIdent)
      {
        GenIncDecIdent(GenWreg, v, stack[i - 1][1], tok);
      }
      else if (stack[i - 1][0] == tokLocalOfs)
      {
        GenIncDecLocal(GenWreg, v, stack[i - 1][1], tok);
      }
      else
      {
        GenPrintInstr2Operands(MipsInstrMov, 0,
                               TEMP_REG_A, 0,
                               GenWreg, 0);
        GenIncDecIndirect(GenWreg, TEMP_REG_A, v, tok);
      }
      break;
    case tokPostInc:
    case tokPostDec:
      if (stack[i - 1][0] == tokIdent)
      {
        GenPostIncDecIdent(GenWreg, v, stack[i - 1][1], tok);
      }
      else if (stack[i - 1][0] == tokLocalOfs)
      {
        GenPostIncDecLocal(GenWreg, v, stack[i - 1][1], tok);
      }
      else
      {
        GenPrintInstr2Operands(MipsInstrMov, 0,
                               TEMP_REG_A, 0,
                               GenWreg, 0);
        GenPostIncDecIndirect(GenWreg, TEMP_REG_A, v, tok);
      }
      break;

    case tokPostAdd:
    case tokPostSub:
      {
        int instr = GenGetBinaryOperatorInstr(tok);
        GenPopReg();
        if (GenWreg == GenLreg)
        {
          GenPrintInstr2Operands(MipsInstrMov, 0,
                                 TEMP_REG_B, 0,
                                 GenLreg, 0);

          GenReadIndirect(GenWreg, TEMP_REG_B, v);
          GenPrintInstr3Operands(instr, 0,
                                 TEMP_REG_A, 0,
                                 GenWreg, 0,
                                 GenRreg, 0);
          GenWriteIndirect(TEMP_REG_B, TEMP_REG_A, v);
        }
        else
        {
          // GenWreg == GenRreg here
          GenPrintInstr2Operands(MipsInstrMov, 0,
                                 TEMP_REG_B, 0,
                                 GenRreg, 0);

          GenReadIndirect(GenWreg, GenLreg, v);
          GenPrintInstr3Operands(instr, 0,
                                 TEMP_REG_B, 0,
                                 GenWreg, 0,
                                 TEMP_REG_B, 0);
          GenWriteIndirect(GenLreg, TEMP_REG_B, v);
        }
      }
      break;

    case tokAssignAdd:
    case tokAssignSub:
    case tokAssignMul:
    case tokAssignAnd:
    case tokAssignXor:
    case tokAssignOr:
    case tokAssignLSh:
    case tokAssignRSh:
    case tokAssignURSh:
      if (stack[i - 1][0] == tokRevLocalOfs || stack[i - 1][0] == tokRevIdent)
      {
        int instr = GenGetBinaryOperatorInstr(tok);

        if (stack[i - 1][0] == tokRevLocalOfs)
          GenReadLocal(TEMP_REG_B, v, stack[i - 1][1]);
        else
          GenReadIdent(TEMP_REG_B, v, stack[i - 1][1]);

        GenPrintInstr3Operands(instr, 0,
                               GenWreg, 0,
                               TEMP_REG_B, 0,
                               GenWreg, 0);

        if (stack[i - 1][0] == tokRevLocalOfs)
          GenWriteLocal(GenWreg, v, stack[i - 1][1]);
        else
          GenWriteIdent(GenWreg, v, stack[i - 1][1]);
      }
      else
      {
        int instr = GenGetBinaryOperatorInstr(tok);
        int lsaved, rsaved;
        GenPopReg();
        if (GenWreg == GenLreg)
        {
          GenPrintInstr2Operands(MipsInstrMov, 0,
                                 TEMP_REG_B, 0,
                                 GenLreg, 0);
          lsaved = TEMP_REG_B;
          rsaved = GenRreg;
        }
        else
        {
          // GenWreg == GenRreg here
          GenPrintInstr2Operands(MipsInstrMov, 0,
                                 TEMP_REG_B, 0,
                                 GenRreg, 0);
          rsaved = TEMP_REG_B;
          lsaved = GenLreg;
        }

        GenReadIndirect(GenWreg, GenLreg, v); // destroys either GenLreg or GenRreg because GenWreg coincides with one of them
        GenPrintInstr3Operands(instr, 0,
                               GenWreg, 0,
                               GenWreg, 0,
                               rsaved, 0);
        GenWriteIndirect(lsaved, GenWreg, v);
      }
      GenExtendRegIfNeeded(GenWreg, v);
      break;

    case tokAssignDiv:
    case tokAssignUDiv:
    case tokAssignMod:
    case tokAssignUMod:
      if (stack[i - 1][0] == tokRevLocalOfs || stack[i - 1][0] == tokRevIdent)
      {
        if (stack[i - 1][0] == tokRevLocalOfs)
          GenReadLocal(TEMP_REG_B, v, stack[i - 1][1]);
        else
          GenReadIdent(TEMP_REG_B, v, stack[i - 1][1]);

        if (tok == tokAssignDiv || tok == tokAssignMod)
          GenPrintInstr3Operands(MipsInstrDiv, 0,
                                 MipsOpRegZero, 0,
                                 TEMP_REG_B, 0,
                                 GenWreg, 0);
        else
          GenPrintInstr3Operands(MipsInstrDivU, 0,
                                 MipsOpRegZero, 0,
                                 TEMP_REG_B, 0,
                                 GenWreg, 0);
        if (tok == tokAssignMod || tok == tokAssignUMod)
          GenPrintInstr1Operand(MipsInstrMfHi, 0,
                                GenWreg, 0);
        else
          GenPrintInstr1Operand(MipsInstrMfLo, 0,
                                GenWreg, 0);

        if (stack[i - 1][0] == tokRevLocalOfs)
          GenWriteLocal(GenWreg, v, stack[i - 1][1]);
        else
          GenWriteIdent(GenWreg, v, stack[i - 1][1]);
      }
      else
      {
        int lsaved, rsaved;
        GenPopReg();
        if (GenWreg == GenLreg)
        {
          GenPrintInstr2Operands(MipsInstrMov, 0,
                                 TEMP_REG_B, 0,
                                 GenLreg, 0);
          lsaved = TEMP_REG_B;
          rsaved = GenRreg;
        }
        else
        {
          // GenWreg == GenRreg here
          GenPrintInstr2Operands(MipsInstrMov, 0,
                                 TEMP_REG_B, 0,
                                 GenRreg, 0);
          rsaved = TEMP_REG_B;
          lsaved = GenLreg;
        }

        GenReadIndirect(GenWreg, GenLreg, v); // destroys either GenLreg or GenRreg because GenWreg coincides with one of them
        if (tok == tokAssignDiv || tok == tokAssignMod)
          GenPrintInstr3Operands(MipsInstrDiv, 0,
                                 MipsOpRegZero, 0,
                                 GenWreg, 0,
                                 rsaved, 0);
        else
          GenPrintInstr3Operands(MipsInstrDivU, 0,
                                 MipsOpRegZero, 0,
                                 GenWreg, 0,
                                 rsaved, 0);
        if (tok == tokAssignMod || tok == tokAssignUMod)
          GenPrintInstr1Operand(MipsInstrMfHi, 0,
                                GenWreg, 0);
        else
          GenPrintInstr1Operand(MipsInstrMfLo, 0,
                                GenWreg, 0);
        GenWriteIndirect(lsaved, GenWreg, v);
      }
      GenExtendRegIfNeeded(GenWreg, v);
      break;

    case '=':
      if (stack[i - 1][0] == tokRevLocalOfs)
      {
        GenWriteLocal(GenWreg, v, stack[i - 1][1]);
      }
      else if (stack[i - 1][0] == tokRevIdent)
      {
        GenWriteIdent(GenWreg, v, stack[i - 1][1]);
      }
      else
      {
        GenPopReg();
        GenWriteIndirect(GenLreg, GenRreg, v);
        if (GenWreg != GenRreg)
          GenPrintInstr2Operands(MipsInstrMov, 0,
                                 GenWreg, 0,
                                 GenRreg, 0);
      }
      GenExtendRegIfNeeded(GenWreg, v);
      break;

    case tokAssign0: // assignment of 0, while throwing away the expression result value
      if (stack[i - 1][0] == tokRevLocalOfs)
      {
        GenWriteLocal(MipsOpRegZero, v, stack[i - 1][1]);
      }
      else if (stack[i - 1][0] == tokRevIdent)
      {
        GenWriteIdent(MipsOpRegZero, v, stack[i - 1][1]);
      }
      else
      {
        GenWriteIndirect(GenWreg, MipsOpRegZero, v);
      }
      break;

    case '<':         GenCmp(&i, 0x00); break;
    case tokLEQ:      GenCmp(&i, 0x01); break;
    case '>':         GenCmp(&i, 0x02); break;
    case tokGEQ:      GenCmp(&i, 0x03); break;
    case tokULess:    GenCmp(&i, 0x10); break;
    case tokULEQ:     GenCmp(&i, 0x11); break;
    case tokUGreater: GenCmp(&i, 0x12); break;
    case tokUGEQ:     GenCmp(&i, 0x13); break;
    case tokEQ:       GenCmp(&i, 0x04); break;
    case tokNEQ:      GenCmp(&i, 0x05); break;

    case tok_Bool:
      GenPrintInstr3Operands(MipsInstrSLTU, 0,
                             GenWreg, 0,
                             MipsOpRegZero, 0,
                             GenWreg, 0);
      break;

    case tokSChar:
#ifdef DONT_USE_SEH
      GenPrintInstr3Operands(MipsInstrSLL, 0,
                             GenWreg, 0,
                             GenWreg, 0,
                             MipsOpConst, 24);
      GenPrintInstr3Operands(MipsInstrSRA, 0,
                             GenWreg, 0,
                             GenWreg, 0,
                             MipsOpConst, 24);
#else
      GenPrintInstr2Operands(MipsInstrSeb, 0,
                             GenWreg, 0,
                             GenWreg, 0);
#endif
      break;
    case tokUChar:
      GenPrintInstr3Operands(MipsInstrAnd, 0,
                             GenWreg, 0,
                             GenWreg, 0,
                             MipsOpConst, 0xFF);
      break;
    case tokShort:
#ifdef DONT_USE_SEH
      GenPrintInstr3Operands(MipsInstrSLL, 0,
                             GenWreg, 0,
                             GenWreg, 0,
                             MipsOpConst, 16);
      GenPrintInstr3Operands(MipsInstrSRA, 0,
                             GenWreg, 0,
                             GenWreg, 0,
                             MipsOpConst, 16);
#else
      GenPrintInstr2Operands(MipsInstrSeh, 0,
                             GenWreg, 0,
                             GenWreg, 0);
#endif
      break;
    case tokUShort:
      GenPrintInstr3Operands(MipsInstrAnd, 0,
                             GenWreg, 0,
                             GenWreg, 0,
                             MipsOpConst, 0xFFFF);
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

    case tokRevIdent:
    case tokRevLocalOfs:
    case tokComma:
    case tokReturn:
    case tokNum0:
      break;

    case tokIf:
      GenJumpIfNotZero(stack[i][1]);
      break;
    case tokIfNot:
      GenJumpIfZero(stack[i][1]);
      break;

    default:
      //error("Error: Internal Error: GenExpr0(): unexpected token %s\n", GetTokenName(tok));
      errorInternal(103);
      break;
    }
  }

  if (GenWreg != MipsOpRegV0)
    errorInternal(104);
}

STATIC
void GenDumpChar(int ch)
{
  if (ch < 0)
  {
    if (TokenStringLen)
      printf2("\"\n");
    return;
  }

  if (TokenStringLen == 0)
  {
    GenStartAsciiString();
    printf2("\"");
  }

  if (ch >= 0x20 && ch <= 0x7E)
  {
    if (ch == '"' || ch == '\\')
      printf2("\\");
    printf2("%c", ch);
  }
  else
  {
    printf2("\\%03o", ch);
  }
}

STATIC
void GenExpr(void)
{
  GenExpr0();
}

STATIC
void GenFin(void)
{
  if (StructCpyLabel)
  {
    int lbl = LabelCnt++;

    puts2(CodeHeaderFooter[0]);

    GenNumLabel(StructCpyLabel);

    puts2("\tmove\t$2, $6\n"
          "\tmove\t$3, $6");
    GenNumLabel(lbl);
    puts2("\tlbu\t$6, 0($5)\n"
          "\taddiu\t$5, $5, 1\n"
          "\taddiu\t$4, $4, -1\n"
          "\tsb\t$6, 0($3)\n"
          "\taddiu\t$3, $3, 1");
    printf2("\tbne\t$4, $0, "); GenPrintNumLabel(lbl);
    puts2("");
#ifdef REORDER_WORKAROUND
    GenNop();
#endif
    puts2("\tj\t$31");
#ifdef REORDER_WORKAROUND
    GenNop();
#endif

    puts2(CodeHeaderFooter[1]);
  }

#ifndef NO_STRUCT_BY_VAL
  if (StructPushLabel)
  {
    int lbl = LabelCnt++;

    puts2(CodeHeaderFooter[0]);

    GenNumLabel(StructPushLabel);

    puts2("\tmove\t$6, $5\n"
          "\taddiu\t$6, $6, 3\n"
          "\tli\t$3, -4\n"
          "\tand\t$6, $6, $3\n"
          "\tsubu\t$29, $29, $6\n"
          "\taddiu\t$3, $29, 16\n"
          "\tmove\t$2, $3");
    GenNumLabel(lbl);
    puts2("\tlbu\t$6, 0($4)\n"
          "\taddiu\t$4, $4, 1\n"
          "\taddiu\t$5, $5, -1\n"
          "\tsb\t$6, 0($3)\n"
          "\taddiu\t$3, $3, 1");
    printf2("\tbne\t$5, $0, "); GenPrintNumLabel(lbl);
    puts2("");
#ifdef REORDER_WORKAROUND
    GenNop();
#endif
    puts2("\tlw\t$2, 0($2)\n"
          "\taddiu\t$29, $29, 4\n"
          "\tj\t$31");
#ifdef REORDER_WORKAROUND
    GenNop();
#endif

    puts2(CodeHeaderFooter[1]);
  }
#endif
}
