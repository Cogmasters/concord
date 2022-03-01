#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h> /* PRIu64, SCNu64 */
#include <assert.h>

#include "discord.h"

void
print_usage(void)
{
    printf(
        "\n\nThis bot demonstrates how easy it is to have a"
        " message be pinned.\n"
        "1. Reply to a message with '!pin' or type '!pin <message_id> to pin "
        "it\n"
        "2. Reply to a message with '!unpin' or type '!unpin <message_id> to "
        "unpin it\n"
        "3. Type '!get_pins' to get a id list of pinned messages\n"
        "\nTYPE ANY KEY TO START BOT\n");
}

void
on_ready(struct discord *client)
{
    const struct discord_user *bot = discord_get_self(client);

    log_info("Pin-Bot succesfully connected to Discord as %s#%s!",
             bot->username, bot->discriminator);
}

void
on_pin(struct discord *client, const struct discord_message *msg)
{
    if (msg->author->bot) return;

    u64snowflake msg_id = 0;

    sscanf(msg->content, "%" SCNu64, &msg_id);

    if (!msg_id) {
        if (!msg->referenced_message) return;

        msg_id = msg->referenced_message->id;
    }

    discord_pin_message(client, msg->channel_id, msg_id, NULL);
}

void
on_unpin(struct discord *client, const struct discord_message *msg)
{
    if (msg->author->bot) return;

    u64snowflake msg_id = 0;

    sscanf(msg->content, "%" SCNu64, &msg_id);

    if (!msg_id) {
        if (!msg->referenced_message) return;

        msg_id = msg->referenced_message->id;
    }

    discord_unpin_message(client, msg->channel_id, msg_id, NULL);
}

struct context {
    u64snowflake channel_id;
    u64snowflake guild_id;
};

void
done_get_pins(struct discord *client,
              void *data,
              const struct discord_messages *msgs)
{
    struct context *cxt = data;
    char text[2000] = "No pins on channel";

    char *cur = text;
    char *end = &text[sizeof(text) - 1];

    for (int i = 0; i < msgs->size; ++i) {
        cur += snprintf(cur, end - cur,
                        "https://discord.com/channels/%" PRIu64 "/%" PRIu64
                        "/%" PRIu64 "\n",
                        cxt->guild_id, cxt->channel_id, msgs->array[i].id);

        if (cur >= end) break;
    }

    struct discord_create_message params = { .content = text };
    discord_create_message(client, cxt->channel_id, &params, NULL);
}

void
fail_get_pins(struct discord *client, CCORDcode code, void *data)
{
    struct context *cxt = data;
    char text[2000] = "";

    snprintf(text, sizeof(text),
             "Failed fetching pinned messages at <#%" PRIu64 ">",
             cxt->channel_id);

    struct discord_create_message params = { .content = text };
    discord_create_message(client, cxt->channel_id, &params, NULL);
}

void
on_get_pins(struct discord *client, const struct discord_message *msg)
{
    if (msg->author->bot) return;

    struct context *cxt = malloc(sizeof(struct context));
    cxt->channel_id = msg->channel_id;
    cxt->guild_id = msg->guild_id;

    struct discord_ret_messages ret = {
        .done = &done_get_pins,
        .fail = &fail_get_pins,
        .data = cxt,
        .cleanup = &free,
    };

    discord_get_pinned_messages(client, msg->channel_id, &ret);
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

    discord_set_on_ready(client, &on_ready);

    discord_set_prefix(client, "!");
    discord_set_on_command(client, "pin", &on_pin);
    discord_set_on_command(client, "unpin", &on_unpin);
    discord_set_on_command(client, "get_pins", &on_get_pins);

    print_usage();
    fgetc(stdin); // wait for input

    discord_run(client);

    discord_cleanup(client);
    ccord_global_cleanup();
}
