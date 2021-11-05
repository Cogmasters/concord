#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "discord.h"

void on_ready(struct discord *client, const struct discord_user *bot)
{
  log_info("Ban-Bot succesfully connected to Discord as %s#%s!", bot->username,
           bot->discriminator);
}

void on_guild_ban_add(struct discord *client,
                      const struct discord_user *bot,
                      const u64_snowflake_t guild_id,
                      const struct discord_user *user)
{
  struct discord_channel general = { 0 };
  if (discord_get_channel_at_pos(client, guild_id, DISCORD_CHANNEL_GUILD_TEXT,
                                 0, &general))
  {
    log_error("Couldn't fetch channel at position 0");
    return;
  }

  char text[128];
  snprintf(text, sizeof(text), "User `%s` has been banned.", user->username);
  struct discord_create_message_params params = { .content = text };
  discord_create_message(client, general.id, &params, NULL);
  discord_channel_cleanup(&general);
}

void on_guild_ban_remove(struct discord *client,
                         const struct discord_user *bot,
                         const u64_snowflake_t guild_id,
                         const struct discord_user *user)
{
  struct discord_channel general = { 0 };
  if (discord_get_channel_at_pos(client, guild_id, DISCORD_CHANNEL_GUILD_TEXT,
                                 0, &general))
  {
    log_error("Couldn't fetch channel at position 0");
    return;
  }

  char text[128];
  snprintf(text, sizeof(text), "User `%s` has been unbanned.", user->username);
  struct discord_create_message_params params = { .content = text };
  discord_create_message(client, general.id, &params, NULL);
  discord_channel_cleanup(&general);
}

void on_ban(struct discord *client,
            const struct discord_user *bot,
            const struct discord_message *msg)
{
  // get member list
  NTL_T(struct discord_guild_member) members = NULL;
  ORCAcode code = discord_list_guild_members(
    client, msg->guild_id,
    &(struct discord_list_guild_members_params){ .limit = 1000, .after = 0 },
    &members);
  if (code != ORCA_OK || !members) return;

  // get username and discriminator of the to be banned user
  char username[128] = "";
  char discriminator[5] = "";
  sscanf(msg->content, "%[^#]#%s", username, discriminator);
  if (!*username || !*discriminator) return;

  // try to find match for to be banned user
  struct discord_user *target = NULL;
  for (size_t i = 0; members[i]; ++i) {
    if (0 == strcmp(members[i]->user->username, username) &&
        0 == strcmp(members[i]->user->discriminator, discriminator))
    {
      target = members[i]->user;
      break; /* EARLY BREAK */
    }
  }
  if (!target) return; // member is not in guild

  char reason[128];
  snprintf(reason, sizeof(reason), "%s said so", msg->author->username);
  discord_create_guild_ban(client, msg->guild_id, target->id,
                           &(struct discord_create_guild_ban_params){
                             .delete_message_days = 1, .reason = reason });

  discord_guild_member_list_free(members);
}

void on_unban(struct discord *client,
              const struct discord_user *bot,
              const struct discord_message *msg)
{
  // get banned list
  NTL_T(struct discord_ban) bans = NULL;

  ORCAcode code;
  code = discord_get_guild_bans(client, msg->guild_id, &bans);
  if (code != ORCA_OK || !bans) return;

  // get username and discriminator of the to be banned user
  char username[128] = "";
  char discriminator[5] = "";
  sscanf(msg->content, "%[^#]#%s", username, discriminator);
  if (!*username || !*discriminator) return;

  // try to find match for to be banned user
  struct discord_user *target = NULL;
  for (size_t i = 0; bans[i]; ++i) {
    if (0 == strcmp(bans[i]->user->username, username) &&
        0 == strcmp(bans[i]->user->discriminator, discriminator))
    {
      target = bans[i]->user;
      break; /* EARLY BREAK */
    }
  }
  if (!target) return; // member wasn't banned

  discord_remove_guild_ban(client, msg->guild_id, target->id);

  discord_ban_list_free(bans);
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
  discord_set_on_guild_ban_add(client, &on_guild_ban_add);
  discord_set_on_guild_ban_remove(client, &on_guild_ban_remove);
  discord_set_on_command(client, "!ban", &on_ban);
  discord_set_on_command(client, "!unban", &on_unban);

  printf("\n\nThis bot demonstrates how easy it is to ban/unban people\n"
         "1. Type '!ban user#1234' to ban user\n"
         "2. Type '!unban user#1234' to unban user\n"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input

  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}
