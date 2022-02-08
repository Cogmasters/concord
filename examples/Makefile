# This Makefile assumes the top folder has been built

TOP = ..
CC ?= gcc

COGUTILS_DIR := $(TOP)/cog-utils
COMMON_DIR   := $(TOP)/common
INCLUDE_DIR  := $(TOP)/include

BOTS := audit-log \
        ban \
        channel \
        components \
        delete-messages \
        copycat \
	8ball \
        embed \
        emoji \
        fetch-messages \
        guild-template \
        guild \
        invite \
        manual-dm \
        pin \
        ping-pong \
	8ball \
        presence \
        reaction \
        shell \
        slash-commands \
        slash-commands2 \
        voice \
        webhook

CFLAGS  += -I$(INCLUDE_DIR) -I$(COGUTILS_DIR) -I$(COMMON_DIR) \
           -I$(COMMON_DIR)/third-party                        \
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
