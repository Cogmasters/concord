CC	:= gcc
OBJDIR	:= obj
LIBDIR	:= lib

SRC		:= $(wildcard gthb-v3-user-agent.cpp)
_OBJS		:= $(patsubst %.cpp, %.o, $(SRC))
OBJS 		:= $(addprefix $(OBJDIR)/, $(_OBJS))

LIBDISCORD_CFLAGS	:= -I./
LIBDISCORD_LDFLAGS	:=  -L./$(LIBDIR) -ldiscord -lcurl


LIBDISCORD_LDFLAGS += -lbearssl -static


LIBS_CFLAGS	:= $(LIBDISCORD_CFLAGS)
LIBS_LDFLAGS	:= $(LIBDISCORD_LDFLAGS)

LIBDISCORD_SLIB	:= $(LIBDIR)/libdiscord.a

CFLAGS := -std=c++03 -Wno-write-strings -fpermissive -O0 -g -DLIBDISCORD_DEBUG -D__stensal__

CFLAGS += -D_DEFAULT_SOURCE

PREFIX ?= /usr/local

.PHONY : all mkdir install clean purge

all : mkdir $(OBJS) $(LIBDISCORD_SLIB)

mkdir :
	mkdir -p $(OBJDIR) $(LIBDIR)

$(OBJDIR)/settings.o : settings.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<
$(OBJDIR)/json-scanf.o : json-scanf.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<
$(OBJDIR)/jscon-common.o : jscon-common.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<

$(OBJDIR)/gthb-v3-user-agent.o: gthb-v3-user-agent.cpp
	$(CXX) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<

$(OBJDIR)/gthb-v3-git-database.o: gthb-v3-git-database.cpp
	$(CXX) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<

$(OBJDIR)/gthb-v3-repositories.o: gthb-v3-repositories.cpp
	$(CXX) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<

$(LIBDISCORD_SLIB) : $(OBJS)
	$(AR) -cvq $@ $(OBJS)

clean :
	rm -rf $(OBJDIR) $(LIBDIR) *.exe 

purge : clean
	rm -rf $(LIBDIR)
