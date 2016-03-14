/*
  Copyright (c) 2016, Alexey Frunze
  2-clause BSD license.
*/

#ifdef __SMALLER_C_32__

#include <string.h>
#include <math.h>

static void rev(char* buf, unsigned size)
{
  char *p1 = buf, *p2 = buf + size;
  while (p1 < p2)
  {
    char t = *p1;
    *p1++ = *--p2;
    *p2 = t;
  }
}

// Converts the integral part of "x" into decimal string representation,
// e.g. 123456.75f -> "123456".
//
// "x" must be finite and non-negative, IOW, it can't be a NaN, an infinity
// or less than zero.
//
// Produces at most "size" digit chars in "buf[]", does not NUL-terminate
// them (uses all "size" chars of the buffer space in the process).
// "size" must be 1 or greater.
//
// Note, there can be up to 39 integral digits in 32-bit single precision
// values as the maximum is ~3.4e38.
//
// Returns the number of digits in the integral part of "x", which can be
// greater than "size". If greater, the difference is how many zero digits
// can be appended for correct result (or you could append "e+NN" instead).
//
// Request (with larger "size") an extra digit so you can round the result
// based on the value of this last digit and then throw this digit away.
//
// If "rem" isn't NULL, returns *rem == 0 if there are no further non-
// zero digits (useful for rounding half-way cases (integers ending in 5))
// or *rem != 0 otherwise.
//
// With this you should be able to implement "%f" and "%e" in printf().
int __cvtdif(float x, char* buf, int size, int* rem)
{
  unsigned short a[8] = { 0 }; // 16-bit chunks of integral part of x
  unsigned long ul;
  int e, i;
  int cnt = 0;
  char* p = buf + size;

  if (rem)
  {
    float t;
    modff(x, &t);
    // check fractional part for zero
    // *rem = x != t; // needs f-p compare
    *rem = memcmp(&x, &t, sizeof t); // doesn't need f-p compare
    if (*rem)
      rem = NULL;
  }

  // get number of bits in integral part of mantissa
  frexpf(x, &e);

  if (e <= 32)
  {
    // simple case: fits into 32-bit unsigned integer
    ul = x;
    a[0] = ul;
    a[1] = ul >> 16;
    // if x < 1, make sure there will be exactly one digit (0)
    if (e <= 0)
      e = 1;
  }
  else
  {
    int e2 = (e + 31) / 32 * 32; // round e up to: 64, 96, 128
    int j = e2 / 16 - 1; // starting chunk: 3, 5, 7
    float t;

    // get 32 bits containing most significant bits of mantissa
    x = ldexpf(x, 32 - e2);
    ul = x;
    a[j--] = ul >> 16;
    a[j--] = ul;

    // get 32 bits containing least significant bits of mantissa
    // x = ldexpf(x - ul, 32); // needs f-p subtraction
    x = ldexpf(modff(x, &t), 32); // doesn't need f-p subtraction
    ul = x;
    a[j--] = ul >> 16;
    a[j] = ul;
  }

  // convert number of bits into starting chunk number
  e = (e - 1) / 16;

  // repeatedly divide the integral part by 10, collecting remainders
  // (decimal digits)
  do
  {
    unsigned long r = 0;
    i = e;
    do
    {
      r = (r << 16) + a[i];
      a[i] = r / 10;
      r %= 10;
    } while (--i >= 0);
    // fill the output buffer circularly from back to front
    *--p = r + '0';
    if (p == buf)
      p += size;
    if (++cnt > size && rem)
      *rem |= r;
    // if the starting 16-bit chunk is 0 after dividing it by 10,
    // don't use it anymore, and if chunk 0 is 0, we're done
    if (a[e] == 0)
      e--;
  } while (e >= 0);

  if (cnt < size)
  {
    // gap: move digits to front
    int t = cnt;
    while (t--)
      *buf++ = *p++;
  }
  else if (cnt > size && p != buf + size)
  {
    // need to rotate digits
    rev(buf, p - buf);
    rev(p, buf + size - p);
    rev(buf, size);
  }

  return cnt;
}

// Converts the fractional part of "x" into decimal string representation,
// e.g. 123456.75f -> "75".
//
// "x" must be finite and non-negative, IOW, it can't be a NaN, an infinity
// or less than zero.
//
// Produces "size" digit chars in "buf[]", does not NUL-terminate.
// If you request more digits than there are, you get extra zeroes, e.g.
// requesting 4 digits for 123456.75f yields "7500".
// "size" can be zero.
//
// Note that although getting the exact full fractional part is rarely needed
// (the useful precision of floats is 7 decimal digits) there can be up to 149
// fractional digits in 32-bit single precision values as the minimum positive
// denormal value is 2**-149 (~1.4e-45).
//
// Request (with larger "size") an extra digit so you can round the result
// based on the value of this last digit and then throw this digit away.
//
// Returns 0 if there are no further non-zero digits (useful for rounding
// half-way cases (fractions ending in 5)) or non-zero otherwise.
//
// If "zeroes" isn't NULL, does not generate leading zeroes (in e.g. ".0625"),
// instead stores the number of the leading zeroes in "*zeroes" (useful
// for "i.fffe-NN" format). If the fractional part is 0, "*zeroes" becomes
// 0 and "size" zero digits are generated.
//
// With this you should be able to implement "%f" and "%e" in printf().
int __cvtdff(float x, char* buf, int size, int* zeroes)
{
  unsigned short a[12] = { 0 }; // 16-bit chunks of fractional part of x
  unsigned long ul;
  int e, i;
  float t;

  // get number of bits in integral part of mantissa
  x = modff(x, &t);
  frexpf(x, &e);
  e = -e;
  if (e <= 32 - 24)
  {
    // simple case: fits into 32 bits
    x = ldexpf(x, 32);
    ul = x;
    a[0] = ul >> 16;
    a[1] = ul;
    e = 1;
  }
  else
  {
    int e2 = e / 32 * 32; // round e down to: 0, 32, 64, 96, 128
    int j = e2 / 16; // starting chunk: 0, 2, 4, 6, 8

    // get 32 bits containing most significant bits of mantissa
    x = ldexpf(x, 32 + e2);
    ul = x;
    a[j++] = ul >> 16;
    a[j++] = ul;

    // get 32 bits containing least significant bits of mantissa
    // x = ldexpf(x - ul, 32); // needs f-p subtraction
    x = ldexpf(modff(x, &t), 32); // doesn't need f-p subtraction
    ul = x;
    a[j++] = ul >> 16;
    a[j] = ul;

    e = j;
  }

  if (zeroes)
    *zeroes = 0;

  while (e >= 0 && a[e] == 0)
    e--;

  if (e < 0) while (size--)
  {
    // fractional part is zero
    *buf++ = '0';
  }
  else while (size--)
  {
    unsigned long r = 0;
    i = e;
    while (i >= 0)
    {
      r += a[i] * 10ul;
      a[i--] = r;
      r >>= 16;
    }
    if (zeroes && r == 0)
      ++*zeroes, size++;
    else
      *buf++ = r + '0', zeroes = NULL;
    while (e >= 0 && a[e] == 0)
      e--;
  }

  // e == -1 if all further digits are 0,
  // this may be used for proper rounding to even if desired
  return e >= 0;
}

#endif
