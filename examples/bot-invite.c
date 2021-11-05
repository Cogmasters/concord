#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h> /* PRIu64 */
#include <assert.h>

#include "discord.h"

void on_ready(struct discord *client, const struct discord_user *bot)
{
  log_info("Invite-Bot succesfully connected to Discord as %s#%s!",
           bot->username, bot->discriminator);
}

void on_invite_get(struct discord *client,
                   const struct discord_user *bot,
                   const struct discord_message *msg)
{
  if (msg->author->bot) return;

  struct discord_invite invite = { 0 };

  ORCAcode code;
  code = discord_get_invite(client, msg->content,
                            &(struct discord_get_invite_params){
                              .with_counts = true, .with_expiration = true },
                            &invite);

  char text[DISCORD_MAX_MESSAGE_LEN];
  if (ORCA_OK == code)
    sprintf(text, "https://discord.gg/%s", invite.code);
  else
    sprintf(text, "Couldn't get invite.");

  struct discord_create_message_params params = { .content = text };
  discord_create_message(client, msg->channel_id, &params, NULL);

  discord_invite_cleanup(&invite);
}

void on_invite_delete(struct discord *client,
                      const struct discord_user *bot,
                      const struct discord_message *msg)
{
  if (msg->author->bot) return;

  struct discord_create_message_params params = { 0 };
  if (ORCA_OK == discord_delete_invite(client, msg->content, NULL))
    params.content = "Succesfully deleted invite.";
  else
    params.content = "Couldn't delete invite";

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

  discord_set_prefix(client, "invite.");
  discord_set_on_command(client, "get", &on_invite_get);
  discord_set_on_command(client, "delete", &on_invite_delete);

  printf("\n\nThis bot demonstrates how easy it is to fetch/delete invites\n"
         "1. Type 'invite.get <invite_code>' to get a invite object from its "
         "particular code\n"
         "2. Type 'invite.delete <invite_code>' to delete a invite object by "
         "its particular code\n"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input

  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}
