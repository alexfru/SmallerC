srcdir != readlink -f $(.PARSEDIR)/$(.PARSEFILE) | sed 's@[^/]*$$@v0100@'
.PATH: $(srcdir) $(srcdir)/srclib
PATH := $(.CURDIR):$(PATH)
.export PATH
.include "$(srcdir)/../common.mk"
