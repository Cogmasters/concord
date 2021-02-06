CC	?= gcc
OBJDIR	:= obj
LIBDIR	:= lib

SRC	:= $(wildcard \
		curl-websocket.c \
		orka-http.c \
		orka-utils.c \
		github-*.cpp \
		discord-*.cpp \
		orka-*.cpp \
		ntl.c json-*.c)

_OBJS := $(filter %.o,$(SRC:.cpp=.o) $(SRC:.c=.o))
OBJS 	:= $(addprefix $(OBJDIR)/, $(_OBJS))

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

CFLAGS   := -Wall -Wextra -O0 -g -D_ORCA_DEBUG -D_GNU_SOURCE \
		-Wno-unused-parameter -Wno-missing-field-initializers

CXXFLAGS := -std=c++03 -O0 -g -D_ORCA_DEBUG -D_GNU_SOURCE \
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

all : mkdir $(OBJS) $(LIBDISCORD_SLIB) bot
bot: $(BOT_EXES)
test: all $(TEST_EXES)


mkdir :
	mkdir -p $(OBJDIR) $(LIBDIR)

$(OBJDIR)/%.o : %.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<
$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CFLAGS) $(CXXFLAGS) $(LIBS_CFLAGS) -c -o $@ $<

%.exe : %.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -o $@ $< $(LIBS_LDFLAGS)
%.exe: %.cpp
	$(CXX) $(CFLAGS) $(CXXFLAGS) $(LIBS_CFLAGS) -o $@ $< $(LIBS_LDFLAGS)

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
