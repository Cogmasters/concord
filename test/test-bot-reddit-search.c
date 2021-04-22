#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "reddit.h"
#include "discord.h"

#include "json-actor.h" /* json_extract() */
#include "orka-utils.h" /* orka_load_whole_file() */
#include "scheduler.h"


#define SEARCH_PARAMS_FILE "test-bot-reddit-search.json"


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


void perform_reddit_search() 
{
  struct sized_buffer json={0};
  reddit_search(BOT.reddit.client, &BOT.reddit.params, BOT.reddit.srs, &json);
  struct discord_create_message_params params = {
    .file.name = "reddit-search.json",
    .file.size = json.size, 
    .file.content = json.start
  };

  for (size_t i=0; BOT.discord.channel_ids[i]; ++i) {
    discord_create_message(
      BOT.discord.client, 
      BOT.discord.channel_ids[i]->value, 
      &params, 
      NULL);
  }
}

void on_ready(struct discord *client, const struct discord_user *bot) 
{
  fprintf(stderr, "\n\nReddit-Search-Bot succesfully connected to Discord as %s#%s!\n\n",
      bot->username, bot->discriminator);

  task_start(
      BOT.reddit.t_search, 
      0, // start immediately
      10000, // refresh every 10s
      NULL, 
      &perform_reddit_search);
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

  discord_set_on_ready(BOT.discord.client, &on_ready);
  discord_run(BOT.discord.client);

  cleanup_BOT();
}
