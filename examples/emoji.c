#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h> /* PRIu64, SCNu64 */
#include <assert.h>

#include "discord.h"
#include "log.h"

void
print_usage(void)
{
    printf(
        "\n\n This bot demonstrates how easy it is to create/delete emojis\n"
        "1. Type 'emoji.list' to get a list of server emojis (in no "
        "particular order)\n"
        "2. Type 'emoji.get <emoji_id>' to get the selected emoji\n"
        "\nTYPE ANY KEY TO START BOT\n");
}

void
on_ready(struct discord *client, const struct discord_ready *event)
{
    log_info("Emoji-Bot succesfully connected to Discord as %s#%s!",
             event->user->username, event->user->discriminator);
}

void
done_list_guild_emojis(struct discord *client,
                       struct discord_response *resp,
                       const struct discord_emojis *emojis)
{
    const struct discord_message *event = resp->keep;
    char text[2000] = "";

    if (!emojis->size) {
        log_info("No emojis in guild");
        return;
    }

    char *cur = text;
    char *end = &text[sizeof(text) - 1];
    char *prev;

    for (int i = 0; i < emojis->size; ++i) {
        prev = cur;

        cur += snprintf(cur, end - cur, "<%s:%s:%" PRIu64 ">(%" PRIu64 ")\n",
                        emojis->array[i].animated ? "a" : "",
                        emojis->array[i].name, emojis->array[i].id,
                        emojis->array[i].id);

        if (cur >= end) { // to make sure no emoji is skipped
            *prev = '\0'; // end string before truncation

            // reset for retry
            cur = text;
            --i;

            struct discord_create_message params = { .content = text };
            discord_create_message(client, event->channel_id, &params, NULL);

            continue;
        }
    }

    struct discord_create_message params = { .content = text };
    discord_create_message(client, event->channel_id, &params, NULL);
}

void
fail_list_guild_emojis(struct discord *client, struct discord_response *resp)
{
    const struct discord_message *event = resp->keep;
    char text[256];

    snprintf(text, sizeof(text), "Couldn't fetch guild emojis: %s",
             discord_strerror(resp->code, client));

    struct discord_create_message params = { .content = text };
    discord_create_message(client, event->channel_id, &params, NULL);
}

void
on_list_guild_emojis(struct discord *client,
                     const struct discord_message *event)
{
    if (event->author->bot) return;

    struct discord_ret_emojis ret = {
        .done = &done_list_guild_emojis,
        .fail = &fail_list_guild_emojis,
        .keep = event,
    };
    discord_list_guild_emojis(client, event->guild_id, &ret);
}

void
done_get_guild_emoji(struct discord *client,
                     struct discord_response *resp,
                     const struct discord_emoji *emoji)
{
    const struct discord_message *event = resp->keep;
    char text[DISCORD_MAX_MESSAGE_LEN];

    snprintf(text, sizeof(text), "Here you go: <%s:%s:%" PRIu64 ">",
             emoji->animated ? "a" : "", emoji->name, emoji->id);

    struct discord_create_message params = { .content = text };
    discord_create_message(client, event->channel_id, &params, NULL);
}

void
fail_get_guild_emoji(struct discord *client, struct discord_response *resp)
{
    const struct discord_message *event = resp->keep;
    char text[256];

    snprintf(text, sizeof(text), "Unknown emoji: %s",
             discord_strerror(resp->code, client));

    struct discord_create_message params = { .content = text };
    discord_create_message(client, event->channel_id, &params, NULL);
}

void
on_get_guild_emoji(struct discord *client, const struct discord_message *event)
{
    if (event->author->bot) return;

    u64snowflake emoji_id = 0ULL;

    sscanf(event->content, "%" SCNu64, &emoji_id);
    if (!emoji_id) return;

    struct discord_ret_emoji ret = {
        .done = &done_get_guild_emoji,
        .fail = &fail_get_guild_emoji,
        .keep = event,
    };
    discord_get_guild_emoji(client, event->guild_id, emoji_id, &ret);
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

    discord_set_prefix(client, "emoji.");
    discord_set_on_command(client, "list", &on_list_guild_emojis);
    discord_set_on_command(client, "get", &on_get_guild_emoji);

    print_usage();
    fgetc(stdin); // wait for input

    discord_run(client);

    discord_cleanup(client);
    ccord_global_cleanup();
}
