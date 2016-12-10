char* p1;
struct { char dummy; }* p2;

int main(void)
{
  // Difference of pointers to incompatible types
  // (we only check the type's sizes, not the actual types).
  // Should not compile.
  return p1 - p2;
}
