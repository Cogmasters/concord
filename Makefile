PREFIX ?= /usr/local
CC     ?= gcc

OBJDIR        := obj
LIBDIR        := lib
SPECS_DIR     := specs
SPECSCODE_DIR := specs-code
CEEUTILS_DIR  := cee-utils
COMMON_DIR    := common
THIRDP_DIR    := $(COMMON_DIR)/third-party
EXAMPLES_DIR  := examples
TEST_DIR      := test

CEEUTILS_SRC := $(CEEUTILS_DIR)/cee-utils.c        \
                $(CEEUTILS_DIR)/json-actor.c       \
                $(CEEUTILS_DIR)/json-actor-boxed.c \
                $(CEEUTILS_DIR)/json-string.c      \
                $(CEEUTILS_DIR)/log.c              \
                $(CEEUTILS_DIR)/logconf.c          \
                $(CEEUTILS_DIR)/ntl.c

COMMON_SRC   := $(COMMON_DIR)/common.c     \
                $(COMMON_DIR)/work.c       \
                $(COMMON_DIR)/user-agent.c \
                $(COMMON_DIR)/websockets.c

THIRDP_SRC   := $(THIRDP_DIR)/sha1.c           \
                $(THIRDP_DIR)/curl-websocket.c \
                $(THIRDP_DIR)/threadpool.c

SRC  := $(CEEUTILS_SRC) $(COMMON_SRC) $(THIRDP_SRC)
OBJS := $(SRC:%.c=$(OBJDIR)/%.o)

# APIs src
DISCORD_SRC := $(wildcard discord-*.c $(SPECSCODE_DIR)/discord/*.c)
GITHUB_SRC  := $(wildcard github-*.c $(SPECSCODE_DIR)/github/*.c)
REDDIT_SRC  := $(wildcard reddit-*.c $(SPECSCODE_DIR)/reddit/*.c)
SLACK_SRC   := $(wildcard slack-*.c $(SPECSCODE_DIR)/slack/*.c)

# APIs objs
DISCORD_OBJS := $(DISCORD_SRC:%.c=$(OBJDIR)/%.o)
GITHUB_OBJS  := $(GITHUB_SRC:%.c=$(OBJDIR)/%.o)
REDDIT_OBJS  := $(REDDIT_SRC:%.c=$(OBJDIR)/%.o)
SLACK_OBJS   := $(SLACK_SRC:%.c=$(OBJDIR)/%.o)

# API libs
LIBDISCORD := $(LIBDIR)/libdiscord.a
LIBGITHUB  := $(LIBDIR)/libgithub.a
LIBREDDIT  := $(LIBDIR)/libreddit.a
LIBSLACK   := $(LIBDIR)/libslack.a

CFLAGS += -O0 -g -pthread                                       \
          -I. -I$(CEEUTILS_DIR) -I$(COMMON_DIR) -I$(THIRDP_DIR) \
          -DLOG_USE_COLOR

WFLAGS += -Wall -Wextra

ifeq ($(static_debug),1)
	CFLAGS += -D_STATIC_DEBUG
else ifeq ($(static_debug),2) 
	CFLAGS += -D_STRICT_STATIC_DEBUG
else ifeq ($(static_debug),3) 
	CFLAGS += -D_STATIC_DEBUG -D_STRICT_STATIC_DEBUG
endif

ifeq (,$(findstring $(CC),stensal-c sfc)) # ifneq stensal-c AND sfc
	CFLAGS  += -fPIC
endif

$(OBJDIR)/$(CEEUTILS_DIR)/%.o : $(CEEUTILS_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJDIR)/$(THIRDP_DIR)/%.o : $(THIRDP_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJDIR)/%.o : %.c
	$(CC) $(CFLAGS) $(WFLAGS) -c -o $@ $<

all: | $(SPECSCODE_DIR)
	$(MAKE) discord github reddit slack

specs_gen: | $(CEEUTILS_DIR)
	@ $(MAKE) -C $(SPECS_DIR) clean
	@ $(MAKE) -C $(SPECS_DIR)
	@ rm -rf $(SPECSCODE_DIR)
	mv $(SPECS_DIR)/specs-code $(SPECSCODE_DIR)

cee_utils:
	./scripts/get-cee-utils.sh

test: all
	@ $(MAKE) -C $(TEST_DIR)

examples: all
	@ $(MAKE) -C $(EXAMPLES_DIR)

discord: $(LIBDISCORD) | $(SPECSCODE_DIR)
github: $(LIBGITHUB) | $(SPECSCODE_DIR)
reddit: $(LIBREDDIT) | $(SPECSCODE_DIR)
slack: $(LIBSLACK) | $(SPECSCODE_DIR)

# API libraries compilation
$(LIBDISCORD): $(DISCORD_OBJS) $(OBJS) | $(LIBDIR)
	$(AR) -cqsv $@ $?
$(LIBGITHUB): $(GITHUB_OBJS) $(OBJS) | $(LIBDIR)
	$(AR) -cqsv $@ $?
$(LIBREDDIT): $(REDDIT_OBJS) $(OBJS) | $(LIBDIR)
	$(AR) -cqsv $@ $?
$(LIBSLACK): $(SLACK_OBJS) $(OBJS) | $(LIBDIR)
	$(AR) -cqsv $@ $?

$(LIBDIR):
	@ mkdir -p $(LIBDIR)
$(SPECSCODE_DIR):
	@ $(MAKE) specs_gen
$(CEEUTILS_DIR):
	@ $(MAKE) cee_utils

$(DISCORD_OBJS): $(OBJS)
$(GITHUB_OBJS): $(OBJS)
$(REDDIT_OBJS): $(OBJS)
$(SLACK_OBJS): $(OBJS)

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	@ mkdir -p $(OBJDIR)/$(THIRDP_DIR)                                 \
	           $(OBJDIR)/$(CEEUTILS_DIR)                               \
	           $(addprefix $(OBJDIR)/, $(wildcard $(SPECSCODE_DIR)/*))

install:
	@ mkdir -p $(PREFIX)/lib/
	@ mkdir -p $(PREFIX)/include/orca
	install -d $(PREFIX)/lib/
	install -m 644 $(LIBDISCORD) $(PREFIX)/lib/
	install -m 644 $(LIBGITHUB) $(PREFIX)/lib/
	install -d $(PREFIX)/include/orca/
	install -m 644 *.h $(CEEUTILS_DIR)/*.h $(COMMON_DIR)/*.h             \
	               $(THIRDP_DIR)/*.h $(PREFIX)/include/orca/
	install -d $(PREFIX)/include/orca/$(SPECSCODE_DIR)/discord/
	install -m 644 $(SPECSCODE_DIR)/discord/*.h                          \
	               $(PREFIX)/include/orca/$(SPECSCODE_DIR)/discord/
	install -d $(PREFIX)/include/orca/$(SPECSCODE_DIR)/github/
	install -m 644 $(SPECSCODE_DIR)/github/*.h                           \
	               $(PREFIX)/include/orca/$(SPECSCODE_DIR)/github/

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
	rm -rf $(CEEUTILS_DIR)
	rm -rf $(SPECSCODE_DIR)

.PHONY: all test examples install echo clean purge
