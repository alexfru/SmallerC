/*
  Copyright (c) 2016, Alexey Frunze
  2-clause BSD license.
*/

// This file implements the basic arithmetic functions on floats and
// expects that the host representation of floats coinsides with the
// target representation of floats and is IEEE 754 single precision.
// It is also expected that the host implementation does not raise
// any signals nor results in undefined behavior when handling
// special cases involving infinities, NaNs and denormal numbers.

// Make sure float and int are the same size, so they can be
// copied one into another byte by byte with memcpy().
extern char StAtIcAsSeRt[(sizeof(float) == sizeof(unsigned)) ? 1 : -1];

// There can be up to 112 significant digits in a 32-bit single precision
// floating point number (in the maximum positive denormal number).
// We'll ignore any following digits, but convert these 112 with proper
// rounding to even, which is enough for all floats representable exactly,
// which should be enough for most practical purposes.
#define MAX_CONST_DIGITS 112 // must be big enough for decimal/octal ints as well
unsigned char ConstDigits[MAX_CONST_DIGITS];
#define FP_MANT_BITS  23    // bits in mantissa, excluding the implicit 1
#define FP_EXP_BITS   8     // bits in exponent
#define FP_MIN_EXP    (-46) // from min denormal, ~1.40e-45
                            // (-46 is chosen because we need to handle numbers
                            // like 9e-46 which round up to a non-zero denormal
                            // number ~1.40e-45)
#define FP_MAX_EXP    38    // from max normal, ~3.40e+38
#define FP_BUF_SIZE   (((((MAX_CONST_DIGITS-FP_MIN_EXP)*10+2)/3+FP_MANT_BITS+2)+7)/8)
unsigned char ConstBinDigits[FP_BUF_SIZE];

STATIC
unsigned f2u(unsigned f)
{
  float ff;
  memcpy(&ff, &f, sizeof ff);
  if (ff != ff || ff <= -1.0f || ff >= (float)0x10000*0x10000/* 2**32 */)
  {
    warnFloat2Int();
    ff = 0;
  }
  return ff;
}

STATIC
unsigned f2i(unsigned f, int opsz)
{
  float ff;
  int ovf = 0;
  memcpy(&ff, &f, sizeof ff);
  if (ff != ff)
  {
    ovf = 1;
  }
  else
  {
    switch (opsz)
    {
    case 1: // unsigned char
      ovf = ff <= -1.0f || ff >= 256.0f;
      break;
    case 2: // unsigned short
      ovf = ff <= -1.0f || ff >= 65536.0f;
      break;
    case -1: // signed char
      ovf = ff <= -129.0f || ff >= 128.0f;
      break;
    case -2: // signed short
      ovf = ff <= -32769.0f || ff >= 32768.0f;
      break;
    default: // signed int
      ovf = ff < -(float)0x8000*0x10000/* -2**31 */ || ff >= (float)0x8000*0x10000/* 2**31 */;
      break;
    }
  }
  if (ovf)
  {
    warnFloat2Int();
    ff = 0;
  }
  return (int)ff;
}

STATIC
unsigned u2f(unsigned i)
{
  float f = i;
  memcpy(&i, &f, sizeof i);
  return i;
}

STATIC
unsigned i2f(unsigned i)
{
  float f = (int)i;
  memcpy(&i, &f, sizeof i);
  return i;
}

STATIC
unsigned fneg(unsigned f)
{
  float ff;
  memcpy(&ff, &f, sizeof ff);
  ff = -ff;
  memcpy(&f, &ff, sizeof f);
  return f;
}

STATIC
unsigned fadd(unsigned fa, unsigned fb)
{
  float ffa, ffb;
  memcpy(&ffa, &fa, sizeof ffa);
  memcpy(&ffb, &fb, sizeof ffb);
  ffa = ffa + ffb;
  memcpy(&fa, &ffa, sizeof fa);
  return fa;
}

STATIC
unsigned fsub(unsigned fa, unsigned fb)
{
  return fadd(fa, fneg(fb));
}

STATIC
unsigned fmul(unsigned fa, unsigned fb)
{
  float ffa, ffb;
  memcpy(&ffa, &fa, sizeof ffa);
  memcpy(&ffb, &fb, sizeof ffb);
  ffa = ffa * ffb;
  memcpy(&fa, &ffa, sizeof fa);
  return fa;
}

STATIC
unsigned fdiv(unsigned fa, unsigned fb)
{
  float ffa, ffb;
  memcpy(&ffa, &fa, sizeof ffa);
  memcpy(&ffb, &fb, sizeof ffb);
  ffa = ffa / ffb;
  memcpy(&fa, &ffa, sizeof fa);
  return fa;
}

STATIC
int fcmp(unsigned fa, unsigned fb, int nanRes)
{
  float ffa, ffb;
  memcpy(&ffa, &fa, sizeof ffa);
  memcpy(&ffb, &fb, sizeof ffb);
  if (ffa != ffa || ffb != ffb)
    return nanRes;
  if (ffa < ffb)
    return -1;
  if (ffa > ffb)
    return +1;
  return 0;
}

STATIC
void ChainMultiplyAdd(unsigned char* pChain,
                      unsigned       ChainLen,
                      unsigned char  Multiplier,
                      unsigned char  Addend)
{
  unsigned carry = Addend;

  while (ChainLen--)
  {
    carry += *pChain * Multiplier;
    *pChain++ = carry & 0xFFu;
    carry >>= 8;
  }
}

STATIC
void ChainDivide(unsigned char* pChain,
                 unsigned       ChainLen,
                 unsigned char  Divisor,
                 unsigned char* pRemainder)
{
  unsigned remainder = 0;

  while (ChainLen)
  {
    remainder += pChain[ChainLen - 1];
    pChain[ChainLen - 1] = remainder / Divisor;
    remainder = (remainder % Divisor) << 8;
    ChainLen--;
  }

  if (pRemainder != NULL)
    *pRemainder = remainder >> 8;
}

// Multiplies an integer (cnt decimal digits (0 to 9) from digits[]) by
// 10**eexp, converts the product to a float and returns it as unsigned int.
// This is an inefficient but straightforward algorithm with proper rounding.
STATIC
unsigned d2f(unsigned char* digits, int cnt, int eexp)
{
  unsigned numDecDigits;
  unsigned denDecDigits;
  unsigned numBinDigits;
  unsigned numBytes;
  int tmp;
  unsigned char remainder;
  int binExp = 0;
  int inexact = 0;
  int lastInexact = 0;
  unsigned res;
  
  // 0?
  if (cnt == 1 && *digits == 0)
    return 0;
  // less than the denormalized minimum?
  if (eexp < FP_MIN_EXP - (cnt - 1))
    return 0;

  // greater than the normalized maximum?
  if (eexp > FP_MAX_EXP - (cnt - 1))
    return 0x7F800000; // +INF

  numDecDigits = cnt + ((eexp >= 0) ? eexp : 0);
  denDecDigits = 1 + ((eexp < 0) ? -eexp : 0);

  // 10/3=3.3(3) > log2(10)~=3.32
  if (eexp >= 0)
  {
    unsigned t1 = (numDecDigits * 10 + 2) / 3;
    unsigned t2 = FP_MANT_BITS + 1;
    numBinDigits = (t1 >= t2) ? t1 : t2;
  }
  else
  {
    unsigned t1 = (numDecDigits * 10 + 2) / 3;
    unsigned t2 = (denDecDigits * 10 + 2) / 3 + FP_MANT_BITS + 1 + 1;
    numBinDigits = (t1 >= t2) ? t1 : t2;
  }

  numBytes = (numBinDigits + 7) / 8;
  if (numBytes > (unsigned)FP_BUF_SIZE)
    errorInternal(200);
  memset(ConstBinDigits, 0, numBytes);

  // Convert the numerator to binary
  for (tmp = 0; tmp < cnt; tmp++)
    ChainMultiplyAdd(ConstBinDigits, numBytes, 10, digits[tmp]);
  for (tmp = eexp; tmp > 0; tmp--)
    ChainMultiplyAdd(ConstBinDigits, numBytes, 10, 0);

  // If the denominator isn't 1, divide the numerator by the denominator
  // getting at least FractionBitCnt+2 significant bits of quotient
  if (eexp < 0)
  {
    binExp = -(int)(numBinDigits - (numDecDigits * 10 + 2) / 3);
    for (tmp = binExp; tmp < 0; tmp++)
      ChainMultiplyAdd(ConstBinDigits, numBytes, 2, 0);
    for (tmp = eexp; tmp < 0; tmp++)
      ChainDivide(ConstBinDigits, numBytes, 10, &remainder),
      lastInexact = inexact, inexact |= !!remainder;
  }

  // Find the most significant bit and normalize the mantissa
  // by shifting it left
  for (tmp = numBytes - 1; tmp >= 0 && !ConstBinDigits[tmp]; tmp--);
  if (tmp >= 0)
  {
    tmp = tmp * 8 + 7;
    while (!(ConstBinDigits[tmp / 8] & (1 << tmp % 8))) tmp--;
    while (tmp < FP_MANT_BITS)
      ChainMultiplyAdd(ConstBinDigits, numBytes, 2, 0), binExp--, tmp++;
  }

  // Find the most significant bit and normalize the mantissa
  // by shifting it right
  do
  {
    remainder = 0;
    for (tmp = numBytes - 1; tmp >= 0 && !ConstBinDigits[tmp]; tmp--);
    if (tmp >= 0)
    {
      tmp = tmp * 8 + 7;
      while (!(ConstBinDigits[tmp / 8] & (1 << tmp % 8))) tmp--;
      while (tmp > FP_MANT_BITS)
        ChainDivide(ConstBinDigits, numBytes, 2, &remainder),
        lastInexact = inexact, inexact |= !!remainder, binExp++, tmp--;
      while (binExp < 2 - (1 << (FP_EXP_BITS - 1)) - FP_MANT_BITS)
        ChainDivide(ConstBinDigits, numBytes, 2, &remainder),
        lastInexact = inexact, inexact |= !!remainder, binExp++;
    }
    // Round to nearest even
    remainder &= (lastInexact | (ConstBinDigits[0] & 1));
    if (remainder)
      ChainMultiplyAdd(ConstBinDigits, numBytes, 1, 1);
  } while (remainder);

  // Collect the result's mantissa
  res = 0;
  while (tmp >= 0)
  {
    res <<= 8;
    res |= ConstBinDigits[tmp / 8];
    tmp -= 8;
  }

  // Collect the result's exponent
  binExp += (1 << (FP_EXP_BITS - 1)) - 1 + FP_MANT_BITS;
  if (!(res & (1u << FP_MANT_BITS))) binExp = 0; // subnormal or 0
  res &= ~(1u << FP_MANT_BITS);
  if (binExp >= (1 << FP_EXP_BITS) - 1)
    binExp = (1 << FP_EXP_BITS) - 1, res = 0, inexact |= 1; // +INF
  res |= (unsigned)binExp << FP_MANT_BITS;

  return res;
}
