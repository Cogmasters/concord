# This Makefile assumes the top folder has been built
TOP = ..
CC ?= gcc

CORE_DIR      = $(TOP)/core
THIRDP_DIR    = $(CORE_DIR)/third-party
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

CFLAGS  = -O0 -g -pthread -Wall \
          -I$(INCLUDE_DIR) -I$(CORE_DIR) -I$(THIRDP_DIR) -I$(GENCODECS_DIR)
LDFLAGS = -L$(TOP)/lib
LDLIBS  = -ldiscord -lcurl

all: $(BOTS)

voice:
	@ CFLAGS="$(CFLAGS) -DCCORD_VOICE" $(MAKE) BOTS="$(BOTS) $(VOICE_BOTS)"

echo:
	@ echo -e 'CC: $(CC)\n'
	@ echo -e 'BOTS: $(BOTS)\n'

clean:
	@ $(RM) $(BOTS) $(VOICE_BOTS)

.PHONY: all echo clean
