# This Makefile assumes the top folder has been built
TOP = ..
CC ?= gcc

COGUTILS_DIR  = $(TOP)/cog-utils
CORE_DIR      = $(TOP)/core
INCLUDE_DIR   = $(TOP)/include
GENCODECS_DIR = $(TOP)/gencodecs

VOICE_BOTS = voice-join
BOTS       = 8ball \
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
             timers

CFLAGS  = -I$(INCLUDE_DIR) -I$(COGUTILS_DIR) -I$(CORE_DIR) \
          -I$(CORE_DIR)/third-party -I$(GENCODECS_DIR)     \
          -O0 -g -pthread -Wall
LDFLAGS = -L$(TOP)/lib
LDLIBS  = -ldiscord -lcurl

all: $(BOTS)

voice:
	@ $(MAKE) CFLAGS="$(CFLAGS) -DCCORD_VOICE" BOTS="$(BOTS) $(VOICE_BOTS)" all

echo:
	@ echo -e 'CC: $(CC)\n'
	@ echo -e 'BOTS: $(BOTS)\n'

clean:
	@ $(RM) $(BOTS) $(VOICE_BOTS)

.PHONY: all echo clean
