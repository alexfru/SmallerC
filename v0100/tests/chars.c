/*
  How to compile for DOS (all mode(l)s: tiny/.COM, small/.EXE, huge/.EXE, unreal/.EXE, 32-bit DPMI/.EXE):
    smlrcc -dost chars.c -o charsdt.com
    smlrcc -doss chars.c -o charsds.exe
    smlrcc -dosh chars.c -o charsdh.exe
    smlrcc -dosu chars.c -o charsdu.exe
    smlrcc -dosp chars.c -o charsdp.exe

  How to compile for Windows:
    smlrcc -win chars.c -o charsw.exe

  How to compile for Linux:
    smlrcc -linux chars.c -o charsl

  How to compile for MacOS:
    smlrcc -macos chars.c -o charsm
*/

#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_WIDE

extern char StAtIcAsSeRt[CHAR_BIT == 8];

enum { WSZ = sizeof(wchar_t) };

int errors;

void test_char(void)
{
  static int a[][2] =
  {
    sizeof 'A', sizeof(int),
    sizeof 'AB', sizeof(int),
    'A', 65,
    '"', 34,
    '?', 63,
    '\"', 34,
    '\?', 63,
    '\\', 92,
    '\'', 39,
    '\a', 7,
    '\b', 8,
    '\f', 12,
    '\n', 10,
    '\r', 13,
    '\t', 9,
    '\v', 11,
    '\x0', 0,
    '\x0000000000000000', 0,
    '\x10', 16,
    '\x00000000000000007F', 127,
    '\x00000000000000007f', 127,
    (unsigned char)'\xFf', 255,
    '\0', 0,
    '\10', 8,
    '\101', 65,
    '\177', 127,
    (unsigned char)'\377', 255,
    'AB', 0x4142,
    '\x41\x42', 0x4142
#ifdef __SMALLER_C_16__
,   '\xFF\xff', -1
#endif
#ifdef __SMALLER_C_32__
,   'ABCD', 0x41424344
,   '\x41\x42\x43\x44', 0x41424344
,   '\xFf\xfF\xFF\xff', -1
#endif
  };

  int i;
  puts("test_char()");
  for (i = 0; i < sizeof a / sizeof a[0]; i++)
    if (a[i][0] != a[i][1])
      printf("a[%d][0]=%d != a[%d][1]=%d\n", i, a[i][0], i, a[i][1]), ++errors;

#ifdef __SMALLER_C_SCHAR__
  if ('\xFF' != -1)
    printf("'\\xFF' != -1\n"), ++errors;
  if ('\377' != -1)
    printf("'\\377' != -1\n"), ++errors;
#endif

#ifdef __SMALLER_C_UCHAR__
  if ('\xFF' != 255)
    printf("'\\xFF' != 255\n"), ++errors;
  if ('\377' != 255)
    printf("'\\377' != 255\n"), ++errors;
#endif

#ifdef __SMALLER_C_16__
  if ('\xFF\xff' >= 0)
    printf("'\\xFF\\xff' >= 0\n"), ++errors;
#endif

#ifdef __SMALLER_C_32__
  if ('\xFf\xfF\xFF\xff' >= 0)
    printf("'\\xFf\\xfF\\xFF\\xff' >= 0\n"), ++errors;
#endif
}

#ifdef TEST_WIDE
void test_wchar(void)
{
  static wchar_t a[][2] =
  {
    sizeof L'A', sizeof(wchar_t),
    L'A', 65,
    L'"', 34,
    L'?', 63,
    L'\"', 34,
    L'\?', 63,
    L'\\', 92,
    L'\'', 39,
    L'\a', 7,
    L'\b', 8,
    L'\f', 12,
    L'\n', 10,
    L'\r', 13,
    L'\t', 9,
    L'\v', 11,
    L'\x0', 0,
    L'\x0000000000000000', 0,
    L'\x10', 16,
    L'\x00000000000000007F', 127,
    L'\x00000000000000007f', 127,
    L'\xFf', 255,
    L'\xfFfF', 0xFFFF,
    L'\0', 0,
    L'\10', 8,
    L'\101', 65,
    L'\177', 127,
    L'\377', 255
#ifdef __SMALLER_C_WCHAR16__
,   L'\xFFff', 0xFFFF
#endif
#ifdef __SMALLER_C_WCHAR32__
,   L'\x12345678', 0x12345678
,   L'\xFFFFffff', 0xFFFFFFFF
#endif
  };

  int i;
  puts("test_wchar()");
  for (i = 0; i < sizeof a / sizeof a[0]; i++)
    if (a[i][0] != a[i][1])
      printf("a[%d][0]=%d != a[%d][1]=%d\n", i, a[i][0], i, a[i][1]), ++errors;

#ifdef __SMALLER_C_WCHAR16__
#ifdef __SMALLER_C_SWCHAR__
  if (L'\xFFff' >= 0)
    printf("L'\\xFFff' >= 0\n"), ++errors;
#endif // __SMALLER_C_SWCHAR__
#ifdef __SMALLER_C_UWCHAR__
  if (L'\xFFff' < 0)
    printf("L'\\xFFff' < 0\n"), ++errors;
#endif // __SMALLER_C_UWCHAR__
#endif // __SMALLER_C_WCHAR16__

#ifdef __SMALLER_C_WCHAR32__
#ifdef __SMALLER_C_SWCHAR__
  if (L'\xFffFFFff' >= 0)
    printf("L'\\xFffFFFff' >= 0\n"), ++errors;
#endif // __SMALLER_C_SWCHAR__
#ifdef __SMALLER_C_UWCHAR__
  if (L'\xFffFFFff' < 0)
    printf("L'\\xFffFFFff' < 0\n"), ++errors;
#endif // __SMALLER_C_UWCHAR__
#endif // __SMALLER_C_WCHAR32__
}
#endif

void test_literal_concat(void)
{
  static char a0[] = "a""b";
  static char a1[] = { "A" "B" };
  static char a2[2] = "a" "b";
  static char a3[2] = { "A""B" };
  char* p0 = "a""b";
  char* p1 = { "A" "B" };
  puts("test_literal_concat()");

  if (sizeof a0 != 3)
    printf("sizeof a0 = %d != 3\n", (int)sizeof a0), ++errors;
  if (sizeof a1 != 3)
    printf("sizeof a1 = %d != 3\n", (int)sizeof a1), ++errors;
  if (sizeof a2 != 2)
    printf("sizeof a2 = %d != 2\n", (int)sizeof a2), ++errors;
  if (sizeof a3 != 2)
    printf("sizeof a3 = %d != 2\n", (int)sizeof a3), ++errors;

  if (sizeof "a" "b" != 3)
    printf("sizeof \"a\" \"b\" = %d != 3\n", (int)sizeof "a" "b"), ++errors;

  if (strcmp(a0, "ab"))
    printf("a0 = \"%.2s\" != \"ab\"\n", a0), ++errors;
  if (strcmp(a1, "AB"))
    printf("a1 = \"%.2s\" != \"AB\"\n", a1), ++errors;
  if (strcmp(p0, "ab"))
    printf("p0 = \"%.2s\" != \"ab\"\n", p0), ++errors;
  if (strcmp(p1, "AB"))
    printf("p1 = \"%.2s\" != \"AB\"\n", p1), ++errors;

  if (strncmp(a2, "ab", 2))
    printf("a2 = \"%.2s\" != \"ab\"\n", a2), ++errors;
  if (strncmp(a3, "AB", 2))
    printf("a3 = \"%.2s\" != \"AB\"\n", a3), ++errors;
}

#ifdef TEST_WIDE
void test_wide_literal_concat(void)
{
  static wchar_t a0[] = L"a" L"b";
  static wchar_t a1[] = { L"A"L"B" };
  static wchar_t a2[2] = L"a"L"b";
  static wchar_t a3[2] = { L"A" L"B" };
  wchar_t* p0 = L"a" L"b";
  wchar_t* p1 = { L"A"L"B" };
  puts("test_wide_literal_concat()");

  if (sizeof a0 != 3 * WSZ)
    printf("sizeof a0 = %d != %d\n", (int)sizeof a0, 3 * WSZ), ++errors;
  if (sizeof a1 != 3 * WSZ)
    printf("sizeof a1 = %d != %d\n", (int)sizeof a1, 3 * WSZ), ++errors;
  if (sizeof a2 != 2 * WSZ)
    printf("sizeof a2 = %d != %d\n", (int)sizeof a2, 2 * WSZ), ++errors;
  if (sizeof a3 != 2 * WSZ)
    printf("sizeof a3 = %d != %d\n", (int)sizeof a3, 2 * WSZ), ++errors;

  if (sizeof L"a" L"b" != 3 * WSZ)
    printf("sizeof L\"a\" L\"b\" = %d != %d\n", (int)sizeof L"a" L"b", 3 * WSZ), ++errors;

  if (memcmp(a0, L"ab", 3 * WSZ))
    printf("a0 != L\"ab\"\n"), ++errors;
  if (memcmp(a1, L"AB", 3 * WSZ))
    printf("a1 != L\"AB\"\n"), ++errors;
  if (memcmp(p0, L"ab", 3 * WSZ))
    printf("p0 != L\"ab\"\n"), ++errors;
  if (memcmp(p1, L"AB", 3 * WSZ))
    printf("p1 != L\"AB\"\n"), ++errors;

  if (memcmp(a2, L"ab", 2 * WSZ))
    printf("a2 != L\"ab\"\n"), ++errors;
  if (memcmp(a3, L"AB", 2 * WSZ))
    printf("a3 != L\"AB\"\n"), ++errors;
}
#endif

void test_literal(void)
{
  static char ac[] =
  {
    "A" "'" "?" "\'" "\?" "\"" "\\" "\n" "\7" "\x0" "\x8" "\x00"
    "\78" "\7A"  "\xfg" "\xFG"    "\101101" "\x00000000000000007f"
  };
  static int ai[] =
  {
    65, 39, 63,  39,  63,  34,  92,  10,   7,    0,    8,     0,
    7,56, 7,65, 15,103, 15,71, 65,49,48,49,                   127,
    0
  };
  extern char StAtIcAsSeRt[sizeof ac / sizeof ac[0] == sizeof ai / sizeof ai[0]];
  int i;
  puts("test_literal()");
  for (i = 0; i < sizeof ac / sizeof ac[0]; i++)
    if (ac[i] != ai[i])
      printf("ac[%d]=%d != ai[%d]=%d\n", i, ac[i], i, ai[i]), ++errors;
}

#ifdef TEST_WIDE
void test_wide_literal(void)
{
  static wchar_t ac[] =
  {
    L"A" L"'" L"?" L"\'" L"\?" L"\"" L"\\" L"\n" L"\7" L"\x0" L"\x8" L"\x00"
    L"\78" L"\7A"  L"\xfg" L"\xFG"    L"\101101" L"\x00000000000000007f"
  };
  static wchar_t ai[] =
  {
     65,  39,  63,   39,   63,   34,   92,   10,    7,     0,     8,      0,
     7,56,  7,65,  15,103,  15,71,  65,49,48,49,                    127,
    0
  };
  extern char StAtIcAsSeRt[sizeof ac / sizeof ac[0] == sizeof ai / sizeof ai[0]];
  int i;
  puts("test_wide_literal()");
  for (i = 0; i < sizeof ac / sizeof ac[0]; i++)
    if (ac[i] != ai[i])
      printf("ac[%d]=%d != ai[%d]=%d\n", i, ac[i], i, ai[i]), ++errors;
}
#endif

int main(void)
{
  test_char();
#ifdef TEST_WIDE
  test_wchar();
#endif
  test_literal_concat();
#ifdef TEST_WIDE
  test_wide_literal_concat();
#endif
  test_literal();
#ifdef TEST_WIDE
  test_wide_literal();
#endif
  printf("%d errors\n\n", errors);
  return errors ? EXIT_FAILURE : 0;
}
