CC           ?= gcc
OBJDIR	     := obj
LIBDIR	     := lib
ACTOR_OBJDIR := actor_obj

ACC          ?= gcc


COMMON_SRC  := $(wildcard common/*.c) $(wildcard common/**/*.c)
DISCORD_SRC := $(wildcard discord-*.c)
SLACK_SRC   := $(wildcard slack-*.c)
GITHUB_SRC  := $(wildcard github-*.c)
REDDIT_SRC  := $(wildcard reddit-*.c)

DB_SRC      := $(wildcard sqlite3/*.c)
ADD_ONS_SRC := $(wildcard add-ons/*.c)

SPECS      := $(sort $(wildcard specs/*.json))
__SPECS    := $(addprefix specs-code/, $(notdir $(SPECS)))
SPECS_C    := $(__SPECS:%.json=%.c)
SPECS_H    := $(__SPECS:%.json=%.h)

ACTOR_GEN_SRC = common/orka-utils.c 	\
				common/json-actor.c 	\
				common/ntl.c 			\
				common/json-string.c 	\
				common/json-scanf.c 	\
				common/json-struct.c 	\
				common/json-printf.c 	\
				test/test-json-struct-gen.c

ACTOR_GEN_OBJS := $(ACTOR_GEN_SRC:%=$(ACTOR_OBJDIR)/%.o)

COMMON_OBJS  := $(COMMON_SRC:%=$(OBJDIR)/%.o)
DISCORD_OBJS := $(DISCORD_SRC:%=$(OBJDIR)/%.o)
SLACK_OBJS   := $(SLACK_SRC:%=$(OBJDIR)/%.o)
GITHUB_OBJS  := $(GITHUB_SRC:%=$(OBJDIR)/%.o)
REDDIT_OBJS  := $(REDDIT_SRC:%=$(OBJDIR)/%.o)
SPECS_OBJS   := $(SPECS_C:%=$(OBJDIR)/%.o)
DB_OBJS      := $(DB_SRC:%=$(OBJDIR)/%.o)
ADD_ONS_OBJS := $(ADD_ONS_SRC:%=$(OBJDIR)/%.o)

OBJS := $(COMMON_OBJS) $(DISCORD_OBJS) $(SLACK_OBJS) $(GITHUB_OBJS) $(REDDIT_OBJS)

ifeq ($(addons),0)
	CFLAGS += -D_DISCORD_ADD_ONS
	OBJS += $(ADD_ONS_OBJS)
endif


BOT_SRC  := $(wildcard bots/bot-*.c)
BOT_EXES := $(patsubst %.c, %.exe, $(BOT_SRC))

BOTX_SRC  := $(wildcard botx/bot-*.c)
BOTX_EXES := $(patsubst %.c, %.bx, $(BOTX_SRC))

BOTZ_SRC  := $(wildcard add-ons/bots/bot-*.c)
BOTZ_EXES := $(patsubst %.c, %.bz, $(BOTZ_SRC))

TEST_SRC  := $(wildcard test/test-*.cpp test/test-*.c)
TEST_EXES := $(filter %.exe, $(TEST_SRC:.cpp=.exe) $(TEST_SRC:.c=.exe))

DISCORD_CFLAGS	:= -I./ -I./mujs  -I./sqlite3 -I./add-ons
DISCORD_LDFLAGS	:= -L./$(LIBDIR) -ldiscord -lcurl -lpthread

ifeq ($(BEARSSL),1)
	DISCORD_LDFLAGS += -lbearssl -static
	CFLAGS += -DBEARSSL -DBEAR_SSL
else ifeq ($(MBEDTLS),1)
	DISCORD_LDFLAGS += -lmbedx509 -lmbedtls -lmbedcrypto -static
	CFLAGS += -DMBEDTLS
else ifeq ($(CC),stensal-c)
	DISCORD_LDFLAGS += -lbearssl -static
	CFLAGS += -DBEARSSL
else
	DISCORD_LDFLAGS += $(pkg-config --libs --cflags libcurl) -lcrypto -lm
endif


LIBS_CFLAGS  := $(DISCORD_CFLAGS)
LIBS_LDFLAGS := $(DISCORD_LDFLAGS)

DISCORD   := $(LIBDIR)/libdiscord.a


CFLAGS += -Wall -std=c11 -O0 -g \
	-Wno-unused-function -Wno-unused-but-set-variable \
	-I. -I./common -I./common/third-party -DLOG_USE_COLOR

ifeq ($(release),1)
else
	CFLAGS +=  -D_STATIC_DEBUG
endif

ifeq ($(DEBUG_JSON),1)
	CFLAGS += -D_STRICT_STATIC_DEBUG
endif

ifeq ($(CC),stensal-c)
	CFLAGS += -D_DEFAULT_SOURCE
else
	CFLAGS += -fPIC -D_XOPEN_SOURCE=700
endif


PREFIX ?= /usr/local

.PHONY : install clean purge mujs


all : mkdir common discord | bot

common: mkdir $(COMMON_OBJS)
discord: mkdir $(DISCORD_OBJS) discord
slack: mkdir $(SLACK_OBJS)
github: mkdir $(GITHUB_OBJS)
reddit: mkdir $(REDDIT_OBJS)
db: mkdir $(DB_OBJS)

specs: mkdir $(SPECS_H) $(SPECS_C) $(SPECS_OBJS)

echo:
	@echo SPECS:      $(SPECS)
	@echo SPECS_H:    $(SPECS_H)
	@echo SPECS_C:    $(SPECS_C)
	@echo SPECS_OBJS: $(SPECS_OBJS)
	@echo BOTZ_SRC:   $(BOTZ_SRC)
	@echo BOTZ_EXES:  $(BOTZ_EXES)

bot: $(BOT_EXES) #@todo should we split by categories (bot_discord, bot_github, etc)?
botx: mkdir common discord | $(BOTX_EXES)
botz: mkdir common discord | $(BOTZ_EXES)

test: common discord slack github reddit $(TEST_EXES) #@todo should we split by categories too ?

mkdir :
	mkdir -p $(ACTOR_OBJDIR)/common  $(ACTOR_OBJDIR)/test bin
	mkdir -p $(OBJDIR)/common/third-party $(OBJDIR)/specs $(LIBDIR)
	mkdir -p $(OBJDIR)/test
	mkdir -p $(OBJDIR)/specs-code
	mkdir -p $(OBJDIR)/sqlite3 
	mkdir -p $(OBJDIR)/add-ons


#generic compilation


$(ACTOR_OBJDIR)/%.c.o : %.c
	$(ACC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<

$(OBJDIR)/%.c.o : %.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<


all_headers: $(SPECS)
	rm -rf specs-code/all_*
	$(foreach var, $(SPECS),./bin/actor-gen.exe -S -a -o specs-code/all_structs.h $(var);)
	$(foreach var, $(SPECS),./bin/actor-gen.exe -E -a -o specs-code/all_enums.h $(var);)
	$(foreach var, $(SPECS),./bin/actor-gen.exe -F -a -o specs-code/all_fun.h $(var);)
	$(foreach var, $(SPECS),./bin/actor-gen.exe -O -a -o specs-code/all_opaque_struct.h $(var);)
	$(foreach var, $(SPECS),./bin/actor-gen.exe -c -o specs-code/$(notdir $(var:.json=.c)) $(var);)
	$(foreach var, $(SPECS),./bin/actor-gen.exe -d -o specs-code/$(notdir $(var:.json=.h)) $(var);)


actor-gen.exe: mkdir $(ACTOR_GEN_OBJS)
	$(ACC) -o $@ $(ACTOR_GEN_OBJS) -lm
	@ mkdir -p bin
	mv $@ ./bin

#generic compilation
%.bx:%.c discord mujs
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -o $@ $< $(LIBS_LDFLAGS) -lmujs -lsqlite3

%.bz:%.c discord mujs $(ADD_ONS_OBJS)
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -o $@ $< $(ADD_ONS_OBJS) $(LIBS_LDFLAGS) 

%.exe:%.c discord
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -o $@ $< $(LIBS_LDFLAGS)

discord: mkdir $(OBJS) $(SPECS_OBJS)
	$(AR) -cvq $(DISCORD) $(OBJS) $(SPECS_OBJS)

mujs:
	$(MAKE) -C mujs
	mkdir -p $(LIBDIR)
	cp mujs/build/release/libmujs.a $(LIBDIR)

install : all
	mkdir -p $(PREFIX)/lib/
	mkdir -p $(PREFIX)/include/orca
	install -d $(PREFIX)/lib/
	install -m 644 $(DISCORD) $(PREFIX)/lib/
	install -d $(PREFIX)/include/orca/
	install -m 644 *.h common/*.h common/**/*.h $(PREFIX)/include/orca/
	install -d $(PREFIX)/include/orca/specs-code/
	install -m 644 specs-code/*.h  $(PREFIX)/include/orca/specs-code/

specs_clean :
	rm -f specs-code/*

clean : 
	rm -rf $(OBJDIR) *.exe test/*.exe bots/*.exe
	rm -rf botx/*.bx
	rm -rf $(LIBDIR)

clean_actor_gen:
	rm -rf $(ACTOR_OBJDIR) bin/*

purge : clean
	rm -rf $(LIBDIR)
	rm -rf $(ACTOR_OBJDIR)
