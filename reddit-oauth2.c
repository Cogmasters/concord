#include <string.h>

#include "reddit.h"
#include "reddit-internal.h"


ORCAcode
reddit_access_token(
  struct reddit *client,
  struct reddit_access_token_params *params,
  struct sized_buffer *p_resp_body)
{
  if (!params) {
    log_error("Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params->grant_type) {
    log_error("Missing 'params.grant_type'");
    return ORCA_MISSING_PARAMETER;
  }

  char query[1024];
  size_t ret=0;
  ret += snprintf(query, sizeof(query), "?grant_type=%s", params->grant_type);
  ASSERT_S(ret < sizeof(query), "Out of bounds write attempt");

  if (STREQ(params->grant_type, "password")) { // script apps
    if (IS_EMPTY_STRING(params->username)) {
      if (!client->username.size) {
        log_error("Missing 'params.username'");
        return ORCA_MISSING_PARAMETER;
      }
      ret += snprintf(query+ret, sizeof(query)-ret, \
               "&username=%.*s", (int)client->username.size, client->username.start);
    }
    else {
      ret += snprintf(query+ret, sizeof(query)-ret, "&username=%s", params->username);
    }

    if (IS_EMPTY_STRING(params->password)) {
      if (!client->password.size) {
        log_error("Missing 'params.password'");
        return ORCA_MISSING_PARAMETER;
      }
      ret += snprintf(query+ret, sizeof(query)-ret, \
               "&password=%.*s", (int)client->password.size, client->password.start);
    }
    else {
      ret += snprintf(query+ret, sizeof(query)-ret, "&password=%s", params->password);
    }
    ASSERT_S(ret < sizeof(query), "Out of bounds write attempt");
  }
  else if (STREQ(params->grant_type, "authorization_code")) { // web apps
    if (IS_EMPTY_STRING(params->code)) {
      log_error("Missing 'params.code'");
      return ORCA_MISSING_PARAMETER;
    }
    if (IS_EMPTY_STRING(params->redirect_uri)) {
      log_error("Missing 'params.redirect_uri'");
      return ORCA_MISSING_PARAMETER;
    }
    ret += snprintf(query+ret, sizeof(query)-ret, \
             "&code=%s&redirect_uri=%s", params->code, params->redirect_uri);
    ASSERT_S(ret < sizeof(query), "Out of bounds write attempt");
  }
  else if (!STREQ(params->grant_type, "refresh_token")) {
    log_error("Unknown 'grant_type' value (%s)", params->grant_type);
    return ORCA_BAD_PARAMETER;
  }

  struct sized_buffer req_body = { query, ret };

  return reddit_adapter_run(
    &client->adapter,
    p_resp_body,
    &req_body,
    HTTP_POST, "/api/v1/access_token");
}
