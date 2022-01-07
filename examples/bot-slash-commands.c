#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <inttypes.h> /* SCNu64, PRIu64 */

#include "discord.h"

unsigned long long g_app_id;

void on_ready(struct discord *client)
{
  const struct discord_user *bot = discord_get_self(client);

  log_info("Slash-Commands-Bot succesfully connected to Discord as %s#%s!",
           bot->username, bot->discriminator);
}

void log_on_app_create(struct discord *client,
                       const struct discord_application_command *cmd)
{
  log_info("Application Command %s created", cmd->name);
}

void on_slash_command_create(struct discord *client,
                             const struct discord_message *msg)
{
  if (msg->author->bot) return;

  struct discord_create_guild_application_command_params params = {
    .type = DISCORD_APPLICATION_COMMAND_CHAT_INPUT,
    .name = "fill-form",
    .description = "A slash command example for form filling",
    .default_permission = true,
    .options =
      (struct discord_application_command_option *[]){
        &(struct discord_application_command_option){
          .type = DISCORD_APPLICATION_COMMAND_OPTION_STRING,
          .name = "nick",
          .description = "Your nick",
          .required = true,
        },
        &(struct discord_application_command_option){
          .type = DISCORD_APPLICATION_COMMAND_OPTION_INTEGER,
          .name = "pets",
          .description = "How many pets you got",
        },
        &(struct discord_application_command_option){
          .type = DISCORD_APPLICATION_COMMAND_OPTION_STRING,
          .name = "gender",
          .description = "Your gender",
          .choices =
            (struct discord_application_command_option_choice *[]){
              &(struct discord_application_command_option_choice){
                .name = "male",
                .value = "male",
              },
              &(struct discord_application_command_option_choice){
                .name = "female",
                .value = "female",
              },
              &(struct discord_application_command_option_choice){
                .name = "other",
                .value = "other",
              },
              NULL // END OF CHOICES
            },
        },
        &(struct discord_application_command_option){
          .type = DISCORD_APPLICATION_COMMAND_OPTION_CHANNEL,
          .name = "favorite",
          .description = "Favorite channel",
          .channel_types =
            (ja_u64 *[]){
              &(ja_u64){ DISCORD_CHANNEL_GUILD_TEXT },
              NULL, // END OF CHANNEL TYPES
            },
        },
        NULL // END OF OPTIONS
      }
  };

  /* Create slash command */
  discord_create_guild_application_command(client, g_app_id, msg->guild_id,
                                           &params, NULL);
}

void on_interaction_create(struct discord *client,
                           const struct discord_interaction *interaction)
{
  /* We're only interested on slash commands */
  if (interaction->type != DISCORD_INTERACTION_APPLICATION_COMMAND) return;
  /* Return in case user input is missing for some reason */
  if (!interaction->data || !interaction->data->options) return;

  char *nick = "blank";
  int pets = 0;
  char *gender = "blank";
  u64_snowflake_t channel_id = 0;

  for (int i = 0; interaction->data->options[i]; ++i) {
    char *name = interaction->data->options[i]->name;
    char *value = interaction->data->options[i]->value;

    if (0 == strcmp("nick", name)) {
      nick = value;
    }
    else if (0 == strcmp("pets", name)) {
      pets = strtol(value, NULL, 10);
    }
    else if (0 == strcmp("gender", name)) {
      gender = value;
    }
    else if (0 == strcmp("favorite", name)) {
      sscanf(value, "%" SCNu64, &channel_id);
    }
  }

  char buf[DISCORD_MAX_MESSAGE_LEN] = "";
  snprintf(buf, sizeof(buf),
           "Fun-facts about <@%" PRIu64 ">!\n"
           "Nick: %s\n"
           "Pets: %d\n"
           "Gender: %s\n"
           "Favorite channel: <#%" PRIu64 ">\n",
           interaction->member->user->id, nick, pets, gender, channel_id);

  struct discord_interaction_response params = {
    .type = DISCORD_INTERACTION_CALLBACK_CHANNEL_MESSAGE_WITH_SOURCE,
    .data = &(struct discord_interaction_callback_data){ .content = buf }
  };

  CCORDcode code;
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

  ccord_global_init();
  struct discord *client = discord_config_init(config_file);
  assert(NULL != client && "Could not initialize client");

  discord_set_on_command(client, "!slash_create", &on_slash_command_create);
  discord_set_on_ready(client, &on_ready);
  discord_set_on_application_command_create(client, &log_on_app_create);
  discord_set_on_interaction_create(client, &on_interaction_create);

  printf("Please provide a valid application id in order to test the Slash "
         "Commands functionality, it can be obtained from: "
         "https://discord.com/developers/applications\n");
  do {
    printf("Application ID:\n");
    fscanf(stdin, "%llu", &g_app_id);
  } while (!g_app_id || errno == ERANGE);

  printf(
    "\n\nThis bot demonstrates how easy it is to create, and react to "
    "application commands\n"
    "1. Type '!slash_create' to create the application command\n"
    "2. Type '/' in the same channel and select the newly created command\n"
    "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input

  discord_run(client);

  discord_cleanup(client);
  ccord_global_cleanup();
}
