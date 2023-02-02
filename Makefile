PREFIX          ?= /usr/local
DESTINCLUDE_DIR  = $(PREFIX)/include/concord
DESTLIBDIR       = $(PREFIX)/lib

SRC_DIR       = src
INCLUDE_DIR   = include
LIBDIR        = lib
DOCS_DIR      = docs
GENCODECS_DIR = gencodecs
CORE_DIR      = core
EXAMPLES_DIR  = examples
TEST_DIR      = test

SOFLAGS     = -fPIC
DYFLAGS     = -fPIC 
DEBUG_FLAGS = -O0 -g

GIT_BRANCHES = master dev
GIT_TARGETS  = latest latest-dev

CFLAGS ?= -O2

all: static

static:
	@ CFLAGS="$(CFLAGS)" $(MAKE) -C $(CORE_DIR)
	@ $(MAKE) -C $(GENCODECS_DIR)
	@ CFLAGS="$(CFLAGS)" $(MAKE) -C $(SRC_DIR) $@
shared:
	@ CFLAGS="$(SOFLAGS) $(CFLAGS)" $(MAKE) -C $(CORE_DIR)
	@ CFLAGS="$(SOFLAGS)" $(MAKE) -C $(GENCODECS_DIR)
	@ CFLAGS="$(CFLAGS)" $(MAKE) -C $(SRC_DIR) $@
shared_osx:
	@ CFLAGS="$(DYFLAGS) $(CFLAGS)" $(MAKE) -C $(CORE_DIR)
	@ CFLAGS="$(DYFLAGS)" $(MAKE) -C $(GENCODECS_DIR)
	@ CFLAGS="$(CFLAGS)" $(MAKE) -C $(SRC_DIR) $@

install:
	@ mkdir -p $(DESTLIBDIR)
	@ mkdir -p $(DESTINCLUDE_DIR)
	install -d $(DESTLIBDIR)
	install -m 644 $(LIBDIR)/* $(DESTLIBDIR)
	install -d $(DESTINCLUDE_DIR)
	install -m 644 $(INCLUDE_DIR)/*.h $(CORE_DIR)/*.h $(GENCODECS_DIR)/*.h \
	               $(DESTINCLUDE_DIR)

uninstall:
	rm -rf $(PREFIX)/include/concord
	rm -rf $(PREFIX)/lib/libdiscord.a
	rm -rf $(PREFIX)/lib/libdiscord.so
	rm -rf $(PREFIX)/lib/libdiscord.dylib

docs:
	@ $(MAKE) -C $(GENCODECS_DIR) headers

echo:
	@ echo -e 'CC: $(CC)\n'
	@ echo -e 'PREFIX: $(PREFIX)\n'
	@ echo -e 'CFLAGS: $(CFLAGS)\n'

voice:
	@ CFLAGS="$(CFLAGS)" $(MAKE) -C $(SRC_DIR) $@
debug:
	@ CFLAGS="$(DEBUG_FLAGS)" $(MAKE)

test: debug
	@ $(MAKE) -C $(TEST_DIR)
examples: all
	@ $(MAKE) -C $(EXAMPLES_DIR)

clean: 
	@ $(MAKE) -C $(SRC_DIR) $@
	@ $(MAKE) -C $(TEST_DIR) $@
	@ $(MAKE) -C $(EXAMPLES_DIR) $@
	@ $(MAKE) -C $(GENCODECS_DIR) $@

purge: clean
	@ $(MAKE) -C $(SRC_DIR) $@

latest: master
latest-dev: dev

$(GIT_BRANCHES):
	$(MAKE) purge
	git switch $@
	git pull
	$(MAKE)

.PHONY: test examples uninstall install echo clean purge docs static shared shared_osx $(GIT_BRANCHES) $(GIT_TARGETS)
