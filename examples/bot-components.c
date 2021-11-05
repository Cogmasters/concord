#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h> /* PRIu64 */
#include <assert.h>

#include "discord.h"
#include "cee-utils.h"

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

void on_ready(struct discord *client, const struct discord_user *bot)
{
  log_info("Components-Bot succesfully connected to Discord as %s#%s!",
           bot->username, bot->discriminator);
}

void on_from_json_init(struct discord *client,
                       const struct discord_user *bot,
                       const struct discord_message *msg)
{
  if (msg->author->bot) return;

  NTL_T(struct discord_component) components = NULL;
  discord_component_list_from_json(JSON_STRING, sizeof(JSON_STRING),
                                   &components);

  struct discord_create_message_params params = {
    .content =
      "Mason is looking for new arena partners. What classes do you play?",
    .components = components
  };
  discord_create_message(client, msg->channel_id, &params, NULL);

  discord_component_list_free(components);
}

void on_designated_init(struct discord *client,
                        const struct discord_user *bot,
                        const struct discord_message *msg)
{
  if (msg->author->bot) return;

  NTL_T(struct discord_component)
  components = (struct discord_component *[]){
    &(struct discord_component){
      .type = DISCORD_COMPONENT_ACTION_ROW,
      .components =
        (struct discord_component *[]){
          // 2nd LEVEL ARRAY START
          &(struct discord_component){
            .type = DISCORD_COMPONENT_SELECT_MENU,
            .custom_id = "class_select_1",
            .options =
              (struct discord_select_option *[]){
                // 3rd LEVEL ARRAY START
                &(struct discord_select_option){
                  .label = "Rogue",
                  .value = "rogue",
                  .description = "Sneak n stab",
                  .emoji =
                    &(struct discord_emoji){ .name = "rogue",
                                             .id = 625891304148303894ULL } },
                &(struct discord_select_option){
                  .label = "Mage",
                  .value = "mage",
                  .description = "Turn 'em into a sheep",
                  .emoji =
                    &(struct discord_emoji){ .name = "mage",
                                             .id = 625891304081063986ULL } },
                &(struct discord_select_option){
                  .label = "Priest",
                  .value = "priest",
                  .description = "You get heals when I'm done doing damage",
                  .emoji =
                    &(struct discord_emoji){ .name = "priest",
                                             .id = 625891303795982337ULL } },
                NULL // 3rd LEVEL ARRAY END
              },
            .placeholder = "Choose a class",
            .min_values = 1,
            .max_values = 3 },
          NULL // 2nd LEVEL ARRAY END
        } },
    NULL // 1st LEVEL ARRAY END
  };

  struct discord_create_message_params params = {
    .content =
      "Mason is looking for new arena partners. What classes do you play?",
    .components = components
  };
  discord_create_message(client, msg->channel_id, &params, NULL);
}

void on_dynamic_init(struct discord *client,
                     const struct discord_user *bot,
                     const struct discord_message *msg)
{
  if (msg->author->bot) return;

  NTL_T(struct discord_component) components = NULL;
  // initialize the action menu structure
  struct discord_component action = { .type = DISCORD_COMPONENT_ACTION_ROW };
  // initialize the select menu structure
  struct discord_component select = { .type = DISCORD_COMPONENT_SELECT_MENU,
                                      .custom_id = "class_select_1",
                                      .placeholder = "Choose a class",
                                      .min_values = 1,
                                      .max_values = 3 };

  // initialize 1st option and append to select.options
  struct discord_select_option option = { .label = "Rogue",
                                          .value = "rogue",
                                          .description = "Sneak n stab",
                                          .emoji = malloc(
                                            sizeof(struct discord_emoji)) };
  *option.emoji = (struct discord_emoji){ .name = strdup("rogue"),
                                          .id = 625891304148303894ULL };
  ntl_append2((ntl_t *)&select.options, sizeof(struct discord_select_option),
              &option);

  // initialize 2nd option and append to select.options
  option =
    (struct discord_select_option){ .label = "Mage",
                                    .value = "mage",
                                    .description = "Turn 'em into a sheep",
                                    .emoji =
                                      malloc(sizeof(struct discord_emoji)) };
  *option.emoji = (struct discord_emoji){ .name = strdup("mage"),
                                          .id = 625891304081063986ULL };
  ntl_append2((ntl_t *)&select.options, sizeof(struct discord_select_option),
              &option);

  // initialize 3rd option and append to select.options
  option = (struct discord_select_option){
    .label = "Priest",
    .value = "priest",
    .description = "You get heals when I'm done doing damage",
    .emoji = malloc(sizeof(struct discord_emoji))
  };
  *option.emoji = (struct discord_emoji){ .name = strdup("priest"),
                                          .id = 625891303795982337ULL };
  ntl_append2((ntl_t *)&select.options, sizeof(struct discord_select_option),
              &option);

  // append the select menu to action.components
  ntl_append2((ntl_t *)&action.components, sizeof(struct discord_component),
              &select);
  // append action to components
  ntl_append2((ntl_t *)&components, sizeof(struct discord_component), &action);

  struct discord_create_message_params params = {
    .content =
      "Mason is looking for new arena partners. What classes do you play?",
    .components = components
  };
  discord_create_message(client, msg->channel_id, &params, NULL);

  // free 'components' and its inner structs
  discord_component_list_free(components);
}

void on_interaction_create(struct discord *client,
                           const struct discord_user *bot,
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

  ORCAcode code;
  code = discord_create_interaction_response(
    client, interaction->id, interaction->token, &params, NULL);
  if (code) {
    log_error("%s", discord_strerror(code, client));
  }
}

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "../config.json";

  discord_global_init();

  struct discord *client = discord_config_init(config_file);
  assert(NULL != client && "Couldn't initialize client");

  discord_set_on_ready(client, &on_ready);
  discord_set_prefix(client, "!");
  discord_set_on_command(client, "from_json_init", &on_from_json_init);
  discord_set_on_command(client, "designated_init", &on_designated_init);
  discord_set_on_command(client, "dynamic_init", &on_dynamic_init);
  discord_set_on_interaction_create(client, &on_interaction_create);

  printf("\n\nThis bot demonstrates how to load message components"
         " with three different methods.\n"
         "1 - From JSON init (type !from_json_init): This is the easiest "
         "method by far, you can use it"
         " with a JSON library of your preference.\n"
         "2 - Designated init (type !designated_init): This is a 'clean' "
         "initialization approach"
         " but is not very flexible.\n"
         "3 - Dynamic init (type !dynamic_init): While this is a very "
         "flexible approach, it can"
         " easily become very hard to read.\n"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input

  discord_run(client);

  discord_cleanup(client);
  discord_global_cleanup();
}
