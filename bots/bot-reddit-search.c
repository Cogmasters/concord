#define _GNU_SOURCE /* asprintf() */
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* strchr() */
#include <ctype.h> /* isalnum() */
#include <assert.h>

#include "reddit.h"
#include "discord.h"

#include "json-actor.h" /* json_extract() */
#include "orka-utils.h" /* orka_load_whole_file() */
#include "scheduler.h"


#define SEARCH_PARAMS_FILE "bot-reddit-search.json"
#define EMBED_THUMBNAIL \
  "https://external-preview.redd.it/ei2UEblhohs09-oGeS6Ws14T2pOd37GN1_1VUzisvZE.png?auto=webp&s=9fc63c64245f6aa267d712c8b4ad885aa5555b7b"


struct {
  struct { /* REDDIT UTILS */
    struct reddit *client;
    struct task_s *tsk_refresh_token;
    struct task_s *tsk_search;
    struct reddit_search_params params;
    char *srs; // subreddits
  } R;
  struct { /* DISCORD UTILS */
    struct discord *client;
    NTL_T(ja_u64) channel_ids;
    struct discord_embed embed;
  } D;
} BOT;


void on_search(
  struct discord *client, 
  const struct discord_user *bot,
  const struct discord_message *msg)
{
  char *subreddits = NULL;
  char *msg_content = msg->content;
  if ('#' == *msg_content) {
    ++msg_content; // eat up '#'

    const char *end_srs = strchr(msg_content, ' ');
    if (!end_srs) {
      struct discord_create_message_params params = { .content = "Invalid syntax: Missing keywords" };
      discord_create_message(BOT.D.client, msg->channel_id, &params, NULL);
      return;
    }
    const size_t size = end_srs - msg_content;
    for (size_t i=0; i < size; ++i) {
      if ( !(isalnum(msg_content[i]) || '_' == msg_content[i]) && msg_content[i] != '+') {
        struct discord_create_message_params params = { 
          .content = "Invalid syntax: Subreddits must be separated with a '+'" 
        };
        discord_create_message(BOT.D.client, msg->channel_id, &params, NULL);
        return;
      }
    }
    asprintf(&subreddits, "%.*s", (int)size, msg_content);
    msg_content += size+1;
  }

  struct sized_buffer json={0};
  { // anonymous block
    struct reddit_search_params params = { .q = msg_content };
    if (subreddits) {
      params.restrict_sr = true;
      reddit_search(BOT.R.client, &params, subreddits, &json);
    }
    else {
      reddit_search(BOT.R.client, &params, "all", &json);
    }
  }

  json_item_t *root = json_parse(json.start, json.size);
  json_item_t *children = NULL;
  for (json_item_t *ji = root; ji != NULL; ji = json_iter_next(ji)) {
    if (0 == json_keycmp(ji, "children")) {
      children = ji;
      break;
    }
  }

  struct discord_create_message_params params = {0};
  if (!children) {
    params.content = "Couldn't retrieve any results";
    discord_create_message(BOT.D.client, msg->channel_id, &params, NULL);
  }
  else {
    ///@todo add check to make sure embed is not over 6000 characters
    json_item_t *title, *url;
    size_t n_size = json_size(children);
    for (size_t i=0; i < n_size; ++i) {
      title = json_get_child(json_get_byindex(children, i), "data.title");
      url = json_get_child(json_get_byindex(children, i), "data.url");
      discord_embed_add_field(
        &BOT.D.embed, 
        json_get_string(title, NULL),
        json_get_string(url, NULL),
        false);
    }
    snprintf(BOT.D.embed.description, sizeof(BOT.D.embed.description), "%zu results", n_size);
    discord_embed_set_footer(&BOT.D.embed, BOT.D.embed.description, NULL, NULL);

    params.embed = &BOT.D.embed;
    discord_create_message(BOT.D.client, msg->channel_id, &params, NULL);
  }

  json_cleanup(root);
  if (subreddits) free(subreddits);
}

void on_ready(struct discord *client, const struct discord_user *bot) {
  fprintf(stderr, "\n\nReddit-Search-Bot succesfully connected to Discord as %s#%s!\n\n",
      bot->username, bot->discriminator);
}

void refresh_reddit_access_token(void *data) {
  reddit_access_token(BOT.R.client);
}

void load_BOT(const char config_file[])
{
  struct sized_buffer json={0};
  json.start = orka_load_whole_file(SEARCH_PARAMS_FILE, &json.size);
  assert(NULL != json.start && "Missing search config file!");

  NTL_T(ja_str) ja_q=NULL;
  NTL_T(ja_str) ja_sr=NULL;
  json_extract(json.start, json.size,
      "(discord_bind_channel_ids):F" 
      "(keywords):F"
      "(restrict_sr):b"
      "(subreddits):F",
      &ja_u64_list_from_json, &BOT.D.channel_ids,
      &ja_str_list_from_json, &ja_q,
      &BOT.R.params.restrict_sr, 
      &ja_str_list_from_json, &ja_sr);
  assert(NULL != BOT.D.channel_ids && "Missing 'discord_bind_channel_ids'");
  assert(NULL != ja_q && "Missing 'keywords'");
  assert(NULL != ja_sr && "Missing 'subreddits'");

  BOT.R.params.q = \
    orka_join_strings((char**)(*ja_q), ntl_length((ntl_t)ja_q), " ", 512, 512);
  assert(NULL != BOT.R.params.q && "Missing keywords");

  BOT.R.srs = \
    orka_join_strings((char**)(*ja_sr), ntl_length((ntl_t)ja_sr), "+", 19, 1024);
  assert(NULL != BOT.R.srs && "Missing subreddits");


  /**
   * Initialize Reddit utils 
   */
  BOT.R.params.limit = 100;
  BOT.R.client = reddit_config_init(config_file);

  BOT.R.tsk_refresh_token = task_init();
  task_start(
      BOT.R.tsk_refresh_token, 
      3600000, // start 1h from now
      3600000, // refresh every 1h
      NULL, 
      &refresh_reddit_access_token);

  // get the first one immediatelly
  reddit_access_token(BOT.R.client);
  BOT.R.tsk_search = task_init();


  /**
   * Initialize Discord utils 
   */
  BOT.D.client = discord_config_init(config_file);
  discord_embed_init(&BOT.D.embed);
  BOT.D.embed.color = 0xff0000; // RED
  snprintf(BOT.D.embed.title, \
      sizeof(BOT.D.embed.title), "Reddit Search");
  discord_embed_set_thumbnail(&BOT.D.embed, EMBED_THUMBNAIL, NULL, 100, 100);
  discord_embed_set_author(
      &BOT.D.embed,
      "designed & built by https://cee.dev",
      "https://cee.dev",
      "https://cee.dev/static/images/cee.png", NULL);

#if 0
  ja_str_list_free(ja_q);
  ja_str_list_free(ja_sr);
#endif
}

void cleanup_BOT()
{
  task_cleanup(BOT.R.tsk_search);
  task_cleanup(BOT.R.tsk_refresh_token);
  free(BOT.R.params.q);
  free(BOT.R.srs);
  reddit_cleanup(BOT.R.client);
  ja_u64_list_free(BOT.D.channel_ids); 
}

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";

  load_BOT(config_file);

  discord_set_prefix(BOT.D.client, "reddit.");
  discord_set_on_command(BOT.D.client, "search", &on_search);

  discord_set_on_ready(BOT.D.client, &on_ready);
  discord_run(BOT.D.client);

  cleanup_BOT();
}
