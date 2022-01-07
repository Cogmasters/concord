# This Makefile assumes the top folder has been built

TOP = ..
CC ?= gcc

COGUTILS_DIR := $(TOP)/cog-utils
COMMON_DIR   := $(TOP)/common
INCLUDE_DIR  := $(TOP)/include

BOTS := bot-audit-log \
        bot-ban \
        bot-channel \
        bot-components \
        bot-delete-messages \
        bot-echo \
        bot-embed \
        bot-emoji \
        bot-fetch-messages \
        bot-guild-template \
        bot-guild \
        bot-invite \
        bot-manual-dm \
        bot-pin \
        bot-ping-pong \
        bot-presence \
        bot-reaction \
        bot-shell \
        bot-slash-commands \
        bot-slash-commands2 \
        bot-voice \
        bot-webhook

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
