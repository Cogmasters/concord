CC	?= gcc
OBJDIR	:= obj
LIBDIR	:= lib

SRC		:= $(wildcard discord-*.c curl-websocket.c settings.c json-scanf.c strscpy.c jscon-common.c)
_OBJS		:= $(patsubst %.c, %.o, $(SRC))
OBJS 		:= $(addprefix $(OBJDIR)/, $(_OBJS))

LIBDISCORD_CFLAGS	:= -I./
LIBDISCORD_LDFLAGS	:=  -L./$(LIBDIR) -ldiscord -lcurl

ifeq ($(CC),stensal-c)
	LIBDISCORD_LDFLAGS += -lbearssl -static 
else
	LIBDISCORD_LDFLAGS += $(pkg-config --libs --cflags libcurl) -lcrypto -lm
endif


LIBS_CFLAGS		:= $(LIBJSCON_CFLAGS) $(LIBCURL_CFLAGS) $(LIBDISCORD_CFLAGS)
LIBS_LDFLAGS	:= $(LIBCURL_LDFLAGS) $(LIBDISCORD_LDFLAGS) $(LIBJSCON_LDFLAGS)

LIBDISCORD_SLIB	:= $(LIBDIR)/libdiscord.a

CFLAGS := -Wall -Wextra -pedantic -std=c11 -O0 -g \
	-DLIBDISCORD_DEBUG -D_DEFAULT_SOURCE -D_XOPEN_SOURCE=700

ifeq ($(CC),stensal-c)
else
	CFLAGS += -fPIC
endif

.PHONY : all mkdir install clean purge

all : mkdir $(OBJS) $(LIBDISCORD_SLIB)

test : all test-api.c test-ws.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) \
		test-api.c -o test-api $(LIBS_LDFLAGS)
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) \
		test-ws.c -o test-ws $(LIBS_LDFLAGS)

mkdir :
	mkdir -p $(OBJDIR) $(LIBDIR)

$(OBJDIR)/discord-%.o : discord-%.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) \
		-c -o $@ $<

$(OBJDIR)/settings.o : settings.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<

$(OBJDIR)/json-scanf.o : json-scanf.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<

$(OBJDIR)/strscpy.o : strscpy.c
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
	cp $(INCLUDE) /usr/local/include

clean :
	rm -rf $(OBJDIR) test-api test-ws lib/*

purge : clean
	rm -rf $(LIBDIR)
