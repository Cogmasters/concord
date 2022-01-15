#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h> /* PRIu64, SCNu64 */
#include <assert.h>

#include "discord.h"

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
on_ready(struct discord *client)
{
    const struct discord_user *bot = discord_get_self(client);

    log_info("Emoji-Bot succesfully connected to Discord as %s#%s!",
             bot->username, bot->discriminator);
}

void
done_list_guild_emojis(struct discord *client,
                       void *data,
                       const struct discord_emoji **emojis)
{
    u64_snowflake_t *channel_id = data;
    char text[DISCORD_MAX_MESSAGE_LEN];

    if (!emojis) {
        log_info("No emojis in guild");
        return;
    }

    char *cur = text;
    char *end = &text[sizeof(text) - 1];
    char *prev;

    for (size_t i = 0; emojis[i]; ++i) {
        prev = cur;

        cur += snprintf(cur, end - cur, "<%s:%s:%" PRIu64 ">(%" PRIu64 ")\n",
                        emojis[i]->animated ? "a" : "", emojis[i]->name,
                        emojis[i]->id, emojis[i]->id);

        if (cur >= end) { // to make sure no emoji is skipped
            *prev = '\0'; // end string before truncation

            // reset for retry
            cur = text;
            --i;

            struct discord_create_message params = { .content = text };
            discord_create_message(client, *channel_id, &params, NULL);

            continue;
        }
    }

    struct discord_create_message params = { .content = text };
    discord_create_message(client, *channel_id, &params, NULL);
}

void
fail_list_guild_emojis(struct discord *client, CCORDcode code, void *data)
{
    u64_snowflake_t *channel_id = data;
    char text[256];

    snprintf(text, sizeof(text), "Couldn't fetch guild emojis: %s",
             discord_strerror(code, client));

    struct discord_create_message params = { .content = text };
    discord_create_message(client, *channel_id, &params, NULL);
}

void
on_list_guild_emojis(struct discord *client, const struct discord_message *msg)
{
    if (msg->author->bot) return;

    u64_snowflake_t *channel_id = malloc(sizeof(u64_snowflake_t));
    *channel_id = msg->channel_id;

    struct discord_ret_emojis ret = {
        .done = &done_list_guild_emojis,
        .fail = &fail_list_guild_emojis,
        .data = channel_id,
        .done_cleanup = &free,
        .fail_cleanup = &free,
    };
    discord_list_guild_emojis(client, msg->guild_id, &ret);
}

void
done_get_guild_emoji(struct discord *client,
                     void *data,
                     const struct discord_emoji *emoji)
{
    u64_snowflake_t *channel_id = data;
    char text[DISCORD_MAX_MESSAGE_LEN];

    snprintf(text, sizeof(text), "Here you go: <%s:%s:%" PRIu64 ">",
             emoji->animated ? "a" : "", emoji->name, emoji->id);

    struct discord_create_message params = { .content = text };
    discord_create_message(client, *channel_id, &params, NULL);
}

void
fail_get_guild_emoji(struct discord *client, CCORDcode code, void *data)
{
    u64_snowflake_t *channel_id = data;
    char text[256];

    snprintf(text, sizeof(text), "Unknown emoji: %s",
             discord_strerror(code, client));

    struct discord_create_message params = { .content = text };
    discord_create_message(client, *channel_id, &params, NULL);
}

void
on_get_guild_emoji(struct discord *client, const struct discord_message *msg)
{
    if (msg->author->bot) return;

    u64_snowflake_t emoji_id = 0ULL;

    sscanf(msg->content, "%" SCNu64, &emoji_id);
    if (!emoji_id) return;

    u64_snowflake_t *channel_id = malloc(sizeof(u64_snowflake_t));
    *channel_id = msg->channel_id;

    struct discord_ret_emoji ret = {
        .done = &done_get_guild_emoji,
        .fail = &fail_get_guild_emoji,
        .data = channel_id,
        .done_cleanup = &free,
        .fail_cleanup = &free,
    };
    discord_get_guild_emoji(client, msg->guild_id, emoji_id, &ret);
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
