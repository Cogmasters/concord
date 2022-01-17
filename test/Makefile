# This Makefile assumes the top folder has been built

TOP = ..
CC ?= gcc

COGUTILS_DIR := $(TOP)/cog-utils
COMMON_DIR   := $(TOP)/common
INCLUDE_DIR  := $(TOP)/include

TEST_DISCORD := discord-sync-rest discord-sync-ws discord-async
TEST_COMMON  := user-agent websockets

EXES := $(TEST_DISCORD) $(TEST_GITHUB) $(TEST_COMMON)

CFLAGS  += -I$(INCLUDE_DIR) -I$(COGUTILS_DIR) -I$(COMMON_DIR) \
           -I$(COMMON_DIR)/third-party                        \
           -O0 -g -pthread -Wall
LDFLAGS += -L$(TOP)/lib $(pkg-config --libs --cflags libcurl) -lcurl

all: $(EXES)

$(TEST_DISCORD): %: %.c
	$(CC) $(CFLAGS) -o $@ $< -ldiscord $(LDFLAGS)
$(TEST_COMMON): %: %.c
	$(CC) $(CFLAGS) -o $@ $< -ldiscord $(LDFLAGS)

echo:
	@ echo -e 'CC: $(CC)\n'
	@ echo -e 'EXES: $(EXES)\n'

clean:
	rm -rf $(EXES)

.PHONY: all echo clean
