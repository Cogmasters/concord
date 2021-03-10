# Build type and install directories:

build ?= release

prefix ?= /usr/local
bindir ?= $(prefix)/bin
incdir ?= $(prefix)/include
libdir ?= $(prefix)/lib

# Compiler flags for various configurations:

CFLAGS := -std=c99 -pedantic -Wall -Wextra -Wno-unused-parameter

ifeq "$(CC)" "clang"
  CFLAGS += -Wunreachable-code
endif

ifeq "$(shell uname)" "Linux"
  HAVE_READLINE := no
endif

ifeq "$(build)" "debug"
  CFLAGS += -g -O0
endif

ifeq "$(HAVE_READLINE)" "yes"
  CFLAGS += -DHAVE_READLINE
  LIBREADLINE += -lreadline
endif

CFLAGS += $(XCFLAGS)

# You shouldn't need to edit anything below here.

OUT := build/$(build)

SRCS := $(wildcard js*.c utf*.c regexp.c)
HDRS := $(wildcard js*.h mujs.h utf.h regexp.h)
OBJS := $(SRCS:%.c=$(OUT)/%.o)

default: shell
shell: $(OUT)/mujs $(OUT)/mujs-pp
static: $(OUT)/libmujs.a

astnames.h: jsparse.h
	grep -E '(AST|EXP|STM)_' jsparse.h | sed 's/^[^A-Z]*\(AST_\)*/"/;s/,.*/",/' | tr A-Z a-z > $@

opnames.h: jscompile.h
	grep -E 'OP_' jscompile.h | sed 's/^[^A-Z]*OP_/"/;s/,.*/",/' | tr A-Z a-z > $@

one.c: $(SRCS)
	ls $(SRCS) | awk '{print "#include \""$$1"\""}' > $@

jsdump.c: astnames.h opnames.h

$(OUT)/%.o: %.c $(HDRS)
	@ mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OUT)/libmujs.a: $(OBJS)
	@ mkdir -p $(dir $@)
	$(AR) cr $@ $^

$(OUT)/mujs: $(OUT)/main.o $(OUT)/libmujs.a
	@ mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) -o $@ $^ $(OUT)/libmujs.a $(LIBREADLINE)  -lm 

$(OUT)/mujs-pp: $(OUT)/pp.o $(OUT)/libmujs.a 
	@ mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) -o $@ $^ $(OUT)/libmujs.a -lm

.PHONY: $(OUT)/mujs.pc
$(OUT)/mujs.pc:
	@ echo Creating $@
	@ echo > $@ Name: mujs
	@ echo >> $@ Description: MuJS embeddable Javascript interpreter
	@ echo >> $@ Cflags: -I$(incdir)
	@ echo >> $@ Libs: -L$(libdir) -lmujs
	@ echo >> $@ Libs.private: -lm

watch:
	@ while ! inotifywait -q -e modify $(SRCS) $(HDRS) ; do time -p $(MAKE) ; done

install-common: $(OUT)/mujs $(OUT)/mujs.pc
	install -d $(DESTDIR)$(incdir)
	install -d $(DESTDIR)$(libdir)
	install -d $(DESTDIR)$(libdir)/pkgconfig
	install -d $(DESTDIR)$(bindir)
	install -m 644 mujs.h $(DESTDIR)$(incdir)
	install -m 644 $(OUT)/mujs.pc $(DESTDIR)$(libdir)/pkgconfig
	install -m 755 $(OUT)/mujs $(DESTDIR)$(bindir)

install-static: install-common $(OUT)/libmujs.a
	install -m 644 $(OUT)/libmujs.a $(DESTDIR)$(libdir)

install: install-static

uninstall:
	rm -f $(DESTDIR)$(bindir)/mujs
	rm -f $(DESTDIR)$(incdir)/mujs.h
	rm -f $(DESTDIR)$(libdir)/pkgconfig/mujs.pc
	rm -f $(DESTDIR)$(libdir)/libmujs.a

tags: $(SRCS) main.c $(HDRS)
	ctags $^

clean:
	rm -rf build

nuke: clean
	rm -f astnames.h opnames.h one.c

debug:
	$(MAKE) build=debug

sanitize:
	$(MAKE) build=sanitize

release:
	$(MAKE) build=release

.PHONY: default static shell clean nuke
.PHONY: install install-common install-static
.PHONY: debug sanitize release
