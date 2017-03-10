void f(void)
{
}

void (*pf1)(void) = &f;
void (*pf2)(void) = f;
void (*pf3)(void) = *f; // doesn't compile
void (*pf4)(void) = **f; // doesn't compile

void ff(void f(void), void (*pf)(void))
{
  f();
  (f)();
  (*f)();
  pf();
  (pf)();
  (*pf)();
  (**f)(); // doesn't compile
  (***f)(); // doesn't compile
  (**pf)(); // doesn't compile
  (***pf)(); // doesn't compile
}

int main(void)
{
  f();
  (f)();
  (&f)();
  pf1();
  (pf1)();
  (*pf1)();
  (*f)(); // doesn't compile
  (**f)(); // doesn't compile
  (**pf1)(); // doesn't compile
  (***pf1)(); // doesn't compile
  return 0;
}
