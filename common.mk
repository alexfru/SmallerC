prefix = /usr/local
bindir = $(prefix)/bin
libdir = $(prefix)/smlrc/lib
incdir = $(prefix)/smlrc/include

CFLAGS ?= -pipe -Wall -O2
CPPFLAGS += -DPATH_PREFIX='"$(prefix)"'

CC ?= gcc

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	CPPFLAGS += -DHOST_MACOS
else
# If not MacOS, assume Linux.
	CPPFLAGS += -DHOST_LINUX
endif

bins = smlrc smlrl smlrcc smlrpp n2f
libs = lcdh.a lcdu.a lcds.a lcw.a lcl.a lcdp.a lcm.a
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
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ -DSTAND_ALONE -DUCPP_CONFIG \
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

# Serialization prevents build failures when concurrent invocations of
# smlrcc on .c and .asm files in $(srcdir)/srclib/ produce intermediate
# files such as .i, .asm, .o of non-unique names in that same source
# directory.
.NOTPARALLEL:
