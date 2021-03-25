CC           ?= gcc
OBJDIR	     := obj
LIBDIR	     := lib
ACTOR_OBJDIR := actor_obj

ACC          ?= gcc


COMMON_SRC  := $(wildcard common/*.c)
ORKA_SRC    := $(wildcard orka-*.c)
DISCORD_SRC := $(wildcard discord-*.c)
GITHUB_SRC  := $(wildcard github-*.c)
SPECS       := $(shell ls specs/*.json)
DB_SRC      := $(wildcard sqlite3/*.c)
JSB_SRC     := $(wildcard jsB/*.c)

SPECS_XX   := $(addprefix specs-code/, $(notdir $(SPECS)))
SPECS_C    := $(SPECS_XX:%.json=%.c)
SPECS_H    := $(SPECS_XX:%.json=%.h)

ACTOR_GEN_SRC = common/orka-utils.c common/json-actor.c \
	common/ntl.c common/json-string.c common/json-scanf.c \
	common/json-struct.c common/json-printf.c \
	test/test-json-struct-gen.c

ACTOR_GEN_OBJS := $(ACTOR_GEN_SRC:%=$(ACTOR_OBJDIR)/%.o)

COMMON_OBJS  := $(COMMON_SRC:%=$(OBJDIR)/%.o)
ORKA_OBJS    := $(ORKA_SRC:%=$(OBJDIR)/%.o)
DISCORD_OBJS := $(DISCORD_SRC:%=$(OBJDIR)/%.o)
GITHUB_OBJS  := $(GITHUB_SRC:%=$(OBJDIR)/%.o)
SPECS_OBJS   := $(SPECS_C:%=$(OBJDIR)/%.o)
DB_OBJS      := $(DB_SRC:%=$(OBJDIR)/%.o)
JSB_OBJS      := $(JSB_SRC:%=$(OBJDIR)/%.o)

OBJS := $(COMMON_OBJS) $(DISCORD_OBJS) $(GITHUB_OBJS) $(ORKA_OBJS)

BOT_SRC  := $(wildcard bots/bot-*.c)
BOT_EXES := $(patsubst %.c, %.exe, $(BOT_SRC))

BOT1_SRC := $(wildcard bots-1/bot-*.c)
BOT1_EXES := $(patsubst %.c, %.b1, $(BOT1_SRC))

BOT2_SRC := $(wildcard bots-2/bot-*.c)
BOT2_EXES := $(patsubst %.c, %.b2, $(BOT2_SRC))

TEST_SRC := $(wildcard test/test-*.cpp test/test-*.c)
TEST_EXES := $(filter %.exe, $(TEST_SRC:.cpp=.exe) $(TEST_SRC:.c=.exe))

LIBDISCORD_CFLAGS	:= -I./ -I./mujs  -I./sqlite3 -I./jsB
LIBDISCORD_LDFLAGS	:= -L./$(LIBDIR) -ldiscord -lcurl -lpthread

ifeq ($(BEARSSL),1)
	LIBDISCORD_LDFLAGS += -lbearssl -static
	CFLAGS += -DBEARSSL -DBEAR_SSL
else ifeq ($(CC),stensal-c)
	LIBDISCORD_LDFLAGS += -lbearssl -static
	CFLAGS += -DBEARSSL
else
	LIBDISCORD_LDFLAGS += $(pkg-config --libs --cflags libcurl) -lcrypto -lm
endif


LIBS_CFLAGS	:= $(LIBDISCORD_CFLAGS)
LIBS_LDFLAGS := $(LIBDISCORD_LDFLAGS)

LIBDISCORD	:= $(LIBDIR)/libdiscord.a


CFLAGS += -Wall -std=c11 -O0 -g -D_GNU_SOURCE \
	-Wno-incompatible-pointer-types -Wno-unused-function -Wno-unused-but-set-variable \
	-I. -I./common 

ifeq ($(release),1)
else
	CFLAGS +=  -D_ORCA_DEBUG
endif

ifeq ($(DEBUG_JSON),1)
	CFLAGS += -D_ORCA_DEBUG_STRICT
endif

ifeq ($(CC),stensal-c)
	CFLAGS += -D_DEFAULT_SOURCE
else
	CFLAGS += -fPIC -D_XOPEN_SOURCE=700
endif


PREFIX ?= /usr/local

.PHONY : install clean purge mujs


all : mkdir common orka discord | bot

common: mkdir $(COMMON_OBJS)
orka: mkdir $(ORKA_OBJS)
discord: mkdir $(DISCORD_OBJS) libdiscord
github: mkdir $(GITHUB_OBJS)
db: mkdir $(DB_OBJS)

specs_h: $(SPECS_H)
specs_c: $(SPECS_C)

specs: mkdir specs_h specs_c $(SPECS_OBJS)

echo:
	@echo SPECS:     $(SPECS)
	@echo SPECS_H:   $(SPECS_H)
	@echo SPECS_C:   $(SPECS_C)
	@echo SPECS_OBJS: $(SPECS_OBJS)

bot: $(BOT_EXES) #@todo should we split by categories (bot_discord, bot_github, etc)?
bot1: $(BOT1_EXES)
bot2: $(BOT2_EXES)

test: common orka discord github $(TEST_EXES) #@todo should we split by categories too ?

mkdir :
	mkdir -p $(ACTOR_OBJDIR)/common  $(ACTOR_OBJDIR)/test bin
	mkdir -p $(OBJDIR) $(OBJDIR)/common $(OBJDIR)/specs $(LIBDIR)
	mkdir -p $(OBJDIR)/test $(OBJDIR)/jsB
	mkdir -p specs-code  $(OBJDIR)/specs-code
	mkdir -p $(OBJDIR)/sqlite3


#generic compilation


$(ACTOR_OBJDIR)/%.c.o : %.c
	$(ACC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<

$(OBJDIR)/%.c.o : %.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<


all_headers: $(SPECS)
	rm -rf specs-code/all_*
	$(foreach var, $(SPECS),./bin/actor-gen.exe -C -S -a -o specs-code/all_structs.h $(var);)
	$(foreach var, $(SPECS),./bin/actor-gen.exe -C -E -a -o specs-code/all_enums.h $(var);)
	$(foreach var, $(SPECS),./bin/actor-gen.exe -C -F -a -o specs-code/all_fun.h $(var);)
	$(foreach var, $(SPECS),./bin/actor-gen.exe -C -O -a -o specs-code/all_opaque_struct.h $(var);)

specs-code/%.c: specs/%.json
	./bin/actor-gen.exe -C -c -o $@ $<

specs-code/%.h: specs/%.json
	./bin/actor-gen.exe -C -d -o $@ $<

actor-gen.exe: mkdir $(ACTOR_GEN_OBJS)
	$(ACC) -o $@ $(ACTOR_GEN_OBJS) -lm
	@ mkdir -p bin
	mv $@ ./bin

#generic compilation
%.b1: %.c libdiscord db
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -o $@ $< $(LIBS_LDFLAGS) $(OBJDIR)/sqlite3/sqlite3.o

%.b2: %.c libdiscord mujs $(JSB_OBJS)
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -o $@ $< $(LIBS_LDFLAGS) -lmujs $(JSB_OBJS) -lsqlite3

%.exe : %.c libdiscord
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -o $@ $< $(LIBS_LDFLAGS)

libdiscord: mkdir $(OBJS) $(SPECS_OBJS)
	$(AR) -cvq $(LIBDISCORD) $(OBJS) $(SPECS_OBJS)


mujs:
	$(MAKE) -C mujs
	mkdir -p $(LIBDIR)
	cp mujs/build/release/libmujs.a $(LIBDIR)

install : all
	install -d $(PREFIX)/lib/
	install -m 644 $(LIBDISCORD) $(PREFIX)/lib/
	install -d $(PREFIX)/include/
	install -m 644 *.h *.hpp common/*.h $(PREFIX)/include/
	install -d $(PREFIX)/include/specs-code
	install -m 644 specs-code/*.hh  $(PREFIX)/include/specs-code

specs_clean :
	rm -f specs-code/*

clean : 
	rm -rf $(OBJDIR) *.exe test/*.exe bots/*.exe
	rm -rf bots-1/*.b1 bots-2/*.b2
	rm -rf $(LIBDIR)


clean_actor_gen:
	rm -rf $(ACTOR_OBJDIR) bin/*

purge : clean
	rm -rf $(LIBDIR)
	rm -rf $(ACTOR_OBJDIR)
