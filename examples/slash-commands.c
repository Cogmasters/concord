#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <inttypes.h> /* SCNu64, PRIu64 */

#include "discord.h"
#include "log.h"

u64snowflake g_app_id;

void
print_usage(void)
{
    printf("\n\nThis bot demonstrates how easy it is to create, and react to "
           "application commands\n"
           "1. Type '!slash_create' to create the application command\n"
           "2. Type '/' in the same channel and select the newly created "
           "command\n"
           "\nTYPE ANY KEY TO START BOT\n");
}

void
on_ready(struct discord *client, const struct discord_ready *event)
{
    log_info("Slash-Commands-Bot succesfully connected to Discord as %s#%s!",
             event->user->username, event->user->discriminator);

    g_app_id = event->application->id;
}

void
on_slash_command_create(struct discord *client,
                        const struct discord_message *event)
{
    if (event->author->bot) return;

    struct discord_application_command_option_choice gender_choices[] = {
        {
            .name = "male",
            .value = "\"male\"",
        },
        {
            .name = "female",
            .value = "\"female\"",
        },
        {
            .name = "other",
            .value = "\"other\"",
        },
    };
    struct discord_application_command_option options[] = {
        {
            .type = DISCORD_APPLICATION_OPTION_STRING,
            .name = "nick",
            .description = "Your nick",
            .required = true,
        },
        {
            .type = DISCORD_APPLICATION_OPTION_INTEGER,
            .name = "pets",
            .description = "How many pets you got",
        },
        {
            .type = DISCORD_APPLICATION_OPTION_STRING,
            .name = "gender",
            .description = "Your gender",
            .choices =
                &(struct discord_application_command_option_choices){
                    .size = sizeof(gender_choices) / sizeof *gender_choices,
                    .array = gender_choices,
                },
        },
        {
            .type = DISCORD_APPLICATION_OPTION_CHANNEL,
            .name = "favorite",
            .description = "Favorite channel",
            .channel_types =
                &(struct integers){
                    .size = 1,
                    .array =
                        (int[]){
                            DISCORD_CHANNEL_GUILD_TEXT,
                        },
                },
        },
    };

    struct discord_create_guild_application_command params = {
        .name = "fill-form",
        .description = "A slash command example for form filling",
        .default_permission = true,
        .options =
            &(struct discord_application_command_options){
                .size = sizeof(options) / sizeof *options,
                .array = options,
            },
    };

    /* Create slash command */
    discord_create_guild_application_command(client, g_app_id, event->guild_id,
                                             &params, NULL);
}

void
on_interaction_create(struct discord *client,
                      const struct discord_interaction *event)
{
    /* We're only interested on slash commands */
    if (event->type != DISCORD_INTERACTION_APPLICATION_COMMAND) return;
    /* Return in case user input is missing for some reason */
    if (!event->data || !event->data->options) return;

    char *nick = "blank";
    int pets = 0;
    char *gender = "blank";
    u64snowflake channel_id = 0;

    for (int i = 0; i < event->data->options->size; ++i) {
        char *name = event->data->options->array[i].name;
        char *value = event->data->options->array[i].value;

        if (0 == strcmp(name, "nick"))
            nick = value;
        else if (0 == strcmp(name, "pets"))
            pets = strtol(value, NULL, 10);
        else if (0 == strcmp(name, "gender"))
            gender = value;
        else if (0 == strcmp(name, "favorite"))
            sscanf(value, "%" SCNu64, &channel_id);
    }

    char buf[DISCORD_MAX_MESSAGE_LEN] = "";
    snprintf(buf, sizeof(buf),
             "Fun-facts about <@%" PRIu64 ">!\n"
             "Nick: %s\n"
             "Pets: %d\n"
             "Gender: %s\n"
             "Favorite channel: <#%" PRIu64 ">\n",
             event->member->user->id, nick, pets, gender, channel_id);

    struct discord_interaction_response params = {
        .type = DISCORD_INTERACTION_CHANNEL_MESSAGE_WITH_SOURCE,
        .data = &(struct discord_interaction_callback_data){ .content = buf }
    };

    discord_create_interaction_response(client, event->id, event->token,
                                        &params, NULL);
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

    discord_set_on_command(client, "!slash_create", &on_slash_command_create);
    discord_set_on_ready(client, &on_ready);
    discord_set_on_interaction_create(client, &on_interaction_create);

    print_usage();
    fgetc(stdin); // wait for input

    discord_run(client);

    discord_cleanup(client);
    ccord_global_cleanup();
}
