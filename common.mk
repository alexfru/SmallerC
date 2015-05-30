prefix = /usr/local
bindir = $(prefix)/bin
libdir = $(prefix)/smlrc/lib
incdir = $(prefix)/smlrc/include

CFLAGS = -pipe -Wall -O2
CFLAGS += -DHOST_LINUX -DPATH_PREFIX='"$(prefix)"'

CC = gcc -std=c99

bins = smlrc smlrl smlrcc
libs = lcdh.a lcds.a lcw.a lcl.a

all: $(libs)

$(libs): $(bins)

install: $(libs)
	install -d $(DESTDIR)$(bindir) $(DESTDIR)$(libdir)
	install $(bins) $(DESTDIR)$(bindir)
	install -m644 $(libs) $(DESTDIR)$(libdir)
	install -d $(DESTDIR)$(incdir)
	cp -L -R $(srcdir)/include/* $(DESTDIR)$(incdir)

clean:
	rm -f $(bins) $(libs) $(libs:.a=.op)

.SUFFIXES: .op .txt

.op.a:
	./smlrcc -SI $(srcdir)/include -I $(srcdir)/srclib @$<

.txt.op:
	awk -vl=$(srcdir)/srclib/ '/[.](c|asm)$$/{$$0=l$$0}{print}' $< > $@

all install clean: FORCE
FORCE:
