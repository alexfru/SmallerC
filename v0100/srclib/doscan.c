/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include "istdio.h"
#include <ctype.h>
#include <string.h>

int __doscan(FILE* f, char* fmt, va_list vl)
{
  int cnt = 0;
  int c, c2;
  int chcnt = 0;

  while ((c = (unsigned char)*fmt++) != '\0')
  {
    if (isspace(c))
    {
      do
      {
        c = (unsigned char)*fmt++;
      } while (isspace(c));
      fmt--;
      do
      {
        c2 = fgetc(f);
        chcnt++;
      } while (isspace(c2));
      if (c2 != EOF)
        ungetc(c2, f), chcnt--;
    }

    else if (c != '%' || *fmt == '%')
    {
      fmt += (c == '%');
      goto lmatchchars2;
lmatchchars:
      if ((c = (unsigned char)*fmt++) == '\0')
        return cnt;
      if (isspace(c) || c == '%')
      {
        fmt--;
        continue;
      }
lmatchchars2:
      c2 = fgetc(f);
      chcnt++;
      if (c2 == c)
        goto lmatchchars;
      return (c2 == EOF) ? EOF : (ungetc(c2, f), cnt);
    }

    else // if (c == '%')
    {
      int assign = 1, width = -1, lmodifier = 0;

      if ((c = (unsigned char)*fmt++) == '\0')
        return EOF;

      if (c == '*')
      {
        assign = 0;
        if ((c = (unsigned char)*fmt++) == '\0')
          return EOF;
      }

      if (isdigit(c))
      {
        width = 0;
        do
        {
          width = width * 10 + (c - '0'); // TBD??? overflow check???
          if ((c = (unsigned char)*fmt++) == '\0')
            return EOF;
        } while (isdigit(c));
        if (!width)
          return EOF;
      }

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
          return EOF;

      if (c == 'n')
      {
        if (lmodifier == 'H')
          **(signed char**)vl = chcnt, vl += sizeof(signed char*);
        else if (lmodifier == 'h')
          **(short**)vl = chcnt, vl += sizeof(short*);
        else
          **(int**)vl = chcnt, vl += sizeof(int*);
        continue;
      }

      if (c == 'X')
        c = 'x';
      else if (!strchr("diouxcsp[", c))
        return EOF;

      if (c != 'c' && c != '[')
      {
        while (isspace(c2 = fgetc(f)))
          chcnt++;
        if (c2 != EOF)
          ungetc(c2, f);
      }
      if ((c2 = fgetc(f)) == EOF)
        return cnt ? cnt : EOF;
      ungetc(c2, f);
      // There must be at least one input char now

      if (c == 'c')
      {
        char* p;
        if (assign)
          p = *(char**)vl, vl += sizeof(char*);
        if (width < 0)
          width = 1;
        while (width-- > 0)
        {
          if ((c2 = fgetc(f)) == EOF)
            break;
          if (assign)
            *p++ = c2;
          chcnt++;
        }
        cnt += assign;
      }
      else if (c == 's')
      {
        char* p;
        if (assign)
          p = *(char**)vl, vl += sizeof(char*);

        if (width < 0)
          width = (unsigned)-1 / 2;
        while (width-- > 0 && (c2 = fgetc(f)) != EOF) // there must be at least 1 non-white-space char, we just checked
        {
          if (isspace(c2))
          {
            ungetc(c2, f);
            break;
          }
          if (assign)
            *p++ = c2;
          chcnt++;
        }

        if (assign)
          *p++ = '\0';
        cnt += assign;
      }
      else if (c != '[')
      {
        unsigned base = 0;
        int sign = 0, lzero = 0, hexpfx = 0, dcnt = 0, match = 1;
        unsigned n = 0;
        enum
        {
          ST_CHECK_SIGN,
          ST_CHECK_0,
          ST_CHECK_X,
          ST_CHECK_DIGIT
        } state = ST_CHECK_SIGN;

        if (width < 0)
          width = (unsigned)-1 / 2;

        if (c == 'x' || c == 'p')
          base = 16;
        else if (c == 'o')
          base = 8;
        else if (c != 'i') // if (c == 'd' || c == 'u')
          base = 10;
        // base may still be unknown (0) now

        while (match && width > 0)
        {
          if ((c2 = fgetc(f)) == EOF)
            break;

          switch (state)
          {
          case ST_CHECK_SIGN:
            if (c2 == '-' || c2 == '+')
            {
              sign = c2;
              chcnt++;
              width--;
            }
            else
            {
              ungetc(c2, f);
            }
            state = ST_CHECK_0;
            break;

          case ST_CHECK_0:
            if (c2 == '0')
            {
              lzero = 1;
              chcnt++;
              width--;
              if ((base | 16) == 16) // unknown base or 16
                state = ST_CHECK_X;
              else
                state = ST_CHECK_DIGIT;
            }
            else
            {
              ungetc(c2, f);
              state = ST_CHECK_DIGIT;
            }
            break;

          case ST_CHECK_X:
            if (toupper(c2) == 'X')
            {
              hexpfx = 1;
              base = 16;
              chcnt++;
              width--;
            }
            else
            {
              if (base == 0)
                base = 8;
              ungetc(c2, f);
            }
            state = ST_CHECK_DIGIT;
            break;

          case ST_CHECK_DIGIT:
            {
              int d = c2;
              if (base == 0)
                base = 10;

              if (isdigit(d))
                d -= '0';
              else if (isalpha(d))
                d = (d & ~0x20) - ('A' - 10);
              else
                match = 0;
              if (d >= base)
                match = 0;
              if (!match)
              {
                ungetc(c2, f);
                break;
              }

              n *= base;
              n += d;

              dcnt++;
              chcnt++;
              width--;
            }
            break;
          } // endof switch (state)
        } // while (match && width > 0)

        dcnt += lzero - hexpfx;
        if (!dcnt)
          return (!match | !width) ? cnt : EOF;

        if (assign)
        {
          if (sign == '-')
            n = -n;
          if (lmodifier == 'H')
            **(unsigned char**)vl = n, vl += sizeof(unsigned char*);
          else if (lmodifier == 'h')
            **(unsigned short**)vl = n, vl += sizeof(unsigned short*);
          else
            **(unsigned**)vl = n, vl += sizeof(unsigned*);
          cnt++;
        }
      }
      else // if (c == '[')
      {
        unsigned char set[256/8] = { 0 };
        int exclude = 0, idx = 0;
        char* p;
        if (assign)
          p = *(char**)vl, vl += sizeof(char*);

        if (*fmt == '^')
          exclude = 1, fmt++;
        // TBD??? support ranges, e.g. "[a-z]"???
        while ((c = (unsigned char)*fmt++) != '\0')
        {
          if (c == ']' && idx)
            break;
          set[c>>3] |= 1 << (c&7);
          idx++;
        }
        if (c == '\0')
          return EOF;

        if (width < 0)
          width = (unsigned)-1 / 2;
        idx = 0;
        while (width-- > 0 && (c2 = fgetc(f)) != EOF) // there must be at least 1 non-white-space char, we just checked
        {
          int inset = (set[c2>>3] & (1 << (c2&7))) != 0;
          if (inset == exclude)
          {
            ungetc(c2, f);
            break;
          }
          if (assign)
            *p++ = c2;
          chcnt++;
          idx++;
        }
        if (!idx)
          return cnt;

        if (assign)
          *p++ = '\0';
        cnt += assign;
      }
    }
  }

  return cnt;
}
