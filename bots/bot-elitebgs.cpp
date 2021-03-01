#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <libdiscord.h>
#include <orka-utils.h>

#define ELITEBGS_API_URL "https://elitebgs.app/api/ebgs/v5"

/* ELITEBGS User Agent for performing connections to the API */
struct user_agent_s g_elitebgs_ua;
uint64_t g_tick_ms;

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


void ticks_from_json(char *str, size_t len, void *data)
{
  struct sized_buffer **t_ticks = NULL;
  json_scanf(str, len, "[]%L", &t_ticks);
  json_scanf(t_ticks[0]->start, t_ticks[0]->size, "[time]%F", &orka_iso8601_to_unix_ms, &g_tick_ms);

  free(t_ticks);
}

void update_last_tick_ms()
{
  struct resp_handle resp_handle =
    {&ticks_from_json, NULL};

  /* Fetch ticks from ELITEBGS API */
  ua_run(
      &g_elitebgs_ua, 
      &resp_handle,
      NULL,
      NULL,
      HTTP_GET, "/ticks");
}

char* happiness_localised(char *happiness_band)
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
  using namespace discord::channel::embed;

  dati *embed = (dati*)p_embed;

  struct doc_s *doc = (struct doc_s*)malloc(sizeof *doc);
  struct sized_buffer **l_docs = NULL; // get docs token from JSON

  struct faction_presence_s *fpresence = (struct faction_presence_s*)malloc(sizeof *fpresence);
  struct faction_presence_s *history = (struct faction_presence_s*)malloc(sizeof *history);
  struct sized_buffer **l_fpresence = NULL; // get faction_presence token from JSON
  struct sized_buffer **l_history = NULL; // get recovering_states token from JSON

  struct state_s *state = (struct state_s*)malloc(sizeof *state);
  struct sized_buffer **l_active_states = NULL; // get active_states token from JSON
  struct sized_buffer **l_pending_states = NULL; // get pending_states token from JSON
  struct sized_buffer **l_recovering_states = NULL; // get recovering_states token from JSON


  json_scanf(str, len, "[docs]%L", &l_docs);

  char field_value[EMBED_FIELD_VALUE_LEN];

  for (size_t i=0; l_docs[i]; ++i) 
  {
    json_scanf(l_docs[i]->start, l_docs[i]->size,
        "[name]%S"
        "[government]%S"
        "[faction_presence]%L"
        "[updated_at]%S"
        "[history]%L",
        doc->name,
        doc->government,
        &l_fpresence,
        doc->updated_at,
        &l_history);

    if (l_fpresence[0]) 
    {
      for (size_t j=0; l_fpresence[j]; ++j)
      {
        json_scanf(l_fpresence[j]->start, l_fpresence[j]->size,
            "[system_name]%S"
            "[system_id]%S"
            "[state]%S"
            "[influence]%f"
            "[happiness]%S"
            "[active_states]%L"
            "[pending_states]%L"
            "[recovering_states]%L"
            "[updated_at]%S",
            fpresence->system_name,
            fpresence->system_id,
            fpresence->state,
            &fpresence->influence,
            fpresence->happiness,
            &l_active_states,
            &l_pending_states,
            &l_recovering_states,
            fpresence->updated_at);

        if (0 != strcasecmp(embed->title, fpresence->system_name))
          continue;

        for (size_t j2=0; l_history[j2]; ++j2)
        {
          json_scanf(l_history[j2]->start, l_history[j2]->size,
              "[system_id]%S"
              "[influence]%f"
              "[updated_at]%S",
              history->system_id,
              &history->influence,
              history->updated_at);

          if (0 == strcmp(history->system_id, fpresence->system_id)){
            break;
          }
        }

        float influence_diff = 100*(fpresence->influence - history->influence);
        char *influence_emoji;
        if (influence_diff > 0)
          influence_emoji = "📈";
        else if (influence_diff < 0)
          influence_emoji = "📉";
        else
          influence_emoji = "🔷";

        int ret = snprintf(field_value, sizeof(field_value), 
                    "State: %s\n"
                    "Influence: %.1f%s%.1f\n"
                    "Happiness: %s\n",
                    fpresence->state,
                    fpresence->influence * 100, influence_emoji, influence_diff,
                    happiness_localised(fpresence->happiness));

        ret += snprintf(&field_value[ret], sizeof(field_value) - ret, "Active States:");
        if (l_active_states[0]) 
        {
          for (size_t k=0; l_active_states[k]; ++k) 
          {
            json_scanf(l_active_states[k]->start, l_active_states[k]->size,
                "[state]%S", state->state);
            ret += snprintf(&field_value[ret], sizeof(field_value) - ret, " %s,", state->state);
          }
          field_value[ret-1] = '\n'; //replace end comma with newline
        }
        else {
          ret += snprintf(&field_value[ret], sizeof(field_value) - ret, " none\n");
        }

        ret += snprintf(&field_value[ret], sizeof(field_value) - ret, "Pending States:");
        if (l_pending_states[0]) 
        {
          for (size_t k=0; l_pending_states[k]; ++k) 
          {
            json_scanf(l_pending_states[k]->start, l_pending_states[k]->size,
                "[state]%S", state->state);
            ret += snprintf(&field_value[ret], sizeof(field_value) - ret, " %s,", state->state);
          }
          field_value[ret-1] = '\n'; //replace end comma with newline
        }
        else {
          ret += snprintf(&field_value[ret], sizeof(field_value) - ret, " none\n");
        }

        ret += snprintf(&field_value[ret], sizeof(field_value) - ret, "Recovering States:");
        if (l_recovering_states[0]) 
        {
          for (size_t k=0; l_recovering_states[k]; ++k) 
          {
            json_scanf(l_recovering_states[k]->start, l_recovering_states[k]->size,
                "[state]%S [trend]%S", state->state, state->trend);
            ret += snprintf(&field_value[ret], sizeof(field_value) - ret, " %s,", state->state);
            //@todo use trend
          }
          field_value[ret-1] = '\n'; //replace end comma with newline
        }
        else {
          ret += snprintf(&field_value[ret], sizeof(field_value) - ret, " none\n");
        }
      }

      free(l_active_states);
      l_active_states = NULL;

      free(l_pending_states);
      l_pending_states = NULL;

      free(l_recovering_states);
      l_recovering_states = NULL;
    }

    free(l_history);
    free(l_fpresence);
    l_fpresence = NULL;

    add_field(embed, doc->name, field_value, true);
  }

  free(doc);
  free(history);
  free(fpresence);
  free(state);

  free(l_docs);
}

void on_ready(discord::client *client, const discord::user::dati *me)
{
  fprintf(stderr, "\n\nEliteBGS-Bot succesfully connected to Discord as %s#%s!\n\n",
      me->username, me->discriminator);

  (void)client;
}

void on_command(
    discord::client *client,
    const discord::user::dati *me,
    const discord::channel::message::dati *msg)
{
  using namespace discord::channel;

  // make sure bot doesn't echoes other bots
  if (msg->author->bot)
    return;

  update_last_tick_ms();

  /* Initialize embed struct that will be loaded to  */
  embed::dati *new_embed = embed::dati_alloc();

  /* Set embed fields */
  strncpy(new_embed->title, msg->content, sizeof(new_embed->title));
  new_embed->timestamp = orka_timestamp_ms();
  new_embed->color = 15844367; //gold
  embed::change_footer(new_embed, 
      "designed & built by https://cee.dev",
      "https://cee.dev/static/images/cee.png", NULL);

  char query[512];
  int ret = query_inject(query, sizeof(query),
              "(system):s"
              "(timeMax):F", 
              msg->content,
              &orka_ulltostr, &g_tick_ms);

  ASSERT_S(ret < (int)sizeof(query), "Out of bounds write attempt");

  trigger_typing(client, msg->channel_id);

  /* Fetch factions from ELITEBGS API */
  struct resp_handle resp_handle = {&embed_from_json, (void*)new_embed};
  ua_run(
      &g_elitebgs_ua, 
      &resp_handle,
      NULL,
      NULL,
      HTTP_GET,
      "/factions%s", query);

  /* Send embed to channel if embed was loaded */
  message::create::params params = {0};
  if (new_embed->fields)
    params.embed = new_embed;
  else 
    params.content = "System does not exist or could not be found.";

  message::create::run(client, msg->channel_id, &params, NULL);

  /* Cleanup resources */
  embed::dati_free(new_embed);
}

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";

  /* Initialize ELITEBGS User Agent */
  ua_init(&g_elitebgs_ua, ELITEBGS_API_URL);

  /* Initialize Discord User Agent */
  discord::global_init();
  discord::client *client = discord::fast_init(config_file);
  assert(NULL != client);

  /* Set discord callbacks */
  discord::setcb(client, discord::READY, &on_ready);
  discord::setcb_command(client, "!system ", &on_command);

  /* Set bot presence activity */
  discord::presence::activity::dati *new_activity;
  new_activity = discord::presence::activity::dati_alloc();
  strcpy(new_activity->name, "!h | cee.dev");
  new_activity->type = 0; // Playing
  discord::set_presence(client, new_activity, "online", false);

  /* Start a connection to Discord */
  discord::run(client);

  /* Cleanup resources */
  ua_cleanup(&g_elitebgs_ua);
  discord::cleanup(client);
  discord::global_cleanup();

  return EXIT_SUCCESS;
}
