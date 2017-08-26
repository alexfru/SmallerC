/*
  Copyright (c) 2014-2017, Alexey Frunze
  2-clause BSD license.
*/
#include "istdio.h"
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "ifp.h"

// *scanf() returns the number of assignments (which is 0 if matching
// failure occurs before the first assignment) or EOF if input failure
// occurs before the first assignment.
// If the width is too small, it's a matching failure.
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
      if (c2 != EOF)
        ungetc(c2, f);
      else
        return cnt ? cnt : EOF;
      return cnt;
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

#ifdef __SMALLER_C_32__
      if (strchr("fgEFG", c))
        c = 'e';
#endif
      if (c == 'X')
        c = 'x';
      else if (!strchr("dioux"
#ifdef __SMALLER_C_32__
                       "e"
#endif
                       "csp[", c))
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
        while (width > 0)
        {
          if ((c2 = fgetc(f)) == EOF)
            break;
          if (assign)
            *p++ = c2;
          chcnt++;
          width--;
        }
        if (width == 0)
          cnt += assign;
        else
          return cnt ? cnt : EOF;
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
#ifdef __SMALLER_C_32__
      else if (c == 'e')
      {
        // There can be up to 112 significant digits in a 32-bit single precision
        // floating point number (in the maximum positive denormal number).
        // We'll ignore any following digits, but convert these 112 with proper
        // rounding to even, which is enough for all floats representable exactly,
        // which should be enough for most practical purposes.
        unsigned char digits[MAX_FP_DIGITS];
        int stop = 0;
        int mcnt = 0, mexp = 0;
        int sign = 0;
        char* word = NULL;
        int widx = 0;
        int gotint = 0, gotfrct = 0;
        int gotexp = 0, esign = 0;
        unsigned eexp = 0;
        float val = 0;
        enum
        {
          ST_CHECK_SIGN,
          ST_CHECK_INF_NAN,
          ST_CHECK_WORD,
          ST_CHECK_LEADING_0,
          ST_CHECK_INT_DIGIT,
          ST_CHECK_FRCT_LEADING_0,
          ST_CHECK_FRCT_DIGIT,
          ST_CHECK_EXP_SIGN,
          ST_CHECK_EXP_DIGIT,
        } state = ST_CHECK_SIGN;

        if (width < 0)
          width = (unsigned)-1 / 2;

        while (!stop)
        {
          // Pass EOF (either a real one from fgetc() or a fake one when width
          // chars have been read) through all the states in order to handle
          // error conditions in context.
          if (width > 0)
            c2 = fgetc(f); // EOF from here may signify input failure
          else
            c2 = EOF, stop = 1; // EOF from here may signify matching failure

          switch (state)
          {
          case ST_CHECK_SIGN:
            if (c2 == '-' || c2 == '+')
            {
              chcnt++; width--;
              sign = c2;
            }
            else
            {
              ungetc(c2, f);
              if (c2 < 0)
                return (cnt | stop) ? cnt : EOF;
            }
            state = ST_CHECK_INF_NAN;
            break;

          case ST_CHECK_INF_NAN:
            if (toupper(c2) == 'I')
            {
              chcnt++; width--;
              word = "INFINITY"; widx = 1;
              state = ST_CHECK_WORD;
            }
            else if (toupper(c2) == 'N')
            {
              chcnt++; width--;
              word = "NAN"; widx = 1;
              state = ST_CHECK_WORD;
            }
            else
            {
              ungetc(c2, f);
              if (c2 < 0)
                return (cnt | stop) ? cnt : EOF;
              state = ST_CHECK_LEADING_0;
            }
            break;

          case ST_CHECK_WORD:
            if (toupper(c2) == word[widx])
            {
              chcnt++; width--;
              if (word[++widx] == '\0')
                stop = 1; // matched "INFINITY" or "NAN", exit the loop
            }
            else
            {
              ungetc(c2, f);
              if (widx == 3)
                stop = 1; // matched "INF", exit the loop
              else
                return cnt;
            }
            break;

          case ST_CHECK_LEADING_0:
            if (c2 == '0')
            {
              chcnt++; width--;
              gotint = 1; // got integral part digits: all zeroes so far
            }
            else
            {
              ungetc(c2, f);
              if (c2 < 0)
              {
                if (gotint)
                  stop = 1; // matched a number, exit the loop
                else
                  return (cnt | stop) ? cnt : EOF;
              }
              state = ST_CHECK_INT_DIGIT;
            }
            break;

          case ST_CHECK_INT_DIGIT:
            if (isdigit(c2))
            {
              chcnt++; width--;
              gotint = 2; // got integral part digits: non-zero
              if (mcnt < MAX_FP_DIGITS)
                digits[mcnt++] = c2 - '0';
              else
                mexp++; // TBD??? overflow
            }
            else if (c2 == '.')
            {
              chcnt++; width--;
              state = (gotint == 2) ? ST_CHECK_FRCT_DIGIT : ST_CHECK_FRCT_LEADING_0;
            }
            else if (toupper(c2) == 'E' && gotint)
            {
              chcnt++; width--;
              gotexp = 1; // got e/E
              state = ST_CHECK_EXP_SIGN;
            }
            else
            {
              ungetc(c2, f);
              if (gotint)
                stop = 1; // matched a number, exit the loop
              else
                return (cnt | stop | (c2 >= 0)) ? cnt : EOF;
            }
            break;

          case ST_CHECK_FRCT_LEADING_0:
            if (c2 == '0')
            {
              chcnt++; width--;
              gotfrct = 1; // got fractional part digits: all zeroes so far
              mexp--; // TBD??? overflow
            }
            else
            {
              ungetc(c2, f);
              if (c2 < 0)
              {
                if (gotint | gotfrct)
                  stop = 1; // matched a number, exit the loop
                else
                  return (cnt | stop) ? cnt : EOF;
              }
              state = ST_CHECK_FRCT_DIGIT;
            }
            break;

          case ST_CHECK_FRCT_DIGIT:
            if (isdigit(c2))
            {
              chcnt++; width--;
              gotfrct = 2; // got fractional part digits: non-zero
              if (mcnt < MAX_FP_DIGITS)
                digits[mcnt++] = c2 - '0';
              mexp--; // TBD??? overflow
            }
            else if (toupper(c2) == 'E' && (gotint | gotfrct))
            {
              chcnt++; width--;
              gotexp = 1; // got e/E
              state = ST_CHECK_EXP_SIGN;
            }
            else
            {
              ungetc(c2, f);
              if (gotint | gotfrct)
                stop = 1; // matched a number, exit the loop
              else
                return (cnt | stop | (c2 >= 0)) ? cnt : EOF;
            }
            break;

          case ST_CHECK_EXP_SIGN:
            if (c2 == '-' || c2 == '+')
            {
              chcnt++; width--;
              esign = c2;
            }
            else
            {
              ungetc(c2, f);
              if (c2 < 0)
                return (cnt | stop) ? cnt : EOF;
            }
            state = ST_CHECK_EXP_DIGIT;
            break;

          case ST_CHECK_EXP_DIGIT:
            if (isdigit(c2))
            {
              int d = c2 - '0';
              unsigned ex10 = eexp * 10;
              chcnt++; width--;
              gotexp = 2; // got e/E and exponent part digits
              if (ex10 / 10 != eexp ||
                  ex10 + d < ex10 ||
                  ex10 + d > (unsigned)-1 / 2)
                eexp = (unsigned)-1 / 2; // cap exponent
              else
                eexp = ex10 + d;
            }
            else
            {
              ungetc(c2, f);
              if (gotexp == 2)
                stop = 1; // matched a number, exit the loop
              else
                return (cnt | stop | (c2 >= 0)) ? cnt : EOF;
            }
            break;
          } // endof switch (state)
        } // endof while (!stop)

        if (word)
        {
          val = (*word == 'N') ? NAN : INFINITY;
        }
        else if (assign)
        {
          int e = (esign == '-') ? -(int)eexp : (int)eexp;
          // drop trailing zeroes, if any
          while (mcnt && !digits[mcnt - 1])
          {
            mcnt--;
            mexp++; // TBD??? overflow
          }
          if (!mcnt)
            mexp = digits[mcnt++] = 0;

          if (mexp >= 0 && e > INT_MAX - mexp)
            mexp = INT_MAX;
          else if (mexp < 0 && e < INT_MIN - mexp)
            mexp = INT_MIN;
          else
            mexp += e;
          eexp = __cvtfd(digits, mcnt, mexp);
          memcpy(&val, &eexp, sizeof val);
        }
        if (sign == '-')
          val = -val;
        if (assign)
        {
          **(float**)vl = val, vl += sizeof(float*);
          cnt++;
        }
      }
#endif
      else if (c != '[')
      {
        int stop = 0;
        unsigned base = 0;
        int sign = 0, gotint = 0;
        unsigned n = 0;
        enum
        {
          ST_CHECK_SIGN,
          ST_CHECK_0,
          ST_CHECK_X,
          ST_CHECK_DIGIT
        } state = ST_CHECK_SIGN;

        if (c == 'x' || c == 'p')
          base = 16;
        else if (c == 'o')
          base = 8;
        else if (c != 'i') // if (c == 'd' || c == 'u')
          base = 10;
        // base may still be unknown (0) now

        if (width < 0)
          width = (unsigned)-1 / 2;

        while (!stop)
        {
          // Pass EOF (either a real one from fgetc() or a fake one when width
          // chars have been read) through all the states in order to handle
          // error conditions in context.
          if (width > 0)
            c2 = fgetc(f); // EOF from here may signify input failure
          else
            c2 = EOF, stop = 1; // EOF from here may signify matching failure

          switch (state)
          {
          case ST_CHECK_SIGN:
            if (c2 == '-' || c2 == '+')
            {
              chcnt++; width--;
              sign = c2;
            }
            else
            {
              ungetc(c2, f);
              if (c2 < 0)
                return (cnt | stop) ? cnt : EOF;
            }
            state = ST_CHECK_0;
            break;

          case ST_CHECK_0:
            if (c2 == '0')
            {
              chcnt++; width--;
              gotint = 1;
              if ((base | 16) == 16) // unknown base or 16
                state = ST_CHECK_X;
              else
                state = ST_CHECK_DIGIT;
            }
            else
            {
              ungetc(c2, f);
              if (c2 < 0)
                return (cnt | stop) ? cnt : EOF;
              state = ST_CHECK_DIGIT;
            }
            break;

          case ST_CHECK_X:
            if (toupper(c2) == 'X')
            {
              chcnt++; width--;
              gotint = 0;
              base = 16;
            }
            else
            {
              if (base == 0)
                base = 8;
              ungetc(c2, f);
              if (c2 < 0)
                stop = 1; // matched 0
            }
            state = ST_CHECK_DIGIT;
            break;

          case ST_CHECK_DIGIT:
            {
              int d = c2;
              int valid = 1;
              if (base == 0)
                base = 10;

              if (isdigit(d))
                d -= '0';
              else if (isalpha(d))
                d = (d & ~0x20) - ('A' - 10);
              else
                valid = 0;
              if (valid && d >= base)
                valid = 0;

              if (valid)
              {
                chcnt++; width--;
                gotint = 1;
                n *= base;
                n += d;
              }
              else
              {
                ungetc(c2, f);
                if (gotint)
                  stop = 1; // matched a number, exit the loop
                else
                  return (cnt | stop | (c2 >= 0)) ? cnt : EOF;
              }
            }
            break;
          } // endof switch (state)
        } // while (!stop)

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
        int exclude = 0, idx = 0, readone = 0;
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
          readone = 1;
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
          return (cnt | readone) ? cnt : EOF;

        if (assign)
          *p++ = '\0';
        cnt += assign;
      }
    }
  }

  return cnt;
}
