PREFIX ?= /usr/local
SHELL  := /bin/bash
CC     ?= gcc

OBJDIR := obj
LIBDIR := lib

SPECS_DIR     := specs
SPECSCODE_DIR := specs-code

CEE_UTILS_DIR := cee-utils
COMMON_DIR    := common

EXAMPLES_DIR := examples
TEST_DIR     := test

SRC := $(CEE_UTILS_DIR)/cee-utils.c               \
       $(CEE_UTILS_DIR)/json-actor.c              \
       $(CEE_UTILS_DIR)/json-actor-boxed.c        \
       $(CEE_UTILS_DIR)/json-string.c             \
       $(CEE_UTILS_DIR)/log.c                     \
       $(CEE_UTILS_DIR)/logconf.c                 \
       $(CEE_UTILS_DIR)/ntl.c                     \
       $(COMMON_DIR)/common.c                     \
       $(COMMON_DIR)/work.c                       \
       $(COMMON_DIR)/user-agent.c                 \
       $(COMMON_DIR)/websockets.c                 \
       $(COMMON_DIR)/third-party/curl-websocket.c \
       $(COMMON_DIR)/third-party/threadpool.c
OBJS := $(SRC:%.c=$(OBJDIR)/%.o)

# APIs src
DISCORD_SRC = $(wildcard discord-*.c)
GITHUB_SRC  = $(wildcard github-*.c)
REDDIT_SRC  = $(wildcard reddit-*.c)
SLACK_SRC   = $(wildcard slack-*.c)

# APIs objs
DISCORD_OBJS = $(DISCORD_SRC:%.c=$(OBJDIR)/%.o)
GITHUB_OBJS  = $(GITHUB_SRC:%.c=$(OBJDIR)/%.o)
REDDIT_OBJS  = $(REDDIT_SRC:%.c=$(OBJDIR)/%.o)
SLACK_OBJS   = $(SLACK_SRC:%.c=$(OBJDIR)/%.o)

# APIs specs
DISCORD_SPECS = $(wildcard $(OBJDIR)/$(SPECSCODE_DIR)/discord/*.o)
GITHUB_SPECS  = $(wildcard $(OBJDIR)/$(SPECSCODE_DIR)/github/*.o)
REDDIT_SPECS  = $(wildcard $(OBJDIR)/$(SPECSCODE_DIR)/reddit/*.o)
SLACK_SPECS   = $(wildcard $(OBJDIR)/$(SPECSCODE_DIR)/slack/*.o)

# API libs cflags
LIBDISCORD_CFLAGS := 
LIBGITHUB_CFLAGS  :=
LIBREDDIT_CFLAGS  :=
LIBSLACK_CFLAGS   :=

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

CFLAGS += -O0 -g -pthread -Wall                           \
          -I. -I./$(CEE_UTILS_DIR)                        \
          -I./$(COMMON_DIR) -I./$(COMMON_DIR)/third-party \
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

# generic compilation
$(OBJDIR)/discord-%.o : discord-%.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $< $(LIBDISCORD_CFLAGS)
$(OBJDIR)/github-%.o : github-%.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $< $(LIBGITHUB_CFLAGS)
$(OBJDIR)/reddit-%.o : reddit-%.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $< $(LIBREDDIT_CFLAGS)
$(OBJDIR)/slack-%.o : slack-%.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $< $(LIBSLACK_CFLAGS)
$(OBJDIR)/%.o : %.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<

all: discord github reddit slack

test: all
	$(MAKE) -C $(TEST_DIR)

examples: all
	$(MAKE) -C $(EXAMPLES_DIR)

discord: $(LIBDISCORD)
github: $(LIBGITHUB)
reddit: $(LIBREDDIT)
slack: $(LIBSLACK)

$(DISCORD_OBJS): $(OBJS)
$(GITHUB_OBJS): $(OBJS)
$(REDDIT_OBJS): $(OBJS)
$(SLACK_OBJS): $(OBJS)
$(OBJS): | $(OBJDIR)

$(SPECSCODE_DIR): | $(CEE_UTILS_DIR)
	@ $(MAKE) -C $(SPECS_DIR) clean
	@ $(MAKE) -C $(SPECS_DIR) build

$(CEE_UTILS_DIR):
	if [[ ! -d $@ ]]; then        \
	  ./scripts/get-cee-utils.sh; \
	fi

$(OBJDIR): | $(SPECSCODE_DIR)
	mkdir -p $(OBJDIR)/$(CEE_UTILS_DIR)           \
	         $(OBJDIR)/$(COMMON_DIR)/third-party  \
	         $(OBJDIR)/$(SPECSCODE_DIR)
	mv $(SPECS_DIR)/specs-code $(SPECSCODE_DIR)
	mv $(SPECS_DIR)/obj/* $(OBJDIR)/$(SPECSCODE_DIR)

$(LIBDIR):
	mkdir -p $(LIBDIR)

# API libraries compilation
$(LIBDISCORD): $(OBJS) $(DISCORD_OBJS) | $(LIBDIR)
	$(AR) -cqsv $@ $? $(DISCORD_SPECS)
$(LIBGITHUB): $(OBJS) $(GITHUB_OBJS) | $(LIBDIR)
	$(AR) -cqsv $@ $? $(GITHUB_SPECS)
$(LIBREDDIT): $(OBJS) $(REDDIT_OBJS) | $(LIBDIR)
	$(AR) -cqsv $@ $? $(REDDIT_SPECS)
$(LIBSLACK): $(OBJS) $(SLACK_OBJS) | $(LIBDIR)
	$(AR) -cqsv $@ $? $(SLACK_SPECS)

install:
	mkdir -p $(PREFIX)/lib/
	mkdir -p $(PREFIX)/include/orca
	install -d $(PREFIX)/lib/
	install -m 644 $(LIBDISCORD) $(PREFIX)/lib/
	install -m 644 $(LIBGITHUB) $(PREFIX)/lib/
	install -d $(PREFIX)/include/orca/
	install -m 644 *.h $(CEE_UTILS_DIR)/*.h $(COMMON_DIR)/*.h $(COMMON_DIR)/**/*.h $(PREFIX)/include/orca/
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
	$(MAKE) -C $(SPECS_DIR) clean
	$(MAKE) -C $(TEST_DIR) clean
	$(MAKE) -C $(EXAMPLES_DIR) clean

purge: clean
	rm -rf $(LIBDIR)
	rm -rf $(CEE_UTILS_DIR)

.PHONY: all test examples install echo clean purge
