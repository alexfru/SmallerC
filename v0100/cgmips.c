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
/*                           MIPS code generator                             */
/*                                                                           */
/*****************************************************************************/

void GenInit(void)
{
  // initialization of target-specific code generator
  SizeOfWord = 4;
  OutputFormat = FormatSegmented;
  CodeHeader = "\t.text";
  DataHeader = "\t.data";
  UseLeadingUnderscores = 0;
}

int GenInitParams(int argc, char** argv, int* idx)
{
  // initialization of target-specific code generator with parameters
  return 0;
}

void GenInitFinalize(void)
{
  // finalization of initialization of target-specific code generator
}

void GenStartCommentLine(void)
{
  printf(" # ");
}

void GenWordAlignment(void)
{
  printf("\t.p2align 2\n");
}

void GenLabel(char* Label)
{
  {
    if (OutputFormat != FormatFlat)
      printf("\t.global\t%s\n", Label);
    printf("%s:\n", Label);
  }
}

void GenExtern(char* Label)
{
  if (OutputFormat != FormatFlat)
  {
    printf("\t.extern\t%s\n", Label);
  }
}

void GenPrintLabel(char* Label)
{
  {
    if (isdigit(*Label))
      printf("$L%s", Label);
    else
      printf("%s", Label);
  }
}

void GenNumLabel(int Label)
{
  printf("$L%d:\n", Label);
}

void GenPrintNumLabel(int label)
{
  printf("$L%d", label);
}

void GenZeroData(unsigned Size)
{
  printf("\t.fill\t%u\n", truncUint(Size)); // or ".space size"
}

void GenIntData(int Size, int Val)
{
  Val = truncInt(Val);
  if (Size == 1)
    printf("\t.byte\t%d\n", Val);
  else if (Size == 2)
    printf("\t.short\t%d\n", Val);
  else if (Size == 4)
    printf("\t.int\t%d\n", Val);
}

void GenStartAsciiString(void)
{
  printf("\t.ascii\t");
}

void GenAddrData(int Size, char* Label)
{
  if (Size == 1)
    printf("\t.byte\t");
  else if (Size == 2)
    printf("\t.short\t");
  else if (Size == 4)
    printf("\t.int\t");
  GenPrintLabel(Label); puts("");
}

#define MipsInstrNop    0x00
#define MipsInstrMov    0x01
#define MipsInstrMfLo   0x02
#define MipsInstrMfHi   0x03
#define MipsInstrMovZ   0x04
#define MipsInstrMovN   0x05
#define MipsInstrLA     0x06
#define MipsInstrLI     0x07
#define MipsInstrLUI    0x08
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
#define MipsInstrBLTZ   0x23
#define MipsInstrBGEZ   0x24
#define MipsInstrBLEZ   0x25
#define MipsInstrBGTZ   0x26
#define MipsInstrBreak  0x27

void GenPrintInstr(int instr, int val)
{
  char* p = "";

  switch (instr)
  {
  case MipsInstrNop  : p = "nop"; break;
  case MipsInstrMov  : p = "move"; break;
  case MipsInstrMfLo : p = "mflo"; break;
  case MipsInstrMfHi : p = "mfhi"; break;
  case MipsInstrMovZ : p = "movz"; break;
  case MipsInstrMovN : p = "movn"; break;
  case MipsInstrLA   : p = "la"; break;
  case MipsInstrLI   : p = "li"; break;
  case MipsInstrLUI  : p = "lui"; break;
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
  case MipsInstrBreak: p = "break"; break;
  }

  printf("\t%s\t", p);
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
#define MipsOpRegSp                      0x1D
#define MipsOpRegFp                      0x1E
#define MipsOpRegRa                      0x1F

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

#define MipsOpConst                      0x80
#define MipsOpLabel                      0x81
#define MipsOpNumLabel                   0x82
#define MipsOpIndLocal                   MipsOpIndRegFp

void GenPrintOperand(int op, int val)
{
  if (op >= 0x00 && op < 0x20)
  {
    printf("$%d", op);
  }
  else if (op >= 0x20 && op < 0x40)
  {
    printf("%d($%d)", truncInt(val), op - 0x20);
  }
  else
  {
    switch (op)
    {
    case MipsOpConst: printf("%d", truncInt(val)); break;
    case MipsOpLabel: GenPrintLabel(IdentTable + val); break;
    case MipsOpNumLabel: GenPrintNumLabel(val); break;
    default: error("WTF!\n"); break;
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
  GenPrintInstr(MipsInstrJAL, 0);
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
  if (operand3 == MipsOpConst && operand3val == 0 &&
      (instr == MipsInstrAddU || instr == MipsInstrSubU))
    return;

  GenPrintInstr(instr, instrval);
  GenPrintOperand(operand1, operand1val);
  GenPrintOperandSeparator();
  GenPrintOperand(operand2, operand2val);
  GenPrintOperandSeparator();
  GenPrintOperand(operand3, operand3val);
  GenPrintNewLine();
}

void GenExtendRegAIfNeeded(int reg, int opSz)
{
  if (opSz == 1)
  {
    if (CharIsSigned)
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
    else
    {
      GenPrintInstr3Operands(MipsInstrAnd, 0,
                             reg, 0,
                             reg, 0,
                             MipsOpConst, 0xFF);
    }
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
  printf(" # JumpIfZero\n");
#endif
  GenPrintInstr3Operands(MipsInstrBEQ, 0,
                         MipsOpRegV0, 0,
                         MipsOpRegZero, 0,
                         MipsOpNumLabel, label);
}

void GenJumpIfNotZero(int label)
{
#ifndef NO_ANNOTATIONS
  printf(" # JumpIfNotZero\n");
#endif
  GenPrintInstr3Operands(MipsInstrBNE, 0,
                         MipsOpRegV0, 0,
                         MipsOpRegZero, 0,
                         MipsOpNumLabel, label);
}

extern int CurFxnParamCntMin, CurFxnParamCntMax;

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
    error("Error: Invalid operator\n");
    return 0;
  }
}

void GenReadIndirect(int regDst, int regSrc, int opSz)
{
  if (opSz == 1)
  {
    if (CharIsSigned)
    {
      GenPrintInstr2Operands(MipsInstrLB, 0,
                             regDst, 0,
                             regSrc + 0x20, 0);
    }
    else
    {
      GenPrintInstr2Operands(MipsInstrLBU, 0,
                             regDst, 0,
                             regSrc + 0x20, 0);
    }
  }
  else
  {
    GenPrintInstr2Operands(MipsInstrLW, 0,
                           regDst, 0,
                           regSrc + 0x20, 0);
  }
}

void GenWriteIndirect(int regDst, int regSrc, int opSz)
{
  if (opSz == 1)
  {
    GenPrintInstr2Operands(MipsInstrSB, 0,
                           regSrc, 0,
                           regDst + 0x20, 0);
  }
  else
  {
    GenPrintInstr2Operands(MipsInstrSW, 0,
                           regSrc, 0,
                           regDst + 0x20, 0);
  }
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
  GenExtendRegAIfNeeded(regDst, opSz);
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
  GenExtendRegAIfNeeded(regDst, opSz);
}

void GenPushReg(int reg)
{
  GenPrintInstr3Operands(MipsInstrSubU, 0,
                         MipsOpRegSp, 0,
                         MipsOpRegSp, 0,
                         MipsOpConst, 4);

  GenPrintInstr2Operands(MipsInstrSW, 0,
                         reg, 0,
                         MipsOpIndRegSp, 0);
}

void GenPopReg(int reg)
{
  GenPrintInstr2Operands(MipsInstrLW, 0,
                         reg, 0,
                         MipsOpIndRegSp, 0);

  GenPrintInstr3Operands(MipsInstrAddU, 0,
                         MipsOpRegSp, 0,
                         MipsOpRegSp, 0,
                         MipsOpConst, 4);
}

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
    case tokNumInt: printf(" # %d\n", truncInt(v)); break;
    case tokNumUint: printf(" # %uu\n", truncUint(v)); break;
    case tokIdent: printf(" # %s\n", IdentTable + v); break;
    case tokLocalOfs: printf(" # local ofs\n"); break;
    case ')': printf(" # ) fxn call\n"); break;
    case tokUnaryStar: printf(" # * (read dereference)\n"); break;
    case '=': printf(" # = (write dereference)\n"); break;
    case tokShortCirc: printf(" # short-circuit "); break;
    case tokLogAnd: printf(" # short-circuit && target\n"); break;
    case tokLogOr: printf(" # short-circuit || target\n"); break;
    case tokIf: case tokIfNot: break;
    default: printf(" # %s\n", GetTokenName(tok)); break;
    }
#endif

    switch (tok)
    {
    case tokNumInt:
    case tokNumUint:
      if (gotUnary)
        GenPushReg(MipsOpRegV0);
      GenPrintInstr2Operands(MipsInstrLI, 0,
                             MipsOpRegV0, 0,
                             MipsOpConst, v);
      gotUnary = 1;
      break;

    case tokIdent:
      if (gotUnary)
        GenPushReg(MipsOpRegV0);
      GenPrintInstr2Operands(MipsInstrLA, 0,
                             MipsOpRegV0, 0,
                             MipsOpLabel, v);
      gotUnary = 1;
      break;

    case tokLocalOfs:
      if (gotUnary)
        GenPushReg(MipsOpRegV0);
      GenPrintInstr3Operands(MipsInstrAddU, 0,
                             MipsOpRegV0, 0,
                             MipsOpRegFp, 0,
                             MipsOpConst, v);
      gotUnary = 1;
      break;

    case '(':
      if (gotUnary)
        GenPushReg(MipsOpRegV0);
      gotUnary = 0;
      if (v < 16)
        GenLocalAlloc(16 - v);
      break;

    case ')':
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
      GenPrintInstr1Operand(MipsInstrJAL, 0,
                            MipsOpRegV0, 0);
      if (v < 16)
        v = 16;
      GenLocalAlloc(-v);
      break;

    case tokUnaryStar:
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
      {
        int instr = GenGetBinaryOperatorInstr(tok);
        GenPopReg(MipsOpRegT0);
        GenPrintInstr3Operands(instr, 0,
                               MipsOpRegV0, 0,
                               MipsOpRegT0, 0,
                               MipsOpRegV0, 0);
      }
      break;

    case '/':
    case tokUDiv:
    case '%':
    case tokUMod:
      GenPopReg(MipsOpRegT0);
      if (tok == '/' || tok == '%')
        GenPrintInstr2Operands(MipsInstrDiv, 0,
                               MipsOpRegT0, 0,
                               MipsOpRegV0, 0);
      else
        GenPrintInstr2Operands(MipsInstrDivU, 0,
                               MipsOpRegT0, 0,
                               MipsOpRegV0, 0);
      if (tok == '%' || tok == tokUMod)
        GenPrintInstr1Operand(MipsInstrMfHi, 0,
                              MipsOpRegV0, 0);
      else
        GenPrintInstr1Operand(MipsInstrMfLo, 0,
                              MipsOpRegV0, 0);
      break;

    case tokInc:
    case tokDec:
      GenPrintInstr2Operands(MipsInstrMov, 0,
                             MipsOpRegT0, 0,
                             MipsOpRegV0, 0);
      GenIncDecIndirect(MipsOpRegV0, MipsOpRegT0, v, tok);
      break;
    case tokPostInc:
    case tokPostDec:
      GenPrintInstr2Operands(MipsInstrMov, 0,
                             MipsOpRegT0, 0,
                             MipsOpRegV0, 0);
      GenPostIncDecIndirect(MipsOpRegV0, MipsOpRegT0, v, tok);
      break;

    case tokPostAdd:
    case tokPostSub:
      {
        int instr = GenGetBinaryOperatorInstr(tok);
        GenPopReg(MipsOpRegT0);
        GenPrintInstr2Operands(MipsInstrMov, 0,
                               MipsOpRegT1, 0,
                               MipsOpRegV0, 0);

        GenReadIndirect(MipsOpRegV0, MipsOpRegT0, v);
        GenPrintInstr3Operands(instr, 0,
                               MipsOpRegT1, 0,
                               MipsOpRegT1, 0,
                               MipsOpRegV0, 0);
        GenWriteIndirect(MipsOpRegT0, MipsOpRegT1, v);
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
        GenPopReg(MipsOpRegT0);
        GenPrintInstr2Operands(MipsInstrMov, 0,
                               MipsOpRegT1, 0,
                               MipsOpRegV0, 0);

        GenReadIndirect(MipsOpRegV0, MipsOpRegT0, v);
        GenPrintInstr3Operands(instr, 0,
                               MipsOpRegV0, 0,
                               MipsOpRegV0, 0,
                               MipsOpRegT1, 0);
        GenWriteIndirect(MipsOpRegT0, MipsOpRegV0, v);

        GenExtendRegAIfNeeded(MipsOpRegV0, v);
      }
      break;

    case tokAssignDiv:
    case tokAssignUDiv:
    case tokAssignMod:
    case tokAssignUMod:
      GenPopReg(MipsOpRegT0);

      GenReadIndirect(MipsOpRegT1, MipsOpRegT0, v);
      if (tok == '/' || tok == '%')
        GenPrintInstr2Operands(MipsInstrDiv, 0,
                               MipsOpRegT1, 0,
                               MipsOpRegV0, 0);
      else
        GenPrintInstr2Operands(MipsInstrDivU, 0,
                               MipsOpRegT1, 0,
                               MipsOpRegV0, 0);
      if (tok == '%' || tok == tokUMod)
        GenPrintInstr1Operand(MipsInstrMfHi, 0,
                              MipsOpRegV0, 0);
      else
        GenPrintInstr1Operand(MipsInstrMfLo, 0,
                              MipsOpRegV0, 0);
      GenWriteIndirect(MipsOpRegT0, MipsOpRegV0, v);

      GenExtendRegAIfNeeded(MipsOpRegV0, v);
      break;

    case '=':
      GenPopReg(MipsOpRegT0);
      GenWriteIndirect(MipsOpRegT0, MipsOpRegV0, v);
      GenExtendRegAIfNeeded(MipsOpRegV0, v);
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
      GenPopReg(MipsOpRegT0);
      GenPrintInstr3Operands(MipsInstrSLT, 0,
                             MipsOpRegV0, 0,
                             MipsOpRegT0, 0,
                             MipsOpRegV0, 0);
      break;
    case tokULess:
      GenPopReg(MipsOpRegT0);
      GenPrintInstr3Operands(MipsInstrSLTU, 0,
                             MipsOpRegV0, 0,
                             MipsOpRegT0, 0,
                             MipsOpRegV0, 0);
      break;
    case '>':
      GenPopReg(MipsOpRegT0);
      GenPrintInstr3Operands(MipsInstrSLT, 0,
                             MipsOpRegV0, 0,
                             MipsOpRegV0, 0,
                             MipsOpRegT0, 0);
      break;
    case tokUGreater:
      GenPopReg(MipsOpRegT0);
      GenPrintInstr3Operands(MipsInstrSLTU, 0,
                             MipsOpRegV0, 0,
                             MipsOpRegV0, 0,
                             MipsOpRegT0, 0);
      break;
    case tokLEQ:
      GenPopReg(MipsOpRegT0);
      GenPrintInstr3Operands(MipsInstrSLT, 0,
                             MipsOpRegV0, 0,
                             MipsOpRegV0, 0,
                             MipsOpRegT0, 0);
      GenPrintInstr3Operands(MipsInstrXor, 0,
                             MipsOpRegV0, 0,
                             MipsOpRegV0, 0,
                             MipsOpConst, 1);
      break;
    case tokULEQ:
      GenPopReg(MipsOpRegT0);
      GenPrintInstr3Operands(MipsInstrSLTU, 0,
                             MipsOpRegV0, 0,
                             MipsOpRegV0, 0,
                             MipsOpRegT0, 0);
      GenPrintInstr3Operands(MipsInstrXor, 0,
                             MipsOpRegV0, 0,
                             MipsOpRegV0, 0,
                             MipsOpConst, 1);
      break;
    case tokGEQ:
      GenPopReg(MipsOpRegT0);
      GenPrintInstr3Operands(MipsInstrSLT, 0,
                             MipsOpRegV0, 0,
                             MipsOpRegT0, 0,
                             MipsOpRegV0, 0);
      GenPrintInstr3Operands(MipsInstrXor, 0,
                             MipsOpRegV0, 0,
                             MipsOpRegV0, 0,
                             MipsOpConst, 1);
      break;
    case tokUGEQ:
      GenPopReg(MipsOpRegT0);
      GenPrintInstr3Operands(MipsInstrSLTU, 0,
                             MipsOpRegV0, 0,
                             MipsOpRegT0, 0,
                             MipsOpRegV0, 0);
      GenPrintInstr3Operands(MipsInstrXor, 0,
                             MipsOpRegV0, 0,
                             MipsOpRegV0, 0,
                             MipsOpConst, 1);
      break;
    case tokEQ:
      GenPopReg(MipsOpRegT0);
      GenPrintInstr3Operands(MipsInstrXor, 0,
                             MipsOpRegV0, 0,
                             MipsOpRegT0, 0,
                             MipsOpRegV0, 0);
      GenPrintInstr3Operands(MipsInstrSLTU, 0,
                             MipsOpRegV0, 0,
                             MipsOpRegV0, 0,
                             MipsOpConst, 1);
      break;
    case tokNEQ:
      GenPopReg(MipsOpRegT0);
      GenPrintInstr3Operands(MipsInstrXor, 0,
                             MipsOpRegV0, 0,
                             MipsOpRegT0, 0,
                             MipsOpRegV0, 0);
      GenPrintInstr3Operands(MipsInstrSLTU, 0,
                             MipsOpRegV0, 0,
                             MipsOpRegZero, 0,
                             MipsOpRegV0, 0);
      break;

    case tok_Bool:
      GenPrintInstr3Operands(MipsInstrSLTU, 0,
                             MipsOpRegV0, 0,
                             MipsOpRegZero, 0,
                             MipsOpRegV0, 0);
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

void GenExpr(void)
{
  GenStrData(1);
  GenExpr0();
}
