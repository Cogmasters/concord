#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "discord.h"
#include "discord-internal.h"

#include "cee-utils.h"

static char JSON[] =
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
"}";


void on_ready(struct discord *client, const struct discord_user *me) {
  log_info("Succesfully connected to Discord as %s#%s!",
      me->username, me->discriminator);
}

void on_disconnect(
  struct discord *client,
  const struct discord_user *bot,
  const struct discord_message *msg)
{
  if (msg->author->bot) return;

  struct discord_create_message_params params = { .content = "Disconnecting ..." };
  discord_create_message(client, msg->channel_id, &params, NULL);

  discord_gateway_shutdown(&client->gw);
}

void on_send_json(
  struct discord *client,
  const struct discord_user *bot,
  const struct discord_message *msg)
{
  if (msg->author->bot) return;

  discord_adapter_run(
    &client->adapter,
    NULL,
    &(struct sized_buffer){ JSON, sizeof(JSON)-1 },
    HTTP_POST, 
    "/channels/%"PRIu64"/messages", msg->channel_id);
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
  discord_set_on_command(client, "disconnect", &on_disconnect);
  discord_set_on_command(client, "send_json", &on_send_json);

  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}

