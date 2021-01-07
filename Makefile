CC			?= gcc
OBJDIR	:= obj
LIBDIR	:= lib

SRC			:= $(wildcard orca-*.c curl-websocket.c)
_OBJS		:= $(patsubst %.c, %.o, $(SRC))
OBJS 		:= $(addprefix $(OBJDIR)/, $(_OBJS))

LIBJSCON_CFLAGS		:= -I./JSCON/include
LIBJSCON_LDFLAGS	:= "-Wl,-rpath,./JSCON/lib" -L./JSCON/lib -ljscon

LIBORCA_CFLAGS		:= -I./
LIBORCA_LDFLAGS	:= "-Wl,-rpath,./lib" -L$(LIBDIR) -lorca -lcurl -lbearssl

LIBS_CFLAGS		:= $(LIBJSCON_CFLAGS) $(LIBCURL_CFLAGS) $(LIBORCA_CFLAGS)
LIBS_LDFLAGS	:= $(LIBJSCON_LDFLAGS) $(LIBCURL_LDFLAGS) $(LIBORCA_LDFLAGS)

LIBORCA_DLIB	:= $(LIBDIR)/liborca.so
LIBORCA_SLIB	:= $(LIBDIR)/liborca.a

CFLAGS := -Wall -Wextra -pedantic -fPIC -std=c11 -O0 -g \
	-DLIBORCA_DEBUG -D_DEFAULT_SOURCE -D_XOPEN_SOURCE=700


.PHONY : all mkdir install clean purge

all : mkdir $(OBJS) $(LIBORCA_DLIB) $(LIBORCA_SLIB)

test : all test-api.c test-ws.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) \
		test-api.c -o test-api $(LIBS_LDFLAGS)
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) \
		test-ws.c -o test-ws $(LIBS_LDFLAGS)

mkdir :
	mkdir -p $(OBJDIR) $(LIBDIR)

$(OBJDIR)/orca-%.o : orca-%.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) \
		-c -o $@ $<

$(OBJDIR)/curl-websocket.o : curl-websocket.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) \
		-U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=1 -c -o $@ $<

$(LIBORCA_DLIB) :
	$(CC) $(LIBS_CFLAGS) \
	  $(OBJS) -shared -o $@ $(LIBS_LDFLAGS)

$(LIBORCA_SLIB) :
	$(AR) -cvq $@ $(OBJS)

# @todo better install solution
install : all
	cp $(INCLUDE) /usr/local/include && \
	cp $(LIBORCA_DLIB) /usr/local/lib && \
	ldconfig

clean :
	rm -rf $(OBJDIR) test-api test-ws

purge : clean
	rm -rf $(LIBDIR)
