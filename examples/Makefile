# This Makefile assumes the top folder has been built

TOP = ..
CC ?= gcc

COGUTILS_DIR := $(TOP)/cog-utils
CORE_DIR     := $(TOP)/core
INCLUDE_DIR  := $(TOP)/include

BOTS := audit-log \
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
        voice \
        webhook

CFLAGS  += -I$(INCLUDE_DIR) -I$(COGUTILS_DIR) -I$(CORE_DIR) \
           -I$(CORE_DIR)/third-party                        \
           -O0 -g -pthread -Wall
LDFLAGS += -L$(TOP)/lib $(pkg-config --libs --cflags libcurl) -lcurl

all: $(BOTS)

$(BOTS): %: %.c
	$(CC) $(CFLAGS) -o $@ $< -ldiscord $(LDFLAGS)

echo:
	@ echo -e 'CC: $(CC)\n'
	@ echo -e 'BOTS: $(BOTS)\n'

clean:
	rm -rf $(BOTS)

.PHONY: all echo clean
