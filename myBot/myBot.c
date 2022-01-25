#include <string.h> // strncmp()
#include <stdio.h>
#include <stdlib.h>
#include "discord.h"

void
on_message(struct discord *client, const struct discord_message *msg)
{
    if (msg->author->bot) return; // early return if author is a bot

    if (0 == strcmp(msg->content, "!ping")) {
        char ping[64];

        snprintf(ping, sizeof(ping), "Pong, `%d`ms", discord_get_ping(client));

        struct discord_create_message params = { .content = ping };
        discord_create_message(client, msg->channel_id, &params, NULL);
    }
    if (0 == strncmp("!say ", msg->content, 5)) {
        char *content = msg->content + 5;

        struct discord_create_message params = { .content = content };
        discord_create_message(client, msg->channel_id, &params, NULL);
    }
}

void
on_ready(struct discord *client)
{
    const struct discord_user *bot = discord_get_self(client);

    log_info("Logged in as %s!", bot->username);
}

int
main(void)
{
    struct discord *client = discord_config_init("../config.json");

    discord_set_on_ready(client, &on_ready);
    discord_set_on_message_create(client, &on_message);
    discord_run(client);

    discord_cleanup(client);

    return EXIT_SUCCESS;
}
