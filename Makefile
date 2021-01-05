CC			:= stensal-c
OBJDIR	:= obj
LIBDIR	:= lib

SRC			:= $(wildcard discord-*.c curl-websocket.c)
_OBJS		:= $(patsubst %.c, %.o, $(SRC))
OBJS 		:= $(addprefix $(OBJDIR)/, $(_OBJS))

LIBJSCON_CFLAGS		:= -I./JSCON/include
LIBJSCON_LDFLAGS	:= "-Wl,-rpath,./JSCON/lib" -L./JSCON/lib -ljscon

LIBDISCORD_CFLAGS		:= -I./
LIBDISCORD_LDFLAGS	:= "-Wl,-rpath,./lib" -L$(LIBDIR) -ldiscord -lcurl -lbearssl

LIBS_CFLAGS		:= $(LIBJSCON_CFLAGS) $(LIBCURL_CFLAGS) \
									$(LIBDISCORD_CFLAGS)
LIBS_LDFLAGS	:= $(LIBJSCON_LDFLAGS) $(LIBCURL_LDFLAGS) \
									$(LIBDISCORD_LDFLAGS)

LIBDISCORD_DLIB	:= $(LIBDIR)/libdiscord.so
LIBDISCORD_SLIB	:= $(LIBDIR)/libdiscord.a

CFLAGS := -Wall -Wextra -pedantic -fPIC -std=c11 -O0 -g \
	-DLIBDISCORD_DEBUG -D_DEFAULT_SOURCE -D_XOPEN_SOURCE=700


.PHONY : all mkdir install clean purge

all : mkdir $(OBJS) $(LIBDISCORD_DLIB) $(LIBDISCORD_SLIB)

test : all test-api.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) \
		test-api.c -o test-api $(LIBS_LDFLAGS)

mkdir :
	mkdir -p $(OBJDIR) $(LIBDIR)

$(OBJDIR)/discord-%.o : discord-%.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) \
		-c -o $@ $<

$(OBJDIR)/curl-websocket.o : curl-websocket.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) \
		-U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=1 -c -o $@ $<

$(LIBDISCORD_DLIB) :
	$(CC) $(LIBS_CFLAGS) \
	  $(OBJS) -shared -o $@ $(LIBS_LDFLAGS)

$(LIBDISCORD_SLIB) :
	$(AR) -cvq $@ $(OBJS)

# @todo better install solution
install : all
	cp $(INCLUDE) /usr/local/include && \
	cp $(LIBDISCORD_DLIB) /usr/local/lib && \
	ldconfig

clean :
	rm -rf $(OBJDIR) test-api

purge : clean
	rm -rf $(LIBDIR)
