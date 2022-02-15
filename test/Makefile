# This Makefile assumes the top folder has been built

TOP = ..
CC ?= gcc

COGUTILS_DIR := $(TOP)/cog-utils
CORE_DIR     := $(TOP)/core
INCLUDE_DIR  := $(TOP)/include

TEST_DISCORD := discord-sync-rest discord-sync-ws discord-async discord-events
TEST_CORE  := user-agent websockets

EXES := $(TEST_DISCORD) $(TEST_GITHUB) $(TEST_CORE)

CFLAGS  += -I$(INCLUDE_DIR) -I$(COGUTILS_DIR) -I$(CORE_DIR) \
           -I$(CORE_DIR)/third-party                        \
           -O0 -g -pthread -Wall
LDFLAGS += -L$(TOP)/lib $(pkg-config --libs --cflags libcurl) -lcurl

all: $(EXES)

$(TEST_DISCORD): %: %.c
	$(CC) $(CFLAGS) -o $@ $< -ldiscord $(LDFLAGS)
$(TEST_CORE): %: %.c
	$(CC) $(CFLAGS) -o $@ $< -ldiscord $(LDFLAGS)

echo:
	@ echo -e 'CC: $(CC)\n'
	@ echo -e 'EXES: $(EXES)\n'

clean:
	rm -rf $(EXES)

.PHONY: all echo clean
