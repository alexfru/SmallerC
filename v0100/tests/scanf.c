/*
  Test for *scanf() functions.

  How to compile for DOS (huge/.EXE, unreal/.EXE, 32-bit DPMI/.EXE):
    smlrcc -dosh scanf.c -o scanfdh.exe
    smlrcc -dosu scanf.c -o scanfdu.exe
    smlrcc -dosp scanf.c -o scanfdp.exe

  How to compile for Windows:
    smlrcc -win scanf.c -o scanfw.exe

  How to compile for Linux:
    smlrcc -linux scanf.c -o scanfl

  How to compile for MacOS:
    smlrcc -macos scanf.c -o scanfm
*/

#include <limits.h>
// <limits.h> should pull <features.h> on gcc with glibc,
// which defines __GNU_LIBRARY__ or __GLIBC__.
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

extern char StAtIcAsSeRt[(CHAR_BIT == 8) ? 1 : -1];
extern char StAtIcAsSeRt[(sizeof(short) == 2) ? 1 : -1];
extern char StAtIcAsSeRt[(sizeof(void*) == sizeof(short*)) ? 1 : -1];
extern char StAtIcAsSeRt[(sizeof(void*) == sizeof(int*)) ? 1 : -1];
extern char StAtIcAsSeRt[(sizeof(void*) == sizeof(long*)) ? 1 : -1];
extern char StAtIcAsSeRt[(sizeof(void*) == sizeof(size_t*)) ? 1 : -1];
extern char StAtIcAsSeRt[(sizeof(void*) == sizeof(float*)) ? 1 : -1];
extern char StAtIcAsSeRt[(sizeof(void*) == sizeof(double*)) ? 1 : -1];

#define MAX_OUTS 8
#define MAX_CHARS 128

typedef struct
{
  int line;
  char* in;
  char* fmt;
  int result;
  struct Out
  {
    enum tOutType
    {
      tAscii,
      tAsciiZ,
      tSChar,
      tUChar,
      tShort,
      tUShort,
      tInt,
      tUInt,
      tLong,
      tULong,
      tSizeT,
      tFloat,
      tDouble,
    } type;
    void* out;
    void* expected[2];
  } outs[MAX_OUTS];
} TestCase;

signed char scouts[MAX_OUTS];
unsigned char ucouts[MAX_OUTS];
short souts[MAX_OUTS];
unsigned short usouts[MAX_OUTS];
int iouts[MAX_OUTS];
unsigned uiouts[MAX_OUTS];
long louts[MAX_OUTS];
unsigned long ulouts[MAX_OUTS];
size_t szouts[MAX_OUTS];
float fouts[MAX_OUTS];
double douts[MAX_OUTS];
char couts[MAX_OUTS + 1][MAX_CHARS + 1];

signed char schars[128];
unsigned char uchars[256];
short shorts[256];
unsigned short ushorts[256];
int ints[256];
unsigned uints[256];

float f_inf; // -INFINITY (INFINITY is non-const expression in Open Watcom)
float finf; // INFINITY (ditto)
float fnan; // NAN (ditto)

void Init(void)
{
  unsigned i;
  for (i = 0; i < sizeof ints / sizeof ints[0]; i++)
    uints[i] = ints[i] = ushorts[i] = shorts[i] = uchars[i] = i;
  for (i = 0; i < sizeof schars / sizeof schars[0]; i++)
    schars[i] = i;
  f_inf = -INFINITY;
  finf = INFINITY;
  fnan = NAN;
}

void PrintHeader(TestCase* t)
{
  printf("FAILURE: line %d: scanf(\"%s\", \"%s\", ...): ",
         t->line, t->in, t->fmt);
}

void PrintOutHeader(int i)
{
  printf("out[%d]: ", i);
}

int CheckRes(TestCase* t, int res)
{
  if (t->result == res)
    return 0;

  PrintHeader(t);
  printf("%d != %d\n",
         res, t->result);
  return 1;
}

int fcmp(float v, float emin, float emax)
{
  // Make sure either both emin and emax are NANs or none.
  assert((emin != emin) == (emax != emax));
  // Check for NAN.
  if (emin != emin)
  {
    return v != v;
  }
  assert(emin <= emax);
  // Range check.
  if (emin <= v && v <= emax)
  {
    // Special case for comparing with +/-0.
    if (emin == 0 && emax == 0 && 1 / emin == 1 / emax)
    {
      // If emin and emax are both zeroes of the same sign, check the sign.
      return 1 / emin == 1 / v;
    }
    return 1;
  }
  return 0;
}

int dcmp(double v, double emin, double emax)
{
  // Make sure either both emin and emax are NANs or none.
  assert((emin != emin) == (emax != emax));
  // Check for NAN.
  if (emin != emin)
  {
    return v != v;
  }
  assert(emin <= emax);
  // Range check.
  if (emin <= v && v <= emax)
  {
    // Special case for comparing with +/-0.
    if (emin == 0 && emax == 0 && 1 / emin == 1 / emax)
    {
      // If emin and emax are both zeroes of the same sign, check the sign.
      return 1 / emin == 1 / v;
    }
    return 1;
  }
  return 0;
}

int CheckOut(TestCase* t, int i)
{
  int res = 1;
  struct Out* o = &t->outs[i];
  // skip if no output or no expected output
  if (!o->out || !o->expected[0])
    return 0;
  switch (o->type)
  {
    case tAscii:
    {
      char *v = o->out, *e = o->expected[0];
      size_t len = strlen(e);
      if (strncmp(v, e, len))
        PrintHeader(t), PrintOutHeader(i),
        printf("\"%.*s\" != \"%s\"\n",
               (int)len, v, e);
      else
        res = 0;
      break;
    }
    case tAsciiZ:
    {
      char *v = o->out, *e = o->expected[0];
      if (strcmp(v, e))
        PrintHeader(t), PrintOutHeader(i),
        printf("\"%s\" != \"%s\"\n",
               v, e);
      else
        res = 0;
      break;
    }
    case tSChar:
    {
      signed char *v = o->out, *e = o->expected[0];
      if (*v != *e)
        PrintHeader(t), PrintOutHeader(i),
        printf("%d != %d\n",
               *v, *e);
      else
        res = 0;
      break;
    }
    case tUChar:
    {
      unsigned char *v = o->out, *e = o->expected[0];
      if (*v != *e)
        PrintHeader(t), PrintOutHeader(i),
        printf("%u != %u\n",
               *v, *e);
      else
        res = 0;
      break;
    }
    case tShort:
    {
      short *v = o->out, *e = o->expected[0];
      if (*v != *e)
        PrintHeader(t), PrintOutHeader(i),
        printf("%d != %d\n",
               *v, *e);
      else
        res = 0;
      break;
    }
    case tUShort:
    {
      unsigned short *v = o->out, *e = o->expected[0];
      if (*v != *e)
        PrintHeader(t), PrintOutHeader(i),
        printf("%u != %u\n",
               *v, *e);
      else
        res = 0;
      break;
    }
    case tInt:
    {
      int *v = o->out, *e = o->expected[0];
      if (*v != *e)
        PrintHeader(t), PrintOutHeader(i),
        printf("%d != %d\n",
               *v, *e);
      else
        res = 0;
      break;
    }
    case tUInt:
    {
      unsigned *v = o->out, *e = o->expected[0];
      if (*v != *e)
        PrintHeader(t), PrintOutHeader(i),
        printf("%u != %u\n",
               *v, *e);
      else
        res = 0;
      break;
    }
    case tLong:
    {
      long *v = o->out, *e = o->expected[0];
      if (*v != *e)
        PrintHeader(t), PrintOutHeader(i),
        printf("%ld != %ld\n",
               *v, *e);
      else
        res = 0;
      break;
    }
    case tULong:
    {
      unsigned long *v = o->out, *e = o->expected[0];
      if (*v != *e)
        PrintHeader(t), PrintOutHeader(i),
        printf("%lu != %lu\n",
               *v, *e);
      else
        res = 0;
      break;
    }
    case tSizeT:
    {
      size_t *v = o->out, *e = o->expected[0];
      if (*v != *e)
        PrintHeader(t), PrintOutHeader(i),
        printf("%zu != %zu\n",
               *v, *e);
      else
        res = 0;
      break;
    }
    case tFloat:
    {
      float *v = o->out, *e0 = o->expected[0], *e1 = o->expected[1];
      if (!e1)
        e1 = e0;
      if (!fcmp(*v, *e0, *e1))
        PrintHeader(t), PrintOutHeader(i),
        printf("%+e != [%+e , %+e]\n",
               *v, *e0, *e1);
      else
        res = 0;
      break;
    }
    case tDouble:
    {
      double *v = o->out, *e0 = o->expected[0], *e1 = o->expected[1];
      if (!e1)
        e1 = e0;
      if (!dcmp(*v, *e0, *e1))
        PrintHeader(t), PrintOutHeader(i),
        printf("%+e != [%+e , %+e]\n",
               *v, *e0, *e1);
      else
        res = 0;
      break;
    }
  }
  return res;
}

int RunCase(TestCase* t)
{
  int res;
  int i;
  for (i = 0; i < MAX_OUTS; i++)
    if (t->outs[i].out)
    {
      scouts[i] = SCHAR_MIN;
      ucouts[i] = UCHAR_MAX;
      souts[i] = SHRT_MIN;
      usouts[i] = USHRT_MAX;
      iouts[i] = INT_MIN;
      uiouts[i] = UINT_MAX;
      louts[i] = LONG_MIN;
      ulouts[i] = ULONG_MAX;
      szouts[i] = (size_t)-1; // SIZE_MAX
      fouts[i] = NAN;
      douts[i] = NAN;
      switch (t->outs[i].type)
      {
        case tAscii:
        case tAsciiZ:
          memset(couts[i], '~', sizeof couts[i]);
          couts[i][sizeof couts[i] - 1] = '\0';
          break;
        case tFloat:
          if (t->outs[i].expected[0])
          {
            float f = *(float*)t->outs[i].expected[0];
            if (f != f)
              fouts[i] = 0.0f;
          }
          break;
        case tDouble:
          if (t->outs[i].expected[0])
          {
            double f = *(double*)t->outs[i].expected[0];
            if (f != f)
              fouts[i] = 0.0;
          }
          break;
      }
    }
  memset(couts[MAX_OUTS], '\0', sizeof couts[MAX_OUTS]);
  res = sscanf(t->in,
               t->fmt,
               t->outs[0].out,
               t->outs[1].out,
               t->outs[2].out,
               t->outs[3].out,
               t->outs[4].out,
               t->outs[5].out,
               t->outs[6].out,
               t->outs[7].out);
  res = CheckRes(t, res);
  for (i = 0; i < MAX_OUTS; i++)
    res |= CheckOut(t, i);
  return res;
}

/*
  Things to test:
  - text, incl spaces and %% in format
  - EOF: before 1st assignment, after 1st
  - width
  - %[h[h]]diouxX
  - %efgEFG
  - lz
  - %c
  - %[],%[^],%[]],%[^]],%[-],%[^-]
  - %s
  - assignment suppression: *
  - %[h[h]]n
  - %p
  - multiple assignments
  - problematic sequences with incomplete ungetc()
  - SCN* macros from <inttypes.h>
  Use an input file to check what's not consumed yet by *scanf()?
*/

signed char sc_1 = -1;

short s_1 = -1;
short s_32768 = -32767-1;
short s32767 = 32767;
unsigned short us65535 = 65535u;

int i_123 = -123;

long l_123 = -123L;
unsigned long ul65536 = 65536UL;

size_t sz65535 = 65535u;

float f_1_5 = -1.5f;
float f_0 = -0.0f;
float f0 = 0.0f;
float f1 = 1.0f;
float f3e_45 = 3e-45f;
float f0_099 = 0.099f;
float f0_101 = 0.101f;
float f1_5 = 1.5f;
float f10 = 10.0f;
float f20 = 20.0f;
float f200 = 200.0f;
float f3_39e_38 = 3.39e38f;

double d_16777215 = -16777215.0;
double d0_001953125 = 0.001953125;
double d0_99999e_30 = 0.99999e-30;
double d1_00001e_30 = 1.00001e-30;

TestCase cases[] =
{
  { __LINE__, "", "%d", EOF },
  { __LINE__, " ", "%d", EOF },
  { __LINE__, "z", "%d", 0 },
  { __LINE__, "-z", "%d", 0 },
  { __LINE__, "123", "%d", 1, { tInt, &iouts[0], { &ints[123] } } },
  { __LINE__, "-123", "%d", 1, { tInt, &iouts[0], { &i_123 } } },
  { __LINE__, "123", "%u", 1, { tUInt, &uiouts[0], { &uints[123] } } },
  { __LINE__, "0x123", "%d", 1, { tInt, &iouts[0], { &ints[0] } } },
  { __LINE__, "", "%e", EOF },
  { __LINE__, " ", "%e", EOF },
  { __LINE__, "z", "%e", 0 },
  { __LINE__, "-z", "%e", 0 },
  { __LINE__, "-1.5", "%e", 1, { tFloat, &fouts[0], { &f_1_5 } } },
  { __LINE__, "1.5", "%f", 1, { tFloat, &fouts[0], { &f1_5 } } },
  { __LINE__, "-1.5", "%g", 1, { tFloat, &fouts[0], { &f_1_5 } } },
  { __LINE__, "1.5", "%E", 1, { tFloat, &fouts[0], { &f1_5 } } },
#if !defined(__MSVCRT__) && !defined(__MINGW32__)
  { __LINE__, "-1.5", "%F", 1, { tFloat, &fouts[0], { &f_1_5 } } }, // %F not recognized by msvcrt
#endif
  { __LINE__, "1.5", "%G", 1, { tFloat, &fouts[0], { &f1_5 } } },
  { __LINE__, "+.01e+01", "%e", 1, { tFloat, &fouts[0], { &f0_099, &f0_101 } } },
  { __LINE__, "1.4e-45", "%e", 1, { tFloat, &fouts[0], { &f0, &f3e_45 } } },
  { __LINE__, "3.4e38", "%e", 1, { tFloat, &fouts[0], { &f3_39e_38, &finf } } },
  { __LINE__, "-n", "%e", 0 },
  { __LINE__, "n", "%e", 0 },
  { __LINE__, "-i", "%e", 0 },
  { __LINE__, "i", "%e", 0 },
  { __LINE__, "-na", "%e", 0 },
  { __LINE__, "na", "%e", 0 },
#if !defined(__MSVCRT__) && !defined(__MINGW32__) && !defined(__WATCOMC__)
  // nan,inf not recognized by msvcrt,OW
  { __LINE__, "-nan", "%e", 1, { tFloat, &fouts[0], { &fnan } } },
  { __LINE__, "-NAN", "%e", 1, { tFloat, &fouts[0], { &fnan } } },
  { __LINE__, "-nAn", "%e", 1, { tFloat, &fouts[0], { &fnan } } },
  { __LINE__, "-NaN", "%e", 1, { tFloat, &fouts[0], { &fnan } } },
  { __LINE__, "nan", "%e", 1, { tFloat, &fouts[0], { &fnan } } },
  { __LINE__, "NAN", "%e", 1, { tFloat, &fouts[0], { &fnan } } },
  { __LINE__, "nAn", "%e", 1, { tFloat, &fouts[0], { &fnan } } },
  { __LINE__, "NaN", "%e", 1, { tFloat, &fouts[0], { &fnan } } },
  { __LINE__, "-in", "%e", 0 },
  { __LINE__, "in", "%e", 0 },
  { __LINE__, "-infi", "%e", 0 },
  { __LINE__, "infi", "%e", 0 },
  { __LINE__, "-infin", "%e", 0 },
  { __LINE__, "infin", "%e", 0 },
  { __LINE__, "-infinit", "%e", 0 },
  { __LINE__, "infinit", "%e", 0 },
  { __LINE__, "-infiniti", "%e", 0 },
  { __LINE__, "infiniti", "%e", 0 },
  { __LINE__, "-infinity", "%e", 1, { tFloat, &fouts[0], { &f_inf } } },
  { __LINE__, "infinity", "%e", 1, { tFloat, &fouts[0], { &finf } } },
  { __LINE__, "-InFiNiTy", "%e", 1, { tFloat, &fouts[0], { &f_inf } } },
  { __LINE__, "+iNfInItY", "%e", 1, { tFloat, &fouts[0], { &finf } } },
  { __LINE__, "infinityz", "%e", 1, { tFloat, &fouts[0], { &finf } } },
  { __LINE__, "nano", "%e", 1, { tFloat, &fouts[0], { &fnan } } },
  { __LINE__, "info", "%e", 1, { tFloat, &fouts[0], { &finf } } },
  { __LINE__, "nano", "%3e", 1, { tFloat, &fouts[0], { &fnan } } },
  { __LINE__, "info", "%3e", 1, { tFloat, &fouts[0], { &finf } } },
#endif
#if !defined(__GNU_LIBRARY__) && !defined(__GLIBC__)
  { __LINE__, "-", "%d", EOF }, // glibc returns 0
  { __LINE__, "-", "%e", EOF }, // glibc returns 0
  { __LINE__, "0x", "%x", EOF, { tUInt, &uiouts[0] } }, // glibc returns 1/0
  { __LINE__, "0x ", "%x", 0, { tUInt, &uiouts[0] } }, // glibc returns 1/0
  { __LINE__, "0x", "%i", EOF, { tInt, &iouts[0] } }, // glibc returns 1/0
#endif
  { __LINE__, "- ", "%d", 0 },
  { __LINE__, "- ", "%e", 0 },
#if !defined(__GNU_LIBRARY__) && !defined(__GLIBC__) && !defined(__WATCOMC__)
  { __LINE__, ".", "%e", EOF, { tFloat, &fouts[0] } }, // glibc returns 0; OW returns 1/0.f
#endif
#if !defined(__WATCOMC__)
  { __LINE__, ". ", "%e", 0, { tFloat, &fouts[0] } }, // OW returns 1/0.f
  { __LINE__, ".e", "%e", 0, { tFloat, &fouts[0] } }, // OW returns 1/0.f
#endif
  { __LINE__, "e", "%e", 0 },
  { __LINE__, "-e", "%e", 0 },
#if defined(__SMALLER_C__)
  { __LINE__, "42e", "%e", EOF, { tFloat, &fouts[0] } }, // msvcrt,glibc,OW return 1/42.f
  { __LINE__, "42e ", "%e", 0, { tFloat, &fouts[0] } }, // msvcrt,glibc return 1/42.f
  { __LINE__, "42ef", "%e", 0, { tFloat, &fouts[0] } }, // msvcrt,glibc return 1/42.f
  { __LINE__, "42e+", "%e", EOF, { tFloat, &fouts[0] } }, // msvcrt,glibc,OW return 1/42.f
  { __LINE__, "42e+ ", "%e", 0, { tFloat, &fouts[0] } }, // msvcrt,glibc return 1/42.f
  { __LINE__, "42e+z", "%e", 0, { tFloat, &fouts[0] } }, // msvcrt,glibc return 1/42.f
#endif
  { __LINE__, "1.5,42", "%e,%d", 2, { tFloat, &fouts[0], { &f1_5 }, tInt, &iouts[0], { &ints[42] } } },
  { __LINE__, "1.5,42", "%e , %d", 2, { tFloat, &fouts[0], { &f1_5 }, tInt, &iouts[0], { &ints[42] } } },
  { __LINE__, "1.5  ,  42", "%e , %d", 2, { tFloat, &fouts[0], { &f1_5 }, tInt, &iouts[0], { &ints[42] } } },
  { __LINE__, "1.5  ,  42", "%e ,%d", 2, { tFloat, &fouts[0], { &f1_5 }, tInt, &iouts[0], { &ints[42] } } },
  { __LINE__, "1.5 ,42", "%e,%d", 1, { tFloat, &fouts[0], { &f1_5 } } },
  { __LINE__, "1.5", "%e,%d", 1, { tFloat, &fouts[0], { &f1_5 } } },
  { __LINE__, "1.5,", "%e,%d", 1, { tFloat, &fouts[0], { &f1_5 } } },
  { __LINE__, "1.5, ", "%e,%d", 1, { tFloat, &fouts[0], { &f1_5 } } },
  { __LINE__, "1.5,-", "%e,%d", 1, { tFloat, &fouts[0], { &f1_5 } } },
  { __LINE__, "1.5,- ", "%e,%d", 1, { tFloat, &fouts[0], { &f1_5 } } },
  { __LINE__, "42,1.5", "%d,%e", 2, { tInt, &iouts[0], { &ints[42] }, tFloat, &fouts[0], { &f1_5 } } },
  { __LINE__, "42,1.5", "%d , %e", 2, { tInt, &iouts[0], { &ints[42] }, tFloat, &fouts[0], { &f1_5 } } },
  { __LINE__, "42  ,  1.5", "%d , %e", 2, { tInt, &iouts[0], { &ints[42] }, tFloat, &fouts[0], { &f1_5 } } },
  { __LINE__, "42  ,  1.5", "%d ,%e", 2, { tInt, &iouts[0], { &ints[42] }, tFloat, &fouts[0], { &f1_5 } } },
  { __LINE__, "42 ,1.5", "%d,%e", 1, { tInt, &iouts[0], { &ints[42] } } },
  { __LINE__, "42", "%d,%e", 1, { tInt, &iouts[0], { &ints[42] } } },
  { __LINE__, "42,", "%d,%e", 1, { tInt, &iouts[0], { &ints[42] } } },
  { __LINE__, "42, ", "%d,%e", 1, { tInt, &iouts[0], { &ints[42] } } },
  { __LINE__, "42,-", "%d,%e", 1, { tInt, &iouts[0], { &ints[42] } } },
  { __LINE__, "42,- ", "%d,%e", 1, { tInt, &iouts[0], { &ints[42] } } },
  { __LINE__, "0x", "%d", 1, { tInt, &iouts[0], { &ints[0] } } },
  { __LINE__, "0x", "%o", 1, { tUInt, &uiouts[0], { &uints[0] } } },
  { __LINE__, "0x", "%u", 1, { tUInt, &uiouts[0], { &uints[0] } } },
  { __LINE__, "0", "%d", 1, { tInt, &iouts[0], { &ints[0] } } },
  { __LINE__, "0", "%i", 1, { tInt, &iouts[0], { &ints[0] } } },
  { __LINE__, "0xFf", "%x", 1, { tUInt, &uiouts[0], { &uints[255] } } },
  { __LINE__, "0XfF", "%x", 1, { tUInt, &uiouts[0], { &uints[255] } } },
  { __LINE__, "0xFf", "%X", 1, { tUInt, &uiouts[0], { &uints[255] } } },
  { __LINE__, "0XfF", "%X", 1, { tUInt, &uiouts[0], { &uints[255] } } },
  { __LINE__, "Ff", "%x", 1, { tUInt, &uiouts[0], { &uints[255] } } },
  { __LINE__, "0xFf", "%i", 1, { tInt, &iouts[0], { &ints[255] } } },
  { __LINE__, "0XfF", "%i", 1, { tInt, &iouts[0], { &ints[255] } } },
  { __LINE__, "08", "%i", 1, { tInt, &iouts[0], { &ints[0] } } },
  { __LINE__, "10", "%d", 1, { tInt, &iouts[0], { &ints[10] } } },
  { __LINE__, "10", "%i", 1, { tInt, &iouts[0], { &ints[10] } } },
  { __LINE__, "10", "%o", 1, { tUInt, &uiouts[0], { &uints[8] } } },
  { __LINE__, "10", "%x", 1, { tUInt, &uiouts[0], { &uints[16] } } },
  { __LINE__, "010", "%d", 1, { tInt, &iouts[0], { &ints[10] } } },
  { __LINE__, "010", "%i", 1, { tInt, &iouts[0], { &ints[8] } } },
  { __LINE__, "010", "%o", 1, { tUInt, &uiouts[0], { &uints[8] } } },
  { __LINE__, "010", "%x", 1, { tUInt, &uiouts[0], { &uints[16] } } },
  { __LINE__, "123", "%2d", 1, { tInt, &iouts[0], { &ints[12] } } },
  { __LINE__, "0.5", "%2e", 1, { tFloat, &fouts[0], { &f0 } } },
#if !defined(__WATCOMC__)
  { __LINE__, "-0.5", "%3e", 1, { tFloat, &fouts[0], { &f_0 } } }, // OW ignores sign of -0.0
#endif
  { __LINE__, "  +1.5999", "%4e", 1, { tFloat, &fouts[0], { &f1_5 } } },
  { __LINE__, "-9", "%1d", 0 },
#if !defined(__GNU_LIBRARY__) && !defined(__GLIBC__)
  { __LINE__, "0x9", "%2x", 0, { tUInt, &uiouts[0] } },  // glibc returns 1/0
#endif
#if !defined(__WATCOMC__)
  { __LINE__, ".9", "%1e", 0, { tFloat, &fouts[0] } }, // OW returns 1/0.f
#endif
  { __LINE__, "1e1", "%e", 1, { tFloat, &fouts[0], { &f10 } } },
  { __LINE__, "1.e1", "%e", 1, { tFloat, &fouts[0], { &f10 } } },
  { __LINE__, ".1e1", "%e", 1, { tFloat, &fouts[0], { &f1 } } },
  { __LINE__, "2E2", "%e", 1, { tFloat, &fouts[0], { &f200 } } },
  { __LINE__, "2.E2", "%e", 1, { tFloat, &fouts[0], { &f200 } } },
  { __LINE__, ".2E2", "%e", 1, { tFloat, &fouts[0], { &f20 } } },
#if defined(__SMALLER_C__)
  { __LINE__, "1e", "%e", EOF, { tFloat, &fouts[0] } }, // msvcrt,OW,glibc return 1/1.0
  { __LINE__, "1e1", "%2e", 0, { tFloat, &fouts[0] } }, // msvcrt,OW,glibc return 1/1.0
  { __LINE__, "1e\x80\xFF", "%e", 0, { tFloat, &fouts[0] } }, // msvcrt,glibc return 1/1.0
#endif
  { __LINE__, "nan", "%2e", 0 },
  { __LINE__, "inf", "%2e", 0 },
  { __LINE__, "infinity", "%7e", 0 },
  { __LINE__, "0e-999", "%e", 1, { tFloat, &fouts[0], { &f0 } } },
  { __LINE__, "0e999", "%e", 1, { tFloat, &fouts[0], { &f0 } } },
  { __LINE__, "1e-999", "%e", 1, { tFloat, &fouts[0], { &f0 } } },
  { __LINE__, "1e999", "%e", 1, { tFloat, &fouts[0], { &finf } } },
#if !defined(__WATCOMC__)
  { __LINE__, "-0e-999", "%e", 1, { tFloat, &fouts[0], { &f_0 } } }, // OW ignores sign, returns +0.0
  { __LINE__, "-0e999", "%e", 1, { tFloat, &fouts[0], { &f_0 } } }, // OW ignores sign, returns +0.0
  { __LINE__, "-1e-999", "%e", 1, { tFloat, &fouts[0], { &f_0 } } }, // OW ignores sign, returns +0.0
  { __LINE__, "-1e999", "%e", 1, { tFloat, &fouts[0], { &f_inf } } }, // OW ignores sign, returns +inf
#endif
  { __LINE__, " z ", "%c%c%c", 3, { tAscii, &couts[0], { " " }, tAscii, &couts[1], { "z" }, tAscii, &couts[2], { " " } } },
  { __LINE__, " xyz", "%3c", 1, { tAscii, &couts[0], { " xy" } } },
  { __LINE__, "  abc xyz ", "%s%s", 2, { tAsciiZ, &couts[0], { "abc" }, tAsciiZ, &couts[1], { "xyz" } } },
#if !defined(__GNU_LIBRARY__) && !defined(__GLIBC__)
  { __LINE__, "", "%c", EOF }, // glibc returns 0
  { __LINE__, "", "%s", EOF }, // glibc returns 0
  { __LINE__, "", "%[abc]", EOF }, // glibc returns 0
  { __LINE__, "", "%[^abc]", EOF }, // glibc returns 0
#endif
  { __LINE__, " z ", "%[z ]", 1, { tAsciiZ, &couts[0], { " z " } } },
  { __LINE__, "abc123", "%[abc]", 1, { tAsciiZ, &couts[0], { "abc" } } },
  { __LINE__, "abc123", "%[^123]", 1, { tAsciiZ, &couts[0], { "abc" } } },
  { __LINE__, "[abc]123", "%[][abc]", 1, { tAsciiZ, &couts[0], { "[abc]" } } },
  { __LINE__, "abc]123[", "%[^]]", 1, { tAsciiZ, &couts[0], { "abc" } } },
  { __LINE__, "abc123", "%[^abc]", 0 },
  { __LINE__, "a-", "%[-a]", 1, { tAsciiZ, &couts[0], { "a-" } } },
  { __LINE__, "-a", "%[a-]", 1, { tAsciiZ, &couts[0], { "-a" } } },
  { __LINE__, "ba-", "%[^-a]", 1, { tAsciiZ, &couts[0], { "b" } } },
  { __LINE__, "ba-", "%[^a-]", 1, { tAsciiZ, &couts[0], { "b" } } },
  { __LINE__, "a-", "%[^-]", 1, { tAsciiZ, &couts[0], { "a" } } },
  { __LINE__, "-", "%[^-]", 0, },
  { __LINE__, "abc", "%2[abc]", 1, { tAsciiZ, &couts[0], { "ab" } } },
  { __LINE__, "a^b", "%[a^]", 1, { tAsciiZ, &couts[0], { "a^" } } },
  { __LINE__, "ab^", "%[^^]", 1, { tAsciiZ, &couts[0], { "ab" } } },
  { __LINE__, "zabc-1.5e+0 xyz 42%", "%*2c%n%*[abc]%n%*e%n%*s%n%d%%%n", 1, {
               tInt, &iouts[0], { &ints[2] },
               tInt, &iouts[1], { &ints[4] },
               tInt, &iouts[2], { &ints[11] },
               tInt, &iouts[3], { &ints[15] },
               tInt, &iouts[4], { &ints[42] },
               tInt, &iouts[5], { &ints[19] } } },
  { __LINE__, "-1,1", "%hhd,%hhd", 2, { tSChar, &scouts[0], { &sc_1 }, tSChar, &scouts[1], { &schars[1] } } },
  { __LINE__, "-1,1", "%hhu,%hhu", 2, { tUChar, &ucouts[0], { &uchars[255] }, tUChar, &ucouts[1], { &uchars[1] } } },
  { __LINE__, "Ff,1", "%hhX,%hhX", 2, { tUChar, &ucouts[0], { &uchars[255] }, tUChar, &ucouts[1], { &uchars[1] } } },
  { __LINE__, "-1,1", "%hd,%hd", 2, { tShort, &souts[0], { &s_1 }, tShort, &souts[1], { &shorts[1] } } },
  { __LINE__, "-32768,+32767", "%hd,%hd", 2, { tShort, &souts[0], { &s_32768 }, tShort, &souts[1], { &s32767 } } },
  { __LINE__, "-1,-65535", "%hu,%hu", 2, { tUShort, &usouts[0], { &us65535 }, tUShort, &usouts[1], { &ushorts[1] } } },
  { __LINE__, "fFfF,1", "%hx,%hx", 2, { tUShort, &usouts[0], { &us65535 }, tUShort, &usouts[1], { &ushorts[1] } } },
  { __LINE__, "ab", "a%hhnb%hhn", 0, { tSChar, &scouts[0], { &schars[1] }, tSChar, &scouts[1], { &schars[2] } } },
  { __LINE__, "ab", "a%hnb%hn", 0, { tShort, &souts[0], { &shorts[1] }, tShort, &souts[1], { &shorts[2] } } },
  { __LINE__, "some text", "some text%n", 0, { tInt, &iouts[0], { &ints[9] } } },
  { __LINE__, "sometext", "some text%n", 0, { tInt, &iouts[0], { &ints[8] } } },
  { __LINE__, "\x80\xFF", "\x80\xFF%n", 0, { tInt, &iouts[0], { &ints[2] } } },
  { __LINE__, "\x80\xFF""123\x80\xFF", "\x80\xFF%d\x80\xFF%n", 1, { tInt, &iouts[0], { &ints[123] }, tInt, &iouts[1], { &ints[7] } } },
  { __LINE__, "\x80\xFF""1.5\x80\xFF", "\x80\xFF%e\x80\xFF%n", 1, { tFloat, &fouts[0], { &f1_5 }, tInt, &iouts[0], { &ints[7] } } },
  { __LINE__, "\x80\xFF""1.\x80\xFF", "\x80\xFF%e\x80\xFF%n", 1, { tFloat, &fouts[0], { &f1 }, tInt, &iouts[0], { &ints[6] } } },
  { __LINE__, "1\x80\xFF", "%e\x80\xFF%n", 1, { tFloat, &fouts[0], { &f1 }, tInt, &iouts[0], { &ints[3] } } },
  { __LINE__, "1.\x80\xFF", "%e\x80\xFF%n", 1, { tFloat, &fouts[0], { &f1 }, tInt, &iouts[0], { &ints[4] } } },
  { __LINE__, "a", "b%d", 0, },
  { __LINE__, "", "a", EOF, },
  { __LINE__, "-123", "%ld", 1, { tLong, &louts[0], { &l_123 } } },
  { __LINE__, "-123", "%li", 1, { tLong, &louts[0], { &l_123 } } },
  { __LINE__, "-0x7b", "%li", 1, { tLong, &louts[0], { &l_123 } } },
  { __LINE__, "-0173", "%li", 1, { tLong, &louts[0], { &l_123 } } },
  { __LINE__, "65536", "%lu", 1, { tULong, &ulouts[0], { &ul65536 } } },
  { __LINE__, "10000", "%lx", 1, { tULong, &ulouts[0], { &ul65536 } } },
  { __LINE__, "0x10000", "%lX", 1, { tULong, &ulouts[0], { &ul65536 } } },
  { __LINE__, "200000", "%lo", 1, { tULong, &ulouts[0], { &ul65536 } } },
#if !defined(__MSVCRT__) && !defined(__MINGW32__)
  { __LINE__, "65535", "%zu", 1, { tSizeT, &szouts[0], { &sz65535 } } }, // %zu not recognized by msvcrt
  { __LINE__, "FfFf", "%zx", 1, { tSizeT, &szouts[0], { &sz65535 } } }, // %zx not recognized by msvcrt
  { __LINE__, "0xFfFf", "%zx", 1, { tSizeT, &szouts[0], { &sz65535 } } }, // %zx not recognized by msvcrt
  { __LINE__, "177777", "%zo", 1, { tSizeT, &szouts[0], { &sz65535 } } }, // %zo not recognized by msvcrt
#endif
  { __LINE__, "-0.16777215e8", "%lf", 1, { tDouble, &douts[0], { &d_16777215 } } },
  { __LINE__, "0.001953125", "%lf", 1, { tDouble, &douts[0], { &d0_001953125 } } },
  { __LINE__, "1e-30", "%lf", 1, { tDouble, &douts[0], { &d0_99999e_30, &d1_00001e_30 } } },
};

int CasePtr(void)
{
  char c, buf[128];
  void* p;
  int res;
  sprintf(buf, "%p", (void*)&c);
  p = (void*)-1;
  res = sscanf(buf, "%p", &p);
  if (res != 1)
  {
    printf("FAILURE: line %d: sscanf(buf, \"%%p\", &p) != 1\n", __LINE__);
    return 1;
  }
  if (p != &c)
  {
    printf("FAILURE: line %d: p != &c\n", __LINE__);
    return 1;
  }
  return 0;
}

int CaseNullPtr(void)
{
  char buf[128];
  void* p;
  int res;
  sprintf(buf, "%p", (void*)NULL);
  p = (void*)-1;
  res = sscanf(buf, "%p", &p);
  if (res != 1)
  {
    printf("FAILURE: line %d: sscanf(buf, \"%%p\", &p) != 1\n", __LINE__);
    return 1;
  }
  if (p != NULL)
  {
    printf("FAILURE: line %d: p != NULL\n", __LINE__);
    return 1;
  }
  return 0;
}

int main(void)
{
  unsigned cnt = sizeof cases / sizeof cases[0];
  unsigned err = 0;
  unsigned i;
  Init();
  for (i = 0; i < cnt; i++)
    err += RunCase(&cases[i]);
  err += CasePtr(); cnt++;
  err += CaseNullPtr(); cnt++;
  printf("%u of %u tests passed!\n", cnt - err, cnt);
  return err ? EXIT_FAILURE : 0;
}
