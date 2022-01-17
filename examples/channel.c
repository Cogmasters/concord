#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h> /* PRIu64 */
#include <assert.h>

#include "discord.h"

void
print_usage(void)
{
    printf(
        "\n\n(USE WITH CAUTION) This bot demonstrates how easy it is to "
        "create/delete channels\n"
        "1. Type 'channel.create <channel_name>' anywhere to create a new "
        "channel\n"
        "2. Type 'channel.rename_this <channel_name>' to rename the current "
        "channel\n"
        "3. Type 'channel.delete_this' to delete the current channel\n"
        "4. Type 'channel.get_invites' to check how many have been created\n"
        "5. Type 'channel.create_invite' to create a new invite\n"
        "6. Type 'channel.start_thread' to start a new thread (reply to a "
        "message if you wish start a thread under it)\n"
        "\nTYPE ANY KEY TO START BOT\n");
}

void
on_ready(struct discord *client)
{
    const struct discord_user *bot = discord_get_self(client);

    log_info("Channel-Bot succesfully connected to Discord as %s#%s!",
             bot->username, bot->discriminator);
}

void
log_on_channel_create(struct discord *client,
                      const struct discord_channel *channel)
{
    log_info("Channel %s (%" PRIu64 ") created", channel->name, channel->id);
}

void
log_on_channel_update(struct discord *client,
                      const struct discord_channel *channel)
{
    log_info("Channel %s (%" PRIu64 ") updated", channel->name, channel->id);
}

void
log_on_channel_delete(struct discord *client,
                      const struct discord_channel *channel)
{
    log_info("Channel %s (%" PRIu64 ") deleted", channel->name, channel->id);
}

void
log_on_thread_create(struct discord *client,
                     const struct discord_channel *thread)
{
    log_info("Thread %s (%" PRIu64 ") created", thread->name, thread->id);
}

void
log_on_thread_update(struct discord *client,
                     const struct discord_channel *thread)
{
    log_info("Thread %s (%" PRIu64 ") updated", thread->name, thread->id);
}

void
log_on_thread_delete(struct discord *client,
                     const struct discord_channel *thread)
{
    log_info("Thread %s (%" PRIu64 ") deleted", thread->name, thread->id);
}

void
on_channel_create(struct discord *client, const struct discord_message *msg)
{
    if (msg->author->bot) return;

    struct discord_create_guild_channel params = { .name = msg->content };
    discord_create_guild_channel(client, msg->guild_id, &params, NULL);
}

void
on_channel_rename_this(struct discord *client,
                       const struct discord_message *msg)
{
    if (msg->author->bot) return;

    struct discord_modify_channel params = { .name = msg->content };
    discord_modify_channel(client, msg->channel_id, &params, NULL);
}

void
on_channel_delete_this(struct discord *client,
                       const struct discord_message *msg)
{
    if (msg->author->bot) return;

    discord_delete_channel(client, msg->channel_id, NULL);
}

void
done_get_channel_invites(struct discord *client,
                         void *data,
                         const struct discord_invite **invites)
{
    if (!invites) {
        log_info("No invites found!");
        return;
    }

    u64_snowflake_t *channel_id = data;

    char text[DISCORD_MAX_MESSAGE_LEN];
    snprintf(text, sizeof(text), "%zu invite links created.",
             ntl_length((ntl_t)invites));

    struct discord_create_message params = { .content = text };
    discord_create_message(client, *channel_id, &params, NULL);
}

void
fail_get_channel_invites(struct discord *client, CCORDcode code, void *data)
{
    (void)data;

    log_info("Couldn't fetch invites: %s", discord_strerror(code, client));
}

void
on_channel_get_invites(struct discord *client,
                       const struct discord_message *msg)
{
    if (msg->author->bot) return;

    u64_snowflake_t *channel_id = malloc(sizeof(u64_snowflake_t));
    *channel_id = msg->channel_id;

    struct discord_ret_invites ret = {
        .done = &done_get_channel_invites,
        .fail = &fail_get_channel_invites,
        .data = channel_id,
        .done_cleanup = &free,
        .fail_cleanup = &free,
    };
    discord_get_channel_invites(client, msg->channel_id, &ret);
}

void
done_create_channel_invite(struct discord *client,
                           void *data,
                           const struct discord_invite *invite)
{
    u64_snowflake_t *channel_id = data;
    char text[256];

    snprintf(text, sizeof(text), "https://discord.gg/%s", invite->code);

    struct discord_create_message params = { .content = text };
    discord_create_message(client, *channel_id, &params, NULL);
}

void
fail_create_channel_invite(struct discord *client, CCORDcode code, void *data)
{
    u64_snowflake_t *channel_id = data;

    struct discord_create_message params = {
        .content = "Couldn't create invite",
    };
    discord_create_message(client, *channel_id, &params, NULL);
}

void
on_channel_create_invite(struct discord *client,
                         const struct discord_message *msg)
{
    if (msg->author->bot) return;

    u64_snowflake_t *channel_id = malloc(sizeof(u64_snowflake_t));
    *channel_id = msg->channel_id;

    struct discord_ret_invite ret = {
        .done = &done_create_channel_invite,
        .fail = &fail_create_channel_invite,
        .data = channel_id,
        .done_cleanup = &free,
        .fail_cleanup = &free,
    };
    discord_create_channel_invite(client, msg->channel_id, NULL, &ret);
}

void
done_start_thread(struct discord *client,
                  void *data,
                  const struct discord_channel *thread)
{
    u64_snowflake_t *channel_id = data;
    char text[1024];

    snprintf(text, sizeof(text), "Created thread <#%" PRIu64 ">", *channel_id);

    struct discord_create_message params = { .content = text };
    discord_create_message(client, *channel_id, &params, NULL);
}

void
fail_start_thread(struct discord *client, CCORDcode code, void *data)
{
    u64_snowflake_t *channel_id = data;
    char text[1024];

    snprintf(text, sizeof(text), "Couldn't create thread: %s",
             discord_strerror(code, client));

    struct discord_create_message params = { .content = text };
    discord_create_message(client, *channel_id, &params, NULL);
}

void
on_channel_start_thread(struct discord *client,
                        const struct discord_message *msg)
{
    if (msg->author->bot) return;

    u64_snowflake_t *channel_id = malloc(sizeof(u64_snowflake_t));
    *channel_id = msg->channel_id;

    struct discord_ret_channel ret = {
        .done = &done_start_thread,
        .fail = &fail_start_thread,
        .data = channel_id,
        .done_cleanup = &free,
        .fail_cleanup = &free,
    };

    if (msg->message_reference) {
        struct discord_start_thread_with_message params = {
            .name = "new_thread",
        };
        discord_start_thread_with_message(client, msg->channel_id,
                                          msg->message_reference->message_id,
                                          &params, &ret);
    }
    else {
        struct discord_start_thread_without_message params = {
            .name = "new_thread",
            .type = DISCORD_CHANNEL_GUILD_PUBLIC_THREAD,
        };
        discord_start_thread_without_message(client, msg->channel_id, &params,
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
    assert(NULL != client && "Could not initialize client");

    discord_set_on_ready(client, &on_ready);
    discord_set_on_channel_create(client, &log_on_channel_create);
    discord_set_on_channel_update(client, &log_on_channel_update);
    discord_set_on_channel_delete(client, &log_on_channel_delete);
    discord_set_on_thread_create(client, &log_on_thread_create);
    discord_set_on_thread_update(client, &log_on_thread_update);
    discord_set_on_thread_delete(client, &log_on_thread_delete);

    discord_set_prefix(client, "channel.");
    discord_set_on_command(client, "create", &on_channel_create);
    discord_set_on_command(client, "rename_this", &on_channel_rename_this);
    discord_set_on_command(client, "delete_this", &on_channel_delete_this);
    discord_set_on_command(client, "get_invites", &on_channel_get_invites);
    discord_set_on_command(client, "create_invite", &on_channel_create_invite);
    discord_set_on_command(client, "start_thread", &on_channel_start_thread);

    print_usage();
    fgetc(stdin); // wait for input

    discord_run(client);

    discord_cleanup(client);
    ccord_global_cleanup();
}
