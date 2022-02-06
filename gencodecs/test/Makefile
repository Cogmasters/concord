TOP = ../..
CC ?= gcc

CORE_DIR     := $(TOP)/core
THIRDP_DIR   := $(TOP)/core/third-party
COGUTILS_DIR := $(TOP)/cog-utils
OBJDIR       := $(TOP)/obj/core

OBJS      := $(OBJDIR)/jsmn-find.o $(OBJDIR)/json-build.o
EXES      := test
TEMPLATES := db.test.h

CFLAGS += -Wall -Wextra -Wpedantic -g \
          -I. -I.. -I$(CORE_DIR) -I$(THIRDP_DIR) -I$(COGUTILS_DIR)

all: $(TEMPLATES) $(EXES)

$(EXES): %: %.c $(OBJS)
	$(CC) $(CFLAGS) $(XFLAGS) -o $@ $^
$(TEMPLATES): db.%: %
	cpp $(CFLAGS) -nostdinc -CC -P $< | clang-format-10 > $@

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	$(MAKE) -C $(TOP)

clean:
	rm -rf $(EXES) db.*.h

.PHONY : all clean


