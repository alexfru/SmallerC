/*
  Copyright (c) 2014-2016, Alexey Frunze
  2-clause BSD license.
*/
#include "istdio.h"
#include <ctype.h>
#include <string.h>

static void __fputc(int c, FILE* f, int cnt[2])
{
  if (cnt[1]) // stop writing after a file write error
    return;

  if (fputc(c, f) != EOF || f->flags & _IOSTRING) // keep counting if (v)s(n)printf()'s buffer exhausted
    cnt[0]++; // TBD??? overflow check???
  else
    cnt[1] = -1; // take a note of a file write error
}

#ifdef __SMALLER_C_32__
#include <float.h>

int __cvtdif(float x, char* buf, int size, int* rem);
int __cvtdff(float x, char* buf, int size, int* zeroes);

static
void roundupf(char* buf, int idx)
{
  do
  {
    if (buf[idx] == '9')
    {
      buf[idx] = '0';
    }
    else
    {
      buf[idx]++;
      break;
    }
  } while (--idx >= 0);
}

// Define MAX_FLT_DIGS to be one greater than the maximum number of
// desired significant digits. Reducing MAX_FLT_DIGS saves stack space.
// Prints full smallest positive denormal (2**-149 ~= 1.4e-45) using "%.149f":
#define MAX_FLT_DIGS (FLT_MANT_DIG - FLT_MIN_EXP + 2)
// Prints full FLT_MAX using "%f":
//#define MAX_FLT_DIGS (FLT_MAX_10_EXP + 2)
// Prints at most 7 significant digits (and the rest are zeroes):
//#define MAX_FLT_DIGS (7 + 1)
static
void printff(float x, int ljust, int sign, int alt, int lzeroes,
             int width, int precision, int conversion,
             FILE* f, int cnt[2])
{
  char buf[1/*overflow digit when rounding*/ + MAX_FLT_DIGS];
  char ebuf[1/*e*/+1/*sign*/+2/*nn*/]; // 2 exponent digits in floats
//  int neg = copysignf(1, x) < 0; // can't portably detect -0.0f otherwise
//  int neg = signbit(x); // can't portably detect -0.0f otherwise
  int upper = isupper(conversion);
  int icnt, iz = 0, dot = 0, fcnt = 0, fz = 0, ecnt = 0, len;
  char* p = buf;
  union
  {
    float f;
    unsigned u;
  } u;

  conversion = tolower(conversion);

//  if (neg) x = -x, sign = '-';
  u.f = x;
  if ((int)u.u < 0)
  {
    u.u &= 0x7FFFFFFF;
    x = u.f;
    sign = '-';
  }

  buf[0] = '0'; // clear rounding overflow

  if (u.u > 0x7F800000) // if (x != x)
  {
    lzeroes = 0;
    strcpy(buf + 1, upper ? "NAN" : "nan");
    icnt = 3;
  }
  else if (u.u == 0x7F800000) // if (x == INFINITY)
  {
    lzeroes = 0;
    strcpy(buf + 1, upper ? "INF" : "inf");
    icnt = 3;
  }
  else
  {
    int wasg = 0;
    int gprecision;
    if (conversion == 'g')
    {
      wasg = 1;
      if (precision < 0)
        precision = 6;
      else if (precision == 0)
        precision = 1;
      // try continuing as %e
      gprecision = precision--;
      conversion = 'e';
    }
lf:
    if (conversion == 'f')
    {
      int rem, lastdig;
      if (precision < 0)
        precision = 6;
      dot = precision || alt;
      icnt = __cvtdif(x, buf + 1, MAX_FLT_DIGS, &rem);
      if (icnt >= MAX_FLT_DIGS)
      {
        // Got MAX_FLT_DIGS digits of integral part
        // (and possibly some implied trailing zeroes).
        // Will use the last digit for rounding.
        iz = icnt - MAX_FLT_DIGS + 1; // trailing zeroes of integral part
        icnt = MAX_FLT_DIGS - 1; // digits of integral part
        fcnt = 0; // digits of fractional part (none)
        fz = precision; // trailing zeroes of fractional part
      }
      else
      {
        // Got fewer than MAX_FLT_DIGS digits in integral part
        // (and no implied trailing zeroes).
        int need = precision + 1/*rounding*/;
        int avail = MAX_FLT_DIGS - icnt;
        iz = 0; // trailing zeroes of integral part (none)
        // Get up to precision + 1 digits of fractional part.
        // Will use the last digit for rounding.
        fcnt = ((need < avail) ? need : avail) - 1; // digits of fractional part
        fz = precision - fcnt; // trailing zeroes of fractional part
        rem = __cvtdff(x, buf + 1 + icnt, fcnt + 1, NULL);
      }
      // Round to even
      if ((lastdig = buf[1 + icnt + fcnt]) >= '5')
      {
        if (lastdig != '5' || rem || ((buf[icnt + fcnt] - '0') & 1))
        {
          roundupf(buf, icnt + fcnt);
          icnt += buf[0] != '0'; // overflow adds a digit in integral part
        }
      }
    }
    else // if (conversion == 'e')
    {
      int rem, lastdig;
      int pow10;
      int need;
      int request;
      if (precision < 0)
        precision = 6;
      dot = precision || alt;
      need = precision + 2/*before dot + rounding*/;
      request = (need < MAX_FLT_DIGS) ? need : MAX_FLT_DIGS;
      icnt = __cvtdif(x, buf + 1, request, &rem);
      if (buf[1] == '0')
      {
        // Integral part is zero.
        // Get fractional part without leading zeroes after the decimal point
        // and get the number of leading zeroes into pow10.
        rem = __cvtdff(x, buf + 1, request, &pow10);
        pow10 = -pow10 - (buf[1] != '0')/*0.0 should keep zero exponent*/;
      }
      else
      {
        // Integral part is non-zero.
        // Get more fractional digits if needed/possible.
        pow10 = icnt - 1; // convert number of integral digits to power
        if (icnt >= request)
          icnt = request; // correct actual number of integral digits obtained
        else
          rem = __cvtdff(x, buf + 1 + icnt, request - icnt, NULL);
      }
      icnt = 1; // digits of integral part
      iz = 0; // trailing zeroes of integral part
      fcnt = request - 2; // digits of fractional part
      fz = precision - fcnt; // trailing zeroes of fractional part
      // Round to even
      if ((lastdig = buf[1 + icnt + fcnt]) >= '5')
      {
        if (lastdig != '5' || rem || ((buf[icnt + fcnt] - '0') & 1))
        {
          roundupf(buf, icnt + fcnt);
          pow10 += buf[0] != '0'; // overflow increments exponent
        }
      }
      if (wasg)
      {
        // see if %f is needed instead of %e
        if (pow10 >= -4 && gprecision > pow10)
        {
          // continue as %f
          precision = gprecision - (pow10 + 1);
          conversion = 'f';
          buf[0] = '0'; // clear rounding overflow
          goto lf;
        }
      }
      ebuf[0] = upper ? 'E' : 'e';
      if (pow10 < 0)
        ebuf[1] = '-', pow10 = -pow10;
      else
        ebuf[1] = '+';
      ebuf[2] = pow10 / 10 + '0';
      ebuf[3] = pow10 % 10 + '0';
      ecnt = 4;
    }
    if (wasg && !alt)
    {
      // remove trailing fractional zeroes and dot
      int i = (buf[0] == '0') + icnt + fcnt - 1;
      while (fcnt && buf[i--] == '0')
        fcnt--;
      if (fcnt == 0)
        dot = 0;
      fz = 0;
    }
  }

  len = (sign != 0) + icnt + iz + dot + fcnt + fz + ecnt;
  width = (width > len) ? (width - len) : 0; // padding

  if (!ljust && !lzeroes)
    while (width)
      __fputc(' ', f, cnt), width--;

  if (sign)
    __fputc(sign, f, cnt);

  if (lzeroes)
    while (width)
      __fputc('0', f, cnt), width--;

  p += buf[0] == '0'; // skip overflow digit if no overflow
  while (icnt--)
    __fputc(*p++, f, cnt);
  while (iz--)
    __fputc('0', f, cnt);
  if (dot)
    __fputc('.', f, cnt);
  while (fcnt--)
    __fputc(*p++, f, cnt);
  while (fz--)
    __fputc('0', f, cnt);

  p = ebuf;
  while (ecnt--)
    __fputc(*p++, f, cnt);

  if (ljust)
    while (width)
      __fputc(' ', f, cnt), width--;
}
#endif

int __doprint(FILE* f, char* fmt, va_list vl)
{
  int cnt[2] = { 0, 0 }; // count, file write error indicator
  int c;
  int ljust, sign, alt, lzeroes;
  int width, precision, lmodifier;

  while ((c = (unsigned char)*fmt++) != '\0')
  {
    if (c != '%' || *fmt == '%')
    {
      __fputc(c, f, cnt);
      fmt += (c == '%');
      continue;
    }
    if ((c = (unsigned char)*fmt++) == '\0')
      return -1;

    ljust = sign = alt = lzeroes = 0;
    for (;;)
    {
      if (c == '-')
        ljust = 1, lzeroes = 0;
      else if (c == '+')
        sign = '+';
      else if (c == ' ')
      {
        if (!sign)
          sign = ' ';
      }
      else if (c == '#')
        alt = 1;
      else if (c == '0')
      {
        if (!ljust)
          lzeroes = 1;
      }
      else
        break;

      if ((c = (unsigned char)*fmt++) == '\0')
        return -1;
    }

    width = -1;
    if (isdigit(c))
    {
      width = 0;
      while (isdigit(c))
      {
        width = width * 10 + (c - '0'); // TBD??? overflow check???
        if ((c = (unsigned char)*fmt++) == '\0')
          return -1;
      }
    }
    else if (c == '*')
    {
      width = *(int*)vl; vl += sizeof(int);
      if (width < 0)
      {
        ljust = 1;
        lzeroes = 0;
        width = -width; // TBD??? overflow check???
      }
      if ((c = *fmt++) == '\0')
        return -1;
    }

    precision = -1;
    if (c == '.')
    {
      if ((c = (unsigned char)*fmt++) == '\0')
        return -1;
      precision = 0;
      if (isdigit(c))
      {
        while (isdigit(c))
        {
          precision = precision * 10 + (c - '0'); // TBD??? overflow check???
          if ((c = (unsigned char)*fmt++) == '\0')
            return -1;
        }
      }
      else if (c == '*')
      {
        precision = *(int*)vl; vl += sizeof(int);
        if ((c = *fmt++) == '\0')
          return -1;
      }
    }

    lmodifier = 0;
    if (c == 'h')
    {
      if (*fmt == 'h')
      {
        fmt++;
        lmodifier = 'H';
      }
      else
      {
        lmodifier = c;
      }
    }
#ifdef __SMALLER_C_32__
    else if (c == 'l' || c == 'L')
    {
      lmodifier = c;
    }
#endif
    else if (strchr("jzt", c))
    {
      lmodifier = c;
    }
    if (lmodifier)
      if ((c = (unsigned char)*fmt++) == '\0')
        return -1;

    if (c == 'n')
    {
      if (lmodifier == 'H')
        **(signed char**)vl = cnt[0], vl += sizeof(signed char*);
      else if (lmodifier == 'h')
        **(short**)vl = cnt[0], vl += sizeof(short*);
      else
        **(int**)vl = cnt[0], vl += sizeof(int*);
      continue;
    }

    if (c == 'i')
      c = 'd';
#ifdef __SMALLER_C_32__
    if (!strchr("douxXcspeEfFgG", c))
      return -1;
#else
    if (!strchr("douxXcsp", c))
      return -1;
#endif

    if (c == 'c')
    {
      int ch = (unsigned char)*(int*)vl;
      vl += sizeof(int);

      if (!ljust)
        while (width > 1)
          __fputc(' ', f, cnt), width--;

      __fputc(ch, f, cnt);

      if (ljust)
        while (width > 1)
          __fputc(' ', f, cnt), width--;

      continue;
    }
    else if (c == 's')
    {
      char* s = *(char**)vl;
      int len, i;
      vl += sizeof(char*);

      if (!s)
        s = "(null)"; // Not defined/required by the standard, but helpful

      if (precision < 0)
      {
        len = strlen(s); // TBD??? overflow check???
      }
      else
      {
        len = 0;
        while (len < precision)
          if (s[len])
            len++;
          else
            break;
      }

      if (!ljust)
        while (width > len)
          __fputc(' ', f, cnt), width--;

      i = len;
      while (i--)
        __fputc(*s++, f, cnt);

      if (ljust)
        while (width > len)
          __fputc(' ', f, cnt), width--;

      continue;
    }
#ifdef __SMALLER_C_32__
    else if (strchr("eEfFgG", c))
    {
      float v = *(float*)vl;
      vl += sizeof(v);
      printff(v, ljust, sign, alt, lzeroes, width, precision, c, f, cnt);
      continue;
    }
#endif
    else
    {
      unsigned v = *(unsigned*)vl, tmp;
      char s[11]; // up to 11 octal digits in 32-bit numbers
      char* p = s + sizeof s;
      unsigned base = (c == 'p') ? 16 : 10;
      char* digits = "0123456789abcdef";
      char* hexpfx = NULL;
      int dcnt;
      int len;
      vl += sizeof(unsigned);

      if (precision >= 0)
        lzeroes = 0;

      if (c == 'o')
        base = 8;
      else if (toupper(c) == 'X')
      {
        base = 16;
        if (c == 'X')
          digits = "0123456789ABCDEF";
        if (alt && v)
          hexpfx = (c == 'X') ? "0X" : "0x";
      }

      if (c != 'd')
      {
        if (lmodifier == 'H')
          v = (unsigned char)v;
        else if (lmodifier == 'h')
          v = (unsigned short)v;
        sign = 0;
      }
      else
      {
        if (lmodifier == 'H')
          v = (signed char)v;
        else if (lmodifier == 'h')
          v = (short)v;
        if ((int)v < 0)
          v = -v, sign = '-';
      }

      tmp = v;
      do
      {
        *--p = digits[tmp % base];
        tmp /= base;
      } while (tmp);
      dcnt = s + sizeof s - p;

      if (precision < 0)
        precision = 1;
      else if (v == 0 && precision == 0)
        dcnt = 0;

      if (alt && c == 'o')
        if ((v == 0 && precision == 0) || (v && precision <= dcnt))
          precision = dcnt + 1;

      if (precision < dcnt)
        precision = dcnt;

      // width padding:
      // - left/right
      // - spaces/zeroes (zeroes are to appear after sign/base prefix)
      // sign:
      // - '-' if negative
      // - '+' or '-' always
      // - space if non-negative or empty
      // alt:
      // - octal: prefix 0 to conversion if non-zero or empty
      // - hex: prefix "0x"/"0X" to conversion if non-zero
      // precision:
      // - prefix conversion digits with zeroes to precision
      // - special case: 0 with precision=0 results in empty conversion

      // [leading spaces] [sign/hex prefix] [leading zeroes] [(precision-dcnt) zeroes] [dcnt digits] [trailing spaces]
      len = (sign != 0) + (hexpfx != NULL) * 2 + precision;

      if (!ljust && !lzeroes)
        while (width > len)
          __fputc(' ', f, cnt), width--;

      if (sign)
        __fputc(sign, f, cnt);
      else if (hexpfx)
        __fputc(hexpfx[0], f, cnt), __fputc(hexpfx[1], f, cnt);

      if (!ljust && lzeroes)
        while (width > len)
          __fputc('0', f, cnt), width--;

      while (precision-- > dcnt)
        __fputc('0', f, cnt);

      while (dcnt--)
        __fputc(*p++, f, cnt);

      if (ljust)
        while (width > len)
          __fputc(' ', f, cnt), width--;

      continue;
    }
  }

  return cnt[1] ? -1 : cnt[0];
}
