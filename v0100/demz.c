// Strips the leading "MZ" sequence off an .EXE.
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
  FILE *fin = NULL, *fout = NULL;
  int c1, c2;
  if (argc != 3 ||
      (fin = fopen(argv[1], "rb")) == NULL ||
      (fout = fopen(argv[2], "wb")) == NULL)
    return EXIT_FAILURE;
  c1 = fgetc(fin);
  c2 = fgetc(fin);
  if (c1 != 'M' || c2 != 'Z')
  {
    printf("%s is not an MZ .EXE!\n", argv[1]);
    fclose(fin);
    fclose(fout);
    remove(argv[2]);
    return EXIT_FAILURE;
  }
  while ((c1 = fgetc(fin)) != EOF)
    fputc(c1, fout);
  fclose(fout);
  fclose(fin);
  return 0;
}
