/*
Copyright (c) 2012-2014, Alexey Frunze
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
/*                           MIPS code generator                             */
/*                                                                           */
/*****************************************************************************/

// Works around bugs in RetroBSD's as instruction reordering
#define REORDER_WORKAROUND
// Works around bugs in RetroBSD's as immediate operand truncation to 16 bits
//#define INSTR_IMM_WORKAROUND

int UseGp = 0;

void GenInit(void)
{
  // initialization of target-specific code generator
  SizeOfWord = 4;
  OutputFormat = FormatSegmented;
  CodeHeader = "\t.text";
  DataHeader = "\t.data";
  UseLeadingUnderscores = 0;
#ifdef REORDER_WORKAROUND
  FileHeader = "\t.set\tnoreorder";
#else
  FileHeader = "\t.set\treorder";
#endif
}

int GenInitParams(int argc, char** argv, int* idx)
{
  (void)argc;
  // initialization of target-specific code generator with parameters
  if (!strcmp(argv[*idx], "-use-gp"))
  {
    UseGp = 1;
    return 1;
  }
  else if (!strcmp(argv[*idx], "-v"))
  {
    // RetroBSD's cc may supply this parameter. Just need to consume it.
    return 1;
  }

  return 0;
}

void GenInitFinalize(void)
{
  // finalization of initialization of target-specific code generator
}

void GenStartCommentLine(void)
{
  printf2(" # ");
}

void GenWordAlignment(void)
{
  printf2("\t.align 2\n");
}

void GenLabel(char* Label, int Static)
{
  {
    if (OutputFormat != FormatFlat && !Static && GenExterns)
      printf2("\t.globl\t%s\n", Label);
    printf2("%s:\n", Label);
  }
}

void GenPrintLabel(char* Label)
{
  {
    if (isdigit(*Label))
      printf2("$L%s", Label);
    else
      printf2("%s", Label);
  }
}

void GenNumLabel(int Label)
{
  printf2("$L%d:\n", Label);
}

void GenPrintNumLabel(int label)
{
  printf2("$L%d", label);
}

void GenZeroData(unsigned Size)
{
  printf2("\t.space\t%u\n", truncUint(Size)); // or ".fill size"
}

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

void GenStartAsciiString(void)
{
  printf2("\t.ascii\t");
}

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

#define MipsInstrNop    0x00
#define MipsInstrMov    0x01
#define MipsInstrMfLo   0x02
#define MipsInstrMfHi   0x03
//#define MipsInstrMovZ   0x04
//#define MipsInstrMovN   0x05
#define MipsInstrLA     0x06
#define MipsInstrLI     0x07
//#define MipsInstrLUI    0x08
#define MipsInstrLB     0x09
#define MipsInstrLBU    0x0A
#define MipsInstrLH     0x0B
#define MipsInstrLHU    0x0C
#define MipsInstrLW     0x0D
#define MipsInstrSB     0x0E
#define MipsInstrSH     0x0F
#define MipsInstrSW     0x10
#define MipsInstrAddU   0x11
#define MipsInstrSubU   0x12
#define MipsInstrAnd    0x13
#define MipsInstrOr     0x14
#define MipsInstrXor    0x15
#define MipsInstrNor    0x16
#define MipsInstrSLL    0x17
#define MipsInstrSRL    0x18
#define MipsInstrSRA    0x19
#define MipsInstrMul    0x1A
#define MipsInstrDiv    0x1B
#define MipsInstrDivU   0x1C
#define MipsInstrSLT    0x1D
#define MipsInstrSLTU   0x1E
#define MipsInstrJ      0x1F
#define MipsInstrJAL    0x20
#define MipsInstrBEQ    0x21
#define MipsInstrBNE    0x22
//#define MipsInstrBLTZ   0x23
//#define MipsInstrBGEZ   0x24
//#define MipsInstrBLEZ   0x25
//#define MipsInstrBGTZ   0x26
//#define MipsInstrBreak  0x27

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
//  case MipsInstrMovZ : p = "movz"; break;
//  case MipsInstrMovN : p = "movn"; break;
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
//  case MipsInstrBLTZ : p = "bltz"; break;
//  case MipsInstrBGEZ : p = "bgez"; break;
//  case MipsInstrBLEZ : p = "blez"; break;
//  case MipsInstrBGTZ : p = "bgtz"; break;
//  case MipsInstrBreak: p = "break"; break;
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
#define MipsOpLabelGpOption              0x83
#define MipsOpIndLocal                   MipsOpIndRegFp

#ifdef REORDER_WORKAROUND
void GenNop(void)
{
  puts2("\tnop");
}
#endif

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
    case MipsOpLabelGpOption:
      if (UseGp)
      {
        printf2("%%gp_rel(");
        GenPrintLabel(IdentTable + val);
        printf2(")($28)");
      }
      else
      {
        printf2("%%lo(");
        GenPrintLabel(IdentTable + val);
        printf2(")($1)");
      }
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
}

void GenPrintInstr3Operands(int instr, int instrval,
                            int operand1, int operand1val,
                            int operand2, int operand2val,
                            int operand3, int operand3val)
{
#ifdef INSTR_IMM_WORKAROUND
  int useAt = 0;
#endif

  if (operand3 == MipsOpConst && operand3val == 0 &&
      (instr == MipsInstrAddU || instr == MipsInstrSubU))
    return;

#ifdef INSTR_IMM_WORKAROUND
  if (operand3 == MipsOpConst)
  {
    unsigned imm = truncUint(operand3val);

    switch (instr)
    {
    // signed imm16:
    //   addi[u], subi[u], slti[u]
    case MipsInstrAddU:
    case MipsInstrSLT:
    case MipsInstrSLTU:
      if (imm > 0x7FFF && imm < 0xFFFF8000) // if not (-0x8000 <= imm <= 0x7FFF)
        useAt = 1;
      break;
    case MipsInstrSubU:
      // subi[u] will be transformed into addi[u] and the immediate will be negated,
      // hence the immediate range is shifted by 1
      if (imm > 0x8000 && imm < 0xFFFF8001) // if not (-0x7FFF <= imm <= 0x8000)
        useAt = 1;
      break;

    // unsigned imm16:
    //   andi, ori, xori
    case MipsInstrAnd:
    case MipsInstrOr:
    case MipsInstrXor:
      if (imm > 0xFFFF)
        useAt = 1;
      break;

    // also: various trap instructions
    default:
      break;
    }
  }

  if (useAt)
  {
    puts2("\t.set\tnoat");
    GenPrintInstr2Operands(MipsInstrLI, 0,
                           MipsOpRegAt, 0,
                           MipsOpConst, operand3val);
    operand3 = MipsOpRegAt;
  }
#endif

  GenPrintInstr(instr, instrval);
  GenPrintOperand(operand1, operand1val);
  GenPrintOperandSeparator();
  GenPrintOperand(operand2, operand2val);
  GenPrintOperandSeparator();
  GenPrintOperand(operand3, operand3val);
  GenPrintNewLine();

#ifdef INSTR_IMM_WORKAROUND
  if (useAt)
  {
    puts2("\t.set\tat");
  }
#endif

#ifdef REORDER_WORKAROUND
  if (instr == MipsInstrBEQ || instr == MipsInstrBNE)
    GenNop();
#endif
}

void GenExtendRegIfNeeded(int reg, int opSz)
{
  if (opSz == -1)
  {
    GenPrintInstr3Operands(MipsInstrSLL, 0,
                           reg, 0,
                           reg, 0,
                           MipsOpConst, 24);
    GenPrintInstr3Operands(MipsInstrSRA, 0,
                           reg, 0,
                           reg, 0,
                           MipsOpConst, 24);
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
    GenPrintInstr3Operands(MipsInstrSLL, 0,
                           reg, 0,
                           reg, 0,
                           MipsOpConst, 16);
    GenPrintInstr3Operands(MipsInstrSRA, 0,
                           reg, 0,
                           reg, 0,
                           MipsOpConst, 16);
  }
  else if (opSz == 2)
  {
    GenPrintInstr3Operands(MipsInstrAnd, 0,
                           reg, 0,
                           reg, 0,
                           MipsOpConst, 0xFFFF);
  }
}

void GenJumpUncond(int label)
{
  GenPrintInstr1Operand(MipsInstrJ, 0,
                        MipsOpNumLabel, label);
}

void GenJumpIfNotEqual(int val, int label)
{
  GenPrintInstr2Operands(MipsInstrLI, 0,
                         MipsOpRegT1, 0,
                         MipsOpConst, val);
  GenPrintInstr3Operands(MipsInstrBNE, 0,
                         MipsOpRegV0, 0,
                         MipsOpRegT1, 0,
                         MipsOpNumLabel, label);
}

void GenJumpIfZero(int label)
{
#ifndef NO_ANNOTATIONS
  printf2(" # JumpIfZero\n");
#endif
  GenPrintInstr3Operands(MipsInstrBEQ, 0,
                         MipsOpRegV0, 0,
                         MipsOpRegZero, 0,
                         MipsOpNumLabel, label);
}

void GenJumpIfNotZero(int label)
{
#ifndef NO_ANNOTATIONS
  printf2(" # JumpIfNotZero\n");
#endif
  GenPrintInstr3Operands(MipsInstrBNE, 0,
                         MipsOpRegV0, 0,
                         MipsOpRegZero, 0,
                         MipsOpNumLabel, label);
}

void GenFxnProlog(void)
{
  GenPrintInstr3Operands(MipsInstrSubU, 0,
                         MipsOpRegSp, 0,
                         MipsOpRegSp, 0,
                         MipsOpConst, 8);

  GenPrintInstr2Operands(MipsInstrSW, 0,
                         MipsOpRegRa, 0,
                         MipsOpIndRegSp, 4);

  GenPrintInstr2Operands(MipsInstrSW, 0,
                         MipsOpRegFp, 0,
                         MipsOpIndRegSp, 0);

  GenPrintInstr2Operands(MipsInstrMov, 0,
                         MipsOpRegFp, 0,
                         MipsOpRegSp, 0);

  if (CurFxnParamCntMax)
  {
    int i, cnt = CurFxnParamCntMax;
    if (cnt > 4)
      cnt = 4;
    for (i = 0; i < cnt; i++)
      GenPrintInstr2Operands(MipsInstrSW, 0,
                             MipsOpRegA0 + i, 0,
                             MipsOpIndRegFp, 8 + 4 * i);
  }
}

void GenLocalAlloc(int size)
{
  GenPrintInstr3Operands(MipsInstrSubU, 0,
                         MipsOpRegSp, 0,
                         MipsOpRegSp, 0,
                         MipsOpConst, size);
}

void GenFxnEpilog(void)
{
  GenPrintInstr2Operands(MipsInstrMov, 0,
                         MipsOpRegSp, 0,
                         MipsOpRegFp, 0);

  GenPrintInstr2Operands(MipsInstrLW, 0,
                         MipsOpRegFp, 0,
                         MipsOpIndRegSp, 0);

  GenPrintInstr2Operands(MipsInstrLW, 0,
                         MipsOpRegRa, 0,
                         MipsOpIndRegSp, 4);

  GenPrintInstr3Operands(MipsInstrAddU, 0,
                         MipsOpRegSp, 0,
                         MipsOpRegSp, 0,
                         MipsOpConst, 8);

  GenPrintInstr1Operand(MipsInstrJ, 0,
                        MipsOpRegRa, 0);
}

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

void GenPreIdentAccess(int label)
{
  if (UseGp)
    return;
  printf2("\t.set\tnoat\n\tlui\t$1, %%hi(");
  GenPrintLabel(IdentTable + label);
  puts2(")");
}

void GenPostIdentAccess(void)
{
  if (UseGp)
    return;
  puts2("\t.set\tat");
}

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
                         MipsOpLabelGpOption, label);
  GenPostIdentAccess();
}

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
                         MipsOpLabelGpOption, label);
  GenPostIdentAccess();
}

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

void GenPushReg(int reg)
{
  if (CanUseTempRegs && TempsUsed < 6)
  {
    GenPrintInstr2Operands(MipsInstrMov, 0,
                           MipsOpRegT2 + TempsUsed, 0,
                           reg, 0);
    TempsUsed++;
    return;
  }

  GenPrintInstr3Operands(MipsInstrSubU, 0,
                         MipsOpRegSp, 0,
                         MipsOpRegSp, 0,
                         MipsOpConst, 4);

  GenPrintInstr2Operands(MipsInstrSW, 0,
                         reg, 0,
                         MipsOpIndRegSp, 0);

  TempsUsed++;
}

int GenPopReg(int reg)
{
  TempsUsed--;

  if (CanUseTempRegs && TempsUsed < 6)
  {
    return MipsOpRegT2 + TempsUsed;
  }

  GenPrintInstr2Operands(MipsInstrLW, 0,
                         reg, 0,
                         MipsOpIndRegSp, 0);

  GenPrintInstr3Operands(MipsInstrAddU, 0,
                         MipsOpRegSp, 0,
                         MipsOpRegSp, 0,
                         MipsOpConst, 4);
  return reg;
}

// Original, primitive stack-based code generator
// DONE: test 32-bit code generation
void GenExpr0(void)
{
  int i;
  int gotUnary = 0;
  int maxCallDepth = 0;
  int callDepth = 0;
  int paramOfs = 0;

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

  for (i = 0; i < sp; i++)
  {
    int tok = stack[i][0];
    int v = stack[i][1];

#ifndef NO_ANNOTATIONS
    switch (tok)
    {
    case tokNumInt: printf2(" # %d\n", truncInt(v)); break;
    case tokNumUint: printf2(" # %uu\n", truncUint(v)); break;
    case tokIdent: printf2(" # %s\n", IdentTable + v); break;
    case tokLocalOfs: printf2(" # local ofs\n"); break;
    case ')': printf2(" # ) fxn call\n"); break;
    case tokUnaryStar: printf2(" # * (read dereference)\n"); break;
    case '=': printf2(" # = (write dereference)\n"); break;
    case tokShortCirc: printf2(" # short-circuit "); break;
    case tokGoto: printf2(" # sh-circ-goto "); break;
    case tokLogAnd: printf2(" # short-circuit && target\n"); break;
    case tokLogOr: printf2(" # short-circuit || target\n"); break;
    case tokIf: case tokIfNot: break;
    default: printf2(" # %s\n", GetTokenName(tok)); break;
    }
#endif

    switch (tok)
    {
    case tokNumInt:
    case tokNumUint:
      if (!(i + 1 < sp && (strchr("+-&^|", stack[i + 1][0]) ||
                           stack[i + 1][0] == tokLShift ||
                           stack[i + 1][0] == tokRShift ||
                           stack[i + 1][0] == tokURShift)))
      {
        if (gotUnary)
          GenPushReg(MipsOpRegV0);

        GenPrintInstr2Operands(MipsInstrLI, 0,
                               MipsOpRegV0, 0,
                               MipsOpConst, v);
      }
      gotUnary = 1;
      break;

    case tokIdent:
      if (gotUnary)
        GenPushReg(MipsOpRegV0);
      if (!(i + 1 < sp && (stack[i + 1][0] == ')' ||
                           stack[i + 1][0] == tokUnaryStar ||
                           stack[i + 1][0] == tokInc ||
                           stack[i + 1][0] == tokDec ||
                           stack[i + 1][0] == tokPostInc ||
                           stack[i + 1][0] == tokPostDec)))
      {
        GenPrintInstr2Operands(MipsInstrLA, 0,
                               MipsOpRegV0, 0,
                               MipsOpLabel, v);
      }
      gotUnary = 1;
      break;

    case tokLocalOfs:
      if (gotUnary)
        GenPushReg(MipsOpRegV0);
      if (!(i + 1 < sp && (stack[i + 1][0] == tokUnaryStar ||
                           stack[i + 1][0] == tokInc ||
                           stack[i + 1][0] == tokDec ||
                           stack[i + 1][0] == tokPostInc ||
                           stack[i + 1][0] == tokPostDec)))
      {
        GenPrintInstr3Operands(MipsInstrAddU, 0,
                               MipsOpRegV0, 0,
                               MipsOpRegFp, 0,
                               MipsOpConst, v);
      }
      gotUnary = 1;
      break;

    case '(':
      if (gotUnary)
        GenPushReg(MipsOpRegV0);
      gotUnary = 0;
      if (v < 16)
        GenLocalAlloc(16 - v);
      paramOfs = v - 4;
      break;

    case ',':
      if (maxCallDepth == 1)
      {
        if (paramOfs == 16)
        {
          GenPushReg(MipsOpRegV0);
          gotUnary = 0;
        }
        if (paramOfs >= 0 && paramOfs <= 12)
        {
          GenPrintInstr2Operands(MipsInstrMov, 0,
                                 MipsOpRegA0 + paramOfs / 4, 0,
                                 MipsOpRegV0, 0);
          gotUnary = 0;
        }
        paramOfs -= 4;
      }
      break;

    case ')':
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
        int vv = v;
        if (vv > 16)
          vv = 16;
        if (vv)
          GenLocalAlloc(vv);
      }
      if (stack[i - 1][0] == tokIdent)
      {
        GenPrintInstr1Operand(MipsInstrJAL, 0,
                              MipsOpLabel, stack[i - 1][1]);
      }
      else
      {
        GenPrintInstr1Operand(MipsInstrJAL, 0,
                              MipsOpRegV0, 0);
      }
      if (v < 16)
        v = 16;
      GenLocalAlloc(-v);
      break;

    case tokUnaryStar:
      if (stack[i - 1][0] == tokIdent)
        GenReadIdent(MipsOpRegV0, v, stack[i - 1][1]);
      else if (stack[i - 1][0] == tokLocalOfs)
        GenReadLocal(MipsOpRegV0, v, stack[i - 1][1]);
      else
        GenReadIndirect(MipsOpRegV0, MipsOpRegV0, v);
      break;

    case tokUnaryPlus:
      break;
    case '~':
      GenPrintInstr3Operands(MipsInstrNor, 0,
                             MipsOpRegV0, 0,
                             MipsOpRegV0, 0,
                             MipsOpRegV0, 0);
      break;
    case tokUnaryMinus:
      GenPrintInstr3Operands(MipsInstrSubU, 0,
                             MipsOpRegV0, 0,
                             MipsOpRegZero, 0,
                             MipsOpRegV0, 0);
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
      if ((stack[i - 1][0] == tokNumInt || stack[i - 1][0] == tokNumUint) && tok != '*')
      {
        int instr = GenGetBinaryOperatorInstr(tok);
        GenPrintInstr3Operands(instr, 0,
                               MipsOpRegV0, 0,
                               MipsOpRegV0, 0,
                               MipsOpConst, stack[i - 1][1]);
      }
      else
      {
        int instr = GenGetBinaryOperatorInstr(tok);
        int reg = GenPopReg(MipsOpRegT0);
        GenPrintInstr3Operands(instr, 0,
                               MipsOpRegV0, 0,
                               reg, 0,
                               MipsOpRegV0, 0);
      }
      break;

    case '/':
    case tokUDiv:
    case '%':
    case tokUMod:
      {
        int reg = GenPopReg(MipsOpRegT0);
        if (tok == '/' || tok == '%')
          GenPrintInstr3Operands(MipsInstrDiv, 0,
                                 MipsOpRegZero, 0,
                                 reg, 0,
                                 MipsOpRegV0, 0);
        else
          GenPrintInstr3Operands(MipsInstrDivU, 0,
                                 MipsOpRegZero, 0,
                                 reg, 0,
                                 MipsOpRegV0, 0);
        if (tok == '%' || tok == tokUMod)
          GenPrintInstr1Operand(MipsInstrMfHi, 0,
                                MipsOpRegV0, 0);
        else
          GenPrintInstr1Operand(MipsInstrMfLo, 0,
                                MipsOpRegV0, 0);
      }
      break;

    case tokInc:
    case tokDec:
      if (stack[i - 1][0] == tokIdent)
      {
        GenIncDecIdent(MipsOpRegV0, v, stack[i - 1][1], tok);
      }
      else if (stack[i - 1][0] == tokLocalOfs)
      {
        GenIncDecLocal(MipsOpRegV0, v, stack[i - 1][1], tok);
      }
      else
      {
        GenPrintInstr2Operands(MipsInstrMov, 0,
                               MipsOpRegT0, 0,
                               MipsOpRegV0, 0);
        GenIncDecIndirect(MipsOpRegV0, MipsOpRegT0, v, tok);
      }
      break;
    case tokPostInc:
    case tokPostDec:
      if (stack[i - 1][0] == tokIdent)
      {
        GenPostIncDecIdent(MipsOpRegV0, v, stack[i - 1][1], tok);
      }
      else if (stack[i - 1][0] == tokLocalOfs)
      {
        GenPostIncDecLocal(MipsOpRegV0, v, stack[i - 1][1], tok);
      }
      else
      {
        GenPrintInstr2Operands(MipsInstrMov, 0,
                               MipsOpRegT0, 0,
                               MipsOpRegV0, 0);
        GenPostIncDecIndirect(MipsOpRegV0, MipsOpRegT0, v, tok);
      }
      break;

    case tokPostAdd:
    case tokPostSub:
      {
        int instr = GenGetBinaryOperatorInstr(tok);
        int reg = GenPopReg(MipsOpRegT0);
        GenPrintInstr2Operands(MipsInstrMov, 0,
                               MipsOpRegT1, 0,
                               MipsOpRegV0, 0);

        GenReadIndirect(MipsOpRegV0, reg, v);
        GenPrintInstr3Operands(instr, 0,
                               MipsOpRegT1, 0,
                               MipsOpRegV0, 0,
                               MipsOpRegT1, 0);
        GenWriteIndirect(reg, MipsOpRegT1, v);
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
      {
        int instr = GenGetBinaryOperatorInstr(tok);
        int reg = GenPopReg(MipsOpRegT0);
        GenPrintInstr2Operands(MipsInstrMov, 0,
                               MipsOpRegT1, 0,
                               MipsOpRegV0, 0);

        GenReadIndirect(MipsOpRegV0, reg, v);
        GenPrintInstr3Operands(instr, 0,
                               MipsOpRegV0, 0,
                               MipsOpRegV0, 0,
                               MipsOpRegT1, 0);
        GenWriteIndirect(reg, MipsOpRegV0, v);

        GenExtendRegIfNeeded(MipsOpRegV0, v);
      }
      break;

    case tokAssignDiv:
    case tokAssignUDiv:
    case tokAssignMod:
    case tokAssignUMod:
      {
        int reg = GenPopReg(MipsOpRegT0);

        GenReadIndirect(MipsOpRegT1, reg, v);
        if (tok == tokAssignDiv || tok == tokAssignMod)
          GenPrintInstr3Operands(MipsInstrDiv, 0,
                                 MipsOpRegZero, 0,
                                 MipsOpRegT1, 0,
                                 MipsOpRegV0, 0);
        else
          GenPrintInstr3Operands(MipsInstrDivU, 0,
                                 MipsOpRegZero, 0,
                                 MipsOpRegT1, 0,
                                 MipsOpRegV0, 0);
        if (tok == tokAssignMod || tok == tokAssignUMod)
          GenPrintInstr1Operand(MipsInstrMfHi, 0,
                                MipsOpRegV0, 0);
        else
          GenPrintInstr1Operand(MipsInstrMfLo, 0,
                                MipsOpRegV0, 0);
        GenWriteIndirect(reg, MipsOpRegV0, v);

        GenExtendRegIfNeeded(MipsOpRegV0, v);
      }
      break;

    case '=':
      {
        int reg = GenPopReg(MipsOpRegT0);
        GenWriteIndirect(reg, MipsOpRegV0, v);
        GenExtendRegIfNeeded(MipsOpRegV0, v);
      }
      break;

/*
  i = il < ir;  // i = slt(il, ir);
  i = il <= ir; // i = slt(ir, il) ^ 1;
  i = il > ir;  // i = slt(ir, il);
  i = il >= ir; // i = slt(il, ir) ^ 1;
  i = il == ir; // i = sltu(il ^ ir, 1);
  i = il != ir; // i = sltu(0, il ^ ir);
*/
    case '<':
      {
        int reg = GenPopReg(MipsOpRegT0);
        GenPrintInstr3Operands(MipsInstrSLT, 0,
                               MipsOpRegV0, 0,
                               reg, 0,
                               MipsOpRegV0, 0);
      }
      break;
    case tokULess:
      {
        int reg = GenPopReg(MipsOpRegT0);
        GenPrintInstr3Operands(MipsInstrSLTU, 0,
                               MipsOpRegV0, 0,
                               reg, 0,
                               MipsOpRegV0, 0);
      }
      break;
    case '>':
      {
        int reg = GenPopReg(MipsOpRegT0);
        GenPrintInstr3Operands(MipsInstrSLT, 0,
                               MipsOpRegV0, 0,
                               MipsOpRegV0, 0,
                               reg, 0);
      }
      break;
    case tokUGreater:
      {
        int reg = GenPopReg(MipsOpRegT0);
        GenPrintInstr3Operands(MipsInstrSLTU, 0,
                               MipsOpRegV0, 0,
                               MipsOpRegV0, 0,
                               reg, 0);
      }
      break;
    case tokLEQ:
      {
        int reg = GenPopReg(MipsOpRegT0);
        GenPrintInstr3Operands(MipsInstrSLT, 0,
                               MipsOpRegV0, 0,
                               MipsOpRegV0, 0,
                               reg, 0);
        GenPrintInstr3Operands(MipsInstrXor, 0,
                               MipsOpRegV0, 0,
                               MipsOpRegV0, 0,
                               MipsOpConst, 1);
      }
      break;
    case tokULEQ:
      {
        int reg = GenPopReg(MipsOpRegT0);
        GenPrintInstr3Operands(MipsInstrSLTU, 0,
                               MipsOpRegV0, 0,
                               MipsOpRegV0, 0,
                               reg, 0);
        GenPrintInstr3Operands(MipsInstrXor, 0,
                               MipsOpRegV0, 0,
                               MipsOpRegV0, 0,
                               MipsOpConst, 1);
      }
      break;
    case tokGEQ:
      {
        int reg = GenPopReg(MipsOpRegT0);
        GenPrintInstr3Operands(MipsInstrSLT, 0,
                               MipsOpRegV0, 0,
                               reg, 0,
                               MipsOpRegV0, 0);
        GenPrintInstr3Operands(MipsInstrXor, 0,
                               MipsOpRegV0, 0,
                               MipsOpRegV0, 0,
                               MipsOpConst, 1);
      }
      break;
    case tokUGEQ:
      {
        int reg = GenPopReg(MipsOpRegT0);
        GenPrintInstr3Operands(MipsInstrSLTU, 0,
                               MipsOpRegV0, 0,
                               reg, 0,
                               MipsOpRegV0, 0);
        GenPrintInstr3Operands(MipsInstrXor, 0,
                               MipsOpRegV0, 0,
                               MipsOpRegV0, 0,
                               MipsOpConst, 1);
      }
      break;
    case tokEQ:
      {
        int reg = GenPopReg(MipsOpRegT0);
        GenPrintInstr3Operands(MipsInstrXor, 0,
                               MipsOpRegV0, 0,
                               reg, 0,
                               MipsOpRegV0, 0);
        GenPrintInstr3Operands(MipsInstrSLTU, 0,
                               MipsOpRegV0, 0,
                               MipsOpRegV0, 0,
                               MipsOpConst, 1);
      }
      break;
    case tokNEQ:
      {
        int reg = GenPopReg(MipsOpRegT0);
        GenPrintInstr3Operands(MipsInstrXor, 0,
                               MipsOpRegV0, 0,
                               reg, 0,
                               MipsOpRegV0, 0);
        GenPrintInstr3Operands(MipsInstrSLTU, 0,
                               MipsOpRegV0, 0,
                               MipsOpRegZero, 0,
                               MipsOpRegV0, 0);
      }
      break;

    case tok_Bool:
      GenPrintInstr3Operands(MipsInstrSLTU, 0,
                             MipsOpRegV0, 0,
                             MipsOpRegZero, 0,
                             MipsOpRegV0, 0);
      break;

    case tokSChar:
      GenPrintInstr3Operands(MipsInstrSLL, 0,
                             MipsOpRegV0, 0,
                             MipsOpRegV0, 0,
                             MipsOpConst, 24);
      GenPrintInstr3Operands(MipsInstrSRA, 0,
                             MipsOpRegV0, 0,
                             MipsOpRegV0, 0,
                             MipsOpConst, 24);
      break;
    case tokUChar:
      GenPrintInstr3Operands(MipsInstrAnd, 0,
                             MipsOpRegV0, 0,
                             MipsOpRegV0, 0,
                             MipsOpConst, 0xFF);
      break;
    case tokShort:
      GenPrintInstr3Operands(MipsInstrSLL, 0,
                             MipsOpRegV0, 0,
                             MipsOpRegV0, 0,
                             MipsOpConst, 16);
      GenPrintInstr3Operands(MipsInstrSRA, 0,
                             MipsOpRegV0, 0,
                             MipsOpRegV0, 0,
                             MipsOpConst, 16);
      break;
    case tokUShort:
      GenPrintInstr3Operands(MipsInstrAnd, 0,
                             MipsOpRegV0, 0,
                             MipsOpRegV0, 0,
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

    case tokComma:
      break;

    case tokIf:
      GenJumpIfNotZero(stack[i][1]);
      break;
    case tokIfNot:
      GenJumpIfZero(stack[i][1]);
      break;

    default:
      //error("Error: Internal Error: GenExpr0(): unexpected token %s\n", GetTokenName(tok));
      errorInternal(102);
      break;
    }
  }
}

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
      unsigned len;

      p = FindString(label);
      len = *p++ & 0xFF;

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
      printf2("\"");
      while (len--)
      {
        // quote ASCII chars for better readability
        if (*p >= 0x20 && *p <= 0x7E)
        {
          if (*p == '\"' || *p == '\\')
            printf2("\\");
          printf2("%c", *p);
        }
        else
        {
          printf2("\\%03o", *p & 0xFFu);
        }
        p++;
      }
      while (requiredLen)
      {
        printf2("\\000");
        requiredLen--;
      }
      printf2("\"");
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
  GenExpr0();
}

void GenFin(void)
{
  if (StructCpyLabel)
  {
    char s[1 + 2 + (2 + CHAR_BIT * sizeof StructCpyLabel) / 3];
    char *p = s + sizeof s;
    int lbl = LabelCnt++;

    *--p = '\0';
    p = lab2str(p, StructCpyLabel);
    *--p = '_';
    *--p = '_';

    if (OutputFormat != FormatFlat)
      puts2(CodeHeader);

    GenLabel(p, 1);

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

    if (OutputFormat != FormatFlat)
      puts2(CodeFooter);
  }
}
