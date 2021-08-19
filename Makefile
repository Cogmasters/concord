PREFIX ?= /usr/local
SHELL  := /bin/bash

CC     ?= gcc
OBJDIR := obj
LIBDIR := lib

# common/utils
CEE_UTILS_DIR  := cee-utils
CEE_UTILS_SRC  := $(wildcard $(CEE_UTILS_DIR)/*.c) 
CEE_UTILS_OBJS := $(CEE_UTILS_SRC:%=$(OBJDIR)/%.o)

COMMON_DIR  := common
COMMON_SRC  := $(wildcard $(COMMON_DIR)/*.c) $(wildcard $(COMMON_DIR)/**/*.c)
COMMON_OBJS := $(COMMON_SRC:%=$(OBJDIR)/%.o)

# Specs
SPECS_RDIR := specs
SPECS_WDIR := specs-code
SPECS_JSON := $(sort $(wildcard $(SPECS_RDIR)/*/*.json))
SPECS_APIS := $(sort $(patsubst $(SPECS_RDIR)/%, %, $(dir $(SPECS_JSON))))
SPECS_C    := $(patsubst $(SPECS_RDIR)/%, $(SPECS_WDIR)/%, $(SPECS_JSON:%.json=%.c))
SPECS_H    := $(patsubst $(SPECS_RDIR)/%, $(SPECS_WDIR)/%, $(SPECS_JSON:%.json=%.h))

# Specs code-generator dependencies
SPECSDEPS_OBJDIR  := specs_obj
SPECSDEPS_SRC     := $(CEE_UTILS_DIR)/cee-utils.c   \
                     $(CEE_UTILS_DIR)/json-actor.c  \
                     $(CEE_UTILS_DIR)/ntl.c         \
                     $(CEE_UTILS_DIR)/json-string.c \
                     $(CEE_UTILS_DIR)/json-scanf.c  \
                     $(CEE_UTILS_DIR)/json-printf.c \
                     $(CEE_UTILS_DIR)/log.c         \
                     $(SPECS_RDIR)/specs-gen.c
SPECSDEPS_OBJS    := $(SPECSDEPS_SRC:%=$(SPECSDEPS_OBJDIR)/%.o)


# APIs objs
DISCORD_SRC  = $(wildcard discord-*.c $(SPECS_WDIR)/discord/*.c)
DISCORD_OBJS = $(DISCORD_SRC:%=$(OBJDIR)/%.o)
GITHUB_SRC   = $(wildcard github-*.c) $(SPECS_WDIR)/github/*.c
GITHUB_OBJS  = $(GITHUB_SRC:%=$(OBJDIR)/%.o)
REDDIT_SRC   = $(wildcard reddit-*.c $(SPECS_WDIR)/reddit/*.c)
REDDIT_OBJS  = $(REDDIT_SRC:%=$(OBJDIR)/%.o)
SLACK_SRC    = $(wildcard slack-*.c)
SLACK_OBJS   = $(SLACK_SRC:%=$(OBJDIR)/%.o)

# API libs cflags
LIBDISCORD_CFLAGS :=
LIBGITHUB_CFLAG   :=
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

BOTS_DIR   := bots
BOTS_SRC   := $(wildcard $(BOTS_DIR)/bot-*.c)
BOTS_EXES  := $(patsubst %.c, %.exe, $(BOTS_SRC))

BOTX_DIR  := botx
BOTX_SRC  := $(wildcard $(BOTX_DIR)/bot-*.c)
BOTX_EXES := $(patsubst %.c, %.bx, $(BOTX_SRC))

TEST_DIR  := test
TEST_SRC  := $(wildcard $(TEST_DIR)/test-*.c)
TEST_EXES := $(filter %.exe, $(TEST_SRC:.c=.exe))


LIBS_CFLAGS  += -I./mujs
LIBS_LDFLAGS += -L./$(LIBDIR) -lpthread -lm

CFLAGS += -std=c11 -O0 -g                                 \
          -Wall -Wno-unused-function                      \
          -I. -I./$(CEE_UTILS_DIR)                        \
          -I./$(COMMON_DIR) -I./$(COMMON_DIR)/third-party \
          -DLOG_USE_COLOR

ifeq ($(addons),1)
	# prepare addon flags
	ADDONS_SRC      := $(wildcard add-ons/*.c)
	ADDONS_OBJS     := $(ADDONS_SRC:%=$(OBJDIR)/%.o)
	ADDONS_BOTS_SRC := $(wildcard add-ons/*_bots/*.c)
	LIBADDONS       := $(LIBDIR)/libaddons.a

	# include addon flags
	BOTS_EXES    += $(ADDONS_BOTS_SRC:%.c=%.exe)
	LIBS_LDFLAGS += -laddons
	CFLAGS       += -I./add-ons
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


# specs compilation
$(SPECSDEPS_OBJDIR)/%.c.o : %.c          # compile specs dependencies
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<
$(SPECS_WDIR)/%.c : $(SPECS_RDIR)/%.json # generate source files
	./bin/specs-gen.exe -c -o $@ $<
$(SPECS_WDIR)/%.h : $(SPECS_RDIR)/%.json # generate header files
	./bin/specs-gen.exe -d -o $@ $<
	./bin/specs-gen.exe -S -a -o $(dir $@)all_structs.h $<
	./bin/specs-gen.exe -E -a -o $(dir $@)all_enums.h $<
	./bin/specs-gen.exe -F -a -o $(dir $@)all_functions.h $<
	./bin/specs-gen.exe -O -a -o $(dir $@)all_opaque_struct.h $<

# generic compilation
$(OBJDIR)/%.c.o : %.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<
$(BOTS_DIR)/%.exe: $(BOTS_DIR)/%.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -o $@ $< $(LIBDISCORD_LDFLAGS) $(LIBGITHUB_LDFLAGS) $(LIBREDDIT_LDFLAGS) $(LIBSLACK_LDFLAGS) $(LIBS_LDFLAGS)
%.exe: %.c mujs all_api_libs
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
	@ echo BOTS_EXES: $(BOTS_EXES)
	@ echo SPECS_JSON: $(SPECS_JSON)
	@ echo SPECSDEPS_OBJS: $(SPECSDEPS_OBJS)
	@ echo SPECSDEPS_OBJDIR: $(SPECSDEPS_OBJDIR)
	@ echo SPECS_APIS: $(SPECS_APIS)

specs_gen :
	$(MAKE) clean specsdeps_clean specs_clean
	$(MAKE) specs_deps
	$(MAKE) specs_code
specs_code : specs_deps $(SPECS_C) $(SPECS_H)
specs_deps : cee_utils | $(SPECSDEPS_OBJS)
	@ $(CC) -o specs-gen.exe $(SPECSDEPS_OBJS) -lm
	@ mkdir -p bin && mv specs-gen.exe ./bin

bots:
	@ $(MAKE) all
	@ $(MAKE) $(BOTS_EXES)

$(CEE_UTILS_DIR):
	if [[ ! -d $@ ]]; then        \
	  ./scripts/get-cee-utils.sh; \
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
	$(AR) -cvq $@ $^
$(LIBGITHUB) : $(CEE_UTILS_OBJS) $(COMMON_OBJS) $(GITHUB_OBJS) | $(LIBDIR)
	$(AR) -cvq $@ $^
$(LIBREDDIT) : $(CEE_UTILS_OBJS) $(COMMON_OBJS) $(REDDIT_OBJS) | $(LIBDIR)
	$(AR) -cvq $@ $^
$(LIBSLACK) : $(CEE_UTILS_OBJS) $(COMMON_OBJS) $(SLACK_OBJS) | $(LIBDIR)
	$(AR) -cvq $@ $^
$(LIBADDONS) : $(CEE_UTILS_OBJS) $(COMMON_OBJS) $(ADDONS_OBJS) | $(LIBDIR)
	$(AR) -cvq $@ $^

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
	install -d $(PREFIX)/include/orca/$(SPECS_WDIR)/github/
	install -m 644 $(SPECS_WDIR)/github/*.h $(PREFIX)/include/orca/$(SPECS_WDIR)/github/

specs_clean :
	rm -rf $(SPECS_WDIR)
specsdeps_clean :
	rm -rf $(SPECSDEPS_OBJDIR) bin/*
clean : 
	rm -rf $(OBJDIR) *.exe $(TEST_DIR)/*.exe $(BOTS_DIR)/*.exe
	rm -rf $(BOTX_DIR)/*.bx
	$(MAKE) -C mujs clean
	rm -rf $(LIBDIR)
purge : clean
	rm -rf $(LIBDIR)
	rm -rf $(SPECSDEPS_OBJDIR)
	rm -rf $(CEE_UTILS_DIR)

.PHONY : all install clean purge mujs bots botx
.ONESHELL :
