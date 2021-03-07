#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <libdiscord.h>
#include "orka-utils.h" // for orka_timestamp_ms()

using namespace discord;

struct session_config {
  char *chat_name;
  char *chat_topic;
  u64_snowflake_t channel_id;
  u64_snowflake_t message_id;
  char *reaction_emoji;
} g_session;

void 
on_ready(client *client, const user::dati *me)
{
  fprintf(stderr, "\n\nQuiz-Bot succesfully connected to Discord as %s#%s!\n\n",
      me->username, me->discriminator);

  (void)client;
}

void
parse_session_config()
{
  size_t len;
  char *json_payload = orka_load_whole_file("bot-quiz.json", &len);
  json_extract(json_payload, len,
    "(new_channel.name):?s"
    "(new_channel.topic):?s"
    "(listener.channel_id):s_as_u64"
    "(listener.message_id):s_as_u64"
    "(listener.reaction_emoji):?s",
    &g_session.chat_name,
    &g_session.chat_topic,
    &g_session.channel_id,
    &g_session.message_id,
    &g_session.reaction_emoji);
}

void
close_existing_sessions(
  client *client, 
  const u64_snowflake_t guild_id,
  const guild::member::dati *member)
{
  /* Check if user already has a session role assigned to */
  guild::role::dati **rls = guild::role::get_list(client, guild_id);

  for (size_t i=0; rls[i]; ++i) {
    if ( strncmp("TMP", rls[i]->name, 3) )
      continue;

    u64_snowflake_t channel_id, user_id;
    sscanf(rls[i]->name, "TMP%" PRIu64 "_%" PRIu64 , &user_id, &channel_id);

    if (member->user->id == user_id) {
      channel::del(client, channel_id, NULL);
      guild::role::del(client, guild_id, rls[i]->id);
    }
  }

  guild::role::dati_list_free(rls);
}

u64_snowflake_t
create_session_channel(
  client *client, 
  const u64_snowflake_t guild_id,
  const guild::member::dati *member)
{
  channel::dati ch;
  channel::dati_init(&ch);

  guild::create_channel::params params1 = {
    .name = g_session.chat_name,
    .topic = g_session.chat_topic
  };

  channel::overwrite::append(
    &params1.permission_overwrites,
    guild_id, // @everyone role id is the same as guild id
    0, // role type
    0, // Don't set allow permissions
    0x40 | 0x400 | 0x800); // Deny Read and Send Messages, Add Reactions permissions

  channel::overwrite::append(
    &params1.permission_overwrites,
    member->user->id,
    1, // user type
    0x40 | 0x400 | 0x800, // Allow Read and Send Messages, Add Reactions permissions
    0); // Don't set deny permissions

  guild::create_channel::run(client, guild_id, &params1, &ch);

  return ch.id;
}

u64_snowflake_t
add_session_role(
  client *client, 
  const u64_snowflake_t guild_id, 
  const u64_snowflake_t channel_id,
  const guild::member::dati *member)
{
  char text[64];
  snprintf(text, sizeof(text), \
    "TMP%" PRIu64 "_%" PRIu64, member->user->id, channel_id);

  guild::role::dati ret_role;
  guild::role::dati_init(&ret_role);
  guild::role::create::params params2 = {
    .name = text
  };
  guild::role::create::run(client, guild_id, &params2, &ret_role);
  if (!ret_role.id) return 0;

  //@todo turn this into a public function
  ja_u64_list_append((ja_u64***)&member->roles, &ret_role.id);
  guild::member::modify::params params3 = {
    .roles = member->roles
  };

  guild::member::modify::run(
    client, 
    guild_id, 
    member->user->id, 
    &params3, 
    NULL);

  return ret_role.id;
}

void on_reaction_add(
    client *client, 
    const user::dati *me,
    const u64_snowflake_t channel_id, 
    const u64_snowflake_t message_id, 
    const u64_snowflake_t guild_id, 
    const guild::member::dati *member, 
    const emoji::dati *emoji)
{
  using namespace channel;

  if (member->user->bot) 
    return; // ignore bots
  if (message_id != g_session.message_id)
    return; // not message we're interested on listening to
  if (strcmp(emoji->name, g_session.reaction_emoji)) 
    return; // not reaction emoji we're interested on

  close_existing_sessions(client, guild_id, member);

  u64_snowflake_t session_channel_id, session_role_id;
  session_channel_id = create_session_channel(client, guild_id, member);
  if (!session_channel_id) 
    return; // couldn't create channel, return

  session_role_id = add_session_role(client, guild_id, session_channel_id, member);
  if (!session_role_id) {
    channel::del(client, session_channel_id, NULL);
    return; // couldn't create role, delete channel and return
  }

  message::dati *ret_msg = message::dati_alloc();
  message::create::params params = {
    .content = "Welcome"
  };
  message::create::run(client, session_channel_id, &params, ret_msg);
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

  setcb(client, REACTION_ADD, &on_reaction_add);

  printf("\n\nTHIS IS A WORK IN PROGRESS"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input

  parse_session_config();

  channel::reaction::create(
    client, 
    g_session.channel_id, 
    g_session.message_id, 
    0, 
    g_session.reaction_emoji);

  run(client);

  cleanup(client);

  global_cleanup();
}


