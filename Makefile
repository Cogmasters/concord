CC	?= gcc
OBJDIR	:= obj
LIBDIR	:= lib

SRC		:= $(wildcard discord-*.c curl-websocket.c settings.c json-scanf.c jscon-common.c)
_OBJS		:= $(patsubst %.c, %.o, $(SRC))
OBJS 		:= $(addprefix $(OBJDIR)/, $(_OBJS))

LIBDISCORD_CFLAGS	:= -I./
LIBDISCORD_LDFLAGS	:=  -L./$(LIBDIR) -ldiscord -lcurl

ifeq ($(CC),stensal-c)
	LIBDISCORD_LDFLAGS += -lbearssl -static 
else
	LIBDISCORD_LDFLAGS += $(pkg-config --libs --cflags libcurl) -lcrypto -lm
endif


LIBS_CFLAGS	:= $(LIBJSCON_CFLAGS) $(LIBCURL_CFLAGS) $(LIBDISCORD_CFLAGS)
LIBS_LDFLAGS	:= $(LIBCURL_LDFLAGS) $(LIBDISCORD_LDFLAGS) $(LIBJSCON_LDFLAGS)

LIBDISCORD_SLIB	:= $(LIBDIR)/libdiscord.a

CFLAGS := -Wall -Wextra -pedantic -std=c11 -O0 -g -DLIBDISCORD_DEBUG  

ifeq ($(CC),stensal-c)
	CFLAGS += -D_DEFAULT_SOURCE
else
	CFLAGS += -fPIC -D_XOPEN_SOURCE=700
endif

PREFIX ?= /usr/local

.PHONY : all mkdir install clean purge

all : mkdir $(OBJS) $(LIBDISCORD_SLIB)

test : all test-api.c test-ws.c test-json-scanf.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) \
		test-api.c -o test-api.exe $(LIBS_LDFLAGS)
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) \
		test-ws.c -o test-ws.exe $(LIBS_LDFLAGS)
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) \
		test-json-scanf.c -o test-json-scanf.exe $(LIBS_LDFLAGS)

echo-bot : all echo-bot.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) \
		echo-bot.c -o echo-bot.exe $(LIBS_LDFLAGS)

mkdir :
	mkdir -p $(OBJDIR) $(LIBDIR)

$(OBJDIR)/discord-%.o : discord-%.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) \
		-c -o $@ $<

$(OBJDIR)/settings.o : settings.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<

$(OBJDIR)/json-scanf.o : json-scanf.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<

$(OBJDIR)/jscon-common.o : jscon-common.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<

$(OBJDIR)/curl-websocket.o : curl-websocket.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) \
		-U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=1 -c -o $@ $<

$(LIBDISCORD_SLIB) : $(OBJS)
	$(AR) -cvq $@ $(OBJS)

# @todo better install solution
install : all
	install -d $(PREFIX)/lib/
	install -m 644 $(LIBDISCORD_SLIB) $(PREFIX)/lib/
	install -d $(PREFIX)/include/
	install -m 644 libdiscord.h $(PREFIX)/include/

clean :
	rm -rf $(OBJDIR) $(LIBDIR) *.exe 

purge : clean
	rm -rf $(LIBDIR)
