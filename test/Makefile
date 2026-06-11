# This Makefile assumes the top folder has been built
#
# Hermetic rule: tests listed in TESTS_HERMETIC must never read test_config.json
# credentials or open non-loopback sockets. They must pass on a fresh clone with
# no Discord token present. Tests that require a live bot token belong in TESTS_LIVE.
TOP = ..

CORE_DIR      = $(TOP)/core
INCLUDE_DIR   = $(TOP)/include
GENCODECS_DIR = $(TOP)/gencodecs

# Hermetic: no credentials, no non-loopback sockets — always runnable
TESTS_HERMETIC = queriec \
                 unit-cog-utils unit-json-build unit-jsmn-find \
                 unit-anomap unit-oa_hash unit-priority_queue \
                 unit-threadpool unit-fixtures-smoke unit-codec-decode \
                 unit-codec-encode unit-ratelimit
# Live: require Discord token in test_config.json
TESTS_LIVE     = racecond rest timeout websockets

TESTS = $(TESTS_HERMETIC) $(TESTS_LIVE)

CFLAGS  = -O0 -g -pthread -Wall \
          -I$(INCLUDE_DIR) -I$(CORE_DIR) -I$(GENCODECS_DIR)
LDFLAGS = -L$(TOP)/lib
LDLIBS  = -ldiscord -lcurl

all: $(TESTS)

check: $(TESTS_HERMETIC)
	@for t in $(TESTS_HERMETIC); do \
		printf '  RUN  %s\n' $$t; \
		./$$t || exit 1; \
	done

echo:
	@ echo -e 'CC: $(CC)\n'
	@ echo -e 'TESTS: $(TESTS)\n'

clean:
	@ rm -f $(TESTS)

.PHONY: all check echo clean
