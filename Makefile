PREFIX ?= /usr/local
SHELL  := /bin/bash

CC     ?= gcc
OBJDIR := obj
LIBDIR := lib

# common/utils
CEE_UTILS_DIR  := cee-utils
CEE_UTILS_SRC  := $(wildcard $(CEE_UTILS_DIR)/*.c) 
CEE_UTILS_OBJS := $(CEE_UTILS_SRC:%.c=$(OBJDIR)/%.o)

COMMON_DIR  := common
COMMON_SRC  := $(wildcard $(COMMON_DIR)/*.c) $(wildcard $(COMMON_DIR)/**/*.c)
COMMON_OBJS := $(COMMON_SRC:%.c=$(OBJDIR)/%.o)

# Specs
SPECS_RDIR := specs
SPECS_WDIR := specs-code
SPECS_JSON := $(sort $(wildcard $(SPECS_RDIR)/*/*.json))
SPECS_APIS := $(sort $(patsubst $(SPECS_RDIR)/%/, %, $(dir $(SPECS_JSON))))

# Specs code-generator dependencies
SPECSDEPS_OBJDIR  := specs_obj
SPECSDEPS_SRC     := $(CEE_UTILS_DIR)/cee-utils.c   \
                     $(CEE_UTILS_DIR)/json-actor.c  \
                     $(CEE_UTILS_DIR)/ntl.c         \
                     $(CEE_UTILS_DIR)/json-string.c \
                     $(CEE_UTILS_DIR)/log.c         \
                     $(SPECS_RDIR)/specs-gen.c
SPECSDEPS_OBJS    := $(SPECSDEPS_SRC:%.c=$(SPECSDEPS_OBJDIR)/%.o)


# APIs objs
DISCORD_SRC  := $(wildcard discord-*.c $(SPECS_WDIR)/discord/*.c)
DISCORD_OBJS := $(DISCORD_SRC:%.c=$(OBJDIR)/%.o)
GITHUB_SRC   := $(wildcard github-*.c $(SPECS_WDIR)/github/*.c)
GITHUB_OBJS  := $(GITHUB_SRC:%.c=$(OBJDIR)/%.o)
REDDIT_SRC   := $(wildcard reddit-*.c $(SPECS_WDIR)/reddit/*.c)
REDDIT_OBJS  := $(REDDIT_SRC:%.c=$(OBJDIR)/%.o)
SLACK_SRC    := $(wildcard slack-*.c)
SLACK_OBJS   := $(SLACK_SRC:%.c=$(OBJDIR)/%.o)

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
LIBDISCORD := $(LIBADDONS) $(LIBDIR)/libdiscord.a
LIBGITHUB  := $(LIBADDONS) $(LIBDIR)/libgithub.a
LIBREDDIT  := $(LIBADDONS) $(LIBDIR)/libreddit.a
LIBSLACK   := $(LIBADDONS) $(LIBDIR)/libslack.a

EXAMPLES_DIR   := examples
EXAMPLES_SRC   := $(wildcard $(EXAMPLES_DIR)/bot-*.c)
EXAMPLES_EXES  := $(patsubst %.c, %.out, $(EXAMPLES_SRC))

BOTX_DIR  := botx
BOTX_SRC  := $(wildcard $(BOTX_DIR)/bot-*.c)
BOTX_EXES := $(patsubst %.c, %.bx, $(BOTX_SRC))

TEST_DIR  := test
TEST_SRC  := $(wildcard $(TEST_DIR)/test-*.c)
TEST_EXES := $(filter %.out, $(TEST_SRC:.c=.out))


LIBS_CFLAGS  += -I./mujs
LIBS_LDFLAGS += -L./$(LIBDIR) -lm

CFLAGS += -O0 -g -pthread                                	\
          -Wall -Wno-unused-function                      \
          -I. -I./$(CEE_UTILS_DIR)                        \
          -I./$(COMMON_DIR) -I./$(COMMON_DIR)/third-party \
          -DLOG_USE_COLOR

ifeq ($(addons),1)
	# prepare addon flags
	ADDONS_SRC      := $(wildcard add-ons/*.c)
	ADDONS_OBJS     := $(ADDONS_SRC:%.c=$(OBJDIR)/%.o)
	ADDONS_BOTS_SRC := $(wildcard add-ons/*_bots/*.c)
	LIBADDONS       := $(LIBDIR)/libaddons.a

	# include addon flags
	EXAMPLES_EXES += $(ADDONS_BOTS_SRC:%.c=%.out)
	LIBS_LDFLAGS  += -laddons
	CFLAGS        += -I./add-ons
endif

ifeq ($(BEARSSL),1)
	LIBS_LDFLAGS += -lbearssl -static
	CFLAGS += -DBEARSSL
else ifneq (,$(findstring $(CC),stensal-c sfc)) # ifeq stensal-c OR sfc
	LIBS_LDFLAGS += -lcurl-bearssl -lbearssl -static
	CFLAGS += -DBEARSSL
else
	LIBS_LDFLAGS += $(pkg-config --libs --cflags libcurl) -lcurl -lcrypto
	CFLAGS += -Wno-unused-but-set-variable
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

# for inserting newlines at the end of each foreach
# see https://stackoverflow.com/questions/29651388/insert-a-new-line-in-a-makefile-foreach-loop
blank :=
define \n

$(blank)
endef

# generic compilation
$(SPECSDEPS_OBJDIR)/%.o : %.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<
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
%.out: %.c mujs all_api_libs
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -o $@ $< $(LIBDISCORD_LDFLAGS) $(LIBGITHUB_LDFLAGS) $(LIBREDDIT_LDFLAGS) $(LIBSLACK_LDFLAGS) -lmujs -lsqlite3 $(LIBS_LDFLAGS)
%.bx: %.c mujs all_api_libs
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -o $@ $< $(LIBDISCORD_LDFLAGS) $(LIBSLACK_LDFLAGS) -lmujs -lsqlite3 $(LIBS_LDFLAGS)
%.bz:%.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -o $@ $< $(LIBS_LDFLAGS) 


all: discord github reddit slack
test: discord github reddit slack mujs $(TEST_EXES)

botx:
	@ $(MAKE) all mujs all_api_libs
	@ $(MAKE) $(BOTX_EXES)

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
$(SPECSDEPS_OBJS): | $(SPECSDEPS_OBJDIR)

echo:
	@ echo CC: $(CC)
	@ echo PREFIX: $(PREFIX)
	@ echo EXAMPLES_EXES: $(EXAMPLES_EXES)
	@ echo SPECS_JSON: $(SPECS_JSON)
	@ echo SPECSDEPS_OBJS: $(SPECSDEPS_OBJS)
	@ echo SPECSDEPS_OBJDIR: $(SPECSDEPS_OBJDIR)
	@ echo SPECS_APIS: $(SPECS_APIS)
	@ echo DISCORD_OBJS: $(DISCORD_OBJS)

specs_gen: $(CEE_UTILS_DIR) | $(SPECSDEPS_OBJS)
	@ $(MAKE) clean specsdeps_clean specs_clean
	@ $(MAKE) specs_code

specs_code: | specs-gen.out
	@ rm -rf $(SPECS_WDIR)/*/one-specs.h
	# Generate header files (specs-code/%/*.h)
	$(foreach var, $(SPECS_JSON), \
	    ./bin/specs-gen.out \
			    -h \
			    -o $(patsubst $(SPECS_RDIR)/%, $(SPECS_WDIR)/%, $(var:%.json=%.h)) \
			    $(var) || exit;$(\n))
	# Generate source files (specs-code/%/*.c)
	$(foreach var, $(SPECS_JSON), \
	    ./bin/specs-gen.out \
			    -c \
			    -o $(patsubst $(SPECS_RDIR)/%, $(SPECS_WDIR)/%, $(var:%.json=%.c)) \
			    -i $(filter $(SPECS_APIS), $(subst /, ,$(dir $(var)))).h \
			    $(var) || exit;$(\n))
	# Generate single header (specs-code/%/one-specs.h)
	$(foreach var, $(SPECS_JSON), \
	    ./bin/specs-gen.out \
			    -O \
			    -a \
			    -o $(patsubst $(SPECS_RDIR)/%, $(SPECS_WDIR)/%, $(dir $(var))one-specs.h) \
			    $(var) || exit;$(\n))
	$(foreach var, $(SPECS_JSON), \
	    ./bin/specs-gen.out \
			    -E \
			    -a \
			    -o $(patsubst $(SPECS_RDIR)/%, $(SPECS_WDIR)/%, $(dir $(var))one-specs.h) \
			    $(var) || exit;$(\n))
	$(foreach var, $(SPECS_JSON), \
	    ./bin/specs-gen.out \
			    -S \
			    -a \
			    -o $(patsubst $(SPECS_RDIR)/%, $(SPECS_WDIR)/%, $(dir $(var))one-specs.h) \
			    $(var) || exit;$(\n))
	$(foreach var, $(SPECS_JSON), \
	    ./bin/specs-gen.out \
			    -F \
			    -a \
			    -o $(patsubst $(SPECS_RDIR)/%, $(SPECS_WDIR)/%, $(dir $(var))one-specs.h) \
			    $(var) || exit;$(\n))

specs-gen.out: cee_utils $(SPECSDEPS_OBJS) | $(SPECSDEPS_OBJDIR)
	$(CC) -o $@ $(SPECSDEPS_OBJS) -lm
	mkdir -p bin
	mv $@ ./bin

examples:
	@ $(MAKE) all
	@ $(MAKE) $(EXAMPLES_EXES)

$(CEE_UTILS_DIR):
	if [[ ! -d $@ ]]; then                \
	  ./scripts/get-cee-utils.sh || exit; \
	fi

$(OBJDIR) :
	mkdir -p $(OBJDIR)/$(CEE_UTILS_DIR)                           \
	         $(OBJDIR)/$(COMMON_DIR)/third-party                  \
	         $(addprefix $(SPECS_WDIR)/, $(SPECS_APIS))           \
	         $(addprefix $(OBJDIR)/$(SPECS_WDIR)/, $(SPECS_APIS)) \
	         $(OBJDIR)/$(TEST_DIR)                                \
	         $(OBJDIR)/add-ons

$(SPECSDEPS_OBJDIR) :
	mkdir -p $(SPECSDEPS_OBJDIR)/$(CEE_UTILS_DIR)          \
	         $(SPECSDEPS_OBJDIR)/$(COMMON_DIR)/third-party \
	         $(SPECSDEPS_OBJDIR)/$(SPECS_RDIR)

$(LIBDIR) :
	mkdir -p $(LIBDIR)

all_api_libs : $(LIBDISCORD) $(LIBGITHUB) $(LIBREDDIT) $(LIBSLACK) $(LIBADDONS)

# API libraries compilation
$(LIBDISCORD) : $(CEE_UTILS_OBJS) $(COMMON_OBJS) $(DISCORD_OBJS) | $(LIBDIR)
	$(AR) -cqsv $@ $?
$(LIBGITHUB) : $(CEE_UTILS_OBJS) $(COMMON_OBJS) $(GITHUB_OBJS) | $(LIBDIR)
	$(AR) -cqsv $@ $?
$(LIBREDDIT) : $(CEE_UTILS_OBJS) $(COMMON_OBJS) $(REDDIT_OBJS) | $(LIBDIR)
	$(AR) -cqsv $@ $?
$(LIBSLACK) : $(CEE_UTILS_OBJS) $(COMMON_OBJS) $(SLACK_OBJS) | $(LIBDIR)
	$(AR) -cqsv $@ $?
$(LIBADDONS) : $(CEE_UTILS_OBJS) $(COMMON_OBJS) $(ADDONS_OBJS) | $(LIBDIR)
	$(AR) -cqsv $@ $?

mujs:
	$(MAKE) -C mujs
	mkdir -p $(LIBDIR)
	cp mujs/build/release/libmujs.a $(LIBDIR)

install :
	mkdir -p $(PREFIX)/lib/
	mkdir -p $(PREFIX)/include/orca
	install -d $(PREFIX)/lib/
	install -m 644 $(LIBDISCORD) $(PREFIX)/lib/
	install -m 644 $(LIBGITHUB) $(PREFIX)/lib/
	install -d $(PREFIX)/include/orca/
	install -m 644 *.h $(CEE_UTILS_DIR)/*.h $(COMMON_DIR)/*.h $(COMMON_DIR)/**/*.h $(PREFIX)/include/orca/
	install -d $(PREFIX)/include/orca/$(SPECS_WDIR)/discord/
	install -m 644 $(SPECS_WDIR)/discord/*.h $(PREFIX)/include/orca/$(SPECS_WDIR)/discord/
	install -d $(PREFIX)/include/orca/$(SPECS_WDIR)/github/
	install -m 644 $(SPECS_WDIR)/github/*.h $(PREFIX)/include/orca/$(SPECS_WDIR)/github/

specs_clean :
	rm -rf $(SPECS_WDIR)
specsdeps_clean :
	rm -rf $(SPECSDEPS_OBJDIR) bin/*
clean : 
	rm -rf $(OBJDIR) *.out $(TEST_DIR)/*.out $(EXAMPLES_DIR)/*.out
	rm -rf $(BOTX_DIR)/*.bx
	$(MAKE) -C mujs clean
	rm -rf $(LIBDIR)
purge : clean
	rm -rf $(LIBDIR)
	rm -rf $(SPECSDEPS_OBJDIR)
	rm -rf $(CEE_UTILS_DIR)

.PHONY : all install clean purge mujs examples botx
.ONESHELL :
