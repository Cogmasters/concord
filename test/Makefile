# This Makefile assumes the top folder has been built
#
# Hermetic rule: tests listed in TESTS_HERMETIC must never read test_config.json
# credentials or open non-loopback sockets. They must pass on a fresh clone with
# no Discord token present. Tests that require a live bot token belong in TESTS_LIVE.
TOP = ..

CORE_DIR      = $(TOP)/core
INCLUDE_DIR   = $(TOP)/include
GENERATED_DIR = $(TOP)/generated
REFLECTC_DIR  = $(TOP)/reflect-c

# Hermetic: no credentials, no non-loopback sockets — always runnable
TESTS_HERMETIC = queriec \
                 unit-cog-utils unit-json-build unit-jsmn-find \
                 unit-anomap unit-oa_hash unit-priority_queue \
                 unit-threadpool unit-fixtures-smoke unit-codec-decode \
                 unit-codec-encode unit-ratelimit unit-fixture-server \
                 unit-base-url unit-client-log rest-integration \
                 ratelimit-integration \
                 unit-mockws unit-gateway-lifecycle unit-gateway-resume \
                 unit-gateway-dispatch discord-data-wrap
# Live: require Discord token in test_config.json
TESTS_LIVE     = racecond rest timeout websockets

TESTS = $(TESTS_HERMETIC) $(TESTS_LIVE)

# += so sanitizer flags passed via the environment (top-level check-san)
# reach test compilation and linking too
CFLAGS += -O0 -g -pthread -Wall \
          -I$(INCLUDE_DIR) -I$(CORE_DIR) -I$(GENERATED_DIR) -I$(REFLECTC_DIR)
LDFLAGS = -L$(TOP)/lib
LDLIBS  = -ldiscord -lcurl

all: $(TESTS)

# suites linking the fixture server (implicit rules only handle
# single-source tests)
TESTS_FIXTURE_SERVER = unit-fixture-server unit-base-url unit-client-log \
                       rest-integration ratelimit-integration

$(TESTS_FIXTURE_SERVER): %: %.c fixture-server.c fixture-server.h \
                         test-client.h test-utils.h $(TOP)/lib/libdiscord.a
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< fixture-server.c $(LDLIBS)

# codec suites depend on the codec harness header (make has no header
# dependency tracking; the implicit rule would miss edits to it)
TESTS_CODEC = unit-codec-decode unit-codec-encode

$(TESTS_CODEC): %: %.c codec-harness.h test-utils.h \
                $(TOP)/lib/libdiscord.a
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LDLIBS)

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

# Refuses before building anything so a placeholder config fails immediately
check-live-preflight:
	@ if ! [ -f test_config.json ]; then \
		echo 'error: test/test_config.json not found'; exit 1; fi
	@ if grep -qE 'YOUR-BOT-TOKEN|TEST-CHANNEL-ID' test_config.json; then \
		echo 'error: test_config.json still contains placeholder credentials.'; \
		echo 'Set discord.token and test.channel_id to real values for a live smoke run.'; \
		exit 1; fi

# Live smoke runner: only `rest` self-terminates; racecond/timeout/websockets
# are interactive harnesses — see README.md
check-live: check-live-preflight $(TESTS_LIVE)
	@ printf '  RUN  %s\n' rest; ./rest

echo:
	@ echo -e 'CC: $(CC)\n'
	@ echo -e 'TESTS: $(TESTS)\n'

clean:
	@ rm -f $(TESTS) mock-websockets.o

.PHONY: all check check-live check-live-preflight echo clean
