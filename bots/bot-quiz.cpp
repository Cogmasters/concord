#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <libdiscord.h>

using namespace discord;


const char *ALPHA_EMOJI[] = {
  "🇦","🇧","🇨","🇩","🇪","🇫","🇬","🇭","🇮","🇯","🇰","🇱","🇲","🇳","🇴","🇵","🇶","🇷","🇸","🇹","🇺""🇻","🇼", "🇽","🇾","🇿" ,NULL
};

enum session_status {
  PAUSED, RUNNING, FINISHED
};

struct session {
  enum session_status status;
  u64_snowflake_t user_id;
  u64_snowflake_t channel_id;
  int curr_question;
  int hits; // correct answers
};

struct answer {
  char *desc;
  bool value;
};

struct question {
  char *desc;
  struct answer *answers;
  int num_answers;
};

#define MAX_SESSIONS 100

struct session_config {
  char *chat_name;
  char *chat_topic;
  u64_snowflake_t channel_id;
  u64_snowflake_t message_id;
  char *reaction_emoji;

  struct question *questions;
  int num_questions;
  int questions_per_session;

  struct session active_sessions[MAX_SESSIONS];
} g_session; /* GLOBAL VARIABLE */

void
parse_session_config()
{
  size_t len;
  char *json_payload = orka_load_whole_file("bot-quiz.json", &len);
  struct sized_buffer **t_questions = NULL;

  json_extract(json_payload, len,
    "(listener.channel_id):s_as_u64"
    "(listener.message_id):s_as_u64"
    "(listener.reaction_emoji):?s"
    "(new_channel.name):?s"
    "(new_channel.topic):?s"
    "(questions_per_session):lld",
    &g_session.channel_id,
    &g_session.message_id,
    &g_session.reaction_emoji,
    &g_session.chat_name,
    &g_session.chat_topic,
    &g_session.questions_per_session);

  json_scanf(json_payload, len, "[questions]%L", &t_questions);

  g_session.num_questions = ntl_length((void**)t_questions);
  if (g_session.num_questions < g_session.questions_per_session)
    g_session.questions_per_session = g_session.num_questions;

  g_session.questions = (struct question*)calloc(1, g_session.num_questions * sizeof(struct question)); 

  for (size_t i=0; t_questions[i]; ++i) {
    struct sized_buffer **t_answers = NULL;
    json_extract(t_questions[i]->start, t_questions[i]->size,
      "(description):?s", &g_session.questions[i].desc);
    json_scanf(t_questions[i]->start, t_questions[i]->size,
      "[answers]%L", &t_answers);

    g_session.questions[i].num_answers = ntl_length((void**)t_answers);
    g_session.questions[i].answers = (struct answer*)calloc(1, g_session.questions[i].num_answers * sizeof(struct answer));
    for (int j=0; t_answers[j]; ++j) {
      json_extract(t_answers[j]->start, t_answers[j]->size,
        "(description):?s"
        "(value):b", 
        &g_session.questions[i].answers[j].desc,
        &g_session.questions[i].answers[j].value);
    }
    free(t_answers);
  }

  free(t_questions);
}

void 
on_ready(client *client, const user::dati *me)
{
  fprintf(stderr, "\n\nQuiz-Bot succesfully connected to Discord as %s#%s!\n\n",
      me->username, me->discriminator);

  (void)client;
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

      // reset active_session if exists
      for (size_t i=0; i < MAX_SESSIONS; ++i) {
        if (user_id == g_session.active_sessions[i].user_id) {
          memset(g_session.active_sessions + i, 0, sizeof(struct session));
          break;
        }
      }
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
  
  // create new active_session if doesn't exist
  for (size_t i=0; i < MAX_SESSIONS; ++i) {
    if (0 == g_session.active_sessions[i].user_id) {
      g_session.active_sessions[i].user_id = member->user->id;
      g_session.active_sessions[i].channel_id = ch.id;
      g_session.active_sessions[i].status = PAUSED;
#if 0
      int *indexes = malloc(g_session.num_questions * sizeof(int));
      for (size_t i=0; i < g_session.num_questions; ++i)
        indexes[i] = i;

      size_t rand_index;
      int tmp;
      for (size_t i=0; i < g_session.num_questions; ++i) {
        rand_index = rand() % g_session.num_questions; 
        tmp = indexes[i];
        indexes[i] = rand_index;
        indexes[rand_index] = tmp;
      }
      free(indexes);
#endif
    }
  }

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

void start_new_session(
  client *client,
  const u64_snowflake_t guild_id,
  const guild::member::dati *member)
{
  using namespace channel;

  close_existing_sessions(client, guild_id, member);

  u64_snowflake_t session_channel_id, session_role_id;
  session_channel_id = create_session_channel(client, guild_id, member);
  if (!session_channel_id) 
    return; // couldn't create channel, return

  session_role_id = add_session_role(client, guild_id, session_channel_id, member);
  if (!session_role_id) {
    close_existing_sessions(client, guild_id, member);
    return; // couldn't create role, delete channel and return
  }

  message::dati *ret_msg = message::dati_alloc();
  message::create::params params = {
    .content = "Would you like to start?"
  };
  message::create::run(client, session_channel_id, &params, ret_msg);

  reaction::create(
    client, 
    session_channel_id, 
    ret_msg->id, 
    0, 
    g_session.reaction_emoji);

  message::dati_free(ret_msg);
}

void send_next_question(
  client *client,
  u64_snowflake_t channel_id,
  struct session *session, 
  struct question *question)
{
  using namespace channel;

  char text[MAX_PAYLOAD_LEN];
  if (session->curr_question == g_session.questions_per_session) {
    sprintf(text, "You got %d out of %d! (%.1f%%)", \
      session->hits, g_session.questions_per_session,
      100*((float)session->hits / (float)g_session.questions_per_session));
    message::create::params params = {
      .content = text
    };
    message::create::run(client, channel_id, &params, NULL);

    session->status = FINISHED;
    return; /* EARLY RETURN */
  }

  int offset = sprintf(text, "QUESTION %d\n%s\n", \
                1+session->curr_question,
                question->desc);

  for (int i=0; i < question->num_answers; ++i) {
    offset += sprintf(text+offset, "(%c)%s ", \
      'A'+ i, question->answers[i].desc);
  }

  message::dati *ret_msg = message::dati_alloc();
  message::create::params params = {
    .content = text
  };
  message::create::run(client, channel_id, &params, ret_msg);

  for (int i=0; i < question->num_answers; ++i) {
    reaction::create(
      client, 
      channel_id, 
      ret_msg->id, 
      0, 
      ALPHA_EMOJI[i]);
  }
  message::dati_free(ret_msg);

  session->status = RUNNING;
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
  if ( (message_id == g_session.message_id) 
      && (0 == strcmp(emoji->name, g_session.reaction_emoji)) )
  { // close existing quiz session / start new quiz session
    start_new_session(client, guild_id, member);
  }

  /* get session associated with the user */
  struct session *session=NULL;
  for (size_t i=0; i < MAX_SESSIONS; ++i) {
    if (channel_id == g_session.active_sessions[i].channel_id) {
      session = &g_session.active_sessions[i];
      break; /* EARLY BREAK */
    }
  }

  if (!session) return; /* EARLY RETURN */
  if (FINISHED == session->status) return; /* EARLY RETURN */

  struct question *question=NULL;
  switch (session->status) {
  case RUNNING:
      // delete previous question from channel
      message::del(client, channel_id, message_id);

      // get current question associated to session
      question = &g_session.questions[session->curr_question];

      // check if current answer is correct
      for (int i=0; i < question->num_answers; ++i) {
        if (strcmp(emoji->name, ALPHA_EMOJI[i]))
          continue; // skip non-alphabet emojis
        if (true == question->answers[i].value)
          ++session->hits;
      }

      ++session->curr_question;
  /* fall through */
  case PAUSED:
      // get next question from session (or first)
      question = &g_session.questions[session->curr_question];

      send_next_question(client, channel_id, session, question);
      break;
  case FINISHED: default:
      close_existing_sessions(client, guild_id, member);
      return; /* it should never happen */
  }
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

  setcb(client, MESSAGE_REACTION_ADD, &on_reaction_add);

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


