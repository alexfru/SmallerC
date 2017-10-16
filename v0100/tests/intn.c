/*
  Small test for <stdint.h> and <inttypes.h>.

  How to compile for DOS (all mode(l)s: tiny/.COM, small/.EXE, huge/.EXE, unreal/.EXE, 32-bit DPMI/.EXE):
    smlrcc -dost intn.c -o intndt.com
    smlrcc -doss intn.c -o intnds.exe
    smlrcc -dosh intn.c -o intndh.exe
    smlrcc -dosu intn.c -o intndu.exe
    smlrcc -dosp intn.c -o intndp.exe

  How to compile for Windows:
    smlrcc -win intn.c -o intnw.exe

  How to compile for Linux:
    smlrcc -linux intn.c -o intnl

  How to compile for MacOS:
    smlrcc -macos intn.c -o intnm
*/

#include <inttypes.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#define TEST_PRINT(out, sfx, val, expected) \
  assert((memset(out,0,sizeof out), sprintf(out, "%" sfx, val), !strcmp(out, expected)))

#define TEST_SCAN(in, sfx, var, expected) \
  assert((var = 0, sscanf(in, "%" sfx, &var) == 1 && var == expected))

int main(void)
{
  char buf[64];
  int8_t i8;
  uint8_t u8;
  int16_t i16;
  uint16_t u16;
#if defined(__SMALLER_C_32__) || !defined(__SMALLER_C__)
  int32_t i32;
  uint32_t u32;
#endif
  intmax_t imax;
  uintmax_t umax;
  TEST_PRINT(buf, PRId8, INT8_C(-128), "-128");
  TEST_PRINT(buf, PRIi8, INT8_C(-128), "-128");
  TEST_PRINT(buf, PRIo8, UINT8_C(255), "377");
  TEST_PRINT(buf, PRIu8, UINT8_C(255), "255");
  TEST_PRINT(buf, PRIx8, UINT8_C(255), "ff");
  TEST_PRINT(buf, PRIX8, UINT8_C(255), "FF");
  TEST_PRINT(buf, PRId16, INT16_C(-32767), "-32767");
  TEST_PRINT(buf, PRIi16, INT16_C(-32767), "-32767");
  TEST_PRINT(buf, PRIo16, UINT16_C(65535), "177777");
  TEST_PRINT(buf, PRIu16, UINT16_C(65535), "65535");
  TEST_PRINT(buf, PRIx16, UINT16_C(65535), "ffff");
  TEST_PRINT(buf, PRIX16, UINT16_C(65535), "FFFF");
  TEST_PRINT(buf, PRIdMAX, INTMAX_C(-32767), "-32767");
  TEST_PRINT(buf, PRIuMAX, UINTMAX_C(65535), "65535");
#if defined(__SMALLER_C_32__) || !defined(__SMALLER_C__)
  TEST_PRINT(buf, PRId32, INT32_C(-2147483647), "-2147483647");
  TEST_PRINT(buf, PRIi32, INT32_C(-2147483647), "-2147483647");
  TEST_PRINT(buf, PRIo32, UINT32_C(4294967295), "37777777777");
  TEST_PRINT(buf, PRIu32, UINT32_C(4294967295), "4294967295");
  TEST_PRINT(buf, PRIx32, UINT32_C(4294967295), "ffffffff");
  TEST_PRINT(buf, PRIX32, UINT32_C(4294967295), "FFFFFFFF");
  TEST_PRINT(buf, PRIdMAX, INTMAX_C(-2147483647), "-2147483647");
  TEST_PRINT(buf, PRIuMAX, UINTMAX_C(4294967295), "4294967295");
#endif
  TEST_SCAN("-128", SCNd8, i8, INT8_C(-128));
  TEST_SCAN("-128", SCNi8, i8, INT8_C(-128));
  TEST_SCAN("377", SCNo8, u8, UINT8_C(255));
  TEST_SCAN("255", SCNu8, u8, UINT8_C(255));
  TEST_SCAN("Ff", SCNx8, u8, UINT8_C(255));
  TEST_SCAN("-32767", SCNd16, i16, INT16_C(-32767));
  TEST_SCAN("-32767", SCNi16, i16, INT16_C(-32767));
  TEST_SCAN("177777", SCNo16, u16, UINT16_C(65535));
  TEST_SCAN("65535", SCNu16, u16, UINT16_C(65535));
  TEST_SCAN("FffF", SCNx16, u16, UINT16_C(65535));
  TEST_SCAN("-32767", SCNdMAX, imax, INTMAX_C(-32767));
  TEST_SCAN("65535", SCNuMAX, umax, UINTMAX_C(65535));
#if defined(__SMALLER_C_32__) || !defined(__SMALLER_C__)
  TEST_SCAN("-2147483647", SCNd32, i32, INT32_C(-2147483647));
  TEST_SCAN("-2147483647", SCNi32, i32, INT32_C(-2147483647));
  TEST_SCAN("37777777777", SCNo32, u32, UINT32_C(4294967295));
  TEST_SCAN("4294967295", SCNu32, u32, UINT32_C(4294967295));
  TEST_SCAN("ffFFffFF", SCNx32, u32, UINT32_C(4294967295));
  TEST_SCAN("-2147483647", SCNdMAX, imax, INTMAX_C(-2147483647));
  TEST_SCAN("4294967295", SCNuMAX, umax, UINTMAX_C(4294967295));
#endif
  return 0;
}
