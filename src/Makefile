TOP  = ..

PREFIX = /usr/local

INCLUDE_DIR   = $(TOP)/include
LIBDIR        = $(TOP)/lib
GENCODECS_DIR = $(TOP)/gencodecs
CORE_DIR      = $(TOP)/core

VERSION_MAJOR = 3.0
VERSION_MINOR = 0

CORE_OBJS     = $(CORE_DIR)/cog-utils.o          \
                $(CORE_DIR)/concord-error.o      \
                $(CORE_DIR)/concord-notifier.o   \
                $(CORE_DIR)/concord-once.o       \
                $(CORE_DIR)/io_poller.o          \
                $(CORE_DIR)/user-agent.o         \
                $(CORE_DIR)/websockets.o         \
                $(CORE_DIR)/jsmn-find.o          \
                $(CORE_DIR)/json-build.o         \
                $(CORE_DIR)/logmod.o             \
                $(CORE_DIR)/oa_hash.o            \
                $(CORE_DIR)/priority_queue.o     \
                $(CORE_DIR)/anomap.o             \
                $(CORE_DIR)/threadpool.o         \
                $(CORE_DIR)/queriec.o
GENCODECS_OBJ = $(GENCODECS_DIR)/discord_codecs.o

OBJS += discord-refcount.o         \
        discord-rest.o             \
        discord-rest_request.o     \
        discord-rest_ratelimit.o   \
        discord-client.o           \
        discord-events.o           \
        discord-cache.o            \
        discord-loop.o             \
        discord-gateway.o          \
        discord-gateway_dispatch.o \
        discord-messagecommands.o  \
        discord-timer.o            \
        discord-misc.o             \
        discord-worker.o           \
        application_command.o      \
        auto_moderation.o          \
        interaction.o              \
        audit_log.o                \
        channel.o                  \
        emoji.o                    \
        gateway.o                  \
        guild.o                    \
        guild_scheduled_event.o    \
        guild_template.o           \
        invite.o                   \
        oauth2.o                   \
				poll.o                     \
				stage_instance.o           \
				sticker.o                  \
        user.o                     \
        voice.o                    \
        webhook.o

WFLAGS  = -Wall -Wextra -Wshadow -Wdouble-promotion -Wconversion -Wpedantic
CFLAGS += -std=c99 -pthread -D_XOPEN_SOURCE=600 \
          -I$(INCLUDE_DIR) -I$(CORE_DIR) -I$(GENCODECS_DIR) -I$(PREFIX)/include

LIBNAME = libdiscord

ARLIB = $(LIBDIR)/$(LIBNAME).a
SOLIB_BASENAME = $(LIBNAME).so
SOLIB_FILENAME = $(SOLIB_BASENAME).$(VERSION_MAJOR).$(VERSION_MINOR)
SOLIB_SONAME = $(SOLIB_BASENAME).$(VERSION_MAJOR)

SOLIB = $(LIBDIR)/$(SOLIB_FILENAME)
SOLIBNOSONAME = $(LIBDIR)/$(SOLIB_BASENAME)
DYLIB = $(LIBDIR)/$(LIBNAME).dylib

ARFLAGS = -cqsv
SOFLAGS = -fPIC
DYFLAGS = -fPIC 

.c.o:
	$(CC) -c $(CFLAGS) $(WFLAGS) -o $@ $<

all: static

static: $(ARLIB)

shared:
	@ CFLAGS="$(SOFLAGS)" $(MAKE) $(SOLIB)
	@ ln -sf $(SOLIB_FILENAME) $(LIBDIR)/$(SOLIB_SONAME)
	@ ln -sf $(SOLIB_FILENAME) $(LIBDIR)/$(SOLIB_BASENAME)
shared_nosoname:
	@ CFLAGS="$(SOFLAGS)" $(MAKE) $(SOLIBNOSONAME)
shared_osx:
	@ CFLAGS="$(DYFLAGS)" $(MAKE) $(DYLIB)

$(ARLIB): deps
	$(AR) $(ARFLAGS) $@ $(OBJS) $(GENCODECS_OBJ) $(CORE_OBJS)
$(SOLIB): deps
	$(CC) -shared -Wl,-soname,$(SOLIB_SONAME) $(LDFLAGS) -o $@ $(OBJS) $(GENCODECS_OBJ) $(CORE_OBJS) -lcurl
$(SOLIBNOSONAME): deps
	$(CC) -shared $(LDFLAGS) -o $@ $(OBJS) $(GENCODECS_OBJ) $(CORE_OBJS) -lcurl
$(DYLIB): deps
	$(CC) -dynamiclib $(DYFLAGS) $(LDFLAGS) -o $@ $(OBJS) $(GENCODECS_OBJ) $(CORE_OBJS) -lcurl

deps:
	@ $(MAKE) -C $(CORE_DIR)
	@ $(MAKE) -C $(GENCODECS_DIR)
	@ $(MAKE) $(OBJS)

echo:
	@ echo -e 'CC: $(CC)\n'
	@ echo -e 'PREFIX: $(PREFIX)\n'
	@ echo -e 'CFLAGS: $(CFLAGS)\n'
	@ echo -e 'GENCODECS_OBJ: $(GENCODECS_OBJ)\n'
	@ echo -e 'CORE_OBJS: $(CORE_OBJS)\n'
	@ echo -e 'OBJS: $(OBJS)\n'

clean: 
	@ rm -rf $(LIBDIR)/*
	@ rm -f $(OBJS)
	@ $(MAKE) -C $(CORE_DIR) clean
purge: clean
	@ $(MAKE) -C $(GENCODECS_DIR) clean

.PHONY: test examples install echo clean purge docs deps static shared shared_osx
