/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#ifndef __ISTDIO_H
#define __ISTDIO_H

#include <stdio.h>

struct __stream
{
  struct __stream *prev, *next;

  int fd;
  int flags; // std/terminal, temp, text/bin, EOF, err, appended, buffering mode, etc

  unsigned char* buf; // internal data buffer
  unsigned char* ptr; // pointer within the buffer
  size_t cnt; // how many bytes or byte placeholders are available at ptr
  size_t bufsz; // buffer size

  unsigned char c; // in-situ buffer if there's no other buffer

  char* name; // for temp files from tmpfile()
};

extern FILE __StreamsHead; // list head for all fopen()'d files

/*
#define _IOFBF    000001
#define _IONBF    000002
#define _IOLBF    000004
*/
#define _IORD     000010 // last was read (or read-only when there's no _IORW)
#define _IOWR     000020 // last was write (or write-only when there's no _IORW)
#define _IORWOK   000040 // read and write allowed
#define _IOBINARY 000100 // no end-of-line character translation ("\n" <-> "\r\n")
#define _IOAPPEND 000200 // append mode: all writes occur at file's end
#define _IOREMOVE 000400 // remove on close (for temporary files from tmpfile())
#define _IOTERM   001000 // terminal handle (e.g. stdin, stdout, stderr)
#define _IOUNGOT  002000 // ungetc() changed the read buffer
#define _IOEXTBUF 004000 // using externally-supplied buffer from set(v)buf(), which won't be freed on close
#define _IOEOF    010000 // end of file reached
#define _IOERR    020000 // read() or write() returned error
#define _IOSTRING 040000 // underlying file is actually a string for formatted I/O with (v)s(n)printf()

extern void (*__pFileCloser)(void);
void __FileCloser(void);

int __fillbuf(FILE*);
int __flushbuf(int, FILE*);
int __doprint(FILE*, char*, va_list);
int __doscan(FILE*, char*, va_list);
char* __tmpnam(char*, unsigned);

extern char* __EnvVar;

#endif
