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
    char before[16];
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
  char *start = msg->content;
  struct discord_create_message_params params = {0};

  char *subreddits=NULL, *before=NULL, *after=NULL;
  if ('?' == *start) { // '?' means query string attached
    ++start; // eat up '?'
    
    // there should be a space between query string and keywords
    char *end = strchr(start, ' ');
    if (!end) {
      params.content = "Invalid syntax: Missing space between query and keywords";
      goto _send_msg;
    }

    // parse query variables, values and next (if any)
    char *var, *value, *next;
    do {
      var = start;
      value = strchr(var, '=');
      if (!value) {
        params.content = "Invalid syntax: Missing value from query string";
        goto _send_msg;
      }
      ++value; // eat up '='

      if (!(next = strchr(var, '&')))
        next = end; // last query string

      ptrdiff_t size = next-value;
      if (0 == strncmp(var, "srs", 3)) // subreddits
      {
        for (size_t i=0; i < size; ++i) {
          switch (value[i]) {
          default:
              if (!isalnum(value[i])) {
                params.content = "Invalid syntax: Subreddits must be separated with a '+'";
                goto _send_msg;
              }
          case '_': 
          case '+':
              break;
          }
        }
        asprintf(&subreddits, "%.*s", (int)size, value);
      }
      else if (0 == strncmp(var, "before", 6)) {
        asprintf(&before, "%.*s", (int)size, value);
      }
      else if (0 == strncmp(var, "after", 5)) {
        asprintf(&after, "%.*s", (int)size, value);
      }
      else {
        params.content = "Invalid query command";
        goto _send_msg;
      }

      start = next+1;

    } while (start < end);
  }

  struct sized_buffer json={0};
  { // anonymous block
    struct reddit_search_params params = { 
      .q = start,
      .before = before ? before : NULL,
      .after = after ? after : NULL
    };
    if (subreddits) {
      params.restrict_sr = true;
      reddit_search(BOT.R.client, &params, subreddits, &json);
    }
    else {
      reddit_search(BOT.R.client, &params, "all", &json);
    }
  }

  json_item_t *root = json_parse(json.start, json.size);
  json_item_t *children = json_get_child(root, "data.children");
  if (!children) {
    params.content = "Couldn't retrieve any results";
    goto _send_msg;
  }
  else {
    ///@todo add check to make sure embed is not over 6000 characters
    json_item_t *data;
    char title[EMBED_TITLE_LEN + 1]; // +1 to trigger auto-truncation
    size_t n_size = json_size(children);
    for (size_t i=0; i < n_size; ++i) {
      data = json_get_child(json_get_byindex(children, i), "data");
      snprintf(title, sizeof(title), "`%s` %s", \
          json_get_string(json_get_child(data, "name"), NULL), 
          json_get_string(json_get_child(data, "title"), NULL));

      discord_embed_add_field(
        &BOT.D.embed, 
        title,
        json_get_string(json_get_child(data, "url"), NULL),
        false);
    }
    snprintf(BOT.D.embed.description, sizeof(BOT.D.embed.description), "%zu results", n_size);
    discord_embed_set_footer(&BOT.D.embed, BOT.D.embed.description, NULL, NULL);

    params.embed = &BOT.D.embed;
  }

  json_cleanup(root);

_send_msg:
  discord_create_message(BOT.D.client, msg->channel_id, &params, NULL);

  if (subreddits) free(subreddits);
  if (before) free(before);
  if (after) free(after);
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
