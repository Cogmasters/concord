# Discord Slash Commands

Slash commands (prefixed with `/`) are Discord's integrated command system that provides a clean, intuitive interface for users to interact with your bot. Unlike traditional text commands that require users to remember specific prefixes, slash commands appear in Discord's UI with autocomplete suggestions, descriptions, and parameter options.

## Table of Contents

- [Overview](#overview)
- [Global vs. Guild Commands](#global-vs-guild-commands)
- [Creating Global Commands](#creating-global-commands)
- [Creating Guild-Specific Commands](#creating-guild-specific-commands)
- [Command Options and Parameters](#command-options-and-parameters)
- [Command Subcommands and Groups](#command-subcommands-and-groups)
- [Responding to Commands](#responding-to-commands)
- [Managing Existing Commands](#managing-existing-commands)
- [Deleting Commands](#deleting-commands)
- [Complete Example](#complete-example)

## Overview

Slash commands are application commands that help users discover and easily use your bot's features. They provide:

- **Discoverability**: Commands appear in Discord's UI with descriptions
- **Structure**: Define parameters with validation and autocomplete
- **Consistency**: Standard interface across all bots
- **Integration**: Native Discord support with lower latency

## Global vs. Guild Commands

Discord supports two types of slash commands:

- **Global Commands**: Available in all servers where your bot is installed
  - Take up to an hour to propagate after creation/updates
  - Best for production-ready features

- **Guild Commands**: Available in specific servers only
  - Update instantly (great for testing)
  - Can be used for server-specific features

## Creating Global Commands

To create a global command that will be available in all servers where your bot is present:

```c
void create_global_command(struct discord *client, const struct discord_ready *bot) {
    struct discord_create_global_application_command params = {
        .name = "ping",                   // Command name (must be lowercase)
        .description = "Check if the bot is responsive", // Description shown in UI
    };

    discord_create_global_application_command(client, bot->id, &params, NULL);
    
    // Note: Global commands can take up to an hour to appear across all guilds
}
```

## Creating Guild-Specific Commands

Guild commands are perfect for testing or server-specific features:

```c
void create_guild_command(struct discord *client, const struct discord_ready *bot) {
    u64snowflake guild_id = 1234567898765431; // Replace with your guild's ID
    
    struct discord_create_guild_application_command params = {
        .name = "test",                  // Command name (lowercase)
        .description = "Test command for development", // Description
    };

    discord_create_guild_application_command(client, bot->id, guild_id, &params, NULL);
    
    // Guild commands appear immediately!
}
```

## Command Options and Parameters

Slash commands can include parameters (called "options") for users to provide input:

```c
struct discord_create_global_application_command params = {
    .name = "echo",
    .description = "Repeat a message back to you",
    .options = &(struct discord_application_command_options){
        .size = 2,
        .array = (struct discord_application_command_option[]) {
            {
                .type = DISCORD_APPLICATION_OPTION_STRING,
                .name = "message",
                .description = "The message to repeat",
                .required = true
            },
            {
                .type = DISCORD_APPLICATION_OPTION_BOOLEAN,
                .name = "ephemeral",
                .description = "Whether to show the message only to you",
                .required = false
            }
        }
    }
};
```

Available option types:

- `DISCORD_APPLICATION_OPTION_STRING` - Text input
- `DISCORD_APPLICATION_OPTION_INTEGER` - Whole numbers
- `DISCORD_APPLICATION_OPTION_BOOLEAN` - True/false
- `DISCORD_APPLICATION_OPTION_USER` - Discord user
- `DISCORD_APPLICATION_OPTION_CHANNEL` - Discord channel
- `DISCORD_APPLICATION_OPTION_ROLE` - Discord role
- `DISCORD_APPLICATION_OPTION_MENTIONABLE` - User or role
- `DISCORD_APPLICATION_OPTION_NUMBER` - Decimal numbers
- `DISCORD_APPLICATION_OPTION_ATTACHMENT` - File uploads

## Command Subcommands and Groups

For more complex bots, you can organize commands into subcommands and groups:

```c
struct discord_create_global_application_command params = {
    .name = "moderation",
    .description = "Moderation commands",
    .options = &(struct discord_application_command_options){
        .size = 1,
        .array = (struct discord_application_command_option[]) {
            {
                .type = DISCORD_APPLICATION_OPTION_SUB_COMMAND_GROUP,
                .name = "user",
                .description = "User moderation commands",
                .options = &(struct discord_application_command_options){
                    .size = 1,
                    .array = (struct discord_application_command_option[]) {
                        {
                            .type = DISCORD_APPLICATION_OPTION_SUB_COMMAND,
                            .name = "timeout",
                            .description = "Timeout a user",
                            .options = &(struct discord_application_command_options){
                                .size = 2,
                                .array = (struct discord_application_command_option[]) {
                                    {
                                        .type = DISCORD_APPLICATION_OPTION_USER,
                                        .name = "user",
                                        .description = "The user to timeout",
                                        .required = true
                                    },
                                    {
                                        .type = DISCORD_APPLICATION_OPTION_INTEGER,
                                        .name = "minutes",
                                        .description = "Duration in minutes",
                                        .required = true
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
};
```

## Responding to Commands

When a user uses your slash command, Discord sends an interaction event:

```c
void on_interaction(struct discord *client, const struct discord_interaction *interaction) {
    // Only handle application commands (slash commands)
    if (interaction->type != DISCORD_INTERACTION_APPLICATION_COMMAND) return;
    
    // Check which command was used
    if (strcmp(interaction->data->name, "ping") == 0) {
        struct discord_interaction_response params = {
            .type = DISCORD_INTERACTION_CHANNEL_MESSAGE_WITH_SOURCE,
            .data = &(struct discord_interaction_callback_data) {
                .content = "Pong! Bot is online.",
                // Make response visible only to the command user
                .flags = DISCORD_MESSAGE_EPHEMERAL
            }
        };
        
        discord_create_interaction_response(client, 
                                           interaction->id, 
                                           interaction->token, 
                                           &params, NULL);
    }
    else if (strcmp(interaction->data->name, "echo") == 0) {
        // Example of accessing command options
        const char* message = NULL;
        bool ephemeral = false;
        
        // Find and extract the "message" option
        for (int i = 0; i < interaction->data->options->size; i++) {
            struct discord_application_command_interaction_data_option *option = 
                &interaction->data->options->array[i];
                
            if (strcmp(option->name, "message") == 0) {
                message = option->value->string;
            }
            else if (strcmp(option->name, "ephemeral") == 0) {
                ephemeral = option->value->boolean;
            }
        }
        
        struct discord_interaction_response params = {
            .type = DISCORD_INTERACTION_CHANNEL_MESSAGE_WITH_SOURCE,
            .data = &(struct discord_interaction_callback_data) {
                .content = message ? message : "No message provided",
                .flags = ephemeral ? DISCORD_MESSAGE_EPHEMERAL : 0
            }
        };
        
        discord_create_interaction_response(client, 
                                           interaction->id, 
                                           interaction->token, 
                                           &params, NULL);
    }
}
```

## Managing Existing Commands

You can retrieve existing commands to check what's currently registered:

```c
void list_global_commands(struct discord *client, const struct discord_ready *bot) {
    discord_get_global_application_commands(client, bot->id, NULL,
        &(struct discord_ret_application_commands){
            .done = print_commands_cb
        });
}

void print_commands_cb(struct discord *client, 
                      struct discord_application_commands *commands) {
    (void)client;
    
    logmod_log(INFO, NULL, "Found %d global commands:", commands->size);
    
    for (int i = 0; i < commands->size; i++) {
        struct discord_application_command *cmd = &commands->array[i];
        logmod_log(INFO, NULL, "%d. %s (%s): %s", 
                  i+1, cmd->name, cmd->id, cmd->description);
    }
}
```

For guild commands:

```c
void list_guild_commands(struct discord *client, const struct discord_ready *bot) {
    u64snowflake guild_id = 1234567898765431; // Replace with guild ID
    
    discord_get_guild_application_commands(client, bot->id, guild_id, NULL,
        &(struct discord_ret_application_commands){
            .done = print_commands_cb
        });
}
```

## Deleting Commands

When you need to remove a command:

```c
void delete_global_command(struct discord *client, const struct discord_ready *bot) {
    u64snowflake command_id = 1234567898765431; // Replace with command ID
    
    discord_delete_global_application_command(client, bot->id, command_id, NULL);
    // Note: Changes to global commands can take up to an hour to propagate
}

void delete_guild_command(struct discord *client, const struct discord_ready *bot) {
    u64snowflake guild_id = 1234567898765431;   // Replace with guild ID
    u64snowflake command_id = 9876543212345678; // Replace with command ID
    
    discord_delete_guild_application_command(client, bot->id, guild_id, command_id, NULL);
    // Guild command changes apply immediately
}
```

## Complete Example

Here's a complete bot example that demonstrates slash commands:

```c
#include <string.h>
#include <stdlib.h>

#include <concord/discord.h>
#include <concord/logmod.h>

void on_ready(struct discord *client, const struct discord_ready *bot) {
    logmod_log(INFO, NULL, "Logged in as %s!", bot->user->username);
    
    // Create a guild command for testing
    u64snowflake test_guild_id = 1234567898765431; // Replace with your guild ID
    
    struct discord_create_guild_application_command params = {
        .name = "echo",
        .description = "Echo a message back to you",
        .options = &(struct discord_application_command_options){
            .size = 2,
            .array = (struct discord_application_command_option[]) {
                {
                    .type = DISCORD_APPLICATION_OPTION_STRING,
                    .name = "message",
                    .description = "The message to repeat",
                    .required = true
                },
                {
                    .type = DISCORD_APPLICATION_OPTION_BOOLEAN,
                    .name = "ephemeral",
                    .description = "Whether to show the message only to you",
                    .required = false
                }
            }
        }
    };
    
    discord_create_guild_application_command(client, bot->id, test_guild_id, &params, NULL);
    logmod_log(INFO, NULL, "Created /echo command in test guild");
}

void on_interaction(struct discord *client, const struct discord_interaction *interaction) {
    // Only handle application commands
    if (interaction->type != DISCORD_INTERACTION_APPLICATION_COMMAND) return;
    
    if (strcmp(interaction->data->name, "echo") == 0) {
        // Extract options
        const char* message = NULL;
        bool ephemeral = false;
        
        for (int i = 0; i < interaction->data->options->size; i++) {
            struct discord_application_command_interaction_data_option *option = 
                &interaction->data->options->array[i];
                
            if (strcmp(option->name, "message") == 0) {
                message = option->value->string;
            }
            else if (strcmp(option->name, "ephemeral") == 0) {
                ephemeral = option->value->boolean;
            }
        }
        
        // Create response
        struct discord_interaction_response response = {
            .type = DISCORD_INTERACTION_CHANNEL_MESSAGE_WITH_SOURCE,
            .data = &(struct discord_interaction_callback_data) {
                .content = message ? message : "No message provided",
                .flags = ephemeral ? DISCORD_MESSAGE_EPHEMERAL : 0
            }
        };
        
        discord_create_interaction_response(client, 
                                          interaction->id, 
                                          interaction->token, 
                                          &response, NULL);
    }
}

int main(void) {
    struct discord *client = discord_from_json("config.json");
    
    // Register event handlers
    discord_set_on_ready(client, &on_ready);
    discord_set_on_interaction_create(client, &on_interaction);
    
    // Start the bot
    discord_run(client);
    discord_cleanup(client);
    return 0;
}
```

With this example, you've learned how to:
- Create slash commands (both global and guild-specific)
- Define command options for user input
- Respond to command interactions
- Access parameter values from commands

Remember that global commands can take up to an hour to propagate, so use guild commands for testing and development.
