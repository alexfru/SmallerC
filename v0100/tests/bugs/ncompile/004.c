// We don't support declarations of new tagged types in casts.
// Should compile.
int a = (enum E { E0 })0;
enum E e;

int main(void)
{
  return 0;
}
