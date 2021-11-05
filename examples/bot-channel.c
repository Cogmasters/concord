#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h> /* PRIu64 */
#include <assert.h>

#include "discord.h"

void on_ready(struct discord *client, const struct discord_user *bot)
{
  log_info("Channel-Bot succesfully connected to Discord as %s#%s!",
           bot->username, bot->discriminator);
}

void log_on_channel_create(struct discord *client,
                           const struct discord_user *bot,
                           const struct discord_channel *channel)
{
  log_info("Channel %s (%" PRIu64 ") created", channel->name, channel->id);
}

void log_on_channel_update(struct discord *client,
                           const struct discord_user *bot,
                           const struct discord_channel *channel)
{
  log_info("Channel %s (%" PRIu64 ") updated", channel->name, channel->id);
}

void log_on_channel_delete(struct discord *client,
                           const struct discord_user *bot,
                           const struct discord_channel *channel)
{
  log_info("Channel %s (%" PRIu64 ") deleted", channel->name, channel->id);
}

void log_on_thread_create(struct discord *client,
                          const struct discord_user *bot,
                          const struct discord_channel *thread)
{
  log_info("Thread %s (%" PRIu64 ") created", thread->name, thread->id);
}

void log_on_thread_update(struct discord *client,
                          const struct discord_user *bot,
                          const struct discord_channel *thread)
{
  log_info("Thread %s (%" PRIu64 ") updated", thread->name, thread->id);
}

void log_on_thread_delete(struct discord *client,
                          const struct discord_user *bot,
                          const struct discord_channel *thread)
{
  log_info("Thread %s (%" PRIu64 ") deleted", thread->name, thread->id);
}

void on_channel_create(struct discord *client,
                       const struct discord_user *bot,
                       const struct discord_message *msg)
{
  if (msg->author->bot) return;

  struct discord_create_guild_channel_params params = { .name = msg->content };
  discord_create_guild_channel(client, msg->guild_id, &params, NULL);
}

void on_channel_rename_this(struct discord *client,
                            const struct discord_user *bot,
                            const struct discord_message *msg)
{
  if (msg->author->bot) return;

  struct discord_modify_channel_params params = { .name = msg->content };
  discord_modify_channel(client, msg->channel_id, &params, NULL);
}

void on_channel_delete_this(struct discord *client,
                            const struct discord_user *bot,
                            const struct discord_message *msg)
{
  if (msg->author->bot) return;

  discord_delete_channel(client, msg->channel_id, NULL);
}

void on_channel_get_invites(struct discord *client,
                            const struct discord_user *bot,
                            const struct discord_message *msg)
{
  if (msg->author->bot) return;

  NTL_T(struct discord_invite) invites = NULL;

  ORCAcode code;
  code = discord_get_channel_invites(client, msg->channel_id, &invites);
  if (code != ORCA_OK || !invites) {
    log_info("Couldn't fetch invites");
    return;
  }

  char text[DISCORD_MAX_MESSAGE_LEN];
  snprintf(text, sizeof(text), "%zu invite links created.",
           ntl_length((ntl_t)invites));
  struct discord_create_message_params params = { .content = text };
  discord_create_message(client, msg->channel_id, &params, NULL);

  discord_invite_list_free(invites);
}

void on_channel_create_invite(struct discord *client,
                              const struct discord_user *bot,
                              const struct discord_message *msg)
{
  if (msg->author->bot) return;

  struct discord_invite invite = { 0 };

  char text[DISCORD_MAX_MESSAGE_LEN];
  if (ORCA_OK ==
      discord_create_channel_invite(client, msg->channel_id, NULL, &invite))
    sprintf(text, "https://discord.gg/%s", invite.code);
  else
    sprintf(text, "Couldn't create invite.");

  struct discord_create_message_params params = { .content = text };
  discord_create_message(client, msg->channel_id, &params, NULL);

  discord_invite_cleanup(&invite);
}

void on_channel_start_thread(struct discord *client,
                             const struct discord_user *bot,
                             const struct discord_message *msg)
{
  if (msg->author->bot) return;

  struct discord_channel channel = { 0 };

  char text[DISCORD_MAX_MESSAGE_LEN];
  ORCAcode code;
  if (msg->message_reference) {
    code = discord_start_thread_with_message(
      client, msg->channel_id, msg->message_reference->message_id,
      &(struct discord_start_thread_with_message_params){ .name =
                                                            "new_thread" },
      &channel);
  }
  else {
    code = discord_start_thread_without_message(
      client, msg->channel_id,
      &(struct discord_start_thread_without_message_params){
        .name = "new_thread", .type = DISCORD_CHANNEL_GUILD_PUBLIC_THREAD },
      &channel);
  }

  if (ORCA_OK == code)
    sprintf(text, "Created thread-channel <#%" PRIu64 ">", channel.id);
  else
    sprintf(text, "Couldn't create channel.");

  struct discord_create_message_params params = { .content = text };
  discord_create_message(client, msg->channel_id, &params, NULL);

  discord_channel_cleanup(&channel);
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
  discord_set_on_channel_create(client, &log_on_channel_create);
  discord_set_on_channel_update(client, &log_on_channel_update);
  discord_set_on_channel_delete(client, &log_on_channel_delete);
  discord_set_on_thread_create(client, &log_on_thread_create);
  discord_set_on_thread_update(client, &log_on_thread_update);
  discord_set_on_thread_delete(client, &log_on_thread_delete);

  discord_set_prefix(client, "channel.");
  discord_set_on_command(client, "create", &on_channel_create);
  discord_set_on_command(client, "rename_this", &on_channel_rename_this);
  discord_set_on_command(client, "delete_this", &on_channel_delete_this);
  discord_set_on_command(client, "get_invites", &on_channel_get_invites);
  discord_set_on_command(client, "create_invite", &on_channel_create_invite);
  discord_set_on_command(client, "start_thread", &on_channel_start_thread);

  printf("\n\n(USE WITH CAUTION) This bot demonstrates how easy it is to "
         "create/delete channels\n"
         "1. Type 'channel.create <channel_name>' anywhere to create a new "
         "channel\n"
         "2. Type 'channel.rename_this <channel_name>' to rename the current "
         "channel\n"
         "3. Type 'channel.delete_this' to delete the current channel\n"
         "4. Type 'channel.get_invites' to check how many have been created\n"
         "5. Type 'channel.create_invite' to create a new invite\n"
         "6. Type 'channel.start_thread' to start a new thread (reply to a "
         "message if you wish start a thread under it)\n"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input

  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}
