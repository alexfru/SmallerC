/*
  How to compile for DOS (huge/.EXE, unreal/.EXE, 32-bit DPMI/.EXE):
    smlrcc -dosh libtest.c -o libtest.exe
    smlrcc -dosu libtest.c -o libtest.exe
    smlrcc -dosp libtest.c -o libtest.exe

  How to compile for Windows:
    smlrcc -win libtest.c -o libtest.exe

  How to compile for Linux:
    smlrcc -linux libtest.c -o libtest

  How to compile for MacOS:
    smlrcc -macos libtest.c -o libtest
*/

/*
 * Ad-hoc libc test program.
 * Nils M Holm, 1995, 2014
 * In the public domain
 *
 * The executable program *must* be called "libtest" or
 * some tests will fail.
 *
 * The program will delete the files "stdio.tmp" and
 * "stdio2.tmp" silently!
 */

/* Todo:
 * abort clearerr ctime difftime fdopen ferror
 * fgetpos fprintf freopen fscanf fsetpos
 * getchar getenv perror
 * scanf setbuf setvbuf sscanf strdup strerror
 * strtol system time varargs vformat
 * vfprintf vprintf vscan vsprintf
 */

#define TMPFILE		"stdio.tmp"
#define TMPFILE2	"stdio2.tmp"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <setjmp.h>
#include <errno.h>
#include <limits.h>
#include <unistd.h>

int	Verbose = 0;
int	Errors = 0;

void fail(char *name) {
	printf("%s failed\n", name);
	Errors++;
}

void pr(char *s) {
	if (Verbose) printf("%s\n", s);
}

void test_memfn(void) {
	char	*c1, *c2, *p;
	char	v1[128];
	int	i;

	pr("memcmp");
	c1 = "test01";
	c2 = "test03";
	if (memcmp(c1, c2, 5)) fail("memcmp-1");
	if (!memcmp(c1, c2, 6)) fail("memcmp-2");
	if (memcmp(c1, c2, 6) >= 0) fail("memcmp-3");
	if (memcmp(c2, c1, 6) <= 0) fail("memcmp-4");

	pr("memcpy");
	c1 = "abcdefghijklmnopqrstuvwxyz0123456789";
	memcpy(v1, c1, 36);
	if (memcmp(c1, v1, 36)) fail("memcpy-1");
//	memcpy(v1+18, v1, 36);
//	if (memcmp(c1, v1+18, 18)) fail("memcpy-2");
//	memcpy(v1, v1+18, 36);
//	if (memcmp(c1, v1, 18)) fail("memcpy-3");

	pr("memmove");
	memcpy(v1, c1, 36);
	memmove(v1+1, v1, 35);
	if (memcmp(v1+1, c1, 35) || *v1 != 'a') fail("memmove-1");
	memcpy(v1, c1, 36);
	memmove(v1, v1+1, 35);
	if (memcmp(v1, c1+1, 35) || v1[35] != '9') fail("memmove-2");

	pr("memset");
	for (i=0; i<128; i++) v1[i] = -1;
	memset(v1, 0, 64);
	if (v1[63]) fail("memset-1");
	if (!v1[64]) fail("memset-2");
	for (i=0; i<128; i++) v1[i] = -1;
	memset(v1, 123, 64);
	if (v1[63] != 123) fail("memset-3");
	if (v1[64] == 123) fail("memset-4");

	pr("memchr");
	c1 = "...............X1";
	p = memchr(c1, 'X', 16);
	if (!p || *p != 'X' || p[1] != '1') fail("memchr-1");
	if (memchr(c1, 'X', 15) != NULL) fail("memchr-2");
}

char *xstrchr(char *s, int c) {
	if (c == 0) return NULL;
	return strchr(s, c);
}

void test_chrfn(void) {
	char	*c1, *p1;
	int	c;
	char	*num, *low, *upc, *wsp, *pun;
	char	alpha[128], alnum[128], xnum[128];

	pr("strchr");
	c1 = "...............X1..............X2";
	p1 = strchr(c1, 'X');
	if (!p1 || *p1 != 'X' || p1[1] != '1') fail("strchr-1");
	if (strchr(c1, 'Z')) fail("strchr-2");

	pr("strrchr");
	p1 = strrchr(c1, 'X');
	if (!p1 || *p1 != 'X' || p1[1] != '2') fail("strrchr-1");
	if (strrchr(c1, 'Z')) fail("strchr-2");

	pr("is*");
	num = "0123456789";
	low = "abcdefghijklmnopqrstuvwxyz";
	upc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	wsp = "\t\v\f\n\r ";
	pun = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
	strcpy(alpha, low);
	strcat(alpha, upc);
	strcpy(alnum, alpha);
	strcat(alnum, num);
	strcpy(xnum, num);
	strcat(xnum, "abcdefABCDEF");
	for (c=0; c<128; c++) {
		if (isalnum(c) && !strchr(alnum, c)) fail("isalnum-1");
		if (isalpha(c) && !strchr(alpha, c)) fail("isalpha-1");
		if (iscntrl(c) && c > 31 && c < 127) fail("iscrntl-1");
		if (isdigit(c) && !strchr(num, c)) fail("isdigit-1");
		if (isgraph(c) && c < 33 && c > 126) fail("isgraph-1");
		if (islower(c) && !strchr(low, c)) fail("islower-1");
		if (isprint(c) && (c < 32 || c > 126)) fail("isprint-1");
		if (ispunct(c) && !strchr(pun, c)) fail("ispunct-1");
		if (isspace(c) && !strchr(wsp, c)) fail("isspace-1");
		if (isupper(c) && !strchr(upc, c)) fail("isupper-1");
		if (isxdigit(c) && !strchr(xnum, c)) fail("isxdigit-1");
		if (!isalnum(c) && xstrchr(alnum, c)) fail("isalnum-2");
		if (!isalpha(c) && xstrchr(alpha, c)) fail("isalpha-2");
		if (!iscntrl(c) && (c < 32 || c > 126)) fail("iscrntl-2");
		if (!isdigit(c) && xstrchr(num, c)) fail("isdigit-2");
		if (!isgraph(c) && c > 32 && c < 127) fail("isgraph-2");
		if (!islower(c) && xstrchr(low, c)) fail("islower-2");
		if (!isprint(c) && c > 31 && c < 127) fail("isprint-2");
		if (!ispunct(c) && xstrchr(pun, c)) fail("ispunct-2");
		if (!isspace(c) && xstrchr(wsp, c)) fail("isspace-2");
		if (!isupper(c) && xstrchr(upc, c)) fail("isupper-2");
		if (!isxdigit(c) && xstrchr(xnum, c)) fail("isxdigit-2");
		if (isupper(c) && !islower(tolower(c))) fail("tolower-1");
		if (islower(c) && tolower(toupper(c)) != c) fail("tolower-2");
		if (islower(c) && !isupper(toupper(c))) fail("toupper-1");
		if (isupper(c) && toupper(tolower(c)) != c) fail("toupper-2");
	}
}

void test_dmem(void) {
	char	*segp[64], *a;
	int	i, j, k;

	pr("malloc");
	for (k=0; k<20; k++) {
		if ((segp[k] = malloc(1024)) == NULL)
			break;
		for (j=0; j<1024; j++)
			segp[k][j] = k;
	}
	if (k < 20) fail("malloc-1");
	for (i=0; i<k; i++) {
		for (j=0; j<1024; j++)
			if (segp[i][j] != i)
				break;
		if (j != 1024)
			break;
	}
	if (i < k) fail("malloc-2");

	pr("free");
	for (j=0; j<k; j++)
		free(segp[j]);

	pr("calloc");
	if ((a = calloc(1, 1024)) == NULL) {
		fail("calloc-1");
	} else {
		for (i=0; i<1024; i++)
			if (a[i]) break;
		if (i < 1024)
			fail("calloc-2");
		free(a);
	}

	pr("realloc");
	if ((a = malloc(123)) == NULL) {
		fail("malloc-3");
	} else {
		for (i=0; i<123; i++)
			a[i] = i;
		if ((a = realloc(a, 257)) == NULL) {
			fail("realloc-1");
		} else {
			for (i=0; i<123; i++)
				if (a[i] != i)
					break;
			if (i < 123) fail("realloc-2");
			if ((a = realloc(a, 97)) == NULL) {
				fail("realloc-3");
			} else {
				for (i=0; i<97; i++)
					if (a[i] != i)
						break;
				if (i < 97) fail("realloc-4");
				free(a);
			}
		}
	}
}

int qcmp(const void *a, const void *b) {
	return (*(const int*)a < *(const int*)b) ? -1 :
		(*(const int*)a > *(const int*)b) ? 1 : 0;
}

void test_sort(void) {
	int	array[128];
	int	i, j;

	pr("qsort");
	for (i=0; i<128; i++)
		array[i] = 128-i;
	qsort(array, 128, sizeof(int), qcmp);
	for (j=i=0; i<128; i++) {
		if (array[i] < j) {
			fail("qsort-1");
			break;
		}
		j = array[i];
	}
}

int	test_array[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 27 };

void test_search(void) {
	int	key;
	int	*p;

	pr("bsearch");
	key = 13;
	if ((p = bsearch(&key, test_array, 10, sizeof(int), qcmp)) == NULL) {
		fail("bsearch-1");
	} else {
		if (*p != 13) fail("bsearch-2");
	}
	key = 15;
	if (bsearch(&key, test_array, 10, sizeof(int), qcmp) != NULL)
		fail("bsearch-3");
}

void test_mem(void) {
	test_memfn();
	test_chrfn();
	test_dmem();
	test_sort();
	test_search();
}

void test_str(void) {
	char	v1[128], *sep, *p;

	pr("strlen");
	if (strlen("\0") != 0) fail("strlen-1");
	if (strlen("0123456789abcdef") != 16) fail("strlen-2");

	pr("strcmp");
	if (strcmp("\0", "\0")) fail("strcmp-1");
	if (strcmp("abcdef", "abcdef")) fail("strcmp-2");
	if (strcmp("abcdef", "abcdefg") >= 0) fail("strcmp-3");
	if (strcmp("abcdefg", "abcdef") <= 0) fail("strcmp-4");
	if (strcmp("abcdef0", "abcdef3") >= 0) fail("strcmp-5");

	pr("strcpy");
	strcpy(v1, "0123456789ABCDEF");
	if (strcmp(v1, "0123456789ABCDEF")) fail("strcpy-1");
	strcpy(v1, "ABCDEF");
	if (strcmp(v1, "ABCDEF")) fail("strcpy-2");
	if (v1[7] != '7') fail("strcpy-3");

	pr("strcat");
	strcpy(v1, "abcXXXXX"); v1[3] = 0;
	strcat(v1, "DEF");
	if (strcmp(v1, "abcDEF")) fail("strcat-1");
	if (v1[7] != 'X') fail("strcat-2");

	pr("strncmp");
	if (strncmp("abcdef", "abcdef", 6)) fail("strncmp-1");
	if (strncmp("abcdxx", "abcdyy", 4)) fail("strncmp-2");
	if (strncmp("abcdx0", "abcdy9", 5) >= 0) fail("strncmp-3");
	if (strncmp("abcdy0", "abcdx9", 5) <= 0) fail("strncmp-4");
	if (strncmp("abcdef", "abcdef", 10)) fail("strncmp-5");
	if (strncmp("abcdefg", "abcdef", 7) <= 0) fail("strncmp-6");
	if (strncmp("abcdef", "abcdefg", 7) >= 0) fail("strncmp-7");
	if (strncmp("abcdefg", "abcdef", 10) <= 0) fail("strncmp-8");
	if (strncmp("abcdef", "abcdefg", 10) >= 0) fail("strncmp-9");

	pr("strncpy");
	strcpy(v1, "0123456789");
	strncpy(v1, "abcdef", 6);
	if (strcmp(v1, "abcdef6789")) fail("strncpy-1");
	strcpy(v1, "0123456789");
	strncpy(v1, "0123", 5);
	if (memcmp(v1, "0123\00056789", 10)) fail("strncpy-2");
	strncpy(v1, "0123", 10);
	if (memcmp(v1, "0123\0\0\0\0\0\0", 10)) fail("strncpy-3");

	pr("strncat");
	strcpy(v1, "012345");
	strncat(v1, "6789", 5);
	if (strcmp(v1, "0123456789")) fail("strncat-1");
	strncat(v1, "abcdef0000", 6);
	if (strcmp(v1, "0123456789abcdef")) fail("strncat-2");

	pr("strspn");
	if (strspn("abcdefg", "abc") != 3) fail("strspn-1");
	if (strspn("abcabcabcdefg", "abc") != 9) fail("strspn-2");
	if (strspn("abcdefg", "") != 0) fail("strspn-3");

	pr("strcspn");
	if (strcspn("abcdefg", "def") != 3) fail("strcspn-1");
	if (strcspn("abcabcabcdefg", "def") != 9) fail("strcspn-2");
	if (strcspn("abcdefg", "") != 7) fail("strcspn-2");
	if (strcspn("abcdefg", "xyz") != 7) fail("strcspn-3");

	pr("strpbrk");
	strcpy(v1, "abcdef");
	if (strpbrk(v1, "def") != v1 + 3) fail("strpbrk-1");
	strcpy(v1, "abcabcabcdef");
	if (strpbrk(v1, "def") != v1 + 9) fail("strpbrk-2");
	if (strpbrk("abcdef", "") != NULL) fail("strpbrk-2");
	if (strpbrk("abcdef", "xyz") != NULL) fail("strpbrk-3");

	pr("strtok");
	sep = "+-*";
	strcpy(v1, "foo++bar---baz*goo");
	if (!(p = strtok(v1, sep)) || strcmp(p, "foo")) fail("strtok-1");
	if (!(p = strtok(NULL, sep)) || strcmp(p, "bar")) fail("strtok-2");
	if (!(p = strtok(NULL, sep)) || strcmp(p, "baz")) fail("strtok-3");
	if (!(p = strtok(NULL, sep)) || strcmp(p, "goo")) fail("strtok-4");
	if (strtok(NULL, sep) != NULL) fail("strtok-5");
	if (strtok(NULL, sep) != NULL) fail("strtok-6");
}

void spfn_test(char *id, char *fmt, int v, char *res) {
	char	buf[256];

	sprintf(buf, fmt, v);
	if (strcmp(buf, res)) {
		strcpy(buf, "sprintf(");
		strcat(buf, fmt);
		strcat(buf, ")-");
		strcat(buf, id);
		fail(buf);
	}
}

void spfs_test(char *id, char *fmt, char *v, char *res) {
	char	buf[256];

	sprintf(buf, fmt, v);
	if (strcmp(buf, res)) {
		strcpy(buf, "sprintf(");
		strcat(buf, fmt);
		strcat(buf, ")-");
		strcat(buf, id);
		fail(buf);
	}
}

void test_sprintf(void) {
	pr("sprintf");
	spfn_test("1", "%d", 12345, "12345");
	spfn_test("2", "%d", -12345, "-12345");
	spfn_test("3", "%+d", 12345, "+12345");
	spfn_test("4", "%+d", -12345, "-12345");
	spfn_test("5", "%10d", 12345, "     12345");
	spfn_test("6", "%10d", -12345, "    -12345");
	spfn_test("7", "%+10d", 12345, "    +12345");
	spfn_test("8", "%+10d", -12345, "    -12345");
	spfn_test("9", "%-10d", 12345, "12345     ");
	spfn_test("10", "%-10d", -12345, "-12345    ");
	spfn_test("11", "%-+10d", 12345, "+12345    ");
	spfn_test("12", "%-+10d", -12345, "-12345    ");
	spfn_test("13", "%+-10d", 12345, "+12345    ");
	spfn_test("14", "%+-10d", -12345, "-12345    ");
	spfn_test("15", "% 10d", 12345, "     12345");
	spfn_test("16", "% 10d", -12345, "    -12345");
	spfn_test("17", "%010d", 12345, "0000012345");
	spfn_test("18", "%010d", -12345, "-000012345");
	spfn_test("19", "%x", 0x2def, "2def");
	spfn_test("20", "%X", 0x2def, "2DEF");
	spfn_test("21", "%#x", 0x2def, "0x2def");
	spfn_test("22", "%#X", 0x2def, "0X2DEF");
//	spfn_test("23", "%x", -0x2def, "-2def");
//	spfn_test("24", "%#x", -0x2def, "-0x2def");
	spfn_test("25", "%+#X", 0x2def, "0X2DEF");
	spfn_test("26", "%#+X", 0x2def, "0X2DEF");
	spfn_test("27", "%#+X", 0x2def, "0X2DEF");
	spfn_test("28", "%10X", 0x2def, "      2DEF");
	spfn_test("29", "%010X", 0x2def, "0000002DEF");
	spfn_test("30", "%-10X", 0x2def, "2DEF      ");
	spfn_test("31", "%#10X", 0x2def, "    0X2DEF");
	spfn_test("32", "%#010X", 0x2def, "0X00002DEF");
	spfn_test("33", "%#-10X", 0x2def, "0X2DEF    ");
//	spfn_test("34", "%10X", -0x2def, "     -2DEF");
//	spfn_test("35", "%010X", -0x2def, "-000002DEF");
//	spfn_test("36", "%-10X", -0x2def, "-2DEF     ");
//	spfn_test("37", "%#10X", -0x2def, "   -0X2DEF");
//	spfn_test("38", "%#010X", -0x2def, "-0X0002DEF");
//	spfn_test("39", "%#-10X", -0x2def, "-0X2DEF   ");
	spfn_test("40", "%o", 0417, "417");
//	spfn_test("41", "%o", -0417, "-417");
	spfn_test("42", "%#o", 0417, "0417");
//	spfn_test("43", "%#o", -0417, "-0417");
	spfn_test("44", "%#+o", 0417, "0417");
	spfn_test("45", "%+#o", 0417, "0417");
	spfn_test("46", "%#10o", 0417, "      0417");
	spfn_test("47", "%#-10o", 0417, "0417      ");
	spfn_test("48", "%#010o", 0417, "0000000417");
//	spfn_test("49", "%#10o", -0417, "     -0417");
//	spfn_test("50", "%#-10o", -0417, "-0417     ");
//	spfn_test("51", "%#010o", -0417, "-000000417");
	spfn_test("52", "%d", 0, "0");
	spfn_test("53", "%o", 0, "0");
	spfn_test("54", "%x", 0, "0");
	spfn_test("55", "%c", 'a', "a");
	spfn_test("56", "%10c", 'a', "         a");
	spfn_test("57", "%-10c", 'a', "a         ");
	spfs_test("58", "%s", "foo", "foo");
	spfs_test("59", "%10s", "foo", "       foo");
	spfs_test("60", "%-10s", "foo", "foo       ");
	spfn_test("61", "%1d", 12345, "12345");
	spfn_test("62", "%-1d", 12345, "12345");
	spfn_test("61", "%#1x", 0xabc, "0xabc");
//	spfn_test("62", "%#-1x", -0xabc, "-0xabc");
	spfs_test("63", "%1s", "foo", "foo");
	spfs_test("64", "%-1s", "foo", "foo");
}

void test_math(void) {
	#define MAX		100
	int	i, j, k;
	int	rns[MAX];

	pr("atoi");
	i = 12345;
	if (i != atoi("   12345")) fail("atoi-1");
	if (i != atoi("\t+12345")) fail("atoi-2");
	i = -i;
	if (i != atoi("-12345")) fail("atoi-3");
	if (i != atoi("  -12345")) fail("atoi-4");
	if (i != atoi("\t-12345")) fail("atoi-5");

	pr("abs");
	if (abs(0) != 0) fail("abs-1");
	if (abs(123) != 123) fail("abs-2");
	if (abs(-456) != 456) fail("abs-3");
//	if (abs(INT_MIN) != INT_MIN) fail("abs-4"); /* man page says so */

	for (i=0; i<MAX; i++) {
		k = rand();
		for (j=0; j<i; j++)
			if (rns[j] == k) {
				fail("rand-1");
				break;
			}
		rns[i] = k;
		if ((unsigned) k > (unsigned) RAND_MAX) fail("rand-2");
	}
}

jmp_buf	here;
int	count;

void jump(void) {
	longjmp(here, 1);
	fail("longjmp-1");
}

void test_ljmp(void) {
	pr("setjmp/longjmp");
	count = 0;
	if (setjmp(here)) {
		if (count != 1) fail("setjmp-1");
		return;
	}
	count++;
	jump();
}

void test_proc(void) {
	test_ljmp();
}

void test_sio1(void) {
	FILE	*f;
	char	buf[80];
	int	i, j;
	int	fd;

	pr("fopen");
	if ((f = fopen(TMPFILE, "w+")) == NULL) {
		fail("fopen-1");
	}
	else {
		pr("feof");
		fgetc(f);
		if (!feof(f)) fail("feof-1");
		fclose(f);
	}
	if ((f = fopen(TMPFILE, "w")) == NULL) {
		fail("fopen-2");
	}
	else {
		pr("fputs");
		if (fputs("1111111111\n", f) == EOF) fail("fputs-1");
		if (fputs("2222222222\n", f) == EOF) fail("fputs-2");
		if (fputs("3333333333\n", f) == EOF) fail("fputs-3");
		if (fputs("4444444444\n", f) == EOF) fail("fputs-4");
		if (fputs("5555555555\n", f) == EOF) fail("fputs-5");
		fd = fileno(f);
		pr("fclose");
		if (fclose(f)) fail("fclose-1");
		if (close(fd) == 0) fail("fclose-2");

		if ((f = fopen(TMPFILE, "r")) == NULL) {
			fail("fopen-3");
		}
		else {
			pr("fgets");
			fgets(buf, 80, f);
			i = '1';
			while (!feof(f)) {
				for (j=0; j<10; j++) {
					if (buf[j] != i) {
						fail("fgets-1");
						break;
					}
				}
				i++;
				fgets(buf, 80, f);
			}
			fd = fileno(f);
			if (fclose(f)) fail("fclose-1");
			if (close(fd) == 0) fail("fclose-2");
		}
	}
	unlink(TMPFILE);
}

void test_sio2(void) {
	FILE	*f;
	int	i;

	pr("fileno");
	if (fileno(stdin) != 0) fail("fileno-1");
	if (fileno(stdout) != 1) fail("fileno-2");
	if (fileno(stderr) != 2) fail("fileno-3");

	if ((f = fopen(TMPFILE, "w+")) == NULL) {
		fail("fopen-4");
		return;
	}

	pr("fputc");
	for (i='A'; i<='Z'; i++)
		if (fputc(i, f) != i)
			fail("fputc-1");

	pr("fflush");
	if (fflush(f) < 0) fail("fflush-1");
	if (lseek(fileno(f), 0, SEEK_END) != 26) fail("fflush-2");

	pr("rewind");
	rewind(f);
	if (lseek(fileno(f), 0, SEEK_CUR) != 0)
		fail("rewind-1");

	pr("fgets");
	for (i='A'; i<='Z'; i++) {
		if (fgetc(f) != i) {
			fail("fgetc-1");
			break;
		}
	}
	if (fgetc(f) != EOF) fail("fgetc-2");
	
	pr("ungetc");
	clearerr(f);

	rewind(f);
	if (fgetc(f) != 'A') fail("ungetc-0");
	if (ungetc('X', f) != 'X') fail("ungetc-1");
	if (fgetc(f) != 'X') fail("ungetc-2");
	if (fgetc(f) != 'B') fail("ungetc-3");
	if (ungetc('X', f) != 'X') fail("ungetc-4");
	if (fgetc(f) != 'X') fail("ungetc-5");

	if (fclose(f)) fail("fclose-5");

	unlink(TMPFILE);
}

void test_sio3(void) {
	FILE	*f;
	static unsigned char	buf[1024];
	int	i, j;

	if ((f = fopen(TMPFILE, "w+")) == NULL) {
		fail("fopen-5");
		return;
	}
	pr("fwrite");
	for (i=31; i<=527; i += 31) {
		memset(buf, i, i);
		if (fwrite(buf, 1, i, f) != i)
			fail("fwrite-1");
	}
	rewind(f);
	pr("fread");
	for (i=31; i<=527; i += 31) {
		memset(buf, 0, i);
		if (fread(buf, 1, i, f) != i)
			fail("fread-1");
		for (j=0; j<i; j++) {
			if (buf[j] != (i & 0xFF))
				break;
		}
		if (j < i) {
			fail("fread-2");
			break;
		}
	}

	if (fclose(f)) fail("fclose-5");

	if ((f = fopen(TMPFILE, "w+")) == NULL) {
		fail("fopen-5");
		return;
	}
	for (i=0; i<1024; i++)
		buf[i] = '5';
	for (i=0; i<16; i++) {
		if (fwrite(buf, 1, 1024, f) != 1024) {
			fail("fwrite-2");
			break;
		}
	}
	rewind(f);
	for (i=0; i<16; i++) {
		if (fread(buf, 1, 1024, f) != 1024) {
			fail("fread-3");
			break;
		}
	}
	if (fgetc(f) != EOF) fail("fread-4");

	clearerr(f);
	rewind(f);
	pr("fseek/ftell");
	if (fseek(f, 0, SEEK_END)) fail("fseek-1");
	if (ftell(f) != 16384) fail("ftell-1");
	if (fseek(f, 8100, SEEK_SET)) fail("fseek-2");
	if (ftell(f) != 8100) fail("fseek-3");
	if (fseek(f, 1900, SEEK_CUR)) fail("fseek-4");
	if (ftell(f) != 10000) fail("fseek-5");

	fclose(f);
	unlink(TMPFILE);
}

void test_stdout(void) {
	int	i;

	puts("0---|----1----|----2----|----3----|----4----|----5");
	for (i=0; i<50; i++) putc('A', stdout);
	puts("");
	for (i=0; i<50; i++) putchar('B');
	puts("");
	printf("CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC\n");
	printf("|%48s|\n", "DDDDDDDDDDDDDDDDDDDDDDDD");
	printf("|%-48s|\n", "EEEEEEEEEEEEEEEEEEEEEEEE");
	for (i=0; i<5; i++)
		printf("%c%c%c%c%c%c%c%c%c%c",
		'1', '2', '3', '4', '5', '6', '7', '8', '9', '0' );
	puts("");
	printf("%50d\n", -12345);
	printf("%-49d|\n", -12345);
	printf("%050d\n", 12345);
	printf("0x%x %15s%d%16s 0%o\n", 0x7BCD, "", 0x7BCD, "", 0x7BCD);
	for (i=0; i<5; i++) printf("%%%%%%%%%%%%%%%%%%%%");
	puts("");
	puts("0---|----1----|----2----|----3----|----4----|----5");
}

void test_sio4(void) {
	FILE	*t, *f;
	char	s1[80], s2[80];
	int	err, lno;

	err = lno = 0;
	pr("stdout");
#if !defined(_LINUX) && !defined(_MACOS)
	system(".\\libtest.exe test-stdout >stdio.tmp");
#else
	system("./libtest test-stdout >stdio.tmp");
#endif
	if ((f = fopen("stdio.ok", "r")) == NULL) {
		fputs("missing file: stdio.ok\n", stdout);
		Errors++;
	}
	else {
		if ((t = fopen(TMPFILE, "r")) == NULL) {
			fputs("could not open test file: stdio.tmp\n",
				stdout);
			fputs("system() failed?\n", stdout);
		}
		else {
			fgets(s1, 80, t);
			for (;;) {
				++lno;
				fgets(s2, 80, f);
				if (feof(t)) break;
				if (feof(f)) break;
				if (memcmp(s1, s2, 52)) ++err;
				fgets(s1, 80, t);
			}
			if (!feof(f) || !feof(t)) {
				puts("test files have different sizes");
				++err;
			}
			fclose(t);
		}
		fclose(f);
	}
	if (!err) unlink(TMPFILE);
	if (err) fail("misc-stdout");
}

void test_stdio(void) {
	test_sio1();
	test_sio2();
	test_sio3();
	test_sio4();
}

void test_file(void) {
	FILE	*f;
	char	buf[1024];
	char	tn1[L_tmpnam], tn2[L_tmpnam];

	if ((f = fopen(TMPFILE, "w")) != NULL) fclose(f);
	pr("remove");
	if (remove(TMPFILE) != 0) fail("remove-1");
	if (remove(TMPFILE) == 0) fail("remove-2");

	pr("rename");
	if (rename(TMPFILE, TMPFILE2) == 0) fail("rename-1");
	if ((f = fopen(TMPFILE, "w")) != NULL) fclose(f);
	if (rename(TMPFILE, TMPFILE2) != 0) fail("rename-2");
	if (rename(TMPFILE, TMPFILE2) == 0) fail("rename-3");
	remove(TMPFILE2);

	pr("tmpfile");
	if ((f = tmpfile()) == NULL) {
		fail("tmpfile-1");
	} else {
		memset(buf, 0x55, 1024);
		if (fwrite(buf, 1, 1024, f) != 1024) fail("tmpfile-2");
		rewind(f);
		if (fread(buf, 1, 1024, f) != 1024) fail("tmpfile-3");
	}

	pr("tmpnam");
	if (tmpnam(tn1) == NULL) {
		fail("tmpnam-1");
	} else {
		if ((f = fopen(tn1, "w")) != NULL) fclose(f);
		if (tmpnam(tn2) == NULL) {
			fail("tmpnam-2");
		} else {
			if (!strcmp(tn1, tn2)) fail("tmpnam-3");
		}
		remove(tn1);
	}
}

void doexit(void) {
	FILE	*f;
	if ((f = fopen(TMPFILE, "w")) != NULL) fclose(f);
}

void test_atexit(void) {
	pr("atexit");
	atexit(doexit);
	exit(0);
}

void test_exit(void) {
	FILE	*f;
	pr("exit");
	remove(TMPFILE);
#if !defined(_LINUX) && !defined(_MACOS)
	system(".\\libtest.exe test-atexit");
#else
	system("./libtest test-atexit");
#endif
	if ((f = fopen(TMPFILE, "r")) == NULL || fclose(f) == EOF)
		fail("atexit-1");
	remove(TMPFILE);
	exit(Errors? EXIT_FAILURE: 0);
	fail("exit-1");
}

int main(int argc, char **argv) {
	if (argc > 1) {
		if (!strcmp(argv[1], "v")) {
			Verbose = 1;
		}
		else if (!strcmp(argv[1], "test-stdout")) {
			test_stdout();
			return EXIT_SUCCESS;
		}
		if (!strcmp(argv[1], "test-atexit")) {
			test_atexit();
			return EXIT_SUCCESS;
		}
	}
	test_mem();
	test_str();
	test_sprintf();
	test_math();
	test_proc();
	test_stdio();
	test_file();
	test_exit();
	return EXIT_FAILURE;
}
