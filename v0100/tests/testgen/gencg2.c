/*
  Generator of tests for testing of relational/equality operators
  and if statements (conditional branches). Primarily for MIPS.

  How to compile for and use under DOS:
    smlrcc -dosp gencg2.c -o gencg2.exe
    gencg2.exe >testcg2.c
    smlrcc -dosp testcg2.c -o testcg2.exe
    testcg2.exe

  How to compile for and use under Windows:
    smlrcc -win gencg2.c -o gencg2.exe
    gencg2.exe >testcg2.c
    smlrcc -win testcg2.c -o testcg2.exe
    testcg2.exe

  How to compile for and use under Linux:
    smlrcc -linux gencg2.c -o gencg2
    ./gencg2 >testcg2.c
    smlrcc -linux testcg2.c -o testcg2
    ./testcg2

  How to compile for and use under MacOS:
    smlrcc -macos gencg2.c -o gencg2
    ./gencg2 >testcg2.c
    smlrcc -macos testcg2.c -o testcg2
    ./testcg2
*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

// Ensure:
// - expected type sizes
extern char StAtIcAsSeRt[(CHAR_BIT == 8) ? 1 : -1];
extern char StAtIcAsSeRt[(sizeof(int) == 4) ? 1 : -1];

int expected(unsigned signed_, unsigned opidx, unsigned l, unsigned r)
{
  if (signed_)
  {
    l ^= 0x80000000;
    r ^= 0x80000000;
  }
  switch (opidx)
  {
  default:
  case 0: // ==
    return l == r;
  case 1: // !=
    return l != r;
  case 2: // <
    return l < r;
  case 3: // >=
    return l >= r;
  case 4: // <=
    return l <= r;
  case 5: // >
    return l > r;
  }
}

int main(int argc, char* argv[])
{
  int i, raw = 0;
  char* outname = NULL;
  unsigned signed_, lconst, rconst, lidx, ridx, if_, opidx;
  unsigned testValues[] =
  {
    0x00000000,
    0x00000001,
    0x00000002,
    0x7FFFFFFD,
    0x7FFFFFFE,
    0x7FFFFFFF,
    0x80000000,
    0x80000001,
    0x80000002,
    0xFFFFFFFD,
    0xFFFFFFFE,
    0xFFFFFFFF
  };
  char* operators[] =
  {
    "==",
    "!=",
    "<",
    ">=",
    "<=",
    ">",
  };

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

  if (!raw)
  {
    printf("#include <limits.h>\n");
    printf("#include <stdio.h>\n");
    printf("#include <stdlib.h>\n\n");
    printf("// Ensure:\n");
    printf("// - expected type sizes\n");
    printf("// - 2's complement arithmetic\n");
    printf("extern char StAtIcAsSeRt[(CHAR_BIT == 8) ? 1 : -1];\n");
    printf("extern char StAtIcAsSeRt[(-INT_MAX == INT_MIN + 1) ? 1 : -1];\n");
    printf("extern char StAtIcAsSeRt[((int)UINT_MAX == -1) ? 1 : -1];\n");
    printf("extern char StAtIcAsSeRt[(sizeof(int) == 4) ? 1 : -1];\n");
    printf("\n");
  }

  printf("int main(void)\n{\n");
  printf("  unsigned error = 0;\n");

  for (signed_ = 0; signed_ <= 1; signed_++)
  for (lconst = 0; lconst <= 1; lconst++)
  for (rconst = 0; rconst <= 1; rconst++)
  for (lidx = 0; lidx < sizeof testValues / sizeof testValues[0]; lidx++)
  for (ridx = 0; ridx < sizeof testValues / sizeof testValues[0]; ridx++)
  for (opidx = 0; opidx < sizeof operators / sizeof operators[0]; opidx++)
  for (if_ = 0; if_ <= 1; if_++)
  {
    unsigned lval = testValues[lidx];
    unsigned rval = testValues[ridx];
    int e = expected(signed_, opidx, lval, rval);

    printf("  {\n");

    if (!lconst)
      printf("    %s l = %s0x%08Xu;\n", signed_ ? "int" : "unsigned", signed_ ? "(int)" : "", lval);
    if (!rconst)
      printf("    %s r = %s0x%08Xu;\n", signed_ ? "int" : "unsigned", signed_ ? "(int)" : "", rval);

    if (if_)
      printf("    if (");
    else
      printf("    int v = ");

    if (lconst)
      printf("%s0x%08Xu", signed_ ? "(int)" : "", lval);
    else
      printf("l");

    printf(" %s ", operators[opidx]);

    if (rconst)
      printf("%s0x%08Xu", signed_ ? "(int)" : "", rval);
    else
      printf("r");

    if (if_)
    {
      if (e)
        printf("); else error = __LINE__;\n");
      else
        printf(") error = __LINE__;\n");
    }
    else
    {
      printf("; if (v == %d); else error = __LINE__;\n", e);
    }

    printf("  }\n");
  }

  printf("  if (error) { printf(\"Test on line %%u failed\\n\", error); return %s; }\n", raw ? "1" : "EXIT_FAILURE");
  printf("  printf(\"All tests passed\\n\");\n");
  printf("  return 0;\n}\n");

  return 0;
}
