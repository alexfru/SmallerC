/*
  Copyright (c) 2017, Alexey Frunze
  2-clause BSD license.
*/

#ifdef __SMALLER_C_32__

#include <string.h>
#include "ifp.h"

static
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

static
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

  if (pRemainder)
    *pRemainder = remainder >> 8;
}

// Multiplies an integer (cnt decimal digits (0 to 9) from digits[]) by
// 10**eexp, converts the product to a float and returns it as unsigned int.
// This is an inefficient but straightforward algorithm with proper rounding.
unsigned __cvtfd(unsigned char* digits, int cnt, int eexp)
{
  unsigned char ConstBinDigits[FP_BUF_SIZE];
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
/*
  if (numBytes > (unsigned)FP_BUF_SIZE)
    errorInternal(200);
*/
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

#endif
