CC			:= stensal-c
SRCDIR	:= src
OBJDIR	:= obj
INCLDIR	:= include
LIBDIR	:= lib

SRC		:= $(wildcard src/*.c)
_OBJS	:= $(patsubst src/%.c, %.o, $(SRC))
OBJS 	:= $(addprefix $(OBJDIR)/, $(_OBJS))

#LIBCURL_CFLAGS	:= $(shell pkg-config --cflags libcurl)
#LIBCURL_LDFLAGS	:= $(shell pkg-config --libs libcurl)

LIBJSCON_CFLAGS		:= -I./JSCON/include
LIBJSCON_LDFLAGS	:= "-Wl,-rpath,./JSCON/lib" -L./JSCON/lib -ljscon

LIBDISCORD_CFLAGS		:= -I$(INCLDIR)
LIBDISCORD_LDFLAGS	:= -lcurl -lbearssl

LIBS_CFLAGS		:= $(LIBJSCON_CFLAGS) $(LIBCURL_CFLAGS) \
									$(LIBDISCORD_CFLAGS)
LIBS_LDFLAGS	:= $(LIBJSCON_LDFLAGS) $(LIBCURL_LDFLAGS) \
									$(LIBDISCORD_LDFLAGS)

LIBDISCORD_DLIB	:= $(LIBDIR)/libdiscord.so
LIBDISCORD_SLIB	:= $(LIBDIR)/libdiscord.a

CFLAGS := -Wall -Werror -pedantic \
	-fPIC -std=c11 -O0 -g -D_XOPEN_SOURCE=600


.PHONY : all mkdir install clean purge

all : mkdir $(OBJS) $(LIBDISCORD_DLIB) $(LIBDISCORD_SLIB)

mkdir :
	mkdir -p $(OBJDIR) $(LIBDIR)

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) \
		-c -o $@ $<

$(LIBDISCORD_DLIB) :
	$(CC) $(LIBS_CFLAGS) \
	  $(OBJS) -shared -o $@ $(LIBS_LDFLAGS)

$(LIBDISCORD_SLIB) :
	$(AR) -cvq $@ $(OBJS)

# @todo better install solution
install : all
	cp $(INCLDIR)/* /usr/local/include && \
	cp $(LIBDISCORD_DLIB) /usr/local/lib && \
	ldconfig

clean :
	rm -rf $(OBJDIR)

purge : clean
	rm -rf $(LIBDIR)
	$(MAKE) -C test clean
