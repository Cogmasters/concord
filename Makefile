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

GENCODECS_HDR = $(GENCODECS_DIR)/discord_codecs.h
GENCODECS_OBJ = $(GENCODECS_DIR)/discord_codecs.o

COGUTILS_OBJS = $(COGUTILS_DIR)/cog-utils.o  \
                $(COGUTILS_DIR)/log.o        \
                $(COGUTILS_DIR)/logconf.o    \
                $(COGUTILS_DIR)/json-build.o \
                $(COGUTILS_DIR)/jsmn-find.o
CORE_OBJS     = $(CORE_DIR)/work.o       \
                $(CORE_DIR)/user-agent.o \
                $(CORE_DIR)/websockets.o \
                $(CORE_DIR)/io_poller.o
THIRDP_OBJS   = $(THIRDP_DIR)/sha1.o           \
                $(THIRDP_DIR)/curl-websocket.o \
                $(THIRDP_DIR)/threadpool.o     \
                $(THIRDP_DIR)/priority_queue.o
DISCORD_OBJS  = $(SRC_DIR)/concord-once.o              \
                $(SRC_DIR)/discord-adapter.o           \
                $(SRC_DIR)/discord-adapter_ratelimit.o \
                $(SRC_DIR)/discord-adapter_request.o   \
                $(SRC_DIR)/discord-refcount.o          \
                $(SRC_DIR)/discord-client.o            \
                $(SRC_DIR)/discord-loop.o              \
                $(SRC_DIR)/discord-gateway.o           \
                $(SRC_DIR)/discord-gateway_dispatch.o  \
                $(SRC_DIR)/discord-messagecommands.o   \
                $(SRC_DIR)/discord-timer.o             \
                $(SRC_DIR)/discord-misc.o              \
                $(SRC_DIR)/application_command.o       \
                $(SRC_DIR)/interaction.o               \
                $(SRC_DIR)/audit_log.o                 \
                $(SRC_DIR)/channel.o                   \
                $(SRC_DIR)/emoji.o                     \
                $(SRC_DIR)/gateway.o                   \
                $(SRC_DIR)/guild.o                     \
                $(SRC_DIR)/guild_template.o            \
                $(SRC_DIR)/invite.o                    \
                $(SRC_DIR)/user.o                      \
                $(SRC_DIR)/voice.o                     \
                $(SRC_DIR)/webhook.o                   \
                $(XOBJ)

OBJS := $(COGUTILS_OBJS) $(CORE_OBJS) $(THIRDP_OBJS) $(DISCORD_OBJS) \
        $(GENCODECS_OBJ)

LIB := $(LIBDIR)/libdiscord.a

CFLAGS += -std=c99 -O0 -g -pthread -D_XOPEN_SOURCE=600                     \
          -I$(INCLUDE_DIR) -I$(COGUTILS_DIR) -I$(CORE_DIR) -I$(THIRDP_DIR) \
          -I$(GENCODECS_DIR) -I$(PREFIX)/include -DLOG_USE_COLOR
WFLAGS += -Wall -Wextra -Wshadow -Wdouble-promotion -Wconversion -Wpedantic

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(WFLAGS) $(XFLAGS) -c -o $@ $<
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(LIB)

voice:
	@ $(MAKE) XFLAGS=-DCCORD_VOICE XOBJ=$(SRC_DIR)/discord-voice.o all

debug:
	@ $(MAKE) XFLAGS="-DCCORD_DEBUG_WEBSOCKETS -DCCORD_DEBUG_ADAPTER" all

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
	@ $(RM) $(GENCODECS_OBJS) $(COGUTILS_OBJS) $(CORE_OBJS) $(THIRDP_OBJS) $(DISCORD_OBJS)
	@ $(MAKE) -C $(TEST_DIR) clean
	@ $(MAKE) -C $(EXAMPLES_DIR) clean

purge: clean
	@ $(RM) -r $(LIBDIR)
	@ $(MAKE) -C $(GENCODECS_DIR) clean

.PHONY: test examples install echo clean purge docs gencodecs
