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
        "\n\nThis bot demonstrates how easy it is to fetch/delete invites\n"
        "1. Type 'invite.get <invite_code>' to get a invite object from its "
        "particular code\n"
        "2. Type 'invite.delete <invite_code>' to delete a invite object by "
        "its particular code\n"
        "\nTYPE ANY KEY TO START BOT\n");
}

void
on_ready(struct discord *client, const struct discord_ready *event)
{
    log_info("Invite-Bot succesfully connected to Discord as %s#%s!",
             event->user->username, event->user->discriminator);
}

void
done(struct discord *client,
     struct discord_response *resp,
     const struct discord_invite *invite)
{
    const struct discord_message *event = resp->keep;
    char text[256];

    snprintf(text, sizeof(text), "Success: https://discord.gg/%s",
             invite->code);

    struct discord_create_message params = { .content = text };
    discord_create_message(client, event->channel_id, &params, NULL);
}

void
fail(struct discord *client, struct discord_response *resp)
{
    const struct discord_message *event = resp->keep;

    struct discord_create_message params = {
        .content = "Couldn't perform operation."
    };
    discord_create_message(client, event->channel_id, &params, NULL);
}

void
on_invite_get(struct discord *client, const struct discord_message *event)
{
    if (event->author->bot) return;

    struct discord_ret_invite ret = {
        .done = &done,
        .fail = &fail,
        .keep = event,
    };

    struct discord_get_invite params = {
        .with_counts = true,
        .with_expiration = true,
    };
    discord_get_invite(client, event->content, &params, &ret);
}

void
on_invite_delete(struct discord *client, const struct discord_message *event)
{
    if (event->author->bot) return;

    struct discord_ret_invite ret = {
        .done = &done,
        .fail = &fail,
        .keep = event,
    };
    struct discord_delete_invite params = { .reason = "Stale invite" };
    discord_delete_invite(client, event->content, &params, &ret);
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

    discord_set_prefix(client, "invite.");
    discord_set_on_command(client, "get", &on_invite_get);
    discord_set_on_command(client, "delete", &on_invite_delete);

    print_usage();
    fgetc(stdin); // wait for input

    discord_run(client);

    discord_cleanup(client);
    ccord_global_cleanup();
}
