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
/*                          TR3200 code generator                            */
/*                                                                           */
/*****************************************************************************/

STATIC
void GenInit(void)
{
  // initialization of target-specific code generator
  SizeOfWord = 4;
  OutputFormat = FormatSegmented;
  CodeHeaderFooter[0] = "\tsection .text";
  DataHeaderFooter[0] = "\tsection .data";
  RoDataHeaderFooter[0] = "\tsection .rodata";
  BssHeaderFooter[0] = "\tsection .bss";
}

STATIC
int GenInitParams(int argc, char** argv, int* idx)
{
  (void)argc;
  (void)argv;
  (void)idx;
  // initialization of target-specific code generator with parameters

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
  printf2(" ; ");
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
      printf2("\t.global\t_%s\n", Label);
    printf2("_%s:\n", Label);
  }
}

STATIC
void GenPrintLabel(char* Label)
{
  {
    if (isdigit(*Label))
      printf2("L%s", Label);
    else
      printf2("_%s", Label);
  }
}

STATIC
void GenNumLabel(int Label)
{
  printf2("L%d:\n", Label);
}

STATIC
void GenPrintNumLabel(int label)
{
  printf2("L%d", label);
}

STATIC
void GenZeroData(unsigned Size, int bss)
{
  (void)bss;
  printf2("\t.fill\t%u\n", truncUint(Size));
}

STATIC
void GenIntData(int Size, int Val)
{
  Val = truncInt(Val);
  if (Size == 1)
    printf2("\t.db\t%d\n", Val);
  else if (Size == 2)
    printf2("\t.dw\t%d\n", Val);
  else if (Size == 4)
    printf2("\t.dd\t%d\n", Val);
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
    printf2("\t.db\t");
  else if (Size == 2)
    printf2("\t.dw\t");
  else if (Size == 4)
    printf2("\t.dd\t");
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

#define Tr32InstrNop    0x00

#define Tr32InstrMov    0x01

#define Tr32InstrLB     0x02
#define Tr32InstrLW     0x03
#define Tr32InstrL      0x04
#define Tr32InstrSB     0x05
#define Tr32InstrSW     0x06
#define Tr32InstrS      0x07

#define Tr32InstrSigxB  0x08
#define Tr32InstrSigxW  0x09

#define Tr32InstrAdd    0x0A
#define Tr32InstrSub    0x0B
#define Tr32InstrRSub   0x0C
#define Tr32InstrAnd    0x0D
#define Tr32InstrOr     0x0E
#define Tr32InstrXor    0x0F
#define Tr32InstrNot    0x10
#define Tr32InstrLLS    0x11
#define Tr32InstrLRS    0x12
#define Tr32InstrARS    0x13
#define Tr32InstrMul    0x14
#define Tr32InstrSDiv   0x15
#define Tr32InstrDiv    0x16

#define Tr32InstrRJmp   0x17
#define Tr32InstrRCall  0x18
#define Tr32InstrCall   0x19
#define Tr32InstrRet    0x1A
#define Tr32InstrPush   0x1B
#define Tr32InstrPop    0x1C

// DO NOT REORDER Tr32InstrIf*; START ON EVEN VALUE
#define Tr32InstrIfSL    0x20
#define Tr32InstrIfSGE   0x21
#define Tr32InstrIfSG    0x22
#define Tr32InstrIfSLE   0x23
#define Tr32InstrIfL     0x24
#define Tr32InstrIfGE    0x25
#define Tr32InstrIfG     0x26
#define Tr32InstrIfLE    0x27
#define Tr32InstrIfEq    0x28
#define Tr32InstrIfNEq   0x29
#define Tr32InstrIfBits  0x2A
#define Tr32InstrIfClear 0x2B

STATIC
void GenPrintInstr(int instr, int val)
{
  char* p = "";

  (void)val;

  switch (instr)
  {
  case Tr32InstrNop  : p = "nop"; break;

  case Tr32InstrMov  : p = "mov"; break;

  case Tr32InstrLB   : p = "loadb"; break;
  case Tr32InstrLW   : p = "loadw"; break;
  case Tr32InstrL    : p = "load"; break;
  case Tr32InstrSB   : p = "storeb"; break;
  case Tr32InstrSW   : p = "storew"; break;
  case Tr32InstrS    : p = "store"; break;

  case Tr32InstrSigxB: p = "sigxb"; break;
  case Tr32InstrSigxW: p = "sigxw"; break;

  case Tr32InstrAdd  : p = "add"; break;
  case Tr32InstrSub  : p = "sub"; break;
  case Tr32InstrRSub : p = "rsb"; break;
  case Tr32InstrAnd  : p = "and"; break;
  case Tr32InstrOr   : p = "or"; break;
  case Tr32InstrXor  : p = "xor"; break;
  case Tr32InstrNot  : p = "not"; break;
  case Tr32InstrLLS  : p = "lls"; break;
  case Tr32InstrLRS  : p = "lrs"; break;
  case Tr32InstrARS  : p = "ars"; break;
  case Tr32InstrMul  : p = "mul"; break;
  case Tr32InstrSDiv : p = "sdiv"; break;
  case Tr32InstrDiv  : p = "div"; break;

  case Tr32InstrRJmp : p = "rjmp"; break;
  case Tr32InstrRCall: p = "rcall"; break;
  case Tr32InstrCall : p = "call"; break;
  case Tr32InstrRet  : p = "ret"; break;
  case Tr32InstrPush : p = "push"; break;
  case Tr32InstrPop  : p = "pop"; break;

  case Tr32InstrIfSL   : p = "ifsl"; break;
  case Tr32InstrIfSGE  : p = "ifsge"; break;
  case Tr32InstrIfSG   : p = "ifsg"; break;
  case Tr32InstrIfSLE  : p = "ifsle"; break;
  case Tr32InstrIfL    : p = "ifl"; break;
  case Tr32InstrIfGE   : p = "ifge"; break;
  case Tr32InstrIfG    : p = "ifg"; break;
  case Tr32InstrIfLE   : p = "ifle"; break;
  case Tr32InstrIfEq   : p = "ifeq"; break;
  case Tr32InstrIfNEq  : p = "ifneq"; break;
  case Tr32InstrIfBits : p = "ifbits"; break;
  case Tr32InstrIfClear: p = "ifclear"; break;
  }

  printf2("\t%s\t", p);
}

#define Tr32OpReg0                       0x00
//...
#define Tr32OpRegY                       0x0B
#define Tr32OpRegBp                      0x0C
#define Tr32OpRegSp                      0x0D
//...
#define Tr32OpRegFlags                   0x0F

#define Tr32OpIndReg0                    0x10
//...
#define Tr32OpIndRegY                    0x1B
#define Tr32OpIndRegBp                   0x1C
#define Tr32OpIndRegSp                   0x1D
//...
#define Tr32OpIndRegFlags                0x1F

#define Tr32OpConst                      0x80
#define Tr32OpLabel                      0x81
#define Tr32OpNumLabel                   0x82

#define MAX_TEMP_REGS 8 // this many temp registers used beginning with R1 to hold subexpression results
#define TEMP_REG_A 9 // two temporary registers used for momentary operations, similarly to the MIPS AT/R1 register
#define TEMP_REG_B 10

#define tokRevMinus    0x100 // reversed subtraction, RSB
#define tokRevIdent    0x101
#define tokRevLocalOfs 0x102

int GenRegsUsed; // bitmask of registers used by the function being compiled

STATIC
void GenPrintOperand(int op, int val)
{
  if (op >= Tr32OpReg0 && op <= Tr32OpRegFlags)
  {
    GenRegsUsed |= 1 << op;
    switch (op)
    {
    case Tr32OpRegBp:    printf2("%%bp");    break;
    case Tr32OpRegSp:    printf2("%%sp");    break;
    case Tr32OpRegY:     printf2("%%y");     break;
    case Tr32OpRegFlags: printf2("%%flags"); break;
    default:             printf2("%%r%d", op);
    }
  }
  else if (op >= Tr32OpIndReg0 && op <= Tr32OpIndRegFlags)
  {
    GenPrintOperand(op - Tr32OpIndReg0, 0);
    val = truncInt(val);
    if (val)
      printf2(", %d", val);
  }
  else
  {
    switch (op)
    {
    case Tr32OpConst: printf2("%d", truncInt(val)); break;
    case Tr32OpLabel: GenPrintLabel(IdentTable + val); break;
    case Tr32OpNumLabel: GenPrintNumLabel(val); break;

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
void GenPrintInstrNoOperand(int instr, int instrval)
{
  GenPrintInstr(instr, instrval);
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
  if (operand3 == Tr32OpConst && operand3val == 0 &&
      (instr == Tr32InstrAdd || instr == Tr32InstrSub) &&
      operand1 == operand2)
    return;

  GenPrintInstr(instr, instrval);
  GenPrintOperand(operand1, operand1val);
  GenPrintOperandSeparator();
  GenPrintOperand(operand2, operand2val);
  GenPrintOperandSeparator();
  GenPrintOperand(operand3, operand3val);
  GenPrintNewLine();
}

STATIC
void GenExtendRegIfNeeded(int reg, int opSz)
{
  if (opSz == -1)
  {
    GenPrintInstr2Operands(Tr32InstrSigxB, 0,
                           reg, 0,
                           reg, 0);
  }
  else if (opSz == 1)
  {
    GenPrintInstr3Operands(Tr32InstrAnd, 0,
                           reg, 0,
                           reg, 0,
                           Tr32OpConst, 0xFF);
  }
  else if (opSz == -2)
  {
    GenPrintInstr2Operands(Tr32InstrSigxW, 0,
                           reg, 0,
                           reg, 0);
  }
  else if (opSz == 2)
  {
    GenPrintInstr3Operands(Tr32InstrAnd, 0,
                           reg, 0,
                           reg, 0,
                           Tr32OpConst, 0xFFFF);
  }
}

STATIC
void GenJumpUncond(int label)
{
  GenPrintInstr1Operand(Tr32InstrRJmp, 0,
                        Tr32OpNumLabel, label);
}

extern int GenWreg; // GenWreg is defined below

#ifndef USE_SWITCH_TAB
STATIC
void GenJumpIfEqual(int val, int label)
{
  GenPrintInstr2Operands(Tr32InstrIfEq, 0,
                         GenWreg, 0,
                         Tr32OpConst, val);
  GenPrintInstr1Operand(Tr32InstrRJmp, 0,
                        Tr32OpNumLabel, label);
}
#endif

STATIC
void GenJumpIfZero(int label)
{
#ifndef NO_ANNOTATIONS
  printf2(" ; JumpIfZero\n");
#endif
  GenPrintInstr2Operands(Tr32InstrIfClear, 0,
                         GenWreg, 0,
                         GenWreg, 0);
  GenPrintInstr1Operand(Tr32InstrRJmp, 0,
                        Tr32OpNumLabel, label);
}

STATIC
void GenJumpIfNotZero(int label)
{
#ifndef NO_ANNOTATIONS
  printf2(" ; JumpIfNotZero\n");
#endif
  GenPrintInstr2Operands(Tr32InstrIfBits, 0,
                         GenWreg, 0,
                         GenWreg, 0);
  GenPrintInstr1Operand(Tr32InstrRJmp, 0,
                        Tr32OpNumLabel, label);
}

STATIC
void GenSaveRestoreRegs(int save)
{
  int rstart, rstop, rinc, r;
  int mask = GenRegsUsed;
  mask &= ~(1 << Tr32OpReg0); // not preserved
//  mask &= ~(1 << Tr32OpRegY); // TBD??? Y is preserved, right???
  mask &= ~(1 << Tr32OpRegBp); // taken care of
  mask &= ~(1 << Tr32OpRegSp); // taken care of
  mask &= ~(1 << Tr32OpRegFlags); // TBD??? flags aren't preserved, right???

  if (save)
    rstart = Tr32OpReg0, rstop = Tr32OpRegFlags, rinc = 1;
  else
    rstart = Tr32OpRegFlags, rstop = Tr32OpReg0, rinc = -1;

  for (r = rstart; r != rstop; r += rinc)
  {
    int used = (mask & (1 << r)) != 0;
    if (save || used)
    {
      int pfx = used ? ' ' : ';';
      printf2(save ? "\t%cpush\t" : "\t%cpop\t", pfx);
      GenPrintOperand(r, 0);
      GenPrintNewLine();
    }
  }
  GenRegsUsed = mask; // undo changes in GenRegsUsed by GenPrintOperand()
}

void GenIsrProlog(void)
{
  // TBD???
}

void GenIsrEpilog(void)
{
  // TBD???
}

fpos_t GenPrologPos;

STATIC
void GenWriteFrameSize(void)
{
  unsigned size = -CurFxnMinLocalOfs;
  int pfx = size ? ' ' : ';';
  printf2("\t%csub\t%%sp, %%sp, %10u\n", pfx, size); // 10 chars are enough for 32-bit unsigned ints
  GenSaveRestoreRegs(1);
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
  GenRegsUsed = 0;

  GenPrintInstr1Operand(Tr32InstrPush, 0,
                        Tr32OpRegBp, 0);

  GenPrintInstr2Operands(Tr32InstrMov, 0,
                         Tr32OpRegBp, 0,
                         Tr32OpRegSp, 0);

  fgetpos(OutFile, &GenPrologPos);
  GenWriteFrameSize();
}

STATIC
void GenGrowStack(int size)
{
  if (!size)
    return;
  GenPrintInstr3Operands(Tr32InstrSub, 0,
                         Tr32OpRegSp, 0,
                         Tr32OpRegSp, 0,
                         Tr32OpConst, size);
}

STATIC
void GenFxnEpilog(void)
{
  GenUpdateFrameSize();

  GenSaveRestoreRegs(0);

  GenPrintInstr2Operands(Tr32InstrMov, 0,
                         Tr32OpRegSp, 0,
                         Tr32OpRegBp, 0);

  GenPrintInstr1Operand(Tr32InstrPop, 0,
                        Tr32OpRegBp, 0);

  GenPrintInstrNoOperand(Tr32InstrRet, 0);
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
    return Tr32InstrAdd;
  case tokPostSub:
  case tokAssignSub:
  case '-':
    return Tr32InstrSub;
  case tokRevMinus:
    return Tr32InstrRSub;
  case '&':
  case tokAssignAnd:
    return Tr32InstrAnd;
  case '^':
  case tokAssignXor:
    return Tr32InstrXor;
  case '|':
  case tokAssignOr:
    return Tr32InstrOr;
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
    return Tr32InstrNop;
  case '*':
  case tokAssignMul:
    return Tr32InstrMul;
  case '/':
  case '%':
  case tokAssignDiv:
  case tokAssignMod:
    GenRegsUsed |= 1 << Tr32OpRegY; // TBD??? hacky
    return Tr32InstrSDiv;
  case tokUDiv:
  case tokUMod:
  case tokAssignUDiv:
  case tokAssignUMod:
    GenRegsUsed |= 1 << Tr32OpRegY; // TBD??? hacky
    return Tr32InstrDiv;
  case tokLShift:
  case tokAssignLSh:
    return Tr32InstrLLS;
  case tokRShift:
  case tokAssignRSh:
    return Tr32InstrARS;
  case tokURShift:
  case tokAssignURSh:
    return Tr32InstrLRS;

  default:
    //error("Error: Invalid operator\n");
    errorInternal(101);
    return 0;
  }
}

STATIC
void GenReadIdent(int regDst, int opSz, int label)
{
  int instr = Tr32InstrL;
  if (opSz == -1 || opSz == 1)
  {
    instr = Tr32InstrLB;
  }
  else if (opSz == -2 || opSz == 2)
  {
    instr = Tr32InstrLW;
  }
  GenPrintInstr2Operands(instr, 0,
                         regDst, 0,
                         Tr32OpLabel, label);

  if (opSz == -1)
    GenPrintInstr2Operands(Tr32InstrSigxB, 0,
                           regDst, 0,
                           regDst, 0);
  else if (opSz == -2)
    GenPrintInstr2Operands(Tr32InstrSigxW, 0,
                           regDst, 0,
                           regDst, 0);
}

STATIC
void GenReadLocal(int regDst, int opSz, int ofs)
{
  int instr = Tr32InstrL;
  if (opSz == -1 || opSz == 1)
  {
    instr = Tr32InstrLB;
  }
  else if (opSz == -2 || opSz == 2)
  {
    instr = Tr32InstrLW;
  }
  GenPrintInstr2Operands(instr, 0,
                         regDst, 0,
                         Tr32OpIndRegBp, ofs);

  if (opSz == -1)
    GenPrintInstr2Operands(Tr32InstrSigxB, 0,
                           regDst, 0,
                           regDst, 0);
  else if (opSz == -2)
    GenPrintInstr2Operands(Tr32InstrSigxW, 0,
                           regDst, 0,
                           regDst, 0);
}

STATIC
void GenReadIndirect(int regDst, int regSrc, int opSz)
{
  int instr = Tr32InstrL;
  if (opSz == -1 || opSz == 1)
  {
    instr = Tr32InstrLB;
  }
  else if (opSz == -2 || opSz == 2)
  {
    instr = Tr32InstrLW;
  }
  GenPrintInstr2Operands(instr, 0,
                         regDst, 0,
                         regSrc + Tr32OpIndReg0, 0);

  if (opSz == -1)
    GenPrintInstr2Operands(Tr32InstrSigxB, 0,
                           regDst, 0,
                           regDst, 0);
  else if (opSz == -2)
    GenPrintInstr2Operands(Tr32InstrSigxW, 0,
                           regDst, 0,
                           regDst, 0);
}

STATIC
void GenWriteIdent(int regSrc, int opSz, int label)
{
  int instr = Tr32InstrS;
  if (opSz == -1 || opSz == 1)
  {
    instr = Tr32InstrSB;
  }
  else if (opSz == -2 || opSz == 2)
  {
    instr = Tr32InstrSW;
  }
  GenPrintInstr2Operands(instr, 0,
                         Tr32OpLabel, label,
                         regSrc, 0);
}

STATIC
void GenWriteLocal(int regSrc, int opSz, int ofs)
{
  int instr = Tr32InstrS;
  if (opSz == -1 || opSz == 1)
  {
    instr = Tr32InstrSB;
  }
  else if (opSz == -2 || opSz == 2)
  {
    instr = Tr32InstrSW;
  }
  GenPrintInstr2Operands(instr, 0,
                         Tr32OpIndRegBp, ofs,
                         regSrc, 0);
}

STATIC
void GenWriteIndirect(int regDst, int regSrc, int opSz)
{
  int instr = Tr32InstrS;
  if (opSz == -1 || opSz == 1)
  {
    instr = Tr32InstrSB;
  }
  else if (opSz == -2 || opSz == 2)
  {
    instr = Tr32InstrSW;
  }
  GenPrintInstr2Operands(instr, 0,
                         regDst + Tr32OpIndReg0, 0,
                         regSrc, 0);
}

STATIC
void GenIncDecIdent(int regDst, int opSz, int label, int tok)
{
  int instr = Tr32InstrAdd;

  if (tok != tokInc)
    instr = Tr32InstrSub;

  GenReadIdent(regDst, opSz, label);
  GenPrintInstr3Operands(instr, 0,
                         regDst, 0,
                         regDst, 0,
                         Tr32OpConst, 1);
  GenWriteIdent(regDst, opSz, label);
  GenExtendRegIfNeeded(regDst, opSz);
}

STATIC
void GenIncDecLocal(int regDst, int opSz, int ofs, int tok)
{
  int instr = Tr32InstrAdd;

  if (tok != tokInc)
    instr = Tr32InstrSub;

  GenReadLocal(regDst, opSz, ofs);
  GenPrintInstr3Operands(instr, 0,
                         regDst, 0,
                         regDst, 0,
                         Tr32OpConst, 1);
  GenWriteLocal(regDst, opSz, ofs);
  GenExtendRegIfNeeded(regDst, opSz);
}

STATIC
void GenIncDecIndirect(int regDst, int regSrc, int opSz, int tok)
{
  int instr = Tr32InstrAdd;

  if (tok != tokInc)
    instr = Tr32InstrSub;

  GenReadIndirect(regDst, regSrc, opSz);
  GenPrintInstr3Operands(instr, 0,
                         regDst, 0,
                         regDst, 0,
                         Tr32OpConst, 1);
  GenWriteIndirect(regSrc, regDst, opSz);
  GenExtendRegIfNeeded(regDst, opSz);
}

STATIC
void GenPostIncDecIdent(int regDst, int opSz, int label, int tok)
{
  int instr = Tr32InstrAdd;

  if (tok != tokPostInc)
    instr = Tr32InstrSub;

  GenReadIdent(regDst, opSz, label);
  GenPrintInstr3Operands(instr, 0,
                         regDst, 0,
                         regDst, 0,
                         Tr32OpConst, 1);
  GenWriteIdent(regDst, opSz, label);
  GenPrintInstr3Operands(instr, 0,
                         regDst, 0,
                         regDst, 0,
                         Tr32OpConst, -1);
  GenExtendRegIfNeeded(regDst, opSz);
}

STATIC
void GenPostIncDecLocal(int regDst, int opSz, int ofs, int tok)
{
  int instr = Tr32InstrAdd;

  if (tok != tokPostInc)
    instr = Tr32InstrSub;

  GenReadLocal(regDst, opSz, ofs);
  GenPrintInstr3Operands(instr, 0,
                         regDst, 0,
                         regDst, 0,
                         Tr32OpConst, 1);
  GenWriteLocal(regDst, opSz, ofs);
  GenPrintInstr3Operands(instr, 0,
                         regDst, 0,
                         regDst, 0,
                         Tr32OpConst, -1);
  GenExtendRegIfNeeded(regDst, opSz);
}

STATIC
void GenPostIncDecIndirect(int regDst, int regSrc, int opSz, int tok)
{
  int instr = Tr32InstrAdd;

  if (tok != tokPostInc)
    instr = Tr32InstrSub;

  GenReadIndirect(regDst, regSrc, opSz);
  GenPrintInstr3Operands(instr, 0,
                         regDst, 0,
                         regDst, 0,
                         Tr32OpConst, 1);
  GenWriteIndirect(regSrc, regDst, opSz);
  GenPrintInstr3Operands(instr, 0,
                         regDst, 0,
                         regDst, 0,
                         Tr32OpConst, -1);
  GenExtendRegIfNeeded(regDst, opSz);
}

int CanUseTempRegs;
int TempsUsed;
int GenWreg = Tr32OpReg0; // current working register (R0, R1, R2, etc)
int GenLreg, GenRreg; // left operand register and right operand register after GenPopReg()

/*
  General idea behind GenWreg, GenLreg, GenRreg:

  - In expressions w/o function calls:

    Subexpressions are evaluated in R0, R1, R2, ..., R<MAX_TEMP_REGS>. If those registers
    aren't enough, the stack is used additionally.

    The expression result ends up in R0, which is handy for returning from
    functions.

    In the process, GenWreg is the current working register and is one of: R0, R1, R2, ... .
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
    will be the same as either GenLreg (when the popped operand comes from R1-R<MAX_TEMP_REGS>)
    or GenRreg (when the popped operand comes from the stack in TEMP_REG_A).

  - In expressions with function calls:

    GenWreg is always R0. R1-R<MAX_TEMP_REGS> are not used. Instead the stack and TEMP_REG_A and TEMP_REG_B
    are used.
*/

STATIC
void GenWregInc(int inc)
{
  if (inc > 0)
  {
    // Advance the current working register to the next available temporary register
    GenWreg++;
  }
  else
  {
    // Return to the previous current working register
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

  GenPrintInstr1Operand(Tr32InstrPush, 0,
                        GenWreg, 0);

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

  GenPrintInstr1Operand(Tr32InstrPop, 0,
                        TEMP_REG_A, 0);

  GenLreg = TEMP_REG_A;
  GenRreg = GenWreg;
}

STATIC
void GenPrep(int* idx)
{
  int tok;
  int oldIdxRight, oldIdxLeft, t0, t1;

  if (*idx < 0)
    //error("GenPrep(): idx < 0\n");
    errorInternal(100);

  tok = stack[*idx][0];

  oldIdxRight = --*idx;

  switch (tok)
  {
  case tokAssignMul:
  case tokUDiv:
  case tokUMod:
  case tokAssignUDiv:
  case tokAssignUMod:
    if (stack[oldIdxRight][0] == tokNumInt || stack[oldIdxRight][0] == tokNumUint)
    {
      unsigned m = truncUint(stack[oldIdxRight][1]);
      if (m && !(m & (m - 1)))
      {
        // Change multiplication to left shift, this helps indexing arrays of ints/pointers/etc
        if (tok == tokAssignMul)
        {
          t1 = 0;
          while (m >>= 1) t1++;
          stack[oldIdxRight][1] = t1;
          tok = tokAssignLSh;
        }
        // Change unsigned division to right shift and unsigned modulo to bitwise and
        else if (tok == tokUMod || tok == tokAssignUMod)
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
  case tokIdent:
  case tokLocalOfs:
    break;

  case tokPostAdd:
  case tokPostSub:
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
  case '-':
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
      case '-':
        xor = '-' ^ tokRevMinus; break;
      default:
        xor = 0; break;
      }
      tok ^= xor;
    }
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
      case tokULEQ:
        // Change left <= const to left < const+1, but const+1 must be <=0xFFFFFFFFu
        if (m != 0xFFFFFFFF)
        {
          stack[oldIdxRight][1]++;
          tok = tokULess;
        }
        break;
      case tokUGEQ:
        // Change left >= const to left > const-1, but const-1 must be >=0u
        if (m)
        {
          stack[oldIdxRight][1]--;
          tok = tokUGreater;
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

STATIC
void GenCmp(int* idx, int instr)
{
  // constness: 0 = zero const, 1 = non-zero const, 2 = non-const
  int constness = (stack[*idx - 1][0] == tokNumInt) ? (stack[*idx - 1][1] != 0) : 2;
  int constval = (constness == 1) ? truncInt(stack[*idx - 1][1]) : 0;
  // condbranch: 0 = no conditional branch, 1 = branch if true, 2 = branch if false
  int condbranch = (*idx + 1 < sp) ? (stack[*idx + 1][0] == tokIf) + (stack[*idx + 1][0] == tokIfNot) * 2 : 0;
  int label = condbranch ? stack[*idx + 1][1] : 0;

  if (constness == 2)
    GenPopReg();

  if (condbranch)
  {
    instr ^= condbranch != 1;
    if (constness == 2)
      GenPrintInstr2Operands(instr, 0,
                             GenLreg, 0,
                             GenRreg, 0);
    else
      GenPrintInstr2Operands(instr, 0,
                             GenWreg, 0,
                             Tr32OpConst, constval);
    GenPrintInstr1Operand(Tr32InstrRJmp, 0,
                          Tr32OpNumLabel, label);
  }
  else if (constness == 0 && (instr == Tr32InstrIfNEq || instr == Tr32InstrIfG))
  {
    // left != 0, left > 0u
    GenPrintInstr2Operands(Tr32InstrIfBits, 0,
                           GenWreg, 0,
                           GenWreg, 0);
    GenPrintInstr2Operands(Tr32InstrMov, 0,
                           GenWreg, 0,
                           Tr32OpConst, 1);
  }
  else if (constness == 0 && instr == Tr32InstrIfEq)
  {
    // left == 0
    GenPrintInstr3Operands(Tr32InstrSub, 0,
                           GenWreg, 0,
                           GenWreg, 0,
                           Tr32OpConst, 1);
    GenPrintInstr3Operands(Tr32InstrAnd, 0,
                           GenWreg, 0,
                           Tr32OpRegFlags, 0,
                           Tr32OpConst, 1);
  }
  else if (instr == Tr32InstrIfNEq)
  {
    // left != right
    if (constness == 2)
      GenPrintInstr3Operands(Tr32InstrXor, 0,
                             GenWreg, 0,
                             GenLreg, 0,
                             GenRreg, 0);
    else
      GenPrintInstr3Operands(Tr32InstrXor, 0,
                             GenWreg, 0,
                             GenWreg, 0,
                             Tr32OpConst, constval);
    GenPrintInstr2Operands(Tr32InstrIfBits, 0,
                           GenWreg, 0,
                           GenWreg, 0);
    GenPrintInstr2Operands(Tr32InstrMov, 0,
                           GenWreg, 0,
                           Tr32OpConst, 1);
  }
  else if ((instr == Tr32InstrIfL || instr == Tr32InstrIfGE ||
            instr == Tr32InstrIfG || instr == Tr32InstrIfLE) &&
           !(constness != 2 && constval == 0))
  {
    // left <[=]u right, left >[=]u right (only if right isn't a zero constant)
    int instr2 = (instr == Tr32InstrIfL || instr == Tr32InstrIfGE) ? Tr32InstrSub : Tr32InstrRSub;
    if (constness == 2)
      GenPrintInstr3Operands(instr2, 0,
                             GenWreg, 0,
                             GenLreg, 0,
                             GenRreg, 0);
    else
      GenPrintInstr3Operands(instr2, 0,
                             GenWreg, 0,
                             GenWreg, 0,
                             Tr32OpConst, constval);
    GenPrintInstr3Operands(Tr32InstrAnd, 0,
                           GenWreg, 0,
                           Tr32OpRegFlags, 0,
                           Tr32OpConst, 1);
    if (instr == Tr32InstrIfGE || instr == Tr32InstrIfLE)
      GenPrintInstr2Operands(Tr32InstrXor, 0,
                             GenWreg, 0,
                             Tr32OpConst, 1);
  }
  else
  {
    // Slow, general, catch-all implementation
    GenPrintInstr2Operands(Tr32InstrMov, 0,
                           TEMP_REG_B, 0,
                           Tr32OpConst, 0);
    if (constness == 2)
      GenPrintInstr2Operands(instr, 0,
                             GenLreg, 0,
                             GenRreg, 0);
    else
      GenPrintInstr2Operands(instr, 0,
                             GenWreg, 0,
                             Tr32OpConst, constval);
    GenPrintInstr2Operands(Tr32InstrMov, 0,
                           TEMP_REG_B, 0,
                           Tr32OpConst, 1);
    GenPrintInstr2Operands(Tr32InstrMov, 0,
                           GenWreg, 0,
                           TEMP_REG_B, 0);
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
  if (GenWreg != Tr32OpReg0)
    errorInternal(102);

  for (i = 0; i < sp; i++)
  {
    int tok = stack[i][0];
    int v = stack[i][1];

#ifndef NO_ANNOTATIONS
    switch (tok)
    {
    case tokNumInt: printf2(" ; %d\n", truncInt(v)); break;
    //case tokNumUint: printf2(" ; %uu\n", truncUint(v)); break;
    case tokIdent: case tokRevIdent: printf2(" ; %s\n", IdentTable + v); break;
    case tokLocalOfs: case tokRevLocalOfs: printf2(" ; local ofs\n"); break;
    case ')': printf2(" ; ) fxn call\n"); break;
    case tokUnaryStar: printf2(" ; * (read dereference)\n"); break;
    case '=': printf2(" ; = (write dereference)\n"); break;
    case tokShortCirc: printf2(" ; short-circuit "); break;
    case tokGoto: printf2(" ; sh-circ-goto "); break;
    case tokLogAnd: printf2(" ; short-circuit && target\n"); break;
    case tokLogOr: printf2(" ; short-circuit || target\n"); break;
    case tokIf: case tokIfNot: case tokReturn: break;
    case tokRevMinus: printf2(" ; -r\n"); break;
    default: printf2(" ; %s\n", GetTokenName(tok)); break;
    }
#endif

    switch (tok)
    {
    // TBD??? forward tokNumInt and tokIdent to ',', push them directly, w/o extra moves
    case tokNumInt:
      if (!(i + 1 < sp && ((t = stack[i + 1][0]) == '+' ||
                           t == '-' ||
                           t == tokRevMinus ||
                           t == '*' ||
                           t == '&' ||
                           t == '^' ||
                           t == '|' ||
                           t == tokLShift ||
                           t == tokRShift ||
                           t == tokURShift ||
                           t == '/' ||
                           t == tokUDiv ||
                           t == '%' ||
                           t == tokUMod ||
                           GenIsCmp(t))))
      {
        if (gotUnary)
          GenPushReg();

        GenPrintInstr2Operands(Tr32InstrMov, 0,
                               GenWreg, 0,
                               Tr32OpConst, v);
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
        GenPrintInstr2Operands(Tr32InstrMov, 0,
                               GenWreg, 0,
                               Tr32OpLabel, v);
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
        GenPrintInstr3Operands(Tr32InstrAdd, 0,
                               GenWreg, 0,
                               Tr32OpRegBp, 0,
                               Tr32OpConst, v);
      }
      gotUnary = 1;
      break;

    case '(':
      if (gotUnary)
        GenPushReg();
      gotUnary = 0;
      break;

    case ',':
      break;

    case ')':
      if (stack[i - 1][0] == tokIdent)
      {
        GenPrintInstr1Operand(Tr32InstrRCall, 0,
                              Tr32OpLabel, stack[i - 1][1]);
      }
      else
      {
        GenPrintInstr1Operand(Tr32InstrCall, 0,
                              GenWreg, 0);
      }
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
      GenPrintInstr1Operand(Tr32InstrNot, 0,
                            GenWreg, 0);
      break;
    case tokUnaryMinus:
      GenPrintInstr3Operands(Tr32InstrRSub, 0,
                             GenWreg, 0,
                             GenWreg, 0,
                             Tr32OpConst, 0);
      break;

    case '+':
    case '-':
    case tokRevMinus:
    case '*':
    case '&':
    case '^':
    case '|':
    case tokLShift:
    case tokRShift:
    case tokURShift:
    case '/':
    case tokUDiv:
    case '%':
    case tokUMod:
      if (stack[i - 1][0] == tokNumInt)
      {
        int instr = GenGetBinaryOperatorInstr(tok);
        GenPrintInstr3Operands(instr, 0,
                               GenWreg, 0,
                               GenWreg, 0,
                               Tr32OpConst, stack[i - 1][1]);
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
      if (tok == '%' || tok == tokUMod)
        GenPrintInstr2Operands(Tr32InstrMov, 0,
                               GenWreg, 0,
                               Tr32OpRegY, 0);
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
        GenPrintInstr2Operands(Tr32InstrMov, 0,
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
        GenPrintInstr2Operands(Tr32InstrMov, 0,
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
          GenPrintInstr2Operands(Tr32InstrMov, 0,
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
          GenPrintInstr2Operands(Tr32InstrMov, 0,
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
    case tokAssignDiv:
    case tokAssignUDiv:
    case tokAssignMod:
    case tokAssignUMod:
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

        if (tok == tokAssignMod || tok == tokAssignUMod)
          GenPrintInstr2Operands(Tr32InstrMov, 0,
                                 GenWreg, 0,
                                 Tr32OpRegY, 0);

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
          GenPrintInstr2Operands(Tr32InstrMov, 0,
                                 TEMP_REG_B, 0,
                                 GenLreg, 0);
          lsaved = TEMP_REG_B;
          rsaved = GenRreg;
        }
        else
        {
          // GenWreg == GenRreg here
          GenPrintInstr2Operands(Tr32InstrMov, 0,
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

        if (tok == tokAssignMod || tok == tokAssignUMod)
          GenPrintInstr2Operands(Tr32InstrMov, 0,
                                 GenWreg, 0,
                                 Tr32OpRegY, 0);

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
          GenPrintInstr2Operands(Tr32InstrMov, 0,
                                 GenWreg, 0,
                                 GenRreg, 0);
      }
      GenExtendRegIfNeeded(GenWreg, v);
      break;

    case '<':         GenCmp(&i, Tr32InstrIfSL ); break;
    case tokLEQ:      GenCmp(&i, Tr32InstrIfSLE); break;
    case '>':         GenCmp(&i, Tr32InstrIfSG ); break;
    case tokGEQ:      GenCmp(&i, Tr32InstrIfSGE); break;
    case tokULess:    GenCmp(&i, Tr32InstrIfL  ); break;
    case tokULEQ:     GenCmp(&i, Tr32InstrIfLE ); break;
    case tokUGreater: GenCmp(&i, Tr32InstrIfG  ); break;
    case tokUGEQ:     GenCmp(&i, Tr32InstrIfGE ); break;
    case tokEQ:       GenCmp(&i, Tr32InstrIfEq ); break;
    case tokNEQ:      GenCmp(&i, Tr32InstrIfNEq); break;

    case tok_Bool:
      GenPrintInstr2Operands(Tr32InstrIfBits, 0,
                             GenWreg, 0,
                             GenWreg, 0);
      GenPrintInstr2Operands(Tr32InstrMov, 0,
                             GenWreg, 0,
                             Tr32OpConst, 1);
      break;

    case tokSChar:
      GenPrintInstr2Operands(Tr32InstrSigxB, 0,
                             GenWreg, 0,
                             GenWreg, 0);
      break;
    case tokUChar:
      GenPrintInstr3Operands(Tr32InstrAnd, 0,
                             GenWreg, 0,
                             GenWreg, 0,
                             Tr32OpConst, 0xFF);
      break;
    case tokShort:
      GenPrintInstr2Operands(Tr32InstrSigxW, 0,
                             GenWreg, 0,
                             GenWreg, 0);
      break;
    case tokUShort:
      GenPrintInstr3Operands(Tr32InstrAnd, 0,
                             GenWreg, 0,
                             GenWreg, 0,
                             Tr32OpConst, 0xFFFF);
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

  if (GenWreg != Tr32OpReg0)
    printf("GenWreg=%d\n",GenWreg), errorInternal(104);
}

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
    puts2("\tpush\t%r1\n"
          "\tpush\t%r2\n"
          "\tpush\t%r3\n"
          "\tload\t%r1, %sp, 16\n" // size
          "\tload\t%r2, %sp, 20\n" // source
          "\tload\t%r3, %sp, 24"); // destination
    GenNumLabel(lbl);
    puts2("\tloadb\t%r0, %r2\n"
          "\tadd\t%r2, %r2, 1\n"
          "\tadd\t%r1, %r1, -1\n"
          "\tstoreb\t%r3, %r0\n"
          "\tadd\t%r3, %r3, 1\n"
          "\tifneq\t%r1, 0");
    printf2("\trjmp\t"); GenPrintNumLabel(lbl);
    puts2("");
    puts2("\tload\t%r0, %sp, 24\n" // destination
          "\tpop\t%r3\n"
          "\tpop\t%r2\n"
          "\tpop\t%r1\n"
          "\tret");

    puts2(CodeHeaderFooter[1]);
  }
}
