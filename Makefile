PREFIX ?= /usr/local
CC     ?= gcc

OBJDIR        := obj
LIBDIR        := lib
SPECS_DIR     := specs
SPECSCODE_DIR := specs-code
CEEUTILS_DIR  := cee-utils
COMMON_DIR    := common
THIRDP_DIR    := $(COMMON_DIR)/third-party
EXAMPLES_DIR  := examples
TEST_DIR      := test
ORCADOCS_DIR  := orca-docs

CEEUTILS_SRC := $(CEEUTILS_DIR)/cee-utils.c        \
                $(CEEUTILS_DIR)/json-actor.c       \
                $(CEEUTILS_DIR)/json-actor-boxed.c \
                $(CEEUTILS_DIR)/json-string.c      \
                $(CEEUTILS_DIR)/log.c              \
                $(CEEUTILS_DIR)/logconf.c          \
                $(CEEUTILS_DIR)/ntl.c

COMMON_SRC   := $(COMMON_DIR)/common.c     \
                $(COMMON_DIR)/work.c       \
                $(COMMON_DIR)/user-agent.c \
                $(COMMON_DIR)/websockets.c

THIRDP_SRC   := $(THIRDP_DIR)/sha1.c           \
                $(THIRDP_DIR)/curl-websocket.c \
                $(THIRDP_DIR)/threadpool.c

SRC  := $(CEEUTILS_SRC) $(COMMON_SRC) $(THIRDP_SRC)
OBJS := $(SRC:%.c=$(OBJDIR)/%.o)

# APIs src
DISCORD_SRC := $(wildcard discord-*.c $(SPECSCODE_DIR)/discord/*.c)

# APIs objs
DISCORD_OBJS := $(DISCORD_SRC:%.c=$(OBJDIR)/%.o)

# API libs
LIBDISCORD := $(LIBDIR)/libdiscord.a

CFLAGS += -std=c99 -O0 -g -pthread -D_XOPEN_SOURCE=600          \
          -I. -I$(CEEUTILS_DIR) -I$(COMMON_DIR) -I$(THIRDP_DIR) \
          -DLOG_USE_COLOR

WFLAGS += -Wall -Wextra -pedantic

ifeq (,$(findstring $(CC),stensal-c sfc)) # ifneq stensal-c AND sfc
	CFLAGS  += -fPIC
endif

$(OBJDIR)/$(CEEUTILS_DIR)/%.o : $(CEEUTILS_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJDIR)/$(THIRDP_DIR)/%.o : $(THIRDP_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJDIR)/%.o : %.c
	$(CC) $(CFLAGS) $(WFLAGS) -c -o $@ $<

all: | $(SPECSCODE_DIR)
	$(MAKE) discord

specs_gen: | $(CEEUTILS_DIR)
	@ $(MAKE) -C $(SPECS_DIR) clean
	@ $(MAKE) -C $(SPECS_DIR) gen_source gen_headers_amalgamation
	@ rm -rf $(SPECSCODE_DIR)
	mv $(SPECS_DIR)/specs-code $(SPECSCODE_DIR)

cee_utils:
	./scripts/get-cee-utils.sh

test: all
	@ $(MAKE) -C $(TEST_DIR)

examples: all
	@ $(MAKE) -C $(EXAMPLES_DIR)

discord: $(LIBDISCORD) | $(SPECSCODE_DIR)

# API libraries compilation
$(LIBDISCORD): $(DISCORD_OBJS) $(OBJS) | $(LIBDIR)
	$(AR) -cqsv $@ $?

$(LIBDIR):
	@ mkdir -p $(LIBDIR)
$(SPECSCODE_DIR):
	@ $(MAKE) specs_gen
$(CEEUTILS_DIR):
	@ $(MAKE) cee_utils

$(DISCORD_OBJS): $(OBJS)

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	@ mkdir -p $(OBJDIR)/$(THIRDP_DIR)                                 \
	           $(OBJDIR)/$(CEEUTILS_DIR)                               \
	           $(addprefix $(OBJDIR)/, $(wildcard $(SPECSCODE_DIR)/*))

install:
	@ mkdir -p $(PREFIX)/lib/
	@ mkdir -p $(PREFIX)/include/orca
	install -d $(PREFIX)/lib/
	install -m 644 $(LIBDISCORD) $(PREFIX)/lib/
	install -d $(PREFIX)/include/orca/
	install -m 644 *.h $(CEEUTILS_DIR)/*.h $(COMMON_DIR)/*.h             \
	               $(THIRDP_DIR)/*.h $(PREFIX)/include/orca/
	install -d $(PREFIX)/include/orca/$(SPECSCODE_DIR)/discord/
	install -m 644 $(SPECSCODE_DIR)/discord/*.h                          \
	               $(PREFIX)/include/orca/$(SPECSCODE_DIR)/discord/

echo:
	@ echo -e 'CC: $(CC)\n'
	@ echo -e 'PREFIX: $(PREFIX)\n'
	@ echo -e 'CFLAGS: $(CFLAGS)\n'
	@ echo -e 'OBJS: $(OBJS)\n'
	@ echo -e 'SPECS DIRS: $(wildcard $(SPECSCODE_DIR)/*)\n'
	@ echo -e 'DISCORD_SRC: $(DISCORD_SRC)\n'
	@ echo -e 'DISCORD_OBJS: $(DISCORD_OBJS)\n'

clean: 
	rm -rf $(OBJDIR)
	rm -rf $(LIBDIR)
	@ $(MAKE) -C $(TEST_DIR) clean
	@ $(MAKE) -C $(EXAMPLES_DIR) clean

purge: clean
	rm -rf $(LIBDIR)
	rm -rf $(CEEUTILS_DIR)
	rm -rf $(SPECSCODE_DIR)

# prepare files for generating documentation at .github/workflows/gh_pages.yml
docs: | $(ORCADOCS_DIR)
	@ $(MAKE) -C $(SPECS_DIR) clean
	@ $(MAKE) -C $(SPECS_DIR) gen_headers
	@ rm -rf $(SPECSCODE_DIR)
	@ mv $(SPECS_DIR)/specs-code $(SPECSCODE_DIR)

$(ORCADOCS_DIR):
	git clone https://github.com/cee-studio/orca-docs
	cp $(ORCADOCS_DIR)/Doxyfile Doxyfile

.PHONY: all test examples install echo clean purge docs
