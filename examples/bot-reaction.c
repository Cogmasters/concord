#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h> /* SCNu64 */
#include <assert.h>

#include "discord.h"

void on_ready(struct discord *client, const struct discord_user *bot)
{
  log_info("Reaction-Bot succesfully connected to Discord as %s#%s!",
           bot->username, bot->discriminator);
}

void on_get_users(struct discord *client,
                  const struct discord_user *bot,
                  const struct discord_message *msg)
{
  if (msg->author->bot || !msg->referenced_message) return;

  NTL_T(struct discord_user) users = NULL;
  ORCAcode code;
  code = discord_get_reactions(
    client, msg->referenced_message->channel_id, msg->referenced_message->id,
    0, msg->content, &(struct discord_get_reactions_params){ .limit = 25 },
    &users);

  char text[DISCORD_MAX_MESSAGE_LEN];
  if (code != ORCA_OK || !users) {
    snprintf(text, sizeof(text), "Nobody reacted with '%s'!", msg->content);
  }
  else {
    char *cur = text;
    char *end = &text[sizeof(text) - 1];
    for (size_t i = 0; users[i]; ++i) {
      cur += snprintf(cur, end - cur, "%s (%" PRIu64 ")\n", users[i]->username,
                      users[i]->id);
      if (cur >= end) break;
    }
    discord_user_list_free(users);
  }

  struct discord_create_message_params params = { .content = text };
  discord_create_message(client, msg->channel_id, &params, NULL);
}

void on_create(struct discord *client,
               const struct discord_user *bot,
               const struct discord_message *msg)
{
  if (msg->author->bot || !msg->referenced_message) return;

  discord_create_reaction(client, msg->referenced_message->channel_id,
                          msg->referenced_message->id, 0, msg->content);
}

void on_delete(struct discord *client,
               const struct discord_user *bot,
               const struct discord_message *msg)
{
  if (msg->author->bot || !msg->referenced_message) return;

  discord_delete_all_reactions_for_emoji(
    client, msg->referenced_message->channel_id, msg->referenced_message->id,
    0, msg->content);
}

void on_delete_all(struct discord *client,
                   const struct discord_user *bot,
                   const struct discord_message *msg)
{
  if (msg->author->bot || !msg->referenced_message) return;

  discord_delete_all_reactions(client, msg->referenced_message->channel_id,
                               msg->referenced_message->id);
}

void on_delete_self(struct discord *client,
                    const struct discord_user *bot,
                    const struct discord_message *msg)
{
  if (msg->author->bot || !msg->referenced_message) return;

  discord_delete_own_reaction(client, msg->referenced_message->channel_id,
                              msg->referenced_message->id, 0, msg->content);
}

void on_delete_user(struct discord *client,
                    const struct discord_user *bot,
                    const struct discord_message *msg)
{
  if (msg->author->bot || !msg->referenced_message) return;

  u64_snowflake_t user_id = 0;
  char emoji_name[256] = "";
  sscanf(msg->content, "%" SCNu64 " %s", &user_id, emoji_name);

  discord_delete_user_reaction(client, msg->referenced_message->channel_id,
                               msg->referenced_message->id, user_id, 0,
                               emoji_name);
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

  discord_set_prefix(client, "reaction.");
  discord_set_on_command(client, "get_users", &on_get_users);
  discord_set_on_command(client, "create", &on_create);
  discord_set_on_command(client, "delete", &on_delete);
  discord_set_on_command(client, "delete_all", &on_delete_all);
  discord_set_on_command(client, "delete_self", &on_delete_self);
  discord_set_on_command(client, "delete_user", &on_delete_user);

  printf("\n\nThis bot demonstrates how easy it is to create/delete"
         " reactions from a message.\n"
         "1. Reply to a message with 'reaction.get_users <emoji>' to get all "
         "the users who reacted with that particular emoji\n"
         "2. Reply to a message with 'reaction.create <emoji>' and the bot "
         "will react with that emoji\n"
         "3. Reply to a message with 'reaction.delete <emoji>' to delete all "
         "reactions with a particular emoji\n"
         "4. Reply to a message with 'reaction.delete_all' to delete all "
         "reactions\n"
         "5. Reply to a message with 'reaction.delete_self <emoji>' to delete "
         "your reaction with a particular emoji\n"
         "6. Reply to a message with 'reaction.delete_user <user_id> <emoji>' "
         "to delete the user reaction with a particular emoji\n"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input

  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}
