# Test Fixtures

Versioned corpus of realistic Discord JSON payloads consumed by the hermetic
test suites (and nothing else — no fixture here requires credentials).

## Naming

One payload per file, named `<type>-<variant>.json`. The `basic` variant is
the realistic docs-shaped payload; `hazards` variants encode known decode
hazards: missing optional fields, explicit `null`s, empty arrays, unknown
extra keys (forward compatibility), and max-length strings.

## Provenance

Every fixture is adapted from the example payloads in the
[Discord developer documentation](https://discord.com/developers/docs), with
all snowflake IDs rewritten to obviously fake `1000000000000000xxx` values
and all tokens/hashes replaced with fake data.

| Fixture family | Source |
| --- | --- |
| `user-*` | <https://discord.com/developers/docs/resources/user#user-object> |
| `guild-*` | <https://discord.com/developers/docs/resources/guild#guild-object> |
| `guild-member-*` | <https://discord.com/developers/docs/resources/guild#guild-member-object> |
| `channel-*` | <https://discord.com/developers/docs/resources/channel#channel-object> |
| `message-*` | <https://discord.com/developers/docs/resources/message#message-object> |
| `role-*` | <https://discord.com/developers/docs/topics/permissions#role-object> |
| `emoji-*` | <https://discord.com/developers/docs/resources/emoji#emoji-object> |
| `interaction-*` | <https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-object> |
| `gateway-*` | <https://discord.com/developers/docs/events/gateway-events> |
| `guild-member-add/update/remove` | <https://discord.com/developers/docs/events/gateway-events#guild-member-add> |
| `message-reaction-add` | <https://discord.com/developers/docs/events/gateway-events#message-reaction-add> |
| `modify-guild-sticker-params` | <https://discord.com/developers/docs/resources/sticker#modify-guild-sticker> |

Fixtures target the schema concord's recipes model (API v9/v10 era): they
keep `discriminator` and the legacy type-1/type-2 message components, and use
post-2023 keys such as `global_name` only as *unknown-key* hazards. When a
docs example diverges from what the deployed API actually sends, the docs
shape stays the default and the observed divergence is recorded as a new
named variant (e.g. `user-api-divergence-<reason>.json`).

## Codec regression workflow

Found a codec bug (field decodes empty, wrong key on the wire, field
missing from a request body)? Make it a fixture before making it a fix:

1. Add a fixture variant here reproducing the payload that misbehaves.
2. Add the failing assertion to `unit-codec-decode.c` (decode bugs) or
   `unit-codec-encode.c` (encode bugs) and watch it go red.
3. Fix the recipe in `src/api/*.recipe.h` — **never** the generated
   `generated/discord_codecs.c`/`.h` — and regenerate with
   `make reflectc-gen`.
4. `make check` goes green; commit the recipe fix and the test separately
   (`fix(recipes): ...` then `feat(test): ...`).

Worked example: `discord_modify_guild_sticker.reason` (commit 7eec9aef)
is the audit-log *header* param, so it lives on the params struct but
must never appear in the JSON body —
`modify-guild-sticker-params.json` plus the
`regression_modify_guild_sticker` suite in `unit-codec-encode.c` pin
that behavior. Likewise the guild member voice-mute flag arrives under
the `"mute"` key (not `"muted"`), pinned by `member_basic` in
`unit-codec-decode.c`.
