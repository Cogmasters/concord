#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <libdiscord.h>
#include <orka-utils.h>
#include <orka-user-agent.hpp>

#define ELITEBGS_API_URL "https://elitebgs.app/api/ebgs/v5"

/* ELITEBGS User Agent for performing connections to the API */
orka::user_agent::dati elitebgs_ua;

void embed_from_json(char *str, size_t len, void *p_embed)
{
  using namespace discord::channel::embed;
  dati *embed = (dati*)p_embed;

  struct sized_buffer **docs = NULL;
  int total, page, pages, pagingCounter;
  bool hasPrevPage, hasNextPage;
  char *prevPage, *nextPage;
  json_scanf(str, len,
     "[docs]%L"
     "[total]%d"
     "[page]%d"
     "[pages]%d"
     "[pagingCounter]%d"
     "[hasPrevPage]%b"
     "[hasNextPage]%b"
     "[prevPage]%?s"
     "[nextPage]%?s",
     &docs,
     &total,
     &page,
     &pages,
     &pagingCounter,
     &hasPrevPage,
     &hasNextPage,
     &prevPage,
     &nextPage);

  /* @todo add some checks here */

  if(!docs) return; /* early return if no docs found */

  struct sized_buffer **faction_presence = NULL;
  char  government[512],
        name[512],
        updated_at[512];

  for (size_t i=0; docs[i]; ++i) 
  {
    json_scanf(docs[i]->start, docs[i]->size,
        "[faction_presence]%L"
        "[government]%s"
        "[name]%s"
        "[updated_at]%s",
        &faction_presence,
        government,
        name,
        updated_at);

    add_field(embed, "Government", government, true);
    add_field(embed, "Name", name, true);
    add_field(embed, "Updated at", updated_at, true);

    if (faction_presence) {
      struct sized_buffer system_name = {0},
                          state       = {0},
                          influence   = {0},
                          happiness   = {0},
                          updated_at  = {0};

      struct sized_buffer **active_states     = NULL, 
                          **pending_states    = NULL,
                          **recovering_states = NULL,
                          **conflicts         = NULL;

      for (size_t j=0; faction_presence[j]; ++j)
      {
        json_scanf(faction_presence[j]->start, faction_presence[j]->size,
            "[system_name]%T"
            "[state]%T"
            "[influence]%T"
            "[happiness]%T"
            "[active_states]%L"
            "[pending_states]%L"
            "[recovering_states]%L"
            "[conflicts]%L"
            "[updated_at]%T",
            &system_name,
            &state,
            &influence,
            &happiness,
            &active_states,
            &pending_states,
            &recovering_states,
            &conflicts,
            &updated_at);

        if (active_states) {
          struct sized_buffer state = {0};
          for (size_t k=0; active_states[k]; ++k) 
          {
            json_scanf(active_states[k]->start, active_states[k]->size,
                "[state]%T", &state);
          }
          free(active_states);
        }
        if (pending_states) {
          struct sized_buffer state = {0};
          for (size_t k=0; pending_states[k]; ++k) 
          {
            json_scanf(pending_states[k]->start, pending_states[k]->size,
                "[state]%T", &state);
          }
          free(pending_states);
        }
        if (recovering_states) {
          struct sized_buffer state = {0},
                              trend = {0};
          for (size_t k=0; recovering_states[k]; ++k) 
          {
            json_scanf(pending_states[k]->start, pending_states[k]->size,
                "[state]%T [trend]%T", &state, &trend);
          }
          free(recovering_states);
        }
        if (conflicts) {
          struct sized_buffer type          = {0},
                              status        = {0},
                              opponent_name = {0},
                              stake         = {0},
                              days_won      = {0};

          for (size_t k=0; conflicts[k]; ++k) 
          {
            json_scanf(pending_states[k]->start, pending_states[k]->size,
                "[type]%T"
                "[status]%T"
                "[opponent_name]%T"
                "[stake]%T"
                "[days_won]%T",
                &type, 
                &status,
                &opponent_name,
                &stake,
                &days_won);
          }
          free(conflicts);
        }
      }

      free(faction_presence);
    }
  }

  if (prevPage)
    free(prevPage);
  if (nextPage)
    free(nextPage);
  free(docs);
}

void on_ready(discord::client *client, const discord::user::dati *me)
{
  fprintf(stderr, "\n\nEddbapi-Bot succesfully connected to Discord as %s#%s!\n\n",
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

  /* Initialize embed struct that will be loaded to  */
  discord::channel::embed::dati new_embed;
  discord::channel::embed::init_dati(&new_embed);

  struct resp_handle resp_handle =
    {&embed_from_json, (void*)&new_embed};

  char query[512];
  int ret = query_inject(query, sizeof(query),
              "(system):s", msg->content);
  ASSERT_S(ret < (int)sizeof(query), "Out of bounds write attempt");

  /* Fetch from ELITEBGS API */
  orka::user_agent::run(
      &elitebgs_ua, 
      &resp_handle,
      NULL,
      HTTP_GET,
      "/factions%s", query);

  strncpy(new_embed.title, msg->content, sizeof(new_embed.title));
  new_embed.timestamp = orka_timestamp_ms();
  new_embed.color = 15844367; //gold
  change_footer(&new_embed, "Made with Orka", NULL, NULL);

  message::create::params params = {0};
  params.embed = &new_embed;

  message::create::run(client, msg->channel_id, &params, NULL);

  /* Cleanup resources */
  discord::channel::embed::cleanup_dati(&new_embed);
}

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";

  /* Initialized ELITEBGS User Agent */
  orka::user_agent::init(&elitebgs_ua, ELITEBGS_API_URL);

  /* Initialize Discord User Agent */
  discord::global_init();
  discord::client *client = discord::fast_init(config_file);
  assert(NULL != client);

  /* Set discord callbacks */
  setcb_ready(client, &on_ready);
  setcb_message_command(client, "!system ", &on_command);

  /* Start a connection to Discord */
  discord::run(client);

  /* Cleanup resources */
  orka::user_agent::cleanup(&elitebgs_ua);
  discord::cleanup(client);
  discord::global_cleanup();

  return EXIT_SUCCESS;
}
