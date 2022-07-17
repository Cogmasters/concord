#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h> /* PRIu64 */
#include <assert.h>

#include "discord.h"
#include "log.h"

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

char JSON[] =
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
    log_info("Components-Bot succesfully connected to Discord as %s#%s!",
             event->user->username, event->user->discriminator);
}

void
on_dynamic(struct discord *client, const struct discord_message *event)
{
    if (event->author->bot) return;

    struct discord_components components = { 0 };
    discord_components_from_json(JSON, sizeof(JSON), &components);

    struct discord_create_message params = {
        .content = "Mason is looking for new arena partners. What classes do "
                   "you play?",
        .components = &components
    };
    discord_create_message(client, event->channel_id, &params, NULL);

    /* must cleanup 'components' afterwards */
    discord_components_cleanup(&components);
}

void
on_static(struct discord *client, const struct discord_message *event)
{
    if (event->author->bot) return;

    struct discord_select_option select_options[] = {
        {
            .label = "Rogue",
            .value = "rogue",
            .description = "Sneak n stab",
            .emoji =
                &(struct discord_emoji){
                    .name = "rogue",
                    .id = 625891304148303894ULL,
                },
        },
        {
            .label = "Mage",
            .value = "mage",
            .description = "Turn 'em into a sheep",
            .emoji =
                &(struct discord_emoji){
                    .name = "mage",
                    .id = 625891304081063986ULL,
                },
        },
        {
            .label = "Priest",
            .value = "priest",
            .description = "You get heals when I'm "
                           "done doing damage",
            .emoji =
                &(struct discord_emoji){
                    .name = "priest",
                    .id = 625891303795982337ULL,
                },
        },
    };
    struct discord_component select_menu[] = {
        {
            .type = DISCORD_COMPONENT_SELECT_MENU,
            .custom_id = "class_select_1",
            .options =
                &(struct discord_select_options){
                    .size = sizeof(select_options) / sizeof *select_options,
                    .array = select_options,
                },
            .placeholder = "Choose a class",
            .min_values = 1,
            .max_values = 3,
        },
    };
    struct discord_component action_rows[] = {
        {
            .type = DISCORD_COMPONENT_ACTION_ROW,
            .components =
                &(struct discord_components){
                    .size = sizeof(select_menu) / sizeof *select_menu,
                    .array = select_menu,
                },
        },
    };
    struct discord_create_message params = {
        .content = "Mason is looking for new arena partners. What classes do "
                   "you play?",
        .components =
            &(struct discord_components){
                .size = sizeof(action_rows) / sizeof *action_rows,
                .array = action_rows,
            },
    };

    discord_create_message(client, event->channel_id, &params, NULL);
}

void
on_interaction_create(struct discord *client,
                      const struct discord_interaction *event)
{
    log_info("Interaction %" PRIu64 " received", event->id);

    if (!event->data || !event->data->values) return;

    char values[1024];
    strings_to_json(values, sizeof(values), event->data->values);

    char text[DISCORD_MAX_MESSAGE_LEN];
    snprintf(text, sizeof(text),
             "So you have chosen:\n"
             "```json\n"
             "%s\n"
             "```",
             values);

    struct discord_interaction_response params = {
        .type = DISCORD_INTERACTION_CHANNEL_MESSAGE_WITH_SOURCE, // 4
        .data =
            &(struct discord_interaction_callback_data){
                .content = text,
                .flags = DISCORD_MESSAGE_EPHEMERAL // 1 << 6
            }
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
    ccord_global_cleanup();
}
