/*
  Generator of randomized tests for basic testing of expressions/code generator.

  How to compile for and use under DOS:
    smlrcc -dosh gencg1.c -o gencg1.exe
    gencg1.exe >testcg1.c
    smlrcc -dosh testcg1.c -o testcg1.exe
    testcg1.exe
   OR
    smlrcc -dosu gencg1.c -o gencg1.exe
    gencg1.exe >testcg1.c
    smlrcc -dosu testcg1.c -o testcg1.exe
    testcg1.exe
   OR
    smlrcc -dosp gencg1.c -o gencg1.exe
    gencg1.exe >testcg1.c
    smlrcc -dosp testcg1.c -o testcg1.exe
    testcg1.exe

  How to compile for and use under Windows:
    smlrcc -win gencg1.c -o gencg1.exe
    gencg1.exe >testcg1.c
    smlrcc -win testcg1.c -o testcg1.exe
    testcg1.exe

  How to compile for and use under Linux:
    smlrcc -linux gencg1.c -o gencg1
    ./gencg1 >testcg1.c
    smlrcc -linux testcg1.c -o testcg1
    ./testcg1

  How to compile for and use under MacOS:
    smlrcc -macos gencg1.c -o gencg1
    ./gencg1 >testcg1.c
    smlrcc -macos testcg1.c -o testcg1
    ./testcg1
*/

#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Ensure:
// - expected type sizes
// - 2's complement arithmetic
// - arithmetic shifts right of negative values
extern char StAtIcAsSeRt[(CHAR_BIT == 8) ? 1 : -1];
extern char StAtIcAsSeRt[(-INT_MAX == INT_MIN + 1) ? 1 : -1];
extern char StAtIcAsSeRt[((int)UINT_MAX == -1) ? 1 : -1];
extern char StAtIcAsSeRt[((-1 >> 1) == -1) ? 1 : -1];
extern char StAtIcAsSeRt[(sizeof(short) == 2) ? 1 : -1];
extern char StAtIcAsSeRt[(sizeof(int) == 4) ? 1 : -1];

int varCnt = 1;

unsigned mySeed = 1;

void mySrand(unsigned seed)
{
  mySeed = seed;
}

int myRand(void)
{
  mySeed = mySeed * 1103515245 + 12345;
  return (mySeed >> 16) & 0x7FFF;
}

int randBool(void)
{
  return myRand() < (int)RAND_MAX / 2;
}

typedef enum
{
  bsChar,
  bsShort,
  bsInt,
} ValBase;

typedef enum
{
  sgnSigned,
  sgnUnsigned
} ValSign;

typedef enum
{
  strVar,
  strArrEl,
} ValStruct;

typedef enum
{
  srgAuto,
  srgStatic,
} ValStorage;

typedef enum
{
  ntVal,
  ntVar,
  ntOperator,
} NodeType;

typedef enum
{
// Unary
  opUnaryFirst,
  opUnaryBeforeFirst = opUnaryFirst - 1,
  opIncDecFirst,
  opIncDecBeforeFirst = opIncDecFirst - 1,
  opPostInc,
  opPostDec,
  opPreInc,
  opPreDec,
  opIncDecAfterLast,
  opIncDecLast = opIncDecAfterLast - 1,
  opUnaryPlus,
  opUnaryMinus,
  opCompl,
  opLogicNot,
  opSizeOf,
  opCastIntFirst,
  opCastIntBeforeFirst = opCastIntFirst - 1,
  opCastUChar,
  opCastSChar,
  opCastUShort,
  opCastSShort,
  opCastUInt,
  opCastSInt,
  opCastIntAfterLast,
  opCastIntLast = opCastIntAfterLast - 1,
  opUnaryAfterLast,
  opUnaryLast = opUnaryAfterLast - 1,
// Binary
  opBinaryFirst,
  opBinaryBeforeFirst = opBinaryFirst - 1,
  opMul,
  opDiv,
  opMod,
  opAdd,
  opSub,
  opShl,
  opShr,
  opLT,
  opGT,
  opLE,
  opGE,
  opEQ,
  opNE,
  opAnd,
  opOr,
  opXor,
  opAndAnd,
  opOrOr,
  opAssignFirst,
  opAssignBeforeFirst = opAssignFirst - 1,
  opAssign,
  opAssignMul,
  opAssignDiv,
  opAssignMod,
  opAssignAdd,
  opAssignSub,
  opAssignShl,
  opAssignShr,
  opAssignAnd,
  opAssignXor,
  opAssignOr,
  opAssignAfterLast,
  opAssignLast = opAssignAfterLast - 1,
  opComma,
  opCond, // special "binary" case: ternary conditional operator
  opBinaryAfterLast,
  opBinaryLast = opBinaryAfterLast - 1,
} Operator;

char* OpStr[] =
{
// Unary
  "++",
  "--",
  "++",
  "--",
  "+",
  "-",
  "~",
  "!",
  "sizeof",
  "(unsigned char)",
  "(signed char)",
  "(unsigned short)",
  "(short)",
  "(unsigned)",
  "(int)",
// Binary
  "*",
  "/",
  "%",
  "+",
  "-",
  "<<",
  ">>",
  "<",
  ">",
  "<=",
  ">=",
  "==",
  "!=",
  "&",
  "|",
  "^",
  "&&",
  "||",
  "=",
  "*=",
  "/=",
  "%=",
  "+=",
  "-=",
  "<<=",
  ">>=",
  "&=",
  "^=",
  "|=",
  ",",
  "", // special case: ternary conditional operator
};

typedef struct Node Node;
struct Node
{
  NodeType type;

  int val;

  ValBase base;
  ValSign sign;

  int varNum;
  ValStruct struc;
  ValStorage storage;

  Operator op;

  Node *child[3]; // 3 operands max (ternary conditional operator needs 3 operands: child[2] ? child[0] : child[1])
};

int operatorNeedsLvalue(Operator op)
{
  return (op >= opIncDecFirst && op <= opIncDecLast) ||
         (op >= opAssignFirst && op <= opAssignLast);
}

int operatorIsBinary(Operator op)
{
  return op >= opBinaryFirst && op <= opBinaryLast;
}

int operatorIsPostUnary(Operator op)
{
  return op == opPostInc || op == opPostDec;
}

void printOperator(Operator op)
{
  printf("%s", OpStr[op]);
}

void printVal(Node* n)
{
  if (n->base == bsInt && n->sign == sgnUnsigned)
    printf("%uu", (unsigned)n->val);
  else if (n->val == -2147483647-1) // INT_MIN
    printf(" (-2147483647-1)");
  else
    printf(" %d", n->val); // extra leading space to prevent unary - turning into prefix -- before negative values
}

void printVarName(Node* n)
{
  printf("v%d", n->varNum);
  if (n->struc == strArrEl)
    printf ("[1]");
}

void printDecl(Node* n)
{
  printf("    ");
  if (n->storage == srgStatic) printf ("static ");
  printf("volatile ");
  switch (n->sign)
  {
  case sgnSigned: printf("signed "); break;
  case sgnUnsigned: printf("unsigned "); break;
  }
  switch (n->base)
  {
  case bsChar: printf("char "); break;
  case bsShort: printf("short "); break;
  case bsInt: printf("int "); break;
  }
  printf("v%d", n->varNum);
  if (n->struc == strArrEl)
    printf ("[3]");
  printf(" = ");
  if (n->struc == strArrEl)
    printf("{ 0, "), printVal(n), printf(", 0 }");
  else
    printVal(n);
  printf(";\n");
}

void printDecls(Node* n)
{
  switch (n->type)
  {
  case ntVar:
    printDecl(n);
    break;
  case ntOperator:
    if (n->child[2])
      printDecls(n->child[2]);
    printDecls(n->child[0]);
    if (n->child[1])
      printDecls(n->child[1]);
    break;
  default:;
  }
}

void reviveVars(Node* n)
{
  switch (n->type)
  {
  case ntVar:
    printf("    ");
    printVarName(n);
    printf(" = ");
    printVal(n);
    printf(";\n");
    break;
  case ntOperator:
    if (n->child[2])
      reviveVars(n->child[2]);
    reviveVars(n->child[0]);
    if (n->child[1])
      reviveVars(n->child[1]);
    break;
  default:;
  }
}

Node* newNode(void)
{
  Node* p = malloc(sizeof *p);
  if (!p)
  {
    printf("Out of memory\n");
    exit(EXIT_FAILURE);
  }
  memset(p, 0, sizeof *p);
  return p;
}

void delNode(Node* n)
{
  if (!n) return;
  delNode(n->child[2]);
  delNode(n->child[0]);
  delNode(n->child[1]);
  free(n);
}

void attach2Nodes(Node* parent, Node* lchild, Node* rchild)
{
  parent->child[0] = lchild;
  parent->child[1] = rchild;
}

void printSubExpr(Node* n)
{
  switch (n->type)
  {
  case ntVal:
    printVal(n);
    break;
  case ntVar:
    printVarName(n);
    break;
  case ntOperator:
    printf("(");
    if (n->op == opCond)
    {
      printSubExpr(n->child[2]);
      printf("?");
      printSubExpr(n->child[0]);
      printf(":");
      printSubExpr(n->child[1]);
    }
    else if (operatorIsBinary(n->op))
    {
      printSubExpr(n->child[0]);
      printOperator(n->op);
      printSubExpr(n->child[1]);
    }
    else
    {
      if (operatorIsPostUnary(n->op))
      {
        printSubExpr(n->child[0]);
        printOperator(n->op);
      }
      else
      {
        printOperator(n->op);
        if (n->op == opSizeOf) printf(" ");
        printSubExpr(n->child[0]);
      }
    }
    printf(")");
    break;
  }
}

/*
void dumpVars(Node* n)
{
  switch (n->type)
  {
  case ntVar:
    printf("    printf(\""); printVarName(n); printf(" : %%d\\n\", (int)"); printVarName(n); printf(");\n");
    break;
  case ntOperator:
    if (n->child[2])
      dumpVars(n->child[2]);
    dumpVars(n->child[0]);
    if (n->child[1])
      dumpVars(n->child[1]);
    break;
  default:;
  }
}
*/

void truncVal(Node* n)
{
  if (n->base == bsChar)
  {
    if (n->sign == sgnUnsigned)
      n->val = (unsigned char)n->val;
    else
      n->val = (signed char)n->val;
  }
  else if (n->base == bsShort)
  {
    if (n->sign == sgnUnsigned)
      n->val = (unsigned short)n->val;
    else
      n->val = (signed short)n->val;
  }
}

void genVal(Node* n)
{
  n->val = myRand() % 255 - 127;
  truncVal(n);
}

Node* genSubExpr(int depth, int lvalNeeded)
{
  Node *n = newNode(), *left = NULL, *right = NULL, *cond = NULL;
  if (lvalNeeded)
  {
lval:
    n->type = ntVar;
    n->base = randBool() ? bsInt : (randBool() ? bsShort : bsChar);
    n->sign = randBool() ? sgnSigned : sgnUnsigned;
    genVal(n);
    n->varNum = varCnt++;
    n->struc = randBool() ? strVar : strArrEl;
    n->storage = randBool() ? srgAuto : srgStatic;
    return n;
  }
  if (depth <= 1)
  {
    if (randBool())
      goto lval;
    n->type = ntVal;
    n->base = bsInt;
    n->sign = randBool() ? sgnSigned : sgnUnsigned;
    genVal(n);
    return n;
  }

  n->type = ntOperator;
  if (randBool())
  {
    n->op = opUnaryFirst + myRand() % (opUnaryLast + 1 - opUnaryFirst);
    lvalNeeded = operatorNeedsLvalue(n->op);
    left = genSubExpr(depth - 1, lvalNeeded);
  }
  else
  {
    int divguard = 0, shiftguard = 0;
    n->op = opBinaryFirst + myRand() % (opBinaryLast + 1 - opBinaryFirst);
    switch (n->op)
    {
    case opDiv:
    case opMod:
    case opAssignDiv:
    case opAssignMod:
      divguard = 1;
      break;
    case opShl:
    case opShr:
    case opAssignShl:
    case opAssignShr:
      shiftguard = 1;
      break;
    default:;
    }
    lvalNeeded = operatorNeedsLvalue(n->op);
    if (n->op == opCond)
      cond = genSubExpr(depth - 1, 0);
    left = genSubExpr(depth - 1, lvalNeeded);
    right = genSubExpr(depth - 1, 0);
    if (divguard || shiftguard)
    {
      // Prevent division by 0 and shifts by more than 31 and less than 0
      Node *n1 = newNode(), *n2 = newNode();
      n1->type = ntOperator;
      n1->op = divguard ? opOr : opAnd;
      n2->type = ntVal;
      n2->val = divguard ? 1 : 31;
      n2->base = bsInt;
      n2->sign = sgnSigned;
      attach2Nodes(n1, right, n2);
      right = n1;
    }
  }
  attach2Nodes(n, left, right);
  n->child[2] = cond;
  return n;
}

int eval(Node* n, int updateVars)
{
  int left = 0, right = 0;
  int cond, binary;
  int unsleft = 0, unsright = 0, unsop = 0, unsres = 0;

  switch (n->type)
  {
  case ntVal:
  case ntVar:
    return n->val;
  default:;
  }

  cond = n->op == opCond;
  if (cond)
    eval(n->child[2], updateVars);

  left = eval(n->child[0], updateVars && (cond ? n->child[2]->val : (n->op != opSizeOf)));
  unsleft = n->child[0]->base == bsInt && n->child[0]->sign == sgnUnsigned;

  binary = operatorIsBinary(n->op);

  if (binary)
  {
    int update = updateVars;
    if ((cond && n->child[2]->val) || (n->op == opAndAnd && !left) || (n->op == opOrOr && left))
      update = 0;
    right = eval(n->child[1], update);
    unsright = n->child[1]->base == bsInt && n->child[1]->sign == sgnUnsigned;
  }

  unsop = unsleft || unsright;
  if (!binary)
  {
    unsres = unsleft;
  }
  else
  {
    if (n->op >= opAssignFirst && n->op <= opAssignLast)
      unsres = unsleft;
    else
      unsres = unsop;
  }

  switch (n->op)
  {
  // Unary
  case opPostInc:
  case opPostDec:
  case opUnaryPlus:
    break;
  case opPreInc:
    ++left;
    break;
  case opPreDec:
    --left;
    break;
  case opUnaryMinus:
    left = -left;
    break;
  case opCompl:
    left = ~left;
    break;
  case opLogicNot:
    unsres = 0;
    left = !left;
    break;
  case opSizeOf:
    unsres = 1;
    switch (n->child[0]->base)
    {
    case bsChar: left = 1; break;
    case bsShort: left = 2; break;
    case bsInt: left = 4; break;
    }
    break;
  case opCastUChar:
    left = (unsigned char)left;
    n->base = bsChar;
    n->sign = sgnUnsigned;
    break;
  case opCastSChar:
    left = (signed char)left;
    n->base = bsChar;
    n->sign = sgnSigned;
    break;
  case opCastUShort:
    left = (unsigned short)left;
    n->base = bsShort;
    n->sign = sgnUnsigned;
    break;
  case opCastSShort:
    left = (short)left;
    n->base = bsShort;
    n->sign = sgnSigned;
    break;
  case opCastUInt:
    n->base = bsInt;
    n->sign = sgnUnsigned;
    break;
  case opCastSInt:
    n->base = bsInt;
    n->sign = sgnSigned;
    break;
  // Binary
  case opMul:
    left *= right;
    break;
  case opDiv:
    if (unsop)
      left /= (unsigned)right;
    else
      left /= right;
    break;
  case opMod:
    if (unsop)
      left %= (unsigned)right;
    else
      left %= right;
    break;
  case opAdd:
    left += right;
    break;
  case opSub:
    left -= right;
    break;
  case opShl:
    unsres = unsleft;
    left <<= right;
    break;
  case opShr:
    unsres = unsleft;
    if (unsleft)
      left = (unsigned)left >> right;
    else
      left >>= right;
    break;
  case opLT:
    unsres = 0;
    if (unsop)
      left = (unsigned)left < (unsigned)right;
    else
      left = left < right;
    break;
  case opGT:
    unsres = 0;
    if (unsop)
      left = (unsigned)left > (unsigned)right;
    else
      left = left > right;
    break;
  case opLE:
    unsres = 0;
    if (unsop)
      left = (unsigned)left <= (unsigned)right;
    else
      left = left <= right;
    break;
  case opGE:
    unsres = 0;
    if (unsop)
      left = (unsigned)left >= (unsigned)right;
    else
      left = left >= right;
    break;
  case opEQ:
    unsres = 0;
    left = left == right;
    break;
  case opNE:
    unsres = 0;
    left = left != right;
    break;
  case opAnd:
    left &= right;
    break;
  case opOr:
    left |= right;
    break;
  case opXor:
    left ^= right;
    break;
  case opAndAnd:
    unsres = 0;
    left = left && right;
    break;
  case opOrOr:
    unsres = 0;
    left = left || right;
    break;
  case opAssign:
    left = right;
    break;
  case opAssignMul:
    left *= right;
    break;
  case opAssignDiv:
    if (unsop)
      left /= (unsigned)right;
    else
      left /= right;
    break;
  case opAssignMod:
    if (unsop)
      left %= (unsigned)right;
    else
      left %= right;
    break;
  case opAssignAdd:
    left += right;
    break;
  case opAssignSub:
    left -= right;
    break;
  case opAssignShl:
    left <<= right;
    break;
  case opAssignShr:
    if (unsleft)
      left = (unsigned)left >> right;
    else
      left >>= right;
    break;
  case opAssignAnd:
    left &= right;
    break;
  case opAssignXor:
    left ^= right;
    break;
  case opAssignOr:
    left |= right;
    break;
  case opComma:
    left = right;
    n->base = n->child[1]->base;
    n->sign = n->child[1]->sign;
    break;
  case opCond:
    if (!n->child[2]->val)
      left = right;
    break;
  default:;
  }

  if (operatorNeedsLvalue(n->op))
  {
    if (updateVars)
    {
      switch (n->op)
      {
      case opPostInc:
        n->child[0]->val++;
        break;
      case opPostDec:
        n->child[0]->val--;
        break;
      default:;
        n->child[0]->val = left;
        break;
      }
      truncVal(n->child[0]);
    }

    n->base = n->child[0]->base;
    n->sign = n->child[0]->sign;
    n->val = left;
    truncVal(n);
    left = n->val;
  }
  else if (n->op != opComma &&
           !(n->op >= opCastIntFirst && n->op <= opCastIntLast))
  {
    n->base = bsInt;
    n->sign = unsres ? sgnUnsigned : sgnSigned;
  }

  return n->val = left;
}

Node* dupSubExpr(Node* n)
{
  Node* p = NULL;
  if (n)
  {
    p = newNode();
    *p = *n;
    p->child[2] = dupSubExpr(n->child[2]);
    p->child[0] = dupSubExpr(n->child[0]);
    p->child[1] = dupSubExpr(n->child[1]);
  }
  return p;
}

void checksVars(Node* n)
{
  switch (n->type)
  {
  case ntVar:
    printf("    if ((int)"); printVarName(n); printf(" != (int)"); printVal(n); printf(")");
    printf(" { failed = 1; printf(\"(int)"); printVarName(n); printf(" : %%d != (int)"); printVal(n); printf("\\n\", "); printVarName(n); printf("); }\n");
    break;
  case ntOperator:
    if (n->child[2])
      checksVars(n->child[2]);
    checksVars(n->child[0]);
    if (n->child[1])
      checksVars(n->child[1]);
    break;
  default:;
  }
}

void genTestCase(int no, int depth)
{
  Node *n, *n2;

  printf("void test%d(void)\n{\n", no);
  printf("  printf(\"-- Test %d (seed: %u) --\\n\");\n", no, mySeed);
  printf("  {\n");
  printf("    int failed = 0;\n\n");
  n = genSubExpr(depth, randBool());
  eval(n, 0);
  n2 = dupSubExpr(n);
  eval(n2, 1);

  printDecls(n);
  printf("    printf(\"- check expr == expected -\\n\");\n");
  printf("    if ((int)("); printSubExpr(n); printf(") != (int)"); printVal(n); printf(")\n");
  printf("      failed = 1;\n");
  checksVars(n2);
  printf("\n");

  reviveVars(n);
  printf("    printf(\"- check passthru(expr) == expected -\\n\");\n");
  printf("    if (passthru((int)("); printSubExpr(n); printf(")) != (int)"); printVal(n); printf(")\n");
  printf("      failed = 1;\n");
  checksVars(n2);
  printf("\n");

  reviveVars(n);
  printf("    printf(\"- print expr -\\n\");\n");
  if (n->base == bsInt && n->sign == sgnUnsigned)
    printf("    printf(\"%%uu\\n\", ");
  else
    printf("    printf(\"%%d\\n\", (int)");
  printSubExpr(n); printf(");\n");
  checksVars(n2);
  printf("\n");

  printf("    if (failed)\n      printf(\"Test %d failed\\n\");\n", no);
  printf("    errors += failed;\n");
  printf("  }\n");
  printf("  printf(\"\\n\");\n");
  printf("}\n\n");

  delNode(n2);
  delNode(n);
}

int main(int argc, char* argv[])
{
  int i, raw = 0, count = 100, depth = 5;
  char* outname = NULL;

  mySrand(time(NULL));

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
    else if (!strcmp(argv[i], "-seed"))
    {
      if (i + 1 < argc)
      {
        ++i;
        mySeed = strtoul(argv[i], NULL, 0);
        continue;
      }
    }
    else if (!strcmp(argv[i], "-count"))
    {
      if (i + 1 < argc)
      {
        ++i;
        count = strtol(argv[i], NULL, 0);
        continue;
      }
    }
    else if (!strcmp(argv[i], "-depth"))
    {
      if (i + 1 < argc)
      {
        ++i;
        depth = strtol(argv[i], NULL, 0);
        continue;
      }
    }

    fprintf(stderr, "Invalid or unsupported command line option '%s'\n", argv[i]);
    return EXIT_FAILURE;
  }

  if (outname)
    freopen(outname, "w", stdout);

  if (!raw)
  {
    printf("#include <limits.h>\n");
    printf("#include <stdio.h>\n");
    printf("#include <stdlib.h>\n\n");
    printf("// Ensure:\n");
    printf("// - expected type sizes\n");
    printf("// - 2's complement arithmetic\n");
    printf("// - arithmetic shifts right of negative values\n");
    printf("extern char StAtIcAsSeRt[(CHAR_BIT == 8) ? 1 : -1];\n");
    printf("extern char StAtIcAsSeRt[(-INT_MAX == INT_MIN + 1) ? 1 : -1];\n");
    printf("extern char StAtIcAsSeRt[((int)UINT_MAX == -1) ? 1 : -1];\n");
    printf("extern char StAtIcAsSeRt[((-1 >> 1) == -1) ? 1 : -1];\n");
    printf("extern char StAtIcAsSeRt[(sizeof(short) == 2) ? 1 : -1];\n");
    printf("extern char StAtIcAsSeRt[(sizeof(int) == 4) ? 1 : -1];\n");
    printf("\n");
  }
  printf("int passthru(int x) { return x; }\n\n");
  printf("int errors = 0;\n\n");

  for (i = 1; i <= count; i++)
    genTestCase(i, depth);

  printf("int main(void)\n{\n");
  for (i = 1; i <= count; i++)
    printf("  test%d();\n", i);
  printf("  if (errors)\n    { printf(\"%%d test(s) failed\\n\", errors); ");
  if (!raw)
    printf("return EXIT_FAILURE; ");
  else
    printf("return 1; ");
  printf("}\n");
  printf("  printf(\"All tests passed\\n\");\n");
  printf("  return 0;\n}\n");

  return 0;
}
