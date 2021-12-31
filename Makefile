PREFIX ?= /usr/local
CC     ?= gcc

OBJDIR        := obj
LIBDIR        := lib
SPECS_DIR     := specs
SPECSCODE_DIR := specs-code
CEEUTILS_DIR  := cee-utils
COMMON_DIR    := common
EXAMPLES_DIR  := examples
TEST_DIR      := test

CEEUTILS_SRC := $(CEEUTILS_DIR)/cee-utils.c        \
                $(CEEUTILS_DIR)/json-actor.c       \
                $(CEEUTILS_DIR)/json-actor-boxed.c \
                $(CEEUTILS_DIR)/json-string.c      \
                $(CEEUTILS_DIR)/log.c              \
                $(CEEUTILS_DIR)/logconf.c          \
                $(CEEUTILS_DIR)/ntl.c
CEEUTILS_OBJS := $(CEEUTILS_SRC:%.c=$(OBJDIR)/%.o)

SRC := $(COMMON_DIR)/common.c                     \
       $(COMMON_DIR)/work.c                       \
       $(COMMON_DIR)/user-agent.c                 \
       $(COMMON_DIR)/websockets.c                 \
       $(COMMON_DIR)/third-party/curl-websocket.c \
       $(COMMON_DIR)/third-party/threadpool.c
OBJS := $(SRC:%.c=$(OBJDIR)/%.o)

# APIs src
DISCORD_SRC := $(wildcard discord-*.c)
GITHUB_SRC  := $(wildcard github-*.c)
REDDIT_SRC  := $(wildcard reddit-*.c)
SLACK_SRC   := $(wildcard slack-*.c)

# APIs objs
DISCORD_OBJS := $(DISCORD_SRC:%.c=$(OBJDIR)/%.o)
GITHUB_OBJS  := $(GITHUB_SRC:%.c=$(OBJDIR)/%.o)
REDDIT_OBJS  := $(REDDIT_SRC:%.c=$(OBJDIR)/%.o)
SLACK_OBJS   := $(SLACK_SRC:%.c=$(OBJDIR)/%.o)

# APIs specs
DISCORD_SPECS = $(wildcard $(OBJDIR)/$(SPECSCODE_DIR)/discord/*.o)
GITHUB_SPECS  = $(wildcard $(OBJDIR)/$(SPECSCODE_DIR)/github/*.o)
REDDIT_SPECS  = $(wildcard $(OBJDIR)/$(SPECSCODE_DIR)/reddit/*.o)
SLACK_SPECS   = $(wildcard $(OBJDIR)/$(SPECSCODE_DIR)/slack/*.o)

# API libs ldflags
LIBDISCORD_LDFLAGS := -ldiscord
LIBGITHUB_LDFLAGS  := -lgithub
LIBREDDIT_LDFLAGS  := -lreddit
LIBSLACK_LDFLAGS   := -lslack

# API libs
LIBDISCORD := $(LIBDIR)/libdiscord.a
LIBGITHUB  := $(LIBDIR)/libgithub.a
LIBREDDIT  := $(LIBDIR)/libreddit.a
LIBSLACK   := $(LIBDIR)/libslack.a

LIBS_CFLAGS  +=
LIBS_LDFLAGS += -L./$(LIBDIR) -lm

CFLAGS += -O0 -g -pthread -Wall                                              \
          -I. -I$(CEEUTILS_DIR) -I$(COMMON_DIR) -I$(COMMON_DIR)/third-party \
          -DLOG_USE_COLOR

ifeq ($(BEARSSL),1)
	LIBS_LDFLAGS += -lbearssl -static
	CFLAGS += -DBEARSSL
else ifneq (,$(findstring $(CC),stensal-c sfc)) # ifeq stensal-c OR sfc
	LIBS_LDFLAGS += -lcurl-bearssl -lbearssl -static
	CFLAGS += -DBEARSSL
else
	LIBS_LDFLAGS += $(pkg-config --libs --cflags libcurl) -lcurl -lcrypto
endif

ifeq ($(static_debug),1)
	CFLAGS +=  -D_STATIC_DEBUG
else ifeq ($(static_debug),2) 
	CFLAGS +=  -D_STRICT_STATIC_DEBUG
else ifeq ($(static_debug),3) 
	CFLAGS +=  -D_STATIC_DEBUG -D_STRICT_STATIC_DEBUG
endif

ifneq (,$(findstring $(CC),stensal-c sfc)) # ifeq stensal-c OR sfc
	CFLAGS += -D_DEFAULT_SOURCE
	__D    := $(shell dirname $(shell which $(CC)))
	__DEST := $(patsubst %/stensal/bin,%,$(__D))
	PREFIX := $(__DEST)/usr
else
	CFLAGS += -fPIC -D_XOPEN_SOURCE=700
endif

$(OBJDIR)/%.o : %.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<

all: discord github reddit slack

test: all
	@ $(MAKE) -C $(TEST_DIR)

examples: all
	@ $(MAKE) -C $(EXAMPLES_DIR)

discord: $(LIBDISCORD)
github: $(LIBGITHUB)
reddit: $(LIBREDDIT)
slack: $(LIBSLACK)

# API libraries compilation
$(LIBDISCORD): $(DISCORD_OBJS) $(OBJS) $(CEEUTILS_OBJS) $(DISCORD_SPECS) | $(LIBDIR)
	$(AR) -cqsv $@ $?
$(LIBGITHUB): $(GITHUB_OBJS) $(OBJS) $(CEEUTILS_OBJS) $(GITHUB_SPECS) | $(LIBDIR)
	$(AR) -cqsv $@ $?
$(LIBREDDIT): $(REDDIT_OBJS) $(OBJS) $(CEEUTILS_OBJS) $(REDDIT_SPECS) | $(LIBDIR)
	$(AR) -cqsv $@ $?
$(LIBSLACK): $(SLACK_OBJS) $(OBJS) $(CEEUTILS_OBJS) $(SLACK_SPECS) | $(LIBDIR)
	$(AR) -cqsv $@ $?

$(CEEUTILS_OBJS): ;

$(LIBDIR):
	@ mkdir -p $(LIBDIR)

$(DISCORD_OBJS): $(OBJS)
$(GITHUB_OBJS): $(OBJS)
$(REDDIT_OBJS): $(OBJS)
$(SLACK_OBJS): $(OBJS)

$(OBJS): | $(OBJDIR)

$(OBJDIR): | $(SPECSCODE_DIR)
	@ mkdir -p $(OBJDIR)/$(COMMON_DIR)/third-party \
	           $(OBJDIR)/$(CEEUTILS_DIR)           \
	           $(OBJDIR)/$(SPECSCODE_DIR)
	@ mv $(SPECS_DIR)/specs-code $(SPECSCODE_DIR)
	@ mv $(SPECS_DIR)/obj/* $(OBJDIR)/$(SPECSCODE_DIR)
	@ cp $(CEEUTILS_DIR)/obj/* $(OBJDIR)/$(CEEUTILS_DIR)
$(SPECSCODE_DIR): | $(CEEUTILS_DIR)
	@ $(MAKE) -C $(SPECS_DIR) clean
	@ $(MAKE) -C $(SPECS_DIR) build
$(CEEUTILS_DIR):
	./scripts/get-cee-utils.sh
	@ $(MAKE) -C $@

install:
	mkdir -p $(PREFIX)/lib/
	mkdir -p $(PREFIX)/include/orca
	install -d $(PREFIX)/lib/
	install -m 644 $(LIBDISCORD) $(PREFIX)/lib/
	install -m 644 $(LIBGITHUB) $(PREFIX)/lib/
	install -d $(PREFIX)/include/orca/
	install -m 644 *.h $(CEEUTILS_DIR)/*.h $(COMMON_DIR)/*.h $(COMMON_DIR)/**/*.h $(PREFIX)/include/orca/
	install -d $(PREFIX)/include/orca/$(SPECSCODE_DIR)/discord/
	install -m 644 $(SPECSCODE_DIR)/discord/*.h $(PREFIX)/include/orca/$(SPECSCODE_DIR)/discord/
	install -d $(PREFIX)/include/orca/$(SPECSCODE_DIR)/github/
	install -m 644 $(SPECSCODE_DIR)/github/*.h $(PREFIX)/include/orca/$(SPECSCODE_DIR)/github/

echo:
	@ echo -e 'CC: $(CC)\n'
	@ echo -e 'PREFIX: $(PREFIX)\n'
	@ echo -e 'OBJS: $(OBJS)\n'
	@ echo -e 'DISCORD_SRC: $(DISCORD_SRC)\n'
	@ echo -e 'DISCORD_OBJS: $(DISCORD_OBJS)\n'
	@ echo -e 'DISCORD_SPECS: $(DISCORD_SPECS)\n'

clean: 
	rm -rf $(OBJDIR)
	rm -rf $(LIBDIR)
	rm -rf $(SPECSCODE_DIR)
	@ $(MAKE) -C $(TEST_DIR) clean
	@ $(MAKE) -C $(EXAMPLES_DIR) clean

purge: clean
	rm -rf $(LIBDIR)
	rm -rf $(CEEUTILS_DIR)
	@ $(MAKE) -C $(SPECS_DIR) clean

.PHONY: all test examples install echo clean purge
