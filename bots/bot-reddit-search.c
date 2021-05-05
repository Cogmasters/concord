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
  struct sized_buffer json; // file contents
  struct { /* REDDIT UTILS */
    struct reddit *client;
    struct task_s *tsk_refresh_token;
    struct task_s *tsk_search;
    struct reddit_search_params params;
    char *srs; // subreddits
  } R;
  struct { /* DISCORD UTILS */
    struct discord *client;
    NTL_T(u64_snowflake_t) channel_ids;
  } D;
} BOT;


struct discord_embed* 
embed_reddit_search_result(
  char *subreddits, 
  char *before,
  char *after,
  char *keywords)
{
  struct sized_buffer search_json={0};
  { // anonymous block
    struct reddit_search_params params = { 
      .q = keywords,
      .before = before,
      .after = after
    };
    if (subreddits) {
      params.restrict_sr = true;
      reddit_search(BOT.R.client, &params, subreddits, &search_json);
    }
    else {
      reddit_search(BOT.R.client, &params, "all", &search_json);
    }
  }

  struct discord_embed *embed = discord_embed_alloc();
  embed->color = 0xff0000; // RED
  snprintf(embed->title, sizeof(embed->title), "Reddit Search");
  discord_embed_set_thumbnail(embed, EMBED_THUMBNAIL, NULL, 100, 100);
  discord_embed_set_author(
      embed,
      "designed & built by https://cee.dev",
      "https://cee.dev",
      "https://cee.dev/static/images/cee.png", NULL);

  json_item_t *root = json_parse(search_json.start, search_json.size);
  json_item_t *children = json_get_child(root, "data.children");
  if (!children) return NULL;
  
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
      embed, 
      title,
      json_get_string(json_get_child(data, "url"), NULL),
      false);
  }
  snprintf(embed->description, sizeof(embed->description), "%zu results", n_size);

  char footer[EMBED_FOOTER_TEXT_LEN];
  snprintf(footer, sizeof(footer), "➡️ %s\t🔎 %s", \
      json_get_string(json_get_child(root, "data.after"), NULL), \
      keywords);
  discord_embed_set_footer(embed, footer, NULL, NULL);

  json_cleanup(root);

  return embed;
}

void on_reaction_add(
    struct discord *client,
    const struct discord_user *bot,
    const u64_snowflake_t user_id, 
    const u64_snowflake_t channel_id, 
    const u64_snowflake_t message_id, 
    const u64_snowflake_t guild_id, 
    const struct discord_guild_member *member,
    const struct discord_emoji *emoji)
{ 
  if (member->user->bot) return;

  struct discord_create_message_params params={};
  struct discord_message *msg = discord_message_alloc();

  discord_get_channel_message(client, channel_id, message_id, msg);

  if (msg->author->id == bot->id && msg->embeds) {
    char after[16]="", keywords[512]="";
    if (msg->embeds) {
      sscanf(msg->embeds[0]->footer->text, "➡️ %s\t🔎 %[^\n]", \
          after, keywords);
    }

    if (strcmp(after, "(null)") && 0 == strcmp(emoji->name, "➡️")) 
    {
      params.embed = embed_reddit_search_result(
                        NULL, 
                        NULL, 
                        after, 
                        keywords);

      if (!params.embed) {
        params.content = "Couldn't complete search";
        discord_create_message(client, channel_id, &params, NULL);
      }
      else {
        struct discord_message *ret = discord_message_alloc();

        discord_delete_message(client, channel_id, message_id);

        discord_create_message(client, channel_id, &params, ret);
        discord_create_reaction(client, channel_id, ret->id, 0, "➡️");
        discord_create_reaction(client, channel_id, ret->id, 0, "❌");

        discord_embed_free(params.embed);
        discord_message_free(ret);
      }
    }
    else if (0 == strcmp(emoji->name, "❌")) {
      discord_delete_message(client, channel_id, message_id);
    }
  }

  discord_message_free(msg);
}


void on_search(
  struct discord *client, 
  const struct discord_user *bot,
  const struct discord_message *msg)
{
  if (msg->author->bot) return;

  struct discord_create_message_params params={};

  char *subreddits=NULL, *before=NULL, *after=NULL;
  char *msg_content = msg->content;
  if ('?' == *msg_content) { // '?' means separate query from keywords
    ++msg_content; // eat up '?'
    
    // there should be a space between query string and keywords
    char *end = strchr(msg_content, ' ');
    if (!end) {
      params.content = "Invalid syntax: Missing space between query and keywords";
      discord_create_message(client, msg->channel_id, &params, NULL);
      return; /* EARLY RETURN */
    }

    // parse query variables, values and next_var (if any)
    char *var, *value, *next_var;
    do {
      var = msg_content;
      value = strchr(var, '=');
      if (!value) {
        params.content = "Invalid syntax: Missing value from query string";
        discord_create_message(client, msg->channel_id, &params, NULL);
        return; /* EARLY RETURN */
      }
      ++value; // eat up '='

      if (!(next_var = strchr(var, '&')))
        next_var = end; // last query string

      ptrdiff_t size = next_var - value;
      if (0 == strncmp(var, "srs", 3)) // subreddits
      {
        for (size_t i=0; i < size; ++i) {
          switch (value[i]) {
          default:
              if (!isalnum(value[i])) {
                params.content = "Invalid syntax: Subreddits must be separated with a '+'";
                discord_create_message(client, msg->channel_id, &params, NULL);
                return; /* EARLY RETURN */
              }
          case '_': 
          case '+':
              break;
          }
        }
        asprintf(&subreddits, "%.*s", (int)size, value);
      }
      else if (0 == strncmp(var, "before", 6))
        asprintf(&before, "%.*s", (int)size, value);
      else if (0 == strncmp(var, "after", 5))
        asprintf(&after, "%.*s", (int)size, value);
      else {
        params.content = "Invalid query command";
        discord_create_message(client, msg->channel_id, &params, NULL);
        return; /* EARLY RETURN */
      }

      msg_content = next_var+1;

    } while (msg_content < end);
  }

  params.embed = embed_reddit_search_result(
                    subreddits, 
                    before, 
                    after, 
                    msg_content);

  if (!params.embed) {
    params.content = "Couldn't complete search";
    discord_create_message(client, msg->channel_id, &params, NULL);
    return; /* EARLY RETURN */
  }

  struct discord_message *ret = discord_message_alloc();
  discord_create_message(client, msg->channel_id, &params, ret);

  if (params.embed) { // succesfully sent a embed
    discord_create_reaction(client, msg->channel_id, ret->id, 0, "➡️");
    discord_create_reaction(client, msg->channel_id, ret->id, 0, "❌");
    discord_embed_free(params.embed);
  }

  discord_message_free(ret);

  if (subreddits) 
    free(subreddits);
  if (before) 
    free(before);
  if (after) 
    free(after);
}

void on_ready(struct discord *client, const struct discord_user *bot) {
  fprintf(stderr, "\n\nReddit-Search-Bot succesfully connected to Discord as %s#%s!\n\n",
      bot->username, bot->discriminator);
}

void refresh_reddit_access_token_cb(void *data) {
  reddit_access_token(BOT.R.client);
}

void search_reddit_cb(void *data) 
{
  struct discord_embed *embed;
  embed = embed_reddit_search_result(
            BOT.R.srs, 
            BOT.R.params.before, 
            NULL, 
            BOT.R.params.q);

  if (!embed) {
    log_error("Couldn't complete search");
    return; /* EARLY RETURN */
  }

  char name[16]="";
  if (embed->fields) {
    sscanf(embed->fields[0]->name, "`%[^`]", name);
    if (BOT.R.params.before) free(BOT.R.params.before);
    BOT.R.params.before = strdup(name);
  }

  if (BOT.R.params.before && strcmp(name, BOT.R.params.before)) {
    log_error("Search couldn't fetch new results");
    discord_embed_free(embed);
    return; /* EARLY RETURN */
  }

  struct discord_message *ret = discord_message_alloc();
  struct discord_create_message_params params = { .embed = embed };
  for (size_t i=0; BOT.D.channel_ids[i]; ++i) {
    discord_create_message(BOT.D.client, *BOT.D.channel_ids[i], &params, ret);
    discord_create_reaction(BOT.D.client, *BOT.D.channel_ids[i], ret->id, 0, "➡️");
    discord_create_reaction(BOT.D.client, *BOT.D.channel_ids[i], ret->id, 0, "❌");
  }

  discord_message_free(ret);
  discord_embed_free(embed);
}

void load_BOT(const char config_file[])
{
  BOT.json.start = orka_load_whole_file(SEARCH_PARAMS_FILE, &BOT.json.size);
  assert(NULL != BOT.json.start && "Missing json file!");

  NTL_T(ja_str) ja_q=NULL;
  NTL_T(ja_str) ja_sr=NULL;
  json_extract(BOT.json.start, BOT.json.size,
      "(discord_bind_channel_ids):F" 
      "(keywords):F"
      "(subreddits):F"
      "(before):?s",
      &ja_u64_list_from_json, &BOT.D.channel_ids,
      &ja_str_list_from_json, &ja_q,
      &ja_str_list_from_json, &ja_sr,
      &BOT.R.params.before);
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
      &refresh_reddit_access_token_cb);
  // get the first one immediatelly
  reddit_access_token(BOT.R.client);

  BOT.R.tsk_search = task_init();
  task_start(
      BOT.R.tsk_search, 
      10000, // start 10s from now
      10000, // refresh every 10s
      NULL, 
      &search_reddit_cb);


  /**
   * Initialize Discord utils 
   */
  BOT.D.client = discord_config_init(config_file);

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
  ja_u64_list_free((NTL_T(ja_u64))BOT.D.channel_ids); 
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
  discord_set_on_message_reaction_add(BOT.D.client, &on_reaction_add);

  discord_set_on_ready(BOT.D.client, &on_ready);
  discord_run(BOT.D.client);

  cleanup_BOT();
}
