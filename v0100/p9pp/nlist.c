#include <u.h>
#include <libc.h>
#include <stdio.h>
#include "cpp.h"

extern	int getopt(int, char **, char *);
extern	char	*optarg;
extern	int	optind;
int	verbose;
int	Mflag;
int	Cplusplus;
int	nolineinfo;
Nlist	*kwdefined;
char	wd[128];

#define	NLSIZE	128

Nlist	*nlist[NLSIZE];

struct	kwtab {
	char	*kw;
	int	val;
	int	flag;
} kwtab[] = {
	"if",		KIF,		ISKW,
	"ifdef",	KIFDEF,		ISKW,
	"ifndef",	KIFNDEF,	ISKW,
	"elif",		KELIF,		ISKW,
	"else",		KELSE,		ISKW,
	"endif",	KENDIF,		ISKW,
	"include",	KINCLUDE,	ISKW,
	"define",	KDEFINE,	ISKW,
	"undef",	KUNDEF,		ISKW,
	"line",		KLINE,		ISKW,
	"error",	KERROR,		ISKW,
	"warning",	KWARNING,	ISKW,		// extension to ANSI
	"pragma",	KPRAGMA,	ISKW,
	"eval",		KEVAL,		ISKW,
	"defined",	KDEFINED,	ISDEFINED+ISUNCHANGE,
	"__LINE__",	KLINENO,	ISMAC+ISUNCHANGE,
	"__FILE__",	KFILE,		ISMAC+ISUNCHANGE,
	"__DATE__",	KDATE,		ISMAC+ISUNCHANGE,
	"__TIME__",	KTIME,		ISMAC+ISUNCHANGE,
	"__STDC__",	KSTDC,		ISUNCHANGE,
	NULL
};

unsigned long	namebit[077+1];
Nlist 	*np;

void
setup(int argc, char **argv)
{
	struct kwtab *kp;
	Nlist *np;
	Token t;
	int fd, i;
	char *fp, *dp;
	Tokenrow tr;
	char *objtype;
	char *includeenv;
	int firstinclude;
	static char nbuf[40];
	static Token deftoken[1] = {{ NAME, 0, 0, 0, 7, (uchar*)"defined" }};
	static Tokenrow deftr = { deftoken, deftoken, deftoken+1, 1 };
	int debuginclude = 0;
	int nodot = 0;
	char xx[2] = { 0, 0};

	for (kp=kwtab; kp->kw; kp++) {
		t.t = (uchar*)kp->kw;
		t.len = strlen(kp->kw);
		np = lookup(&t, 1);
		np->flag = kp->flag;
		np->val = kp->val;
		if (np->val == KDEFINED) {
			kwdefined = np;
			np->val = NAME;
			np->vp = &deftr;
			np->ap = 0;
		}
	}
	/*
	 * For Plan 9, search /objtype/include, then /sys/include
	 * (Note that includelist is searched from high end to low)
	 */
	if ((objtype = getenv("objtype"))){
		snprintf(nbuf, sizeof nbuf, "/%s/include", objtype);
		includelist[1].file = nbuf;
		includelist[1].always = 1;
	} else {
		includelist[1].file = NULL;
		error(WARNING, "Unknown $objtype");
	}
	if (getwd(wd, sizeof(wd))==0)
		wd[0] = '\0';
	includelist[0].file = "/sys/include";
	includelist[0].always = 1;
	firstinclude = NINCLUDE-2;
	if ((includeenv=getenv("include")) != NULL) {
		char *cp;
		includeenv = strdup(includeenv);
		for (;firstinclude>0; firstinclude--) {
			cp = strtok(includeenv, " ");
			if (cp==NULL)
				break;
			includelist[firstinclude].file = cp;
			includelist[firstinclude].always = 1;
			includeenv = NULL;
		}
	}
	setsource("", -1, 0);
	ARGBEGIN {
		case 'N':
			for (i=0; i<NINCLUDE; i++)
				if (includelist[i].always==1)
					includelist[i].deleted = 1;
			break;
		case 'I':
			for (i=firstinclude; i>=0; i--) {
				if (includelist[i].file==NULL) {
					includelist[i].always = 1;
					includelist[i].file = ARGF();
					break;
				}
			}
			if (i<0)
				error(WARNING, "Too many -I directives");
			break;
		case 'D':
		case 'U':
			setsource("<cmdarg>", -1, ARGF());
			maketokenrow(3, &tr);
			gettokens(&tr, 1);
			doadefine(&tr, ARGC());
			unsetsource();
			break;
		case 'M':
			Mflag++;
			break;
		case 'V':
			verbose++;
			break;
		case '+':
			Cplusplus++;
			break;
		case 'i':
			debuginclude++;
			break;
		case 'P':
			nolineinfo++;
			break;
		case '.':
			nodot++;
			break;
		default:
			xx[0] = ARGC();
			error(FATAL, "Unknown argument '%s'", xx);
			break;
	} ARGEND
	dp = ".";
	fp = "<stdin>";
	fd = 0;
	if (argc > 2)
		error(FATAL, "Too many file arguments; see cpp(1)");
	if (argc > 0) {
		if ((fp = strrchr(argv[0], '/')) != NULL) {
			int len = fp - argv[0];
			dp = (char*)newstring((uchar*)argv[0], len+1, 0);
			dp[len] = '\0';
		}
		fp = (char*)newstring((uchar*)argv[0], strlen(argv[0]), 0);
		if ((fd = open(fp, 0)) < 0)
			error(FATAL, "Can't open input file %s", fp);
	}
	if (argc > 1) {
		int fdo = create(argv[1], 1, 0666);
		if (fdo<0)
			error(FATAL, "Can't open output file %s", argv[1]);
		dup(fdo, 1);
	}
	if (Mflag)
		setobjname(fp);
	includelist[NINCLUDE-1].always = 0;
	includelist[NINCLUDE-1].file = dp;
	if(nodot)
		includelist[NINCLUDE-1].deleted = 1;
	setsource(fp, fd, NULL);
	if (debuginclude) {
		for (i=0; i<NINCLUDE; i++)
			if (includelist[i].file && includelist[i].deleted==0)
				error(WARNING, "Include: %s", includelist[i].file);
	}
}

Nlist *
lookup(Token *tp, int install)
{
	unsigned int h;
	Nlist *np;
	uchar *cp, *cpe;

	h = 0;
	for (cp=tp->t, cpe=cp+tp->len; cp<cpe; )
		h += *cp++;
	h %= NLSIZE;
	np = nlist[h];
	while (np) {
		if (*tp->t==*np->name && tp->len==np->len 
		 && strncmp((char*)tp->t, (char*)np->name, tp->len)==0)
			return np;
		np = np->next;
	}
	if (install) {
		np = new(Nlist);
		np->val = 0;
		np->vp = NULL;
		np->ap = NULL;
		np->flag = 0;
		np->len = tp->len;
		np->name = newstring(tp->t, tp->len, 0);
		np->next = nlist[h];
		nlist[h] = np;
		quickset(tp->t[0], tp->len>1? tp->t[1]:0);
		return np;
	}
	return NULL;
}
