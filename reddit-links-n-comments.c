#define _GNU_SOURCE /* asprintf() */
#include <string.h>

#include "reddit.h"
#include "reddit-internal.h"

ORCAcode
reddit_comment(struct reddit *client,
               struct reddit_comment_params *params,
               struct sized_buffer *p_resp_body)
{
  if (!params) {
    log_error("Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params->text) {
    log_error("Missing 'params.text'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params->thing_id) {
    log_error("Missing 'params.thing_id'");
    return ORCA_MISSING_PARAMETER;
  }

  char query[4096];
  size_t ret = 0;

  char *text_url_encoded = url_encode(params->text);
  ret += snprintf(query, sizeof(query), "text=%s", text_url_encoded);
  ASSERT_S(ret < sizeof(query), "Out of bounds write attempt");
  free(text_url_encoded);

  ret += snprintf(query + ret, sizeof(query) - ret, "&thing_id=%s",
                  params->thing_id);
  ASSERT_S(ret < sizeof(query), "Out of bounds write attempt");

  if (params->api_type) {
    ret += snprintf(query + ret, sizeof(query) - ret, "&api_type=%s",
                    params->api_type);
    ASSERT_S(ret < sizeof(query), "Out of bounds write attempt");
  }
  if (params->return_rtjson) {
    ret += snprintf(query + ret, sizeof(query) - ret, "&return_rtjson=%d",
                    params->return_rtjson);
    ASSERT_S(ret < sizeof(query), "Out of bounds write attempt");
  }
  if (params->richtext_json) {
    ret += snprintf(query + ret, sizeof(query) - ret, "&richtext_json=%s",
                    params->richtext_json);
    ASSERT_S(ret < sizeof(query), "Out of bounds write attempt");
  }
  if (params->uh) {
    ret += snprintf(query + ret, sizeof(query) - ret, "&uh=%s", params->uh);
    ASSERT_S(ret < sizeof(query), "Out of bounds write attempt");
  }

  return reddit_adapter_run(&client->adapter, p_resp_body,
                            &(struct sized_buffer){ query, ret }, HTTP_POST,
                            "/api/comment");
}
