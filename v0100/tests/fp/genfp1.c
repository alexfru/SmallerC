/*
  Generator of floating point tests.

  How to compile for and use under DOS:
    smlrcc -dosp genfp1.c -o genfp1.exe
    genfp1.exe >testfp1.c
    smlrcc -dosp testfp1.c -o testfp1.exe
    testfp1.exe

  How to compile for and use under Windows:
    smlrcc -win genfp1.c -o genfp1.exe
    genfp1.exe >testfp1.c
    smlrcc -win testfp1.c -o testfp1.exe
    testfp1.exe

  How to compile for and use under Linux:
    smlrcc -linux genfp1.c -o genfp1
    ./genfp1 >testfp1.c
    smlrcc -linux testfp1.c -o testfp1
    ./testfp1

  How to compile for and use under MacOS:
    smlrcc -macos genfp1.c -o genfp1
    ./genfp1 >testfp1.c
    smlrcc -macos testfp1.c -o testfp1
    ./testfp1
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum
{
  fvNan,
  fv_Inf,
  fv_1,
  fv_0,
  fv0,
  fv1,
  fvInf,

  fvCnt
} FloatVal;

char* FloatValConstText[fvCnt] =
{
  "(0.0f/0.0f)",
  "(-1.0f/0.0f)",
  "(-1.0f)",
  "(-0.0f)",
  "(+0.0f)",
  "(+1.0f)",
  "(+1.0f/0.0f)"
};

char* FloatValConstName[fvCnt] =
{
  "FNAN",
  "F_INF",
  "F_1",
  "F_0",
  "F0",
  "F1",
  "FINF"
};

char* FloatValNonConstName[fvCnt] =
{
  "fnan",
  "f_inf",
  "f_1",
  "f_0",
  "f0",
  "f1",
  "finf"
};

typedef enum
{
  coLT,
  coLE,
  coEQ,
  coGE,
  coGT,
  coNE,

  coCnt
} CmpOperator;

char* CmpOperatorText[coCnt] =
{
  "<", "<=", "==", ">=", ">", "!="
};

int Fcmp(FloatVal a, FloatVal b, int NanVal)
{
  if (a == fvNan || b == fvNan)
    return NanVal;
  // -0.0 == +0.0
  if (a == fv_0)
    a = fv0;
  if (b == fv_0)
    b = fv0;
  if (a < b)
    return -1;
  if (a > b)
    return +1;
  return 0;
}

int FcmpOp(FloatVal a, FloatVal b, CmpOperator op)
{
  int NanVal = (op == coGE || op == coGT) ? -1 : +1;
  int r = Fcmp(a, b, NanVal);
  switch (op)
  {
  case coLT:
    return r < 0;
  case coLE:
    return r <= 0;
  case coEQ:
    return r == 0;
  case coGE:
    return r >= 0;
  case coGT:
    return r > 0;
  default:
  case coNE:
    return r != 0;
  }
}

void GenDefs(int raw)
{
  int i;
  if (!raw)
  {
    puts("#include <stdio.h>");
    puts("#include <stdlib.h>\n");
  }
  for (i = 0; i < fvCnt; i++)
  {
    printf("#define %s %s\n", FloatValConstName[i], FloatValConstText[i]);
    printf("float   %s = %s;\n", FloatValNonConstName[i], FloatValConstName[i]);
  }
  puts("");
  puts("float f0_5 = 0.5f;");
  puts("float f1_5 = 1.5f;");
  puts("int i0 = 0;");
  puts("int i1 = 1;");
  puts("int i4 = 4;");
  puts("");
}

void GenArithm(void)
{
  int lidx, ridx;
  puts("void arithm(void)\n{");
  puts("  int error = 0;\n");

  for (lidx = 0; lidx < 4; lidx++)
  for (ridx = 0; ridx < 4; ridx++)
  {
    static char* v[] = { "1.5f", "f1_5", "4", "i4" };
    static char* vdiv[] = { "0.5f", "f0_5", "4", "i4" };
    printf("  if ((%s + %s) != %s) error = __LINE__;\n",
           v[lidx],
           v[ridx],
           (lidx < 2) ? ((ridx < 2) ? "3": "5.5f") : ((ridx < 2) ? "5.5f": "8"));
    printf("  if ((%s - %s) != %s) error = __LINE__;\n",
           v[lidx],
           v[ridx],
           (lidx < 2) ? ((ridx < 2) ? "0": "-2.5f") : ((ridx < 2) ? "2.5f": "0"));
    printf("  if ((%s * %s) != %s) error = __LINE__;\n",
           v[lidx],
           v[ridx],
           (lidx < 2) ? ((ridx < 2) ? "2.25f": "6") : ((ridx < 2) ? "6": "16"));
    printf("  if ((%s / %s) != %s) error = __LINE__;\n",
           vdiv[lidx],
           vdiv[ridx],
           (lidx < 2) ? ((ridx < 2) ? "1": "0.125f") : ((ridx < 2) ? "8": "1"));
  }

  puts("\n  if (error)\n    { printf(\"Test failed on line %d\\n\", error); abort(); }");
  puts("}\n");
}

void GenCmp(void)
{
  int lconst, rconst, lidx, ridx, opidx;
  puts("void cmp(void)\n{");
  puts("  int error = 0;\n");

  // if (float cmp float)
  for (lconst = 0; lconst <= 1; lconst++)
  for (rconst = 0; rconst <= 1; rconst++)
  for (lidx = 0; lidx < fvCnt; lidx++)
  for (ridx = 0; ridx < fvCnt; ridx++)
  for (opidx = 0; opidx < coCnt; opidx++)
  {
    printf("  if ((%s %s %s) != %d) error = __LINE__;\n",
           lconst ? FloatValConstName[lidx] : FloatValNonConstName[lidx],
           CmpOperatorText[opidx],
           rconst ? FloatValConstName[ridx] : FloatValNonConstName[ridx],
           FcmpOp(lidx, ridx, opidx));
  }

  // if (float cmp int)
  for (lconst = 0; lconst <= 1; lconst++)
  for (rconst = 0; rconst <= 1; rconst++)
  for (lidx = 0; lidx < fvCnt; lidx++)
  for (ridx = 0; ridx <= 1; ridx++)
  for (opidx = 0; opidx < coCnt; opidx++)
  {
    printf("  if ((%s %s %s) != %d) error = __LINE__;\n",
           lconst ? FloatValConstName[lidx] : FloatValNonConstName[lidx],
           CmpOperatorText[opidx],
           rconst ? (ridx ? "1" : "0") : (ridx ? "i1" : "i0"),
           FcmpOp(lidx, (ridx ? fv1 : fv0), opidx));
  }

  // if (int cmp float)
  for (lconst = 0; lconst <= 1; lconst++)
  for (rconst = 0; rconst <= 1; rconst++)
  for (lidx = 0; lidx <= 1; lidx++)
  for (ridx = 0; ridx < fvCnt; ridx++)
  for (opidx = 0; opidx < coCnt; opidx++)
  {
    printf("  if ((%s %s %s) != %d) error = __LINE__;\n",
           lconst ? (lidx ? "1" : "0") : (lidx ? "i1" : "i0"),
           CmpOperatorText[opidx],
           rconst ? FloatValConstName[ridx] : FloatValNonConstName[ridx],
           FcmpOp((lidx ? fv1 : fv0), ridx, opidx));
  }

  puts("\n  if (error)\n    { printf(\"Test failed on line %d\\n\", error); abort(); }");
  puts("}\n");
}

void GenCtrl(void)
{
  int lconst, lidx, rconst, ridx, cconst, cidx, opidx;
  puts("void ctrl(void)\n{");
  puts("  int error = 0;");
  puts("  int cnt;\n");

  // if (float) {} else {}
  for (lconst = 0; lconst <= 1; lconst++)
  for (lidx = 0; lidx < fvCnt; lidx++)
  {
    char *e[] = { "", "error = __LINE__;" };
    int tru = FcmpOp(lidx, fv0, coNE);
    printf("  if (%s) { %s } else { %s }\n",
           lconst ? FloatValConstName[lidx] : FloatValNonConstName[lidx],
           e[!tru],
           e[tru]);
  }

  // for (;float;) {}
  for (lconst = 0; lconst <= 1; lconst++)
  for (lidx = 0; lidx < fvCnt; lidx++)
  {
    int tru = FcmpOp(lidx, fv0, coNE);
    printf("  for (cnt = 0; %s; ) { cnt++; break; } if (cnt != %d) error = __LINE__;\n",
           lconst ? FloatValConstName[lidx] : FloatValNonConstName[lidx],
           tru);
  }

  // while (float) {}
  for (lconst = 0; lconst <= 1; lconst++)
  for (lidx = 0; lidx < fvCnt; lidx++)
  {
    int tru = FcmpOp(lidx, fv0, coNE);
    printf("  cnt = 0; while (%s) { cnt++; break; } if (cnt != %d) error = __LINE__;\n",
           lconst ? FloatValConstName[lidx] : FloatValNonConstName[lidx],
           tru);
  }

  // do {} while (float);
  for (lconst = 0; lconst <= 1; lconst++)
  for (lidx = 0; lidx < fvCnt; lidx++)
  {
    int tru = FcmpOp(lidx, fv0, coNE);
    printf("  cnt = 0; do { if (cnt++) break; } while (%s); if (cnt != %d) error = __LINE__;\n",
           lconst ? FloatValConstName[lidx] : FloatValNonConstName[lidx],
           1 + tru);
  }

  // float ||/&& float
  for (lconst = 0; lconst <= 1; lconst++)
  for (rconst = 0; rconst <= 1; rconst++)
  for (lidx = 0; lidx < fvCnt; lidx++)
  for (ridx = 0; ridx < fvCnt; ridx++)
  for (opidx = 0; opidx <= 1; opidx++)
  {
    int ltru = FcmpOp(lidx, fv0, coNE);
    int rtru = FcmpOp(ridx, fv0, coNE);
    int tru = opidx ? (ltru && rtru) : (ltru || rtru);
    printf("  if ((%s %s %s) != %d) error = __LINE__;\n",
           lconst ? FloatValConstName[lidx] : FloatValNonConstName[lidx],
           opidx ? "&&" : "||",
           rconst ? FloatValConstName[ridx] : FloatValNonConstName[ridx],
           tru);
  }

  // float ||/&& int
  // int ||/&& float
  for (lconst = 0; lconst <= 1; lconst++)
  for (rconst = 0; rconst <= 1; rconst++)
  for (lidx = 0; lidx < fvCnt; lidx++)
  for (ridx = 0; ridx <= 1; ridx++)
  for (opidx = 0; opidx <= 1; opidx++)
  {
    int tru = FcmpOp(lidx, fv0, coNE);
    tru = opidx ? (tru && ridx) : (tru || ridx);
    printf("  if ((%s %s %s) != %d) error = __LINE__;\n",
           lconst ? FloatValConstName[lidx] : FloatValNonConstName[lidx],
           opidx ? "&&" : "||",
           rconst ? (ridx ? "1" : "0") : (ridx ? "i1" : "i0"),
           tru);
    printf("  if ((%s %s %s) != %d) error = __LINE__;\n",
           rconst ? (ridx ? "1" : "0") : (ridx ? "i1" : "i0"),
           opidx ? "&&" : "||",
           lconst ? FloatValConstName[lidx] : FloatValNonConstName[lidx],
           tru);
  }

  // float ? int : float
  // float ? float : int
  // float ? float : float
  for (cconst = 0; cconst <= 1; cconst++)
  for (cidx = 0; cidx < fvCnt; cidx++)
  for (lidx = 0; lidx < 4; lidx++)
  for (ridx = 0; ridx < 4; ridx++)
  {
    static char* v[] = { "1.5f", "f1_5", "4", "i4" };
    int tru = FcmpOp(cidx, fv0, coNE);
    char *l = v[lidx], *r = v[ridx];
    printf("  if ((%s ? %s : %s) != %s) error = __LINE__;\n",
           cconst ? FloatValConstName[cidx] : FloatValNonConstName[cidx],
           l,
           r,
           tru ? l : r);
  }

  puts("\n  if (error)\n    { printf(\"Test failed on line %d\\n\", error); abort(); }");
  puts("}\n");
}

void GenCast(void)
{
  puts("void cast(void)\n{");
  puts("  int error = 0;");
  puts("  float f_128_75 = -128.75f;");
  puts("  float f127_75 = 127.75f;");
  puts("  float f_0_75 = -0.75f;");
  puts("  float f255_75 = 255.75f;");
  puts("  float f_32768_75 = -32768.75f;");
  puts("  float f32767_75 = 32767.75f;");
  puts("  float f65535_75 = 65535.75f;");
  puts("  float f_2147483648 = -2147483648.0f;");
  puts("  float f2147483520 = 2147483520.0f;");
  puts("  float f4294967040 = 4294967040.0f;");
  puts("  int i_2147483648 = (-2147483647-1);");
  puts("  int i2147483520 = 2147483520;");
  puts("  unsigned u4294967040 = 4294967040u;");
  puts("  int i2147483647 = 2147483647;");
  puts("  unsigned u4294967295 = 4294967295u;\n");

  puts("  if (((signed char)-128.75f == -128) != 1) error = __LINE__;");
  puts("  if (((signed char)f_128_75 == -128) != 1) error = __LINE__;");
  puts("  if (((signed char)+127.75f == +127) != 1) error = __LINE__;");
  puts("  if (((signed char)f127_75 == +127) != 1) error = __LINE__;");

  puts("  if (((unsigned char)-0.75f == 0) != 1) error = __LINE__;");
  puts("  if (((unsigned char)f_0_75 == 0) != 1) error = __LINE__;");
  puts("  if (((unsigned char)255.75f == 255) != 1) error = __LINE__;");
  puts("  if (((unsigned char)f255_75 == 255) != 1) error = __LINE__;");

  puts("  if (((short)-32768.75f == -32768) != 1) error = __LINE__;");
  puts("  if (((short)f_32768_75 == -32768) != 1) error = __LINE__;");
  puts("  if (((short)+32767.75f == +32767) != 1) error = __LINE__;");
  puts("  if (((short)f32767_75 == +32767) != 1) error = __LINE__;");

  puts("  if (((unsigned short)-0.75f == 0) != 1) error = __LINE__;");
  puts("  if (((unsigned short)f_0_75 == 0) != 1) error = __LINE__;");
  puts("  if (((unsigned short)65535.75f == 65535) != 1) error = __LINE__;");
  puts("  if (((unsigned short)f65535_75 == 65535) != 1) error = __LINE__;");

  puts("  if (((int)-2147483648.0f == (-2147483647-1)) != 1) error = __LINE__;");
  puts("  if (((int)f_2147483648 == (-2147483647-1)) != 1) error = __LINE__;");
  puts("  if (((int)+2147483520.0f == +2147483520) != 1) error = __LINE__;");
  puts("  if (((int)f2147483520 == +2147483520) != 1) error = __LINE__;");

  puts("  if (((unsigned)-0.75f == 0) != 1) error = __LINE__;");
  puts("  if (((unsigned)f_0_75 == 0) != 1) error = __LINE__;");
  puts("  if (((unsigned)4294967040.0f == 4294967040u) != 1) error = __LINE__;");
  puts("  if (((unsigned)f4294967040 == 4294967040u) != 1) error = __LINE__;");

  puts("  if (((float)(-2147483647-1) == (-2147483647-1)) != 1) error = __LINE__;");
  puts("  if (((float)i_2147483648 == (-2147483647-1)) != 1) error = __LINE__;");
  puts("  if (((float)+2147483520 == +2147483520) != 1) error = __LINE__;");
  puts("  if (((float)i2147483520 == +2147483520) != 1) error = __LINE__;");
  puts("  if (((float)4294967040u == 4294967040u) != 1) error = __LINE__;");
  puts("  if (((float)u4294967040 == 4294967040u) != 1) error = __LINE__;");

  puts("  if ((-(float)2147483647 == (-2147483647-1)) != 1) error = __LINE__;");
  puts("  if ((-(float)i2147483647 == (-2147483647-1)) != 1) error = __LINE__;");
  puts("  if (((float)4294967295u == -2.0f*(-2147483647-1)) != 1) error = __LINE__;");
  puts("  if (((float)u4294967295 == -2.0f*(-2147483647-1)) != 1) error = __LINE__;");

  puts("  if (((float)(float)(-2147483647-1) == (-2147483647-1)) != 1) error = __LINE__;");
  puts("  if (((float)(float)i_2147483648 == (-2147483647-1)) != 1) error = __LINE__;");
  puts("  if (((float)f_0_75 == -0.75f) != 1) error = __LINE__;");

  puts("\n  if (error)\n    { printf(\"Test failed on line %d\\n\", error); abort(); }");
  puts("}\n");
}

void GenInit(void)
{
  puts("void init(void)\n{");
  puts("  int error = 0;");
  puts("  float f_2147483648 = (-2147483647-1);");
  puts("  static float sf_2147483648 = (-2147483647-1);");
  puts("  float f4294967040 = 4294967040u;");
  puts("  static float sf4294967040 = 4294967040u;");
  puts("  int i_2147483648 = -2147483648.0f;");
  puts("  static int si_2147483648 = -2147483648.0f;");
  puts("  unsigned u4294967040 = 4294967040.0f;");
  puts("  static unsigned su4294967040 = 4294967040.0f;\n");

  puts("  if ((f_2147483648 == (-2147483647-1)) != 1) error = __LINE__;");
  puts("  if ((sf_2147483648 == (-2147483647-1)) != 1) error = __LINE__;");
  puts("  if ((f4294967040 == 4294967040u) != 1) error = __LINE__;");
  puts("  if ((sf4294967040 == 4294967040u) != 1) error = __LINE__;");
  puts("  if ((i_2147483648 == (-2147483647-1)) != 1) error = __LINE__;");
  puts("  if ((si_2147483648 == (-2147483647-1)) != 1) error = __LINE__;");
  puts("  if ((u4294967040 == 4294967040u) != 1) error = __LINE__;");
  puts("  if ((su4294967040 == 4294967040u) != 1) error = __LINE__;");

  puts("\n  if (error)\n    { printf(\"Test failed on line %d\\n\", error); abort(); }");
  puts("}\n");
}

void GenAssign(void)
{
  puts("void assign(void)\n{");
  puts("  int error = 0;");
  puts("  float f;");
  puts("  int i;");
  puts("  unsigned u;\n");

  puts("  if (((f = (-2147483647-1)) == -2147483648.0f) != 1) error = __LINE__;");
  puts("  if (((f = 4294967040u) == 4294967040.0f) != 1) error = __LINE__;");
  puts("  if (((i = -2147483648.0f) == (-2147483647-1)) != 1) error = __LINE__;");
  puts("  if (((u = 4294967040.0f) == 4294967040u) != 1) error = __LINE__;");

  puts("\n  if (error)\n    { printf(\"Test failed on line %d\\n\", error); abort(); }");
  puts("}\n");
}

void GenPass(void)
{
  puts("void accept_i1(int* error, int line, int a)\n{\n  if (a != 1) *error = line;\n}\n");
  puts("void accept_u1(int* error, int line, unsigned a)\n{\n  if (a != 1) *error = line;\n}\n");
  puts("void accept_f1(int* error, int line, float a)\n{\n  if (a != 1.0f) *error = line;\n}\n");
  puts("void accept_i_2147483648(int* error, int line, int a)\n{\n  if (a != (-2147483647-1)) *error = line;\n}\n");
  puts("void accept_u4294967040(int* error, int line, unsigned a)\n{\n  if (a != 4294967040u) *error = line;\n}\n");
  puts("void accept_f_2147483648(int* error, int line, float a)\n{\n  if (a != -2147483648.0f) *error = line;\n}\n");
  puts("void accept_f4294967040(int* error, int line, float a)\n{\n  if (a != 4294967040.0f) *error = line;\n}\n");

  puts("void pass(void)\n{");
  puts("  int error = 0;");
  puts("  unsigned u1 = 1;");
  puts("  float f_2147483648 = -2147483648.0f;");
  puts("  float f4294967040 = 4294967040.0f;");
  puts("  int i_2147483648 = (-2147483647-1);");
  puts("  unsigned u4294967040 = 4294967040u;\n");

  puts("  accept_i1(&error, __LINE__, F1);");
  puts("  accept_i1(&error, __LINE__, f1);");
  puts("  accept_u1(&error, __LINE__, F1);");
  puts("  accept_u1(&error, __LINE__, f1);");
  puts("  accept_f1(&error, __LINE__, F1);");
  puts("  accept_f1(&error, __LINE__, f1);");
  puts("  accept_f1(&error, __LINE__, i1);");
  puts("  accept_f1(&error, __LINE__, u1);");
  puts("  accept_f1(&error, __LINE__, 1);");
  puts("  accept_f1(&error, __LINE__, 1u);");
  puts("  accept_i_2147483648(&error, __LINE__, -2147483648.0f);");
  puts("  accept_i_2147483648(&error, __LINE__, f_2147483648);");
  puts("  accept_u4294967040(&error, __LINE__, 4294967040.0f);");
  puts("  accept_u4294967040(&error, __LINE__, f4294967040);");
  puts("  accept_f_2147483648(&error, __LINE__, (-2147483647-1));");
  puts("  accept_f_2147483648(&error, __LINE__, i_2147483648);");
  puts("  accept_f4294967040(&error, __LINE__, 4294967040u);");
  puts("  accept_f4294967040(&error, __LINE__, u4294967040);");

  // TBD??? passing into f() and f(blah, ...)???

  puts("\n  if (error)\n    { printf(\"Test failed on line %d\\n\", error); abort(); }");
  puts("}\n");
}

void GenRet(void)
{
  puts("signed char ret_sc_f(float a)\n{\n  return a;\n}\n");
  puts("signed char ret_sc__128_75(void)\n{\n  return -128.75f;\n}\n");
  puts("unsigned char ret_uc_f(float a)\n{\n  return a;\n}\n");
  puts("unsigned char ret_uc__0_75(void)\n{\n  return -0.75f;\n}\n");
  puts("unsigned char ret_uc_255_75(void)\n{\n  return 255.75f;\n}\n");
  puts("short ret_ss_f(float a)\n{\n  return a;\n}\n");
  puts("short ret_ss__32768_75(void)\n{\n  return -32768.75f;\n}\n");
  puts("unsigned short ret_us_f(float a)\n{\n  return a;\n}\n");
  puts("unsigned short ret_us__0_75(void)\n{\n  return -0.75f;\n}\n");
  puts("unsigned short ret_us_65535_75(void)\n{\n  return 65535.75f;\n}\n");
  puts("int ret_si_f(float a)\n{\n  return a;\n}\n");
  puts("int ret_si__2147483648_0(void)\n{\n  return -2147483648.0f;\n}\n");
  puts("unsigned ret_ui_f(float a)\n{\n  return a;\n}\n");
  puts("unsigned ret_ui_4294967040_0(void)\n{\n  return 4294967040.0f;\n}\n");
  puts("float ret_f_si(int a)\n{\n  return a;\n}\n");
  puts("float ret_f__2147483648(void)\n{\n  return (-2147483647-1);\n}\n");
  puts("float ret_f_ui(unsigned a)\n{\n  return a;\n}\n");
  puts("float ret_f_4294967040(void)\n{\n  return 4294967040u;\n}\n");

  puts("void ret(void)\n{");
  puts("  int error = 0;");

  puts("  if (ret_sc_f(-128.75f) != -128) error = __LINE__;");
  puts("  if (ret_sc__128_75() != -128) error = __LINE__;");
  puts("  if (ret_uc_f(255.75f) != +255) error = __LINE__;");
  puts("  if (ret_uc__0_75() != 0) error = __LINE__;");
  puts("  if (ret_uc_255_75() != +255) error = __LINE__;");
  puts("  if (ret_ss_f(-32768.75f) != -32768) error = __LINE__;");
  puts("  if (ret_ss__32768_75() != -32768) error = __LINE__;");
  puts("  if (ret_us_f(65535.75f) != +65535) error = __LINE__;");
  puts("  if (ret_us__0_75() != 0) error = __LINE__;");
  puts("  if (ret_us_65535_75() != +65535) error = __LINE__;");
  puts("  if (ret_si_f(-2147483648.0f) != (-2147483647-1)) error = __LINE__;");
  puts("  if (ret_si__2147483648_0() != (-2147483647-1)) error = __LINE__;");
  puts("  if (ret_ui_f(4294967040.0f) != +4294967040u) error = __LINE__;");
  puts("  if (ret_ui_4294967040_0() != +4294967040u) error = __LINE__;");
  puts("  if (ret_f_si((-2147483647-1)) != -2147483648.0f) error = __LINE__;");
  puts("  if (ret_f__2147483648() != -2147483648.0f) error = __LINE__;");
  puts("  if (ret_f_ui(+4294967040u) != 4294967040.0f) error = __LINE__;");
  puts("  if (ret_f_4294967040() != 4294967040.0f) error = __LINE__;");

  puts("\n  if (error)\n    { printf(\"Test failed on line %d\\n\", error); abort(); }");
  puts("}\n");
}

void GenMain(void)
{
  puts("int main(void)\n{");
  puts("  arithm();");
  puts("  cmp();");
  puts("  ctrl();");
  puts("  cast();");
  puts("  init();");
  puts("  assign();");
  puts("  pass();");
  puts("  ret();");
  puts("  puts(\"All tests passed.\");");
  puts("  return 0;\n}");
}

int main(int argc, char* argv[])
{
  int i, raw = 0;
  char* outname = NULL;

  for (i = 1; i < argc; i++)
  {
    if (!strcmp(argv[i], "-raw"))
    {
      raw = 1;
      continue;
    }
    else if (!strcmp(argv[i], "-o"))
    {
      if (i + 1 < argc)
      {
        ++i;
        outname = argv[i];
        continue;
      }
    }
    fprintf(stderr, "Invalid or unsupported command line option '%s'\n", argv[i]);
    return EXIT_FAILURE;
  }

  if (outname)
    freopen(outname, "w", stdout);

  GenDefs(raw);
  GenArithm();
  GenCmp();
  GenCtrl();
  GenCast();
  GenInit();
  GenAssign();
  GenPass();
  GenRet();
  GenMain();

  return 0;
}
