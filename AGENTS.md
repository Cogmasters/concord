# AGENTS.md

Concord is a Discord API wrapper library written in C, built with plain Makefiles. Its only external dependency is libcurl (built with WebSocket support).

## Build and test

```sh
make            # build static library (lib/libdiscord.a)
make test       # BUILD test binaries only — it does not run them
make clean
```

- Tests live in `test/` and use the vendored `greatest.h`. The suites `rest`, `racecond`, and `timeout` are LIVE tests: they need a real bot token in `test/test_config.json` and hit the real Discord API. Never run them unattended; do not treat them as a development gate.
- CI (`.github/workflows/test_build.yml`) builds everything on Linux/macOS but does not execute tests yet.

## Layout

- `core/` — transport and utility layer: `user-agent.c` (REST/curl-easy), `websockets.c` (curl WS), `io_poller.c`, containers, JSON (`jsmn-find.h`, `json-build.h`). libcurl usage is confined to `core/` plus `src/discord-rest_request.c` and `src/discord-gateway.c`.
- `src/` — Discord client: REST scheduler (`discord-rest*.c`), gateway (`discord-gateway*.c`), per-resource endpoint files (`channel.c`, `guild.c`, ...).
- `gencodecs/api/*.PRE.h` — macro specs that generate all JSON codecs and params structs. **Codec bugs are fixed here, never in generated output** (`generated/`, or headers produced at build time). The top-level `make` regenerates.
- `include/` — public headers. `docs/CODING_GUIDELINES.md` covers style; `.clang-format` exists.
- `test/`, `examples/`, `docs/`.

## Gotchas

- `.gitignore` is a whitelist (`*` ignored, then `!` rules). Any NEW file or directory you add is invisible to git until whitelisted — always verify with `git status` that your files are actually tracked.
- Useful test seams that already exist: `ua_conn_attr.base_url` (core/user-agent.h) for redirecting REST, and the `ws_*` interface (core/websockets.h) as the gateway's only network boundary.
