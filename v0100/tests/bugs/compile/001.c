// "Comma-expression" isn't a constant expression.
// The constant expression is defined as a conditional expression.
// Should not compile.
int a = (1, 0);

int main(void)
{
  return a;
}
