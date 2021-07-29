#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "discord.h"
#include "cee-utils.h"

char JSON_STRING[] = \
"{\n"
"    \"content\": \"Mason is looking for new arena partners. What classes do you play?\",\n"
"    \"components\": [\n"
"        {\n"
"            \"type\": 1,\n"
"            \"components\": [\n"
"                {\n"
"                    \"type\": 3,\n"
"                    \"custom_id\": \"class_select_1\",\n"
"                    \"options\":[\n"
"                        {\n"
"                            \"label\": \"Rogue\",\n"
"                            \"value\": \"rogue\",\n"
"                            \"description\": \"Sneak n stab\",\n"
"                            \"emoji\": {\n"
"                                \"name\": \"rogue\",\n"
"                                \"id\": \"625891304148303894\"\n"
"                            }\n"
"                        },\n"
"                        {\n"
"                            \"label\": \"Mage\",\n"
"                            \"value\": \"mage\",\n"
"                            \"description\": \"Turn 'em into a sheep\",\n"
"                            \"emoji\": {\n"
"                                \"name\": \"mage\",\n"
"                                \"id\": \"625891304081063986\"\n"
"                            }\n"
"                        },\n"
"                        {\n"
"                            \"label\": \"Priest\",\n"
"                            \"value\": \"priest\",\n"
"                            \"description\": \"You get heals when I'm done doing damage\",\n"
"                            \"emoji\": {\n"
"                                \"name\": \"priest\",\n"
"                                \"id\": \"625891303795982337\"\n"
"                            }\n"
"                        }\n"
"                    ],\n"
"                    \"placeholder\": \"Choose a class\",\n"
"                    \"min_values\": 1,\n"
"                    \"max_values\": 3\n"
"                }\n"
"            ]\n"
"        }\n"
"    ]\n"
"}\n"
;


void on_ready(struct discord *client, const struct discord_user *bot) {
  log_info("Components-Bot succesfully connected to Discord as %s#%s!",
      bot->username, bot->discriminator);
}

void on_from_json_init(
    struct discord *client,
    const struct discord_user *bot,
    const struct discord_message *msg)
{
  if (msg->author->bot) return;

  struct discord_message *loaded_msg=NULL;
  discord_message_from_json(JSON_STRING, sizeof(JSON_STRING), &loaded_msg);

  struct discord_create_message_params params = {
    .content = loaded_msg->content,
    .components = loaded_msg->components
  };
  discord_create_message(client, msg->channel_id, &params, NULL);

  discord_message_free(loaded_msg);
}

void on_designated_init(
    struct discord *client,
    const struct discord_user *bot,
    const struct discord_message *msg)
{
  if (msg->author->bot) return;

  struct discord_create_message_params params = 
  {
    .content = "Mason is looking for new arena partners. What classes do you play?",
    .components = (struct discord_component*[]){ // NULL-TERMINATED ARRAY
      &(struct discord_component){ 
        .type = DISCORD_COMPONENT_ACTION_ROW,
        .components = (struct discord_component*[]){ // NULL-TERMINATED ARRAY
          &(struct discord_component){
            .type = DISCORD_COMPONENT_SELECT_MENU,
            .custom_id = "class_select_1",
            .options = (struct discord_select_option*[])
            {
              &(struct discord_select_option){
                .label = "Rogue",
                .value = "rogue",
                .description = "Sneak n stab",
                .emoji = &(struct discord_emoji){
                  .name = "rogue",
                  .id = 625891304148303894ULL
                }
              },
              &(struct discord_select_option){
                .label = "Mage",
                .value = "mage",
                .description = "Turn 'em into a sheep",
                .emoji = &(struct discord_emoji){
                  .name = "mage",
                  .id = 625891304081063986ULL
                }
              },
              &(struct discord_select_option){
                .label = "Priest",
                .value = "priest",
                .description = "You get heals when I'm done doing damage",
                .emoji = &(struct discord_emoji){
                  .name = "priest",
                  .id = 625891303795982337ULL
                }
              },
              (struct discord_select_option*){ NULL }
            },
            .placeholder = "Choose a class",
            .min_values = 1,
            .max_values = 3
          },
          (struct discord_component*){ NULL }
        }
      }, 
      (struct discord_component*){ NULL }
    }
  };

  discord_create_message(client, msg->channel_id, &params, NULL);
}

void on_dynamic_init(
    struct discord *client,
    const struct discord_user *bot,
    const struct discord_message *msg)
{
  if (msg->author->bot) return;

  struct discord_component *select = discord_component_alloc();   
  select->type = DISCORD_COMPONENT_SELECT_MENU;
  snprintf(select->custom_id, sizeof(select->custom_id), "class_select_1");

  struct discord_select_option *option1 = discord_select_option_alloc();
  snprintf(option1->label, sizeof(option1->label), "Rogue");
  snprintf(option1->value, sizeof(option1->value), "rogue");
  snprintf(option1->description, sizeof(option1->description), "Sneak n stab");
  option1->emoji->name = strdup("rogue");
  option1->emoji->id = 625891304148303894ULL;
  ntl_append2((ntl_t*)&select->options, sizeof(struct discord_select_option), option1);

  struct discord_select_option *option2 = discord_select_option_alloc();
  snprintf(option2->label, sizeof(option2->label), "Mage");
  snprintf(option2->value, sizeof(option2->value), "mage");
  snprintf(option2->description, sizeof(option2->description), "Turn 'em into a sheep");
  option2->emoji->name = strdup("mage");
  option2->emoji->id = 625891304081063986ULL;
  ntl_append2((ntl_t*)&select->options, sizeof(struct discord_select_option), option2);

  struct discord_select_option *option3 = discord_select_option_alloc();
  snprintf(option3->label, sizeof(option3->label), "Priest");
  snprintf(option3->value, sizeof(option3->value), "priest");
  snprintf(option3->description, sizeof(option3->description), "You get heals when I'm done doing damage");
  option3->emoji->name = strdup("priest");
  option3->emoji->id = 625891303795982337ULL;
  ntl_append2((ntl_t*)&select->options, sizeof(struct discord_select_option), option3);

  struct discord_component *action = discord_component_alloc();   
  action->type = DISCORD_COMPONENT_ACTION_ROW;
  ntl_append2((ntl_t*)&action->components, sizeof(struct discord_component), select);

  NTL_T(struct discord_component) components = NULL;
  ntl_append2((ntl_t*)&components, sizeof(struct discord_component), action);

  struct discord_create_message_params params = { 
    .content = "Mason is looking for new arena partners. What classes do you play?",
    .components = components
  };

  discord_create_message(client, msg->channel_id, &params, NULL);

  discord_component_list_free(components);
}

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";

  discord_global_init();

  struct discord *client = discord_config_init(config_file);
  assert(NULL != client && "Couldn't initialize client");

  discord_set_on_ready(client, &on_ready);
  discord_set_prefix(client, "!");
  discord_set_on_command(client, "from_json_init", &on_from_json_init);
  discord_set_on_command(client, "designated_init", &on_designated_init);
  discord_set_on_command(client, "dynamic_init", &on_dynamic_init);

  printf("\n\nThis bot demonstrates how to load message components"
         " with three different methods.\n"
         "1 - From JSON init (type !from_json_init): This is the easiest method by far, you can use it"
         " with a JSON library of your preference.\n"
         "2 - Designated init (type !designated_init): This is a 'clean' initialization approach"
         " but is not very flexible.\n"
         "3 - Dynamic init (type !dynamic_init): While this is a very flexible approach, it can"
         " easily become very hard to read.\n"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input

  discord_run(client);

  discord_cleanup(client);
  discord_global_cleanup();
}

