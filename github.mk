OBJDIR	:= obj
LIBDIR	:= lib

SRC	:= $(wildcard http-common.c github-v3-user-agent.cpp \
          json-scanf.c json-printf.c json-string.c \
		  github-v3-git-op.cpp orka-utils.c\
		  settings.c orka-user-agent.cpp ntl.c)

_OBJS	:= $(patsubst %.cpp, %.o, $(SRC))
OBJS1   += $(patsubst %.c, %.o, $(_OBJS))
OBJS 	:= $(addprefix $(OBJDIR)/, $(OBJS1))

LIBDISCORD_CFLAGS	:= -I./
LIBDISCORD_LDFLAGS	:=  -L./$(LIBDIR) -ldiscord -lcurl \
						-lbearssl -static


LIBS_CFLAGS	:= $(LIBDISCORD_CFLAGS)
LIBS_LDFLAGS	:= $(LIBDISCORD_LDFLAGS)

LIBDISCORD_SLIB	:= $(LIBDIR)/libdiscord.a

CFLAGS := -Wall -Wno-write-strings -fpermissive -O0 -g -D_ORCA_DEBUG -D__stensal__ \
					-D_DEFAULT_SOURCE -DJSON_SCANF_DEBUG

CXXFLAGS = -std=c++03


PREFIX ?= /usr/local

.PHONY : all mkdir install clean purge

all : mkdir $(OBJS) $(LIBDISCORD_SLIB) test-git.exe test-git2.exe test-cee.exe

mkdir :
	mkdir -p $(OBJDIR) $(LIBDIR)
	echo $(OBJS)

$(OBJDIR)/ntl.o : ntl.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<

$(OBJDIR)/http-common.o : http-common.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<

$(OBJDIR)/settings.o : settings.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<

$(OBJDIR)/json-scanf.o : json-scanf.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<

$(OBJDIR)/json-printf.o : json-printf.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<

$(OBJDIR)/json-string.o : json-string.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<

$(OBJDIR)/orka-utils.o: orka-utils.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<

$(OBJDIR)/orka-user-agent.o: orka-user-agent.cpp
	$(CXX) $(CFLAGS) $(CXXFLAGS) $(LIBS_CFLAGS) -c -o $@ $<

$(OBJDIR)/github-v3-user-agent.o: github-v3-user-agent.cpp
	$(CXX) $(CFLAGS) $(CXXFLAGS) $(LIBS_CFLAGS) -c -o $@ $<

$(OBJDIR)/github-v3-git-op.o: github-v3-git-op.cpp
	$(CXX) $(CFLAGS) $(CXXFLAGS) $(LIBS_CFLAGS) -c -o $@ $<

$(OBJDIR)/github-v3-repositories.o: github-v3-repositories.cpp
	$(CXX) $(CFLAGS) $(CXXFLAGS) $(LIBS_CFLAGS) -c -o $@ $<

test-git.exe: test-git.cpp $(OBJS)
	$(CXX) $(CFLAGS) $(LIBS_CFLAGS) -o $@ $< $(OBJS) -lcurl -lbearssl -static

test-git2.exe: test-git2.cpp $(OBJS)
	$(CXX) $(CFLAGS) $(LIBS_CFLAGS) -o $@ $< $(OBJS) -lcurl -lbearssl -static

test-cee.exe: test-cee.cpp $(OBJS)
	$(CXX) $(CFLAGS) $(LIBS_CFLAGS) -o $@ $< $(OBJS) -lcurl -lbearssl -static

$(LIBDISCORD_SLIB) : $(OBJS)
	$(AR) -cvq $@ $(OBJS)

clean :
	rm -rf $(OBJDIR) $(LIBDIR) *.exe 

purge : clean
	rm -rf $(LIBDIR)
