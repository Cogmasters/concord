#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h> /* PRIu64, SCNu64 */
#include <assert.h>

#include "discord.h"
#include "orka-utils.h" // for orka_timestamp_ms()


void on_ready(struct discord *client, const struct discord_user *bot) {
  fprintf(stderr, "\n\nGuild-Bot succesfully connected to Discord as %s#%s!\n\n",
      bot->username, bot->discriminator);
}

void on_log_role_create(
  struct discord *client,
  const struct discord_user *bot,
  const u64_snowflake_t guild_id,
  const struct discord_guild_role *role)
{
  log_warn("Role (%"PRIu64") created", role->id);
}

void on_log_role_update(
  struct discord *client,
  const struct discord_user *bot,
  const u64_snowflake_t guild_id,
  const struct discord_guild_role *role)
{
  log_warn("Role (%"PRIu64") updated", role->id);
}

void on_log_role_delete(
  struct discord *client,
  const struct discord_user *bot,
  const u64_snowflake_t guild_id,
  const u64_snowflake_t role_id)
{
  log_warn("Role (%"PRIu64") deleted", role_id);
}

void on_create(
  struct discord *client,
  const struct discord_user *bot,
  const struct discord_message *msg)
{
  if (msg->author->bot) return;

  struct discord_guild *guild = discord_guild_alloc();
  ORCAcode code;
  {
    struct discord_create_guild_params params = { 
      .name = *msg->content ? msg->content : "TestGuild" 
    };
    code = discord_create_guild(client, &params, guild);
  }

  char text[MAX_MESSAGE_LEN];
  if (ORCA_OK == code) {
    size_t offset = sprintf(text, "Succesfully created guild: %s\n", guild->name);
    if (ORCA_OK == discord_delete_guild(client, guild->id))
      sprintf(text + offset, "Aaaand its gone. Poof.");
    else
      sprintf(text + offset, "Couldn't delete it, ouch. Please delete it manually.");
  }
  else {
    sprintf(text, "Couldn't create guild.");
  }

  struct discord_create_message_params params={ .content = text };
  discord_create_message(client, msg->channel_id, &params, NULL);

  discord_guild_free(guild);
}

void on_role_create(
  struct discord *client,
  const struct discord_user *bot,
  const struct discord_message *msg)
{
  if (msg->author->bot) return;

  char name[128]="";
  sscanf(msg->content, "%s", name);

  char text[MAX_MESSAGE_LEN];
  if (!*name) {
    sprintf(text, "Couldn't create role `%s`", name);
  }
  else {
    struct discord_guild_role role;
    discord_guild_role_init(&role);

    struct discord_create_guild_role_params params = { .name = name };
    if (ORCA_OK == discord_create_guild_role(client, msg->guild_id, &params, &role))
      sprintf(text, "Succesfully create <@&%"PRIu64">", role.id);
    else
      sprintf(text, "Couldn't create role `%s`", name);

    discord_guild_role_cleanup(&role);
  }

  struct discord_create_message_params params = { .content = text };
  discord_create_message(client, msg->channel_id, &params, NULL);
}

void on_role_delete(
  struct discord *client,
  const struct discord_user *bot,
  const struct discord_message *msg)
{
  if (msg->author->bot) return;

  u64_snowflake_t role_id=0;
  sscanf(msg->content, "%"SCNu64, &role_id);

  char text[MAX_MESSAGE_LEN];
  if (!role_id) {
    sprintf(text, "Invalid format for `guild.role_delete <role_id>`");
  }
  else {
    if (ORCA_OK == discord_delete_guild_role(client, msg->guild_id, role_id))
      sprintf(text, "Succesfully delete role");
    else
      sprintf(text, "Couldn't delete <@&%"PRIu64">", role_id);
  }

  struct discord_create_message_params params = { .content = text };
  discord_create_message(client, msg->channel_id, &params, NULL);
}

void on_role_member_add(
  struct discord *client,
  const struct discord_user *bot,
  const struct discord_message *msg)
{
  if (msg->author->bot) return;

  u64_snowflake_t user_id=0, role_id=0;
  sscanf(msg->content, "%"SCNu64" %"SCNu64, &user_id, &role_id);

  char text[MAX_MESSAGE_LEN];
  if (!user_id || !role_id) {
    sprintf(text, "Invalid format for `guild.role_member_add <user_id> <role_id>`");
  }
  else {
    if (ORCA_OK == discord_add_guild_member_role(client, msg->guild_id, user_id, role_id))
      sprintf(text, "Assigned role <@&%"PRIu64"> to <@%"PRIu64">", role_id, user_id);
    else
      sprintf(text, "Couldn't assign role <@&%"PRIu64"> to <@%"PRIu64">", role_id, user_id);
  }

  struct discord_create_message_params params = { .content = text };
  discord_create_message(client, msg->channel_id, &params, NULL);
}

void on_role_member_remove(
  struct discord *client,
  const struct discord_user *bot,
  const struct discord_message *msg)
{
  if (msg->author->bot) return;

  u64_snowflake_t user_id=0, role_id=0;
  sscanf(msg->content, "%"SCNu64" %"SCNu64, &user_id, &role_id);

  char text[MAX_MESSAGE_LEN];
  if (!user_id || !role_id) {
    sprintf(text, "Invalid format for `guild.role_member_remove <user_id> <role_id>`");
  }
  else {
    if (ORCA_OK == discord_remove_guild_member_role(client, msg->guild_id, user_id, role_id))
      sprintf(text, "Removed role <@&%"PRIu64"> from <@%"PRIu64">", role_id, user_id);
    else
      sprintf(text, "Couldn't remove role <@&%"PRIu64"> from <@%"PRIu64">", role_id, user_id);
  }

  struct discord_create_message_params params = { .content = text };
  discord_create_message(client, msg->channel_id, &params, NULL);
}

void on_role_list(
  struct discord *client,
  const struct discord_user *bot,
  const struct discord_message *msg)
{
  if (msg->author->bot) return;

  NTL_T(struct discord_guild_role) roles=NULL;
  discord_get_guild_roles(client, msg->guild_id, &roles);

  char text[MAX_MESSAGE_LEN];
  if (!roles) {
    sprintf(text, "No guild roles found.");
  }
  else {
    char *cur = text;
    char *end = &text[sizeof(text)-1];
    char *prev;
    for (size_t i=0; roles[i]; ++i) {
      prev = cur;
      cur += snprintf(cur, end-cur, \
              "<@&%"PRIu64">(%"PRIu64")\n", roles[i]->id, roles[i]->id);

      if (cur >= end) { // to make sure no role is skipped
        *prev = '\0'; // end string before truncation
        cur = text; // reset
        --i; // retry current iteration

        struct discord_create_message_params params = { .content = text };
        discord_create_message(client, msg->channel_id, &params, NULL);
        continue;
      }
    }
    discord_guild_role_list_free(roles);
  }

  struct discord_create_message_params params = { .content = text };
  discord_create_message(client, msg->channel_id, &params, NULL);
}

void
on_change_nick(
  struct discord *client,
  const struct discord_user *bot,
  const struct discord_message *msg)
{
  if (msg->author->bot) return;

  u64_snowflake_t user_id=0;
  char nick[MAX_USERNAME_LEN]="";
  sscanf(msg->content, "%"SCNu64" %s", &user_id, nick);
  char text[MAX_MESSAGE_LEN];
  if (!user_id || !*nick) {
    sprintf(text, "Invalid format for `guild.change_nick <user_id> <nick>`");
  }
  else {
    struct discord_modify_guild_member_params params = { .nick = nick };
    if (ORCA_OK == discord_modify_guild_member(client, msg->guild_id, user_id, &params, NULL))
      sprintf(text, "Succesfully changed <@%"PRIu64"> nick", user_id);
    else
      sprintf(text, "Couldn't change <@%"PRIu64"> nick", user_id);
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
    config_file = "bot.config";

  discord_global_init();

  struct discord *client = discord_config_init(config_file);
  assert(NULL != client && "Couldn't initialize client");

  discord_set_on_ready(client, &on_ready);
  discord_set_on_guild_role_create(client, &on_log_role_create);
  discord_set_on_guild_role_update(client, &on_log_role_update);
  discord_set_on_guild_role_delete(client, &on_log_role_delete);

  discord_set_prefix(client, "guild.");
  discord_set_on_command(client, "create", &on_create);
  discord_set_on_command(client, "role_create", &on_role_create);
  discord_set_on_command(client, "role_delete", &on_role_delete);
  discord_set_on_command(client, "role_member_add", &on_role_member_add);
  discord_set_on_command(client, "role_member_remove", &on_role_member_remove);
  discord_set_on_command(client, "role_list", &on_role_list);
  discord_set_on_command(client, "change_nick", &on_change_nick);

  printf("\n\nThis bot demonstrates how easy it is to manipulate guild"
         " endpoints.\n"
         "1. Type 'guild.create <?name>' to create a new guild (will be deleted afterwards)\n"
         "2. Type 'guild.role_create <name>' to create a new role\n"
         "3. Type 'guild.role_delete <role_id>' to delete\n"
         "4. Type 'guild.role_member_add <user_id> <role_id>' to assign role to user\n"
         "5. Type 'guild.role_member_remove <user_id> <role_id>' to remove role from user\n"
         "6. Type 'guild.role_list' to get a list of this guild roles\n"
         "7. Type 'guild.change_nick <user_id> <nick>' to change user nick\n"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input


  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}
