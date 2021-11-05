#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <assert.h>

#include "discord.h"
#include "cee-utils.h"
#include "json-actor.h"

const char *ALPHA_EMOJI[] = { "🇦",
                              "🇧",
                              "🇨",
                              "🇩",
                              "🇪",
                              "🇫",
                              "🇬",
                              "🇭",
                              "🇮",
                              "🇯",
                              "🇰",
                              "🇱",
                              "🇲",
                              "🇳",
                              "🇴",
                              "🇵",
                              "🇶",
                              "🇷",
                              "🇸",
                              "🇹",
                              "🇺"
                              "🇻",
                              "🇼",
                              "🇽",
                              "🇾",
                              "🇿",
                              NULL };

enum session_status { PAUSED, RUNNING, FINISHED };

/* @sqlite THIS SHOULD BE STORED IN DB
 *  @status can be used to resume state
 *  @user_id the user who this session belongs to
 *  @channel_id the channel this session is happening
 *  @curr_question the current question index
 *  @hits how many questions the user got correct */
struct session {
  enum session_status status;
  u64_snowflake_t user_id;
  u64_snowflake_t channel_id;
  int curr_question;
  int hits; // correct answers
};

#define MAX_SESSIONS 100 //@sqlite this can be removed after DB is implemented
struct answer {
  char *desc;
  bool value;
};
struct question {
  char *desc;
  struct answer *answers;
  int num_answers;
};
struct session_config {
  char *chat_name;
  char *chat_topic;
  u64_snowflake_t channel_id;
  u64_snowflake_t message_id;
  char *reaction_emoji;

  struct question *questions;
  int num_questions;
  int questions_per_session;

  /* @sqlite
   *  @active_sessions can be rid of, its not thread safe and it shouldn't be
   *    necessary to maintain a register of ongoing sessions */
  struct session active_sessions[MAX_SESSIONS];
} g_session; /* GLOBAL VARIABLE */

void parse_session_config()
{
  size_t len;
  char *json_payload = cee_load_whole_file("bot-quiz.json", &len);
  NTL_T(struct sized_buffer) t_questions = NULL;

  json_extract(json_payload, len,
               "(listener.channel_id):s_as_u64"
               "(listener.message_id):s_as_u64"
               "(listener.reaction_emoji):?s"
               "(new_channel.name):?s"
               "(new_channel.topic):?s"
               "(questions_per_session):lld",
               &g_session.channel_id, &g_session.message_id,
               &g_session.reaction_emoji, &g_session.chat_name,
               &g_session.chat_topic, &g_session.questions_per_session);

  json_extract(json_payload, len, "(questions):[L]", &t_questions);

  g_session.num_questions = ntl_length((void **)t_questions);
  if (g_session.num_questions < g_session.questions_per_session)
    g_session.questions_per_session = g_session.num_questions;

  g_session.questions = (struct question *)calloc(
    1, g_session.num_questions * sizeof(struct question));

  for (size_t i = 0; t_questions[i]; ++i) {
    NTL_T(struct sized_buffer) t_answers = NULL;
    json_extract(t_questions[i]->start, t_questions[i]->size,
                 "(description):?s", &g_session.questions[i].desc);
    json_extract(t_questions[i]->start, t_questions[i]->size, "(answers):[L]",
                 &t_answers);

    g_session.questions[i].num_answers = ntl_length((void **)t_answers);
    g_session.questions[i].answers = (struct answer *)calloc(
      1, g_session.questions[i].num_answers * sizeof(struct answer));
    for (int j = 0; t_answers[j]; ++j) {
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

void on_ready(struct discord *client, const struct discord_user *bot)
{
  log_info("Quiz-Bot succesfully connected to Discord as %s#%s!",
           bot->username, bot->discriminator);
}

/* @sqlite after DB is implemented there will be no need of checking if a
 * session exists by checking if there is a corresponding role attributed to
 * the user */
void close_existing_sessions(struct discord *client,
                             const u64_snowflake_t guild_id,
                             const struct discord_guild_member *member)
{
  /* @sqlite simply fetching a database row by the user_id should be enough to
   * get a ongoing session */

  /* Check if user already has a session role assigned to */
  NTL_T(struct discord_role) rls = NULL;
  discord_get_guild_roles(client, guild_id, &rls);

  for (size_t i = 0; rls[i]; ++i) {
    if (strncmp("TMP", rls[i]->name, 3)) continue;

    u64_snowflake_t channel_id, user_id;
    sscanf(rls[i]->name, "TMP%" PRIu64 "_%" PRIu64, &user_id, &channel_id);

    if (member->user->id == user_id) {
      discord_delete_channel(client, channel_id, NULL);
      discord_delete_guild_role(client, guild_id, rls[i]->id);

      // reset active_session if exists
      for (size_t i = 0; i < MAX_SESSIONS; ++i) {
        if (user_id == g_session.active_sessions[i].user_id) {
          memset(g_session.active_sessions + i, 0, sizeof(struct session));
          break;
        }
      }
    }
  }

  discord_role_list_free(rls);
}

u64_snowflake_t create_session_channel(
  struct discord *client,
  const u64_snowflake_t guild_id,
  const struct discord_guild_member *member)
{
  struct discord_channel ch = { 0 };

  struct discord_create_guild_channel_params params1 = {
    .name = g_session.chat_name, .topic = g_session.chat_topic
  };

  discord_overwrite_append(
    &params1.permission_overwrites,
    guild_id, // @everyone role id is the same as guild id
    0, // role type
    DISCORD_BITWISE_PERMISSION_ZERO, // Allow
    DISCORD_BITWISE_PERMISSION_ADD_REACTIONS // Deny
      | DISCORD_BITWISE_PERMISSION_VIEW_CHANNEL |
      DISCORD_BITWISE_PERMISSION_SEND_MESSAGES);

  discord_overwrite_append(&params1.permission_overwrites, member->user->id,
                           1, // user type
                           DISCORD_BITWISE_PERMISSION_ADD_REACTIONS // Allow
                             | DISCORD_BITWISE_PERMISSION_VIEW_CHANNEL |
                             DISCORD_BITWISE_PERMISSION_SEND_MESSAGES,
                           DISCORD_BITWISE_PERMISSION_ZERO); // Deny

  discord_create_guild_channel(client, guild_id, &params1, &ch);

  /* @sqlite here you can try and fetch the session from the database
   *  by the user_id, instead of using this for loop to find a match */
  // create new active_session if doesn't exist
  for (size_t i = 0; i < MAX_SESSIONS; ++i) {
    if (0 == g_session.active_sessions[i].user_id) {
      g_session.active_sessions[i].user_id = member->user->id;
      g_session.active_sessions[i].channel_id = ch.id;
      g_session.active_sessions[i].status = PAUSED;
    }
  }

  return ch.id;
}

/* @sqlite this is irrelevant and unecessary when a DB is added, as we won't
 * need a unique
 *  role created per user that associates himself and a session's channel */
u64_snowflake_t add_session_role(struct discord *client,
                                 const u64_snowflake_t guild_id,
                                 const u64_snowflake_t channel_id,
                                 const struct discord_guild_member *member)
{
  char text[64];
  snprintf(text, sizeof(text), "TMP%" PRIu64 "_%" PRIu64, member->user->id,
           channel_id);

  struct discord_role ret_role = { 0 };
  struct discord_create_guild_role_params params2 = { .name = text };
  discord_create_guild_role(client, guild_id, &params2, &ret_role);
  if (!ret_role.id) return 0;

  //@todo turn this into a public function
  ja_u64_list_append((ja_u64 ***)&member->roles, &ret_role.id);
  struct discord_modify_guild_member_params params3 = { .roles =
                                                          member->roles };
  discord_modify_guild_member(client, guild_id, member->user->id, &params3,
                              NULL);

  return ret_role.id;
}

void start_new_session(struct discord *client,
                       const u64_snowflake_t guild_id,
                       const struct discord_guild_member *member)
{
#if 1 /* @sqlite this section can be replaced by a simple DB fetch, try to    \
         fetch a row by the user_id, if it doesn't exist create a new session               \
         and store in DB, otherwise if it exists you can delete the                                    \
         channel_id associated with the ongoing                               \
          session, (or continue/restart the quiz in the same channel) */
  close_existing_sessions(client, guild_id, member);

  u64_snowflake_t session_channel_id, session_role_id;
  session_channel_id = create_session_channel(client, guild_id, member);
  if (!session_channel_id) return; // couldn't create channel, return

  session_role_id =
    add_session_role(client, guild_id, session_channel_id, member);
  if (!session_role_id) {
    close_existing_sessions(client, guild_id, member);
    return; // couldn't create role, delete channel and return
  }
#endif

  struct discord_message ret_msg = { 0 };

  struct discord_create_message_params params = {
    .content = "Would you like to start?"
  };
  discord_create_message(client, session_channel_id, &params, &ret_msg);

  discord_create_reaction(client, session_channel_id, ret_msg.id, 0,
                          g_session.reaction_emoji);

  discord_message_cleanup(&ret_msg);
}

void send_next_question(struct discord *client,
                        u64_snowflake_t channel_id,
                        struct session *session,
                        struct question *question)
{
  char text[DISCORD_MAX_PAYLOAD_LEN];
  if (session->curr_question == g_session.questions_per_session) {
    sprintf(text, "You got %d out of %d! (%.1f%%)", session->hits,
            g_session.questions_per_session,
            100 *
              ((float)session->hits / (float)g_session.questions_per_session));
    struct discord_create_message_params params = { .content = text };
    discord_create_message(client, channel_id, &params, NULL);

    session->status = FINISHED;
    return; /* EARLY RETURN */
  }

  int offset = sprintf(text, "QUESTION %d\n%s\n", 1 + session->curr_question,
                       question->desc);

  for (int i = 0; i < question->num_answers; ++i) {
    offset +=
      sprintf(text + offset, "(%c)%s ", 'A' + i, question->answers[i].desc);
  }

  struct discord_message ret_msg = { 0 };
  struct discord_create_message_params params = { .content = text };
  discord_create_message(client, channel_id, &params, &ret_msg);

  for (int i = 0; i < question->num_answers; ++i) {
    discord_create_reaction(client, channel_id, ret_msg.id, 0, ALPHA_EMOJI[i]);
  }
  discord_message_cleanup(&ret_msg);

  session->status = RUNNING;
}

void on_reaction_add(struct discord *client,
                     const struct discord_user *bot,
                     const u64_snowflake_t user_id,
                     const u64_snowflake_t channel_id,
                     const u64_snowflake_t message_id,
                     const u64_snowflake_t guild_id,
                     const struct discord_guild_member *member,
                     const struct discord_emoji *emoji)
{
  if (member->user->bot) return; // ignore bots
  if ((message_id == g_session.message_id) &&
      (0 == strcmp(emoji->name, g_session.reaction_emoji)))
  { // close existing quiz session / start new quiz session
    start_new_session(client, guild_id, member);
  }

  /* get session associated with the user */
  struct session *session = NULL;
  for (size_t i = 0; i < MAX_SESSIONS; ++i) {
    if (channel_id == g_session.active_sessions[i].channel_id) {
      session = &g_session.active_sessions[i];
      break; /* EARLY BREAK */
    }
  }

  if (!session) return; /* EARLY RETURN */
  if (FINISHED == session->status) return; /* EARLY RETURN */

  struct question *question = NULL;
  switch (session->status) {
  case RUNNING:
    // delete previous question from channel
    discord_delete_message(client, channel_id, message_id);

    // get current question associated to session
    question = &g_session.questions[session->curr_question];

    // check if current answer is correct
    for (int i = 0; i < question->num_answers; ++i) {
      if (strcmp(emoji->name, ALPHA_EMOJI[i]))
        continue; // skip non-alphabet emojis
      if (true == question->answers[i].value) ++session->hits;
    }

    ++session->curr_question;
  /* fall through */
  case PAUSED:
    // get next question from session (or first)
    question = &g_session.questions[session->curr_question];

    send_next_question(client, channel_id, session, question);
    break;
  case FINISHED:
  default:
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
    config_file = "../config.json";

  setlocale(LC_ALL, "");

  discord_global_init();

  struct discord *client = discord_config_init(config_file);
  assert(NULL != client);

  discord_set_on_message_reaction_add(client, &on_reaction_add);

  printf("\n\nTHIS IS A WORK IN PROGRESS"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input

  parse_session_config();

  discord_create_reaction(client, g_session.channel_id, g_session.message_id,
                          0, g_session.reaction_emoji);

  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}
