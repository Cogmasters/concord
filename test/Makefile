TOP 	:= ..
CC		:= stensal-c

LIBDIR	:= $(TOP)/lib

LIBJSCON_CFLAGS		:= -I./JSCON/include
LIBJSCON_LDFLAGS	:= "-Wl,-rpath,$(TOP)/JSCON/lib" -L$(TOP)/JSCON/lib -ljscon

LIBDISCORD_CFLAGS	:= -I$(TOP)/include
LIBDISCORD_LDFLAGS	:= "-Wl,-rpath,$(LIBDIR)" -L$(LIBDIR) -ldiscord

LIBS_CFLAGS	:= $(LIBJSCON_CFLAGS) $(LIBDISCORD_CFLAGS)
LIBS_LDFLAGS	:= $(LIBJSCON_LDFLAGS) $(LIBDISCORD_LDFLAGS)

CFLAGS	= -Wall -Wextra -pedantic -g

.PHONY : clean purge

all: test-api

test-api : test-api.c $(LIBDIR) Makefile
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) \
	      test-api.c -o $@ $(LIBS_LDFLAGS)

$(LIBDIR) :
	$(MAKE) -C $(TOP)

clean :
	rm -rf test-api *.out
