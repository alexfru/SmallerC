prefix = /usr/local
bindir = $(prefix)/bin
libdir = $(prefix)/smlrc/lib
incdir = $(prefix)/smlrc/include

CFLAGS = -pipe -Wall -O2
CFLAGS += -DHOST_LINUX -DPATH_PREFIX='"$(prefix)"'

CC = gcc

bins = smlrc smlrl smlrcc smlrpp n2f
libs = lcdh.a lcdu.a lcds.a lcw.a lcl.a lcdp.a
stub = dpstub.exe

all: $(libs) $(stub)

$(libs): $(bins)
$(stub): $(bins)

install: $(libs) $(stub)
	install -d $(DESTDIR)$(bindir) $(DESTDIR)$(libdir)
	install $(bins) $(DESTDIR)$(bindir)
	install -m644 $(libs) $(stub) $(DESTDIR)$(libdir)
	install -d $(DESTDIR)$(incdir)
	cp -L -R $(srcdir)/include/* $(DESTDIR)$(incdir)

clean:
	rm -f $(bins) $(libs) $(libs:.a=.op) $(stub)

.SUFFIXES: .op .txt

.op.a:
	./smlrcc -SI $(srcdir)/include -I $(srcdir)/srclib @$<

.txt.op:
	awk -v l=$(srcdir)/srclib/ '/[.](c|asm)$$/{$$0=l$$0}{print}' $< > $@

$(stub):
	./smlrcc -small $(srcdir)/srclib/dpstub.asm -o $@

smlrpp:
	$(CC) $(CFLAGS) -o $@ -DSTAND_ALONE -DUCPP_CONFIG \
	$(srcdir)/ucpp/arith.c \
	$(srcdir)/ucpp/assert.c \
	$(srcdir)/ucpp/cpp.c \
	$(srcdir)/ucpp/eval.c \
	$(srcdir)/ucpp/lexer.c \
	$(srcdir)/ucpp/macro.c \
	$(srcdir)/ucpp/mem.c \
	$(srcdir)/ucpp/nhash.c

all install clean: FORCE
FORCE:
