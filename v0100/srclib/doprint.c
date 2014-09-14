/*
  Copyright (c) 2014, Alexey Frunze
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
      lzeroes = 0;
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
    else if (c == 'l')
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
    if (!strchr("douxXcsp", c))
      return -1;

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
