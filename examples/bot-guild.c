#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h> /* PRIu64, SCNu64 */
#include <assert.h>

#include "discord.h"
#include "cee-utils.h" // for cee_timestamp_ms()

void on_ready(struct discord *client, const struct discord_user *bot)
{
  log_info("Guild-Bot succesfully connected to Discord as %s#%s!",
           bot->username, bot->discriminator);
}

void on_log_role_create(struct discord *client,
                        const struct discord_user *bot,
                        const u64_snowflake_t guild_id,
                        const struct discord_role *role)
{
  log_warn("Role (%" PRIu64 ") created", role->id);
}

void on_log_role_update(struct discord *client,
                        const struct discord_user *bot,
                        const u64_snowflake_t guild_id,
                        const struct discord_role *role)
{
  log_warn("Role (%" PRIu64 ") updated", role->id);
}

void on_log_role_delete(struct discord *client,
                        const struct discord_user *bot,
                        const u64_snowflake_t guild_id,
                        const u64_snowflake_t role_id)
{
  log_warn("Role (%" PRIu64 ") deleted", role_id);
}

void on_create(struct discord *client,
               const struct discord_user *bot,
               const struct discord_message *msg)
{
  if (msg->author->bot) return;

  struct discord_guild guild = { 0 };

  ORCAcode code;
  code = discord_create_guild(
    client,
    &(struct discord_create_guild_params){
      .name = *msg->content ? msg->content : "TestGuild" },
    &guild);

  char text[DISCORD_MAX_MESSAGE_LEN];
  if (ORCA_OK == code)
    sprintf(text, "%s (%" PRIu64 ") created.", guild.name, guild.id);
  else
    sprintf(text, "Couldn't create guild.");

  struct discord_create_message_params params = { .content = text };
  discord_create_message(client, msg->channel_id, &params, NULL);

  discord_guild_cleanup(&guild);
}

void on_modify(struct discord *client,
               const struct discord_user *bot,
               const struct discord_message *msg)
{
  if (msg->author->bot) return;

  u64_snowflake_t guild_id = 0;
  char guild_name[DISCORD_MAX_NAME_LEN] = "";
  sscanf(msg->content, "%" SCNu64 " %s", &guild_id, guild_name);

  char text[DISCORD_MAX_MESSAGE_LEN];
  struct discord_guild guild = { 0 };

  ORCAcode code;
  code = discord_modify_guild(
    client, guild_id,
    &(struct discord_modify_guild_params){ .name = guild_name }, &guild);

  if (ORCA_OK == code)
    sprintf(text, "Renamed guild to %s.", guild.name);
  else
    sprintf(text, "Couldn't rename guild.");

  struct discord_create_message_params params = { .content = text };
  discord_create_message(client, msg->channel_id, &params, NULL);

  discord_guild_cleanup(&guild);
}

void on_delete(struct discord *client,
               const struct discord_user *bot,
               const struct discord_message *msg)
{
  if (msg->author->bot) return;

  u64_snowflake_t guild_id = 0;
  sscanf(msg->content, "%" SCNu64, &guild_id);

  struct discord_create_message_params params = { 0 };
  if (ORCA_OK == discord_delete_guild(client, guild_id))
    params.content = "Succesfully deleted guild.";
  else
    params.content = "Couldn't delete guild.";
  discord_create_message(client, msg->channel_id, &params, NULL);
}

void on_role_create(struct discord *client,
                    const struct discord_user *bot,
                    const struct discord_message *msg)
{
  if (msg->author->bot) return;

  char name[128] = "";
  sscanf(msg->content, "%s", name);

  char text[DISCORD_MAX_MESSAGE_LEN];
  if (!*name) {
    sprintf(text, "Couldn't create role `%s`", name);
  }
  else {
    struct discord_role role = { 0 };

    struct discord_create_guild_role_params params = { .name = name };
    if (ORCA_OK ==
        discord_create_guild_role(client, msg->guild_id, &params, &role))
      sprintf(text, "Succesfully create <@&%" PRIu64 ">", role.id);
    else
      sprintf(text, "Couldn't create role `%s`", name);

    discord_role_cleanup(&role);
  }

  struct discord_create_message_params params = { .content = text };
  discord_create_message(client, msg->channel_id, &params, NULL);
}

void on_role_delete(struct discord *client,
                    const struct discord_user *bot,
                    const struct discord_message *msg)
{
  if (msg->author->bot) return;

  u64_snowflake_t role_id = 0;
  sscanf(msg->content, "%" SCNu64, &role_id);

  char text[DISCORD_MAX_MESSAGE_LEN];
  if (!role_id) {
    sprintf(text, "Invalid format for `guild.role_delete <role_id>`");
  }
  else {
    if (ORCA_OK == discord_delete_guild_role(client, msg->guild_id, role_id))
      sprintf(text, "Succesfully delete role");
    else
      sprintf(text, "Couldn't delete <@&%" PRIu64 ">", role_id);
  }

  struct discord_create_message_params params = { .content = text };
  discord_create_message(client, msg->channel_id, &params, NULL);
}

void on_role_member_add(struct discord *client,
                        const struct discord_user *bot,
                        const struct discord_message *msg)
{
  if (msg->author->bot) return;

  u64_snowflake_t user_id = 0, role_id = 0;
  sscanf(msg->content, "%" SCNu64 " %" SCNu64, &user_id, &role_id);

  char text[DISCORD_MAX_MESSAGE_LEN];
  if (!user_id || !role_id) {
    sprintf(text,
            "Invalid format for `guild.role_member_add <user_id> <role_id>`");
  }
  else {
    if (ORCA_OK ==
        discord_add_guild_member_role(client, msg->guild_id, user_id, role_id))
      sprintf(text, "Assigned role <@&%" PRIu64 "> to <@%" PRIu64 ">", role_id,
              user_id);
    else
      sprintf(text, "Couldn't assign role <@&%" PRIu64 "> to <@%" PRIu64 ">",
              role_id, user_id);
  }

  struct discord_create_message_params params = { .content = text };
  discord_create_message(client, msg->channel_id, &params, NULL);
}

void on_role_member_remove(struct discord *client,
                           const struct discord_user *bot,
                           const struct discord_message *msg)
{
  if (msg->author->bot) return;

  u64_snowflake_t user_id = 0, role_id = 0;
  sscanf(msg->content, "%" SCNu64 " %" SCNu64, &user_id, &role_id);

  char text[DISCORD_MAX_MESSAGE_LEN];
  if (!user_id || !role_id) {
    sprintf(
      text,
      "Invalid format for `guild.role_member_remove <user_id> <role_id>`");
  }
  else {
    if (ORCA_OK == discord_remove_guild_member_role(client, msg->guild_id,
                                                    user_id, role_id))
      sprintf(text, "Removed role <@&%" PRIu64 "> from <@%" PRIu64 ">",
              role_id, user_id);
    else
      sprintf(text, "Couldn't remove role <@&%" PRIu64 "> from <@%" PRIu64 ">",
              role_id, user_id);
  }

  struct discord_create_message_params params = { .content = text };
  discord_create_message(client, msg->channel_id, &params, NULL);
}

void on_role_list(struct discord *client,
                  const struct discord_user *bot,
                  const struct discord_message *msg)
{
  if (msg->author->bot) return;

  NTL_T(struct discord_role) roles = NULL;
  ORCAcode code;
  code = discord_get_guild_roles(client, msg->guild_id, &roles);

  char text[DISCORD_MAX_MESSAGE_LEN];
  if (code != ORCA_OK || !roles) {
    sprintf(text, "No guild roles found.");
  }
  else {
    char *cur = text;
    char *end = &text[sizeof(text) - 1];
    char *prev;
    for (size_t i = 0; roles[i]; ++i) {
      prev = cur;
      cur += snprintf(cur, end - cur, "<@&%" PRIu64 ">(%" PRIu64 ")\n",
                      roles[i]->id, roles[i]->id);

      if (cur >= end) { // to make sure no role is skipped
        *prev = '\0'; // end string before truncation
        cur = text; // reset
        --i; // retry current iteration

        struct discord_create_message_params params = { .content = text };
        discord_create_message(client, msg->channel_id, &params, NULL);
        continue;
      }
    }
    discord_role_list_free(roles);
  }

  struct discord_create_message_params params = { .content = text };
  discord_create_message(client, msg->channel_id, &params, NULL);
}

void on_member_get(struct discord *client,
                   const struct discord_user *bot,
                   const struct discord_message *msg)
{
  if (msg->author->bot) return;

  u64_snowflake_t user_id = 0;
  sscanf(msg->content, "%" SCNu64, &user_id);
  char text[DISCORD_MAX_MESSAGE_LEN];
  if (!user_id) {
    sprintf(text, "Invalid format for `guild.member_get <user_id>`");
  }
  else {
    struct discord_guild_member member = { 0 };

    if (ORCA_OK == discord_get_guild_member(client, msg->guild_id,
                                            msg->author->id, &member))
      sprintf(text, "Member <@%" PRIu64 "> found!", user_id);
    else
      sprintf(text, "Couldn't find member");
    discord_guild_member_cleanup(&member);
  }

  struct discord_create_message_params params = { .content = text };
  discord_create_message(client, msg->channel_id, &params, NULL);
}

void on_member_change_nick(struct discord *client,
                           const struct discord_user *bot,
                           const struct discord_message *msg)
{
  if (msg->author->bot) return;

  u64_snowflake_t user_id = 0;
  char nick[DISCORD_MAX_USERNAME_LEN] = "";
  sscanf(msg->content, "%" SCNu64 " %s", &user_id, nick);
  char text[DISCORD_MAX_MESSAGE_LEN];
  if (!user_id || !*nick) {
    sprintf(text,
            "Invalid format for `guild.member_change_nick <user_id> <nick>`");
  }
  else {
    struct discord_modify_guild_member_params params = { .nick = nick };
    if (ORCA_OK == discord_modify_guild_member(client, msg->guild_id, user_id,
                                               &params, NULL))
      sprintf(text, "Succesfully changed <@%" PRIu64 "> nick", user_id);
    else
      sprintf(text, "Couldn't change <@%" PRIu64 "> nick", user_id);
  }

  struct discord_create_message_params params = { .content = text };
  discord_create_message(client, msg->channel_id, &params, NULL);
}

void on_member_search(struct discord *client,
                      const struct discord_user *bot,
                      const struct discord_message *msg)
{
  if (msg->author->bot) return;

  NTL_T(struct discord_guild_member) members = NULL;
  ORCAcode code;
  code = discord_search_guild_members(
    client, msg->guild_id,
    &(struct discord_search_guild_members_params){ .query = msg->content },
    &members);

  char text[DISCORD_MAX_MESSAGE_LEN];
  if (ORCA_OK != code || !members) {
    sprintf(text, "No members matching '%s' found.", msg->content);
  }
  else {
    char *cur = text;
    char *end = &text[sizeof(text) - 1];
    char *prev;
    for (size_t i = 0; members[i]; ++i) {
      prev = cur;
      cur +=
        snprintf(cur, end - cur, "<@!%" PRIu64 ">\n", members[i]->user->id);

      if (cur >= end) { // to make sure no member is skipped
        *prev = '\0'; // end string before truncation
        // reset for retry
        cur = text;
        --i;

        struct discord_create_message_params params = { .content = text };
        discord_create_message(client, msg->channel_id, &params, NULL);
        continue;
      }
    }
    discord_guild_member_list_free(members);
  }
  struct discord_create_message_params params = { .content = text };
  discord_create_message(client, msg->channel_id, &params, NULL);
}

void on_bot_change_nick(struct discord *client,
                        const struct discord_user *bot,
                        const struct discord_message *msg)
{
  if (msg->author->bot) return;

  char text[DISCORD_MAX_MESSAGE_LEN];
  if (!*msg->content) {
    sprintf(text, "Invalid format for `guild.bot_change_nick <nick>`");
  }
  else {
    struct discord_modify_current_member_params params = { .nick =
                                                             msg->content };
    if (ORCA_OK ==
        discord_modify_current_member(client, msg->guild_id, &params, NULL))
      sprintf(text, "Succesfully changed <@%" PRIu64 "> nick", bot->id);
    else
      sprintf(text, "Couldn't change <@%" PRIu64 "> nick", bot->id);
  }

  struct discord_create_message_params params = { .content = text };
  discord_create_message(client, msg->channel_id, &params, NULL);
}

void on_bot_get_welcome_screen(struct discord *client,
                               const struct discord_user *bot,
                               const struct discord_message *msg)
{
  if (msg->author->bot) return;

  struct discord_welcome_screen screen = { 0 };
  char text[DISCORD_MAX_MESSAGE_LEN];

  if (!*msg->content) {
    sprintf(text, "Invalid format for `guild.welcome_screen <guild_id>`");
    return;
  }

  ORCAcode response = discord_get_guild_welcome_screen(
    client, strtoul(msg->content, NULL, 10), &screen);

  if (response != ORCA_OK) {
    sprintf(text, "Could not fetch welcome screen from guild %s.",
            msg->content);
  }
  else {
    sprintf(text, "%s\n", screen.description);
  }

  struct discord_create_message_params params = { .content = text };
  discord_create_message(client, msg->channel_id, &params, NULL);
  discord_welcome_screen_cleanup(&screen);
}
void on_bot_get_invites(struct discord *client,
                        const struct discord_user *bot,
                        const struct discord_message *msg)
{
  if (msg->author->bot) return;

  char text[DISCORD_MAX_MESSAGE_LEN] = { 0 };
  struct discord_invite **invites = { 0 };

  if (!*msg->content) {
    sprintf(text, "Invalid format for `guild.invites <guild_id>`");
    return;
  }

  ORCAcode response = discord_get_guild_invites(
    client, strtoul(msg->content, NULL, 10), &invites);

  if (response != ORCA_OK) {
    sprintf(text, "Could not fetch invites from guild %s.", msg->content);
  }
  else {
    int index;

    sprintf(text, "%s", "Active invites in this server:\n");

    for (index = 0; invites && invites[index] != NULL; index++) {
      sprintf(text, "%s\n", invites[0][index].code);
    }
  }

  struct discord_create_message_params params = { .content = text };
  discord_create_message(client, msg->channel_id, &params, NULL);
  discord_invite_list_free(invites);
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
  discord_set_on_guild_role_create(client, &on_log_role_create);
  discord_set_on_guild_role_update(client, &on_log_role_update);
  discord_set_on_guild_role_delete(client, &on_log_role_delete);

  discord_set_prefix(client, "guild.");
  discord_set_on_command(client, "create", &on_create);
  discord_set_on_command(client, "modify", &on_modify);
  discord_set_on_command(client, "delete", &on_delete);
  discord_set_on_command(client, "role_create", &on_role_create);
  discord_set_on_command(client, "role_delete", &on_role_delete);
  discord_set_on_command(client, "role_member_add", &on_role_member_add);
  discord_set_on_command(client, "role_member_remove", &on_role_member_remove);
  discord_set_on_command(client, "role_list", &on_role_list);
  discord_set_on_command(client, "member_get", &on_member_get);
  discord_set_on_command(client, "member_change_nick", &on_member_change_nick);
  discord_set_on_command(client, "member_search", &on_member_search);
  discord_set_on_command(client, "bot_change_nick", &on_bot_change_nick);
  discord_set_on_command(client, "welcome_screen", &on_bot_get_welcome_screen);
  discord_set_on_command(client, "invites", &on_bot_get_invites);

  printf("\n\nThis bot demonstrates how easy it is to manipulate guild"
         " endpoints.\n"
         "1. Type 'guild.create <?name>' to create a new guild\n"
         "2. Type 'guild.modify <guild_id> <name>' to rename a guild\n"
         "3. Type 'guild.delete <guild_id>' to delete guild\n"
         "4. Type 'guild.role_create <name>' to create a new role\n"
         "5. Type 'guild.role_delete <role_id>' to delete\n"
         "6. Type 'guild.role_member_add <user_id> <role_id>' to assign role "
         "to user\n"
         "7. Type 'guild.role_member_remove <user_id> <role_id>' to remove "
         "role from user\n"
         "8. Type 'guild.role_list' to get a list of this guild roles\n"
         "10. Type 'guild.member_get <id>' to fetch a member by his ID\n"
         "11. Type 'guild.member_change_nick <user_id> <nick>' to change "
         "member nick\n"
         "12. Type 'guild.member_search <nick>' to search for members "
         "matching a nick\n"
         "13. Type 'guild.bot_change_nick <nick>' to change bot nick\n"
         "14. Type 'guild.welcome_screen' <guild_id> to get the welcome "
         "screen of a guild\n"
         "15. Type 'guild.invites' <guild_id> to get the active invites of a "
         "guild\n"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input

  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}
