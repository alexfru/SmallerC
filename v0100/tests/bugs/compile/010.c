int main(void)
{
  // We don't validate all redefinitions and
  // the last definition obscures previous ones.
  // Should not compile.
  int a = 0, a = 0;
  return a;
}
