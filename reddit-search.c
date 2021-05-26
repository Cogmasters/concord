#include <string.h>

#include "reddit.h"
#include "reddit-internal.h"


ORCAcode
reddit_search(
  struct reddit *client, 
  struct reddit_search_params *params, 
  char subreddit[], 
  struct sized_buffer *p_json)
{
  if (IS_EMPTY_STRING(subreddit)) {
    log_error("Missing 'subreddit'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    log_error("Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }
  if (params->after && params->before) {
    log_error("Can't have both 'params.after' and 'params.before'");
    return ORCA_BAD_PARAMETER;
  }
  if (!orka_str_bounds_check(params->category, 5)) {
    log_error("'params.category' should be no longer than 5 characters");
    return ORCA_BAD_PARAMETER;
  }
  if (!orka_str_bounds_check(params->q, 512)) {
    log_error("'params.q' should be no longer than 512 characters");
    return ORCA_BAD_PARAMETER;
  }
  if (!IS_EMPTY_STRING(params->show) && !STREQ(params->show, "all")) {
    log_error("'params.show' should be NULL or \"all\"");
    return ORCA_BAD_PARAMETER;
  }
  if (!IS_EMPTY_STRING(params->sort)
      && !(STREQ(params->sort, "relevance")
         || STREQ(params->sort, "hot")
         || STREQ(params->sort, "top")
         || STREQ(params->sort, "new")
         || STREQ(params->sort, "comments")))
  {
    log_error("'params.sort' should be one of: (relevance, hot, top, new, comments)");
    return ORCA_BAD_PARAMETER;
  }
  if (IS_EMPTY_STRING(params->q)) {
    log_error("Missing 'params->q'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!IS_EMPTY_STRING(params->t)
      && !(STREQ(params->t, "hour")
         || STREQ(params->t, "day")
         || STREQ(params->t, "week")
         || STREQ(params->t, "month")
         || STREQ(params->t, "year")
         || STREQ(params->t, "all")))
  {
    log_error("'params.t' should be one of: (hour, day, week, month, year, all)");
    return ORCA_BAD_PARAMETER;
  }
  if (!IS_EMPTY_STRING(params->type)
      && !(STREQ(params->type, "sr")
         || STREQ(params->type, "link")
         || STREQ(params->type, "user")))
  {
    log_error("'params.type' should be one of: (sr, link, user)");
    return ORCA_BAD_PARAMETER;
  }

  if (!params->limit) // default is 25
    params->limit = 25;
  else if (params->limit > 100)
    params->limit = 100;

  char limit_query[64];
  snprintf(limit_query, sizeof(limit_query),
      "&limit=%d", params->limit);
  char restrict_sr_query[32] = "";
  if (true == params->restrict_sr) {
    snprintf(restrict_sr_query, sizeof(restrict_sr_query),
        "&restrict_sr=1");
  }
  char q_query[600] = "";
  if (params->q) {
    char *q_url_encoded = url_encode(params->q);
    snprintf(q_query, sizeof(q_query),
        "&q=%s", q_url_encoded);
    free(q_url_encoded);
  }
  char t_query[32] = "";
  if (params->t) {
    snprintf(t_query, sizeof(t_query),
        "&t=%s", params->t);
  }
  char sort_query[32] = "";
  if (params->sort) {
    snprintf(sort_query, sizeof(sort_query),
        "&sort=%s", params->sort);
  }
  char before_query[32] = "";
  if (params->before) {
    snprintf(before_query, sizeof(before_query),
        "&before=%s", params->before);
  }
  char after_query[32] = "";
  if (params->after) {
    snprintf(after_query, sizeof(after_query),
        "&after=%s", params->after);
  }

  return reddit_adapter_run(
    &client->adapter,
    p_json,
    NULL,
    HTTP_GET, "/r/%s/search.json?raw_json=1%s%s%s%s%s%s%s", 
    subreddit, limit_query, restrict_sr_query, q_query, t_query, sort_query, before_query, after_query);
}
