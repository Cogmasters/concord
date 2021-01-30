OBJDIR	:= obj
LIBDIR	:= lib

SRC	:= $(wildcard http-common.c github-v3-user-agent.cpp \
          json-scanf.c json-printf.c json-string.c \
		  github-v3-git-op.cpp orka-utils.c\
		  settings.c orka-user-agent.cpp ntl.c)

_OBJS	:= $(patsubst %.cpp, %.o, $(SRC))
OBJS1   += $(patsubst %.c, %.o, $(_OBJS))
OBJS 	:= $(addprefix $(OBJDIR)/, $(OBJS1))

LIBGITHUB_CFLAGS	:= -I./
LIBGITHUB_LDFLAGS	:=  -L./$(LIBDIR) -lcurl #-lgithub

LIBS_CFLAGS	:= $(LIBGITHUB_CFLAGS)
LIBS_LDFLAGS	:= $(LIBGITHUB_LDFLAGS)

LIBGITHUB_SLIB	:= $(LIBDIR)/libdiscord.a

CFLAGS := -Wall -Wno-write-strings -O0 -g -D_ORCA_DEBUG \
					-D_DEFAULT_SOURCE -DJSON_SCANF_DEBUG

CXXFLAGS := -std=c++03

PREFIX ?= /usr/local


ifeq ($(CC),stensal-c)
	LIBS_LDFLAGS += -lbearssl -static 
	CFLAGS += -D__stensal__
else
	LIBS_LDFLAGS += $(pkg-config --libs --cflags libcurl) -lcrypto -lm
endif


.PHONY : all mkdir install clean purge

all : mkdir $(OBJS) $(LIBGITHUB_SLIB) test-git.exe test-git2.exe test-cee.exe

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

test-git.exe: test-git.cpp
	$(CXX) $(CFLAGS) $(LIBS_CFLAGS) \
		-o $@ $(OBJS) $^ $(LIBS_LDFLAGS)
test-git2.exe: test-git2.cpp
	$(CXX) $(CFLAGS) $(LIBS_CFLAGS) \
		-o $@ $(OBJS) $^ $(LIBS_LDFLAGS)
test-cee.exe: test-cee.cpp
	$(CXX) $(CFLAGS) $(LIBS_CFLAGS) \
		-o $@ $(OBJS) $^ $(LIBS_LDFLAGS)

$(LIBGITHUB_SLIB) : $(OBJS)
	$(AR) -cvq $@ $(OBJS)

clean :
	rm -rf $(OBJDIR) $(LIBDIR) *.exe 

purge : clean
	rm -rf $(LIBDIR)
