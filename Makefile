# Concord top-level Makefile
# Various options in this file can be tailored to the user's environment.

# Installation prefix that the headers/libraries will be deposited into:
PREFIX           = /usr/local
SHAREDIR         = /usr/share
DESTINCLUDE_DIR  = $(PREFIX)/include/concord
DESTLIBDIR       = $(PREFIX)/lib
# If you have a nonstandard pkg_config directory, specify it here:
PKGCONFIGDIR     = $(SHAREDIR)/pkgconfig

SRC_DIR        = src
INCLUDE_DIR    = include
LIBDIR         = lib
DOCS_DIR       = docs
API_DIR    = $(SRC_DIR)/api
CORE_DIR       = core
EXAMPLES_DIR   = examples
TEST_DIR       = test
# Flags for compiling the shared version of Concord:
SOFLAGS       = -fPIC
DYFLAGS       = -fPIC 
# C compiler debug options:
DEBUG_FLAGS   = -O0 -g

# Directories for generated files and reflect-c outputs
REFLECTC_DIR  = reflect-c
REFLECTC_OUT  = $(GENERATED_DIR)/discord_codecs
REFLECTC_CFLAGS = -I. -Wall -Wextra -Wpedantic -std=c89
GENERATED_DIR = generated
GENERATED_FILES = $(REFLECTC_OUT).c $(REFLECTC_OUT).h

GIT_BRANCHES = master dev
GIT_TARGETS  = latest latest-dev

# If you are using Solaris, comment out the second line.
INSTALL       = install
# INSTALL       = /usr/ucb/install

# ?= so flags passed via the environment (debug/check-san recipes, distro
# packagers) are honored instead of silently overridden
CFLAGS ?= -O2

# Sanitizer flags: -fno-sanitize-recover so UBSan findings fail the exit status
SANFLAGS = -fsanitize=address,undefined -fno-sanitize-recover=undefined \
           -fno-omit-frame-pointer

all: static

$(REFLECTC_OUT).c: $(REFLECTC_OUT).h

$(REFLECTC_OUT).h: reflectc-gen

static: $(GENERATED_FILES)
	@ CFLAGS="$(CFLAGS)" $(MAKE) -C $(CORE_DIR)
	@ CFLAGS="$(CFLAGS)" $(MAKE) -C $(SRC_DIR) $@
shared: $(GENERATED_FILES)
	@ CFLAGS="$(SOFLAGS) $(CFLAGS)" $(MAKE) -C $(CORE_DIR)
	@ CFLAGS="$(CFLAGS)" $(MAKE) -C $(SRC_DIR) $@
shared_nosoname: $(GENERATED_FILES)
	@ CFLAGS="$(SOFLAGS) $(CFLAGS)" $(MAKE) -C $(CORE_DIR)
	@ CFLAGS="$(CFLAGS)" $(MAKE) -C $(SRC_DIR) $@
shared_osx: $(GENERATED_FILES)
	@ CFLAGS="$(DYFLAGS) $(CFLAGS)" $(MAKE) -C $(CORE_DIR)
	@ CFLAGS="$(CFLAGS)" $(MAKE) -C $(SRC_DIR) $@

install:
	@ mkdir -p $(DESTLIBDIR)
	@ mkdir -p $(DESTINCLUDE_DIR)
	$(INSTALL) -d $(DESTLIBDIR)
	@ for lib in $(LIBDIR)/libdiscord.a $(LIBDIR)/libdiscord.so $(LIBDIR)/libdiscord.so.* $(LIBDIR)/libdiscord.dylib; do \
		if [ -e "$$lib" ]; then chmod 755 "$$lib"; fi; \
	done
	cp -P $(LIBDIR)/* $(DESTLIBDIR)
	$(INSTALL) -d $(DESTINCLUDE_DIR)
	$(INSTALL) -m 644 $(INCLUDE_DIR)/*.h $(CORE_DIR)/*.h $(GENERATED_DIR)/*.h \
	               $(DESTINCLUDE_DIR)
	$(INSTALL) -m 644 $(REFLECTC_DIR)/reflect-c.h $(DESTINCLUDE_DIR)
	$(INSTALL) -d $(PKGCONFIGDIR)
	$(INSTALL) -m 644 concord.pc $(PKGCONFIGDIR)/concord.pc

uninstall:
	rm -rf $(PREFIX)/include/concord
	rm -rf $(PREFIX)/lib/libdiscord.a
	rm -f $(PREFIX)/lib/libdiscord.so $(PREFIX)/lib/libdiscord.so.*
	rm -rf $(PREFIX)/lib/libdiscord.dylib
	rm -f $(PKGCONFIGDIR)/concord.pc

docs: $(REFLECTC_OUT).h

reflectc-update:
	git submodule update --init --remote $(REFLECTC_DIR)
reflectc-submodule:
	@ git submodule update --init --recursive $(REFLECTC_DIR)
reflectc-gen: reflectc-submodule
	@ mkdir -p $(GENERATED_DIR) # untracked: absent on a fresh clone
	@ $(MAKE) -C $(REFLECTC_DIR) CFLAGS="$(REFLECTC_CFLAGS) $(CFLAGS)" REFLECTC_TUPLE_MAX=64 tuples
	@ $(MAKE) -C $(REFLECTC_DIR) CFLAGS="$(REFLECTC_CFLAGS) $(CFLAGS)" API_DIR=../$(API_DIR) OUT=../$(REFLECTC_OUT) gen
reflectc-headers: reflectc-submodule
	@ $(MAKE) -C $(REFLECTC_DIR) CFLAGS="$(REFLECTC_CFLAGS) $(CFLAGS)" REFLECTC_TUPLE_MAX=64 tuples
	@ $(MAKE) -C $(REFLECTC_DIR) CFLAGS="$(REFLECTC_CFLAGS) $(CFLAGS)" API_DIR=../$(API_DIR) OUT=../$(REFLECTC_OUT) headers

echo:
	@ echo -e 'CC: $(CC)\n'
	@ echo -e 'PREFIX: $(PREFIX)\n'
	@ echo -e 'CFLAGS: $(CFLAGS)\n'

debug:
	@ CFLAGS="$(DEBUG_FLAGS)" $(MAKE)

test: debug
	@ $(MAKE) -C $(TEST_DIR)
check: debug
	@ $(MAKE) -C $(TEST_DIR) check
# Hermetic suites under ASan/UBSan. Cleans first: make doesn't track flag
# changes, and stale unsanitized objects would silently weaken the run.
check-san:
	@ $(MAKE) clean
	@ CFLAGS="$(DEBUG_FLAGS) $(SANFLAGS)" $(MAKE)
	@ CFLAGS="$(DEBUG_FLAGS) $(SANFLAGS)" $(MAKE) -C $(TEST_DIR) check
# Live smoke suites against real Discord; requires credentials in
# test/test_config.json (see test/README.md). Preflight runs before any
# build so a placeholder config is refused immediately.
check-live:
	@ $(MAKE) -C $(TEST_DIR) check-live-preflight
	@ $(MAKE) test
	@ $(MAKE) -C $(TEST_DIR) check-live
examples: all
	@ $(MAKE) -C $(EXAMPLES_DIR)

clean:
	@ $(MAKE) -C $(SRC_DIR) $@
	@ $(MAKE) -C $(TEST_DIR) $@
	@ $(MAKE) -C $(EXAMPLES_DIR) $@
	@ # tolerate an uninitialized submodule (fresh clone/CI cleans first)
	@ if [ -f $(REFLECTC_DIR)/Makefile ]; then \
	      $(MAKE) -C $(REFLECTC_DIR) $@; \
	  fi
	@ rm -f $(REFLECTC_OUT).c $(REFLECTC_OUT).h $(REFLECTC_OUT).o
purge: clean
	@ $(MAKE) -C $(SRC_DIR) $@

latest: master
latest-dev: dev

$(GIT_BRANCHES):
	$(MAKE) purge
	git switch $@
	git pull
	$(MAKE)

.PHONY: test check check-san check-live examples uninstall install echo clean purge docs static shared shared_osx \
	reflectc-update reflectc-submodule reflectc-gen reflectc-headers \
	$(GIT_BRANCHES) $(GIT_TARGETS)
