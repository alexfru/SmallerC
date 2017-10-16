/*
  Generator of tests for testing binary & ternary operator precedence & associativity.

  How to compile for and use under DOS:
    smlrcc -dosh genopa.c -o genopa.exe
    genopa.exe >testopa.c
    smlrcc -dosh testopa.c -o testopa.exe
    testopa.exe
   OR
    smlrcc -dosu genopa.c -o genopa.exe
    genopa.exe >testopa.c
    smlrcc -dosu testopa.c -o testopa.exe
    testopa.exe
   OR
    smlrcc -dosp genopa.c -o genopa.exe
    genopa.exe >testopa.c
    smlrcc -dosp testopa.c -o testopa.exe
    testopa.exe

  How to compile for and use under Windows:
    smlrcc -win genopa.c -o genopa.exe
    genopa.exe >testopa.c
    smlrcc -win testopa.c -o testopa.exe
    testopa.exe

  How to compile for and use under Linux:
    smlrcc -linux genopa.c -o genopa
    ./genopa >testopa.c
    smlrcc -linux testopa.c -o testopa
    ./testopa

  How to compile for and use under MacOS:
    smlrcc -macos genopa.c -o genopa
    ./genopa >testopa.c
    smlrcc -macos testopa.c -o testopa
    ./testopa
*/

/*
  From the C standard:

  (comma-)expression:
    assignment-expression
    (comma-)expression , assignment-expression

  assignment-expression:
    conditional-expression
    unary-expression assignment-operator assignment-expression

  conditional-expression (AKA constant-expression):
    logical-OR-exression
    logical-OR-exression ? (comma-)expression : conditional-expression

  logical-OR-exression:
    logical-AND-exression
    logical-OR-exression || logical-AND-expression

  logical-AND-exression:
    inclusive-OR-expression
    logical-AND-exression && inclusive-OR-expression

  inclusive-OR-expression:
    exclusive-OR-expression
    inclusive-OR-expression | exclusive-OR-expression

  exclusive-OR-expression:
    AND-expression
    exclusive-OR-expression ^ AND-expression

  AND-expression:
    equality-expression
    AND-expression & equality-expression

  equality-expression:
    relational-expression
    equality-expression (non)equality-operator relational-expression

  relational-expression:
    shift-expression
    relational-expression relational-operator shift-expression

  shift-expression:
    additive-expression
    shift-expression shift-operator additive-expression

  additive-expression:
    multiplicative-expression
    additive-expression additive-operator multiplicative-expression

  multiplicative-expression:
    cast-expression
    multiplicative-expression multiplicative-operator cast-expression

  We're not interested in the details of the following:
  - logical-OR-exression through shift-expression (they're all the same)
  - cast-expression
  - unary-expression
*/

#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Ensure:\n");
// - expected type sizes\n");
extern char StAtIcAsSeRt[(CHAR_BIT == 8) ? 1 : -1];
extern char StAtIcAsSeRt[(sizeof(int) == 4) ? 1 : -1];

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

typedef struct Node Node;
struct Node
{
  int type;
  int varNum;
  unsigned varVal;
  Node* child[3]; // 3 operands max (ternary conditional operator needs 3 operands: child[2] ? child[0] : child[1])
};

int Allowance[128];
int VarCnt;

void ReInit(void)
{
  Allowance['-'] = 7;
  Allowance['*'] = 6;
  Allowance['?'] = 5;
  Allowance['='] = 4;
  Allowance[','] = 3;
  VarCnt = 1; // v0 is reserved for the result
}

Node* NewNode(void)
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

void DelNode(Node* n)
{
  if (!n) return;
  DelNode(n->child[2]);
  DelNode(n->child[0]);
  DelNode(n->child[1]);
  free(n);
}

Node* Binary(int op, Node* left, Node* right)
{
  Node* n = NewNode();
  n->type = op;
  n->child[0] = left;
  n->child[1] = right;
  return n;
}

Node* Ternary(int op, Node* cond, Node* true_expr, Node* false_expr)
{
  Node* n = NewNode();
  n->type = op;
  n->child[0] = true_expr;
  n->child[1] = false_expr;
  n->child[2] = cond;
  return n;
}

int CanDo(int op)
{
  int r;
  if (!Allowance[op])
    return 0;
  r = randBool();
  Allowance[op] -= r;
  return r;
}

Node* GenLvalExpr(void)
{
  Node* n = NewNode();
  n->type = 'L';
  n->varNum = VarCnt++;
  n->varVal = myRand() & 3;
  return n;
}

Node* GenMulExpr(void)
{
  if (CanDo('*'))
  {
    Node* left = GenMulExpr();
    Node* right = GenLvalExpr(); // Skip cast-expr all the way to unary-expr
    return Binary('*', left, right);
  }
  return GenLvalExpr(); // Skip cast-expr all the way to unary-expr
}

Node* GenAddExpr(void)
{
  if (CanDo('-'))
  {
    Node* left = GenAddExpr();
    Node* right = GenMulExpr();
    return Binary('-', left, right);
  }
  return GenMulExpr();
}

Node* GenCommaExpr(void);

Node* GenCondExpr(void)
{
  if (CanDo('?'))
  {
    Node* cond = GenAddExpr(); // Skip logical-OR-expr all the way to additive-expr
    Node* true_expr = GenCommaExpr();
    Node* false_expr = GenCondExpr();
    return Ternary('?', cond, true_expr, false_expr);
  }
  return GenAddExpr(); // Skip logical-OR-expr all the way to additive-expr
}

Node* GenAssignExpr(void)
{
  if (CanDo('='))
  {
    Node* left = GenLvalExpr();
    Node* right = GenAssignExpr();
    return Binary('=', left, right);
  }
  return GenCondExpr();
}

Node* GenCommaExpr(void)
{
  if (CanDo(','))
  {
    Node* left = GenCommaExpr();
    Node* right = GenAssignExpr();
    return Binary(',', left, right);
  }
  return GenAssignExpr();
}

void PrintDecl(Node* n)
{
  printf("    unsigned v%d = %uu;\n", n->varNum, n->varVal);
}

void PrintDecls(Node* n)
{
  if (!n)
    return;
  switch (n->type)
  {
  case 'L':
    PrintDecl(n);
    break;
  default:
    PrintDecls(n->child[2]);
    PrintDecls(n->child[0]);
    PrintDecls(n->child[1]);
    break;
  }
}

void PrintExpr(Node* n)
{
  switch (n->type)
  {
  case 'L':
    printf("v%d", n->varNum);
    break;
  case '?':
    PrintExpr(n->child[2]);
    printf(" ? ");
    PrintExpr(n->child[0]);
    printf(" : ");
    PrintExpr(n->child[1]);
    break;
  default:
    PrintExpr(n->child[0]);
    printf(" %c ", n->type);
    PrintExpr(n->child[1]);
    break;
  }
}

Node* DupExpr(Node* n)
{
  Node* p = NULL;
  if (n)
  {
    p = NewNode();
    *p = *n;
    p->child[2] = DupExpr(n->child[2]);
    p->child[0] = DupExpr(n->child[0]);
    p->child[1] = DupExpr(n->child[1]);
  }
  return p;
}

unsigned Eval(Node* n)
{
  switch (n->type)
  {
  case ',':
    Eval(n->child[0]);
    return Eval(n->child[1]);
  case '?':
    if (Eval(n->child[2]))
      return Eval(n->child[0]);
    return Eval(n->child[1]);
  case '=':
    n->child[0]->varVal = Eval(n->child[1]);
    return n->child[0]->varVal;
  case '*':
    return Eval(n->child[0]) * Eval(n->child[1]);
  case '-':
    return Eval(n->child[0]) - Eval(n->child[1]);
  default:
  case 'L':
    return n->varVal;
  }
}

void CheckVars(Node* n)
{
  switch (n->type)
  {
  case 'L':
    printf("    if (v%d != %uu) ", n->varNum, n->varVal);
    printf("{ failed = 1; printf(\"v%d != %uu\\n\"); }\n", n->varNum, n->varVal);
    break;
  default:
    if (n->child[2])
      CheckVars(n->child[2]);
    CheckVars(n->child[0]);
    CheckVars(n->child[1]);
    break;
  }
}

void GenTestCase(int no)
{
  Node *n1, *n2;
  unsigned v0;
  printf("void test%d(void)\n{\n", no);
  printf("  printf(\"-- Test %d (seed: %u) --\\n\");\n", no, mySeed);
  printf("  {\n");
  printf("    int failed = 0;\n");
  ReInit();
  n1 = GenCommaExpr();
  PrintDecls(n1);
  printf("    unsigned v0 = (");
  PrintExpr(n1);
  printf(");\n");
  n2 = DupExpr(n1);
  v0 = Eval(n2);
  CheckVars(n2);
  printf("    if (v0 != %uu) ", v0);
  printf("{ failed = 1; printf(\"v0 != %uu\\n\"); }\n", v0);
  printf("    if (failed)\n      printf(\"Test %d failed\\n\");\n", no);
  printf("    errors += failed;\n");
  printf("  }\n");
  printf("  printf(\"\\n\");\n");
  printf("}\n\n");
  DelNode(n1);
  DelNode(n2);
}

int main(int argc, char* argv[])
{
  int i, raw = 0, count = 100;
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
    printf("extern char StAtIcAsSeRt[(CHAR_BIT == 8) ? 1 : -1];\n");
    printf("extern char StAtIcAsSeRt[(sizeof(int) == 4) ? 1 : -1];\n");
    printf("\n");
  }
  printf("int errors = 0;\n\n");
  for (i = 1; i <= count; i++)
    GenTestCase(i);
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
