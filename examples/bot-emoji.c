#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h> /* PRIu64, SCNu64 */
#include <assert.h>

#include "discord.h"

void on_ready(struct discord *client, const struct discord_user *bot)
{
  log_info("Emoji-Bot succesfully connected to Discord as %s#%s!",
           bot->username, bot->discriminator);
}

void on_list(struct discord *client,
             const struct discord_user *bot,
             const struct discord_message *msg)
{
  if (msg->author->bot) return;

  NTL_T(struct discord_emoji) emojis = NULL;
  ORCAcode code;
  code = discord_list_guild_emojis(client, msg->guild_id, &emojis);

  char text[DISCORD_MAX_MESSAGE_LEN];
  if (code != ORCA_OK || !emojis) {
    sprintf(text, "No guild emojis found.");
  }
  else {
    char *cur = text;
    char *end = &text[sizeof(text) - 1];
    char *prev;
    for (size_t i = 0; emojis[i]; ++i) {
      prev = cur;
      cur += snprintf(cur, end - cur, "<%s:%s:%" PRIu64 ">(%" PRIu64 ")\n",
                      emojis[i]->animated ? "a" : "", emojis[i]->name,
                      emojis[i]->id, emojis[i]->id);

      if (cur >= end) { // to make sure no emoji is skipped
        *prev = '\0'; // end string before truncation
        // reset for retry
        cur = text;
        --i;

        struct discord_create_message_params params = { .content = text };
        discord_create_message(client, msg->channel_id, &params, NULL);
        continue;
      }
    }
    discord_emoji_list_free(emojis);
  }

  struct discord_create_message_params params = { .content = text };
  discord_create_message(client, msg->channel_id, &params, NULL);
}

void on_get(struct discord *client,
            const struct discord_user *bot,
            const struct discord_message *msg)
{
  if (msg->author->bot) return;

  char text[DISCORD_MAX_MESSAGE_LEN];
  u64_snowflake_t emoji_id = 0;
  sscanf(msg->content, "%" SCNu64, &emoji_id);
  if (!emoji_id) {
    sprintf(text, "Missing 'emoji_id'");
  }
  else {
    struct discord_emoji emoji = { 0 };

    discord_get_guild_emoji(client, msg->guild_id, emoji_id, &emoji);
    if (emoji.id)
      sprintf(text, "Here you go: <%s:%s:%" PRIu64 ">",
              emoji.animated ? "a" : "", emoji.name, emoji.id);
    else
      sprintf(text, "Unknown emoji");

    discord_emoji_cleanup(&emoji);
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
  assert(NULL != client && "Could not initialize client");

  discord_set_on_ready(client, &on_ready);

  discord_set_prefix(client, "emoji.");
  discord_set_on_command(client, "list", &on_list);
  discord_set_on_command(client, "get", &on_get);

  printf("\n\n This bot demonstrates how easy it is to create/delete emojis\n"
         "1. Type 'emoji.list' to get a list of server emojis\n"
         "2. Type 'emoji.get <emoji_id>' to get the selected emoji\n"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input

  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}
