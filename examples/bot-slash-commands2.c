#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <inttypes.h> /* SCNu64 */
#include <pthread.h>
#include <assert.h>

#include "discord.h"

u64_snowflake_t g_application_id;

void print_usage(void)
{
  log_info(
    "\nUsage :\n"
    "\tPrint Usage : HELP\n"
    "\tList Commands : LIST <?guild_id>\n"
    "\tCreate Command : CREATE <cmd_name>[<cmd_desc>] <?guild_id>\n"
    "\tUpdate Command : UPDATE <cmd_id> <cmd_name>[<cmd_desc>] <?guild_id>\n"
    "\tDelete Command : DELETE <cmd_id> <?guild_id>\n");
}

void on_ready(struct discord *client, const struct discord_user *bot)
{
  log_info("Slash-Commands-Bot succesfully connected to Discord as %s#%s!",
           bot->username, bot->discriminator);
}

void log_on_application_command_create(
  struct discord *client,
  const struct discord_user *bot,
  const struct discord_application_command *cmd)
{
  log_info("Application Command %s created", cmd->name);
}

void log_on_application_command_update(
  struct discord *client,
  const struct discord_user *bot,
  const struct discord_application_command *cmd)
{
  log_info("Application Command %s updated", cmd->name);
}

void log_on_application_command_delete(
  struct discord *client,
  const struct discord_user *bot,
  const struct discord_application_command *cmd)
{
  log_info("Application Command %s deleted", cmd->name);
}

void on_interaction_create(struct discord *client,
                           const struct discord_user *bot,
                           const struct discord_interaction *interaction)
{
  log_info("Interaction %" PRIu64 " received", interaction->id);

  struct discord_interaction_response params = {
    .type = DISCORD_INTERACTION_CALLBACK_CHANNEL_MESSAGE_WITH_SOURCE, // 4
    .data =
      &(struct discord_interaction_callback_data){
        .content = "Hello World!",
        .flags = DISCORD_INTERACTION_CALLBACK_DATA_EPHEMERAL // 1 << 6
      }
  };

  ORCAcode code;
  code = discord_create_interaction_response(
    client, interaction->id, interaction->token, &params, NULL);
  if (code) {
    log_error("%s", discord_strerror(code, client));
  }
}

void *read_input(void *p_client)
{
  pthread_detach(pthread_self());
  struct discord *client = p_client;

  char buf[DISCORD_MAX_MESSAGE_LEN];
  ptrdiff_t bufoffset;

  char cmd_action[9 + 1];

  ORCAcode code;
  while (1) {
    memset(buf, 0, sizeof(buf));

    fgets(buf, sizeof(buf), stdin);
    if (!*buf) continue; // is empty

    memset(cmd_action, 0, sizeof(cmd_action));
    sscanf(buf, "%s", cmd_action);
    bufoffset = strlen(cmd_action) + 1;

    if (!*cmd_action || 0 == strcasecmp(cmd_action, "HELP")) goto _help;

    if (0 == strcasecmp(cmd_action, "LIST")) {
      u64_snowflake_t guild_id = 0;
      sscanf(buf + bufoffset, "%" SCNu64, &guild_id);

      NTL_T(struct discord_application_command) app_cmds = NULL;
      if (guild_id)
        code = discord_get_guild_application_commands(client, g_application_id,
                                                      guild_id, &app_cmds);
      else
        code = discord_get_global_application_commands(
          client, g_application_id, &app_cmds);

      if (ORCA_OK == code && app_cmds) {
        char list[4096] = ""; // should be large enough ?
        size_t len = 0;
        for (int i = 0; app_cmds[i]; ++i) {
          len += snprintf(list + len, sizeof(list) - len,
                          "\t%d:\t%s (%" PRIu64 ")\n", i, app_cmds[i]->name,
                          app_cmds[i]->id);
        }
        log_info("\nCommands: \n%.*s", (int)len, list);
        discord_application_command_list_free(app_cmds);
      }
      else {
        log_error("Couldn't list commands");
      }
    }
    else if (0 == strcasecmp(cmd_action, "CREATE")) {
      char cmd_name[32 + 1] = "", cmd_desc[100 + 1] = "";
      u64_snowflake_t guild_id = 0;
      sscanf(buf + bufoffset, "%32[^[][%100[^]]] %" SCNu64, cmd_name, cmd_desc,
             &guild_id);
      if (!*cmd_name || !*cmd_desc) goto _help;

      struct discord_application_command app_cmd = { 0 };
      if (guild_id) {
        code = discord_create_guild_application_command(
          client, g_application_id, guild_id,
          &(struct discord_create_guild_application_command_params){
            .name = cmd_name,
            .description = cmd_desc,
            .default_permission = true,
            .type = 1 },
          &app_cmd);
      }
      else {
        code = discord_create_global_application_command(
          client, g_application_id,
          &(struct discord_create_global_application_command_params){
            .name = cmd_name,
            .description = cmd_desc,
            .default_permission = true,
            .type = 1 },
          &app_cmd);
      }

      if (ORCA_OK == code && app_cmd.id) {
        log_info("Created command:\t%s (" PRIu64 ")", app_cmd.name,
                 app_cmd.id);
        discord_application_command_cleanup(&app_cmd);
      }
      else {
        log_error("Couldn't create command '%s'", cmd_name);
      }
    }
    else if (0 == strcasecmp(cmd_action, "UPDATE")) {
      char cmd_name[32 + 1] = "", cmd_desc[100 + 1] = "";
      u64_snowflake_t command_id = 0, guild_id = 0;
      sscanf(buf + bufoffset, "%" SCNu64 " %32[^[][%100[^]]] %" SCNu64,
             &command_id, cmd_name, cmd_desc, &guild_id);
      if (!command_id) goto _help;

      struct discord_application_command app_cmd = { 0 };
      if (guild_id) {
        code = discord_edit_guild_application_command(
          client, g_application_id, guild_id, command_id,
          &(struct discord_edit_guild_application_command_params){
            .name = *cmd_name ? cmd_name : NULL,
            .description = *cmd_desc ? cmd_desc : NULL,
            .default_permission = true },
          &app_cmd);
      }
      else {
        code = discord_edit_global_application_command(
          client, g_application_id, command_id,
          &(struct discord_edit_global_application_command_params){
            .name = *cmd_name ? cmd_name : NULL,
            .description = *cmd_desc ? cmd_desc : NULL,
            .default_permission = true },
          &app_cmd);
      }

      if (ORCA_OK == code && app_cmd.id) {
        log_info("Edited command:\t%s (%" PRIu64 ")", app_cmd.name,
                 app_cmd.id);
        discord_application_command_cleanup(&app_cmd);
      }
      else {
        log_error("Couldn't create command '%s'", cmd_name);
      }
    }
    else if (0 == strcasecmp(cmd_action, "DELETE")) {
    }
    else {
      goto _help;
    }

    continue;
  _help:
    print_usage();
  }

  pthread_exit(NULL);
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
  discord_set_on_application_command_create(
    client, &log_on_application_command_create);
  discord_set_on_application_command_update(
    client, &log_on_application_command_update);
  discord_set_on_application_command_delete(
    client, &log_on_application_command_delete);
  discord_set_on_interaction_create(client, &on_interaction_create);

  printf("\n\nThis bot demonstrates how easy it is to create/update/delete "
         "application commands\n"
         "1. Input a valid application id from "
         "https://discord.com/developers/applications\n"
         "2. Type HELP to see commands\n"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input

  printf("Please input a valid application id: ");
  scanf("%" SCNu64 "%*[^\n]", &g_application_id);
  scanf("%*c"); // eat-up newline

  pthread_t tid;
  pthread_create(&tid, NULL, &read_input, client);

  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}
