# AGENTS.md

Concord is a Discord API wrapper library written in C, built with plain Makefiles. Its only external dependency is libcurl (built with WebSocket support).

## Build and test

```sh
make            # build static library (lib/libdiscord.a)
make check      # build + run the hermetic test suites (the development gate)
make check-san  # same, rebuilt from clean under ASan/UBSan; SANFLAGS overridable
make test       # BUILD test binaries only — it does not run them
make clean
```

- Tests live in `test/` and use the vendored `greatest.h`; see `test/README.md` for the hermetic/live split and conventions. The suites `rest`, `racecond`, and `timeout` are LIVE tests: they need a real bot token in `test/test_config.json` and hit the real Discord API (`make check-live` runs the automatable subset after a credential preflight). Never run them unattended; do not treat them as a development gate.
- CI (`.github/workflows/test_build.yml`) runs `make check` on Linux/macOS plus ASan/UBSan and TSan jobs (`make check-san`) on every push and pull request.

## Layout

- `core/` — transport and utility layer: `user-agent.c` (REST/curl-easy), `websockets.c` (curl WS), `io_poller.c`, containers, JSON (`jsmn-find.h`, `json-build.h`). libcurl usage is confined to `core/` plus `src/discord-rest_request.c` and `src/discord-gateway.c`.
- `src/` — Discord client: REST scheduler (`discord-rest*.c`), gateway (`discord-gateway*.c`), per-resource endpoint files (`channel.c`, `guild.c`, ...).
- `gencodecs/api/*.PRE.h` — macro specs that generate all JSON codecs and params structs. **Codec bugs are fixed here, never in generated output** (`generated/`, or headers produced at build time). The top-level `make` regenerates.
- `include/` — public headers. `docs/CODING_GUIDELINES.md` covers style; `.clang-format` exists.
- `test/`, `examples/`, `docs/`.

## Gotchas

- `.gitignore` is a whitelist (`*` ignored, then `!` rules). Any NEW file or directory you add is invisible to git until whitelisted — always verify with `git status` that your files are actually tracked.
- Useful test seams that already exist: `ua_conn_attr.base_url` (core/user-agent.h) for redirecting REST, and the `ws_*` interface (core/websockets.h) as the gateway's only network boundary.
