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
                 unit-codec-encode unit-ratelimit unit-fixture-server \
                 unit-base-url rest-integration ratelimit-integration \
                 unit-mockws unit-gateway-lifecycle unit-gateway-resume \
                 unit-gateway-dispatch
# Live: require Discord token in test_config.json
TESTS_LIVE     = racecond rest timeout websockets

TESTS = $(TESTS_HERMETIC) $(TESTS_LIVE)

CFLAGS  = -O0 -g -pthread -Wall \
          -I$(INCLUDE_DIR) -I$(CORE_DIR) -I$(GENCODECS_DIR)
LDFLAGS = -L$(TOP)/lib
LDLIBS  = -ldiscord -lcurl

all: $(TESTS)

# suites linking the fixture server (implicit rules only handle
# single-source tests)
TESTS_FIXTURE_SERVER = unit-fixture-server unit-base-url \
                       rest-integration ratelimit-integration

$(TESTS_FIXTURE_SERVER): %: %.c fixture-server.c fixture-server.h \
                         test-client.h test-utils.h $(TOP)/lib/libdiscord.a
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< fixture-server.c $(LDLIBS)

# gateway suites substitute core/websockets.o with the mock transport;
# mock-websockets.o is linked before -ldiscord so every ws_* symbol
# resolves to the mock and the archive member is never pulled in
TESTS_MOCK_WS = unit-mockws
# gateway suites additionally boot a real client via the fixture server
TESTS_GATEWAY = unit-gateway-lifecycle unit-gateway-resume \
                unit-gateway-dispatch

mock-websockets.o: mock-websockets.c mock-websockets.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(TESTS_MOCK_WS): %: %.c mock-websockets.o test-utils.h \
                  $(TOP)/lib/libdiscord.a
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< mock-websockets.o $(LDLIBS)

$(TESTS_GATEWAY): %: %.c mock-websockets.o gateway-harness.h \
                  fixture-server.c fixture-server.h test-client.h \
                  test-utils.h $(TOP)/lib/libdiscord.a
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< fixture-server.c \
	    mock-websockets.o $(LDLIBS)

check: $(TESTS_HERMETIC)
	@for t in $(TESTS_HERMETIC); do \
		printf '  RUN  %s\n' $$t; \
		./$$t || exit 1; \
	done

echo:
	@ echo -e 'CC: $(CC)\n'
	@ echo -e 'TESTS: $(TESTS)\n'

clean:
	@ rm -f $(TESTS) mock-websockets.o

.PHONY: all check echo clean
