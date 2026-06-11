#ifndef CODEC_HARNESS_H
#define CODEC_HARNESS_H

#include <string.h>

#include "discord.h"
#include "discord-internal.h"

/* Codec suites need a struct discord only for its reflect-c registry —
 * every discord_data_* macro resolves it through discord_get_registry().
 * Use a real, zeroed struct discord so member access stays
 * compiler-checked (no layout assumptions), without booting the REST or
 * gateway machinery a full discord_init() would bring up.
 *
 * One registry serves the whole binary: discord_data_cleanup() erases
 * its registry entry, so stack addresses recycled across tests can't
 * alias stale wraps. */
static struct discord codec_harness_client;

static inline struct discord *
codec_harness_init(void)
{
    memset(&codec_harness_client, 0, sizeof codec_harness_client);
    if (!(codec_harness_client.registry = reflectc_init())) return NULL;
    return &codec_harness_client;
}

static inline void
codec_harness_cleanup(void)
{
    if (codec_harness_client.registry) {
        reflectc_dispose(codec_harness_client.registry);
        codec_harness_client.registry = NULL;
    }
}

#endif /* CODEC_HARNESS_H */
