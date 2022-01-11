#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h> /* PRIu64 */
#include <assert.h>

#include "discord.h"

char JSON_STRING[] =
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
on_ready(struct discord *client)
{
    const struct discord_user *bot = discord_get_self(client);

    log_info("Components-Bot succesfully connected to Discord as %s#%s!",
             bot->username, bot->discriminator);
}

void
on_dynamic(struct discord *client, const struct discord_message *msg)
{
    if (msg->author->bot) return;

    struct discord_component **components = NULL;
    discord_component_list_from_json(JSON_STRING, sizeof(JSON_STRING),
                                     &components);

    struct discord_create_message_params params = {
        .content = "Mason is looking for new arena partners. What classes do "
                   "you play?",
        .components = components
    };
    discord_create_message(client, msg->channel_id, &params, NULL);

    /* must cleanup 'components' afterwards */
    discord_component_list_free(components);
}

void
on_static(struct discord *client, const struct discord_message *msg)
{
    if (msg->author->bot) return;

    struct discord_component **components = (struct discord_component *[]){
        &(struct discord_component){
            .type = DISCORD_COMPONENT_ACTION_ROW,
            .components =
                (struct discord_component *[]){
                    &(struct discord_component){
                        .type = DISCORD_COMPONENT_SELECT_MENU,
                        .custom_id = "class_select_1",
                        .options =
                            (struct discord_select_option *[]){
                                &(struct discord_select_option){
                                    .label = "Rogue",
                                    .value = "rogue",
                                    .description = "Sneak n stab",
                                    .emoji =
                                        &(struct discord_emoji){
                                            .name = "rogue",
                                            .id = 625891304148303894ULL,
                                        },
                                },
                                &(struct discord_select_option){
                                    .label = "Mage",
                                    .value = "mage",
                                    .description = "Turn 'em into a sheep",
                                    .emoji =
                                        &(struct discord_emoji){
                                            .name = "mage",
                                            .id = 625891304081063986ULL,
                                        },
                                },
                                &(struct discord_select_option){
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
                                NULL /* ARRAY END */
                            },
                        .placeholder = "Choose a class",
                        .min_values = 1,
                        .max_values = 3,
                    },
                    NULL /* ARRAY END */
                },
        },
        NULL /* ARRAY END */
    };

    struct discord_create_message_params params = {
        .content = "Mason is looking for new arena partners. What classes do "
                   "you play?",
        .components = components
    };
    discord_create_message(client, msg->channel_id, &params, NULL);
}

void
on_interaction_create(struct discord *client,
                      const struct discord_interaction *interaction)
{
    log_info("Interaction %" PRIu64 " received", interaction->id);

    if (!interaction->data || !interaction->data->values) return;

    char values[1024];
    ja_str_list_to_json(values, sizeof(values), interaction->data->values);

    char text[DISCORD_MAX_MESSAGE_LEN];
    snprintf(text, sizeof(text),
             "So you have chosen:\n"
             "```json\n"
             "%s\n"
             "```",
             values);

    struct discord_interaction_response params = {
        .type = DISCORD_INTERACTION_CALLBACK_CHANNEL_MESSAGE_WITH_SOURCE, // 4
        .data =
            &(struct discord_interaction_callback_data){
                .content = text,
                .flags = DISCORD_INTERACTION_CALLBACK_DATA_EPHEMERAL // 1 << 6
            }
    };

    CCORDcode code;
    code = discord_create_interaction_response(
        client, interaction->id, interaction->token, &params, NULL);
    if (code) {
        log_error("%s", discord_strerror(code, client));
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

    ccord_global_init();
    struct discord *client = discord_config_init(config_file);
    assert(NULL != client && "Couldn't initialize client");

    discord_set_on_ready(client, &on_ready);
    discord_set_prefix(client, "!");
    discord_set_on_command(client, "dynamic", &on_dynamic);
    discord_set_on_command(client, "static", &on_static);
    discord_set_on_interaction_create(client, &on_interaction_create);

    printf(
        "\n\nThis bot demonstrates how to load message components"
        " with three different methods.\n"
        "1 - Dynamic-approach (type !dynamic): Load the components from "
        "a JSON string.\n"
        "2 - Static-approach (type !static): A clean initialization approach "
        "using the combination of designated initialization and compound "
        "literals.\n"
        "\nTYPE ANY KEY TO START BOT\n");
    fgetc(stdin); // wait for input

    discord_run(client);

    discord_cleanup(client);
    ccord_global_cleanup();
}
