CC	?= gcc
OBJDIR	:= obj
LIBDIR	:= lib


COMMON_SRC  := $(wildcard common/*.c)
ORKA_SRC    := $(wildcard orka-*.cpp)
DISCORD_SRC := $(wildcard discord-*.cpp)
GITHUB_SRC  := $(wildcard github-*.cpp)
SPECS       := $(wildcard specs/*.json)

SPECS_XX   := $(addprefix specs-code/, $(notdir $(SPECS)))
SPECS_CC   := $(SPECS_XX:%.json=%.cc)
SPECS_HH   := $(SPECS_XX:%.json=%.hh)

ACTOR_GEN_SRC = common/orka-utils.c common/json-actor.c \
	common/ntl.c common/json-string.c common/json-scanf.c \
	common/json-struct.c common/json-printf.c \
	test/test-json-struct-gen.c

ACTOR_GEN_OBJS := $(ACTOR_GEN_SRC:%=$(OBJDIR)/%.o)

COMMON_OBJS  := $(COMMON_SRC:%=$(OBJDIR)/%.o)
ORKA_OBJS    := $(ORKA_SRC:%=$(OBJDIR)/%.o)
DISCORD_OBJS := $(DISCORD_SRC:%=$(OBJDIR)/%.o)
GITHUB_OBJS  := $(GITHUB_SRC:%=$(OBJDIR)/%.o)
SPECS_OBJS   := $(SPECS_CC:%=$(OBJDIR)/%.o)

OBJS := $(COMMON_OBJS) $(DISCORD_OBJS) $(GITHUB_OBJS) $(ORKA_OBJS)

BOT_SRC := $(wildcard bots/bot-*.cpp)
BOT_EXES := $(patsubst %.cpp, %.exe, $(BOT_SRC))

TEST_SRC := $(wildcard test/test-*.cpp test/test-*.c)
TEST_EXES := $(filter %.exe, $(TEST_SRC:.cpp=.exe) $(TEST_SRC:.c=.exe))

LIBDISCORD_CFLAGS	:= -I./
LIBDISCORD_LDFLAGS	:= -L./$(LIBDIR) -ldiscord -lcurl

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
LIBS_LDFLAGS	:= $(LIBDISCORD_LDFLAGS)

LIBDISCORD	:= $(LIBDIR)/libdiscord.a


CFLAGS += -Wall -std=c11 -O0 -g -D_ORCA_DEBUG -D_GNU_SOURCE \
	-Wno-incompatible-pointer-types -Wno-unused-function \
	-I. -I./common 

CXXFLAGS += -Wall -std=c++03 -O0 -g -D_ORCA_DEBUG -D_GNU_SOURCE \
	-Wno-write-strings  -I. -I./common

GENFLAGS += -fpermissive

ifeq ($(DEBUG_JSON),1)
	CFLAGS += -D_ORCA_DEBUG_STRICT
	CXXFLAGS += -D_ORCA_DEBUG_STRICT
endif

ifeq ($(CC),stensal-c)
	CFLAGS += -D_DEFAULT_SOURCE
	CXXFLAGS += -D_DEFAULT_SOURCE
else
	CFLAGS += -fPIC -D_XOPEN_SOURCE=700
	CXXFLAGS += -fPIC -D_XOPEN_SOURCE=700
endif


PREFIX ?= /usr/local

.PHONY : all mkdir install clean purge


all : mkdir actor-gen.exe specs_hh common orka discord specs github bot

common: mkdir $(COMMON_OBJS)
orka: mkdir $(ORKA_OBJS)
discord: mkdir $(DISCORD_OBJS) libdiscord
github: mkdir $(GITHUB_OBJS)

specs_hh: $(SPECS_HH)
specs_cc: $(SPECS_CC)

specs: mkdir specs_hh specs_cc $(SPECS_OBJS)

echo:
	@echo SPECS:      $(SPECS)
	@echo SPECS_HH:   $(SPECS_HH)
	@echo SPECS_CC:   $(SPECS_CC)
	@echo SPECS_OBJS: $(SPECS_OBJS)

bot: $(BOT_EXES) #@todo should we split by categories (bot_discord, bot_github, etc)?
test: common orka discord github $(TEST_EXES) #@todo should we split by categories too ?

mkdir :
	mkdir -p bin $(OBJDIR) $(OBJDIR)/common $(OBJDIR)/specs $(LIBDIR)
	mkdir -p $(OBJDIR)/test
	mkdir -p specs-code  $(OBJDIR)/specs-code

$(OBJDIR)/common/curl-%.c.o : common/curl-%.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $< \
		-U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=1

#generic compilation


$(OBJDIR)/%.c.o : %.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<

$(OBJDIR)/%.cpp.o: %.cpp
	$(CXX) $(CXXFLAGS) $(LIBS_CFLAGS) -c -o $@ $<

specs-code/%.cc: specs/%.json
	./bin/actor-gen.exe -c -o $@ $<

specs-code/%.hh: specs/%.json
	./bin/actor-gen.exe -d -o $@ $<

$(OBJDIR)/%.cc.o: %.cc
	$(CXX) $(CXXFLAGS) $(LIBS_CFLAGS) $(GENFLAGS) -c -o $@ $< -Wno-unused-but-set-variable

actor-gen.exe: mkdir $(ACTOR_GEN_OBJS)
	$(CC) -o $@ $(ACTOR_GEN_OBJS) -lm
	mv $@ ./bin

#generic compilation
%.exe : %.c libdiscord
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -o $@ $< $(LIBS_LDFLAGS)
%.exe: %.cpp libdiscord
	$(CXX) $(CXXFLAGS) $(LIBS_CFLAGS) -o $@ $< $(LIBS_LDFLAGS)

libdiscord: mkdir $(OBJS) $(SPECS_OBJS)
	$(AR) -cvq $(LIBDISCORD) $(OBJS) $(SPECS_OBJS)


install : all
	install -d $(PREFIX)/lib/
	install -m 644 $(LIBDISCORD) $(PREFIX)/lib/
	install -d $(PREFIX)/include/
	install -m 644 *.h *.hpp common/*.h common/*.hpp $(PREFIX)/include/

specs_clean :
	rm -f specs/*.cc specs/*.h

clean : specs_clean
	rm -rf $(OBJDIR) *.exe test/*.exe bots/*.exe bin/*

purge : clean
	rm -rf $(LIBDIR)
