// Strips the leading "MZ" sequence off an .EXE.
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
  FILE *fin = NULL, *fout = NULL;
  int c1, c2;
  int res = EXIT_FAILURE;

  if (argc != 3)
  {
    printf("Strips the leading \"MZ\" sequence off an .EXE.\n"
           "Usage:\n  demz <input.exe> <output.exe>\n");
    goto lend;
  }

  if ((fin = fopen(argv[1], "rb")) == NULL)
  {
    printf("Can't open file '%s'!\n", argv[1]);
    goto lend;
  }

  c1 = fgetc(fin);
  c2 = fgetc(fin);
  if (c1 != 'M' || c2 != 'Z')
  {
    printf("'%s' is not an MZ .EXE!\n", argv[1]);
    goto lend;
  }

  if ((fout = fopen(argv[2], "wb")) == NULL)
  {
    printf("Can't create file '%s'!\n", argv[2]);
    goto lend;
  }

  while ((c1 = fgetc(fin)) != EOF)
    fputc(c1, fout);

  if (ferror(fin))
  {
    printf("Can't read file '%s'!\n", argv[1]);
    goto lend;
  }

  if (ferror(fout))
  {
    printf("Can't write file '%s'!\n", argv[2]);
    goto lend;
  }

  res = 0;

lend:

  if (fin != NULL)
  {
    fclose(fin);
  }

  if (fout != NULL)
  {
    if (fclose(fout))
    {
      printf("Can't write file '%s'!\n", argv[2]);
      res = EXIT_FAILURE;
    }
    if (res)
    {
      remove(argv[2]);
    }
  }

  return res;
}
