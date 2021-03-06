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
create_beginner_channel(
  client *client, 
  const guild::member::dati *member,
  const u64_snowflake_t guild_id)
{
  channel::dati ch;
  channel::dati_init(&ch);

  guild::create_channel::params params = {
    .name = "welcome",
    .topic = "Questionnaire."
  };

  channel::overwrite::append(
    &params.permission_overwrites,
    guild_id, // @everyone role id is the same as guild id
    0, // role type
    0, // Don't set allow permissions
    0x40 | 0x400 | 0x800); // Deny Read and Send Messages, Add Reactions permissions

  channel::overwrite::append(
    &params.permission_overwrites,
    member->user->id,
    1, // user type
    0x40 | 0x400 | 0x800,  // Allow Read and Send Messages, Add Reactions permissions
    0); // Don't set deny permissions

  guild::create_channel::run(client, guild_id, &params, &ch);

  return ch.id;
}

void 
on_member_join(
  client *client, 
  const user::dati *me, 
  const u64_snowflake_t guild_id, 
  const guild::member::dati *member)
{
  if (member->user->bot) return; // ignore bots

  u64_snowflake_t channel_id = create_beginner_channel(client, member, guild_id);
  if (!channel_id) return; /* @todo this is not how to properly handle this */

  // Send some messages to be read by the newcomer
  char text[512];
  snprintf(text, sizeof(text), "Welcome, <@!%" PRIu64 ">!", member->user->id);
  channel::message::create::params params2 = {
    .content = text
  };
  channel::message::create::run(client, channel_id, &params2, NULL);
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

  setcb(client, GUILD_MEMBER_ADD, &on_member_join);

  printf("\n\nTHIS IS A WORK IN PROGRESS"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input

  run(client);

  cleanup(client);

  global_cleanup();
}


