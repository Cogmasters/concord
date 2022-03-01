#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>

#include "discord.h"

struct context {
    u64snowflake channel_id;
    u64snowflake guild_id;
};

void
print_usage(void)
{
    printf(
        "\n\nThis bot is a work in progress, it should demonstrate some "
        "Voice related utilities\n"
        "1. Type 'voice.list_regions' to list regions that can be used when "
        "creating servers\n"
        "2. Type 'voice.join <channel position>' to join a particular voice "
        "channel by its position\n"
        "3. Type 'voice.kick <user id>' to kick a particular user from the "
        "voice channel he's at\n"
        "\nTYPE ANY KEY TO START BOT\n");
}

void
log_on_voice_state_update(struct discord *client,
                          const struct discord_voice_state *vs)
{
    log_info("User <@!%" PRIu64 "> has joined <#%" PRIu64 ">!", vs->user_id,
             vs->channel_id);
}

void
on_ready(struct discord *client)
{
    const struct discord_user *bot = discord_get_self(client);

    log_info("Voice-Bot succesfully connected to Discord as %s#%s!",
             bot->username, bot->discriminator);
}

void
done_list_voice_regions(struct discord *client,
                        void *data,
                        const struct discord_voice_regions *regions)
{
    struct context *cxt = data;

    for (int i = 0; i < regions->size; ++i) {
        struct discord_create_message params = { .content =
                                                     regions->array[i].name };
        discord_create_message(client, cxt->channel_id, &params, NULL);
    }
}

void
fail_list_voice_regions(struct discord *client, CCORDcode code, void *data)
{
    struct context *cxt = data;

    struct discord_create_message params = {
        .content = "Could not fetch voice regions"
    };
    discord_create_message(client, cxt->channel_id, &params, NULL);
}

void
on_list_voice_regions(struct discord *client,
                      const struct discord_message *msg)
{
    if (msg->author->bot) return;

    u64snowflake *channel_id = malloc(sizeof(u64snowflake));
    *channel_id = msg->channel_id;

    struct discord_ret_voice_regions ret = {
        .done = &done_list_voice_regions,
        .fail = &fail_list_voice_regions,
        .data = channel_id,
        .cleanup = &free,
    };

    discord_list_voice_regions(client, &ret);
}

void
done_get_vchannel_position(struct discord *client,
                           void *data,
                           const struct discord_channel *vchannel)
{
    struct context *cxt = data;
    char text[256];

    discord_voice_join(client, cxt->guild_id, vchannel->id, false, false);

    snprintf(text, sizeof(text), "Joining <@!%" PRIu64 "> to <#%" PRIu64 ">!",
             discord_get_self(client)->id, vchannel->id);

    struct discord_create_message params = { .content = text };
    discord_create_message(client, cxt->channel_id, &params, NULL);
}

void
fail_get_vchannel_position(struct discord *client, CCORDcode code, void *data)
{
    struct context *cxt = data;

    struct discord_create_message params = { .content =
                                                 "Invalid channel position" };
    discord_create_message(client, cxt->channel_id, &params, NULL);
}

void
on_voice_join(struct discord *client, const struct discord_message *msg)
{
    if (msg->author->bot) return;

    int position = -1;

    sscanf(msg->content, "%d", &position);

    struct context *cxt = malloc(sizeof(struct context));
    cxt->channel_id = msg->channel_id;
    cxt->guild_id = msg->guild_id;

    struct discord_ret_channel ret = {
        .done = &done_get_vchannel_position,
        .fail = &fail_get_vchannel_position,
        .data = cxt,
        .cleanup = &free,
    };

    discord_get_channel_at_pos(client, msg->guild_id,
                               DISCORD_CHANNEL_GUILD_VOICE, position - 1,
                               &ret);
}

void
done_disconnect_guild_member(struct discord *client,
                             void *data,
                             const struct discord_guild_member *member)
{
    struct context *cxt = data;
    char text[256];

    snprintf(text, sizeof(text), "<@!%" PRIu64 "> has been kicked from VC",
             member->user->id);

    struct discord_create_message params = { .content = text };
    discord_create_message(client, cxt->channel_id, &params, NULL);
}

void
fail_disconnect_guild_member(struct discord *client,
                             CCORDcode code,
                             void *data)
{
    struct context *cxt = data;

    struct discord_create_message params = {
        .content = "Couldn't disconnect user from voice channel"
    };
    discord_create_message(client, cxt->channel_id, &params, NULL);
}

void
on_voice_kick(struct discord *client, const struct discord_message *msg)
{
    if (msg->author->bot) return;

    u64snowflake user_id = 0;

    sscanf(msg->content, "%" SCNu64, &user_id);

    if (!user_id) {
        struct discord_create_message params = { .content =
                                                     "Missing user ID" };
        discord_create_message(client, msg->channel_id, &params, NULL);
    }
    else {
        struct context *cxt = malloc(sizeof(struct context));
        cxt->channel_id = msg->channel_id;
        cxt->guild_id = msg->guild_id;

        struct discord_ret_guild_member ret = {
            .done = &done_disconnect_guild_member,
            .fail = &fail_disconnect_guild_member,
            .data = cxt,
            .cleanup = &free,
        };

        discord_disconnect_guild_member(client, msg->guild_id, user_id, &ret);
    }
}

int
main(int argc, char *argv[])
{
    const char *config_file;
    if (argc > 1)
        config_file = argv[1];
    else
        config_file = "../config.json";

    ccord_global_init();
    struct discord *client = discord_config_init(config_file);
    assert(NULL != client && "Couldn't initialize client");

    discord_set_on_voice_state_update(client, &log_on_voice_state_update);

    discord_set_prefix(client, "voice.");
    discord_set_on_command(client, "list_regions", &on_list_voice_regions);
    discord_set_on_command(client, "join", &on_voice_join);
    discord_set_on_command(client, "kick", &on_voice_kick);

    print_usage();
    fgetc(stdin); // wait for input

    discord_run(client);

    discord_cleanup(client);
    ccord_global_cleanup();
}
