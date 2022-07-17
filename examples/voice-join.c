#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>

#include "discord.h"
#include "log.h"

void
print_usage(void)
{
    printf(
        "\n\nThis bot demonstrates some of the Discord Voice Connections "
        "interface\n"
        "1. Type 'voice.list_regions' to list regions that can be used when "
        "creating servers\n"
        "2. Type 'voice.join <channel position>' to join a particular voice "
        "channel by its position\n"
        "3. Type 'voice.kick <user id>' to kick a particular user from the "
        "voice channel they are at\n"
        "\nTYPE ANY KEY TO START BOT\n");
}

void
on_ready(struct discord *client, const struct discord_ready *event)
{
    log_info("Voice-Bot succesfully connected to Discord as %s#%s!",
             event->user->username, event->user->discriminator);
}

void
log_on_voice_state_update(struct discord *client,
                          const struct discord_voice_state *event)
{
    log_info("User <@!%" PRIu64 "> has joined <#%" PRIu64 ">!", event->user_id,
             event->channel_id);
}

void
done_list_voice_regions(struct discord *client,
                        struct discord_response *resp,
                        const struct discord_voice_regions *regions)
{
    const struct discord_message *event = resp->keep;

    for (int i = 0; i < regions->size; ++i) {
        struct discord_create_message params = { .content =
                                                     regions->array[i].name };
        discord_create_message(client, event->channel_id, &params, NULL);
    }
}

void
fail_list_voice_regions(struct discord *client, struct discord_response *resp)
{
    const struct discord_message *event = resp->keep;

    struct discord_create_message params = {
        .content = "Could not fetch voice regions"
    };
    discord_create_message(client, event->channel_id, &params, NULL);
}

void
on_list_voice_regions(struct discord *client,
                      const struct discord_message *event)
{
    if (event->author->bot) return;

    struct discord_ret_voice_regions ret = {
        .done = &done_list_voice_regions,
        .fail = &fail_list_voice_regions,
        .keep = event,
    };

    discord_list_voice_regions(client, &ret);
}

void
done_get_vchannel_position(struct discord *client,
                           struct discord_response *resp,
                           const struct discord_channel *vchannel)
{
    const struct discord_message *event = resp->keep;
    char text[256];

    discord_voice_join(client, event->guild_id, vchannel->id, false, false);

    snprintf(text, sizeof(text), "Joining <@!%" PRIu64 "> to <#%" PRIu64 ">!",
             discord_get_self(client)->id, vchannel->id);

    struct discord_create_message params = { .content = text };
    discord_create_message(client, event->channel_id, &params, NULL);
}

void
fail_get_vchannel_position(struct discord *client,
                           struct discord_response *resp)
{
    const struct discord_message *event = resp->keep;

    struct discord_create_message params = { .content =
                                                 "Invalid channel position" };
    discord_create_message(client, event->channel_id, &params, NULL);
}

void
on_voice_join(struct discord *client, const struct discord_message *event)
{
    if (event->author->bot) return;

    int position = -1;

    sscanf(event->content, "%d", &position);

    struct discord_ret_channel ret = {
        .done = &done_get_vchannel_position,
        .fail = &fail_get_vchannel_position,
        .keep = event,
    };

    discord_get_channel_at_pos(client, event->guild_id,
                               DISCORD_CHANNEL_GUILD_VOICE, position - 1,
                               &ret);
}

void
done_disconnect_guild_member(struct discord *client,
                             struct discord_response *resp,
                             const struct discord_guild_member *member)
{
    const struct discord_message *event = resp->keep;
    char text[256];

    snprintf(text, sizeof(text), "<@!%" PRIu64 "> has been kicked from VC",
             member->user->id);

    struct discord_create_message params = { .content = text };
    discord_create_message(client, event->channel_id, &params, NULL);
}

void
fail_disconnect_guild_member(struct discord *client,
                             struct discord_response *resp)
{
    const struct discord_message *event = resp->keep;

    struct discord_create_message params = {
        .content = "Couldn't disconnect user from voice channel"
    };
    discord_create_message(client, event->channel_id, &params, NULL);
}

void
on_voice_kick(struct discord *client, const struct discord_message *event)
{
    if (event->author->bot) return;

    u64snowflake user_id = 0;

    sscanf(event->content, "%" SCNu64, &user_id);

    if (!user_id) {
        struct discord_create_message params = { .content =
                                                     "Missing user ID" };
        discord_create_message(client, event->channel_id, &params, NULL);
    }
    else {
        struct discord_ret_guild_member ret = {
            .done = &done_disconnect_guild_member,
            .fail = &fail_disconnect_guild_member,
            .keep = event,
        };

        discord_disconnect_guild_member(client, event->guild_id, user_id,
                                        &ret);
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
