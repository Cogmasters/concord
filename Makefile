PREFIX ?= /usr/local
CC     ?= gcc

SRC_DIR       = src
INCLUDE_DIR   = include
OBJDIR        = obj
LIBDIR        = lib
DOCS_DIR      = docs
COGUTILS_DIR  = cog-utils
GENCODECS_DIR = gencodecs
CORE_DIR      = core
THIRDP_DIR    = $(CORE_DIR)/third-party
EXAMPLES_DIR  = examples
TEST_DIR      = test
CCORDDOCS_DIR = concord-docs

GENCODECS_HDR = $(GENCODECS_DIR)/discord-codecs.h
GENCODECS_OBJ = $(GENCODECS_DIR)/discord-codecs.o

COGUTILS_OBJS = $(OBJDIR)/$(COGUTILS_DIR)/cog-utils.o \
                $(OBJDIR)/$(COGUTILS_DIR)/log.o       \
                $(OBJDIR)/$(COGUTILS_DIR)/logconf.o
CORE_OBJS     = $(OBJDIR)/$(CORE_DIR)/work.o       \
                $(OBJDIR)/$(CORE_DIR)/user-agent.o \
                $(OBJDIR)/$(CORE_DIR)/websockets.o \
                $(OBJDIR)/$(CORE_DIR)/io_poller.o  \
                $(OBJDIR)/$(CORE_DIR)/json-build.o \
                $(OBJDIR)/$(CORE_DIR)/jsmn-find.o
THIRDP_OBJS   = $(OBJDIR)/$(THIRDP_DIR)/sha1.o           \
                $(OBJDIR)/$(THIRDP_DIR)/curl-websocket.o \
                $(OBJDIR)/$(THIRDP_DIR)/threadpool.o
DISCORD_OBJS  = $(OBJDIR)/$(SRC_DIR)/concord-once.o        \
                $(OBJDIR)/$(SRC_DIR)/discord-adapter.o     \
                $(OBJDIR)/$(SRC_DIR)/discord-ratelimit.o   \
                $(OBJDIR)/$(SRC_DIR)/discord-client.o      \
                $(OBJDIR)/$(SRC_DIR)/discord-gateway.o     \
                $(OBJDIR)/$(SRC_DIR)/discord-misc.o        \
                $(OBJDIR)/$(SRC_DIR)/application_command.o \
                $(OBJDIR)/$(SRC_DIR)/interaction.o         \
                $(OBJDIR)/$(SRC_DIR)/audit_log.o           \
                $(OBJDIR)/$(SRC_DIR)/channel.o             \
                $(OBJDIR)/$(SRC_DIR)/emoji.o               \
                $(OBJDIR)/$(SRC_DIR)/gateway.o             \
                $(OBJDIR)/$(SRC_DIR)/guild.o               \
                $(OBJDIR)/$(SRC_DIR)/guild_template.o      \
                $(OBJDIR)/$(SRC_DIR)/invite.o              \
                $(OBJDIR)/$(SRC_DIR)/user.o                \
                $(OBJDIR)/$(SRC_DIR)/voice.o               \
                $(OBJDIR)/$(SRC_DIR)/webhook.o             \
                $(XOBJ)

OBJS := $(COGUTILS_OBJS) $(CORE_OBJS) $(THIRDP_OBJS) $(DISCORD_OBJS) \
        $(GENCODECS_OBJ)

LIB := $(LIBDIR)/libdiscord.a

CFLAGS += -std=c99 -O0 -g -pthread -D_XOPEN_SOURCE=600                     \
          -I$(INCLUDE_DIR) -I$(COGUTILS_DIR) -I$(CORE_DIR) -I$(THIRDP_DIR) \
          -I$(GENCODECS_DIR) -I$(PREFIX)/include -DLOG_USE_COLOR

WFLAGS += -Wall -Wextra -pedantic

$(OBJDIR)/$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(WFLAGS) $(XFLAGS) -c -o $@ $<
$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(LIB)

voice:
	@ $(MAKE) XFLAGS=-DHAS_DISCORD_VOICE XOBJ=$(OBJDIR)/$(SRC_DIR)/discord-voice.o all

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

$(OBJS): $(GENCODECS_HDR) | $(OBJDIR)

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

docs:
	@ $(MAKE) -C $(GENCODECS_DIR) docs

echo:
	@ echo -e 'CC: $(CC)\n'
	@ echo -e 'PREFIX: $(PREFIX)\n'
	@ echo -e 'CFLAGS: $(CFLAGS)\n'
	@ echo -e 'COGUTILS_OBJS: $(COGUTILS_OBJS)\n'
	@ echo -e 'CORE_OBJS: $(CORE_OBJS)\n'
	@ echo -e 'DISCORD_OBJS: $(DISCORD_OBJS)\n'
	@ echo -e 'OBJS: $(OBJS)\n'

clean: 
	rm -rf $(OBJDIR)
	rm -rf $(LIBDIR)
	@ $(MAKE) -C $(TEST_DIR) clean
	@ $(MAKE) -C $(EXAMPLES_DIR) clean

purge: clean
	rm -rf $(LIBDIR)
	@ $(MAKE) -C $(GENCODECS_DIR) clean

.PHONY: test examples install echo clean purge docs gencodecs
