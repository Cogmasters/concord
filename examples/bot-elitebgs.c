#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <assert.h>

#include "discord.h"
#include "discord-internal.h" /* access struct logconf from struct discord */

#include "user-agent.h"
#include "cee-utils.h"
#include "json-actor.h"

#define ELITEBGS_API_URL "https://elitebgs.app/api/ebgs/v5"

/* ELITEBGS User Agent for performing connections to the API */
struct user_agent *g_elitebgs_ua;

struct doc_s {
  char name[512];
  char government[512];
  char updated_at[512];
};

struct faction_presence_s {
  char system_id[512];
  char system_name[512];
  char state[512];
  float influence;
  char happiness[512];
  char updated_at[512];
};

struct state_s {
  char state[512];
  char trend[512];
};

void ticks_from_json(char *str, size_t len, void *p_tick_ms)
{
  uint64_t *tick_ms = p_tick_ms;

  struct sized_buffer **ticks = NULL;
  json_extract(str, len, "[L]", &ticks);
  if (!ticks) return;

  json_extract(ticks[0]->start, ticks[0]->size, "(time):F",
               &cee_iso8601_to_unix_ms, tick_ms);

  free(ticks);
}

void update_last_tick_ms(uint64_t *tick_ms)
{
  struct ua_resp_handle resp_handle = { .ok_cb = &ticks_from_json,
                                        .ok_obj = tick_ms };

  /* Fetch ticks from ELITEBGS API */
  ua_run(g_elitebgs_ua, NULL, &resp_handle, NULL, HTTP_GET, "/ticks");
}

char *happiness_localised(char *happiness_band)
{
  if (0 == strcasecmp(happiness_band, "$faction_happinessband1;"))
    return "elated";
  if (0 == strcasecmp(happiness_band, "$faction_happinessband2;"))
    return "happy";
  if (0 == strcasecmp(happiness_band, "$faction_happinessband3;"))
    return "discontented";
  if (0 == strcasecmp(happiness_band, "$faction_happinessband4;"))
    return "unhappy";
  if (0 == strcasecmp(happiness_band, "$faction_happinessband5;"))
    return "despondent";
  return "unknown";
}

void embed_from_json(char *str, size_t len, void *p_embed)
{
  struct discord_embed *embed = p_embed;

  NTL_T(struct sized_buffer) l_docs = NULL;
  NTL_T(struct sized_buffer) l_fpresence = NULL;
  NTL_T(struct sized_buffer) l_history = NULL;
  NTL_T(struct sized_buffer) l_active_states = NULL;
  NTL_T(struct sized_buffer) l_pending_states = NULL;
  NTL_T(struct sized_buffer) l_recovering_states = NULL;

  struct doc_s *doc = malloc(sizeof *doc);
  struct faction_presence_s *fpresence = malloc(sizeof *fpresence);
  struct faction_presence_s *history = malloc(sizeof *history);
  struct state_s *state = malloc(sizeof *state);

  json_extract(str, len, "(docs):[L]", &l_docs);

  char field_value[DISCORD_EMBED_FIELD_VALUE_LEN];
  for (size_t i = 0; l_docs[i]; ++i) {
    json_extract(l_docs[i]->start, l_docs[i]->size,
                 "(name):.*s"
                 "(government):.*s"
                 "(faction_presence):[L]"
                 "(updated_at):.*s"
                 "(history):[L]",
                 sizeof(doc->name), doc->name, sizeof(doc->government),
                 doc->government, &l_fpresence, sizeof(doc->updated_at),
                 doc->updated_at, &l_history);

    for (size_t i = 0; l_fpresence[i]; ++i) {
      json_extract(l_fpresence[i]->start, l_fpresence[i]->size,
                   "(system_name):.*s"
                   "(system_id):.*s"
                   "(state):.*s"
                   "(influence):f"
                   "(happiness):.*s"
                   "(active_states):[L]"
                   "(pending_states):[L]"
                   "(recovering_states):[L]"
                   "(updated_at):.*s",
                   sizeof(fpresence->system_name), fpresence->system_name,
                   sizeof(fpresence->system_id), fpresence->system_id,
                   sizeof(fpresence->state), fpresence->state,
                   &fpresence->influence, sizeof(fpresence->happiness),
                   fpresence->happiness, &l_active_states, &l_pending_states,
                   &l_recovering_states, sizeof(fpresence->updated_at),
                   fpresence->updated_at);

      if (strcasecmp(embed->title, fpresence->system_name))
        continue; /* not the system we are interested in */

      float influence_diff = 0.0;
      char *influence_emoji = "🔷";
      for (size_t i = 0; l_history[i]; ++i) {
        json_extract(l_history[i]->start, l_history[i]->size,
                     "(system_id):.*s"
                     "(influence):f"
                     "(updated_at):.*s",
                     sizeof(history->system_id), history->system_id,
                     &history->influence, sizeof(history->system_id),
                     history->updated_at);

        if (strcmp(history->system_id, fpresence->system_id)) {
          influence_diff = 100 * (fpresence->influence - history->influence);
          if (influence_diff > 0)
            influence_emoji = "📈";
          else if (influence_diff < 0)
            influence_emoji = "📉";

          break; /* found a match */
        }
      }

      if (!influence_diff) {
        influence_diff = fpresence->influence * 100;
      }

      int ret =
        snprintf(field_value, sizeof(field_value),
                 "State: %s\n"
                 "Influence: %.1f%s%.1f\n"
                 "Happiness: %s\n",
                 fpresence->state, fpresence->influence * 100, influence_emoji,
                 influence_diff, happiness_localised(fpresence->happiness));

      ret += snprintf(&field_value[ret], sizeof(field_value) - ret,
                      "Active States:");

      if (!*l_active_states) {
        for (size_t i = 0; l_active_states[i]; ++i) {
          json_extract(l_active_states[i]->start, l_active_states[i]->size,
                       "(state):.*s", sizeof(state->state), state->state);
          ret += snprintf(&field_value[ret], sizeof(field_value) - ret, " %s,",
                          state->state);
        }
        field_value[ret - 1] = '\n'; // replace end comma with newline
      }
      else {
        ret +=
          snprintf(&field_value[ret], sizeof(field_value) - ret, " none\n");
      }

      ret += snprintf(&field_value[ret], sizeof(field_value) - ret,
                      "Pending States:");
      if (*l_pending_states) {
        for (size_t i = 0; l_pending_states[i]; ++i) {
          json_extract(l_pending_states[i]->start, l_pending_states[i]->size,
                       "(state):.*s", sizeof(state->state), state->state);
          ret += snprintf(&field_value[ret], sizeof(field_value) - ret, " %s,",
                          state->state);
        }
        field_value[ret - 1] = '\n'; // replace end comma with newline
      }
      else {
        ret +=
          snprintf(&field_value[ret], sizeof(field_value) - ret, " none\n");
      }

      ret += snprintf(&field_value[ret], sizeof(field_value) - ret,
                      "Recovering States:");
      if (*l_recovering_states) {
        for (size_t i = 0; l_recovering_states[i]; ++i) {
          json_extract(l_recovering_states[i]->start,
                       l_recovering_states[i]->size,
                       "(state):.*s"
                       "(trend):.*s",
                       sizeof(state->state), state->state,
                       sizeof(state->trend), state->trend);
          ret += snprintf(&field_value[ret], sizeof(field_value) - ret, " %s,",
                          state->state);
          //@todo use trend
        }
        field_value[ret - 1] = '\n'; // replace end comma with newline
      }
      else {
        ret +=
          snprintf(&field_value[ret], sizeof(field_value) - ret, " none\n");
      }
    }

    free(l_active_states);
    l_active_states = NULL;

    free(l_pending_states);
    l_pending_states = NULL;

    free(l_recovering_states);
    l_recovering_states = NULL;

    free(l_history);
    free(l_fpresence);
    l_fpresence = NULL;

    discord_embed_add_field(embed, doc->name, field_value, true);
  }

  free(doc);
  free(history);
  free(fpresence);
  free(state);
  free(l_docs);
}

void on_ready(struct discord *client, const struct discord_user *bot)
{
  log_info("EliteBGS-Bot succesfully connected to Discord as %s#%s!",
           bot->username, bot->discriminator);
}

void on_command(struct discord *client,
                const struct discord_user *bot,
                const struct discord_message *msg)
{
  // make sure bot doesn't echoes other bots
  if (msg->author->bot) return;

  uint64_t tick_ms = 0;
  update_last_tick_ms(&tick_ms);

  /* Initialize embed struct that will be loaded to  */
  struct discord_embed new_embed = {
    .timestamp = cee_timestamp_ms(),
    .color = 15844367 // gold
  };
  /* Set embed fields */
  discord_embed_set_title(&new_embed, "%s", msg->content);
  discord_embed_set_footer(&new_embed, "designed & built by https://cee.dev",
                           "https://cee.dev/static/images/cee.png", NULL);

  char query[512];
  int ret = query_inject(query, sizeof(query),
                         "(system):s"
                         "(timeMax):F",
                         msg->content, &cee_ulltostr, &tick_ms);
  ASSERT_S(ret < sizeof(query), "Out of bounds write attempt");

  discord_trigger_typing_indicator(client, msg->channel_id);

  char endpoint[2048];
  snprintf(endpoint, sizeof(endpoint), "/factions%s", query);

  /* Fetch factions from ELITEBGS API */
  ua_run(g_elitebgs_ua, NULL,
         &(struct ua_resp_handle){ .ok_cb = &embed_from_json,
                                   .ok_obj = &new_embed },
         NULL, HTTP_GET, endpoint);

  /* Send embed to channel if embed was loaded */
  struct discord_create_message_params params = { 0 };
  if (new_embed.fields)
    params.embed = &new_embed;
  else
    params.content = "System does not exist or could not be found.";
  discord_create_message(client, msg->channel_id, &params, NULL);

  /* Cleanup resources */
  discord_embed_cleanup(&new_embed);
}

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "../config.json";

  /* Initialize Discord User Agent */
  discord_global_init();
  struct discord *client = discord_config_init(config_file);
  assert(NULL != client);

  /* Initialize ELITEBGS User Agent (share discord logconf) */
  g_elitebgs_ua = ua_init(client->conf);
  ua_set_url(g_elitebgs_ua, ELITEBGS_API_URL);

  /* Set discord callbacks */
  discord_set_on_ready(client, &on_ready);
  discord_set_on_command(client, "!system", &on_command);

  printf("\n\nThis bot demonstrates how easy it is to make two"
         " distinct APIs work together, EliteBGS + Discord.\n"
         "1. Type !system <system_name> to print informations about that "
         "system (ex: !system Qa'Wakana)\n"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input

  /* Set bot presence activity */
  struct discord_presence_status new_presence = {
    .status = "online",
    .since = cee_timestamp_ms(),
  };
  discord_presence_add_activity(&new_presence, &(struct discord_activity){
                                                 .name = "cee.dev",
                                                 .type = 0 // Playing
                                               });
  discord_set_presence(client, &new_presence);

  /* Start a connection to Discord */
  discord_run(client);

  /* Cleanup resources */
  ua_cleanup(g_elitebgs_ua);
  discord_cleanup(client);
  discord_global_cleanup();

  return EXIT_SUCCESS;
}
