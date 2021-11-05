#define _GNU_SOURCE /* asprintf() */
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* strchr() */
#include <ctype.h> /* isalnum() */
#include <assert.h>

#include "reddit.h"
#include "discord.h"

#include "json-actor.h" /* json_extract() */
#include "cee-utils.h" /* cee_load_whole_file() */
#include "scheduler.h"

#define SEARCH_PARAMS_FILE "bot-reddit.json"
#define EMBED_THUMBNAIL                                                       \
  "https://external-preview.redd.it/"                                         \
  "ei2UEblhohs09-oGeS6Ws14T2pOd37GN1_1VUzisvZE.png?auto=webp&s="              \
  "9fc63c64245f6aa267d712c8b4ad885aa5555b7b"

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

void on_ready(struct discord *client, const struct discord_user *bot)
{
  log_info("Reddit-Bot succesfully connected to Discord as %s#%s!",
           bot->username, bot->discriminator);
}

struct discord_embed *embed_reddit_search_result(
  char subreddits[], char before[], char after[], char sort[], char keywords[])
{
  struct sized_buffer resp_body = { 0 };
  ORCAcode code;

  if (!subreddits || !*subreddits) subreddits = "all";

  code = reddit_search(BOT.R.client,
                       &(struct reddit_search_params){
                         .q = (keywords && *keywords) ? keywords : NULL,
                         .before = (before && *before) ? before : NULL,
                         .after = (after && *after) ? after : NULL,
                         .sort = (sort && *sort) ? sort : NULL,
                         .restrict_sr = (strcmp(subreddits, "all") != 0) },
                       subreddits, &resp_body);

  struct discord_embed *embed = malloc(sizeof *embed);
  discord_embed_init(embed);

  embed->color = 0xff0000; // RED
  discord_embed_set_title(embed, "Reddit Search");
  discord_embed_set_thumbnail(embed, EMBED_THUMBNAIL, NULL, 100, 100);
  discord_embed_set_author(embed, "designed & built by https://cee.dev",
                           "https://cee.dev",
                           "https://cee.dev/static/images/cee.png", NULL);

  json_item_t *root = json_parse(resp_body.start, resp_body.size);
  json_item_t *children = json_get_child(root, "data.children");
  if (!children) return NULL;

  json_item_t *data;
  char title[DISCORD_EMBED_TITLE_LEN];
  char permalink[DISCORD_EMBED_FIELD_VALUE_LEN];
  size_t n_size = json_size(children);
  for (size_t i = 0; i < n_size; ++i) {
    data = json_get_child(json_get_byindex(children, i), "data");
    snprintf(title, sizeof(title), "%s",
             json_get_string(json_get_child(data, "title"), NULL));
    snprintf(permalink, sizeof(permalink), "https://reddit.com%s",
             json_get_string(json_get_child(data, "permalink"), NULL));
    discord_embed_add_field(embed, title, permalink, false);
  }
  discord_embed_set_description(embed, "%zu results", n_size);

  char footer[DISCORD_EMBED_FOOTER_TEXT_LEN];
  snprintf(footer, sizeof(footer), "🔎 %s\t🔗 %s", keywords, subreddits);
  discord_embed_set_footer(embed, footer, NULL, NULL);

  json_cleanup(root);

  return embed;
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
  if (member->user->bot) return;

  struct discord_create_message_params params = { 0 };
  struct discord_message msg;
  discord_message_init(&msg);

  discord_get_channel_message(client, channel_id, message_id, &msg);

  if (msg.author->id == bot->id && msg.embeds) {
    char keywords[512] = "", subreddits[1024] = "";
    struct discord_embed *embed = msg.embeds[0];
    if (!embed->fields) {
      discord_message_cleanup(&msg);
      return; /* EARLY RETURN */
    }
    sscanf(embed->footer->text, "🔎 %[^\t]\t🔗 %[^\n]", keywords, subreddits);

    if (0 == strcmp(emoji->name, "⬅️")) {
      char before[16] = "t3_";
      sscanf(embed->fields[0]->value,
             "https://reddit.com/r/%*[^/]/comments/%[^/]",
             &before[sizeof("t3_") - 1]);

      params.embed = embed_reddit_search_result(subreddits, before, NULL,
                                                "relevance", keywords);

      if (!params.embed) {
        params.content = "Couldn't complete search";
        discord_create_message(client, channel_id, &params, NULL);
      }
      else {
        struct discord_message ret;
        discord_message_init(&ret);

        discord_delete_message(client, channel_id, message_id);

        discord_create_message(client, channel_id, &params, &ret);
        discord_create_reaction(client, channel_id, ret.id, 0, "⬅️");
        discord_create_reaction(client, channel_id, ret.id, 0, "➡️");
        discord_create_reaction(client, channel_id, ret.id, 0, "❌");

        discord_embed_cleanup(params.embed);
        free(params.embed);

        discord_message_cleanup(&ret);
      }
    }
    else if (0 == strcmp(emoji->name, "➡️")) {
      size_t len = ntl_length((ntl_t)embed->fields);
      char after[16] = "t3_";
      sscanf(embed->fields[len - 1]->value,
             "https://reddit.com/r/%*[^/]/comments/%[^/]",
             &after[sizeof("t3_") - 1]);

      params.embed = embed_reddit_search_result(subreddits, NULL, after,
                                                "relevance", keywords);

      if (!params.embed) {
        params.content = "Couldn't complete search";
        discord_create_message(client, channel_id, &params, NULL);
      }
      else {
        struct discord_message ret;
        discord_message_init(&ret);

        discord_delete_message(client, channel_id, message_id);

        discord_create_message(client, channel_id, &params, &ret);
        discord_create_reaction(client, channel_id, ret.id, 0, "⬅️");
        discord_create_reaction(client, channel_id, ret.id, 0, "➡️");
        discord_create_reaction(client, channel_id, ret.id, 0, "❌");

        discord_embed_cleanup(params.embed);
        free(params.embed);

        discord_message_cleanup(&ret);
      }
    }
    else if (0 == strcmp(emoji->name, "❌")) {
      discord_delete_message(client, channel_id, message_id);
    }
  }

  discord_message_cleanup(&msg);
}

void on_search(struct discord *client,
               const struct discord_user *bot,
               const struct discord_message *msg)
{
  if (msg->author->bot) return;

  struct discord_create_message_params params = { 0 };

  char subreddits[1024] = "", before[16] = "", after[16] = "";
  char *msg_content = msg->content;
  if ('?' == *msg_content) { // '?' means separate query from keywords
    ++msg_content; // eat up '?'

    // there should be a space between query string and keywords
    char *query_end = strchr(msg_content, ' ');
    if (!query_end) {
      params.content =
        "Invalid syntax: Missing space between query and keywords";
      discord_create_message(client, msg->channel_id, &params, NULL);
      return; /* EARLY RETURN */
    }

    // parse query variables, values and next_var (if any)
    char *query_var, *query_value, *query_next_var;
    do {
      query_var = msg_content;
      query_value = strchr(query_var, '=');
      if (!query_value) {
        params.content = "Invalid syntax: Missing value from query string";
        discord_create_message(client, msg->channel_id, &params, NULL);
        return; /* EARLY RETURN */
      }
      ++query_value; // eat up '='

      if (!(query_next_var = strchr(query_var, '&')))
        query_next_var = query_end; // last query string

      ptrdiff_t query_size = query_next_var - query_value;
      if (0 == strncmp(query_var, "srs", 3)) // subreddits
      {
        for (size_t i = 0; i < query_size; ++i) {
          switch (query_value[i]) {
          default:
            if (!isalnum(query_value[i])) {
              params.content =
                "Invalid syntax: Subreddits must be separated with a '+'";
              discord_create_message(client, msg->channel_id, &params, NULL);
              return; /* EARLY RETURN */
            }
          case '_':
          case '+': break;
          }
        }
        snprintf(subreddits, sizeof(subreddits), "%.*s", (int)query_size,
                 query_value);
      }
      else if (0 == strncmp(query_var, "before", 6))
        snprintf(before, sizeof(before), "%.*s", (int)query_size, query_value);
      else if (0 == strncmp(query_var, "after", 5))
        snprintf(after, sizeof(after), "%.*s", (int)query_size, query_value);
      else {
        params.content = "Invalid query command";
        discord_create_message(client, msg->channel_id, &params, NULL);
        return; /* EARLY RETURN */
      }

      msg_content = query_next_var + 1;

    } while (msg_content < query_end);
  }

  params.embed = embed_reddit_search_result(subreddits, before, after,
                                            "relevance", msg_content);

  if (!params.embed) {
    params.content = "Couldn't complete search";
    discord_create_message(client, msg->channel_id, &params, NULL);
    return; /* EARLY RETURN */
  }

  struct discord_message ret;
  discord_message_init(&ret);

  discord_create_message(client, msg->channel_id, &params, &ret);

  if (params.embed) { // succesfully sent a embed
    discord_create_reaction(client, msg->channel_id, ret.id, 0, "⬅️");
    discord_create_reaction(client, msg->channel_id, ret.id, 0, "➡️");
    discord_create_reaction(client, msg->channel_id, ret.id, 0, "❌");
    discord_embed_cleanup(params.embed);
    free(params.embed);
  }

  discord_message_cleanup(&ret);
}

void refresh_reddit_access_token_cb(void *data)
{
  struct sized_buffer resp_body = { 0 };
  struct reddit_access_token_params params = { .grant_type = "refresh_token" };
  reddit_access_token(BOT.R.client, &params, &resp_body);
}

void search_reddit_cb(void *data)
{
  struct discord_embed *embed;
  embed = embed_reddit_search_result(BOT.R.srs, BOT.R.params.before, NULL,
                                     BOT.R.params.sort, BOT.R.params.q);

  if (!embed || !embed->fields) {
    log_error("Couldn't complete search");
    return; /* EARLY RETURN */
  }

  char before[16] = "";
  sscanf(embed->fields[0]->value, "https://reddit.com/r/%*[^/]/comments/%[^/]",
         before);

  if (BOT.R.params.before) {
    if (strcmp(before, BOT.R.params.before)) {
      log_trace("Search couldn't fetch new results");
      discord_embed_cleanup(embed);
      free(embed);
      return; /* EARLY RETURN */
    }
    free(BOT.R.params.before);
  }
  asprintf(&BOT.R.params.before, "t3_%s", before);

  struct discord_message ret;
  discord_message_init(&ret);

  struct discord_create_message_params params = { .embed = embed };
  for (size_t i = 0; BOT.D.channel_ids[i]; ++i) {
    discord_create_message(BOT.D.client, *BOT.D.channel_ids[i], &params, &ret);
    discord_create_reaction(BOT.D.client, *BOT.D.channel_ids[i], ret.id, 0,
                            "⬅️");
    discord_create_reaction(BOT.D.client, *BOT.D.channel_ids[i], ret.id, 0,
                            "➡️");
    discord_create_reaction(BOT.D.client, *BOT.D.channel_ids[i], ret.id, 0,
                            "❌");
  }

  discord_message_cleanup(&ret);
  discord_embed_cleanup(embed);
  free(embed);
}

void on_comment(struct discord *client,
                const struct discord_user *bot,
                const struct discord_message *msg)
{
  if (msg->author->bot) return;

  char *delim = strchr(msg->content, ' ');
  if (!delim) return;

  char thing_id[16] = { 0 };
  memcpy(thing_id, msg->content, delim - msg->content);

  struct reddit_comment_params params = { .text = delim + 1,
                                          .thing_id = thing_id,
                                          .api_type = "json" };
  reddit_comment(BOT.R.client, &params, NULL);
}

void load_BOT(const char config_file[])
{
  BOT.json.start = cee_load_whole_file(SEARCH_PARAMS_FILE, &BOT.json.size);
  assert(NULL != BOT.json.start && "Missing json file!");

  bool enable = false;
  int refresh_seconds = 0;
  NTL_T(ja_str) ja_q = NULL;
  NTL_T(ja_str) ja_sr = NULL;
  json_extract(BOT.json.start, BOT.json.size,
               "(enable):b"
               "(refresh_seconds):d"
               "(sort):?s"
               "(discord_bind_channel_ids):F"
               "(keywords):F"
               "(subreddits):F"
               "(before):?s",
               &enable, &refresh_seconds, &BOT.R.params.sort,
               &ja_u64_list_from_json, &BOT.D.channel_ids,
               &ja_str_list_from_json, &ja_q, &ja_str_list_from_json, &ja_sr,
               &BOT.R.params.before);
  assert(NULL != BOT.D.channel_ids && "Missing 'discord_bind_channel_ids'");
  assert(NULL != ja_q && "Missing 'keywords'");

  BOT.R.params.q =
    cee_join_strings((char **)(*ja_q), ntl_length((ntl_t)ja_q), " ", 512, 512);
  assert(NULL != BOT.R.params.q && "Missing keywords");

  if (ja_sr) {
    BOT.R.srs = cee_join_strings((char **)(*ja_sr), ntl_length((ntl_t)ja_sr),
                                 "+", 19, 1024);
    assert(NULL != BOT.R.srs && "Missing subreddits");
  }

  /**
   * Initialize Discord utils
   */
  BOT.D.client = discord_config_init(config_file);

  /**
   * Initialize Reddit utils
   */
  BOT.R.params.limit = 100;
  BOT.R.client = reddit_config_init(config_file);

  BOT.R.tsk_refresh_token = task_init();
  task_start(BOT.R.tsk_refresh_token,
             3600000, // start 1h from now
             3600000, // refresh every 1h
             NULL, &refresh_reddit_access_token_cb);
  // get the first one immediately
  struct sized_buffer resp_body = { 0 };
  struct reddit_access_token_params params = { .grant_type = "password" };
  reddit_access_token(BOT.R.client, &params, &resp_body);
  log_debug("%.*s", (int)resp_body.size, resp_body.start);

  if (true == enable) {
    BOT.R.tsk_search = task_init();
    task_start(BOT.R.tsk_search,
               10000, // start 10s from now
               refresh_seconds * 1000, NULL, &search_reddit_cb);
  }

  ja_str_list_free(ja_q);
  ja_str_list_free(ja_sr);
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

enum discord_event_scheduler scheduler(struct discord *client,
                                       struct discord_user *bot,
                                       struct sized_buffer *event_data,
                                       enum discord_gateway_events event)
{
  return DISCORD_EVENT_WORKER_THREAD;
}

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "../config.json";

  printf(
    "\n\nThis bot demonstrates how easy it is to have two distinct"
    " APIs interacting with eachother (Reddit + Discord).\n"
    "1. Type reddit.search<?query> <keywords> \n"
    "\tEx1: reddit.search Hello everyone!\n"
    "\tEx2: reddit.search?srs=CryptoCurrency+dogecoin dogecoin made me poor\n"
    "\tEx3: reddit.search?srs=c_programming&before=t_a1234 Segfault\n"
    "2. Edit bot-reddit.json to enable auto-search mode \n"
    "\t2.1. enable: enable auto-search mode\n"
    "\t2.2. refresh_seconds: interval when bot should perform search\n"
    "\t2.3. sort: sort results by [new, hot, comments, relevance] \n"
    "\t2.4. discord_bind_channel_ids: array of channel ids the search results "
    "will be output to \n"
    "\t2.5. keywords: array of keywords that will be searched for\n"
    "\t2.6. subreddits: array of subreddits for lookup (leave null to include "
    "all)\n"
    "\t2.7. before: show results before a certain message ID\n"
    "3. Type reddit.comment <thing_id> <text> to comment to some post \n"
    "\tEx1: reddit.comment t3_15bfi0 Hello there!\n"
    "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input

  load_BOT(config_file);

  /* trigger event callbacks in a multi-threaded fashion */
  discord_set_event_scheduler(BOT.D.client, &scheduler);

  discord_set_on_ready(BOT.D.client, &on_ready);

  discord_set_prefix(BOT.D.client, "reddit.");
  discord_set_on_command(BOT.D.client, "search", &on_search);
  discord_set_on_message_reaction_add(BOT.D.client, &on_reaction_add);
  discord_set_on_command(BOT.D.client, "comment", &on_comment);

  discord_run(BOT.D.client);

  cleanup_BOT();
}
