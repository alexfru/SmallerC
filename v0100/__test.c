//// comment comment */ comment /* comment //

/* comment /* comment
// comment */

int putchar(int c);
int getchar(void);
void pokeb(unsigned seg, unsigned ofs, char val);

char* strcpy(char* s1, char* s2)
{
  char* tmp = s1;
  while(*s1++ = *s2++);
  return tmp;
}
unsigned strlen(char* s)
{
  unsigned l = 0;
  while(*s++) ++l;
  return l;
}
char* strchr(char* s, int c)
{
  do
  {
    if (*s == c)
      return s;
  } while (*s++ != '\0');
  return 0;
}

int puts(char* s)
{
  while (*s)
    putchar(*s++);
  putchar('\n');
  return 0;
}

int isspace(int c)
{
  return c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v';
}
int isdigit(int c)
{
  return c >= '0' && c <= '9';
}

int vprintf(char* fmt, void* vl)
{
  int* pp = vl;
  int cnt = 0;
  char* p;
  char* phex = "0123456789abcdef";
  char s[1/*sign*/+10/*magnitude*/+1/*\0*/]; // up to 11 octal digits in 32-bit numbers
  char* pc;
  int n, sign, msign;
  int minlen = 0, len;

  for (p = fmt; *p != '\0'; p++)
  {
    if (*p != '%' || p[1] == '%')
    {
      putchar(*p);
      p = p + (*p == '%');
      cnt++;
      continue;
    }
    p++;
    minlen = 0;
    msign = 0;
    if (*p == '+') { msign = 1; p++; }
    else if (*p == '-') { msign = -1; p++; }
    if (isdigit(*p))
    {
      while (isdigit(*p))
        minlen = minlen * 10 + *p++ - '0';
      if (msign < 0)
        minlen = -minlen;
      msign = 0;
    }
    if (!msign)
    {
      if (*p == '+') { msign = 1; p++; }
      else if (*p == '-') { msign = -1; p++; }
    }
    switch (*p)
    {
    case 'c':
      while (minlen > 1) { putchar(' '); cnt++; minlen--; }
      putchar(*pp++);
      while (-minlen > 1) { putchar(' '); cnt++; minlen++; }
      cnt++;
      break;
    case 's':
      pc = *pp++;
      len = 0;
      if (pc)
        len = strlen(pc);
      while (minlen > len) { putchar(' '); cnt++; minlen--; }
      if (len)
        while (*pc != '\0')
        {
          putchar(*pc++); 
          cnt++;
        }
      while (-minlen > len) { putchar(' '); cnt++; minlen++; }
      break;
    case 'i':
    case 'd':
      pc = &s[sizeof s - 1];
      *pc = '\0';
      len = 0;
      n = *pp++;
      sign = 1 - 2 * (n < 0);
      do
      {
        *--pc = '0' + (n - n / 10 * 10) * sign;
        n = n / 10;
        len++;
      } while (n);
      if (sign < 0)
      {
        *--pc = '-';
        len++;
      }
      else if (msign > 0)
      {
        *--pc = '+';
        len++;
        msign = 0;
      }
      while (minlen > len) { putchar(' '); cnt++; minlen--; }
      while (*pc != '\0')
      {
        putchar(*pc++); 
        cnt++;
      }
      while (-minlen > len) { putchar(' '); cnt++; minlen++; }
      break;
    case 'u':
      pc = &s[sizeof s - 1];
      *pc = '\0';
      len = 0;
      n = *pp++;
      do
      {
        unsigned nn = n;
        *--pc = '0' + nn % 10;
        n = nn / 10;
        len++;
      } while (n);
      if (msign > 0)
      {
        *--pc = '+';
        len++;
        msign = 0;
      }
      while (minlen > len) { putchar(' '); cnt++; minlen--; }
      while (*pc != '\0')
      {
        putchar(*pc++); 
        cnt++;
      }
      while (-minlen > len) { putchar(' '); cnt++; minlen++; }
      break;
    case 'X':
      phex = "0123456789ABCDEF";
      // fallthrough
    case 'p':
    case 'x':
      pc = &s[sizeof s - 1];
      *pc = '\0';
      len = 0;
      n = *pp++;
      do
      {
        unsigned nn = n;
        *--pc = phex[nn & 0xF];
        n = nn >> 4;
        len++;
      } while (n);
      while (minlen > len) { putchar(' '); cnt++; minlen--; }
      while (*pc != '\0')
      {
        putchar(*pc++); 
        cnt++;
      }
      while (-minlen > len) { putchar(' '); cnt++; minlen++; }
      break;
    case 'o':
      pc = &s[sizeof s - 1];
      *pc = '\0';
      len = 0;
      n = *pp++;
      do
      {
        unsigned nn = n;
        *--pc = '0' + (nn & 7);
        n = nn >> 3;
        len++;
      } while (n);
      while (minlen > len) { putchar(' '); cnt++; minlen--; }
      while (*pc != '\0')
      {
        putchar(*pc++); 
        cnt++;
      }
      while (-minlen > len) { putchar(' '); cnt++; minlen++; }
      break;
    default:
      return -1;
    }
  }

  return cnt;
}

int printf(char* fmt, ...)
{
  void** pp = &fmt;
  return vprintf(fmt, pp + 1);
}

void putdec(int n)
{
  int r;

  if (n < 0)
  {
    putchar('-');
    r = n / 10 * 10 - n;
    n = n / -10;
  }
  else
  {
    r = n % 10;
    n = n / 10;
  }

  if (n)
    putdec(n);

  putchar('0' + r);
}

void putdecu(unsigned n)
{
  int r;

  r = n % 10;
  n = n / 10;

  if (n)
    putdecu(n);

  putchar('0' + r);
}

int fact(int x)
{
  if (x <= 1)
    return 1;

  return x * fact(x - 1);
}

int fib(int x)
{
  if (x <= 0) return 0;
  else if (x == 1) return 1;
  return fib(x - 1) + fib(x - 2);
}

void breakCont(void)
{
  int i;
  for (i = 0; i < 10; i++)
  {
    int j = i;
    if (j == 1)
      continue;
    putdec(j);
    if (j==7)
      break;
  }
  putchar('\n');
}

void PointerStew(void)
{
  char* c[4];
  char** cp[4];
  char*** cpp = cp;

  c[0] = "ENTER";
  c[1] = "NEW";
  c[2] = "POINT";
  c[3] = "FIRST";

  cp[0] = c + 3;
  cp[1] = c + 2;
  cp[2] = c + 1;
  cp[3] = c;

  printf("%s", **++cpp);
  printf("%s ", *--*++cpp + 3);
  printf("%s", *cpp[-2] + 3);
  printf("%s\n", cpp[-1][-1] + 1);
}

void (*(*(*(*(*(*(*Print8
  (char* Str))
  (char*))
  (char*))
  (char*))
  (char*))
  (char*))
  (char*))
  (char*)
{
  printf("%s", Str);
  return &Print8;
}

void macros(void)
{
 # define/*comment*/SOMETHING/*comment*/42/*comment*/ // comment
#define NOTHING/*comment*/
#define SOMETHING_2 "42" // comment /*comment*/
  NOTHING
  printf("SOMETHING=%d, SOMETHING_2=\"%s\"\n", SOMETHING, SOMETHING_2);
  NOTHING
//#define BLAH()
//#define NOTHING
/*
#define M1 M2
#define M2 M1
  M2
*/
/*
#define MMM MMM
  MMM
*/
/*
#define MMM MMMQ
  MMM
*/
}

char* Hola = "iHola!";

int main(void)
{
  char hws[16], *phw = hws;
  *phw++='H'; *phw++='e'; *phw++='l'; *phw++='l'; *phw++='o'; *phw++=' ';
  *phw++='W'; *phw++='o'; *phw++='r'; *phw++='l'; *phw++='d'; *phw++='!'; *phw++='\0';

  printf("hws=\"%s\", strlen(hws)=%u\n", hws, strlen(hws));
  puts("Buongiorno!");
  puts(Hola);

  printf("%% char='%c' str=\"%s\" dec=%d hex=%x %% char='%c' str=\"%s\" dec=%d hex=%X\n",
         'a', "abc", 32767, 0xAAAA, 'z', "xyz", -32767-1, 0xFFFF);

  printf("07777=%d, 0xFff=%d, 4095=0%o\n", 07777, 0xFff, 4095);

  printf("'\\x0'=%X, '\\x7F'=%X, '\\0'=%o, '\\177'=%o, '\\xFf'=%X, '\\377'=%o\n",
         '\x0', '\x7F', '\0', '\177', '\xFf', '\377');

  printf("\"xyz\"[2]='%c', sizeof \"az\"=%u\n", "xyz"[2], sizeof "az");

  printf("fact(7)=%d, fib(10)=%d\n", fact(7), fib(10));

  printf("printf(\"pea\\0nut\"): \"%s\"\n", "pea\0nut");
  printf("printf(\"peanut\" + 3): \"%s\"\n", "peanut" + 3);

  puts("press a key..."); getchar();

  breakCont();
  int xx, yy[sizeof(xx)][2];
  int zz[sizeof("az")][2];
  void Switch(void);
  Switch();
  char* pgb = "Green on Black!";
  puts(pgb);

  int x, y;
  for (y = 0; y < 25; y++)
    for (x = 0; x < 80; x++)
      pokeb(0xB800, (y * 80 + x) * 2 + 1, 0x02);

  puts("press a key once for graphics mode and then another time for text mode..."); getchar();

  void gfxmode(int mode);
  gfxmode(0x13);
  for (y = 0; y < 200; y++)
    for (x = 0; x < 320; x++)
      pokeb(0xA000, y * 320 + x, (x + y) & 15);
  getchar();
  gfxmode(3);

  printf("sizeof(char)=%u\n", sizeof(char));
  printf("sizeof(int)=%u\n", sizeof(int));
  printf("sizeof(char[3])=%u\n", sizeof(char[3]));
  printf("sizeof char(*[5])()=%u\n", sizeof char(*[5])());
  printf("sizeof(int[sizeof(int[sizeof(int[3])])])=%u\n", sizeof(int[sizeof(int[sizeof(int[3])])]));
  char yui[sizeof(int[sizeof(int[sizeof(int[3])])])];
  printf("sizeof(char(*)())=%u\n", sizeof(char(*)()));
  printf("sizeof(char())=%u\n", sizeof(char()));
  printf("sizeof(char*())=%u\n", sizeof(char*()));
  printf("sizeof(int())=%u\n", sizeof(int()));
  printf("sizeof main=%u\n", sizeof main);
  printf("sizeof main()=%u\n", sizeof main());
  printf("sizeof(void()())=%u\n", sizeof(void()()));
  printf("sizeof((char[7]))=%u\n", sizeof((char[7])));

  PointerStew();
  Print8("hello")(" ")("world")("!")("\n");
  macros();
/*
  TBD!!!
#define SIX "six "
  printf("These ""are " SIX "concatenated ""string "  "literals!\n");
*/
  printf("These ""are " "six ""concatenated ""string "  "literals!\n");
  printf("\"\\x41\\x42\\x43\\60\\61\\62abc\" = \"%s\"\n", "\x41\x42\x43\60\61\62abc");

  puts("press a key..."); getchar();

  int arr[3], *p = arr + 1;
  arr[0] = 11;
  arr[1] = 22;
  arr[2] = 33;

  printf("arr[0]=%d\n", *(p -= 1));
  printf("arr[1]=%d\n", *(p += 1));
  printf("arr[2]=%d\n", *(p += 1));

  printf("arr[0] *= arr[1] *= arr[2];\n");
  arr[0] *= arr[1] *= arr[2];

  printf("arr[0]=%d\narr[1]=%d\narr[2]=%d\n", arr[0], arr[1], arr[2]);

  char c = 127;
  printf("char c = 127; sizeof(c * 127)=%d; sizeof(c *= 127)=%d\n", sizeof(c * 127), sizeof(c *= 127));
  printf("printf(\"%%d\\n\", c * 127): %d\n", c * 127);
  printf("printf(\"%%d\\n\", c *= 127): %d\n", c *= 127); // DONE: must be 1, not 16129

  putdecu(32767); putchar('\n');
  putdecu(32768u); putchar('\n');
  putdecu(32769u); putchar('\n');
  putdecu(32770u); putchar('\n');
  putdecu(65533u); putchar('\n');
  putdecu(65534u); putchar('\n');
  printf("%u\n", 65535u);

  return 0;
}

void Switch(void)
{
  switch (1) { default: }
  switch (1) { case 0: }
  switch (1) { case 1: }
  switch (1) { { int i; } }
  switch (1)
  {
  puts("never printed");
  case 0: puts("0"); break;
  case 1: puts("1"); break;
  case 2: puts("2"); break;
  default: puts("default"); break;
  }
  switch (2)
  {
  case 2: puts("2"); break;
  }
  switch (1)
  {
  default: puts("default"); break;
  }
  switch (1)
  {
  default: puts("default"); break;
  case 0: puts("0"); break;
  }
  switch (1)
  {
  case 0: puts("0"); break;
  default: puts("default"); break;
  }
  switch (3)
  {
  case 2: puts("2 & fallthru");
  case 3: puts("3 & fallthru");
  case 4: puts("4 & fallthru");
  default: puts("default & fallthru");
  }
  switch (5)
  {
  default: puts("default & fallthru");
  case 4: puts("4 & fallthru");
  case 3: puts("3 & fallthru");
  case 2: puts("2 & fallthru");
  }
  int i;
  for (i = 1; i <= 5; i++)
    switch (i)
    {
    case 3: continue;
    default: printf("%d\n", i); break;
    }
  return;
}
