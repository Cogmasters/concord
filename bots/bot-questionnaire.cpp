#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <libdiscord.h>
#include "orka-utils.h" // for orka_timestamp_ms()

using namespace discord;

void 
on_ready(client *client, const user::dati *me)
{
  fprintf(stderr, "\n\nQuestionnaire-Bot succesfully connected to Discord as %s#%s!\n\n",
      me->username, me->discriminator);

  (void)client;
}

u64_snowflake_t
create_readonly_channel(client *client, const u64_snowflake_t guild_id)
{
  channel::dati ch;
  channel::dati_init(&ch);

  guild::create_channel::params params = {
    .name = "introduction",
    .topic = "Questionnaire."
  };

  channel::overwrite::append(
    &params.permission_overwrites,
    guild_id, // @everyone role id is the same as guild id
    0, // role type
    0, // Don't set allow permissions
    0x40 | 0x400 | 0x800); // Deny Read and Send Messages, Add Reactions permissions

  guild::create_channel::run(client, guild_id, &params, &ch);

  return ch.id;
}

void 
on_create(
  client *client, 
  const user::dati *me, 
  const channel::message::dati *msg)
{
  using namespace channel;

  if (msg->author->bot) return; // ignore bots

  u64_snowflake_t channel_id = create_readonly_channel(client, msg->guild_id);
  if (!channel_id) return; /* @todo this is not how to properly handle this */

  message::create::params params = {
    .content = "React to me."
  };
  message::dati *ret_msg = message::dati_alloc();

  message::create::run(client, channel_id, &params, ret_msg);
  reaction::create(client, channel_id, ret_msg->id, 0, "😊");

  message::dati_free(ret_msg);
}

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";

  setlocale(LC_ALL, "");

  global_init();

  client *client = config_init(config_file);
  assert(NULL != client);

  set_prefix(client, "!channel");
  setcb_command(client, "Create", &on_create);

  printf("\n\nTHIS IS A WORK IN PROGRESS"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input

  run(client);

  cleanup(client);

  global_cleanup();
}


