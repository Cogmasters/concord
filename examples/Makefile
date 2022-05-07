# This Makefile assumes the top folder has been built
TOP = ..
CC ?= gcc

COGUTILS_DIR  = $(TOP)/cog-utils
CORE_DIR      = $(TOP)/core
INCLUDE_DIR   = $(TOP)/include
GENCODECS_DIR = $(TOP)/gencodecs

BOTS = 8ball \
       audit-log \
       ban \
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
       timers \
       $(XSRC)

VOICE_BOT = voice-join

CFLAGS  = -I$(INCLUDE_DIR) -I$(COGUTILS_DIR) -I$(CORE_DIR) \
          -I$(CORE_DIR)/third-party -I$(GENCODECS_DIR)     \
          -O0 -g -pthread -Wall $(XFLAGS)
LDFLAGS = -ldiscord -L$(TOP)/lib -lcurl

all: $(BOTS)

voice:
	$(MAKE) XFLAGS=-DCCORD_VOICE XSRC=$(VOICE_BOT) all

.SUFFIXES:
.DEFAULT:
	$(CC) $(CFLAGS) -o $@ $@.c $(LDFLAGS)

echo:
	@ echo -e 'CC: $(CC)\n'
	@ echo -e 'BOTS: $(BOTS)\n'

clean:
	@ $(RM) $(BOTS) $(VOICE_BOT)

.PHONY: all echo clean
