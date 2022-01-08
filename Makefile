PREFIX ?= /usr/local
CC     ?= gcc

SRC_DIR       := src
INCLUDE_DIR   := include
OBJDIR        := obj
LIBDIR        := lib
DOCS_DIR      := docs
SPECS_DIR     := specs
C_SPECS_DIR   := $(SRC_DIR)/specs-code
H_SPECS_DIR   := $(DOCS_DIR)/specs-headers
COGUTILS_DIR  := cog-utils
COMMON_DIR    := common
THIRDP_DIR    := $(COMMON_DIR)/third-party
EXAMPLES_DIR  := examples
TEST_DIR      := test
CCORDDOCS_DIR := concord-docs

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
                $(COMMON_DIR)/websockets.c \
								$(COMMON_DIR)/io_poller.c

THIRDP_SRC   := $(THIRDP_DIR)/sha1.c           \
                $(THIRDP_DIR)/curl-websocket.c \
                $(THIRDP_DIR)/threadpool.c

DISCORD_SRC  := $(wildcard $(SRC_DIR)/*.c $(C_SPECS_DIR)/*.c)

SRC  := $(COGUTILS_SRC) $(COMMON_SRC) $(THIRDP_SRC) $(DISCORD_SRC)
OBJS := $(SRC:%.c=$(OBJDIR)/%.o)

# API libs
LIB := $(LIBDIR)/libdiscord.a

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

all: | $(C_SPECS_DIR)
	$(MAKE) discord

specs_gen: | $(COGUTILS_DIR)
	@ $(MAKE) -C $(SPECS_DIR) clean
	@ $(MAKE) -C $(SPECS_DIR) gen_source gen_headers_amalgamation
	@ mkdir -p $(C_SPECS_DIR)
	mv $(SPECS_DIR)/specs-code/discord/*.c $(C_SPECS_DIR)
	mv $(SPECS_DIR)/specs-code/discord/one-specs.h $(INCLUDE_DIR)

cog_utils:
	git clone https://github.com/cogmasters/cog-utils $(COGUTILS_DIR)

test: all
	@ $(MAKE) -C $(TEST_DIR)

examples: all
	@ $(MAKE) -C $(EXAMPLES_DIR)

discord: $(LIB) | $(C_SPECS_DIR)

# API libraries compilation
$(LIB): $(OBJS) | $(LIBDIR)
	$(AR) -cqsv $@ $?

$(LIBDIR):
	@ mkdir -p $@
$(C_SPECS_DIR):
	@ $(MAKE) specs_gen
$(COGUTILS_DIR):
	@ $(MAKE) cog_utils

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	@ mkdir -p $@/$(THIRDP_DIR)                                 \
	           $@/$(COGUTILS_DIR)                               \
	           $(addprefix $@/, $(wildcard $(C_SPECS_DIR)/*))

install:
	@ mkdir -p $(PREFIX)/lib/
	@ mkdir -p $(PREFIX)/include/concord
	install -d $(PREFIX)/lib/
	install -m 644 $(LIB) $(PREFIX)/lib/
	install -d $(PREFIX)/include/concord/
	install -m 644 $(INCLUDE_DIR)/*.h $(COGUTILS_DIR)/*.h $(COMMON_DIR)/*.h  \
	               $(THIRDP_DIR)/*.h $(PREFIX)/include/concord/

echo:
	@ echo -e 'CC: $(CC)\n'
	@ echo -e 'PREFIX: $(PREFIX)\n'
	@ echo -e 'CFLAGS: $(CFLAGS)\n'
	@ echo -e 'OBJS: $(OBJS)\n'
	@ echo -e 'SPECS DIRS: $(wildcard $(C_SPECS_DIR)/*)\n'
	@ echo -e 'COGUTILS_SRC: $(COGUTILS_SRC)\n'
	@ echo -e 'COMMON_SRC: $(COMMON_SRC)\n'
	@ echo -e 'DISCORD_SRC: $(DISCORD_SRC)\n'

clean: 
	rm -rf $(OBJDIR)
	rm -rf $(LIBDIR)
	@ $(MAKE) -C $(TEST_DIR) clean
	@ $(MAKE) -C $(EXAMPLES_DIR) clean

purge: clean
	rm -rf $(LIBDIR)
	rm -rf $(COGUTILS_DIR)
	rm -rf $(C_SPECS_DIR)

# prepare files for generating documentation at .github/workflows/gh_pages.yml
docs: | $(CCORDDOCS_DIR)
	@ $(MAKE) -C $(SPECS_DIR) clean
	@ $(MAKE) -C $(SPECS_DIR) gen_headers
	@ mv $(SPECS_DIR)/specs-code/discord/*.h $(H_SPECS_DIR)

$(CCORDDOCS_DIR): | $(H_SPECS_DIR)
	git clone https://github.com/cogmasters/concord-docs $@
	cp $@/Doxyfile Doxyfile

$(H_SPECS_DIR): | $(C_SPECS_DIR)
	@ mkdir -p $@

.PHONY: all test examples install echo clean purge docs
