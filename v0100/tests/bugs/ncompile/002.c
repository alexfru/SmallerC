// We don't support declarations of new tagged types in sizeof.
// Should compile.
int b = sizeof(enum E { E0 });
enum E e;

int main(void)
{
  return 0;
}
