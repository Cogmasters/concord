PREFIX ?= /usr/local
CC     ?= gcc

SRC_DIR       := src
INCLUDE_DIR   := include
OBJDIR        := obj
LIBDIR        := lib

SPECS_DIR     := specs
SPECSCODE_DIR := $(SRC_DIR)/specs-code
COGUTILS_DIR  := cog-utils
COMMON_DIR    := common
THIRDP_DIR    := $(COMMON_DIR)/third-party
EXAMPLES_DIR  := examples
TEST_DIR      := test
DOCS_DIR      := concord-docs

COGUTILS_SRC := $(COGUTILS_DIR)/cog-utils.c        \
                $(COGUTILS_DIR)/json-actor.c       \
                $(COGUTILS_DIR)/json-actor-boxed.c \
                $(COGUTILS_DIR)/json-string.c      \
                $(COGUTILS_DIR)/log.c              \
                $(COGUTILS_DIR)/logconf.c          \
                $(COGUTILS_DIR)/ntl.c

COMMON_SRC   := $(COMMON_DIR)/common.c     \
                $(COMMON_DIR)/work.c       \
                $(COMMON_DIR)/user-agent.c \
                $(COMMON_DIR)/websockets.c

THIRDP_SRC   := $(THIRDP_DIR)/sha1.c           \
                $(THIRDP_DIR)/curl-websocket.c \
                $(THIRDP_DIR)/threadpool.c

SRC  := $(COGUTILS_SRC) $(COMMON_SRC) $(THIRDP_SRC)
OBJS := $(SRC:%.c=$(OBJDIR)/%.o)

# APIs src
DISCORD_SRC := $(wildcard $(SRC_DIR)/discord-*.c $(SPECSCODE_DIR)/*.c)

# APIs objs
DISCORD_OBJS := $(DISCORD_SRC:%.c=$(OBJDIR)/%.o)

# API libs
LIBDISCORD := $(LIBDIR)/libdiscord.a

CFLAGS += -std=c99 -O0 -g -pthread -D_XOPEN_SOURCE=600                       \
          -I$(INCLUDE_DIR) -I$(COGUTILS_DIR) -I$(COMMON_DIR) -I$(THIRDP_DIR) \
          -DLOG_USE_COLOR

WFLAGS += -Wall -Wextra -pedantic

$(OBJDIR)/$(COGUTILS_DIR)/%.o : $(COGUTILS_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJDIR)/$(THIRDP_DIR)/%.o : $(THIRDP_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJDIR)/%.o : %.c
	$(CC) $(CFLAGS) $(WFLAGS) -c -o $@ $<

all: | $(SPECSCODE_DIR)
	$(MAKE) discord

specs_gen: | $(COGUTILS_DIR)
	@ $(MAKE) -C $(SPECS_DIR) clean
	@ $(MAKE) -C $(SPECS_DIR) gen_source gen_headers_amalgamation
	@ mkdir -p $(SPECSCODE_DIR)
	mv $(SPECS_DIR)/specs-code/discord/*.c $(SPECSCODE_DIR)
	mv $(SPECS_DIR)/specs-code/discord/*.h $(INCLUDE_DIR)

cog_utils:
	./scripts/get-cog-utils.sh

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
$(COGUTILS_DIR):
	@ $(MAKE) cog_utils

$(DISCORD_OBJS): $(OBJS)

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	@ mkdir -p $(OBJDIR)/$(THIRDP_DIR)                                 \
	           $(OBJDIR)/$(COGUTILS_DIR)                               \
	           $(addprefix $(OBJDIR)/, $(wildcard $(SPECSCODE_DIR)/*))

install:
	@ mkdir -p $(PREFIX)/lib/
	@ mkdir -p $(PREFIX)/include/concord
	install -d $(PREFIX)/lib/
	install -m 644 $(LIBDISCORD) $(PREFIX)/lib/
	install -d $(PREFIX)/include/concord/
	install -m 644 $(SRC_DIR)/*.h $(COGUTILS_DIR)/*.h $(COMMON_DIR)/*.h             \
	               $(THIRDP_DIR)/*.h $(PREFIX)/include/concord/
	install -d $(PREFIX)/include/concord/$(SPECSCODE_DIR)/discord/
	install -m 644 $(SPECSCODE_DIR)/discord/*.h                          \
	               $(PREFIX)/include/concord/$(SPECSCODE_DIR)/discord/

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
	rm -rf $(COGUTILS_DIR)
	rm -rf $(SPECSCODE_DIR)

# prepare files for generating documentation at .github/workflows/gh_pages.yml
docs: | $(DOCS_DIR)
	@ $(MAKE) -C $(SPECS_DIR) clean
	@ $(MAKE) -C $(SPECS_DIR) gen_headers
	@ mv $(SPECS_DIR)/specs-code $(SPECSCODE_DIR)

$(DOCS_DIR):
	git clone https://github.com/cogmasters/concord-docs
	cp $(DOCS_DIR)/Doxyfile Doxyfile

.PHONY: all test examples install echo clean purge docs
