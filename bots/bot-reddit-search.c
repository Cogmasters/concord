#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "reddit.h"
#include "discord.h"

#include "json-actor.h" /* json_extract() */
#include "orka-utils.h" /* orka_load_whole_file() */
#include "scheduler.h"


#define SEARCH_PARAMS_FILE "bot-reddit-search.json"
#define EMBED_THUMBNAIL \
  "https://external-preview.redd.it/ei2UEblhohs09-oGeS6Ws14T2pOd37GN1_1VUzisvZE.png?auto=webp&s=9fc63c64245f6aa267d712c8b4ad885aa5555b7b"


/* Read-Only after load_BOT */
struct {
  struct {
    struct reddit *client;
    struct task_s *t_refresh_token;
    struct task_s *t_search;
    struct reddit_search_params params;
    char *srs; // subreddits
  } reddit;
  struct {
    struct discord *client;
    NTL_T(ja_u64) channel_ids;
  } discord;
} BOT;


void on_search(
  struct discord *client, 
  const struct discord_user *bot,
  const struct discord_message *msg)
{
  struct sized_buffer json={0};
  {
    struct reddit_search_params params = { .q = msg->content };
    reddit_search(BOT.reddit.client, &params, "all", &json);
  }

  json_item_t *root = json_parse(json.start, json.size);

  json_item_t *children=0;
  for (json_item_t *ji = root; ji != NULL; ji = json_iter_next(ji)) {
    if (0 == json_keycmp(ji, "children")) {
      children = ji;
      break;
    }
  }

  struct discord_create_message_params params = {0};
  if (!children) {
    params.content = "Couldn't retrieve any results";
    discord_create_message(BOT.discord.client, msg->channel_id, &params, NULL);
  }
  else {
    struct discord_embed embed;
    discord_embed_init(&embed);
    embed.color = 0xff0000; // RED
    snprintf(embed.title, sizeof(embed.title), "Reddit Search");
    discord_embed_set_thumbnail(&embed, EMBED_THUMBNAIL, NULL, 100, 100);
    discord_embed_set_author(&embed,
        "designed & built by https://cee.dev",
        "https://cee.dev",
        "https://cee.dev/static/images/cee.png", NULL);

    ///@todo add check to make sure embed is not over 6000 characters
    json_item_t *title, *url;
    size_t n_size = json_size(children);
    for (size_t i=0; i < n_size; ++i) {
      title = json_get_child(json_get_byindex(children, i), "data.title");
      url = json_get_child(json_get_byindex(children, i), "data.url");
      discord_embed_add_field(
        &embed, 
        json_get_string(title, NULL),
        json_get_string(url, NULL),
        false);
    }
    snprintf(embed.description, sizeof(embed.description), "%zu results", n_size);
    discord_embed_set_footer(&embed, embed.description, NULL, NULL);

    params.embed = &embed;
    discord_create_message(BOT.discord.client, msg->channel_id, &params, NULL);
  }

  json_cleanup(root);
}

void on_ready(struct discord *client, const struct discord_user *bot) 
{
  fprintf(stderr, "\n\nReddit-Search-Bot succesfully connected to Discord as %s#%s!\n\n",
      bot->username, bot->discriminator);
}

void refresh_reddit_access_token(void *data) {
  reddit_access_token(BOT.reddit.client);
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
      &ja_u64_list_from_json, &BOT.discord.channel_ids,
      &ja_str_list_from_json, &ja_q,
      &BOT.reddit.params.restrict_sr, 
      &ja_str_list_from_json, &ja_sr);
  assert(NULL != BOT.discord.channel_ids && "Missing 'discord_bind_channel_ids'");
  assert(NULL != ja_q && "Missing 'keywords'");
  assert(NULL != ja_sr && "Missing 'subreddits'");

  BOT.reddit.params.q = orka_cat_strings(
                          (char**)(*ja_q), 
                          ntl_length((ntl_t)ja_q), 
                          " ", 
                          512, 
                          512);
  assert(NULL != BOT.reddit.params.q && "Missing keywords");

  BOT.reddit.srs = orka_cat_strings(
                            (char**)(*ja_sr), 
                            ntl_length((ntl_t)ja_sr), 
                            "+", 
                            19,
                            1024);
  assert(NULL != BOT.reddit.srs && "Missing subreddits");

  BOT.reddit.params.limit = 100;
  BOT.reddit.client = reddit_config_init(config_file);

  BOT.reddit.t_refresh_token = task_init();
  task_start(
      BOT.reddit.t_refresh_token, 
      3600000, // start 1h from now
      3600000, // refresh every 1h
      NULL, 
      &refresh_reddit_access_token);

  // get the first one immediatelly
  reddit_access_token(BOT.reddit.client);

  BOT.reddit.t_search = task_init();

  BOT.discord.client = discord_config_init(config_file);

#if 0
  ja_str_list_free(ja_q);
  ja_str_list_free(ja_sr);
#endif
}

void cleanup_BOT()
{
  task_cleanup(BOT.reddit.t_search);
  task_cleanup(BOT.reddit.t_refresh_token);
  free(BOT.reddit.params.q);
  free(BOT.reddit.srs);
  reddit_cleanup(BOT.reddit.client);
  ja_u64_list_free(BOT.discord.channel_ids); 
}

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";

  load_BOT(config_file);

  discord_set_prefix(BOT.discord.client, "reddit.");
  discord_set_on_command(BOT.discord.client, "search", &on_search);

  discord_set_on_ready(BOT.discord.client, &on_ready);
  discord_run(BOT.discord.client);

  cleanup_BOT();
}
