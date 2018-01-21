extern int a;
static int a; // shouldn't compile

void f(void);
static void f(void) {} // shouldn't compile

int main(void)
{
  return 0;
}
