[discord-invite]: https://discord.gg/Y7Xa6MA82v
[portability]: PORTABILITY.md
[config_json]: guides/config.json_directives.md

# Concord - A Discord API wrapper library made in C

## About

Concord is an asynchronous C (C99) Discord API library with minimal external dependencies and a low-abstraction translation of the Discord official API to C code.

It is currently maintained by a team of passionate C developers, and is used by a [community][discord-invite] that is always willing to help!

```c
#include <string.h>
#include <concord/discord.h>

#define BOT_TOKEN "YOUR-BOT-TOKEN-HERE"

void on_ready(struct discord *client, const struct discord_ready *event) {
    struct discord_create_guild_application_command params = {
        .name = "ping",
        .description = "Ping command!"
    };
    discord_create_guild_application_command(client, event->application->id,
                                             GUILD_ID, &params, NULL);
}

void on_interaction(struct discord *client, const struct discord_interaction *event) {
    if (event->type != DISCORD_INTERACTION_APPLICATION_COMMAND)
        return; /* return if interaction isn't a slash command */

    if (strcmp(event->data->name, "ping") == 0) {
          struct discord_interaction_response params = {
                .type = DISCORD_INTERACTION_CHANNEL_MESSAGE_WITH_SOURCE,
                .data = &(struct discord_interaction_callback_data){
                      .content = "pong"
                }
          };
          discord_create_interaction_response(client, event->id,
                                              event->token, &params, NULL);
    }
}

int main(void) {
    struct discord *client = discord_init(BOT_TOKEN);
    discord_set_on_ready(client, &on_ready);
    discord_set_on_interaction_create(client, &on_interaction);
    discord_run(client);
}
```

## Features
- Discord v10 support
- Fully asynchronous
- [Portability][portability]
- Timers
- Caching

## Getting started
<!-- List guides to help set up the first bot, concord's workflow, and some of its quirks -->
- [Configuring your bot][config_json]

## Guides
<!-- General purpose guides, how to use embeds, interactions, etc -->

## Other topics
<!-- Links to other useful C resources, such as good debugging practices >
