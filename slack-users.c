#include <string.h>

#include "slack.h"
#include "slack-internal.h"

ORCAcode
slack_users_info(struct slack *client,
                 struct slack_users_info_params *params,
                 struct sized_buffer *p_resp_body)
{
  if (!params) {
    log_error("Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }
  if (IS_EMPTY_STRING(params->user)) {
    log_error("Missing 'params.user'");
    return ORCA_MISSING_PARAMETER;
  }

  char query[4096];
  size_t ret = 0;

  ret += snprintf(query + ret, sizeof(query) - ret, "user=%s", params->user);
  ASSERT_S(ret < sizeof(query), "Out of bounds write attempt");
  if (params->token) {
    ret +=
      snprintf(query + ret, sizeof(query) - ret, "&token=%s", params->token);
    ASSERT_S(ret < sizeof(query), "Out of bounds write attempt");
  }
  if (params->include_locale) {
    ret += snprintf(query + ret, sizeof(query) - ret, "&include_locale=true");
    ASSERT_S(ret < sizeof(query), "Out of bounds write attempt");
  }

  return slack_webapi_run(&client->webapi, p_resp_body,
                          &(struct sized_buffer){ query, ret }, HTTP_POST,
                          "/users.info");
}
