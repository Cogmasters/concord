# Slash commands

Slash commands are just a type of application command. You set the `name`, the `description`, and the [`options`](https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-object-application-command-interaction-data-option-structure); the `name` and `description` allow users to rapidly identificate your bot's slash command among many others (since it's expected to a lot of other bots have the same slash command names as yours), and the [`options`](https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-object-application-command-interaction-data-option-structure) field let the user fill information about the requested command params to send to your bot.

## Creating a slash command (Globally)

There are currently two ways of creating/updating a slash command, globally and guild specific (per guild), globals are for all the guilds that your bot is in, and guild specific already explains it by the name. In this topic, we will be creating global slash commands, see the next topic for guild specific slash commands.

To create the slash commands we will be using the [`discord_create_global_application_command()`](https://cogmasters.github.io/concord/group__DiscordAPIInteractionsApplicationCommand.html#ga348051bd3bd310b9abb34526ae346f8b) function, which takes only `4` parameters, see the example below of creating a slash command called `concordy` with a description of `Concord is really amazing.`:

*Re-creating a global slash command will make its information change to the new one.*

```c
struct discord_create_global_application_command params = {
    .name = "concordy",
    .description = "Concord is really amazing."
};

discord_create_global_application_command(client, event->application->id, &params, NULL);
```

Done! Sadly, global application commands may take hours to set up, so you may need to wait, till it appears for you to use.

*That is a resumed guide, you may want to see more fields of the `discord_create_global_application_command` struct, for that, you can click [here](https://cogmasters.github.io/concord/structdiscord__create__guild__application__command.html)*

## Creating a slash command (Guild specific)

Guild specific slash commands are slash commands where that will only appear in the guild it wants to appear. It's good for testing since it takes short time for it to appear and change its information, and you can rapidly test things out with it before making global slash commands.

Making a guild specific slash command, it's very simple and similar to creating a global one, see the example below:

```c
#define GUILD_ID 1234567898765431

struct discord_create_guild_application_command params = {
    .name = "concordy",
    .description = "Concord is really amazing."
};

discord_create_guild_application_command(client, event->application->id, GUILD_ID, &params, NULL);
```

To see more fields on the `discord_create_guild_application_command` struct, you can click [here](https://cogmasters.github.io/concord/structdiscord__create__guild__application__command.html).

## Responding to slash commands

After we created a slash command, we will need to now respond to those. Concord provides functions that allow you to rapidly respond to them.

*It doesn't matter if you created a slash command using the global or guild specific topic, you will end up with the same functions to respond to them.*

```c
void on_interaction(struct discord *client, const struct discord_interaction *interaction) {
    if (interaction->type != DISCORD_INTERACTION_APPLICATION_COMMAND) return;

    if (strcmp(interaction->data->name, "concordy") == 0) {
        struct discord_interaction_response params = {
            .type = DISCORD_INTERACTION_CHANNEL_MESSAGE_WITH_SOURCE,
            .data = &(struct discord_interaction_callback_data) {
                        .content = "Concord is the best!" // Here, is the content of the message
                        .flags = DISCORD_MESSAGE_EPHEMERAL // This makes the message only be visible to who executed the slash command
                    }
        };
        discord_create_interaction_response(client, interaction->id, interaction->token, &params, NULL);
    }
}
```

Yes, that's it, it will respond to the slash command `concordy` with the message `Concord is the best`, being only visible to who executed the slash command.

## Deleting a slash command

If you regretted creating a slash command, this topic is for you. In case you want to delete either a global or guild specific (the functions for each one are different) slash command, you can use the function `discord_delete_global_application_command`/`discord_delete_guild_application_command` respectively, see the example below:


### Global

```c
discord_delete_global_application_command(client, interaction->id, bot->id, NULL);
```

### Guild specific

```c
#define GUILD_ID 1234567898765431

discord_delete_guild_application_command(client, interaction->id, GUILD_ID, bot->id, NULL);
```

If it's global, it may take a while to disappear, but if it's guild specific, it will almost disappear instantly.

## Code example

Here is the mix of all the topics above into a single code example.

You will have `.createslash` that will create a guild specific slash command. The slash command will respond to the slash command called `concordy`.

```c
#include <string.h>
#include <stdlib.h>

#include <concord/discord.h>
#include <concord/logmod.h>

void on_ready(struct discord *client, const struct discord_ready *bot) {
    (void) client;
    logmod_log(INFO, NULL, "Logged in as %s!", bot->user->username);
}

void on_createslash(struct discord *client, const struct discord_message *msg) {
    const struct discord_user *bot = discord_get_self(client);

    struct discord_create_guild_application_command params = {
        .name = "concordy",
        .description = "Concord is really amazing."
    };

    discord_create_guild_application_command(client, bot->id, msg->guild_id, &params, NULL);

    struct discord_create_message paramsMessage = {
        .content = "Done, slash command created."
    };

    discord_create_message(client, msg->channel_id, &paramsMessage, NULL);
}

void on_interaction(struct discord *client, const struct discord_interaction *interaction) {
    if (interaction->type != DISCORD_INTERACTION_APPLICATION_COMMAND) return;

    if (strcmp(interaction->data->name, "concordy") == 0) {
        struct discord_interaction_response params = {
            .type = DISCORD_INTERACTION_CHANNEL_MESSAGE_WITH_SOURCE,
            .data = &(struct discord_interaction_callback_data) {
                        .content = "Concord is the best!",
                        .flags = DISCORD_MESSAGE_EPHEMERAL
                    }
        };
        discord_create_interaction_response(client, interaction->id, interaction->token, &params, NULL);
    }
}

int main(void) {
    struct discord *client = discord_config_init("config.json");

    discord_add_intents(client, DISCORD_GATEWAY_MESSAGE_CONTENT);

    discord_set_on_ready(client, &on_ready);
    discord_set_on_interaction_create(client, &on_interaction);

    discord_set_on_command(client, ".createslash", &on_createslash);

    discord_run(client);
}
```
