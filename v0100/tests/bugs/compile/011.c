int main(void)
{
  {
    extern int v;
    void f(void);
  }
  {
    extern char* v; // shouldn't compile
    int f(int); // shouldn't compile
  }
  return 0;
}
