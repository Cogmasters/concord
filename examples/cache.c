
#include "discord.h"

static void
on_message(struct discord *client, const struct discord_message *message)
{
    if (message->author->bot) return;

    const struct discord_guild *guild =
        discord_cache_get_guild(client, message->guild_id);
    if (guild) {
        printf("message received in guild '%s'\n", guild->name);
        discord_unclaim(client, guild);
    }

    // check if this message is in the cache, NULL if it isn't
    const struct discord_message *cached_message =
        discord_cache_get_channel_message(client, message->channel_id,
                                          message->id);

    if (cached_message) {
        // discord_claim(cached_message); is implicit
        discord_create_message(client, cached_message->channel_id,
                               &(struct discord_create_message){
                                   .content = cached_message->content,
                               },
                               NULL);

        // don't forget to clean up cached message when done
        discord_unclaim(client, cached_message);
    }
}

int
main(int argc, char *argv[])
{
    const char *const config_file = argc > 1 ? argv[1] : "../config.json";
    ccord_global_init();
    struct discord *client = discord_config_init(config_file);

    // enable message caching
    discord_cache_enable(client,
                         DISCORD_CACHE_MESSAGES | DISCORD_CACHE_GUILDS);

    discord_add_intents(client, DISCORD_GATEWAY_MESSAGE_CONTENT);
    discord_set_on_message_create(client, on_message);

    discord_run(client);
    discord_cleanup(client);
    ccord_global_cleanup();
}