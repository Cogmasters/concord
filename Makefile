CC	?= gcc
OBJDIR	:= obj
LIBDIR	:= lib

COMMON_SRC  := $(wildcard \
		curl-websocket.c \
		http-common.c \
		orka-utils.c \
		ntl.c json-*.c)


DISCORD_SRC := $(wildcard discord-*.cpp)
GITHUB_SRC  := $(wildcard github-*.cpp)
ORKA_SRC    := $(wildcard orka-*.cpp)

COMMON_OBJS := $(COMMON_SRC:%=$(OBJDIR)/%.o)
DISCORD_OBJS := $(DISCORD_SRC:%=$(OBJDIR)/%.o)
GITHUB_OBJS := $(GITHUB_SRC:%=$(OBJDIR)/%.o)
ORKA_OBJS  := $(ORKA_SRC:%=$(OBJDIR)/%.o)

OBJS := $(COMMON_OBJS) $(DISCORD_OBJS) $(GITHUB_OBJS) $(ORKA_OBJS)

BOT_SRC := $(wildcard bots/bot-*.cpp)
BOT_EXES := $(patsubst %.cpp, %.exe, $(BOT_SRC))

TEST_SRC := $(wildcard test/test-*.cpp test/test-*.c)
TEST_EXES := $(filter %.exe, $(TEST_SRC:.cpp=.exe) $(TEST_SRC:.c=.exe))

LIBDISCORD_CFLAGS	:= -I./
LIBDISCORD_LDFLAGS	:=  -L./$(LIBDIR) -ldiscord -lcurl

ifeq ($(CC),stensal-c)
	LIBDISCORD_LDFLAGS += -lbearssl -static 
else
	LIBDISCORD_LDFLAGS += $(pkg-config --libs --cflags libcurl) -lcrypto -lm
endif


LIBS_CFLAGS	:= $(LIBDISCORD_CFLAGS)
LIBS_LDFLAGS	:= $(LIBDISCORD_LDFLAGS)

LIBDISCORD_SLIB	:= $(LIBDIR)/libdiscord.a

CFLAGS   := -Wall -Wextra -pedantic -O0 -g -D_ORCA_DEBUG -D_GNU_SOURCE \
		-Wno-unused-parameter -Wno-missing-field-initializers \
		-Wno-incompatible-pointer-types

CXXFLAGS := -Wall -std=c++03 -O0 -g -D_ORCA_DEBUG -D_GNU_SOURCE \
		-Wno-write-strings

ifeq ($(CC),stensal-c)
	CFLAGS += -D_DEFAULT_SOURCE
	CXXFLAGS += -D_DEFAULT_SOURCE
else
	CFLAGS += -fPIC -D_XOPEN_SOURCE=700
	CXXFLAGS += -fPIC -D_XOPEN_SOURCE=700
endif

PREFIX ?= /usr/local

.PHONY : all mkdir install clean purge

all : mkdir common discord github orka $(LIBDISCORD_SLIB) bot

common: mkdir $(COMMON_OBJS)
discord: mkdir $(DISCORD_OBJS)
github: mkdir $(GITHUB_OBJS)
orka: mkdir $(ORKA_OBJS)

bot: $(BOT_EXES)
test: all $(TEST_EXES)


mkdir :
	mkdir -p $(OBJDIR) $(LIBDIR)

$(OBJDIR)/%.c.o : %.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<
$(OBJDIR)/%.cpp.o: %.cpp
	$(CXX) $(CXXFLAGS) $(LIBS_CFLAGS) -c -o $@ $<

%.exe : %.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -o $@ $< $(LIBS_LDFLAGS)

%.exe: %.cpp
	$(CXX) $(CXXFLAGS) $(LIBS_CFLAGS) -o $@ $< $(LIBS_LDFLAGS)

$(LIBDISCORD_SLIB) : $(OBJS)
	$(AR) -cvq $@ $(OBJS)

install : all
	install -d $(PREFIX)/lib/
	install -m 644 $(LIBDISCORD_SLIB) $(PREFIX)/lib/
	install -d $(PREFIX)/include/
	install -m 644 libdiscord.h $(PREFIX)/include/

clean :
	rm -rf $(OBJDIR) $(LIBDIR) \
	*.exe test/*.exe bots/*.exe

purge : clean
	rm -rf $(LIBDIR)
