# This Makefile assumes the top folder has been built
TOP = ..
CC ?= cc

CORE_DIR      = $(TOP)/core
INCLUDE_DIR   = $(TOP)/include
GENCODECS_DIR = $(TOP)/gencodecs

EXES = 8ball \
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

BOTS += $(EXES)

CFLAGS  += -O0 -g -pthread -Wall \
           -I$(INCLUDE_DIR) -I$(CORE_DIR) -I$(GENCODECS_DIR)
LDFLAGS  = -L$(TOP)/lib
LDLIBS   = -ldiscord -lcurl

all: $(BOTS)

echo:
	@ echo -e 'CC: $(CC)\n'
	@ echo -e 'EXES: $(EXES)\n'

clean:
	@ rm -f $(EXES)

.PHONY: all echo clean
