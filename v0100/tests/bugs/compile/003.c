typedef struct { int dummy; } T;
T a, b;
T f(void) { return a; }

int main(void)
{
  // Functions don't return lvalues.
  // But our structures are always lvalues.
  // Should not compile.
  f() = b;
  return 0;
}
