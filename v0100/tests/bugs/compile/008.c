// Function-definition should not be part of declaration.
// Some compilers allow this, including ours.
// Should not compile.
int one = 1, fzero(void) { return 0; }

int main(void)
{
  return 0;
}
