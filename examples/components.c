#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h> /* PRIu64 */
#include <assert.h>

#include "discord.h"
#include "logmod.h"

void
print_usage(void)
{
    printf(
        "\n\nThis bot demonstrates how to load message components"
        " with three different methods.\n"
        "1 - Dynamic-approach (type !dynamic): Load the components from "
        "a JSON string.\n"
        "2 - Static-approach (type !static): A clean initialization approach "
        "using the combination of designated initialization and compound "
        "literals.\n"
        "\nTYPE ANY KEY TO START BOT\n");
}

static const char JSON[] =
    "[\n"
    "    {\n"
    "        \"type\": 1,\n"
    "        \"components\": [\n"
    "            {\n"
    "                \"type\": 3,\n"
    "                \"custom_id\": \"class_select_1\",\n"
    "                \"options\":[\n"
    "                    {\n"
    "                        \"label\": \"Rogue\",\n"
    "                        \"value\": \"rogue\",\n"
    "                        \"description\": \"Sneak n stab\",\n"
    "                        \"emoji\": {\n"
    "                            \"name\": \"rogue\",\n"
    "                            \"id\": \"625891304148303894\"\n"
    "                        }\n"
    "                    },\n"
    "                    {\n"
    "                        \"label\": \"Mage\",\n"
    "                        \"value\": \"mage\",\n"
    "                        \"description\": \"Turn 'em into a sheep\",\n"
    "                        \"emoji\": {\n"
    "                            \"name\": \"mage\",\n"
    "                            \"id\": \"625891304081063986\"\n"
    "                        }\n"
    "                    },\n"
    "                    {\n"
    "                        \"label\": \"Priest\",\n"
    "                        \"value\": \"priest\",\n"
    "                        \"description\": \"You get heals when I'm done "
    "doing damage\",\n"
    "                        \"emoji\": {\n"
    "                            \"name\": \"priest\",\n"
    "                            \"id\": \"625891303795982337\"\n"
    "                        }\n"
    "                    }\n"
    "                ],\n"
    "                \"placeholder\": \"Choose a class\",\n"
    "                \"min_values\": 1,\n"
    "                \"max_values\": 3\n"
    "            }\n"
    "        ]\n"
    "    }\n"
    "]\n";

void
on_ready(struct discord *client, const struct discord_ready *event)
{
    logmod_log(INFO, NULL,
               "Components-Bot succesfully connected to Discord as %s#%s!",
               event->user->username, event->user->discriminator);
}

void
on_dynamic(struct discord *client, const struct discord_message *event)
{
    if (event->author->bot) return;

    struct discord_component *components = NULL;
    discord_component_from_json(JSON, sizeof(JSON), &components);

    struct discord_create_message params = {
        .content = "Mason is looking for new arena partners. What classes do "
                   "you play?",
        .components = components
    };
    discord_create_message(client, event->channel_id, &params, NULL);

    /* must free 'components' afterwards */
    discord_free(components);
}

void
on_static(struct discord *client, const struct discord_message *event)
{
    if (event->author->bot) return;

    struct discord_select_option *select_options = discord_array(
        struct discord_select_option,
        {
            {
                .label = "Rogue",
                .value = "rogue",
                .description = "Sneak n stab",
                .emoji = discord_struct(emoji,
                                        {
                                            .name = "rogue",
                                            .id = 625891304148303894ULL,
                                        }),
            },
            {
                .label = "Mage",
                .value = "mage",
                .description = "Turn 'em into a sheep",
                .emoji = discord_struct(emoji,
                                        {
                                            .name = "mage",
                                            .id = 625891304081063986ULL,
                                        }),
            },
            {
                .label = "Priest",
                .value = "priest",
                .description = "You get heals when I'm "
                               "done doing damage",
                .emoji = discord_struct(emoji,
                                        {
                                            .name = "priest",
                                            .id = 625891303795982337ULL,
                                        }),
            },
        });
    struct discord_component *select_menu =
        discord_array(component, {
                                     {
                                         .type = DISCORD_COMPONENT_SELECT_MENU,
                                         .custom_id = "class_select_1",
                                         .options = select_options,
                                         .placeholder = "Choose a class",
                                         .min_values = 1,
                                         .max_values = 3,
                                     },
                                 });
    struct discord_component *action_rows = discord_array(
        struct discord_compoent, {
                                     { .type = DISCORD_COMPONENT_ACTION_ROW,
                                       .components = select_menu },
                                 });
    struct discord_create_message params = {
        .content = "Mason is looking for new arena partners. What classes do "
                   "you play?",
        .components = action_rows,
    };

    discord_create_message(client, event->channel_id, &params, NULL);
}

void
on_interaction_create(struct discord *client,
                      const struct discord_interaction *event)
{
    logmod_log(INFO, NULL, "Interaction %" PRIu64 " received", event->id);

    if (!event->data || !event->data->values) return;

    char *values = NULL;
    size_t size = 0;
    discord_to_json(&values, &size, event->data->values);
    char text[DISCORD_MAX_MESSAGE_LEN];
    snprintf(text, sizeof(text),
             "So you have chosen:\n"
             "```json\n"
             "%s\n"
             "```",
             values);
    discord_free(values);

    struct discord_interaction_response params = {
        .type = DISCORD_INTERACTION_CHANNEL_MESSAGE_WITH_SOURCE, // 4
        .data = discord_struct(interaction_callback_data,
                               {
                                   .content = text,
                                   .flags = DISCORD_MESSAGE_EPHEMERAL // 1 << 6
                               }),
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

    struct discord *client = discord_from_json(config_file);
    assert(NULL != client && "Couldn't initialize client");

    discord_set_on_ready(client, &on_ready);
    discord_set_prefix(client, "!");
    discord_set_on_command(client, "dynamic", &on_dynamic);
    discord_set_on_command(client, "static", &on_static);
    discord_set_on_interaction_create(client, &on_interaction_create);

    print_usage();
    fgetc(stdin); // wait for input

    discord_run(client);

    discord_cleanup(client);
}
