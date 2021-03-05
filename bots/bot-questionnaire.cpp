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
create_beginner_role(
  client *client, 
  const guild::member::dati *member,
  const u64_snowflake_t guild_id)
{
  role::dati rl;
  role::dati_init(&rl);

  guild::create_role::params params = {
    .name = "beginner"
  };
  guild::create_role::run(client, guild_id, &params, &rl);

  return rl.id;
}

u64_snowflake_t
create_beginner_channel(
  client *client, 
  const guild::member::dati *member,
  const u64_snowflake_t guild_id,
  const u64_snowflake_t role_id)
{
  channel::dati ch;
  channel::dati_init(&ch);

  guild::create_channel::params params = {
    .name = "welcome",
    .topic = "Questionnaire."
  };
  channel::overwrite::append(
    &params.permission_overwrites,
    role_id,
    0, // role type
    0x40 | 0x400 | 0x800,  // Read and Send Messages, Add Reactions
    0);

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

  u64_snowflake_t role_id = create_beginner_role(client, member, guild_id);
  if (!role_id) return; /* @todo this is not how to properly handle this */

  u64_snowflake_t channel_id = create_beginner_channel(client, member, guild_id, role_id);
  if (!channel_id) return; /* @todo this is not how to properly handle this */

  // Assign newly created role to new user
  guild::modify_member::params params1 = {0};
  ja_u64_list_append(&params1.roles, &role_id);
  guild::modify_member::run(client, guild_id, member->user->id, &params1, NULL);

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


