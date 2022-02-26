#include "discord.h"
#include "discord-internal.h"
#include "cog-utils.h"

#define SHARD client->shards.array[0]
#define GW client->shards.array[0].gw

enum gw_status {
    GW_RECONNECT,
    GW_RUNNING,
    GW_QUIT,
    GW_DONE,
};

struct internal {
    enum gw_status status;
};

static CCORDcode
controller_init(struct discord *client) {
    client->shards.controller.internal = calloc(1, sizeof(struct internal));
    client->shards.array =
        calloc(client->shards.total = 1, sizeof *client->shards.array);
    client->shards.total = 1;
    SHARD.client = client;
    SHARD.gw = calloc(1, sizeof *GW);
    SHARD.shard = 0;
    discord_gateway_init(&SHARD, GW, &client->conf, &client->token);
    if (client->shards.cbs.on_shard_enabled)
        client->shards.cbs.on_shard_enabled(client, 0, true);
    return CCORD_OK;
}

static CCORDcode
controller_shutdown(struct discord *client) {
    if (client->shards.cbs.on_shard_enabled)
        client->shards.cbs.on_shard_enabled(client, 0, false);
    discord_gateway_shutdown(GW);
    return CCORD_OK;
}

static void
controller_reconnect(struct discord *client, bool resume) {
    discord_gateway_reconnect(GW, resume);
}

static CCORDcode
controller_destroy(struct discord *client) {
    discord_gateway_cleanup(GW);
    free(GW);
    free(client->shards.array);
    free(client->shards.controller.internal);
    client->shards.array = NULL;
    return CCORD_OK;
}

static CCORDcode
controller_perform(struct discord *client) {
    struct internal *internal = client->shards.controller.internal;
    CCORDcode code;
    switch (internal->status) {
    case GW_RECONNECT:
        if (CCORD_OK == (code = discord_gateway_start(GW))) {
            internal->status = GW_RUNNING;
            client->shards.active.count = 1;
        } else {
            internal->status = GW_QUIT;
            return code;
        }
        //fallthru
    case GW_RUNNING:
        if (CCORD_OK == (code = discord_gateway_perform(GW)))
            break;
        client->shards.active.count = 0;
        internal->status = GW_QUIT;
        //fallthru
    case GW_QUIT:
        if (!discord_gateway_end(GW)) {
            internal->status = GW_RECONNECT;
            break;
        }
        internal->status = GW_DONE;
        //fallthru
    case GW_DONE:
        return CCORD_DISCORD_CONNECTION;
    }
    return CCORD_OK;
}

static void
controller_set_presence(struct discord *client,
                  struct discord_presence_update *presence)
{
    memcpy(SHARD.gw->id.presence, presence, sizeof *presence);
    discord_gateway_send_presence_update(SHARD.gw);
}


static int
controller_get_ping(struct discord *client) {

    int ping_ms;
    pthread_rwlock_rdlock(&GW->timer->rwlock);
    ping_ms = GW->timer->ping_ms;
    pthread_rwlock_unlock(&GW->timer->rwlock);
    return ping_ms;
}

void
discord_sharding_use_none(struct discord *client) {
    struct discord_shard_controller *controller = &client->shards.controller;
    controller->init = controller_init;
    controller->shutdown = controller_shutdown;
    controller->reconnect = controller_reconnect;
    controller->destroy = controller_destroy;
    controller->perform = controller_perform;
    controller->set_presence = controller_set_presence;
    controller->get_ping = controller_get_ping;
}
