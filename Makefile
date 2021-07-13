CC           ?= gcc
ACC          ?= gcc
OBJDIR	     := obj
LIBDIR	     := lib
SPECSDIR     := specs-code
ACTOR_OBJDIR := actor_obj

PREFIX ?= /usr/local
SHELL  := /bin/bash

# common/utils src
CEE_UTILS_SRC  := $(wildcard cee-utils/*.c) 
COMMON_SRC     := $(wildcard common/*.c) $(wildcard common/**/*.c)

# API specific src
DISCORD_SRC := $(wildcard discord-*.c)
GITHUB_SRC  := $(wildcard github-*.c)
REDDIT_SRC  := $(wildcard reddit-*.c)

# DB src
DB_SRC      := $(wildcard sqlite3/*.c)

# specs src
SPECS      	 := $(sort $(wildcard specs/*/*.json))
SPECS_SRC    := $(patsubst specs/%, $(SPECSDIR)/%, $(SPECS:%.json=%.c))
SPECS_SUBDIR := $(sort $(patsubst specs/%, %, $(dir $(SPECS))))

# generated code src
ACTOR_GEN_SRC = cee-utils/cee-utils.c   \
				        cee-utils/json-actor.c  \
				        cee-utils/ntl.c 			  \
				        cee-utils/json-string.c \
				        cee-utils/json-scanf.c 	\
				        cee-utils/json-struct.c \
				        cee-utils/json-printf.c \
				        cee-utils/log.c         \
				        specs/specs-gen.c


DB_OBJS        := $(DB_SRC:%=$(OBJDIR)/%.o)
SPECS_OBJS     := $(SPECS_SRC:%=$(OBJDIR)/%.o)
ACTOR_GEN_OBJS := $(ACTOR_GEN_SRC:%=$(ACTOR_OBJDIR)/%.o)

# utils objects
CEE_UTILS_OBJS  := $(CEE_UTILS_SRC:%=$(OBJDIR)/%.o)
COMMON_OBJS     := $(COMMON_SRC:%=$(OBJDIR)/%.o)

# API objects
DISCORD_OBJS := $(DISCORD_SRC:%=$(OBJDIR)/%.o)
GITHUB_OBJS  := $(GITHUB_SRC:%=$(OBJDIR)/%.o)
REDDIT_OBJS  := $(REDDIT_SRC:%=$(OBJDIR)/%.o)

# objects
ORCA_OBJS := $(CEE_UTILS_OBJS) $(COMMON_OBJS) $(DISCORD_OBJS) $(GITHUB_OBJS) $(REDDIT_OBJS)


BOT_SRC  := $(wildcard bots/bot-*.c)
BOT_EXES := $(patsubst %.c, %.exe, $(BOT_SRC))

BOTX_SRC  := $(wildcard botx/bot-*.c)
BOTX_EXES := $(patsubst %.c, %.bx, $(BOTX_SRC))

TEST_SRC  := $(wildcard test/test-*.c)
TEST_EXES := $(filter %.exe, $(TEST_SRC:.c=.exe))


# API libs cflags
LIBDISCORD_CFLAGS	:=
LIBGITHUB_CFLAGS	:=
LIBREDDIT_CFLAGS	:=

# API libs ldflags
LIBDISCORD_LDFLAGS := -ldiscord
LIBGITHUB_LDFLAGS	 := -lgithub
LIBREDDIT_LDFLAGS	 := -lreddit

# API libs
LIBDISCORD := $(LIBDIR)/libdiscord.a
LIBGITHUB  := $(LIBDIR)/libgithub.a
LIBREDDIT  := $(LIBDIR)/libreddit.a

# general-purpose flags
LIBORCA_CFLAGS  := $(LIBDISCORD_CFLAGS) $(LIBGITHUB_CFLAGS) $(LIBREDDIT_CFLAGS)
LIBORCA_LDFLAGS := $(LIBDISCORD_LDFLAGS) $(LIBGITHUB_LDFLAGS) $(LIBREDDIT_LDFLAGS)
LIBORCA         := $(LIBDISCORD) $(LIBGITHUB) $(LIBREDDIT)

LIBS_CFLAGS  += $(LIBORCA_CFLAGS) -I./mujs -I./sqlite3
LIBS_LDFLAGS += -L./$(LIBDIR) $(LIBORCA_LDFLAGS) -lpthread

CFLAGS += -Wall -std=c11 -O0 -g \
	-Wno-unused-function \
	-I. -I./cee-utils -I./common -I./common/third-party -DLOG_USE_COLOR

ifeq ($(BEARSSL),1)
	LIBS_LDFLAGS += -lbearssl -static
	CFLAGS += -DBEARSSL
else ifeq ($(CC),stensal-c)
	LIBS_LDFLAGS += -lcurl-bearssl -lbearssl -static
	CFLAGS += -DBEARSSL
else ifeq ($(CC),sfc)
	LIBS_LDFLAGS += -lcurl-bearssl -lbearssl -static
	CFLAGS += -DBEARSSL
else
	LIBS_LDFLAGS += $(pkg-config --libs --cflags libcurl) -lcurl -lcrypto -lm
	CFLAGS += -Wno-unused-but-set-variable
endif

ifeq ($(static_debug),1)
	CFLAGS +=  -D_STATIC_DEBUG
else ifeq ($(static_debug),2) 
	CFLAGS +=  -D_STRICT_STATIC_DEBUG
else ifeq ($(static_debug),3) 
	CFLAGS +=  -D_STATIC_DEBUG -D_STRICT_STATIC_DEBUG
endif

ifeq ($(addons),1)
	# prepare addon flags
	ADDONS_SRC := $(wildcard add-ons/*.c)
	ADDONS_OBJS := $(ADDONS_SRC:%=$(OBJDIR)/%.o)
	ADDONS_BOT_SRC := $(wildcard add-ons/*_bots/*.c)
	LIBADDONS_LDFLAGS := -laddons
	LIBADDONS := $(LIBDIR)/libaddons.a

	# append addon flags
	ORCA_OBJS += $(ADDONS_OBJS)
	BOT_EXES += $(ADDONS_BOT_SRC:%.c=%.exe)
	LIBORCA_LDFLAGS += $(LIBADDONS_LDFLAGS)
	LIBORCA += $(LIBADDONS)
	CFLAGS += -I./add-ons
endif

ifeq ($(CC),stensal-c)
	CFLAGS += -D_DEFAULT_SOURCE
	D=$(shell dirname $(shell which stensal-c))
	DEST=$(patsubst %/stensal/bin,%,$(D))
	PREFIX=$(DEST)/usr
else ifeq ($(CC),sfc)
	CFLAGS += -D_DEFAULT_SOURCE
	D=$(shell dirname $(shell which sfc))
	DEST=$(patsubst %/stensal/bin,%,$(D))
	PREFIX=$(DEST)/usr
else
	CFLAGS += -fPIC -D_XOPEN_SOURCE=700
endif


.PHONY : install clean purge mujs
.ONESHELL:


all : mkdir get_cee_utils $(ORCA_OBJS) | bots

get_cee_utils:
	if [[ ! -d cee-utils ]]; then \
		./scripts/get-cee-utils.sh; \
	fi

cee_utils: mkdir get_cee_utils $(CEE_UTILS_OBJS)
common: mkdir $(COMMON_OBJS)
discord: mkdir $(DISCORD_OBJS) $(LIBDISCORD)
reddit: mkdir $(REDDIT_OBJS) $(LIBREDDIT)
github: mkdir $(GITHUB_OBJS)
db: mkdir $(DB_OBJS)

specs: mkdir $(SPECS_SRC) $(SPECS_OBJS)

echo:
	@echo BOT_EXES:     $(BOT_EXES)
	@echo ORCA_OBJS:   	$(ORCA_OBJS)
	@echo SPECS:        $(SPECS)
	@echo SPECS_SRC:    $(SPECS_SRC)
	@echo SPECS_OBJS:   $(SPECS_OBJS)
	@echo SPECS_SUBDIR: $(SPECS_SUBDIR)
	@echo DEST:         $(DEST)

##@todo should we split by categories (bot_discord, bot_github, etc)?
bots: $(BOT_EXES)
botx: mkdir cee_utils common discord | $(BOTX_EXES)

##@todo should we split by categories too ?
test: cee_utils common discord github reddit $(TEST_EXES)

mkdir :
	mkdir -p $(OBJDIR)/cee-utils
	mkdir -p $(ACTOR_OBJDIR)/cee-utils
	mkdir -p $(ACTOR_OBJDIR)/common/third-party  $(ACTOR_OBJDIR)/specs
	mkdir -p $(OBJDIR)/common/third-party $(LIBDIR)
	mkdir -p $(addprefix $(SPECSDIR)/, $(SPECS_SUBDIR)) $(addprefix $(OBJDIR)/$(SPECSDIR)/, $(SPECS_SUBDIR))
	mkdir -p $(OBJDIR)/test
	mkdir -p $(OBJDIR)/sqlite3 
	mkdir -p $(OBJDIR)/add-ons


all_headers: $(SPECS)
	rm -rf $(SPECSDIR)/*/all_*
	$(foreach var, $(SPECS),./bin/actor-gen.exe -S -a -o $(patsubst specs/%, $(SPECSDIR)/%, $(dir $(var))all_structs.h) $(var);)
	$(foreach var, $(SPECS),./bin/actor-gen.exe -E -a -o $(patsubst specs/%, $(SPECSDIR)/%, $(dir $(var))all_enums.h) $(var);)
	$(foreach var, $(SPECS),./bin/actor-gen.exe -F -a -o $(patsubst specs/%, $(SPECSDIR)/%, $(dir $(var))all_functions.h) $(var);)
	$(foreach var, $(SPECS),./bin/actor-gen.exe -O -a -o $(patsubst specs/%, $(SPECSDIR)/%, $(dir $(var))all_opaque_struct.h) $(var);)
	$(foreach var, $(SPECS),./bin/actor-gen.exe -c -o $(patsubst specs/%, $(SPECSDIR)/%, $(var:%.json=%.c)) $(var);)
	$(foreach var, $(SPECS),./bin/actor-gen.exe -d -o $(patsubst specs/%, $(SPECSDIR)/%, $(var:%.json=%.h)) $(var);)


actor-gen.exe: mkdir $(ACTOR_GEN_OBJS)
	$(ACC) -o $@ $(ACTOR_GEN_OBJS) -lm
	mkdir -p bin
	mv $@ ./bin

#generic compilation
$(ACTOR_OBJDIR)/%.c.o : %.c
	$(ACC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<
$(OBJDIR)/%.c.o : %.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<
%.bx:%.c $(LIBORCA) mujs
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -o $@ $< $(LIBS_LDFLAGS) -lmujs -lsqlite3
%.bz:%.c $(LIBORCA) mujs 
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -o $@ $< $(LIBS_LDFLAGS) 
%.exe:%.c $(LIBORCA) mujs
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -o $@ $< $(LIBS_LDFLAGS) -lmujs


$(LIBORCA) : $(LIBDISCORD) $(LIBGITHUB) $(LIBREDDIT) $(LIBADDONS)

# API libraries compilation
$(LIBDISCORD) : $(CEE_UTILS_OBJS) $(COMMON_OBJS) $(DISCORD_OBJS) $(SPECS_OBJS)
	$(AR) -cvq $@ $^
$(LIBGITHUB) : $(CEE_UTILS_OBJS) $(COMMON_OBJS) $(GITHUB_OBJS) $(SPECS_OBJS)
	$(AR) -cvq $@ $^
$(LIBREDDIT) : $(CEE_UTILS_OBJS) $(COMMON_OBJS) $(REDDIT_OBJS) $(SPECS_OBJS)
	$(AR) -cvq $@ $^
$(LIBADDONS) : $(CEE_UTILS_OBJS) $(COMMON_OBJS) $(ADDONS_OBJS) $(SPECS_OBJS)
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
	install -d $(PREFIX)/include/orca/
	install -m 644 *.h cee-utils/*.h common/*.h common/**/*.h $(PREFIX)/include/orca/
	install -d $(PREFIX)/include/orca/$(SPECSDIR)/discord/
	install -m 644 $(SPECSDIR)/discord/*.h $(PREFIX)/include/orca/$(SPECSDIR)/discord/

specs_clean :
	rm -rf $(SPECSDIR)
clean_actor_gen:
	rm -rf $(ACTOR_OBJDIR) bin/*
clean : 
	rm -rf $(OBJDIR) *.exe test/*.exe bots/*.exe
	rm -rf botx/*.bx
	rm -rf $(LIBDIR)
purge : clean
	rm -rf $(LIBDIR)
	rm -rf $(ACTOR_OBJDIR)
	rm -rf cee-utils
