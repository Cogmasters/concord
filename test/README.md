# Test Suite

## Hermetic vs. live suites

Tests are split into two categories:

**Hermetic** (`TESTS_HERMETIC` in `test/Makefile`) — always runnable with no credentials and no
non-loopback network access. These gate development via `make check`.

**Live** (`TESTS_LIVE`) — require a real Discord bot token in `test_config.json` and access to a
live Discord server (or, for `websockets`, a running `wstest` server). Never run implicitly;
build them with `make test` and invoke manually.

The contract for hermetic tests: **do not read `test_config.json`, do not open sockets to
addresses outside `127.0.0.1`/`::1`.**

## Running tests

```sh
# Build the library and run all hermetic suites (CI entrypoint):
make check

# Build everything including live suites (no execution):
make test

# Run a single hermetic binary after make check:
./test/unit-anomap
```

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
