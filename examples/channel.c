#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h> /* PRIu64 */
#include <assert.h>

#include "discord.h"
#include "log.h"

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
on_ready(struct discord *client, const struct discord_ready *event)
{
    log_info("Channel-Bot succesfully connected to Discord as %s#%s!",
             event->user->username, event->user->discriminator);
}

void
log_on_channel_create(struct discord *client,
                      const struct discord_channel *event)
{
    log_info("Channel %s (%" PRIu64 ") created", event->name, event->id);
}

void
log_on_channel_update(struct discord *client,
                      const struct discord_channel *event)
{
    log_info("Channel %s (%" PRIu64 ") updated", event->name, event->id);
}

void
log_on_channel_delete(struct discord *client,
                      const struct discord_channel *event)
{
    log_info("Channel %s (%" PRIu64 ") deleted", event->name, event->id);
}

void
log_on_thread_create(struct discord *client,
                     const struct discord_channel *event)
{
    log_info("Thread %s (%" PRIu64 ") created", event->name, event->id);
}

void
log_on_thread_update(struct discord *client,
                     const struct discord_channel *event)
{
    log_info("Thread %s (%" PRIu64 ") updated", event->name, event->id);
}

void
log_on_thread_delete(struct discord *client,
                     const struct discord_channel *event)
{
    log_info("Thread %s (%" PRIu64 ") deleted", event->name, event->id);
}

void
on_channel_create(struct discord *client, const struct discord_message *event)
{
    if (event->author->bot) return;

    struct discord_create_guild_channel params = {
        .name = event->content,
        .reason = "Shiny new channel",
    };
    discord_create_guild_channel(client, event->guild_id, &params, NULL);
}

void
on_channel_rename_this(struct discord *client,
                       const struct discord_message *event)
{
    if (event->author->bot) return;

    struct discord_modify_channel params = {
        .name = event->content,
        .reason = "Clicks better",
    };
    discord_modify_channel(client, event->channel_id, &params, NULL);
}

void
on_channel_delete_this(struct discord *client,
                       const struct discord_message *event)
{
    if (event->author->bot) return;

    struct discord_delete_channel params = { .reason = "Stinky channel" };
    discord_delete_channel(client, event->channel_id, &params, NULL);
}

void
done_get_channel_invites(struct discord *client,
                         struct discord_response *resp,
                         const struct discord_invites *invites)
{
    if (!invites->size) {
        log_info("No invites found!");
        return;
    }

    const struct discord_message *event = resp->keep;
    char text[DISCORD_MAX_MESSAGE_LEN];
    snprintf(text, sizeof(text), "%d invite links created.", invites->size);

    struct discord_create_message params = { .content = text };
    discord_create_message(client, event->channel_id, &params, NULL);
}

void
fail_get_channel_invites(struct discord *client, struct discord_response *resp)
{
    log_info("Couldn't fetch invites: %s",
             discord_strerror(resp->code, client));
}

void
on_channel_get_invites(struct discord *client,
                       const struct discord_message *event)
{
    if (event->author->bot) return;

    struct discord_ret_invites ret = {
        .done = &done_get_channel_invites,
        .fail = &fail_get_channel_invites,
        .keep = event,
    };
    discord_get_channel_invites(client, event->channel_id, &ret);
}

void
done_create_channel_invite(struct discord *client,
                           struct discord_response *resp,
                           const struct discord_invite *invite)
{
    const struct discord_message *event = resp->keep;
    char text[256];

    snprintf(text, sizeof(text), "https://discord.gg/%s", invite->code);

    struct discord_create_message params = { .content = text };
    discord_create_message(client, event->channel_id, &params, NULL);
}

void
fail_create_channel_invite(struct discord *client,
                           struct discord_response *resp)
{
    const struct discord_message *event = resp->keep;

    struct discord_create_message params = {
        .content = "Couldn't create invite",
    };
    discord_create_message(client, event->channel_id, &params, NULL);
}

void
on_channel_create_invite(struct discord *client,
                         const struct discord_message *event)
{
    if (event->author->bot) return;

    struct discord_ret_invite ret = {
        .done = &done_create_channel_invite,
        .fail = &fail_create_channel_invite,
        .keep = event,
    };
    discord_create_channel_invite(client, event->channel_id, NULL, &ret);
}

void
done_start_thread(struct discord *client,
                  struct discord_response *resp,
                  const struct discord_channel *thread)
{
    const struct discord_message *event = resp->keep;
    char text[1024];

    snprintf(text, sizeof(text), "Created thread <#%" PRIu64 ">", thread->id);

    struct discord_create_message params = { .content = text };
    discord_create_message(client, event->channel_id, &params, NULL);
}

void
fail_start_thread(struct discord *client, struct discord_response *resp)
{
    const struct discord_message *event = resp->keep;
    char text[1024];

    snprintf(text, sizeof(text), "Couldn't create thread: %s",
             discord_strerror(resp->code, client));

    struct discord_create_message params = { .content = text };
    discord_create_message(client, event->channel_id, &params, NULL);
}

void
on_channel_start_thread(struct discord *client,
                        const struct discord_message *event)
{
    if (event->author->bot) return;

    struct discord_ret_channel ret = {
        .done = &done_start_thread,
        .fail = &fail_start_thread,
        .keep = event,
    };

    if (event->message_reference) {
        struct discord_start_thread_with_message params = {
            .name = "new_thread",
        };
        discord_start_thread_with_message(client, event->channel_id,
                                          event->message_reference->message_id,
                                          &params, &ret);
    }
    else {
        struct discord_start_thread_without_message params = {
            .name = "new_thread",
            .type = DISCORD_CHANNEL_GUILD_PUBLIC_THREAD,
        };
        discord_start_thread_without_message(client, event->channel_id,
                                             &params, &ret);
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
