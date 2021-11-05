#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h> /* PRIu64, SCNu64 */
#include <assert.h>

#include "discord.h"

void on_ready(struct discord *client, const struct discord_user *bot)
{
  log_info("Pin-Bot succesfully connected to Discord as %s#%s!", bot->username,
           bot->discriminator);
}

void on_pin(struct discord *client,
            const struct discord_user *bot,
            const struct discord_message *msg)
{
  if (msg->author->bot) return;

  u64_snowflake_t msg_id = 0;
  sscanf(msg->content, "%" SCNu64, &msg_id);
  if (!msg_id) {
    if (!msg->referenced_message) return;
    msg_id = msg->referenced_message->id;
  }

  discord_pin_message(client, msg->channel_id, msg_id);
}

void on_unpin(struct discord *client,
              const struct discord_user *bot,
              const struct discord_message *msg)
{
  if (msg->author->bot) return;

  u64_snowflake_t msg_id = 0;
  sscanf(msg->content, "%" SCNu64, &msg_id);
  if (!msg_id) {
    if (!msg->referenced_message) return;
    msg_id = msg->referenced_message->id;
  }

  discord_unpin_message(client, msg->channel_id, msg_id);
}

void on_get_pins(struct discord *client,
                 const struct discord_user *bot,
                 const struct discord_message *msg)
{
  if (msg->author->bot) return;

  NTL_T(struct discord_message) msgs = NULL;
  discord_get_pinned_messages(client, msg->channel_id, &msgs);

  char text[DISCORD_MAX_MESSAGE_LEN];
  if (!msgs) {
    sprintf(text, "No pinned messages in <#%" PRIu64 ">", msg->channel_id);
  }
  else {
    char *cur = text;
    char *end = &text[sizeof(text) - 1];
    for (size_t i = 0; msgs[i]; ++i) {
      cur += snprintf(cur, end - cur,
                      "https://discord.com/channels/%" PRIu64 "/%" PRIu64
                      "/%" PRIu64 "\n",
                      msg->guild_id, msg->channel_id, msgs[i]->id);
      if (cur >= end) break;
    }
    discord_message_list_free(msgs);
  }

  struct discord_create_message_params params = { .content = text };
  discord_create_message(client, msg->channel_id, &params, NULL);
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
  discord_set_on_command(client, "pin", &on_pin);
  discord_set_on_command(client, "unpin", &on_unpin);
  discord_set_on_command(client, "get_pins", &on_get_pins);

  printf(
    "\n\nThis bot demonstrates how easy it is to have a"
    " message be pinned.\n"
    "1. Reply to a message with '!pin' or type '!pin <message_id> to pin it\n"
    "2. Reply to a message with '!unpin' or type '!unpin <message_id> to "
    "unpin it\n"
    "3. Type '!get_pins' to get a id list of pinned messages\n"
    "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input

  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}
