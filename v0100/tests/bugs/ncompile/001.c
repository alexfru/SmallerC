// We don't support declarations of new tagged types in sizeof.
// Should compile.
int a = sizeof(struct S { int dummy; });
struct S s;

int main(void)
{
  return 0;
}
