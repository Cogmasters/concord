CC	?= gcc
OBJDIR	:= obj
LIBDIR	:= lib


COMMON_SRC  := $(wildcard common/*.c)
ORKA_SRC    := $(wildcard orka-*.cpp)
DISCORD_SRC := $(wildcard discord-*.cpp)
GITHUB_SRC  := $(wildcard github-*.cpp)


COMMON_OBJS := $(COMMON_SRC:%=$(OBJDIR)/%.o)
ORKA_OBJS  := $(ORKA_SRC:%=$(OBJDIR)/%.o)
DISCORD_OBJS := $(DISCORD_SRC:%=$(OBJDIR)/%.o)
GITHUB_OBJS := $(GITHUB_SRC:%=$(OBJDIR)/%.o)

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


CFLAGS   += -Wall -Wextra -pedantic -std=c11 -O0 -g -D_ORCA_DEBUG -D_GNU_SOURCE \
		-Wno-unused-parameter -Wno-missing-field-initializers -I. -I./common

CXXFLAGS += -Wall -std=c++03 -O0 -g -D_ORCA_DEBUG -D_GNU_SOURCE \
		-Wno-write-strings  -I. -I./common


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


all : mkdir common orka discord github bot

common: mkdir $(COMMON_OBJS)
orka: mkdir $(ORKA_OBJS)
discord: mkdir $(DISCORD_OBJS) libdiscord
github: mkdir $(GITHUB_OBJS)

bot: $(BOT_EXES) #@todo should we split by categories (bot_discord, bot_github, etc)?
test: common orka discord github $(TEST_EXES) #@todo should we split by categories too ?


mkdir :
	mkdir -p $(OBJDIR) $(OBJDIR)/common $(LIBDIR)

$(OBJDIR)/common/curl-%.c.o : common/curl-%.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $< \
		-U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=1 -Wno-unused-function

#generic compilation
$(OBJDIR)/%.c.o : %.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<
$(OBJDIR)/%.cpp.o: %.cpp
	$(CXX) $(CXXFLAGS) $(LIBS_CFLAGS) -c -o $@ $<

#generic compilation
%.exe : %.c libdiscord
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -o $@ $< $(LIBS_LDFLAGS)
%.exe: %.cpp libdiscord
	$(CXX) $(CXXFLAGS) $(LIBS_CFLAGS) -o $@ $< $(LIBS_LDFLAGS)

libdiscord: mkdir $(OBJS)
	$(AR) -cvq $(LIBDISCORD) $(OBJS)


install : all
	install -d $(PREFIX)/lib/
	install -m 644 $(LIBDISCORD) $(PREFIX)/lib/
	install -d $(PREFIX)/include/
	install -m 644 *.h *.hpp common/*.h common/*.hpp $(PREFIX)/include/

clean :
	rm -rf $(OBJDIR) *.exe test/*.exe bots/*.exe

purge : clean
	rm -rf $(LIBDIR)
