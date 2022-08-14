#include "discord.h"
#include "discord-internal.h"
#include "chash.h"

struct _discord_cache_data {
    enum discord_cache_options options;
};

#define EV_CB(name, data)                                                     \
    static void _on_##name(struct discord *client, const struct data *ev)

EV_CB(guild_create, discord_guild)
{
    struct _discord_cache_data *data = client->cache.data;
}

EV_CB(guild_update, discord_guild) {}
EV_CB(guild_delete, discord_guild) {}

EV_CB(channel_create, discord_channel) {}
EV_CB(channel_update, discord_channel) {}
EV_CB(channel_delete, discord_channel) {}

EV_CB(guild_role_create, discord_guild_role_create) {}
EV_CB(guild_role_update, discord_guild_role_update) {}
EV_CB(guild_role_delete, discord_guild_role_delete) {}

EV_CB(message_create, discord_message) {}
EV_CB(message_update, discord_message) {}
EV_CB(message_delete, discord_message_delete) {}

#define ASSIGN_CB(ev, cb) client->gw.cbs[0][ev] = (discord_ev_event)_on_##cb

static void
_discord_cache_cleanup(struct discord *client)
{
}

void
discord_enable_cache(struct discord *client,
                     enum discord_cache_options options)
{
    struct _discord_cache_data *data;
    if (client->cache.data)
        data = client->cache.data;
    else {
        client->cache.cleanup = _discord_cache_cleanup;
        data = client->cache.data = calloc(1, sizeof *data);
    }
    data->options |= options;

    if (options & DISCORD_CACHE_GUILDS) {
        discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
        ASSIGN_CB(DISCORD_EV_GUILD_CREATE, guild_create);
        ASSIGN_CB(DISCORD_EV_GUILD_UPDATE, guild_update);
        ASSIGN_CB(DISCORD_EV_GUILD_DELETE, guild_delete);

        ASSIGN_CB(DISCORD_EV_CHANNEL_CREATE, channel_create);
        ASSIGN_CB(DISCORD_EV_CHANNEL_UPDATE, channel_update);
        ASSIGN_CB(DISCORD_EV_CHANNEL_DELETE, channel_delete);

        ASSIGN_CB(DISCORD_EV_GUILD_ROLE_CREATE, guild_role_create);
        ASSIGN_CB(DISCORD_EV_GUILD_ROLE_UPDATE, guild_role_update);
        ASSIGN_CB(DISCORD_EV_GUILD_ROLE_DELETE, guild_role_delete);
    }

    if (0) {
        ASSIGN_CB(DISCORD_EV_MESSAGE_CREATE, message_create);
        ASSIGN_CB(DISCORD_EV_MESSAGE_UPDATE, message_update);
        ASSIGN_CB(DISCORD_EV_MESSAGE_DELETE, message_delete);
    }
}
