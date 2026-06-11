# Test Suite

## Hermetic vs. live suites

Tests are split into two categories:

**Hermetic** (`TESTS_HERMETIC` in `test/Makefile`) — always runnable with no credentials and no
non-loopback network access. These gate development via `make check`.

**Live** (`TESTS_LIVE`) — require a real Discord bot token in `test_config.json` and access to a
live Discord server (or, for `websockets`, a running `wstest` server). Never run implicitly;
they are pre-release smoke checks, run manually — see "Live smoke suites" below.

The contract for hermetic tests: **do not read `test_config.json`, do not open sockets to
addresses outside `127.0.0.1`/`::1`.**

## Running tests

```sh
# Build the library and run all hermetic suites (CI entrypoint):
make check

# Same, but compiled with AddressSanitizer/UndefinedBehaviorSanitizer.
# Always rebuilds from clean; run `make clean` before going back to
# normal builds so no sanitized objects linger:
make check-san

# Live smoke run against real Discord (needs credentials, see below):
make check-live

# Build everything including live suites (no execution):
make test

# Run a single hermetic binary after make check:
./test/unit-anomap
```

`make check-san` accepts an alternate sanitizer via
`make check-san SANFLAGS="-fsanitize=thread"`. CI runs `make check` on
Linux/macOS and `make check-san` on Linux for every push and pull request.

## Live smoke suites

Hermetic tests verify concord against its understanding of Discord; the live
suites verify that understanding against the real service (API changes,
undocumented behavior). They are deliberately **human-run** — before releases
and after Discord API version bumps — and are never part of the development
gate or CI.

Requirements: a bot token in `test_config.json` (`discord.token`) and a text
channel the bot can read and send messages in (`test.channel_id`). With
placeholder values still in place, `make check-live` refuses to run before
building anything.

`make check-live` runs `rest` — sync and async REST smoke checks
(current-user fetch, guild listing, error paths on bogus requests) that
exit on their own. The remaining live suites need a human in the loop and
are run directly from `test/`:

- `racecond` — gateway/threadpool stress bot. Start it, then drive it by
  typing `!racecond spam_threads` (and the other `!racecond` commands listed
  in its source) in the test channel; type `!racecond disconnect` to exit.
- `timeout` — timer/wakeup behavior. Observe the cycle/wakeup/idle output
  alternating as documented in `main()`; stop with Ctrl-C.
- `websockets` — autobahn-testsuite compliance client for the `ws_*`
  transport. Needs a local `wstest -m fuzzingserver` (no Discord
  credentials); run it with `-u ws://localhost:9001 -s 1 -e 260`.

`rest.c` and `timeout.c` keep more depth than a smoke layer needs; they will
be slimmed once the hermetic REST integration suites (roadmap scope C04)
fully replace their assertions.

## Adding a new hermetic suite

1. Create `test/unit-<module>.c` using `greatest.h` and `test-utils.h`:

   ```c
   #include "greatest.h"
   #include "test-utils.h"

   TEST my_test(void) {
       ASSERT_EQ(1, 1);
       PASS();
   }

   SUITE(my_module) {
       RUN_TEST(my_test);
   }

   GREATEST_MAIN_DEFS();
   int main(int argc, char *argv[]) {
       GREATEST_MAIN_BEGIN();
       RUN_SUITE(my_module);
       GREATEST_MAIN_END();
   }
   ```

2. Add the binary name to `TESTS_HERMETIC` in `test/Makefile`.

3. Verify with `make check`.

Single-source suites build via the implicit `%: %.c` rule. Suites that
link extra objects belong in one of the explicit Makefile groups:

- `TESTS_FIXTURE_SERVER` — REST suites linking `fixture-server.c` (an
  in-process loopback HTTP server) and booting a real client against it
  via `test-client.h`.
- `TESTS_MOCK_WS` / `TESTS_GATEWAY` — gateway suites linking
  `mock-websockets.o` *before* `-ldiscord`, which substitutes every
  `ws_*` symbol so the real `core/websockets.o` is never pulled from
  the archive. `TESTS_GATEWAY` suites additionally link the fixture
  server and boot through `gateway-harness.h` (full client, mock
  transport, `discord_gateway_start()` bypassed); the mock's control
  API lives in `mock-websockets.h`.

## Shared test helpers (`test-utils.h`)

| Helper | Purpose |
|---|---|
| `test_load_fixture(path, &buf, &len)` | Load a file into a malloc'd buffer |
| `test_load_json_fixture(name, &len)` | Load `test/fixtures/<name>` into a returned malloc'd buffer |
| `test_json_load/_unload(&tj, js, len)` | Heap-parse a JSON document of any size for path lookups |
| `test_json_get(&tj, "a.b.0.c")` | Dotted-path lookup; array elements by decimal index; NULL if absent |
| `ASSERT_JSON_HAS/ABSENT(&tj, path)` | Assert a path exists / does not exist |
| `ASSERT_JSON_PATH_STR(&tj, path, expected)` | Assert the raw token text at a path (quotes stripped) |
| `ASSERT_JSON_SAME(&exp, &got, path)` | Assert a path's token text is identical in two documents |

Fixture files live in `test/fixtures/` — see `test/fixtures/README.md` for
naming, provenance, and the codec regression workflow.
