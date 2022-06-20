#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <limits.h>
#include <string.h>
#include <assert.h>

#include "discord.h"
#include "log.h"

void
print_usage(void)
{
    printf("\n\nThis bot demonstrates how easy it is to log"
           " for certain events.\n"
           "1. Type '!last_channel' to check the most recent channel created "
           "by you\n"
           "\tsee: "
           "https://discord.com/developers/docs/resources/"
           "audit-log#audit-log-entry-object-audit-log-events\n"
           "\nTYPE ANY KEY TO START BOT\n");
}

void
on_ready(struct discord *client, const struct discord_ready *event)
{
    log_info("Audit-Log-Bot succesfully connected to Discord as %s#%s!",
             event->user->username, event->user->discriminator);
}

void
log_on_guild_member_add(struct discord *client,
                        const struct discord_guild_member *event)
{
    log_info("%s#%s joined guild %" PRIu64, event->user->username,
             event->user->discriminator, event->guild_id);
}

void
log_on_guild_member_update(struct discord *client,
                           const struct discord_guild_member_update *event)
{
    char nick[128] = "";

    if (event->nick && *event->nick)
        snprintf(nick, sizeof(nick), " (%s)", event->nick);

    log_info("%s#%s%s updated (guild %" PRIu64 ")", event->user->username,
             event->user->discriminator, nick, event->guild_id);
}

void
log_on_guild_member_remove(struct discord *client,
                           const struct discord_guild_member_remove *event)
{
    log_info("%s#%s left guild %" PRIu64, event->user->username,
             event->user->discriminator, event->guild_id);
}

void
done(struct discord *client,
     struct discord_response *resp,
     const struct discord_audit_log *audit_log)
{
    const struct discord_message *event = resp->keep;

    if (!audit_log->audit_log_entries || !audit_log->audit_log_entries->size) {
        log_warn("No audit log entries found!");
        return;
    }

    struct discord_audit_log_entry *entry =
        &audit_log->audit_log_entries->array[0];

    char text[1028];
    snprintf(text, sizeof(text), "<@!%" PRIu64 "> has created <#%" PRIu64 ">!",
             entry->user_id, entry->target_id);

    struct discord_create_message params = { .content = text };
    discord_create_message(client, event->channel_id, &params, NULL);
}

void
fail(struct discord *client, struct discord_response *resp)
{
    (void)resp;

    log_error("Couldn't retrieve audit log: %s",
              discord_strerror(resp->code, client));
}

void
on_audit_channel_create(struct discord *client,
                        const struct discord_message *event)
{
    if (event->author->bot) return;

    struct discord_ret_audit_log ret = {
        .done = &done,
        .fail = &fail,
        .keep = event,
    };
    struct discord_get_guild_audit_log params = {
        .user_id = event->author->id,
        .action_type = DISCORD_AUDIT_LOG_CHANNEL_CREATE,
    };
    discord_get_guild_audit_log(client, event->guild_id, &params, &ret);
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

    discord_add_intents(client, 32767); // subscribe to all events

    discord_set_on_ready(client, &on_ready);
    discord_set_on_guild_member_add(client, &log_on_guild_member_add);
    discord_set_on_guild_member_update(client, &log_on_guild_member_update);
    discord_set_on_guild_member_remove(client, &log_on_guild_member_remove);

    discord_set_on_command(client, "!last_channel", &on_audit_channel_create);

    print_usage();
    fgetc(stdin); // wait for input

    discord_run(client);

    discord_cleanup(client);
    ccord_global_cleanup();
}
