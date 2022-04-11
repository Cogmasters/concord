# This Makefile assumes the top folder has been built

TOP = ..
CC = gcc

COGUTILS_DIR  := $(TOP)/cog-utils
CORE_DIR      := $(TOP)/core
GENCODECS_DIR := $(TOP)/gencodecs
INCLUDE_DIR   := $(TOP)/include

TEST_DISCORD := rest sync async timeout
TEST_CORE  := user-agent websockets

EXES := $(TEST_DISCORD) $(TEST_GITHUB) $(TEST_CORE)

CFLAGS  += -I$(INCLUDE_DIR) -I$(COGUTILS_DIR) -I$(CORE_DIR) \
           -I$(CORE_DIR)/third-party -I$(GENCODECS_DIR)     \
           -O0 -g -pthread -Wall
LDFLAGS += -L$(TOP)/lib $(pkg-config --libs --cflags libcurl) -lcurl

all: $(EXES)

$(TEST_DISCORD): 
	for test in $(TEST_DISCORD); do \
		echo $$test; \
		$(CC) $(CFLAGS) -o $$test $$test.c -ldiscord $(LDFLAGS); \
	done
$(TEST_CORE): 
	for test in $(TEST_DISCORD); do \
		echo $$test; \
		$(CC) $(CFLAGS) -o $$test $$test.c -ldiscord $(LDFLAGS); \
	done

echo:
	@ echo -e 'CC: $(CC)\n'
	@ echo -e 'EXES: $(EXES)\n'

clean:
	rm -rf $(EXES)

.PHONY: all echo clean
