#include "u.h"
#include "libc.h"
#include "cpp.h"

Includelist	includelist[NINCLUDE];

char	*objname;

void
doinclude(Tokenrow *trp)
{
	char fname[256], iname[256], *p;
	Includelist *ip;
	int angled, len, i;
	FILE *f;

	trp->tp += 1;
	if (trp->tp>=trp->lp)
		goto syntax;
	if (trp->tp->type!=STRING && trp->tp->type!=LT) {
		len = trp->tp - trp->bp;
		expandrow(trp, "<include>", Notinmacro);
		trp->tp = trp->bp+len;
	}
	if (trp->tp->type==STRING) {
		len = trp->tp->len-2;
		if ((size_t)len > sizeof(fname) - 1)
			len = sizeof(fname) - 1;
		strncpy(fname, (char*)trp->tp->t+1, len);
		angled = 0;
	} else if (trp->tp->type==LT) {
		len = 0;
		trp->tp++;
		while (trp->tp->type!=GT) {
			if (trp->tp>trp->lp || len+trp->tp->len+2 >= sizeof(fname))
				goto syntax;
			strncpy(fname+len, (char*)trp->tp->t, trp->tp->len);
			len += trp->tp->len;
			trp->tp++;
		}
		angled = 1;
	} else
		goto syntax;
	trp->tp += 2;
	if (trp->tp < trp->lp || len==0)
		goto syntax;
	fname[len] = '\0';
	/* Note: using "rb" in order to determine the file size with fsize(). */
	if (fname[0]=='/') {
		f = fopen(fname, "rb");
		strcpy(iname, fname);
	} else for (f=NULL,i=NINCLUDE-1; i>=0; i--) {
		ip = &includelist[i];
		if (ip->file==NULL || ip->deleted || (angled && ip->always==0))
			continue;
		if (strlen(fname)+strlen(ip->file)+2 > sizeof(iname))
			continue;
		strcpy(iname, ip->file);
		strcat(iname, "/");
		strcat(iname, fname);
		if ((f = fopen(iname, "rb")) != NULL)
			break;
	}
	if (f == NULL) {
		strcpy(iname, cursource->filename);
		p = strrchr(iname, '/');
		if(p != NULL) {
			*p = '\0';
			strcat(iname, "/");
			strcat(iname, fname);
			f = fopen(iname, "rb");
		}
	}
	if ( Mflag>1 || (!angled&&Mflag==1) ) {
		fwrite(objname,1,strlen(objname),stdout);
		fwrite(iname,1,strlen(iname),stdout);
		fwrite("\n",1,1,stdout);
	}
	if (f != NULL) {
		if (++incdepth > 20)
			error(FATAL, "#include too deeply nested");
		setsource((char*)newstring((uchar*)iname, strlen(iname), 0), f, NULL);
		genline();
	} else {
		trp->tp = trp->bp+2;
		error(ERROR, "Could not find include file %r", trp);
	}
	return;
syntax:
	error(ERROR, "Syntax error in #include");
	return;
}

/*
 * Generate a line directive for cursource
 */
void
genline(void)
{
	static Token ta = { UNCLASS, 0, 0, 0, 0, NULL };
	static Tokenrow tr = { &ta, &ta, &ta+1, 1 };
	uchar *p;

	if(nolineinfo)
		return;

	ta.t = p = (uchar*)outp;
	strcpy((char*)p, "#line ");
	p += sizeof("#line ")-1;
	p = (uchar*)outnum((char*)p, cursource->line);
	*p++ = ' '; *p++ = '"';
	if (cursource->filename[0]!='/' && wd[0]) {
		strcpy((char*)p, wd);
		p += strlen(wd);
		*p++ = '/';
	}
	strcpy((char*)p, cursource->filename);
	p += strlen((char*)p);
	*p++ = '"'; *p++ = '\n';
	ta.len = (char*)p-outp;
	outp = (char*)p;
	tr.tp = tr.bp;
	puttokens(&tr);
}

void
setobjname(char *f)
{
	int n = strlen(f);
	objname = (char*)domalloc(n+5);
	strcpy(objname,f);
	if(objname[n-2]=='.'){
		strcpy(objname+n-1,"$O: ");
	}else{
		strcpy(objname+n,"$O: ");
	}
}
