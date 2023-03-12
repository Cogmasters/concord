# This Makefile assumes the top folder has been built
TOP = ..
CC ?= cc

CORE_DIR      = $(TOP)/core
INCLUDE_DIR   = $(TOP)/include
GENCODECS_DIR = $(TOP)/gencodecs

STD_BOTS   = 8ball \
             audit-log \
             ban \
             cache \
             channel \
             components \
             copycat \
             embed \
             emoji \
             fetch-messages \
             guild-template \
             guild \
             invite \
             manual-dm \
             pin \
             ping-pong \
             presence \
             reaction \
             shell \
             slash-commands \
             slash-commands2 \
             spam \
             webhook \
             timers
VOICE_BOTS = voice-join

BOTS += $(STD_BOTS)

CFLAGS  += -O0 -g -pthread -Wall \
           -I$(INCLUDE_DIR) -I$(CORE_DIR) -I$(GENCODECS_DIR)
LDFLAGS  = -L$(TOP)/lib
LDLIBS   = -ldiscord -lcurl

all: $(BOTS)

voice:
	@ CFLAGS=-DCCORD_VOICE BOTS=$(VOICE_BOTS) $(MAKE)

echo:
	@ echo -e 'CC: $(CC)\n'
	@ echo -e 'STD_BOTS: $(STD_BOTS)\n'
	@ echo -e 'VOICE_BOTS: $(VOICE_BOTS)\n'

clean:
	@ rm -f $(STD_BOTS) $(VOICE_BOTS)

.PHONY: all echo clean
