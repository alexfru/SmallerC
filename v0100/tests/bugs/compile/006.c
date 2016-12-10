// Enumeration types are incomplete unil the closing brace, }.
// But we treat all enums as ints at all times.
// Should not compile.
enum E { ESZ = sizeof(enum E) };

int main(void)
{
  return 0;
}
