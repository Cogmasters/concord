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

Fixtures target the schema concord's gencodecs model (API v9/v10 era): they
keep `discriminator` and the legacy type-1/type-2 message components, and use
post-2023 keys such as `global_name` only as *unknown-key* hazards. When a
docs example diverges from what the deployed API actually sends, the docs
shape stays the default and the observed divergence is recorded as a new
named variant (e.g. `user-api-divergence-<reason>.json`).
