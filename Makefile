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
CORE_DIR      := core
THIRDP_DIR    := $(CORE_DIR)/third-party
EXAMPLES_DIR  := examples
TEST_DIR      := test
CCORDDOCS_DIR := concord-docs

H_SPECS := discord-specs.h

COGUTILS_SRC := $(COGUTILS_DIR)/cog-utils.c        \
                $(COGUTILS_DIR)/json-actor.c       \
                $(COGUTILS_DIR)/json-actor-boxed.c \
                $(COGUTILS_DIR)/json-string.c      \
                $(COGUTILS_DIR)/log.c              \
                $(COGUTILS_DIR)/logconf.c          \
                $(COGUTILS_DIR)/ntl.c

CORE_SRC     := $(CORE_DIR)/common.c     \
                $(CORE_DIR)/work.c       \
                $(CORE_DIR)/user-agent.c \
                $(CORE_DIR)/websockets.c \
                $(CORE_DIR)/io_poller.c

THIRDP_SRC   := $(THIRDP_DIR)/sha1.c           \
                $(THIRDP_DIR)/curl-websocket.c \
                $(THIRDP_DIR)/threadpool.c

C_SPECS_SRC  := $(C_SPECS_DIR)/application.c                 \
                $(C_SPECS_DIR)/application_commands.c        \
                $(C_SPECS_DIR)/application_commands.params.c \
                $(C_SPECS_DIR)/audit_log.c                   \
                $(C_SPECS_DIR)/audit_log.params.c            \
                $(C_SPECS_DIR)/channel.c                     \
                $(C_SPECS_DIR)/channel.params.c              \
                $(C_SPECS_DIR)/emoji.c                       \
                $(C_SPECS_DIR)/emoji.params.c                \
                $(C_SPECS_DIR)/gateway.c                     \
                $(C_SPECS_DIR)/guild.c                       \
                $(C_SPECS_DIR)/guild.params.c                \
                $(C_SPECS_DIR)/guild_template.c              \
                $(C_SPECS_DIR)/guild_template.params.c       \
                $(C_SPECS_DIR)/interaction.c                 \
                $(C_SPECS_DIR)/interaction.params.c          \
                $(C_SPECS_DIR)/invite.c                      \
                $(C_SPECS_DIR)/invite.params.c               \
                $(C_SPECS_DIR)/message_components.c          \
                $(C_SPECS_DIR)/permissions.c                 \
                $(C_SPECS_DIR)/stage_instance.c              \
                $(C_SPECS_DIR)/stage_instance.params.c       \
                $(C_SPECS_DIR)/sticker.c                     \
                $(C_SPECS_DIR)/sticker.params.c              \
                $(C_SPECS_DIR)/user.c                        \
                $(C_SPECS_DIR)/user.params.c                 \
                $(C_SPECS_DIR)/voice-connections.c           \
                $(C_SPECS_DIR)/voice.c                       \
                $(C_SPECS_DIR)/webhook.c                     \
                $(C_SPECS_DIR)/webhook.params.c

DISCORD_SRC  := $(SRC_DIR)/adapter-api.c       \
                $(SRC_DIR)/adapter-ratelimit.c \
                $(SRC_DIR)/adapter.c           \
                $(SRC_DIR)/client.c            \
                $(SRC_DIR)/gateway.c           \
                $(SRC_DIR)/misc.c              \
                $(SRC_DIR)/voice.c             \
                $(C_SPECS_SRC)

SRC  := $(COGUTILS_SRC) $(CORE_SRC) $(THIRDP_SRC) $(DISCORD_SRC)
OBJS := $(SRC:%.c=$(OBJDIR)/%.o)

LIB := $(LIBDIR)/libdiscord.a

CFLAGS += -std=c99 -O0 -g -pthread -D_XOPEN_SOURCE=600                       \
          -I$(INCLUDE_DIR) -I$(COGUTILS_DIR) -I$(CORE_DIR) -I$(THIRDP_DIR) \
          -DLOG_USE_COLOR

WFLAGS += -Wall -Wextra -pedantic

$(OBJDIR)/$(SRC_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(WFLAGS) -c -o $@ $<
$(OBJDIR)/%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: | $(C_SPECS_DIR)
	$(MAKE) discord

specs_gen: | $(COGUTILS_DIR)
	@ $(MAKE) -C $(SPECS_DIR) clean
	@ $(MAKE) -C $(SPECS_DIR) gen_source gen_headers_amalgamation
	@ mkdir -p $(C_SPECS_DIR)
	mv $(SPECS_DIR)/code/*.c $(C_SPECS_DIR)
	mv $(SPECS_DIR)/code/$(H_SPECS) $(INCLUDE_DIR)

cog_utils:
	git clone https://github.com/cogmasters/cog-utils $(COGUTILS_DIR)

test: all
	@ $(MAKE) -C $(TEST_DIR)

examples: all
	@ $(MAKE) -C $(EXAMPLES_DIR)

discord: $(LIB) | $(C_SPECS_DIR)

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
	@ mkdir -p $@/$(THIRDP_DIR)   \
	           $@/$(COGUTILS_DIR) \
	           $@/$(C_SPECS_DIR)

install:
	@ mkdir -p $(PREFIX)/lib/
	@ mkdir -p $(PREFIX)/include/concord
	install -d $(PREFIX)/lib/
	install -m 644 $(LIB) $(PREFIX)/lib/
	install -d $(PREFIX)/include/concord/
	install -m 644 $(INCLUDE_DIR)/*.h $(COGUTILS_DIR)/*.h $(CORE_DIR)/*.h  \
	               $(THIRDP_DIR)/*.h $(PREFIX)/include/concord/

echo:
	@ echo -e 'CC: $(CC)\n'
	@ echo -e 'PREFIX: $(PREFIX)\n'
	@ echo -e 'CFLAGS: $(CFLAGS)\n'
	@ echo -e 'OBJS: $(OBJS)\n'
	@ echo -e 'COGUTILS_SRC: $(COGUTILS_SRC)\n'
	@ echo -e 'CORE_SRC: $(CORE_SRC)\n'
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
	rm -rf $(H_SPECS)

# prepare files for generating documentation at .github/workflows/gh_pages.yml
docs: | $(CCORDDOCS_DIR)
	@ $(MAKE) -C $(SPECS_DIR) clean
	@ $(MAKE) -C $(SPECS_DIR) gen_headers
	@ mv $(SPECS_DIR)/code/*.h $(H_SPECS_DIR)

$(CCORDDOCS_DIR): | $(H_SPECS_DIR)
	git clone https://github.com/cogmasters/concord-docs $@
	cp $@/Doxyfile Doxyfile

$(H_SPECS_DIR): | $(C_SPECS_DIR)
	@ mkdir -p $@

.PHONY: all test examples install echo clean purge docs
