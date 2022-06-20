PREFIX ?= /usr/local
CC     ?= gcc

SRC_DIR       = src
INCLUDE_DIR   = include
LIBDIR        = lib
DOCS_DIR      = docs
GENCODECS_DIR = gencodecs
CORE_DIR      = core
THIRDP_DIR    = $(CORE_DIR)/third-party
EXAMPLES_DIR  = examples
TEST_DIR      = test
CCORDDOCS_DIR = concord-docs

GENCODECS_HDR = $(GENCODECS_DIR)/discord_codecs.h

GENCODECS_OBJ = $(GENCODECS_DIR)/discord_codecs.o
CORE_OBJS     = $(CORE_DIR)/cog-utils.o  \
                $(CORE_DIR)/io_poller.o  \
                $(CORE_DIR)/user-agent.o \
                $(CORE_DIR)/websockets.o
THIRDP_OBJS   = $(THIRDP_DIR)/curl-websocket.o \
                $(THIRDP_DIR)/jsmn-find.o      \
                $(THIRDP_DIR)/json-build.o     \
                $(THIRDP_DIR)/log.o            \
                $(THIRDP_DIR)/logconf.o        \
                $(THIRDP_DIR)/priority_queue.o \
                $(THIRDP_DIR)/sha1.o           \
                $(THIRDP_DIR)/threadpool.o
DISCORD_OBJS  = $(SRC_DIR)/concord-once.o              \
                $(SRC_DIR)/discord-refcount.o          \
                $(SRC_DIR)/discord-rest.o              \
                $(SRC_DIR)/discord-rest_request.o      \
                $(SRC_DIR)/discord-rest_ratelimit.o    \
                $(SRC_DIR)/discord-client.o            \
                $(SRC_DIR)/discord-events.o            \
                $(SRC_DIR)/discord-loop.o              \
                $(SRC_DIR)/discord-gateway.o           \
                $(SRC_DIR)/discord-gateway_dispatch.o  \
                $(SRC_DIR)/discord-messagecommands.o   \
                $(SRC_DIR)/discord-timer.o             \
                $(SRC_DIR)/discord-misc.o              \
                $(SRC_DIR)/discord-worker.o            \
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
                $(SRC_DIR)/webhook.o

OBJS = $(GENCODECS_OBJ) $(CORE_OBJS) $(THIRDP_OBJS) $(DISCORD_OBJS)

ARLIB   = $(LIBDIR)/libdiscord.a
ARFLAGS = -cqsv

SOLIB   = $(LIBDIR)/libdiscord.so
SOFLAGS = -fPIC
LDFLAGS = -lcurl

DYLIB   = $(LIBDIR)/libdiscord.dylib
DYFLAGS = -fPIC 

WFLAGS += -Wall -Wextra -Wshadow -Wdouble-promotion -Wconversion -Wpedantic
CFLAGS += -std=c99 -O0 -g -pthread -D_XOPEN_SOURCE=600 -DLOG_USE_COLOR      \
          -I$(INCLUDE_DIR) -I$(CORE_DIR) -I$(THIRDP_DIR) -I$(GENCODECS_DIR) \
          -I$(PREFIX)/include

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(WFLAGS) -c -o $@ $<

all: $(ARLIB)

shared: 
	@ $(MAKE) clean
	@ $(MAKE) CFLAGS="$(SOFLAGS) $(CFLAGS)" $(SOLIB)

shared_osx:
	@ $(MAKE) clean
	@ $(MAKE) CFLAGS="$(DYFLAGS) $(CFLAGS)" $(DYLIB)

voice:
	@ $(MAKE) clean
	@ $(MAKE) CFLAGS="$(CFLAGS) -DCCORD_VOICE"
	          OBJS="$(OBJS) $(SRC_DIR)/discord-voice.o"

debug:
	@ $(MAKE) clean
	@ $(MAKE) CFLAGS="$(CFLAGS) -DCCORD_DEBUG_WEBSOCKETS -DCCORD_DEBUG_HTTP"

test: all
	@ $(MAKE) -C $(TEST_DIR)

examples: all
	@ $(MAKE) -C $(EXAMPLES_DIR)

gencodecs:
	@ $(MAKE) -C $(GENCODECS_DIR)

$(ARLIB): $(OBJS) | $(LIBDIR)
	$(AR) $(ARFLAGS) $@ $?

$(SOLIB): $(OBJS) | $(LIBDIR)
	$(CC) -shared $(LDFLAGS) -o $@ $<

$(DYLIB): $(OBJS) | $(LIBDIR)
	$(CC) -dynamiclib $(DYFLAGS) -o $@ $<

$(LIBDIR):
	@ mkdir -p $@

$(OBJS): $(GENCODECS_HDR)

$(GENCODECS_HDR): gencodecs

install:
	@ mkdir -p $(PREFIX)/lib/
	@ mkdir -p $(PREFIX)/include/concord
	install -d $(PREFIX)/lib/
	install -m 644 $(ARLIB) $(PREFIX)/lib/                              \
	  || install -m 644 $(SOLIB) $(PREFIX)/lib/                         \
	  || install -m 644 $(DYLIB) $(PREFIX)/lib/
	install -d $(PREFIX)/include/concord/
	install -m 644 $(INCLUDE_DIR)/*.h $(CORE_DIR)/*.h $(THIRDP_DIR)/*.h \
	               $(GENCODECS_DIR)/*.h $(PREFIX)/include/concord/

docs:
	@ $(MAKE) -C $(GENCODECS_DIR) docs

echo:
	@ echo -e 'CC: $(CC)\n'
	@ echo -e 'PREFIX: $(PREFIX)\n'
	@ echo -e 'CFLAGS: $(CFLAGS)\n'
	@ echo -e 'GENCODECS_OBJ: $(GENCODECS_OBJ)\n'
	@ echo -e 'CORE_OBJS: $(CORE_OBJS)\n'
	@ echo -e 'THIRDP_OBJS: $(THIRDP_OBJS)\n'
	@ echo -e 'DISCORD_OBJS: $(DISCORD_OBJS)\n'

clean: 
	@ $(RM) $(GENCODECS_OBJ) $(CORE_OBJS) $(THIRDP_OBJS) $(DISCORD_OBJS)
	@ $(RM) -r $(LIBDIR)
	@ $(MAKE) -C $(TEST_DIR) clean
	@ $(MAKE) -C $(EXAMPLES_DIR) clean

purge: clean
	@ $(MAKE) -C $(GENCODECS_DIR) clean

.PHONY: test examples install echo clean purge docs gencodecs
