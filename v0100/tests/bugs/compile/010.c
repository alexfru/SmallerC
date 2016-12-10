// We don't validate all redefinitions and
// the last definition obscures previous ones.
// Should not compile.
struct S { int a, a; };

int main(void)
{
  return 0;
}
