/*
Copyright (c) 2012-2018, Alexey Frunze
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
/*                           x86 code generator                              */
/*                                                                           */
/*****************************************************************************/

// TBD!!! compress/clean up

#ifdef CAN_COMPILE_32BIT
int WindowsStack = 0;
int WinChkStkLabel = 0;
#endif

#define MAX_GLOBALS_TABLE_LEN MAX_IDENT_TABLE_LEN

/*
  Globals table entry format:
    use char:       use: bit 0 = defined, bit 1 = used
    idlen char:     string length (<= 127)
    id char[idlen]: string (ASCIIZ)
*/
char GlobalsTable[MAX_GLOBALS_TABLE_LEN];
int GlobalsTableLen = 0;
int Use8086InstrOnly = 0;

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
      error("Table of globals exhausted\n");
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
  else if (!strcmp(argv[*idx], "-8086"))
  {
    Use8086InstrOnly = 1;
    return 1;
  }
  else if (!strcmp(argv[*idx], "-seg16"))
  {
    // this is the default option for x86
    OutputFormat = FormatSegmented; SizeOfWord = 2;
    return 1;
  }
#ifdef CAN_COMPILE_32BIT
  else if (!strcmp(argv[*idx], "-seg32"))
  {
    OutputFormat = FormatSegmented; SizeOfWord = 4;
    return 1;
  }
  else if (!strcmp(argv[*idx], "-huge"))
  {
    OutputFormat = FormatSegHuge; SizeOfWord = 4;
    return 1;
  }
  else if (!strcmp(argv[*idx], "-unreal"))
  {
    OutputFormat = FormatSegUnreal; SizeOfWord = 4;
    return 1;
  }
  else if (!strcmp(argv[*idx], "-winstack"))
  {
    WindowsStack = 1;
    return 1;
  }
#endif

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
  if (SizeOfWord == 2 || OutputFormat == FormatSegHuge || OutputFormat == FormatSegUnreal)
  {
    if(Use8086InstrOnly)
    {
      FileHeader = "bits 16\ncpu 8086\n";
    }
    else
    {
      FileHeader = "bits 16\n";
    }
  }
  else
    FileHeader = "bits 32\n";
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

STATIC
void GenNumLabel(int Label)
{
  if (UseLeadingUnderscores)
    printf2("L%d:\n", Label);
  else
    printf2("..@L%d:\n", Label);
}

STATIC
void GenPrintNumLabel(int label)
{
  if (UseLeadingUnderscores)
    printf2("L%d", label);
  else
    printf2("..@L%d", label);
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
  if (Size == 1)
    printf2("\tdb\t%d\n", Val);
  else if (Size == 2)
    printf2("\tdw\t%d\n", Val);
#ifdef CAN_COMPILE_32BIT
  else if (Size == 4)
    printf2("\tdd\t%d\n", Val);
#endif
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
#ifdef CAN_COMPILE_32BIT
  if (OutputFormat == FormatSegHuge)
  {
    int lab = LabelCnt++;
    printf2("section .relod\n\tdd\t"); GenPrintNumLabel(lab); puts2("");
    puts2(DataHeaderFooter[0]);
    GenNumLabel(lab);
  }
#endif
  if (Size == 1)
    printf2("\tdb\t");
  else if (Size == 2)
    printf2("\tdw\t");
#ifdef CAN_COMPILE_32BIT
  else if (Size == 4)
    printf2("\tdd\t");
#endif
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
#ifdef CAN_COMPILE_32BIT
  return (OutputFormat == FormatSegHuge || OutputFormat == FormatSegUnreal) && GenExterns;
#else
  return 0;
#endif
}

STATIC
void GenRecordFxnSize(char* startLabelName, int endLabelNo)
{
  // In the huge mode(l) individual functions must each fit into a 64KB segment.
  // A special non-allocated section, ".fxnsz", will hold function sizes and
  // the linker will check them.
#ifdef CAN_COMPILE_32BIT
  // YASM unnecessarily warns when it sees the same section flags again, so
  // generate them only once.
  static int firstTime = 1;
  printf2("section .fxnsz%s\n", firstTime ? " noalloc" : "");
  firstTime = 0;
  printf2("\tdd\t");
  GenPrintNumLabel(endLabelNo);
  printf2(" - ");
  GenPrintLabel(startLabelName);
  puts2("\n");
#else
  (void)startLabelName;
  (void)endLabelNo;
#endif
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

char* winstrs[] =
{
  "mov",
  "movsx",
  "movzx",
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
  case X86InstrLeave:
    p = (OutputFormat != FormatSegHuge && OutputFormat != FormatSegUnreal) ? "leave" : "db\t0x66\n\tleave";
    break;

  case X86InstrRet:
    p = (OutputFormat != FormatSegHuge && OutputFormat != FormatSegUnreal) ? "ret" : "retf";
    break;

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

  default:
    p = winstrs[instr];
    break;
  }

  switch (instr)
  {
  case X86InstrCbw:
  case X86InstrCwd:
#ifdef CAN_COMPILE_32BIT
  case X86InstrCdq:
#endif
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
#define X86OpRegAHalfWord               0x07
#define X86OpRegCHalfWord               0x08
#define X86OpRegBpWord                  0x09
#define X86OpRegSpWord                  0x0A
#define X86OpRegAByteOrWord             0x0B
#define X86OpRegCByteOrWord             0x0C
#define X86OpConst                      0x0D
#define X86OpLabel                      0x0E
#define X86OpNumLabel                   0x0F
#define X86OpIndLabel                   0x10
#define X86OpIndLabelExplicitByte       0x11
#define X86OpIndLabelExplicitWord       0x12
#define X86OpIndLabelExplicitHalfWord   0x13
#define X86OpIndLabelExplicitByteOrWord 0x14
#define X86OpIndLocal                   0x15
#define X86OpIndLocalExplicitByte       0x16
#define X86OpIndLocalExplicitWord       0x17
#define X86OpIndLocalExplicitHalfWord   0x18
#define X86OpIndLocalExplicitByteOrWord 0x19
#define X86OpIndRegB                    0x1A
#define X86OpIndRegBExplicitByte        0x1B
#define X86OpIndRegBExplicitWord        0x1C
#define X86OpIndRegBExplicitHalfWord    0x1D
#define X86OpIndRegBExplicitByteOrWord  0x1E
#define X86OpRegCByteHigh               0x1F

STATIC
int GenSelectByteOrWord(int op, int opSz)
{
  switch (op)
  {
  case X86OpRegAByteOrWord:
    op = X86OpRegAByte;
    if (opSz == SizeOfWord)
      op = X86OpRegAWord;
#ifdef CAN_COMPILE_32BIT
    else if (opSz == 2 || opSz == -2)
      op = X86OpRegAHalfWord;
#endif
    break;
  case X86OpRegCByteOrWord:
    op = X86OpRegCByte;
    if (opSz == SizeOfWord)
      op = X86OpRegCWord;
#ifdef CAN_COMPILE_32BIT
    else if (opSz == 2 || opSz == -2)
      op = X86OpRegCHalfWord;
#endif
    break;
  case X86OpIndLabelExplicitByteOrWord:
    op = X86OpIndLabelExplicitByte;
    if (opSz == SizeOfWord)
      op = X86OpIndLabelExplicitWord;
#ifdef CAN_COMPILE_32BIT
    else if (opSz == 2 || opSz == -2)
      op = X86OpIndLabelExplicitHalfWord;
#endif
    break;
  case X86OpIndLocalExplicitByteOrWord:
    op = X86OpIndLocalExplicitByte;
    if (opSz == SizeOfWord)
      op = X86OpIndLocalExplicitWord;
#ifdef CAN_COMPILE_32BIT
    else if (opSz == 2 || opSz == -2)
      op = X86OpIndLocalExplicitHalfWord;
#endif
    break;
  case X86OpIndRegBExplicitByteOrWord:
    op = X86OpIndRegBExplicitByte;
    if (opSz == SizeOfWord)
      op = X86OpIndRegBExplicitWord;
#ifdef CAN_COMPILE_32BIT
    else if (opSz == 2 || opSz == -2)
      op = X86OpIndRegBExplicitHalfWord;
#endif
    break;
  }
  return op;
}

STATIC
void GenPrintOperand(int op, int val)
{
  if (SizeOfWord == 2)
  {
    switch (op)
    {
    case X86OpRegAByte: printf2("al"); break;
    case X86OpRegAByteHigh: printf2("ah"); break;
    case X86OpRegCByte: printf2("cl"); break;
    case X86OpRegCByteHigh: printf2("ch"); break;
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
    case X86OpIndLocal: printf2("[bp%+d]", truncInt(val)); break;
    case X86OpIndLocalExplicitByte: printf2("byte [bp%+d]", truncInt(val)); break;
    case X86OpIndLocalExplicitWord: printf2("word [bp%+d]", truncInt(val)); break;
    case X86OpIndRegB: printf2("[bx]"); break;
    case X86OpIndRegBExplicitByte: printf2("byte [bx]"); break;
    case X86OpIndRegBExplicitWord: printf2("word [bx]"); break;
    }
  }
#ifdef CAN_COMPILE_32BIT
  else
  {
    char* frame = (OutputFormat == FormatSegHuge || OutputFormat == FormatSegUnreal) ? "bp" : "ebp";
    char* stk = (OutputFormat == FormatSegHuge || OutputFormat == FormatSegUnreal) ? "sp" : "esp";
    char* base = (OutputFormat == FormatSegHuge) ? "si" : "ebx";
    char* adrsz = (OutputFormat == FormatSegUnreal) ? "dword " : "";
    switch (op)
    {
    case X86OpRegAByte: printf2("al"); break;
    case X86OpRegAByteHigh: printf2("ah"); break;
    case X86OpRegCByte: printf2("cl"); break;
    case X86OpRegAWord: printf2("eax"); break;
    case X86OpRegBWord: printf2("ebx"); break;
    case X86OpRegCWord: printf2("ecx"); break;
    case X86OpRegDWord: printf2("edx"); break;
    case X86OpRegAHalfWord: printf2("ax"); break;
    case X86OpRegCHalfWord: printf2("cx"); break;
    case X86OpRegBpWord: printf2("ebp"); break;
    case X86OpRegSpWord: printf2(stk); break;
    case X86OpConst: printf2("%d", truncInt(val)); break;
    case X86OpLabel: GenPrintLabel(IdentTable + val); break;
    case X86OpNumLabel: GenPrintNumLabel(val); break;
    case X86OpIndLabel: printf2("[%s", adrsz); GenPrintLabel(IdentTable + val); printf2("]"); break;
    case X86OpIndLabelExplicitByte: printf2("byte [%s", adrsz); GenPrintLabel(IdentTable + val); printf2("]"); break;
    case X86OpIndLabelExplicitWord: printf2("dword [%s", adrsz); GenPrintLabel(IdentTable + val); printf2("]"); break;
    case X86OpIndLabelExplicitHalfWord: printf2("word [%s", adrsz); GenPrintLabel(IdentTable + val); printf2("]"); break;
    case X86OpIndLocal: printf2("[%s%+d]", frame, truncInt(val)); break;
    case X86OpIndLocalExplicitByte: printf2("byte [%s%+d]", frame, truncInt(val)); break;
    case X86OpIndLocalExplicitWord: printf2("dword [%s%+d]", frame, truncInt(val)); break;
    case X86OpIndLocalExplicitHalfWord: printf2("word [%s%+d]", frame, truncInt(val)); break;
    case X86OpIndRegB: printf2("[%s]", base); break;
    case X86OpIndRegBExplicitByte: printf2("byte [%s]", base); break;
    case X86OpIndRegBExplicitWord: printf2("dword [%s]", base); break;
    case X86OpIndRegBExplicitHalfWord: printf2("word [%s]", base); break;
    }
  }
#endif
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

#ifdef CAN_COMPILE_32BIT
STATIC
void GenRegB2Seg(void)
{
  if (OutputFormat == FormatSegHuge)
    puts2("\tmov\tesi, ebx\n\tror\tesi, 4\n\tmov\tds, si\n\tshr\tesi, 28");
}
#endif

STATIC
void GenPrintInstr1Operand(int instr, int instrval, int operand, int operandval)
{
#ifdef CAN_COMPILE_32BIT
  if (instr == X86InstrPush && (OutputFormat == FormatSegHuge || OutputFormat == FormatSegUnreal))
  {
    if (operand == X86OpConst)
    {
      printf2("\tpush\tdword %d\n", truncInt(operandval));
      return;
    }
    else if (operand == X86OpLabel)
    {
      if (OutputFormat == FormatSegHuge)
      {
        int lab = LabelCnt++;
        printf2("section .relod\n\tdd\t"); GenPrintNumLabel(lab); puts2("");
        puts2(CodeHeaderFooter[0]);
        puts2("\tdb\t0x66, 0x68"); // push dword const
        GenNumLabel(lab);
        printf2("\tdd\t"); GenPrintLabel(IdentTable + operandval); puts2("");
      }
      else
      {
        printf2("\tpush\tdword "); GenPrintLabel(IdentTable + operandval); puts2("");
      }
      return;
    }
  }
#endif

  GenPrintInstr(instr, instrval);
  GenPrintOperand(operand, operandval);
  GenPrintNewLine();
}

STATIC
void GenPrintInstr2Operands(int instr, int instrval, int operand1, int operand1val, int operand2, int operand2val)
{
  if (operand2 == X86OpConst && truncUint(operand2val) == 0 &&
      (instr == X86InstrAdd || instr == X86InstrSub))
    return;

#ifdef CAN_COMPILE_32BIT
  if (OutputFormat == FormatSegHuge || OutputFormat == FormatSegUnreal)
  {
    if (instr == X86InstrLea)
    {
      if (operand2 == X86OpIndLocal)
      {
        if (operand1 == X86OpRegAWord)
        {
          puts2("\txor\teax, eax\n\tmov\tax, ss"); // mov r32, sreg leaves top 16 bits undefined on pre-Pentium CPUs
          printf2("\tshl\teax, 4\n\tlea\teax, [ebp+eax%+d]\n", truncInt(operand2val));
          return;
        }
        else if (operand1 == X86OpRegCWord)
        {
          puts2("\txor\tecx, ecx\n\tmov\tcx, ss"); // mov r32, sreg leaves top 16 bits undefined on pre-Pentium CPUs
          printf2("\tshl\tecx, 4\n\tlea\tecx, [ebp+ecx%+d]\n", truncInt(operand2val));
          return;
        }
      }
      errorInternal(106);
    }
    if (instr == X86InstrMov && OutputFormat == FormatSegHuge)
    {
      if (operand1 == X86OpRegAWord && operand2 == X86OpLabel)
      {
        int lab = LabelCnt++;
        printf2("section .relod\n\tdd\t"); GenPrintNumLabel(lab); puts2("");
        puts2(CodeHeaderFooter[0]);
        puts2("\tdb\t0x66, 0xB8"); // mov eax, const
        GenNumLabel(lab);
        printf2("\tdd\t"); GenPrintLabel(IdentTable + operand2val); puts2("");
        return;
      }
    }
  }
#endif

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
  if (SizeOfWord == 2)
  {
    if (opSz == -1)
      GenPrintInstrNoOperand(X86InstrCbw);
    else if (opSz == 1)
      GenPrintInstr2Operands(X86InstrMov, 0,
                             X86OpRegAByteHigh, 0,
                             X86OpConst, 0);
  }
#ifdef CAN_COMPILE_32BIT
  else
  {
    if (opSz == -1)
      GenPrintInstr2Operands(X86InstrMovSx, 0,
                             X86OpRegAWord, 0,
                             X86OpRegAByte, 0);
    else if (opSz == 1)
      GenPrintInstr2Operands(X86InstrMovZx, 0,
                             X86OpRegAWord, 0,
                             X86OpRegAByte, 0);
    else if (opSz == -2)
      GenPrintInstr2Operands(X86InstrMovSx, 0,
                             X86OpRegAWord, 0,
                             X86OpRegAHalfWord, 0);
    else if (opSz == 2)
      GenPrintInstr2Operands(X86InstrMovZx, 0,
                             X86OpRegAWord, 0,
                             X86OpRegAHalfWord, 0);
  }
#endif
}

STATIC
void GenJumpUncond(int label)
{
  GenPrintInstr1Operand(X86InstrJmp, 0,
                        X86OpNumLabel, label);
}

STATIC
void GenJumpIfEqual(int val, int label)
{
  GenPrintInstr2Operands(X86InstrCmp, 0,
                         X86OpRegAWord, 0,
                         X86OpConst, val);
  GenPrintInstr1Operand(X86InstrJcc, tokEQ,
                        X86OpNumLabel, label);
}

STATIC
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

STATIC
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

fpos_t GenPrologPos;

STATIC
void GenWriteFrameSize(void)
{
  unsigned size = -CurFxnMinLocalOfs;
  int pfx = size ? ' ' : ';';
#ifdef CAN_COMPILE_32BIT
  if (SizeOfWord == 4 &&
      OutputFormat != FormatSegHuge &&
      OutputFormat != FormatSegUnreal &&
      WindowsStack)
  {
    int pfx = (size >= 4096) ? ' ' : ';';
    // When targeting Windows, call equivalent of _chkstk() to
    // correctly grow the stack page by page by probing it
    if (!WinChkStkLabel)
      WinChkStkLabel = -LabelCnt++; // reserve a label for _chkstk() and mark unused
    if (WinChkStkLabel < 0 && pfx == ' ')
      WinChkStkLabel = -WinChkStkLabel; // _chkstk() has been used at least once

    printf2("\t%cmov\teax, %10u\n", pfx, size); // 10 chars are enough for 32-bit unsigned ints
    printf2("\t%ccall\t", pfx);
    GenPrintNumLabel((WinChkStkLabel < 0) ? -WinChkStkLabel : WinChkStkLabel);
    puts2("");
  }
#endif
  if (SizeOfWord == 2 || OutputFormat == FormatSegHuge || OutputFormat == FormatSegUnreal)
    printf2("\t%csub\tsp, %10u\n", pfx, size); // 10 chars are enough for 32-bit unsigned ints
#ifdef CAN_COMPILE_32BIT
  else
    printf2("\t%csub\tesp, %10u\n", pfx, size); // 10 chars are enough for 32-bit unsigned ints
#endif
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
  GenPrintInstr1Operand(X86InstrPush, 0,
                        X86OpRegBpWord, 0);
#ifdef CAN_COMPILE_32BIT
  if (OutputFormat == FormatSegHuge || OutputFormat == FormatSegUnreal)
    puts2("\tmovzx\tebp, sp");
  else
#endif
    GenPrintInstr2Operands(X86InstrMov, 0,
                           X86OpRegBpWord, 0,
                           X86OpRegSpWord, 0);
  fgetpos(OutFile, &GenPrologPos);
  GenWriteFrameSize();
}

STATIC
void GenGrowStack(int size)
{
  if (!size)
    return;
  GenPrintInstr2Operands(X86InstrSub, 0,
                         X86OpRegSpWord, 0,
                         X86OpConst, size);
}

STATIC
void GenFxnEpilog(void)
{
  GenUpdateFrameSize();
  if(Use8086InstrOnly)
  {
    GenPrintInstr2Operands(X86InstrMov,0,
                          X86OpRegSpWord, 0,
                          X86OpRegBpWord, 0);
    GenPrintInstr1Operand(X86InstrPop,0,
                          X86OpRegBpWord, 0);
  }
  else
  {
    GenPrintInstrNoOperand(X86InstrLeave);
  }
  GenPrintInstrNoOperand(X86InstrRet);
}

STATIC
int GenMaxLocalsSize(void)
{
#ifdef CAN_COMPILE_32BIT
  if (SizeOfWord == 4 && OutputFormat != FormatSegHuge && OutputFormat != FormatSegUnreal)
    return 0x7FFFFFFF;
#endif
  return 0x7FFF;
}

#ifdef CAN_COMPILE_32BIT
/*
struct INTREGS
{
  unsigned short gs, fs, es, ds;
  unsigned edi, esi, ebp, esp, ebx, edx, ecx, eax;
  unsigned short ss, ip, cs, flags;
};
void __interrupt isr(struct INTREGS** ppRegs)
{
  // **ppRegs (input/output values of registers) can be modified to
  // handle software interrupts requested via the int instruction and
  // communicate data via registers

  // *ppRegs (directly related to the stack pointer) can be modified to
  // return to a different location & implement preemptive scheduling,
  // e.g. save *ppRegs of the interrupted task somewhere, update *ppRegs
  // with a value from another interrupted task.
}
*/
void GenIsrProlog(void)
{
  // The CPU has already done these:
  //   push flags
  //   push cs
  //   push ip

  puts2("\tpush\tss");
  puts2("\tpushad");
  puts2("\tpush\tds\n"
        "\tpush\tes\n"
        "\tpush\tfs\n"
        "\tpush\tgs");

  // The context has been saved

  puts2("\txor\teax, eax");
  if (OutputFormat == FormatSegUnreal)
    puts2("\tmov\tds, ax\n\tmov\tes, ax");
  puts2("\tmov\tax, ss"); // mov r32, sreg leaves top 16 bits undefined on pre-Pentium CPUs
  puts2("\tmovzx\tebx, sp"); // top 16 bits of esp can contain garbage as well
  puts2("\tshl\teax, 4\n\tadd\teax, ebx");
  puts2("\tpush\teax"); // pointer to the structure with register values
  puts2("\tsub\teax, 4\n\tpush\teax"); // pointer to the pointer to the structure with register values

  puts2("\tpush\teax"); // fake return address allowing to use the existing bp-relative addressing of locals and params

  puts2("\tpush\tebp\n"
        "\tmovzx\tebp, sp");
  fgetpos(OutFile, &GenPrologPos);
  GenWriteFrameSize();
}

void GenIsrEpilog(void)
{
  GenUpdateFrameSize();
  puts2("\tdb\t0x66\n\tleave");

  puts2("\tpop\teax"); // fake return address

  puts2("\tpop\teax"); // pointer to the pointer to the structure with register values
  puts2("\tpop\tebx"); // pointer to the structure with register values
  puts2("\tror\tebx, 4\n\tmov\tds, bx\n\tshr\tebx, 28"); // ds:bx = pointer to the structure with register values
  puts2("\tmov\tax, [bx+4*10]\n\tmov\tbx, [bx+4*5]\n\tsub\tbx, 4*10"); // ax:bx = proper pointer (with original segment) to the struct...
  puts2("\tmov\tss, ax\n\tmov\tsp, bx"); // restore ss:sp that we had after push gs

  // The context is now going to be restored

  puts2("\tpop\tgs\n"
        "\tpop\tfs\n"
        "\tpop\tes\n"
        "\tpop\tds");
  puts2("\tpopad");
  puts2("\tpop\tss");

  puts2("\tiret");
}
#endif

STATIC
void GenReadIdent(int opSz, int label)
{
  GenPrintInstr2Operands(X86InstrMov, 0,
                         GenSelectByteOrWord(X86OpRegAByteOrWord, opSz), 0,
                         X86OpIndLabel, label);
  GenExtendRegAIfNeeded(opSz);
}

STATIC
void GenReadLocal(int opSz, int ofs)
{
  GenPrintInstr2Operands(X86InstrMov, 0,
                         GenSelectByteOrWord(X86OpRegAByteOrWord, opSz), 0,
                         X86OpIndLocal, ofs);
  GenExtendRegAIfNeeded(opSz);
}

STATIC
void GenReadIndirect(int opSz)
{
  GenPrintInstr2Operands(X86InstrMov, 0,
                         X86OpRegBWord, 0,
                         X86OpRegAWord, 0);
#ifdef CAN_COMPILE_32BIT
  GenRegB2Seg();
#endif
  GenPrintInstr2Operands(X86InstrMov, 0,
                         GenSelectByteOrWord(X86OpRegAByteOrWord, opSz), 0,
                         X86OpIndRegB, 0);
  GenExtendRegAIfNeeded(opSz);
}

STATIC
void GenReadCRegIdent(int opSz, int label)
{
  if (opSz == -1)
  {
    if(Use8086InstrOnly)
    {

      GenPrintInstr1Operand(X86InstrPush, 0,
                            X86OpRegAWord, 0);
      GenPrintInstr2Operands(X86InstrMov, 0,
                            X86OpRegAByte, 0,
                            X86OpIndLabelExplicitByte, label);
      GenPrintInstrNoOperand(X86InstrCbw);
      GenPrintInstr2Operands(X86InstrMov, 0,
                            X86OpRegCWord, 0,
                            X86OpRegAWord, 0);
      GenPrintInstr1Operand(X86InstrPop, 0,
                            X86OpRegAWord, 0);
    }
    else
    {
      GenPrintInstr2Operands(X86InstrMovSx, 0,
                            X86OpRegCWord, 0,
                            X86OpIndLabelExplicitByte, label);
    }
  }
  else if (opSz == 1)
  {
    if(Use8086InstrOnly)
    {
      GenPrintInstr2Operands(X86InstrMov, 0,
                            X86OpRegCByte, 0,
                            X86OpIndLabelExplicitByte, label);
      GenPrintInstr2Operands(X86InstrXor, 0,
                            X86OpRegCByteHigh, 0,
                            X86OpRegCByteHigh, 0);
    }
    else
    {
      GenPrintInstr2Operands(X86InstrMovZx, 0,
                            X86OpRegCWord, 0,
                            X86OpIndLabelExplicitByte, label);
    }
  }
#ifdef CAN_COMPILE_32BIT
  else if (opSz != SizeOfWord && -opSz != SizeOfWord)
  {
    if (opSz == -2)
      GenPrintInstr2Operands(X86InstrMovSx, 0,
                             X86OpRegCWord, 0,
                             X86OpIndLabelExplicitHalfWord, label);
    else if (opSz == 2)
      GenPrintInstr2Operands(X86InstrMovZx, 0,
                             X86OpRegCWord, 0,
                             X86OpIndLabelExplicitHalfWord, label);
  }
#endif
  else
    GenPrintInstr2Operands(X86InstrMov, 0,
                           X86OpRegCWord, 0,
                           X86OpIndLabel, label);
}

STATIC
void GenReadCRegLocal(int opSz, int ofs)
{
  if (opSz == -1)
    if(Use8086InstrOnly)
    {

      GenPrintInstr1Operand(X86InstrPush, 0,
                            X86OpRegAWord, 0);
      GenPrintInstr2Operands(X86InstrMov, 0,
                            X86OpRegAByte, 0,
                            X86OpIndLocalExplicitByte, ofs);
      GenPrintInstrNoOperand(X86InstrCbw);
      GenPrintInstr2Operands(X86InstrMov, 0,
                            X86OpRegCWord, 0,
                            X86OpRegAWord, 0);
      GenPrintInstr1Operand(X86InstrPop, 0,
                            X86OpRegAWord, 0);
    }
    else
    {
      GenPrintInstr2Operands(X86InstrMovSx, 0,
                            X86OpRegCWord, 0,
                            X86OpIndLocalExplicitByte, ofs);
    }
  else if (opSz == 1)
    if(Use8086InstrOnly)
    {
      GenPrintInstr2Operands(X86InstrMov, 0,
                            X86OpRegCByte, 0,
                            X86OpIndLocalExplicitByte, ofs);
      GenPrintInstr2Operands(X86InstrXor, 0,
                            X86OpRegCByteHigh, 0,
                            X86OpRegCByteHigh, 0);
    }
    else
    {
      GenPrintInstr2Operands(X86InstrMovZx, 0,
                            X86OpRegCWord, 0,
                            X86OpIndLocalExplicitByte, ofs);
    }
#ifdef CAN_COMPILE_32BIT
  else if (opSz != SizeOfWord && -opSz != SizeOfWord)
  {
    if (opSz == -2)
      GenPrintInstr2Operands(X86InstrMovSx, 0,
                             X86OpRegCWord, 0,
                             X86OpIndLocalExplicitHalfWord, ofs);
    else if (opSz == 2)
      GenPrintInstr2Operands(X86InstrMovZx, 0,
                             X86OpRegCWord, 0,
                             X86OpIndLocalExplicitHalfWord, ofs);
  }
#endif
  else
    GenPrintInstr2Operands(X86InstrMov, 0,
                           X86OpRegCWord, 0,
                           X86OpIndLocal, ofs);
}

STATIC
void GenReadCRegIndirect(int opSz)
{
  GenPrintInstr2Operands(X86InstrMov, 0,
                         X86OpRegBWord, 0,
                         X86OpRegAWord, 0);
#ifdef CAN_COMPILE_32BIT
  GenRegB2Seg();
#endif
  if (opSz == -1)
    if(Use8086InstrOnly)
    {

      GenPrintInstr1Operand(X86InstrPush, 0,
                            X86OpRegAWord, 0);
      GenPrintInstr2Operands(X86InstrMov, 0,
                            X86OpRegAByte, 0,
                            X86OpIndRegBExplicitByte, 0);
      GenPrintInstrNoOperand(X86InstrCbw);
      GenPrintInstr2Operands(X86InstrMov, 0,
                            X86OpRegCWord, 0,
                            X86OpRegAWord, 0);
      GenPrintInstr1Operand(X86InstrPop, 0,
                            X86OpRegAWord, 0);
    }
    else
    {
      GenPrintInstr2Operands(X86InstrMovSx, 0,
                            X86OpRegCWord, 0,
                            X86OpIndRegBExplicitByte, 0);
    }
  else if (opSz == 1)
    if(Use8086InstrOnly)
    {
      GenPrintInstr2Operands(X86InstrMov, 0,
                            X86OpRegCByte, 0,
                            X86OpIndRegBExplicitByte, 0);
      GenPrintInstr2Operands(X86InstrXor, 0,
                            X86OpRegCByteHigh, 0,
                            X86OpRegCByteHigh, 0);
    }
    else
    {
      GenPrintInstr2Operands(X86InstrMovZx, 0,
                            X86OpRegCWord, 0,
                            X86OpIndRegBExplicitByte, 0);
    }
#ifdef CAN_COMPILE_32BIT
  else if (opSz != SizeOfWord && -opSz != SizeOfWord)
  {
    if (opSz == -2)
      GenPrintInstr2Operands(X86InstrMovSx, 0,
                             X86OpRegCWord, 0,
                             X86OpIndRegBExplicitHalfWord, 0);
    else if (opSz == 2)
      GenPrintInstr2Operands(X86InstrMovZx, 0,
                             X86OpRegCWord, 0,
                             X86OpIndRegBExplicitHalfWord, 0);
  }
#endif
  else
    GenPrintInstr2Operands(X86InstrMov, 0,
                           X86OpRegCWord, 0,
                           X86OpIndRegB, 0);
}

STATIC
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

STATIC
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

STATIC
void GenIncDecIndirect(int opSz, int tok)
{
  int instr = X86InstrInc;

  if (tok != tokInc)
    instr = X86InstrDec;

  GenPrintInstr2Operands(X86InstrMov, 0,
                         X86OpRegBWord, 0,
                         X86OpRegAWord, 0);
#ifdef CAN_COMPILE_32BIT
  GenRegB2Seg();
#endif
  GenPrintInstr1Operand(instr, 0,
                        GenSelectByteOrWord(X86OpIndRegBExplicitByteOrWord, opSz), 0);
  GenPrintInstr2Operands(X86InstrMov, 0,
                         GenSelectByteOrWord(X86OpRegAByteOrWord, opSz), 0,
                         X86OpIndRegB, 0);
  GenExtendRegAIfNeeded(opSz);
}

STATIC
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

STATIC
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

STATIC
void GenPostIncDecIndirect(int opSz, int tok)
{
  int instr = X86InstrInc;

  if (tok != tokPostInc)
    instr = X86InstrDec;

  GenPrintInstr2Operands(X86InstrMov, 0,
                         X86OpRegBWord, 0,
                         X86OpRegAWord, 0);
#ifdef CAN_COMPILE_32BIT
  GenRegB2Seg();
#endif
  GenPrintInstr2Operands(X86InstrMov, 0,
                         GenSelectByteOrWord(X86OpRegAByteOrWord, opSz), 0,
                         X86OpIndRegB, 0);
  GenExtendRegAIfNeeded(opSz);
  GenPrintInstr1Operand(instr, 0,
                        GenSelectByteOrWord(X86OpIndRegBExplicitByteOrWord, opSz), 0);
}

STATIC
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

STATIC
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

STATIC
void GenPostAddSubIndirect(int opSz, int val, int tok)
{
  int instr = X86InstrAdd;

  if (tok != tokPostAdd)
    instr = X86InstrSub;

  GenPrintInstr2Operands(X86InstrMov, 0,
                         X86OpRegBWord, 0,
                         X86OpRegAWord, 0);
#ifdef CAN_COMPILE_32BIT
  GenRegB2Seg();
#endif
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
#ifdef CAN_COMPILE_32BIT
      if (OutputFormat == FormatSegHuge)
        goto l1;
#endif
      return tokOpIndIdent;
    case tokLocalOfs:
      return tokOpIndLocalOfs;

    default:
#ifdef CAN_COMPILE_32BIT
l1:
#endif
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
#ifdef CAN_COMPILE_32BIT
    if (OutputFormat == FormatSegHuge)
      goto l2;
#endif
    return tokOpIdent;
  case tokLocalOfs:
    return tokOpLocalOfs;

  default:
#ifdef CAN_COMPILE_32BIT
l2:
#endif
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
#ifdef CAN_COMPILE_32BIT
      if (OutputFormat == FormatSegHuge)
        goto l1;
#endif
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
#ifdef CAN_COMPILE_32BIT
l1:
#endif
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
#ifdef CAN_COMPILE_32BIT
      if (OutputFormat == FormatSegHuge)
        goto l2;
#endif
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
#ifdef CAN_COMPILE_32BIT
l2:
#endif
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
#ifdef CAN_COMPILE_32BIT
  case tokShort:
  case tokUShort:
#endif
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
#ifdef CAN_COMPILE_32BIT
      if (OutputFormat == FormatSegHuge)
        goto l3;
#endif
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
#ifdef CAN_COMPILE_32BIT
l3:
#endif
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
      if(Use8086InstrOnly)
      {
        int labelCC = LabelCnt++;
        int labelCCAfter = LabelCnt++;
        GenPrintInstr1Operand(X86InstrJcc, tokNEQ,
                              X86OpNumLabel, labelCC);
        GenPrintInstr2Operands(X86InstrMov, 0,
                              X86OpRegAByte, 0,
                              X86OpConst, 0);
        GenPrintInstr1Operand(X86InstrJmp, 0,
                              X86OpNumLabel, labelCCAfter);
        GenNumLabel(labelCC);
        GenPrintInstr2Operands(X86InstrMov, 0,
                              X86OpRegAByte, 0,
                              X86OpConst, 1);
        GenNumLabel(labelCCAfter);
      }
      else
      {
        GenPrintInstr1Operand(X86InstrSetCc, tokNEQ,
                              X86OpRegAByte, 0);
      }
      // fallthrough
    case tokSChar:
      if (SizeOfWord == 2)
        GenPrintInstrNoOperand(X86InstrCbw);
#ifdef CAN_COMPILE_32BIT
      else
        GenPrintInstr2Operands(X86InstrMovSx, 0,
                               X86OpRegAWord, 0,
                               X86OpRegAByte, 0);
#endif
      break;
    case tokUChar:
      GenPrintInstr2Operands(X86InstrAnd, 0,
                             X86OpRegAWord, 0,
                             X86OpConst, 0xFF);
      break;
#ifdef CAN_COMPILE_32BIT
    case tokShort:
      GenPrintInstr2Operands(X86InstrMovSx, 0,
                             X86OpRegAWord, 0,
                             X86OpRegAHalfWord, 0);
      break;
    case tokUShort:
      GenPrintInstr2Operands(X86InstrMovZx, 0,
                             X86OpRegAWord, 0,
                             X86OpRegAHalfWord, 0);
      break;
#endif

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
      GenPrintInstr1Operand(X86InstrPush, 0,
                            X86OpRegAWord, 0);
      break;

    case ',':
      // push operand directly if it hasn't been loaded into ax
      if (stack[i - 2][0] == tokUnaryStar && stack[i - 2][1] == SizeOfWord)
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
#ifdef CAN_COMPILE_32BIT
          GenRegB2Seg();
#endif
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
          if(Use8086InstrOnly)
          {
            GenPrintInstr2Operands(X86InstrMov, 0,
                                  X86OpRegAWord, 0,
                                  X86OpConst, stack[i - 1][1]);
            GenPrintInstr1Operand(X86InstrPush, 0,
                                  X86OpRegAWord, 0);
          }
          else
          {
            GenPrintInstr1Operand(X86InstrPush, 0,
                                  X86OpConst, stack[i - 1][1]);
          }
          break;
        case tokIdent:
          if(Use8086InstrOnly)
          {
            GenPrintInstr2Operands(X86InstrMov, 0,
                                  X86OpRegAWord, 0,
                                  X86OpLabel, stack[i - 1][1]);
            GenPrintInstr1Operand(X86InstrPush, 0,
                                  X86OpRegAWord, 0);
          }
          else
          {
            GenPrintInstr1Operand(X86InstrPush, 0,
                                  X86OpLabel, stack[i - 1][1]);
          }
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
          GenPrintInstr2Operands(X86InstrMov, 0,
                                 X86OpRegCWord, 0,
                                 X86OpRegAWord, 0);
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
        GenReadIdent(v / 16 - 8, stack[i + 1][1]);
        break;
      case tokOpIndLocalOfs:
        GenReadLocal(v / 16 - 8, stack[i + 1][1]);
        break;
      case tokOpIndAcc:
        GenReadIndirect(v / 16 - 8);
        break;
      case tokOpStack:
        GenPrintInstr1Operand(X86InstrPop, 0,
                              X86OpRegAWord, 0);
        break;
      case tokOpIndStack:
        GenPrintInstr1Operand(X86InstrPop, 0,
                              X86OpRegBWord, 0);
#ifdef CAN_COMPILE_32BIT
        GenRegB2Seg();
#endif
        GenPrintInstr2Operands(X86InstrMov, 0,
                               GenSelectByteOrWord(X86OpRegAByteOrWord, v / 16 - 8), 0,
                               X86OpIndRegB, 0);
        GenExtendRegAIfNeeded(v / 16 - 8);
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
          if (v % 16 - 8 != SizeOfWord)
          {
            GenReadCRegIdent(v % 16 - 8, stack[i + 2][1]);
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
          if (v % 16 - 8 != SizeOfWord)
          {
            GenReadCRegLocal(v % 16 - 8, stack[i + 2][1]);
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
            if(Use8086InstrOnly)
            {
              int labelCC = LabelCnt++;
              int labelCCAfter = LabelCnt++;
              GenPrintInstr1Operand(X86InstrJcc, tok,
                                    X86OpNumLabel, labelCC);
              GenPrintInstr2Operands(X86InstrMov, 0,
                                    X86OpRegAByte, 0,
                                    X86OpConst, 0);
              GenPrintInstr1Operand(X86InstrJmp, 0,
                                    X86OpNumLabel, labelCCAfter);
              GenNumLabel(labelCC);
              GenPrintInstr2Operands(X86InstrMov, 0,
                                    X86OpRegAByte, 0,
                                    X86OpConst, 1);
              GenNumLabel(labelCCAfter);
            }
            else
            {
              GenPrintInstr1Operand(X86InstrSetCc, tok,
                                    X86OpRegAByte, 0);
            }
            if (SizeOfWord == 2)
              GenPrintInstrNoOperand(X86InstrCbw);
#ifdef CAN_COMPILE_32BIT
            else
              GenPrintInstr2Operands(X86InstrMovZx, 0,
                                     X86OpRegAWord, 0,
                                     X86OpRegAByte, 0);
#endif
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
          if(Use8086InstrOnly)
          {
            GenPrintInstr2Operands(X86InstrMov, 0,
                                  X86OpRegBWord, 0,
                                  X86OpConst, stack[i + 2][1]);
            GenPrintInstr1Operand(X86InstrImul, 0,
                                  X86OpRegBWord, 0);
          }
          else
          {
            GenPrintInstr3Operands(X86InstrImul, 0,
                                  X86OpRegAWord, 0,
                                  X86OpRegAWord, 0,
                                  X86OpConst, stack[i + 2][1]);
          }
          break;
        case tokOpIdent:
          if(Use8086InstrOnly)
          {
            GenPrintInstr2Operands(X86InstrMov, 0,
                                  X86OpRegBWord, 0,
                                  X86OpLabel, stack[i + 2][1]);
            GenPrintInstr1Operand(X86InstrImul, 0,
                                  X86OpRegBWord, 0);
          }
          else
          {
            GenPrintInstr3Operands(X86InstrImul, 0,
                                  X86OpRegAWord, 0,
                                  X86OpRegAWord, 0,
                                  X86OpLabel, stack[i + 2][1]);
          }
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
          if (v % 16 - 8 != SizeOfWord)
          {
            GenReadCRegIdent(v % 16 - 8, stack[i + 2][1]);
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
          if (v % 16 - 8 != SizeOfWord)
          {
            GenReadCRegLocal(v % 16 - 8, stack[i + 2][1]);
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
#ifdef CAN_COMPILE_32BIT
          else
            GenPrintInstrNoOperand(X86InstrCdq);
#endif
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
          if (v % 16 - 8 != SizeOfWord)
          {
            GenReadCRegIdent(v % 16 - 8, stack[i + 2][1]);
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
          if (v % 16 - 8 != SizeOfWord)
          {
            GenReadCRegLocal(v % 16 - 8, stack[i + 2][1]);
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
          if(Use8086InstrOnly)
          {
            GenPrintInstr2Operands(X86InstrMov, 0,
                                  X86OpRegCByte, 0,
                                  X86OpConst, stack[i + 2][1]);
            GenPrintInstr2Operands(instr, 0,
                                  X86OpRegAWord, 0,
                                  X86OpRegCByte, 0);
          }
          else
          {
            GenPrintInstr2Operands(instr, 0,
                                  X86OpRegAWord, 0,
                                  X86OpConst, stack[i + 2][1]);
          }
          break;
        case tokOpIdent:
          if(Use8086InstrOnly)
          {
            GenPrintInstr2Operands(X86InstrMov, 0,
                                  X86OpRegCByte, 0,
                                  X86OpLabel, stack[i + 2][1]);
            GenPrintInstr2Operands(instr, 0,
                                  X86OpRegAWord, 0,
                                  X86OpRegCByte, 0);
          }
          else
          {
            GenPrintInstr2Operands(instr, 0,
                                  X86OpRegAWord, 0,
                                  X86OpLabel, stack[i + 2][1]);
          }
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
          GenPrintInstr2Operands(X86InstrMov, 0,
                                 X86OpIndLabel, stack[i + 1][1],
                                 GenSelectByteOrWord(X86OpRegAByteOrWord, v / 16 - 8), 0);
          break;
        case tokOpIndLocalOfs:
          GenPrintInstr2Operands(X86InstrMov, 0,
                                 X86OpIndLocal, stack[i + 1][1],
                                 GenSelectByteOrWord(X86OpRegAByteOrWord, v / 16 - 8), 0);
          break;
        case tokOpIndAcc:
        case tokOpIndStack:
#ifdef CAN_COMPILE_32BIT
          GenRegB2Seg();
#endif
          GenPrintInstr2Operands(X86InstrMov, 0,
                                 X86OpIndRegB, 0,
                                 GenSelectByteOrWord(X86OpRegAByteOrWord, v / 16 - 8), 0);
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
#ifdef CAN_COMPILE_32BIT
        if (OutputFormat == FormatSegHuge || OutputFormat == FormatSegUnreal)
        {
          int lab = LabelCnt++;
          puts2("\tdb\t0x9A"); // call far seg:ofs
          printf2("section .relot\n\tdd\t"); GenPrintNumLabel(lab); puts2("");
          puts2(CodeHeaderFooter[0]);
          GenNumLabel(lab);
          printf2("\tdd\t"); GenPrintLabel(IdentTable + stack[i - 1][1]); puts2("");
        }
        else // fallthrough
#endif
          GenPrintInstr1Operand(X86InstrCall, 0,
                                X86OpLabel, stack[i - 1][1]);
      }
      else
      {
#ifdef CAN_COMPILE_32BIT
        if (OutputFormat == FormatSegHuge || OutputFormat == FormatSegUnreal)
        {
          // TBD??? replace this call with "push cs" + "call near16 $+3" and reduce .text and .relot size.
          int lab = (LabelCnt += 3) - 3;
          puts2("\tdb\t0x9A"); // call far seg:ofs (only to generate return address)
          printf2("section .relot\n\tdd\t"); GenPrintNumLabel(lab); puts2("");
          puts2(CodeHeaderFooter[0]);
          GenNumLabel(lab);
          printf2("\tdd\t"); GenPrintNumLabel(lab + 1); puts2("");
          GenNumLabel(lab + 1);
          puts2("\tmov\tsi, sp");
          printf2("\tadd\tword [ss:si], "); GenPrintNumLabel(lab + 2); printf2(" - "); GenPrintNumLabel(lab + 1); puts2(""); // adjust return address
          puts2("\tshl\teax, 12\n\trol\tax, 4\n\tpush\teax\n\tretf");
          GenNumLabel(lab + 2);
        }
        else // fallthrough
#endif
          GenPrintInstr1Operand(X86InstrCall, 0,
                                X86OpRegAWord, 0);
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
#ifdef CAN_COMPILE_32BIT
      if (OutputFormat == FormatSegHuge || OutputFormat == FormatSegUnreal)
      {
        // TBD??? replace this call with "push cs" + "call near16 $+3" and reduce .text and .relot size.
        int lab = (LabelCnt += 3) - 3;
        puts2("\tdb\t0x9A"); // call far seg:ofs (only to generate return address)
        printf2("section .relot\n\tdd\t"); GenPrintNumLabel(lab); puts2("");
        puts2(CodeHeaderFooter[0]);
        GenNumLabel(lab);
        printf2("\tdd\t"); GenPrintNumLabel(lab + 1); puts2("");
        GenNumLabel(lab + 1);
        puts2("\tmov\tsi, sp");
        printf2("\tadd\tword [ss:si], "); GenPrintNumLabel(lab + 2); printf2(" - "); GenPrintNumLabel(lab + 1); puts2(""); // adjust return address
        puts2("\tshl\teax, 12\n\trol\tax, 4\n\tpush\teax\n\tretf");
        GenNumLabel(lab + 2);
      }
      else // fallthrough
#endif
        GenPrintInstr1Operand(X86InstrCall, 0,
                              X86OpRegAWord, 0);
      GenGrowStack(-v);
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
#ifdef CAN_COMPILE_32BIT
        else
          GenPrintInstrNoOperand(X86InstrCdq);
#endif
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
#ifdef CAN_COMPILE_32BIT
        GenRegB2Seg();
#endif
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
#ifdef CAN_COMPILE_32BIT
        GenRegB2Seg();
#endif
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
#ifdef CAN_COMPILE_32BIT
      GenRegB2Seg();
#endif
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
#ifdef CAN_COMPILE_32BIT
        else
          GenPrintInstrNoOperand(X86InstrCdq);
#endif
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
#ifdef CAN_COMPILE_32BIT
        GenRegB2Seg();
#endif
        GenPrintInstr2Operands(X86InstrMov, 0,
                               X86OpRegCWord, 0,
                               X86OpRegAWord, 0);
        GenPrintInstr2Operands(X86InstrMov, 0,
                               GenSelectByteOrWord(X86OpRegAByteOrWord, v), 0,
                               X86OpIndRegB, 0);
        GenExtendRegAIfNeeded(v);
        GenPrintInstr2Operands(instr, 0,
                               X86OpRegAWord, 0,
                               X86OpRegCByte, 0);
        GenPrintInstr2Operands(X86InstrMov, 0,
                               X86OpIndRegB, 0,
                               GenSelectByteOrWord(X86OpRegAByteOrWord, v), 0);
        GenExtendRegAIfNeeded(v);
      }
      break;

    case '=':
      GenPrintInstr1Operand(X86InstrPop, 0,
                            X86OpRegBWord, 0);
#ifdef CAN_COMPILE_32BIT
      GenRegB2Seg();
#endif
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
#ifdef CAN_COMPILE_32BIT
      else
        GenPrintInstr2Operands(X86InstrMovZx, 0,
                               X86OpRegAWord, 0,
                               X86OpRegAByte, 0);
#endif
      break;

    case tok_Bool:
      GenPrintInstr2Operands(X86InstrTest, 0,
                             X86OpRegAWord, 0,
                             X86OpRegAWord, 0);
      GenPrintInstr1Operand(X86InstrSetCc, tokNEQ,
                            X86OpRegAByte, 0);
      // fallthrough
    case tokSChar:
      if (SizeOfWord == 2)
        GenPrintInstrNoOperand(X86InstrCbw);
#ifdef CAN_COMPILE_32BIT
      else
        GenPrintInstr2Operands(X86InstrMovSx, 0,
                               X86OpRegAWord, 0,
                               X86OpRegAByte, 0);
#endif
      break;
    case tokUChar:
      GenPrintInstr2Operands(X86InstrAnd, 0,
                             X86OpRegAWord, 0,
                             X86OpConst, 0xFF);
      break;
#ifdef CAN_COMPILE_32BIT
    case tokShort:
      GenPrintInstr2Operands(X86InstrMovSx, 0,
                             X86OpRegAWord, 0,
                             X86OpRegAHalfWord, 0);
      break;
    case tokUShort:
      GenPrintInstr2Operands(X86InstrMovZx, 0,
                             X86OpRegAWord, 0,
                             X86OpRegAHalfWord, 0);
      break;
#endif

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

    if (SizeOfWord == 2)
    {
      puts2("\tmov\tdi, [bp+8]\n"
            "\tmov\tsi, [bp+6]\n"
            "\tmov\tcx, [bp+4]\n"
            "\tcld\n"
            "\trep\tmovsb\n"
            "\tmov\tax, [bp+8]");
    }
#ifdef CAN_COMPILE_32BIT
    else if (OutputFormat == FormatSegHuge)
    {
      int lbl = (LabelCnt += 2) - 2;

      puts2("\tmov\tedi, [bp+16]\n"
            "\tror\tedi, 4\n"
            "\tmov\tes, di\n"
            "\tshr\tedi, 28\n"
            "\tmov\tesi, [bp+12]\n"
            "\tror\tesi, 4\n"
            "\tmov\tds, si\n"
            "\tshr\tesi, 28");
      puts2("\tmov\tebx, [bp+8]\n"
            "\tcld");

      GenNumLabel(lbl); // L1:

      puts2("\tmov\tecx, 32768\n"
            "\tcmp\tebx, ecx");

      printf2("\tjc\t"); GenPrintNumLabel(lbl + 1); // jc L2

      puts2("\n"
            "\tsub\tebx, ecx\n"
            "\trep\tmovsb\n"
            "\tand\tdi, 15\n"
            "\tmov\tax, es\n"
            "\tadd\tax, 2048\n"
            "\tmov\tes, ax\n"
            "\tand\tsi, 15\n"
            "\tmov\tax, ds\n"
            "\tadd\tax, 2048\n"
            "\tmov\tds, ax");

      printf2("\tjmp\t"); GenPrintNumLabel(lbl); // jmp L1
      puts2("");

      GenNumLabel(lbl + 1); // L2:

      puts2("\tmov\tcx, bx\n"
            "\trep\tmovsb\n"
            "\tmov\teax, [bp+16]");
    }
    else if (OutputFormat == FormatSegUnreal)
    {
      puts2("\tmov\tedi, [bp+16]\n"
            "\tmov\tesi, [bp+12]\n"
            "\tmov\tecx, [bp+8]\n"
            "\tcld\n"
            "\tdb\t0x67\n"
            "\trep\tmovsb\n"
            "\tmov\teax, [bp+16]");
    }
    else
    {
      puts2("\tmov\tedi, [ebp+16]\n"
            "\tmov\tesi, [ebp+12]\n"
            "\tmov\tecx, [ebp+8]\n"
            "\tcld\n"
            "\trep\tmovsb\n"
            "\tmov\teax, [ebp+16]");
    }
#endif

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

    if (SizeOfWord == 2)
    {
      puts2("\tmov\tdx, [bp+2]\n" // dx = return address
            "\tmov\tsi, [bp+4]\n" // si = &struct
            "\tmov\tcx, [bp+6]\n" // cx = sizeof(struct)
            "\tmov\tbp, [bp]\n"   // restore bp

            "\tmov\tax, cx\n"  // ax = sizeof(struct)
            "\tinc\tax\n"      // ax = sizeof(struct) + 1
            "\tand\tax, -2\n"  // ax = sizeof(struct) rounded up to multiple of 2 bytes
            "\tadd\tsp, 4*2\n" // remove bp, return address and 2 args from stack
            "\tsub\tsp, ax");  // allocate stack space for struct
      if (Use8086InstrOnly)
      {
        puts2("\tmov\tdi, sp\n" // di = where struct should be copied to
              "\tcld\n"
              "\trep\tmovsb\n"  // copy

              "\tpop\tax\n"  // return first 2 bytes of struct in ax
              "\tpush\tax\n"
              "\txor\tcx, cx\n" // Set 0 in cx to push (8086 cant push numbers in stack)
              "\tpush\tcx\n"  // caller will remove this 0 and first 2 bytes of struct from stack (as 2 args)
              "\tpush\tdx\n" //   and then it will push ax (first 2 bytes of struct) back
              "\tret");      // actually return to return address saved in dx
      }
      else
      {
        puts2("\tmov\tdi, sp\n" // di = where struct should be copied to
              "\tcld\n"
              "\trep\tmovsb\n"  // copy

              "\tpop\tax\n"  // return first 2 bytes of struct in ax
              "\tpush\tax\n"
              "\tpush\tbyte 0\n"  // caller will remove this 0 and first 2 bytes of struct from stack (as 2 args)
              "\tpush\tdx\n" //   and then it will push ax (first 2 bytes of struct) back
              "\tret");      // actually return to return address saved in dx
      }
    }
#ifdef CAN_COMPILE_32BIT
    else if (OutputFormat == FormatSegHuge)
    {
      puts2("\tmov\tedx, [bp+4]\n"   // edx = return address (seg:ofs)
            "\tmov\tesi, [bp+8]\n"   // esi = &struct (phys)
            "\tror\tesi, 4\n"
            "\tmov\tds, si\n"
            "\tshr\tesi, 28\n"       // ds:si = &struct (seg:ofs)
            "\tmov\tecx, [bp+12]\n"  // ecx = sizeof(struct)
            "\tmov\tebp, [bp]\n"     // restore ebp

            "\tlea\teax, [ecx + 3]\n" // eax = sizeof(struct) + 3
            "\tand\teax, -4\n"        // eax = sizeof(struct) rounded up to multiple of 4 bytes
            "\tsub\tax, 4*4\n"        // remove ebp, return address and 2 args from stack
            "\tsub\tsp, ax\n"         // allocate stack space for struct

            "\tmov\tax, ss\n"
            "\tmov\tes, ax\n" // es = ss
            "\tmov\tdi, sp\n" // es:di = where struct should be copied to (seg:ofs)
            "\tcld\n"
            "\trep\tmovsb\n"  // copy; limit to ~64KB since stack size itself is ~64KB max

            "\tpop\teax\n"  // return first 4 bytes of struct in eax
            "\tpush\teax\n"
            "\tpush\teax\n" // caller will remove this and first 4 bytes of struct from stack (as 2 args)
            "\tpush\tedx\n" //   and then it will push eax (first 4 bytes of struct) back
            "\tretf");      // actually return to return address saved in edx
    }
    else if (OutputFormat == FormatSegUnreal)
    {
      puts2("\tmov\tedx, [bp+4]\n"   // edx = return address
            "\tmov\tesi, [bp+8]\n"   // esi = &struct
            "\tmov\tecx, [bp+12]\n"  // ecx = sizeof(struct)
            "\tmov\tebp, [bp]\n"     // restore ebp

            "\tlea\teax, [ecx + 3]\n" // eax = sizeof(struct) + 3
            "\tand\teax, -4\n"        // eax = sizeof(struct) rounded up to multiple of 4 bytes
            "\tsub\tax, 4*4\n"        // remove ebp, return address and 2 args from stack
            "\tsub\tsp, ax\n"         // allocate stack space for struct

            "\tmov\tax, ss\n"
            "\tmovzx\teax, ax\n"
            "\tshl\teax, 4\n"
            "\tmovzx\tedi, sp\n"
            "\tadd\tedi, eax\n"       // edi = where struct should be copied to

            "\tcld\n"
            "\tdb\t0x67\n"
            "\trep\tmovsb\n"      // copy

            "\tpop\teax\n"        // return first 4 bytes of struct in eax
            "\tpush\teax\n"
            "\tpush\teax\n"       // caller will remove this and first 4 bytes of struct from stack (as 2 args)
            "\tpush\tedx\n"       //   and then it will push eax (first 4 bytes of struct) back
            "\tretf");            // actually return to return address saved in edx
    }
    else
    {
      // Copying the pushed structure to the stack backwards
      // (from higher to lower addresses) in order to correctly
      // grow the stack on Windows, page by page
      puts2("\tmov\tedx, [ebp+4]\n"  // edx = return address
            "\tmov\tesi, [ebp+8]\n"  // esi = &struct
            "\tmov\tecx, [ebp+12]\n" // ecx = sizeof(struct)
            "\tmov\tebp, [ebp]\n"    // restore ebp

            "\tlea\teax, [ecx + 3]\n" // eax = sizeof(struct) + 3
            "\tand\teax, -4\n"        // eax = sizeof(struct) rounded up to multiple of 4 bytes
            "\tsub\teax, 4*4\n"       // remove ebp, return address and 2 args from stack
            "\tsub\tesp, eax\n"       // allocate stack space for struct

            "\tlea\tesi, [esi + ecx - 1]\n" // esi = &last byte of struct
            "\tlea\tedi, [esp + ecx - 1]\n" // edi = where it should be copied to
            "\tstd\n"
            "\trep\tmovsb\n"      // copy
            "\tcld\n"

            "\tmov\teax, [esp]\n" // return first 4 bytes of struct in eax
            "\tpush\t0\n"         // caller will remove this 0 and first 4 bytes of struct from stack (as 2 args)
            "\tpush\tedx\n"       //   and then it will push eax (first 4 bytes of struct) back
            "\tret");             // actually return to return address saved in edx
    }
#endif

//    GenFxnEpilog();

    puts2(CodeHeaderFooter[1]);
  }
#endif

#ifdef CAN_COMPILE_32BIT
  if (WinChkStkLabel > 0) // if _chkstk() has been used at least once
  {
    // When targeting Windows, simulate _chkstk() to
    // correctly grow the stack page by page by probing it
    int lbl = LabelCnt++;

    puts2(CodeHeaderFooter[0]);

    GenNumLabel(WinChkStkLabel);
    puts2("\tlea\tebx, [esp+4]\n"
          "\tmov\tecx, ebx\n"
          "\tsub\tecx, eax\n"
          "\tand\tebx, -4096\n"
          "\tand\tecx, -4096");
    GenNumLabel(lbl); // L1:
    puts2("\tsub\tebx, 4096\n"
          "\tmov\tal, [ebx]\n"
          "\tcmp\tebx, ecx");
    printf2("\tjne\t"); GenPrintNumLabel(lbl); // jne L1
    puts2("\n\tret");

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
