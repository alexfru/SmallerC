#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

void
exits(const char *s)
{
	if (s) {
		fprintf(stderr, s);
		exit(EXIT_FAILURE);
	}
	exit(0);
}

void
sysfatal(const char *s, ...)
{
	va_list vl;
	va_start(vl, s);
	vfprintf(stderr, s, vl);
	va_end(vl);
	exit(EXIT_FAILURE);
}

void
errMem(void)
{
	sysfatal("Out of memory\n");
}

int
chartorune(unsigned *rune, char *str)
{
	/* This breaks UTF8. TBD!!! fix it or drop UTF8 altogether. */
	*rune = (unsigned char)*str;
	return 1;
}

/* Avoid strdup() as it may not exist or we may redefine it. */
char *
mystrdup(const char *s)
{
	char *p = malloc(strlen(s) + 1);
	if (p)
		strcpy(p, s);
	return p;
}

/* Determines binary file size portably (when stat()/fstat() aren't available) */
long fsize(FILE* binaryStream)
{
  long ofs, ofs2;
  int result;

  if (fseek(binaryStream, 0, SEEK_SET) != 0 ||
      fgetc(binaryStream) == EOF)
    return 0;

  ofs = 1;

  while ((result = fseek(binaryStream, ofs, SEEK_SET)) == 0 &&
         (result = (fgetc(binaryStream) == EOF)) == 0 &&
         ofs <= LONG_MAX / 4 + 1)
    ofs *= 2;

  /* If the last seek failed, back up to the last successfully seekable offset */
  if (result != 0)
    ofs /= 2;

  for (ofs2 = ofs / 2; ofs2 != 0; ofs2 /= 2)
    if (fseek(binaryStream, ofs + ofs2, SEEK_SET) == 0 &&
        fgetc(binaryStream) != EOF)
      ofs += ofs2;

  /* Return -1 for files longer than LONG_MAX */
  if (ofs == LONG_MAX)
    return -1;

  return ofs + 1;
}

/*
 * Expands "@filename" in program arguments into arguments contained within file "filename".
 * This is a workaround for short DOS command lines limited to 126 characters.
 * Note, the expansion is NOT recursive.
 * TBD!!! parse the file the same way as the command line.
 */
void fatargs(int* pargc, char*** pargv)
{
  int i, j = 0;
  char** pp;
  int pcnt = *pargc;

  if (pcnt < 2)
    return;

  for (i = 1; i < pcnt; i++)
    if ((*pargv)[i][0] == '@')
      break;
  if (i >= pcnt)
    return;

  if ((pp = malloc(++pcnt * sizeof(char*))) == NULL) /* there's supposed to be one more NULL pointer argument */
  {
    errMem();
  }

  pp[j++] = (*pargv)[0]; /* skip program name */

  for (i = 1; i < *pargc; i++)
    if ((*pargv)[i][0] != '@')
    {
      pp[j++] = (*pargv)[i]; /* it's not an name of a file with arguments, treat it as an argument */
    }
    else
    {
      FILE* f;
      long fsz;
      if (!(f = fopen((*pargv)[i] + 1, "rb")))
      {
        pp[j++] = (*pargv)[i]; /* there's no file by this name, treat it as an argument */
        continue;
      }
      if ((fsz = fsize(f)) < 0)
      {
        fclose(f);
        errMem();
      }
      if (fsz > 0)
      {
        size_t sz;
        char* buf;
        if ((sz = fsz) == (unsigned long)fsz &&
            sz + 1 > sz &&
            (buf = malloc(sz + 1)) != NULL)
        {
          static const char* const sep = "\f\n\r\t\v ";
          char* p;
          memset(buf, '\0', sz + 1);
          fseek(f, 0, SEEK_SET);
          buf[fread(buf, 1, sz, f)] = '\0';
          p = strtok(buf, sep);
          pcnt--; /* don't count the file name as an argument, count only what's inside */
          while (p)
          {
            size_t s;
            if (++pcnt == INT_MAX ||
                (s = (unsigned)pcnt * sizeof(char*)) / sizeof(char*) != (unsigned)pcnt ||
                (pp = realloc(pp, s)) == NULL)
            {
              fclose(f);
              errMem();
            }
            pp[j++] = p;
            p = strtok(NULL, sep);
          }
        }
        else
        {
          fclose(f);
          errMem();
        }
      }
      fclose(f);
    }

  pp[j] = NULL; /* there's supposed to be one more NULL pointer argument */
  *pargc = j;
  *pargv = pp;
}
