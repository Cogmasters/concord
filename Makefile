PREFIX ?= /usr/local
CC     ?= gcc

SRC_DIR       := src
INCLUDE_DIR   := include
OBJDIR        := obj
LIBDIR        := lib
DOCS_DIR      := docs
COGUTILS_DIR  := cog-utils
GENCODECS_DIR := gencodecs
CORE_DIR      := core
THIRDP_DIR    := $(CORE_DIR)/third-party
EXAMPLES_DIR  := examples
TEST_DIR      := test
CCORDDOCS_DIR := concord-docs

COGUTILS_SRC := $(COGUTILS_DIR)/cog-utils.c        \
                $(COGUTILS_DIR)/log.c              \
                $(COGUTILS_DIR)/logconf.c

CORE_SRC     := $(CORE_DIR)/common.c     \
                $(CORE_DIR)/work.c       \
                $(CORE_DIR)/user-agent.c \
                $(CORE_DIR)/websockets.c \
                $(CORE_DIR)/io_poller.c  \
                $(CORE_DIR)/json-build.c \
                $(CORE_DIR)/jsmn-find.c

THIRDP_SRC   := $(THIRDP_DIR)/sha1.c           \
                $(THIRDP_DIR)/curl-websocket.c \
                $(THIRDP_DIR)/threadpool.c

GENCODECS_HDR := $(GENCODECS_DIR)/discord-codecs.h
GENCODECS_SRC := $(GENCODECS_DIR)/discord-codecs.c

DISCORD_SRC  := $(SRC_DIR)/adapter-api.c       \
                $(SRC_DIR)/adapter-ratelimit.c \
                $(SRC_DIR)/adapter.c           \
                $(SRC_DIR)/client.c            \
                $(SRC_DIR)/gateway.c           \
                $(SRC_DIR)/misc.c              \
                $(GENCODECS_SRC)               \
                $(XSRC)

SRC  := $(COGUTILS_SRC) $(CORE_SRC) $(THIRDP_SRC) $(DISCORD_SRC) $(GENCODECS_SRC)
OBJS := $(SRC:%.c=$(OBJDIR)/%.o)

LIB := $(LIBDIR)/libdiscord.a

CFLAGS += -std=c99 -O0 -g -pthread -D_XOPEN_SOURCE=600                     \
          -I$(INCLUDE_DIR) -I$(COGUTILS_DIR) -I$(CORE_DIR) -I$(THIRDP_DIR) \
          -I$(GENCODECS_DIR) -I/usr/local/include -DLOG_USE_COLOR

WFLAGS += -Wall -Wextra -pedantic

$(OBJDIR)/$(SRC_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(WFLAGS) $(XFLAGS) -c -o $@ $<
$(OBJDIR)/%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(GENCODECS_HDR)
	@ $(MAKE) discord

discord: $(LIB)

voice:
	@ $(MAKE) XFLAGS=-DHAS_DISCORD_VOICE XSRC=$(SRC_DIR)/voice.c all

debug:
	@ $(MAKE) XFLAGS="-D_CCORD_DEBUG_WEBSOCKETS -D_CCORD_DEBUG_ADAPTER" all

test: all
	@ $(MAKE) -C $(TEST_DIR)

examples: all
	@ $(MAKE) -C $(EXAMPLES_DIR)

gencodecs:
	@ $(MAKE) -C $(GENCODECS_DIR)

$(LIB): $(OBJS) | $(LIBDIR)
	$(AR) -cqsv $@ $?

$(LIBDIR):
	@ mkdir -p $@

$(OBJS): | $(OBJDIR)

$(GENCODECS_HDR): gencodecs

$(OBJDIR):
	@ mkdir -p $@/$(THIRDP_DIR)   \
	           $@/$(COGUTILS_DIR) \
	           $@/$(SRC_DIR)      \
	           $@/$(GENCODECS_DIR)

install:
	@ mkdir -p $(PREFIX)/lib/
	@ mkdir -p $(PREFIX)/include/concord
	install -d $(PREFIX)/lib/
	install -m 644 $(LIB) $(PREFIX)/lib/
	install -d $(PREFIX)/include/concord/
	install -m 644 $(INCLUDE_DIR)/*.h $(COGUTILS_DIR)/*.h $(CORE_DIR)/*.h  \
	               $(THIRDP_DIR)/*.h $(GENCODECS_DIR)/*.h $(PREFIX)/include/concord/

echo:
	@ echo -e 'CC: $(CC)\n'
	@ echo -e 'PREFIX: $(PREFIX)\n'
	@ echo -e 'CFLAGS: $(CFLAGS)\n'
	@ echo -e 'OBJS: $(OBJS)\n'
	@ echo -e 'COGUTILS_SRC: $(COGUTILS_SRC)\n'
	@ echo -e 'CORE_SRC: $(CORE_SRC)\n'
	@ echo -e 'DISCORD_SRC: $(DISCORD_SRC)\n'
	@ echo -e 'GENCODECS_SRC: $(GENCODECS_SRC)\n'

clean: 
	rm -rf $(OBJDIR)
	rm -rf $(LIBDIR)
	@ $(MAKE) -C $(TEST_DIR) clean
	@ $(MAKE) -C $(EXAMPLES_DIR) clean

purge: clean
	rm -rf $(LIBDIR)
	@ $(MAKE) -C $(GENCODECS_DIR) clean

.PHONY: test examples install echo clean purge docs gencodecs
