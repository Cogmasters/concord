#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <inttypes.h> /* SCNu64, PRIu64 */

#include "discord.h"
#include "logmod.h"

u64snowflake g_app_id;

void
print_usage(void)
{
    printf("\n\nThis bot demonstrates how to make slash commands with "
           "autocomplete interactions\n"
           "1. Use the command /foobar to try it out\n"
           "\nTYPE ANY KEY TO START BOT\n");
}

void
on_ready(struct discord *client, const struct discord_ready *event)
{
    logmod_log(INFO, NULL,
               "Autocomplete-Bot succesfully connected to Discord as %s#%s!",
               event->user->username, event->user->discriminator);

    g_app_id = event->application->id;
}

void
foo(struct discord *client, const struct discord_interaction *event)
{
    // in this example, foo will provide the same options no matter what the
    // user has already typed
    //
    // normally, autocomplete choices should change depending on what the user
    // has typed, but we will show it with this way only for the sake of the
    // example
    struct discord_interaction_response params = {
        .type = DISCORD_INTERACTION_APPLICATION_COMMAND_AUTOCOMPLETE_RESULT,
        .data =
            &(struct discord_interaction_callback_data){
                .choices =
                    &(struct discord_application_command_option_choices){
                        .size = 3,
                        .array =
                            (struct discord_application_command_option_choice
                                 []){
                                {
                                    // name is what the user sees in the drop
                                    // down menu
                                    .name = "🍍 Pineapple",

                                    // value is what is actually received when
                                    // the command is sent
                                    //
                                    // if you are passing a string value, it
                                    // must be wrapped in quotes
                                    .value = "\"pineapple\"",
                                },
                                {
                                    .name = "🍎 Apple",
                                    .value = "\"apple\"",
                                },
                                {
                                    .name = "🖊️ Pen",
                                    .value = "\"pen\"",
                                },
                            },
                    },
            }
    };
    discord_create_interaction_response(client, event->id, event->token,
                                        &params, NULL);
}

void
bar(struct discord *client,
    const struct discord_interaction *event,
    char *value)
{
    // the bar option will append bar to whatever the user has already typed
    char *bar = malloc(strlen(value) + 3 + 1);
    strcpy(bar, value);
    strcat(bar, "bar");

    // the name does not have to be wrapped in quotes; the value does, however
    char *val = malloc(strlen(bar) + 2 + 1);
    strcpy(val, "\"");
    strcat(val, bar);
    strcat(val, "\"");

    struct discord_interaction_response params = {
        .type = DISCORD_INTERACTION_APPLICATION_COMMAND_AUTOCOMPLETE_RESULT,
        .data =
            &(struct discord_interaction_callback_data){
                .choices =
                    &(struct discord_application_command_option_choices){
                        .size = 1,
                        .array =
                            (struct discord_application_command_option_choice
                                 []){
                                {
                                    .name = bar,
                                    .value = val,
                                },
                            },
                    },
            }
    };
    discord_create_interaction_response(client, event->id, event->token,
                                        &params, NULL);
    free(bar);
    free(val);
}

void
on_interaction_create(struct discord *client,
                      const struct discord_interaction *event)
{
    if (event->type == DISCORD_INTERACTION_APPLICATION_COMMAND_AUTOCOMPLETE) {
        for (int i = 0; i < event->data->options->size; i++) {
            const char *name = event->data->options->array[i].name;
            char *value = event->data->options->array[i].value;
            bool focused = event->data->options->array[i].focused;

            // focused is true when the user is typing in that option
            if (focused == false) continue;

            // this code is split into two other functions to avoid
            // excessive amounts of indents
            if (strcmp(name, "foo") == 0) {
                foo(client, event);
            }
            else if (strcmp(name, "bar") == 0) {
                bar(client, event, value);
            }
        }
    }
    else if (event->type == DISCORD_INTERACTION_APPLICATION_COMMAND) {
        char *foo = "NULL";
        char *bar = "NULL";

        for (int i = 0; i < event->data->options->size; i++) {
            const char *name = event->data->options->array[i].name;
            char *value = event->data->options->array[i].value;

            if (strcmp(name, "foo") == 0)
                foo = value;
            else if (strcmp(name, "bar") == 0)
                bar = value;
        }

        int len = strlen(foo) + strlen(bar);

        char *msg = malloc(len + 1);
        strcpy(msg, foo);
        strcat(msg, bar);

        struct discord_interaction_response params = {
            .type = DISCORD_INTERACTION_CHANNEL_MESSAGE_WITH_SOURCE,
            .data =
                &(struct discord_interaction_callback_data){
                    .content = msg,
                }
        };

        discord_create_interaction_response(client, event->id, event->token,
                                            &params, NULL);

        free(msg);

        return;
    }
}

int
main(int argc, char *argv[])
{
    const char *config_file;
    if (argc > 1)
        config_file = argv[1];
    else
        config_file = "../config.json";

    struct discord *client = discord_from_json(config_file);
    assert(NULL != client && "Could not initialize client");

    discord_set_on_ready(client, &on_ready);
    discord_set_on_interaction_create(client, &on_interaction_create);

    print_usage();
    fgetc(stdin); // wait for input

    discord_run(client);

    discord_cleanup(client);
}
