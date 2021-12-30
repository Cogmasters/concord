PREFIX ?= /usr/local

CC     ?= gcc
OBJDIR := obj
LIBDIR := lib

SPECS_DIR     := specs
SPECSCODE_DIR := specs-code
SPECS_MAKE    := $(SPECS_DIR)/specs.mk

# common/utils
CEE_UTILS_DIR  := cee-utils
CEE_UTILS_SRC  := $(wildcard $(CEE_UTILS_DIR)/*.c) 
CEE_UTILS_OBJS := $(CEE_UTILS_SRC:%.c=$(OBJDIR)/%.o)

COMMON_DIR  := common
COMMON_SRC  := $(wildcard $(COMMON_DIR)/*.c $(COMMON_DIR)/**/*.c)
COMMON_OBJS := $(COMMON_SRC:%.c=$(OBJDIR)/%.o)

# APIs src
DISCORD_SRC = $(wildcard discord-*.c $(SPECSCODE_DIR)/discord/*.c)
GITHUB_SRC  = $(wildcard github-*.c $(SPECSCODE_DIR)/github/*.c)
REDDIT_SRC  = $(wildcard reddit-*.c $(SPECSCODE_DIR)/reddit/*.c)
SLACK_SRC   = $(wildcard slack-*.c $(SPECSCODE_DIR)/slack/*.c)

# APIs objs
DISCORD_OBJS = $(DISCORD_SRC:%.c=$(OBJDIR)/%.o)
GITHUB_OBJS  = $(GITHUB_SRC:%.c=$(OBJDIR)/%.o)
REDDIT_OBJS  = $(REDDIT_SRC:%.c=$(OBJDIR)/%.o)
SLACK_OBJS   = $(SLACK_SRC:%.c=$(OBJDIR)/%.o)

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

EXAMPLES_DIR   := examples
EXAMPLES_SRC   := $(wildcard $(EXAMPLES_DIR)/bot-*.c)
EXAMPLES_EXES  := $(patsubst %.c, %.out, $(EXAMPLES_SRC))

TEST_DIR  := test
TEST_SRC  := $(wildcard $(TEST_DIR)/test-*.c)
TEST_EXES := $(filter %.out, $(TEST_SRC:.c=.out))

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
$(EXAMPLES_DIR)/%.out: $(EXAMPLES_DIR)/%.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -o $@ $< $(LIBDISCORD_LDFLAGS) $(LIBGITHUB_LDFLAGS) $(LIBREDDIT_LDFLAGS) $(LIBSLACK_LDFLAGS) $(LIBS_LDFLAGS)
%.out: %.c all_api_libs
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -o $@ $< $(LIBDISCORD_LDFLAGS) $(LIBGITHUB_LDFLAGS) $(LIBREDDIT_LDFLAGS) $(LIBSLACK_LDFLAGS) $(LIBS_LDFLAGS)

all: $(SPECSCODE_DIR)
	$(MAKE) discord github reddit slack

test: all $(TEST_EXES)

discord: common $(DISCORD_OBJS) $(LIBDISCORD)
github: common $(GITHUB_OBJS) $(LIBGITHUB)
reddit: common $(REDDIT_OBJS) $(LIBREDDIT)
slack: common $(SLACK_OBJS) $(LIBSLACK)

common: cee_utils $(COMMON_OBJS)
cee_utils: $(CEE_UTILS_OBJS) | $(CEE_UTILS_DIR)

$(CEE_UTILS_OBJS): | $(OBJDIR)
$(COMMON_OBJS):    | $(OBJDIR)
$(DISCORD_OBJS):   | $(OBJDIR)
$(GITHUB_OBJS):    | $(OBJDIR)
$(REDDIT_OBJS):    | $(OBJDIR)
$(SLACK_OBJS):     | $(OBJDIR)

specs_gen:
	@ $(MAKE) clean
	@ $(MAKE) -C $(SPECS_DIR) -f $(SPECS_MAKE) clean
	@ $(MAKE) -C $(SPECS_DIR) -f $(SPECS_MAKE)
	mv $(SPECS_DIR)/$(SPECSCODE_DIR) .

examples:
	@ $(MAKE) all
	@ $(MAKE) $(EXAMPLES_EXES)

$(SPECSCODE_DIR): specs_gen

$(CEE_UTILS_DIR):
	if [[ ! -d $@ ]]; then        \
	  ./scripts/get-cee-utils.sh; \
	fi

$(OBJDIR) :
	mkdir -p $(OBJDIR)/$(CEE_UTILS_DIR)                             \
	         $(OBJDIR)/$(COMMON_DIR)/third-party                    \
	         $(OBJDIR)/$(TEST_DIR)                                  \
					 $(addprefix $(OBJDIR)/, $(wildcard $(SPECSCODE_DIR)/*))

$(LIBDIR) :
	mkdir -p $(LIBDIR)

all_api_libs : $(LIBDISCORD) $(LIBGITHUB) $(LIBREDDIT) $(LIBSLACK)

# API libraries compilation
$(LIBDISCORD) : $(CEE_UTILS_OBJS) $(COMMON_OBJS) $(DISCORD_OBJS) | $(LIBDIR)
	$(AR) -cqsv $@ $?
$(LIBGITHUB) : $(CEE_UTILS_OBJS) $(COMMON_OBJS) $(GITHUB_OBJS) | $(LIBDIR)
	$(AR) -cqsv $@ $?
$(LIBREDDIT) : $(CEE_UTILS_OBJS) $(COMMON_OBJS) $(REDDIT_OBJS) | $(LIBDIR)
	$(AR) -cqsv $@ $?
$(LIBSLACK) : $(CEE_UTILS_OBJS) $(COMMON_OBJS) $(SLACK_OBJS) | $(LIBDIR)
	$(AR) -cqsv $@ $?

install :
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
	@ echo CC: $(CC)
	@ echo PREFIX: $(PREFIX)
	@ echo EXAMPLES_EXES: $(EXAMPLES_EXES)
	@ echo DISCORD_OBJS: $(DISCORD_OBJS)

clean : 
	rm -rf $(OBJDIR) *.out $(TEST_DIR)/*.out $(EXAMPLES_DIR)/*.out
	rm -rf $(LIBDIR)
	rm -rf $(SPECSCODE_DIR)
	make -C $(SPECS_DIR) -f specs.mk clean

purge : clean
	rm -rf $(LIBDIR)
	rm -rf $(CEE_UTILS_DIR)

.PHONY : all install clean purge examples
