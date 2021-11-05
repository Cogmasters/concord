#include <string.h>

#include "reddit.h"
#include "reddit-internal.h"

ORCAcode
reddit_search(struct reddit *client,
              struct reddit_search_params *params,
              char subreddit[],
              struct sized_buffer *p_resp_body)
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
  if (!cee_str_bounds_check(params->category, 5)) {
    log_error("'params.category' should be no longer than 5 characters");
    return ORCA_BAD_PARAMETER;
  }
  if (IS_EMPTY_STRING(params->q)) {
    log_error("Missing 'params->q'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!cee_str_bounds_check(params->q, 512)) {
    log_error("'params.q' should be no longer than 512 characters");
    return ORCA_BAD_PARAMETER;
  }
  if (!IS_EMPTY_STRING(params->show) && !STREQ(params->show, "all")) {
    log_error("'params.show' should be NULL or \"all\"");
    return ORCA_BAD_PARAMETER;
  }
  if (!IS_EMPTY_STRING(params->sort) &&
      !(STREQ(params->sort, "relevance") || STREQ(params->sort, "hot") ||
        STREQ(params->sort, "top") || STREQ(params->sort, "new") ||
        STREQ(params->sort, "comments")))
  {
    log_error(
      "'params.sort' should be one of: (relevance, hot, top, new, comments)");
    return ORCA_BAD_PARAMETER;
  }
  if (!IS_EMPTY_STRING(params->t) &&
      !(STREQ(params->t, "hour") || STREQ(params->t, "day") ||
        STREQ(params->t, "week") || STREQ(params->t, "month") ||
        STREQ(params->t, "year") || STREQ(params->t, "all")))
  {
    log_error(
      "'params.t' should be one of: (hour, day, week, month, year, all)");
    return ORCA_BAD_PARAMETER;
  }
  if (!IS_EMPTY_STRING(params->type) &&
      !(STREQ(params->type, "sr") || STREQ(params->type, "link") ||
        STREQ(params->type, "user")))
  {
    log_error("'params.type' should be one of: (sr, link, user)");
    return ORCA_BAD_PARAMETER;
  }

  if (!params->limit) // default is 25
    params->limit = 25;
  else if (params->limit > 100)
    params->limit = 100;

  char query[1024];
  size_t ret = 0;
  ret += snprintf(query, sizeof(query), "limit=%d", params->limit);
  ASSERT_S(ret < sizeof(query), "Out of bounds write attempt");

  char *q_url_encoded = url_encode(params->q);
  ret += snprintf(query + ret, sizeof(query) - ret, "&q=%s", q_url_encoded);
  ASSERT_S(ret < sizeof(query), "Out of bounds write attempt");
  free(q_url_encoded);

  if (true == params->restrict_sr) {
    ret += snprintf(query + ret, sizeof(query) - ret, "&restrict_sr=1");
    ASSERT_S(ret < sizeof(query), "Out of bounds write attempt");
  }
  if (params->t) {
    ret += snprintf(query + ret, sizeof(query) - ret, "&t=%s", params->t);
    ASSERT_S(ret < sizeof(query), "Out of bounds write attempt");
  }
  if (params->sort) {
    ret +=
      snprintf(query + ret, sizeof(query) - ret, "&sort=%s", params->sort);
    ASSERT_S(ret < sizeof(query), "Out of bounds write attempt");
  }
  if (params->before) {
    ret +=
      snprintf(query + ret, sizeof(query) - ret, "&before=%s", params->before);
    ASSERT_S(ret < sizeof(query), "Out of bounds write attempt");
  }
  if (params->after) {
    ret +=
      snprintf(query + ret, sizeof(query) - ret, "&after=%s", params->after);
    ASSERT_S(ret < sizeof(query), "Out of bounds write attempt");
  }

  return reddit_adapter_run(&client->adapter, p_resp_body, NULL, HTTP_GET,
                            "/r/%s/search.json?raw_json=1%s", subreddit,
                            query);
}
