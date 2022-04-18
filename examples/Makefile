# This Makefile assumes the top folder has been built

TOP = ..
CC = gcc

COGUTILS_DIR := $(TOP)/cog-utils
CORE_DIR     := $(TOP)/core
INCLUDE_DIR  := $(TOP)/include
GENCODECS_DIR  := $(TOP)/gencodecs

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
        webhook \
        timers \
        $(XSRC)


SRCS := audit-log.c \
        ban.c \
        channel.c \
        components.c \
        copycat.c \
        embed.c \
        emoji.c \
        fetch-messages.c \
        guild-template.c \
        guild.c \
        invite.c \
        manual-dm.c \
        pin.c \
        ping-pong.c \
        presence.c \
        reaction.c \
        shell.c \
        slash-commands.c \
        slash-commands2.c \
        spam.c \
        webhook.c \
        timers.c

CFLAGS  += -I$(INCLUDE_DIR) -I$(COGUTILS_DIR) -I$(CORE_DIR) \
           -I$(CORE_DIR)/third-party -I$(GENCODECS_DIR)     \
           -O0 -g -pthread -Wall $(XFLAGS)
LDFLAGS += -L$(TOP)/lib -lcurl

all: $(BOTS)

voice:
	$(MAKE) XFLAGS=-DCCORD_VOICE XSRC=voice all

$(BOTS): $(SRCS)
	for bot in $(BOTS); do \
		echo $$bot; \
		$(CC) $(CFLAGS) -o $$bot $$bot.c -ldiscord $(LDFLAGS); \
	done

echo:
	@ echo -e 'CC: $(CC)\n'
	@ echo -e 'BOTS: $(BOTS)\n'

clean:
	rm -rf $(BOTS) voice

.PHONY: all echo clean
