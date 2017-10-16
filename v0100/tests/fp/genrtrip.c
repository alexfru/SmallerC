/*
  Generator of floating point round-trip tests.

  How to compile for and use under DOS:
    smlrcc -dosp genrtrip.c -o genrtrip.exe
    genrtrip.exe >rtrip.c
    smlrcc -dosp rtrip.c -o rtrip.exe
    rtrip.exe

  How to compile for and use under Windows:
    smlrcc -win genrtrip.c -o genrtrip.exe
    genrtrip.exe >rtrip.c
    smlrcc -win rtrip.c -o rtrip.exe
    rtrip.exe

  How to compile for and use under Linux:
    smlrcc -linux genrtrip.c -o genrtrip
    ./genrtrip >rtrip.c
    smlrcc -linux rtrip.c -o rtrip
    ./rtrip

  How to compile for and use under MacOS:
    smlrcc -macos genrtrip.c -o genrtrip
    ./genrtrip >rtrip.c
    smlrcc -macos rtrip.c -o rtrip
    ./rtrip
*/

#include <limits.h>
#include <float.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Ensure:
// - expected type sizes
extern char StAtIcAsSeRt[(CHAR_BIT == 8) ? 1 : -1];
extern char StAtIcAsSeRt[(sizeof(int) == 4) ? 1 : -1];
extern char StAtIcAsSeRt[(sizeof(float) == 4) ? 1 : -1];

void test1(unsigned v)
{
  union
  {
    unsigned u;
    float f;
  } u;
  u.u = v;
  // Print v as integer, float and quoted float (string)
  printf("  0x%08X, \"%.*ef\", %.*ef,\n", v, DECIMAL_DIG - 1, u.f, DECIMAL_DIG - 1, u.f);
}

void test10(unsigned v)
{
  // The mask helps avoid NaNs and infinities
  test1(v & 0x5FFFFFFF);
  test1(~v & 0x5FFFFFFF);
}

void test4bits(void)
{
  int i, j, k, l;
  for (i = 3; i <= 30; i++)
    for (j = 2; j < i; j++)
      for (k = 1; k < j; k++)
        for (l = 0; l < k; l++)
          test10((1u << i) | (1u << j) | (1u << k) | (1u << l));
}

void test3bits(void)
{
  int j, k, l;
  for (j = 2; j <= 30; j++)
    for (k = 1; k < j; k++)
      for (l = 0; l < k; l++)
        test10((1u << j) | (1u << k) | (1u << l));
}

void test2bits(void)
{
  int k, l;
  for (k = 1; k <= 30; k++)
    for (l = 0; l < k; l++)
      test10((1u << k) | (1u << l));
}

void test1bits(void)
{
  int l;
  for (l = 0; l <= 30; l++)
    test10((1u << l));
}

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

void testrand(unsigned cnt)
{
  while (cnt--)
  {
    unsigned v;
    v = myRand() & 0x7FFF;
    v = (v << 15) | (myRand() & 0x7FFF);
    v = (v << 1) | (myRand() & 0x1);
    test10(v);
  }
}

int main(int argc, char* argv[])
{
  int i;
  char* outname = NULL;

//  mySrand(time(NULL));

  for (i = 1; i < argc; i++)
  {
    if (!strcmp(argv[i], "-o"))
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

  printf("#include <limits.h>\n");
  printf("#include <float.h>\n");
  printf("#include <stdio.h>\n");
  printf("#include <string.h>\n\n");
  printf("#include <stdlib.h>\n\n");
  printf("// Ensure:\n");
  printf("// - expected type sizes\n");
  printf("extern char StAtIcAsSeRt[(CHAR_BIT == 8) ? 1 : -1];\n");
  printf("extern char StAtIcAsSeRt[(sizeof(int) == 4) ? 1 : -1];\n");
  printf("extern char StAtIcAsSeRt[(sizeof(float) == 4) ? 1 : -1];\n");
  printf("\n");

  puts("struct { unsigned u; char* s; float f; } a[] =\n{");
  test1bits();
  test2bits();
  test3bits();
  test4bits();
  testrand(10000);
  puts("};\n");

  // TBD!!! Also test sscanf(), strtod(), atof() when they're ready.
  puts("int main(void)\n"
       "{\n"
       "  unsigned i, t = 0, p = 0;\n"
       "  for (i = 0; i < sizeof a / sizeof a[0]; i++)\n"
       "  {\n"
       "    union\n"
       "    {\n"
       "      unsigned u;\n"
       "      float f;\n"
       "    } u;\n"
       "    int pass = memcmp(&a[i].u, &a[i].f, sizeof a[i].u) == 0;\n"
       "    u.f = a[i].f;\n"
       "    if (!pass)\n"
       "      printf(\"%s: 0x%08X -> \\\"%s\\\" -> 0x%08X -> \\\"%.*e\\\"\\n\",\n"
       "             pass ? \"pass\" : \"fail\",\n"
       "             a[i].u,\n"
       "             a[i].s,\n"
       "             u.u,\n"
       "             DECIMAL_DIG - 1,\n"
       "             u.f);\n"
       "    p += pass;\n"
       "    t++;\n"
       "  }\n"
       "  printf(\"%u/%u passed\\n\", p, t);\n"
       "  return (p == t) ? 0 : EXIT_FAILURE;\n"
       "}");

  return 0;
}
