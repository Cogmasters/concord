#define _GNU_SOURCE /* asprintf() */
#include <string.h>

#include "reddit.h"
#include "reddit-internal.h"


static void
get_json(char *str, size_t len, void *p_json)
{
  struct sized_buffer *json = p_json;
  asprintf(&json->start, "%.*s", (int)len, str);
  json->size = len;
}

void
reddit_search(
  struct reddit *client, 
  struct reddit_search_params *params, 
  char subreddit[], 
  struct sized_buffer *p_json)
{
  if (orka_str_bounds_check(subreddit, 19) <= 0) {
    log_error("Missing 'subreddit' or over 19 characters threshold");
    return;
  }
  if (params->after && params->before) {
    log_error("Can't have both 'params.after' and 'params.before'");
    return;
  }
  if (!orka_str_bounds_check(params->category, 5)) {
    log_error("'params.category' should be no longer than 5 characters");
    return;
  }
  if (!orka_str_bounds_check(params->q, 512)) {
    log_error("'params.q' should be no longer than 512 characters");
    return;
  }
  if (!IS_EMPTY_STRING(params->show) && !STREQ(params->show, "all")) {
    log_error("'params.show' should be NULL or \"all\"");
    return;
  }
  if (IS_EMPTY_STRING(params->sort)
      || (!STREQ(params->sort, "relevance")
         && !STREQ(params->sort, "hot")
         && !STREQ(params->sort, "top")
         && !STREQ(params->sort, "new")
         && !STREQ(params->sort, "comments")))
  {
    log_error("'params.sort' should be one of: (relevance, hot, top, new, comments)");
    return;
  }
  if (IS_EMPTY_STRING(params->q)) {
    log_error("Missing 'params->q'");
    return;
  }
  if (IS_EMPTY_STRING(params->t)
      || (!STREQ(params->t, "hour")
         && !STREQ(params->t, "day")
         && !STREQ(params->t, "week")
         && !STREQ(params->t, "month")
         && !STREQ(params->t, "year")
         && !STREQ(params->t, "all")))
  {
    log_error("'params.t' should be one of: (hour, day, week, month, year, all)");
    return;
  }
  if (!IS_EMPTY_STRING(params->type)
      && (!STREQ(params->type, "sr")
         || !STREQ(params->type, "link")
         || !STREQ(params->type, "user")))
  {
    log_error("'params.type' should be one of: (sr, link, user)");
    return;
  }

  if (!params->limit) // default is 25
    params->limit = 25;
  else if (params->limit > 100)
    params->limit = 100;

  char query[1024];
  int ret = query_inject(query, sizeof(query),
              "(after):s"
              "(before):s"
              "(category):s"
              "(count):d"
              "(include_facets):b"
              "(limit):d"
              "(q):s"
              "(restrict_sr):b"
              "(show):s"
              "(sort):s"
              "(sr_detail):s"
              "(t):s"
              "(type):s", 
              params->after,
              params->before,
              params->category,
              &params->count,
              &params->include_facets,
              &params->limit,
              params->q,
              &params->restrict_sr,
              params->show,
              params->sort,
              params->sr_detail,
              params->t,
              params->type);
  ASSERT_S(ret < sizeof(query), "Out of bounds write attempt");

  struct ua_resp_handle resp_handle = {
    .ok_cb = p_json ? &get_json : NULL,
    .ok_obj = p_json,
  };

  reddit_adapter_run(
    &client->adapter,
    &resp_handle,
    NULL,
    HTTP_GET, "/r/%s/search.json%s", subreddit, query);
}
