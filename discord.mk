OBJDIR	:= obj
LIBDIR	:= lib

SRC	:= $(wildcard http-common.c discord-*.cpp curl-websocket.c \
	     orka-utils.c \
         settings.c ntl.c json-scanf.c json-printf.c json-string.c)

_OBJS	:= $(patsubst %.cpp, %.o, $(SRC))
OBJS1   += $(patsubst %.c, %.o, $(_OBJS))
OBJS 	:= $(addprefix $(OBJDIR)/, $(OBJS1))

LIBDISCORD_CFLAGS	:= -I./
LIBDISCORD_LDFLAGS	:=  -L./$(LIBDIR) -ldiscord -lcurl

LIBS_CFLAGS	:= $(LIBDISCORD_CFLAGS)
LIBS_LDFLAGS	:= $(LIBDISCORD_LDFLAGS)

LIBDISCORD_SLIB	:= $(LIBDIR)/libdiscord.a

CFLAGS := -Wall -Wno-write-strings -O0 -g -D_ORCA_DEBUG \
					-D_DEFAULT_SOURCE # -DJSON_SCANF_DEBUG

CXXFLAGS := -std=c++03

PREFIX ?= /usr/local


ifeq ($(CC),stensal-c)
	LIBS_LDFLAGS += -lbearssl -static 
	CFLAGS += -D__stensal__
else
	LIBS_LDFLAGS += $(pkg-config --libs --cflags libcurl) -lcrypto -lm
endif



.PHONY : all mkdir install clean purge

all : mkdir $(OBJS) $(LIBDISCORD_SLIB) bot-echo bot-pin bot-ping-pong bot-mimic test-api test-ws

mkdir :
	mkdir -p $(OBJDIR) $(LIBDIR)
	echo $(OBJS)

$(OBJDIR)/http-common.o : http-common.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<
$(OBJDIR)/settings.o : settings.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<
$(OBJDIR)/discord-%.o : discord-%.cpp
	$(CXX) $(CFLAGS) $(CXXFLAGS) $(LIBS_CFLAGS) -c -o $@ $<
$(OBJDIR)/ntl.o : ntl.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<
$(OBJDIR)/json-scanf.o : json-scanf.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<
$(OBJDIR)/json-printf.o : json-printf.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<
$(OBJDIR)/json-string.o : json-string.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<
$(OBJDIR)/orka-utils.o : orka-utils.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<
$(OBJDIR)/curl-websocket.o : curl-websocket.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) \
		-U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=1 -c -o $@ $<

test-api : test-api.cpp
	$(CXX) $(CFLAGS) $(LIBS_CFLAGS) \
		test-api.cpp $(OBJS) -o test-api.exe $(LIBS_LDFLAGS)
test-ws : test-ws.cpp
	$(CXX) $(CFLAGS) $(LIBS_CFLAGS) \
		test-ws.cpp $(OBJS) -o test-ws.exe $(LIBS_LDFLAGS)

bot-echo : bot-echo.cpp
	$(CXX) $(CFLAGS) $(LIBS_CFLAGS) \
		bot-echo.cpp $(OBJS) -o bot-echo.exe $(LIBS_LDFLAGS)
bot-pin : bot-pin.cpp
	$(CXX) $(CFLAGS) $(LIBS_CFLAGS) \
		bot-pin.cpp $(OBJS) -o bot-pin.exe $(LIBS_LDFLAGS)
bot-ping-pong : bot-ping-pong.cpp
	$(CXX) $(CFLAGS) $(LIBS_CFLAGS) \
		bot-ping-pong.cpp $(OBJS) -o bot-ping-pong.exe $(LIBS_LDFLAGS)
bot-mimic : bot-mimic.cpp
	$(CXX) $(CFLAGS) $(LIBS_CFLAGS) \
		bot-mimic.cpp $(OBJS) -o bot-mimic.exe $(LIBS_LDFLAGS)

$(LIBDISCORD_SLIB) : $(OBJS)
	$(AR) -cvq $@ $(OBJS)

clean :
	rm -rf $(OBJDIR) $(LIBDIR) *.exe 

purge : clean
	rm -rf $(LIBDIR)
