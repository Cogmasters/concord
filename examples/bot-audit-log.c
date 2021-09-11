#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <limits.h>
#include <string.h>
#include <assert.h>
#include <locale.h>

#include "discord.h"


void on_ready(struct discord *client, const struct discord_user *bot) {
  log_info("Audit-Log-Bot succesfully connected to Discord as %s#%s!", bot->username, bot->discriminator);
}

void on_log_guild_member_add(
  struct discord *client,
  const struct discord_user *bot,
  const uint64_t guild_id, 
  const struct discord_guild_member *member)
{
  log_info("%s#%s joined guild %"PRIu64, member->user->username, member->user->discriminator, guild_id);
}

void on_log_guild_member_update(
  struct discord *client,
  const struct discord_user *bot,
  const uint64_t guild_id, 
  const struct discord_guild_member *member)
{
  char nick[128]="";
  if (member->nick && *member->nick)
    snprintf(nick, sizeof(nick), " (%s)", member->nick);
  log_info("%s#%s%s updated (guild %"PRIu64")", member->user->username, member->user->discriminator, nick, guild_id);
}

void on_log_guild_member_remove(
  struct discord *client,
  const struct discord_user *bot,
  const uint64_t guild_id, 
  const struct discord_user *user)
{
  log_info("%s#%s left guild %"PRIu64, user->username, user->discriminator, guild_id);
}

void on_get_my_audit_log(
    struct discord *client,
    const struct discord_user *bot,
    const struct discord_message *msg)
{
  if (msg->author->bot) return;

  int event=0;
  if (*msg->content) {
    sscanf(msg->content, "%d", &event);
  }

  struct discord_audit_log audit_log={0};
  {
    struct discord_get_guild_audit_log_params params = {
      .user_id = msg->author->id,
      .action_type = (enum discord_audit_log_events)event
    };
    if (discord_get_guild_audit_log(client, msg->guild_id, &params, &audit_log)) {
      log_error("Couldn't retrieve audit log");
      return;
    }
  }

  char audit_json[4096];
  size_t size = discord_audit_log_to_json(audit_json, sizeof(audit_json), &audit_log);

  struct discord_create_message_params params;
  if (size) {
    params = (struct discord_create_message_params){
      .file = &(struct discord_file){
        .name = "audit.json",
        .content = audit_json,
        .size = size
      }
    };
  }
  else {
    params = (struct discord_create_message_params){
      .content = "Couldn't retrieve any results."
    };
  }
  discord_create_message(client, msg->channel_id, &params, NULL);

  discord_audit_log_cleanup(&audit_log);
}

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "../config.json";

  setlocale(LC_ALL, "");

  discord_global_init();

  struct discord *client = discord_config_init(config_file);
  assert(NULL != client && "Couldn't initialize client");

  discord_add_intents(client, 32767); // subscribe to all events
  discord_set_on_ready(client, &on_ready);
  discord_set_on_guild_member_add(client, &on_log_guild_member_add);
  discord_set_on_guild_member_update(client, &on_log_guild_member_update);
  discord_set_on_guild_member_remove(client, &on_log_guild_member_remove);

  discord_set_on_command(client, "!my_audit", &on_get_my_audit_log);

  printf("\n\nThis bot demonstrates how easy it is to log"
         " for certain events.\n"
         "1. Type '!my_audit <event_value>' to check your most recent audit from event\n"
         "\tsee: https://discord.com/developers/docs/resources/audit-log#audit-log-entry-object-audit-log-events\n"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input

  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}
