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
    "\tGet Global Commands : GET\n"
    "\tCreate Global Command : CREATE <cmd_name>[<cmd_desc>]\n\n"
    "PRESS ENTER TO CONTINUE");
  fgetc(stdin); // wait for input
}

void on_ready(struct discord *client, const struct discord_user *bot) {
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

void* read_input(void *p_client)
{
  pthread_detach(pthread_self());
  struct discord *client = p_client;

  char buf[DISCORD_MAX_MESSAGE_LEN];

  char cmd_action[9 + 1], cmd_name[32 + 1], cmd_desc[100 + 1];
  while (1) 
  {
    memset(buf, 0, sizeof(buf));
    fgets(buf, sizeof(buf), stdin);
    if (!*buf) continue; // is empty
    
    memset(cmd_action, 0, sizeof(cmd_action));
    memset(cmd_name, 0, sizeof(cmd_name));
    memset(cmd_desc, 0, sizeof(cmd_desc));

    // create|update|delete <cmd_name>[<cmd_desc>]
    sscanf(buf, "%9s %32[^[][%100[^]]]", cmd_action, cmd_name, cmd_desc);

    if (!*cmd_action || 0 == strcasecmp(cmd_action, "HELP")) 
      goto _help;

    if (0 == strcasecmp(cmd_action, "GET")) {
      if (!*cmd_name) {
        NTL_T(struct discord_application_command) app_cmds = NULL;
        ORCAcode code = discord_get_global_application_commands(client, g_application_id, &app_cmds);
        if (ORCA_OK == code && app_cmds) {
          char list[4096]=""; // should be big enough ?
          size_t len=0;
          for (int i=0; app_cmds[i]; ++i) {
            len += snprintf(list+len, sizeof(list)-len, "\t%d:\t%s\n", i, app_cmds[i]->name);
          }
          log_info("\nCommands: \n%.*s", (int)len, list);
          discord_application_command_list_free(app_cmds);
        }
      }
    }
    else if (0 == strcasecmp(cmd_action, "CREATE"))
    {
      if (!*cmd_name || !*cmd_desc) goto _help;

      struct discord_application_command app_cmd={0};
      struct discord_create_global_application_command_params params = {
        .name = cmd_name,
        .description = cmd_desc,
        .default_permission = true,
        .type = 1
      };
      ORCAcode code = discord_create_global_application_command(client, g_application_id, &params, &app_cmd);
      if (ORCA_OK == code && app_cmd.id) {
        log_info("Created command:\t%s", app_cmd.name);
        discord_application_command_cleanup(&app_cmd);
      }
      else {
        log_error("Couldn't create command '%s'", cmd_name);
      }
    }
    else if (0 == strcasecmp(cmd_action, "UPDATE")) {
      if (!*cmd_name || !*cmd_desc) goto _help;
    }
    else if (0 == strcasecmp(cmd_action, "DELETE")) {
      if (!*cmd_name || !*cmd_desc) goto _help;
    }
    else {
      goto _help;
    }

    continue;

_help:
    print_usage();
    continue;
  }

  pthread_exit(NULL);
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
  assert(NULL != client && "Could not initialize client");

  discord_set_on_ready(client, &on_ready);
  discord_set_on_application_command_create(client, &log_on_application_command_create);
  discord_set_on_application_command_update(client, &log_on_application_command_update);
  discord_set_on_application_command_delete(client, &log_on_application_command_delete);

  printf("\n\nThis bot demonstrates how easy it is to create/update/delete application commands\n"
         "1. Input a valid application id from https://discord.com/developers/applications\n"
         "2. Create a command ex: \"CREATE kill[This command will kill the process]\""
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input

  printf("Please input a valid application id: ");
  scanf("%"SCNu64"%*[^\n]", &g_application_id);
  scanf("%*c"); // eat-up newline

  pthread_t tid;
  pthread_create(&tid, NULL, &read_input, client);

  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}
