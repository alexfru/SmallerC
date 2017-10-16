/*
  Simple test for structure passing and returning.

  How to compile for DOS (all mode(l)s: tiny/.COM, small/.EXE, huge/.EXE, unreal/.EXE, 32-bit DPMI/.EXE):
    smlrcc -dost prstr.c -o prstrdt.com
    smlrcc -doss prstr.c -o prstrds.exe
    smlrcc -dosh prstr.c -o prstrdh.exe
    smlrcc -dosu prstr.c -o prstrdu.exe
    smlrcc -dosp prstr.c -o prstrdp.exe

  How to compile for Windows:
    smlrcc -win prstr.c -o prstrw.exe

  How to compile for Linux:
    smlrcc -linux prstr.c -o prstrl

  How to compile for MacOS:
    smlrcc -macos prstr.c -o prstrm
*/

#include <stdio.h>
#include <string.h>
#include <assert.h>

#ifdef __SMALLER_C_32__
#define PAD_VAL1 0xDEADBEEF
#define PAD_VAL2 0xBADC0FFE
#endif
#ifdef __SMALLER_C_16__
#define PAD_VAL1 0xDEAD
#define PAD_VAL2 0xBEEF
#endif

void ScrubStack(void)
{
  unsigned char arr[1024];
  memset(arr, 0, sizeof arr);
}

#define DECL(N) \
typedef struct { unsigned char data[N]; } t##N; \
void Init##N(t##N* p) \
{ int i; \
  for (i = 0; i < N; i++) \
    p->data[i] = i ^ N; } \
void ValidatePtr##N(const t##N* p) \
{ int i; \
  for (i = 0; i < N; i++) \
    assert(p->data[i] == (unsigned char)(i ^ N)); } \
void ValidateStr##N(unsigned pad1, t##N s, unsigned pad2) \
{ int i; \
  assert(pad1 == PAD_VAL1); \
  for (i = 0; i < N; i++) \
    assert(s.data[i] == (unsigned char)(i ^ N)); \
  assert(pad2 == PAD_VAL2); } \
t##N ProduceStr##N(void) \
{ t##N s; Init##N(&s); return s; }

#define TEST(N) \
{ \
  static t##N s1##N, s2##N; \
  t##N s3##N; \
  Init##N(&s1##N); \
  ScrubStack(); \
  ValidateStr##N(PAD_VAL1, s1##N, PAD_VAL2); \
  ScrubStack(); \
  ValidateStr##N(PAD_VAL1, ProduceStr##N(), PAD_VAL2); \
  ScrubStack(); \
  s2##N = ProduceStr##N(); \
  ScrubStack(); \
  ValidatePtr##N(&s2##N); \
  ScrubStack(); \
  s3##N = ProduceStr##N(); \
  ScrubStack(); \
  ValidatePtr##N(&s3##N); \
}

         DECL( 1) DECL( 2) DECL( 3) DECL( 4) DECL( 5) DECL( 6) DECL( 7) DECL( 8) DECL( 9)
DECL(10) DECL(11) DECL(12) DECL(13) DECL(14) DECL(15) DECL(16) DECL(17) DECL(18) DECL(19)
DECL(20) DECL(21) DECL(22) DECL(23) DECL(24) DECL(25) DECL(26) DECL(27) DECL(28) DECL(29)
DECL(30) DECL(31) DECL(32) DECL(33) DECL(34) DECL(35) DECL(36) DECL(37) DECL(38) DECL(39)

int main(void)
{
           TEST( 1) TEST( 2) TEST( 3) TEST( 4) TEST( 5) TEST( 6) TEST( 7) TEST( 8) TEST( 9)
  TEST(10) TEST(11) TEST(12) TEST(13) TEST(14) TEST(15) TEST(16) TEST(17) TEST(18) TEST(19)
  TEST(20) TEST(21) TEST(22) TEST(23) TEST(24) TEST(25) TEST(26) TEST(27) TEST(28) TEST(29)
  TEST(30) TEST(31) TEST(32) TEST(33) TEST(34) TEST(35) TEST(36) TEST(37) TEST(38) TEST(39)
  puts("Test passed!");
  return 0;
}
