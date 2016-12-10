// We don't support declarations of new tagged types in casts.
// Should compile.
void* p = (struct S { char dummy; }*)0;
struct S s;

int main(void)
{
  return 0;
}
