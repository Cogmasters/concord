#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <libdiscord.h>
#include <orka-utils.h>
#include <orka-user-agent.hpp>

#define EDDBAPI_API_URL "https://eddbapi.kodeblox.com/api/v4"


struct doc {
  char _id[512];
  int id;
  char name_lower[1024];
  bool is_name_faction;
  int home_system_id;
  char allegiance[512];
  int allegiance_id;
  char government[512];
  int government_id;
  uint64_t updated_at;
  char name[1024];
  int __v;
};

void doc_from_json(char *str, size_t len, void *p_doc)
{
  struct doc *doc = (struct doc*)p_doc;
  json_scanf(str, len,
      "[_id]%s"
      "[id]%d"
      "[name_lower]%s"
      "[is_name_faction]%b"
      "[home_system_id]%d"
      "[allegiance]%s"
      "[allegiance_id]%d"
      "[government]%s"
      "[government_id]%d"
      "[updated_at]%F"
      "[name]%s"
      "[__v]%d",
      doc->_id,
      &doc->id,
      doc->name_lower,
      &doc->is_name_faction,
      &doc->home_system_id,
      doc->allegiance,
      &doc->allegiance_id,
      doc->government,
      &doc->government_id,
      &orka_iso8601_to_unix_ms, &doc->updated_at,
      doc->name,
      &doc->__v);

  D_PRINT("Doc object loaded with API response");
}

void init_doc(void *p_doc) {
  memset(p_doc, 0, sizeof(struct doc));
}

void
cleanup_doc(void *p_channel) {
  DS_NOTOP_PUTS("Doc object fields cleared"); 
}

void docs_list_from_json(char *str, size_t len, void *p_docs)
{
  struct ntl_deserializer deserializer = {
    .elem_size = sizeof(struct doc),
    .init_elem = &init_doc,
    .elem_from_buf = &doc_from_json,
    .ntl_recipient_p = (void***)p_docs
  };
  orka_str_to_ntl(str, len, &deserializer);
}

void embed_from_json(char *str, size_t len, void *p_embed)
{
  using namespace discord::channel::embed;
  dati *embed = (dati*)p_embed;

  struct doc **docs = NULL;
  int total;
  json_scanf(str, len,
     "[docs]%F"
     "[total]%d",
     &docs_list_from_json, &docs,
     &total);

  ntl_free((void**)docs, &cleanup_doc);
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

  orka::user_agent::dati *p_eddbapi_ua = (orka::user_agent::dati*)discord::get_data(client);

  /* Initialize embed struct that will be loaded to  */
  discord::channel::embed::dati new_embed;
  discord::channel::embed::init_dati(&new_embed);

  struct resp_handle resp_handle =
    {&embed_from_json, (void*)&new_embed};

  char query[512];
  int ret = query_inject(query, sizeof(query),
              "(homesystemname):s", msg->content);
  ASSERT_S(ret < (int)sizeof(query), "Out of bounds write attempt");

  orka::user_agent::run(
      p_eddbapi_ua, 
      &resp_handle,
      NULL,
      HTTP_GET,
      "/factions%s", query);

  message::create::params params = {
    .embed = &new_embed
  };

  message::create::run(client, msg->channel_id, &params, NULL);

  discord::channel::embed::cleanup_dati(&new_embed);
}

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";

  /* Initialize Discord user agent */
  discord::global_init();
  discord::client *client = discord::fast_init(config_file);
  assert(NULL != client);

  /* Set discord callbacks */
  setcb_ready(client, &on_ready);
  setcb_message_command(client, "!system ", &on_command);

  /* Initialize EDDBAPI user agent */
  orka::user_agent::dati eddbapi_ua;
  orka::user_agent::init(&eddbapi_ua, EDDBAPI_API_URL);

  /* Store eddbapi_ua for retrieval within callbacks */
  // @todo make set_data and get_data thread safe
  discord::set_data(client, (void*)&eddbapi_ua);

  /* Start a connection to Discord */
  discord::run(client);

  /* Cleanup allocated resources */
  orka::user_agent::cleanup(&eddbapi_ua);
  discord::cleanup(client);
  discord::global_cleanup();

  return EXIT_SUCCESS;
}
