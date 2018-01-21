// Composite types aren't fully supported.
// Should compile.
extern int a[];
extern int a[10];
extern int a[];

int main();
int main(int argc, char* argv[])
{
  return 0;
}
int main(); // doesn't compile
