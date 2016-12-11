typedef int F(int a, int b);
F add;

// The following function definition (both declaration and
// compound-statement) should not compile.
F add
{
  return a + b;
}

int main(void)
{
  return 0;
}
