# This Makefile assumes the top folder has been built
TOP = ..

CORE_DIR      = $(TOP)/core
INCLUDE_DIR   = $(TOP)/include
GENCODECS_DIR = $(TOP)/gencodecs

TEST_DISCORD = racecond rest timeout
TEST_CORE    = user-agent websockets queriec

TESTS = $(TEST_DISCORD) $(TEST_GITHUB) $(TEST_CORE)

CFLAGS  = -O0 -g -pthread -Wall \
          -I$(INCLUDE_DIR) -I$(CORE_DIR) -I$(GENCODECS_DIR)
LDFLAGS = -L$(TOP)/lib
LDLIBS  = -ldiscord -lcurl

all: $(TESTS)

echo:
	@ echo -e 'CC: $(CC)\n'
	@ echo -e 'TESTS: $(TESTS)\n'

clean:
	@ rm -f $(TESTS)

.PHONY: all echo clean
