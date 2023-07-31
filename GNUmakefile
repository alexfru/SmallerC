srcdir := $(dir $(shell readlink \
	$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))))v0100
VPATH = $(srcdir) $(srcdir)/srclib
export PATH := $(CURDIR):$(PATH)
include $(srcdir)/../common.mk
